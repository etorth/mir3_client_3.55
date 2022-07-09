#include "StdAfx.h"
#include "TeamProc.h"


void DevideScript(char *pszScript);

CTeamProcess::CTeamProcess()
:m_xImage(g_xGameProc.m_xImage),
m_xMap(g_xGameProc.m_xMap),
m_stMapItemList(g_xGameProc.m_stMapItemList)
{
	m_pMyHero = new CTeamHero;
	m_pSocket = new CClientSocket;
	Init();
}


CTeamProcess::~CTeamProcess()
{
	DeleteProc();
	delete m_pMyHero;
	delete m_pSocket;
}


VOID CTeamProcess::Init()
{
	m_nProcState = _LOGIN_PROC;
	m_nBuff = 0;
	m_bLoad = FALSE;

	ZeroMemory(&m_ptMousePos, sizeof(POINT));
	ZeroMemory(&m_ptCurrTile, sizeof(POINT));
	ZeroMemory(m_stMemMappedID, sizeof(MEMMAPPEDID)*_VIEW_CELL_X_COUNT* _VIEW_CELL_Y_COUNT);

	m_pxMouseTargetActor	= NULL;		// ÇöÀç ¸¶¿ì½º°¡ °¡¸®Å°´Â °÷ÀÇ Å¸°Ù¾×ÅÍ.
	m_pxMouseOldTargetActor	= NULL;		// ÀúÀåµÇ¾îÀÖ´Â Å¸°Ù¾×ÅÍ.
	m_pxSavedTargetActor	= NULL;

	ZeroMemory(m_szMapName, MAX_PATH);

	m_pMyHero->InitActor();
	m_pMyHero->SetSocket( m_pSocket );

//	m_xMap.InitMapHandler();

	ReadIniFileForTeam();
}


VOID CTeamProcess::DeleteProc()
{
	INT			nCnt;
	SHORT		shLeftMsgCnt;
	LPPACKETMSG	lpPacketMsg;

	m_bLoad = FALSE;

	lpPacketMsg  = NULL;
	shLeftMsgCnt = m_xWaitPacketQueue.GetCount();

	// É¾³ýÃ»ÄÜ´¦ÀíÍêÈ«µÄÐÐ¶¯ÏûÏ¢
	if ( shLeftMsgCnt > 0 )
	{
		for ( nCnt = 0; nCnt < shLeftMsgCnt; nCnt++ )
		{
			lpPacketMsg = (LPPACKETMSG)m_xWaitPacketQueue.PopQ();
			if ( lpPacketMsg )
			{
				SAFE_DELETE(lpPacketMsg);
			}
		}
	}

	lpPacketMsg  = NULL;
	shLeftMsgCnt = m_xWaitDefaultPacketQueue.GetCount();

	// ½×¿©ÀÖ´Â ÆÐÅ¶À» Áö¿î´Ù.
	if ( shLeftMsgCnt > 0 )
	{
		for ( nCnt = 0; nCnt < shLeftMsgCnt; nCnt++ )
		{
			lpPacketMsg = (LPPACKETMSG)m_xWaitDefaultPacketQueue.PopQ();
			if ( lpPacketMsg )
			{
				SAFE_DELETE(lpPacketMsg);
			}
		}
	}


	m_pMyHero->DestroyActor();

	m_xActorList.ClearAllNodes();
	m_stMapItemList.ClearAllNodes();

	m_pSocket->DisconnectToServer();
	Init();//clear zero
}

VOID CTeamProcess::Load(DWORD dwMsgFilter)
{
	if( m_bLoad )
		DeleteProc();

	m_bLoad = TRUE;
	m_DecMsg.Init();

	m_pMyHero->m_bActive = FALSE;
	strcpy( m_szServerIP, g_szLoginServerIP );
	m_nServerPort = g_nLoginServerPort;

	m_pSocket->m_pxDefProc = this;
	m_pSocket->ConnectToServer(g_xMainWnd.GetSafehWnd(), m_szServerIP, m_nServerPort, dwMsgFilter);

}	


VOID CTeamProcess::LoadMapChanged(CHAR* szMap)
{
//	m_xMap.LoadMapData(szMap);

	ZeroMemory(m_stMemMappedID, sizeof(MEMMAPPEDID)*_VIEW_CELL_X_COUNT* _VIEW_CELL_Y_COUNT);
}



 
BOOL CTeamProcess::TargetInLongAttack(BYTE bDir)
{
	INT		nCnt;
	POINT	ptLongTarget;
	if ( !m_xMap.GetNextTileCanMove(m_pMyHero->m_wPosX, m_pMyHero->m_wPosY, bDir, 2, &ptLongTarget) )
	{
		CActor*	pxActor;
		m_xActorList.MoveCurrentToTop();
		for ( nCnt = 0; nCnt < m_xActorList.GetCounter(); nCnt++)
		{
			pxActor = m_xActorList.GetCurrentData();

			if ( pxActor->m_wPosX == ptLongTarget.x && pxActor->m_wPosY == ptLongTarget.y )
			{
				return TRUE;
			}
			
			m_xActorList.MoveNextNode();
		}
	}

	return FALSE;
}


VOID CTeamProcess::CheckMappedData(INT nLoopTime, BOOL bIsMoveTime)
{
	INT		nCnt, nObjCnt;
	BOOL	bIsSaveTargetExisted = FALSE;
	BOOL	bFocused;

	ZeroMemory(m_stMemMappedID, sizeof(MEMMAPPEDID)*_VIEW_CELL_X_COUNT* _VIEW_CELL_Y_COUNT);

	CActor* pxActor = NULL;
	CActor* pxDeadTargetActor = NULL;

	m_xActorList.MoveCurrentToTop();
	for ( nCnt = 0; nCnt < m_xActorList.GetCounter(); )
	{
		pxActor = m_xActorList.GetCurrentData();

		if ( !pxActor )
		{
			m_xActorList.MoveNextNode();
			continue;
		}

		switch ( pxActor->m_stFeature.bGender )
		{
		case _GENDER_MAN:
		case _GENDER_WOMAN:
			{
				CHero* pxHero;
				pxHero = (CHero*)pxActor;
				pxHero->UpdateMotionState(nLoopTime, bIsMoveTime);
				m_xActorList.MoveNextNode();
				nCnt++;
			}
			break;
		case _GENDER_NPC:
			{
				CNPC* pxNPC;
				pxNPC = (CNPC*)pxActor;
				pxNPC->UpdateMotionState(nLoopTime, bIsMoveTime);
				m_xActorList.MoveNextNode();
				nCnt++;
			}
			break;
		case _GENDER_MON:
			{
				pxActor->UpdateMotionState(nLoopTime, bIsMoveTime);

				if ( pxActor->m_bAppearState == _DIG_DOWNDEL )
				{
					m_xActorList.DeleteCurrentNodeEx();
					delete((CActor*)pxActor);
					pxActor = NULL;
				}
				else
				{
					m_xActorList.MoveNextNode();
					nCnt++;
				}
			}
			break;
		default:
			m_xActorList.MoveNextNode();
			nCnt++;
		}

		if ( !pxActor )
			continue;

		if ( pxActor->m_wPosX >= m_xMap.m_shStartViewTileX && pxActor->m_wPosX < m_xMap.m_shStartViewTileX + _VIEW_CELL_X_COUNT && 
			 pxActor->m_wPosY >= m_xMap.m_shStartViewTileY && pxActor->m_wPosY < m_xMap.m_shStartViewTileY + _VIEW_CELL_Y_COUNT )				 
		{
			for ( nObjCnt = 0; nObjCnt < _MAX_CELL_OBJ; nObjCnt++ )
			{
				if ( m_stMemMappedID[pxActor->m_wPosY - m_xMap.m_shStartViewTileY][pxActor->m_wPosX - m_xMap.m_shStartViewTileX].pxActor[nObjCnt] == NULL )
				{
					bFocused = FALSE;
					if ( pxActor == m_pxSavedTargetActor )
					{
						bIsSaveTargetExisted = TRUE;
					}

					// ±×¸²ÀÇ ½ÃÀÛÁÂÇ¥, Æ÷Ä¿½º»óÅÂ, ±×¸²ÀÚ ºí·»µù »óÅÂ¸¦ ³Ñ°ÜÁØ´Ù.
					if ( !m_pxMouseTargetActor /*&& !pxActor->m_bIsDead*/ )
					{
						if ( PtInRect(&pxActor->m_rcActor, m_ptMousePos) )
						{
							m_pxMouseTargetActor = pxActor;
							bFocused = TRUE;
						}
					}
					else
					{
						if ( PtInRect(&pxActor->m_rcTargetRgn, m_ptMousePos) )
						{
							if ( !pxActor->m_bIsDead )
							{
								m_pxMouseTargetActor = pxActor;
								bFocused = TRUE;
							}
							else
							{
								pxDeadTargetActor = pxActor;
								bFocused = TRUE;
							}
						}
					}	

					// Á×Àº Actor´Â ¾ÕÀ¸·Î ¶¯±ä´Ù.
					if ( pxActor->m_bIsDead )
					{
						CActor* pxTempActor[_MAX_CELL_OBJ];
						ZeroMemory(pxTempActor, sizeof(CActor*)*_MAX_CELL_OBJ);

						pxTempActor[0] = pxActor;
						memcpy(&pxTempActor[1], m_stMemMappedID[pxActor->m_wPosY - m_xMap.m_shStartViewTileY][pxActor->m_wPosX - m_xMap.m_shStartViewTileX].pxActor, sizeof(CActor*)*(_MAX_CELL_OBJ-1));
						memcpy(m_stMemMappedID[pxActor->m_wPosY - m_xMap.m_shStartViewTileY][pxActor->m_wPosX - m_xMap.m_shStartViewTileX].pxActor, pxTempActor, sizeof(CActor*)*(_MAX_CELL_OBJ));

						switch ( pxActor->m_stFeature.bGender )
						{
						case _GENDER_MAN:
						case _GENDER_WOMAN:
							{
								CHero* pxHero;
								pxHero = (CHero*)pxActor;
								pxHero->DrawActor(&m_xMap, bFocused);
							}
							break;
						case _GENDER_NPC:
							{
								CNPC* pxNPC;
								pxNPC = (CNPC*)pxActor;
								pxNPC->DrawActor(&m_xMap, bFocused);
							}
							break;
						case _GENDER_MON:
							{
								pxActor->DrawActor(&m_xMap, bFocused);
							}
							break;
						}

					}
					else
						m_stMemMappedID[pxActor->m_wPosY - m_xMap.m_shStartViewTileY][pxActor->m_wPosX - m_xMap.m_shStartViewTileX].pxActor[nObjCnt] = pxActor;

					break;
				}
			}
		}
	} 

	if ( !bIsSaveTargetExisted )		m_pxSavedTargetActor = NULL;

	if ( !m_pxMouseTargetActor && pxDeadTargetActor )
	{
		m_pxMouseTargetActor = pxDeadTargetActor;
	}

	CMagic* pxMagic;
	m_xGroundMagicList.MoveCurrentToTop();
	for ( nCnt = 0; nCnt < m_xGroundMagicList.GetCounter(); )
	{
		pxMagic = m_xGroundMagicList.GetCurrentData();

		if ( pxMagic->m_bMagicNum == _SKILL_HOLYSHIELD || pxMagic->m_bMagicNum == _SKILL_EARTHFIRE )
		{
			CRepeatMagic* pxRepeatMagic = (CRepeatMagic*)pxMagic;

			pxRepeatMagic->UpdateMagic(nLoopTime);

			if ( pxRepeatMagic->m_bActiveState == _MAGIC_FINISH )
			{
				m_xGroundMagicList.DeleteCurrentNodeEx();
				delete((CRepeatMagic*)pxRepeatMagic);
				pxRepeatMagic = NULL;
			}
			else
			{
				if ( pxMagic->m_shTargetTileX >= m_xMap.m_shStartViewTileX && pxMagic->m_shTargetTileX < m_xMap.m_shStartViewTileX  + _VIEW_CELL_X_COUNT && 
					 pxMagic->m_shTargetTileY >= m_xMap.m_shStartViewTileY && pxMagic->m_shTargetTileY < m_xMap.m_shStartViewTileY  + _VIEW_CELL_Y_COUNT )
				{
					for ( nObjCnt = 0; nObjCnt < _MAX_CELL_OBJ; nObjCnt++ )
					{
						if ( m_stMemMappedID[pxMagic->m_shTargetTileY - m_xMap.m_shStartViewTileY][pxMagic->m_shTargetTileX - m_xMap.m_shStartViewTileX].pxMagic[nObjCnt] == NULL )
						{
 							m_stMemMappedID[pxMagic->m_shTargetTileY - m_xMap.m_shStartViewTileY][pxMagic->m_shTargetTileX - m_xMap.m_shStartViewTileX].pxMagic[nObjCnt] = pxMagic;
							break;
						}
					}
				}

				m_xGroundMagicList.MoveNextNode();
				nCnt++;
			}
		}
		else if ( pxMagic->m_bMagicNum == _SKILL_FIRE )
		{
			CMagicStream* pxMagicStream = (CMagicStream*)pxMagic;

			pxMagicStream->UpdateMagic(nLoopTime);

			if ( pxMagicStream->m_bActiveState == _MAGIC_FINISH )
			{
				m_xGroundMagicList.DeleteCurrentNodeEx();
				delete((CMagicStream*)pxMagicStream);
				pxMagicStream = NULL;
			}
			else
			{
				if ( pxMagic->m_shTargetTileX >= m_xMap.m_shStartViewTileX && pxMagic->m_shTargetTileX < m_xMap.m_shStartViewTileX  + _VIEW_CELL_X_COUNT && 
					 pxMagic->m_shTargetTileY >= m_xMap.m_shStartViewTileY && pxMagic->m_shTargetTileY < m_xMap.m_shStartViewTileY  + _VIEW_CELL_Y_COUNT )
				{
					for ( nObjCnt = 0; nObjCnt < _MAX_CELL_OBJ; nObjCnt++ )
					{
						if ( m_stMemMappedID[pxMagic->m_shTargetTileY - m_xMap.m_shStartViewTileY][pxMagic->m_shTargetTileX - m_xMap.m_shStartViewTileX].pxMagic[nObjCnt] == NULL )
						{
							m_stMemMappedID[pxMagic->m_shTargetTileY - m_xMap.m_shStartViewTileY][pxMagic->m_shTargetTileX - m_xMap.m_shStartViewTileX].pxMagic[nObjCnt] = pxMagic;
							break;
						}
					}
				}

				m_xGroundMagicList.MoveNextNode();
				nCnt++;
			}
		}
	}		
	
	LPGROUNDITEM pstItem;
	m_stMapItemList.MoveCurrentToTop();
	for ( nCnt = 0; nCnt < m_stMapItemList.GetCounter(); nCnt++ )
	{
		pstItem = m_stMapItemList.GetCurrentData();

		if ( pstItem->shTileX >= m_xMap.m_shStartViewTileX && pstItem->shTileX < m_xMap.m_shStartViewTileX  + _VIEW_CELL_X_COUNT && 
			 pstItem->shTileY >= m_xMap.m_shStartViewTileY && pstItem->shTileY < m_xMap.m_shStartViewTileY  + _VIEW_CELL_Y_COUNT )
		{
			for ( nObjCnt = 0; nObjCnt < _MAX_CELL_OBJ; nObjCnt++ )
			{
				if ( m_stMemMappedID[pstItem->shTileY - m_xMap.m_shStartViewTileY][pstItem->shTileX - m_xMap.m_shStartViewTileX].pstItem[nObjCnt] == NULL )
				{
					m_stMemMappedID[pstItem->shTileY - m_xMap.m_shStartViewTileY][pstItem->shTileX - m_xMap.m_shStartViewTileX].pstItem[nObjCnt] = pstItem;
					break;
				}
			}
		}

		m_stMapItemList.MoveNextNode();
	}
}


VOID CTeamProcess::AutoTargeting()
{
	static BYTE bLastDir = _DIRECTION_LIST_1;

	if ( !m_pMyHero->m_bMotionLock && !m_pMyHero->m_bInputLock && m_pxSavedTargetActor )
	{
		SHORT shLeftMsgCnt = m_pMyHero->m_xPacketQueue.GetCount();
		if ( shLeftMsgCnt > 0 )
		{
			if ( m_pMyHero->m_stFeatureEx.bHorse == _HORSE_NONE )	m_pMyHero->SetMotionState(_MT_STAND,      m_pMyHero->m_bCurrDir);
			else													m_pMyHero->SetMotionState(_MT_HORSESTAND, m_pMyHero->m_bCurrDir);
			m_pMyHero->UpdatePacketState();
			return;
		}

		POINT ptTargetTile = {0, 0};
		BYTE bDir = m_pMyHero->CalcDirection(m_pxSavedTargetActor->m_wPosX, m_pxSavedTargetActor->m_wPosY);

		if ( m_pxSavedTargetActor->m_bIsDead )
			return;

		if ( (m_pxSavedTargetActor->m_stFeature.bGender == _GENDER_MON && m_pxSavedTargetActor->m_bCurrMtn == _MT_MON_DIE) ||
			 (m_pxSavedTargetActor->m_stFeature.bGender <= _GENDER_WOMAN && m_pxSavedTargetActor->m_bCurrMtn == _MT_DIE) )
			 return;


		if ( (INT)(sqrt((float)(m_pMyHero->m_wPosX-m_pxSavedTargetActor->m_wPosX)*(m_pMyHero->m_wPosX-m_pxSavedTargetActor->m_wPosX) + 	(m_pMyHero->m_wPosY-m_pxSavedTargetActor->m_wPosY)*(m_pMyHero->m_wPosY-m_pxSavedTargetActor->m_wPosY)))
			      < 2 )
		{
			if ( m_pMyHero->m_stFeatureEx.bHorse == _HORSE_NONE && !m_pxSavedTargetActor->m_bIsDead )
			{
				// °ø°ÝÇÑ´Ù.
				ptTargetTile.x = m_pMyHero->m_wPosX;
				ptTargetTile.y = m_pMyHero->m_wPosY;
				m_pMyHero->SetMotionState(_MT_ONEHSWING, bDir, m_pxSavedTargetActor->m_dwIdentity, m_pxSavedTargetActor->m_bIsDead, &ptTargetTile);
			}
		}
		// Actor°¡ ÀÖ´Â ¹æÇâÀ¸·Î ÀÌµ¿ °¡´ÉÇÑ°¡?(¸Ê¼Ó¼ºÃ¼Å©) 
		else if ( m_xMap.GetNextTileCanMove(m_pMyHero->m_wPosX, m_pMyHero->m_wPosY, bDir, 1, &ptTargetTile) )
		{
			// 1Å¸ÀÏ ÀÌµ¿ÇÑ´Ù.
			if ( m_pMyHero->m_stFeatureEx.bHorse == _HORSE_NONE )
			{
				m_pMyHero->SetMotionState(_MT_WALK, bDir);
			}
			else
			{
				m_pMyHero->SetMotionState(_MT_HORSEWALK, bDir);
			}
			bLastDir = bDir;
		}
		else if ( !m_xMap.GetNextTileCanMove(m_pMyHero->m_wPosX, m_pMyHero->m_wPosY, bDir, 1, &ptTargetTile) )
		{
			BYTE	bSelectedDirList[8] = {0, 0, 0, 0, 0, 0, 0, 0};
			INT		nSeclectedDirCnt = -1;
			INT		nLastDistance = 100;
			INT		nCurrDistance;
			BYTE	bInvDir;
			BYTE	bSelectedDir = 255;

			if ( bLastDir < 4 )		bInvDir = bLastDir + 4;
			else					bInvDir = bLastDir - 4;

			INT nCnt;
			for ( nCnt = 0; nCnt < _MAX_DIRECTION; nCnt++ )
			{
				if ( m_xMap.GetNextTileCanMove(m_pMyHero->m_wPosX, m_pMyHero->m_wPosY, nCnt, 1, &ptTargetTile) )
				{
					nCurrDistance = (INT)(sqrt((float)(ptTargetTile.x-m_pxSavedTargetActor->m_wPosX)*(ptTargetTile.x-m_pxSavedTargetActor->m_wPosX) + (ptTargetTile.y-m_pxSavedTargetActor->m_wPosY)*(ptTargetTile.y-m_pxSavedTargetActor->m_wPosY)));
					if ( nCurrDistance <= nLastDistance && bInvDir != nCnt )
					{
						nLastDistance = nCurrDistance;
						nSeclectedDirCnt++;
						bSelectedDirList[nSeclectedDirCnt] = nCnt;
					}
				}
			}

			BYTE bDirOrderList[8][8] = 
			{
				{0, 7, 1, 6, 2, 5, 3, 4},
				{1, 0, 2, 7, 3, 6, 4, 5},
				{2, 1, 3, 0, 4, 7, 5, 6},
				{3, 2, 4, 1, 5, 0, 6, 7},
				{4, 5, 3, 6, 2, 7, 1, 0},
				{5, 6, 4, 7, 3, 0, 2, 1},
				{6, 7, 5, 0, 4, 1, 3, 2},
				{7, 0, 6, 1, 5, 2, 4, 3},
			};

			BYTE bOrderCnt = 0;

			for ( nCnt = 0; nCnt < nSeclectedDirCnt; nCnt++ )
			{
				while ( bSelectedDirList[nCnt] != bDirOrderList[bDir][bOrderCnt] || bOrderCnt < 8 )	bOrderCnt++;
				if ( bOrderCnt >= 8 )			bOrderCnt = 0;
				else					
				{	bSelectedDir = bLastDir = bSelectedDirList[nCnt];	break;	}
			}

			if ( bSelectedDir == 255 )		bSelectedDir = bLastDir = bSelectedDirList[GetRandomNum(0, nSeclectedDirCnt+1)];
	

			if ( nSeclectedDirCnt != -1 )
			{
				// 1Å¸ÀÏ ÀÌµ¿ÇÑ´Ù.
				m_xMap.GetNextTileCanMove(m_pMyHero->m_wPosX, m_pMyHero->m_wPosY, bSelectedDir, 1, &ptTargetTile);
				if ( m_pMyHero->m_stFeatureEx.bHorse == _HORSE_NONE )
				{
					m_pMyHero->SetMotionState(_MT_WALK, bSelectedDir);
				}
				else
				{
					m_pMyHero->SetMotionState(_MT_HORSEWALK, bSelectedDir);
				}
			}
			else
			{
				if ( m_pMyHero->m_stFeatureEx.bHorse == _HORSE_NONE )
				{
					m_pMyHero->SetMotionState(_MT_STAND, bDir);
				}
				else
				{
					m_pMyHero->SetMotionState(_MT_HORSESTAND, bDir);
				}
			}
		}
		else
		{
			if ( m_pMyHero->m_stFeatureEx.bHorse == _HORSE_NONE )
			{
				m_pMyHero->SetMotionState(_MT_STAND, bDir);
			}
			else
			{
				m_pMyHero->SetMotionState(_MT_HORSESTAND, bDir);
			}
		}
	}
}



VOID CTeamProcess::RenderScene(INT nLoopTime)
{
	BOOL		 bIsMoveTime	= FALSE;
	static WORD	 wMoveTime		= 0;
	static DWORD dwReceiveTime	= 0;

	wMoveTime			  += nLoopTime;
	m_wCurrInputDelayTime += nLoopTime;

	if( !m_bLoad) return;

	if ( nLoopTime < 10000 )		dwReceiveTime += nLoopTime;
	if ( m_wCurrInputDelayTime >= m_wInputDelayTime )
	{
		m_wCurrInputDelayTime	= 0;
		m_wInputDelayTime		= 0;
	}
	if ( wMoveTime > 100 )
	{
		bIsMoveTime = TRUE;
		wMoveTime	= 0;
	}

	if ( !m_bRender && dwReceiveTime > 100000 )
	{
		g_xGameProc.m_xInterface.MsgAdd( _CLR_RED, _CLR_BLACK, "TeamProc:½ÓÊÕÊý¾Ý³¬Ê±" );
		dwReceiveTime = 0;
	}	
	
	//¿½±´¹²ÏíÊý¾Ý
	m_pxMouseTargetActor	= g_xGameProc.m_pxMouseTargetActor;
	m_pxMouseOldTargetActor	= g_xGameProc.m_pxMouseOldTargetActor;
	m_pxSavedTargetActor	= g_xGameProc.m_pxSavedTargetActor;


	//Ö÷ÒªÊÇ¿½±´g_xGameProcµÄÊý¾Ý,»òÕß¸üÐÂg_xGameProcµÄÊý¾Ý



	if ( m_bRender )
	{
		CMyHero* pHero = (CMyHero*)g_xGameProc.FindActor( m_pMyHero->m_dwIdentity );
		if( pHero )
		{
			memcpy( &m_pMyHero->m_rcActor, &pHero->m_rcActor, sizeof(RECT) );
			m_pMyHero->m_wPosX = pHero->m_wPosX;//FIXME ¸ÄÎª×Ô¼º½âÎö
			m_pMyHero->m_wPosY = pHero->m_wPosY;
			m_pMyHero->DrawName();
		}

		m_pMyHero->UpdateMotionState(nLoopTime, bIsMoveTime);
	//	CheckMappedData(nLoopTime, bIsMoveTime);
		AutoTargeting();

	}
}



LRESULT CTeamProcess::OnDestroy(WPARAM wParam, LPARAM lParam)
{
	return 0L;
}

void CTeamProcess::ProcessLogin(char* pszMsg)
{
	_TDEFAULTMESSAGE	tdm;
	fnDecodeMessage(&tdm, pszMsg);
	DWORD dwEventFilter;

	//LOGIN
	if( m_nProcState == _LOGIN_PROC )
	{
		if( tdm.wIdent == SM_PASSOK_SELECTSERVER )
		{
			g_xGameProc.m_xInterface.MsgAdd( _CLR_RED, 0, "ÃÜÂëÑéÖ¤³É¹¦" );
			Sleep(1000);
			m_pSocket->OnSelectServer( m_szServer );

		}
		else if( tdm.wIdent == SM_SELECTSERVER_OK )
		{
			//210.22.194.216/7100/1090502
			char szDecodeMsg[256];
			char *pszIP = szDecodeMsg, *pszPort, *pszIdenty;

			ZeroMemory(szDecodeMsg, sizeof(szDecodeMsg));

			fnDecode6BitBuf((pszMsg + DEFBLOCKSIZE), szDecodeMsg, sizeof(szDecodeMsg));

			if (pszPort = strchr(szDecodeMsg, '/')){
				*pszPort = '\0';
				pszPort++;

				if (pszIdenty = strchr(pszPort, '/')){
					*pszIdenty = '\0';
					pszIdenty++;

					strcpy(m_szServerIP, pszIP);
					m_nServerPort = atoi(pszPort);

					m_nCertifyCode = tdm.nRecog;
					dwEventFilter = m_pSocket->m_dwEventFilter;
					m_pSocket->DisconnectToServer();
				}
			}
			//Á¬½Óµ½Ñ¡½Ç·þÎñÆ÷

			m_pSocket->ConnectToServer(g_xMainWnd.GetSafehWnd(), m_szServerIP, m_nServerPort, dwEventFilter);
			m_nProcState = _SVR_SEL_PROC;
			
		}
		else
		{
			g_xGameProc.m_xInterface.MsgAdd(_CLR_RED, 0, "µÇÂ½Ê§°Ü" );
			m_bLoad = FALSE;
			dwEventFilter = m_pSocket->m_dwEventFilter;
			m_pSocket->DisconnectToServer();
		}
	}

	if( m_nProcState == _SVR_SEL_PROC )
	{
		switch(tdm.wIdent)
		{
		case SM_QUERYCHR:
			m_pSocket->OnSelChar( m_szUser, m_szCharName );
			break;
		case	SM_NEWCHR_SUCCESS:		// New character Create Success
			break;
		case	SM_STARTPLAY:			// Start Game
			{
				char	szDecodeMsg[512];
				char	*pszIP = &szDecodeMsg[0], *pszPort;

				ZeroMemory(szDecodeMsg, sizeof(szDecodeMsg));

				fnDecode6BitBuf((pszMsg + DEFBLOCKSIZE), szDecodeMsg, sizeof(szDecodeMsg));

				if (pszPort = strchr(pszIP, '/'))
				{
					*pszPort = '\0';
					pszPort++;
					strcpy(m_szServerIP, pszIP);
					m_nServerPort = atoi(pszPort);
					dwEventFilter = m_pSocket->m_dwEventFilter;
					m_pSocket->DisconnectToServer();

					//Á¬½ÓGameGate
					m_pSocket->ConnectToServer(g_xMainWnd.GetSafehWnd(), m_szServerIP, m_nServerPort, dwEventFilter);
					m_nProcState = _CHAR_SEL_PROC;

				}
				break;
			}
		}
	}
}


LRESULT CTeamProcess::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{	
	if ( !m_bRender )			return 0L;
	
	POINT ptTaretTilePos;
	m_pxSavedTargetActor = NULL;

	m_pMyHero->m_wABlendDelay = 0;
	m_pMyHero->m_bMotionLock = FALSE;
	m_pMyHero->m_bInputLock = FALSE;

	m_ptMousePos.x = LOWORD(lParam);
	m_ptMousePos.y = HIWORD(lParam);
	m_ptCurrTile.x = m_xMap.m_shStartViewTileX + (m_ptMousePos.x - _VIEW_CELL_X_START) / TILE_WIDTH;
	m_ptCurrTile.y = m_xMap.m_shStartViewTileY + (m_ptMousePos.y - _VIEW_CELL_Y_START) / TILE_HEIGHT;

	if ( true/*!m_xInterface.OnLButtonDown(m_ptMousePos)*/ )
	{
		// ÀÎÅÍÆäÀÌ½º¿¡¼­ ÇÏ´ÂÀÏÀÌ ¾øÀ»¶§.

		// 1. ÈÓ¶«Î÷
//		if ( m_xInterface.m_stCommonItem.bSetted && !m_xInterface.m_stCommonItem.bWaitResponse && !m_xInterface.m_stCommonItem.bIsEquipItem )
//		{
//			m_pSocket->SendItemIndex(CM_DROPITEM, m_xInterface.m_stCommonItem.xItem.m_stItemInfo.nMakeIndex, m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName);
//			m_xInterface.m_stCommonItem.bWaitResponse = TRUE;
//			return 0L;
//		}

		// 2. ¼ñ¶«Î÷
		if ( m_stMapItemList.GetCounter() != 0 )
		{
			m_stMapItemList.MoveCurrentToTop();
			LPGROUNDITEM pstItem;

			for ( INT nCnt = 0; nCnt < m_stMapItemList.GetCounter(); nCnt++ )
			{
				pstItem = m_stMapItemList.GetCurrentData();

				if ( pstItem->shTileX == m_ptCurrTile.x && pstItem->shTileY == m_ptCurrTile.y && pstItem->shTileX == m_pMyHero->m_wPosX && pstItem->shTileY == m_pMyHero->m_wPosY )
				{
					m_pSocket->SendPickUp(pstItem->shTileX, pstItem->shTileY);
					return 0L;
				}
				m_stMapItemList.MoveNextNode();
			}
		}

		if ( m_pxMouseTargetActor )
		{
			if ( !m_pxMouseTargetActor->m_bIsDead )
			{
				// °ø°Ý´ë»ó ActorÁ¤ÇÏ±â.
				m_pxSavedTargetActor = m_pxMouseTargetActor;
			}

//			ptTaretTilePos.x = m_pxMouseTargetActor->m_wPosX;
//			ptTaretTilePos.y = m_pxMouseTargetActor->m_wPosY;
//			if ( m_pxMouseTargetActor->m_stFeature.bGender == _GENDER_NPC )
//			{
//				m_pSocket->SendNPCClick(m_pxMouseTargetActor->m_dwIdentity);
//				m_pxSavedTargetActor = NULL;
//			}
//			else
			{
				m_pMyHero->OnLButtonDown(m_ptMousePos, m_pxMouseTargetActor->m_dwIdentity, m_pxMouseTargetActor->m_bIsDead, &ptTaretTilePos);
			}
		}
		else
		{
			m_pMyHero->OnLButtonDown(m_ptMousePos);
		}
	}

	return 0L;
}


LRESULT CTeamProcess::OnRButtonDown(WPARAM wParam, LPARAM lParam)
{	
	if ( !m_bRender )			return 0L;

	m_ptMousePos.x = LOWORD(lParam);
	m_ptMousePos.y = HIWORD(lParam);

	m_ptCurrTile.x = m_xMap.m_shStartViewTileX + (m_ptMousePos.x - _VIEW_CELL_X_START) / TILE_WIDTH;
	m_ptCurrTile.y = m_xMap.m_shStartViewTileY + (m_ptMousePos.y - _VIEW_CELL_Y_START) / TILE_HEIGHT;

	m_pxSavedTargetActor = NULL;

	m_pMyHero->OnRButtonDown(m_ptMousePos);

	return 0L;
}


LRESULT CTeamProcess::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	if ( !m_bRender )			return 0L;

	m_ptMousePos.x = LOWORD(lParam);
	m_ptMousePos.y = HIWORD(lParam);
	m_ptCurrTile.x = m_xMap.m_shStartViewTileX + (m_ptMousePos.x - _VIEW_CELL_X_START) / TILE_WIDTH;
	m_ptCurrTile.y = m_xMap.m_shStartViewTileY + (m_ptMousePos.y - _VIEW_CELL_Y_START) / TILE_HEIGHT;

	return 0L;
}


LRESULT CTeamProcess::OnRButtonUp(WPARAM wParam, LPARAM lParam)
{
	m_ptMousePos.x = LOWORD(lParam);
	m_ptMousePos.y = HIWORD(lParam);
	m_ptCurrTile.x = m_xMap.m_shStartViewTileX + (m_ptMousePos.x - _VIEW_CELL_X_START) / TILE_WIDTH;
	m_ptCurrTile.y = m_xMap.m_shStartViewTileY + (m_ptMousePos.y - _VIEW_CELL_Y_START) / TILE_HEIGHT;

	return 0L;
}



LRESULT CTeamProcess::OnTimer(WPARAM wParam, LPARAM lParam)
{
	if ( wParam != _TIMER_ID )
	{
		if (m_pSocket->m_PacketQ.GetCount())
		{
			char *pszPacket = (char*)m_pSocket->m_PacketQ.PopQ();

			if (pszPacket)
			{
				strcpy(&m_szBuff[m_nBuff], pszPacket);

				char *pszRemain = OnMessageReceive(m_szBuff);

				if (pszRemain)
				{
					m_nBuff = strlen(pszRemain);
					memcpy(m_szBuff, pszRemain, m_nBuff);
					m_szBuff[m_nBuff] = '\0';
				}
				else
				{
					m_nBuff = 0;
					ZeroMemory(m_szBuff, sizeof(m_szBuff));
				}

				delete [] pszPacket;
			}
		}

		ProcessPacket();
		ProcessDefaultPacket();
	}

	return 0L;
}


char* CTeamProcess::OnMessageReceive(CHAR* pszMessage)
{
	char	*pszFirst;
	char	*pszEnd;
	int		nCount = 0;

	if (*pszMessage == '*')
	{
		pszFirst = pszMessage + 1;
		send(m_pSocket->m_sockClient, "*", 1, 0);
	}
	else
		pszFirst = pszMessage;

	while (pszEnd = strchr(pszFirst, '!'))
	{
		*pszEnd++ = '\0';

		if( m_nProcState == _GAME_PROC )
			OnSocketMessageRecieve(pszFirst + 1);
		else
			ProcessLogin(pszFirst + 1);


		if (*pszEnd == '*')
		{
			send(m_pSocket->m_sockClient, "*", 1, 0);
			pszEnd++;
		}

		if (*pszEnd == '#')
			pszFirst = pszEnd;
		else
			return NULL;
	}

	return pszFirst;
}

void CTeamProcess::OnProcPacketNotEncode(char *pszMsg)
{
	static char pszGood[]	= "GOOD";
	static char pszFail[]	= "FAIL";
	static char pszLng[]	= "LNG";
	static char pszUlng[]	= "ULNG";
	static char pszWid[]	= "WID";
	static char pszUWid[]	= "UWID";
	static char pszFir[]	= "FIR";
	static char pszUFir[]	= "UFIR";
	static char pszUPwr[]	= "PWR";

	if ( memcmp(pszMsg, pszGood, strlen(pszGood)) == 0 )
		m_pMyHero->m_bMotionLock = FALSE;
 	else if( memcmp(pszMsg, pszFail, strlen(pszFail)) == 0 )
		m_pMyHero->SetOldPosition();
 	else if( memcmp(pszMsg, pszLng, strlen(pszLng)) == 0 )
		m_pMyHero->m_bUseErgum  = TRUE;
 	else if( memcmp(pszMsg, pszUlng, strlen(pszUlng)) == 0 )
		m_pMyHero->m_bUseErgum  = FALSE;
 	else if( memcmp(pszMsg, pszWid, strlen(pszWid)) == 0 )
		m_pMyHero->m_bUseBanwol = TRUE;
 	else if( memcmp(pszMsg, pszUWid, strlen(pszUWid)) == 0 )
		m_pMyHero->m_bUseBanwol = FALSE;
 	else if( memcmp(pszMsg, pszFir, strlen(pszFir)) == 0 )
		m_pMyHero->m_bFireHitCnt  = 1;
 	else if( memcmp(pszMsg, pszUFir, strlen(pszUFir)) == 0 )
		m_pMyHero->m_bFireHitCnt  = 0;
 	else if( memcmp(pszMsg, pszUPwr, strlen(pszUPwr)) == 0 )
		m_pMyHero->m_bYedoCnt  = 1;
}

CActor*	CTeamProcess::FindActor(int nID) // gadget
{
	CActor* pxActor = NULL;

	m_xActorList.MoveCurrentToTop();
	
	for ( INT nCnt = 0; nCnt < m_xActorList.GetCounter(); nCnt++ )
	{
		pxActor = m_xActorList.GetCurrentData();

		if ( pxActor->m_dwIdentity == nID )
			return pxActor;
	
		m_xActorList.MoveNextNode();
	}

	return NULL;
}

extern "C" void sub_430230(DWORD* pShort, char* pszData);
extern "C" void sub_42F6B0(char* pszData);
extern "C" void sub_47D330(char* pszData);

void CTeamProcess::OnSocketMessageRecieve(char *pszMsg)
{
	if (*pszMsg == '+')
		OnProcPacketNotEncode(pszMsg + 1);
	else
	{
		int					nPos = 0;
		_TDEFAULTMESSAGE	tdm;

		fnDecodeMessage(&tdm, pszMsg);

		//ÐÂ°æµÄÏûÏ¢Í·¾­¹ý¼ÓÃÜµÄ,½âÃÜÏÈ
		m_DecMsg.DecodeMessageHead(&tdm);
		
		//for debug
		char sztxt[128];
		sprintf( sztxt, "TeamProc RECV:nRecog=%08x,wIdent=%04x(%d),wParam=%04x,wTag=%04x,wSeries=%04x\n",
			tdm.nRecog, tdm.wIdent, tdm.wIdent, tdm.wParam, tdm.wTag, tdm.wSeries );
		OutputDebugString( sztxt);


		switch (tdm.wIdent)
		{
			case SM_DECODEKEY:
			{
				char szKey[256];
				
				////////////////////
				DWORD dwMyId = m_pMyHero->m_dwIdentity;

				memset( szKey, 0, sizeof(szKey) );
				sub_430230( &dwMyId, szKey );
				sub_42F6B0( szKey );
				m_pSocket->SendEncryption( szKey );


				nPos = fnDecode6BitBuf((pszMsg + DEFBLOCKSIZE), szKey, sizeof(szKey));
				szKey[nPos] = '\0';
				m_DecMsg.GetDecodeKey( szKey );
				break;
			}
			case SM_SENDNOTICE:
			{
//				char szDecodeMsg[8192];
//
//				nPos = fnDecode6BitBuf((pszMsg + DEFBLOCKSIZE), szDecodeMsg, sizeof(szDecodeMsg));
//				szDecodeMsg[nPos] = '\0';
//				m_xNotice.ShowMessageBox(szDecodeMsg, _IDX_IMG_NOTICEBOX);
				//²»ÐèÒªÏÔÊ¾,Ö±½Ó·¢ËÍµÇÂ½ÏûÏ¢
				m_pSocket->SendNoticeOK();
		
				OutputDebugString( "SM_SENDNOTICE\n");
				break;
			}
			case SM_NEWMAP:
				OnSvrMsgNewMap(&tdm, (pszMsg + DEFBLOCKSIZE));
				break;
			case SM_LOGON:
				OnSvrMsgLogon(&tdm, (pszMsg + DEFBLOCKSIZE));
				OutputDebugString( "SM_LOGON\n");
				break;
			case SM_MAPDESCRIPTION://µØÍ¼Ãû
				nPos = fnDecode6BitBuf((pszMsg + DEFBLOCKSIZE), (char*)m_szMapName, sizeof(m_szMapName));
				m_szMapName[nPos] = '\0';
				break;
			case SM_ABILITY:
			{
				m_pMyHero->m_nGlod	= tdm.nRecog;
				m_pMyHero->m_bJob	= tdm.wParam;	

				fnDecode6BitBuf((pszMsg + DEFBLOCKSIZE), (char*)&m_pMyHero->m_stAbility, sizeof(ACTORABILITY));
				break;
			}
			case SM_WINEXP:
			{
				m_pMyHero->m_stAbility.dwExp = tdm.nRecog;
				
				CHAR szExp[MAX_PATH];											
				sprintf(szExp, "%s : »ñµÃ¾­ÑéÖµ %d µã, ÎäÆ÷ÐÞÁ¶Öµ %d", m_pMyHero->m_szName, tdm.wParam, tdm.wTag);
				
				DWORD dwFont = GetChatColor(_CHAT_COLOR4);
				DWORD dwBack = GetChatColor(_CHAT_COLOR3);
				g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, szExp);

				break;
			}
			case SM_SUBABILITY:
			{
				m_pMyHero->m_stSubAbility.wAntiMagic		= LOWORD(LOBYTE(tdm.nRecog));	
				m_pMyHero->m_stSubAbility.bHitPoint		= LOBYTE(tdm.wParam);	
				m_pMyHero->m_stSubAbility.bSpeedPoint	= HIBYTE(tdm.wParam);	
				m_pMyHero->m_stSubAbility.bAntiPoison	= LOBYTE(tdm.wTag);	
				m_pMyHero->m_stSubAbility.bPoisonRecover = HIBYTE(tdm.wTag);				
				m_pMyHero->m_stSubAbility.bHealthRecover = LOBYTE(tdm.wSeries);
				m_pMyHero->m_stSubAbility.bSpellRecover	= HIBYTE(tdm.wSeries);

				break;
			}
			case SM_SENDMYMAGIC:
			{
//				SAFE_DELETE(m_xInterface.m_xStatusWnd.m_pstMyMagic);
//				
//				m_xInterface.m_xStatusWnd.m_bMyMagicCnt = tdm.wSeries;
//				m_xInterface.m_xStatusWnd.m_pstMyMagic	= new CLIENTMAGICRCD[m_xInterface.m_xStatusWnd.m_bMyMagicCnt];
//				
//				ZeroMemory(m_xInterface.m_xStatusWnd.m_pstMyMagic, sizeof(CLIENTMAGICRCD) * m_xInterface.m_xStatusWnd.m_bMyMagicCnt);
//
//				char *pszMagic = (pszMsg + DEFBLOCKSIZE);
//				char *pszNextMagic;
//
//				for ( INT nLoop = 0; nLoop < m_xInterface.m_xStatusWnd.m_bMyMagicCnt; nLoop++ )
//				{
//					if (pszNextMagic = strchr(pszMagic, '/'))
//					{
//						*pszNextMagic = '\0';
//
//						fnDecode6BitBuf(pszMagic, (char*)&m_xInterface.m_xStatusWnd.m_pstMyMagic[nLoop], sizeof(CLIENTMAGICRCD));
//
//						pszMagic = pszNextMagic + 1;
//					}
//				}
//
				break;
			} 
			case SM_MAGIC_LVEXP:
			{
//				for ( INT nLoop = 0; nLoop < m_xInterface.m_xStatusWnd.m_bMyMagicCnt; nLoop++ )
//				{
//					if ( m_xInterface.m_xStatusWnd.m_pstMyMagic[nLoop].stStdMagic.wMagicID == tdm.nRecog )
//					{
//						m_xInterface.m_xStatusWnd.m_pstMyMagic[nLoop].nCurrTrain	= MAKELONG(tdm.wTag, tdm.wSeries);
//						m_xInterface.m_xStatusWnd.m_pstMyMagic[nLoop].bLevel		= tdm.wParam;
//
//						break;
//					}
//				}
				break;
			}
			case SM_BAGITEMS:
			{
//				char *pszItem  = (pszMsg + DEFBLOCKSIZE);
//				char *pszNextItem;
//				int  nCount = 0;
//				CLIENTITEMRCD	stReceivedItem;//Õâ¸öÓÐ¸Ä±ä
//				CItem			xItem;
//				m_xInterface.m_xInventoryWnd.DeleteAllInvenItem();
//				do
//				{
//					if (pszNextItem = strchr(pszItem, '/'))
//					{
//						*pszNextItem = '\0';
//
//						fnDecode6BitBuf(pszItem, (char*)&stReceivedItem, sizeof(CLIENTITEMRCD));
//						xItem.SetItem(stReceivedItem, 0);
//
//						m_xInterface.m_xInventoryWnd.AddInvenItem(xItem, 0, FALSE);
//
//						pszItem = pszNextItem + 1;
//
//						nCount++;
//					}
//				} while (nCount < tdm.wSeries && pszNextItem);
				//TODO¸Ä±ä´æ´¢·½Ê½,ÓëMyHero¹Ò¹³,ÇÐ»»Ê±ºòÔÙ¿½±´µ½m_xInterface.m_xInventoryWnd
				break;
			}
			case SM_SENDUSEITEMS:
			{
//				CLIENTITEMRCD cItemRcd[9];
//
//				char *pszUseIndex = (pszMsg + DEFBLOCKSIZE);
//				char *pszItem;
//				char *pszNextItem;
//
//				ZeroMemory(cItemRcd, 9*sizeof(CLIENTITEMRCD));
//
//				for (int i = 0; i < 9; i++)
//				{
//					if (pszItem = strchr(pszUseIndex, '/'))
//					{
//						*pszItem = '\0';
//						pszItem++;
//						
//						if (pszNextItem = strchr(pszItem, '/'))
//						{
//							*pszNextItem = '\0';
//
//							fnDecode6BitBuf(pszItem, (char*)&cItemRcd[i], sizeof(CLIENTITEMRCD));	
//							
//							CItem xItem;
//							xItem.SetItem(cItemRcd[i], 0);
//
//							m_xInterface.m_xStatusWnd.m_stEquipItem[atoi(pszUseIndex)].xItem = xItem;
//							m_xInterface.m_xStatusWnd.m_stEquipItem[atoi(pszUseIndex)].bSetted = TRUE;
//
//							pszUseIndex = pszNextItem + 1;
//						}
//						else
//							break;
//					}
//					else
//						break;
//				}

				//TODO
				break;
			}
			case SM_ADDITEM:
			{											
//				CLIENTITEMRCD	stReceivedItem;
//
//				char *pszItem = (pszMsg + DEFBLOCKSIZE);
//
//				fnDecode6BitBuf(pszItem, (char*)&stReceivedItem, sizeof(CLIENTITEMRCD));
//				CItem xItem;
//				xItem.SetItem(stReceivedItem, 0);
//				m_xInterface.m_xInventoryWnd.AddInvenItem(xItem, 0, FALSE);
//
//				CHAR szSysMsg[MAX_PATH];
//				sprintf(szSysMsg, "%s ±»·¢ÏÖ", xItem.m_stItemInfo.stStdItem.szName);
//				m_xInterface.m_xClientSysMsg.AddSysMsg(szSysMsg);
				//TODO
				break;
			}
			case SM_DELITEM:
			{											
//				CLIENTITEMRCD	stReceivedItem;
//
//				char *pszItem = (pszMsg + DEFBLOCKSIZE);
//
//				fnDecode6BitBuf(pszItem, (char*)&stReceivedItem, sizeof(CLIENTITEMRCD));
//
//				m_xInterface.m_xInventoryWnd.DeleteInvenItem(stReceivedItem.nMakeIndex, stReceivedItem.stStdItem.szName);
//				m_xInterface.m_xStatusWnd.DeleteEquipItem(stReceivedItem.nMakeIndex, stReceivedItem.stStdItem.szName);
//
//				CHAR szSysMsg[MAX_PATH];
//				sprintf(szSysMsg, "%s ¶ªÊ§", stReceivedItem.stStdItem.szName);
//				m_xInterface.m_xClientSysMsg.AddSysMsg(szSysMsg);
				//TODO
				break;
			}
			case SM_DELITEMS:
			{		
//				CHAR szSysMsg[MAX_PATH];
//
//				char szItemName[64];
//				char szItemIndex[32];
//				char nItemIndex;
//
//				char *pszItem  = (pszMsg + DEFBLOCKSIZE);
//				char *pszItemIndex;
//				int  nCount = 0;
//
//				do
//				{
//					if (pszItemIndex = strchr(pszItem, '/'))
//					{
//						*pszItemIndex++ = '\0';
//
//						nPos = fnDecode6BitBuf(pszItem, (char*)&szItemName, sizeof(szItemName));
//						szItemName[nPos] = '\0';
//
//						if (pszItem = strchr(pszItemIndex, '/'))
//						{
//							*pszItem++ = '\0';
//
//							fnDecode6BitBuf(pszItem, (char*)&szItemIndex, sizeof(szItemIndex));
//							szItemIndex[nPos] = '\0';
//
//							nItemIndex = atoi(szItemIndex);
//
//							m_xInterface.m_xInventoryWnd.DeleteInvenItem(nItemIndex, szItemName);
//							m_xInterface.m_xStatusWnd.DeleteEquipItem(nItemIndex, szItemName);
//
//							sprintf(szSysMsg, "%s ¶ªÊ§", szItemName);
//							m_xInterface.m_xClientSysMsg.AddSysMsg(szSysMsg);
//
//							nCount++;
//						}
//					}
//				} while (nCount < tdm.wSeries && pszItem);

				//TODO
				break;
			}
			case SM_EAT_OK:
			{
//				CHAR szMsg[32];
//				sprintf( szMsg, "Ê¹ÓÃ %s", m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName );
//				m_xInterface.m_xClientSysMsg.AddSysMsg( szMsg );
//
//				m_xInterface.m_xInventoryWnd.AddNewBeltItem(&m_xInterface.m_stCommonItem);
//				//½«Ê£ÏÂÒ©Æ¬·Å»ØÈ¥
//				if( (m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.bStdMode == 0 || m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.bStdMode == 3)  )
//				{
//					m_xInterface.m_stCommonItem.xItem.m_stItemInfo.bDrugNum--;
//					if( m_xInterface.m_stCommonItem.xItem.m_stItemInfo.bDrugNum > 0 )
//						m_xInterface.m_xInventoryWnd.SetInvenFromCommon(m_xInterface.m_stCommonItem.xItem.m_shCellNum, &m_xInterface.m_stCommonItem);
//				}
//				ZeroMemory(&m_xInterface.m_stCommonItem, sizeof(COMMONITEMSET));//Çå³ýµ±Ç°Ñ¡Ôñ
				//TODO
				break;
			}
			case SM_EAT_FAIL:
			{
//				if ( m_xInterface.m_stCommonItem.bSetted )
//				{
//					if ( !m_xInterface.m_stCommonItem.bIsBeltItem )
//						m_xInterface.m_xInventoryWnd.AddInvenItem(m_xInterface.m_stCommonItem.xItem, m_xInterface.m_stCommonItem.xItem.m_shCellNum, TRUE);
//					else
//						m_xInterface.m_xInventoryWnd.AddBeltItem(m_xInterface.m_stCommonItem.xItem, m_xInterface.m_stCommonItem.xItem.m_shCellNum, TRUE);
//				}
//				ZeroMemory(&m_xInterface.m_stCommonItem, sizeof(COMMONITEMSET));
				//TODO
				break;
			}
			case SM_ADDMAGIC:
			{
//				m_xInterface.m_xStatusWnd.m_bMyMagicCnt++;
//				CLIENTMAGICRCD* pstMagicRCD;
//				pstMagicRCD = new CLIENTMAGICRCD[m_xInterface.m_xStatusWnd.m_bMyMagicCnt];
//
//				memcpy(pstMagicRCD, m_xInterface.m_xStatusWnd.m_pstMyMagic, sizeof(CLIENTMAGICRCD)*(m_xInterface.m_xStatusWnd.m_bMyMagicCnt-1));
//
//				fnDecode6BitBuf(&pszMsg[_DEFBLOCKSIZE], (char*)&pstMagicRCD[m_xInterface.m_xStatusWnd.m_bMyMagicCnt-1], sizeof(CLIENTMAGICRCD));
//
//				SAFE_DELETE(m_xInterface.m_xStatusWnd.m_pstMyMagic);
//
//				m_xInterface.m_xStatusWnd.m_pstMyMagic = pstMagicRCD;
				break;
			}
			case SM_TAKEON_OK:
			{
//				FEATURE stFeature;
//				memcpy(&stFeature, &tdm.nRecog, sizeof(LONG));
//				g_xGameProc.m_pMyHero->ChangeFeature(stFeature, g_xGameProc.m_pMyHero->m_stFeatureEx);
//
//				// ÀåÂøÃ¢ÀÇ Âø¿ë¾ÆÀÌÅÛ(m_stTakeOnItemSet)À» ÀåÂøÃ¢ÀÇ ¸Â´Â¼¿¿¡ Àû¿ë½ÃÅ°°í, Âø¿ë¾ÆÀÌÅÛ(m_stTakeOnItemSet)À» Áö¿î´Ù.
//				m_xInterface.m_xStatusWnd.SetEquipFromTakeOn();
//				// ¸¸¾à °øÅë(¸¶¿ì½º)¾ÆÀÌÅÛÀÌ ÀÖ´Ù¸é ÀÎº¥Åä¸®À©µµ¿ìÀÇ ºó¼¿¿¡ ³Ö°í, °øÅë(¸¶¿ì½º)¾ÆÀÌÅÛÀ» Áö¿î´Ù.
//				if ( m_xInterface.m_stCommonItem.bSetted )
//				{
////					m_xInterface.m_xInventoryWnd.AddInvenItem(m_xInterface.m_stCommonItem.xItem, 0, FALSE);
//					ZeroMemory(&m_xInterface.m_stCommonItem, sizeof(ITEMSET));
//				}
				break;
			}
			case SM_TAKEON_FAIL:
			{
				// ÀåÂøÃ¢ÀÇ Âø¿ë¾ÆÀÌÅÛ(m_stTakeOnItemSet)À» ´Ù½Ã ÀÎº¥Åä¸®¿¡ ³Ö´Â´Ù.
				// ¸¸¾à¿¡ °øÅë(¸¶¿ì½º)¾ÆÀÌÅÛÀÌ ÀÖ´Ù¸é ±×°É Âø¿ë¼¿¿¡ ³Ö´Â´Ù.
//				if ( m_xInterface.m_xStatusWnd.m_stTakeOnItemSet.bSetted )
//				{
//					m_xInterface.m_xInventoryWnd.AddInvenItem(m_xInterface.m_xStatusWnd.m_stTakeOnItemSet.xItem, 0, FALSE);
//					ZeroMemory(&m_xInterface.m_xStatusWnd.m_stTakeOnItemSet, sizeof(ITEMSET));
//				}
//				if ( m_xInterface.m_stCommonItem.bSetted )
//				{
//					m_xInterface.m_xStatusWnd.SetEquipFromCommon(m_xInterface.m_stCommonItem.xItem.m_shCellNum, &m_xInterface.m_stCommonItem);
//	//												ZeroMemory(&m_xInterface.m_stCommonItem, sizeof(ITEMSET));
//				}
				break;
			}
			case SM_TAKEOFF_OK:
			{
//				FEATURE stFeature;
//				memcpy(&stFeature, &tdm.nRecog, sizeof(LONG));
//				g_xGameProc.m_pMyHero->ChangeFeature(stFeature, g_xGameProc.m_pMyHero->m_stFeatureEx);
//
//				// ¹þÀ»·Á°í ÇÑ¾ÆÀÌÅÛÀ» ÀÎº¥Åä¸®¿¡ ³Ö´Â´Ù.
//				if ( m_xInterface.m_stCommonItem.bSetted )
//				{
////					m_xInterface.m_xInventoryWnd.AddInvenItem(m_xInterface.m_stCommonItem.xItem, 0, FALSE);
//					ZeroMemory(&m_xInterface.m_stCommonItem, sizeof(ITEMSET));
//				}
				break;
			}
			case SM_TAKEOFF_FAIL:
			{
//				// °øÅë(¸¶¿ì½º)¾ÆÀÌÅÛÀ» ´Ù½Ã Âø¿ë¼¿¿¡ ³Ö´Â´Ù.
//				if ( m_xInterface.m_stCommonItem.bSetted )
//				{
//					m_xInterface.m_xStatusWnd.SetEquipFromCommon(m_xInterface.m_stCommonItem.xItem.m_shCellNum, &m_xInterface.m_stCommonItem);
//	//												ZeroMemory(&m_xInterface.m_stCommonItem, sizeof(ITEMSET));
//				}
				break;
			}
			case SM_ITEMSHOW:
			{
				BOOL bExisted = FALSE;

				if ( m_stMapItemList.GetCounter() != 0 )
				{
					m_stMapItemList.MoveCurrentToTop();
					LPGROUNDITEM pstItem;

					for ( INT nCnt = 0; nCnt < m_stMapItemList.GetCounter(); nCnt++ )
					{
						pstItem = m_stMapItemList.GetCurrentData();

						if ( pstItem->nRecog == tdm.nRecog )
							bExisted = TRUE;

						m_stMapItemList.MoveNextNode();
					}
				}	

				if ( !bExisted )
				{
					LPGROUNDITEM pstItem = new GROUNDITEM;

					pstItem->nRecog  = tdm.nRecog;
					pstItem->shTileX = tdm.wParam;
					pstItem->shTileY = tdm.wTag;
					pstItem->wLooks  = tdm.wSeries;
					nPos = fnDecode6BitBuf((pszMsg + DEFBLOCKSIZE), (char*)pstItem->szItemName, sizeof(pstItem->szItemName));
					pstItem->szItemName[nPos] = '\0';

					m_stMapItemList.AddNode(pstItem);
				}											

				break;
			}
			case SM_ITEMHIDE:
			{
				LPGROUNDITEM pstItem;

				m_stMapItemList.MoveCurrentToTop();
				
				for ( INT nCnt = 0; nCnt < m_stMapItemList.GetCounter(); nCnt++ )
				{
					pstItem = m_stMapItemList.GetCurrentData();												
					
					if ( pstItem->nRecog == tdm.nRecog )
					{
						m_stMapItemList.DeleteCurrentNodeEx();
						SAFE_DELETE(pstItem);
						break;
					}
				
					m_stMapItemList.MoveNextNode();
				}	

				break;
			}
			case SM_SHOWEVENT:
			{
//				BOOL bExisted = FALSE;
//
//				_TSHORTMSSEAGE stShortMsg;
//				
//				fnDecode6BitBuf((pszMsg + DEFBLOCKSIZE), (char*)&stShortMsg, sizeof(_TSHORTMSSEAGE));
//
//				if ( m_xGroundMagicList.GetCounter() != 0 )
//				{
//					m_xGroundMagicList.MoveCurrentToTop();
//					CMagic* pxMagic;
//
//					for ( INT nCnt = 0; nCnt < m_xGroundMagicList.GetCounter(); nCnt++ )
//					{
//						pxMagic = m_xGroundMagicList.GetCurrentData();
//
//						switch ( pxMagic->m_bMagicNum )
//						{
//							case _SKILL_EARTHFIRE: 
//							case _SKILL_HOLYSHIELD:
//							{
//								CRepeatMagic* pxRepeatMagic = (CRepeatMagic*)pxMagic;
//								if ( pxRepeatMagic->m_nEventID == tdm.nRecog )
//									bExisted = TRUE;
//
//								break;
//							}
//						}
//
//						m_xGroundMagicList.MoveNextNode();
//					}
//				}	
//
//				// »ý¼ºÇÑ´Ù.
//				if ( !bExisted )
//				{
//					BYTE bEffectNum = 0;
//
//					if ( tdm.wParam == _ET_FIRE )
//					{
//						bEffectNum = _SKILL_EARTHFIRE;
//						CRepeatMagic* pxRepeatMagic;
//						pxRepeatMagic = new CRepeatMagic;
//						pxRepeatMagic->CreateMagic(tdm.nRecog, bEffectNum, 0, 0, tdm.wTag, tdm.wSeries, 0XFFFFFFFF, NULL, NULL);
//
//						pxRepeatMagic->m_dwCurrFrame += GetRandomNum(1, 8);
//
//						g_xGameProc.m_xGroundMagicList.AddNode(pxRepeatMagic);
//
//					}
//					else if ( tdm.wParam == _ET_HOLYCURTAIN )
//					{
//						bEffectNum = _SKILL_HOLYSHIELD;
//						CRepeatMagic* pxRepeatMagic;
//						pxRepeatMagic = new CRepeatMagic;
//						pxRepeatMagic->CreateMagic(tdm.nRecog, bEffectNum, 0, 0, tdm.wTag, tdm.wSeries, 0XFFFFFFFF, NULL, NULL);
//
//						pxRepeatMagic->m_dwCurrFrame += GetRandomNum(1, 8);
//
//						g_xGameProc.m_xGroundMagicList.AddNode(pxRepeatMagic);
//					}
//				}							
				break;
			}
			case SM_HIDEEVENT:
			{
				if ( m_xGroundMagicList.GetCounter() != 0 )
				{
					m_xGroundMagicList.MoveCurrentToTop();
					CMagic* pxMagic;

					for ( INT nCnt = 0; nCnt < m_xGroundMagicList.GetCounter(); nCnt++ )
					{
						pxMagic = m_xGroundMagicList.GetCurrentData();
						CRepeatMagic* pxRepeatMagic = NULL;

						switch ( pxMagic->m_bMagicNum )
						{
							case _SKILL_EARTHFIRE: 
							case _SKILL_HOLYSHIELD:
							{
								pxRepeatMagic = (CRepeatMagic*)pxMagic;
								break;
							}
						}
						if ( pxRepeatMagic && pxRepeatMagic->m_nEventID == tdm.nRecog )
						{
							pxRepeatMagic->m_dwMagiLifeTotal = 0;
							break;
						}

						m_xGroundMagicList.MoveNextNode();
					}
				}	
				break;
			}
			case SM_LEVELUP:
			{
				m_pMyHero->m_stAbility.dwExp = tdm.nRecog;
				m_pMyHero->m_stAbility.bLevel = tdm.wParam;

				g_xGameProc.m_xInterface.m_xClientSysMsg.AddSysMsg("·¹º§ÀÌ ¿Ã¶ú½À´Ï´Ù");
				break;
			}
			case SM_DAYCHANGING:
			{
				break;
			}
			case SM_AREASTATE:
			{
				break;
			}
			case SM_HEAR:
			case SM_SYSMESSAGE:
			case SM_GUILDMESSAGE:
			case SM_CRY:
			case SM_WHISPER:
			case SM_GROUPMESSAGE:
			case SM_MONSTERSAY:
		//		OnSvrMsgHear(&tdm, (pszMsg + DEFBLOCKSIZE));
				//¹Ø±ÕÁÄÌìÏûÏ¢
				break;
			case SM_DISAPPEAR:
			case SM_CLEAROBJECT:
			{
				_TDEFAULTMESSAGE*	lpstDefMsg;
				lpstDefMsg	= new _TDEFAULTMESSAGE;

				memcpy(lpstDefMsg, &tdm, sizeof(_TDEFAULTMESSAGE));
				
				m_xWaitDefaultPacketQueue.PushQ((BYTE*)lpstDefMsg);
				break;
			}
			case SM_MERCHANTSAY:		// gadget ÉÌÈËËµ»°?
			{	
//				int		nPos;
//				char	szDecodeMsg[8192];
//				char	*pszSay;
//
//				m_xInterface.m_xNPCWnd.ResetDialog();
//
//				m_wNPCWndPosX = m_pMyHero->m_wPosX;
//				m_wNPCWndPosY = m_pMyHero->m_wPosY;
//
////				if (tdm.nRecog != m_xInterface.m_xNPCWnd.m_nNpcId)
////				{
////				}
//				
//				nPos = fnDecode6BitBuf((pszMsg + DEFBLOCKSIZE), szDecodeMsg, sizeof(szDecodeMsg));
//				szDecodeMsg[nPos] = '\0';
//
//				if (pszSay = strchr(szDecodeMsg, '/'))
//				{
//					*pszSay++ = '\0';
//
//					if (pszSay)
//						DevideScript(pszSay);
//				}
//
//				if(!m_xInterface.m_xNPCWnd.GetGameWndActive())
//				{
//					m_xInterface.WindowActivate(_WND_ID_NPCCHAT);
//					m_xInterface.m_xNPCWnd.SetNPC(tdm.nRecog);//ÉèÖÃID
//				}
				
				break;
			}
			case SM_MERCHANTDLGCLOSE:
			{
//				CloseNPCWindow();
				break;
			}
			case SM_SENDGOODSLIST:
			case SM_SENDDETAILGOODSLIST:
			case SM_BUYITEM_SUCCESS:
			case SM_BUYITEM_FAIL:
			
			{	// »óÁ¡Ã¢ Ã³¸® ·çÆ¾
//				LPPACKETMSG	lpPacketMsg	= new PACKETMSG;
//				lpPacketMsg->stDefMsg	= tdm;
//				lstrcpy(lpPacketMsg->szEncodeData, (pszMsg + DEFBLOCKSIZE));
//				m_xInterface.m_xStoreWnd.m_xPacketQueue.PushQ((BYTE*)lpPacketMsg);	// PacketÀ» Queue¿¡ ³Ö´Â´Ù.
//				if(!m_xInterface.m_xStoreWnd.GetGameWndActive())
//				{
//					m_xInterface.WindowActivate(_WND_ID_STORE);
//					m_xInterface.m_xStoreWnd.SetNPC(tdm.nRecog);
//				}
				//TODO
				break;
			}
			case SM_DROPITEM_SCCESS: 
			{
//				CHAR	pszItemName[15];
//				if (m_xInterface.m_stCommonItem.bWaitResponse )
//				{
//					if ( m_xInterface.m_stCommonItem.bSetted && m_xInterface.m_stCommonItem.xItem.m_stItemInfo.nMakeIndex == tdm.nRecog )
//					{
//						nPos = fnDecode6BitBuf((pszMsg + DEFBLOCKSIZE), (char*)pszItemName, sizeof(pszItemName));
//						pszItemName[nPos] = '\0';
//
//						if ( !strcmp(pszItemName, m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName) )
//						{
//							ZeroMemory(&m_xInterface.m_stCommonItem, sizeof(COMMONITEMSET));
//						}
//					}
//					m_xInterface.m_stCommonItem.bWaitResponse = FALSE;
//				}
				//TODO
				break;
			}
			case SM_DROPITEM_FAIL:
			{
				// °¡¹æ¿¡ ´Ù½Ã ³Ö¾î¹ö¸°´Ù.
//				CHAR	pszItemName[15];
//				if (m_xInterface.m_stCommonItem.bWaitResponse )
//				{
//					if ( m_xInterface.m_stCommonItem.bSetted && m_xInterface.m_stCommonItem.xItem.m_stItemInfo.nMakeIndex == tdm.nRecog )
//					{
//						nPos = fnDecode6BitBuf((pszMsg + DEFBLOCKSIZE), (char*)pszItemName, sizeof(pszItemName));
//						pszItemName[nPos] = '\0';
//
//						if ( !strcmp(pszItemName, m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName) )
//						{
//							if ( !m_xInterface.m_stCommonItem.bIsBeltItem )
//								m_xInterface.m_xInventoryWnd.AddInvenItem(m_xInterface.m_stCommonItem.xItem, m_xInterface.m_stCommonItem.xItem.m_shCellNum, TRUE);
//							else
//								m_xInterface.m_xInventoryWnd.AddBeltItem(m_xInterface.m_stCommonItem.xItem, m_xInterface.m_stCommonItem.xItem.m_shCellNum, TRUE);
//							ZeroMemory(&m_xInterface.m_stCommonItem, sizeof(COMMONITEMSET));
//						}
//					}
//					m_xInterface.m_stCommonItem.bWaitResponse = FALSE;
//				}
				//TODO
				break;
			}
			case SM_DURACHANGE:
			{
//				if ( m_xInterface.m_xStatusWnd.m_stEquipItem[tdm.wParam].bSetted )
//				{
//					m_xInterface.m_xStatusWnd.m_stEquipItem[tdm.wParam].xItem.m_stItemInfo.nDura = tdm.nRecog;
//					m_xInterface.m_xStatusWnd.m_stEquipItem[tdm.wParam].xItem.m_stItemInfo.nDuraMax = MAKELONG(tdm.wTag, tdm.wSeries);
//				}
				break;
			}
			case SM_GOLDCHANGE:
			{
				m_pMyHero->m_nGlod = tdm.nRecog;
				break;
			}
			case SM_WEIGHTCHANGED:
			{
				m_pMyHero->m_stAbility.wWeight	  = tdm.nRecog;
				m_pMyHero->m_stAbility.bWearWeight = tdm.wParam;
				m_pMyHero->m_stAbility.bHandWeight = tdm.wTag;											
				break;
			}
			case SM_RIDEHORSE:
			{
				m_pMyHero->m_stFeatureEx.bHorse = tdm.nRecog;
				m_pMyHero->ChangeFeature(m_pMyHero->m_stFeature, m_pMyHero->m_stFeatureEx);

//				if ( m_pMyHero->m_stFeatureEx.bHorse != _HORSE_NONE )
//					m_pMyHero->SetMotionFrame(_MT_HORSESTAND, m_pMyHero->m_bCurrDir);
//				else
//					m_pMyHero->SetMotionFrame(_MT_STAND, m_pMyHero->m_bCurrDir);

				break;
			}
			case SM_OPENDOOR_OK:
			{
				INT nIdx = m_xMap.GetDoor(tdm.wParam, tdm.wTag);
				if ( nIdx )
				{
					m_xMap.OpenDoor(tdm.wParam, tdm.wTag, nIdx);
				}
				break;
			}
			case SM_OPENDOOR_LOCK:
			{
//				m_xInterface.m_xClientSysMsg.AddSysMsg("ÃÅ¹Ø±Õ");
				break;
			}
			case SM_CLOSEDOOR:
			{
				INT nIdx = m_xMap.GetDoor(tdm.wParam, tdm.wTag);
				if ( nIdx )
				{
					m_xMap.CloseDoor(tdm.wParam, tdm.wTag, nIdx);
				}
				break;
			}
			case SM_HEALTHSPELLCHANGED: // gadget
			{
				if ( tdm.nRecog == m_pMyHero->m_dwIdentity )
				{
					m_pMyHero->m_wHP			= tdm.wParam;
					m_pMyHero->m_wMP			= tdm.wTag;
					m_pMyHero->m_wMAXHP		= tdm.wSeries;
					FLOAT wHPRate			= (FLOAT)((FLOAT)m_pMyHero->m_wHP/(FLOAT)m_pMyHero->m_wMAXHP);
					m_pMyHero->m_bHPPercent  = wHPRate * 100;
				}
				else
				{
					CActor* pxActor = FindActor(tdm.nRecog);

					if (pxActor)
					{
						pxActor->m_wHP			= tdm.wParam;
						pxActor->m_wMP			= tdm.wTag;
						pxActor->m_wMAXHP		= tdm.wSeries;
						FLOAT wHPRate			= (FLOAT)((FLOAT)pxActor->m_wHP/(FLOAT)pxActor->m_wMAXHP);
						pxActor->m_bHPPercent	= wHPRate * 100;
					}
				}

				break;
			}
			case SM_CREATEGROUP_OK:
			{
//            changegroupmodetime := GetTickCount;
//            AllowGroup := TRUE;
				break;
			}
			case SM_CREATEGROUP_FAIL:
			{
//            changegroupmodetime := GetTickCount;
				switch (tdm.nRecog)
				{
					case -1: 
						//FrmDlg.DMessageDlg ('ÀÌ¹Ì ±×·ì¿¡ °¡ÀÔµÇ¾î ÀÖ½À´Ï´Ù.', [mbOk]);
						break;
					case -2: 
						//FrmDlg.DMessageDlg ('±×·ì¿¡ Âü¿©ÇÒ ÀÌ¸§ÀÌ ¹Ù¸£Áö ¾Ê½À´Ï´Ù.', [mbOk]);
						break;
					case -3: 
						//FrmDlg.DMessageDlg ('ÇÔ²² Âü¿©ÇÏ·Á´Â »ç¶÷ÀÌ ´Ù¸¥ ±×·ì¿¡ Âü¿©ÁßÀÔ´Ï´Ù.', [mbOk]);
						break;
					case -4: 
						//FrmDlg.DMessageDlg ('»ó´ë¹æÀÌ ±×·ì°ÅºÎÁßÀÔ´Ï´Ù.', [mbOk]);
						break;
				}
			}
			case SM_GROUPMEMBERS:
			{
//				char	szDecodeMsg[8192];
//				char	*pszMembers, *pszNext;
//
//				m_xInterface.m_xGroupWnd.m_xGroupList.ClearAllNodes();
//
//				nPos = fnDecode6BitBuf((pszMsg + DEFBLOCKSIZE), szDecodeMsg, sizeof(szDecodeMsg));
//				szDecodeMsg[nPos] = '\0';
//
//				pszMembers = szDecodeMsg;
//
//				while (pszNext = strchr(pszMembers, '/'))
//				{
//					*pszNext++ = '\0';
//
//					CGroupMember* pGroupMember = new CGroupMember;
//
//					if (pGroupMember)
//					{
//						strcpy(pGroupMember->szMemberName, pszMembers);
//						m_xInterface.m_xGroupWnd.m_xGroupList.AddNode(pGroupMember);
//					}
//
//					pszMembers = pszNext;
//				}
				//TODO

				break;
			}
			case SM_GROUPCANCEL:
			{
//				m_xInterface.m_xGroupWnd.m_xGroupList.ClearAllNodes();

				break;
			}
			case SM_BUILDGUILD_OK:
			{
//         begin
//            FrmDlg.LastestClickTime := GetTickCount;
//          FrmDlg.DMessageDlg ('¹®ÆÄ°¡ ¸¸µé¾î Á³½À´Ï´Ù.', [mbOk]);
//         end;
				break;
			}
			case SM_BUILDGUILD_FAIL:
			{
//         begin
//            FrmDlg.LastestClickTime := GetTickCount;
//            case msg.Recog of
//               -1: FrmDlg.DMessageDlg ('ÀÌ¹Ì ¹®ÆÄ¿¡ °¡ÀÔÇØ ÀÖ½À´Ï´Ù.', [mbOk]);
//               -2: FrmDlg.DMessageDlg ('µî·Ïºñ¿ëÀÌ ºÎÁ·ÇÕ´Ï´Ù.', [mbOk]);
//               -3: FrmDlg.DMessageDlg ('ÇÊ¿ä¾ÆÀÌÅÛÀ» ¸ðµÎ °¡Áö°í ÀÖÁö ¾Ê½À´Ï´Ù.', [mbOk]);
//            end;
//         end;
				break;
			}
			case SM_OPENGUILDDLG:
			{
//				char szDecodeMsg[8192];
//
//				INT nPos = fnDecode6BitBuf((pszMsg + DEFBLOCKSIZE), szDecodeMsg, sizeof(szDecodeMsg));
//				szDecodeMsg[nPos] = '\0';
//
//				m_xInterface.WindowActivate(_WND_ID_GUILDMASTER);	

				//TODO
				break;
			}
			case SM_USERNAME:
			{
				char szDecodeMsg[1024];
				char *pszGuildName;

				INT nPos = fnDecode6BitBuf((pszMsg + DEFBLOCKSIZE), szDecodeMsg, sizeof(szDecodeMsg));
				szDecodeMsg[nPos] = '\0';

				if (pszGuildName = strchr(szDecodeMsg, '\\'))
					*pszGuildName++ = '\0';

				if ( tdm.nRecog == m_pMyHero->m_dwIdentity )
				{				
					m_pMyHero->m_dwNameClr = GetUserNameColor(tdm.wParam);

					strcpy(m_pMyHero->m_szName, szDecodeMsg);

					if (pszGuildName)
						strcpy(m_pMyHero->m_szGuildName, pszGuildName);
				}
				else
				{
					CActor* pxActor = FindActor(tdm.nRecog);

					if (pxActor)
					{
						pxActor->m_dwNameClr = GetUserNameColor(tdm.wParam);

						strcpy(pxActor->m_szName, szDecodeMsg);

						if (pszGuildName)
							strcpy(pxActor->m_szGuildName, pszGuildName);

					}
				}

				break;
			}
			case SM_CHANGEGUILDNAME:
			{
				char szDecodeMsg[1024];
				char *pszGuildPos;

				INT nPos = fnDecode6BitBuf((pszMsg + DEFBLOCKSIZE), szDecodeMsg, sizeof(szDecodeMsg));
				szDecodeMsg[nPos] = '\0';

				if (pszGuildPos = strchr(szDecodeMsg, '/'))
				{
					*pszGuildPos = ' ';

					strcpy(m_pMyHero->m_szGuildName, szDecodeMsg);
				}

				break;
			}
			case SM_INVENTITEM:
			{
//				m_xInterface.m_xInventoryWnd.SetInventItemNum(tdm.nRecog, tdm.wParam);
				break;
			}
			case SM_639:
			case SM_709:
			case SM_801:
			case SM_803:
			case SM_807:
			case SM_1104:
			case SM_1318:
			case SM_1323:
			case SM_1401:
			{
				//for debug Êä³öÎ´´¦ÀíµÄMsg
				OutputDebugString("Å×Æú´¦ÀíµÄÏûÏ¢°ü");
				OutputDebugString( sztxt);
				break;
			}
			default:
			{
				//for debug Êä³öÎ´´¦ÀíµÄMsg
				if( tdm.wIdent > 658 )
				{
					OutputDebugString("Î´ÖªÏûÏ¢°ü, TeamProc");
					OutputDebugString( sztxt);
				}

				LPPACKETMSG	lpPacketMsg	= new PACKETMSG;

				lpPacketMsg->stDefMsg			= tdm;
				lpPacketMsg->szEncodeData[0]	= NULL;

				if ( tdm.wIdent != SM_HIT && tdm.wIdent != SM_BACKSTEP && tdm.wIdent != SM_RUSH )
 					lstrcpy(lpPacketMsg->szEncodeData, (pszMsg + DEFBLOCKSIZE));

 				m_xWaitPacketQueue.PushQ((BYTE*)lpPacketMsg);

				break;
			}
		}
	}
}

//´¦ÀíÏûÊ§ÊÂ¼þ	
//case SM_DISAPPEAR:
//case SM_CLEAROBJECT:
VOID CTeamProcess::ProcessDefaultPacket()
{
	_TDEFAULTMESSAGE*	lpstDefMsg;

	for (int i = 0; i < m_xWaitDefaultPacketQueue.GetCount(); i++)
	{
		lpstDefMsg = (_TDEFAULTMESSAGE*)m_xWaitDefaultPacketQueue.PopQ();

		if ( lpstDefMsg )
		{
			if ( lpstDefMsg->wIdent == SM_DISAPPEAR )
			{
				CActor* pxActor = NULL;

				m_xActorList.MoveCurrentToTop();
				for ( INT nCnt = 0; nCnt < m_xActorList.GetCounter(); nCnt++ )
				{
					pxActor = m_xActorList.GetCurrentData();
					
					if ( pxActor->m_dwIdentity == lpstDefMsg->nRecog )
					{
						INT nPacketCnt = pxActor->m_xPacketQueue.GetCount();
						for ( INT nLoopCnt = 0; nLoopCnt < nPacketCnt; nLoopCnt++ )
						{
							LPPACKETMSG	lpObjPacketMsg = (LPPACKETMSG)pxActor->m_xPacketQueue.PopQ();
							SAFE_DELETE(lpObjPacketMsg);
						}

						switch ( pxActor->m_stFeature.bGender )
						{
						case _GENDER_MAN:
						case _GENDER_WOMAN:
							{
								m_xActorList.DeleteCurrentNodeEx();

								CHero* pxHero = (CHero*)pxActor;
								delete pxHero;
								pxHero = NULL;
							}
							break;
						case _GENDER_NPC:
							{
								m_xActorList.DeleteCurrentNodeEx();
								CNPC* pxNPC = (CNPC*)pxActor;
								delete((CNPC*)pxNPC);
								pxNPC = NULL;
							}
							break;
						case _GENDER_MON:
							{
								m_xActorList.DeleteCurrentNodeEx();
								delete(pxActor);
								pxActor = NULL;
							}
							break;
						}		

						break;		//Èç¹ûÕÒµ½Ôòbreak£¬Ö»É¾³ýÒ»¸ö
					}	

					m_xActorList.MoveNextNode();
				}//for
			}
			//È«É¾
			else if ( lpstDefMsg->wIdent == SM_CLEAROBJECT )
			{
				CActor* pxActor = NULL;

				m_xActorList.MoveCurrentToTop();
				for ( INT nCnt = 0; nCnt < m_xActorList.GetCounter(); )
				{
					pxActor = m_xActorList.GetCurrentData();
					
					INT nPacketCnt = pxActor->m_xPacketQueue.GetCount();
					for ( INT nLoopCnt = 0; nLoopCnt < nPacketCnt; nLoopCnt++ )
					{
						LPPACKETMSG	lpObjPacketMsg = (LPPACKETMSG)pxActor->m_xPacketQueue.PopQ();
						SAFE_DELETE(lpObjPacketMsg);
					}

					switch ( pxActor->m_stFeature.bGender )
					{
					case _GENDER_MAN:
					case _GENDER_WOMAN:
						{
							m_xActorList.DeleteCurrentNodeEx();
							CHero* pxHero = (CHero*)pxActor;
							delete((CHero*)pxHero);
							pxHero = NULL;
						}
						break;
					case _GENDER_NPC:
						{
							m_xActorList.DeleteCurrentNodeEx();
							CNPC* pxNPC = (CNPC*)pxActor;
							delete((CNPC*)pxNPC);
							pxNPC = NULL;
						}
						break;
					case _GENDER_MON:
						{
							m_xActorList.DeleteCurrentNodeEx();
							delete(pxActor);
							pxActor = NULL;
						}
						break;
					}

				}					
			}
		}
		SAFE_DELETE(lpstDefMsg);
	}						
}

//³öÀ´ÈË/¹Ö¶¯×÷ÊÂ¼þ
VOID CTeamProcess::ProcessPacket()
{
//	LPPACKETMSG	lpPacketMsg;

//	for (int i = 0; i < m_xWaitPacketQueue.GetCount(); i++)
//	{
//		BOOL bExist = FALSE;
//		CActor* pxActor = NULL;
//
//		lpPacketMsg = (LPPACKETMSG)m_xWaitPacketQueue.PopQ();
//
//		if ( lpPacketMsg )
//		{
//			if ( lpPacketMsg->stDefMsg.nRecog == m_pMyHero->m_dwIdentity )
//			{
//				if ( lpPacketMsg->stDefMsg.wIdent == SM_NOWDEATH || lpPacketMsg->stDefMsg.wIdent == SM_DEATH )
//				{
//					m_pMyHero->m_xPriorPacketQueue.PushQ((BYTE*)lpPacketMsg);
//				}
//				else if ( lpPacketMsg->stDefMsg.wIdent == SM_CHANGEMAP )//»»µØÍ¼
//				{
////					m_pMyHero->SetMotionFrame(_MT_STAND, m_pMyHero->m_bCurrDir);
////					ZeroMemory(m_stMemMappedID, sizeof(MEMMAPPEDID)*_VIEW_CELL_X_COUNT* _VIEW_CELL_Y_COUNT);
////					OnSvrMsgNewMap( &lpPacketMsg->stDefMsg, lpPacketMsg->szEncodeData );
////
////					// gadget			
////					m_wInputDelayTime = 2300;
////					m_wCurrInputDelayTime = 0;
////					m_pMyHero->m_wABlendCurrDelay = 0;
////					m_pMyHero->m_wABlendDelay = 2300;
//
////					CloseNPCWindow();
//				}
//				else
//				{
//					if ( lpPacketMsg->stDefMsg.wIdent == SM_STRUCK )//±»¹¥»÷?
//					{
////						m_pMyHero->StruckMsgReassign();
//
//						if ( timeGetTime() - m_pMyHero->m_dwLastStruckTime < 500 )
//						{
//							SAFE_DELETE(lpPacketMsg);
//							continue;
//						}
//
//						MESSAGEBODYWL stMsgBodyWl;
//						fnDecode6BitBuf(lpPacketMsg->szEncodeData, (char*)&stMsgBodyWl, sizeof(MESSAGEBODYWL));
//
//						for ( INT nCnt = 0; nCnt < m_xActorList.GetCounter(); nCnt++ )
//						{
//							CActor* pxGaheja = m_xActorList.GetCurrentData();
//
//							if ( pxGaheja->m_dwIdentity == stMsgBodyWl.nTag1 )
//							{
//								m_pMyHero->m_stHitter = pxGaheja->m_stFeature;
//								break;
//							}
//
//							m_xActorList.MoveNextNode();
//						}						
//					}					
//					
//					m_pMyHero->StruckMsgReassign();
//					m_pMyHero->m_xPacketQueue.PushQ((BYTE*)lpPacketMsg);
//				}
//			}
//			else	//if ( lpPacketMsg->stDefMsg.nRecog == m_pMyHero->m_dwIdentity )
//			{
//				FEATURE		stFeature;
//				FEATUREEX	stFeatureEx;
//
// 				fnDecode6BitBuf(lpPacketMsg->szEncodeData, (char*)&stFeature, sizeof(FEATURE));
//				//ÕâºóÃæ»¹ÓÐÊý¾Ý,²Î¿¼CHero::OnWalk()
//
//				m_xActorList.MoveCurrentToTop();
//				
//				//²éÕÒMonster
//				for ( INT nCnt = 0; nCnt < m_xActorList.GetCounter(); nCnt++ )
//				{
//					pxActor = m_xActorList.GetCurrentData();
//			
//					if ( pxActor->m_dwIdentity == lpPacketMsg->stDefMsg.nRecog )
//					{
//						bExist = TRUE;
//						break;
//					}
//				
//					m_xActorList.MoveNextNode();
//				}
//
//				//Ìí¼Ómonster
//				if ( !bExist )
//				{
//					//FOR DEBUG 
//					CHAR szHeroBurn[128];
//					sprintf( szHeroBurn, "ÈËÎï/¹ÖÎï³öÏÖ:nRecog=%08x,wIdent=%04x(%d),wParam=%04x,wTag=%04x,wSeries=%04x\n",
//						lpPacketMsg->stDefMsg.nRecog, lpPacketMsg->stDefMsg.wIdent, lpPacketMsg->stDefMsg.wIdent, lpPacketMsg->stDefMsg.wParam, lpPacketMsg->stDefMsg.wTag, lpPacketMsg->stDefMsg.wSeries );
//					OutputDebugString( szHeroBurn );
//
//					if ( stFeature.bGender == _GENDER_MAN || stFeature.bGender == _GENDER_WOMAN ) 
//					{
//						fnDecode6BitBuf(&lpPacketMsg->szEncodeData[_FEATURESIZE*3], (char*)&stFeatureEx, sizeof(FEATUREEX));
//
//						pxActor = new CHero;
//						CHero* pxHero = (CHero*)pxActor;
//
//						pxHero->m_dwIdentity = lpPacketMsg->stDefMsg.nRecog;
//
//						if ( pxHero->Create(&m_xImage, _MT_STAND, _DIRECTION_LIST_1, lpPacketMsg->stDefMsg.wParam, lpPacketMsg->stDefMsg.wTag, &stFeature, &stFeatureEx) )
//						{
//							m_xActorList.AddNode(pxActor);
//							pxHero->m_wABlendCurrDelay = 0;
//							pxHero->m_wABlendDelay  = 1500;
//						}
//					}
//					else if ( stFeature.bGender == _GENDER_NPC )
//					{
//						pxActor = new CNPC;
//						CNPC* pxNPC = (CNPC*)pxActor;
//
//						pxNPC->m_dwIdentity = lpPacketMsg->stDefMsg.nRecog;
//
//						if ( pxNPC->Create(&m_xImage, &stFeature, _MT_STAND, _DIRECTION_LIST_1, lpPacketMsg->stDefMsg.wParam, lpPacketMsg->stDefMsg.wTag) )
//							m_xActorList.AddNode(pxActor);
//
//						pxNPC->m_wABlendCurrDelay = 0;
//						pxNPC->m_wABlendDelay	  = 0;
//					}
//					else
//					{
//						stFeature.bGender	= _GENDER_MON;
//
//						// Àû¿ë½ÃÄÑ¾ßÇÔ.
//
//						pxActor = new CActor;
//						pxActor->m_dwIdentity = lpPacketMsg->stDefMsg.nRecog;
//
//						if ( pxActor->Create(&m_xImage, &stFeature, _MT_STAND, _DIRECTION_LIST_1, lpPacketMsg->stDefMsg.wParam, lpPacketMsg->stDefMsg.wTag) )
//						{
//							m_xActorList.AddNode(pxActor);
//							pxActor->m_wABlendCurrDelay = 0;
//							pxActor->m_wABlendDelay		= 150;
//						}
//					}
//				}
//
//				if ( pxActor )				
//				{
//					if ( lpPacketMsg->stDefMsg.wIdent == SM_STRUCK )
//					{
//						MESSAGEBODYWL stMsgBodyWl;
//						fnDecode6BitBuf(lpPacketMsg->szEncodeData, (char*)&stMsgBodyWl, sizeof(MESSAGEBODYWL));
//
//						for ( INT nCnt = 0; nCnt < m_xActorList.GetCounter(); nCnt++ )
//						{
//							CActor* pxGaheja = m_xActorList.GetCurrentData();
//
//							if ( pxGaheja->m_dwIdentity == stMsgBodyWl.nTag1 )
//							{
//								pxActor->m_stHitter = pxGaheja->m_stFeature;
//								break;
//							}
//
//							m_xActorList.MoveNextNode();
//						}
//						
//					}
//
//					pxActor->StruckMsgReassign();
//					pxActor->m_xPacketQueue.PushQ((BYTE*)lpPacketMsg);
//				}
//				else							
//					SAFE_DELETE(lpPacketMsg);
//			}
//		}
//	}
}

// **************************************************************************************
//
//		 Packet Handling
//
// **************************************************************************************

VOID CTeamProcess::OnSvrMsgNewMap(_TDEFAULTMESSAGE	*ptdm, char *pszMapName)
{
//	char szMapName[32];

	m_pMyHero->m_wPosX = ptdm->wParam;
	m_pMyHero->m_wPosY = ptdm->wTag;

//	int nPos = fnDecode6BitBuf(pszMapName, (char*)szMapName, sizeof(szMapName));
//	szMapName[nPos] = '\0';
//
//	m_xMap.SetStartViewTile(m_pMyHero->m_wPosX - _GAPY_TILE_CHAR_MAP, m_pMyHero->m_wPosY - _GAPY_TILE_CHAR_MAP);
//	m_xMap.LoadMapData(szMapName); 

	char	szMsg[64];
	sprintf( szMsg, "%s : ÎÒÔÚÕâ¶ù %d,%d \n", m_szCharName, m_pMyHero->m_wPosX, m_pMyHero->m_wPosY);
	OutputDebugString( szMsg );
	g_xGameProc.m_xInterface.MsgAdd( _CLR_RED, _CLR_BLACK, szMsg);

	m_bRender = TRUE;
}

VOID CTeamProcess::OnSvrMsgLogon(_TDEFAULTMESSAGE	*ptdm, char *pszMsg)
{
	MESSAGEBODYWL wl;
	FEATUREEX stFeatureEx;

	m_pMyHero->m_dwIdentity	= ptdm->nRecog;
	m_pMyHero->m_bLightSize	= HIBYTE(ptdm->wSeries);

	BYTE bDir = LOBYTE(ptdm->wSeries);

	if ( bDir > 8 )
		bDir = 0;

	// Ãß°¡ÄÚµå
	fnDecode6BitBuf(pszMsg, (char*)&wl, sizeof(wl));
	
	fnDecode6BitBuf(&pszMsg[22], (char*)&stFeatureEx , sizeof(FEATUREEX));

	if ( stFeatureEx.bHorse == _HORSE_NONE )
		m_pMyHero->Create(&m_xImage, _MT_STAND, bDir, ptdm->wParam/*x*/, ptdm->wTag/*y*/, (FEATURE *)&wl.lParam1, &stFeatureEx);
	else
		m_pMyHero->Create(&m_xImage, _MT_HORSESTAND, bDir, m_pMyHero->m_wPosX, m_pMyHero->m_wPosY, (FEATURE *)&wl.lParam1, &stFeatureEx);

	strcpy(g_xGameProc.m_pMyHero->m_szName, g_szCharName);
	
	//ÉèÖÃÖ÷½ÇµØÍ¼
	m_pMyHero->SetMapHandler(&m_xMap);

	CMagic* pxMagic;
	pxMagic = new CMagic;
	pxMagic->CreateMagic(_SKILL_SPACEMOVE2, m_pMyHero->m_wPosX, m_pMyHero->m_wPosY, m_pMyHero->m_wPosX, m_pMyHero->m_wPosY, NULL, m_pMyHero->m_dwIdentity);
	m_xMagicList.AddNode(pxMagic);	
	
	m_wInputDelayTime				= 2300;
	m_wCurrInputDelayTime			= 0;
	m_pMyHero->m_wABlendCurrDelay	= 0;
	m_pMyHero->m_wABlendDelay		= 2300;

	m_pSocket->SendQueryMsg(CM_QUERYBAGITEMS);
}

VOID CTeamProcess::OnSvrMsgHear(_TDEFAULTMESSAGE *ptdm, char *pszMsg)
{
	//ÏÈ²»×öÈÎºÎ´¦Àí
//	char szDecodeMsg[MAX_PATH];
//
//	int nPos = fnDecode6BitBuf(pszMsg, szDecodeMsg, sizeof(szDecodeMsg));
//	szDecodeMsg[nPos] = '\0';
//
//
//	DWORD dwBack = GetChatColor(ptdm->wParam);
//	DWORD dwFont = GetChatColor(ptdm->wTag);
//	m_xInterface.MsgAdd(dwFont, dwBack, szDecodeMsg);
//
//	if ( ptdm->wIdent == SM_HEAR || ptdm->wIdent == SM_MONSTERSAY )
//	{
//		if ( ptdm->nRecog == m_pMyHero->m_dwIdentity )
//		{
//			strncpy(m_pMyHero->m_szChatMsg, szDecodeMsg, MAX_PATH-1);
//			
//			m_pMyHero->ChatMsgAdd();
//			m_pMyHero->m_wCurrChatDelay = 0;
//		}
//		else
//		{
//			m_xActorList.MoveCurrentToTop();
//			
//			CActor* pxActor;
//			
//			if ( m_xActorList.GetCounter() != 0 )
//			{
//				for ( INT nCnt = 0; nCnt <= m_xActorList.GetCounter(); nCnt++ )
//				{ 
//					pxActor = m_xActorList.GetCurrentData();
//
//					if ( pxActor->m_dwIdentity == ptdm->nRecog )
//					{
//						strncpy(pxActor->m_szChatMsg, szDecodeMsg, MAX_PATH-1);
//
//						pxActor->ChatMsgAdd();
//						pxActor->m_wCurrChatDelay = 0;
//					}
//
//					m_xActorList.MoveNextNode();							
//				}
//			}
//		}
//	}
}

VOID CTeamProcess::ReadIniFileForTeam()
{
	CHAR	szFullPathFileName[MAX_PATH];

	GetCurrentDirectory(MAX_PATH, szFullPathFileName);
	strcat(szFullPathFileName, "\\");
	strcat(szFullPathFileName, MIR3_TEAM_INIFILE);

	// Get Server user , passwd , heroname
	GetPrivateProfileString( MIR3_TEAM_SECTION, MIR3_TEAM_USER,		"", m_szUser,	32, szFullPathFileName );
	GetPrivateProfileString( MIR3_TEAM_SECTION, MIR3_TEAM_PASSWD,	"", m_szPasswd, 32, szFullPathFileName );
	GetPrivateProfileString( MIR3_TEAM_SECTION, MIR3_TEAM_SERVER,	"", m_szServer, 32, szFullPathFileName );
	GetPrivateProfileString( MIR3_TEAM_SECTION, MIR3_TEAM_CHARNAME,	"", m_szCharName, 32, szFullPathFileName );

}

VOID CTeamProcess::OnConnectToServer()
{
	if( m_nProcState == _LOGIN_PROC )
	{
		m_pSocket->OnLogin( m_szUser, m_szPasswd );
	}
	else if( m_nProcState == _SVR_SEL_PROC )
	{
		//OnQueryChar()
		Sleep( 300 );
		m_pSocket->OnQueryChar( m_szUser, m_nCertifyCode );
	}
	else if( m_nProcState == _CHAR_SEL_PROC )
	{
		Sleep( 300 );
		m_pSocket->SendRunLogin( m_szUser, m_szCharName, m_nCertifyCode, g_nVersion );
		m_nProcState = _GAME_PROC;
	}

	char szTemp[64];
	sprintf( szTemp, "OnConnectToServer() %d", m_nProcState );
	OutputDebugString( szTemp );

}

LRESULT CTeamProcess::DefMainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if( !m_bLoad )	return 0;

	switch ( uMsg )
	{
	case WM_DESTROY:
		OnDestroy(wParam, lParam);
		break;
	case WM_TIMER:
		OnTimer(wParam, lParam);
		break;
//	case WM_KEYDOWN:
//		OnKeyDown(wParam, lParam);
//		break;
//	case WM_KEYUP:
//		OnKeyUp(wParam, lParam);
//		break;
	case WM_LBUTTONDOWN:
		OnLButtonDown(wParam, lParam);
		break;
	case WM_RBUTTONDOWN:
		OnRButtonDown(wParam, lParam);
		break;
	case WM_LBUTTONUP:
		OnLButtonUp(wParam, lParam);
		break;
	case WM_RBUTTONUP:
		OnRButtonUp(wParam, lParam);
		break;
//	case WM_MOVE:
//		OnMove(wParam, lParam);
//		break;
//	case WM_SYSKEYDOWN:
//		return OnSysKeyDown(wParam, lParam);
//	case WM_SYSKEYUP:
//		return OnSysKeyUp(wParam, lParam);
//	case _WM_USER_MSG_INPUTTED:
//		return OnMsgInputted(wParam, lParam);
	default:
		//socket¶ÁÈ¡ÏûÏ¢
		if( uMsg == m_pSocket->m_dwEventFilter )
		{
			m_pSocket->OnSocketMessage(wParam, lParam);
		}
		break;
	}

	return 0;
}



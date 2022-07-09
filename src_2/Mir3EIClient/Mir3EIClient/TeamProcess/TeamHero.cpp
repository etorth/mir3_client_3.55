#include "stdafx.h"
#include ".\teamhero.h"

CTeamHero::CTeamHero(void)
{
	m_bActive = FALSE;
}

CTeamHero::~CTeamHero(void)
{
}

BOOL CTeamHero::OnLButtonDown(POINT ptMouse, INT nTargetID, BOOL bIsDead, POINT* lpptTargetPos)
{
	POINT ptTargetTile;
	POINT ptMouseTilePos;
	BYTE  bDir;

//	if ( g_xGameProc.m_xInterface.OnLButtonDown(ptMouse) )
//		return FALSE;
//	if ( m_wABlendDelay )
//		return FALSE;

	if(	nTargetID == m_dwIdentity )
	{
		m_bActive = !m_bActive;
	}

	if( !m_bActive )
		return FALSE;

	if ( !m_bMotionLock && !m_bInputLock )
	{
		SHORT shLeftMsgCnt = m_xPacketQueue.GetCount();
		if ( shLeftMsgCnt > 0 )
		{
			UpdatePacketState();
			return FALSE;
		}

		ptMouseTilePos = GetPosMouseToTile(ptMouse.x, ptMouse.y);
		bDir		   = CalcDirection(ptMouseTilePos.x, ptMouseTilePos.y);

		//如果在原地(同一个Cell),保持方向不变
		if ( m_wPosX == ptMouseTilePos.x && m_wPosY == ptMouseTilePos.y )
			bDir = m_bCurrDir;

		INT nLength;
		if ( lpptTargetPos ) 
			nLength = (INT)sqrt((float)(m_wPosX-lpptTargetPos->x)*(m_wPosX-lpptTargetPos->x) + (m_wPosY-lpptTargetPos->y)*(m_wPosY-lpptTargetPos->y));
		else
			nLength = (INT)sqrt((float)(float)(m_wPosX-ptMouseTilePos.x)*(m_wPosX-ptMouseTilePos.x) + (m_wPosY-ptMouseTilePos.y)*(m_wPosY-ptMouseTilePos.y));


		// 1. SHIFT.(长距攻击,距离为2)
		if ( HIBYTE(GetKeyState(VK_SHIFT)) )
		{
			if ( m_stFeatureEx.bHorse == _HORSE_NONE )
			{
				if ( m_bUseErgum && ((CTeamProcess*)m_pGameProc)->TargetInLongAttack(bDir)/*检查是否在长距攻击范围内*/ )
				{
					if ( m_stFeatureEx.bHorse == _HORSE_NONE && !bIsDead )
					{
						// 傍拜茄促.
						ptTargetTile.x = m_wPosX;
						ptTargetTile.y = m_wPosY;
						SetMotionState(_MT_ONEHSWING, bDir, nTargetID, bIsDead, &ptTargetTile);
					}
				}
				else
				{
					ptTargetTile.x = m_wPosX;
					ptTargetTile.y = m_wPosY;
					SetMotionState(_MT_ONEHSWING, bDir, nTargetID, bIsDead, &ptTargetTile);				
				}
			}
		}

		// 2. ALT.(戒扁)
		else if ( HIBYTE(GetKeyState(VK_MENU)) )
		{
			SetMotionState(_MT_CUT, bDir, nTargetID, bIsDead, &ptTargetTile);
		}

		// 4. 如果选中目标, 攻击!
		else if ( nTargetID != -1 && lpptTargetPos )
		{
			//1. 短距攻击
			if ( nLength == 1 /*nLength < 2 && nLength > 0*/ ) 
			{
				if ( m_stFeatureEx.bHorse == _HORSE_NONE && !bIsDead )
				{
					// 傍拜茄促.
					ptTargetTile.x = m_wPosX;
					ptTargetTile.y = m_wPosY;
					bDir = CalcDirection(lpptTargetPos->x, lpptTargetPos->y);
					SetMotionState(_MT_ONEHSWING, bDir, nTargetID, bIsDead, &ptTargetTile);

				}
			}
			// 距离不够,移动! 
			else if ( m_pxMap->GetNextTileCanMove(m_wPosX, m_wPosY, bDir, 1, &ptTargetTile) && nLength > 0)
			{
				// 1鸥老 捞悼茄促.
				if ( m_stFeatureEx.bHorse == _HORSE_NONE )		SetMotionState(_MT_WALK, bDir, nTargetID, bIsDead, &ptTargetTile);
				else											SetMotionState(_MT_HORSEWALK, bDir, nTargetID, bIsDead, &ptTargetTile);
			}
			else
			{
				if ( m_stFeatureEx.bHorse == _HORSE_NONE )		SetMotionState(_MT_STAND, bDir);
				else											SetMotionState(_MT_HORSESTAND, bDir);

			}

		}
		// 6. 按照选定的方向 移动 1 个距离
		else if ( m_pxMap->GetNextTileCanMove(m_wPosX, m_wPosY, bDir, 1, &ptTargetTile) && nLength > 0 )
		{
			// 1鸥老 捞悼茄促.
			if ( m_stFeatureEx.bHorse == _HORSE_NONE )			SetMotionState(_MT_WALK, bDir, nTargetID, bIsDead, &ptTargetTile);
			else												SetMotionState(_MT_HORSEWALK, bDir, nTargetID, bIsDead, &ptTargetTile);

		}
		// 7. 如果不能按照鼠标方向移动,尝试多个方向移动
		else if ( !m_pxMap->GetNextTileCanMove(m_wPosX, m_wPosY, bDir, 1, &ptTargetTile) )
		{
			INT nSelectedDir = -1;
			INT nDistance;
			INT nSelectedDistance = 100;
			for ( INT nCnt = 0; nCnt < _MAX_DIRECTION; nCnt++ )
			{
				if ( m_pxMap->GetNextTileCanMove(m_wPosX, m_wPosY, nCnt, 1, &ptTargetTile) )
				{
					nDistance = (INT)(sqrt((float)(ptTargetTile.x-ptMouseTilePos.x)*(ptTargetTile.x-ptMouseTilePos.x) + 
						(ptTargetTile.y-ptMouseTilePos.y)*(ptTargetTile.y-ptMouseTilePos.y)));
					if ( nDistance <= nSelectedDistance )
					{
						nSelectedDistance = nDistance;
						nSelectedDir = nCnt;
					}
				}
			}

			if ( nSelectedDir != -1 && nDistance > 0 )
			{
				// 1鸥老 捞悼茄促.
				m_pxMap->GetNextTileCanMove(m_wPosX, m_wPosY, nSelectedDir, 1, &ptTargetTile);
				if ( m_stFeatureEx.bHorse == _HORSE_NONE )		SetMotionState(_MT_WALK, nSelectedDir, nTargetID, bIsDead, &ptTargetTile);
				else											SetMotionState(_MT_HORSEWALK, nSelectedDir, nTargetID, bIsDead, &ptTargetTile);
			}
			else
			{
				if ( m_stFeatureEx.bHorse == _HORSE_NONE )		SetMotionState(_MT_STAND, bDir);
				else											SetMotionState(_MT_HORSESTAND, bDir);
			}
		}
		else
		{
			if ( m_stFeatureEx.bHorse == _HORSE_NONE )		SetMotionState(_MT_STAND, bDir);
			else											SetMotionState(_MT_HORSESTAND, bDir);
		}
	}

	return FALSE;
}

VOID CTeamHero::SetMotionState(BYTE bMtn, BYTE bDir, INT nMouseTargetID, BOOL bIsDead, LPPOINT lpptPos, SHORT shSkill)
{
		switch ( bMtn )
		{
		case _MT_WALK:
		case _MT_HORSEWALK:
			{
				if ( lpptPos )
				{
					POINT ptNext;

					for ( INT nCnt = 0; nCnt < _MAX_DIRECTION; nCnt++ )
					{
						m_pxMap->GetNextTileCanMove(lpptPos->x, lpptPos->y, nCnt, 1, &ptNext);
						if ( !m_pxMap->IsDoorOpen(ptNext.x, ptNext.y) )
						{
							m_pSocketClient->SendOpenDoor(ptNext.x, ptNext.y, m_pxMap->GetDoor(ptNext.x, ptNext.y));
							break;
						}
					}

					//向服务器发送
					m_pSocketClient->SendRunMsg(CM_WALK, lpptPos->x, lpptPos->y, bDir);
					m_bMotionLock = m_bInputLock = TRUE;//发送行走命令后锁定运动
					m_wOldPosX = m_wPosX;
					m_wOldPosY = m_wPosY;
					m_bOldDir  = m_bCurrDir;

		//			SetMotionFrame(bMtn, bDir);
					m_bMoveSpeed = _SPEED_WALK;

		//			m_pxMap->ScrollMap(m_bMoveDir, m_dwCurrFrame-m_dwFstFrame, m_bMoveSpeed);
				}
				break;
			}
		case _MT_RUN:
		case _MT_HORSERUN:
			{
				if ( lpptPos )
				{
					POINT ptNext;
					POINT ptStart;

					if ( bMtn == _MT_RUN )
						m_bMoveSpeed = _SPEED_RUN;
					else
						m_bMoveSpeed = _SPEED_HORSERUN;

					m_pxMap->GetNextTileCanMove(m_wPosX, m_wPosY, bDir, 1, &ptStart);
					for ( INT nCnt = 0; nCnt < _MAX_DIRECTION; nCnt++ )
					{
						for ( INT nSpeedCnt = 0; nSpeedCnt < m_bMoveSpeed; nSpeedCnt++ )
						{
							m_pxMap->GetNextTileCanMove(ptStart.x, ptStart.y, nCnt, nSpeedCnt+1, &ptNext);
							if ( !m_pxMap->IsDoorOpen(ptNext.x, ptNext.y) )
							{
								m_pSocketClient->SendOpenDoor(ptNext.x, ptNext.y, m_pxMap->GetDoor(ptNext.x, ptNext.y));
								break;
							}
						}
					}

					m_pSocketClient->SendRunMsg(CM_RUN, lpptPos->x, lpptPos->y, bDir);
					m_bMotionLock = m_bInputLock = TRUE;
					m_wOldPosX = m_wPosX;
					m_wOldPosY = m_wPosY;
					m_bOldDir  = m_bCurrDir;

			//		SetMotionFrame(bMtn, bDir);

			//		m_pxMap->ScrollMap(m_bMoveDir, m_dwCurrFrame-m_dwFstFrame, m_bMoveSpeed);			
				}
				break;
			}
		case _MT_ONEHSWING:
			{
				if ( m_bAttackMode == _MT_ONEHSWING || m_bAttackMode == _MT_ONEVSWING )
				{
					BYTE bAttackStyle = rand()%2;
					if ( bAttackStyle )			m_bAttackMode = _MT_ONEVSWING;
					else						m_bAttackMode = _MT_ONEHSWING;

					m_bAttackMode = _MT_ONEVSWING;
				}			

				if ( lpptPos && CanNextHit() )
				{
					m_bMotionLock	= m_bInputLock = TRUE;
					m_wOldPosX		= m_wPosX;
					m_wOldPosY		= m_wPosY;
					m_bOldDir		= m_bCurrDir;
					m_bWarMode		= TRUE;
					m_dwWarModeTime	= 0;

					if ( m_bUseErgum && g_xGameProc.TargetInLongAttack(bDir) )
					{
//						SetMotionFrame(_MT_ONEVSWING, bDir);
						LoadEffect(&g_xGameProc.m_xImage, _SKILL_ERGUM, bDir);
						m_bUseSwordEffect = TRUE;
						m_pSocketClient->SendActMsg(CM_LONGHIT, lpptPos->x, lpptPos->y, bDir);
					}
					else if ( m_bFireHitCnt == 1 && m_stAbility.wMP > 7 )
					{
//						SetMotionFrame(_MT_ONEVSWING, bDir);
						LoadEffect(&g_xGameProc.m_xImage, _SKILL_FIRESWORD, bDir);
						m_bUseSwordEffect = TRUE;
						m_pSocketClient->SendActMsg(CM_FIREHIT, lpptPos->x, lpptPos->y, bDir);
						m_bFireHitCnt = 2;
					}
					else if ( m_bYedoCnt == 1 )
					{
//						SetMotionFrame(_MT_ONEVSWING, bDir);
//						LoadEffect(&g_xGameProc.m_xImage, _SKILL_YEDO, bDir);
						m_bUseSwordEffect = TRUE;
						m_pSocketClient->SendActMsg(CM_POWERHIT, lpptPos->x, lpptPos->y, bDir);
						m_bYedoCnt = 2;
					}
					else if ( m_bUseBanwol && m_stAbility.wMP > 3 )
					{
//						SetMotionFrame(_MT_ONEHSWING, bDir);
//						LoadEffect(&g_xGameProc.m_xImage, _SKILL_BANWOL, bDir);
						m_bUseSwordEffect = TRUE;
						m_pSocketClient->SendActMsg(CM_WIDEHIT, lpptPos->x, lpptPos->y, bDir);
					}
					else
					{
//						SetMotionFrame(m_bAttackMode, bDir);
//						if ( m_bAttackMode == _MT_WHEELWIND )
//						{
//							LoadEffect(&g_xGameProc.m_xImage, _SKILL_JUMPSHOT, bDir);
//							m_bUseSwordEffect = TRUE;
//						}
//						else if ( m_bAttackMode == _MT_RANDSWING )
//						{
//							LoadEffect(&g_xGameProc.m_xImage, _SKILL_RANDSWING, bDir);
//							m_bUseSwordEffect = TRUE;
//						}
						WORD wAttackStyle;
						if ( m_bAttackMode != _MT_ONEVSWING && m_bAttackMode != _MT_ONEHSWING )
							wAttackStyle = _MT_ONEVSWING;
						else
						{
							wAttackStyle = m_bAttackMode;
						}
						m_pSocketClient->SendHitMsg(CM_HIT, lpptPos->x, lpptPos->y, bDir, wAttackStyle);
					}
				}
				break;
			}
		case _MT_MOODEPO:
			{
				if ( lpptPos )		
				{
					m_pSocketClient->SendSpellMsg(shSkill, lpptPos->x, lpptPos->y, 0);
					// 冲撞
					m_dwLastRushTime = timeGetTime();
					m_bMotionLock = m_bInputLock = TRUE;
					m_bWarMode	= TRUE;
				}

				break;
			}
		case _MT_SPELL2:
		case _MT_SPELL1:
			{
				if ( lpptPos )
				{
					m_pSocketClient->SendSpellMsg(shSkill, lpptPos->x, lpptPos->y, nMouseTargetID);

					m_wOldPosX = m_wPosX;
					m_wOldPosY = m_wPosY;
					m_bOldDir  = m_bCurrDir;

					m_bMotionLock = m_bInputLock = TRUE;
					m_bWarMode	= TRUE;

					if ( m_shCurrMagicID == _SKILL_FIREBALL || m_shCurrMagicID == _SKILL_FIREBALL2 || m_shCurrMagicID == _SKILL_FIRE || m_shCurrMagicID == _SKILL_SHOOTLIGHTEN ||
						m_shCurrMagicID == _SKILL_HANGMAJINBUB || m_shCurrMagicID== _SKILL_DEJIWONHO || m_shCurrMagicID == _SKILL_FIRECHARM || m_shCurrMagicID == _SKILL_SINSU ||
						m_shCurrMagicID == _SKILL_BIGCLOAK )
						LoadEffect(&g_xGameProc.m_xImage, m_shCurrMagicID, bDir);
					else
						LoadEffect(&g_xGameProc.m_xImage, m_shCurrMagicID);

					m_bUseEffect = TRUE;
					if ( m_shCurrMagicID == _SKILL_SHOWHP )
						m_bEffectFrameCnt = 20;
					else if ( m_shCurrMagicID == _SKILL_LIGHTFLOWER )
						m_bEffectFrameCnt = 15;
					else if ( m_shCurrMagicID == _SKILL_SPACEMOVE )
						m_bEffectFrameCnt = 19;
					else if ( m_shCurrMagicID == _SKILL_LIGHTENING )			
						m_bEffectFrameCnt = 17;


//					SetMotionFrame(bMtn, bDir);
				}
				break;
			}
		case _MT_CUT:
			{
				m_bInputLock = TRUE;
				m_bMotionLock = TRUE;
				m_wOldPosX = m_wPosX;
				m_wOldPosY = m_wPosY;
				m_bOldDir  = m_bCurrDir;
//				SetMotionFrame(bMtn, bDir);

				m_pSocketClient->SendActMsg(CM_SITDOWN, m_wPosX, m_wPosY, bDir);
				if ( nMouseTargetID && bIsDead )
				{
					m_pSocketClient->SendButchAnimal(m_wPosX, m_wPosY, bDir, nMouseTargetID);
				}
				break;
			}
		case _MT_HORSESTAND:
		case _MT_STAND:
			{
				if ( bDir != m_bCurrDir )	
				{
					m_pSocketClient->SendActMsg(CM_TRUN, m_wPosX, m_wPosY, bDir);
					m_bMotionLock = TRUE;
					m_bInputLock = TRUE;
					m_wOldPosX = m_wPosX;
					m_wOldPosY = m_wPosY;
					m_bOldDir  = m_bCurrDir;
//					SetMotionFrame(bMtn, bDir);
				}
				break;
			}
		}


	m_dwMotionLockTime	= 0;
}


VOID CTeamHero::UpdateMotionState(INT nLoopTime, BOOL bIsMoveTime)
{
	if ( m_bMotionLock ) 
		m_dwMotionLockTime += nLoopTime;

	if ( m_bWarMode ) 
		m_dwWarModeTime += nLoopTime;

	m_wABlendCurrDelay += nLoopTime;
	if ( m_wABlendCurrDelay >= m_wABlendDelay )
	{
		m_wABlendCurrDelay = 0;
		m_wABlendDelay	   = 0;
		m_bABlendRev	   = FALSE;
	}

	if ( m_bCurrMtn == _MT_DIE && m_dwCurrFrame >= m_dwEndFrame-1 )
	{
		m_bIsDead = TRUE;
	}

	if ( m_bIsDead )
	{
		m_dwCurrFrame = m_dwEndFrame - 1;
		m_bInputLock  = TRUE;
		return;
	}


	if ( UpdateMove(bIsMoveTime) )
	{
		UpdatePacketState();
		return;
	}
	else
	{
		if ( !m_bIsMon )
		{
			m_wCurrDelay += nLoopTime;

			m_wShieldCurrDelay += nLoopTime;

			if ( m_wShieldCurrDelay > 150 )  
			{
				m_bShieldCurrFrm++;
				m_wShieldCurrDelay = 0;
				if ( m_bShieldCurrFrm > 2 )
					m_bShieldCurrFrm = 0;
			}

			if ( m_wCurrDelay > m_wDelay )
			{
				m_wCurrDelay  = 0;

				if ( m_dwCurrFrame < m_dwEndFrame )
				{
					m_dwCurrFrame++;

					PlayActSound();

					if ( (m_bCurrMtn == _MT_SPELL2 || m_bCurrMtn == _MT_SPELL1) && m_bUseEffect )
					{
						m_dwCurrEffectFrame++;
						m_bEffectFrame++;
					}
				}
			}

			UpdatePacketState();

			// 楷加利牢 橇饭烙 吝俊辑 秦具且老.
			if ( m_dwMotionLockTime > _MOTION_LOCKTIME )
			{
				m_dwMotionLockTime = 0;
				m_bMotionLock	   = FALSE;
				//				SetOldPosition();
			}

			if ( m_dwWarModeTime > _WARMODE_TIME )
			{
				m_dwWarModeTime = 0;
				m_bWarMode		= FALSE;
			}

			if ( m_dwCurrFrame >= m_dwEndFrame-1 )
			{
				if ( (m_bCurrMtn == _MT_SPELL2) && m_bUseEffect )
				{
					if ( m_dwCurrEffectFrame - m_dwFstEffectFrame < m_bEffectFrameCnt-2 )
					{
						m_dwCurrFrame = m_dwEndFrame - 2;
					}
				}
			}
			else if ( m_dwCurrFrame >= m_dwEndFrame-3 )
			{
				if ( (m_bCurrMtn == _MT_SPELL1) && m_bUseEffect )
				{
					if ( m_dwCurrEffectFrame - m_dwFstEffectFrame < m_bEffectFrameCnt-5 )
					{
						m_dwCurrFrame = m_dwEndFrame - 4;
					}
				}
			}

			if ( m_dwCurrFrame >= m_dwEndFrame )
			{
				switch ( m_bCurrMtn )
				{
				case _MT_CUT:
					{
						m_bInputLock  = FALSE;
						m_bMotionLock = FALSE;
						m_dwCurrFrame = m_dwFstFrame;
//						if ( m_stFeatureEx.bHorse == _HORSE_NONE )		SetMotionFrame(_MT_STAND, m_bCurrDir);
//						else											SetMotionFrame(_MT_HORSESTAND, m_bCurrDir);
					}
					break;
				case _MT_STAND:
				case _MT_HORSESTAND:
					{
						m_bInputLock  = FALSE;
						m_bMotionLock = FALSE;
						m_bUseEffect = FALSE;
						m_bUseSwordEffect = FALSE;
						m_dwCurrFrame = m_dwFstFrame;
						break;
					}
				case _MT_ATTACKMODE:
					{
//						if ( !m_bWarMode )
//							SetMotionFrame(_MT_STAND, m_bCurrDir);
//						else
//						{
//							m_bInputLock  = FALSE;
//							m_bMotionLock = FALSE;
//							m_dwCurrFrame = m_dwFstFrame;
//						}
						if ( m_bWarMode )
						{
							m_bInputLock  = FALSE;
							m_bMotionLock = FALSE;
							m_dwCurrFrame = m_dwFstFrame;
						}
						break;
					}
				default:
					{
						m_dwCurrEffectFrame = 0;
						m_dwFstEffectFrame = 0;
						m_dwEndEffectFrame = 0;
						m_bEffectFrame = 0;
						m_bEffectFrameCnt = _DEFAULT_SPELLFRAME;
						m_bUseEffect = FALSE;
						m_bUseSwordEffect = FALSE;
						if ( !m_bMotionLock )
						{				
							m_bInputLock = FALSE;

//							if ( m_stFeatureEx.bHorse == _HORSE_NONE )
//							{
//								if ( m_bWarMode )
//									SetMotionFrame(_MT_ATTACKMODE, m_bCurrDir);
//								else
//									SetMotionFrame(_MT_STAND, m_bCurrDir);
//							}
//							else
//							{
//								SetMotionFrame(_MT_HORSESTAND, m_bCurrDir);
//							}
						}
						else
						{
							m_dwCurrFrame = m_dwEndFrame-1;
						}
					}
					break;
				}
			}

			if ( m_bCurrMtn == _MT_STAND || m_bCurrMtn == _MT_HORSESTAND )
			{
				POINT ptMouse;
				GetCursorPos(&ptMouse);
				ScreenToClient(g_xMainWnd.GetSafehWnd(), &ptMouse);
				m_bCanRun = FALSE;

				if ( HIBYTE(GetKeyState(VK_RBUTTON)) || ( HIBYTE(GetKeyState(VK_LBUTTON)) && HIBYTE(GetKeyState(VK_CONTROL))) )
				{
					OnRButtonDown(ptMouse);
				}
				else if ( HIBYTE(GetKeyState(VK_LBUTTON)) )
				{
					//左键
					OnLButtonDown(ptMouse);

					/*					LPARAM lParam = MAKELPARAM((WORD)ptMouse.x, (WORD)ptMouse.y);
					WPARAM wParam = 0;
					g_xGameProc.OnLButtonDown(wParam, lParam);
					*/			
				}
			}
		}
	}
		
}

BOOL CTeamHero::UpdateMove(BOOL bIsMoveTime)
{
//		if ( m_bCurrMtn == _MT_WALK || m_bCurrMtn == _MT_RUN || m_bCurrMtn == _MT_HORSEWALK || m_bCurrMtn == _MT_HORSERUN || m_bCurrMtn == _MT_MOODEPO || m_bCurrMtn == _MT_PUSHBACK)
//		{
//			m_wCurrDelay = 0;
//
//			if ( bIsMoveTime )
//			{
//				if ( m_bCurrMtn == _MT_PUSHBACK )
//				{
//
//				}
//				else if ( m_bCurrMtn == _MT_MOODEPO )
//				{
//	
//				}
//				else
//				{
//					if ( m_bCurrMtn == _MT_PUSHBACK )
//					{
//						if ( m_bBackStepFrame >= m_bBackStepFrameCnt-m_bMoveNextFrmCnt && !m_bIsMoved )
//						{
//							SetMoved();
//							m_bIsMoved = TRUE;
//						}
//					}
//					else
//					{
//						if ( m_dwCurrFrame >= m_dwEndFrame-m_bMoveNextFrmCnt && !m_bIsMoved )
//						{
//							SetMoved();
//							m_bIsMoved = TRUE;
//						}
//					}
//			}
//
//			// 楷加利牢 橇饭烙 吝俊辑 秦具且老.
//			if ( m_dwCurrFrame >= m_dwEndFrame )
//			{
//				m_dwCurrFrame = m_dwEndFrame-1;
//				m_bCanRun = FALSE;
//
//				switch ( m_bCurrMtn )
//				{
//				case _MT_MOODEPO:
//					{
//						if ( m_bInputLock )
//						{
//							m_bIsMoved = FALSE;
//							m_bInputLock = FALSE;
//							m_pxMap->SetMovedTileBuffer(m_shShiftTileX, m_shShiftTileY);
//							m_bMoveSpeed	= 0;
//							m_shShiftPixelX	= 0;
//							m_shShiftPixelY	= 0;
//							m_shShiftTileX	= 0;
//							m_shShiftTileY	= 0;
//							// 捞悼饶 谅钎犬牢.
//							if ( CheckMyPostion() == FALSE )
//								AdjustMyPostion();
//
//							if ( m_bWarMode )
//								SetMotionFrame(_MT_ATTACKMODE, m_bCurrDir);
//							else
//								SetMotionFrame(_MT_STAND, m_bCurrDir);
//						}
//						break;
//					}
//				case _MT_PUSHBACK:
//					{
//						if ( m_bInputLock )
//						{
//							m_bIsMoved = FALSE;
//							m_bInputLock = FALSE;
//							m_pxMap->SetMovedTileBuffer(m_shShiftTileX, m_shShiftTileY);
//							m_bMoveSpeed	= 0;
//							m_shShiftPixelX	= 0;
//							m_shShiftPixelY	= 0;
//							m_shShiftTileX	= 0;
//							m_shShiftTileY	= 0;
//
//							m_bBackStepFrame = 0;
//							m_bBackStepFrameCnt = 0;
//							// 捞悼饶 谅钎犬牢.
//							if ( CheckMyPostion() == FALSE )
//								AdjustMyPostion();
//
//							if ( m_bWarMode )
//								SetMotionFrame(_MT_ATTACKMODE, m_bCurrDir);
//							else
//								SetMotionFrame(_MT_STAND, m_bCurrDir);
//						}
//						break;
//					}
//				case _MT_WALK:
//				case _MT_HORSEWALK:
//					{
//						if ( !m_bMotionLock && m_bInputLock )
//						{
//							m_bIsMoved = FALSE;
//							m_bInputLock = FALSE;
//							m_pxMap->SetMovedTileBuffer(m_shShiftTileX, m_shShiftTileY);
//							m_bMoveSpeed	= 0;
//							m_shShiftPixelX	= 0;
//							m_shShiftPixelY	= 0;
//							m_shShiftTileX	= 0;
//							m_shShiftTileY	= 0;
//
//							if ( m_bCurrMtn == _MT_WALK && m_stFeatureEx.bHorse == _HORSE_NONE )
//							{
//								if ( m_bWarMode )
//								{
//									SetMotionFrame(_MT_ATTACKMODE, m_bCurrDir);
//								}
//								else		SetMotionFrame(_MT_STAND, m_bCurrDir);
//							}
//							else	SetMotionFrame(_MT_HORSESTAND, m_bCurrDir);
//
//							// 捞悼饶 谅钎犬牢.
//							if ( CheckMyPostion() == FALSE )
//								AdjustMyPostion();
//							POINT ptMouse;
//							GetCursorPos(&ptMouse);
//							ScreenToClient(g_xMainWnd.GetSafehWnd(), &ptMouse);
//							if ( HIBYTE(GetKeyState(VK_RBUTTON)) || ( HIBYTE(GetKeyState(VK_LBUTTON)) && HIBYTE(GetKeyState(VK_CONTROL))) )
//							{
//								m_bCanRun = TRUE;
//								OnRButtonDown(ptMouse);
//							}
//							else if ( HIBYTE(GetKeyState(VK_LBUTTON)) )
//							{
//								OnLButtonDown(ptMouse);
//							}
//						}
//						break;
//					}
//				case _MT_RUN:
//				case _MT_HORSERUN:
//					{
//						if ( !m_bMotionLock && m_bInputLock )
//						{				
//							m_bIsMoved = FALSE;
//							m_bInputLock = FALSE;
//							m_pxMap->SetMovedTileBuffer(m_shShiftTileX, m_shShiftTileX);
//							m_bMoveSpeed	= 0;
//							m_shShiftPixelX	= 0;
//							m_shShiftPixelY	= 0;
//							m_shShiftTileX	= 0;
//							m_shShiftTileY	= 0;
//
//							if ( m_bCurrMtn == _MT_RUN && m_stFeatureEx.bHorse == _HORSE_NONE )
//							{
//								if ( m_bWarMode )
//								{
//									SetMotionFrame(_MT_ATTACKMODE, m_bCurrDir);
//								}
//								else	SetMotionFrame(_MT_STAND, m_bCurrDir);
//							}
//							else	SetMotionFrame(_MT_HORSESTAND, m_bCurrDir);
//
//							if ( CheckMyPostion() == FALSE )
//								AdjustMyPostion();
//							POINT ptMouse;
//							GetCursorPos(&ptMouse);
//							ScreenToClient(g_xMainWnd.GetSafehWnd(), &ptMouse);
//
//							if ( HIBYTE(GetKeyState(VK_RBUTTON)) || ( HIBYTE(GetKeyState(VK_LBUTTON)) && HIBYTE(GetKeyState(VK_CONTROL))) )
//							{
//								m_bCanRun = TRUE;
//								OnRButtonDown(ptMouse);
//							}
//							else if ( HIBYTE(GetKeyState(VK_LBUTTON)) )
//							{
//								OnLButtonDown(ptMouse);
//							}
//						}
//						break;
//					}
//				}
//			}
//			else
//			{
//				switch ( m_bCurrMtn )
//				{
//				case _MT_WALK:
//				case _MT_RUN:
//				case _MT_HORSEWALK:
//				case _MT_HORSERUN:
//				case _MT_MOODEPO:
//					m_pxMap->ScrollMap(m_bMoveDir, m_dwCurrFrame-m_dwFstFrame, m_bMoveSpeed);			
//					//					m_pxMap->ScrollMap(m_bMoveDir, m_wCurrDelay, m_wDelay*(m_dwEndFrame-m_dwFstFrame), m_bMoveSpeed);
//					break;
//				case _MT_PUSHBACK:
//					m_pxMap->ScrollMap(m_bMoveDir, m_bBackStepFrame, m_bMoveSpeed);			
//					break;
//				}
//			}
//
//			// 楷加利牢 橇饭烙 吝俊辑 秦具且老.
//			if ( m_dwMotionLockTime > _MOTION_LOCKTIME )
//			{
//				m_dwMotionLockTime = 0;
//				m_bMotionLock	   = FALSE;
//				//				SetOldPosition();
//			}
//
//			if ( m_dwWarModeTime > _WARMODE_TIME )
//			{
//				m_dwWarModeTime = 0;
//				m_bWarMode		= FALSE;
//			}
//
//			return TRUE;
//		}

	return FALSE;
}

BOOL CTeamHero::UpdatePacketState()
{	
	LPPACKETMSG	lpPacketMsg = NULL;

	SHORT shLeftMsgCnt = m_xPriorPacketQueue.GetCount();

	if ( shLeftMsgCnt > 0 )
	{
		lpPacketMsg = (LPPACKETMSG)m_xPriorPacketQueue.PopQ();
		if ( lpPacketMsg )
		{
			if ( lpPacketMsg->stDefMsg.wIdent == SM_NOWDEATH || lpPacketMsg->stDefMsg.wIdent == SM_DEATH )
			{
				OnDeath(lpPacketMsg);
				SAFE_DELETE(lpPacketMsg);
				return TRUE;
			}
		}
	}

	if ( m_bCurrMtn == _MT_STAND || m_bCurrMtn == _MT_ATTACKMODE || m_bCurrMtn == _MT_HORSESTAND || (m_bCurrMtn==_MT_SPELL1 && m_dwCurrFrame==m_dwEndFrame - 2) )
	{
		LPPACKETMSG	lpPacketMsg;

		SHORT shLeftMsgCnt = m_xPacketQueue.GetCount();

		if ( shLeftMsgCnt > 0 )
		{
			lpPacketMsg = (LPPACKETMSG)m_xPacketQueue.PopQ();

			if ( shLeftMsgCnt >= 3 )		m_bMsgHurryCheck = TRUE;
			else							m_bMsgHurryCheck = FALSE;

//			if ( lpPacketMsg )
//			{
//				switch ( lpPacketMsg->stDefMsg.wIdent )
//				{
//				case SM_STRUCK:
//					{
//						m_bInputLock = TRUE;
//						m_stAbility.wHP	   = lpPacketMsg->stDefMsg.wParam;
//						m_stAbility.wMaxHP = lpPacketMsg->stDefMsg.wTag;
//						OnStruck(lpPacketMsg);
//
//						if ( m_dwNameClr == RGB(255, 0, 0) )
//						{
//							m_dwLastPKStruckTime = timeGetTime();
//						}
//						m_dwLastStruckTime = timeGetTime();
//						break;
//					}
//				case SM_RUSH:
//					{
//						m_bInputLock = TRUE;
//						m_wOldPosX	 = m_wPosX;
//						m_wOldPosY	 = m_wPosY;
//						m_bOldDir	 = m_bCurrDir;
//						OnRush(lpPacketMsg);
//						if ( !CheckMyPostion() )			AdjustMyPostion();
//						m_pxMap->ScrollMap(m_bMoveDir, m_dwCurrFrame-m_dwFstFrame, m_bMoveSpeed);
//						break;
//					}
//				case SM_BACKSTEP:
//					{
//						m_bInputLock = TRUE;
//						m_wOldPosX = m_wPosX;
//						m_wOldPosY = m_wPosY;
//						m_bOldDir  = m_bCurrDir;
//						OnBackStep(lpPacketMsg);
//
//						if ( !CheckMyPostion() )			AdjustMyPostion();
//						m_pxMap->ScrollMap(m_bMoveDir, m_dwCurrFrame-m_dwFstFrame, m_bMoveSpeed);			
//						break;
//					}
//				case SM_FEATURECHANGED:		{	OnFeatureChanged(lpPacketMsg);		break;	}
//				case SM_OPENHEALTH:			{	OnOpenHealth(lpPacketMsg);			break;	}
//				case SM_CLOSEHEALTH:		{	OnCloseHealth(lpPacketMsg);			break;	}
//				case SM_CHANGELIGHT:		{	OnChangeLight(lpPacketMsg);			break;	}
//				case SM_USERNAME:			{	OnUserName(lpPacketMsg);			break;	}
//				case SM_CHANGENAMECOLOR:	{	OnChangeNameClr(lpPacketMsg);		break;	}
//				case SM_CHARSTATUSCHANGE:	{	OnCharStatusChanged(lpPacketMsg);	break;	}
//				case SM_MAGICFIRE:			{	OnMagicFire(lpPacketMsg);			break;	}
//				case SM_HEALTHSPELLCHANGED:	{	OnHealthSpellChanged(lpPacketMsg);	break;	}
//				default:
//					{										
//						break;	
//					}
//				}				
//			}
			SAFE_DELETE(lpPacketMsg);

			return TRUE;
		}
	}
	return FALSE;
}

BOOL CTeamHero::SetOldPosition()
{
	m_wPosX	   = m_wOldPosX;
	m_wPosY	   = m_wOldPosY;
	m_bCurrDir = m_bOldDir;

	if ( m_stFeatureEx.bHorse == _HORSE_NONE )
	{
		if ( SetMotionFrame(_MT_STAND, m_bCurrDir) )
		{
		//	AdjustMyPostion();
			m_bMotionLock = m_bInputLock = FALSE;
			return TRUE;
		}
	}
	else
	{
		if ( SetMotionFrame(_MT_HORSESTAND, m_bCurrDir) )
		{
		//	AdjustMyPostion();
			m_bMotionLock = m_bInputLock = FALSE;
			return TRUE;
		}
	}
	return FALSE;
}













#include "StdAfx.h"
#include "seed.h"

#define	MAXBUFFER		100000

#define	ENCRYPTMODE		1
#define	DECRYPTMODE		2

//DLL에 저장된 KEY값..
CHAR SUBKEY[16] = {122,121,22,67,43,78,33,67};


BYTE TPT[MAXBUFFER], TCT[MAXBUFFER];


struct my_error_mgr {
  struct jpeg_error_mgr pub;	/* "public" fields */

  jmp_buf setjmp_buffer;	/* for return to caller */
};

typedef struct my_error_mgr * my_error_ptr;


METHODDEF(void) my_error_exit (j_common_ptr cinfo);

METHODDEF(void) my_error_exit (j_common_ptr cinfo)
{
	/* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
	my_error_ptr myerr = (my_error_ptr) cinfo->err;

	char buffer[JMSG_LENGTH_MAX];

	/* Create the message */
	(*cinfo->err->format_message) (cinfo, buffer);

	/* Always display the message. */
	MessageBox(NULL,buffer,"JPEG Fatal Error",MB_ICONSTOP);


	/* Return control to the setjmp point */
	longjmp(myerr->setjmp_buffer, 1);
}


// 게임시간 공지
INT g_nMsgIdx = 1560;
INT g_nNoticeTimes = 0;


/******************************************************************************************************************

	게임 플레이 관련 함수들.

*******************************************************************************************************************/

/******************************************************************************************************************

	함수명 : CGameProcess::CGameProcess()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
CGameProcess::CGameProcess()
{
	Init();

	m_hBrush = NULL;
}



/******************************************************************************************************************

	함수명 : CGameProcess::~CGameProcess()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
CGameProcess::~CGameProcess()
{
	DeleteProc();
}



VOID CGameProcess::Init()
{
	m_hFindHackDll			= NULL;
	m_bDrawName				= FALSE;
	m_bTileView				= FALSE;
	m_bObj1View				= FALSE;
	m_bObj2View				= FALSE;
	m_bCellView				= FALSE;
	m_bStatusView			= FALSE;
	m_bDebugInfo			= FALSE;
	m_bStopPtView			= FALSE;
	m_bRender				= FALSE;
	m_bShowSnow				= FALSE;
	m_bSnowOn				= TRUE;
	m_bShowMist				= FALSE;
	m_bShowRain				= FALSE;
	m_bShadowABlend			= FALSE;
	m_bNoticeCehcked		= FALSE;
	m_bRunTarget			= FALSE;
	m_bAutoTarget			= FALSE;
	m_bChatSave				= FALSE;
	m_bVerChk				= FALSE;
	m_bViewMonInfo			= TRUE;
	m_bAutoMagic			= TRUE;

	m_bUseHotKey			= TRUE;
	m_bViewMode				= _VIEW__WITH_NORMAL;
	m_nViewLGapX			= 0;
	m_nViewRGapX			= 0;

	m_bDrawGroundItemName	= FALSE;

	
//  Speed Hack관련.	
	m_dwFindHackTime		= 0;
	m_dwClientActTick		= 0;
	m_dwServerActTick		= 0;
	m_fHackTickRate			= 1.0f;
	m_nHackCnt				= 0;
	m_fTickSum				= 0.0f;
	m_nTickCnt				= 0;

	m_bShowFPS				= FALSE;
	m_bShowBloodNum			= TRUE;
	m_bAttackUser			= FALSE;
	m_bDrawMagicLight		= TRUE;

	ZeroMemory(&m_ptMousePos, sizeof(POINT));
	ZeroMemory(&m_ptCurrTile, sizeof(POINT));
	ZeroMemory(m_stMemMappedID, sizeof(MEMMAPPEDID)*_VIEW_CELL_X_COUNT* _VIEW_CELL_Y_COUNT);

	m_bDayState				= _DAYSTATE_NIGHT;
	m_bFogState				= _FOGSTATE_NIGHT;

	m_pxMouseTargetActor	= NULL;		// 현재 마우스가 가리키는 곳의 타겟액터.
	m_pxMouseOldTargetActor	= NULL;		// 저장되어있는 타겟액터.
	m_pxSavedTargetActor	= NULL;
	m_pxAutoSavedTargetActor= NULL;
	m_pxExplainActor		= NULL;

	m_fTileLightRed			= 255;
	m_fTileLightGreen		= 230;
	m_fTileLightBlue		= 180;

	m_fDarkRate				= 0.0f;
	m_dwInputDelayTime		= 0;
	m_dwCurrInputDelayTime	= 0;

	m_nNPCWndPosX			= 0;
	m_nNPCWndPosY			= 0;
	m_nAreaState			= 0;

	m_bFateState			= 0;
	m_dwFadeTime			= 0;

	m_bNoticeSeed1			= 0;
	m_bNoticeSeed2			= 0;
	m_wNoticeSeed3			= 0;
	m_wNoticeSeed4			= 0;

	ZeroMemory(m_wShadowClr, 800);

	m_ShowAddOn				= FALSE;
	ZeroMemory(m_szTime, 15);
	
	m_dwMonShowTick			= 0;
	m_dwNPCClickTick		= 0;

	m_dwMapMoveTime			= 0;
	m_bPlayBGM				= FALSE;

	m_bShowPaySys			= FALSE;

	m_dwPickUpTime			= 0;
	m_bAutoPickup			= FALSE;
	m_bDrawHealthNum		= FALSE;

	m_bSetMiniMap			= FALSE;
	
	m_bShowHelmet			= FALSE;
	m_bShowMonEffect		= FALSE;
	m_bShowDeying			= FALSE;

	// Follow 관련
	m_dwFollowTimer			= 0;
	m_nIdxFollowChar		= 0;
	m_bFollowChar			= FALSE;

	ZeroMemory(m_szSocket, MAX_PATH);

	SetRect(&m_rcEventMsg, 0, 0, 300, 200);
	m_xEventMsglist.ClearAll();
	m_dwEventMsgMaxTime		= 0;
	m_dwEventMsgTimer		= 0;
	m_bDrawEventMsg			= FALSE;
	m_nMsgImgIdx			= -1;

	m_bHasTarget			= FALSE;
	m_bIncreaseX			= TRUE;
	m_bIncreaseY			= TRUE;
	m_nMoveDir				= 0;
	m_dwAutoTimer			= 0;

	m_dwLoadTxtTimer	= 0;
	m_nLoadTxtImg		= 2230;

	m_bCreditShow			= FALSE;

	m_dwNameQueryTimer		= 0;
	// 공지영역 정의.
	SetRect(&m_rcCredit, 200, 0, 450, 600);
	
	m_bDiceModeActive		= FALSE;
	m_dwDicePlayTime		= 0;
	m_dwCurrDicePlayTime	= 0;
	ZeroMemory(&m_pszCmd, sizeof(MAX_PATH));
	ZeroMemory(&m_rcDiceBoard, sizeof(RECT)); 
	ZeroMemory(m_stDiceInfo, sizeof(DICEINFO)*_MAX_DICE); 

	ZeroMemory(m_szMapName, MAX_PATH);

	m_xImage.InitAllImage();
	m_xInterface.Init();
	m_xMyHero.InitActor();
	m_xMap.InitMapHandler();

	//m_xLightFog.Init(RGB(255, 255, 255));

	m_xMist.Init();
	m_xFlyingTail.InitSystem();
	m_xSmoke.InitSystem();
	m_xBoom.InitSystem();
	m_xSnow.InitSystem();
	m_xScatter.InitSystem();
	m_xRain.InitSystem();
	m_xElec.InitElec();

	// 지속시간 표시 초기화
	m_xMagicEftTimeList.ClearAll();

	m_xImageLogin.Init();

//	m_hbmMouse.ReleaseSurface();

	m_nMagicStoneIdx = -1;
}


VOID CGameProcess::DeleteProc()
{
	INT			nCnt;
	INT			nLeftMsgCnt;
	LPPACKETMSG	lpPacketMsg;

	KillTimer(g_xMainWnd.GetSafehWnd(), _TIMER_ID);

	lpPacketMsg = NULL;
	nLeftMsgCnt = m_xWaitPacketQueue.GetCount();

	// 쌓여있는 패킷을 지운다.
	if ( nLeftMsgCnt > 0 )
	{
		for ( nCnt = 0; nCnt < nLeftMsgCnt; nCnt++ )
		{
			lpPacketMsg = (LPPACKETMSG)m_xWaitPacketQueue.PopQ();
			if ( lpPacketMsg )
			{
				SAFE_DELETE(lpPacketMsg);
			}
		}
	}

	_TDEFAULTMESSAGE*	lpstDefMsg;
	lpstDefMsg = NULL;
	nLeftMsgCnt = m_xWaitDefaultPacketQueue.GetCount();

	// 쌓여있는 패킷을 지운다.
	if ( nLeftMsgCnt > 0 )
	{
		for ( nCnt = 0; nCnt < nLeftMsgCnt; nCnt++ )
		{
			lpstDefMsg = (_TDEFAULTMESSAGE*)m_xWaitDefaultPacketQueue.PopQ();
			if ( lpstDefMsg )
			{
				SAFE_DELETE(lpstDefMsg);
			}
		}
	}

	if ( m_hBrush )
	{
		DeleteObject(m_hBrush);
	}

	m_xImage.DeleteAllImage();
	m_xMap.DestroyMapHandler();
	m_xInterface.Destroy();
	m_xMyHero.DestroyActor();
	m_xMist.Destory();

	m_xSnow.DestroySystem();
	m_xRain.DestroySystem();
	m_xScatter.DestroySystem();

	MagicListClear();
	GroundMagicListClear();
	ActorListClear();
	m_stGroupPosList.ClearAll();
	m_stMapItemList.ClearAll();
	m_stEventImgList.ClearAll();

	g_SoundManager.SndmngrReleaseAllWaveSound();
	g_SoundManager.SndmngrStopMp3();

	Init();

	m_xImageLogin.Destroy();

//	g_xClientSocket.DisconnectToServer();
	
	strcpy(g_szServerIP,g_szPreServerIP);
	g_nServerPort = g_nPreServerPort;
}



/******************************************************************************************************************

	함수명 : CGameProcess::Load()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CGameProcess::Load()
{
	INT nCnt;

	if ( g_execCmds.bFullScreen )
	{
		g_xMainWnd.ResetDXG(800, 600, _SCREEN_BPP, _DXG_SCREENMODE_FULLSCREEN, _DXG_DEVICEMODE_PRIMARY|_DXG_DEVICEMODE_D3D);
	}
	else
	{
		g_xMainWnd.ResetDXG(800, 600, _SCREEN_BPP, _DXG_SCREENMODE_WINDOW, _DXG_DEVICEMODE_PRIMARY|_DXG_DEVICEMODE_D3D);
	}

	Init();
	g_xClientSocket.ConnectToServer(g_xMainWnd.GetSafehWnd(), g_szServerIP, g_nServerPort);

	m_xImage.LoadAllImage();

	m_xGameMsgBox.InitMsgBox();
/*
	CHAR pszMsg[MAX_PATH];
	sprintf(pszMsg, "\r\n\r\n                    %s\r\n                  %s\r\n               %s",
		    g_xMsg.GetMsg(1400), g_xMsg.GetMsg(1401), g_xMsg.GetMsg(1402));

	m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GAMEOUT, _NONE, pszMsg, FALSE, 235, 164);
*/
	m_bShowLoading = TRUE;
	m_nLoadImg = GetRandomNum(360, 373);

	m_hBrush = CreateSolidBrush(RGB(30, 30, 30));

	m_xLightFog.Init(RGB(25, 25, 25));
	//m_xLightFog.Init(RGB(255, 255, 255));
	m_xInterface.CreateInterface(&m_xImage);
	m_xNotice.Load(&m_xImage.m_xImageList[_IMAGE_INTER]);
	m_xMist.Create();
	m_xSnow.InitSystem();
	m_xSnow.SetupSystem();
	m_xScatter.InitSystem();
	m_xScatter.SetupSystem();
	m_xRain.InitSystem();
	m_xRain.SetupSystem();
	m_xFlyingTail.InitSystem();
	m_xFlyingTail.SetupSystem();
	m_xSmoke.InitSystem();
	m_xSmoke.SetupSystem();
	m_xBoom.InitSystem();
	m_xBoom.SetupSystem();
	m_xElec.InitElec();
	m_xElec.SetupElec();

	ZeroMemory(m_stMemMappedID, sizeof(MEMMAPPEDID)*_VIEW_CELL_X_COUNT* _VIEW_CELL_Y_COUNT);

	ZeroMemory(g_xChatEditBox.m_szInputMsg, sizeof(g_xChatEditBox.m_szInputMsg));
	SetWindowText(g_xChatEditBox.GetSafehWnd(), "");
	SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETPASSWORDCHAR, NULL, 0);
	g_xChatEditBox.SetLimitText(90);
	g_xChatEditBox.SetEnterUse(TRUE);

	WORD wShadowClr = g_xMainWnd.ConvertColor24To16(RGB(20, 20, 20));
	for ( nCnt = 0; nCnt < 800; nCnt++ )
	{
		m_wShadowClr[nCnt] = wShadowClr;
	}

	m_xImage.DelAllTextrFileList();


/*	for ( INT nFrm = 0; nFrm < m_xImage.m_xImageList[_IMAGE_MAGIC].m_nIndexCount; nFrm++ )
	{
		g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_MAGIC, _IMAGE_MAGIC, nFrm);
	}*/

//	CreateLog();

//	m_hbmMouse.DDLoadBitmap(g_xMainWnd.GetDirectDraw(), "Mouse.bmp", 60, 40);




}	


VOID CGameProcess::MagicListClear()
{
	CListNode < CMagic >		*pNode;
	CListNode < CMagic >		*pNodeTemp;
	CMagic*						pxMagic = NULL;

	for ( pNode = m_xMagicList.GetHead(); pNode; )
	{
		pNodeTemp = pNode->GetNext();

		pxMagic = m_xMagicList.RemoveNode(pNode);

		if ( pxMagic )
		{
/*			if ( pxMagic->m_wMagicNum == _SKILL_SHOOTLIGHTEN )
			{
				CElecMagic* pxElecMagic = (CElecMagic*)pxMagic;
				delete((CElecMagic*)pxElecMagic);
				pxElecMagic = NULL;
			}
			else */
			if ( pxMagic->m_wMagicNum == _SKILL_CONCENFIREBALL )
			{
				CConcenFireball* pxCocenFireball = (CConcenFireball*)pxMagic;
				delete((CConcenFireball*)pxCocenFireball);
				pxCocenFireball = NULL;
			}
			else if ( pxMagic->m_wMagicNum == _SKILL_REFINEADD )
			{
				CRefineAdd* pxRefineAdd = (CRefineAdd*)pxMagic;
				delete((CRefineAdd*)pxRefineAdd);
				pxRefineAdd = NULL;
			}
			else
			{
				delete((CMagic*)pxMagic);
				pxMagic = NULL;
			}
		}

		pNode = pNodeTemp;
	}
}


VOID CGameProcess::GroundMagicListClear()
{
	CListNode < CMagic >		*pNode;
	CListNode < CMagic >		*pNodeTemp;
	CMagic*						pxMagic = NULL;

	for ( pNode = m_xGroundMagicList.GetHead(); pNode; )
	{
		pNodeTemp = pNode->GetNext();

		pxMagic = m_xGroundMagicList.RemoveNode(pNode);

		if ( pxMagic )
		{
			if ( pxMagic->m_wMagicNum == _SKILL_HOLYSHIELD || pxMagic->m_wMagicNum == _SKILL_EARTHFIRE ||pxMagic->m_wMagicNum == _SKILL_LIGHTWALL ||
				 pxMagic->m_wMagicNum == _EVENT_LEFTFIRE1 || pxMagic->m_wMagicNum == _EVENT_LEFTFIRE2 || pxMagic->m_wMagicNum == _EVENT_LEFTFIRE3 || 
				 pxMagic->m_wMagicNum == _EVENT_LEFTFIRE4 || pxMagic->m_wMagicNum == _EVENT_LEFTFIRE5 || pxMagic->m_wMagicNum == _SKILL_KANGMAK ||
				 pxMagic->m_wMagicNum == _SKILL_JISOKGYE )
			{
				CRepeatMagic* pxRepeatMagic = (CRepeatMagic*)pxMagic;
				delete((CRepeatMagic*)pxRepeatMagic);
				pxRepeatMagic = NULL;
			}
			else if ( pxMagic->m_wMagicNum == _SKILL_FIRE || pxMagic->m_wMagicNum == _SKILL_ICE || pxMagic->m_wMagicNum == _SKILL_SHOOTLIGHTEN_ADD )
			{
				CMagicStream* pxMagicStream = (CMagicStream*)pxMagic;
				delete((CMagicStream*)pxMagicStream);
				pxMagicStream = NULL;
			}
			else if ( pxMagic->m_wMagicNum == _SKILL_HURRICANE )
			{
				CHurricaneMagic* pxHurricaneMagic = (CHurricaneMagic*)pxMagic;
				delete((CHurricaneMagic*)pxHurricaneMagic);
				pxHurricaneMagic = NULL;
			}
			else if ( pxMagic->m_wMagicNum == _SKILL_HURRICANESHOT || pxMagic->m_wMagicNum == _SKILL_HURRICANEBOMB)
			{
				CHurricaneMagic* pxHurricaneMagic = (CHurricaneMagic*)pxMagic;
				delete((CHurricaneMagic*)pxHurricaneMagic);
				pxHurricaneMagic = NULL;
			}
			else if ( pxMagic->m_wMagicNum == _SKILL_ICEWALL )
			{
				CMiddleRepeateMagic* pxMiddleRepeateMagic = (CMiddleRepeateMagic*)pxMagic;
				delete((CMiddleRepeateMagic*)pxMiddleRepeateMagic);
				pxMiddleRepeateMagic = NULL;
			}
			else
			{
				delete((CMagic*)pxMagic);
				pxMagic = NULL;
			}
		}

		pNode = pNodeTemp;
	}		
}


VOID CGameProcess::ActorListClear()
{
	INT							nActorID;
	CListNode < CActor >		*pNode;
	CListNode < CActor >		*pNodeTemp;
	CActor*						pxActor	= NULL;

	for ( pNode = m_xActorList.GetHead(); pNode; )
	{
		pNodeTemp = pNode->GetNext();

		pxActor = m_xActorList.RemoveNode(pNode);

		if ( pxActor )
		{
			nActorID = pxActor->m_nIdentity;

			// 마법에서 쓰는지를 체크.
			CheckMagicUseActor(pxActor);

			// 패킷을 지운다.
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
					CHero* pxHero = (CHero*)pxActor;
					pxHero->DestroyActor();
					
					delete((CHero*)pxHero);
					pxHero = NULL;
				}
				break;
			case _GENDER_FLAG:
			case _GENDER_NPC:
				{
					CNPC* pxNPC = (CNPC*)pxActor;
					pxNPC->DestroyActor();

					delete((CNPC*)pxNPC);
					pxNPC = NULL;
				}
				break;
			case _GENDER_MON:
				{
					pxActor->DestroyActor();

					delete(pxActor);
					pxActor = NULL;
				}
				break;
			}
		}

		pNode = pNodeTemp;
	}					
}


BOOL CGameProcess::ShowMonExplain(INT nIdx, INT nX, INT nY)
{	
#ifdef _NEWINTERFACE
	if ( m_pxExplainActor == NULL || m_bViewMonInfo == FALSE )
	{
		return FALSE;
	}

	CHAR			pszDivided[MAX_PATH*2];
	INT				nLineCnt;
	D3DMATERIAL7	mtrl;
	RECT			rcFrame;
	INT				nIconImgIndex = -1;

	SetRect(&rcFrame, nX, nY, nX+105, nY+215);
	D3DVECTOR	vecTrans((FLOAT)nX, (FLOAT)nY, 0);
	D3DVECTOR	vecScale((FLOAT)(rcFrame.right-rcFrame.left), (FLOAT)(rcFrame.bottom-rcFrame.top), 1);
	D3DUtil_InitMaterial(mtrl, (FLOAT)50/255.0f, (FLOAT)50/255.0f, (FLOAT)50/255.0f);
	mtrl.diffuse.a = 100.0f/255.0f;
	g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
	g_xMainWnd.DrawWithGDI(&rcFrame, NULL, RGB(120, 120, 120), 1);

	INT nSX, nSY;

	if (m_xImage.m_xImageList[_IMAGE_MONSMALL].NewSetIndex(nIdx))
	{
		SetRect(&rcFrame, nX+10, nY+7, nX + 94, nY + 103);

		nSX = rcFrame.left + (rcFrame.right - rcFrame.left)/2 - m_xImage.m_xImageList[_IMAGE_MONSMALL].m_lpstNewCurrWilImageInfo->shWidth/2 + 1;
		nSY = rcFrame.top + (rcFrame.bottom - rcFrame.top)/2 - m_xImage.m_xImageList[_IMAGE_MONSMALL].m_lpstNewCurrWilImageInfo->shHeight/2;

		g_xMainWnd.DrawWithImageForComp(nSX, nSY, m_xImage.m_xImageList[_IMAGE_MONSMALL].m_lpstNewCurrWilImageInfo->shWidth, 
										m_xImage.m_xImageList[_IMAGE_MONSMALL].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)m_xImage.m_xImageList[_IMAGE_MONSMALL].m_pbCurrImage);

		g_xMainWnd.DrawWithGDI(&rcFrame, NULL, RGB(140, 140, 140), 1);
	}


	if (m_pxExplainActor->m_stMonType.nDead == 1)
		nIconImgIndex = 635;
	else
		nIconImgIndex = 634;

 	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].NewSetIndex(nIconImgIndex) )
	{
 		g_xMainWnd.DrawWithImageForComp(
						nX + 74,nY + 82,
						g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shWidth,					
						g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shHeight,
						(WORD*)g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_pbCurrImage);
	}


	SetRect(&rcFrame, nX, nY + 105, nX + 100, nY + 119);
	if (m_pxExplainActor->m_stMonType.nDead == 1)
		sprintf(pszDivided, "%s", m_pxExplainActor->m_szName);
	else
		sprintf(pszDivided, "%s", m_pxExplainActor->m_szName);
		
	g_xMainWnd.PutsHan(NULL, rcFrame, m_pxExplainActor->m_dwNameClr, RGB(0, 0, 0), pszDivided);

	FLOAT fHPPercent = (FLOAT)((FLOAT)m_pxExplainActor->m_bHPPercent/100);
	SetRect(&rcFrame, 0, 0, (INT)(84*fHPPercent), 6);

 	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].NewSetIndex(660) )
	{
 		g_xMainWnd.DrawWithImageForComp(
						nX + 10, nY + 120,
						g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shWidth,					
						g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shHeight,
						(WORD*)g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_pbCurrImage);
	}
	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].NewSetIndex(661) )
	{
 		g_xMainWnd.DrawWithImageForComp(
						nX + 11, nY + 121,
						&rcFrame,
						(WORD*)g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_pbCurrImage);
	}

	nSX = 8;
	nSY = 122;

	if ( m_pxExplainActor->m_stMonType.stMonStats.szSpeed != -1 && 
		 m_pxExplainActor->m_stMonType.nDead != -1 && 
		 m_pxExplainActor->m_stMonType.nTaiming != -1 )
	{
		nSY += 8;

		if (m_pxExplainActor->m_stMonType.nTaiming == 0)
			nIconImgIndex = 632;
		else
			nIconImgIndex = 631;

		if (m_xImage.m_xImageList[_IMAGE_PROGUSE].NewSetIndex(nIconImgIndex))
		{
			g_xMainWnd.DrawWithImageForComp(nSX, nSY, m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shWidth, 
											m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD *)m_xImage.m_xImageList[_IMAGE_PROGUSE].m_pbCurrImage);
		}

		if (m_pxExplainActor->m_stMonType.stMonStats.szMcType != 0)
		{
			nIconImgIndex = 599 + m_pxExplainActor->m_stMonType.stMonStats.szMcType;
			nSX += 21;
			if (m_xImage.m_xImageList[_IMAGE_PROGUSE].NewSetIndex(nIconImgIndex))
			{
				g_xMainWnd.DrawWithImageForComp(nSX, nSY, m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shWidth, 
												m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shHeight,
												(WORD *)m_xImage.m_xImageList[_IMAGE_PROGUSE].m_pbCurrImage);
			}
		}

		INT	nIdx = 0;

		if(m_pxExplainActor->m_stMonType.stMonStats.szAc >= 5)
			nIdx = 0;
		else if(m_pxExplainActor->m_stMonType.stMonStats.szAc <= -5)
			nIdx = 10;
		else
			nIdx = abs(m_pxExplainActor->m_stMonType.stMonStats.szAc - 5);

		CHAR		szTemp[MAX_PATH];

		nSX += 21;
		nIconImgIndex = 620+m_pxExplainActor->m_stMonType.stMonStats.szSpeed;
		if (m_xImage.m_xImageList[_IMAGE_PROGUSE].NewSetIndex(nIconImgIndex))
		{
			g_xMainWnd.DrawWithImageForComp(nSX, nSY, m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shWidth, 
											m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD *)m_xImage.m_xImageList[_IMAGE_PROGUSE].m_pbCurrImage);
		}

		nSX += 21;
		if (m_xImage.m_xImageList[_IMAGE_PROGUSE].NewSetIndex(630))
		{
			g_xMainWnd.DrawWithImageForComp(nSX, nSY, m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shWidth, 
											m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD *)m_xImage.m_xImageList[_IMAGE_PROGUSE].m_pbCurrImage);
		}

		sprintf(szTemp, "%d%", 10 - nIdx);
		g_xMainWnd.PutsHan(NULL, nSX+22, nSY+5, RGB(230, 230, 230), RGB(0, 0, 0), szTemp);

		nSX = 8;

		for (int nI=0; nI<7; nI++)
		{
/*			if(m_pxExplainActor->m_stMonType.stMonStats.szMac[nI] >= 5)
				nIdx = 0;
			else if(m_pxExplainActor->m_stMonType.stMonStats.szMac[nI] <= -5)
				nIdx = 10;
			else
				nIdx = abs(m_pxExplainActor->m_stMonType.stMonStats.szMac[nI] - 5);
*/

			if (m_pxExplainActor->m_stMonType.stMonStats.szMac[nI] >= 0)
				sprintf(szTemp, " +%d%", m_pxExplainActor->m_stMonType.stMonStats.szMac[nI]);
			else
				sprintf(szTemp, " %d%", m_pxExplainActor->m_stMonType.stMonStats.szMac[nI]);

			if ( (nI%3) == 0 )
				nSY += 20;
			else if ( (nI%3) == 1 )
				nSX += 32;
			else
				nSX += 32;

			if (m_xImage.m_xImageList[_IMAGE_PROGUSE].NewSetIndex(610+nI))
			{
				g_xMainWnd.DrawWithImageForComp(nSX, nSY, m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shWidth, 
												m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shHeight,
												(WORD *)m_xImage.m_xImageList[_IMAGE_PROGUSE].m_pbCurrImage);
			}
			g_xMainWnd.PutsHan(NULL, nSX+15, nSY+5, RGB(230, 230, 230), RGB(0, 0, 0), szTemp);
			if ( (nI%3) == 2 )
				nSX -= 64;
		}
#else //_NEWINTERFACE
	if ( m_pxExplainActor == NULL || m_bViewMonInfo == FALSE )
	{
		return FALSE;
	}

	CHAR			pszDivided[MAX_PATH*2];
	INT				nLineCnt;
	D3DMATERIAL7	mtrl;
	RECT			rcFrame;
	INT				nIconImgIndex = -1;

	SetRect(&rcFrame, nX, nY, nX+130, nY+283);
	D3DVECTOR	vecTrans((FLOAT)nX, (FLOAT)nY, 0);
	D3DVECTOR	vecScale((FLOAT)(rcFrame.right-rcFrame.left), (FLOAT)(rcFrame.bottom-rcFrame.top), 1);
	D3DUtil_InitMaterial(mtrl, (FLOAT)50/255.0f, (FLOAT)50/255.0f, (FLOAT)50/255.0f);
	mtrl.diffuse.a = 100.0f/255.0f;
	g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
	g_xMainWnd.DrawWithGDI(&rcFrame, NULL, RGB(120, 120, 120), 1);

	INT nSX, nSY;

	if (m_xImage.m_xImageList[_IMAGE_MONSMALL].NewSetIndex(nIdx))
	{
		SetRect(&rcFrame, nX + 8, nY + 5, nX + 120, nY + 115);

		nSX = rcFrame.left + (rcFrame.right - rcFrame.left)/2 - m_xImage.m_xImageList[_IMAGE_MONSMALL].m_lpstNewCurrWilImageInfo->shWidth/2 + 1;
		nSY = rcFrame.top + (rcFrame.bottom - rcFrame.top)/2 - m_xImage.m_xImageList[_IMAGE_MONSMALL].m_lpstNewCurrWilImageInfo->shHeight/2;

		g_xMainWnd.DrawWithImageForComp(nSX, nSY, m_xImage.m_xImageList[_IMAGE_MONSMALL].m_lpstNewCurrWilImageInfo->shWidth, 
										m_xImage.m_xImageList[_IMAGE_MONSMALL].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)m_xImage.m_xImageList[_IMAGE_MONSMALL].m_pbCurrImage);

		g_xMainWnd.DrawWithGDI(&rcFrame, NULL, RGB(140, 140, 140), 1);
	}


	if (m_pxExplainActor->m_stMonType.nDead == 1)
	{
		SetRect(&rcFrame, nX + 90, nY + 85, nX + 120, nY + 134);
		sprintf(pszDivided, g_xMsg.GetMsg(1403));
	}
	else
	{
		SetRect(&rcFrame, nX + 82, nY + 85, nX + 120, nY + 134);
		sprintf(pszDivided, g_xMsg.GetMsg(1404));
	}

	g_xMainWnd.PutsHan(NULL, rcFrame, m_pxExplainActor->m_dwNameClr, RGB(0, 0, 0), pszDivided);

	SetRect(&rcFrame, nX + 8, nY + 120, nX + 128, nY + 134);
	if (m_pxExplainActor->m_stMonType.nDead == 1)
		sprintf(pszDivided, "%s", m_pxExplainActor->m_szName);
	else
		sprintf(pszDivided, "%s", m_pxExplainActor->m_szName);
		
	g_xMainWnd.PutsHan(NULL, rcFrame, m_pxExplainActor->m_dwNameClr, RGB(0, 0, 0), pszDivided);

	FLOAT fHPPercent = (FLOAT)((FLOAT)m_pxExplainActor->m_bHPPercent/100);
	SetRect(&rcFrame, 0, 0, (INT)(104*fHPPercent), 6);

 	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].NewSetIndex(4) )
	{
 		g_xMainWnd.DrawWithImageForComp(
						nX + 13, nY + 138,
						g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shWidth,					
						g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shHeight,
						(WORD*)g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_pbCurrImage);
	}
	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].NewSetIndex(5) )
	{
 		g_xMainWnd.DrawWithImageForComp(
						nX + 13, nY + 138,
						&rcFrame,
						(WORD*)g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_pbCurrImage);
	}

	nSX = 13;
	nSY = 138;

	if ( m_pxExplainActor->m_stMonType.stMonStats.szSpeed != -1 && 
		 m_pxExplainActor->m_stMonType.nDead != -1 && 
		 m_pxExplainActor->m_stMonType.nTaiming != -1 )
	{
		nSY += 14;
		g_xMainWnd.PutsHan(NULL, nSX, nSY, RGB(230, 230, 230), RGB(0, 0, 0), g_xMsg.GetMsg(m_pxExplainActor->m_stMonType.nTaiming+5030));
		nSY += 14;
		g_xMainWnd.PutsHan(NULL, nSX, nSY, RGB(230, 230, 230), RGB(0, 0, 0), g_xMsg.GetMsg(m_pxExplainActor->m_stMonType.stMonStats.szMcType+5010));

		INT	nIdx = 0;

		if(m_pxExplainActor->m_stMonType.stMonStats.szAc >= 5)
			nIdx = 0;
		else if(m_pxExplainActor->m_stMonType.stMonStats.szAc <= -5)
			nIdx = 10;
		else
			nIdx = abs(m_pxExplainActor->m_stMonType.stMonStats.szAc - 5);

		CHAR		szTemp[MAX_PATH];

		nSY += 14;
		sprintf(szTemp, "%s : %d%%", g_xMsg.GetMsg(1405), 100 - nIdx*10);
		g_xMainWnd.PutsHan(NULL, nSX, nSY, RGB(230, 230, 230), RGB(0, 0, 0), szTemp);

		sprintf(szTemp, "%s", g_xMsg.GetMsg(1406));
		nSY += 14;
		g_xMainWnd.PutsHan(NULL, nSX, nSY, RGB(230, 230, 230), RGB(0, 0, 0), szTemp);
		
		for (int nI=0; nI<7; nI++)
		{
			if(m_pxExplainActor->m_stMonType.stMonStats.szMac[nI] >= 5)
				nIdx = 0;
			else if(m_pxExplainActor->m_stMonType.stMonStats.szMac[nI] <= -5)
				nIdx = 10;
			else
				nIdx = abs(m_pxExplainActor->m_stMonType.stMonStats.szMac[nI] - 5);

			sprintf(szTemp, "%s:%d%", g_xMsg.GetMsg(nI+5050), 100 - nIdx*10);

			if ( (nI%2) == 0 )
				nSY += 14;
			else
				nSX += 55;

			g_xMainWnd.PutsHan(NULL, nSX, nSY, RGB(230, 230, 230), RGB(0, 0, 0), szTemp);
			if ( (nI%2) != 0 )
				nSX -= 55;
		}

		nSY += 14;
		g_xMainWnd.PutsHan(NULL, nSX, nSY, RGB(230, 230, 230), RGB(0, 0, 0), g_xMsg.GetMsg(5000+m_pxExplainActor->m_stMonType.stMonStats.szSpeed));
#endif //_NEWINTERFACE 
	}

	ZeroMemory(pszDivided, MAX_PATH*2);

	if ( timeGetTime() - m_dwMonShowTick > 800 )
	{
		m_dwMonShowTick = timeGetTime();
		m_pxExplainActor = NULL;
	}

	return TRUE;

}


VOID CGameProcess::SetNextProc()
{
	m_bRender = FALSE;
	DeleteProc();

	g_bProcState = _CHAR_SEL_PROC;
	g_xClientSocket.m_pxDefProc = g_xMainWnd.m_pxDefProcess = &g_xChrSelProc;
	g_xChrSelProc.Load();

	if ( g_execCmds.bFullScreen )
		g_xMainWnd.ResetDXG(640, 480, 16, _DXG_SCREENMODE_FULLSCREEN, _DXG_DEVICEMODE_PRIMARY|_DXG_DEVICEMODE_D3D);
	else
		g_xMainWnd.ResetDXG(640, 480, 16, _DXG_SCREENMODE_WINDOW, _DXG_DEVICEMODE_PRIMARY|_DXG_DEVICEMODE_D3D);
//	CloseLog();
}

 
BOOL CGameProcess::TargetInLongAttack(BYTE bDir)
{
	POINT	ptLongTarget;

	if ( !m_xMap.GetNextTileCanMove(m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, bDir, 2, &ptLongTarget) )
	{
		CActor*					pxActor = NULL;
		CListNode < CActor >	*pNode;

		for ( pNode = m_xActorList.GetHead(); pNode; pNode = pNode->GetNext() )
		{
			pxActor = pNode->GetData();

			if ( pxActor )
			{
				if ( pxActor->m_nPosX == ptLongTarget.x && pxActor->m_nPosY == ptLongTarget.y )
					return TRUE;
			}
		}
	}

	return FALSE;
}


BOOL CGameProcess::CanGameOut()
{
	DWORD dwCurrTick = timeGetTime();
   if ( (dwCurrTick - m_xMyHero.m_dwLastStruckTime  > 8000) &&
		(dwCurrTick - m_xMyHero.m_dwLastMagicTime   > 8000) &&
		(dwCurrTick - m_xMyHero.m_dwLastHitTime		> 8000) || 
		(g_xGameProc.m_xMyHero.m_bCurrMtn == _MT_DIE ) )
   {
		return TRUE;
   }
   else
   {
	   DWORD dwFont, dwBack;

	   dwFont = GetChatColor(2);
	   dwBack = GetChatColor(3);

	   m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(1407));
   }
   return FALSE;
}


// Update?
// by eriastoa 2006.04.06
VOID CGameProcess::CheckMappedData(INT nLoopTime, BOOL bIsMoveTime)
{
	INT		nObjCnt;
	BOOL	bIsSaveTargetExisted = FALSE;
	BOOL	bIsExplainActorExisted = FALSE;
	BOOL	bIsAutoSaveTargetExisted = FALSE;
	BOOL	bIsAutoMagicTargetExisted = FALSE;

	ZeroMemory(m_stMemMappedID, sizeof(MEMMAPPEDID)*_VIEW_CELL_X_COUNT* _VIEW_CELL_Y_COUNT);

	CActor*			pxActor = NULL;
	CActor*			pxDeadTargetActor = NULL;
	CMagic*			pxMagic = NULL;
	LPGROUNDITEM	pstItem = NULL;
	LPEVENTIMG		pstEventImg = NULL;
	
	CListNode < CActor >		*pNode;
	CListNode < CActor >		*pNodeTemp;
	CListNode < CMagic >		*pNodeMagic;
	CListNode < CMagic >		*pNodeMagicTemp;
	CListNode < GROUNDITEM >	*pNodeItem;
	CListNode < GROUNDITEM >	*pNodeItemTemp;
	CListNode < EVENTIMG >		*pNodeEvent;
	CListNode < EVENTIMG >		*pNodeEventTemp;

	RECT rcMyRgn = {m_xMyHero.m_nPosX - 24, m_xMyHero.m_nPosY - 24, m_xMyHero.m_nPosX + 24, m_xMyHero.m_nPosY + 24};

	for ( pNode = m_xActorList.GetHead(); pNode; )
	{
		pxActor = pNode->GetData();

		if ( !pxActor )
		{
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
			}
			break;
		case _GENDER_FLAG:
		case _GENDER_NPC:
			{
				CNPC* pxNPC;
				pxNPC = (CNPC*)pxActor;
				pxNPC->UpdateMotionState(nLoopTime, bIsMoveTime);
			}
			break;
		case _GENDER_MON:
			{
				WORD wDress = pxActor->m_stFeature.bDress;


				pxActor->UpdateMotionState(nLoopTime, bIsMoveTime);

				if ( pxActor->m_bAppearState == _DIG_DOWNDEL )
				{
					CheckMagicUseActor(pxActor);

					pNodeTemp = pNode->GetNext();
					m_xActorList.RemoveNode(pNode);
					pNode = pNodeTemp;

					delete((CActor*)pxActor);
					pxActor = NULL;

					continue;
				}
			}
			break;
		}

		// 현재 내가 있는 위치에서 너무 멀리 떨어져 있는 놈들은 지운다.(서버와 일치해야한다. 안그러면 잔상몹이 생길수 있다. 좌, 우, 위, 아래 12타일이다.)
		POINT ptActorPos = {pxActor->m_nPosX, pxActor->m_nPosY};
		

		//RECT rect = {m_xMyHero.m_nPosX - 12, m_xMyHero.m_nPosY - 12, m_xMyHero.m_nPosX + 12, m_xMyHero.m_nPosY + 12};

		if ( !PtInRect(&rcMyRgn, ptActorPos) )
		{
			switch ( pxActor->m_stFeature.bGender )
			{
			case _GENDER_MAN:
			case _GENDER_WOMAN:
				{
					CheckMagicUseActor(pxActor);

					CHero* pxHero;
					pxHero = (CHero*)pxActor;

					pNodeTemp = pNode->GetNext();
					m_xActorList.RemoveNode(pNode);
					pNode = pNodeTemp;

					delete((CHero*)pxHero);
					pxHero = NULL;

					continue;
				}
				break;
			case _GENDER_FLAG:
			case _GENDER_NPC:
				{
					CheckMagicUseActor(pxActor);

					CNPC* pxNPC;
					pxNPC = (CNPC*)pxActor;

					pNodeTemp = pNode->GetNext();
					m_xActorList.RemoveNode(pNode);
					pNode = pNodeTemp;

					delete((CNPC*)pxNPC);
					pxNPC = NULL;

					continue;
				}
				break;
			case _GENDER_MON:
				{
					CheckMagicUseActor(pxActor);

					pNodeTemp = pNode->GetNext();
					m_xActorList.RemoveNode(pNode);
					pNode = pNodeTemp;

					delete((CActor*)pxActor);
					pxActor = NULL;

					continue;
				}
				break;
			}
		}

		if ( pxActor->m_nPosX >= m_xMap.m_nStartViewTileX && pxActor->m_nPosX < m_xMap.m_nStartViewTileX + _VIEW_CELL_X_COUNT && 
			 pxActor->m_nPosY >= m_xMap.m_nStartViewTileY && pxActor->m_nPosY < m_xMap.m_nStartViewTileY + _VIEW_CELL_Y_COUNT )				 
		{
			//그룹여부를 체크한다.
			pxActor->m_bOpenHealth = FALSE;
			if ( FindGroupPos(pxActor->m_nIdentity) )
			{
//				if ( pxActor->m_stFeature.bGender <= _GENDER_WOMAN )
				{
					pxActor->m_bOpenHealth = TRUE;
				}
			}

			for ( nObjCnt = 0; nObjCnt < _MAX_CELL_OBJ; nObjCnt++ )
			{
				if ( m_stMemMappedID[pxActor->m_nPosY - m_xMap.m_nStartViewTileY][pxActor->m_nPosX - m_xMap.m_nStartViewTileX].pxActor[nObjCnt] == NULL )
				{
					if ( pxActor == m_pxSavedTargetActor )
					{
						bIsSaveTargetExisted = TRUE;
					}
#ifdef _DEBUG
					if ( m_bAutoTarget && pxActor == m_pxAutoSavedTargetActor )
					{
						bIsAutoSaveTargetExisted = TRUE;
					}
#endif
					if ( m_bAutoMagic && pxActor == m_pxAutoSavedMagicActor )
					{
						bIsAutoMagicTargetExisted = TRUE;
					}

					if ( pxActor == m_pxExplainActor )
					{
						bIsExplainActorExisted = TRUE;
					}

					if ( !m_pxMouseTargetActor )
					{
						if ( !pxActor->m_bIsDead )
						{
							if ( PtInRect(&pxActor->m_rcActor, m_ptMousePos) )
							{
								m_pxMouseTargetActor = pxActor;
							}
						}
						else
						{
							if ( PtInRect(&pxActor->m_rcTargetRgn, m_ptMousePos) )
							{
								m_pxMouseTargetActor = pxDeadTargetActor = pxActor;
							}
						}
					}
					else
					{
						if ( PtInRect(&pxActor->m_rcTargetRgn, m_ptMousePos) )
						{
							if ( !pxActor->m_bIsDead )
							{
								m_pxMouseTargetActor = pxActor;
							}
							else
							{
								pxDeadTargetActor = pxActor;
							}
						}
					}	

					// 죽은 Actor는 앞으로 땡긴다.
					if ( pxActor->m_bIsDead )
					{
						CActor* pxTempActor[_MAX_CELL_OBJ];

						pxTempActor[0] = pxActor;
						memcpy(&pxTempActor[1], m_stMemMappedID[pxActor->m_nPosY - m_xMap.m_nStartViewTileY][pxActor->m_nPosX - m_xMap.m_nStartViewTileX].pxActor, sizeof(CActor*)*(_MAX_CELL_OBJ-1));
						memcpy(m_stMemMappedID[pxActor->m_nPosY - m_xMap.m_nStartViewTileY][pxActor->m_nPosX - m_xMap.m_nStartViewTileX].pxActor, pxTempActor, sizeof(CActor*)*(_MAX_CELL_OBJ));
					}
					else
					{
						m_stMemMappedID[pxActor->m_nPosY - m_xMap.m_nStartViewTileY][pxActor->m_nPosX - m_xMap.m_nStartViewTileX].pxActor[nObjCnt] = pxActor;
					}

					break;
				}
			}
		}

		if ( pNode )
		{
			pNode = pNode->GetNext();
		}
	} 

	if ( !bIsSaveTargetExisted )		m_pxSavedTargetActor = NULL;
	if ( !bIsExplainActorExisted )		m_pxExplainActor	 = NULL;
#ifdef _DEBUG
	if ( m_bAutoTarget && !bIsAutoSaveTargetExisted )	m_pxAutoSavedTargetActor = NULL;
#endif
	if ( m_bAutoMagic && !bIsAutoMagicTargetExisted )
	{
		m_pxAutoSavedMagicActor = NULL;		
	}

	if ( !m_pxMouseTargetActor && pxDeadTargetActor )
	{
		m_pxMouseTargetActor = pxDeadTargetActor;
	}

	// Magic Loop
	for ( pNodeMagic = m_xGroundMagicList.GetHead(); pNodeMagic; )
	{
		pxMagic = pNodeMagic->GetData();

		if ( !pxMagic )
		{
			continue;
		}

		if ( pxMagic->m_wMagicNum == _SKILL_HOLYSHIELD || pxMagic->m_wMagicNum == _SKILL_EARTHFIRE || pxMagic->m_wMagicNum == _SKILL_LIGHTWALL ||
			 pxMagic->m_wMagicNum == _EVENT_LEFTFIRE1  || pxMagic->m_wMagicNum == _EVENT_LEFTFIRE2 || pxMagic->m_wMagicNum == _EVENT_LEFTFIRE3 || 
			 pxMagic->m_wMagicNum == _EVENT_LEFTFIRE4  || pxMagic->m_wMagicNum == _EVENT_LEFTFIRE5 || pxMagic->m_wMagicNum == _SKILL_KANGMAK ||
			 pxMagic->m_wMagicNum == _SKILL_JISOKGYE )
		{
			CRepeatMagic* pxRepeatMagic = (CRepeatMagic*)pxMagic;

			// 한타일에 같은 이벤트가 여러개 있는것을 검사.
			pxRepeatMagic->m_bShowLight = TRUE;
			if ( pxRepeatMagic->m_nTargetTileX >= m_xMap.m_nStartViewTileX && pxRepeatMagic->m_nTargetTileX < m_xMap.m_nStartViewTileX  + _VIEW_CELL_X_COUNT && 
				 pxRepeatMagic->m_nTargetTileY >= m_xMap.m_nStartViewTileY && pxRepeatMagic->m_nTargetTileY < m_xMap.m_nStartViewTileY  + _VIEW_CELL_Y_COUNT )
			{
				for ( nObjCnt = 0; nObjCnt < _MAX_CELL_OBJ; nObjCnt++ )
				{
					CMagic* pxMagicCheck = NULL;
					
					if ( m_stMemMappedID[pxRepeatMagic->m_nTargetTileY - m_xMap.m_nStartViewTileY][pxRepeatMagic->m_nTargetTileX - m_xMap.m_nStartViewTileX].pxMagic[nObjCnt] != NULL )
					{
						pxMagicCheck = m_stMemMappedID[pxRepeatMagic->m_nTargetTileY - m_xMap.m_nStartViewTileY][pxRepeatMagic->m_nTargetTileX - m_xMap.m_nStartViewTileX].pxMagic[nObjCnt];

						if ( pxMagicCheck->m_bActiveState == _MAGIC_ACTIVE && pxMagicCheck->m_wMagicNum == pxRepeatMagic->m_wMagicNum && pxMagicCheck->m_nTileX == pxRepeatMagic->m_nTileX && pxMagicCheck->m_nTileY == pxRepeatMagic->m_nTileY )
						{
							pxRepeatMagic->m_bShowLight = FALSE;
							break;
						}
					}
				}
			}

			pxRepeatMagic->UpdateMagic(nLoopTime);

			if ( pxRepeatMagic->m_bActiveState == _MAGIC_FINISH )
			{
				pNodeMagicTemp = pNodeMagic->GetNext();
				m_xGroundMagicList.RemoveNode(pNodeMagic);
				pNodeMagic = pNodeMagicTemp;

				delete((CRepeatMagic*)pxRepeatMagic);
				pxRepeatMagic = NULL;

				continue;
			}
			else
			{
				if ( pxRepeatMagic->m_nTargetTileX >= m_xMap.m_nStartViewTileX && pxRepeatMagic->m_nTargetTileX < m_xMap.m_nStartViewTileX  + _VIEW_CELL_X_COUNT && 
					 pxRepeatMagic->m_nTargetTileY >= m_xMap.m_nStartViewTileY && pxRepeatMagic->m_nTargetTileY < m_xMap.m_nStartViewTileY  + _VIEW_CELL_Y_COUNT )
				{
					if ( pxRepeatMagic->m_bShowLight == FALSE )
					{
						pNodeMagic = pNodeMagic->GetNext();
						continue;
					}

					for ( nObjCnt = 0; nObjCnt < _MAX_CELL_OBJ; nObjCnt++ )
					{
						if ( m_stMemMappedID[pxRepeatMagic->m_nTargetTileY - m_xMap.m_nStartViewTileY][pxRepeatMagic->m_nTargetTileX - m_xMap.m_nStartViewTileX].pxMagic[nObjCnt] == NULL )
						{
							m_stMemMappedID[pxRepeatMagic->m_nTargetTileY - m_xMap.m_nStartViewTileY][pxRepeatMagic->m_nTargetTileX - m_xMap.m_nStartViewTileX].pxMagic[nObjCnt] = pxRepeatMagic;
							break;
						}
					}
				}
			}
		}
		else if ( pxMagic->m_wMagicNum == _SKILL_FIRE || pxMagic->m_wMagicNum == _SKILL_ICE || pxMagic->m_wMagicNum == _SKILL_SHOOTLIGHTEN_ADD )
		{
			CMagicStream* pxMagicStream = (CMagicStream*)pxMagic;

			pxMagicStream->UpdateMagic(nLoopTime);

			if ( pxMagicStream->m_bActiveState == _MAGIC_FINISH )
			{
				pNodeMagicTemp = pNodeMagic->GetNext();
				m_xGroundMagicList.RemoveNode(pNodeMagic);
				pNodeMagic = pNodeMagicTemp;

				delete((CMagicStream*)pxMagicStream);
				pxMagicStream = NULL;

				continue;
			}
			else
			{
				if ( pxMagicStream->m_nTargetTileX >= m_xMap.m_nStartViewTileX && pxMagicStream->m_nTargetTileX < m_xMap.m_nStartViewTileX  + _VIEW_CELL_X_COUNT && 
					 pxMagicStream->m_nTargetTileY >= m_xMap.m_nStartViewTileY && pxMagicStream->m_nTargetTileY < m_xMap.m_nStartViewTileY  + _VIEW_CELL_Y_COUNT )
				{
					for ( nObjCnt = 0; nObjCnt < _MAX_CELL_OBJ; nObjCnt++ )
					{
						if ( m_stMemMappedID[pxMagicStream->m_nTargetTileY - m_xMap.m_nStartViewTileY][pxMagicStream->m_nTargetTileX - m_xMap.m_nStartViewTileX].pxMagic[nObjCnt] == NULL )
						{
							m_stMemMappedID[pxMagicStream->m_nTargetTileY - m_xMap.m_nStartViewTileY][pxMagicStream->m_nTargetTileX - m_xMap.m_nStartViewTileX].pxMagic[nObjCnt] = pxMagicStream;
							break;
						}
					}
				}
			}
		}
		else if ( pxMagic->m_wMagicNum == _SKILL_HURRICANE || pxMagic->m_wMagicNum == _SKILL_HURRICANESHOT || pxMagic->m_wMagicNum == _SKILL_HURRICANEBOMB )
		{
			CHurricaneMagic* pxHurricaneMagic = (CHurricaneMagic*)pxMagic;

			pxHurricaneMagic->UpdateMagic(nLoopTime);

			if ( pxHurricaneMagic->m_bActiveState == _MAGIC_FINISH )
			{
				pNodeMagicTemp = pNodeMagic->GetNext();
				m_xGroundMagicList.RemoveNode(pNodeMagic);
				pNodeMagic = pNodeMagicTemp;

				delete((CHurricaneMagic*)pxHurricaneMagic);
				pxHurricaneMagic = NULL;

				continue;
			}
			else
			{
				if ( pxHurricaneMagic->m_nTargetTileX >= m_xMap.m_nStartViewTileX && pxHurricaneMagic->m_nTargetTileX < m_xMap.m_nStartViewTileX  + _VIEW_CELL_X_COUNT && 
					 pxHurricaneMagic->m_nTargetTileY >= m_xMap.m_nStartViewTileY && pxHurricaneMagic->m_nTargetTileY < m_xMap.m_nStartViewTileY  + _VIEW_CELL_Y_COUNT )
				{
					for ( nObjCnt = 0; nObjCnt < _MAX_CELL_OBJ; nObjCnt++ )
					{
						if ( m_stMemMappedID[pxHurricaneMagic->m_nTargetTileY - m_xMap.m_nStartViewTileY][pxHurricaneMagic->m_nTargetTileX - m_xMap.m_nStartViewTileX].pxMagic[nObjCnt] == NULL )
						{
							m_stMemMappedID[pxHurricaneMagic->m_nTargetTileY - m_xMap.m_nStartViewTileY][pxHurricaneMagic->m_nTargetTileX - m_xMap.m_nStartViewTileX].pxMagic[nObjCnt] = pxHurricaneMagic;
							break;
						}
					}
				}
			}
		}
		else if ( pxMagic->m_wMagicNum == _SKILL_ICEWALL )
		{
			CMiddleRepeateMagic* pxMiddleRepeateMagic = (CMiddleRepeateMagic*)pxMagic;

			pxMiddleRepeateMagic->UpdateMagic(nLoopTime);

			if ( pxMiddleRepeateMagic->m_bActiveState == _MAGIC_FINISH )
			{
				pNodeMagicTemp = pNodeMagic->GetNext();
				m_xGroundMagicList.RemoveNode(pNodeMagic);
				pNodeMagic = pNodeMagicTemp;

				delete((CMiddleRepeateMagic*)pxMiddleRepeateMagic);
				pxMiddleRepeateMagic = NULL;

				continue;
			}
			else
			{
				if ( pxMiddleRepeateMagic->m_nTargetTileX >= m_xMap.m_nStartViewTileX && pxMiddleRepeateMagic->m_nTargetTileX < m_xMap.m_nStartViewTileX  + _VIEW_CELL_X_COUNT && 
					 pxMiddleRepeateMagic->m_nTargetTileY >= m_xMap.m_nStartViewTileY && pxMiddleRepeateMagic->m_nTargetTileY < m_xMap.m_nStartViewTileY  + _VIEW_CELL_Y_COUNT )
				{
					for ( nObjCnt = 0; nObjCnt < _MAX_CELL_OBJ; nObjCnt++ )
					{
						if ( m_stMemMappedID[pxMiddleRepeateMagic->m_nTargetTileY - m_xMap.m_nStartViewTileY][pxMiddleRepeateMagic->m_nTargetTileX - m_xMap.m_nStartViewTileX].pxMagic[nObjCnt] == NULL )
						{
							m_stMemMappedID[pxMiddleRepeateMagic->m_nTargetTileY - m_xMap.m_nStartViewTileY][pxMiddleRepeateMagic->m_nTargetTileX - m_xMap.m_nStartViewTileX].pxMagic[nObjCnt] = pxMiddleRepeateMagic;
							break;
						}
					}
				}
			}
		}
		else
		{
			pxMagic->UpdateMagic(nLoopTime);

			if ( pxMagic->m_bActiveState == _MAGIC_FINISH )
			{
				pNodeMagicTemp = pNodeMagic->GetNext();
				m_xGroundMagicList.RemoveNode(pNodeMagic);
				pNodeMagic = pNodeMagicTemp;

				delete(pxMagic);
				pxMagic = NULL;

				continue;
			}
			else
			{
				if ( pxMagic->m_nTargetTileX >= m_xMap.m_nStartViewTileX && pxMagic->m_nTargetTileX < m_xMap.m_nStartViewTileX  + _VIEW_CELL_X_COUNT && 
					 pxMagic->m_nTargetTileY >= m_xMap.m_nStartViewTileY && pxMagic->m_nTargetTileY < m_xMap.m_nStartViewTileY  + _VIEW_CELL_Y_COUNT )
				{
					for ( nObjCnt = 0; nObjCnt < _MAX_CELL_OBJ; nObjCnt++ )
					{
						if ( m_stMemMappedID[pxMagic->m_nTargetTileY - m_xMap.m_nStartViewTileY][pxMagic->m_nTargetTileX - m_xMap.m_nStartViewTileX].pxMagic[nObjCnt] == NULL )
						{
							m_stMemMappedID[pxMagic->m_nTargetTileY - m_xMap.m_nStartViewTileY][pxMagic->m_nTargetTileX - m_xMap.m_nStartViewTileX].pxMagic[nObjCnt] = pxMagic;
							break;
						}
					}
				}
			}
		}

		pNodeMagic = pNodeMagic->GetNext();
	}		
	
	// Item Loop
	for ( pNodeItem = m_stMapItemList.GetHead(); pNodeItem; )
	{
		pstItem = pNodeItem->GetData();

		if ( pstItem )
		{
			// 현재 내가 있는 위치에서 너무 멀리 떨어져 있는 놈들은 지운다.(서버와 일치해야한다. 안그러면 잔상몹이 생길수 있다. 좌, 우, 위, 아래 12타일이다.)
			POINT ptItemPos = {pstItem->nTileX, pstItem->nTileY};
			if ( !PtInRect(&rcMyRgn, ptItemPos) )
			{
				pNodeItemTemp = pNodeItem->GetNext();
				m_stMapItemList.RemoveNode(pNodeItem);
				pNodeItem = pNodeItemTemp;

				SAFE_DELETE(pstItem);
				continue;
			}

			if ( pstItem->nTileX >= m_xMap.m_nStartViewTileX && pstItem->nTileX < m_xMap.m_nStartViewTileX  + _VIEW_CELL_X_COUNT && 
				 pstItem->nTileY >= m_xMap.m_nStartViewTileY && pstItem->nTileY < m_xMap.m_nStartViewTileY  + _VIEW_CELL_Y_COUNT )
			{
				for ( nObjCnt = 0; nObjCnt < _MAX_CELL_OBJ; nObjCnt++ )
				{
					if ( m_stMemMappedID[pstItem->nTileY - m_xMap.m_nStartViewTileY][pstItem->nTileX - m_xMap.m_nStartViewTileX].pstItem[nObjCnt] == NULL )
					{
						m_stMemMappedID[pstItem->nTileY - m_xMap.m_nStartViewTileY][pstItem->nTileX - m_xMap.m_nStartViewTileX].pstItem[nObjCnt] = pstItem;
						break;
					}
				}
			}
		}

		if ( pNodeItem )
		{
			pNodeItem = pNodeItem->GetNext();
		}
	}

	// Event Loop
	for ( pNodeEvent = m_stEventImgList.GetHead(); pNodeEvent; )
	{
		pstEventImg = pNodeEvent->GetData();

		if ( pstEventImg )
		{
			if ( timeGetTime() - pstEventImg->dwTick > pstEventImg->dwLifeTime )
			{
				pNodeEventTemp = pNodeEvent->GetNext();
				m_stEventImgList.RemoveNode(pNodeEvent);
				pNodeEvent = pNodeEventTemp;

				delete((LPEVENTIMG)pstEventImg);
				pstEventImg = NULL;

				continue;
			}
			else
			{
				if ( pstEventImg->nTileX >= m_xMap.m_nStartViewTileX && pstEventImg->nTileX < m_xMap.m_nStartViewTileX  + _VIEW_CELL_X_COUNT && 
					 pstEventImg->nTileY >= m_xMap.m_nStartViewTileY && pstEventImg->nTileY < m_xMap.m_nStartViewTileY  + _VIEW_CELL_Y_COUNT )
				{
					for ( nObjCnt = 0; nObjCnt < _MAX_CELL_OBJ; nObjCnt++ )
					{
						if ( m_stMemMappedID[pstEventImg->nTileY - m_xMap.m_nStartViewTileY][pstEventImg->nTileX - m_xMap.m_nStartViewTileX].pstEvent[nObjCnt] == NULL )
						{
							m_stMemMappedID[pstEventImg->nTileY - m_xMap.m_nStartViewTileY][pstEventImg->nTileX - m_xMap.m_nStartViewTileX].pstEvent[nObjCnt] = pstEventImg;
							break;
						}
					}
				}
			}
		}

		if ( pNodeEvent )
		{
			pNodeEvent = pNodeEvent->GetNext();
		}
	}
}


VOID CGameProcess::AutoTargeting()
{
	if ( !m_xMyHero.m_bMotionLock && !m_xMyHero.m_bInputLock )
	{
		INT nLeftMsgCnt = m_xMyHero.m_xPacketQueue.GetCount();
		if ( nLeftMsgCnt > 0 )
		{
			if ( m_xMyHero.m_stFeatureEx.bHorse == _HORSE_NONE )	m_xMyHero.SetMotionState(_MT_STAND,      m_xMyHero.m_bCurrDir);
			else													m_xMyHero.SetMotionState(_MT_HORSESTAND, m_xMyHero.m_bCurrDir);
			m_xMyHero.UpdatePacketState();
		}

		POINT ptTargetTile;

//----------------------------------------------------------------------------------------------------------------------------------
		if ( !m_xMap.GetNextTileCanMove(m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, m_xMyHero.m_bCurrDir, 1, &ptTargetTile) )
		{
			if ( m_xMyHero.m_stFeature.bWeapon == 7 && m_xMyHero.m_bAutoDig )	// 곡괭이.
			{
				m_xMyHero.SetMotionState(_MT_ONEHSWING, m_xMyHero.m_bCurrDir, -1, FALSE, &ptTargetTile);
			}
		}
//----------------------------------------------------------------------------------------------------------------------------------

		if ( m_pxSavedTargetActor == NULL )
		{
			return;
		}

		if ( m_pxSavedTargetActor->m_bIsDead )
		{
			return;
		}

		// 표창공격.
		if ( m_xMyHero.m_stFeature.bWeapon == 34 )
		{
			m_pxSavedTargetActor = NULL;
			return;
		}

		// 경비병도 안때리게.
		BOOL bIsGuard = FALSE;
		BYTE bDress   = m_pxSavedTargetActor->m_stFeature.bDress;

		if ( bDress ==  86 || bDress == 113 || bDress == 114 || 
			 bDress == 115 || bDress == 165 || bDress == 166 || bDress == 26)
		{
			bIsGuard = TRUE;
		}

		if ( m_pxSavedTargetActor->m_stFeature.bGender == _GENDER_MAN || m_pxSavedTargetActor->m_stFeature.bGender == _GENDER_WOMAN ||
		    (m_pxSavedTargetActor->m_stFeature.bGender == _GENDER_MON && bIsGuard) ||
			 strchr(m_pxSavedTargetActor->m_szName, '(') )
		{
			// 채팅입력창에 포커스가 있으면 공격안한다.
			if ( !HIBYTE(GetKeyState(VK_SHIFT)) || (GetFocus() != g_xMainWnd.GetSafehWnd()) )
			{
				if ( m_pxSavedTargetActor->m_dwNameClr != RGB(255, 0, 0) && m_pxSavedTargetActor->m_dwNameClr != RGB(239, 107, 0) )
				{
					return;
				}				
			}
		}

		if ( (m_pxSavedTargetActor->m_stFeature.bGender == _GENDER_MON && m_pxSavedTargetActor->m_bCurrMtn == _MT_MON_DIE) ||
			 (m_pxSavedTargetActor->m_stFeature.bGender <= _GENDER_WOMAN && m_pxSavedTargetActor->m_bCurrMtn == _MT_DIE) )
		{
			 return;
		}

		BYTE bDir = m_xMap.GetNextDirection(m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, m_pxSavedTargetActor->m_nPosX, m_pxSavedTargetActor->m_nPosY);

/*		// 길찾기 추가.(AddSuccesor()함수.???)
		if ( m_xMap.PathFinding(m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, m_pxSavedTargetActor->m_nPosX, m_pxSavedTargetActor->m_nPosY) )
		{
			POINT ptArround[8] = { {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1} };
			INT nDestX, nDestY;
			for ( INT nCnt = 0; nCnt < 8; nCnt++ )
			{
				nDestX = m_xMyHero.m_nPosX + ptArround[nCnt].x;
				nDestY = m_xMyHero.m_nPosY + ptArround[nCnt].y;

				if ( nDestX > 0 && nDestY > 0 && nDestX < m_xMap.m_stMapFileHeader.shWidth && nDestY < m_xMap.m_stMapFileHeader.shHeight )
				{
					if ( m_xMap.m_pcPath[nDestX + nDestY*m_xMap.m_stMapFileHeader.shHeight] == PATH )
					{
						bDir = m_xMap.GetNextDirection(m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, nDestX, nDestY);
						break;
					}
				}
			}
		}
		else
		{
			m_pxSavedTargetActor = NULL;
			return;
		}*/

		if ( (INT)(sqrt((double)(m_xMyHero.m_nPosX-m_pxSavedTargetActor->m_nPosX)*(m_xMyHero.m_nPosX-m_pxSavedTargetActor->m_nPosX) + 	(m_xMyHero.m_nPosY-m_pxSavedTargetActor->m_nPosY)*(m_xMyHero.m_nPosY-m_pxSavedTargetActor->m_nPosY)))
			       < 2 )
		{
			if ( m_xMyHero.m_stFeatureEx.bHorse == _HORSE_NONE && !m_pxSavedTargetActor->m_bIsDead )
			{
				// 공격한다.
				ptTargetTile.x = m_xMyHero.m_nPosX;
				ptTargetTile.y = m_xMyHero.m_nPosY;
				m_xMyHero.SetMotionState(_MT_ONEHSWING, bDir, m_pxSavedTargetActor->m_nIdentity, m_pxSavedTargetActor->m_bIsDead, &ptTargetTile);
			}
		}
		// Actor가 있는 방향으로 이동 가능한가?(맵속성체크) 
		else if ( m_xMap.GetNextTileCanMove(m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, bDir, 1, &ptTargetTile) )
		{
			// 1타일 이동한다.
			if ( m_xMyHero.m_stFeatureEx.bHorse == _HORSE_NONE )
			{
				m_xMyHero.SetMotionState(_MT_WALK, bDir, m_pxSavedTargetActor->m_nIdentity, m_pxSavedTargetActor->m_bIsDead, &ptTargetTile);
			}
			else
			{
				m_xMyHero.SetMotionState(_MT_HORSEWALK, bDir, m_pxSavedTargetActor->m_nIdentity, m_pxSavedTargetActor->m_bIsDead, &ptTargetTile);
			}
		}
		// 이동할수 없을때.
		else if ( !m_xMap.GetNextTileCanMove(m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, bDir, 1, &ptTargetTile) )
		{
			const BYTE bDirOrderList[8][2] = 
			{
				{7, 1}, {0, 2}, {1, 3}, {2, 4}, {5, 3}, {6, 4}, {7, 5}, {0, 6},
			};

			for ( INT nCnt = 0; nCnt < 2; nCnt++ )
			{				
				if ( m_xMap.GetNextTileCanMove(m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, bDirOrderList[bDir][nCnt], 1, &ptTargetTile) )
				{
					{
						// 1타일 이동한다.
						if ( m_xMyHero.m_stFeatureEx.bHorse == _HORSE_NONE )
						{
							m_xMyHero.SetMotionState(_MT_WALK, bDirOrderList[bDir][nCnt], m_pxSavedTargetActor->m_nIdentity, m_pxSavedTargetActor->m_bIsDead, &ptTargetTile);
						}
						else
						{
							m_xMyHero.SetMotionState(_MT_HORSEWALK, bDirOrderList[bDir][nCnt], m_pxSavedTargetActor->m_nIdentity, m_pxSavedTargetActor->m_bIsDead, &ptTargetTile);
						}

						return;
					}
				}
			}

			if ( m_xMyHero.m_stFeatureEx.bHorse == _HORSE_NONE )
			{
				m_xMyHero.SetMotionState(_MT_STAND, bDir);
			}
			else
			{
				m_xMyHero.SetMotionState(_MT_HORSESTAND, bDir);
			}
		}
		else
		{
			if ( m_xMyHero.m_stFeatureEx.bHorse == _HORSE_NONE )
			{
				m_xMyHero.SetMotionState(_MT_STAND, bDir);
			}
			else
			{
				m_xMyHero.SetMotionState(_MT_HORSESTAND, bDir);
			}
		}
	}
}


VOID CGameProcess::AutoRunTargeting()
{
	if ( !m_xMyHero.m_bMotionLock && !m_xMyHero.m_bInputLock )
	{
		INT nLeftMsgCnt = m_xMyHero.m_xPacketQueue.GetCount();
		if ( nLeftMsgCnt > 0 )
		{
			if ( m_xMyHero.m_stFeatureEx.bHorse == _HORSE_NONE )	m_xMyHero.SetMotionState(_MT_STAND,      m_xMyHero.m_bCurrDir);
			else													m_xMyHero.SetMotionState(_MT_HORSESTAND, m_xMyHero.m_bCurrDir);
			m_xMyHero.UpdatePacketState();
			return;
		}

		POINT ptTargetTile;

//----------------------------------------------------------------------------------------------------------------------------------
		if ( !m_xMap.GetNextTileCanMove(m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, m_xMyHero.m_bCurrDir, 1, &ptTargetTile) )
		{
			if ( m_xMyHero.m_stFeature.bWeapon == 7 && m_xMyHero.m_bAutoDig )	// 곡괭이.
			{
				m_xMyHero.SetMotionState(_MT_ONEHSWING, m_xMyHero.m_bCurrDir, -1, FALSE, &ptTargetTile);
			}
		}
//----------------------------------------------------------------------------------------------------------------------------------

		if ( m_pxSavedTargetActor == NULL )
		{
			return;
		}

		if ( m_pxSavedTargetActor->m_bIsDead )
		{
			return;
		}

		// 경비병도 안때리게.
		BOOL bIsGuard = FALSE;
		BYTE bDress   = m_pxSavedTargetActor->m_stFeature.bDress;

		if ( bDress ==  26 || bDress ==  86 || bDress == 113 || bDress == 114 || 
			 bDress == 115 || bDress == 165 || bDress == 166 || bDress == 26 )
		{
			bIsGuard = TRUE;
		}

		if ( m_pxSavedTargetActor->m_stFeature.bGender == _GENDER_MAN || m_pxSavedTargetActor->m_stFeature.bGender == _GENDER_WOMAN ||
		    (m_pxSavedTargetActor->m_stFeature.bGender == _GENDER_MON && bIsGuard) ||
			 strchr(m_pxSavedTargetActor->m_szName, '(') )
		{
			if ( !HIBYTE(GetKeyState(VK_SHIFT)) && (GetFocus() ==g_xMainWnd.GetSafehWnd()) )
			{
				if ( m_pxSavedTargetActor->m_dwNameClr != RGB(255, 0, 0) && m_pxSavedTargetActor->m_dwNameClr != RGB(239, 107, 0) )
				{
					return;
				}				
			}
		}

		if ( (m_pxSavedTargetActor->m_stFeature.bGender == _GENDER_MON && m_pxSavedTargetActor->m_bCurrMtn == _MT_MON_DIE) ||
			 (m_pxSavedTargetActor->m_stFeature.bGender <= _GENDER_WOMAN && m_pxSavedTargetActor->m_bCurrMtn == _MT_DIE) )
		{
			 return;
		}

		BYTE bDir = m_xMap.GetNextDirection(m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, m_pxSavedTargetActor->m_nPosX, m_pxSavedTargetActor->m_nPosY);

		if ( (INT)(sqrt((double)(m_xMyHero.m_nPosX-m_pxSavedTargetActor->m_nPosX)*(m_xMyHero.m_nPosX-m_pxSavedTargetActor->m_nPosX) + 	(m_xMyHero.m_nPosY-m_pxSavedTargetActor->m_nPosY)*(m_xMyHero.m_nPosY-m_pxSavedTargetActor->m_nPosY)))
			       < 2 )
		{
			if ( m_xMyHero.m_stFeatureEx.bHorse == _HORSE_NONE && !m_pxSavedTargetActor->m_bIsDead )
			{
				// 공격한다.
				ptTargetTile.x = m_xMyHero.m_nPosX;
				ptTargetTile.y = m_xMyHero.m_nPosY;
				m_xMyHero.SetMotionState(_MT_ONEHSWING, bDir, m_pxSavedTargetActor->m_nIdentity, m_pxSavedTargetActor->m_bIsDead, &ptTargetTile);
			}
		}
		else
		{
/*			m_xMap.PathFinding(m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, m_pxSavedTargetActor->m_nPosX, m_pxSavedTargetActor->m_nPosY);
			POINT ptArround[8] = { {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1} };
			INT nDestX, nDestY;
			for ( INT nCnt = 0; nCnt < 8; nCnt++ )
			{
				nDestX = m_xMyHero.m_nPosX + ptArround[nCnt].x;
				nDestY = m_xMyHero.m_nPosY + ptArround[nCnt].y;

				if ( nDestX > 0 && nDestY > 0 && nDestX < m_xMap.m_stMapFileHeader.shWidth && nDestY < m_xMap.m_stMapFileHeader.shHeight )
				{
					if ( m_xMap.m_pcPath[nDestX + nDestY*m_xMap.m_stMapFileHeader.shHeight] == PATH )
					{
						bDir = m_xMap.GetNextDirection(m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, nDestX, nDestY);
						break;
					}
				}
			}*/
			
			if ( m_xMyHero.m_stFeatureEx.bHorse != _HORSE_NONE )
			{
				// 목적지타일과의 방향으로 1, 2, 3타일째의 위치에 방해물이 없을때.
				if ( m_xMap.GetNextTileCanMove(m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, bDir, 1, &ptTargetTile) && 
					 m_xMap.GetNextTileCanMove(m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, bDir, 2, &ptTargetTile) &&
					 m_xMap.GetNextTileCanMove(m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, bDir, 3, &ptTargetTile) )
				{
					// 3타일 이동한다.
					m_xMap.GetNextTileCanMove(m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, bDir, 3, &ptTargetTile);
					m_xMyHero.SetMotionState(_MT_HORSERUN, bDir, 0, FALSE, &ptTargetTile);
				}
				// 목적지타일과의 방향으로 1타일째의 위치에 방해물이 없을때.
				else if ( m_xMap.GetNextTileCanMove(m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, bDir, 1, &ptTargetTile) )
				{
					m_xMyHero.SetMotionState(_MT_HORSEWALK, bDir, 0, FALSE, &ptTargetTile);
				}
				// 목적지타일과의 방향으로 1타일째의 위치에 방해물이 있을때.
				else
				{
					BYTE bSelectedDir = (_MAX_DIRECTION+1);
					INT nDistance	  = 0;
					INT nSelectedDistance = 100;
					for ( BYTE bDirCnt = 0; bDirCnt < _MAX_DIRECTION; bDirCnt++ )
					{
						if ( m_xMap.GetNextTileCanMove(m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, bDirCnt, 1, &ptTargetTile) )
						{
							nDistance = (INT)(sqrt((double)(ptTargetTile.x-m_ptCurrTile.x)*(ptTargetTile.x-m_ptCurrTile.x) + 
											  (ptTargetTile.y-m_ptCurrTile.y)*(ptTargetTile.y-m_ptCurrTile.y)));
							if ( nDistance <= nSelectedDistance )
							{
								nSelectedDistance = nDistance;
								bSelectedDir = bDirCnt;
							}
						}
					}
					if ( bSelectedDir != (_MAX_DIRECTION+1) )
					{
						// 1타일 이동한다.
						m_xMap.GetNextTileCanMove(m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, bSelectedDir, 1, &ptTargetTile);
						m_xMyHero.SetMotionState(_MT_HORSEWALK, bSelectedDir, 0, FALSE, &ptTargetTile);
					}
					else
					{
						m_xMyHero.SetMotionState(_MT_HORSESTAND, bSelectedDir);
					}
				}
			}
			// 말을 안타고 있을때.
			else
			{
				// 목적지타일과의 방향으로 1, 2타일째의 위치에 방해물이 없을때.
				if ( m_xMap.GetNextTileCanMove(m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, bDir, 1, &ptTargetTile) && 
					 m_xMap.GetNextTileCanMove(m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, bDir, 2, &ptTargetTile) )
				{
					// 2타일 이동한다.
					m_xMap.GetNextTileCanMove(m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, bDir, 2, &ptTargetTile);
					m_xMyHero.SetMotionState(_MT_RUN, bDir, 0, FALSE, &ptTargetTile);
				}
				// 목적지타일과의 방향으로 1타일째의 위치에 방해물이 없을때.
				else if ( m_xMap.GetNextTileCanMove(m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, bDir, 1, &ptTargetTile) )
				{
					m_xMyHero.SetMotionState(_MT_WALK, bDir, 0, FALSE, &ptTargetTile);
				}
				// 목적지타일과의 방향으로 1타일째의 위치에 방해물이 있을때.
				else
				{
					BYTE bSelectedDir = (_MAX_DIRECTION+1);
					INT nDistance;
					INT nSelectedDistance = 100;
					for ( BYTE bDirCnt = 0; bDirCnt < _MAX_DIRECTION; bDirCnt++ )
					{
						if ( m_xMap.GetNextTileCanMove(m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, bDirCnt, 1, &ptTargetTile) )
						{
							nDistance = (INT)(sqrt((double)(ptTargetTile.x-m_ptCurrTile.x)*(ptTargetTile.x-m_ptCurrTile.x) + 
											  (ptTargetTile.y-m_ptCurrTile.y)*(ptTargetTile.y-m_ptCurrTile.y)));
							if ( nDistance <= nSelectedDistance )
							{
								nSelectedDistance = nDistance;
								bSelectedDir = bDirCnt;
							}
						}
					}
					if ( bSelectedDir != (_MAX_DIRECTION+1) )
					{
						// 1타일 이동한다.
						m_xMap.GetNextTileCanMove(m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, bSelectedDir, 1, &ptTargetTile);
						m_xMyHero.SetMotionState(_MT_WALK, bSelectedDir, 0, FALSE, &ptTargetTile);
					}
					else
					{
						m_xMyHero.SetMotionState(_MT_STAND, bSelectedDir);
					}
				}
			}
		}
	}
}



VOID CGameProcess::ShowAreaState()
{
	INT		nCnt;
	RECT	rcAdd;
	RECT	rcState = { 2, 2, 70, 16 };

	if ( m_nAreaState & 0X04 )
	{
		D3DMATERIAL7 mtrl;
		D3DVECTOR	vecTrans(2, 2, 0);
		D3DVECTOR	vecScale(68, 14, 1);

		D3DUtil_InitMaterial(mtrl, (FLOAT)100/255.0f, (FLOAT)100/255.0f, (FLOAT)100/255.0f);
		mtrl.diffuse.a = 150.0f/255.0f;
		m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);


		SetRect(&rcAdd, rcState.left-1, rcState.top-1, rcState.right-1, rcState.bottom-1);
		g_xMainWnd.PutsHan(NULL, rcAdd, RGB(50, 50, 50), RGB(0, 0, 0), g_xMsg.GetMsg(1408));

		SetRect(&rcAdd, rcState.left-1, rcState.top+1, rcState.right-1, rcState.bottom+1);
		g_xMainWnd.PutsHan(NULL, rcAdd, RGB(50, 50, 50), RGB(0, 0, 0), g_xMsg.GetMsg(1408));

		SetRect(&rcAdd, rcState.left+1, rcState.top-1, rcState.right+1, rcState.bottom-1);
		g_xMainWnd.PutsHan(NULL, rcAdd, RGB(50, 50, 50), RGB(0, 0, 0), g_xMsg.GetMsg(1408));

		SetRect(&rcAdd, rcState.left+1, rcState.top+1, rcState.right+1, rcState.bottom+1);
		g_xMainWnd.PutsHan(NULL, rcAdd, RGB(50, 50, 50), RGB(0, 0, 0), g_xMsg.GetMsg(1408));
		
		g_xMainWnd.PutsHan(NULL, rcState, RGB(250, 200, 150), RGB(0, 0, 0), g_xMsg.GetMsg(1408));
	}

	for ( nCnt = 0; nCnt < 15; nCnt++ )
	{
		if ( m_nAreaState & (0X01 << nCnt) )
		{
			if ( m_xImage.m_xImageList[_IMAGE_PROGUSE].NewSetIndex(150+nCnt) )
			{
				g_xMainWnd.DrawWithImageForComp(
								770,  2, 
								g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shWidth, 
								g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shHeight,
								(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_pbCurrImage));

			}			
		}
	}
}


VOID CGameProcess::DropItemShow()
{
	SIZE			sizeLen;
	LPGROUNDITEM	pstItem = NULL;

	INT nCenterX, nCenterY, nStartX, nStartY;

	INT nYCnt = 0, nXCnt = 0;

	if ( m_bDrawGroundItemName )
	{
		for ( nYCnt = m_xMap.m_nStartViewTileY; nYCnt < m_xMap.m_nStartViewTileY+_VIEW_CELL_Y_COUNT_FOR_OBJ; nYCnt++ )
		{
			for ( nXCnt = m_xMap.m_nStartViewTileX+m_nViewLGapX; nXCnt < m_xMap.m_nStartViewTileX+_VIEW_CELL_X_COUNT+m_nViewRGapX; nXCnt++ )
			{
				INT nMapViewX	   = 0;
				INT nMapViewY	   = 0;
				BOOL bFind = FALSE;

				if ( nXCnt >= m_xMap.m_nStartViewTileX && nXCnt < m_xMap.m_nStartViewTileX + _VIEW_CELL_X_COUNT && nYCnt >= m_xMap.m_nStartViewTileY && nYCnt < m_xMap.m_nStartViewTileY + _VIEW_CELL_Y_COUNT )
				{
					bFind = TRUE;
					nMapViewX = nXCnt - m_xMap.m_nStartViewTileX;
					nMapViewY = nYCnt - m_xMap.m_nStartViewTileY;
				}
		
				for ( INT nObjCnt = 0; nObjCnt < _MAX_CELL_OBJ && bFind ; nObjCnt++ )
				{

					pstItem = m_stMemMappedID[nMapViewY][nMapViewX].pstItem[nObjCnt];

					if ( pstItem )
					{
						nCenterX = (pstItem->nTileX-m_xMap.m_nStartViewTileX)*_CELL_WIDTH +m_xMap.m_nViewPosX-m_xMap.m_nViewOffsetX+_CELL_WIDTH /2;
						nCenterY = (pstItem->nTileY-m_xMap.m_nStartViewTileY)*_CELL_HEIGHT+m_xMap.m_nViewPosY-m_xMap.m_nViewOffsetY+_CELL_HEIGHT/2-20;

						sizeLen	= g_xMainWnd.GetStrLength(NULL, NULL, pstItem->szItemName);

						nStartX = nCenterX-sizeLen.cx/2;
						nStartY = nCenterY - nObjCnt*16;
						
						g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(), nStartX - 1, nStartY + 2, RGB( 0,  0,  0), RGB(0, 0, 0), pstItem->szItemName);
						g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(), nStartX, nStartY + 1, RGB(255, 255, 125), RGB(0, 0, 0), pstItem->szItemName);

					}
				}
			}
		}
	}
	else
	{
		if ( m_ptCurrTile.x >= m_xMap.m_nStartViewTileX && m_ptCurrTile.x < m_xMap.m_nStartViewTileX  + _VIEW_CELL_X_COUNT && 
			 m_ptCurrTile.y >= m_xMap.m_nStartViewTileY && m_ptCurrTile.y < m_xMap.m_nStartViewTileY  + _VIEW_CELL_Y_COUNT )
		{
			INT nPosX = m_ptCurrTile.x - m_xMap.m_nStartViewTileX;
			INT nPosY = m_ptCurrTile.y - m_xMap.m_nStartViewTileY;

			nCenterX = (m_ptCurrTile.x-m_xMap.m_nStartViewTileX)*_CELL_WIDTH +m_xMap.m_nViewPosX-m_xMap.m_nViewOffsetX+_CELL_WIDTH /2;
			nCenterY = (m_ptCurrTile.y-m_xMap.m_nStartViewTileY)*_CELL_HEIGHT+m_xMap.m_nViewPosY-m_xMap.m_nViewOffsetY+_CELL_HEIGHT/2-20;

			for ( INT nObjCnt = 0; nObjCnt < _MAX_CELL_OBJ; nObjCnt++ )
			{
				pstItem = m_stMemMappedID[nPosY][nPosX].pstItem[nObjCnt];

				if ( pstItem )
				{
					sizeLen	= g_xMainWnd.GetStrLength(NULL, NULL, pstItem->szItemName);

					nStartX = nCenterX-sizeLen.cx/2;
					nStartY = nCenterY - nObjCnt*16;

					D3DMATERIAL7 mtrl;
					D3DVECTOR	vecTrans((FLOAT)nStartX, (FLOAT)nStartY, 0);
					D3DVECTOR	vecScale((FLOAT)sizeLen.cx, 15, 1);

					D3DUtil_InitMaterial(mtrl, (FLOAT)80/255.0f, (FLOAT)60/255.0f, (FLOAT)40/255.0f);
					mtrl.diffuse.a = 150.0f/255.0f;
					m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

					// 추석맞이 이벤트용.
					CHAR pszEventItm[20];
					for ( INT nCnt = 0; nCnt < 10; nCnt++ )
					{
						sprintf(pszEventItm, "%s%d", g_xMsg.GetMsg(1409), nCnt);
						if ( !strcmp(pstItem->szItemName, pszEventItm) )
						{
							g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(), nStartX - 1, nStartY + 2, RGB( 0,  0,  0), RGB(0, 0, 0), g_xMsg.GetMsg(1409));
							g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(), nStartX, nStartY + 1, RGB(255, 255, 125), RGB(0, 0, 0), g_xMsg.GetMsg(1409));
							return;
						}
					}

					g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(), nStartX - 1, nStartY + 2, RGB( 0,  0,  0), RGB(0, 0, 0), pstItem->szItemName);
					g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(), nStartX, nStartY + 1, RGB(255, 255, 125), RGB(0, 0, 0), pstItem->szItemName);
				}
				else
				{
					break;
				}
			}
		}
	}
}	


VOID CGameProcess::ProcessRecvPacket()
{
	CStreamBuffer< char > &recvBuf = g_xClientSocket.m_recvBuf;
	if ( recvBuf.Length() )
	{
		char* pNext = OnMessageReceive( recvBuf.Buffer(), recvBuf.Length() );
		
		if ( pNext )
		{
			recvBuf.Remove( pNext - recvBuf );
		}
		else
		{
			recvBuf.ClearAll();
		}
	}
}


VOID CGameProcess::ProcessDelQue()
{
	INT nCnt, nLeftMsgCnt;

	LPPACKETMSG	lpPacketMsg  = NULL;
	nLeftMsgCnt = m_xWaitPacketQueue.GetCount();

	// 쌓여있는 패킷을 지운다.
	if ( nLeftMsgCnt > QUEUE_MAX - 50 )
	{
		for ( nCnt = 0; nCnt < nLeftMsgCnt; nCnt++ )
		{
/*			char szstr[100];
			sprintf(szstr, "%d\n", nCnt);
			FLOG0( "log1.txt", szstr );
*/
			lpPacketMsg = (LPPACKETMSG)m_xWaitPacketQueue.PopQ();
			if ( lpPacketMsg )
			{
				SAFE_DELETE(lpPacketMsg);
			}
		}
	}

	_TDEFAULTMESSAGE* lpstDefMsg = NULL;
	nLeftMsgCnt = m_xWaitDefaultPacketQueue.GetCount();

	// 쌓여있는 패킷을 지운다.
	if ( nLeftMsgCnt > QUEUE_MAX - 50 )
	{
		for ( nCnt = 0; nCnt < nLeftMsgCnt; nCnt++ )
		{
			lpstDefMsg = (_TDEFAULTMESSAGE*)m_xWaitDefaultPacketQueue.PopQ();
			if ( lpstDefMsg )
			{
				SAFE_DELETE(lpstDefMsg);
			}
		}
	}
}


VOID CGameProcess::CheckMagicUseActor(CActor* pxActor)
{
	// Magic List검사.
	CListNode < CMagic >		*pNode;
	CMagic*						pxMagic = NULL;

	for ( pNode = m_xMagicList.GetHead(); pNode; pNode = pNode->GetNext() )
	{
		pxMagic = pNode->GetData();

		if ( pxMagic )
		{
			if ( pxMagic->m_pxOwner == pxActor )
			{
				pxMagic->m_pxOwner = NULL;
			}
			if ( pxMagic->m_pxTarget == pxActor )
			{
				pxMagic->m_pxTarget = NULL;
			}
		}
	}

	for ( pNode = m_xGroundMagicList.GetHead(); pNode; pNode = pNode->GetNext() )
	{
		pxMagic = pNode->GetData();

		if ( pxMagic )
		{
			if ( pxMagic->m_pxOwner == pxActor )
			{
				pxMagic->m_pxOwner = NULL;
			}
			if ( pxMagic->m_pxTarget == pxActor )
			{
				pxMagic->m_pxTarget = NULL;
			}
		}
	}
}


VOID CGameProcess::RenderFadeState(INT nLoopTime)
{
	FLOAT  fRate = 0.0f;
	m_dwFadeTime += nLoopTime;

	// 보통상태.
	if ( m_bFateState == 0 )
	{
		m_dwFadeTime = 0;
		return;
	}
	else if ( m_bFateState == 1 )	// 점점 밝아지는 상태.
	{
		if ( m_dwFadeTime > 2500 )
		{
			m_bFateState = 0;
			m_dwFadeTime   = 0;
			fRate = 0; 
			return;
		}
		else
		{
			fRate = ((FLOAT)m_dwFadeTime/10.0f); 
		}		
	}
	else if ( m_bFateState == 2 )	// 점점 어두워지는 상태.
	{
		if ( m_dwFadeTime > 500 )
			g_xClientSocket.DisconnectToServer();

		if ( m_dwFadeTime > 2500 )
		{
			m_bFateState = 0;
			m_dwFadeTime   = 0;
			fRate = 0;
			SetNextProc();
			return;
		}
		else
		{
			fRate = 255 - ((FLOAT)m_dwFadeTime/10.0f); 
		}		
	}
	D3DMATERIAL7 mtrl;
	D3DVECTOR	vecTrans((FLOAT)0, (FLOAT)0, 0);
	D3DVECTOR	vecScale((FLOAT)800, (FLOAT)600, 0.0f);
	D3DUtil_InitMaterial(mtrl, (FLOAT)fRate/255.0f, (FLOAT)fRate/255.0f, (FLOAT)fRate/255.0f);
	mtrl.diffuse.a = 100.0f/255.0f;
	m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL, 6);
}


VOID CGameProcess::SetDiceMode(LPPACKETMSG lpPacketMsg)
{
	INT nCnt;
	MESSAGEBODYWL	wl;
	fnDecode6BitBuf(lpPacketMsg->szEncodeData, (char*)&wl, sizeof(wl));

	ZeroMemory(&m_pszCmd, sizeof(MAX_PATH));
	INT nPos = fnDecode6BitBuf(lpPacketMsg->szEncodeData+_MESSAGEBODYWLSIZE, m_pszCmd, sizeof(m_pszCmd));
	m_pszCmd[nPos] = '\0';

	INT nResult[_MAX_DICE];

	nResult[0] = LOBYTE(LOWORD(wl.lParam1));
	nResult[1] = HIBYTE(LOWORD(wl.lParam1));
	nResult[2] = LOBYTE(HIWORD(wl.lParam1));
	nResult[3] = HIBYTE(HIWORD(wl.lParam1));


	for ( nCnt = lpPacketMsg->stDefMsg.wParam; nCnt < _MAX_DICE; nCnt++ )
	{
		nResult[nCnt] = 0;
	}

	m_bDiceModeActive		= TRUE;
	m_dwDicePlayTime		= 0;
	m_dwCurrDicePlayTime	= 0;
	ZeroMemory(m_stDiceInfo, sizeof(DICEINFO)*_MAX_DICE); 
	ZeroMemory(&m_rcDiceBoard, sizeof(RECT)); 

	INT nHWidth  = ((lpPacketMsg->stDefMsg.wParam*2)*60)/2;
	INT nHHeight = 60;
	SetRect(&m_rcDiceBoard, 400-nHWidth, 240-nHHeight, 400+nHWidth, 240+nHHeight);

	for ( nCnt = 0; nCnt < lpPacketMsg->stDefMsg.wParam; nCnt++ )
	{
		m_stDiceInfo[nCnt].bSetted	   = TRUE;
		m_stDiceInfo[nCnt].nCurrFrm	   = 150;
		m_stDiceInfo[nCnt].nPlayTime   = GetRandomNum(1500, 2500);
		m_stDiceInfo[nCnt].nCurrDelay  = 0;
		m_stDiceInfo[nCnt].nFrameDelay = GetRandomNum(80, 120);
		m_stDiceInfo[nCnt].nTotalDelay = 0;
		m_stDiceInfo[nCnt].nResult	   = nResult[nCnt];

		m_stDiceInfo[nCnt].nPosX	   = m_rcDiceBoard.left+22+(nCnt*120);
		m_stDiceInfo[nCnt].nPosY	   = m_rcDiceBoard.top+17;


		if ( m_stDiceInfo[nCnt].nPlayTime > m_dwDicePlayTime )
		{
			m_dwDicePlayTime = m_stDiceInfo[nCnt].nPlayTime;
		}
	}

	m_dwDicePlayTime += 2000;
}


VOID CGameProcess::RenderDiceMode(INT nLoopTime)
{
	if ( m_bDiceModeActive )
	{
		m_dwCurrDicePlayTime += nLoopTime;

		if ( m_dwCurrDicePlayTime > m_dwDicePlayTime )
		{
			// 초기화 시킨다.
			m_bDiceModeActive		= FALSE;
			// 잠시동안 입력을 막는다.
			m_dwInputDelayTime	    = 1000;
			m_dwCurrInputDelayTime  = 0;

			m_dwDicePlayTime		= 0;
			m_dwCurrDicePlayTime	= 0;
			ZeroMemory(m_stDiceInfo, sizeof(DICEINFO)*_MAX_DICE); 
			ZeroMemory(&m_rcDiceBoard, sizeof(RECT)); 
			g_xClientSocket.SendNPCMessage(CM_MERCHANTDLGSELECT,(DWORD)m_xInterface.m_xNPCWnd.m_nNpcId, 0, m_pszCmd);
			ZeroMemory(&m_pszCmd, sizeof(MAX_PATH));
		}
		else
		{
			INT			 nCnt;
			D3DMATERIAL7 mtrl;

			// 판때기그리기.
			D3DVECTOR	vecTrans((FLOAT)m_rcDiceBoard.left, (FLOAT)m_rcDiceBoard.top, 0);
			D3DVECTOR	vecScale((FLOAT)(m_rcDiceBoard.right-m_rcDiceBoard.left), (FLOAT)(m_rcDiceBoard.bottom-m_rcDiceBoard.top), 0.0f);
			D3DUtil_InitMaterial(mtrl, (FLOAT)10/255.0f, (FLOAT)10/255.0f, (FLOAT)10/255.0f);
			mtrl.diffuse.a = 100.0f/255.0f;
			m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
			g_xMainWnd.DrawWithGDI(&m_rcDiceBoard, NULL, RGB(80, 80, 80), 1);

			// 주사위 그리기.
			for ( nCnt = 0; nCnt < _MAX_DICE; nCnt++ )
			{
				if ( m_stDiceInfo[nCnt].bSetted )
				{
					m_stDiceInfo[nCnt].nCurrDelay  += nLoopTime;
					m_stDiceInfo[nCnt].nTotalDelay += nLoopTime;

					if ( m_stDiceInfo[nCnt].nTotalDelay > m_stDiceInfo[nCnt].nPlayTime )
					{
						m_stDiceInfo[nCnt].nCurrFrm = 140 + m_stDiceInfo[nCnt].nResult -1;
					}
					else
					{
						if ( m_stDiceInfo[nCnt].nCurrDelay > m_stDiceInfo[nCnt].nFrameDelay )
						{
							m_stDiceInfo[nCnt].nCurrDelay = 0;
							m_stDiceInfo[nCnt].nCurrFrm++;
							if ( m_stDiceInfo[nCnt].nCurrFrm > 153 )
							{
								m_stDiceInfo[nCnt].nCurrFrm = 150;
							}
						}
					}

					CWHWilImageData* pxImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_INVENTORY];
					if ( pxImg && pxImg->NewSetIndex(m_stDiceInfo[nCnt].nCurrFrm) )
					{
						g_xMainWnd.DrawWithImageForCompClipRgn(m_stDiceInfo[nCnt].nPosX, m_stDiceInfo[nCnt].nPosY, 
																pxImg->m_lpstNewCurrWilImageInfo->shWidth,pxImg->m_lpstNewCurrWilImageInfo->shHeight,
															   (WORD*)pxImg->m_pbCurrImage, _CLIP_WIDTH, _CLIP_HEIGHT);
					}
				}
				else
				{
					break;
				}
			}
		}
	}
}

VOID CGameProcess::RenderScene(INT nArgLoopTime)
{
	static DWORD dwReceiveTime	= 0;
	static DWORD dwMoveTime		= 0;

	BOOL bIsMoveTime	= FALSE;
	dwReceiveTime		= 0;

//  Speed Hack관련.	
	INT nLoopTime = nArgLoopTime*m_fHackTickRate;
	if ( nLoopTime < 10 )
	{
		nLoopTime = nArgLoopTime;
	}

//	무공 아이템 동시 사용 관련
	if ( g_dwCurrTime - m_dwSpellTimer > 300 )
		m_bUseSpell = FALSE;

	if ( m_bCreditShow )
	{
		Clear(0);

/*		if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(340))
		{
			g_xMainWnd.DrawWithImageForComp(0, 0, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
		}

*/
		if (m_xImageLogin.NewSetIndex(m_nIdxCreditBack))
		{
			g_xMainWnd.DrawWithImageForComp(0, 0, 
											m_xImageLogin.m_lpstNewCurrWilImageInfo->shWidth, 
											m_xImageLogin.m_lpstNewCurrWilImageInfo->shHeight,
											(WORD *)m_xImageLogin.m_pbCurrImage);
		}

		ShowCredit(nLoopTime);
		return;
	}

	CHAR pszMsg[MAX_PATH];
/*
	m_dwFindHackTime += nLoopTime;
	if ( m_dwFindHackTime > 30000 )
	{
		HWND hWnd = NULL; 

		hWnd = FindWindow( "TfrmNPMON", "WWW.NPROTECT.COM" );

		if (hWnd != NULL)
    		m_dwFindHackTime = 0;
		else
		{
			spintf(pszMsg, "\r\n\r\n%s \r\n%s", g_xMsg.GetMsg(1410), g_xMsg.GetMsg(1411));
			m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GAMEOUT, _OK, pszMsg);
		}
	}
*/
	if ( g_xMainWnd.m_bIsActiveChanged )
	{
/*		if ( g_xMainWnd.GetScreenMode() & _DXG_SCREENMODE_FULLSCREEN )
		{
			g_xGameProc.m_bRender = FALSE;
			g_xMainWnd.m_bIsWindowReady = FALSE;

			if ( FAILED(g_xMainWnd.ResetDXG(800, 600, 16, _DXG_SCREENMODE_FULLSCREEN, _DXG_DEVICEMODE_PRIMARY|_DXG_DEVICEMODE_D3D)) )
			{
				MessageBox(g_xMainWnd.GetSafehWnd(), TEXT("DirectDraw RESETUP failed!!!") TEXT("The Program will now exit."), TEXT("MirDXG"), MB_ICONERROR | MB_OK);
			}

			SetFocus(g_xMainWnd.GetSafehWnd());

			m_xInterface.m_xMiniMap.ResetMiniMap(g_xMainWnd.Get3DDevice());
			m_xImage.DelAllTextrFileList();
			g_xMainWnd.m_bIsWindowReady = TRUE;
			m_bRender = TRUE;
		}
		g_xMainWnd.m_bIsActiveChanged = FALSE;
*/	}

	dwMoveTime			   += nLoopTime;
	m_dwCurrInputDelayTime += nLoopTime;

	if ( m_dwCurrInputDelayTime >= m_dwInputDelayTime )
	{
		m_dwCurrInputDelayTime = 0;
		m_dwInputDelayTime	   = 0;
	}

	if ( dwMoveTime > 95 )
	{
		bIsMoveTime = TRUE;
		dwMoveTime	= 0;
	}

	if ( m_bPlayBGM )
	{
		m_dwMapMoveTime	+= nLoopTime;

		if ( m_dwMapMoveTime > 5000 )
		{
			if ( m_bVerChk == FALSE )
			{
				sprintf(pszMsg, "%s %s", g_xMsg.GetMsg(1412), g_xMsg.GetMsg(1411));
				m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_DIRECT_GAMEOUT, _OK, pszMsg);
			}

			g_SoundManager.SndmngrPlayMp3(m_xMap.m_pszMapName, TRUE, 0);
			Sleep(30);
			m_bPlayBGM = FALSE;
			m_dwMapMoveTime = 0;
		}
	}

	ProcessRecvPacket();
	ProcessDefaultPacket();
	ProcessPacket();

	CWHWilImageData::CheckAllCachedImage();
	m_xImage.m_helper.CheckAllCachedTexture();

	
	// ShowLoading 함수로 만듬 - 코드 정리 차원;;
	// by eriastoa 2006.04.05
	if ( m_bShowLoading ) { ShowLoading(); return; }

	

	if ( m_bRender )
	{
		CMagic*					pxMagic = NULL;
		CListNode < CMagic >	*pNode;
		CListNode < CMagic >	*pNodeTemp;
		CListNode < CActor >	*pNodeActor;

		m_xMap.LoadMemViewBuffer(m_xMyHero.m_nPosX, m_xMyHero.m_nPosY/*, nLoopTime*/);

		m_xLightFog.ClearSavedLightColor();
		m_xMyHero.UpdateMotionState(nLoopTime, bIsMoveTime);

		if ( m_bRunTarget )
		{
			AutoRunTargeting();
		}
		else
		{
			AutoTargeting();
		}

  		if ( m_xMap.m_bUseTileBuffer )
		{
			g_xMainWnd.DrawWithImagePerLineClipRgn(
				m_xMap.m_rcView.left+m_xMap.m_nViewPosX-m_xMap.m_nViewOffsetX,
				m_xMap.m_rcView.top+m_xMap.m_nViewPosY-m_xMap.m_nViewOffsetY,
				m_xMap.m_rcView.right-m_xMap.m_rcView.left,
				m_xMap.m_rcView.bottom-m_xMap.m_rcView.top,
				m_xMap.m_wSavedMapBuffer, _CLIP_WIDTH, _CLIP_HEIGHT);
		}
		else
		{
			Clear(0);
			m_xMap.DrawTile();
		}

		// * 부분 뭔지 몰라서 주석처리 하도록 한다. 실행되자 마자 m_bCheckBigLight = FALSE 세팅된다
		// by eriastoa 2006.03.31

		//if( m_bCheckBigLight ) *
		{
		//	if( g_dwCurrTime - m_dwChkTimerBigLight > 5000 ) *
		//		m_bCheckBigLight = FALSE; *


			if ( m_xInterface.m_xStatusWnd.m_stEquipItem[_U_RIGHTHAND].bSetted &&  strcmp( m_xInterface.m_xStatusWnd.m_stEquipItem[_U_RIGHTHAND].xItem.m_stItemInfo.stStdItem.szName, "견혼령" ) == 0 )
			{
				DWORD	dwFogColor;
				FLOAT	fDstDarkRate = 0.0f;

				fDstDarkRate = 255.0f;
				dwFogColor = RGB(fDstDarkRate, fDstDarkRate, fDstDarkRate);
				m_xLightFog.ChangeLightColor(dwFogColor);
			}
		}
		
#ifdef _DEBUG
		if ( !m_xMyHero.m_bIsDead )
		{
			m_xInterface.m_xUtilWnd.ProcessUtilFunc();
			m_xInterface.m_xUtilWnd.UseHPPotion();
			m_xInterface.m_xUtilWnd.UseMPPotion();
		}
#endif
		m_pxMouseTargetActor = NULL;

		CheckMappedData(nLoopTime, bIsMoveTime);

		RenderObject(nLoopTime);

#ifdef _DEBUG
		RenderMapTileGrid();
#endif
/*
		if ( m_xInterface.m_xStatusWnd.m_stEquipItem[_U_RIGHTHAND].bSetted &&  strcmp( m_xInterface.m_xStatusWnd.m_stEquipItem[_U_RIGHTHAND].xItem.m_stItemInfo.stStdItem.szName, "견혼령" ) == 0 )
		{
			DWORD	dwFogColor;
			FLOAT	fDstDarkRate = 0.0f;

			fDstDarkRate = 255.0f;
			dwFogColor = RGB(fDstDarkRate, fDstDarkRate, fDstDarkRate);
			m_xLightFog.ChangeLightColor(dwFogColor);
		}
		else
		{
			DWORD	dwFogColor = RGB(10, 10, 10);
			FLOAT	fDstDarkRate = 0.0f;

			switch ( m_bFogState )
			{
			case _FOGSTATE_DAY:
				{
					dwFogColor = RGB(255, 255, 255);
					break;
				}
			case _FOGSTATE_NIGHT:
				{
					dwFogColor = RGB(15, 15, 15);
					break;
				}
			case _FOGSTATE_DAWN:
				{
					dwFogColor = RGB(85, 85, 85);
					break;
				}
			}
			m_xLightFog.ChangeLightColor(dwFogColor);
//			m_xMyHero.m_bLightSize = (BYTE)(lpPacketMsg->stDefMsg.wParam);
		}
*/
		
		// 마법 업데이트
		for ( pNode = m_xMagicList.GetHead(); pNode; )
		{
			pNodeTemp = pNode->GetNext();

			pxMagic = pNode->GetData();

			if ( pxMagic )
			{
/*				if ( pxMagic->m_wMagicNum == _SKILL_SHOOTLIGHTEN )
				{
					CElecMagic* pxElecMagic = (CElecMagic*)pxMagic;

					pxElecMagic->UpdateMagic(nLoopTime);

					if ( pxElecMagic->m_bActiveState == _MAGIC_FINISH )
					{
						m_xMagicList.RemoveNode(pNode);

						delete((CElecMagic*)pxElecMagic);
						pxElecMagic = NULL;
					}
				}
				else */
				if ( pxMagic->m_wMagicNum == _SKILL_CONCENFIREBALL )
				{
					CConcenFireball* pxCocenFireball = (CConcenFireball*)pxMagic;

					pxCocenFireball->UpdateMagic(nLoopTime);

					if ( pxCocenFireball->m_bActiveState == _MAGIC_FINISH )
					{
						m_xMagicList.RemoveNode(pNode);

						delete((CConcenFireball*)pxCocenFireball);
						pxCocenFireball = NULL;
					}
				}
				else if ( pxMagic->m_wMagicNum == _SKILL_REFINEADD )
				{
					CRefineAdd* pxRefineAdd = (CRefineAdd*)pxMagic;

					pxRefineAdd->UpdateMagic(nLoopTime);

					if ( pxRefineAdd->m_bActiveState == _MAGIC_FINISH )
					{
						m_xMagicList.RemoveNode(pNode);

						delete((CRefineAdd*)pxRefineAdd);
						pxRefineAdd = NULL;
					}
				}
				else
				{
					pxMagic->UpdateMagic(nLoopTime);

					if ( pxMagic->m_bActiveState == _MAGIC_FINISH )
					{
						m_xMagicList.RemoveNode(pNode);

						delete((CMagic*)pxMagic);
						pxMagic = NULL;
					}
				}
			}

			pNode = pNodeTemp; 
		}

		if ( m_bSnowOn && m_bShowMist )
		{
			m_xMist.ProgressMist();
		}

		if ( m_bSnowOn && m_bShowSnow )
		{
			m_xSnow.UpdateSystem(nLoopTime);
			m_xSnow.RenderSystem(g_xMainWnd.Get3DDevice());
		}

		if ( m_bShowRain )			
		{
			m_xRain.UpdateSystem(nLoopTime);
			m_xRain.RenderSystem(g_xMainWnd.Get3DDevice());
		}

		m_xScatter.UpdateSystem(nLoopTime);
		m_xScatter.RenderSystem(g_xMainWnd.Get3DDevice());

		m_xFlyingTail.UpdateSystem(nLoopTime);
		m_xFlyingTail.RenderSystem(g_xMainWnd.Get3DDevice());

		m_xSmoke.UpdateSystem(nLoopTime);
		m_xSmoke.RenderSystem(g_xMainWnd.Get3DDevice());		

		m_xBoom.UpdateSystem(nLoopTime);
		m_xBoom.RenderSystem(g_xMainWnd.Get3DDevice());

		m_xMyHero.DrawEffect();
		m_xMyHero.ShowMessage(nLoopTime);
		m_xMyHero.DrawHPBar();
		m_xMyHero.DrawHPNum();

		CActor*					pxActor;

		// 유저 그리기
		for ( pNodeActor = m_xActorList.GetHead(); pNodeActor; pNodeActor = pNodeActor->GetNext() )
		{
			pxActor = pNodeActor->GetData();

			if ( pxActor )
			{			
				switch ( pxActor->m_stFeature.bGender )
				{
					case _GENDER_MAN:
					case _GENDER_WOMAN:
					{
						CHero*	pxHero;
						pxHero = (CHero*)pxActor;
						pxHero->DrawEffect();
						pxHero->ShowMessage(nLoopTime);
						pxHero->DrawHPBar();
						pxHero->DrawHPNum();
						break;
					}
					case _GENDER_MON:
					{
						pxActor->ShowMessage(nLoopTime);
						pxActor->DrawEffect();
						pxActor->DrawHPBar();
						pxActor->DrawHPNum();
						break;
					}
					case _GENDER_NPC:
					{
						pxActor->ShowMessage(nLoopTime);
						pxActor->DrawEffect();
						CheckMarketWindow(pxActor);
						break;
					}
				}
			}
		}

		DropItemShow();

		m_xLightFog.ShowLightFog();


		// 마법 그리기
		for ( pNode = m_xMagicList.GetHead(); pNode; pNode = pNode->GetNext() )
		{
			pxMagic = pNode->GetData();

			if ( pxMagic )
			{
				if ( pxMagic->m_wMagicNum == _SKILL_CONCENFIREBALL )
				{
					CConcenFireball* pxCocenFireball = (CConcenFireball*)pxMagic;
					pxCocenFireball->DrawMagic();
				}
				else if ( pxMagic->m_wMagicNum == _SKILL_CONCENFIREBALL )
				{
					CRefineAdd* pxRefineAdd = (CRefineAdd*)pxMagic;
					pxRefineAdd->DrawMagic();
				}
				else			
				{
					pxMagic->DrawMagic();
				}
			}
		}

		if ( m_pxAutoSavedMagicActor )
		{
			if ( m_pxAutoSavedMagicActor->m_stFeature.bGender == _GENDER_MON && !m_pxAutoSavedMagicActor->m_bIsDead )
			{
				m_pxAutoSavedMagicActor->DrawName();
				m_pxAutoSavedMagicActor->DrawHPBar(900, 700);
			}
		}

		if ( m_pxSavedTargetActor )
		{
			if ( m_pxSavedTargetActor->m_stFeature.bGender == _GENDER_MON && !m_pxSavedTargetActor->m_bIsDead )
			{
				m_pxSavedTargetActor->DrawName();
				m_pxSavedTargetActor->DrawHPBar(900, 700);
			}
		}
		

		if ( m_pxMouseTargetActor )
		{
			m_pxExplainActor = m_pxMouseTargetActor;

			if ( m_pxMouseOldTargetActor != m_pxMouseTargetActor )
			{
				m_dwMonShowTick = timeGetTime();

				if ( !m_pxMouseTargetActor->m_szName[0] )
				{
					g_xClientSocket.SendQueryName(m_pxMouseTargetActor->m_nIdentity, m_pxMouseTargetActor->m_nPosX, m_pxMouseTargetActor->m_nPosY);
				}
				else if ( m_bViewMonInfo && m_pxExplainActor && m_pxExplainActor->m_stMonType.stMonStats.szSpeed == -1 )
				{
					g_xClientSocket.SendQueryMonsterInfo(m_pxExplainActor->m_nIdentity, m_pxExplainActor->m_nPosX, m_pxExplainActor->m_nPosY);
				}
			}

			if ( m_pxMouseTargetActor->m_stFeature.bGender == _GENDER_MON && !m_pxExplainActor->m_bIsDead )
			{
				m_pxMouseTargetActor->DrawName();
				m_pxMouseTargetActor->DrawHPBar(900, 700);
			}
			else if ( m_pxMouseTargetActor->m_stFeature.bGender != _GENDER_MON )
			{
				m_pxMouseTargetActor->DrawName();
			}

			m_pxMouseOldTargetActor = m_pxMouseTargetActor;
		}
		else
		{
			if ( timeGetTime() - m_dwMonShowTick > 800 )
			{
				m_pxExplainActor = NULL;
			}
		}

		if ( m_nNPCWndPosX && m_nNPCWndPosY && ( abs(m_nNPCWndPosX-m_xMyHero.m_nPosX) > 5 || abs(m_nNPCWndPosY-m_xMyHero.m_nPosY) > 5) )
		{
			CloseNPCWindow();
		}

		RenderShine(nLoopTime);

		CheckGroupPosValidate();

		// 마법지속시간 표시
#ifdef _TEST_SERVER
		CheckMagicEffectTime();
		if( g_xGameProc.m_xInterface.m_xOptionWnd.mOptionWnd_bShowMagicEffectTime )
		{
			ShowMagicEffectTime();
		}
#endif

		m_xInterface.RenderInterface(nLoopTime, m_ptMousePos);
	
		// 밤나무, 트리.
//		if ( m_pxExplainActor && m_pxExplainActor->m_stFeature.bGender == _GENDER_MON && !m_pxExplainActor->m_bIsDead && 
//			 MAKEWORD(m_pxExplainActor->m_stFeature.bDress, m_pxExplainActor->m_stFeature.bHair) != 127 &&
//			 MAKEWORD(m_pxExplainActor->m_stFeature.bDress, m_pxExplainActor->m_stFeature.bHair) != 153 )
//		{
//			ShowMonExplain(m_pxExplainActor->m_stFeature.bDress, 0, 0);
//		}

//		g_xMainWnd.DrawWithGrayBackBuffer();

		ShowAreaState();
		RenderDiceMode(nLoopTime);

#ifdef _DEBUG
		ShowStatus(0, 0);
#endif
	}
	else
	{
		dwReceiveTime += nLoopTime;

		Clear(0);

		if ( !m_bNoticeCehcked && dwReceiveTime > 100000 )
		{
			m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GAMEOUT, _OK, g_xMsg.GetMsg(1512));
		}
	}

	m_xGameMsgBox.RenderMsgBox(m_ptMousePos);
	m_xNotice.RenderMessageBox(nLoopTime);
/*
	if ( m_bSetMiniMap == FALSE && m_xInterface.m_nInformationMode == _INFO_MINIMAP)
	{
		g_xClientSocket.SendWantMMap();
		m_xInterface.m_bReadyInforMap = TRUE;
		m_bSetMiniMap = TRUE;
	}
*/
	// 자동 줍기
	if ( m_bAutoPickup )
		AutoPickUp();

//	AutoFollow();

	RenderFadeState(nLoopTime);

	//AutoHunt();
/*
	if ( m_ShowAddOn )
	{
		CHAR szTemp[MAX_PATH];
		// 시간 
		g_xMainWnd.PutsHan(NULL, 5, 2, RGB(250, 250, 250), RGB(0, 0, 0), m_szTime);

		// 경험치
		sprintf(szTemp, "%s %I64d/", g_xMsg.GetMsg(1520), m_xMyHero.m_stAbility.dlngExp );
		sprintf(szTemp, "%s%I64d", szTemp, g_xGameProc.m_xMyHero.m_stAbility.dlngMaxExp );
		g_xMainWnd.PutsHan(NULL, 100, 2, RGB(250, 250, 250), RGB(0, 0, 0), szTemp);

		// 무기 경험치
		if ( m_xInterface.m_xStatusWnd.m_stEquipItem[_U_WEAPON].bSetted ) 
		{
			INT	 nLevel = 0;
			for ( INT nCnt=0; nCnt<35; nCnt++ )
			{
				if ( g_nWeaponLevelTable[nCnt] <= m_xInterface.m_xStatusWnd.m_stEquipItem[_U_WEAPON].xItem.m_stItemInfo.bLevel_R && g_nWeaponLevelTable[nCnt+1] > m_xInterface.m_xStatusWnd.m_stEquipItem[_U_WEAPON].xItem.m_stItemInfo.bLevel_R )
				{
					break;
				}
			}

			nLevel = nCnt+1;

			if ( nLevel >= 17 )
			{
				sprintf( szTemp,  "g_xMsg.GetMsg(2508) : MAX" );
			}
			else
			{
				UINT  wSwordTrainPoint = m_xInterface.m_xStatusWnd.m_stEquipItem[_U_WEAPON].xItem.m_stItemInfo.wAmount_GB;
				wSwordTrainPoint = wSwordTrainPoint + (60000 * m_xInterface.m_xStatusWnd.m_stEquipItem[_U_WEAPON].xItem.m_stItemInfo.bLevel_R);
		
				INT	  nExpIdx = nLevel - 1;

				if (nExpIdx > 0)
				{
					for ( INT nIdx=0; nIdx < nLevel-1 && nIdx < 35; nIdx++ )
						wSwordTrainPoint -= g_nWeaponExpTable[nIdx];
				}

				sprintf(szTemp, "%s %d/%d", g_xMsg.GetMsg(1521), wSwordTrainPoint , g_nWeaponExpTable[nExpIdx]);
			}
			g_xMainWnd.PutsHan(NULL, 300, 2, RGB(250, 250, 250), RGB(0, 0, 0), szTemp);
		}

		// 착용 무게
		sprintf(szTemp, "%s %d/%d", g_xMsg.GetMsg(2402), m_xMyHero.m_stAbility.bWearWeight, m_xMyHero.m_stAbility.bMaxWearWeight);
		g_xMainWnd.PutsHan(NULL, 450, 2, RGB(250, 250, 250), RGB(0, 0, 0), szTemp);

		sprintf(szTemp, "%s %d/%d", g_xMsg.GetMsg(2404), m_xMyHero.m_stAbility.wWeight, m_xMyHero.m_stAbility.wMaxWeight);

		g_xMainWnd.PutsHan(NULL, 620, 17, RGB(250, 250, 250), RGB(0, 0, 0), szTemp);

	}
*/
//	if (m_szSocket[0] != NULL)
//	{
//		g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(), 0, 0, RGB(250, 250, 250), RGB(0, 0, 0), m_szSocket);
//	}
	
//	RECT rc = {m_rcMain.left+534, m_rcMain.top+13, m_rcMain.left+618, m_rcMain.top+116};
//	g_xGameProc.m_pxExplainActor->m_hbmFaceImg.Draw(g_xMainWnd.GetBackBuffer(), &rc);

//	RECT ptDest = {m_ptMousePos.x, m_ptMousePos.y, m_ptMousePos.x + 60, m_ptMousePos.y + 40};

//	ShowCursor( FALSE );

//	m_hbmMouse.Draw(g_xMainWnd.GetBackBuffer(), &ptDest);

////////////// 윈도우모드 막기 ///////////////////////////////////////////////////
//		CHAR	szTemp[MAX_PATH];
//		DWORD dwFrameWidth    = GetSystemMetrics( SM_CXFULLSCREEN );

//		sprintf(szTemp, "%d", dwFrameWidth);

//		g_xMainWnd.PutsHan(NULL, 0, 200, RGB(250, 250, 0), RGB(0, 0, 0), szTemp);
////////////// 윈도우모드 막기 ///////////////////////////////////////////////////

//		if ( dwFrameWidth != 800 )
//		{
//			SendMessage(g_xMainWnd.GetSafehWnd(), WM_DESTROY, NULL, NULL);
//		}
//		m_dwScreenModeTimer = g_dwCurrTime;
//




}


VOID CGameProcess::CloseNPCWindow()
{
	if ( m_xInterface.m_xNPCWnd.GetGameWndActive() )
	{
		m_xInterface.DeleteWindowToList(_WND_ID_NPCCHAT);
		m_xInterface.m_xNPCWnd.SetGameWndActive(FALSE);

		m_nNPCWndPosX = m_nNPCWndPosY = 0;
	}
	if (m_xInterface.m_xStoreWnd.GetGameWndActive())
	{
		m_xInterface.DeleteWindowToList(_WND_ID_STORE);
		m_xInterface.m_xStoreWnd.SetGameWndActive(FALSE);
	}
	if ( m_xInterface.m_xInventoryWnd.GetGameWndActive() && m_xInterface.m_xInventoryWnd.GetInvenType() != _INVEN_TYPE_BAG )
	{
		m_xInterface.DeleteWindowToList(_WND_ID_INVENTORY);
		m_xInterface.m_xInventoryWnd.SetGameWndActive(FALSE);
		m_xInterface.m_xInventoryWnd.SetInvenType(_INVEN_TYPE_BAG);
		m_xInterface.m_xInventoryWnd.SetMerchantID(0);
		m_xInterface.m_xInventoryWnd.InitParkItem();
	}
}



BOOL CGameProcess::RenderShine(INT nLoopTime)
{
	LPGROUNDITEM pstItem = NULL;
	DWORD		 dwCurrTick = timeGetTime();

	CListNode < GROUNDITEM >	*pNode;

	for ( pNode = m_stMapItemList.GetHead(); pNode; pNode = pNode->GetNext() )
	{
		pstItem = pNode->GetData();

		if ( pstItem )
		{
			if ( dwCurrTick - pstItem->dwLastShineTick > pstItem->dwRandShineDelay )
			{
				pstItem->dwShineCurrDelay += nLoopTime;

				if ( pstItem->dwShineCurrDelay > 100 )
				{
					pstItem->dwCurrShineFrm++;
					pstItem->dwShineCurrDelay = 0;

					if ( pstItem->dwCurrShineFrm > 9 )
					{
						pstItem->dwLastShineTick = dwCurrTick;
						pstItem->dwCurrShineFrm = 0;
						continue;
					}
				}

				CWHWilImageData* pxShineImg = &m_xImage.m_xImageList[_IMAGE_PROGUSE];
				if ( pxShineImg->NewSetIndex(pstItem->dwCurrShineFrm+40) )
				{
					D3DMATERIAL7 mtrl;
					INT nCenterX = (pstItem->nTileX-m_xMap.m_nStartViewTileX)*_CELL_WIDTH +m_xMap.m_nViewPosX-m_xMap.m_nViewOffsetX+8;
					INT nCenterY = (pstItem->nTileY-m_xMap.m_nStartViewTileY)*_CELL_HEIGHT+m_xMap.m_nViewPosY-m_xMap.m_nViewOffsetY;

					D3DVECTOR	vecTrans((FLOAT)nCenterX, (FLOAT)nCenterY, 0);
					D3DVECTOR	vecScale((FLOAT)pxShineImg->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxShineImg->m_lpstNewCurrWilImageInfo->shHeight, 0.0f);

					LPDIRECTDRAWSURFACE7 lpddsTextr = m_xImage.GetTextrImg(_TEXTR_FILE_PARTICLE, _IMAGE_PROGUSE, pstItem->dwCurrShineFrm+40);

					D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)255/255.0f, (FLOAT)255/255.0f);
					mtrl.diffuse.a = 1.0f/255.0f;

					m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr);
				}
			}
		}
	}

	return TRUE;
}



VOID CGameProcess::RenderObject(INT nLoopTime)
{
	INT	 nXCnt, nYCnt, nStartX, nStartY, nObjFileIdx, nImgIdx, nArrayNum, nObjCnt, nMapViewX, nMapViewY;
	BOOL bIsMapViewTime = FALSE;

	if ( m_xMap.m_bMapLoaded == FALSE )
	{
		return;
	}

	m_xMap.SetAniTileFrame(nLoopTime);

	// 48*32 타일형 오브젝트 그리기.
	for ( nYCnt = m_xMap.m_nStartViewTileY-10; nYCnt < m_xMap.m_nStartViewTileY+_VIEW_CELL_Y_COUNT+10; nYCnt++ )
	{
		for ( nXCnt = m_xMap.m_nStartViewTileX-10+m_nViewLGapX; nXCnt < m_xMap.m_nStartViewTileX+_VIEW_CELL_X_COUNT+10+m_nViewRGapX; nXCnt++ )
		{
			if ( nYCnt >= m_xMap.m_stMapFileHeader.shHeight )
			{
				break;
			}

			if ( nXCnt >= m_xMap.m_stMapFileHeader.shWidth || nXCnt < 0 || nYCnt < 0 )
			{
				continue; 
			}

			// Test : 광원을 위해서 -10부터 +10까지의 영역을 더 잡는다.
			LIGHTINFO stLight = m_xMap.GetTileLightInfo(nXCnt, nYCnt);
			if ( stLight.bIsLight && stLight.cLightSizeType < 4 && stLight.cLightColorType < 10 )
			{
				m_xLightFog.SetLightRadiusWithCircle((nXCnt-m_xMap.m_nStartViewTileX)*_CELL_WIDTH-m_xMap.m_nViewOffsetX+m_xMap.m_nViewPosX,
													 (nYCnt-m_xMap.m_nStartViewTileY)*_CELL_HEIGHT-m_xMap.m_nViewOffsetY+m_xMap.m_nViewPosY, 
													 m_xMap.m_bLightSize[stLight.cLightSizeType], 
													 m_xMap.m_stRGBInfo[stLight.cLightColorType].bBlue, m_xMap.m_stRGBInfo[stLight.cLightColorType].bGreen, m_xMap.m_stRGBInfo[stLight.cLightColorType].bRed);			
			}

			m_xMap.DrawObjOneCellTile(nXCnt, nYCnt, 0);
			m_xMap.DrawObjOneCellTile(nXCnt, nYCnt, 1);

			nMapViewX	   = 0;
			nMapViewY	   = 0;
			bIsMapViewTime = FALSE;

			if ( nXCnt >= m_xMap.m_nStartViewTileX && nXCnt < m_xMap.m_nStartViewTileX + _VIEW_CELL_X_COUNT && nYCnt >= m_xMap.m_nStartViewTileY && nYCnt < m_xMap.m_nStartViewTileY + _VIEW_CELL_Y_COUNT )
			{
				bIsMapViewTime = TRUE;
				nMapViewX = nXCnt - m_xMap.m_nStartViewTileX;
				nMapViewY = nYCnt - m_xMap.m_nStartViewTileY;
			}

			RenderActorList(nMapViewX, nMapViewY, TRUE);
		}
	}	

	// 48*32가 아닌 길이가 있는 타일형 오브젝트 그리기.
	for ( nYCnt = m_xMap.m_nStartViewTileY; nYCnt < m_xMap.m_nStartViewTileY+_VIEW_CELL_Y_COUNT_FOR_OBJ; nYCnt++ )
	{
		for ( nXCnt = m_xMap.m_nStartViewTileX+m_nViewLGapX; nXCnt < m_xMap.m_nStartViewTileX+_VIEW_CELL_X_COUNT+m_nViewRGapX; nXCnt++ )
		{
			if ( nYCnt >= m_xMap.m_stMapFileHeader.shHeight )
			{
				break;
			}
			if ( nXCnt >= m_xMap.m_stMapFileHeader.shWidth || nXCnt < 0 || nYCnt < 0 )
			{
				continue; 
			}

			nArrayNum = nYCnt + nXCnt*m_xMap.m_stMapFileHeader.shHeight;

			m_xMap.DrawObjTile(nXCnt, nYCnt, 0);
			m_xMap.DrawObjTile(nXCnt, nYCnt, 1);

//			m_xMap.DrawOpenDoor(nXCnt, nYCnt);

			nMapViewX	   = 0;
			nMapViewY	   = 0;
			bIsMapViewTime = FALSE;

			if ( nXCnt >= m_xMap.m_nStartViewTileX && nXCnt < m_xMap.m_nStartViewTileX + _VIEW_CELL_X_COUNT && nYCnt >= m_xMap.m_nStartViewTileY && nYCnt < m_xMap.m_nStartViewTileY + _VIEW_CELL_Y_COUNT )
			{
				bIsMapViewTime = TRUE;
				nMapViewX = nXCnt - m_xMap.m_nStartViewTileX;
				nMapViewY = nYCnt - m_xMap.m_nStartViewTileY;
			}
	
			if ( bIsMapViewTime )
			{
				// 이벤트이미지 그리기.
				RenderEvent(nMapViewX, nMapViewY);
				// 바닥아이템 그리기.
				RenderGroundItem(nMapViewX, nMapViewY);
			}

			// 내캐릭터 그리기.
			if ( nXCnt == m_xMyHero.m_nPosX && nYCnt == m_xMyHero.m_nPosY )
			{
				BOOL bFocused = FALSE;
				// 그림의 시작좌표, 포커스상태, 그림자 블렌딩 상태를 넘겨준다.
				if ( PtInRect(&m_xMyHero.m_rcActor, m_ptMousePos) && !m_pxMouseTargetActor )
				{
					bFocused			 = TRUE;
					m_pxMouseTargetActor = &m_xMyHero;
				}


				if ( (( m_xMyHero.m_bEftFeature & 32 ) >> 5 ) && !(m_xMyHero.m_nCharState & 0X00800000) )
				{
					INT nState = m_xMyHero.m_nCharState;
					m_xMyHero.m_nCharState = 0X08000000;
					m_xMyHero.DrawActorAfterImage(&m_xMap, bFocused, m_bShadowABlend, FALSE, !m_bShadowABlend, 2);
					m_xMyHero.m_nCharState = 0X00001000;
					m_xMyHero.DrawActorAfterImage(&m_xMap, bFocused, m_bShadowABlend, FALSE, !m_bShadowABlend, 1);
					m_xMyHero.m_nCharState = nState;
				}
				m_xMyHero.DrawActor(bFocused, m_bShadowABlend, FALSE, !m_bShadowABlend);
				
				m_xMyHero.DrawCharLight(FALSE);
				m_xMyHero.ShowShield();
				m_xMyHero.ShowPahwangbo();
			}

			if ( bIsMapViewTime )
			{
				// 다른 캐릭터 그리기.
				RenderActorList(nMapViewX, nMapViewY);
				// 땅에 깔리는 마법.
				RenderGroundMagic(nMapViewX, nMapViewY);
			}
		}
	}		

	// 반투명하게 찍을 부분.
	if ( !m_xMyHero.m_nABlendDelay )
	{
		m_xMyHero.m_nABlendDelay	 = 10;
		m_xMyHero.m_nABlendCurrDelay = 6;
		m_xMyHero.DrawActor(FALSE, m_bShadowABlend, FALSE, m_bShadowABlend, TRUE );
		m_xMyHero.m_nABlendDelay	 = 0;
		m_xMyHero.m_nABlendCurrDelay = 0;
	}




/*	if ( m_pxMouseTargetActor && m_pxMouseTargetActor != &m_xMyHero && !m_pxMouseTargetActor->m_nABlendDelay )
	{
		m_pxMouseTargetActor->m_nABlendDelay	 = 10;
		m_pxMouseTargetActor->m_nABlendCurrDelay = 5;
		m_pxMouseTargetActor->DrawActor(&m_xMap, FALSE, m_bShadowABlend, FALSE, m_bShadowABlend);		
		m_pxMouseTargetActor->m_nABlendDelay	 = 0;
		m_pxMouseTargetActor->m_nABlendCurrDelay = 0;
	}*/
}



VOID CGameProcess::RenderEvent(INT nMapViewX, INT nMapViewY)
{	
	INT nStartX, nStartY, nX, nY;
	for ( INT nObjCnt = 0; nObjCnt < _MAX_CELL_OBJ; nObjCnt++ )
	{
		LPEVENTIMG pstEvent = m_stMemMappedID[nMapViewY][nMapViewX].pstEvent[nObjCnt];

		if ( pstEvent )
		{
			if ( timeGetTime() - pstEvent->dwTick > pstEvent->wOutDelay )
			{
				D3DMATERIAL7 mtrl;

				CWHWilImageData* pxEventImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE];

				if ( pxEventImg->NewSetIndex(pstEvent->wFrameNum) )
				{
					nStartX = (pstEvent->nTileX-m_xMap.m_nStartViewTileX)* _CELL_WIDTH+m_xMap.m_nViewPosX-m_xMap.m_nViewOffsetX;
					nStartY = (pstEvent->nTileY-m_xMap.m_nStartViewTileY)*_CELL_HEIGHT+m_xMap.m_nViewPosY-m_xMap.m_nViewOffsetY;

					nX  = nStartX+pxEventImg->m_lpstNewCurrWilImageInfo->shPX;
					nY  = nStartY+pxEventImg->m_lpstNewCurrWilImageInfo->shPY;

					if ( !pstEvent->bUseAlpha )
					{
						g_xMainWnd.DrawWithImageForCompClipRgn(nX, nY, pxEventImg->m_lpstNewCurrWilImageInfo->shWidth, pxEventImg->m_lpstNewCurrWilImageInfo->shHeight,
															   (WORD*)pxEventImg->m_pbCurrImage, _CLIP_WIDTH, _CLIP_HEIGHT);
					}
					else
					{
						D3DVECTOR	vecTrans((FLOAT)nX, (FLOAT)nY, 0);
						D3DVECTOR	vecScale((FLOAT)pxEventImg->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxEventImg->m_lpstNewCurrWilImageInfo->shHeight, 1);

						LPDIRECTDRAWSURFACE7 lpSurface = m_xImage.GetTextrImg(_TEXTR_FILE_PARTICLE, _IMAGE_PROGUSE, pstEvent->wFrameNum);

						D3DUtil_InitMaterial(mtrl, (FLOAT)1.0f, (FLOAT)1.0f, (FLOAT)1.0f);
						mtrl.diffuse.a = (FLOAT)180/255.0f;
						g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpSurface);
					}
				}
			}
		}
		else
		{
			break;
		}
	}
}


VOID CGameProcess::RenderGroundItem(INT nMapViewX, INT nMapViewY)
{
	INT nStartX, nStartY, nX, nY;

	for ( INT nObjCnt = 0; nObjCnt < _MAX_CELL_OBJ; nObjCnt++ )
	{
		LPGROUNDITEM pstItem = m_stMemMappedID[nMapViewY][nMapViewX].pstItem[nObjCnt];
		if ( pstItem )
		{
			CWHWilImageData* pxItemImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_GROUND];
			if ( pxItemImg->NewSetIndex(pstItem->wLooks) )
			{
				nStartX = (pstItem->nTileX-m_xMap.m_nStartViewTileX)*_CELL_WIDTH+m_xMap.m_nViewPosX-m_xMap.m_nViewOffsetX;
				nStartY = (pstItem->nTileY-m_xMap.m_nStartViewTileY)*_CELL_HEIGHT+m_xMap.m_nViewPosY-m_xMap.m_nViewOffsetY;
				INT nX  = nStartX+_CELL_WIDTH/2-pxItemImg->m_lpstNewCurrWilImageInfo->shWidth/2;
				INT nY  = nStartY+_CELL_HEIGHT/2-pxItemImg->m_lpstNewCurrWilImageInfo->shHeight/2;

				g_xMainWnd.DrawWithShadowABlend(
										nX+1, nY+1, 
										pxItemImg->m_lpstNewCurrWilImageInfo->shWidth,
										pxItemImg->m_lpstNewCurrWilImageInfo->shHeight,
										(WORD*)pxItemImg->m_pbCurrImage, 
										_CLIP_WIDTH, _CLIP_HEIGHT, m_wShadowClr, FALSE, 15);

				if ( nMapViewX+m_xMap.m_nStartViewTileX == m_ptCurrTile.x && nMapViewY+m_xMap.m_nStartViewTileY == m_ptCurrTile.y )
				{
					g_xMainWnd.DrawWithImageForCompClipRgn(nX, nY, pxItemImg->m_lpstNewCurrWilImageInfo->shWidth,pxItemImg->m_lpstNewCurrWilImageInfo->shHeight,
														   (WORD*)pxItemImg->m_pbCurrImage, _CLIP_WIDTH, _CLIP_HEIGHT, 0XFFFF, 0XFFFF, TRUE);
				}
				else
				{
					g_xMainWnd.DrawWithImageForCompClipRgn(nX, nY, pxItemImg->m_lpstNewCurrWilImageInfo->shWidth,pxItemImg->m_lpstNewCurrWilImageInfo->shHeight,
														   (WORD*)pxItemImg->m_pbCurrImage, _CLIP_WIDTH, _CLIP_HEIGHT);
				}

			}
		}
		else
		{
			break;
		}
	}
}


VOID CGameProcess::RenderActorList(INT nMapViewX, INT nMapViewY, BOOL bDeadDraw)
{
	for ( INT nObjCnt = 0; nObjCnt < _MAX_CELL_OBJ; nObjCnt++ )
	{
		BOOL	bFocused	= FALSE;
		BOOL	bDrawShadow = TRUE;
		CActor* pxActor = m_stMemMappedID[nMapViewY][nMapViewX].pxActor[nObjCnt];

		if ( pxActor )
		{
			BYTE bOpa = 50;

			if ( bDeadDraw )
			{
				// 밤나무, 트리 예외적용.
				if ( !pxActor->m_bIsDead && 
					 MAKEWORD(pxActor->m_stFeature.bDress, pxActor->m_stFeature.bHair) != 127 &&
					 MAKEWORD(pxActor->m_stFeature.bDress, pxActor->m_stFeature.bHair) != 153 && 
					 MAKEWORD(pxActor->m_stFeature.bDress, pxActor->m_stFeature.bHair) != 187 && 
					 MAKEWORD(pxActor->m_stFeature.bDress, pxActor->m_stFeature.bHair) != 188 && 
					 MAKEWORD(pxActor->m_stFeature.bDress, pxActor->m_stFeature.bHair) != 534 && 
					 MAKEWORD(pxActor->m_stFeature.bDress, pxActor->m_stFeature.bHair) != 535 && 
					 MAKEWORD(pxActor->m_stFeature.bDress, pxActor->m_stFeature.bHair) != 536 && 
					 MAKEWORD(pxActor->m_stFeature.bDress, pxActor->m_stFeature.bHair) != 537 &&
					 MAKEWORD(pxActor->m_stFeature.bDress, pxActor->m_stFeature.bHair) != 179 && 
					 MAKEWORD(pxActor->m_stFeature.bDress, pxActor->m_stFeature.bHair) != 189	// 성훈씨.
				   )
				{
					break;
				}
				else
				{
					bOpa = 30;
				}
			}
			else
			{
				if ( pxActor->m_bIsDead && 
					 MAKEWORD(pxActor->m_stFeature.bDress, pxActor->m_stFeature.bHair) != 127 &&
					 MAKEWORD(pxActor->m_stFeature.bDress, pxActor->m_stFeature.bHair) != 153
					)
				{
					continue;
				}
			}

			if ( pxActor == m_pxMouseTargetActor )
			{
				bFocused = TRUE;
			}

/*			if ( pxActor == m_pxMouseTargetActor && m_bShadowABlend )
			{
				bDrawShadow = FALSE;
			}
*/
			switch ( pxActor->m_stFeature.bGender )
			{
				case _GENDER_MAN:
				case _GENDER_WOMAN:
				{
					CHero* pxHero;
					pxHero = (CHero*)pxActor;

					if ( (( pxHero->m_bEftFeature & 32 ) >> 5 ) && !(pxHero->m_nCharState & 0X00800000) )
					{
						INT nState = pxHero->m_nCharState;
						pxHero->m_nCharState = 0X08000000;
						pxHero->DrawActorAfterImage(&m_xMap, bFocused, m_bShadowABlend, FALSE, !m_bShadowABlend, 2);
						pxHero->m_nCharState = 0X00001000;
						pxHero->DrawActorAfterImage(&m_xMap, bFocused, m_bShadowABlend, FALSE, !m_bShadowABlend, 1);
						pxHero->m_nCharState = nState;
					}

					pxHero->DrawActor(&m_xMap, bFocused, m_bShadowABlend, TRUE, bDrawShadow);

					if (m_bDrawName == TRUE)
						pxHero->DrawName();

					pxHero->DrawCharLight();
					pxHero->ShowShield();
					pxHero->ShowPahwangbo();

					break;
				}
				case _GENDER_NPC:
				case _GENDER_FLAG:
				{
					CNPC* pxNPC;
					pxNPC = (CNPC*)pxActor;

					pxNPC->DrawActor(&m_xMap, bFocused, m_bShadowABlend, TRUE, bDrawShadow);
					pxNPC->DrawCharLight();
					break;
				}
				case _GENDER_MON:
				{
					pxActor->DrawActor(&m_xMap, bFocused, m_bShadowABlend, TRUE, bDrawShadow);

					if ( m_xMap.m_pszMapName[0] == 'T' )
					{
						if ( !pxActor->m_bIsDead )
						{
							pxActor->DrawName();
						}

						if ( pxActor->m_szName[0] == NULL && g_dwCurrTime - m_dwNameQueryTimer > 500 )
						{
							g_xClientSocket.SendQueryName(pxActor->m_nIdentity, pxActor->m_nPosX, pxActor->m_nPosY);
							m_dwNameQueryTimer = g_dwCurrTime;
						}

						pxActor->m_bOpenHealth = TRUE;
						pxActor->DrawHPBar();
						pxActor->m_bOpenHealth = FALSE;
					}

					break;
				}
			}
		}
		else
		{
			break;
		}
	}	
}


VOID CGameProcess::RenderGroundMagic(INT nMapViewX, INT nMapViewY)
{
	INT nMagicID[_MAX_CELL_OBJ];
	BOOL bSameMagic = FALSE;
	for ( INT nObjCnt = 0; nObjCnt < _MAX_CELL_OBJ; nObjCnt++ )
	{
		CMagic* pxMagic = m_stMemMappedID[nMapViewY][nMapViewX].pxMagic[nObjCnt];

		INT nNum = 0;

		if ( pxMagic )
		{
			nMagicID[nObjCnt] = pxMagic->m_wMagicNum;

			if ( nNum == pxMagic->m_wMagicNum)
				return;

			if ( !bSameMagic )
			{
				if ( pxMagic->m_wMagicNum == _SKILL_HOLYSHIELD || pxMagic->m_wMagicNum == _SKILL_EARTHFIRE ||pxMagic->m_wMagicNum == _SKILL_LIGHTWALL ||
					 pxMagic->m_wMagicNum == _EVENT_LEFTFIRE1 || pxMagic->m_wMagicNum == _EVENT_LEFTFIRE2 || pxMagic->m_wMagicNum == _EVENT_LEFTFIRE3 || 
					 pxMagic->m_wMagicNum == _EVENT_LEFTFIRE4 || pxMagic->m_wMagicNum == _EVENT_LEFTFIRE5 || pxMagic->m_wMagicNum == _SKILL_KANGMAK ||
					 pxMagic->m_wMagicNum == _SKILL_JISOKGYE )
				{
					CRepeatMagic* pxRepeatMagic = (CRepeatMagic*)pxMagic;
					pxRepeatMagic->DrawMagic();
				}
				else if ( pxMagic->m_wMagicNum == _SKILL_HURRICANE || pxMagic->m_wMagicNum == _SKILL_HURRICANESHOT || _SKILL_HURRICANEBOMB)
				{
					CHurricaneMagic* pxHurricaneMagic = (CHurricaneMagic*)pxMagic;
					pxHurricaneMagic->DrawMagic();
				}
				else if ( pxMagic->m_wMagicNum == _SKILL_FIRE || pxMagic->m_wMagicNum == _SKILL_ICE || pxMagic->m_wMagicNum == _SKILL_SHOOTLIGHTEN_ADD )
				{
					CMagicStream* pxMagicStream = (CMagicStream*)pxMagic;
					pxMagicStream->DrawMagic();
				}
				else
				{
					pxMagic->DrawMagic();
				}
			}
		}					
		else
		{
			break;
		}
	}
}



/******************************************************************************************************************

	메시지 관련 함수.

*******************************************************************************************************************/
LRESULT CGameProcess::OnMsgBoxReturn(WPARAM wParam, LPARAM lParam)
{
	BYTE  bWndID;
	BYTE  bMsgReturn;
	WORD  wPacket;

	bWndID		= HIBYTE(HIWORD(wParam));
	bMsgReturn	= LOBYTE(HIWORD(wParam));
	wPacket		= LOWORD(wParam);

	switch ( bWndID )
	{
		case _WND_ID_LOGOUT:
		{
			if ( bMsgReturn == _BTN_YES && CanGameOut() )
			{
				g_xClientSocket.SendQueryMsg(CM_SOFTCLOSE);				
				m_xInterface.SaveItemPos(m_xMyHero.m_szName);

				m_xInterface.m_xBeltWnd.SaveBeltPosition();
#ifdef _DEBUG
				m_xInterface.m_xUtilWnd.SaveUtilSet();
#endif
				m_xInterface.m_xMagicShortcutWnd.SaveMagicKeySet();
				m_dwFadeTime = 0;
				m_bFateState = 2;
			}
			break;
		}
		case _WND_ID_GAMEOVER:
		{
			if ( bMsgReturn == _BTN_YES && CanGameOut() )
			{
				WSACleanup();
				LoadCredit();

				if ( g_xMainWnd.GetScreenMode() & _DXG_SCREENMODE_WINDOW )
				{
					if ( FAILED(g_xMainWnd.ResetDXG(640, 480, 16, _DXG_SCREENMODE_WINDOW, _DXG_DEVICEMODE_PRIMARY|_DXG_DEVICEMODE_D3D)) )
					{
						MessageBox(g_xMainWnd.GetSafehWnd(), TEXT("DirectDraw RESETUP failed!!!") TEXT("The Program will now exit."), TEXT("MirDXG"), MB_ICONERROR | MB_OK);
					}
				}
				else
				{
					if ( FAILED(g_xMainWnd.ResetDXG(640, 480, 16, _DXG_SCREENMODE_FULLSCREEN, _DXG_DEVICEMODE_PRIMARY|_DXG_DEVICEMODE_D3D)) )
					{
						MessageBox(g_xMainWnd.GetSafehWnd(), TEXT("DirectDraw RESETUP failed!!!") TEXT("The Program will now exit."), TEXT("MirDXG"), MB_ICONERROR | MB_OK);
					}
				}
			}
			break;
		}
		case _WND_ID_GAMEOUT:
		{
			if ( bMsgReturn == _BTN_OK && CanGameOut() )
			{
				SendMessage(g_xMainWnd.GetSafehWnd(), WM_DESTROY, NULL, NULL);			
			}
			break;
		}
		case _WND_ID_DIRECT_GAMEOUT:
		{
			SendMessage(g_xMainWnd.GetSafehWnd(), WM_DESTROY, NULL, NULL);			
			break;
		}
		case _WND_ID_DROPGOLD:
		{
			if ( bMsgReturn == _BTN_YES )
			{
				INT nAtoI = atoi((CHAR*) lParam);

				if ( nAtoI < m_xMyHero.m_nGlod )
				{
					g_xClientSocket.SendDropGold(nAtoI);
				}
			}
			break;
		}
		case _WND_ID_SELLMULTIPLEITEM:
		{
			if ( bMsgReturn == _BTN_YES )
			{
				INT nAtoI = 0;
				INT nItem = m_xInterface.m_xInventoryWnd.m_stParkItem.nItemNum;
				DWORD	dwCount = m_xInterface.m_xInventoryWnd.m_stInventoryItem[nItem].xItem.m_stItemInfo.wAmount_GB;

				if ( strcmp( (CHAR*)lParam, "") == 0)
					nAtoI = dwCount;
				else
					nAtoI = atoi((CHAR*) lParam);


				if ( nAtoI <= dwCount && nAtoI > 0)
				{
					g_xClientSocket.SendSellItem(m_xInterface.m_xInventoryWnd.m_stInventoryItem[nItem].xItem.m_stItemInfo.nMakeIndex, m_xInterface.m_xInventoryWnd.m_nMerchantID, m_xInterface.m_xInventoryWnd.m_stInventoryItem[nItem].xItem.m_stItemInfo.stStdItem.szName, nAtoI);
				}
			}
			break;
		}
		case _WND_ID_BUYMULTIPLEITEM:
		{
			if ( bMsgReturn == _BTN_YES )
			{
				INT nAtoI = 0;

				if ( strcmp( (CHAR*)lParam, "") == 0)
					nAtoI = 1 ;
				else
					nAtoI = atoi((CHAR*) lParam);

				if ( nAtoI > 0)
				{
					g_xClientSocket.SendBuyGood(m_xInterface.m_xStoreWnd.m_nNpcID, m_xInterface.m_xStoreWnd.m_pstStoreAdd->pszName, m_xInterface.m_xStoreWnd.m_pstStoreAdd->nStock, nAtoI);
				}
			}
			break;
		}
			
		case _WND_ID_DROPMULTIPLEITEM:
		{
			if ( bMsgReturn == _BTN_YES )
			{
				INT nAtoI = 0;
				DWORD	dwCount = m_xInterface.m_stCommonItem.xItem.m_stItemInfo.wAmount_GB;

				if ( strcmp( (CHAR*)lParam, "") == 0)
					nAtoI = dwCount;
				else
					nAtoI = atoi((CHAR*) lParam);

				if ( nAtoI >= 100 )
					nAtoI = 100;

				if ( nAtoI < dwCount && nAtoI > 0)
				{
					g_xClientSocket.SendDropMultipleItem(m_xInterface.m_stCommonItem.xItem.m_stItemInfo.nMakeIndex, nAtoI, m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName);
					m_xInterface.m_xInventoryWnd.AddInvenItem(m_xInterface.m_stCommonItem.xItem, 0, FALSE);
					ZeroMemory(&m_xInterface.m_stCommonItem, sizeof(COMMONITEMSET));
				}
				else if ( nAtoI == dwCount)
				{
					g_xClientSocket.SendDropMultipleItem(m_xInterface.m_stCommonItem.xItem.m_stItemInfo.nMakeIndex, nAtoI, m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName);
				}
			}
			break;
		}
		case _WND_ID_DROPITEM:
		{
			if ( bMsgReturn == _BTN_YES )
			{
				if ( g_xGameProc.m_bUseSpell == FALSE )
				{
					g_xClientSocket.SendItemIndex(CM_DROPITEM, m_xInterface.m_stCommonItem.xItem.m_stItemInfo.nMakeIndex, m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName);
					m_xInterface.m_stCommonItem.bWaitResponse = TRUE;
				}
			}
			break;
		}
		case _WND_ID_SETUTILHP:
		{
			INT nAtoI = 0;
			nAtoI = atoi((CHAR*) lParam);

			if ( m_xInterface.m_xUtilWnd.mUtil_bMode == _SET_ITEM_MODE )
			{
				if ( m_xMyHero.m_stAbility.wMaxHP < nAtoI || nAtoI < 0 )
				{
					break;
				}

				m_xInterface.m_xUtilWnd.mUtil_nHPValue = nAtoI;
			}
			break;
		}
		case _WND_ID_SETUTILSCROLL:
		{
			INT nAtoI = 0;
			nAtoI = atoi((CHAR*) lParam);

			if ( m_xInterface.m_xUtilWnd.mUtil_bMode == _SET_ITEM_MODE )
			{
				if ( m_xMyHero.m_stAbility.wMaxHP < nAtoI || nAtoI < 0 )
				{
					break;
				}

				m_xInterface.m_xUtilWnd.mUtil_nScrollValue = nAtoI;
			}
			break;
		}
		case _WND_ID_SETUTILMP:
		{
			INT nAtoI = 0;
			nAtoI = atoi((CHAR*) lParam);

			if ( m_xInterface.m_xUtilWnd.mUtil_bMode == _SET_ITEM_MODE )
			{
				if ( m_xMyHero.m_stAbility.wMaxMP < nAtoI || nAtoI < 0 )
				{
					break;
				}

				m_xInterface.m_xUtilWnd.mUtil_nMPValue = nAtoI;
			}
			break;
		}
		case _WND_ID_SAVEMULTIPLEITEM:
		{
			if ( bMsgReturn == _BTN_YES )
			{
				INT		nAtoI = 0;
				INT		nItem = m_xInterface.m_xInventoryWnd.m_stParkItem.nItemNum;
				DWORD	dwCount = m_xInterface.m_xInventoryWnd.m_stInventoryItem[nItem].xItem.m_stItemInfo.wAmount_GB;

				if ( strcmp( (CHAR*)lParam, "") == 0)
					nAtoI = dwCount;
				else
					nAtoI = atoi((CHAR*) lParam);

				if ( nAtoI <= dwCount && nAtoI > 0)
				{
						g_xClientSocket.SendStorageItem(m_xInterface.m_xInventoryWnd.m_stInventoryItem[nItem].xItem.m_stItemInfo.nMakeIndex, m_xInterface.m_xInventoryWnd.m_nMerchantID, m_xInterface.m_xInventoryWnd.m_stInventoryItem[nItem].xItem.m_stItemInfo.stStdItem.szName, nAtoI);
				}
			}
			break;
		}
		case _WND_ID_TAKEBACKMULTIPLEITEM:
		{
			if ( bMsgReturn == _BTN_YES )
			{
				INT		nAtoI = 0;
				CItem* pxItem = m_xInterface.m_xStoreWnd.GetSelDetailItemInfo(m_xInterface.m_xStoreWnd.m_nSelDetailItem);
				DWORD	dwCount = pxItem->m_stItemInfo.wAmount_GB;

				if ( strcmp( (CHAR*)lParam, "") == 0)
					nAtoI = dwCount;
				else
					nAtoI = atoi((CHAR*) lParam);

				if ( nAtoI <= dwCount && nAtoI > 0)
				{
					g_xClientSocket.SendTakeBackItem(m_xInterface.m_xStoreWnd.m_nNpcID, pxItem->m_stItemInfo.stStdItem.szName, pxItem->m_stItemInfo.nMakeIndex, nAtoI);
				}
			}
			break;
		}
		case _WND_ID_EXCHANGEMULTIPLEITEM:
		{
			if ( bMsgReturn == _BTN_YES )
			{
				INT nAtoI = 0;

				DWORD	dwCount = m_xInterface.m_stCommonItem.xItem.m_stItemInfo.wAmount_GB;

				if ( strcmp( (CHAR*)lParam, "") == 0)
					nAtoI = dwCount;
				else
					nAtoI = atoi((CHAR*) lParam);


				if ( nAtoI <= dwCount && nAtoI > 0)
				{
					m_xInterface.m_xExchangeWnd.SetDealOnItemFromCommon(m_xInterface.m_xExchangeWnd.m_pstCommonItemSet, m_xInterface.m_xExchangeWnd.m_nDealCellNum);
					g_xClientSocket.SendAddDealItem(m_xInterface.m_xExchangeWnd.m_stDealOnItem.xItem.m_stItemInfo.stStdItem.szName, m_xInterface.m_xExchangeWnd.m_stDealOnItem.xItem.m_stItemInfo.nMakeIndex, nAtoI);
					m_xInterface.m_xExchangeWnd.m_pstCommonItemSet->bWaitResponse = TRUE;
				}
			}
			break;
		}
		case _WND_ID_SETVALUE:
		{
			if ( bMsgReturn == _BTN_YES )
			{
				INT nAtoI = 0;
				nAtoI = atoi((CHAR*) lParam);

				if ( nAtoI < 0 || nAtoI > 100000000 )
					break;

				if ( nAtoI != 0 )
					m_xInterface.m_xMarketUpWnd.mUserMarketUp_nPrice = nAtoI;
			}
			m_xInterface.m_xMarketUpWnd.mUserMarketUp_bSetItemPrice = FALSE;
		}
		break;
		case _WND_ID_SENDMONEY:
		{
			if ( bMsgReturn == _BTN_YES )
			{
				INT nAtoI = 0;
				nAtoI = atoi((CHAR*) lParam);

				if ( nAtoI < 0 || nAtoI > 100000000 )
					break;

				if ( nAtoI != 0 )
					m_xInterface.m_xMessengerWnd.mMessenger_nMoney = nAtoI;

				m_xInterface.m_xMessengerWnd.mMessenger_bSetMoney = TRUE;
			}
			else
			{
				m_xInterface.m_xMessengerWnd.mMessenger_bSetMoney = FALSE;
			}

			m_xInterface.m_xMessengerWnd.mMessenger_bSettingMoney = FALSE;
		}
		break;
		case _WND_ID_CUTWHISPER:
		{
			if ( bMsgReturn == _BTN_YES )
			{
				CHAR szSay[MAX_PATH];

				sprintf( szSay, "%s %s", g_xMsg.GetMsg(2162), (CHAR*) lParam );
				g_xClientSocket.SendSay(szSay);
			}
		}
		break;
		case _WND_ID_WANTTOBUY:
		{
			if ( bMsgReturn == _BTN_YES )
			{
				m_xInterface.m_xMarketWnd.BuyItem();
			}
		}
		break;
		case _WND_ID_WANTTOCANCEL:
		{
			if ( bMsgReturn == _BTN_YES )
			{
				m_xInterface.m_xMarketWnd.TakeBackMarketItem();
			}
		}
		break;
		case _WND_ID_WANTTOREGISTRY:
		{
			if ( bMsgReturn == _BTN_YES )
			{
				m_xInterface.m_xMarketUpWnd.RegistMyItem();
			}
		}
		break;
		case _WND_ID_CHARGE_BULLET:
		{
			if ( bMsgReturn == _BTN_YES )
			{
				INT nAtoI = 0;

				DWORD	dwCount = m_xInterface.m_stCommonItem.xItem.m_stItemInfo.wAmount_GB;

				if ( strcmp( (CHAR*)lParam, "") == 0)
					nAtoI = dwCount;
				else
					nAtoI = atoi((CHAR*) lParam);

				if ( nAtoI <= dwCount && nAtoI > 0)
				{
					g_xClientSocket.SendChargeItem(m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName, nAtoI, m_xInterface.m_stCommonItem.xItem.m_stItemInfo.nMakeIndex);
					m_xInterface.m_xInventoryWnd.AddInvenItem(m_xInterface.m_stCommonItem.xItem, 0, FALSE);
					ZeroMemory(&m_xInterface.m_stCommonItem, sizeof(COMMONITEMSET));

//					m_xInterface.m_stCommonItem.bWaitResponse = TRUE;
				}
			}
		}
		break;
		case _WND_ID_GAME:
		{
			if ( wPacket == CM_GUILDADDMEMBER && bMsgReturn == _BTN_YES )
			{
				g_xClientSocket.SendGuildAddMem((CHAR*)lParam);
			}
			break;
		}
#ifdef _DEBUG
		case _WND_ID_SETUTIL:
		{
			INT nAtoI = 0;
			nAtoI = atoi((CHAR*) lParam);

			if ( m_xInterface.m_xUtilWnd.mUtil_bMode == _SET_ITEM_MODE )
			{
				if ( m_xInterface.m_xUtilWnd.mUtil_nFocusedValue == 5 || m_xInterface.m_xUtilWnd.mUtil_nFocusedValue == 6 || m_xInterface.m_xUtilWnd.mUtil_nFocusedValue == 7 || m_xInterface.m_xUtilWnd.mUtil_nFocusedValue == 8 )
				{
					if ( m_xMyHero.m_stAbility.wMaxMP < nAtoI || nAtoI < 0 )
					{
						break;
					}
				}
				else
				{
					if ( m_xMyHero.m_stAbility.wMaxHP < nAtoI || nAtoI < 0 )
					{
						break;
					}
				}

				m_xInterface.m_xUtilWnd.mUtil_xUtilItemInfo[m_xInterface.m_xUtilWnd.mUtil_nFocusedValue].nValue = nAtoI;
			}
			else if ( m_xInterface.m_xUtilWnd.mUtil_bMode == _SET_MAGIC_MODE )
			{
				m_xInterface.m_xUtilWnd.mUtil_xUtilMagicInfo[m_xInterface.m_xUtilWnd.mUtil_nFocusedValue].nValue = nAtoI;
			}
		}
		break;
		case _WND_ID_SETPRIORITY:
		{
			INT nAtoI = 0;
			nAtoI = atoi((CHAR*) lParam);

			if ( nAtoI >= 0 && nAtoI < 11 )
			{
				if ( m_xInterface.m_xUtilWnd.mUtil_bMode == _SET_ITEM_MODE )
				{
					for ( INT nI=0; nI<10; nI++ )
					{
						if ( m_xInterface.m_xUtilWnd.mUtil_xUtilItemInfo[nI].nPriority == nAtoI )
							m_xInterface.m_xUtilWnd.mUtil_xUtilItemInfo[nI].nPriority = 0;
					}

					m_xInterface.m_xUtilWnd.mUtil_xUtilItemInfo[m_xInterface.m_xUtilWnd.mUtil_nFocusedValue].nPriority = nAtoI;
				}
				else if ( m_xInterface.m_xUtilWnd.mUtil_bMode == _SET_MAGIC_MODE )
				{
					for ( INT nI=0; nI<10; nI++ )
					{
						if ( m_xInterface.m_xUtilWnd.mUtil_xUtilMagicInfo[nI].nPriority == nAtoI )
							m_xInterface.m_xUtilWnd.mUtil_xUtilMagicInfo[nI].nPriority = 0;
					}

					m_xInterface.m_xUtilWnd.mUtil_xUtilMagicInfo[m_xInterface.m_xUtilWnd.mUtil_nFocusedValue].nPriority = nAtoI;
				}
			}
		}
		break;
		case _WND_ID_SETPRIORITY2:
		{
			INT nAtoI = 0;
			nAtoI = atoi((CHAR*) lParam);

			if ( nAtoI >= 0 && nAtoI < 5 )
			{
				for ( INT nI=0; nI<4; nI++ )
				{
					if ( m_xInterface.m_xUtilWnd.mUtil_xUtilItemInfo2[nI].nPriority == nAtoI )
						m_xInterface.m_xUtilWnd.mUtil_xUtilItemInfo2[nI].nPriority = 0;
				}

				m_xInterface.m_xUtilWnd.mUtil_xUtilItemInfo2[m_xInterface.m_xUtilWnd.mUtil_nFocusedValue].nPriority = nAtoI;
			}
		}
		break;
		case _WND_ID_SETNAME:
		{
			CHAR szTemp[MAX_PATH];

			sprintf(szTemp, (CHAR*) lParam);

			sprintf( m_xInterface.m_xUtilWnd.mUtil_xUtilMagicInfo[m_xInterface.m_xUtilWnd.mUtil_nFocusedValue].szName, szTemp);
		}
		break;
#endif
	}

	m_xInterface.OnMsgBoxReturn(wParam, lParam);

	return 0L;
}

LRESULT CGameProcess::OnDestroy(WPARAM wParam, LPARAM lParam)
{
	m_xInterface.SaveItemPos(m_xMyHero.m_szName);
	m_xInterface.m_xUtilWnd.SaveUtilSet();
	m_xInterface.m_xMagicShortcutWnd.SaveMagicKeySet();
	m_xInterface.m_xBeltWnd.SaveBeltPosition();

	DestroyFindHack();

//	DeleteProc();

//	WSACleanup();
//	ReleaseFontList();
	return 0L;
}

LRESULT CGameProcess::OnTimer(WPARAM wParam, LPARAM lParam)
{
	if ( wParam == _TIMER_ID )
	{
		if ( m_xInterface.m_xStatusWnd.m_stEquipItem[_U_RIGHTHAND].bSetted &&  strcmp( m_xInterface.m_xStatusWnd.m_stEquipItem[_U_RIGHTHAND].xItem.m_stItemInfo.stStdItem.szName, "견혼령" ) == 0 )
		{
			KillTimer(g_xMainWnd.GetSafehWnd(), _TIMER_ID);
		}

		DWORD	dwFogColor;
		FLOAT	fDstDarkRate = 0.0f;
		switch ( m_bFogState )
		{
		case _FOGSTATE_DAWN:
			{
				fDstDarkRate = 85.0f;
			}
			break;
		case _FOGSTATE_DAY:
			{
				fDstDarkRate = 255.0f;
			}
			break;
		case _FOGSTATE_NIGHT:
			{
				fDstDarkRate = 15.0f;
			}
			break;
		}

		if		( m_fDarkRate > fDstDarkRate )	m_fDarkRate -= 0.5f;
		else if ( m_fDarkRate < fDstDarkRate )	m_fDarkRate += 0.5f;
		else	
		{
			KillTimer(g_xMainWnd.GetSafehWnd(), _TIMER_ID);
		}

		dwFogColor = RGB(m_fDarkRate, m_fDarkRate, m_fDarkRate); 
		m_xLightFog.ChangeLightColor(dwFogColor);
	}
	else if ( wParam == _TIMER_MTESTID )
	{
		KillTimer(g_xMainWnd.GetSafehWnd(), _TIMER_MTESTID);
		m_xMyHero.ClientTestMagic();
	}
	else if ( wParam == _TIMER_SYSTIME )
	{
		GetLocalTime(&m_stSysTime);
		CHAR szTemp[10];
		sprintf(m_szTime,"%d%s", m_stSysTime.wHour, g_xMsg.GetMsg(1522));
		sprintf(szTemp,"%d%s", m_stSysTime.wMinute, g_xMsg.GetMsg(1523));
		strcat(m_szTime, szTemp);
		sprintf(szTemp,"%d%s", m_stSysTime.wSecond, g_xMsg.GetMsg(1524));
		strcat(m_szTime, szTemp);
	}
	// 게임시간 공지
	// by eriastoa 2006.05.25
	else if( wParam == _NOTICE_TIMER )
	{
/*
#define _CHAT_COLOR2				1	//RGB( 10,  10,  10); // 검정색.
#define _CHAT_COLOR3				2	//RGB(255, 255, 255); // 흰색.
#define _CHAT_COLOR4				3	//RGB(255,   0,   0); // 빨강.
#define _CHAT_COLOR5				4	//RGB(  0, 255,   0); // 녹색.
#define _CHAT_COLOR6				5	//RGB(  0,   0, 255); // 푸른색
#define _CHAT_COLOR7				6	//RGB(255, 255,   0); // 노랑색.
#define _CHAT_COLOR8				7	//RGB(255, 128,   0); // 주황색
*/
		DWORD dwFont = GetChatColor( _CHAT_COLOR3 );
		DWORD dwBack = GetChatColor( _CHAT_COLOR8 );
					
		++g_nNoticeTimes;
		if( g_nNoticeTimes >= 3 )
		{
			dwBack = GetChatColor( _CHAT_COLOR4 );
			g_nMsgIdx = 1561;
		}

		CHAR str[ 256 ];
		sprintf( str, g_xMsg.GetMsg( g_nMsgIdx ), g_nNoticeTimes );

		m_xInterface.MsgAdd( dwFont, dwBack, str );
	}

	return 0L;
}


LRESULT CGameProcess::OnLButtonDoubleClick(WPARAM wParam, LPARAM lParam)
{
	m_ptMousePos.x = LOWORD(lParam);
	m_ptMousePos.y = HIWORD(lParam);

	if ( m_bRender == FALSE )
	{
		return 0L;
	}

	m_xInterface.OnLButtonDoubleClick(m_ptMousePos);

	return 0L;
}


LRESULT CGameProcess::OnWheel(WPARAM wParam, LPARAM lParam)
{
	INT nDelta;

	if ( m_bRender == FALSE )
	{
		return 0L;
	}

	nDelta = ( (INT)wParam < 0 ) ? -1 : 1;
	if ( nDelta > 0 )
		m_xInterface.OnScrollDown();
	else
		m_xInterface.OnScrollUp();


/*	for ( int ii = 0; ii < 3; ii++ )
	{
		CMagic* pxMagic;
		POINT ptPos = {m_xMyHero.m_nPosX + GetRandomNum(-5, 5), m_xMyHero.m_nPosY + GetRandomNum(-5, 5)};
		pxMagic = new CMagic;
//		if ( pxMagic->CreateMagic(_SKILL_HANGMAJINBUB, m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, ptPos.x, ptPos.y) )
		if ( pxMagic->CreateMagic(_SKILL_DEJIWONHO, m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, ptPos.x, ptPos.y) )
//			if ( pxMagic->CreateMagic(_SKILL_BIGCLOAK, m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, ptPos.x, ptPos.y) )
		{
			m_xMagicList.Insert (pxMagic);						
		}
		else
		{
			delete pxMagic;
		}

		if ( ii == 2 )
		{
			return 0L;
		}
	}
*/

	return 0L;
}


LRESULT CGameProcess::OnSysKeyDown(WPARAM wParam, LPARAM lParam)
{
	if ( wParam == VK_RETURN && m_bDebugInfo )
	{
		m_bRender = FALSE;
		g_xMainWnd.m_bIsWindowReady = FALSE;

		if ( g_xMainWnd.GetScreenMode() & _DXG_SCREENMODE_WINDOW )
		{
			if ( FAILED(g_xMainWnd.ResetDXG(800, 600, 16, _DXG_SCREENMODE_FULLSCREEN, _DXG_DEVICEMODE_PRIMARY|_DXG_DEVICEMODE_D3D)) )
			{
				MessageBox(g_xMainWnd.GetSafehWnd(), TEXT("DirectDraw RESETUP failed!!!") TEXT("The Program will now exit."), TEXT("MirDXG"), MB_ICONERROR | MB_OK);
			}
		}
		else
		{
			if ( FAILED(g_xMainWnd.ResetDXG(800, 600, 16, _DXG_SCREENMODE_WINDOW, _DXG_DEVICEMODE_PRIMARY|_DXG_DEVICEMODE_D3D)) )
			{
				MessageBox(g_xMainWnd.GetSafehWnd(), TEXT("DirectDraw RESETUP failed!!!") TEXT("The Program will now exit."), TEXT("MirDXG"), MB_ICONERROR | MB_OK);
			}
		}

		SetFocus(g_xMainWnd.GetSafehWnd());

		m_xInterface.m_xMiniMap.ResetMiniMap(g_xMainWnd.Get3DDevice());
		m_xImage.DelAllTextrFileList();
		g_xMainWnd.m_bIsWindowReady = TRUE;

		m_bRender = TRUE;
	}

	if ( m_xInterface.m_xGameOverWnd.GetGameWndActive() )
	{
		return 0L;
	}

	if ( m_xGameMsgBox.IsActive() )
	{
		return 0L;
	}

	if ( wParam == VK_F10 )
	{
		if ( m_xInterface.OnSysKeyDown(wParam, lParam) )
		{
			return FALSE;
		}

		INT		nTargetID		= 0;
		POINT	ptTaretTilePos	= {0, 0};
		FEATURE stFeature;
		ZeroMemory(&stFeature, sizeof(FEATURE));

		if ( m_pxAutoSavedMagicActor )
		{
			if ( NeedAutoTarget( wParam ) )
			{
				nTargetID			= m_pxAutoSavedMagicActor->m_nIdentity;
				ptTaretTilePos.x	= m_pxAutoSavedMagicActor->m_nPosX;
				ptTaretTilePos.y	= m_pxAutoSavedMagicActor->m_nPosY;
				stFeature			= m_pxAutoSavedMagicActor->m_stFeature;
			}
		}

		if ( m_pxMouseTargetActor )	
		{
			if ( m_bAutoMagic )
			{
				if ( m_pxMouseTargetActor->m_stFeature.bGender == _GENDER_MON )
					m_pxAutoSavedMagicActor = m_pxMouseTargetActor;
			}

			nTargetID			= m_pxMouseTargetActor->m_nIdentity;
			ptTaretTilePos.x	= m_pxMouseTargetActor->m_nPosX;
			ptTaretTilePos.y	= m_pxMouseTargetActor->m_nPosY;
			stFeature			= m_pxMouseTargetActor->m_stFeature;
		}
		m_xMyHero.OnSysKeyDown(wParam, lParam, m_ptMousePos, ptTaretTilePos, nTargetID, stFeature);
	}

	switch ( wParam )
	{
	case 'X':
	case 'x':
		if ( g_xGameProc.CanGameOut() )
		{
			g_xGameProc.m_xInterface.WindowActivate(_WNDIMGIDX_EXIT);
//			m_xGameMsgBox.CreateMsgBox(&m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_LOGOUT, _YESNO, g_xMsg.GetMsg(1065));
		}
		break;
	case 'Q':
	case 'q':
		if ( g_xGameProc.CanGameOut() )
		{
			g_xGameProc.m_xInterface.WindowActivate(_WNDIMGIDX_EXIT);
//			g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GAMEOVER, _YESNO, g_xMsg.GetMsg(2636));
		}
		break;
	case 'O':
	case 'o':
		{
			CHAR			szItemFile[MAX_PATH];
			ZeroMemory(szItemFile, MAX_PATH);
			g_xMainWnd.StringPlus(szItemFile, ".\\Data\\", m_xMyHero.m_szName, ".itms", "");
			DeleteFile(szItemFile);
			g_xGameProc.m_xInterface.m_xInventoryWnd.DeleteAllInvenItem();
			Sleep(500);

			g_xClientSocket.SendQueryMsg(CM_QUERYBAGITEMS);
		}
		break;
	}

	return 0L;
}


LRESULT CGameProcess::OnSysKeyUp(WPARAM wParam, LPARAM lParam)
{
	return 0L;
}


LRESULT CGameProcess::OnMove(WPARAM wParam, LPARAM lParam)
{
	INT	 nMoveGapX, nMoveGapY;
	RECT rc, rcEdit;

	rc = g_xMainWnd.m_rcWindow;

	GetWindowRect(g_xChatEditBox.GetSafehWnd(), &rcEdit);
//	ScreenToClient(g_xMainWnd.GetSafehWnd(), (POINT*)&rcEdit);
//	ScreenToClient(g_xMainWnd.GetSafehWnd(), (POINT*)&rcEdit+1);

	g_xMainWnd.OnMove(wParam, lParam);

	nMoveGapX = g_xMainWnd.m_rcWindow.left - rc.left;
	nMoveGapY = g_xMainWnd.m_rcWindow.top  - rc.top;

	MoveWindow(g_xChatEditBox.GetSafehWnd(), 
			   rcEdit.left+nMoveGapX, rcEdit.top+nMoveGapY, rcEdit.right-rcEdit.left, rcEdit.bottom-rcEdit.top, TRUE);

	return 0L;
	if ( m_xInterface.m_xNoticeEditWnd.m_hNoticeEdit )
	{
		GetWindowRect(m_xInterface.m_xNoticeEditWnd.m_hNoticeEdit, &rcEdit);
		MoveWindow(m_xInterface.m_xNoticeEditWnd.m_hNoticeEdit, 
				   rcEdit.left+nMoveGapX, rcEdit.top+nMoveGapY, rcEdit.right-rcEdit.left, rcEdit.bottom-rcEdit.top, TRUE);
	}

	if ( m_xInterface.m_xMarketUpWnd.mUserMarketUp_hDescEdit )
	{
		GetWindowRect(m_xInterface.m_xMarketUpWnd.mUserMarketUp_hDescEdit, &rcEdit);
		MoveWindow(m_xInterface.m_xMarketUpWnd.mUserMarketUp_hDescEdit, 
				   rcEdit.left+nMoveGapX, rcEdit.top+nMoveGapY, rcEdit.right-rcEdit.left, rcEdit.bottom-rcEdit.top, TRUE);
	}

	if ( m_xInterface.m_xMessengerWnd.mMessenger_hWriteMsg )
	{
		GetWindowRect(m_xInterface.m_xMessengerWnd.mMessenger_hWriteMsg, &rcEdit);
		MoveWindow(m_xInterface.m_xMessengerWnd.mMessenger_hWriteMsg, 
				   rcEdit.left+nMoveGapX, rcEdit.top+nMoveGapY, rcEdit.right-rcEdit.left, rcEdit.bottom-rcEdit.top, TRUE);
	}

	if ( m_xInterface.m_xMessengerWnd.mMessenger_hGiftMsg )
	{
		GetWindowRect(m_xInterface.m_xMessengerWnd.mMessenger_hGiftMsg, &rcEdit);
		MoveWindow(m_xInterface.m_xMessengerWnd.mMessenger_hGiftMsg, 
				   rcEdit.left+nMoveGapX, rcEdit.top+nMoveGapY, rcEdit.right-rcEdit.left, rcEdit.bottom-rcEdit.top, TRUE);
	}
	return 0L;
}


LRESULT CGameProcess::OnMouseMove(WPARAM wParam, LPARAM lParam)
{	
	m_ptMousePos.x = LOWORD(lParam);
	m_ptMousePos.y = HIWORD(lParam);

	m_xInterface.m_xMagicWnd.m_nShowMagicNum = -1;
	m_xInterface.m_xMagicShortcutWnd.mMSCutwnd_nShowMagicNum = -1;

	if ( m_xNotice.IsActive() )
	{
		m_xNotice.MoveWnd(m_ptMousePos);
		return 0L;
	}

/*	for ( int ii = 0; ii < 1; ii++ )
	{
		CMagic* pxMagic;
		POINT ptPos = {m_xMyHero.m_nPosX + GetRandomNum(-10, 10), m_xMyHero.m_nPosY + GetRandomNum(-10, 10)};
		pxMagic = new CMagic;
//		if ( pxMagic->CreateMagic(_SKILL_HANGMAJINBUB, m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, ptPos.x, ptPos.y) )
//		if ( pxMagic->CreateMagic(_SKILL_DEJIWONHO, m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, ptPos.x, ptPos.y) )
		if ( pxMagic->CreateMagic(_SKILL_LIGHTENING, m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, m_ptCurrTile.x, m_ptCurrTile.y) )
		{
			m_xMagicList.Insert (pxMagic);						
		}
		else
		{
			delete pxMagic;
		}

		if ( ii == 1 )
		{
			return 0L;
		}
	}
*/
	m_xGameMsgBox.OnMouseMove(m_ptMousePos);

	if ( m_bRender == FALSE )
	{
		return 0L;
	}

	m_ptCurrTile.x = m_xMap.m_nStartViewTileX + (m_ptMousePos.x - m_xMap.m_nViewPosX) / TILE_WIDTH;
	m_ptCurrTile.y = m_xMap.m_nStartViewTileY + (m_ptMousePos.y - m_xMap.m_nViewPosY) / TILE_HEIGHT;

	m_xInterface.OnMouseMove(m_ptMousePos);

	return 0L;
}


LRESULT CGameProcess::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{	
	m_ptMousePos.x = LOWORD(lParam);
	m_ptMousePos.y = HIWORD(lParam);

	if ( m_xNotice.IsActive() )
	{
		m_xNotice.OnButtonDown(m_ptMousePos);
		return 0L;
	}

	if ( m_xGameMsgBox.OnLButtonDown(m_ptMousePos) )
	{
		return 0L;
	}

	if ( !m_bRender )		
	{
		return 0L;
	}

	if ( m_dwInputDelayTime > 0 )
	{
		return 0L;
	}

	if ( m_bDiceModeActive )
	{
		return 0L;
	}

	m_ptCurrTile.x = m_xMap.m_nStartViewTileX + (m_ptMousePos.x - m_xMap.m_nViewPosX) / TILE_WIDTH;
	m_ptCurrTile.y = m_xMap.m_nStartViewTileY + (m_ptMousePos.y - m_xMap.m_nViewPosY) / TILE_HEIGHT;

	// 1. 인터페이스.
	if ( m_xInterface.OnLButtonDown(m_ptMousePos) )
	{
		return 0L;
	}

	if ( PtInRect(&m_xInterface.m_rcMain, m_ptMousePos ) )
	{
		return 0L;
	}

	// 2. 아이템을 떨어뜨리기.
	if ( m_xInterface.m_stCommonItem.bSetted && !m_xInterface.m_stCommonItem.bWaitResponse && !m_xInterface.m_stCommonItem.bIsEquipItem)
	{
		DWORD	dwCount = m_xInterface.m_stCommonItem.xItem.m_stItemInfo.wAmount_GB;

		if ( !strcmp(m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(1050)) )
		{
			m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_DROPGOLD, _YESNO, g_xMsg.GetMsg(1415), TRUE);
			ZeroMemory(&m_xInterface.m_stCommonItem, sizeof(COMMONITEMSET));
		}
		else if (m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.bThrow >= _MULTIPLE_TYPE_ITEM && dwCount > 1)
		{
			if ( !m_xInterface.m_stCommonItem.bIsBeltItem && !m_xInterface.m_stCommonItem.bIsUtilItem )
				m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_DROPMULTIPLEITEM, _YESNO, g_xMsg.GetMsg(1416), TRUE);
		}
		else
		{
			if (m_xInterface.m_stCommonItem.bIsDealItem)
			{
				m_xInterface.m_xExchangeWnd.SetDealFromCommon(0, 0, &m_xInterface.m_stCommonItem);
			}
			else
			{
				if (!m_xInterface.m_stCommonItem.bIsBeltItem)
				{
					CHAR szTemp[MAX_PATH];
					sprintf( szTemp, g_xMsg.GetMsg(1526), m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName );
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_DROPITEM, _YESNO, szTemp, FALSE);
//					g_xClientSocket.SendItemIndex(CM_DROPITEM, m_xInterface.m_stCommonItem.xItem.m_stItemInfo.nMakeIndex, m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName);
//					m_xInterface.m_stCommonItem.bWaitResponse = TRUE;
				}
			}
		}
		return 0L;
	}

	// 3. 아이템 줍기.
	LPGROUNDITEM	pstItem;

	INT nPosX = m_ptCurrTile.x - m_xMap.m_nStartViewTileX;
	INT nPosY = m_ptCurrTile.y - m_xMap.m_nStartViewTileY;

	for ( INT nObjCnt = 0; nObjCnt < _MAX_CELL_OBJ; nObjCnt++ )
	{
		pstItem = m_stMemMappedID[nPosY][nPosX].pstItem[nObjCnt];
		if ( pstItem )
		{
			if ( pstItem->nTileX == m_ptCurrTile.x && pstItem->nTileY == m_ptCurrTile.y && pstItem->nTileX == m_xMyHero.m_nPosX && pstItem->nTileY == m_xMyHero.m_nPosY )
			{
				// 말을 타고 있을 때는 아이템을 주울 수 없다 2006.10.26
				if( g_xGameProc.m_xMyHero.m_stFeatureEx.bHorse != _HORSE_NONE )
					return 0L;
				
				INT nItemCnt;
				INT	nTotalItem  = 0;
				for ( nItemCnt = 0; nItemCnt < _MAX_INVEN_ITEM; nItemCnt++ )
				{
					if ( g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nItemCnt].bSetted )
					{
						nTotalItem++;
					}
				}
				
				if ( !strncmp(pstItem->szItemName, g_xMsg.GetMsg(1050), 4 ) || (nTotalItem < _MAX_INVEN_ITEM) || pstItem->nThrow >= 2 )
				{
					if ( (nTotalItem >= _MAX_INVEN_ITEM) && pstItem->nThrow >= 2 )
					{						
						if ( m_xInterface.m_xInventoryWnd.FindInvenItem(pstItem->wLooks) )
						{
							g_xClientSocket.SendPickUp(pstItem->nTileX, pstItem->nTileY);
						}
						else
						{
							m_xInterface.m_xClientSysMsg.AddSysMsg(g_xMsg.GetMsg(1417));
						}
					}
					else
					{
						g_xClientSocket.SendPickUp(pstItem->nTileX, pstItem->nTileY);
					}
				}
				else
				{
					m_xInterface.m_xClientSysMsg.AddSysMsg(g_xMsg.GetMsg(1417));
				}
				return 0L;
			}
		}
		else
		{
			break;
		}
	}
	// 4. 캐릭터의 입력.
	if ( m_pxMouseTargetActor && !m_pxMouseTargetActor->m_bIsDead )
	{
		POINT ptTaretTilePos;

		m_pxSavedTargetActor = m_pxMouseTargetActor;	// 공격대상 Actor정하기.

#ifdef _DEBUG
		if ( m_bAutoTarget )
		{
			m_pxAutoSavedTargetActor = m_pxMouseTargetActor;
		}
#endif
		
		ptTaretTilePos.x = m_pxMouseTargetActor->m_nPosX;
		ptTaretTilePos.y = m_pxMouseTargetActor->m_nPosY;
		if ( m_pxMouseTargetActor->m_stFeature.bGender == _GENDER_NPC || m_pxMouseTargetActor->m_stFeature.bGender == _GENDER_FLAG )
		{
			if ( m_dwNPCClickTick - timeGetTime() > 500 )
			{
				if ( m_xInterface.m_xNPCWnd.GetGameWndActive() == FALSE && m_xInterface.m_xNPCWnd.m_nNpcId == -1)
				{
					m_xInterface.m_xNPCWnd.m_nNpcId = m_pxMouseTargetActor->m_nIdentity;
					g_xClientSocket.SendNPCClick(m_pxMouseTargetActor->m_nIdentity);
				}
				m_dwNPCClickTick = timeGetTime();
			}
			m_pxSavedTargetActor = NULL;
		}
		else
		{
			if ( HIBYTE(GetKeyState(VK_SHIFT)) || m_pxMouseTargetActor->m_stFeature.bGender == _GENDER_MON  || m_bAttackUser )
			{
				// 경비병도 안때리게.
				BOOL bIsGuard = FALSE;
				BYTE bDress   = m_pxMouseTargetActor->m_stFeature.bDress;

				if ( bDress ==  86 || bDress == 113 || bDress == 114 || 
					 bDress == 115 || bDress == 165 || bDress == 166 || bDress == 26 )
				{
					bIsGuard = TRUE;
				}

				// 열린 사북성문 안 때리게.
				WORD wDress = MAKEWORD(m_pxMouseTargetActor->m_stFeature.bDress, m_pxMouseTargetActor->m_stFeature.bHair);
				if ( (wDress  == 530 || wDress  == 531 || wDress  == 532 || wDress  == 533 /*성훈씨*/) && m_pxMouseTargetActor->m_bCurrDir == 7 )
				{
					bIsGuard = TRUE;
				}

				if ( !bIsGuard /*&& !strchr(m_pxMouseTargetActor->m_szName, '(') */)
				{
					BOOL bIsDead = FALSE;
					if ( m_pxMouseTargetActor->m_stFeature.bGender == _GENDER_MAN || m_pxMouseTargetActor->m_stFeature.bGender == _GENDER_WOMAN )
					{
						if ( m_pxMouseTargetActor->m_bCurrMtn == _MT_DIE || m_pxMouseTargetActor->m_bIsDead )
						{
							bIsDead = TRUE;
						}
					}
					else if ( m_pxMouseTargetActor->m_stFeature.bGender == _GENDER_MON )
					{
						if ( m_pxMouseTargetActor->m_bCurrMtn == _MT_MON_DIE || m_pxMouseTargetActor->m_bIsDead )
						{
							bIsDead = TRUE;
						}
						else if ( HIBYTE(GetKeyState(VK_SHIFT)) )
						{
							m_pxSavedTargetActor = NULL;
						}
					}

					m_xMyHero.OnLButtonDown(m_ptMousePos, m_pxMouseTargetActor->m_nIdentity, bIsDead, &ptTaretTilePos);
				}
			}
			else if ( m_pxMouseTargetActor == &m_xMyHero )
			{
				m_pxSavedTargetActor = NULL;
				m_xMyHero.OnLButtonDown(m_ptMousePos);
			}
			else
			{
				m_xMyHero.OnLButtonDown(m_ptMousePos);
			}
		}
	}
	else
	{
		m_pxSavedTargetActor = NULL;
		m_xMyHero.OnLButtonDown(m_ptMousePos);
	}

	return 0L;
}


LRESULT CGameProcess::OnRButtonDown(WPARAM wParam, LPARAM lParam)
{	
	m_ptMousePos.x = LOWORD(lParam);
	m_ptMousePos.y = HIWORD(lParam);

	if ( m_xGameMsgBox.OnRButtonDown(m_ptMousePos) )
	{
		return 0L;
	}

	if ( m_bRender == FALSE )
	{
		return 0L;
	}

	m_ptCurrTile.x = m_xMap.m_nStartViewTileX + (m_ptMousePos.x - m_xMap.m_nViewPosX) / TILE_WIDTH;
	m_ptCurrTile.y = m_xMap.m_nStartViewTileY + (m_ptMousePos.y - m_xMap.m_nViewPosY) / TILE_HEIGHT;

	if ( m_pxSavedTargetActor && 
		 (m_pxSavedTargetActor->m_stFeature.bGender  == _GENDER_MON ||
		 ((m_pxSavedTargetActor->m_stFeature.bGender == _GENDER_MAN || m_pxSavedTargetActor->m_stFeature.bGender == _GENDER_WOMAN) && 
		  (m_pxSavedTargetActor->m_dwNameClr == RGB(30, 17, 0)		))) )
	{
		m_pxSavedTargetActor = NULL;
	}

	if ( HIBYTE(GetKeyState(VK_MENU)) )
	{
		if ( m_pxMouseTargetActor )
		{
			if ( m_pxMouseTargetActor->m_stFeature.bGender == _GENDER_MAN || m_pxMouseTargetActor->m_stFeature.bGender == _GENDER_WOMAN )
			{
				BOOL			bFind = FALSE;
				CGroupMember*	pGroupMember = NULL;
				CListNode <	CGroupMember > *pNode;

				if ( g_xGameProc.m_xInterface.m_xGroupWnd.m_xGroupList.GetCount() )
				{
					for ( pNode = g_xGameProc.m_xInterface.m_xGroupWnd.m_xGroupList.GetHead(); pNode; pNode = pNode->GetNext() )
					{
						pGroupMember = pNode->GetData();

						if ( pGroupMember )
						{
							if ( strcmp( pGroupMember->szMemberName ,m_pxMouseTargetActor->m_szName ) == 0 )
								bFind = TRUE;
						}
					}
				}

				if ( bFind )
					g_xClientSocket.SendDelGroupMember((CHAR*)m_pxMouseTargetActor->m_szName);
				else
					g_xClientSocket.SendAddGroupMember((CHAR*)m_pxMouseTargetActor->m_szName);
				return 0L;
			}
		}
	}

	if ( m_xInterface.OnRButtonDown(m_ptMousePos) )
	{
		return 0L;
	}

	if ( PtInRect(&m_xInterface.m_rcMain, m_ptMousePos ) )
	{
		return 0L;
	}

	if ( m_bDiceModeActive )
	{
		return 0L;
	}

	if ( GetKeyState(VK_CONTROL) & 0x80 )
	{
		if ( m_pxMouseTargetActor && m_pxMouseTargetActor->m_nIdentity != m_xMyHero.m_nIdentity )
		{
			if ( (m_pxMouseTargetActor->m_stFeature.bGender == _GENDER_MAN || m_pxMouseTargetActor->m_stFeature.bGender == _GENDER_WOMAN) && 
				 !m_pxMouseTargetActor->m_bIsDead )
			{
				g_xClientSocket.SendQueryUserState(m_pxMouseTargetActor->m_nIdentity, m_pxMouseTargetActor->m_nPosX, m_pxMouseTargetActor->m_nPosY);
				return 0L;
			}
		}
	}

	if ( !strcmp(m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(1050)) )
	{
		ZeroMemory(&m_xInterface.m_stCommonItem, sizeof(COMMONITEMSET));
		return 0L;
	}

	m_xMyHero.OnRButtonDown(m_ptMousePos);

	return 0L;
}


LRESULT CGameProcess::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	m_ptMousePos.x = LOWORD(lParam);
	m_ptMousePos.y = HIWORD(lParam);

	if ( m_xNotice.IsActive() )
	{
		if ( m_xNotice.OnButtonUp(m_ptMousePos) )
		{
			m_xNotice.HideMessageBox();
			m_bNoticeCehcked = TRUE;		
			m_bFateState = 1;
			m_dwFadeTime = 0;
		}
		return 0L;
	}

	if ( m_xGameMsgBox.OnLButtonUp(m_ptMousePos) )
	{
		return 0L;
	}

	if ( m_bRender == FALSE )
	{
		return 0L;
	}

	if ( m_bDiceModeActive )
	{
		return 0L;
	}

	m_ptCurrTile.x = m_xMap.m_nStartViewTileX + (m_ptMousePos.x - m_xMap.m_nViewPosX) / TILE_WIDTH;
	m_ptCurrTile.y = m_xMap.m_nStartViewTileY + (m_ptMousePos.y - m_xMap.m_nViewPosY) / TILE_HEIGHT;

	m_xInterface.OnLButtonUp(m_ptMousePos);

	return 0L;
}


LRESULT CGameProcess::OnRButtonUp(WPARAM wParam, LPARAM lParam)
{
	m_ptMousePos.x = LOWORD(lParam);
	m_ptMousePos.y = HIWORD(lParam);

	if ( m_bRender == FALSE )
	{
		return FALSE;
	}

	if ( m_bDiceModeActive )
	{
		return 0L;
	}

	m_ptCurrTile.x = m_xMap.m_nStartViewTileX + (m_ptMousePos.x - m_xMap.m_nViewPosX) / TILE_WIDTH;
	m_ptCurrTile.y = m_xMap.m_nStartViewTileY + (m_ptMousePos.y - m_xMap.m_nViewPosY) / TILE_HEIGHT;

	return 0L;
}


LRESULT CGameProcess::OnKeyUp(WPARAM wParam, LPARAM lParam)
{
	if ( m_bRender == FALSE) 
	{
		return FALSE;
	}

	m_xInterface.OnKeyUp(wParam, lParam);

	return 0L;
}


LRESULT CGameProcess::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	// 게임종료 - 키보드로
	// by eriastoa 2006.04.06
#ifdef _TEST_SERVER_DEBUG
	if ( GetAsyncKeyState( VK_CONTROL ) )
	{
		if( GetAsyncKeyState( VK_ESCAPE ) )
		{
			WSACleanup();
			LoadCredit();

			if ( g_xMainWnd.GetScreenMode() & _DXG_SCREENMODE_WINDOW )
			{
				if ( FAILED(g_xMainWnd.ResetDXG(640, 480, 16, _DXG_SCREENMODE_WINDOW, _DXG_DEVICEMODE_PRIMARY|_DXG_DEVICEMODE_D3D)) )
				{
					MessageBox(g_xMainWnd.GetSafehWnd(), TEXT("DirectDraw RESETUP failed!!!") TEXT("The Program will now exit."), TEXT("MirDXG"), MB_ICONERROR | MB_OK);
				}
			}
			else
			{
				if ( FAILED(g_xMainWnd.ResetDXG(640, 480, 16, _DXG_SCREENMODE_FULLSCREEN, _DXG_DEVICEMODE_PRIMARY|_DXG_DEVICEMODE_D3D)) )
				{
					MessageBox(g_xMainWnd.GetSafehWnd(), TEXT("DirectDraw RESETUP failed!!!") TEXT("The Program will now exit."), TEXT("MirDXG"), MB_ICONERROR | MB_OK);
				}
			}

			return 0L;
		}
	}
#endif








	INT		nTargetID		= 0;
	POINT	ptTaretTilePos	= {0, 0};
	FEATURE stFeature;
	ZeroMemory(&stFeature, sizeof(FEATURE));

	if ( m_bCreditShow )
	{
		SendMessage(g_xMainWnd.GetSafehWnd(), WM_DESTROY, NULL, NULL);
	}

	if ( m_xNotice.IsActive() )
	{
		if ( m_xNotice.OnKeyDown(wParam, lParam) )
		{
			m_xNotice.HideMessageBox();
			m_bNoticeCehcked = TRUE;		
			m_bFateState = 1;
			m_dwFadeTime = 0;
		}
		return 0L;
	}

	if ( m_xGameMsgBox.OnKeyDown(wParam, lParam) )
	{
		return 0L;
	}

	if ( !m_bRender )		
	{
		return 0L;
	}

	if ( m_xInterface.OnKeyDown(wParam, lParam) )
	{
		return 0L;
	}

	if ( m_pxAutoSavedMagicActor )
	{
		if ( NeedAutoTarget( wParam ) )
		{
			nTargetID			= m_pxAutoSavedMagicActor->m_nIdentity;
			ptTaretTilePos.x	= m_pxAutoSavedMagicActor->m_nPosX;
			ptTaretTilePos.y	= m_pxAutoSavedMagicActor->m_nPosY;
			stFeature			= m_pxAutoSavedMagicActor->m_stFeature;
		}
	}

	if ( m_pxMouseTargetActor )	
	{
		if ( !m_pxMouseTargetActor->m_bIsDead || m_pxMouseTargetActor->m_stFeature.bGender != _GENDER_MON )
		{
			if ( m_bAutoMagic )
			{
				if ( m_pxMouseTargetActor->m_stFeature.bGender == _GENDER_MON )
					m_pxAutoSavedMagicActor = m_pxMouseTargetActor;
			}

			nTargetID			= m_pxMouseTargetActor->m_nIdentity;
			ptTaretTilePos.x	= m_pxMouseTargetActor->m_nPosX;
			ptTaretTilePos.y	= m_pxMouseTargetActor->m_nPosY;
			stFeature			= m_pxMouseTargetActor->m_stFeature;
		}
	}

#ifdef _DEBUG
	if ( m_bAutoTarget && m_pxAutoSavedTargetActor )
	{
		nTargetID			= m_pxAutoSavedTargetActor->m_nIdentity;
		ptTaretTilePos.x	= m_pxAutoSavedTargetActor->m_nPosX;
		ptTaretTilePos.y	= m_pxAutoSavedTargetActor->m_nPosY;
		stFeature			= m_pxAutoSavedTargetActor->m_stFeature;
	}
#endif

	m_xMyHero.OnKeyDown(wParam, lParam, m_ptMousePos, ptTaretTilePos, nTargetID, stFeature);

	if ( HIBYTE(GetKeyState('M')) )
	{
		if ( m_xMyHero.m_bCurrMtn == _MT_STAND || m_xMyHero.m_bCurrMtn == _MT_HORSESTAND )
		{
			if ( m_xMyHero.m_stFeatureEx.bHorse == _HORSE_NONE )
			{
				g_xClientSocket.SendSay(g_xMsg.GetMsg(1418));
			}
			else
			{
				g_xClientSocket.SendSay(g_xMsg.GetMsg(1419));
			}
			m_dwInputDelayTime	   = 1000;
			m_dwCurrInputDelayTime = 0;		

			return 0L;
		}		
	}
/*
	if ( HIBYTE(GetKeyState('I')) )
	{
		m_bViewMonInfo = !m_bViewMonInfo;
		DWORD dwBack = GetChatColor(_CHAT_COLOR4);
		DWORD dwFont = GetChatColor(_CHAT_COLOR3);
		if ( m_bViewMonInfo )
		{
			m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(1420));
		}
		else
		{
			m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(1421));
		}
		return 0L;
	}
*/
	switch ( wParam )
	{
		case 220:
		{					// '\'
			m_bAttackUser  == FALSE ? m_bAttackUser  = TRUE : m_bAttackUser  = FALSE;
			DWORD dwFont = GetChatColor(_CHAT_COLOR3);
			DWORD dwBack = GetChatColor(_CHAT_COLOR8);
			if ( m_bAttackUser )
				m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(1515));
			else
				m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(1516));
		}
		break;
		case 187:			// =
		{
			m_bDrawMagicLight == FALSE ? m_bDrawMagicLight = TRUE : m_bDrawMagicLight = FALSE;
			DWORD dwFont = GetChatColor(_CHAT_COLOR3);
			DWORD dwBack = GetChatColor(_CHAT_COLOR8);
			if ( m_bDrawMagicLight )
				m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(1518));
			else
				m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(1517));
		}
		break;
		case 'h':
		case 'H':
		{
			//대인공격 방법
			if ( HIBYTE(GetKeyState(VK_CONTROL)) )
			{
				g_xClientSocket.SendSay (g_xMsg.GetMsg(1422));
			}
			break;
		}
		case 'a':
		case 'A':
		{
			//대인공격 방법
			if ( HIBYTE(GetKeyState(VK_CONTROL)) )
			{
				g_xClientSocket.SendSay (g_xMsg.GetMsg(1423));
			}
			break;
		}
	/*	case 'f':
		case 'F':
		{
			//폰트바꾸기.
			if ( HIBYTE(GetKeyState(VK_CONTROL)) )
			{
				DWORD dwFont = GetChatColor(_CHAT_COLOR4);
				DWORD dwBack = GetChatColor(_CHAT_COLOR3);
				m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(1424));
			}
			break;
		}
	*/	case VK_RETURN:
		case VK_SPACE:
		{
			m_xInterface.m_xChatWnd.ActiveEditBox();
			break;
		}
		case 'U':
		{
			if ( m_bDebugInfo )
			{
				DWORD dwFogColor;

				dwFogColor = 0;
				m_bFogState++;

				if ( m_bFogState > _FOGSTATE_DAWN )			m_bFogState = _FOGSTATE_DAY;

				switch ( m_bFogState )
				{
				case _FOGSTATE_DAY:
					{
						m_fDarkRate = 255.0f;
						dwFogColor = RGB(m_fDarkRate, m_fDarkRate, m_fDarkRate);
						break;
					}
				case _FOGSTATE_NIGHT:
					{
						m_fDarkRate = 15.0f;
						dwFogColor = RGB(m_fDarkRate, m_fDarkRate, m_fDarkRate);
						break;
					}
				case _FOGSTATE_DAWN:
					{
						m_fDarkRate = 85.0f;
						dwFogColor = RGB(m_fDarkRate, m_fDarkRate, m_fDarkRate);
						break;
					}
				}

				m_xLightFog.ChangeLightColor(dwFogColor);
			}			
			break;
		}
	}			

	return 0L;
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 유저 디파인 메시지관련 함수.
LRESULT CGameProcess::OnMsgInputted(WPARAM wParam, LPARAM lParam)
{
	if ( m_xInterface.OnMsgInputted(wParam, lParam) )
	{
		return 0L;
	}

	if ( m_xInterface.m_xChatWnd.GetGameWndActive() )
	{
		if ( g_xGameProc.m_xInterface.m_xChatWnd.mChat_bLargeChat == FALSE )
			m_xInterface.WindowActivate(_WND_ID_CHAT);
	}

	if ( !strcmp(g_xChatEditBox.m_szInputMsg, g_xMsg.GetMsg(1425)) )
	{
		if ( m_xInterface.m_xGuildWnd.m_bIsGM )
		{
			CHAR pszMsg[MAX_PATH];
			ZeroMemory(pszMsg, MAX_PATH);
			sprintf(pszMsg, g_xMsg.GetMsg(1426), m_xInterface.m_xGuildWnd.m_szGuildName);
			m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GAME, _YESNO, pszMsg, TRUE, -1, -1, CM_GUILDADDMEMBER);
		}
		else
		{
			m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GAME, _OK, g_xMsg.GetMsg(1427));
		}
		ZeroMemory(g_xChatEditBox.m_szInputMsg, sizeof(g_xChatEditBox.m_szInputMsg));
		return 0L;
	}

#ifdef _DEBUG
	if ( !strcmp(g_xChatEditBox.m_szInputMsg, "@showdebug") )
	{
		m_bDebugInfo = !m_bDebugInfo;
	}	
	// 커맨드 메시지.
	if ( wParam && m_bDebugInfo )
	{
		CommandAnalyze();
	}
#endif
	if ( !strcmp(g_xChatEditBox.m_szInputMsg, "@chatsave") )
	{
		m_bChatSave = !m_bChatSave;
	}
	else if ( !strcmp(g_xChatEditBox.m_szInputMsg, "@snow") )
	{
		m_bSnowOn = !m_bSnowOn;
	}

	if ( g_xChatEditBox.m_szInputMsg[0] == '/' )
	{
		DWORD dwBack = GetChatColor(_CHAT_COLOR1);
		DWORD dwFont = GetChatColor(_CHAT_COLOR6);
		m_xInterface.MsgAdd(dwFont, dwBack, g_xChatEditBox.m_szInputMsg);

		m_xInterface.m_xChatWnd.SetCaputeString(g_xChatEditBox.m_szInputMsg);
		m_xInterface.AddHearList(&m_xInterface.m_xChatWnd.m_pszLastCapture[1]);
	}
	else if ( g_xChatEditBox.m_szInputMsg[0] == '#' )
	{
		m_xInterface.AddMacroList(&g_xChatEditBox.m_szInputMsg[1]);
		return 0L;
	}

	if ( !strcmp(g_xChatEditBox.m_szInputMsg, g_xMsg.GetMsg(1418)) || !strcmp(g_xChatEditBox.m_szInputMsg, g_xMsg.GetMsg(1428)) || !strcmp(g_xChatEditBox.m_szInputMsg, g_xMsg.GetMsg(1419)) )
	{
		// 잠시동안 입력을 막는다. 안 그러면 서버로부터 좌표재설정이 이루어진다.
		m_dwInputDelayTime = 300;
		m_dwCurrInputDelayTime = 0;
	}

	g_xClientSocket.SendSay(g_xChatEditBox.m_szInputMsg);

	ZeroMemory(g_xChatEditBox.m_szInputMsg, sizeof(g_xChatEditBox.m_szInputMsg));

	return 0L;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////








/******************************************************************************************************************

	기타 함수및 디버그용 함수.

*******************************************************************************************************************/
VOID CGameProcess::ShowStatus(INT nStartX, INT nStartY)
{
/*	TCHAR			szBuff1[MAX_PATH];
	sprintf(szBuff1, "마법갯수%d", m_xMagicList.GetCount());
	g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(), 0, 0, RGB(250, 250, 250), RGB(0, 0, 0), szBuff1);

	sprintf(szBuff1, "대지마법갯수%d", m_xGroundMagicList.GetCount());
	g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(), 0, 16, RGB(250, 250, 250), RGB(0, 0, 0), szBuff1);

*/	if ( m_bStatusView )
	{
		TCHAR			szBuff[MAX_PATH];
		sprintf(szBuff, "Curr Tile Pos x:%d, y:%d", m_ptCurrTile.x, m_ptCurrTile.y);
		g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(), nStartX, nStartY+10, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

/*		sprintf(szBuff, "Conn Sever IP : %s", g_szServerIP);
		g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(), nStartX, nStartY+25, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

		sprintf(szBuff, "Mouse Pos x:%d, y:%d", m_ptMousePos.x, m_ptMousePos.y);
		g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(), nStartX, nStartY+40, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

		sprintf(szBuff, "MYIDNUM:%x, %d", m_xMyHero.m_nIdentity, m_xMyHero.m_xPacketQueue.GetCount());
		g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(), nStartX, nStartY+55, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);
*/
/*		CActor*						pxActor = NULL;
		CListNode < CActor >		*pNode;
		for ( pNode = m_xActorList.GetHead(); pNode; pNode = pNode->GetNext() )
		{
			pxActor = pNode->GetData();

			if ( pxActor )
			{
				sprintf(szBuff, "IDNUM:%d, X:%d, Y:%d, MSGCNT:%d", pxActor->m_nIdentity, pxActor->m_nPosX, pxActor->m_nPosY, pxActor->m_xPacketQueue.GetCount());
				sprintf(szBuff, "ID:%d, Create:%d, Total Receive Packet:%d, Uncarried Packet:%d", pxActor->m_nIdentity, pxActor->m_nGenPacket, pxActor->m_nRecvPacketCnt, pxActor->m_xPacketQueue.GetCount());
				sprintf(szBuff, "ID:%d, Uncarried Packet:%d", pxActor->m_nIdentity, pxActor->m_xPacketQueue.GetCount());
				g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(), pxActor->m_nScrnPosX, pxActor->m_nScrnPosY, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);
			}
		}*/

/*		g_xMainWnd.UsedAndFreeMemoryCheck();
		sprintf(szBuff, "Total Texture:%d, Texture Remain:%d, Used Texture:%d", g_xMainWnd.m_dwTextureTotal, g_xMainWnd.m_dwTextureFree, g_xMainWnd.m_dwTextureTotal-g_xMainWnd.m_dwTextureFree);
		g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(), nStartX, nStartY+70, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

		sprintf(szBuff, "Total VRam:%d, VRam Remain:%d, Used VRam:%d", g_xMainWnd.m_dwVideoTotal, g_xMainWnd.m_dwVideoFree, g_xMainWnd.m_dwVideoTotal-g_xMainWnd.m_dwVideoFree);
		g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(), nStartX, nStartY+85, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);*/
	}

	if ( m_bShowFPS )
	{
		CWHDefProcess::ShowStatus(0, 0);
	}
}



VOID CGameProcess::CommandAnalyze()
{
	CHAR	szCommand[MAX_PATH];
	CHAR	szArg1[MAX_PATH];
	CHAR	szArg2[MAX_PATH];
	CHAR	szArg3[MAX_PATH];
	CHAR	szArg4[MAX_PATH];

	ZeroMemory(szCommand, MAX_PATH);
	ZeroMemory(szArg1, MAX_PATH);
	ZeroMemory(szArg2, MAX_PATH);
	ZeroMemory(szArg3, MAX_PATH);
	ZeroMemory(szArg4, MAX_PATH);

	sscanf(g_xChatEditBox.m_szInputMsg, "%[^ ]%*c %[^ ]%*c %[^ ]%*c %[^ ]%*c %[^ ]%*c", szCommand, szArg1, szArg2, szArg3, szArg4);

	INT nArg1;	INT nArg2;	INT nArg3;	INT nArg4;
	nArg1 = nArg2 = nArg3 = nArg4 = 0;

	if ( !strcmp(szCommand, "@grid") )
	{
		nArg1 = atoi(szArg1);
		switch ( nArg1 )
		{
		case 0:
			m_bCellView= !m_bCellView;
			break;
		case 1:
			m_bTileView = !m_bTileView;
			break;
		case 2:
			m_bObj1View = !m_bObj1View;
			break;
		case 3:
			m_bObj2View = !m_bObj2View;
			break;
		case 4:
			m_bStopPtView = !m_bStopPtView;
			break;
		}
	}
	else if ( !strcmp(szCommand, "@run") )
	{
		m_bRunTarget = !m_bRunTarget;
	}
	else if ( !strcmp(szCommand, "@reloadm") )
	{
		g_xSpriteInfo.SetInfo();		
	}
	else if ( !strcmp(szCommand, "@auto") )
	{
		m_bAutoTarget = !m_bAutoTarget;
	}
/*	else if ( !strcmp(szCommand, "@ID") )
	{
		nArg1 = atoi(szArg1);

		CActor* pxActor;

		if ( nArg1 )
		{
			pxActor = FindActor(nArg1);
		}
		else
		{
			pxActor = m_pxMouseTargetActor;
		}

		if ( pxActor )
		{
			m_xInterface.m_xClientSysMsg.AddSysMsg(g_xMsg.GetMsg(1429));

			CHAR					 szBuff[1000];
			CListNode < PACKETMSG >* pNodePacket;
			LPPACKETMSG				 lpPacket;

			INT nCnt = 0;

			for ( pNodePacket = pxActor->m_xRecvPacketList.GetHead(); pNodePacket; pNodePacket = pNodePacket->GetNext() )
			{
				lpPacket = pNodePacket->GetData();

				if ( lpPacket )
				{			
					nCnt++;

					sprintf(szBuff, "[%d] %s(%d), wIdent:%d, wParam:%d, wTag:%d", nCnt, pxActor->m_szName, pxActor->m_nIdentity, lpPacket->stDefMsg.wIdent, lpPacket->stDefMsg.wParam, lpPacket->stDefMsg.wTag);

					DWORD dwFont = GetChatColor(_CHAT_COLOR3);
					DWORD dwBack = GetChatColor(_CHAT_COLOR1);
					m_xInterface.MsgAdd(dwFont, dwBack, szBuff);
				}
			}
		}
	}*/
	else if ( !strcmp(szCommand, "@timechange") )
	{
		m_bFogState = (BYTE)atoi(szArg1);
		SetTimer(g_xMainWnd.GetSafehWnd(), _TIMER_ID, 50, NULL);
	}	
	else if ( !strcmp(szCommand, "@magic") )
	{
		m_xMyHero.m_nTestMagicID = atoi(szArg1);
	}
	else if ( !strcmp(szCommand, "@fps") )
	{
		m_bShowFPS = !m_bShowFPS;
	}
	else if ( !strcmp(szCommand, "@show") )
	{
		if ( !strcmp(szArg1, "rain") )
		{
			m_bShowRain = !m_bShowRain;
		}
		else if ( !strcmp(szArg1, "snow") )
		{
			m_bShowSnow = !m_bShowSnow;
		}
		else if ( !strcmp(szArg1, "fog") )
		{
			m_bShowMist = !m_bShowMist;
		}
		else if ( !strcmp(szArg1, "state") )
		{
			m_bStatusView = !m_bStatusView;
		}
	}
	else if ( !strcmp(szCommand, "@fix") )
	{
		if ( !strcmp(szArg1, "delay") )
		{
			nArg2 = atoi(szArg2);
			m_xMyHero.m_nDelay	= nArg2;
		}
	}	
	if ( !strcmp(szCommand, "@dresscolor") )
	{
		nArg1 = atoi(szArg1);
		nArg2 = atoi(szArg2);
		nArg3 = atoi(szArg3);
		
		WORD wColor = g_xMainWnd.ConvertColor24To16(RGB(nArg3, nArg2, nArg1));

		m_xMyHero.m_stFeatureEx.wDressColor = wColor;
	}	
	else if ( !strcmp(szCommand, "@speed") )
	{
		nArg1 = atoi(szArg1);
		m_xMyHero.m_shHitSpeed = (SHORT)nArg1;
	}	
	else if ( !strcmp(szCommand, "@npc") )
	{
		static int nNPC = 0;
		CActor* pxActor = NULL;

		nArg1 = atoi(szArg1);
		pxActor = new CNPC;
		CNPC* pxNPC = (CNPC*)pxActor;

		pxNPC->m_nIdentity = nNPC;
		FEATURE stFeature;
		stFeature.bGender = _GENDER_NPC;
		stFeature.bDress = (BYTE)nArg1;
		stFeature.bHair = 0;
		stFeature.bWeapon = 0;

		if ( pxNPC->Create(&m_xImage, &stFeature, _MT_STAND, (BYTE)GetRandomNum(0, 7), m_xMyHero.m_nPosX, m_xMyHero.m_nPosY-1) )
			m_xActorList.Insert (pxActor);

		nNPC++;
	}	
	else if ( !strcmp(szCommand, "@light") )
	{
		m_fTileLightRed = (FLOAT)atoi(szArg1);
		m_fTileLightGreen = (FLOAT)atoi(szArg2);
		m_fTileLightBlue = (FLOAT)atoi(szArg3);
	}	
	else if ( !strcmp(szCommand, "@shadow") )
	{
		m_bShadowABlend = !m_bShadowABlend;
		WORD wShadowClr;

		if ( m_bShadowABlend )
		{
			wShadowClr = g_xMainWnd.ConvertColor24To16(RGB(0, 0, 0));
		}
		else
		{
			wShadowClr = g_xMainWnd.ConvertColor24To16(RGB(20, 20, 20));
		}
			
		for ( INT nCnt = 0; nCnt < 800; nCnt++ )
		{
			m_wShadowClr[nCnt] = wShadowClr;
		}	

	}	
	else if ( !strcmp(szCommand, "@haircolor") )
	{
		nArg1 = atoi(szArg1);
		nArg2 = atoi(szArg2);
		nArg3 = atoi(szArg3);
		
		WORD wColor = g_xMainWnd.ConvertColor24To16(RGB(nArg3, nArg2, nArg1));
		m_xMyHero.m_stFeatureEx.wHairColor = wColor;
	}	
	else if ( !strcmp(szCommand, "@dress") )
	{
		nArg1 = atoi(szArg1);

		FEATURE stFeature = m_xMyHero.m_stFeature;
		stFeature.bDress = (BYTE)nArg1;
		m_xMyHero.ChangeFeature(stFeature, m_xMyHero.m_stFeatureEx);
	}	
	else if ( !strcmp(szCommand, "@weapon") )
	{
		nArg1 = atoi(szArg1);

		FEATURE stFeature = m_xMyHero.m_stFeature;
		stFeature.bWeapon = (BYTE)nArg1;

		m_xMyHero.ChangeFeature(stFeature, m_xMyHero.m_stFeatureEx);
	}	
	else if ( !strcmp(szCommand, "@hair") )
	{
		nArg1 = atoi(szArg1);

		FEATURE stFeature = m_xMyHero.m_stFeature;
		stFeature.bHair = (BYTE)nArg1;
		if ( stFeature.bHair > _MAX_HAIR )
			stFeature.bHair = _HAIR_NONE;

		m_xMyHero.ChangeFeature(stFeature, m_xMyHero.m_stFeatureEx);
	}	
}


VOID CGameProcess::RenderMapTileGrid()
{
	WORD	bCanMove = FALSE;
	INT		nObjCnt1 = 0;
	INT		nObjCnt2 = 0;

	INT		nObjFileIdx;
	INT		nFileIdx;
	INT		nImgIdx;

	RECT	rc;

	if ( m_bCellView || m_bTileView || m_bObj1View || m_bObj2View || m_bStopPtView )
	{
		for ( INT nXCnt = m_xMap.m_nStartViewTileX; nXCnt < m_xMap.m_nStartViewTileX+_VIEW_CELL_X_COUNT; nXCnt++ )
			for ( INT nYCnt = m_xMap.m_nStartViewTileY; nYCnt < m_xMap.m_nStartViewTileY+_VIEW_CELL_Y_COUNT_FOR_OBJ; nYCnt++ )
		{
			if ( nXCnt >= m_xMap.m_stMapFileHeader.shWidth || nYCnt >= m_xMap.m_stMapFileHeader.shHeight || nXCnt < 0 || nYCnt < 0 )
			{
				continue; 
			}

			INT nArrayNum = nYCnt + nXCnt*m_xMap.m_stMapFileHeader.shHeight;

			// Cell그리드 보여주기.
			if ( m_bCellView )
			{
				SetRect(&rc,
					   (nXCnt-m_xMap.m_nStartViewTileX)*_CELL_WIDTH +m_xMap.m_nViewPosX-m_xMap.m_nViewOffsetX,
					   (nYCnt-m_xMap.m_nStartViewTileY)*_CELL_HEIGHT+m_xMap.m_nViewPosY-m_xMap.m_nViewOffsetY,
					   (nXCnt-m_xMap.m_nStartViewTileX)*_CELL_WIDTH +m_xMap.m_nViewPosX+_CELL_WIDTH -m_xMap.m_nViewOffsetX,
					   (nYCnt-m_xMap.m_nStartViewTileY)*_CELL_HEIGHT+m_xMap.m_nViewPosY+_CELL_HEIGHT-m_xMap.m_nViewOffsetY);
				g_xMainWnd.DrawWithGDI(&rc, NULL, RGB(0, 255, 255), 1);
/*
				CHAR szBuf[MAX_PATH];
				if (m_xMap.m_pstCellInfo->bFlag > 3)
					INT tet = 0;

				INT nTest = (m_xMap.m_pstCellInfo[nYCnt + nXCnt*m_xMap.m_stMapFileHeader.shHeight].bFlag & 12) >> 2;
				sprintf(szBuf, "%d", nTest);
				g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(), 
				rc.left,
				rc.top,
				RGB(250, 250, 250), RGB(0, 0, 0), szBuf);
*/			}

			if ( m_bTileView )
			{
				// 타일그리드보여주기.
 				if( !( nXCnt % 2 ) && !( nYCnt % 2 ) && nYCnt < m_xMap.m_nStartViewTileY+_VIEW_CELL_Y_COUNT )
 				{
					nFileIdx= m_xMap.m_pstTileInfo[(nYCnt/2) + (nXCnt/2)*m_xMap.m_stMapFileHeader.shHeight/2].bFileIdx;
					nImgIdx = m_xMap.m_pstTileInfo[(nYCnt/2) + (nXCnt/2)*m_xMap.m_stMapFileHeader.shHeight/2].wTileIdx;

					// 맵데이타는 15개 단위로 세팅되있다.
					nFileIdx -= nFileIdx/15;

					// 타일 파일이 아니다.
					if ( nFileIdx % 14 < 3 || nFileIdx < 70 )
					{
						if( nFileIdx != 255 && nImgIdx != 65535 )
						{
							if ( g_xGameProc.m_xImage.m_xImageList[nFileIdx].NewSetIndex(nImgIdx) )
							{
								SetRect(&rc,
									   (nXCnt-m_xMap.m_nStartViewTileX)*_CELL_WIDTH +m_xMap.m_nViewPosX-m_xMap.m_nViewOffsetX,
									   (nYCnt-m_xMap.m_nStartViewTileY)*_CELL_HEIGHT+m_xMap.m_nViewPosY-m_xMap.m_nViewOffsetY,
									   (nXCnt-m_xMap.m_nStartViewTileX)*_CELL_WIDTH +m_xMap.m_nViewPosX+g_xGameProc.m_xImage.m_xImageList[nFileIdx].m_lpstNewCurrWilImageInfo->shWidth -m_xMap.m_nViewOffsetX,
									   (nYCnt-m_xMap.m_nStartViewTileY)*_CELL_HEIGHT+m_xMap.m_nViewPosY+g_xGameProc.m_xImage.m_xImageList[nFileIdx].m_lpstNewCurrWilImageInfo->shHeight-m_xMap.m_nViewOffsetY);
								g_xMainWnd.DrawWithGDI(&rc, NULL, RGB(255, 0, 0), 1);

								TCHAR szBuff[MAX_PATH];
	//							sprintf(szBuff, "[%d]%d%d", nObjCnt1, nXCnt, nYCnt);
								sprintf(szBuff, "%d %d", nFileIdx, nImgIdx);
								g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(), 
												   (nXCnt-m_xMap.m_nStartViewTileX)*_CELL_WIDTH +m_xMap.m_nViewPosX-m_xMap.m_nViewOffsetX,
												   (nYCnt-m_xMap.m_nStartViewTileY)*_CELL_HEIGHT+m_xMap.m_nViewPosY-m_xMap.m_nViewOffsetY,
												   RGB(0, 10, 10), RGB(0, 0, 0), szBuff);
							}
							else 
							{
								TCHAR szBuff[MAX_PATH];
	//							sprintf(szBuff, "[%d]%d%d", nObjCnt1, nXCnt, nYCnt);
								sprintf(szBuff, "%d %d", nFileIdx, nImgIdx);
								g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(), 
												   (nXCnt-m_xMap.m_nStartViewTileX)*_CELL_WIDTH +m_xMap.m_nViewPosX-m_xMap.m_nViewOffsetX,
												   (nYCnt-m_xMap.m_nStartViewTileY)*_CELL_HEIGHT+m_xMap.m_nViewPosY-m_xMap.m_nViewOffsetY,
												   RGB(0, 210, 10), RGB(0, 0, 0), szBuff);
							}
						}
					}
				}
			}

			if ( m_bObj1View )
			{
				// Obj1타일 그리드 보여주기.
				if ( m_xMap.m_pstCellInfo[nArrayNum].wFileIdx != 65535 )
				{
					if ( m_xMap.m_pstCellInfo[nArrayNum].wObj1 != 65535 )
					{
						nObjFileIdx = (m_xMap.m_pstCellInfo[nArrayNum].wFileIdx & 0XFF00) >> 8;
						nImgIdx		= m_xMap.m_pstCellInfo[nArrayNum].wObj1;

						// 맵데이타는 15개 단위로 세팅되있다.
						nObjFileIdx -= nObjFileIdx/15;

						if ( nObjFileIdx % 14 > 2 || nObjFileIdx < 70 )
						{
							if ( g_xGameProc.m_xImage.m_xImageList[nObjFileIdx].NewSetIndex(nImgIdx) )
							{
								SetRect(&rc,
									   (nXCnt-m_xMap.m_nStartViewTileX)*_CELL_WIDTH +m_xMap.m_nViewPosX-m_xMap.m_nViewOffsetX,
									   (nYCnt-m_xMap.m_nStartViewTileY)*_CELL_HEIGHT+m_xMap.m_nViewPosY-g_xGameProc.m_xImage.m_xImageList[nObjFileIdx].m_lpstNewCurrWilImageInfo->shHeight+_CELL_HEIGHT-m_xMap.m_nViewOffsetY,
									   (nXCnt-m_xMap.m_nStartViewTileX)*_CELL_WIDTH +m_xMap.m_nViewPosX+g_xGameProc.m_xImage.m_xImageList[nObjFileIdx].m_lpstNewCurrWilImageInfo->shWidth -m_xMap.m_nViewOffsetX,
									   (nYCnt-m_xMap.m_nStartViewTileY)*_CELL_HEIGHT+m_xMap.m_nViewPosY+g_xGameProc.m_xImage.m_xImageList[nObjFileIdx].m_lpstNewCurrWilImageInfo->shHeight-m_xMap.m_nViewOffsetY);

							}

							if ( PtInRect(&rc, m_ptMousePos) )
							{
								nObjCnt1++;
								g_xMainWnd.DrawWithGDI(&rc, NULL, RGB(255, 0, 255), 1);

								TCHAR szBuff[MAX_PATH];
	//							sprintf(szBuff, "[%d]%d%d", nObjCnt1, nXCnt, nYCnt);
								sprintf(szBuff, "%d %d", nXCnt, nYCnt);
								g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(), 
												   (nXCnt-m_xMap.m_nStartViewTileX)*_CELL_WIDTH +m_xMap.m_nViewPosX-m_xMap.m_nViewOffsetX,
												   (nYCnt-m_xMap.m_nStartViewTileY)*_CELL_HEIGHT+m_xMap.m_nViewPosY-g_xGameProc.m_xImage.m_xImageList[nObjFileIdx].m_lpstNewCurrWilImageInfo->shHeight+_CELL_HEIGHT-m_xMap.m_nViewOffsetY,
												   RGB(255, 0, 255), RGB(0, 0, 0), szBuff);
							}
						}
					}
				}
			}
			
			if ( m_bObj2View )
			{
				// Obj2타일 그리드 보여주기.
				if ( m_xMap.m_pstCellInfo[nArrayNum].wFileIdx != 65535 )
				{
					if ( m_xMap.m_pstCellInfo[nArrayNum].wObj2 != 65535 /*&& m_shObjTileViewState == 2*/ )
					{
						nObjFileIdx = (m_xMap.m_pstCellInfo[nArrayNum].wFileIdx & 0XFF);
						nImgIdx		= m_xMap.m_pstCellInfo[nArrayNum].wObj2;

						// 맵데이타는 15개 단위로 세팅되있다.
						nObjFileIdx -= nObjFileIdx/15;

						if ( nObjFileIdx % 14 > 2 || nObjFileIdx < 70 )
						{
							if ( g_xGameProc.m_xImage.m_xImageList[nObjFileIdx].NewSetIndex(nImgIdx) )
							{
								SetRect(&rc,
									   (nXCnt-m_xMap.m_nStartViewTileX)*_CELL_WIDTH +m_xMap.m_nViewPosX-m_xMap.m_nViewOffsetX,
									   (nYCnt-m_xMap.m_nStartViewTileY)*_CELL_HEIGHT+m_xMap.m_nViewPosY-g_xGameProc.m_xImage.m_xImageList[nObjFileIdx].m_lpstNewCurrWilImageInfo->shHeight+_CELL_HEIGHT-m_xMap.m_nViewOffsetY,
									   (nXCnt-m_xMap.m_nStartViewTileX)*_CELL_WIDTH +m_xMap.m_nViewPosX+g_xGameProc.m_xImage.m_xImageList[nObjFileIdx].m_lpstNewCurrWilImageInfo->shWidth -m_xMap.m_nViewOffsetX,
									   (nYCnt-m_xMap.m_nStartViewTileY)*_CELL_HEIGHT+m_xMap.m_nViewPosY+_CELL_HEIGHT-m_xMap.m_nViewOffsetY);
							}

							if ( PtInRect(&rc, m_ptMousePos) )
							{
								nObjCnt2++;
								g_xMainWnd.DrawWithGDI(&rc, NULL, RGB(0, 255, 255), 1);

								TCHAR szBuff[MAX_PATH];
	//							sprintf(szBuff, "[%d]%d%d", nObjCnt2, nXCnt, nYCnt);
								sprintf(szBuff, "%d %d", nXCnt, nYCnt);
								g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(), 
												   (nXCnt-m_xMap.m_nStartViewTileX)*_CELL_WIDTH +m_xMap.m_nViewPosX-m_xMap.m_nViewOffsetX,
												   (nYCnt-m_xMap.m_nStartViewTileY)*_CELL_HEIGHT+m_xMap.m_nViewPosY-g_xGameProc.m_xImage.m_xImageList[nObjFileIdx].m_lpstNewCurrWilImageInfo->shHeight+_CELL_HEIGHT-m_xMap.m_nViewOffsetY,
												   RGB(0, 255, 255), RGB(0, 0, 0), szBuff);
							}
						}
					}
				}
			}

			if ( m_bStopPtView )
			{
				bCanMove  = m_xMap.GetTileAttribute(nXCnt, nYCnt);
				if ( bCanMove != _CAN_WALK && m_bStopPtView )
				{
					SetRect(&rc,
						   (nXCnt-m_xMap.m_nStartViewTileX)*_CELL_WIDTH +m_xMap.m_nViewPosX-m_xMap.m_nViewOffsetX,
						   (nYCnt-m_xMap.m_nStartViewTileY)*_CELL_HEIGHT+m_xMap.m_nViewPosY-m_xMap.m_nViewOffsetY,
						   (nXCnt-m_xMap.m_nStartViewTileX)*_CELL_WIDTH +m_xMap.m_nViewPosX+_CELL_WIDTH -m_xMap.m_nViewOffsetX,
						   (nYCnt-m_xMap.m_nStartViewTileY)*_CELL_HEIGHT+m_xMap.m_nViewPosY+_CELL_HEIGHT-m_xMap.m_nViewOffsetY);
					g_xMainWnd.DrawWithGDI(&rc, NULL, RGB(255, 255, 0), 1);
				}
			}

/*			if ( ( m_xMap.m_pstCellInfo[nArrayNum].wLigntNEvent & 0X07 ) == 2 )
			{
				SetRect(&rc,
					   (nXCnt-m_xMap.m_nStartViewTileX)*_CELL_WIDTH +m_xMap.m_nViewPosX-m_xMap.m_nViewOffsetX,
					   (nYCnt-m_xMap.m_nStartViewTileY)*_CELL_HEIGHT+m_xMap.m_nViewPosY-m_xMap.m_nViewOffsetY,
					   (nXCnt-m_xMap.m_nStartViewTileX)*_CELL_WIDTH +m_xMap.m_nViewPosX+_CELL_WIDTH -m_xMap.m_nViewOffsetX,
					   (nYCnt-m_xMap.m_nStartViewTileY)*_CELL_HEIGHT+m_xMap.m_nViewPosY+_CELL_HEIGHT-m_xMap.m_nViewOffsetY);
				g_xMainWnd.DrawWithGDI(&rc, NULL, RGB(255, 255, 255), 2);
			}
*/
		}
	}
	for ( INT nXCnt = m_xMap.m_nStartViewTileX; nXCnt < m_xMap.m_nStartViewTileX+_VIEW_CELL_X_COUNT; nXCnt++ )
		for ( INT nYCnt = m_xMap.m_nStartViewTileY; nYCnt < m_xMap.m_nStartViewTileY+_VIEW_CELL_Y_COUNT_FOR_OBJ; nYCnt++ )
	{
		if ( nXCnt >= m_xMap.m_stMapFileHeader.shWidth || nYCnt >= m_xMap.m_stMapFileHeader.shHeight || nXCnt < 0 || nYCnt < 0 )
			continue; 

//		if ( m_xMap.GetDoor(nXCnt, nYCnt) )
		if ( !m_xMap.IsDoorOpen(nXCnt, nYCnt) )
		{
			SetRect(&rc,
				   (nXCnt-m_xMap.m_nStartViewTileX)*_CELL_WIDTH +m_xMap.m_nViewPosX-m_xMap.m_nViewOffsetX,
				   (nYCnt-m_xMap.m_nStartViewTileY)*_CELL_HEIGHT+m_xMap.m_nViewPosY-m_xMap.m_nViewOffsetY,
				   (nXCnt-m_xMap.m_nStartViewTileX)*_CELL_WIDTH +m_xMap.m_nViewPosX+_CELL_WIDTH -m_xMap.m_nViewOffsetX,
				   (nYCnt-m_xMap.m_nStartViewTileY)*_CELL_HEIGHT+m_xMap.m_nViewPosY+_CELL_HEIGHT-m_xMap.m_nViewOffsetY);
			g_xMainWnd.DrawWithGDI(&rc, NULL, RGB(255, 255, 255), 1);
		}
	}
}


LRESULT CGameProcess::DefMainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch ( uMsg )
	{
		case WM_HOTKEY:
		{
			if ( !m_bUseHotKey )
			{
				return 0L;
			}
			break;
		}
		case WM_CTLCOLOREDIT:
		{
			if ( (HWND)lParam == NULL )
			{
				return 0L;
			}

			if ( (HWND)lParam == g_xChatEditBox.GetSafehWnd() || (HWND)lParam == m_xInterface.m_xNoticeEditWnd.m_hNoticeEdit || 
				 (HWND)lParam == m_xInterface.m_xMarketUpWnd.mUserMarketUp_hDescEdit || (HWND)lParam == m_xInterface.m_xMessengerWnd.mMessenger_hWriteMsg ||
				 (HWND)lParam == m_xInterface.m_xMessengerWnd.mMessenger_hGiftMsg)
			{
				SetBkColor((HDC)wParam, RGB(30, 30, 30));
				SetTextColor((HDC)wParam, RGB(220, 220, 220));

				UnrealizeObject(m_hBrush);
				
				POINT pt;

				SetBrushOrgEx((HDC)wParam, 0, 0, &pt);

				return (LRESULT)m_hBrush;
			}

			break;
		}
		case WM_DESTROY:
			OnDestroy(wParam, lParam);
			break;
		case WM_TIMER:
			OnTimer(wParam, lParam);
			break;


// m_bRender Check 할 메시지함수들.
		case WM_MOUSEMOVE:
			OnMouseMove(wParam, lParam);
			break;
		case WM_LBUTTONDBLCLK:
			OnLButtonDoubleClick(wParam, lParam);
			break;
		case WM_LBUTTONDOWN:
			OnLButtonDown(wParam, lParam);
			break;
		case WM_RBUTTONDOWN:
			OnRButtonDown(wParam, lParam);
			break;
		case WM_KEYDOWN:
			OnKeyDown(wParam, lParam);
			break;
		case WM_KEYUP:
			OnKeyUp(wParam, lParam);
			break;
		case WM_LBUTTONUP:
			OnLButtonUp(wParam, lParam);
			break;
		case WM_RBUTTONUP:
			OnRButtonUp(wParam, lParam);
			break;
		case WM_SYSKEYDOWN:
			return OnSysKeyDown(wParam, lParam);
		case WM_SYSKEYUP:
			return OnSysKeyUp(wParam, lParam);
		case WM_MOUSEWHEEL:
			return OnWheel(wParam,lParam);
		case _WM_MSGBOX_RETURN:
			OnMsgBoxReturn(wParam, lParam);
			break;
		case _WM_USER_MSG_INPUTTED:
			return OnMsgInputted(wParam, lParam);

		case _WM_USER_MSG_CTRLNUM:
			return m_xInterface.CtrlNumPushed(wParam, lParam);

		case _WM_USER_MSG_ALTNUM:
			return m_xInterface.AltNumPushed(wParam, lParam);

		case WM_MOVE:
			OnMove(wParam, lParam);
			break;
		case ID_SOCKCLIENT_EVENT_MSG:
			g_xClientSocket.OnSocketMessage(wParam, lParam);
			break;
/*		case WM_NPROTECT_EXIT_TWO :
			{
				CHAR pszMsg[MAX_PATH];
				sprintf(pszMsg, "\r\n\r\n    %s\r\n    %s", g_xMsg.GetMsg(1430), g_xMsg.GetMsg(1411));
				m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GAMEOUT, _OK, pszMsg);
			}
			break;
*/		default:
			break;
	}

	g_SoundManager.SndmngrMessageProc(hWnd, uMsg, wParam, lParam);

//	if ( wParam != 91 )
		return CWHDefProcess::DefMainWndProc(hWnd, uMsg, wParam, lParam);
}

VOID CGameProcess::OnConnectToServer()
{
}


char* CGameProcess::OnMessageReceive( char *pBuf, int nLen )
{
/*	char *pStart = pBuf;
	char *pEnd	 = NULL;
	char *pTmp	= NULL;
	char *pTmp2 = NULL;
	char *pPacket = NULL;

	
	while(pTmp2 = (char*) memchr(pStart,'#',nLen))
	{
		//1. #을찾는다.
		pStart = (char*) memchr(pStart,'#',nLen);
		

		//2. #이 있으면 $를 찾는다.(없으면 걍 리턴)
		pTmp = (char*) memchr(pStart,'$',nLen);
		if(!pTmp) return pStart;

		
		//3. 그사이의 숫자값을 구한다. 전체길이가 nLen보다 작으면 return시킨다.
		int nEncodeLen = atoi(pStart+1);

		//pstart를 nEncode만큼 전진
		nLen = nLen - (pTmp - pStart + 1);//nLen - ( pTmp + nEncodeLen+2 - pStart);

		if ((nEncodeLen <=0) || (nEncodeLen > nLen)) return pStart;

		//4. nEncodeLen만큼만 내용을 전달.
		pPacket = (char*)malloc(nEncodeLen);
		memcpy(pPacket, pTmp+1, nEncodeLen);
		pPacket[nEncodeLen] = NULL;
		OnSocketMessageReceive(pPacket, nEncodeLen);
//		printf("%s\n", pPacket );

		
		if ( nLen < 0 )
			INT ntes = 0;
		nLen = nLen - nEncodeLen;
		pStart =  pTmp + nEncodeLen+2;
	}
	return pStart;
*/

	char *pStart = pBuf;
	char *pEnd	 = NULL;
	char *pNum	 = NULL;
	INT  nNewLen = 0;
	INT  nCnt = 0;

	while ( pEnd = (char *) memchr( pStart, '!', nLen ) )
	{
/*		*pEnd++ = '\0';

		if ( pNum = strchr(pStart, '$') )
			*pNum = '\0';
		else
			INT nt = 0;


		int nNum = atoi(pStart+1);
		nNewLen = strlen(pStart);
		pStart = pNum + 1;

		OnSocketMessageReceive( pStart, nNum);

//		nLen -= pEnd - pStart;

		nNewLen++;

		nLen  = nLen  - ( pEnd - pStart) - nNewLen;
/////		
*/		*pEnd++ = '\0';

		OnSocketMessageReceive( pStart + 1, 0 );

		nLen -= pEnd - pStart;

		if ( !(pStart = (char *) memchr( pEnd, '#', nLen )) )
		{
			return NULL;
		}
		nCnt++;
	}

	return pStart;

}


void CGameProcess::OnProcPacketNotEncode(char *pszMsg)
{
	//  Speed Hack관련.	
	CHAR* pszSrvTick = strchr(pszMsg, '/');
	if ( pszSrvTick )
	{
		pszSrvTick++;
		DWORD dwSrvTick	 = atoi(pszSrvTick);
		DWORD dwRecvTick = timeGetTime();

		if ( m_dwServerActTick )
		{
			DWORD dwSrvGap = dwSrvTick -m_dwServerActTick;
			DWORD dwCliGap = dwRecvTick-m_dwClientActTick;

			m_fTickSum += fabs((FLOAT)dwSrvGap/(FLOAT)dwCliGap);
			m_nTickCnt++;

			// 평균.
			if ( m_nTickCnt >= GetRandomNum(15, 25) )
			{
				m_fHackTickRate = (FLOAT)(m_fTickSum/m_nTickCnt);

				if ( m_fHackTickRate > 1.0f )		// Speed Down 은 신경쓰지 않는다.
				{
					m_fHackTickRate = 1.0f;
				}

				if ( m_fHackTickRate < 0.94f )		// Speed UP Hack!!
				{
					m_nHackCnt++;
					if ( m_nHackCnt > 2 )
					{
						DWORD dwFont = GetChatColor(_CHAT_COLOR3);
						DWORD dwBack = GetChatColor(_CHAT_COLOR4);
						m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(1431));
						m_nHackCnt = 0;
					}
				}
				else
				{
					m_nHackCnt--;
					if ( m_nHackCnt < 0 )
					{
						m_nHackCnt = 0;
					}
				}

				m_nTickCnt = 0;
				m_fTickSum = 0.0f;
			}

		}

		m_dwClientActTick = dwRecvTick;
		m_dwServerActTick = dwSrvTick;
	}

	if ( memcmp(pszMsg, g_pszGood, strlen(g_pszGood)) == 0 )
	{
		m_xMyHero.m_bMotionLock	= FALSE;
		m_xMyHero.m_nOldPosX = m_xMyHero.m_nPosX;
		m_xMyHero.m_nOldPosY = m_xMyHero.m_nPosY;
	}
 	else if( memcmp(pszMsg, g_pszFail, strlen(g_pszFail)) == 0 )
	{
		m_xMyHero.SetOldPosition();
	}
 	else if( memcmp(pszMsg, g_pszLng, strlen(g_pszLng)) == 0 )
	{
		m_xMyHero.m_bUseErgum  = TRUE;
	}
 	else if( memcmp(pszMsg, g_pszUlng, strlen(g_pszUlng)) == 0 )
	{
		m_xMyHero.m_bUseErgum  = FALSE;
		m_xMyHero.m_bUseHErgum  = FALSE;
	}
 	else if( memcmp(pszMsg, g_pszHLng, strlen(g_pszHLng)) == 0 )
	{
		m_xMyHero.m_bUseHErgum  = TRUE;
	}
 	else if( memcmp(pszMsg, g_pszWid, strlen(g_pszWid)) == 0 )
	{
		m_xMyHero.m_bUseBanwol = TRUE;
		m_xMyHero.m_bUseManwol = FALSE;
		m_xMyHero.m_bUseHManwol = FALSE;
	}
 	else if( memcmp(pszMsg, g_pszUWid, strlen(g_pszUWid)) == 0 )
	{
		m_xMyHero.m_bUseBanwol = FALSE;
	}
	// 염화결.
 	else if( memcmp(pszMsg, g_pszFir, strlen(g_pszFir)) == 0 )
	{
		m_xMyHero.m_bFireHitCnt	= 1;
	}
 	else if( memcmp(pszMsg, g_pszUFir, strlen(g_pszUFir)) == 0 )
	{
		m_xMyHero.m_bFireHitCnt = 0;
	}
	// 연월참
 	else if( memcmp(pszMsg, g_pszRnd, strlen(g_pszRnd)) == 0 )
	{
		m_xMyHero.m_bRandSwingCnt= 1;
	}
 	else if( memcmp(pszMsg, g_pszURnd, strlen(g_pszURnd)) == 0 )
	{
		m_xMyHero.m_bRandSwingCnt= 0;
	}
	// 고급연월참
 	else if( memcmp(pszMsg, g_pszHRnd, strlen(g_pszHRnd)) == 0 )
	{
		m_xMyHero.m_bHRandSwingCnt = 1;
	}
 	else if( memcmp(pszMsg, g_pszUHRnd, strlen(g_pszUHRnd)) == 0 )
	{
		m_xMyHero.m_bHRandSwingCnt = 0;
	}

	

	// 돌려베기.
 	else if( memcmp(pszMsg, g_pszBks, strlen(g_pszBks)) == 0 )
	{
		m_xMyHero.m_bBackSwingCnt= 1;
	}
 	else if( memcmp(pszMsg, g_pszUBks, strlen(g_pszUBks)) == 0 )
	{
		m_xMyHero.m_bBackSwingCnt= 0;
	}
 	
	else if( memcmp(pszMsg, g_pszUPwr, strlen(g_pszUPwr)) == 0 )
	{
		m_xMyHero.m_bYedoCnt	= 1;
	}
 	else if( memcmp(pszMsg, g_pszUDig, strlen(g_pszUDig)) == 0 )
	{
		m_xMyHero.m_bViewDigFragment = TRUE;
	}
	else if( memcmp(pszMsg, g_pszUHPwr, strlen(g_pszUHPwr)) == 0 )
	{
		m_xMyHero.m_bHYedoCnt	= 1;
	}
		
	// 회선참
 	else if( memcmp(pszMsg, g_pszMan, strlen(g_pszMan)) == 0 )
	{
		m_xMyHero.m_bUseManwol = TRUE;
		m_xMyHero.m_bUseBanwol = FALSE;
	}
 	else if( memcmp(pszMsg, g_pszHMan, strlen(g_pszHMan)) == 0 )
	{
		m_xMyHero.m_bUseHManwol = TRUE;
		m_xMyHero.m_bUseBanwol = FALSE;
	}
 	else if( memcmp(pszMsg, g_pszUMan, strlen(g_pszUMan)) == 0 )
	{
		m_xMyHero.m_bUseManwol = 0;
	}

	// 고급맹룡승천세
 	else if( memcmp(pszMsg, g_pszHWID, strlen(g_pszHWID)) == 0 )
	{
		m_xMyHero.m_bMang = TRUE;
	}
 	else if( memcmp(pszMsg, g_pszUHWID, strlen(g_pszUHWID)) == 0 )
	{
		m_xMyHero.m_bMang = FALSE;
	}

}


CActor*	CGameProcess::FindActor(int nID)
{
	CActor*					pxActor = NULL;
	CListNode < CActor >	*pNode;

	for ( pNode = m_xActorList.GetHead(); pNode; pNode = pNode->GetNext() )
	{
		pxActor = pNode->GetData();

		if ( pxActor )
		{
			if ( pxActor->m_nIdentity == nID )
				return pxActor;
		}
	}

	return NULL;
}



LPGROUPPOS CGameProcess::FindGroupPos(INT nID)
{
	LPGROUPPOS				pstGroupPos = NULL;
	CListNode < GROUPPOS >	*pNode;

	for ( pNode = m_stGroupPosList.GetHead(); pNode; pNode = pNode->GetNext() )
	{
		pstGroupPos = pNode->GetData();

		if ( pstGroupPos )
		{
			if ( pstGroupPos->nID == nID )
			{
				return pstGroupPos;
			}
		}
	}

	return NULL;
}


VOID CGameProcess::CheckGroupPosValidate()
{
	if ( m_stGroupPosList.GetCount() )
	{
		CListNode < GROUPPOS >		*pNode;
		CListNode < GROUPPOS >		*pNodeTemp;
		LPGROUPPOS					pstGroupPos = NULL;

		for ( pNode = m_stGroupPosList.GetHead(); pNode; )
		{
			pstGroupPos = pNode->GetData();

			if ( pstGroupPos )
			{
				if ( timeGetTime() - pstGroupPos->dwLastRecvTick >= 5000 )
				{
					// 지운다.
					pNodeTemp = pNode->GetNext();
					m_stGroupPosList.RemoveNode(pNode);
					pNode = pNodeTemp;

					delete((LPGROUPPOS)pstGroupPos);
					pstGroupPos = NULL;
					continue;
				}
			}

			pNode = pNode->GetNext();

		}
	}
}



//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
LPEVENTIMG CGameProcess::FindEvent(INT nType, INT nX, INT nY)
{
	LPEVENTIMG					pstEvent = NULL;
	CListNode < EVENTIMG >		*pNode;

	for ( pNode = m_stEventImgList.GetHead(); pNode; pNode = pNode->GetNext() )
	{
		pstEvent = pNode->GetData();

		if ( pstEvent )
		{
			if ( pstEvent->nTileX == nX && pstEvent->nTileY == nY && pstEvent->nType == nType )
			{
				return pstEvent;
			}
		}
	}

	return NULL;
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



CActor*	CGameProcess::FrontActor(INT nXPos, INT nYPos, BYTE bDir, INT nGap)
{
	INT  nXGapPos, nYGapPos;
	nXGapPos = nYGapPos = 0;

	switch ( bDir )
	{
	case _DIRECTION_LIST_1:
		{
			nXGapPos = nXPos;
			nYGapPos = nYPos-nGap;
		}
		break;
	case _DIRECTION_LIST_2:
		{
			nXGapPos = nXPos+nGap;
			nYGapPos = nYPos-nGap;
		}
		break;
	case _DIRECTION_LIST_3:
		{
			nXGapPos = nXPos+nGap;
			nYGapPos = nYPos;
		}
		break;
	case _DIRECTION_LIST_4:
		{
			nXGapPos = nXPos+nGap;
			nYGapPos = nYPos+nGap;
		}
		break;
	case _DIRECTION_LIST_5:
		{
			nXGapPos = nXPos;
			nYGapPos = nYPos+nGap;
		}
		break;
	case _DIRECTION_LIST_6:
		{
			nXGapPos = nXPos-nGap;
			nYGapPos = nYPos+nGap;
		}
		break;
	case _DIRECTION_LIST_7:
		{
			nXGapPos = nXPos-nGap;
			nYGapPos = nYPos;
		}
		break;
	case _DIRECTION_LIST_8:
		{
			nXGapPos = nXPos-nGap;
			nYGapPos = nYPos-nGap;
		}
		break;
	}

	CActor*					pxActor = NULL;
	CListNode < CActor >	*pNode;

	for ( pNode = g_xGameProc.m_xActorList.GetHead(); pNode; pNode = pNode->GetNext() )
	{
		pxActor = pNode->GetData();
		
		if ( pxActor )
		{
			if ( pxActor->m_nPosX == nXGapPos &&  pxActor->m_nPosY == nYGapPos && !pxActor->m_bIsDead && 
				 (pxActor->m_stFeature.bGender == _GENDER_MAN || pxActor->m_stFeature.bGender == _GENDER_WOMAN) )
			{
				return pxActor;
			}
		}
	} 

	return NULL;
}


void CGameProcess::OnSocketMessageReceive(char *pszMsg, INT nLen)
{
	WORD wIdent;

	if (*pszMsg == '+')
	{
		OnProcPacketNotEncode(pszMsg + 1);
	}
	else
	{
		int					nPos = 0;
		_TDEFAULTMESSAGE	tdm, tdmTemp;
		BYTE				szTemp[9];
		char				*pNum = NULL;
		INT					nLength = 0;
		char				*pTmpSrc = NULL;
		BYTE				Tmp[4098];
		

		fnDecodeMessage(&tdmTemp, pszMsg);

		tdmTemp.wIdent = tdmTemp.wIdent ^ m_wNoticeSeed3;

		tdm.nRecog = MAKELONG( MAKEWORD(HIBYTE(tdmTemp.wIdent) , HIBYTE(tdmTemp.wParam) ), 
			                   MAKEWORD(HIBYTE(tdmTemp.wTag), HIBYTE(tdmTemp.wSeries) ));
		tdm.wIdent = MAKEWORD( LOBYTE(LOWORD(tdmTemp.nRecog)) ^ m_bNoticeSeed1, 
			                   LOBYTE(tdmTemp.wIdent) ^ m_bNoticeSeed2 );
		tdm.wParam = MAKEWORD( HIBYTE(LOWORD(tdmTemp.nRecog)), LOBYTE(tdmTemp.wParam) );
		tdm.wTag   = MAKEWORD( LOBYTE(HIWORD(tdmTemp.nRecog)), LOBYTE(tdmTemp.wTag) );
		tdm.wSeries= MAKEWORD( HIBYTE(HIWORD(tdmTemp.nRecog)), LOBYTE(tdmTemp.wSeries) );


		switch (tdm.wIdent)
		{
			case SM_SHOWMONSTER:
			{
				break;
			}
			case SM_SVRVERSION:
			{
				m_bVerChk = TRUE;

				// #ifdef 추가 ( 06.03.16 by eriastoa )
#ifdef _TEST_SERVER
				if (tdm.wParam != 9102)
				{
					m_bVerChk = FALSE;
				}
#endif
				break;
			}
			case SM_PLAYDICE:
			{
				LPPACKETMSG	lpPacketMsg	= new PACKETMSG;

				lpPacketMsg->stDefMsg			= tdm;
				lpPacketMsg->szEncodeData[0]	= NULL;

				lstrcpy(lpPacketMsg->szEncodeData, (pszMsg + _DEFBLOCKSIZE));

				SetDiceMode(lpPacketMsg);
				break;
			}	
			case SM_QUESTDIARYDETAIL:
			{
				char szDecodeMsg[8192];

				nPos = fnDecode6BitBuf((pszMsg + _DEFBLOCKSIZE), szDecodeMsg, sizeof(szDecodeMsg));
				szDecodeMsg[nPos] = '\0';
				m_xInterface.m_xQuestWnd.SetSubDetail(szDecodeMsg,tdm.wSeries,tdm.wParam);
				break;
			}
			case SM_QUERYMONSTERINFO:
			{
				CActor* pxActor = FindActor(tdm.nRecog);
				
				MONSTERSTATUSINFO	stMonsterStatusInfo;

				nPos = fnDecode6BitBuf((pszMsg + _DEFBLOCKSIZE), (CHAR*)&stMonsterStatusInfo, sizeof(MONSTERSTATUSINFO));

				if (pxActor)
				{
					pxActor->m_stMonType.nTaiming = tdm.wParam;
					pxActor->m_stMonType.nDead = tdm.wTag;
					memcpy(&pxActor->m_stMonType.stMonStats, &stMonsterStatusInfo, sizeof(MONSTERSTATUSINFO) );
				}
				break;
			}
			case SM_SENDNOTICE:
			{
				char szDecodeMsg[8192];
				m_xGameMsgBox.InitMsgBox();
				nPos = fnDecode6BitBuf((pszMsg + _DEFBLOCKSIZE), szDecodeMsg, sizeof(szDecodeMsg));
				szDecodeMsg[nPos] = '\0';
				m_xNotice.ShowMessageBox(szDecodeMsg, _IDX_IMG_NOTICEBOX);
 				break;
			}
			case SM_MAPDESCRIPTION:
			{
				nPos = fnDecode6BitBuf((pszMsg + _DEFBLOCKSIZE), (char*)m_szMapName, sizeof(m_szMapName));
				m_szMapName[nPos] = '\0';
				break;
			}
// 퀘스트.
			case SM_QUERYQUESTDIARY:
			{
				char	szDecodeMsg[8192];

				nPos = fnDecode6BitBuf((pszMsg + _DEFBLOCKSIZE), szDecodeMsg, sizeof(szDecodeMsg));
				szDecodeMsg[nPos] = '\0';

				m_xInterface.m_xQuestWnd.SetMainQuest(szDecodeMsg,tdm.wParam);
				break;
			}
			case SM_ADDQUEST:
			{
				char szDecodeMsg[8192];

				nPos = fnDecode6BitBuf((pszMsg + _DEFBLOCKSIZE), szDecodeMsg, sizeof(szDecodeMsg));
				szDecodeMsg[nPos] = '\0';

				DWORD dwFont = GetChatColor(_CHAT_COLOR3);
				DWORD dwBack = GetChatColor(_CHAT_COLOR4);
				m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(1432));
				m_xInterface.m_xQuestWnd.AddSubQuest(szDecodeMsg,tdm.wParam,tdm.wSeries);

				break;
			}
			case SM_ADDQUESTUNIT:
			{
				char szDecodeMsg[8192];
//				CHAR szSysMsg[MAX_PATH];

				nPos = fnDecode6BitBuf((pszMsg + _DEFBLOCKSIZE), szDecodeMsg, sizeof(szDecodeMsg));
				szDecodeMsg[nPos] = '\0';

				DWORD dwFont = GetChatColor(_CHAT_COLOR3);
				DWORD dwBack = GetChatColor(_CHAT_COLOR4);
				m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(1433));
				m_xInterface.m_xQuestWnd.AddMainQuest(szDecodeMsg,tdm.wSeries);

				break;
			}
			case SM_QUERYSUBQUESTDIARY:
			{
				char szDecodeMsg[8192];
//				CHAR szSysMsg[MAX_PATH];

				nPos = fnDecode6BitBuf((pszMsg + _DEFBLOCKSIZE), szDecodeMsg, sizeof(szDecodeMsg));
				szDecodeMsg[nPos] = '\0';
				m_xInterface.m_xQuestWnd.SetSubQuest(szDecodeMsg, tdm.wSeries, tdm.wParam);
				break;
			}








			case SM_DEALTRY_FAIL:
			{
				m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_STORE, _OK, g_xMsg.GetMsg(1434));
				break;
			}
			case SM_DEALMENU:
			{
				if ( !m_xInterface.m_xExchangeWnd.GetGameWndActive() )
				{
					m_xInterface.WindowActivate(_WND_ID_EXCHANGE);
					m_xInterface.m_xExchangeWnd.m_xExchangeBtn.ResetGameBtn(372, 373, -1);

					CHAR	pszDecodeMsg[60];

					nPos = fnDecode6BitBuf((pszMsg + _DEFBLOCKSIZE), pszDecodeMsg, sizeof(pszDecodeMsg));
					pszDecodeMsg[nPos] = '\0';

					m_xInterface.m_xExchangeWnd.SetDealName(pszDecodeMsg);
				}

				if ( !m_xInterface.m_xInventoryWnd.GetGameWndActive() )
				{
					m_xInterface.WindowActivate(_WND_ID_INVENTORY);

					POINT ptPos = {518, 0};
					m_xInterface.m_xInventoryWnd.MoveGameWnd(ptPos, TRUE);
				}

				break;
			}
			case SM_DEALCANCEL:
			{
				// 교환창에 있는 모든 아이템을 가방창에 원상복귀한다. 단 갯수 아이템은 삭제시키고 서버한테 새로 받는다.
				// 공통(마우스)아이템이 있다면 가방에 넣는다.
				// 공통(마우스)아이템을 초기화한다.
				// 교환창의 내용을 초기화한다.
				for ( INT nCnt = 0; nCnt < _MAX_DEAL_ITEM; nCnt++ )
				{
					if ( m_xInterface.m_xExchangeWnd.m_stDealItem[_MY_DEAL][nCnt].bSetted )
					{
						if ( m_xInterface.m_xExchangeWnd.m_stDealItem[_MY_DEAL][nCnt].xItem.m_stItemInfo.stStdItem.bThrow >= _MULTIPLE_TYPE_ITEM )
						{
							ZeroMemory(&m_xInterface.m_stCommonItem, sizeof(COMMONITEMSET));
						}
						else
						{
							m_xInterface.m_xInventoryWnd.AddInvenItem(m_xInterface.m_xExchangeWnd.m_stDealItem[_MY_DEAL][nCnt].xItem, 0, FALSE);
						}
					}
				}

				// 만약에 Deal영역에서 나온아이템이라면 가방에 넣는다.
				if ( m_xInterface.m_stCommonItem.bSetted && m_xInterface.m_stCommonItem.bIsDealItem )
				{
					if ( strcmp(m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(1050)) )
					{
						if ( m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.bThrow >= _MULTIPLE_TYPE_ITEM )
						{
							if (m_xInterface.m_xInventoryWnd.IsThereMultipleItem(m_xInterface.m_stCommonItem.xItem) == FALSE)
								m_xInterface.m_xInventoryWnd.AddInvenItem(m_xInterface.m_stCommonItem.xItem, 0, FALSE);
						}
						else
						{
							m_xInterface.m_xInventoryWnd.AddInvenItem(m_xInterface.m_stCommonItem.xItem, 0, FALSE);
						}
					}
					ZeroMemory(&m_xInterface.m_stCommonItem, sizeof(COMMONITEMSET));
				}

				m_xMyHero.m_nGlod += m_xInterface.m_xExchangeWnd.m_nDealGold[_MY_DEAL];

				// Deal영역 보관창에 아이템이있다면 가방에 넣는다.
				if ( m_xInterface.m_xExchangeWnd.m_stDealOnItem.bSetted )
				{
					if ( m_xInterface.m_xExchangeWnd.m_stDealOnItem.xItem.m_stItemInfo.stStdItem.bThrow >= _MULTIPLE_TYPE_ITEM )
					{
						if (m_xInterface.m_xInventoryWnd.IsThereMultipleItem(m_xInterface.m_xExchangeWnd.m_stDealOnItem.xItem) == FALSE)
							m_xInterface.m_xInventoryWnd.AddInvenItem(m_xInterface.m_xExchangeWnd.m_stDealOnItem.xItem, 0, FALSE);
					}
					else
					{
						m_xInterface.m_xInventoryWnd.AddInvenItem(m_xInterface.m_xExchangeWnd.m_stDealOnItem.xItem, 0, FALSE);
					}
				}

				m_xInterface.m_xExchangeWnd.CloseExchangeWnd();

				// 교환창의 내용을 초기화한다.
				if ( m_xInterface.m_xExchangeWnd.GetGameWndActive() )
				{
					m_xInterface.DeleteWindowToList(_WND_ID_EXCHANGE);
					m_xInterface.m_xExchangeWnd.SetGameWndActive(FALSE);
				}
				break;
			}
			case SM_DEALADDITEM_OK:
			{
				INT nNewIndex = tdm.nRecog;
				INT	nRemain = tdm.wParam;

				if ( nRemain == 0 )
				{
					m_xInterface.ItemClickSound(&m_xInterface.m_xExchangeWnd.m_stDealOnItem.xItem);

					INT nBeltNum = 0;

					nBeltNum = g_xGameProc.m_xInterface.m_xBeltWnd.FindSameItemInBelt(m_xInterface.m_xExchangeWnd.m_stDealOnItem.xItem);

					if (nBeltNum != -1)
						g_xGameProc.m_xInterface.m_xBeltWnd.DeleteBeltItem(nBeltNum);

					m_xInterface.m_xExchangeWnd.SetDealFromDealOnItem();
					ZeroMemory(&m_xInterface.m_stCommonItem, sizeof(COMMONITEMSET));
				}
				else
				{
					m_xInterface.m_xExchangeWnd.m_pstCommonItemSet->xItem = m_xInterface.m_xExchangeWnd.m_stDealOnItem.xItem;
					m_xInterface.m_xExchangeWnd.m_pstCommonItemSet->xItem.m_stItemInfo.wAmount_GB = nRemain;

					INT nBeltNum = 0;

					nBeltNum = g_xGameProc.m_xInterface.m_xBeltWnd.FindSameItemInBelt(m_xInterface.m_xExchangeWnd.m_pstCommonItemSet->xItem);

					if (nBeltNum != -1)
					{
						g_xGameProc.m_xInterface.m_xBeltWnd.m_stBeltItem[nBeltNum].xItem.m_stItemInfo.wAmount_GB = nRemain;
					}

					m_xInterface.m_xExchangeWnd.m_pstCommonItemSet->bSetted = TRUE;

					DWORD	dwCount = m_xInterface.m_xExchangeWnd.m_stDealOnItem.xItem.m_stItemInfo.wAmount_GB;

					dwCount -= nRemain;

					m_xInterface.m_xExchangeWnd.m_stDealOnItem.xItem.m_stItemInfo.wAmount_GB = dwCount;
					m_xInterface.m_xExchangeWnd.m_stDealOnItem.xItem.m_stItemInfo.nMakeIndex = nNewIndex;

					if (nRemain != 0)
						m_xInterface.m_xInventoryWnd.SetInvenFromCommonOLD(0, m_xInterface.m_xExchangeWnd.m_pstCommonItemSet);
					m_xInterface.m_xExchangeWnd.SetDealFromDealOnItem();
					ZeroMemory(&m_xInterface.m_xExchangeWnd.m_stDealOnItem, sizeof(ITEMSET));
				}
				break;
			}
			case SM_DEALADDITEM_FAIL:
			{
				if ( m_xInterface.m_xExchangeWnd.m_stDealOnItem.bSetted )
				{
					m_xInterface.ItemClickSound(&m_xInterface.m_xExchangeWnd.m_stDealOnItem.xItem);
					m_xInterface.m_xInventoryWnd.AddInvenItem(m_xInterface.m_xExchangeWnd.m_stDealOnItem.xItem, 0, FALSE);
				}
				ZeroMemory(&m_xInterface.m_xExchangeWnd.m_stDealOnItem, sizeof(ITEMSET));
				ZeroMemory(&m_xInterface.m_stCommonItem, sizeof(COMMONITEMSET));
				break;
			}
			case SM_DEALDELITEM_OK:
			{
				if ( m_xInterface.m_stCommonItem.bSetted )
				{
					m_xInterface.ItemClickSound(&m_xInterface.m_stCommonItem.xItem);

					if ( strcmp(m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(1050)) )
					{
						if ( m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.bThrow >= _MULTIPLE_TYPE_ITEM )
						{
							if (m_xInterface.m_xInventoryWnd.IsThereMultipleItem(m_xInterface.m_stCommonItem.xItem) == FALSE)
								m_xInterface.m_xInventoryWnd.AddInvenItem(m_xInterface.m_stCommonItem.xItem, 0, FALSE);
						}
						else
						{
							m_xInterface.m_xInventoryWnd.AddInvenItem(m_xInterface.m_stCommonItem.xItem, 0, FALSE);
						}
					}
					ZeroMemory(&m_xInterface.m_stCommonItem, sizeof(COMMONITEMSET));
				}

				break;
			}
		    case SM_DEALDELITEM_FAIL:
			{
//					dealactiontime := GetTickCount;
//					if DealDlgItem.S.Name <> '' then begin
//					   DelItemBag (DealDlgItem.S.Name, DealDlgItem.MakeIndex);
//					   AddDealItem (DealDlgItem);
//					   DealDlgItem.S.Name := '';

				// 벗을려고 한아이템을 교환창넣는다.
				if ( m_xInterface.m_stCommonItem.bSetted )
				{
					m_xInterface.ItemClickSound(&m_xInterface.m_stCommonItem.xItem);

					m_xInterface.m_xExchangeWnd.AddDealItem(_MY_DEAL, m_xInterface.m_stCommonItem.xItem, 0, FALSE);
					ZeroMemory(&m_xInterface.m_stCommonItem, sizeof(COMMONITEMSET));
				}

				break;
			}
		    case SM_DEALCHGGOLD_OK:
			{
				g_SoundManager.SndmngrPlayWavSound(_SOUND_MONEY, 0, 0);
				m_xInterface.m_xExchangeWnd.m_nDealGold[_MY_DEAL] = tdm.nRecog;
				m_xMyHero.m_nGlod = MAKELONG(tdm.wParam, tdm.wTag);
//					DealGold := msg.Recog;
//					Myself.Gold := MakeLong(msg.param, msg.tag);
//					dealactiontime := GetTickCount;
				break;
			}
			case SM_DEALCHGGOLD_FAIL:
			{
				m_xInterface.m_xExchangeWnd.m_nDealGold[_MY_DEAL] = tdm.nRecog;
				m_xMyHero.m_nGlod = MAKELONG(tdm.wParam, tdm.wTag);
//					DealGold := msg.Recog;
//					Myself.Gold := MakeLong(msg.param, msg.tag);
//					dealactiontime := GetTickCount;
				break;
			}
			case SM_DEALREMOTECHGGOLD:
			{
				g_SoundManager.SndmngrPlayWavSound(_SOUND_MONEY, 0, 0);
				m_xInterface.m_xExchangeWnd.m_nDealGold[_YOU_DEAL] = tdm.nRecog;
				break;
			}
			case SM_DEALSUCCESS:
			{
				// 교환창의 내용을 초기화한다.
				m_xInterface.m_xExchangeWnd.FindNDeleteHotKeyItem();
				m_xInterface.m_xExchangeWnd.CloseExchangeWnd();

				if ( m_xInterface.m_xExchangeWnd.GetGameWndActive() )
				{
					m_xInterface.DeleteWindowToList(_WND_ID_EXCHANGE);
					m_xInterface.m_xExchangeWnd.SetGameWndActive(FALSE);
				}
				break;
			}
			case SM_DEALREMOTEADDITEM:
			{
				CLIENTITEMRCD	stReceivedItem;

				char *pszItem = (pszMsg + _DEFBLOCKSIZE);

				fnDecode6BitBuf(pszItem, (char*)&stReceivedItem, sizeof(CLIENTITEMRCD));

				CItem xItem;
				xItem.SetItem(stReceivedItem, 0);
				m_xInterface.m_xExchangeWnd.AddDealItem(_YOU_DEAL, xItem, 0, FALSE);

				m_xInterface.ItemClickSound(&xItem);

				CHAR szSysMsg[MAX_PATH];
				sprintf(szSysMsg, g_xMsg.GetMsg(1435), xItem.m_stItemInfo.stStdItem.szName);
				m_xInterface.m_xClientSysMsg.AddSysMsg(szSysMsg);

				break;
			}
			case SM_DEALREMOTEDELITEM:
			{
				CLIENTITEMRCD	stReceivedItem;

				char *pszItem = (pszMsg + _DEFBLOCKSIZE);

				fnDecode6BitBuf(pszItem, (char*)&stReceivedItem, sizeof(CLIENTITEMRCD));

				CItem xItem;
				xItem.SetItem(stReceivedItem, 0);	
				m_xInterface.ItemClickSound(&xItem);
				
				m_xInterface.m_xExchangeWnd.DeleteDealItem(_YOU_DEAL, stReceivedItem.nMakeIndex, stReceivedItem.stStdItem.szName);

				CHAR szSysMsg[MAX_PATH];
				sprintf(szSysMsg, g_xMsg.GetMsg(1436), stReceivedItem.stStdItem.szName);
				m_xInterface.m_xClientSysMsg.AddSysMsg(szSysMsg);

				break;
			}
			case SM_SENDGOODSLIST:
			{
//상점.
				INT nPos;
				char	szDecodeMsg[10240];
	
				nPos = fnDecode6BitBuf((pszMsg + _DEFBLOCKSIZE), szDecodeMsg, sizeof(szDecodeMsg));
				szDecodeMsg[nPos] = '\0';

				m_xInterface.m_xStoreWnd.SetStoreItemList(szDecodeMsg,tdm.wParam);
				if(!m_xInterface.m_xStoreWnd.GetGameWndActive())
				{
					m_xInterface.WindowActivate(_WND_ID_STORE);
					m_xInterface.m_xStoreWnd.SetNPC(tdm.nRecog);
				}
				break;
			}
			case SM_SENDDETAILGOODSLIST:
			{
//상점.
				m_xInterface.m_xStoreWnd.SetDetailItemLst(pszMsg + _DEFBLOCKSIZE, tdm.wParam, tdm.wTag);
				break;
			}
			case SM_BUYITEM_SUCCESS:
			{
				//상점.
				m_xMyHero.m_nGlod = tdm.nRecog;
				m_xInterface.m_xStoreWnd.DeleteDetailItem();
				break;
			}
			case SM_BUYITEM_FAIL:
			{
//상점.
				switch(tdm.nRecog)
				{
				case 1:
					m_xInterface.m_xStoreWnd.DeleteDetailItem();// 이미 필린 물건이므로 리스트에서 삭제
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_STORE, _OK, g_xMsg.GetMsg(1437));					
					break;
				case 2:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_STORE, _OK, g_xMsg.GetMsg(1438));
					break;
				case 3:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_STORE, _OK, g_xMsg.GetMsg(1439));
					break;
				}
				break;
			}
			case SM_SENDUSERMAKEDRUGITEMLIST:
			{
//상점.
				char	szDecodeMsg[10240];

				nPos = fnDecode6BitBuf((pszMsg + _DEFBLOCKSIZE), szDecodeMsg, sizeof(szDecodeMsg));
				szDecodeMsg[nPos] = '\0';
   
				m_xInterface.m_xStoreWnd.SetDrugList(szDecodeMsg);
				if(!m_xInterface.m_xStoreWnd.GetGameWndActive())
				{
					m_xInterface.WindowActivate(_WND_ID_STORE);
					m_xInterface.m_xStoreWnd.SetNPC(tdm.nRecog);
				}
				break;
			}
			case SM_MAKEDRUG_SUCCESS:
			{
				m_xMyHero.m_nGlod = tdm.nRecog;
				m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_STORE, _OK, g_xMsg.GetMsg(1440));
				break;
			}
			case SM_MAKEDRUG_FAIL:
			{
				switch(tdm.nRecog)
				{
				case 1:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_STORE, _OK, g_xMsg.GetMsg(1441));
					break;
				case 2:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_STORE, _OK, g_xMsg.GetMsg(1442));
					break;
				case 3:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_STORE, _OK, g_xMsg.GetMsg(1443));
					break;
				case 4:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_STORE, _OK, g_xMsg.GetMsg(1444));
					break;
				}
				break;
			}
			// 창고 물건 찾기
			case SM_SAVEITEMLIST:
			{
//상점.
				m_xInterface.m_xStoreWnd.SetStorageList(pszMsg + _DEFBLOCKSIZE, tdm.wSeries);

				if ( !m_xInterface.m_xStoreWnd.GetGameWndActive() )
				{
					m_xInterface.WindowActivate(_WND_ID_STORE);
					m_xInterface.m_xStoreWnd.SetNPC(tdm.nRecog);
				}
				break;
			}
			case SM_SAVEITEMLIST2:
			{
				m_xInterface.m_xStoreWnd.AddStorageList(pszMsg + _DEFBLOCKSIZE, tdm.wSeries);
				break;
			}
			case SM_SAVEITEMLIST3:
			{
				m_xInterface.m_xStoreWnd.AddStorageList(pszMsg + _DEFBLOCKSIZE, tdm.wSeries);
				break;
			}
			case SM_TAKEBACKSTORAGEITEM_OK:
			{
				INT nRemain = tdm.wParam;
				INT nCount = tdm.wTag;

				if (nCount > 0)
				{
					CItem* pxItem = m_xInterface.m_xStoreWnd.GetSelDetailItemInfo(m_xInterface.m_xStoreWnd.m_nSelDetailItem);
					m_xInterface.m_xInventoryWnd.ChangeItemCount(pxItem->m_stItemInfo.nMakeIndex, nCount);
				}

				if (nRemain == 0)
					m_xInterface.m_xStoreWnd.DeleteDetailItem();
				else
				{
					CItem* pxItem = m_xInterface.m_xStoreWnd.GetSelDetailItemInfo(m_xInterface.m_xStoreWnd.m_nSelDetailItem);

					if (pxItem != NULL)
					{
						pxItem->m_stItemInfo.wAmount_GB = nRemain;
					}
				}
				break;
			}
			case SM_TAKEBACKSTORAGEITEM_FAIL:
			{
				m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_STORE, _OK, g_xMsg.GetMsg(1445));
				break;
			}
			case SM_TAKEBACKSTORAGEITEM_FULLBAG:
			{
				m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_STORE, _OK, g_xMsg.GetMsg(1446));
				break;
			}
			// 창고에 물건 맡기기
			case SM_SENDUSERSTORAGEITEM:
			{
				if(!m_xInterface.m_xInventoryWnd.GetGameWndActive())
				{
					m_xInterface.WindowActivate(_WND_ID_INVENTORY);
				}

				if (m_xInterface.m_xStoreWnd.GetGameWndActive())
					m_xInterface.WindowActivate(_WND_ID_STORE);

				{
					m_xInterface.m_xInventoryWnd.SetInvenType(_INVEN_TYPE_STORAGE);
					m_xInterface.m_xInventoryWnd.SetMerchantID(tdm.nRecog);
					POINT ptPos = {519, 0};
					m_xInterface.m_xInventoryWnd.MoveGameWnd(ptPos, TRUE);
				}
				break;
			}
			

			// 맡긴 후 성공시
			case SM_STORAGE_OK:
			{
				if ( m_xInterface.m_xInventoryWnd.m_stParkItem.bSetted )
				{
					INT nCount = tdm.wTag; // 보관된 갯수
					INT nRemain = tdm.wParam; // 남은갯수

					CHAR szSysMsg[MAX_PATH];
					INT nItemNum = m_xInterface.m_xInventoryWnd.m_stParkItem.nItemNum;
					if (nCount > 0)
						sprintf(szSysMsg, g_xMsg.GetMsg(1447), m_xInterface.m_xInventoryWnd.m_stInventoryItem[nItemNum].xItem.m_stItemInfo.stStdItem.szName, nCount);
					else
						sprintf(szSysMsg, g_xMsg.GetMsg(1448), m_xInterface.m_xInventoryWnd.m_stInventoryItem[nItemNum].xItem.m_stItemInfo.stStdItem.szName);

					m_xInterface.m_xClientSysMsg.AddSysMsg(szSysMsg);

					if (nRemain != 0)
						m_xInterface.m_xInventoryWnd.ChangeItemCount(m_xInterface.m_xInventoryWnd.m_stInventoryItem[nItemNum].xItem.m_stItemInfo.nMakeIndex, nRemain);
					else
					{
						INT nBeltNum = 0;
						nBeltNum = g_xGameProc.m_xInterface.m_xBeltWnd.FindSameItemInBelt(m_xInterface.m_xInventoryWnd.m_stInventoryItem[nItemNum].xItem);

						if (nBeltNum != -1)
							g_xGameProc.m_xInterface.m_xBeltWnd.DeleteBeltItem(nBeltNum);
						m_xInterface.m_xInventoryWnd.DeleteInvenItem(m_xInterface.m_xInventoryWnd.m_stParkItem.nItemNum);
					}
				}
				m_xInterface.m_xInventoryWnd.InitParkItem();
				break;
			}
			case SM_STORAGE_FULL:
			{
				m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_INVENTORY, _OK, g_xMsg.GetMsg(1449));
				m_xInterface.m_xInventoryWnd.InitParkItem();
				break;
			}
			case SM_STORAGE_FAIL:
			{
				m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_INVENTORY, _OK, g_xMsg.GetMsg(1450));
				m_xInterface.m_xInventoryWnd.InitParkItem();
				break;
			}
			case SM_SENDUSERSELL:
			{
				if(!m_xInterface.m_xInventoryWnd.GetGameWndActive())
				{
					m_xInterface.WindowActivate(_WND_ID_INVENTORY);
				}
				m_xInterface.m_xInventoryWnd.SetInvenType(_INVEN_TYPE_SELL);
				m_xInterface.m_xInventoryWnd.SetMerchantID(tdm.nRecog);
				POINT ptPos = {519, 0};
				m_xInterface.m_xInventoryWnd.MoveGameWnd(ptPos, TRUE);

				break;
			}
			case SM_SENDBUYPRICE:
			{
				if ( m_xInterface.m_xInventoryWnd.m_stParkItem.bSetted )
				{
					INT nItemNum = m_xInterface.m_xInventoryWnd.m_stParkItem.nItemNum;
					m_xInterface.m_xInventoryWnd.m_nPrice = tdm.nRecog;
					if (m_xInterface.m_xInventoryWnd.m_stInventoryItem[nItemNum].xItem.m_stItemInfo.stStdItem.bThrow >= _MULTIPLE_TYPE_ITEM)
						sprintf(m_xInterface.m_xInventoryWnd.m_pszPrice, g_xMsg.GetMsg(1451), tdm.nRecog);
					else
						sprintf(m_xInterface.m_xInventoryWnd.m_pszPrice, g_xMsg.GetMsg(1452), tdm.nRecog);

					if ( tdm.nRecog == 0 )
						m_xInterface.m_xInventoryWnd.m_stParkItem.bRecvPrice = _PRICE_NONE;
					else
						m_xInterface.m_xInventoryWnd.m_stParkItem.bRecvPrice = _PRICE_RECEIVED;
				}
				break;
			}
			case SM_USERSELLITEM_OK:
			{
//            FrmDlg.LastestClickTime := GetTickCount;
				m_xMyHero.m_nGlod = tdm.nRecog;
				if ( m_xInterface.m_xInventoryWnd.m_stParkItem.bSetted )
				{
					CHAR szSysMsg[MAX_PATH];
					INT nItemNum = m_xInterface.m_xInventoryWnd.m_stParkItem.nItemNum;
					sprintf(szSysMsg, g_xMsg.GetMsg(1453), m_xInterface.m_xInventoryWnd.m_stInventoryItem[nItemNum].xItem.m_stItemInfo.stStdItem.szName);
					m_xInterface.m_xClientSysMsg.AddSysMsg(szSysMsg);

					m_xInterface.m_xInventoryWnd.DeleteInvenItem(m_xInterface.m_xInventoryWnd.m_stParkItem.nItemNum);
				}
				m_xInterface.m_xInventoryWnd.InitParkItem();
				break;
			}
			case SM_USERSELLCOUNTITEM_OK:
			{
				m_xMyHero.m_nGlod = tdm.nRecog;
				int nRemain = tdm.wParam;
				int nCount = tdm.wTag;

				if ( m_xInterface.m_xInventoryWnd.m_stParkItem.bSetted )
				{
					CHAR szSysMsg[MAX_PATH];
					INT nItemNum = m_xInterface.m_xInventoryWnd.m_stParkItem.nItemNum;

					sprintf(szSysMsg, g_xMsg.GetMsg(1454), m_xInterface.m_xInventoryWnd.m_stInventoryItem[nItemNum].xItem.m_stItemInfo.stStdItem.szName, nCount);
					m_xInterface.m_xClientSysMsg.AddSysMsg(szSysMsg);

					if (nRemain != 0)
						m_xInterface.m_xInventoryWnd.ChangeItemCount(m_xInterface.m_xInventoryWnd.m_stInventoryItem[nItemNum].xItem.m_stItemInfo.nMakeIndex, nRemain);
					else
					{
						INT nBeltNum = 0;
						nBeltNum = g_xGameProc.m_xInterface.m_xBeltWnd.FindSameItemInBelt(m_xInterface.m_xInventoryWnd.m_stInventoryItem[nItemNum].xItem);

						if (nBeltNum != -1)
							g_xGameProc.m_xInterface.m_xBeltWnd.DeleteBeltItem(nBeltNum);
						m_xInterface.m_xInventoryWnd.DeleteInvenItem(m_xInterface.m_xInventoryWnd.m_stParkItem.nItemNum);
					}
				}
				m_xInterface.m_xInventoryWnd.InitParkItem();
				break;
			}
			case SM_USERSELLCOUNTITEM_FAIL:
			{
				m_xInterface.m_xInventoryWnd.InitParkItem();
				break;
			}
			case SM_USERSELLITEM_FAIL:
			{
				m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_INVENTORY, _OK, g_xMsg.GetMsg(1455));
				m_xInterface.m_xInventoryWnd.InitParkItem();
				break;
			}
			case SM_USERGETSHOOTER:
			{
/*   Param:  공성병기의 종류
           1: 발석거
           2: 쇠뇌기
   Tag: 발사 걸리 방식
           0:  1칸 앞
           1:  2칸 앞
           2:  3칸 앞
           3:  2, 3칸 앞
	Recog:  Lo:장전된 총알 수  Hi:장전 할 수 
		   
*/
				char	szDecodeMsg[8192];
				char	*pszIndex = NULL;
				INT		nPos;

				nPos = fnDecode6BitBuf((pszMsg + _DEFBLOCKSIZE), szDecodeMsg, sizeof(szDecodeMsg));
				szDecodeMsg[nPos] = '\0';

				if ( pszIndex = strchr(szDecodeMsg, 0x09 ))
				{
					*pszIndex++ = '\0';
					m_xInterface.m_xSiegeWnd.m_nIndex = atoi(pszIndex);
				}

				m_xInterface.m_bHasSiege = TRUE;
				
				m_xInterface.m_xSiegeWnd.m_nLoadedBullet = LOWORD(tdm.nRecog);
				m_xInterface.m_xSiegeWnd.m_nMaxBullet = HIWORD(tdm.nRecog);

				m_xInterface.m_xSiegeWnd.m_nKind = tdm.wParam;

				int ntest = 0;
				break;
			}
			case SM_SHOOTERSTATUSCHANGED:
			{
				m_xInterface.m_xSiegeWnd.m_nLoadedBullet = LOWORD(tdm.nRecog);
				m_xInterface.m_xSiegeWnd.m_nMaxBullet = HIWORD(tdm.nRecog);
				break;
			}
			case SM_SHOTEFFECT:
			{
				tdm.nRecog;	 // 좌표
				tdm.wParam;  // 방향
				tdm.wTag; // 효과번호 돌 :10 화살 :20

				INT nStartX, nStartY, nX, nY;

				nX = LOWORD(tdm.nRecog);
				nY = HIWORD(tdm.nRecog);

				if ( tdm.wTag == 10 )
				{
					switch(tdm.wParam)
					{
					case 4:
						nStartX = nX;
						nStartY = nY - 20;
						break;
					case 5:
						nStartX = nX + 20;
						nStartY = nY - 30;
						break;
					case 6:
						nStartX = nX + 20;
						nStartY = nY - 10;
						break;
					case 7:
						nStartX = nX + 20;
						nStartY = nY + 10;
						break;
					case 0:
						nStartX = nX;
						nStartY = nY + 20;
						break;
					case 1:
						nStartX = nX - 20;
						nStartY = nY + 10;
						break;
					case 2:
						nStartX = nX - 20;
						nStartY = nY - 10;
						break;
					case 3:
						nStartX = nX - 20;
						nStartY = nY - 30;
						break;
					}

					CMagic* pxMagic;
					pxMagic = new CMagic;
					if ( pxMagic->CreateMagic(_MONMAGIC_SIEGE_HITTED, nStartX, nStartY, nX, nY, NULL, 0) )
						g_xGameProc.m_xMagicList.Insert (pxMagic);
					else
						delete pxMagic;
				}
				else if ( tdm.wTag == 20 )
				{
					char	szDecodeMsg[8192];
					char	*pszIndex = NULL;
					char	*pszNext = NULL;
					INT		nPos, nCnt = 0, nI;
					POINT	ptTarget[9];

					nPos = fnDecode6BitBuf((pszMsg + _DEFBLOCKSIZE), szDecodeMsg, sizeof(szDecodeMsg));
					szDecodeMsg[nPos] = '\0';
					pszIndex = szDecodeMsg;

					do
					{
						if ( pszNext = strchr(pszIndex, 0x09 ))
						{
							*pszNext++ = '\0';
							ptTarget[nCnt].x = atoi(pszIndex);

							pszIndex = pszNext;
						}

						if ( pszNext = strchr(pszIndex, 0x09 ))
						{
							*pszNext++ = '\0';
							ptTarget[nCnt].y = atoi(pszIndex);

							pszIndex = pszNext;
						}
						nCnt++;
					} while (pszNext);
					nCnt--;

					for ( nI=0; nI<nCnt; nI++)
					{
						switch(tdm.wParam)
						{
						case 4:
							nStartX = ptTarget[nI].x;
							nStartY = ptTarget[nI].y - 20;
							break;
						case 5:
							nStartX = ptTarget[nI].x + 20;
							nStartY = ptTarget[nI].y - 20;
							break;
						case 6:
							nStartX = ptTarget[nI].x + 20;
							nStartY = ptTarget[nI].y - 20;
							break;
						case 7:
							nStartX = ptTarget[nI].x + 20;
							nStartY = ptTarget[nI].y + 20;
							break;
						case 0:
							nStartX = ptTarget[nI].x;
							nStartY = ptTarget[nI].y + 20;
							break;
						case 1:
							nStartX = ptTarget[nI].x - 20;
							nStartY = ptTarget[nI].y + 20;
							break;
						case 2:
							nStartX = ptTarget[nI].x - 20;
							nStartY = ptTarget[nI].y - 20;
							break;
						case 3:
							nStartX = ptTarget[nI].x - 20;
							nStartY = ptTarget[nI].y - 20;
							break;
						}
						CMagic* pxMagic;
						pxMagic = new CMagic;
						if ( pxMagic->CreateMagic(_MONMAGIC_SIEGECAR_HITTED, nStartX, nStartY, ptTarget[nI].x, ptTarget[nI].y, NULL, 0, nI*70) )
							g_xGameProc.m_xMagicList.Insert (pxMagic);
						else
							delete pxMagic;
					}
				
				}
				break;	
			}
			case SM_LOSESHOOTER:
			{
				m_xInterface.m_bHasSiege = FALSE;

				if( m_xInterface.m_xSiegeWnd.GetGameWndActive() )
					m_xInterface.WindowActivate(_WND_ID_SIEGE);
			}
			break;
			case SM_SENDLISTUSERMARKET:
			{
				m_xInterface.m_xMarketWnd.SetMarketItemList(pszMsg, tdm.wSeries, tdm.wParam, tdm.wTag);
				
				if(!m_xInterface.m_xMarketWnd.GetGameWndActive())
				{
					m_xInterface.WindowActivate(_WND_ID_USERMARKET);
					m_xInterface.m_xMarketWnd.mUserMarket_nNpcId = tdm.nRecog;
				}
			}
			break;
			case SM_SENDDHLTITLES:
			{
				if (  tdm.wParam == 0 )
					m_xInterface.m_xMessengerWnd.SetReceivedMSGList(pszMsg, tdm.wSeries);
				else if ( tdm.wParam == 2 )
					m_xInterface.m_xMessengerWnd.SetSendMSGList(pszMsg, tdm.wSeries);
			}
			break;
			case SM_READDHLMESSAGE:
			{
				LPCLIENTDHLCONTAIN pstDhlMsg = NULL;
				pstDhlMsg = new CLIENTDHLCONTAIN;
				char szDecodeMsg[_MAX_STRING_LEN];

				fnDecode6BitBuf(pszMsg + _DEFBLOCKSIZE, (char*)pstDhlMsg, sizeof(CLIENTDHLCONTAIN));
				
				m_xInterface.m_xMessengerWnd.mMessenger_nMode = _READ_BOX;

				if ( tdm.wParam == 0 )
				{
					m_xInterface.m_xMessengerWnd.AddReceivedMsg(pstDhlMsg);
					m_xInterface.m_xMessengerWnd.mMessenger_nReadMode = _RECEIVED_MODE;
				}
				else if ( tdm.wParam == 2 )
				{
					m_xInterface.m_xMessengerWnd.AddReceivedMsg(pstDhlMsg);
					m_xInterface.m_xMessengerWnd.mMessenger_nReadMode = _SEND_MODE;
				}
			}
			break;
			case SM_HAVEARRIVEDNEWDHL:
			{
				m_xInterface.m_bHasNewMessage = TRUE;
			}
			break;
			case SM_CMDRESULT:
			{
				// 2006.06.28 - 원보상점 아이템 구매 이후 성공
				m_xInterface.m_xMarketWnd.mUserMarket_bReadytoGet = !tdm.nRecog;
			}
			break;
			case SM_SENDCHARSTATUS:
			{
				m_xInterface.m_xOptionWnd.OptionChanged(tdm.nRecog, tdm.wParam);
//				LPPICTURE m_pPicture;
//				SIZE m_sizeInHiMetric;
//				m_pPicture->get_Width(&m_sizeInHiMetric.cx);
			}
			break;
			case SM_UPDATEFACERESULT:
			{
				int nDate = tdm.nRecog;

				if ( nDate == 0 )
				{
//					CHAR szFileName[MAX_PATH];

//					if ( GetCurrentDirectory(MAX_PATH, szFileName))
//					{
//						if ( szFileName[0] == '\0' )
//						{
//							break;
//						}

//						sprintf(szFileName, "%s\\%s_%s.jpg", szFileName, g_szServerName, m_xMyHero.m_szName);
//						DeleteFile(szFileName);
//					}
				}
				else 
				{
					DWORD dwFont = GetChatColor(_CHAT_COLOR3);
					DWORD dwBack = GetChatColor(_CHAT_COLOR4);
					m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(1519));

					CHAR szFileName[MAX_PATH];
					// Userpic.ini 갱신
					if ( GetCurrentDirectory(MAX_PATH, szFileName))
					{
						if ( szFileName[0] == '\0' )
						{
							break;
						}

						strcat(szFileName, "\\UserPic.ini");

						CHAR szTemp[MAX_PATH];

						// 파일 검색
						CHAR	szSearchKey[MAX_PATH];
						CHAR	szVal[MAX_PATH];

						sprintf(szVal, "%d", nDate);

						char	*pszName = NULL;
						pszName = CheckAbnormalName(m_xMyHero.m_szName);
						sprintf(szSearchKey, "%s_%s", g_szServerName, pszName);

						g_xGameProc.m_xMyHero.m_nFaceImageDate = nDate;

						WritePrivateProfileString("UserPic", szSearchKey, szVal, szFileName);
					}
				}
			}
			break;
			case SM_SENDFACEIMAGE:
			{
				char szDecodeMsg[_MAX_STRING_LEN*4];
				CHAR szFileName[MAX_PATH];
				CHAR szSave[MAX_PATH];

				INT nId = tdm.nRecog;
				INT nDate = MAKELONG(tdm.wParam, tdm.wTag);

				CActor* pxActor = NULL;

				if ( tdm.nRecog == m_xMyHero.m_nIdentity )
				{
					// File Save
					if ( GetCurrentDirectory(MAX_PATH, szFileName))
					{
						if ( szFileName[0] == '\0' )
						{
							break;
						}

						int nPos = fnDecode6BitBuf(pszMsg + _DEFBLOCKSIZE, szDecodeMsg, sizeof(szDecodeMsg));

						CHAR szNewDir[MAX_PATH];

						sprintf( szNewDir, "%s\\Data", szFileName );
						SetCurrentDirectory(szNewDir);

						FILE *fp;

						char	*pszName = NULL;
						pszName = CheckAbnormalName(m_xMyHero.m_szName);

						sprintf(szSave, "%s_%s.jpg", g_szServerName, pszName);

						fp = fopen( szSave, "wb" );

						if ( fp )
						{
							fwrite( szDecodeMsg, sizeof( char ), nPos, fp );
							fclose( fp );

							// 암호화해서 저장
							fp = fopen( szSave, "rb" );
							
							int len = _filelength( _fileno( fp ) );
							char *buf = new char[ len + 8 ];
							if ( !buf )
							{
								fclose( fp );
								return;
							}

							fread( buf + 8, 1, len, fp );
							fclose( fp );

							if ( !crypto::encrypt( (unsigned char *) buf + 8, len ) )
							{
								delete[] buf;
								return;
							}

							CHAR szCryptName[MAX_PATH];

							char	*pszName = NULL;
							pszName = CheckAbnormalName(m_xMyHero.m_szName);
							sprintf(szCryptName, "%s_%s.fac", g_szServerName, pszName);

							fp = fopen( szCryptName, "wb" );
							if ( !fp )
								return;

							fwrite( buf, 1, len + 8, fp );
							fclose( fp );

							DeleteFile(szSave);			//    암호화 끝 파일 지우기

							SetCurrentDirectory(szFileName);
							m_xInterface.m_bIsThereUserFile = TRUE;

							// Userpic.ini 갱신
							if ( GetCurrentDirectory(MAX_PATH, szFileName))
							{
								if ( szFileName[0] == '\0' )
								{
									break;
								}

								strcat(szFileName, "\\UserPic.ini");

								CHAR szTemp[MAX_PATH];

								// 파일 검색
								CHAR	szSearchKey[MAX_PATH];
								CHAR	szVal[MAX_PATH];

								sprintf(szVal, "%d", nDate);
								pszName = CheckAbnormalName(m_xMyHero.m_szName);
								sprintf(szSearchKey, "%s_%s", g_szServerName, pszName);

								WritePrivateProfileString("UserPic", szSearchKey, szVal, szFileName);
							}
						}
					}
				}
				else
				{
					pxActor = FindActor(tdm.nRecog);
				}

				if ( pxActor == NULL )
					break;

				if ( nDate == 0 )
				{
					if ( GetCurrentDirectory(MAX_PATH, szFileName))
					{
						if ( szFileName[0] == '\0' )
						{
							break;
						}

						strcat(szFileName, "\\UserPic.ini");

						CHAR szTemp[MAX_PATH];

						// 파일 검색
						CHAR	szSearchKey[MAX_PATH];
						CHAR	szVal[MAX_PATH];

						sprintf(szVal, "%d", nDate);

						char	*pszName = NULL;
						pszName = CheckAbnormalName(pxActor->m_szName);

						sprintf(szSearchKey, "%s_%s", g_szServerName, pszName);

						WritePrivateProfileString("UserPic", szSearchKey, szVal, szFileName);
					}
				}
				else
				{
					int nPos = fnDecode6BitBuf(pszMsg + _DEFBLOCKSIZE, szDecodeMsg, sizeof(szDecodeMsg));
					
					// File Save
					if ( GetCurrentDirectory(MAX_PATH, szFileName))
					{
						if ( szFileName[0] == '\0' )
						{
							break;
						}

						CHAR szNewDir[MAX_PATH];

						sprintf( szNewDir, "%s\\Data", szFileName );
						SetCurrentDirectory(szNewDir);

						FILE *fp;

						char	*pszName = NULL;
						pszName = CheckAbnormalName(pxActor->m_szName);

						sprintf(szSave, "%s_%s.jpg", g_szServerName, pszName);

						fp = fopen( szSave, "wb" );

						if ( fp != NULL )
						{
							fwrite( szDecodeMsg, sizeof( char ), nPos, fp );
							fclose( fp );

							// 암호화해서 저장
							fp = fopen( szSave, "rb" );
							
							int len = _filelength( _fileno( fp ) );
							char *buf = new char[ len + 8 ];
							if ( !buf )
							{
								fclose( fp );
								return;
							}

							fread( buf + 8, 1, len, fp );
							fclose( fp );

							if ( !crypto::encrypt( (unsigned char *) buf + 8, len ) )
							{
								delete[] buf;
								return;
							}

							CHAR szCryptName[MAX_PATH];

							char	*pszName = NULL;
							pszName = CheckAbnormalName(pxActor->m_szName);

							sprintf(szCryptName, "%s_%s.fac", g_szServerName, pszName);

							fp = fopen( szCryptName, "wb" );
							if ( !fp )
								return;

							fwrite( buf, 1, len + 8, fp );
							fclose( fp );

							DeleteFile(szSave);			//    암호화 끝 파일 지우기

							SetCurrentDirectory(szFileName);

							// Userpic.ini 갱신
							if ( GetCurrentDirectory(MAX_PATH, szFileName))
							{
								if ( szFileName[0] == '\0' )
								{
									break;
								}

								strcat(szFileName, "\\UserPic.ini");

								CHAR szTemp[MAX_PATH];

								// 파일 검색
								CHAR	szSearchKey[MAX_PATH];
								CHAR	szVal[MAX_PATH];

								sprintf(szVal, "%d", nDate);

								char	*pszName = NULL;
								pszName = CheckAbnormalName(pxActor->m_szName);

								sprintf(szSearchKey, "%s_%s", g_szServerName, pszName);

								WritePrivateProfileString("UserPic", szSearchKey, szVal, szFileName);
								pxActor->m_bNeedLoadFameImg = TRUE;
							}
						}
					}
				}
			}
			break;
			case SM_SENDUSERREPAIR:
			{
				if(!m_xInterface.m_xInventoryWnd.GetGameWndActive())
				{
					m_xInterface.WindowActivate(_WND_ID_INVENTORY);
				}
				m_xInterface.m_xInventoryWnd.SetInvenType(_INVEN_TYPE_REPAIR);
				m_xInterface.m_xInventoryWnd.SetMerchantID(tdm.nRecog);
				POINT ptPos = {519, 0};
				m_xInterface.m_xInventoryWnd.MoveGameWnd(ptPos, TRUE);
				break;
			}
			case SM_SENDREPAIRCOST:
			{
				if ( m_xInterface.m_xInventoryWnd.m_stParkItem.bSetted )
				{
					m_xInterface.m_xInventoryWnd.m_nPrice = tdm.nRecog;
					sprintf(m_xInterface.m_xInventoryWnd.m_pszPrice, g_xMsg.GetMsg(1452), tdm.nRecog);

					if ( tdm.nRecog == 0 )
						m_xInterface.m_xInventoryWnd.m_stParkItem.bRecvPrice = _PRICE_NONE;
					else
						m_xInterface.m_xInventoryWnd.m_stParkItem.bRecvPrice = _PRICE_RECEIVED;
				}
				break;
			}
			case SM_USERREPAIRITEM_OK:
			{
				m_xMyHero.m_nGlod = tdm.nRecog;

				if ( m_xInterface.m_xInventoryWnd.m_stParkItem.bSetted )
				{
					INT nItemNum = m_xInterface.m_xInventoryWnd.m_stParkItem.nItemNum;

					m_xInterface.m_xInventoryWnd.m_stInventoryItem[nItemNum].xItem.m_stItemInfo.nDura	 = tdm.wParam;
					m_xInterface.m_xInventoryWnd.m_stInventoryItem[nItemNum].xItem.m_stItemInfo.nDuraMax = tdm.wTag;

					m_xInterface.m_xClientSysMsg.AddSysMsg(g_xMsg.GetMsg(1456));
				}
				m_xInterface.m_xInventoryWnd.InitParkItem();
				break;
			}
			case SM_USERREPAIRITEM_FAIL:
			{
				m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_INVENTORY, _OK, g_xMsg.GetMsg(1457));
				m_xInterface.m_xInventoryWnd.InitParkItem();
				break;
			}

			case SM_READMINIMAP_OK:
			{
				m_xInterface.m_dwQueryMsgTime = timeGetTime();
				m_xInterface.m_xMiniMap.SetMiniMap(tdm.wParam-1);
				m_xInterface.m_xMiniMapInSiege.SetMiniMap(tdm.wParam-1);

				if ( m_xInterface.m_bReadyViewMap == TRUE )
				{
					m_xInterface.m_bViewMiniMap = TRUE;
					m_xInterface.m_bReadyViewMap = FALSE;
				}

				if ( m_xInterface.m_bReadyInforMap == TRUE )
				{
					m_xInterface.m_bViewMiniMapInMain = TRUE;
					m_xInterface.m_nInformationMode = _INFO_MINIMAP;
					m_xInterface.m_bReadyInforMap = FALSE;
				}
				break;
			}	
			case SM_READMINIMAP_FAIL:
			{
				m_xInterface.m_dwQueryMsgTime = timeGetTime();
				DWORD dwFont = GetChatColor(_CHAT_COLOR3);
				DWORD dwBack = GetChatColor(_CHAT_COLOR4);
				m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(1458));

				m_xInterface.m_bViewMiniMap = FALSE;
				m_xInterface.m_bReadyViewMap = FALSE;

				if ( m_xInterface.m_bReadyInforMap == TRUE )
				{
					m_xInterface.m_nInformationMode = _INFO_MINIMAP;
					m_xInterface.m_bViewMiniMapInMain = FALSE;
					m_xInterface.m_bReadyInforMap = FALSE;
				}
			}
			break;
			case SM_WINEXP:
			{
				CHAR szExp[MAX_PATH];
				DWORD	dwNow;
				BOOL	bLevelChange = FALSE;
				
				char szDecodeMsg[8192];

				nPos = fnDecode6BitBuf((pszMsg + _DEFBLOCKSIZE), szDecodeMsg, sizeof(szDecodeMsg));
				szDecodeMsg[nPos] = '\0';

				char *pszFame = NULL;
				char *pszExp = NULL;
				INT nWinExp = 0, nFame = 0;
				LONGLONG dlngExp = 0;

				if (pszFame = strchr(szDecodeMsg, '/'))
				{
					INT ntest = 0;
					*pszFame++ = '\0';

					nWinExp = atoi(szDecodeMsg);
					nFame = atoi(pszFame);
					pszExp = strchr(pszFame, '/');
					*pszExp++ = '\0';
				}
				
				m_xMyHero.m_stAbility.dlngExp = _atoi64(pszExp);
				dwNow = tdm.wParam;

				m_xMyHero.m_nFame = nFame;

				bLevelChange = LOBYTE(tdm.wSeries);
				
				int nFlag = HIBYTE(tdm.wSeries);

				if ( nFlag )
				{
					DWORD dwFont = GetChatColor(_CHAT_COLOR3);
					DWORD dwBack = GetChatColor(_CHAT_COLOR4);
					sprintf(szExp, g_xMsg.GetMsg(1513));
					m_xInterface.MsgAdd(dwFont, dwBack, szExp);
				}
				
				BOOL bAddMsg = FALSE;

				if (tdm.wTag > 0)
				{
					sprintf(szExp, g_xMsg.GetMsg(1459), nWinExp, tdm.wTag);
					INT  nSwordTrainPoint;
					if ( bLevelChange )
					{
						nSwordTrainPoint = m_xInterface.m_xStatusWnd.m_stEquipItem[_U_WEAPON].xItem.m_stItemInfo.wAmount_GB;
						nSwordTrainPoint += tdm.wTag;
					}
					else
					{
						nSwordTrainPoint = m_xInterface.m_xStatusWnd.m_stEquipItem[_U_WEAPON].xItem.m_stItemInfo.wAmount_GB;
						nSwordTrainPoint += tdm.wTag;
					}

					if ( nSwordTrainPoint > 60000 )
						m_xMyHero.m_nTempWeaponExp = nSwordTrainPoint;
					else 
						m_xMyHero.m_nTempWeaponExp = 0;


					m_xInterface.m_xStatusWnd.m_stEquipItem[_U_WEAPON].xItem.m_stItemInfo.wAmount_GB = nSwordTrainPoint;
					bAddMsg = TRUE;
				}
				else if ( nWinExp > 0 )
				{
					sprintf(szExp, g_xMsg.GetMsg(1460), nWinExp);
					bAddMsg = TRUE;
				}
				
				if ( bAddMsg )
				{
					DWORD dwFont = GetChatColor(_CHAT_COLOR3);
					DWORD dwBack = GetChatColor(_CHAT_COLOR4);
					m_xInterface.MsgAdd(dwFont, dwBack, szExp);
				}

				break;
			}
			case SM_WEAPONLEVELUP:
			{
				CHAR szExp[MAX_PATH];

				BOOL bCheck = FALSE;
				INT	 nLevel = 0, nValue;
				WORD  wSwordTrainPoint;

				m_xInterface.m_xStatusWnd.m_stEquipItem[_U_WEAPON].xItem.m_stItemInfo.wAmount_GB = m_xMyHero.m_nTempWeaponExp - 60000;

				m_xInterface.m_xStatusWnd.m_stEquipItem[_U_WEAPON].xItem.m_stItemInfo.bLevel_R = tdm.wParam;

				for ( INT nCnt=0; nCnt<35; nCnt++ )
				{
					if ( g_nWeaponLevelTable[nCnt] <= tdm.wParam && g_nWeaponLevelTable[nCnt+1] > tdm.wParam )
					{
						bCheck = TRUE;
						break;
					}
				}

				if ( nCnt == 34 && bCheck == TRUE )
					nCnt = 35;

				nLevel = nCnt+1;

				if ( nLevel != tdm.wTag )
				{
					sprintf(szExp, "%s %d -> %d", g_xMsg.GetMsg(1462), nLevel - 1, nLevel);

					DWORD dwFont = GetChatColor(_CHAT_COLOR3);
					DWORD dwBack = GetChatColor(_CHAT_COLOR4);
					m_xInterface.MsgAdd(dwFont, dwBack, szExp);
				}
			}
			break;
			case SM_UPGRADEWEAPONOK:
			{
				CHAR szExp[MAX_PATH];

				if ( tdm.wParam )
				{
					CActor* pxActor = FindActor(tdm.nRecog);
					if ( !pxActor )
					{
						if ( tdm.nRecog == m_xMyHero.m_nIdentity )
							pxActor = &m_xMyHero;
					}

					if ( pxActor )
					{
						CMagic* pxMagic = new CMagic;

						char szDecodeMsg[_MAX_STRING_LEN];

						int nPos = fnDecode6BitBuf(pszMsg + _DEFBLOCKSIZE, szDecodeMsg, sizeof(szDecodeMsg));

						if ( nPos >= _MAX_STRING_LEN ) 
						{
							nPos = _MAX_STRING_LEN;
						}
						szDecodeMsg[nPos] = '\0';
						
						if ( pxMagic->CreateMagic(_SKILL_REFINE_S, pxActor->m_nPosX, pxActor->m_nPosY, pxActor->m_nPosX, pxActor->m_nPosY, pxActor, tdm.nRecog, 0) )
						{
							if ( nPos != 0 )
								sprintf( pxMagic->m_szServerNotice, szDecodeMsg);

							g_xGameProc.m_xGroundMagicList.Insert (pxMagic);
						}
						else
						{
							delete pxMagic;	
						}

						CRefineAdd* pxRefineAdd;
						pxRefineAdd = new CRefineAdd;
						if ( pxRefineAdd->CreateMagic(_SKILL_REFINEADD, pxActor->m_nPosX, pxActor->m_nPosY, pxActor->m_nPosX, pxActor->m_nPosY, NULL, 0, 0) )
							g_xGameProc.m_xMagicList.Insert (pxRefineAdd);
						else
							delete pxRefineAdd;

						pxActor->SetMotionFrame(_MT_ATTACKMODE, 4);
						pxActor->m_bWarMode = TRUE;
						pxActor->m_dwWarModeTime = 0;
						g_xGameProc.m_dwInputDelayTime	    = 2000;
						g_xGameProc.m_dwCurrInputDelayTime  = 0;

						g_xGameProc.m_xScatter.SetParticles(D3DVECTOR(pxActor->m_nScrnPosX-2, pxActor->m_nScrnPosY-30, 0));
					}
				}
				else
				{
					CActor* pxActor = FindActor(tdm.nRecog);
					if ( !pxActor )
					{
						if ( tdm.nRecog == m_xMyHero.m_nIdentity )
							pxActor = &m_xMyHero;
					}

					if ( pxActor )
					{
						CRefineAdd* pxRefineAdd;
						pxRefineAdd = new CRefineAdd;
						if ( pxRefineAdd->CreateMagic(_SKILL_REFINEADD, pxActor->m_nPosX, pxActor->m_nPosY, pxActor->m_nPosX, pxActor->m_nPosY, NULL, 0, 0) )
							g_xGameProc.m_xMagicList.Insert (pxRefineAdd);
						else
							delete pxRefineAdd;

						char szDecodeMsg[_MAX_STRING_LEN];

						int nPos = fnDecode6BitBuf(pszMsg + _DEFBLOCKSIZE, szDecodeMsg, sizeof(szDecodeMsg));

						if ( nPos >= _MAX_STRING_LEN ) 
						{
							nPos = _MAX_STRING_LEN;
						}
						szDecodeMsg[nPos] = '\0';
						
						CMagic* pxMagic = new CMagic;
						if ( pxMagic->CreateMagic(_SKILL_REFINE_F, pxActor->m_nPosX, pxActor->m_nPosY, pxActor->m_nPosX, pxActor->m_nPosY, pxActor, tdm.nRecog, 1000) )
						{
							if ( nPos != 0 )
								sprintf( pxMagic->m_szServerNotice, szDecodeMsg);

							pxActor->SetMotionFrame(_MT_ATTACKMODE, 4);
							pxActor->m_bWarMode = TRUE;
							pxActor->m_dwWarModeTime = 0;
							g_xGameProc.m_dwInputDelayTime	    = 2000;
							g_xGameProc.m_dwCurrInputDelayTime  = 0;
							g_xGameProc.m_xGroundMagicList.Insert (pxMagic);
						}
					}
				}
			}
			break;
			case SM_CHANGEMAGICCODE:
			{
				char szDecodeMsg[8192];
				char szDecodeInt[21];
				char szDecodeInt2[21];
				char szDecodeWord[21];

				nPos = fnDecode6BitBuf((pszMsg + _DEFBLOCKSIZE), szDecodeMsg, sizeof(szDecodeMsg));
				szDecodeMsg[nPos] = '\0';

				char szTemp[40];
				ZeroMemory(szTemp, 40);
				EncriptInt((byte *)&m_xMyHero.m_nIdentity, szTemp);
				INT nTemp = DecriptInt(szTemp);

				if ( m_xMyHero.m_nIdentity != nTemp )
				{
					INT ntest = 0;
				}
				g_xClientSocket.SendMagicCode(szTemp);

				int n = strlen(szDecodeMsg);

				if (strlen(szDecodeMsg) == 60) 
				{
					memcpy(szDecodeInt, szDecodeMsg, 20);
					szDecodeInt[20] = '\0';

					memcpy(szDecodeInt2, (char*)&szDecodeMsg[20], 20);
					szDecodeInt2[20] = '\0';

					memcpy(szDecodeWord, (char*)&szDecodeMsg[40], 20);
					szDecodeWord[20] = '\0';

					WORD wRecog1 = DecriptWord(szDecodeInt);
					WORD wRecog2 = DecriptWord(szDecodeInt2);
					WORD wParam = DecriptWord(szDecodeWord);

					m_bNoticeSeed1 = LOBYTE(wParam);
					m_bNoticeSeed2 = HIBYTE(wParam);

					m_wNoticeSeed3 = wRecog1;
					m_wNoticeSeed4 = wRecog2;
				}
			}
			break;
			case SM_WEAPONPREFIXCHANGED:
			{
				char szDecodeMsg[_MAX_STRING_LEN];

				int nPos = fnDecode6BitBuf(pszMsg + _DEFBLOCKSIZE, szDecodeMsg, sizeof(szDecodeMsg));

				if ( nPos >= _MAX_STRING_LEN ) 
				{
					nPos = _MAX_STRING_LEN;
				}
				szDecodeMsg[nPos] = '\0';

				for ( INT nI=0; nI<_EQUIP_MAX_CELL; nI++ )
				{
					if ( m_xInterface.m_xStatusWnd.m_stEquipItem[nI].xItem.m_stItemInfo.nMakeIndex == tdm.nRecog )
						sprintf( m_xInterface.m_xStatusWnd.m_stEquipItem[nI].xItem.m_stItemInfo.Prefix, szDecodeMsg );
				}
			}
			break;
			case SM_CUSTOMMONACTION:
			{
				
				char szDecodeMsg[1024];
				BYTE bDir;
				INT nPosX, nPosY, nActMsg, nPos;

				CActor* pxActor = FindActor(tdm.nRecog);

				if (pxActor)
				{

					bDir = tdm.wSeries;
					nPosX = tdm.wParam;
					nPosY = tdm.wTag;

					nPos = fnDecode6BitBuf((pszMsg + _DEFBLOCKSIZE), szDecodeMsg, sizeof(szDecodeMsg));
					szDecodeMsg[nPos] = '\0';
					nActMsg = atoi(szDecodeMsg);

					switch(nActMsg)
					{
					case 1:
						pxActor->SetMotionFrame(_MT_MON_ATTACK_A, bDir);
						break;
					case 2:
						pxActor->SetMotionFrame(_MT_MON_ATTACK_B, bDir);
						break;
					case 3:
						pxActor->SetMotionFrame(_MT_MON_SPELL_A, bDir);
						break;
					case 4:
						pxActor->SetMotionFrame(_MT_MON_SPELL_B, bDir);
						break;
					}
				}
			}
			break;
			case SM_RECONNECT:
			{
				char	szDecodeMsg[8192];
				char	*pszPort = NULL;

				m_xMyHero.m_nIdentity = 0;

				nPos = fnDecode6BitBuf((pszMsg + _DEFBLOCKSIZE), szDecodeMsg, sizeof(szDecodeMsg));
				szDecodeMsg[nPos] = '\0';

				if (pszPort = strchr(szDecodeMsg, '/'))
				{
					*pszPort++ = '\0';

					g_xClientSocket.DisconnectToServer();

					ActorListClear();
					Sleep(500);
					
					m_bNoticeSeed1 = 0;
					m_bNoticeSeed2 = 0;
					m_wNoticeSeed3 = 0;
					m_wNoticeSeed4 = 0;

					m_dwInputDelayTime		= 500;
					m_dwCurrInputDelayTime	= 0;

					g_xClientSocket.ConnectToServer(g_xMainWnd.GetSafehWnd(), szDecodeMsg, atoi(pszPort));
				}
				break;
			}
			case SM_CHANGEGUILDNAME:
			{
				char  pszDecodeMsg[1024], pszMateName[1024];
				char* pszGuildPos = NULL;
				char* pszMatePos = NULL;
				int   nLen1, nLen2 = 0;
				
				INT nPos = fnDecode6BitBuf((pszMsg + _DEFBLOCKSIZE), pszDecodeMsg, sizeof(pszDecodeMsg));
				pszDecodeMsg[nPos] = '\0';

				pszMatePos = strchr(pszDecodeMsg, '/*'); 

				if ( pszMatePos )
				{
					*pszMatePos++ = '\0';

					nLen1 = strlen(pszDecodeMsg);

					if ( nLen1 > 0 )
						pszDecodeMsg[nLen1-1] = '\0';

					ZeroMemory(m_xMyHero.m_szMateName, 60);
					sprintf(m_xMyHero.m_szMateName, "%s", pszMatePos);

				}
				else
				{
					ZeroMemory(m_xMyHero.m_szMateName, 60);
				}

				pszGuildPos = strchr(pszDecodeMsg, '/');

				ZeroMemory(m_xMyHero.m_szGuildName, 60);
				ZeroMemory(m_xMyHero.m_szRankName, 60);

				if ( pszGuildPos )
				{
					*pszGuildPos++ = '\0';

					// 화면상보일 문자열의 최대 길이를 30로 한다.
					nLen1 = strlen(pszDecodeMsg);
					nLen2 = strlen(pszGuildPos);

					int ntest = 0;
					if ( nLen1 + nLen2 > 40 )
					{
						nLen2 = 40 - nLen1;
						*(pszGuildPos + nLen2) = '\0';
					}

					sprintf(m_xMyHero.m_szGuildName, "%s", pszDecodeMsg);
					sprintf(m_xMyHero.m_szRankName, "%s", pszGuildPos);
				}

				break;
			}
			case SM_SENDMYMAGIC:
			{
				m_xInterface.m_xMagicWnd.SetMyMagic(tdm.wSeries, (pszMsg + _DEFBLOCKSIZE));
				break;
			} 
			case SM_DELMAGIC:
			{
				m_xInterface.m_xMagicWnd.DelMyMagic(tdm.nRecog);
				break;
			}
			case SM_MAGIC_LVEXP:
			{
				m_xInterface.m_xMagicWnd.MagicExpUp(tdm.nRecog, MAKELONG(tdm.wTag, tdm.wSeries), (BYTE)tdm.wParam);
				break;
			}
			case SM_SOUND:
			{
				if ( tdm.nRecog == 0 )
					g_SoundManager.SndmngrPlayWavSound(tdm.wParam, 0, 0);
				else
				{
					CActor* pxActor = FindActor(tdm.nRecog);
					if (pxActor)
					{
						pxActor->PlayActSound();
					}
				}
			}
			break;
			// 가방창 아이템 리스트
			case SM_BAGITEMS:
			{
				char *pszItem  = (pszMsg + _DEFBLOCKSIZE);
				char *pszNextItem;
				int  nCount = 0;

				CLIENTITEMRCD	stReceivedItem;
 				m_xInterface.m_xInventoryWnd.DeleteAllInvenItem();

				do
				{
					if ( pszNextItem = strchr(pszItem, '/') )
					{
						CItem xItem;

						*pszNextItem = '\0';

						fnDecode6BitBuf(pszItem, (char*)&stReceivedItem, sizeof(CLIENTITEMRCD));

						xItem.SetItem(stReceivedItem, 0);

						m_xInterface.m_xInventoryWnd.AddInvenItem(xItem, 0, FALSE);

						pszItem = pszNextItem + 1;
						
						nCount++;
					}
				} while (nCount < tdm.wSeries && pszNextItem);

				m_xInterface.CheckItemPos(m_xMyHero.m_szName);
				m_xInterface.m_xBeltWnd.LoadBeltPosition();
#ifdef _DEBUG
				m_xInterface.m_xUtilWnd.LoadUtilSet();
#endif
				m_xInterface.m_xMagicShortcutWnd.LoadMagicKeySet();
				break;
			}
			case SM_SENDUSEITEMS:
			{
				CLIENTITEMRCD cItemRcd[_EQUIP_MAX_CELL];

				char *pszUseIndex = (pszMsg + _DEFBLOCKSIZE);
				char *pszItem;
				char *pszNextItem;

				ZeroMemory(cItemRcd, sizeof(CLIENTITEMRCD));

				for (int i = 0; i < _EQUIP_MAX_CELL; i++)
				{
					if ( pszItem = strchr(pszUseIndex, '/') )
					{
						*pszItem = '\0';
						pszItem++;
						
						if ( pszNextItem = strchr(pszItem, '/') )
						{
							*pszNextItem = '\0';

							fnDecode6BitBuf(pszItem, (char*)&cItemRcd[i], sizeof(CLIENTITEMRCD));	
							
							CItem xItem;
							xItem.SetItem(cItemRcd[i], 0);

							m_xInterface.m_xStatusWnd.m_stEquipItem[atoi(pszUseIndex)].xItem = xItem;
							m_xInterface.m_xStatusWnd.m_stEquipItem[atoi(pszUseIndex)].bSetted = TRUE;

							pszUseIndex = pszNextItem + 1;
						}
						else
							break;
					}
					else
						break;
				}
				break;
			}
			case SM_COUNTERITEMCHANGE:
			{
				DWORD dwFont = GetChatColor(_CHAT_COLOR3);
				DWORD dwBack = GetChatColor(_CHAT_COLOR8);

				m_xInterface.m_xInventoryWnd.ChangeItemCount(tdm.nRecog, tdm.wParam);
			}
			break;
			case SM_ADDITEM:
			{
				CLIENTITEMRCD	stReceivedItem;

				char *pszItem = (pszMsg + _DEFBLOCKSIZE);

				fnDecode6BitBuf(pszItem, (char*)&stReceivedItem, sizeof(CLIENTITEMRCD));

				CItem xItem;
				xItem.SetItem(stReceivedItem, 0);
				m_xInterface.m_xInventoryWnd.AddInvenItem(xItem, 0, FALSE);

				CHAR szSysMsg[MAX_PATH];
				
				// 추석맞이 이벤트용.
				BOOL bChk = FALSE;
				CHAR pszEventItm[20];
				for ( INT nCnt = 0; nCnt < 10; nCnt++ )
				{
					sprintf(pszEventItm, "%s%d", g_xMsg.GetMsg(1409), nCnt);
					if ( !strcmp(xItem.m_stItemInfo.stStdItem.szName, pszEventItm) )
					{
						sprintf(szSysMsg, g_xMsg.GetMsg(1463));
						bChk = TRUE;
						break;
					}				
				}

				if ( !bChk )
				{
					if (xItem.m_stItemInfo.stStdItem.bThrow > _MULTIPLE_TYPE_ITEM)
					{
						DWORD	dwCount = 0;
						dwCount = xItem.m_stItemInfo.wAmount_GB;

						sprintf(szSysMsg, g_xMsg.GetMsg(1461), xItem.m_stItemInfo.stStdItem.szName, dwCount);
					}
					else
						sprintf(szSysMsg, g_xMsg.GetMsg(1465), xItem.m_stItemInfo.stStdItem.szName);
				}

				m_xInterface.m_xClientSysMsg.AddSysMsg(szSysMsg);

				break;
			}
			case SM_DELITEM:
			{											
				CLIENTITEMRCD	stReceivedItem;

				char *pszItem = (pszMsg + _DEFBLOCKSIZE);

				fnDecode6BitBuf(pszItem, (char*)&stReceivedItem, sizeof(CLIENTITEMRCD));

				if ( strcmp( stReceivedItem.stStdItem.szName, "견혼령" ) == 0 )
				{
					DWORD	dwFogColor = RGB(10, 10, 10);
					FLOAT	fDstDarkRate = 0.0f;

					switch ( m_bFogState )
					{
					case _FOGSTATE_DAY:
						{
							dwFogColor = RGB(255, 255, 255);
							break;
						}
					case _FOGSTATE_NIGHT:
						{
							dwFogColor = RGB(15, 15, 15);
							break;
						}
					case _FOGSTATE_DAWN:
						{
							dwFogColor = RGB(85, 85, 85);
							break;
						}
					}
					m_xLightFog.ChangeLightColor(dwFogColor);
				}


				m_xInterface.m_xInventoryWnd.DeleteInvenItem(stReceivedItem.nMakeIndex, stReceivedItem.stStdItem.szName);
				m_xInterface.m_xStatusWnd.DeleteEquipItem(stReceivedItem.nMakeIndex, stReceivedItem.stStdItem.szName);

				if ( m_xInterface.m_stCommonItem.xItem.m_stItemInfo.nMakeIndex == stReceivedItem.nMakeIndex )
					ZeroMemory(&m_xInterface.m_stCommonItem, sizeof(COMMONITEMSET));

				CHAR szSysMsg[MAX_PATH];
				sprintf(szSysMsg, g_xMsg.GetMsg(1466), stReceivedItem.stStdItem.szName);
				m_xInterface.m_xClientSysMsg.AddSysMsg(szSysMsg);

				break;
			}
			case SM_UPDATEITEM:
			{
				CLIENTITEMRCD	stReceivedItem;

				char *pszItem = (pszMsg + _DEFBLOCKSIZE);

				fnDecode6BitBuf(pszItem, (char*)&stReceivedItem, sizeof(CLIENTITEMRCD));

				CItem xItem;
				xItem.SetItem(stReceivedItem, 0);

				 if (  (m_xInterface.m_xInventoryWnd.DeleteInvenItem(xItem.m_stItemInfo.nMakeIndex, xItem.m_stItemInfo.stStdItem.szName)) == TRUE )
				 {
					 m_xInterface.m_xInventoryWnd.AddInvenItem(xItem, 0, FALSE);
				 }

				 if (  (m_xInterface.m_xStatusWnd.DeleteEquipItem(xItem.m_stItemInfo.nMakeIndex, xItem.m_stItemInfo.stStdItem.szName)) == TRUE )
				 {
					 m_xInterface.m_xStatusWnd.AddEquipItem(xItem, xItem.m_shCellNum, FALSE);
				 }

				 m_xInterface.ItemClickSound(&xItem);
				 break;
			}
			case SM_DELITEMS:
			{		
				int nItemIndex;
				CHAR szDecodeMsg[10240];

				char *pszItem;
				char* pszItemName;
				char *pszItemIndex;
				int  nCount = 0;

				nPos = fnDecode6BitBuf((pszMsg + _DEFBLOCKSIZE), szDecodeMsg, sizeof(szDecodeMsg));
				szDecodeMsg[nPos] = NULL;
				pszItem = szDecodeMsg;

				do
				{
					pszItemName = pszItem;
					pszItemIndex = strchr(pszItemName, '/');
					*pszItemIndex = NULL;
					pszItemIndex ++;

					pszItem = strchr(pszItemIndex, '/');
					*pszItem = NULL;
					pszItem ++;

					nItemIndex = atoi(pszItemIndex);

					m_xInterface.m_xInventoryWnd.DeleteInvenItem(nItemIndex, pszItemName);
					m_xInterface.m_xStatusWnd.DeleteEquipItem(nItemIndex, pszItemName);

					nCount++;
				} while (nCount < tdm.wSeries && pszItem);

				break;
			}
			case SM_EAT_OK:
			{
				CHAR szSysMsg[MAX_PATH];

				// 추석맞이 이벤트용.
				CHAR pszName[MAX_PATH];
				ZeroMemory(pszName, MAX_PATH);
				CHAR pszEventItm[20];

				for ( INT nCnt = 0; nCnt < 10; nCnt++ )
				{
					sprintf(pszEventItm, "%s%d", g_xMsg.GetMsg(1409), nCnt);
					if ( !strcmp(m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName, pszEventItm) )
					{
						sprintf(pszName, g_xMsg.GetMsg(1409));
					}				
				}

				if ( !pszName[0] )
				{
					sprintf(pszName, m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName);
				}

				sprintf(szSysMsg, g_xMsg.GetMsg(1464), pszName);
				m_xInterface.m_xClientSysMsg.AddSysMsg(szSysMsg);

				m_xInterface.ItemUseSound(&m_xInterface.m_stCommonItem.xItem);

				if ( m_xInterface.m_stCommonItem.bIsBeltItem || m_xInterface.m_stCommonItem.bIsUtilItem )
				{
					if (tdm.wParam > 0)
						sprintf(szSysMsg, g_xMsg.GetMsg(1467), pszName, tdm.wParam);
					else
						sprintf(szSysMsg, g_xMsg.GetMsg(1468), pszName);

					m_xInterface.m_xClientSysMsg.AddSysMsg(szSysMsg);
				}

				if (m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.bThrow == 3)
				{
					DWORD	dwCount = m_xInterface.m_stCommonItem.xItem.m_stItemInfo.wAmount_GB;

					if (dwCount > 1)
					{
						dwCount = tdm.wParam;
		
						m_xInterface.m_xInventoryWnd.ChangeItemCount(m_xInterface.m_stCommonItem.xItem.m_stItemInfo.nMakeIndex, tdm.wParam);
						if (!m_xInterface.m_stCommonItem.bIsBeltItem)
						{
							INT nBeltNum = 0;

							nBeltNum = m_xInterface.m_xBeltWnd.FindSameItemInBelt(m_xInterface.m_stCommonItem.xItem);

							if (nBeltNum != -1)
							{
								m_xInterface.m_xBeltWnd.m_stBeltItem[nBeltNum].xItem.m_stItemInfo.wAmount_GB = dwCount;
							}
						}

						m_xInterface.m_stCommonItem.xItem.m_stItemInfo.wAmount_GB = dwCount;

						if (m_xInterface.m_stCommonItem.bIsBeltItem)
							m_xInterface.m_xBeltWnd.SetBeltFromCommon(m_xInterface.m_stCommonItem.xItem.m_shCellNum, &m_xInterface.m_stCommonItem);
						else if ( !m_xInterface.m_stCommonItem.bIsUtilItem )
						{
							m_xInterface.m_xInventoryWnd.AddInvenItem(m_xInterface.m_stCommonItem.xItem, m_xInterface.m_stCommonItem.xItem.m_shCellNum, TRUE);
						}
							
						ZeroMemory(&m_xInterface.m_stCommonItem, sizeof(COMMONITEMSET));
					}
					else
					{
						INT nBeltNum = 0;

						nBeltNum = m_xInterface.m_xBeltWnd.FindSameItemInBelt(m_xInterface.m_stCommonItem.xItem);

						if (nBeltNum != -1)
						{
							m_xInterface.m_xBeltWnd.DeleteBeltItem(nBeltNum);
						}

						m_xInterface.m_xInventoryWnd.DeleteInvenItem(m_xInterface.m_stCommonItem.xItem.m_stItemInfo.nMakeIndex, m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName);
						ZeroMemory(&m_xInterface.m_stCommonItem, sizeof(COMMONITEMSET));
					}
				}
				else
					ZeroMemory(&m_xInterface.m_stCommonItem, sizeof(COMMONITEMSET));
				break;
			}
			case SM_EAT_FAIL:
			{
				if ( m_xInterface.m_stCommonItem.bSetted )
				{
					if ( m_xInterface.m_stCommonItem.bSetted && m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.bStdMode == 51 )
					{
						m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GAME, _OK, g_xMsg.GetMsg(1414));
					}

					if ( !m_xInterface.m_stCommonItem.bIsBeltItem && !m_xInterface.m_stCommonItem.bIsUtilItem && strcmp(m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(1050)) )
					{
						m_xInterface.m_xInventoryWnd.AddInvenItem(m_xInterface.m_stCommonItem.xItem, m_xInterface.m_stCommonItem.xItem.m_shCellNum, TRUE);
					}
					else if ( m_xInterface.m_stCommonItem.bIsBeltItem )
						m_xInterface.m_xBeltWnd.AddBeltItem(m_xInterface.m_stCommonItem.xItem, m_xInterface.m_stCommonItem.xItem.m_shCellNum, TRUE);
				}

				ZeroMemory(&m_xInterface.m_stCommonItem, sizeof(COMMONITEMSET));
				break;
			}
			case SM_ADDMAGIC:
			{
				m_xInterface.m_xMagicWnd.AddNewMagic((pszMsg + _DEFBLOCKSIZE));
				break;
			}
			case SM_TAKEON_OK:
			{

				FEATURE stFeature;
				memcpy(&stFeature, &tdm.nRecog, sizeof(LONG));

				g_xGameProc.m_xMyHero.m_bEftFeature = stFeature.bDress;
				stFeature.bDress  = stFeature.bDress & 15;

				m_xInterface.ItemClickSound(&m_xInterface.m_xStatusWnd.m_stTakeOnItemSet.xItem);

				g_xGameProc.m_xMyHero.m_stFeatureEx.wDressColor = tdm.wParam;
				g_xGameProc.m_xMyHero.m_stFeatureEx.wHairColor = tdm.wTag;
				g_xGameProc.m_xMyHero.m_stFeatureEx.bWeaponColor = tdm.wSeries;
				g_xGameProc.m_xMyHero.ChangeFeature(stFeature, g_xGameProc.m_xMyHero.m_stFeatureEx);

				// 견혼령을 장착한 경우 밝기를 바꾸어준다.
				if ( strcmp( m_xInterface.m_xStatusWnd.m_stTakeOnItemSet.xItem.m_stItemInfo.stStdItem.szName, "견혼령" ) == 0 )
				{
					DWORD	dwFogColor;
					FLOAT	fDstDarkRate = 0.0f;

					fDstDarkRate = 255.0f;
					dwFogColor = RGB(fDstDarkRate, fDstDarkRate, fDstDarkRate);
					m_xLightFog.ChangeLightColor(dwFogColor);
				}
				else if ( m_xInterface.m_xStatusWnd.m_stTakeOnItemSet.xItem.m_shCellNum == 2 )
				{
					DWORD	dwFogColor = RGB(10, 10, 10);
					FLOAT	fDstDarkRate = 0.0f;

					switch ( m_bFogState )
					{
					case _FOGSTATE_DAY:
						{
							dwFogColor = RGB(255, 255, 255);
							break;
						}
					case _FOGSTATE_NIGHT:
						{
							dwFogColor = RGB(15, 15, 15);
							break;
						}
					case _FOGSTATE_DAWN:
						{
							dwFogColor = RGB(85, 85, 85);
							break;
						}
					}
					m_xLightFog.ChangeLightColor(dwFogColor);
				}

				// 장착창의 착용아이템(m_stTakeOnItemSet)을 장착창의 맞는셀에 적용시키고, 착용아이템(m_stTakeOnItemSet)을 지운다.
				m_xInterface.m_xStatusWnd.SetEquipFromTakeOn();

				// 만약 공통(마우스)아이템이 있다면 인벤토리윈도우의 빈셀에 넣고, 공통(마우스)아이템을 지운다.
				ZeroMemory(&m_xInterface.m_stCommonItem, sizeof(COMMONITEMSET));
				break;
			}
			case SM_TAKEON_FAIL:
			{
				// 장착창의 착용아이템(m_stTakeOnItemSet)을 다시 인벤토리에 넣는다.
				// 만약에 공통(마우스)아이템이 있다면 그걸 착용셀에 넣는다.

//				FEATURE stFeature;
//				memcpy(&stFeature, &tdm.nRecog, sizeof(LONG));
//				g_xGameProc.m_xMyHero.m_stFeatureEx.wDressColor = tdm.wParam;
//				g_xGameProc.m_xMyHero.m_stFeatureEx.wHairColor = tdm.wTag;
//				g_xGameProc.m_xMyHero.ChangeFeature(stFeature, g_xGameProc.m_xMyHero.m_stFeatureEx);

				m_xInterface.ItemClickSound(&m_xInterface.m_xStatusWnd.m_stTakeOnItemSet.xItem);

				if ( m_xInterface.m_xStatusWnd.m_stTakeOnItemSet.bSetted )
				{
					m_xInterface.m_xInventoryWnd.AddInvenItem(m_xInterface.m_xStatusWnd.m_stTakeOnItemSet.xItem, 0, FALSE);
					ZeroMemory(&m_xInterface.m_xStatusWnd.m_stTakeOnItemSet, sizeof(ITEMSET));
				}
				if ( m_xInterface.m_stCommonItem.bSetted )
				{
					m_xInterface.m_xStatusWnd.SetEquipFromCommon(m_xInterface.m_stCommonItem.xItem.m_shCellNum, &m_xInterface.m_stCommonItem);
	//												ZeroMemory(&m_xInterface.m_stCommonItem, sizeof(ITEMSET));
				}
				break;
			}
			case SM_TAKEOFF_OK:
			{
				FEATURE stFeature;
				memcpy(&stFeature, &tdm.nRecog, sizeof(LONG));

				g_xGameProc.m_xMyHero.m_bEftFeature = stFeature.bDress;
				stFeature.bDress  = stFeature.bDress & 15;

				g_xGameProc.m_xMyHero.ChangeFeature(stFeature, g_xGameProc.m_xMyHero.m_stFeatureEx);

				m_xInterface.ItemClickSound(&m_xInterface.m_stCommonItem.xItem);

				if ( strcmp( m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName, "견혼령" ) == 0 )
				{
					DWORD	dwFogColor = RGB(10, 10, 10);
					FLOAT	fDstDarkRate = 0.0f;

					switch ( m_bFogState )
					{
					case _FOGSTATE_DAY:
						{
							dwFogColor = RGB(255, 255, 255);
							break;
						}
					case _FOGSTATE_NIGHT:
						{
							dwFogColor = RGB(15, 15, 15);
							break;
						}
					case _FOGSTATE_DAWN:
						{
							dwFogColor = RGB(85, 85, 85);
							break;
						}
					}
					m_xLightFog.ChangeLightColor(dwFogColor);
		//			m_xMyHero.m_bLightSize = (BYTE)(lpPacketMsg->stDefMsg.wParam);
				}

				ZeroMemory(&m_xInterface.m_stCommonItem, sizeof(COMMONITEMSET));
				break;
			}
			case SM_TAKEOFF_FAIL:
			{
				if ( m_xInterface.m_stCommonItem.bSetted )
				{
					m_xInterface.ItemClickSound(&m_xInterface.m_stCommonItem.xItem);
					m_xInterface.m_xStatusWnd.SetEquipFromCommon(m_xInterface.m_stCommonItem.xItem.m_shCellNum, &m_xInterface.m_stCommonItem);
				}
				break;
			}
			case SM_ITEMSHOW:
			{
				BOOL bExisted = FALSE;

				LPGROUNDITEM				pstItem = NULL;
				CListNode < GROUNDITEM >	*pNode;

				for ( pNode = m_stMapItemList.GetHead(); pNode; pNode = pNode->GetNext() )
				{
					pstItem = pNode->GetData();

					if ( pstItem )
					{
						if ( pstItem->nRecog == tdm.nRecog )
						{
							bExisted = TRUE;
							break;
						}
					}
				}	

				if ( !bExisted )
				{
					LPGROUNDITEM pstItem = new GROUNDITEM;

					pstItem->nRecog  = tdm.nRecog;
					pstItem->nTileX = tdm.wParam;
					pstItem->nTileY = tdm.wTag;
					pstItem->wLooks  = tdm.wSeries;
					pstItem->nThrow  = 0;

					CHAR pszItemName[40];
					nPos = fnDecode6BitBuf((pszMsg + _DEFBLOCKSIZE), (char*)pszItemName, sizeof(pszItemName));
					pszItemName[nPos] = '\0';

					CHAR* pszThrow = NULL;
					if ( pszThrow = strchr(pszItemName, '/') )
					{
						*pszThrow = '\0';
						pstItem->nThrow = atoi(pszItemName);

						strcpy(pstItem->szItemName, ++pszThrow);
					}
					else
					{
						strcpy(pstItem->szItemName, pszItemName);
					}

					pstItem->dwLastShineTick = timeGetTime();
					pstItem->dwShineCurrDelay = 0;
					pstItem->dwCurrShineFrm	 = 0;
					pstItem->dwRandShineDelay = GetRandomNum(3000, 7000);

					m_stMapItemList.Insert (pstItem);
				}											

				break;
			}
			case SM_ITEMHIDE:
			{
				LPGROUNDITEM pstItem = NULL;
				CListNode < GROUNDITEM >	*pNode;

				for ( pNode = m_stMapItemList.GetHead(); pNode; pNode = pNode->GetNext() )
				{
					pstItem = pNode->GetData();												

					if ( pstItem )
					{					
						if ( pstItem->nRecog == tdm.nRecog )
						{
							m_stMapItemList.RemoveNode(pNode);
							SAFE_DELETE(pstItem);
							return;
						}
					}
				}	

				break;
			}
			case SM_SHOWEVENT:
			{
				BOOL bExisted = FALSE;

				_TSHORTMSSEAGE stShortMsg;
				
				fnDecode6BitBuf((pszMsg + _DEFBLOCKSIZE), (char*)&stShortMsg, sizeof(_TSHORTMSSEAGE));

				CMagic*						pxMagic = NULL;
				CListNode < CMagic >		*pNode;
				LPEVENTIMG					pstEvent = NULL;
				CListNode < EVENTIMG >		*pNode2;

				for ( pNode = m_xGroundMagicList.GetHead(); pNode; pNode = pNode->GetNext() )
				{
					pxMagic = pNode->GetData();

					if ( pxMagic )
					{
						switch ( pxMagic->m_wMagicNum )
						{
							case _SKILL_EARTHFIRE: 
							case _SKILL_KANGMAK:
							case _SKILL_HOLYSHIELD:
							case _SKILL_LIGHTWALL:
							case _SKILL_ICEWALL:
							case _SKILL_JISOKGYE:
							{
								CRepeatMagic* pxRepeatMagic = (CRepeatMagic*)pxMagic;
								if ( pxRepeatMagic->m_nEventID == tdm.nRecog )
									bExisted = TRUE;

								break;
							}
						}
					}
				}	

				if ( !bExisted )
				{
					for ( pNode2 = m_stEventImgList.GetHead(); pNode2; pNode2 = pNode2->GetNext() )
					{
						pstEvent = pNode2->GetData();

						if ( pstEvent )
						{
							if ( pstEvent->nEventID == tdm.nRecog )
							{
								bExisted = TRUE;
								break;
							}
						}
					}
				}	
				
				// 생성한다.
				if ( !bExisted )
				{
					WORD wEffectNum = 0;

					if ( tdm.wParam == _ET_FIRE )
					{
						wEffectNum = _SKILL_EARTHFIRE;
						CRepeatMagic* pxRepeatMagic;
						pxRepeatMagic = new CRepeatMagic;
						if ( pxRepeatMagic->CreateMagic(tdm.nRecog, wEffectNum, 0, 0, tdm.wTag, tdm.wSeries, 0XFFFFFFFF, NULL, NULL) ) 
						{
							pxRepeatMagic->m_dwCurrFrame += GetRandomNum(1, 8);
							g_xGameProc.m_xGroundMagicList.Insert (pxRepeatMagic);
						}
						else
							delete pxRepeatMagic;
					}
					else if ( tdm.wParam == _ET_FIRE_HIGH )
					{
						wEffectNum = _SKILL_JISOKGYE;
						CRepeatMagic* pxRepeatMagic;
						pxRepeatMagic = new CRepeatMagic;
						if ( pxRepeatMagic->CreateMagic(tdm.nRecog, wEffectNum, 0, 0, tdm.wTag, tdm.wSeries, 0XFFFFFFFF, NULL, NULL) ) 
						{
							pxRepeatMagic->m_dwCurrFrame += GetRandomNum(1, 8);
							g_xGameProc.m_xGroundMagicList.Insert (pxRepeatMagic);
						}
						else
							delete pxRepeatMagic;
					}
					else if ( tdm.wParam == _ET_ICEWALL )
					{
						wEffectNum = _SKILL_ICEWALL;
						CMiddleRepeateMagic* pxMiddleRepeateMagic;
						pxMiddleRepeateMagic = new CMiddleRepeateMagic;
						if ( pxMiddleRepeateMagic->CreateMagic(tdm.nRecog, wEffectNum, 0, 0, tdm.wTag, tdm.wSeries, 0XFFFFFFFF, NULL, NULL) ) 
						{
							g_xGameProc.m_xGroundMagicList.Insert (pxMiddleRepeateMagic);
						}
						else
							delete pxMiddleRepeateMagic;
					}
					else if ( tdm.wParam == _ET_WINDWALL )
					{
						wEffectNum = _SKILL_KANGMAK;
						CRepeatMagic* pxRepeatMagic;
						pxRepeatMagic = new CRepeatMagic;
						if ( pxRepeatMagic->CreateMagic(tdm.nRecog, wEffectNum, 0, 0, tdm.wTag, tdm.wSeries, 0XFFFFFFFF, NULL, NULL) ) 
						{
							pxRepeatMagic->m_dwCurrFrame += GetRandomNum(1, 8);
							g_xGameProc.m_xGroundMagicList.Insert (pxRepeatMagic);
						}
						else
							delete pxRepeatMagic;
					}
					else if ( tdm.wParam == _ET_HOLYCURTAIN )
					{
						wEffectNum = _SKILL_HOLYSHIELD;
						CRepeatMagic* pxRepeatMagic;
						pxRepeatMagic = new CRepeatMagic;
						if ( pxRepeatMagic->CreateMagic(tdm.nRecog, wEffectNum, 0, 0, tdm.wTag, tdm.wSeries, 0XFFFFFFFF, NULL, NULL) )
						{
							pxRepeatMagic->m_dwCurrFrame += GetRandomNum(1, 8);
							g_xGameProc.m_xGroundMagicList.Insert (pxRepeatMagic);
						}
						else							delete pxRepeatMagic;
					}
					// 뢰벽.
					/*
					else if ( _SKILL_LIGHTWALL )
					{
					}*/
					else if ( tdm.wParam == _ET_SCULPEICE )
					{
						LPEVENTIMG pstEvent = new EVENTIMG;

						pstEvent->nType	   = _ET_SCULPEICE;
						pstEvent->nEventID = tdm.nRecog;
						pstEvent->dwTick  = timeGetTime();
						pstEvent->nTileX = tdm.wTag;
						pstEvent->nTileY = tdm.wSeries;

						pstEvent->dwLifeTime = 0XFFFF;
						pstEvent->wFrameNum = 210;
						pstEvent->wOutDelay = 0;
						pstEvent->bUseAlpha = FALSE;

						g_xGameProc.m_stEventImgList.Insert (pstEvent);
					}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					else if ( tdm.wParam == _ET_PILESTONES )
					{
						LPEVENTIMG pstEvent = new EVENTIMG;

						pstEvent->nType	   = _ET_PILESTONES;
						pstEvent->nEventID = tdm.nRecog;
						pstEvent->dwTick  = timeGetTime();
						pstEvent->nTileX = tdm.wTag;
						pstEvent->nTileY = tdm.wSeries;
						pstEvent->dwLifeTime = 0XFFFF;
						pstEvent->wFrameNum = 230;
						pstEvent->wOutDelay = 0;
						pstEvent->bUseAlpha = FALSE;
						g_xGameProc.m_stEventImgList.Insert (pstEvent);
					}
					else if ( tdm.wParam == _ET_DIGOUTZOMBI )
					{
					}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				}							
				break;
			}
			case SM_HIDEEVENT:
			{
				BOOL bChecked = FALSE;

				CMagic*						pxMagic = NULL;
				CListNode < CMagic >		*pNode;

				for ( pNode = m_xGroundMagicList.GetHead(); pNode; pNode = pNode->GetNext() )
				{
					CRepeatMagic* pxRepeatMagic = NULL;

					pxMagic = pNode->GetData();					
					
					if ( pxMagic )
					{
						switch ( pxMagic->m_wMagicNum )
						{
						case _SKILL_EARTHFIRE: 
						case _SKILL_HOLYSHIELD:
						case _SKILL_LIGHTWALL:
						case _SKILL_ICEWALL:
						case _SKILL_KANGMAK:
						case _SKILL_JISOKGYE:
							{
								pxRepeatMagic = (CRepeatMagic*)pxMagic;
								break;
							}
						}

						if ( pxRepeatMagic && pxRepeatMagic->m_nEventID == tdm.nRecog )
						{
							pxRepeatMagic->m_dwMagiLifeTotal = 0;
							bChecked = TRUE;

							if ( pxMagic->m_wMagicNum == _SKILL_EARTHFIRE )
							{
								INT nRand = GetRandomNum(1000, 2000);
								// 연기.
								if ( pxRepeatMagic->m_wMagicNum == _SKILL_EARTHFIRE )
								{
									WORD wEffectNum = (WORD)GetRandomNum(_EVENT_LEFTFIRE1, _EVENT_LEFTFIRE5);

									CRepeatMagic* pxLeftFire;
									pxLeftFire = new CRepeatMagic;

									if ( pxLeftFire->CreateMagic(tdm.nRecog, wEffectNum, 0, 0, tdm.wTag, tdm.wSeries, nRand, NULL, NULL) )
									{
										g_xGameProc.m_xGroundMagicList.Insert (pxLeftFire);
									}
									else
									{
										delete pxLeftFire;
									}

									// 바닥에 깔린 재.
									LPEVENTIMG pstEvent = new EVENTIMG;

									pstEvent->nType	    = 0;
									pstEvent->nEventID	= 0;
									pstEvent->dwTick	= timeGetTime();
									pstEvent->nTileX	= tdm.wTag;
									pstEvent->nTileY	= tdm.wSeries;
									pstEvent->dwLifeTime = nRand + 800;
									pstEvent->wFrameNum = 220;
									pstEvent->wOutDelay = 0;
									pstEvent->bUseAlpha = TRUE;
									g_xGameProc.m_stEventImgList.Insert (pstEvent);
								}
							}
					

							break; // for 문을 빠져나간다.
						}
					}					
				}	

				if ( !bChecked )
				{
					LPEVENTIMG					pstEvent = NULL;
					CListNode < EVENTIMG >		*pNode2;

					for ( pNode2 = m_stEventImgList.GetHead(); pNode2; pNode2 = pNode2->GetNext() )
					{
						pstEvent = pNode2->GetData();
						
						if ( pstEvent && pstEvent->nEventID == tdm.nRecog )
						{
							pstEvent->dwLifeTime = 0;
							bChecked = TRUE;
							break;
						}
					}	
				}
				break;
			}
			case SM_REFLEXPOWER:
			{
				if ( m_xMyHero.m_nIdentity == tdm.nRecog )
				{
					CMagic* pxMagic;
					pxMagic = new CMagic;
					if ( pxMagic->CreateMagic(_SKILL_BANTAN_HITTED, m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, NULL, 0) )
						g_xGameProc.m_xMagicList.Insert(pxMagic);
					else
						delete pxMagic;
				}
				else
				{
					CActor* pxActor = FindActor(tdm.nRecog);
					
					if (pxActor)
					{
						CMagic* pxMagic;
						pxMagic = new CMagic;
						if ( pxMagic->CreateMagic(_SKILL_BANTAN_HITTED, pxActor->m_nPosX, pxActor->m_nPosY, pxActor->m_nPosX, pxActor->m_nPosY, NULL, 0) )
							g_xGameProc.m_xMagicList.Insert(pxMagic);
						else
							delete pxMagic;
					}
				}
			}
			break;
			case SM_LEVELUP:
			{
				if ( tdm.wSeries == 0 )
				{
					m_xMyHero.m_stAbility.dlngExp = tdm.nRecog;
					m_xMyHero.m_stAbility.bLevel = (BYTE)tdm.wParam;

					m_xMyHero.SetMotionFrame(_MT_ATTACKMODE, 4);

					CMagic* pxMagic;
					pxMagic = new CMagic;
					if ( pxMagic->CreateMagic(_SKILL_LEVELUP, m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, NULL, m_xMyHero.m_nIdentity) )
						g_xGameProc.m_xMagicList.Insert(pxMagic);
					else
						delete pxMagic;

					m_xInterface.m_xClientSysMsg.AddSysMsg(g_xMsg.GetMsg(1469));
				}
				else if ( tdm.wSeries == 1 )
				{
					CActor* pxActor = FindActor(tdm.nRecog);
					if (pxActor)
					{
						pxActor->SetMotionFrame(_MT_ATTACKMODE, 4);					

						CMagic* pxMagic;
						pxMagic = new CMagic;
						if ( pxMagic->CreateMagic(_SKILL_LEVELUP, pxActor->m_nPosX, pxActor->m_nPosY, pxActor->m_nPosX, pxActor->m_nPosY, NULL, pxActor->m_nIdentity) )
							g_xGameProc.m_xMagicList.Insert(pxMagic);
						else
							delete pxMagic;
					}
				}
			}
			break;
			case SM_POWERUP:
			{
//				tdm.wparam 값으로 씀
				if ( tdm.wParam == _SKILL_MAXDEFENCE )		// 철포삼
				{
					if ( tdm.nRecog == m_xMyHero.m_nIdentity )
					{
						m_xMyHero.SetMotionFrame(_MT_ATTACKMODE, 4, 400);

						CMagic* pxMagic;
						pxMagic = new CMagic;
						if ( pxMagic->CreateMagic(_SKILL_MAXDEFENCE, m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, NULL, m_xMyHero.m_nIdentity) )
							g_xGameProc.m_xMagicList.Insert(pxMagic);
						else
							delete pxMagic;
					}
					else
					{
						CActor* pxActor = FindActor(tdm.nRecog);

						if (pxActor)
						{
							pxActor->SetMotionFrame(_MT_ATTACKMODE, 4, 400);

							CMagic* pxMagic;
							pxMagic = new CMagic;
							if ( pxMagic->CreateMagic(_SKILL_MAXDEFENCE, pxActor->m_nPosX, pxActor->m_nPosY, pxActor->m_nPosX, pxActor->m_nPosY, NULL, pxActor->m_nIdentity) )
								g_xGameProc.m_xMagicList.Insert(pxMagic);
							else
								delete pxMagic;
						}
					}
				}
				else if ( tdm.wParam == _SKILL_MAXDEFENCE_HIGH )
				{
					if ( tdm.nRecog == m_xMyHero.m_nIdentity )
					{
						m_xMyHero.SetMotionFrame(_MT_ATTACKMODE, 4, 400);

						CMagic* pxMagic;
						pxMagic = new CMagic;
						if ( pxMagic->CreateMagic(_SKILL_MAXDEFENCE_HIGH, m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, NULL, m_xMyHero.m_nIdentity) )
							g_xGameProc.m_xMagicList.Insert(pxMagic);
						else
							delete pxMagic;
					}
					else
					{
						CActor* pxActor = FindActor(tdm.nRecog);

						if (pxActor)
						{
							pxActor->SetMotionFrame(_MT_ATTACKMODE, 4, 400);

							CMagic* pxMagic;
							pxMagic = new CMagic;
							if ( pxMagic->CreateMagic(_SKILL_MAXDEFENCE_HIGH, pxActor->m_nPosX, pxActor->m_nPosY, pxActor->m_nPosX, pxActor->m_nPosY, NULL, pxActor->m_nIdentity) )
								g_xGameProc.m_xMagicList.Insert(pxMagic);
							else
								delete pxMagic;
						}
					}
				}
				// 역혈마공, 서버에서 오는 데이터 확인해야 할듯
				// 자기 자신인 경우 철포삼으로 나온다고 했음
				// by eriasoa 2006.05.22
				else if ( tdm.wParam == _SKILL_MAXDEFEECEMAGIC )		
				{
					if ( tdm.nRecog == m_xMyHero.m_nIdentity )
					{
						// 2006.05.22

						// 역혈마공 시전시 케릭터 방향 고정 정면( 4 ) 2006.10.24
						m_xMyHero.SetMotionFrame(_MT_ATTACKMODE, 7, 400);

						CMagic* pxMagic;
						pxMagic = new CMagic;
						if ( pxMagic->CreateMagic(_SKILL_MAXDEFEECEMAGIC, m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, NULL, m_xMyHero.m_nIdentity) )
							g_xGameProc.m_xMagicList.Insert(pxMagic);
						else
							delete pxMagic;
					}
					else
					{
						// OnSpell 에서 처리가 된다 2006.10.25

						/*CActor* pxActor = FindActor(tdm.nRecog);

						if (pxActor)
						{
							// 두번 행동하게 된다
							// by eriastoa 2006.05.22
	
							// 2006.10.25
							// 역혈마공 시전시 OnSpell에서는 예외처리하여 그냥 리턴시키고 여기서 처리하도록 한다
#ifdef _TEST_SERVER_DEBUG
							pxActor->SetMotionFrame(_MT_ATTACKMODE, 4, 400);
#endif

							CMagic* pxMagic;
							pxMagic = new CMagic;
							if ( pxMagic->CreateMagic(_SKILL_MAXDEFEECEMAGIC, pxActor->m_nPosX, pxActor->m_nPosY, pxActor->m_nPosX, pxActor->m_nPosY, NULL, pxActor->m_nIdentity) )
								g_xGameProc.m_xMagicList.Insert(pxMagic);
							else
								delete pxMagic;
						}*/
					}
				}
				else if ( tdm.wParam == _SKILL_MAXDEFEECEMAGIC_HIGH )
				{
					if ( tdm.nRecog == m_xMyHero.m_nIdentity )
					{
						// 2006.05.22
						m_xMyHero.SetMotionFrame(_MT_ATTACKMODE, 7, 400);

						CMagic* pxMagic;
						pxMagic = new CMagic;
						if ( pxMagic->CreateMagic(_SKILL_MAXDEFEECEMAGIC_HIGH, m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, NULL, m_xMyHero.m_nIdentity) )
							g_xGameProc.m_xMagicList.Insert(pxMagic);
						else
							delete pxMagic;
					}
					else
					{
						/*CActor* pxActor = FindActor(tdm.nRecog);

						if (pxActor)
						{
							// 2006.05.22
							
							// 2006.10.25
							// 역혈마공 시전시 OnSpell에서는 예외처리하여 그냥 리턴시키고 여기서 처리하도록 한다
#ifdef _TEST_SERVER_DEBUG
							pxActor->SetMotionFrame(_MT_ATTACKMODE, 4, 400);
#endif

							CMagic* pxMagic;
							pxMagic = new CMagic;
							if ( pxMagic->CreateMagic(_SKILL_MAXDEFEECEMAGIC_HIGH, pxActor->m_nPosX, pxActor->m_nPosY, pxActor->m_nPosX, pxActor->m_nPosY, NULL, pxActor->m_nIdentity) )
								g_xGameProc.m_xMagicList.Insert(pxMagic);
							else
								delete pxMagic;
						}*/
					}
				}
				else if ( tdm.wParam == _SKILL_MAXOFENCE )
				{
					if ( tdm.nRecog == m_xMyHero.m_nIdentity )
					{
						m_xMyHero.SetMotionFrame(_MT_ATTACKMODE, 4, 400);

						CMagic* pxMagic;
						pxMagic = new CMagic;
						if ( pxMagic->CreateMagic(_SKILL_MAXOFENCE, m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, NULL, m_xMyHero.m_nIdentity) )
							g_xGameProc.m_xMagicList.Insert(pxMagic);
						else
							delete pxMagic;
					}
					else
					{
						CActor* pxActor = FindActor(tdm.nRecog);

						if (pxActor)
						{
							pxActor->SetMotionFrame(_MT_ATTACKMODE, 4, 400);

							CMagic* pxMagic;
							pxMagic = new CMagic;
							if ( pxMagic->CreateMagic(_SKILL_MAXOFENCE, pxActor->m_nPosX, pxActor->m_nPosY, pxActor->m_nPosX, pxActor->m_nPosY, NULL, pxActor->m_nIdentity) )
								g_xGameProc.m_xMagicList.Insert(pxMagic);
							else
								delete pxMagic;
						}
					}
				}
				else if ( tdm.wParam == _SKILL_BIGMOUNTAIN )
				{
					if ( tdm.nRecog == m_xMyHero.m_nIdentity )
					{
						m_xMyHero.SetMotionFrame(_MT_ATTACKMODE, 4, 400);

						CMagic* pxMagic;
						pxMagic = new CMagic;
						if ( pxMagic->CreateMagic(_SKILL_BIGMOUNTAIN, m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, NULL, m_xMyHero.m_nIdentity) )
							g_xGameProc.m_xMagicList.Insert(pxMagic);
						else
							delete pxMagic;
					}
					else
					{
						CActor* pxActor = FindActor(tdm.nRecog);

						if (pxActor)
						{
							pxActor->SetMotionFrame(_MT_ATTACKMODE, 4, 400);

							CMagic* pxMagic;
							pxMagic = new CMagic;
							if ( pxMagic->CreateMagic(_SKILL_BIGMOUNTAIN, pxActor->m_nPosX, pxActor->m_nPosY, pxActor->m_nPosX, pxActor->m_nPosY, NULL, pxActor->m_nIdentity) )
								g_xGameProc.m_xMagicList.Insert(pxMagic);
							else
								delete pxMagic;
						}
					}
				}
				else if ( tdm.wParam == _SKILL_MONSTERUP )
				{
					if ( tdm.nRecog == m_xMyHero.m_nIdentity )
					{
						CMagic* pxMagic;
						pxMagic = new CMagic;
						if ( pxMagic->CreateMagic(_SKILL_MONSTERUP, m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, NULL, m_xMyHero.m_nIdentity) )
							g_xGameProc.m_xMagicList.Insert(pxMagic);
						else
							delete pxMagic;
					}
					else
					{
						CActor* pxActor = FindActor(tdm.nRecog);

						if (pxActor)
						{
							CMagic* pxMagic;
							pxMagic = new CMagic;
							if ( pxMagic->CreateMagic(_SKILL_MONSTERUP, pxActor->m_nPosX, pxActor->m_nPosY, pxActor->m_nPosX, pxActor->m_nPosY, NULL, pxActor->m_nIdentity) )
								g_xGameProc.m_xMagicList.Insert(pxMagic);
							else
								delete pxMagic;
						}
					}
				}
				else if ( tdm.wParam == _SKILL_MAXDEFEECEMAGIC )
				{
					if ( tdm.nRecog == m_xMyHero.m_nIdentity )
					{
						m_xMyHero.SetMotionFrame(_MT_ATTACKMODE, 4, 400);

						CMagic* pxMagic;
						pxMagic = new CMagic;
						if ( pxMagic->CreateMagic(_SKILL_MAXDEFEECEMAGIC, m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, NULL, m_xMyHero.m_nIdentity) )
							g_xGameProc.m_xMagicList.Insert(pxMagic);
						else
							delete pxMagic;
					}
					else
					{
						CActor* pxActor = FindActor(tdm.nRecog);

						if (pxActor)
						{
							pxActor->SetMotionFrame(_MT_ATTACKMODE, 4, 400);

							CMagic* pxMagic;
							pxMagic = new CMagic;
							if ( pxMagic->CreateMagic(_SKILL_MAXDEFEECEMAGIC, pxActor->m_nPosX, pxActor->m_nPosY, pxActor->m_nPosX, pxActor->m_nPosY, NULL, pxActor->m_nIdentity) )
								g_xGameProc.m_xMagicList.Insert(pxMagic);
							else
								delete pxMagic;
						}
					}
				}
				else if ( tdm.wParam == _SKILL_BANTAN )
				{
					if ( tdm.nRecog == m_xMyHero.m_nIdentity )
					{
						m_xMyHero.SetMotionFrame(_MT_ATTACKMODE, 4, 400);

						CMagic* pxMagic;
						pxMagic = new CMagic;
						if ( pxMagic->CreateMagic(_SKILL_BANTAN, m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, NULL, m_xMyHero.m_nIdentity) )
							g_xGameProc.m_xMagicList.Insert(pxMagic);
						else
							delete pxMagic;
					}
					else
					{
						CActor* pxActor = FindActor(tdm.nRecog);

						if (pxActor)
						{
							pxActor->SetMotionFrame(_MT_ATTACKMODE, 4, 400);

							CMagic* pxMagic;
							pxMagic = new CMagic;
							if ( pxMagic->CreateMagic(_SKILL_BANTAN, pxActor->m_nPosX, pxActor->m_nPosY, pxActor->m_nPosX, pxActor->m_nPosY, NULL, pxActor->m_nIdentity) )
								g_xGameProc.m_xMagicList.Insert(pxMagic);
							else
								delete pxMagic;
						}
					}
				}
				else 
				{
					if ( tdm.nRecog == m_xMyHero.m_nIdentity )
					{
						m_xMyHero.SetMotionFrame(_MT_ATTACKMODE, 4);

						CMagic* pxMagic;
						pxMagic = new CMagic;
						if ( pxMagic->CreateMagic(_SKILL_POWERUPGRADE, m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, m_xMyHero.m_nPosX, m_xMyHero.m_nPosY, NULL, m_xMyHero.m_nIdentity) )
							g_xGameProc.m_xMagicList.Insert(pxMagic);
						else
							delete pxMagic;
					}
					else
					{
						CActor* pxActor = FindActor(tdm.nRecog);

						if (pxActor)
						{
							pxActor->SetMotionFrame(_MT_ATTACKMODE, 4);

							CMagic* pxMagic;
							pxMagic = new CMagic;
							if ( pxMagic->CreateMagic(_SKILL_POWERUPGRADE, pxActor->m_nPosX, pxActor->m_nPosY, pxActor->m_nPosX, pxActor->m_nPosY, NULL, pxActor->m_nIdentity) )
								g_xGameProc.m_xMagicList.Insert(pxMagic);
							else
								delete pxMagic;
						}
					}
				}
			}
			break;
			case SM_DAYCHANGING:
			{
				m_bDayState = (BYTE)tdm.wParam;

				if ( m_bFogState != tdm.wTag )
				{
					SetTimer(g_xMainWnd.GetSafehWnd(), _TIMER_ID, 50, NULL);
				}

				m_bShowSnow = FALSE;
				m_bShowMist = FALSE;
				m_bShowRain = FALSE;

				if ( tdm.wSeries == 1 )
				{
					m_bShowSnow = TRUE;
					m_bShowMist = TRUE;
					m_xSnow.DestroySystem();
					m_xSnow.InitSystem();
					m_xSnow.SetupSystem();
				}
				else if ( tdm.wSeries == 2 )
				{
					m_bShowMist = TRUE;
				}
				else if ( tdm.wSeries == 3 )
				{
					m_bShowRain = TRUE;
				}

				m_bFogState = (BYTE)tdm.wTag;

				break;
			}
			case SM_AREASTATE:
			{
				m_nAreaState = tdm.nRecog;
				break;
			}
			case SM_HEAR:
			case SM_SYSMESSAGE:
			case SM_GUILDMESSAGE:
			case SM_CRY:
			case SM_WHISPER:
			case SM_GROUPMESSAGE:
			case SM_OBSERVERMSG:
			{
				OnSvrMsgHear(&tdm, (pszMsg + _DEFBLOCKSIZE));
				break;
			}
			case SM_EVENTMESSAGE:
			{
				char szDecodeMsg[8192];

				nPos = fnDecode6BitBuf((pszMsg + _DEFBLOCKSIZE), szDecodeMsg, sizeof(szDecodeMsg));
				szDecodeMsg[nPos] = '\0';

				if ( strlen(szDecodeMsg) == 0 )
					break;

				m_nMsgImgIdx = tdm.wParam - 1;

				if ( m_nMsgImgIdx != -1 )
					SetRect(&m_rcEventMsg, 0, 0, 300, 200);
				else
					SetRect(&m_rcEventMsg, 0, 0, 390, 200);


				AddEventMessage(szDecodeMsg);
			}
			break;
			case SM_DISAPPEAR:
			case SM_HIDE:
			case SM_GHOST:
			case SM_CLEAROBJECT:
			{
				_TDEFAULTMESSAGE*	lpstDefMsg;
				lpstDefMsg	= new _TDEFAULTMESSAGE;

				memcpy(lpstDefMsg, &tdm, sizeof(_TDEFAULTMESSAGE));
				
				m_xWaitDefaultPacketQueue.PushQ((BYTE*)lpstDefMsg);
				break;
			}
			// NPC Wnd 처리 루틴
			case SM_MERCHANTSAY:		// gadget
			{	
				int		nPos;
				char	szDecodeMsg[8192];
				char	*pszSay;

				m_xInterface.m_xNPCWnd.ResetDialog();

				m_nNPCWndPosX = m_xMyHero.m_nPosX;
				m_nNPCWndPosY = m_xMyHero.m_nPosY;

//				if (tdm.nRecog != m_xInterface.m_xNPCWnd.m_nNpcId)
//				{
//				}
				
				nPos = fnDecode6BitBuf((pszMsg + _DEFBLOCKSIZE), szDecodeMsg, sizeof(szDecodeMsg));
				szDecodeMsg[nPos] = '\0';

				if ( pszSay = strchr(szDecodeMsg, '/') )
				{
					*pszSay++ = '\0';

					if (pszSay)
					{
						m_xInterface.m_xNPCWnd.NpcWndCountLineNumInScript(pszSay);
						m_xInterface.m_xNPCWnd.DevideScript(pszSay);
					}
				}

				if ( !m_xInterface.m_xNPCWnd.GetGameWndActive() )
				{
					m_xInterface.WindowActivate(_WND_ID_NPCCHAT);
					m_xInterface.m_xNPCWnd.SetNPC(tdm.nRecog);
				}
				
				break;
			}
			case SM_MERCHANTDLGCLOSE:
			{
				CloseNPCWindow();
				break;
			}
			case SM_NEXTTIME_PASSWORD:
			{
				SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETPASSWORDCHAR, (WPARAM)'*', 0);
				g_xChatEditBox.m_bUsePassMode = TRUE;
				break;
			}
			case SM_DROPITEM_SCCESS: 
			{
/*				CHAR	pszItemName[15];
				nPos = fnDecode6BitBuf((pszMsg + _DEFBLOCKSIZE), (char*)pszItemName, sizeof(pszItemName));
				pszItemName[nPos] = '\0';

				if ( strcmp(pszItemName, m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName) || m_xInterface.m_stCommonItem.xItem.m_stItemInfo.nMakeIndex == tdm.nRecog  )
				{
					if ( !m_xInterface.m_stCommonItem.bIsBeltItem )
						m_xInterface.m_xInventoryWnd.AddInvenItem(m_xInterface.m_stCommonItem.xItem, 0, FALSE);
					else
						m_xInterface.AddBeltItem(m_xInterface.m_stCommonItem.xItem, m_xInterface.m_stCommonItem.xItem.m_shCellNum, TRUE);
				}
*/
				if (m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.bThrow > _MULTIPLE_TYPE_ITEM)
				{
					INT	nBeltNum = 0;
					nBeltNum = m_xInterface.m_xBeltWnd.FindSameItemInBelt(m_xInterface.m_stCommonItem.xItem);
					if (nBeltNum != -1)
						{
						m_xInterface.m_xBeltWnd.DeleteBeltItem(nBeltNum);
					}
				}			// 물약을 바닥에 버릴 때 단축키에 등록이 되어 있으면 단축키에서 삭제시킨다.

				ZeroMemory(&m_xInterface.m_stCommonItem, sizeof(COMMONITEMSET));
				break;
			}
			case SM_DROPITEM_FAIL:
			{
				CHAR	pszItemName[15];
				nPos = fnDecode6BitBuf((pszMsg + _DEFBLOCKSIZE), (char*)pszItemName, sizeof(pszItemName));
				pszItemName[nPos] = '\0';

				if ( strcmp(pszItemName, m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName) || m_xInterface.m_stCommonItem.xItem.m_stItemInfo.nMakeIndex == tdm.nRecog  )
				{
					if ( !m_xInterface.m_stCommonItem.bIsBeltItem && strcmp(m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(1050)) )
						m_xInterface.m_xInventoryWnd.AddInvenItem(m_xInterface.m_stCommonItem.xItem, 0, FALSE);
					else
						m_xInterface.m_xBeltWnd.AddBeltItem(m_xInterface.m_stCommonItem.xItem, m_xInterface.m_stCommonItem.xItem.m_shCellNum, TRUE);
				}
				ZeroMemory(&m_xInterface.m_stCommonItem, sizeof(COMMONITEMSET));
				break;
			}
			case SM_DURACHANGE:
			{
				if ( tdm.wParam < _EQUIP_MAX_CELL )
				{
					if ( m_xInterface.m_xStatusWnd.m_stEquipItem[tdm.wParam].bSetted )
					{
						m_xInterface.m_xStatusWnd.m_stEquipItem[tdm.wParam].xItem.m_stItemInfo.nDura	= tdm.nRecog;
						m_xInterface.m_xStatusWnd.m_stEquipItem[tdm.wParam].xItem.m_stItemInfo.nDuraMax = MAKELONG(tdm.wTag, tdm.wSeries);

						INT nDura = 0;
						if ( m_xInterface.m_xStatusWnd.m_stEquipItem[tdm.wParam].xItem.m_stItemInfo.stStdItem.bStdMode != 54 && 
							 m_xInterface.m_xStatusWnd.m_stEquipItem[tdm.wParam].xItem.m_stItemInfo.stStdItem.bStdMode != 55 &&/*눈덩이*/
							 m_xInterface.m_xStatusWnd.m_stEquipItem[tdm.wParam].xItem.m_stItemInfo.stStdItem.bStdMode != 25)
						{
							nDura = RoundFunc(tdm.nRecog, 1000);
						}
						else // 표창 & 눈덩이(55)
						{
							nDura = RoundFunc(tdm.nRecog, 10);
						}

						if ( m_xInterface.m_xStatusWnd.m_stEquipItem[tdm.wParam].xItem.m_stItemInfo.stStdItem.bStdMode == 25 && 
							 nDura <= 10 )
						{
							CHAR szSysMsg[MAX_PATH];
							sprintf(szSysMsg, g_xMsg.GetMsg(1525), m_xInterface.m_xStatusWnd.m_stEquipItem[tdm.wParam].xItem.m_stItemInfo.stStdItem.szName, nDura);
							m_xInterface.m_xClientSysMsg.AddSysMsg(szSysMsg, RGB(50, 255, 255));
						}
						else if ( nDura <= 0 )
						{
							CHAR szSysMsg[MAX_PATH];
							sprintf(szSysMsg, g_xMsg.GetMsg(1470), m_xInterface.m_xStatusWnd.m_stEquipItem[tdm.wParam].xItem.m_stItemInfo.stStdItem.szName);
							m_xInterface.m_xClientSysMsg.AddSysMsg(szSysMsg, RGB(50, 255, 255));
						}
					}
				}
				break;
			}
			case SM_LAMPCHANGEDURA:
			{
				if ( m_xInterface.m_xStatusWnd.m_stEquipItem[_U_RIGHTHAND].bSetted )
				{
					m_xInterface.m_xStatusWnd.m_stEquipItem[_U_RIGHTHAND].xItem.m_stItemInfo.nDura	= tdm.nRecog;

					INT nDura = 0;
					nDura = RoundFunc(tdm.nRecog, 1000);

					CHAR szSysMsg[MAX_PATH];
					sprintf(szSysMsg, g_xMsg.GetMsg(1527), m_xInterface.m_xStatusWnd.m_stEquipItem[_U_RIGHTHAND].xItem.m_stItemInfo.stStdItem.szName, nDura);
					m_xInterface.m_xClientSysMsg.AddSysMsg(szSysMsg, RGB(50, 255, 255));
				}
				break;
			}
			case SM_GOLDCHANGED:
			{
				g_SoundManager.SndmngrPlayWavSound(_SOUND_MONEY, 0, 0);

				if ( tdm.nRecog - m_xMyHero.m_nGlod > 0 )
				{
					CHAR szGold[MAX_PATH];	
					sprintf(szGold, g_xMsg.GetMsg(1471), tdm.nRecog - m_xMyHero.m_nGlod);
					m_xInterface.m_xClientSysMsg.AddSysMsg(szGold);
				}
				else 
				{
					CHAR szGold[MAX_PATH];	
					sprintf(szGold, g_xMsg.GetMsg(1514), m_xMyHero.m_nGlod - tdm.nRecog);
					m_xInterface.m_xClientSysMsg.AddSysMsg(szGold);
				}
				m_xMyHero.m_nGlod = tdm.nRecog;

/*				CHAR pszLog[100];
				sprintf(pszLog, "nRecog:%d, wIdent:%d, wParam, %d, wSeries:%d, wTag:%d, %s\n", tdm.nRecog, tdm.wIdent, tdm.wParam, tdm.wSeries, tdm.wTag, pszMsg);
				FLOG0("LogGold.txt", pszLog);
*/
				break;
			}
			case SM_WEIGHTCHANGED:
			{
				m_xMyHero.m_stAbility.wWeight	  = (WORD)tdm.nRecog;
				m_xMyHero.m_stAbility.bWearWeight = (BYTE)tdm.wParam;
				m_xMyHero.m_stAbility.bHandWeight = (BYTE)tdm.wTag;											


/*				CHAR pszLog[100];
				sprintf(pszLog, "nRecog:%d, wIdent:%d, wParam, %d, wSeries:%d, wTag:%d, %s\n", tdm.nRecog, tdm.wIdent, tdm.wParam, tdm.wSeries, tdm.wTag, pszMsg);
				FLOG0("LogWeight.txt", pszLog);
*/
				break;
			}
			case SM_RIDEHORSE:
			{
				INT nFeature = MAKELONG(tdm.wParam, tdm.wTag);
				FEATURE stFeature;
				memcpy(&stFeature, &nFeature, sizeof(LONG));

				g_xGameProc.m_xMyHero.m_bEftFeature = stFeature.bDress;
				stFeature.bDress  = stFeature.bDress & 15;

				m_xMyHero.m_stFeatureEx.bHorse = (BYTE)tdm.nRecog;
				m_xMyHero.ChangeFeature(stFeature, m_xMyHero.m_stFeatureEx);

				if ( m_xMyHero.m_stFeatureEx.bHorse != _HORSE_NONE )
					m_xMyHero.SetMotionFrame(_MT_HORSESTAND, m_xMyHero.m_bCurrDir);
				else
					m_xMyHero.SetMotionFrame(_MT_STAND, m_xMyHero.m_bCurrDir);

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
				m_xInterface.m_xClientSysMsg.AddSysMsg(g_xMsg.GetMsg(1472));
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

			// 상대 정보 보기
			case SM_SENDUSERSTATE: 
			{
				USERSTATE	stUserState;

				fnDecode6BitBuf((pszMsg + _DEFBLOCKSIZE), (char*)&stUserState, sizeof(USERSTATE));

				// 안열려 있으면 다시연다.
				if ( !m_xInterface.m_xUserStateWnd.GetGameWndActive() )
				{
					m_xInterface.WindowActivate(_WND_ID_USERSTATE);
				}
				m_xInterface.m_xUserStateWnd.SetUserState(&stUserState);

				break;
			}
			case SM_OPENGUILDDLG: 
			{
				if ( !m_xInterface.m_xGuildWnd.GetGameWndActive() )
				{
					m_xInterface.WindowActivate(_WND_ID_GUILD);
				}

				CHAR	szDecodeMsg[8192];
				nPos = fnDecode6BitBuf((pszMsg + _DEFBLOCKSIZE), szDecodeMsg, sizeof(szDecodeMsg));
				szDecodeMsg[nPos] = '\0';
				m_xInterface.m_xGuildWnd.DevideGuildHome(szDecodeMsg);
				break;
			}
			case SM_OPENGUILDDLG2:
			case SM_OPENGUILDDLG3:
			{
				CHAR	szDecodeMsg[8192];
				nPos = fnDecode6BitBuf((pszMsg + _DEFBLOCKSIZE), szDecodeMsg, sizeof(szDecodeMsg));
				szDecodeMsg[nPos] = '\0';
				m_xInterface.m_xGuildWnd.AddGuildHome(szDecodeMsg);
				break;
			}
			case SM_OPENGUILDDLG_FAIL:
			{
				m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1473));
				break;
			}
			case SM_SENDGUILDMEMBERLIST:
			{
				m_xInterface.m_xGuildWnd.DevideGuildMemberList((pszMsg + _DEFBLOCKSIZE));
				break;
			}
			case SM_SENDGUILDMEMBERLIST2:
			case SM_SENDGUILDMEMBERLIST3:
			{
				m_xInterface.m_xGuildWnd.AddGuildMemberList((pszMsg + _DEFBLOCKSIZE));
				break;
			}
			case SM_GUILDADDMEMBER_OK:
			{
				g_xClientSocket.SendGuildMemberList();
				m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1474));
				break;
			}
			case SM_GUILDADDMEMBER_FAIL:
			{
				switch ( tdm.nRecog )
				{
				case 1:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1475));
					break;
				case 2:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1476));
					break;
				case 3:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1477));
					break;
				case 4:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1478));
					break;
				case 5:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1479));
					break;
				}
				break;
			}
			case SM_GUILDDELMEMBER_OK:
			{
				g_xClientSocket.SendGuildMemberList();
				break;
			}
			case SM_GUILDDELMEMBER_FAIL:
			{
				switch ( tdm.nRecog )
				{
				case 1:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1475));
					break;
				case 2:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1480));
					break;
				case 3:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1481));
					break;
				case 4:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1482));
					break;
				}
				break;
			}
			case SM_GUILDRANKUPDATE_FAIL:
			{
				switch ( tdm.nRecog )
				{
				case -2:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1483));
					break;
				case -3:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1484));
					break;
				case -4:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1485));
					break;
				case -5:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1486));
					break;
				case -6:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1487));
					break;
				case -7:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1488));
					break;
				}

				break;
			}
			case SM_GUILDMAKEALLY_OK:
			case SM_GUILDMAKEALLY_FAIL:
			{
				switch ( tdm.nRecog )
				{
				case -1:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1489));
					break;
				case -2:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1490));
					break;
				case -3:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1491));
					break;
				case -4:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1492));
					break;
				}
				break;
			}
			case SM_GUILDBREAKALLY_OK:
			case SM_GUILDBREAKALLY_FAIL:
			{
				switch ( tdm.nRecog )
				{
				case -1:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1489));
					break;
				case -2:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1493));
					break;
				case -3:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1494));
					break;
				}
			   break;
			}








			case SM_CREATEGROUP_OK:
			{
				m_xInterface.m_xGroupWnd.m_bAllowGroup = TRUE;

				if ( m_xInterface.m_xGroupWnd.m_bAllowGroup )
				{
					m_xInterface.m_xGroupWnd.m_xGroupBtn[_BTN_ID_GROUPICON].ResetGameBtn(177, 177, 177);
					m_xInterface.m_xOptionWnd.m_xOptionBtn[_BTN_ID_ALLOWGROUP].ResetGameBtn(297, 297, -1);
				}
				else
				{
					m_xInterface.m_xGroupWnd.m_xGroupBtn[_BTN_ID_GROUPICON].ResetGameBtn(178, 178);
					m_xInterface.m_xOptionWnd.m_xOptionBtn[_BTN_ID_ALLOWGROUP].ResetGameBtn(301, 301, 299);
				}
				
//	            changegroupmodetime := GetTickCount;
//	            AllowGroup := TRUE;
				break;
			}
			case SM_CREATEGROUP_FAIL:
			{
//            changegroupmodetime := GetTickCount;
				switch ( tdm.nRecog )
				{
				case -1:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GROUP, _OK, g_xMsg.GetMsg(1495));
					break;
				case -2:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GROUP, _OK, g_xMsg.GetMsg(1496));
					break;
				case -3:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GROUP, _OK, g_xMsg.GetMsg(1497));
					break;
				case -4:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GROUP, _OK, g_xMsg.GetMsg(1498));
					break;
				}
				break;
			}
			case SM_GROUPMEMBERS:
			{
				char	szDecodeMsg[8192];
				char	*pszMembers, *pszNext;

				m_xInterface.m_xGroupWnd.m_xGroupList.ClearAll();

				nPos = fnDecode6BitBuf((pszMsg + _DEFBLOCKSIZE), szDecodeMsg, sizeof(szDecodeMsg));
				szDecodeMsg[nPos] = '\0';

				pszMembers = szDecodeMsg;

				while ( pszNext = strchr(pszMembers, '/') )
				{
					*pszNext++ = '\0';

					CGroupMember* pGroupMember = new CGroupMember;

					if (pGroupMember)
					{
						strcpy(pGroupMember->szMemberName, pszMembers);
						m_xInterface.m_xGroupWnd.m_xGroupList.Insert (pGroupMember);
					}

					pszMembers = pszNext;
				}

				break;
			}


			case SM_GROUPADDMEM_OK:
			{
				break;
			}
			case SM_GROUPADDMEM_FAIL:
			{
				switch ( tdm.nRecog )
				{
				case -1:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1499));
					break;
				case -2:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1500));
					break;
				case -3:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1501));
					break;
				case -4:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1498));
					break;
				case -5:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1502));
					break;
				}
				break;
			}
			case SM_GROUPDELMEM_OK:
			{
				break;
			}
			case SM_GROUPDELMEM_FAIL:
			{
				switch ( tdm.nRecog )
				{
				case -1:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1499));
					break;
				case -2:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1500));
					break;
				case -3:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1503));
					break;
				}
				break;
			}


			case SM_GROUPCANCEL:
			{
				m_xInterface.m_xGroupWnd.m_xGroupList.ClearAll();

				break;
			}
			case SM_BUILDGUILD_OK:
			{
				m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1504));
				break;
			}
			case SM_GROUPPOS:
			case SM_GUILDPOS:
			{
				LPGROUPPOS lpGroupPos;
				lpGroupPos = FindGroupPos(tdm.nRecog);

				if ( !lpGroupPos )
				{
					lpGroupPos = new GROUPPOS;
					m_stGroupPosList.Insert(lpGroupPos);
				}

				lpGroupPos->dwLastRecvTick = timeGetTime();
				lpGroupPos->nID			   = tdm.nRecog;
				lpGroupPos->nPosX		   = tdm.wParam;
				lpGroupPos->nPosY		   = tdm.wTag;
				lpGroupPos->bMon		   = tdm.wSeries;

				break;
			}
			case SM_FIRECRACKER:
			{
				char szDecodeMsg[4096];
				nPos = fnDecode6BitBuf((pszMsg + _DEFBLOCKSIZE), szDecodeMsg, sizeof(szDecodeMsg));

				CMagic* pxMagic;
				pxMagic = new CMagic;

				WORD	wRed = (65280 & tdm.nRecog) >> 8;
				WORD	wGreen = 255 & tdm.nRecog;
				WORD	wBlue = atoi(szDecodeMsg);

				RGB(wRed, wGreen, wBlue);

				if ( pxMagic->CreateMagic(_EFFECT_FIRECRACKER_S+tdm.wSeries, tdm.wParam, tdm.wTag, tdm.wParam, tdm.wTag, NULL, 0, 0, 0, wRed, wGreen, wBlue) )
					g_xGameProc.m_xMagicList.Insert (pxMagic);
				else
					delete pxMagic;
				break;
			}
			case SM_MAGICUSETIME:
			{
				INT nKind = (INT)tdm.wParam;
				INT nTime = (INT)tdm.wTag; 
				BOOL bFind = FALSE;

				LPMAGICEFFECTTIME pstMagicEftTime   = NULL;
				CListNode <MAGICEFFECTTIME> *pNode;

				for ( pNode = m_xMagicEftTimeList.GetHead(); pNode; pNode = pNode->GetNext())
				{
					pstMagicEftTime = pNode->GetData();

					if ( pstMagicEftTime )
					{
						if ( nKind == pstMagicEftTime->nKind )
						{
							if( nTime > pstMagicEftTime->nTime )	// 지속시간이 큰것을 비교한다
							{
								pstMagicEftTime->nTime = nTime;
								bFind = TRUE;
							}
						}
						// 항마진법 중복처리
						else if( nKind >= 3 && nKind <= 9 && pstMagicEftTime->nKind >= 3 && pstMagicEftTime->nKind <= 9 )
						{
							if( nTime > pstMagicEftTime->nTime )	// 지속시간이 큰것을 비교한다
							{
								pstMagicEftTime->nKind = nKind;
								pstMagicEftTime->nTime = nTime;
								bFind = TRUE;
							}
						}
						// 강마진법 중복처리
						else if( nKind >= 10 && nKind <= 16 && pstMagicEftTime->nKind >= 10 && pstMagicEftTime->nKind <= 16 )
						{
							if( nTime > pstMagicEftTime->nTime )
							{
								pstMagicEftTime->nKind = nKind;
								pstMagicEftTime->nTime = nTime;
								bFind = TRUE;
							}						
						}
					}
				}

				if ( bFind == FALSE )
				{
					pstMagicEftTime = new MAGICEFFECTTIME;
					pstMagicEftTime->nKind = nKind;
					pstMagicEftTime->nTime = nTime;
					pstMagicEftTime->dwInputTime = g_dwCurrTime;
					m_xMagicEftTimeList.Insert(pstMagicEftTime);
				}
				break;
			}
			case SM_BUILDGUILD_FAIL:
			{
				switch ( tdm.nRecog )
				{
				case -1:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1505));
					break;
				case -2:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1506));
					break;
				case -3:
					m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(1507));
					break;
				}

				break;
			}

/*
캐릭터 상태변경치.
SM_FEATURECHANGED
SM_CHARSTATUSCHANGE
SM_OPENHEALTH
SM_CLOSEHEALTH
SM_CHANGELIGHT
SM_CHANGENAMECOLOR
SM_USERNAME
SM_HEALTHSPELLCHANGED
OnFeatureChanged(lpPacketMsg);		
OnCharStatusChanged(lpPacketMsg);	
OnOpenHealth(lpPacketMsg);			
OnCloseHealth(lpPacketMsg);			
OnChangeLight(lpPacketMsg);			
OnChangeNameClr(lpPacketMsg);		
OnUserName(lpPacketMsg);			
OnHealthSpellChanged(lpPacketMsg);	
*/
			case SM_FEATURECHANGED:		
			{
				PACKETMSG stPacketMsg;
				stPacketMsg.stDefMsg		= tdm;
				stPacketMsg.szEncodeData[0] = NULL;

				lstrcpy(stPacketMsg.szEncodeData, (pszMsg + _DEFBLOCKSIZE));

				if ( tdm.nRecog == m_xMyHero.m_nIdentity )
				{
					m_xMyHero.OnFeatureChanged(&stPacketMsg);
				}
				else
				{
					CActor* pxActor = FindActor(tdm.nRecog);
					if (pxActor)
					{
						switch ( pxActor->m_stFeature.bGender )
						{
							case _GENDER_MAN:
							case _GENDER_WOMAN:
							{
								CHero* pxHero = (CHero*)pxActor;
								pxHero->OnFeatureChanged(&stPacketMsg);
								break;
							}	
							case _GENDER_NPC:
							case _GENDER_FLAG:
							case _GENDER_MON:
							{
								pxActor->OnFeatureChanged(&stPacketMsg);
								break;
							}	
						}
					}
				}

				break;	
			}
			case SM_CHARSTATUSCHANGE:	
			{
				PACKETMSG stPacketMsg;
				stPacketMsg.stDefMsg		= tdm;
				stPacketMsg.szEncodeData[0] = NULL;

				lstrcpy(stPacketMsg.szEncodeData, (pszMsg + _DEFBLOCKSIZE));

				if ( tdm.nRecog == m_xMyHero.m_nIdentity )
				{
					m_xMyHero.OnCharStatusChanged(&stPacketMsg);
				}
				else
				{
					CActor* pxActor = FindActor(tdm.nRecog);
					if (pxActor)
					{
						switch ( pxActor->m_stFeature.bGender )
						{
							case _GENDER_MAN:
							case _GENDER_WOMAN:
							{
								CHero* pxHero = (CHero*)pxActor;
								pxHero->OnCharStatusChanged(&stPacketMsg);
								break;
							}	
							case _GENDER_NPC:
							case _GENDER_FLAG:
							case _GENDER_MON:
							{
								pxActor->OnCharStatusChanged(&stPacketMsg);
								break;
							}	
						}
					}
				}

				break;	
			}
			case SM_OPENHEALTH:			
			{
				PACKETMSG stPacketMsg;
				stPacketMsg.stDefMsg		= tdm;
				stPacketMsg.szEncodeData[0] = NULL;

				lstrcpy(stPacketMsg.szEncodeData, (pszMsg + _DEFBLOCKSIZE));

				if ( tdm.nRecog == m_xMyHero.m_nIdentity )
				{
					m_xMyHero.OnOpenHealth(&stPacketMsg);
				}
				else
				{
					CActor* pxActor = FindActor(tdm.nRecog);
					if (pxActor)
					{
						pxActor->OnOpenHealth(&stPacketMsg);
					}
				}

				break;	
			}
			case SM_CLOSEHEALTH:		
			{
				PACKETMSG stPacketMsg;
				stPacketMsg.stDefMsg		= tdm;
				stPacketMsg.szEncodeData[0] = NULL;

				lstrcpy(stPacketMsg.szEncodeData, (pszMsg + _DEFBLOCKSIZE));

				if ( tdm.nRecog == m_xMyHero.m_nIdentity )
				{
					m_xMyHero.OnCloseHealth(&stPacketMsg);
				}
				else
				{
					CActor* pxActor = FindActor(tdm.nRecog);
					if (pxActor)
					{
						pxActor->OnCloseHealth(&stPacketMsg);
					}
				}

				break;	
			}
			case SM_CHANGELIGHT:		
			{
				PACKETMSG stPacketMsg;
				stPacketMsg.stDefMsg		= tdm;
				stPacketMsg.szEncodeData[0] = NULL;

				lstrcpy(stPacketMsg.szEncodeData, (pszMsg + _DEFBLOCKSIZE));

				if ( tdm.nRecog == m_xMyHero.m_nIdentity )
				{
					m_xMyHero.OnChangeLight(&stPacketMsg);
				}
				else
				{
					CActor* pxActor = FindActor(tdm.nRecog);
					if (pxActor)
					{
						pxActor->OnChangeLight(&stPacketMsg);
					}
				}

				break;	
			}
			case SM_CHANGENAMECOLOR:	
			{	
				PACKETMSG stPacketMsg;
				stPacketMsg.stDefMsg		= tdm;
				stPacketMsg.szEncodeData[0] = NULL;

				lstrcpy(stPacketMsg.szEncodeData, (pszMsg + _DEFBLOCKSIZE));

				if ( tdm.nRecog == m_xMyHero.m_nIdentity )
				{
					m_xMyHero.OnChangeNameClr(&stPacketMsg);
				}
				else
				{
					CActor* pxActor = FindActor(tdm.nRecog);
					if (pxActor)
					{
						pxActor->OnChangeNameClr(&stPacketMsg);
					}
				}
				
				break;	
			}
			case SM_USERNAME:			
			{
				PACKETMSG stPacketMsg;
				stPacketMsg.stDefMsg		= tdm;
				stPacketMsg.szEncodeData[0] = NULL;

				lstrcpy(stPacketMsg.szEncodeData, (pszMsg + _DEFBLOCKSIZE));

				if ( tdm.nRecog == m_xMyHero.m_nIdentity )
				{
					m_xMyHero.OnUserName(&stPacketMsg);
				}
				else
				{
					CActor* pxActor = FindActor(tdm.nRecog);
					if (pxActor)
					{
						pxActor->OnUserName(&stPacketMsg);
					}
				}
				
				break;
			}
			case SM_HEALTHSPELLCHANGED:	
			{
				PACKETMSG stPacketMsg;
				stPacketMsg.stDefMsg		= tdm;
				stPacketMsg.szEncodeData[0] = NULL;

				lstrcpy(stPacketMsg.szEncodeData, (pszMsg + _DEFBLOCKSIZE));

				if ( tdm.nRecog == m_xMyHero.m_nIdentity )
				{
					m_xMyHero.OnHealthSpellChanged(&stPacketMsg);
				}
				else
				{
					CActor* pxActor = FindActor(tdm.nRecog);
					if (pxActor)
					{
						pxActor->OnHealthSpellChanged(&stPacketMsg);
					}
				}
				
				break;	
			}
			case SM_SETXY:
			case SM_WALK:	
			case SM_TURN:	
			case SM_REVIVAL:
			case SM_MYREVIVAL:
			case SM_MAGICHIT:
			case SM_DIGUP:	
			case SM_ALIVE:	
			case SM_DEATH:	
			case SM_RUSH:
			case SM_RUSH2:
			case SM_RUSHKUNG:
			case SM_RUN:
			case SM_BACKSTEP:
			case SM_BACKSTEP2:
			case SM_NOWDEATH:
			case SM_DIGDOWN:
//			case SM_FEATURECHANGED:
//			case SM_OPENHEALTH:	
//			case SM_CLOSEHEALTH:
//			case SM_CHANGELIGHT:
//			case SM_CHANGENAMECOLOR:
//			case SM_HEALTHSPELLCHANGED:
//			case SM_CHARSTATUSCHANGE:
//			case SM_USERNAME:
			case SM_STRUCK:
			case SM_STRUCK2:
			case SM_HIT:
			case SM_FLYAXE:
			case SM_LIGHTING:
			case SM_SKELETON:
			case SM_SITDOWN:
			case SM_BUTCH:
			case SM_HEAVYHIT:
			case SM_FIREHIT:
			case SM_LONGHIT:
			case SM_POWERHIT:
			case SM_WIDEHIT:
			case SM_MANWOL:
			case SM_MAGICFIRE:
			case SM_MAGICFIRE2:
			case SM_SPELL:

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Log In 했을때 받는 정보들.
			case SM_CHANGEMAP:
			case SM_NEWMAP:
			case SM_LOGON:
			case SM_ABILITY:
			case SM_SUBABILITY:
/*
SM_NEWMAP
SM_LOGON
SM_USERNAME
SM_AREASTATE
SM_MAPDESCRIPTION
SM_CHANGELIGHT
SM_CHARSTATUSCHANGE
SM_HEAR
SM_HEAR
SM_HEAR
SM_ABILITY
SM_SUBABILITY
SM_DAYCHANGING
SM_SENDUSEITEMS
SM_SENDMYMAGIC
*/
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			case SM_THROWHIT:
			case SM_THROWDOT:
			case SM_RANDSWINGHIT:
			case SM_HIGH_RANDSWINGHIT:
			case SM_BACKSWINGHIT:
			case SM_BACKKICKHIT:
			case SM_BACKKICKUP:
			case SM_PULL_SHOW:
			case SM_SPACEMOVE_HIDE:
			case SM_SPACEMOVE_SHOW:
			case SM_SPACEMOVE_HIDE2:
			case SM_SPACEMOVE_SHOW2:
			{
				LPPACKETMSG	lpPacketMsg	= new PACKETMSG;

				lpPacketMsg->stDefMsg			= tdm;
				lpPacketMsg->szEncodeData[0]	= NULL;

				lstrcpy(lpPacketMsg->szEncodeData, (pszMsg + _DEFBLOCKSIZE));

 				m_xWaitPacketQueue.PushQ((BYTE*)lpPacketMsg);
//				FLOG2("LogMon.txt", "Server Msg : ", tdm.wIdent, g_dwCurrTime);
				break;
			}
/*			default:
			{
				CHAR pszLog[100];
				sprintf(pszLog, "nRecog:%d, wIdent:%d, wParam, %d, wSeries:%d, wTag:%d\n", tdm.nRecog, tdm.wIdent, tdm.wParam, tdm.wSeries, tdm.wTag);
				FLOG0("Log000.txt", pszLog);
				break;
			}*/
		}
	}
}


VOID CGameProcess::ProcessDefaultPacket()
{
	_TDEFAULTMESSAGE*		lpstDefMsg;
	CActor*					pxActor = NULL;
	CListNode < CActor >	*pNode;

	for (DWORD dwCnt = 0; dwCnt < m_xWaitDefaultPacketQueue.GetCount(); dwCnt++)
	{
		lpstDefMsg = (_TDEFAULTMESSAGE*)m_xWaitDefaultPacketQueue.PopQ();

		if ( lpstDefMsg )
		{
			if ( lpstDefMsg->wIdent == SM_DISAPPEAR || lpstDefMsg->wIdent == SM_HIDE || lpstDefMsg->wIdent == SM_GHOST )
			{
				for (pNode = m_xActorList.GetHead(); pNode; pNode = pNode->GetNext())
				{
					pxActor = pNode->GetData();
					
					if ( pxActor && pxActor->m_nIdentity == lpstDefMsg->nRecog )
					{
						CheckMagicUseActor(pxActor);
						
						if ( pxActor == m_pxMouseTargetActor )
						{
							m_pxMouseTargetActor = NULL;
						}
						if ( pxActor == m_pxExplainActor )
						{
							m_pxExplainActor = NULL;
						}
						if ( pxActor == m_pxMouseOldTargetActor )
						{
							m_pxMouseOldTargetActor = NULL;
						}
						if ( pxActor == m_pxSavedTargetActor )
						{
							m_pxSavedTargetActor = NULL;
						}

						INT nPacketCnt = pxActor->m_xPacketQueue.GetCount();

						for ( INT nLoopCnt = 0; nLoopCnt < nPacketCnt; nLoopCnt++ )
						{
							LPPACKETMSG	lpObjPacketMsg = (LPPACKETMSG)pxActor->m_xPacketQueue.PopQ();
							SAFE_DELETE(lpObjPacketMsg);
						}

//						WriteLog(pxActor->m_nPosX, pxActor->m_nPosY, pxActor->m_bCurrDir, pxActor->m_stFeature.bGender, pxActor->m_stFeature.bDress, lpstDefMsg, 2);

						switch ( pxActor->m_stFeature.bGender )
						{
						case _GENDER_MAN:
						case _GENDER_WOMAN:
							{
								m_xActorList.RemoveNode(pNode);

								CHero* pxHero = (CHero*)pxActor;
								delete((CHero*)pxHero);
								pxHero = NULL;
							}
							break;
						case _GENDER_NPC:
						case _GENDER_FLAG:
							{
								m_xActorList.RemoveNode(pNode);

								CNPC* pxNPC = (CNPC*)pxActor;
								delete((CNPC*)pxNPC);
								pxNPC = NULL;
							}
							break;
						case _GENDER_MON:
							{
								if ( pxActor->m_bAppearState != _DIG_DOWN )
								{
									m_xActorList.RemoveNode(pNode);
									delete(pxActor);
									pxActor = NULL;
								}
							}
							break;
						}
						break;		//for문을 빠져나간다.
					}			
				}
				SAFE_DELETE(lpstDefMsg);
			}
			else if ( lpstDefMsg->wIdent == SM_CLEAROBJECT )
			{
				SAFE_DELETE(lpstDefMsg);

/*				INT nPacketCnt = m_xWaitDefaultPacketQueue.GetCount();

				for ( INT nLoopCnt = 0; nLoopCnt < nPacketCnt; nLoopCnt++ )
				{
					_TDEFAULTMESSAGE* lpstDefMsg = (_TDEFAULTMESSAGE*)m_xWaitDefaultPacketQueue.PopQ();
					SAFE_DELETE(lpstDefMsg);
				}*/

				// 리스트들 초기화.
				// 마법이나 이벤트등 타겟이 Actor인경우 반드시 먼저 클리어 해준다.
//				GroundMagicListClear();
//				MagicListClear();
//				m_stEventImgList.ClearAll();
//				m_stMapItemList.ClearAll();

				ActorListClear();
				m_stGroupPosList.ClearAll();

				m_pxMouseTargetActor	 = NULL;
				m_pxExplainActor		 = NULL;
				m_pxMouseOldTargetActor	 = NULL;
				m_pxSavedTargetActor	 = NULL;

				return;
			}
		}
	}						
}



BOOL CGameProcess::GenerateAcotor(LPPACKETMSG lpPacketMsg)
{
	BOOL bRet = FALSE;

	if ( lpPacketMsg->stDefMsg.wIdent == SM_TURN	 || lpPacketMsg->stDefMsg.wIdent == SM_RUN   || lpPacketMsg->stDefMsg.wIdent == SM_WALK			  || 
		 lpPacketMsg->stDefMsg.wIdent == SM_BACKSTEP || lpPacketMsg->stDefMsg.wIdent == SM_DEATH || lpPacketMsg->stDefMsg.wIdent == SM_SKELETON		  ||
		 lpPacketMsg->stDefMsg.wIdent == SM_DIGUP	 || lpPacketMsg->stDefMsg.wIdent == SM_ALIVE || lpPacketMsg->stDefMsg.wIdent == SM_SPACEMOVE_SHOW ||
		 lpPacketMsg->stDefMsg.wIdent == SM_SPACEMOVE_SHOW2 || lpPacketMsg->stDefMsg.wIdent == SM_PULL_SHOW || lpPacketMsg->stDefMsg.wIdent == SM_BACKSTEP2 )
	{
		CActor*		pxActor;

		WORD		wPosX;
		WORD		wPosY;
		BYTE		bDir;
		DWORD		dwID;
		FEATURE		stFeature;
		FEATUREEX	stFeatureEx;
		CHARDESC	stCharDesc;
		
		dwID	= lpPacketMsg->stDefMsg.nRecog;
		wPosX	= lpPacketMsg->stDefMsg.wParam;
		wPosY	= lpPacketMsg->stDefMsg.wTag;
		bDir	= LOBYTE(lpPacketMsg->stDefMsg.wSeries);

		fnDecode6BitBuf(lpPacketMsg->szEncodeData, (char*)&stCharDesc, sizeof(CHARDESC));
		memcpy(&stFeature, &stCharDesc.nFeature, sizeof(FEATURE));

/*		CHAR pszLog[1000];
		sprintf(pszLog, 
				"nRecog:%d, wIdent:%d, wParam, %d, wSeries:%d, wTag:%d, bGender:%d, bDress:%d, bHair:%d, bWeapon:%d, %s", 
			    lpPacketMsg->stDefMsg.nRecog, lpPacketMsg->stDefMsg.wIdent, lpPacketMsg->stDefMsg.wParam, lpPacketMsg->stDefMsg.wSeries, lpPacketMsg->stDefMsg.wTag, 
				stFeature.bGender, stFeature.bDress, stFeature.bHair, stFeature.bWeapon, lpPacketMsg->szEncodeData);
		FLOG0("LogActor.txt", pszLog);
*/

		BYTE bTemp = stFeature.bDress;

		if ( stFeature.bGender == _GENDER_MAN || stFeature.bGender == _GENDER_WOMAN ) 
		{
			pxActor				 = new CHero;
			CHero* pxHero		 = (CHero*)pxActor;
			pxHero->m_nIdentity = dwID;

			fnDecode6BitBuf(&lpPacketMsg->szEncodeData[_CHARDESCSIZE], (char*)&stFeatureEx, sizeof(FEATUREEX));

			if ( pxHero->Create(&m_xImage, _MT_STAND, _DIRECTION_LIST_1, wPosX, wPosY, &stFeature, &stFeatureEx) )
			{
				m_xActorList.Insert(pxHero);
				pxHero->m_xPacketQueue.PushQ((BYTE*)lpPacketMsg);

				bRet = TRUE;

				pxHero->m_nABlendDelay	 = 300;
				pxHero->m_nABlendCurrDelay = 0;
				pxHero->m_bEftFeature = bTemp;
				pxHero->m_stFeature.bDress = bTemp & 31;

/*				pxHero->m_nGenPacket = lpPacketMsg->stDefMsg.wIdent;

				pxActor->m_nRecvPacketCnt++;
				LPPACKETMSG lpRecvPacketMsg;
				lpRecvPacketMsg = new PACKETMSG;
				memcpy(lpRecvPacketMsg, lpPacketMsg, sizeof(PACKETMSG));
				pxActor->m_xRecvPacketList.Insert(lpRecvPacketMsg);*/
			}
			else
			{
				delete((CHero*)pxHero);
				pxHero = NULL;
			}
		}
		else if ( stFeature.bGender == _GENDER_NPC || stFeature.bGender == _GENDER_FLAG )
		{
			pxActor				= new CNPC;
			CNPC* pxNPC			= (CNPC*)pxActor;
			pxNPC->m_nIdentity = dwID;
			
			if ( pxNPC->Create(&m_xImage, &stFeature, _MT_STAND, _DIRECTION_LIST_1, wPosX, wPosY) )
			{
				m_xActorList.Insert(pxNPC);
				pxNPC->m_xPacketQueue.PushQ((BYTE*)lpPacketMsg);


				bRet = TRUE;

				pxNPC->m_nABlendDelay	 = 300;
				pxNPC->m_nABlendCurrDelay = 0;

/*				pxNPC->m_nGenPacket = lpPacketMsg->stDefMsg.wIdent;

				pxActor->m_nRecvPacketCnt++;
				LPPACKETMSG lpRecvPacketMsg;
				lpRecvPacketMsg = new PACKETMSG;
				memcpy(lpRecvPacketMsg, lpPacketMsg, sizeof(PACKETMSG));
				pxActor->m_xRecvPacketList.Insert(lpRecvPacketMsg);*/
			}
			else
			{
				delete((CNPC*)pxNPC);
				pxNPC = NULL;
			}
		}
		else
		{
			pxActor				  = new CActor;
			pxActor->m_nIdentity = dwID;
			stFeature.bGender	 = _GENDER_MON;

			if ( pxActor->Create(&m_xImage, &stFeature, _MT_STAND, _DIRECTION_LIST_1, wPosX, wPosY) )
			{
				m_xActorList.Insert (pxActor);
				pxActor->m_xPacketQueue.PushQ((BYTE*)lpPacketMsg);

				bRet = TRUE;

				pxActor->m_nABlendDelay	 = 300;
				pxActor->m_nABlendCurrDelay = 0;

/*				pxActor->m_nGenPacket = lpPacketMsg->stDefMsg.wIdent;

				pxActor->m_nRecvPacketCnt++;
				LPPACKETMSG lpRecvPacketMsg;
				lpRecvPacketMsg = new PACKETMSG;
				memcpy(lpRecvPacketMsg, lpPacketMsg, sizeof(PACKETMSG));
				pxActor->m_xRecvPacketList.Insert(lpRecvPacketMsg);*/
			}
			else
			{
				delete((CActor*)pxActor);
				pxActor = NULL;
			}
		}
	}

	return bRet;
}


VOID CGameProcess::ProcessPacket()
{
	LPPACKETMSG	lpPacketMsg;
	BOOL		bExist;
	CActor*		pxActor = NULL;
	CListNode <CActor> *pNode;

	for (DWORD dwCnt = 0; dwCnt < m_xWaitPacketQueue.GetCount(); dwCnt++)
	{
		lpPacketMsg = (LPPACKETMSG)m_xWaitPacketQueue.PopQ();

		if ( lpPacketMsg )
		{
			if ( lpPacketMsg->stDefMsg.wIdent == SM_NEWMAP || lpPacketMsg->stDefMsg.wIdent == SM_CHANGEMAP )
			{
				OnSvrMsgResetMap(lpPacketMsg);
			}
			else if ( lpPacketMsg->stDefMsg.wIdent == SM_LOGON )
			{
				OnSvrMsgLogon(lpPacketMsg);
			}
			else if ( lpPacketMsg->stDefMsg.wIdent == SM_ABILITY )
			{
				OnSvrMsgAbility(lpPacketMsg);
			}
			else if ( lpPacketMsg->stDefMsg.wIdent == SM_SUBABILITY )
			{
				OnSvrMsgSubAbility(lpPacketMsg);
			}
			else if ( lpPacketMsg->stDefMsg.wIdent == SM_MYREVIVAL )
			{
				m_xMyHero.m_xPacketQueue.PushQ((BYTE*)lpPacketMsg);
			}
			else if ( lpPacketMsg->stDefMsg.nRecog == m_xMyHero.m_nIdentity )
			{
				if ( lpPacketMsg->stDefMsg.wIdent == SM_STRUCK )
				{
					if ( timeGetTime() - m_xMyHero.m_dwLastStruckTime < 500 )
					{
						// 죽은경우이다.
						m_xMyHero.m_wHP	   = m_xMyHero.m_stAbility.wHP	  = lpPacketMsg->stDefMsg.wParam;
						m_xMyHero.m_wMAXHP = m_xMyHero.m_stAbility.wMaxHP = lpPacketMsg->stDefMsg.wTag;

						if ( m_xMyHero.m_wHP != 0 )
						{
							SAFE_DELETE(lpPacketMsg);
							continue;
						}
					}
								
					m_xMyHero.StruckMsgReassign();
					m_xMyHero.m_xPacketQueue.PushQ((BYTE*)lpPacketMsg);
				}
				else
				{
					m_xMyHero.m_xPacketQueue.PushQ((BYTE*)lpPacketMsg);
				}
			}
			else
			{
				bExist	= FALSE;
				pxActor	= NULL;

				for (pNode = m_xActorList.GetHead(); pNode; pNode = pNode->GetNext())
				{
					pxActor = pNode->GetData();

					if ( pxActor )
					{					
						if ( pxActor->m_nIdentity == lpPacketMsg->stDefMsg.nRecog )
						{
							pxActor->StruckMsgReassign();
							pxActor->m_xPacketQueue.PushQ((BYTE*)lpPacketMsg);
							bExist = TRUE;

/*							pxActor->m_nRecvPacketCnt++;
							LPPACKETMSG lpRecvPacketMsg;
							lpRecvPacketMsg = new PACKETMSG;
							memcpy(lpRecvPacketMsg, lpPacketMsg, sizeof(PACKETMSG));
							pxActor->m_xRecvPacketList.Insert(lpRecvPacketMsg);

							if ( pxActor == m_pxAutoSavedTargetActor )
							{
								CHAR		 szBuff[1000];

								static DWORD dwLastTick = timeGetTime();
								DWORD		 dwCurrTick = timeGetTime();

								sprintf(szBuff, "[%d] %s(%d), wIdent:%d, Tick:%d, Gap:%d", pxActor->m_xRecvPacketList.GetCount(), pxActor->m_szName, pxActor->m_nIdentity, lpRecvPacketMsg->stDefMsg.wIdent, dwCurrTick, dwCurrTick-dwLastTick);

								dwLastTick = timeGetTime();

								DWORD dwFont = GetChatColor(_CHAT_COLOR4);
								DWORD dwBack = GetChatColor(_CHAT_COLOR3);
								m_xInterface.MsgAdd(dwFont, dwBack, szBuff);
								FLOG0("Log.txt", szBuff);
							}
*/
/*							if ( pxActor == m_pxAutoSavedTargetActor )
							{
								CHAR		 szBuff[1000];

								static DWORD dwLastTick = timeGetTime();
								DWORD		 dwCurrTick = timeGetTime();

								sprintf(szBuff, "갯수:%d 이름:%s 아이디:%d, wIdent:%d", pxActor->m_xPacketQueue.GetCount(), pxActor->m_szName,
									   pxActor->m_nIdentity, lpPacketMsg->stDefMsg.wIdent);

								dwLastTick = timeGetTime();

								DWORD dwFont = GetChatColor(_CHAT_COLOR4);
								DWORD dwBack = GetChatColor(_CHAT_COLOR3);
								m_xInterface.MsgAdd(dwFont, dwBack, szBuff);
							}*/

							break;
						}
					}
					else
					{
						int ntest = 0;
					}
				}

				if ( bExist == FALSE )
				{
					if ( !GenerateAcotor(lpPacketMsg) )
					{
						SAFE_DELETE(lpPacketMsg);
					}
				}
			}
		}
	}
}



// **************************************************************************************
//
//		 Packet Handling
//
// **************************************************************************************
// 처음접속시나 이동할때.
VOID CGameProcess::OnSvrMsgResetMap(LPPACKETMSG	lpPacketMsg)
{
	INT			nPos;
	DWORD		dwFogColor = RGB(10, 10, 10);
	CHAR		szDecodeMsg[_MAX_STRING_LEN];

	//FLOG0("LogMap.txt", "/*맵이동시작***********************************************************************/");

	m_bRender = FALSE;
	// 만약 아공등일때 끝날때까지 기다린다.
/*	if ( ( m_xMyHero.m_bCurrMtn == _MT_SPELL2 && (m_xMyHero.m_dwCurrEffectFrame-m_xMyHero.m_dwFstEffectFrame) < (DWORD)(m_xMyHero.m_bEffectFrameCnt - 1) ) || m_dwInputDelayTime != 0  )
	{
		INT nCnt;
		INT nLeftMsgCnt = m_xWaitPacketQueue.GetCount();
		LPPACKETMSG* lppPacketSave = new LPPACKETMSG[nLeftMsgCnt];
		if ( lppPacketSave )
		{
			for ( INT nCnt = 0; nCnt < nLeftMsgCnt; nCnt++ )
			{
				LPPACKETMSG lpMsg = (LPPACKETMSG)m_xWaitPacketQueue.PopQ();

				if ( lpMsg )
				{
					lppPacketSave[nCnt] = lpMsg;
				}
			}
		}

		m_xWaitPacketQueue.PushQ((BYTE*)lpPacketMsg);

		for ( nCnt = nLeftMsgCnt-1; nCnt >= 0; nCnt-- )
		{
			m_xWaitPacketQueue.PushQ((BYTE*)lppPacketSave[nCnt]);
		}

		SAFE_DELETEARR(lppPacketSave);

		m_bRender = TRUE;

		return;	
	}
*/
	
	//FLOG0("LogMap.txt", "1. 아공동작끝");

	m_xInterface.SaveItemPos(m_xMyHero.m_szName);

	m_xInterface.m_xMagicShortcutWnd.SaveMagicKeySet();
	m_xInterface.m_xUtilWnd.SaveUtilSet();
	
	//FLOG0("LogMap.txt", "2. 아이템파일저장");

	// 사운드 소리멈추기.
	g_SoundManager.SndmngrStopAllWaveSound();
	g_SoundManager.SndmngrStopMp3();

	//FLOG0("LogMap.txt", "3. 사운드 OFF");

	// Delay.
	m_dwInputDelayTime		= 1500;
	m_dwCurrInputDelayTime	= 0;


	//  Speed Hack관련.	
	m_dwFindHackTime		= 0;
	m_dwClientActTick		= 0;
	m_dwServerActTick		= 0;
	m_fHackTickRate			= 1.0f;
	m_fTickSum				= 0.0f;
	m_nTickCnt				= 0;


	// 내캐릭터.
	m_xMyHero.m_dwFstEffectFrame	= 0;
	m_xMyHero.m_dwEndEffectFrame	= 0;
	m_xMyHero.m_dwCurrEffectFrame	= 0;
	m_xMyHero.m_bEffectFrame		= 0;
	m_xMyHero.m_bEffectFrameCnt		= _DEFAULT_SPELLFRAME;
	m_xMyHero.m_bUseEffect			= FALSE;
	m_xMyHero.m_bIsMoved			= FALSE;
	m_xMyHero.m_bInputLock			= FALSE;
	m_xMyHero.m_bMotionLock			= FALSE;
	m_xMyHero.m_bMoveSpeed			= 0; 
	m_xMyHero.m_nShiftPixelX		= 0;
	m_xMyHero.m_nShiftPixelY		= 0;
	m_xMyHero.m_nShiftTileX			= 0;
	m_xMyHero.m_nShiftTileY			= 0;
	m_xMyHero.m_nPosX				= m_xMyHero.m_nOldPosX = lpPacketMsg->stDefMsg.wParam;
	m_xMyHero.m_nPosY				= m_xMyHero.m_nOldPosY = lpPacketMsg->stDefMsg.wTag;
	m_xMyHero.m_bOldDir				= m_xMyHero.m_bCurrDir;
	m_xMyHero.SetMapHandler(&m_xMap);
	m_xMyHero.SetMotionFrame(_MT_STAND, m_xMyHero.m_bCurrDir);

	//FLOG2("LogMap.txt", "4. 움직임 제어 Delay 세팅과 내캐릭터 데이타 초기화", lpPacketMsg->stDefMsg.wParam, lpPacketMsg->stDefMsg.wTag);

	// 맵.
	nPos = fnDecode6BitBuf(lpPacketMsg->szEncodeData, szDecodeMsg, sizeof(szDecodeMsg));
	if ( nPos >= _MAX_STRING_LEN ) 
	{
		nPos = _MAX_STRING_LEN;
	}
	szDecodeMsg[nPos] = '\0';
	m_xMap.SetStartViewTile(m_xMyHero.m_nPosX - _GAPX_TILE_CHAR_MAP, m_xMyHero.m_nPosY - _GAPY_TILE_CHAR_MAP);
	m_xMap.LoadMapData(szDecodeMsg);
	ZeroMemory(m_stMemMappedID, sizeof(MEMMAPPEDID)*_VIEW_CELL_X_COUNT* _VIEW_CELL_Y_COUNT);

	//FLOG0("LogMap.txt", "5. 맵데이타 로딩완료");
	//FLOG0("LogMap.txt", szDecodeMsg);

	// 하루상태.
	// 서서히 포그상태를 바꾸는 타이머를 죽인다.
	if ( m_bFogState == lpPacketMsg->stDefMsg.wSeries )
	{
		KillTimer(g_xMainWnd.GetSafehWnd(), _TIMER_ID);
	}
	m_bFogState = LOBYTE(lpPacketMsg->stDefMsg.wSeries);
	switch ( m_bFogState )
	{
	case _FOGSTATE_DAY:
		{
			dwFogColor = RGB(255, 255, 255);
			break;
		}
	case _FOGSTATE_NIGHT:
		{
			dwFogColor = RGB(15, 15, 15);
			break;
		}
	case _FOGSTATE_DAWN:
		{
			dwFogColor = RGB(85, 85, 85);
			break;
		}
	}
	m_xLightFog.ChangeLightColor(dwFogColor);

	if ( m_xInterface.m_xStatusWnd.m_stEquipItem[_U_RIGHTHAND].bSetted &&  strcmp( m_xInterface.m_xStatusWnd.m_stEquipItem[_U_RIGHTHAND].xItem.m_stItemInfo.stStdItem.szName, "견혼령" ) == 0 )
	{
		DWORD	dwFogColor;
		FLOAT	fDstDarkRate = 0.0f;

		fDstDarkRate = 255.0f;
		dwFogColor = RGB(fDstDarkRate, fDstDarkRate, fDstDarkRate);
		m_xLightFog.ChangeLightColor(dwFogColor);
	}

	m_bShowSnow = FALSE;
	m_bShowMist = FALSE;
	m_bShowRain = FALSE;

	if ( HIBYTE(lpPacketMsg->stDefMsg.wSeries) == 1 )
	{
		m_bShowSnow = TRUE;
		m_bShowMist = TRUE;
		m_xSnow.DestroySystem();
		m_xSnow.InitSystem();
		m_xSnow.SetupSystem();
	}

	if ( HIBYTE(lpPacketMsg->stDefMsg.wSeries) == 2 )
	{
		m_bShowMist = TRUE;
	}

	if ( HIBYTE(lpPacketMsg->stDefMsg.wSeries) == 3 )
	{
		m_bShowRain = TRUE;
	}
	//FLOG0("LogMap.txt", "6. 포그상태 죽이기");

	// 인터페이스닫기.
	CloseNPCWindow();

	//FLOG0("LogMap.txt", "7. 스크립트창 닫기");

	// 미니맵.
	if ( m_xInterface.m_bViewMiniMap )
	{
		m_xInterface.m_bReadyViewMap = TRUE;
		g_xClientSocket.SendWantMMap();
	}
/*
	if ( m_xInterface.m_nInformationMode == _INFO_MINIMAP )
	{
		m_xInterface.m_bReadyInforMap = TRUE;
		g_xClientSocket.SendWantMMap();
	}
*/
	//FLOG0("LogMap.txt", "8. 미니맵 재요청 완료");

	// 리스트들 초기화.
	GroundMagicListClear();
	MagicListClear();
	m_stEventImgList.ClearAll();
	m_stMapItemList.ClearAll();

	//FLOG0("LogMap.txt", "9. 각 리스트들 초기화");

	// 상태저장 캐릭터들 초기화.
	m_pxMouseTargetActor	= NULL;
	m_pxExplainActor		= NULL;
	m_pxMouseOldTargetActor = NULL;
	m_pxSavedTargetActor	= NULL;

	m_xInterface.m_xNPCWnd.m_nNpcId = -1;

	//FLOG0("LogMap.txt", "10. 각 타겟 저장 포인터들 초기화");

	// 현패킷지우기.
	SAFE_DELETE(lpPacketMsg);

	m_bRender = TRUE;
	if ( m_bShowLoading )
	{
		m_bFateState = 1;
		m_dwFadeTime = 0;
	}

	m_bShowLoading = FALSE;

	m_bPlayBGM = TRUE;
	m_dwMapMoveTime = 0;

	m_xInterface.SetViewMode();

	m_bCheckBigLight = TRUE;
	m_dwChkTimerBigLight = g_dwCurrTime;
	//FLOG0("LogMap.txt", "11. 패킷분석완료.");

	//FLOG0("LogMap.txt", "/*맵이동끝***********************************************************************/");
	//FLOG0("LogMap.txt", " ");

/*	// 남아있는패킷지우기.
	INT					nLeftMsgCnt;
	LPPACKETMSG			lpLeftPacketMsg;
	_TDEFAULTMESSAGE*	lpstDefMsg;

	lpLeftPacketMsg = NULL;
	nLeftMsgCnt		= m_xWaitPacketQueue.GetCount();

	// 쌓여있는 패킷을 지운다.
	if ( nLeftMsgCnt > 0 )
	{
		for ( nCnt = 0; nCnt < nLeftMsgCnt; nCnt++ )
		{
			lpLeftPacketMsg = (LPPACKETMSG)m_xWaitPacketQueue.PopQ();
			SAFE_DELETE(lpLeftPacketMsg);
		}
	}

	lpstDefMsg	= NULL;
	nLeftMsgCnt = m_xWaitDefaultPacketQueue.GetCount();

	// 쌓여있는 패킷을 지운다.
	if ( nLeftMsgCnt > 0 )
	{
		for ( nCnt = 0; nCnt < nLeftMsgCnt; nCnt++ )
		{
			lpstDefMsg = (_TDEFAULTMESSAGE*)m_xWaitDefaultPacketQueue.PopQ();
			SAFE_DELETE(lpstDefMsg);
		}
	}*/
}

VOID CGameProcess::OnSvrMsgLogon(LPPACKETMSG lpPacketMsg)
{
	MESSAGEBODYWL	wl;
	FEATUREEX		fx;
	CHARDESC		stCharDesc;
	BYTE			bDir;

	m_xMyHero.m_nIdentity	= lpPacketMsg->stDefMsg.nRecog;
	m_xMyHero.m_bLightSize	= HIBYTE(lpPacketMsg->stDefMsg.wSeries);
	bDir					= LOBYTE(lpPacketMsg->stDefMsg.wSeries);

	// 추가코드
	fnDecode6BitBuf(lpPacketMsg->szEncodeData, (char*)&wl, sizeof(wl));
	m_xMyHero.m_nFame = wl.nTag2;
	fnDecode6BitBuf(lpPacketMsg->szEncodeData + _MESSAGEBODYWLSIZE, (char*)&fx, sizeof(fx));
	fnDecode6BitBuf(lpPacketMsg->szEncodeData + _MESSAGEBODYWLSIZE + _FEATURESIZEEX, (char*)&stCharDesc, sizeof(stCharDesc));

	if ( stCharDesc.nFaceImageDate != m_xMyHero.m_nFaceImageDate )
		m_xInterface.m_bIsThereUserFile = TRUE;

	m_xMyHero.m_nCharState		= stCharDesc.nStatus;
	m_xMyHero.m_nFaceImageDate	= stCharDesc.nFaceImageDate;
	m_xMyHero.m_bGuildFlag		= stCharDesc.bGuildFlag;
	m_xMyHero.m_bFlagRed		= stCharDesc.bFlagRed;
	m_xMyHero.m_bFlagGreen		= stCharDesc.bFlagGreen;
	m_xMyHero.m_bFlagBlue		= stCharDesc.bFlagBlue;
//	m_xMyHero.m_wEffectLooks	= stCharDesc.wLooks;

	if ( fx.bHorse == _HORSE_NONE )
	{
		m_xMyHero.Create(&m_xImage, _MT_STAND, bDir, lpPacketMsg->stDefMsg.wParam/*x*/, lpPacketMsg->stDefMsg.wTag/*y*/, (FEATURE *)&wl.lParam1, &fx);
	}
	else
	{
		m_xMyHero.Create(&m_xImage, _MT_HORSESTAND, bDir, lpPacketMsg->stDefMsg.wParam/*x*/, lpPacketMsg->stDefMsg.wTag/*y*/, (FEATURE *)&wl.lParam1, &fx);
	}

	strcpy(g_xGameProc.m_xMyHero.m_szName, g_szCharName);
	m_xInterface.m_xUtilWnd.LoadUtilSet();
	m_xInterface.m_xMagicShortcutWnd.LoadMagicKeySet();
	m_xInterface.m_xBeltWnd.LoadBeltPosition();

//	if ( LOBYTE(LOWORD(wl.nTag1)) )
	if ( wl.nTag1 )
	{
		m_xInterface.m_xGroupWnd.m_bAllowGroup = TRUE;
	}
	else
	{
		m_xInterface.m_xGroupWnd.m_bAllowGroup = FALSE;
	}

	// 현패킷지우기.
	SAFE_DELETE(lpPacketMsg);

	m_stGroupPosList.ClearAll();
	m_xGameMsgBox.InitMsgBox();
	m_bUseHotKey = FALSE;
	m_bRender	 = TRUE;
	g_xClientSocket.SendQueryMsg(CM_QUERYBAGITEMS);

	DWORD dwBack = GetChatColor((BYTE)_CHAT_COLOR4);
	DWORD dwFont = GetChatColor((BYTE)_CHAT_COLOR3);

	// 마우스 아이템을 없앤다.
	ZeroMemory(&m_xInterface.m_stCommonItem, sizeof(COMMONITEMSET));

#ifndef _TEST_SERVER
	if ( !m_bShowPaySys )
	{
		switch(g_nPaySystem)
		{
		case _KIND_IP_FIXED_TIME:
			{
				m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(1508));
			}
			break;
		case _KIND_IP_FIXED_MONEY:
			{
				m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(1509));
			}
			break;
		case _KIND_PRIVATE_FIXED_TIME:
			{
				m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(1510));
			}
			break;
		case _KIND_PRIVATE_FIXED_MONEY:
			{
				m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(1511));
			}
			break;
		}
	}

	m_bShowPaySys = TRUE;
#endif
}


VOID CGameProcess::OnSvrMsgHear(_TDEFAULTMESSAGE *ptdm, char *pszMsg)
{
	char szDecodeMsg[_MAX_STRING_LEN];

	if ( strlen(pszMsg) > _MAX_STRING_LEN )
		return;

	int nPos = fnDecode6BitBuf(pszMsg, szDecodeMsg, sizeof(szDecodeMsg));

	if ( nPos >= _MAX_STRING_LEN ) 
	{
		nPos = _MAX_STRING_LEN - 1;
	}
	szDecodeMsg[nPos] = '\0';

#ifdef _DEBUG
	if ( m_bChatSave )
	{
		if ( ptdm->wIdent != SM_SYSMESSAGE )
		{
			FLOG0("Chat.txt", szDecodeMsg)
		}
	}
#endif


	if ( ptdm->wIdent == SM_GUILDMESSAGE )
	{
		DWORD dwBack = GetChatColor((BYTE)_CHAT_COLOR1);
		DWORD dwFont = GetChatColor((BYTE)_CHAT_COLOR5);
		m_xInterface.MsgAdd(dwFont, dwBack, szDecodeMsg);

		m_xInterface.m_xGuildWnd.MsgAdd(szDecodeMsg);
	}
	else
	{
		DWORD dwBack = GetChatColor((BYTE)ptdm->wTag);
		DWORD dwFont = GetChatColor((BYTE)ptdm->wParam);

		m_xInterface.MsgAdd(dwFont, dwBack, szDecodeMsg);
	}

	if ( ptdm->wIdent == SM_HEAR || ptdm->wIdent == SM_MONSTERSAY )
	{
		if ( m_xMyHero.m_nIdentity && ptdm->nRecog == m_xMyHero.m_nIdentity )
		{
			strcpy(m_xMyHero.m_szChatMsg, szDecodeMsg);

			m_xMyHero.ChatMsgAdd();
			m_xMyHero.m_wCurrChatDelay = 0;
		}
		else
		{
			CActor*				pxActor = NULL;
			CListNode <CActor> 	*pNode;

			if ( m_xActorList.GetCount() )
			{
				for ( pNode = m_xActorList.GetHead(); pNode; pNode = pNode->GetNext() )
				{ 
					pxActor = pNode->GetData();

					if ( pxActor )
					{
						if ( pxActor->m_nIdentity && pxActor->m_nIdentity == ptdm->nRecog )
						{
							strcpy(pxActor->m_szChatMsg, szDecodeMsg);

							pxActor->ChatMsgAdd();
							pxActor->m_wCurrChatDelay = 0;
							break;
						}
					}
				}
			}
		}
	}
}


VOID CGameProcess::OnSvrMsgAbility(LPPACKETMSG lpPacketMsg)
{
	m_xMyHero.m_nGlod	= lpPacketMsg->stDefMsg.nRecog;
	m_xMyHero.m_bJob	= (BYTE)lpPacketMsg->stDefMsg.wParam;

	fnDecode6BitBuf(lpPacketMsg->szEncodeData, (char*)&m_xMyHero.m_stAbility, sizeof(ACTORABILITY));

	m_xMyHero.m_wHP	   = m_xMyHero.m_stAbility.wHP;
	m_xMyHero.m_wMAXHP = m_xMyHero.m_stAbility.wMaxHP;
	m_xMyHero.m_wMP	   = m_xMyHero.m_stAbility.wMP;

	m_xMyHero.m_bGuildFlag = LOBYTE(lpPacketMsg->stDefMsg.wTag);
	m_xMyHero.m_bFlagColorR = HIBYTE(lpPacketMsg->stDefMsg.wTag)*16;
	m_xMyHero.m_bFlagColorG = LOBYTE(lpPacketMsg->stDefMsg.wSeries)*16;
	m_xMyHero.m_bFlagColorB = HIBYTE(lpPacketMsg->stDefMsg.wSeries)*16;

	SAFE_DELETE(lpPacketMsg);
}



VOID CGameProcess::OnSvrMsgSubAbility(LPPACKETMSG lpPacketMsg)
{
	m_xMyHero.m_stSubAbility.wAntiMagic		= LOBYTE(LOWORD(lpPacketMsg->stDefMsg.nRecog));	
	m_xMyHero.m_stSubAbility.bHitPoint		= LOBYTE(lpPacketMsg->stDefMsg.wParam);	
	m_xMyHero.m_stSubAbility.bSpeedPoint	= HIBYTE(lpPacketMsg->stDefMsg.wParam);	
	m_xMyHero.m_stSubAbility.bFameIdx		= lpPacketMsg->stDefMsg.wTag;
//	m_xMyHero.m_stSubAbility.bAntiPoison	= LOBYTE(lpPacketMsg->stDefMsg.wTag);
//	m_xMyHero.m_stSubAbility.bPoisonRecover = HIBYTE(lpPacketMsg->stDefMsg.wTag);
	m_xMyHero.m_stSubAbility.bHealthRecover = LOBYTE(lpPacketMsg->stDefMsg.wSeries);
	m_xMyHero.m_stSubAbility.bSpellRecover	= HIBYTE(lpPacketMsg->stDefMsg.wSeries);




	SAFE_DELETE(lpPacketMsg);
}

INT CGameProcess::DecriptInt(char* szStr)
{
    int   i, k;
    BYTE  bVal, bMagic, bMagicBase;
    int   nMadeInt = 0;
	
	if (strlen(szStr) >= 40 ) 
	{
		for (i=0; i<=3; i++) 
		{
			bMagicBase = (BYTE)*(szStr + i*10);
			bMagic = (BYTE)*(szStr + i*10 + 9);

			for (k=0; k<=7; k++) 
			{
				bVal = (BYTE)*(szStr + i*10 + 1 + k);
				if (bVal >= bMagicBase + bMagic) 
				{
					nMadeInt = nMadeInt | (0x80000000 >> (i*8 + k));
				}
			}
		}
	}

    return  MAKELONG( MAKEWORD( HIBYTE(HIWORD(nMadeInt) ^ 0xD5 ^ 0x52),
                                LOBYTE(HIWORD(nMadeInt) ^ 0xD5 ^ 0x52)),
                      MAKEWORD( HIBYTE(LOWORD(nMadeInt) ^ 0xD5 ^ 0x52),
                                LOBYTE(LOWORD(nMadeInt) ^ 0xD5 ^ 0x52) ) );
}

WORD CGameProcess::DecriptWord(char* szStr)
{
    int  i, k;
    BYTE bVal, bMagic, bMagicBase;
    WORD wMadeWord = 0;

	if (strlen(szStr) < 20) return 0;

    for (i=0; i<=1; i++) 
	{
        bMagicBase = (BYTE)*(szStr + i*10);
        bMagic = (BYTE)*(szStr + i*10 + 9);

        for (k=0; k<=7; k++) 
		{
            bVal = (BYTE)*(szStr + i*10 + 1 + k);
            if (bVal >= bMagicBase + bMagic) 
			{
                wMadeWord = wMadeWord | (0x8000 >> (i*8 + k));
            }
        }
    }

    return  MAKEWORD( HIBYTE(wMadeWord) ^ 0xD5 ^ 0x52, LOBYTE(wMadeWord) ^ 0xD5 ^ 0x52 );
}

VOID CGameProcess::RenderEventMessage()
{
	RECT rc = {0, -15, 400, 98};
	BOOL bMonImg = FALSE, bHasImg = FALSE;

	D3DVECTOR	 vecTrans((FLOAT)(rc.left), (FLOAT)(rc.top), 0);
	D3DVECTOR	 vecScale((FLOAT)(rc.right), (FLOAT)(rc.bottom), 1);
	D3DMATERIAL7 mtrl;

	D3DUtil_InitMaterial(mtrl, (FLOAT)70/255.0f, (FLOAT)70/255.0f, (FLOAT)70/255.0f);
	mtrl.diffuse.a = 100.0f/255.0f;
	g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

	if ( m_nMsgImgIdx >= 10000 )
	{
		INT nIdx = m_nMsgImgIdx - 10000;

		if (m_xInterface.m_xNPCWnd.m_xNPCImage.NewSetIndex(nIdx))
		{
			g_xMainWnd.DrawWithImageForComp(m_rcEventMsg.left+2, m_rcEventMsg.top-13, 
											m_xInterface.m_xNPCWnd.m_xNPCImage.m_lpstNewCurrWilImageInfo->shWidth, 
											m_xInterface.m_xNPCWnd.m_xNPCImage.m_lpstNewCurrWilImageInfo->shHeight, 
											(WORD *)m_xInterface.m_xNPCWnd.m_xNPCImage.m_pbCurrImage);
			bHasImg = TRUE;
			bMonImg = FALSE;
		}
	}
	else
	{
		if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_MONSMALL].NewSetIndex(m_nMsgImgIdx))
		{
			g_xMainWnd.DrawWithImageForComp(m_rcEventMsg.left+2, m_rcEventMsg.top-2, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_MONSMALL].m_lpstNewCurrWilImageInfo->shWidth, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_MONSMALL].m_lpstNewCurrWilImageInfo->shHeight-10,
											(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_MONSMALL].m_pbCurrImage);
			bHasImg = TRUE;
			bMonImg = TRUE;
		}
	}

	if ( !m_xEventMsglist.IsEmpty() )
	{
		INT		nCnt, nShowLine;
		LPCHAT	pstChat;

		CListNode < CHAT >		*pNode;

		pNode = m_xEventMsglist.GetHead();

		nShowLine = m_xEventMsglist.GetCount();

		for ( nCnt = 0; nCnt < nShowLine; nCnt++ )
		{
			pstChat = *pNode;

			if ( pstChat )
			{
				DWORD dwFontColor = RGB(0, 0, 0);
				INT nX = 0;

				if ( bMonImg && bHasImg )
					nX = 85;
				else if ( bHasImg )
					nX = 85;

				g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(),
								   m_rcEventMsg.left+nX+7, m_rcEventMsg.top+nCnt*17+5,
								   dwFontColor, pstChat->dwBackColor, pstChat->pszChat);
				g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(),
								   m_rcEventMsg.left+nX+9, m_rcEventMsg.top+nCnt*17+5,
								   dwFontColor, pstChat->dwBackColor, pstChat->pszChat);
				g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(),
								   m_rcEventMsg.left+nX+8, m_rcEventMsg.top+nCnt*17+4,
								   dwFontColor, pstChat->dwBackColor, pstChat->pszChat);
				g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(),
								   m_rcEventMsg.left+nX+8, m_rcEventMsg.top+nCnt*17+6,
								   dwFontColor, pstChat->dwBackColor, pstChat->pszChat);
				g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(),
								   m_rcEventMsg.left+nX+8, m_rcEventMsg.top+nCnt*17+5,
								   pstChat->dwFontColor, pstChat->dwBackColor, pstChat->pszChat);
			}

			pNode = pNode->GetNext();
		}
	}

	if ( timeGetTime() - m_dwEventMsgTimer > m_dwEventMsgMaxTime )
	{
		m_dwEventMsgMaxTime = 0;
		m_dwEventMsgTimer = 0;
		m_bDrawEventMsg = FALSE;
	}
}

VOID CGameProcess::AddEventMessage(CHAR* pszMsg)
{
	DWORD dwFontColor = RGB(250, 250, 250), dwFontBackColor = RGB(0, 0, 0);

	if ( pszMsg )
	{
//		INT nLength = strlen(pszMsg);
//		m_dwEventMsgMaxTime = nLength * 10 * 15;
//		if ( m_dwEventMsgMaxTime < 10000 )
		m_dwEventMsgMaxTime = 10000;
		m_dwEventMsgTimer = timeGetTime();
		m_xEventMsglist.ClearAll();				// 초기화
		m_bDrawEventMsg = TRUE;

		if ( pszMsg[0] != NULL )
		{
			INT  nCnt;
			CHAT* stChat;
			INT	 nLineCnt;
			CHAR pszDivied[_MAX_STRING_LEN*2];
			CHAR pszArg[7][MAX_PATH];

			ZeroMemory(pszDivied, _MAX_STRING_LEN*2);
			ZeroMemory(pszArg,	  MAX_PATH*7);

			g_xMainWnd.StringDivide(m_rcEventMsg.right-m_rcEventMsg.left, nLineCnt, pszMsg, pszDivied);

			sscanf(pszDivied, "%[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c", pszArg[0], pszArg[1], pszArg[2], pszArg[3], pszArg[4], pszArg[5], pszArg[6]);

			if ( nLineCnt > 7 )
			{
				nLineCnt = 7;
			}

			// 문자열 삽입.
			for ( nCnt = 0; nCnt < nLineCnt; nCnt++ )
			{
				stChat = new CHAT;
				stChat->dwFontColor = dwFontColor;
				stChat->dwBackColor = dwFontBackColor;
				strcpy(stChat->pszChat, pszArg[nCnt]);
				
				m_xEventMsglist.Insert(stChat);
			}
		}
	}
}


VOID CGameProcess::ShowGraphicNum(POINT ptLoc, INT nNum)
{
	if ( m_bShowBloodNum == FALSE )
		return; 

	if ( nNum == 0 )
	{
		if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(1850))
		{
			g_xMainWnd.DrawWithImageForComp(ptLoc.x-10, ptLoc.y , 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
		}
		return;
	}

	BOOL bIsPlus;
	INT nImg;

	if ( nNum > 0 )
		bIsPlus = TRUE;
	else
		bIsPlus = FALSE;

	nNum = abs(nNum);

	INT nCount = nNum / 10;

	if ( nCount == 0 )
		nCount = 1;
	else if ( nCount >= 1 && nCount <= 9 )
		nCount = 2;
	else if ( nCount >= 10 && nCount <= 99 )
		nCount = 3;
	else if ( nCount >= 100 && nCount <= 999 )
		nCount = 4;
	else if ( nCount >= 1000 && nCount <= 9999 )
		nCount = 5;

	if ( bIsPlus )
	{
		nImg = 1821;
		if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(nImg))
		{
			g_xMainWnd.DrawWithImageForComp(ptLoc.x-10, ptLoc.y , 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
		}
	}
	else if ( nNum >= 500 )
	{
		nImg = 1760;
		if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(nImg))
		{
			g_xMainWnd.DrawWithImageForComp(ptLoc.x-14, ptLoc.y + 6, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
		}
	}
	else if ( nNum >= 100 )
	{
		nImg = 1840;
		if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(nImg))
		{
			g_xMainWnd.DrawWithImageForComp(ptLoc.x-8, ptLoc.y + 4, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
		}
	}
	else
	{
		nImg = 1800;
		if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(nImg))
		{
			g_xMainWnd.DrawWithImageForComp(ptLoc.x-8, ptLoc.y + 4, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
		}
	}

	BOOL bLarge = FALSE;
	BOOL bBig = FALSE;

	for ( INT nI=0; nI<nCount; nI++ )
	{
		INT nValue = nNum / pow(10, (double)(nCount-1-nI));

		if ( bIsPlus )
		{
			nImg = 1810 + nValue;
		}
		else if ( nNum >= 500 || bBig )
		{
			nImg = 1750 + nValue;
			bBig = TRUE;
		}
		else if ( nNum >= 100 || bLarge == TRUE )
		{
			nImg = 1830 + nValue;
			bLarge = TRUE;
		}
		else
		{
			nImg = 1790 + nValue;
		}

		if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(nImg))
		{
			g_xMainWnd.DrawWithImageForComp(ptLoc.x + nI*11, ptLoc.y, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
		}
		nNum -= nValue * pow(10, (double)(nCount-1-nI));
	}
}

VOID CGameProcess::AutoPickUp()
{
	// 말을 타고 있을 때는 아이템을 주울 수 없다 2006.10.26
	if( g_xGameProc.m_xMyHero.m_stFeatureEx.bHorse != _HORSE_NONE )
		return;

	LPGROUNDITEM	pstItem;

	// 2006.07.24
	// 아이템 줍기 - 8방향 + 자기위치
#ifdef _TEST_SERVER
	for( INT nTotal = 0; nTotal < 9; ++nTotal )
	{
		INT nPosX = m_xMyHero.m_nPosX - m_xMap.m_nStartViewTileX;
		INT nPosY = m_xMyHero.m_nPosY - m_xMap.m_nStartViewTileY;

		if ( nTotal == 0 )
		{
			nPosX = nPosX;
			nPosY = nPosY;
		}
		else if ( nTotal == 1 )
		{
			nPosX = nPosX - 1;
			nPosY = nPosY - 1;
		}
		else if ( nTotal == 2 )
		{
			nPosX = nPosX;
			nPosY = nPosY - 1;
		}
		else if ( nTotal == 3 )
		{
			nPosX = nPosX + 1;
			nPosY = nPosY - 1;
		}
		else if ( nTotal == 4 )
		{
			nPosX = nPosX - 1;
			nPosY = nPosY;
		}
		else if ( nTotal == 5 )
		{
			nPosX = nPosX + 1;
			nPosY = nPosY;
		}
		else if ( nTotal == 6 )
		{
			nPosX = nPosX - 1;
			nPosY = nPosY + 1;
		}
		else if ( nTotal == 7 )
		{
			nPosX = nPosX;
			nPosY = nPosY + 1;
		}
		else if ( nTotal == 8 )
		{
			nPosX = nPosX + 1;
			nPosY = nPosY + 1;
		}

		for ( INT nObjCnt = 0; nObjCnt < _MAX_CELL_OBJ && nPosY > 0 && nPosX > 0 && timeGetTime() - m_dwPickUpTime > 500 ; nObjCnt++ )
		{
			pstItem = m_stMemMappedID[nPosY][nPosX].pstItem[nObjCnt];
			if ( pstItem )
			{
				//if ( pstItem->nTileX == m_xMyHero.m_nPosX && pstItem->nTileY == m_xMyHero.m_nPosY )
				//{
					INT nItemCnt;
					INT	nTotalItem  = 0;
					for ( nItemCnt = 0; nItemCnt < _MAX_INVEN_ITEM; nItemCnt++ )
					{
						if ( g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nItemCnt].bSetted )
						{
							nTotalItem++;
						}
					}
					
					if ( !strncmp(pstItem->szItemName, g_xMsg.GetMsg(1050), 4 ) || (nTotalItem < _MAX_INVEN_ITEM) || pstItem->nThrow >= 2 )
					{
						if ( (nTotalItem >= _MAX_INVEN_ITEM) && pstItem->nThrow >= 2 )
						{						
							if ( m_xInterface.m_xInventoryWnd.FindInvenItem(pstItem->wLooks) )
							{
								g_xClientSocket.SendPickUp(pstItem->nTileX, pstItem->nTileY);
								m_dwPickUpTime = timeGetTime();
							}
							else
							{
								m_xInterface.m_xClientSysMsg.AddSysMsg(g_xMsg.GetMsg(1417));
							}
						}
						else
						{
							g_xClientSocket.SendPickUp(pstItem->nTileX, pstItem->nTileY);
							m_dwPickUpTime = timeGetTime();
						}
					}
					else
					{
						m_xInterface.m_xClientSysMsg.AddSysMsg(g_xMsg.GetMsg(1417));
					}
				//}
			}
		}	// end for( INT nObjCnt~ )
	}		// end for( INT nTotal~ )
#endif
}

BOOL CGameProcess::NeedAutoTarget(DWORD wKey)
{
	BYTE				bMagicKey = 0;
	LPCLIENTMAGICRCD	pstMagic;

	switch ( wKey )
	{
		case VK_F1:		{	bMagicKey = '1';	break;	}
		case VK_F2:		{	bMagicKey = '2';	break;	}
		case VK_F3:		{	bMagicKey = '3';	break;	}
		case VK_F4:		{	bMagicKey = '4';	break;	}
		case VK_F5:		{	bMagicKey = '5';	break;	}
		case VK_F6:		{	bMagicKey = '6';	break;	}
		case VK_F7:		{	bMagicKey = '7';	break;	}
		case VK_F8:		{	bMagicKey = '8';	break;	}
		case VK_F9:		{	bMagicKey = '9';	break;	}
		case VK_F10:	{	bMagicKey = 'A';	break;	}
		case VK_F11:	{	bMagicKey = 'B';	break;	}
		case VK_F12:	{	bMagicKey = 'C';	break;	}
	}

	if ( bMagicKey != 0 )
	{
		INT nAtoI = atoi((char*)&bMagicKey);
		BYTE bKeyNum = 0;

		if ( nAtoI < 10 && nAtoI > 0 )
		{
			bKeyNum = (BYTE)nAtoI;
		}
		else
		{
			bKeyNum = (BYTE)(bMagicKey - 55);
		}

		INT nMagicID = g_xGameProc.m_xInterface.m_xMagicShortcutWnd.GetMagicIDByKey(bKeyNum);
		pstMagic = g_xGameProc.m_xInterface.m_xMagicWnd.GetMagicByMagicKey(nMagicID);

//		pstMagic = g_xGameProc.m_xInterface.m_xMagicWnd.GetMagicByKey(bMagicKey);

		if ( pstMagic )
		{
			switch(pstMagic->stStdMagic.wMagicID)
			{
				case _SKILL_FIREBALL:
				case _SKILL_FIREBALL2:
				case _SKILL_ICEBOLT:
				case _SKILL_SUPERICEBOLT:
				case _SKILL_MAGICARROW:
				case _SKILL_LIGHTENING:
				case _SKILL_HANDWIND:
				case _SKILL_HURRICANEBOMB:
				case _SKILL_MOONOK:
				case _SKILL_MOONCHAM:
				case _SKILL_MOONCHAM_HIGH:
				case _SKILL_AMYOUNSUL:
				case _SKILL_BIGAM:
				case _SKILL_AMYOUNSUL_HIGH:
				case _SKILL_FIRECHARM:
				case _SKILL_TAMMING:
				case _SKILL_TAMMING_HIGH:
				case _SKILL_KILLUNDEAD:
				case _SKILL_MYULSAL:
				case _SKILL_BALSACHE:
				case _SKILL_LIGHTFLOWER:
				case _SKILL_FIREBOOM:
				case _SKILL_HURRICANE:
				case _SKILL_SNOWWIND:
					return TRUE;
			}
		}
	}

	return FALSE;
}

VOID CGameProcess::CheckMarketWindow(CActor* pxNpc)
{
	if ( pxNpc->m_nIdentity == m_xInterface.m_xMarketWnd.mUserMarket_nNpcId )
	{
		if ( ( abs(pxNpc->m_nPosX-m_xMyHero.m_nPosX) > 10 || abs(pxNpc->m_nPosY-m_xMyHero.m_nPosY) > 10) )
		{
			m_xInterface.m_xMarketWnd.CloseMarketWnd();
		}
	}

	if ( pxNpc->m_nIdentity == m_xInterface.m_xMarketUpWnd.mUserMarketUp_nNpcId )
	{
		if ( ( abs(pxNpc->m_nPosX-m_xMyHero.m_nPosX) > 10 || abs(pxNpc->m_nPosY-m_xMyHero.m_nPosY) > 10) )
		{
			m_xInterface.m_xMarketUpWnd.CloseMarketUpWnd();
		}
	}
}

VOID CGameProcess::EncriptInt(byte * Value, char * pBuf)
{
	int  nI, nK;
	BYTE bVal, bMagicbase, bMagic, bOut; 


    for ( nI=0; nI<4; nI++) 
	{
		bVal = *Value;
    	bVal = (byte)(bVal ^ 0x52 ^ 0xD5);
		
    	bMagicbase = 10 + GetRandomNum(0, 49);
    	bMagic = 10 + GetRandomNum(0, 19);
    	
    	pBuf[nI*10] = bMagicbase;
    	pBuf[nI*10 + 9] = bMagic; 
    	
    	for ( nK=0; nK<8; nK++) 
		{
    	  if ( (bVal & (0x80 >> nK)) == 0 )
		  {
			  bOut = bMagicbase + GetRandomNum(0, bMagic-1);
		  }
		  else 
		  {
			  bOut = (bMagicbase + bMagic) + GetRandomNum(0, bMagic-1);
		  }
		  pBuf[nI*10 + 1 + nK] = bOut;
    	}
		Value++;
    }
}

BYTE * CGameProcess::JpegFileToRGB(CHAR *fileName,
							   UINT *width,
							   UINT *height)

{
	*width=0;
	*height=0;

	/* This struct contains the JPEG decompression parameters and pointers to
	* working space (which is allocated as needed by the JPEG library).
	*/
	struct jpeg_decompress_struct cinfo;
	/* We use our private extension JPEG error handler.
	* Note that this struct must live as long as the main JPEG parameter
	* struct, to avoid dangling-pointer problems.
	*/

	struct my_error_mgr jerr;
	/* More stuff */
	FILE * infile=NULL;		/* source file */

	JSAMPARRAY buffer;		/* Output row buffer */
	int row_stride;		/* physical row width in output buffer */
	char buf[250];

	/* In this example we want to open the input file before doing anything else,
	* so that the setjmp() error recovery below can assume the file is open.
	* VERY IMPORTANT: use "b" option to fopen() if you are on a machine that
	* requires it in order to read binary files.
	*/

	if ((infile = fopen(fileName, "rb")) == NULL) 
	{
		return NULL;
	}

	/* Step 1: allocate and initialize JPEG decompression object */

	/* We set up the normal JPEG error routines, then override error_exit. */
	cinfo.err = jpeg_std_error(&jerr.pub);
	jerr.pub.error_exit = my_error_exit;

	/* Establish the setjmp return context for my_error_exit to use. */
	if (setjmp(jerr.setjmp_buffer)) 
	{
		/* If we get here, the JPEG code has signaled an error.
		 * We need to clean up the JPEG object, close the input file, and return.
		 */

		jpeg_destroy_decompress(&cinfo);

		if (infile!=NULL)
			fclose(infile);
		return NULL;
	}

	/* Now we can initialize the JPEG decompression object. */
	jpeg_create_decompress(&cinfo);

	/* Step 2: specify data source (eg, a file) */

	jpeg_stdio_src(&cinfo, infile);

	/* Step 3: read file parameters with jpeg_read_header() */

	(void) jpeg_read_header(&cinfo, TRUE);
	/* We can ignore the return value from jpeg_read_header since
	*   (a) suspension is not possible with the stdio data source, and
	*   (b) we passed TRUE to reject a tables-only JPEG file as an error.
	* See libjpeg.doc for more info.
	*/

	/* Step 4: set parameters for decompression */

	/* In this example, we don't need to change any of the defaults set by
	* jpeg_read_header(), so we do nothing here.
	*/

	/* Step 5: Start decompressor */

	(void) jpeg_start_decompress(&cinfo);
	/* We can ignore the return value since suspension is not possible
	* with the stdio data source.
	*/

	/* We may need to do some setup of our own at this point before reading
	* the data.  After jpeg_start_decompress() we have the correct scaled
	* output image dimensions available, as well as the output colormap
	* if we asked for color quantization.
	* In this example, we need to make an output work buffer of the right size.
	*/ 

	// get our buffer set to hold data
	BYTE *dataBuf;

	////////////////////////////////////////////////////////////
	// alloc and open our new buffer
	dataBuf=(BYTE *)new BYTE[cinfo.output_width * 3 * cinfo.output_height];
	if (dataBuf==NULL) 
	{
//		MessageBox(g_xMainWnd.GetSafehWnd(), TEXT("JpegFile :\nOut of memory") , TEXT("MirJPEG"), MB_ICONERROR | MB_OK);

		jpeg_destroy_decompress(&cinfo);
		
		fclose(infile);

		return NULL;
	}

	// how big is this thing gonna be?
	*width = cinfo.output_width;
	*height = cinfo.output_height;
	
	/* JSAMPLEs per row in output buffer */
	row_stride = cinfo.output_width * cinfo.output_components;

	/* Make a one-row-high sample array that will go away when done with image */
	buffer = (*cinfo.mem->alloc_sarray)
		((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

	/* Step 6: while (scan lines remain to be read) */
	/*           jpeg_read_scanlines(...); */

	/* Here we use the library's state variable cinfo.output_scanline as the
	* loop counter, so that we don't have to keep track ourselves.
	*/
	while (cinfo.output_scanline < cinfo.output_height) {
		/* jpeg_read_scanlines expects an array of pointers to scanlines.
		 * Here the array is only one element long, but you could ask for
		 * more than one scanline at a time if that's more convenient.
		 */
		(void) jpeg_read_scanlines(&cinfo, buffer, 1);
		/* Assume put_scanline_someplace wants a pointer and sample count. */

		// asuumer all 3-components are RGBs
		if (cinfo.out_color_components==3) {
			
			j_putRGBScanline(buffer[0], 
								*width,
								dataBuf,
								cinfo.output_scanline-1);

		} else if (cinfo.out_color_components==1) {

			// assume all single component images are grayscale
			j_putGrayScanlineToRGB(buffer[0], 
								*width,
								dataBuf,
								cinfo.output_scanline-1);

		}

	}

	/* Step 7: Finish decompression */

	(void) jpeg_finish_decompress(&cinfo);
	/* We can ignore the return value since suspension is not possible
	* with the stdio data source.
	*/

	/* Step 8: Release JPEG decompression object */

	/* This is an important step since it will release a good deal of memory. */
	jpeg_destroy_decompress(&cinfo);

	/* After finish_decompress, we can close the input file.
	* Here we postpone it until after no more JPEG errors are possible,
	* so as to simplify the setjmp error logic above.  (Actually, I don't
	* think that jpeg_destroy can do an error exit, but why assume anything...)
	*/
	fclose(infile);

	/* At this point you may want to check to see whether any corrupt-data
	* warnings occurred (test whether jerr.pub.num_warnings is nonzero).
	*/
	return dataBuf;
}


void CGameProcess::j_putRGBScanline(BYTE *jpegline, 
					 int widthPix,
					 BYTE *outBuf,
					 int row)
{
	int offset = row * widthPix * 3;
	int count;
	for (count=0;count<widthPix;count++) {
		BYTE iRed, iBlu, iGrn;
		LPBYTE oRed, oBlu, oGrn;

		iRed = *(jpegline + count * 3 + 0);
		iGrn = *(jpegline + count * 3 + 1);
		iBlu = *(jpegline + count * 3 + 2);

		oRed = outBuf + offset + count * 3 + 0;
		oGrn = outBuf + offset + count * 3 + 1;
		oBlu = outBuf + offset + count * 3 + 2;

		*oRed = iRed;
		*oGrn = iGrn;
		*oBlu = iBlu;
	}
}


void CGameProcess::j_putGrayScanlineToRGB(BYTE *jpegline, int widthPix, BYTE *outBuf, int row)
{
	int offset = row * widthPix * 3;
	int count;
	for (count=0;count<widthPix;count++) {

		BYTE iGray;
		LPBYTE oRed, oBlu, oGrn;

		// get our grayscale value
		iGray = *(jpegline + count);

		oRed = outBuf + offset + count * 3;
		oGrn = outBuf + offset + count * 3 + 1;
		oBlu = outBuf + offset + count * 3 + 2;

		*oRed = iGray;
		*oGrn = iGray;
		*oBlu = iGray;
	}
}

BOOL CGameProcess::BGRFromRGB(BYTE *buf, UINT widthPix, UINT height)
{
	if (buf==NULL)
		return FALSE;

	UINT col, row;
	for (row=0;row<height;row++) {
		for (col=0;col<widthPix;col++) {
			LPBYTE pRed, pGrn, pBlu;
			pRed = buf + row * widthPix * 3 + col * 3;
			pGrn = buf + row * widthPix * 3 + col * 3 + 1;
			pBlu = buf + row * widthPix * 3 + col * 3 + 2;

			// swap red and blue
			BYTE tmp;
			tmp = *pRed;
			*pRed = *pBlu;
			*pBlu = tmp;
		}
	}
	return TRUE;
}

BOOL CGameProcess::VertFlipBuf(BYTE  * inbuf, UINT widthBytes, UINT height)
{
	BYTE  *tb1;
	BYTE  *tb2;

	if (inbuf==NULL)
		return FALSE;

	UINT bufsize;

	bufsize=widthBytes;

	tb1= (BYTE *)new BYTE[bufsize];
	if (tb1==NULL) {
		return FALSE;
	}

	tb2= (BYTE *)new BYTE [bufsize];
	if (tb2==NULL) {
		delete [] tb1;
		return FALSE;
	}
	
	UINT row_cnt;     
	ULONG off1=0;
	ULONG off2=0;

	for (row_cnt=0;row_cnt<(height+1)/2;row_cnt++) {
		off1=row_cnt*bufsize;
		off2=((height-1)-row_cnt)*bufsize;   
		
		memcpy(tb1,inbuf+off1,bufsize);
		memcpy(tb2,inbuf+off2,bufsize);	
		memcpy(inbuf+off1,tb2,bufsize);
		memcpy(inbuf+off2,tb1,bufsize);
	}	

	delete [] tb1;
	delete [] tb2;

	return TRUE;
}        

BYTE * CGameProcess::MakeDwordAlignedBuf(BYTE *dataBuf, UINT widthPix, UINT height, UINT *uiOutWidthBytes)
{
	////////////////////////////////////////////////////////////
	// what's going on here? this certainly means trouble 
	if (dataBuf==NULL)
		return NULL;

	////////////////////////////////////////////////////////////
	// how big is the smallest DWORD-aligned buffer that we can use?
	UINT uiWidthBytes;
	uiWidthBytes = WIDTHBYTES(widthPix * 24);

	DWORD dwNewsize=(DWORD)((DWORD)uiWidthBytes * 
							(DWORD)height);
	BYTE *pNew;

	////////////////////////////////////////////////////////////
	// alloc and open our new buffer
	pNew=(BYTE *)new BYTE[dwNewsize];
	if (pNew==NULL) {
		return NULL;
	}
	
	////////////////////////////////////////////////////////////
	// copy row-by-row
	UINT uiInWidthBytes = widthPix * 3;
	UINT uiCount;
	for (uiCount=0;uiCount < height;uiCount++) {
		BYTE * bpInAdd;
		BYTE * bpOutAdd;
		ULONG lInOff;
		ULONG lOutOff;

		lInOff=uiInWidthBytes * uiCount;
		lOutOff=uiWidthBytes * uiCount;

		bpInAdd= dataBuf + lInOff;
		bpOutAdd= pNew + lOutOff;

		memcpy(bpOutAdd,bpInAdd,uiInWidthBytes);
	}

	*uiOutWidthBytes=uiWidthBytes;
	return pNew;
}


BOOL CGameProcess::Convert24To16(BYTE *pOrgImage, BYTE bOrgImgBitCount, WORD *pwImage, INT nWidth, INT nHeight)
{
	BYTE byRBit, byGBit, byBBit;
	WORD wPixel;

	int nByteAlignCX = (((nWidth * bOrgImgBitCount) + 31) & ~31) >> 3;

	for (int nYIdx = 0; nYIdx < nHeight; nYIdx++)
	{
		for (int nXIdx = 0; nXIdx < nWidth; nXIdx++)
		{			
			byRBit = pOrgImage[(nXIdx * 3 + 2) + (nYIdx * nByteAlignCX)];
			byGBit = pOrgImage[(nXIdx * 3 + 1) + (nYIdx * nByteAlignCX)];
			byBBit = pOrgImage[(nXIdx * 3 + 0) + (nYIdx * nByteAlignCX)];
			
			wPixel = ((byRBit >> 3) << 11) | ((byGBit >> 2) << 5) | (byBBit >> 3);

			if (((byRBit != 0) || (byGBit != 0) || (byBBit != 0)) && (wPixel == 0))
				wPixel = 1;

			// 비트맵을 거꾸로 돌림
			pwImage[nXIdx + ((nHeight - 1) - nYIdx) * nWidth] = wPixel;
		}
	}

	return TRUE;
}

char* CGameProcess::CheckAbnormalName(char *pszName)
{
	return pszName;
	CHAR szText[MAX_PATH];

	INT nLen = strlen(pszName);
	INT nI = 0, nJ = 0;

	while (nLen)
	{
		if ( *pszName == '<' || *pszName == '>' )
		{
			*pszName++;
		}
		else
		{
			szText[nI] = *pszName;
			nI++;
			*pszName++;
		}
		nLen--;
	}

	szText[nI] = 0;

//	return szText;
}

VOID CGameProcess::LoadCredit()
{
	ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_HIDE);

	m_xImageLogin.NewLoad(".\\Data\\Interface1c.wil");
	m_nIdxCreditBack = GetRandomNum(20,32);

	m_bCreditShow = TRUE;

	INT nW = m_rcCredit.right - m_rcCredit.left;

	INT nCnt;
	INT nLineCnt = 0;
	CHAR pszDivied[_MAX_STRING_LEN*2];
	CHAR pszArg[10][MAX_PATH];
	ZeroMemory(pszDivied, _MAX_STRING_LEN*2);
	ZeroMemory(pszArg,	  MAX_PATH*10);

	// 암호화 루틴해제.
	char* pszBuf = NULL;

	crypto_seed s = {(char) 0xF0, (char) 0x39, (char) 0xAB, (char) 0x8E, 0x9FDE1A93};
	crypto::setSeed( &s );

	FILE *fp = fopen("credit.edt", "rb");

	if ( !fp )
	{
		return;
	}

	int len = _filelength( _fileno( fp ) );
	pszBuf = new char[ len ];

	pszBuf[len] = 0;

	if ( !pszBuf )
	{
		fclose( fp );
		delete [] pszBuf;
		return;
	}

	fread( pszBuf, 1, len, fp );
	fclose( fp );

	if ( !crypto::decrypt( (unsigned char *)pszBuf, len ) )
	{
		delete[] pszBuf;
		return;
	}

	CHAR* pszTemp = pszBuf+8;

	INT nLen = strlen(pszTemp);

	fp = fopen( "credit.txt", "wb" );

	fwrite( pszTemp, sizeof( char ), nLen, fp );
	fclose( fp );

	fp = fopen("credit.txt", "rb");

	if ( !fp )
	{
		return;
	}

	CHAR	pszLine[MAX_PATH];
	CHAR	pszGet[MAX_PATH];
	CHAR*	pszNext = NULL;
	CHAR*	pszMark = NULL;
	CHAR*	pszStr  = NULL;

	while ( fgets(pszLine, MAX_PATH, fp) )
	{
		if ( pszLine[0] != ';' )
		{
			if ( pszNext = (CHAR*)strchr(pszLine, '\r') )
			{
				*pszNext = '\0';
			}

			pszStr = pszLine;

			INT	nSize   = 9;
			INT nBC     = 0;
			INT nFC     = 2;
			INT nWeight = FW_NORMAL;

			// 폰트사이즈.
			if ( pszMark = (CHAR*)strchr(pszLine, '!') )
			{
				ZeroMemory(pszGet, MAX_PATH);
				sscanf(++pszMark, "%s %*[^\0]", pszGet);
				nSize = atoi(pszGet);
			}

			// 폰트BackColor.
			if ( pszMark = (CHAR*)strchr(pszLine, '@') )
			{
				ZeroMemory(pszGet, MAX_PATH);
				sscanf(++pszMark, "%s %*[^\0]", pszGet);
				nBC = atoi(pszGet);
			}

			// 폰트Color.
			if ( pszMark = (CHAR*)strchr(pszLine, '#') )
			{
				ZeroMemory(pszGet, MAX_PATH);
				sscanf(++pszMark, "%s %*[^\0]", pszGet);
				nFC = atoi(pszGet);
			}

			// 폰트Bold.(두껍게)
			if ( (CHAR*)strchr(pszLine, '$') )
			{
				nWeight = FW_BOLD;
			}

			// 내용.
			if ( pszMark = (CHAR*)strchr(pszLine, '*') )
			{
				pszStr = ++pszMark;
			}

			ZeroMemory(pszDivied, _MAX_STRING_LEN*2);
			ZeroMemory(pszArg,	  MAX_PATH*10);
			g_xMainWnd.StringDivide(nW, nLineCnt, pszStr, pszDivied, g_xMainWnd.CreateGameFont(NULL, nSize, 0, nWeight));
			sscanf(pszDivied, "%[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c",
				   pszArg[0], pszArg[1], pszArg[2], pszArg[3], pszArg[4], 
				   pszArg[5], pszArg[6], pszArg[7], pszArg[8], pszArg[9]);

			if ( nLineCnt > 10 )
			{
				nLineCnt = 10;
			}

			for ( nCnt = 0; nCnt < nLineCnt; nCnt++ )
			{
				LPCREDIT pstNotice = new CREDIT;
				pstNotice->nBC  = nBC;
				pstNotice->nFC  = nFC;
				pstNotice->nSize = nSize;
				pstNotice->nWeight = nWeight;
				strcpy(pstNotice->pszMsg, pszArg[nCnt]);
				m_xCreditList.Insert(pstNotice);
			}
		}
	}
	fclose( fp );
	DeleteFile("credit.txt");
}


VOID CGameProcess::ShowCredit(INT nLoopTime)
{
	if ( m_xCreditList.GetCount() > 0 )
	{
		// 화면출력.
		LPCREDIT pstCredit   = NULL;
		CListNode < CREDIT > *pNode;

		INT nCnt;

		RECT rc = {m_rcCredit.left-5, m_rcCredit.top-5, m_rcCredit.right+5, m_rcCredit.bottom};
		INT nW = rc.right - rc.left;
		INT nH = rc.bottom - rc.top;

		static INT nScrlY = 0;
		static INT nSum   = -1500;

		if ( nLoopTime < 10000 )
		{
			nSum += nLoopTime;
		}

		if ( nSum > 15 )
		{
			nSum = 0;

			if ( m_xCreditList.GetCount()*14 > nH )
			{
				nScrlY -= 1;

				if ( abs(nScrlY) >= (m_xCreditList.GetCount()-1)*14 )
				{
					nScrlY = nH-14;
				}
			}
		}

		for ( pNode = m_xCreditList.GetHead(), nCnt = 0; pNode; pNode = pNode->GetNext(), nCnt++ )
		{
			pstCredit = pNode->GetData();

			if ( pstCredit )
			{
				if ( m_rcCredit.top+(nCnt*14)+nScrlY >= m_rcCredit.top && m_rcCredit.top+((nCnt+1)*14)+nScrlY < m_rcCredit.bottom )
				{
					g_xMainWnd.PutsHan(NULL, m_rcCredit.left, m_rcCredit.top+(nCnt*14)+nScrlY, 
									   GetChatColor(pstCredit->nFC), GetChatColor(pstCredit->nBC), 
									   pstCredit->pszMsg, g_xMainWnd.CreateGameFont(NULL, pstCredit->nSize, 0, pstCredit->nWeight));
				}
			}
		}
	}
}


// ShowLoading 함수로 때어내자 - 코드 정리
// by eriastoa 2006.04.05
VOID
CGameProcess::ShowLoading()
{
	Clear(0);
	
	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].NewSetIndex(m_nLoadImg) )
	{
		g_xMainWnd.DrawWithImageForComp(0, 0,
			g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shWidth,					
			g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shHeight,
			(WORD*)g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_pbCurrImage);
	}
	
	if ( g_dwCurrTime - m_dwLoadTxtTimer > 70 )
	{
		m_nLoadTxtImg++;
		m_dwLoadTxtTimer = g_dwCurrTime;
	}
	
	if ( m_nLoadTxtImg > 2239 )
		m_nLoadTxtImg = 2230;
	
	
	if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(m_nLoadTxtImg))
	{
		g_xMainWnd.DrawWithImageForComp(354, 540, 
			g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
			g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
			(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
	}
	
}

VOID CGameProcess::ShowMagicEffectTime()
{
	CHAR szMsg[40];
	RECT rcMsg = { 630, 460, 800, 475 };
	LPMAGICEFFECTTIME pstMagicEftTime   = NULL;
	CListNode <MAGICEFFECTTIME> *pNode;
	INT nCnt = 0;

	for ( pNode = m_xMagicEftTimeList.GetHead(); pNode; pNode = pNode->GetNext())
	{
		pstMagicEftTime = pNode->GetData();

		if ( pstMagicEftTime )
		{
			INT nKind = 1528+pstMagicEftTime->nKind;
			sprintf(szMsg, "%s : %d%s", g_xMsg.GetMsg(nKind), pstMagicEftTime->nTime, g_xMsg.GetMsg(1524) );
			g_xMainWnd.PutsHan(NULL, rcMsg.left, rcMsg.top,  RGB(255, 255,   0), RGB(0, 0, 0), szMsg);
			rcMsg.top -= 16;
			rcMsg.bottom -= 16;
			nCnt++;
		}
	}
}

VOID CGameProcess::CheckMagicEffectTime()
{
	LPMAGICEFFECTTIME pstMagicEftTime   = NULL;
	CListNode <MAGICEFFECTTIME> *pNode;
	CListNode <MAGICEFFECTTIME> *pNodeTemp;

	for ( pNode = m_xMagicEftTimeList.GetHead(); pNode; )
	{
		pstMagicEftTime = pNode->GetData();
		
		if ( pstMagicEftTime )
		{
			if ( g_dwCurrTime - pstMagicEftTime->dwInputTime > 1000 )
			{
				pstMagicEftTime->nTime = pstMagicEftTime->nTime - ( (g_dwCurrTime - pstMagicEftTime->dwInputTime) / 1000 );
				pstMagicEftTime->dwInputTime = g_dwCurrTime;

				if ( pstMagicEftTime->nTime <= 0 )

				{
					pNodeTemp = pNode->GetNext();


					m_xMagicEftTimeList.RemoveNode(pNode);
					pNode = pNodeTemp;
					continue;
				}
			}
			pNode = pNode->GetNext();
		}
	}
}
	
VOID CGameProcess::AutoFollow()
{
	if ( m_bFollowChar )
	{
		if ( g_dwCurrTime - m_dwFollowTimer > 10 )
		{
			CActor* pxActor;
			POINT	ptMouse;

			if ( m_nIdxFollowChar != 0 )
			{
				pxActor = FindActor(m_nIdxFollowChar);

				if ( pxActor )
				{
					ptMouse = m_xMyHero.GetPosTileToMouse(pxActor->m_nPosX, pxActor->m_nPosY);
					m_xMyHero.m_bCanRun = TRUE;
					m_xMyHero.OnRButtonDown(ptMouse);

					m_dwFollowTimer = g_dwCurrTime;
				}
			}
		}
	}
}

VOID CGameProcess::AutoHunt()
{
	return;

	AutoPickUp();

	CListNode < CActor >		*pNode;
	CListNode < CActor >		*pNodeTemp;
	CActor*						pxActor	= NULL;
	CActor*						pxTargetActor = NULL;

	BOOL						bFindTarget = FALSE;
	INT							nDistance = 0;
	INT							nMaxDistance = 6;
	BOOL						bFindItem = FALSE;

	POINT						ptMouse;

	if ( !bFindTarget )
	{
		// 아이템 찾아가기
		SIZE			sizeLen;
		LPGROUNDITEM	pstItem = NULL;

		INT nCenterX, nCenterY, nStartX, nStartY;

		INT nYCnt = 0, nXCnt = 0;

		nMaxDistance = 18;

		for ( nYCnt = m_xMap.m_nStartViewTileY; nYCnt < m_xMap.m_nStartViewTileY+_VIEW_CELL_Y_COUNT_FOR_OBJ; nYCnt++ )
		{
			for ( nXCnt = m_xMap.m_nStartViewTileX+m_nViewLGapX; nXCnt < m_xMap.m_nStartViewTileX+_VIEW_CELL_X_COUNT+m_nViewRGapX; nXCnt++ )
			{
				INT nMapViewX	   = 0;
				INT nMapViewY	   = 0;
				BOOL bFind = FALSE;

				if ( nXCnt >= m_xMap.m_nStartViewTileX && nXCnt < m_xMap.m_nStartViewTileX + _VIEW_CELL_X_COUNT && nYCnt >= m_xMap.m_nStartViewTileY && nYCnt < m_xMap.m_nStartViewTileY + _VIEW_CELL_Y_COUNT )
				{
					bFind = TRUE;
					nMapViewX = nXCnt - m_xMap.m_nStartViewTileX;
					nMapViewY = nYCnt - m_xMap.m_nStartViewTileY;
				}
		
				for ( INT nObjCnt = 0; nObjCnt < _MAX_CELL_OBJ && bFind ; nObjCnt++ )
				{

					pstItem = m_stMemMappedID[nMapViewY][nMapViewX].pstItem[nObjCnt];

					if ( pstItem )
					{
						INT nItemCnt;
						INT	nTotalItem  = 0;
						BOOL bGold = FALSE;
						for ( nItemCnt = 0; nItemCnt < _MAX_INVEN_ITEM; nItemCnt++ )
						{
							if ( g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nItemCnt].bSetted )
							{
								nTotalItem++;
							}
						}

						if ( strstr(pstItem->szItemName, g_xMsg.GetMsg(1050)) )
						{
							bGold = TRUE;
						}

						if ( (m_xMyHero.m_stAbility.wMaxWeight - m_xMyHero.m_stAbility.wWeight < 10) && !bGold )
						{
							continue;
						}

						if ( nTotalItem >= _MAX_INVEN_ITEM && !bGold )
						{						
							continue;
						}
						else
						{
						}

						nDistance = (INT)(sqrt((double)(nXCnt - m_xMyHero.m_nPosX)*(nXCnt - m_xMyHero.m_nPosX) + 
										  (nYCnt - m_xMyHero.m_nPosY)*(nYCnt - m_xMyHero.m_nPosY)));

						if ( nDistance < nMaxDistance )
						{
							nMaxDistance = nDistance;

							m_dwAutoTimer = g_dwCurrTime;
							ptMouse = m_xMyHero.GetPosTileToMouse(nXCnt, nYCnt);
							bFindItem = TRUE;
						}
					}
				}
			}
		}
	}

	if ( bFindItem )
	{
		m_xMyHero.m_bCanRun = FALSE;
		m_xMyHero.OnLButtonDown(ptMouse);
	}


	if ( !bFindItem )
	{
		nMaxDistance = 6;
		// 타겟 찾기
		for ( pNode = m_xActorList.GetHead(); pNode;  pNode = pNode->GetNext() )
		{
			pxActor = pNode->GetData();

			if ( pxActor )
			{
				BOOL bIsGuard = FALSE;
				BYTE bDress   = pxActor->m_stFeature.bDress;

				if ( bDress ==  86 || bDress == 113 || bDress == 114 || 
					 bDress == 115 || bDress == 165 || bDress == 166 || bDress == 26 || bDress == 127 )
				{
					continue;
				}

				if ( strchr( pxActor->m_szName, '(') )
				{
					continue;
				}

				if ( !pxActor->m_bIsDead )
				{
					switch ( pxActor->m_stFeature.bGender )
					{
					case _GENDER_MON:
						{
							nDistance = (INT)(sqrt((double)(pxActor->m_nPosX - m_xMyHero.m_nPosX)*(pxActor->m_nPosX - m_xMyHero.m_nPosX) + 
											  (pxActor->m_nPosY - m_xMyHero.m_nPosY)*(pxActor->m_nPosY - m_xMyHero.m_nPosY)));

							if ( nDistance < nMaxDistance )
							{
								nMaxDistance = nDistance;
								pxTargetActor = pxActor;
								bFindTarget = TRUE;
							}
						}
					}
				}
			}
		}
	}

	if ( bFindTarget )
	{
		m_pxSavedTargetActor = pxTargetActor;	// 공격대상 Actor정하기.
		m_dwAutoTimer = g_dwCurrTime;
	}
	

	if ( g_dwCurrTime - m_dwAutoTimer > 30000 && m_dwAutoTimer != 0)
	{
		for ( INT nCnt = 0; nCnt <= _MAX_INVEN_ITEM; nCnt++ )
		{
			if ( g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nCnt].bSetted )
			{
				if ( 205 == g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nCnt].xItem.m_stItemInfo.stStdItem.wLooks)
				{
					if ( !g_xGameProc.m_xInterface.m_stCommonItem.bSetted )
					{
						if ( g_xGameProc.m_bUseSpell == FALSE )
						{
							g_xGameProc.m_xInterface.m_stCommonItem.bSetted = TRUE;
							g_xGameProc.m_xInterface.m_stCommonItem.xItem = g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nCnt].xItem;
							g_xGameProc.m_xInterface.m_stCommonItem.bWaitResponse		= TRUE;
							g_xGameProc.m_xInterface.m_stCommonItem.bIsEquipItem		= FALSE;
							g_xGameProc.m_xInterface.m_stCommonItem.bIsDealItem		= FALSE;
							g_xGameProc.m_xInterface.m_stCommonItem.bIsHideItem		= TRUE;
							g_xGameProc.m_xInterface.m_stCommonItem.bIsBeltItem		= FALSE;
							g_xGameProc.m_xInterface.m_stCommonItem.bIsUtilItem 	= TRUE;

							m_dwAutoTimer = g_dwCurrTime;
							g_xClientSocket.SendItemIndex(CM_EAT, g_xGameProc.m_xInterface.m_stCommonItem.xItem.m_stItemInfo.nMakeIndex, g_xGameProc.m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName);
						}
					}
				}
			}
		}
	}

	if ( !bFindItem && !bFindTarget )
	{
		INT nTargetX, nTargetY;
		POINT ptMouse;

		if ( m_xMyHero.m_nPosX == 50 && m_xMyHero.m_nPosY == 50 )
		{
			m_nMoveDir = 1;
		}
		else if ( m_xMyHero.m_nPosX == 300 && m_xMyHero.m_nPosY == 50 )
		{
			m_nMoveDir = 2;
		}
		else if ( m_xMyHero.m_nPosX == 300 && m_xMyHero.m_nPosY == 300 )
		{
			m_nMoveDir = 3;
		}
		else if ( m_xMyHero.m_nPosX == 50 && m_xMyHero.m_nPosY == 300 )
		{
			m_nMoveDir = 0;
		}

		if ( m_nMoveDir == 0 )
		{
			nTargetX = 50;
			nTargetY = 50;
		}
		else if ( m_nMoveDir == 1 )
		{
			nTargetX = 300;
			nTargetY = 50;
		}
		else if ( m_nMoveDir == 2 )
		{
			nTargetX = 300;
			nTargetY = 300;
		}
		else if ( m_nMoveDir == 3 )
		{
			nTargetX = 50;
			nTargetY = 300;
		}

		if ( m_nMoveDir == 0 )
		{
			if ( nTargetX > m_xMyHero.m_nPosX )
				nTargetX = m_xMyHero.m_nPosX + 10;
			else if ( nTargetX < m_xMyHero.m_nPosX )
				nTargetX = m_xMyHero.m_nPosX - 10;

			if ( nTargetY > m_xMyHero.m_nPosY )
				nTargetY = m_xMyHero.m_nPosY + 10;
			else if ( nTargetY < m_xMyHero.m_nPosY )
				nTargetY = m_xMyHero.m_nPosY - 10;
			ptMouse = m_xMyHero.GetPosTileToMouse(nTargetX, nTargetY);
		}
		else if ( m_nMoveDir == 1 )
		{
			if ( nTargetX > m_xMyHero.m_nPosX )
				nTargetX = m_xMyHero.m_nPosX + 10;
			else if ( nTargetX < m_xMyHero.m_nPosX )
				nTargetX = m_xMyHero.m_nPosX - 10;

			if ( nTargetY > m_xMyHero.m_nPosY )
				nTargetY = m_xMyHero.m_nPosY + 10;
			else if ( nTargetY < m_xMyHero.m_nPosY )
				nTargetY = m_xMyHero.m_nPosY - 10;
			ptMouse = m_xMyHero.GetPosTileToMouse(nTargetX, nTargetY);
		}
		else if ( m_nMoveDir == 2 )
		{
			if ( nTargetX > m_xMyHero.m_nPosX )
				nTargetX = m_xMyHero.m_nPosX + 10;
			else if ( nTargetX < m_xMyHero.m_nPosX )
				nTargetX = m_xMyHero.m_nPosX - 10;

			if ( nTargetY > m_xMyHero.m_nPosY )
				nTargetY = m_xMyHero.m_nPosY + 10;
			else if ( nTargetY < m_xMyHero.m_nPosY )
				nTargetY = m_xMyHero.m_nPosY - 10;
			ptMouse = m_xMyHero.GetPosTileToMouse(nTargetX, nTargetY);
		}
		else if ( m_nMoveDir == 3 )
		{
			if ( nTargetX > m_xMyHero.m_nPosX )
				nTargetX = m_xMyHero.m_nPosX + 10;
			else if ( nTargetX < m_xMyHero.m_nPosX )
				nTargetX = m_xMyHero.m_nPosX - 10;

			if ( nTargetY > m_xMyHero.m_nPosY )
				nTargetY = m_xMyHero.m_nPosY + 10;
			else if ( nTargetY < m_xMyHero.m_nPosY )
				nTargetY = m_xMyHero.m_nPosY - 10;
			ptMouse = m_xMyHero.GetPosTileToMouse(nTargetX, nTargetY);
		}


/*
		if ( m_xMyHero.m_nPosX <= 100 )
		{
			nTargetX = m_xMyHero.m_nPosX + 1;
			m_bIncreaseX = TRUE;
		}
		else if ( m_xMyHero.m_nPosX >= 250 )
		{
			nTargetX = m_xMyHero.m_nPosX - 1;
			m_bIncreaseX = FALSE;
		}
		else if ( m_bIncreaseX )
		{
			nTargetX = m_xMyHero.m_nPosX + 1;
		}
		else if ( !m_bIncreaseX )
		{
			nTargetX = m_xMyHero.m_nPosX - 1;
		}

		if ( m_xMyHero.m_nPosY <= 100 )
		{
			nTargetY = m_xMyHero.m_nPosY + 1;
			m_bIncreaseY = TRUE;
		}
		else if ( m_xMyHero.m_nPosY >= 250 )
		{
			nTargetY = m_xMyHero.m_nPosY - 1;
			m_bIncreaseY = FALSE;
		}
		else if ( m_bIncreaseY )
		{
			nTargetY = m_xMyHero.m_nPosY + 1;
		}
		else if ( !m_bIncreaseY )
		{
			nTargetY = m_xMyHero.m_nPosY - 1;
		}
*/
		ptMouse = m_xMyHero.GetPosTileToMouse(nTargetX, nTargetY);
		m_xMyHero.m_bCanRun = FALSE;
		m_xMyHero.OnLButtonDown(ptMouse);
 
	}
}


INT CGameProcess::Encodebuffer(BYTE *szSource, BYTE *szKey, BYTE *szResult, BYTE nMode, int nSize)
{
	DWORD	pdwRoundKey[NoRoundKeys];
	BYTE	PT[16], DT[16],szTotalKey[16];

	ZeroMemory(PT, sizeof(PT));
	ZeroMemory(DT, sizeof(DT));
	ZeroMemory(szTotalKey, sizeof(szTotalKey));
	ZeroMemory(TCT, sizeof(TCT));

	
	int nBufferLen = nSize;//strlen((char *)szSource);

	szSource[nBufferLen] = NULL;
	if(nBufferLen < 0) return NULL;
	memcpy(TPT, szSource,nBufferLen);
	TPT[nBufferLen] = NULL;

	memcpy(szTotalKey, SUBKEY, 8);
	memcpy(szTotalKey+8, (char*)szKey,  8);

	SeedEncRoundKey(pdwRoundKey, szTotalKey);
	
	int nReadPos =0;
	int nWritePos = 0;

	while(nReadPos < nBufferLen)
	{
		ZeroMemory(PT, sizeof(PT));
		ZeroMemory(DT, sizeof(DT));

		for(int i=0;i<16;i++)
		{
			if(nReadPos<nBufferLen)
				PT[i]=TPT[nReadPos++]; 
			//nReadPos++;
		}

		memcpy(DT, PT, 16);
		//DT[16] = NULL;

		switch(nMode)
		{
		case ENCRYPTMODE : SeedEncrypt(DT, pdwRoundKey); break;
		case DECRYPTMODE : SeedDecrypt(DT, pdwRoundKey); break;
		} 

		//SeedDecrypt(DT, pdwRoundKey); 

		for(i=0;i<16;i++)
		{
			TCT[nWritePos]=DT[i];
			nWritePos++;
		}
	}
	for(int i=0;i<=nWritePos-1;i++)
		szResult[i] = TCT[i];
	szResult[nWritePos] = NULL;

	return nWritePos;
}

/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"

#define _VIEWMODE_CLICK_TIME  500

/******************************************************************************************************************

	함수명 : CInterface::CInterface()

	작성자 : 
	작성일 : 

	목적   : 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
CInterface::CInterface()
{
	Init();
}



/******************************************************************************************************************

	함수명 : CInterface::~CInterface()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
CInterface::~CInterface()
{
	Destroy();
}



/******************************************************************************************************************

	함수명 : CInterface::Init()

	작성자 : 
	작성일 : 

	목적   : 인터페이스관련 변수및, 객체초기화.
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CInterface::Init()
{
	m_nLogoIdx = 0;
	m_dwLogoTimer = 0;
	m_nMoveOffset = 0;
	m_bMoveWarning = FALSE;
	m_nWarningCnt = 0;
	sprintf( m_szWarning, "" );
	sprintf( m_szWarningOrigin, "" );

	m_dwViewModeClickTick = timeGetTime();
	m_nIdxMsgBox		= 0;
	m_nFstLine			= 0;
	m_nFstLineInLarge	= 0;
	m_shBeltHeight		= 0;
	m_bShowKey			= FALSE;
	m_bMoveFocusedWnd	= FALSE;
	m_bBeltState		= _BELT_STATE_STAY;
	m_bIsLargeChat		= FALSE;
	m_bIsMoving			= FALSE;
	m_bIsDown			= FALSE;

	m_bNewFliker		= FALSE;
	m_dwNewFliker		= 0;

	m_nFstLineInSystemChat = 0;
	m_nFstLineInNormalChat = 0;

	SetRect(&m_rcMain, 0, 0, 0, 0);
	SetRect(&m_rcChat, 0, 0, 0, 0);
	SetRect(&m_rcLargeChat, 0, 0, 0, 0);
	SetRect(&m_rcLargeChatRgn, 0, 0, 0, 0);

	SetRect(&m_rcSystemChat, 0, 0, 0, 0);
	SetRect(&m_rcNormalChat, 0, 0, 0, 0);

	ZeroMemory(&m_ptFrameLoc, sizeof(POINT));
	ZeroMemory(&m_stCommonItem, sizeof(ITEMSET));

	m_xClientSysMsg.Init();

	m_pxInterImg = NULL;

	m_nTopWndID = -1;

	m_xStatusWnd.Init();
	m_xStoreWnd.Init();
	m_xGuildWnd.Init();
	m_xGroupWnd.Init();
	m_xChatPopWnd.Init();
	m_xExchangeWnd.Init();
	m_xUserStateWnd.Init();
	m_xInventoryWnd.Init();
	m_xNoticeEditWnd.Init();
	m_xBeltWnd.Init();
	m_xSiegeWnd.Init();
	m_xMarketWnd.Init();
	m_xMarketUpWnd.Init();
	m_xMessengerWnd.Init();
	m_xFaceImgUpWnd.Init();
	m_xUtilWnd.Init();
	m_xViewMiniMapWnd.Init();
	m_xChatWnd.Init();
	m_xMagicShortcutWnd.Init();

	ZeroMemory(m_pszLastCapture, MAX_PATH);

	m_bViewMiniMap = FALSE;
	m_bViewMiniMapInMain = FALSE;
	m_dwQueryMsgTime = timeGetTime();

	m_dwWarningTimer = 0;

	for ( INT nCnt = 0; nCnt < _MAX_INTER_BTN; nCnt++ )
	{
		m_xInterBtn[nCnt].Init();
	}

	m_xWndOrderList.ClearAllNodes();

	m_xHearList.ClearAll();
	m_nSelHearNum = 0;

	m_xMacroList.ClearAll();
	m_nSelMacroNum = 0;

	m_nChatMode	= _CHAT_MODE_NORMAL;

	m_nInformationMode = _INFO_MINIMAP;
	m_bLoadUserFace = FALSE;
	m_bIsThereUserFile = TRUE;

	m_bAcShow = TRUE;
	m_bDcScMcShow = 0;

	m_bChatallDeny = FALSE;
	m_bDenyGuild   = FALSE;
	m_bDenyShout   = FALSE;

	m_bReadyViewMap = FALSE;
	m_bReadyInforMap = FALSE;

	m_bHasSiege = FALSE;
	m_bHasNewMessage = FALSE;

	m_dwFaceImgTimer = 0;
	m_dwSaveItemTimer = 0;

	m_bShowUserPic = TRUE;

	SetRect(&m_rcAcnum, 634, 570, 664, 590);
	SetRect(&m_rcDcnum, 372, 574, 397, 589);

	SetRect(&m_rcCharFace,  0, 0, 0, 0);
	SetRect(&m_rcLogo,  0, 0, 0, 0);

	//------------------------------------------------------------------------------------------------------------
	// 벨트 영역.
	ZeroMemory(m_rcBeltCell, sizeof(RECT) *_BELT_MAX_CELL );
	ZeroMemory(m_stBeltItem, sizeof(ITEMSET)*_MAX_BELT_ITEM );
	//------------------------------------------------------------------------------------------------------------

	ZeroMemory(&m_rcHPS , sizeof(RECT));						
	ZeroMemory(&m_rcMPS , sizeof(RECT));						
	ZeroMemory(&m_rcExpS, sizeof(RECT));						
	ZeroMemory(&m_rcWetS, sizeof(RECT));

}



/******************************************************************************************************************

	함수명 : CInterface::Destroy()

	작성자 : 
	작성일 : 

	목적   : 인터페이스관련 변수, 객체의 소멸및, 초기화.
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CInterface::Destroy()
{
	m_xClientSysMsg.Destroy();

//	m_xInterImgEx.Destroy();
	m_pxInterImg = NULL;
	

	m_xInventoryWnd.Destroy();
	m_xStatusWnd.Destroy();
	m_xStoreWnd.Destroy();
	m_xExchangeWnd.Destroy();
	m_xGuildWnd.Destroy();
	m_xGroupWnd.Destroy();
	m_xChatPopWnd.Destroy();
	m_xUserStateWnd.Destroy();
	m_xOptionWnd.Destroy();
	m_xQuestWnd.Destroy();
	m_xHorseWnd.Destroy();
	m_xMagicWnd.Destroy();
	m_xNPCWnd.Destroy();
	m_xNoticeEditWnd.Destroy();
	m_xSiegeWnd.Destroy();
	m_xMarketWnd.Destroy();
	m_xMarketUpWnd.Destroy();
	m_xMessengerWnd.Destroy();
	m_xFaceImgUpWnd.Destroy();
	m_xUtilWnd.Destroy();
	m_xViewMiniMapWnd.Destroy();
	m_xChatWnd.Destroy();
	m_xSettingWnd.Destroy();
	m_xGameOverWnd.Destroy();
	m_xMagicShortcutWnd.Destroy();

	for ( INT nCnt = 0; nCnt < _MAX_INTER_BTN; nCnt++ )
	{
		m_xInterBtn[nCnt].Destroy();
	}

	m_xSystemChat.ClearAll();
	m_xNormalChat.ClearAll();

	m_xChatlist.ClearAll();
	m_xLargeChatlist.ClearAll();
	m_xWndOrderList.ClearAllNodes();




	Init();






	
}


VOID CInterface::CreateInterface(CImageHandler* pxImgHandler)
{
	INT nCnt;

	m_pxInterImg = &(pxImgHandler->m_xImageList[_IMAGE_INTER]);

	//------------------------------------------------------------------------------------------------------------
	// 채팅에디트 윈도우 위치지정.
	MoveWindow(g_xChatEditBox.GetSafehWnd(), 
			   g_xMainWnd.m_rcWindow.left+_NEW_INPUT_EDITWND_XPOS, g_xMainWnd.m_rcWindow.top+_NEW_INPUT_EDITWND_YPOS,
			   _NEW_INPUT_EDITWND_WIDTH, _NEW_INPUT_EDITWND_HEIGHT, TRUE);

	// 메인인터페이스 영역설정.
	if ( m_pxInterImg->NewSetIndex(_WNDIMGIDX_MAIN) )
	{
		SetRect(&m_rcMain, 
				0, (600-m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight), 
				m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth, 600);
	}

	// 채팅 영역설정.
	SetRect(&m_rcSystemChat, 460, 488, 790, 548);
	SetRect(&m_rcNormalChat, 1, 450, 340, 524);

	// 큰채팅창화면 나왔을때 캐릭터움직임(LButtonDown) 제약할 범위.
	SetRect(&m_rcLargeChatRgn, 176, 297, 635, 552);

	for ( nCnt = 0; nCnt < _SYSTEM_CHATLINE; nCnt++ )
	{
		SetRect(&m_rcSystemChatLine[nCnt], 189, (492+nCnt*15), 530, (507+nCnt*15));
	}

	for ( nCnt = 0; nCnt < _SYSTEM_CHATLINE; nCnt++ )
	{
		SetRect(&m_rcNormalChatLine[nCnt], 189, (492+nCnt*15), 530, (507+nCnt*15));
	}

	SetRect(&m_rcHPS , 110, 560, 290, 574);						
	SetRect(&m_rcMPS ,  73, 475, 109, 563);						
	SetRect(&m_rcExpS,  94, 544, 794, 556);
	SetRect(&m_rcWetS,  95, 555, 110, 595);


	SetRect(&m_rcCharFace,  0, 457, 96, 600);
	SetRect(&m_rcLogo,  0, 514, 96, 600);

	m_ptFrameLoc.y = m_rcLogo.top;

	m_xInterBtn[ _3rd_BTN_ID_CHAR].CreateGameBtn(m_pxInterImg, 80, 81, m_rcMain.left+524, m_rcMain.top+16, g_xMsg.GetMsg(2613), _BTN_TYPE_FOCUS, -1, TRUE);		// 상태창.

	m_xInterBtn[ _3rd_BTN_ID_BAG].CreateGameBtn(m_pxInterImg, 82, 83, m_rcMain.left+558, m_rcMain.top+16, g_xMsg.GetMsg(2612), _BTN_TYPE_FOCUS, -1, TRUE);		// 가방창.

	m_xInterBtn[ _3rd_BTN_ID_MUGONG].CreateGameBtn(m_pxInterImg, 84, 85, m_rcMain.left+592, m_rcMain.top+16, g_xMsg.GetMsg(2607), _BTN_TYPE_FOCUS, -1, TRUE);		// 무공키창.

	m_xInterBtn[ _3rd_BTN_ID_BELT].CreateGameBtn(m_pxInterImg, 86, 87, m_rcMain.left+660, m_rcMain.top+16, g_xMsg.GetMsg(2615), _BTN_TYPE_FOCUS, -1, TRUE);		// 벨트창

	m_xInterBtn[ _3rd_BTN_ID_MINIMAP].CreateGameBtn(m_pxInterImg, 88, 89, m_rcMain.left+694, m_rcMain.top+16, g_xMsg.GetMsg(2601), _BTN_TYPE_FOCUS, -1, TRUE);		// 미니맵.

	m_xInterBtn[ _3rd_BTN_ID_QUEST].CreateGameBtn(m_pxInterImg, 90, 91, m_rcMain.left+728, m_rcMain.top+16, g_xMsg.GetMsg(2608), _BTN_TYPE_FOCUS, -1, TRUE);	// 퀘스트.

	m_xInterBtn[ _3rd_BTN_ID_OPTION].CreateGameBtn(m_pxInterImg, 92, 93, m_rcMain.left+762, m_rcMain.top+16, g_xMsg.GetMsg(2609), _BTN_TYPE_FOCUS, -1, TRUE);		// 옵션.
	m_xInterBtn[ _3rd_BTN_ID_CHANGE].CreateGameBtn(m_pxInterImg, 94, 95, m_rcMain.left+626, m_rcMain.top+16, g_xMsg.GetMsg(2600), _BTN_TYPE_FOCUS, -1, TRUE);		// 교환창.	

	m_xInterBtnofNewMessage.CreateGameBtn(m_pxInterImg, 330, 331, m_rcMain.left+757, m_rcMain.top-20, g_xMsg.GetMsg(4622), _BTN_TYPE_FOCUS, 330, TRUE);		// 새 메세지 버튼
	m_xInterBtnFaceImgUp.CreateGameBtn(m_pxInterImg, 2096, 2097, m_rcMain.left+757, m_rcMain.top-20, g_xMsg.GetMsg(4715), _BTN_TYPE_FOCUS, 2096, TRUE);		// 새 메세지 버튼

	m_xInventoryWnd.CreateInventoryWnd(_WND_ID_INVENTORY, m_pxInterImg, _WNDIMGIDX_INVENTORY, 518, 0, 282, 466, TRUE);
	m_xStatusWnd.CreateStatusWnd(_WND_ID_STATUS, m_pxInterImg, _WNDIMGIDX_STATUS, 0, 0, 328, 466, TRUE);
	m_xStoreWnd.CreateStoreWnd(_WND_ID_STORE, m_pxInterImg, _WNDIMGIDX_STORE, 0, 0, 292, 219, FALSE);

	POINT ptBelt = m_xBeltWnd.LoadBeltPosition();
	m_xBeltWnd.CreateBeltWnd(_WND_ID_BELT, m_pxInterImg, _WNDIMGIDX_BELT, ptBelt.x, ptBelt.y, 274, 50, TRUE, 3);


	m_xOptionWnd.CreateOptionWnd(_WND_ID_OPTION, m_pxInterImg, _WNDIMGIDX_OPTION, 255, 70, 290, 390, TRUE, 3);
	m_xGuildWnd.CreateGuildWnd(_WND_ID_GUILD, m_pxInterImg, _WNDIMGIDX_GUILD, 102, 22, 594, 444, TRUE);
	m_xNoticeEditWnd.CreateNoticeWnd(_WND_ID_NOTICEEDIT, m_pxInterImg, _WNDIMGIDX_NOTICEEDIT, 107, 110, 584, 252, FALSE, 3);
	m_xNPCWnd.CreateNPCChatWnd(_WND_ID_NPCCHAT, m_pxInterImg, _WNDIMGIDX_NPCCHAT_TOP_NOFACE, 0, 0, 386, 140, FALSE);
	m_xGroupWnd.CreateGroupWnd(_WND_ID_GROUP, m_pxInterImg, _WNDIMGIDX_GROUP, 272, 123, 238, 240, TRUE);
	m_xExchangeWnd.CreateExchangeWnd(_WND_ID_EXCHANGE, m_pxInterImg, _WNDIMGIDX_EXCHANGE, 0, 0, 494, 330, FALSE);
	m_xHorseWnd.CreateHorseWnd(_WND_ID_HORSE, m_pxInterImg, _NEW_WNDIMGIDX_HORSE, 0, 0, 276, 322, TRUE);
	m_xQuestWnd.CreateQuestWnd(_WND_ID_QUEST, m_pxInterImg, _NEW_WNDIMGIDX_QUEST, 0, 0, 340, 440, TRUE);
	m_xUserStateWnd.CreateUserStateWnd(_WND_ID_USERSTATE, m_pxInterImg, _WNDIMGIDX_STAUS_OTHERS, 516, 0, 284, 368, TRUE);
	m_xMagicWnd.CreateMagicWnd(_WND_ID_MAGIC, m_pxInterImg, _WNDIMGIDX_MAGIC, 348, 0, 360, 488, TRUE, 3);
	m_xSiegeWnd.CreateSiegeWnd(_WND_ID_SIEGE, m_pxInterImg, _WNDIMGIDX_SIEGE, 100, 100, 194, 285, TRUE);
	m_xMarketWnd.CreateUserMarketWnd(_WND_ID_USERMARKET, m_pxInterImg, _WNDIMGIDX_USERMARKET, 60, 20, 720, 440, FALSE, 3);
	m_xMarketUpWnd.CreateUserMarketWnd(_WND_ID_USERMARKETUP, m_pxInterImg, _WNDIMGIDX_USERMARKETUP, 0, 10, 408, 310, FALSE, 3);
	m_xMessengerWnd.CreateMessengerWnd(_WND_ID_MESSENGER, m_pxInterImg, _WNDIMGIDX_MESSENGER, 0, 0, 440, 310, FALSE, 3);
	m_xFaceImgUpWnd.CreateFaceImgUpWnd(_WND_ID_FACEIMGUP, m_pxInterImg, _WNDIMGIDX_FACEIMGUP, 0, 0, 580, 404, FALSE, 3);
	m_xChatWnd.CreateChatWnd(_WND_ID_CHAT, m_pxInterImg, _WNDIMGIDX_CHAT, 98, 519, 360, 26, FALSE, 0);
	m_xSettingWnd.CreateSettingWnd(_WND_ID_SETTING, m_pxInterImg, _WNDIMGIDX_SETTING, 660, 154, 140, 392, TRUE, 3);
	m_xGameOverWnd.CreateGameOverWnd(_WND_ID_EXIT, m_pxInterImg, _WNDIMGIDX_EXIT, 275, 200, 250, 110, FALSE, 3);
#ifdef _DEBUG
	m_xUtilWnd.CreateUtilWnd(_WND_ID_UTIL, m_pxInterImg, _WNDIMGIDX_UTIL, 120, 100, 564, 376, FALSE, 3);
#endif
	m_xViewMiniMapWnd.CreateViewMiniMapWnd(_WND_ID_VIEWMINIMAP, m_pxInterImg, _WNDIMGIDX_VIEWMINIMAP, 26, 1, 748, 588, FALSE);
	m_xMagicShortcutWnd.CreateMagicShortcutWnd(_WND_ID_MAGICSHORTCUT, m_pxInterImg, _WNDIMGIDX_MAGICSHORTCUT, 10, 10, 220, 196, TRUE, 3);
	//------------------------------------------------------------------------------------------------------------
	// 윈도우들 생성.
	m_xChatPopWnd.CreateChatPopWnd(_WND_ID_CHATPOP, m_pxInterImg, _WNDIMGIDX_CHATPOP, 114, 76, 572, 388, TRUE, 0);
	
	
	
	
	//------------------------------------------------------------------------------------------------------------


	//------------------------------------------------------------------------------------------------------------
	// 벨트 영역.
	for ( nCnt = 0; nCnt < _MAX_BELT_ITEM; nCnt++ )
	{
		SetRect(&m_rcBeltCell[nCnt], 
				_BELT_CELL_XSTART+(nCnt*_BELT_CELL_XGAP),
				_BELT_CELL_YSTART,
				_BELT_CELL_XSTART+(nCnt*_BELT_CELL_XGAP)+_INVENTORY_CELL_WIDTH,
				_BELT_CELL_YSTART+_INVENTORY_CELL_HEIGHT);
	}

	//------------------------------------------------------------------------------------------------------------

	m_xMiniMap.InitMiniMap(g_xMainWnd.Get3DDevice());
	m_xMiniMapInSiege.InitMiniMap(g_xMainWnd.Get3DDevice());

	LoadHearList();
	LoadMacroList();
}



/******************************************************************************************************************

	함수명 : CInterface::MsgAdd()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : DWORD dwFontColor
	         DWORD dwFontBackColor
	         CHAR* pszMsg
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CInterface::MsgAdd(DWORD dwFontColor, DWORD dwFontBackColor, CHAR* pszMsg)
{
	m_xChatWnd.MsgAdd(dwFontColor, dwFontBackColor, pszMsg);
	
	if ( pszMsg )
	{
		if ( strncmp( pszMsg, "(*)", 3 ) == 0 )
		{
			m_sizeWarning = g_xMainWnd.GetStrLength(NULL, g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 10, 0, FW_BOLD), pszMsg);
			m_sizeWarning.cx /= 2;
			m_nMoveOffset = 0;
			
			strcpy( &m_szWarning[0], &pszMsg[3]);
			strcpy( &m_szWarningOrigin[0], &pszMsg[3]);
			m_nWarningCnt = 0;
			m_dwWarningTimer = g_dwCurrTime;
			m_bMoveWarning = TRUE;
			return;
		}

		if ( dwFontColor == 16777215 && dwFontBackColor == 33023 ||
			 dwFontColor == 16777215 && dwFontBackColor == 255 ||
			 dwFontColor == 657930 && dwFontBackColor == 16750230 ||
			 dwFontColor == 255 && dwFontBackColor == 16777215 )
		{
			if ( pszMsg[0] != NULL )
			{
				INT  nCnt;
				CHAT* stChat;
				INT	 nLineCnt;
				CHAR pszDivided[_MAX_STRING_LEN*2];
				CHAR pszArg[5][MAX_PATH];
				
				ZeroMemory(pszDivided, _MAX_STRING_LEN*2);
				ZeroMemory(pszArg,	  MAX_PATH*5);
				
				g_xMainWnd.StringDivide(m_rcSystemChat.right-m_rcSystemChat.left, nLineCnt, pszMsg, pszDivided);
				sscanf(pszDivided, "%[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c", pszArg[0], pszArg[1], pszArg[2], pszArg[3], pszArg[4]);

				if ( nLineCnt > 5 )		
				{
					nLineCnt = 5;
				}

				// 문자열 삽입.
				for ( nCnt = 0; nCnt < nLineCnt; nCnt++ )
				{
					if ( m_xSystemChat.GetCount() - m_nFstLineInSystemChat == _SYSTEM_CHATLINE )
					{
						m_nFstLineInSystemChat++;
					}

					stChat = new CHAT;

					if ( dwFontColor == 16777215 && dwFontBackColor == 255 )
						stChat->dwFontColor = GetChatColor(_CHAT_COLOR4);
					else if ( dwFontColor == 657930 && dwFontBackColor == 16750230 )
						stChat->dwFontColor = GetChatColor(_CHAT_COLOR6);
					else
						stChat->dwFontColor = dwFontColor;

					stChat->dwBackColor = g_dwCurrTime;
					strcpy(stChat->pszChat, pszArg[nCnt]);
					
					m_xSystemChat.Insert(stChat);
				}

				CListNode < CHAT >		*pNode;
				CHAT*					pstChat = NULL;

				while ( m_xSystemChat.GetCount() > _SYSTEM_CHATLINE )
				{
					pNode = m_xSystemChat.GetHead();
					pstChat = m_xSystemChat.RemoveNode(pNode);

					if ( pstChat )
					{
						delete((CHAT*) pstChat);
						pstChat = NULL;
					}

					if ( m_nFstLineInSystemChat > 0 )
					{
						m_nFstLineInSystemChat--;
					}
				}
			}
		}
		else if ( dwFontColor == 16777215 && dwFontBackColor == 0 || 
				  dwFontColor == 657930 && dwFontBackColor == 5308415 ||
				  dwFontColor == 657930 && dwFontBackColor == 65280 ||
				  dwFontColor == 65280 && dwFontBackColor == 0 ||
				  dwFontColor == 5308415 && dwFontBackColor == 0 ||
				  dwFontColor == 16750230 && dwFontBackColor == 0 ||
				  dwFontColor == 33023 && dwFontBackColor == 0 ||
				  dwFontColor == 255 && dwFontBackColor == 0 )
		{
			if ( pszMsg[0] != NULL )
			{
				INT  nCnt;
				CHAT* stChat;
				INT	 nLineCnt;
				CHAR pszDivided[_MAX_STRING_LEN*2];
				CHAR pszArg[5][MAX_PATH];
				
				ZeroMemory(pszDivided, _MAX_STRING_LEN*2);
				ZeroMemory(pszArg,	  MAX_PATH*5);
				
				g_xMainWnd.StringDivide(m_rcNormalChat.right-m_rcNormalChat.left, nLineCnt, pszMsg, pszDivided);
				sscanf(pszDivided, "%[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c", pszArg[0], pszArg[1], pszArg[2], pszArg[3], pszArg[4]);

				if ( nLineCnt > 5 )		
				{
					nLineCnt = 5;
				}

				// 문자열 삽입.
				for ( nCnt = 0; nCnt < nLineCnt; nCnt++ )
				{
					if ( m_xNormalChat.GetCount() - m_nFstLineInNormalChat == _SYSTEM_CHATLINE )
					{
						m_nFstLineInNormalChat++;
					}

					stChat = new CHAT;
					stChat->dwBackColor = g_dwCurrTime;
					strcpy(stChat->pszChat, pszArg[nCnt]);

					if ( dwFontColor == 657930 && dwFontBackColor == 5308415 )
					{
						stChat->dwFontColor = GetChatColor(_CHAT_COLOR7);
					}
					else if ( dwFontColor == 657930 && dwFontBackColor == 65280 )
					{
						stChat->dwFontColor = GetChatColor(_CHAT_COLOR5);
					}
					else if ( dwFontColor == 65280 && dwFontBackColor == 0 )
					{
						stChat->dwFontColor = GetChatColor(_CHAT_COLOR6);
					}
					else if ( dwFontColor == 5308415 && dwFontBackColor == 0 )
					{
						stChat->dwFontColor = GetChatColor(_CHAT_COLOR7);
					}
					else if ( dwFontColor == 16750230 && dwFontBackColor == 0 )
					{
						stChat->dwFontColor = dwFontColor;
					}
					else if ( dwFontColor == 33023 && dwFontBackColor == 0 )
					{
						stChat->dwFontColor = dwFontColor;
					}
					else if ( dwFontColor == 255 && dwFontBackColor == 0 )
					{
						stChat->dwFontColor = dwFontColor;
					}
					else
					{
						stChat->dwFontColor = RGB(250, 250, 250);
					}

					
					m_xNormalChat.Insert(stChat);
				}

				CListNode < CHAT >		*pNode;
				CHAT*					pstChat = NULL;

				while ( m_xNormalChat.GetCount() > _SYSTEM_CHATLINE )
				{
					pNode = m_xNormalChat.GetHead();
					pstChat = m_xNormalChat.RemoveNode(pNode);

					if ( pstChat )
					{
						delete((CHAT*) pstChat);
						pstChat = NULL;
					}

					if ( m_nFstLineInNormalChat > 0 )
					{
						m_nFstLineInNormalChat--;
					}
				}
			}
		}
		else if ( dwFontBackColor == 255 && dwFontColor == 16777215 )
		{
			m_sizeWarning = g_xMainWnd.GetStrLength(NULL, g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 10, 0, FW_BOLD), pszMsg);
			m_sizeWarning.cx /= 2;
			m_nMoveOffset = 0;
			
			strcpy( &m_szWarning[0], &pszMsg[3]);
			strcpy( &m_szWarningOrigin[0], &pszMsg[3]);
//			sprintf( m_szWarning, pszMsg );
//			sprintf( m_szWarningOrigin, pszMsg );
			m_dwWarningTimer = g_dwCurrTime;
			m_bMoveWarning = TRUE;
		}
	}
}



/******************************************************************************************************************

	함수명 : CInterface::ShowWndList()

	작성자 : 
	작성일 : 

	목적   : Active되어있는 윈도우의 리스트를 보여준다.
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CInterface::ShowWndList()
{
	m_xInterBtnFaceImgUp.ChangeRect(m_rcMain.left+535, m_rcMain.top+100);

	if ( m_xWndOrderList.GetCounter() != 0 )
	{
		m_xWndOrderList.MoveCurrentToTop();

		INT* pnCurrID;

		BOOL bDrawChatEdit = TRUE;
		RECT rcChat = {_NEW_INPUT_EDITWND_XPOS, _NEW_INPUT_EDITWND_YPOS, _NEW_INPUT_EDITWND_XPOS+_NEW_INPUT_EDITWND_WIDTH, _NEW_INPUT_EDITWND_YPOS+_NEW_INPUT_EDITWND_HEIGHT};
		RECT rcIntersect;

		for ( INT nCnt = 0; nCnt < m_xWndOrderList.GetCounter(); nCnt++ )
		{
			pnCurrID = m_xWndOrderList.GetCurrentData();

			RECT* prcInter = NULL;

			switch ( *pnCurrID )
			{
			case _WND_ID_INVENTORY:
				m_xInventoryWnd.ShowInventoryWnd();
				prcInter = &m_xInventoryWnd.m_rcWnd;
				break;
			case _WND_ID_STATUS:
				m_xStatusWnd.ShowStatusWnd();
				prcInter = &m_xStatusWnd.m_rcWnd;
				break;
			case _WND_ID_STORE:
				m_xStoreWnd.ShowStoreWnd();
				prcInter = &m_xStoreWnd.m_rcWnd;
				break;
			case _WND_ID_EXCHANGE:
				m_xExchangeWnd.ShowExchangeWnd();
				prcInter = &m_xExchangeWnd.m_rcWnd;
				break;
			case _WND_ID_GUILD:
				m_xGuildWnd.ShowGuildWnd();
				prcInter = &m_xGuildWnd.m_rcWnd;
				break;
			case _WND_ID_GROUP:
				m_xGroupWnd.ShowGroupWnd();
				prcInter = &m_xGroupWnd.m_rcWnd;
				break;
			case _WND_ID_USERSTATE:
				m_xUserStateWnd.ShowUserStateWnd();
				prcInter = &m_xUserStateWnd.m_rcWnd;
				break;
			case _WND_ID_CHATPOP:
				m_xChatPopWnd.ShowChatPopWnd();
				prcInter = &m_xChatPopWnd.m_rcWnd;
				break;
			case _WND_ID_NPCCHAT:
				m_xNPCWnd.ShowNPCChatWnd();
				prcInter = &m_xNPCWnd.m_rcWnd;
				break;
			case _WND_ID_QUEST:
				m_xQuestWnd.ShowQuestWnd();
				prcInter = &m_xQuestWnd.m_rcWnd;
				break;
			case _WND_ID_OPTION:
				m_xOptionWnd.ShowOptionWnd();
				prcInter = &m_xOptionWnd.m_rcWnd;
				break;
			case _WND_ID_HORSE:
				m_xHorseWnd.ShowHorseWnd();
				prcInter = &m_xHorseWnd.m_rcWnd;
				break;
			case _WND_ID_MAGIC:
				m_xMagicWnd.ShowMagicWnd();
				prcInter = &m_xMagicWnd.m_rcWnd;
				break;
			case _WND_ID_NOTICEEDIT:
				m_xNoticeEditWnd.ShowNoticeWnd();
				prcInter = &m_xNoticeEditWnd.m_rcWnd;
				break;
			case _WND_ID_BELT:
				m_xBeltWnd.ShowBeltWnd();
				prcInter = &m_xBeltWnd.m_rcWnd;
				break;
			case _WND_ID_SIEGE:
				m_xSiegeWnd.ShowSiegeWnd();
				prcInter = &m_xSiegeWnd.m_rcWnd;
				break;
			case _WND_ID_MAGICSHORTCUT:
				m_xMagicShortcutWnd.ShowMagicShortcutWnd();
				prcInter = &m_xMagicShortcutWnd.m_rcWnd;
				break;
			case _WND_ID_USERMARKET:
				m_xMarketWnd.ShowUserMarketWnd();
				prcInter = &m_xMarketWnd.m_rcWnd;
				break;
			case _WND_ID_USERMARKETUP:
				m_xMarketUpWnd.ShowUserMarketUpWnd();
				prcInter = &m_xMarketUpWnd.m_rcWnd;
				break;
			case _WND_ID_MESSENGER:
				m_xMessengerWnd.ShowMessengerWnd();
				prcInter = &m_xMessengerWnd.m_rcWnd;
				break;
			case _WND_ID_FACEIMGUP:
				m_xFaceImgUpWnd.ShowFaceImgUpWnd();
				prcInter = &m_xFaceImgUpWnd.m_rcWnd;
				break;
			case _WND_ID_UTIL:
				m_xUtilWnd.ShowUtilWnd();
				prcInter = &m_xUtilWnd.m_rcWnd;
				break;
			case _WND_ID_VIEWMINIMAP:
				m_xViewMiniMapWnd.ShowViewMiniMapWnd();
				prcInter = &m_xViewMiniMapWnd.m_rcWnd;
				break;
			case _WND_ID_CHAT:
				m_xChatWnd.ShowChatWnd();
				prcInter = &m_xChatWnd.m_rcWnd;
				break;
			case _WND_ID_SETTING:
				m_xSettingWnd.ShowSettingWnd();
				prcInter = &m_xSettingWnd.m_rcWnd;
				break;
			case _WNDIMGIDX_EXIT:
				m_xGameOverWnd.ShowGameOver();
				prcInter = &m_xGameOverWnd.m_rcWnd;
				break;
			}			

			if ( *pnCurrID != _WND_ID_CHATPOP && IntersectRect(&rcIntersect, &rcChat, prcInter) )
			{
				bDrawChatEdit = FALSE;
			}

			m_xWndOrderList.MoveNextNode();
		}

		m_nTopWndID = *pnCurrID;

		// 아이템 상태치 보여줄 윈도우를 고른다.
		INT	nMouseWnd = GetWindowInMousePos(g_xGameProc.m_ptMousePos);
		switch ( nMouseWnd )
		{
		case _WND_ID_INVENTORY:
			m_xInventoryWnd.ShowInvenItemState();	
			break;
		case _WND_ID_STATUS:
			m_xStatusWnd.ShowEquipItemState();
			break;
		case _WND_ID_EXCHANGE:
			m_xExchangeWnd.ShowDealItemState();
			break;
		case _WND_ID_USERSTATE:
			m_xUserStateWnd.ShowUserItemState();
			break;
		case _WND_ID_STORE:
			m_xStoreWnd.ShowDetailItemState();
			break;
		case _WND_ID_UTIL:
			m_xUtilWnd.ShowMenuItemState();
			break;
		}

		if ( !bDrawChatEdit )
		{
			ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_HIDE);
		}
	}	
}



/******************************************************************************************************************

	함수명 : CInterface::ShowChatList()

	작성자 : 
	작성일 : 

	목적   : 채팅 리스트를 보여준다.
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CInterface::ShowSystemChat()
{
	if ( !m_xSystemChat.IsEmpty() )
	{
		INT		nCnt, nShowLine;
		LPCHAT	pstChat;

		CListNode < CHAT >		*pNode;

		pNode = m_xSystemChat.GetHead();
		for ( ; pNode; )
		{
			pstChat = *pNode;
			
			if ( pstChat )
			{
				if ( g_dwCurrTime - pstChat->dwBackColor > 10000 )
				{
					m_xSystemChat.RemoveNode(pNode);
					pNode = m_xSystemChat.GetHead();
					SAFE_DELETE(pstChat);

					if ( m_nFstLineInSystemChat > 0 )
					{
						m_nFstLineInSystemChat--;
					}
					continue;
				}
				else
					pNode = pNode->GetNext();
			}
		}

		pNode = m_xSystemChat.GetHead();
		for ( INT nCount=0; nCount < m_nFstLineInSystemChat; nCount++)
			pNode = pNode->GetNext();

		if ( m_xSystemChat.GetCount() - m_nFstLineInSystemChat >= _SYSTEM_CHATLINE)
			nShowLine = _SYSTEM_CHATLINE;
		else
			nShowLine = m_xSystemChat.GetCount() - m_nFstLineInSystemChat;

		SetRect(&m_rcSystemChat, 460, 473, 790, 548);
		
		for ( nCnt = 0; nCnt < nShowLine; nCnt++ )
		{
			pstChat = *pNode;

			if ( pstChat )
			{
				if ( timeGetTime() - pstChat->dwBackColor > 10000 )
				{
					pNode = pNode->GetNext();
					continue;
				}

				INT nTemp = nCnt;
				if ( m_xSystemChat.GetCount() < 5 ) 
					nTemp += 5 - m_xSystemChat.GetCount();

				g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(),
								   m_rcSystemChat.left+1, m_rcSystemChat.top+nTemp*15+1,
								   0, 0, pstChat->pszChat);

				g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(),
								   m_rcSystemChat.left, m_rcSystemChat.top+nTemp*15,
								   pstChat->dwFontColor, 0, pstChat->pszChat);
			}

			pNode = pNode->GetNext();
		}
	}
}

VOID CInterface::ShowNormalChat()
{
	if ( !m_xNormalChat.IsEmpty() && ( !m_xChatWnd.GetGameWndActive() || !m_xChatWnd.mChat_bLargeChat) )
	{
		INT		nCnt, nShowLine;
		LPCHAT	pstChat;

		CListNode < CHAT >		*pNode;

		pNode = m_xNormalChat.GetHead();
		for ( ; pNode; )
		{
			pstChat = *pNode;
			
			if ( pstChat )
			{
				if ( g_dwCurrTime - pstChat->dwBackColor > 10000 )
				{
					m_xNormalChat.RemoveNode(pNode);
					pNode = m_xNormalChat.GetHead();
					SAFE_DELETE(pstChat);

					if ( m_nFstLineInNormalChat > 0 )
					{
						m_nFstLineInNormalChat--;
					}
					continue;
				}
				else
					pNode = pNode->GetNext();
			}
		}

		pNode = m_xNormalChat.GetHead();
		for ( INT nCount=0; nCount < m_nFstLineInNormalChat; nCount++)
			pNode = pNode->GetNext();

		if ( m_xNormalChat.GetCount() - m_nFstLineInNormalChat >= _SYSTEM_CHATLINE)
			nShowLine = _SYSTEM_CHATLINE;
		else
			nShowLine = m_xNormalChat.GetCount() - m_nFstLineInNormalChat;

		if ( m_nInformationMode == _INFO_CHAR )
			SetRect(&m_rcNormalChat, 1, 384, 340, 457);
		else
			SetRect(&m_rcNormalChat, 1, 440, 340, 545);

		for ( nCnt = 0; nCnt < nShowLine; nCnt++ )
		{
			pstChat = *pNode;

			if ( pstChat )
			{
//				if ( g_dwCurrTime - pstChat->dwBackColor > 10000 )
//				{
//					m_xNormalChat.RemoveNode(pNode);
//					pNode = pNode->GetNext();
//					continue;
//				}

				INT nTemp = nCnt;
				if ( m_xNormalChat.GetCount() < 5 ) 
					nTemp += 5 - m_xNormalChat.GetCount();

				g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(),
								   m_rcNormalChat.left, m_rcNormalChat.top+nTemp*15-1,
								   0, 0, pstChat->pszChat);

				g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(),
								   m_rcNormalChat.left, m_rcNormalChat.top+nTemp*15+1,
								   0, 0, pstChat->pszChat);

				g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(),
								   m_rcNormalChat.left+1, m_rcNormalChat.top+nTemp*15,
								   0, 0, pstChat->pszChat);

				g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(),
								   m_rcNormalChat.left-1, m_rcNormalChat.top+nTemp*15,
								   0, 0, pstChat->pszChat);

				g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(),
								   m_rcNormalChat.left, m_rcNormalChat.top+nTemp*15,
								   pstChat->dwFontColor, 0, pstChat->pszChat);
			}

			pNode = pNode->GetNext();
		}
	}
}



VOID CInterface::ShowLargeChatList()
{
	if ( !m_xLargeChatlist.IsEmpty() )
	{
		INT		nCnt, nShowLine;
		LPCHAT	pstChat;

		CListNode < CHAT >		*pNode;

		pNode = m_xLargeChatlist.GetHead();
		for ( INT nCount=0; nCount < m_nFstLineInLarge; nCount++)
			pNode = pNode->GetNext();

		if ( m_xLargeChatlist.GetCount() - m_nFstLineInLarge >= _MAX_CHATLINE)
			nShowLine = _MAX_CHATLINE;
		else
			nShowLine = m_xLargeChatlist.GetCount() - m_nFstLineInLarge;		
		
		for ( nCnt = 0; nCnt < nShowLine; nCnt++ )
		{
			pstChat = *pNode;

			if ( pstChat )
			{
				g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(),
								   m_rcLargeChat.left, m_rcLargeChat.top+nCnt*15,
								   pstChat->dwFontColor, pstChat->dwBackColor, pstChat->pszChat);
			}

			pNode = pNode->GetNext();
		}
	}
}


VOID CInterface::SetCaputeString(CHAR* pszChat)
{
	CHAR  pszString[MAX_PATH];
	CHAR* pszCapture;
	CHAR* pszCut;

	strcpy(pszString, pszChat);

	pszCapture = pszString;

	if ( pszCapture[0] == '/' )
	{
		pszCapture++;
		
		while ( pszCut = strchr(pszCapture, ' ') )
		{
			pszCut++;
			if ( *pszCut )
			{
				*pszCut = '\0';
				break;
			}
			else
			{
				sprintf(m_pszLastCapture, "/%s", pszCapture);
				return;
			}
			pszCapture = pszCut;
		}

		if ( *pszCapture )
		{
			if ( pszCut = strchr(pszCapture, ' ') )
			{
				*pszCut = '\0';
			}

			sprintf(m_pszLastCapture, "/%s ", pszCapture);
		}
	}
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// 귓말 리스트 관련.
//---------------------------------------------------------------------------------------------------------------//
LONG CInterface::CtrlNumPushed(WPARAM wParam, LPARAM lParam)
{
	if ( !g_xGameProc.m_xGameMsgBox.IsActive() )
	{
		if ( m_xHearList.GetCount() > (INT)wParam )
		{
			m_nSelHearNum = (INT)wParam;
		}

		SetHearList();
	}
	return 0L;
}


VOID CInterface::SetHearList()
{
	CListNode < CHAT > *pNode;

	INT		nCnt;
	LPCHAT	pstChat = NULL;

	for ( pNode = m_xHearList.GetHead(), nCnt = 0; pNode; pNode = pNode->GetNext(), nCnt++ )
	{
		pstChat = pNode->GetData();

		if ( nCnt == m_nSelHearNum )
		{
			if ( pstChat )
			{
				sprintf(m_pszLastCapture, "/%s", pstChat->pszChat);

				SetFocus(g_xChatEditBox.GetSafehWnd());
				ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);
				SetWindowText(g_xChatEditBox.GetSafehWnd(), m_pszLastCapture);

				INT nLen = strlen(m_pszLastCapture);
				SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETSEL, nLen , nLen);
				g_xChatEditBox.SetHanguelMode();

				break;
			}
		}
	}
}


LPCHAT CInterface::FindHearList(CHAR* pszHear)
{
	CListNode < CHAT > *pNode;

	LPCHAT pstChat = NULL;

	for ( pNode = m_xHearList.GetHead(); pNode; pNode = pNode->GetNext() )
	{
		pstChat = pNode->GetData();

		if ( pstChat )
		{
			if ( !strcmp(pstChat->pszChat, pszHear) )
			{
				return pstChat;
			}			
		}
	}

	return NULL;
}


VOID CInterface::AddHearList(CHAR* pszHear)
{
	if ( FindHearList(pszHear) == NULL )
	{
		LPCHAT pstChat = NULL;
		pstChat = new CHAT;
		pstChat->dwBackColor = RGB(0, 0, 0);
		pstChat->dwFontColor = RGB(255, 255, 255);
		sprintf(pstChat->pszChat, "%s", pszHear);
		m_xHearList.Insert(pstChat);

		if ( m_xHearList.GetCount() > 10 )
		{
			CListNode < CHAT > *pNode   = m_xHearList.GetHead();
			LPCHAT				pstChat = pNode->GetData();
			if ( pstChat )
			{
				m_xHearList.RemoveNode(pNode);
				SAFE_DELETE(pstChat);
			}
		}

		SaveHearList();
	}
}


VOID CInterface::ShowHearList()
{
	if ( m_xHearList.GetCount() && !g_xGameProc.m_xGameMsgBox.IsActive() && (GetKeyState(VK_CONTROL) & 0x80) && (GetFocus() == g_xChatEditBox.GetSafehWnd()) )
	{
		CListNode < CHAT > *pNode;

		INT		nCnt;
		LPCHAT	pstChat = NULL;
		RECT	rcList;

		SetRect(&rcList, 100, 356, 230, 520);
		g_xMainWnd.DrawWithGDI(&rcList, NULL, RGB(200, 200, 200), 1);

		D3DMATERIAL7 mtrl;
		D3DVECTOR	 vecTrans((FLOAT)rcList.left, (FLOAT)rcList.top, 0);
		D3DVECTOR	 vecScale((FLOAT)rcList.right-rcList.left, rcList.bottom-rcList.top, 1);

		D3DUtil_InitMaterial(mtrl, (FLOAT)80/255.0f, (FLOAT)80/255.0f, (FLOAT)80/255.0f);
		mtrl.diffuse.a = 180.0f/255.0f;
		g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

		for ( pNode = m_xHearList.GetHead(), nCnt = 0; pNode; pNode = pNode->GetNext(), nCnt++ )
		{
			pstChat = pNode->GetData();

			if ( pstChat )
			{
				if ( nCnt == m_nSelHearNum )
				{
					D3DUtil_InitMaterial(mtrl, (FLOAT)100/255.0f, (FLOAT)100/255.0f, (FLOAT)100/255.0f);
					mtrl.diffuse.a = 120.0f/255.0f;
					vecTrans = D3DVECTOR((FLOAT)rcList.left+1, (FLOAT)rcList.top+nCnt*16+2, 0);
					vecScale = D3DVECTOR((FLOAT)(rcList.right-rcList.left-2), 16.0f, 1);
 					g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
				}
				g_xMainWnd.PutsHan(NULL, rcList.left+4, rcList.top+nCnt*16+4, RGB( 10,  10,  10), RGB(0, 0, 0), pstChat->pszChat, NULL);
				g_xMainWnd.PutsHan(NULL, rcList.left+5, rcList.top+nCnt*16+5, RGB(255, 255, 255), RGB(0, 0, 0), pstChat->pszChat, NULL);
			}
		}
	}
}


VOID CInterface::LoadHearList()
{
	CHAR pszFileName[MAX_PATH];
	sprintf(pszFileName, ".\\Data\\%s(%s).slt", g_szCharName, g_szServerName);

	FILE *fp = fopen(pszFileName, "rb");

	if ( !fp )
	{
		return;
	}

	CHAR pszLine[1024];
	ZeroMemory(pszLine, 1024);
	
	// 파일 마지막 검사.
	INT		nDat		= 0;
	INT		nLineCol	= 0;
	INT		nListCount	= 0;

	while ( feof( fp ) == 0 )
	{
		nDat = fgetc(fp);

		// 개행.
		if ( (nDat == '\r' && fgetc(fp) == '\n') || feof( fp ) != 0 )
		{
			CHAR* pszData = pszLine;
			CHAR* pszChk  = NULL;

			// 주석검사.
			while ( pszChk = strchr(pszData, '/') )
			{
				*pszChk = '\0';

				LPCHAT pstChat = new CHAT;
				pstChat->dwBackColor = RGB(0, 0, 0);
				pstChat->dwFontColor = RGB(255, 255, 255);
				sprintf(pstChat->pszChat, "%s", pszData);
				m_xHearList.Insert(pstChat);

				if ( m_xHearList.GetCount() > 9 )
				{
					fclose( fp );
					return;
				}

				pszData = ++pszChk;
			}

			nLineCol = 0;
			ZeroMemory(pszLine, 1024);
		}
		else
		{
			pszLine[nLineCol] = nDat;
			nLineCol++;
		}
	}

	fclose( fp );

}


VOID CInterface::SaveHearList()
{
	CHAR pszFileName[MAX_PATH];
	sprintf(pszFileName, ".\\Data\\%s(%s).slt", g_szCharName, g_szServerName);

	HANDLE	hFile;

	hFile = CreateFile(pszFileName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if ( hFile != INVALID_HANDLE_VALUE )
	{
		DWORD		dwWriteLen;

		CListNode < CHAT > *pNode;

		LPCHAT pstChat = NULL;

		const CHAR pszSlash[] = "/";

		for ( pNode = m_xHearList.GetHead(); pNode; pNode = pNode->GetNext() )
		{
			pstChat = pNode->GetData();

			if ( pstChat )
			{
				WriteFile(hFile, pstChat->pszChat, strlen(pstChat->pszChat), &dwWriteLen, NULL);
				WriteFile(hFile, pszSlash, 1, &dwWriteLen, NULL);
			}
		}

		CloseHandle(hFile);
	}
}






LONG CInterface::AltNumPushed(WPARAM wParam, LPARAM lParam)
{
	if ( !g_xGameProc.m_xGameMsgBox.IsActive() )
	{
		if ( m_xMacroList.GetCount() > (INT)wParam )
		{
			m_nSelMacroNum = (INT)wParam;
		}

		SetMacroList();
	}
	return 0L;
}


VOID CInterface::SetMacroList()
{
	CListNode < CHAT > *pNode;

	INT		nCnt;
	LPCHAT	pstChat = NULL;

	for ( pNode = m_xMacroList.GetHead(), nCnt = 0; pNode; pNode = pNode->GetNext(), nCnt++ )
	{
		pstChat = pNode->GetData();

		if ( nCnt == m_nSelMacroNum )
		{
			if ( pstChat )
			{
				SetFocus(g_xChatEditBox.GetSafehWnd());
				ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);
				SetWindowText(g_xChatEditBox.GetSafehWnd(), pstChat->pszChat);

				INT nLen = strlen(pstChat->pszChat);
				SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETSEL, nLen , nLen);
				g_xChatEditBox.SetHanguelMode();

				break;
			}
		}
	}
}


LPCHAT CInterface::FindMacroList(CHAR* pszMacro)
{
	CListNode < CHAT > *pNode;

	LPCHAT pstChat = NULL;

	for ( pNode = m_xMacroList.GetHead(); pNode; pNode = pNode->GetNext() )
	{
		pstChat = pNode->GetData();

		if ( pstChat )
		{
			if ( !strcmp(pstChat->pszChat, pszMacro) )
			{
				return pstChat;
			}			
		}
	}

	return NULL;
}


VOID CInterface::AddMacroList(CHAR* pszMacro)
{
	if ( FindMacroList(pszMacro) == NULL )
	{
		LPCHAT pstChat = NULL;
		pstChat = new CHAT;
		pstChat->dwBackColor = RGB(0, 0, 0);
		pstChat->dwFontColor = RGB(255, 255, 255);
		sprintf(pstChat->pszChat, "%s", pszMacro);
		m_xMacroList.Insert(pstChat);

		if ( m_xMacroList.GetCount() > 10 )
		{
			CListNode < CHAT > *pNode   = m_xMacroList.GetHead();
			LPCHAT				pstChat = pNode->GetData();
			if ( pstChat )
			{
				m_xMacroList.RemoveNode(pNode);
				SAFE_DELETE(pstChat);
			}
		}

		SaveMacroList();
	}
}


VOID CInterface::ShowMacroList()
{
	if ( m_xMacroList.GetCount() && !g_xGameProc.m_xGameMsgBox.IsActive() && (GetKeyState(VK_MENU) & 0x80) && (GetFocus() == g_xChatEditBox.GetSafehWnd()) )
	{
		CListNode < CHAT > *pNode;

		INT		nCnt;
		LPCHAT	pstChat = NULL;

		RECT rcList;
		SetRect(&rcList, 230, 356, 456, 520);
		
		D3DMATERIAL7 mtrl;
		D3DVECTOR	 vecTrans((FLOAT)rcList.left, (FLOAT)rcList.top, 0);
		D3DVECTOR	 vecScale((FLOAT)rcList.right-rcList.left, rcList.bottom-rcList.top, 1);

		D3DUtil_InitMaterial(mtrl, (FLOAT)50/255.0f, (FLOAT)50/255.0f, (FLOAT)50/255.0f);
		mtrl.diffuse.a = 180.0f/255.0f;
		g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

		for ( pNode = m_xMacroList.GetHead(), nCnt = 0; pNode; pNode = pNode->GetNext(), nCnt++ )
		{
			pstChat = pNode->GetData();

			if ( pstChat )
			{
				if ( nCnt == m_nSelMacroNum )
				{
					D3DUtil_InitMaterial(mtrl, (FLOAT)50/255.0f, (FLOAT)50/255.0f, (FLOAT)200/255.0f);
					mtrl.diffuse.a = 120.0f/255.0f;
					vecTrans = D3DVECTOR((FLOAT)rcList.left+1, (FLOAT)rcList.top+nCnt*16+2, 0);
					vecScale = D3DVECTOR((FLOAT)(rcList.right-rcList.left-2), 16.0f, 1);
 					g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
				}

				SIZE sizeLen = g_xMainWnd.GetStrLength(NULL, NULL, pstChat->pszChat);

				if ( sizeLen.cx <= 230 )
				{
					g_xMainWnd.PutsHan(NULL, rcList.left+4, rcList.top+nCnt*16+4, RGB( 10,  10,  10), RGB(0, 0, 0), pstChat->pszChat, NULL);
					g_xMainWnd.PutsHan(NULL, rcList.left+5, rcList.top+nCnt*16+5, RGB(255, 255, 255), RGB(0, 0, 0), pstChat->pszChat, NULL);
				}
				else
				{
					CHAR pszShow[64];
					memcpy(pszShow, pstChat->pszChat, 36);

					sprintf(&pszShow[36], "...");
					pszShow[63] = '\0';

					g_xMainWnd.PutsHan(NULL, rcList.left+4, rcList.top+nCnt*16+4, RGB( 10,  10,  10), RGB(0, 0, 0), pszShow, NULL);
					g_xMainWnd.PutsHan(NULL, rcList.left+5, rcList.top+nCnt*16+5, RGB(255, 255, 255), RGB(0, 0, 0), pszShow, NULL);
				}
			}
		}
	}
}


VOID CInterface::LoadMacroList()
{
	CHAR pszFileName[MAX_PATH];
	sprintf(pszFileName, ".\\Data\\%s(%s).mlt", g_szCharName, g_szServerName);

	FILE *fp = fopen(pszFileName, "rb");

	if ( !fp )
	{
		return;
	}

	CHAR pszLine[1024];
	ZeroMemory(pszLine, 1024);
	
	// 파일 마지막 검사.
	INT		nDat		= 0;
	INT		nLineCol	= 0;
	INT		nListCount	= 0;

	while ( feof( fp ) == 0 )
	{
		nDat = fgetc(fp);

		// 개행.
		if ( (nDat == '\r' && fgetc(fp) == '\n') || feof( fp ) != 0 )
		{
			CHAR* pszData = pszLine;
			CHAR* pszChk  = NULL;

			// 주석검사.
			while ( pszChk = strchr(pszData, '/') )
			{
				*pszChk = '\0';

				LPCHAT pstChat = new CHAT;
				pstChat->dwBackColor = RGB(0, 0, 0);
				pstChat->dwFontColor = RGB(255, 255, 255);
				sprintf(pstChat->pszChat, "%s", pszData);
				m_xMacroList.Insert(pstChat);

				if ( m_xMacroList.GetCount() > 9 )
				{
					fclose( fp );
					return;
				}

				pszData = ++pszChk;
			}

			nLineCol = 0;
			ZeroMemory(pszLine, 1024);
		}
		else
		{
			pszLine[nLineCol] = nDat;
			nLineCol++;
		}
	}

	fclose( fp );

}


VOID CInterface::SaveMacroList()
{
	CHAR pszFileName[MAX_PATH];
	sprintf(pszFileName, ".\\Data\\%s(%s).mlt", g_szCharName, g_szServerName);

	HANDLE	hFile;

	hFile = CreateFile(pszFileName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if ( hFile != INVALID_HANDLE_VALUE )
	{
		DWORD		dwWriteLen;

		CListNode < CHAT > *pNode;

		LPCHAT pstChat = NULL;

		const CHAR pszSlash[] = "/";

		for ( pNode = m_xMacroList.GetHead(); pNode; pNode = pNode->GetNext() )
		{
			pstChat = pNode->GetData();

			if ( pstChat )
			{
				WriteFile(hFile, pstChat->pszChat, strlen(pstChat->pszChat), &dwWriteLen, NULL);
				WriteFile(hFile, pszSlash, 1, &dwWriteLen, NULL);
			}
		}

		CloseHandle(hFile);
	}
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//



/******************************************************************************************************************

	함수명 : CInterface::RenderInterface()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : INT nLoopTime
	         POINT ptMousePos
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CInterface::RenderInterface(INT nLoopTime, POINT ptMousePos)
{
	INT nX, nY, nCnt, nLen;
	BOOL bShowMonInfo = FALSE, bDoor = FALSE, bShowActorInfo = FALSE;
/*
	// 영국 키보드 락업 지우기 기능
	if ( m_bLockRelease )
	{
		if ( g_dwCurrTime - m_dwLockRelease > 5000 )
		{
			g_xGameProc.m_xMyHero.m_bInputLock = FALSE;
			m_bLockRelease = FALSE;
		}
	}
*/
#ifdef _3rdINTERFACE
	INT	nIconImgIndex = 0;

/*	if ( g_xGameProc.m_pxSavedTargetActor && g_xGameProc.m_pxSavedTargetActor->m_stFeature.bGender == _GENDER_MON && !g_xGameProc.m_pxSavedTargetActor->m_bIsDead && 
		 MAKEWORD(g_xGameProc.m_pxSavedTargetActor->m_stFeature.bDress, g_xGameProc.m_pxSavedTargetActor->m_stFeature.bHair) != 127 &&
		 MAKEWORD(g_xGameProc.m_pxSavedTargetActor->m_stFeature.bDress, g_xGameProc.m_pxSavedTargetActor->m_stFeature.bHair) != 153)
	{
		CHAR			pszDivided[MAX_PATH];
		BOOL			bDraw = FALSE;
		WORD			wDress = MAKEWORD(g_xGameProc.m_pxSavedTargetActor->m_stFeature.bDress, g_xGameProc.m_pxSavedTargetActor->m_stFeature.bHair);

		if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(64))
		{
			g_xMainWnd.DrawWithImageForComp(291, 0, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
		}

		sprintf( pszDivided, g_xGameProc.m_pxSavedTargetActor->m_szName );
		RECT rcName = { 298, 17, 501, 32};
		g_xMainWnd.PutsHan(NULL, rcName , RGB(230, 230, 230), RGB(0, 0, 0), pszDivided);
		
		RECT	rcFrame;
		FLOAT fHPPercent = (FLOAT)((FLOAT)g_xGameProc.m_pxSavedTargetActor->m_bHPPercent/100);
		SetRect(&rcFrame, 0, 0, (INT)(198*fHPPercent), 5);

		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(65) )
		{
 			g_xMainWnd.DrawWithImageForComp(
							301, 8,
							&rcFrame,
							(WORD*)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
		}
	}

	
	if ( g_xGameProc.m_pxAutoSavedMagicActor && g_xGameProc.m_pxAutoSavedMagicActor->m_stFeature.bGender == _GENDER_MON && !g_xGameProc.m_pxAutoSavedMagicActor->m_bIsDead && 
		 MAKEWORD(g_xGameProc.m_pxAutoSavedMagicActor->m_stFeature.bDress, g_xGameProc.m_pxAutoSavedMagicActor->m_stFeature.bHair) != 127 &&
		 MAKEWORD(g_xGameProc.m_pxAutoSavedMagicActor->m_stFeature.bDress, g_xGameProc.m_pxAutoSavedMagicActor->m_stFeature.bHair) != 153)
	{
		CHAR			pszDivided[MAX_PATH];
		BOOL			bDraw = FALSE;
		WORD			wDress = MAKEWORD(g_xGameProc.m_pxAutoSavedMagicActor->m_stFeature.bDress, g_xGameProc.m_pxAutoSavedMagicActor->m_stFeature.bHair);

		if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(64))
		{
			g_xMainWnd.DrawWithImageForComp(291, 0, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
		}

		sprintf( pszDivided, g_xGameProc.m_pxAutoSavedMagicActor->m_szName );
		RECT rcName = { 298, 17, 501, 32};
		g_xMainWnd.PutsHan(NULL, rcName , RGB(230, 230, 230), RGB(0, 0, 0), pszDivided);
		
		RECT	rcFrame;
		FLOAT fHPPercent = (FLOAT)((FLOAT)g_xGameProc.m_pxAutoSavedMagicActor->m_bHPPercent/100);
		SetRect(&rcFrame, 0, 0, (INT)(198*fHPPercent), 5);

		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(65) )
		{
 			g_xMainWnd.DrawWithImageForComp(
							301, 8,
							&rcFrame,
							(WORD*)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
		}
	}
*/
	if ( m_nInformationMode == _INFO_CHAR && (g_xGameProc.m_pxExplainActor && g_xGameProc.m_pxExplainActor->m_stFeature.bGender == _GENDER_MAN || 
		g_xGameProc.m_pxExplainActor && g_xGameProc.m_pxExplainActor->m_stFeature.bGender == _GENDER_WOMAN) &&
		g_xGameProc.m_pxExplainActor->m_nIdentity != g_xGameProc.m_xMyHero.m_nIdentity )
	{
		if ( g_xGameProc.m_pxExplainActor->m_nFaceImageDate !=0 && m_bShowUserPic )
		{
			if ( g_xGameProc.m_pxExplainActor->m_bNeedLoadFameImg )
			{
				g_xGameProc.m_pxExplainActor->m_bLoadFaceImg = UpdateUserPicInfo( g_xGameProc.m_pxExplainActor->m_szName, g_xGameProc.m_pxExplainActor->m_nFaceImageDate );
				g_xGameProc.m_pxExplainActor->m_bNeedLoadFameImg = FALSE;
			}

			if ( g_xGameProc.m_pxExplainActor->m_bLoadFaceImg )
			{
				INT nOffSet = 0;

				if ( m_bIsMoving )
				{
					if ( m_bIsDown )
						nOffSet = 5;
					else
					{
						nOffSet = -5;
						if ( m_ptFrameLoc.y - 5 < m_rcCharFace.top )
						{
							INT ntset = 0;
							nOffSet = -2;
						}
					}

				}

				RECT rc = {m_rcMain.left+7, m_ptFrameLoc.y+40+nOffSet, m_rcMain.left+91, m_ptFrameLoc.y+136+nOffSet};
				g_xGameProc.m_pxExplainActor->m_hbmFaceImg.Draw(g_xMainWnd.GetBackBuffer(), &rc);
			}
			else
				DrawJobPic( g_xGameProc.m_pxExplainActor->m_bJob );
		}
		else
		{
			DrawJobPic( g_xGameProc.m_pxExplainActor->m_bJob );
		}

		bShowActorInfo = TRUE;
	}
	else if (m_nInformationMode == _INFO_CHAR )
	{
		if ( m_bIsThereUserFile == TRUE )				// 커스텀 이미지(캐릭터네임.fac)가 있나 체크
		{
			CHAR	szName[MAX_PATH];

			if ( !UpdateUserPicInfo(g_xGameProc.m_xMyHero.m_szName, g_xGameProc.m_xMyHero.m_nFaceImageDate) )
			{
				if ( g_xGameProc.m_xMyHero.m_nFaceImageDate != 0 )
				{
					// 파일 다운로드(타이머 사용)
					DWORD dwTemp = timeGetTime();

					if ( dwTemp - m_dwFaceImgTimer > 2000 )
					{
						m_dwFaceImgTimer = dwTemp;
						g_xClientSocket.RequestFaceImg(g_xGameProc.m_xMyHero.m_szName);
					}
				}
				else
				{
					m_bLoadUserFace = FALSE;
					m_bIsThereUserFile = FALSE;
				}
			}
			else
			{
				m_bLoadUserFace = TRUE;
				m_bIsThereUserFile = FALSE;
			}
		}

		if ( m_bLoadUserFace == FALSE )
		{
			switch (g_xGameProc.m_xMyHero.m_bJob)
			{
				case _JOB_JUNSA:
					{
						if (g_xGameProc.m_xMyHero.m_stFeature.bGender == _GENDER_MAN)
							nIconImgIndex = 650;
						else
							nIconImgIndex = 651;
					}
					break;
				case _JOB_SULSA:
					{
						if (g_xGameProc.m_xMyHero.m_stFeature.bGender == _GENDER_MAN)
							nIconImgIndex = 652;
						else
							nIconImgIndex = 653;
					}
					break;
				case _JOB_DOSA:
					{
						if (g_xGameProc.m_xMyHero.m_stFeature.bGender == _GENDER_MAN)
							nIconImgIndex = 654;
						else
							nIconImgIndex = 655;
					}
					break;
			}

			if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].NewSetIndex(nIconImgIndex) )
			{
				g_xMainWnd.DrawWithImageForComp(m_rcMain.left+6, m_ptFrameLoc.y+42, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shWidth, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shHeight,
												(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_pbCurrImage);
			}
		}
		else
		{
			INT nOffSet = 0;

			if ( m_bIsMoving )
			{
				if ( m_bIsDown )
					nOffSet = 5;
				else
				{
					nOffSet = -5;
					if ( m_ptFrameLoc.y - 5 < m_rcCharFace.top )
					{
						INT ntset = 0;
						nOffSet = -2;
					}
				}

			}

			if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(70))
			{
				g_xMainWnd.DrawWithImageForComp(m_rcCharFace.left + 6, m_ptFrameLoc.y + 40 + nOffSet, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
												(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
			}

			RECT rc = {m_rcMain.left+7, m_ptFrameLoc.y+40+nOffSet, m_rcMain.left+91, m_ptFrameLoc.y+136+nOffSet};
			g_xGameProc.m_xMyHero.m_hbmFaceImg.Draw(g_xMainWnd.GetBackBuffer(), &rc);
		}
	}

	if ( g_xGameProc.m_pxExplainActor && g_xGameProc.m_pxExplainActor->m_stFeature.bGender == _GENDER_MON && !g_xGameProc.m_pxExplainActor->m_bIsDead && 
		 MAKEWORD(g_xGameProc.m_pxExplainActor->m_stFeature.bDress, g_xGameProc.m_pxExplainActor->m_stFeature.bHair) != 127 &&
		 MAKEWORD(g_xGameProc.m_pxExplainActor->m_stFeature.bDress, g_xGameProc.m_pxExplainActor->m_stFeature.bHair) != 153)
		 // 살아있는 몬스터를 마우스가 가르키면 몬스터 종보를 보여준다.
	{
		CHAR			pszDivided[MAX_PATH];
		BOOL			bDraw = FALSE;
		WORD			wDress = MAKEWORD(g_xGameProc.m_pxExplainActor->m_stFeature.bDress, g_xGameProc.m_pxExplainActor->m_stFeature.bHair);

//		if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(64))
//		{
//			g_xMainWnd.DrawWithImageForComp(291, 0, 
//											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
//											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
//											(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
///		}

//		sprintf( pszDivided, g_xGameProc.m_pxExplainActor->m_szName );
//		RECT rcName = { 298, 17, 501, 32};
//		g_xMainWnd.PutsHan(NULL, rcName , RGB(230, 230, 230), RGB(0, 0, 0), pszDivided);
		
//		RECT	rcFrame;
//		FLOAT fHPPercent = (FLOAT)((FLOAT)g_xGameProc.m_pxExplainActor->m_bHPPercent/100);
//		SetRect(&rcFrame, 0, 0, (INT)(198*fHPPercent), 5);

//		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(65) )
//		{
 //			g_xMainWnd.DrawWithImageForComp(
//							301, 8,
//							&rcFrame,
//							(WORD*)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
//		}

		// 몬스터 사진 그리기
		if ( wDress < 2000 )
			nIconImgIndex = g_xGameProc.m_pxExplainActor->m_stFeature.bDress;
		else
			nIconImgIndex = wDress;

		if ( wDress == 530 || wDress == 531 || wDress == 532 || wDress == 533 || wDress == 534 || wDress == 535 || wDress == 536 || wDress == 537 || wDress == 538 )
		{
			bDoor = TRUE;
			nIconImgIndex = wDress;
		}

		if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_MONSMALL].NewSetIndex(nIconImgIndex))
		{
			g_xMainWnd.DrawWithImageForComp(m_rcMain.left+6, m_ptFrameLoc.y+42, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_MONSMALL].m_lpstNewCurrWilImageInfo->shWidth, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_MONSMALL].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_MONSMALL].m_pbCurrImage);
			bDraw = TRUE;
		}

		// 몬스터 사진 그리기
	}

	if ( !m_bViewMiniMap )
	{
		// 맵이름 좌표
		if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(144))
		{
			g_xMainWnd.DrawWithImageForComp(668, 1, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);

			RECT rcName = { 674, 9, 796, 24 };
			CHAR szMap[MAX_PATH];
			sprintf(szMap, "%s", g_xGameProc.m_szMapName);
			g_xMainWnd.PutsHan(NULL, rcName, RGB(255, 255, 255), RGB(0, 0, 0), szMap, NULL);

			rcName.top += 17;
			rcName.bottom += 17;
			sprintf(szMap, "%d, %d", g_xGameProc.m_xMyHero.m_nPosX, g_xGameProc.m_xMyHero.m_nPosY);
			g_xMainWnd.PutsHan(NULL, rcName, RGB(255, 255, 255), RGB(0, 0, 0), szMap, NULL);
		}
	}

	if ( m_nInformationMode == _INFO_CHAR )
	{
		if ( m_bIsMoving )
		{
			if ( m_bIsDown )
			{
				m_ptFrameLoc.y += 5;

				if ( m_ptFrameLoc.y > m_rcLogo.top )
				{
					m_ptFrameLoc.y = m_rcLogo.top;
					m_bIsDown = FALSE;
					m_nInformationMode = !m_nInformationMode;
				}
			}
			else
			{
				m_ptFrameLoc.y -= 5;

				if ( m_ptFrameLoc.y < m_rcCharFace.top )
				{
					m_ptFrameLoc.y = m_rcCharFace.top;
					m_bIsMoving = FALSE;
				}
			}
		}

		if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(67))
		{
			g_xMainWnd.DrawWithImageForComp(m_rcCharFace.left, m_ptFrameLoc.y, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
		}
	}
	else
	{
		if ( m_bIsMoving )
		{
			if ( m_bIsDown )
			{
				m_ptFrameLoc.y += 5;

				if ( m_ptFrameLoc.y >= 600 )
				{
					m_ptFrameLoc.y = 600;
					m_bIsDown = FALSE;
					m_nInformationMode = !m_nInformationMode;
				}
			}
			else
			{
				m_ptFrameLoc.y -= 5;

				if ( m_ptFrameLoc.y < m_rcLogo.top )
				{
					m_ptFrameLoc.y = m_rcLogo.top;
					m_bIsMoving = FALSE;
				}
			}
		}

		if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(70))
		{
			g_xMainWnd.DrawWithImageForComp(m_rcCharFace.left + 6, m_ptFrameLoc.y + 41, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
		}

		if ( g_dwCurrTime - m_dwLogoTimer > 300 )
		{
			m_nLogoIdx++;
			m_dwLogoTimer = g_dwCurrTime;

			if ( m_nLogoIdx > 9 )
				m_nLogoIdx = 0;
		}

		INT nImgIdx = 320 + m_nLogoIdx;

		if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].NewSetIndex(nImgIdx))
		{
			g_xMainWnd.DrawWithImageForComp(m_rcLogo.left + 8, m_ptFrameLoc.y + 44, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shWidth, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_pbCurrImage);
		}

		if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(68))
		{
			g_xMainWnd.DrawWithImageForComp(m_rcLogo.left, m_ptFrameLoc.y, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
		}

	}

	if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(_WNDIMGIDX_MAIN))
	{
		g_xMainWnd.DrawWithImageForComp(m_rcMain.left+94, m_rcMain.top, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
	}
	
	for ( nCnt = _MAX_INTER_BTN-1; nCnt >= 0; nCnt--)
	{
		m_xInterBtn[nCnt].ShowGameBtn();
	}

/*
	INT nFlagIdx = 1689 + g_xGameProc.m_xMyHero.m_bGuildFlag;

	if ( m_pxInterImg->NewSetIndex(nFlagIdx) )
	{
		WORD wClr = 0XFFFF;
		wClr = g_xMainWnd.ConvertColor24To16(RGB(g_xGameProc.m_xMyHero.m_bFlagColorB, 
												 g_xGameProc.m_xMyHero.m_bFlagColorG,
												 g_xGameProc.m_xMyHero.m_bFlagColorR));
 		g_xMainWnd.DrawWithABlendCompDataWithBackBufferEx(m_rcMain.left-10, m_rcMain.top-107,
														  m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth,
														  m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight,
														  (WORD*)m_pxInterImg->m_pbCurrImage, _CLIP_WIDTH, 600, wClr, 0XFFFF, 25);
	}
*/
	if ( m_bViewMiniMap )
	{
		m_xMiniMap.MoveMiniMap(g_xGameProc.m_xMyHero.m_nPosX, g_xGameProc.m_xMyHero.m_nPosY);
		m_xMiniMap.RenderMiniMap(nLoopTime);
	}

	ShowGroupMember();

	ShowSystemChat();
	ShowNormalChat();

	if ( m_bHasNewMessage ==  TRUE )
	{
		m_xInterBtnofNewMessage.ShowGameBtn();
		m_xInterBtnofNewMessage.ChangeRect(752, 500);

		if ( g_dwCurrTime - m_dwNewFliker > 500 || m_dwNewFliker == 0 )
		{
			m_bNewFliker = !m_bNewFliker;
			m_dwNewFliker = g_dwCurrTime;
		}

		if ( m_bNewFliker )
		{
			if ( m_xInterBtnofNewMessage.m_bBtnState == _BTN_STATE_FOCUS )
			{
				m_xInterBtnofNewMessage.ResetGameBtn(332, 331, 332);
				m_xInterBtnofNewMessage.m_bBtnState = _BTN_STATE_FOCUS;
			}
			else
			{
				m_xInterBtnofNewMessage.ResetGameBtn(332, 331, 332);
			}
		}
		else
		{
			if ( m_xInterBtnofNewMessage.m_bBtnState == _BTN_STATE_FOCUS )
			{
				m_xInterBtnofNewMessage.ResetGameBtn(330, 331, 330);
				m_xInterBtnofNewMessage.m_bBtnState = _BTN_STATE_FOCUS;
			}
			else
			{
				m_xInterBtnofNewMessage.ResetGameBtn(330, 331, 330);
			}

		}
	}

	ShowGameStatus();

	ShowWndList();

	if ( g_xGameProc.m_bDrawEventMsg )
	{
		g_xGameProc.RenderEventMessage();
	}

	if ( m_szWarningOrigin[0] != NULL )
	{
		// 뒷판 그리기.
		RECT rc = {173, 30, 628, 19};
		INT	 nWidth, nHeight;
		nWidth = 455;
		nHeight = 20;

		D3DVECTOR	 vecTrans((FLOAT)(rc.left), (FLOAT)(rc.top), 0);
		D3DVECTOR	 vecScale((FLOAT)(nWidth), (FLOAT)(nHeight), 1);
		D3DMATERIAL7 mtrl;

		D3DUtil_InitMaterial(mtrl, (FLOAT)30/255.0f, (FLOAT)30/255.0f, (FLOAT)30/255.0f);
		mtrl.diffuse.a = 150.0f/255.0f;
		g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

		if ( m_nMoveOffset < 100 )
		{
			m_nMoveOffset += 2;
			SetRect(&m_rcWarning1, 613 - m_nMoveOffset, 33, 613, 48);
		}
		else
		{
			m_nMoveOffset += 2;

			INT nLen = strlen(m_szWarning);

			if ( m_nMoveOffset > 430 && (nLen > 1 && !( nLen == 2 && m_szWarning[0] < 0) ) )
			{
				CHAR szTemp[MAX_PATH], szFirst[2];
				SIZE sizeLen;

				if ( m_szWarning[0] < 0 )
				{
					strncpy(szFirst, m_szWarning, 2);
					szFirst[2] = 0;
					sizeLen = g_xMainWnd.GetStrLength(NULL, g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 10, 0, FW_BOLD), szFirst);					
					
					strcpy( &szTemp[0], &m_szWarning[2] );
					m_nMoveOffset -= sizeLen.cx;
					SetRect(&m_rcWarning1, 613 - m_nMoveOffset, 33, 613, 48);
				}
				else
				{
					strncpy(szFirst, m_szWarning, 1);
					szFirst[1] = 0;
					sizeLen = g_xMainWnd.GetStrLength(NULL, g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 10, 0, FW_BOLD), szFirst);
					strcpy( &szTemp[0], &m_szWarning[1] );
					m_nMoveOffset -= sizeLen.cx;
					SetRect(&m_rcWarning1, 613 - m_nMoveOffset, 33, 613, 48);
				}
				
				sprintf( m_szWarning, szTemp );
			}
			else
			{
				SetRect(&m_rcWarning1, 613 - m_nMoveOffset, 33, 613, 48);
			}

			if ( nLen <= 1 || ( nLen == 2 && m_szWarning[0] < 0) )
			{
				m_nMoveOffset = 0;
				sprintf( m_szWarning, m_szWarningOrigin );
				SetRect(&m_rcWarning1, 613 - m_nMoveOffset, 33, 613, 48);

				m_nWarningCnt++;
			}
		}

		g_xMainWnd.PutsHanLeft(NULL, m_rcWarning1, RGB(230, 230, 230), RGB(0, 0, 0), m_szWarning, g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 10, 0, FW_BOLD));

		if ( m_nWarningCnt == 2 )
		{
			sprintf( m_szWarning, "" );
			sprintf( m_szWarningOrigin, "" );
			m_nWarningCnt = 0;
		}

		if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(327))
		{
			g_xMainWnd.DrawWithImageForComp(173, 24, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
		}

	}

	// 마우스 아이템.
	if ( m_stCommonItem.bSetted && !m_stCommonItem.bIsHideItem )
	{
		nX = ptMousePos.x - _INVENTORY_CELL_WIDTH /2;
		nY = ptMousePos.y - _INVENTORY_CELL_HEIGHT/2;
		m_stCommonItem.xItem.DrawItem(nX, nY);
	}

	// 클라이언트메시지(왼쪽상단).
	m_xClientSysMsg.ShowSysMsg(nLoopTime, 30, 340);

	ShowHearList();
	ShowMacroList();

//	ShowMagicKey();

#else //_NEWINTERFACE
	// 메인인터페이스.
	INT	nIconImgIndex = 0;

	if ( m_bIsLargeChat == FALSE)
	{
		if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(1490))
		{
			g_xMainWnd.DrawWithImageForComp(m_rcMain.left+534, m_rcMain.top+20, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
		}
		if (m_nInformationMode == _INFO_CHAR )
		{
			if ( m_bIsThereUserFile == TRUE )				// 커스텀 이미지(캐릭터네임.fac)가 있나 체크
			{
				CHAR	szName[MAX_PATH];

				if ( !UpdateUserPicInfo(g_xGameProc.m_xMyHero.m_szName, g_xGameProc.m_xMyHero.m_nFaceImageDate) )
				{
					if ( g_xGameProc.m_xMyHero.m_nFaceImageDate != 0 )
					{
						// 파일 다운로드(타이머 사용)
						DWORD dwTemp = timeGetTime();

						if ( dwTemp - m_dwFaceImgTimer > 2000 )
						{
							m_dwFaceImgTimer = dwTemp;
							g_xClientSocket.RequestFaceImg(g_xGameProc.m_xMyHero.m_szName);
						}
					}
					else
					{
						m_bLoadUserFace = FALSE;
						m_bIsThereUserFile = FALSE;
					}
				}
				else
				{
					m_bLoadUserFace = TRUE;
					m_bIsThereUserFile = FALSE;
				}
			}

			if ( m_bLoadUserFace == FALSE )
			{
				switch (g_xGameProc.m_xMyHero.m_bJob)
				{
					case _JOB_JUNSA:
						{
							if (g_xGameProc.m_xMyHero.m_stFeature.bGender == _GENDER_MAN)
								nIconImgIndex = 650;
							else
								nIconImgIndex = 651;
						}
						break;
					case _JOB_SULSA:
						{
							if (g_xGameProc.m_xMyHero.m_stFeature.bGender == _GENDER_MAN)
								nIconImgIndex = 652;
							else
								nIconImgIndex = 653;
						}
						break;
					case _JOB_DOSA:
						{
							if (g_xGameProc.m_xMyHero.m_stFeature.bGender == _GENDER_MAN)
								nIconImgIndex = 654;
							else
								nIconImgIndex = 655;
						}
						break;
				}

				if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].NewSetIndex(nIconImgIndex) )
				{
					g_xMainWnd.DrawWithImageForComp(m_rcMain.left+534, m_rcMain.top+20, 
													g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shWidth, 
													g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shHeight,
													(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_pbCurrImage);
				}
			}
			else
			{
				RECT rc = {m_rcMain.left+534, m_rcMain.top+20, m_rcMain.left+616, m_rcMain.top+114};
				g_xGameProc.m_xMyHero.m_hbmFaceImg.Draw(g_xMainWnd.GetBackBuffer(), &rc);
			}
		}		
		else if ( m_bViewMiniMapInMain == TRUE )
		{
			m_xMiniMap.MoveMiniMap(g_xGameProc.m_xMyHero.m_nPosX, g_xGameProc.m_xMyHero.m_nPosY);
			m_xMiniMap.RenderMinimapInMain(nLoopTime);
		}

//////////////////////////////////////////////////////////////
		if ( g_xGameProc.m_pxExplainActor && g_xGameProc.m_pxExplainActor->m_stFeature.bGender == _GENDER_MON && !g_xGameProc.m_pxExplainActor->m_bIsDead && 
			 MAKEWORD(g_xGameProc.m_pxExplainActor->m_stFeature.bDress, g_xGameProc.m_pxExplainActor->m_stFeature.bHair) != 127 &&
			 MAKEWORD(g_xGameProc.m_pxExplainActor->m_stFeature.bDress, g_xGameProc.m_pxExplainActor->m_stFeature.bHair) != 153)
			 // 살아있는 몬스터를 마우스가 가르키면 몬스터 종보를 보여준다.
		{
			CHAR			pszDivided[MAX_PATH];
			BOOL			bDraw = FALSE;
			WORD			wDress = MAKEWORD(g_xGameProc.m_pxExplainActor->m_stFeature.bDress, g_xGameProc.m_pxExplainActor->m_stFeature.bHair);

			if ( wDress < 2000 )
				nIconImgIndex = g_xGameProc.m_pxExplainActor->m_stFeature.bDress;
			else
				nIconImgIndex = wDress;

			if ( wDress == 530 || wDress == 531 || wDress == 532 || wDress == 533 || wDress == 534 || wDress == 535 || wDress == 536 || wDress == 537 || wDress == 538 )
			{
				bDoor = TRUE;
				nIconImgIndex = wDress;
			}

			if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_MONSMALL].NewSetIndex(nIconImgIndex))
			{
				g_xMainWnd.DrawWithImageForComp(m_rcMain.left+534, m_rcMain.top+20, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_MONSMALL].m_lpstNewCurrWilImageInfo->shWidth, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_MONSMALL].m_lpstNewCurrWilImageInfo->shHeight,
												(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_MONSMALL].m_pbCurrImage);
				bDraw = TRUE;
			}

			if ( bDraw == FALSE )
			{
				if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_MONSMALL].NewSetIndex(1999))
				{
					g_xMainWnd.DrawWithImageForComp(m_rcMain.left+534, m_rcMain.top+20, 
													g_xGameProc.m_xImage.m_xImageList[_IMAGE_MONSMALL].m_lpstNewCurrWilImageInfo->shWidth, 
													g_xGameProc.m_xImage.m_xImageList[_IMAGE_MONSMALL].m_lpstNewCurrWilImageInfo->shHeight,
													(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_MONSMALL].m_pbCurrImage);
				}
			}

			RECT  rcFrame;

			if (g_xGameProc.m_pxExplainActor->m_stMonType.nDead == 1)
				nIconImgIndex = 635;
			else
				nIconImgIndex = 634;

 			if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].NewSetIndex(nIconImgIndex) && !bDoor )
			{
 				g_xMainWnd.DrawWithImageForComp(
								m_rcMain.left+595,m_rcMain.top+94,
								g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shWidth,					
								g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shHeight,
								(WORD*)g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_pbCurrImage);
			}

			bShowMonInfo = TRUE;
		}
		else if ( (g_xGameProc.m_pxExplainActor && g_xGameProc.m_pxExplainActor->m_stFeature.bGender == _GENDER_MAN || 
			g_xGameProc.m_pxExplainActor && g_xGameProc.m_pxExplainActor->m_stFeature.bGender == _GENDER_WOMAN) &&
			g_xGameProc.m_pxExplainActor->m_nIdentity != g_xGameProc.m_xMyHero.m_nIdentity )
		{
			if ( g_xGameProc.m_pxExplainActor->m_nFaceImageDate !=0 && m_bShowUserPic )
			{
				if ( g_xGameProc.m_pxExplainActor->m_bNeedLoadFameImg )
				{
					g_xGameProc.m_pxExplainActor->m_bLoadFaceImg = UpdateUserPicInfo( g_xGameProc.m_pxExplainActor->m_szName, g_xGameProc.m_pxExplainActor->m_nFaceImageDate );
					g_xGameProc.m_pxExplainActor->m_bNeedLoadFameImg = FALSE;
				}

				if ( g_xGameProc.m_pxExplainActor->m_bLoadFaceImg )
				{
					RECT rc = {m_rcMain.left+534, m_rcMain.top+13, m_rcMain.left+618, m_rcMain.top+116};
					g_xGameProc.m_pxExplainActor->m_hbmFaceImg.Draw(g_xMainWnd.GetBackBuffer(), &rc);
				}
				else
					DrawJobPic( g_xGameProc.m_pxExplainActor->m_bJob );
			}
			else
			{
				DrawJobPic( g_xGameProc.m_pxExplainActor->m_bJob );
			}

			bShowActorInfo = TRUE;
		}
	}

	if (m_bIsLargeChat == TRUE)
	{
		// 뒷판 그리기.
		RECT rc = {185, 317, 600, 500};
		INT	 nWidth, nHeight;
		nWidth = 433;
		nHeight = 213;

		D3DVECTOR	 vecTrans((FLOAT)(rc.left), (FLOAT)(rc.top), 0);
		D3DVECTOR	 vecScale((FLOAT)(nWidth), (FLOAT)(nHeight), 1);
		D3DMATERIAL7 mtrl;

		D3DUtil_InitMaterial(mtrl, (FLOAT)30/255.0f, (FLOAT)30/255.0f, (FLOAT)30/255.0f);
		mtrl.diffuse.a = 150.0f/255.0f;
		g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
	}

	if ( m_pxInterImg->NewSetIndex(1160) )
	{
 		g_xMainWnd.DrawWithImageForCompClipRgn(m_rcMain.left, m_rcMain.top,	
												m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth,
												m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight,
											   (WORD*)m_pxInterImg->m_pbCurrImage, _CLIP_WIDTH, 600);
	}

	if (m_bIsLargeChat == TRUE)
	{
		if ( m_pxInterImg->NewSetIndex(1162) )
		{
 			g_xMainWnd.DrawWithImageForCompClipRgn(m_rcMain.left+178, m_rcMain.top-186,	
													m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth,
													m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight,
												   (WORD*)m_pxInterImg->m_pbCurrImage, _CLIP_WIDTH, 600);
		}
	}
	else
	{
		if ( m_pxInterImg->NewSetIndex(1161) )
		{
 			g_xMainWnd.DrawWithImageForCompClipRgn(m_rcMain.left+178, m_rcMain.top-19,	
													m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth,
													m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight,
												   (WORD*)m_pxInterImg->m_pbCurrImage, _CLIP_WIDTH, 600);
		}
	}


	if (m_bIsLargeChat == TRUE)
		ShowLargeChatList();
	else
		ShowChatList();

	ShowGameStatus();

	for ( nCnt = _MAX_INTER_BTN - 1; nCnt >= 0; nCnt--)
	{
		m_xInterBtn[nCnt].ShowGameBtn();
	}

	INT nFlagIdx = 1689 + g_xGameProc.m_xMyHero.m_bGuildFlag;

//	if ( nFlagIdx > 0 && nFlagIdx < 13 )
//	{
		if ( m_pxInterImg->NewSetIndex(nFlagIdx) )
		{
			WORD wClr = 0XFFFF;
			wClr = g_xMainWnd.ConvertColor24To16(RGB(g_xGameProc.m_xMyHero.m_bFlagColorB, 
													 g_xGameProc.m_xMyHero.m_bFlagColorG,
													 g_xGameProc.m_xMyHero.m_bFlagColorR));
 			g_xMainWnd.DrawWithABlendCompDataWithBackBufferEx(m_rcMain.left-10, m_rcMain.top-107,
															  m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth,
															  m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight,
															  (WORD*)m_pxInterImg->m_pbCurrImage, _CLIP_WIDTH, 600, wClr, 0XFFFF, 25);
		}
//	}
	// 스크롤바.
	for ( nCnt = nMaxBtn -1; nCnt >= 0; nCnt--)
	{
		m_xInterBtn[nCnt].ShowGameBtn();
	}

//	if ( m_bHasSiege == TRUE )
//		m_xInterBtnofSiege.ShowGameBtn();

	if ( m_bHasNewMessage ==  TRUE )
	{
		m_xInterBtnofNewMessage.ShowGameBtn();

		if ( m_dwNewFliker - g_dwCurrTime > 1000 || m_dwNewFliker == 0 )
		{
			m_bNewFliker = !m_bNewFliker;
			m_dwNewFliker = g_dwCurrTime;
		}

		if ( m_bNewFliker )
		{
			if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(332))
			{
				g_xMainWnd.DrawWithImageForComp(0, 20, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
												(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
			}
		}
		else
		{
		}
	}

	if ( PtInRect(&m_rcInfoModeChange, g_xGameProc.m_ptMousePos) && m_bIsLargeChat == FALSE )
	{
		m_xInterBtnFaceImgUp.ShowGameBtn();
	}

	if ( m_bViewMiniMap )
	{
		m_xMiniMap.MoveMiniMap(g_xGameProc.m_xMyHero.m_nPosX, g_xGameProc.m_xMyHero.m_nPosY);
		m_xMiniMap.RenderMiniMap(nLoopTime);
	}

	if ( bShowMonInfo )
	{
		RECT	rcFrame;
		FLOAT fHPPercent = (FLOAT)((FLOAT)g_xGameProc.m_pxExplainActor->m_bHPPercent/100);
		SetRect(&rcFrame, 0, 0, (INT)(84*fHPPercent), 6);

		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].NewSetIndex(660) )
		{
 			g_xMainWnd.DrawWithImageForComp(
							m_rcMain.left+533, m_rcMain.top+116,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shWidth,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shHeight,
							(WORD*)g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_pbCurrImage);
		}
		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].NewSetIndex(661) )
		{
 			g_xMainWnd.DrawWithImageForComp(
							m_rcMain.left+534, m_rcMain.top+117,
							&rcFrame,
							(WORD*)g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_pbCurrImage);
		}
	}
/*
	if ( bShowActorInfo ) 
	{
		RECT	rcFrame;
		FLOAT fHPPercent = (FLOAT)((FLOAT)g_xGameProc.m_pxExplainActor->m_bHPPercent/100);
		SetRect(&rcFrame, 0, 0, (INT)(84*fHPPercent), 6);

		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].NewSetIndex(660) )
		{
 			g_xMainWnd.DrawWithImageForComp(
							m_rcMain.left+533, m_rcMain.top+116,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shWidth,					
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shHeight,
							(WORD*)g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_pbCurrImage);
		}
		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].NewSetIndex(661) )
		{
 			g_xMainWnd.DrawWithImageForComp(
							m_rcMain.left+534, m_rcMain.top+117,
							&rcFrame,
							(WORD*)g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_pbCurrImage);
		}
	}
*/
	ShowWndList();

	// 마우스 아이템.
	if ( m_stCommonItem.bSetted && !m_stCommonItem.bIsHideItem )
	{
		nX = ptMousePos.x - _INVENTORY_CELL_WIDTH /2;
		nY = ptMousePos.y - _INVENTORY_CELL_HEIGHT/2;
		m_stCommonItem.xItem.DrawItem(nX, nY);
	}

	m_xClientSysMsg.ShowSysMsg(nLoopTime, 30, 340);

	ShowHearList();
	ShowMacroList();

	ShowMagicKey();

	if ( m_xGameOverWnd.GetGameWndActive() )
	{
		m_xGameOverWnd.ShowGameOver();
	}

	if ( bShowMonInfo && !bDoor)
	{
		// 몬스터 상세 정보
		CHAR			pszDivided[MAX_PATH*2];
		INT				nLineCnt;
		D3DMATERIAL7	mtrl;
		RECT			rcFrame;
		INT				nIconImgIndex = -1;
		INT				nOffsetX = 615, nOffsetY = 487;

		SetRect(&rcFrame, nOffsetX, nOffsetY, nOffsetX+105, nOffsetY+85);
		D3DVECTOR	vecTrans((FLOAT)nOffsetX, (FLOAT)nOffsetY, 0);
		D3DVECTOR	vecScale((FLOAT)(rcFrame.right-rcFrame.left), (FLOAT)(rcFrame.bottom-rcFrame.top), 1);
		D3DUtil_InitMaterial(mtrl, (FLOAT)50/255.0f, (FLOAT)50/255.0f, (FLOAT)50/255.0f);
		mtrl.diffuse.a = 230.0f/255.0f;
		g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
		g_xMainWnd.DrawWithGDI(&rcFrame, NULL, RGB(120, 120, 120), 1);

		INT nSX, nSY;

		nSX = 620;
		nSY = 482;

		if ( g_xGameProc.m_pxExplainActor->m_stMonType.stMonStats.szSpeed != -1 && 
			 g_xGameProc.m_pxExplainActor->m_stMonType.nDead != -1 && 
			 g_xGameProc.m_pxExplainActor->m_stMonType.nTaiming != -1 )
		{
			nSY += 8;

			if (g_xGameProc.m_pxExplainActor->m_stMonType.nTaiming == 0)
				nIconImgIndex = 632;
			else
				nIconImgIndex = 631;

			if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].NewSetIndex(nIconImgIndex))
			{
				g_xMainWnd.DrawWithImageForComp(nSX, nSY, g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shWidth, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shHeight,
												(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_pbCurrImage);
			}

			if (g_xGameProc.m_pxExplainActor->m_stMonType.stMonStats.szMcType != 0)
			{
				nIconImgIndex = 599 + g_xGameProc.m_pxExplainActor->m_stMonType.stMonStats.szMcType;
				nSX += 21;
				if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].NewSetIndex(nIconImgIndex))
				{
					g_xMainWnd.DrawWithImageForComp(nSX, nSY, g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shWidth, 
													g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shHeight,
													(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_pbCurrImage);
				}
			}

			INT	nIdx = 0;

			if(g_xGameProc.m_pxExplainActor->m_stMonType.stMonStats.szAc >= 5)
				nIdx = 0;
			else if(g_xGameProc.m_pxExplainActor->m_stMonType.stMonStats.szAc <= -5)
				nIdx = 10;
			else
				nIdx = abs(g_xGameProc.m_pxExplainActor->m_stMonType.stMonStats.szAc - 5);

			CHAR		szTemp[MAX_PATH];

			nSX += 21;
			nIconImgIndex = 620+g_xGameProc.m_pxExplainActor->m_stMonType.stMonStats.szSpeed;
			if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].NewSetIndex(nIconImgIndex))
			{
				g_xMainWnd.DrawWithImageForComp(nSX, nSY, g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shWidth, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shHeight,
												(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_pbCurrImage);
			}
/*
			nSX += 21;
			if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].NewSetIndex(630))
			{
				g_xMainWnd.DrawWithImageForComp(nSX, nSY, g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shWidth, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shHeight,
												(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_pbCurrImage);
			}
*/
//			sprintf(szTemp, "%d%", 10 - nIdx);
//			g_xMainWnd.PutsHan(NULL, nSX+22, nSY+5, RGB(230, 230, 230), RGB(0, 0, 0), szTemp);

			nSX = 620;

			INT		nOrder[7]={0,1,2,3,4,5,6};
			CHAR	szTempBuf[7];
			for (INT nCount=0; nCount<7; nCount++)
				szTempBuf[nCount] = g_xGameProc.m_pxExplainActor->m_stMonType.stMonStats.szMac[nCount];

			for (INT nX=6; nX>=0; nX--)
			{
				for (INT nY=nX; nY>0; nY--)
				{
					if (szTempBuf[nY] > szTempBuf[nY-1])
					{
						INT nTemp = szTempBuf[nY-1];
						szTempBuf[nY-1] = szTempBuf[nY];
						szTempBuf[nY] = nTemp;

						INT nTempIdx = nOrder[nY-1];
						nOrder[nY-1] = nOrder[nY];
						nOrder[nY] = nTempIdx;
					}
				}
			}

			for (nX=0; nX<7; nX++)
			{
				if (szTempBuf[nX] == 0)
				{
					INT nTemp = szTempBuf[nX];
					INT nTempIdx = nOrder[nX];
					for (nY=nX; nY<7; nY++)
					{
						if (szTempBuf[nY] != 0)
						{
							szTempBuf[nX] = szTempBuf[nY];
							szTempBuf[nY] = nTemp;
							nOrder[nX] = nOrder[nY];
							nOrder[nY] = nTempIdx;
							break;
						}
					}
				}
			}

			for (int nI=0; nI<7; nI++)
			{
				INT nIdx = nOrder[nI];
				if (g_xGameProc.m_pxExplainActor->m_stMonType.stMonStats.szMac[nIdx] == 0)
					continue;

				if (g_xGameProc.m_pxExplainActor->m_stMonType.stMonStats.szMac[nIdx] >= 0)
					sprintf(szTemp, " +%d%", g_xGameProc.m_pxExplainActor->m_stMonType.stMonStats.szMac[nIdx]);
				else
					sprintf(szTemp, " %d%", g_xGameProc.m_pxExplainActor->m_stMonType.stMonStats.szMac[nIdx]);

				if ( (nI%3) == 0 )
					nSY += 20;
				else if ( (nI%3) == 1 )
					nSX += 32;
				else
					nSX += 32;

				if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].NewSetIndex(610+nIdx))
				{
					g_xMainWnd.DrawWithImageForComp(nSX, nSY, g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shWidth, 
													g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shHeight,
													(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_pbCurrImage);
				}
				g_xMainWnd.PutsHan(NULL, nSX+15, nSY+5, RGB(230, 230, 230), RGB(0, 0, 0), szTemp);
				if ( (nI%3) == 2 )
					nSX -= 64;
			}
		}
	}
			
//	g_xMainWnd.DrawWithGDI(&m_rcInfoModeChange, NULL, RGB(160, 80, 80), 1);

#endif
}



/******************************************************************************************************************

	함수명 : CInterface::ShowBeltItem()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CInterface::ShowBeltItem()
{
	INT nX, nY;

	if ( m_bBeltState == _BELT_STATE_UP )
	{
		m_shBeltHeight += 10;

		if ( m_shBeltHeight >= 46 )	
		{
			m_shBeltHeight = 46;
		}
	}
	else if ( m_bBeltState == _BELT_STATE_DOWN )
	{
		m_shBeltHeight -= 10;
		if ( m_shBeltHeight <= 0 )
		{
			m_shBeltHeight = 0;
			m_bBeltState   = _BELT_STATE_STAY;
		}
	}

	if ( m_bBeltState != _BELT_STATE_STAY )
	{
		if ( m_pxInterImg->NewSetIndex(_IMGIDX_BELT) )
		{
 			g_xMainWnd.DrawWithImageForCompClipRgn(275, 478-m_shBeltHeight,
												   m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth,
												   m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight,
												   (WORD*)m_pxInterImg->m_pbCurrImage, _CLIP_WIDTH, 600);
			// 벨트 아이템 그리기.
			for ( INT nCnt = 0; nCnt < _MAX_BELT_ITEM; nCnt++ )
			{
				if ( m_stBeltItem[nCnt].bSetted )
				{
					nX = m_rcBeltCell[nCnt].left + 2;
					nY = m_rcBeltCell[nCnt].top + 5 + 46 - m_shBeltHeight;

					m_stBeltItem[nCnt].xItem.DrawItem(nX, nY);
				}
			}
			}
	}
}



/******************************************************************************************************************

	함수명 : CInterface::ShowGameStatus()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CInterface::ShowGameStatus()
{
	FLOAT	fMyHPRate = 0.0f;
	FLOAT	fMyMPRate = 0.0f;		
	FLOAT	fMyWetRate = 0.0f;		
	double  fMyExpRate = 0.0f;
//	WORD	wJobIcon;
	WORD	wImgNum;
	CHAR	pszBuff[MAX_PATH];
	RECT	rcStats;
	DWORD	dwFntClr;

	BYTE	bMyLevel= g_xGameProc.m_xMyHero.m_stAbility.bLevel;
	WORD	wMyAC   = g_xGameProc.m_xMyHero.m_stAbility.wAC;
	DWORD	dwMyDC   = g_xGameProc.m_xMyHero.m_stAbility.dwDC;
	DWORD	dwMyMC   = g_xGameProc.m_xMyHero.m_stAbility.dwMC;
	DWORD	dwMySC   = g_xGameProc.m_xMyHero.m_stAbility.dwSC;
	BYTE	bDay	= g_xGameProc.m_bDayState;

	WORD	wHP		= g_xGameProc.m_xMyHero.m_stAbility.wHP	   = g_xGameProc.m_xMyHero.m_wHP;
	WORD	wMaxHP	= g_xGameProc.m_xMyHero.m_stAbility.wMaxHP = g_xGameProc.m_xMyHero.m_wMAXHP;
	WORD	wMP		= g_xGameProc.m_xMyHero.m_stAbility.wMP	   = g_xGameProc.m_xMyHero.m_wMP;
	WORD	wWet	= g_xGameProc.m_xMyHero.m_stAbility.wWeight;
	BYTE	bJob	= g_xGameProc.m_xMyHero.m_bJob;
	LONGLONG	dlngExp	= g_xGameProc.m_xMyHero.m_stAbility.dlngExp;
	
	// 하루의 상태치(밤, 낮, 저녁, 새벽)
	switch ( bDay )
	{
	case _DAYSTATE_DAY:
		wImgNum = 1200;
		break;
	case _DAYSTATE_DUSK:
		wImgNum = 1201;
		break;
	case _DAYSTATE_NIGHT:
		wImgNum = 1202;
		break;
	case _DAYSTATE_DAWN:
		wImgNum = 1203;
		break;
	}
/*
	if (m_bIsLargeChat == TRUE)
	{
		if ( m_pxInterImg->NewSetIndex(wImgNum) )
		{
 			g_xMainWnd.DrawWithImageForComp(m_rcMain.left+384, m_rcMain.top-178,
											m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth,
											m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight,
											(WORD*)m_pxInterImg->m_pbCurrImage, _CLIP_WIDTH, 600);
		}
	}
	else
	{
		if ( m_pxInterImg->NewSetIndex(wImgNum) )
		{
 			g_xMainWnd.DrawWithImageForComp(m_rcMain.left+385, m_rcMain.top-11,
											m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth,
											m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight,
											(WORD*)m_pxInterImg->m_pbCurrImage, _CLIP_WIDTH, 600);
		}
	}
*/
	// HP, MP찍기.
	// 비율검사.
	if ( wHP )	
	{
		if ( wMaxHP )
		{
			fMyHPRate = (FLOAT)((FLOAT)wHP/(FLOAT)wMaxHP);

			if ( fMyHPRate > 1.0f ) 
			{
				fMyHPRate = 1.0f;
			}
		}
	}
	else			
	{
		fMyHPRate = 0;
	}

	if ( wMP )		
	{
		if ( g_xGameProc.m_xMyHero.m_stAbility.wMaxMP )
		{
			fMyMPRate = (FLOAT)((FLOAT)wMP/(FLOAT)g_xGameProc.m_xMyHero.m_stAbility.wMaxMP);

			if ( fMyMPRate > 1.0f ) 
			{
				fMyMPRate = 1.0f;
			}
		}
	}
	else			
	{
		fMyMPRate = 0;
	}

	if ( dlngExp )	
	{
		if ( g_xGameProc.m_xMyHero.m_stAbility.dlngMaxExp )
		{
			fMyExpRate = ((double)(LONGLONG)dlngExp/(double)(LONGLONG)g_xGameProc.m_xMyHero.m_stAbility.dlngMaxExp);

			if ( fMyExpRate > 1.0f ) 
			{
				fMyExpRate = 1.0f;
			}
		}
	}
	else			
	{
		fMyExpRate = 0;
	}

	if ( wWet )		
	{
		if ( g_xGameProc.m_xMyHero.m_stAbility.wMaxWeight )
		{
			fMyWetRate = (FLOAT)((FLOAT)wWet /(FLOAT)g_xGameProc.m_xMyHero.m_stAbility.wMaxWeight);

			if ( fMyWetRate > 1.0f ) 
			{
				fMyWetRate = 1.0f;
			}
		}
	}
	else			
	{
		fMyWetRate = 0;
	}

	RECT rcHP;
	RECT rcMP;

	RECT rcEXP;
	RECT rcWET;

#ifdef _3rdINTERFACE

	// HP찍기
	if ( m_pxInterImg->NewSetIndex(52) )
	{
		SetRect(&rcHP, 0, 0, 
				(INT)(m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth*fMyHPRate), m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight);
 		g_xMainWnd.DrawWithImageForComp(m_rcMain.left+111, m_rcMain.top+17, &rcHP, (WORD*)m_pxInterImg->m_pbCurrImage);
	}
	sprintf(pszBuff, "%d/%d", wHP, wMaxHP);
	SetRect(&rcStats, 174, 561, 238, 576);

	g_xMainWnd.PutsHan(NULL, rcStats, RGB(255, 255, 255), RGB(0, 0, 0), pszBuff, NULL);

	// MP찍기
	if ( m_pxInterImg->NewSetIndex(54) )
	{
		SetRect(&rcMP, 0, 0, 
				 (INT)(m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth*fMyMPRate ), m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight);
 		g_xMainWnd.DrawWithImageForComp(m_rcMain.left+111, m_rcMain.top+33, &rcMP, (WORD*)m_pxInterImg->m_pbCurrImage);
	}
	sprintf(pszBuff, "%d/%d", wMP, g_xGameProc.m_xMyHero.m_stAbility.wMaxMP);
	SetRect(&rcStats, 174, 577, 238, 592);

	g_xMainWnd.PutsHan(NULL, rcStats, RGB(255, 255, 255), RGB(0, 0, 0), pszBuff, NULL);

	INT nExpCnt = fMyExpRate * 10;
	nExpCnt = nExpCnt;

	if ( nExpCnt == 0 )
	{
		if ( m_pxInterImg->NewSetIndex(56) )
		{
			RECT rcExp;
			FLOAT	fRemainRate;

			fRemainRate = fMyExpRate * 10;

			SetRect(&rcExp, 0, 0, 
					 (INT)(m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth*fRemainRate ), m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight);
 			g_xMainWnd.DrawWithImageForComp(m_rcMain.left+96, m_rcMain.top+5, &rcExp, (WORD*)m_pxInterImg->m_pbCurrImage);
		}
	}
	else if ( nExpCnt == 9 )
	{
		if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(56))
		{
			g_xMainWnd.DrawWithImageForComp(m_rcMain.left+96, m_rcMain.top + 5, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
		}

		for ( INT nI=0; nI<nExpCnt-1; nI++ )
		{
			if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(56))
			{
				g_xMainWnd.DrawWithImageForComp(m_rcMain.left+166 + 70*nI, m_rcMain.top + 5, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
												(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
			}
		}

		if ( m_pxInterImg->NewSetIndex(56) )
		{
			RECT rcExp;
			FLOAT	fRemainRate;

			fRemainRate = fMyExpRate * 10 - nExpCnt;

			SetRect(&rcExp, 0, 0, 
					 (INT)(m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth*fRemainRate ), m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight);
 			g_xMainWnd.DrawWithImageForComp(m_rcMain.left+166 + 70*(nExpCnt-1), m_rcMain.top+5, &rcExp, (WORD*)m_pxInterImg->m_pbCurrImage);
		}

	}
	else
	{
		// 맨 왼쪽 경험치 바
		if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(56))
		{
			g_xMainWnd.DrawWithImageForComp(m_rcMain.left+96, m_rcMain.top + 5, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
		}

		// 중간 경험치 바 꽉 찬 것들
		for ( INT nI=0; nI<nExpCnt-1; nI++ )
		{
			if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(56))
			{
				g_xMainWnd.DrawWithImageForComp(m_rcMain.left+166 + 70*nI, m_rcMain.top + 5, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
												(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
			}
		}

		if ( m_pxInterImg->NewSetIndex(56) )
		{
			RECT	rcExp;
			FLOAT	fRemainRate;

			fRemainRate = fMyExpRate * 10 - nExpCnt;

			SetRect(&rcExp, 0, 0, 
					 (INT)(m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth*fRemainRate ), m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight);
 			g_xMainWnd.DrawWithImageForComp(m_rcMain.left+166 + 70*(nExpCnt-1), m_rcMain.top+5, &rcExp, (WORD*)m_pxInterImg->m_pbCurrImage);

		}
	}

	if ( PtInRect(&m_rcExpS, g_xGameProc.m_ptMousePos) )
	{			
		sprintf(pszBuff, "%s%.2f%s", g_xMsg.GetMsg(2624), fMyExpRate*100, "%");
		SIZE sizeLen = g_xMainWnd.GetStrLength(NULL, NULL, pszBuff);

		SetRect(&rcStats, g_xGameProc.m_ptMousePos.x - sizeLen.cx/2 - 5, 552 - sizeLen.cy/2 - 1, g_xGameProc.m_ptMousePos.x + sizeLen.cx/2 + 5, 552 + sizeLen.cy/2 + 1);

		D3DMATERIAL7 mtrl;
		D3DVECTOR	vecTrans((FLOAT)rcStats.left, (FLOAT)rcStats.top, 0);
		D3DVECTOR	vecScale((FLOAT)rcStats.right-rcStats.left, rcStats.bottom-rcStats.top, 1);

		D3DUtil_InitMaterial(mtrl, (FLOAT)80/255.0f, (FLOAT)60/255.0f, (FLOAT)40/255.0f);
		mtrl.diffuse.a = 150.0f/255.0f;
		g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

		g_xMainWnd.PutsHan(NULL, rcStats, RGB(255, 255, 255), RGB(0, 0, 0), pszBuff, NULL);
		g_xMainWnd.DrawWithGDI(&rcStats, NULL, RGB(100, 75, 50), 1);
	}

	// 가방무게
	if ( m_pxInterImg->NewSetIndex(60) )
	{
		RECT rcBagWeight;
		SetRect(&rcBagWeight, 0, (INT)(m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight-(m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight*fMyWetRate)),
				m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth, m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight);
 		g_xMainWnd.DrawWithImageForComp(m_rcMain.left+101, m_rcMain.top+16, &rcBagWeight, (WORD*)m_pxInterImg->m_pbCurrImage);
	}

	if ( PtInRect(&m_rcWetS, g_xGameProc.m_ptMousePos) )
	{
		sprintf(pszBuff, "%s%d/%d", g_xMsg.GetMsg(2625), wWet, g_xGameProc.m_xMyHero.m_stAbility.wMaxWeight);

		SIZE sizeLen = g_xMainWnd.GetStrLength(NULL, NULL, pszBuff);

		SetRect(&rcStats, 100 - sizeLen.cx/2 - 5, 550- sizeLen.cy/2 - 1, 100 + sizeLen.cx/2 + 5, 550 + sizeLen.cy/2 + 1);

		D3DMATERIAL7 mtrl;
		D3DVECTOR	vecTrans((FLOAT)rcStats.left, (FLOAT)rcStats.top, 0);
		D3DVECTOR	vecScale((FLOAT)rcStats.right-rcStats.left, rcStats.bottom-rcStats.top, 1);

		D3DUtil_InitMaterial(mtrl, (FLOAT)100/255.0f, (FLOAT)100/255.0f, (FLOAT)0/255.0f);
		mtrl.diffuse.a = 150.0f/255.0f;
		g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

		g_xMainWnd.PutsHan(NULL, rcStats, RGB(255, 255, 255), RGB(0, 0, 0), pszBuff, NULL);
		g_xMainWnd.DrawWithGDI(&rcStats, NULL, RGB(120, 120, 0), 1);
	}


	// 경험치

	// 직업
	CHAR szInfo[MAX_PATH];
	switch(bJob)
	{
	case _JOB_JUNSA:
		sprintf(szInfo, g_xMsg.GetMsg(2651));
		break;
	case _JOB_SULSA:
		sprintf(szInfo, g_xMsg.GetMsg(2652));
		break;
	case _JOB_DOSA:
		sprintf(szInfo, g_xMsg.GetMsg(2653));
		break;
	}
	RECT rcInfo = { m_rcMain.left + 328, m_rcMain.top + 16, m_rcMain.left + 372, m_rcMain.top + 31 };
	g_xMainWnd.PutsHan(NULL, rcInfo, RGB(255, 255, 255), RGB(0, 0, 0), szInfo, NULL);

	// 레벨
	sprintf(szInfo, "%d", bMyLevel);
	rcInfo.top = m_rcMain.top + 34;
	rcInfo.bottom = m_rcMain.top + 49;
	g_xMainWnd.PutsHan(NULL, rcInfo, RGB(255, 255, 255), RGB(0, 0, 0), szInfo, NULL);

	// 명성치
	sprintf(szInfo, "%d", g_xGameProc.m_xMyHero.m_nFame);
	rcInfo.left = m_rcMain.left + 394;
	rcInfo.right = m_rcMain.left + 440;
	rcInfo.top = m_rcMain.top + 16;
	rcInfo.bottom = m_rcMain.top + 31;
	g_xMainWnd.PutsHan(NULL, rcInfo, RGB(255, 255, 255), RGB(0, 0, 0), szInfo, NULL);

	// 공격력
	if ( m_bDcScMcShow == 0 )
		sprintf(szInfo, "%d-%d", LOWORD(dwMyDC), HIWORD(dwMyDC));
	else if ( m_bDcScMcShow == 1 )
	{
		sprintf(szInfo, "%d-%d", LOWORD(dwMyMC), HIWORD(dwMyMC));
		
		if ( m_pxInterImg->NewSetIndex(62) )
		{
 			g_xMainWnd.DrawWithImageForCompClipRgn(m_rcMain.left+374, m_rcMain.top+33,	
													m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth,
													m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight,
												   (WORD*)m_pxInterImg->m_pbCurrImage, _CLIP_WIDTH, 600);
		}
	}
	else if ( m_bDcScMcShow == 2 )
	{
		sprintf(szInfo, "%d-%d", LOWORD(dwMySC), HIWORD(dwMySC));
		
		if ( m_pxInterImg->NewSetIndex(63) )
		{
 			g_xMainWnd.DrawWithImageForCompClipRgn(m_rcMain.left+374, m_rcMain.top+33,	
													m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth,
													m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight,
												   (WORD*)m_pxInterImg->m_pbCurrImage, _CLIP_WIDTH, 600);
		}
	}

	rcInfo.top = m_rcMain.top + 34;
	rcInfo.bottom = m_rcMain.top + 49;
	g_xMainWnd.PutsHan(NULL, rcInfo, RGB(255, 255, 255), RGB(0, 0, 0), szInfo, NULL);

	// 방어력
	sprintf(szInfo, "%d-%d", LOBYTE(wMyAC), HIBYTE(wMyAC));
	rcInfo.left = m_rcMain.left + 462;
	rcInfo.right = m_rcMain.left + 508;
	rcInfo.top = m_rcMain.top + 16;
	rcInfo.bottom = m_rcMain.top + 31;
	g_xMainWnd.PutsHan(NULL, rcInfo, RGB(255, 255, 255), RGB(0, 0, 0), szInfo, NULL);

	// 마법방어력
	sprintf(szInfo, "%d-%d", LOBYTE(g_xGameProc.m_xMyHero.m_stAbility.wMAC), HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.wMAC));	
	rcInfo.top = m_rcMain.top + 34;
	rcInfo.bottom = m_rcMain.top + 49;		
	g_xMainWnd.PutsHan(NULL, rcInfo, RGB(255, 255, 255), RGB(0, 0, 0), szInfo, NULL);
	
#else //_3rdINTERFACE	
	if ( bJob == _JOB_JUNSA && bMyLevel < 24 )
	{
		if ( m_pxInterImg->NewSetIndex(1163) )
		{
			SetRect(&rcHP, 0, (INT)(m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight-(m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight*fMyHPRate)),
				    m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth, m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight);
 			g_xMainWnd.DrawWithImageForComp(m_rcMain.left+33, m_rcMain.top+8, &rcHP, (WORD*)m_pxInterImg->m_pbCurrImage);
		}

		if ( m_pxInterImg->NewSetIndex(1165) )
		{
 			g_xMainWnd.DrawWithImageForComp(m_rcMain.left+73, m_rcMain.top+8, &rcHP, (WORD*)m_pxInterImg->m_pbCurrImage);
		}

		if ( PtInRect(&m_rcHPS, g_xGameProc.m_ptMousePos) || PtInRect(&m_rcMPS, g_xGameProc.m_ptMousePos) )
		{
			sprintf(pszBuff, "%s%d/%d", g_xMsg.GetMsg(2622), wHP, wMaxHP);
			SIZE sizeLen = g_xMainWnd.GetStrLength(NULL, NULL, pszBuff);

			SetRect(&rcStats, 70 - sizeLen.cx/2 - 5, 528 - sizeLen.cy/2 - 1, 70 + sizeLen.cx/2 + 5, 528 + sizeLen.cy/2 + 1);

			D3DMATERIAL7 mtrl;
			D3DVECTOR	vecTrans((FLOAT)rcStats.left, (FLOAT)rcStats.top, 0);
			D3DVECTOR	vecScale((FLOAT)rcStats.right-rcStats.left, rcStats.bottom-rcStats.top, 1);

			D3DUtil_InitMaterial(mtrl, (FLOAT)120/255.0f, (FLOAT)60/255.0f, (FLOAT)60/255.0f);
			mtrl.diffuse.a = 150.0f/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

			g_xMainWnd.PutsHan(NULL, rcStats, RGB(255, 255, 255), RGB(0, 0, 0), pszBuff, NULL);
			g_xMainWnd.DrawWithGDI(&rcStats, NULL, RGB(160, 80, 80), 1);
		}
	}
	else
	{
		if ( m_pxInterImg->NewSetIndex(1163) )
		{
			SetRect(&rcHP, 0, (INT)(m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight-(m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight*fMyHPRate)), 
					m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth, m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight);
 			g_xMainWnd.DrawWithImageForComp(m_rcMain.left+33, m_rcMain.top+8, &rcHP, (WORD*)m_pxInterImg->m_pbCurrImage);
		}

		if ( m_pxInterImg->NewSetIndex(1164) )
		{
			 SetRect(&rcMP, 0, (INT)(m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight-(m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight*fMyMPRate)), 
					 m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth, m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight);
 			g_xMainWnd.DrawWithImageForComp(m_rcMain.left+73, m_rcMain.top+8, &rcMP, (WORD*)m_pxInterImg->m_pbCurrImage);
		}

		if ( PtInRect(&m_rcHPS, g_xGameProc.m_ptMousePos) )
		{
			sprintf(pszBuff, "%s%d/%d", g_xMsg.GetMsg(2622), wHP, wMaxHP);
			SIZE sizeLen = g_xMainWnd.GetStrLength(NULL, NULL, pszBuff);

			SetRect(&rcStats, 55 - sizeLen.cx/2 - 5, 528 - sizeLen.cy/2 - 1, 55 + sizeLen.cx/2 + 5, 528 + sizeLen.cy/2 + 1);

			D3DMATERIAL7 mtrl;
			D3DVECTOR	vecTrans((FLOAT)rcStats.left, (FLOAT)rcStats.top, 0);
			D3DVECTOR	vecScale((FLOAT)rcStats.right-rcStats.left, rcStats.bottom-rcStats.top, 1);

			D3DUtil_InitMaterial(mtrl, (FLOAT)120/255.0f, (FLOAT)60/255.0f, (FLOAT)60/255.0f);
			mtrl.diffuse.a = 150.0f/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

			g_xMainWnd.PutsHan(NULL, rcStats, RGB(255, 255, 255), RGB(0, 0, 0), pszBuff, NULL);
			g_xMainWnd.DrawWithGDI(&rcStats, NULL, RGB(160, 80, 80), 1);
		}
		if ( PtInRect(&m_rcMPS, g_xGameProc.m_ptMousePos) )
		{
			sprintf(pszBuff, "%s%d/%d", g_xMsg.GetMsg(2623), wMP, g_xGameProc.m_xMyHero.m_stAbility.wMaxMP);
			SIZE sizeLen = g_xMainWnd.GetStrLength(NULL, NULL, pszBuff);

			SetRect(&rcStats, 105 - sizeLen.cx/2 - 5, 528 - sizeLen.cy/2 - 1, 105 + sizeLen.cx/2 + 5, 528 + sizeLen.cy/2 + 1);

			D3DMATERIAL7 mtrl;
			D3DVECTOR	vecTrans((FLOAT)rcStats.left, (FLOAT)rcStats.top, 0);
			D3DVECTOR	vecScale((FLOAT)rcStats.right-rcStats.left, rcStats.bottom-rcStats.top, 1);

			D3DUtil_InitMaterial(mtrl, (FLOAT)60/255.0f, (FLOAT)60/255.0f, (FLOAT)120/255.0f);
			mtrl.diffuse.a = 150.0f/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

			g_xMainWnd.PutsHan(NULL, rcStats, RGB(255, 255, 255), RGB(0, 0, 0), pszBuff, NULL);
			g_xMainWnd.DrawWithGDI(&rcStats, NULL, RGB(80, 80, 160), 1);
		}
	}


	if ( m_pxInterImg->NewSetIndex(1167) )
	{
		SetRect(&rcWET, 0, (INT)(m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight-(m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight*fMyWetRate)), 
				m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth, m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight);
 		g_xMainWnd.DrawWithImageForComp(m_rcMain.left+165, m_rcMain.top+26, &rcWET, (WORD*)m_pxInterImg->m_pbCurrImage);

		if ( PtInRect(&m_rcWetS, g_xGameProc.m_ptMousePos) )
		{
			sprintf(pszBuff, "%s%d/%d", g_xMsg.GetMsg(2625), wWet, g_xGameProc.m_xMyHero.m_stAbility.wMaxWeight);

			SIZE sizeLen = g_xMainWnd.GetStrLength(NULL, NULL, pszBuff);

			SetRect(&rcStats, 210 - sizeLen.cx/2 - 5, 535- sizeLen.cy/2 - 1, 210 + sizeLen.cx/2 + 5, 535 + sizeLen.cy/2 + 1);

			D3DMATERIAL7 mtrl;
			D3DVECTOR	vecTrans((FLOAT)rcStats.left, (FLOAT)rcStats.top, 0);
			D3DVECTOR	vecScale((FLOAT)rcStats.right-rcStats.left, rcStats.bottom-rcStats.top, 1);

			D3DUtil_InitMaterial(mtrl, (FLOAT)100/255.0f, (FLOAT)100/255.0f, (FLOAT)0/255.0f);
			mtrl.diffuse.a = 150.0f/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

			g_xMainWnd.PutsHan(NULL, rcStats, RGB(255, 255, 255), RGB(0, 0, 0), pszBuff, NULL);
			g_xMainWnd.DrawWithGDI(&rcStats, NULL, RGB(120, 120, 0), 1);
		}
	}

	if ( m_pxInterImg->NewSetIndex(1166) )
	{
		SetRect(&rcEXP, 0, (INT)(m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight-(m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight*fMyExpRate)), 
				m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth, m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight);
 		g_xMainWnd.DrawWithImageForComp(m_rcMain.left + 152, m_rcMain.top + 26, &rcEXP, (WORD*)m_pxInterImg->m_pbCurrImage);

		if ( PtInRect(&m_rcExpS, g_xGameProc.m_ptMousePos) )
		{			
			sprintf(pszBuff, "%s%.2f%s", g_xMsg.GetMsg(2624), fMyExpRate*100, "%");
			SIZE sizeLen = g_xMainWnd.GetStrLength(NULL, NULL, pszBuff);

			SetRect(&rcStats, 152 - sizeLen.cx/2 - 5, 544 - sizeLen.cy/2 - 1, 152 + sizeLen.cx/2 + 5, 544 + sizeLen.cy/2 + 1);

			D3DMATERIAL7 mtrl;
			D3DVECTOR	vecTrans((FLOAT)rcStats.left, (FLOAT)rcStats.top, 0);
			D3DVECTOR	vecScale((FLOAT)rcStats.right-rcStats.left, rcStats.bottom-rcStats.top, 1);

			D3DUtil_InitMaterial(mtrl, (FLOAT)80/255.0f, (FLOAT)60/255.0f, (FLOAT)40/255.0f);
			mtrl.diffuse.a = 150.0f/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

			g_xMainWnd.PutsHan(NULL, rcStats, RGB(255, 255, 255), RGB(0, 0, 0), pszBuff, NULL);
			g_xMainWnd.DrawWithGDI(&rcStats, NULL, RGB(100, 75, 50), 1);
		}
	}

	dwFntClr = RGB(225, 225, 0);
	// 레벨찍기.
	sprintf(pszBuff, "%d", g_xGameProc.m_xMyHero.m_stAbility.bLevel);
	if (m_bIsLargeChat == TRUE)
		SetRect(&rcStats, 393, 298, 409, 314);
	else
		SetRect(&rcStats, 393, 466, 409, 482);
	g_xMainWnd.PutsHan(NULL, rcStats, dwFntClr, RGB(0, 0, 0), pszBuff, g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 8, 0, FW_BOLD));

	dwFntClr = RGB(255, 255, 200);
	// 맵이름 및 좌표찍기.
	sprintf(pszBuff, "%s : [%d,%d]", g_xGameProc.m_szMapName, g_xGameProc.m_xMyHero.m_nPosX, g_xGameProc.m_xMyHero.m_nPosY);
	SetRect(&rcStats, 6, 577, 139, 594);

	RECT rcBack;
	SetRect(&rcBack, rcStats.left-1, rcStats.top-1, rcStats.right-1, rcStats.bottom-1);
	g_xMainWnd.PutsHan(NULL, rcBack, RGB(10, 10, 10), RGB(0, 0, 0), pszBuff);

	SetRect(&rcBack, rcStats.left+1, rcStats.top-1, rcStats.right+1, rcStats.bottom-1);
	g_xMainWnd.PutsHan(NULL, rcBack, RGB(10, 10, 10), RGB(0, 0, 0), pszBuff);

	SetRect(&rcBack, rcStats.left-1, rcStats.top+1, rcStats.right-1, rcStats.bottom+1);
	g_xMainWnd.PutsHan(NULL, rcBack, RGB(10, 10, 10), RGB(0, 0, 0), pszBuff);

	SetRect(&rcBack, rcStats.left+1, rcStats.top+1, rcStats.right+1, rcStats.bottom+1);
	g_xMainWnd.PutsHan(NULL, rcBack, RGB(10, 10, 10), RGB(0, 0, 0), pszBuff);

	g_xMainWnd.PutsHan(NULL, rcStats, dwFntClr, RGB(0, 0, 0), pszBuff);

	dwFntClr = RGB(255, 200, 50);

	if ( m_bAcShow == TRUE )
	{
		if ( m_pxInterImg->NewSetIndex(1500) )
		{
 			g_xMainWnd.DrawWithImageForCompClipRgn(m_rcMain.left+635, m_rcMain.top+105,	
													m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth,
													m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight,
												   (WORD*)m_pxInterImg->m_pbCurrImage, _CLIP_WIDTH, 600);
		}
		sprintf(pszBuff, "%d-%d", LOBYTE(wMyAC), HIBYTE(wMyAC));
		SetRect(&rcStats, 663, 570, 713, 594);
		g_xMainWnd.PutsHan(NULL, rcStats, dwFntClr, RGB(0, 0, 0), pszBuff);
	}
	else
	{
		if ( m_pxInterImg->NewSetIndex(1502) )
		{
 			g_xMainWnd.DrawWithImageForCompClipRgn(m_rcMain.left+635, m_rcMain.top+105,	
													m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth,
													m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight,
												   (WORD*)m_pxInterImg->m_pbCurrImage, _CLIP_WIDTH, 600);
		}

		sprintf(pszBuff, "%d-%d", LOBYTE(g_xGameProc.m_xMyHero.m_stAbility.wMAC), HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.wMAC));
		SetRect(&rcStats, 663, 570, 713, 594);
		g_xMainWnd.PutsHan(NULL, rcStats, dwFntClr, RGB(0, 0, 0), pszBuff);

	}

	if ( m_bDcScMcShow == TRUE )
	{
		if ( m_pxInterImg->NewSetIndex(1501) )
		{
 			g_xMainWnd.DrawWithImageForCompClipRgn(m_rcMain.left+715, m_rcMain.top+105,	
													m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth,
													m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight,
												   (WORD*)m_pxInterImg->m_pbCurrImage, _CLIP_WIDTH, 600);
		}
		sprintf(pszBuff, "%d-%d", LOWORD(dwMyDC), HIWORD(dwMyDC));
		SetRect(&rcStats, 742, 570, 798, 594);		
		g_xMainWnd.PutsHan(NULL, rcStats, dwFntClr, RGB(0, 0, 0), pszBuff);
	}
	else
	{
		if ( m_pxInterImg->NewSetIndex(1503) )
		{
 			g_xMainWnd.DrawWithImageForCompClipRgn(m_rcMain.left+715, m_rcMain.top+105,	
													m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth,
													m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight,
												   (WORD*)m_pxInterImg->m_pbCurrImage, _CLIP_WIDTH, 600);
		}
		if ( g_xGameProc.m_xMyHero.m_bJob == _JOB_DOSA )
			sprintf(pszBuff, "%d-%d", LOBYTE(g_xGameProc.m_xMyHero.m_stAbility.wSC), HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.wSC));
		else 
			sprintf(pszBuff, "%d-%d", LOBYTE(g_xGameProc.m_xMyHero.m_stAbility.dwMC), HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.dwMC));

		SetRect(&rcStats, 742, 570, 798, 594);
		g_xMainWnd.PutsHan(NULL, rcStats, dwFntClr, RGB(0, 0, 0), pszBuff);
	}
#endif //_3rdINTERFACE

/*	switch ( bJob )
	{
	case _JOB_DOSA:		
		{
//			wJobIcon = 66;
			wImgNum	 = 123;
//			sprintf(pszBuff, "%d-%d", LOBYTE(wMySC), HIBYTE(wMySC));
//			g_xMainWnd.PutsHan(NULL, rcStats, dwFntClr, RGB(0, 0, 0), pszBuff);
		}
		break;
	case _JOB_SULSA:	
		{
//			wJobIcon = 65;	
			wImgNum	 = 124;
//			sprintf(pszBuff, "%d-%d", LOBYTE(wMyMC), HIBYTE(wMyMC));
//			g_xMainWnd.PutsHan(NULL, rcStats, dwFntClr, RGB(0, 0, 0), pszBuff);
		}
		break;
	case _JOB_JUNSA:	
		{
//			wJobIcon = 64;
			wImgNum	 = 122;
			sprintf(pszBuff, "%d-%d", LOBYTE(wMyDC), HIBYTE(wMyDC));
			g_xMainWnd.PutsHan(NULL, rcStats, dwFntClr, RGB(0, 0, 0), pszBuff);
		}
		break;
	}
*//*	if ( m_pxInterImg->NewSetIndex(wJobIcon) )
	{
 		g_xMainWnd.DrawWithImageForComp(m_rcMain.left+82, m_rcMain.top+71,
										m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth,
										m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight,
										(WORD*)m_pxInterImg->m_pbCurrImage);
	}
*/	// AC찍기.
/*	if ( m_pxInterImg->NewSetIndex(120) )
	{
 		g_xMainWnd.DrawWithImageForComp(m_rcMain.left+403, m_rcMain.top+136,
										m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth,
										m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight,
										(WORD*)m_pxInterImg->m_pbCurrImage);
	}
	// DC, MC, SC
	if ( m_pxInterImg->NewSetIndex(wImgNum) )
	{
 		g_xMainWnd.DrawWithImageForComp(m_rcMain.left+501, m_rcMain.top+136,
										m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth,
										m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight,
										(WORD*)m_pxInterImg->m_pbCurrImage);
	}
*/
}


VOID CInterface::ShowMagicKey()
{
	if ( m_bShowKey )
	{
		INT nCnt;		
		INT nRow = 0;
		INT nRemainder = 0;



// 추가.. 무공키블렌드./////////////
		D3DMATERIAL7	mtrl;
		D3DVECTOR		vecTrans;
		D3DVECTOR		vecScale;
		RECT	rcTemp;

		for ( nCnt = 0; nCnt < _MAGIC_MAX_KEY; nCnt++)
		{
			nRow = nCnt / 2;
			nRemainder = nCnt % 2;

			if ( m_xMagicWnd.m_bMagicKeyTable[nCnt] && g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].NewSetIndex((m_xMagicWnd.m_bMagicKeyTable[nCnt]-1)+1000) )
			{
				vecTrans = D3DVECTOR((FLOAT)(nRemainder*32) + 736, 200 + (nRow*32) + 2.0f, 0);
				vecScale = D3DVECTOR((FLOAT)g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_lpstNewCurrWilImageInfo->shHeight, 1);

				LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_MICON, ((m_xMagicWnd.m_bMagicKeyTable[nCnt]-1)+1000));

				D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)255/255.0f, (FLOAT)255/255.0f);
				mtrl.diffuse.a = 200.0f/255.0f;
				g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr);
			}
			else if ( m_pxInterImg->NewSetIndex(100+nCnt) )
			{
				vecTrans = D3DVECTOR((FLOAT)(nRemainder*32) + 736, 200 + (nRow*32) + 2.0f, 0);
				vecScale = D3DVECTOR((FLOAT)m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight, 1);

				rcTemp.left = (nRemainder*32) + 730;
				rcTemp.top = 200 + (nRow*32) + 2.0f;
				rcTemp.right  = rcTemp.left + 32;
				rcTemp.bottom = rcTemp.top + 32;
//				g_xMainWnd.DrawWithGDI(&rcTemp, NULL, RGB(200, 200, 200), 1);

				LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_INTER, (100+nCnt));

				D3DUtil_InitMaterial(mtrl, (FLOAT)150/255.0f, (FLOAT)150/255.0f, (FLOAT)150/255.0f);
				mtrl.diffuse.a = 150.0f/255.0f;
				g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr);
			}
		}
/*
		g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(2090);

		vecTrans = D3DVECTOR((FLOAT)410, 170.0f, 0);
		vecScale = D3DVECTOR((FLOAT)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight, 3);

		LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_INTER, 2090);

		D3DUtil_InitMaterial(mtrl, (FLOAT)100/255.0f, (FLOAT)230/255.0f, (FLOAT)100/255.0f);
		mtrl.diffuse.a = 150.0f/255.0f;
		g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr);
*/
	}
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 윈도우 관리부분/////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************

	함수명 : CInterface::GetWindowInMousePos()

	작성자 : 
	작성일 : 

	목적   : 마우스 포인터를 영역안에 가지고 있는 윈도우리스트중 맨처음 윈도우의 ID를 리턴한다.
	입력   : POINT ptMouse
	출력   : 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
INT	CInterface::GetWindowInMousePos(POINT ptMouse)
{
	if ( m_xWndOrderList.GetCounter() != 0 )
	{
		RECT rcWnd;
		INT* pnCurrID;
		m_xWndOrderList.MoveCurrentToTail();

		for ( INT nCnt = m_xWndOrderList.GetCounter()-1; nCnt >= 0 ; nCnt-- )
		{
			pnCurrID = m_xWndOrderList.GetCurrentData();

			switch ( *pnCurrID )
			{
			case _WND_ID_INVENTORY:
				rcWnd = m_xInventoryWnd.GetGameWndRect();
				break;
			case _WND_ID_STATUS:
				rcWnd = m_xStatusWnd.GetGameWndRect();
				break;
			case _WND_ID_STORE:
				rcWnd = m_xStoreWnd.GetGameWndRect();
				break;
			case _WND_ID_EXCHANGE:
				rcWnd = m_xExchangeWnd.GetGameWndRect();
				break;
			case _WND_ID_GUILD:
				rcWnd = m_xGuildWnd.GetGameWndRect();
				break;
			case _WND_ID_GROUP:
				rcWnd = m_xGroupWnd.GetGameWndRect();
				break;
			case _WND_ID_USERSTATE:
				rcWnd = m_xUserStateWnd.GetGameWndRect();
				break;
			case _WND_ID_CHATPOP:
				rcWnd = m_xChatPopWnd.GetGameWndRect();
				break;
			case _WND_ID_NPCCHAT:
				rcWnd = m_xNPCWnd.GetGameWndRect();
				break;
			case _WND_ID_QUEST:
				rcWnd = m_xQuestWnd.GetGameWndRect();
				break;
			case _WND_ID_OPTION:
				rcWnd = m_xOptionWnd.GetGameWndRect();
				break;
			case _WND_ID_HORSE:
				rcWnd = m_xHorseWnd.GetGameWndRect();
				break;
			case _WND_ID_MAGIC:
				rcWnd = m_xMagicWnd.GetGameWndRect();
				break;
			case _WND_ID_BELT:
				rcWnd = m_xBeltWnd.GetGameWndRect();
				break;
			case _WND_ID_SIEGE:
				rcWnd = m_xSiegeWnd.GetGameWndRect();
				break;
			case _WND_ID_MAGICSHORTCUT:
				rcWnd = m_xMagicShortcutWnd.GetGameWndRect();
				break;
			case _WND_ID_USERMARKET:
				rcWnd = m_xMarketWnd.GetGameWndRect();
				break;
			case _WND_ID_USERMARKETUP:
				rcWnd = m_xMarketUpWnd.GetGameWndRect();
				break;
			case _WND_ID_MESSENGER:
				rcWnd = m_xMessengerWnd.GetGameWndRect();
				break;
			case _WND_ID_FACEIMGUP:
				rcWnd = m_xFaceImgUpWnd.GetGameWndRect();
				break;
			case _WND_ID_UTIL:
				rcWnd = m_xUtilWnd.GetGameWndRect();
				break;
			case _WND_ID_VIEWMINIMAP:
				rcWnd = m_xViewMiniMapWnd.GetGameWndRect();
				break;
			case _WND_ID_CHAT:
				rcWnd = m_xChatWnd.GetGameWndRect();
				break;
			case _WND_ID_SETTING:
				rcWnd = m_xSettingWnd.GetGameWndRect();
				break;
			case _WNDIMGIDX_EXIT:
				rcWnd = m_xGameOverWnd.GetGameWndRect();
				break;
			}

			if ( PtInRect(&rcWnd, ptMouse) )
			{
				return *pnCurrID;
			}

			m_xWndOrderList.MovePreviousNode();
		}
	}
	return -1;
}




/******************************************************************************************************************

	함수명 : CInterface::AddWindowToList()

	작성자 : 
	작성일 : 

	목적   : 윈도우리스트의 맨 마지막에 현재 입력받은 아이디가 nID인 윈도우를 추가한다.
	입력   : INT nID
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CInterface::AddWindowToList( INT nID )
{
	m_xWndOrderList.AddNode(nID);
}

/******************************************************************************************************************

	함수명 : CInterface::DeleteWindowToList()

	작성자 : 
	작성일 : 

	목적   : nID의 아이디를 가진 윈도우를 리스트상에서 삭제한다.
	입력   : INT nID
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CInterface::DeleteWindowToList(INT nID)
{
	if ( m_xWndOrderList.GetCounter() != 0 )
	{
		m_xWndOrderList.MoveCurrentToTop();

		INT* pnCurrID;
		for ( INT nCnt = 0; nCnt < m_xWndOrderList.GetCounter(); nCnt++ )
		{
			pnCurrID = m_xWndOrderList.GetCurrentData();

			if ( *pnCurrID == nID )
			{
				m_xWndOrderList.DeleteCurrentNode();
				break;
			}

			m_xWndOrderList.MoveNextNode();
		}
	}	
}


/******************************************************************************************************************

	함수명 : CInterface::WindowActivate()

	작성자 : 
	작성일 : 

	목적   : nID인 윈도우를 윈도우리스트에 추가시키거나 삭제시키며, 추가의 경우, 윈도우의 상태를 최상위 상태로 세팅한다.
			 윈도우가 키입력을 받아서 화면에 나올때 호출하는 함수이다.
	입력   : INT nID
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CInterface::WindowActivate(INT nID)
{
	// 새로운 윈도우에 포커스를 주기위해서 모든 윈도우의 포커스를 FALSE시켜준다.
	BOOL bRet = FALSE;

	AllWindowsFocusOff();

	switch ( nID )
	{
	case _WND_ID_INVENTORY:
		{
			if ( m_xInventoryWnd.GetGameWndActive() )
			{
				DeleteWindowToList(_WND_ID_INVENTORY);
				m_xInventoryWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				AddWindowToList(_WND_ID_INVENTORY);
				m_xInventoryWnd.SetGameWndActive(TRUE);
				m_xInventoryWnd.SetInvenType(_INVEN_TYPE_BAG);
				m_xInventoryWnd.InitParkItem();
				bRet = TRUE;
			}
		}
		break;
	case _WND_ID_STATUS:
		{
			if ( m_xStatusWnd.GetGameWndActive() )
			{
				DeleteWindowToList(_WND_ID_STATUS);
				m_xStatusWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				AddWindowToList(_WND_ID_STATUS);
				m_xStatusWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;
	case _WND_ID_STORE:
		{
			if ( m_xStoreWnd.GetGameWndActive() )
			{
				DeleteWindowToList(_WND_ID_STORE);
				m_xStoreWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				AddWindowToList(_WND_ID_STORE);
				m_xStoreWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;
	case _WND_ID_EXCHANGE:
		{
			if ( m_xExchangeWnd.GetGameWndActive() )
			{
				DeleteWindowToList(_WND_ID_EXCHANGE);
				m_xExchangeWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				AddWindowToList(_WND_ID_EXCHANGE);
				m_xExchangeWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;
	case _WND_ID_QUEST:
		{
			if ( m_xNPCWnd.GetGameWndActive() )
			{
				bRet = FALSE;
			}
			else
			{
				g_xClientSocket.SendSay (g_xMsg.GetMsg(2650));
				bRet = TRUE;
			}
		}
		break;
	case _WND_ID_OPTION:
		{
			if ( m_xOptionWnd.GetGameWndActive() )
			{
				DeleteWindowToList(_WND_ID_OPTION);
				m_xOptionWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				AddWindowToList(_WND_ID_OPTION);
				m_xOptionWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;
	case _WND_ID_SETTING:
		{
			if ( m_xSettingWnd.GetGameWndActive() )
			{
				DeleteWindowToList(_WND_ID_SETTING);
				m_xSettingWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				AddWindowToList(_WND_ID_SETTING);
				m_xSettingWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;
	case _WNDIMGIDX_EXIT:
		{
			if ( m_xGameOverWnd.GetGameWndActive() )
			{
				DeleteWindowToList(_WNDIMGIDX_EXIT);
				m_xGameOverWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				AddWindowToList(_WNDIMGIDX_EXIT);
				m_xGameOverWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;
	case _WND_ID_HORSE:
		{
			if ( m_xHorseWnd.GetGameWndActive() )
			{
				DeleteWindowToList(_WND_ID_HORSE);
				m_xHorseWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				AddWindowToList(_WND_ID_HORSE);
				m_xHorseWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;

	case _WND_ID_MAGIC:
		{
			if ( m_xMagicWnd.GetGameWndActive() )
			{
				DeleteWindowToList(_WND_ID_MAGIC);
				m_xMagicWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				AddWindowToList(_WND_ID_MAGIC);
				m_xMagicWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;

	case _WND_ID_GUILD:
		{
			if ( m_xGuildWnd.GetGameWndActive() )
			{
				DeleteWindowToList(_WND_ID_GUILD);
				m_xGuildWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				g_xClientSocket.SendGuildHome();
				AddWindowToList(_WND_ID_GUILD);
				m_xGuildWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;
	case _WND_ID_GROUP:
		{
			if ( m_xGroupWnd.GetGameWndActive() )
			{
				DeleteWindowToList(_WND_ID_GROUP);
				m_xGroupWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				AddWindowToList(_WND_ID_GROUP);
				m_xGroupWnd.SetGameWndActive(TRUE);
				if ( m_xGroupWnd.m_bAllowGroup )
				{
					m_xGroupWnd.m_xGroupBtn[_BTN_ID_GROUPICON].ResetGameBtn(177, 177, 177);
				}
				else
				{
					m_xGroupWnd.m_xGroupBtn[_BTN_ID_GROUPICON].ResetGameBtn(178, 178, 178);
				}
				bRet = TRUE;
			}
		}
		break;
	case _WND_ID_USERSTATE:
		{
			if ( m_xUserStateWnd.GetGameWndActive() )
			{
				DeleteWindowToList(_WND_ID_USERSTATE);
				m_xUserStateWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				AddWindowToList(_WND_ID_USERSTATE);
				m_xUserStateWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;
	case _WND_ID_SIEGE:
		{
			if ( m_xSiegeWnd.GetGameWndActive() )
			{
				DeleteWindowToList(_WND_ID_SIEGE);
				m_xSiegeWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				AddWindowToList(_WND_ID_SIEGE);
				m_xSiegeWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;
	case _WND_ID_MAGICSHORTCUT:
		{
			if ( m_xMagicShortcutWnd.GetGameWndActive() )
			{
				DeleteWindowToList(_WND_ID_MAGICSHORTCUT);
				m_xMagicShortcutWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				AddWindowToList(_WND_ID_MAGICSHORTCUT);
				m_xMagicShortcutWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;
	case _WND_ID_USERMARKET:
		{
			if ( m_xMarketWnd.GetGameWndActive() )
			{
				m_xMarketWnd.CloseMarketWnd();
				bRet = FALSE;
			}
			else
			{
				AddWindowToList(_WND_ID_USERMARKET);
				m_xMarketWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;
	case _WND_ID_USERMARKETUP:
		{
			if ( m_xMarketUpWnd.GetGameWndActive() )
			{
				m_xMarketUpWnd.CloseMarketUpWnd();
				bRet = FALSE;
			}
			else
			{
				if ( !m_xInventoryWnd.GetGameWndActive() )
					WindowActivate(_WND_ID_INVENTORY);

				AddWindowToList(_WND_ID_USERMARKETUP);
				m_xMarketUpWnd.SetGameWndActive(TRUE);

				if ( m_xMarketUpWnd.mUserMarketUp_hDescEdit )
				{
					ShowWindow(m_xMarketUpWnd.mUserMarketUp_hDescEdit, SW_SHOW);
					UpdateWindow(m_xMarketUpWnd.mUserMarketUp_hDescEdit);

					MoveWindow(m_xMarketUpWnd.mUserMarketUp_hDescEdit, g_xMainWnd.m_rcWindow.left + m_xMarketUpWnd.mUserMarketUp_rcEditBox.left, 
	 						   g_xMainWnd.m_rcWindow.top + m_xMarketUpWnd.mUserMarketUp_rcEditBox.top, 
							   m_xMarketUpWnd.mUserMarketUp_rcEditBox.right - m_xMarketUpWnd.mUserMarketUp_rcEditBox.left, 
							   m_xMarketUpWnd.mUserMarketUp_rcEditBox.bottom - m_xMarketUpWnd.mUserMarketUp_rcEditBox.top, TRUE);

					SetFocus(m_xMarketUpWnd.mUserMarketUp_hDescEdit);
				}

				g_xChatEditBox.SetEnterUse(FALSE);
				bRet = TRUE;
			}
		}
		break;
	case _WND_ID_MESSENGER:
		{
			if ( m_xMessengerWnd.GetGameWndActive() )
			{
				DeleteWindowToList(_WND_ID_MESSENGER);
				m_xMessengerWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				AddWindowToList(_WND_ID_MESSENGER);
				m_xMessengerWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;
	case _WND_ID_UTIL:
		{
			if ( m_xUtilWnd.GetGameWndActive() )
			{
				DeleteWindowToList(_WND_ID_UTIL);
				m_xUtilWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				AddWindowToList(_WND_ID_UTIL);
				m_xUtilWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;
	case _WND_ID_VIEWMINIMAP:
		{
			if ( m_xViewMiniMapWnd.GetGameWndActive() )
			{
				DeleteWindowToList(_WND_ID_VIEWMINIMAP);
				m_xViewMiniMapWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				m_xViewMiniMapWnd.ReadMapNameFromMIF();
				AddWindowToList(_WND_ID_VIEWMINIMAP);
				m_xViewMiniMapWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;
	case _WND_ID_FACEIMGUP:
		{
			if ( m_xFaceImgUpWnd.GetGameWndActive() )
			{
				m_xFaceImgUpWnd.CloseFaceImgUpWnd();
//				DeleteWindowToList(_WND_ID_FACEIMGUP);
//				m_xFaceImgUpWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				AddWindowToList(_WND_ID_FACEIMGUP);
				m_xFaceImgUpWnd.FindJPGFile();
				m_xFaceImgUpWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;
	case _WND_ID_CHAT:
		{
			if ( m_xChatWnd.GetGameWndActive() )
			{
				DeleteWindowToList(_WND_ID_CHAT);
				m_xChatWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				AddWindowToList(_WND_ID_CHAT);
				m_xChatWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;
	case _WND_ID_NPCCHAT:
		{
			if ( m_xNPCWnd.GetGameWndActive() )
			{
				DeleteWindowToList(_WND_ID_NPCCHAT);
//				m_xNPCWnd.CloseWnd();
				m_xNPCWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				// 임시
				AddWindowToList(_WND_ID_NPCCHAT);
				m_xNPCWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;
	case _WND_ID_BELT:
		{
			if ( m_xBeltWnd.GetGameWndActive() )
			{
				DeleteWindowToList(_WND_ID_BELT);
				m_xBeltWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				AddWindowToList(_WND_ID_BELT);
				m_xBeltWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;
	case _WND_ID_NOTICEEDIT:
		{
			if ( m_xNoticeEditWnd.GetGameWndActive() )
			{
				if ( g_xGameProc.m_xInterface.m_bIsLargeChat == FALSE )
				{
					MoveWindow(g_xChatEditBox.GetSafehWnd(), 
							   g_xMainWnd.m_rcWindow.left+_NEW_INPUT_EDITWND_XPOS, g_xMainWnd.m_rcWindow.top+_NEW_INPUT_EDITWND_YPOS,
							   _NEW_INPUT_EDITWND_WIDTH, _NEW_INPUT_EDITWND_HEIGHT, TRUE);
				}
				else
				{
					MoveWindow(g_xChatEditBox.GetSafehWnd(), 
							   g_xMainWnd.m_rcWindow.left+_NEW_INPUT_EDITWND_XPOS, g_xMainWnd.m_rcWindow.top+_NEW_INPUT_LARGEEDITWND_YPOS,
							   _NEW_INPUT_LARGEEDITWND_WIDTH, _NEW_INPUT_EDITWND_HEIGHT, TRUE);
				}
				DeleteWindowToList(_WND_ID_NOTICEEDIT);
				m_xNoticeEditWnd.SetGameWndActive(FALSE);

				if ( m_xNoticeEditWnd.m_hNoticeEdit )
				{
					ShowWindow(m_xNoticeEditWnd.m_hNoticeEdit, SW_HIDE);
					SetWindowText(m_xNoticeEditWnd.m_hNoticeEdit, "");
				}
				SetFocus(g_xMainWnd.GetSafehWnd());
				g_xChatEditBox.SetEnterUse(TRUE);
				bRet = FALSE;
			}
			else
			{
				AddWindowToList(_WND_ID_NOTICEEDIT);
				m_xNoticeEditWnd.SetGameWndActive(TRUE);

				if ( m_xNoticeEditWnd.m_hNoticeEdit )
				{
					ShowWindow(m_xNoticeEditWnd.m_hNoticeEdit, SW_SHOW);
					UpdateWindow(m_xNoticeEditWnd.m_hNoticeEdit);

					MoveWindow(m_xNoticeEditWnd.m_hNoticeEdit, g_xMainWnd.m_rcWindow.left + m_xNoticeEditWnd.m_rcEditBox.left, 
	 						   g_xMainWnd.m_rcWindow.top + m_xNoticeEditWnd.m_rcEditBox.top, 
							   m_xNoticeEditWnd.m_rcEditBox.right - m_xNoticeEditWnd.m_rcEditBox.left, 
							   m_xNoticeEditWnd.m_rcEditBox.bottom - m_xNoticeEditWnd.m_rcEditBox.top, TRUE);

					SetFocus(m_xNoticeEditWnd.m_hNoticeEdit);
				}

				g_xChatEditBox.SetEnterUse(FALSE);
				bRet = TRUE;
			}
		}
		break;
	}

	return bRet;
}


/******************************************************************************************************************

	함수명 : CInterface::MoveTopWindow()

	작성자 : 
	작성일 : 

	목적   : 맨위의 윈도우를 마우스 좌표로 이동시킨다.
	입력   : POINT ptMouse
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CInterface::MoveTopWindow(POINT ptMouse)
{
	if ( m_xChatPopWnd.GetGameWndActive() && !IsTopWindow(_WND_ID_CHATPOP) )
	{
		ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_HIDE);
	}

	if ( m_xWndOrderList.GetCounter() != 0 )
	{
		INT* pnCurrID;
		m_xWndOrderList.MoveCurrentToTail();
		pnCurrID = m_xWndOrderList.GetCurrentData();
		if ( m_bMoveFocusedWnd )
		{
			switch ( *pnCurrID )
			{
			case _WND_ID_INVENTORY:
				m_xInventoryWnd.MoveGameWnd(ptMouse);
				break;
			case _WND_ID_STATUS:
				m_xStatusWnd.MoveGameWnd(ptMouse);
				break;
			case _WND_ID_STORE:
			{
				if ( m_xStoreWnd.CanMove(ptMouse) )
				{
					m_xStoreWnd.MoveGameWnd(ptMouse);
				}
				break;
			}
			case _WND_ID_EXCHANGE:
				m_xExchangeWnd.MoveGameWnd(ptMouse);
				break;
			case _WND_ID_GUILD:
				m_xGuildWnd.MoveGameWnd(ptMouse);
				break;
			case _WND_ID_GROUP:
				m_xGroupWnd.MoveGameWnd(ptMouse);
				break;
			case _WND_ID_USERSTATE:
				m_xUserStateWnd.MoveGameWnd(ptMouse);
				break;
			case _WND_ID_CHATPOP:
				m_xChatPopWnd.MoveGameWnd(ptMouse);
				ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_HIDE);
				break;
			case _WND_ID_NPCCHAT:
				m_xNPCWnd.MoveGameWnd(ptMouse);
				break;

			case _WND_ID_QUEST:
				m_xQuestWnd.MoveGameWnd(ptMouse);
				break;
			case _WND_ID_OPTION:
				m_xOptionWnd.MoveGameWnd(ptMouse);
				break;
			case _WND_ID_HORSE:
				m_xHorseWnd.MoveGameWnd(ptMouse);
				break;
			case _WND_ID_MAGIC:
				m_xMagicWnd.MoveGameWnd(ptMouse);
				break;
			case _WND_ID_NOTICEEDIT:
				m_xNoticeEditWnd.MoveGameWnd(ptMouse);
				break;
			case _WND_ID_BELT:
				m_xBeltWnd.MoveBeltWnd(ptMouse);
				break;
			case _WND_ID_SIEGE:
				m_xSiegeWnd.MoveGameWnd(ptMouse);
				break;
			case _WND_ID_MAGICSHORTCUT:
				m_xMagicShortcutWnd.MoveGameWnd(ptMouse);
				break;
			case _WND_ID_USERMARKET:
				m_xMarketWnd.MoveGameWnd(ptMouse);
				break;
			case _WND_ID_USERMARKETUP:
				m_xMarketUpWnd.MoveGameWnd(ptMouse);
				break;
			case _WND_ID_MESSENGER:
				m_xMessengerWnd.MoveGameWnd(ptMouse);
				break;
			case _WND_ID_FACEIMGUP:
				m_xFaceImgUpWnd.MoveGameWnd(ptMouse);
				break;
			case _WND_ID_UTIL:
				m_xUtilWnd.MoveGameWnd(ptMouse);
				break;
			case _WND_ID_VIEWMINIMAP:
				m_xViewMiniMapWnd.MoveGameWnd(ptMouse);
				break;
			case _WND_ID_CHAT:
				m_xChatWnd.MoveChatWnd(ptMouse);
				m_xChatWnd.MoveEditBox();
				break;
			case _WND_ID_SETTING:
				m_xSettingWnd.MoveGameWnd(ptMouse);
				break;
			}
		}
	}
}



/******************************************************************************************************************

	함수명 : CInterface::WindowFocusChanged()

	작성자 : 
	작성일 : 

	목적   : 윈도우 영역으로 마우스 클릭이 되면 현재 Top 윈도우를 마우스 클릭 윈도우로 바꿔주고 그윈도우로 포커스를 맞춰준다.
	입력   : INT nID
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CInterface::WindowFocusChangedAndSetReadyMove(INT nID, POINT ptMouse)
{
	if ( m_xWndOrderList.GetCounter() != 0 )
	{
		AllWindowsFocusOff();

		DeleteWindowToList(nID);
		AddWindowToList(nID);
		// 마우스 클릭이 된상태이면 이동시킬 준비가 된상태이다.
		m_bMoveFocusedWnd = TRUE;

		switch ( nID )
		{
		case _WND_ID_INVENTORY:
			m_xInventoryWnd.SetGameWndFocused(TRUE);
			m_xInventoryWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_STATUS:
			m_xStatusWnd.SetGameWndFocused(TRUE);
			m_xStatusWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_STORE:
		{
			if ( m_xStoreWnd.CanMove( ptMouse) )
			{
				m_xStoreWnd.SetGameWndFocused(TRUE);
				m_xStoreWnd.SetReadyMove(ptMouse);
			}
			break;
		}
		case _WND_ID_EXCHANGE:
			m_xExchangeWnd.SetGameWndFocused(TRUE);
			m_xExchangeWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_GUILD:
			m_xGuildWnd.SetGameWndFocused(TRUE);
			m_xGuildWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_GROUP:
			m_xGroupWnd.SetGameWndFocused(TRUE);
			m_xGroupWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_USERSTATE:
			m_xUserStateWnd.SetGameWndFocused(TRUE);
			m_xUserStateWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_CHATPOP:
			m_xChatPopWnd.SetGameWndFocused(TRUE);
			m_xChatPopWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_NPCCHAT:
			m_xNPCWnd.SetGameWndFocused(TRUE);
			m_xNPCWnd.SetReadyMove(ptMouse);
			break;

		case _WND_ID_QUEST:
			m_xQuestWnd.SetGameWndFocused(TRUE);
			m_xQuestWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_OPTION:
			m_xOptionWnd.SetGameWndFocused(TRUE);
			m_xOptionWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_HORSE:
			m_xHorseWnd.SetGameWndFocused(TRUE);
			m_xHorseWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_MAGIC:
			m_xMagicWnd.SetGameWndFocused(TRUE);
			m_xMagicWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_BELT:
			m_xBeltWnd.SetGameWndFocused(TRUE);
			m_xBeltWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_SIEGE:
			m_xSiegeWnd.SetGameWndFocused(TRUE);
			m_xSiegeWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_MAGICSHORTCUT:
			m_xMagicShortcutWnd.SetGameWndFocused(TRUE);
			m_xMagicShortcutWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_USERMARKET:
			m_xMarketWnd.SetGameWndFocused(TRUE);
			m_xMarketWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_USERMARKETUP:
			m_xMarketUpWnd.SetGameWndFocused(TRUE);
			m_xMarketUpWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_MESSENGER:
			m_xMessengerWnd.SetGameWndFocused(TRUE);
			m_xMessengerWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_FACEIMGUP:
			m_xFaceImgUpWnd.SetGameWndFocused(TRUE);
			m_xFaceImgUpWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_UTIL:
			m_xUtilWnd.SetGameWndFocused(TRUE);
			m_xUtilWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_VIEWMINIMAP:
			m_xViewMiniMapWnd.SetGameWndFocused(TRUE);
			m_xViewMiniMapWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_CHAT:
			m_xChatWnd.SetGameWndFocused(TRUE);
			m_xChatWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_SETTING:
			m_xSettingWnd.SetGameWndFocused(TRUE);
			m_xSettingWnd.SetReadyMove(ptMouse);
			break;
		case _WNDIMGIDX_EXIT:
			m_xGameOverWnd.SetGameWndFocused(TRUE);
			m_xGameOverWnd.SetReadyMove(ptMouse);
			break;			
		}
	}	
}


VOID CInterface::AllWindowsFocusOff()
{
	// 쪽지창 겹침
	m_xInterBtnofNewMessage.m_bBtnState = _BTN_STATE_NORMAL;

	if ( m_xWndOrderList.GetCounter() != 0 )
	{
		m_xWndOrderList.MoveCurrentToTop();

		INT* pnCurrID;
		for ( INT nCnt = 0; nCnt < m_xWndOrderList.GetCounter(); nCnt++ )
		{
			pnCurrID = m_xWndOrderList.GetCurrentData();

			switch ( *pnCurrID )
			{
			case _WND_ID_INVENTORY:
				m_xInventoryWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_STATUS:
				m_xStatusWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_STORE:
				m_xStoreWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_EXCHANGE:
				m_xExchangeWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_GUILD:
				m_xGuildWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_GROUP:
				m_xGroupWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_USERSTATE:
				m_xUserStateWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_CHATPOP:
				m_xChatPopWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_NPCCHAT:
				m_xNPCWnd.SetGameWndFocused(FALSE);
				break;

			case _WND_ID_QUEST:
				m_xQuestWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_OPTION:
				m_xOptionWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_HORSE:
				m_xHorseWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_MAGIC:
				m_xMagicWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_BELT:
				m_xBeltWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_SIEGE:
				m_xSiegeWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_MAGICSHORTCUT:
				m_xMagicShortcutWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_USERMARKET:
				m_xMarketWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_USERMARKETUP:
				m_xMarketUpWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_MESSENGER:
				m_xMessengerWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_FACEIMGUP:
				m_xFaceImgUpWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_UTIL:
				m_xUtilWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_VIEWMINIMAP:
				m_xViewMiniMapWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_CHAT:
				m_xChatWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_SETTING:
				m_xSettingWnd.SetGameWndFocused(FALSE);
				break;
			case _WNDIMGIDX_EXIT:
				m_xGameOverWnd.SetGameWndFocused(FALSE);
				break;
			}
		}
	}
}

BOOL CInterface::IsTopWindow(INT nID)
{
	if ( m_nTopWndID == nID )
		return TRUE;
	else
		return FALSE;
/*	if ( m_xWndOrderList.GetCounter() != 0 )
	{
		INT* pnCurrID;
		m_xWndOrderList.MoveCurrentToTail();
		pnCurrID = m_xWndOrderList.GetCurrentData();

		if ( nID == *pnCurrID )
			return TRUE;
	}
	return FALSE;
*/
}








///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 메시지 입력관련부분/////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CInterface::OnRButtonDown(POINT ptMouse)
{
/*	if ( SetCaputeString(ptMouse) )
	{
		return TRUE;
	}
*/
	INT nInterfaceWndInRect;
	nInterfaceWndInRect = GetWindowInMousePos(ptMouse);

	if ( nInterfaceWndInRect != -1 )
	{
		switch ( nInterfaceWndInRect )
		{
		case _WND_ID_INVENTORY:
			if ( m_xInventoryWnd.OnRButtonDown(&m_stCommonItem, ptMouse) )
				return TRUE;
			break;
		}
	}

	return FALSE;
}







/******************************************************************************************************************

	함수명 : CInterface::OnLButtonDown()

 	작성자 : 
	작성일 : 

	목적   : Mouse LButtonDown이 일어났을때 인터페이스에서 할일을 정의한다.
	입력   : POINT ptMouse
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CInterface::OnLButtonDown(POINT ptMouse)
{
	if ( m_xGameOverWnd.GetGameWndActive() )
	{
		m_xGameOverWnd.OnLButtonDown(ptMouse);
		return TRUE;
	}

	if ( m_xNoticeEditWnd.GetGameWndActive() )
	{
		m_xNoticeEditWnd.OnLButtonDown(ptMouse);
		return TRUE;
	}

	INT nInterfaceWndInRect;
	nInterfaceWndInRect = GetWindowInMousePos(ptMouse);

	if ( nInterfaceWndInRect != -1 )
	{
		switch ( nInterfaceWndInRect )
		{
		case _WND_ID_INVENTORY:
			if ( !m_xInventoryWnd.OnLButtonDown(&m_stCommonItem, ptMouse) )
				WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
			break;
		case _WND_ID_STATUS:
			if ( !m_xStatusWnd.OnLButtonDown(&m_stCommonItem, ptMouse) )
				WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
			break;
		case _WND_ID_STORE:
			if ( !m_xStoreWnd.OnLButtonDown(ptMouse) )
				WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
			break;
		case _WND_ID_EXCHANGE:
			if ( !m_xExchangeWnd.OnLButtonDown(ptMouse) )
				WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
			break;
		case _WND_ID_GUILD:
			if ( !m_xGuildWnd.OnLButtonDown(ptMouse) )
				WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
			break;
		case _WND_ID_GROUP:
			if ( !m_xGroupWnd.OnLButtonDown(ptMouse) )
				WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
			break;
		case _WND_ID_USERSTATE:
			if ( !m_xUserStateWnd.OnLButtonDown(ptMouse) )
				WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
			break;
		case _WND_ID_CHATPOP:
			if ( !m_xChatPopWnd.OnLButtonDown(ptMouse) )
				WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
			break;
		case _WND_ID_NPCCHAT:
			if ( !m_xNPCWnd.OnLButtonDown(ptMouse) )
				WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
			break;
		case _WND_ID_QUEST:
			if ( !m_xQuestWnd.OnLButtonDown(ptMouse) )
				WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
			break;
		case _WND_ID_OPTION:
			if ( !m_xOptionWnd.OnLButtonDown(ptMouse) )
				WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
			break;
		case _WND_ID_HORSE:
			if ( !m_xHorseWnd.OnLButtonDown(ptMouse) )
				WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
			break;
		case _WND_ID_MAGIC:
			if ( !m_xMagicWnd.OnLButtonDown(ptMouse) )
				WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
			break;
		case _WND_ID_BELT:
			if ( !m_xBeltWnd.OnLButtonDown(ptMouse) )
				WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
			break;
		case _WND_ID_SIEGE:
			if ( !m_xSiegeWnd.OnLButtonDown(ptMouse) )
				WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
			break;
		case _WND_ID_MAGICSHORTCUT:
			if ( !m_xMagicShortcutWnd.OnLButtonDown(ptMouse) )
				WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
			break;
		case _WND_ID_USERMARKET:
			if ( !m_xMarketWnd.OnLButtonDown(&m_stCommonItem, ptMouse) )
				WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
			break;
		case _WND_ID_USERMARKETUP:
			if ( !m_xMarketUpWnd.OnLButtonDown(&m_stCommonItem, ptMouse) )
				WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
			break;
		case _WND_ID_MESSENGER:
			if ( !m_xMessengerWnd.OnLButtonDown(&m_stCommonItem, ptMouse) )
				WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
			break;
		case _WND_ID_FACEIMGUP:
			if ( !m_xFaceImgUpWnd.OnLButtonDown(ptMouse) )
				WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
			break;
		case _WND_ID_UTIL:
			if ( !m_xUtilWnd.OnLButtonDown(ptMouse) )
				WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
			break;
		case _WND_ID_VIEWMINIMAP:
			if ( !m_xViewMiniMapWnd.OnLButtonDown(ptMouse) )
				WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
			break;
		case _WND_ID_CHAT:
			if ( !m_xChatWnd.OnLButtonDown(ptMouse) )
				WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
			break;
		case _WND_ID_SETTING:
			if ( !m_xSettingWnd.OnLButtonDown(ptMouse) )
				WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
			break;
		case _WNDIMGIDX_EXIT:
			if ( !m_xGameOverWnd.OnLButtonDown(ptMouse) )
				WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
			break;
		}

		if ( nInterfaceWndInRect != _WND_ID_STORE )
		{
			return TRUE;
		}
		else
		{
			if ( m_xStoreWnd.CanMove(ptMouse) )
			{
				return TRUE;
			}
		}
	}
	else
	{
		AllWindowsFocusOff();
	}

/*	if ( SetCaputeString(ptMouse) )
	{
		return TRUE;
	}
*/
	for( INT nCnt = 0; nCnt < _MAX_INTER_BTN; nCnt++ )
	{
		if ( m_xInterBtn[nCnt].OnLButtonDown(ptMouse) )
		{
			return TRUE;
		}
	}

//	if ( m_bHasSiege == TRUE )
//	{
//		if ( m_xInterBtnofSiege.OnLButtonDown(ptMouse) )
//		{
//			return TRUE;
//		}
//	}

	if ( m_bHasNewMessage == TRUE )
	{
		if ( m_xInterBtnofNewMessage.OnLButtonDown(ptMouse) )
		{
			return TRUE;
		}
	}

	if ( PtInRect(&m_rcLogo, ptMouse) && m_nInformationMode != _INFO_CHAR )
	{
		m_bIsMoving = TRUE;
		m_bIsDown = FALSE;
		m_nInformationMode = !m_nInformationMode;
		return TRUE;
	}

	if ( PtInRect(&m_rcCharFace, ptMouse) && m_nInformationMode == _INFO_CHAR )
	{
		m_bIsMoving = TRUE;
		m_bIsDown = TRUE;
		return TRUE;
	}

	if ( PtInRect(&m_rcAcnum, ptMouse) )
	{
		m_bAcShow = !m_bAcShow;
		m_xOptionWnd.SetIniFile();
	}

	if ( PtInRect(&m_rcDcnum, ptMouse) )
	{
		m_bDcScMcShow++;
		if ( m_bDcScMcShow > 2 )
			m_bDcScMcShow = 0;
		m_xOptionWnd.SetIniFile();
	}
	
	//-----------------------------------------------------------------------------------------------------------------
	// 벨트 영역.
	INT nBeltInventoryNum = GetBeltNum(ptMouse);
	//-----------------------------------------------------------------------------------------------------------------
	if ( nBeltInventoryNum != -1 )
	{
		return TRUE;
	}
	//-----------------------------------------------------------------------------------------------------------------

	if ( m_bViewMiniMap && m_xMiniMap.OnLButtonDown(ptMouse) )
	{
		return TRUE;
	}

	return FALSE;
}



/******************************************************************************************************************

	함수명 : CInterface::OnLButtonUp()

	작성자 : 
	작성일 : 

	목적   : Mouse LButtonUp이 일어났을때 인터페이스에서 할일을 정의한다.
	입력   : POINT ptMouse
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CInterface::OnLButtonUp(POINT ptMouse)
{
	m_bMoveFocusedWnd = FALSE;

	if ( m_xNoticeEditWnd.GetGameWndActive() )
	{
		if ( m_xNoticeEditWnd.OnLButtonUp(ptMouse) )
		{
			WindowActivate(_WND_ID_NOTICEEDIT);
		}
		return TRUE;
	}

	INT nInterfaceWndInRect;
	nInterfaceWndInRect = GetWindowInMousePos(ptMouse);

	if ( nInterfaceWndInRect == _WND_ID_STORE )
	{
		if ( !m_xStoreWnd.CanMove(ptMouse) )
		{
			nInterfaceWndInRect = -1;
		}
	}

	// 각 윈도우의 OnLButtonUp의 리턴값이 TRUE이면 윈도우즈는 Close된다.
	if ( nInterfaceWndInRect != -1 )
	{
		switch ( nInterfaceWndInRect )
		{
			case _WND_ID_INVENTORY:		
			{
				if ( m_xInventoryWnd.OnLButtonUp(&m_stCommonItem, ptMouse) && CanViewModeChange() )
				{
					WindowActivate(_WND_ID_INVENTORY);		
					SetViewMode();
				}
				break;
			}
			case _WND_ID_STATUS:
			{
				if ( m_xStatusWnd.OnLButtonUp(&m_stCommonItem, ptMouse) && CanViewModeChange() )
				{
					WindowActivate(_WND_ID_STATUS);		
					SetViewMode();
				}
				break;
			}
			case _WND_ID_STORE:			if ( m_xStoreWnd.OnLButtonUp(ptMouse) )							WindowActivate(_WND_ID_STORE);			break;
			
			case _WND_ID_EXCHANGE:		if ( m_xExchangeWnd.OnLButtonUp(&m_stCommonItem, ptMouse) )		WindowActivate(_WND_ID_EXCHANGE);		break;
			case _WND_ID_GUILD:			if ( m_xGuildWnd.OnLButtonUp(ptMouse) )							WindowActivate(_WND_ID_GUILD);			break;
			case _WND_ID_GROUP:			if ( m_xGroupWnd.OnLButtonUp(ptMouse) )							WindowActivate(_WND_ID_GROUP);			break;
			case _WND_ID_USERSTATE:		if ( m_xUserStateWnd.OnLButtonUp(ptMouse) )						WindowActivate(_WND_ID_USERSTATE);		break;
			case _WND_ID_CHATPOP:		if ( m_xChatPopWnd.OnLButtonUp(ptMouse) )						WindowActivate(_WND_ID_CHATPOP);		break;

			case _WND_ID_QUEST:			if ( m_xQuestWnd.OnLButtonUp(ptMouse) )							WindowActivate(_WND_ID_QUEST);			break;
			case _WND_ID_OPTION:		if ( m_xOptionWnd.OnLButtonUp(ptMouse) )						WindowActivate(_WND_ID_OPTION);			break;
			case _WND_ID_HORSE:			if ( m_xHorseWnd.OnLButtonUp(ptMouse) )							WindowActivate(_WND_ID_HORSE);			break;

			case _WND_ID_MAGIC:			if ( m_xMagicWnd.OnLButtonUp(ptMouse) )							WindowActivate(_WND_ID_MAGIC);			break;
			
			case _WND_ID_NPCCHAT:		if ( m_xNPCWnd.OnLButtonUp(ptMouse) )							g_xGameProc.CloseNPCWindow();			break;
			
			case _WND_ID_BELT:			if ( m_xBeltWnd.OnLButtonUp(&m_stCommonItem, ptMouse) )			WindowActivate(_WND_ID_BELT);		break;
			case _WND_ID_SIEGE:			if ( m_xSiegeWnd.OnLButtonUp(&m_stCommonItem, ptMouse) )		WindowActivate(_WND_ID_SIEGE);		break;
			case _WND_ID_MAGICSHORTCUT:	if ( m_xMagicShortcutWnd.OnLButtonUp(ptMouse) )					WindowActivate(_WND_ID_MAGICSHORTCUT);		break;
			case _WND_ID_USERMARKET:	if ( m_xMarketWnd.OnLButtonUp(&m_stCommonItem, ptMouse) )		WindowActivate(_WND_ID_USERMARKET);		break;
			case _WND_ID_USERMARKETUP:	if ( m_xMarketUpWnd.OnLButtonUp(&m_stCommonItem, ptMouse) )		WindowActivate(_WND_ID_USERMARKETUP);		break;
			case _WND_ID_MESSENGER:		if ( m_xMessengerWnd.OnLButtonUp(&m_stCommonItem, ptMouse) )	WindowActivate(_WND_ID_MESSENGER);		break;
			case _WND_ID_FACEIMGUP:		if ( m_xFaceImgUpWnd.OnLButtonUp(ptMouse) )						WindowActivate(_WND_ID_MESSENGER);		break;
			case _WND_ID_UTIL:			if ( m_xUtilWnd.OnLButtonUp(ptMouse) )							WindowActivate(_WND_ID_UTIL);		break;
			case _WND_ID_VIEWMINIMAP:	if ( m_xViewMiniMapWnd.OnLButtonUp(ptMouse) )					WindowActivate(_WND_ID_VIEWMINIMAP);		break;
			case _WND_ID_CHAT:			if ( m_xChatWnd.OnLButtonUp(ptMouse) )							WindowActivate(_WND_ID_CHAT);		break;
			case _WND_ID_SETTING:		if ( m_xSettingWnd.OnLButtonUp(ptMouse) )						WindowActivate(_WND_ID_SETTING);		break;
			case _WNDIMGIDX_EXIT:		if ( m_xGameOverWnd.OnLButtonUp(ptMouse) )						WindowActivate(_WNDIMGIDX_EXIT);		break;
		}
		return TRUE;
	}

	for( INT nCnt = 0; nCnt < _MAX_INTER_BTN; nCnt++ )
	{
		if ( m_xInterBtn[nCnt].OnLButtonUp(ptMouse) )
		{
			switch ( nCnt )
			{
				case _3rd_BTN_ID_QUEST:		WindowActivate(_WND_ID_QUEST);					break;
				case _3rd_BTN_ID_OPTION:	WindowActivate(_WND_ID_SETTING);					break;
				case _3rd_BTN_ID_CHANGE:
				{
					CActor* pxActor = g_xGameProc.FrontActor(g_xGameProc.m_xMyHero.m_nPosX, g_xGameProc.m_xMyHero.m_nPosY, g_xGameProc.m_xMyHero.m_bCurrDir, 1);

					if ( pxActor )
					{
						m_xExchangeWnd.m_xExchangeBtn.ResetGameBtn(372, 373, -1);
						g_xClientSocket.SendDealTry(pxActor->m_szName);
					}
					break;
				}

				case _3rd_BTN_ID_BELT:		WindowActivate(_WND_ID_BELT);					break;
				case _3rd_BTN_ID_BAG:
				{
					if ( CanViewModeChange() )
					{
						WindowActivate(_WND_ID_INVENTORY);
						SetViewMode();

						m_xInventoryWnd.SetInvenType(_INVEN_TYPE_BAG);
					}
					break;
				}
				case _3rd_BTN_ID_CHAR:
				{
					if ( CanViewModeChange() )
					{
						WindowActivate(_WND_ID_STATUS);
						SetViewMode();
					}
					break;
				}
				case _3rd_BTN_ID_MUGONG:
					if ( m_xMagicWnd.GetGameWndActive() )
					{
						WindowActivate(_WND_ID_MAGIC);
						if ( m_xMagicShortcutWnd.GetGameWndActive() )
						{
							WindowActivate(_WND_ID_MAGICSHORTCUT);
						}
					}
					else
					{
						WindowActivate(_WND_ID_MAGIC);
						if ( !m_xMagicShortcutWnd.GetGameWndActive() )
						{
							WindowActivate(_WND_ID_MAGICSHORTCUT);
						}
					}
					m_xMagicWnd.m_bWantSetKey = FALSE;
//					m_bShowKey = !m_bShowKey;
					break;
				case _3rd_BTN_ID_MINIMAP:
				{
					if ( timeGetTime() - m_dwQueryMsgTime > 100 )
					{
						if ( m_bViewMiniMap == FALSE )
						{
							g_xClientSocket.SendWantMMap();
							m_bReadyViewMap = TRUE;
						}
						else
						{
							m_bViewMiniMap = FALSE;
						}						
					}
					break;
				}
/*
				case _NEW_BTN_ID_LOGOUT:
				{
					if ( g_xGameProc.CanGameOut() )
					{
						g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_LOGOUT, _YESNO, g_xMsg.GetMsg(1065));
					}
					break;
				}
				case _NEW_BTN_ID_MESSENGER:
				{
					if ( m_bHasNewMessage == TRUE || m_xMessengerWnd.mMessenger_xReceivedMSGList.GetCount() == 0 )
						g_xClientSocket.SendRefreshMailBox(0);
					if ( !m_xMessengerWnd.GetGameWndActive() )
						WindowActivate(_WND_ID_MESSENGER);
					else
					{
						m_xMessengerWnd.CloseMessengerWnd();
					}
				}
				break;
#ifdef _DEBUG
				case _NEW_BTN_ID_HORSE:		WindowActivate(_WND_ID_UTIL);					break;
#else
//				case _NEW_BTN_ID_HORSE:		WindowActivate(_WND_ID_HORSE);					break;
#endif
				case _NEW_BTN_ID_GUILD:		
				{
					g_xClientSocket.SendGuildHome();
					break;
				}
				case _NEW_BTN_ID_GROUP:		WindowActivate(_WND_ID_GROUP);					break;
				case _NEW_BTN_ID_LARGECHAT:
					{
						ChangeChatSize();
					}
					break;
*/
/*				case _3rd_BTN_ID_EXIT:
				{
					 if ( g_xGameProc.CanGameOut() )
					 {
						 g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GAMEOVER, _YESNO, g_xMsg.GetMsg(2636));
					 }
					break;
				}
*/
/*				case _NEW_BTN_ID_MAGIC:
				{
					WindowActivate(_WND_ID_MAGIC);
					break;
				}
				case _NEW_BTN_ID_CHATDENY:
				{
					SetFocus(g_xChatEditBox.GetSafehWnd());
					ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);
					SetWindowText(g_xChatEditBox.GetSafehWnd(), g_xMsg.GetMsg(1072));
					INT nLen = strlen(g_xMsg.GetMsg(1072));
					SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETSEL, nLen , nLen);
					g_xChatEditBox.SetHanguelMode();
					break;
				}
				case _NEW_BTN_ID_CHATSHOUT:
				{
					SetFocus(g_xChatEditBox.GetSafehWnd());
					ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);
					SetWindowText(g_xChatEditBox.GetSafehWnd(), "!");
					INT nLen = strlen("!");
					SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETSEL, nLen , nLen);
					g_xChatEditBox.SetHanguelMode();
					break;
				}
				case _NEW_BTN_ID_CHATGROUP:
				{
					DWORD dwFont = GetChatColor(_CHAT_COLOR3);
					DWORD dwBack = GetChatColor(_CHAT_COLOR8);

					if (m_nChatMode != _CHAT_MODE_GROUP)
					{
						MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2633));
						m_nChatMode = _CHAT_MODE_GROUP;
						m_xInterBtn[ _NEW_BTN_ID_CHATGUILD].ChangeBtnTooltip(g_xMsg.GetMsg(2619));
						m_xInterBtn[ _NEW_BTN_ID_CHATGROUP].ChangeBtnTooltip(g_xMsg.GetMsg(2631));
						m_xInterBtn[ _NEW_BTN_ID_CHATGROUP].ResetGameBtn(1335, 1335, 1335);
						m_xInterBtn[ _NEW_BTN_ID_CHATGUILD].ResetGameBtn(1336, 1336, 1336);
					}
					else
					{
						MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2626));
						m_nChatMode = _CHAT_MODE_NORMAL;
						m_xInterBtn[ _NEW_BTN_ID_CHATGROUP].ChangeBtnTooltip(g_xMsg.GetMsg(2618));
						m_xInterBtn[ _NEW_BTN_ID_CHATGROUP].ResetGameBtn(1334, 1334, 1334);
					}
					break;
				}
				case _NEW_BTN_ID_CHATGUILD:
				{
					DWORD dwFont = GetChatColor(_CHAT_COLOR3);
					DWORD dwBack = GetChatColor(_CHAT_COLOR8);

					if (m_nChatMode != _CHAT_MODE_GUILD)
					{
						MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2635));
						m_nChatMode = _CHAT_MODE_GUILD;
						m_xInterBtn[ _NEW_BTN_ID_CHATGROUP].ChangeBtnTooltip(g_xMsg.GetMsg(2618));
						m_xInterBtn[ _NEW_BTN_ID_CHATGUILD].ChangeBtnTooltip(g_xMsg.GetMsg(2630));
						m_xInterBtn[ _NEW_BTN_ID_CHATGROUP].ResetGameBtn(1334, 1334, 1334);
						m_xInterBtn[ _NEW_BTN_ID_CHATGUILD].ResetGameBtn(1337, 1337, 1337);
					}
					else
					{
						MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2626));
						m_nChatMode = _CHAT_MODE_NORMAL;
						m_xInterBtn[ _NEW_BTN_ID_CHATGUILD].ChangeBtnTooltip(g_xMsg.GetMsg(2619));
						m_xInterBtn[ _NEW_BTN_ID_CHATGUILD].ResetGameBtn(1336, 1336, 1336);
					}
					break;
				}
				case _NEW_BTN_ID_CHATALLDENY:
				{
					if ( m_bChatallDeny == TRUE )
					{
						m_xInterBtn[ _NEW_BTN_ID_CHATALLDENY].ResetGameBtn(-1, -1, -1);
						m_xInterBtn[ _NEW_BTN_ID_CHATALLDENY].ChangeBtnTooltip(g_xMsg.GetMsg(2637));
					}
					else
					{
						m_xInterBtn[ _NEW_BTN_ID_CHATALLDENY].ResetGameBtn(1338, 1338, 1338);
						m_xInterBtn[ _NEW_BTN_ID_CHATALLDENY].ChangeBtnTooltip(g_xMsg.GetMsg(2638));
					}
					g_xClientSocket.SendSay (g_xMsg.GetMsg(1070));
					break;
				}
				case _NEW_BTN_ID_DENYGUILD:
				{
					if ( m_bDenyGuild == TRUE )
					{
						m_xInterBtn[ _NEW_BTN_ID_DENYGUILD].ResetGameBtn(-1, -1, -1);
						m_xInterBtn[ _NEW_BTN_ID_DENYGUILD].ChangeBtnTooltip(g_xMsg.GetMsg(2639));
					}
					else
					{
						m_xInterBtn[ _NEW_BTN_ID_DENYGUILD].ResetGameBtn(1340, 1340, 1340);
						m_xInterBtn[ _NEW_BTN_ID_DENYGUILD].ChangeBtnTooltip(g_xMsg.GetMsg(2640));
					}
					g_xClientSocket.SendSay (g_xMsg.GetMsg(1071));
					break;
				}
				case _NEW_BTN_ID_DENYSHOUT:
				{
					if ( m_bDenyShout == TRUE )
					{
						m_xInterBtn[ _NEW_BTN_ID_DENYSHOUT].ResetGameBtn(-1, -1, -1);
						m_xInterBtn[ _NEW_BTN_ID_DENYSHOUT].ChangeBtnTooltip(g_xMsg.GetMsg(2643));
					}
					else
					{
						m_xInterBtn[ _NEW_BTN_ID_DENYSHOUT].ResetGameBtn(1342, 1342, 1342);
						m_xInterBtn[ _NEW_BTN_ID_DENYSHOUT].ChangeBtnTooltip(g_xMsg.GetMsg(2644));
					}
					g_xClientSocket.SendSay (g_xMsg.GetMsg(1073));
				}
*/
			}
		}
	}

/*	if ( m_bHasSiege == TRUE )
	{
		if ( m_xInterBtnofSiege.OnLButtonUp(ptMouse) )
		{
			if (WindowActivate(_WND_ID_SIEGE) == TRUE )
			{
				g_xClientSocket.SendWantMMap();
			}
			else
			{
			}
			return FALSE;
		}
	}
*/
	if ( m_bHasNewMessage == TRUE )
	{
		if ( m_xInterBtnofNewMessage.OnLButtonUp(ptMouse) )
		{
			if ( !m_xMessengerWnd.GetGameWndActive() )
			{
				g_xClientSocket.SendRefreshMailBox(0);
				WindowActivate(_WND_ID_MESSENGER);
			}
			return FALSE;
		}
	}

	if ( PtInRect(&m_rcInfoModeChange, ptMouse) && m_bIsLargeChat == FALSE)
	{
		if ( m_xInterBtnFaceImgUp.OnLButtonUp(ptMouse) )
		{
			WindowActivate(_WND_ID_FACEIMGUP);
			return FALSE;
		}
	}

	if ( m_bViewMiniMap && m_xMiniMap.OnLButtonUp(ptMouse) )
	{
		return TRUE;
	}

/*
	if ( PtInRect(&m_rcLogo, ptMouse) && m_nInformationMode != _INFO_CHAR )
	{
		m_nInformationMode = !m_nInformationMode;
	}

	if ( PtInRect(&m_rcCharFace, ptMouse) && m_nInformationMode == _INFO_CHAR )
	{
		m_nInformationMode = !m_nInformationMode;
/*		if ( timeGetTime() - m_dwQueryMsgTime > 1000)
		{
			if ( m_nInformationMode == _INFO_CHAR )
			{
				g_xClientSocket.SendWantMMap();
				m_bReadyInforMap = TRUE;
				m_nInformationMode = !m_nInformationMode;
			}
			else
			{
				m_bViewMiniMapInMain = FALSE;
				m_nInformationMode = !m_nInformationMode;
			}

			CHAR	szVal[MAX_PATH];
			CHAR	szFileName[MAX_PATH];

			if ( GetCurrentDirectory(MAX_PATH, szFileName))
			{
				if ( szFileName[0] == '\0' )
					return TRUE;
				strcat(szFileName, "\\Config.ini");

				sprintf(szVal, "%d", m_nInformationMode );
				WritePrivateProfileString(SECTION_OPTIONS, KEY_INFORMATIONMODE, szVal, szFileName);		// Effect Sound On or Off
			}

		}

		return TRUE;
	}
*/

return FALSE;
}


/******************************************************************************************************************

	함수명 : CInterface::OnMouseMove()

	작성자 : 
	작성일 : 

	목적   : Mouse Move가 일어났을때 인터페이스에서 할일을 정의한다.
	입력   : POINT ptMouse
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CInterface::OnMouseMove(POINT ptMouse)
{
	if ( m_xGameOverWnd.GetGameWndActive() )
	{
		m_xGameOverWnd.OnMouseMove(ptMouse);
	}

	if ( m_xNoticeEditWnd.GetGameWndActive() )
	{
		m_xNoticeEditWnd.OnMouseMove(ptMouse);
	}

	INT nInterfaceWndInRect;
	nInterfaceWndInRect = GetWindowInMousePos(ptMouse);

	if ( nInterfaceWndInRect != -1 )
	{
		switch ( nInterfaceWndInRect )
		{
		case _WND_ID_INVENTORY:
			if ( m_xInventoryWnd.OnMouseMove(ptMouse) )
			{
				return TRUE;
			}
		case _WND_ID_STATUS:
			m_xStatusWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_STORE:
			if ( m_xStoreWnd.OnMouseMove(ptMouse) )
			{
				return TRUE;
			}
		case _WND_ID_EXCHANGE:
			m_xExchangeWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_GUILD:
			m_xGuildWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_GROUP:
			m_xGroupWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_USERSTATE:
			m_xUserStateWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_CHATPOP:
			m_xChatPopWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_QUEST:
			m_xQuestWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_OPTION:
			m_xOptionWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_HORSE:
			m_xHorseWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_MAGIC:
			m_xMagicWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_NPCCHAT:
			m_xNPCWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_BELT:
			m_xBeltWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_SIEGE:
			m_xSiegeWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_MAGICSHORTCUT:
			m_xMagicShortcutWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_USERMARKET:
			m_xMarketWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_USERMARKETUP:
			m_xMarketUpWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_MESSENGER:
			m_xMessengerWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_FACEIMGUP:
			m_xFaceImgUpWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_UTIL:
			m_xUtilWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_VIEWMINIMAP:
			m_xViewMiniMapWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_CHAT:
			m_xChatWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_SETTING:
			m_xSettingWnd.OnMouseMove(ptMouse);
			break;
		case _WNDIMGIDX_EXIT:
			m_xGameOverWnd.OnMouseMove(ptMouse);
			break;
		}
	}
	else
	{
		m_xGroupWnd.SetStatusBtnInit();
		m_xStatusWnd.SetStatusBtnInit();
		m_xStoreWnd.SetStatusBtnInit();
		m_xInventoryWnd.SetInvenBtnInit();
		m_xChatPopWnd.SetStatusBtnInit();
		m_xOptionWnd.SetStatusBtnInit();
		m_xGuildWnd.SetStatusBtnInit();
		m_xQuestWnd.SetStatusBtnInit();
		m_xHorseWnd.SetStatusBtnInit();
		m_xMagicWnd.SetStatusBtnInit();
		m_xExchangeWnd.SetStatusBtnInit();	
		m_xNPCWnd.SetStatusBtnInit();
		m_xUserStateWnd.SetStatusBtnInit();
		m_xNoticeEditWnd.SetStatusBtnInit();
		m_xBeltWnd.SetStatusBtnInit();

		// 쪽지 메시지와 세팅 윈도우의 닫기버튼 겹치 수정 2006.10.26

		// 세팅 윈도우의 닫기 버튼이 한번더 OnMouseMove 해주지 않으면 툴팁이 사라지지 않는 경우가 있다
		m_xSettingWnd.OnMouseMove( ptMouse );
		m_xInterBtnofNewMessage.OnMouseMove( ptMouse );
	}

	MoveTopWindow(ptMouse);

	if ( m_bViewMiniMap && m_xMiniMap.OnMouseMove(ptMouse) )
	{
		return TRUE;
	}

	for( INT nCnt = 0; nCnt < _MAX_INTER_BTN; nCnt++ )
	{
		m_xInterBtn[nCnt].OnMouseMove(ptMouse);
	}

//	m_xInterBtnofSiege.OnMouseMove(ptMouse);

	return FALSE;
}


BOOL CInterface::OnScrollDown()
{
	INT nInterfaceWndInRect;
	nInterfaceWndInRect = GetWindowInMousePos(g_xGameProc.m_ptMousePos);

	// 각 윈도우의 OnLButtonUp의 리턴값이 TRUE이면 윈도우즈는 Close된다.
	if ( nInterfaceWndInRect != -1 )
	{
		switch ( nInterfaceWndInRect )
		{
		case _WND_ID_INVENTORY:
			m_xInventoryWnd.OnScrollDown();
			break;
		case _WND_ID_NPCCHAT:
			m_xNPCWnd.OnScrollDown();
			break;
		case _WND_ID_CHATPOP:
			m_xChatPopWnd.OnScrollDown();
			break;
		case _WND_ID_EXCHANGE:
			m_xExchangeWnd.OnScrollDown();
			break;
		case _WND_ID_STORE:
			m_xStoreWnd.OnScrollDown();
			break;
		case _WND_ID_QUEST:
			m_xQuestWnd.OnScrollDown();
			break;
		case _WND_ID_GUILD:
			m_xGuildWnd.OnScrollDown();
			break;
		case _WND_ID_USERMARKET:
			m_xMarketWnd.OnScrollDown();
			break;
		case _WND_ID_MESSENGER:
			m_xMessengerWnd.OnScrollDown();
			break;
		case _WND_ID_FACEIMGUP:
			m_xFaceImgUpWnd.OnScrollDown();
			break;
		case _WND_ID_VIEWMINIMAP:
			m_xViewMiniMapWnd.OnScrollDown();
			break;
		case _WND_ID_MAGIC:
			m_xMagicWnd.OnScrollDown();
			break;
		case _WND_ID_CHAT:
			m_xChatWnd.OnScrollDown();
			break;
		}
	}	
	else
	{
		if (m_bIsLargeChat == TRUE)
		{
			if ( m_nFstLineInLarge > 0 )	
			{
				m_nFstLineInLarge--;
			}
		}
		else
		{
			if ( m_nFstLine > 0 )	
			{
				m_nFstLine--;
			}
		}
	}

	return TRUE;
}


BOOL CInterface::OnScrollUp()
{
	INT nInterfaceWndInRect;
	nInterfaceWndInRect = GetWindowInMousePos(g_xGameProc.m_ptMousePos);

	if ( nInterfaceWndInRect != -1 )
	{
		switch ( nInterfaceWndInRect )
		{
		case _WND_ID_INVENTORY:
			m_xInventoryWnd.OnScrollUp();
			break;
		case _WND_ID_NPCCHAT:
			m_xNPCWnd.OnScrollUp();
			break;
		case _WND_ID_CHATPOP:
			m_xChatPopWnd.OnScrollUp();
			break;
		case _WND_ID_EXCHANGE:
			m_xExchangeWnd.OnScrollUp();
			break;
		case _WND_ID_STORE:
			m_xStoreWnd.OnScrollUp();
			break;
		case _WND_ID_QUEST:
			m_xQuestWnd.OnScrollUp();
			break;
		case _WND_ID_GUILD:
			m_xGuildWnd.OnScrollUp();
			break;
		case _WND_ID_USERMARKET:
			m_xMarketWnd.OnScrollUp();
			break;
		case _WND_ID_MESSENGER:
			m_xMessengerWnd.OnScrollUp();
			break;
		case _WND_ID_FACEIMGUP:
			m_xFaceImgUpWnd.OnScrollUp();
			break;
		case _WND_ID_VIEWMINIMAP:
			m_xViewMiniMapWnd.OnScrollUp();
			break;
		case _WND_ID_MAGIC:
			m_xMagicWnd.OnScrollUp();
			break;
		case _WND_ID_CHAT:
			m_xChatWnd.OnScrollUp();
			break;
		}
	}
	else
	{
		if (m_bIsLargeChat == TRUE)
		{
			if ( m_nFstLineInLarge < (m_xLargeChatlist.GetCount()-1) )
			{
				m_nFstLineInLarge++;
			}
		}
		else
		{
			if ( m_nFstLine < (m_xChatlist.GetCount()-1) )
			{
				m_nFstLine++;
			}
		}
	}
	return TRUE;
}


BOOL CInterface::OnLButtonDoubleClick(POINT ptMouse)
{
	if ( IsTopWindow(m_xQuestWnd.m_nID) )
	{
		m_xQuestWnd.OnDblClick(ptMouse);
		return TRUE;
	}
	else if ( IsTopWindow(m_xStoreWnd.m_nID) )
	{
		m_xStoreWnd.OnLButtonDoubleClick(ptMouse);
		return TRUE;
	}
	else if ( IsTopWindow(m_xMagicWnd.m_nID) )
	{
		m_xMagicWnd.OnLButtonDoubleClick(ptMouse);
		return TRUE;
	}
	else if ( IsTopWindow(m_xMessengerWnd.m_nID) )
	{
		m_xMessengerWnd.OnLButtonDoubleClick(ptMouse);
		return TRUE;
	}
	else if ( IsTopWindow(m_xFaceImgUpWnd.m_nID) )
	{
		m_xFaceImgUpWnd.OnLButtonDoubleClick(ptMouse);
		return TRUE;
	}
	else if ( IsTopWindow(m_xUserStateWnd.m_nID) )
	{
		m_xUserStateWnd.OnLButtonDoubleClick(ptMouse);
		return TRUE;
	}

	m_xBeltWnd.OnLButtonDoubleClick(ptMouse);
	INT nBeltInventoryNum = GetBeltNum(ptMouse);

	if ( nBeltInventoryNum != -1 )
	{
		BYTE bStdMode = m_stCommonItem.xItem.m_stItemInfo.stStdItem.bStdMode;
		WORD wLooks   = m_stCommonItem.xItem.m_stItemInfo.stStdItem.wLooks;

/*		if ( bStdMode != 0 || 
			(bStdMode == 0 && timeGetTime() - m_xInventoryWnd.m_dwDLClickTime > 2000) || 
			(bStdMode == 0 && timeGetTime() - m_xInventoryWnd.m_dwDLClickTime > 1000 && (wLooks == 20 || wLooks == 21 || wLooks == 70)) 
		   )*/
		if ( (bStdMode != 0 && bStdMode != 3) ||
			((bStdMode == 0 || bStdMode == 3) && timeGetTime() - m_xInventoryWnd.m_dwDLClickTime > 2000) || // 물약류, 전서류...(2초지연)
			 (bStdMode == 0 && timeGetTime() - m_xInventoryWnd.m_dwDLClickTime > 1000 &&
			 (wLooks == 20 || wLooks == 21 || wLooks == 70 || wLooks == 25 || wLooks == 26 || wLooks == 27 || wLooks == 28 || wLooks == 35 || wLooks == 36 || wLooks == 37 || wLooks == 38
			 || wLooks == 63 || wLooks == 53 || wLooks == 32) ) // 선화수등..(1초지연)
		   ) // 2006.09.01 아이템 사용 예외처리 추가 - 대만작업으로 인함
		{
			if ( m_stCommonItem.bSetted && !m_stCommonItem.bWaitResponse && !m_stCommonItem.bIsEquipItem && g_xGameProc.m_bUseSpell == FALSE )
			{			
				if ( strcmp(m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(1050)) &&
					(bStdMode == 0 || bStdMode == 3) )
				{
					m_stCommonItem.bWaitResponse = TRUE;
					g_xClientSocket.SendItemIndex(CM_EAT, m_stCommonItem.xItem.m_stItemInfo.nMakeIndex, m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName);
					m_xInventoryWnd.m_dwDLClickTime = timeGetTime();
					return TRUE;
				}
			}
		}

		if ( bStdMode == 0 || bStdMode == 3 )
		{
			CHAR szSysMsg[MAX_PATH];
			if ( m_stCommonItem.bSetted )
			{
				sprintf(szSysMsg, g_xMsg.GetMsg(1051));
			}
			else
			{
				sprintf(szSysMsg, g_xMsg.GetMsg(1066), nBeltInventoryNum+1);
			}		
			m_xClientSysMsg.AddSysMsg(szSysMsg);
		}
	}

	return FALSE;
}


BOOL CInterface::OnKeyUp(WPARAM wParam, LPARAM lParam)
{
	switch ( wParam )
	{
	case 9 :
			g_xGameProc.m_bDrawGroundItemName = FALSE;
			break;
	case 192:
		{
			g_xGameProc.m_bAutoPickup = FALSE;
		}
		break;
	}

	return FALSE;
}

BOOL CInterface::CanViewModeChange()
{
	return TRUE;

	if ( timeGetTime() - m_dwViewModeClickTick > _VIEWMODE_CLICK_TIME )
	{
		m_dwViewModeClickTick = timeGetTime();
		return TRUE;
	}

	return FALSE;
}

VOID CInterface::SetViewMode()
{
	return;
}

BOOL CInterface::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	if ( m_xGameOverWnd.GetGameWndActive() )
	{
		return TRUE;
	}

	if ( m_xNoticeEditWnd.GetGameWndActive() )
	{
		return TRUE;
	}

	if ( m_xChatPopWnd.GetGameWndActive() && IsTopWindow(_WND_ID_CHATPOP) )
	{
		if ( m_xChatPopWnd.OnKeyDown(wParam, lParam) )
		{
			return TRUE;
		}
	}

	if ( m_xMarketWnd.GetGameWndActive() && IsTopWindow(_WND_ID_USERMARKET) )
	{
		if ( m_xMarketWnd.OnKeyDown(wParam, lParam) )
		{
			return TRUE;
		}
	}

	if ( m_xMessengerWnd.GetGameWndActive() && IsTopWindow(_WND_ID_MESSENGER) )
	{
		if ( m_xMessengerWnd.OnKeyDown(wParam, lParam) )
		{
			return TRUE;
		}
	}
	if ( wParam == VK_F1 )
	{
		if ( GetKeyState(VK_CONTROL) & 0x80 )
		{
			m_xMagicShortcutWnd.mMSCutwnd_nTabNum = 0;
			return TRUE;
		}
	}
	else if ( wParam == VK_F2 )
	{
		if ( GetKeyState(VK_CONTROL) & 0x80 )
		{
			m_xMagicShortcutWnd.mMSCutwnd_nTabNum = 1;
			return TRUE;
		}
	}
	else if ( wParam == VK_F3 )
	{
		if ( GetKeyState(VK_CONTROL) & 0x80 )
		{
			m_xMagicShortcutWnd.mMSCutwnd_nTabNum = 2;
			return TRUE;
		}
	}
	else if ( wParam == VK_F4 )
	{
		if ( GetKeyState(VK_CONTROL) & 0x80 )
		{
			m_xMagicShortcutWnd.mMSCutwnd_nTabNum = 3;
			return TRUE;
		}
	}

	INT nBeltInventoryNum = -1;
/*	if ( m_stCommonItem.bSetted && m_stCommonItem.bWaitResponse )
	{
		return TRUE;
	}
*/
	if ( HIBYTE(GetKeyState('W')) )
	{
//		if ( GetKeyState(VK_CONTROL) & 0x80 )
		{
			if ( CanViewModeChange() )
			{
				WindowActivate(_WND_ID_INVENTORY);
				SetViewMode();
				m_xInventoryWnd.SetInvenType(_INVEN_TYPE_BAG);
			}
		}
	}
	else if ( HIBYTE(GetKeyState('Q')) )
	{
//		if ( GetKeyState(VK_CONTROL) & 0x80 )
		{
			if ( CanViewModeChange() )
			{
				WindowActivate(_WND_ID_STATUS);
				SetViewMode();

//				m_xStatusWnd.SetStatusWndType(_TYPE_EQUIP);
			}
		}
	}
	else if ( HIBYTE(GetKeyState('E')) )
	{
//		if ( GetKeyState(VK_CONTROL) & 0x80 )
		{
			if ( m_xMagicWnd.GetGameWndActive() )
			{
				WindowActivate(_WND_ID_MAGIC);
				if ( m_xMagicShortcutWnd.GetGameWndActive() )
				{
					WindowActivate(_WND_ID_MAGICSHORTCUT);
				}
			}
			else
			{
				WindowActivate(_WND_ID_MAGIC);
				if ( !m_xMagicShortcutWnd.GetGameWndActive() )
				{
					WindowActivate(_WND_ID_MAGICSHORTCUT);
				}
			}
			m_xMagicWnd.m_bWantSetKey = FALSE;
		}

	}
	else if ( HIBYTE(GetKeyState('R')) )
	{
//		if ( GetKeyState(VK_CONTROL) & 0x80 )
		{
			if ( !m_xChatWnd.GetGameWndActive() )
			{
				if ( !m_xChatWnd.mChat_bLargeChat )
					m_xChatWnd.ChangeChatSize();

				WindowActivate(_WND_ID_CHAT);
			}
			else
			{
				m_xChatWnd.ChangeChatSize();
			}
		}
	}
	else if ( HIBYTE(GetKeyState('A')) )
	{
//		if ( GetKeyState(VK_CONTROL) & 0x80 )
//		{
//			WindowActivate(_WND_ID_VIEWMINIMAP);
			if ( HIBYTE(GetKeyState(VK_CONTROL)) )
				return FALSE;
			else
			{
				WindowActivate(_WND_ID_MAGICSHORTCUT);
				return TRUE;
			}
//			WindowActivate(_WND_ID_HORSE);
//		}
	}
	else if ( HIBYTE(GetKeyState('S')) )
	{
//		if ( GetKeyState(VK_CONTROL) & 0x80 )
//		{
//			WindowActivate(_WND_ID_VIEWMINIMAP);
//			WindowActivate(_WND_ID_UTIL);
//		m_xStatusWnd.m_nTestFame += 2;

//		if ( m_xStatusWnd.m_nTestFame > 12 )
//			m_xStatusWnd.m_nTestFame = 0;
		
//		}
//		g_xClientSocket.SendSetXY();
	}
	else if ( HIBYTE(GetKeyState('J')) )
	{
//		if ( timeGetTime() - m_dwQueryMsgTime > 1000)
//		{
///			if ( m_nInformationMode == _INFO_CHAR )
//			{
//				g_xClientSocket.SendWantMMap();
//				m_bReadyInforMap = TRUE;
//				m_nInformationMode = !m_nInformationMode;
//			}
//			else
//			{
//				m_bViewMiniMapInMain = FALSE;
//				m_nInformationMode = !m_nInformationMode;
//			}
//		}
//
//		CHAR	szVal[MAX_PATH];
//		CHAR	szFileName[MAX_PATH];
//
//		if ( GetCurrentDirectory(MAX_PATH, szFileName))
//		{
//			if ( szFileName[0] == '\0' )
//				return TRUE;
//			strcat(szFileName, "\\Config.ini");
//
//			sprintf(szVal, "%d", m_nInformationMode );
//			WritePrivateProfileString(SECTION_OPTIONS, KEY_INFORMATIONMODE, szVal, szFileName);		// Effect Sound On or Off
//		}
	}
	else if ( HIBYTE(GetKeyState('O')) )
	{
		g_xGameProc.m_bShowBloodNum == FALSE ? g_xGameProc.m_bShowBloodNum = TRUE : g_xGameProc.m_bShowBloodNum = FALSE;

		CHAR	szVal[MAX_PATH];
		CHAR	szFileName[MAX_PATH];

		if ( GetCurrentDirectory(MAX_PATH, szFileName))
		{
			if ( szFileName[0] == '\0' )
				return TRUE;
			strcat(szFileName, "\\Config.ini");

			sprintf(szVal, "%d", g_xGameProc.m_bShowBloodNum );
			WritePrivateProfileString(SECTION_OPTIONS, KEY_SHOWBLOODNUM, szVal, szFileName);		// Effect Sound On or Off
		}
	}
#ifdef _DEBUG
	else if ( HIBYTE(GetKeyState('U')) )
	{
		g_xGameProc.m_ShowAddOn = !g_xGameProc.m_ShowAddOn;

	}
#endif
	else if ( HIBYTE(GetKeyState('I')) )
	{
		DWORD dwFont = GetChatColor(_CHAT_COLOR3);
		DWORD dwBack = GetChatColor(_CHAT_COLOR8);

		if ( g_xGameProc.m_xInterface.m_xMiniMap.m_bShowMonInfo == FALSE )
		{
			MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2646));
			m_xOptionWnd.m_xOptionBtn[_BTN_ID_SHOWMONINMAP].ResetGameBtn(1293, 1295, 1292);
			g_xGameProc.m_xInterface.m_xMiniMap.m_bShowMonInfo = TRUE;
		}
		else
		{
			MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2647));
			m_xOptionWnd.m_xOptionBtn[_BTN_ID_SHOWMONINMAP].ResetGameBtn(1294, 1292, 1295);
			g_xGameProc.m_xInterface.m_xMiniMap.m_bShowMonInfo = FALSE;
		}

		CHAR	szVal[MAX_PATH];
		CHAR	szFileName[MAX_PATH];

		if ( GetCurrentDirectory(MAX_PATH, szFileName))
		{
			if ( szFileName[0] == '\0' )
				return TRUE;
			strcat(szFileName, "\\Config.ini");

			sprintf(szVal, "%d", g_xGameProc.m_xInterface.m_xMiniMap.m_bShowMonInfo );
			WritePrivateProfileString(SECTION_OPTIONS, KEY_SHOWMON, szVal, szFileName);		// Effect Sound On or Off
		}
	}
	else if ( HIBYTE(GetKeyState('K')) )
	{
		m_xChatWnd.mChat_nMode++;
		if ( m_xChatWnd.mChat_nMode > _CHAT_MODE_GUILD )
			m_xChatWnd.mChat_nMode = _CHAT_MODE_NORMAL;

		DWORD dwFont = GetChatColor(_CHAT_COLOR3);
		DWORD dwBack = GetChatColor(_CHAT_COLOR8);

		switch ( m_xChatWnd.mChat_nMode )
		{
		case _CHAT_MODE_NORMAL:
			MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2626));
			m_xChatWnd.mChat_BtnMode.ResetGameBtn(166, 166, 166);
			break;
		case _CHAT_MODE_GROUP:
			MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2627));
			m_xChatWnd.mChat_BtnMode.ResetGameBtn(167, 167, 167);
			break;
		case _CHAT_MODE_GUILD:
			MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2628));
			m_xChatWnd.mChat_BtnMode.ResetGameBtn(168, 168, 168);
			break;
		}
	}
	else if ( HIBYTE(GetKeyState('D')) )
	{
//		if ( GetKeyState(VK_CONTROL) & 0x80 )
		{
			WindowActivate(_WND_ID_QUEST);
		}
	}
	else if ( HIBYTE(GetKeyState('L')) )
	{
		g_xGameProc.m_bDrawName == FALSE ? g_xGameProc.m_bDrawName = TRUE : g_xGameProc.m_bDrawName = FALSE;

		CHAR	szVal[MAX_PATH];
		CHAR	szFileName[MAX_PATH];

		if ( GetCurrentDirectory(MAX_PATH, szFileName))
		{
			if ( szFileName[0] == '\0' )
				return TRUE;
			strcat(szFileName, "\\Config.ini");

			sprintf(szVal, "%d", g_xGameProc.m_bDrawName );
			WritePrivateProfileString(SECTION_OPTIONS, KEY_DRAWNAME, szVal, szFileName);		// Effect Sound On or Off
		}
	}
	else if ( HIBYTE(GetKeyState('P')) )
	{
		if ( m_bHasSiege )
		{	
			if (WindowActivate(_WND_ID_SIEGE) == TRUE )
			{
				g_xClientSocket.SendWantMMap();
			}
			else
			{
			}
		}
		return FALSE;
	}
	else if ( HIBYTE(GetKeyState('Z')) )
	{
		m_xBeltWnd.ProceessKeyDownMessage(wParam, lParam);
	}
	else if ( HIBYTE(GetKeyState('C')) )
	{
//		if ( GetKeyState(VK_CONTROL) & 0x80 )
		{
			CActor* pxActor = g_xGameProc.FrontActor(g_xGameProc.m_xMyHero.m_nPosX, g_xGameProc.m_xMyHero.m_nPosY, g_xGameProc.m_xMyHero.m_bCurrDir, 1);

			if ( pxActor )
			{
				g_xClientSocket.SendDealTry(pxActor->m_szName);
			}
		}
	}
	else if ( HIBYTE(GetKeyState('V')) )
	{
//		if ( GetKeyState(VK_CONTROL) & 0x80 )
		{
			if ( timeGetTime() - m_dwQueryMsgTime > 1000)
			{
				if ( m_bViewMiniMap == FALSE )
				{
					g_xClientSocket.SendWantMMap();
					m_bReadyViewMap = TRUE;
				}
				else
				{
					m_bViewMiniMap = FALSE;
				}						
			}
		}
	}
	else if ( HIBYTE(GetKeyState('B')) )
	{
//		if ( GetKeyState(VK_CONTROL) & 0x80 )
		{
			WindowActivate(_WND_ID_CHAT);
			m_bShowKey = !m_bShowKey;
		}
	}
	else if ( HIBYTE(GetKeyState('G')) )
	{
//		if ( GetKeyState(VK_CONTROL) & 0x80 )
		{
			WindowActivate(_WND_ID_GROUP);
		}
	}
	else if ( HIBYTE(GetKeyState('F')) )
	{
//		if ( GetKeyState(VK_CONTROL) & 0x80 )
		{
			if ( !m_xGuildWnd.GetGameWndActive() )
				g_xClientSocket.SendGuildHome();
		}
	}
	else if ( HIBYTE(GetKeyState('N')) )
	{
//		if ( GetKeyState(VK_CONTROL) & 0x80 )
		{
//			WindowActivate(_WND_ID_UTIL);
			
			WindowActivate(_WND_ID_SETTING);
		}
	}
	else if ( HIBYTE(GetKeyState('T')) )
	{
		if ( m_bViewMiniMap == TRUE || m_bViewMiniMapInMain == TRUE)
		{
/*			m_xMiniMap.m_bMultiple = !m_xMiniMap.m_bMultiple;

			if ( m_xMiniMap.m_bMultiple )
			{
				m_xMiniMap.MiniMapSurface(g_xMainWnd.Get3DDevice(), 256, 256);
			}
			else
			{
				m_xMiniMap.MiniMapSurface(g_xMainWnd.Get3DDevice(), 128, 128);
			}*/
			m_xMiniMap.m_bMultiple++;

			if ( m_xMiniMap.m_bMultiple > _SND_RATE )
			{
				m_xMiniMap.m_bMultiple = _FST_RATE; 
			}

			switch ( m_xMiniMap.m_bMultiple )
			{
				case _FST_RATE:
				{
					m_xMiniMap.MiniMapSurface(g_xMainWnd.Get3DDevice(), 128, 128);
					break;
				}
				case _SND_RATE:
				{
					m_xMiniMap.MiniMapSurface(g_xMainWnd.Get3DDevice(), 256, 256);
					break;
				}
				case _TRD_RATE:
				{
					m_xMiniMap.MiniMapSurface(g_xMainWnd.Get3DDevice(), 512, 512);
					break;
				}
				case _FOURTH_RATE:
				{
					m_xMiniMap.MiniMapSurface(g_xMainWnd.Get3DDevice(), 1024, 1024);
					break;
				}
			}
		}
	}
	else if ( HIBYTE(GetKeyState('Y')) )
	{
		if ( m_bViewMiniMap == TRUE)
		{
			m_xMiniMap.m_bBlend = !m_xMiniMap.m_bBlend;
		}
	}

	INT nInterfaceWndInRect;
	nInterfaceWndInRect = GetWindowInMousePos(g_xGameProc.m_ptMousePos);

	switch ( wParam )
	{
		case VK_RETURN:	
		{
			return FALSE;
		}
		break;
/*		case 186:
		{
			if ( HIBYTE(GetKeyState(VK_SHIFT) ))
			{
				Sleep(500);
				ZeroMemory(&g_xGameProc.m_xInterface.m_stCommonItem, sizeof(COMMONITEMSET));
			}
			break;
		}
*/		// 영국 키보드 락업 지우기 기능
		case 188:
		{
			if ( m_bHasNewMessage == TRUE || m_xMessengerWnd.mMessenger_xReceivedMSGList.GetCount() == 0 )
				g_xClientSocket.SendRefreshMailBox(0);
			if ( !m_xMessengerWnd.GetGameWndActive() )
				WindowActivate(_WND_ID_MESSENGER);
			else
			{
				m_xMessengerWnd.CloseMessengerWnd();
			}
		}
		break;
		case 9:
		{
			g_xGameProc.m_bDrawGroundItemName = TRUE;
		}
		break;
		case 192:	// '`' 아이템 줍기
		{
			g_xGameProc.m_bAutoPickup = TRUE;
		}
		break;
		case VK_ESCAPE:
		{
			// 포커스가 채팅창에 없을때.
			if ( m_xWndOrderList.GetCounter() != 0 && (GetFocus() == g_xMainWnd.GetSafehWnd()) &&
				!IsTopWindow(_WND_ID_CHAT) )
			{
				INT* pnCurrID;
				m_xWndOrderList.MoveCurrentToTail();
				pnCurrID = m_xWndOrderList.GetCurrentData();

				if ( *pnCurrID == _WND_ID_NPCCHAT && g_xGameProc.m_bDiceModeActive )
				{
					m_xWndOrderList.MovePreviousNode();
					pnCurrID = m_xWndOrderList.GetCurrentData();

					if ( *pnCurrID == _WND_ID_NPCCHAT )
					{
						pnCurrID = NULL;
					}
				}

				if ( pnCurrID )
				{
					if ( *pnCurrID == _WND_ID_NPCCHAT )
					{
						g_xGameProc.CloseNPCWindow();
					}
					else if ( *pnCurrID == _WND_ID_MESSENGER )
					{
						m_xMessengerWnd.CloseMessengerWnd();
					}
					else
					{
						if ( *pnCurrID == _WND_ID_INVENTORY || *pnCurrID == _WND_ID_STATUS )
						{
							if ( CanViewModeChange() )
							{
								WindowActivate(*pnCurrID);
								SetViewMode();
							}
						}
						else
						{
							WindowActivate(*pnCurrID);
						}
					}
				}

				return TRUE;
			}
/*			else if ( g_xChatEditBox.GetSafehWnd() != GetFocus() && !m_xGameOverWnd.GetGameWndActive() )
			{
				 if ( g_xGameProc.CanGameOut() )
				 {
					 m_xGameOverWnd.SetGameWndActive(TRUE);
					 return TRUE;
				 }
			}*/
			break;
		}
		case VK_UP:
		{
			if ( !g_xGameProc.m_xGameMsgBox.IsActive() && (GetFocus() == g_xChatEditBox.GetSafehWnd()) )
			{
				if ( (GetKeyState(VK_CONTROL) & 0x80) )
				{
					m_nSelHearNum--;

					if ( m_nSelHearNum < 0 )
					{
						m_nSelHearNum = 0;
					}

					SetHearList();
				}
				else if ( (GetKeyState(VK_MENU) & 0x80) )
				{
					m_nSelMacroNum--;

					if ( m_nSelMacroNum < 0 )
					{
						m_nSelMacroNum = 0;
					}

					SetMacroList();
				}
			}
			else
			{
				OnScrollDown();
			}
			return TRUE;
		}
		case VK_DOWN:
		{
			if ( !g_xGameProc.m_xGameMsgBox.IsActive() && (GetFocus() == g_xChatEditBox.GetSafehWnd()) )
			{
				if ( (GetKeyState(VK_CONTROL) & 0x80) )
				{
					m_nSelHearNum++;

					if ( m_nSelHearNum >= m_xHearList.GetCount() )
					{
						m_nSelHearNum = m_xHearList.GetCount()-1;
					}

					SetHearList();
				}
				else if ( (GetKeyState(VK_MENU) & 0x80) )
				{
					m_nSelMacroNum++;

					if ( m_nSelMacroNum >= m_xMacroList.GetCount() )
					{
						m_nSelMacroNum = m_xMacroList.GetCount()-1;
					}

					SetMacroList();
				}				
			}
			else
			{
				OnScrollUp();
			}
			return TRUE;
		}
		case 0XBF:			// /
		{
			g_xGameProc.m_xInterface.m_xChatWnd.ActiveEditBox();
			SetFocus(g_xChatEditBox.GetSafehWnd());
			ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);

			if ( m_xChatWnd.m_pszLastCapture[0] == '\0' )
			{
				strcpy(m_xChatWnd.m_pszLastCapture, "/");
			}

			SetWindowText(g_xChatEditBox.GetSafehWnd(), m_xChatWnd.m_pszLastCapture);

			INT nLen = strlen(m_xChatWnd.m_pszLastCapture);
			SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETSEL, nLen , nLen);
			g_xChatEditBox.SetHanguelMode();
			break;
		}
		case '1':			// !
		{
			if (m_xBeltWnd.ProceessKeyDownMessage(wParam, lParam) == TRUE)
				return TRUE;
		}
		break;
		case '2':			// @
		{			
			if (m_xBeltWnd.ProceessKeyDownMessage(wParam, lParam) == TRUE)
				return TRUE;
		}
		break;
		case '3':
		{
			if (m_xBeltWnd.ProceessKeyDownMessage(wParam, lParam) == TRUE)
				return TRUE;
		}
		break;
		case '4':
		{
			if (m_xBeltWnd.ProceessKeyDownMessage(wParam, lParam) == TRUE)
				return TRUE;
		}
		break;
		case '5':
		{
			if (m_xBeltWnd.ProceessKeyDownMessage(wParam, lParam) == TRUE)
				return TRUE;
		}
		break;
		case '6':
		{
			if (m_xBeltWnd.ProceessKeyDownMessage(wParam, lParam) == TRUE)
				return TRUE;
		}
		break;
	}

	if ( nInterfaceWndInRect != -1 )
	{
		if ( nInterfaceWndInRect == _WND_ID_MAGIC )
		{
			if ( m_xMagicWnd.OnKeyDown(wParam, lParam, g_xGameProc.m_ptMousePos) )
				return TRUE;
		}
	}
#ifdef _DEBUG
	if ( nInterfaceWndInRect != -1 )
	{
		if ( nInterfaceWndInRect == _WND_ID_UTIL )
		{
			if ( m_xUtilWnd.OnKeyDown(wParam, lParam) )
				return TRUE;
		}
	}
#endif
	return FALSE;
}


BOOL CInterface::OnSysKeyDown(WPARAM wParam, LPARAM lParam)
{
	if ( m_xMagicWnd.GetGameWndActive() )
	{
		if ( m_xMagicWnd.OnSysKeyDown(wParam, lParam, g_xGameProc.m_ptMousePos) )
		{
			return TRUE;
		}
	}

#ifdef _DEBUG	
	if ( m_xUtilWnd.GetGameWndActive() )
	{
		if ( m_xUtilWnd.OnSysKeyDown(wParam, lParam) )
		{
			return TRUE;
		}
	}
#endif
	return FALSE;
}


BOOL CInterface::OnMsgInputted(WPARAM wParam, LPARAM lParam)
{
	if ( m_xNPCWnd.GetGameWndActive() )
	{
		if ( m_xNPCWnd.OnMsgInputted() )
		{
			return TRUE;
		}
	}

	return FALSE;
}


LRESULT CInterface::OnMsgBoxReturn(WPARAM wParam, LPARAM lParam)
{
	BYTE bWndID;
	BYTE bMsgReturn;

	bWndID	   = HIBYTE(HIWORD(wParam));
	bMsgReturn = LOBYTE(HIWORD(wParam));

	switch ( bWndID )
	{
	case _WND_ID_GROUP:
		m_xGroupWnd.OnMsgBoxReturn(wParam, lParam);
		break;
	case _WND_ID_INVENTORY:
		break;
	case _WND_ID_STATUS:
		break;
	case _WND_ID_STORE:
		break;
	case _WND_ID_EXCHANGE:
		m_xExchangeWnd.OnMsgBoxReturn(wParam, lParam);
		break;
	case _WND_ID_GUILD:
		m_xGuildWnd.OnMsgBoxReturn(wParam, lParam);
		break;
	case _WND_ID_USERSTATE:
		break;
	case _WND_ID_CHATPOP:
		break;
	case _WND_ID_QUEST:
		break;
	case _WND_ID_OPTION:
		break;
	case _WND_ID_HORSE:
		break;
	case _WND_ID_MAGIC:
		break;
	case _WND_ID_NPCCHAT:
		m_xNPCWnd.OnMsgBoxReturn(wParam, lParam);
		break;
	}

	return 0L;
}











///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------------------------------------------
// 벨트 영역.
//-----------------------------------------------------------------------------------------------------------------
/******************************************************************************************************************

	함수명 : CInterface::GetBeltNum()

	작성자 : 
	작성일 : 

	목적   : 마우스 위치에서 현재 벨트의 셀번호를 얻어온다.
	입력   : POINT ptMouse
	출력   : INT 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
INT CInterface::GetBeltNum(POINT ptMouse)
{
	RECT	rc;
	if ( m_bBeltState != _BELT_STATE_STAY )
	{
		for ( INT nCnt = 0; nCnt < _MAX_BELT_ITEM; nCnt++ )
		{
			SetRect(&rc, m_rcBeltCell[nCnt].left, m_rcBeltCell[nCnt].top, 
					m_rcBeltCell[nCnt].left+_INVENTORY_CELL_WIDTH, m_rcBeltCell[nCnt].top+_INVENTORY_CELL_HEIGHT);
			if ( PtInRect(&rc, ptMouse) )
			{
				return nCnt;
			}
		}
	}

	return -1;
}


/******************************************************************************************************************

	함수명 : CInterface::DeleteCurrBeltItemList()

	작성자 : 
	작성일 : 

	목적   : 벨트의 해당셀 아이템을 지운다.
	입력   : INT nBeltInventoryNum
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CInterface::DeleteBeltItem(INT nBeltInventoryNum)
{
	ZeroMemory(&m_stBeltItem[nBeltInventoryNum], sizeof(ITEMSET));
}



/******************************************************************************************************************

	함수명 : CInterface::DeleteAllBeltItemList()

	작성자 : 
	작성일 : 

	목적   : 벨트의 모든 아이템을 지운다.
	입력   : INT nBeltInventoryNum
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CInterface::DeleteAllBeltItem()
{
	for ( INT nCnt = 0; nCnt < _MAX_BELT_ITEM; nCnt++ )
	{
		ZeroMemory(&m_stBeltItem[nCnt], sizeof(ITEMSET));
	}
}


/******************************************************************************************************************

	함수명 : CInterface::AddBeltItem()

	작성자 : 
	작성일 : 

	목적   : 벨트에 아이템을 넣는다.
	입력   : CItem xItem
	         INT nBeltNum
	         BOOL bUseBeltNum
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CInterface::AddBeltItem(CItem xItem, INT nBeltNum, BOOL bUseBeltNum)
{
	if ( bUseBeltNum )
	{
		if ( !m_stBeltItem[nBeltNum].bSetted )
		{
			m_stBeltItem[nBeltNum].bSetted = TRUE;
			m_stBeltItem[nBeltNum].xItem = xItem;

			return TRUE;
		}
	}

	for ( INT nCnt = 0; nCnt < _MAX_BELT_ITEM; nCnt++ )
	{
		if ( !m_stBeltItem[nCnt].bSetted )
		{
			m_stBeltItem[nCnt].bSetted = TRUE;
			m_stBeltItem[nCnt].xItem = xItem;

			return TRUE;
		}
	}
	return FALSE;
}


/******************************************************************************************************************

	함수명 : CInterface::ExtractBeltItem()

	작성자 : 
	작성일 : 

	목적   : 가방창에서 현재 번호의 아이템을 뽑아온다.
	입력   : CItem* pxItem
	         INT nBeltInventoryNum
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CInterface::ExtractBeltItem(CItem* pxItem, INT nBeltInventoryNum)
{
	if ( m_stBeltItem[nBeltInventoryNum].bSetted )
	{
		memcpy(pxItem, &m_stBeltItem[nBeltInventoryNum].xItem, sizeof(CItem));
		DeleteBeltItem(nBeltInventoryNum);
				
		return TRUE;
	}
	return FALSE;
}


/******************************************************************************************************************

	함수명 : CInterface::ChangeBeltWithCommonOLD()

	작성자 : 
	작성일 : 

	목적   : 벨트의 아이템과 공통(마우스)아이템을 바꾼다.
	입력   : INT nBeltInventoryNum
	         LPCOMMONITEMSET pstCommonItemSet
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CInterface::ChangeBeltWithCommonOLD(INT nBeltInventoryNum, LPCOMMONITEMSET pstCommonItemSet)
{
	if ( pstCommonItemSet->bSetted )
	{
		CItem xBeltItem;
		if ( ExtractBeltItem(&xBeltItem, nBeltInventoryNum) )
		{
			AddBeltItem(pstCommonItemSet->xItem, nBeltInventoryNum, TRUE);

			pstCommonItemSet->bSetted			= TRUE;
			pstCommonItemSet->xItem				= xBeltItem;
			pstCommonItemSet->bWaitResponse		= FALSE;
			pstCommonItemSet->bIsDealItem		= FALSE;
			pstCommonItemSet->bIsEquipItem		= FALSE;
			pstCommonItemSet->bIsHideItem		= FALSE;
			pstCommonItemSet->bIsBeltItem		= TRUE;
			pstCommonItemSet->xItem.m_shCellNum = (SHORT)nBeltInventoryNum; 
		}
	}
}

VOID CInterface::ChangeBeltWithCommon(INT nBeltInventoryNum, LPCOMMONITEMSET pstCommonItemSet)
{
	if ( pstCommonItemSet->bSetted )
	{
		CItem xBeltItem;
		CHAR szSysMsg[MAX_PATH];

		if (strcmp(m_stBeltItem[nBeltInventoryNum].xItem.m_stItemInfo.stStdItem.szName, pstCommonItemSet->xItem.m_stItemInfo.stStdItem.szName) == 0)
		{
			sprintf(szSysMsg, g_xMsg.GetMsg(1069));
			m_xClientSysMsg.AddSysMsg(szSysMsg);
			return;
		}

		if ( ExtractBeltItem(&xBeltItem, nBeltInventoryNum) )
		{
			AddBeltItem(pstCommonItemSet->xItem, nBeltInventoryNum, TRUE);

			if (!pstCommonItemSet->bIsBeltItem)
				m_xInventoryWnd.AddInvenItem(pstCommonItemSet->xItem, 0, FALSE);

			pstCommonItemSet->bSetted			= TRUE;
			pstCommonItemSet->xItem				= xBeltItem;
			pstCommonItemSet->bWaitResponse		= FALSE;
			pstCommonItemSet->bIsDealItem		= FALSE;
			pstCommonItemSet->bIsEquipItem		= FALSE;
			pstCommonItemSet->bIsHideItem		= FALSE;
			pstCommonItemSet->bIsBeltItem		= TRUE;
			pstCommonItemSet->xItem.m_shCellNum = (SHORT)nBeltInventoryNum; 
		}
	}
}

/******************************************************************************************************************

	함수명 : CInterface::SetCommonFromBelt()

	작성자 : 
	작성일 : 

	목적   : 벨트창의 해당번호 아이템을 공통(마우스)아이템으로 세팅한다.
	입력   : INT nBeltInventoryNum
	         LPCOMMONITEMSET pstCommonItemSet
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CInterface::SetCommonFromBelt(INT nBeltInventoryNum, LPCOMMONITEMSET pstCommonItemSet)
{
	CItem xBeltItem;
	if ( ExtractBeltItem(&xBeltItem, nBeltInventoryNum) )
	{
		pstCommonItemSet->bSetted			= TRUE;
		pstCommonItemSet->xItem				= xBeltItem;
		pstCommonItemSet->bWaitResponse		= FALSE;
		pstCommonItemSet->bIsEquipItem		= FALSE;
		pstCommonItemSet->bIsDealItem		= FALSE;
		pstCommonItemSet->bIsHideItem		= FALSE;
		pstCommonItemSet->bIsBeltItem		= TRUE;
		pstCommonItemSet->xItem.m_shCellNum = (SHORT)nBeltInventoryNum; 

		ItemClickSound(&pstCommonItemSet->xItem);
	}
}	


/******************************************************************************************************************

	함수명 : CInterface::SetBeltFromCommonOLD()

	작성자 : 
	작성일 : 

	목적   : 공통(마우스)아이템을 벨트창의 해당번호로 세팅한다.
	입력   : INT nBeltInventoryNum
	         LPCOMMONITEMSET pstCommonItemSet
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CInterface::SetBeltFromCommonOLD(INT nBeltInventoryNum, LPCOMMONITEMSET pstCommonItemSet)
{
	if ( pstCommonItemSet->bSetted )
	{
		if (pstCommonItemSet->bIsDealItem)
		{
			m_xExchangeWnd.SetDealFromCommon(0, 0, pstCommonItemSet);
			ItemClickSound(&pstCommonItemSet->xItem);
			ZeroMemory(pstCommonItemSet, sizeof(LPCOMMONITEMSET));
			return;
		}

		ItemClickSound(&pstCommonItemSet->xItem);

		pstCommonItemSet->xItem.m_shCellNum = (SHORT)nBeltInventoryNum;
		AddBeltItem(pstCommonItemSet->xItem, nBeltInventoryNum);

		ZeroMemory(pstCommonItemSet, sizeof(LPCOMMONITEMSET));
	}
}

VOID CInterface::SetBeltFromCommon(INT nBeltInventoryNum, LPCOMMONITEMSET pstCommonItemSet)
{
	CHAR szSysMsg[MAX_PATH];

	if ( pstCommonItemSet->bSetted )
	{
		if (pstCommonItemSet->bIsDealItem)
		{
			m_xExchangeWnd.SetDealFromCommon(0, 0, pstCommonItemSet);
			ItemClickSound(&pstCommonItemSet->xItem);
			ZeroMemory(pstCommonItemSet, sizeof(LPCOMMONITEMSET));
			return;
		}

		if (FindSameItemInBelt(pstCommonItemSet->xItem) != -1)
		{
			sprintf(szSysMsg, g_xMsg.GetMsg(1067), pstCommonItemSet->xItem.m_stItemInfo.stStdItem.szName);
			m_xClientSysMsg.AddSysMsg(szSysMsg);
			return;
		}

		ItemClickSound(&pstCommonItemSet->xItem);

		pstCommonItemSet->xItem.m_shCellNum = (SHORT)nBeltInventoryNum;

		if (!pstCommonItemSet->bIsBeltItem)
		{
			m_xInventoryWnd.AddInvenItem(pstCommonItemSet->xItem, pstCommonItemSet->xItem.m_shCellNum, TRUE);

			sprintf(szSysMsg, g_xMsg.GetMsg(1068), pstCommonItemSet->xItem.m_stItemInfo.stStdItem.szName, nBeltInventoryNum + 1);
			m_xClientSysMsg.AddSysMsg(szSysMsg);
			AddBeltItem(pstCommonItemSet->xItem, nBeltInventoryNum);
		}
		else
		{
			AddBeltItem(pstCommonItemSet->xItem, nBeltInventoryNum);
		}
		ZeroMemory(pstCommonItemSet, sizeof(LPCOMMONITEMSET));
	}
}

BOOL CInterface::AddNewBeltItem(LPCOMMONITEMSET pstCommonItemSet)
{
	INT nCnt;
	if ( pstCommonItemSet->bSetted && pstCommonItemSet->bIsBeltItem )
	{
		if ( strcmp(m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(1050)) &&
			(m_stCommonItem.xItem.m_stItemInfo.stStdItem.bStdMode == 0 || m_stCommonItem.xItem.m_stItemInfo.stStdItem.bStdMode == 3) )
		{
			for ( nCnt = 0; nCnt < _MAX_INVEN_ITEM; nCnt++ )
			{
				if ( m_xInventoryWnd.m_stInventoryItem[nCnt].bSetted && 
					 m_xInventoryWnd.m_stInventoryItem[nCnt].xItem.m_stItemInfo.stStdItem.bStdMode == pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bStdMode &&
					 m_xInventoryWnd.m_stInventoryItem[nCnt].xItem.m_stItemInfo.stStdItem.wLooks == pstCommonItemSet->xItem.m_stItemInfo.stStdItem.wLooks )
				{
					if ( !m_stBeltItem[pstCommonItemSet->xItem.m_shCellNum].bSetted )
					{
						m_stBeltItem[pstCommonItemSet->xItem.m_shCellNum].xItem = m_xInventoryWnd.m_stInventoryItem[nCnt].xItem;
						m_stBeltItem[pstCommonItemSet->xItem.m_shCellNum].bSetted = TRUE;
						m_xInventoryWnd.DeleteInvenItem(nCnt);
						return TRUE;
					}
				}
			}
		}			 
	}
	return FALSE;
}


/******************************************************************************************************************

	아이템 넣고빼기 관련, 인벤토리위치 저장파일 세이브및 로드.(인벤토리 및 벨트)

*******************************************************************************************************************/
/******************************************************************************************************************

	함수명 : CInterface::CheckItemPosOLD()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : CHAR* szName
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CInterface::CheckItemPosOLD(CHAR* szName)
{
	HANDLE			hFile;
	CHAR			szItemFile[MAX_PATH];
	INT				nCnt1, nCnt2, nCheck;

	INVENITEMSET	stInvenItem[_MAX_INVEN_ITEM];								// 임시데이타 로드용변수.
	SHORT			shItemSetInfo[_INVEN_TOTAL_CELL];

	INVENITEMSET	stCheckedInvenItem[_MAX_INVEN_ITEM];						// 임시데이타 로드용변수.
	SHORT			shCheckedItemSetInfo[_INVEN_TOTAL_CELL];

	ITEMSET			stBeltItem[_MAX_BELT_ITEM];							

	ZeroMemory(m_stBeltItem, sizeof(ITEMSET)*_MAX_BELT_ITEM );

	ZeroMemory(szItemFile, MAX_PATH);
	g_xMainWnd.StringPlus(szItemFile, ".\\Data\\", szName, ".itms", "");

	hFile = CreateFile(szItemFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ZeroMemory(stInvenItem,	   sizeof(INVENITEMSET)*_MAX_INVEN_ITEM);
	memset(shItemSetInfo, -1, _INVEN_TOTAL_CELL*sizeof(SHORT));

	ZeroMemory(stCheckedInvenItem,	   sizeof(INVENITEMSET)*_MAX_INVEN_ITEM);
	memset(shCheckedItemSetInfo, -1, _INVEN_TOTAL_CELL*sizeof(SHORT));

	ZeroMemory(stBeltItem ,	   sizeof(ITEMSET)*_MAX_BELT_ITEM );

	if ( hFile != INVALID_HANDLE_VALUE )
	{
		DWORD		dwReadLen;

		ReadFile(hFile, &stInvenItem,	sizeof(INVENITEMSET)*_MAX_INVEN_ITEM, &dwReadLen, NULL);
		ReadFile(hFile, &shItemSetInfo, _INVEN_TOTAL_CELL*sizeof(SHORT), &dwReadLen, NULL);

		ReadFile(hFile, &stBeltItem ,	sizeof(ITEMSET)*_MAX_BELT_ITEM , &dwReadLen, NULL);

		// 서버에서 받은 인벤토리데이타와 클라이언트에서 마지막에 저장시킨 벨트창데이타를 비교하면서 맞는 위치에 배정시킨다.
		for ( nCnt1 = 0; nCnt1 < _MAX_BELT_ITEM; nCnt1++ )
		{
			if ( stBeltItem[nCnt1].bSetted )
			{
				for ( nCnt2 = 0; nCnt2 < _MAX_INVEN_ITEM; nCnt2++ )
				{
					if ( m_xInventoryWnd.m_stInventoryItem[nCnt2].bSetted )
					{
						// 같은아이템인지를 뽑아낸다.
						if ( !strcmp(stBeltItem[nCnt1].xItem.m_stItemInfo.stStdItem.szName, m_xInventoryWnd.m_stInventoryItem[nCnt2].xItem.m_stItemInfo.stStdItem.szName) &&
							 stBeltItem[nCnt1].xItem.m_stItemInfo.nMakeIndex == m_xInventoryWnd.m_stInventoryItem[nCnt2].xItem.m_stItemInfo.nMakeIndex &&
							 stBeltItem[nCnt1].xItem.m_stItemInfo.nDura      == m_xInventoryWnd.m_stInventoryItem[nCnt2].xItem.m_stItemInfo.nDura &&
							 stBeltItem[nCnt1].xItem.m_stItemInfo.nDuraMax	 == m_xInventoryWnd.m_stInventoryItem[nCnt2].xItem.m_stItemInfo.nDuraMax )
						{
							m_stBeltItem[nCnt1].bSetted = TRUE;
							m_stBeltItem[nCnt1].xItem   = m_xInventoryWnd.m_stInventoryItem[nCnt2].xItem;
							m_xInventoryWnd.DeleteInvenItem(stBeltItem[nCnt1].xItem.m_stItemInfo.nMakeIndex, stBeltItem[nCnt1].xItem.m_stItemInfo.stStdItem.szName);
						}
					}
				}
			}
		} 

		// 인벤토리.
		for ( nCnt1 = 0; nCnt1 < _MAX_INVEN_ITEM; nCnt1++ )
		{
			if ( stInvenItem[nCnt1].bSetted )
			{
				for ( nCnt2 = 0; nCnt2 < _MAX_INVEN_ITEM; nCnt2++ )
				{
					if ( m_xInventoryWnd.m_stInventoryItem[nCnt2].bSetted )
					{
						// 같은아이템인지를 뽑아낸다.
						if ( !strcmp(stInvenItem[nCnt1].xItem.m_stItemInfo.stStdItem.szName, m_xInventoryWnd.m_stInventoryItem[nCnt2].xItem.m_stItemInfo.stStdItem.szName) &&
							 stInvenItem[nCnt1].xItem.m_stItemInfo.nMakeIndex == m_xInventoryWnd.m_stInventoryItem[nCnt2].xItem.m_stItemInfo.nMakeIndex &&
							 stInvenItem[nCnt1].xItem.m_stItemInfo.nDura	  == m_xInventoryWnd.m_stInventoryItem[nCnt2].xItem.m_stItemInfo.nDura &&
							 stInvenItem[nCnt1].xItem.m_stItemInfo.nDuraMax   == m_xInventoryWnd.m_stInventoryItem[nCnt2].xItem.m_stItemInfo.nDuraMax )
						{
							stCheckedInvenItem[nCnt1] = m_xInventoryWnd.m_stInventoryItem[nCnt2];

							for ( nCheck = 0; nCheck < _INVEN_TOTAL_CELL; nCheck++ )
							{
								if ( shItemSetInfo[nCheck] != -1 )
								{
									if ( shItemSetInfo[nCheck] % 1000 == nCnt1 )
									{
										shCheckedItemSetInfo[nCheck] = shItemSetInfo[nCheck];
										shItemSetInfo[nCheck] = -1;
									}
								}
							}

							m_xInventoryWnd.DeleteInvenItem(stInvenItem[nCnt1].xItem.m_stItemInfo.nMakeIndex, stInvenItem[nCnt1].xItem.m_stItemInfo.stStdItem.szName);
							ZeroMemory(&stInvenItem[nCnt1],	sizeof(INVENITEMSET));
							break;
						}						
					}
				}
			}
		}

		INVENITEMSET	stNonCheckedInvenItem[_MAX_INVEN_ITEM];
		memcpy(stNonCheckedInvenItem, m_xInventoryWnd.m_stInventoryItem, sizeof(INVENITEMSET)*_MAX_INVEN_ITEM);

		memcpy(m_xInventoryWnd.m_stInventoryItem, stCheckedInvenItem, sizeof(INVENITEMSET)*_MAX_INVEN_ITEM);
		memcpy(m_xInventoryWnd.m_shItemSetInfo, shCheckedItemSetInfo, _INVEN_TOTAL_CELL*sizeof(SHORT));

		for ( nCnt1 = 0; nCnt1 < _MAX_INVEN_ITEM; nCnt1++ )
		{
			if ( stNonCheckedInvenItem[nCnt1].bSetted )
			{
				m_xInventoryWnd.AddInvenItem(stNonCheckedInvenItem[nCnt1].xItem, 0, FALSE);
			}
		}
	
		CloseHandle(hFile);
		return TRUE;
	}

	return FALSE;
}

BOOL CInterface::CheckItemPos(CHAR* szName)
{
	HANDLE			hFile;
	CHAR			szItemFile[MAX_PATH];
	INT				nCnt1, nCnt2, nCheck;

	INVENITEMSET	stInvenItem[_MAX_INVEN_ITEM];								// 임시데이타 로드용변수.
	SHORT			shItemSetInfo[_INVEN_TOTAL_CELL];

	INVENITEMSET	stCheckedInvenItem[_MAX_INVEN_ITEM];						// 임시데이타 로드용변수.
	SHORT			shCheckedItemSetInfo[_INVEN_TOTAL_CELL];

	ITEMSET			stBeltItem[_MAX_BELT_ITEM];

	ZeroMemory(m_stBeltItem, sizeof(ITEMSET)*_MAX_BELT_ITEM );

	ZeroMemory(szItemFile, MAX_PATH);
	g_xMainWnd.StringPlus(szItemFile, ".\\Data\\", szName, ".itms", "");

	hFile = CreateFile(szItemFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ZeroMemory(stInvenItem,	   sizeof(INVENITEMSET)*_MAX_INVEN_ITEM);
	memset(shItemSetInfo, -1, _INVEN_TOTAL_CELL*sizeof(SHORT));

	ZeroMemory(stCheckedInvenItem,	   sizeof(INVENITEMSET)*_MAX_INVEN_ITEM);
	memset(shCheckedItemSetInfo, -1, _INVEN_TOTAL_CELL*sizeof(SHORT));

	ZeroMemory(stBeltItem ,	   sizeof(ITEMSET)*_MAX_BELT_ITEM );

	if ( hFile != INVALID_HANDLE_VALUE )
	{
		DWORD		dwReadLen;

		ReadFile(hFile, &stInvenItem,	sizeof(INVENITEMSET)*_MAX_INVEN_ITEM, &dwReadLen, NULL);
		ReadFile(hFile, &shItemSetInfo, _INVEN_TOTAL_CELL*sizeof(SHORT), &dwReadLen, NULL);

		ReadFile(hFile, &stBeltItem ,	sizeof(ITEMSET)*_MAX_BELT_ITEM , &dwReadLen, NULL);

		// 서버에서 받은 인벤토리데이타와 클라이언트에서 마지막에 저장시킨 벨트창데이타를 비교하면서 맞는 위치에 배정시킨다.
		for ( nCnt1 = 0; nCnt1 < _MAX_BELT_ITEM; nCnt1++ )
		{
			if ( stBeltItem[nCnt1].bSetted )
			{
				for ( nCnt2 = 0; nCnt2 < _MAX_INVEN_ITEM; nCnt2++ )
				{
					if ( m_xInventoryWnd.m_stInventoryItem[nCnt2].bSetted )
					{
						// 같은아이템인지를 뽑아낸다.
						if ( strcmp(stBeltItem[nCnt1].xItem.m_stItemInfo.stStdItem.szName, m_xInventoryWnd.m_stInventoryItem[nCnt2].xItem.m_stItemInfo.stStdItem.szName) == 0)
						{
							m_xBeltWnd.m_stBeltItem[nCnt1].bSetted = TRUE;
							m_xBeltWnd.m_stBeltItem[nCnt1].xItem   = m_xInventoryWnd.m_stInventoryItem[nCnt2].xItem;
						}
					}
				}
			}
		} 

		// 인벤토리.
		for ( nCnt1 = 0; nCnt1 < _MAX_INVEN_ITEM; nCnt1++ )
		{
			if ( stInvenItem[nCnt1].bSetted )
			{
				for ( nCnt2 = 0; nCnt2 < _MAX_INVEN_ITEM; nCnt2++ )
				{
					if ( m_xInventoryWnd.m_stInventoryItem[nCnt2].bSetted )
					{
						// 같은아이템인지를 뽑아낸다.
						if ( !strcmp(stInvenItem[nCnt1].xItem.m_stItemInfo.stStdItem.szName, m_xInventoryWnd.m_stInventoryItem[nCnt2].xItem.m_stItemInfo.stStdItem.szName) &&
							 stInvenItem[nCnt1].xItem.m_stItemInfo.nMakeIndex == m_xInventoryWnd.m_stInventoryItem[nCnt2].xItem.m_stItemInfo.nMakeIndex &&
							 stInvenItem[nCnt1].xItem.m_stItemInfo.nDura	  == m_xInventoryWnd.m_stInventoryItem[nCnt2].xItem.m_stItemInfo.nDura &&
							 stInvenItem[nCnt1].xItem.m_stItemInfo.nDuraMax   == m_xInventoryWnd.m_stInventoryItem[nCnt2].xItem.m_stItemInfo.nDuraMax )
						{
							stCheckedInvenItem[nCnt1] = m_xInventoryWnd.m_stInventoryItem[nCnt2];

							for ( nCheck = 0; nCheck < _INVEN_TOTAL_CELL; nCheck++ )
							{
								if ( shItemSetInfo[nCheck] != -1 )
								{
									if ( shItemSetInfo[nCheck] % 1000 == nCnt1 )
									{
										shCheckedItemSetInfo[nCheck] = shItemSetInfo[nCheck];
										shItemSetInfo[nCheck] = -1;
									}
								}
							}

							m_xInventoryWnd.DeleteInvenItem(stInvenItem[nCnt1].xItem.m_stItemInfo.nMakeIndex, stInvenItem[nCnt1].xItem.m_stItemInfo.stStdItem.szName);
							ZeroMemory(&stInvenItem[nCnt1],	sizeof(INVENITEMSET));
							break;
						}						
					}
				}
			}
		}

		INVENITEMSET	stNonCheckedInvenItem[_MAX_INVEN_ITEM];
		memcpy(stNonCheckedInvenItem, m_xInventoryWnd.m_stInventoryItem, sizeof(INVENITEMSET)*_MAX_INVEN_ITEM);

		memcpy(m_xInventoryWnd.m_stInventoryItem, stCheckedInvenItem, sizeof(INVENITEMSET)*_MAX_INVEN_ITEM);
		memcpy(m_xInventoryWnd.m_shItemSetInfo, shCheckedItemSetInfo, _INVEN_TOTAL_CELL*sizeof(SHORT));

		for ( nCnt1 = 0; nCnt1 < _MAX_INVEN_ITEM; nCnt1++ )
		{
			if ( stNonCheckedInvenItem[nCnt1].bSetted )
			{
				m_xInventoryWnd.AddInvenItem(stNonCheckedInvenItem[nCnt1].xItem, 0, FALSE);
			}
		}

		if ( nCnt2 == 0 )
		{
			GetCurrentDirectory(MAX_PATH,szItemFile);
			
			CloseHandle(hFile);
			sprintf(szItemFile, "%s\\Data\\%s.itms", szItemFile,  szName);

			//.itms 파일이 깨져있을 공산이 큼...삭제
			DeleteFile(szItemFile);

			return FALSE;
		}
	
		CloseHandle(hFile);

		return TRUE;
	}

	return FALSE;
}




/******************************************************************************************************************

	함수명 : CInterface::SaveItemPos()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : CHAR* szName
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CInterface::SaveItemPos(CHAR* szName)
{
	if( szName == "" )
	{
		return FALSE;
	}
	
	HANDLE	hFile;
	CHAR	szItemFile[MAX_PATH];

	DWORD dwCur = timeGetTime();

	if ( dwCur - m_dwSaveItemTimer > 2000 )
	{
		m_dwSaveItemTimer = dwCur;

		ZeroMemory(szItemFile, MAX_PATH);
		g_xMainWnd.StringPlus(szItemFile, ".\\Data\\", szName, ".itms", "");
		hFile = CreateFile(szItemFile, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		if ( hFile != INVALID_HANDLE_VALUE )
		{
			DWORD		dwWriteLen;

			WriteFile(hFile, m_xInventoryWnd.m_stInventoryItem, sizeof(INVENITEMSET)*_MAX_INVEN_ITEM, &dwWriteLen, NULL);
			WriteFile(hFile, m_xInventoryWnd.m_shItemSetInfo, _INVEN_TOTAL_CELL*sizeof(SHORT), &dwWriteLen, NULL);
			WriteFile(hFile, m_xBeltWnd.m_stBeltItem, sizeof(ITEMSET)*_MAX_BELT_ITEM , &dwWriteLen, NULL);

			CloseHandle(hFile);

			return TRUE;
		}
	}

	return FALSE;
}

VOID CInterface::ItemClickSound(CItem* pxItem)
{
	switch ( pxItem->m_stItemInfo.stStdItem.bStdMode )
	{
	case  0:
		g_SoundManager.SndmngrPlayWavSound(_SOUND_CLICK_DRUG, 0, 0);
		break;
	case 31:
		{
			// 물약류.
			if ( pxItem->m_stItemInfo.stStdItem.bShape < 106 )
			{
				g_SoundManager.SndmngrPlayWavSound(_SOUND_CLICK_DRUG, 0, 0);
			}
			// 전서류.
			else
			{
				g_SoundManager.SndmngrPlayWavSound(_SOUND_CLICK_ITEM, 0, 0);
			}
		}
		break;
	case  5:
	case  6:
		g_SoundManager.SndmngrPlayWavSound(_SOUND_CLICK_WEAPON, 0, 0);
		break;
	case 10:
	case 11:
		g_SoundManager.SndmngrPlayWavSound(_SOUND_CLICK_ARMOR, 0, 0);
		break;
	case 22:
	case 23:
		g_SoundManager.SndmngrPlayWavSound(_SOUND_CLICK_RING, 0, 0);
		break;
	case 24:
	case 26:
		{
			if ( g_xMainWnd.BelongStr(pxItem->m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(2641)) || g_xMainWnd.BelongStr(pxItem->m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(2642)) )
			{
				g_SoundManager.SndmngrPlayWavSound(_SOUND_CLICK_GROBES, 0, 0);
			}
			else
			{
				g_SoundManager.SndmngrPlayWavSound(_SOUND_CLICK_ARMRING, 0, 0);
			}
			break;
		}
	case 19:
	case 20:
	case 21:
		g_SoundManager.SndmngrPlayWavSound(_SOUND_CLICK_NECK, 0, 0);
		break;
	case 15:
		g_SoundManager.SndmngrPlayWavSound(_SOUND_CLICK_HELMET, 0, 0);
		break;
	default:
		g_SoundManager.SndmngrPlayWavSound(_SOUND_CLICK_ITEM, 0, 0);
		break;
	}
}


VOID CInterface::ItemUseSound(CItem* pxItem)
{
	switch ( pxItem->m_stItemInfo.stStdItem.bStdMode )
	{
	case  0:
		g_SoundManager.SndmngrPlayWavSound(_SOUND_CLICK_DRUG, 0, 0);
		break;
	case  1:
	case  2:
		g_SoundManager.SndmngrPlayWavSound(_SOUND_EAT_DRUG, 0, 0);
		break;
	}
}


int
CInterface::FindSameItemInBelt(CItem xItem)
{
	for (int nI=0; nI<_MAX_BELT_ITEM; nI++)
	{
		if ( m_stBeltItem[nI].bSetted )
		{
			if (strcmp(m_stBeltItem[nI].xItem.m_stItemInfo.stStdItem.szName, xItem.m_stItemInfo.stStdItem.szName) == 0)
				return nI;
		}
	}
	return -1;
}


VOID
CInterface::ChatListClear()
{
	CListNode < CHAT >	*pNode;
	CListNode < CHAT >	*pNodeTemp;
	CHAT*				pstChat = NULL;

	for ( pNode = m_xChatlist.GetHead(); pNode; )
	{
		pNodeTemp = pNode->GetNext();

		pstChat = m_xChatlist.RemoveNode(pNode);

		if ( pstChat )
		{
			delete((CHAT*) pstChat);
			pstChat = NULL;
		}
		pNode = pNodeTemp;
	}
}

BOOL CInterface::UpdateUserPicInfo(CHAR *szName, INT nFaceImg)
{
	CHAR	szFileName[MAX_PATH];

	if ( GetCurrentDirectory(MAX_PATH, szFileName))
	{
		if ( szFileName[0] == '\0' )
		{
			return FALSE;
		}

		strcat(szFileName, "\\UserPic.ini");

		CHAR szTemp[MAX_PATH];

		// 파일 검색
		CHAR	szSearchKey[MAX_PATH];
		char	*pszName = NULL;
		pszName = g_xGameProc.CheckAbnormalName(szName);

		sprintf(szSearchKey, "%s_%s", g_szServerName, pszName );

		GetPrivateProfileString("UserPic", szSearchKey, "", szTemp, MAX_PATH, szFileName);

		if ( szTemp[0] != '0' )
		{
			INT nNum = atoi(szTemp);

			if ( nNum == nFaceImg )
			{
				CHAR szNewDir[MAX_PATH], szFileName[MAX_PATH];

				GetCurrentDirectory(MAX_PATH, szFileName);

				sprintf( szNewDir, "%s\\Data", szFileName );
				SetCurrentDirectory(szNewDir);

				if ( !LoadUserPic(szName, nFaceImg) )
				{
					// 파일 다운로드(타이머 사용)
					DWORD dwTemp = timeGetTime();

					if ( dwTemp - m_dwFaceImgTimer > 1000 )
					{
						m_dwFaceImgTimer = dwTemp;
						g_xClientSocket.RequestFaceImg(szName);
					}

					SetCurrentDirectory(szFileName);
					return FALSE;
				}
				else
				{
					SetCurrentDirectory(szFileName);
					return TRUE;
				}
			}
			else
			{
				// 파일 다운로드(타이머 사용)
				DWORD dwTemp = timeGetTime();

				if ( dwTemp - m_dwFaceImgTimer > 1000 )
				{
					m_dwFaceImgTimer = dwTemp;
					g_xClientSocket.RequestFaceImg(szName);
				}
			}
		}
	}
	return FALSE;
}

BOOL CInterface::LoadUserPic(CHAR *szName, INT nDate)
{
	UINT nWidth;
	UINT nHeight;

	CHAR	szFileName[MAX_PATH];
	
	if ( GetCurrentDirectory(MAX_PATH, szFileName))
	{
		if ( szFileName[0] == '\0' )
		{
			return FALSE;
		}

		char	*pszName = NULL;
		pszName = g_xGameProc.CheckAbnormalName(szName);

		sprintf(szFileName, "%s\\%s_%s.fac", szFileName,  g_szServerName, pszName);

		if ( strcmp(szName, g_xGameProc.m_xMyHero.m_szName) == 0 )
		{
			if ( !LoadFACFile(szFileName, &g_xGameProc.m_xMyHero.m_hbmFaceImg) )
				return FALSE;
		}
		else
		{
			if ( !LoadFACFile(szFileName, &g_xGameProc.m_pxExplainActor->m_hbmFaceImg) )
				return FALSE;
		}
	}
	return TRUE;
}

VOID CInterface::DrawJobPic(BYTE bJob)
{
	INT nIconImgIndex = 0;
	switch (bJob)
	{
		case _JOB_JUNSA:
			{
				if (g_xGameProc.m_pxExplainActor->m_stFeature.bGender == _GENDER_MAN)
					nIconImgIndex = 650;
				else
					nIconImgIndex = 651;
			}
			break;
		case _JOB_SULSA:
			{
				if (g_xGameProc.m_pxExplainActor->m_stFeature.bGender == _GENDER_MAN)
					nIconImgIndex = 652;
				else
					nIconImgIndex = 653;
			}
			break;
		case _JOB_DOSA:
			{
				if (g_xGameProc.m_pxExplainActor->m_stFeature.bGender == _GENDER_MAN)
					nIconImgIndex = 654;
				else
					nIconImgIndex = 655;
			}
			break;
	}

	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].NewSetIndex(nIconImgIndex) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcMain.left+6, m_ptFrameLoc.y+42, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_pbCurrImage);
	}
}

BOOL CInterface::LoadFACFile(char *szFileName, CWHSurface *m_hbmFaceImg)
{

	// 암호화 루틴해제.
	char* pszBuf = NULL;

	crypto_seed s = {(char) 0xF0, (char) 0x39, (char) 0xAB, (char) 0x8E, 0x9FDE1A93};
	crypto::setSeed( &s );

	FILE *fp = fopen( szFileName, "rb" );

	if ( !fp )
	{
		return FALSE;
	}

	int len = _filelength( _fileno( fp ) );
	pszBuf = new char[ len ];

	if ( !pszBuf )
	{
		fclose( fp );
		delete [] pszBuf;
		return FALSE;
	}

	fread( pszBuf, 1, len, fp );
	fclose( fp );

	if ( !crypto::decrypt( (unsigned char *)pszBuf, len ) )
	{
		delete[] pszBuf;
		return FALSE;
	}

	CHAR* pszTemp = pszBuf+8;

	CHAR szSave[MAX_PATH];
	INT nLen = strlen(szFileName);

	strncpy( szSave, szFileName, nLen - 4 );
	szSave[nLen-4] = 0;
	sprintf( szSave, "%s.jpg", szSave );

	fp = fopen( szSave, "wb" );

	fwrite( pszTemp, sizeof( char ), len-8, fp );
	fclose( fp );

	// 암호화 루틴해제 끝

	UINT	nWidth, nHeight;
	BYTE	*buf = NULL;
	buf = g_xGameProc.JpegFileToRGB(szSave, &nWidth, &nHeight);

	DeleteFile(szSave);

	if ( buf == NULL )
		return FALSE;

	if ( g_xGameProc.BGRFromRGB(buf, nWidth, nHeight) == FALSE )
		return FALSE;

	if ( g_xGameProc.VertFlipBuf(buf, nWidth * 3, nHeight) == FALSE )
		return FALSE;

	UINT nWidthDW = 0;
	BYTE	*temp = NULL;
	temp = g_xGameProc.MakeDwordAlignedBuf(buf,nWidth,nHeight,&nWidthDW);

	if ( temp == NULL )
		return FALSE;
	
	WORD *wpFaceImg = NULL;
	wpFaceImg = new WORD[sizeof(WORD) * nWidth * nHeight];

	INT nNewWidth = int(( nWidth + 3 ) / 4) * 4;

	g_xGameProc.Convert24To16(temp, 24, wpFaceImg, nWidth, nHeight);

	m_hbmFaceImg->ReleaseSurface();
	m_hbmFaceImg->CreateOffScreenSurface(g_xMainWnd.GetDirectDraw(), nNewWidth, nHeight);
	m_hbmFaceImg->CopyImageToSurfaceDx(nWidth, nHeight, nNewWidth, wpFaceImg);

	if ( wpFaceImg != NULL )
	{
		delete [] wpFaceImg;
	}
	return TRUE;
}

VOID CInterface::ShowGroupMember()
{
	CGroupMember*	pGroupMember = NULL;
	CListNode <	CGroupMember > *pNode;

	CActor*					pxActor = NULL;
	CListNode < CActor >	*pNodeActor;
	INT						nCnt = 0;

	if ( m_xGroupWnd.m_xGroupList.GetCount() )
	{
		for ( pNode = m_xGroupWnd.m_xGroupList.GetHead(); pNode; pNode = pNode->GetNext() )
		{
			pGroupMember = pNode->GetData();

			if ( pGroupMember )
			{
				if ( strcmp( g_xGameProc.m_xMyHero.m_szName, pGroupMember->szMemberName ) == 0 )
				{
					FLOAT	fHPPercent	= (FLOAT)((FLOAT)g_xGameProc.m_xMyHero.m_bHPPercent/100);
					RECT	rcHP		= {0, 0, (LONG)(36*fHPPercent), 4};

					RECT	rcFrame, rcFrame2;
					RECT	rcName = { 2, 30*nCnt + 2, 70, 30*nCnt+17 };
					SetRect(&rcFrame, 0, 0, (INT)(69*fHPPercent), 5);
					SetRect(&rcFrame2, 0, 0, 69, 5);

					g_xMainWnd.PutsHan(NULL, rcName, RGB(255, 255, 0), RGB(0, 0, 0), g_xGameProc.m_xMyHero.m_szName );

					if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(316) )
					{
 						g_xMainWnd.DrawWithImageForComp(
										2, 30*nCnt + 19,
										&rcFrame2,
										(WORD*)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
					}

					if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(315) )
					{
 						g_xMainWnd.DrawWithImageForComp(
										2, 30*nCnt + 19,
										&rcFrame,
										(WORD*)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
					}
					nCnt++;
				}

				for ( pNodeActor = g_xGameProc.m_xActorList.GetHead(); pNodeActor; pNodeActor = pNodeActor->GetNext())
				{
					pxActor = pNodeActor->GetData();

					if ( strcmp( pxActor->m_szName, pGroupMember->szMemberName ) == 0 )
					{
						FLOAT	fHPPercent	= (FLOAT)((FLOAT)pxActor->m_bHPPercent/100);
						RECT	rcHP		= {0, 0, (LONG)(36*fHPPercent), 4};

						RECT	rcFrame, rcFrame2;
						RECT	rcName = { 2, 30*nCnt + 2, 70, 30*nCnt+17 };
						SetRect(&rcFrame, 0, 0, (INT)(69*fHPPercent), 5);
						SetRect(&rcFrame2, 0, 0, 69, 5);

						g_xMainWnd.PutsHan(NULL, rcName, RGB(255, 255, 0), RGB(0, 0, 0), pxActor->m_szName);

						if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(316) )
						{
 							g_xMainWnd.DrawWithImageForComp(
											2, 30*nCnt + 19,
											&rcFrame2,
											(WORD*)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
						}

						if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(315) )
						{
 							g_xMainWnd.DrawWithImageForComp(
											2, 30*nCnt + 19,
											&rcFrame,
											(WORD*)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
						}
						nCnt++;
					}
				}
			}
		}
	}
}

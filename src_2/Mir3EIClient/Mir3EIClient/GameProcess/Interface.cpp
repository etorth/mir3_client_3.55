/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"

#define BELT_POS_X	0
#define BELT_POS_Y	457
#define BELT_WND_WIDTH	512
#define BELT_WND_HEIGHT 48

/******************************************************************************************************************

	함수명 : CInterface::CInterface()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : 

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
	m_nIdxMsgBox		= 0;
	m_nFstLine			= 0;
	m_shBeltHeight		= 0;
	m_bShowKey			= FALSE;
	m_bMoveFocusedWnd	= FALSE;
	m_bBeltState		= _BELT_STATE_STAY;

	SetRect(&m_rcMain,  0, 0, 0, 0);
	SetRect(&m_rcChat,  0, 0, 0, 0);

	ZeroMemory(&m_stCommonItem, sizeof(ITEMSET));

	m_xClientSysMsg.Init();

	m_pxInterImg = NULL;
//YDQ	m_xInterImgEx.Init();

	m_xStatusWnd.Init();
	m_xStoreWnd.Init();
	m_xGuildWnd.Init();
	m_xGroupWnd.Init();
	m_xChatPopWnd.Init();
	m_xExchangeWnd.Init();
	m_xGroupPopWnd.Init();
	m_xInventoryWnd.Init();
	m_xGuildMasterWnd.Init();

	for ( INT nCnt = 0; nCnt < _MAX_INTER_BTN; nCnt++ )
	{
		m_xInterBtn[nCnt].Init();
	}

	m_xScrlBar.Init();

	m_xChat.ClearAllNodes();
	m_xWndOrderList.ClearAllNodes();
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
	m_xStoreWnd.Destroy();
	m_xStatusWnd.Destroy();
	m_xGuildWnd.Destroy();
	m_xGroupWnd.Destroy();
	m_xExchangeWnd.Destroy();
	m_xGuildMasterWnd.Destroy();
	m_xGroupPopWnd.Destroy();
	m_xChatPopWnd.Destroy();

	for ( INT nCnt = 0; nCnt < _MAX_INTER_BTN; nCnt++ )
	{
		m_xInterBtn[nCnt].Destroy();
	}

	m_xChat.ClearAllNodes();
	m_xWndOrderList.ClearAllNodes();

	Init();
}


VOID CInterface::CreateInterface(CImageHandler* pxImgHandler)
{
	m_pxInterImg = &(pxImgHandler->m_xImageList[_IMAGE_INTER]);

	//------------------------------------------------------------------------------------------------------------
	// 채팅에디트 윈도우 위치지정.
	MoveWindow(g_xChatEditBox.GetSafehWnd(), 
			   g_xMainWnd.m_rcWindow.left+_INPUT_EDITWND_XPOS, g_xMainWnd.m_rcWindow.top+_INPUT_EDITWND_YPOS,
			   _INPUT_EDITWND_WIDTH, _INPUT_EDITWND_HEIGHT, TRUE);

	if ( m_pxInterImg->NewSetIndex(_WNDIMGIDX_MAIN) )
	{
		SetRect(&m_rcMain, 
				0, (600-m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight), 
				m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth, 600);
	}
	//------------------------------------------------------------------------------------------------------------

	//------------------------------------------------------------------------------------------------------------
	// 좔莖혐堵.
	SetRect(&m_rcChat, 188, 490, 532, 560);

	//------------------------------------------------------------------------------------------------------------

	//------------------------------------------------------------------------------------------------------------
	// 관범.
	m_xInventoryWnd.CreateInventoryWnd(_WND_ID_INVENTORY, m_pxInterImg, _WNDIMGIDX_INVENTORY, 0, 0, 280, 464, TRUE);
	//榴檄
	m_xStatusWnd.CreateStatusWnd(_WND_ID_STATUS, m_pxInterImg, _WNDIMGIDX_ITEMSET, 510, 0, 330, 468, TRUE);
	//닸뇨
	m_xStoreWnd.CreateStoreWnd(_WND_ID_STORE, m_pxInterImg, _WNDIMGIDX_STORE, 0, 0, 290, 224, TRUE);
	//슥弄
	m_xExchangeWnd.CreateExchangeWnd(_WND_ID_EXCHANGE, m_pxInterImg, _WNDIMGIDX_EXCHANGE, 0, 0, 0, 0, TRUE);
	//契삔
	m_xGuildMasterWnd.CreateGuildMasterWnd(_WND_ID_GUILDMASTER, m_pxInterImg, _WNDIMGIDX_GUILDMASTER, 0, 0, 0, 0, TRUE);
//	m_xGuildWnd.CreateGuildWnd(_WND_ID_GUILD, &m_xInterImgEx, _WNDIMGIDX_GUILD, 0, 0, 540, 442, TRUE);

	//莉
	m_xGroupWnd.CreateGroupWnd(_WND_ID_GROUP, m_pxInterImg, _WNDIMGIDX_GROUP, 0, 0, 260, 245, TRUE);
	//YDQ	m_xGroupPopWnd.CreateGroupPopWnd(_WND_ID_GROUPPOP, &m_xInterImgEx, _WNDIMGIDX_GROUPPOP, 0, 0, 260, 114, TRUE);
	//좔莖
	m_xChatPopWnd.CreateChatPopWnd(_WND_ID_CHATPOP, m_pxInterImg, _WNDIMGIDX_CHATPOP, 0, 0, 0, 0, TRUE);

	//꾸鱗
	m_xOptionWnd.CreateOptionWnd(_WND_ID_OPTION, m_pxInterImg, _WNDIMGIDX_OPTION, 0, 0, 0, 0, TRUE);
	
	m_xQuestWnd.CreateQuestWnd(_WND_ID_QUEST, m_pxInterImg, _WNDIMGIDX_QUEST, 0, 0, 0, 0, TRUE);
	//쯩
	m_xHorseWnd.CreateHorseWnd(_WND_ID_HORSE, m_pxInterImg, _WNDIMGIDX_HORSE, 0, 0, 0, 0, TRUE);

	//NPC
	m_xNPCWnd.CreateNPCChatWnd(_WND_ID_NPCCHAT, m_pxInterImg, _WNDIMGIDX_NPCCHAT, 0, 0, 388, 204, TRUE);				// 용기

	// 놓迦뺏객큐
	m_xInterBtn[ _BTN_ID_CHANGE	].CreateGameBtn(m_pxInterImg, 1170, 1170, m_rcMain.left+638, m_rcMain.top+7);//슥弄
	m_xInterBtn[ _BTN_ID_MINIMAP].CreateGameBtn(m_pxInterImg, 1172, 1172, m_rcMain.left+638, m_rcMain.top+41);//鬼뒈暠
	m_xInterBtn[ _BTN_ID_MUGONG	].CreateGameBtn(m_pxInterImg, 1174, 1174, m_rcMain.left+638, m_rcMain.top+76);//Unknown

	m_xInterBtn[ _BTN_ID_EXIT	].CreateGameBtn(m_pxInterImg, 1176, 1176, m_rcMain.left+8, m_rcMain.top+72);//藁놔객큐
	m_xInterBtn[ _BTN_ID_LOGOUT	].CreateGameBtn(m_pxInterImg, 1178, 1178, m_rcMain.left+109, m_rcMain.top+72);//logout
	m_xInterBtn[ _BTN_ID_GROUP	].CreateGameBtn(m_pxInterImg, 1180, 1181, m_rcMain.left+706, m_rcMain.top+8);	// 莉
	m_xInterBtn[ _BTN_ID_GUILD	].CreateGameBtn(m_pxInterImg, 1182, 1183, m_rcMain.left+674, m_rcMain.top+11);	// 契삔

	m_xInterBtn[ _BTN_ID_BELT	].CreateGameBtn(m_pxInterImg, 1205, 1205, m_rcMain.left+148, m_rcMain.top+2);	// BELT 우쌥으

	m_xInterBtn[ _BTN_ID_MAGIC	].CreateGameBtn(m_pxInterImg,1184, 1184, m_rcMain.left+739, m_rcMain.top+33);	// 침랬
	m_xInterBtn[ _BTN_ID_POPUP	].CreateGameBtn(m_pxInterImg,1168, 1168, m_rcMain.left+619, m_rcMain.top+6);	// 좔莖으뎐놔
	m_xInterBtn[ _BTN_ID_QUEST	].CreateGameBtn(m_pxInterImg,1186, 1187, m_rcMain.left+742, m_rcMain.top+11);	// 훨蛟.
	m_xInterBtn[ _BTN_ID_OPTION	].CreateGameBtn(m_pxInterImg,1188, 1189, m_rcMain.left+706, m_rcMain.top+72);	// ?阮?
	m_xInterBtn[ _BTN_ID_HELP	].CreateGameBtn(m_pxInterImg,1190, 1191, m_rcMain.left+742, m_rcMain.top+61);	// help
	m_xInterBtn[ _BTN_ID_HORSE	].CreateGameBtn(m_pxInterImg,1192, 1193, m_rcMain.left+674, m_rcMain.top+61);	// horse
	m_xInterBtn[ _BTN_ID_BAG	].CreateGameBtn(m_pxInterImg,1194, 1195, m_rcMain.left+682, m_rcMain.top+33);	// .
	m_xInterBtn[ _BTN_ID_CHAR	].CreateGameBtn(m_pxInterImg,1196, 1197, m_rcMain.left+711, m_rcMain.top+31);	// 실?グ늚?

	//버땡係
	m_xScrlBar.CreateScrlBar(m_pxInterImg, 1207, _MAX_CHATLINE, 12, 56, 12);

	m_xMsgBox.Load(m_pxInterImg);	// 용기
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
	if ( pszMsg )
	{	
		if ( pszMsg[0] != NULL )
		{
			INT  nCnt;
			CHAT stChat;
			INT	 nLineCnt;
			CHAR pszDivied[MAX_PATH*2];
			CHAR pszArg[5][MAX_PATH];

			m_xChatPopWnd.MsgAdd(dwFontColor, dwFontBackColor, pszMsg);

			ZeroMemory(pszDivied, MAX_PATH*2);
			ZeroMemory(pszArg,	  MAX_PATH*5);

			g_xMainWnd.StringDivide(m_rcChat.right-m_rcChat.left, nLineCnt, pszMsg, pszDivied);

			sscanf(pszDivied, "%[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c", pszArg[0], pszArg[1], pszArg[2], pszArg[3], pszArg[4]);

			if ( nLineCnt > 5 )		
			{
				nLineCnt = 5;
			}

			// 문자열 삽입.
			for ( nCnt = 0; nCnt < nLineCnt; nCnt++ )
			{
				// 칸이 다음으로 갈조건.
				if ( m_xChat.GetCounter() - m_nFstLine == _MAX_CHATLINE )
				{
					m_nFstLine++;
				}

				stChat.dwFontColor = dwFontColor;
				stChat.dwBackColor = dwFontBackColor;
				strcpy(stChat.pszChat, pszArg[nCnt]);

				m_xChat.AddNode(stChat);
			}

			// 최대저장라인 검사해서 그이상이면 삭제한다.
			while ( m_xChat.GetCounter() >= 50 )
			{
				m_xChat.MoveCurrentToTop();
				m_xChat.DeleteCurrentNode();

				if ( m_nFstLine > 0 )
					m_nFstLine--;
			}
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
				m_xInventoryWnd.ShowInventoryWnd();
				break;
			case _WND_ID_STATUS:
				m_xStatusWnd.ShowStatusWnd();
				break;
			case _WND_ID_STORE:
				m_xStoreWnd.ShowStoreWnd();
				break;
			case _WND_ID_EXCHANGE:
				m_xExchangeWnd.ShowExchangeWnd();
				break;
			case _WND_ID_GUILDMASTER:
				m_xGuildMasterWnd.ShowGuildMasterWnd();
				break;
			case _WND_ID_GUILD:
				m_xGuildWnd.ShowGuildWnd();
				break;
			case _WND_ID_GROUP:
				m_xGroupWnd.ShowGroupWnd();
				break;
			case _WND_ID_GROUPPOP:
				m_xGroupPopWnd.ShowGroupPopWnd();
				break;
			case _WND_ID_CHATPOP:
				m_xChatPopWnd.ShowChatPopWnd();
				break;
			case _WND_ID_NPCCHAT:					// 용기
				m_xNPCWnd.ShowNPCChatWnd();
				break;

			case _WND_ID_QUEST:
				m_xQuestWnd.ShowQuestWnd();
				break;
			case _WND_ID_OPTION:
				m_xOptionWnd.ShowOptionWnd();
				break;
			case _WND_ID_HORSE:
				m_xHorseWnd.ShowHorseWnd();
				break;
			}			

			m_xWndOrderList.MoveNextNode();
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
VOID CInterface::ShowChatList()
{
	if ( !m_xChat.CheckEmpty() )
	{
		INT		nCnt, nShowLine;
		LPCHAT	pstChat;

		m_xChat.MoveCurrentToTop();
		m_xChat.MoveNode(m_nFstLine);

		nShowLine = ((m_xChat.GetCounter() - m_nFstLine ) >= _MAX_CHATLINE) ?  _MAX_CHATLINE : m_xChat.GetCounter() - m_nFstLine;
		
		for ( nCnt = 0; nCnt < nShowLine; nCnt++ )
		{
			pstChat = m_xChat.GetCurrentData();

			g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(),
							   m_rcChat.left, m_rcChat.top+nCnt*15,
							   pstChat->dwBackColor, pstChat->dwFontColor, pstChat->pszChat);

			m_xChat.MoveNextNode();
		}
	}
}



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
	INT nX, nY, nCnt;

	ShowBeltItem();

	ShowWndList();

	//柑깃苟돨膠틔
	if ( m_stCommonItem.bSetted && !m_stCommonItem.bIsHideItem )
	{
		nX = ptMousePos.x - _INVENTORY_CELL_WIDTH /2;
		nY = ptMousePos.y - _INVENTORY_CELL_HEIGHT/2;
		m_stCommonItem.xItem.DrawItem(nX, nY);
	}


	if ( m_pxInterImg->NewSetIndex(_WNDIMGIDX_MAIN) )
	{
 		g_xMainWnd.DrawWithImageForCompClipRgn(m_rcMain.left, m_rcMain.top,	m_rcMain.right-m_rcMain.left, m_rcMain.bottom-m_rcMain.top,
											   (WORD*)m_pxInterImg->m_pbCurrImage, _CLIP_WIDTH, 600);
	}
	//ydq董珂警속돨
	if ( m_pxInterImg->NewSetIndex(_WNDIMGIDX_CHATPOP-1) )
	{
		g_xMainWnd.DrawWithImageForCompClipRgn(m_rcMain.left+178, m_rcMain.top-18,
			m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth, m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight,
			(WORD*)m_pxInterImg->m_pbCurrImage, _CLIP_WIDTH, 600);
	}

	//좔莖斤口
	ShowChatList();
	ShowGameStatus();


	for ( nCnt = 0; nCnt < _MAX_INTER_BTN; nCnt++)
	{
		m_xInterBtn[nCnt].ShowGameBtn();
	}

	// 스크롤바.
	m_xScrlBar.ShowScrlBar(m_rcMain.left+620, m_rcMain.top+40, m_nFstLine, m_xChat.GetCounter());

	// 클라이언트메시지(왼쪽상단).
	m_xClientSysMsg.ShowSysMsg(nLoopTime, 30, 30);

	// 용기
	m_xMsgBox.RenderMessageBox(0);

	ShowMagicKey();

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
 			g_xMainWnd.DrawWithImageForCompClipRgn(BELT_POS_X - 115, BELT_POS_Y-m_shBeltHeight,
												   m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth,
												   m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight,
												   (WORD*)m_pxInterImg->m_pbCurrImage, _CLIP_WIDTH, 600);
			m_xInventoryWnd.SetBeltRect(BELT_POS_X, BELT_POS_Y-m_shBeltHeight, BELT_POS_X+BELT_WND_WIDTH, BELT_POS_Y-m_shBeltHeight+BELT_WND_HEIGHT);

			// 벨트 아이템 그리기.
			for ( INT nCnt = 0; nCnt < _MAX_BELT_ITEM; nCnt++ )
			{
				if ( m_xInventoryWnd.m_stBeltItem[nCnt].bSetted )
				{
					nX = BELT_POS_X + 8 + nCnt*40;
					nY = BELT_POS_X - 6  - m_shBeltHeight;

					m_xInventoryWnd.m_stBeltItem[nCnt].xItem.DrawItem(nX, nY);
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
	FLOAT	fMyHPRate;
	FLOAT	fMyMPRate;				
	FLOAT	fMyWetRate;				
	FLOAT	fMyExpRate;
	WORD	wJobIcon;
	WORD	wImgNum;
	CHAR	pszBuff[MAX_PATH];
	RECT	rcStats;
	DWORD	dwFntClr;

	BYTE	bMyJob  = g_xGameProc.m_pMyHero->m_bJob;
	BYTE	bMyLevel= g_xGameProc.m_pMyHero->m_stAbility.bLevel;
	WORD	wMyAC   = g_xGameProc.m_pMyHero->m_stAbility.wAC;
	WORD	wMyDC   = g_xGameProc.m_pMyHero->m_stAbility.wDC;
	WORD	wMyMC   = g_xGameProc.m_pMyHero->m_stAbility.wMC;
	WORD	wMySC   = g_xGameProc.m_pMyHero->m_stAbility.wSC;
	BYTE	bDay	= g_xGameProc.m_bDayState;

	WORD	wHP		= g_xGameProc.m_pMyHero->m_stAbility.wHP;
	WORD	wMP		= g_xGameProc.m_pMyHero->m_stAbility.wMP;
	WORD	wWet	= g_xGameProc.m_pMyHero->m_stAbility.wWeight;
	DWORD	dwExp	= g_xGameProc.m_pMyHero->m_stAbility.dwExp;

	BYTE	bJob	= g_xGameProc.m_pMyHero->m_bJob;
	
	// 하루의 상태치(밤, 낮, 저녁, 새벽)
	switch ( bDay )
	{
	case _DAYSTATE_DAY:
//		wImgNum = 130;
		wImgNum = 1200;
		break;
	case _DAYSTATE_DUSK:
//		wImgNum = 131;
		wImgNum = 1201;
		break;
	case _DAYSTATE_NIGHT:
//		wImgNum = 132;
		wImgNum = 1202;
		break;
	case _DAYSTATE_DAWN:
//		wImgNum = 133;
		wImgNum = 1204;
		break;
	}
	if ( m_pxInterImg->NewSetIndex(wImgNum) )
	{
 		g_xMainWnd.DrawWithImageForComp(m_rcMain.left+384/*684*/, m_rcMain.top-9/*+70*/,
										m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth,
										m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight,
										(WORD*)m_pxInterImg->m_pbCurrImage, _CLIP_WIDTH, 600);
	}

	// HP, MP찍기.
	// 비율검사.
	if ( wHP )	
	{
		fMyHPRate = (FLOAT)((FLOAT)wHP/(FLOAT)g_xGameProc.m_pMyHero->m_stAbility.wMaxHP);

		if ( fMyHPRate > 1.0f ) 
		{
			fMyHPRate = 1.0f;
		}
	}
	else			
	{
		fMyHPRate = 0;
	}

	if ( wMP )		
	{
		fMyMPRate = (FLOAT)((FLOAT)wMP/(FLOAT)g_xGameProc.m_pMyHero->m_stAbility.wMaxMP);

		if ( fMyMPRate > 1.0f ) 
		{
			fMyMPRate = 1.0f;
		}
	}
	else			
	{
		fMyMPRate = 0;
	}

	if ( dwExp )	
	{
		fMyExpRate = (FLOAT)((FLOAT)dwExp/(FLOAT)g_xGameProc.m_pMyHero->m_stAbility.dwMaxExp);

		if ( fMyExpRate > 1.0f ) 
		{
			fMyExpRate = 1.0f;
		}
	}
	else			
	{
		fMyExpRate = 0;
	}

	if ( wWet )		
	{
		fMyWetRate = (FLOAT)((FLOAT)wWet /(FLOAT)g_xGameProc.m_pMyHero->m_stAbility.wMaxWeight);

		if ( fMyWetRate > 1.0f ) 
		{
			fMyWetRate = 1.0f;
		}
	}
	else			
	{
		fMyWetRate = 0;
	}

	if ( m_pxInterImg->NewSetIndex(1163) )
	{
		RECT rcHP = { 0, m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight-(m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight*fMyHPRate), 
					  m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth, m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight };
 		g_xMainWnd.DrawWithImageForComp(m_rcMain.left+33, m_rcMain.top+8, rcHP, (WORD*)m_pxInterImg->m_pbCurrImage);
	}

	if ( m_pxInterImg->NewSetIndex(1164) )
	{
		RECT rcMP = { 0, m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight-(m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight*fMyMPRate), 
					  m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth, m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight };
 		g_xMainWnd.DrawWithImageForComp(m_rcMain.left+73, m_rcMain.top+8, rcMP, (WORD*)m_pxInterImg->m_pbCurrImage);
	}

	// EXP, WET 
	if ( m_pxInterImg->NewSetIndex(1166) )
	{
		RECT rcEXP = { 0, m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight-(m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight*fMyExpRate), 
					   m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth, m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight };
 		g_xMainWnd.DrawWithImageForComp(m_rcMain.left+152, m_rcMain.top+27, rcEXP, (WORD*)m_pxInterImg->m_pbCurrImage);
	}

	if ( m_pxInterImg->NewSetIndex(1167) )
	{
		RECT rcWET = { 0, m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight-(m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight*fMyWetRate), 
					  m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth, m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight };
 		g_xMainWnd.DrawWithImageForComp(m_rcMain.left+166, m_rcMain.top+27, rcWET, (WORD*)m_pxInterImg->m_pbCurrImage);
	}

	dwFntClr = RGB(225, 225, 0);
	// 레벨찍6기.
	//矜狼踞좔莖으긴뺏랍맣긴
	sprintf(pszBuff, "%d", g_xGameProc.m_pMyHero->m_stAbility.bLevel);
	SetRect(&rcStats, m_rcMain.left+394, m_rcMain.top+2, m_rcMain.left+408, m_rcMain.top+16);
	g_xMainWnd.PutsHan(NULL, rcStats, dwFntClr, RGB(0, 0, 0), pszBuff, g_xMainWnd.CreateGameFont("궁서체", 10, 0, FW_BOLD));

	dwFntClr = RGB(255, 255, 200);
	sprintf(pszBuff, "%s : [%d,%d]", g_xGameProc.m_szMapName, g_xGameProc.m_pMyHero->m_wPosX, g_xGameProc.m_pMyHero->m_wPosY);
	SetRect(&rcStats, 9, 579, 139, 592);
	g_xMainWnd.PutsHan(NULL, rcStats, dwFntClr, RGB(0, 0, 0), pszBuff);

	//FIXME 꼇츠겜痂척雷鋼
	dwFntClr = RGB(255, 200, 50);
	// 직업별 아이콘및 특성치 찍기.
	sprintf(pszBuff, "%d-%d", LOBYTE(wMyAC), HIBYTE(wMyAC));
	SetRect(&rcStats, 662, 577, 703, 590);
	g_xMainWnd.PutsHan(NULL, rcStats, dwFntClr, RGB(0, 0, 0), pszBuff);

	SetRect(&rcStats, 750, 577, 791, 590);
	switch ( bJob )
	{
	case _JOB_DOSA:		
		{
			wJobIcon = 66;
			wImgNum	 = 123;
			sprintf(pszBuff, "%d-%d", LOBYTE(wMySC), HIBYTE(wMySC));
			g_xMainWnd.PutsHan(NULL, rcStats, dwFntClr, RGB(0, 0, 0), pszBuff);
		}
		break;
	case _JOB_SULSA:	
		{
			wJobIcon = 65;	
			wImgNum	 = 124;
			sprintf(pszBuff, "%d-%d", LOBYTE(wMyMC), HIBYTE(wMyMC));
			g_xMainWnd.PutsHan(NULL, rcStats, dwFntClr, RGB(0, 0, 0), pszBuff);
		}
		break;
	case _JOB_JUNSA:	
		{
			wJobIcon = 64;
			wImgNum	 = 122;
			sprintf(pszBuff, "%d-%d", LOBYTE(wMyDC), HIBYTE(wMyDC));
			g_xMainWnd.PutsHan(NULL, rcStats, dwFntClr, RGB(0, 0, 0), pszBuff);
		}
		break;
	}
	if ( m_pxInterImg->NewSetIndex(wJobIcon) )
	{
 		g_xMainWnd.DrawWithImageForComp(m_rcMain.left+82, m_rcMain.top+71,
										m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth,
										m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight,
										(WORD*)m_pxInterImg->m_pbCurrImage);
	}
	// AC찍기.
	if ( m_pxInterImg->NewSetIndex(120) )
	{
 		g_xMainWnd.DrawWithImageForComp(m_rcMain.left+391, m_rcMain.top+136,
										m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth,
										m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight,
										(WORD*)m_pxInterImg->m_pbCurrImage);
	}
	// DC, MC, SC
	if ( m_pxInterImg->NewSetIndex(wImgNum) )
	{
 		g_xMainWnd.DrawWithImageForComp(m_rcMain.left+487, m_rcMain.top+136,
										m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth,
										m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight,
										(WORD*)m_pxInterImg->m_pbCurrImage);
	}
}


VOID CInterface::ShowMagicKey()
{
	if ( m_bShowKey )
	{
		INT nCnt;

		for ( nCnt = 0; nCnt < 12; nCnt++ )
		{
			if ( m_pxInterImg->NewSetIndex(1450+nCnt) )
			{
 				g_xMainWnd.DrawWithABlendCompDataWithBackBuffer(nCnt*m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth, 0,
																m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth,
																m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight,
																(WORD*)m_pxInterImg->m_pbCurrImage, _CLIP_WIDTH, 600);

			}
		}
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
			case _WND_ID_GUILDMASTER:
				rcWnd = m_xGuildMasterWnd.GetGameWndRect();
				break;
			case _WND_ID_GUILD:
				rcWnd = m_xGuildWnd.GetGameWndRect();
				break;
			case _WND_ID_GROUP:
				if( m_xGroupWnd.m_xSelectCharWnd.m_bActive)
					rcWnd = m_xGroupWnd.m_xSelectCharWnd.GetGameWndRect();
				else
					rcWnd = m_xGroupWnd.GetGameWndRect();
				break;
			case _WND_ID_GROUPPOP:
				rcWnd = m_xGroupPopWnd.GetGameWndRect();
				break;
			case _WND_ID_CHATPOP:
				rcWnd = m_xChatPopWnd.GetGameWndRect();
				break;
			case _WND_ID_NPCCHAT:	// 용기
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
VOID CInterface::AddWindowToList(INT nID)
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
			if ( m_xQuestWnd.GetGameWndActive() )
			{
				DeleteWindowToList(_WND_ID_QUEST);
				m_xQuestWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				AddWindowToList(_WND_ID_QUEST);
				m_xQuestWnd.SetGameWndActive(TRUE);
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

	case _WND_ID_GUILDMASTER:
		{
			if ( m_xGuildMasterWnd.GetGameWndActive() )
			{
				DeleteWindowToList(_WND_ID_GUILDMASTER);
				m_xGuildMasterWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				AddWindowToList(_WND_ID_GUILDMASTER);
				m_xGuildMasterWnd.SetGameWndActive(TRUE);
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
				bRet = TRUE;
			}
		}
		break;
	case _WND_ID_GROUPPOP:
		{
			if ( m_xGroupPopWnd.GetGameWndActive() )
			{
				DeleteWindowToList(_WND_ID_GROUPPOP);
				m_xGroupPopWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				AddWindowToList(_WND_ID_GROUPPOP);
				m_xGroupPopWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;
	case _WND_ID_CHATPOP:
		{
			if ( m_xChatPopWnd.GetGameWndActive() )
			{
				MoveWindow(g_xChatEditBox.GetSafehWnd(), g_xMainWnd.m_rcWindow.left+_INPUT_EDITWND_XPOS, 
	 					   g_xMainWnd.m_rcWindow.top+_INPUT_EDITWND_YPOS, _INPUT_EDITWND_WIDTH, _INPUT_EDITWND_HEIGHT, TRUE);

				DeleteWindowToList(_WND_ID_CHATPOP);
				m_xChatPopWnd.SetGameWndActive(FALSE);
				bRet = FALSE;
			}
			else
			{
				MoveWindow(g_xChatEditBox.GetSafehWnd(), g_xMainWnd.m_rcWindow.left + m_xChatPopWnd.m_rcWnd.left + m_xChatPopWnd.m_rcEditBoxFrame.left, 
	 					   g_xMainWnd.m_rcWindow.top + m_xChatPopWnd.m_rcWnd.top + m_xChatPopWnd.m_rcEditBoxFrame.top, 
						   m_xChatPopWnd.m_rcEditBoxFrame.right - m_xChatPopWnd.m_rcEditBoxFrame.left, 
						   m_xChatPopWnd.m_rcEditBoxFrame.bottom - m_xChatPopWnd.m_rcEditBoxFrame.top, TRUE);

				SetFocus(g_xChatEditBox.GetSafehWnd());
				AddWindowToList(_WND_ID_CHATPOP);
				m_xChatPopWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;
	case _WND_ID_NPCCHAT:		// 용기
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
//				m_xNPCWnd.SetNPCStr("하늘을 우러러 한점 부끄럼 없기를 잎세에이는 바람에도 나는 괴로워 했다 <별/@STAR>을 노래하는 마음으로 모든 죽어 가는것을 <사랑/@LOVE>해야지 그리고 또 나에게 주워 진길을 걸어 가야 겠다. 오늘 밤에도 별이 바람에 스치운다. 동해물과 백두산이 마르고 닭토록 하느님이 보우하사 우리나라 만세 무궁화 삼천리 화려강산 대한사람 대한으로 길이 보전하세. 시몬 너는 아느냐 김밥 옆구리 긁는 소리는  시몬 너는 아느냐 긁던 옆구리 터지는 소리를 너무나도 아름다운 그소리를 정넌 너는 모르는 것이냐\n <문파를 생성해볼까?/@@buildguildnow>  \n <종료/@end>",0);
				m_xNPCWnd.SetGameWndActive(TRUE);
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
				m_xStoreWnd.MoveGameWnd(ptMouse);
				break;
			case _WND_ID_EXCHANGE:
				m_xExchangeWnd.MoveGameWnd(ptMouse);
				break;
			case _WND_ID_GUILDMASTER:
				m_xGuildMasterWnd.MoveGameWnd(ptMouse);
				break;
			case _WND_ID_GUILD:
				m_xGuildWnd.MoveGameWnd(ptMouse);
				break;
			case _WND_ID_GROUP:
				m_xGroupWnd.MoveGameWnd(ptMouse);
				break;
			case _WND_ID_GROUPPOP:
				m_xGroupPopWnd.MoveGameWnd(ptMouse);
				break;
			case _WND_ID_CHATPOP:
				m_xChatPopWnd.MoveGameWnd(ptMouse);
				ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_HIDE);
				break;
			case _WND_ID_NPCCHAT:		// 용기
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
			m_xStoreWnd.SetGameWndFocused(TRUE);
			m_xStoreWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_EXCHANGE:
			m_xExchangeWnd.SetGameWndFocused(TRUE);
			m_xExchangeWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_GUILDMASTER:
			m_xGuildMasterWnd.SetGameWndFocused(TRUE);
			m_xGuildMasterWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_GUILD:
			m_xGuildWnd.SetGameWndFocused(TRUE);
			m_xGuildWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_GROUP:
			if( m_xGroupWnd.m_xSelectCharWnd.m_bActive )
			{
				m_xGroupWnd.m_xSelectCharWnd.SetGameWndFocused(TRUE);
				m_xGroupWnd.m_xSelectCharWnd.SetReadyMove(ptMouse);
			}
			else
			{
				m_xGroupWnd.SetGameWndFocused(TRUE);
				m_xGroupWnd.SetReadyMove(ptMouse);
			}
			break;
		case _WND_ID_GROUPPOP:
			m_xGroupPopWnd.SetGameWndFocused(TRUE);
			m_xGroupPopWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_CHATPOP:
			m_xChatPopWnd.SetGameWndFocused(TRUE);
			m_xChatPopWnd.SetReadyMove(ptMouse);
			break;
		case _WND_ID_NPCCHAT:		// 용기
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

		}
	}	
}


VOID CInterface::AllWindowsFocusOff()
{
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
			case _WND_ID_GUILDMASTER:
				m_xGuildMasterWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_GUILD:
				m_xGuildWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_GROUP:
				m_xGroupWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_GROUPPOP:
				m_xGroupPopWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_CHATPOP:
				m_xChatPopWnd.SetGameWndFocused(FALSE);
				break;
			case _WND_ID_NPCCHAT:		// 용기
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

			}
			m_xWndOrderList.MoveNextNode();
		}
	}
}

BOOL CInterface::IsTopWindow(INT nID)
{
	if ( m_xWndOrderList.GetCounter() != 0 )
	{
		INT* pnCurrID;
		m_xWndOrderList.MoveCurrentToTail();
		pnCurrID = m_xWndOrderList.GetCurrentData();

		if ( nID == *pnCurrID )
			return TRUE;
	}
	return FALSE;
}








///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 메시지 입력관련부분/////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
	if(m_xMsgBox.IsActive())	// 용기
	{
		m_xMsgBox.OnButtonDown(ptMouse);
		return TRUE;
	}
	else
	{
		if ( m_xScrlBar.OnLButtonDown(ptMouse) )
		{
			FLOAT	fScrlRate;

			fScrlRate = m_xScrlBar.GetScrlRate();
			m_nFstLine  = (m_xChat.GetCounter()-1)*fScrlRate;

			return TRUE;
		}

		for( INT nCnt = 0; nCnt < _MAX_INTER_BTN; nCnt++ )
		{
			if ( m_xInterBtn[nCnt].OnLButtonDown(ptMouse) )
				return TRUE;
		}

		//BeltWnd
		if( PtInRect(&m_xInventoryWnd.m_rcBeltWnd, ptMouse))
		{
			m_xInventoryWnd.OnLButtonDown(&m_stCommonItem, ptMouse);
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
			case _WND_ID_GUILDMASTER:
				if ( !m_xGuildMasterWnd.OnLButtonDown(ptMouse) )
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
			case _WND_ID_GROUPPOP:
				if ( !m_xGroupPopWnd.OnLButtonDown(ptMouse) )
					WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
				break;
			case _WND_ID_CHATPOP:
				if ( !m_xChatPopWnd.OnLButtonDown(ptMouse) )
					WindowFocusChangedAndSetReadyMove(nInterfaceWndInRect, ptMouse);
				break;
			case _WND_ID_NPCCHAT:	// 용기
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

			}
			return TRUE;
		}
		else
			AllWindowsFocusOff();
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

	if ( m_xMsgBox.IsActive() )	// 용기
	{
		HRESULT hResult;
		hResult = m_xMsgBox.OnButtonUp(ptMouse);
		if ( hResult != 0 )
		{
			switch ( m_nIdxMsgBox )
			{
			case 12:
				{
					switch ( hResult )	// 에디트 박스가 없음.
					{
					case 2:
						{
						   DWORD dwCurrTick = timeGetTime();
						   if ( (dwCurrTick - g_xGameProc.m_pMyHero->m_dwLastPKStruckTime> 10000) &&
								(dwCurrTick - g_xGameProc.m_pMyHero->m_dwLastMagicTime   > 10000) &&
								(dwCurrTick - g_xGameProc.m_pMyHero->m_dwLastHitTime		> 10000) || 
								(g_xGameProc.m_pMyHero->m_bCurrMtn					== _MT_DIE ) )
								SendMessage(g_xMainWnd.GetSafehWnd(), WM_DESTROY, NULL, NULL);
						   else
						   {
							   DWORD dwFont, dwBack;

							   dwFont = GetChatColor(3);
							   dwBack = GetChatColor(2);

							   MsgAdd(dwFont, dwBack, "珂쇌꼇돕,꼇횻浬?");
						   }
						}
						break;
					case 4:
						m_xMsgBox.HideMessageBox();
						break;
					}
				}
				break;
			}
		}
	}
	else
	{
		if ( m_xScrlBar.OnLButtonUp(ptMouse) )
		{
			return TRUE;
		}

		//BeltWnd
		if( PtInRect(&m_xInventoryWnd.m_rcBeltWnd, ptMouse))
		{
			m_xInventoryWnd.OnLButtonUp(&m_stCommonItem, ptMouse);
			return TRUE;
		}

		for( INT nCnt = 0; nCnt < _MAX_INTER_BTN; nCnt++ )
		{
			if ( m_xInterBtn[nCnt].OnLButtonUp(ptMouse) )
			{
				switch ( nCnt )
				{
				case _BTN_ID_QUEST:		WindowActivate(_WND_ID_QUEST);					break;
				case _BTN_ID_OPTION:	WindowActivate(_WND_ID_OPTION);					break;
				case _BTN_ID_HORSE:		WindowActivate(_WND_ID_HORSE);					break;

				case _BTN_ID_CHANGE:	WindowActivate(_WND_ID_EXCHANGE);				break;
				case _BTN_ID_GUILD:		
					g_xGameProc.m_pSocket->SendGuildHome();
					break;
				case _BTN_ID_GROUP:		WindowActivate(_WND_ID_GROUP);					break;
				case _BTN_ID_POPUP:		WindowActivate(_WND_ID_CHATPOP);				break;
				case _BTN_ID_BAG:		WindowActivate(_WND_ID_INVENTORY);				break;
				case _BTN_ID_MUGONG:	m_bShowKey = !m_bShowKey;						break;
				case _BTN_ID_BELT:
					{
						if ( m_shBeltHeight >= 46 )	
						{
							m_shBeltHeight = 46;
						}
						else if ( m_shBeltHeight <= 0 )		
						{
							m_shBeltHeight = 0;
						}

						if ( m_shBeltHeight == 46 )
						{
							m_bBeltState = _BELT_STATE_DOWN;
						}
						else if ( m_shBeltHeight == 0 )
						{
							m_bBeltState = _BELT_STATE_UP;
						}
					}
					break;
				case _BTN_ID_EXIT:
					{
						CHAR	  szMsg[MAX_PATH];
						m_nIdxMsgBox = 12;

						strcpy( szMsg, "콱拳狼藁놔넋埼찐?" );
						m_xMsgBox.ShowMessageBox(szMsg, 2);					// YES/No ?
					}
					break;
				case _BTN_ID_MAGIC:
					if ( m_xStatusWnd.GetStatusWndType() != _TYPE_SETMAGIC )
					{
						if ( !WindowActivate(_WND_ID_STATUS) )		WindowActivate(_WND_ID_STATUS);
					}
					else
						WindowActivate(_WND_ID_STATUS);
					m_xStatusWnd.SetStatusWndType(_TYPE_SETMAGIC);
					break;
				case _BTN_ID_CHAR:
//					if ( m_xStatusWnd.GetStatusWndType() != _TYPE_EQUIP )
//					{
//						if ( !WindowActivate(_WND_ID_STATUS) )		WindowActivate(_WND_ID_STATUS);
//					}
//					else
//						WindowActivate(_WND_ID_STATUS);
//					m_xStatusWnd.SetStatusWndType(_TYPE_EQUIP);
//					m_xStatusWnd.SetStatusWndType(_WND_ID_STATUS);

					m_xStatusWnd.SetStatusWndType(_TYPE_STATUS);
					WindowActivate(_WND_ID_STATUS);
					break;
				case _BTN_ID_MINIMAP:	WindowActivate(_BTN_ID_MINIMAP);				break;
				case _BTN_ID_LOGOUT:
					{
						//TEST路劤되쩍
						g_xGameProc.ReLoad();
					}
				}
			}
		}

		INT nInterfaceWndInRect;
		nInterfaceWndInRect = GetWindowInMousePos(ptMouse);

		// 각 윈도우의 OnLButtonUp의 리턴값이 TRUE이면 윈도우즈는 Close된다.
		if ( nInterfaceWndInRect != -1 )
		{
			switch ( nInterfaceWndInRect )
			{
			case _WND_ID_INVENTORY:		if ( m_xInventoryWnd.OnLButtonUp(&m_stCommonItem, ptMouse) )	WindowActivate(_WND_ID_INVENTORY);		break;
			case _WND_ID_STATUS:		if ( m_xStatusWnd.OnLButtonUp(&m_stCommonItem, ptMouse) )		WindowActivate(_WND_ID_STATUS);			break;
			case _WND_ID_STORE:			if ( m_xStoreWnd.OnLButtonUp(ptMouse) )							WindowActivate(_WND_ID_STORE);			break;
			case _WND_ID_EXCHANGE:		if ( m_xExchangeWnd.OnLButtonUp(ptMouse) )						WindowActivate(_WND_ID_EXCHANGE);		break;
			case _WND_ID_GUILDMASTER:
			{
				if ( m_xGuildMasterWnd.OnLButtonUp(ptMouse) )
					WindowActivate(_WND_ID_EXCHANGE);
				break;
			}
			case _WND_ID_GUILD:			if ( m_xGuildWnd.OnLButtonUp(ptMouse) )							WindowActivate(_WND_ID_GUILD);			break;
			case _WND_ID_GROUP:			if ( m_xGroupWnd.OnLButtonUp(ptMouse) )							WindowActivate(_WND_ID_GROUP);			break;
			case _WND_ID_GROUPPOP:		if ( m_xGroupPopWnd.OnLButtonUp(ptMouse) )						WindowActivate(_WND_ID_GROUPPOP);		break;
			case _WND_ID_CHATPOP:		if ( m_xChatPopWnd.OnLButtonUp(ptMouse) )						WindowActivate(_WND_ID_CHATPOP);		break;

			case _WND_ID_QUEST:			if ( m_xQuestWnd.OnLButtonUp(ptMouse) )							WindowActivate(_WND_ID_QUEST);			break;
			case _WND_ID_OPTION:		if ( m_xOptionWnd.OnLButtonUp(ptMouse) )						WindowActivate(_WND_ID_OPTION);			break;
			case _WND_ID_HORSE:			if ( m_xHorseWnd.OnLButtonUp(ptMouse) )							WindowActivate(_WND_ID_HORSE);			break;

			case _WND_ID_NPCCHAT:		if ( m_xNPCWnd.OnLButtonUp(ptMouse) )							WindowActivate(_WND_ID_NPCCHAT);		break; // 용기
			}
			return TRUE;
		}
	}
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
	MoveTopWindow(ptMouse);

	if ( m_xScrlBar.OnMouseMove(ptMouse) )
	{
		FLOAT	fScrlRate;

		fScrlRate = m_xScrlBar.GetScrlRate();
		m_nFstLine  = (m_xChat.GetCounter()-1)*fScrlRate;
		return TRUE;
	}

	for( INT nCnt = 0; nCnt < _MAX_INTER_BTN; nCnt++ )
		m_xInterBtn[nCnt].OnMouseMove(ptMouse);

	INT nInterfaceWndInRect;
	nInterfaceWndInRect = GetWindowInMousePos(ptMouse);

	if ( nInterfaceWndInRect != -1 )
	{
		switch ( nInterfaceWndInRect )
		{
		case _WND_ID_INVENTORY:
			m_xInventoryWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_STATUS:
			m_xStatusWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_STORE:
			m_xStoreWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_EXCHANGE:
			m_xExchangeWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_GUILDMASTER:
			m_xGuildMasterWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_GUILD:
			m_xGuildWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_GROUP:
			m_xGroupWnd.OnMouseMove(ptMouse);
			break;
		case _WND_ID_GROUPPOP:
			m_xGroupPopWnd.OnMouseMove(ptMouse);
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

		case _WND_ID_NPCCHAT:		// 용기
			m_xNPCWnd.OnMouseMove(ptMouse);
			break;
		}
		return TRUE;
	}
	else
	{
		m_xStatusWnd.SetStatusBtnInit();
		m_xInventoryWnd.SetInvenBtnInit();
		m_xChatPopWnd.SetStatusBtnInit();
		m_xGuildMasterWnd.SetStatusBtnInit();
		m_xOptionWnd.SetStatusBtnInit();
		m_xQuestWnd.SetStatusBtnInit();
		m_xHorseWnd.SetStatusBtnInit();
		m_xExchangeWnd.SetStatusBtnInit();
	}

	return FALSE;
}


BOOL CInterface::OnScrollDown()
{
	if ( IsTopWindow(m_xInventoryWnd.m_nID) )
	{
		m_xInventoryWnd.OnScrollDown();
	}
	else if ( IsTopWindow(m_xStatusWnd.m_nID) )
	{
		m_xStatusWnd.OnScrollDown();
	}
	else if (IsTopWindow(m_xNPCWnd.m_nID))		// 용기
	{
		m_xNPCWnd.OnScrollDown();
	}
	else if(IsTopWindow(m_xStoreWnd.m_nID))
	{
		m_xStoreWnd.OnScrollDown();
	}
	else
	{
		if ( !m_xChatPopWnd.m_bActive )
		{
			if ( m_nFstLine > 0 )	
			{
				m_nFstLine--;
			}
		}
		else
		{
			m_xChatPopWnd.OnScrollDown();
		}
	}
	return TRUE;
}


BOOL CInterface::OnScrollUp()
{
	if ( IsTopWindow(m_xInventoryWnd.m_nID) )
	{
		m_xInventoryWnd.OnScrollUp();
	}
	else if ( IsTopWindow(m_xStatusWnd.m_nID) )
	{
		m_xStatusWnd.OnScrollUp();
	}
	else if (IsTopWindow(m_xNPCWnd.m_nID))		// 용기
	{
		m_xNPCWnd.OnScrollUp();
	}
	else if(IsTopWindow(m_xStoreWnd.m_nID))
	{
		m_xStoreWnd.OnScrollUp();
	}
	else
	{
		if ( !m_xChatPopWnd.m_bActive )
		{
			if ( m_nFstLine < (m_xChat.GetCounter()-1) )
			{
				m_nFstLine++;
			}
		}
		else
		{
			m_xChatPopWnd.OnScrollUp();
		}
	}
	return TRUE;
}

BOOL CInterface::OnLButtonDoubleClick(POINT ptMouse)
{
	if ( IsTopWindow(m_xInventoryWnd.m_nID) )
		m_xInventoryWnd.OnLButtonDoubleClick(&m_stCommonItem, ptMouse);
	return TRUE;
}


BOOL CInterface::OnKeyUp(WPARAM wParam, LPARAM lParam)
{
	if ( m_xInventoryWnd.OnKeyUp(&m_stCommonItem, wParam, lParam) )
	{
		return TRUE;
	}
	return FALSE;
}


BOOL CInterface::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	switch ( wParam )
	{
	case VK_RETURN:	
		break;
	case VK_F9:	
		WindowActivate(_WND_ID_INVENTORY);			
		break;
	case VK_F11:
		if ( m_xStatusWnd.GetStatusWndType() != _TYPE_SETMAGIC )
		{
			if ( !WindowActivate(_WND_ID_STATUS) )
				WindowActivate(_WND_ID_STATUS);
		}
		else
			WindowActivate(_WND_ID_STATUS);

		m_xStatusWnd.SetStatusWndType(_TYPE_SETMAGIC);
		break;
	}

	INT nInterfaceWndInRect;
	nInterfaceWndInRect = GetWindowInMousePos(g_xGameProc.m_ptMousePos);

	if ( nInterfaceWndInRect != -1 )
	{
		if ( nInterfaceWndInRect == _WND_ID_STATUS )
		{
			if ( m_xStatusWnd.OnKeyDown(wParam, lParam, g_xGameProc.m_ptMousePos) )
				return TRUE;
		}
	}
		
	return FALSE;
}


VOID CInterface::OnSysKeyDown()
{
	// F10 Key 눌렸을때.
	if ( m_xStatusWnd.GetStatusWndType() != _TYPE_EQUIP )
	{
		if ( !WindowActivate(_WND_ID_STATUS) )
			WindowActivate(_WND_ID_STATUS);
	}
	else
		WindowActivate(_WND_ID_STATUS);

	m_xStatusWnd.SetStatusWndType(_TYPE_EQUIP);
}


LRESULT	CInterface::OnMsgInputted(WPARAM wParam, LPARAM lParam)
{
	if ( m_xNPCWnd.OnMsgInputted() )
		return TRUE;

	return 0L;
}
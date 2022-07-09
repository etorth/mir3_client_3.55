/******************************************************************************************************************
                                                                                                                   
	¸ðµâ¸í:																											
																													
	ÀÛ¼ºÀÚ:																											
	ÀÛ¼ºÀÏ:																											
																													
	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤ ³»¿ë																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"

#define BELT_POS_X	0
#define BELT_POS_Y	457
#define BELT_WND_WIDTH	512
#define BELT_WND_HEIGHT 48

/******************************************************************************************************************

	ÇÔ¼ö¸í : CInterface::CInterface()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : 
	Ãâ·Â   : 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
CInterface::CInterface()
{
	Init();
}



/******************************************************************************************************************

	ÇÔ¼ö¸í : CInterface::~CInterface()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : 
	Ãâ·Â   : 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
CInterface::~CInterface()
{
	Destroy();
}



/******************************************************************************************************************

	ÇÔ¼ö¸í : CInterface::Init()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : ÀÎÅÍÆäÀÌ½º°ü·Ã º¯¼ö¹×, °´Ã¼ÃÊ±âÈ­.
	Ãâ·Â   : VOID 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

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

	ÇÔ¼ö¸í : CInterface::Destroy()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : ÀÎÅÍÆäÀÌ½º°ü·Ã º¯¼ö, °´Ã¼ÀÇ ¼Ò¸ê¹×, ÃÊ±âÈ­.
	Ãâ·Â   : VOID 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

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
	// Ã¤ÆÃ¿¡µðÆ® À©µµ¿ì À§Ä¡ÁöÁ¤.
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
	// ÁÄÌìÇøÓò.
	SetRect(&m_rcChat, 188, 490, 532, 560);

	//------------------------------------------------------------------------------------------------------------

	//------------------------------------------------------------------------------------------------------------
	// °ü¹ü.
	m_xInventoryWnd.CreateInventoryWnd(_WND_ID_INVENTORY, m_pxInterImg, _WNDIMGIDX_INVENTORY, 0, 0, 280, 464, TRUE);
	//×´Ì¬
	m_xStatusWnd.CreateStatusWnd(_WND_ID_STATUS, m_pxInterImg, _WNDIMGIDX_ITEMSET, 510, 0, 330, 468, TRUE);
	//´æ´¢
	m_xStoreWnd.CreateStoreWnd(_WND_ID_STORE, m_pxInterImg, _WNDIMGIDX_STORE, 0, 0, 290, 224, TRUE);
	//½»Ò×
	m_xExchangeWnd.CreateExchangeWnd(_WND_ID_EXCHANGE, m_pxInterImg, _WNDIMGIDX_EXCHANGE, 0, 0, 0, 0, TRUE);
	//ÐÐ»á
	m_xGuildMasterWnd.CreateGuildMasterWnd(_WND_ID_GUILDMASTER, m_pxInterImg, _WNDIMGIDX_GUILDMASTER, 0, 0, 0, 0, TRUE);
//	m_xGuildWnd.CreateGuildWnd(_WND_ID_GUILD, &m_xInterImgEx, _WNDIMGIDX_GUILD, 0, 0, 540, 442, TRUE);

	//×é
	m_xGroupWnd.CreateGroupWnd(_WND_ID_GROUP, m_pxInterImg, _WNDIMGIDX_GROUP, 0, 0, 260, 245, TRUE);
	//YDQ	m_xGroupPopWnd.CreateGroupPopWnd(_WND_ID_GROUPPOP, &m_xInterImgEx, _WNDIMGIDX_GROUPPOP, 0, 0, 260, 114, TRUE);
	//ÁÄÌì
	m_xChatPopWnd.CreateChatPopWnd(_WND_ID_CHATPOP, m_pxInterImg, _WNDIMGIDX_CHATPOP, 0, 0, 0, 0, TRUE);

	//²Ù×÷
	m_xOptionWnd.CreateOptionWnd(_WND_ID_OPTION, m_pxInterImg, _WNDIMGIDX_OPTION, 0, 0, 0, 0, TRUE);
	
	m_xQuestWnd.CreateQuestWnd(_WND_ID_QUEST, m_pxInterImg, _WNDIMGIDX_QUEST, 0, 0, 0, 0, TRUE);
	//Âí
	m_xHorseWnd.CreateHorseWnd(_WND_ID_HORSE, m_pxInterImg, _WNDIMGIDX_HORSE, 0, 0, 0, 0, TRUE);

	//NPC
	m_xNPCWnd.CreateNPCChatWnd(_WND_ID_NPCCHAT, m_pxInterImg, _WNDIMGIDX_NPCCHAT, 0, 0, 388, 204, TRUE);				// ¿ë±â

	// ³õÊ¼»¯°´Å¥
	m_xInterBtn[ _BTN_ID_CHANGE	].CreateGameBtn(m_pxInterImg, 1170, 1170, m_rcMain.left+638, m_rcMain.top+7);//½»Ò×
	m_xInterBtn[ _BTN_ID_MINIMAP].CreateGameBtn(m_pxInterImg, 1172, 1172, m_rcMain.left+638, m_rcMain.top+41);//Ð¡µØÍ¼
	m_xInterBtn[ _BTN_ID_MUGONG	].CreateGameBtn(m_pxInterImg, 1174, 1174, m_rcMain.left+638, m_rcMain.top+76);//Unknown

	m_xInterBtn[ _BTN_ID_EXIT	].CreateGameBtn(m_pxInterImg, 1176, 1176, m_rcMain.left+8, m_rcMain.top+72);//ÍË³ö°´Å¥
	m_xInterBtn[ _BTN_ID_LOGOUT	].CreateGameBtn(m_pxInterImg, 1178, 1178, m_rcMain.left+109, m_rcMain.top+72);//logout
	m_xInterBtn[ _BTN_ID_GROUP	].CreateGameBtn(m_pxInterImg, 1180, 1181, m_rcMain.left+706, m_rcMain.top+8);	// ×é
	m_xInterBtn[ _BTN_ID_GUILD	].CreateGameBtn(m_pxInterImg, 1182, 1183, m_rcMain.left+674, m_rcMain.top+11);	// ÐÐ»á

	m_xInterBtn[ _BTN_ID_BELT	].CreateGameBtn(m_pxInterImg, 1205, 1205, m_rcMain.left+148, m_rcMain.top+2);	// BELT ¿ì½ÝÀ¸

	m_xInterBtn[ _BTN_ID_MAGIC	].CreateGameBtn(m_pxInterImg,1184, 1184, m_rcMain.left+739, m_rcMain.top+33);	// Ä§·¨
	m_xInterBtn[ _BTN_ID_POPUP	].CreateGameBtn(m_pxInterImg,1168, 1168, m_rcMain.left+619, m_rcMain.top+6);	// ÁÄÌìÀ¸µ¯³ö
	m_xInterBtn[ _BTN_ID_QUEST	].CreateGameBtn(m_pxInterImg,1186, 1187, m_rcMain.left+742, m_rcMain.top+11);	// ÈÎÎñ.
	m_xInterBtn[ _BTN_ID_OPTION	].CreateGameBtn(m_pxInterImg,1188, 1189, m_rcMain.left+706, m_rcMain.top+72);	// ÉèÖÃ
	m_xInterBtn[ _BTN_ID_HELP	].CreateGameBtn(m_pxInterImg,1190, 1191, m_rcMain.left+742, m_rcMain.top+61);	// help
	m_xInterBtn[ _BTN_ID_HORSE	].CreateGameBtn(m_pxInterImg,1192, 1193, m_rcMain.left+674, m_rcMain.top+61);	// horse
	m_xInterBtn[ _BTN_ID_BAG	].CreateGameBtn(m_pxInterImg,1194, 1195, m_rcMain.left+682, m_rcMain.top+33);	// .
	m_xInterBtn[ _BTN_ID_CHAR	].CreateGameBtn(m_pxInterImg,1196, 1197, m_rcMain.left+711, m_rcMain.top+31);	// ½ÇÉ«°´Å¥

	//¹ö¶¯Ìõ
	m_xScrlBar.CreateScrlBar(m_pxInterImg, 1207, _MAX_CHATLINE, 12, 56, 12);

	m_xMsgBox.Load(m_pxInterImg);	// ¿ë±â
}



/******************************************************************************************************************

	ÇÔ¼ö¸í : CInterface::MsgAdd()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : 
	ÀÔ·Â   : DWORD dwFontColor
	         DWORD dwFontBackColor
	         CHAR* pszMsg
	Ãâ·Â   : VOID 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

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

			// ¹®ÀÚ¿­ »ðÀÔ.
			for ( nCnt = 0; nCnt < nLineCnt; nCnt++ )
			{
				// Ä­ÀÌ ´ÙÀ½À¸·Î °¥Á¶°Ç.
				if ( m_xChat.GetCounter() - m_nFstLine == _MAX_CHATLINE )
				{
					m_nFstLine++;
				}

				stChat.dwFontColor = dwFontColor;
				stChat.dwBackColor = dwFontBackColor;
				strcpy(stChat.pszChat, pszArg[nCnt]);

				m_xChat.AddNode(stChat);
			}

			// ÃÖ´ëÀúÀå¶óÀÎ °Ë»çÇØ¼­ ±×ÀÌ»óÀÌ¸é »èÁ¦ÇÑ´Ù.
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

	ÇÔ¼ö¸í : CInterface::ShowWndList()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : ActiveµÇ¾îÀÖ´Â À©µµ¿ìÀÇ ¸®½ºÆ®¸¦ º¸¿©ÁØ´Ù.
	Ãâ·Â   : VOID 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

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
			case _WND_ID_NPCCHAT:					// ¿ë±â
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

	ÇÔ¼ö¸í : CInterface::ShowChatList()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : Ã¤ÆÃ ¸®½ºÆ®¸¦ º¸¿©ÁØ´Ù.
	Ãâ·Â   : VOID 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

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

	ÇÔ¼ö¸í : CInterface::RenderInterface()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : 
	ÀÔ·Â   : INT nLoopTime
	         POINT ptMousePos
	Ãâ·Â   : VOID 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
VOID CInterface::RenderInterface(INT nLoopTime, POINT ptMousePos)
{
	INT nX, nY, nCnt;

	ShowBeltItem();

	ShowWndList();

	//Êó±êÏÂµÄÎïÆ·
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
	//ydqÔÝÊ±Ìí¼ÓµÄ
	if ( m_pxInterImg->NewSetIndex(_WNDIMGIDX_CHATPOP-1) )
	{
		g_xMainWnd.DrawWithImageForCompClipRgn(m_rcMain.left+178, m_rcMain.top-18,
			m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth, m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight,
			(WORD*)m_pxInterImg->m_pbCurrImage, _CLIP_WIDTH, 600);
	}

	//ÁÄÌìÐÅÏ¢
	ShowChatList();
	ShowGameStatus();


	for ( nCnt = 0; nCnt < _MAX_INTER_BTN; nCnt++)
	{
		m_xInterBtn[nCnt].ShowGameBtn();
	}

	// ½ºÅ©·Ñ¹Ù.
	m_xScrlBar.ShowScrlBar(m_rcMain.left+620, m_rcMain.top+40, m_nFstLine, m_xChat.GetCounter());

	// Å¬¶óÀÌ¾ðÆ®¸Þ½ÃÁö(¿ÞÂÊ»ó´Ü).
	m_xClientSysMsg.ShowSysMsg(nLoopTime, 30, 30);

	// ¿ë±â
	m_xMsgBox.RenderMessageBox(0);

	ShowMagicKey();

}



/******************************************************************************************************************

	ÇÔ¼ö¸í : CInterface::ShowBeltItem()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : 
	Ãâ·Â   : VOID 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

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

			// º§Æ® ¾ÆÀÌÅÛ ±×¸®±â.
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

	ÇÔ¼ö¸í : CInterface::ShowGameStatus()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : 
	Ãâ·Â   : BOOL 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

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
	
	// ÇÏ·çÀÇ »óÅÂÄ¡(¹ã, ³·, Àú³á, »õº®)
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

	// HP, MPÂï±â.
	// ºñÀ²°Ë»ç.
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
	// ·¹º§Âï6±â.
	//ÐèÒªËæÁÄÌìÀ¸±ä»¯¶ø¸Ä±ä
	sprintf(pszBuff, "%d", g_xGameProc.m_pMyHero->m_stAbility.bLevel);
	SetRect(&rcStats, m_rcMain.left+394, m_rcMain.top+2, m_rcMain.left+408, m_rcMain.top+16);
	g_xMainWnd.PutsHan(NULL, rcStats, dwFntClr, RGB(0, 0, 0), pszBuff, g_xMainWnd.CreateGameFont("±Ã¼­Ã¼", 10, 0, FW_BOLD));

	dwFntClr = RGB(255, 255, 200);
	sprintf(pszBuff, "%s : [%d,%d]", g_xGameProc.m_szMapName, g_xGameProc.m_pMyHero->m_wPosX, g_xGameProc.m_pMyHero->m_wPosY);
	SetRect(&rcStats, 9, 579, 139, 592);
	g_xMainWnd.PutsHan(NULL, rcStats, dwFntClr, RGB(0, 0, 0), pszBuff);

	//FIXME ²»Ã÷°×Ê²Ã´ÒâË¼
	dwFntClr = RGB(255, 200, 50);
	// Á÷¾÷º° ¾ÆÀÌÄÜ¹× Æ¯¼ºÄ¡ Âï±â.
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
	// ACÂï±â.
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
// À©µµ¿ì °ü¸®ºÎºÐ/////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************

	ÇÔ¼ö¸í : CInterface::GetWindowInMousePos()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : ¸¶¿ì½º Æ÷ÀÎÅÍ¸¦ ¿µ¿ª¾È¿¡ °¡Áö°í ÀÖ´Â À©µµ¿ì¸®½ºÆ®Áß ¸ÇÃ³À½ À©µµ¿ìÀÇ ID¸¦ ¸®ÅÏÇÑ´Ù.
	ÀÔ·Â   : POINT ptMouse
	Ãâ·Â   : 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

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
			case _WND_ID_NPCCHAT:	// ¿ë±â
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

	ÇÔ¼ö¸í : CInterface::AddWindowToList()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : À©µµ¿ì¸®½ºÆ®ÀÇ ¸Ç ¸¶Áö¸·¿¡ ÇöÀç ÀÔ·Â¹ÞÀº ¾ÆÀÌµð°¡ nIDÀÎ À©µµ¿ì¸¦ Ãß°¡ÇÑ´Ù.
	ÀÔ·Â   : INT nID
	Ãâ·Â   : VOID 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
VOID CInterface::AddWindowToList(INT nID)
{
	m_xWndOrderList.AddNode(nID);
}


/******************************************************************************************************************

	ÇÔ¼ö¸í : CInterface::DeleteWindowToList()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : nIDÀÇ ¾ÆÀÌµð¸¦ °¡Áø À©µµ¿ì¸¦ ¸®½ºÆ®»ó¿¡¼­ »èÁ¦ÇÑ´Ù.
	ÀÔ·Â   : INT nID
	Ãâ·Â   : VOID 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

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

	ÇÔ¼ö¸í : CInterface::WindowActivate()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : nIDÀÎ À©µµ¿ì¸¦ À©µµ¿ì¸®½ºÆ®¿¡ Ãß°¡½ÃÅ°°Å³ª »èÁ¦½ÃÅ°¸ç, Ãß°¡ÀÇ °æ¿ì, À©µµ¿ìÀÇ »óÅÂ¸¦ ÃÖ»óÀ§ »óÅÂ·Î ¼¼ÆÃÇÑ´Ù.
			 À©µµ¿ì°¡ Å°ÀÔ·ÂÀ» ¹Þ¾Æ¼­ È­¸é¿¡ ³ª¿Ã¶§ È£ÃâÇÏ´Â ÇÔ¼öÀÌ´Ù.
	ÀÔ·Â   : INT nID
	Ãâ·Â   : VOID 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
BOOL CInterface::WindowActivate(INT nID)
{
	// »õ·Î¿î À©µµ¿ì¿¡ Æ÷Ä¿½º¸¦ ÁÖ±âÀ§ÇØ¼­ ¸ðµç À©µµ¿ìÀÇ Æ÷Ä¿½º¸¦ FALSE½ÃÄÑÁØ´Ù.
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
	case _WND_ID_NPCCHAT:		// ¿ë±â
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
				// ÀÓ½Ã
				AddWindowToList(_WND_ID_NPCCHAT);
//				m_xNPCWnd.SetNPCStr("ÇÏ´ÃÀ» ¿ì·¯·¯ ÇÑÁ¡ ºÎ²ô·³ ¾ø±â¸¦ ÀÙ¼¼¿¡ÀÌ´Â ¹Ù¶÷¿¡µµ ³ª´Â ±«·Î¿ö Çß´Ù <º°/@STAR>À» ³ë·¡ÇÏ´Â ¸¶À½À¸·Î ¸ðµç Á×¾î °¡´Â°ÍÀ» <»ç¶û/@LOVE>ÇØ¾ßÁö ±×¸®°í ¶Ç ³ª¿¡°Ô ÁÖ¿ö Áø±æÀ» °É¾î °¡¾ß °Ú´Ù. ¿À´Ã ¹ã¿¡µµ º°ÀÌ ¹Ù¶÷¿¡ ½ºÄ¡¿î´Ù. µ¿ÇØ¹°°ú ¹éµÎ»êÀÌ ¸¶¸£°í ´ßÅä·Ï ÇÏ´À´ÔÀÌ º¸¿ìÇÏ»ç ¿ì¸®³ª¶ó ¸¸¼¼ ¹«±ÃÈ­ »ïÃµ¸® È­·Á°­»ê ´ëÇÑ»ç¶÷ ´ëÇÑÀ¸·Î ±æÀÌ º¸ÀüÇÏ¼¼. ½Ã¸ó ³Ê´Â ¾Æ´À³Ä ±è¹ä ¿·±¸¸® ±Ü´Â ¼Ò¸®´Â  ½Ã¸ó ³Ê´Â ¾Æ´À³Ä ±Ü´ø ¿·±¸¸® ÅÍÁö´Â ¼Ò¸®¸¦ ³Ê¹«³ªµµ ¾Æ¸§´Ù¿î ±×¼Ò¸®¸¦ Á¤³Í ³Ê´Â ¸ð¸£´Â °ÍÀÌ³Ä\n <¹®ÆÄ¸¦ »ý¼ºÇØº¼±î?/@@buildguildnow>  \n <Á¾·á/@end>",0);
				m_xNPCWnd.SetGameWndActive(TRUE);
				bRet = TRUE;
			}
		}
		break;
	}

	return bRet;
}


/******************************************************************************************************************

	ÇÔ¼ö¸í : CInterface::MoveTopWindow()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : ¸ÇÀ§ÀÇ À©µµ¿ì¸¦ ¸¶¿ì½º ÁÂÇ¥·Î ÀÌµ¿½ÃÅ²´Ù.
	ÀÔ·Â   : POINT ptMouse
	Ãâ·Â   : VOID 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

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
			case _WND_ID_NPCCHAT:		// ¿ë±â
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

	ÇÔ¼ö¸í : CInterface::WindowFocusChanged()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : À©µµ¿ì ¿µ¿ªÀ¸·Î ¸¶¿ì½º Å¬¸¯ÀÌ µÇ¸é ÇöÀç Top À©µµ¿ì¸¦ ¸¶¿ì½º Å¬¸¯ À©µµ¿ì·Î ¹Ù²ãÁÖ°í ±×À©µµ¿ì·Î Æ÷Ä¿½º¸¦ ¸ÂÃçÁØ´Ù.
	ÀÔ·Â   : INT nID
	Ãâ·Â   : VOID 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
VOID CInterface::WindowFocusChangedAndSetReadyMove(INT nID, POINT ptMouse)
{
	if ( m_xWndOrderList.GetCounter() != 0 )
	{
		AllWindowsFocusOff();

		DeleteWindowToList(nID);
		AddWindowToList(nID);
		// ¸¶¿ì½º Å¬¸¯ÀÌ µÈ»óÅÂÀÌ¸é ÀÌµ¿½ÃÅ³ ÁØºñ°¡ µÈ»óÅÂÀÌ´Ù.
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
		case _WND_ID_NPCCHAT:		// ¿ë±â
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
			case _WND_ID_NPCCHAT:		// ¿ë±â
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
// ¸Þ½ÃÁö ÀÔ·Â°ü·ÃºÎºÐ/////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************

	ÇÔ¼ö¸í : CInterface::OnLButtonDown()

 	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : Mouse LButtonDownÀÌ ÀÏ¾î³µÀ»¶§ ÀÎÅÍÆäÀÌ½º¿¡¼­ ÇÒÀÏÀ» Á¤ÀÇÇÑ´Ù.
	ÀÔ·Â   : POINT ptMouse
	Ãâ·Â   : BOOL 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
BOOL CInterface::OnLButtonDown(POINT ptMouse)
{
	if(m_xMsgBox.IsActive())	// ¿ë±â
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
			case _WND_ID_NPCCHAT:	// ¿ë±â
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

	ÇÔ¼ö¸í : CInterface::OnLButtonUp()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : Mouse LButtonUpÀÌ ÀÏ¾î³µÀ»¶§ ÀÎÅÍÆäÀÌ½º¿¡¼­ ÇÒÀÏÀ» Á¤ÀÇÇÑ´Ù.
	ÀÔ·Â   : POINT ptMouse
	Ãâ·Â   : BOOL 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
BOOL CInterface::OnLButtonUp(POINT ptMouse)
{
	m_bMoveFocusedWnd = FALSE;

	if ( m_xMsgBox.IsActive() )	// ¿ë±â
	{
		HRESULT hResult;
		hResult = m_xMsgBox.OnButtonUp(ptMouse);
		if ( hResult != 0 )
		{
			switch ( m_nIdxMsgBox )
			{
			case 12:
				{
					switch ( hResult )	// ¿¡µðÆ® ¹Ú½º°¡ ¾øÀ½.
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

							   MsgAdd(dwFont, dwBack, "Ê±¼ä²»µ½,²»ÈÃ×ß?");
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

						strcpy( szMsg, "ÄãÏëÒªÍË³ö³ÌÐòÂð?" );
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
						//TESTÖØÐÂµÇÂ½
						g_xGameProc.ReLoad();
					}
				}
			}
		}

		INT nInterfaceWndInRect;
		nInterfaceWndInRect = GetWindowInMousePos(ptMouse);

		// °¢ À©µµ¿ìÀÇ OnLButtonUpÀÇ ¸®ÅÏ°ªÀÌ TRUEÀÌ¸é À©µµ¿ìÁî´Â CloseµÈ´Ù.
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

			case _WND_ID_NPCCHAT:		if ( m_xNPCWnd.OnLButtonUp(ptMouse) )							WindowActivate(_WND_ID_NPCCHAT);		break; // ¿ë±â
			}
			return TRUE;
		}
	}
	return FALSE;
}


/******************************************************************************************************************

	ÇÔ¼ö¸í : CInterface::OnMouseMove()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : Mouse Move°¡ ÀÏ¾î³µÀ»¶§ ÀÎÅÍÆäÀÌ½º¿¡¼­ ÇÒÀÏÀ» Á¤ÀÇÇÑ´Ù.
	ÀÔ·Â   : POINT ptMouse
	Ãâ·Â   : BOOL 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

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

		case _WND_ID_NPCCHAT:		// ¿ë±â
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
	else if (IsTopWindow(m_xNPCWnd.m_nID))		// ¿ë±â
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
	else if (IsTopWindow(m_xNPCWnd.m_nID))		// ¿ë±â
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
	// F10 Key ´­·ÈÀ»¶§.
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
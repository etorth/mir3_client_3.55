/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/

#include "StdAfx.h"

#define GUILDWND_TEXT_STARTX		35
#define GUILDWND_TEXT_STARTY		60
#define GUILDWND_MAX_SHOWLINE		18


CGuildWnd::CGuildWnd()
{
	Init();
}

CGuildWnd::~CGuildWnd()
{
	Destroy();
}

VOID CGuildWnd::Init()
{
	CGameWnd::Init();

	m_nStartLine = 0;
	m_bIsGM		 = FALSE;
	m_bShowType  = 0;		//공지사항.

	for ( INT nCnt = 0; nCnt < _MAX_GUILD_BTN; nCnt++ )
	{
		m_xGuildBtn[nCnt].Init();
	}

	m_xGuildScrlBar.Init();

	m_xMemberList.ClearAll();
	m_xEditMemberList.ClearAll();
	m_xNoticeList.ClearAll();
	m_xEditNoticeList.ClearAll();
	m_xGuildChatList.ClearAll();

	ZeroMemory(&m_szTemp, sizeof(8192));
	m_nStep = 0;
}

VOID CGuildWnd::Destroy()
{
	CGameWnd::Destroy();
}

VOID CGuildWnd::CreateGuildWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove)
{
	CreateGameWnd(nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight);

	m_xGuildBtn[_BTN_ID_GUILDLOSE].CreateGameBtn	(pxWndImage, 1221, 1222, nStartX+554, nStartY+401, g_xMsg.GetMsg(1052), _BTN_TYPE_FOCUS, 1221, FALSE);
	m_xGuildBtn[_BTN_ID_NOTICE].CreateGameBtn		(pxWndImage, 281, 281, nStartX+41, nStartY+387, g_xMsg.GetMsg(4010), _BTN_TYPE_FOCUS, -1, FALSE);
	m_xGuildBtn[_BTN_ID_GUILDER].CreateGameBtn		(pxWndImage, 281, 281, nStartX+91, nStartY+387, g_xMsg.GetMsg(4009), _BTN_TYPE_FOCUS, -1, FALSE);
	m_xGuildBtn[_BTN_ID_GUILDCHAT].CreateGameBtn	(pxWndImage, 281, 281, nStartX+141, nStartY+387, g_xMsg.GetMsg(4008), _BTN_TYPE_FOCUS, -1, FALSE);
	m_xGuildBtn[_BTN_ID_NOTICEREPAIR].CreateGameBtn	(pxWndImage, 281, 281, nStartX+291, nStartY+387, g_xMsg.GetMsg(4011), _BTN_TYPE_FOCUS, -1, FALSE);
	m_xGuildBtn[_BTN_ID_GUILDERDEL].CreateGameBtn	(pxWndImage, 281, 281, nStartX+341, nStartY+387, g_xMsg.GetMsg(4012), _BTN_TYPE_FOCUS, -1, FALSE);
	m_xGuildBtn[_BTN_ID_GUILDDEL].CreateGameBtn		(pxWndImage, 281, 281, nStartX+391, nStartY+387, g_xMsg.GetMsg(4013), _BTN_TYPE_FOCUS, -1, FALSE);
	m_xGuildBtn[_BTN_ID_CHANGEPOS].CreateGameBtn	(pxWndImage, 281, 281, nStartX+441, nStartY+387, g_xMsg.GetMsg(4014), _BTN_TYPE_FOCUS, -1, FALSE);
	m_xGuildBtn[_BTN_ID_ALLYDEL].CreateGameBtn		(pxWndImage, 281, 281, nStartX+491, nStartY+387, g_xMsg.GetMsg(4015), _BTN_TYPE_FOCUS, -1, FALSE);

	m_xGuildScrlBar.CreateScrlBar(pxWndImage, 1225, _MAX_CHATLINE_POPUP, 12, 258, 12);
}

VOID CGuildWnd::ShowGuildWnd()
{
	ShowGameWnd();

	RECT		rcGuild;
	SetRect(&rcGuild, m_rcWnd.left+260, m_rcWnd.top+20, m_rcWnd.left+480, m_rcWnd.top+40);
	g_xMainWnd.PutsHan(NULL, rcGuild, RGB(255, 200, 150), RGB(0, 0, 0), m_szGuildName);

	if ( m_bShowType == 0 )				// 공지사항.
	{
		ShowNotice();
	}
	else if ( m_bShowType == 1 )		// 문원리스트.
	{
		ShowMemberList();
	}
	else								// 문파채팅.
	{
		ShowGuildChatList();
	}

	if ( m_bShowType == 0 )				// 공지사항.
	{
		m_xGuildScrlBar.ShowScrlBar(m_rcWnd.left+570, m_rcWnd.top+60, m_nStartLine, m_xNoticeList.GetCount());
	}
	else if ( m_bShowType == 1 )		// 문원리스트.
	{
		m_xGuildScrlBar.ShowScrlBar(m_rcWnd.left+570, m_rcWnd.top+60, m_nStartLine, m_xMemberList.GetCount());
	}
	else								// 문파채팅.
	{
		m_xGuildScrlBar.ShowScrlBar(m_rcWnd.left+570, m_rcWnd.top+60, m_nStartLine, m_xGuildChatList.GetCount());
	}

	m_xGuildBtn[_BTN_ID_GUILDLOSE].ChangeRect	 (m_rcWnd.left+546, m_rcWnd.top+398);
	m_xGuildBtn[_BTN_ID_NOTICE].ChangeRect		 (m_rcWnd.left+ 20, m_rcWnd.top+376);
	m_xGuildBtn[_BTN_ID_GUILDER].ChangeRect		 (m_rcWnd.left+100, m_rcWnd.top+376);
	m_xGuildBtn[_BTN_ID_GUILDCHAT].ChangeRect	 (m_rcWnd.left+ 20, m_rcWnd.top+406);
	m_xGuildBtn[_BTN_ID_NOTICEREPAIR].ChangeRect (m_rcWnd.left+297, m_rcWnd.top+376);
	m_xGuildBtn[_BTN_ID_GUILDERDEL].ChangeRect	 (m_rcWnd.left+377, m_rcWnd.top+376);
	m_xGuildBtn[_BTN_ID_GUILDDEL].ChangeRect	 (m_rcWnd.left+457, m_rcWnd.top+406);
	m_xGuildBtn[_BTN_ID_CHANGEPOS].ChangeRect	 (m_rcWnd.left+297, m_rcWnd.top+406);
	m_xGuildBtn[_BTN_ID_ALLYDEL].ChangeRect		 (m_rcWnd.left+377, m_rcWnd.top+406);

	for ( INT nCnt = _MAX_GUILD_BTN -1 ; nCnt > -1; nCnt-- )
	{
		m_xGuildBtn[nCnt].ShowGameBtn();
	}

	RECT rcBtn = {m_rcWnd.left+20, m_rcWnd.top+380, m_rcWnd.left+96, m_rcWnd.top + 400};

	// 공지사항
	g_xMainWnd.PutsHan(NULL, rcBtn, RGB(255, 255, 0), RGB(0, 0, 0), "공지사항");

	rcBtn.left += 80;
	rcBtn.right += 80;

	// 문원목록
	g_xMainWnd.PutsHan(NULL, rcBtn, RGB(255, 255, 0), RGB(0, 0, 0), "문원목록");
	
	rcBtn.left += 198;
	rcBtn.right += 198;

	// 공지수정
	g_xMainWnd.PutsHan(NULL, rcBtn, RGB(255, 255, 0), RGB(0, 0, 0), "공지수정");
	
	rcBtn.left += 80;
	rcBtn.right += 80;

	// 문원삭제
	g_xMainWnd.PutsHan(NULL, rcBtn, RGB(255, 255, 0), RGB(0, 0, 0), "문원삭제");
	
	rcBtn.top += 30;
	rcBtn.bottom += 30;

	rcBtn.left = m_rcWnd.left+20;
	rcBtn.right = m_rcWnd.left+96;

	// 문파채팅
	g_xMainWnd.PutsHan(NULL, rcBtn, RGB(255, 255, 0), RGB(0, 0, 0), "문파채팅");
	
	rcBtn.left += 278;
	rcBtn.right += 278;

	// 직위수정
	g_xMainWnd.PutsHan(NULL, rcBtn, RGB(255, 255, 0), RGB(0, 0, 0), "직위수정");
	
	rcBtn.left += 80;
	rcBtn.right += 80;

	// 동맹해제
	g_xMainWnd.PutsHan(NULL, rcBtn, RGB(255, 255, 0), RGB(0, 0, 0), "동맹해제");
	
	rcBtn.left += 80;
	rcBtn.right += 80;

	// 문파해체
	g_xMainWnd.PutsHan(NULL, rcBtn, RGB(255, 255, 0), RGB(0, 0, 0), "문파해체");

	INT nFlagIdx = 1689 + g_xGameProc.m_xMyHero.m_bGuildFlag;

	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(nFlagIdx) )
	{
		WORD wClr = 0XFFFF;
		wClr = g_xMainWnd.ConvertColor24To16(RGB(g_xGameProc.m_xMyHero.m_bFlagColorB, 
												 g_xGameProc.m_xMyHero.m_bFlagColorG,
												 g_xGameProc.m_xMyHero.m_bFlagColorR));
 		g_xMainWnd.DrawWithABlendCompDataWithBackBufferEx(m_rcWnd.left+500, m_rcWnd.top+280,
														  g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth,
														  g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
														  (WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage, _CLIP_WIDTH, 600, wClr, 0XFFFF, 25);
	}
}



VOID CGuildWnd::ShowNotice()
{
	RECT	rcTitle = {m_rcWnd.left + 45, m_rcWnd.top + 17, m_rcWnd.left + 196, m_rcWnd.top + 42};
	g_xMainWnd.PutsHan(NULL, rcTitle, RGB(255, 200, 150), RGB(0, 0, 0), g_xMsg.GetMsg(4010));

	if (m_xNoticeList.GetCount())
	{
		INT							nCnt, nShowLine;
		CListNode <CGuildMsgList>	*pNode;
		CGuildMsgList*				pxMsg = NULL;
		SIZE						sizeLen;

		sizeLen = g_xMainWnd.GetStrLength(NULL, NULL, m_szGuildName);
		sizeLen.cy += 5;

		nShowLine = ((m_xNoticeList.GetCount() - m_nStartLine ) >= GUILDWND_MAX_SHOWLINE) ?  GUILDWND_MAX_SHOWLINE : m_xNoticeList.GetCount() - m_nStartLine;
		
		for (pNode = m_xNoticeList.GetHead(), nCnt = 0; pNode; pNode = pNode->GetNext(), nCnt++)
		{
			if ( nCnt < m_nStartLine )
			{
				continue;
			}

			if ( nCnt >= m_nStartLine + nShowLine )
			{
				break;
			}

			pxMsg = pNode->GetData();

			if ( pxMsg )
			{
				if ( !strcmp(pxMsg->m_szData, g_xMsg.GetMsg(4004)) || !strcmp(pxMsg->m_szData, g_xMsg.GetMsg(4005)) || !strcmp(pxMsg->m_szData, g_xMsg.GetMsg(4006)) )
				{
					g_xMainWnd.PutsHan(NULL, m_rcWnd.left + GUILDWND_TEXT_STARTX, m_rcWnd.top + GUILDWND_TEXT_STARTY + (nCnt - m_nStartLine) * sizeLen.cy,
									   RGB(255, 150, 0), RGB(0, 0, 0), pxMsg->m_szData);
				}
				else
				{
					g_xMainWnd.PutsHan(NULL, m_rcWnd.left + GUILDWND_TEXT_STARTX, m_rcWnd.top + GUILDWND_TEXT_STARTY + (nCnt - m_nStartLine) * sizeLen.cy,
									   RGB(255, 255, 255), RGB(0, 0, 0), pxMsg->m_szData);
				}
			}
		}
	}
}


VOID CGuildWnd::ShowMemberList()
{
	RECT	rcTitle = {m_rcWnd.left + 45, m_rcWnd.top + 17, m_rcWnd.left + 196, m_rcWnd.top + 42};
	g_xMainWnd.PutsHan(NULL, rcTitle, RGB(255, 200, 150), RGB(0, 0, 0), g_xMsg.GetMsg(4009));

	if (m_xMemberList.GetCount())
	{
		INT							nCnt, nShowLine;
		CListNode <CGuildMsgList>	*pNode;
		CGuildMsgList*				pxMsg = NULL;
		SIZE						sizeLen;

		sizeLen = g_xMainWnd.GetStrLength(NULL, NULL, m_szGuildName);
		sizeLen.cy += 5;

		nShowLine = ((m_xMemberList.GetCount() - m_nStartLine ) >= GUILDWND_MAX_SHOWLINE) ?  GUILDWND_MAX_SHOWLINE : m_xMemberList.GetCount() - m_nStartLine;
		
		for (pNode = m_xMemberList.GetHead(), nCnt = 0; pNode; pNode = pNode->GetNext(), nCnt++)
		{
			if ( nCnt < m_nStartLine )
			{
				continue;
			}

			if ( nCnt >= m_nStartLine + nShowLine )
			{
				break;
			}

			pxMsg = pNode->GetData();

			if ( pxMsg )
			{
				if ( !strcmp(pxMsg->m_szData, g_xMsg.GetMsg(4007)) )
				{
					g_xMainWnd.PutsHan(NULL, m_rcWnd.left + GUILDWND_TEXT_STARTX, m_rcWnd.top + GUILDWND_TEXT_STARTY + (nCnt - m_nStartLine) * sizeLen.cy,
									   RGB(255, 150, 0), RGB(0, 0, 0), pxMsg->m_szData);
				}
				else
				{
					g_xMainWnd.PutsHan(NULL, m_rcWnd.left + GUILDWND_TEXT_STARTX, m_rcWnd.top + GUILDWND_TEXT_STARTY + (nCnt - m_nStartLine) * sizeLen.cy,
									   RGB(255, 255, 255), RGB(0, 0, 0), pxMsg->m_szData);
				}
			}
		}
	}
}


VOID CGuildWnd::ShowGuildChatList()
{
	RECT	rcTitle = {m_rcWnd.left + 45, m_rcWnd.top + 17, m_rcWnd.left + 196, m_rcWnd.top + 42};
	g_xMainWnd.PutsHan(NULL, rcTitle, RGB(255, 200, 150), RGB(0, 0, 0), g_xMsg.GetMsg(4008));

	if (m_xGuildChatList.GetCount())
	{
		INT							nCnt, nShowLine;
		CListNode <CGuildMsgList>	*pNode;
		CGuildMsgList*				pxMsg = NULL;
		SIZE						sizeLen;

		sizeLen = g_xMainWnd.GetStrLength(NULL, NULL, m_szGuildName);
		sizeLen.cy += 5;

		nShowLine = ((m_xGuildChatList.GetCount() - m_nStartLine ) >= GUILDWND_MAX_SHOWLINE) ?  GUILDWND_MAX_SHOWLINE : m_xGuildChatList.GetCount() - m_nStartLine;
		
		for (pNode = m_xGuildChatList.GetHead(), nCnt = 0; pNode; pNode = pNode->GetNext(), nCnt++)
		{
			if ( nCnt < m_nStartLine )
			{
				continue;
			}

			if ( nCnt >= m_nStartLine + nShowLine )
			{
				break;
			}

			pxMsg = pNode->GetData();

			if ( pxMsg )
			{
				g_xMainWnd.PutsHan(NULL, m_rcWnd.left + GUILDWND_TEXT_STARTX-1, m_rcWnd.top + GUILDWND_TEXT_STARTY + (nCnt - m_nStartLine) * sizeLen.cy -1,
								   RGB(10, 20, 10), RGB(0, 0, 0), pxMsg->m_szData);
				g_xMainWnd.PutsHan(NULL, m_rcWnd.left + GUILDWND_TEXT_STARTX, m_rcWnd.top + GUILDWND_TEXT_STARTY + (nCnt - m_nStartLine) * sizeLen.cy,
								   RGB(0, 255, 0), RGB(0, 0, 0), pxMsg->m_szData);
			}
		}
	}
}




VOID CGuildWnd::MsgAdd(CHAR* pszMsg)
{
	if ( pszMsg )
	{	
		if ( pszMsg[0] != NULL )
		{
			INT  nCnt;
			CHAT stChat;
			INT	 nLineCnt;
			CHAR pszDivied[_MAX_STRING_LEN*2];
			CHAR pszArg[5][MAX_PATH];

			ZeroMemory(pszDivied, _MAX_STRING_LEN*2);
			ZeroMemory(pszArg,	  MAX_PATH*5);

			g_xMainWnd.StringDivide(514, nLineCnt, pszMsg, pszDivied);

			sscanf(pszDivied, "%[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c", pszArg[0], pszArg[1], pszArg[2], pszArg[3], pszArg[4]);

			if ( nLineCnt > 5 )		
			{
				nLineCnt = 5;
			}

			// 문자열 삽입.
			for ( nCnt = 0; nCnt < nLineCnt; nCnt++ )
			{
				// 칸이 다음으로 갈조건.
				if ( m_xGuildChatList.GetCount() - m_nStartLine == GUILDWND_MAX_SHOWLINE )
				{
					m_nStartLine++;
				}

				CGuildMsgList* pxMsg = new CGuildMsgList;
				strcpy(pxMsg->m_szData, pszArg[nCnt]);
				m_xGuildChatList.Insert(pxMsg);
			}


			CListNode < CGuildMsgList >*	pNode;
			CGuildMsgList*					pxMsg = NULL;
			// 최대저장라인 검사해서 그이상이면 삭제한다.
			while ( m_xGuildChatList.GetCount() >= _MAX_SAVECHATLINE )
			{
				pNode = m_xGuildChatList.GetHead();

				pxMsg = m_xGuildChatList.RemoveNode(pNode);
				SAFE_DELETE((CGuildMsgList*)pxMsg);

				if ( m_nStartLine > 0 )
				{
					m_nStartLine--;
				}
			}
		}
	}
}



LRESULT CGuildWnd::OnMsgBoxReturn(WPARAM wParam, LPARAM lParam)
{
	BYTE	bMsgReturn;
	WORD	wPacket;

	bMsgReturn = LOBYTE(HIWORD(wParam));
	wPacket	   = LOWORD(wParam);

/*	if ( wPacket == CM_GUILDADDMEMBER && bMsgReturn == _BTN_YES )
	{
		g_xClientSocket.SendGuildAddMem((CHAR*)lParam);
	}
	else */
	if ( wPacket == CM_GUILDDELMEMBER && bMsgReturn == _BTN_YES )
	{
		g_xClientSocket.SendGuildDelMem((CHAR*)lParam);
		g_xClientSocket.SendGuildMemberList();		
	}
	else if ( wPacket == CM_GUILDMAKEALLY && bMsgReturn == _BTN_YES )
	{
		g_xClientSocket.SendSay(g_xMsg.GetMsg(4018));
	}
	else if ( wPacket == CM_GUILDBREAKALLY && bMsgReturn == _BTN_YES )
	{
		CHAR pszMessage[MAX_PATH];
		ZeroMemory(pszMessage, MAX_PATH);

		// 동맹파기 2006.10.23
		CHAR szMsg[ MAX_PATH ];
		sprintf( szMsg, "@%s", g_xMsg.GetMsg( 4016 ) );		// 4016 동맹파기

		g_xMainWnd.StringPlus(pszMessage, szMsg, (CHAR*)lParam, "");
		g_xClientSocket.SendSay(pszMessage);
		g_xClientSocket.SendGuildHome();
	}

	return 0L;
}


BOOL CGuildWnd::OnLButtonUp(POINT ptMouse)
{
	INT nCnt;

	if ( m_xGuildScrlBar.OnLButtonUp(ptMouse) )
	{
		return FALSE;
	}

	if ( m_xGuildBtn[_BTN_ID_GUILDLOSE].OnLButtonUp(ptMouse) )
	{
		return TRUE;
	}

	// 공지사항보기버튼.
	if ( m_xGuildBtn[_BTN_ID_NOTICE].OnLButtonUp(ptMouse) )
	{
		m_bShowType = 0;
		m_nStartLine = 0;
		g_xClientSocket.SendGuildHome();
		return FALSE;
	}

	// 문원목록보기버튼.
	if ( m_xGuildBtn[_BTN_ID_GUILDER].OnLButtonUp(ptMouse) )
	{
		m_bShowType = 1;
		m_nStartLine = 0;
		g_xClientSocket.SendGuildMemberList();		
		return FALSE;
	}

	// 문파채팅버튼.
	if ( m_xGuildBtn[_BTN_ID_GUILDCHAT].OnLButtonUp(ptMouse) )
	{
		m_nStartLine = 0;
		m_bShowType = 2;
		return FALSE;
	}

	// 공지사항수정버튼.
	if ( m_xGuildBtn[_BTN_ID_NOTICEREPAIR].OnLButtonUp(ptMouse) )
	{
		if ( m_bIsGM == FALSE )
		{
			g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(4000));
			return FALSE;
		}

		g_xGameProc.m_xInterface.WindowActivate(_WND_ID_NOTICEEDIT);
		g_xGameProc.m_xInterface.m_xNoticeEditWnd.SetEditType(1);

		// 공지사항 목록을 에디트 박스안에 넣어준다.
		TCHAR  pszMessage[5000];
		ZeroMemory(pszMessage, 5000);

		INT				nLineCnt = 0;
		CGuildMsgList*	pxMsg = NULL;
		CListNode <CGuildMsgList>	*pNode;

		if (m_xEditNoticeList.GetCount())
		{
			for (pNode = m_xEditNoticeList.GetHead(); pNode; pNode = pNode->GetNext())
			{
				pxMsg = pNode->GetData();

				if ( pxMsg )
				{
					g_xMainWnd.StringPlus(pszMessage, pxMsg->m_szData, "\r\n", "");
				}
			}
		}

		if ( g_xGameProc.m_xInterface.m_xNoticeEditWnd.m_hNoticeEdit )
		{
			SetWindowText(g_xGameProc.m_xInterface.m_xNoticeEditWnd.m_hNoticeEdit, pszMessage);

/*			INT nLen = strlen(pszMessage);
			SendMessage(g_xGameProc.m_xInterface.m_xNoticeEditWnd.m_hNoticeEdit, EM_SETSEL, nLen , nLen);
*/		}
		
		return FALSE;
	}

	// 문파직위수정버튼.
	if ( m_xGuildBtn[_BTN_ID_CHANGEPOS].OnLButtonUp(ptMouse) )
	{
		if ( m_bIsGM == FALSE )
		{
			g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(4000));
			return FALSE;
		}
		else if ( m_xMemberList.GetCount() == 0 )
		{
			g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(4017));
			return FALSE;
		}		

		g_xGameProc.m_xInterface.WindowActivate(_WND_ID_NOTICEEDIT);
		g_xGameProc.m_xInterface.m_xNoticeEditWnd.SetEditType(0);

		// 문원리스트 목록을 에디트 박스안에 넣어준다.
		TCHAR  pszMessage[5000];
		ZeroMemory(pszMessage, 5000);

		INT				nLineCnt = 0;
		CGuildMsgList*	pxMsg = NULL;
		CListNode <CGuildMsgList>	*pNode;

		if (m_xEditMemberList.GetCount())
		{
			for (pNode = m_xEditMemberList.GetHead(); pNode; pNode = pNode->GetNext())
			{
				pxMsg = pNode->GetData();

				if ( pxMsg )
				{
					g_xMainWnd.StringPlus(pszMessage, pxMsg->m_szData, "\r\n", "");
				}
			}
		}

		if ( g_xGameProc.m_xInterface.m_xNoticeEditWnd.m_hNoticeEdit )
		{
			SetWindowText(g_xGameProc.m_xInterface.m_xNoticeEditWnd.m_hNoticeEdit, pszMessage);

/*			INT nLen = strlen(pszMessage);
			SendMessage(g_xGameProc.m_xInterface.m_xNoticeEditWnd.m_hNoticeEdit, EM_SETSEL, nLen , nLen);
*/		}
		
		return FALSE;
	}

/*	if ( m_xGuildBtn[_BTN_ID_NOTICE].OnLButtonUp(ptMouse) )
	{
		CHAR pszMsg[MAX_PATH];
		sprintf(pszMsg, "%s 의 문원으로 추가할 사람의 이름을 입력하십시오.", m_szGuildName);
		g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _YESNO, pszMsg, TRUE, -1, -1, CM_GUILDADDMEMBER);
		return FALSE;
	}
*/
/*	if ( m_xGuildBtn[_BTN_ID_GUILDDEL].OnLButtonUp(ptMouse) )
	{
		g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _YESNO, 
											   "동맹을 하기 위해서는 상대방 문파가 [동맹가능] 상태 이어야 하며 상대 문주와 마주보고 있어야 합니다. 동맹을 하시겠습니까?", 
											   TRUE, -1, -1, CM_GUILDMAKEALLY);
		return FALSE;
	}
*/	

	if ( m_xGuildBtn[_BTN_ID_GUILDERDEL].OnLButtonUp(ptMouse) )
	{
		if ( m_bIsGM == FALSE )
		{
			g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(4000));
			return FALSE;
		}

		CHAR pszMsg[MAX_PATH];
		sprintf(pszMsg, "'%s' %s", m_szGuildName, g_xMsg.GetMsg(4001));
		g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _YESNO, pszMsg, TRUE, -1, -1, CM_GUILDDELMEMBER);
		return FALSE;
	}

	if ( m_xGuildBtn[_BTN_ID_ALLYDEL].OnLButtonUp(ptMouse) )
	{
		if ( m_bIsGM == FALSE )
		{
			g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(4000));
			return FALSE;
		}

		g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _YESNO, 
											   g_xMsg.GetMsg(4002), TRUE, -1, -1, CM_GUILDBREAKALLY);
		return FALSE;
	}

	if ( m_xGuildBtn[_BTN_ID_GUILDDEL].OnLButtonUp(ptMouse) )
	{
		if ( m_bIsGM == FALSE )
		{
			g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(4000));
			return FALSE;
		}
		// 새로운패킷필요.
		return FALSE;
	}

	return FALSE;
}

BOOL CGuildWnd::OnLButtonDown(POINT ptMouse)
{
	INT nCnt;

	if ( m_xGuildScrlBar.OnLButtonDown(ptMouse) )
	{
		FLOAT	fScrlRate;

		fScrlRate = m_xGuildScrlBar.GetScrlRate();

		if ( m_bShowType == 0 )				// 공지사항.
		{
			m_nStartLine = (INT)((m_xNoticeList.GetCount()-1)*fScrlRate);
		}
		else if ( m_bShowType == 1 )		// 문원리스트.
		{
			m_nStartLine = (INT)((m_xMemberList.GetCount()-1)*fScrlRate);
		}
		else								// 문파채팅.
		{
			m_nStartLine = (INT)((m_xGuildChatList.GetCount()-1)*fScrlRate);
		}


		return TRUE;
	}

	for ( nCnt = 0; nCnt < _MAX_GUILD_BTN; nCnt++ )
	{
		if ( m_xGuildBtn[nCnt].OnLButtonDown(ptMouse) )
		{
			return TRUE;
		}
	}

	return FALSE;
}


VOID CGuildWnd::OnScrollDown()
{
	if ( m_nStartLine > 0 )												m_nStartLine--;
}


VOID CGuildWnd::OnScrollUp()
{
	if ( m_bShowType == 0 )				// 공지사항.
	{
		if ( m_nStartLine < m_xNoticeList.GetCount()-1 )		m_nStartLine++;
	}
	else if ( m_bShowType == 1 )		// 문원리스트.
	{
		if ( m_nStartLine < m_xMemberList.GetCount()-1 )		m_nStartLine++;
	}
	else								// 문파채팅.
	{
		if ( m_nStartLine < m_xGuildChatList.GetCount()-1 )		m_nStartLine++;
	}
}

BOOL CGuildWnd::OnMouseMove(POINT ptMouse)
{
	INT nCnt;

	if ( m_xGuildScrlBar.OnMouseMove(ptMouse) )
	{
		FLOAT	fScrlRate;
		fScrlRate = m_xGuildScrlBar.GetScrlRate();

		if ( m_bShowType == 0 )				// 공지사항.
		{
			m_nStartLine = (INT)((m_xNoticeList.GetCount()-1)*fScrlRate);
		}
		else if ( m_bShowType == 1 )		// 문원리스트.
		{
			m_nStartLine = (INT)((m_xMemberList.GetCount()-1)*fScrlRate);
		}
		else								// 문파채팅.
		{
			m_nStartLine = (INT)((m_xGuildChatList.GetCount()-1)*fScrlRate);
		}
		return TRUE;
	}

	for ( nCnt = 0; nCnt < _MAX_GUILD_BTN; nCnt++ )
	{
		m_xGuildBtn[nCnt].OnMouseMove(ptMouse);
	}

	return FALSE;
}

VOID CGuildWnd::SetStatusBtnInit()
{
	INT nCnt;

	for ( nCnt = 0; nCnt < _MAX_GUILD_BTN; nCnt++ )
	{
		m_xGuildBtn[nCnt].SetBtnState(_BTN_STATE_NORMAL);
	}
}


VOID CGuildWnd::DevideGuildHome(CHAR *pszMsg)
{
	char	*pszGuildMaster, *pszData;
	char	*pszEmpty1, *pszEmpty2;
	char	*pszNotice;
	m_nStep = 0;

	m_xNoticeList.ClearAll();
	m_xEditNoticeList.ClearAll();
	m_bIsGM	= FALSE;

	CGuildMsgList* pxTmp1 = new CGuildMsgList;
	sprintf(pxTmp1->m_szData, "%s", g_xMsg.GetMsg(4003));
	m_xNoticeList.Insert(pxTmp1);

	CGuildMsgList* pxTmp2 = new CGuildMsgList;
	sprintf(pxTmp2->m_szData, " ");
	m_xNoticeList.Insert(pxTmp2);

	if ( pszEmpty1 = strchr(pszMsg, 0x0D) )
	{
		*pszEmpty1++ = '\0';

		strcpy(m_szGuildName, pszMsg);
		
		if (pszEmpty2 = strchr(pszEmpty1, 0x0D))
		{
			if (pszGuildMaster = strchr(pszEmpty2, 0x0D))
			{
				*pszGuildMaster++ = '\0';

				if ( *pszGuildMaster == '1' )
				{
					m_bIsGM = TRUE;
				}

				if (pszData = strchr(pszGuildMaster, 0x0D))
				{
					*pszData++ = '\0';

					while (pszData)
					{
						if (pszNotice = strchr(pszData, 0x0D))
						{
							*pszNotice++ = '\0';

							CGuildMsgList* pxMsg = new CGuildMsgList;

							if (memcmp(pszData, "<Notice>", 8) == 0)
							{
								sprintf(pxMsg->m_szData, "%s", g_xMsg.GetMsg(4004));
								m_nStep = 1;
							}
							else if (memcmp(pszData, "<KillGuilds>", 12) == 0)
							{
								sprintf(pxMsg->m_szData, "%s", g_xMsg.GetMsg(4005));
								m_nStep = 2;
							}
							else if (memcmp(pszData, "<AllyGuilds>", 12) == 0)
							{
								sprintf(pxMsg->m_szData, "%s", g_xMsg.GetMsg(4006));
								m_nStep = 3;
							}
							else
							{
								INT nLen = strlen( pszData );
								if ( nLen > 100 )
									INT ntest = 0;
								strcpy(pxMsg->m_szData, pszData);

								if ( m_nStep == 1 || m_nStep == 2 )
								{
									CGuildMsgList* pxEditMsg = new CGuildMsgList;
									strcpy(pxEditMsg->m_szData, pszData);
									m_xEditNoticeList.Insert(pxEditMsg);
								}
							}

							m_xNoticeList.Insert(pxMsg);
							pszData = pszNotice;
						}
						else
						{
							CGuildMsgList* pxMsg = new CGuildMsgList;
								INT nLen = strlen( pszData );
								if ( nLen > 100 )
									INT ntest = 0;
								strcpy(pxMsg->m_szData, pszData);

								if ( m_nStep == 1 || m_nStep == 2 )
								{
									CGuildMsgList* pxEditMsg = new CGuildMsgList;
									strcpy(pxEditMsg->m_szData, pszData);
									m_xEditNoticeList.Insert(pxEditMsg);
								}

							m_xNoticeList.Insert(pxMsg);

//							sprintf(m_szTemp, pszData);
							break;
						}
					}
				}
			}
		}
	}
}


VOID CGuildWnd::AddGuildHome(CHAR *pszMsg)
{
	char	*pszGuildMaster, *pszData;
	char	*pszEmpty1, *pszEmpty2;
	char	*pszNotice;
	
	while (pszMsg)
	{
		if (pszNotice = strchr(pszMsg, 0x0D))
		{
			*pszNotice++ = '\0';

			CGuildMsgList* pxMsg = new CGuildMsgList;

			if (memcmp(pszMsg, "<Notice>", 8) == 0)
			{
				sprintf(pxMsg->m_szData, "%s", g_xMsg.GetMsg(4004));
				m_nStep = 1;
			}
			else if (memcmp(pszMsg, "<KillGuilds>", 12) == 0)
			{
				sprintf(pxMsg->m_szData, "%s", g_xMsg.GetMsg(4005));
				m_nStep = 2;
			}
			else if (memcmp(pszMsg, "<AllyGuilds>", 12) == 0)
			{
				sprintf(pxMsg->m_szData, "%s", g_xMsg.GetMsg(4006));
				m_nStep = 3;
			}
			else
			{
				int ntest = 0;
				strcpy(pxMsg->m_szData, pszMsg);
/*
				if ( m_szTemp != NULL )
				{
					ntest = strlen(m_szTemp);
					strcat(m_szTemp, pxMsg->m_szData);
					ntest = strlen(m_szTemp);
					strcpy(pxMsg->m_szData, m_szTemp);
				}
*/
				if ( m_nStep == 1 || m_nStep == 2 )
				{
					CGuildMsgList* pxEditMsg = new CGuildMsgList;
					strcpy(pxEditMsg->m_szData, pszMsg);
/*
					if ( m_szTemp != NULL )
					{
						strcat(m_szTemp, pxEditMsg->m_szData);
						strcpy(pxEditMsg->m_szData, m_szTemp);
					}
*/
					m_xEditNoticeList.Insert(pxEditMsg);
				}
			}

			m_xNoticeList.Insert(pxMsg);
//			ZeroMemory(&m_szTemp, sizeof(8192));
			pszMsg = pszNotice;
		}
		else
			break;
	}
}

VOID CGuildWnd::DevideGuildMemberList(CHAR *pszMsg)
{
	char			szDecodeMsg[8192];
//	CGuildRank*		pCurrGuildRank	= NULL;
	char			*pszDevide		= NULL;
	char			*pszNext		= NULL;
	int				nMaxLength		= 0;
	INT				nRank			= 0;

	CHAR*			pszRank			= NULL;
	CHAR*			pszRankName		= NULL;
	CHAR*			pszMember		= NULL;

	CHAR			pszMemberLine[MAX_PATH];
	INT				nMemberLen		= 0;
	ZeroMemory(pszMemberLine, MAX_PATH);

	nMaxLength = fnDecode6BitBuf(pszMsg, szDecodeMsg, sizeof(szDecodeMsg));
	szDecodeMsg[nMaxLength] = '\0';

	m_xMemberList.ClearAll();
	m_xEditMemberList.ClearAll();

	pszDevide = szDecodeMsg;

	CGuildMsgList* pxTmp1 = new CGuildMsgList;
	sprintf(pxTmp1->m_szData, "%s", g_xMsg.GetMsg(4003));
	m_xMemberList.Insert(pxTmp1);

	CGuildMsgList* pxTmp2 = new CGuildMsgList;
	sprintf(pxTmp2->m_szData, " ");
	m_xMemberList.Insert(pxTmp2);

	CGuildMsgList* pxSubject = new CGuildMsgList;
	sprintf(pxSubject->m_szData, "%s", g_xMsg.GetMsg(4007));
	m_xMemberList.Insert(pxSubject);

	while (pszNext = strchr(pszDevide, '/'))
	{
		*pszNext = '\0';

		if (*pszDevide == '#')
		{
			nRank = atoi(pszDevide + 1);
			nMemberLen = 0;
			ZeroMemory(pszMemberLine, MAX_PATH);
		}
		else if (*pszDevide == '*')
		{
			pszRankName = pszDevide + 1;

			CHAR pszRank[MAX_PATH];
			itoa(nRank, pszRank, 10);

			CGuildMsgList* pxMsg = new CGuildMsgList;
			if ( pxMsg )
			{
				if ( m_bIsGM )
				{
					pxMsg->m_szData[0] = '\0';
					g_xMainWnd.StringPlus(pxMsg->m_szData, "(", pszRank, ")", " ", "<", pszRankName, ">", "");
				}	
				else
				{
					pxMsg->m_szData[0] = '\0';
					g_xMainWnd.StringPlus(pxMsg->m_szData, "<", pszRankName, ">", "");
				}
				m_xMemberList.Insert(pxMsg);
			}

			CGuildMsgList* pxEditMsg = new CGuildMsgList;
			if ( pxEditMsg )
			{
				pxEditMsg->m_szData[0] = '\0';
				g_xMainWnd.StringPlus(pxEditMsg->m_szData, "#", pszRank, " ", "<", pszRankName, ">", "");
				m_xEditMemberList.Insert(pxEditMsg);
			}
			nMemberLen = 0;
			ZeroMemory(pszMemberLine, MAX_PATH);
		}
		else
		{
			nMemberLen += (strlen(pszDevide) + 1);

			g_xMainWnd.StringPlus(pszMemberLine, pszDevide, " ", "");

			if ( nMemberLen > 60 || (*(pszNext + 1) == '#') || (*(pszNext + 1) == '\0') )
			{
				CGuildMsgList* pxMsg = new CGuildMsgList;
				if ( pxMsg )
				{
					pxMsg->m_szData[0] = '\0';
					g_xMainWnd.StringPlus(pxMsg->m_szData, pszMemberLine, "");
					m_xMemberList.Insert(pxMsg);
				}

				CGuildMsgList* pxEditMsg = new CGuildMsgList;
				if ( pxEditMsg )
				{
					pxEditMsg->m_szData[0] = '\0';
					g_xMainWnd.StringPlus(pxEditMsg->m_szData, pszMemberLine, "");
					m_xEditMemberList.Insert(pxEditMsg);
				}

				nMemberLen = 0;
				ZeroMemory(pszMemberLine, MAX_PATH);
			}
		}

		if ((pszNext - &szDecodeMsg[0]) >= nMaxLength) 
		{
			break;
		}

		pszDevide = (pszNext + 1);
	}
}

VOID CGuildWnd::AddGuildMemberList(CHAR *pszMsg)
{
	char			szDecodeMsg[8192];
//	CGuildRank*		pCurrGuildRank	= NULL;
	char			*pszDevide		= NULL;
	char			*pszNext		= NULL;
	int				nMaxLength		= 0;
	INT				nRank			= 0;

	CHAR*			pszRank			= NULL;
	CHAR*			pszRankName		= NULL;
	CHAR*			pszMember		= NULL;

	CHAR			pszMemberLine[MAX_PATH];
	INT				nMemberLen		= 0;
	ZeroMemory(pszMemberLine, MAX_PATH);

	nMaxLength = fnDecode6BitBuf(pszMsg, szDecodeMsg, sizeof(szDecodeMsg));
	szDecodeMsg[nMaxLength] = '\0';

	m_xMemberList.ClearAll();
	m_xEditMemberList.ClearAll();

	pszDevide = szDecodeMsg;

	CGuildMsgList* pxTmp1 = new CGuildMsgList;
	sprintf(pxTmp1->m_szData, "%s", g_xMsg.GetMsg(4003));
	m_xMemberList.Insert(pxTmp1);

	CGuildMsgList* pxTmp2 = new CGuildMsgList;
	sprintf(pxTmp2->m_szData, " ");
	m_xMemberList.Insert(pxTmp2);

	CGuildMsgList* pxSubject = new CGuildMsgList;
	sprintf(pxSubject->m_szData, "%s", g_xMsg.GetMsg(4007));
	m_xMemberList.Insert(pxSubject);

	while (pszNext = strchr(pszDevide, '/'))
	{
		*pszNext = '\0';

		if (*pszDevide == '#')
		{
			nRank = atoi(pszDevide + 1);
			nMemberLen = 0;
			ZeroMemory(pszMemberLine, MAX_PATH);
		}
		else if (*pszDevide == '*')
		{
			pszRankName = pszDevide + 1;

			CHAR pszRank[MAX_PATH];
			itoa(nRank, pszRank, 10);

			CGuildMsgList* pxMsg = new CGuildMsgList;
			if ( pxMsg )
			{
				if ( m_bIsGM )
				{
					pxMsg->m_szData[0] = '\0';
					g_xMainWnd.StringPlus(pxMsg->m_szData, "(", pszRank, ")", " ", "<", pszRankName, ">", "");
				}	
				else
				{
					pxMsg->m_szData[0] = '\0';
					g_xMainWnd.StringPlus(pxMsg->m_szData, "<", pszRankName, ">", "");
				}
				m_xMemberList.Insert(pxMsg);
			}

			CGuildMsgList* pxEditMsg = new CGuildMsgList;
			if ( pxEditMsg )
			{
				pxEditMsg->m_szData[0] = '\0';
				g_xMainWnd.StringPlus(pxEditMsg->m_szData, "#", pszRank, " ", "<", pszRankName, ">", "");
				m_xEditMemberList.Insert(pxEditMsg);
			}
			nMemberLen = 0;
			ZeroMemory(pszMemberLine, MAX_PATH);
		}
		else
		{
			nMemberLen += (strlen(pszDevide) + 1);

			g_xMainWnd.StringPlus(pszMemberLine, pszDevide, " ", "");

			if ( nMemberLen > 60 || (*(pszNext + 1) == '#') || (*(pszNext + 1) == '\0') )
			{
				CGuildMsgList* pxMsg = new CGuildMsgList;
				if ( pxMsg )
				{
					pxMsg->m_szData[0] = '\0';
					g_xMainWnd.StringPlus(pxMsg->m_szData, pszMemberLine, "");
					m_xMemberList.Insert(pxMsg);
				}

				CGuildMsgList* pxEditMsg = new CGuildMsgList;
				if ( pxEditMsg )
				{
					pxEditMsg->m_szData[0] = '\0';
					g_xMainWnd.StringPlus(pxEditMsg->m_szData, pszMemberLine, "");
					m_xEditMemberList.Insert(pxEditMsg);
				}

				nMemberLen = 0;
				ZeroMemory(pszMemberLine, MAX_PATH);
			}
		}

		if ((pszNext - &szDecodeMsg[0]) >= nMaxLength) 
		{
			break;
		}

		pszDevide = (pszNext + 1);
	}
}

/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"



CChatPopWnd::CChatPopWnd()
{
	Init();
}

CChatPopWnd::~CChatPopWnd()
{
	Destroy();
}


VOID CChatPopWnd::Init()
{
	INT nCnt;
	CGameWnd::Init();

	m_nFstLine			= 0;
	SetRect(&m_rcChatPopFrame, 0, 0, 0, 0);	
	SetRect(&m_rcEditBoxFrame, 0, 0, 0, 0);

	m_xChatPopBar.Init();
	m_xstrDividedChat.ClearAllNodes();

	for ( nCnt = 0; nCnt < _MAX_CHATPOP_BTN; nCnt++ )
	{
		m_xChatPopBtn[nCnt].Init();
	}
}

VOID CChatPopWnd::Destroy()
{
	m_xstrDividedChat.ClearAllNodes();
	Init();
}


VOID CChatPopWnd::CreateChatPopWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend)
{
	CreateGameWnd(nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight, bBlend);
	SetRect(&m_rcChatPopFrame, 40, 29, 531, 308);
	SetRect(&m_rcEditBoxFrame, 25, 311, 524, 326);

	for ( INT nCnt = 0; nCnt < _MAX_CHATLINE_POPUP; nCnt++ )
	{
		SetRect(&m_rcChatPopLine[nCnt], nStartX+35, nStartY+(28+nCnt*14), nStartX+520, nStartY+(43+nCnt*14));
	}

	m_xChatPopBtn[_BTN_ID_CHATCLOSE].CreateGameBtn(pxWndImage, 161, 162, nStartX+532, nStartY+350);
	m_xChatPopBtn[_BTN_ID_CHATDENY].CreateGameBtn  (pxWndImage, 360, 361, nStartX+ 25, nStartY+332, g_xMsg.GetMsg(1200));
	m_xChatPopBtn[_BTN_ID_CHATSHOUT].CreateGameBtn(pxWndImage, 362, 363, nStartX+ 65, nStartY+332, g_xMsg.GetMsg(1201));
	m_xChatPopBtn[_BTN_ID_CHATGROUP].CreateGameBtn(pxWndImage, 364, 365, nStartX+105, nStartY+332, g_xMsg.GetMsg(1202));
	m_xChatPopBtn[_BTN_ID_CHATGUILD].CreateGameBtn(pxWndImage, 366, 367, nStartX+145, nStartY+332, g_xMsg.GetMsg(1203));
	m_xChatPopBtn[_BTN_ID_CHATALLDENY].CreateGameBtn    (pxWndImage, 368, 369, nStartX+185, nStartY+332, g_xMsg.GetMsg(1204));
	m_xChatPopBtn[_BTN_ID_DENYGUILD].CreateGameBtn    (pxWndImage, 370, 371, nStartX+225, nStartY+332, g_xMsg.GetMsg(1205));
	m_xChatPopBtn[_BTN_ID_SCRLUP].CreateGameBtn   (pxWndImage, 380, 381, nStartX+539, nStartY+ 25);
	m_xChatPopBtn[_BTN_ID_SCRLDOWN].CreateGameBtn (pxWndImage, 382, 383, nStartX+539, nStartY+311);

	m_xChatPopBar.CreateScrlBar(pxWndImage, 380, _MAX_CHATLINE_POPUP, 12, 260, 12);
}


BOOL CChatPopWnd::SetCaputeString(POINT ptMouse)
{
	INT nCnt;

	for ( nCnt = 0; nCnt < _MAX_CHATLINE_POPUP; nCnt++ )
	{
		if ( PtInRect(&m_rcChatPopLine[nCnt], ptMouse) )
		{
			if ( !m_xstrDividedChat.CheckEmpty() )
			{
				LPCHAT	pstChat;

				m_xstrDividedChat.MoveCurrentToTop();
				m_xstrDividedChat.MoveNode(m_nFstLine+nCnt);

				pstChat = m_xstrDividedChat.GetCurrentData();

				if ( pstChat )
				{
					CHAR  pszString[MAX_PATH];
					CHAR* pszCapture;
					CHAR* pszCut;

					strcpy(pszString,  pstChat->pszChat);

					pszCapture = pszString;

					if ( pszString[0] == '/' )
					{
						pszCapture = &pszString[1];
					}
					else if ( *pszString == '(' && *(pszString+1) == '!' && *(pszString+2) == ')' )
					{
						pszCapture = &pszString[3];
					}

					pszCut = strchr(pszCapture, ' ');

					if ( !pszCut )
					{
						pszCut = strchr(pszCapture, ':');
					}

					if ( pszCut )
					{
						*pszCut = NULL;

						pszCut = strchr(pszCapture, ':');
						if ( pszCut ) 
						{
							*pszCut = NULL;
						}

						pszCut = strchr(pszCapture, '=');
						if ( pszCut && *(pszCut+1) == '>' )
						{
							*pszCut = NULL;
						}

						sprintf(m_pszLastChatPopCapture, "/%s ", pszCapture);

						g_xGameProc.m_xInterface.m_xChatWnd.ActiveEditBox();
						SetFocus(g_xChatEditBox.GetSafehWnd());
						ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);
						SetWindowText(g_xChatEditBox.GetSafehWnd(), m_pszLastChatPopCapture);

						INT nLen = strlen(m_pszLastChatPopCapture);
						SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETSEL, nLen , nLen);
						g_xChatEditBox.SetHanguelMode();

						return TRUE;
					}
				}
			}
		}
	}

	return FALSE;
}


BOOL CChatPopWnd::MsgAdd(DWORD dwFontColor, DWORD dwFontBackColor, CHAR* szMsg)
{
	if ( szMsg != NULL )
	{
		if ( szMsg[0] != NULL )
		{
			INT nLineCnt;
			CHAR szDivied[_MAX_STRING_LEN*2];
			CHAR szArg[5][MAX_PATH];

			ZeroMemory(szDivied, _MAX_STRING_LEN*2);
			ZeroMemory(&szArg[0], MAX_PATH*5);

			g_xMainWnd.StringDivide(m_rcChatPopFrame.right-m_rcChatPopFrame.left, nLineCnt, szMsg, szDivied);

			sscanf(szDivied, "%[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c", szArg[0], szArg[1], szArg[2], szArg[3], szArg[4]);

			if ( nLineCnt > 5 )		nLineCnt = 5;

			for ( INT nCnt = 0; nCnt < nLineCnt; nCnt++ )
			{
				// 칸이 다음으로 갈조건.
				if ( m_xstrDividedChat.GetCounter() - m_nFstLine == _MAX_CHATLINE_POPUP )
				{
					m_nFstLine++;
				}

				CHAT	stChatStr;
				stChatStr.dwFontColor = dwFontColor;
				stChatStr.dwBackColor = dwFontBackColor;
				strcpy(stChatStr.pszChat, szArg[nCnt]);
				m_xstrDividedChat.AddNode(stChatStr);
			}

			// 최대저장라인 검사해서 그이상이면 삭제한다.
			while ( m_xstrDividedChat.GetCounter() >= _MAX_SAVECHATLINE )
			{
				m_xstrDividedChat.MoveCurrentToTop();
				m_xstrDividedChat.DeleteCurrentNode();

				if ( m_nFstLine > 0 )
					m_nFstLine--;
			}
		}
	}
	return TRUE;
}


VOID CChatPopWnd::ShowChatPopWnd()
{
	INT nCnt;
	ShowGameWnd();

	SetRect(&m_rcEditBoxFrame, 26, 311, 525, 326);

	if ( !m_xstrDividedChat.CheckEmpty() )
	{
		INT		nCnt, nShowLine;

		m_xstrDividedChat.MoveCurrentToTop();
		m_xstrDividedChat.MoveNode(m_nFstLine);

		nShowLine = ((m_xstrDividedChat.GetCounter() - m_nFstLine ) >= _MAX_CHATLINE_POPUP) ?  _MAX_CHATLINE_POPUP : m_xstrDividedChat.GetCounter() - m_nFstLine;
		
		for ( nCnt = 0; nCnt < nShowLine; nCnt++ )
		{
			LPCHAT pstChatString;

			pstChatString = m_xstrDividedChat.GetCurrentData();

			if ( pstChatString )
			{
				g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(),
								   m_rcWnd.left+m_rcChatPopFrame.left, m_rcWnd.top+m_rcChatPopFrame.top+nCnt*14,
								   pstChatString->dwFontColor, pstChatString->dwBackColor, pstChatString->pszChat);
			}

			m_xstrDividedChat.MoveNextNode();
		}
	}

	m_xChatPopBar.ShowScrlBar(m_rcWnd.left+533, m_rcWnd.top-208, m_nFstLine, m_xstrDividedChat.GetCounter());

	m_xChatPopBtn[_BTN_ID_CHATCLOSE].ChangeRect(m_rcWnd.left+532, m_rcWnd.top+350);
	m_xChatPopBtn[_BTN_ID_CHATDENY]. ChangeRect (m_rcWnd.left+ 25, m_rcWnd.top+332);
	m_xChatPopBtn[_BTN_ID_CHATSHOUT].ChangeRect(m_rcWnd.left+ 65, m_rcWnd.top+332);
	m_xChatPopBtn[_BTN_ID_CHATGROUP].ChangeRect(m_rcWnd.left+105, m_rcWnd.top+332);
	m_xChatPopBtn[_BTN_ID_CHATGUILD].ChangeRect(m_rcWnd.left+145, m_rcWnd.top+332);
	m_xChatPopBtn[_BTN_ID_CHATALLDENY].ChangeRect(m_rcWnd.left+185, m_rcWnd.top+332);
	m_xChatPopBtn[_BTN_ID_DENYGUILD].ChangeRect	   (m_rcWnd.left+225, m_rcWnd.top+332);
	m_xChatPopBtn[_BTN_ID_SCRLUP].ChangeRect   (m_rcWnd.left+539, m_rcWnd.top+ 25);
	m_xChatPopBtn[_BTN_ID_SCRLDOWN].ChangeRect (m_rcWnd.left+539, m_rcWnd.top+311);

	for ( nCnt = 0; nCnt < _MAX_CHATPOP_BTN; nCnt++ )
	{
		m_xChatPopBtn[nCnt].ShowGameBtn();
	}

	for ( nCnt = 0; nCnt < _MAX_CHATLINE_POPUP; nCnt++ )
	{
		SetRect(&m_rcChatPopLine[nCnt], m_rcWnd.left+35, m_rcWnd.top+(28+nCnt*14), m_rcWnd.left+520, m_rcWnd.top+(43+nCnt*14));
	}
}

BOOL CChatPopWnd::OnLButtonUp(POINT ptMouse)
{
	INT nCnt;

	MoveWindow(g_xChatEditBox.GetSafehWnd(), g_xMainWnd.m_rcWindow.left + m_rcWnd.left + m_rcEditBoxFrame.left, 
	 		   g_xMainWnd.m_rcWindow.top + m_rcWnd.top + m_rcEditBoxFrame.top, 
			   m_rcEditBoxFrame.right - m_rcEditBoxFrame.left, 
			   m_rcEditBoxFrame.bottom - m_rcEditBoxFrame.top, TRUE);

	if ( m_xChatPopBar.OnLButtonUp(ptMouse) )
	{
		return FALSE;
	}

	if ( m_xChatPopBtn[_BTN_ID_CHATCLOSE].OnLButtonUp(ptMouse) )		
	{
		return TRUE;
	}

	if ( m_xChatPopBtn[_BTN_ID_CHATDENY].OnLButtonUp(ptMouse) )		
	{
		SetFocus(g_xChatEditBox.GetSafehWnd());
		ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);
		SetWindowText(g_xChatEditBox.GetSafehWnd(), g_xMsg.GetMsg(1072));
		INT nLen = strlen(g_xMsg.GetMsg(1072));
		SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETSEL, nLen , nLen);
		g_xChatEditBox.SetHanguelMode();
		return FALSE;
	}
	if ( m_xChatPopBtn[_BTN_ID_CHATSHOUT].OnLButtonUp(ptMouse) )		
	{
		SetFocus(g_xChatEditBox.GetSafehWnd());
		ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);
		SetWindowText(g_xChatEditBox.GetSafehWnd(), "!");
		INT nLen = strlen("!");
		SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETSEL, nLen , nLen);
		g_xChatEditBox.SetHanguelMode();
		return FALSE;
	}
	if ( m_xChatPopBtn[_BTN_ID_CHATGROUP].OnLButtonUp(ptMouse) )		
	{
		SetFocus(g_xChatEditBox.GetSafehWnd());
		ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);
		SetWindowText(g_xChatEditBox.GetSafehWnd(), "!!");
		INT nLen = strlen("!!");
		SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETSEL, nLen , nLen);
		g_xChatEditBox.SetHanguelMode();
		return FALSE;
	}
	if ( m_xChatPopBtn[_BTN_ID_CHATGUILD].OnLButtonUp(ptMouse) )		
	{
		SetFocus(g_xChatEditBox.GetSafehWnd());
		ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);
		SetWindowText(g_xChatEditBox.GetSafehWnd(), "!~");
		INT nLen = strlen("!~");
		SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETSEL, nLen , nLen);
		g_xChatEditBox.SetHanguelMode();
		return FALSE;
	}
	if ( m_xChatPopBtn[_BTN_ID_CHATALLDENY].OnLButtonUp(ptMouse) )		
	{
		SetFocus(g_xChatEditBox.GetSafehWnd());
		ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);
		SetWindowText(g_xChatEditBox.GetSafehWnd(), g_xMsg.GetMsg(1070));
		INT nLen = strlen(g_xMsg.GetMsg(1070));
		SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETSEL, nLen , nLen);
		g_xChatEditBox.SetHanguelMode();
		return FALSE;
	}
	if ( m_xChatPopBtn[_BTN_ID_DENYGUILD].OnLButtonUp(ptMouse) )		
	{
		SetFocus(g_xChatEditBox.GetSafehWnd());
		ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);
		SetWindowText(g_xChatEditBox.GetSafehWnd(), g_xMsg.GetMsg(1071));
		INT nLen = strlen(g_xMsg.GetMsg(1071));
		SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETSEL, nLen , nLen);
		g_xChatEditBox.SetHanguelMode();
		return FALSE;
	}

	if ( m_xChatPopBtn[_BTN_ID_SCRLUP].OnLButtonUp(ptMouse) )		
	{
		return FALSE;
	}

	if ( m_xChatPopBtn[_BTN_ID_SCRLDOWN].OnLButtonUp(ptMouse) )		
	{
		return FALSE;
	}

	return FALSE;
}

BOOL CChatPopWnd::OnLButtonDown(POINT ptMouse)
{
	INT nCnt;

	if ( m_xChatPopBar.OnLButtonDown(ptMouse) )
	{
		FLOAT	fScrlRate;

		fScrlRate = m_xChatPopBar.GetScrlRate();
		m_nFstLine = (INT)((m_xstrDividedChat.GetCounter()-1)*fScrlRate);

		return TRUE;
	}

	for ( nCnt = 0; nCnt < _MAX_CHATPOP_BTN; nCnt++ )
	{
		if ( m_xChatPopBtn[nCnt].OnLButtonDown(ptMouse) )
		{
			return TRUE;
		}
	}

	if ( SetCaputeString(ptMouse) )
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CChatPopWnd::OnMouseMove(POINT ptMouse)
{
	INT nCnt;

	if ( m_xChatPopBar.OnMouseMove(ptMouse) )
	{
		FLOAT	fScrlRate;

		fScrlRate = m_xChatPopBar.GetScrlRate();
		m_nFstLine = (INT)((m_xstrDividedChat.GetCounter()-1)*fScrlRate);
		return TRUE;
	}

	for ( nCnt = 0; nCnt < _MAX_CHATPOP_BTN; nCnt++ )
	{
		m_xChatPopBtn[nCnt].OnMouseMove(ptMouse);
	}

	return FALSE;
}

VOID CChatPopWnd::OnScrollDown()
{
	if ( m_nFstLine > 0 )														
	{
		m_nFstLine--;
	}
}

VOID CChatPopWnd::OnScrollUp()
{
	if ( m_nFstLine < m_xstrDividedChat.GetCounter()-1 )	
	{
		m_nFstLine++;
	}
}

VOID CChatPopWnd::SetStatusBtnInit()
{
	INT nCnt;

	for ( nCnt = 0; nCnt < _MAX_CHATPOP_BTN; nCnt++ )
	{
		m_xChatPopBtn[nCnt].SetBtnState(_BTN_STATE_NORMAL);
	}
}


BOOL CChatPopWnd::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	switch ( wParam )
	{
		case 0XBF:			// /
		{
			SetFocus(g_xChatEditBox.GetSafehWnd());
			ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);
			if ( m_pszLastChatPopCapture[0] == '\0' )
			{
				strcpy(m_pszLastChatPopCapture, "/");
			}
			SetWindowText(g_xChatEditBox.GetSafehWnd(), m_pszLastChatPopCapture);
			INT nLen = strlen(m_pszLastChatPopCapture);
			SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETSEL, nLen , nLen);
			g_xChatEditBox.SetHanguelMode();
			return TRUE;
		}
		case 0X31:			// !
		{			
			if ( HIBYTE(GetKeyState(VK_SHIFT)) )
			{
				SetFocus(g_xChatEditBox.GetSafehWnd());
				ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);
				SetWindowText(g_xChatEditBox.GetSafehWnd(), "!");
				INT nLen = strlen("!");
				SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETSEL, nLen , nLen);
				g_xChatEditBox.SetHanguelMode();
				return TRUE;
			}
		}
		case 0X32:			// @
		{			
			if ( HIBYTE(GetKeyState(VK_SHIFT)) )
			{
				SetFocus(g_xChatEditBox.GetSafehWnd());
				ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);
				SetWindowText(g_xChatEditBox.GetSafehWnd(), "@");
				INT nLen = strlen("@");
				SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETSEL, nLen , nLen);
				g_xChatEditBox.SetHanguelMode();
				return TRUE;
			}
		}
	}
		
	return FALSE;
}

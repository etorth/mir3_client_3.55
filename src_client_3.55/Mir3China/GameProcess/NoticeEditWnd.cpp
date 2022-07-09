/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"


CNoticEditWnd::CNoticEditWnd()
{
	Init();
}

CNoticEditWnd::~CNoticEditWnd()
{
	Destroy();
}

VOID CNoticEditWnd::Init()
{
	INT nCnt;

	CGameWnd::Init();

	m_hNoticeEdit = NULL;

	ZeroMemory(&m_rcEditBox, sizeof(RECT));

	m_bType = 0;

	for ( nCnt = 0; nCnt < _MAX_NOTICE_BTN; nCnt++ )
	{
		m_xNoticeBtn[nCnt].Init();
	}
}

VOID CNoticEditWnd::Destroy()
{
	CGameWnd::Destroy();

	if ( m_hNoticeEdit )
	{
		DestroyWindow(m_hNoticeEdit);
		m_hNoticeEdit = NULL;
	}
}

VOID CNoticEditWnd::CreateNoticeWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend)
{
	CreateGameWnd(nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight, bBlend);

	m_xNoticeBtn[_BTN_ID_NOTICECLOSE].CreateGameBtn	(pxWndImage, 1221, 1222, nStartX+546, nStartY+212, "", _BTN_TYPE_FOCUS, 1221, FALSE);
	m_xNoticeBtn[_BTN_ID_ACCEPET].CreateGameBtn	   (pxWndImage, 285, 286, nStartX+464, nStartY+17, "", _BTN_TYPE_FOCUS, -1, FALSE);

	// 에디트박스관련.
	SetRect(&m_rcEditBox, m_rcWnd.left+46, m_rcWnd.top+64, m_rcWnd.left+514, m_rcWnd.top+234);

	m_hNoticeEdit = CreateWindowEx(NULL, _T("EDIT"), "", WS_POPUP | ES_LEFT | ES_AUTOVSCROLL | ES_MULTILINE,
								   g_xMainWnd.m_rcWindow.left + m_rcEditBox.left, 
								   g_xMainWnd.m_rcWindow.top + m_rcEditBox.top, 
								   m_rcEditBox.right - m_rcEditBox.left, 
								   m_rcEditBox.bottom - m_rcEditBox.top, 
								   g_xMainWnd.GetSafehWnd(), NULL, g_xMainWnd.GetSafehInstance(), NULL);

	if ( m_hNoticeEdit )
	{
		UpdateWindow(m_hNoticeEdit);
		ShowWindow(m_hNoticeEdit, SW_HIDE);
		SendMessage(m_hNoticeEdit, EM_LIMITTEXT, (WPARAM)4000, 0);

		SendMessage(m_hNoticeEdit, WM_SETFONT, (WPARAM)g_xChatEditBox.m_hFontChatEdit, MAKELPARAM(TRUE, 0));
	}
}


VOID CNoticEditWnd::ShowNoticeWnd()
{
	INT nCnt;

	ShowGameWnd();

	RECT rcHint;

	if ( m_bType == 0 )
	{
		g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(), m_rcWnd.left+92, m_rcWnd.top+22, RGB(255, 200, 150), RGB(0, 0, 0), 
						   g_xMsg.GetMsg(1900), g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 12, 0, FW_NORMAL));
		g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(), m_rcWnd.left+250, m_rcWnd.top+16, RGB(50, 50, 50), RGB(0, 0, 0), 
						   g_xMsg.GetMsg(1901));
		g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(), m_rcWnd.left+250, m_rcWnd.top+17, RGB(255, 200, 150), RGB(0, 0, 0), 
						   g_xMsg.GetMsg(1901));
		g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(), m_rcWnd.left+251, m_rcWnd.top+30, RGB(50, 50, 50), RGB(0, 0, 0), 
						   g_xMsg.GetMsg(1902));
		g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(), m_rcWnd.left+251, m_rcWnd.top+31, RGB(255, 200, 150), RGB(0, 0, 0), 
						   g_xMsg.GetMsg(1902));
	}
	else 
	{
		g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(), m_rcWnd.left+92, m_rcWnd.top+22, RGB(255, 200, 150), RGB(0, 0, 0), 
						   g_xMsg.GetMsg(1903), g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 12, 0, FW_NORMAL));
		g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(), m_rcWnd.left+250, m_rcWnd.top+21, RGB(50, 50, 50), RGB(0, 0, 0), 
						   g_xMsg.GetMsg(1904));
		g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(), m_rcWnd.left+251, m_rcWnd.top+22, RGB(255, 200, 150), RGB(0, 0, 0), 
						   g_xMsg.GetMsg(1904));
	}

	m_xNoticeBtn[_BTN_ID_NOTICECLOSE].ChangeRect(m_rcWnd.left+547, m_rcWnd.top+213);
	m_xNoticeBtn[_BTN_ID_ACCEPET].ChangeRect	(m_rcWnd.left+500, m_rcWnd.top+19);

	for ( nCnt = 0; nCnt < _MAX_NOTICE_BTN; nCnt++ )
	{
		m_xNoticeBtn[nCnt].ShowGameBtn();
	}
}

BOOL CNoticEditWnd::OnLButtonUp(POINT ptMouse)
{
	INT nCnt;

	if ( m_xNoticeBtn[_BTN_ID_NOTICECLOSE].OnLButtonUp(ptMouse) )		
		return TRUE;

	if ( m_xNoticeBtn[_BTN_ID_ACCEPET].OnLButtonUp(ptMouse) )
	{
		if ( m_hNoticeEdit )
		{
			INT nLen	  = 0;
			TCHAR  pszEditMessage[4000];
			TCHAR  pszMessage[4000];

			ZeroMemory(pszEditMessage, 4000);
			ZeroMemory(pszMessage, 4000);

			TCHAR* pszCheck = NULL;
			TCHAR* pszNextCheck = NULL;

			GetWindowText(m_hNoticeEdit, pszEditMessage, 4000);

			pszCheck = pszEditMessage;

			if ( strstr(pszCheck, "*") != NULL )
			{
				g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GUILD, _OK, g_xMsg.GetMsg(4020));
				return TRUE;
			}

			while ( pszNextCheck = strchr(pszCheck, '\n') )
			{			
				*pszNextCheck = '\0';

				if ( *pszCheck == '\r' )
				{
					g_xMainWnd.StringPlus(&pszMessage[nLen], " \r", "");
					nLen += 2;
				}
				else
				{
					g_xMainWnd.StringPlus(&pszMessage[nLen], pszCheck, "");
					nLen += pszNextCheck - pszCheck;
				}

				pszNextCheck++;
				pszCheck = pszNextCheck;
			}

			if ( pszCheck[0] )
			{
				g_xMainWnd.StringPlus(&pszMessage[nLen], pszCheck, "");
			}

			if ( pszMessage[0] )
			{
				if ( m_bType == 0 )
				{
					g_xClientSocket.SendGuildUpdateGrade(pszMessage);
				}
				else 
				{
					g_xClientSocket.SendGuildUpdateNotice(pszMessage);
				}
			}
		}

		return TRUE;
	}

	return FALSE;
}

BOOL CNoticEditWnd::OnLButtonDown(POINT ptMouse)
{
	INT nCnt;

	for ( nCnt = 0; nCnt < _MAX_NOTICE_BTN; nCnt++ )
	{
		if ( m_xNoticeBtn[nCnt].OnLButtonDown(ptMouse) )
		{
			return TRUE;
		}
	}

	return FALSE;
}

VOID CNoticEditWnd::OnMouseMove(POINT ptMouse)
{
	INT nCnt;

	for ( nCnt = 0; nCnt < _MAX_NOTICE_BTN; nCnt++ )
	{
		m_xNoticeBtn[nCnt].OnMouseMove(ptMouse);
	}
}

VOID CNoticEditWnd::SetStatusBtnInit()
{
	INT nCnt;

	for ( nCnt = 0; nCnt < _MAX_NOTICE_BTN; nCnt++ )
	{
		m_xNoticeBtn[nCnt].SetBtnState(_BTN_STATE_NORMAL);
	}
}
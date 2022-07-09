/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"

static CChatEdit*	g_xChatEdit = NULL;

//#define WM_KEYCRYPTION_EDIT_ASTERISK_NOTIFY WM_USER+2002				// KeyCrypt관련

/******************************************************************************************************************

	CChatEdit Functions

*******************************************************************************************************************/


/******************************************************************************************************************

	함수명 : CChatEdit::CChatEdit()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
CChatEdit::CChatEdit()
{
	m_hChatEdit = NULL;
	g_xChatEdit	= this;
	m_hFontChatEdit = NULL;
	m_bSetEnterUse = TRUE;
	m_bUsePassMode = FALSE;

	m_dwFontColor = RGB(255, 0, 255);
	ZeroMemory(m_szInputMsg, MAX_PATH);
}



/******************************************************************************************************************

	함수명 : CChatEdit::~CChatEdit()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
CChatEdit::~CChatEdit()
{
	DestroyDialog();
}



/******************************************************************************************************************

	함수명 : CChatEdit::DestroyDialog()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CChatEdit::DestroyDialog()
{
	if ( m_hFontChatEdit != NULL )
	{
		DeleteObject(m_hFontChatEdit);
		m_hFontChatEdit = NULL;
	}

	DestroyWindow(m_hChatEdit);

	return TRUE;
}



/******************************************************************************************************************

	함수명 : ChatEditDlgProc()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : HWND hWnd
	         UINT uMsg
	         WPARAM wParam
	         LPARAM lParam
	출력   : INT_PTR CALLBACK 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
INT_PTR CALLBACK ChatEditDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return g_xChatEdit->ChatEditProc(hWnd, uMsg, wParam, lParam);
}


void CChatEdit::SetHanguelMode()
{
	HIMC hIMC = ImmGetContext(m_hChatEdit);

	ImmSetConversionStatus(hIMC, IME_CMODE_NATIVE, IME_SMODE_CONVERSATION);
	ImmReleaseContext(m_hChatEdit, hIMC); 
}


void CChatEdit::SetAlphaNumericMode()
{
	HIMC hIMC = ImmGetContext(m_hChatEdit);

	ImmSetConversionStatus(hIMC, IME_CMODE_ALPHANUMERIC, IME_SMODE_CONVERSATION);
	ImmReleaseContext(m_hChatEdit, hIMC); 

}

/******************************************************************************************************************

	함수명 : CChatEdit::ChatEditProc()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : HWND hWnd
	         UINT nMsg
	         WPARAM wParam
	         LPARAM lParam
	출력   : LRESULT CALLBACK 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
LRESULT CALLBACK CChatEdit::ChatEditProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT		ps;

	switch (nMsg)
	{
/*		case WM_KEYCRYPTION_EDIT_ASTERISK_NOTIFY:
		{
			UCHAR tmp[33] = {0,};
			MyGetCryptData(tmp);

			nMsg = WM_CHAR;
			wParam = (WPARAM) *tmp;
			break;
		}
*/		case WM_SYSKEYDOWN:
		{
			if ( wParam == VK_F4 )
			{
				HWND m_hMainWindow = g_xMainWnd.GetSafehWnd();
				SendMessage(m_hMainWindow, WM_HOTKEY, (INT)0, 1);
				return 0L;
			}			
		}
		case WM_KEYDOWN:
		{
			if ( m_bSetEnterUse == TRUE )
			{
				switch ( (INT)wParam )
				{
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
					{
						if ( GetKeyState(VK_CONTROL) & 0x80 )
						{
							SendMessage(g_xMainWnd.GetSafehWnd(), _WM_USER_MSG_CTRLNUM, (INT)(wParam-49), NULL);
						}
						else if ( GetKeyState(VK_MENU) & 0x80 )
						{
							SendMessage(g_xMainWnd.GetSafehWnd(), _WM_USER_MSG_ALTNUM, (INT)(wParam-49), NULL);
						}						
						break;
					}
					case '0':
					{
						if ( GetKeyState(VK_CONTROL) & 0x80 )
						{
							SendMessage(g_xMainWnd.GetSafehWnd(), _WM_USER_MSG_CTRLNUM, 9, NULL);
						}
						else if ( GetKeyState(VK_MENU) & 0x80 )
						{
							SendMessage(g_xMainWnd.GetSafehWnd(), _WM_USER_MSG_ALTNUM, 9, NULL);
						}						
						break;
					}
					case VK_F1:
					case VK_F2:
					case VK_F3:
					case VK_F4:
					case VK_F5:
					case VK_F6:
					case VK_F7:
					case VK_F8:
					case VK_F9:
					case VK_F10:
					case VK_F11:
					case VK_F12:
					case VK_ESCAPE:
					case VK_UP:
					case VK_DOWN:
						{
							HWND m_hMainWindow = g_xMainWnd.GetSafehWnd();
	//						SetFocus(m_hMainWindow);
							SendMessage(m_hMainWindow, WM_KEYDOWN, (INT)wParam, lParam);
							return 0L;
						}
					case 'Q':	
					case 'W':	
					case 'E':
					{
						if ( GetKeyState(VK_CONTROL) & 0x80 )
						{
							HWND m_hMainWindow = g_xMainWnd.GetSafehWnd();
	//						SetFocus(m_hMainWindow);
							SendMessage(m_hMainWindow, WM_KEYDOWN, (INT)wParam, lParam);
							return 0L;
						}

						break;
					}
				}
			}
			break;
		}
		case WM_CHAR:
		{
			if ( g_xGameProc.m_bDiceModeActive )
			{
				return 0L;
			}

			switch ( (INT)wParam )
			{
				case VK_RETURN:
				{
					if ( m_bSetEnterUse )
					{
						SetAlphaNumericMode();

						GetWindowText(hWnd, m_szInputMsg, MAX_PATH);
						SetWindowText(hWnd, "");
						HWND m_hMainWindow = g_xMainWnd.GetSafehWnd();
						SetFocus(m_hMainWindow);
						ShowWindow(m_hChatEdit, SW_HIDE);

						if ( m_szInputMsg )
						{
							if (m_bUsePassMode == TRUE)
							{
								SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETPASSWORDCHAR, NULL, 0);
								m_bUsePassMode = FALSE;
							}

							if ( m_szInputMsg[0] == '@' )
							{
								SendMessage(m_hMainWindow, _WM_USER_MSG_INPUTTED, TRUE, NULL);
							}
							else
							{
								SendMessage(m_hMainWindow, _WM_USER_MSG_INPUTTED, NULL, NULL);
							}
							return 0L;
						}
					}
					else
					{
//						if ( g_xGameProc.m_xGameMsgBox.IsActive() )
						{
							SendMessage(g_xMainWnd.GetSafehWnd(), WM_KEYDOWN, wParam, lParam);
							return 0L;
						}
					}
					break;
				}
				case VK_TAB:
				{
					HWND m_hMainWindow = g_xMainWnd.GetSafehWnd();
					SetFocus(m_hMainWindow);
					SendMessage(m_hMainWindow, WM_KEYDOWN, (INT)wParam, lParam);
					return 0L;
				}
			}
			break;
		}
		case WM_PAINT:
		{
			BeginPaint(m_hChatEdit, &ps);
			InvalidateRect(hWnd, NULL, FALSE);
			EndPaint(m_hChatEdit, &ps);
			break;
		}
/*		case WM_MOVE:
		{
			RECT rc;
			GetWindowRect(m_hChatEdit, &rc);
			ScreenToClient(g_xMainWnd.GetSafehWnd(), (POINT*)&rc);
			ScreenToClient(g_xMainWnd.GetSafehWnd(), (POINT*)&rc+1);

			MoveWindow(m_hChatEdit, g_xMainWnd.m_rcWindow.left+rc.left, g_xMainWnd.m_rcWindow.top+rc.top, 
					  rc.right-rc.left, rc.bottom-rc.top, FALSE);
			break;
		}
*/		default:
			break;
	}
	return CallWindowProc(m_WndProcChatEdit, hWnd, nMsg, wParam, lParam);
}



/******************************************************************************************************************

	함수명 : CChatEdit::Create()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : HINSTANCE hInstance
	         HWND hWndParent
	         INT nX
	         INT nY
	         INT nXsize
	         INT nYSize
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CChatEdit::Create(HINSTANCE hInstance, HWND hWndParent, INT nX, INT nY, INT nXsize, INT nYSize)
{
	m_hChatEdit = CreateWindowEx(NULL, _T("EDIT"), "", WS_POPUP | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL/* | ES_MULTILINE*/,
								 nX, nY, nXsize, nYSize,
								 hWndParent, NULL, hInstance, NULL);	  
	m_WndProcChatEdit = (WNDPROC)SetWindowLong(m_hChatEdit, GWL_WNDPROC, (LONG)ChatEditDlgProc);
	ShowWindow(m_hChatEdit, SW_HIDE);

	// 이미 폰트가 생성되어 있으면 새로 만들수 있도록 Clear
	if ( m_hFontChatEdit != NULL )
	{
		DeleteObject(m_hFontChatEdit); 
		m_hFontChatEdit = NULL; 
	}

	if ( g_xMainWnd.m_pszDefFont[0] != '\0' )
	{
		m_hFontChatEdit = CreateFont(-12, 0, 0, 0, FW_NORMAL, 0, 0, 0, HANGUL_CHARSET, 
									 OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
									 DEFAULT_QUALITY, DEFAULT_PITCH, g_xMainWnd.m_pszDefFont);
	}
	else
	{
		m_hFontChatEdit = CreateFont(-12, 0, 0, 0, FW_NORMAL, 0, 0, 0, HANGUL_CHARSET, 
									 OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
									 DEFAULT_QUALITY, DEFAULT_PITCH, g_xMsg.GetMsg(1074));
	}


	SendMessage(m_hChatEdit, WM_SETFONT, (WPARAM)m_hFontChatEdit, MAKELPARAM(TRUE, 0));

	// 입력에디트윈도우의 최대입력문자 갯수 정의.
	SendMessage(m_hChatEdit, EM_LIMITTEXT, (WPARAM)90, 0);

    UpdateWindow(m_hChatEdit);
	return TRUE;
}



BOOL CChatEdit::SetLimitText(INT nLimitText)
{
	if ( m_hChatEdit )
	{
		SendMessage(m_hChatEdit, EM_LIMITTEXT, (WPARAM)nLimitText, 0);
		return TRUE;
	}
	return FALSE;
}
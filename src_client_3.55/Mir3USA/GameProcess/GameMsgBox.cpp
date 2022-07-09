/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"


/******************************************************************************************************************

	CGameMsgBox Class

*******************************************************************************************************************/

CGameMsgBox::CGameMsgBox()
{
	InitMsgBox();
}

CGameMsgBox::~CGameMsgBox()
{
	ReleaseMsgBox();
}

VOID CGameMsgBox::InitMsgBox()
{
	m_bActive = FALSE;

	SetRect(&m_rcMsg, 0, 0, 0, 0);
	SetRect(&m_rcStr, 0, 0, 0, 0);

	ZeroMemory(m_pszMsg, sizeof(MAX_PATH));
	ZeroMemory(m_pszEditMsg, sizeof(MAX_PATH));	

	for ( INT nCnt = 0; nCnt < _MAX_MSGBTN; nCnt++ )
	{
		m_stBtn[nCnt].bActive = FALSE;
		m_stBtn[nCnt].xGameBtn.Init();
	}

	m_wPacketNum = 0XFFFF;

	m_bFocusBtn	 = _BTN_YES;

	m_temp.x = 24;
	m_temp.y = 50;
}

VOID CGameMsgBox::ReleaseMsgBox()
{
	InitMsgBox();
}

VOID CGameMsgBox::CreateMsgBox(CWHWilImageData* pxMsgBoxImage, INT nWndID, INT nType, CHAR* pszStr, BOOL bUseInput, INT nXPos, INT nYPos, WORD wIdent, BOOL bSecret, INT nMaxChar)
{
	InitMsgBox();

//---------------------------------------------------------------------------------------------------------------//
// 메시지박스에 쓰일 이미지및 고정.
	m_pxMsgBoxImage	= pxMsgBoxImage;
	if ( nType == _NONE )
		m_nBoxImgIdx	= 663;
	else
		m_nBoxImgIdx	= 420;
//---------------------------------------------------------------------------------------------------------------//

	if ( m_pxMsgBoxImage->NewSetIndex(m_nBoxImgIdx) )
	{
		INT nSX, nSY;

		m_nGameWndID = nWndID;
		strcpy(m_pszMsg, pszStr);

		//---------------------------------------------------------------------------------------------------------------//
		// 메시지박스영역 설정.
		//---------------------------------------------------------------------------------------------------------------//
		if ( nXPos == -1 && nYPos == -1 )
		{
			nSX = _SCREEN_X/2 - m_pxMsgBoxImage->m_lpstNewCurrWilImageInfo->shWidth /2;
			nSY = _SCREEN_Y/2 - m_pxMsgBoxImage->m_lpstNewCurrWilImageInfo->shHeight/2;
		}
		else
		{
			nSX = nXPos;
			nSY = nYPos;
		}
		SetRect(&m_rcMsg, nSX, nSY, nSX + m_pxMsgBoxImage->m_lpstNewCurrWilImageInfo->shWidth, nSY + m_pxMsgBoxImage->m_lpstNewCurrWilImageInfo->shHeight);

		//---------------------------------------------------------------------------------------------------------------//
		// 버튼 설정.
		//---------------------------------------------------------------------------------------------------------------//
		switch ( nType )
		{
		case _OK:
			m_stBtn[_BTN_YES].bActive = FALSE;
			m_stBtn[_BTN_OK ].bActive = TRUE;
			m_stBtn[_BTN_NO ].bActive = FALSE;
			m_bFocusBtn	 = _BTN_OK;
			break;
		case _YESNO:
			m_stBtn[_BTN_YES].bActive = TRUE;
			m_stBtn[_BTN_OK ].bActive = FALSE;
			m_stBtn[_BTN_NO ].bActive = TRUE;
			m_bFocusBtn	 = _BTN_YES;
			break;
		case _NONE:
			m_stBtn[_BTN_YES].bActive = FALSE;
			m_stBtn[_BTN_OK ].bActive = FALSE;
			m_stBtn[_BTN_NO ].bActive = FALSE;
			break;
		}

		m_stBtn[_BTN_YES].xGameBtn.CreateGameBtn(m_pxMsgBoxImage, 421, 422, m_rcMsg.left+ _NEW_BTN_YES_X, m_rcMsg.top+ _NEW_BTN_YES_Y, NULL, _BTN_TYPE_FOCUS, 421);
		m_stBtn[_BTN_OK ].xGameBtn.CreateGameBtn(m_pxMsgBoxImage, 423, 424, m_rcMsg.left+ _NEW_BTN_OK_X, m_rcMsg.top+ _NEW_BTN_OK_Y, NULL, _BTN_TYPE_FOCUS, 423);
		m_stBtn[_BTN_NO ].xGameBtn.CreateGameBtn(m_pxMsgBoxImage, 425, 426, m_rcMsg.left+ _NEW_BTN_NO_X, m_rcMsg.top+ _NEW_BTN_NO_Y, NULL, _BTN_TYPE_FOCUS, 425);

		//---------------------------------------------------------------------------------------------------------------//
		// 텍스트가 찍힐영역설정.
		//---------------------------------------------------------------------------------------------------------------//

		if ( bUseInput ) 
		{
			SetRect(&m_rcStr, m_rcMsg.left+_NEW_STR_SX+20, m_rcMsg.top+_NEW_STR_SY, m_rcMsg.left+_NEW_STR_EX-10, m_rcMsg.top+_NEW_STR_EY-20);

			//------------------------------------------------------------------------------------------------------------
			// 채팅에디트 윈도우 위치지정.
			MoveWindow(g_xChatEditBox.GetSafehWnd(), 
					   g_xMainWnd.m_rcWindow.left+m_rcMsg.left+24, g_xMainWnd.m_rcWindow.top+m_rcMsg.top+181,
					   260, 15, TRUE);
			//------------------------------------------------------------------------------------------------------------
			if ( bSecret )
				SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETPASSWORDCHAR, (WPARAM)'*', 0);
			else
				SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETPASSWORDCHAR, NULL, 0);

			SetWindowText(g_xChatEditBox.GetSafehWnd(), "");
			SetFocus(g_xChatEditBox.GetSafehWnd());
			ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);

			if ( nMaxChar == 0 )
				g_xChatEditBox.SetLimitText(90);
			else
				g_xChatEditBox.SetLimitText(nMaxChar);

			g_xChatEditBox.SetEnterUse(FALSE);
		}
		else
		{
			if (nType == _NONE)
				SetRect(&m_rcStr, m_rcMsg.left+_NEW_STR_SX_SMALL, m_rcMsg.top+_NEW_STR_SY_SMALL, m_rcMsg.left+_NEW_STR_EX_SMALL, m_rcMsg.top+_NEW_STR_EY_SMALL);
			else
				SetRect(&m_rcStr, m_rcMsg.left+_NEW_STR_SX, m_rcMsg.top+_NEW_STR_SY, m_rcMsg.left+_NEW_STR_EX, m_rcMsg.top+_NEW_STR_EY);
		}

		m_bActive = TRUE;
		m_wPacketNum = wIdent;
	}
}


BOOL CGameMsgBox::RenderMsgBox(POINT ptMouse)
{
	if( m_bActive )
	{
		INT nCnt;
//---------------------------------------------------------------------------------------------------------------//
// 메시지박스 프레임.
//---------------------------------------------------------------------------------------------------------------//
		if ( m_pxMsgBoxImage->NewSetIndex(m_nBoxImgIdx) )
		{
 			g_xMainWnd.DrawWithImageForCompClipRgn(m_rcMsg.left, m_rcMsg.top, m_pxMsgBoxImage->m_lpstNewCurrWilImageInfo->shWidth, m_pxMsgBoxImage->m_lpstNewCurrWilImageInfo->shHeight,
												   (WORD*)m_pxMsgBoxImage->m_pbCurrImage, _CLIP_WIDTH, 600);
		}
//---------------------------------------------------------------------------------------------------------------//
// 텍스트.
//---------------------------------------------------------------------------------------------------------------//
		g_xMainWnd.PutsHanEx(NULL, m_rcStr, RGB(255, 250, 200), RGB(0, 0, 0), m_pszMsg);

//---------------------------------------------------------------------------------------------------------------//
// 버튼.
//---------------------------------------------------------------------------------------------------------------//
		for ( nCnt = 0; nCnt < _MAX_MSGBTN; nCnt++ )
		{
			if ( m_stBtn[nCnt].bActive )
			{
				if ( !PtInRect(&m_stBtn[nCnt].xGameBtn.m_rcBtn, ptMouse) )
				{
					m_stBtn[nCnt].xGameBtn.SetBtnState(_BTN_STATE_NORMAL);
				}

				m_stBtn[nCnt].xGameBtn.ShowGameBtn();

				// 포커스 버튼찍기.
				if ( nCnt == m_bFocusBtn && m_stBtn[nCnt].xGameBtn.m_bBtnState != _BTN_STATE_CLICK )
				{
/*					RECT rc = {m_stBtn[nCnt].xGameBtn.m_rcBtn.left, m_stBtn[nCnt].xGameBtn.m_rcBtn.top,
						       m_stBtn[nCnt].xGameBtn.m_rcBtn.right-2 , m_stBtn[nCnt].xGameBtn.m_rcBtn.bottom-2};
					D3DMATERIAL7 mtrl;
					D3DVECTOR	vecTrans(rc.left, rc.top, 0);
					D3DVECTOR	vecScale(rc.right-rc.left, 
						                 rc.bottom-rc.top, 1);

					D3DUtil_InitMaterial(mtrl, (FLOAT)95/255.0f, (FLOAT)95/255.0f, (FLOAT)95/255.0f);
					mtrl.diffuse.a = 125.0f/255.0f;
					g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
*/
					if ( m_pxMsgBoxImage->NewSetIndex(m_stBtn[nCnt].xGameBtn.m_nFocusImgIdx) )
					{
 						g_xMainWnd.DrawWithImageForCompClipRgn(m_stBtn[nCnt].xGameBtn.m_rcBtn.left, m_stBtn[nCnt].xGameBtn.m_rcBtn.top, m_pxMsgBoxImage->m_lpstNewCurrWilImageInfo->shWidth, m_pxMsgBoxImage->m_lpstNewCurrWilImageInfo->shHeight,
															   (WORD*)m_pxMsgBoxImage->m_pbCurrImage, _CLIP_WIDTH, 600);
					}
				}
			}
		}

		return TRUE;
	}
	return FALSE;
}

BOOL CGameMsgBox::OnLButtonDown(POINT ptMouse)
{
	if( m_bActive )
	{
		INT nCnt;
		for ( nCnt = 0; nCnt < _MAX_MSGBTN; nCnt++ )
		{
			if ( m_stBtn[nCnt].bActive )
			{				
				if ( m_stBtn[nCnt].xGameBtn.OnLButtonDown(ptMouse) )
				{
					m_bFocusBtn = (BYTE)nCnt;
				}
			}
		}		
		return TRUE;
	}
	return FALSE;
}


BOOL CGameMsgBox::OnRButtonDown(POINT ptMouse)
{
	if( m_bActive )
	{
		return TRUE;
	}
	return FALSE;
}



BOOL CGameMsgBox::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	INT nCnt;

	if( m_bActive )
	{
		switch ( wParam )
		{
			case VK_TAB:
			{
				for ( nCnt = 0; nCnt < _MAX_MSGBTN; )
				{
					m_bFocusBtn++;

					if ( m_bFocusBtn >= _MAX_MSGBTN )
					{
						m_bFocusBtn = 0;
					}

					if ( m_stBtn[m_bFocusBtn].bActive )
					{
						return TRUE;						
					}
					else
					{
						nCnt++;
					}
				}

				// 확인코드이다.
				if ( !m_stBtn[m_bFocusBtn].bActive )
				{
					for ( nCnt = 0; nCnt < _MAX_MSGBTN; nCnt++ )
					{
						if ( m_stBtn[nCnt].bActive )
						{
							m_bFocusBtn = (BYTE)nCnt;
							break;
						}
					}
				}
			}
			case VK_RETURN:
			case VK_SPACE:
			{
				if ( m_stBtn[m_bFocusBtn].bActive )
				{
					WORD  wComplex = MAKEWORD((BYTE)m_bFocusBtn, (BYTE)m_nGameWndID);
					WPARAM wParam = MAKEWPARAM((WORD)m_wPacketNum, wComplex);

					MoveWindow(g_xChatEditBox.GetSafehWnd(), 
							   g_xMainWnd.m_rcWindow.left+_NEW_INPUT_EDITWND_XPOS, g_xMainWnd.m_rcWindow.top+_NEW_INPUT_EDITWND_YPOS,
							   _NEW_INPUT_EDITWND_WIDTH, _NEW_INPUT_EDITWND_HEIGHT, TRUE);
					ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_HIDE);

					GetWindowText(g_xChatEditBox.GetSafehWnd(), m_pszEditMsg, MAX_PATH);
					SetWindowText(g_xChatEditBox.GetSafehWnd(), "");
					SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETPASSWORDCHAR, NULL, 0);

					g_xChatEditBox.SetEnterUse(TRUE);

					SendMessage(g_xMainWnd.GetSafehWnd(), _WM_MSGBOX_RETURN, wParam, (LPARAM)m_pszEditMsg);
					InitMsgBox();
				}
			}
		}
		return TRUE;
	}

	return FALSE;
}



BOOL CGameMsgBox::OnLButtonUp(POINT ptMouse)
{
	if( m_bActive )
	{
		INT nCnt;
		for ( nCnt = 0; nCnt < _MAX_MSGBTN; nCnt++ )
		{
			if ( m_stBtn[nCnt].bActive )
			{
				if ( m_stBtn[nCnt].xGameBtn.OnLButtonUp(ptMouse) )
				{
					m_bFocusBtn	 = (BYTE)nCnt;

					WORD  wComplex = MAKEWORD((BYTE)nCnt, (BYTE)m_nGameWndID);
					WPARAM wParam = MAKEWPARAM((WORD)m_wPacketNum, wComplex);

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

					ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_HIDE);

					GetWindowText(g_xChatEditBox.GetSafehWnd(), m_pszEditMsg, MAX_PATH);
					SetWindowText(g_xChatEditBox.GetSafehWnd(), "");
					SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETPASSWORDCHAR, NULL, 0);

					g_xChatEditBox.SetEnterUse(TRUE);

					SendMessage(g_xMainWnd.GetSafehWnd(), _WM_MSGBOX_RETURN, wParam, (LPARAM)m_pszEditMsg);
					InitMsgBox();
				}
			}
		}		
		return TRUE;
	}
	return FALSE;
}

VOID CGameMsgBox::OnMouseMove(POINT ptMouse)
{
	if( m_bActive )
	{
		m_stBtn[_BTN_YES].xGameBtn.ChangeRect(m_rcMsg.left+_NEW_BTN_YES_X, m_rcMsg.top+ _NEW_BTN_YES_Y);
		m_stBtn[_BTN_YES].xGameBtn.OnMouseMove(ptMouse);
		m_stBtn[_BTN_OK].xGameBtn.ChangeRect(m_rcMsg.left+ _NEW_BTN_OK_X, m_rcMsg.top+  _NEW_BTN_OK_Y);
		m_stBtn[_BTN_OK].xGameBtn.OnMouseMove(ptMouse);
		m_stBtn[_BTN_NO].xGameBtn.ChangeRect(m_rcMsg.left+ _NEW_BTN_NO_X, m_rcMsg.top+  _NEW_BTN_NO_Y);
		m_stBtn[_BTN_NO].xGameBtn.OnMouseMove(ptMouse);
	}
}



#include "stdafx.h"

#define WRITESTRLENTH 50
#define MAX_NOTICESTR_WIDTH	324
#define MAX_NOTICESHOW_LINE 20

/*#define BTN_POS_X	165
#define BTN_POS_Y	483
*/
#define BTN_POS_X	135
#define BTN_POS_Y	400

#define _NEW_BTN_POS_X	131
#define _NEW_BTN_POS_Y	429

#define _IDX_UP_BTN_IMG			1
#define _IDX_ON_BTN_IMG			2
#define _IDX_DOWN_BTN_IMG		3

#define _NEW_IDX_ON_BTN_IMG		1251
#define _NEW_IDX_DOWN_BTN_IMG	1252

CNoticeBox::CNoticeBox()
{
	m_bActive = FALSE;
	m_bInited = FALSE;
	m_bIsSelected = FALSE;
	m_bSet = FALSE;

	ZeroMemory(&m_rcWnd,sizeof(RECT));
}

BOOL CNoticeBox::Load(CWHWilImageData* pxBtnImage=NULL)
{
	if(pxBtnImage!=NULL)
	{
		// Init Button;
		m_bSet			=	TRUE;
		m_pxBtnImage	=	pxBtnImage;

		m_xMsgBtn.CreateGameBtn(pxBtnImage, 661, 662, _NEW_BTN_POS_X,_NEW_BTN_POS_Y);
	}
	else
	{
		m_bSet = FALSE;
	}
	return m_bSet;
}

BOOL CNoticeBox::DestoryMessageBox(VOID)						// DestoryMessage box
{
	m_bActive = FALSE;
	m_bInited = FALSE;
	m_bSet = FALSE;
//	m_xMsg.ClearAllNodes();
	return FALSE;
}

BOOL CNoticeBox::HideMessageBox(VOID)							// Hide Message box
{
	m_bActive = FALSE;
	return FALSE;
}

CNoticeBox::~CNoticeBox()										// Destructor
{
}

BOOL CNoticeBox::SetBoxImage(INT nImageIndex)
{
	POINT xSize,xPos;
	if(m_bSet)
	{
		if ( m_pxBtnImage->NewSetIndex(nImageIndex) )
		{
			m_wpData = (WORD*)m_pxBtnImage->m_pbCurrImage;
			m_shWidth = m_pxBtnImage->m_lpstNewCurrWilImageInfo->shWidth;
			m_shHeight = m_pxBtnImage->m_lpstNewCurrWilImageInfo->shHeight;
		}
		xSize.x = g_xMainWnd.m_rcWindow.right - g_xMainWnd.m_rcWindow.left;
		xSize.y = g_xMainWnd.m_rcWindow.bottom - g_xMainWnd.m_rcWindow.top;
		xPos.x = (xSize.x - m_shWidth)/2;
		xPos.y = (xSize.y - m_shHeight)/2;

		SetRect(&m_rcWnd, xPos.x, xPos.y, xPos.x + m_shWidth, xPos.y + m_shHeight);
	}
	return m_bSet;
}

BOOL CNoticeBox::ShowMessageBox(CHAR* szMsg,INT nImgIndex) // Show	Message box with Initialization
{
//	INT Lenth;
	if(!m_bActive)
	{
		if(SetBoxImage(nImgIndex))
		{
			if(ShowMessage(szMsg))
			{
				m_xMsgBtn.ChangeRect(m_rcWnd.left + _NEW_BTN_POS_X, m_rcWnd.top + _NEW_BTN_POS_Y);
			}
			else
			{
				m_bActive = FALSE;
			}
		}
		else
		{
			m_bActive = FALSE;
			m_bInited = FALSE;
		}
	}
	return m_bActive;
}

// Message Process
HRESULT CNoticeBox::OnButtonDown(POINT tpMouse)		// Button Down
{
	HRESULT hResult=0;

	if(m_xMsgBtn.OnLButtonDown(tpMouse))
	{
		hResult = 1;
	}

	if(!hResult)
	{
		if(IsInRect(tpMouse.x,tpMouse.y,m_rcWnd))
		{
			m_bGrabbedMousePos.x  = tpMouse.x - m_rcWnd.left;
			m_bGrabbedMousePos.y  = tpMouse.y - m_rcWnd.top;
			m_bIsSelected = TRUE;
			hResult = 0;
		}
	}

	return hResult;
}

HRESULT	CNoticeBox::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	HRESULT hResult=0;

	switch ( wParam )
	{
		case VK_RETURN:
		{
			g_xClientSocket.SendNoticeOK();
			hResult = 1;
		}
	}

	return hResult;

}

HRESULT	CNoticeBox::OnButtonUp(POINT tpMouse)			// Button Up
{
	HRESULT hResult=0;

	if(m_xMsgBtn.OnLButtonUp(tpMouse))
	{
		g_xClientSocket.SendNoticeOK();
		hResult = 1;
	}

	m_bIsSelected = FALSE;
	hResult=0;
	if(m_xMsgBtn.OnLButtonUp(tpMouse))
		hResult = 1; // Here
	return hResult;
}

// Render Process
BOOL CNoticeBox::RenderMessageBox(INT nLoopTIme)							// Render Function
{
	INT nLine;
//	INT	nCount;
	INT nLineCnt;
	SIZE tSize;
	POINT xTxtPos;

	char	szTempText[1024];

	if(m_bActive&&m_bInited&&m_bSet)
	{	
		g_xMainWnd.DrawWithImageForCompClipRgn( m_rcWnd.left, m_rcWnd.top, m_shWidth, m_shHeight, m_wpData, 800, 600 );
		//m_szMsg
		xTxtPos.x = m_rcWnd.left + 50;
		xTxtPos.y = m_rcWnd.top	 + 115;

		tSize = g_xMainWnd.GetStrLength(NULL, NULL, m_szMsg);

		nLine  = 0;
		nLineCnt  =0;
		if (nLine + tSize.cx > MAX_NOTICESTR_WIDTH)
		{
			int nLen	= strlen(m_szMsg);
			int nCount	= 0;

			for (int i = 0; i < nLen; i++)
			{
				if(m_szMsg[i] == '\n' || m_szMsg[i] == 0x1B)	// 강제개행     \n으로하면  Error ????
				{
					if (nLineCnt >= 0 && nLineCnt <= MAX_NOTICESHOW_LINE)
						g_xMainWnd.PutsHan(NULL, xTxtPos.x + nLine, xTxtPos.y + (nLineCnt * (tSize.cy + 3)), RGB(255,255,255), RGB(0, 0, 0), szTempText);

					nLineCnt++;
					nLine	= 0;
					nCount	= 0;
				}
				else
				{
					if (m_szMsg[i] < 0)
					{
						szTempText[nCount++]	=  m_szMsg[i++];
						szTempText[nCount]		=  m_szMsg[i];
						szTempText[nCount + 1]	= '\0';
					}
					else
					{
						szTempText[nCount]		=  m_szMsg[i];
						szTempText[nCount + 1]	= '\0';
					}

					tSize = g_xMainWnd.GetStrLength(NULL, NULL, szTempText);

					if (nLine + tSize.cx >= MAX_NOTICESTR_WIDTH)
					{
						if (nLineCnt >= 0 && nLineCnt <= MAX_NOTICESHOW_LINE)
							g_xMainWnd.PutsHan(NULL, xTxtPos.x + nLine, xTxtPos.y + (nLineCnt * (tSize.cy + 3)), RGB(255,255,255), RGB(0, 0, 0), szTempText);

						nLineCnt++;
						nLine	= 0;
						nCount	= 0;
					}
					else
						nCount++;
				}
			}

			if (nCount)
			{
				if (nLineCnt >= 0 && nLineCnt <= MAX_NOTICESHOW_LINE)
					g_xMainWnd.PutsHan(NULL, xTxtPos.x + nLine, xTxtPos.y + (nLineCnt * (tSize.cy + 3)), RGB(255,255,255), RGB(0, 0, 0), szTempText);
				nLine += tSize.cx;
			}
		}
		else
		{
			if (nLineCnt >= 0 && nLineCnt <= MAX_NOTICESHOW_LINE)
				g_xMainWnd.PutsHan(NULL, xTxtPos.x + nLine, xTxtPos.y + (nLineCnt * (tSize.cy + 3)), RGB(255,255,255), RGB(0, 0, 0), m_szMsg);

			nLine += tSize.cx;
		}
		
		m_xMsgBtn.ChangeRect(m_rcWnd.left + 133, m_rcWnd.top + 414);
		m_xMsgBtn.ShowGameBtn();

		return FALSE;
	}
	return TRUE;
}

VOID CNoticeBox::MoveWnd(POINT ptMouse)					// Move Window
{
	if ( m_bActive && m_bIsSelected)
	{
		SetRect(&m_rcWnd, ptMouse.x-m_bGrabbedMousePos.x, ptMouse.y-m_bGrabbedMousePos.y,
				ptMouse.x-m_bGrabbedMousePos.x+m_shWidth, ptMouse.y-m_bGrabbedMousePos.y+m_shHeight);
		m_xMsgBtn.ChangeRect(m_rcWnd.left + _NEW_BTN_POS_X, m_rcWnd.top + _NEW_BTN_POS_Y);
	}
	else
	{
		m_xMsgBtn.OnMouseMove(ptMouse);
	}
}


BOOL CNoticeBox::ShowMessage(CHAR* szMsg)		// Show	Message box with Initialization
{
	if(SetMsg(szMsg))
		m_bActive = TRUE;
	else
		m_bActive = FALSE;

	return m_bActive;
}

BOOL CNoticeBox::SetMsg(CHAR* szMsg)				// Init Messages
{
	INT nLength;
	nLength = strlen(szMsg);
	if(nLength!=0)
	{
		ZeroMemory(m_szMsg,MAX_PATH);
		strcpy(m_szMsg,szMsg);
		m_bInited = TRUE;
	}
	else
		m_bInited = FALSE;

	return m_bInited;
}

/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"

VOID CGameBtn::DrawToolTip()
{
	POINT pt = {0, 0};
	static char szLastText[512] = "";
	static bool fAnimation = true;
	static int  nLastSize = 6;

	if (m_szToolTip[0] == '\0')	
	{
		ZeroMemory(&pt, sizeof(pt) );		
		return;
	}

	SIZE size = g_xMainWnd.GetStrLength(NULL, NULL, m_szToolTip);

	size.cx += 12;
	size.cy += 4;

	pt.x = m_rcBtn.right;
	pt.y = m_rcBtn.bottom;

	if ( pt.x + size.cx > 800 )
		pt.x = 800 - size.cx;

	if (strcmp(szLastText, m_szToolTip) ) 
	{
		fAnimation = true;
		strcpy(szLastText, m_szToolTip);
	}

	HRGN	hRgn;
	HBRUSH	hBrushFr = CreateSolidBrush(RGB(255, 255, 150) );
	HBRUSH	hBrushBk = CreateSolidBrush(RGB(  0,   0,   0) );

	// Animation
	if (fAnimation) 
	{
		hRgn = CreateRectRgn(pt.x, pt.y - ++nLastSize, pt.x + size.cx, pt.y);
		if (nLastSize == size.cy)
		{
			fAnimation = false; nLastSize = 6; 
		}
	} 
	else
		hRgn = CreateRectRgn(pt.x, pt.y - size.cy, pt.x + size.cx, pt.y);

	RECT rc;
	GetRgnBox(hRgn, &rc);

	g_xMainWnd.DrawWithGDI(&rc, NULL, RGB(255, 255, 150), 2);
	g_xMainWnd.DrawWithGDI(&rc, NULL, RGB(0, 0, 0), 1);
	g_xMainWnd.PutsHan(NULL, rc, RGB(0, 0, 0), RGB(0, 0, 0), m_szToolTip);

	DeleteObject(hRgn);
	DeleteObject(hBrushFr);
	DeleteObject(hBrushBk);
}

VOID CGameBtn::CreateGameBtn(CWHWilImageData* pxBtnImage, INT nFocusImgIdx, INT nClickImgIdx, INT nStartX, INT nStartY, 
							 CHAR* pszToolTip, BYTE bBtnType, INT nNormalImgIdx, BOOL bUseFocus)
{
	m_bBtnType		= bBtnType;
	m_bBtnState		= _BTN_STATE_NORMAL;
	m_pxBtnImage	= pxBtnImage;
	m_nFocusImgIdx	= nFocusImgIdx;
	m_nClickImgIdx	= nClickImgIdx;
	m_nNormalImgIdx	= nNormalImgIdx;
	m_bUseFocus     = bUseFocus;

	if ( m_pxBtnImage->NewSetIndex(nFocusImgIdx) )
	{
		SetRect(&m_rcBtn, nStartX, nStartY, 
				nStartX+m_pxBtnImage->m_lpstNewCurrWilImageInfo->shWidth,
				nStartY+m_pxBtnImage->m_lpstNewCurrWilImageInfo->shHeight);
	}

	m_nDrawSX = nStartX;
	m_nDrawSY = nStartY;

	if (pszToolTip)
	{
		strcpy(m_szToolTip, pszToolTip);
	}
}


VOID CGameBtn::Init()
{
	m_bBtnType		= _BTN_TYPE_FOCUS;
	m_bBtnState		= _BTN_STATE_FOCUS;
	m_pxBtnImage	= NULL;
	m_nFocusImgIdx	= 0;
	m_nClickImgIdx	= 0;
	m_nNormalImgIdx = 0;
	m_bUseFocus     = FALSE;
	SetRect(&m_rcBtn, 0, 0, 0, 0);

	ZeroMemory(m_szToolTip, sizeof(m_szToolTip));
}


VOID CGameBtn::Destroy()
{
	Init();
}


VOID CGameBtn::ShowGameBtn()
{
	if ( m_bBtnState == _BTN_STATE_NORMAL && m_bBtnType == _BTN_TYPE_FOCUS )
	{
		if ( m_nNormalImgIdx != -1 && m_pxBtnImage->NewSetIndex(m_nNormalImgIdx) )
		{
 			g_xMainWnd.DrawWithImageForCompClipRgn(m_nDrawSX, m_nDrawSY, m_pxBtnImage->m_lpstNewCurrWilImageInfo->shWidth, m_pxBtnImage->m_lpstNewCurrWilImageInfo->shHeight,
												   (WORD*)m_pxBtnImage->m_pbCurrImage, _CLIP_WIDTH, 600);
		}
	}
	else if ( m_bBtnState == _BTN_STATE_FOCUS && m_bBtnType == _BTN_TYPE_FOCUS )
	{
		if ( m_bUseFocus )
		{
			if ( m_pxBtnImage->NewSetIndex(m_nFocusImgIdx) )
			{
 				g_xMainWnd.DrawWithImageForCompClipRgn(m_nDrawSX, m_nDrawSY, m_pxBtnImage->m_lpstNewCurrWilImageInfo->shWidth, m_pxBtnImage->m_lpstNewCurrWilImageInfo->shHeight,
													   (WORD*)m_pxBtnImage->m_pbCurrImage, _CLIP_WIDTH, 600);

			}
		}
		else
		{		
			if ( m_nNormalImgIdx != -1 && m_pxBtnImage->NewSetIndex(m_nNormalImgIdx) )
			{
 				g_xMainWnd.DrawWithImageForCompClipRgn(m_nDrawSX, m_nDrawSY, m_pxBtnImage->m_lpstNewCurrWilImageInfo->shWidth, m_pxBtnImage->m_lpstNewCurrWilImageInfo->shHeight,
													   (WORD*)m_pxBtnImage->m_pbCurrImage, _CLIP_WIDTH, 600);
			}
		}
		DrawToolTip();
	}
	else if ( m_bBtnState == _BTN_STATE_CLICK )
	{
		if ( m_pxBtnImage->NewSetIndex(m_nClickImgIdx) )
		{
 			g_xMainWnd.DrawWithImageForCompClipRgn(m_nDrawSX, m_nDrawSY, m_pxBtnImage->m_lpstNewCurrWilImageInfo->shWidth, m_pxBtnImage->m_lpstNewCurrWilImageInfo->shHeight,
												   (WORD*)m_pxBtnImage->m_pbCurrImage, _CLIP_WIDTH, 600);
		}
	}
}


VOID CGameBtn::OnMouseMove(POINT ptMouse)
{
	if ( PtInRect(&m_rcBtn, ptMouse) && (m_bBtnState != _BTN_STATE_CLICK) )
	{
		m_bBtnState = _BTN_STATE_FOCUS;
		return;
	}
	else if ( m_bBtnState == _BTN_STATE_CLICK )
	{
		return;
	}
	m_bBtnState = _BTN_STATE_NORMAL;
}


BOOL CGameBtn::OnLButtonDown(POINT ptMouse)
{
	if ( PtInRect(&m_rcBtn, ptMouse) )
	{
		m_bBtnState = _BTN_STATE_CLICK;
		return TRUE;
	}
	return FALSE;
}


BOOL CGameBtn::OnLButtonUp(POINT ptMouse, BOOL bUseSound)
{
	m_bBtnState = _BTN_STATE_NORMAL;
	if ( PtInRect(&m_rcBtn, ptMouse) )
	{
		if (bUseSound == TRUE)
			g_SoundManager.SndmngrPlayWavSound(_SOUND_GLASS_BUTTON, 0, 0);
		return TRUE;
	}
	return FALSE;
}


VOID CGameBtn::ChangeRect(INT nStartX, INT nStartY)
{
	m_nDrawSX = nStartX;
	m_nDrawSY = nStartY;
	if ( m_pxBtnImage->NewSetIndex(m_nFocusImgIdx) )
	{
		SetRect(&m_rcBtn, nStartX, nStartY, 
				nStartX+m_pxBtnImage->m_lpstNewCurrWilImageInfo->shWidth,
				nStartY+m_pxBtnImage->m_lpstNewCurrWilImageInfo->shHeight);
	}
}

VOID CGameBtn::ResetGameBtn(INT nFocusImgIdx, INT nClickImgIdx, INT nNormalImgIdx)
{
	m_bBtnState		= _BTN_STATE_NORMAL;
	m_nNormalImgIdx	= nNormalImgIdx;
	m_nFocusImgIdx	= nFocusImgIdx;
	m_nClickImgIdx	= nClickImgIdx;
	if ( m_pxBtnImage->NewSetIndex(nFocusImgIdx) )
	{
		INT nStartX = m_nDrawSX = m_rcBtn.left;
		INT nStartY = m_nDrawSY = m_rcBtn.top;
		SetRect(&m_rcBtn, nStartX, nStartY, 
				nStartX+m_pxBtnImage->m_lpstNewCurrWilImageInfo->shWidth,
				nStartY+m_pxBtnImage->m_lpstNewCurrWilImageInfo->shHeight);
	}
}

VOID CGameBtn::ChangeBtnTooltip(CHAR *pszTooltip)
{
	if (pszTooltip)
	{
		strcpy(m_szToolTip, pszTooltip);
	}
}


CMsgBoxBtn::CMsgBoxBtn():CGameBtn()
{
}

CMsgBoxBtn::~CMsgBoxBtn()
{
}

VOID CMsgBoxBtn::ShowGameBtn()
{
	if ( m_bBtnState != _BTN_STATE_CLICK)
	{
		if ( m_pxBtnImage->NewSetIndex(m_nFocusImgIdx) )
		{
 			g_xMainWnd.DrawWithImageForCompClipRgn(m_rcBtn.left, m_rcBtn.top, m_rcBtn.right-m_rcBtn.left, m_rcBtn.bottom-m_rcBtn.top,
												   (WORD*)m_pxBtnImage->m_pbCurrImage, _CLIP_WIDTH, 600);
		}
	}
	else
	{
		if ( m_pxBtnImage->NewSetIndex(m_nClickImgIdx) )
		{
 			g_xMainWnd.DrawWithImageForCompClipRgn(m_rcBtn.left, m_rcBtn.top, m_rcBtn.right-m_rcBtn.left, m_rcBtn.bottom-m_rcBtn.top,
												   (WORD*)m_pxBtnImage->m_pbCurrImage, _CLIP_WIDTH, 600);
		}
	}
}












CScrlBar::CScrlBar()
{
	Init();
}

CScrlBar::~CScrlBar()
{
}

VOID CScrlBar::CreateScrlBar(CWHWilImageData* pxImage, INT ImgIdx, INT nPageLine, WORD wScrlWidth, WORD wScrlHeight, WORD wScrlBtnLength, BOOL bType)
{
	m_pxScrlImage	= pxImage;
	m_nScrlImgIdx	= ImgIdx;
	m_nPageLine		= nPageLine;

	m_wScrlWidth	= wScrlWidth;
	m_wScrlHeight	= wScrlHeight;

	m_wScrlBtnLength= wScrlBtnLength;

	m_dwTick		= timeGetTime();
	mScrlbar_bType	= bType;
}

VOID CScrlBar::ShowScrlBar(INT nX, INT nY, INT nFstPos, INT nCounter)
{
	RECT	rcImg;

	if ( m_pxScrlImage->NewSetIndex(m_nScrlImgIdx) )
	{
		INT nImgHeight = m_pxScrlImage->m_lpstNewCurrWilImageInfo->shHeight;
		INT nImgWidth  = m_pxScrlImage->m_lpstNewCurrWilImageInfo->shWidth;

		if ( (nCounter-1) <= 0 )
		{
			m_fScrlRate = 0.0f;
		}
		else
		{
			m_fScrlRate = (FLOAT)nFstPos/(FLOAT)(nCounter-1);
		}

		if ( nCounter == 0 )
		{
			m_fPageRate = 0.0f;
		}
		else
		{
			m_fPageRate = (FLOAT)m_nPageLine/(FLOAT)(nCounter);
		}

		if (mScrlbar_bType == SCR_TYPE_VERTICAL)
		{
			SetRect(&rcImg,
					0, 0, m_pxScrlImage->m_lpstNewCurrWilImageInfo->shWidth, m_pxScrlImage->m_lpstNewCurrWilImageInfo->shHeight);

			SetRect(&m_rcScrlRgn, 
					nX, nY, nX+m_pxScrlImage->m_lpstNewCurrWilImageInfo->shWidth, nY+m_wScrlHeight + m_pxScrlImage->m_lpstNewCurrWilImageInfo->shHeight);

			SetRect(&m_rcScrlBtnRgn, 
					nX, nY+m_wScrlHeight*m_fScrlRate, 
					nX+m_pxScrlImage->m_lpstNewCurrWilImageInfo->shWidth, nY+m_wScrlHeight*m_fScrlRate+m_pxScrlImage->m_lpstNewCurrWilImageInfo->shHeight);
		}
		else if (mScrlbar_bType == SCR_TYPE_HORIZONTAL)
		{
//			SetRect(&rcImg,
//					(INT)(nImgWidth - m_wScrlWidth - m_fScrlRate * m_wScrlWidth), 0,
//					(INT)(nImgWidth - m_fScrlRate * m_wScrlWidth), m_wScrlHeight);
			SetRect(&rcImg,
					0, 0, m_pxScrlImage->m_lpstNewCurrWilImageInfo->shWidth, m_pxScrlImage->m_lpstNewCurrWilImageInfo->shHeight);


//			SetRect(&m_rcScrlRgn, 
//					nX + nImgWidth - m_wScrlWidth - rcImg.left , nY, nX+nImgWidth - rcImg.left , nY+m_wScrlHeight);

			SetRect(&m_rcScrlRgn, 
					nX, nY, nX+m_wScrlWidth+m_pxScrlImage->m_lpstNewCurrWilImageInfo->shWidth, nY+ m_pxScrlImage->m_lpstNewCurrWilImageInfo->shHeight);

//			SetRect(&m_rcScrlBtnRgn,
//					(INT)(nX+nImgWidth - m_wScrlWidth + (m_wScrlWidth*m_fScrlRate) - rcImg.left ), nY,
//					(INT)(nX+nImgWidth - m_wScrlWidth + (m_wScrlWidth * m_fScrlRate) + m_wScrlBtnLength - rcImg.left )
//					, nY + m_wScrlHeight);

			SetRect(&m_rcScrlBtnRgn, 
					nX+m_wScrlWidth*m_fScrlRate, nY, 
					nX+m_wScrlWidth*m_fScrlRate+m_pxScrlImage->m_lpstNewCurrWilImageInfo->shWidth, nY+m_pxScrlImage->m_lpstNewCurrWilImageInfo->shHeight);

		}

		RECT rc;
		SetRect(&rc, nX, nY+10, nX+nImgWidth, nY+nImgHeight+10);

//		g_xMainWnd.DrawWithGDI(&rc, NULL, RGB(200, 200, 200), 1);
//		g_xMainWnd.DrawWithGDI(&rcImg, NULL, RGB(200, 0, 200), 1);
//		g_xMainWnd.DrawWithGDI(&m_rcScrlRgn, NULL, RGB(200, 200, 0), 1);
//		g_xMainWnd.DrawWithGDI(&m_rcScrlBtnRgn, NULL, RGB(200, 200, 200), 1);

//		g_xMainWnd.DrawWithImageForComp(nX, nY+m_fScrlRate*m_wScrlHeight, nImgWidth, nImgHeight, (WORD*)m_pxScrlImage->m_pbCurrImage);
		if (mScrlbar_bType == SCR_TYPE_VERTICAL)
	 		g_xMainWnd.DrawWithImageForComp(nX, (INT)(nY+m_fScrlRate*m_wScrlHeight), &rcImg, (WORD*)m_pxScrlImage->m_pbCurrImage);
		else if (mScrlbar_bType == SCR_TYPE_HORIZONTAL)
			g_xMainWnd.DrawWithImageForComp((INT)(nX + m_fScrlRate * m_wScrlWidth), nY, &rcImg, (WORD*)m_pxScrlImage->m_pbCurrImage);
	}
}

BOOL CScrlBar::OnMouseMove(POINT ptMouse)
{
	if ( m_bGrapsed )
	{
		if (mScrlbar_bType == SCR_TYPE_VERTICAL)
		{
			if ( ptMouse.y <= m_rcScrlRgn.top )
			{
				m_fScrlRate = 0.0f;
			}
			else if ( ptMouse.y >= m_rcScrlRgn.bottom )
			{
				m_fScrlRate = 1.0f;
			}
			else if ( m_rcScrlRgn.bottom-m_rcScrlRgn.top == 0 )
			{
				m_fScrlRate = 0.0f;
			}
			else
			{
				m_fScrlRate = (FLOAT)(ptMouse.y-m_rcScrlRgn.top)/(FLOAT)(m_rcScrlRgn.bottom-m_rcScrlRgn.top);
			}
		}
		else if (mScrlbar_bType == SCR_TYPE_HORIZONTAL)
		{
			if ( ptMouse.x <= m_rcScrlRgn.left )
			{
				m_fScrlRate = 0.0f;
			}
			else if ( ptMouse.x >= m_rcScrlRgn.right )
			{
				m_fScrlRate = 1.0f;
			}
			else if ( m_rcScrlRgn.right-m_rcScrlRgn.left == 0 )
			{
				m_fScrlRate = 0.0f;
			}
			else
			{
				m_fScrlRate = (FLOAT)(ptMouse.x-m_rcScrlRgn.left)/(FLOAT)(m_rcScrlRgn.right-m_rcScrlRgn.left);
			}
		}
		return TRUE;
	}

	return FALSE;
}

BOOL CScrlBar::OnLButtonDown(POINT ptMouse)
{
	if ( PtInRect(&m_rcScrlRgn, ptMouse) )
	{
		if ( timeGetTime() - m_dwTick > 10 )
		{
			if ( PtInRect(&m_rcScrlBtnRgn, ptMouse)  )
			{
				m_bGrapsed = TRUE;
			}
			else if ( PtInRect(&m_rcScrlRgn, ptMouse) )
			{
				if (mScrlbar_bType == SCR_TYPE_VERTICAL)
				{
					// 위로 한페이지 스크롤.
					if ( m_rcScrlBtnRgn.top+m_wScrlBtnLength/2 > ptMouse.y )
					{
						m_fScrlRate -= m_fPageRate;

						if ( m_fScrlRate < 0.0f )
						{
							m_fScrlRate = 0.0f;
						}
					}
					// 아래로 한페이지 스크롤.
					else if ( m_rcScrlBtnRgn.top+m_wScrlBtnLength/2 <= ptMouse.y )
					{
						m_fScrlRate += m_fPageRate;

						if ( m_fScrlRate > 1.0f )
						{
							m_fScrlRate = 1.0f;
						}
					}
				}
				else if (mScrlbar_bType == SCR_TYPE_HORIZONTAL)
				{
					// 왼쪽으로 한페이지 스크롤.
					if ( m_rcScrlBtnRgn.left + m_wScrlBtnLength/2 > ptMouse.x )
					{
						m_fScrlRate -= m_fPageRate;

						if ( m_fScrlRate < 0.0f )
						{
							m_fScrlRate = 0.0f;
						}
					}
					// 오른쪽으로 한페이지 스크롤.
					else if ( m_rcScrlBtnRgn.left + m_wScrlBtnLength/2 <= ptMouse.x )
					{
						m_fScrlRate += m_fPageRate;

						if ( m_fScrlRate > 1.0f )
						{
							m_fScrlRate = 1.0f;
						}
					}
				}
			}
			m_dwTick = timeGetTime();
		}
		return TRUE;
	}

	return FALSE;
}

BOOL CScrlBar::OnLButtonUp(POINT ptMouse)
{
	m_dwTick = timeGetTime();

	if ( m_bGrapsed )
	{
		m_bGrapsed = FALSE;
		return TRUE;
	}
	else
		return FALSE;
}

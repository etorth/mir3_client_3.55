/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"


VOID CGameWnd::CreateGameWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, BOOL bCanMove, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BYTE bBlend)
{
	m_nID			= nID;
	m_nFrameImgIdx	= nFrameImgIdx;
	m_pxWndImage	= pxWndImage;
	m_bCanMove		= bCanMove;

	RECT	rcImg = {0, 0, 0, 0};
	if ( m_pxWndImage->NewSetIndex(m_nFrameImgIdx) )
	{
		SetRect(&rcImg, 0, 0, 
				m_pxWndImage->m_lpstNewCurrWilImageInfo->shWidth,
				m_pxWndImage->m_lpstNewCurrWilImageInfo->shHeight);
	}

	( ! nWidth )  ?	m_nWidth = rcImg.right -rcImg.left: m_nWidth  = nWidth;
	( ! nHeight ) ?	m_nHeight =rcImg.bottom-rcImg.top : m_nHeight = nHeight;
	
	SetRect(&m_rcImgWnd, 
			nStartX - (rcImg.right - rcImg.left - m_nWidth )/2, 
			nStartY - (rcImg.bottom - rcImg.top - m_nHeight)/2, 
			nStartX - (rcImg.right - rcImg.left - m_nWidth )/2 + (rcImg.right - rcImg.left), 
			nStartY - (rcImg.bottom - rcImg.top - m_nHeight)/2 + (rcImg.bottom - rcImg.top));

	SetRect(&m_rcWnd, nStartX, nStartY, nStartX+m_nWidth, nStartY+m_nHeight);

	SetBlend(bBlend);
}


VOID CGameWnd::Init()
{
	m_nID			= 0; 
	m_nFrameImgIdx	= 0;
	m_nWidth		= 0;
	m_nHeight		= 0;
	m_pxWndImage	= NULL;
	m_bActive		= FALSE;
	m_bFocused		= FALSE;
	m_bMoving		= FALSE;
	m_bCanMove		= FALSE;
	SetRect(&m_rcWnd, 0, 0, 0, 0);
	SetRect(&m_rcImgWnd, 0, 0, 0, 0);
	ZeroMemory(&m_bGrabbedMousePos, sizeof(POINT));
}


VOID CGameWnd::Destroy()
{
	Init();
}


VOID CGameWnd::ShowGameWnd(INT nIdx)
{
	if ( m_bActive )
	{
		if ( g_bTextrRistricted )
		{
			if ( m_pxWndImage->NewSetIndex(m_nFrameImgIdx) )
			{
 				g_xMainWnd.DrawWithImageForCompClipRgn(m_rcImgWnd.left, m_rcImgWnd.top, m_pxWndImage->m_lpstNewCurrWilImageInfo->shWidth, m_pxWndImage->m_lpstNewCurrWilImageInfo->shHeight,
													   (WORD*)m_pxWndImage->m_pbCurrImage, _CLIP_WIDTH, 600);
			}
		}
		else if ( nIdx == _IMAGE_INTER1 )
		{
			D3DMATERIAL7	mtrl;
			D3DVECTOR		vecTrans;
			D3DVECTOR		vecScale;

			vecTrans = D3DVECTOR((FLOAT)m_rcImgWnd.left, (FLOAT)m_rcImgWnd.top, 0);
			vecScale = D3DVECTOR((FLOAT)(m_rcImgWnd.right -m_rcImgWnd.left), (FLOAT)(m_rcImgWnd.bottom -m_rcImgWnd.top), 1);

			LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_INTER1, m_nFrameImgIdx);

			D3DUtil_InitMaterial(mtrl, (FLOAT)m_bBright/255.0f, (FLOAT)m_bBright/255.0f, (FLOAT)m_bBright/255.0f);
			mtrl.diffuse.a = (FLOAT)m_bOpa/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr);
		}
		else// if( nIdx == _IMAGE_INTER )
		{
			D3DMATERIAL7	mtrl;
			D3DVECTOR		vecTrans;
			D3DVECTOR		vecScale;

			vecTrans = D3DVECTOR((FLOAT)m_rcImgWnd.left, (FLOAT)m_rcImgWnd.top, 0);
			vecScale = D3DVECTOR((FLOAT)(m_rcImgWnd.right -m_rcImgWnd.left), (FLOAT)(m_rcImgWnd.bottom -m_rcImgWnd.top), 1);

			LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_INTER, m_nFrameImgIdx);

			D3DUtil_InitMaterial(mtrl, (FLOAT)m_bBright/255.0f, (FLOAT)m_bBright/255.0f, (FLOAT)m_bBright/255.0f);
			mtrl.diffuse.a = (FLOAT)m_bOpa/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr);
		}
	}

}

VOID CGameWnd::ResetWndImg(INT nIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight)
{
	if ( m_pxWndImage->NewSetIndex(nIdx) )
	{
		m_nFrameImgIdx = nIdx;

		RECT	rcImg = {0, 0, 0, 0};
		SetRect(&rcImg, 0, 0, 
				m_pxWndImage->m_lpstNewCurrWilImageInfo->shWidth,
				m_pxWndImage->m_lpstNewCurrWilImageInfo->shHeight);

		( ! nWidth )  ?	m_nWidth = rcImg.right -rcImg.left: m_nWidth  = nWidth;
		( ! nHeight ) ?	m_nHeight =rcImg.bottom-rcImg.top : m_nHeight = nHeight;
		
		SetRect(&m_rcImgWnd, 
				nStartX - (rcImg.right - rcImg.left - m_nWidth )/2, 
				nStartY - (rcImg.bottom - rcImg.top - m_nHeight)/2, 
				nStartX - (rcImg.right - rcImg.left - m_nWidth )/2 + (rcImg.right - rcImg.left), 
				nStartY - (rcImg.bottom - rcImg.top - m_nHeight)/2 + (rcImg.bottom - rcImg.top));

		SetRect(&m_rcWnd, nStartX, nStartY, nStartX+m_nWidth, nStartY+m_nHeight);
	}
}

// 윈도우를 활성화 한다.
VOID CGameWnd::SetGameWndActive(BOOL bActive)
{
	m_bActive = bActive;
}

// 윈도우에 포커스를 준다.
VOID CGameWnd::SetGameWndFocused(BOOL bFocused)
{
	m_bFocused = bFocused;
}

VOID CGameWnd::MoveGameWnd(POINT ptMouse, BOOL bForceMove)
{
	INT nImgWidth  = m_rcImgWnd.right - m_rcImgWnd.left;
	INT nImgHeight = m_rcImgWnd.bottom - m_rcImgWnd.top;
	if ( bForceMove )
	{
		SetRect(&m_rcWnd, ptMouse.x, ptMouse.y, ptMouse.x+m_nWidth, ptMouse.y+m_nHeight); 
		SetRect(&m_rcImgWnd, 
				ptMouse.x - (nImgWidth - m_nWidth )/2, 
				ptMouse.y - (nImgHeight- m_nHeight)/2, 
				ptMouse.x - (nImgWidth - m_nWidth )/2 + nImgWidth, 
				ptMouse.y - (nImgHeight- m_nHeight)/2 + nImgHeight);
	}
	else
	{
		if ( (m_bActive && m_bFocused && m_bCanMove) )
		{
			INT nSX = ptMouse.x-m_bGrabbedMousePos.x;
			INT nSY = ptMouse.y-m_bGrabbedMousePos.y;

			if ( (nSY + m_nHeight) > 570  )
			{
				nSY = 565 - m_nHeight;
			}

			SetRect(&m_rcWnd, nSX, nSY, nSX+m_nWidth, nSY+m_nHeight); 

			SetRect(&m_rcImgWnd, 
					nSX - (nImgWidth - m_nWidth )/2, 
					nSY - (nImgHeight- m_nHeight)/2, 
					nSX - (nImgWidth - m_nWidth )/2 + nImgWidth, 
					nSY - (nImgHeight- m_nHeight)/2 + nImgHeight);
		}
	}
}

// 윈도우가 움직이기 시작할때 마우스와의 Gap을 얻는다.
VOID CGameWnd::SetReadyMove(POINT ptMouse)
{
	if ( m_bActive && m_bFocused && m_bCanMove )
	{
		m_bGrabbedMousePos.x = ptMouse.x - m_rcWnd.left;
		m_bGrabbedMousePos.y = ptMouse.y - m_rcWnd.top;
	}
}

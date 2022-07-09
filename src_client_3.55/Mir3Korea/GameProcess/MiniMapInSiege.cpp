/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"



CMiniMapInSiege::CMiniMapInSiege()
{
}


CMiniMapInSiege::~CMiniMapInSiege()
{
	SAFE_RELEASE(m_pddsSurface);
	m_xMinimapData1.Destroy();
	m_xMinimapData2.Destroy();
}


VOID CMiniMapInSiege::InitMiniMap(LPDIRECT3DDEVICE7 pd3dDevice)
{
	m_xMinimapData1.Init();
	m_xMinimapData2.Init();

	m_xMinimapData1.NewLoad(".\\Data\\MMap.wil");
	m_xMinimapData2.NewLoad(".\\Data\\FMMap.wil");

	ZeroMemory(&m_rcView, sizeof(RECT));
	ZeroMemory(&m_rcMiniMapRect, sizeof(RECT));

	m_nWidth	= 128;
	m_nHeight	= 128;

	SetRect(&m_rcScrn, 800-m_nWidth, 0, 800, m_nHeight);

	m_nMMapIdx	= -1;
	m_nDelay	= 0;

	m_bShowMonInfo = FALSE;

	m_bBlend	= FALSE;
//	m_bMultiple = FALSE;
	m_bMultiple = _FST_RATE;

	ZeroMemory(&m_rcBlend, sizeof(RECT));
	ZeroMemory(&m_rcMultiple, sizeof(RECT));

	ZeroMemory(&m_ptGrasp, sizeof(POINT));
	ZeroMemory(&m_ptMyPos, sizeof(POINT));
	ZeroMemory(&m_ptMySiegePos, sizeof(POINT));

    SAFE_RELEASE(m_pddsSurface);
	
	MiniMapSurface(pd3dDevice, 256, 256);
}


HRESULT CMiniMapInSiege::MiniMapSurface(LPDIRECT3DDEVICE7 pd3dDevice, INT nWidth, INT nHeight)
{
    D3DDEVICEDESC7 ddDesc;
    DDSURFACEDESC2 ddsd;

	m_nWidth  = nWidth;
	m_nHeight = nHeight;

	INT nRealWidth, nRealHeight;

	if ( nWidth >= m_rcMiniMapRect.right - m_rcMiniMapRect.left )
	{
		nRealWidth = m_rcMiniMapRect.right - m_rcMiniMapRect.left;
	}
	else
	{
		nRealWidth = nWidth;
	}

	if ( nHeight >= m_rcMiniMapRect.bottom - m_rcMiniMapRect.top )
	{
		nRealHeight = m_rcMiniMapRect.bottom - m_rcMiniMapRect.top;
	}
	else
	{
		nRealHeight = nHeight;
	}
	
	SetRect(&m_rcScrn, 800-nRealWidth, 0, 800, nRealHeight);

	SAFE_RELEASE(m_pddsSurface);

    if( NULL == pd3dDevice )
	{
        return DDERR_INVALIDPARAMS;
	}

    if ( FAILED(pd3dDevice->GetCaps(&ddDesc)) )
	{
        return E_FAIL;
	}

    D3DUtil_InitSurfaceDesc( ddsd );
//	ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
//	ddsd.dwSize			 = sizeof(DDSURFACEDESC2);
    ddsd.dwFlags         = DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH/*|DDSD_TEXTURESTAGE*/;
    ddsd.ddsCaps.dwCaps  = DDSCAPS_TEXTURE;
	ddsd.dwTextureStage  = 0;    
    ddsd.dwWidth         = nWidth;
    ddsd.dwHeight        = nHeight;

    if ( ddDesc.deviceGUID == IID_IDirect3DHALDevice || ddDesc.deviceGUID == IID_IDirect3DTnLHalDevice )
	{
        ddsd.ddsCaps.dwCaps2 = DDSCAPS2_TEXTUREMANAGE;
	}
    else
	{
        ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
	}

	// 직사각형의 텍스춰를 지원하지 않는다면...
    if ( ddDesc.dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_SQUAREONLY )
    {
        if ( ddsd.dwWidth > ddsd.dwHeight ) ddsd.dwHeight = ddsd.dwWidth;
        else                                ddsd.dwWidth  = ddsd.dwHeight;
    }

    HRESULT hr = g_xMainWnd.GetDirectDraw()->CreateSurface(&ddsd, &m_pddsSurface, NULL);

    if( FAILED(hr) )
	{
        return hr;
	}
	// 컬러키를 세팅한다.
	DDSetColorKey(m_pddsSurface, RGB(0, 0, 0));

	return S_OK;
}

BOOL CMiniMapInSiege::SetMiniMap(INT nIdx)
{
	m_nMMapIdx	 = nIdx;

	if ( m_nMMapIdx >= 1000 )
	{
		if ( m_xMinimapData2.NewSetIndex(m_nMMapIdx-1000) )
		{
 			SetRect(&m_rcMiniMapRect, 0, 0, m_xMinimapData2.m_lpstNewCurrWilImageInfo->shWidth, m_xMinimapData2.m_lpstNewCurrWilImageInfo->shHeight);
			MiniMapSurface(g_xMainWnd.Get3DDevice(), 256, 256);
			return TRUE;
		}
	}
	else
	{
		if ( m_xMinimapData1.NewSetIndex(m_nMMapIdx) )
		{
 			SetRect(&m_rcMiniMapRect, 0, 0, m_xMinimapData1.m_lpstNewCurrWilImageInfo->shWidth, m_xMinimapData1.m_lpstNewCurrWilImageInfo->shHeight);
			MiniMapSurface(g_xMainWnd.Get3DDevice(), 180, 130);
			return TRUE;
		}
	}

	return FALSE;
}


VOID CMiniMapInSiege::MoveMiniMap(INT nX, INT nY)
{
	if ( m_nMMapIdx	== -1 )
	{
		return;
	}

	INT nSX, nSY;

//	m_ptMyPos.x = nX;
//	m_ptMyPos.y = nY;

	m_ptMySiegePos.x = nX;
	m_ptMySiegePos.y = nY;

	if ( m_rcMiniMapRect.right > m_nWidth )
	{
		nSX = (INT)(nX*1.5f - m_nWidth/2);
	}
	else
	{
		nSX = (INT)(nX*1.5f - m_rcMiniMapRect.right/2);
	}

	if ( m_rcMiniMapRect.bottom > m_nHeight )
	{
		nSY = nY - m_nHeight/2;
	}
	else
	{
		nSY = nY - m_rcMiniMapRect.bottom/2;
	}

	SetRect(&m_rcView, nSX, nSY, nSX+m_nWidth, nSY+m_nHeight);

	if ( m_rcView.left < 0 )
	{
		m_rcView.left  = 0;
		m_rcView.right = m_rcMiniMapRect.right;
		
		if ( m_rcView.right > m_nWidth )
		{
			m_rcView.right = m_nWidth;
		}
	}
	if ( m_rcView.right  >= m_rcMiniMapRect.right )
	{
		m_rcView.left  = m_rcMiniMapRect.right-m_nWidth;
		m_rcView.right = m_rcMiniMapRect.right;

		if ( m_rcView.left < 0 ) 
		{
			m_rcView.left = 0;
		}
	}
	if ( m_rcView.top <  0 )							
	{
		m_rcView.top    = 0;
		m_rcView.bottom = m_rcMiniMapRect.bottom;

		if ( m_rcView.bottom > m_nHeight )
		{
			m_rcView.bottom = m_nHeight;
		}
	}
	if ( m_rcView.bottom >= m_rcMiniMapRect.bottom)		
	{
		m_rcView.top    = m_rcMiniMapRect.bottom-m_nHeight;
		m_rcView.bottom = m_rcMiniMapRect.bottom;

		if ( m_rcView.top < 0 ) 
			m_rcView.top = 0;
	}

	INT nWidth, nHeight;

	nWidth  = m_rcView.right - m_rcView.left;
	nHeight = m_rcView.bottom - m_rcView.top;

	if ( nHeight < m_nHeight || nWidth < m_nWidth )
	{
		DDBLTFX ddbltfx;
		ZeroMemory(&ddbltfx, sizeof(ddbltfx));
		ddbltfx.dwSize      = sizeof(ddbltfx);
		ddbltfx.dwFillColor = RGB(0, 0, 0);
		m_pddsSurface->Blt(NULL, NULL, NULL, DDBLT_COLORFILL, &ddbltfx);
	}

	SetRect(&m_rcScrn, m_rcScrn.left, m_rcScrn.top, m_rcScrn.left+nWidth, m_rcScrn.top+nHeight);


	if ( m_nMMapIdx >= 1000 )
	{
		if ( m_xMinimapData2.NewSetIndex(m_nMMapIdx-1000) )
		{
			g_xMainWnd.DrawWithImageForComp(&m_rcView, (WORD*)m_xMinimapData2.m_pbCurrImage, m_pddsSurface);
		}
	}
	else
	{
		if ( m_xMinimapData1.NewSetIndex(m_nMMapIdx) )
		{
			g_xMainWnd.DrawWithImageForComp(&m_rcView, (WORD*)m_xMinimapData1.m_pbCurrImage, m_pddsSurface);
		}
	}
}


BOOL CMiniMapInSiege::OnLButtonDown(POINT ptMouse)
{
	if ( PtInRect(&m_rcScrn, ptMouse) )
	{
		if ( ( HIBYTE(GetKeyState(VK_CONTROL))) )
		{
			m_ptGrasp.x = ptMouse.x - m_rcScrn.left;
			m_ptGrasp.y = ptMouse.y - m_rcScrn.top;

			return TRUE;
		}
	}

	if ( PtInRect(&m_rcBlend, ptMouse) )
	{
		m_bBlend = !m_bBlend;
		return TRUE;
	}

	if ( PtInRect(&m_rcMultiple, ptMouse) )
	{	
		m_bMultiple++;

		if ( m_bMultiple > _SND_RATE )
		{
			m_bMultiple = _FST_RATE; 
		}

		switch ( m_bMultiple )
		{
			case _FST_RATE:
			{
				MiniMapSurface(g_xMainWnd.Get3DDevice(), 128, 128);
				break;
			}
			case _SND_RATE:
			{
				MiniMapSurface(g_xMainWnd.Get3DDevice(), 256, 256);
				break;
			}
			case _TRD_RATE:
			{
				MiniMapSurface(g_xMainWnd.Get3DDevice(), 512, 512);
				break;
			}
			case _FOURTH_RATE:
			{
				MiniMapSurface(g_xMainWnd.Get3DDevice(), 1024, 1024);
				break;
			}
			case _INMAINFRAME_RATE:
			{
				MiniMapSurface(g_xMainWnd.Get3DDevice(), 80, 80);
				break;
			}
		}
/*		m_bMultiple = !m_bMultiple;

		if ( m_bMultiple )
		{
			MiniMapSurface(g_xMainWnd.Get3DDevice(), 256, 256);
		}
		else
		{
			MiniMapSurface(g_xMainWnd.Get3DDevice(), 128, 128);
		}*/

		return TRUE;
	}

	return FALSE;
}


BOOL CMiniMapInSiege::OnLButtonUp(POINT ptMouse)
{
	return FALSE;
}


BOOL CMiniMapInSiege::OnMouseMove(POINT ptMouse)
{
	if ( PtInRect(&m_rcScrn, ptMouse) )
	{
		if ( ( HIBYTE(GetKeyState(VK_LBUTTON)) && HIBYTE(GetKeyState(VK_CONTROL))) )
		{
			SetRect(&m_rcScrn, ptMouse.x-m_ptGrasp.x, ptMouse.y-m_ptGrasp.y, 
					ptMouse.x-m_ptGrasp.x+m_nWidth, ptMouse.y-m_ptGrasp.y+m_nHeight); 

			return TRUE;
		}
	}
	return FALSE;
}



HRESULT CMiniMapInSiege::ResetMiniMap(LPDIRECT3DDEVICE7 pd3dDevice)
{
    D3DDEVICEDESC7 ddDesc;
    DDSURFACEDESC2 ddsd;

 	m_xMinimapData1.Destroy();
	m_xMinimapData1.Init();
	m_xMinimapData2.Destroy();
	m_xMinimapData2.Init();

	m_xMinimapData1.NewLoad(".\\Data\\MMap.wil");
	m_xMinimapData2.NewLoad(".\\Data\\FMMap.wil");

    SAFE_RELEASE(m_pddsSurface);

    if( NULL == pd3dDevice )
	{
        return DDERR_INVALIDPARAMS;
	}

    if ( FAILED(pd3dDevice->GetCaps(&ddDesc)) )
	{
        return E_FAIL;
	}

//	ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
//	ddsd.dwSize			 = sizeof(DDSURFACEDESC2);
    D3DUtil_InitSurfaceDesc( ddsd );
    ddsd.dwFlags         = DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH/*|DDSD_TEXTURESTAGE*/;
    ddsd.ddsCaps.dwCaps  = DDSCAPS_TEXTURE;
    ddsd.dwTextureStage  = 0;
    ddsd.dwWidth         = m_nWidth;
    ddsd.dwHeight        = m_nHeight;

    if ( ddDesc.deviceGUID == IID_IDirect3DHALDevice || ddDesc.deviceGUID == IID_IDirect3DTnLHalDevice )
        ddsd.ddsCaps.dwCaps2 = DDSCAPS2_TEXTUREMANAGE;
    else
        ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;

	// 직사각형의 텍스춰를 지원하지 않는다면...
    if ( ddDesc.dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_SQUAREONLY )
    {
        if ( ddsd.dwWidth > ddsd.dwHeight ) ddsd.dwHeight = ddsd.dwWidth;
        else                                ddsd.dwWidth  = ddsd.dwHeight;
    }

    HRESULT hr = g_xMainWnd.GetDirectDraw()->CreateSurface(&ddsd, &m_pddsSurface, NULL);

    if( FAILED(hr) )
	{
        return hr;
	}
	// 컬러키를 세팅한다.
	DDSetColorKey(m_pddsSurface, RGB(0, 0, 0));

	return S_OK;
}

VOID CMiniMapInSiege::SetInMainFrame()
{
	m_bMultiple = _INMAINFRAME_RATE;

	MiniMapSurface(g_xMainWnd.Get3DDevice(), 82, 100);

	m_rcScrn.left = 533;
	m_rcScrn.top = 482;
}


VOID CMiniMapInSiege::RenderMinimapInMain(INT nLoopTime)
{
	if ( m_pddsSurface == NULL )
	{
		return;
	}

	INT		nStartX, nStartY, nWidth, nHeight;
	RECT	rcScrn;

	nStartX = g_xGameProc.m_xInterface.m_xSiegeWnd.m_rcMinimap.left;
	nStartY = g_xGameProc.m_xInterface.m_xSiegeWnd.m_rcMinimap.top;

	nWidth = 180;
	nHeight = 150;

	SetRect(&rcScrn, nStartX, nStartY, nStartX+nWidth, nStartY+nHeight);

	D3DMATERIAL7 mtrl;
	D3DVECTOR	vecTrans((FLOAT)nStartX, (FLOAT)nStartY, 0);
	D3DVECTOR	vecScale((FLOAT)nWidth, (FLOAT)nHeight, 1);

	D3DUtil_InitMaterial(mtrl, (FLOAT)150/255.0f, (FLOAT)150/255.0f, (FLOAT)150/255.0f);
	if ( m_bBlend )
		mtrl.diffuse.a = 175.0f/255.0f;
	else 
		mtrl.diffuse.a = 200.0f/200.0f;

	g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, m_pddsSurface);

	RECT rcCnt;
	INT	 nSX, nSY;
	
	CActor*				pxActor = NULL;
	CListNode <CActor>	*pNode;
	INT					nPosX, nPosY;
	for ( pNode = g_xGameProc.m_xActorList.GetHead(); pNode; pNode = pNode->GetNext() )
	{
		pxActor = pNode->GetData();

		if ( pxActor )
		{
			if ( pxActor->m_nIdentity == g_xGameProc.m_xInterface.m_xSiegeWnd.m_nIndex )
			{
				nSX = (INT)(rcScrn.left + pxActor->m_nPosX*1.04f - m_rcView.left*0.7f - 1);
				nSY = (INT)(rcScrn.top + pxActor->m_nPosY*0.59f - m_rcView.top*0.58f - 1);
			}

			if ( pxActor->m_stFeature.bGender == _GENDER_NPC )
			{
				nPosX = (INT)(rcScrn.left + pxActor->m_nPosX*1.04f - m_rcView.left*0.7f - 1);
				nPosY = (INT)(rcScrn.top + pxActor->m_nPosY*0.59f - m_rcView.top*0.58f - 1);

				SetRect(&rcCnt, nPosX, nPosY, nPosX, nPosY);

				g_xMainWnd.DrawWithGDI(&rcCnt, NULL, RGB(255, 255, 0), 1);
			}

			// 세트아이템 : 몬스터의 위치를 보여준다.
			if ( m_bShowMonInfo )
			{
				if ( !pxActor->m_bIsDead )
				{
					if ( pxActor->m_stFeature.bGender == _GENDER_MON )
					{
						nPosX = (INT)(rcScrn.left + pxActor->m_nPosX*1.04f - m_rcView.left*0.7f - 1);
						nPosY = (INT)(rcScrn.top + pxActor->m_nPosY*0.59f - m_rcView.top*0.58f - 1);

						SetRect(&rcCnt, nPosX, nPosY, nPosX+2, nPosY+2);

						g_xMainWnd.DrawWithGDI(&rcCnt, NULL, RGB(255, 0, 0), 2);
					}
				}
			}
		}
	}

	LPGROUPPOS				pstGroupPos = NULL;
	CListNode < GROUPPOS >	*pNodeGroup;
	for ( pNodeGroup = g_xGameProc.m_stGroupPosList.GetHead(); pNodeGroup; pNodeGroup = pNodeGroup->GetNext() )
	{
		pstGroupPos = pNodeGroup->GetData();

		if ( pstGroupPos->nID == g_xGameProc.m_xInterface.m_xSiegeWnd.m_nIndex )
		{
			nSX = (INT)(rcScrn.left + pstGroupPos->nPosX*1.04f - m_rcView.left*0.7f - 1);
			nSY = (INT)(rcScrn.top + pstGroupPos->nPosY*0.59f - m_rcView.top*0.58f - 1);
		}

		if ( pstGroupPos )
		{
			if ( pstGroupPos->nID == g_xGameProc.m_xInterface.m_xSiegeWnd.m_nIndex )
				continue;

			nPosX = (INT)(rcScrn.left + pstGroupPos->nPosX*1.04f - m_rcView.left*0.7f - 1);
			nPosY = (INT)(rcScrn.top + pstGroupPos->nPosY*0.59f - m_rcView.top*0.58f - 1);

			if ( abs(nSX - nPosX) < m_nWidth/2 && abs(nSY - nPosY) < m_nHeight/2 )
			{
				SetRect(&rcCnt, nPosX-1, nPosY-1, nPosX+2, nPosY+2);

				if ( pstGroupPos->bMon )
				{
					g_xMainWnd.DrawWithGDI(&rcCnt, NULL, RGB(250, 150, 50), 2);
				}
				else
				{
					g_xMainWnd.DrawWithGDI(&rcCnt, NULL, RGB(100, 250, 100), 2);
				}
			}
		}
	}

	nPosX = (INT)(rcScrn.left + g_xGameProc.m_xMyHero.m_nPosX*1.04f - m_rcView.left*0.7f - 1);
	nPosY = (INT)(rcScrn.top + g_xGameProc.m_xMyHero.m_nPosY*0.59f - m_rcView.top*0.58f - 1);

	SetRect(&rcCnt, nPosX, nPosY, nPosX+4, nPosY+4);

	g_xMainWnd.DrawWithGDI(&rcCnt, NULL, RGB(100, 250, 100), 1);

	nPosX = (INT)(rcScrn.left + g_xGameProc.m_xInterface.m_xSiegeWnd.m_ptTarget.x*1.04f - m_rcView.left*0.7f - 1);
	nPosY = (INT)(rcScrn.top + g_xGameProc.m_xInterface.m_xSiegeWnd.m_ptTarget.y*0.59f - m_rcView.top*0.58f - 1);
	
	if ( abs(nSX - nPosX) < m_nWidth/2 && abs(nSY - nPosY) < (m_nHeight/2 - 3) )
	{
		if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(698))
		{
			g_xMainWnd.DrawWithImageForComp(nPosX - 2, nPosY - 9, g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
		}
	}

	SetRect(&rcCnt, nSX, nSY, nSX+3, nSY+3);

	g_xMainWnd.DrawWithGDI(&rcCnt, NULL, RGB(100, 250, 250), 2);
}



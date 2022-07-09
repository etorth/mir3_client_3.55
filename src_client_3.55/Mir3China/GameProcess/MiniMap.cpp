/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"



CMiniMap::CMiniMap()
{
}


CMiniMap::~CMiniMap()
{
	SAFE_RELEASE(m_pddsSurface);
	m_xMinimapData1.Destroy();
	m_xMinimapData2.Destroy();
}


VOID CMiniMap::InitMiniMap(LPDIRECT3DDEVICE7 pd3dDevice)
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

	m_bBlend	= FALSE;
//	m_bMultiple = FALSE;
	m_bMultiple = _FST_RATE;

	ZeroMemory(&m_rcBlend, sizeof(RECT));
	ZeroMemory(&m_rcMultiple, sizeof(RECT));
	ZeroMemory(&m_rcMapBook, sizeof(RECT));

	ZeroMemory(&m_ptGrasp, sizeof(POINT));
	ZeroMemory(&m_ptMyPos, sizeof(POINT));

    SAFE_RELEASE(m_pddsSurface);

	MiniMapSurface(pd3dDevice, 128, 128);

	m_xMinimapBtn[_NEW_BLEND_BTN].CreateGameBtn(g_xGameProc.m_xInterface.m_pxInterImg, 130, 130, 96, 114, g_xMsg.GetMsg(1800), _BTN_TYPE_FOCUS, 130, TRUE);
	m_xMinimapBtn[_NEW_EXPAND_BTN].CreateGameBtn(g_xGameProc.m_xInterface.m_pxInterImg, 132, 132, 116, 114, g_xMsg.GetMsg(1801), _BTN_TYPE_FOCUS, 132, TRUE);
	m_xMinimapBtn[_3rd_MAPBOOK_BTN].CreateGameBtn(g_xGameProc.m_xInterface.m_pxInterImg, 137, 137, 116, 114, g_xMsg.GetMsg(1801), _BTN_TYPE_FOCUS, 137, TRUE);
	
}


HRESULT CMiniMap::MiniMapSurface(LPDIRECT3DDEVICE7 pd3dDevice, INT nWidth, INT nHeight)
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


BOOL CMiniMap::SetMiniMap(INT nIdx)
{
	m_nMMapIdx	 = nIdx;

	if ( m_nMMapIdx >= 1000 )
	{
		if ( m_xMinimapData2.NewSetIndex(m_nMMapIdx-1000) )
		{
 			SetRect(&m_rcMiniMapRect, 0, 0, m_xMinimapData2.m_lpstNewCurrWilImageInfo->shWidth, m_xMinimapData2.m_lpstNewCurrWilImageInfo->shHeight);
			MiniMapSurface(g_xMainWnd.Get3DDevice(), m_nWidth, m_nHeight);
			return TRUE;
		}
	}
	else
	{
		if ( m_xMinimapData1.NewSetIndex(m_nMMapIdx) )
		{
 			SetRect(&m_rcMiniMapRect, 0, 0, m_xMinimapData1.m_lpstNewCurrWilImageInfo->shWidth, m_xMinimapData1.m_lpstNewCurrWilImageInfo->shHeight);
			MiniMapSurface(g_xMainWnd.Get3DDevice(), m_nWidth, m_nHeight);
			return TRUE;
		}
	}

	return FALSE;
}


VOID CMiniMap::MoveMiniMap(INT nX, INT nY)
{
	if ( m_nMMapIdx	== -1 )
	{
		return;
	}

	INT nSX, nSY;

	m_ptMyPos.x = nX;
	m_ptMyPos.y = nY;

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


VOID CMiniMap::RenderMiniMap(INT nLoopTime)
{
	if ( m_pddsSurface == NULL )
	{
		return;
	}

	D3DMATERIAL7 mtrl;
	D3DVECTOR	vecTrans((FLOAT)m_rcScrn.left, (FLOAT)m_rcScrn.top, 0);
	D3DVECTOR	vecScale((FLOAT)m_nWidth, (FLOAT)m_nHeight, 1);

	D3DUtil_InitMaterial(mtrl, (FLOAT)150/255.0f, (FLOAT)150/255.0f, (FLOAT)150/255.0f);
	if ( m_bBlend )
		mtrl.diffuse.a = 175.0f/255.0f;
	else 
		mtrl.diffuse.a = 255.0f/255.0f;

	g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, m_pddsSurface);

	RECT rcCnt;
	INT	 nSX, nSY;
	
	nSX = (INT)(m_rcScrn.left + m_ptMyPos.x*1.5f - m_rcView.left - 2);
	nSY = (INT)(m_rcScrn.top + m_ptMyPos.y - m_rcView.top - 2);

	g_xMainWnd.DrawWithGDI(&m_rcScrn, NULL, RGB(100, 100, 100), 1);

//	SetRect(&rcCnt, m_rcScrn.right-20, m_rcScrn.bottom, m_rcScrn.right, m_rcScrn.bottom+10);
//	g_xMainWnd.DrawWithGDI(&rcCnt, NULL, RGB(200, 200, 200), 2);

	SetRect(&m_rcMapBook, m_rcScrn.right-18, m_rcScrn.top + 34, m_rcScrn.right-3, m_rcScrn.top + 49);
	SetRect(&m_rcMultiple, m_rcScrn.right-18, m_rcScrn.top + 18, m_rcScrn.right-3, m_rcScrn.top + 33);
	SetRect(&m_rcBlend, m_rcScrn.right-18, m_rcScrn.top+ 2, m_rcScrn.right-3, m_rcScrn.top + 17);
	

	if ( m_bBlend )
		m_xMinimapBtn[_NEW_BLEND_BTN].ResetGameBtn(131, 131, 131);
	else
		m_xMinimapBtn[_NEW_BLEND_BTN].ResetGameBtn(130, 130, 130);

	if ( m_bMultiple == _FST_RATE )
	{
		m_xMinimapBtn[_NEW_EXPAND_BTN].ResetGameBtn(141, 141, 141);
	}
	else if ( m_bMultiple == _SND_RATE )
	{
		m_xMinimapBtn[_NEW_EXPAND_BTN].ResetGameBtn(132, 132, 132);
	}


	CActor*				pxActor = NULL;
	CListNode <CActor>	*pNode;
	INT					nPosX, nPosY;
	for ( pNode = g_xGameProc.m_xActorList.GetHead(); pNode; pNode = pNode->GetNext() )
	{
		pxActor = pNode->GetData();

		if ( pxActor )
		{
			if ( pxActor->m_stFeature.bGender == _GENDER_NPC )
			{
				nPosX = (INT)(m_rcScrn.left + pxActor->m_nPosX*1.5f - m_rcView.left - 1);
				nPosY = (INT)(m_rcScrn.top + pxActor->m_nPosY - m_rcView.top - 1);
				SetRect(&rcCnt, nPosX, nPosY, nPosX+2, nPosY+2);

				g_xMainWnd.DrawWithGDI(&rcCnt, NULL, RGB(255, 255, 0), 1);
			}

			// 세트아이템 : 몬스터의 위치를 보여준다.
			if ( m_bShowMonInfo )
			{
				if ( !pxActor->m_bIsDead )
				{
					if ( pxActor->m_stFeature.bGender == _GENDER_MON )
					{
						nPosX = (INT)(m_rcScrn.left + pxActor->m_nPosX*1.5f - m_rcView.left - 1);
						nPosY = (INT)(m_rcScrn.top + pxActor->m_nPosY - m_rcView.top - 1);
						SetRect(&rcCnt, nPosX, nPosY, nPosX+2, nPosY+2);

						g_xMainWnd.DrawWithGDI(&rcCnt, NULL, RGB(255, 0, 0), 2);
					}
					else if ( pxActor->m_stFeature.bGender == _GENDER_MAN || 
							  pxActor->m_stFeature.bGender == _GENDER_WOMAN )
					{
						nPosX = (INT)(m_rcScrn.left + pxActor->m_nPosX*1.5f - m_rcView.left - 1);
						nPosY = (INT)(m_rcScrn.top + pxActor->m_nPosY - m_rcView.top - 1);
						SetRect(&rcCnt, nPosX, nPosY, nPosX+2, nPosY+2);

						g_xMainWnd.DrawWithGDI(&rcCnt, NULL, RGB(255, 255, 255), 2);
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

		if ( pstGroupPos )
		{
			nPosX = (INT)(m_rcScrn.left + pstGroupPos->nPosX*1.5f - m_rcView.left - 1);
			nPosY = (INT)(m_rcScrn.top + pstGroupPos->nPosY - m_rcView.top - 1);

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

	SetRect(&rcCnt, nSX, nSY, nSX+4, nSY+4);
	m_nDelay += nLoopTime;
	if ( m_nDelay > 800 )
	{
		m_nDelay = 0;
	}
	if ( m_nDelay > 0 && m_nDelay < 500 )
	{
		g_xMainWnd.DrawWithGDI(&rcCnt, NULL, RGB(100, 250, 100), 1);
	}

	if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(134))
	{
		g_xMainWnd.DrawWithImageForComp(m_rcScrn.left, m_rcScrn.top, g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
	}

	if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(136))
	{
		g_xMainWnd.DrawWithImageForComp(m_rcScrn.right-25, m_rcScrn.bottom-25, g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
	}

	if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(135))
	{
		g_xMainWnd.DrawWithImageForComp(m_rcScrn.left, m_rcScrn.bottom-25, g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
	}
	// 맵이름 찍기
	CHAR pszBuff[MAX_PATH];
	RECT rcInfo = {m_rcScrn.left+3, 0, m_rcScrn.right-5, 15};
	
	sprintf(pszBuff, "%s", g_xGameProc.m_szMapName);
	g_xMainWnd.PutsHan(NULL, rcInfo, RGB(255, 255, 255), RGB(0,0,0), pszBuff);

	sprintf(pszBuff, "<%d,%d>", g_xGameProc.m_xMyHero.m_nPosX, g_xGameProc.m_xMyHero.m_nPosY);

	if ( m_bMultiple == _SND_RATE )
	{
		rcInfo.left = rcInfo.right-155;
		rcInfo.right = rcInfo.left+60;
	}
	else
	{
		rcInfo.left = rcInfo.right-90;
		rcInfo.right = rcInfo.left+60;
	}

	rcInfo.top = m_rcScrn.bottom - 15;
	rcInfo.bottom = rcInfo.top + 15;
	g_xMainWnd.PutsHan(NULL, rcInfo, RGB(255, 255, 255), RGB(0,0,0), pszBuff);

	m_xMinimapBtn[_NEW_BLEND_BTN].ChangeRect(m_rcScrn.right-17, m_rcScrn.top+3);
	m_xMinimapBtn[_NEW_EXPAND_BTN].ChangeRect(m_rcScrn.right-17, m_rcScrn.top+19);
	m_xMinimapBtn[_3rd_MAPBOOK_BTN].ChangeRect(m_rcScrn.right-17, m_rcScrn.top+35);

	SetRect(&m_rcMapBook, m_rcScrn.right-18, m_rcScrn.top + 34, m_rcScrn.right-3, m_rcScrn.top + 49);
	SetRect(&m_rcMultiple, m_rcScrn.right-18, m_rcScrn.top + 18, m_rcScrn.right-3, m_rcScrn.top + 33);
	SetRect(&m_rcBlend, m_rcScrn.right-18, m_rcScrn.top+ 2, m_rcScrn.right-3, m_rcScrn.top + 17);


	if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(143))
	{
		g_xMainWnd.DrawWithImageForComp(m_rcScrn.right - 20, m_rcScrn.top, g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
	}

	m_xMinimapBtn[_NEW_BLEND_BTN].ShowGameBtn();
	m_xMinimapBtn[_NEW_EXPAND_BTN].ShowGameBtn();
	m_xMinimapBtn[_3rd_MAPBOOK_BTN].ShowGameBtn();

/*
	CActor*				pxActor = NULL;
	CListNode <CActor>	*pNode;
	INT					nPosX, nPosY;

	for ( pNode = g_xGameProc.m_xActorList.GetHead(); pNode; pNode = pNode->GetNext() )
	{
		pxActor = pNode->GetData();

		if ( pxActor && !pxActor->m_bIsDead )
		{
			nPosX = (INT)(m_rcScrn.left + pxActor->m_nPosX*1.5f - m_rcView.left - 1);
			nPosY = (INT)(m_rcScrn.top + pxActor->m_nPosY - m_rcView.top - 1);
			SetRect(&rcCnt, nPosX, nPosY, nPosX+2, nPosY+2);

			if ( pxActor->m_stFeature.bGender == _GENDER_MAN || pxActor->m_stFeature.bGender == _GENDER_WOMAN )
			{
				g_xMainWnd.DrawWithGDI(&rcCnt, NULL, RGB(0, 255, 0), 2);
			}
			else if ( pxActor->m_stFeature.bGender == _GENDER_NPC )
			{
				nPosX = (INT)(m_rcScrn.left + pxActor->m_nPosX*1.5f - m_rcView.left - 1);
				nPosY = (INT)(m_rcScrn.top + pxActor->m_nPosY - m_rcView.top - 1);
				SetRect(&rcCnt, nPosX, nPosY, nPosX+2, nPosY+2);

				g_xMainWnd.DrawWithGDI(&rcCnt, NULL, RGB(255, 255, 0), 1);
			}
			else
			{
				g_xMainWnd.DrawWithGDI(&rcCnt, NULL, RGB(255, 0, 0), 2);
			}
		}
	}


	LPGROUPPOS				pstGroupPos = NULL;
	CListNode < GROUPPOS >	*pNodeGroup;
	for ( pNodeGroup = g_xGameProc.m_stGroupPosList.GetHead(); pNodeGroup; pNodeGroup = pNodeGroup->GetNext() )
	{
		pstGroupPos = pNodeGroup->GetData();

		if ( pstGroupPos )
		{
			nPosX = (INT)(m_rcScrn.left + pstGroupPos->nPosX*1.5f - m_rcView.left - 1);
			nPosY = (INT)(m_rcScrn.top + pstGroupPos->nPosY - m_rcView.top - 1);

			if ( abs(nSX - nPosX) < m_nWidth/2 && abs(nSY - nPosY) < m_nHeight/2 )
			{
				SetRect(&rcCnt, nPosX-1, nPosY-1, nPosX+2, nPosY+2);
				g_xMainWnd.DrawWithGDI(&rcCnt, NULL, RGB(100, 255, 255), 2);
			}
		}
	}
*/
}


BOOL CMiniMap::OnLButtonDown(POINT ptMouse)
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
		if ( m_bBlend )
		{
			m_xMinimapBtn[_NEW_BLEND_BTN].ResetGameBtn(130, 130, 130);
			m_xMinimapBtn[_NEW_BLEND_BTN].ChangeBtnTooltip(g_xMsg.GetMsg(1800));
		}
		else
		{
			m_xMinimapBtn[_NEW_BLEND_BTN].ResetGameBtn(131, 131, 131);
			m_xMinimapBtn[_NEW_BLEND_BTN].ChangeBtnTooltip(g_xMsg.GetMsg(1802));
		}

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
				m_xMinimapBtn[_NEW_EXPAND_BTN].ResetGameBtn(132, 132, 132);
				m_xMinimapBtn[_NEW_EXPAND_BTN].ChangeBtnTooltip(g_xMsg.GetMsg(1801));
				MiniMapSurface(g_xMainWnd.Get3DDevice(), 128, 128);
				break;
			}
			case _SND_RATE:
			{
				m_xMinimapBtn[_NEW_EXPAND_BTN].ResetGameBtn(141, 141, 141);
				m_xMinimapBtn[_NEW_EXPAND_BTN].ChangeBtnTooltip(g_xMsg.GetMsg(1803));
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


	if ( PtInRect(&m_rcMapBook, ptMouse) )
	{
		g_xGameProc.m_xInterface.WindowActivate(_WND_ID_VIEWMINIMAP);
		return TRUE;
	}

	return FALSE;
}


BOOL CMiniMap::OnLButtonUp(POINT ptMouse)
{
	return FALSE;
}


BOOL CMiniMap::OnMouseMove(POINT ptMouse)
{
/*	if ( PtInRect(&m_rcScrn, ptMouse) )
	{
		if ( ( HIBYTE(GetKeyState(VK_LBUTTON)) && HIBYTE(GetKeyState(VK_CONTROL))) )
		{
			SetRect(&m_rcScrn, ptMouse.x-m_ptGrasp.x, ptMouse.y-m_ptGrasp.y, 
					ptMouse.x-m_ptGrasp.x+m_nWidth, ptMouse.y-m_ptGrasp.y+m_nHeight); 

			return TRUE;
		}
	}
*/
	return FALSE;
}



HRESULT CMiniMap::ResetMiniMap(LPDIRECT3DDEVICE7 pd3dDevice)
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

VOID CMiniMap::SetInMainFrame()
{
	m_bMultiple = _INMAINFRAME_RATE;

	MiniMapSurface(g_xMainWnd.Get3DDevice(), 82, 100);

	m_rcScrn.left = 533;
	m_rcScrn.top = 482;
}


VOID CMiniMap::RenderMinimapInMain(INT nLoopTime)
{
	if ( m_pddsSurface == NULL )
	{
		return;
	}

	INT		nStartX, nStartY, nWidth, nHeight;
	RECT	rcScrn;

	if ( m_bMultiple == _SND_RATE )
	{
		if ( m_rcScrn.right - m_rcScrn.left < 256 )
		{
			nStartX = 530;
			nWidth = 128;
		}
		else
		{
			nStartX = 510;
			nWidth = 128;
		}
	}
	else
	{
		nStartX = 510;
		nWidth = 128;
	}

	if ( m_bMultiple == _SND_RATE )
	{
		if ( m_rcScrn.bottom - m_rcScrn.top < 256 )
		{
			nStartY = 485;
			nHeight = 128;//m_rcScrn.bottom - m_rcScrn.top;
		}
		else
		{
			nStartY = 470;
			nHeight = 128;
		}
	}
	else
	{
		nStartY = 470;
		nHeight = 128;
	}

	SetRect(&rcScrn, nStartX, nStartY, nStartX+nWidth, nStartY+nHeight);

	D3DMATERIAL7 mtrl;
	D3DVECTOR	vecTrans((FLOAT)nStartX, (FLOAT)nStartY, 0);
	D3DVECTOR	vecScale((FLOAT)nWidth, (FLOAT)nHeight, 1);

	D3DUtil_InitMaterial(mtrl, (FLOAT)150/255.0f, (FLOAT)150/255.0f, (FLOAT)150/255.0f);
    mtrl.diffuse.a = 255.0f/255.0f;

	g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, m_pddsSurface);

	RECT rcCnt;
	INT	 nSX, nSY;
	
	if ( m_bMultiple == _FST_RATE )
	{
		nSX = (INT)(nStartX + m_ptMyPos.x*1.5f - m_rcView.left - 2);
		nSY = (INT)(nStartY + m_ptMyPos.y - m_rcView.top - 2);
	}
	else
	{
		nSX = (INT)(nStartX + m_ptMyPos.x/2*1.5f - m_rcView.left/2 - 2);
		nSY = (INT)(nStartY + m_ptMyPos.y/2 - m_rcView.top/2 - 2);
	}

	g_xMainWnd.DrawWithGDI(&rcScrn, NULL, RGB(100, 100, 100), 1);

	CActor*				pxActor = NULL;
	CListNode <CActor>	*pNode;
	INT					nPosX, nPosY;
	for ( pNode = g_xGameProc.m_xActorList.GetHead(); pNode; pNode = pNode->GetNext() )
	{
		pxActor = pNode->GetData();

		if ( pxActor )
		{
			if ( pxActor->m_stFeature.bGender == _GENDER_NPC )
			{
				if ( m_bMultiple == _FST_RATE )
				{
					nPosX = (INT)(rcScrn.left + pxActor->m_nPosX*1.5f - m_rcView.left - 1);
					nPosY = (INT)(rcScrn.top + pxActor->m_nPosY - m_rcView.top - 1);
				}
				else
				{
					nPosX = (INT)(rcScrn.left + pxActor->m_nPosX/2*1.5f - m_rcView.left/2 - 1);
					nPosY = (INT)(rcScrn.top + pxActor->m_nPosY/2 - m_rcView.top/2 - 1);
				}

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
						if ( m_bMultiple == _FST_RATE )
						{
							nPosX = (INT)(rcScrn.left + pxActor->m_nPosX*1.5f - m_rcView.left - 1);
							nPosY = (INT)(rcScrn.top + pxActor->m_nPosY - m_rcView.top - 1);
						}
						else
						{
							nPosX = (INT)(rcScrn.left + pxActor->m_nPosX/2*1.5f - m_rcView.left/2 - 1);
							nPosY = (INT)(rcScrn.top + pxActor->m_nPosY/2 - m_rcView.top/2 - 1);
						}

						SetRect(&rcCnt, nPosX, nPosY, nPosX+2, nPosY+2);

						g_xMainWnd.DrawWithGDI(&rcCnt, NULL, RGB(255, 0, 0), 2);
					}
					else if ( pxActor->m_stFeature.bGender == _GENDER_MAN || 
							  pxActor->m_stFeature.bGender == _GENDER_WOMAN )
					{
						if ( m_bMultiple == _FST_RATE )
						{
							nPosX = (INT)(rcScrn.left + pxActor->m_nPosX*1.5f - m_rcView.left - 1);
							nPosY = (INT)(rcScrn.top + pxActor->m_nPosY - m_rcView.top - 1);
						}
						else
						{
							nPosX = (INT)(rcScrn.left + pxActor->m_nPosX/2*1.5f - m_rcView.left/2 - 1);
							nPosY = (INT)(rcScrn.top + pxActor->m_nPosY/2 - m_rcView.top/2 - 1);
						}

						SetRect(&rcCnt, nPosX, nPosY, nPosX+2, nPosY+2);

						g_xMainWnd.DrawWithGDI(&rcCnt, NULL, RGB(  0, 0, 255), 2);
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

		if ( pstGroupPos )
		{
			if ( m_bMultiple == _FST_RATE )
			{
				nPosX = (INT)(rcScrn.left + pstGroupPos->nPosX*1.5f - m_rcView.left - 1);
				nPosY = (INT)(rcScrn.top + pstGroupPos->nPosY - m_rcView.top - 1);
			}
			else
			{
				nPosX = (INT)(rcScrn.left + pstGroupPos->nPosX/2*1.5f - m_rcView.left/2 - 1);
				nPosY = (INT)(rcScrn.top + pstGroupPos->nPosY/2 - m_rcView.top/2 - 1);
			}

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

	SetRect(&rcCnt, nSX, nSY, nSX+4, nSY+4);
	m_nDelay += nLoopTime;
	if ( m_nDelay > 800 )
	{
		m_nDelay = 0;
	}
	if ( m_nDelay > 0 && m_nDelay < 500 )
	{
		g_xMainWnd.DrawWithGDI(&rcCnt, NULL, RGB(100, 250, 100), 1);
	}
}
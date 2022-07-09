#include "stdafx.h"



//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT CImageHandlerHelper::RestoreImg(sTextureNode* pstTextrNode)
{
    D3DDEVICEDESC7		ddDesc;
    DDSURFACEDESC2		ddsd;
	LPDIRECT3DDEVICE7	pd3dDevice = g_xMainWnd.Get3DDevice();
	DWORD				dwWidth, dwHeight;
	WORD*				pwSrc;

	if ( pstTextrNode == NULL )
	{
		return E_FAIL;
	}

	if ( pd3dDevice == NULL )
	{
		return E_FAIL;
	}

    if ( FAILED(pd3dDevice->GetCaps(&ddDesc)) )
	{
        return E_FAIL;
	}

	dwWidth = dwHeight = 0;
	pwSrc	= NULL;
	if ( pstTextrNode->pImg->NewSetIndex(pstTextrNode->nImgIdx) )
	{
		dwWidth  = pstTextrNode->pImg->m_lpstNewCurrWilImageInfo->shWidth;
		dwHeight = pstTextrNode->pImg->m_lpstNewCurrWilImageInfo->shHeight;
		pwSrc	 = (WORD*)pstTextrNode->pImg->m_pbCurrImage;			
	}
	else
	{
        return E_FAIL;
	}

//  D3DUtil_InitSurfaceDesc( ddsd );
    ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
    ddsd.dwSize          = sizeof(ddsd);
    ddsd.dwFlags         = DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps  = DDSCAPS_TEXTURE;
    ddsd.dwWidth         = dwWidth;
    ddsd.dwHeight        = dwHeight;

    if ( ddDesc.deviceGUID == IID_IDirect3DHALDevice || ddDesc.deviceGUID == IID_IDirect3DTnLHalDevice )
	{
        ddsd.ddsCaps.dwCaps2 = DDSCAPS2_TEXTUREMANAGE;
	}
    else
	{
        ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
	}

	// 2�� �������� ����.
    if ( ddDesc.dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_POW2 )
    {
        for ( ddsd.dwWidth =1; dwWidth>ddsd.dwWidth;   ddsd.dwWidth<<=1  );
        for ( ddsd.dwHeight=1; dwHeight>ddsd.dwHeight; ddsd.dwHeight<<=1 );
    }

    DWORD dwMaxWidth  = ddDesc.dwMaxTextureWidth;
    DWORD dwMaxHeight = ddDesc.dwMaxTextureHeight;
    ddsd.dwWidth  = min(ddsd.dwWidth,  (dwMaxWidth  ? dwMaxWidth  : 256));
    ddsd.dwHeight = min(ddsd.dwHeight, (dwMaxHeight ? dwMaxHeight : 256));

	// ���簢���� �ؽ��縦 �������� �ʴ´ٸ�.
    if ( ddDesc.dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_SQUAREONLY )
    {
        if ( ddsd.dwWidth > ddsd.dwHeight )
		{
			ddsd.dwHeight = ddsd.dwWidth;
		}
        else 
		{
			ddsd.dwWidth  = ddsd.dwHeight;
		}
    }

    LPDIRECTDRAW7 pDD =	g_xMainWnd.GetDirectDraw();

	if ( pDD == NULL )
	{
		return E_FAIL;
	}

    if ( FAILED(pDD->CreateSurface(&ddsd, &pstTextrNode->pSurface, NULL)) )
	{
        return E_FAIL;
	}

	if ( ddsd.dwWidth == dwWidth && ddsd.dwHeight == dwHeight )
	{
		if ( CopyDToS(dwWidth, dwHeight, pwSrc, pstTextrNode->pSurface) == E_FAIL )
		{
			SAFE_RELEASE(pstTextrNode->pSurface);
			return E_FAIL;
		}
	}
	else
	{
		if ( CopyDToSToS(dwWidth, dwHeight, pwSrc, pstTextrNode->pSurface) == E_FAIL )
		{
			SAFE_RELEASE(pstTextrNode->pSurface);
			return E_FAIL;
		}
	}

	// �÷�Ű�� �����Ѵ�.
	DDSetColorKey(pstTextrNode->pSurface, RGB(0, 0, 0));

    return S_OK;
}


HRESULT CImageHandlerHelper::CopyDToSToS(DWORD dwWidth, DWORD dwHeight, WORD* pwSrc, LPDIRECTDRAWSURFACE7 lpddsDst)
{
	HRESULT					hr;
    DDSURFACEDESC2			ddsd;
    LPDIRECTDRAWSURFACE7	pddsTempSurface;
	LPDIRECTDRAW7			pDD = g_xMainWnd.GetDirectDraw();

	if ( pDD == NULL )
	{
		return E_FAIL;
	}

    ddsd.dwSize = sizeof(DDSURFACEDESC2);
    lpddsDst->GetSurfaceDesc(&ddsd);
    ddsd.dwFlags         = DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps  = DDSCAPS_TEXTURE|DDSCAPS_SYSTEMMEMORY;
    ddsd.ddsCaps.dwCaps2 = 0L;
    ddsd.dwWidth         = dwWidth;
    ddsd.dwHeight        = dwHeight;

    if ( FAILED(pDD->CreateSurface(&ddsd, &pddsTempSurface, NULL)) )
    {
        return E_FAIL;
    }

	LONG	lWidth;
    DDSURFACEDESC2	ddsdLock;
	ZeroMemory(&ddsdLock, sizeof(DDSURFACEDESC2));
	ddsdLock.dwSize = sizeof(DDSURFACEDESC2);
	if ( FAILED(pddsTempSurface->Lock(NULL, &ddsdLock, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL)) )
	{
		SAFE_RELEASE(pddsTempSurface);
		return E_FAIL;
	}
    WORD* pwdDst = (WORD*)ddsdLock.lpSurface;
	lWidth		 = ddsdLock.lPitch >> 1;
			
	INT nWidthStart		= 0;
	INT nWidthEnd		= 0;
	INT nCurrWidth		= 0;
	INT nCntCopyWord	= 0;
	INT nYCnt			= 0;
	INT nLastWidth		= 0;

	// y�࿡ ���ؼ� ������ ���ν�ų Count���� ���Ѵ�.
	for ( nYCnt = 0; nYCnt < dwHeight ; nYCnt++ )
	{
		// �Ѷ����� ���̸� ���´�.(������ ����)
		nWidthEnd += pwSrc[nWidthStart];
		nWidthStart++;
		
		// ������ ���̸�ŭ ȭ�鿡 �ѷ��ش�.
		for ( INT x = nWidthStart; x < nWidthEnd ; )
		{
			if ( pwSrc[x] == 0xC0 )
			{
				x++;
				nCntCopyWord = pwSrc[x];
				x++;

				nLastWidth = nCurrWidth;
				nCurrWidth += nCntCopyWord;

				memset(&pwdDst[((nYCnt) * lWidth) + (nLastWidth)], 0, sizeof(WORD)*nCntCopyWord);
			}
			else if ( pwSrc[x] == 0xC1 || pwSrc[x] == 0xC2 || pwSrc[x] == 0xC3 )
			{
				x++;
				nCntCopyWord = pwSrc[x];
				x++;

				nLastWidth = nCurrWidth;
				nCurrWidth += nCntCopyWord;

				memcpy(&pwdDst[((nYCnt) * lWidth) + (nLastWidth)], &pwSrc[x], sizeof(WORD)*nCntCopyWord);

				x += nCntCopyWord;
			}
		}
		// ������ ���� ���� ������ �������� �Ű��ش�.
		nWidthEnd++;

		nWidthStart	= nWidthEnd;
		nCurrWidth = 0;
	}

	pddsTempSurface->Unlock(NULL);

	while ( TRUE )
	{
		hr = lpddsDst->Blt(NULL, pddsTempSurface, NULL, DDBLT_WAIT, NULL);

		if ( hr == DDERR_SURFACELOST )
		{
			lpddsDst->Restore();
		}

//		if ( hr == DD_OK )
		if ( hr != DDERR_WASSTILLDRAWING )
		{
			SAFE_RELEASE(pddsTempSurface);
		    return S_OK;
		}
	} 
	
	return E_FAIL;
}


HRESULT CImageHandlerHelper::CopyDToS(DWORD dwWidth, DWORD dwHeight, WORD* pwSrc, LPDIRECTDRAWSURFACE7 lpddsDst)
{
	RECT			rc;
	HRESULT			hr;
	DDSURFACEDESC2	ddsd;
	
	LONG	lWidth;
	ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
	ddsd.dwSize = sizeof(DDSURFACEDESC2);
	if ( FAILED(lpddsDst->Lock(NULL, &ddsd, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL)) )
	{
		return E_FAIL;
	}

    WORD* pwdDst = (WORD*)ddsd.lpSurface;
	lWidth		 = ddsd.lPitch >> 1;

	INT nWidthStart		= 0;
	INT nWidthEnd		= 0;
	INT nCurrWidth		= 0;
	INT nCntCopyWord	= 0;
	INT nYCnt			= 0;
	INT nLastWidth		= 0;

	// y�࿡ ���ؼ� ������ ���ν�ų Count���� ���Ѵ�.
	for ( nYCnt = 0 ; nYCnt < dwHeight ; nYCnt++ )
	{
		// �Ѷ����� ���̸� ���´�.(������ ����)
		nWidthEnd += pwSrc[nWidthStart];
		nWidthStart++;
		
		// ������ ���̸�ŭ ȭ�鿡 �ѷ��ش�.
		for ( INT x = nWidthStart; x < nWidthEnd ; )
		{
			if ( pwSrc[x] == 0xC0 )
			{
				x++;
				nCntCopyWord = pwSrc[x];
				x++;

				nLastWidth = nCurrWidth;
				nCurrWidth += nCntCopyWord;

				memset(&pwdDst[((nYCnt) * lWidth) + (nLastWidth)], 0, sizeof(WORD)*nCntCopyWord);
			}
			else if ( pwSrc[x] == 0xC1 || pwSrc[x] == 0xC2 || pwSrc[x] == 0xC3 )
			{
				x++;
				nCntCopyWord = pwSrc[x];
				x++;

				nLastWidth = nCurrWidth;
				nCurrWidth += nCntCopyWord;

				memcpy(&pwdDst[((nYCnt) * lWidth) + (nLastWidth)], &pwSrc[x], sizeof(WORD)*nCntCopyWord);

				x += nCntCopyWord;
			}
		}
		// ������ ���� ���� ������ �������� �Ű��ش�.
		nWidthEnd++;

		nWidthStart	= nWidthEnd;
		nCurrWidth = 0;
	}

	lpddsDst->Unlock(NULL);

	return S_OK;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------






CImageHandlerHelper::CImageHandlerHelper( CWHWilImageData *pListImage )
{
	m_pListImage = pListImage;

	m_listTexture.InitHashTable( MAX_HASHSIZE, IHT_ROUNDUP );
	m_listTexture.SetGetKeyFunction( __cbTextureKey );
}


CImageHandlerHelper::~CImageHandlerHelper()
{
	m_listTexture.UninitHashTable();
	m_pListImage = NULL;
}


void CImageHandlerHelper::CheckAllCachedTexture()
{
	if ( GetTickCount() - m_nLastTick > TEXTURE_CHECKALLTIME )
	{
		CListNode< sTextureNode >	*pNode = m_listTexture.GetHead();
		CListNode< sTextureNode >	*pTemp;
		sTextureNode				*pObj = NULL;

		while ( pNode )
		{
			pObj = pNode->GetData();

			if ( GetTickCount() - pObj->nLastTick >= TEXTURE_SAVETIME )
			{
				pTemp = pNode->GetNext();

				m_listTexture.Remove( pObj );

				SAFE_RELEASE(pObj->pSurface);
				SAFE_DELETE(pObj);

				pNode = pTemp;
			}
			else
			{
				pNode = pNode->GetNext();
			}
		}

		m_nLastTick = GetTickCount();
	}
}


IDirectDrawSurface7* CImageHandlerHelper::AddTexture( WORD nFileType, WORD nFileIdx, WORD nImgIdx )
{
	if ( !m_pListImage[ nFileIdx ].NewSetIndex( nImgIdx ) )
	{
		return NULL;
	}

	sTextureNode *pObj = new sTextureNode;

	sprintf( pObj->szKey, "%05d%05d%05d", nFileType, nFileIdx, nImgIdx );
	pObj->nFileType	= nFileType;
	pObj->nFileIdx	= nFileIdx;
	pObj->nImgIdx	= nImgIdx;
	pObj->pImg		= &m_pListImage[ nFileIdx ];
	pObj->nLastTick	= GetTickCount();
	pObj->pSurface	= NULL;
	if ( RestoreImg(pObj) == E_FAIL )
	{
		SAFE_DELETE(pObj);
		return NULL;
	}

	m_listTexture.Insert( pObj );
	return pObj->pSurface;
}


IDirectDrawSurface7 * CImageHandlerHelper::GetTexture( WORD nFileType, WORD nFileIdx, WORD nImgIdx )
{
	sTextureNode *pObj = FindTexture( nFileType, nFileIdx, nImgIdx );

	if ( !pObj )
	{
		return AddTexture( nFileType, nFileIdx, nImgIdx );
	}

	pObj->nLastTick = GetTickCount();

	return pObj->pSurface;
}


void CImageHandlerHelper::DelTexture( WORD nFileType, WORD nFileIdx, WORD nImgIdx )
{
	sTextureNode *pObj = FindTexture( nFileType, nFileIdx, nImgIdx );
	if ( pObj )
	{
		m_listTexture.Remove( pObj );
		SAFE_RELEASE(pObj->pSurface);
		SAFE_DELETE(pObj);
	}
}


void CImageHandlerHelper::DelAllTexture()
{
	CListNode< sTextureNode >	*pNode = m_listTexture.GetHead();
	CListNode< sTextureNode >	*pTemp;
	sTextureNode				*pObj = NULL;

	while ( pNode )
	{
		pObj = pNode->GetData();

		pTemp = pNode->GetNext();

		m_listTexture.Remove( pObj );
		SAFE_RELEASE(pObj->pSurface);
		SAFE_DELETE(pObj);

		pNode = pTemp;
	}
}


char * CImageHandlerHelper::__cbTextureKey( CImageHandlerHelper::sTextureNode *pNode )
{
	return pNode->szKey;
}


CImageHandlerHelper::sTextureNode * CImageHandlerHelper::FindTexture( WORD nFileType, WORD nFileIdx, WORD nImgIdx )
{
	char szKey[16];
	sprintf( szKey, "%05d%05d%05d", nFileType, nFileIdx, nImgIdx );

	return m_listTexture.SearchKey( szKey );
}
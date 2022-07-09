/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#include "stdafx.h"
#include "WHEngine.h"



/******************************************************************************************************************

	함수명 : CWHSurface::ReleaseSurface()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CWHSurface::ReleaseSurface()
{
	if ( m_pDDS )
	{
		m_pDDS->Release();
		m_pDDS = NULL;

		return TRUE;
	}

	return FALSE;
}



/******************************************************************************************************************

	함수명 : CWHSurface::CreateOffScreenSurface()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : LPDIRECTDRAW7 pDD
	         DWORD dwXSize
	         DWORD dwYSize
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CWHSurface::CreateOffScreenSurface(LPDIRECTDRAW7 pDD, DWORD dwXSize, DWORD dwYSize) 
{
	HRESULT					hr;
	DDSURFACEDESC2			ddsd;

	ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));

	ddsd.dwSize			= sizeof(DDSURFACEDESC2);
	ddsd.dwFlags		= DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
	ddsd.dwWidth		= dwXSize;
	ddsd.dwHeight		= dwYSize;

	hr = pDD->CreateSurface(&ddsd, &m_pDDS, NULL);

	if ( hr != DD_OK )	return FALSE;

	return TRUE;
}



/******************************************************************************************************************

	함수명 : CWHSurface::CopyImageToSurface()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : DWORD dwSrcWidth
	         DWORD dwSrcHeight
	         WORD* pwSrc
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CWHSurface::CopyImageToSurface(DWORD dwSrcWidth, DWORD dwSrcHeight, WORD* pwSrc)
{
	DDSURFACEDESC2			ddsd;
	WORD*					pwdDst = NULL;

	ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));

	ddsd.dwSize	= sizeof(DDSURFACEDESC2);
	
	if (m_pDDS->Lock(NULL, &ddsd, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL) == DD_OK)
	{
		pwdDst = (WORD*)ddsd.lpSurface;

		CopyMemory(pwdDst, pwSrc, dwSrcWidth * dwSrcHeight * sizeof(WORD));

		m_pDDS->Unlock(NULL);

		DDCOLORKEY              ddck;
		ddck.dwColorSpaceLowValue =  RGB( 0,  0,  0);
		ddck.dwColorSpaceHighValue = RGB(10, 10, 10);
		m_pDDS->SetColorKey(DDCKEY_SRCBLT, &ddck);

		return TRUE;
	}

	return FALSE;
}

BOOL CWHSurface::CopyImageToSurfaceDx(DWORD dwSrcWidth, DWORD dwSrcHeight, DWORD dwDestWidth, WORD* pwSrc)
{
	DDSURFACEDESC2			ddsd;
	WORD*					pwdDst = NULL;

	ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));

	ddsd.dwSize	= sizeof(DDSURFACEDESC2);
	
	if (m_pDDS->Lock(NULL, &ddsd, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL) == DD_OK)
	{
		pwdDst = (WORD*)ddsd.lpSurface;

		int  i;
		for (i=0; i<dwSrcHeight; i++) {

			CopyMemory(pwdDst, pwSrc, dwSrcWidth * sizeof(WORD));
			pwdDst = pwdDst + dwDestWidth;
			pwSrc  = pwSrc + dwSrcWidth;
			
		}
		m_pDDS->Unlock(NULL);

		DDCOLORKEY              ddck;
		ddck.dwColorSpaceLowValue =  RGB( 0,  0,  0);
		ddck.dwColorSpaceHighValue = RGB(10, 10, 10);
		m_pDDS->SetColorKey(DDCKEY_SRCBLT, &ddck);

		return TRUE;
	}

	return FALSE;
}


BOOL CWHSurface::DDLoadBitmap(IDirectDraw7 * pdd, LPCSTR szBitmap, int dx, int dy)
{
    HBITMAP                 hbm;
    BITMAP                  bm;

	ReleaseSurface();

    //
    //  Try to load the bitmap as a resource, if that fails, try it as a file
    //
    hbm = (HBITMAP) LoadImage(GetModuleHandle(NULL), szBitmap, IMAGE_BITMAP, dx, dy, LR_CREATEDIBSECTION);
    if (hbm == NULL)
	{
        hbm = (HBITMAP) LoadImage(NULL, szBitmap, IMAGE_BITMAP, dx, dy, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	}
    if (hbm == NULL)
	{
        return FALSE;
	}
    //
    // Get size of the bitmap
    //
    GetObject(hbm, sizeof(bm), &bm);
    //
    // Create a DirectDrawSurface for this bitmap
    //

	if ( CreateOffScreenSurface(pdd, bm.bmWidth, bm.bmHeight) )
	{
		DDCopyBitmap(hbm, 0, 0, 0, 0);
		DeleteObject(hbm);

		DDCOLORKEY	ddck;
		ddck.dwColorSpaceLowValue  = RGB(0, 0, 0);
		ddck.dwColorSpaceHighValue = RGB(1, 1, 1);
		m_pDDS->SetColorKey(DDCKEY_SRCBLT, &ddck);
	}

    return TRUE;
}


HRESULT CWHSurface::DDCopyBitmap(HBITMAP hbm, int x, int y, int dx, int dy)
{
    HDC                     hdcImage;
    HDC                     hdc;
    BITMAP                  bm;
    DDSURFACEDESC2          ddsd;
    HRESULT                 hr;

    if (hbm == NULL || m_pDDS == NULL)
	{
        return E_FAIL;
	}
    //
    // Make sure this surface is restored.
    //
    m_pDDS->Restore();
    //
    // Select bitmap into a memoryDC so we can use it.
    //
    hdcImage = CreateCompatibleDC(NULL);
    if (!hdcImage)
	{
        OutputDebugString("createcompatible dc failed\n");
	}

    SelectObject(hdcImage, hbm);
    //
    // Get size of the bitmap
    //
    GetObject(hbm, sizeof(bm), &bm);
    dx = dx == 0 ? bm.bmWidth  : dx;     // Use the passed size, unless zero
    dy = dy == 0 ? bm.bmHeight : dy;
    //
    // Get size of surface.
    //
    ddsd.dwSize  = sizeof(ddsd);
    ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH;
    m_pDDS->GetSurfaceDesc(&ddsd);
    
    if ((hr = m_pDDS->GetDC(&hdc)) == DD_OK)
    {
        StretchBlt(hdc, 0, 0, ddsd.dwWidth, ddsd.dwHeight, hdcImage, x, y, dx, dy, SRCCOPY);
        m_pDDS->ReleaseDC(hdc);
    }

    DeleteDC(hdcImage);

    return hr;
}

HRESULT CWHSurface::Draw(LPDIRECTDRAWSURFACE7 pddsDst, RECT* prcDst)
{
	HRESULT hr;

	if ( NULL == pddsDst )
	{
		return E_POINTER;
	}

	while ( TRUE )
	{
		hr = pddsDst->Blt(prcDst, m_pDDS, NULL, DDBLT_WAIT, NULL);

		if ( hr != DDERR_WASSTILLDRAWING )
		{
			return hr;
		}
	} 
}

#ifndef _WINDHORN_SURFACE
#define	_WINDHORN_SURFACE


class CWHSurface
{
protected:
	LPDIRECTDRAWSURFACE7	m_pDDS;

public:
	__inline CWHSurface()	{ m_pDDS = NULL; }
	__inline CWHSurface(LPDIRECTDRAW7 pDD, DWORD dwXSize, DWORD dwYSize) { CreateOffScreenSurface(pDD, dwXSize, dwYSize); }
	__inline ~CWHSurface()	{ ReleaseSurface(); }

public:
	BOOL		CreateOffScreenSurface(LPDIRECTDRAW7 pDD, DWORD dwXSize, DWORD dwYSize);
	BOOL		CopyImageToSurface(DWORD dwSrcWidth, DWORD dwSrcHeight, WORD* pwSrc);
	BOOL		CopyImageToSurfaceDx(DWORD dwSrcWidth, DWORD dwSrcHeight, DWORD dwDestWidth, WORD* pwSrc);
	BOOL		ReleaseSurface();

	BOOL		DDLoadBitmap(IDirectDraw7 *pdd, LPCSTR szBitmap, int dx = 0, int dy = 0);
	HRESULT     DDCopyBitmap(HBITMAP hbm, int x, int y, int dx, int dy);

	HRESULT		Draw(LPDIRECTDRAWSURFACE7 pddsDst, RECT* prcDst);

	__inline LPDIRECTDRAWSURFACE7 GetSur()	{ return m_pDDS; }
	__inline BOOL CopyImageToSurface(CWHImage* xImage) { return CopyImageToSurface(xImage->m_wWidth, xImage->m_wHeight, xImage->m_pwImage); }
};



#endif //_WINDHORN_SURFACE

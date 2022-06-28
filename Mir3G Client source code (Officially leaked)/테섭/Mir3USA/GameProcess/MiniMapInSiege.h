#ifndef _CMINIMAPINSIEGE_H
#define _CMINIMAPINSIEGE_H



/******************************************************************************************************************

	CMiniMapInSiege Class

*******************************************************************************************************************/


//#define _MMAP_WIDTH	256
//#define _MMAP_HEIGHT	256
#define _FST_RATE			0
#define _SND_RATE			1
#define _TRD_RATE			2
#define _FOURTH_RATE		3
#define _INMAINFRAME_RATE	4


class CMiniMapInSiege
{
public:
	CMiniMapInSiege();
	~CMiniMapInSiege();

    LPDIRECTDRAWSURFACE7	m_pddsSurface;				// Texture Img Surface;
	
	CWHWilImageData			m_xMinimapData1;
	CWHWilImageData			m_xMinimapData2;
	INT						m_nMMapIdx;

// 옵션관련. 블렌드와, 영역확대.
	BOOL					m_bBlend;
	BYTE					m_bMultiple;

	RECT					m_rcBlend;
	RECT					m_rcMultiple;

	INT						m_nWidth;
	INT						m_nHeight;

	RECT					m_rcScrn;
	RECT					m_rcView;
	RECT					m_rcMiniMapRect;

	POINT					m_ptGrasp;

	POINT					m_ptMyPos;

	POINT					m_ptMySiegePos;

	INT						m_nDelay;

	BOOL					m_bShowMonInfo;



	VOID	InitMiniMap(LPDIRECT3DDEVICE7 pd3dDevice);
	HRESULT MiniMapSurface(LPDIRECT3DDEVICE7 pd3dDevice, INT nWidth, INT nHeight);

	BOOL	SetMiniMap(INT nIdx);
	BOOL	ReleaseMiniMap();
	VOID	MoveMiniMap(INT nX, INT nY);

	BOOL	OnLButtonDown(POINT ptMouse);
	BOOL	OnLButtonUp(POINT ptMouse);
	BOOL	OnRButtonDown(POINT ptMouse);
	BOOL	OnMouseMove(POINT ptMouse);
	VOID	SetInMainFrame();
	VOID	RenderMinimapInMain(INT nLoopTime);
	
	HRESULT	ResetMiniMap(LPDIRECT3DDEVICE7 pd3dDevice);
};



#endif // _CMiniMapInSiege_H
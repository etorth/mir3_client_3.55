#ifndef _CSIEGEWND_H
#define _CSIEGEWND_H


class CSiegeWnd : public CGameWnd
{ 
// Constructor & Destructor
public:
	CSiegeWnd();
	~CSiegeWnd();
// Attributes
public:
	CGameBtn		m_xSiegeBtn[_MAX_SIEGE_BTN];

	INT				m_nLoadedBullet;
	INT				m_nMaxBullet;

	POINT			m_ptTarget;
	RECT			m_rcMinimap;

	RECT			m_rcMaxRange;
	RECT			m_rcMinRange;

	RECT			m_rcRadar;

	BOOL			m_bIncrease;
	INT				m_nIndex;

	INT				m_nKind;


// Operations
public:
	virtual VOID Init();
	virtual VOID Destroy();

	VOID	CreateSiegeWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove);
	VOID	ShowSiegeWnd();
	
	BOOL	OnLButtonDown(POINT ptMouse);
	BOOL	OnLButtonUp(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse);
	VOID	OnMouseMove(POINT ptMouse);
};


#endif // _CSIEGEWND_H
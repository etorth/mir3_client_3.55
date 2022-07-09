#ifndef _VIEWMINIMAPWND_H
#define _VIEWMINIMAPWND_H


typedef struct tagCLIENTMINIMAPVIEWER
{
	INT				nMinimapIdx;
	char*			pszMinimapName;
}CLIENTMINIMAPVIEWER, *LPCLIENTMINIMAPVIEWER;


class CViewMiniMapWnd : public CGameWnd
{ 
// Constructor & Destructor
public:
	CViewMiniMapWnd();
	~CViewMiniMapWnd();
// Attributes
public:
	CGameBtn					mViewMiniMap_BtnClose;					// ´Ý±â
	CGameBtn					mViewMiniMap_Btn2x;						// 2¹è
	CGameBtn					mViewMiniMap_Btn1x;						// 1¹è
	CGameBtn					mViewMiniMap_BtnHalfx;					// 1/2¹è
	
	CList<CLIENTMINIMAPVIEWER>	mViewMiniMap_xInfo;

	CHAR						mViewMiniMap_szMenu[_MAX_MENU][30];
	CHAR						mViewMiniMap_szSelectedMapName[30];

	RECT						mViewMiniMap_rcMenu[_MAX_MENU];

	INT							mViewMiniMap_nSelectedNum;
	INT							mViewMiniMap_nMouseLocated;

	INT							mViewMiniMap_nSelectedMapIdx;

	BOOL						mViewMiniMap_bIsLoad;

	CWHWilImageData				mViewMiniMap_xMinimapData1;
	CWHWilImageData				mViewMiniMap_xMinimapData2;

	LPDIRECTDRAWSURFACE7		mViewMiniMap_pddsSurface;				// Texture Img Surface;

	RECT						mViewMiniMap_rcMiniMapRect;
	RECT						mViewMiniMap_rcScrn;

	INT							mViewMiniMap_nMiniMapWidth;
	INT							mViewMiniMap_nMiniMapHeight;

	INT							mViewMiniMap_nMultiple;

	INT							mViewMiniMap_nMinimapCnt;
	INT							mViewMiniMap_nMunuStart;
	CScrlBar					mViewMiniMap_xScrSelectMenu;

	INT							mViewMiniMap_nMapHeight;
	INT							mViewMiniMap_nStartYMap;
	CScrlBar					mViewMiniMap_xScrVerMap;

	INT							mViewMiniMap_nMapWidth;
	INT							mViewMiniMap_nStartXMap;
	CScrlBar					mViewMiniMap_xScrHorMap;
	
	RECT						mViewMiniMap_rcShowMenu;
	RECT						mViewMiniMap_rcMap;
	
// Operations
public:
	virtual VOID			Init();
	virtual VOID			Destroy();

	VOID					CreateViewMiniMapWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove);
	VOID					ShowViewMiniMapWnd();

	BOOL					OnLButtonDown(POINT ptMouse);
	BOOL					OnLButtonUp(POINT ptMouse);
	BOOL					OnMouseMove(POINT ptMouse);
	BOOL					OnKeyDown(WPARAM wParam, LPARAM lParam);

	VOID					OnScrollDown();
	VOID					OnScrollUp();

	BOOL					LoadMIF();
	VOID					DelAllMIF();
	VOID					ReadMapNameFromMIF();

	BOOL					SetMiniMap(INT nIdx);
	VOID					RenderMiniMap();
	VOID					RenderMiniMap2();
	HRESULT					MiniMapSurface(LPDIRECT3DDEVICE7 pd3dDevice, INT nWidth, INT nHeight);

	VOID					SetMiniMapSize();
};



#endif // _UTILWND_H
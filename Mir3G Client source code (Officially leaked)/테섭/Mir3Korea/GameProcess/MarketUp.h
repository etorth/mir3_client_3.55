#ifndef _MARKETUPWND_H
#define _MARKETUPWND_H






class CMarketUpWnd : public CGameWnd
{ 
// Constructor & Destructor
public:
	CMarketUpWnd();
	~CMarketUpWnd();
// Attributes
public:
	CGameBtn				mUserMarketUp_BtnClose;
	CGameBtn				mUserMarketUp_BtnCancel;
	CGameBtn				mUserMarketUp_BtnRegistry;

	CItem					mUserMarketUp_xItem;

	RECT					mUserMarketUp_rcShowItem;
	RECT					mUserMarketUp_rcGold;

	INT						mUserMarketUp_nPrice;
	INT						mUserMarketUp_nNpcId;
	
	HWND					mUserMarketUp_hDescEdit;

	RECT					mUserMarketUp_rcEditBox;

	BOOL					mUserMarketUp_bSetItemPrice;
	BOOL					mUserMarketUp_bItemSet;


public:
	virtual VOID Init();
	virtual VOID Destroy();

	VOID	CreateUserMarketWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend);
	VOID	ShowUserMarketUpWnd();

	BOOL	OnLButtonDown(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse);
	BOOL	OnLButtonUp(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse);

	BOOL	OnRButtonDown(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse);
	BOOL	OnMouseMove(POINT ptMouse);

	BOOL	OnKeyDown(WPARAM wParam, LPARAM lParam);

	VOID	SetItemDesc();
	
	VOID	CloseMarketUpWnd();
	VOID	RegistMyItem();
};



#endif // _MARKETUPWND_H
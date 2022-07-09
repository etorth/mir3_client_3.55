#ifndef _MARKETWND_H
#define _MARKETWND_H



typedef struct tagCLIENTSELLITEM	 
{
	CHAR			szServer[13];
	INT				nSellIndex;
	CHAR			szSellWho[25];
	CHAR			szItemName[25];
	INT				nSellPrice;
	CHAR			szSellDate[15];

	CLIENTITEMRCD	stItem;

	CHAR			szText[121];
}CLIENTSELLITEM, *LPCLIENTSELLITEM;




class CMarketWnd : public CGameWnd
{ 
// Constructor & Destructor
public:
	CMarketWnd();
	~CMarketWnd();
// Attributes
public:
	CGameBtn				mUserMarket_BtnClose;
	CGameBtn				mUserMarket_BtnDetailClose;
	CGameBtn				mUserMarket_BtnBuy;
	CGameBtn				mUserMarket_BtnRegistry;
	CGameBtn				mUserMarket_BtnFindItem;
	CGameBtn				mUserMarket_BtnFindWriter;
	CGameBtn				mUserMarket_BtnRefresh;
	CGameBtn				mUserMarket_BtnNext;
	CGameBtn				mUserMarket_BtnBefore;


	CList<CLIENTSELLITEM>	m_xMarketItemList;

	BOOL					mUserMarket_bSelectedFindItem;
	BOOL					mUserMarket_bSelectedFindName;
	BOOL					mUserMarket_bReadytoGet;

	RECT					mUserMarket_rcList[_MAX_MARKETCELL];
	RECT					mUserMarket_rcShowItem;
	RECT					mUserMarket_rcFindItem;
	RECT					mUserMarket_rcFindName;

	INT						mUserMarket_nMouseLocated;
	INT						mUserMarket_nSelected;
	INT						mUserMarket_nNpcId;
	INT						mUserMarket_nCurPage;
	INT						mUserMarket_nTotalPage;
	INT						mUserMarket_nIconFrame;

	CList<CHAT>				mUserMarket_xDesclist;			// 아이템 설명
	
	CItem					mUserMarket_xShowItem;

	DWORD					mUserMarket_dwLastSendTime;
	DWORD					mUserMarket_dwIconTimer;

public:
	virtual VOID Init();
	virtual VOID Destroy();

	VOID	CreateUserMarketWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend);
	VOID	ShowUserMarketWnd();

	BOOL	OnLButtonDown(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse);
	BOOL	OnLButtonUp(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse);

	BOOL	OnRButtonDown(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse);
	BOOL	OnMouseMove(POINT ptMouse);

	VOID	OnScrollUp();
	VOID	OnScrollDown();

	BOOL	OnKeyDown(WPARAM wParam, LPARAM lParam);

	VOID	SetMarketItemList(CHAR* pszMsg, INT nCount, INT nPage, INT nTotalPage);
	VOID	SetItemDesc();
	VOID	SendFindMsg();

	VOID	CloseMarketWnd();

	VOID	BuyItem();
	VOID	TakeBackMarketItem();
};



#endif // _MARKETWND_H
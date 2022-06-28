// InventoryExWnd.h


#ifndef _INVENTORYEXWND_H_
#define _INVENTORYEXWND_H_

class CInventoryExWnd : public CGameWnd
{ 
protected:
	BYTE		m_bType;							// 가방창, 수리창, 상점팔기창.

	INT			m_nStartLineNum;					// 인벤토리창의 처음 라인의 번호. (총 10줄이고 화면에는 4줄 까지 볼수 있다.)

	CGameBtn	m_xInventoryBtn[_MAX_INVEN_BTN];
	CScrlBar	m_xInvenScrlBar;

public:
	SHORT		 m_shItemSetInfo[_INVEN_TOTAL_CELL];
	INVENITEMSET m_stInventoryItem[_MAX_INVENEX_ITEM];

	PARKITEM	 m_stParkItem;
	INT			 m_nMerchantID;
	CHAR		 m_pszPrice[20];
	INT			 m_nPrice;

	DWORD		 m_dwDLClickTime;
	DWORD		 m_dwLClickTime;
	DWORD		 m_dwRClickTime;

public:
	CInventoryExWnd();
	~CInventoryExWnd();

	virtual VOID Init();
	virtual VOID Destroy();

	VOID	CreateInventoryExWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove);
	VOID	ShowInventoryExWnd();
	VOID	ShowInvenItemState();
	VOID	SetInvenBtnInit();

	INT		GetInvenItemNum(POINT ptMouse);
	INT		GetInvenCellNum(POINT ptMouse);
	INT		GetEmptyInvenNum();
	VOID	ShowInvenItem();
	BOOL	GetCellWH(WORD wLooks, INT& nCellWidth, INT& nCellHeight);
	BOOL	CanItemInsert(INT nCellNum, CItem* pxItem, RECT& rcCell);
	VOID	SetItemState(CItem* pxItem, INT nItemNum = -1, LPRECT lprcCell = NULL);

	VOID	InitParkItem();
	VOID	SetInvenType(BYTE bType);

	__inline BYTE GetInvenType()
	{
		return m_bType;
	}

	__inline VOID SetMerchantID(INT nID)
	{
		m_nMerchantID = nID;
	}

	LPINVENITEMSET FindInvenItem(WORD wLooks);
	
public:
	BOOL	DeleteInvenItem(INT nInvenItemNum);
	BOOL	DeleteInvenItem(INT nMakeIndex, CHAR* szName);
	VOID	DeleteAllInvenItem();

	VOID	AddInvenItem(CItem xItem, INT nCellNum, BOOL bUseInvenNum = TRUE);
	BOOL	ExtractInvenItem(CItem* pxItem, INT nInvenItemNum);
	VOID	ChangeInvenWithCommonOLD(INT nInvenCellNum, INT nInvenItemNum, LPCOMMONITEMSET pstCommonItemSet);
	VOID	ChangeInvenWithCommon(INT nInvenCellNum, INT nInvenItemNum, LPCOMMONITEMSET pstCommonItemSet);
	VOID	SetCommonFromInven(INT nInvenCellNum, INT nInvenItemNum, LPCOMMONITEMSET pstCommonItemSet);
	VOID	SetInvenFromCommonOLD(INT nInvenCellNum, LPCOMMONITEMSET pstCommonItemSet);
	VOID	SetInvenFromCommon(INT nInvenCellNum, LPCOMMONITEMSET pstCommonItemSet);

	VOID	SetCommonFromGold(LPCOMMONITEMSET pstCommonItemSet);

	BOOL	OnLButtonDoubleClick(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse);
	BOOL	OnLButtonDown(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse);
	BOOL	OnLButtonUp(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse);

	BOOL	OnRButtonDown(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse);

	BOOL	OnMouseMove(POINT ptMouse);
	VOID	OnScrollDown();
	VOID	OnScrollUp();

	VOID	ChangeItemCount(INT	nIdx, DWORD	wCount);
	BOOL	IsThereMultipleItem(CItem xItem);

	INT		GetSameItemCount(CItem xItem);
};

#endif

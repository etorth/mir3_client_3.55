#ifndef _INVENTORYWND_H
#define _INVENTORYWND_H


#pragma pack(1)
typedef struct tagITEMSET
{
	BOOL	bSetted;
	CItem	xItem;
}ITEMSET, *LPITEMSET;
typedef struct tagCOMMONITEMSET
{
	BOOL	bSetted;					// 아이템이 세팅되었는지의 여부.
	BOOL	bWaitResponse;				// 현재 아이템이 먹거나, 착용되어서 서버의 응답을 기다리는지의 여부.
	BOOL	bIsEquipItem;				// 현재 아이템이 장착창으로부터 왔는지의 여부.
	BOOL	bIsBeltItem;				// 현재 아이템이 벨트창으로부터 왔는지의 여부.
	BOOL	bIsHideItem;				// 마우스상태의 아이템을 보여줄것인가?.
	CItem	xItem;						// 아이템.
}COMMONITEMSET, *LPCOMMONITEMSET;
#pragma pack(8)


class CInventoryWnd : public CGameWnd
{ 
protected:
	INT			m_nStartLineNum;					// item鞫刻닒뒤섯契역迦
	RECT		m_rcInvenCell[_INVEN_MAX_CELL];		// Invent item rect.
	RECT		m_rcBeltCell[_BELT_MAX_CELL];		// Belt item rect


	CGameBtn	m_xInventoryBtn[_MAX_INVEN_BTN];

	CScrlBar	m_xInvenScrlBar;

public:
	ITEMSET		m_stInventoryItem[_MAX_INVEN_ITEM];
	ITEMSET		m_stBeltItem[_MAX_BELT_ITEM];

	RECT		m_rcBeltWnd;						// Belt 눗왯
public:
	CInventoryWnd();
	~CInventoryWnd();

	virtual VOID Init();
	virtual VOID Destroy();

	VOID	CreateInventoryWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove);
	VOID	ShowInventoryWnd();
	VOID	ShowItemStatus(LPCLIENTITEMRCD pstItemInfo);
	VOID	ShowInvenItemState();
	VOID	SetInvenBtnInit();
	VOID	SetInventItemNum(INT nMakeIndex, BYTE bNum);
public:
	BOOL	CheckItemPos(CHAR* szName);
	BOOL	SaveItemPos(CHAR* szName);

	VOID	DeleteBeltItem(INT nBeltInventoryNum);
	VOID	DeleteInvenItem(INT nInventoryNum);
	VOID	DeleteInvenItem(INT nMakeIndex, CHAR* szName);
	VOID	DeleteAllBeltItem();
	VOID	DeleteAllInvenItem();

	BOOL	AddInvenItem(CItem xItem, INT nInvenNum, BOOL bUseInvenNum = TRUE);
	BOOL	AddBeltItem(CItem xItem, INT nBeltNum, BOOL bUseBeltNum = TRUE);

	INT		GetInvenNum(POINT ptMouse);
	INT		GetBeltNum(POINT ptMouse);

	BOOL	ExtractInvenItem(CItem* pxItem, INT nInventoryNum);
	BOOL	ExtractBeltItem(CItem* pxItem, INT nBeltInventoryNum);

	VOID	ChangeInvenWithCommon(INT nInventoryNum, LPCOMMONITEMSET pstCommonItemSet);
	VOID	ChangeBeltWithCommon(INT nBeltInventoryNum, LPCOMMONITEMSET pstCommonItemSet);

	VOID	SetCommonFromInven(INT nInventoryNum, LPCOMMONITEMSET pstCommonItemSet);
	VOID	SetCommonFromBelt(INT nBeltInventoryNum, LPCOMMONITEMSET pstCommonItemSet);

	VOID	SetInvenFromCommon(INT nInventoryNum, LPCOMMONITEMSET pstCommonItemSet);
	VOID	SetBeltFromCommon(INT nBeltInventoryNum, LPCOMMONITEMSET pstCommonItemSet);

	VOID	AddNewBeltItem(LPCOMMONITEMSET pstCommonItemSet);


	BOOL	OnKeyUp(LPCOMMONITEMSET pstCommonItemSet, WPARAM wParam, LPARAM lParam);
	BOOL	OnLButtonDoubleClick(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse);
	BOOL	OnLButtonDown(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse);
	BOOL	OnLButtonUp(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse);
	VOID	OnMouseMove(POINT ptMouse);
	VOID	OnScrollDown();
	VOID	OnScrollUp();

	VOID	SetBeltRect(INT l, INT t, INT r, INT b) { SetRect(&m_rcBeltWnd, l, t, r, b); }
};



#endif // _INVENTORYWND_H
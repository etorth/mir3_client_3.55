#ifndef _CSTOREWND_H
#define _CSTOREWND_H

typedef struct tagSTOREOBJ
{
	CHAR	pszName[30];
	INT 	nSubMenu;
	INT		nPrice;
	INT		nStock;
	INT		nGrade;
	INT		nLooks;
	INT		nNeed;
	INT		nNeedLevel;
}STOREITEM, *LPSTOREITEM;


class CStoreWnd : public CGameWnd
{ 
private:
protected:
	CGameBtn			m_xStoreBtn[_MAX_STORE_BTN];

	BYTE				m_bType;	// 0:상점. 1:삼점+세부품목. 2:아이템보관. 3.약만들기.

	// 상점.
	CScrlBar			m_xStoreScrlBar;
	CList<STOREITEM>	m_xStoreItemList;
	RECT				m_rcStoreItem[_NEW_MAX_STORE_ITEM];
	RECT				m_rcStoreItemDesc[_NEW_MAX_STORE_ITEM];
	INT					m_nStoreFstLine;
	INT					m_nSelStoreItem;

	// 아이템 세부품목.
	CList<CItem>		m_xDetailItemList;
	RECT				m_rcDetailItem[_MAX_STORE_DETAIL_ITEM];
	INT					m_nDetailPage;
	INT					m_nSelDetailIdx;

	// 아이템 하나짜리.
	BYTE				m_bAddType;	// 0:일반상품, 1:약만들기.
	
	RECT				m_rcStoreAddItem;
	RECT				m_rcStoreAddItemDesc;

public:
	LPSTOREITEM			m_pstStoreAdd;
	INT					m_nNpcID;
	INT					m_nSelDetailItem;

public:
	CStoreWnd();
	~CStoreWnd();

	virtual VOID Init();
	virtual VOID Destroy();

	__inline VOID SetNPC(INT Id)
	{
		m_nNpcID = Id;
	}

	VOID	CreateStoreWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove);

	VOID	ShowStoreWnd();
	VOID	ShowStore();
	VOID	ShowDetail();
	VOID	ShowStoreAdd();
	VOID	PutNeedLevel(INT nX, INT nY, INT nNeed, INT nNeedLevel);
	VOID	PutJobBook(INT nX, INT nY, INT nNeedLevel);

	VOID	ShowDetailItemState();

	VOID	SetStatusBtnInit();

	INT				GetSelStoreItemNum(POINT ptMouse);
	LPSTOREITEM		GetSelStoreItemInfo(INT nListNum);

	INT				GetSelDetailItemNum(POINT ptMouse);
	CItem*			GetSelDetailItemInfo(INT nListNum);
	VOID			DeleteDetailItem();

	BOOL	SetStoreItemList(CHAR* pszMsg, INT nCount);
	BOOL	SetDetailItemLst(CHAR* pszMsg, INT nCount, INT nCurrentIdx);
	BOOL	SetStorageList(CHAR* pszMsg, INT nCount);
	BOOL	AddStorageList(CHAR* pszMsg, INT nCount);
	BOOL	SetDrugList(CHAR* pszMsg);

	BOOL	CanMove(POINT ptMouse);
public:

	BOOL	OnLButtonDown(POINT ptMouse);
	BOOL	OnLButtonUp(POINT ptMouse);
	BOOL	OnMouseMove(POINT ptMouse);
	VOID	OnScrollDown();
	VOID	OnScrollUp();
	BOOL	OnLButtonDoubleClick(POINT ptMouse);
};


#endif // _CSTOREWND_H
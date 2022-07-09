#ifndef _CEXCHANGEWND_H
#define _CEXCHANGEWND_H


class CExchangeWnd : public CGameWnd
{ 
private:
protected:
public:
	virtual VOID Init();
	virtual VOID Destroy();

	INT				m_nStartLineNum[2];
	RECT			m_rcDealRgn[2];
	CGameBtn		m_xExchangeBtn;
	CGameBtn		mExchange_btnClose;
	SHORT			m_shItemSetInfo[2][_DEAL_TOTAL_CELL];
	INVENITEMSET	m_stDealItem[2][_MAX_DEAL_ITEM];

	CHAR			m_pszDealName[64];

	INT				m_nDealGold[2];

	ITEMSET			m_stDealOnItem;

	BOOL			m_bIsDealPushed;

	CScrlBar		m_xExchangeScrlBar[2];

	INT				m_nDealCellNum;
	LPCOMMONITEMSET m_pstCommonItemSet;

public:

	CExchangeWnd();
	~CExchangeWnd();
	VOID	CreateExchangeWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove);
	VOID	ShowExchangeWnd();
	VOID	SetStatusBtnInit();

	inline VOID SetDealName(CHAR* pszName)
	{
		strcpy(m_pszDealName, pszName);
	}

	VOID	CloseExchangeWnd();

	VOID	ShowDealItem();
	BOOL	CanItemInsert(BYTE bPos, INT nCellNum, CItem* pxItem, RECT& rcCell);
	VOID	SetItemState(BYTE bPos, CItem* pxItem, INT nItemNum = -1, LPRECT lprcCell = NULL);
	INT		GetEmptyInvenNum(BYTE bPos);
	VOID	DeleteDealItem(BYTE bPos, INT nDealItemNum);
	VOID	DeleteDealItem(BYTE bPos, INT nMakeIndex, CHAR* szName);
	VOID	DeleteAllDealItem(BYTE bPos);
	VOID	AddDealItem(BYTE bPos, CItem xItem, INT nCellNum, BOOL bUseInvenNum = TRUE);
	INT		GetEmptyDealNum(BYTE bPos);
	BOOL	GetCellWH(WORD wLooks, INT& nCellWidth, INT& nCellHeight);
	VOID	ShowDealItemState(BYTE bPos);
	VOID	ShowDealItemState();
	INT		GetDealCellNum(BYTE bPos, POINT ptMouse);
	INT		GetDealItemNum(BYTE bPos, POINT ptMouse);



	BOOL	ExtractDealItem(BYTE bPos, CItem* pxItem, INT nDealItemNum);
	VOID	SetCommonFromDeal(BYTE bPos, INT nDealCellNum, INT nDealItemNum, LPCOMMONITEMSET pstCommonItemSet);
	VOID	ChangeDealWithCommon(BYTE bPos, INT nDealCellNum, INT nDealItemNum, LPCOMMONITEMSET pstCommonItemSet);
	VOID	SetDealFromCommon(BYTE bPos, INT nDealCellNum, LPCOMMONITEMSET pstCommonItemSet);


	VOID	SetDealOnItemFromCommon(LPCOMMONITEMSET pstCommonItemSet, INT nCellNum);
	VOID	SetDealFromDealOnItem();

	VOID	FindNDeleteHotKeyItem();


//  메시지 함수.
	BOOL	OnLButtonDown(POINT ptMouse);
	BOOL	OnLButtonUp(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse);
	BOOL	OnMouseMove(POINT ptMouse);
	VOID	OnScrollDown();
	VOID	OnScrollUp();

	LRESULT OnMsgBoxReturn(WPARAM wParam, LPARAM lParam);
};


#endif // _CEXCHANGEWND_H

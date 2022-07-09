#ifndef _BELTWND_H
#define _BELTWND_H

class CBeltWnd : public CGameWnd
{ 
// Constructor & Destructor
public:
	CBeltWnd();
	~CBeltWnd();

// Attributes
public:
	CGameBtn			m_xBeltBtnClose;
	CGameBtn			m_xBeltBtnRotate;

	BOOL				mBelt_nMode;

	SHORT				m_shBeltHeight;
	BYTE				m_bBeltState;
	RECT				m_rcBeltCell[_BELT_MAX_CELL];
	ITEMSET				m_stBeltItem[_MAX_BELT_ITEM];
	
// Operations
public:
	virtual VOID		Init();
	virtual VOID		Destroy();

	VOID				CreateBeltWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend);
	BOOL				OnLButtonDown(POINT ptMouse);
	BOOL				OnLButtonUp(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse);
	BOOL				OnLButtonDoubleClick(POINT ptMouse);
	BOOL				OnMouseMove(POINT ptMouse);
	VOID				SetStatusBtnInit();

	VOID				ShowBeltWnd();

	BOOL				SaveItemPos(CHAR* szName);

	VOID				MoveBeltWnd(POINT ptMouse);

	VOID				SaveBeltPosition();
	POINT				LoadBeltPosition();

	VOID				DeleteBeltItem(INT nBeltInventoryNum);
	VOID				DeleteAllBeltItem();
	BOOL				AddBeltItem(CItem xItem, INT nBeltNum, BOOL bUseBeltNum = TRUE);
	INT					GetBeltNum(POINT ptMouse);
	BOOL				ExtractBeltItem(CItem* pxItem, INT nBeltInventoryNum);
	VOID				ChangeBeltWithCommonOLD(INT nBeltInventoryNum, LPCOMMONITEMSET pstCommonItemSet);
	VOID				ChangeBeltWithCommon(INT nBeltInventoryNum, LPCOMMONITEMSET pstCommonItemSet);
	VOID				SetCommonFromBelt(INT nBeltInventoryNum, LPCOMMONITEMSET pstCommonItemSet);
	VOID				SetBeltFromCommonOLD(INT nBeltInventoryNum, LPCOMMONITEMSET pstCommonItemSet);
	VOID				SetBeltFromCommon(INT nBeltInventoryNum, LPCOMMONITEMSET pstCommonItemSet);
	BOOL				AddNewBeltItem(LPCOMMONITEMSET pstCommonItemSet);
	BOOL				ChangeBeltItem(INT nBeltInventoryNum, LPCOMMONITEMSET pstCommonItemSet);

	INT					FindSameItemInBelt(CItem xItem);

	BOOL				ProceessKeyDownMessage(WPARAM wParam, LPARAM lParam);
};



#endif // _BELTWND_H
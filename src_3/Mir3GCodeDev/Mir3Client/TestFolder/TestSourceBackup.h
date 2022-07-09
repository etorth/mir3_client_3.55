#ifndef _TestSourceBackup_h_
#define _TestSourceBackup_h_

// exclude file from build

/* 

  
// GameOverWnd - Success
class CTestWnd : public CGameWnd
{
public:
	CTestWnd();
	~CTestWnd();

	VOID CreateTestWnd(
		INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend );
	VOID ShowTestWnd();
	
	VOID Init();
	VOID Destroy();

	BOOL OnLButtonDown( POINT ptMouse );
	BOOL OnLButtonUp( POINT ptMouse );
	VOID OnMouseMove( POINT ptMouse );
	VOID MoveTestWnd( POINT ptMouse );
	
	CGameBtn	m_BtnClose;
	CGameBtn	m_BtnLogout;
	CGameBtn	m_BtnExit;

public:
	// TEST LOG

	INT			m_iChildLeftOffset;
	INT			m_iChildRightOffset;
	INT			m_iChildUpOffset;
	INT			m_iChildDownOffset;
	INT			m_iChildStartXOffset;
	INT			m_iChildStartYOffset;
	CHAR		m_strChildPosInfo[ 260 ];

	INT			m_iStartX;
	INT			m_iStartY;
	INT			m_iWidth;
	INT			m_iHeight;
	CHAR		m_strParentPosInfo[ 260 ];

	CHAR*		GetChildPosInfo();
	CHAR*		GetParentPosInfo();
};



// InventoryWnd - Scroll, Button Success, Item Move Failed
#define MAX_INVENTORY_CELL		100
#define SHOW_INVENTORY_CELL		8
#define INVENTORY_ITEM_STARTX	17
#define INVENTORY_ITEM_STARTY	71
#define ITEM_CELL_WIDTH			38
#define ITEM_CELL_HEIGHT		38
#define INVENTORY_ITEM_XNUM		6
#define INVENTORY_ITEM_YNUM		8

class CTestWnd : public CGameWnd
{
public:
	CTestWnd();
	~CTestWnd();

	VOID CreateTestWnd(
		INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend );
	VOID ShowTestWnd();
	
	VOID Init();
	VOID Destroy();

	BOOL OnLButtonDown( LPCOMMONITEMSET pCommonItemSet, POINT ptMouse );
	BOOL OnLButtonUp( POINT ptMouse );
	BOOL OnMouseMove( POINT ptMouse );
	VOID MoveTestWnd( POINT ptMouse );
	VOID OnScrollDown();
	VOID OnScrollUp();
	
	CGameBtn	m_BtnClose;
	CScrlBar	m_ScrlBar;
	INT			m_iFstLine;				// 스크롤 스타트 라인 인덱스
	INT			m_iCurrentCellNum;		// 마우스로 클릭한 곳의 아이템 인덱스

	// 아이템
	INVENITEMSET	m_iisInventoryItem[ INVENTORY_ITEM_XNUM * MAX_INVENTORY_CELL ];

	INT		GetInvenItemNum( POINT ptMouse );
	INT		GetInvenCellNum( POINT ptMouse );
	INT		GetEmptyInvenNum();
	BOOL	SetItemToInvenFromCommon( LPCOMMONITEMSET pCommonItemSet );
	BOOL	CanItemInsertToInventory( LPCOMMONITEMSET pCommonItemSet );
	VOID	AddItemToInventory( LPCOMMONITEMSET pCommonItemSet );

	VOID	ShowInventoryItem();


public:
	// TEST LOG

	INT			m_iChildLeftOffset;
	INT			m_iChildRightOffset;
	INT			m_iChildUpOffset;
	INT			m_iChildDownOffset;
	INT			m_iChildStartXOffset;
	INT			m_iChildStartYOffset;
	CHAR		m_strChildPosInfo[ 260 ];

	INT			m_iStartX;
	INT			m_iStartY;
	INT			m_iWidth;
	INT			m_iHeight;
	CHAR		m_strParentPosInfo[ 260 ];

	CHAR*		GetChildPosInfo();
	CHAR*		GetParentPosInfo();
};


*/

#endif
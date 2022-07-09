#ifndef _UTILWND_H
#define _UTILWND_H


typedef struct tagCLIENTUTILITEMINFO
{
	BOOL			bCheck;
	CItem			xItem;
	INT				nValue;
	INT				nPriority;
}CLIENTUTILITEMINFO, *LPCLIENTUTILITEMINFO;

typedef struct tagCLIENTUTILMAGICINFO
{
	BOOL			bCheck;
	CHAR			szName[64];
	INT				nValue;
	INT				nPriority;
}CLIENTUTILMAGICINFO, *LPCLIENTUTILMAGICINFO;


class CUtilWnd : public CGameWnd
{ 
// Constructor & Destructor
public:
	CUtilWnd();
	~CUtilWnd();
// Attributes
public:
	CGameBtn				mUtil_BtnClose;					// 닫기
	CGameBtn				mUtil_BtnDownofHP1;				// 메뉴 펼침 버튼(체약1)
	CGameBtn				mUtil_BtnDownofHP2;				// 메뉴 펼침 버튼(체약2)
	CGameBtn				mUtil_BtnDownofHP3;				// 메뉴 펼침 버튼(체약3)
	CGameBtn				mUtil_BtnDownofHP4;				// 메뉴 펼침 버튼(체약4)

	CGameBtn				mUtil_BtnDownofMP1;				// 메뉴 펼침 버튼(마약3)
	CGameBtn				mUtil_BtnDownofMP2;				// 메뉴 펼침 버튼(마약3)
	CGameBtn				mUtil_BtnDownofMP3;				// 메뉴 펼침 버튼(마약3)
	
	CGameBtn				mUtil_BtnDownofHPMP;			// 메뉴 펼침 버튼(선화수1)

	CGameBtn				mUtil_BtnDownofMP4;			// 메뉴 펼침 버튼(전서1)
	CGameBtn				mUtil_BtnDownofScroll2;			// 메뉴 펼침 버튼(전서2)

	CGameBtn				mUtil_BtnItemMode;				// 메뉴 펼침 버튼(아이템모드 탭버튼)
	CGameBtn				mUtil_BtnMagicMode;				// 메뉴 펼침 버튼(마법모드 탭버튼)

	CGameBtn				mUtil_BtnDownofCharm1;			// 메뉴 펼침 버튼(부적1)
	CGameBtn				mUtil_BtnDownofCharm2;			// 메뉴 펼침 버튼(부적2)

	CGameBtn				mUtil_BtnDownofPoison1;			// 메뉴 펼침 버튼(아이템모드 탭버튼)
	CGameBtn				mUtil_BtnDownofPoison2;			// 메뉴 펼침 버튼(마법모드 탭버튼)

	CItem					mUtil_xItem[7];

	BOOL					mUtil_bMode;

	INT						mUtil_nSettedItemCount;
	INT						mUtil_nKindofSettedItem;

	INT						mUtil_nFocusedValue;

	CLIENTUTILITEMINFO		mUtil_xUtilItemInfo[10];

	CLIENTUTILITEMINFO		mUtil_xUtilItemInfo2[4];
	CLIENTUTILMAGICINFO		mUtil_xUtilMagicInfo[10];

	RECT					mUtil_rcCheck[10];
	RECT					mUtil_rcItem[10];
	RECT					mUtil_rcValue[10];
	RECT					mUtil_rcPriority[10];
	RECT					mUtil_rcName[10];

	RECT					mUtil_rcMenu[7];

	RECT					mUtil_rcCheck2[4];				// 도사용 아이템 자동 교체 
	RECT					mUtil_rcPriority2[4];			// 도사용 아이템 자동 교체 

	DWORD					mUtil_dwItemUseTimer;			// 물약 먹기	
	DWORD					mUtil_dwItemTakeonTimer;		// 도사용 아이템 교체
	DWORD					mUtil_dwMagicUseTimer;			// 도사용 자동 힐

	

// Operations
public:
	virtual VOID			Init();
	virtual VOID			Destroy();

	VOID					CreateUtilWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend);
	VOID					ShowUtilWnd();

	VOID					ShowItemSetMode();
	VOID					ShowMagicSetMode();

	BOOL					OnLButtonDown(POINT ptMouse);
	BOOL					OnLButtonUp(POINT ptMouse);
	BOOL					OnMouseMove(POINT ptMouse);

	BOOL					OnKeyDown(WPARAM wParam, LPARAM lParam);

	BOOL					LBtnDownOnItemSetMode(POINT ptMouse);
	BOOL					LBtnDownOnMagicSetMode(POINT ptMouse);
	BOOL					LBtnUpOnItemSetMode(POINT ptMouse);
	BOOL					LBtnUpOnMagicSetMode(POINT ptMouse);
	BOOL					MouseMoveOnItemSetMode(POINT ptMouse);
	BOOL					MouseMoveOnMagicSetMode(POINT ptMouse);

	
	VOID					SetMenuItemToHPItem();
	VOID					SetMenuItemToMPItem();
	VOID					SetMenuItemToHPMPItem();
	VOID					SetMenuItemToScrollItem();
	VOID					SetMenuItemToCharmItem();
	VOID					SetMenuItemToPoisonItem();

	VOID					ShowMenuItemState();

	VOID					SetMenuRect();

	VOID					ProcessUtilFunc();

	BOOL					SaveUtilSet();
	BOOL					LoadUtilSet();

	VOID					SetKey(BYTE bKey);
	VOID					CheckKey(BYTE bKey);
	BOOL					UseKey(BYTE bKey);
};



#endif // _UTILWND_H
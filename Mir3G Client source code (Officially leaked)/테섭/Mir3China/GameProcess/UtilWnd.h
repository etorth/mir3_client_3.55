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

	CGameBtn				mUtil_BtnDownofHP;			// 체약용 메뉴 펼침 버튼
	CGameBtn				mUtil_BtnDownofMP;			// 마약용 메뉴 펼침 버튼
	CGameBtn				mUtil_BtnDownofScroll;		// 전서용 메뉴 펼침 버튼

	INT						mUtil_nHPValue;				// 체약용 설정값
	INT						mUtil_nScrollValue;			// 전서용 설정값
	INT						mUtil_nMPValue;				// 마약용 설정값

	RECT					mUtil_rcHPValue;			// 체약용 설정값
	RECT					mUtil_rcScrollValue;		// 전서용 설정값
	RECT					mUtil_rcMPValue;			// 마약용 설정값

	CHAR					mUtil_szHPpotion[16];		// 선택된 체력회복약 종류
	CHAR					mUtil_szScroll[16];			// 선택된 전서 종류
	CHAR					mUtil_szMPpotion[16];		// 선택된 마력회복약 종류

	CGameBtn				mUtil_BtnItemMode;				// 메뉴 펼침 버튼(아이템모드 탭버튼)
	CGameBtn				mUtil_BtnMagicMode;				// 메뉴 펼침 버튼(마법모드 탭버튼)
	CGameBtn				mUtil_BtnEtcMode;				// 메뉴 펼침 버튼(기타설정모드 탭버튼)

	CGameBtn				mUtil_BtnDownofMagicKind[20];		// 메뉴 펼침 버튼(무공종류)
	CGameBtn				mUtil_BtnDownofCharmSize[20];		// 메뉴 펼침 버튼(부적크기)	
	CGameBtn				mUtil_BtnDownofCharmKind[20];		// 메뉴 펼침 버튼(부적종류)

	INT						mUtil_nSeletedMenu;
	INT						mUtil_nMenuCount;
	

	CGameBtn				mUtil_BtnLeftfCharm;
	CGameBtn				mUtil_BtnRightCharm;

	CGameBtn				mUtil_BtnDownofPoison1;			// 메뉴 펼침 버튼(아이템모드 탭버튼)
	CGameBtn				mUtil_BtnDownofPoison2;			// 메뉴 펼침 버튼(마법모드 탭버튼)

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

	RECT					mUtil_rcMenu[24];

	RECT					mUtil_rcCheck2[4];				// 도사용 아이템 자동 교체 
	RECT					mUtil_rcPriority2[4];			// 도사용 아이템 자동 교체 

	DWORD					mUtil_dwItemUseTimer;			// 물약 먹기	
	DWORD					mUtil_dwItemTakeonTimer;		// 도사용 아이템 교체
	DWORD					mUtil_dwMagicUseTimer;			// 도사용 자동 힐
	DWORD					mUtil_dwScrollUseTimer;			// 전서사용	

	INT						mUtil_nPageInCharm;

	CHAR					mUtil_szCharmName[40][16];
	CHAR					mUtil_szCharmKind[40][4];
	CHAR					mUtil_szMagicName[40][16];


	BOOL					mUtil_bShowSysTime;
	RECT					mUtil_rchowSysTime;

	CGameBtn				mUtil_BtnChangeWeather;

	BOOL					mUtil_bShowMagicTime;
	RECT					mUtil_rcMagicTime;

	BOOL					mUtil_bShowHumanHP;
	RECT					mUtil_rcShowHumanHP;

	BOOL					mUtil_bGrayPotion;

	INT						TEST;
	

// Operations
public:
	virtual VOID			Init();
	virtual VOID			Destroy();

	VOID					CreateUtilWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend);
	VOID					ShowUtilWnd();

	VOID					ShowItemSetMode();
	VOID					ShowMagicSetMode();
	VOID					ShowEtcSetMode();

	BOOL					OnLButtonDown(POINT ptMouse);
	BOOL					OnLButtonUp(POINT ptMouse);
	BOOL					OnMouseMove(POINT ptMouse);

	BOOL					OnKeyDown(WPARAM wParam, LPARAM lParam);
	BOOL					OnSysKeyDown(WPARAM wParam, LPARAM lParam);

	BOOL					LBtnDownOnItemSetMode(POINT ptMouse);
	BOOL					LBtnDownOnMagicSetMode(POINT ptMouse);
	BOOL					LBtnDownOnEtcSetMode(POINT ptMouse);
	BOOL					LBtnUpOnItemSetMode(POINT ptMouse);
	BOOL					LBtnUpOnMagicSetMode(POINT ptMouse);
	BOOL					LBtnUpOnEtcSetMode(POINT ptMouse);
	BOOL					MouseMoveOnItemSetMode(POINT ptMouse);
	BOOL					MouseMoveOnMagicSetMode(POINT ptMouse);
	BOOL					MouseMoveOnEtcSetMode(POINT ptMouse);

	
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
	VOID					UseCharm(INT nMagicID);
	VOID					UseHPPotion();
	VOID					UseMPPotion();
};



#endif // _UTILWND_H
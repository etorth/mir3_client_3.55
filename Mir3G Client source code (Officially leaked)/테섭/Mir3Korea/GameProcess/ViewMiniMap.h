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
	CGameBtn				mUtil_BtnClose;					// �ݱ�
	CGameBtn				mUtil_BtnDownofHP1;				// �޴� ��ħ ��ư(ü��1)
	CGameBtn				mUtil_BtnDownofHP2;				// �޴� ��ħ ��ư(ü��2)
	CGameBtn				mUtil_BtnDownofHP3;				// �޴� ��ħ ��ư(ü��3)
	CGameBtn				mUtil_BtnDownofHP4;				// �޴� ��ħ ��ư(ü��4)

	CGameBtn				mUtil_BtnDownofMP1;				// �޴� ��ħ ��ư(����3)
	CGameBtn				mUtil_BtnDownofMP2;				// �޴� ��ħ ��ư(����3)
	CGameBtn				mUtil_BtnDownofMP3;				// �޴� ��ħ ��ư(����3)
	
	CGameBtn				mUtil_BtnDownofHPMP;			// �޴� ��ħ ��ư(��ȭ��1)

	CGameBtn				mUtil_BtnDownofMP4;			// �޴� ��ħ ��ư(����1)
	CGameBtn				mUtil_BtnDownofScroll2;			// �޴� ��ħ ��ư(����2)

	CGameBtn				mUtil_BtnItemMode;				// �޴� ��ħ ��ư(�����۸�� �ǹ�ư)
	CGameBtn				mUtil_BtnMagicMode;				// �޴� ��ħ ��ư(������� �ǹ�ư)

	CGameBtn				mUtil_BtnDownofCharm1;			// �޴� ��ħ ��ư(����1)
	CGameBtn				mUtil_BtnDownofCharm2;			// �޴� ��ħ ��ư(����2)

	CGameBtn				mUtil_BtnDownofPoison1;			// �޴� ��ħ ��ư(�����۸�� �ǹ�ư)
	CGameBtn				mUtil_BtnDownofPoison2;			// �޴� ��ħ ��ư(������� �ǹ�ư)

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

	RECT					mUtil_rcCheck2[4];				// ����� ������ �ڵ� ��ü 
	RECT					mUtil_rcPriority2[4];			// ����� ������ �ڵ� ��ü 

	DWORD					mUtil_dwItemUseTimer;			// ���� �Ա�	
	DWORD					mUtil_dwItemTakeonTimer;		// ����� ������ ��ü
	DWORD					mUtil_dwMagicUseTimer;			// ����� �ڵ� ��

	

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
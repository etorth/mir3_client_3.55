#ifndef _MESSENGERWND_H
#define _MESSENGERWND_H


#pragma pack(1)
typedef struct tagCLIENTDHLCONTAIN
{
	INT				nIndex;
	WORD			wDhlType;
	WORD			wReadCheck;
	INT				nMoney;
	CLIENTITEMRCD	stItemInfo;
	CHAR			szText[501];
}CLIENTDHLCONTAIN, *LPCLIENTDHLCONTAIN;
#pragma pack(8)



class CMessengerWnd : public CGameWnd
{ 
// Constructor & Destructor
public:
	CMessengerWnd();
	~CMessengerWnd();
// Attributes
public:
	CGameBtn				mMessenger_BtnClose;			// �޽��� �ݱ�
	CGameBtn				mMessenger_BtnDelete;			// ���õ� ���� ����
	CGameBtn				mMessenger_BtnRefresh;			// ���� ���� ��������
	CGameBtn				mMessenger_BtnToSendBox;		// ���� ����������
	CGameBtn				mMessenger_BtnToGiftBox;		// ����������
	CGameBtn				mMessenger_BtnToWriteBox;		// ����â����
	CGameBtn				mMessenger_BtnToReadBox;		// �б�â����
	CGameBtn				mMessenger_BtnToReceiveBox;		// ��������������
	CGameBtn				mMessenger_BtnDeleteThis;		// �б�â���� �����ϱ�
	CGameBtn				mMessenger_BtnReturn;			// �б�â���� �����ϱ�
	CGameBtn				mMessenger_BtnNext;				// �б�â���� ���� ���� �б�
	CGameBtn				mMessenger_BtnPrev;				// �б�â���� ���� ���� �б�
	CGameBtn				mMessenger_BtnResetPaper;		// ����â���� �ʱ�ȭ
	CGameBtn				mMessenger_BtnSendPaper;		// �� ���� ������
	CGameBtn				mMessenger_BtnResetGift;		// ����â���� �ʱ�ȭ
	CGameBtn				mMessenger_BtnSendGift;			// ���� ������
	CGameBtn				mMessenger_BtnTakeBack;			// ��ã�ƿ���



	INT						mMessenger_nMode;
	

	CList<CLIENTDHLTITLE>	mMessenger_xReceivedMSGList;
	CList<CLIENTDHLCONTAIN> mMessenger_xReceivedContain;
	CList<CHAT>				mMessenger_xReceivedMsg;				// ���� ����


	CList<CLIENTDHLTITLE>	mMessenger_xSendMSGList;
	CList<CLIENTDHLCONTAIN> mMessenger_xSendContain;
	CList<CHAT>				mMessenger_xSendMsg;				// ���� ����


	RECT					mMessenger_rcReadGift;
	CItem					mMessenger_xReceivedItem;
	BOOL					mMessenger_bItemReceive;
	BOOL					mMessenger_bMoneyReceive;
	

	CHAR					mMessenger_szReadID[25];
	CHAR					mMessenger_szDate[20];
	
	HWND					mMessenger_hWriteMsg;
	BOOL					mMessenger_bWirteID;
	BOOL					mMessenger_bWriteMsg;
	RECT					mMessenger_rcWriteID;
	RECT					mMessenger_rcWriteMsg;
	CHAR					mMessenger_szWriteID[25];

	BOOL					mMessenger_bSettingMoney;


	HWND					mMessenger_hGiftMsg;
	BOOL					mMessenger_bGiftID;
	BOOL					mMessenger_bGiftMsg;
	BOOL					mMessenger_bGiftItemSet;
	CItem					mMessenger_xItem;
	RECT					mMessenger_rcGiftEditBox;
	RECT					mMessenger_rcGiftShowItem;
	RECT					mMessenger_rcGiftID;
	CHAR					mMessenger_szGiftID[25];
	

	CScrlBar				mMessenger_xReceiveScrBar;
	CScrlBar				mMessenger_xSendScrBar;
	CScrlBar				mMessenger_xReadScrBar;

	INT						mMessenger_nMoneyGift;

	INT						mMessenger_nReadStartLine;
	INT						mMessenger_nReadMaxLine;

	INT						mMessenger_nReadMode;

	INT						mMessenger_nReceiveStartLine;
	INT						mMessenger_nSendStartLine;

	INT						mMessenger_nReceiveMaxLine;
	INT						mMessenger_nSendMaxLine;

	INT						mMessenger_nReceiveSelected;
	INT						mMessenger_nSendSelected;


	INT						mMessenger_nMouseLacated;
	
	RECT					mMessenger_rcTitle[7];
	RECT					mMessenger_rcCheck[7];
	RECT					mMessenger_rcCell[7];

	INT						mMessenger_nReceiveChecked;
	INT						mMessenger_nSendChecked;


	INT						mMessenger_nMoney;
	BOOL					mMessenger_bSetMoney;


	DWORD					mMessenger_dwLastSendTimer;



// Operations
public:
	virtual VOID Init();
	virtual VOID Destroy();

	VOID	CreateMessengerWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend);
	VOID	ShowMessengerWnd();

	BOOL	OnLButtonDown(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse);
	BOOL	OnLButtonUp(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse);

	BOOL	OnRButtonDown(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse);
	BOOL	OnMouseMove(POINT ptMouse);

	BOOL	OnLButtonDoubleClick(POINT ptMouse);

	BOOL	OnKeyDown(WPARAM wParam, LPARAM lParam);

	VOID	OnScrollDown();
	VOID	OnScrollUp();

	VOID	ShowReceivedBox();
	VOID	ShowReadBox();
	VOID	ShowWriteBox();
	VOID	ShowGiftBox();
	VOID	ShowSendBox();

	VOID	SendMSG();

	VOID	SetReceivedMSGList(CHAR* pszMsg, INT nCount);
	VOID	AddReceivedMsg(LPCLIENTDHLCONTAIN pstDhlMsg);

	VOID	SetSendMSGList(CHAR* pszMsg, INT nCount);
	VOID	AddSendMsg(LPCLIENTDHLCONTAIN pstDhlMsg);

	BOOL	ReadReceivedMsg(INT nIndex);
	BOOL	ReadSendMsg(INT nIndex);

	VOID	SendMyItem();
	VOID	ChangeEditBoxLoc();
	VOID	CloseMessengerWnd();
};



#endif // _MESSENGERWND_H
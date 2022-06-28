#ifndef _INTERFACE_H
#define _INTERFACE_H

// ���� ������ ����
typedef struct _tagTExpireAbilitys
{
	INT		nItemExExpireTime;			// �߰� ���� ����ð�

	INT		nSavedItemExExpireTime;		// �߰� â�� ����ð�
	
	FLOAT	fExpRate;					// ����ġ �߰� ����
	INT		nExpRateExpireTime;			// ����ġ �߰� ���� ����ð�
	
	FLOAT	fDropRate;					// ����� �߰� ����
	INT		nDropRateExpireTime;		// ����� �߰� ���� ����ð�
	
	FLOAT	fMiningRate;				// ä���� �߰� ����
	INT		nMiningRateExpireTime;		// ä���� �߰� ���� ����ð�

	INT		nIgnoreLevelExpireTime;		// ���� ���� ���� ����ð�
	
	INT		nUserTitleExprieTime;		// ���� Ÿ��Ʋ ����ð�

	enum { NUM_ITEMS = 7 };

} TEXPIREABILITYS, *LPTEXPIREABILITYS;

class CInterface
{ 
public:
	 CInterface();
	~CInterface();
public:
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// ��������� Message ����.
//---------------------------------------------------------------------------------------------------------------//
	ClientSysMsg	m_xClientSysMsg;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Main Interface ó������.
//---------------------------------------------------------------------------------------------------------------//
	CWHWilImageData*	m_pxInterImg;					// ���ӻ󿡼� ����� �������̽� �̹���.
//	CWHWilImageData		m_xInterImgEx;					// �������̽� ���� �̹���.

	COMMONITEMSET		m_stCommonItem;					// ���� ������ ����(���콺 ������).
	RECT				m_rcMain;						// �����������̽� ��ü ����.

	RECT				m_rcHPS;						
	RECT				m_rcMPS;						
	RECT				m_rcExpS;						
	RECT				m_rcWetS;						

	RECT				m_rcChatLine[_MAX_CHATLINE];	// 5���� ä�ÿ���.
	RECT				m_rcLargeChatLine[_MAX_CHATLINE];	// 14���� ä�ÿ���.

	RECT				m_rcChat;						// ä��â ����.
	RECT				m_rcLargeChat;					// Ŀ�ٶ� ä��â ����.
	INT					m_nFstLine;						// ä��ȭ������� ���� ������ ����Ű�� ä�ø���Ʈ�� ��ȣ�ε���.
	INT					m_nFstLineInLarge;
	CList<CHAT>			m_xChatlist;					// �������� ä�� ����Ÿ.
	CList<CHAT>			m_xLargeChatlist;				// �������� ä�� ����Ÿ - ū ä��â��.


	INT					m_nFstLineInSystemChat;
	RECT				m_rcSystemChat;
	RECT				m_rcSystemChatLine[_SYSTEM_CHATLINE];	// 4���� ä�ÿ���.
	CList<CHAT>			m_xSystemChat;

	INT					m_nFstLineInNormalChat;
	RECT				m_rcNormalChat;
	RECT				m_rcNormalChatLine[_SYSTEM_CHATLINE];	// 4���� ä�ÿ���.

	CList<CHAT>			m_xNormalChat;

	RECT				m_rcLargeChatRgn;				// �����������̽� ��ü ����.


	CDLList<CHAT>		m_xChat;						// �������� ä�� ����Ÿ.

	CDLList<INT>		m_xWndOrderList;				
	BOOL				m_bMoveFocusedWnd;

	// ��Ʈ����.
	SHORT				m_shBeltHeight;
	BYTE				m_bBeltState;
	RECT				m_rcBeltCell[_BELT_MAX_CELL];
	ITEMSET				m_stBeltItem[_MAX_BELT_ITEM];

	CGameBtn			m_xInterBtn[_NEW_MAX_INTER_BTN];	// ��ư.
	CGameBtn			m_xInterBtnofSiege;					// �߼��Ź�ư.
	CGameBtn			m_xInterBtnofNewMessage;			// ���޼�����ư.
	CGameBtn			m_xInterBtnFaceImgUp;				// �̹��� ���ε� ��ư.


	CScrlBar			m_xScrlBarInSmallChat;
	CScrlBar			m_xScrlBarInLargeChat;

	BOOL				m_bShowKey;
	BOOL				m_bNewFliker;
	DWORD				m_dwNewFliker;

	INT					m_nIdxMsgBox;					

	DWORD				m_dwViewModeClickTick;				// ȭ���¿���(����, ����) �̵� ���ɿ���üũƽ.

	DWORD				m_dwQueryMsgTime;
	CMiniMap			m_xMiniMap;
	CMiniMapInSiege		m_xMiniMapInSiege;
	BOOL				m_bViewMiniMap;

	BOOL				m_bViewMiniMapInMain;

	BOOL				m_bIsLargeChat;
	INT					m_nChatMode;

	INT					m_nInformationMode;

	CWHSurface			m_hbmUserFace;
	BOOL				m_bLoadUserFace;
	BOOL				m_bIsThereUserFile;
	DWORD				m_dwFaceImgTimer;

	RECT				m_rcInfoModeChange;
	RECT				m_rcCharFace;
	RECT				m_rcLogo;
	RECT				m_rcAcnum;
	RECT				m_rcDcnum;

	POINT				m_ptFrameLoc;
	BYTE				m_bDcScMcShow;

	BOOL				m_bIsMoving;
	BOOL				m_bIsDown;

	BOOL				m_bAcShow;
	
	BOOL				m_bChatallDeny;
	BOOL				m_bDenyGuild;
	BOOL				m_bDenyShout;

	BOOL				m_bReadyViewMap;

	BOOL				m_bReadyInforMap;

	BOOL				m_bHasSiege;
	BOOL				m_bHasNewMessage;

	BOOL				m_bShowUserPic;

	DWORD				m_dwSaveItemTimer;

	RECT				m_rcWarning1;
	RECT				m_rcWarning2;

	BOOL				m_bMoveWarning;
	INT					m_nMoveOffset;
	INT					m_nWarningCnt;
	SIZE				m_sizeWarning;

	CHAR				m_szWarning[MAX_PATH];
	CHAR				m_szWarningOrigin[MAX_PATH];
	DWORD				m_dwWarningTimer;

	DWORD				m_dwLogoTimer;
	INT					m_nLogoIdx;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// �Ӹ� ����Ʈ ����, ���� ��ũ�ΰ���.
//---------------------------------------------------------------------------------------------------------------//
	CList<CHAT>			m_xHearList;
	INT					m_nSelHearNum;
	LONG 				CtrlNumPushed(WPARAM wParam, LPARAM lParam);
	VOID				SetHearList();
	LPCHAT				FindHearList(CHAR* pszHear);
	VOID				AddHearList(CHAR* pszHear);
	VOID				LoadHearList();					// �ش缭��, �ش� ĳ��.
	VOID				SaveHearList();					// �ش缭��, �ش� ĳ��.
	VOID				ShowHearList();

	BYTE				*m_temp;

	CList<CHAT>			m_xMacroList;
	INT					m_nSelMacroNum;
	LONG 				AltNumPushed(WPARAM wParam, LPARAM lParam);
	VOID				SetMacroList();
	LPCHAT				FindMacroList(CHAR* pszMacro);
	VOID				AddMacroList(CHAR* pszMacro);
	VOID				LoadMacroList();				// �ش缭��, �ش� ĳ��.
	VOID				SaveMacroList();				// �ش缭��, �ش� ĳ��.
	VOID				ShowMacroList();
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Main Interface ���� �����ϴ� Window.
//---------------------------------------------------------------------------------------------------------------//
	CInventoryWnd		m_xInventoryWnd;				//����������.
	CStatusWnd			m_xStatusWnd;					//ĳ���� ���� ����������(3��).
	CStoreWnd			m_xStoreWnd;					//����������.
	CExchangeWnd		m_xExchangeWnd;					//��ȯ������.
	CGuildWnd			m_xGuildWnd;					//����������.
	CGroupWnd			m_xGroupWnd;					//�׷�������.
	CUserStateWnd		m_xUserStateWnd;				//�׷��Է�������.
	CChatPopWnd			m_xChatPopWnd;					//�׷��Է�������.
	CNPCWnd				m_xNPCWnd;						//NPC ��ȭâ.
	CQuestWnd			m_xQuestWnd;					//����Ʈâ.
	COptionWnd			m_xOptionWnd;					//�ɼ�â.
	CHorseWnd			m_xHorseWnd;					//��â.
	CMagicWnd			m_xMagicWnd;					//����â.
	CNoticEditWnd		m_xNoticeEditWnd;				//���İ���â.
	CBeltWnd			m_xBeltWnd;
	CSiegeWnd			m_xSiegeWnd;					//�߼���������
	CMarketWnd			m_xMarketWnd;					//���� ������ �ŷ� ������
	CMarketUpWnd		m_xMarketUpWnd;					//���� ������ ��� ������
	CMessengerWnd		m_xMessengerWnd;				//�޽���
	CFaceImgUpWnd		m_xFaceImgUpWnd;				//�������
	CUtilWnd			m_xUtilWnd;						//��ƿ
	CViewMiniMapWnd		m_xViewMiniMapWnd;				//�̴ϸ� ���
	CChatWnd			m_xChatWnd;						//ä��â
	CSettingWnd			m_xSettingWnd;					//ȯ�漳��â
	CMagicShortcutWnd	m_xMagicShortcutWnd;			//��������Űâ
	CMarketExWnd		m_xMarketExWnd;					// ��������â
	CInventoryExWnd		m_xInventoryExWnd;				// �߰� ����


	CGameOver			m_xGameOverWnd;					//��������.

	CHAR				m_pszLastCapture[MAX_PATH];

	INT					m_nTopWndID;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

public:
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// �ʱ�ȭ, ����, ����.
//---------------------------------------------------------------------------------------------------------------//
	VOID			Init();
	VOID			Destroy();
	VOID			CreateInterface(CImageHandler* pxImgHandler);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// ä�ø޽������� �Լ�.
//---------------------------------------------------------------------------------------------------------------//
	VOID			MsgAdd(DWORD dwFontColor, DWORD dwFontBackColor, CHAR* pszMsg = NULL);
	BOOL			MsgDelete();					// �޽��� ����.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// �����������̽����� �Լ�.
//---------------------------------------------------------------------------------------------------------------//
	VOID			RenderInterface(INT nLoopTime, POINT ptMousePos);	// ȭ�鿡 �������̽� ���úκ��� �����ش�.

	VOID			SetCaputeString(CHAR* pszChat);

	VOID			ShowWndList();
	VOID			ShowChatList();
	VOID			ShowLargeChatList();
	VOID			ShowBeltItem();
	VOID			ShowGameStatus();
	VOID			ShowMagicKey();

	VOID			ShowSystemChat();
	VOID			ShowNormalChat();
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// ��Ʈ����.
//---------------------------------------------------------------------------------------------------------------//
	BOOL				CheckItemPosOLD(CHAR* szName);
	BOOL				CheckItemPos(CHAR* szName);
	BOOL				SaveItemPos(CHAR* szName);

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

	int					FindSameItemInBelt(CItem xItem);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// ������ ����Ʈ ���� �� ����ġ �����Լ�.
//---------------------------------------------------------------------------------------------------------------//
	INT				GetWindowInMousePos(POINT ptMouse);
	VOID			AddWindowToList(INT nID);
	VOID			DeleteWindowToList(INT nID);

	BOOL			WindowActivate(INT nID);
	VOID			WindowFocusChangedAndSetReadyMove(INT nID, POINT ptMouse);
	VOID			MoveTopWindow(POINT ptMouse);
	VOID			AllWindowsFocusOff();
	BOOL			IsTopWindow(INT nID);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

	VOID			SetViewMode();
	BOOL			CanViewModeChange();

	BOOL			UpdateUserPicInfo(CHAR *szName, INT nFaceImg);
	BOOL			LoadUserPic(CHAR *szName, INT nDate);
	VOID			DrawJobPic(BYTE bJob);

	BOOL			LoadFACFile(char *szFileName, CWHSurface *m_hbmFaceImg);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Message Funtion.
//---------------------------------------------------------------------------------------------------------------//
	BOOL			OnSysKeyDown(WPARAM wParam, LPARAM lParam);
	BOOL 			OnKeyDown(WPARAM wParam, LPARAM lParam);
	BOOL 			OnKeyUp(WPARAM wParam, LPARAM lParam);
	BOOL			OnLButtonDown(POINT ptMouse);
	BOOL			OnRButtonDown(POINT ptMouse);
	BOOL			OnLButtonUp(POINT ptMouse);
	BOOL			OnMouseMove(POINT ptMouse);
	BOOL			OnScrollDown();
	BOOL			OnScrollUp();
	BOOL			OnLButtonDoubleClick(POINT ptMouse);
	BOOL			OnMsgInputted(WPARAM wParam, LPARAM lParam);
	LRESULT			OnMsgBoxReturn(WPARAM wParam, LPARAM lParam);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

	VOID			ItemClickSound(CItem* pxItem);
	VOID			ItemUseSound(CItem* pxItem);
	VOID			ChatListClear();
	VOID			ChangeChatSize();

	VOID			ShowGroupMember();

// ���� ������ ����
public:
	VOID			SetExpireAbilitys();
	VOID			GetExpireTime( INT nExpireTime, INT& nYear, INT& nMonth, INT& nDay, INT& nHour, INT& nMin );
	VOID			ShowExpireAbilitys();

	BOOL			m_bDrawExpireAbilitys;
	
	INT				m_nExpireCnt;
	ITEMSTATE		m_TExpireState[ TEXPIREABILITYS::NUM_ITEMS ];	
	TEXPIREABILITYS	m_TExpireAbilitys;
};



#endif // _INTERFACE_H




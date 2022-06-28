#ifndef _INTERFACE_H
#define _INTERFACE_H

// 유료 아이템 정보
typedef struct _tagTExpireAbilitys
{
	INT		nItemExExpireTime;			// 추가 가방 만료시간

	INT		nSavedItemExExpireTime;		// 추가 창고 만료시간
	
	FLOAT	fExpRate;					// 경험치 추가 비율
	INT		nExpRateExpireTime;			// 경험치 추가 비율 만료시간
	
	FLOAT	fDropRate;					// 드랍율 추가 비율
	INT		nDropRateExpireTime;		// 드랍율 추가 비율 만료시간
	
	FLOAT	fMiningRate;				// 채광률 추가 비율
	INT		nMiningRateExpireTime;		// 채광률 추가 비율 만료시간

	INT		nIgnoreLevelExpireTime;		// 몬스터 레벨 무시 만료시간
	
	INT		nUserTitleExprieTime;		// 유저 타이틀 만료시간

	enum { NUM_ITEMS = 7 };

} TEXPIREABILITYS, *LPTEXPIREABILITYS;

class CInterface
{ 
public:
	 CInterface();
	~CInterface();
public:
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// 좌측상단의 Message 관리.
//---------------------------------------------------------------------------------------------------------------//
	ClientSysMsg	m_xClientSysMsg;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Main Interface 처리변수.
//---------------------------------------------------------------------------------------------------------------//
	CWHWilImageData*	m_pxInterImg;					// 게임상에서 사용할 인터페이스 이미지.
//	CWHWilImageData		m_xInterImgEx;					// 인터페이스 관련 이미지.

	COMMONITEMSET		m_stCommonItem;					// 공용 아이템 저장(마우스 아이템).
	RECT				m_rcMain;						// 메인인터페이스 전체 영역.

	RECT				m_rcHPS;						
	RECT				m_rcMPS;						
	RECT				m_rcExpS;						
	RECT				m_rcWetS;						

	RECT				m_rcChatLine[_MAX_CHATLINE];	// 5줄의 채팅영역.
	RECT				m_rcLargeChatLine[_MAX_CHATLINE];	// 14줄의 채팅영역.

	RECT				m_rcChat;						// 채팅창 영역.
	RECT				m_rcLargeChat;					// 커다란 채팅창 영역.
	INT					m_nFstLine;						// 채팅화면라인의 제일 윗줄이 가리키는 채팅리스트의 번호인덱스.
	INT					m_nFstLineInLarge;
	CList<CHAT>			m_xChatlist;					// 나누어진 채팅 데이타.
	CList<CHAT>			m_xLargeChatlist;				// 나누어진 채팅 데이타 - 큰 채팅창용.


	INT					m_nFstLineInSystemChat;
	RECT				m_rcSystemChat;
	RECT				m_rcSystemChatLine[_SYSTEM_CHATLINE];	// 4줄의 채팅영역.
	CList<CHAT>			m_xSystemChat;

	INT					m_nFstLineInNormalChat;
	RECT				m_rcNormalChat;
	RECT				m_rcNormalChatLine[_SYSTEM_CHATLINE];	// 4줄의 채팅영역.

	CList<CHAT>			m_xNormalChat;

	RECT				m_rcLargeChatRgn;				// 메인인터페이스 전체 영역.


	CDLList<CHAT>		m_xChat;						// 나누어진 채팅 데이타.

	CDLList<INT>		m_xWndOrderList;				
	BOOL				m_bMoveFocusedWnd;

	// 벨트관련.
	SHORT				m_shBeltHeight;
	BYTE				m_bBeltState;
	RECT				m_rcBeltCell[_BELT_MAX_CELL];
	ITEMSET				m_stBeltItem[_MAX_BELT_ITEM];

	CGameBtn			m_xInterBtn[_NEW_MAX_INTER_BTN];	// 버튼.
	CGameBtn			m_xInterBtnofSiege;					// 발석거버튼.
	CGameBtn			m_xInterBtnofNewMessage;			// 새메세지버튼.
	CGameBtn			m_xInterBtnFaceImgUp;				// 이미지 업로드 버튼.


	CScrlBar			m_xScrlBarInSmallChat;
	CScrlBar			m_xScrlBarInLargeChat;

	BOOL				m_bShowKey;
	BOOL				m_bNewFliker;
	DWORD				m_dwNewFliker;

	INT					m_nIdxMsgBox;					

	DWORD				m_dwViewModeClickTick;				// 화면좌우측(가방, 장착) 이동 가능여부체크틱.

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
// 귓말 리스트 관련, 저장 매크로관련.
//---------------------------------------------------------------------------------------------------------------//
	CList<CHAT>			m_xHearList;
	INT					m_nSelHearNum;
	LONG 				CtrlNumPushed(WPARAM wParam, LPARAM lParam);
	VOID				SetHearList();
	LPCHAT				FindHearList(CHAR* pszHear);
	VOID				AddHearList(CHAR* pszHear);
	VOID				LoadHearList();					// 해당서버, 해당 캐릭.
	VOID				SaveHearList();					// 해당서버, 해당 캐릭.
	VOID				ShowHearList();

	BYTE				*m_temp;

	CList<CHAT>			m_xMacroList;
	INT					m_nSelMacroNum;
	LONG 				AltNumPushed(WPARAM wParam, LPARAM lParam);
	VOID				SetMacroList();
	LPCHAT				FindMacroList(CHAR* pszMacro);
	VOID				AddMacroList(CHAR* pszMacro);
	VOID				LoadMacroList();				// 해당서버, 해당 캐릭.
	VOID				SaveMacroList();				// 해당서버, 해당 캐릭.
	VOID				ShowMacroList();
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Main Interface 에서 관리하는 Window.
//---------------------------------------------------------------------------------------------------------------//
	CInventoryWnd		m_xInventoryWnd;				//가방윈도우.
	CStatusWnd			m_xStatusWnd;					//캐릭터 정보 보기윈도우(3개).
	CStoreWnd			m_xStoreWnd;					//상점윈도우.
	CExchangeWnd		m_xExchangeWnd;					//교환윈도우.
	CGuildWnd			m_xGuildWnd;					//문원윈도우.
	CGroupWnd			m_xGroupWnd;					//그룹윈도우.
	CUserStateWnd		m_xUserStateWnd;				//그룹입력윈도우.
	CChatPopWnd			m_xChatPopWnd;					//그룹입력윈도우.
	CNPCWnd				m_xNPCWnd;						//NPC 대화창.
	CQuestWnd			m_xQuestWnd;					//퀘스트창.
	COptionWnd			m_xOptionWnd;					//옵션창.
	CHorseWnd			m_xHorseWnd;					//말창.
	CMagicWnd			m_xMagicWnd;					//마법창.
	CNoticEditWnd		m_xNoticeEditWnd;				//문파공지창.
	CBeltWnd			m_xBeltWnd;
	CSiegeWnd			m_xSiegeWnd;					//발석거윈도우
	CMarketWnd			m_xMarketWnd;					//유저 아이템 거래 윈도우
	CMarketUpWnd		m_xMarketUpWnd;					//유저 아이템 등록 윈도우
	CMessengerWnd		m_xMessengerWnd;				//메신저
	CFaceImgUpWnd		m_xFaceImgUpWnd;				//사진등록
	CUtilWnd			m_xUtilWnd;						//유틸
	CViewMiniMapWnd		m_xViewMiniMapWnd;				//미니맵 뷰어
	CChatWnd			m_xChatWnd;						//채팅창
	CSettingWnd			m_xSettingWnd;					//환경설정창
	CMagicShortcutWnd	m_xMagicShortcutWnd;			//무공단축키창
	CMarketExWnd		m_xMarketExWnd;					// 원보상점창
	CInventoryExWnd		m_xInventoryExWnd;				// 추가 가방


	CGameOver			m_xGameOverWnd;					//게임종료.

	CHAR				m_pszLastCapture[MAX_PATH];

	INT					m_nTopWndID;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

public:
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// 초기화, 삭제, 생성.
//---------------------------------------------------------------------------------------------------------------//
	VOID			Init();
	VOID			Destroy();
	VOID			CreateInterface(CImageHandler* pxImgHandler);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// 채팅메시지관련 함수.
//---------------------------------------------------------------------------------------------------------------//
	VOID			MsgAdd(DWORD dwFontColor, DWORD dwFontBackColor, CHAR* pszMsg = NULL);
	BOOL			MsgDelete();					// 메시지 삭제.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// 메인인터페이스관련 함수.
//---------------------------------------------------------------------------------------------------------------//
	VOID			RenderInterface(INT nLoopTime, POINT ptMousePos);	// 화면에 인터페이스 관련부분을 보여준다.

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
// 벨트관련.
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
// 윈도우 리스트 관리 및 상태치 설정함수.
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

// 유료 아이템 정보
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




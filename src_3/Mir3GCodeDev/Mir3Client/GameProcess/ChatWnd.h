#ifndef _CHATWND_H
#define _CHATWND_H




class CChatWnd : public CGameWnd
{ 
// Constructor & Destructor
public:
	CChatWnd();
	~CChatWnd();
// Attributes
public:

	CGameBtn				mChat_BtnExpand;
	CGameBtn				mChat_BtnClose;
	CGameBtn				mChat_BtnMode;
	CGameBtn				mChat_BtnRotate;

	CScrlBar				mChat_xScrlChat;

	INT						mChat_nMode;

	INT						mChat_nShowMode;


	INT						mChat_nSurfaceW, mChat_nSurfaceH;
	INT						mChat_nSX, mChat_nSY;
	INT						mChat_nNumMiddleImg;

	CList<CHAT>				mChat_xChatlist;					// 전체 채팅
	INT						mChat_nFstLineInAll;
	INT						mChat_nMaxLineInAll;
	
//	CList<CHAT>				mChat_xNormalChatlist;				// 일반 채팅
	INT						mChat_nFstLineInNormal;
	INT						mChat_nMaxLineInNormal;

//	CList<CHAT>				mChat_xShoutChatlist;				// 외치기 채팅
	INT						mChat_nFstLineInShout;
	INT						mChat_nMaxLineInShout;

//	CList<CHAT>				mChat_xGroupChatlist;				// 그룹 채팅
	INT						mChat_nFstLineInGroup;
	INT						mChat_nMaxLineInGroup;

//	CList<CHAT>				mChat_xGuildChatlist;				// 문파 채팅
	INT						mChat_nFstLineInGuild;
	INT						mChat_nMaxLineInGuild;

	BOOL					mChat_bLargeChat;
	LPDIRECTDRAWSURFACE7	mChat_pddsSurface;				// Texture Img Surface;

	RECT					mChat_rcTopImg;
	RECT					mChat_rcMiddleImg;
	RECT					mChat_rcBottomImg;

	RECT					mChat_rcChat;

	RECT					mChat_rcChatLine[_MAX_CHATLINE];

	CHAR					m_pszLastCapture[MAX_PATH];


// Operations
public:
	virtual VOID Init();
	virtual VOID Destroy();

	

	VOID	CreateChatWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend);
	VOID	ShowChatWnd();

	BOOL	OnLButtonDown(POINT ptMouse);
	BOOL	OnLButtonUp(POINT ptMouse);
	BOOL	OnMouseMove(POINT ptMouse);
	VOID	OnScrollDown();
	VOID	OnScrollUp();

	VOID	MoveEditBox();

	VOID	MoveChatWnd(POINT ptMouse);

	VOID	SetChatWndTextr(LPDIRECT3DDEVICE7 pd3dDevice);
	VOID	ChangeToSmallChat();

	VOID	ActiveEditBox();

	VOID	MsgAdd(DWORD dwFontColor, DWORD dwFontBackColor, CHAR* pszMsg);
	VOID	ChatListClear();
	VOID	ShowChatList();

	VOID	SetCaputeString(CHAR* pszChat);
	BOOL	SetCaputeString(POINT ptMouse);
	VOID	SetHearList();

	VOID	ChangeChatSize();
};



#endif // _CHATWND_H
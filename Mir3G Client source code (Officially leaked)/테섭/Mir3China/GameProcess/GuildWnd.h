#ifndef _CGUILDWND_H
#define _CGUILDWND_H

class CGuildMsgList
{
public:
	CHAR			m_szData[4096];
};

class CGuildWnd : public CGameWnd
{
public:
	CHAR			m_szGuildName[64];
	BOOL			m_bIsGM;
	BYTE			m_bShowType;				// 0 공지사항, 1 문원목록, 2 문파채팅.
	INT				m_nStartLine;

	CList<CGuildMsgList>	m_xMemberList;
	CList<CGuildMsgList>	m_xEditMemberList;

	CList<CGuildMsgList>	m_xNoticeList;
	CList<CGuildMsgList>	m_xEditNoticeList;

	CList<CGuildMsgList>	m_xGuildChatList;

	CGameBtn		m_xGuildBtn[_MAX_GUILD_BTN];

	CScrlBar		m_xGuildScrlBar;

	CHAR			m_szTemp[4096];

	INT				m_nStep;

public:
	CGuildWnd();
	~CGuildWnd();

	virtual VOID Init();
	virtual VOID Destroy();

	VOID	CreateGuildWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove);
	VOID	ShowGuildWnd();
	VOID	ShowNotice();
	VOID	ShowMemberList();
	VOID	ShowGuildChatList();

	VOID	MsgAdd(CHAR* pszMsg);

	VOID	SetStatusBtnInit();
	VOID	DevideGuildHome(CHAR *pszMsg);
	VOID	AddGuildHome(CHAR *pszMsg);

	VOID	DevideGuildMemberList(CHAR *pszMsg);
	VOID	AddGuildMemberList(CHAR *pszMsg);
public:
//  메시지 함수.
	BOOL	OnLButtonDown(POINT ptMouse);
	BOOL	OnLButtonUp(POINT ptMouse);
	BOOL	OnMouseMove(POINT ptMouse);
	LRESULT OnMsgBoxReturn(WPARAM wParam, LPARAM lParam);
	
	VOID	OnScrollDown();
	VOID	OnScrollUp();
};


#endif // _CGUILDWND_H
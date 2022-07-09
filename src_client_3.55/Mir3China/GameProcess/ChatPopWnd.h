#ifndef _CCHATPOPWND_H
#define _CCHATPOPWND_H

class CChatPopWnd : public CGameWnd
{ 
private:
protected:
	CDLList<CHAT>	m_xstrDividedChat;		// 나누어진 채팅 데이타.
	
	CGameBtn		m_xChatPopBtn[_MAX_CHATPOP_BTN];
	RECT			m_rcChatPopFrame;			// 채팅영역.
	INT				m_nFstLine;					// 채팅화면라인의 제일 윗줄이 가리키는 채팅리스트의 번호인덱스.

	CScrlBar		m_xChatPopBar;

	RECT			m_rcChatPopLine[_MAX_CHATLINE_POPUP];				// 5줄의 채팅영역.
	CHAR			m_pszLastChatPopCapture[MAX_PATH];

	BOOL			SetCaputeString(POINT ptMouse);

public:
	RECT			m_rcEditBoxFrame;			

public:
	CChatPopWnd();
	~CChatPopWnd();

	virtual VOID Init();
	virtual VOID Destroy();

	BOOL	MsgAdd(DWORD dwFontColor, DWORD dwFontBackColor, CHAR* szMsg = NULL);

	VOID	CreateChatPopWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend);
	VOID	ShowChatPopWnd();
	VOID	SetStatusBtnInit();
public:
//  메시지 함수.
	BOOL	OnLButtonDown(POINT ptMouse);
	BOOL	OnLButtonUp(POINT ptMouse);
	BOOL 	OnMouseMove(POINT ptMouse);

	VOID	OnScrollDown();
	VOID	OnScrollUp();
	BOOL	OnKeyDown(WPARAM wParam, LPARAM lParam);
};


#endif // _CCHATPOPWND_H

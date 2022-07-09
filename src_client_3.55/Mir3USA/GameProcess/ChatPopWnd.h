#ifndef _CCHATPOPWND_H
#define _CCHATPOPWND_H

class CChatPopWnd : public CGameWnd
{ 
private:
protected:
	CDLList<CHAT>	m_xstrDividedChat;		// �������� ä�� ����Ÿ.
	
	CGameBtn		m_xChatPopBtn[_MAX_CHATPOP_BTN];
	RECT			m_rcChatPopFrame;			// ä�ÿ���.
	INT				m_nFstLine;					// ä��ȭ������� ���� ������ ����Ű�� ä�ø���Ʈ�� ��ȣ�ε���.

	CScrlBar		m_xChatPopBar;

	RECT			m_rcChatPopLine[_MAX_CHATLINE_POPUP];				// 5���� ä�ÿ���.
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
//  �޽��� �Լ�.
	BOOL	OnLButtonDown(POINT ptMouse);
	BOOL	OnLButtonUp(POINT ptMouse);
	BOOL 	OnMouseMove(POINT ptMouse);

	VOID	OnScrollDown();
	VOID	OnScrollUp();
	BOOL	OnKeyDown(WPARAM wParam, LPARAM lParam);
};


#endif // _CCHATPOPWND_H

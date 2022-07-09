/******************************************************************************************************************
                                                                                                                   
	����:																											
																													
	�ۼ���:																											
	�ۼ���:																											
																													
	[����][������] : ���� ����																						
                                                                                                                   
*******************************************************************************************************************/


#ifndef _CHATEDITBOX_H
#define _CHATEDITBOX_H


class CChatEdit
{
//1: Constructor/Destructor
public:
	CChatEdit();
	~CChatEdit();
protected:
	HWND	m_hChatEdit;
	HWND	m_hMainWindow;

	DWORD	m_dwFontColor;
	BOOL	m_bSetEnterUse;

	WNDPROC	m_WndProcChatEdit;

public:
	HFONT	m_hFontChatEdit;

	BOOL	m_bUsePassMode;

	CHAR	m_szInputMsg[MAX_PATH];

	__inline	VOID SetEnterUse(BOOL bUse) { m_bSetEnterUse = bUse; }
	__inline	HWND GetSafehWnd()			{ return m_hChatEdit; }
	void		SetHanguelMode();
	VOID		SetAlphaNumericMode();
	BOOL		Create(HINSTANCE hInstance, HWND hWndParent, INT nX, INT nY, INT nXsize, INT nYSize);
	BOOL		DestroyDialog();
	BOOL		SetLimitText(INT nLimitText);
	__inline	VOID SetSelectAll() { SendMessage(m_hChatEdit, EM_SETSEL, 0, (LPARAM)-1); }
public:
//4: Message Map
	virtual	LRESULT CALLBACK ChatEditProc(HWND hWndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
};


#endif // _CHATEDITBOX

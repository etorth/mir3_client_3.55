#ifndef _SELECTCHARWND_H
#define _SELECTCHARWND_H

class CCharLine
{
public:
	char	m_pszScriptText[64];
	RECT	m_Rect;
	bool	m_fIsSelected;
	bool	m_fIsFocused;

public:
	CCharLine()
	{
		m_pszScriptText[0]	= NULL;
		m_fIsFocused		= FALSE;
		m_fIsSelected		= FALSE;
	}
	~CCharLine()
	{
	}
};

class CSelectCharWnd : public CGameWnd
{ 
public:
	CSelectCharWnd();
	~CSelectCharWnd();
	virtual VOID Init();
	virtual VOID Destroy();

	VOID	CreateSelectCharWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove);
	VOID	ShowSelectCharWnd();

	VOID	ShowAddChar();
	VOID	ShowDelChar();
	VOID	HideChars();
	VOID	SendCommand(CHAR* szCharName);
	
	CGameBtn	m_xButton[4];
	CGameBtn	m_xButtonClose;
	CPDLList<CCharLine>	m_ScriptList;
	INT		m_nStartLine;
	INT		m_nCommand;
	VOID	SetCommand(INT nCommand){ 	m_nCommand = nCommand; }
public:
	BOOL	OnLButtonDown(POINT ptMouse);
	BOOL	OnLButtonUp(POINT ptMouse);
	VOID	OnMouseMove(POINT ptMouse);

	VOID	OnScrollDown();
	VOID	OnScrollUp();
};

#endif // _CGROUPWND_H
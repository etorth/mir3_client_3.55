#ifndef _CNPCWnd_H
#define _CNPCWnd_H

#define SCRIPT_GENTEXT			1
#define SCRIPT_BUTTON			2
#define SCRIPT_RETURN			3
#define SCRIPT_TAG				4

typedef struct
{
	BYTE	m_btScriptType;
	char	*m_pszScriptText;
	char	*m_pszScriptCommand;
	RECT	m_rcScriptRect[5];
	bool	m_fIsSelected;
	bool	m_fIsFocused;
}CScriptLine, *LPCScriptLine;

class CNPCWnd : public CGameWnd
{
/* Constructor & Destructor */
public :
	CNPCWnd();
	~CNPCWnd();

/* Attributes */
public:
	INT						m_nNpcId;
	CGameBtn				m_xNPCBtn[_MAX_NPC_BTN];

	BOOL					m_bCanClose;
	CWHWilImageData			m_xNPCImage;

protected:
	int						m_nStartLine;
	int						m_nMaxLine;
	CScrlBar				m_xNPCScrlBar;
	CHAR					m_pszSaveCmd[MAX_PATH];
	DWORD					m_dwLastNPCTick;

private:
	INT						m_nSurfaceW, m_nSurfaceH;
	INT						m_nSX, m_nSY;
    LPDIRECTDRAWSURFACE7	m_pddsSurface;				// Texture Img Surface;
	VOID					SetNPCWndTextr(LPDIRECT3DDEVICE7 pd3dDevice);
	VOID					ShowNpcWnd();


	INT						m_nNpcMsgState;
	int						mNpcwnd_nNumMiddleWindow;
	RECT					mNpcwnd_rcTopImg;
	RECT					mNpcwnd_rcMiddleImg;
	RECT					mNpcwnd_rcBottomImg;
	RECT					mNpcwnd_rcTopWnd;
	RECT					mNpcwnd_rcMiddleWnd;
	RECT					mNpcwnd_rcBottomWnd;
	BYTE					mNpcwnd_bBright;
	BYTE					mNpcwnd_bOpa;
	bool					mNpcwnd_bHasImage;
	int						mNpcwnd_nCharCount;
	int						mNpcwnd_nLineCnt;
	bool					mNpcwnd_bShowScroll;
	bool					mNpcwnd_bShowFlickeringDownBtn;
	int						mNpcwnd_bShowFlickeringTimer;
	int						mNpcwnd_nMaxShowLine;

	INT						mNpcwnd_nHeightMiddleWindow;
	INT						mNpcwnd_nSumOfTopBottomLine;
	INT						mNpcwnd_nMaxMiddleWndCount;

	
/* Operation */
public:
	VOID					CreateNPCChatWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, 
											 INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove);
	VOID					ShowNPCChatWnd();	
	void					ResetDialog();
	VOID					SetNpcEditBoxPos(VOID);
	VOID					SetWndRectReduce(VOID);
	VOID					SetWndRectExtend(VOID);
	BOOL					OnLButtonDown(POINT ptMouse);
	BOOL					OnLButtonUp(POINT ptMouse);
	BOOL					OnMouseMove(POINT ptMouse);
	BOOL					OnMsgInputted(VOID);
	LRESULT					OnMsgBoxReturn(WPARAM wParam, LPARAM lParam);
	VOID					OnScrollDown();
	VOID					OnScrollUp();
	VOID					OnEnterKeyDown(VOID);
	VOID					Init();
	VOID					Destroy();
	VOID					SetStatusBtnInit();
	VOID					CreateNpcwnd(CWHWilImageData* pxWndImage);
	void					NpcWndCountLineNumInScript(char *pszScript);
	char*					NpcWndCheckText(char *pszScript, int *nCnt);
	BOOL					NpcWndSetScriptsRect(CScriptLine* pScriptLine, RECT rcRect);
	void					NpcWndSetScriptsRectInit();
	void					NpcWndScriptInit();

	char*					CheckText(char *pszScript);
	char*					AddScriptLine(char *pszLine, int nLineLen, int nType);
	void					DevideScript(char *pszScript);
	


	__inline void			SetNPC(int nNPCID) { m_nNpcId = nNPCID; }	

	virtual	VOID			SetGameWndActive(BOOL bActive);
	virtual	VOID			ShowGameWnd();
};

#endif // _CNPCWnd_H
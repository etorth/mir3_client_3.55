/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/


#ifndef _LOGINPROC_H
#define	_LOGINPROC_H


typedef struct tagSVRLIST
{
	CHAR  pszCaption[MAX_PATH];
	CHAR  pszName[MAX_PATH];
	RECT  rcRgn;
}SVRLIST, *LPSVRLIST;


typedef struct tagNOTICE
{
	CHAR   pszMsg[MAX_PATH];
	INT	   nSize;
	INT    nBC;
	INT	   nFC;
	INT    nWeight;

	tagNOTICE()
	{
		ZeroMemory(pszMsg, MAX_PATH);
		nSize = 9;
		nBC   = 0;
		nFC   = 2;
		nWeight = FW_NORMAL;
	}
}NOTICE, *LPNOTICE;


class CLoginProcess : public CWHDefProcess
{
protected:

public:
	 CLoginProcess();
	~CLoginProcess();

public:
	CHAR				m_pszSvrIP[MAX_PATH];
	INT					m_nSvrPort;

private:
	BOOL				m_bBGMPlay;
	DWORD				m_dwBGMPlayTime;			
//	ClientSysMsg		m_xClientSysMsg;

	CGameMsgBox			m_xMsgBox;

	CWHWilImageData		m_xImageInter;		// GameInter.wil
	CWHWilImageData		m_xImageLogin;		// interface1c.wil

	CAvi				m_xAvi;				// 상황에 맞게 Load, Release;

	BYTE				m_bProcState;		// Wemade Logo, Login, Server Select.
	BYTE				m_bBackState;		// Wemade Logo, Login, Still 화면.

	POINT				m_ptMousePos;

	HBRUSH				m_hBrush;

	D3DVERTEX			m_avBillBoard[4];

	
	RECT				m_rcSvrListRgn;
	CList<SVRLIST>		m_stSvrList;
	INT					m_nClickedSvr;

	CGameBtn			m_xLoginBtn[_MAX_LOGIN_BTN];

	BYTE				m_bLoginInputState;	// None, ID, PW.
	CHAR				m_pszID[MAX_PATH];
	CHAR				m_pszPW[MAX_PATH];
	RECT				m_rcEditID;
	RECT				m_rcEditPW;

	INT					m_nFadeProcTime;

	HSNDOBJ				m_stOpenSnd;

	INT					m_nBackIdx;

public:
	VOID	SetEditFocus();

private:
	

	VOID	SetSvrBtn();
	VOID	OnConnectToServer();
	CHAR*	OnMessageReceive(CHAR* pszBuf, INT nLen);
	VOID	OnSocketMessageReceive(CHAR* pszMsg);
//	VOID	GetErrorMsg(INT nMsg, CHAR* pszMsg);

	INT			GetSvrNum(POINT ptMouse);
	LPSVRLIST	GetSvrList(INT nNum);

	HRESULT DrawBillBoard(LPDIRECT3DDEVICE7 lpDevice, D3DVECTOR* pvTrans, D3DVECTOR* pvScale, /*D3DVECTOR vRot, */D3DMATERIAL7* pmtrl, /*FLOAT fRotRad, */LPDIRECTDRAWSURFACE7 lpddsTextr, BYTE bBlendType = _BLEND_NORMAL);

	VOID	RenderBackground(INT nLoopTime);
	VOID	RenderLogin();
	VOID	RenderSvrSel();
	VOID	RenderFade(INT nLoopTime);

	LRESULT OnKeyDown(WPARAM wParam, LPARAM lParam);
	LRESULT OnDestroy(WPARAM wParam, LPARAM lParam);
	LRESULT	OnLButtonDown(WPARAM wParam, LPARAM lParam);
	LRESULT	OnLButtonUp(WPARAM wParam, LPARAM lParam);
	LRESULT	OnMouseMove(WPARAM wParam, LPARAM lParam);
	LRESULT	OnMove(WPARAM wParam, LPARAM lParam);
	LRESULT	OnMsgBoxReturn(WPARAM wParam, LPARAM lParam);

	virtual LRESULT DefMainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);





	RECT				m_rcNotice;
	CList <NOTICE>		m_xNoticeList;

	BOOL	LoadNoticeText();
	VOID	ShowNotice(INT nLoopTime);
	VOID	ReleaseNoticeText();

	VOID	DrawEffect(INT nIdx, INT nX, INT nY);






public:
	VOID	Init();
	VOID	Load();
	VOID	DeleteProc();
	VOID	SetNextProc();
	VOID	RenderScene(INT nLoopTime);

	inline  VOID SetSvrIP(CHAR* pszSvrIP)
	{
		strcpy(m_pszSvrIP, pszSvrIP);
	}
	inline  VOID SetSvrPort(INT nPort)
	{
		m_nSvrPort = nPort;
	}
};


#endif // _LOGINPROC_H
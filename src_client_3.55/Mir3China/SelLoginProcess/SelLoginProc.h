/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/


#ifndef _SELLOGINPROC_H
#define	_SELLOGINPROC_H

typedef struct tagSERVERINFO
{
	char	szServerName[32];
	char	szLoginSectionName[32];
	char	szPatchSectionName[32];
} SERVERINFO, *LPSERVERINFO;


	typedef struct tagMIRINIINFO
	{
		char		szLoginSvrAddr[16];
		char		szParam1[64];
		char		szParam2[64];
		char		szParam3[64];
		char		szServerList[1024];
	} MIRINIINFO;

	typedef struct tagMIRPATCHINFO
	{
		char		szServerIP[128];
		char		szBaseDirectory[256];
	} MIRPATCHINFO;


class CSelLoginProcess : public CWHDefProcess
{
protected:

public:
	 CSelLoginProcess();
	~CSelLoginProcess();

	struct sTextureNode
	{
		char					szKey[16];
		WORD					nFileType, nFileIdx, nImgIdx;
		CWHWilImageData*		pImg;
		IDirectDrawSurface7*	pSurface;
		DWORD					nLastTick;
	};


private:
	CWHWilImageData		m_xImageLogin;		// interface1c.wil
	char				m_szProfileFullName[256];

//	SERVERINFO			m_xServerInfo[40];
	MIRINIINFO			m_MirInfo;
	MIRPATCHINFO		m_MirPatchInfo;

	CList<SERVERINFO>	m_xServerInfo;
	CScrlBar			m_xScrSelectMenu;
	INT					m_nMenuStart;

	INT					m_nSerNameCnt;

	POINT				m_ptAreaBtn[40];
	CHAR				m_szServerName[40][MAX_PATH];
	CHAR				m_szScreenName[40][MAX_PATH];
	INT					m_nAreaBtnCount;
	RECT				m_rcAreaBtn[40];
	INT					m_nSelectedAreaBtn;

	INT					m_nSvrBtnCount;
	RECT				m_rcSvrBtn[40];
	INT					m_nSelectedSvrBtn;

	POINT				m_ptMousePos;

	sTextureNode*		m_pObj;

	LPDIRECTDRAWSURFACE7 m_lpddsTextr;

	CGameBtn			m_xCloseBtn;


private:
	VOID	SetEditFocus();

	VOID	OnConnectToServer();
	CHAR*	OnMessageReceive(CHAR* pszBuf, INT nLen);
//	VOID	GetErrorMsg(INT nMsg, CHAR* pszMsg);

	HRESULT DrawBillBoard(LPDIRECT3DDEVICE7 lpDevice, D3DVECTOR* pvTrans, D3DVECTOR* pvScale, /*D3DVECTOR vRot, */D3DMATERIAL7* pmtrl, /*FLOAT fRotRad, */LPDIRECTDRAWSURFACE7 lpddsTextr, BYTE bBlendType = _BLEND_NORMAL);

	VOID	RenderBackground(INT nLoopTime);
	VOID	RenderLogin();
	VOID	RenderSvrSel();
	VOID	RenderFade(INT nLoopTime);

	LRESULT OnDestroy(WPARAM wParam, LPARAM lParam);
	LRESULT	OnLButtonDown(WPARAM wParam, LPARAM lParam);
	LRESULT	OnLButtonUp(WPARAM wParam, LPARAM lParam);
	LRESULT	OnMouseMove(WPARAM wParam, LPARAM lParam);
	LRESULT	OnWheel(WPARAM wParam, LPARAM lParam);
	LRESULT	OnMove(WPARAM wParam, LPARAM lParam);
	LRESULT	OnMsgBoxReturn(WPARAM wParam, LPARAM lParam);

	virtual LRESULT DefMainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HRESULT RestoreImg(sTextureNode* pstTextrNode);
	HRESULT CopyDToSToS(DWORD dwWidth, DWORD dwHeight, WORD* pwSrc, LPDIRECTDRAWSURFACE7 lpddsDst);
	HRESULT CopyDToS(DWORD dwWidth, DWORD dwHeight, WORD* pwSrc, LPDIRECTDRAWSURFACE7 lpddsDst);

	VOID	LoadServerList();
	VOID	MakeIniFile();
	VOID	WriteMirProfile();
	VOID	WriteMirPatchProfile();
	char*	GetCaptionName( int nIndex, char *pszText, char *pszFileName );

	VOID	QuitProgram(BOOL bRestart);


public:
	VOID	Init();
	VOID	Load();
	VOID	DeleteProc();
	VOID	SetNextProc();
	VOID	RenderScene(INT nLoopTime);
};


#endif // _SELLOGINPROC_H
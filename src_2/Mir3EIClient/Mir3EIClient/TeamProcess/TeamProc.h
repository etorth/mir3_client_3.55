#ifndef _TEAMPROC_H
#define	_TEAMPROC_H

class CClientSocket;

#define MIR3_TEAM_INIFILE	"Team.ini"
#define MIR3_TEAM_SECTION	"TEAMMUMBER"
#define MIR3_TEAM_USER		"user"
#define MIR3_TEAM_PASSWD	"passwd"
#define MIR3_TEAM_SERVER	"server"
#define MIR3_TEAM_CHARNAME	"charname"


class CTeamProcess : public CWHDefProcess
{
protected:
	VOID	OnSvrMsgNewMap(_TDEFAULTMESSAGE	*ptdm, char *pszMapName);
	VOID	OnSvrMsgLogon(_TDEFAULTMESSAGE	*ptdm, char *pszMsg);
	VOID	OnSvrMsgHear(_TDEFAULTMESSAGE *ptdm, char *pszMsg);

	char	m_szBuff[8192];
	int		m_nBuff;

	//////////////////////私有数据
	BOOL	m_bLoad;
	INT		m_nProcState;	//_LOGIN_PROC,_SVR_SEL_PROC,_CHAR_SEL_PROC,_GAME_PROC
	char	m_szServerIP[16];	//每一步的ip
	INT		m_nServerPort;
	INT		m_nCertifyCode;	//验证码
	char	m_szUser[32];
	char	m_szPasswd[32];
	char	m_szServer[32];
	char	m_szCharName[32];
	VOID	ReadIniFileForTeam();//读取配置文件Team.ini
	void	ProcessLogin(char* pszMsg);//登陆
public:
	 CTeamProcess();
	~CTeamProcess();
public:
	CDecodeMessage			m_DecMsg;//ydq
	CHAR					m_szMapName[MAX_PATH];
	MEMMAPPEDID				m_stMemMappedID[_VIEW_CELL_Y_COUNT][_VIEW_CELL_X_COUNT];
	BOOL					m_bRender;

	CTeamHero*				m_pMyHero;//MyHero
	CClientSocket*			m_pSocket;

	CPDLList<CMagic>		m_xMagicList;
	CPDLList<CMagic>		m_xGroundMagicList;
	///////////////////////////////////////
	CPDLList<CActor>		m_xActorList;//共享

	CPDLList<GROUNDITEM>&	m_stMapItemList;//地上的物品
	CMapHandler&			m_xMap;		//共享,改成引用,减少内存消耗
	CImageHandler&			m_xImage;//共享, 改成引用
	POINT					m_ptMousePos;
	POINT					m_ptCurrTile;//因为地图改变了,有偏差,

	CActor*					m_pxMouseTargetActor;
	CActor*					m_pxMouseOldTargetActor;
	CActor*					m_pxSavedTargetActor;

	//商人位置用于计算MyHero和NPC的距离,关闭NPC对话框,用处不大
	WORD					m_wNPCWndPosX, m_wNPCWndPosY;

	////////////////////////////////////////////////


	CWHQueue				m_xWaitPacketQueue;	//人/怪物行动消息
	CWHQueue				m_xWaitDefaultPacketQueue;//人/怪物消失

	WORD					m_wInputDelayTime;
	WORD					m_wCurrInputDelayTime;



	LRESULT OnRButtonDown(WPARAM wParam, LPARAM lParam);
	LRESULT OnLButtonDown(WPARAM wParam, LPARAM lParam);
	LRESULT OnLButtonUp(WPARAM wParam, LPARAM lParam);
	LRESULT OnRButtonUp(WPARAM wParam, LPARAM lParam);

	void				OnProcPacketNotEncode(char *pszMsg);

	void				OnSocketMessageRecieve(char *pszMsg);

	virtual VOID		OnConnectToServer();
	virtual char*		OnMessageReceive(CHAR* pszMessage);

	LRESULT OnTimer(WPARAM wParam, LPARAM lParam);
	LRESULT OnDestroy(WPARAM wParam, LPARAM lParam);
	virtual LRESULT DefMainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	BOOL	GetLoad() { return m_bLoad;}
public:
	VOID	Init();
	VOID	Load(DWORD dwMsgFilter);
	VOID	DeleteProc();

//	VOID	DropItemShow();
	VOID	LoadMapChanged(CHAR* szMap);

	VOID	AutoTargeting();//自动攻击目标

//	BOOL	ReceivePacket(CHAR* szMsg, INT nPacketLen);
//	VOID	RenderObject(INT nLoopTime);
//	VOID	DrawObject(INT nXCnt, INT nYCnt, INT nObject);
	VOID	RenderScene(INT nLoopTime);

	BOOL	CheckMove(INT nX, INT nY, INT nSpeed, POINT* ptDestTile = NULL, INT* nDestDir = NULL);
	VOID	CheckMappedData(INT nLoopTime, BOOL bIsMoveTime);


	/*检查是否在长距攻击范围内*/
	BOOL	TargetInLongAttack(BYTE bDir);

	VOID	ProcessPacket();
	VOID	ProcessDefaultPacket();

	CActor*	FindActor(int nID); // gadget

};



#endif //_TEAMPROC_H
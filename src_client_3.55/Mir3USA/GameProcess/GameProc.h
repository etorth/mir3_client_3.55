/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/


#ifndef _GAMEPROC_H
#define	_GAMEPROC_H

typedef struct tagMEMMAPPEDID
{
	CActor*			pxActor[_MAX_CELL_OBJ];
	CMagic*			pxMagic[_MAX_CELL_OBJ];
	LPGROUNDITEM	pstItem[_MAX_CELL_OBJ];
	LPEVENTIMG		pstEvent[_MAX_CELL_OBJ];
}MEMMAPPEDID, *LPMEMMAPPEDID;

typedef struct tagCREDIT
{
	CHAR   pszMsg[MAX_PATH];
	INT	   nSize;
	INT    nBC;
	INT	   nFC;
	INT    nWeight;

	tagCREDIT()
	{
		ZeroMemory(pszMsg, MAX_PATH);
		nSize = 9;
		nBC   = 0;
		nFC   = 2;
		nWeight = FW_NORMAL;
	}
}CREDIT, *LPCREDIT;

typedef struct tagMAGICEFFECTTIME
{
	INT				nKind;
	INT				nTime;
	DWORD			dwInputTime;
}MAGICEFFECTTIME, *LPMAGICEFFECTTIME;

class CGameProcess : public CWHDefProcess
{
protected:
	VOID	OnSvrMsgResetMap(LPPACKETMSG lpPacketMsg);
	VOID	OnSvrMsgLogon(LPPACKETMSG lpPacketMsg);
	VOID	OnSvrMsgHear(_TDEFAULTMESSAGE *ptdm, char *pszMsg);
	VOID	OnSvrMsgAbility(LPPACKETMSG lpPacketMsg);
	VOID	OnSvrMsgSubAbility(LPPACKETMSG lpPacketMsg);

public:
	 CGameProcess();
	~CGameProcess();
public:
	BOOL					m_bDrawName;
	BOOL					m_bStatusView;
	BOOL					m_bTileView;
	BOOL					m_bCellView;
	BOOL					m_bObj1View;
	BOOL					m_bObj2View;
	BOOL					m_bStopPtView;
	BOOL					m_bShowSnow;
	BOOL					m_bSnowOn;
	BOOL					m_bShowMist;
	BOOL					m_bShowRain;
	BOOL					m_bShadowABlend;
	BOOL					m_bShowFPS;
	BOOL					m_bDebugInfo;
	BOOL					m_bRunTarget;
	BOOL					m_bAutoTarget;
	BOOL					m_bChatSave;
	BOOL					m_bVerChk;
	BOOL					m_bViewMonInfo;

	BOOL					m_bNoticeCehcked;

	BOOL					m_bUseHotKey;



	// 견혼령 체크
	// by eriastoa 2006.03.28
	BOOL					m_bCheckBigLight;
	DWORD					m_dwChkTimerBigLight;




	CHAR					m_szMapName[MAX_PATH];
	MEMMAPPEDID				m_stMemMappedID[_VIEW_CELL_Y_COUNT][_VIEW_CELL_X_COUNT];

	CList<CActor>			m_xActorList;
	CList<CMagic>			m_xMagicList;
	CList<GROUPPOS>			m_stGroupPosList;
	CList<CMagic>			m_xGroundMagicList;
	CList<GROUNDITEM>		m_stMapItemList;
	CList<EVENTIMG>			m_stEventImgList;

	CImageHandler			m_xImage;
	CMapHandler				m_xMap;
	CInterface				m_xInterface;
	HBRUSH					m_hBrush;
	CMyHero					m_xMyHero;
	POINT					m_ptMousePos;
	POINT					m_ptCurrTile;
	BOOL					m_bRender;
	BYTE					m_bDayState;
	BYTE					m_bFogState;
	CLightFog				m_xLightFog;
	CMist					m_xMist;
	CSnow					m_xSnow;
	CScatter				m_xScatter;
	CRain					m_xRain;
	CFlyingTail				m_xFlyingTail;
	CSmoke					m_xSmoke;
	CBoom					m_xBoom;
	CGameMsgBox				m_xGameMsgBox;

	CElec					m_xElec;

	CNoticeBox				m_xNotice;

	CActor*					m_pxMouseTargetActor;
	CActor*					m_pxExplainActor;
	CActor*					m_pxMouseOldTargetActor;
	CActor*					m_pxSavedTargetActor;
	CActor*					m_pxAutoSavedTargetActor;
	CActor*					m_pxAutoSavedMagicActor;

	CWHQueue				m_xWaitPacketQueue;	
	CWHQueue				m_xWaitDefaultPacketQueue;	

	INT						m_nAreaState;

	DWORD					m_dwInputDelayTime;
	DWORD					m_dwCurrInputDelayTime;

	FLOAT					m_fDarkRate;

	FLOAT					m_fTileLightRed;
	FLOAT					m_fTileLightGreen;
	FLOAT					m_fTileLightBlue;

	WORD					m_wShadowClr[800];

	D3DMATRIX				m_matWorld;

	DWORD					m_dwMonShowTick;
	DWORD					m_dwNPCClickTick;

	BOOL					m_bPlayBGM;
	DWORD					m_dwMapMoveTime;

	VOID					RenderFadeState(INT nLoopTime);

	VOID					CheckMagicUseActor(CActor* pxActor);

	BOOL					RenderShine(INT nLoopTime);

	INT						m_nNPCWndPosX, m_nNPCWndPosY;

	RECT					m_rcDiceBoard;
	BOOL					m_bDiceModeActive;
	DWORD					m_dwDicePlayTime;
	DWORD					m_dwCurrDicePlayTime;
	CHAR					m_pszCmd[MAX_PATH];
	DICEINFO				m_stDiceInfo[_MAX_DICE];

	VOID					SetDiceMode(LPPACKETMSG lpPacketMsg);
	VOID					RenderDiceMode(INT nLoopTime);

	BYTE					m_bFateState;
	DWORD					m_dwFadeTime;
	
//  Speed Hack관련.	
	DWORD					m_dwFindHackTime;

	DWORD					m_dwClientActTick;
	DWORD					m_dwServerActTick;
	FLOAT					m_fTickSum;			// 30단위로 모아서 평균을 낸다.
	INT						m_nTickCnt;
	FLOAT					m_fHackTickRate;
	INT						m_nHackCnt;

//	Packet Hack
	BYTE					m_bNoticeSeed1;
	BYTE					m_bNoticeSeed2;
	WORD					m_wNoticeSeed3;
	WORD					m_wNoticeSeed4;

//	인벤토리윈도우 출력시 좌우 화면조정관련.
	BYTE					m_bViewMode;		// 0:보통, 1:상태창떳을때, 2:인벤토리창떳을때.
	INT						m_nViewLGapX;
	INT						m_nViewRGapX;

//  Event Message 관련
	INT						m_nMsgImgIdx;
	BOOL					m_bDrawEventMsg;
	RECT					m_rcEventMsg;
	CList<CHAT>				m_xEventMsglist;	// 이벤트 메세지 리스트
	DWORD					m_dwEventMsgTimer;
	DWORD					m_dwEventMsgMaxTime;
	BOOL					m_bIsNpcImg;

	BOOL					m_bShowPaySys;

	BOOL					m_bShowBloodNum;

	BOOL					m_bDrawGroundItemName;

	DWORD					m_dwPickUpTime;
	BOOL					m_bAutoPickup;
	BOOL					m_bDrawHealthNum;

	BOOL					m_bAutoMagic;

	BOOL					m_bAttackUser;
	BOOL					m_bDrawMagicLight;

	BOOL					m_ShowAddOn;

	BOOL					m_bShowHelmet;
	BOOL					m_bShowMonEffect;
	BOOL					m_bShowDeying;
	// Timer 관련
	SYSTEMTIME				m_stSysTime;
	CHAR					m_szTime[15];

//  FindHack 관련
	HINSTANCE				m_hFindHackDll;

	BOOL					m_bSetMiniMap;

	CWHSurface				m_hbmMouse;

	BOOL					m_bCreditShow;
	CList <CREDIT>			m_xCreditList;
	RECT					m_rcCredit;

	INT						m_nIdxCreditBack;

	CWHWilImageData			m_xImageLogin;		// interface1c.wil

	BOOL					m_bUseSpell;
	DWORD					m_dwSpellTimer;


	CHAR					m_szSocket[MAX_PATH];

	LPDIRECTDRAWSURFACE7	lpddsMagicTextrtest;

	BOOL					m_bHasTarget;
	BOOL					m_bIncreaseX;
	BOOL					m_bIncreaseY;
	INT						m_nMoveDir;
	DWORD					m_dwAutoTimer;

	DWORD					m_dwNameQueryTimer;

	BOOL					m_bShowLoading;
	INT						m_nLoadImg;

	INT						m_nLoadTxtImg;
	DWORD					m_dwLoadTxtTimer;

	DWORD					m_dwScreenModeTimer;

	CList <MAGICEFFECTTIME>	m_xMagicEftTimeList;		

	virtual LRESULT DefMainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	void				OnProcPacketNotEncode(char *pszMsg);

	void				OnSocketMessageReceive(char *pszMsg);

	virtual VOID		OnConnectToServer();
	virtual char*		OnMessageReceive( char *pBuf, int nLen );

	BOOL	ShowMonExplain(INT nIdx, INT nX, INT nY);

	LRESULT OnKeyDown(WPARAM wParam, LPARAM lParam);
	LRESULT OnKeyUp(WPARAM wParam, LPARAM lParam);
	LRESULT OnMouseMove(WPARAM wParam, LPARAM lParam);
	LRESULT OnRButtonDown(WPARAM wParam, LPARAM lParam);
	LRESULT OnLButtonDown(WPARAM wParam, LPARAM lParam);
	LRESULT OnLButtonUp(WPARAM wParam, LPARAM lParam);
	LRESULT OnRButtonUp(WPARAM wParam, LPARAM lParam);
	LRESULT OnMove(WPARAM wParam, LPARAM lParam);
	LRESULT OnSysKeyDown(WPARAM wParam, LPARAM lParam);
	LRESULT OnSysKeyUp(WPARAM wParam, LPARAM lParam);
	LRESULT OnMsgInputted(WPARAM wParam, LPARAM lParam);
	LRESULT OnWheel(WPARAM wParam, LPARAM lParam);
	LRESULT OnLButtonDoubleClick(WPARAM wParam, LPARAM lParam);
	LRESULT OnTimer(WPARAM wParam, LPARAM lParam);
	LRESULT OnDestroy(WPARAM wParam, LPARAM lParam);
	LRESULT OnMsgBoxReturn(WPARAM wParam, LPARAM lParam);

public:
	VOID	Init();
	VOID	Load();
	VOID	DeleteProc();
	VOID	SetNextProc();

	VOID	DropItemShow();

	VOID	ShowAreaState();

	VOID	AutoTargeting();
	VOID	AutoRunTargeting();

	VOID	ProcessRecvPacket();
	VOID	ProcessDelQue();

	BOOL	ReceivePacket(CHAR* szMsg, INT nPacketLen);
	VOID	RenderObject(INT nLoopTime);
	VOID	RenderEvent(INT nMapViewX, INT nMapViewY);
	VOID	RenderGroundItem(INT nMapViewX, INT nMapViewY);
	VOID	RenderActorList(INT nMapViewX, INT nMapViewY, BOOL bDeadDraw = FALSE);
	VOID	RenderGroundMagic(INT nMapViewX, INT nMapViewY);
	VOID	RenderScene(INT nArgLoopTime);

	BOOL	CheckMove(INT nX, INT nY, INT nSpeed, POINT* ptDestTile = NULL, INT* nDestDir = NULL);
	VOID	CheckMappedData(INT nLoopTime, BOOL bIsMoveTime);

	VOID	RenderMapTileGrid();
	VOID	CommandAnalyze();

	BOOL	TargetInLongAttack(BYTE bDir);

	BOOL	CanGameOut();

	VOID	ProcessPacket();
	VOID	ProcessDefaultPacket();

	VOID	CloseNPCWindow();

	VOID	ActorListClear();
	VOID	GroundMagicListClear();
	VOID	MagicListClear();


	CActor*	FindActor(int nID);
	LPGROUPPOS FindGroupPos(INT nID);
	VOID CheckGroupPosValidate();
	CActor*	FrontActor(INT nXPos, INT nYPos, BYTE bDir, INT nGap);
	BOOL	GenerateAcotor(LPPACKETMSG lpPacketMsg);

	INT		DecriptInt(char* szStr);
	WORD	DecriptWord(char* szStr);

	VOID	RenderEventMessage();
	VOID	AddEventMessage(CHAR* pszMsg);

	VOID	ShowGraphicNum(POINT ptLoc, INT nNum);

	VOID	AutoPickUp();

	BOOL	NeedAutoTarget(DWORD wKey);

	VOID	CheckMarketWindow(CActor* pxNpc);

	VOID	EncriptInt(byte * Value, char * pBuf);

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	LPEVENTIMG	FindEvent(INT nType, INT nX, INT nY);
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	BYTE	*JpegFileToRGB(CHAR * fileName, UINT *width, UINT *height);
	BOOL	BGRFromRGB(BYTE *buf, UINT widthPix, UINT height);
	BOOL	VertFlipBuf(BYTE  * inbuf, UINT widthBytes, UINT height);
	BYTE	*MakeDwordAlignedBuf(BYTE *dataBuf, UINT widthPix, UINT height, UINT *uiOutWidthBytes);
	
	void	j_putRGBScanline(BYTE *jpegline, int widthPix, BYTE *outBuf, int row);
	void	j_putGrayScanlineToRGB(BYTE *jpegline, int widthPix, BYTE *outBuf, int row);

	BOOL	Convert24To16(BYTE *pOrgImage, BYTE bOrgImgBitCount, WORD *pwImage, INT nWidth, INT nHeight);

	virtual VOID ShowStatus(INT nStartX, INT nStartY);

	char*	CheckAbnormalName(char *pszName);
	VOID	LoadCredit();
	VOID	ShowCredit(INT nLoopTime);
	VOID	ShowMagicEffectTime();
	VOID	CheckMagicEffectTime();
};



#endif //_GAMEPROC_H
#ifndef _CACTOR_H
#define _CACTOR_H



/******************************************************************************************************************

	CActor Class

*******************************************************************************************************************/
#pragma pack(1)
typedef struct tagMESSAGEBODYWL
{
	LONG	lParam1;
	LONG	lParam2;
	LONG	nTag1;			// 때린놈 ID.(SM_STRUCK일때).
	LONG	nTag2;
}MESSAGEBODYWL, *LPMESSAGEBODYWL;

typedef struct tagMESSAGEBODYW
{
	WORD	wParam1;
	WORD	wParam2;
	WORD	wTag1;			// 때린놈 ID.(SM_STRUCK일때).
	WORD	wTag2;
}MESSAGEBODYW, *LPMESSAGEBODYW;

typedef struct tagCHARDESC
{
	LONG	nFeature;
	LONG	nStatus;
	INT		nFaceImageDate;
    BYTE	bGuildFlag;
    BYTE	bFlagRed;
    BYTE	bFlagGreen;
    BYTE	bFlagBlue;
//	WORD	wLooks;
}CHARDESC, *LPCHARDESC;

typedef struct tagFEATURE
{
	BYTE	bGender; 
	BYTE	bWeapon;
	BYTE	bDress; 
	BYTE	bHair;
}FEATURE, *LPFEATURE;

typedef struct tagMONSTERSTATUSINFO
{
	CHAR	szSpeed;
	CHAR	szAc;
	CHAR	szMcType;
	CHAR	szMac[7];
}MONSTERSTATUSINFO, *LPMONSTERSTATUSINFO;

typedef struct tagMONTYPE
{
	int						nTaiming;
	int						nDead;
	MONSTERSTATUSINFO		stMonStats;
}MONTYPE, *LPMONTYPE;

typedef struct tagAFTERIMAGE
{
	DWORD				m_dwFrame;
	DWORD				m_dwFstFrame;
	DWORD				m_dwEndFrame;
	DWORD				m_dwMoveNextFrmCnt;
	INT					m_nPosX;
	INT					m_nPosY;
	INT					m_nShiftPixelX;
	INT					m_nShiftPixelY;
	BYTE				m_bMoveSpeed;
	BYTE				m_bMtn;
	BYTE				m_bMoveDir;
}AFTERIMAGE, *LPAFTERIMAGE;




typedef struct tagACTORCRIPT
{
	INT					m_nIdentity;					// ID Index From Server.
	BYTE				m_bMoveSpeed;					// 이동속도.

	INT					m_nDelay;						// 현재 동작에 대한 지연시간.

	BYTE				m_bHPPercent;
	WORD				m_wMAXHP;
	WORD				m_wHP;
	WORD				m_wMP;
	INT					m_nOpenHealth;

	BYTE				m_bLightSize;					// Actor주변의 광원크기.
}ACTORCRIPT, *LPACTORCRIPT;

#pragma pack(8)
class CActor
{
private:
public:
//	INT					m_nGenPacket;
//	INT					m_nRecvPacketCnt;
//	CList<PACKETMSG>	m_xRecvPacketList;

//	INT					m_nIdentity;					// ID Index From Server.
			
	CWHSurface	m_hbmFaceImg;	
	INT	m_nDividedChatLine;	
	BYTE	m_bMoveSpeed;	// 이동속도.
	DWORD	m_dwFstFrame;	// 현재 동작의 시작 프레임.
	DWORD	m_dwEndEffectFrame;	// 캐릭터 Effect마지막 프레임.
	AFTERIMAGE	m_xAfterImage[10];	
	FEATURE	m_stHitter;	
	CWHWilImageData*	m_pxActorImage;	// 이미지를 얻어올 포인터들.
	INT	m_nShiftTileX;	// 현재 자신의 타일에서 X축만큼 이동한 타일의 거리.
	BYTE	m_bFlagBlue;	
			
	INT	m_nPosY;	// 타일 Y좌표.
	DWORD	m_dwCurrFrame;	// 현재 프레임.
			
	BYTE	m_bEftFeature;	

	// 2006.07.03 - 신규의복 이펙트
	INT		m_nEft;
	CWHWilImageData*	m_pxDragonImage;				// 용갑옷 이미지 포인터 - 2006.07.03 -신규의복 이펙트
	RECT				m_rcDragon;						// 용갑옷 Actor 영역




	CHAR	m_szFoo2[2];	// 캐릭터나 몬스터의 이름.
			
	BYTE	m_bCurrDir;	// 현재 방향.
			
			
	MONTYPE	m_stMonType;	
	WORD	m_wMAXHP;	
			
			
	BOOL	m_bABlendRev;	
	BYTE	m_bEffectImgIdx;	// 현재 Actor가 가질 이미지구조체의 번호.
	INT	m_nPlayIdx1;	
	DWORD	m_nTimerAfterImg;	
	BYTE	m_bFlagGreen;	
	INT	m_nPosX;	// 타일 X좌표.
	BYTE	m_bMoveDir;	// 현재 방향.
	DWORD	m_dwSturnTimer;	
	INT	m_nCharState;	
	CHAR	m_szFoo1[1];	// 캐릭터나 몬스터의 이름.
			
	INT	m_nABlendDelay;	
	BYTE	m_bMoveNextFrmCnt;	
	BOOL	m_bNeedLoadFameImg;	
			
	CHAR	m_szGuildName[64];	
	CWHQueue	m_xPacketQueue;	// Actor가 처리해야될 메시지를 저장하고 있는 큐.
	INT	m_nABlendCurrDelay;	
	BOOL	m_bUseSwordEffect;	// 검법효과 사용.
	BOOL	m_bUseEffect;	// 이펙트프레임을 사용.
			
			
	CHAR	m_szChatMsg[MAX_PATH];	// 채팅메시지.
	INT	m_nShiftPixelX;	// 현재 자신의 타일에서 X축만큼 이동한 픽셀의 거리.
			
	INT	m_nCurrDelay;	// 현재 지연시간.
	BOOL	m_bIsMoved;	
			
			
	DWORD	m_wCurrChatDelay;	
	INT	m_nHealthSeed;	
	BOOL	m_bLatestFaceImg;	
	BYTE	m_bLightRadius[2];	// 광원 너비.
	BYTE	m_bLightColor [2][3];	// 광원 색.
			
	POINT	m_ptShowBlood[8];	
			
	BOOL	m_bIsDead;	
	CHAR	m_szChatMsgArg[8][MAX_PATH];	// 채팅메시지를 5개의 스트링으로 구분한것.
	D3DVERTEX	m_avBoard[4];	
			
	BOOL	m_bFstSoundPlayed;	
	WORD	m_wHP;	
	FEATURE	m_stFeature;	// 캐릭터의 외형을 결정짓는다.
	INT 	m_nShowBlood[8];	
	BYTE	m_bDelStruckCnt;	// SM_STRUCK이 왔을때 맞는 동작을 생략하기 위해 지운 패킷의 수.
			
			
	BOOL	m_bReverse;	
	WORD	m_wStateClr;	
	INT	m_nScrnPosX;	// 중심점을 고려하지 않은 화면상의 X좌표.
	RECT	m_rcTargetRgn;	// 현재 Actor의 타겟영역.
	DWORD	m_dwFstEffectFrame;	// 캐릭터 Effect처음 프레임.
	BYTE	m_bEffectBlend;	// 브렌드종류.
	DWORD	m_dwEndFrame;	// 현재 동작의 마지막프레임.
	CHAR	m_szShowName[3][64];	
	BYTE	m_bEffectOpa;	// 투명도.
	WORD	m_wMonColor;	// 추가변수. 몬스터 염색색.
	BYTE	m_bGuildFlag;	
			
	BYTE	m_bBackStepFrame;	
	BYTE	m_bFlagRed;	
	INT	m_nScrnPosY;	// 중심점을 고려하지 않은 화면상의 Y좌표.
	INT	m_nShiftPixelY;	// 현재 자신의 타일에서 Y축만큼 이동한 픽셀의 거리.
	RECT	m_rcActor;	// 현재 스크린상의Actor의 사각 영역.
			
	WORD	m_wMP;	
	WORD	m_wEffectLooks;	
	INT	m_nIdentity;	// ID Index From Server.
	BYTE	m_bHPPercent;	
	WORD	m_dwShowBloodTimer[8];	
	INT	m_nOpenHealth;	
	BYTE	m_bCurrMtn;	// 현재 동작.
			
	BYTE	m_bEffectFrameCnt;	
	INT	m_nFaceImageDate;	
	BYTE	m_bLightSize;	// Actor주변의 광원크기.
	INT	m_nShiftTileY;	// 현재 자신의 타일에서 Y축만큼 이동한 타일의 거리.
			
	CHAR	m_szName[64];	// 캐릭터나 몬스터의 이름.
	BYTE	m_bAppearState;	
	DWORD	m_dwNameClr;	
	BOOL	m_bWarMode;	
	BOOL	m_bIsSturn;	
	CHAR	m_szRankName[64];	
	CHAR	m_szFoo3[3];	// 캐릭터나 몬스터의 이름.
	BYTE	m_bActorImgIdx;	// 현재 Actor가 가질 이미지구조체의 번호.
	DWORD	m_dwCurrMoveSkip;	
	BYTE	m_bEffectFrame;	
			
			
	BYTE	m_bJob;	
	DWORD	m_dwWarModeTime;	
	INT	m_nShowBloodIdx;	
	CHAR	m_szMateName[64];	
			
			
	INT	m_nDelay;	// 현재 동작에 대한 지연시간.
	INT	m_nStrurnFrame;	
			
	BOOL	m_bMsgHurryCheck;	// 메시지가 2개이상 쌓여있을때는 프레임을 1프레임씩을 건너뛴다.
	BYTE	m_bBackStepFrameCnt;	
	BYTE	m_bEffectColor[3];	// 색.
			
	DWORD	m_dwCurrEffectFrame;	// 캐릭터 Effect현재 프레임.
			
	INT	m_nPlayIdx2;	
			
	BOOL	m_bLoadFaceImg;	
public:
//---------------------------------------------------------------------------------------------------------------//
// 생성자 및 소멸자.
	CActor();
	virtual ~CActor();

	virtual VOID InitActor();
	virtual VOID DestroyActor();
//---------------------------------------------------------------------------------------------------------------//

//---------------------------------------------------------------------------------------------------------------//
// 생성.
	virtual BOOL Create(CImageHandler* pxImgHandler, FEATURE* pstFeature, BYTE bMtn, BYTE bDir, INT nPosX, INT nPosY);
//---------------------------------------------------------------------------------------------------------------//

	BOOL LoadEffect(CImageHandler* pxImgHandler, WORD wEffectNum, BYTE bDir = 0, int nElement = -1);
	VOID DrawWithEffected(INT nx, INT nY, INT nXSize, INT nYSize, WORD* pwSrc, WORD wChooseColor1 = 0XFFFF, WORD wChooseColor2 = 0XFFFF, BOOL bFocused = FALSE, BYTE bOpa = 50, WORD wState = _STATE_NOTUSED);
//---------------------------------------------------------------------------------------------------------------//
// 프레임 설정관련.
	BOOL	CheckFeatureValidate(FEATURE stFeature);
	BOOL	ChangeFeature(FEATURE stFeature);
	virtual BOOL SetMotionFrame(BYTE bMtn, BYTE bDir, DWORD dwDelay = 0);
//---------------------------------------------------------------------------------------------------------------//

//---------------------------------------------------------------------------------------------------------------//
// 캐릭터 이동.
	VOID SetMoving();
	VOID SetMovingAfterImage();
	VOID SetBackStepMoving();
	VOID SetMoved();
	WORD GetCharState();
//---------------------------------------------------------------------------------------------------------------//

	VOID ChatMsgAdd();
	VOID ShowMessage(INT nLoopTime);
	VOID StruckMsgReassign();
	VOID DrawCharLight(BOOL bUseScrnPos = TRUE);
	
	virtual VOID PlayActSound();

//---------------------------------------------------------------------------------------------------------------//
// 동작 진행.
	virtual BOOL UpdatePacketState();
	virtual VOID UpdateMotionState(INT nLoopTime, BOOL bIsMoveTime);
	virtual BOOL UpdateMove(BOOL bIsMoveTime);

// 유형별 패킷상태적용.
	virtual VOID OnCharDescPacket(LPPACKETMSG lpPacketMsg);
	virtual VOID OnUserName(LPPACKETMSG lpPacketMsg);
	virtual VOID OnChangeNameClr(LPPACKETMSG lpPacketMsg);
	virtual VOID OnChangeLight(LPPACKETMSG lpPacketMsg);
	virtual VOID OnOpenHealth(LPPACKETMSG lpPacketMsg);
	virtual VOID OnCloseHealth(LPPACKETMSG lpPacketMsg);
	virtual VOID OnFeatureChanged(LPPACKETMSG lpPacketMsg);
	virtual VOID OnHealthSpellChanged(LPPACKETMSG lpPacketMsg);
	virtual VOID OnWalk(LPPACKETMSG lpPacketMsg);
	virtual VOID OnTurn(LPPACKETMSG lpPacketMsg);
	virtual VOID OnDigup(LPPACKETMSG lpPacketMsg);
	virtual VOID OnDigDown(LPPACKETMSG lpPacketMsg);
	virtual VOID OnDeath(LPPACKETMSG lpPacketMsg);
	virtual VOID OnAlive(LPPACKETMSG lpPacketMsg);
	virtual VOID OnBackStep(LPPACKETMSG lpPacketMsg);
	virtual VOID OnStruck(LPPACKETMSG lpPacketMsg);
	virtual VOID OnHit(LPPACKETMSG lpPacketMsg);
	virtual VOID OnFlyAxe(LPPACKETMSG lpPacketMsg);
	virtual VOID OnLighting(LPPACKETMSG lpPacketMsg);
	virtual VOID OnCharStatusChanged(LPPACKETMSG lpPacketMsg);

	virtual VOID OnSpaceMoveShow(LPPACKETMSG lpPacketMsg);
	virtual VOID OnSpaceMoveHide(LPPACKETMSG lpPacketMsg);

	VOID	MakeDeathEffect(WORD wDress);
	BOOL	CheckMultiLineName(char *pszName);
//---------------------------------------------------------------------------------------------------------------//

//---------------------------------------------------------------------------------------------------------------//
// Rendering.
	virtual BOOL DrawActor(CMapHandler* pxMap, BOOL bFocused = FALSE, BOOL bShadowAblended = FALSE, 
		                   BOOL bUseScrnPos = TRUE, BOOL bDrawShadow = TRUE);
	virtual VOID DrawHPBar(INT nX = -1, INT nY = -1);
	virtual VOID DrawHPNum();
	virtual VOID DrawName();

	BOOL DrawEffect();
	VOID MakeMagicStream(WORD wMagicID, INT nTarID, INT nTarX, INT nTarY);	// 염사장, 빙사장, 뢰인장부가효과등을 만든다.
	VOID MakeMagicStreamEx(WORD wMagicID, INT nStartX, INT nStartY, INT nTarX, INT nTarY);	// 빙렬파
//---------------------------------------------------------------------------------------------------------------//
protected:
public:
};












/******************************************************************************************************************

	CNPC Class

*******************************************************************************************************************/
class CNPC : public CActor
{
private:
private:
public:
	virtual VOID OnHit(LPPACKETMSG lpPacketMsg);
	virtual VOID OnTurn(LPPACKETMSG lpPacketMsg);
	virtual BOOL UpdatePacketState();
	virtual VOID UpdateMotionState(INT nLoopTime, BOOL bIsMoveTime);
	virtual BOOL DrawActor(CMapHandler* pxMap, BOOL bFocused = FALSE, BOOL bShadowAblended = FALSE, 
		                   BOOL bUseScrnPos = TRUE, BOOL bDrawShadow = TRUE);
};


















/******************************************************************************************************************

	CHero Class

*******************************************************************************************************************/
#pragma pack(1)
typedef struct tagFEATUREEX
{
	BYTE		bHorse;
	WORD		wDressColor;
	WORD		wHairColor;
	BYTE		bWeaponColor;

	INT			nEft;	// 2006.07.03 - 신규의복 이펙트

	//INT			nIcon;	// 아이콘
}FEATUREEX, *LPFEATUREEX;
#pragma pack(8)

class CHero : public CActor
{
private:
public:
									
	DWORD	m_dwCurrWeaponFrame;							
									
	INT	m_nAfterPosY;							
	BOOL	m_bUseHErgum;							
	BYTE	m_bHorseImgIdx;	//	현재	Actor	말이	가질	이미지구조체의	번호.
									
									
	DWORD	m_dwThunderTimer;							
	INT	m_nDelayTemp1400;							
	DWORD	m_dwAfterTimer;							
	INT	m_nSaveIdx;							
	INT	m_dwAmorTimer;							
	DWORD	m_dwCurrHairFrame;							
	BOOL	m_bPahwangbo;							
	BOOL	m_bViewDigFragment;							
	CWHWilImageData*	m_pxWeaponImage;							
	BYTE	m_bBackSwingCnt;							
	INT	m_nDelaySeed1400_1;							
	BYTE	m_bShieldCurrFrm;							
	INT	m_nDelaySeed1000_3;							
	RECT	m_rcHair;							
	BOOL	m_bUseHManwol;							
	BYTE	m_bHairImgIdx;	//	현재	Actor	머리가	가질	이미지구조체의	번호.
	INT	m_nDelaySeed1500_2;							
	INT	m_nShieldCurrDelay;							
	BOOL	m_bUseErgum;							
	INT	m_nFame;							
									
	BYTE	m_bHYedoCnt;							
									
	INT	m_nMinTemp370;							
	CWHWilImageData*	m_pxHorseImage;							
									
	INT	m_nDelaySeed1500_3;							
									
	INT	m_nDelayTemp1000;							
	INT	m_nGhostAmorEftIdx;							
	INT		m_nThunderIdx;						
	INT	m_nRushKungPosX;							
									
									
	INT	m_nDelaySeed1500_1;							
	INT	m_nCurrMagicID;							
	BYTE	m_bHRandSwingCnt;							
	CWHWilImageData*	m_pxHairImage;							
	INT	m_nDelayTemp1500;							
									
	BOOL	m_bUseManwol;							
									
	INT	m_nDelaySeed1000_1;							
									
	BYTE	m_bWeaponImgIdx;	//	현재	Actor	무기가	가질	이미지구조체의	번호.
	INT	m_dwGhostAmorTimer;							
	INT	m_nDelaySeed1000_2;							
	BOOL	m_bSetIdx;							
	BOOL	m_bRushKung;							
	BYTE	m_bYedoCnt;							
	INT	m_nAmorEftIdx;							
	BYTE	m_bRandSwingCnt;							
	RECT	m_rcHorse;							
	BOOL	m_bUseBanwol;							
	RECT	m_rcWeapon;							
	SHORT	m_shHitSpeed;							
	FEATUREEX	m_stFeatureEx;							
									
	INT	m_nDelaySeed1400_3;							
									
									
	BOOL	m_bMang;							
	DWORD	m_dwShieldTick;							
									
	INT	m_nDelaySeed1400_2;							
									
	INT	m_nRushKungPosY;							
	BOOL	m_bDrawOnce;							
	INT	m_nMinTemp800;							
	DWORD	m_dwCurrHorseFrame;							
									
	BYTE	m_bFireHitCnt;							
									
	INT	m_nAfterPosX;							

protected:
public:
	CHero();
	~CHero();

	virtual VOID InitActor();
	virtual VOID DestroyActor();

	VOID	ShowShield();
	VOID	ShowPahwangbo();
	VOID	PlayMoveSound();
	VOID	DrawTheSwordEffect(INT nFrame);

	VOID	DrawTheAomorEffect(INT nFrame);		// 2006.07.03 - 신규의복 이펙트

	virtual VOID PlayActSound();
	virtual BOOL ChangeFeature(FEATURE stFeature, FEATUREEX stFeatureEx);
	virtual BOOL Create(CImageHandler* pxImgHandler, BYTE bMtn, BYTE bDir, INT nPosX, INT nPosY, FEATURE* pstFeature, FEATUREEX* pstFeatureEx);
	virtual BOOL UpdatePacketState();
	virtual VOID UpdateMotionState(INT nLoopTime, BOOL bIsMoveTime);
	virtual BOOL UpdateMove(BOOL bIsMoveTime);
	virtual VOID OnRun(LPPACKETMSG lpPacketMsg);
	virtual VOID OnRush(LPPACKETMSG lpPacketMsg);
	virtual VOID OnRushKung(LPPACKETMSG lpPacketMsg);
	virtual VOID OnMagicFire(LPPACKETMSG lpPacketMsg);
	virtual VOID OnMagicFire2(LPPACKETMSG lpPacketMsg);
	virtual VOID OnThrowDot(LPPACKETMSG lpPacketMsg);
	virtual VOID OnSpell(LPPACKETMSG lpPacketMsg);
	virtual VOID OnCharDescPacket(LPPACKETMSG lpPacketMsg);
	virtual VOID OnFeatureChanged(LPPACKETMSG lpPacketMsg);
	virtual VOID OnCharStatusChanged(LPPACKETMSG lpPacketMsg);
	virtual VOID OnBackStep(LPPACKETMSG lpPacketMsg);
	virtual VOID OnDeath(LPPACKETMSG lpPacketMsg);
	virtual VOID OnWalk(LPPACKETMSG lpPacketMsg);
	virtual VOID OnTurn(LPPACKETMSG lpPacketMsg);
	virtual VOID OnSetXY(LPPACKETMSG lpPacketMsg);
	virtual VOID OnStruck(LPPACKETMSG lpPacketMsg);
	virtual VOID OnHit(LPPACKETMSG lpPacketMsg);
	virtual VOID OnButch(LPPACKETMSG lpPacketMsg);
	virtual BOOL DrawActor(CMapHandler* pxMap, BOOL bFocused = FALSE, BOOL bShadowAblended = FALSE, 
		                   BOOL bUseScrnPos = TRUE, BOOL bDrawShadow = TRUE, BOOL bMyTwice = FALSE);
	BOOL		 DrawActorAfterImage(CMapHandler* pxMap, BOOL bFocused = FALSE, BOOL bShadowAblended = FALSE, 
		                   BOOL bUseScrnPos = TRUE, BOOL bDrawShadow = TRUE, INT nOrder = 0);

	virtual VOID DrawHPBar(INT nX = -1, INT nY = -1);
	virtual VOID DrawHPNum();

	virtual VOID OnSpaceMoveShow(LPPACKETMSG lpPacketMsg);

	virtual WORD FindWeaponColor(WORD wColorIdx);
};










/******************************************************************************************************************

	CMyHero Class

*******************************************************************************************************************/
#define _MAX_ATOM_		7

#pragma pack(1)
typedef struct tagACTORABILITY //새서버
{
	BYTE			bLevel;

	WORD			wAC;
	WORD			wMAC;
	DWORD			dwDC;
	DWORD			dwMC;			//원소적용변경 //magic power class   -> makeword(min/max)
	DWORD			dwSC;			//원소적용변경 //sprite energy class    -> makeword(min/max)
	
	WORD			wHP;
	WORD			wMP;

	WORD			wMaxHP;
	WORD			wMaxMP;

	ULONGLONG		dlngExp;
	ULONGLONG		dlngMaxExp;

	WORD			wWeight;
	WORD			wMaxWeight;

	BYTE			bWearWeight;
	BYTE			bMaxWearWeight;
	BYTE			bHandWeight;
	BYTE			bMaxHandWeight;

/*	BYTE			FameLevel;
	BYTE			MiningLevel;
	BYTE			ramingLevel;
	BYTE			FishingLevel;

	int				FameExp;
	int				FameMaxExp;
	int				MiningExp;
	int				MiningMaxExp;
	int				FramingExp;
	int				FramingMaxExp;
	int				FishingExp;
	int				FishingMaxExp;
*/
	WORD			ATOM_DC[_MAX_ATOM_];
	CHAR			ATOM_AC_GOOD[_MAX_ATOM_];
	CHAR			ATOM_AC_BAD[_MAX_ATOM_];
}ACTORABILITY, *LPACTORABILITY;

typedef struct tagACTORSUBABILITY
{
	WORD wAntiMagic;		// 마법회피.
	BYTE bHitPoint;			// 정확.
	BYTE bSpeedPoint;		// 민첩.
	BYTE bAntiPoison;		// 중독회피.
	BYTE bPoisonRecover;	// 중독회복.
	BYTE bHealthRecover;	// 체력회복.
	BYTE bSpellRecover;		// 마력회복.
	BYTE bFameIdx;
}ACTORSUBABILITY, *LPACTORSUBABILITY;

typedef struct tagACCEPTMTN
{
	BYTE	bAcceptMtn;
	BYTE	bAcceptDir;
	SHORT	shEffect;
}ACCEPTMTN, *LPACCEPTMTN;
#pragma pack(8)

class CMyHero : public CHero
{
private:
public:
	BOOL			m_bMyHeroSetted;
//---------------------------------------------------------------------------------------------------------------//
//  캐릭터 보정용 변수.
	DWORD			m_dwMotionLockTime;
	BOOL			m_bInputLock;							// 캐릭터가 동작되면 어떤입력도 받지 않는다.
	BOOL			m_bMotionLock;							// 캐릭터의 동작이 세팅되면 서버에서 동작승인이 오기전까진 어떤동작도 받지 않는다.
//---------------------------------------------------------------------------------------------------------------//

	CMapHandler*	m_pxMap;
	BOOL			m_bCanRun;
	DWORD			m_dwCanRunTick;
	BYTE		    m_bJob;
	INT				m_nGlod;
	ACCEPTMTN		m_stAcceptMtn;
	ACTORABILITY    m_stAbility;
	ACTORSUBABILITY m_stSubAbility;

	INT				m_nOldPosX;								// 현재 행동이 있기전의 타일X좌표.
	INT				m_nOldPosY;
	BYTE			m_bOldDir;								// 현재 행동이 있기전의 방향.

	BYTE			m_bGuildFlag;
    BYTE			m_bFlagColorR;
    BYTE			m_bFlagColorG;
    BYTE			m_bFlagColorB;

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	BOOL			m_bAutoDig;
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//---------------------------------------------------------------------------------------------------------------//
//  캐릭터 Delay관련 변수.
	DWORD			m_dwLastMoveTime;						// 걷기, 뛰기 틱 보관값
	DWORD			m_dwLastHitTime;						// 칼질이 들어갔을때의 틱 보관값.
	DWORD			m_dwLastSpellTime;						// 마법이 들어갔을때의 틱 보관값.
	DWORD			m_dwLastMagicTime;						// 염화결 시전후의 틱보관값.
	DWORD			m_dwLastStruckTime;						// 맞았을때의 틱 보관값.
	DWORD			m_dwLastPKStruckTime;
	DWORD			m_dwLastRushTime;						// 무태보 시전후의 틱보관값.
	DWORD			m_dwLastKickTime;						// 무태보 시전후의 틱보관값.
	DWORD			m_dwLastFireHitTime;					// 염화결 시전후의 틱보관값.

	DWORD			m_dwLastJSHitTime;						// 돌려베기 시전후의 틱보관값.
	DWORD			m_dwLastRSHitTime;						// 마구베기시전후의 틱보관값.


	DWORD			m_dwMagicPKDelayTime;					// 마법으로 사람을 공격했을때의 패널티Delay.(걷기와 뛰기에 적용된다.)
	DWORD			m_dwMagicDelayTime;						// 마법을쓰고 난후 다음마법이 들어갈때까지의 Delay.


	DWORD			m_dwLastWalkTime;
	DWORD			m_dwLastMagicUseTime;
	DWORD			m_dwLastHitUseTime;

	INT				m_nTempWeaponExp;

	INT				m_nPoint;								// 포인트상점, 원보상점


//---------------------------------------------------------------------------------------------------------------//

//---------------------------------------------------------------------------------------------------------------//
//  마법 테스트관련.
	POINT			m_ptDstMagicTile;
	INT				m_nTestMagicID;
	VOID ClientTestSpell(INT nMounseX, INT nMouseY);
	VOID ClientTestMagic();
//---------------------------------------------------------------------------------------------------------------//


protected:
public:
	CMyHero();
	~CMyHero();

	virtual VOID InitActor();
	virtual VOID DestroyActor();

	VOID  SetMotionInit();

	VOID  SetMotionState(BYTE bMtn, BYTE bDir, INT nMouseTargetID = NULL, BOOL bIsDead = FALSE, LPPOINT lpptPos = NULL, SHORT shSkill = -1);
	VOID  SetMapHandler(CMapHandler* pxMap);
	VOID  SetMagic(LPCLIENTMAGICRCD	pstMagic, BYTE bDir, INT nTargetID, FEATURE stTargetFeature, POINT ptTargetPos);
	BOOL  SetOldPosition();
	BOOL  CheckMyPostion();
	VOID  AdjustMyPostion();
	BOOL  CheckDelay();
	POINT GetPosMouseToTile(INT nXPos, INT nYPos);
	POINT GetPosTileToMouse(INT nXPos, INT nYPos);

	virtual BOOL Create(CImageHandler* pxImgHandler, BYTE bMtn, BYTE bDir, INT nPosX, INT nPosY, FEATURE* pstFeature, FEATUREEX* pstFeatureEx);
	virtual VOID OnHealthSpellChanged(LPPACKETMSG lpPacketMsg);
	virtual VOID DrawHPBar(INT nX = -1, INT nY = -1);

	virtual VOID OnSpaceMoveHide(LPPACKETMSG lpPacketMsg);

	virtual BOOL UpdatePacketState();
	virtual VOID UpdateMotionState(INT nLoopTime, BOOL bIsMoveTime);
	virtual BOOL UpdateMove(BOOL bIsMoveTime);
	virtual BOOL DrawActor(BOOL bFocused = FALSE, BOOL bShadowAblended = FALSE, 
		                   BOOL bUseScrnPos = FALSE, BOOL bDrawShadow = TRUE, BOOL bMyTwice = FALSE );

	__inline virtual BOOL ChangeFeature(FEATURE stFeature, FEATUREEX stFeatureEx)
	{
		if ( CHero::ChangeFeature(stFeature, stFeatureEx) )		return TRUE;

		return FALSE;
	}

//---------------------------------------------------------------------------------------------------------------//
//  캐릭터 Delay관련 함수.
	BOOL CanNextHit();									// 지금 칼질할수 있나의 여부. 레벨과 착용무게에 따라 달라진다.
	BOOL CanWalk();										// Delay와 관련지어서 캐릭터가 움직일수 있는지의 여부.
	BOOL CanRun();										// Delay와 관련지어서 캐릭터가 움직일수 있는지의 여부.
//---------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------//
//  유저 입력함수.
	BOOL OnLButtonDown(POINT ptMouse, INT nTargetID = -1, BOOL bIsDead = FALSE, POINT* lpptTargetPos = NULL);
	BOOL OnRButtonDown(POINT ptMouse);
	BOOL OnKeyDown(WPARAM wParam, LPARAM lParam, POINT ptMouse, POINT ptTargetPos, INT nMosueTargetID, FEATURE stTargetFeature);
	BOOL OnSysKeyDown(WPARAM wParam, LPARAM lParam, POINT ptMouse, POINT ptTargetPos, INT nMosueTargetID, FEATURE stTargetFeature);
//---------------------------------------------------------------------------------------------------------------//
};








#endif // _CACTOR_H
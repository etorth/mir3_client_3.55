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
	LONG	nTag1;			// ������ ID.(SM_STRUCK�϶�).
	LONG	nTag2;
}MESSAGEBODYWL, *LPMESSAGEBODYWL;

typedef struct tagMESSAGEBODYW
{
	WORD	wParam1;
	WORD	wParam2;
	WORD	wTag1;			// ������ ID.(SM_STRUCK�϶�).
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
	BYTE				m_bMoveSpeed;					// �̵��ӵ�.

	INT					m_nDelay;						// ���� ���ۿ� ���� �����ð�.

	BYTE				m_bHPPercent;
	WORD				m_wMAXHP;
	WORD				m_wHP;
	WORD				m_wMP;
	INT					m_nOpenHealth;

	BYTE				m_bLightSize;					// Actor�ֺ��� ����ũ��.
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
	BYTE	m_bMoveSpeed;	// �̵��ӵ�.
	DWORD	m_dwFstFrame;	// ���� ������ ���� ������.
	DWORD	m_dwEndEffectFrame;	// ĳ���� Effect������ ������.
	AFTERIMAGE	m_xAfterImage[10];	
	FEATURE	m_stHitter;	
	CWHWilImageData*	m_pxActorImage;	// �̹����� ���� �����͵�.
	INT	m_nShiftTileX;	// ���� �ڽ��� Ÿ�Ͽ��� X�ุŭ �̵��� Ÿ���� �Ÿ�.
	BYTE	m_bFlagBlue;	
			
	INT	m_nPosY;	// Ÿ�� Y��ǥ.
	DWORD	m_dwCurrFrame;	// ���� ������.
			
	BYTE	m_bEftFeature;	

	// 2006.07.03 - �ű��Ǻ� ����Ʈ
	INT		m_nEft;
	CWHWilImageData*	m_pxDragonImage;				// �방�� �̹��� ������ - 2006.07.03 -�ű��Ǻ� ����Ʈ
	RECT				m_rcDragon;						// �방�� Actor ����




	CHAR	m_szFoo2[2];	// ĳ���ͳ� ������ �̸�.
			
	BYTE	m_bCurrDir;	// ���� ����.
			
			
	MONTYPE	m_stMonType;	
	WORD	m_wMAXHP;	
			
			
	BOOL	m_bABlendRev;	
	BYTE	m_bEffectImgIdx;	// ���� Actor�� ���� �̹�������ü�� ��ȣ.
	INT	m_nPlayIdx1;	
	DWORD	m_nTimerAfterImg;	
	BYTE	m_bFlagGreen;	
	INT	m_nPosX;	// Ÿ�� X��ǥ.
	BYTE	m_bMoveDir;	// ���� ����.
	DWORD	m_dwSturnTimer;	
	INT	m_nCharState;	
	CHAR	m_szFoo1[1];	// ĳ���ͳ� ������ �̸�.
			
	INT	m_nABlendDelay;	
	BYTE	m_bMoveNextFrmCnt;	
	BOOL	m_bNeedLoadFameImg;	
			
	CHAR	m_szGuildName[64];	
	CWHQueue	m_xPacketQueue;	// Actor�� ó���ؾߵ� �޽����� �����ϰ� �ִ� ť.
	INT	m_nABlendCurrDelay;	
	BOOL	m_bUseSwordEffect;	// �˹�ȿ�� ���.
	BOOL	m_bUseEffect;	// ����Ʈ�������� ���.
			
			
	CHAR	m_szChatMsg[MAX_PATH];	// ä�ø޽���.
	INT	m_nShiftPixelX;	// ���� �ڽ��� Ÿ�Ͽ��� X�ุŭ �̵��� �ȼ��� �Ÿ�.
			
	INT	m_nCurrDelay;	// ���� �����ð�.
	BOOL	m_bIsMoved;	
			
			
	DWORD	m_wCurrChatDelay;	
	INT	m_nHealthSeed;	
	BOOL	m_bLatestFaceImg;	
	BYTE	m_bLightRadius[2];	// ���� �ʺ�.
	BYTE	m_bLightColor [2][3];	// ���� ��.
			
	POINT	m_ptShowBlood[8];	
			
	BOOL	m_bIsDead;	
	CHAR	m_szChatMsgArg[8][MAX_PATH];	// ä�ø޽����� 5���� ��Ʈ������ �����Ѱ�.
	D3DVERTEX	m_avBoard[4];	
			
	BOOL	m_bFstSoundPlayed;	
	WORD	m_wHP;	
	FEATURE	m_stFeature;	// ĳ������ ������ �������´�.
	INT 	m_nShowBlood[8];	
	BYTE	m_bDelStruckCnt;	// SM_STRUCK�� ������ �´� ������ �����ϱ� ���� ���� ��Ŷ�� ��.
			
			
	BOOL	m_bReverse;	
	WORD	m_wStateClr;	
	INT	m_nScrnPosX;	// �߽����� ������� ���� ȭ����� X��ǥ.
	RECT	m_rcTargetRgn;	// ���� Actor�� Ÿ�ٿ���.
	DWORD	m_dwFstEffectFrame;	// ĳ���� Effectó�� ������.
	BYTE	m_bEffectBlend;	// �귻������.
	DWORD	m_dwEndFrame;	// ���� ������ ������������.
	CHAR	m_szShowName[3][64];	
	BYTE	m_bEffectOpa;	// ����.
	WORD	m_wMonColor;	// �߰�����. ���� ������.
	BYTE	m_bGuildFlag;	
			
	BYTE	m_bBackStepFrame;	
	BYTE	m_bFlagRed;	
	INT	m_nScrnPosY;	// �߽����� ������� ���� ȭ����� Y��ǥ.
	INT	m_nShiftPixelY;	// ���� �ڽ��� Ÿ�Ͽ��� Y�ุŭ �̵��� �ȼ��� �Ÿ�.
	RECT	m_rcActor;	// ���� ��ũ������Actor�� �簢 ����.
			
	WORD	m_wMP;	
	WORD	m_wEffectLooks;	
	INT	m_nIdentity;	// ID Index From Server.
	BYTE	m_bHPPercent;	
	WORD	m_dwShowBloodTimer[8];	
	INT	m_nOpenHealth;	
	BYTE	m_bCurrMtn;	// ���� ����.
			
	BYTE	m_bEffectFrameCnt;	
	INT	m_nFaceImageDate;	
	BYTE	m_bLightSize;	// Actor�ֺ��� ����ũ��.
	INT	m_nShiftTileY;	// ���� �ڽ��� Ÿ�Ͽ��� Y�ุŭ �̵��� Ÿ���� �Ÿ�.
			
	CHAR	m_szName[64];	// ĳ���ͳ� ������ �̸�.
	BYTE	m_bAppearState;	
	DWORD	m_dwNameClr;	
	BOOL	m_bWarMode;	
	BOOL	m_bIsSturn;	
	CHAR	m_szRankName[64];	
	CHAR	m_szFoo3[3];	// ĳ���ͳ� ������ �̸�.
	BYTE	m_bActorImgIdx;	// ���� Actor�� ���� �̹�������ü�� ��ȣ.
	DWORD	m_dwCurrMoveSkip;	
	BYTE	m_bEffectFrame;	
			
			
	BYTE	m_bJob;	
	DWORD	m_dwWarModeTime;	
	INT	m_nShowBloodIdx;	
	CHAR	m_szMateName[64];	
			
			
	INT	m_nDelay;	// ���� ���ۿ� ���� �����ð�.
	INT	m_nStrurnFrame;	
			
	BOOL	m_bMsgHurryCheck;	// �޽����� 2���̻� �׿��������� �������� 1�����Ӿ��� �ǳʶڴ�.
	BYTE	m_bBackStepFrameCnt;	
	BYTE	m_bEffectColor[3];	// ��.
			
	DWORD	m_dwCurrEffectFrame;	// ĳ���� Effect���� ������.
			
	INT	m_nPlayIdx2;	
			
	BOOL	m_bLoadFaceImg;	
public:
//---------------------------------------------------------------------------------------------------------------//
// ������ �� �Ҹ���.
	CActor();
	virtual ~CActor();

	virtual VOID InitActor();
	virtual VOID DestroyActor();
//---------------------------------------------------------------------------------------------------------------//

//---------------------------------------------------------------------------------------------------------------//
// ����.
	virtual BOOL Create(CImageHandler* pxImgHandler, FEATURE* pstFeature, BYTE bMtn, BYTE bDir, INT nPosX, INT nPosY);
//---------------------------------------------------------------------------------------------------------------//

	BOOL LoadEffect(CImageHandler* pxImgHandler, WORD wEffectNum, BYTE bDir = 0, int nElement = -1);
	VOID DrawWithEffected(INT nx, INT nY, INT nXSize, INT nYSize, WORD* pwSrc, WORD wChooseColor1 = 0XFFFF, WORD wChooseColor2 = 0XFFFF, BOOL bFocused = FALSE, BYTE bOpa = 50, WORD wState = _STATE_NOTUSED);
//---------------------------------------------------------------------------------------------------------------//
// ������ ��������.
	BOOL	CheckFeatureValidate(FEATURE stFeature);
	BOOL	ChangeFeature(FEATURE stFeature);
	virtual BOOL SetMotionFrame(BYTE bMtn, BYTE bDir, DWORD dwDelay = 0);
//---------------------------------------------------------------------------------------------------------------//

//---------------------------------------------------------------------------------------------------------------//
// ĳ���� �̵�.
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
// ���� ����.
	virtual BOOL UpdatePacketState();
	virtual VOID UpdateMotionState(INT nLoopTime, BOOL bIsMoveTime);
	virtual BOOL UpdateMove(BOOL bIsMoveTime);

// ������ ��Ŷ��������.
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
	VOID MakeMagicStream(WORD wMagicID, INT nTarID, INT nTarX, INT nTarY);	// ������, ������, ������ΰ�ȿ������ �����.
	VOID MakeMagicStreamEx(WORD wMagicID, INT nStartX, INT nStartY, INT nTarX, INT nTarY);	// ������
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

	INT			nEft;	// 2006.07.03 - �ű��Ǻ� ����Ʈ

	//INT			nIcon;	// ������
}FEATUREEX, *LPFEATUREEX;
#pragma pack(8)

class CHero : public CActor
{
private:
public:
									
	DWORD	m_dwCurrWeaponFrame;							
									
	INT	m_nAfterPosY;							
	BOOL	m_bUseHErgum;							
	BYTE	m_bHorseImgIdx;	//	����	Actor	����	����	�̹�������ü��	��ȣ.
									
									
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
	BYTE	m_bHairImgIdx;	//	����	Actor	�Ӹ���	����	�̹�������ü��	��ȣ.
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
									
	BYTE	m_bWeaponImgIdx;	//	����	Actor	���Ⱑ	����	�̹�������ü��	��ȣ.
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

	VOID	DrawTheAomorEffect(INT nFrame);		// 2006.07.03 - �ű��Ǻ� ����Ʈ

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
typedef struct tagACTORABILITY //������
{
	BYTE			bLevel;

	WORD			wAC;
	WORD			wMAC;
	DWORD			dwDC;
	DWORD			dwMC;			//�������뺯�� //magic power class   -> makeword(min/max)
	DWORD			dwSC;			//�������뺯�� //sprite energy class    -> makeword(min/max)
	
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
	WORD wAntiMagic;		// ����ȸ��.
	BYTE bHitPoint;			// ��Ȯ.
	BYTE bSpeedPoint;		// ��ø.
	BYTE bAntiPoison;		// �ߵ�ȸ��.
	BYTE bPoisonRecover;	// �ߵ�ȸ��.
	BYTE bHealthRecover;	// ü��ȸ��.
	BYTE bSpellRecover;		// ����ȸ��.
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
//  ĳ���� ������ ����.
	DWORD			m_dwMotionLockTime;
	BOOL			m_bInputLock;							// ĳ���Ͱ� ���۵Ǹ� ��Էµ� ���� �ʴ´�.
	BOOL			m_bMotionLock;							// ĳ������ ������ ���õǸ� �������� ���۽����� ���������� ����۵� ���� �ʴ´�.
//---------------------------------------------------------------------------------------------------------------//

	CMapHandler*	m_pxMap;
	BOOL			m_bCanRun;
	DWORD			m_dwCanRunTick;
	BYTE		    m_bJob;
	INT				m_nGlod;
	ACCEPTMTN		m_stAcceptMtn;
	ACTORABILITY    m_stAbility;
	ACTORSUBABILITY m_stSubAbility;

	INT				m_nOldPosX;								// ���� �ൿ�� �ֱ����� Ÿ��X��ǥ.
	INT				m_nOldPosY;
	BYTE			m_bOldDir;								// ���� �ൿ�� �ֱ����� ����.

	BYTE			m_bGuildFlag;
    BYTE			m_bFlagColorR;
    BYTE			m_bFlagColorG;
    BYTE			m_bFlagColorB;

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	BOOL			m_bAutoDig;
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//---------------------------------------------------------------------------------------------------------------//
//  ĳ���� Delay���� ����.
	DWORD			m_dwLastMoveTime;						// �ȱ�, �ٱ� ƽ ������
	DWORD			m_dwLastHitTime;						// Į���� �������� ƽ ������.
	DWORD			m_dwLastSpellTime;						// ������ �������� ƽ ������.
	DWORD			m_dwLastMagicTime;						// ��ȭ�� �������� ƽ������.
	DWORD			m_dwLastStruckTime;						// �¾������� ƽ ������.
	DWORD			m_dwLastPKStruckTime;
	DWORD			m_dwLastRushTime;						// ���º� �������� ƽ������.
	DWORD			m_dwLastKickTime;						// ���º� �������� ƽ������.
	DWORD			m_dwLastFireHitTime;					// ��ȭ�� �������� ƽ������.

	DWORD			m_dwLastJSHitTime;						// �������� �������� ƽ������.
	DWORD			m_dwLastRSHitTime;						// ��������������� ƽ������.


	DWORD			m_dwMagicPKDelayTime;					// �������� ����� ������������ �г�ƼDelay.(�ȱ�� �ٱ⿡ ����ȴ�.)
	DWORD			m_dwMagicDelayTime;						// ���������� ���� ���������� ���������� Delay.


	DWORD			m_dwLastWalkTime;
	DWORD			m_dwLastMagicUseTime;
	DWORD			m_dwLastHitUseTime;

	INT				m_nTempWeaponExp;

	INT				m_nPoint;								// ����Ʈ����, ��������


//---------------------------------------------------------------------------------------------------------------//

//---------------------------------------------------------------------------------------------------------------//
//  ���� �׽�Ʈ����.
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
//  ĳ���� Delay���� �Լ�.
	BOOL CanNextHit();									// ���� Į���Ҽ� �ֳ��� ����. ������ ���빫�Կ� ���� �޶�����.
	BOOL CanWalk();										// Delay�� ������� ĳ���Ͱ� �����ϼ� �ִ����� ����.
	BOOL CanRun();										// Delay�� ������� ĳ���Ͱ� �����ϼ� �ִ����� ����.
//---------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------//
//  ���� �Է��Լ�.
	BOOL OnLButtonDown(POINT ptMouse, INT nTargetID = -1, BOOL bIsDead = FALSE, POINT* lpptTargetPos = NULL);
	BOOL OnRButtonDown(POINT ptMouse);
	BOOL OnKeyDown(WPARAM wParam, LPARAM lParam, POINT ptMouse, POINT ptTargetPos, INT nMosueTargetID, FEATURE stTargetFeature);
	BOOL OnSysKeyDown(WPARAM wParam, LPARAM lParam, POINT ptMouse, POINT ptTargetPos, INT nMosueTargetID, FEATURE stTargetFeature);
//---------------------------------------------------------------------------------------------------------------//
};








#endif // _CACTOR_H
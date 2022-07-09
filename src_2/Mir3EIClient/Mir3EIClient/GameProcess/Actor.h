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
	LONG	nTag1;			// 锭赴仇 ID.(SM_STRUCK老锭).
	LONG	nTag2;
}MESSAGEBODYWL, *LPMESSAGEBODYWL;
typedef struct tagMESSAGEBODYW
{
	WORD	wParam1;
	WORD	wParam2;
	WORD	wTag1;			// 锭赴仇 ID.(SM_STRUCK老锭).
	WORD	wTag2;
}MESSAGEBODYW, *LPMESSAGEBODYW;

typedef struct tagCHARDESC
{
	LONG	nFeature;
	LONG	nStatus;
}CHARDESC, *LPCHARDESC;

typedef struct tagFEATURE
{
	BYTE	bGender; 
	BYTE	bWeapon;
	BYTE	bDress; 
	BYTE	bHair;
}FEATURE, *LPFEATURE;
#pragma pack(8)



class CActor
{
private:
public:
	DWORD				m_dwIdentity;					// ID Index From Server.
	CHAR				m_szName[64];					// 某腐磐唱 阁胶磐狼 捞抚.
	CHAR				m_szGuildName[64];

	FEATURE				m_stFeature;					// 某腐磐狼 寇屈阑 搬沥窿绰促.
	BYTE				m_bActorImgIdx;					// 泅犁 Actor啊 啊龙 捞固瘤备炼眉狼 锅龋.
	BYTE				m_bEffectImgIdx;				// 泅犁 Actor啊 啊龙 捞固瘤备炼眉狼 锅龋.
	CWHWilImageData*	m_pxActorImage;					// 捞固瘤甫 掘绢棵 器牢磐甸.
	RECT				m_rcActor;						// 泅犁 胶农赴惑狼Actor狼 荤阿 康开.
	RECT				m_rcTargetRgn;					// 泅犁 Actor狼 鸥百康开.

	DWORD				m_dwFstFrame;					// 泅犁 悼累狼 矫累 橇饭烙.
	DWORD				m_dwEndFrame;					// 泅犁 悼累狼 付瘤阜橇饭烙.
	WORD				m_wDelay;						// 泅犁 悼累俊 措茄 瘤楷矫埃.

	BYTE				m_bCurrMtn;						// 泅犁 悼累.
	BYTE				m_bCurrDir;						// 泅犁 规氢.
	BYTE				m_bMoveDir;						// 泅犁 规氢.
	DWORD				m_dwCurrFrame;					// 泅犁 橇饭烙.
	WORD				m_wCurrDelay;					// 泅犁 瘤楷矫埃.

	WORD				m_wOldPosX;						// 泅犁 青悼捞 乐扁傈狼 鸥老X谅钎.
	WORD				m_wOldPosY;
	BYTE				m_bOldDir;						// 泅犁 青悼捞 乐扁傈狼 规氢.
	WORD				m_wPosX;						// 鸥老 X谅钎.
	WORD				m_wPosY;						// 鸥老 Y谅钎.
	SHORT				m_shShiftPixelX;				// 泅犁 磊脚狼 鸥老俊辑 X绵父怒 捞悼茄 侨伎狼 芭府.
	SHORT				m_shShiftPixelY;				// 泅犁 磊脚狼 鸥老俊辑 Y绵父怒 捞悼茄 侨伎狼 芭府.
	SHORT				m_shShiftTileX;					// 泅犁 磊脚狼 鸥老俊辑 X绵父怒 捞悼茄 鸥老狼 芭府.
	SHORT				m_shShiftTileY;					// 泅犁 磊脚狼 鸥老俊辑 Y绵父怒 捞悼茄 鸥老狼 芭府.
	SHORT				m_shScrnPosX;					// 吝缴痢阑 绊妨窍瘤 臼篮 拳搁惑狼 X谅钎.
	SHORT				m_shScrnPosY;					// 吝缴痢阑 绊妨窍瘤 臼篮 拳搁惑狼 Y谅钎.
	BYTE				m_bMoveSpeed;					// 捞悼加档.

	CWHQueue			m_xPacketQueue;					// Actor啊 贸府秦具瞪 皋矫瘤甫 历厘窍绊 乐绰 钮.
	BOOL				m_bMsgHurryCheck;				// 皋矫瘤啊 2俺捞惑 阶咯乐阑锭绰 橇饭烙阑 1橇饭烙究阑 扒呈囤促.

	BYTE				m_bBackStepFrame;
	BYTE				m_bBackStepFrameCnt;

	DWORD				m_dwCurrEffectFrame;			// 某腐磐 Effect泅犁 橇饭烙.
	DWORD				m_dwFstEffectFrame;				// 某腐磐 Effect贸澜 橇饭烙.
	DWORD				m_dwEndEffectFrame;				// 某腐磐 Effect付瘤阜 橇饭烙.
	BYTE				m_bEffectFrame;
	BYTE				m_bEffectFrameCnt;
	BYTE				m_bLightRadius[2];				// 堡盔 呈厚.
	BYTE				m_bLightColor [2][3];			// 堡盔 祸.

	BOOL				m_bUseEffect;					// 捞棋飘橇饭烙阑 荤侩.
	BOOL				m_bUseSwordEffect;				// 八过瓤苞 荤侩.

	BOOL				m_bWarMode;
	DWORD				m_dwWarModeTime;

	BYTE				m_bHPPercent;
	WORD				m_wMAXHP;
	WORD				m_wHP;
	WORD				m_wMP;
	BOOL				m_bOpenHealth;

	BYTE				m_bLightSize;					// Actor林函狼 堡盔农扁.

//	D3DVERTEX			m_avBoard[4];

	WORD				m_wABlendDelay;
	WORD				m_wABlendCurrDelay;
	BOOL				m_bABlendRev;

	BOOL				m_bReverse;

	INT					m_nState;
	WORD				m_wStateClr;

	DWORD				m_dwNameClr;

	BOOL				m_bIsDead;

	FEATURE				m_stHitter;

	BYTE				m_bAppearState;

	BYTE				m_bMoveNextFrmCnt;
	BOOL				m_bIsMoved;

	BOOL				m_bFstSoundPlayed;

	INT					m_nDividedChatLine;
	DWORD				m_wCurrChatDelay;
	CHAR				m_szChatMsg[MAX_PATH];			// 盲泼皋矫瘤.
	CHAR				m_szChatMsgArg[5][MAX_PATH];	// 盲泼皋矫瘤甫 5俺狼 胶飘傅栏肺 备盒茄巴.

public:
//---------------------------------------------------------------------------------------------------------------//
// 积己磊 棺 家戈磊.
	CActor();
	~CActor();

	virtual VOID InitActor();
	virtual VOID DestroyActor();
//---------------------------------------------------------------------------------------------------------------//

//---------------------------------------------------------------------------------------------------------------//
// 积己.
	virtual BOOL Create(CImageHandler* pxImgHandler, FEATURE* pstFeature, BYTE bMtn, WORD bDir, WORD wPosX, WORD wPosY);
//---------------------------------------------------------------------------------------------------------------//

	BOOL LoadEffect(CImageHandler* pxImgHandler, WORD wEffectNum, BYTE bDir = 0);
	VOID DrawWithEffected(INT nx, INT nY, INT nXSize, INT nYSize, WORD* pwSrc, WORD wChooseColor1 = 0XFFFF, WORD wChooseColor2 = 0XFFFF, BOOL bFocused = FALSE, BYTE bOpa = 50, WORD wState = _STATE_NOTUSED);
//---------------------------------------------------------------------------------------------------------------//
// 橇饭烙 汲沥包访.
	BOOL	CheckFeatureValidate(FEATURE stFeature);
	BOOL	ChangeFeature(FEATURE stFeature);
	virtual BOOL SetMotionFrame(BYTE bMtn, BYTE bDir);
//---------------------------------------------------------------------------------------------------------------//

//---------------------------------------------------------------------------------------------------------------//
// 某腐磐 捞悼.
	VOID SetMoving();
	VOID SetBackStepMoving();
	VOID SetMoved();
	WORD GetCharState();
//---------------------------------------------------------------------------------------------------------------//

	VOID ChatMsgAdd();
	VOID ShowMessage(INT nLoopTime);
	VOID StruckMsgReassign();
	
	virtual VOID PlayActSound();

//---------------------------------------------------------------------------------------------------------------//
// 悼累 柳青.
	virtual BOOL UpdatePacketState();
	virtual VOID UpdateMotionState(INT nLoopTime, BOOL bIsMoveTime);
	virtual BOOL UpdateMove(BOOL bIsMoveTime);

// 蜡屈喊 菩哦惑怕利侩.
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
	virtual VOID OnBackStep(LPPACKETMSG lpPacketMsg);
	virtual VOID OnStruck(LPPACKETMSG lpPacketMsg);
	virtual VOID OnHit(LPPACKETMSG lpPacketMsg);
	virtual VOID OnFlyAxe(LPPACKETMSG lpPacketMsg);
	virtual VOID OnLighting(LPPACKETMSG lpPacketMsg);
//---------------------------------------------------------------------------------------------------------------//

//---------------------------------------------------------------------------------------------------------------//
// Rendering.
	virtual BOOL DrawActor(CMapHandler* pxMap, BOOL bFocused = FALSE, BOOL bShadowAblended = FALSE, 
		                   BOOL bUseScrnPos = TRUE, BOOL bDrawShadow = TRUE);
	virtual VOID DrawHPBar();
	virtual VOID DrawName();

	BOOL DrawEffect();
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
//typedef struct tagFEATUREEX
//{
//	BYTE		bHorse;
//	BYTE		wHairColor;
//	BYTE		wDressColor;
//}FEATUREEX, *LPFEATUREEX;
//ydq 7-24 试试改的效果
typedef struct tagFEATUREEX
{
	BYTE		bHorse;
	WORD		wDressColor;
	WORD		wHairColor;
}FEATUREEX, *LPFEATUREEX;
#pragma pack(8)

class CHero : public CActor
{
private:
public:
	FEATUREEX			m_stFeatureEx;

	BYTE				m_bWeaponImgIdx;				// 泅犁 Actor 公扁啊 啊龙 捞固瘤备炼眉狼 锅龋.
	BYTE				m_bHairImgIdx;					// 泅犁 Actor 赣府啊 啊龙 捞固瘤备炼眉狼 锅龋.
	BYTE				m_bHorseImgIdx;					// 泅犁 Actor 富捞   啊龙 捞固瘤备炼眉狼 锅龋.

	BYTE				m_bYedoCnt;
	BYTE				m_bFireHitCnt;
	BOOL				m_bUseBanwol;
	BOOL				m_bUseErgum;

	RECT				m_rcHair;
	RECT				m_rcWeapon;
	RECT				m_rcHorse;

	CWHWilImageData*	m_pxHairImage;		
	CWHWilImageData*	m_pxWeaponImage;
	CWHWilImageData*	m_pxHorseImage;

	DWORD				m_dwCurrHairFrame;
	DWORD				m_dwCurrWeaponFrame;
	DWORD				m_dwCurrHorseFrame;

	BYTE				m_bShieldCurrFrm;
	WORD				m_wShieldCurrDelay;

	SHORT				m_shHitSpeed;

	BOOL				m_bIsMon;

	SHORT				m_shCurrMagicID;

protected:
public:
	CHero();
	~CHero();

	virtual VOID InitActor();
	virtual VOID DestroyActor();

	VOID ShowShield();
	VOID PlayMoveSound();

	virtual VOID PlayActSound();
	virtual BOOL ChangeFeature(FEATURE stFeature, FEATUREEX stFeatureEx);
	virtual BOOL Create(CImageHandler* pxImgHandler, BYTE bMtn, BYTE bDir, WORD wPosX, WORD wPosY, FEATURE* pstFeature, FEATUREEX* pstFeatureEx);
	virtual BOOL UpdatePacketState();
	virtual VOID UpdateMotionState(INT nLoopTime, BOOL bIsMoveTime);
	virtual BOOL UpdateMove(BOOL bIsMoveTime);
	virtual VOID OnRun(LPPACKETMSG lpPacketMsg);
	virtual VOID OnRush(LPPACKETMSG lpPacketMsg);
	virtual VOID OnMagicFire(LPPACKETMSG lpPacketMsg);
	virtual VOID OnSpell(LPPACKETMSG lpPacketMsg);
	virtual VOID OnCharDescPacket(LPPACKETMSG lpPacketMsg);
	virtual VOID OnFeatureChanged(LPPACKETMSG lpPacketMsg);
	virtual VOID OnCharStatusChanged(LPPACKETMSG lpPacketMsg);
	virtual VOID OnBackStep(LPPACKETMSG lpPacketMsg);
	virtual VOID OnDeath(LPPACKETMSG lpPacketMsg);
	virtual VOID OnWalk(LPPACKETMSG lpPacketMsg);
	virtual VOID OnTurn(LPPACKETMSG lpPacketMsg);
	virtual VOID OnStruck(LPPACKETMSG lpPacketMsg);
	virtual VOID OnHit(LPPACKETMSG lpPacketMsg);
	virtual VOID OnButch(LPPACKETMSG lpPacketMsg);
	virtual BOOL DrawActor(CMapHandler* pxMap, BOOL bFocused = FALSE, BOOL bShadowAblended = FALSE, 
		                   BOOL bUseScrnPos = TRUE, BOOL bDrawShadow = TRUE);
};


/*
"ac" 防御力下限
"ac2" 防御力上限
"mac" 魔防下限
"mac2" 魔防上限
"dc" 物理攻击力下限 
"dc2" 物理攻击力上限 超过了255带在身上攻击是会减成0
"mc" 魔法攻击力下限
"mc2" 魔法攻击力上限
"sc" 道术下限
"sc2" 道术上限
"needlevel" 需要等级
"price" 价格


(9)物品是首饰时：
"ac2" 表示准确
"mac2" 表示敏捷
"ac" 表示防御下限
"ac2" 表示防御上限
"mac" 表示魔御下限
"mac2" 表示魔御上限
*/







/******************************************************************************************************************

	CMyHero Class

*******************************************************************************************************************/
#pragma pack(1)
typedef struct tagACTORABILITY
{
	BYTE	bLevel;
    WORD	wAC;		//防御力
    WORD	wMAC;		//魔防
	WORD	wDC;		//物理攻击力
    WORD	wMC;		//魔法攻击力
    WORD	wSC;		//道术
	WORD	wHP;
	WORD	wMP;
    WORD	wMaxHP;
    WORD	wMaxMP;
	DWORD	dwExp;
	DWORD	dwMaxExp;
	WORD	wWeight;
	WORD	wMaxWeight;
	BYTE	bWearWeight;
	BYTE	bMaxWearWeight;
    BYTE	bHandWeight;
    BYTE	bMaxHandWeight;

}ACTORABILITY, *LPACTORABILITY;

typedef struct tagACTORSUBABILITY
{
	WORD wAntiMagic;		// 付过雀乔.
	BYTE bHitPoint;			// 沥犬.
	BYTE bSpeedPoint;		// 刮酶.
	BYTE bAntiPoison;		// 吝刀雀乔.
	BYTE bPoisonRecover;	// 吝刀雀汗.
	BYTE bHealthRecover;	// 眉仿雀汗.
	BYTE bSpellRecover;		// 付仿雀汗.
}ACTORSUBABILITY, *LPACTORSUBABILITY;
#pragma pack(8)

class CMyHero : public CHero
{
public:

	//  锁定
	DWORD			m_dwMotionLockTime;
	BOOL			m_bInputLock;				// 输入锁定
	BOOL			m_bMotionLock;				// 锁定运动,SetMotionState()加锁, UpdateMotionState()解锁,也就是在这一段时间内不响应鼠标消息

	CMapHandler*	m_pxMap;
	BOOL			m_bCanRun;
	BYTE			m_bAttackMode;
	ACTORABILITY    m_stAbility;
	ACTORSUBABILITY m_stSubAbility;
	BYTE		    m_bJob;
	UINT			m_nGlod;

	CWHQueue		m_xPriorPacketQueue;					// Actor啊 贸府秦具瞪 皋矫瘤甫 历厘窍绊 乐绰 钮.

	//  动作延迟.
	DWORD			m_dwLastHitTime;						// 最近攻击时间
	DWORD			m_dwLastSpellTime;						// 最近使用符咒的时间
	DWORD			m_dwLastMagicTime;						// 最近使用魔法的时间
	DWORD			m_dwLastStruckTime;						// 最近被攻击时间
	DWORD			m_dwLastPKStruckTime;					// PK时间,主要不让杀人就跑或下线
	DWORD			m_dwLastRushTime;						// 冲撞时间(最近使用魔法冲撞时间)
	DWORD			m_dwLastFireHitTime;					// 使用魔法火球的时间

	WORD			m_wMagicPKDelayTime;					// 魔法PK时间
	WORD			m_wMagicDelayTime;						// 魔法延迟

	BOOL			m_bActive;//是否响应用户消息

public:
	CMyHero();
	~CMyHero();

	virtual VOID InitActor();
	virtual VOID DestroyActor();

	VOID  SetMapHandler(CMapHandler* pxMap);
	
	//动作函数,发送MyHero的行走,魔法命令 AutoTargeting(), OnLButtonDown()...调用
	virtual VOID  SetMotionState(BYTE bMtn, BYTE bDir, INT nMouseTargetID = NULL, BOOL bIsDead = FALSE, LPPOINT lpptPos = NULL, SHORT shSkill = -1);
	//使用魔法,调用SetMotionState()完成魔法动作
	VOID  SetMagic(LPCLIENTMAGICRCD	pstMagic, BYTE bKeyNum, BYTE bDir, INT nTargetID, FEATURE stTargetFeature, POINT ptTargetPos);
	//退回到前一个状态, 接收到"+FAIL"行走失败命令后调用这个函数
	virtual BOOL  SetOldPosition();

	//检查MyHero是否在屏幕正中,也就是检查是否需要移动地图
	BOOL  CheckMyPostion();
	//移动地图,相当于移动MyHero  ScrollMap()移动地图的偏移量来移动地图,范围在一个Tile内.
	VOID  AdjustMyPostion();
	//计算方向
	BYTE  CalcDirection(INT nTargetTileX, INT nTargetTileY);
	//将鼠标坐标换成地图坐标
	POINT GetPosMouseToTile(INT nXPos, INT nYPos);

	virtual BOOL Create(CImageHandler* pxImgHandler, BYTE bMtn, BYTE bDir, WORD wPosX, WORD wPosY, FEATURE* pstFeature, FEATUREEX* pstFeatureEx);
	virtual VOID OnHealthSpellChanged(LPPACKETMSG lpPacketMsg);

	//处理状态改变
	virtual BOOL UpdatePacketState();
	//更新运动状态,绘制动作和特效,CheckMappedData()调用UpdateMotionState()绘制除MyHero的动作,
	//RenderScene()调用UpdateMotionState()绘制MyHero的动作, UpdateMotionState()调用UpdateMove()实现移动动作,和连续移动
	virtual VOID UpdateMotionState(INT nLoopTime, BOOL bIsMoveTime);
	//绘制移动, 并检查鼠标状态,实现连续移动
	virtual BOOL UpdateMove(BOOL bIsMoveTime);

	virtual BOOL DrawActor(BOOL bFocused = FALSE, BOOL bShadowAblended = FALSE, 
		                   BOOL bUseScrnPos = FALSE, BOOL bDrawShadow = TRUE);

	//改变外观
	__inline virtual BOOL ChangeFeature(FEATURE stFeature, FEATUREEX stFeatureEx)
	{
		if ( m_bIsMon )		
		{
			if ( CActor::ChangeFeature(stFeature) )					return TRUE;
		}
		else	
		{
			if ( CHero::ChangeFeature(stFeature, stFeatureEx) )		return TRUE;
		}

		return FALSE;
	}


	
	BOOL CanNextHit();						// 判断延迟时间来判断是否可以攻击,和m_stAbility.bLevel也挂钩
	BOOL CanWalk();							//  if ( timeGetTime() - m_dwLastSpellTime < m_wMagicPKDelayTime )	return TRUE;
	BOOL CanRun();							// (timeGetTime() - m_dwLastPKStruckTime < 3000) || (timeGetTime() - m_dwLastSpellTime < m_wMagicPKDelayTime )

	
	//  鼠标消息.
	virtual BOOL OnLButtonDown(POINT ptMouse, INT nTargetID = -1, BOOL bIsDead = FALSE, POINT* lpptTargetPos = NULL);
	virtual BOOL OnRButtonDown(POINT ptMouse);
	virtual BOOL OnKeyDown(WPARAM wParam, LPARAM lParam, POINT ptMouse, POINT ptTargetPos, INT nMosueTargetID, FEATURE stTargetFeature);

	VOID DrawName();

	//处理多人事件添加的函数和变量
	VOID	SetSocket(CClientSocket* pSocket) { m_pSocketClient = pSocket;}
	VOID	SetProc( CWHDefProcess* pProc ){ m_pGameProc = pProc; }//设置关联的处理类
protected:
	CClientSocket*	m_pSocketClient;//socket连接
	CWHDefProcess*	m_pGameProc;//关联的处理类
};








#endif // _CACTOR_H
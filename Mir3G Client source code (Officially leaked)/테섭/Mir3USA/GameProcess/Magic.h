/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#ifndef _CMAGIC_H
#define _CMAGIC_H



/******************************************************************************************************************

	CMagic Class
	

*******************************************************************************************************************/
class CMagic
{
/* Constructor & Destructor */
public:
	CMagic();
	virtual ~CMagic();

/* Attributes */
public:
	BYTE				m_bActiveState;							// 마법 활성화여부.(마법소멸시에 사용된다.)
	BOOL				m_bRepeat;								// 애니메이션의 반복여부.
	BOOL				m_bFixed;								// 마법의 이동여부.
	WORD				m_wMagicNum;							// 마법번호.

	CActor*				m_pxOwner;								// 마법발사주체.
	CActor*				m_pxTarget;								// 마법발사객체.

	D3DVERTEX			m_avMagic[4];
	CWHWilImageData*	m_pxMagicImg;

	// 좌표정보.
	INT					m_nScrnX, m_nScrnY;								// 마법스크린좌표.
	FLOAT				m_fFloatScrnX, m_fFloatScrnY;					// 마법스크린좌표.
	INT					m_nTileX, m_nTileY;								// 마법타일좌표.

	INT					m_nFireScrnX, m_nFireScrnY;						// 마법생성스크린좌표.	
	INT					m_nFireTileX, m_nFireTileY;						// 마법생성타일좌표.

	INT					m_nTargetScrnX, m_nTargetScrnY;					// 목표점의 스크린좌표.
	INT					m_nTargetTileX, m_nTargetTileY;					// 목표점의 타일좌표.(변화될수있다.)

	LPDIRECTDRAWSURFACE7 m_testlpddsMagicTextr;
	BOOL				 m_tsetbool;

	// 렌더링정보.
	INT					m_nCurrDelay;									// 지연시간저장값.
	INT					m_nCurrLightDelay;
	INT					m_nFrmDelay;									// 프레임을 넘기기 위한 지연시간값.
	DWORD				m_dwMagicLife;									// 마법이 실행되고 있는 시간.(ms단위)

	BYTE				m_bLightRadius[2];								// 광원 너비.
	BYTE				m_bLightColor[2][3];							// 광원 색.
	BYTE				m_bMagicColor[3];								// 색.

	DWORD				m_dwFstFrame;									// 현재 마법의 시작프레임.
	DWORD				m_dwEndFrame;									// 현재 마법의 마지막프레임.
	DWORD				m_dwCurrFrame;									// 프레임저장값.

	BYTE				m_bBlendType;									// 마법을 어떤형태로 그릴것인가를 결정.
	BYTE				m_bOpacity;										// 0 - 255단계. 0은 완전 투명(라이트형태), 255는 불투명.
	BYTE				m_bSwingCnt;									// 마법의 흔들림 조건을 준다.

	FLOAT				m_fGradient;
	INT					m_nShiftX;
	INT					m_nShiftY;
	INT					m_nDistanceX;
	INT					m_nDistanceY;
	INT					m_nPrevDistanceX;
	INT					m_nPrevDistanceY;

	BYTE				m_bDir16;
	BYTE				m_bCurrSwing;

	BOOL				m_bShowLight;

	WORD				m_wStartDelay;	

	WORD				m_wFileType;
	WORD				m_wFileIdx;

	INT					m_nDuplicateNum;

	BOOL				m_bStartSound;
	BOOL				m_bMiddleSound;

	CHAR				m_szServerNotice[MAX_PATH];

	DWORD				m_dwTemp;

/* Operation */
public:

	virtual BOOL CreateMagic(WORD wMagicNum, INT nFireTileX, INT nFireTileY, 
		                     INT nTargetTileX, INT nTargetTileY, CActor* pxOwner = NULL, INT nTarget = 0, WORD wStartDelay = 0, INT nAtom = 0, WORD wRed = 0, WORD wBlue = 0, WORD wGreen = 0);


	virtual VOID DestoryMagic();
	virtual BOOL UpdateMagic(INT nLoopTime);
	virtual BOOL DrawMagic();
	virtual BOOL DrawLight(CLightFog* xLightFog, INT nLoopTime);
};

class CConcenFireball : public CMagic
{
private:
	FLOAT   m_fRate;
	BOOL	m_bReverse;
public:
	virtual BOOL CreateMagic(WORD wMagicNum, INT nFireTileX, INT nFireTileY, 
		                     INT nTargetTileX, INT nTargetTileY, CActor* pxOwner = NULL, INT nTarget = 0, WORD wStartDelay = 0, BOOL bReverse = FALSE);
	virtual BOOL UpdateMagic(INT nLoopTime);
	virtual BOOL DrawMagic();
};


class CRefineAdd : public CMagic
{
private:
public:
	virtual BOOL CreateMagic(WORD wMagicNum, INT nFireTileX, INT nFireTileY, 
		                     INT nTargetTileX, INT nTargetTileY, CActor* pxOwner = NULL, INT nTarget = 0, WORD wStartDelay = 0);
	virtual BOOL UpdateMagic(INT nLoopTime);
	virtual BOOL DrawMagic();
};


// _SKILL_FIRE. _SKILL_ICE. _SKILL_SHOOTLIGHTENADD.
class CMagicStream : public CMagic
{
private:
	WORD	m_wMagicStart;
	POINT	m_ptTileGap;
public:
	BOOL CreateMagic(WORD wMagicNum, INT nFireTileX, INT nFireTileY, 
		             INT nTargetTileX, INT nTargetTileY, CActor* pxOwner, INT nTarget, WORD wStartMagicTime, POINT ptTileGap);
	BOOL UpdateMagic(INT nLoopTime);
	BOOL DrawMagic();
};


class CElecMagic : public CMagic
{
private:
	CElec m_xElec;

public:
	virtual BOOL CreateMagic(WORD wMagicNum, INT nFireTileX, INT nFireTileY, 
		                     INT nTargetTileX, INT nTargetTileY, CActor* pxOwner = NULL, INT nTarget = 0);
	virtual BOOL UpdateMagic(INT nLoopTime);
	virtual BOOL DrawMagic();
};



// _SKILL_HOLYSHIELD, _SKILL_EARTHFIRE, _SKILL_LIGHTWALL 전용.
class CRepeatMagic : public CMagic
{
private:
public:
	DWORD	m_dwMagiLifeTotal;
	INT		m_nEventID;					// 이벤트로관리된다.

	_inline CRepeatMagic()
	{
		m_nEventID		  = 0;
		m_dwMagiLifeTotal = 0;
	}

	BOOL CreateMagic(INT nEventID, WORD wMagicNum, INT nFireTileX, INT nFireTileY, 
	                 INT nTargetTileX, INT nTargetTileY, DWORD dwMagicLifeTotal, CActor* pxOwner = NULL, INT nTarget = 0);
	BOOL UpdateMagic(INT nLoopTime);
	BOOL DrawMagic();
};

//	_SKILL_HURRICANE 전용
class CHurricaneMagic : public CMagic
{
public:
	INT		mHurricaneMagic_nState;
	int		mHurricaneMagic_nOffsetX;
	int		mHurricaneMagic_nOffsetY;
	INT		mHurricaneMagic_nId;
	float	mHurricaneMagic_fRadius;
	INT		mHurricaneMagic_nIncrease;

	INT		mHurricaneMagic_nAddX;
	INT		mHurricaneMagic_nAddY;

	INT		mHurricaneMagic_nKind;

public:
	virtual	BOOL	CreateMagic(WORD wMagicNum, INT nFireTileX, INT nFireTileY, 
				                 INT nTargetTileX, INT nTargetTileY, INT nKind, CActor* pxOwner = NULL, INT nTarget = 0);
	BOOL	UpdateMagic(INT nLoopTime);
	BOOL	DrawMagic();
};

// ICE_WALL 전용
class CMiddleRepeateMagic : public CMagic
{
public:
	DWORD	m_dwMagiLifeTotal;
	INT		m_nEventID;					// 이벤트로관리된다.


	BOOL CreateMagic(INT nEventID, WORD wMagicNum, INT nFireTileX, INT nFireTileY, 
	                 INT nTargetTileX, INT nTargetTileY, DWORD dwMagicLifeTotal, CActor* pxOwner = NULL, INT nTarget = 0);
	BOOL UpdateMagic(INT nLoopTime);
	BOOL DrawMagic();
};

#endif // _CMAGIC_H

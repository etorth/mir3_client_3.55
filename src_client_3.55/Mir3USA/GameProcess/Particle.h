/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/


#ifndef _CPARTICLE_H
#define _CPARTICLE_H



#define _RAND_FLOAT			((FLOAT)(rand()%1000)/1000.0f)



/******************************************************************************************************************

	CParticle Class

*******************************************************************************************************************/
class CParticle
{
public:
//------------------------------------------------------------------------------------------------------------------
// 입자관련 정보.
	INT						m_nLife;					// 수명.
	INT						m_nCurrLife;				// 현재수명.
	D3DVECTOR				m_vecPos;					// 좌표.
	D3DVECTOR				m_vecOldPos;				// 좌표 보관.
	D3DVECTOR				m_vecDstPos;				// 목적좌표.
	D3DVECTOR				m_vecVel;					// 속도.
	D3DVECTOR				m_vecAccel;					// 가속도.
	D3DVECTOR				m_vecLocalForce;			// 파티클에 개별 영향을 주는 힘.
	D3DVECTOR				m_vecPrevDis;
	FLOAT					m_fMass;					// 질량.
	FLOAT					m_fSize;					// 크기.
	BOOL					m_bIsDead;					// 파티클의 존재여부.
	BYTE					m_bRed, m_bGreen, m_bBlue;	// 색.
	BYTE					m_bOpa;

	FLOAT					m_fOriSize;					// 처음크기.
	BYTE					m_bFstRed, m_bFstGreen, m_bFstBlue;	// 파티클 생성시점의색.
	BYTE					m_bEndRed, m_bEndGreen, m_bEndBlue;	// 파티클 종료시점의색.
//------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------
// 입자 Frame관련 정보.
	INT					m_nDelay;					// Animation Delay.
	INT					m_nCurrDelay;
	INT					m_nCurrFrame;				
//------------------------------------------------------------------------------------------------------------------
public:
	CParticle()
	{
		Init();
	}
	VOID Init()
	{
		m_nLife			= 0;		
		m_vecPos		= D3DVECTOR(0, 0, 0);		
		m_vecOldPos		= D3DVECTOR(0, 0, 0);		
		m_vecVel		= D3DVECTOR(0, 0, 0);		
		m_vecAccel		= D3DVECTOR(0, 0, 0);		
		m_vecLocalForce	= D3DVECTOR(0, 0, 0);
		m_vecDstPos		= D3DVECTOR(0, 0, 0);
		m_vecPrevDis	= D3DVECTOR(10000.0f, 10000.0f, 10000.0f);
		m_fMass			= 0.0f;
		m_fSize			= 0.0f;	
		m_fOriSize		= 0.0f;	
		m_bIsDead		= TRUE;		

		m_bRed = m_bGreen =  m_bBlue = 255;
		m_bFstRed = m_bFstGreen = m_bFstBlue = 255;
		m_bEndRed = m_bEndGreen = m_bEndBlue = 255;
		m_nDelay		= 0;		
		m_nCurrDelay	= 0;
		m_nCurrFrame	= 0;	
		m_nCurrLife		= 0;
		m_bOpa			= 255;
	}
};



/******************************************************************************************************************

	CParticleSystem Class
	파티클 관리 Base Class

*******************************************************************************************************************/
#define _MAX_PARTICLE_TEXTR 20

class CParticleSystem
{
protected:
//	FLOAT					m_fAirFiction;			// 공기마찰개수.(바람.)
//	D3DVECTOR				m_vecEnvironment;		// 입자에 작용하는 환경변수(중력, 바람).
	D3DVECTOR				m_vecBounding[2];		// 충돌체크영역 설정.

	INT						m_nNum;					// 입자의 갯수.
	CParticle*				m_pxParticle;			// 입자 개체.
    D3DVERTEX				m_avShape[4];			// Vertex.

	FLOAT					m_fDeltaTime;

public:
	D3DVECTOR				m_vecEnvironment;		// 입자에 작용하는 환경변수(중력, 바람).
	FLOAT					m_fAirFiction;			// 공기마찰개수.(바람.)

	CParticleSystem();
	virtual ~CParticleSystem();

	VOID UpdateAirFiction(INT nNum);				// 공기마찰계수 적용.
	VOID UpdateMove(INT nNum);						// 중력장 적용.
	VOID UpdateCrash(INT nNum);					// 충돌반발력 적용.

	__inline VOID SetEnvFactor(FLOAT fAirFriction = -0.05f, 
							   D3DVECTOR vecEnvironment = D3DVECTOR(0, 300, 0), 
							   D3DVECTOR vecMinBound = D3DVECTOR(0, 0, 0), 
							   D3DVECTOR vecMaxBound = D3DVECTOR(0, 0, 0))
	{
		m_fAirFiction	 = fAirFriction;
		m_vecEnvironment = vecEnvironment;
		m_vecBounding[0] = vecMinBound;
		m_vecBounding[1] = vecMaxBound;
	}

	virtual VOID	InitSystem();
	virtual VOID	SetupSystem(WORD wCnt = 200);
	virtual VOID	DestroySystem();
    virtual HRESULT RenderSystem(LPDIRECT3DDEVICE7 lpDevice) = 0;
	virtual VOID	UpdateSystem(INT nLoopTime, D3DVECTOR vecGenPos) = 0;
	virtual VOID	SetParticleDefault(INT nNum, D3DVECTOR vecGenPos) = 0;
};



/******************************************************************************************************************

	CScatter Class	

*******************************************************************************************************************/
#define _MAX_SCATTERFRAME	1
// 제련할때 쓰인다.
class CScatter : public CParticleSystem
{
private:
	SHORT	m_shPartNum;

public:
    CScatter();
    ~CScatter();

	virtual VOID	InitSystem();
	virtual VOID	DestroySystem();
	virtual VOID	SetupSystem(WORD wCnt = 2000);
    virtual HRESULT RenderSystem(LPDIRECT3DDEVICE7 lpDevice);

	virtual VOID	SetParticles(D3DVECTOR vecDstPos);
	virtual VOID	UpdateSystem(INT nLoopTime, D3DVECTOR vecGenPos = D3DVECTOR(0.0f, 0.0f, 0.0f));
	virtual VOID	SetParticleDefault(INT nNum, D3DVECTOR vecGenPos = D3DVECTOR(0.0f, 0.0f, 0.0f)) {}
};



/******************************************************************************************************************

	CSnow Class	

*******************************************************************************************************************/
#define _MAX_SNOWFRAME	1

class CSnow : public CParticleSystem
{
private:
    FLOAT	m_fWidth, m_fGround;
	SHORT	m_shPartNum;

public:
    CSnow();
    ~CSnow();

	virtual VOID	InitSystem();
	virtual VOID	DestroySystem();
	virtual VOID	SetupSystem(WORD wCnt = 500, FLOAT fWidth = 800, FLOAT fGround = 600);
    virtual HRESULT RenderSystem(LPDIRECT3DDEVICE7 lpDevice);

	virtual VOID	UpdateSystem(INT nLoopTime, D3DVECTOR vecGenPos = D3DVECTOR(0.0f, 0.0f, 0.0f));
	virtual VOID	SetParticleDefault(INT nNum, D3DVECTOR vecGenPos = D3DVECTOR(0.0f, 0.0f, 0.0f));
};



/******************************************************************************************************************

	CRain Class

*******************************************************************************************************************/
#define _MAX_RAINFRAME		1
#define _MAX_RAINDROPFRAME	5

class CRain : public CParticleSystem
{
private:
    FLOAT	m_fWidth, m_fGround;

	BYTE	m_bRainIntensity;			// 비의강도.
	SHORT	m_shPartNum;

public:
	BYTE	m_bGenCnt;					

    CRain();
    ~CRain();

	virtual VOID	InitSystem();
	virtual VOID	DestroySystem();
	virtual VOID	SetupSystem(WORD wCnt = 400, FLOAT fWidth = 800, FLOAT fGround = 600);
    virtual HRESULT RenderSystem(LPDIRECT3DDEVICE7 lpDevice);

	virtual VOID	UpdateSystem(INT nLoopTime, D3DVECTOR vecGenPos = D3DVECTOR(0.0f, 0.0f, 0.0f));
	virtual VOID	SetParticleDefault(INT nNum, D3DVECTOR vecGenPos = D3DVECTOR(0.0f, 0.0f, 0.0f));
};



/******************************************************************************************************************

	CFly Class
	날아가는 형태의 Praticle관리.(유성의 꼬리)

*******************************************************************************************************************/
#define _MAX_FLYFRAME	4

class CFly : public CParticleSystem
{
private:
	BYTE	m_bGenCnt;					

public:
	CFly();
	~CFly();
		
	virtual VOID	InitSystem();
	virtual VOID	DestroySystem();
	virtual VOID	SetupSystem(WORD wCnt = 100);
    virtual HRESULT RenderSystem(LPDIRECT3DDEVICE7 lpDevice);

	virtual VOID	UpdateSystem(INT nLoopTime, D3DVECTOR vecGenPos = D3DVECTOR(0.0f, 0.0f, 0.0f));
	virtual VOID	SetParticleDefault(INT nNum, D3DVECTOR vecGenPos = D3DVECTOR(0.0f, 0.0f, 0.0f));
};



/******************************************************************************************************************

	CBoom
	폭발 형태의 Praticle관리.

*******************************************************************************************************************/
#define _MAX_BOOMFRAME	4

class CBoom : public CParticleSystem
{
private:
	SHORT	m_shPartNum;

public:
	CBoom();
	~CBoom();
		
	virtual VOID	InitSystem();
	virtual VOID	DestroySystem();
	virtual VOID	SetupSystem(WORD wCnt = 1000);
    virtual HRESULT RenderSystem(LPDIRECT3DDEVICE7 lpDevice);

	VOID	SetBoomParticle(D3DVECTOR vecGenPos);
	VOID	SetBoomParticle2(D3DVECTOR vecGenPos);
	VOID	SetBoomParticle3(D3DVECTOR vecGenPos);
	VOID	SetBoomParticle4(D3DVECTOR vecGenPos);
	VOID	SetBoomParticle5(D3DVECTOR vecGenPos);
	VOID	SetBoomParticle6(D3DVECTOR vecGenPos);

	virtual VOID	UpdateSystem(INT nLoopTime, D3DVECTOR  vecGenPos = D3DVECTOR(0, 0, 0));
	virtual VOID	SetParticleDefault(INT nNum, D3DVECTOR vecGenPos);
	virtual VOID	SetParticleDefault2(INT nNum, D3DVECTOR vecGenPos);
	virtual VOID	SetParticleDefault3(INT nNum, D3DVECTOR vecGenPos);
	
};



/******************************************************************************************************************

	CFlyingTail
	날아가는 형태의 Praticle관리.

*******************************************************************************************************************/
#define _MAX_FLYTAILFRAME	1

class CFlyingTail : public CParticleSystem
{
private:
	SHORT	m_shPartNum;

public:
	CFlyingTail();
	~CFlyingTail();
		
	virtual VOID	InitSystem();
	virtual VOID	DestroySystem();
	virtual VOID	SetupSystem(WORD wCnt = 1000);
    virtual HRESULT RenderSystem(LPDIRECT3DDEVICE7 lpDevice);

	VOID	SetFlyTailParticle(D3DVECTOR vecGenPos);
	VOID	SetFlyTailParticleEx(D3DVECTOR vecGenPos);
	VOID	SetFlyTailParticleEx2(D3DVECTOR vecGenPos);
	VOID	SetFlyTailParticleEx3(D3DVECTOR vecGenPos);
	VOID	SetFlyTailParticleEx4(D3DVECTOR vecGenPos);
	VOID	SetFlyTailParticleEx5(D3DVECTOR vecGenPos);


	virtual VOID	UpdateSystem(INT nLoopTime, D3DVECTOR vecGenPos = D3DVECTOR(0, 0, 0));
	virtual VOID	SetParticleDefault(INT nNum, D3DVECTOR vecGenPos);
};









/******************************************************************************************************************

	CSmoke

*******************************************************************************************************************/
#define _MAX_SMOKEFRAME		1
class CSmoke : public CParticleSystem
{
private:
	SHORT	m_shPartNum;
public:
	CSmoke();
	~CSmoke();
		
	virtual VOID	InitSystem();
	virtual VOID	DestroySystem();
	virtual VOID	SetupSystem(WORD wCnt = 1000);
    virtual HRESULT RenderSystem(LPDIRECT3DDEVICE7 lpDevice);

	VOID	SetSmokeParticle(D3DVECTOR vecGenPos);
	VOID	SetSmokeParticleEx(D3DVECTOR vecGenPos);
	VOID	SetSmokeParticleEx2(D3DVECTOR vecGenPos);
	VOID	SetSmokeParticleEx3(D3DVECTOR vecGenPos);
	VOID	SetSmokeParticleEx4(D3DVECTOR vecGenPos);
	VOID	SetSmokeParticleEx5(D3DVECTOR vecGenPos);
	VOID	SetSmokeParticleEx6(D3DVECTOR vecGenPos);
	VOID	SetSmokeParticleEx7(D3DVECTOR vecGenPos);
	VOID	SetSmokeParticleEx8(D3DVECTOR vecGenPos);
	VOID	SetSmokeParticleEx9(D3DVECTOR vecGenPos);
	VOID	SetSmokeParticleEx10(D3DVECTOR vecGenPos);
	VOID	SetSmokeParticleEx11(D3DVECTOR vecGenPos);
	VOID	SetSmokeParticleEx12(D3DVECTOR vecGenPos);
	VOID	SetSmokeParticleEx13(D3DVECTOR vecGenPos);

	virtual VOID	UpdateSystem(INT nLoopTime, D3DVECTOR vecGenPos = D3DVECTOR(0, 0, 0));
	virtual VOID	SetParticleDefault(INT nNum, D3DVECTOR vecGenPos);
};



/******************************************************************************************************************

	CElec
	전기 파장 Praticle관리.

*******************************************************************************************************************/
#define _MAX_ELECFRAME	1
#define _MAX_ELEC_NODEX	2
#define _MAX_ELEC_NODEY	10
#define _ELEC_INDICES	_MAX_ELEC_NODEX*_MAX_ELEC_NODEY*3*2
#define _ELEC_VERTICES	(_MAX_ELEC_NODEX+1)*(_MAX_ELEC_NODEY+1)
class CElec
{
private:
	SHORT		m_shPosX, m_shPosY;
	SHORT		m_shDstPosX, m_shDstPosY;

	FLOAT		m_fSize;
	FLOAT		m_fRadian;

	D3DVERTEX	m_avElec[_MAX_ELEC_NODEY+1][_MAX_ELEC_NODEX+1];
	D3DVERTEX	m_avSaveElec[_MAX_ELEC_NODEY+1][_MAX_ELEC_NODEX+1];
//	D3DLVERTEX	m_avElec[_MAX_ELEC_NODE+1][2];
	WORD		m_pwElecIndices[_ELEC_INDICES];

public:
	CElec();
	~CElec();

	VOID		InitElec();
	VOID		DestroyElec();

	VOID		SetupElec();

	VOID		UpdateElec(SHORT shPosX, SHORT shPosY, SHORT shDstPosX, SHORT shDstPosY);

	HRESULT		RenderElec(LPDIRECT3DDEVICE7 lpDevice);
};


#define _MIST_STATE_START 0

class CMist
{
public:
	BOOL	m_bActive;
	BYTE	m_bMistState;	

	D3DVERTEX m_avBillboard[4];
	D3DVECTOR m_vTrans;
	D3DVECTOR m_vScale;	

private:

public:
	CMist();
	~CMist();
	BOOL Create();			// 안개 생성.	
	VOID Init();			// 안개 변수 초기화.
	VOID Destory();			// 텍스춰등의 메모리해제.
	HRESULT DrawMist();
	VOID ProgressMist();	// 안개 진행.(안개시작시점, 안개진행, 안개종료시점에서 서로 다르다.)
};



#endif // _CPARTICLE_H
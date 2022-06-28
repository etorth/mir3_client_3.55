/******************************************************************************************************************
                                                                                                                   
	����:																											
																													
	�ۼ���:																											
	�ۼ���:																											
																													
	[����][������] : ���� ����																						
                                                                                                                   
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
	BYTE				m_bActiveState;							// ���� Ȱ��ȭ����.(�����Ҹ�ÿ� ���ȴ�.)
	BOOL				m_bRepeat;								// �ִϸ��̼��� �ݺ�����.
	BOOL				m_bFixed;								// ������ �̵�����.
	WORD				m_wMagicNum;							// ������ȣ.

	CActor*				m_pxOwner;								// �����߻���ü.
	CActor*				m_pxTarget;								// �����߻簴ü.

	D3DVERTEX			m_avMagic[4];
	CWHWilImageData*	m_pxMagicImg;

	// ��ǥ����.
	INT					m_nScrnX, m_nScrnY;								// ������ũ����ǥ.
	FLOAT				m_fFloatScrnX, m_fFloatScrnY;					// ������ũ����ǥ.
	INT					m_nTileX, m_nTileY;								// ����Ÿ����ǥ.

	INT					m_nFireScrnX, m_nFireScrnY;						// ����������ũ����ǥ.	
	INT					m_nFireTileX, m_nFireTileY;						// ��������Ÿ����ǥ.

	INT					m_nTargetScrnX, m_nTargetScrnY;					// ��ǥ���� ��ũ����ǥ.
	INT					m_nTargetTileX, m_nTargetTileY;					// ��ǥ���� Ÿ����ǥ.(��ȭ�ɼ��ִ�.)

	LPDIRECTDRAWSURFACE7 m_testlpddsMagicTextr;
	BOOL				 m_tsetbool;

	// ����������.
	INT					m_nCurrDelay;									// �����ð����尪.
	INT					m_nCurrLightDelay;
	INT					m_nFrmDelay;									// �������� �ѱ�� ���� �����ð���.
	DWORD				m_dwMagicLife;									// ������ ����ǰ� �ִ� �ð�.(ms����)

	BYTE				m_bLightRadius[2];								// ���� �ʺ�.
	BYTE				m_bLightColor[2][3];							// ���� ��.
	BYTE				m_bMagicColor[3];								// ��.

	DWORD				m_dwFstFrame;									// ���� ������ ����������.
	DWORD				m_dwEndFrame;									// ���� ������ ������������.
	DWORD				m_dwCurrFrame;									// ���������尪.

	BYTE				m_bBlendType;									// ������ ����·� �׸����ΰ��� ����.
	BYTE				m_bOpacity;										// 0 - 255�ܰ�. 0�� ���� ����(����Ʈ����), 255�� ������.
	BYTE				m_bSwingCnt;									// ������ ��鸲 ������ �ش�.

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



// _SKILL_HOLYSHIELD, _SKILL_EARTHFIRE, _SKILL_LIGHTWALL ����.
class CRepeatMagic : public CMagic
{
private:
public:
	DWORD	m_dwMagiLifeTotal;
	INT		m_nEventID;					// �̺�Ʈ�ΰ����ȴ�.

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

//	_SKILL_HURRICANE ����
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

// ICE_WALL ����
class CMiddleRepeateMagic : public CMagic
{
public:
	DWORD	m_dwMagiLifeTotal;
	INT		m_nEventID;					// �̺�Ʈ�ΰ����ȴ�.


	BOOL CreateMagic(INT nEventID, WORD wMagicNum, INT nFireTileX, INT nFireTileY, 
	                 INT nTargetTileX, INT nTargetTileY, DWORD dwMagicLifeTotal, CActor* pxOwner = NULL, INT nTarget = 0);
	BOOL UpdateMagic(INT nLoopTime);
	BOOL DrawMagic();
};

#endif // _CMAGIC_H

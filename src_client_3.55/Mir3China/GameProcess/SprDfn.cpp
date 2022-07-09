/******************************************************************************************************************
                                                                                                                   
	����:																											
																													
	�ۼ���:																											
	�ۼ���:																											
																													
	[����][������] : ���� ����																						
                                                                                                                   
*******************************************************************************************************************/


#include "StdAfx.h"





/******************************************************************************************************************

	CSprite Class

*******************************************************************************************************************/
/******************************************************************************************************************

	�Լ��� : CSprite::CSprite()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	���   : 

	[����][������] : ��������

*******************************************************************************************************************/
CSprite::CSprite()
{
	InitSpriteInfo();
}



/******************************************************************************************************************

	�Լ��� : CSprite::~CSprite()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	���   : 

	[����][������] : ��������

*******************************************************************************************************************/
CSprite::~CSprite()
{
	DeleteSpriteInfo();
}



/******************************************************************************************************************

	�Լ��� : CSprite::InitSpriteInfo()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CSprite::InitSpriteInfo()
{	
	ZeroMemory(m_stHeroSpr, sizeof(SPRFRMDEF)*_MAX_HERO_MTN);
	ZeroMemory(m_stMonSpr, sizeof(SPRFRMDEF)*_MAX_MON_MTN);
	ZeroMemory(m_stNPCSpr, sizeof(SPRFRMDEF)*_MAX_NPC_MTN);

	m_pstEffectSpr	   = NULL;
	m_pstMagicSpr	   = NULL;
	m_pstExplosionSpr  = NULL;

	m_nEffectCnt	   = 0;
	m_nMagicCnt		   = 0;
	m_nExplosionCnt	   = 0;
}



/******************************************************************************************************************

	�Լ��� : CSprite::DeleteSpriteInfo()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CSprite::DeleteSpriteInfo()
{
	SAFE_DELETEARR(m_pstEffectSpr);
	SAFE_DELETEARR(m_pstMagicSpr);
	SAFE_DELETEARR(m_pstExplosionSpr);
}
 


/******************************************************************************************************************

	�Լ��� : CSprite::SetEffectInfo()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : LPEFFECTSPRINFO pstEffect
	         DWORD dwFstFrm
	         DWORD dwEndFrm
	         WORD wDelay
	         WORD wImgIdx
	         WORD wEffectIdx
	         BYTE bSLightRadius
	         BYTE bLLightRadius
	         BYTE bSLightRColor
	         BYTE bSLightGColor
	         BYTE bSLightBColor
	         BYTE bLLightRColor
	         BYTE bLLightGColor
	         BYTE bLLightBColor
	         BYTE bBlendType
	         BYTE bOpa
	         BYTE bSwingCnt
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CSprite::SetEffectInfo(LPEFFECTSPRINFO pstEffect, DWORD dwFstFrm, DWORD dwEndFrm, WORD wDelay, WORD wImgIdx, WORD wEffectIdx,
				   BYTE bSLightRadius, BYTE bLLightRadius, 
				   BYTE bSLightRColor, BYTE bSLightGColor, BYTE bSLightBColor,
				   BYTE bLLightRColor, BYTE bLLightGColor, BYTE bLLightBColor, 
				   BYTE bMagicRColor, BYTE bMagicGColor, BYTE bMagicBColor, 
				   BYTE bBlendType, BYTE bOpa, BYTE bSwingCnt, 
				   BYTE bDir, BOOL bRepeat, BOOL bFixed, BOOL bShowLight, BOOL bTargetUse)
{
	pstEffect->dwFstFrm = dwFstFrm;
	pstEffect->dwEndFrm = dwEndFrm;
	pstEffect->wDelay	= wDelay;
	pstEffect->wImgIdx  = wImgIdx;
	pstEffect->wEffectIdx = wEffectIdx;

	pstEffect->bLightRadius[0] = bSLightRadius;
	pstEffect->bLightRadius[1] = bLLightRadius;

	pstEffect->bLightColor[0][0] = bSLightRColor;
	pstEffect->bLightColor[0][1] = bSLightGColor;
	pstEffect->bLightColor[0][2] = bSLightBColor;

	pstEffect->bLightColor[1][0] = bLLightRColor;
	pstEffect->bLightColor[1][1] = bLLightGColor;
	pstEffect->bLightColor[1][2] = bLLightBColor;

	pstEffect->bMagicColor[0] = bMagicRColor;
	pstEffect->bMagicColor[1] = bMagicGColor;
	pstEffect->bMagicColor[2] = bMagicBColor;

	pstEffect->bBlendType	= bBlendType;
	pstEffect->bOpa			= bOpa;
	pstEffect->bSwingCnt	= bSwingCnt;

	pstEffect->bDir			= bDir;
	pstEffect->bRepeat		= bRepeat;
	pstEffect->bFixed		= bFixed;
	pstEffect->bShowLight	= bShowLight;
	pstEffect->bTargetUse	= bTargetUse;
}


/******************************************************************************************************************

	�Լ��� : CSprite::GetEffectInfo()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : WORD wEffectNum
	���   : LPEFFECTSPRINFO 

	[����][������] : ��������

*******************************************************************************************************************/
LPEFFECTSPRINFO CSprite::GetEffectInfo(WORD wEffectNum)
{
	LPEFFECTSPRINFO pstEffect = NULL;

	for ( INT nCnt = 0; nCnt < m_nEffectCnt; nCnt++ )
	{
		if ( wEffectNum == m_pstEffectSpr[nCnt].wEffectIdx )
		{
			pstEffect = &m_pstEffectSpr[nCnt];			
			break;
		}
	}

	return pstEffect;
}



/******************************************************************************************************************

	�Լ��� : CSprite::GetExplosionInfo()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : WORD wEffectNum
	���   : LPEFFECTSPRINFO 

	[����][������] : ��������

*******************************************************************************************************************/
LPEFFECTSPRINFO CSprite::GetExplosionInfo(WORD wEffectNum)
{
	LPEFFECTSPRINFO pstEffect = NULL;

	for ( INT nCnt = 0; nCnt < m_nExplosionCnt; nCnt++ )
	{
		if ( wEffectNum == m_pstExplosionSpr[nCnt].wEffectIdx )
		{
			pstEffect = &m_pstExplosionSpr[nCnt];
			break;
		}
	}

	return pstEffect;
}



/******************************************************************************************************************

	�Լ��� : CSprite::GetMagicInfo()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : WORD wEffectNum
	���   : LPEFFECTSPRINFO 

	[����][������] : ��������

*******************************************************************************************************************/
LPEFFECTSPRINFO CSprite::GetMagicInfo(WORD wEffectNum)
{
	LPEFFECTSPRINFO pstEffect = NULL;

	for ( INT nCnt = 0; nCnt < m_nMagicCnt; nCnt++ )
	{
		if ( wEffectNum == m_pstMagicSpr[nCnt].wEffectIdx )
		{
			pstEffect = &m_pstMagicSpr[nCnt];		
			break;
		}
	}

	return pstEffect;
}



/******************************************************************************************************************

	�Լ��� : CSprite::SetSprDfn()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : LPSPRFRMDEF pstSprDfn
	         WORD wFstFrm
	         WORD wFrmCnt
	         WORD wDelay
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CSprite::SetSprDfn(LPSPRFRMDEF pstSprDfn, WORD wFstFrm, WORD wFrmCnt, WORD wDelay)
{
	pstSprDfn->wFstFrm	= wFstFrm;
	pstSprDfn->wFrmCnt	= wFrmCnt;
	pstSprDfn->wDelay	= wDelay;
}


/******************************************************************************************************************

	�Լ��� : CSprite::SetInfo()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
BOOL CSprite::SetInfo()
{
	SetWeaponOrder("weapon.ord");

	//~~~ Hero ��������Ʈ ����. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	SetSprDfn(&m_stHeroSpr[0],     0,  4, 200);			// _MT_STAND		
	SetSprDfn(&m_stHeroSpr[1],    80,  6, 100);			// _MT_ARROWATTACK	
	SetSprDfn(&m_stHeroSpr[2],   160,  5,  75);			// _MT_SPELL1		
	SetSprDfn(&m_stHeroSpr[3],   240,  5,  75);			// _MT_SPELL2		
	SetSprDfn(&m_stHeroSpr[4],   320,  1, 100);			// _MT_HOLD		
	SetSprDfn(&m_stHeroSpr[5],   400,  1, 100);			// _MT_PUSHBACK	
	SetSprDfn(&m_stHeroSpr[6],   480,  1, 100);			// _MT_PUSHBACKFLY	
	SetSprDfn(&m_stHeroSpr[7],   560,  3, 200);			// _MT_ATTACKMODE	
	SetSprDfn(&m_stHeroSpr[8],   640,  2, 400);			// _MT_CUT			
	SetSprDfn(&m_stHeroSpr[9],   720,  6,  85);			// _MT_ONEVSWING
	SetSprDfn(&m_stHeroSpr[10],  800,  6,  85);			// _MT_TWOVSWING	
	SetSprDfn(&m_stHeroSpr[11],  880,  6,  85);			// _MT_ONEHSWING	
	SetSprDfn(&m_stHeroSpr[12],  960,  6,  85);			// _MT_TWOHSWING	
	SetSprDfn(&m_stHeroSpr[13], 1040,  6,  85);			// _MT_SPEARVSWING	
	SetSprDfn(&m_stHeroSpr[14], 1120,  6,  85);			// _MT_SPEARHSWING	
	SetSprDfn(&m_stHeroSpr[15], 1200,  3, 100);			// _MT_HITTED		
	SetSprDfn(&m_stHeroSpr[16], 1280, 10,  70);			// _MT_WHEELWIND	
	SetSprDfn(&m_stHeroSpr[17], 1360, 10,  90);			// _MT_RANDSWING	
	SetSprDfn(&m_stHeroSpr[18], 1440, 10,  70);			// _MT_BACKDROPKICK
	SetSprDfn(&m_stHeroSpr[19], 1520, 10, 120);			// _MT_DIE			
	SetSprDfn(&m_stHeroSpr[20], 1600, 10, 100);			// _MT_SPECIALDIE	
	SetSprDfn(&m_stHeroSpr[21], 1680,  6,  90);			// _MT_WALK		
	SetSprDfn(&m_stHeroSpr[22], 1760,  6, 120);			// _MT_RUN			
	SetSprDfn(&m_stHeroSpr[23], 1840,  6, 100);			// _MT_MOODEPO		
	SetSprDfn(&m_stHeroSpr[24], 1920, 10, 100);			// _MT_ROLL		
	SetSprDfn(&m_stHeroSpr[25], 2000,  4, 180);			// _MT_FISHSTAND	
	SetSprDfn(&m_stHeroSpr[26], 2080,  3, 180);			// _MT_FISHHAND	
	SetSprDfn(&m_stHeroSpr[27], 2160,  8, 180);			// _MT_FISHTHROW	
	SetSprDfn(&m_stHeroSpr[28], 2240,  8, 180);			// _MT_FISHPULL	
	SetSprDfn(&m_stHeroSpr[29], 2320,  4, 200);			// _MT_HORSESTAND	
	SetSprDfn(&m_stHeroSpr[30], 2400,  6, 100);			// _MT_HORSEWALK	
	SetSprDfn(&m_stHeroSpr[31], 2480,  6, 100);			// _MT_HORSERUN	
	SetSprDfn(&m_stHeroSpr[32], 2560,  3, 100);			// _MT_HORSEHIT	

	//~~~ Monster ��������Ʈ ����. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	SetSprDfn(&m_stMonSpr[0],     0,  4, 300);			// ���޵���.
	SetSprDfn(&m_stMonSpr[1],    80,  6, 130);			// �ȱ⵿��.
	SetSprDfn(&m_stMonSpr[2],   160,  6, 120);			// �Ϲݰ��ݵ���.
	SetSprDfn(&m_stMonSpr[3],   240,  2, 300);			// �±⵿��.
	SetSprDfn(&m_stMonSpr[4],   320, 10, 150);			// �ױ⵿��.
	SetSprDfn(&m_stMonSpr[5],   400,  6, 150);			// Ư�����ݵ���1.
	SetSprDfn(&m_stMonSpr[6],   480, 10, 150);			// Ư�����ݵ���2.
	SetSprDfn(&m_stMonSpr[7],   560, 10, 150);			// ������⵿��.
	SetSprDfn(&m_stMonSpr[8],   640,  6, 150);			// Ư������.

	//~~~ NPC ��������Ʈ ����. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	SetSprDfn(&m_stNPCSpr[0],     0,  4, 300);			// ���޵���.
	SetSprDfn(&m_stNPCSpr[1],    30, 10, 300);			// Ư������1.
	SetSprDfn(&m_stNPCSpr[2],    60,  6, 300);			// Ư������2.

	return LoadMagicInfo();
/*	//~~~ Effect Frame Define. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	SetEffectInfo(&m_stEffectSpr[0],   230,  236, 100, _IMAGE_MAGIC,       _SKILL_BANWOL, 3, 4, 100, 100, 100, 100, 100, 170);	// �ݿ����� 12��.
	SetEffectInfo(&m_stEffectSpr[1],    60,   70, 100, _IMAGE_MAGIC,    _SKILL_AMYOUNSUL, 3, 4, 100, 100, 100, 100, 160, 100, 255, 255, 255, _BLEND_NORMAL);	// �Ͽ��� ����.
	SetEffectInfo(&m_stEffectSpr[2],    90,   98, 100, _IMAGE_MAGIC,     _SKILL_FIREWIND, 3, 4, 100, 100, 100, 100, 140, 180);	// ȭ��ǳ.
	SetEffectInfo(&m_stEffectSpr[3],  1820, 1828, 100, _IMAGE_MAGIC,         _SKILL_FIRE, 3, 4, 100, 100, 100, 100, 140, 180);	// ������ ����.
	SetEffectInfo(&m_stEffectSpr[4],     0,    9, 100, _IMAGE_MAGIC,      _SKILL_TAMMING, 3, 4, 100, 100, 100, 170, 100, 100);	// ��ȥ�ݽ���.
	SetEffectInfo(&m_stEffectSpr[5],  2360, 2370, 100, _IMAGE_MAGIC,    _SKILL_SPACEMOVE, 3, 4, 100, 100, 100, 170, 100, 100);	// �ư����.
	SetEffectInfo(&m_stEffectSpr[6],   130,  140, 100, _IMAGE_MAGIC,   _SKILL_KILLUNDEAD, 3, 4, 100, 100, 100, 170, 100, 100);	// ������ȸ����.
	SetEffectInfo(&m_stEffectSpr[7],  1820, 1828, 100, _IMAGE_MAGIC,     _SKILL_FIREBALL, 3, 4, 100, 100, 100, 100, 140, 180);	// ȭ����.
	SetEffectInfo(&m_stEffectSpr[8],   600,  610, 100, _IMAGE_MAGIC,     _SKILL_HEALLING, 3, 4, 100, 100, 100, 140, 100, 120);	// ȸ����.
	SetEffectInfo(&m_stEffectSpr[9],   630,  640, 100, _IMAGE_MAGIC,   _SKILL_HOLYSHIELD, 3, 4, 100, 100, 100, 170, 100, 100);	// ���.
	SetEffectInfo(&m_stEffectSpr[10],  660,  670, 100, _IMAGE_MAGIC,  _SKILL_BIGHEALLING, 3, 4, 100, 100, 100, 140, 100, 120);	// ��ȸ��.
	SetEffectInfo(&m_stEffectSpr[11],  690,  701, 100, _IMAGE_MAGIC,  _SKILL_LIGHTFLOWER, 3, 4, 150, 100,  50, 150, 100,  50);	// �ڼ�ȭ.	
	SetEffectInfo(&m_stEffectSpr[12], 1970, 1978,  80, _IMAGE_MAGIC, _SKILL_SHOOTLIGHTEN, 3, 4, 100, 100, 100, 170, 100, 100);	// ������.
	SetEffectInfo(&m_stEffectSpr[13],  740,  750, 100, _IMAGE_MAGIC,    _SKILL_SKELLETON, 3, 4, 100, 100, 100, 120, 100, 120);	// ����ȯ��.
	SetEffectInfo(&m_stEffectSpr[14],  770,  780, 100, _IMAGE_MAGIC,     _SKILL_SNOWWIND, 3, 4, 100, 100, 100, 170, 100, 100);	// ����ǳ.
	SetEffectInfo(&m_stEffectSpr[15],  870,  890, 100, _IMAGE_MAGIC,       _SKILL_SHOWHP, 3, 4, 100, 100, 100, 100, 100, 170);	// Ž���Ŀ�.
	SetEffectInfo(&m_stEffectSpr[16],  910,  920, 100, _IMAGE_MAGIC,    _SKILL_EARTHFIRE, 3, 4, 100, 100, 100, 100, 140, 180);	// ������.
	SetEffectInfo(&m_stEffectSpr[17],  940,  950, 100, _IMAGE_MAGIC,     _SKILL_FIREBOOM, 3, 4, 100, 100, 100, 100, 140, 180);	// ������.
	SetEffectInfo(&m_stEffectSpr[18], 1560, 1569, 100, _IMAGE_MAGIC,    _SKILL_FIREBALL2, 3, 4, 100, 100, 100, 100, 140, 180);	// �ݰ�ȭ����.
	SetEffectInfo(&m_stEffectSpr[19],  320,  326, 100, _IMAGE_MAGIC,        _SKILL_ERGUM, 3, 4, 100, 100, 100, 100, 100, 170);	// ��˼�.
	SetEffectInfo(&m_stEffectSpr[20], 1350, 1356, 100, _IMAGE_MAGIC,         _SKILL_YEDO, 3, 4, 100, 100, 100, 100, 100, 170);	// �����˹�.
	SetEffectInfo(&m_stEffectSpr[21], 1470, 1476, 100, _IMAGE_MAGIC,    _SKILL_FIRESWORD, 3, 4, 100, 100, 100, 100, 140, 180);	// ��ȭ��.
	SetEffectInfo(&m_stEffectSpr[22], 1430, 1442, 100, _IMAGE_MAGIC,   _SKILL_LIGHTENING, 3, 4, 100, 100, 100, 170, 100, 100);	// ����.
	SetEffectInfo(&m_stEffectSpr[23],  810,  820, 100, _IMAGE_MAGIC,        _SKILL_CLOAK, 3, 4, 150, 150, 150, 200, 150, 180);	// ����.
	SetEffectInfo(&m_stEffectSpr[24], 2080, 2086, 100, _IMAGE_MAGIC, _SKILL_HANGMAJINBUB, 3, 4, 150, 100,  50, 200, 150, 100);	// �׸�����.
	SetEffectInfo(&m_stEffectSpr[25], 2080, 2086, 100, _IMAGE_MAGIC,    _SKILL_DEJIWONHO, 3, 4, 150, 180, 200, 180, 200, 220);	// ������ȣ.
	SetEffectInfo(&m_stEffectSpr[26], 2080, 2086, 100, _IMAGE_MAGIC,    _SKILL_FIRECHARM, 3, 4, 100, 150, 200, 150, 200, 250);	// �����.
	SetEffectInfo(&m_stEffectSpr[27], 2080, 2086, 100, _IMAGE_MAGIC,     _SKILL_BIGCLOAK, 3, 4, 150, 150, 150, 200, 150, 180);	// ������.
	SetEffectInfo(&m_stEffectSpr[28], 2180, 2190, 100, _IMAGE_MAGIC,     _SKILL_JUMPSHOT, 3, 4, 150, 150, 150, 200, 150, 180);	// ������.
	SetEffectInfo(&m_stEffectSpr[29], 2270, 2280, 100, _IMAGE_MAGIC,    _SKILL_RANDSWING, 3, 4, 150, 150, 150, 200, 150, 180);	// ��������.
	SetEffectInfo(&m_stEffectSpr[30], 2080, 2086, 100, _IMAGE_MAGIC,		_SKILL_SINSU, 3, 4, 150, 150, 150, 200, 150, 180, 255, 255, 255, _BLEND_NORMAL, 255);	// �ż���ȯ.

	SetEffectInfo(&m_stEffectSpr[31], 1680, 1686, 100, _IMAGE_MONMAGIC, _MONMAGIC_NUMAGUMGI, 3, 4, 150, 150, 150, 200, 150, 180, 255, 255, 255, _BLEND_NORMAL, 255);// ������ �˱�.
	SetEffectInfo(&m_stEffectSpr[32], 830, 849, 100, _IMAGE_MAGIC, _SKILL_SHIELD, 3, 4, 100, 100, 100, 170, 100, 100);			// �ּ��Ǹ�.

	SetEffectInfo(&m_stEffectSpr[33], 1800, 1810, 100, _IMAGE_MONMAGIC, _MONMAGIC_BOSSATT, 3, 4, 150, 100, 50, 200, 150, 100);	// ��õȲ����.

	SetEffectInfo(&m_stEffectSpr[34], 2620, 2626, 100, _IMAGE_MAGIC, _SKILL_ICEBOLT, 3, 4, 100, 100, 100, 170, 100, 100);		// ������.
	SetEffectInfo(&m_stEffectSpr[35], 2880, 2886, 100, _IMAGE_MAGIC, _SKILL_SUPERICEBOLT, 3, 4, 100, 100, 100, 170, 100, 100);	// ������õ��.
	SetEffectInfo(&m_stEffectSpr[36], 2990, 2996, 100, _IMAGE_MAGIC, _SKILL_MAGICARROW, 3, 4, 100, 100, 100, 170, 100, 100);	// �����.
	SetEffectInfo(&m_stEffectSpr[37], 3250, 3256, 100, _IMAGE_MAGIC, _SKILL_MOONOK, 3, 4, 100, 100, 100, 170, 100, 100);		// ������.
	SetEffectInfo(&m_stEffectSpr[38], 3360, 3366, 100, _IMAGE_MAGIC, _SKILL_MOONCHAM, 3, 4, 100, 100, 100, 170, 100, 100);		// ������.

	SetEffectInfo(&m_stEffectSpr[39], 2120, 2126, 150, _IMAGE_MONMAGIC, _MONMAGIC_GUMGI, 2, 3, 100, 100, 100, 150, 150, 150);	// �Ű����Ͱ˱�ȿ��.

	SetEffectInfo(&m_stEffectSpr[40], 3560, 3570, 150, _IMAGE_MAGIC, _SKILL_ICE, 3, 4, 100, 100, 100, 200, 100, 100, 255, 255, 255, _BLEND_NORMAL);			// ������.


	//~~~ Monster Effect Frame Define. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	//~~~ Magic Frame Define. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	SetEffectInfo(&m_stMagicSpr[0],    70,   88, 100, _IMAGE_MAGIC,    _SKILL_AMYOUNSUL, 3, 4, 190, 220, 190, 190, 240, 190, 255, 255, 255, _BLEND_NORMAL); // �Ͽ���.
	SetEffectInfo(&m_stMagicSpr[1],  1900, 1960,  50, _IMAGE_MAGIC,         _SKILL_FIRE, 3, 4,  70,  90, 110,  90, 120, 150);	// ������.
	SetEffectInfo(&m_stMagicSpr[2],    10,   30,  50, _IMAGE_MAGIC,      _SKILL_TAMMING, 3, 4, 200, 100, 100, 250, 150, 150);	// ��ȥ��.
	SetEffectInfo(&m_stMagicSpr[3],   140,  159,  50, _IMAGE_MAGIC,   _SKILL_KILLUNDEAD, 3, 4, 200, 100, 100, 100,  75,  50);	// ������ȸ.
	SetEffectInfo(&m_stMagicSpr[4],   420,  425,  20, _IMAGE_MAGIC,     _SKILL_FIREBALL, 2, 3, 100, 150, 200, 150, 200, 250);	// ȭ����.
	SetEffectInfo(&m_stMagicSpr[5],   610,  620, 100, _IMAGE_MAGIC,     _SKILL_HEALLING, 3, 4, 200, 140, 170, 230, 170, 200);	// ȸ����.
	SetEffectInfo(&m_stMagicSpr[6],   640,  650, 100, _IMAGE_MAGIC,   _SKILL_HOLYSHIELD, 3, 4, 120,  60,  60, 150,  80,  80);	// ���.
	SetEffectInfo(&m_stMagicSpr[7],   670,  680, 100, _IMAGE_MAGIC,  _SKILL_BIGHEALLING, 4, 5, 200, 140, 170, 230, 170, 200);//200, 100, 100, 250, 150, 150);	// ��ȸ��.
	SetEffectInfo(&m_stMagicSpr[8],  2050, 2056,  80, _IMAGE_MAGIC, _SKILL_SHOOTLIGHTEN, 10, 11, 225, 50, 50, 255, 100, 100);	// ������.
	SetEffectInfo(&m_stMagicSpr[9],   750,  760, 155, _IMAGE_MAGIC,    _SKILL_SKELLETON, 3, 4, 150, 150, 150, 200, 150, 180);	// ����ȯ��.
	SetEffectInfo(&m_stMagicSpr[10],  780,  800, 100, _IMAGE_MAGIC,     _SKILL_SNOWWIND, 5, 6, 255, 123,   0, 255, 123,   0, 255, 255, 255, _BLEND_LIGHTINV, 0, 1);	// ����ǳ.
//	SetEffectInfo(&m_stMagicSpr[10],  780,  800, 100, _IMAGE_MAGIC,     _SKILL_SNOWWIND, 4, 5, 220, 150, 150, 250, 170, 170);	// ����ǳ.
	SetEffectInfo(&m_stMagicSpr[11],  840,  850, 100, _IMAGE_MAGIC,       _SKILL_SHIELD, 3, 4, 100, 100, 100, 100, 140, 180);	// �ּ��Ǹ�. // �Ⱦ�.
	SetEffectInfo(&m_stMagicSpr[12],  890,  900, 100, _IMAGE_MAGIC,       _SKILL_SHOWHP, 3, 4,  75,  75,  75, 100,  75,  50);	// Ž���Ŀ�.
	SetEffectInfo(&m_stMagicSpr[13],  920,  930, 120, _IMAGE_MAGIC,    _SKILL_EARTHFIRE, 4, 5,  40,  60,  80,  60,  80, 100);	// ������.
	SetEffectInfo(&m_stMagicSpr[14],  980,  983, 100, _IMAGE_MAGIC,    _SKILL_FIRECHARM, 2, 3, 100, 150, 200, 150, 200, 250, 255, 255, 255, _BLEND_NORMAL, 255);	// �����.
	SetEffectInfo(&m_stMagicSpr[15],  980,  983, 100, _IMAGE_MAGIC, _SKILL_HANGMAJINBUB, 2, 3, 150, 100,  50, 200, 150, 100, 255, 255, 255, _BLEND_NORMAL, 255);	// �׸�����.
	SetEffectInfo(&m_stMagicSpr[16],  980,  983, 100, _IMAGE_MAGIC,    _SKILL_DEJIWONHO, 2, 3, 150, 180, 200, 180, 200, 220, 255, 255, 255, _BLEND_NORMAL, 255);	// ������ȣ.
	SetEffectInfo(&m_stMagicSpr[17],  950,  970,  50, _IMAGE_MAGIC,     _SKILL_FIREBOOM, 5, 6, 100, 150, 200, 150, 200, 250);	// ������.
	SetEffectInfo(&m_stMagicSpr[18], 1640, 1646,  10, _IMAGE_MAGIC,    _SKILL_FIREBALL2, 2, 3, 100, 150, 200, 150, 200, 250);	// �ݰ�ȭ����.
//	SetEffectInfo(&m_stMagicSpr[19], 1450, 1455, 100, _IMAGE_MAGIC,   _SKILL_LIGHTENING, 5, 6, 250, 150, 150, 255, 200, 200);	// ����.
	SetEffectInfo(&m_stMagicSpr[19], 1450, 1455, 100, _IMAGE_MAGIC,   _SKILL_LIGHTENING, 20, 21, 255, 125, 50, 255, 255, 255);	// ����.
	SetEffectInfo(&m_stMagicSpr[20],  980,  983, 100, _IMAGE_MAGIC,     _SKILL_BIGCLOAK, 2, 3, 150, 150, 150, 200, 150, 180);	// ������.
	SetEffectInfo(&m_stMagicSpr[21],  110,  120, 100, _IMAGE_MAGIC,_SKILL_SPACEMOVESHOW, 3, 4, 100, 100, 100, 170, 100, 100);	// �ư������Ÿ����.

	//~~~ Monster Magic Frame Define. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	SetEffectInfo(&m_stMagicSpr[23],    0,    4, 100, _IMAGE_MONMAGIC,    _MONMAGIC_KEPAL, 2, 3, 100, 100, 100, 150, 150, 150);	
	SetEffectInfo(&m_stMagicSpr[24],  300,  320, 100, _IMAGE_MONMAGIC,  _MONMAGIC_EXPLODE, 2, 3, 100, 100,  50, 150, 150,  75);	
	SetEffectInfo(&m_stMagicSpr[25],   20,   30, 100, _IMAGE_MONMAGIC,   _MONMAGIC_BLACK1, 2, 3, 100, 100, 100, 150, 150, 150);	
	SetEffectInfo(&m_stMagicSpr[26],   40,   50, 100, _IMAGE_MONMAGIC,   _MONMAGIC_BLACK2, 2, 3, 100, 100, 100, 150, 150, 150);	
	SetEffectInfo(&m_stMagicSpr[27],   80,   86, 100, _IMAGE_MONMAGIC,  _MONMAGIC_ANTHEAL, 2, 3, 100, 100, 100, 150, 150, 150);	
	SetEffectInfo(&m_stMagicSpr[28],  200,  208, 100, _IMAGE_MONMAGIC, _MONMAGIC_GREATANT, 2, 3, 100, 100, 100, 150, 150, 150);	
	SetEffectInfo(&m_stMagicSpr[29],  280,  289, 100, _IMAGE_MONMAGIC,	   _MONMAGIC_RED1, 2, 3, 100, 100, 100, 150, 150, 150);	
	SetEffectInfo(&m_stMagicSpr[30],   40,   50, 100, _IMAGE_MONMAGIC,     _MONMAGIC_RED2, 2, 3, 100, 100, 100, 150, 150, 150);	
	SetEffectInfo(&m_stMagicSpr[31],  220,  227, 100, _IMAGE_MONMAGIC,      _MONMAGIC_ANT, 2, 3, 100, 100, 100, 150, 150, 150);	
	SetEffectInfo(&m_stMagicSpr[32],  240,  246, 100, _IMAGE_MONMAGIC,  _MONMAGIC_WORKANT, 2, 3, 100, 100, 100, 150, 150, 150);	
	SetEffectInfo(&m_stMagicSpr[33],  440,  446, 100, _IMAGE_MONMAGIC, _MONMAGIC_COWGHOST, 2, 3, 100, 100, 100, 150, 150, 150);	// ���Ϳ�.
	SetEffectInfo(&m_stMagicSpr[34],  980,  986, 100, _IMAGE_MONMAGIC,    _MONMAGIC_SINSU, 2, 3, 100, 100, 100, 150, 150, 150);	// �ż�.
	SetEffectInfo(&m_stMagicSpr[35],  600,  606, 100, _IMAGE_MONMAGIC,   _MONMAGIC_ZOMBIE, 2, 3, 100, 100, 100, 150, 150, 150);	// ����.
	SetEffectInfo(&m_stMagicSpr[36],  720,  728, 100, _IMAGE_MONMAGIC, _MONMAGIC_JUMAWANG, 2, 3, 100, 100, 100, 150, 150, 150);	// �ָ���.

	SetEffectInfo(&m_stMagicSpr[37], 1240, 1241, 100, _IMAGE_MONMAGIC,         _MONMAGIC_CHIM, 2, 3, 100, 100, 100, 150, 150, 150, 255, 255, 255, _BLEND_NORMAL, 255);	// ��ũħ.
	SetEffectInfo(&m_stMagicSpr[38], 1400, 1401, 100, _IMAGE_MONMAGIC,        _MONMAGIC_ARROW, 2, 3, 100, 100, 100, 150, 150, 150, 255, 255, 255, _BLEND_NORMAL, 255);	// �ü����ȭ��.
	SetEffectInfo(&m_stMagicSpr[39], 1070, 1071, 100, _IMAGE_MONMAGIC,      _MONMAGIC_MAARROW, 2, 3, 100, 100, 100, 150, 150, 150, 255, 255, 255, _BLEND_NORMAL, 255);	// ���û�ȭ��.
	SetEffectInfo(&m_stMagicSpr[40],  800,  806, 100, _IMAGE_MONMAGIC,      _MONMAGIC_DUALAXE, 2, 3, 100, 100, 100, 150, 150, 150, 255, 255, 255, _BLEND_NORMAL, 255);	// �ֵ����ذ������.
	SetEffectInfo(&m_stMagicSpr[41],  520,  527, 100, _IMAGE_MONMAGIC,     _MONMAGIC_COWFLAME, 2, 3, 100, 100, 100, 150, 150, 150);	// ȭ������.
	SetEffectInfo(&m_stMagicSpr[42],  360,  370, 100, _IMAGE_MONMAGIC,  _MONMAGIC_BIGGINE_ATT, 2, 3, 100, 100, 100, 150, 150, 150);	// �˷�� ����.
	SetEffectInfo(&m_stMagicSpr[43],  380,  400, 100, _IMAGE_MONMAGIC, _MONMAGIC_BIGGINE_CHAR, 2, 3, 100, 100, 100, 150, 150, 150);	// �˷�ſ� ���ݴ���.
	SetEffectInfo(&m_stMagicSpr[44],  320,  330,  70, _IMAGE_MONMAGIC,     _MONMAGIC_SANDFISH, 2, 3, 100, 100, 100, 150, 150, 150, 255, 255, 255, _BLEND_LIGHTINV, 255);		// ������.
	SetEffectInfo(&m_stMagicSpr[45],  260,  266, 100, _IMAGE_MONMAGIC,       _MONMAGIC_BAODIE, 2, 3, 100, 100, 100, 150, 150, 150);	// �ٿ��޵�����.
	SetEffectInfo(&m_stMagicSpr[46],  880,  886, 150, _IMAGE_MONMAGIC,        _MONMAGIC_SSEGI, 2, 3, 100, 100, 100, 150, 150, 150, 255, 255, 255, _BLEND_LIGHTINV, 15);		// ���⳪��Ÿ��.
	SetEffectInfo(&m_stMagicSpr[47],   60,   80, 100, _IMAGE_MONMAGIC,    _MONMAGIC_SINGI_DIE, 2, 3, 100, 100, 100, 150, 150, 150);	// �����ױ�. �氩�ʱ��, ȫ��, ���Ǹ�����. // ���ⱸ���� ����.
	SetEffectInfo(&m_stMagicSpr[48],  680,  689, 100, _IMAGE_MONMAGIC,     _MONMAGIC_HUSU_DIE, 2, 3, 100, 100, 100, 150, 150, 150);	// ����ƺ��ױ�.
	SetEffectInfo(&m_stMagicSpr[49],  700,  708, 100, _IMAGE_MONMAGIC,   _MONMAGIC_ZOMBIE_DIE, 2, 3, 100, 100, 100, 150, 150, 150);	// �����ױ�.

//	SetEffectInfo(&m_stMagicSpr[50],  980,  983, 10, _IMAGE_MAGIC,	_SKILL_SINSU, 3, 4, 150, 150, 150, 200, 150, 180, 255, 255, 255, _BLEND_NORMAL, 255);	// �ż�.
	SetEffectInfo(&m_stMagicSpr[50], 2590, 2609, 100, _IMAGE_MAGIC,	_SKILL_SINSU, 3, 4, 150, 150, 150, 200, 150, 180, 255, 255, 255, _BLEND_NORMAL, 255);	// �ż�. 

	SetEffectInfo(&m_stMagicSpr[51],  1770,  1790, 100, _IMAGE_MONMAGIC,  _MONMAGIC_EXPLODE1, 2, 3, 100, 100,  50, 150, 150,  75);	

	SetEffectInfo(&m_stMagicSpr[52],  2450,  2460, 150, _IMAGE_MAGIC,   _EVENT_LEFTFIRE1, 2, 3, 20, 30, 40, 50, 60, 70, 255, 255, 255, _BLEND_LIGHTINV);	// ���ܻ�1.
	SetEffectInfo(&m_stMagicSpr[53],  2460,  2470, 150, _IMAGE_MAGIC,   _EVENT_LEFTFIRE2, 2, 3, 20, 30, 40, 50, 60, 70, 255, 255, 255, _BLEND_LIGHTINV);	// ���ܻ�2.
	SetEffectInfo(&m_stMagicSpr[54],  2470,  2480, 150, _IMAGE_MAGIC,   _EVENT_LEFTFIRE3, 2, 3, 20, 30, 40, 50, 60, 70, 255, 255, 255, _BLEND_LIGHTINV);	// ���ܻ�3.
	SetEffectInfo(&m_stMagicSpr[55],  2480,  2490, 150, _IMAGE_MAGIC,   _EVENT_LEFTFIRE4, 2, 3, 20, 30, 40, 50, 60, 70, 255, 255, 255, _BLEND_LIGHTINV);	// ���ܻ�4.
	SetEffectInfo(&m_stMagicSpr[56],  2490,  2500, 150, _IMAGE_MAGIC,   _EVENT_LEFTFIRE5, 2, 3, 20, 30, 40, 50, 60, 70, 255, 255, 255, _BLEND_LIGHTINV);	// ���ܻ�5.

	SetEffectInfo(&m_stMagicSpr[57],  1890,  1908, 60, _IMAGE_MONMAGIC, _MONMAGIC_BOSSDIE, 3, 4, 100, 200, 100, 150, 250, 100, 255, 255, 255, _BLEND_NORMAL);	// ��õȲ����.

	SetEffectInfo(&m_stMagicSpr[58], 2700, 2703, 50, _IMAGE_MAGIC, _SKILL_ICEBOLT, 3, 4, 255, 123,   0, 255, 123,   0);			// ������.
	SetEffectInfo(&m_stMagicSpr[59], 2960, 2966, 20, _IMAGE_MAGIC, _SKILL_SUPERICEBOLT, 3, 4, 255, 123,   0, 255, 123,   0);	// ������õ��.
	SetEffectInfo(&m_stMagicSpr[60], 3070, 3076, 50, _IMAGE_MAGIC, _SKILL_MAGICARROW, 3, 4, 255, 123,   0, 255, 123,   0);		// �����.
	SetEffectInfo(&m_stMagicSpr[61], 3330, 3336, 50, _IMAGE_MAGIC, _SKILL_MOONOK, 3, 4, 255, 123,   0, 255, 123,   0);			// ������.
	SetEffectInfo(&m_stMagicSpr[62], 3440, 3446, 20, _IMAGE_MAGIC, _SKILL_MOONCHAM, 3, 4, 255, 123,   0, 255, 123,   0);		// ������.

	SetEffectInfo(&m_stMagicSpr[63], 3470,  3473, 100, _IMAGE_MAGIC, _EVENT_DUST, 2, 3, 50, 50, 50, 70, 70, 70, 255, 255, 255, _BLEND_LIGHTINV);	// ��Ķ�� ����.
	SetEffectInfo(&m_stMagicSpr[64], 2410, 2430, 50, _IMAGE_MAGIC,_SKILL_SPACEMOVEHIDE2, 3, 4, 100, 100, 100, 170, 100, 100);
	SetEffectInfo(&m_stMagicSpr[65], 2390, 2410, 50, _IMAGE_MAGIC,_SKILL_SPACEMOVESHOW2, 3, 4, 100, 100, 100, 170, 100, 100);

	SetEffectInfo(&m_stMagicSpr[66], 1920, 1930, 100, _IMAGE_MONMAGIC, _MONMAGIC_OMASKEL_DIE, 2, 3, 100, 100, 100, 150, 150, 150);	// �ذ���� �ױ�.
	SetEffectInfo(&m_stMagicSpr[67], 1940, 1945, 150, _IMAGE_MONMAGIC, _MONMAGIC_GUDEGI, 2, 3, 100, 100, 100, 150, 150, 150, 255, 255, 255, _BLEND_LIGHTINV, 15);	// ���������� ����ȿ��.
	SetEffectInfo(&m_stMagicSpr[68], 2030, 2035, 150, _IMAGE_MONMAGIC, _MONMAGIC_DUNG, 2, 3, 100, 100, 100, 150, 150, 150, 255, 255, 255, _BLEND_LIGHTINV, 15);		// �հ���ȿ��.

	SetEffectInfo(&m_stMagicSpr[69], 1450, 1455, 100, _IMAGE_MAGIC,  _MONMAGIC_LIGHTENING, 20, 21, 180, 180, 50, 200, 200, 200, 100, 255, 255);		// ���Ͱ���.
	SetEffectInfo(&m_stMagicSpr[70],  690,  701, 100, _IMAGE_MAGIC,  _MONMAGIC_LIGHTFLOWER, 5, 6, 180, 180, 50, 200, 200, 200, 100, 255, 255);		// ���ͷڼ�ȭ.	
	SetEffectInfo(&m_stMagicSpr[71], 2210, 2217,  80, _IMAGE_MONMAGIC,  _MONMAGIC_POKAN, 2, 3, 50, 180, 50, 150, 250, 150, 200, 200, 200);			// ���ְŹ� ������.	
	SetEffectInfo(&m_stMagicSpr[72], 2250, 2270,  50, _IMAGE_MONMAGIC,  _MONMAGIC_BIDOK, 2, 3, 50, 180, 50, 150, 250, 150, 200, 200, 200);			// ���� �ױ�.	
	SetEffectInfo(&m_stMagicSpr[73], 2230, 2236,  80, _IMAGE_MONMAGIC,  _MONMAGIC_REDMOON, 2, 3, 50, 180, 50, 150, 250, 150, 200, 200, 200, _BLEND_NORMAL, 255);			// ������.	
	SetEffectInfo(&m_stMagicSpr[74], 1570, 1580,  70, _IMAGE_MONMAGIC,  _MONMAGIC_WINDGOD, 2, 3, 50, 180, 50, 150, 250, 150, 255, 255, 255);		// ǳ��.	

	SetEffectInfo(&m_stMagicSpr[75], 3650, 3670,  50, _IMAGE_MAGIC, _SKILL_ICE, 3, 4,  150,  120, 90,  200, 150, 100, 200, 200, 200, _BLEND_NORMAL, 255);	// ������.
	
	//~~~ Explosion Frame Define. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	SetEffectInfo(&m_stExplosionSpr[0],  200,  220,  80, _IMAGE_MAGIC, _SKILL_HANGMAJINBUB, 4, 5, 250, 150, 100, 255, 210, 160, 255, 255, 255, _BLEND_LIGHTINV, 0, 1);// �׸�����.
	SetEffectInfo(&m_stExplosionSpr[1],  170,  190,  80, _IMAGE_MAGIC,    _SKILL_DEJIWONHO, 4, 5, 120, 170, 220, 160, 210, 255, 255, 255, 255, _BLEND_LIGHTINV, 0, 1);// ������ȣ.
	SetEffectInfo(&m_stExplosionSpr[2],  580,  590, 100, _IMAGE_MAGIC,     _SKILL_FIREBALL, 2, 3, 120, 170, 220, 160, 210, 255);	// ȭ����.
	SetEffectInfo(&m_stExplosionSpr[3], 1140, 1150, 100, _IMAGE_MAGIC,    _SKILL_FIRECHARM, 2, 3, 120, 170, 220, 160, 210, 255);	// �����.
	SetEffectInfo(&m_stExplosionSpr[4], 1800, 1810, 100, _IMAGE_MAGIC,    _SKILL_FIREBALL2, 2, 3, 120, 170, 220, 160, 210, 255);	// �ݰ�ȭ����.
	SetEffectInfo(&m_stExplosionSpr[5],  820,  830, 100, _IMAGE_MAGIC,     _SKILL_BIGCLOAK, 4, 5, 200, 210, 190, 200, 150, 180);	// ������.
	//~~~ Monster Explosion Frame Define. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	SetEffectInfo(&m_stExplosionSpr[6],  100,  110, 100, _IMAGE_MONMAGIC, _MONMAGIC_ANTHEAL, 2, 3, 100, 100, 100, 150, 150, 150);	// ���ⱸ���� ����.

	SetEffectInfo(&m_stExplosionSpr[7], 2590, 2609, 100, _IMAGE_MAGIC,	_SKILL_SINSU, 3, 4, 150, 150, 150, 200, 150, 180, 255, 255, 255, _BLEND_NORMAL);	// �ż�. // �Ⱦ�.
	SetEffectInfo(&m_stExplosionSpr[8], 2860, 2870, 100, _IMAGE_MAGIC, _SKILL_ICEBOLT, 3, 4, 255, 123,   0, 255, 123,   0);			// ������.
	SetEffectInfo(&m_stExplosionSpr[9], 2970, 2980, 100, _IMAGE_MAGIC, _SKILL_SUPERICEBOLT, 3, 4, 255, 123,   0, 255, 123,   0);	// ������õ��.
	SetEffectInfo(&m_stExplosionSpr[10], 3230, 3240, 100, _IMAGE_MAGIC, _SKILL_MAGICARROW, 3, 4, 255, 123,   0, 255, 123,   0);		// �����.
	SetEffectInfo(&m_stExplosionSpr[11], 3340, 3350, 100, _IMAGE_MAGIC, _SKILL_MOONOK, 3, 4, 255, 123,   0, 255, 123,   0);			// ������.
	SetEffectInfo(&m_stExplosionSpr[12], 3450, 3460, 100, _IMAGE_MAGIC, _SKILL_MOONCHAM, 3, 4, 255, 123,   0, 255, 123,   0);		// ������.
*/
}


VOID CSprite::SetNPCFrameInfo(WORD wNPCNum)
{
	// 0. NPC Mtn -> ����.
	switch ( wNPCNum )
	{
	case  51:	case  52:	case  53:	case  54:	case  55:	case 59:	case 64:  case 65: case 91: case 92: case 93:
		SetSprDfn(&m_stNPCSpr[0], 0,  1, 300);			// ���޵���.
		break;
	case  56:	case  57:
		SetSprDfn(&m_stNPCSpr[0], 0, 12,  80);			// Ư������1.
		break;
	case 19:   case  69:
		SetSprDfn(&m_stNPCSpr[0], 0,  4, 300);			// ���޵���.
		break;
	case  87:											// ���ƾ�
		SetSprDfn(&m_stNPCSpr[0], 0,  10, 150);			// ���޵���.
		break;
	default:
		SetSprDfn(&m_stNPCSpr[0], 0,  4, 300);			// ���޵���.
		break;
	}
	// 1. NPC Mtn -> Ư��1.
	switch ( wNPCNum )
	{
	case  27:
		SetSprDfn(&m_stNPCSpr[1], 30, 6, 300);			// Ư������1.
		break;
	case  28:
		SetSprDfn(&m_stNPCSpr[1], 30, 9, 300);			// Ư������1.
		break;
	case  51:	case  52:	case  53:	case  54:	case  55:	case  59:	case 64:  case 65: case 91: case 92:
		SetSprDfn(&m_stNPCSpr[1],  0, 1, 300);			// Ư������1.
		break; 
	case  56:	case  57:
		SetSprDfn(&m_stNPCSpr[1], 0, 12,  80);			// Ư������1.
		break;
	case 87:											//���ƾ�
		SetSprDfn(&m_stNPCSpr[1], 0, 10,  150);			// Ư������1.
		break;
	case 19:   case 88:    case 89:
		SetSprDfn(&m_stNPCSpr[1],  0,  4, 300);			// Ư������1.
		break;
	default:
		SetSprDfn(&m_stNPCSpr[1], 30, 10, 300);			// Ư������1.
		break;
	}

	// 2. NPC Mtn -> Ư��2.
	switch ( wNPCNum )
	{
	case  28:
		SetSprDfn(&m_stNPCSpr[2], 60,  6, 300);			// Ư������2.
		break;
	case  51:	case  52:	case  53:	case  54:	case  55:	case 59:  case 64:  case 65: case 91: case 92:
		SetSprDfn(&m_stNPCSpr[2],  0,  1, 300);			// Ư������2.
		break;
	case  56:	case  57:
		SetSprDfn(&m_stNPCSpr[2], 0,  12,  80);			// Ư������2.
		break;
	case 87:											//���ƾ�
		SetSprDfn(&m_stNPCSpr[2], 0, 10,  150);			// Ư������1.
		break;
	case 19:   case 88:    case 89:
		SetSprDfn(&m_stNPCSpr[2],  0,  4, 300);			// Ư������2.
		break;
	default:
		SetSprDfn(&m_stNPCSpr[2], 60,  6, 300);			// Ư������2.
		break;
	}
}


VOID CSprite::SetMonFrameInfo(WORD wMonNum)
{
/*	//~~~ Monster ��������Ʈ ����. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	SetSprDfn(&m_stMonSpr[0],    0,  4, 300);			// ���޵���.
	SetSprDfn(&m_stMonSpr[1],   80,  6, 130);			// �ȱ⵿��.
	SetSprDfn(&m_stMonSpr[2],  160,  6, 120);			// �Ϲݰ��ݵ���1.
	SetSprDfn(&m_stMonSpr[3],  240,  2, 300);			// �±⵿��.
	SetSprDfn(&m_stMonSpr[4],  320, 10, 150);			// �ױ⵿��.
	SetSprDfn(&m_stMonSpr[5],  400,  6, 150);			// �Ϲݰ��ݵ���2.
	SetSprDfn(&m_stMonSpr[6],  480, 10, 150);			// �������ݵ���1.
	SetSprDfn(&m_stMonSpr[7],  560, 10, 150);			// �������ݵ���2.
	SetSprDfn(&m_stMonSpr[8],  640,  6, 150);			// ��Ÿ����, �������.
	SetSprDfn(&m_stMonSpr[9],  720,  6, 150);			// Ư������1.
*/
	// 0. Monster Mtn -> ���޵���.
	switch ( wMonNum )
	{
	case 3: case 11: case 15: case 16:
		SetSprDfn(&m_stMonSpr[0],    0,  1, 250);
		break;
	case  0: case  1: case  2: case  4: case  6: case  7: case  8: case  9:
		SetSprDfn(&m_stMonSpr[0],    0,  4, 250);
		break;
	case 5:
		SetSprDfn(&m_stMonSpr[0],    0,  10, 130);
		break;
	case 39:
		SetSprDfn(&m_stMonSpr[0],    0,  8, 130);
		break;
	case 95:										// ���μ�.
		SetSprDfn(&m_stMonSpr[0],    0,  1, 250);		
		break;
	case  147:										// ������.
		SetSprDfn(&m_stMonSpr[0],	 0,  4, 150);
		break;
	case  145:										// �ٹ���1.
	case  146:										// �ٹ���2.
		SetSprDfn(&m_stMonSpr[0],    0,  4, 150);
		break;

//@@@@@@@@@@@@@@@@@@@@@@@@@@@���ڸ���Ʈ
	case 158:
		SetSprDfn(&m_stMonSpr[0],    0,  4, 200);
		break;
	case 161:	case 165:	case 166:
		SetSprDfn(&m_stMonSpr[0],    0,  4, 250);
		break;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@���ڸ���Ʈ

	case 530 :	// ��ϼ���1
	case 531 :	// ��ϼ���2
	case 532 :	// ��ϼ���3
	case 533 :	// ��ϼ���4
	case 538 :  // ���ƾ�
		SetSprDfn(&m_stMonSpr[0],    0,  1, 200);
		break;
	case 174 :	case 175 :  case 176 : case 178 :
		SetSprDfn(&m_stMonSpr[0],  720, 10, 120);
		break;

	case 212:										// ������
	case 213:										// ������2
		SetSprDfn(&m_stMonSpr[0],    0, 10, 120);
		break;


	default:
		SetSprDfn(&m_stMonSpr[0],    0,  4, 300);		
		break;
	}

	// 1. Monster Mtn -> �ȱ⵿��.
	switch ( wMonNum )
	{
	case 212:										// ������
	case 213:										// ������2
		SetSprDfn(&m_stMonSpr[1],    80,  10, 50);
		break;
	default:
		SetSprDfn(&m_stMonSpr[1],    80,  6, 90);
		break;
	}

	// 2. Monster Mtn -> �Ϲݰ��ݵ���1.
	switch ( wMonNum )
	{
	case  19:		case 203:								// ȫ�ǹ���, �Ѻ�������2
		SetSprDfn(&m_stMonSpr[2],  160, 6, 150);		
		break;
	case  0: case  1: case  2: case 12: case 99:
		SetSprDfn(&m_stMonSpr[2],  160,  6, 100);	// ����, �����, ���ȷ���, ��, �ٿ��޵�.
		break;
	case 14: case 16: case 92:
		SetSprDfn(&m_stMonSpr[2],  160,  6, 120);	// ���밳��, �峭����, �ٰ�.
		break;
	case  3: case  6: case  7: case  8: case  9: case 15: case 93: case 96: case 97: case 98:
		SetSprDfn(&m_stMonSpr[2],  160,  6, 140);	// �籫, ���ڿ�, ġ������, ���ְ���, ��, ������, ����������, ���簳��, ǳ��, ������1.
		break;
	case  4: case 10: case 11: case 13: case 17: case 18: case 94:	case 205:
		SetSprDfn(&m_stMonSpr[2],  160,  6, 150);	// ������, ȯ����, �����1, ��������, ��������, ����, ���, ȭ��
		break;
	case  33: case  46: case  82:
		SetSprDfn(&m_stMonSpr[2],  160,  6, 90);
		break;
	case  90:										// �ż� ������.
		SetSprDfn(&m_stMonSpr[2],  160,  6, 160);
		break;
	case  95:										// ���μ�.
		SetSprDfn(&m_stMonSpr[2],  160, 10, 90);
		break;
	case  120:										// ��õȲ.
		SetSprDfn(&m_stMonSpr[2],  160, 10, 90);
		break;
	case  186:										// Ÿ�簡
		SetSprDfn(&m_stMonSpr[2],  400, 8, 90);
		break;
	case  149:										// ġ��.
		SetSprDfn(&m_stMonSpr[2],  160,  6, 150);
		break;
	case  147:										// ������.
		SetSprDfn(&m_stMonSpr[2],  160,  6, 120);
		break;
	case  145:										// �ٹ���1.
	case  146:										// �ٹ���2.
		SetSprDfn(&m_stMonSpr[2],  160,  6, 150);
		break;

//@@@@@@@@@@@@@@@@@@@@@@@@@@@���ڸ���Ʈ
	case 164:										// ���ս�.
		SetSprDfn(&m_stMonSpr[2],  160,  9, 120);
		break;

	case 154:	case 155:	case 162:	case 163:	// ���ı�, ������, ���Ͽ���1, ���Ͽ���2
		SetSprDfn(&m_stMonSpr[2],  160,  6, 120);
		break;
	case 159:	case 160:	case 161:				// ȭ������, ��ȭ����, ���½���.
		SetSprDfn(&m_stMonSpr[2],  160,  6, 140);
		break;
	case 156:	case 157:	case 165:	case 166:	// ���ŵ�1, ���ŵ�2, ���1, ���2
		SetSprDfn(&m_stMonSpr[2],  160,  6, 150);
		break;
	case 167:   case 169:							// �߼���, ������
		SetSprDfn(&m_stMonSpr[2],  160,  10, 150);
		break;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@���ڸ���Ʈ
	case 212:										// ������1
		SetSprDfn(&m_stMonSpr[2],  160,  10, 150);
		break;
	case 213:										// ������2
		SetSprDfn(&m_stMonSpr[2],  160,  20, 90);
		break;
	case 192:	case 191:	case 193:	case 194:	case 195:	case 196:	case 199:	case 204:	case 207:	case 208:	case 171:
		//����, ��, ������, ��α�, ���ķ�, ��Ʒ�, ������, ���ɱ��,�����ΰ�, ���, �����
		SetSprDfn(&m_stMonSpr[2],  160,  6, 60);	
		break;

	default:
		SetSprDfn(&m_stMonSpr[2],  160,  6, 130);	
		break;
	}

	// 3. Monster Mtn -> �±⵿��.
	switch ( wMonNum )
	{
	case  0: 
		SetSprDfn(&m_stMonSpr[3],  0, 4, 250);	
		break;
	case 3: case 11: case 15: case 16:
		SetSprDfn(&m_stMonSpr[3],  240, 1, 250);	
		break;
	case  1: case  2: case  4: case  6: case  7: case  8: case  9:
		SetSprDfn(&m_stMonSpr[3],  240, 2, 180);	
		break;
	case 39:
		SetSprDfn(&m_stMonSpr[3],  240, 3, 150);	
		break;
	case  116:										// ��.
	case  117:										
	case  118:										
		SetSprDfn(&m_stMonSpr[3],  240, 3, 150);		
		break;
	case  149:										// ġ��.
		SetSprDfn(&m_stMonSpr[3],  240, 2, 300);
		break;
	case  147:										// ������.
		SetSprDfn(&m_stMonSpr[3],  240, 2, 150);
		break;
	case  145:										// �ٹ���1.
	case  146:										// �ٹ���2.
		SetSprDfn(&m_stMonSpr[3],  240, 2, 150);
		break;

//@@@@@@@@@@@@@@@@@@@@@@@@@@@���ڸ���Ʈ
	case 154:	case 155:	case 156:	case 157:	case 159:	case 160:	case 161:	case 162:	case 163:	case 164:
	SetSprDfn(&m_stMonSpr[3],  240, 2, 300);
		break;
	case  158:	case  165:	case  166:
		SetSprDfn(&m_stMonSpr[3],  240, 2, 200);
		break;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@���ڸ���Ʈ
	case 530 :	// ��ϼ���1
	case 531 :	// ��ϼ���2
	case 532 :	// ��ϼ���3
	case 533 :	// ��ϼ���4
	case 538 :	/*���ƾ�*/
		SetSprDfn(&m_stMonSpr[3],  240, 2, 200);
		break;
	case  212:										// ������
		SetSprDfn(&m_stMonSpr[3],  240, 4, 150);
		break;
	case  213:										// ������2
		SetSprDfn(&m_stMonSpr[3],  480, 4, 150);
		break;
	default:
		SetSprDfn(&m_stMonSpr[3],  240, 2, 180);
		break;
	}

	// 4. Monster Mtn -> �ױ⵿��.
	switch ( wMonNum )
	{
	case  3:										// ���
		SetSprDfn(&m_stMonSpr[4],  320, 6, 130);		
		break;
	case 39:										// �±ر�
		SetSprDfn(&m_stMonSpr[4],  320, 8, 130);		
		break;
	case  94:										// ���
		SetSprDfn(&m_stMonSpr[4],  320, 10, 130);		
		break;
	case  30:										// ����.
	case  37:										// ����������.
		SetSprDfn(&m_stMonSpr[4],  320, 4, 220);		
		break;
	case  104:										// ������.
		SetSprDfn(&m_stMonSpr[4],  320, 20, 120);		
		break;
	case  127:										// �㳪��.
	case  153:										// Ʈ��
	case 187:	case 188:	case 534:	case 535:	case 536:	case 537:	case 179:	case 189: // ���ƾ�.
		SetSprDfn(&m_stMonSpr[4],  320, 9, 120);		
		break;
	case  141:										// �ذ�����.
		SetSprDfn(&m_stMonSpr[4],  720, 20, 120);		
		break;
	case  149:										// ġ��.
		SetSprDfn(&m_stMonSpr[4],  320, 10, 120);
		break;
	case  147:										// ������.
		SetSprDfn(&m_stMonSpr[4],  320, 10, 95);
		break;
	case  145:										// �ٹ���1.
	case  146:										// �ٹ���2.
		SetSprDfn(&m_stMonSpr[4],  320, 10, 95); 
		break;
	case  8:										// ���ְ���
		SetSprDfn(&m_stMonSpr[4],  320, 10, 130);
		break;
	case  86:										// �ú�, �ü����
		SetSprDfn(&m_stMonSpr[4],  320, 10, 130);
		break;
	case 105:										// ����
		SetSprDfn(&m_stMonSpr[4],  320, 10, 130);
		break;

//@@@@@@@@@@@@@@@@@@@@@@@@@@@���ڸ���Ʈ
	case  154:	case  155:
		SetSprDfn(&m_stMonSpr[4],  320, 10, 95);
		break;
	case  156:	case  157:
		SetSprDfn(&m_stMonSpr[4],  320, 10, 145);
		break;
	case  158:	case  165:	case  166:
		SetSprDfn(&m_stMonSpr[4],  320, 10, 150);
		break;
	case  159:	case  160:	case  161:
		SetSprDfn(&m_stMonSpr[4],  320, 10, 110);
		break;
	case  162:	case  163:	case  164:
		SetSprDfn(&m_stMonSpr[4],  320, 10, 120);
		break;
	case 182: // ���ƾ� �Ʒ ����
		SetSprDfn(&m_stMonSpr[4],  320, 0, 120);
		break;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@���ڸ���Ʈ
	case 530 :	// ��ϼ���1
	case 531 :	// ��ϼ���2
	case 532 :	// ��ϼ���3
	case 533 :	// ��ϼ���4
	case 538 :  // ���ƾ�
		SetSprDfn(&m_stMonSpr[4],  320,  8, 120);
		break;
	case 213:										// ������2
		SetSprDfn(&m_stMonSpr[4],  560, 10, 120);
		break;

	default:
		SetSprDfn(&m_stMonSpr[4],  320, 10, 140);
		break;
	}

	// 5. Monster Mtn -> �Ϲݰ��ݵ���2.
	switch ( wMonNum )
	{
	case  0: case  1: case  2: case  3: case  4: case  6: case  7: case  8: case  9:
		SetSprDfn(&m_stMonSpr[5],  400,  6, 150);
		break;

//@@@@@@@@@@@@@@@@@@@@@@@@@@@���ڸ���Ʈ
	case 159:	case 160:							// ȭ������, ��ȭ����
		SetSprDfn(&m_stMonSpr[5],  400,  6, 140);
		break;
	case 164:										// ���ս�
		SetSprDfn(&m_stMonSpr[5],  400,  9, 120);
		break;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@���ڸ���Ʈ
	case  212:										// ������
		SetSprDfn(&m_stMonSpr[5],  160,  10, 150);
		break;
	case 213:										// ������2
		SetSprDfn(&m_stMonSpr[5],  320,  20, 70);
		break;
	case 211:										// ��������
		SetSprDfn(&m_stMonSpr[5],  400,  9, 120);
		break;
	default:
		SetSprDfn(&m_stMonSpr[5],  400,  6, 150);		
		break;
	}

	// 6. Monster Mtn -> �������ݵ���1.
	switch ( wMonNum )
	{
	case 10:	case 205:							// ȯ����, ȭ��
	case 172:
	case 181:										// ���ƾ�(npc 19����)
	case 203:
		SetSprDfn(&m_stMonSpr[6],  400, 6, 150);
		break;
	case 196:										// ��Ʒ�
		SetSprDfn(&m_stMonSpr[6],  480, 6, 60);		
		break;
	case  13:										// ��������
	case 170:										// ����ͳ�
		SetSprDfn(&m_stMonSpr[6],  480, 6, 150);		
		break;
	case  139:										// ��麻��
		SetSprDfn(&m_stMonSpr[6],  480, 6, 200);		
		break;
	case  141:										// �ذ�����
		SetSprDfn(&m_stMonSpr[6],  480, 6, 120);		
		break;

//@@@@@@@@@@@@@@@@@@@@@@@@@@@���ڸ���Ʈ
	case 161:										// ���½���
		SetSprDfn(&m_stMonSpr[6],  480, 6, 140);		
		break;
	case 158:										// ��ȯ��
		SetSprDfn(&m_stMonSpr[6],  480, 6, 200);
		break;
	case 204:										// ȭ��â�⺴
		SetSprDfn(&m_stMonSpr[6],  480, 6, 60);
		break;
	case 164:										// ���ս�
		SetSprDfn(&m_stMonSpr[6],  480, 8, 150);
		break;
	case 157:	case 202:							// ���ŵ�2, ��ȥ����1
		SetSprDfn(&m_stMonSpr[6],  480, 6, 150);
		break;
	case 195:										// ���ķ�
		SetSprDfn(&m_stMonSpr[6],  480, 6, 60);		
		break;
	case 185:										// ����ģ������
	case 182:										// �Ʒ
		SetSprDfn(&m_stMonSpr[6],  480, 6, 150);		
		break;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@���ڸ���Ʈ
	case 186:										// Ÿ�簡
		SetSprDfn(&m_stMonSpr[6],  480, 8, 150);		
		break;
	case 197:										// ��������
		SetSprDfn(&m_stMonSpr[6],  480, 8, 150);		
		break;
	default:
		SetSprDfn(&m_stMonSpr[6],  480, 10, 150);		
		break;
	}

	// 7. Monster Mtn -> �������ݵ���2.
	switch ( wMonNum )
	{
	case  0: case  1: case  2: case  3: case  4: case  6: case  7: case  8: case  9:
		SetSprDfn(&m_stMonSpr[7],  560, 10, 150);		
		break;
	case  141:										// �ذ�����
		SetSprDfn(&m_stMonSpr[7],  560, 6, 120);		
		break;
	default:
		SetSprDfn(&m_stMonSpr[7],  560, 10, 150);		
		break;
	}

	// 8. Monster Mtn -> �������, ��Ÿ���� ����.
	switch ( wMonNum )
	{
	case  0: case  1: case  2: case  3: case  4: case  6: case  7: case  8: case  9:
		SetSprDfn(&m_stMonSpr[8],  640,  10, 120);		
		break;
	case 90:	// �ż�������.
		SetSprDfn(&m_stMonSpr[8],  640,  10, 100);		
		break;
	case 83:	// �ָ�����.
		SetSprDfn(&m_stMonSpr[8],  640,  6, 120);		
		break;
	case 84:	// �ָ�ȣ��.
		SetSprDfn(&m_stMonSpr[8],  640,  6, 120);		
		break;
	case 85:	// �ָ���.
		SetSprDfn(&m_stMonSpr[8],  640,  20, 120);		
		break;
	case 530 :	// ��ϼ���1
	case 531 :	// ��ϼ���2
	case 532 :	// ��ϼ���3
	case 533 :	// ��ϼ���4
	case 538:   // ���ƾ�
		SetSprDfn(&m_stMonSpr[8],  640,   7, 120);		
		break;
	default:
		SetSprDfn(&m_stMonSpr[8],  640,  10, 120);		
		break;
	}

	// 9. Monster Mtn -> Ư������1.
	switch ( wMonNum )
	{
	default:
		SetSprDfn(&m_stMonSpr[9],  720,  6, 150);		
		break;
	}

	// 10. Monster Mtn -> �ذ�.
	switch ( wMonNum )
	{
	default:
		SetSprDfn(&m_stMonSpr[10],  880,  1, 500);		
		break;
	}
}


BYTE CSprite::GetWeaponMtn(BYTE nWeapon, BOOL bIsVertical)
{
	BYTE bMtn = _MT_ONEVSWING;

	switch ( nWeapon )
	{
	case 2: case 3:  case 6: case 16: case 17: case 19:			//â.
		bMtn = _MT_SPEARVSWING;
		break;
	case 4: case 5:  case 7: case 15:							//���Į.
		bMtn = _MT_TWOVSWING;
		break;
	}

	if ( bIsVertical == FALSE )
	{
		switch ( bMtn ) 
		{
		case _MT_ONEVSWING:
			bMtn = _MT_ONEHSWING;
			break;
		case _MT_SPEARVSWING:
			bMtn = _MT_SPEARHSWING;
			break;
		case _MT_TWOVSWING:
			bMtn = _MT_TWOHSWING;
			break;
		}
	}

	return bMtn;
}


BOOL CSprite::SetWeaponOrder(CHAR* szFileName)
{
	HANDLE	hFile;

	hFile = CreateFile(szFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if ( hFile != INVALID_HANDLE_VALUE )
	{
		DWORD		dwReadLen;
		ReadFile(hFile, &m_bWOrder, _MAX_HERO_REALFRAME, &dwReadLen, NULL);
		CloseHandle(hFile);
		return TRUE;
	}

	return FALSE;
}



BOOL CSprite::LoadMagicInfo()
{
	// ��ȣȭ ��ƾ����.
	char* pszBuf = NULL;

	crypto_seed s = {(char) 0xF0, (char) 0x39, (char) 0xAB, (char) 0x8E, 0x9FDE1A93};
	crypto::setSeed( &s );
	FILE *fp = fopen( "MInfo.Dat", "rb" );
	if ( !fp )
	{
		MessageBox(g_xMainWnd.GetSafehWnd(), (char*)"MInfo File Error.", "[Error] - Legend of Mir III", MB_ICONERROR);
		return FALSE;
	}

	int len = _filelength( _fileno( fp ) );
	pszBuf = new char[ len ];

	if ( !pszBuf )
	{
		fclose( fp );
		delete [] pszBuf;
		MessageBox(g_xMainWnd.GetSafehWnd(), (char*)"MInfo File Error", "[Error] - Legend of Mir III", MB_ICONERROR);
		return FALSE;
	}

	fread( pszBuf, 1, len, fp );
	fclose( fp );

	if ( !crypto::decrypt( (unsigned char *)pszBuf, len ) )
	{
		delete[] pszBuf;
		MessageBox(g_xMainWnd.GetSafehWnd(), (char*)"MInfo File Error.", "[Error] - Legend of Mir III", MB_ICONERROR);
		return FALSE;
	}

	SAFE_DELETEARR(m_pstEffectSpr);
	SAFE_DELETEARR(m_pstMagicSpr);
	SAFE_DELETEARR(m_pstExplosionSpr);

	// ����Ÿ����.
	char* pszSharp		= NULL;
	char* pszComment	= NULL;
	char* pszCheck		= NULL;
	char* pszValue		= NULL;

	EFFECTSPRINFO	stSprInfo;
	INT				nValue[24];
	INT*			pnCurrValue = NULL;

	INT   nStep			= -1;				// 0 : Spell, 1 : Magic, 2 : Explosion.
	INT	  nEffectCnt	= 0;
	INT   nArrayNum		= 0;

	BOOL  bIsInserting	= FALSE;

	char* pszLineNext	= NULL;
	char* pszLine		= pszBuf + 8;		// Seed�� �ǳʶڴ�.

	while ( pszLineNext = (char*)strchr(pszLine, '\r') )
	{
		*pszLineNext = '\0';
	
		if ( pszSharp = (char*)strchr(pszLine, '#') )
		{
			if ( pszCheck = (char*)strchr(pszSharp, ' ') )
			{
				*pszCheck = '\0';

				if ( !strcmp(pszSharp, "#SPELL") )
				{
					nStep	   = 0;
					nEffectCnt = atoi((char*)(pszCheck+1));
					SAFE_DELETEARR(m_pstEffectSpr);
					m_pstEffectSpr = new EFFECTSPRINFO[nEffectCnt];

					m_nEffectCnt    = nEffectCnt;

					ZeroMemory(m_pstEffectSpr, sizeof(EFFECTSPRINFO)*nEffectCnt);
				}
				else if ( !strcmp(pszSharp, "#MAGIC") )
				{
					nStep = 1;
					nEffectCnt = atoi((char*)(pszCheck+1));
					SAFE_DELETEARR(m_pstMagicSpr);
					m_pstMagicSpr = new EFFECTSPRINFO[nEffectCnt];

					m_nMagicCnt		= nEffectCnt;

					ZeroMemory(m_pstMagicSpr, sizeof(EFFECTSPRINFO)*nEffectCnt);
				}
				else if ( !strcmp(pszSharp, "#EXPLOSION") )
				{
					nStep = 2;
					nEffectCnt = atoi((char*)(pszCheck+1));
					SAFE_DELETEARR(m_pstExplosionSpr);
					m_pstExplosionSpr = new EFFECTSPRINFO[nEffectCnt];

					m_nExplosionCnt	= nEffectCnt;

					ZeroMemory(m_pstExplosionSpr, sizeof(EFFECTSPRINFO)*nEffectCnt);
				}
			}
		}
		else if ( !strcmp(pszLine, "{") )
		{
			if ( nStep != -1 )
			{
				bIsInserting = TRUE;
				nArrayNum	 = 0;
			}
			else
			{
				// Error.
				MessageBox(g_xMainWnd.GetSafehWnd(), (char*)"MInfo File Error.", "[Error] - Legend of Mir III", MB_ICONERROR);
			}
		}
		else if ( !strcmp(pszLine, "}") )
		{
			bIsInserting = FALSE;
			nStep		 = -1;
		}
		else if ( (char*)strchr(pszLine, '[') )
		{
			if ( bIsInserting && nStep != -1 )
			{
				if ( nArrayNum < nEffectCnt )
				{
					// Value Analysys.
					ZeroMemory(&stSprInfo, sizeof(EFFECTSPRINFO));
					ZeroMemory(&nValue, sizeof(INT)*24);
					pnCurrValue = nValue;

					pszValue = ++pszLine;

					while ( pszValue = (char*)strchr(pszLine, ',') )
					{
						*pszValue = '\0';

						//  ���� ������� �����Ѵ�.
						*pnCurrValue = atoi(pszLine);
						pnCurrValue++;


						pszLine = ++pszValue;
					}

					if ( pszValue = (char*)strchr(pszLine, ']') )
					{
						*pszValue = '\0';

						pszLine = ++pszValue;
					}
					else
					{
						// Error.
						MessageBox(g_xMainWnd.GetSafehWnd(), (char*)"MInfo File Error.", "[Error] - Legend of Mir III", MB_ICONERROR);
					}

					SetEffectInfo(&stSprInfo, (DWORD)nValue[0], (DWORD)nValue[1], (WORD)nValue[2], (WORD)nValue[3], (WORD)nValue[4],
											  (BYTE)nValue[5], (BYTE)nValue[6], 
											  (BYTE)nValue[7], (BYTE)nValue[8], (BYTE)nValue[9],
											  (BYTE)nValue[10], (BYTE)nValue[11], (BYTE)nValue[12], 
											  (BYTE)nValue[13], (BYTE)nValue[14], (BYTE)nValue[15], 
											  (BYTE)nValue[16], (BYTE)nValue[17], (BYTE)nValue[18]);

					switch ( nStep )
					{
						case 0:
						{
							m_pstEffectSpr[nArrayNum] = stSprInfo;
							break;
						}
						case 1:
						{
							m_pstMagicSpr[nArrayNum] = stSprInfo;
							break;
						}
						case 2:
						{
							m_pstExplosionSpr[nArrayNum] = stSprInfo;
							break;
						}
					}

					nArrayNum++;
				}
				else
				{
					// Error.
					MessageBox(g_xMainWnd.GetSafehWnd(), (char*)"MInfo File Error.", "[Error] - Legend of Mir III", MB_ICONERROR);
				}
			}
			else
			{
				// Error.
				MessageBox(g_xMainWnd.GetSafehWnd(), (char*)"MInfo File Error.", "[Error] - Legend of Mir III", MB_ICONERROR);
			}
		}

		// Comment.
		if ( pszComment = (char*)strchr(pszLine, '/') )
		{
			*pszComment = '\0';

		}

		pszLine = (pszLineNext+2);  // '\r''\n'
	}

	delete [] pszBuf;

	if ( nStep != -1 || bIsInserting )
	{
		// Error.
		MessageBox(g_xMainWnd.GetSafehWnd(), (char*)"MInfo File Error.", "[Error] - Legend of Mir III", MB_ICONERROR);
		return FALSE;
	}

	return TRUE;
}

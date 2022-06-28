/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/


#include "StdAfx.h"





/******************************************************************************************************************

	CSprite Class

*******************************************************************************************************************/
/******************************************************************************************************************

	함수명 : CSprite::CSprite()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
CSprite::CSprite()
{
	InitSpriteInfo();
}



/******************************************************************************************************************

	함수명 : CSprite::~CSprite()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
CSprite::~CSprite()
{
	DeleteSpriteInfo();
}



/******************************************************************************************************************

	함수명 : CSprite::InitSpriteInfo()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : VOID 

	[일자][수정자] : 수정내용

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

	함수명 : CSprite::DeleteSpriteInfo()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CSprite::DeleteSpriteInfo()
{
	SAFE_DELETEARR(m_pstEffectSpr);
	SAFE_DELETEARR(m_pstMagicSpr);
	SAFE_DELETEARR(m_pstExplosionSpr);
}
 


/******************************************************************************************************************

	함수명 : CSprite::SetEffectInfo()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : LPEFFECTSPRINFO pstEffect
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
	출력   : VOID 

	[일자][수정자] : 수정내용

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

	함수명 : CSprite::GetEffectInfo()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : WORD wEffectNum
	출력   : LPEFFECTSPRINFO 

	[일자][수정자] : 수정내용

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

	함수명 : CSprite::GetExplosionInfo()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : WORD wEffectNum
	출력   : LPEFFECTSPRINFO 

	[일자][수정자] : 수정내용

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

	함수명 : CSprite::GetMagicInfo()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : WORD wEffectNum
	출력   : LPEFFECTSPRINFO 

	[일자][수정자] : 수정내용

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

	함수명 : CSprite::SetSprDfn()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : LPSPRFRMDEF pstSprDfn
	         WORD wFstFrm
	         WORD wFrmCnt
	         WORD wDelay
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CSprite::SetSprDfn(LPSPRFRMDEF pstSprDfn, WORD wFstFrm, WORD wFrmCnt, WORD wDelay)
{
	pstSprDfn->wFstFrm	= wFstFrm;
	pstSprDfn->wFrmCnt	= wFrmCnt;
	pstSprDfn->wDelay	= wDelay;
}


/******************************************************************************************************************

	함수명 : CSprite::SetInfo()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CSprite::SetInfo()
{
	SetWeaponOrder("weapon.ord");

	//~~~ Hero 스프라이트 설정. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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

	//~~~ Monster 스프라이트 설정. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	SetSprDfn(&m_stMonSpr[0],     0,  4, 300);			// 유휴동작.
	SetSprDfn(&m_stMonSpr[1],    80,  6, 130);			// 걷기동작.
	SetSprDfn(&m_stMonSpr[2],   160,  6, 120);			// 일반공격동작.
	SetSprDfn(&m_stMonSpr[3],   240,  2, 300);			// 맞기동작.
	SetSprDfn(&m_stMonSpr[4],   320, 10, 150);			// 죽기동작.
	SetSprDfn(&m_stMonSpr[5],   400,  6, 150);			// 특수공격동작1.
	SetSprDfn(&m_stMonSpr[6],   480, 10, 150);			// 특수공격동작2.
	SetSprDfn(&m_stMonSpr[7],   560, 10, 150);			// 사라지기동작.
	SetSprDfn(&m_stMonSpr[8],   640,  6, 150);			// 특수동작.

	//~~~ NPC 스프라이트 설정. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	SetSprDfn(&m_stNPCSpr[0],     0,  4, 300);			// 유휴동작.
	SetSprDfn(&m_stNPCSpr[1],    30, 10, 300);			// 특수동작1.
	SetSprDfn(&m_stNPCSpr[2],    60,  6, 300);			// 특수동작2.

	return LoadMagicInfo();
/*	//~~~ Effect Frame Define. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	SetEffectInfo(&m_stEffectSpr[0],   230,  236, 100, _IMAGE_MAGIC,       _SKILL_BANWOL, 3, 4, 100, 100, 100, 100, 100, 170);	// 반월공격 12시.
	SetEffectInfo(&m_stEffectSpr[1],    60,   70, 100, _IMAGE_MAGIC,    _SKILL_AMYOUNSUL, 3, 4, 100, 100, 100, 100, 160, 100, 255, 255, 255, _BLEND_NORMAL);	// 암연술 시전.
	SetEffectInfo(&m_stEffectSpr[2],    90,   98, 100, _IMAGE_MAGIC,     _SKILL_FIREWIND, 3, 4, 100, 100, 100, 100, 140, 180);	// 화염풍.
	SetEffectInfo(&m_stEffectSpr[3],  1820, 1828, 100, _IMAGE_MAGIC,         _SKILL_FIRE, 3, 4, 100, 100, 100, 100, 140, 180);	// 염사장 시전.
	SetEffectInfo(&m_stEffectSpr[4],     0,    9, 100, _IMAGE_MAGIC,      _SKILL_TAMMING, 3, 4, 100, 100, 100, 170, 100, 100);	// 뢰혼격시전.
	SetEffectInfo(&m_stEffectSpr[5],  2360, 2370, 100, _IMAGE_MAGIC,    _SKILL_SPACEMOVE, 3, 4, 100, 100, 100, 170, 100, 100);	// 아공행법.
	SetEffectInfo(&m_stEffectSpr[6],   130,  140, 100, _IMAGE_MAGIC,   _SKILL_KILLUNDEAD, 3, 4, 100, 100, 100, 170, 100, 100);	// 사자윤회시전.
	SetEffectInfo(&m_stEffectSpr[7],  1820, 1828, 100, _IMAGE_MAGIC,     _SKILL_FIREBALL, 3, 4, 100, 100, 100, 100, 140, 180);	// 화염장.
	SetEffectInfo(&m_stEffectSpr[8],   600,  610, 100, _IMAGE_MAGIC,     _SKILL_HEALLING, 3, 4, 100, 100, 100, 140, 100, 120);	// 회복술.
	SetEffectInfo(&m_stEffectSpr[9],   630,  640, 100, _IMAGE_MAGIC,   _SKILL_HOLYSHIELD, 3, 4, 100, 100, 100, 170, 100, 100);	// 결계.
	SetEffectInfo(&m_stEffectSpr[10],  660,  670, 100, _IMAGE_MAGIC,  _SKILL_BIGHEALLING, 3, 4, 100, 100, 100, 140, 100, 120);	// 대회복.
	SetEffectInfo(&m_stEffectSpr[11],  690,  701, 100, _IMAGE_MAGIC,  _SKILL_LIGHTFLOWER, 3, 4, 150, 100,  50, 150, 100,  50);	// 뢰설화.	
	SetEffectInfo(&m_stEffectSpr[12], 1970, 1978,  80, _IMAGE_MAGIC, _SKILL_SHOOTLIGHTEN, 3, 4, 100, 100, 100, 170, 100, 100);	// 뢰인장.
	SetEffectInfo(&m_stEffectSpr[13],  740,  750, 100, _IMAGE_MAGIC,    _SKILL_SKELLETON, 3, 4, 100, 100, 100, 120, 100, 120);	// 백골소환술.
	SetEffectInfo(&m_stEffectSpr[14],  770,  780, 100, _IMAGE_MAGIC,     _SKILL_SNOWWIND, 3, 4, 100, 100, 100, 170, 100, 100);	// 빙설풍.
	SetEffectInfo(&m_stEffectSpr[15],  870,  890, 100, _IMAGE_MAGIC,       _SKILL_SHOWHP, 3, 4, 100, 100, 100, 100, 100, 170);	// 탐기파연.
	SetEffectInfo(&m_stEffectSpr[16],  910,  920, 100, _IMAGE_MAGIC,    _SKILL_EARTHFIRE, 3, 4, 100, 100, 100, 100, 140, 180);	// 지염술.
	SetEffectInfo(&m_stEffectSpr[17],  940,  950, 100, _IMAGE_MAGIC,     _SKILL_FIREBOOM, 3, 4, 100, 100, 100, 100, 140, 180);	// 폭열파.
	SetEffectInfo(&m_stEffectSpr[18], 1560, 1569, 100, _IMAGE_MAGIC,    _SKILL_FIREBALL2, 3, 4, 100, 100, 100, 100, 140, 180);	// 금강화염장.
	SetEffectInfo(&m_stEffectSpr[19],  320,  326, 100, _IMAGE_MAGIC,        _SKILL_ERGUM, 3, 4, 100, 100, 100, 100, 100, 170);	// 어검술.
	SetEffectInfo(&m_stEffectSpr[20], 1350, 1356, 100, _IMAGE_MAGIC,         _SKILL_YEDO, 3, 4, 100, 100, 100, 100, 100, 170);	// 예도검법.
	SetEffectInfo(&m_stEffectSpr[21], 1470, 1476, 100, _IMAGE_MAGIC,    _SKILL_FIRESWORD, 3, 4, 100, 100, 100, 100, 140, 180);	// 염화결.
	SetEffectInfo(&m_stEffectSpr[22], 1430, 1442, 100, _IMAGE_MAGIC,   _SKILL_LIGHTENING, 3, 4, 100, 100, 100, 170, 100, 100);	// 강격.
	SetEffectInfo(&m_stEffectSpr[23],  810,  820, 100, _IMAGE_MAGIC,        _SKILL_CLOAK, 3, 4, 150, 150, 150, 200, 150, 180);	// 은신.
	SetEffectInfo(&m_stEffectSpr[24], 2080, 2086, 100, _IMAGE_MAGIC, _SKILL_HANGMAJINBUB, 3, 4, 150, 100,  50, 200, 150, 100);	// 항마진법.
	SetEffectInfo(&m_stEffectSpr[25], 2080, 2086, 100, _IMAGE_MAGIC,    _SKILL_DEJIWONHO, 3, 4, 150, 180, 200, 180, 200, 220);	// 대지원호.
	SetEffectInfo(&m_stEffectSpr[26], 2080, 2086, 100, _IMAGE_MAGIC,    _SKILL_FIRECHARM, 3, 4, 100, 150, 200, 150, 200, 250);	// 폭살계.
	SetEffectInfo(&m_stEffectSpr[27], 2080, 2086, 100, _IMAGE_MAGIC,     _SKILL_BIGCLOAK, 3, 4, 150, 150, 150, 200, 150, 180);	// 대은신.
	SetEffectInfo(&m_stEffectSpr[28], 2180, 2190, 100, _IMAGE_MAGIC,     _SKILL_JUMPSHOT, 3, 4, 150, 150, 150, 200, 150, 180);	// 점프샷.
	SetEffectInfo(&m_stEffectSpr[29], 2270, 2280, 100, _IMAGE_MAGIC,    _SKILL_RANDSWING, 3, 4, 150, 150, 150, 200, 150, 180);	// 랜덤스윙.
	SetEffectInfo(&m_stEffectSpr[30], 2080, 2086, 100, _IMAGE_MAGIC,		_SKILL_SINSU, 3, 4, 150, 150, 150, 200, 150, 180, 255, 255, 255, _BLEND_NORMAL, 255);	// 신수소환.

	SetEffectInfo(&m_stEffectSpr[31], 1680, 1686, 100, _IMAGE_MONMAGIC, _MONMAGIC_NUMAGUMGI, 3, 4, 150, 150, 150, 200, 150, 180, 255, 255, 255, _BLEND_NORMAL, 255);// 누마왕 검기.
	SetEffectInfo(&m_stEffectSpr[32], 830, 849, 100, _IMAGE_MAGIC, _SKILL_SHIELD, 3, 4, 100, 100, 100, 170, 100, 100);			// 주술의막.

	SetEffectInfo(&m_stEffectSpr[33], 1800, 1810, 100, _IMAGE_MONMAGIC, _MONMAGIC_BOSSATT, 3, 4, 150, 100, 50, 200, 150, 100);	// 파천황공격.

	SetEffectInfo(&m_stEffectSpr[34], 2620, 2626, 100, _IMAGE_MAGIC, _SKILL_ICEBOLT, 3, 4, 100, 100, 100, 170, 100, 100);		// 빙월장.
	SetEffectInfo(&m_stEffectSpr[35], 2880, 2886, 100, _IMAGE_MAGIC, _SKILL_SUPERICEBOLT, 3, 4, 100, 100, 100, 170, 100, 100);	// 빙월진천장.
	SetEffectInfo(&m_stEffectSpr[36], 2990, 2996, 100, _IMAGE_MAGIC, _SKILL_MAGICARROW, 3, 4, 100, 100, 100, 170, 100, 100);	// 비격장.
	SetEffectInfo(&m_stEffectSpr[37], 3250, 3256, 100, _IMAGE_MAGIC, _SKILL_MOONOK, 3, 4, 100, 100, 100, 170, 100, 100);		// 월영옥.
	SetEffectInfo(&m_stEffectSpr[38], 3360, 3366, 100, _IMAGE_MAGIC, _SKILL_MOONCHAM, 3, 4, 100, 100, 100, 170, 100, 100);		// 월영참.

	SetEffectInfo(&m_stEffectSpr[39], 2120, 2126, 150, _IMAGE_MONMAGIC, _MONMAGIC_GUMGI, 2, 3, 100, 100, 100, 150, 150, 150);	// 신경비몬스터검기효과.

	SetEffectInfo(&m_stEffectSpr[40], 3560, 3570, 150, _IMAGE_MAGIC, _SKILL_ICE, 3, 4, 100, 100, 100, 200, 100, 100, 255, 255, 255, _BLEND_NORMAL);			// 빙사장.


	//~~~ Monster Effect Frame Define. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	//~~~ Magic Frame Define. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	SetEffectInfo(&m_stMagicSpr[0],    70,   88, 100, _IMAGE_MAGIC,    _SKILL_AMYOUNSUL, 3, 4, 190, 220, 190, 190, 240, 190, 255, 255, 255, _BLEND_NORMAL); // 암연술.
	SetEffectInfo(&m_stMagicSpr[1],  1900, 1960,  50, _IMAGE_MAGIC,         _SKILL_FIRE, 3, 4,  70,  90, 110,  90, 120, 150);	// 염사장.
	SetEffectInfo(&m_stMagicSpr[2],    10,   30,  50, _IMAGE_MAGIC,      _SKILL_TAMMING, 3, 4, 200, 100, 100, 250, 150, 150);	// 뢰혼격.
	SetEffectInfo(&m_stMagicSpr[3],   140,  159,  50, _IMAGE_MAGIC,   _SKILL_KILLUNDEAD, 3, 4, 200, 100, 100, 100,  75,  50);	// 사자윤회.
	SetEffectInfo(&m_stMagicSpr[4],   420,  425,  20, _IMAGE_MAGIC,     _SKILL_FIREBALL, 2, 3, 100, 150, 200, 150, 200, 250);	// 화염장.
	SetEffectInfo(&m_stMagicSpr[5],   610,  620, 100, _IMAGE_MAGIC,     _SKILL_HEALLING, 3, 4, 200, 140, 170, 230, 170, 200);	// 회복술.
	SetEffectInfo(&m_stMagicSpr[6],   640,  650, 100, _IMAGE_MAGIC,   _SKILL_HOLYSHIELD, 3, 4, 120,  60,  60, 150,  80,  80);	// 결계.
	SetEffectInfo(&m_stMagicSpr[7],   670,  680, 100, _IMAGE_MAGIC,  _SKILL_BIGHEALLING, 4, 5, 200, 140, 170, 230, 170, 200);//200, 100, 100, 250, 150, 150);	// 대회복.
	SetEffectInfo(&m_stMagicSpr[8],  2050, 2056,  80, _IMAGE_MAGIC, _SKILL_SHOOTLIGHTEN, 10, 11, 225, 50, 50, 255, 100, 100);	// 뢰인장.
	SetEffectInfo(&m_stMagicSpr[9],   750,  760, 155, _IMAGE_MAGIC,    _SKILL_SKELLETON, 3, 4, 150, 150, 150, 200, 150, 180);	// 백골소환술.
	SetEffectInfo(&m_stMagicSpr[10],  780,  800, 100, _IMAGE_MAGIC,     _SKILL_SNOWWIND, 5, 6, 255, 123,   0, 255, 123,   0, 255, 255, 255, _BLEND_LIGHTINV, 0, 1);	// 빙설풍.
//	SetEffectInfo(&m_stMagicSpr[10],  780,  800, 100, _IMAGE_MAGIC,     _SKILL_SNOWWIND, 4, 5, 220, 150, 150, 250, 170, 170);	// 빙설풍.
	SetEffectInfo(&m_stMagicSpr[11],  840,  850, 100, _IMAGE_MAGIC,       _SKILL_SHIELD, 3, 4, 100, 100, 100, 100, 140, 180);	// 주술의막. // 안씀.
	SetEffectInfo(&m_stMagicSpr[12],  890,  900, 100, _IMAGE_MAGIC,       _SKILL_SHOWHP, 3, 4,  75,  75,  75, 100,  75,  50);	// 탐기파연.
	SetEffectInfo(&m_stMagicSpr[13],  920,  930, 120, _IMAGE_MAGIC,    _SKILL_EARTHFIRE, 4, 5,  40,  60,  80,  60,  80, 100);	// 지염술.
	SetEffectInfo(&m_stMagicSpr[14],  980,  983, 100, _IMAGE_MAGIC,    _SKILL_FIRECHARM, 2, 3, 100, 150, 200, 150, 200, 250, 255, 255, 255, _BLEND_NORMAL, 255);	// 폭살계.
	SetEffectInfo(&m_stMagicSpr[15],  980,  983, 100, _IMAGE_MAGIC, _SKILL_HANGMAJINBUB, 2, 3, 150, 100,  50, 200, 150, 100, 255, 255, 255, _BLEND_NORMAL, 255);	// 항마진법.
	SetEffectInfo(&m_stMagicSpr[16],  980,  983, 100, _IMAGE_MAGIC,    _SKILL_DEJIWONHO, 2, 3, 150, 180, 200, 180, 200, 220, 255, 255, 255, _BLEND_NORMAL, 255);	// 대지원호.
	SetEffectInfo(&m_stMagicSpr[17],  950,  970,  50, _IMAGE_MAGIC,     _SKILL_FIREBOOM, 5, 6, 100, 150, 200, 150, 200, 250);	// 폭열파.
	SetEffectInfo(&m_stMagicSpr[18], 1640, 1646,  10, _IMAGE_MAGIC,    _SKILL_FIREBALL2, 2, 3, 100, 150, 200, 150, 200, 250);	// 금강화염장.
//	SetEffectInfo(&m_stMagicSpr[19], 1450, 1455, 100, _IMAGE_MAGIC,   _SKILL_LIGHTENING, 5, 6, 250, 150, 150, 255, 200, 200);	// 강격.
	SetEffectInfo(&m_stMagicSpr[19], 1450, 1455, 100, _IMAGE_MAGIC,   _SKILL_LIGHTENING, 20, 21, 255, 125, 50, 255, 255, 255);	// 강격.
	SetEffectInfo(&m_stMagicSpr[20],  980,  983, 100, _IMAGE_MAGIC,     _SKILL_BIGCLOAK, 2, 3, 150, 150, 150, 200, 150, 180);	// 대은신.
	SetEffectInfo(&m_stMagicSpr[21],  110,  120, 100, _IMAGE_MAGIC,_SKILL_SPACEMOVESHOW, 3, 4, 100, 100, 100, 170, 100, 100);	// 아공행법나타나기.

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
	SetEffectInfo(&m_stMagicSpr[33],  440,  446, 100, _IMAGE_MONMAGIC, _MONMAGIC_COWGHOST, 2, 3, 100, 100, 100, 150, 150, 150);	// 우면귀왕.
	SetEffectInfo(&m_stMagicSpr[34],  980,  986, 100, _IMAGE_MONMAGIC,    _MONMAGIC_SINSU, 2, 3, 100, 100, 100, 150, 150, 150);	// 신수.
	SetEffectInfo(&m_stMagicSpr[35],  600,  606, 100, _IMAGE_MONMAGIC,   _MONMAGIC_ZOMBIE, 2, 3, 100, 100, 100, 150, 150, 150);	// 좀비.
	SetEffectInfo(&m_stMagicSpr[36],  720,  728, 100, _IMAGE_MONMAGIC, _MONMAGIC_JUMAWANG, 2, 3, 100, 100, 100, 150, 150, 150);	// 주마왕.

	SetEffectInfo(&m_stMagicSpr[37], 1240, 1241, 100, _IMAGE_MONMAGIC,         _MONMAGIC_CHIM, 2, 3, 100, 100, 100, 150, 150, 150, 255, 255, 255, _BLEND_NORMAL, 255);	// 다크침.
	SetEffectInfo(&m_stMagicSpr[38], 1400, 1401, 100, _IMAGE_MONMAGIC,        _MONMAGIC_ARROW, 2, 3, 100, 100, 100, 150, 150, 150, 255, 255, 255, _BLEND_NORMAL, 255);	// 궁수경비화살.
	SetEffectInfo(&m_stMagicSpr[39], 1070, 1071, 100, _IMAGE_MONMAGIC,      _MONMAGIC_MAARROW, 2, 3, 100, 100, 100, 150, 150, 150, 255, 255, 255, _BLEND_NORMAL, 255);	// 마궁사화살.
	SetEffectInfo(&m_stMagicSpr[40],  800,  806, 100, _IMAGE_MONMAGIC,      _MONMAGIC_DUALAXE, 2, 3, 100, 100, 100, 150, 150, 150, 255, 255, 255, _BLEND_NORMAL, 255);	// 쌍도끼해골던지기.
	SetEffectInfo(&m_stMagicSpr[41],  520,  527, 100, _IMAGE_MONMAGIC,     _MONMAGIC_COWFLAME, 2, 3, 100, 100, 100, 150, 150, 150);	// 화염우면귀.
	SetEffectInfo(&m_stMagicSpr[42],  360,  370, 100, _IMAGE_MONMAGIC,  _MONMAGIC_BIGGINE_ATT, 2, 3, 100, 100, 100, 150, 150, 150);	// 촉룡신 공격.
	SetEffectInfo(&m_stMagicSpr[43],  380,  400, 100, _IMAGE_MONMAGIC, _MONMAGIC_BIGGINE_CHAR, 2, 3, 100, 100, 100, 150, 150, 150);	// 촉룡신에 공격당함.
	SetEffectInfo(&m_stMagicSpr[44],  320,  330,  70, _IMAGE_MONMAGIC,     _MONMAGIC_SANDFISH, 2, 3, 100, 100, 100, 150, 150, 150, 255, 255, 255, _BLEND_LIGHTINV, 255);		// 사어공격.
	SetEffectInfo(&m_stMagicSpr[45],  260,  266, 100, _IMAGE_MONMAGIC,       _MONMAGIC_BAODIE, 2, 3, 100, 100, 100, 150, 150, 150);	// 바오달드죽음.
	SetEffectInfo(&m_stMagicSpr[46],  880,  886, 150, _IMAGE_MONMAGIC,        _MONMAGIC_SSEGI, 2, 3, 100, 100, 100, 150, 150, 150, 255, 255, 255, _BLEND_LIGHTINV, 15);		// 쐐기나방타액.
	SetEffectInfo(&m_stMagicSpr[47],   60,   80, 100, _IMAGE_MONMAGIC,    _MONMAGIC_SINGI_DIE, 2, 3, 100, 100, 100, 150, 150, 150);	// 몬스터죽기. 경갑옷기사, 홍의, 흑의마법사. // 방향구별은 없다.
	SetEffectInfo(&m_stMagicSpr[48],  680,  689, 100, _IMAGE_MONMAGIC,     _MONMAGIC_HUSU_DIE, 2, 3, 100, 100, 100, 150, 150, 150);	// 허수아비죽기.
	SetEffectInfo(&m_stMagicSpr[49],  700,  708, 100, _IMAGE_MONMAGIC,   _MONMAGIC_ZOMBIE_DIE, 2, 3, 100, 100, 100, 150, 150, 150);	// 좀비죽기.

//	SetEffectInfo(&m_stMagicSpr[50],  980,  983, 10, _IMAGE_MAGIC,	_SKILL_SINSU, 3, 4, 150, 150, 150, 200, 150, 180, 255, 255, 255, _BLEND_NORMAL, 255);	// 신수.
	SetEffectInfo(&m_stMagicSpr[50], 2590, 2609, 100, _IMAGE_MAGIC,	_SKILL_SINSU, 3, 4, 150, 150, 150, 200, 150, 180, 255, 255, 255, _BLEND_NORMAL, 255);	// 신수. 

	SetEffectInfo(&m_stMagicSpr[51],  1770,  1790, 100, _IMAGE_MONMAGIC,  _MONMAGIC_EXPLODE1, 2, 3, 100, 100,  50, 150, 150,  75);	

	SetEffectInfo(&m_stMagicSpr[52],  2450,  2460, 150, _IMAGE_MAGIC,   _EVENT_LEFTFIRE1, 2, 3, 20, 30, 40, 50, 60, 70, 255, 255, 255, _BLEND_LIGHTINV);	// 불잔상1.
	SetEffectInfo(&m_stMagicSpr[53],  2460,  2470, 150, _IMAGE_MAGIC,   _EVENT_LEFTFIRE2, 2, 3, 20, 30, 40, 50, 60, 70, 255, 255, 255, _BLEND_LIGHTINV);	// 불잔상2.
	SetEffectInfo(&m_stMagicSpr[54],  2470,  2480, 150, _IMAGE_MAGIC,   _EVENT_LEFTFIRE3, 2, 3, 20, 30, 40, 50, 60, 70, 255, 255, 255, _BLEND_LIGHTINV);	// 불잔상3.
	SetEffectInfo(&m_stMagicSpr[55],  2480,  2490, 150, _IMAGE_MAGIC,   _EVENT_LEFTFIRE4, 2, 3, 20, 30, 40, 50, 60, 70, 255, 255, 255, _BLEND_LIGHTINV);	// 불잔상4.
	SetEffectInfo(&m_stMagicSpr[56],  2490,  2500, 150, _IMAGE_MAGIC,   _EVENT_LEFTFIRE5, 2, 3, 20, 30, 40, 50, 60, 70, 255, 255, 255, _BLEND_LIGHTINV);	// 불잔상5.

	SetEffectInfo(&m_stMagicSpr[57],  1890,  1908, 60, _IMAGE_MONMAGIC, _MONMAGIC_BOSSDIE, 3, 4, 100, 200, 100, 150, 250, 100, 255, 255, 255, _BLEND_NORMAL);	// 파천황죽음.

	SetEffectInfo(&m_stMagicSpr[58], 2700, 2703, 50, _IMAGE_MAGIC, _SKILL_ICEBOLT, 3, 4, 255, 123,   0, 255, 123,   0);			// 빙월장.
	SetEffectInfo(&m_stMagicSpr[59], 2960, 2966, 20, _IMAGE_MAGIC, _SKILL_SUPERICEBOLT, 3, 4, 255, 123,   0, 255, 123,   0);	// 빙월진천장.
	SetEffectInfo(&m_stMagicSpr[60], 3070, 3076, 50, _IMAGE_MAGIC, _SKILL_MAGICARROW, 3, 4, 255, 123,   0, 255, 123,   0);		// 비격장.
	SetEffectInfo(&m_stMagicSpr[61], 3330, 3336, 50, _IMAGE_MAGIC, _SKILL_MOONOK, 3, 4, 255, 123,   0, 255, 123,   0);			// 월영옥.
	SetEffectInfo(&m_stMagicSpr[62], 3440, 3446, 20, _IMAGE_MAGIC, _SKILL_MOONCHAM, 3, 4, 255, 123,   0, 255, 123,   0);		// 월영참.

	SetEffectInfo(&m_stMagicSpr[63], 3470,  3473, 100, _IMAGE_MAGIC, _EVENT_DUST, 2, 3, 50, 50, 50, 70, 70, 70, 255, 255, 255, _BLEND_LIGHTINV);	// 광캘때 먼지.
	SetEffectInfo(&m_stMagicSpr[64], 2410, 2430, 50, _IMAGE_MAGIC,_SKILL_SPACEMOVEHIDE2, 3, 4, 100, 100, 100, 170, 100, 100);
	SetEffectInfo(&m_stMagicSpr[65], 2390, 2410, 50, _IMAGE_MAGIC,_SKILL_SPACEMOVESHOW2, 3, 4, 100, 100, 100, 170, 100, 100);

	SetEffectInfo(&m_stMagicSpr[66], 1920, 1930, 100, _IMAGE_MONMAGIC, _MONMAGIC_OMASKEL_DIE, 2, 3, 100, 100, 100, 150, 150, 150);	// 해골류들 죽기.
	SetEffectInfo(&m_stMagicSpr[67], 1940, 1945, 150, _IMAGE_MONMAGIC, _MONMAGIC_GUDEGI, 2, 3, 100, 100, 100, 150, 150, 150, 255, 255, 255, _BLEND_LIGHTINV, 15);	// 동굴구더기 가스효과.
	SetEffectInfo(&m_stMagicSpr[68], 2030, 2035, 150, _IMAGE_MONMAGIC, _MONMAGIC_DUNG, 2, 3, 100, 100, 100, 150, 150, 150, 255, 255, 255, _BLEND_LIGHTINV, 15);		// 둥가스효과.

	SetEffectInfo(&m_stMagicSpr[69], 1450, 1455, 100, _IMAGE_MAGIC,  _MONMAGIC_LIGHTENING, 20, 21, 180, 180, 50, 200, 200, 200, 100, 255, 255);		// 몬스터강격.
	SetEffectInfo(&m_stMagicSpr[70],  690,  701, 100, _IMAGE_MAGIC,  _MONMAGIC_LIGHTFLOWER, 5, 6, 180, 180, 50, 200, 200, 200, 100, 255, 255);		// 몬스터뢰설화.	
	SetEffectInfo(&m_stMagicSpr[71], 2210, 2217,  80, _IMAGE_MONMAGIC,  _MONMAGIC_POKAN, 2, 3, 50, 180, 50, 150, 250, 150, 200, 200, 200);			// 폭주거미 터지기.	
	SetEffectInfo(&m_stMagicSpr[72], 2250, 2270,  50, _IMAGE_MONMAGIC,  _MONMAGIC_BIDOK, 2, 3, 50, 180, 50, 150, 250, 150, 200, 200, 200);			// 비독주 죽기.	
	SetEffectInfo(&m_stMagicSpr[73], 2230, 2236,  80, _IMAGE_MONMAGIC,  _MONMAGIC_REDMOON, 2, 3, 50, 180, 50, 150, 250, 150, 200, 200, 200, _BLEND_NORMAL, 255);			// 적월마.	
	SetEffectInfo(&m_stMagicSpr[74], 1570, 1580,  70, _IMAGE_MONMAGIC,  _MONMAGIC_WINDGOD, 2, 3, 50, 180, 50, 150, 250, 150, 255, 255, 255);		// 풍백.	

	SetEffectInfo(&m_stMagicSpr[75], 3650, 3670,  50, _IMAGE_MAGIC, _SKILL_ICE, 3, 4,  150,  120, 90,  200, 150, 100, 200, 200, 200, _BLEND_NORMAL, 255);	// 빙사장.
	
	//~~~ Explosion Frame Define. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	SetEffectInfo(&m_stExplosionSpr[0],  200,  220,  80, _IMAGE_MAGIC, _SKILL_HANGMAJINBUB, 4, 5, 250, 150, 100, 255, 210, 160, 255, 255, 255, _BLEND_LIGHTINV, 0, 1);// 항마진법.
	SetEffectInfo(&m_stExplosionSpr[1],  170,  190,  80, _IMAGE_MAGIC,    _SKILL_DEJIWONHO, 4, 5, 120, 170, 220, 160, 210, 255, 255, 255, 255, _BLEND_LIGHTINV, 0, 1);// 대지원호.
	SetEffectInfo(&m_stExplosionSpr[2],  580,  590, 100, _IMAGE_MAGIC,     _SKILL_FIREBALL, 2, 3, 120, 170, 220, 160, 210, 255);	// 화염장.
	SetEffectInfo(&m_stExplosionSpr[3], 1140, 1150, 100, _IMAGE_MAGIC,    _SKILL_FIRECHARM, 2, 3, 120, 170, 220, 160, 210, 255);	// 폭살계.
	SetEffectInfo(&m_stExplosionSpr[4], 1800, 1810, 100, _IMAGE_MAGIC,    _SKILL_FIREBALL2, 2, 3, 120, 170, 220, 160, 210, 255);	// 금강화염장.
	SetEffectInfo(&m_stExplosionSpr[5],  820,  830, 100, _IMAGE_MAGIC,     _SKILL_BIGCLOAK, 4, 5, 200, 210, 190, 200, 150, 180);	// 대은신.
	//~~~ Monster Explosion Frame Define. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	SetEffectInfo(&m_stExplosionSpr[6],  100,  110, 100, _IMAGE_MONMAGIC, _MONMAGIC_ANTHEAL, 2, 3, 100, 100, 100, 150, 150, 150);	// 방향구별은 없다.

	SetEffectInfo(&m_stExplosionSpr[7], 2590, 2609, 100, _IMAGE_MAGIC,	_SKILL_SINSU, 3, 4, 150, 150, 150, 200, 150, 180, 255, 255, 255, _BLEND_NORMAL);	// 신수. // 안씀.
	SetEffectInfo(&m_stExplosionSpr[8], 2860, 2870, 100, _IMAGE_MAGIC, _SKILL_ICEBOLT, 3, 4, 255, 123,   0, 255, 123,   0);			// 빙월장.
	SetEffectInfo(&m_stExplosionSpr[9], 2970, 2980, 100, _IMAGE_MAGIC, _SKILL_SUPERICEBOLT, 3, 4, 255, 123,   0, 255, 123,   0);	// 빙월진천장.
	SetEffectInfo(&m_stExplosionSpr[10], 3230, 3240, 100, _IMAGE_MAGIC, _SKILL_MAGICARROW, 3, 4, 255, 123,   0, 255, 123,   0);		// 비격장.
	SetEffectInfo(&m_stExplosionSpr[11], 3340, 3350, 100, _IMAGE_MAGIC, _SKILL_MOONOK, 3, 4, 255, 123,   0, 255, 123,   0);			// 월영옥.
	SetEffectInfo(&m_stExplosionSpr[12], 3450, 3460, 100, _IMAGE_MAGIC, _SKILL_MOONCHAM, 3, 4, 255, 123,   0, 255, 123,   0);		// 월영참.
*/
}


VOID CSprite::SetNPCFrameInfo(WORD wNPCNum)
{
	// 0. NPC Mtn -> 유휴.
	switch ( wNPCNum )
	{
	case  51:	case  52:	case  53:	case  54:	case  55:	case 59:	case 64:  case 65: case 91: case 92: case 93:
		SetSprDfn(&m_stNPCSpr[0], 0,  1, 300);			// 유휴동작.
		break;
	case  56:	case  57:
		SetSprDfn(&m_stNPCSpr[0], 0, 12,  80);			// 특수동작1.
		break;
	case 19:   case  69:
		SetSprDfn(&m_stNPCSpr[0], 0,  4, 300);			// 유휴동작.
		break;
	case  87:											// 성훈씨
		SetSprDfn(&m_stNPCSpr[0], 0,  10, 150);			// 유휴동작.
		break;
	default:
		SetSprDfn(&m_stNPCSpr[0], 0,  4, 300);			// 유휴동작.
		break;
	}
	// 1. NPC Mtn -> 특수1.
	switch ( wNPCNum )
	{
	case  27:
		SetSprDfn(&m_stNPCSpr[1], 30, 6, 300);			// 특수동작1.
		break;
	case  28:
		SetSprDfn(&m_stNPCSpr[1], 30, 9, 300);			// 특수동작1.
		break;
	case  51:	case  52:	case  53:	case  54:	case  55:	case  59:	case 64:  case 65: case 91: case 92:
		SetSprDfn(&m_stNPCSpr[1],  0, 1, 300);			// 특수동작1.
		break; 
	case  56:	case  57:
		SetSprDfn(&m_stNPCSpr[1], 0, 12,  80);			// 특수동작1.
		break;
	case 87:											//성훈씨
		SetSprDfn(&m_stNPCSpr[1], 0, 10,  150);			// 특수동작1.
		break;
	case 19:   case 88:    case 89:
		SetSprDfn(&m_stNPCSpr[1],  0,  4, 300);			// 특수동작1.
		break;
	default:
		SetSprDfn(&m_stNPCSpr[1], 30, 10, 300);			// 특수동작1.
		break;
	}

	// 2. NPC Mtn -> 특수2.
	switch ( wNPCNum )
	{
	case  28:
		SetSprDfn(&m_stNPCSpr[2], 60,  6, 300);			// 특수동작2.
		break;
	case  51:	case  52:	case  53:	case  54:	case  55:	case 59:  case 64:  case 65: case 91: case 92:
		SetSprDfn(&m_stNPCSpr[2],  0,  1, 300);			// 특수동작2.
		break;
	case  56:	case  57:
		SetSprDfn(&m_stNPCSpr[2], 0,  12,  80);			// 특수동작2.
		break;
	case 87:											//성훈씨
		SetSprDfn(&m_stNPCSpr[2], 0, 10,  150);			// 특수동작1.
		break;
	case 19:   case 88:    case 89:
		SetSprDfn(&m_stNPCSpr[2],  0,  4, 300);			// 특수동작2.
		break;
	default:
		SetSprDfn(&m_stNPCSpr[2], 60,  6, 300);			// 특수동작2.
		break;
	}
}


VOID CSprite::SetMonFrameInfo(WORD wMonNum)
{
/*	//~~~ Monster 스프라이트 설정. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	SetSprDfn(&m_stMonSpr[0],    0,  4, 300);			// 유휴동작.
	SetSprDfn(&m_stMonSpr[1],   80,  6, 130);			// 걷기동작.
	SetSprDfn(&m_stMonSpr[2],  160,  6, 120);			// 일반공격동작1.
	SetSprDfn(&m_stMonSpr[3],  240,  2, 300);			// 맞기동작.
	SetSprDfn(&m_stMonSpr[4],  320, 10, 150);			// 죽기동작.
	SetSprDfn(&m_stMonSpr[5],  400,  6, 150);			// 일반공격동작2.
	SetSprDfn(&m_stMonSpr[6],  480, 10, 150);			// 마법공격동작1.
	SetSprDfn(&m_stMonSpr[7],  560, 10, 150);			// 마법공격동작2.
	SetSprDfn(&m_stMonSpr[8],  640,  6, 150);			// 나타나기, 사라지기.
	SetSprDfn(&m_stMonSpr[9],  720,  6, 150);			// 특수동작1.
*/
	// 0. Monster Mtn -> 유휴동작.
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
	case 95:										// 형인수.
		SetSprDfn(&m_stMonSpr[0],    0,  1, 250);		
		break;
	case  147:										// 포안충.
		SetSprDfn(&m_stMonSpr[0],	 0,  4, 150);
		break;
	case  145:										// 다발충1.
	case  146:										// 다발충2.
		SetSprDfn(&m_stMonSpr[0],    0,  4, 150);
		break;

//@@@@@@@@@@@@@@@@@@@@@@@@@@@앙코르와트
	case 158:
		SetSprDfn(&m_stMonSpr[0],    0,  4, 200);
		break;
	case 161:	case 165:	case 166:
		SetSprDfn(&m_stMonSpr[0],    0,  4, 250);
		break;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@앙코르와트

	case 530 :	// 사북성문1
	case 531 :	// 사북성문2
	case 532 :	// 사북성문3
	case 533 :	// 사북성문4
	case 538 :  // 성훈씨
		SetSprDfn(&m_stMonSpr[0],    0,  1, 200);
		break;
	case 174 :	case 175 :  case 176 : case 178 :
		SetSprDfn(&m_stMonSpr[0],  720, 10, 120);
		break;

	case 212:										// 가무녀
	case 213:										// 가무녀2
		SetSprDfn(&m_stMonSpr[0],    0, 10, 120);
		break;


	default:
		SetSprDfn(&m_stMonSpr[0],    0,  4, 300);		
		break;
	}

	// 1. Monster Mtn -> 걷기동작.
	switch ( wMonNum )
	{
	case 212:										// 가무녀
	case 213:										// 가무녀2
		SetSprDfn(&m_stMonSpr[1],    80,  10, 50);
		break;
	default:
		SetSprDfn(&m_stMonSpr[1],    80,  6, 90);
		break;
	}

	// 2. Monster Mtn -> 일반공격동작1.
	switch ( wMonNum )
	{
	case  19:		case 203:								// 홍의법사, 한빙마전사2
		SetSprDfn(&m_stMonSpr[2],  160, 6, 150);		
		break;
	case  0: case  1: case  2: case 12: case 99:
		SetSprDfn(&m_stMonSpr[2],  160,  6, 100);	// 저파, 야행귀, 케팔로프, 견, 바오달드.
		break;
	case 14: case 16: case 92:
		SetSprDfn(&m_stMonSpr[2],  160,  6, 120);	// 병용개미, 드난개미, 다곤.
		break;
	case  3: case  6: case  7: case  8: case  9: case 15: case 93: case 96: case 97: case 98:
		SetSprDfn(&m_stMonSpr[2],  160,  6, 140);	// 사괴, 바자울, 치유개미, 갑주개미, 론, 누마왕, 데나가다코, 포루개미, 풍백, 누마왕1.
		break;
	case  4: case 10: case 11: case 13: case 17: case 18: case 94:	case 205:
		SetSprDfn(&m_stMonSpr[2],  160,  6, 150);	// 석장인, 환마군, 모디젼1, 누마법로, 누마비장, 누마, 사어, 화영
		break;
	case  33: case  46: case  82:
		SetSprDfn(&m_stMonSpr[2],  160,  6, 90);
		break;
	case  90:										// 신수 변신후.
		SetSprDfn(&m_stMonSpr[2],  160,  6, 160);
		break;
	case  95:										// 형인수.
		SetSprDfn(&m_stMonSpr[2],  160, 10, 90);
		break;
	case  120:										// 파천황.
		SetSprDfn(&m_stMonSpr[2],  160, 10, 90);
		break;
	case  186:										// 타당가
		SetSprDfn(&m_stMonSpr[2],  400, 8, 90);
		break;
	case  149:										// 치충.
		SetSprDfn(&m_stMonSpr[2],  160,  6, 150);
		break;
	case  147:										// 포안충.
		SetSprDfn(&m_stMonSpr[2],  160,  6, 120);
		break;
	case  145:										// 다발충1.
	case  146:										// 다발충2.
		SetSprDfn(&m_stMonSpr[2],  160,  6, 150);
		break;

//@@@@@@@@@@@@@@@@@@@@@@@@@@@앙코르와트
	case 164:										// 마왕신.
		SetSprDfn(&m_stMonSpr[2],  160,  9, 120);
		break;

	case 154:	case 155:	case 162:	case 163:	// 원후군, 원후자, 지하여신1, 지하여신2
		SetSprDfn(&m_stMonSpr[2],  160,  6, 120);
		break;
	case 159:	case 160:	case 161:				// 화염사자, 석화사자, 무력신장.
		SetSprDfn(&m_stMonSpr[2],  160,  6, 140);
		break;
	case 156:	case 157:	case 165:	case 166:	// 마신도1, 마신도2, 경비병1, 경비병2
		SetSprDfn(&m_stMonSpr[2],  160,  6, 150);
		break;
	case 167:   case 169:							// 발석차, 연노차
		SetSprDfn(&m_stMonSpr[2],  160,  10, 150);
		break;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@앙코르와트
	case 212:										// 가무녀1
		SetSprDfn(&m_stMonSpr[2],  160,  10, 150);
		break;
	case 213:										// 가무녀2
		SetSprDfn(&m_stMonSpr[2],  160,  20, 90);
		break;
	case 192:	case 191:	case 193:	case 194:	case 195:	case 196:	case 199:	case 204:	case 207:	case 208:	case 171:
		//구아, 비강, 반형괴, 사두괴, 저파룡, 대아룡, 사혈괴, 유령기사,늑대인간, 백랑, 멧돼지
		SetSprDfn(&m_stMonSpr[2],  160,  6, 60);	
		break;

	default:
		SetSprDfn(&m_stMonSpr[2],  160,  6, 130);	
		break;
	}

	// 3. Monster Mtn -> 맞기동작.
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
	case  116:										// 말.
	case  117:										
	case  118:										
		SetSprDfn(&m_stMonSpr[3],  240, 3, 150);		
		break;
	case  149:										// 치충.
		SetSprDfn(&m_stMonSpr[3],  240, 2, 300);
		break;
	case  147:										// 포안충.
		SetSprDfn(&m_stMonSpr[3],  240, 2, 150);
		break;
	case  145:										// 다발충1.
	case  146:										// 다발충2.
		SetSprDfn(&m_stMonSpr[3],  240, 2, 150);
		break;

//@@@@@@@@@@@@@@@@@@@@@@@@@@@앙코르와트
	case 154:	case 155:	case 156:	case 157:	case 159:	case 160:	case 161:	case 162:	case 163:	case 164:
	SetSprDfn(&m_stMonSpr[3],  240, 2, 300);
		break;
	case  158:	case  165:	case  166:
		SetSprDfn(&m_stMonSpr[3],  240, 2, 200);
		break;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@앙코르와트
	case 530 :	// 사북성문1
	case 531 :	// 사북성문2
	case 532 :	// 사북성문3
	case 533 :	// 사북성문4
	case 538 :	/*성훈씨*/
		SetSprDfn(&m_stMonSpr[3],  240, 2, 200);
		break;
	case  212:										// 가무녀
		SetSprDfn(&m_stMonSpr[3],  240, 4, 150);
		break;
	case  213:										// 가무녀2
		SetSprDfn(&m_stMonSpr[3],  480, 4, 150);
		break;
	default:
		SetSprDfn(&m_stMonSpr[3],  240, 2, 180);
		break;
	}

	// 4. Monster Mtn -> 죽기동작.
	switch ( wMonNum )
	{
	case  3:										// 사어
		SetSprDfn(&m_stMonSpr[4],  320, 6, 130);		
		break;
	case 39:										// 태극기
		SetSprDfn(&m_stMonSpr[4],  320, 8, 130);		
		break;
	case  94:										// 사어
		SetSprDfn(&m_stMonSpr[4],  320, 10, 130);		
		break;
	case  30:										// 뭉코.
	case  37:										// 동굴구더기.
		SetSprDfn(&m_stMonSpr[4],  320, 4, 220);		
		break;
	case  104:										// 적월마.
		SetSprDfn(&m_stMonSpr[4],  320, 20, 120);		
		break;
	case  127:										// 밤나무.
	case  153:										// 트리
	case 187:	case 188:	case 534:	case 535:	case 536:	case 537:	case 179:	case 189: // 성훈씨.
		SetSprDfn(&m_stMonSpr[4],  320, 9, 120);		
		break;
	case  141:										// 해골진왕.
		SetSprDfn(&m_stMonSpr[4],  720, 20, 120);		
		break;
	case  149:										// 치충.
		SetSprDfn(&m_stMonSpr[4],  320, 10, 120);
		break;
	case  147:										// 포안충.
		SetSprDfn(&m_stMonSpr[4],  320, 10, 95);
		break;
	case  145:										// 다발충1.
	case  146:										// 다발충2.
		SetSprDfn(&m_stMonSpr[4],  320, 10, 95); 
		break;
	case  8:										// 갑주개미
		SetSprDfn(&m_stMonSpr[4],  320, 10, 130);
		break;
	case  86:										// 궁병, 궁수경비
		SetSprDfn(&m_stMonSpr[4],  320, 10, 130);
		break;
	case 105:										// 폭주
		SetSprDfn(&m_stMonSpr[4],  320, 10, 130);
		break;

//@@@@@@@@@@@@@@@@@@@@@@@@@@@앙코르와트
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
	case 182: // 성훈씨 아룽가 예외
		SetSprDfn(&m_stMonSpr[4],  320, 0, 120);
		break;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@앙코르와트
	case 530 :	// 사북성문1
	case 531 :	// 사북성문2
	case 532 :	// 사북성문3
	case 533 :	// 사북성문4
	case 538 :  // 성훈씨
		SetSprDfn(&m_stMonSpr[4],  320,  8, 120);
		break;
	case 213:										// 가무녀2
		SetSprDfn(&m_stMonSpr[4],  560, 10, 120);
		break;

	default:
		SetSprDfn(&m_stMonSpr[4],  320, 10, 140);
		break;
	}

	// 5. Monster Mtn -> 일반공격동작2.
	switch ( wMonNum )
	{
	case  0: case  1: case  2: case  3: case  4: case  6: case  7: case  8: case  9:
		SetSprDfn(&m_stMonSpr[5],  400,  6, 150);
		break;

//@@@@@@@@@@@@@@@@@@@@@@@@@@@앙코르와트
	case 159:	case 160:							// 화염사자, 석화사자
		SetSprDfn(&m_stMonSpr[5],  400,  6, 140);
		break;
	case 164:										// 마왕신
		SetSprDfn(&m_stMonSpr[5],  400,  9, 120);
		break;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@앙코르와트
	case  212:										// 가무녀
		SetSprDfn(&m_stMonSpr[5],  160,  10, 150);
		break;
	case 213:										// 가무녀2
		SetSprDfn(&m_stMonSpr[5],  320,  20, 70);
		break;
	case 211:										// 새벽여왕
		SetSprDfn(&m_stMonSpr[5],  400,  9, 120);
		break;
	default:
		SetSprDfn(&m_stMonSpr[5],  400,  6, 150);		
		break;
	}

	// 6. Monster Mtn -> 마법공격동작1.
	switch ( wMonNum )
	{
	case 10:	case 205:							// 환마군, 화영
	case 172:
	case 181:										// 성훈씨(npc 19번도)
	case 203:
		SetSprDfn(&m_stMonSpr[6],  400, 6, 150);
		break;
	case 196:										// 대아룡
		SetSprDfn(&m_stMonSpr[6],  480, 6, 60);		
		break;
	case  13:										// 누마법로
	case 170:										// 빙백귀녀
		SetSprDfn(&m_stMonSpr[6],  480, 6, 150);		
		break;
	case  139:										// 우면본왕
		SetSprDfn(&m_stMonSpr[6],  480, 6, 200);		
		break;
	case  141:										// 해골진왕
		SetSprDfn(&m_stMonSpr[6],  480, 6, 120);		
		break;

//@@@@@@@@@@@@@@@@@@@@@@@@@@@앙코르와트
	case 161:										// 무력신장
		SetSprDfn(&m_stMonSpr[6],  480, 6, 140);		
		break;
	case 158:										// 거환수
		SetSprDfn(&m_stMonSpr[6],  480, 6, 200);
		break;
	case 204:										// 화영창기병
		SetSprDfn(&m_stMonSpr[6],  480, 6, 60);
		break;
	case 164:										// 마왕신
		SetSprDfn(&m_stMonSpr[6],  480, 8, 150);
		break;
	case 157:	case 202:							// 마신도2, 빙혼무장1
		SetSprDfn(&m_stMonSpr[6],  480, 6, 150);
		break;
	case 195:										// 저파룡
		SetSprDfn(&m_stMonSpr[6],  480, 6, 60);		
		break;
	case 185:										// 누마친위대장
	case 182:										// 아룽가
		SetSprDfn(&m_stMonSpr[6],  480, 6, 150);		
		break;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@앙코르와트
	case 186:										// 타당가
		SetSprDfn(&m_stMonSpr[6],  480, 8, 150);		
		break;
	case 197:										// 육혈마룡
		SetSprDfn(&m_stMonSpr[6],  480, 8, 150);		
		break;
	default:
		SetSprDfn(&m_stMonSpr[6],  480, 10, 150);		
		break;
	}

	// 7. Monster Mtn -> 마법공격동작2.
	switch ( wMonNum )
	{
	case  0: case  1: case  2: case  3: case  4: case  6: case  7: case  8: case  9:
		SetSprDfn(&m_stMonSpr[7],  560, 10, 150);		
		break;
	case  141:										// 해골진왕
		SetSprDfn(&m_stMonSpr[7],  560, 6, 120);		
		break;
	default:
		SetSprDfn(&m_stMonSpr[7],  560, 10, 150);		
		break;
	}

	// 8. Monster Mtn -> 사라지기, 나타나기 동작.
	switch ( wMonNum )
	{
	case  0: case  1: case  2: case  3: case  4: case  6: case  7: case  8: case  9:
		SetSprDfn(&m_stMonSpr[8],  640,  10, 120);		
		break;
	case 90:	// 신수공격형.
		SetSprDfn(&m_stMonSpr[8],  640,  10, 100);		
		break;
	case 83:	// 주마신장.
		SetSprDfn(&m_stMonSpr[8],  640,  6, 120);		
		break;
	case 84:	// 주마호법.
		SetSprDfn(&m_stMonSpr[8],  640,  6, 120);		
		break;
	case 85:	// 주마왕.
		SetSprDfn(&m_stMonSpr[8],  640,  20, 120);		
		break;
	case 530 :	// 사북성문1
	case 531 :	// 사북성문2
	case 532 :	// 사북성문3
	case 533 :	// 사북성문4
	case 538:   // 성훈씨
		SetSprDfn(&m_stMonSpr[8],  640,   7, 120);		
		break;
	default:
		SetSprDfn(&m_stMonSpr[8],  640,  10, 120);		
		break;
	}

	// 9. Monster Mtn -> 특수동작1.
	switch ( wMonNum )
	{
	default:
		SetSprDfn(&m_stMonSpr[9],  720,  6, 150);		
		break;
	}

	// 10. Monster Mtn -> 해골.
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
	case 2: case 3:  case 6: case 16: case 17: case 19:			//창.
		bMtn = _MT_SPEARVSWING;
		break;
	case 4: case 5:  case 7: case 15:							//양손칼.
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
	// 암호화 루틴해제.
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

	// 데이타적용.
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
	char* pszLine		= pszBuf + 8;		// Seed를 건너뛴다.

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

						//  값을 순서대로 대입한다.
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

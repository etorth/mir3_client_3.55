#ifndef _SPRITEDEF_H
#define _SPRITEDEF_H



/******************************************************************************************************************

	Actor Sprite Frame Define

*******************************************************************************************************************/

//~~~ Hero와 몬스터, NPC를 위한 프레임정의. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
typedef struct tagSPRFRMDEF
{
	WORD		wFstFrm;						// 동작의 시작 프레임.
	WORD		wFrmCnt;						// 동작의 프레임갯수.
	WORD		wDelay;							// 동작의 지연시간.
}SPRFRMDEF, *LPSPRFRMDEF;


/******************************************************************************************************************

	Effect Sprite Frame Define

*******************************************************************************************************************/

//~~~ 마법을 위한 프레임정의. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
typedef struct tagEFFECTSPRINFO
{
	DWORD		dwFstFrm;
	DWORD		dwEndFrm;
	WORD		wDelay;
	WORD		wImgIdx;
	WORD		wEffectIdx;
	BYTE		bLightRadius[2];				// 광원 너비.
	BYTE		bLightColor [2][3];				// 광원 색.
	BYTE		bMagicColor [3];				// 마법 색.
	BYTE		bBlendType;
	BYTE		bOpa;
	BYTE		bSwingCnt;
	BYTE		bDir;
	BOOL		bRepeat;
	BOOL		bFixed;
	BOOL		bShowLight;
	BOOL		bTargetUse;
}EFFECTSPRINFO, *LPEFFECTSPRINFO;


class CSprite
{
public:
	INT					m_nEffectCnt;
	INT					m_nMagicCnt;
	INT					m_nExplosionCnt;

	LPEFFECTSPRINFO		m_pstEffectSpr;			// 마법의 시전및 검법효과.
	LPEFFECTSPRINFO		m_pstMagicSpr;			// 마법효과.
	LPEFFECTSPRINFO		m_pstExplosionSpr;		// 마법폭발효과.

	SPRFRMDEF			m_stHeroSpr[_MAX_HERO_MTN];			// Hero의 동작프레임 정의.
	SPRFRMDEF			m_stMonSpr [_MAX_MON_MTN];			// Monster의 동작프레임 정의.
	SPRFRMDEF			m_stNPCSpr [_MAX_NPC_MTN];			// Monster의 동작프레임 정의.

	BYTE				m_bWOrder[_MAX_HERO_REALFRAME];	

public:
	CSprite();
	~CSprite();

	VOID InitSpriteInfo();
	VOID DeleteSpriteInfo();

	BOOL SetInfo();

	VOID SetSprDfn(LPSPRFRMDEF pstSprDfn, WORD wFstFrm, WORD wFrmCnt, WORD wDelay);

	VOID SetEffectInfo(LPEFFECTSPRINFO pstEffect, DWORD dwFstFrm, DWORD dwEndFrm, WORD wDelay, WORD wImgIdx, WORD wEffectIdx,
					   BYTE bSLightRadius, BYTE bLLightRadius, 
					   BYTE bSLightRColor, BYTE bSLightGColor, BYTE bSLightBColor,
					   BYTE bLLightRColor, BYTE bLLightGColor, BYTE bLLightBColor, 
					   BYTE bMagicRColor = 255, BYTE bMagicGColor = 255, BYTE bMagicBColor = 255, 
					   BYTE bBlendType = _BLEND_LIGHTINV, BYTE bOpa = 0, BYTE bSwingCnt = 0,
					   BYTE bDir = 0, BOOL bRepeat = FALSE, BOOL bFixed = TRUE, BOOL bShowLight = TRUE, BOOL bTargetUse = TRUE);

	LPEFFECTSPRINFO GetEffectInfo(WORD wEffectNum);
	LPEFFECTSPRINFO GetExplosionInfo(WORD wEffectNum);
	LPEFFECTSPRINFO GetMagicInfo(WORD wEffectNum);

	VOID			SetMonFrameInfo(WORD wMonNum);
	VOID			SetNPCFrameInfo(WORD wNPCNum);

	BOOL			SetWeaponOrder(CHAR* szFileName);

	BYTE			GetWeaponMtn(BYTE nWeapon, BOOL bIsVertical = TRUE);

	BOOL			LoadMagicInfo();
};



#endif //_SPRITEDEF_H




















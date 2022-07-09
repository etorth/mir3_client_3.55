/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"



/******************************************************************************************************************

	CActor Class

*******************************************************************************************************************/
/******************************************************************************************************************

	함수명 : CActor::CActor()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
CActor::CActor()
{
	InitActor();
}



/******************************************************************************************************************

	함수명 : CActor::~CActor()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
CActor::~CActor()
{
	DestroyActor();
}

VOID CActor::InitActor()
{
	m_bOpenHealth		= FALSE;
	m_bWarMode			= FALSE;
	m_bCurrMtn			= _MT_MON_STAND;
	m_bCurrDir			= _DIRECTION_LIST_1;
	m_bMoveDir			= _DIRECTION_LIST_1;
	m_bEffectFrameCnt	= _DEFAULT_SPELLFRAME;
	m_bHPPercent		= 100;

	m_bMoveNextFrmCnt	= 5;
	m_bIsMoved			= FALSE;

	m_bLatestFaceImg	= TRUE;
	m_bLoadFaceImg		= FALSE;
	m_bNeedLoadFameImg	= TRUE;

	m_dwCurrMoveSkip	= 0;

	m_wHP				= 0;
	m_dwWarModeTime		= 0;
	m_wMAXHP			= 0;
	m_wMP				= 0;
	m_nPosX				= 0;
	m_nPosY				= 0;
	m_bLightSize		= 2;
	m_nShiftPixelX		= 0;
	m_nShiftPixelY		= 0;
	m_nShiftTileX		= 0;
	m_nShiftTileY		= 0;
	m_bMoveSpeed		= 0;
	m_nScrnPosX			= 0;
	m_nScrnPosY			= 0;
	m_nCurrDelay		= 0;
	m_dwFstFrame		= 0;
	m_dwEndFrame		= 1;
	m_dwCurrFrame		= 0;	
	m_nDelay			= 0;		
	m_pxActorImage		= NULL;
//	m_pxDragonImage		= NULL;
	m_bMsgHurryCheck	= FALSE;
	m_bUseEffect		= FALSE;
	m_bUseSwordEffect	= FALSE;
	m_bReverse			= FALSE;
	m_bIsDead			= FALSE;
	m_bABlendRev		= FALSE;
	m_nABlendDelay		= 0;
	m_nABlendCurrDelay	= 0;

	m_dwCurrEffectFrame = 0;
	m_dwFstEffectFrame	= 0;
	m_dwEndEffectFrame	= 0;
	m_bEffectFrame		= 0;
	m_bBackStepFrame	= 0;
	m_bBackStepFrameCnt = 0;

	m_nCharState			= 0;
	m_nFaceImageDate	= 0;
	m_bGuildFlag		= 0;
	m_bFlagRed			= 0;
	m_bFlagGreen		= 0;
	m_bFlagBlue			= 0;
	m_wEffectLooks		= 0;

	m_nDividedChatLine	= 0;
	m_nIdentity			= 0;
	m_wCurrChatDelay	= 0;

	m_bDelStruckCnt		= 0;

	m_nShowBloodIdx		= 0;

	m_dwNameQueryTimer	= 0;
//	m_nGenPacket		= -1;
//	m_nRecvPacketCnt	= 0;

	m_bFstSoundPlayed   = FALSE;

	m_wMonColor			= 0XFFFF;

	m_bAppearState		= _DIG_NORMAL;

	m_wStateClr			= _STATE_NOTUSED;
	m_dwNameClr			= RGB(255, 255, 255);

	m_bActorImgIdx		= _IMAGE_M_HUMAN;
	m_bEffectImgIdx		= _IMAGE_MAGIC;

	m_bJob				= 0;

	m_dwSturnTimer		= 0;
	m_nStrurnFrame		= 680;

	m_bIsSturn			= FALSE;

	ZeroMemory(m_szMateName, 64);
	ZeroMemory(m_szName, 64);
	ZeroMemory(m_szGuildName, 64);
	ZeroMemory(m_szRankName, 64);

	for ( INT nI=0; nI<3; nI++ )
		ZeroMemory(m_szShowName[nI], 64);

	m_hbmFaceImg.ReleaseSurface();

	ZeroMemory(&m_stFeature,   sizeof(FEATURE));
	ZeroMemory(&m_stHitter,    sizeof(FEATURE));
	ZeroMemory(m_bLightRadius, sizeof(BYTE)*2);
	ZeroMemory(m_bLightColor , sizeof(BYTE)*2*3);
	ZeroMemory(m_bEffectColor, sizeof(BYTE)*3);
	ZeroMemory(m_szChatMsg, MAX_PATH);
	ZeroMemory(m_szChatMsgArg, MAX_PATH*8);
	ZeroMemory(&m_rcActor, sizeof(RECT));
	ZeroMemory(&m_rcTargetRgn, sizeof(RECT));
	ZeroMemory(m_nShowBlood, sizeof(INT)*8);
	ZeroMemory(m_ptShowBlood, sizeof(POINT)*8);
	ZeroMemory(&m_dwShowBloodTimer, sizeof(WORD)*8);
	m_bEffectBlend = _BLEND_LIGHTINV;	
	m_bEffectOpa = 0;

	D3DVECTOR		vNorm(0, 0, -1);
	m_avBoard[0] = D3DVERTEX(D3DVECTOR(-0.5f, 0.5f, 0), vNorm, 0, 0);
	m_avBoard[1] = D3DVERTEX(D3DVECTOR(-0.5f,-0.5f, 0), vNorm, 0, 1);
	m_avBoard[2] = D3DVERTEX(D3DVECTOR( 0.5f, 0.5f, 0), vNorm, 1, 0);
	m_avBoard[3] = D3DVERTEX(D3DVECTOR( 0.5f,-0.5f, 0), vNorm, 1, 1);

	m_stMonType.nDead = -1;
	m_stMonType.nTaiming = -1;
	memset(&m_stMonType.stMonStats, -1, sizeof(MONSTERSTATUSINFO));
}


VOID CActor::DestroyActor()
{
	INT			nCnt;
	INT			nLeftMsgCnt;
	LPPACKETMSG	lpPacketMsg;

	lpPacketMsg  = NULL;
	nLeftMsgCnt = m_xPacketQueue.GetCount();

	// 쌓여있는 패킷을 지운다.
	if ( nLeftMsgCnt > 0 )
	{
		for ( nCnt = 0; nCnt < nLeftMsgCnt; nCnt++ )
		{
			lpPacketMsg = (LPPACKETMSG)m_xPacketQueue.PopQ();
			if ( lpPacketMsg )
			{
				SAFE_DELETE(lpPacketMsg);
			}
		}
	}

	// 모든변수를 초기화 시켜둔다.
	InitActor();
}

/******************************************************************************************************************

	함수명 : CActor::GetCharState()

	작성자 : 이경수
	작성일 : 

	목적   : 캐릭터 상태 값 반환
	출력   : WORD형 캐릭터 상태 값

	[일자][수정자] : 수정내용
	[2006/01/06][이경수] : 석화 상태 비교 구문 맨 뒤로 뺌. 석화 상태가 먼저 비교되면 불필요하게 서버에 움직이는 메세지 보냄.
	                       최종 상태값을 반환하기 때문에 잠재적인 문제가 있음

*******************************************************************************************************************/
WORD CActor::GetCharState()
{		
	WORD wCharState =	 0XFFFF;

//	if( m_nCharState & 0X00100000 )			wCharState = _STATE_SHIELDUSE;
	if( m_nCharState & 0X00800000 )
		wCharState = _STATE_ABLEND;

	if( m_nCharState & 0X20000000 )
		wCharState = _STATE_FUCHSIA;

//	if( m_nCharState & 0X10000000 )			wCharState = _STATE_YELLOW;
	if( m_nCharState & 0X08000000 )
		wCharState = _STATE_BLUE;

	if( m_nCharState & 0X00001000 )
		wCharState = _STATE_DARKBLUE;

	if( m_nCharState & 0X40000000 )
		wCharState = _STATE_RED;

	if( m_nCharState & 0X80000000 )
		wCharState = _STATE_GREEN;

	if( m_nCharState & 0X00020000 )
		wCharState = _STATE_ABLEND;

	// 석화
	if( m_nCharState & 0X04000000 )
		wCharState = _STATE_GRAY;

	m_wStateClr = _STATE_NOTUSED;

 	if ( m_wStateClr == _STATE_ABLEND || m_wStateClr == _STATE_SHIELDUSE )
	{
		m_wStateClr = _STATE_NOTUSED;
	}

	return wCharState;
}

/******************************************************************************************************************

	함수명 : CActor::DrawWithEffected

	작성자 : 이경수
	작성일 : 

	목적   : 실제 캐릭터 그리는 함수
	출력   : 없음

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CActor::DrawWithEffected(INT nX, INT nY, INT nXSize, INT nYSize, WORD* pwSrc, WORD wChooseColor1, WORD wChooseColor2, BOOL bFocused, BYTE bOpa, WORD wState)
{
	switch ( wState )
	{
	case _STATE_RED:
	case _STATE_GREEN:
	case _STATE_BLUE:		
	case _STATE_YELLOW:
	case _STATE_FUCHSIA:	
	case _STATE_GRAY:
	case _STATE_DARKBLUE:
		if ( m_nABlendDelay )
			g_xMainWnd.DrawWithImageForCompClipRgnColor(nX, nY, nXSize, nYSize, pwSrc, _CLIP_WIDTH, _CLIP_HEIGHT, wState, bFocused, TRUE);
		else
			g_xMainWnd.DrawWithImageForCompClipRgnColor(nX, nY, nXSize, nYSize, pwSrc, _CLIP_WIDTH, _CLIP_HEIGHT, wState, bFocused, FALSE);
		break;
	case _STATE_ABLEND:
		{
			bOpa = 8;
			g_xMainWnd.DrawWithABlendCompDataWithBackBufferEx(nX, nY, nXSize, nYSize, pwSrc, _CLIP_WIDTH, _CLIP_HEIGHT, wChooseColor1, wChooseColor2, bOpa);
		}
		break;
	case _STATE_SHIELDUSE:
	case _STATE_NOTUSED:
	default:
		{
		if ( !m_nABlendDelay )
		{
			if ( g_xGameProc.m_bShowDeying )
				g_xMainWnd.DrawWithImageForCompClipRgn(nX, nY, nXSize, nYSize, pwSrc, _CLIP_WIDTH, _CLIP_HEIGHT, wChooseColor1, wChooseColor2, bFocused);
			else
				g_xMainWnd.DrawWithImageForCompClipRgnBaseNoColor(nX, nY, nXSize, nYSize, pwSrc, _CLIP_WIDTH, _CLIP_HEIGHT);
		}
		else
			g_xMainWnd.DrawWithABlendCompDataWithBackBufferEx(nX, nY, nXSize, nYSize, pwSrc, _CLIP_WIDTH, _CLIP_HEIGHT, wChooseColor1, wChooseColor2, bOpa);			
		}
		break;
	}
}


/******************************************************************************************************************

	함수명 : CActor::Create()

	작성자 : 
	작성일 : 

	목적   : 기본적인 캐릭터 생성 처리. 
	입력   : CImageHandler* pxImgHandler
	         FEATURE stFeature
	         BYTE bMtn
	         WORD bDir
	         WORD wPosX
	         WORD wPosY
	출력   : BOOL 
	주의   : 서버에서 불필요한 방향을 보내는 경우가 있어 방향을 생성시부터 고정시키는 경우가 있음.

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CActor::Create(CImageHandler* pxImgHandler, FEATURE* pstFeature, BYTE bMtn, BYTE bDir, INT nPosX, INT nPosY)
{
	// 전달인자 적용 및 확인./////////////////////////////////////////////////////////////////////////////////
	if ( (bDir >= 0 && bDir < _MAX_DIRECTION) )
	{
		switch ( pstFeature->bGender )
		{
		case _GENDER_MAN:
			{
				if ( (pstFeature->bDress >= _MAX_HERO_KIND) || (bMtn >= _MAX_HERO_MTN) )	
				{
					return FALSE;
				}
				else	
				{
					m_bActorImgIdx = _IMAGE_M_HUMAN;
					m_dwFstFrame   = g_xSpriteInfo.m_stHeroSpr[bMtn].wFstFrm + pstFeature->bDress*_MAX_HERO_FRAME + bDir*10;
					m_dwEndFrame   = m_dwFstFrame + g_xSpriteInfo.m_stHeroSpr[bMtn].wFrmCnt;
					m_nDelay	   = g_xSpriteInfo.m_stHeroSpr[bMtn].wDelay;
				}
			}
			break;
		case _GENDER_WOMAN:
			{
				if ( (pstFeature->bDress >= _MAX_HERO_KIND) || (bMtn >= _MAX_HERO_MTN) )	
				{
					return FALSE;
				}
				else
				{
					m_bActorImgIdx = _IMAGE_WM_HUMAN;
					m_dwFstFrame   = g_xSpriteInfo.m_stHeroSpr[bMtn].wFstFrm + pstFeature->bDress*_MAX_HERO_FRAME + bDir*10;
					m_dwEndFrame   = m_dwFstFrame + g_xSpriteInfo.m_stHeroSpr[bMtn].wFrmCnt;
					m_nDelay	   = g_xSpriteInfo.m_stHeroSpr[bMtn].wDelay;
				}
			}
			break;
		case _GENDER_MON:
			{	
				WORD wDress = MAKEWORD(pstFeature->bDress, pstFeature->bHair);
				if ( /*(wDress >= _MAX_MON_KIND) || */(bMtn >= _MAX_MON_MTN) )	
				{
					return FALSE;
				}
				else
				{
					switch ( wDress )
					{
					case 0:		// 돌기둥
					case 31:	// 식인초.
					case 67:	// 촉룡신.
					case 73:	// 비막원충.
					case 104:	// 적월마.
					case 127:	// 밤나무.
					case 187:	case 188:	case 534:	case 535:	case 536:	case 537:	case 179:	case 189:// 성훈씨.
					case 153:	// 트리
					case 5:		// 이계의문
					case 3:     // 훈련소
					case 11:	// 수호자
					case 15:	// 신전
					case 16:	// 사령부
					case 39:	// 태극기
						bDir = 0;
						break;
					case 106:	// 폭안거미.
						bDir = 1;
						break;
					default:
						break;
					}

					g_xSpriteInfo.SetMonFrameInfo(wDress);

					if ( wDress < 2000 )
					{
						m_bActorImgIdx = (BYTE)(_IMAGE_MONSTER1 + (BYTE)(wDress / 10));

						if ( m_bActorImgIdx >= _MAX_IMAGE )
						{
							return FALSE;
						}

						if ( wDress == 182 )
						{
							WORD wTemp = 185;

							m_dwFstFrame = g_xSpriteInfo.m_stMonSpr[bMtn].wFstFrm + (wTemp%10)*_MAX_MON_FRAME + bDir*10;
							m_dwEndFrame = m_dwFstFrame + g_xSpriteInfo.m_stMonSpr[bMtn].wFrmCnt;
							m_nDelay = g_xSpriteInfo.m_stMonSpr[bMtn].wDelay;
						}
						else
						{
							m_dwFstFrame = g_xSpriteInfo.m_stMonSpr[bMtn].wFstFrm + (wDress%10)*_MAX_MON_FRAME + bDir*10;
							m_dwEndFrame = m_dwFstFrame + g_xSpriteInfo.m_stMonSpr[bMtn].wFrmCnt;
							m_nDelay = g_xSpriteInfo.m_stMonSpr[bMtn].wDelay;
						}
					}
					else
					{
						m_bActorImgIdx = (BYTE)(_IMAGE_DMONSTER1 + (BYTE)((wDress-2000) / 100));

						if ( m_bActorImgIdx >= _MAX_IMAGE )
						{
							return FALSE;
						}

						m_wMonColor = GetMonDyeingColor(wDress%10);
						
						m_dwFstFrame = g_xSpriteInfo.m_stMonSpr[bMtn].wFstFrm + ((wDress-2000)/10)*_MAX_MON_FRAME + bDir*10;
						m_dwEndFrame = m_dwFstFrame + g_xSpriteInfo.m_stMonSpr[bMtn].wFrmCnt;
						m_nDelay = g_xSpriteInfo.m_stMonSpr[bMtn].wDelay;
					}
				}
			}
			break;
		case _GENDER_FLAG:
			{
				WORD wDress = m_stFeature.bWeapon;
				
				m_bActorImgIdx = _IMAGE_FLAG;

				bMtn = _MT_NPC_STAND;
				bDir = 0;

				g_xSpriteInfo.SetNPCFrameInfo(wDress+77);

				m_dwFstFrame = g_xSpriteInfo.m_stNPCSpr[bMtn].wFstFrm + wDress*_MAX_NPC_FRAME + bDir*10;
				m_dwEndFrame = m_dwFstFrame + g_xSpriteInfo.m_stNPCSpr[bMtn].wFrmCnt;
				m_nDelay = g_xSpriteInfo.m_stNPCSpr[bMtn].wDelay;
			}
			break;
		case _GENDER_NPC:
			{
				if ( (pstFeature->bDress >= _MAX_NPC_KIND) || (bMtn >= _MAX_NPC_MTN) )	
				{
					return FALSE;
				}
				else
				{
					m_bActorImgIdx = _IMAGE_NPC;

					bDir		   = (BYTE)(bDir%3);

					// 특수동작이 없는 NPC들.
					if ( (bMtn ==_MT_NPC_ACT01) && ( pstFeature->bDress == 24 || pstFeature->bDress == 25 || pstFeature->bDress == 34 || pstFeature->bDress == 35 || 
						 pstFeature->bDress == 43 || pstFeature->bDress == 44 || pstFeature->bDress == 45 || pstFeature->bDress == 46 || pstFeature->bDress == 47 || 
						 pstFeature->bDress == 48 || pstFeature->bDress == 49 || pstFeature->bDress == 50) )
					{
						bMtn = _MT_NPC_STAND;
					}

					// 한방향밖에 없는 NPC들.
					if ( pstFeature->bDress == 40 )
					{
						bDir = 0;
					}

					if ( pstFeature->bDress == 51 || pstFeature->bDress == 52 || m_stFeature.bDress == 53 || m_stFeature.bDress == 54 || m_stFeature.bDress == 55 )
					{
						bMtn = _MT_NPC_STAND;
						bDir = 0;
					}

					// 경량화
					bMtn = _MT_NPC_STAND;
					bDir = 0;

					g_xSpriteInfo.SetNPCFrameInfo(pstFeature->bDress);

					m_dwFstFrame = g_xSpriteInfo.m_stNPCSpr[bMtn].wFstFrm + pstFeature->bDress*_MAX_NPC_FRAME + bDir*10;
					m_dwEndFrame = m_dwFstFrame + g_xSpriteInfo.m_stNPCSpr[bMtn].wFrmCnt;
					m_nDelay = g_xSpriteInfo.m_stNPCSpr[bMtn].wDelay;
				}
			}
			break;
		default:
			{
				return FALSE;
			}
		}
		
		m_bCurrMtn		= bMtn;
		m_bCurrDir		= bDir;
		m_bMoveDir		= bDir;
		m_nPosX			= nPosX;
		m_nPosY			= nPosY;
		
		ChangeFeature(*pstFeature);

		m_pxActorImage	= &(pxImgHandler->m_xImageList[m_bActorImgIdx]);
		m_dwCurrFrame	= m_dwFstFrame;
		m_bMoveDir		= m_bCurrDir;

#ifdef _TEST_SERVER		// by eriastoa 2006.05.29
		if ( m_nEft == 1 ) // 용갑옷 입고 있으면
		{
			if ( pstFeature->bGender == _GENDER_MAN )
				m_pxDragonImage = &(pxImgHandler->m_xImageList[_IMAGE_M_ARMOREFT]);
			else if ( pstFeature->bGender == _GENDER_WOMAN )
				m_pxDragonImage = &(pxImgHandler->m_xImageList[_IMAGE_WM_ARMOREFT]);
		}
		else
		{
			m_pxDragonImage = NULL;
		}
#endif

		D3DVECTOR		vNorm(0, 0, -1);
		m_avBoard[0] = D3DVERTEX(D3DVECTOR(-0.5f, 0.5f, 0), vNorm, 0, 0);
		m_avBoard[1] = D3DVERTEX(D3DVECTOR(-0.5f,-0.5f, 0), vNorm, 0, 1);
		m_avBoard[2] = D3DVERTEX(D3DVECTOR( 0.5f, 0.5f, 0), vNorm, 1, 0);
		m_avBoard[3] = D3DVERTEX(D3DVECTOR( 0.5f,-0.5f, 0), vNorm, 1, 1);

		m_nScrnPosX = (m_nPosX - g_xGameProc.m_xMap.m_nStartViewTileX) * _CELL_WIDTH + g_xGameProc.m_xMap.m_nViewPosX - g_xGameProc.m_xMap.m_nViewOffsetX + m_nShiftPixelX;
		m_nScrnPosY = (m_nPosY - g_xGameProc.m_xMap.m_nStartViewTileY) * _CELL_HEIGHT+ g_xGameProc.m_xMap.m_nViewPosY - g_xGameProc.m_xMap.m_nViewOffsetY + m_nShiftPixelY;

		return TRUE;
	}
	
	return FALSE;
}



/******************************************************************************************************************

	함수명 : CActor::CheckFeatureValidate()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : FEATURE stFeature
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CActor::CheckFeatureValidate(FEATURE stFeature)
{
	switch ( stFeature.bGender )
	{
	case _GENDER_MAN:
	case _GENDER_WOMAN:
		if ( stFeature.bDress >= _MAX_HERO_KIND )		return FALSE;
		break;
	case _GENDER_FLAG:
		return TRUE;
		break;
	case _GENDER_MON:
	{
//		WORD wDress = MAKEWORD(stFeature.bDress, stFeature.bHair);
//		if ( stFeature.bDress >= _MAX_MON_KIND )		return FALSE;
		break;
	}
	case _GENDER_NPC:
		if ( stFeature.bDress >= _MAX_NPC_KIND )		return FALSE;
		break;
	default:
		return FALSE;
	}

	return TRUE;
}



/******************************************************************************************************************

	함수명 : CActor::ChangeFeature()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : CImageHandler* pxImgHandler
	         FEATURE stFeature
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CActor::ChangeFeature(FEATURE stFeature)
{
	CImageHandler* pxImgHandler = &g_xGameProc.m_xImage;

	if ( CheckFeatureValidate(stFeature) )
	{
		m_stFeature		= stFeature;

		switch ( stFeature.bGender )
		{
		case _GENDER_MAN:
			{
				if ( stFeature.bDress >= _MAX_HERO_KIND )
				{
					return FALSE;
				}
				else	
				{
					m_bActorImgIdx = _IMAGE_M_HUMAN;
					m_dwFstFrame = g_xSpriteInfo.m_stHeroSpr[m_bCurrMtn].wFstFrm + stFeature.bDress*_MAX_HERO_FRAME + m_bCurrDir*10;
					m_dwEndFrame = m_dwFstFrame + g_xSpriteInfo.m_stHeroSpr[m_bCurrMtn].wFrmCnt;
					m_nDelay = g_xSpriteInfo.m_stHeroSpr[m_bCurrMtn].wDelay;
					m_stFeature.bHair = stFeature.bHair & 0x3F; 
					m_bJob = (stFeature.bHair >> 6) & 0x03;
				}
			}
			break;
		case _GENDER_WOMAN:
			{
				if ( stFeature.bDress >= _MAX_HERO_KIND )
				{
					return FALSE;
				}
				else
				{
					m_bActorImgIdx = _IMAGE_WM_HUMAN;
					m_dwFstFrame = g_xSpriteInfo.m_stHeroSpr[m_bCurrMtn].wFstFrm + stFeature.bDress*_MAX_HERO_FRAME + m_bCurrDir*10;
					m_dwEndFrame = m_dwFstFrame + g_xSpriteInfo.m_stHeroSpr[m_bCurrMtn].wFrmCnt;
					m_nDelay = g_xSpriteInfo.m_stHeroSpr[m_bCurrMtn].wDelay;
					m_stFeature.bHair = stFeature.bHair & 0x3F; 
					m_bJob = (stFeature.bHair >> 6) & 0x03;
				}
			}
			break;
		case _GENDER_FLAG:
			{
				WORD wDress = m_stFeature.bWeapon;
				
				m_bActorImgIdx = _IMAGE_FLAG;

				m_bCurrMtn = _MT_NPC_STAND;
				m_bCurrDir = 0;

				g_xSpriteInfo.SetNPCFrameInfo(wDress+77);
				
				m_dwFstFrame = g_xSpriteInfo.m_stNPCSpr[m_bCurrMtn].wFstFrm + wDress*_MAX_NPC_FRAME + m_bCurrDir*10;
				m_dwEndFrame = m_dwFstFrame + g_xSpriteInfo.m_stNPCSpr[m_bCurrMtn].wFrmCnt;
				m_nDelay = g_xSpriteInfo.m_stNPCSpr[m_bCurrMtn].wDelay;
			}
			break;
		case _GENDER_MON:
			{
/*				if ( stFeature.bDress >= _MAX_MON_KIND )
				{
					return FALSE;
				}
				else
*/				{
					WORD wDress = MAKEWORD(stFeature.bDress, stFeature.bHair);

					g_xSpriteInfo.SetMonFrameInfo(wDress);
					
					// 코드 정리 by eriastoa 2006.04.20
					if( SetMonImgIdx( wDress ) == FALSE ) { return FALSE; }
					
					if( wDress < 1000 )
					{
						if( wDress == 182 )
						{
							WORD wTemp = 185;

							m_dwFstFrame = g_xSpriteInfo.m_stMonSpr[m_bCurrMtn].wFstFrm + (wTemp%10)*_MAX_MON_FRAME + m_bCurrDir*10;
							m_dwEndFrame = m_dwFstFrame + g_xSpriteInfo.m_stMonSpr[m_bCurrMtn].wFrmCnt;
							m_nDelay = g_xSpriteInfo.m_stMonSpr[m_bCurrMtn].wDelay;
						}
						else
						{
							m_dwFstFrame = g_xSpriteInfo.m_stMonSpr[m_bCurrMtn].wFstFrm + (wDress%10)*_MAX_MON_FRAME + m_bCurrDir*10;
							m_dwEndFrame = m_dwFstFrame + g_xSpriteInfo.m_stMonSpr[m_bCurrMtn].wFrmCnt;
							m_nDelay = g_xSpriteInfo.m_stMonSpr[m_bCurrMtn].wDelay;
						}
					}
					else
					{
						m_dwFstFrame = g_xSpriteInfo.m_stMonSpr[m_bCurrMtn].wFstFrm + ((wDress-2000)/10)*_MAX_MON_FRAME + m_bCurrDir*10;
						m_dwEndFrame = m_dwFstFrame + g_xSpriteInfo.m_stMonSpr[m_bCurrMtn].wFrmCnt;
						m_nDelay = g_xSpriteInfo.m_stMonSpr[m_bCurrMtn].wDelay;
					}
				}
			}
			break;
		case _GENDER_NPC:
			if ( stFeature.bDress >= _MAX_NPC_KIND )
			{
				return FALSE;
			}
			else
			{
				m_bActorImgIdx = _IMAGE_NPC;
				m_dwFstFrame = g_xSpriteInfo.m_stNPCSpr[m_bCurrMtn].wFstFrm + stFeature.bDress*_MAX_NPC_FRAME + m_bCurrDir*10;
				m_dwEndFrame = m_dwFstFrame + g_xSpriteInfo.m_stNPCSpr[m_bCurrMtn].wFrmCnt;
				m_nDelay = g_xSpriteInfo.m_stNPCSpr[m_bCurrMtn].wDelay;
			}
			break;
		}
		
		m_pxActorImage	= &(pxImgHandler->m_xImageList[m_bActorImgIdx]);
		if ( m_bCurrMtn != _MT_SPELL2 && m_bCurrMtn != _MT_SPELL1 )
		{
			m_dwCurrFrame	= m_dwFstFrame;
		}

#ifdef _TEST_SERVER		// by eriastoa 2006.05.29
		if ( m_nEft == 1 ) // 용갑옷 입고 있으면
		{
			if ( stFeature.bGender == _GENDER_MAN )
				m_pxDragonImage = &(pxImgHandler->m_xImageList[_IMAGE_M_ARMOREFT]);
			else if ( stFeature.bGender == _GENDER_WOMAN )
				m_pxDragonImage = &(pxImgHandler->m_xImageList[_IMAGE_WM_ARMOREFT]);
		}
		else
		{
			m_pxDragonImage = NULL;
		}
#endif

		return TRUE;
	}
	
	return FALSE;
}


/******************************************************************************************************************

	함수명 : CActor::SetMotionFrame()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : BYTE bMtn
	         BYTE bDir
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CActor::SetMotionFrame(BYTE bMtn, BYTE bDir, DWORD dwDelay)
{
	if ( m_stFeature.bGender == _GENDER_MAN || m_stFeature.bGender == _GENDER_WOMAN )
	{
		if ( bMtn == _MT_TWOVSWING || bMtn == _MT_SPEARVSWING )
			bMtn = _MT_ONEVSWING;
		else if ( bMtn == _MT_TWOHSWING || bMtn == _MT_SPEARHSWING )
			bMtn = _MT_ONEHSWING;
	}

	if ( bDir >= _MAX_DIRECTION )
	{
		return FALSE;
	}

	if ( m_bActorImgIdx >= _MAX_IMAGE )
	{
		return FALSE;
	}

	if ( !m_pxActorImage )
	{
		m_pxActorImage	= &(g_xGameProc.m_xImage.m_xImageList[m_bActorImgIdx]);
	}

	// by eriastoa 2006.05.24
#ifdef _TEST_SERVER
	if ( !m_pxDragonImage ) // 용갑옷 입고 있으면
	{
		if ( m_stFeature.bGender == _GENDER_MAN )
			m_pxDragonImage = &(g_xGameProc.m_xImage.m_xImageList[_IMAGE_M_ARMOREFT]);
		else if ( m_stFeature.bGender == _GENDER_WOMAN )
			m_pxDragonImage = &(g_xGameProc.m_xImage.m_xImageList[_IMAGE_WM_ARMOREFT]);
	}
#endif

	switch ( m_stFeature.bGender )
	{
	case _GENDER_MAN:
		{
			if ( (m_stFeature.bDress >= _MAX_HERO_KIND) || (bMtn >= _MAX_HERO_MTN) )	
			{
				return FALSE;
			}
			else	
			{
				m_dwFstFrame   = g_xSpriteInfo.m_stHeroSpr[bMtn].wFstFrm + m_stFeature.bDress*_MAX_HERO_FRAME + bDir*10;
				m_dwEndFrame = m_dwFstFrame + g_xSpriteInfo.m_stHeroSpr[bMtn].wFrmCnt;
				m_nDelay = g_xSpriteInfo.m_stHeroSpr[bMtn].wDelay;
			}
		}
		break;

	case _GENDER_WOMAN:
		{
			if ( (m_stFeature.bDress >= _MAX_HERO_KIND) || (bMtn >= _MAX_HERO_MTN) )	
			{
				return FALSE;
			}
			else	
			{
				m_dwFstFrame = g_xSpriteInfo.m_stHeroSpr[bMtn].wFstFrm + m_stFeature.bDress*_MAX_HERO_FRAME + bDir*10;
				m_dwEndFrame = m_dwFstFrame + g_xSpriteInfo.m_stHeroSpr[bMtn].wFrmCnt;
				m_nDelay = g_xSpriteInfo.m_stHeroSpr[bMtn].wDelay;
			}
		}
		break;

	case _GENDER_MON:
		{
			WORD wDress = MAKEWORD(m_stFeature.bDress, m_stFeature.bHair);
			if ( /*(wDress >= _MAX_MON_KIND) ||*/ (bMtn >= _MAX_MON_MTN) )	
			{
				return FALSE;
			}

			// 코드 정리 by eriastoa 2006.04.19
			MonEffectLoad( wDress, bMtn, bDir );
		}
		break;
	case _GENDER_FLAG:
		{
			WORD wDress = m_stFeature.bWeapon;
			
			m_bActorImgIdx = _IMAGE_FLAG;

			bMtn = _MT_NPC_STAND;
			bDir = 0;


			g_xSpriteInfo.SetNPCFrameInfo(wDress+77);

			m_dwFstFrame = g_xSpriteInfo.m_stNPCSpr[bMtn].wFstFrm + wDress*_MAX_NPC_FRAME + bDir*10;
			m_dwEndFrame = m_dwFstFrame + g_xSpriteInfo.m_stNPCSpr[bMtn].wFrmCnt;
			m_nDelay = g_xSpriteInfo.m_stNPCSpr[bMtn].wDelay;
		}
		break;
	case _GENDER_NPC:
		{
			if ( (m_stFeature.bDress >= _MAX_NPC_KIND) || (bMtn >= _MAX_NPC_MTN) )	
			{
				return FALSE;
			}
			else
			{
				bDir = (BYTE)(bDir%3);

				// 경량화
				bDir = 0;

				// 특수동작이 없는 NPC들.
				if ( (bMtn ==_MT_NPC_ACT01) && ( m_stFeature.bDress == 24 || m_stFeature.bDress == 25 || m_stFeature.bDress == 34 || m_stFeature.bDress == 35 || 
					 m_stFeature.bDress == 43 || m_stFeature.bDress == 44 || m_stFeature.bDress == 45 || m_stFeature.bDress == 46 || m_stFeature.bDress == 47 || 
					 m_stFeature.bDress == 48 || m_stFeature.bDress == 49 || m_stFeature.bDress == 50 || m_stFeature.bDress == 58 || m_stFeature.bDress == 76 ||
					 m_stFeature.bDress == 69 || 
					 m_stFeature.bDress == 80 || m_stFeature.bDress == 82 || m_stFeature.bDress == 83 || m_stFeature.bDress == 84 || m_stFeature.bDress == 85 || 
					 m_stFeature.bDress == 86 || m_stFeature.bDress == 90) )
				{
					bMtn = _MT_NPC_STAND;
				} 

				if ( m_stFeature.bDress == 40 || m_stFeature.bDress == 56 || m_stFeature.bDress == 57 || m_stFeature.bDress == 87)
				{
					bDir = 0;
				}

				if ( m_stFeature.bDress == 51 || m_stFeature.bDress == 52 || m_stFeature.bDress == 53 || m_stFeature.bDress == 54 || 
					 m_stFeature.bDress == 55 || m_stFeature.bDress == 59 || m_stFeature.bDress == 64 || m_stFeature.bDress == 65 || 
					 m_stFeature.bDress == 88 || m_stFeature.bDress == 89 || m_stFeature.bDress == 19 || m_stFeature.bDress == 91 || m_stFeature.bDress == 92)
				{
					bMtn = _MT_NPC_STAND;
					bDir = 0;
				}

				// 경량화
				bMtn = _MT_NPC_STAND;
				bDir = 0;

				// 누마사령법사.
				if ( m_stFeature.bDress == 87 )
				{
					LoadEffect(&g_xGameProc.m_xImage, _NPCEFFECT_THESWORD, bDir);
					m_bUseSwordEffect = TRUE;
					break;
				}

				g_xSpriteInfo.SetNPCFrameInfo(m_stFeature.bDress);
				m_dwFstFrame = g_xSpriteInfo.m_stNPCSpr[bMtn].wFstFrm + m_stFeature.bDress*_MAX_NPC_FRAME + bDir*10;
				m_dwEndFrame = m_dwFstFrame + g_xSpriteInfo.m_stNPCSpr[bMtn].wFrmCnt;
				m_nDelay = g_xSpriteInfo.m_stNPCSpr[bMtn].wDelay;
			}
		}
		break;
	default:
		return FALSE;
	}

	if ( dwDelay != 0 )
		m_nDelay = dwDelay;

	// if( bMtn == _MT_MON_DIE ) if( m_wHP == 0 ) { } 이게 들어가야 하지 안을까?
	// by eriastoa 2006.04.05
	m_bCurrMtn		= bMtn;

	if ( m_stFeature.bGender == _GENDER_MAN || m_stFeature.bGender == _GENDER_WOMAN )
	{
		if ( m_bCurrMtn == _MT_TWOVSWING || m_bCurrMtn == _MT_SPEARVSWING )
			m_bCurrMtn = _MT_ONEVSWING;
		else if ( m_bCurrMtn == _MT_TWOHSWING || m_bCurrMtn == _MT_SPEARHSWING )
			m_bCurrMtn = _MT_ONEHSWING;
	}

	m_bCurrDir		= bDir;
	m_bMoveDir		= bDir;
	m_dwCurrFrame	= m_dwFstFrame;
	m_nCurrDelay	= 0;

	if ( m_bCurrDir == _DIRECTION_LIST_8 )
	{
		m_bMoveNextFrmCnt = 2;
	}
	else
	{
		m_bMoveNextFrmCnt = 5;
	}

	if( m_nCharState & 0X8000000 )			
	{
		m_nDelay *= 2;
	}

	return TRUE;
}


VOID CActor::PlayActSound()
{
	INT nWaveNum = -1;

	WORD wDress;
	if ( m_stFeature.bGender == _GENDER_MON )
	{
		wDress = MAKEWORD(m_stFeature.bDress, m_stFeature.bHair);
	}
	else
	{
		wDress = m_stFeature.bDress;
	}

	if ( m_dwCurrFrame == m_dwFstFrame+1 && m_bCurrMtn == _MT_MON_APPEAR )			// 나타나기.
	{
		nWaveNum = 200 + wDress*10;
	}
	else if ( (m_dwCurrFrame == m_dwFstFrame+1) && (m_bCurrMtn == _MT_MON_STAND || m_bCurrMtn == _MT_MON_WALK) )		// 멈춰있기.
	{
		INT nRand = rand();

		if ( m_bFstSoundPlayed && !m_bIsDead )
		{
			if ( !(nRand%25) )
				nWaveNum = 200 + wDress*10 + 1;
			else
				nWaveNum = -1;
		}
		else
		{
			if ( !(nRand%3) && !m_bIsDead )
			{
				nWaveNum = 200 + wDress*10 + 1;
				m_bFstSoundPlayed = TRUE;
			}
			else
				nWaveNum = -1;
		}
	}
	else if ( m_dwCurrFrame == m_dwFstFrame+1 && m_bCurrMtn == _MT_MON_ATTACK_A )	// 일반공격1.(무기?)
	{
		nWaveNum = 200 + wDress*10 + 2;
	}
	else if ( m_dwCurrFrame == m_dwFstFrame+2 && m_bCurrMtn == _MT_MON_ATTACK_A )	// 일반공격1.(괴성?)
	{
		nWaveNum = 200 + wDress*10 + 3;
	}
	else if ( m_dwCurrFrame == m_dwFstFrame+1 && m_bCurrMtn == _MT_MON_HITTED )		// 맞기.
	{
		nWaveNum = 200 + wDress*10 + 4;
	}
	else if ( m_dwCurrFrame == m_dwFstFrame+2 && m_bCurrMtn == _MT_MON_DIE )		// 죽기1.
	{
		nWaveNum = 200 + wDress*10 + 5;
	}
	else if ( m_dwCurrFrame == m_dwFstFrame+3 && m_bCurrMtn == _MT_MON_DIE )		// 죽기2.
	{
		nWaveNum = 200 + wDress*10 + 6;
	}
	else if ( m_dwCurrFrame == m_dwFstFrame+1 && m_bCurrMtn == _MT_MON_ATTACK_B )	// 일반공격2.
	{
		nWaveNum = 200 + wDress*10 + 7;
	}
	else if ( m_dwCurrFrame == m_dwFstFrame+1 && m_bCurrMtn == _MT_MON_SPELL_A )	// 마법공격1.
	{
		nWaveNum = 200 + wDress*10 + 8;
	}
	else if ( m_dwCurrFrame == m_dwFstFrame+1 && m_bCurrMtn == _MT_MON_SPELL_B )	// 마법공격2.
	{
		nWaveNum = 200 + wDress*10 + 9;
	}

	// 발석차 연노차일 경우 움직이는 소리 내 준다.
	if ( ( wDress == 167 || wDress == 169 ) &&  m_bCurrMtn == _MT_MON_WALK )
	{
		if ( m_dwCurrFrame == m_dwEndFrame-5 || m_bBackStepFrame == m_dwEndFrame-5 || m_bBackStepFrame == m_bBackStepFrameCnt-2  )
			nWaveNum = 200 + wDress*10 + 9;
	}

	if ( nWaveNum != -1 )
	{
		g_SoundManager.SndmngrPlayWavSound(nWaveNum, m_nPosX, m_nPosY);
	}

	nWaveNum = -1;
	if ( m_dwCurrFrame == m_dwFstFrame+1 && m_bCurrMtn == _MT_MON_HITTED )
	{
		if ( m_stHitter.bGender < 2 )
		{
			switch ( m_stHitter.bWeapon )
			{
/*				case 21: case 24: // 단검, 천군지장.
				case 8: case 9: // 목검, 아리수목검.
				case 18:  case 22:  case 23:  case 26:  case 27:  case 28:  case 30:  case 32:  // 사모검. 청동검. 철검. 청음검. 벽사검. 천령. 곡성검. 적혈마검.
				case 1:   case 4:  case 11:  case 13:  case 14:  case 20:  case 25:  case 29:  case 31:	 case 33:   // 유월도. 묵청대도. 육합도. 군도. 도룡보도. 사각도. 세첨도. 예도. 초혼도. 무명도.
					nWaveNum = 70;
					break;
				case 5:  case 10:  case 12: // 삼적대부. 청동도끼. 연자부.
				case 15:  // 파뇌진당.
					nWaveNum = 71;
					break;
				case 2:  case 3:  case 6:  case 7: case 16:  case 17: case 19:  // 삼지창. 천형목. 홍아창. 곡괭이. 청마창, 용아장. 제마봉
					nWaveNum = 72;
					break;
				default:
					nWaveNum = 73;	// 맨손.
					break;*/
				case 21:  // 단검.
					nWaveNum = 60;
					break;
				case 8: case 9: // 목검, 아리수목검.
					nWaveNum = 61;
					break;
				case 18:  case 22:  case 23:  case 26:  case 27:  case 28:  case 30:  case 32:  // 사모검. 청동검. 철검. 청음검. 벽사검. 천령. 곡성검. 적혈마검.
					nWaveNum = 62;
					break;
				case 1:   case 4:  case 11:  case 13:  case 14:  case 20:  case 25:  case 29:  case 31:	 case 33:  case 38:  case 40:  case 45:  case 46: // 유월도. 묵청대도. 육합도. 군도. 도룡보도. 사각도. 세첨도. 예도. 초혼도. 무명도. 나락. 도철. 혼천도. 혼천마도
					nWaveNum = 63;
					break;
				case 5:  case 10:  case 12: // 삼적대부. 청동도끼. 연자부.
					nWaveNum = 64;
					break;
				case 15:  // 파뇌진당.
					nWaveNum = 65;
					break;
				case 2:  case 3:  case 6:  case 7: case 16:  case 17: case 19:  case 24: // 삼지창. 천형목. 홍아창. 곡괭이. 청마창, 용아장. 제마봉. 천군지장
					nWaveNum = 72;
					break;
				default:
					nWaveNum = 73;	// 맨손.
					break;
			}
		}
	}

	if ( nWaveNum != -1 )
	{
		g_SoundManager.SndmngrPlayWavSound(nWaveNum, m_nPosX, m_nPosY);
	}
}



/******************************************************************************************************************

	함수명 : CActor::SetMoving()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CActor::SetMoving()
{	
	WORD wFrmCnt  = (WORD)(m_dwEndFrame  - m_dwFstFrame);
	WORD wCurrFrm = (WORD)(m_dwCurrFrame - m_dwFstFrame);

	if ( wFrmCnt == 0 )
	{
		return;
	}

	INT nMoveFrame = 6;

	if ( m_stFeature.bGender == _GENDER_MON )
	{
		WORD wDress = MAKEWORD(m_stFeature.bDress, m_stFeature.bHair);

		// 이부분이 212, 213 가무녀 예외처리 부분 by eriastoa 2006.05.07
		// 원래는 6프레임인데 가무녀의 경우 10프레임이다
		// 222 진룡마왕 10프레임 예외처리 추가
		// 223 진룡여왕 10프레임 by eriastoa 2006.05.08
		/*#define _MONNUM_CHIUOO	220
#define _MONNUM_JINRYONGMA	221
#define _MONNUM_JINRYONGYO	222
#define _MONNUM_MASSO		223
#define _MONNUM_MACHONG		224
#define _MONNUM_YOUMGONMA	225*/
		if ( wDress == 212 || wDress == 213 || wDress == _MONNUM_JINRYONGMA || wDress == _MONNUM_JINRYONGYO )
		{
			nMoveFrame = 10;
		}
	}

	switch ( m_bMoveDir )
	{
	case _DIRECTION_LIST_1:
		m_nShiftPixelX =  0;

		if ( wCurrFrm < (nMoveFrame-m_bMoveNextFrmCnt) )
			m_nShiftPixelY = -(_CELL_HEIGHT/wFrmCnt * (wCurrFrm+1))*m_bMoveSpeed;
		else
			m_nShiftPixelY =  (_CELL_HEIGHT/wFrmCnt * (wFrmCnt - wCurrFrm -1))*m_bMoveSpeed;
		break;
	case _DIRECTION_LIST_2:
		if ( wCurrFrm < (nMoveFrame-m_bMoveNextFrmCnt) )
			m_nShiftPixelX =  (_CELL_WIDTH /wFrmCnt * (wCurrFrm+1))*m_bMoveSpeed;
		else
			m_nShiftPixelX = -(_CELL_WIDTH /wFrmCnt * (wFrmCnt - wCurrFrm -1))*m_bMoveSpeed;

		if ( wCurrFrm < (nMoveFrame-m_bMoveNextFrmCnt) )
			m_nShiftPixelY = -(_CELL_HEIGHT/wFrmCnt * (wCurrFrm+1))*m_bMoveSpeed;
		else
			m_nShiftPixelY =  (_CELL_HEIGHT/wFrmCnt * (wFrmCnt - wCurrFrm -1))*m_bMoveSpeed;
		break;
	case _DIRECTION_LIST_3:
		if ( wCurrFrm < (nMoveFrame-m_bMoveNextFrmCnt) )
			m_nShiftPixelX =  (_CELL_WIDTH /wFrmCnt * (wCurrFrm+1))*m_bMoveSpeed;
		else
			m_nShiftPixelX = -(_CELL_WIDTH /wFrmCnt * (wFrmCnt - wCurrFrm -1))*m_bMoveSpeed;

		m_nShiftPixelY = 0;
		break;
	case _DIRECTION_LIST_4:
		if ( wCurrFrm < (nMoveFrame-m_bMoveNextFrmCnt) )
			m_nShiftPixelX =  (_CELL_WIDTH /wFrmCnt * (wCurrFrm+1))*m_bMoveSpeed;
		else
			m_nShiftPixelX = -(_CELL_WIDTH /wFrmCnt * (wFrmCnt - wCurrFrm -1))*m_bMoveSpeed;

		if ( wCurrFrm < (nMoveFrame-m_bMoveNextFrmCnt) )
			m_nShiftPixelY =  (_CELL_HEIGHT/wFrmCnt * (wCurrFrm+1))*m_bMoveSpeed;
		else
			m_nShiftPixelY = -(_CELL_HEIGHT/wFrmCnt * (wFrmCnt - wCurrFrm -1))*m_bMoveSpeed;
		break;
	case _DIRECTION_LIST_5:
		m_nShiftPixelX =  0;

		if ( wCurrFrm < (nMoveFrame-m_bMoveNextFrmCnt) )
			m_nShiftPixelY =  (_CELL_HEIGHT/wFrmCnt * (wCurrFrm+1))*m_bMoveSpeed;
		else
			m_nShiftPixelY = -(_CELL_HEIGHT/wFrmCnt * (wFrmCnt - wCurrFrm -1))*m_bMoveSpeed;
		break;
	case _DIRECTION_LIST_6:
		if ( wCurrFrm < (nMoveFrame-m_bMoveNextFrmCnt) )
			m_nShiftPixelX = -(_CELL_WIDTH /wFrmCnt * (wCurrFrm+1))*m_bMoveSpeed;
		else
			m_nShiftPixelX =  (_CELL_WIDTH /wFrmCnt * (wFrmCnt - wCurrFrm -1))*m_bMoveSpeed;

		if ( wCurrFrm < (nMoveFrame-m_bMoveNextFrmCnt) )
			m_nShiftPixelY =  (_CELL_HEIGHT/wFrmCnt * (wCurrFrm+1))*m_bMoveSpeed;
		else
			m_nShiftPixelY = -(_CELL_HEIGHT/wFrmCnt * (wFrmCnt - wCurrFrm -1))*m_bMoveSpeed;
		break;
	case _DIRECTION_LIST_7:
		if ( wCurrFrm < (nMoveFrame-m_bMoveNextFrmCnt) )
			m_nShiftPixelX = -(_CELL_WIDTH /wFrmCnt * (wCurrFrm+1))*m_bMoveSpeed;
		else
			m_nShiftPixelX =  (_CELL_WIDTH /wFrmCnt * (wFrmCnt - wCurrFrm -1))*m_bMoveSpeed;

		m_nShiftPixelY =  0;
		break;
	case _DIRECTION_LIST_8:
		if ( wCurrFrm < (nMoveFrame-m_bMoveNextFrmCnt) )
			m_nShiftPixelX = -(_CELL_WIDTH /wFrmCnt * (wCurrFrm+1))*m_bMoveSpeed;
		else
			m_nShiftPixelX =  (_CELL_WIDTH /wFrmCnt * (wFrmCnt - wCurrFrm -1))*m_bMoveSpeed;

		if ( wCurrFrm < (nMoveFrame-m_bMoveNextFrmCnt) )
			m_nShiftPixelY = -(_CELL_HEIGHT/wFrmCnt * (wCurrFrm+1))*m_bMoveSpeed;
		else
			m_nShiftPixelY =  (_CELL_HEIGHT/wFrmCnt * (wFrmCnt - wCurrFrm -1))*m_bMoveSpeed;
		break;	
	}
}



/******************************************************************************************************************

	함수명 : CActor::SetBackStepMoving()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CActor::SetBackStepMoving()
{	
	if ( m_bBackStepFrameCnt == 0 )
	{
		return;
	}

	INT nMoveFrame = 6;

	if ( m_stFeature.bGender == _GENDER_MON )
	{
		WORD wDress = MAKEWORD(m_stFeature.bDress, m_stFeature.bHair);

		// 이부분이 212, 213 가무녀 예외처리 부분 by eriastoa 2006.05.07
		// 원래는 6프레임인데 가무녀의 경우 10프레임이다
		// 222 진룡마왕 10프레임 예외처리 추가
		// 223 진룡여왕 10프레임 by eriastoa 2006.05.08
		/*#define _MONNUM_CHIUOO	220
#define _MONNUM_JINRYONGMA	221
#define _MONNUM_JINRYONGYO	222
#define _MONNUM_MASSO		223
#define _MONNUM_MACHONG		224
#define _MONNUM_YOUMGONMA	225*/
		if ( wDress == 212 || wDress == 213 || wDress == _MONNUM_JINRYONGMA || wDress == _MONNUM_JINRYONGYO )
		{
			nMoveFrame = 10;
		}
	}	

	switch ( m_bMoveDir )
	{
	case _DIRECTION_LIST_1:
		m_nShiftPixelX =  0;

		if ( m_bBackStepFrame < (nMoveFrame-m_bMoveNextFrmCnt) )
			m_nShiftPixelY = -(_CELL_HEIGHT/m_bBackStepFrameCnt * (m_bBackStepFrame+1))*m_bMoveSpeed;
		else
			m_nShiftPixelY =  (_CELL_HEIGHT/m_bBackStepFrameCnt * (m_bBackStepFrameCnt - m_bBackStepFrame -1))*m_bMoveSpeed;
		break;
	case _DIRECTION_LIST_2:
		if ( m_bBackStepFrame < (nMoveFrame-m_bMoveNextFrmCnt) )
			m_nShiftPixelX =  (_CELL_WIDTH /m_bBackStepFrameCnt * (m_bBackStepFrame+1))*m_bMoveSpeed;
		else
			m_nShiftPixelX = -(_CELL_WIDTH /m_bBackStepFrameCnt * (m_bBackStepFrameCnt - m_bBackStepFrame -1))*m_bMoveSpeed;

		if ( m_bBackStepFrame < (nMoveFrame-m_bMoveNextFrmCnt) )
			m_nShiftPixelY = -(_CELL_HEIGHT/m_bBackStepFrameCnt * (m_bBackStepFrame+1))*m_bMoveSpeed;
		else
			m_nShiftPixelY =  (_CELL_HEIGHT/m_bBackStepFrameCnt * (m_bBackStepFrameCnt - m_bBackStepFrame -1))*m_bMoveSpeed;
		break;
	case _DIRECTION_LIST_3:
		if ( m_bBackStepFrame < (nMoveFrame-m_bMoveNextFrmCnt) )
			m_nShiftPixelX =  (_CELL_WIDTH /m_bBackStepFrameCnt * (m_bBackStepFrame+1))*m_bMoveSpeed;
		else
			m_nShiftPixelX = -(_CELL_WIDTH /m_bBackStepFrameCnt * (m_bBackStepFrameCnt - m_bBackStepFrame -1))*m_bMoveSpeed;

		m_nShiftPixelY = 0;
		break;
	case _DIRECTION_LIST_4:
		if ( m_bBackStepFrame < (nMoveFrame-m_bMoveNextFrmCnt) )
			m_nShiftPixelX =  (_CELL_WIDTH /m_bBackStepFrameCnt * (m_bBackStepFrame+1))*m_bMoveSpeed;
		else
			m_nShiftPixelX = -(_CELL_WIDTH /m_bBackStepFrameCnt * (m_bBackStepFrameCnt - m_bBackStepFrame -1))*m_bMoveSpeed;

		if ( m_bBackStepFrame < (nMoveFrame-m_bMoveNextFrmCnt) )
			m_nShiftPixelY =  (_CELL_HEIGHT/m_bBackStepFrameCnt * (m_bBackStepFrame+1))*m_bMoveSpeed;
		else
			m_nShiftPixelY = -(_CELL_HEIGHT/m_bBackStepFrameCnt * (m_bBackStepFrameCnt - m_bBackStepFrame -1))*m_bMoveSpeed;
		break;
	case _DIRECTION_LIST_5:
		m_nShiftPixelX =  0;

		if ( m_bBackStepFrame < (nMoveFrame-m_bMoveNextFrmCnt) )
			m_nShiftPixelY =  (_CELL_HEIGHT/m_bBackStepFrameCnt * (m_bBackStepFrame+1))*m_bMoveSpeed;
		else
			m_nShiftPixelY = -(_CELL_HEIGHT/m_bBackStepFrameCnt * (m_bBackStepFrameCnt - m_bBackStepFrame -1))*m_bMoveSpeed;
		break;
	case _DIRECTION_LIST_6:
		if ( m_bBackStepFrame < (nMoveFrame-m_bMoveNextFrmCnt) )
			m_nShiftPixelX = -(_CELL_WIDTH /m_bBackStepFrameCnt * (m_bBackStepFrame+1))*m_bMoveSpeed;
		else
			m_nShiftPixelX =  (_CELL_WIDTH /m_bBackStepFrameCnt * (m_bBackStepFrameCnt - m_bBackStepFrame -1))*m_bMoveSpeed;

		if ( m_bBackStepFrame < (nMoveFrame-m_bMoveNextFrmCnt) )
			m_nShiftPixelY =  (_CELL_HEIGHT/m_bBackStepFrameCnt * (m_bBackStepFrame+1))*m_bMoveSpeed;
		else
			m_nShiftPixelY = -(_CELL_HEIGHT/m_bBackStepFrameCnt * (m_bBackStepFrameCnt - m_bBackStepFrame -1))*m_bMoveSpeed;
		break;
	case _DIRECTION_LIST_7:
		if ( m_bBackStepFrame < (nMoveFrame-m_bMoveNextFrmCnt) )
			m_nShiftPixelX = -(_CELL_WIDTH /m_bBackStepFrameCnt * (m_bBackStepFrame+1))*m_bMoveSpeed;
		else
			m_nShiftPixelX =  (_CELL_WIDTH /m_bBackStepFrameCnt * (m_bBackStepFrameCnt - m_bBackStepFrame -1))*m_bMoveSpeed;

		m_nShiftPixelY =  0;
		break;
	case _DIRECTION_LIST_8:
		if ( m_bBackStepFrame < (nMoveFrame-m_bMoveNextFrmCnt) )
			m_nShiftPixelX = -(_CELL_WIDTH /m_bBackStepFrameCnt * (m_bBackStepFrame+1))*m_bMoveSpeed;
		else
			m_nShiftPixelX =  (_CELL_WIDTH /m_bBackStepFrameCnt * (m_bBackStepFrameCnt - m_bBackStepFrame -1))*m_bMoveSpeed;

		if ( m_bBackStepFrame < (nMoveFrame-m_bMoveNextFrmCnt) )
			m_nShiftPixelY = -(_CELL_HEIGHT/m_bBackStepFrameCnt * (m_bBackStepFrame+1))*m_bMoveSpeed;
		else
			m_nShiftPixelY =  (_CELL_HEIGHT/m_bBackStepFrameCnt * (m_bBackStepFrameCnt - m_bBackStepFrame -1))*m_bMoveSpeed;
		break;	
	}
}


/******************************************************************************************************************

	함수명 : CActor::SetMoved()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CActor::SetMoved()
{
	switch ( m_bMoveDir )
	{
	case _DIRECTION_LIST_1:
		m_nShiftTileX =  0;
		m_nShiftTileY = -m_bMoveSpeed;
		break;
	case _DIRECTION_LIST_2:
		m_nShiftTileX =  m_bMoveSpeed;
		m_nShiftTileY = -m_bMoveSpeed;
		break;
	case _DIRECTION_LIST_3:
		m_nShiftTileX =  m_bMoveSpeed;
		m_nShiftTileY =  0;
		break;
	case _DIRECTION_LIST_4:
		m_nShiftTileX =  m_bMoveSpeed;
		m_nShiftTileY =  m_bMoveSpeed;
		break;
	case _DIRECTION_LIST_5:
		m_nShiftTileX =  0;
		m_nShiftTileY =  m_bMoveSpeed;
		break;
	case _DIRECTION_LIST_6:
		m_nShiftTileX = -m_bMoveSpeed;
		m_nShiftTileY =  m_bMoveSpeed;
		break;
	case _DIRECTION_LIST_7:
		m_nShiftTileX = -m_bMoveSpeed;
		m_nShiftTileY =  0;
		break;
	case _DIRECTION_LIST_8:
		m_nShiftTileX = -m_bMoveSpeed;
		m_nShiftTileY = -m_bMoveSpeed;
		break;
	}
	m_nPosX += m_nShiftTileX;
	m_nPosY += m_nShiftTileY;
	m_nShiftPixelX = 0;
	m_nShiftPixelY = 0;
}


/******************************************************************************************************************

	함수명 : CActor::
	Packet()

	작성자 : 
	작성일 : 

	목적   : SM_WALK, SM_DEATH, SM_TURN, SM_RUN, SM_DIGUP 메시지에 사용한다.
	입력   : LPPACKETMSG lpPacketMsg
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CActor::OnCharDescPacket(LPPACKETMSG lpPacketMsg)
{
	CHARDESC	stCharDesc;
	FEATURE		stFeature;
	fnDecode6BitBuf(lpPacketMsg->szEncodeData, (char*)&stCharDesc, sizeof(CHARDESC));

	memcpy(&stFeature, &stCharDesc.nFeature, sizeof(FEATURE));
	m_nCharState			= stCharDesc.nStatus;
	
	if( m_nCharState & 0X2 )
		m_bOpenHealth = TRUE;
	else
		m_bOpenHealth = FALSE;

	if ( stFeature.bGender == _GENDER_MON )
		ChangeFeature(stFeature);
}

VOID CActor::OnChangeNameClr(LPPACKETMSG lpPacketMsg)
{
	m_dwNameClr = GetUserNameColor((BYTE)lpPacketMsg->stDefMsg.wParam);
}

VOID CActor::OnChangeLight(LPPACKETMSG lpPacketMsg)
{
	m_bLightSize = (BYTE)(lpPacketMsg->stDefMsg.wParam);
}

VOID CActor::OnOpenHealth(LPPACKETMSG lpPacketMsg)
{
	m_bOpenHealth = TRUE;
}

VOID CActor::OnCloseHealth(LPPACKETMSG lpPacketMsg)
{
	m_bOpenHealth = FALSE;
}

VOID CActor::OnCharStatusChanged(LPPACKETMSG lpPacketMsg)
{
	m_nCharState = MAKELONG(lpPacketMsg->stDefMsg.wParam, lpPacketMsg->stDefMsg.wTag);

	if ( m_nCharState == 0 )
		m_bIsSturn = FALSE;

	if( m_nCharState & 0X2 )
		m_bOpenHealth = TRUE;
	else
		m_bOpenHealth = FALSE;
}

VOID CActor::OnSpaceMoveShow(LPPACKETMSG lpPacketMsg)
{
	BYTE		bDir;
	CHARDESC	stCharDesc;
	FEATURE		stFeature;
	INT			nPos;
	m_nPosX = lpPacketMsg->stDefMsg.wParam;
	m_nPosY = lpPacketMsg->stDefMsg.wTag;
	bDir		 = LOBYTE(lpPacketMsg->stDefMsg.wSeries);
	m_bLightSize = HIBYTE(lpPacketMsg->stDefMsg.wSeries);

	fnDecode6BitBuf(lpPacketMsg->szEncodeData, (char*)&stCharDesc, sizeof(CHARDESC));

	g_SoundManager.SndmngrPlayWavSound(_SOUND_SPACEMOVE_OUT, m_nPosX, m_nPosY);

	if (strlen(lpPacketMsg->szEncodeData) > _CHARDESCSIZE)
	{
/*		CHAR pszDecodeMsg[1024];
		CHAR *pszStr1;
		CHAR *pszStr2;

		nPos = fnDecode6BitBuf(&lpPacketMsg->szEncodeData[_CHARDESCSIZE], pszDecodeMsg, sizeof(pszDecodeMsg));
		pszDecodeMsg[nPos] = '\0';

		if ( pszStr1 = strchr(pszDecodeMsg, '\\') )
		{
			*pszStr1++ = '\0';								// pszDecodeMsg == m_szName;

			strcpy(m_szName, pszDecodeMsg);

			if ( pszStr2 = strrchr(pszStr1, '/') )
			{
				*pszStr2++ = '\0';							// pszStr1 == m_GuildName;

				strcpy(m_szGuildName, pszStr1);

				if ( pszStr2[0] != NULL )
				{
					m_dwNameClr = GetUserNameColor(atoi(pszStr2));
				}
			}
		}
		else
		{
			if ( pszStr2 = strrchr(pszDecodeMsg, '/') )
			{
				*pszStr2++ = '\0';							// pszStr2 == m_szName;
				strcpy(m_szName, pszDecodeMsg);

				if ( pszStr2[0] != NULL )
				{
					m_dwNameClr = GetUserNameColor(atoi(pszStr2));
				}
			}
		}
*/
		CHAR szName[128];
		nPos = fnDecode6BitBuf(&lpPacketMsg->szEncodeData[_CHARDESCSIZE], szName, sizeof(szName));
		szName[nPos] = '\0';

		CheckMultiLineName(szName);

		CHAR* szClr = strrchr(szName, '/');

		if ( szClr )
		{
			m_dwNameClr = GetUserNameColor((BYTE)(atoi(szClr+1)));
			*szClr = '\0';
		}
	}

	memcpy(&stFeature, &stCharDesc.nFeature, sizeof(FEATURE));
	m_nCharState			= stCharDesc.nStatus;

	if( m_nCharState & 0X2 )
		m_bOpenHealth = TRUE;
	else
		m_bOpenHealth = FALSE;

	ChangeFeature(stFeature);

	CMagic* pxMagic;
	// 아공전서로 다른맵에 나타나기.
	if ( lpPacketMsg->stDefMsg.wIdent == SM_SPACEMOVE_SHOW )
	{
		pxMagic = new CMagic;
		if ( pxMagic->CreateMagic(_SKILL_SPACEMOVESHOW2, m_nPosX, m_nPosY, m_nPosX, m_nPosY, NULL, 0) )
		{
			g_xGameProc.m_xMagicList.Insert (pxMagic);	
		}
		else
		{
			delete pxMagic;
		}
	}
	else if ( lpPacketMsg->stDefMsg.wIdent == SM_PULL_SHOW )
	{
		pxMagic = new CMagic;
		if ( pxMagic->CreateMagic(_SKILL_PULLSHOW, m_nPosX, m_nPosY, m_nPosX, m_nPosY, NULL, 0) )
		{
			g_xGameProc.m_xMagicList.Insert (pxMagic);	
		}
		else
		{
			delete pxMagic;
		}
	}	

	SetMotionFrame(_MT_MON_STAND, bDir);
}


VOID CActor::OnSpaceMoveHide(LPPACKETMSG lpPacketMsg)
{
//	m_nPosX = lpPacketMsg->stDefMsg.wParam;
//	m_nPosY = lpPacketMsg->stDefMsg.wTag;
	CMagic* pxMagic;

	g_SoundManager.SndmngrPlayWavSound(_SOUND_SPACEMOVE_IN, m_nPosX, m_nPosY);
	
	// 아공전서로 다른맵에 나타나기.
	if ( lpPacketMsg->stDefMsg.wIdent == SM_SPACEMOVE_HIDE )
	{
		pxMagic = new CMagic;
		if ( pxMagic->CreateMagic(_SKILL_SPACEMOVEHIDE2, m_nPosX, m_nPosY, m_nPosX, m_nPosY, NULL, 0) )
		{
			g_xGameProc.m_xMagicList.Insert (pxMagic);	
		}
		else
		{
			delete pxMagic;
		}
	}
	// 아공행법으로 새로운맵으로 나타나기.
	else if ( lpPacketMsg->stDefMsg.wIdent == SM_SPACEMOVE_HIDE2 )
	{	
		pxMagic = new CMagic;
		if ( pxMagic->CreateMagic(_SKILL_SPACEMOVESHOW, m_nPosX, m_nPosY, m_nPosX, m_nPosY, NULL, 0) )
		{
			g_xGameProc.m_xMagicList.Insert (pxMagic);	
		}
		else
		{
			delete pxMagic;
		}
	}
}

VOID CActor::OnFeatureChanged(LPPACKETMSG lpPacketMsg)
{
	FEATURE stFeature;
	LONG nFeature	  = MAKELONG(lpPacketMsg->stDefMsg.wParam, lpPacketMsg->stDefMsg.wTag);

	memcpy(&stFeature, &nFeature, sizeof(LONG));

	if ( stFeature.bGender == _GENDER_MON || stFeature.bGender == _GENDER_FLAG )
	{
		ChangeFeature(stFeature);
	}
}

VOID CActor::OnHealthSpellChanged(LPPACKETMSG lpPacketMsg)
{
	if ( lpPacketMsg->stDefMsg.wParam - m_wHP != 0 && m_wHP != 0 && g_xGameProc.m_bShowBloodNum )
	{
		m_nShowBlood[m_nShowBloodIdx] = lpPacketMsg->stDefMsg.wParam - m_wHP;
		m_ptShowBlood[m_nShowBloodIdx].x = m_nScrnPosX;
		m_ptShowBlood[m_nShowBloodIdx].y = m_nScrnPosY;
		m_dwShowBloodTimer[m_nShowBloodIdx] = 0;

		m_nShowBloodIdx++;

		if ( m_nShowBloodIdx > 7 )
			m_nShowBloodIdx = 0;
	}

	FLOAT wHPRate = 0.0f;
	if ( lpPacketMsg->stDefMsg.wSeries )
	{
		wHPRate = (FLOAT)((FLOAT)lpPacketMsg->stDefMsg.wParam/(FLOAT)lpPacketMsg->stDefMsg.wSeries);
	}						
	m_wHP			= lpPacketMsg->stDefMsg.wParam;
	m_wMP			= lpPacketMsg->stDefMsg.wTag;
	m_wMAXHP		= lpPacketMsg->stDefMsg.wSeries;
	m_bHPPercent	= (BYTE)(wHPRate * 100);
}


VOID CActor::OnWalk(LPPACKETMSG lpPacketMsg)
{
	BYTE		bDir;
	CHARDESC	stCharDesc;
	FEATURE		stFeature;

	bDir		 = LOBYTE(lpPacketMsg->stDefMsg.wSeries);
	m_bLightSize = HIBYTE(lpPacketMsg->stDefMsg.wSeries);

	// 좀비 억지로 살리기
	m_bIsDead = 0;

	fnDecode6BitBuf(lpPacketMsg->szEncodeData, (char*)&stCharDesc, sizeof(CHARDESC));

	memcpy(&stFeature, &stCharDesc.nFeature, sizeof(FEATURE));
	m_nCharState			= stCharDesc.nStatus;

	if( m_nCharState & 0X2 )
		m_bOpenHealth = TRUE;
	else
		m_bOpenHealth = FALSE;

	if ( stFeature.bGender == _GENDER_MON )
		ChangeFeature(stFeature);

	// 2006.07.06 가무녀 움직임 수정
	/*if ( stFeature.bGender != _GENDER_MAN && stFeature.bGender != _GENDER_WOMAN && stFeature.bGender != _GENDER_NPC &&
		stFeature.bGender != _GENDER_FLAG )
	{
		stFeature.bGender = _GENDER_MON;
		ChangeFeature(stFeature);
	}*/

	SetMotionFrame(_MT_MON_WALK, bDir);
	m_bMoveSpeed = _SPEED_WALK;

	g_xGameProc.m_xMap.GetLastTile(lpPacketMsg->stDefMsg.wParam, lpPacketMsg->stDefMsg.wTag, bDir, m_nPosX, m_nPosY, m_bMoveSpeed);

	SetMoving();
}


VOID CActor::OnUserName(LPPACKETMSG lpPacketMsg)
{
	char szDecodeMsg[1024];
	char *pszGuildName;
	INT nCnt = 0;

	INT nPos = fnDecode6BitBuf(lpPacketMsg->szEncodeData, szDecodeMsg, sizeof(szDecodeMsg));
	szDecodeMsg[nPos] = '\0';
	CheckMultiLineName(szDecodeMsg);

	m_dwNameClr = GetUserNameColor((BYTE)lpPacketMsg->stDefMsg.wParam);
	strcpy(m_szName, m_szShowName[0]);
/*
	if ( pszGuildName = strchr(szDecodeMsg, '\\') )
	{
		*pszGuildName++ = '\0';
	}

	m_dwNameClr = GetUserNameColor((BYTE)lpPacketMsg->stDefMsg.wParam);
	strcpy(m_szName, szDecodeMsg);

	if ( pszGuildName )
	{
		strcpy(m_szGuildName, pszGuildName);
	}
*/
}


BOOL CActor::CheckMultiLineName(char *pszName)
{
	char *pszGuildName;
	INT nCnt = 0;

	for ( INT nI=0; nI<3; nI++ )
		ZeroMemory(m_szShowName[nI], 64);

//	CHAR szTemp[128];

//	sprintf(szTemp, pszName);

//  NPC Name
	if ( pszGuildName = strchr(pszName, '_') )
	{
		*pszGuildName++ = '\0';
		strcpy(m_szShowName[nCnt], pszName);
		pszName = pszGuildName;

		if ( pszGuildName = strchr(pszName, '/') )
		{
			*pszGuildName++ = '\0';
			strcpy(m_szShowName[nCnt+1], pszName);
			sprintf(pszName, "/%s", pszGuildName);
			pszGuildName = NULL;
		}
		else
		{
			strcpy(m_szShowName[nCnt+1], pszName);
		}

	}
	else
	{
		do
		{
			if ( pszGuildName = strchr(pszName, '\r') )
			{
				*pszGuildName++ = '\0';
				strcpy(m_szShowName[nCnt], pszName);
			}
			else
			{
				if ( pszGuildName = strchr(pszName, '/') )
				{
					*pszGuildName++ = '\0';
					strcpy(m_szShowName[nCnt], pszName);
					sprintf(pszName, "/%s", pszGuildName);
					pszGuildName = NULL;
					break;
				}
				else
				{
					pszGuildName = NULL;
					strcpy(m_szShowName[nCnt], pszName);
				}
			}

			if ( pszGuildName )
				strcpy(pszName, pszGuildName);
			nCnt++;

		}while(pszGuildName != NULL && nCnt<3);
	}

	if ( m_szShowName[0] != NULL )
		sprintf(m_szName, m_szShowName[0]);

//	CHAR* szClr;
//	if ( szClr = strrchr(pszName, '/') )
//	{
//		*szClr++ = '\0';
//		strcpy(m_szName, pszName);
//		sprintf(pszName, "/%s", szClr);
//	}

//	INT nTest = strlen(m_szName);

//	if ( nTest > 30 )
//		INT nbreak = 0;
	m_bNeedLoadFameImg = TRUE;
	return TRUE;
}


VOID CActor::OnTurn(LPPACKETMSG lpPacketMsg)
{
	BYTE		bDir;
	CHARDESC	stCharDesc;
	FEATURE		stFeature;
	INT			nPos;
	m_nPosX = lpPacketMsg->stDefMsg.wParam;
	m_nPosY = lpPacketMsg->stDefMsg.wTag;
	bDir		 = LOBYTE(lpPacketMsg->stDefMsg.wSeries);
	m_bLightSize = HIBYTE(lpPacketMsg->stDefMsg.wSeries);

	fnDecode6BitBuf(lpPacketMsg->szEncodeData, (char*)&stCharDesc, sizeof(CHARDESC));

	if ( lpPacketMsg->stDefMsg.wIdent == SM_REVIVAL )
	{
		m_bIsDead = FALSE;
		m_nABlendDelay = 600;
		m_nABlendCurrDelay = 0;
	}

	if (strlen(lpPacketMsg->szEncodeData) > _CHARDESCSIZE)
	{
		CHAR szName[64];
		nPos = fnDecode6BitBuf(&lpPacketMsg->szEncodeData[_CHARDESCSIZE], szName, sizeof(szName));
		szName[nPos] = '\0';

		CheckMultiLineName(szName);

		CHAR* szClr = strrchr(szName, '/');

		if ( szClr )
		{
			m_dwNameClr = GetUserNameColor((BYTE)atoi(szClr+1));
			*szClr = '\0';
		}
	}

	memcpy(&stFeature, &stCharDesc.nFeature, sizeof(FEATURE));
	m_nCharState			= stCharDesc.nStatus;

	if( m_nCharState & 0X2 )
		m_bOpenHealth = TRUE;
	else
		m_bOpenHealth = FALSE;

	if ( stFeature.bGender == _GENDER_MON )
		ChangeFeature(stFeature);

	// 2006.07.06 가무녀 움직임 수정
	/*if ( stFeature.bGender != _GENDER_MAN && stFeature.bGender != _GENDER_WOMAN && stFeature.bGender != _GENDER_NPC &&
		stFeature.bGender != _GENDER_FLAG )
	{
		stFeature.bGender = _GENDER_MON;
		ChangeFeature(stFeature);
	}*/

	SetMotionFrame(_MT_MON_STAND, bDir);

	if( m_nCharState & 0X1 )		// 석화상태.
	{
		WORD wDress;
		if ( m_stFeature.bGender == _GENDER_MON )
		{
			wDress = MAKEWORD(m_stFeature.bDress, m_stFeature.bHair);
		}
		else
		{
			wDress = m_stFeature.bDress;
		}

		switch ( wDress )
		{
		case 83: //주마신장.
		case 84: //주마호법.
		case 85: //주마왕.
			SetMotionFrame(_MT_MON_APPEAR, 0);
			m_dwEndFrame = m_dwFstFrame + 1;
			m_bCurrMtn = _MT_MON_STAND;
		}
	}
}

VOID CActor::OnDigup(LPPACKETMSG lpPacketMsg)
{
	//MESSAGEBODYWL ????????
	BYTE bDir;
	m_nPosX      = lpPacketMsg->stDefMsg.wParam;
	m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
	bDir		 = LOBYTE(lpPacketMsg->stDefMsg.wSeries);
	m_bLightSize = HIBYTE(lpPacketMsg->stDefMsg.wSeries);
	OnCharDescPacket(lpPacketMsg);
	m_bReverse = FALSE;

	LPEVENTIMG pstEvent;

	WORD wDress;
	if ( m_stFeature.bGender == _GENDER_MON )
	{
		wDress = MAKEWORD(m_stFeature.bDress, m_stFeature.bHair);
	}
	else
	{
		wDress = m_stFeature.bDress;
	}
	
	switch ( wDress )
	{
	case 3:
		m_bReverse = TRUE;
		break;
	case 4: //석장인.
		{
			if ( g_xGameProc.m_bShowMonEffect )
			{
				pstEvent = new EVENTIMG;

				pstEvent->nEventID = 0;
				pstEvent->nType	   = 0;
				pstEvent->dwTick  = timeGetTime();
				pstEvent->nTileX = m_nPosX;
				pstEvent->nTileY = m_nPosY;

				pstEvent->dwLifeTime = 60000;
				pstEvent->wFrameNum = (WORD)(200+bDir);
				pstEvent->wOutDelay = 1200;

				pstEvent->bUseAlpha = FALSE;

				g_xGameProc.m_stEventImgList.Insert (pstEvent);
			}
		}		
		break;
	case 49: //땅뚫고 올라온 좀비.
		{
			if ( g_xGameProc.m_bShowMonEffect )
			{
				pstEvent = new EVENTIMG;

				pstEvent->nEventID = 0;
				pstEvent->nType	   = 0;
				pstEvent->dwTick  = timeGetTime();
				pstEvent->nTileX = m_nPosX;
				pstEvent->nTileY = m_nPosY;

				pstEvent->dwLifeTime = 60000;
				pstEvent->wFrameNum = WORD(240+bDir);
				pstEvent->wOutDelay = 1200;

				pstEvent->bUseAlpha = FALSE;

				g_xGameProc.m_stEventImgList.Insert (pstEvent);
			}
		}		
		break;
	case 85: //주마왕.
		bDir = 0;
		break;
	case 31: //식인초.		
		bDir = 0;
		m_bReverse = TRUE;
		break;
	case 56:
		{
			if ( g_xGameProc.m_bShowMonEffect )
			{
				CMagic* pxMagic;
				pxMagic = new CMagic;
				if ( pxMagic->CreateMagic(_SKILL_SKELLETON, m_nPosX, m_nPosY, m_nPosX, m_nPosY, NULL, 0) )
					g_xGameProc.m_xMagicList.Insert (pxMagic);	
				else
					delete pxMagic;
				break;
			}
		}
	case 89:
		{
			if ( g_xGameProc.m_bShowMonEffect )
			{
				CMagic* pxMagic;
				pxMagic = new CMagic;
				if ( pxMagic->CreateMagic(_SKILL_SINSU, m_nPosX, m_nPosY, m_nPosX, m_nPosY, NULL, 0) )
					g_xGameProc.m_xMagicList.Insert (pxMagic);	
				else
					delete pxMagic;
				break;
			}
		}
	case 530:		
	case 531:
	case 532:
	case 533:
		bDir = 0;
		m_bReverse = FALSE;
		break;
	}

	if ( m_stFeature.bGender == _GENDER_MAN || m_stFeature.bGender == _GENDER_WOMAN)
	{
		if ( g_xGameProc.m_bShowMonEffect )
		{
			CMagic* pxMagic;
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_SKILL_COPY, m_nPosX, m_nPosY, m_nPosX, m_nPosY, NULL, 0) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);	
			else
				delete pxMagic;
		}
	}
	else
	{
		m_bAppearState = _DIG_UP;
		SetMotionFrame(_MT_MON_APPEAR, bDir);
	}
}

VOID CActor::OnDigDown(LPPACKETMSG lpPacketMsg)
{
	BYTE bDir;	m_nPosX		 = lpPacketMsg->stDefMsg.wParam;
	m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
	bDir		 = m_bCurrDir;
	m_bReverse	 = TRUE;

	WORD wDress;
	if ( m_stFeature.bGender == _GENDER_MON )
	{
		wDress = MAKEWORD(m_stFeature.bDress, m_stFeature.bHair);
	}
	else
	{
		wDress = m_stFeature.bDress;
	}

	switch ( wDress )
	{
	case 3: 
//	case 90: // 신수 공격형.
		m_bReverse = FALSE;
		break;
	case 31: //식인초.		
		bDir = 0;
		m_bReverse = FALSE;
		break;
	case 530:
	case 531:
	case 532:
	case 533:
		bDir = 0;
		m_bReverse = TRUE;
		break;
	}

	if ( m_stFeature.bGender == _GENDER_MAN || m_stFeature.bGender == _GENDER_WOMAN)
	{
		if ( g_xGameProc.m_bShowMonEffect )
		{
			CMagic* pxMagic;
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_SKILL_COPYDIE, m_nPosX, m_nPosY, m_nPosX, m_nPosY, NULL, 0) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);	
			else
				delete pxMagic;
		}
	}
	else
	{
		m_bAppearState = _DIG_DOWN;

		SetMotionFrame(_MT_MON_APPEAR, bDir);
	}
}


VOID
CActor::MakeDeathEffect(WORD wDress)
{
	if ( !g_xGameProc.m_bShowMonEffect )
		return;

	switch ( wDress )
	{
		case 4:		// 석장인.
		{
			CMagic* pxMagic;
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_EXPLODE1, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);	
			else
				delete pxMagic;
			break;
		}
		case  5:		// 바쿠가르나.
		case  6:		// 바자울.
		case 11:		// 모디젼.
		case 19:		// 레디가르나.
		{
			CMagic* pxMagic;
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_SINGI_DIE, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);	
			else
				delete pxMagic;
			break;
		}
		case 40:		// 허수아비.
		{
			CMagic* pxMagic;
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_HUSU_DIE, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);	
			else
				delete pxMagic;
			break;
		}
		case 32:
		case 33:
		case 34:
		case 35:
		case 36:// 해골류죽기.
		{
			CMagic* pxMagic;
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_OMASKEL_DIE, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);	
			else
				delete pxMagic;
			break;
		}

		case 48:		// 좀비.
		{
			CMagic* pxMagic;
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_ZOMBIE_DIE, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);	
			else
				delete pxMagic;
			break;
		}
		case 99:		// 바오달드.
		{
			CMagic* pxMagic;
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_BAODIE, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);	
			else
				delete pxMagic;
			break;
		}
		case 120:		// 신기선보스.
		{
			CMagic* pxMagic;
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_BOSSDIE, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);	
			else
				delete pxMagic;
			break;
		}
		case 186:		// 타당가
		{
			CMagic* pxMagic;
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_TADANGGA_DIE, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this, 0, 800) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);	
			else
				delete pxMagic;
			break;
		}
		case 105:		// 폭안거미.
		{
			CMagic* pxMagic;
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_POKAN, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);	
			else
				delete pxMagic;
			break;
		}
		case 101:		// 비독주.
		{
			CMagic* pxMagic;
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_BIDOK, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);	
			else
				delete pxMagic;
			break;
		}
		case 130:		// 광명우사.
		{
			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_LIGHTRIGHTDIE, 0);

			m_bUseSwordEffect = TRUE;
			break;
		}
		case 131:		// 광명좌사.
		{
			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_LIGHTLEFTDIE, 0);
			m_bUseSwordEffect = TRUE;
			break;
		}
		case 138:		// 외팔이좀비.
		{
			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_ONEZOMBIEDIE, 0);
			m_bUseSwordEffect = TRUE;
			break;
		}
		case 140:		// 해골장수.
		{
			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_SKELCHIEFDIE, m_bCurrDir);
			m_bUseSwordEffect = TRUE;
			break;
		}
		case 142:		// 창칼활 해골.
		case 143:
		case 144:
		{
			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_WEAPONSKELDIE, 0);
			m_bUseSwordEffect = TRUE;
			break;
		}
		case 159:		// 화염돌사자
		{
			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_FLION_D, 0);
			m_bUseSwordEffect = TRUE;
			break;
		}
		case 160:		// 석화돌사자
		{
			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_SLION_D, 0);
			m_bUseSwordEffect = TRUE;
			break;
		}
		case 161:		// 무력신장
		{
			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_MURYUK_D, 0);
			m_bUseSwordEffect = TRUE;
			break;
		}
		case 3:
		case 15:
		case 16:
		{
			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_BARRACK_DIE, 0);
			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_BARRACK_DIE, 0);
			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_BARRACK_DIE, 0);
			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_BARRACK_DIE, 0);
			m_bUseSwordEffect = TRUE;
			break;
		}
		case 164:		// 진천마신.
		{
			CMagic* pxMagic;
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_MAWANG_D, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);	
			else
				delete pxMagic;
			break;
		}
		case 184:		// 누마사령법사
		{
			CMagic* pxMagic;
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_NUMABUBSA5, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this, 0, 800) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);	
			else
				delete pxMagic;
			break;
		}
		case 185:		// 누마친위대장
		case 182:		// 아룽가
		{
			CMagic* pxMagic;
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_NUMABODYGUARD_DIE, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);	
			else
				delete pxMagic;
			break;
		}		
		case 210:
		{
			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_GUARDGEN_DIE, 0);
			m_bUseSwordEffect = TRUE;
		}
		break;
		case 211:
		{
			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_DAWNQUEEN_DIE, 0);
			m_bUseSwordEffect = TRUE;
		}
		break;
		default :
		{
			break;
		}
	}
}


VOID CActor::OnDeath(LPPACKETMSG lpPacketMsg)
{
	BYTE bDir;
	m_nPosX = lpPacketMsg->stDefMsg.wParam;
	m_nPosY = lpPacketMsg->stDefMsg.wTag;
	bDir		 = LOBYTE(lpPacketMsg->stDefMsg.wSeries);
	m_bLightSize = HIBYTE(lpPacketMsg->stDefMsg.wSeries);
	m_bHPPercent = 0;
	OnCharDescPacket(lpPacketMsg);

	if ( g_xGameProc.m_pxSavedTargetActor && g_xGameProc.m_pxSavedTargetActor->m_nIdentity == lpPacketMsg->stDefMsg.nRecog )
	{
		g_xGameProc.m_pxSavedTargetActor = NULL;
	}

	if ( lpPacketMsg->stDefMsg.wIdent == SM_DEATH )			
	{
		SetMotionFrame(_MT_MON_DIE, bDir);
		m_dwCurrFrame = m_dwEndFrame - 1;
		m_bIsDead = TRUE;
	}
	else if ( lpPacketMsg->stDefMsg.wIdent == SM_SKELETON )			
	{
		SetMotionFrame(_MT_MON_SKELETON, bDir);
		m_bIsDead = TRUE;
	}
	else 
	{
		SetMotionFrame(_MT_MON_DIE, bDir);
		// 몬스터일때.
		if ( m_stFeature.bGender == _GENDER_MON )
		{
			WORD wDress;
			if ( m_stFeature.bGender == _GENDER_MON )
			{
				wDress = MAKEWORD(m_stFeature.bDress, m_stFeature.bHair);
			}
			else
			{
				wDress = m_stFeature.bDress;
			}

			MakeDeathEffect(wDress);
		}

		// m_bIsDead = TRUE 추가해야 하지 않을까? 어디선가 또 세팅 해주는가?
		// m_bIsDead 가 몬스터 행동에 영향을 미치는 부분을 다 찾아봐야 한다
		// by eriastoa 2006.04.06

	}	
}


VOID CActor::OnAlive(LPPACKETMSG lpPacketMsg)
{
	BYTE bDir;
	m_nPosX = lpPacketMsg->stDefMsg.wParam;
	m_nPosY = lpPacketMsg->stDefMsg.wTag;
	bDir		 = LOBYTE(lpPacketMsg->stDefMsg.wSeries);
	m_bLightSize = HIBYTE(lpPacketMsg->stDefMsg.wSeries);

	OnCharDescPacket(lpPacketMsg);

	m_bReverse = FALSE;
	m_bIsDead  = FALSE;
	SetMotionFrame(_MT_MON_APPEAR, bDir);
}


VOID CActor::OnBackStep(LPPACKETMSG lpPacketMsg)
{
	BYTE		bDir;
	CHARDESC	stCharDesc;
	FEATURE		stFeature;
	INT			nPos;
	bDir		 = LOBYTE(lpPacketMsg->stDefMsg.wSeries);
	BYTE		bRevDir;
	if ( bDir < 4 )			bRevDir = (BYTE)(bDir + 4);
	else					bRevDir = (BYTE)(bDir - 4);
	m_bLightSize = HIBYTE(lpPacketMsg->stDefMsg.wSeries);

	fnDecode6BitBuf(lpPacketMsg->szEncodeData, (char*)&stCharDesc, sizeof(CHARDESC));

/*	if (strlen(lpPacketMsg->szEncodeData) > _CHARDESCSIZE)
	{
		nPos = fnDecode6BitBuf(&lpPacketMsg->szEncodeData[_CHARDESCSIZE], m_szName, sizeof(m_szName));
		m_szName[nPos] = '\0';

		CHAR* szClr = strrchr(m_szName, '/');

		if ( szClr )
		{
			m_dwNameClr = GetUserNameColor((BYTE)(atoi(szClr+1)));
			*szClr = '\0';
		}
	}
*/

	memcpy(&stFeature, &stCharDesc.nFeature, sizeof(FEATURE));
	m_nCharState			= stCharDesc.nStatus;

	if( m_nCharState & 0X2 )
		m_bOpenHealth = TRUE;
	else
		m_bOpenHealth = FALSE;

	if ( stFeature.bGender == _GENDER_MON )
		ChangeFeature(stFeature);

	SetMotionFrame(_MT_MON_WALK, bDir);

	if ( m_bCurrDir < 4 )
		m_bMoveDir = (BYTE)(m_bCurrDir + 4);
	else
		m_bMoveDir = (BYTE)(m_bCurrDir - 4);

	m_bMoveSpeed = _SPEED_WALK;
	m_bBackStepFrame	= 0;
	m_bBackStepFrameCnt = 6;

	g_xGameProc.m_xMap.GetLastTile(lpPacketMsg->stDefMsg.wParam, lpPacketMsg->stDefMsg.wTag, bRevDir, m_nPosX, m_nPosY);

	SetBackStepMoving();
}

VOID CActor::OnStruck(LPPACKETMSG lpPacketMsg)
{
	CMagic*		  pxMagic = NULL;

	MESSAGEBODYWL stMsgBodyWl;
	FEATURE		  stFeature;
	WORD		  wDamage = 0;
	FLOAT wHPRate = 0.0f;

	if ( lpPacketMsg->stDefMsg.wTag != 0 )
	{
		wHPRate = (FLOAT)((FLOAT)lpPacketMsg->stDefMsg.wParam/(FLOAT)lpPacketMsg->stDefMsg.wTag);
	}
	wDamage		  = lpPacketMsg->stDefMsg.wSeries;
	m_wHP		  = lpPacketMsg->stDefMsg.wParam;
	m_wMAXHP	  = lpPacketMsg->stDefMsg.wTag;
	m_bHPPercent  = (BYTE)(wHPRate*100);

	if ( g_xGameProc.m_bShowBloodNum && m_bCurrMtn != _MT_MON_DIE )
	{
		m_nShowBlood[m_nShowBloodIdx] = wDamage*(-1);
		m_ptShowBlood[m_nShowBloodIdx].x = m_nScrnPosX;
		m_ptShowBlood[m_nShowBloodIdx].y = m_nScrnPosY;
		m_dwShowBloodTimer[m_nShowBloodIdx] = 0;

		m_nShowBloodIdx++;

		if ( m_nShowBloodIdx > 7 )
			m_nShowBloodIdx = 0;
	}

	fnDecode6BitBuf(lpPacketMsg->szEncodeData, (char*)&stMsgBodyWl, sizeof(MESSAGEBODYWL));

	memcpy(&stFeature, &stMsgBodyWl.lParam1, sizeof(LONG));

	if ( stFeature.bGender == _GENDER_MON )
		ChangeFeature(stFeature);

	if ( m_wHP == 0 && !m_bIsDead )
	{
		SetMotionFrame(_MT_MON_DIE, m_bCurrDir);
		MakeDeathEffect(MAKEWORD(m_stFeature.bDress, m_stFeature.bHair));
	}
	else if ( wDamage != 0 )
	{
		SetMotionFrame(_MT_MON_HITTED, m_bCurrDir);
	}

	// 원소타격마법.
	if ( !m_bIsDead && wDamage != 0 )
	{
		pxMagic = new CMagic;
		if ( pxMagic->CreateMagic(_SKILL_STRUCK_FIRE+HIWORD(stMsgBodyWl.nTag2), m_nPosX, m_nPosY, m_nPosX, m_nPosY, this, m_nIdentity) )
			g_xGameProc.m_xMagicList.Insert (pxMagic);
		else
			delete pxMagic;
	}

	WORD wDress = MAKEWORD(m_stFeature.bDress, m_stFeature.bHair);
	if ( wDress == 161)
	{
		LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_MURYUK_S, m_bCurrDir);
		m_bUseSwordEffect = TRUE;
	}


	CActor*		pxActor = NULL;
	CListNode <CActor> *pNode;

	if ( stMsgBodyWl.nTag1 == g_xGameProc.m_xMyHero.m_nIdentity )
	{
		m_stHitter = g_xGameProc.m_xMyHero.m_stFeature;
	}
	else
	{
		for (pNode = g_xGameProc.m_xActorList.GetHead(); pNode; pNode = pNode->GetNext())
		{
			CActor* pxGaheja = pNode->GetData();

			if ( pxGaheja )
			{
				if ( pxGaheja->m_nIdentity == stMsgBodyWl.nTag1 )
				{
					m_stHitter = pxGaheja->m_stFeature;
					break;
				}
			}
		}	
	}

	// 몬스터일때.
	if ( m_stHitter.bGender == _GENDER_MON && g_xGameProc.m_bShowMonEffect )
	{
		switch ( MAKEWORD(m_stHitter.bDress, m_stHitter.bHair) )
		{
		case 104:		// 적월마.
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_REDMOON, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this) )
			{
				g_xGameProc.m_xMagicList.Insert (pxMagic);

				LPEVENTIMG pstEvent;

				pstEvent = new EVENTIMG;
				pstEvent->nEventID = 0;
				pstEvent->nType	   = 0;
				pstEvent->dwTick  = timeGetTime();
				pstEvent->nTileX = m_nPosX;
				pstEvent->nTileY = m_nPosY;
				pstEvent->dwLifeTime = 15000;
				pstEvent->wFrameNum = (WORD)(250);
				pstEvent->wOutDelay = 420;
				pstEvent->bUseAlpha = FALSE;
				g_xGameProc.m_stEventImgList.Insert (pstEvent);
			}
			else
				delete pxMagic;

			break;
		case 2:		// 케팔로프.
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_KEPAL, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
			break;
		case 67:	// 촉룡신.
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_BIGGINE_CHAR, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
			break;
		case 150:	// 돈왕.
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_BYDONKING, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
			break;
		default :
			break;
		}
	}
}


VOID CActor::OnLighting(LPPACKETMSG lpPacketMsg)
{
	INT		nTargetID;
	CMagic* pxMagic;

	MESSAGEBODYWL stMsgBodyWl;
	fnDecode6BitBuf(lpPacketMsg->szEncodeData, (char*)&stMsgBodyWl, sizeof(MESSAGEBODYWL));
	nTargetID = stMsgBodyWl.nTag1;

	if (stMsgBodyWl.nTag2 == 1)		// 1:좀비 -- 뢰인장
	{
		m_nPosX      = lpPacketMsg->stDefMsg.wParam;
		m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
		m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

		if ( g_xGameProc.m_bShowMonEffect )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_ZOMBIE, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this, nTargetID) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
		}

		SetMotionFrame(_MT_MON_ATTACK_A, m_bCurrDir);
	}
	else if (stMsgBodyWl.nTag2 == 2) // 2:우면귀왕, 누마법로 -- 강격
	{
//		m_nPosX      = lpPacketMsg->stDefMsg.wParam;
//		m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
		m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

		WORD wDress;
		if ( m_stFeature.bGender == _GENDER_MON )
		{
			wDress = MAKEWORD(m_stFeature.bDress, m_stFeature.bHair);
		}
		else
		{
			wDress = m_stFeature.bDress;
		}

		if ( wDress == 13 )			// 누마법로.
		{
			if ( g_xGameProc.m_bShowMonEffect )
			{
				pxMagic = new CMagic;
				if ( pxMagic->CreateMagic(_MONMAGIC_LIGHTENING, m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2, this, nTargetID, 500) )
					g_xGameProc.m_xMagicList.Insert(pxMagic);
				else
					delete pxMagic;
			}

			SetMotionFrame(_MT_MON_SPELL_A, m_bCurrDir);
		}
		else						// 우면귀왕.
		{
			if ( g_xGameProc.m_bShowMonEffect )
			{
				pxMagic = new CMagic;
				if ( pxMagic->CreateMagic(_MONMAGIC_LIGHTENING, m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2, this, nTargetID) )
					g_xGameProc.m_xMagicList.Insert(pxMagic);
				else
					delete pxMagic;
			}
		}
	}
	else if (stMsgBodyWl.nTag2 == 3) // 3:우면귀왕 -- 뢰설화
	{
		m_nPosX      = lpPacketMsg->stDefMsg.wParam;
		m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
		m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

		if ( g_xGameProc.m_bShowMonEffect )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_LIGHTFLOWER, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this) )
				g_xGameProc.m_xMagicList.Insert(pxMagic);
			else
				delete pxMagic;
		}
	}
	else if (stMsgBodyWl.nTag2 == 4) // 4:백돈.(풍백용 파장효과)
	{
		m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

		if ( g_xGameProc.m_bShowMonEffect )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_WINDGOD, m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2, this, nTargetID) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
		}
	}
	else if (stMsgBodyWl.nTag2 == 5) // 5:주마왕(폭열파).
	{
		m_nPosX      = lpPacketMsg->stDefMsg.wParam;
		m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
		m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

		if ( g_xGameProc.m_bShowMonEffect )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_SKILL_FIREBOOM, m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2, this, nTargetID) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
		}
	}
	else if (stMsgBodyWl.nTag2 == 6) // 6:주마왕(염사장).
	{
		m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

		if ( g_xGameProc.m_bShowMonEffect )
			MakeMagicStream(_SKILL_FIRE, nTargetID, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2);
	}
	else if (stMsgBodyWl.nTag2 == 7) // 7:광명좌사.
	{
		m_nPosX      = lpPacketMsg->stDefMsg.wParam;
		m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
		m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

		if ( g_xGameProc.m_bShowMonEffect )
		{
			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_LIGHTLEFTMAGIC, m_bCurrDir);
			m_bUseSwordEffect = TRUE;

			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_FIREBALL, m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2, this, nTargetID, 500) )
				g_xGameProc.m_xMagicList.Insert(pxMagic);
			else
				delete pxMagic;
		}

		SetMotionFrame(_MT_MON_ATTACK_B, m_bCurrDir);
	}
	else if (stMsgBodyWl.nTag2 == 8) // 8:광명우사.
	{
		m_nPosX      = lpPacketMsg->stDefMsg.wParam;
		m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
		m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

		if ( g_xGameProc.m_bShowMonEffect )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_LIGHTENING, m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2, this, nTargetID, 500) )
				g_xGameProc.m_xMagicList.Insert(pxMagic);
			else
				delete pxMagic;
		}

		SetMotionFrame(_MT_MON_ATTACK_B, m_bCurrDir);
	}
	else if (stMsgBodyWl.nTag2 == 9) // 9:사우천왕.
	{
		m_nPosX      = lpPacketMsg->stDefMsg.wParam;
		m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
		m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

		if ( g_xGameProc.m_bShowMonEffect )
		{
			WORD wDress;
			wDress = MAKEWORD(m_stFeature.bDress, m_stFeature.bHair);

			if ( g_xGameProc.m_bShowMonEffect && wDress != 144 )
			{
				pxMagic = new CMagic;
				if ( pxMagic->CreateMagic(_MONMAGIC_REALUMAMAGICATT, m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2, this, nTargetID) )
					g_xGameProc.m_xMagicList.Insert(pxMagic);
				else
					delete pxMagic;
			}
			else		// 고루궁수
			{
				pxMagic = new CMagic;
				if ( pxMagic->CreateMagic(_MONMAGIC_BINGHONGUNG_A, m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2, this, nTargetID, 365) )
					g_xGameProc.m_xMagicList.Insert (pxMagic);
				else
					delete pxMagic;
				
//				SetMotionFrame(_MT_MON_ATTACK_A, m_bCurrDir);
			}
		}
	}
	else if (stMsgBodyWl.nTag2 == 10 || stMsgBodyWl.nTag2 == 11 ) // 10:원후군
	{
		m_nPosX      = lpPacketMsg->stDefMsg.wParam;
		m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
		m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

		WORD wDress;
		wDress = MAKEWORD(m_stFeature.bDress, m_stFeature.bHair);


		if ( g_xGameProc.m_bShowMonEffect && wDress != 208 )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_THROW_STONE, m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2, this, nTargetID, 400) )
				g_xGameProc.m_xMagicList.Insert(pxMagic);
			else
				delete pxMagic;
		}

		SetMotionFrame(_MT_MON_ATTACK_B, m_bCurrDir);
	}
/*	else if (stMsgBodyWl.nTag2 == 11) // 11:원후자
	{
		m_nPosX      = lpPacketMsg->stDefMsg.wParam;
		m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
		m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

		SetMotionFrame(_MT_MON_ATTACK_B, m_bCurrDir);
	}*/
	else if (stMsgBodyWl.nTag2 == 12) // 12:석화사자
	{
		m_nPosX      = lpPacketMsg->stDefMsg.wParam;
		m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
		m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

		if ( g_xGameProc.m_bShowMonEffect )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_LION1, m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2, this, nTargetID, 400) )
				g_xGameProc.m_xMagicList.Insert(pxMagic);
			else
				delete pxMagic;
		}

		SetMotionFrame(_MT_MON_ATTACK_B, m_bCurrDir);
	}
	else if (stMsgBodyWl.nTag2 == 13) // 13:마신도2
	{
		m_nPosX      = lpPacketMsg->stDefMsg.wParam;
		m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
		m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

		if ( g_xGameProc.m_bShowMonEffect )
		{
			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_POISON, m_bCurrDir);
			m_bUseSwordEffect = TRUE;
		}

		SetMotionFrame(_MT_MON_SPELL_A, m_bCurrDir);
	}
	else if (stMsgBodyWl.nTag2 == 14) // 14:거환수
	{
		m_nPosX      = lpPacketMsg->stDefMsg.wParam;
		m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
		m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

		if ( g_xGameProc.m_bShowMonEffect )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_SANDFISH, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
		}

		SetMotionFrame(_MT_MON_SPELL_A, m_bCurrDir);
	}
	else if (stMsgBodyWl.nTag2 == 15) // 15:화염사자.
	{		
		m_nPosX      = lpPacketMsg->stDefMsg.wParam;
		m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
		m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

		if ( g_xGameProc.m_bShowMonEffect )
		{
			WORD wDress;
			wDress = MAKEWORD(m_stFeature.bDress, m_stFeature.bHair);

			if ( g_xGameProc.m_bShowMonEffect && wDress != 141 )
			{
				pxMagic = new CMagic;
				if ( pxMagic->CreateMagic(_MONMAGIC_LION2, m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2, this, nTargetID, 400) )
					g_xGameProc.m_xMagicList.Insert(pxMagic);
				else
					delete pxMagic;

				SetMotionFrame(_MT_MON_ATTACK_B, m_bCurrDir);
			}
			else			// 고루마왕
			{
				pxMagic = new CMagic;
				if ( pxMagic->CreateMagic(_MONMAGIC_LION2, m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2, this, nTargetID, 365) )
					g_xGameProc.m_xMagicList.Insert (pxMagic);
				else
					delete pxMagic;
				
//				SetMotionFrame(_MT_MON_ATTACK_A, m_bCurrDir);
			}
		}

//		SetMotionFrame(_MT_MON_ATTACK_B, m_bCurrDir);
	}
	else if (stMsgBodyWl.nTag2 == 16) // 16:무력장군.
	{
		m_nPosX      = lpPacketMsg->stDefMsg.wParam;
		m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
		m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

		if ( g_xGameProc.m_bShowMonEffect )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_MURYUK_A, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this, -1) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
		}

		SetMotionFrame(_MT_MON_SPELL_A, m_bCurrDir);
	}
	else if (stMsgBodyWl.nTag2 == 17) // 17:해골반왕.
	{
		m_nPosX      = lpPacketMsg->stDefMsg.wParam;
		m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
		m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

/*		pxMagic = new CMagic;
		if ( pxMagic->CreateMagic(_MONMAGIC_SKELBOSSFIRE, m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2, this, nTargetID, 600) )
			g_xGameProc.m_xMagicList.Insert (pxMagic);
		else
			delete pxMagic;*/

		if ( g_xGameProc.m_bShowMonEffect )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_FIREBALL, m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2, this, nTargetID, 500) )
				g_xGameProc.m_xMagicList.Insert(pxMagic);
			else
				delete pxMagic;
		}

		SetMotionFrame(_MT_MON_SPELL_B, m_bCurrDir);
	}
	else if (stMsgBodyWl.nTag2 == 18) // 18:진천마신 독공격.
	{
		WORD wDress;
		if ( m_stFeature.bGender == _GENDER_MON )
		{
			wDress = MAKEWORD(m_stFeature.bDress, m_stFeature.bHair);
		}

		if ( wDress == 164 )
		{
			m_nPosX      = lpPacketMsg->stDefMsg.wParam;
			m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
			m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

			if ( g_xGameProc.m_bShowMonEffect )
			{
				pxMagic = new CMagic;
				if ( pxMagic->CreateMagic(_MONMAGIC_MAWANG_MA, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this) )
					g_xGameProc.m_xMagicList.Insert(pxMagic);
				else
					delete pxMagic;
			}
		}
		else if ( wDress == 198 )
		{
			m_nPosX      = lpPacketMsg->stDefMsg.wParam;
			m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
			m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

			if ( g_xGameProc.m_bShowMonEffect )
			{
				pxMagic = new CMagic;
				if ( pxMagic->CreateMagic(_MONMAGIC_JICHUN_MAGIC_B, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this) )
					g_xGameProc.m_xMagicList.Insert(pxMagic);
				else
					delete pxMagic;
			}
		}

		SetMotionFrame(_MT_MON_SPELL_A, m_bCurrDir);
	}
	else if (stMsgBodyWl.nTag2 == 19) // 19:진천마신검기특수.
	{
		WORD wDress;
		if ( m_stFeature.bGender == _GENDER_MON )
		{
			wDress = MAKEWORD(m_stFeature.bDress, m_stFeature.bHair);
		}

		if ( wDress == 164 )
		{
			m_nPosX      = lpPacketMsg->stDefMsg.wParam;
			m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
			m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

			// 가끔하는 공격검기.
			if ( g_xGameProc.m_bShowMonEffect )
			{
				LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_MAWANG_A1, m_bCurrDir);
				m_bUseSwordEffect = TRUE;
			}

			SetMotionFrame(_MT_MON_ATTACK_B, m_bCurrDir);
		}
		else if ( wDress == 198 )
		{
			m_nPosX      = lpPacketMsg->stDefMsg.wParam;
			m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
			m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

			// 가끔하는 공격검기.
			if ( g_xGameProc.m_bShowMonEffect )
			{
				LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_JICHUN_MAGIC_A, m_bCurrDir);
				m_bUseSwordEffect = TRUE;
			}

			SetMotionFrame(_MT_MON_ATTACK_B, m_bCurrDir);
		}
	}
	else if (stMsgBodyWl.nTag2 == 20) // 20:누마기병
	{
		m_nPosX      = lpPacketMsg->stDefMsg.wParam;
		m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
		m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

		WORD wDress;

		if ( m_stFeature.bGender == _GENDER_MON )
		{
			wDress = MAKEWORD(m_stFeature.bDress, m_stFeature.bHair);
		}


		if ( wDress == 196 )
		{
			if ( g_xGameProc.m_bShowMonEffect )
			{
				pxMagic = new CMagic;
				if ( pxMagic->CreateMagic(_MONMAGIC_DEARYONG_A, m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2, this, nTargetID, 1100) )
				{
					LPEVENTIMG pstEvent;

					pstEvent = new EVENTIMG;
					pstEvent->nEventID = 0;
					pstEvent->nType	   = 0;
					pstEvent->dwTick  = timeGetTime();
					pstEvent->nTileX = stMsgBodyWl.lParam1;
					pstEvent->nTileY = stMsgBodyWl.lParam2;
					pstEvent->dwLifeTime = 10000;
					pstEvent->wFrameNum = (WORD)(250);
					pstEvent->wOutDelay = 0;
					pstEvent->bUseAlpha = FALSE;
					g_xGameProc.m_stEventImgList.Insert (pstEvent);

					g_xGameProc.m_xMagicList.Insert (pxMagic);

				}
				else
					delete pxMagic;
			}
			SetMotionFrame(_MT_MON_SPELL_A, m_bCurrDir);
		}
		else
		{
			if ( g_xGameProc.m_bShowMonEffect )
			{
				pxMagic = new CMagic;
				if ( pxMagic->CreateMagic(_MONMAGIC_NUMAGIBYUNG, m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2, this, nTargetID, 800) )
					g_xGameProc.m_xMagicList.Insert(pxMagic);
				else
					delete pxMagic;
			}

			SetMotionFrame(_MT_MON_ATTACK_B, m_bCurrDir);
		}
	}
	else if (stMsgBodyWl.nTag2 == 21) // 21:누마사령법사
	{
		m_nPosX      = lpPacketMsg->stDefMsg.wParam;
		m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
		m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

//		LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_NUMABUBSA6, m_bCurrDir);
//		m_bUseSwordEffect = TRUE;

		if ( g_xGameProc.m_bShowMonEffect )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_NUMABUBSA6, m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2, this, nTargetID, 400) )
				g_xGameProc.m_xMagicList.Insert(pxMagic);
			else
				delete pxMagic;
		}

		SetMotionFrame(_MT_MON_ATTACK_B, m_bCurrDir);
	}
	else if (stMsgBodyWl.nTag2 == 22) // 22:누마친위대장
	{
		m_nPosX      = lpPacketMsg->stDefMsg.wParam;
		m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
		m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

		if ( g_xGameProc.m_bShowMonEffect )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_NUMABODYGUARD_A, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this, -1) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
		}

		SetMotionFrame(_MT_MON_SPELL_A, m_bCurrDir);
	}
	else if (stMsgBodyWl.nTag2 == 23) // 23:회복술
	{
		m_nPosX      = lpPacketMsg->stDefMsg.wParam;
		m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
		m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

		if ( g_xGameProc.m_bShowMonEffect )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_SKILL_HEALLING, m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2, this, nTargetID, 700) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
		}
	}
	else if (stMsgBodyWl.nTag2 == 24) // 24:대회복술
	{
		m_nPosX      = lpPacketMsg->stDefMsg.wParam;
		m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
		m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

		if ( g_xGameProc.m_bShowMonEffect )
		{
			CMagic* pxMagic;
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_SKILL_BIGHEALLING, m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2, NULL, nTargetID) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);						
			else
				delete pxMagic;
		}
	}
	else if (stMsgBodyWl.nTag2 == 25) // 25:빙사장
	{
		m_nPosX      = lpPacketMsg->stDefMsg.wParam;
		m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
		m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

		if ( g_xGameProc.m_bShowMonEffect )
			MakeMagicStream(_SKILL_ICE, 0, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2);
	}
	else if (stMsgBodyWl.nTag2 == 26) // 26:정화술
	{
		m_nPosX      = lpPacketMsg->stDefMsg.wParam;
		m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
		m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

		if ( g_xGameProc.m_bShowMonEffect )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_SKILL_REMOVEPOISON, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2, m_nPosX, m_nPosY, this, nTargetID, 700) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
		}
	}
	else if (stMsgBodyWl.nTag2 == 27) // 27:빙백귀녀 날아가는 마법
	{
		m_nPosX      = lpPacketMsg->stDefMsg.wParam;
		m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
		m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

		if ( g_xGameProc.m_bShowMonEffect )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_BINGBAK_MAGIC_A, m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2, this, nTargetID, 500) )
				g_xGameProc.m_xMagicList.Insert(pxMagic);
			else
				delete pxMagic;
		}

		SetMotionFrame(_MT_MON_ATTACK_A, (BYTE)g_xGameProc.m_xMap.CalcDirection8(m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2));
	}
	else if (stMsgBodyWl.nTag2 == 28) // 28:빙백귀녀 터지는 마법
	{
		m_nPosX      = lpPacketMsg->stDefMsg.wParam;
		m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
		m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

		if ( g_xGameProc.m_bShowMonEffect )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_BINGBAK_MAGIC_B, m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2, this, nTargetID, 500) )
				g_xGameProc.m_xMagicList.Insert(pxMagic);
			else
				delete pxMagic;
		}

		BYTE bDir = (BYTE)g_xGameProc.m_xMap.CalcDirection8(m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2);
		LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_BINGBAK_SIJUN, 0);
		m_bUseSwordEffect = TRUE;

		SetMotionFrame(_MT_MON_SPELL_A, bDir);
	}
	else if (stMsgBodyWl.nTag2 == 29) // 29:빙혼무장1,2 터지는 마법
	{
		m_nPosX      = lpPacketMsg->stDefMsg.wParam;
		m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
		m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

		if ( g_xGameProc.m_bShowMonEffect )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_HANBINGMA_MAGIC, m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2, this, nTargetID, 500) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
		}
		SetMotionFrame(_MT_MON_ATTACK_A, (BYTE)g_xGameProc.m_xMap.CalcDirection8(m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2));
	}
	else if (stMsgBodyWl.nTag2 == 30) // 29:빙혼무장1,2 터지는 마법
	{
		m_nPosX      = lpPacketMsg->stDefMsg.wParam;
		m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
		m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

		if ( g_xGameProc.m_bShowMonEffect )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_RED1, m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2, this, nTargetID, 500) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
		}
		SetMotionFrame(_MT_MON_SPELL_A, (BYTE)g_xGameProc.m_xMap.CalcDirection8(m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2));
	}
	else if (stMsgBodyWl.nTag2 == 31) // 화영
	{
		m_nPosX      = lpPacketMsg->stDefMsg.wParam;
		m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
		m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

		if ( g_xGameProc.m_bShowMonEffect )
		{
			CMagic* pxMagic;
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_WHAYOUNG_MAGIC, m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2, this, nTargetID, 500) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
		}
	}
	else if ( stMsgBodyWl.nTag2 == 33 ) //가무녀1 주변 마법
	{
		m_nPosX      = lpPacketMsg->stDefMsg.wParam;
		m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
		m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

		if ( g_xGameProc.m_bShowMonEffect )
		{
			WORD wDress;
			wDress = MAKEWORD(m_stFeature.bDress, m_stFeature.bHair);

			if ( g_xGameProc.m_bShowMonEffect && wDress != 144 )
			{
				pxMagic = new CMagic;
				if ( pxMagic->CreateMagic(_MONMAGIC_GAMU_MAGIC, m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2, this, nTargetID) )
					g_xGameProc.m_xMagicList.Insert(pxMagic);
				else
					delete pxMagic;
			}
		}

	}
	else if ( stMsgBodyWl.nTag2 == 34 ) //가무녀1 전체 마법
	{
		m_nPosX      = lpPacketMsg->stDefMsg.wParam;
		m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
		m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

		if ( g_xGameProc.m_bShowMonEffect )
		{
			WORD wDress;
			wDress = MAKEWORD(m_stFeature.bDress, m_stFeature.bHair);

			if ( g_xGameProc.m_bShowMonEffect && wDress != 144 )
			{
				pxMagic = new CMagic;
				if ( pxMagic->CreateMagic(_MONMAGIC_GAMU_MAGIC, m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2, this, nTargetID) )
					g_xGameProc.m_xMagicList.Insert(pxMagic);
				else
					delete pxMagic;
			}
		}
	}
	else if ( stMsgBodyWl.nTag2 == 35 ) //가무녀2마법
	{
		m_nPosX      = lpPacketMsg->stDefMsg.wParam;
		m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
		m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

		if ( g_xGameProc.m_bShowMonEffect )
		{
			WORD wDress;
			wDress = MAKEWORD(m_stFeature.bDress, m_stFeature.bHair);

			if ( g_xGameProc.m_bShowMonEffect && wDress != 144 )
			{
				pxMagic = new CMagic;
				if ( pxMagic->CreateMagic(_MONMAGIC_GAMU2_MAGIC, m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2, this, nTargetID) )
					g_xGameProc.m_xMagicList.Insert(pxMagic);
				else
					delete pxMagic;
			}
		}
	}									// 36,37은 안 그리는 이펙트?-_-??
	else if ( stMsgBodyWl.nTag2 == 38 ) //시전
	{
		m_nPosX      = lpPacketMsg->stDefMsg.wParam;
		m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
		m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

		WORD wDress;
		wDress = MAKEWORD(m_stFeature.bDress, m_stFeature.bHair);

		if ( g_xGameProc.m_bShowMonEffect && wDress == 212 )           // 가무녀1
		{
			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_GAMU_MAGIC_NEAR, 0);
			m_bUseSwordEffect = TRUE;

			SetMotionFrame(_MT_MON_ATTACK_A, (BYTE)g_xGameProc.m_xMap.CalcDirection8(m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2));
		}
	}
	else if ( stMsgBodyWl.nTag2 == 39 ) //시전
	{
		m_nPosX      = lpPacketMsg->stDefMsg.wParam;
		m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
		m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

		WORD wDress;
		wDress = MAKEWORD(m_stFeature.bDress, m_stFeature.bHair);

		if ( g_xGameProc.m_bShowMonEffect && wDress == 212 )           // 가무녀1
		{
			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_GAMU_MAGIC_SELF, 0);
			m_bUseSwordEffect = TRUE;

			SetMotionFrame(_MT_MON_ATTACK_B, (BYTE)g_xGameProc.m_xMap.CalcDirection8(m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2));
		}
		else if ( g_xGameProc.m_bShowMonEffect && wDress == 213 )           // 가무녀2
		{
			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_GAMU2_MAGIC_SELF, 0);
			m_bUseSwordEffect = TRUE;

			SetMotionFrame(_MT_MON_ATTACK_B, (BYTE)g_xGameProc.m_xMap.CalcDirection8(m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2));
		}
		else if ( g_xGameProc.m_bShowMonEffect && wDress == 210 )           // 호위장수
		{
			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_GUARDGEN_MAGIC, 0);
			m_bUseSwordEffect = TRUE;

			SetMotionFrame(_MT_MON_ATTACK_B, (BYTE)g_xGameProc.m_xMap.CalcDirection8(m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2));
		}
		else if ( g_xGameProc.m_bShowMonEffect && wDress == 211 )           // 새벽여왕
		{
			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_DAWNQUEEN_MAGIC, 0);
			m_bUseSwordEffect = TRUE;

			SetMotionFrame(_MT_MON_ATTACK_B, (BYTE)g_xGameProc.m_xMap.CalcDirection8(m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2));
		}
		else if ( g_xGameProc.m_bShowMonEffect && wDress == 205 )           // 화영
		{
			SetMotionFrame(_MT_MON_ATTACK_B, (BYTE)g_xGameProc.m_xMap.CalcDirection8(m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2));
		}

	}
	// 쾌도난마 by eriastoa 2006.05.17
	else if( stMsgBodyWl.nTag2 == 40 )
	{
		m_nPosX      = lpPacketMsg->stDefMsg.wParam;
		m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
		m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

		if ( g_xGameProc.m_bShowMonEffect )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_SKILL_HYPERSWORD, m_nPosX, m_nPosY, stMsgBodyWl.lParam1, stMsgBodyWl.lParam2, this, nTargetID) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
		}
	}
}



VOID CActor::OnFlyAxe(LPPACKETMSG lpPacketMsg)
{
	WORD	wTargetX, wTargetY;
	INT		nTargetID;
	CMagic* pxMagic;

	m_nPosX      = lpPacketMsg->stDefMsg.wParam;
	m_nPosY		 = lpPacketMsg->stDefMsg.wTag;
	m_bCurrDir	 = (BYTE)(lpPacketMsg->stDefMsg.wSeries);

	MESSAGEBODYW stMsgBodyW;
	fnDecode6BitBuf(lpPacketMsg->szEncodeData, (char*)&stMsgBodyW, sizeof(MESSAGEBODYW));
	wTargetX = stMsgBodyW.wParam1;
	wTargetY = stMsgBodyW.wParam2;
	nTargetID = MAKELONG(stMsgBodyW.wTag1, stMsgBodyW.wTag2);

	WORD wDress;

	if ( m_stFeature.bGender == _GENDER_MON )
	{
		wDress = MAKEWORD(m_stFeature.bDress, m_stFeature.bHair);
	}
	else
	{
		wDress = m_stFeature.bDress;
	}

	switch ( wDress )
	{
	case 11:
	case 16:
	case 3:
	case 15:
		if ( g_xGameProc.m_bShowMonEffect )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_BINGHONGUNG_A, m_nPosX, m_nPosY, wTargetX, wTargetY, this, nTargetID, 365) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
		}
//		SetMotionFrame(_MT_MON_ATTACK_A, m_bCurrDir);
		break;
	case 19:		// 홍의법사
		if ( g_xGameProc.m_bShowMonEffect )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_RED1, m_nPosX, m_nPosY, wTargetX, wTargetY, this, nTargetID, 500) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
		}
		SetMotionFrame(_MT_MON_ATTACK_A, m_bCurrDir);
		break;
	case 203:		// 빙혼무장2
		if ( g_xGameProc.m_bShowMonEffect )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_HANBINGMA_MAGIC, m_nPosX, m_nPosY, wTargetX, wTargetY, this, nTargetID, 500) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
		}
		SetMotionFrame(_MT_MON_ATTACK_A, m_bCurrDir);
		break;
	case 96:				// 포수개미.
		if ( g_xGameProc.m_bShowMonEffect )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_POSUANT, m_nPosX, m_nPosY, wTargetX, wTargetY, this, nTargetID, 500) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
		}
		SetMotionFrame(_MT_MON_ATTACK_A, m_bCurrDir);
		break;
	case 7:				// 치유개미.
		if ( g_xGameProc.m_bShowMonEffect )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_ANTHEAL, m_nPosX, m_nPosY, wTargetX, wTargetY, this, nTargetID, 500) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
		}
		SetMotionFrame(_MT_MON_ATTACK_A, m_bCurrDir);
		break;
	case 33:				// 쌍도끼해골.
		if ( g_xGameProc.m_bShowMonEffect )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_DUALAXE, m_nPosX, m_nPosY, wTargetX, wTargetY, this, nTargetID, 365) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
		}
		SetMotionFrame(_MT_MON_ATTACK_A, m_bCurrDir);
		break;
	case 46:				// 다크.
		if ( g_xGameProc.m_bShowMonEffect )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_CHIM, m_nPosX, m_nPosY, wTargetX, wTargetY, this, nTargetID, 365) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
		}
		SetMotionFrame(_MT_MON_ATTACK_A, m_bCurrDir);
		break;
	case 82:				// 마궁사.
	case 144:				// 해골궁수.
		if ( g_xGameProc.m_bShowMonEffect )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_MAARROW, m_nPosX, m_nPosY, wTargetX, wTargetY, this, nTargetID, 365) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
		}
		SetMotionFrame(_MT_MON_ATTACK_A, m_bCurrDir);
		break;
	case 200:				// 빙혼궁사1
	case 201:				// 빙혼궁사2
		if ( g_xGameProc.m_bShowMonEffect )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_BINGHONGUNG_A, m_nPosX, m_nPosY, wTargetX, wTargetY, this, nTargetID, 365) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
		}
		SetMotionFrame(_MT_MON_ATTACK_A, m_bCurrDir);
		break;
	case 199:				// 사혈괴
		if ( g_xGameProc.m_bShowMonEffect )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_SAHYULGUI_A, m_nPosX, m_nPosY, wTargetX, wTargetY, this, nTargetID, 365) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
		}
		SetMotionFrame(_MT_MON_ATTACK_A, m_bCurrDir);
		break;
	case 86:				// 궁사.
		if ( g_xGameProc.m_bShowMonEffect )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_ARROW, m_nPosX, m_nPosY, wTargetX, wTargetY, this, nTargetID, 365) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
		}
		SetMotionFrame(_MT_MON_ATTACK_A, m_bCurrDir);
		break;
	case 95:				// 형인수.
		if ( g_xGameProc.m_bShowMonEffect )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_HUMANTREE, m_nPosX, m_nPosY, wTargetX, wTargetY, this, nTargetID, 700) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
		}
		SetMotionFrame(_MT_MON_ATTACK_A, m_bCurrDir);
		break;
	case 145:				// 다발충1.
	case 146:				// 다발충2.
		if ( g_xGameProc.m_bShowMonEffect )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_FLEA_SHOT, m_nPosX, m_nPosY, wTargetX, wTargetY, this, nTargetID) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
		}
		SetMotionFrame(_MT_MON_ATTACK_A, m_bCurrDir);
		break;
	case 124:				// 예진
	case 125:				// 허준
		if ( g_xGameProc.m_bShowMonEffect )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_YEJIN_HEAL, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this, m_nIdentity, 0) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;	

			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_SKILL_HEALLING, m_nPosX, m_nPosY, wTargetX, wTargetY, this, nTargetID, 700) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
			break;
		}
	case 156:				// 마신도1
		if ( g_xGameProc.m_bShowMonEffect )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_SPEAR, m_nPosX, m_nPosY, wTargetX, wTargetY, this, nTargetID, 700) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
		}

		SetMotionFrame(_MT_MON_ATTACK_A, m_bCurrDir);
		break;
	case 183:
		if ( g_xGameProc.m_bShowMonEffect )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_SKILL_FIREBOOM, m_nPosX, m_nPosY, wTargetX, wTargetY, this, nTargetID, 700) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
		}

		SetMotionFrame(_MT_MON_ATTACK_A, m_bCurrDir);

		break;
	case 167:				// 발석거
		INT nTargetX, nTargetY;

		switch(m_bCurrDir)
		{
		case 0:
			nTargetX = m_nPosX;
			nTargetY = m_nPosY - 20;
			break;
		case 1:
			nTargetX = m_nPosX + 20;
			nTargetY = m_nPosY - 30;
			break;
		case 2:
			nTargetX = m_nPosX + 20;
			nTargetY = m_nPosY - 5;
			break;
		case 3:
			nTargetX = m_nPosX + 20;
			nTargetY = m_nPosY + 10;
			break;
		case 4:
			nTargetX = m_nPosX;
			nTargetY = m_nPosY + 20;
			break;
		case 5:
			nTargetX = m_nPosX - 20;
			nTargetY = m_nPosY + 10;
			break;
		case 6:
			nTargetX = m_nPosX - 20;
			nTargetY = m_nPosY - 5;
			break;
		case 7:
			nTargetX = m_nPosX - 20;
			nTargetY = m_nPosY - 30;
			break;
		}

		if ( g_xGameProc.m_bShowMonEffect )
		{
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_SIEGE_SHOOT, m_nPosX, m_nPosY, nTargetX, nTargetY, this, 0, 700) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
		}

		SetMotionFrame(_MT_MON_ATTACK_A, m_bCurrDir);
		break;
	case 169:				// 쇠뇌차
		switch(m_bCurrDir)
		{
		case 0:
			nTargetX = m_nPosX;
			nTargetY = m_nPosY - 20;
			break;
		case 1:
			nTargetX = m_nPosX + 20;
			nTargetY = m_nPosY - 30;
			break;
		case 2:
			nTargetX = m_nPosX + 30;
			nTargetY = m_nPosY - 8;
			break;
		case 3:
			nTargetX = m_nPosX + 20;
			nTargetY = m_nPosY + 12;
			break;
		case 4:
			nTargetX = m_nPosX;
			nTargetY = m_nPosY + 20;
			break;
		case 5:
			nTargetX = m_nPosX - 20;
			nTargetY = m_nPosY + 12;
			break;
		case 6:
			nTargetX = m_nPosX - 30;
			nTargetY = m_nPosY - 8;
			break;
		case 7:
			nTargetX = m_nPosX - 20;
			nTargetY = m_nPosY - 30;
			break;
		}

		for (INT nI=0; nI<9; nI++)
		{
			SetMotionFrame(_MT_MON_ATTACK_A, m_bCurrDir);
			if ( g_xGameProc.m_bShowMonEffect )
			{
				switch(nI)
				{
				case 0:
					{
					pxMagic = new CMagic;
					if ( pxMagic->CreateMagic(_MONMAGIC_SIEGECAR_SHOOT, m_nPosX, m_nPosY, nTargetX, nTargetY, this, 0, 0) )
						g_xGameProc.m_xMagicList.Insert (pxMagic);
					else
						delete pxMagic;
					}
					break;
				case 1:
					{
					pxMagic = new CMagic;
					if ( pxMagic->CreateMagic(_MONMAGIC_SIEGECAR_SHOOT, m_nPosX, m_nPosY, nTargetX+2, nTargetY, this, 0, 70) )
						g_xGameProc.m_xMagicList.Insert (pxMagic);
					else
						delete pxMagic;
					}
					break;
				case 2:
					{
					pxMagic = new CMagic;
					if ( pxMagic->CreateMagic(_MONMAGIC_SIEGECAR_SHOOT, m_nPosX, m_nPosY, nTargetX, nTargetY+2, this, 0, 140) )
						g_xGameProc.m_xMagicList.Insert (pxMagic);
					else
						delete pxMagic;
					}
					break;
				case 3:
					{
					pxMagic = new CMagic;
					if ( pxMagic->CreateMagic(_MONMAGIC_SIEGECAR_SHOOT, m_nPosX, m_nPosY, nTargetX+2, nTargetY+2, this, 0, 210) )
						g_xGameProc.m_xMagicList.Insert (pxMagic);
					else
						delete pxMagic;
					}
					break;
				case 4:
					{
					pxMagic = new CMagic;
					if ( pxMagic->CreateMagic(_MONMAGIC_SIEGECAR_SHOOT, m_nPosX, m_nPosY, nTargetX+3, nTargetY+2, this, 0, 280) )
						g_xGameProc.m_xMagicList.Insert (pxMagic);
					else
						delete pxMagic;
					}
					break;
				case 5:
					{
					pxMagic = new CMagic;
					if ( pxMagic->CreateMagic(_MONMAGIC_SIEGECAR_SHOOT, m_nPosX, m_nPosY, nTargetX-2, nTargetY, this, 0, 350) )
						g_xGameProc.m_xMagicList.Insert (pxMagic);
					else
						delete pxMagic;
					}
					break;
				case 6:
					{
					pxMagic = new CMagic;
					if ( pxMagic->CreateMagic(_MONMAGIC_SIEGECAR_SHOOT, m_nPosX, m_nPosY, nTargetX, nTargetY-2, this, 0, 420) )
						g_xGameProc.m_xMagicList.Insert (pxMagic);
					else
						delete pxMagic;
					}
					break;
				case 7:
					{
					pxMagic = new CMagic;
					if ( pxMagic->CreateMagic(_MONMAGIC_SIEGECAR_SHOOT, m_nPosX, m_nPosY, nTargetX-2, nTargetY-2, this, 0, 490) )
						g_xGameProc.m_xMagicList.Insert (pxMagic);
					else
						delete pxMagic;
					}
					break;
				case 8:
					{
					pxMagic = new CMagic;
					if ( pxMagic->CreateMagic(_MONMAGIC_SIEGECAR_SHOOT, m_nPosX, m_nPosY, nTargetX-3, nTargetY-2, this, 0, 560) )
						g_xGameProc.m_xMagicList.Insert (pxMagic);
					else
						delete pxMagic;
					}
					break;
				}
			}
		}
		break;

//	case 224:	// 마총패 공격 2
//		{
//			INT nPosX, nPosY;
//			INT nTargetX, nTargetY;
//			
//			switch( bDir )
//			{
//			case 0:
//				nPosX = m_nPosX;
//				nPosY = m_nPosY + 2;
//				nTargetX = m_nPosX;
//				nTargetY = m_nPosY - 10;
//				break;
//			case 1:
//				nPosX = m_nPosX - 2;
//				nPosY = m_nPosY + 2;
//				nTargetX = m_nPosX + 10;
//				nTargetY = m_nPosY - 10;
//				break;
//			case 2:
//				nPosX = m_nPosX - 2;
//				nPosY = m_nPosY;
//				nTargetX = m_nPosX + 10;
//				nTargetY = m_nPosY;
//				break;
//			case 3:
//				nPosX = m_nPosX - 2;
//				nPosY = m_nPosY - 2;
//				nTargetX = m_nPosX + 10;
//				nTargetY = m_nPosY + 10;
//				break;
//			case 4:
//				nPosX = m_nPosX;
//				nPosY = m_nPosY - 2;
//				nTargetX = m_nPosX;
//				nTargetY = m_nPosY + 10;
//				break;
//			case 5:
//				nPosX = m_nPosX + 2;
//				nPosY = m_nPosY - 2;
//				nTargetX = m_nPosX - 10;
//				nTargetY = m_nPosY + 10;
//				break;
//			case 6:
//				nPosX = m_nPosX + 2;
//				nPosY = m_nPosY;
//				nTargetX = m_nPosX - 10;
//				nTargetY = m_nPosY;
//				break;
//			case 7:
//				nPosX = m_nPosX + 2;
//				nPosY = m_nPosY + 2;
//				nTargetX = m_nPosX - 10;
//				nTargetY = m_nPosY - 10;
//				break;
//			}
//			
//			CMagic* pxMagic;
//			pxMagic = new CMagic;
//			if ( pxMagic->CreateMagic( _MONMAGIC_MACHONG_ATTACK_B_FLY_0 + bDir, nPosX, nPosY, nTargetX, nTargetY, this, 0, 700 ) )
//				g_xGameProc.m_xMagicList.Insert (pxMagic);
//			else
//				delete pxMagic;
//		}
//		break;

	}
}


VOID CActor::OnHit(LPPACKETMSG lpPacketMsg)
{
	BYTE bDir;
	bDir	= (BYTE)(lpPacketMsg->stDefMsg.wSeries);

	m_nPosX = lpPacketMsg->stDefMsg.wParam;
	m_nPosY = lpPacketMsg->stDefMsg.wTag;
	SetMotionFrame(_MT_MON_ATTACK_A, bDir);

	// 좀비 억지로 살리기
	m_bIsDead = 0;

	// 몬스터일때.
	if ( m_stFeature.bGender == _GENDER_MON && g_xGameProc.m_bShowMonEffect )
	{
		CMagic* pxMagic;

		WORD wDress;
		if ( m_stFeature.bGender == _GENDER_MON )
		{
			wDress = MAKEWORD(m_stFeature.bDress, m_stFeature.bHair);
		}
		else
		{
			wDress = m_stFeature.bDress;
		}

		switch ( wDress )
		{
		case 9:		// 론.
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_EXPLODE, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
			break;
		case 5:		// 바쿠가르나.
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_BLACK1, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
			break;
		case 19:		// 홍의법사
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_RED1, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
			break;
		case 203:		// 빙혼무장2
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_HANBINGMA_MAGIC, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
			break;
		case 45:		// 우면귀왕. 
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_COWGHOST, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
			break;
		case 90:		// 신수.
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_SINSU, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this, 0, 900) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
			break;
		case 43:		// 화염우면귀.
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_COWFLAME, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
			break;
		case 85:		// 주마왕.
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_JUMAWANG, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
			break;
		case 67:		// 촉룡신.
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_BIGGINE_ATT, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this, 200) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
			break;	
		case 75:		// 쐐기나방.
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_SSEGI, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this, -1, 400) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
			break;	
		case 47:		// 둥.
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_DUNG, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this, -1, 300) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
			break;	
		case 37:		// 동굴구더기.
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_GUDEGI, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this, -1, 300) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
			break;	
		case 94:		// 사어.
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_SANDFISH, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
			break;	
		case 97:		// 풍백.
		{
			POINT ptAtt;
			g_xGameProc.m_xMap.GetNextTileCanMove(m_nPosX, m_nPosY, m_bCurrDir, 1, &ptAtt);
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_WINDGOD, ptAtt.x, ptAtt.y, ptAtt.x, ptAtt.y, this, -1, 600) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
			break;	
		}
		case 132:		// 구오좀비.
		{
			POINT ptAtt;
			g_xGameProc.m_xMap.GetNextTileCanMove(m_nPosX, m_nPosY, m_bCurrDir, 1, &ptAtt);
			pxMagic = new CMagic;
			// _MONMAGIC_GUOBLUEATT
			// _MONMAGIC_GUOREDATT
			if ( pxMagic->CreateMagic(_MONMAGIC_GUOBLUEATT, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this, -1, 600) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
			break;	
		}
/*		case 164:
		{
			POINT ptAtt;
			g_xGameProc.m_xMap.GetNextTileCanMove(m_nPosX, m_nPosY, m_bCurrDir, 1, &ptAtt);
			pxMagic = new CMagic;

			if ( pxMagic->CreateMagic(_MONMAGIC_MAWANG_MA, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this, -1, 600) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
			break;	
		}
*/		case 141:
		{
			SetMotionFrame(_MT_MON_SPELL_A, bDir);
			break;
		}
		case 113:		// 경비검기.
		{
			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_GUMGI, bDir);
			m_bUseSwordEffect = TRUE;
			break;
		}
		case 98:		// 상급괴물검기.
		{
			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_NUMAGUMGI, bDir);
			m_bUseSwordEffect = TRUE;
			break;
		}
		case 120:		// 신기선보스검기.
		{
			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_BOSSATT, bDir);
			m_bUseSwordEffect = TRUE;
			break;
		}
		case 186:		// 타당가
		{
			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_TADANGGA_ATTACK, bDir);
			m_bUseSwordEffect = TRUE;
			break;
		}
		case 130:		// 광명우사.
		{
			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_LIGHTRIGHTATT, bDir);
			m_bUseSwordEffect = TRUE;
			break;
		}
		case 131:		// 광명좌사.
		{
			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_LIGHTLEFTATT, bDir);
			m_bUseSwordEffect = TRUE;
			break;
		}
		case 139:		// 우면본왕검기.
		{
			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_REALUMAATT, bDir);
			m_bUseSwordEffect = TRUE;
			break;
		}
		case 150:		// 돈왕검기.
		{
			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_DONKING, bDir);
			m_bUseSwordEffect = TRUE;
			break;
		}
/*		case 151:		// 왕중왕검기.
		{
			POINT ptAtt;
			g_xGameProc.m_xMap.GetNextTileCanMove(m_nPosX, m_nPosY, m_bCurrDir, 1, &ptAtt);
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_KINGKING2, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this, -1, 0) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
			SetMotionFrame(_MT_MON_ATTACK_B, bDir);
			m_bUseSwordEffect = TRUE;
			break;
		}
*/		case 152:		// 변종혈사갈.
		{
			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_BLOODSAGAL, bDir);
			m_bUseSwordEffect = TRUE;
			break;
		}
		case 164:		// 진천마신 검기.
		{
			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_MAWANG_A2, bDir);
			m_bUseSwordEffect = TRUE;
			break;
		}	
		case 198:		// 지천멸왕 검기.
		{
			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_JICHUN_ATTACK, bDir);
			m_bUseSwordEffect = TRUE;
			break;
		}
		case 197:		// 육혈
		{
			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_YOUKHYUL_ATTACK, bDir);
			m_bUseSwordEffect = TRUE;
			break;
		}
		case 213:		// 가무녀2
		{
			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_GAMU_B, bDir);
			m_bUseSwordEffect = TRUE;
			break;
		}
//		case 210:		// 호위장수
//		{
//			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_GUARDGEN_B, 0);
//			m_bUseSwordEffect = TRUE;
//			break;
//		}
		case 211:		// 새벽여왕
		{
			LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_DAWNQUEEN_B, 0);
			m_bUseSwordEffect = TRUE;
			break;
		}
		default :
			break;
		}
	}
}


VOID CActor::StruckMsgReassign()
{
	INT			nCnt;
	WORD		wDamage = 0;
	INT			nLeftMsgCnt;
	LPPACKETMSG	lpPacketMsg;

	lpPacketMsg  = NULL;
	nLeftMsgCnt = m_xPacketQueue.GetCount();

	m_bDelStruckCnt = 0;

	if ( nLeftMsgCnt > 1 )
	{
		for ( nCnt = 0; nCnt < nLeftMsgCnt; nCnt++ )
		{
			lpPacketMsg = (LPPACKETMSG)m_xPacketQueue.PopQ();
			if ( lpPacketMsg )
			{
				if ( lpPacketMsg->stDefMsg.wIdent == SM_STRUCK )
				{
					wDamage			 = lpPacketMsg->stDefMsg.wSeries;
					FLOAT wHPRate = 0.0f;
					if ( lpPacketMsg->stDefMsg.wTag != 0 )
					{
						wHPRate = (FLOAT)((FLOAT)lpPacketMsg->stDefMsg.wParam/(FLOAT)lpPacketMsg->stDefMsg.wTag);
					}
					m_wHP			 = lpPacketMsg->stDefMsg.wParam;
					m_wMAXHP		 = lpPacketMsg->stDefMsg.wTag;
					m_bHPPercent     = (BYTE)(wHPRate*100);
					m_bDelStruckCnt++;
					SAFE_DELETE(lpPacketMsg);
				}
				else
				{
					m_xPacketQueue.PushQ((BYTE*)lpPacketMsg);
				}
			}
		}
	}
}


/******************************************************************************************************************

	함수명 : CActor::UpdatePacketState()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CActor::UpdatePacketState()
{
	LPPACKETMSG	lpPacketMsg = NULL;

	if ( m_bCurrMtn == _MT_MON_STAND || m_bIsDead )
	{
		INT	nLeftMsgCnt = m_xPacketQueue.GetCount();

		if ( nLeftMsgCnt > 0 )
		{
			if ( m_xPacketQueue.GetCount() >= 3 )		m_bMsgHurryCheck = TRUE;
			else										m_bMsgHurryCheck = FALSE;

			lpPacketMsg = (LPPACKETMSG)m_xPacketQueue.PopQ();
				
			if ( lpPacketMsg )
			{
				switch ( lpPacketMsg->stDefMsg.wIdent )
				{
					case SM_NOWDEATH:
					case SM_SKELETON:
					case SM_DEATH:
					{
						OnDeath(lpPacketMsg);				
						break;
					}
					case SM_ALIVE:				
					{	
						OnAlive(lpPacketMsg);
						break;	
					}
					case SM_WALK:
					{	
						OnWalk(lpPacketMsg);				
						break;	
					}
					case SM_MAGICHIT:
					{
						SetMotionFrame(_MT_MON_SPELL_A, m_bCurrDir);
						break;	
					}
					case SM_TURN:
					case SM_REVIVAL:
					{
						OnTurn(lpPacketMsg);
						break;	
					}
					case SM_DIGUP:				
					{	
						OnDigup(lpPacketMsg);				
						break;	
					}
					case SM_DIGDOWN:			
					{	
						OnDigDown(lpPacketMsg);				
						break;	
					}
					case SM_BACKSTEP:			
					{
						OnBackStep(lpPacketMsg);			
						break;	 
					}
					case SM_BACKSTEP2:
					{
						m_bIsSturn = TRUE;
						OnBackStep(lpPacketMsg);
						break;
					}
					case SM_STRUCK:
					{
						OnStruck(lpPacketMsg);				
						break;	
					}
					case SM_SPACEMOVE_SHOW:		
					case SM_SPACEMOVE_SHOW2:	
					case SM_PULL_SHOW:
					{
						OnSpaceMoveShow(lpPacketMsg);		
						break;	
					}
					case SM_SPACEMOVE_HIDE:		
					case SM_SPACEMOVE_HIDE2:	
					{
						OnSpaceMoveHide(lpPacketMsg);		
						break;	
					}
					case SM_STRUCK2:				
					{
						OnStruck(lpPacketMsg);
						LPPACKETMSG	lpPacketMsgAdd = new PACKETMSG;
						memcpy(lpPacketMsgAdd , lpPacketMsg, sizeof(PACKETMSG));
						lpPacketMsgAdd->stDefMsg.wIdent = SM_STRUCK;
						m_xPacketQueue.PushQ((BYTE*)lpPacketMsgAdd );
						break;	
					}
					case SM_HIT:
					{	
						OnHit(lpPacketMsg);					
						break;	
					}
					case SM_FLYAXE:				
					{	
						OnFlyAxe(lpPacketMsg);				
						break;	
					}
					case SM_LIGHTING:			
					{	
						OnLighting(lpPacketMsg);			
						break;	
					}
					default:
					{										
						break;	
					}
				}

				SAFE_DELETE(lpPacketMsg);

				if ( m_bIsDead )
				{
					if ( m_bCurrMtn == _MT_MON_SKELETON )
					{
						SetMotionFrame(_MT_MON_SKELETON, m_bCurrDir);
					}
					else
					{
						SetMotionFrame(_MT_MON_DIE, m_bCurrDir);
						m_dwCurrFrame = m_dwEndFrame - 1;						
					}
				}

				return TRUE;
			}
		}			
	}

	return FALSE;
}



/******************************************************************************************************************

	함수명 : CActor::LoadEffect()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : CImageHandler* pxImgHandler
	         WORD wEffectNum
	         BYTE bDir
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CActor::LoadEffect(CImageHandler* pxImgHandler, WORD wEffectNum, BYTE bDir, int nElement)
{
	BYTE bIndex = 0;

	LPEFFECTSPRINFO pstEffect = g_xSpriteInfo.GetEffectInfo(wEffectNum);

	if ( pstEffect )
	{
		m_bEffectImgIdx	   = (BYTE)(pstEffect->wImgIdx);		
		m_dwFstEffectFrame = pstEffect->dwFstFrm;
		m_dwEndEffectFrame = pstEffect->dwEndFrm;

		if ( bDir )
		{
			// 해골진왕.
			WORD wDress = MAKEWORD(m_stFeature.bDress, m_stFeature.bHair);
			if ( wDress == 141 && m_bCurrMtn == _MT_MON_DIE )
			{
				m_dwFstEffectFrame = m_dwFstEffectFrame + bDir*20;
				m_dwEndEffectFrame = m_dwEndEffectFrame + bDir*20;
			}
			else
			{
				m_dwFstEffectFrame = m_dwFstEffectFrame + bDir*10;
				m_dwEndEffectFrame = m_dwEndEffectFrame + bDir*10;
			}
		}
		m_dwCurrEffectFrame = m_dwFstEffectFrame;
		m_bEffectFrame = 0;

		m_bLightRadius[0] = pstEffect->bLightRadius[0];
		m_bLightRadius[1] = pstEffect->bLightRadius[1];

		m_bLightColor[0][0]	= pstEffect->bLightColor[0][0];
		m_bLightColor[0][1]	= pstEffect->bLightColor[0][1];
		m_bLightColor[0][2]	= pstEffect->bLightColor[0][2];
		
		m_bLightColor[1][0]	= pstEffect->bLightColor[1][0];
		m_bLightColor[1][1]	= pstEffect->bLightColor[1][1];
		m_bLightColor[1][2]	= pstEffect->bLightColor[1][2];

		m_bEffectColor[0] = pstEffect->bMagicColor[0];
		m_bEffectColor[1] = pstEffect->bMagicColor[1];
		m_bEffectColor[2] = pstEffect->bMagicColor[2];

		INT nTemp = 0, nIndex = 0;
		BOOL bCheck = FALSE;

		if ( m_nIdentity == g_xGameProc.m_xMyHero.m_nIdentity )
		{
			for ( INT nI=0; nI<7; nI++ )
			{
				if ( g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[nI] > 0 )
				{
					if ( g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[nI] > nTemp )
					{
						bCheck = TRUE;
						nTemp = g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[nI];
						nIndex = nI;
					}
				}
			}
		}

		// 칼공격일 경우에만 적용
		if ( bCheck &&  g_xGameProc.m_xInterface.m_xStatusWnd.m_stEquipItem[_U_WEAPON].xItem.m_stItemInfo.Desc[11] > 0 && m_bUseSwordEffect == TRUE)
		{
			bIndex = g_xGameProc.m_xInterface.m_xStatusWnd.m_stEquipItem[_U_WEAPON].xItem.m_stItemInfo.Desc[11] - 1;

			m_bEffectColor[0] = g_bWeaponEnergyColor[bIndex][0];
			m_bEffectColor[1] = g_bWeaponEnergyColor[bIndex][1];
			m_bEffectColor[2] = g_bWeaponEnergyColor[bIndex][2];
		}
		else if ( bCheck && m_bUseSwordEffect == TRUE )
		{
			bIndex = nIndex;

			m_bEffectColor[0] = g_bWeaponEnergyColor[bIndex][0];
			m_bEffectColor[1] = g_bWeaponEnergyColor[bIndex][1];
			m_bEffectColor[2] = g_bWeaponEnergyColor[bIndex][2];
		}
		else if (g_xGameProc.m_xInterface.m_xStatusWnd.m_stEquipItem[_U_WEAPON].xItem.m_stItemInfo.stStdItem.bAtomDCType > 0 && m_bUseSwordEffect == TRUE)
		{
			bIndex = g_xGameProc.m_xInterface.m_xStatusWnd.m_stEquipItem[_U_WEAPON].xItem.m_stItemInfo.stStdItem.bAtomDCType - 1;

			m_bEffectColor[0] = g_bWeaponEnergyColor[bIndex][0];
			m_bEffectColor[1] = g_bWeaponEnergyColor[bIndex][1];
			m_bEffectColor[2] = g_bWeaponEnergyColor[bIndex][2];
		}
		else if ( nElement != 7 && nElement != -1 )
		{
			m_bEffectColor[0] = g_bWeaponEnergyColor[nElement][0];
			m_bEffectColor[1] = g_bWeaponEnergyColor[nElement][1];
			m_bEffectColor[2] = g_bWeaponEnergyColor[nElement][2];
		}
		else
		{
			m_bEffectColor[0] = pstEffect->bMagicColor[0];
			m_bEffectColor[1] = pstEffect->bMagicColor[1];
			m_bEffectColor[2] = pstEffect->bMagicColor[2];
		}

		

		// 염색 마법 칼라값 보정
		/*if ( wEffectNum == _SKILL_FIREBOOM )
		{
			bIndex = g_xGameProc.m_xInterface.m_xStatusWnd.m_stEquipItem[_U_CHARM].xItem.m_stItemInfo.stStdItem.FuncType - 1;

			m_bEffectColor[0] = g_bWeaponEnergyColor[bIndex][0];
			m_bEffectColor[1] = g_bWeaponEnergyColor[bIndex][1];
			m_bEffectColor[2] = g_bWeaponEnergyColor[bIndex][2];
		}*/

		m_bEffectOpa	  = pstEffect->bOpa;
		m_bEffectBlend	  = pstEffect->bBlendType;

		INT nWaveNum = wEffectNum*10 + 10000;
		g_SoundManager.SndmngrPlayWavSound(nWaveNum, m_nPosX, m_nPosY);
		
		return TRUE;

	}
	return FALSE;
}


VOID CActor::MakeMagicStream(WORD wMagicID, INT nTarID, INT nTarX, INT nTarY)
{
	BYTE  bDir16	 = (BYTE)g_xGameProc.m_xMap.GetNextDirection(m_nPosX, m_nPosY, nTarX, nTarY);
	POINT ptTileGap  = {0, 0};
	POINT ptTileDest = {0, 0};
	BYTE  bLoopCnt	 = 9;
	BYTE  bDelay     = 150;

	if ( wMagicID == _SKILL_SHOOTLIGHTEN_ADD )
	{
		bDelay   = 30;
	}

	switch ( bDir16 )
	{
	case 0 :	ptTileGap.x =  0; ptTileGap.y = -1; break;
	case 1 :	ptTileGap.x =  1; ptTileGap.y = -1; break;
	case 2 :	ptTileGap.x =  1; ptTileGap.y =  0; break;
	case 3 :	ptTileGap.x =  1; ptTileGap.y =  1; break;
	case 4 :	ptTileGap.x =  0; ptTileGap.y =  1; break;
	case 5 :	ptTileGap.x = -1; ptTileGap.y =  1; break;
	case 6 :	ptTileGap.x = -1; ptTileGap.y =  0; break;
	case 7 :	ptTileGap.x = -1; ptTileGap.y = -1; break;
	}

	for ( INT nCnt = 0; nCnt < bLoopCnt; nCnt++ )
	{
		CMagicStream* pxMagicStream;
		pxMagicStream = new CMagicStream;
		ptTileDest.x = m_nPosX + ptTileGap.x*(nCnt+1);
		ptTileDest.y = m_nPosY + ptTileGap.y*(nCnt+1);

		if ( pxMagicStream->CreateMagic(wMagicID, m_nPosX, m_nPosY, ptTileDest.x, ptTileDest.y, NULL, nTarID, (WORD)(nCnt*bDelay), ptTileGap) )
		{
			g_xGameProc.m_xGroundMagicList.Insert (pxMagicStream);
		}
		else
		{
			delete pxMagicStream;
		}
	}
}


VOID CActor::MakeMagicStreamEx(WORD wMagicID, INT nStartX, INT nStartY, INT nTarX, INT nTarY)
{
	BYTE  bDir16	 = (BYTE)g_xGameProc.m_xMap.GetNextDirection(nStartX, nStartY, nTarX, nTarY);
	POINT ptTileGap  = {0, 0};
	POINT ptTileDest = {0, 0};
	BYTE  bLoopCnt	 = 5;
	BYTE  bDelay     = 150;

	switch ( bDir16 )
	{
	case 0 :	ptTileGap.x =  0; ptTileGap.y = -1; break;
	case 1 :	ptTileGap.x =  1; ptTileGap.y = -1; break;
	case 2 :	ptTileGap.x =  1; ptTileGap.y =  0; break;
	case 3 :	ptTileGap.x =  1; ptTileGap.y =  1; break;
	case 4 :	ptTileGap.x =  0; ptTileGap.y =  1; break;
	case 5 :	ptTileGap.x = -1; ptTileGap.y =  1; break;
	case 6 :	ptTileGap.x = -1; ptTileGap.y =  0; break;
	case 7 :	ptTileGap.x = -1; ptTileGap.y = -1; break;
	}

	for ( INT nCnt = 0; nCnt < bLoopCnt; nCnt++ )
	{
		CMagicStream* pxMagicStream;
		pxMagicStream = new CMagicStream;
		ptTileDest.x = nStartX + ptTileGap.x*(nCnt);
		ptTileDest.y = nStartY + ptTileGap.y*(nCnt);

		if ( pxMagicStream->CreateMagic(wMagicID, nStartX, nStartY, ptTileDest.x, ptTileDest.y, NULL, 0, (WORD)(nCnt*bDelay), ptTileGap) )
		{
			g_xGameProc.m_xGroundMagicList.Insert (pxMagicStream);
		}
		else
		{
			delete pxMagicStream;
		}
	}
}

/******************************************************************************************************************

	함수명 : CActor::DrawEffect()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CActor::DrawEffect()
{
	if ( m_bUseEffect || m_bUseSwordEffect )
	{
		if ( g_xMainWnd.Get3DDevice() )
		{
			WORD wFileType		= _IMAGE_MAGIC;
			BOOL bIndexSetted	= FALSE;
			CWHWilImageData*	pxWilImg;

			if ( m_bEffectImgIdx == _IMAGE_MAGIC || m_bEffectImgIdx == _IMAGE_MAGICEX || m_bEffectImgIdx == _IMAGE_MAGICEX2 || m_bEffectImgIdx == _IMAGE_MAGICEX3 )
			{
				wFileType = _TEXTR_FILE_MAGIC;
			}
			else if ( m_bEffectImgIdx == _IMAGE_MONMAGIC || m_bEffectImgIdx == _IMAGE_MONMAGICEX || m_bEffectImgIdx == _IMAGE_MONMAGICEX2 || m_bEffectImgIdx == _IMAGE_MONMAGICEX3 || m_bEffectImgIdx == _IMAGE_MONMAGICEX4 || m_bEffectImgIdx == _IMAGE_MONMAGICEX5 )
			{
				wFileType = _TEXTR_FILE_MONMAGIC;
			}
			if ( !m_bUseEffect )
			{
				m_dwCurrEffectFrame = m_dwFstEffectFrame + m_dwCurrFrame - m_dwFstFrame;
			}

			LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(wFileType, m_bEffectImgIdx, m_dwCurrEffectFrame);

			pxWilImg = &g_xGameProc.m_xImage.m_xImageList[m_bEffectImgIdx];
			if ( pxWilImg->NewSetIndex(m_dwCurrEffectFrame) )
			{
				D3DVECTOR vTrans;
				D3DMATRIX matTrans;
				D3DMATRIX matScale;
				D3DMATRIX matWorld;
				D3DMATRIX matWorldOriginal;
				D3DMATERIAL7 mtrl;

				D3DUtil_InitMaterial(mtrl, (FLOAT)m_bEffectColor[0]/255.0f, (FLOAT)m_bEffectColor[1]/255.0f, (FLOAT)m_bEffectColor[2]/255.0f);
//				D3DUtil_InitMaterial(mtrl, (FLOAT)((FLOAT)140/255.0f), (FLOAT)((FLOAT)200/255.0f), (FLOAT)((FLOAT)150/255.0f));

				mtrl.diffuse.a = (FLOAT)(m_bEffectOpa)/255.0f;
				g_xMainWnd.Get3DDevice()->SetMaterial(&mtrl);

 				vTrans.x = (FLOAT)m_nScrnPosX+(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth/2+pxWilImg->m_lpstNewCurrWilImageInfo->shPX-400; 
				vTrans.y = (FLOAT)-m_nScrnPosY-(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight/2-pxWilImg->m_lpstNewCurrWilImageInfo->shPY+300; 
				vTrans.z = 0;

				if( SUCCEEDED(g_xMainWnd.Get3DDevice()->BeginScene()) )
				{
					g_xMainWnd.Get3DDevice()->GetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

					D3DUtil_SetTranslateMatrix(matTrans, vTrans);
					D3DUtil_SetScaleMatrix(matScale, (FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight, 1.0f);
					D3DMath_MatrixMultiply(matWorld, matScale, matTrans);
					g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);

					SetBlendRenderState(g_xMainWnd.Get3DDevice(), m_bEffectBlend, &mtrl);

					g_xMainWnd.Get3DDevice()->SetTexture(0, lpddsTextr); 

					g_xMainWnd.Get3DDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_VERTEX, m_avBoard, 4, NULL);

					ResetBlendenderState(g_xMainWnd.Get3DDevice());

					g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

					g_xMainWnd.Get3DDevice()->EndScene();
				}
			}

			if ( m_bLightRadius[1] != 0 )
			{
				if ( m_bUseEffect )
				{
					if ( m_bEffectFrame < m_bEffectFrameCnt / 2 )
					{
						m_bLightRadius[0] = m_bEffectFrame;
						m_bLightRadius[1] = (BYTE)(m_bEffectFrame+1);
					}
					else
					{
						m_bLightRadius[0] = (BYTE)(m_bEffectFrameCnt - m_bEffectFrame -1);
						m_bLightRadius[1] = (BYTE)(m_bEffectFrameCnt - m_bEffectFrame);
					}					
					g_xGameProc.m_xLightFog.SetLightRadiusWithRing(
													  m_nScrnPosX + _CELL_WIDTH/2,
							  						  m_nScrnPosY + _CELL_HEIGHT/2, 
													  m_bLightRadius[0], m_bLightColor[0][0], m_bLightColor[0][1], m_bLightColor[0][2], 
													  m_bLightRadius[1], m_bLightColor[1][0], m_bLightColor[1][1], m_bLightColor[1][2]);
				}
				else if ( m_bUseSwordEffect )
				{
					if ( m_dwEndEffectFrame - m_dwFstEffectFrame > 8 )
					{
						m_bLightRadius[0] = (BYTE)((m_dwCurrEffectFrame - m_dwFstEffectFrame)/2 + 2);
						m_bLightRadius[1] = (BYTE)((m_dwCurrEffectFrame - m_dwFstEffectFrame)/2 + 3);
					}
					else
					{
						m_bLightRadius[0] = (BYTE)(m_dwCurrEffectFrame - m_dwFstEffectFrame + 2);
						m_bLightRadius[1] = (BYTE)(m_dwCurrEffectFrame - m_dwFstEffectFrame + 3);
					}
					g_xGameProc.m_xLightFog.SetLightRadiusWithRing(
													  m_nScrnPosX + _CELL_WIDTH/2,
							  						  m_nScrnPosY + _CELL_HEIGHT/2, 
													  m_bLightRadius[0], m_bLightColor[0][0], m_bLightColor[0][1], m_bLightColor[0][2], 
													  m_bLightRadius[1], m_bLightColor[1][0], m_bLightColor[1][1], m_bLightColor[1][2]);
				}
			}

			return TRUE;
		}
	}
	return FALSE;
}



/******************************************************************************************************************

	함수명 : CActor::UpdateMotionState()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : INT nLoopTime
	         SHORT shStartViewTileX
	         SHORT shStartViewTileY
	         SHORT shViewOffsetX
	         SHORT shViewOffsetY
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CActor::UpdateMotionState(INT nLoopTime, BOOL bIsMoveTime)
{
	m_nABlendCurrDelay += nLoopTime;

	if ( m_nABlendCurrDelay >= m_nABlendDelay )
	{
		m_nABlendCurrDelay = 0;
		m_nABlendDelay	   = 0;
		m_bABlendRev	   = FALSE;
	}

	if ( m_bCurrMtn == _MT_MON_DIE && m_dwCurrFrame >= m_dwEndFrame-1 )
	{
		m_bIsDead = TRUE;
	}

	if ( UpdateMove(bIsMoveTime) )
	{
		UpdatePacketState();
		return;
	}
	else
	{
		m_nCurrDelay += nLoopTime;

		if ( m_nCurrDelay > m_nDelay )
		{
			m_nCurrDelay = 0;

			if ( m_dwCurrFrame < m_dwEndFrame )
			{
				m_dwCurrFrame++;

				PlayActSound();

				if ( m_bMsgHurryCheck )			
				{
					m_nDelay = m_nDelay/2;
					m_bMsgHurryCheck = FALSE;
				}
			}
		}

		if ( m_dwCurrFrame >= m_dwEndFrame )
		{
			m_nShiftTileX = 0;
			m_nShiftTileY = 0;
			m_nShiftPixelX = 0;
			m_nShiftPixelY = 0;

			m_bReverse		= FALSE;
			m_dwCurrEffectFrame = 0;
			m_dwFstEffectFrame = 0;
			m_dwEndEffectFrame = 0;
			m_bEffectFrame = 0;
			m_bEffectFrameCnt = _DEFAULT_SPELLFRAME;
			m_bUseEffect = FALSE;
			m_bUseSwordEffect = FALSE;

			m_dwCurrFrame = m_dwFstFrame;

			if ( m_bCurrMtn == _MT_MON_APPEAR )				// 사북성 문짝 다 열린 후 다 닫힌 후 처리
			{
				WORD wDress = MAKEWORD(m_stFeature.bDress, m_stFeature.bHair);
				if ( m_stFeature.bGender == _GENDER_MON && ( wDress == 530 || wDress == 531 || wDress == 532 || wDress == 533 || wDress == 538 /*성훈씨*/) )
				{
					if ( m_bAppearState == _DIG_UP )
						m_bCurrDir = 7;
					else
					{
						m_bAppearState = _DIG_UP;
						m_bCurrDir = 0;
					}
				}
			}

			if ( m_bIsDead )
			{
				if ( m_bCurrMtn == _MT_MON_SKELETON )
				{
					SetMotionFrame(_MT_MON_SKELETON, m_bCurrDir);
				}
				else
				{
					SetMotionFrame(_MT_MON_DIE, m_bCurrDir);
					m_dwCurrFrame = m_dwEndFrame - 1;
				}
			}
			else
			{
				SetMotionFrame(_MT_MON_STAND, m_bCurrDir);
			}

			if( m_nCharState & 0X1 )		// 석화상태.
			{
				WORD wDress;
				if ( m_stFeature.bGender == _GENDER_MON )
				{
					wDress = MAKEWORD(m_stFeature.bDress, m_stFeature.bHair);
				}
				else
				{
					wDress = m_stFeature.bDress;
				}

				switch ( wDress )
				{
				case 83: //주마신장.
				case 84: //주마호법.
				case 85: //주마왕.
					SetMotionFrame(_MT_MON_APPEAR, 0);
					m_dwEndFrame = m_dwFstFrame + 1;
					m_bCurrMtn = _MT_MON_STAND;
				}
			}

			if ( m_bAppearState == _DIG_DOWN )
			{
				m_bAppearState = _DIG_DOWNDEL;
			}
		}

		UpdatePacketState();
	}
}



/******************************************************************************************************************

	함수명 : CActor::UpdateMove(BOOL bIsMoveTime)

	작성자 : 
	작성일 : 

	목적   : 
	출력   : BOOL

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CActor::UpdateMove(BOOL bIsMoveTime)
{
	if ( m_bCurrMtn == _MT_MON_WALK )
	{
		m_nCurrDelay = 0;

		if ( bIsMoveTime )
		{
			if ( m_bBackStepFrameCnt == 0 )
			{
				BYTE bMoveSkipLevel = 0;

				if( m_nCharState & 0X8000000 )			
				{
					bMoveSkipLevel = 1;
				}

				if ( bMoveSkipLevel > 0 )
				{
					bMoveSkipLevel++;
					m_dwCurrMoveSkip++;

					if ( m_dwCurrMoveSkip > 100000 )
					{
						m_dwCurrMoveSkip = 1;
					}

					if ( (m_dwCurrMoveSkip % bMoveSkipLevel) )
					{
						return FALSE;
					}
				}
			}

			if ( m_bBackStepFrameCnt )
			{
				m_dwCurrFrame += 2;
				m_bBackStepFrame += 2;
				if ( m_bBackStepFrame >= m_bBackStepFrameCnt )
				{
					m_bBackStepFrame = m_bBackStepFrameCnt;
				}
			}
			else
			{
				m_dwCurrFrame++;

				WORD wDress = MAKEWORD(m_stFeature.bDress, m_stFeature.bHair);
				// 발석차 연노차일 경우 움직이는 소리 내 준다.
				if ( wDress == 167 || wDress == 169 )
				{
					PlayActSound();
				}

				if ( m_bMsgHurryCheck )			
				{
					m_dwCurrFrame++;
				}
			}

			if ( m_dwCurrFrame >= m_dwEndFrame-m_bMoveNextFrmCnt && !m_bIsMoved )
			{
				SetMoved();
				m_bIsMoved = TRUE;
			}
		}
		else
		{
			int ntest = 0;
		}

		// 연속적인 프레임 중에서 해야할일.
		if ( m_dwCurrFrame >= m_dwEndFrame )
		{
			m_dwCurrFrame = m_dwEndFrame - 1;

			m_nShiftTileX = 0;
			m_nShiftTileY = 0;
			m_nShiftPixelX = 0;
			m_nShiftPixelY = 0;

			m_dwCurrEffectFrame = 0;
			m_dwFstEffectFrame = 0;
			m_dwEndEffectFrame = 0;
			m_bEffectFrame = 0;
			m_bUseEffect = FALSE;
			m_bUseSwordEffect = FALSE;
			m_dwCurrFrame = m_dwFstFrame;

			m_bBackStepFrame = 0;
			m_bBackStepFrameCnt = 0;

			m_bIsMoved = FALSE;

			SetMotionFrame(_MT_MON_STAND, m_bCurrDir);
		}
		else if ( m_dwCurrFrame < m_dwEndFrame )
		{
			if ( m_bBackStepFrameCnt == 0 )
				SetMoving();
			else
				SetBackStepMoving();
		}
		return TRUE;
	}
	return FALSE;
}


VOID CActor::DrawCharLight(BOOL bUseScrnPos)
{
	if ( bUseScrnPos )
	{
		if ( m_bLightSize == 2 )
			g_xGameProc.m_xLightFog.SetLightRadiusWithCircle(m_rcActor.left+_CELL_WIDTH/2, m_rcActor.top+_CELL_HEIGHT/2, 4, 100, 100, 100);
		else if ( m_bLightSize == 0 )
			g_xGameProc.m_xLightFog.SetLightRadiusWithCircle(m_rcActor.left+_CELL_WIDTH/2, m_rcActor.top+_CELL_HEIGHT/2, 4, 10, 5, 5);
		else if ( m_bLightSize == 8 )
			g_xGameProc.m_xLightFog.SetLightRadiusWithCircle(m_rcActor.left+_CELL_WIDTH/2, m_rcActor.top+_CELL_HEIGHT/2, 8, 255, 255, 255);
		else
			g_xGameProc.m_xLightFog.SetLightRadiusWithCircle(m_rcActor.left+_CELL_WIDTH/2, m_rcActor.top+_CELL_HEIGHT/2, 10, 255, 255, 255);
	}
	else
	{
		if ( m_bLightSize == 2 )
			g_xGameProc.m_xLightFog.SetLightRadiusWithCircle(m_nScrnPosX, m_nScrnPosY, 4, 100, 100, 100);
		else if ( m_bLightSize == 0 )
			g_xGameProc.m_xLightFog.SetLightRadiusWithCircle(m_nScrnPosX, m_nScrnPosY, 4, 100, 100, 100);
		else if ( m_bLightSize == 8 )
			g_xGameProc.m_xLightFog.SetLightRadiusWithCircle(m_nScrnPosX, m_nScrnPosY, 8, 255, 255, 255);
		else
			g_xGameProc.m_xLightFog.SetLightRadiusWithCircle(m_nScrnPosX, m_nScrnPosY, 10, 255, 255, 255);
	}
}



/******************************************************************************************************************

	함수명 : CActor::DrawActor()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : BOOL bFocused
	         BOOL bShadowAblended
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CActor::DrawActor(CMapHandler* pxMap, BOOL bFocused, BOOL bShadowAblended, BOOL bUseScrnPos, BOOL bDrawShadow)
{
	// 좌표처리.
	if ( bUseScrnPos )
	{
		m_nScrnPosX = (m_nPosX - pxMap->m_nStartViewTileX) * _CELL_WIDTH + pxMap->m_nViewPosX - pxMap->m_nViewOffsetX + m_nShiftPixelX;
		m_nScrnPosY = (m_nPosY - pxMap->m_nStartViewTileY) * _CELL_HEIGHT+ pxMap->m_nViewPosY - pxMap->m_nViewOffsetY + m_nShiftPixelY;
	}

	BYTE	bShadowType;
	SHORT	shShadowPX;
	SHORT	shShadowPY;

	if ( m_bCurrMtn != 0 )
	{
		int nt = 0;
	}

	if ( m_pxActorImage )
	{
		SHORT shPX, shPY;
		DWORD dwCurrFrm;

		if ( !m_bReverse )
		{
			if ( m_bBackStepFrameCnt )
				dwCurrFrm = m_dwEndFrame - (m_dwCurrFrame - m_dwFstFrame) -1;
			else
				dwCurrFrm = m_dwCurrFrame;
		}
		else
		{
			if ( m_bBackStepFrameCnt )
				dwCurrFrm = m_dwCurrFrame;
			else
				dwCurrFrm = m_dwEndFrame - (m_dwCurrFrame - m_dwFstFrame) -1;
		}

		if ( m_pxActorImage->NewSetIndex(dwCurrFrm) )
		{
			shPX = m_pxActorImage->m_lpstNewCurrWilImageInfo->shPX;
			shPY = m_pxActorImage->m_lpstNewCurrWilImageInfo->shPY;

			bShadowType = m_pxActorImage->m_lpstNewCurrWilImageInfo->bShadow;
			shShadowPX  = m_pxActorImage->m_lpstNewCurrWilImageInfo->shShadowPX;
			shShadowPY  = m_pxActorImage->m_lpstNewCurrWilImageInfo->shShadowPY;

			SetRect(&m_rcActor, m_nScrnPosX + shPX, m_nScrnPosY + shPY, 
					m_nScrnPosX + shPX + m_pxActorImage->m_lpstNewCurrWilImageInfo->shWidth, 
					m_nScrnPosY + shPY + m_pxActorImage->m_lpstNewCurrWilImageInfo->shHeight);

			if ( ( m_rcActor.right - m_rcActor.left ) > _CELL_WIDTH + _TARGETRGN_GAPX )
			{
				m_rcTargetRgn.left  = m_rcActor.left + ( (m_rcActor.right - m_rcActor.left) - (_CELL_WIDTH + _TARGETRGN_GAPX) )/2;
				m_rcTargetRgn.right = m_rcActor.left + ( (m_rcActor.right - m_rcActor.left) + (_CELL_WIDTH + _TARGETRGN_GAPX) )/2;
			}
			else
			{
				m_rcTargetRgn.left  = m_rcActor.left;
				m_rcTargetRgn.right = m_rcActor.right;
			}

			if ( ( m_rcActor.bottom - m_rcActor.top ) > _CELL_HEIGHT + _TARGETRGN_GAPY )
			{
				m_rcTargetRgn.top    = m_rcActor.top + ( (m_rcActor.bottom - m_rcActor.top) - (_CELL_HEIGHT + _TARGETRGN_GAPY) )/2;
				m_rcTargetRgn.bottom = m_rcActor.top + ( (m_rcActor.bottom - m_rcActor.top) + (_CELL_HEIGHT + _TARGETRGN_GAPY) )/2;
			}
			else
			{
				m_rcTargetRgn.top    = m_rcActor.top;
				m_rcTargetRgn.bottom = m_rcActor.bottom;
			}

			INT nStartX1 = m_nScrnPosX + shShadowPX;
			INT nStartY1 = m_nScrnPosY + shShadowPY;

			BYTE bOpaRate = 13;
			WORD wState   = GetCharState();
			WORD wDress	  = MAKEWORD(m_stFeature.bDress, m_stFeature.bHair);

			// 몬스터 그림자 파일 적용.
			if ( bDrawShadow  && 
				wDress != 530 && wDress != 531 && wDress != 532 && wDress != 533 && wDress != 538 )
			{
				CWHWilImageData* pxSahdowImage;

				if ( m_stFeature.bGender == _GENDER_MON )
				{
					if ( wDress < 200 )
					{
						pxSahdowImage = &g_xGameProc.m_xImage.m_xImageList[m_bActorImgIdx+_MAX_MONSTER_IMAGE];
					}
					else
					{
						pxSahdowImage = &g_xGameProc.m_xImage.m_xImageList[m_bActorImgIdx+1];
					}
				}
				else
				{
					pxSahdowImage = &g_xGameProc.m_xImage.m_xImageList[m_bActorImgIdx+_MAX_MONSTER_IMAGE];
				}

				if ( pxSahdowImage->NewSetIndex(dwCurrFrm) )
				{
					SHORT shShadowPX, shShadowPY;
					if ( ( m_nABlendDelay || wState==_STATE_ABLEND || bShadowAblended ) && wDress != 127 ) // 밤나무 예외 처리
					{
						shShadowPX = pxSahdowImage->m_lpstNewCurrWilImageInfo->shPX;
						shShadowPY = pxSahdowImage->m_lpstNewCurrWilImageInfo->shPY;

						g_xMainWnd.DrawWithABlendCompDataWithBackBufferEx(m_nScrnPosX+shShadowPX, m_nScrnPosY+shShadowPY, pxSahdowImage->m_lpstNewCurrWilImageInfo->shWidth,	pxSahdowImage->m_lpstNewCurrWilImageInfo->shHeight, (WORD*)pxSahdowImage->m_pbCurrImage,
																		  _CLIP_WIDTH, _CLIP_HEIGHT, 0XFFFF, 0XFFFF, bOpaRate);
					}
					else
					{
						shShadowPX = pxSahdowImage->m_lpstNewCurrWilImageInfo->shPX;
						shShadowPY = pxSahdowImage->m_lpstNewCurrWilImageInfo->shPY;
						
						g_xMainWnd.DrawWithImageForCompClipRgn(m_nScrnPosX+shShadowPX, m_nScrnPosY+shShadowPY, pxSahdowImage->m_lpstNewCurrWilImageInfo->shWidth,	pxSahdowImage->m_lpstNewCurrWilImageInfo->shHeight, (WORD*)pxSahdowImage->m_pbCurrImage,
															   _CLIP_WIDTH, _CLIP_HEIGHT, 0XFFFF, 0XFFFF, bFocused);
					}
				}
				// 계산해서 그리기.
				else
				{
					// 그림자를 그린다.
					if ( m_nABlendDelay || wState==_STATE_ABLEND || bShadowAblended )
					{
						if ( bOpaRate < 0 || bOpaRate > 31 )
						{
							bOpaRate  = 0;
						}
						bShadowAblended = TRUE;
					}

					// 밤나무 예외적용.
					if ( !m_bIsDead || wDress == 127 || wDress == 153 /*트리*/)
					{
						// 그림자 그리기 정리 by eriastoa 2006.05.03
						//DrawShadow( nStartX1, nStartY1, bShadowAblended, bShadowType, bOpaRate );
						g_xMainWnd.DrawWithShadowABlend(
												nStartX1, nStartY1, 
												m_pxActorImage->m_lpstNewCurrWilImageInfo->shWidth,							
												m_pxActorImage->m_lpstNewCurrWilImageInfo->shHeight,
												(WORD*)m_pxActorImage->m_pbCurrImage,
												_CLIP_WIDTH, _CLIP_HEIGHT, g_xGameProc.m_wShadowClr, bShadowAblended, bShadowType, bOpaRate);
					}
					else
					{

						
						g_xMainWnd.DrawWithShadowABlend(
												m_rcActor.left+3, m_rcActor.top+2, 
												m_pxActorImage->m_lpstNewCurrWilImageInfo->shWidth,							
												m_pxActorImage->m_lpstNewCurrWilImageInfo->shHeight,
												(WORD*)m_pxActorImage->m_pbCurrImage,
												_CLIP_WIDTH, _CLIP_HEIGHT, g_xGameProc.m_wShadowClr, bShadowAblended, 50, bOpaRate);

					}
				}
			}

			if ( m_nABlendDelay > 0 )
			{
				if ( m_bABlendRev )
				{
					bOpaRate = (BYTE)(31 - ( (m_nABlendCurrDelay * 31) / m_nABlendDelay ));
				}
				else
				{
					bOpaRate = (BYTE)(( (m_nABlendCurrDelay * 31) / m_nABlendDelay ));
				}
			}

			if ( bFocused )								
			{
				if ( m_bABlendRev )
				{
					bOpaRate -= 5;
				}
				else
				{
					bOpaRate += 5;
				}
			}

			if ( bOpaRate < 0 || bOpaRate > 31 )		bOpaRate  = 0;


			DrawWithEffected(m_rcActor.left, m_rcActor.top, m_pxActorImage->m_lpstNewCurrWilImageInfo->shWidth, m_pxActorImage->m_lpstNewCurrWilImageInfo->shHeight, (WORD*)m_pxActorImage->m_pbCurrImage, 
					 m_wMonColor, 0XFFFF, bFocused, bOpaRate, wState);
			
			if ( m_bIsSturn )
			{
				DWORD dwCur = timeGetTime();
				if ( dwCur - m_dwSturnTimer > 150 )
				{
					m_dwSturnTimer = dwCur;
					m_nStrurnFrame++;

					if ( m_nStrurnFrame > 685 )
						m_nStrurnFrame = 680;
				}

				INT nX = m_nScrnPosX+7;
				INT	nY = m_nScrnPosY-80;

				if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].NewSetIndex(m_nStrurnFrame) )
				{
 					g_xMainWnd.DrawWithImageForComp(
									nX,
									nY,
									g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shWidth,
									g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shHeight,
									(WORD*)g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_pbCurrImage);
				}
			}

			return TRUE;
		}
		else
		{
			int ntest = 0;
		}
	}
	return FALSE;
}

VOID CActor::DrawHPNum()
{
	if ( g_xGameProc.m_bShowBloodNum )
	{
		for ( INT nI=0; nI<m_nShowBloodIdx; nI++ )
		{
			if ( m_dwShowBloodTimer[nI] > 40 )
				continue;
			m_ptShowBlood[nI].x = (m_nScrnPosX + 20) + m_dwShowBloodTimer[nI];
			m_ptShowBlood[nI].y = (m_nScrnPosY - 30) - m_dwShowBloodTimer[nI]*1.3;

			g_xGameProc.ShowGraphicNum(m_ptShowBlood[nI], m_nShowBlood[nI]);
			m_dwShowBloodTimer[nI]++;
		}
	}
}


/******************************************************************************************************************

	함수명 : CActor::DrawHPBar()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CActor::DrawHPBar(INT nX, INT nY)
{
	g_xGameProc.m_bDrawHealthNum = FALSE;

	if ( ( m_bOpenHealth || g_xGameProc.m_bDrawHealthNum || ( nX == 900 && nY == 700 ) ) && !m_bIsDead )
	{
		FLOAT	fHPPercent	= (FLOAT)((FLOAT)m_bHPPercent/100);
		RECT	rcHP		= {0, 0, (LONG)(46*fHPPercent), 2};

		if ( nX == 900 && nY == 700 )
		{
			nX= -1;
			nY = -1;
		}

 		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(3) )
		{
			if ( nX == -1 && nY == -1 )
			{
				nX = m_nScrnPosX;
				nY = m_nScrnPosY-56;
			}

 			g_xMainWnd.DrawWithImageForComp(
							nX,
							nY,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
							(WORD*)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
		}
		
		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(4) )
		{
 			g_xMainWnd.DrawWithImageForComp(
							nX+1,
							nY+1,
							&rcHP,
							(WORD*)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
		}
	}
}



/******************************************************************************************************************

	함수명 : CActor::DrawName()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CActor::DrawName()
{
	SIZE sizeLen;
	RECT rc, rcBack;

	if ( m_szName[0] != NULL )
	{
		sizeLen = g_xMainWnd.GetStrLength(NULL, NULL, m_szName);

		WORD wDress = MAKEWORD(m_stFeature.bDress, m_stFeature.bHair);
		
		if ( ( wDress == 530 || wDress == 531 || wDress == 532 || wDress == 533 || wDress == 538 ) && m_bCurrDir == 7 )
			SetRect(&rc , m_nScrnPosX+(_CELL_WIDTH-sizeLen.cx)/2, m_nScrnPosY-90, m_nScrnPosX+(_CELL_WIDTH+sizeLen.cx)/2, m_nScrnPosY-75);
		else	
			SetRect(&rc , m_nScrnPosX+(_CELL_WIDTH-sizeLen.cx)/2, m_nScrnPosY-30, m_nScrnPosX+(_CELL_WIDTH+sizeLen.cx)/2, m_nScrnPosY-15);

		if ( strlen(m_szShowName[0]) != 0 )
		{
			sizeLen = g_xMainWnd.GetStrLength(NULL, NULL, m_szShowName[0]);
			SetRect(&rcBack, rc.left-1, rc.top-1, rc.right-1, rc.bottom-1);
			g_xMainWnd.PutsHan(NULL, rcBack, RGB(10, 10, 10), RGB(0, 0, 0), m_szShowName[0]);

			SetRect(&rcBack, rc.left+1, rc.top-1, rc.right+1, rc.bottom-1);
			g_xMainWnd.PutsHan(NULL, rcBack, RGB(10, 10, 10), RGB(0, 0, 0), m_szShowName[0]);

			SetRect(&rcBack, rc.left-1, rc.top+1, rc.right-1, rc.bottom+1);
			g_xMainWnd.PutsHan(NULL, rcBack, RGB(10, 10, 10), RGB(0, 0, 0), m_szShowName[0]);

			SetRect(&rcBack, rc.left+1, rc.top+1, rc.right+1, rc.bottom+1);
			g_xMainWnd.PutsHan(NULL, rcBack, RGB(10, 10, 10), RGB(0, 0, 0), m_szShowName[0]);

			g_xMainWnd.PutsHan(NULL, rc, m_dwNameClr, RGB(0, 0, 0), m_szShowName[0]);

			if ( strlen(m_szShowName[1]) != 0 )
			{
				sizeLen = g_xMainWnd.GetStrLength(NULL, NULL, m_szShowName[1]);
				SetRect(&rc , m_nScrnPosX+(_CELL_WIDTH-sizeLen.cx)/2, m_nScrnPosY-15, m_nScrnPosX+(_CELL_WIDTH+sizeLen.cx)/2, m_nScrnPosY);

				SetRect(&rcBack, rc.left-1, rc.top-1, rc.right-1, rc.bottom-1);
				g_xMainWnd.PutsHan(NULL, rcBack, RGB(10, 10, 10), RGB(0, 0, 0), m_szShowName[1]);

				SetRect(&rcBack, rc.left+1, rc.top-1, rc.right+1, rc.bottom-1);
				g_xMainWnd.PutsHan(NULL, rcBack, RGB(10, 10, 10), RGB(0, 0, 0), m_szShowName[1]);

				SetRect(&rcBack, rc.left-1, rc.top+1, rc.right-1, rc.bottom+1);
				g_xMainWnd.PutsHan(NULL, rcBack, RGB(10, 10, 10), RGB(0, 0, 0), m_szShowName[1]);

				SetRect(&rcBack, rc.left+1, rc.top+1, rc.right+1, rc.bottom+1);
				g_xMainWnd.PutsHan(NULL, rcBack, RGB(10, 10, 10), RGB(0, 0, 0), m_szShowName[1]);

				g_xMainWnd.PutsHan(NULL, rc, m_dwNameClr, RGB(0, 0, 0), m_szShowName[1]);
			}

			if ( strlen(m_szShowName[2]) != 0 )
			{
				sizeLen = g_xMainWnd.GetStrLength(NULL, NULL, m_szShowName[2]);
				SetRect(&rc , m_nScrnPosX+(_CELL_WIDTH-sizeLen.cx)/2, m_nScrnPosY, m_nScrnPosX+(_CELL_WIDTH+sizeLen.cx)/2, m_nScrnPosY+15);

				SetRect(&rcBack, rc.left-1, rc.top-1, rc.right-1, rc.bottom-1);
				g_xMainWnd.PutsHan(NULL, rcBack, RGB(10, 10, 10), RGB(0, 0, 0), m_szShowName[2]);

				SetRect(&rcBack, rc.left+1, rc.top-1, rc.right+1, rc.bottom-1);
				g_xMainWnd.PutsHan(NULL, rcBack, RGB(10, 10, 10), RGB(0, 0, 0), m_szShowName[2]);

				SetRect(&rcBack, rc.left-1, rc.top+1, rc.right-1, rc.bottom+1);
				g_xMainWnd.PutsHan(NULL, rcBack, RGB(10, 10, 10), RGB(0, 0, 0), m_szShowName[2]);

				SetRect(&rcBack, rc.left+1, rc.top+1, rc.right+1, rc.bottom+1);
				g_xMainWnd.PutsHan(NULL, rcBack, RGB(10, 10, 10), RGB(0, 0, 0), m_szShowName[2]);

				g_xMainWnd.PutsHan(NULL, rc, m_dwNameClr, RGB(0, 0, 0), m_szShowName[2]);
			}
		}
		else
		{
			SetRect(&rcBack, rc.left-1, rc.top-1, rc.right-1, rc.bottom-1);
			g_xMainWnd.PutsHan(NULL, rcBack, RGB(10, 10, 10), RGB(0, 0, 0), m_szName);

			SetRect(&rcBack, rc.left+1, rc.top-1, rc.right+1, rc.bottom-1);
			g_xMainWnd.PutsHan(NULL, rcBack, RGB(10, 10, 10), RGB(0, 0, 0), m_szName);

			SetRect(&rcBack, rc.left-1, rc.top+1, rc.right-1, rc.bottom+1);
			g_xMainWnd.PutsHan(NULL, rcBack, RGB(10, 10, 10), RGB(0, 0, 0), m_szName);

			SetRect(&rcBack, rc.left+1, rc.top+1, rc.right+1, rc.bottom+1);
			g_xMainWnd.PutsHan(NULL, rcBack, RGB(10, 10, 10), RGB(0, 0, 0), m_szName);

			g_xMainWnd.PutsHan(NULL, rc, m_dwNameClr, RGB(0, 0, 0), m_szName);
		}
	}
}



VOID CActor::ChatMsgAdd()
{
	CHAR szDivied[MAX_PATH*2];
	ZeroMemory(szDivied, MAX_PATH*2);

	g_xMainWnd.StringDivide(_CHAT_WIDTH, m_nDividedChatLine, m_szChatMsg, szDivied);
	sscanf(szDivied, "%[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c", 
		   m_szChatMsgArg[0], m_szChatMsgArg[1], m_szChatMsgArg[2], m_szChatMsgArg[3], m_szChatMsgArg[4], m_szChatMsgArg[5], m_szChatMsgArg[6], m_szChatMsgArg[7]);

	m_wCurrChatDelay = 0;
}


VOID CActor::ShowMessage(INT nLoopTime)
{
	if ( m_szChatMsg[0] != NULL )
	{
		m_wCurrChatDelay += nLoopTime;
	}

	if ( m_wCurrChatDelay > 3000 )
	{
		m_wCurrChatDelay = 0;
		ZeroMemory(m_szChatMsg, MAX_PATH);
		ZeroMemory(m_szChatMsgArg, MAX_PATH*8);
	}

	if ( m_szChatMsg[0] != NULL )
	{
		INT nStartX = m_nScrnPosX + 28 - _CHAT_WIDTH/2;
		INT nStartY = m_nScrnPosY - 55;

		RECT rcBack;

		if ( m_nDividedChatLine == 1 )
		{
			SIZE sizeLen;
			sizeLen = g_xMainWnd.GetStrLength(NULL, NULL, m_szChatMsgArg[0]);
			nStartX = m_nScrnPosX + 28 - sizeLen.cx/2;
			SetRect(&rcBack, nStartX, nStartY-14-4, nStartX+sizeLen.cx, nStartY);
		}
		else
		{
			SetRect(&rcBack, nStartX, nStartY-m_nDividedChatLine*14-4, nStartX+_CHAT_WIDTH, nStartY);
		}

		if ( g_xMainWnd.Get3DDevice() )
		{
			D3DVECTOR vTrans;
			D3DMATRIX matTrans;
			D3DMATRIX matScale;
			D3DMATRIX matWorld;
			D3DMATRIX matWorldOriginal;
			D3DMATERIAL7 mtrl;

			D3DUtil_InitMaterial(mtrl, (FLOAT)80/255.0f,(FLOAT)60/255.0f, (FLOAT)40/255.0f);
			mtrl.diffuse.a = 120/255.0f;
			g_xMainWnd.Get3DDevice()->SetMaterial(&mtrl);

			vTrans.x = (FLOAT)nStartX-400+(rcBack.right-rcBack.left)/2;  
			vTrans.y = (FLOAT)-nStartY+300+(rcBack.bottom-rcBack.top)/2; 
			vTrans.z = 0;

			FLOAT fXScale = (FLOAT)(rcBack.right-rcBack.left);
			FLOAT fYScale = (FLOAT)(rcBack.bottom-rcBack.top);

			if( SUCCEEDED(g_xMainWnd.Get3DDevice()->BeginScene()) )
			{
				g_xMainWnd.Get3DDevice()->GetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

				D3DUtil_SetTranslateMatrix(matTrans, vTrans);
				D3DUtil_SetScaleMatrix(matScale, fXScale, fYScale, 0.0f);
				D3DMath_MatrixMultiply(matWorld, matScale, matTrans);
				g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);				

				g_xMainWnd.Get3DDevice()->SetRenderState( D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
				g_xMainWnd.Get3DDevice()->SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, TRUE);
				g_xMainWnd.Get3DDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
				g_xMainWnd.Get3DDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE);
				g_xMainWnd.Get3DDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
				g_xMainWnd.Get3DDevice()->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
				g_xMainWnd.Get3DDevice()->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
				g_xMainWnd.Get3DDevice()->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
				g_xMainWnd.Get3DDevice()->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);

				g_xMainWnd.Get3DDevice()->SetTexture(0, NULL);

				g_xMainWnd.Get3DDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_VERTEX, m_avBoard, 4, NULL);

				g_xMainWnd.Get3DDevice()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
				g_xMainWnd.Get3DDevice()->SetTextureStageState(0, D3DTSS_COLOROP,   D3DTOP_MODULATE);
				g_xMainWnd.Get3DDevice()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
				g_xMainWnd.Get3DDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
				g_xMainWnd.Get3DDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1);
				g_xMainWnd.Get3DDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
				g_xMainWnd.Get3DDevice()->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
				g_xMainWnd.Get3DDevice()->SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, FALSE);
				g_xMainWnd.Get3DDevice()->SetRenderState(D3DRENDERSTATE_SRCBLEND , D3DBLEND_ONE);
				g_xMainWnd.Get3DDevice()->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO);
				g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

				g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);				

				g_xMainWnd.Get3DDevice()->EndScene();
			}
		}

		for ( INT nCnt = 0; nCnt < m_nDividedChatLine; nCnt++ )
		{
			SIZE sizeLen;
			sizeLen = g_xMainWnd.GetStrLength(NULL, NULL, m_szChatMsgArg[nCnt]);

			if ( m_nDividedChatLine != 1 )
			{
				if ( nCnt == m_nDividedChatLine-1 )
				{
					nStartX += (_CHAT_WIDTH-sizeLen.cx)/2;
				}
			}

			DWORD dwColor;

			if ( strncmp(m_szChatMsgArg[0], "(!)", 3) == 0 )
				dwColor = RGB(200, 200, 0);
			else
				dwColor = RGB(255, 255, 255);

			g_xMainWnd.PutsHan(NULL, nStartX+1, nStartY-(m_nDividedChatLine-nCnt)*14+1, RGB(10, 10, 10), RGB(0, 0, 0), m_szChatMsgArg[nCnt]);

			g_xMainWnd.PutsHan(NULL, nStartX, nStartY-(m_nDividedChatLine-nCnt)*14, dwColor, RGB(0,0,0), m_szChatMsgArg[nCnt]);

		}
	}
}












/******************************************************************************************************************

	CNPC Class

*******************************************************************************************************************/
/******************************************************************************************************************

	함수명 : CNPC::DrawActor()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : CMapHandler* pxMap
	         BOOL bFocused
	         BOOL bShadowAblended
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CNPC::DrawActor(CMapHandler* pxMap, BOOL bFocused, BOOL bShadowAblended, BOOL bUseScrnPos, BOOL bDrawShadow)
{
	// 좌표처리.
	m_nScrnPosX = (m_nPosX - pxMap->m_nStartViewTileX) * _CELL_WIDTH + pxMap->m_nViewPosX - pxMap->m_nViewOffsetX + m_nShiftPixelX;
	m_nScrnPosY = (m_nPosY - pxMap->m_nStartViewTileY) * _CELL_HEIGHT+ pxMap->m_nViewPosY - pxMap->m_nViewOffsetY + m_nShiftPixelY;

	BYTE	bShadowType;
	SHORT	shShadowPX;
	SHORT	shShadowPY;

	if ( m_pxActorImage )
	{
		SHORT shPX, shPY;
		if ( m_pxActorImage->NewSetIndex(m_dwCurrFrame) )
		{
			shPX = m_pxActorImage->m_lpstNewCurrWilImageInfo->shPX;
			shPY = m_pxActorImage->m_lpstNewCurrWilImageInfo->shPY;

			bShadowType = m_pxActorImage->m_lpstNewCurrWilImageInfo->bShadow;
			shShadowPX  = m_pxActorImage->m_lpstNewCurrWilImageInfo->shShadowPX;
			shShadowPY  = m_pxActorImage->m_lpstNewCurrWilImageInfo->shShadowPY;

			SetRect(&m_rcActor, m_nScrnPosX + shPX, m_nScrnPosY + shPY, 
					m_nScrnPosX + shPX + m_pxActorImage->m_lpstNewCurrWilImageInfo->shWidth, 
					m_nScrnPosY + shPY + m_pxActorImage->m_lpstNewCurrWilImageInfo->shHeight);

			if ( ( m_rcActor.right - m_rcActor.left ) > _CELL_WIDTH + _TARGETRGN_GAPX )
			{
				m_rcTargetRgn.left  = m_rcActor.left + ( (m_rcActor.right - m_rcActor.left) - (_CELL_WIDTH + _TARGETRGN_GAPX) )/2;
				m_rcTargetRgn.right = m_rcActor.left + ( (m_rcActor.right - m_rcActor.left) + (_CELL_WIDTH + _TARGETRGN_GAPX) )/2;
			}
			else
			{
				m_rcTargetRgn.left  = m_rcActor.left;
				m_rcTargetRgn.right = m_rcActor.right;
			}

			if ( ( m_rcActor.bottom - m_rcActor.top ) > _CELL_HEIGHT + _TARGETRGN_GAPY )
			{
				m_rcTargetRgn.top    = m_rcActor.top + ( (m_rcActor.bottom - m_rcActor.top) - (_CELL_HEIGHT + _TARGETRGN_GAPY) )/2;
				m_rcTargetRgn.bottom = m_rcActor.top + ( (m_rcActor.bottom - m_rcActor.top) + (_CELL_HEIGHT + _TARGETRGN_GAPY) )/2;
			}
			else
			{
				m_rcTargetRgn.top    = m_rcActor.top;
				m_rcTargetRgn.bottom = m_rcActor.bottom;
			}

			// 캐릭터 그림자.
			INT nStartX1 = m_nScrnPosX + shShadowPX;
			INT nStartY1 = m_nScrnPosY + shShadowPY;

			BYTE bOpaRate = 13;
			WORD wState   = GetCharState();

			// 그림자를 그린다.
			if ( m_nABlendDelay || wState==_STATE_ABLEND )
			{
				bShadowAblended = TRUE;
			}
	
			if ( bDrawShadow )
				g_xMainWnd.DrawWithShadowABlend(
										nStartX1, nStartY1,
										m_pxActorImage->m_lpstNewCurrWilImageInfo->shWidth,							
										m_pxActorImage->m_lpstNewCurrWilImageInfo->shHeight,
										(WORD*)m_pxActorImage->m_pbCurrImage,
										_CLIP_WIDTH, _CLIP_HEIGHT, g_xGameProc.m_wShadowClr, bShadowAblended, bShadowType, bOpaRate);

			if ( m_nABlendDelay > 0 )
			{
				if ( m_bABlendRev )
					bOpaRate = (BYTE)(31 - ( (m_nABlendCurrDelay * 31) / m_nABlendDelay ));
				else
					bOpaRate = (BYTE)( (m_nABlendCurrDelay * 31) / m_nABlendDelay );
			}

			if ( bFocused )								
			{
				if ( m_bABlendRev )
					bOpaRate -= 5;
				else
					bOpaRate += 5;
			}

			if ( bOpaRate < 0 || bOpaRate > 31 )
				bOpaRate  = 0;

			/////////////// 깃발 칼라 값 얻어서 적용시키는 부분//////////////////////////////////
			WORD wClr = 0XFFFF;

			if ( m_stFeature.bGender == _GENDER_FLAG )
			{
				BYTE bRed, bGreen, bBlue;

				bRed = ( ( m_stFeature.bDress & 0x0F )  );
				bRed *= 16;
				bGreen = ( ( m_stFeature.bHair & 0xF0 ) >> 4 );
				bGreen *= 16;
				bBlue = ( ( m_stFeature.bHair & 0x0F )  );
				bBlue *= 16;

				m_nABlendDelay = 0;
				wClr = g_xMainWnd.ConvertColor24To16(RGB(bRed, bGreen, bBlue));
			}
			DrawWithEffected(m_rcActor.left, m_rcActor.top, m_pxActorImage->m_lpstNewCurrWilImageInfo->shWidth, m_pxActorImage->m_lpstNewCurrWilImageInfo->shHeight, (WORD*)m_pxActorImage->m_pbCurrImage, 
							 wClr, 0XFFFF, bFocused, bOpaRate, wState);
			

			return TRUE;
		}
	}
	return FALSE;
}


VOID CNPC::OnTurn(LPPACKETMSG lpPacketMsg)
{
/*	BYTE bDir;
	m_nPosX = lpPacketMsg->stDefMsg.wParam;
	m_nPosY = lpPacketMsg->stDefMsg.wTag;
	bDir		 = LOBYTE(lpPacketMsg->stDefMsg.wSeries);
	m_bLightSize = HIBYTE(lpPacketMsg->stDefMsg.wSeries);
	OnCharDescPacket(lpPacketMsg);
	SetMotionFrame(_MT_NPC_STAND, bDir);
*/
	BYTE		bDir;
	CHARDESC	stCharDesc;
	FEATURE		stFeature;
	INT			nPos;
	m_nPosX = lpPacketMsg->stDefMsg.wParam;
	m_nPosY = lpPacketMsg->stDefMsg.wTag;
	bDir		 = LOBYTE(lpPacketMsg->stDefMsg.wSeries);
	m_bLightSize = HIBYTE(lpPacketMsg->stDefMsg.wSeries);

	fnDecode6BitBuf(lpPacketMsg->szEncodeData, (char*)&stCharDesc, sizeof(CHARDESC));

	if ( lpPacketMsg->stDefMsg.wIdent == SM_REVIVAL )
	{
		m_bIsDead = FALSE;
		m_nABlendDelay = 600;
		m_nABlendCurrDelay = 0;
	}

	if ( strlen(lpPacketMsg->szEncodeData) > _CHARDESCSIZE )
	{
/*		CHAR pszDecodeMsg[1024];
		CHAR *pszStr1;
		CHAR *pszStr2;

		nPos = fnDecode6BitBuf(&lpPacketMsg->szEncodeData[_CHARDESCSIZE], pszDecodeMsg, sizeof(pszDecodeMsg));
		pszDecodeMsg[nPos] = '\0';

		if ( pszStr1 = strchr(pszDecodeMsg, '\\') )
		{
			*pszStr1++ = '\0';								// pszDecodeMsg == m_szName;

			strcpy(m_szName, pszDecodeMsg);

			if ( pszStr2 = strrchr(pszStr1, '/') )
			{
				*pszStr2++ = '\0';							// pszStr1 == m_GuildName;

				strcpy(m_szGuildName, pszStr1);

				if ( pszStr2[0] != NULL )
				{
					m_dwNameClr = GetUserNameColor(atoi(pszStr2));
				}
			}
		}
		else
		{
			if ( pszStr2 = strrchr(pszDecodeMsg, '/') )
			{
				*pszStr2++ = '\0';							// pszStr2 == m_szName;
				strcpy(m_szName, pszDecodeMsg);

				if ( pszStr2[0] != NULL )
				{
					m_dwNameClr = GetUserNameColor(atoi(pszStr2));
				}
			}
		}
*/
		CHAR szName[64];
		nPos = fnDecode6BitBuf(&lpPacketMsg->szEncodeData[_CHARDESCSIZE], szName, sizeof(szName));
		szName[nPos] = '\0';

		CheckMultiLineName(szName);

		CHAR* szClr = strrchr(szName, '/');

		if ( szClr )
		{
			m_dwNameClr = GetUserNameColor((BYTE)atoi(szClr+1));
			*szClr = '\0';
		}
	}

	memcpy(&stFeature, &stCharDesc.nFeature, sizeof(FEATURE));
	m_nCharState = stCharDesc.nStatus;

	if( m_nCharState & 0X2 )	m_bOpenHealth = TRUE;
	else					m_bOpenHealth = FALSE;

	ChangeFeature(stFeature);

	SetMotionFrame(_MT_NPC_ACT01, bDir);
}


VOID CNPC::OnHit(LPPACKETMSG lpPacketMsg)
{
	BYTE bDir;
	bDir	= (BYTE)lpPacketMsg->stDefMsg.wSeries;
	m_nPosX = lpPacketMsg->stDefMsg.wParam;
	m_nPosY = lpPacketMsg->stDefMsg.wTag;

	if ( m_stFeature.bDress == 28 )
	{
		SetMotionFrame(GetRandomNum(_MT_NPC_ACT01, _MT_NPC_ACT02), bDir);
	}
	else
	{
		SetMotionFrame(_MT_NPC_ACT01, bDir);
	}
}


/******************************************************************************************************************

	함수명 : CNPC::UpdatePacketState()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CNPC::UpdatePacketState()
{
	LPPACKETMSG	lpPacketMsg = NULL;
	INT			nLeftMsgCnt = m_xPacketQueue.GetCount();

	if ( nLeftMsgCnt > 0 )
	{
		if ( nLeftMsgCnt >= 3 )				m_bMsgHurryCheck = TRUE;
		else								m_bMsgHurryCheck = FALSE;

		lpPacketMsg = (LPPACKETMSG)m_xPacketQueue.PopQ();
		
		if ( lpPacketMsg )
		{
			switch ( lpPacketMsg->stDefMsg.wIdent )
			{
				case SM_TURN:
				case SM_REVIVAL:
				{
					OnTurn(lpPacketMsg);				
					break;	
				}
				case SM_HIT:				
				{
					OnHit(lpPacketMsg);					
					break;	
				}
				default:
				{										
					break;	
				}
			}

			SAFE_DELETE(lpPacketMsg);

			return TRUE;
		}		
	}

	return FALSE;
}



/******************************************************************************************************************

	함수명 : CNPC::UpdateMotionState()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : INT nLoopTime
	         BOOL bIsMoveTime
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CNPC::UpdateMotionState(INT nLoopTime, BOOL bIsMoveTime)
{
	m_nCurrDelay += nLoopTime;
	m_nABlendCurrDelay += nLoopTime;

	if ( m_nABlendCurrDelay >= m_nABlendDelay )
	{
		m_nABlendCurrDelay = 0;
		m_nABlendDelay	   = 0;
		m_bABlendRev	   = FALSE;
	}

	if ( m_nCurrDelay > m_nDelay )
	{
		m_nCurrDelay = 0;

		if ( m_dwCurrFrame < m_dwEndFrame )
			m_dwCurrFrame++;
	}

	if ( m_dwCurrFrame >= m_dwEndFrame )		
	{
		m_dwCurrFrame = m_dwFstFrame;
		SetMotionFrame(_MT_NPC_STAND, m_bCurrDir);
	}

	UpdatePacketState();
}









/******************************************************************************************************************

	CHero Class

*******************************************************************************************************************/
/******************************************************************************************************************

	함수명 : CHero::CHero()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
CHero::CHero()
{
	InitActor();
}



/******************************************************************************************************************

	함수명 : CHero::~CHero()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
CHero::~CHero()
{
	DestroyActor();
}


VOID CHero::InitActor()
{
	CActor::InitActor();

	ZeroMemory(&m_stFeatureEx, sizeof(FEATUREEX));

	m_bWeaponImgIdx = 0;
	m_bHairImgIdx	= 0;	
	m_bHorseImgIdx	= 0;	
	m_bYedoCnt		= 0;
	m_bFireHitCnt	= 0;
	m_bRandSwingCnt = 0;
	m_bBackSwingCnt = 0;
	m_bHRandSwingCnt = 0;
	m_bHYedoCnt		= 0;

	m_shHitSpeed	= 0;

	m_pxHairImage	= NULL;
	m_pxWeaponImage	= NULL;
	m_pxHorseImage	= NULL;

	m_bUseBanwol	= FALSE;
	m_bUseManwol	= FALSE;
	m_bUseErgum		= FALSE;
	m_bRushKung		= FALSE;
	m_bUseHErgum	= FALSE;
	m_bUseHManwol	= FALSE;
	m_bMang			= FALSE;

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	m_bViewDigFragment = FALSE;
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	m_bShieldCurrFrm	= 0;
	m_dwShieldTick	    = 0;
	m_nShieldCurrDelay	= 0;
	m_dwCurrHairFrame	= 0;
	m_dwCurrWeaponFrame	= 0;
	m_dwCurrHorseFrame	= 0;
	m_nCurrMagicID		= -1;

	m_nFame				= 0;
	m_bPahwangbo		= FALSE;

	m_nGhostAmorEftIdx  = 0;
	m_dwGhostAmorTimer  = 0;

	m_dwAmorTimer		= 0;
	m_nAmorEftIdx		= 500;

	m_dwFAEftTimer		= 0;
	m_nFAEftIdx			= 0;

	m_bEftFeature		= 0;
#ifdef _TEST_SERVER
	m_nEft				= 0;		// 이펙트 변수 추가 by eriastoa 2006.05.29
#endif

	m_nAfterPosX		= 0;
	m_nAfterPosY		= 0;

	m_nTimerAfterImg	= 0;

	m_nSaveIdx			= 0;
	m_nPlayIdx1			= 0;
	m_nPlayIdx2			= 0;
	m_bSetIdx			= FALSE;

	m_dwAfterTimer		= 0;

	m_nThunderIdx		= 2210;
	m_dwThunderTimer	= 0;

	for ( INT nI=0; nI<10; nI++ )
		ZeroMemory(&m_xAfterImage[nI], sizeof(AFTERIMAGE));

	ZeroMemory(&m_rcHair, sizeof(RECT));
	ZeroMemory(&m_rcWeapon, sizeof(RECT));
	ZeroMemory(&m_rcHorse, sizeof(RECT));
}


VOID CHero::DestroyActor()
{
	CActor::DestroyActor();
	InitActor();
}




/******************************************************************************************************************

	함수명 : CHero::Create()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : CImageHandler* pxImgHandler
	         WORD wActor
	         BYTE bMtn
	         WORD bDir
	         WORD wPosX
	         WORD wPosY
	         FEATURE stFeature
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CHero::Create(CImageHandler* pxImgHandler, BYTE bMtn, BYTE bDir, INT nPosX, INT nPosY, 
				   FEATURE* pstFeature, FEATUREEX* pstFeatureEx)
{
#ifdef _TEST_SERVER		// by eriastoa 2006.05.29
	m_nEft = pstFeatureEx->nEft;
#endif
			
	m_bEftFeature = pstFeature->bDress;
	pstFeature->bDress = pstFeature->bDress & 15; //이운

	if ( CActor::Create(pxImgHandler, pstFeature, bMtn, bDir, nPosX, nPosY) )
	{
		memcpy(&m_stFeatureEx, pstFeatureEx, sizeof(FEATUREEX));

		if ( m_stFeature.bHair	  >= _MAX_HAIR )
			m_stFeature.bHair	= _HAIR_NONE;

		if ( m_stFeature.bWeapon  >= 100 )
		{
			m_stFeature.bWeapon	= m_stFeature.bWeapon;
		}
		else if ( m_stFeature.bWeapon  >= _MAX_WEAPON )
			m_stFeature.bWeapon	= _WEAPON_NONE;

		if ( m_stFeatureEx.bHorse > _MAX_HORSE )
			m_stFeatureEx.bHorse= _HORSE_NONE;
		else if ( m_stFeatureEx.bHorse == _MAX_HORSE )
			m_stFeatureEx.bHorse= 1;

		if ( m_stFeatureEx.bHorse != _HORSE_NONE )
			m_bHorseImgIdx	= _IMAGE_HORSE;

		if ( m_stFeature.bGender == _GENDER_MAN )
		{
			if ( m_stFeature.bHair != _HAIR_NONE )
			{
				if ( m_stFeature.bHair > 20 )
					m_bHairImgIdx	= (BYTE)(_IMAGE_M_HAIR+(m_stFeature.bHair-1)/10 + 11);
				else
					m_bHairImgIdx	= (BYTE)(_IMAGE_M_HAIR+(m_stFeature.bHair-1)/10);
			}
			if ( m_stFeature.bWeapon != _WEAPON_NONE )
			{
				if ( m_stFeature.bWeapon <= 40 )
					m_bWeaponImgIdx	= (BYTE)(_IMAGE_M_WEAPON1+(m_stFeature.bWeapon-1)/10);
				else if ( m_stFeature.bWeapon >= 100 )
					m_bWeaponImgIdx	= _IMAGE_M_WEAPON10;
				else
					m_bWeaponImgIdx	= _IMAGE_M_WEAPON5;
			}
		}
		else if ( m_stFeature.bGender == _GENDER_WOMAN )
		{
			if ( m_stFeature.bHair != _HAIR_NONE )
			{
				if ( m_stFeature.bHair > 20 )
					m_bHairImgIdx	= (BYTE)(_IMAGE_WM_HAIR+(m_stFeature.bHair-1)/10 + 10);
				else
					m_bHairImgIdx	= (BYTE)(_IMAGE_WM_HAIR+(m_stFeature.bHair-1)/10);
			}
			if ( m_stFeature.bWeapon != _WEAPON_NONE )
			{
				if ( m_stFeature.bWeapon <= 40 )
					m_bWeaponImgIdx	= (BYTE)(_IMAGE_WM_WEAPON1+(m_stFeature.bWeapon-1)/10);
				else if ( m_stFeature.bWeapon >= 100 )
					m_bWeaponImgIdx	= _IMAGE_WM_WEAPON10;
				else
					m_bWeaponImgIdx	= _IMAGE_WM_WEAPON5;
			}
		}
		else			return FALSE;

		if ( m_stFeature.bHair != _HAIR_NONE )
			m_pxHairImage	= &pxImgHandler->m_xImageList[m_bHairImgIdx];
		else
			m_pxHairImage	= NULL;

		if ( m_stFeature.bWeapon != _WEAPON_NONE )
			m_pxWeaponImage	= &pxImgHandler->m_xImageList[m_bWeaponImgIdx];
		else
			m_pxWeaponImage	= NULL;

		if ( m_stFeatureEx.bHorse != _HORSE_NONE )
			m_pxHorseImage	= &pxImgHandler->m_xImageList[m_bHorseImgIdx];
		else
			m_pxHorseImage	= NULL;
  
		return TRUE;
	}
	return FALSE;
}


VOID CHero::DrawHPNum()
{
	if ( g_xGameProc.m_bShowBloodNum )
	{
		for ( INT nI=0; nI<m_nShowBloodIdx; nI++ )
		{
			if ( m_dwShowBloodTimer[nI] > 40 )
				continue;
			m_ptShowBlood[nI].x = (m_nScrnPosX + 20) + m_dwShowBloodTimer[nI];
			m_ptShowBlood[nI].y = (m_nScrnPosY - 40) - m_dwShowBloodTimer[nI]*1.3;

			g_xGameProc.ShowGraphicNum(m_ptShowBlood[nI], m_nShowBlood[nI]);
			m_dwShowBloodTimer[nI]++;
		}
	}
}

/******************************************************************************************************************

	함수명 : CActor::DrawHPBar()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CHero::DrawHPBar(INT nX, INT nY)
{
	g_xGameProc.m_bDrawHealthNum = FALSE;

	if ( ( m_bOpenHealth || g_xGameProc.m_bDrawHealthNum ) && !m_bIsDead )
	{
		FLOAT	fHPPercent	= (FLOAT)((FLOAT)m_bHPPercent/100);
		RECT	rcHP		= {0, 0, (LONG)(46*fHPPercent), 2};

 		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(3) )
		{
			if ( nX == -1 && nY == -1 )
			{
				nX = m_nScrnPosX;
				if ( m_stFeatureEx.bHorse == _HORSE_NONE )
				{
					nY = m_nScrnPosY-56;
				}
				else
				{
					nY = m_nScrnPosY-80;
				}
			}

 			g_xMainWnd.DrawWithImageForComp(
							nX,
							nY,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
							(WORD*)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
		}
		
		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(1) )
		{
 			g_xMainWnd.DrawWithImageForComp(
							nX+1,
							nY+1,
							&rcHP,
							(WORD*)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
		}
	}
}


VOID CHero::PlayActSound()
{
	INT nWaveNum = -1;

	if ( m_dwCurrFrame == m_dwFstFrame+1 && m_bCurrMtn == _MT_HITTED )
	{
		switch ( m_stHitter.bWeapon )
		{
			case 21: // 단검, 천군지장.
			case 8: case 9: // 목검, 아리수목검.
			case 18:  case 22:  case 23:  case 26:  case 27:  case 28:  case 30:  case 32:  // 사모검. 청동검. 철검. 청음검. 벽사검. 천령. 곡성검. 적혈마검.
			case 1:   case 4:  case 11:  case 13:  case 14:  case 20:  case 25:  case 29:  case 31:	 case 33:   case 38:  case 40:  case 45:  case 46: // 유월도. 묵청대도. 육합도. 군도. 도룡보도. 사각도. 세첨도. 예도. 초혼도. 무명도. 나락. 도철. 혼천도. 혼천마도
				nWaveNum = 70;
				break;
			case 5:  case 10:  case 12: // 삼적대부. 청동도끼. 연자부.
			case 15:  // 파뇌진당.
				nWaveNum = 71;
				break;
			case 2:  case 3:  case 6:  case 7: case 16:  case 17: case 19:  case 24: // 삼지창. 천형목. 홍아창. 곡괭이. 청마창, 용아장. 제마봉. 천군지장.
				nWaveNum = 72;
				break;
			default:
				nWaveNum = 73;	// 맨손.
				break;
		}
		if ( m_stFeature.bDress == 3 || m_stFeature.bDress == 6 )		// 미갑주, 패갑주.
		{
			nWaveNum += 10;
		}
	}
	if ( m_dwCurrFrame == m_dwFstFrame+2 && m_bCurrMtn == _MT_HITTED )
	{
		if ( m_stFeature.bGender == _GENDER_MAN )	nWaveNum = 138;
		else										nWaveNum = 139;
	}
	if ( m_dwCurrFrame == m_dwFstFrame+1 && m_bCurrMtn == _MT_DIE )
	{
		if ( m_stFeature.bGender == _GENDER_MAN )	nWaveNum = 144;
		else										nWaveNum = 145;

	}
	if ( m_dwCurrFrame == m_dwFstFrame+1 && ((m_bCurrMtn >= _MT_ONEVSWING && m_bCurrMtn <= _MT_SPEARHSWING) || m_bCurrMtn == _MT_WHEELWIND || m_bCurrMtn == _MT_RANDSWING) )
	{
		if ( m_bFireHitCnt == 2 )
		{
			nWaveNum = 137;
			m_bFireHitCnt = 0;
		}
		else if ( m_bRandSwingCnt == 2 )
		{
			nWaveNum = 140;
			m_bRandSwingCnt = 0;
		}
		else if ( m_bHRandSwingCnt == 2 )
		{
			nWaveNum = 140;
			m_bHRandSwingCnt = 0;
		}
		else if ( m_bBackSwingCnt == 2 )
		{
			nWaveNum = 141;
			m_bBackSwingCnt = 0;
		}
		else if ( m_bYedoCnt == 2 || m_bHYedoCnt == 2 )
		{
			if ( m_stFeature.bGender == _GENDER_MAN )
			{
				g_SoundManager.SndmngrPlayWavSound(130, m_nPosX, m_nPosY);
			}
			else
			{
				g_SoundManager.SndmngrPlayWavSound(131, m_nPosX, m_nPosY);
			}
			m_bYedoCnt = 0;
			m_bHYedoCnt = 0;
		}
		else if ( m_bUseSwordEffect && m_bUseBanwol )
		{
			nWaveNum = 133;
		}
		else if ( m_bUseSwordEffect && m_bUseManwol )
		{
			nWaveNum = 133;
		}
		else if ( m_bUseSwordEffect && m_bUseHManwol )
		{
			nWaveNum = 133;
		}
		else if ( m_bUseSwordEffect && m_bUseErgum )
		{
			nWaveNum = 132;
		}
		else if ( m_bUseSwordEffect && m_bUseHErgum )
		{
			nWaveNum = 132;
		}
		else if ( m_bUseSwordEffect )
		{
			nWaveNum = -1;
		}
	}
	if ( m_dwCurrFrame == m_dwFstFrame+2 && m_bCurrMtn >= _MT_ONEVSWING && m_bCurrMtn <= _MT_SPEARHSWING )
	{
		switch ( m_stFeature.bWeapon )
		{
		case 21: // 단검
			nWaveNum = 50;
			break;
		case 8: case 9: // 목검, 아리수목검.
			nWaveNum = 51;
			break;
		case 18:  case 22:  case 23:  case 26:  case 27:  case 28:  case 30:  case 32:  // 사모검. 청동검. 철검. 청음검. 벽사검. 천령. 곡성검. 적혈마검.
			nWaveNum = 52;
			break;
		case 1:   case 4:  case 11:  case 13:  case 14:  case 20:  case 25:  case 29:  case 31:	 case 33:  case 38: case 40: case 45: case 46:// 유월도. 묵청대도. 육합도. 군도. 도룡보도. 사각도. 세첨도. 예도. 초혼도. 무명도. 나락. 도철. 혼천도. 혼천마도
			nWaveNum = 53;
			break;
		case 5:  case 10:  case 12: // 삼적대부. 청동도끼. 연자부.
			nWaveNum = 54;
			break;
		case 15:  // 파뇌진당.
			nWaveNum = 55;
			break;
		case 2:  case 3:  case 6:  case 7: case 16:  case 17: case 19: case 24:// 삼지창. 천형목. 홍아창. 곡괭이. 청마창, 용아장. 제마봉
			nWaveNum = 56;
			break;
		default:
			nWaveNum = 57;	// 맨손.
			break;
		}
	}

	if ( nWaveNum != -1 )
	{
		g_SoundManager.SndmngrPlayWavSound(nWaveNum, m_nPosX, m_nPosY);
	}
}


VOID CHero::PlayMoveSound()
{
	if ( m_bCurrMtn == _MT_WALK || m_bCurrMtn == _MT_RUN || m_bCurrMtn == _MT_HORSEWALK || m_bCurrMtn == _MT_HORSERUN || m_bCurrMtn == _MT_MOODEPO || m_bCurrMtn == _MT_PUSHBACK )
	{
		if ( m_bCurrMtn == _MT_HORSEWALK )
		{
			if ( m_dwCurrFrame == m_dwFstFrame+1 )
			{
				g_SoundManager.SndmngrPlayWavSound(33, m_nPosX, m_nPosY);
			}
			else if ( m_dwCurrFrame == m_dwFstFrame+4 )
			{
				g_SoundManager.SndmngrPlayWavSound(34, m_nPosX, m_nPosY);
			}
		}
		else if ( m_bCurrMtn == _MT_HORSERUN && m_dwCurrFrame == m_dwFstFrame+3 )
		{
			g_SoundManager.SndmngrPlayWavSound(35, m_nPosX, m_nPosY);
		}
		else if ( m_bCurrMtn != _MT_HORSEWALK && m_bCurrMtn != _MT_HORSERUN )
		{
			if ( m_dwCurrFrame == m_dwEndFrame-5 || m_bBackStepFrame == m_dwEndFrame-5 || m_dwCurrFrame == m_dwEndFrame-2 || m_bBackStepFrame == m_bBackStepFrameCnt-2  )
			{
				g_SoundManager.SndmngrPlayWavSound(1, m_nPosX, m_nPosY);
			}
		}
	}
}


VOID CHero::ShowShield()
{
	// 2006.08.29
	// 주술의막, 선천기공 이펙트 시전관련
#ifdef _TEST_SERVER_DEBUG
	/*if( this->m_nIdentity == g_xGameProc.m_xMyHero.m_nIdentity )
	{
		CHAR szwCharState[256];
		sprintf( szwCharState, "m_nCharState : %d, m_dwShieldTick : %d", m_nCharState, ( m_dwShieldTick ) );
		g_xMainWnd.PutsHan( NULL, 300, 350, RGB( 255, 255, 255 ), RGB( 0, 0, 0 ), szwCharState );
	}*/
#endif

	if ( (m_nCharState & 0x00100000) && (timeGetTime()-m_dwShieldTick > 1700)/*(m_bCurrMtn != _MT_SPELL1 || m_bCurrMtn != _MT_SPELL2)*/ )
//	if ( (m_nCharState & 0x00100000) && (timeGetTime()-m_dwShieldTick > 1500)/*(m_bCurrMtn != _MT_SPELL1 || m_bCurrMtn != _MT_SPELL2)*/ )
	{
		WORD wShieldFrm;

		if ( m_bCurrMtn == _MT_HITTED )
			wShieldFrm = (WORD)(m_bShieldCurrFrm + 853);
		else
			wShieldFrm = (WORD)(m_bShieldCurrFrm + 850);
//			wShieldFrm = (WORD)(m_bShieldCurrFrm + 570);

		CWHWilImageData* pxWilImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_MAGIC];
//		CWHWilImageData* pxWilImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_MAGICEX3];

		if ( g_xMainWnd.Get3DDevice() )
		{
			LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_MAGIC, _IMAGE_MAGIC, wShieldFrm);

			if ( pxWilImg->NewSetIndex(wShieldFrm) )
			{
				D3DVECTOR vTrans;
				D3DMATRIX matTrans;
				D3DMATRIX matScale;
				D3DMATRIX matWorld;
				D3DMATRIX matWorldOriginal;
				D3DMATERIAL7 mtrl;

				D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)255/255.0f, (FLOAT)255/255.0f);
				mtrl.diffuse.a = 1/255.0f;
				g_xMainWnd.Get3DDevice()->SetMaterial(&mtrl);

 				vTrans.x = (FLOAT)m_nScrnPosX+(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth/2+pxWilImg->m_lpstNewCurrWilImageInfo->shPX-400; 
				vTrans.y = (FLOAT)-m_nScrnPosY-(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight/2-pxWilImg->m_lpstNewCurrWilImageInfo->shPY+300; 
				vTrans.z = 0;

				if( SUCCEEDED(g_xMainWnd.Get3DDevice()->BeginScene()) )
				{
					g_xMainWnd.Get3DDevice()->GetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

					D3DUtil_SetTranslateMatrix(matTrans, vTrans);
					D3DUtil_SetScaleMatrix(matScale, (FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight, 1.0f);
					D3DMath_MatrixMultiply(matWorld, matScale, matTrans);
					g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);

					SetBlendRenderState(g_xMainWnd.Get3DDevice(), _BLEND_LIGHTINV, &mtrl);

					g_xMainWnd.Get3DDevice()->SetTexture(0, lpddsTextr);

					g_xMainWnd.Get3DDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_VERTEX, m_avBoard, 4, NULL);

					ResetBlendenderState(g_xMainWnd.Get3DDevice());

					g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

					g_xMainWnd.Get3DDevice()->EndScene();
				}		
			}			
		}
	}
	else if ( (m_nCharState & 0X00040000) && (timeGetTime()-m_dwShieldTick > 2000) ) // 선천기공
	{
		WORD wShieldFrm;

		if ( m_bCurrMtn == _MT_HITTED )
			wShieldFrm = (WORD)(m_bShieldCurrFrm + 303);
		else
			wShieldFrm = (WORD)(m_bShieldCurrFrm + 300);

		CWHWilImageData* pxWilImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_MAGICEX2];

		if ( g_xMainWnd.Get3DDevice() )
		{
			LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_MAGIC, _IMAGE_MAGICEX2, wShieldFrm);

			if ( pxWilImg->NewSetIndex(wShieldFrm) )
			{
				D3DVECTOR vTrans;
				D3DMATRIX matTrans;
				D3DMATRIX matScale;
				D3DMATRIX matWorld;
				D3DMATRIX matWorldOriginal;
				D3DMATERIAL7 mtrl;

				D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)255/255.0f, (FLOAT)255/255.0f);
				mtrl.diffuse.a = 1/255.0f;
				g_xMainWnd.Get3DDevice()->SetMaterial(&mtrl);

 				vTrans.x = (FLOAT)m_nScrnPosX+(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth/2+pxWilImg->m_lpstNewCurrWilImageInfo->shPX-400; 
				vTrans.y = (FLOAT)-m_nScrnPosY-(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight/2-pxWilImg->m_lpstNewCurrWilImageInfo->shPY+300; 
				vTrans.z = 0;

				if( SUCCEEDED(g_xMainWnd.Get3DDevice()->BeginScene()) )
				{
					g_xMainWnd.Get3DDevice()->GetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

					D3DUtil_SetTranslateMatrix(matTrans, vTrans);
					D3DUtil_SetScaleMatrix(matScale, (FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight, 1.0f);
					D3DMath_MatrixMultiply(matWorld, matScale, matTrans);
					g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);

					SetBlendRenderState(g_xMainWnd.Get3DDevice(), _BLEND_LIGHTINV, &mtrl);

					g_xMainWnd.Get3DDevice()->SetTexture(0, lpddsTextr);

					g_xMainWnd.Get3DDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_VERTEX, m_avBoard, 4, NULL);

					ResetBlendenderState(g_xMainWnd.Get3DDevice());

					g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

					g_xMainWnd.Get3DDevice()->EndScene();
				}		
			}			
		}
	}
	else if ( ( m_nCharState & 0X00010000) && (timeGetTime()-m_dwShieldTick > 1500)/*(m_bCurrMtn != _MT_SPELL1 || m_bCurrMtn != _MT_SPELL2)*/ )
	{
		WORD wShieldFrm;

		if ( m_bCurrMtn == _MT_HITTED )
			wShieldFrm = (WORD)(m_bShieldCurrFrm + 573);
		else
			wShieldFrm = (WORD)(m_bShieldCurrFrm + 570);

		CWHWilImageData* pxWilImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_MAGICEX3];

		if ( g_xMainWnd.Get3DDevice() )
		{
			LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_MAGIC, _IMAGE_MAGICEX3, wShieldFrm);

			if ( pxWilImg->NewSetIndex(wShieldFrm) )
			{
				D3DVECTOR vTrans;
				D3DMATRIX matTrans;
				D3DMATRIX matScale;
				D3DMATRIX matWorld;
				D3DMATRIX matWorldOriginal;
				D3DMATERIAL7 mtrl;

				D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)255/255.0f, (FLOAT)255/255.0f);
				mtrl.diffuse.a = 1/255.0f;
				g_xMainWnd.Get3DDevice()->SetMaterial(&mtrl);

 				vTrans.x = (FLOAT)m_nScrnPosX+(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth/2+pxWilImg->m_lpstNewCurrWilImageInfo->shPX-400; 
				vTrans.y = (FLOAT)-m_nScrnPosY-(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight/2-pxWilImg->m_lpstNewCurrWilImageInfo->shPY+300; 
				vTrans.z = 0;

				if( SUCCEEDED(g_xMainWnd.Get3DDevice()->BeginScene()) )
				{
					g_xMainWnd.Get3DDevice()->GetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

					D3DUtil_SetTranslateMatrix(matTrans, vTrans);
					D3DUtil_SetScaleMatrix(matScale, (FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight, 1.0f);
					D3DMath_MatrixMultiply(matWorld, matScale, matTrans);
					g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);

					SetBlendRenderState(g_xMainWnd.Get3DDevice(), _BLEND_LIGHTINV, &mtrl);

					g_xMainWnd.Get3DDevice()->SetTexture(0, lpddsTextr);

					g_xMainWnd.Get3DDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_VERTEX, m_avBoard, 4, NULL);

					ResetBlendenderState(g_xMainWnd.Get3DDevice());

					g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

					g_xMainWnd.Get3DDevice()->EndScene();
				}		
			}			
		}
	}

}

VOID CHero::ShowPahwangbo()
{
	if ( m_bCurrMtn == _MT_MOODEPO && m_bPahwangbo )
	{
		WORD wFrame;
		
		INT nTemp = (m_dwCurrFrame - m_dwFstFrame)/2;

		wFrame = 740 + m_bCurrDir*10 + nTemp;

		CWHWilImageData* pxWilImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_MAGICEX2];


		if ( g_xMainWnd.Get3DDevice() )
		{
			LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_MAGIC, _IMAGE_MAGICEX2, wFrame);

			if ( pxWilImg->NewSetIndex(wFrame) )
			{
				D3DVECTOR vTrans;
				D3DMATRIX matTrans;
				D3DMATRIX matScale;
				D3DMATRIX matWorld;
				D3DMATRIX matWorldOriginal;
				D3DMATERIAL7 mtrl;

				D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)255/255.0f, (FLOAT)255/255.0f);
				mtrl.diffuse.a = 1/255.0f;
				g_xMainWnd.Get3DDevice()->SetMaterial(&mtrl);

 				vTrans.x = (FLOAT)m_nScrnPosX+(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth/2+pxWilImg->m_lpstNewCurrWilImageInfo->shPX-400; 
				vTrans.y = (FLOAT)-m_nScrnPosY-(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight/2-pxWilImg->m_lpstNewCurrWilImageInfo->shPY+300; 
				vTrans.z = 0;

				if( SUCCEEDED(g_xMainWnd.Get3DDevice()->BeginScene()) )
				{
					g_xMainWnd.Get3DDevice()->GetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

					D3DUtil_SetTranslateMatrix(matTrans, vTrans);
					D3DUtil_SetScaleMatrix(matScale, (FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight, 1.0f);
					D3DMath_MatrixMultiply(matWorld, matScale, matTrans);
					g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);

					SetBlendRenderState(g_xMainWnd.Get3DDevice(), _BLEND_LIGHTINV, &mtrl);

					g_xMainWnd.Get3DDevice()->SetTexture(0, lpddsTextr);

					g_xMainWnd.Get3DDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_VERTEX, m_avBoard, 4, NULL);

					ResetBlendenderState(g_xMainWnd.Get3DDevice());

					g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

					g_xMainWnd.Get3DDevice()->EndScene();
				}		
			}			
		}
	}
}


/******************************************************************************************************************

	함수명 : CHero::UpdateMove(BOOL bIsMoveTime)

	작성자 : 
	작성일 : 

	목적   : 
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CHero::UpdateMove(BOOL bIsMoveTime)
{
	if ( m_bCurrMtn == _MT_WALK || m_bCurrMtn == _MT_RUN || m_bCurrMtn == _MT_HORSEWALK || m_bCurrMtn == _MT_HORSERUN || m_bCurrMtn == _MT_MOODEPO || m_bCurrMtn == _MT_PUSHBACK )
	{
		m_nCurrDelay = 0;

		if ( bIsMoveTime )
		{
			BYTE bMoveSkipLevel = 0;

			if( m_nCharState & 0X8000000 )			
			{
				bMoveSkipLevel = 1;
			}

			if ( bMoveSkipLevel > 0 )
			{
				bMoveSkipLevel++;
				m_dwCurrMoveSkip++;

				if ( m_dwCurrMoveSkip > 100000 )
				{
					m_dwCurrMoveSkip = 1;
				}

				if ( (m_dwCurrMoveSkip % bMoveSkipLevel) )
				{
					return FALSE;
				}
			}

			if ( m_bCurrMtn == _MT_PUSHBACK )
			{
				m_bBackStepFrame += 2;
				if ( m_bBackStepFrame >= m_bBackStepFrameCnt )
				{
					m_dwCurrFrame++;
					m_bBackStepFrame = m_bBackStepFrameCnt;
				}
			}
			else if ( m_bCurrMtn == _MT_MOODEPO )
			{
				m_dwCurrFrame+=2;
				if ( m_dwCurrFrame >= m_dwEndFrame )
				{
					m_dwCurrFrame = m_dwEndFrame;
				}

				// 밀다가 실패한경우이다. 원위치로 돌려준다.
				if ( m_bRushKung )
				{
					if ( m_dwCurrFrame > m_dwEndFrame - 3 )
					{
						m_bRushKung = FALSE;
						m_nPosX = m_nRushKungPosX;
						m_nPosY = m_nRushKungPosY;
						m_nShiftTileX  = 0;
						m_nShiftTileY  = 0;
						m_nShiftPixelX = 0;
						m_nShiftPixelY = 0;

						SetMotionFrame(_MT_ATTACKMODE, m_bCurrDir);
						return TRUE;
					}					
				}
			}
			else
			{
				m_dwCurrFrame++;
				PlayMoveSound();
				if ( m_bMsgHurryCheck )
				{
					m_dwCurrFrame++;
				}
			}

			if ( m_bCurrMtn == _MT_PUSHBACK )
			{
				if ( m_bBackStepFrame >= m_bBackStepFrameCnt-m_bMoveNextFrmCnt && !m_bIsMoved )
				{
					SetMoved();
					m_bIsMoved = TRUE;
				}
			}
			else
			{
				if ( m_dwCurrFrame >= m_dwEndFrame-m_bMoveNextFrmCnt && !m_bIsMoved )
				{
					SetMoved();
					m_bIsMoved = TRUE;
				}
			}
		}

		// 연속적인 프레임 중에서 해야할일.
		if ( m_dwCurrFrame >= m_dwEndFrame )
		{
			m_dwCurrFrame = m_dwEndFrame - 1;

			m_nShiftTileX = 0;
			m_nShiftTileY = 0;
			m_nShiftPixelX = 0;
			m_nShiftPixelY = 0;

			m_dwCurrEffectFrame = 0;
			m_dwFstEffectFrame = 0;
			m_dwEndEffectFrame = 0;
			m_bEffectFrame = 0;
			m_bEffectFrameCnt = _DEFAULT_SPELLFRAME;
			m_bUseEffect = FALSE;
			m_bUseSwordEffect = FALSE;
			m_dwCurrFrame = m_dwFstFrame;

			m_bBackStepFrame = 0;
			m_bBackStepFrameCnt = 0;

			m_bIsMoved = FALSE;

			if ( m_stFeatureEx.bHorse == _HORSE_NONE )
			{
				if ( m_bWarMode )
					SetMotionFrame(_MT_ATTACKMODE, m_bCurrDir);
				else
					SetMotionFrame(_MT_STAND, m_bCurrDir);
			}
			else
			{
				SetMotionFrame(_MT_HORSESTAND, m_bCurrDir);
			}
		}
		else if ( m_dwCurrFrame < m_dwEndFrame )
		{
			if ( m_bCurrMtn != _MT_PUSHBACK )
			{
				SetMoving();
			}
			else
			{
				SetBackStepMoving();
			}
		}
		return TRUE;
	}
	return FALSE;
}


VOID CHero::OnCharDescPacket(LPPACKETMSG lpPacketMsg)
{
	CHARDESC	stCharDesc;
	FEATURE		stFeature;
	fnDecode6BitBuf(lpPacketMsg->szEncodeData, (char*)&stCharDesc, sizeof(CHARDESC));

	memcpy(&stFeature, &stCharDesc.nFeature, sizeof(FEATURE));

	if ( stCharDesc.nFaceImageDate != m_nFaceImageDate)
		m_bNeedLoadFameImg = TRUE;

	m_nCharState			= stCharDesc.nStatus;
	m_nFaceImageDate	= stCharDesc.nFaceImageDate;
	m_bGuildFlag		= stCharDesc.bGuildFlag;
	m_bFlagRed			= stCharDesc.bFlagRed;
	m_bFlagGreen		= stCharDesc.bFlagGreen;
	m_bFlagBlue			= stCharDesc.bFlagBlue;
//	m_wEffectLooks		= stCharDesc.wLooks;

	if( m_nCharState & 0X2 )
		m_bOpenHealth = TRUE;
	else
		m_bOpenHealth = FALSE;

	ChangeFeature(stFeature, m_stFeatureEx);
}




VOID CHero::OnSpaceMoveShow(LPPACKETMSG lpPacketMsg)
{
	BYTE		bDir;
	CHARDESC	stCharDesc;
	FEATURE		stFeature;
	FEATUREEX	stFeatureEx;
	INT			nPos;
	m_nPosX = lpPacketMsg->stDefMsg.wParam;
	m_nPosY = lpPacketMsg->stDefMsg.wTag;
	bDir		 = LOBYTE(lpPacketMsg->stDefMsg.wSeries);
	m_bLightSize = HIBYTE(lpPacketMsg->stDefMsg.wSeries);

	fnDecode6BitBuf(lpPacketMsg->szEncodeData, (char*)&stCharDesc, sizeof(CHARDESC));
	fnDecode6BitBuf(&lpPacketMsg->szEncodeData[_CHARDESCSIZE], (char*)&stFeatureEx , sizeof(FEATUREEX));

	g_SoundManager.SndmngrPlayWavSound(_SOUND_SPACEMOVE_OUT, m_nPosX, m_nPosY);

	if (strlen(lpPacketMsg->szEncodeData) > _CHARDESCSIZE +_FEATURESIZEEX)
	{
/*		CHAR pszDecodeMsg[1024];
		CHAR *pszStr1;
		CHAR *pszStr2;

		nPos = fnDecode6BitBuf(&lpPacketMsg->szEncodeData[_CHARDESCSIZE], pszDecodeMsg, sizeof(pszDecodeMsg));
		pszDecodeMsg[nPos] = '\0';

		if ( pszStr1 = strchr(pszDecodeMsg, '\\') )
		{
			*pszStr1++ = '\0';								// pszDecodeMsg == m_szName;

			strcpy(m_szName, pszDecodeMsg);

			if ( pszStr2 = strrchr(pszStr1, '/') )
			{
				*pszStr2++ = '\0';							// pszStr1 == m_GuildName;

				strcpy(m_szGuildName, pszStr1);

				if ( pszStr2[0] != NULL )
				{
					m_dwNameClr = GetUserNameColor(atoi(pszStr2));
				}
			}
		}
		else
		{
			if ( pszStr2 = strrchr(pszDecodeMsg, '/') )
			{
				*pszStr2++ = '\0';							// pszStr2 == m_szName;
				strcpy(m_szName, pszDecodeMsg);

				if ( pszStr2[0] != NULL )
				{
					m_dwNameClr = GetUserNameColor(atoi(pszStr2));
				}
			}
		}
*/

		char szDecodeMsg[1024];
		nPos		  = fnDecode6BitBuf(lpPacketMsg->szEncodeData, szDecodeMsg, sizeof(szDecodeMsg));
		szDecodeMsg[nPos] = '\0';

		CheckMultiLineName(szDecodeMsg);

		CHAR* szClr = strrchr(szDecodeMsg, '/');

		if ( szClr )
		{
			m_dwNameClr = GetUserNameColor((BYTE)atoi(szClr+1));
			*szClr = '\0';
		}
	}

	memcpy(&stFeature, &stCharDesc.nFeature, sizeof(FEATURE));

	if ( stCharDesc.nFaceImageDate != m_nFaceImageDate)
		m_bNeedLoadFameImg = TRUE;

	m_nCharState			= stCharDesc.nStatus;
	m_nFaceImageDate	= stCharDesc.nFaceImageDate;
	m_bGuildFlag		= stCharDesc.bGuildFlag;
	m_bFlagRed			= stCharDesc.bFlagRed;
	m_bFlagGreen		= stCharDesc.bFlagGreen;
	m_bFlagBlue			= stCharDesc.bFlagBlue;
//	m_wEffectLooks		= stCharDesc.wLooks;

	if( m_nCharState & 0X2 )
		m_bOpenHealth = TRUE;
	else
		m_bOpenHealth = FALSE;

	ChangeFeature(stFeature, stFeatureEx);

	// 아공전서로 다른맵에 나타나기.
	CMagic * pxMagic;
	if ( lpPacketMsg->stDefMsg.wIdent == SM_SPACEMOVE_SHOW )
	{
		pxMagic = new CMagic;
		if ( pxMagic->CreateMagic(_SKILL_SPACEMOVESHOW2, m_nPosX, m_nPosY, m_nPosX, m_nPosY, NULL, 0) )
		{
			g_xGameProc.m_xMagicList.Insert (pxMagic);	
		}
		else 
		{
			delete pxMagic;
		}
	}
	else if ( lpPacketMsg->stDefMsg.wIdent == SM_PULL_SHOW )
	{
		pxMagic = new CMagic;
		if ( pxMagic->CreateMagic(_SKILL_PULLSHOW, m_nPosX, m_nPosY, m_nPosX, m_nPosY, NULL, 0) )
		{
			g_xGameProc.m_xMagicList.Insert (pxMagic);	
		}
		else
		{
			delete pxMagic;
		}
	}	

	if ( m_stFeatureEx.bHorse == _HORSE_NONE )		SetMotionFrame(_MT_STAND, bDir);
	else											SetMotionFrame(_MT_HORSESTAND, bDir);
}

WORD CHero::FindWeaponColor(WORD wColorIdx)
{
	WORD wColor = 0;

	switch ( wColorIdx )
	{
	case 0:
		wColor = RGB(255, 255, 255);
		break;
	case 1:
		wColor = 49345;
		break;
	case 2:
		wColor = 47039;
		break;
	case 3:
		wColor = 15709;
		break;
	case 4:
		wColor = 20382;
		break;
	case 5:
		wColor = 50900;
		break;
	case 6:
		wColor = 0;
		break;
	case 7:
		wColor = 56027;
		break;
	}

	return wColor;
}

VOID CHero::OnFeatureChanged(LPPACKETMSG lpPacketMsg)
{
	FEATURE   stFeature;
	FEATUREEX stFeatureEx;

	LONG nFeature	  = MAKELONG(lpPacketMsg->stDefMsg.wParam, lpPacketMsg->stDefMsg.wTag);

	memcpy(&stFeature, &nFeature, sizeof(LONG));

	fnDecode6BitBuf(lpPacketMsg->szEncodeData, (char*)&stFeature, sizeof(stFeature));
	fnDecode6BitBuf(lpPacketMsg->szEncodeData + _FEATURESIZE, (char*)&stFeatureEx, sizeof(FEATUREEX));

#ifdef _TEST_SERVER		// by eriastoa 2006.05.29
	m_nEft = stFeatureEx.nEft;
#endif
		
	m_bEftFeature		= stFeature.bDress;
	stFeature.bDress = stFeature.bDress & 15; //이운

//	g_xGameProc.m_xMyHero.ChangeFeature(stFeature, stFeatureEx);
	ChangeFeature(stFeature, stFeatureEx);
}

VOID CHero::OnCharStatusChanged(LPPACKETMSG lpPacketMsg)
{
	m_shHitSpeed = lpPacketMsg->stDefMsg.wSeries;
	m_nCharState = MAKELONG(lpPacketMsg->stDefMsg.wParam, lpPacketMsg->stDefMsg.wTag);

	if ( m_nCharState == 0 )
		m_bIsSturn = FALSE;

	if( m_nCharState & 0X00000002 )
		m_bOpenHealth = TRUE;
	else
		m_bOpenHealth = FALSE;
}

VOID CHero::OnRush(LPPACKETMSG lpPacketMsg)
{
/*	BYTE bDir = lpPacketMsg->stDefMsg.wSeries;
	m_nPosX   = lpPacketMsg->stDefMsg.wParam;
	m_nPosY   = lpPacketMsg->stDefMsg.wTag;
	SetMotionFrame(_MT_MOODEPO, bDir);
	m_bMoveSpeed = _SPEED_WALK;
	SetMoving();
*/
	BYTE		bDir;
	CHARDESC	stCharDesc;
	FEATURE		stFeature;
	FEATUREEX	stFeatureEx;
//	m_nPosX = lpPacketMsg->stDefMsg.wParam;
//	m_nPosY = lpPacketMsg->stDefMsg.wTag;
	bDir		 = LOBYTE(lpPacketMsg->stDefMsg.wSeries);
	m_bLightSize = HIBYTE(lpPacketMsg->stDefMsg.wSeries);

	fnDecode6BitBuf(lpPacketMsg->szEncodeData, (char*)&stCharDesc, sizeof(CHARDESC));
//	fnDecode6BitBuf(&lpPacketMsg->szEncodeData[_FEATURESIZE*2], (char*)&stFeatureEx, sizeof(FEATUREEX));
	fnDecode6BitBuf(&lpPacketMsg->szEncodeData[_CHARDESCSIZE], (char*)&stFeatureEx, sizeof(FEATUREEX));

	memcpy(&stFeature, &stCharDesc.nFeature, sizeof(FEATURE));

	if ( stCharDesc.nFaceImageDate != m_nFaceImageDate)
		m_bNeedLoadFameImg = TRUE;

	m_nCharState			= stCharDesc.nStatus;
	m_nFaceImageDate	= stCharDesc.nFaceImageDate;
	m_bGuildFlag		= stCharDesc.bGuildFlag;
	m_bFlagRed			= stCharDesc.bFlagRed;
	m_bFlagGreen		= stCharDesc.bFlagGreen;
	m_bFlagBlue			= stCharDesc.bFlagBlue;
//	m_wEffectLooks		= stCharDesc.wLooks;


	if( m_nCharState & 0X2 )
		m_bOpenHealth = TRUE;
	else
		m_bOpenHealth = FALSE;

	ChangeFeature(stFeature, m_stFeatureEx);
//	ChangeFeature(stFeature, stFeatureEx);

						
	SetMotionFrame(_MT_MOODEPO, bDir);
	m_bMoveSpeed = _SPEED_WALK;

	g_xGameProc.m_xMap.GetLastTile(lpPacketMsg->stDefMsg.wParam, lpPacketMsg->stDefMsg.wTag, bDir, m_nPosX, m_nPosY);

	SetMoving();
}

VOID CHero::OnRushKung(LPPACKETMSG lpPacketMsg)
{
	BYTE		bDir;
	CHARDESC	stCharDesc;
	FEATURE		stFeature;
	FEATUREEX	stFeatureEx;
	bDir		 = LOBYTE(lpPacketMsg->stDefMsg.wSeries);
	m_bLightSize = HIBYTE(lpPacketMsg->stDefMsg.wSeries);

	fnDecode6BitBuf(lpPacketMsg->szEncodeData, (char*)&stCharDesc, sizeof(CHARDESC));
	fnDecode6BitBuf(&lpPacketMsg->szEncodeData[_CHARDESCSIZE], (char*)&stFeatureEx, sizeof(FEATUREEX));

	memcpy(&stFeature, &stCharDesc.nFeature, sizeof(FEATURE));

	if ( stCharDesc.nFaceImageDate != m_nFaceImageDate)
		m_bNeedLoadFameImg = TRUE;

	m_nCharState			= stCharDesc.nStatus;
	m_nFaceImageDate	= stCharDesc.nFaceImageDate;
	m_bGuildFlag		= stCharDesc.bGuildFlag;
	m_bFlagRed			= stCharDesc.bFlagRed;
	m_bFlagGreen		= stCharDesc.bFlagGreen;
	m_bFlagBlue			= stCharDesc.bFlagBlue;
//	m_wEffectLooks		= stCharDesc.wLooks;

	if( m_nCharState & 0X2 )
		m_bOpenHealth = TRUE;
	else
		m_bOpenHealth = FALSE;

	ChangeFeature(stFeature, m_stFeatureEx);
						
	SetMotionFrame(_MT_MOODEPO, bDir);
	m_bMoveSpeed	= _SPEED_WALK;
	g_xGameProc.m_xMap.GetLastTile(lpPacketMsg->stDefMsg.wParam, lpPacketMsg->stDefMsg.wTag, bDir, m_nPosX, m_nPosY);

	m_bRushKung		= TRUE;
	m_nRushKungPosX = m_nPosX;
	m_nRushKungPosY = m_nPosY;

	SetMoving();
}

VOID CHero::OnBackStep(LPPACKETMSG lpPacketMsg)
{
	BYTE		bDir;
	CHARDESC	stCharDesc;
	FEATURE		stFeature;
	FEATUREEX	stFeatureEx;
	INT			nPos;
	bDir		 = LOBYTE(lpPacketMsg->stDefMsg.wSeries);
	BYTE		bRevDir;
	if ( bDir < 4 )			bRevDir = (BYTE)(bDir + 4);
	else					bRevDir = (BYTE)(bDir - 4);
	m_bLightSize = HIBYTE(lpPacketMsg->stDefMsg.wSeries);

	fnDecode6BitBuf(lpPacketMsg->szEncodeData, (char*)&stCharDesc, sizeof(CHARDESC));
	fnDecode6BitBuf(&lpPacketMsg->szEncodeData[_CHARDESCSIZE], (char*)&stFeatureEx , sizeof(FEATUREEX));

/*	if ( strlen(lpPacketMsg->szEncodeData) > _CHARDESCSIZE+_FEATURESIZEEX )
	{
		nPos = fnDecode6BitBuf(&lpPacketMsg->szEncodeData[_CHARDESCSIZE +_FEATURESIZEEX], m_szName, sizeof(m_szName));
		m_szName[nPos] = '\0';

		CHAR* szClr = strrchr(m_szName, '/');

		if ( szClr )
		{
			m_dwNameClr = GetUserNameColor((BYTE)atoi(szClr+1));
			*szClr = '\0';
		}
	}*/

	memcpy(&stFeature, &stCharDesc.nFeature, sizeof(FEATURE));

	if ( stCharDesc.nFaceImageDate != m_nFaceImageDate)
		m_bNeedLoadFameImg = TRUE;

	m_nCharState			= stCharDesc.nStatus;
	m_nFaceImageDate	= stCharDesc.nFaceImageDate;
	m_bGuildFlag		= stCharDesc.bGuildFlag;
	m_bFlagRed			= stCharDesc.bFlagRed;
	m_bFlagGreen		= stCharDesc.bFlagGreen;
	m_bFlagBlue			= stCharDesc.bFlagBlue;
//	m_wEffectLooks		= stCharDesc.wLooks;

	if( m_nCharState & 0X2 )
		m_bOpenHealth = TRUE;
	else
		m_bOpenHealth = FALSE;

	ChangeFeature(stFeature, stFeatureEx);

	SetMotionFrame(_MT_PUSHBACK, bDir);

	if ( m_bCurrDir < 4 )			m_bMoveDir = (BYTE)(m_bCurrDir + 4);
	else							m_bMoveDir = (BYTE)(m_bCurrDir - 4);

	m_bMoveSpeed = _SPEED_WALK;
	m_bBackStepFrame	= 0;
	m_bBackStepFrameCnt = 6;

	g_xGameProc.m_xMap.GetLastTile(lpPacketMsg->stDefMsg.wParam, lpPacketMsg->stDefMsg.wTag, bRevDir, m_nPosX, m_nPosY);

	SetBackStepMoving();
}

VOID CHero::OnDeath(LPPACKETMSG lpPacketMsg)
{
	BYTE bDir;
	m_nPosX = lpPacketMsg->stDefMsg.wParam;
	m_nPosY = lpPacketMsg->stDefMsg.wTag;
	bDir		 = LOBYTE(lpPacketMsg->stDefMsg.wSeries);
	m_bLightSize = HIBYTE(lpPacketMsg->stDefMsg.wSeries);
	OnCharDescPacket(lpPacketMsg);
	m_bHPPercent = 0;
	SetMotionFrame(_MT_DIE, bDir);

	if ( g_xGameProc.m_pxSavedTargetActor && g_xGameProc.m_pxSavedTargetActor->m_nIdentity == lpPacketMsg->stDefMsg.nRecog )
	{
		g_xGameProc.m_pxSavedTargetActor = NULL;
	}

	if ( lpPacketMsg->stDefMsg.wIdent == SM_DEATH )
	{
		m_dwCurrFrame = m_dwEndFrame - 1;
		m_bIsDead = TRUE;
	}
}

VOID CHero::OnWalk(LPPACKETMSG lpPacketMsg)
{
	BYTE		bDir;
	CHARDESC	stCharDesc;
	FEATURE		stFeature;
	FEATUREEX	stFeatureEx;
	bDir		 = LOBYTE(lpPacketMsg->stDefMsg.wSeries);
	m_bLightSize = HIBYTE(lpPacketMsg->stDefMsg.wSeries);

	fnDecode6BitBuf(lpPacketMsg->szEncodeData, (char*)&stCharDesc, sizeof(CHARDESC));
	fnDecode6BitBuf(&lpPacketMsg->szEncodeData[_CHARDESCSIZE], (char*)&stFeatureEx, sizeof(FEATUREEX));

	memcpy(&stFeature, &stCharDesc.nFeature, sizeof(FEATURE));

	if ( stCharDesc.nFaceImageDate != m_nFaceImageDate)
		m_bNeedLoadFameImg = TRUE;

	m_nCharState			= stCharDesc.nStatus;
	m_nFaceImageDate	= stCharDesc.nFaceImageDate;
	m_bGuildFlag		= stCharDesc.bGuildFlag;
	m_bFlagRed			= stCharDesc.bFlagRed;
	m_bFlagGreen		= stCharDesc.bFlagGreen;
	m_bFlagBlue			= stCharDesc.bFlagBlue;
//	m_wEffectLooks		= stCharDesc.wLooks;

	if( m_nCharState & 0X2 )
		m_bOpenHealth = TRUE;
	else
		m_bOpenHealth = FALSE;

	ChangeFeature(stFeature, stFeatureEx);

	if ( m_stFeatureEx.bHorse == _HORSE_NONE )		SetMotionFrame(_MT_WALK, bDir);
	else											SetMotionFrame(_MT_HORSEWALK, bDir);
						
	m_bMoveSpeed = _SPEED_WALK;

	g_xGameProc.m_xMap.GetLastTile(lpPacketMsg->stDefMsg.wParam, lpPacketMsg->stDefMsg.wTag, bDir, m_nPosX, m_nPosY);
	
	SetMoving();
}

VOID CHero::OnRun(LPPACKETMSG lpPacketMsg)
{
	BYTE		bDir;
	CHARDESC	stCharDesc;
	FEATURE		stFeature;
	FEATUREEX	stFeatureEx;
//	m_nPosX = lpPacketMsg->stDefMsg.wParam;
//	m_nPosY = lpPacketMsg->stDefMsg.wTag;
	bDir		 = LOBYTE(lpPacketMsg->stDefMsg.wSeries);
	m_bLightSize = HIBYTE(lpPacketMsg->stDefMsg.wSeries);

	fnDecode6BitBuf(lpPacketMsg->szEncodeData, (char*)&stCharDesc, sizeof(CHARDESC));
	fnDecode6BitBuf(&lpPacketMsg->szEncodeData[_CHARDESCSIZE], (char*)&stFeatureEx, sizeof(FEATUREEX));

	memcpy(&stFeature, &stCharDesc.nFeature, sizeof(FEATURE));

	if ( stCharDesc.nFaceImageDate != m_nFaceImageDate)
		m_bNeedLoadFameImg = TRUE;

	m_nCharState			= stCharDesc.nStatus;
	m_nFaceImageDate	= stCharDesc.nFaceImageDate;
	m_bGuildFlag		= stCharDesc.bGuildFlag;
	m_bFlagRed			= stCharDesc.bFlagRed;
	m_bFlagGreen		= stCharDesc.bFlagGreen;
	m_bFlagBlue			= stCharDesc.bFlagBlue;
//	m_wEffectLooks		= stCharDesc.wLooks;

	if( m_nCharState & 0X2 )
		m_bOpenHealth = TRUE;
	else
		m_bOpenHealth = FALSE;

	ChangeFeature(stFeature, stFeatureEx);

	if ( m_stFeatureEx.bHorse == _HORSE_NONE )	
	{
		SetMotionFrame(_MT_RUN, bDir);
		m_bMoveSpeed = _SPEED_RUN;
	}
	else
	{
		SetMotionFrame(_MT_HORSERUN, bDir);
		m_bMoveSpeed = _SPEED_HORSERUN;
	}

	g_xGameProc.m_xMap.GetLastTile(lpPacketMsg->stDefMsg.wParam, lpPacketMsg->stDefMsg.wTag, bDir, m_nPosX, m_nPosY, m_bMoveSpeed);

	SetMoving();
}


VOID CHero::OnTurn(LPPACKETMSG lpPacketMsg)
{
	BYTE		bDir;
	CHARDESC	stCharDesc;
	FEATURE		stFeature;
	FEATUREEX	stFeatureEx;
	INT			nPos;
	m_nPosX = lpPacketMsg->stDefMsg.wParam;
	m_nPosY = lpPacketMsg->stDefMsg.wTag;
	bDir		 = LOBYTE(lpPacketMsg->stDefMsg.wSeries);
	m_bLightSize = HIBYTE(lpPacketMsg->stDefMsg.wSeries);

	fnDecode6BitBuf(lpPacketMsg->szEncodeData, (char*)&stCharDesc, sizeof(CHARDESC));
	fnDecode6BitBuf(&lpPacketMsg->szEncodeData[_CHARDESCSIZE], (char*)&stFeatureEx , sizeof(FEATUREEX));

	if ( lpPacketMsg->stDefMsg.wIdent == SM_REVIVAL || lpPacketMsg->stDefMsg.wIdent == SM_MYREVIVAL )
	{
		m_bIsDead = FALSE;
		m_nABlendDelay = 600;
		m_nABlendCurrDelay = 0;
	}
	if (strlen(lpPacketMsg->szEncodeData) > _CHARDESCSIZE +_FEATURESIZEEX)
	{
		CHAR szName[64];
		nPos = fnDecode6BitBuf(&lpPacketMsg->szEncodeData[_CHARDESCSIZE +_FEATURESIZEEX], szName, sizeof(szName));
		szName[nPos] = '\0';

		CheckMultiLineName(szName);

		CHAR* szClr = strrchr(szName, '/');

		if ( szClr )
		{
			m_dwNameClr = GetUserNameColor((BYTE)atoi(szClr+1));
			*szClr = '\0';
		}
	}

	memcpy(&stFeature, &stCharDesc.nFeature, sizeof(FEATURE));

	if ( stCharDesc.nFaceImageDate != m_nFaceImageDate)
		m_bNeedLoadFameImg = TRUE;

	m_nCharState			= stCharDesc.nStatus;
	m_nFaceImageDate	= stCharDesc.nFaceImageDate;
	m_bGuildFlag		= stCharDesc.bGuildFlag;
	m_bFlagRed			= stCharDesc.bFlagRed;
	m_bFlagGreen		= stCharDesc.bFlagGreen;
	m_bFlagBlue			= stCharDesc.bFlagBlue;
//	m_wEffectLooks		= stCharDesc.wLooks;

	if( m_nCharState & 0X2 )
		m_bOpenHealth = TRUE;
	else
		m_bOpenHealth = FALSE;

	ChangeFeature(stFeature, stFeatureEx);

	if ( m_stFeatureEx.bHorse == _HORSE_NONE )		SetMotionFrame(_MT_STAND, bDir);
	else											SetMotionFrame(_MT_HORSESTAND, bDir);
}

VOID CHero::OnSetXY(LPPACKETMSG lpPacketMsg)
{
	g_xGameProc.m_xMyHero.m_nOldPosX = lpPacketMsg->stDefMsg.wParam;
	g_xGameProc.m_xMyHero.m_nOldPosY = lpPacketMsg->stDefMsg.wTag;
	g_xGameProc.m_xMyHero.SetOldPosition();
}

VOID CHero::OnStruck(LPPACKETMSG lpPacketMsg)
{
	WORD		  wDamage;
	MESSAGEBODYWL stMsgBodyWl;
	FEATURE		  stFeature;
	CMagic*		  pxMagic = NULL;

	wDamage			 = lpPacketMsg->stDefMsg.wSeries;
	FLOAT wHPRate = 0.0f;
	if ( lpPacketMsg->stDefMsg.wTag != 0 )
	{
		wHPRate = (FLOAT)((FLOAT)lpPacketMsg->stDefMsg.wParam/(FLOAT)lpPacketMsg->stDefMsg.wTag);
	}
	m_wHP			 = lpPacketMsg->stDefMsg.wParam;
	m_wMAXHP		 = lpPacketMsg->stDefMsg.wTag;
	m_bHPPercent     = (BYTE)(wHPRate*100);
	m_bShieldCurrFrm = 0;

	if ( g_xGameProc.m_bShowBloodNum && m_bCurrMtn != _MT_DIE )
	{
		m_nShowBlood[m_nShowBloodIdx] = wDamage*(-1);
		m_ptShowBlood[m_nShowBloodIdx].x = m_nScrnPosX;
		m_ptShowBlood[m_nShowBloodIdx].y = m_nScrnPosY;
		m_dwShowBloodTimer[m_nShowBloodIdx] = 0;

		m_nShowBloodIdx++;

		if ( m_nShowBloodIdx > 7 )
			m_nShowBloodIdx = 0;
	}

	fnDecode6BitBuf(lpPacketMsg->szEncodeData, (char*)&stMsgBodyWl, sizeof(MESSAGEBODYWL));
	memcpy(&stFeature, &stMsgBodyWl.lParam1, sizeof(LONG));

	ChangeFeature(stFeature, m_stFeatureEx);

	if ( wDamage != 0 )
	{
		if ( m_stFeatureEx.bHorse == _HORSE_NONE )
			SetMotionFrame(_MT_HITTED, m_bCurrDir);
		else
			SetMotionFrame(_MT_HORSEHIT, m_bCurrDir);
	}

	// 원소타격마법.
	if ( !m_bIsDead && wDamage != 0 )
	{
		pxMagic = new CMagic;
		if ( pxMagic->CreateMagic(_SKILL_STRUCK_FIRE+HIWORD(stMsgBodyWl.nTag2), m_nPosX, m_nPosY, m_nPosX, m_nPosY, this, m_nIdentity) )
			g_xGameProc.m_xMagicList.Insert (pxMagic);
		else
			delete pxMagic;
	}

	CActor*		pxActor = NULL;
	CListNode <CActor> *pNode;

	ZeroMemory(&m_stHitter,    sizeof(FEATURE));

	if ( stMsgBodyWl.nTag1 == g_xGameProc.m_xMyHero.m_nIdentity )
	{
		m_stHitter = g_xGameProc.m_xMyHero.m_stFeature;
	}
	else
	{
		for (pNode = g_xGameProc.m_xActorList.GetHead(); pNode; pNode = pNode->GetNext())
		{
			CActor* pxGaheja = pNode->GetData();

			if ( pxGaheja )
			{
				if ( pxGaheja->m_nIdentity == stMsgBodyWl.nTag1 )
				{
					m_stHitter = pxGaheja->m_stFeature;
					break;
				}
			}
		}	
	}

	// 몬스터일때.
	if ( m_stHitter.bGender == _GENDER_MON )
	{
		switch ( m_stHitter.bDress )
		{
		case 104:		// 적월마.
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_REDMOON, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this) )
			{
				g_xGameProc.m_xMagicList.Insert (pxMagic);

				LPEVENTIMG pstEvent;

				pstEvent = new EVENTIMG;
				pstEvent->nEventID = 0;
				pstEvent->nType	   = 0;
				pstEvent->dwTick  = timeGetTime();
				pstEvent->nTileX = m_nPosX;
				pstEvent->nTileY = m_nPosY;
				pstEvent->dwLifeTime = 15000;
				pstEvent->wFrameNum = (WORD)(250);
				pstEvent->wOutDelay = 420;
				pstEvent->bUseAlpha = FALSE;
				g_xGameProc.m_stEventImgList.Insert (pstEvent);
			}
			else
				delete pxMagic;
			break;
		case 2:		// 케팔로프.
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_KEPAL, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this, 0) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
			break;
		case 67:	// 촉룡신.
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_BIGGINE_CHAR, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
			break;
		case 150:	// 돈왕.
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_MONMAGIC_BYDONKING, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this) )
				g_xGameProc.m_xMagicList.Insert (pxMagic);
			else
				delete pxMagic;
			break;
		default :
			break;
		}
	}
}

VOID CHero::OnHit(LPPACKETMSG lpPacketMsg)
{
	BYTE bDir, bKind;

	bDir	= LOBYTE(lpPacketMsg->stDefMsg.wSeries);
	bKind	= HIBYTE(lpPacketMsg->stDefMsg.wSeries);

	m_nPosX = lpPacketMsg->stDefMsg.wParam;
	m_nPosY = lpPacketMsg->stDefMsg.wTag;

	m_dwCurrEffectFrame = 50;
	m_dwFstEffectFrame  = 50;
	m_dwEndEffectFrame  = 60;
	m_bEffectFrame		= 0;
	m_bEffectFrameCnt	= _DEFAULT_SPELLFRAME;
	m_bWarMode			= TRUE;

	if ( lpPacketMsg->stDefMsg.wIdent == SM_WIDEHIT )
	{
		SetMotionFrame(g_xSpriteInfo.GetWeaponMtn(m_stFeature.bWeapon, FALSE), bDir);
		LoadEffect(&g_xGameProc.m_xImage, _SKILL_BANWOL, bDir, bKind);
		m_bUseSwordEffect = TRUE;
//		m_bUseBanwol = TRUE;
	}
	else if ( lpPacketMsg->stDefMsg.wIdent == SM_MANWOL )
	{
		SetMotionFrame(g_xSpriteInfo.GetWeaponMtn(m_stFeature.bWeapon, FALSE), bDir);
		LoadEffect(&g_xGameProc.m_xImage, _SKILL_MANWOL, 0, bKind);
		m_bUseSwordEffect = TRUE;
		m_bUseManwol = TRUE;
	}
	else if ( lpPacketMsg->stDefMsg.wIdent == SM_MANWOL_HIGH )
	{
		SetMotionFrame(g_xSpriteInfo.GetWeaponMtn(m_stFeature.bWeapon, FALSE), bDir);
		LoadEffect(&g_xGameProc.m_xImage, _SKILL_MANWOL_HIGH, 0, bKind);
		m_bUseSwordEffect = TRUE;
		m_bUseHManwol = TRUE;
	}
	else if ( lpPacketMsg->stDefMsg.wIdent == SM_THROWHIT )
	{
		SetMotionFrame(_MT_ONEVSWING, bDir);
	}
	else if ( lpPacketMsg->stDefMsg.wIdent == SM_POWERHIT )
	{
		SetMotionFrame(g_xSpriteInfo.GetWeaponMtn(m_stFeature.bWeapon), bDir);
		LoadEffect(&g_xGameProc.m_xImage, _SKILL_YEDO, bDir, bKind);
		m_bUseSwordEffect = TRUE;
		m_bYedoCnt = 2;
	}
	else if ( lpPacketMsg->stDefMsg.wIdent == SM_POWERHIT_HIGH )
	{
		SetMotionFrame(g_xSpriteInfo.GetWeaponMtn(m_stFeature.bWeapon), bDir);
		LoadEffect(&g_xGameProc.m_xImage, _SKILL_YEDO_HIGH, bDir, bKind);
		m_bUseSwordEffect = TRUE;
		m_bHYedoCnt = 2;
	}
	else if ( lpPacketMsg->stDefMsg.wIdent == SM_FIREHIT )
	{
		SetMotionFrame(g_xSpriteInfo.GetWeaponMtn(m_stFeature.bWeapon), bDir);
		LoadEffect(&g_xGameProc.m_xImage, _SKILL_FIRESWORD, bDir, bKind);
		m_bUseSwordEffect = TRUE;
		m_bFireHitCnt = 2;
	}
	else if ( lpPacketMsg->stDefMsg.wIdent == SM_LONGHIT )
	{
		SetMotionFrame(g_xSpriteInfo.GetWeaponMtn(m_stFeature.bWeapon), bDir);
		LoadEffect(&g_xGameProc.m_xImage, _SKILL_ERGUM, bDir, bKind);
		m_bUseSwordEffect = TRUE;
		m_bUseErgum = TRUE;
	}
	else if ( lpPacketMsg->stDefMsg.wIdent == SM_LONGHIT_HIGH )
	{
		SetMotionFrame(g_xSpriteInfo.GetWeaponMtn(m_stFeature.bWeapon), bDir);
		LoadEffect(&g_xGameProc.m_xImage, _SKILL_ERGUM_HIGH, bDir, bKind);
		m_bUseSwordEffect = TRUE;
		m_bUseHErgum = TRUE;
	}
	else if ( lpPacketMsg->stDefMsg.wIdent == SM_RANDSWINGHIT )
	{
		SetMotionFrame(_MT_RANDSWING, bDir);
		LoadEffect(&g_xGameProc.m_xImage, _SKILL_RANDSWING, bDir, bKind);
		m_bUseSwordEffect = TRUE;
		m_bRandSwingCnt = 2;
	}
	else if ( lpPacketMsg->stDefMsg.wIdent == SM_HIGH_RANDSWINGHIT )
	{
		SetMotionFrame(_MT_RANDSWING, bDir);
		LoadEffect(&g_xGameProc.m_xImage, _SKILL_RANDSWING_HIGH, bDir, bKind);
		m_bUseSwordEffect = TRUE;
		m_bHRandSwingCnt = 2;
	}
	else if ( lpPacketMsg->stDefMsg.wIdent == SM_BACKSWINGHIT )
	{
		SetMotionFrame(_MT_WHEELWIND, m_bCurrDir);
		LoadEffect(&g_xGameProc.m_xImage, _SKILL_JUMPSHOT, bDir, bKind);
		m_bUseSwordEffect = TRUE;
		m_bBackSwingCnt = 2;
	}
	else if ( lpPacketMsg->stDefMsg.wIdent == SM_BACKKICKHIT )
	{
		SetMotionFrame(_MT_BACKDROPKICK, bDir);
		g_SoundManager.SndmngrPlayWavSound(_SKILL_KICK*10 + 10000, m_nPosX, m_nPosY);
	}
	else if ( lpPacketMsg->stDefMsg.wIdent == SM_BACKKICKUP )
	{
		if ( m_nIdentity != g_xGameProc.m_xMyHero.m_nIdentity )
		{
			SetMotionFrame(_MT_BACKDROPKICK, bDir);
			g_SoundManager.SndmngrPlayWavSound(_SKILL_KICK*10 + 10000, m_nPosX, m_nPosY);
		}

		INT nTargetX, nTargetY;

		switch ( bDir )
		{
		case 0:
			nTargetX = m_nPosX;
			nTargetY = m_nPosY - 1;
			break;
		case 1:
			nTargetX = m_nPosX + 1;
			nTargetY = m_nPosY - 1;
			break;
		case 2:
			nTargetX = m_nPosX + 1;
			nTargetY = m_nPosY;
			break;
		case 3:
			nTargetX = m_nPosX + 1;
			nTargetY = m_nPosY + 1;
			break;
		case 4:
			nTargetX = m_nPosX;
			nTargetY = m_nPosY + 1;
			break;
		case 5:
			nTargetX = m_nPosX - 1;
			nTargetY = m_nPosY + 1;
			break;
		case 6:
			nTargetX = m_nPosX - 1;
			nTargetY = m_nPosY;
			break;
		case 7:
			nTargetX = m_nPosX - 1;
			nTargetY = m_nPosY - 1;
			break;
		}

		CMagic* pxMagic;
		pxMagic = new CMagic;
		if ( pxMagic->CreateMagic(_SKILL_TAWOO, m_nPosX, m_nPosY, nTargetX, nTargetY, NULL, 0) )
			g_xGameProc.m_xMagicList.Insert (pxMagic);						
		else
			delete pxMagic;
	}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	else if ( lpPacketMsg->stDefMsg.wIdent == SM_HEAVYHIT )
	{
		// 곡괭이질.
		SetMotionFrame(g_xSpriteInfo.GetWeaponMtn(m_stFeature.bWeapon), bDir);

		// 먼지붙이기.
		if ( lpPacketMsg->szEncodeData[0] != NULL )
		{
			m_bViewDigFragment = TRUE;
		}
	}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	else
	{

		bDir = LOBYTE(lpPacketMsg->stDefMsg.wSeries);
		BYTE bAttackMode; 
		bAttackMode = HIBYTE(lpPacketMsg->stDefMsg.wSeries);
		SetMotionFrame(g_xSpriteInfo.GetWeaponMtn(m_stFeature.bWeapon), bDir);

		if ( bKind != 7 )
		{
			// 속성공격 Effect.
			WORD wSkillNum;
			wSkillNum = _SKILL_GUMGI_FIRE + bKind;
			LoadEffect(&g_xGameProc.m_xImage, wSkillNum, bDir, bKind);
			m_bUseSwordEffect = TRUE;
		}

		/*CHAR szMsg[ 256 ];
		sprintf( szMsg, "%d", bAttackMode );
		g_xMainWnd.PutsHan( NULL, 10, 10, RGB( 0, 0, 0 ), RGB( 255, 255, 255 ), szMsg, NULL );*/
	}
}

VOID CHero::OnThrowDot(LPPACKETMSG lpPacketMsg)
{
	POINT	ptPos;
	WORD	wMagicID;
	INT		nMagicTargetID, nPos;

	ptPos.x	 = lpPacketMsg->stDefMsg.wParam;
	ptPos.y  = lpPacketMsg->stDefMsg.wTag;
	wMagicID = (BYTE)lpPacketMsg->stDefMsg.wSeries;

	nPos = fnDecode6BitBuf(lpPacketMsg->szEncodeData, (CHAR*)&nMagicTargetID, sizeof(INT));

	// 표창번호를 구한다.
	WORD wWeapon = _SKILL_DOT_1+m_stFeature.bWeapon-33;

	CMagic* pxMagic;
	pxMagic = new CMagic;
	
//	if ( pxMagic->CreateMagic(_SKILL_SNOWDART, m_nPosX, m_nPosY, ptPos.x, ptPos.y, NULL, nMagicTargetID) )
	if ( pxMagic->CreateMagic(wWeapon, m_nPosX, m_nPosY, ptPos.x, ptPos.y, NULL, nMagicTargetID) )
	{
		g_xGameProc.m_xMagicList.Insert(pxMagic);	
	}
	else
	{
		delete pxMagic;
	}
}


VOID CHero::OnMagicFire(LPPACKETMSG lpPacketMsg)
{
	POINT	ptPos;
	WORD	wMagicID;
	INT		nMagicTargetID, nPos;
	INT		nAtom = lpPacketMsg->stDefMsg.wSeries;

	ptPos.x	 = lpPacketMsg->stDefMsg.wParam;
	ptPos.y  = lpPacketMsg->stDefMsg.wTag;
	wMagicID = lpPacketMsg->stDefMsg.wSeries;

	if ( wMagicID >= 10000 )
	{
		if ( wMagicID != _SKILL_ERGUM_HIGH && wMagicID != _SKILL_MAXDEFENCE_HIGH && wMagicID != _SKILL_MANWOL_HIGH && 
			 wMagicID != _SKILL_YEDO_HIGH &&  wMagicID != _SKILL_TAMMING_HIGH && wMagicID != _SKILL_AMYOUNSUL_HIGH && 
			 wMagicID != _SKILL_REVIVE_HIGH && wMagicID != _SKILL_REMOVEPOISON_HIGH )
			 wMagicID -= 10000;
	}

	nPos = fnDecode6BitBuf(lpPacketMsg->szEncodeData, (CHAR*)&nMagicTargetID, sizeof(INT));
	
	if ( wMagicID == _SKILL_SMALLSPACEMOVE ||
		 wMagicID == _SKILL_SPACEMOVE   || wMagicID == _SKILL_SINSU			 || 
		 wMagicID == _SKILL_FIREWIND    || wMagicID == _SKILL_CLOAK	         || wMagicID == _SKILL_SKELLETON	  ||
		 wMagicID == _SKILL_TRANSFORM   || /*wMagicID == _SKILL_LIGHTFLOWER    || */wMagicID == _SKILL_LIGHTFLOWERUP  || 
		 wMagicID == _SKILL_POWERSKELLETON || wMagicID == _SKILL_FULLCLOAK   || wMagicID == _SKILL_DOLL )
	{
		return;
	}

	if ( wMagicID == _SKILL_CONCENFIREBALL )
	{
		CMagic* pxMagic;
		pxMagic = new CMagic;
		if ( pxMagic->CreateMagic(_SKILL_FIREBALL, m_nPosX, m_nPosY, ptPos.x, ptPos.y, NULL, 0) )
			g_xGameProc.m_xMagicList.Insert (pxMagic);						
		else
			delete pxMagic;

		for ( INT nCnt = 0; nCnt < 2; nCnt++ )
		{
			CConcenFireball* pxCocenFireball;
			pxCocenFireball = new CConcenFireball;
			if ( pxCocenFireball->CreateMagic(wMagicID, m_nPosX, m_nPosY, ptPos.x, ptPos.y, NULL, 0, nCnt*30, nCnt) )
				g_xGameProc.m_xMagicList.Insert (pxCocenFireball);
			else
				delete pxCocenFireball;
		}
	}
	else if ( wMagicID == _SKILL_HURRICANESHOT || wMagicID == _SKILL_HURRICANEBOMB)
	{
		for (int nI=0; nI<1; nI++)
		{
			CHurricaneMagic* pxHurricaneMagic;
			pxHurricaneMagic = new CHurricaneMagic;

			pxHurricaneMagic->mHurricaneMagic_nId = nI;

			if ( pxHurricaneMagic->CreateMagic(wMagicID, m_nPosX, m_nPosY, ptPos.x, ptPos.y, wMagicID, NULL, 0) )
			{
				g_xGameProc.m_xGroundMagicList.Insert (pxHurricaneMagic);
			}
			else
				delete pxHurricaneMagic;
		}
	}
	else if ( wMagicID == _SKILL_FIRE || wMagicID == _SKILL_ICE )
	{
		MakeMagicStream(wMagicID, nMagicTargetID, ptPos.x, ptPos.y);
	}
	else if ( wMagicID == _SKILL_CROSS_ICE )
	{
		POINT ptTar1,ptTar2,ptTar3,ptStart;

		switch ( m_bCurrDir )
		{
		case 0: 
			ptTar1.x = m_nPosX;
			ptTar1.y = m_nPosY - 5;
			ptTar2.x = m_nPosX - 5;
			ptTar2.y = m_nPosY - 5;
			ptTar3.x = m_nPosX + 5;
			ptTar3.y = m_nPosY - 5;
			ptStart.x = m_nPosX;
			ptStart.y = m_nPosY - 1;
			break;
		case 1: 
			ptTar1.x = m_nPosX + 5;
			ptTar1.y = m_nPosY - 5;
			ptTar2.x = m_nPosX;
			ptTar2.y = m_nPosY - 5;
			ptTar3.x = m_nPosX + 5;
			ptTar3.y = m_nPosY;
			ptStart.x = m_nPosX + 1;
			ptStart.y = m_nPosY - 1;
			break;
		case 2: 
			ptTar1.x = m_nPosX + 5;
			ptTar1.y = m_nPosY - 5;
			ptTar2.x = m_nPosX + 5;
			ptTar2.y = m_nPosY;
			ptTar3.x = m_nPosX + 5;
			ptTar3.y = m_nPosY + 5;
			ptStart.x = m_nPosX + 1;
			ptStart.y = m_nPosY;
			break;
		case 3: 
			ptTar1.x = m_nPosX + 5;
			ptTar1.y = m_nPosY + 5;
			ptTar2.x = m_nPosX + 5;
			ptTar2.y = m_nPosY;
			ptTar3.x = m_nPosX;
			ptTar3.y = m_nPosY + 5;
			ptStart.x = m_nPosX + 1;
			ptStart.y = m_nPosY + 1;
			break;
		case 4: 
			ptTar1.x = m_nPosX;
			ptTar1.y = m_nPosY + 5;
			ptTar2.x = m_nPosX + 5;
			ptTar2.y = m_nPosY + 5;
			ptTar3.x = m_nPosX - 5;
			ptTar3.y = m_nPosY + 5;
			ptStart.x = m_nPosX;
			ptStart.y = m_nPosY + 1;
			break;
		case 5: 
			ptTar1.x = m_nPosX - 5;
			ptTar1.y = m_nPosY + 5;
			ptTar2.x = m_nPosX;
			ptTar2.y = m_nPosY + 5;
			ptTar3.x = m_nPosX - 5;
			ptTar3.y = m_nPosY;
			ptStart.x = m_nPosX - 1;
			ptStart.y = m_nPosY + 1;
			break;
		case 6: 
			ptTar1.x = m_nPosX - 5;
			ptTar1.y = m_nPosY;
			ptTar2.x = m_nPosX - 5;
			ptTar2.y = m_nPosY - 5;
			ptTar3.x = m_nPosX - 5;
			ptTar3.y = m_nPosY + 5;
			ptStart.x = m_nPosX - 1;
			ptStart.y = m_nPosY;
			break;
		case 7: 
			ptTar1.x = m_nPosX - 5;
			ptTar1.y = m_nPosY - 5;
			ptTar2.x = m_nPosX;
			ptTar2.y = m_nPosY - 5;
			ptTar3.x = m_nPosX - 5;
			ptTar3.y = m_nPosY;
			ptStart.x = m_nPosX - 1;
			ptStart.y = m_nPosY - 1;
			break;
		}
		MakeMagicStreamEx(_SKILL_CROSS_ICE, ptStart.x, ptStart.y, ptTar1.x, ptTar1.y);
		MakeMagicStreamEx(_SKILL_CROSS_ICE, ptStart.x, ptStart.y, ptTar2.x, ptTar2.y);
		MakeMagicStreamEx(_SKILL_CROSS_ICE, ptStart.x, ptStart.y, ptTar3.x, ptTar3.y);
	}
	else if ( wMagicID != _SKILL_EARTHFIRE &&  wMagicID != _SKILL_HOLYSHIELD && wMagicID != _SKILL_LIGHTWALL && wMagicID != _SKILL_KANGMAK && wMagicID !=_SKILL_COPY 
		    && wMagicID != _SKILL_JISOKGYE )
	{
		CMagic* pxMagic;
		pxMagic = new CMagic;
		if ( pxMagic->CreateMagic(wMagicID, m_nPosX, m_nPosY, ptPos.x, ptPos.y, NULL, nMagicTargetID, 0, -1) )
			g_xGameProc.m_xMagicList.Insert (pxMagic);						
		else
			delete pxMagic;

		if ( wMagicID == _SKILL_SHOOTLIGHTEN )
		{
			MakeMagicStream(_SKILL_SHOOTLIGHTEN_ADD, nMagicTargetID, ptPos.x, ptPos.y);
		}
	}

	m_nCurrMagicID = wMagicID;
}


VOID CHero::OnMagicFire2(LPPACKETMSG lpPacketMsg)
{
	POINT	ptPos;
	WORD	wMagicID;
	INT		nMagicTargetID, nPos;

	ptPos.x	 = lpPacketMsg->stDefMsg.wParam;
	ptPos.y  = lpPacketMsg->stDefMsg.wTag;
	wMagicID = (BYTE)lpPacketMsg->stDefMsg.wSeries;

	char szDecodeMsg[1024];
	nPos = fnDecode6BitBuf(lpPacketMsg->szEncodeData, szDecodeMsg, sizeof(szDecodeMsg));

	if ( wMagicID == _SKILL_FIREBALL10 )
	{
		char *pszMsg  = (szDecodeMsg);
		char *pszNext;
		int  nCount = 0;
		INT	 nTarX, nTarY, nTargetID;

		do
		{
			if ( pszNext = strchr(pszMsg, '/') )
			{
				*pszNext = '\0';				
				nTargetID = atoi(pszMsg);
				if (  pszNext != NULL )
					pszMsg = pszNext + 1;
				
				// ID 뽑기
				CActor* pxActor = g_xGameProc.FindActor(nTargetID);

				if ( pxActor != NULL )
				{
					CMagic* pxMagic;
					pxMagic = new CMagic;

					if ( pxMagic->CreateMagic(wMagicID, m_nPosX, m_nPosY, pxActor->m_nPosX, pxActor->m_nPosY, NULL, nTargetID) )
						g_xGameProc.m_xMagicList.Insert (pxMagic);						
					else
						delete pxMagic;
				}
			}
			else if ( pszMsg != NULL )
			{
				nTargetID = atoi(pszMsg);

				CActor* pxActor = g_xGameProc.FindActor(nTargetID);

				if ( pxActor != NULL )
				{
					CMagic* pxMagic;
					pxMagic = new CMagic;

					if ( pxMagic->CreateMagic(wMagicID, m_nPosX, m_nPosY, pxActor->m_nPosX, pxActor->m_nPosY, NULL, nTargetID) )
						g_xGameProc.m_xMagicList.Insert (pxMagic);						
					else
						delete pxMagic;
				}
				else if ( g_xGameProc.m_xMyHero.m_nIdentity == nTargetID )
				{
					CMagic* pxMagic;
					pxMagic = new CMagic;

					if ( pxMagic->CreateMagic(wMagicID, m_nPosX, m_nPosY, g_xGameProc.m_xMyHero.m_nPosX, g_xGameProc.m_xMyHero.m_nPosY, NULL, nTargetID) )
						g_xGameProc.m_xMagicList.Insert (pxMagic);						
					else
						delete pxMagic;
				}
			}
		} while (pszNext);
	}

	m_nCurrMagicID = wMagicID;
}


VOID CHero::OnSpell(LPPACKETMSG lpPacketMsg)
{
	BYTE  bMagicDir; 
	WORD  wMagicID;
	POINT ptTargetPos;
	INT	  nAtom = -1;

//	nAtom = lpPacketMsg->stDefMsg.wSeries;

	ptTargetPos.x = lpPacketMsg->stDefMsg.wParam;
	ptTargetPos.y = lpPacketMsg->stDefMsg.wTag;
//	bDir		  = lpPacketMsg->stDefMsg.wSeries;
//	nPos		  = fnDecode6BitBuf(lpPacketMsg->szEncodeData, szDecodeMsg, sizeof(szDecodeMsg));
//	szDecodeMsg[nPos] = '\0';

	bMagicDir = g_xGameProc.m_xMap.GetNextDirection(m_nPosX, m_nPosY, ptTargetPos.x, ptTargetPos.y);
	wMagicID  = (WORD)atoi(lpPacketMsg->szEncodeData);

	// 쾌도난마 2006.10.26
#ifdef _TEST_SERVER
	if( wMagicID == _SKILL_HYPERSWORD )
		g_xGameProc.m_nMagicStoneIdx = lpPacketMsg->stDefMsg.wSeries;
	else
		g_xGameProc.m_nMagicStoneIdx = -1;
#endif

	if ( wMagicID >= 10000 )
	{
		if ( wMagicID != _SKILL_ERGUM_HIGH && wMagicID != _SKILL_MAXDEFENCE_HIGH && wMagicID != _SKILL_MANWOL_HIGH && 
			 wMagicID != _SKILL_YEDO_HIGH &&  wMagicID != _SKILL_TAMMING_HIGH && wMagicID != _SKILL_AMYOUNSUL_HIGH && 
			 wMagicID != _SKILL_REVIVE_HIGH && wMagicID != _SKILL_REMOVEPOISON_HIGH )
			 wMagicID -= 10000;
	}

	if ( wMagicID == _SKILL_FIREBALL     || wMagicID == _SKILL_FIREBALL2	|| wMagicID == _SKILL_FIRE       || wMagicID == _SKILL_SHOOTLIGHTEN || wMagicID == _SKILL_ICE				 ||
		 wMagicID == _SKILL_HANGMAJINBUB || wMagicID== _SKILL_DEJIWONHO     || wMagicID == _SKILL_FIRECHARM  || wMagicID == _SKILL_BIGCLOAK		|| wMagicID == _SKILL_SINSU				 ||
		 wMagicID == _SKILL_ICEBOLT		 || wMagicID == _SKILL_SUPERICEBOLT || wMagicID == _SKILL_MAGICARROW || wMagicID == _SKILL_MOONOK		|| wMagicID == _SKILL_MOONCHAM			 ||
		 wMagicID == _SKILL_POWERUP		 || wMagicID == _SKILL_MAGICUP		|| wMagicID == _SKILL_MAGICUP_FIRE	|| wMagicID == _SKILL_MAGICUP_ICE|| wMagicID == _SKILL_MAGICUP_LIGHTENING  ||wMagicID==_SKILL_MAGICUP_WIND	 || 
		 wMagicID == _SKILL_HANDWIND	 || wMagicID == _SKILL_ANTIMAGIC_FIRE||wMagicID == _SKILL_ANTIMAGIC_ICE||wMagicID== _SKILL_ANTIMAGIC_LIGHTENING||wMagicID==_SKILL_ANTIMAGIC_WIND ||		 
		 wMagicID == _SKILL_WITH_FIRE    || wMagicID == _SKILL_WITH_ICE     || wMagicID == _SKILL_WITH_LIGHT   ||	
		 wMagicID == _SKILL_WITH_WIND    ||	wMagicID == _SKILL_WITH_DEF	    || wMagicID == _SKILL_WITH_MAGIC   ||	
		 wMagicID == _SKILL_WITH_ATT	 || wMagicID == _SKILL_CONCENFIREBALL || 
		 wMagicID == _SKILL_CROSS_ICE	 ||
		 wMagicID == _SKILL_FIREBALL10	 ||
		 wMagicID == _SKILL_PULL		 || wMagicID == _SKILL_MYULSAL		|| wMagicID == _SKILL_DEJIWONHO_HIGH||
		 wMagicID == _SKILL_MOONCHAM_HIGH|| wMagicID == _SKILL_BALSACHE		|| wMagicID == _SKILL_JIKSUNGYE		|| wMagicID == _SKILL_CLOAK_HIGH )
	{
		LoadEffect(&g_xGameProc.m_xImage, wMagicID, bMagicDir, nAtom);
	}
	else
	{
		LoadEffect(&g_xGameProc.m_xImage, wMagicID);
	}

	m_bEffectFrameCnt	= _DEFAULT_SPELLFRAME;

	if	( wMagicID == _SKILL_SHOWHP )									m_bEffectFrameCnt = 20;
//	else if ( wMagicID == _SKILL_LIGHTFLOWER )							m_bEffectFrameCnt = 11;
	else if ( wMagicID == _SKILL_LIGHTENING )							m_bEffectFrameCnt = 13;
	else if ( wMagicID == _SKILL_TRANSFORM )							m_bEffectFrameCnt = 14;

	m_bWarMode = m_bUseEffect = TRUE;

	if ( wMagicID == _SKILL_SHIELD || wMagicID == _SKILL_DOSASHIELD || wMagicID == _SKILL_SHIELD_HIGH )
	{
		m_dwShieldTick = timeGetTime();
	}
	m_nCurrMagicID	= wMagicID;

	switch( wMagicID )
	{
		case _SKILL_HANGMAJINBUB:
		case _SKILL_DEJIWONHO:
		case _SKILL_FIRECHARM:
		case _SKILL_MYULSAL:
		case _SKILL_FIRE:
		case _SKILL_ICE:
		case _SKILL_FIREBALL2:
		case _SKILL_FIREBALL:
		case _SKILL_BALSACHE:
		case _SKILL_SHOOTLIGHTEN:
		case _SKILL_JIKSUNGYE:
		case _SKILL_BIGCLOAK:
		case _SKILL_ICEBOLT:
		case _SKILL_SUPERICEBOLT:
		case _SKILL_MAGICARROW:
		case _SKILL_MOONOK:
		case _SKILL_MOONCHAM:
		case _SKILL_MOONCHAM_HIGH:
		case _SKILL_CONCENFIREBALL:
		case _SKILL_POWERUP:
		
		case _SKILL_WITH_FIRE:
		case _SKILL_WITH_ICE:
		case _SKILL_WITH_LIGHT:
		case _SKILL_WITH_WIND:
		case _SKILL_WITH_DEF:
		case _SKILL_WITH_MAGIC:
		case _SKILL_WITH_ATT:

		case _SKILL_MAGICUP:
		case _SKILL_MAGICUP_FIRE:
		case _SKILL_MAGICUP_ICE:
		case _SKILL_CROSS_ICE:
		case _SKILL_MAGICUP_LIGHTENING:
		case _SKILL_MAGICUP_WIND:
		case _SKILL_HANDWIND:
		case _SKILL_ANTIMAGIC_FIRE:
		case _SKILL_ANTIMAGIC_ICE:
		case _SKILL_ANTIMAGIC_LIGHTENING:
		case _SKILL_ANTIMAGIC_WIND:
		case _SKILL_PULL:
		case _SKILL_FIREBALL10:
		case _SKILL_INHALEHP:
			SetMotionFrame(_MT_SPELL1, bMagicDir);
			break;
		case _SKILL_FIREWIND:	
		case _SKILL_AMYOUNSUL:
		case _SKILL_BIGAM:
		case _SKILL_AMYOUNSUL_HIGH:
		case _SKILL_MONSTERUP:
		case _SKILL_REMOVEPOISON:
		case _SKILL_DEJIWONHO_HIGH:
		case _SKILL_REMOVEPOISON_HIGH:
		case _SKILL_TAMMING:
		case _SKILL_TAMMING_HIGH:
		case _SKILL_KILLUNDEAD:
		case _SKILL_HEALLING:
		case _SKILL_HOLYSHIELD:
		case _SKILL_LIGHTWALL:
		case _SKILL_BIGHEALLING:
		case _SKILL_LIGHTFLOWER:
		case _SKILL_LIGHTFLOWERUP:
		case _SKILL_SKELLETON:
		case _SKILL_DOLL:
		case _SKILL_POWERSKELLETON:
		case _SKILL_SINSU:
		case _SKILL_SNOWWIND:
		case _SKILL_THUNDERSTORM:
		case _SKILL_SHIELD:
		case _SKILL_SHIELD_HIGH:
		case _SKILL_DOSASHIELD:
		case _SKILL_SHOWHP:
		case _SKILL_EARTHFIRE:
		case _SKILL_JISOKGYE:
		case _SKILL_KANGMAK:
		case _SKILL_FIREBOOM:
		case _SKILL_HYPERSWORD:
		case _SKILL_POKBAL:
		case _EFFECT_FIRECRACKER_S:
		case _EFFECT_FIRECRACKER_M:
		case _EFFECT_FIRECRACKER_L:
		case _EFFECT_FIRECRACKER_XL:
		case _SKILL_COPY:
		case _SKILL_EARTH_SUMMON:
		case _SKILL_MAGICTRAP:
		case _SKILL_FIREBOOMUP:
		case _SKILL_SPACEMOVE:
		case _SKILL_SMALLSPACEMOVE:
		case _SKILL_CLOAK:
		case _SKILL_CLOAK_HIGH:
		case _SKILL_FULLCLOAK:
		case _SKILL_LIGHTENING:

		case _SKILL_TRANSFORM:
		case _SKILL_REVIVE:
		case _SKILL_REVIVE_HIGH:
		case _SKILL_HURRICANE :
		case _SKILL_HURRICANESHOT:
		case _SKILL_HURRICANEBOMB:
		case _SKILL_CHANGEPOSITION:
		default:
			SetMotionFrame(_MT_SPELL2, bMagicDir);
			break;			
	}

	// 딜레이를 줄인다.
	if ( m_nCurrMagicID == _SKILL_SMALLSPACEMOVE )
	{
		m_nDelay = 40;
	}
}



VOID CHero::OnButch(LPPACKETMSG lpPacketMsg)
{
	BYTE bDir;
	m_nPosX = lpPacketMsg->stDefMsg.wParam;
	m_nPosY = lpPacketMsg->stDefMsg.wTag;
	bDir	= (BYTE)lpPacketMsg->stDefMsg.wSeries;
	SetMotionFrame(_MT_CUT, bDir);
}


/******************************************************************************************************************

	함수명 : CHero::UpdatePacketState()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CHero::UpdatePacketState()
{
	LPPACKETMSG	lpPacketMsg = NULL;

	if ( m_bCurrMtn == _MT_STAND || m_bCurrMtn == _MT_ATTACKMODE || m_bCurrMtn == _MT_HORSESTAND /*|| (m_bCurrMtn==_MT_SPELL1 && m_dwCurrFrame == m_dwEndFrame-2)*/ || m_bIsDead )
	{
		INT nLeftMsgCnt = m_xPacketQueue.GetCount();

		if ( nLeftMsgCnt > 0 )
		{
			if ( nLeftMsgCnt >= 3 )			m_bMsgHurryCheck = TRUE;
			else							m_bMsgHurryCheck = FALSE;

			lpPacketMsg = (LPPACKETMSG)m_xPacketQueue.PopQ();
			
			if ( lpPacketMsg )
			{
				switch ( lpPacketMsg->stDefMsg.wIdent )
				{
					case SM_DIGUP:				
					{	
						OnDigup(lpPacketMsg);				
						break;	
					}
					case SM_DIGDOWN:				
					{	
						OnDigDown(lpPacketMsg);				
						break;	
					}
					case SM_SITDOWN:
					case SM_BUTCH:				
					{	
						OnButch(lpPacketMsg);		
						break;	
					}
					case SM_RUSH:				
					{
						m_bPahwangbo = FALSE;
						OnRush(lpPacketMsg);				
						break;	
					}
					case SM_RUSH2:
					{
						m_bPahwangbo = TRUE;
						INT nWaveNum = _SKILL_PAWHANGBO * 10 + 10000;
						g_SoundManager.SndmngrPlayWavSound(nWaveNum, m_nPosX, m_nPosY);
						OnRush(lpPacketMsg);
						break;	
					}
					case SM_RUSHKUNG:
					{
						OnRushKung(lpPacketMsg);			
						break;	
					}
					case SM_BACKSTEP:			
					{
						OnBackStep(lpPacketMsg);			
						break;	
					}
					case SM_BACKSTEP2:
					{
						m_bIsSturn = TRUE;
						OnBackStep(lpPacketMsg);
						break;
					}
					case SM_NOWDEATH:
					case SM_DEATH:
					{
						OnDeath(lpPacketMsg);				
						break;
					}
					case SM_WALK:
					{
						OnWalk(lpPacketMsg);				
						break;	
					}
					case SM_RUN:				
					{	
						OnRun(lpPacketMsg);					
						break;	
					}
					case SM_TURN:				
					case SM_REVIVAL:
					{	
						OnTurn(lpPacketMsg);				
						break;	
					}
					case SM_STRUCK:				
					{
						OnStruck(lpPacketMsg);				
						break;	
					}
					case SM_STRUCK2:				
					{
						OnStruck(lpPacketMsg);
						LPPACKETMSG	lpPacketMsgAdd = new PACKETMSG;
						memcpy(lpPacketMsgAdd , lpPacketMsg, sizeof(PACKETMSG));
						lpPacketMsgAdd->stDefMsg.wIdent = SM_STRUCK;
						m_xPacketQueue.PushQ((BYTE*)lpPacketMsgAdd );
						break;	
					}
					case SM_SPACEMOVE_SHOW:		
					case SM_SPACEMOVE_SHOW2:	
					case SM_PULL_SHOW:
					{
						OnSpaceMoveShow(lpPacketMsg);		
						break;	
					}
					case SM_SPACEMOVE_HIDE:		
					case SM_SPACEMOVE_HIDE2:	
					{
						OnSpaceMoveHide(lpPacketMsg);		
						break;	
					}
					case SM_HIT:
					case SM_HEAVYHIT:
					case SM_FIREHIT:
					case SM_LONGHIT:
					case SM_POWERHIT:
					case SM_BACKSWINGHIT:
					case SM_BACKKICKHIT:
					case SM_BACKKICKUP:
					case SM_RANDSWINGHIT:
					case SM_HIGH_RANDSWINGHIT:
					case SM_WIDEHIT:
					case SM_MANWOL:
					case SM_THROWHIT:			
					{	
						OnHit(lpPacketMsg);					
						break;	
					}
					case SM_THROWDOT:
					{
						OnThrowDot(lpPacketMsg);
						break;
					}
					case SM_MAGICFIRE:			
					{
						OnMagicFire(lpPacketMsg);			
						break;	
					}
					case SM_REFLEXPOWER:
					{
						CMagic* pxMagic;
						pxMagic = new CMagic;
						if ( pxMagic->CreateMagic(_SKILL_BANTAN_HITTED, m_nPosX, m_nPosY, m_nPosX, m_nPosY, NULL, 0) )
							g_xGameProc.m_xMagicList.Insert (pxMagic);						
						else
							delete pxMagic;
						break;
					}
					case SM_MAGICFIRE2:
					{
						OnMagicFire2(lpPacketMsg);			
						break;	
					}
					case SM_SPELL:				
					{
						OnSpell(lpPacketMsg);				
						break;	
					}
					case SM_LIGHTING:			
					{	
						OnLighting(lpPacketMsg);
						break;	
					}
					default:
					{										
						break;	
					}
				}

				SAFE_DELETE(lpPacketMsg);

				if ( m_bIsDead )
				{
					SetMotionFrame(_MT_DIE, m_bCurrDir);
					m_dwCurrFrame = m_dwEndFrame - 1;
				}
				
				return TRUE;
			}
		}
	}

	return FALSE;
}



/******************************************************************************************************************

	함수명 : CHero::UpdateMotionState()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : INT nLoopTime
	         BOOL bIsMoveTime
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CHero::UpdateMotionState(INT nLoopTime, BOOL bIsMoveTime)
{
	if ( m_bWarMode ) 
		m_dwWarModeTime += nLoopTime;

	m_nABlendCurrDelay += nLoopTime;
	m_nShieldCurrDelay += nLoopTime;

	if ( m_nShieldCurrDelay > 150 )  
	{
		m_bShieldCurrFrm++;
		m_nShieldCurrDelay = 0;

		if ( m_bShieldCurrFrm > 2 )
			m_bShieldCurrFrm = 0;
	}

	if ( m_nABlendCurrDelay >= m_nABlendDelay )
	{
		m_nABlendCurrDelay = 0;
		m_nABlendDelay  = 0;
		m_bABlendRev	= FALSE;
	}

	if ( m_bCurrMtn == _MT_DIE && m_dwCurrFrame >= m_dwEndFrame-1 )
	{
		m_bIsDead = TRUE;
	}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if ( m_bViewDigFragment )
	{
		if ( m_bCurrMtn == g_xSpriteInfo.GetWeaponMtn(m_stFeature.bWeapon) && m_dwCurrFrame == m_dwFstFrame + 3 )
		{
			CMagic* pxMagic;
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_EVENT_DUST, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this, -1) )
			{
				g_xGameProc.m_xMagicList.Insert(pxMagic);	
			}
			else
			{
				delete pxMagic;
			}

			LPEVENTIMG	pstEvent = g_xGameProc.FindEvent(_ET_PILESTONES, m_nPosX, m_nPosY);
			if ( pstEvent)
			{
				pstEvent->wFrameNum++;
				if ( pstEvent->wFrameNum >= 234 )
				{
					pstEvent->wFrameNum = 234;
				}								
			}

			m_bViewDigFragment = FALSE;
		}
	}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	if ( UpdateMove(bIsMoveTime) )
	{
		UpdatePacketState();
		return;
	}
	else
	{
		m_nCurrDelay += nLoopTime;

		if ( m_nCurrDelay > m_nDelay )
		{
			m_nCurrDelay = 0;

			if ( m_dwCurrFrame < m_dwEndFrame )
			{
				m_dwCurrFrame++;

				PlayActSound();

				if ( (m_bCurrMtn == _MT_SPELL2 || m_bCurrMtn == _MT_SPELL1) && m_bUseEffect )
				{
					m_dwCurrEffectFrame++;
					m_bEffectFrame++;
				}

				if ( m_bMsgHurryCheck )			
				{
					m_nDelay = m_nDelay/2;
					m_bMsgHurryCheck = FALSE;
				}
			}
		}

		if ( m_dwWarModeTime > _WARMODE_TIME )
		{
			m_dwWarModeTime = 0;
			m_bWarMode		= FALSE;
		}

/*		if ( (m_bCurrMtn == _MT_SPELL2) && m_bUseEffect )
		{
			if ( m_dwCurrFrame >= m_dwEndFrame-1 )
			{
				if ( m_dwCurrEffectFrame - m_dwFstEffectFrame <= (BYTE)(m_bEffectFrameCnt-2) )
				{
					m_nDelay = 70;
					m_dwCurrFrame = m_dwEndFrame - 2;
				}
			}
		}
		else if ( (m_bCurrMtn == _MT_SPELL1) && m_bUseEffect )
		{
			if ( m_dwCurrFrame >= m_dwEndFrame-3 )
			{
				if ( m_dwCurrEffectFrame - m_dwFstEffectFrame < (BYTE)(m_bEffectFrameCnt-4) )
				{
					m_nDelay = 70;
					m_dwCurrFrame = m_dwEndFrame - 4;
				}
			}
		}
*/		if ( (m_bCurrMtn == _MT_SPELL2) && m_bUseEffect )
		{
			if ( m_dwCurrFrame >= m_dwEndFrame-1 )
			{
				if ( m_dwCurrEffectFrame - m_dwFstEffectFrame <= (BYTE)(m_bEffectFrameCnt-2) )
				{
					m_nDelay = 70;
					m_dwCurrFrame = m_dwEndFrame - 2;
				}
			}
		}
		else if ( (m_bCurrMtn == _MT_SPELL1) && m_bUseEffect )
		{
			if ( m_dwCurrFrame >= m_dwEndFrame-3 && m_dwCurrFrame < m_dwEndFrame-2 )
			{
				if ( m_dwCurrEffectFrame - m_dwFstEffectFrame < (BYTE)(m_bEffectFrameCnt-4) )
				{
					m_dwCurrFrame = m_dwEndFrame - 4;
				}
			}
			else if ( m_dwCurrFrame >= m_dwEndFrame-2 && m_dwCurrFrame < m_dwEndFrame-1 )
			{
				m_nDelay = 200;
			}
			else if ( m_dwCurrFrame >= m_dwEndFrame-1 )
			{
				m_nDelay = 80;
			}
		}

		if ( m_dwCurrFrame >= m_dwEndFrame )
		{
			m_dwCurrEffectFrame = 0;
			m_dwFstEffectFrame = 0;
			m_dwEndEffectFrame = 0;
			m_bEffectFrame = 0;
			m_bEffectFrameCnt = _DEFAULT_SPELLFRAME;
			m_bUseEffect = FALSE;
			m_bUseSwordEffect = FALSE;
			m_dwCurrFrame = m_dwFstFrame;

			if ( m_bIsDead )
			{
				SetMotionFrame(_MT_DIE, m_bCurrDir);
				m_dwCurrFrame = m_dwEndFrame - 1;
			}
			else if ( m_stFeatureEx.bHorse == _HORSE_NONE )
			{
				if ( m_bWarMode )
					SetMotionFrame(_MT_ATTACKMODE, m_bCurrDir);
				else
					SetMotionFrame(_MT_STAND, m_bCurrDir);
			}
			else
			{
				SetMotionFrame(_MT_HORSESTAND, m_bCurrDir);
			}
		}

		UpdatePacketState();
	}
}



/******************************************************************************************************************

	함수명 : CHero::ChangeFeature()

	작성자 : 
	작성일 : 

	목적   : BYTE bGender, BYTE bWear, BYTE bHair, BYTE bWeapon;
	입력   : WORD wActor
	         BYTE bHair
	         BYTE bWeapon
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CHero::ChangeFeature(FEATURE stFeature, FEATUREEX stFeatureEx)
{
	stFeature.bDress = stFeature.bDress & 15; //이운교

	if ( CActor::ChangeFeature(stFeature) )
	{
		CImageHandler* pxImgHandler = &g_xGameProc.m_xImage;

		m_stFeatureEx = stFeatureEx;

		if ( m_stFeature.bHair	  >= _MAX_HAIR )
			m_stFeature.bHair	= _HAIR_NONE;

		if ( m_stFeature.bWeapon  >= 100 )
		{
			m_stFeature.bWeapon	= m_stFeature.bWeapon;
		}
		else if ( m_stFeature.bWeapon  >= _MAX_WEAPON )
			m_stFeature.bWeapon	= _WEAPON_NONE;

		if ( m_stFeatureEx.bHorse > _MAX_HORSE )
			m_stFeatureEx.bHorse= _HORSE_NONE;
		else if ( m_stFeatureEx.bHorse == _MAX_HORSE )
			m_stFeatureEx.bHorse= 1;

		if ( m_stFeatureEx.bHorse != _HORSE_NONE )
			m_bHorseImgIdx	= _IMAGE_HORSE;

		if ( m_stFeature.bGender == _GENDER_MAN )
		{
			if ( m_stFeature.bHair != _HAIR_NONE )
			{
				if ( m_stFeature.bHair > 20 )
					m_bHairImgIdx	= (BYTE)(_IMAGE_M_HAIR+(m_stFeature.bHair-1)/10 + 11);
				else
					m_bHairImgIdx	= (BYTE)(_IMAGE_M_HAIR+(m_stFeature.bHair-1)/10);
			}
			if ( m_stFeature.bWeapon != _WEAPON_NONE )
			{
				if ( m_stFeature.bWeapon <= 40 )
					m_bWeaponImgIdx	= (BYTE)(_IMAGE_M_WEAPON1+(m_stFeature.bWeapon-1)/10);
				else if ( m_stFeature.bWeapon >= 100 )
					m_bWeaponImgIdx	= _IMAGE_M_WEAPON10;
				else
					m_bWeaponImgIdx	= _IMAGE_M_WEAPON5;
			}
		}
		else if ( m_stFeature.bGender == _GENDER_WOMAN )
		{
			if ( m_stFeature.bHair != _HAIR_NONE )
			{
				if ( m_stFeature.bHair > 20 )
					m_bHairImgIdx	= (BYTE)(_IMAGE_WM_HAIR+(m_stFeature.bHair-1)/10 + 10);
				else
					m_bHairImgIdx	= (BYTE)(_IMAGE_WM_HAIR+(m_stFeature.bHair-1)/10);
			}
			if ( m_stFeature.bWeapon != _WEAPON_NONE )
			{
				if ( m_stFeature.bWeapon <= 40 )
					m_bWeaponImgIdx	= (BYTE)(_IMAGE_WM_WEAPON1+(m_stFeature.bWeapon-1)/10);
				else if ( m_stFeature.bWeapon >= 100 )
					m_bWeaponImgIdx	= _IMAGE_WM_WEAPON10;
				else
					m_bWeaponImgIdx	= _IMAGE_WM_WEAPON5;
			}
		}
		else
			return FALSE;

		if ( m_stFeature.bHair != _HAIR_NONE )
			m_pxHairImage	= &pxImgHandler->m_xImageList[m_bHairImgIdx];
		else
			m_pxHairImage	= NULL;

		if ( m_stFeature.bWeapon != _WEAPON_NONE )
			m_pxWeaponImage	= &pxImgHandler->m_xImageList[m_bWeaponImgIdx];
		else
			m_pxWeaponImage	= NULL;

		if ( m_stFeatureEx.bHorse != _HORSE_NONE )
			m_pxHorseImage	= &pxImgHandler->m_xImageList[m_bHorseImgIdx];
		else
			m_pxHorseImage	= NULL;

		return TRUE;
	}
	return FALSE;
}


/******************************************************************************************************************

	함수명 : CHero::DrawActor()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : BOOL bFocused
	         BOOL bShadowAblended
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CHero::DrawActor(CMapHandler* pxMap, BOOL bFocused, BOOL bShadowAblended, BOOL bUseScrnPos, BOOL bDrawShadow, BOOL bMyTwice)
{
	// 투명반지 확인
#ifdef _TEST_SERVER_DEBUG
	/*if( this->m_nIdentity == g_xGameProc.m_xMyHero.m_nIdentity )
	{
		CHAR EftFeatureValue[256];
		sprintf( EftFeatureValue, "Dress : %d, Eft : %d", m_stFeature.bDress, m_bEftFeature );
		g_xMainWnd.PutsHan( NULL, 300, 370, RGB( 255, 255, 255 ), RGB( 0, 0, 0 ), EftFeatureValue );
	}*/	
#endif


	// 좌표처리.
	if ( bUseScrnPos )
	{
		m_nScrnPosX = (m_nPosX - pxMap->m_nStartViewTileX) * _CELL_WIDTH + pxMap->m_nViewPosX - pxMap->m_nViewOffsetX + m_nShiftPixelX;
		m_nScrnPosY = (m_nPosY - pxMap->m_nStartViewTileY) * _CELL_HEIGHT+ pxMap->m_nViewPosY - pxMap->m_nViewOffsetY + m_nShiftPixelY;
	}

	if ( m_bCurrMtn == _MT_SPELL2 )
	{
		if ( m_nShiftPixelX ==  0 )
			int sfs = 0;
		else 
			int as = 0;
	}

	if ( bMyTwice == FALSE && g_dwCurrTime - m_dwAfterTimer > 30 )
	{
		m_xAfterImage[m_nSaveIdx].m_dwFrame = m_dwCurrFrame;
		m_xAfterImage[m_nSaveIdx].m_nPosX = m_nPosX;
		m_xAfterImage[m_nSaveIdx].m_nPosY = m_nPosY;
		m_xAfterImage[m_nSaveIdx].m_nShiftPixelX = m_nShiftPixelX;
		m_xAfterImage[m_nSaveIdx].m_nShiftPixelY = m_nShiftPixelY;
		m_xAfterImage[m_nSaveIdx].m_dwFstFrame = m_dwFstFrame;
		m_xAfterImage[m_nSaveIdx].m_dwEndFrame = m_dwEndFrame;
		m_xAfterImage[m_nSaveIdx].m_dwMoveNextFrmCnt = m_bMoveNextFrmCnt;
		m_xAfterImage[m_nSaveIdx].m_bMoveSpeed = m_bMoveSpeed;
		m_xAfterImage[m_nSaveIdx].m_bMtn = m_bCurrMtn;
		m_dwAfterTimer = g_dwCurrTime;

		if ( m_dwCurrFrame == 1200 )
			INT AS = 0;
		

		if ( m_bSetIdx == FALSE )
		{
			if ( m_nSaveIdx == 6 )
			{
				m_nPlayIdx1 = 3;
				m_nPlayIdx2 = 0;
				m_bSetIdx = TRUE;
			}
		}

		if ( m_bSetIdx == TRUE )
		{
			m_nPlayIdx1++;
			m_nPlayIdx2++;
		}

		m_nSaveIdx++;

		if ( m_nSaveIdx >= 10 )
			m_nSaveIdx = 0;

		if ( m_nPlayIdx1 >= 10 )
			m_nPlayIdx1 = 0;

		if ( m_nPlayIdx2 >= 10 )
			m_nPlayIdx2 = 0;
	}

	BYTE	bShadowType= 48;
	SHORT	shShadowPX = 0;
	SHORT	shShadowPY = 0;
	DWORD   dwHorseShadowFrame = 0;
	SHORT	shPX, shPY;
	BOOL	bPairDraw = FALSE;
	//---------------------------------------------------------------------------------------------------------------//
	// 각 이미지 세팅및 좌표영역 체크.
	//---------------------------------------------------------------------------------------------------------------//

	// 오성패
	// 찾았다! 지존패 by eriastoa 2006.04.25
	if ( (( m_bEftFeature & 128 ) >> 7 ) && ( m_nAmorEftIdx >= 500 && m_nAmorEftIdx <= 513 )  )
	{
		if ( m_bDrawOnce || m_nIdentity != g_xGameProc.m_xMyHero.m_nIdentity )
		{
			bPairDraw = TRUE;

			if ( g_dwCurrTime - m_dwAmorTimer > 80 )
			{
				m_dwAmorTimer = g_dwCurrTime;
				m_nAmorEftIdx++;

				if ( m_nAmorEftIdx > 540 )
					m_nAmorEftIdx = 500;
			}

			const POINT ptArr[] = 
			{
				{0, 20}, {8, 20}, {11, 12}, {7, 15}, {1, 10}, {-10, 15}, {-12, 10}, {-8, 18}
			};

			if ( g_xMainWnd.Get3DDevice() )
			{
				BOOL bIndexSetted	= FALSE;
				CWHWilImageData*	pxWilImg;

				LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_INTER, m_nAmorEftIdx);

				pxWilImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER];

				if ( pxWilImg->NewSetIndex(m_nAmorEftIdx) )
				{
					D3DVECTOR vTrans;
					D3DMATRIX matTrans;
					D3DMATRIX matScale;
					D3DMATRIX matWorld;
					D3DMATRIX matWorldOriginal;
					D3DMATERIAL7 mtrl;

					D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)255/255.0f, (FLOAT)255/255.0f);

					mtrl.diffuse.a = (FLOAT)(1)/255.0f;
					g_xMainWnd.Get3DDevice()->SetMaterial(&mtrl);

					if ( m_stFeatureEx.bHorse != _HORSE_NONE )
					{
 						vTrans.x = (FLOAT)m_nScrnPosX+(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth/2+pxWilImg->m_lpstNewCurrWilImageInfo->shPX-400+ptArr[m_bCurrDir].x; 
						vTrans.y = (FLOAT)-m_nScrnPosY-(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight/2-pxWilImg->m_lpstNewCurrWilImageInfo->shPY+300+ptArr[m_bCurrDir].y - 5; 
					}
					else
					{
 						vTrans.x = (FLOAT)m_nScrnPosX+(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth/2+pxWilImg->m_lpstNewCurrWilImageInfo->shPX-400; 
						vTrans.y = (FLOAT)-m_nScrnPosY-(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight/2-pxWilImg->m_lpstNewCurrWilImageInfo->shPY+300 - 5; 
					}
					vTrans.z = 0;

					if( SUCCEEDED(g_xMainWnd.Get3DDevice()->BeginScene()) )
					{
						g_xMainWnd.Get3DDevice()->GetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

						D3DUtil_SetTranslateMatrix(matTrans, vTrans);
						D3DUtil_SetScaleMatrix(matScale, (FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight, 1.0f);
						D3DMath_MatrixMultiply(matWorld, matScale, matTrans);
						g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);

						SetBlendRenderState(g_xMainWnd.Get3DDevice(), 2, &mtrl);

						g_xMainWnd.Get3DDevice()->SetTexture(0, lpddsTextr); 

						g_xMainWnd.Get3DDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_VERTEX, m_avBoard, 4, NULL);

						ResetBlendenderState(g_xMainWnd.Get3DDevice());

						g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

						g_xMainWnd.Get3DDevice()->EndScene();
					}
				}
			}
		}
	}

	// 말.
	if ( m_stFeatureEx.bHorse != _HORSE_NONE && m_pxHorseImage != NULL )
	{
		if ( m_bCurrMtn >= _START_HORSE_MTN )
		{
			m_dwCurrHorseFrame = (m_stFeatureEx.bHorse*_MAX_HORSE_FRAME-_MAX_HORSE_FRAME)+(m_dwCurrFrame-(_MAX_HERO_FRAME*m_stFeature.bDress)-_START_HORSE_FRAME);
			dwHorseShadowFrame = m_dwCurrHorseFrame % 400 + 10000;

			if ( !m_pxHorseImage->NewSetIndex(m_dwCurrHorseFrame) )
				return FALSE;
			shPX = m_pxHorseImage->m_lpstNewCurrWilImageInfo->shPX;
			shPY = m_pxHorseImage->m_lpstNewCurrWilImageInfo->shPY;
			SetRect(&m_rcHorse, m_nScrnPosX + shPX, m_nScrnPosY + shPY,
					m_nScrnPosX + shPX + m_pxHorseImage->m_lpstNewCurrWilImageInfo->shWidth, 
					m_nScrnPosX + shPY + m_pxHorseImage->m_lpstNewCurrWilImageInfo->shHeight);
		}
	} 

	// 무기.
	if ( m_stFeature.bWeapon != _WEAPON_NONE && m_pxWeaponImage != NULL )// && m_stFeature.bWeapon != 37 눈덩이 )
	{
		if ( m_bCurrMtn < _MAX_WEAPON_MTN )
		{
			if ( m_stFeature.bWeapon == 254 )
				m_dwCurrWeaponFrame = (((m_stFeature.bWeapon-2)%10)*_MAX_WEAPON_FRAME)+(m_dwCurrFrame-(_MAX_HERO_FRAME*m_stFeature.bDress));
			else
				m_dwCurrWeaponFrame = (((m_stFeature.bWeapon-1)%10)*_MAX_WEAPON_FRAME)+(m_dwCurrFrame-(_MAX_HERO_FRAME*m_stFeature.bDress));

			if ( !m_pxWeaponImage->NewSetIndex(m_dwCurrWeaponFrame) )
				return FALSE;

			shPX = m_pxWeaponImage->m_lpstNewCurrWilImageInfo->shPX;
			shPY = m_pxWeaponImage->m_lpstNewCurrWilImageInfo->shPY;
			SetRect(&m_rcWeapon, m_nScrnPosX + shPX, m_nScrnPosY + shPY, 
					m_nScrnPosX + shPX + m_pxWeaponImage->m_lpstNewCurrWilImageInfo->shWidth, 
					m_nScrnPosY + shPY + m_pxWeaponImage->m_lpstNewCurrWilImageInfo->shHeight);
		}
	}

	// 귀혼마갑
	if ( (m_bEftFeature & 64) >> 6 ) //이운교
	{
		if ( m_bDrawOnce || m_nIdentity != g_xGameProc.m_xMyHero.m_nIdentity )
		{
			INT	nImgIdx;

			// 귀혼마갑
			{
				if ( m_bJob == _JOB_JUNSA)
					nImgIdx = 2140 + m_nGhostAmorEftIdx;
				else if ( m_bJob == _JOB_SULSA)
					nImgIdx = 2160 + m_nGhostAmorEftIdx;
				else if ( m_bJob == _JOB_DOSA)
				{
					nImgIdx = 2180 + m_nGhostAmorEftIdx;
					INT ntest = 0;
				}
			}

			// 지연시간이 100ms 이다. 0.1초 by eriastoa 2006.04.20
			// 지정 시간이 경과하면 m_nGhostAmorEftIdx를 증가시켜서 다음 프레임의 이미지를 참조한다
			if ( g_dwCurrTime - m_dwGhostAmorTimer > 100 )
			{
				m_dwGhostAmorTimer = g_dwCurrTime;
				m_nGhostAmorEftIdx++;

				// 귀혼마갑
				{
					// 각 직업의 프레임 카운트 15, 12, 15
					if ( m_bJob == _JOB_JUNSA)
					{
						if ( m_nGhostAmorEftIdx > 15 )
							m_nGhostAmorEftIdx = 0;
					}
					else if ( m_bJob == _JOB_SULSA)
					{
						if ( m_nGhostAmorEftIdx > 12 )
							m_nGhostAmorEftIdx = 0;
					}
					else if ( m_bJob == _JOB_DOSA)
					{
						if ( m_nGhostAmorEftIdx > 15 )
							m_nGhostAmorEftIdx = 0;
					}
				}
			}

			// 말을 타고 있을 때 귀혼마갑 이펙트의 위치를 조정한다
			// 추가 by eriastoa 2006.05.02
			const POINT ptArr[] = 
			{
				{0, 20}, {8, 20}, {11, 12}, {7, 15}, {1, 10}, {-10, 15}, {-12, 10}, {-8, 18}
			};

			if ( g_xMainWnd.Get3DDevice() )
			{
				BOOL bIndexSetted	= FALSE;
				CWHWilImageData*	pxWilImg;

				LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_INTER, nImgIdx);

				pxWilImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER];

				if ( pxWilImg->NewSetIndex(nImgIdx) )
				{
					D3DVECTOR vTrans;
					D3DMATRIX matTrans;
					D3DMATRIX matScale;
					D3DMATRIX matWorld;
					D3DMATRIX matWorldOriginal;
					D3DMATERIAL7 mtrl;

					D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)255/255.0f, (FLOAT)255/255.0f);

					mtrl.diffuse.a = (FLOAT)(1)/255.0f;
					g_xMainWnd.Get3DDevice()->SetMaterial(&mtrl);

					// 말을 타고 있을 때 귀혼마갑 이펙트의 위치를 조정한다
					// 추가 by eriastoa 2006.05.02
					if ( m_stFeatureEx.bHorse != _HORSE_NONE )
					{
 						vTrans.x = (FLOAT)m_nScrnPosX+(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth/2+pxWilImg->m_lpstNewCurrWilImageInfo->shPX-400+ptArr[m_bCurrDir].x; 
						vTrans.y = (FLOAT)-m_nScrnPosY-(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight/2-pxWilImg->m_lpstNewCurrWilImageInfo->shPY+300+ptArr[m_bCurrDir].y; 
					}
					else
					{
 						vTrans.x = (FLOAT)m_nScrnPosX+(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth/2+pxWilImg->m_lpstNewCurrWilImageInfo->shPX-400; 
						vTrans.y = (FLOAT)-m_nScrnPosY-(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight/2-pxWilImg->m_lpstNewCurrWilImageInfo->shPY+300; 
					}
					
					vTrans.z = 0;

					if( SUCCEEDED(g_xMainWnd.Get3DDevice()->BeginScene()) )
					{
						g_xMainWnd.Get3DDevice()->GetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

						D3DUtil_SetTranslateMatrix(matTrans, vTrans);
						D3DUtil_SetScaleMatrix(matScale, (FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight, 1.0f);
						D3DMath_MatrixMultiply(matWorld, matScale, matTrans);
						g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);

						SetBlendRenderState(g_xMainWnd.Get3DDevice(), 2, &mtrl);

						g_xMainWnd.Get3DDevice()->SetTexture(0, lpddsTextr); 

						g_xMainWnd.Get3DDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_VERTEX, m_avBoard, 4, NULL);

						ResetBlendenderState(g_xMainWnd.Get3DDevice());

						g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

						g_xMainWnd.Get3DDevice()->EndScene();
					}
				}
			}
			if ( bPairDraw )
				m_bDrawOnce = FALSE;

			bPairDraw = TRUE;

		}

		INT nRed1, nGreen1, nBlue1;
		INT nRed2, nGreen2, nBlue2;

		if ( m_bJob == _JOB_JUNSA)
		{
			nRed1 = 190;
			nGreen1 = 250; 
			nBlue1 = 170;
			nRed2 = 100;
			nGreen2 = 200;
			nBlue2 = 100;
		}
		else if ( m_bJob == _JOB_SULSA)
		{
			nRed1 = 250;
			nGreen1 = 100; 
			nBlue1 = 100;
			nRed2 = 200;
			nGreen2 = 50;
			nBlue2 = 30;
		}
		else if ( m_bJob == _JOB_DOSA)
		{
			nRed1 = 80;
			nGreen1 = 80; 
			nBlue1 = 250;
			nRed2 = 50;
			nGreen2 = 30;
			nBlue2 = 230;
		}

		g_xGameProc.m_xLightFog.SetLightRadiusWithRing(
										  m_nScrnPosX + _CELL_WIDTH/2,
							  			  m_nScrnPosY - _CELL_HEIGHT/2, 
										  2, nBlue1, nGreen1, nRed1, 
										  3, nBlue2, nGreen2, nRed2);
	}
	// 캐릭터 그리기
	if ( m_pxActorImage )
	{
#ifdef _TEST_SERVER		// by eriastoa 2006.05.29
		if ( m_nEft == 1 )
		{
			if( m_pxDragonImage && m_pxDragonImage->NewSetIndex(m_dwCurrFrame) )
			{
				shPX = m_pxDragonImage->m_lpstNewCurrWilImageInfo->shPX;
				shPY = m_pxDragonImage->m_lpstNewCurrWilImageInfo->shPY;
				
				SetRect(&m_rcDragon, m_nScrnPosX + shPX, m_nScrnPosY + shPY, 
					m_nScrnPosX + shPX + m_pxDragonImage->m_lpstNewCurrWilImageInfo->shWidth, 
					m_nScrnPosY + shPY + m_pxDragonImage->m_lpstNewCurrWilImageInfo->shHeight);
			}
		}
#endif
		
		// 케릭터를 그리기 위한 좌표를 설정하는 곳
		if ( !m_pxActorImage->NewSetIndex(m_dwCurrFrame) )
			return FALSE;
		shPX = m_pxActorImage->m_lpstNewCurrWilImageInfo->shPX;
		shPY = m_pxActorImage->m_lpstNewCurrWilImageInfo->shPY;
		bShadowType = m_pxActorImage->m_lpstNewCurrWilImageInfo->bShadow;
		shShadowPX  = m_pxActorImage->m_lpstNewCurrWilImageInfo->shShadowPX;
		shShadowPY  = m_pxActorImage->m_lpstNewCurrWilImageInfo->shShadowPY;

		SetRect(&m_rcActor, m_nScrnPosX + shPX, m_nScrnPosY + shPY, 
				m_nScrnPosX + shPX + m_pxActorImage->m_lpstNewCurrWilImageInfo->shWidth, 
				m_nScrnPosY + shPY + m_pxActorImage->m_lpstNewCurrWilImageInfo->shHeight);

		if ( ( m_rcActor.right - m_rcActor.left ) > _CELL_WIDTH + _TARGETRGN_GAPX )
		{
			m_rcTargetRgn.left  = m_rcActor.left + ( (m_rcActor.right - m_rcActor.left) - (_CELL_WIDTH + _TARGETRGN_GAPX) )/2;
			m_rcTargetRgn.right = m_rcActor.left + ( (m_rcActor.right - m_rcActor.left) + (_CELL_WIDTH + _TARGETRGN_GAPX) )/2;
		}
		else
		{
			m_rcTargetRgn.left  = m_rcActor.left;
			m_rcTargetRgn.right = m_rcActor.right;
		}

		if ( ( m_rcActor.bottom - m_rcActor.top ) > _CELL_HEIGHT + _TARGETRGN_GAPY )
		{
			m_rcTargetRgn.top    = m_rcActor.top + ( (m_rcActor.bottom - m_rcActor.top) - (_CELL_HEIGHT + _TARGETRGN_GAPY) )/2;
			m_rcTargetRgn.bottom = m_rcActor.top + ( (m_rcActor.bottom - m_rcActor.top) + (_CELL_HEIGHT + _TARGETRGN_GAPY) )/2;
		}
		else
		{
			m_rcTargetRgn.top    = m_rcActor.top;
			m_rcTargetRgn.bottom = m_rcActor.bottom;
		}
	}

	// 머리.
	if ( m_stFeature.bHair != _HAIR_NONE && m_pxHairImage != NULL )
	{
		m_dwCurrHairFrame = ((m_stFeature.bHair-1)%10*_MAX_HERO_FRAME)+(m_dwCurrFrame-(_MAX_HERO_FRAME*m_stFeature.bDress));

		if ( !m_pxHairImage->NewSetIndex(m_dwCurrHairFrame) )
			return FALSE;
		shPX = m_pxHairImage->m_lpstNewCurrWilImageInfo->shPX;
		shPY = m_pxHairImage->m_lpstNewCurrWilImageInfo->shPY;
		SetRect(&m_rcHair, m_nScrnPosX + shPX, m_nScrnPosY + shPY, 
					m_nScrnPosX + shPX + m_pxHairImage->m_lpstNewCurrWilImageInfo->shWidth, 
					m_nScrnPosY + shPY + m_pxHairImage->m_lpstNewCurrWilImageInfo->shHeight);
	}

	//---------------------------------------------------------------------------------------------------------------//
	// 그림자그리기.
	//---------------------------------------------------------------------------------------------------------------//
	BYTE bOpaRate = 13;
	WORD wState   = GetCharState();

	if ( m_nABlendDelay || wState==_STATE_ABLEND )
	{
		bShadowAblended = TRUE;
	}

	// 무기.
	if ( m_stFeature.bWeapon != _WEAPON_NONE && m_pxWeaponImage != NULL && m_bCurrMtn != _MT_CUT && m_stFeature.bWeapon != 37 /*눈덩이*/ )
	{
		if ( m_bCurrMtn < _MAX_WEAPON_MTN )
		{
			if ( bDrawShadow )
			{
				if ( !m_bIsDead )
				{
					g_xMainWnd.DrawWithShadowABlend(
									m_rcWeapon.left, m_rcWeapon.top,
									m_pxWeaponImage->m_lpstNewCurrWilImageInfo->shWidth,
									m_pxWeaponImage->m_lpstNewCurrWilImageInfo->shHeight,
									m_pxWeaponImage->m_lpstNewCurrWilImageInfo->shPX,
									m_pxWeaponImage->m_lpstNewCurrWilImageInfo->shPY,
									(WORD*)m_pxWeaponImage->m_pbCurrImage, 						
									_CLIP_WIDTH, _CLIP_HEIGHT, g_xGameProc.m_wShadowClr, bShadowAblended, bOpaRate);
				}
			}
		}
	}

	// 말.
	if ( m_stFeatureEx.bHorse != _HORSE_NONE && m_pxHorseImage != NULL )
	{
		if ( m_bCurrMtn >= _START_HORSE_MTN )
		{
			if ( bDrawShadow )
			{
				CWHWilImageData* pxSahdowImage;

				pxSahdowImage = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_SHORSE];

				if ( pxSahdowImage->NewSetIndex(m_dwCurrHorseFrame) )
				{
					SHORT shShadowPX, shShadowPY;
					if ( m_nABlendDelay || wState==_STATE_ABLEND || bShadowAblended )
					{
						shShadowPX = pxSahdowImage->m_lpstNewCurrWilImageInfo->shPX;
						shShadowPY = pxSahdowImage->m_lpstNewCurrWilImageInfo->shPY;

						g_xMainWnd.DrawWithABlendCompDataWithBackBufferEx(m_nScrnPosX+shShadowPX, m_nScrnPosY+shShadowPY, pxSahdowImage->m_lpstNewCurrWilImageInfo->shWidth,	pxSahdowImage->m_lpstNewCurrWilImageInfo->shHeight, (WORD*)pxSahdowImage->m_pbCurrImage,
																		  _CLIP_WIDTH, _CLIP_HEIGHT, 0XFFFF, 0XFFFF, bOpaRate);
					}
					else
					{
						shShadowPX = pxSahdowImage->m_lpstNewCurrWilImageInfo->shPX;
						shShadowPY = pxSahdowImage->m_lpstNewCurrWilImageInfo->shPY;
						
						g_xMainWnd.DrawWithImageForCompClipRgn(m_nScrnPosX+shShadowPX, m_nScrnPosY+shShadowPY, pxSahdowImage->m_lpstNewCurrWilImageInfo->shWidth,	pxSahdowImage->m_lpstNewCurrWilImageInfo->shHeight, (WORD*)pxSahdowImage->m_pbCurrImage,
															   _CLIP_WIDTH, _CLIP_HEIGHT, 0XFFFF, 0XFFFF, bFocused);
					}
				}
/*
				if ( m_pxHorseImage->NewSetIndex(dwHorseShadowFrame) )
				{
					SHORT shShadowPX, shShadowPY;
					if ( bShadowAblended )
					{
						shShadowPX = m_pxHorseImage->m_lpstNewCurrWilImageInfo->shPX;
						shShadowPY = m_pxHorseImage->m_lpstNewCurrWilImageInfo->shPY;

						g_xMainWnd.DrawWithABlendCompDataWithBackBufferEx(m_nScrnPosX+shShadowPX, m_nScrnPosY+shShadowPY, m_pxHorseImage->m_lpstNewCurrWilImageInfo->shWidth,	m_pxHorseImage->m_lpstNewCurrWilImageInfo->shHeight, (WORD*)m_pxHorseImage->m_pbCurrImage,
																		  _CLIP_WIDTH, _CLIP_HEIGHT, 0XFFFF, 0XFFFF, bOpaRate);
					}
					else
					{
						shShadowPX = m_pxHorseImage->m_lpstNewCurrWilImageInfo->shPX;
						shShadowPY = m_pxHorseImage->m_lpstNewCurrWilImageInfo->shPY;
						
						g_xMainWnd.DrawWithImageForCompClipRgn(m_nScrnPosX+shShadowPX, m_nScrnPosY+shShadowPY, m_pxHorseImage->m_lpstNewCurrWilImageInfo->shWidth,	m_pxHorseImage->m_lpstNewCurrWilImageInfo->shHeight, (WORD*)m_pxHorseImage->m_pbCurrImage,
															   _CLIP_WIDTH, _CLIP_HEIGHT, 0XFFFF, 0XFFFF, bFocused);
					}
				}

				if ( !m_pxHorseImage->NewSetIndex(m_dwCurrHorseFrame) )
					return FALSE;
*/
			}
		}
	}

	// 캐릭터 그림자
	if ( m_pxActorImage )
	{
		INT nStartX1 = m_nScrnPosX + shShadowPX;
		INT nStartY1 = m_nScrnPosY + shShadowPY;

		if ( bDrawShadow )
		{
			if ( !m_bIsDead )
			{
				g_xMainWnd.DrawWithShadowABlend(
									nStartX1, nStartY1,
									m_pxActorImage->m_lpstNewCurrWilImageInfo->shWidth,
									m_pxActorImage->m_lpstNewCurrWilImageInfo->shHeight,
									(WORD*)m_pxActorImage->m_pbCurrImage,
									_CLIP_WIDTH, _CLIP_HEIGHT, g_xGameProc.m_wShadowClr, bShadowAblended, bShadowType, bOpaRate);
			}
			else
			{
				g_xMainWnd.DrawWithShadowABlend(
									m_rcActor.left+3, m_rcActor.top+2,
									m_pxActorImage->m_lpstNewCurrWilImageInfo->shWidth,
									m_pxActorImage->m_lpstNewCurrWilImageInfo->shHeight,
									(WORD*)m_pxActorImage->m_pbCurrImage,
									_CLIP_WIDTH, _CLIP_HEIGHT, g_xGameProc.m_wShadowClr, bShadowAblended, 50, bOpaRate);
			}
		}
	}

	// 머리는 그림자를 그리지 않는다.
	if ( m_nABlendDelay > 0 )		
	{
		bShadowAblended = TRUE;

		if ( m_nABlendDelay )	
		{
			if ( m_bABlendRev )
				bOpaRate = (BYTE)(31 - ( (m_nABlendCurrDelay * 31) / m_nABlendDelay ));
			else
				bOpaRate = (BYTE)( (m_nABlendCurrDelay * 31) / m_nABlendDelay );
		}

		if ( bFocused )								
		{
			if ( m_bABlendRev )
				bOpaRate -= 5;
			else
				bOpaRate += 5;
		}

		if ( bOpaRate < 0 || bOpaRate > 31 )		bOpaRate  = 0;
	}
	else if ( wState == _STATE_ABLEND )			bShadowAblended = TRUE;


	// 이펙트 그리는 위치를 조정한다
	// by eriatoa 2006.05.30
	BOOL m_bDrawHorse = FALSE;
	//---------------------------------------------------------------------------------------------------------------//
	// 이미지 그리기.
	//---------------------------------------------------------------------------------------------------------------//
	// 말.
	if ( m_stFeatureEx.bHorse != _HORSE_NONE && m_pxHorseImage != NULL && m_bCurrDir != 4 )
	{
		if ( m_bCurrMtn >= _START_HORSE_MTN )
		{			
			DrawWithEffected(m_rcHorse.left, m_rcHorse.top, m_pxHorseImage->m_lpstNewCurrWilImageInfo->shWidth, m_pxHorseImage->m_lpstNewCurrWilImageInfo->shHeight, (WORD*)m_pxHorseImage->m_pbCurrImage, 
				             0XFFFF, 0XFFFF, bFocused, bOpaRate, wState);

			m_bDrawHorse = TRUE;
		}
	}

	// 0000 0000 0000 0000 0000 0000 0000 0001 적룡신갑
	// 0000 0000 0000 0000 0000 0000 0000 0010 적관마의
	// 0000 0000 0000 0000 0000 0000 0000 0100 명광봉의
	// 0000 0000 0000 0000 0000 0000 0000 1000 용린보갑
#ifdef _TEST_SERVER		// by eriastoa 2006.05.29
	BOOL	bEftDraw		= FALSE;
	INT		nStartIdx		= 0;

	if( m_nEft == 8 )
	{
		bEftDraw = TRUE;
		nStartIdx = 2300;
	}
	else if( m_nEft == 4 )
	{
		bEftDraw = TRUE;
		nStartIdx = 2500;
	}
	else if( m_nEft == 2 )
	{
		bEftDraw = TRUE;
		nStartIdx = 2700;
	}
	
	if( bEftDraw )
	{
		// 아랫쪽방향으로 보고 있을 때 이펙트를 먼저에 찍어야 된다, 용린보갑 등~
		// by eriastoa 2006.05.09
		if( m_bCurrDir != 7 && m_bCurrDir != 0 && m_bCurrDir != 1 )
		{
			
			if ( m_bDrawOnce || m_nIdentity != g_xGameProc.m_xMyHero.m_nIdentity )
			{
				INT	nImgIdx;
				
				// 용린보갑
				nImgIdx = nStartIdx + m_bCurrDir * 20 + m_nGhostAmorEftIdx;
				
				// 지연시간이 100ms 이다. 0.1초 by eriastoa 2006.04.20
				// 지정 시간이 경과하면 m_nGhostAmorEftIdx를 증가시켜서 다음 프레임의 이미지를 참조한다
				if ( g_dwCurrTime - m_dwGhostAmorTimer > 100 )
				{
					m_dwGhostAmorTimer = g_dwCurrTime;
					m_nGhostAmorEftIdx++;
					
					if ( m_nGhostAmorEftIdx > 14)
						m_nGhostAmorEftIdx = 0;
				}
				
				const POINT ptArr[] = 
				{
					{0, 20}, {8, 20}, {11, 12}, {7, 15}, {1, 10}, {-10, 15}, {-12, 10}, {-8, 18}
				};
				
				if ( g_xMainWnd.Get3DDevice() )
				{
					BOOL bIndexSetted	= FALSE;
					CWHWilImageData*	pxWilImg;
					
					LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_INTER, nImgIdx);
					
					pxWilImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER];
					
					if ( pxWilImg->NewSetIndex(nImgIdx) )
					{
						D3DVECTOR vTrans;
						D3DMATRIX matTrans;
						D3DMATRIX matScale;
						D3DMATRIX matWorld;
						D3DMATRIX matWorldOriginal;
						D3DMATERIAL7 mtrl;
						
						D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)255/255.0f, (FLOAT)255/255.0f);
						
						mtrl.diffuse.a = (FLOAT)(1)/255.0f;
						g_xMainWnd.Get3DDevice()->SetMaterial(&mtrl);
						
						if ( m_stFeatureEx.bHorse != _HORSE_NONE )
						{
							vTrans.x = (FLOAT)m_nScrnPosX+(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth/2+pxWilImg->m_lpstNewCurrWilImageInfo->shPX-400+ptArr[m_bCurrDir].x; 
							vTrans.y = (FLOAT)-m_nScrnPosY-(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight/2-pxWilImg->m_lpstNewCurrWilImageInfo->shPY+300+ptArr[m_bCurrDir].y; 
						}
						else
						{
							vTrans.x = (FLOAT)m_nScrnPosX+(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth/2+pxWilImg->m_lpstNewCurrWilImageInfo->shPX-400; 
							vTrans.y = (FLOAT)-m_nScrnPosY-(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight/2-pxWilImg->m_lpstNewCurrWilImageInfo->shPY+300; 
						}
						
						vTrans.z = 0;
						
						if( SUCCEEDED(g_xMainWnd.Get3DDevice()->BeginScene()) )
						{
							g_xMainWnd.Get3DDevice()->GetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);
							
							D3DUtil_SetTranslateMatrix(matTrans, vTrans);
							D3DUtil_SetScaleMatrix(matScale, (FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight, 1.0f);
							D3DMath_MatrixMultiply(matWorld, matScale, matTrans);
							g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);
							
							SetBlendRenderState(g_xMainWnd.Get3DDevice(), 2, &mtrl);
							
							g_xMainWnd.Get3DDevice()->SetTexture(0, lpddsTextr); 
							
							g_xMainWnd.Get3DDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_VERTEX, m_avBoard, 4, NULL);
							
							ResetBlendenderState(g_xMainWnd.Get3DDevice());
							
							g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);
							
							g_xMainWnd.Get3DDevice()->EndScene();
						}
					}
				}
				if ( bPairDraw )
					m_bDrawOnce = FALSE;
				
				bPairDraw = TRUE;
				
			}
		}
	}
#endif

	// 말.
	if ( m_stFeatureEx.bHorse != _HORSE_NONE && m_pxHorseImage != NULL && ! m_bDrawHorse )
	{
		if ( m_bCurrMtn >= _START_HORSE_MTN )
		{			
			DrawWithEffected(m_rcHorse.left, m_rcHorse.top, m_pxHorseImage->m_lpstNewCurrWilImageInfo->shWidth, m_pxHorseImage->m_lpstNewCurrWilImageInfo->shHeight, (WORD*)m_pxHorseImage->m_pbCurrImage, 
				             0XFFFF, 0XFFFF, bFocused, bOpaRate, wState);
		}
	}

	/*if ( 0 && ( m_bCurrDir == 3 || m_bCurrDir == 4 || m_bCurrDir == 5 ) )// 도사 갑옷 이펙트
	{
		if ( m_bDrawOnce || m_nIdentity != g_xGameProc.m_xMyHero.m_nIdentity )
		{
			if ( g_dwCurrTime - m_dwFAEftTimer > 80 )
			{
				m_dwFAEftTimer = g_dwCurrTime;
				m_nFAEftIdx++;

				if ( m_nFAEftIdx > 14 )
					m_nFAEftIdx = 0;
			}

			INT nFrame = m_bCurrDir*20 + m_nFAEftIdx;

			if ( m_bEftFeature == 10 )
				nFrame+= 110;
			else if ( m_bEftFeature == 11 )
				nFrame+= 310;
			else if ( m_bEftFeature == 9 )
				nFrame+= 510;

			const POINT ptArr[] = 
			{
				{0, 20}, {8, 20}, {11, 12}, {7, 15}, {1, 10}, {-10, 15}, {-12, 10}, {-8, 18}
			};

			if ( g_xMainWnd.Get3DDevice() )
			{
				BOOL bIndexSetted	= FALSE;
				CWHWilImageData*	pxWilImg;

				LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_FAEFFECT, nFrame);

				pxWilImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_FAEFFECT];

				if ( pxWilImg->NewSetIndex(nFrame) )
				{
					D3DVECTOR vTrans;
					D3DMATRIX matTrans;
					D3DMATRIX matScale;
					D3DMATRIX matWorld;
					D3DMATRIX matWorldOriginal;
					D3DMATERIAL7 mtrl;

					D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)255/255.0f, (FLOAT)255/255.0f);

					mtrl.diffuse.a = (FLOAT)(1)/255.0f;
					g_xMainWnd.Get3DDevice()->SetMaterial(&mtrl);

					if ( m_stFeatureEx.bHorse != _HORSE_NONE )
					{
 						vTrans.x = (FLOAT)m_nScrnPosX+(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth/2+pxWilImg->m_lpstNewCurrWilImageInfo->shPX-400+ptArr[m_bCurrDir].x; 
						vTrans.y = (FLOAT)-m_nScrnPosY-(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight/2-pxWilImg->m_lpstNewCurrWilImageInfo->shPY+300+ptArr[m_bCurrDir].y; 
					}
					else
					{
 						vTrans.x = (FLOAT)m_nScrnPosX+(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth/2+pxWilImg->m_lpstNewCurrWilImageInfo->shPX-400; 
						vTrans.y = (FLOAT)-m_nScrnPosY-(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight/2-pxWilImg->m_lpstNewCurrWilImageInfo->shPY+300; 
					}

					vTrans.z = 0;

					if( SUCCEEDED(g_xMainWnd.Get3DDevice()->BeginScene()) )
					{
						g_xMainWnd.Get3DDevice()->GetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

						D3DUtil_SetTranslateMatrix(matTrans, vTrans);
						D3DUtil_SetScaleMatrix(matScale, (FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight, 1.0f);
						D3DMath_MatrixMultiply(matWorld, matScale, matTrans);
						g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);

						SetBlendRenderState(g_xMainWnd.Get3DDevice(), 2, &mtrl);

						g_xMainWnd.Get3DDevice()->SetTexture(0, lpddsTextr); 

						g_xMainWnd.Get3DDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_VERTEX, m_avBoard, 4, NULL);

						ResetBlendenderState(g_xMainWnd.Get3DDevice());

						g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

						g_xMainWnd.Get3DDevice()->EndScene();
					}
				}
			}
		}
	}*/

	// 무기를 먼저 그려야될방향.
	if ( m_stFeature.bWeapon != _WEAPON_NONE && m_pxWeaponImage != NULL && g_xSpriteInfo.m_bWOrder[(m_dwCurrFrame-(_MAX_HERO_FRAME*m_stFeature.bDress))] && m_stFeature.bWeapon != 37 /*눈덩이*/ )
	{
		if ( m_bCurrMtn < _MAX_WEAPON_MTN )
		{
			WORD wColor = FindWeaponColor(m_stFeatureEx.bWeaponColor);
			DrawWithEffected(m_rcWeapon.left, m_rcWeapon.top, m_pxWeaponImage->m_lpstNewCurrWilImageInfo->shWidth, m_pxWeaponImage->m_lpstNewCurrWilImageInfo->shHeight, (WORD*)m_pxWeaponImage->m_pbCurrImage,
							 wColor, 0XFFFF, bFocused, 10, wState);

			if ( m_stFeature.bWeapon == 254 )			// 절대검
			{
				INT nTemp, nCurEffectFrame;
				if ( m_stFeature.bGender == _GENDER_MAN )
				{
					nTemp = m_dwCurrFrame - m_stFeature.bDress*_MAX_HERO_FRAME;
					nCurEffectFrame = 1900 + nTemp;
				}
				else
				{
					nTemp = m_dwCurrFrame - m_stFeature.bDress*_MAX_HERO_FRAME;
					nCurEffectFrame = 3900 + nTemp;
				}
				DrawTheSwordEffect(nCurEffectFrame);
			}
		}
	}

#ifdef _TEST_SERVER		// by eriastoa 2006.05.29
	if( m_bCurrDir == 3 || m_bCurrDir == 4 || m_bCurrDir == 5 )
	{
		if( m_nEft == 1 )
		{
			if( m_pxDragonImage )
				DrawTheAomorEffect( m_dwCurrFrame );
		}
	}
#endif


	// 캐릭터.
	if ( m_pxActorImage != NULL )
	{
		DrawWithEffected(m_rcActor.left, m_rcActor.top, m_pxActorImage->m_lpstNewCurrWilImageInfo->shWidth, m_pxActorImage->m_lpstNewCurrWilImageInfo->shHeight, (WORD*)m_pxActorImage->m_pbCurrImage,
						 m_stFeatureEx.wDressColor, 0XFFFF, bFocused, bOpaRate, wState);
	}

	// 머리.
 	if ( m_stFeature.bHair != _HAIR_NONE && m_pxHairImage != NULL )
	{
		WORD wHairClr = m_stFeatureEx.wHairColor;

		// 투구.
		if ( m_stFeature.bHair > 10 )
		{
			wHairClr = 0XFFFF;
		}

		DrawWithEffected(m_rcHair.left, m_rcHair.top, m_pxHairImage->m_lpstNewCurrWilImageInfo->shWidth, m_pxHairImage->m_lpstNewCurrWilImageInfo->shHeight, (WORD*)m_pxHairImage->m_pbCurrImage, 
				         wHairClr, 0XFFFF, bFocused, 20, wState);
	}			

	// 무기를 나중에 그려야될 방향.
	if ( m_stFeature.bWeapon != _WEAPON_NONE && m_pxWeaponImage != NULL && !g_xSpriteInfo.m_bWOrder[(m_dwCurrFrame-(_MAX_HERO_FRAME*m_stFeature.bDress))] && m_stFeature.bWeapon != 37 /*눈덩이*/ ) 
	{
		if ( m_bCurrMtn < _MAX_WEAPON_MTN )
		{	
			WORD wColor = FindWeaponColor(m_stFeatureEx.bWeaponColor);
 			DrawWithEffected(m_rcWeapon.left, m_rcWeapon.top, m_pxWeaponImage->m_lpstNewCurrWilImageInfo->shWidth, m_pxWeaponImage->m_lpstNewCurrWilImageInfo->shHeight, (WORD*)m_pxWeaponImage->m_pbCurrImage,
							 wColor, 0XFFFF, bFocused, /*bOpaRate*/22, wState);

			if ( m_stFeature.bWeapon == 254 )			// 절대검
			{
				INT nTemp, nCurEffectFrame;
				if ( m_stFeature.bGender == _GENDER_MAN )
				{
					nTemp = m_dwCurrFrame - m_stFeature.bDress*_MAX_HERO_FRAME;
					nCurEffectFrame = 1900 + nTemp;
				}
				else
				{
					nTemp = m_dwCurrFrame - m_stFeature.bDress*_MAX_HERO_FRAME;
					nCurEffectFrame = 3900 + nTemp;
				}

				DrawTheSwordEffect(nCurEffectFrame);
			}
		}
	}

	if ( m_bIsSturn )
	{
		DWORD dwCur = timeGetTime();
		if ( dwCur - m_dwSturnTimer > 150 )
		{
			m_dwSturnTimer = dwCur;
			m_nStrurnFrame++;

			if ( m_nStrurnFrame > 685 )
				m_nStrurnFrame = 680;
		}

		INT nX = m_nScrnPosX+7;
		INT	nY = m_nScrnPosY-60;

		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].NewSetIndex(m_nStrurnFrame) )
		{
 			g_xMainWnd.DrawWithImageForComp(
							nX,
							nY,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shWidth,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shHeight,
							(WORD*)g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_pbCurrImage);

		}
	}

	
#ifdef _TEST_SERVER		// by eriastoa 2006.05.29
	if( m_bCurrDir != 3 || m_bCurrDir != 4 || m_bCurrDir != 5 )
	{
		if( m_nEft == 1 )
		{
			if( m_pxDragonImage )
				DrawTheAomorEffect( m_dwCurrFrame );
		}
	}

	// 임시로 테스트 해본다 by eriastoa 2006.05.09
	// 1000 0000 용린보갑
	// 0100 0000 명광봉의
	// 0010 0000 적관마의
	// 0001 0000 적룡신갑
	if( bEftDraw )
	{
		// 윗쪽방향으로 보고 있을 때 이펙트를 나중에 찍어야 된다, 용린보갑 등~	
		// by eriastoa 2006.05.09
		if( m_bCurrDir == 7 || m_bCurrDir == 0 || m_bCurrDir == 1 )
		{			
			if ( m_bDrawOnce || m_nIdentity != g_xGameProc.m_xMyHero.m_nIdentity )
			{
				INT	nImgIdx;
				
				// 용린보갑
				nImgIdx = nStartIdx + m_bCurrDir * 20 + m_nGhostAmorEftIdx;
				
				// 지연시간이 100ms 이다. 0.1초 by eriastoa 2006.04.20
				// 지정 시간이 경과하면 m_nGhostAmorEftIdx를 증가시켜서 다음 프레임의 이미지를 참조한다
				if ( g_dwCurrTime - m_dwGhostAmorTimer > 100 )
				{
					m_dwGhostAmorTimer = g_dwCurrTime;
					m_nGhostAmorEftIdx++;
					
					if ( m_nGhostAmorEftIdx > 14)
						m_nGhostAmorEftIdx = 0;
				}
				
				const POINT ptArr[] = 
				{
					{0, 20}, {8, 20}, {11, 12}, {7, 15}, {1, 10}, {-10, 15}, {-12, 10}, {-8, 18}
				};
				
				if ( g_xMainWnd.Get3DDevice() )
				{
					BOOL bIndexSetted	= FALSE;
					CWHWilImageData*	pxWilImg;
					
					LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_INTER, nImgIdx);
					
					pxWilImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER];
					
					if ( pxWilImg->NewSetIndex(nImgIdx) )
					{
						D3DVECTOR vTrans;
						D3DMATRIX matTrans;
						D3DMATRIX matScale;
						D3DMATRIX matWorld;
						D3DMATRIX matWorldOriginal;
						D3DMATERIAL7 mtrl;
						
						D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)255/255.0f, (FLOAT)255/255.0f);
						
						mtrl.diffuse.a = (FLOAT)(1)/255.0f;
						g_xMainWnd.Get3DDevice()->SetMaterial(&mtrl);
						
						if ( m_stFeatureEx.bHorse != _HORSE_NONE )
						{
							vTrans.x = (FLOAT)m_nScrnPosX+(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth/2+pxWilImg->m_lpstNewCurrWilImageInfo->shPX-400+ptArr[m_bCurrDir].x; 
							vTrans.y = (FLOAT)-m_nScrnPosY-(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight/2-pxWilImg->m_lpstNewCurrWilImageInfo->shPY+300+ptArr[m_bCurrDir].y; 
						}
						else
						{
							vTrans.x = (FLOAT)m_nScrnPosX+(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth/2+pxWilImg->m_lpstNewCurrWilImageInfo->shPX-400; 
							vTrans.y = (FLOAT)-m_nScrnPosY-(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight/2-pxWilImg->m_lpstNewCurrWilImageInfo->shPY+300; 
						}
						
						vTrans.z = 0;
						
						if( SUCCEEDED(g_xMainWnd.Get3DDevice()->BeginScene()) )
						{
							g_xMainWnd.Get3DDevice()->GetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);
							
							D3DUtil_SetTranslateMatrix(matTrans, vTrans);
							D3DUtil_SetScaleMatrix(matScale, (FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight, 1.0f);
							D3DMath_MatrixMultiply(matWorld, matScale, matTrans);
							g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);
							
							SetBlendRenderState(g_xMainWnd.Get3DDevice(), 2, &mtrl);
							
							g_xMainWnd.Get3DDevice()->SetTexture(0, lpddsTextr); 
							
							g_xMainWnd.Get3DDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_VERTEX, m_avBoard, 4, NULL);
							
							ResetBlendenderState(g_xMainWnd.Get3DDevice());
							
							g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);
							
							g_xMainWnd.Get3DDevice()->EndScene();
						}
					}
				}
				if ( bPairDraw )
					m_bDrawOnce = FALSE;
				
				bPairDraw = TRUE;
				
			}
		}
	}
#endif
	
/*
	if ( !m_bEftFeature 
		&& ( m_bCurrDir == 0 || m_bCurrDir == 1 || m_bCurrDir == 2 || m_bCurrDir== 6 || m_bCurrDir == 7) )// 도사 갑옷 이펙트
	{
		if ( m_bDrawOnce || m_nIdentity != g_xGameProc.m_xMyHero.m_nIdentity )
		{
			if ( g_dwCurrTime - m_dwFAEftTimer > 80 )
			{
				m_dwFAEftTimer = g_dwCurrTime;
				m_nFAEftIdx++;

				if ( m_nFAEftIdx > 14 )
					m_nFAEftIdx = 0;
			}

			INT nFrame = m_bCurrDir*20 + m_nFAEftIdx;

			if ( m_bEftFeature == 10 )
				nFrame+= 110;
			else if ( m_bEftFeature == 11 )
				nFrame+= 310;
			else if ( m_bEftFeature == 9 )
				nFrame+= 510;

			const POINT ptArr[] = 
			{
				{0, 20}, {8, 20}, {11, 12}, {7, 15}, {1, 10}, {-10, 15}, {-12, 10}, {-8, 18}
			};

			if ( g_xMainWnd.Get3DDevice() )
			{
				BOOL bIndexSetted	= FALSE;
				CWHWilImageData*	pxWilImg;

				LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_FAEFFECT, nFrame);

				pxWilImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_FAEFFECT];

				if ( pxWilImg->NewSetIndex(nFrame) )
				{
					D3DVECTOR vTrans;
					D3DMATRIX matTrans;
					D3DMATRIX matScale;
					D3DMATRIX matWorld;
					D3DMATRIX matWorldOriginal;
					D3DMATERIAL7 mtrl;

					D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)255/255.0f, (FLOAT)255/255.0f);

					mtrl.diffuse.a = (FLOAT)(1)/255.0f;
					g_xMainWnd.Get3DDevice()->SetMaterial(&mtrl);

					if ( m_stFeatureEx.bHorse != _HORSE_NONE )
					{
 						vTrans.x = (FLOAT)m_nScrnPosX+(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth/2+pxWilImg->m_lpstNewCurrWilImageInfo->shPX-400+ptArr[m_bCurrDir].x; 
						vTrans.y = (FLOAT)-m_nScrnPosY-(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight/2-pxWilImg->m_lpstNewCurrWilImageInfo->shPY+300+ptArr[m_bCurrDir].y; 
					}
					else
					{
 						vTrans.x = (FLOAT)m_nScrnPosX+(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth/2+pxWilImg->m_lpstNewCurrWilImageInfo->shPX-400; 
						vTrans.y = (FLOAT)-m_nScrnPosY-(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight/2-pxWilImg->m_lpstNewCurrWilImageInfo->shPY+300; 
					}
					vTrans.z = 0;

					if( SUCCEEDED(g_xMainWnd.Get3DDevice()->BeginScene()) )
					{
						g_xMainWnd.Get3DDevice()->GetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

						D3DUtil_SetTranslateMatrix(matTrans, vTrans);
						D3DUtil_SetScaleMatrix(matScale, (FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight, 1.0f);
						D3DMath_MatrixMultiply(matWorld, matScale, matTrans);
						g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);

						SetBlendRenderState(g_xMainWnd.Get3DDevice(), 2, &mtrl);

						g_xMainWnd.Get3DDevice()->SetTexture(0, lpddsTextr); 

						g_xMainWnd.Get3DDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_VERTEX, m_avBoard, 4, NULL);

						ResetBlendenderState(g_xMainWnd.Get3DDevice());

						g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

						g_xMainWnd.Get3DDevice()->EndScene();
					}
				}
			}
		}
	}
*/
	// 오성패
	// 찾았다! 지존패 by eriastoa 2006.04.25 제발 좀 주석 좀 잘 달아놓자! 짜증 이빠이
	if ( (( m_bEftFeature & 128 ) >> 7 ) && ( m_nAmorEftIdx >= 514 && m_nAmorEftIdx <= 540 ) )
	{
		if ( m_bDrawOnce || m_nIdentity != g_xGameProc.m_xMyHero.m_nIdentity )
		{
			if ( g_dwCurrTime - m_dwAmorTimer > 80 )
			{
				m_dwAmorTimer = g_dwCurrTime;
				m_nAmorEftIdx++;

				if ( m_nAmorEftIdx > 540 )
					m_nAmorEftIdx = 500;
			}

			const POINT ptArr[] = 
			{
				{0, 20}, {8, 20}, {11, 12}, {7, 15}, {1, 10}, {-10, 15}, {-12, 10}, {-8, 18}
			};

			if ( g_xMainWnd.Get3DDevice() )
			{
				BOOL bIndexSetted	= FALSE;
				CWHWilImageData*	pxWilImg;

				LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_INTER, m_nAmorEftIdx);

				pxWilImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER];

				if ( pxWilImg->NewSetIndex(m_nAmorEftIdx) )
				{
					D3DVECTOR vTrans;
					D3DMATRIX matTrans;
					D3DMATRIX matScale;
					D3DMATRIX matWorld;
					D3DMATRIX matWorldOriginal;
					D3DMATERIAL7 mtrl;

					D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)255/255.0f, (FLOAT)255/255.0f);

					mtrl.diffuse.a = (FLOAT)(1)/255.0f;
					g_xMainWnd.Get3DDevice()->SetMaterial(&mtrl);

					if ( m_stFeatureEx.bHorse != _HORSE_NONE )
					{
 						vTrans.x = (FLOAT)m_nScrnPosX+(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth/2+pxWilImg->m_lpstNewCurrWilImageInfo->shPX-400+ptArr[m_bCurrDir].x; 
						vTrans.y = (FLOAT)-m_nScrnPosY-(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight/2-pxWilImg->m_lpstNewCurrWilImageInfo->shPY+300+ptArr[m_bCurrDir].y - 5; 
					}
					else
					{
 						vTrans.x = (FLOAT)m_nScrnPosX+(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth/2+pxWilImg->m_lpstNewCurrWilImageInfo->shPX-400; 
						vTrans.y = (FLOAT)-m_nScrnPosY-(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight/2-pxWilImg->m_lpstNewCurrWilImageInfo->shPY+300 - 5; 
					}
					vTrans.z = 0;

					if( SUCCEEDED(g_xMainWnd.Get3DDevice()->BeginScene()) )
					{
						g_xMainWnd.Get3DDevice()->GetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

						D3DUtil_SetTranslateMatrix(matTrans, vTrans);
						D3DUtil_SetScaleMatrix(matScale, (FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight, 1.0f);
						D3DMath_MatrixMultiply(matWorld, matScale, matTrans);
						g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);

						SetBlendRenderState(g_xMainWnd.Get3DDevice(), 2, &mtrl);

						g_xMainWnd.Get3DDevice()->SetTexture(0, lpddsTextr); 

						g_xMainWnd.Get3DDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_VERTEX, m_avBoard, 4, NULL);

						ResetBlendenderState(g_xMainWnd.Get3DDevice());

						g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

						g_xMainWnd.Get3DDevice()->EndScene();
					}
				}
			}

			m_bDrawOnce = FALSE;
		}
	}

	// 천뢰
	if ( ( m_bEftFeature & 16 ) >> 4 )
	{
		if ( g_dwCurrTime - m_dwThunderTimer > 150 )
		{
			m_dwThunderTimer = g_dwCurrTime;
			m_nThunderIdx++;

			if ( m_nThunderIdx > 2218 )
				m_nThunderIdx = 2210;
		}

		if ( g_xMainWnd.Get3DDevice() )
		{
			BOOL bIndexSetted	= FALSE;
			CWHWilImageData*	pxWilImg;

			LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_INTER, m_nThunderIdx);

			pxWilImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER];

			if ( pxWilImg->NewSetIndex(m_nThunderIdx) )
			{
				D3DVECTOR vTrans;
				D3DMATRIX matTrans;
				D3DMATRIX matScale;
				D3DMATRIX matWorld;
				D3DMATRIX matWorldOriginal;
				D3DMATERIAL7 mtrl;

				D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)255/255.0f, (FLOAT)255/255.0f);

				mtrl.diffuse.a = (FLOAT)(1)/255.0f;
				g_xMainWnd.Get3DDevice()->SetMaterial(&mtrl);

 				vTrans.x = (FLOAT)m_nScrnPosX+(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth/2+pxWilImg->m_lpstNewCurrWilImageInfo->shPX-400; 
				vTrans.y = (FLOAT)-m_nScrnPosY-(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight/2-pxWilImg->m_lpstNewCurrWilImageInfo->shPY+300; 
				vTrans.z = 0;

				if( SUCCEEDED(g_xMainWnd.Get3DDevice()->BeginScene()) )
				{
					g_xMainWnd.Get3DDevice()->GetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

					D3DUtil_SetTranslateMatrix(matTrans, vTrans);
					D3DUtil_SetScaleMatrix(matScale, (FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight, 1.0f);
					D3DMath_MatrixMultiply(matWorld, matScale, matTrans);
					g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);

					SetBlendRenderState(g_xMainWnd.Get3DDevice(), 2, &mtrl);

					g_xMainWnd.Get3DDevice()->SetTexture(0, lpddsTextr); 

					g_xMainWnd.Get3DDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_VERTEX, m_avBoard, 4, NULL);

					ResetBlendenderState(g_xMainWnd.Get3DDevice());

					g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

					g_xMainWnd.Get3DDevice()->EndScene();
				}
			}
		}
	}	

	if ( bPairDraw == FALSE )
		m_bDrawOnce = TRUE;

	return TRUE;

/*
	DWORD dwCur = timeGetTime();
	if ( dwCur - m_dwSturnTimer > 150 )
	{
		m_dwSturnTimer = dwCur;
		m_nStrurnFrame=1;

		if ( m_nStrurnFrame > 2218 )
			m_nStrurnFrame = 2210;
	}

	if ( g_xMainWnd.Get3DDevice() )
	{
		BOOL bIndexSetted	= FALSE;
		CWHWilImageData*	pxWilImg;

		LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_INTER, m_nStrurnFrame);

		pxWilImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER];

		if ( pxWilImg->NewSetIndex(m_nStrurnFrame) )
		{
			D3DVECTOR vTrans;
			D3DMATRIX matTrans;
			D3DMATRIX matScale;
			D3DMATRIX matWorld;
			D3DMATRIX matWorldOriginal;
			D3DMATERIAL7 mtrl;

			D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)255/255.0f, (FLOAT)255/255.0f);

			mtrl.diffuse.a = (FLOAT)(1)/255.0f;
			g_xMainWnd.Get3DDevice()->SetMaterial(&mtrl);

 			vTrans.x = (FLOAT)m_nScrnPosX+(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth/2+pxWilImg->m_lpstNewCurrWilImageInfo->shPX-400; 
			vTrans.y = (FLOAT)-m_nScrnPosY-(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight/2-pxWilImg->m_lpstNewCurrWilImageInfo->shPY+300; 
			vTrans.z = 0;

			if( SUCCEEDED(g_xMainWnd.Get3DDevice()->BeginScene()) )
			{
				g_xMainWnd.Get3DDevice()->GetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

				D3DUtil_SetTranslateMatrix(matTrans, vTrans);
				D3DUtil_SetScaleMatrix(matScale, (FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight, 1.0f);
				D3DMath_MatrixMultiply(matWorld, matScale, matTrans);
				g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);

				SetBlendRenderState(g_xMainWnd.Get3DDevice(), 2, &mtrl);

				g_xMainWnd.Get3DDevice()->SetTexture(0, lpddsTextr); 

				g_xMainWnd.Get3DDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_VERTEX, m_avBoard, 4, NULL);

				ResetBlendenderState(g_xMainWnd.Get3DDevice());

				g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

				g_xMainWnd.Get3DDevice()->EndScene();
			}
		}

//		g_xGameProc.m_xLightFog.SetLightRadiusWithRing(
//										  m_nScrnPosX + _CELL_WIDTH/2,
//							  			  m_nScrnPosY + _CELL_HEIGHT/2, 
//										  2, 40, 40, 250, 
//										  5, 40, 40, 250);
	}

/*
	if ( m_bCurrMtn == _MT_WALK || m_bCurrMtn == _MT_RUN )
	{
		const POINT ptArr1[] = 
		{
			{5, 24}, {10, 20}, {- 4, 54}, {1, -10}, {5, -10}, {2, 3}, {1, 1}, {1, 1}
		};
		const POINT ptArr2[] = 
		{
			{39, 24}, {10, 38}, {- 6, 20}, {20, -10}, {39, -10}, {2, 3}, {1, 1}, {1, 1}
		};

		g_xGameProc.m_xFlyingTail.SetFlyTailParticle(D3DVECTOR((FLOAT)(m_nScrnPosX+m_pxActorImage->m_lpstNewCurrWilImageInfo->shPX + ptArr1[m_bCurrDir].x), (FLOAT)(m_nScrnPosY+m_pxActorImage->m_lpstNewCurrWilImageInfo->shPY + ptArr1[m_bCurrDir].y), 0));
//		g_xGameProc.m_xFlyingTail.SetFlyTailParticle(D3DVECTOR((FLOAT)(m_nScrnPosX+m_pxActorImage->m_lpstNewCurrWilImageInfo->shPX + ptArr2[m_bCurrDir].x), (FLOAT)(m_nScrnPosY+m_pxActorImage->m_lpstNewCurrWilImageInfo->shPY + ptArr2[m_bCurrDir].y), 0));
//		g_xGameProc.m_xSmoke.SetSmokeParticle(D3DVECTOR((FLOAT)(m_nScrnPosX+m_pxActorImage->m_lpstNewCurrWilImageInfo->shPX + ptArr1[m_bCurrDir].x), (FLOAT)(m_nScrnPosY+m_pxActorImage->m_lpstNewCurrWilImageInfo->shPY + ptArr1[m_bCurrDir].y), 0));	
	}
*/
	//return TRUE;
}


BOOL CHero::DrawActorAfterImage(CMapHandler* pxMap, BOOL bFocused, BOOL bShadowAblended, BOOL bUseScrnPos, BOOL bDrawShadow, INT nOrder)
{
	// 좌표처리.

	DWORD dwFrame, dwFstFrame, dwEndFrame, dwMoveNextFrmCnt;
	INT   nPosX, nPosY;
	INT	  nShiftPixelX, nShiftPixelY;
	BYTE  m_bMoveSpeed, bMtn;

	if ( m_bCurrMtn == _MT_WALK )
	{
		
		if ( m_nShiftPixelX ==  0 )
			int sfs = 0;
		else 
			int as = 0;
	}

	if ( nOrder == 1 )
	{
		dwFrame = m_xAfterImage[m_nPlayIdx1].m_dwFrame;
		dwFstFrame = m_xAfterImage[m_nPlayIdx1].m_dwFstFrame;
		dwEndFrame = m_xAfterImage[m_nPlayIdx1].m_dwEndFrame;
		dwMoveNextFrmCnt = m_xAfterImage[m_nPlayIdx1].m_dwMoveNextFrmCnt;
		nPosX = m_xAfterImage[m_nPlayIdx1].m_nPosX;
		nPosY = m_xAfterImage[m_nPlayIdx1].m_nPosY;
		nShiftPixelX = m_xAfterImage[m_nPlayIdx1].m_nShiftPixelX;
		nShiftPixelY = m_xAfterImage[m_nPlayIdx1].m_nShiftPixelY;
		m_bMoveSpeed = m_xAfterImage[m_nPlayIdx1].m_bMoveSpeed;
		bMtn = m_xAfterImage[m_nPlayIdx1].m_bMtn;
	}
	else
	{
		dwFrame = m_xAfterImage[m_nPlayIdx2].m_dwFrame;
		dwFstFrame = m_xAfterImage[m_nPlayIdx2].m_dwFstFrame;
		dwEndFrame = m_xAfterImage[m_nPlayIdx2].m_dwEndFrame;
		dwMoveNextFrmCnt = m_xAfterImage[m_nPlayIdx2].m_dwMoveNextFrmCnt;
		nPosX = m_xAfterImage[m_nPlayIdx2].m_nPosX;
		nPosY = m_xAfterImage[m_nPlayIdx2].m_nPosY;
		nShiftPixelX = m_xAfterImage[m_nPlayIdx2].m_nShiftPixelX;
		nShiftPixelY = m_xAfterImage[m_nPlayIdx2].m_nShiftPixelY;
		m_bMoveSpeed = m_xAfterImage[m_nPlayIdx2].m_bMoveSpeed;
		bMtn = m_xAfterImage[m_nPlayIdx2].m_bMtn;
	}
/*
	if ( bMtn == _MT_WALK || bMtn == _MT_RUN || bMtn == _MT_MOODEPO || bMtn == _MT_HORSEWALK || bMtn == _MT_HORSERUN)

	{
		WORD wFrmCnt  = (WORD)(dwEndFrame  - dwFstFrame);
		WORD wCurrFrm = (WORD)(dwFrame - dwFstFrame);

		if ( wFrmCnt == 0 )
			return FALSE;

		int nMoveFrame = 6;

		switch ( m_bMoveDir )
		{
		case _DIRECTION_LIST_1:
			nShiftPixelX =  0;

			if ( wCurrFrm < (nMoveFrame-dwMoveNextFrmCnt) )
				nShiftPixelY = -(_CELL_HEIGHT/wFrmCnt * (wCurrFrm+1))*1;
			else
				nShiftPixelY =  (_CELL_HEIGHT/wFrmCnt * (wFrmCnt - wCurrFrm -1))*m_bMoveSpeed;
			break;
		case _DIRECTION_LIST_2:
			if ( wCurrFrm < (nMoveFrame-dwMoveNextFrmCnt) )
				nShiftPixelX =  (_CELL_WIDTH /wFrmCnt * (wCurrFrm+1))*m_bMoveSpeed;
			else
				nShiftPixelX = -(_CELL_WIDTH /wFrmCnt * (wFrmCnt - wCurrFrm -1))*m_bMoveSpeed;

			
			if ( wCurrFrm < (nMoveFrame-dwMoveNextFrmCnt) )
				nShiftPixelY = -(_CELL_HEIGHT/wFrmCnt * (wCurrFrm+1))*m_bMoveSpeed;
			else
				nShiftPixelY =  (_CELL_HEIGHT/wFrmCnt * (wFrmCnt - wCurrFrm -1))*m_bMoveSpeed;
			break;
		case _DIRECTION_LIST_3:
			if ( wCurrFrm < (nMoveFrame-dwMoveNextFrmCnt) )
				nShiftPixelX =  (_CELL_WIDTH /wFrmCnt * (wCurrFrm+1))*m_bMoveSpeed;
			else
				nShiftPixelX = -(_CELL_WIDTH /wFrmCnt * (wFrmCnt - wCurrFrm -1))*m_bMoveSpeed;

			nShiftPixelY = 0;
			break;
		case _DIRECTION_LIST_4:
			if ( wCurrFrm < (nMoveFrame-dwMoveNextFrmCnt) )
				nShiftPixelX =  (_CELL_WIDTH /wFrmCnt * (wCurrFrm+1))*m_bMoveSpeed;
			else
				nShiftPixelX = -(_CELL_WIDTH /wFrmCnt * (wFrmCnt - wCurrFrm -1))*m_bMoveSpeed;

			if ( wCurrFrm < (nMoveFrame-dwMoveNextFrmCnt) )
				nShiftPixelY =  (_CELL_HEIGHT/wFrmCnt * (wCurrFrm+1))*m_bMoveSpeed;
			else
				nShiftPixelY = -(_CELL_HEIGHT/wFrmCnt * (wFrmCnt - wCurrFrm -1))*m_bMoveSpeed;
			break;
		case _DIRECTION_LIST_5:
			nShiftPixelX =  0;

			if ( wCurrFrm < (nMoveFrame-dwMoveNextFrmCnt) )
				nShiftPixelY =  (_CELL_HEIGHT/wFrmCnt * (wCurrFrm+1))*m_bMoveSpeed;
			else
				nShiftPixelY = -(_CELL_HEIGHT/wFrmCnt * (wFrmCnt - wCurrFrm -1))*m_bMoveSpeed;
			break;
		case _DIRECTION_LIST_6:
			if ( wCurrFrm < (nMoveFrame-dwMoveNextFrmCnt) )
				nShiftPixelX = -(_CELL_WIDTH /wFrmCnt * (wCurrFrm+1))*m_bMoveSpeed;
			else
				nShiftPixelX =  (_CELL_WIDTH /wFrmCnt * (wFrmCnt - wCurrFrm -1))*m_bMoveSpeed;

			if ( wCurrFrm < (nMoveFrame-dwMoveNextFrmCnt) )
				nShiftPixelY =  (_CELL_HEIGHT/wFrmCnt * (wCurrFrm+1))*m_bMoveSpeed;
			else
				nShiftPixelY = -(_CELL_HEIGHT/wFrmCnt * (wFrmCnt - wCurrFrm -1))*m_bMoveSpeed;
			break;
		case _DIRECTION_LIST_7:
			if ( wCurrFrm < (nMoveFrame-dwMoveNextFrmCnt) )
				nShiftPixelX = -(_CELL_WIDTH /wFrmCnt * (wCurrFrm+1))*m_bMoveSpeed;
			else
				nShiftPixelX =  (_CELL_WIDTH /wFrmCnt * (wFrmCnt - wCurrFrm -1))*m_bMoveSpeed;

			nShiftPixelY =  0;
			break;
		case _DIRECTION_LIST_8:
			if ( wCurrFrm < (nMoveFrame-dwMoveNextFrmCnt) )
				nShiftPixelX = -(_CELL_WIDTH /wFrmCnt * (wCurrFrm+1))*m_bMoveSpeed;
			else
				nShiftPixelX =  (_CELL_WIDTH /wFrmCnt * (wFrmCnt - wCurrFrm -1))*m_bMoveSpeed;

			if ( wCurrFrm < (nMoveFrame-dwMoveNextFrmCnt) )
				nShiftPixelY = -(_CELL_HEIGHT/wFrmCnt * (wCurrFrm+1))*m_bMoveSpeed;
			else
				nShiftPixelY =  (_CELL_HEIGHT/wFrmCnt * (wFrmCnt - wCurrFrm -1))*m_bMoveSpeed;
			break;	
		}
	}
*/
	INT nScrnPosX = (nPosX - pxMap->m_nStartViewTileX) * _CELL_WIDTH + pxMap->m_nViewPosX - pxMap->m_nViewOffsetX + nShiftPixelX;
	INT nScrnPosY = (nPosY - pxMap->m_nStartViewTileY) * _CELL_HEIGHT+ pxMap->m_nViewPosY - pxMap->m_nViewOffsetY + nShiftPixelY;

//	CHAR pszLog[100];
//	sprintf(pszLog, "m_nScrnPosX:%d, nPosX:%d, pxMap->m_nStartViewTileX:%d, pxMap->m_nViewPosX:%d, pxMap->m_nViewOffsetX:%d, nShiftPixelX:%d, dwFrame:%d, nOrder:%d",
//					 m_nScrnPosX, nPosX, pxMap->m_nStartViewTileX, pxMap->m_nViewPosX, pxMap->m_nViewOffsetX, nShiftPixelX, dwFrame, nOrder);
//	FLOG0("LogGold.txt", pszLog);

//	CHAR szTemp[MAX_PATH];
//	sprintf( szTemp, "nScrnPosY:%d, Mtn:%d, m_nShiftPixelY:%d, pxMap->m_nViewOffsetY:%d", nScrnPosY, bMtn, nShiftPixelY, pxMap->m_nViewOffsetY );
//	g_xMainWnd.PutsHan(NULL, nScrnPosX, nScrnPosY-100, RGB( 250, 250, 250), RGB(0, 0, 0), szTemp);
//	FLOG0("LogY3.txt", szTemp);

	SHORT	shPX, shPY;
	BOOL	bPairDraw = FALSE;
	//---------------------------------------------------------------------------------------------------------------//
	// 각 이미지 세팅및 좌표영역 체크.
	//---------------------------------------------------------------------------------------------------------------//
	// 말.

	if ( m_stFeatureEx.bHorse != _HORSE_NONE && m_pxHorseImage != NULL )
	{
		if ( m_bCurrMtn >= _START_HORSE_MTN )
		{		
			m_dwCurrHorseFrame = (m_stFeatureEx.bHorse*_MAX_HORSE_FRAME-_MAX_HORSE_FRAME)+(dwFrame-(_MAX_HERO_FRAME*m_stFeature.bDress)-_START_HORSE_FRAME);
			
			if ( !m_pxHorseImage->NewSetIndex(m_dwCurrHorseFrame) )
				return FALSE;
			shPX = m_pxHorseImage->m_lpstNewCurrWilImageInfo->shPX;
			shPY = m_pxHorseImage->m_lpstNewCurrWilImageInfo->shPY;
			SetRect(&m_rcHorse, nScrnPosX + shPX, nScrnPosY + shPY,
					nScrnPosX + shPX + m_pxHorseImage->m_lpstNewCurrWilImageInfo->shWidth, 
					nScrnPosX + shPY + m_pxHorseImage->m_lpstNewCurrWilImageInfo->shHeight);
		}
	} 

	// 무기.
	if ( m_stFeature.bWeapon != _WEAPON_NONE && m_pxWeaponImage != NULL )/* && m_stFeature.bWeapon != 37 /*눈덩이 )*/
	{
		if ( m_bCurrMtn < _MAX_WEAPON_MTN )
		{	
			if ( m_stFeature.bWeapon == 254 )
				m_dwCurrWeaponFrame = (((m_stFeature.bWeapon-2)%10)*_MAX_WEAPON_FRAME)+(dwFrame-(_MAX_HERO_FRAME*m_stFeature.bDress));
			else
				m_dwCurrWeaponFrame = (((m_stFeature.bWeapon-1)%10)*_MAX_WEAPON_FRAME)+(dwFrame-(_MAX_HERO_FRAME*m_stFeature.bDress));

			if ( !m_pxWeaponImage->NewSetIndex(m_dwCurrWeaponFrame) )
				return FALSE;

			shPX = m_pxWeaponImage->m_lpstNewCurrWilImageInfo->shPX;
			shPY = m_pxWeaponImage->m_lpstNewCurrWilImageInfo->shPY;
			SetRect(&m_rcWeapon, nScrnPosX + shPX, nScrnPosY + shPY, 
					nScrnPosX + shPX + m_pxWeaponImage->m_lpstNewCurrWilImageInfo->shWidth, 
					nScrnPosY + shPY + m_pxWeaponImage->m_lpstNewCurrWilImageInfo->shHeight);
		}
	}

	// 캐릭터.
	if ( m_pxActorImage )
	{
		if ( !m_pxActorImage->NewSetIndex(dwFrame) )
			return FALSE;
		shPX = m_pxActorImage->m_lpstNewCurrWilImageInfo->shPX;
		shPY = m_pxActorImage->m_lpstNewCurrWilImageInfo->shPY;

		SetRect(&m_rcActor, nScrnPosX + shPX, nScrnPosY + shPY, 
				nScrnPosX + shPX + m_pxActorImage->m_lpstNewCurrWilImageInfo->shWidth, 
				nScrnPosY + shPY + m_pxActorImage->m_lpstNewCurrWilImageInfo->shHeight);
	}

	// 머리.
	if ( m_stFeature.bHair != _HAIR_NONE && m_pxHairImage != NULL )
	{
		m_dwCurrHairFrame = ((m_stFeature.bHair-1)%10*_MAX_HERO_FRAME)+(dwFrame-(_MAX_HERO_FRAME*m_stFeature.bDress));

		if ( !m_pxHairImage->NewSetIndex(m_dwCurrHairFrame) )
			return FALSE;
		shPX = m_pxHairImage->m_lpstNewCurrWilImageInfo->shPX;
		shPY = m_pxHairImage->m_lpstNewCurrWilImageInfo->shPY;
		SetRect(&m_rcHair, m_nScrnPosX + shPX, m_nScrnPosY + shPY, 
					m_nScrnPosX + shPX + m_pxHairImage->m_lpstNewCurrWilImageInfo->shWidth, 
					m_nScrnPosY + shPY + m_pxHairImage->m_lpstNewCurrWilImageInfo->shHeight);
	}

	//---------------------------------------------------------------------------------------------------------------//
	// 그림자그리기.
	//---------------------------------------------------------------------------------------------------------------//
	BYTE bOpaRate = 13;
	WORD wState   = GetCharState();

	if ( m_nABlendDelay || wState==_STATE_ABLEND )
	{
		bShadowAblended = TRUE;
	}

	// 머리는 그림자를 그리지 않는다.
	if ( m_nABlendDelay > 0 )		
	{
		bShadowAblended = TRUE;

		if ( m_nABlendDelay )	
		{
			if ( m_bABlendRev )
				bOpaRate = (BYTE)(31 - ( (m_nABlendCurrDelay * 31) / m_nABlendDelay ));
			else
				bOpaRate = (BYTE)( (m_nABlendCurrDelay * 31) / m_nABlendDelay );
		}

		if ( bFocused )								
		{
			if ( m_bABlendRev )
				bOpaRate -= 5;
			else
				bOpaRate += 5;
		}

		if ( bOpaRate < 0 || bOpaRate > 31 )		bOpaRate  = 0;
	}
	else if ( wState == _STATE_ABLEND )			bShadowAblended = TRUE;

	//---------------------------------------------------------------------------------------------------------------//
	// 이미지 그리기.
	//---------------------------------------------------------------------------------------------------------------//
	// 말.
	if ( m_stFeatureEx.bHorse != _HORSE_NONE && m_pxHorseImage != NULL )
	{
		if ( m_bCurrMtn >= _START_HORSE_MTN )
		{			
			DrawWithEffected(m_rcHorse.left, m_rcHorse.top, m_pxHorseImage->m_lpstNewCurrWilImageInfo->shWidth, m_pxHorseImage->m_lpstNewCurrWilImageInfo->shHeight, (WORD*)m_pxHorseImage->m_pbCurrImage, 
				             0XFFFF, 0XFFFF, bFocused, bOpaRate, wState);
		}
	}

	// 무기를 먼저 그려야될방향.
	if ( m_stFeature.bWeapon != _WEAPON_NONE && m_pxWeaponImage != NULL && g_xSpriteInfo.m_bWOrder[(dwFrame-(_MAX_HERO_FRAME*m_stFeature.bDress))] && m_stFeature.bWeapon != 37 /*눈덩이*/ )
	{
		if ( m_bCurrMtn < _MAX_WEAPON_MTN )
		{			
			WORD wColor = FindWeaponColor(m_stFeatureEx.bWeaponColor);
			DrawWithEffected(m_rcWeapon.left, m_rcWeapon.top, m_pxWeaponImage->m_lpstNewCurrWilImageInfo->shWidth, m_pxWeaponImage->m_lpstNewCurrWilImageInfo->shHeight, (WORD*)m_pxWeaponImage->m_pbCurrImage,
							 wColor, 0XFFFF, bFocused, 10, wState);

			if ( m_stFeature.bWeapon == 254 )			// 절대검
			{
				INT nTemp, nCurEffectFrame;
				if ( m_stFeature.bGender == _GENDER_MAN )
				{
					nTemp = dwFrame - m_stFeature.bDress*_MAX_HERO_FRAME;
					nCurEffectFrame = 1900 + nTemp;
				}
				else
				{
					nTemp = dwFrame - m_stFeature.bDress*_MAX_HERO_FRAME;
					nCurEffectFrame = 3900 + nTemp;
				}
				DrawTheSwordEffect(nCurEffectFrame);
			}
		}
	}

	// 캐릭터.
	if ( m_pxActorImage != NULL )
	{
		DrawWithEffected(m_rcActor.left, m_rcActor.top, m_pxActorImage->m_lpstNewCurrWilImageInfo->shWidth, m_pxActorImage->m_lpstNewCurrWilImageInfo->shHeight, (WORD*)m_pxActorImage->m_pbCurrImage,
				         m_stFeatureEx.wDressColor, 0XFFFF, bFocused, bOpaRate, wState);
	}

	// 머리.
 	if ( m_stFeature.bHair != _HAIR_NONE && m_pxHairImage != NULL )
	{
		WORD wHairClr = m_stFeatureEx.wHairColor;

		// 투구.
		if ( m_stFeature.bHair > 10 )

		{
			wHairClr = 0XFFFF;
		}

		DrawWithEffected(m_rcHair.left, m_rcHair.top, m_pxHairImage->m_lpstNewCurrWilImageInfo->shWidth, m_pxHairImage->m_lpstNewCurrWilImageInfo->shHeight, (WORD*)m_pxHairImage->m_pbCurrImage, 
				         wHairClr, 0XFFFF, bFocused, 20, wState);
	}			

	// 무기를 나중에 그려야될 방향.
	if ( m_stFeature.bWeapon != _WEAPON_NONE && m_pxWeaponImage != NULL && !g_xSpriteInfo.m_bWOrder[(dwFrame-(_MAX_HERO_FRAME*m_stFeature.bDress))] && m_stFeature.bWeapon != 37 /*눈덩이*/ ) 
	{
		if ( m_bCurrMtn < _MAX_WEAPON_MTN )
		{			
			WORD wColor = FindWeaponColor(m_stFeatureEx.bWeaponColor);
 			DrawWithEffected(m_rcWeapon.left, m_rcWeapon.top, m_pxWeaponImage->m_lpstNewCurrWilImageInfo->shWidth, m_pxWeaponImage->m_lpstNewCurrWilImageInfo->shHeight, (WORD*)m_pxWeaponImage->m_pbCurrImage,
							 wColor, 0XFFFF, bFocused, /*bOpaRate*/22, wState);

			if ( m_stFeature.bWeapon == 254 )			// 절대검
			{
				INT nTemp, nCurEffectFrame;
				if ( m_stFeature.bGender == _GENDER_MAN )
				{
					nTemp = dwFrame - m_stFeature.bDress*_MAX_HERO_FRAME;
					nCurEffectFrame = 1900 + nTemp;
				}
				else
				{
					nTemp = dwFrame - m_stFeature.bDress*_MAX_HERO_FRAME;
					nCurEffectFrame = 3900 + nTemp;
				}

				DrawTheSwordEffect(nCurEffectFrame);
			}
		}
	}

	return TRUE;
}

VOID CHero::DrawTheSwordEffect(INT nFrame)
{
	if ( g_xMainWnd.Get3DDevice() )
	{
		BOOL bIndexSetted	= FALSE;
		CWHWilImageData*	pxWilImg;

		LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_MONMAGIC, _IMAGE_MONMAGICEX4, nFrame);

		pxWilImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_MONMAGICEX4];

		if ( pxWilImg->NewSetIndex(nFrame) )
		{
			D3DVECTOR vTrans;
			D3DMATRIX matTrans;
			D3DMATRIX matScale;
			D3DMATRIX matWorld;
			D3DMATRIX matWorldOriginal;
			D3DMATERIAL7 mtrl;

			D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)255/255.0f, (FLOAT)255/255.0f);

			mtrl.diffuse.a = (FLOAT)(1)/255.0f;
			g_xMainWnd.Get3DDevice()->SetMaterial(&mtrl);

 			vTrans.x = (FLOAT)m_nScrnPosX+(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth/2+pxWilImg->m_lpstNewCurrWilImageInfo->shPX-400; 
			vTrans.y = (FLOAT)-m_nScrnPosY-(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight/2-pxWilImg->m_lpstNewCurrWilImageInfo->shPY+300; 
			vTrans.z = 0;

			if( SUCCEEDED(g_xMainWnd.Get3DDevice()->BeginScene()) )
			{
				g_xMainWnd.Get3DDevice()->GetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

				D3DUtil_SetTranslateMatrix(matTrans, vTrans);
				D3DUtil_SetScaleMatrix(matScale, (FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight, 1.0f);
				D3DMath_MatrixMultiply(matWorld, matScale, matTrans);
				g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);

				SetBlendRenderState(g_xMainWnd.Get3DDevice(), 2, &mtrl);

				g_xMainWnd.Get3DDevice()->SetTexture(0, lpddsTextr); 

				g_xMainWnd.Get3DDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_VERTEX, m_avBoard, 4, NULL);

				ResetBlendenderState(g_xMainWnd.Get3DDevice());

				g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

				g_xMainWnd.Get3DDevice()->EndScene();
			}
		}

		g_xGameProc.m_xLightFog.SetLightRadiusWithRing(
										  m_nScrnPosX + _CELL_WIDTH/2,
							  			  m_nScrnPosY + _CELL_HEIGHT/2, 
										  2, 40, 40, 250, 
										  5, 40, 40, 250);
	}
}



VOID CHero::DrawTheAomorEffect(INT nFrame)
{
	if ( g_xMainWnd.Get3DDevice() )
	{
		BOOL bIndexSetted	= FALSE;
		CWHWilImageData*	pxWilImg;

		LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_WM_ARMOREFT, nFrame);

		pxWilImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_WM_ARMOREFT];

		if ( pxWilImg->NewSetIndex(nFrame) )
		{
			D3DVECTOR vTrans;
			D3DMATRIX matTrans;
			D3DMATRIX matScale;
			D3DMATRIX matWorld;
			D3DMATRIX matWorldOriginal;
			D3DMATERIAL7 mtrl;

			D3DUtil_InitMaterial(mtrl, (FLOAT)190/255.0f, (FLOAT)190/255.0f, (FLOAT)190/255.0f);

			mtrl.diffuse.a = (FLOAT)(0.1)/255.0f;
			g_xMainWnd.Get3DDevice()->SetMaterial(&mtrl);

 			vTrans.x = (FLOAT)m_nScrnPosX+(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth/2+pxWilImg->m_lpstNewCurrWilImageInfo->shPX-400; 
			vTrans.y = (FLOAT)-m_nScrnPosY-(FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight/2-pxWilImg->m_lpstNewCurrWilImageInfo->shPY+300; 
			vTrans.z = 0;

			if( SUCCEEDED(g_xMainWnd.Get3DDevice()->BeginScene()) )
			{
				g_xMainWnd.Get3DDevice()->GetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

				D3DUtil_SetTranslateMatrix(matTrans, vTrans);
				D3DUtil_SetScaleMatrix(matScale, (FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxWilImg->m_lpstNewCurrWilImageInfo->shHeight, 1.0f);
				D3DMath_MatrixMultiply(matWorld, matScale, matTrans);
				g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);

				SetBlendRenderState(g_xMainWnd.Get3DDevice(), 2, &mtrl);

				g_xMainWnd.Get3DDevice()->SetTexture(0, lpddsTextr); 

				g_xMainWnd.Get3DDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_VERTEX, m_avBoard, 4, NULL);

				ResetBlendenderState(g_xMainWnd.Get3DDevice());

				g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

				g_xMainWnd.Get3DDevice()->EndScene();
			}
		}
	}
}




















/******************************************************************************************************************

	CMyHero Class

*******************************************************************************************************************/
/******************************************************************************************************************

	함수명 : CMyHero::CMyHero()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
CMyHero::CMyHero()
{
	InitActor();
}



/******************************************************************************************************************

	함수명 : CMyHero::~CMyHero()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
CMyHero::~CMyHero()
{
	DestroyActor();
}


VOID CMyHero::InitActor()
{
	CHero::InitActor();

	m_bMyHeroSetted		= FALSE;

	m_nOldPosX			= 0;
	m_nOldPosY			= 0;
	m_bOldDir			= 0;
	m_dwWarModeTime		= 0;
	m_dwMotionLockTime	= 0;

	m_dwMagicDelayTime	= 0;
	m_dwMagicPKDelayTime= 0;

	m_bJob				= 0;
	m_nGlod				= 0;

	m_dwLastMoveTime	= 0;
	m_dwLastHitTime		= 0;
	m_dwLastSpellTime	= 0;
	m_dwLastMagicTime	= 0;
	m_dwLastStruckTime  = 0;
	m_dwLastPKStruckTime= 0;
	m_dwLastRushTime	= 0;
	m_dwLastKickTime	= 0;
	m_dwLastFireHitTime = 0;

	m_dwLastJSHitTime	= 0;
	m_dwLastRSHitTime	= 0;

	m_dwLastWalkTime	= 0;
	m_dwLastMagicUseTime	= 0;
	m_dwLastHitUseTime	= 0;

	m_bCanRun			= FALSE;
	m_dwCanRunTick		= 0;
	m_bInputLock		= FALSE;
	m_bMotionLock		= FALSE;
	m_bWarMode			= FALSE;

	m_pxMap				= NULL;

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	m_bAutoDig			= FALSE;
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	ZeroMemory(&m_stAbility, sizeof(ACTORABILITY));
	ZeroMemory(&m_stSubAbility, sizeof(ACTORSUBABILITY));

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 마법 테스트관련.
	m_nTestMagicID	   = -1;
	m_ptDstMagicTile.x = 0;
	m_ptDstMagicTile.y = 0;
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	m_nDelaySeed1400_1	= 7;
	m_nDelaySeed1400_2	= 20;
	m_nDelaySeed1400_3	= 10;

	m_nDelaySeed1500_1	= 5;
	m_nDelaySeed1500_2	= 30;
	m_nDelaySeed1500_3	= 10;

	m_nDelayTemp1400	= 0;
	m_nDelayTemp1500	= 0;

	m_nDelaySeed1000_1	= 9;
	m_nDelaySeed1000_2	= 8;
	m_nDelaySeed1000_3	= 28;

	m_nDelayTemp1000	= 0;

	m_nMinTemp370		= 370;
	m_nMinTemp800		= 800;

	m_nTempWeaponExp    = 0;


	// 2006.06.20 - 포인트상점
#ifdef _TEST_SERVER
	m_nPoint			= 0;
#endif
}

VOID CMyHero::DestroyActor()
{
	CHero::DestroyActor();
	InitActor();
}

BOOL CMyHero::Create(CImageHandler* pxImgHandler, BYTE bMtn, BYTE bDir, INT nPosX, INT nPosY, 
				   FEATURE* pstFeature, FEATUREEX* pstFeatureEx)
{
	ZeroMemory(&m_stAbility, sizeof(ACTORABILITY));
	ZeroMemory(&m_stSubAbility, sizeof(ACTORSUBABILITY));
	
	if ( !(CHero::Create(pxImgHandler, bMtn, bDir, nPosX, nPosY, pstFeature, pstFeatureEx)) )
	{
		return FALSE;
	}

	m_nOldPosX = m_nPosX;
	m_nOldPosY = m_nPosY;
	m_bMyHeroSetted = TRUE;
	return TRUE;
}



/******************************************************************************************************************

	함수명 : CMyHero::SetMapHandler()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : CMapHandler* pxMap
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CMyHero::SetMapHandler(CMapHandler* pxMap)
{
	m_pxMap = pxMap;
}


VOID CMyHero::OnHealthSpellChanged(LPPACKETMSG lpPacketMsg)
{
	if ( lpPacketMsg->stDefMsg.wParam - m_wHP != 0 && m_wHP != 0 && g_xGameProc.m_bShowBloodNum )
	{
		m_nShowBlood[m_nShowBloodIdx] = lpPacketMsg->stDefMsg.wParam - m_wHP;
		m_ptShowBlood[m_nShowBloodIdx].x = m_nScrnPosX;
		m_ptShowBlood[m_nShowBloodIdx].y = m_nScrnPosY;
		m_dwShowBloodTimer[m_nShowBloodIdx] = 0;

		m_nShowBloodIdx++;

		if ( m_nShowBloodIdx > 7 )
			m_nShowBloodIdx = 0;
	}

	m_stAbility.wHP 	= m_wHP    = lpPacketMsg->stDefMsg.wParam;
	m_stAbility.wMP 	= m_wMP    = lpPacketMsg->stDefMsg.wTag;
	m_stAbility.wMaxHP	= m_wMAXHP = lpPacketMsg->stDefMsg.wSeries;
	FLOAT wHPRate = 0.0f;

	if ( lpPacketMsg->stDefMsg.wSeries )
	{
		wHPRate = (FLOAT)((FLOAT)lpPacketMsg->stDefMsg.wParam/(FLOAT)lpPacketMsg->stDefMsg.wSeries);
	}
	m_bHPPercent	=(BYTE)(wHPRate * 100);
}



VOID CMyHero::OnSpaceMoveHide(LPPACKETMSG lpPacketMsg)
{
//	m_nPosX = lpPacketMsg->stDefMsg.wParam;
//	m_nPosY = lpPacketMsg->stDefMsg.wTag;
	CMagic* pxMagic;

	g_SoundManager.SndmngrPlayWavSound(_SOUND_SPACEMOVE_IN, m_nPosX, m_nPosY);
	
	// 아공전서로 다른맵에 나타나기.
	if ( lpPacketMsg->stDefMsg.wIdent == SM_SPACEMOVE_HIDE )
	{
		pxMagic = new CMagic;
		if ( pxMagic->CreateMagic(_SKILL_SPACEMOVEHIDE2, m_nPosX, m_nPosY, m_nPosX, m_nPosY, NULL, 0) )
		{
			g_xGameProc.m_xMagicList.Insert (pxMagic);	

			g_xGameProc.m_dwInputDelayTime = 1500;
			g_xGameProc.m_dwCurrInputDelayTime = 0;
		}
		else
		{
			delete pxMagic;
		}
	}
	// 아공행법으로 새로운맵으로 나타나기.
	else if ( lpPacketMsg->stDefMsg.wIdent == SM_SPACEMOVE_HIDE2 )
	{		
		pxMagic = new CMagic;
		if ( pxMagic->CreateMagic(_SKILL_SPACEMOVESHOW, m_nPosX, m_nPosY, m_nPosX, m_nPosY, NULL, 0) )
		{
			g_xGameProc.m_xMagicList.Insert (pxMagic);	
		}
		else
		{
			delete pxMagic;
		}
	}
}



VOID CMyHero::DrawHPBar(INT nX, INT nY)
{	
	if ( g_xGameProc.m_xInterface.m_xOptionWnd.mOptionWnd_bShowHealthbar && !m_bIsDead )
	{
		FLOAT	fHPPercent	= (FLOAT)((FLOAT)m_bHPPercent/100);
		RECT	rcHP		= {0, 0, (LONG)(46*fHPPercent), 2};

		FLOAT	fMPPercent  = (FLOAT)((FLOAT)m_stAbility.wMP/m_stAbility.wMaxMP);
		RECT	rcMP		= {0, 0, (LONG)(46*fMPPercent), 2};

 		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(3) )
		{
			if ( nX == -1 && nY == -1 )
			{
				nX = m_nScrnPosX;
				if ( m_stFeatureEx.bHorse == _HORSE_NONE )
				{
					nY = m_nScrnPosY-58;
				}
				else
				{
					nY = m_nScrnPosY-80;
				}
			}

 			g_xMainWnd.DrawWithImageForComp(
							nX,
							nY,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
							(WORD*)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);

 			g_xMainWnd.DrawWithImageForComp(
							nX,
							nY+4,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
							(WORD*)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
		}

		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(1) )
		{
 			g_xMainWnd.DrawWithImageForComp(
							nX+1,
							nY+1,
							&rcHP,
							(WORD*)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
		}

		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(2) )
		{
 			g_xMainWnd.DrawWithImageForComp(
							nX+1,
							nY+5,
							&rcMP,
							(WORD*)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
		}
	}
}

/******************************************************************************************************************

	함수명 : CMyHero::UpdatePacketState()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CMyHero::UpdatePacketState()
{	
	BOOL bRet = TRUE;

	LPPACKETMSG	lpPacketMsg = NULL;

	if ( m_bCurrMtn == _MT_STAND || m_bCurrMtn == _MT_ATTACKMODE || m_bCurrMtn == _MT_HORSESTAND || (m_bCurrMtn==_MT_SPELL1 && m_dwCurrFrame==m_dwEndFrame - 2) || m_bIsDead )
	{
		INT	nLeftMsgCnt = m_xPacketQueue.GetCount();

		if ( nLeftMsgCnt > 0 )
		{
			if ( nLeftMsgCnt >= 3 )		m_bMsgHurryCheck = TRUE;
			else						m_bMsgHurryCheck = FALSE;			
	
			lpPacketMsg = (LPPACKETMSG)m_xPacketQueue.PopQ();
			
			if ( lpPacketMsg )
			{
				switch ( lpPacketMsg->stDefMsg.wIdent )
				{
					case SM_BACKKICKUP:
					case SM_WIDEHIT:
					case SM_BACKSWINGHIT:
					{
						OnHit(lpPacketMsg);					
						break;	
					}
					case SM_REFLEXPOWER:
					{
						CMagic* pxMagic;
						pxMagic = new CMagic;
						if ( pxMagic->CreateMagic(_SKILL_BANTAN_HITTED, m_nPosX, m_nPosY, m_nPosX, m_nPosY, NULL, 0) )
							g_xGameProc.m_xMagicList.Insert (pxMagic);						
						else
							delete pxMagic;
						break;
					}
					case SM_SETXY:
					{
						OnSetXY(lpPacketMsg);
						break;	
					}
					case SM_NOWDEATH:
					case SM_DEATH:
					{
						OnDeath(lpPacketMsg);
						break;;
					}
					case SM_MYREVIVAL:
					{
						OnTurn(lpPacketMsg);
						m_bInputLock  = FALSE;
						m_bMotionLock  = FALSE;
						break;
					}
					case SM_STRUCK:
					case SM_STRUCK2:				
					{
						m_bInputLock = TRUE;
						m_wHP	 = m_stAbility.wHP	  = lpPacketMsg->stDefMsg.wParam;
						m_wMAXHP = m_stAbility.wMaxHP = lpPacketMsg->stDefMsg.wTag;
						OnStruck(lpPacketMsg);

						if ( m_dwNameClr == RGB(255, 0, 0) )
						{
							m_dwLastPKStruckTime = timeGetTime();
						}

						m_dwLastStruckTime = timeGetTime();

						// 레벨이 높을수록 맞는 시간이 짧아진다.
						m_nDelay = (200 - m_stAbility.bLevel * 3);
						if ( m_nDelay < 80 )
						{
							m_nDelay = 80;
						}
						MESSAGEBODYWL stMsgBodyWl;
						fnDecode6BitBuf(lpPacketMsg->szEncodeData, (char*)&stMsgBodyWl, sizeof(MESSAGEBODYWL));

						if ( lpPacketMsg->stDefMsg.wSeries == 0 )
						{
							m_bInputLock = FALSE;
							SAFE_DELETE(lpPacketMsg);
							return FALSE;
						}

						if ( LOWORD(stMsgBodyWl.nTag2) )
						{
							m_nDelay += m_bDelStruckCnt*15;
							// 2초동안 걷게 만든다(바로 뛰지 못하도록).
							m_dwCanRunTick = timeGetTime();
						}

						if ( lpPacketMsg->stDefMsg.wIdent == SM_STRUCK2 )
						{
							LPPACKETMSG	lpPacketMsgAdd = new PACKETMSG;
							memcpy(lpPacketMsgAdd , lpPacketMsg, sizeof(PACKETMSG));
							lpPacketMsgAdd->stDefMsg.wIdent = SM_STRUCK;
							m_xPacketQueue.PushQ((BYTE*)lpPacketMsgAdd);
						}

						break;	
					}
					case SM_RUSH:
					{
						if ( g_dwCurrTime - m_nTimerAfterImg > 1100 )
						{
							m_nAfterPosX = m_nPosX;
							m_nAfterPosY = m_nPosY;
							m_nTimerAfterImg = g_dwCurrTime;
						}
						m_bPahwangbo = FALSE;
						m_bInputLock = TRUE;
						OnRush(lpPacketMsg);
						m_pxMap->ScrollMap(m_bMoveDir, m_dwCurrFrame-m_dwFstFrame, m_bMoveSpeed);
						break;
					}
					case SM_RUSH2:
					{
						m_bPahwangbo = TRUE;
						m_bInputLock = TRUE;
						INT nWaveNum = _SKILL_PAWHANGBO * 10 + 10000;
						g_SoundManager.SndmngrPlayWavSound(nWaveNum, m_nPosX, m_nPosY);
						OnRush(lpPacketMsg);
						m_pxMap->ScrollMap(m_bMoveDir, m_dwCurrFrame-m_dwFstFrame, m_bMoveSpeed);
						break;
					}
					case SM_RUSHKUNG:
					{
						m_bInputLock = TRUE;
						OnRushKung(lpPacketMsg);
						m_pxMap->ScrollMap(m_bMoveDir, m_dwCurrFrame-m_dwFstFrame, m_bMoveSpeed);
						break;
					}
					case SM_BACKSTEP:
					{
						m_bInputLock = TRUE;
						OnBackStep(lpPacketMsg);
						m_pxMap->ScrollMap(m_bMoveDir, m_dwCurrFrame-m_dwFstFrame, m_bMoveSpeed);			
						break;
					}
					case SM_BACKSTEP2:
					{
						m_bIsSturn = TRUE;
						m_bInputLock = TRUE;
						OnBackStep(lpPacketMsg);
						m_pxMap->ScrollMap(m_bMoveDir, m_dwCurrFrame-m_dwFstFrame, m_bMoveSpeed);			
						break;
					}
					case SM_THROWDOT:			
					{
						OnThrowDot(lpPacketMsg);
						break;
					}
					case SM_MAGICFIRE:		
					{	
						OnMagicFire(lpPacketMsg);	
						bRet = FALSE;
						break;	
					}
					case SM_LIGHTING:			
					{	
						OnLighting(lpPacketMsg);
						bRet = FALSE;
						break;	
					}
					case SM_MAGICFIRE2:
					{
						OnMagicFire2(lpPacketMsg);			
						bRet = FALSE;
						break;	
					}
					case SM_SPACEMOVE_SHOW:		
					case SM_SPACEMOVE_SHOW2:	
					case SM_PULL_SHOW:
					{	
						OnSpaceMoveShow(lpPacketMsg);
						break;	
					}
					case SM_SPACEMOVE_HIDE:		
					case SM_SPACEMOVE_HIDE2:	
					{	
						OnSpaceMoveHide(lpPacketMsg);		
						break;	
					}
					default:
					{										
						break;	
					}
				}
				
				SAFE_DELETE(lpPacketMsg);

				if ( m_bIsDead )
				{
					SetMotionFrame(_MT_DIE, m_bCurrDir);
					m_dwCurrFrame = m_dwEndFrame - 1;
				}
			}
		}
	}

	return bRet;
}



/******************************************************************************************************************

	함수명 : CMyHero::SetOldPosition()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CMyHero::SetOldPosition()
{
	if ( m_bIsDead )
	{
		return FALSE;
	}

	m_nShiftTileX		= 0;
	m_nShiftTileY		= 0;
	m_nShiftPixelX		= 0;
	m_nShiftPixelY		= 0;
	m_nPosX				= m_nOldPosX;
	m_nPosY				= m_nOldPosY;
	m_bCurrDir			= m_bOldDir;
	m_dwCurrEffectFrame = 0;
	m_dwFstEffectFrame	= 0;
	m_dwEndEffectFrame	= 0;
	m_bEffectFrame		= 0;
	m_bBackStepFrame	= 0;
	m_bBackStepFrameCnt = 0;
	m_bIsMoved			= FALSE;
	m_bUseEffect		= FALSE;
	m_bUseSwordEffect	= FALSE;
	m_dwCurrFrame		= m_dwFstFrame;

	if ( m_stFeatureEx.bHorse == _HORSE_NONE )
	{
		if ( SetMotionFrame(_MT_STAND, m_bCurrDir) )
		{
			AdjustMyPostion();
			m_bMotionLock = FALSE;
			m_dwMotionLockTime = 0;
			return TRUE;
		}
	}
	else
	{
		if ( SetMotionFrame(_MT_HORSESTAND, m_bCurrDir) )
		{
			AdjustMyPostion();
			m_bMotionLock = FALSE;
			m_dwMotionLockTime = 0;
			return TRUE;
		}
	}

	return FALSE;
}



/******************************************************************************************************************

	함수명 : CMyHero::CheckMyPostion()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CMyHero::CheckMyPostion()
{
	if ( m_nPosX != m_pxMap->m_nStartViewTileX + _GAPX_TILE_CHAR_MAP ||
		 m_nPosY != m_pxMap->m_nStartViewTileY + _GAPY_TILE_CHAR_MAP )
	{
		return FALSE;
	}
	return TRUE;
}



/******************************************************************************************************************

	함수명 : CMyHero::AdjustMyPostion()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CMyHero::AdjustMyPostion()
{
	m_pxMap->SetStartViewTile(m_nPosX-_GAPX_TILE_CHAR_MAP, m_nPosY-_GAPY_TILE_CHAR_MAP);
	g_xGameProc.m_xInterface.SetViewMode();
	m_pxMap->LoadNewMapBuffer();
}



/******************************************************************************************************************

	함수명 : CMyHero::SetMotionState()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : BYTE bMtn
	         BYTE bDir
	         LPPOINT lpptTarget
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CMyHero::SetMotionState(BYTE bMtn, BYTE bDir, INT nMouseTargetID, BOOL bIsDead, LPPOINT lpptPos, SHORT shSkill)
{
	if ( m_bIsDead )
	{
		SetMotionFrame(_MT_DIE, m_bCurrDir);
		m_dwCurrFrame = m_dwEndFrame - 1;
		return;
	}

	if ( m_bCurrMtn == _MT_DIE )
	{
		return;
	}

	if ( GetCharState() == _STATE_GRAY )
	{
		return;
	}

	switch ( bMtn )
	{
		case _MT_WALK:
		case _MT_HORSEWALK:
		{
			if ( lpptPos )
			{
				POINT ptNext;
				BYTE  bDirCnt;

				if ( !CanWalk() )
				{
					return;
				}

				for ( bDirCnt = 0; bDirCnt < _MAX_DIRECTION; bDirCnt++ )
				{
					m_pxMap->GetNextTileCanMove(lpptPos->x, lpptPos->y, bDirCnt, 1, &ptNext);
					if ( !m_pxMap->IsDoorOpen(ptNext.x, ptNext.y) )
					{
						g_xClientSocket.SendOpenDoor(ptNext.x, ptNext.y, m_pxMap->GetDoor(ptNext.x, ptNext.y));
						break;
					}
				}

				g_xClientSocket.SendActMsg(CM_WALK, lpptPos->x, lpptPos->y, bDir, m_dwLastMoveTime);

				m_bMotionLock = m_bInputLock = TRUE;
				m_nOldPosX = m_nPosX;
				m_nOldPosY = m_nPosY;
				m_bOldDir  = m_bCurrDir;

				SetMotionFrame(bMtn, bDir);
				m_bMoveSpeed = _SPEED_WALK;

				m_pxMap->ScrollMap(m_bMoveDir, m_dwCurrFrame-m_dwFstFrame, m_bMoveSpeed);
			}
			break;
		}
		case _MT_RUN:
		case _MT_HORSERUN:
		{
			if ( lpptPos )
			{
				POINT ptNext;
				POINT ptStart;
				BYTE  bDirCnt;

				if ( !CanWalk() )
				{
					return;
				}

				if ( bMtn == _MT_RUN )
				{
					m_bMoveSpeed = _SPEED_RUN;
				}
				else
				{
					m_bMoveSpeed = _SPEED_HORSERUN;
				}
				
				m_pxMap->GetNextTileCanMove(m_nPosX, m_nPosY, bDir, 1, &ptStart);
				for ( bDirCnt = 0; bDirCnt < _MAX_DIRECTION; bDirCnt++ )
				{
					for ( INT nSpeedCnt = 0; nSpeedCnt < m_bMoveSpeed; nSpeedCnt++ )
					{
						m_pxMap->GetNextTileCanMove(ptStart.x, ptStart.y, bDirCnt, nSpeedCnt+1, &ptNext);
						if ( !m_pxMap->IsDoorOpen(ptNext.x, ptNext.y) )
						{
							g_xClientSocket.SendOpenDoor(ptNext.x, ptNext.y, m_pxMap->GetDoor(ptNext.x, ptNext.y));
							break;
						}
					}
				}
				
				g_xClientSocket.SendActMsg(CM_RUN, lpptPos->x, lpptPos->y, bDir, m_dwLastMoveTime);
				m_bMotionLock = m_bInputLock = TRUE;
				m_nOldPosX = m_nPosX;
				m_nOldPosY = m_nPosY;
				m_bOldDir  = m_bCurrDir;

				SetMotionFrame(bMtn, bDir);

				m_pxMap->ScrollMap(m_bMoveDir, m_dwCurrFrame-m_dwFstFrame, m_bMoveSpeed);			
			}
			break;
		}
		case _MT_ONEHSWING:
		{
			if ( lpptPos && CanNextHit() )
			{
				m_bMotionLock	= m_bInputLock = TRUE;
				m_bWarMode		= TRUE;
				m_dwWarModeTime	= 0;

				m_nOldPosX		= m_nPosX;
				m_nOldPosY		= m_nPosY;
				m_bOldDir		= m_bCurrDir;

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				// 곡괭이.
				if ( m_stFeature.bWeapon == 7 && nMouseTargetID == -1 )
				{
					if ( CheckDelay() == TRUE )
						m_dwLastHitUseTime = timeGetTime();
					else
						return;

					SetMotionFrame(g_xSpriteInfo.GetWeaponMtn(m_stFeature.bWeapon), bDir);
					g_xClientSocket.SendActMsg(CM_HEAVYHIT, m_nPosX, m_nPosY, m_bCurrDir, timeGetTime());

					m_bAutoDig = TRUE;
				}
				else if ( m_stFeature.bWeapon == 34 || m_stFeature.bWeapon == 35 || m_stFeature.bWeapon == 36 || m_stFeature.bWeapon == 37)
				{
					SetMotionFrame(_MT_ONEVSWING, bDir);
					g_xClientSocket.SendThrowMsg(CM_THROWHIT, lpptPos->x, lpptPos->y, nMouseTargetID);
				}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				else if ( m_bFireHitCnt == 1 && m_stAbility.wMP > 7 )
				{
					if ( CheckDelay() == TRUE )
						m_dwLastHitUseTime = timeGetTime();
					else
						return;

					SetMotionFrame(g_xSpriteInfo.GetWeaponMtn(m_stFeature.bWeapon), bDir);
					m_bUseSwordEffect = TRUE;
					LoadEffect(&g_xGameProc.m_xImage, _SKILL_FIRESWORD, bDir);
					g_xClientSocket.SendActMsg(CM_FIREHIT, lpptPos->x, lpptPos->y, bDir, timeGetTime());
					m_bFireHitCnt = 2;
				}
				// 돌려베기.
				else if ( m_bBackSwingCnt == 1 && m_stAbility.wMP > 11 )
				{
					if ( CheckDelay() == TRUE )
						m_dwLastHitUseTime = timeGetTime();
					else
						return;

					SetMotionFrame(_MT_WHEELWIND, bDir);
					m_bUseSwordEffect = TRUE;
					LoadEffect(&g_xGameProc.m_xImage, _SKILL_JUMPSHOT, bDir);
					g_xClientSocket.SendActMsg(CM_BKSHIT, lpptPos->x, lpptPos->y, bDir, timeGetTime());
					m_bBackSwingCnt = 2;
				}
				// 연월참
				else if ( m_bRandSwingCnt == 1 && m_stAbility.wMP > 15 )
				{
					if ( CheckDelay() == TRUE )
						m_dwLastHitUseTime = timeGetTime();
					else
						return;

					SetMotionFrame(_MT_RANDSWING, bDir);
					m_bUseSwordEffect = TRUE;
					LoadEffect(&g_xGameProc.m_xImage, _SKILL_RANDSWING, bDir);
					g_xClientSocket.SendActMsg(CM_RANDHIT, lpptPos->x, lpptPos->y, bDir, timeGetTime());
					m_bRandSwingCnt = 2;
				}
				// 고급연월참
				else if ( m_bHRandSwingCnt == 1 && m_stAbility.wMP > 15 )
				{
					if ( CheckDelay() == TRUE )
						m_dwLastHitUseTime = timeGetTime();
					else
						return;

					SetMotionFrame(_MT_RANDSWING, bDir);
					m_bUseSwordEffect = TRUE;
					LoadEffect(&g_xGameProc.m_xImage, _SKILL_RANDSWING_HIGH, bDir);
					g_xClientSocket.SendActMsg(CM_HIGH_RANDSWINGHIT, lpptPos->x, lpptPos->y, bDir, timeGetTime());
					m_bHRandSwingCnt = 2;
				}
				else if ( m_bUseErgum && g_xGameProc.TargetInLongAttack(bDir) )
				{
					if ( CheckDelay() == TRUE )
						m_dwLastHitUseTime = timeGetTime();
					else
						return;

					SetMotionFrame(g_xSpriteInfo.GetWeaponMtn(m_stFeature.bWeapon), bDir);
					m_bUseSwordEffect = TRUE;
					LoadEffect(&g_xGameProc.m_xImage, _SKILL_ERGUM, bDir);
					g_xClientSocket.SendActMsg(CM_LONGHIT, lpptPos->x, lpptPos->y, bDir, timeGetTime());
				}
				else if ( m_bUseHErgum && g_xGameProc.TargetInLongAttack(bDir) )
				{
					if ( CheckDelay() == TRUE )
						m_dwLastHitUseTime = timeGetTime();
					else
						return;

					SetMotionFrame(g_xSpriteInfo.GetWeaponMtn(m_stFeature.bWeapon), bDir);
					m_bUseSwordEffect = TRUE;
					LoadEffect(&g_xGameProc.m_xImage, _SKILL_ERGUM_HIGH, bDir);
					g_xClientSocket.SendActMsg(CM_LONGHIT, lpptPos->x, lpptPos->y, bDir, timeGetTime());
				}
				else if ( m_bYedoCnt == 1 )
				{
					if ( CheckDelay() == TRUE )
						m_dwLastHitUseTime = timeGetTime();
					else
						return;

					SetMotionFrame(g_xSpriteInfo.GetWeaponMtn(m_stFeature.bWeapon), bDir);
					m_bUseSwordEffect = TRUE;
					LoadEffect(&g_xGameProc.m_xImage, _SKILL_YEDO, bDir);
					g_xClientSocket.SendActMsg(CM_POWERHIT, lpptPos->x, lpptPos->y, bDir, timeGetTime());
					m_bYedoCnt = 2;
				}
				else if ( m_bHYedoCnt == 1 )
				{
					if ( CheckDelay() == TRUE )
						m_dwLastHitUseTime = timeGetTime();
					else
						return;

					SetMotionFrame(g_xSpriteInfo.GetWeaponMtn(m_stFeature.bWeapon), bDir);
					m_bUseSwordEffect = TRUE;
					LoadEffect(&g_xGameProc.m_xImage, _SKILL_YEDO_HIGH, bDir);
					g_xClientSocket.SendActMsg(CM_POWERHIT, lpptPos->x, lpptPos->y, bDir, timeGetTime());
					m_bHYedoCnt = 2;
				}
				else if ( m_bUseBanwol && m_stAbility.wMP > 3 )
				{
					if ( CheckDelay() == TRUE )
						m_dwLastHitUseTime = timeGetTime();
					else
						return;

					SetMotionFrame(g_xSpriteInfo.GetWeaponMtn(m_stFeature.bWeapon, FALSE), bDir);
					m_bUseSwordEffect = TRUE;
					LoadEffect(&g_xGameProc.m_xImage, _SKILL_BANWOL, bDir);
					g_xClientSocket.SendActMsg(CM_WIDEHIT, lpptPos->x, lpptPos->y, bDir, timeGetTime());
				}
				else if ( m_bUseManwol && m_stAbility.wMP > 7 )
				{
					if ( CheckDelay() == TRUE )
						m_dwLastHitUseTime = timeGetTime();
					else
						return;

					SetMotionFrame(g_xSpriteInfo.GetWeaponMtn(m_stFeature.bWeapon, FALSE), bDir);
					m_bUseSwordEffect = TRUE;					
					LoadEffect(&g_xGameProc.m_xImage, _SKILL_MANWOL, 0);
					g_xClientSocket.SendActMsg(CM_MANWOL, lpptPos->x, lpptPos->y, bDir, timeGetTime());
				}
				else if ( m_bUseHManwol && m_stAbility.wMP > 7 )
				{
					if ( CheckDelay() == TRUE )
						m_dwLastHitUseTime = timeGetTime();
					else
						return;

					SetMotionFrame(g_xSpriteInfo.GetWeaponMtn(m_stFeature.bWeapon, FALSE), bDir);
					m_bUseSwordEffect = TRUE;					
					LoadEffect(&g_xGameProc.m_xImage, _SKILL_MANWOL_HIGH, 0);
					g_xClientSocket.SendActMsg(CM_MANWOL, lpptPos->x, lpptPos->y, bDir, timeGetTime());
				}
				else if ( m_bMang && m_stAbility.wMP > 3 )
				{
					if ( CheckDelay() == TRUE )
						m_dwLastHitUseTime = timeGetTime();
					else
						return;
					
					g_xClientSocket.SendActMsg(CM_HIGHWIDEHIT, lpptPos->x, lpptPos->y, bDir, timeGetTime());
				}
				else
				{
					if ( CheckDelay() == TRUE )
						m_dwLastHitUseTime = timeGetTime();
					else
						return;

					if ( g_xGameProc.m_xInterface.m_xStatusWnd.m_stEquipItem[_U_WEAPON].xItem.m_stItemInfo.Desc[11] > 0 )
					{
						// 속성공격 Effect.
						WORD wSkillNum;
						wSkillNum = _SKILL_GUMGI_FIRE + g_xGameProc.m_xInterface.m_xStatusWnd.m_stEquipItem[_U_WEAPON].xItem.m_stItemInfo.Desc[11] - 1;
						m_bUseSwordEffect = TRUE;
						LoadEffect(&g_xGameProc.m_xImage, wSkillNum, bDir);
					}
					else if (g_xGameProc.m_xInterface.m_xStatusWnd.m_stEquipItem[_U_WEAPON].xItem.m_stItemInfo.stStdItem.wAtomDC > 0)
					{
						WORD wSkillNum;
						wSkillNum = _SKILL_GUMGI_FIRE + g_xGameProc.m_xInterface.m_xStatusWnd.m_stEquipItem[_U_WEAPON].xItem.m_stItemInfo.stStdItem.bAtomDCType - 1;
						m_bUseSwordEffect = TRUE;
						LoadEffect(&g_xGameProc.m_xImage, wSkillNum, bDir);
					}

					// 마석 착용시 공격 이펙트 2006.10.24
					else if( g_xGameProc.m_xInterface.m_xStatusWnd.m_stEquipItem[ _U_CHARM ].xItem.m_stItemInfo.stStdItem.FuncType > 0 )
					{
						WORD wSkillNum;
						wSkillNum = _SKILL_GUMGI_FIRE + g_xGameProc.m_xInterface.m_xStatusWnd.m_stEquipItem[_U_CHARM].xItem.m_stItemInfo.stStdItem.FuncType - 1;
						m_bUseSwordEffect = TRUE;
						LoadEffect(&g_xGameProc.m_xImage, wSkillNum, bDir);
					}

					SetMotionFrame(g_xSpriteInfo.GetWeaponMtn(m_stFeature.bWeapon), bDir);
					g_xClientSocket.SendHitMsg(CM_HIT, lpptPos->x, lpptPos->y, bDir, 0, nMouseTargetID);

				}
			}
			break;
		}
		case _MT_MOODEPO:
		{
			if ( lpptPos )
			{
				m_nOldPosX		= m_nPosX;
				m_nOldPosY		= m_nPosY;
				m_bOldDir		= m_bCurrDir;

				g_xClientSocket.SendSpellMsg(shSkill, bDir, 0, 0);
				// 무태보 시간값 기록.
				m_dwLastRushTime = timeGetTime();
				m_bMotionLock = m_bInputLock = TRUE;
				m_bWarMode	= TRUE;
			}

			break;
		}/*
		case _MT_WHEELWIND:
		{
			if ( lpptPos )		
			{
				m_nOldPosX		= m_nPosX;
				m_nOldPosY		= m_nPosY;
				m_bOldDir		= m_bCurrDir;

				g_xClientSocket.SendSpellMsg(shSkill, lpptPos->x, lpptPos->y, nMouseTargetID);
				m_bMotionLock = m_bInputLock = m_bWarMode = TRUE;

				SetMotionFrame(_MT_WHEELWIND, bDir);
				LoadEffect(&g_xGameProc.m_xImage, _SKILL_JUMPSHOT, bDir);
				m_bUseSwordEffect = TRUE;
			}
			break;
		}
		case _MT_RANDSWING:
		{
			if ( lpptPos )		
			{
				m_nOldPosX		= m_nPosX;
				m_nOldPosY		= m_nPosY;
				m_bOldDir		= m_bCurrDir;

				g_xClientSocket.SendSpellMsg(shSkill, lpptPos->x, lpptPos->y, nMouseTargetID);
				m_bMotionLock = m_bInputLock = m_bWarMode = TRUE;

				SetMotionFrame(_MT_RANDSWING, bDir);
				LoadEffect(&g_xGameProc.m_xImage, _SKILL_RANDSWING, bDir);
				m_bUseSwordEffect = TRUE;
			}

			break;
		}*/
		case _MT_BACKDROPKICK:
		{
			if ( lpptPos )		
			{
				m_nOldPosX		= m_nPosX;
				m_nOldPosY		= m_nPosY;
				m_bOldDir		= m_bCurrDir;
//				g_xClientSocket.SendSpellMsg(125, bDir, 0, 0);

				g_xClientSocket.SendSpellMsg(shSkill, bDir, 0, 0);
				m_dwLastKickTime = timeGetTime();
				m_bMotionLock = m_bInputLock = m_bWarMode = TRUE;
				SetMotionFrame(_MT_BACKDROPKICK, bDir);

				// 무상각 소리.
				g_SoundManager.SndmngrPlayWavSound(_SKILL_KICK*10 + 10000, m_nPosX, m_nPosY);
			}
			break;
		}
		case _MT_SPELL2:
		case _MT_SPELL1:
		{
			if ( lpptPos )
			{
				m_nOldPosX		= m_nPosX;
				m_nOldPosY		= m_nPosY;
				m_bOldDir		= m_bCurrDir;

				g_xClientSocket.SendSpellMsg(shSkill, lpptPos->x, lpptPos->y, nMouseTargetID);

				m_bMotionLock = m_bInputLock = TRUE;
				m_bWarMode	= TRUE;

				if ( m_nCurrMagicID == _SKILL_FIREBALL	   || m_nCurrMagicID == _SKILL_FIREBALL2	|| m_nCurrMagicID == _SKILL_FIRE	   || m_nCurrMagicID == _SKILL_SHOOTLIGHTEN     ||
					 m_nCurrMagicID == _SKILL_HANGMAJINBUB || m_nCurrMagicID== _SKILL_DEJIWONHO	    || m_nCurrMagicID == _SKILL_FIRECHARM  || m_nCurrMagicID == _SKILL_SINSU		    ||
					 m_nCurrMagicID == _SKILL_BIGCLOAK	   || m_nCurrMagicID == _SKILL_ICE	  	    || m_nCurrMagicID == _SKILL_ICEBOLT	   || m_nCurrMagicID == _SKILL_SUPERICEBOLT     || 
					 m_nCurrMagicID == _SKILL_MAGICARROW   || m_nCurrMagicID == _SKILL_MOONOK	    || m_nCurrMagicID == _SKILL_MOONCHAM   ||
					 m_nCurrMagicID == _SKILL_POWERUP	   || m_nCurrMagicID == _SKILL_MAGICUP		|| m_nCurrMagicID == _SKILL_MAGICUP_FIRE || m_nCurrMagicID == _SKILL_MAGICUP_ICE||m_nCurrMagicID==_SKILL_MAGICUP_LIGHTENING  || m_nCurrMagicID==_SKILL_MAGICUP_WIND	 || 
					 m_nCurrMagicID == _SKILL_HANDWIND	   || m_nCurrMagicID == _SKILL_ANTIMAGIC_FIRE||m_nCurrMagicID ==_SKILL_ANTIMAGIC_ICE||m_nCurrMagicID==_SKILL_ANTIMAGIC_LIGHTENING|| m_nCurrMagicID==_SKILL_ANTIMAGIC_WIND||
					 m_nCurrMagicID == _SKILL_WITH_FIRE    ||
					 m_nCurrMagicID == _SKILL_WITH_ICE     ||		 
					 m_nCurrMagicID == _SKILL_WITH_LIGHT   ||	
					 m_nCurrMagicID == _SKILL_WITH_WIND    ||	
					 m_nCurrMagicID == _SKILL_WITH_DEF	   ||	
					 m_nCurrMagicID == _SKILL_WITH_MAGIC   ||	
					 m_nCurrMagicID == _SKILL_WITH_ATT	   ||
					 m_nCurrMagicID == _SKILL_CONCENFIREBALL || 
					 m_nCurrMagicID == _SKILL_CROSS_ICE	   ||
					 m_nCurrMagicID == _SKILL_FIREBALL10   ||
					 m_nCurrMagicID == _SKILL_PULL		   ||
					 m_nCurrMagicID == _SKILL_MYULSAL	   || 
					 m_nCurrMagicID == _SKILL_MOONCHAM_HIGH|| 
					 m_nCurrMagicID == _SKILL_JIKSUNGYE	   || 
					 m_nCurrMagicID == _SKILL_INHALEHP )
				{
					LoadEffect(&g_xGameProc.m_xImage, m_nCurrMagicID, bDir);
				}
				else if ( m_nCurrMagicID == _SKILL_CHANGEPOSITION || m_nCurrMagicID == _SKILL_DEJIWONHO_HIGH ||
					      m_nCurrMagicID == _SKILL_JISOKGYE		  || m_nCurrMagicID == _SKILL_BALSACHE ||
						  m_nCurrMagicID == _SKILL_CLOAK_HIGH )
				{
					LoadEffect(&g_xGameProc.m_xImage, m_nCurrMagicID, 0);
				}
				else
				{
					LoadEffect(&g_xGameProc.m_xImage, m_nCurrMagicID);
				}

				m_bUseEffect = TRUE;

 				if ( m_nCurrMagicID == _SKILL_SHOWHP)
					m_bEffectFrameCnt = 20;
//				else if ( m_nCurrMagicID == _SKILL_LIGHTFLOWER )
//					m_bEffectFrameCnt = 11;
				else if ( m_nCurrMagicID == _SKILL_LIGHTENING )			
					m_bEffectFrameCnt = 13;
				else if ( m_nCurrMagicID == _SKILL_SHIELD && !(m_nCharState & 0X100000) )
					m_dwShieldTick = timeGetTime();
				else if ( m_nCurrMagicID == _SKILL_SHIELD_HIGH && !(m_nCharState & 0X00010000) )
					m_dwShieldTick = timeGetTime();
				else if ( m_nCurrMagicID == _SKILL_DOSASHIELD && !(m_nCharState & 0X00040000) )
					m_dwShieldTick = timeGetTime();
				else if ( m_nCurrMagicID == _SKILL_TRANSFORM )						
					m_bEffectFrameCnt = 14;

				SetMotionFrame(bMtn, bDir);

				// 딜레이를 줄인다.
				if ( m_nCurrMagicID == _SKILL_SMALLSPACEMOVE )
				{
					m_nDelay = 40;
				}
			}
			break;
		}
		case _MT_CUT:
		{
			m_bMotionLock = m_bInputLock = TRUE;
			SetMotionFrame(bMtn, bDir);

			m_nOldPosX		= m_nPosX;
			m_nOldPosY		= m_nPosY;
			m_bOldDir		= m_bCurrDir;

			g_xClientSocket.SendActMsg(CM_SITDOWN, m_nPosX, m_nPosY, bDir);
			if ( nMouseTargetID && lpptPos && bIsDead )
			{
				g_xClientSocket.SendButchAnimal(m_nPosX, m_nPosY, bDir, nMouseTargetID);
			}
			break;
		}
		case _MT_HORSESTAND:
		case _MT_STAND:
		{
			if ( bDir != m_bCurrDir )	
			{
				g_xClientSocket.SendActMsg(CM_TRUN, m_nPosX, m_nPosY, bDir);
				m_bMotionLock = m_bInputLock = TRUE;
				SetMotionFrame(bMtn, bDir);
			}
			break;
		}
	}

	m_dwMotionLockTime	= 0;
}



/******************************************************************************************************************

	함수명 : CMyHero::UpdateMotionState()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : INT nLoopTime
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CMyHero::UpdateMotionState(INT nLoopTime, BOOL bIsMoveTime)
{
	if ( m_bMotionLock ) 
		m_dwMotionLockTime += nLoopTime;

	if ( m_bWarMode ) 
		m_dwWarModeTime += nLoopTime;

	m_nABlendCurrDelay += nLoopTime;
	if ( m_nABlendCurrDelay >= m_nABlendDelay )
	{
		m_nABlendCurrDelay = 0;
		m_nABlendDelay	   = 0;
		m_bABlendRev	   = FALSE;
	}

	m_nShieldCurrDelay += nLoopTime;
	if ( m_nShieldCurrDelay > 150 )  
	{
		m_bShieldCurrFrm++;
		m_nShieldCurrDelay = 0;

		if ( m_bShieldCurrFrm > 2 )
			m_bShieldCurrFrm = 0;
	}

	if ( m_bCurrMtn == _MT_DIE && m_dwCurrFrame >= m_dwEndFrame-1 )
	{
		m_bIsDead = TRUE;
		m_bHPPercent = 0;
		m_wHP = 0;
		m_stAbility.wHP = 0;
	}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if ( m_bViewDigFragment )
	{
		if ( m_bCurrMtn == g_xSpriteInfo.GetWeaponMtn(m_stFeature.bWeapon) && m_dwCurrFrame == m_dwFstFrame + 3 )
		{
			CMagic* pxMagic;
			pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_EVENT_DUST, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this, -1) )
			{
				g_xGameProc.m_xMagicList.Insert(pxMagic);	
			}
			else
			{
				delete pxMagic;
			}

			LPEVENTIMG	pstEvent = g_xGameProc.FindEvent(_ET_PILESTONES, m_nPosX, m_nPosY);
			
			if ( pstEvent)
			{
				pstEvent->wFrameNum++;
				if ( pstEvent->wFrameNum >= 234 )
				{
					pstEvent->wFrameNum = 234;
				}								
			}

			m_bViewDigFragment = FALSE;
		}
	}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	if ( UpdateMove(bIsMoveTime) )
	{
		UpdatePacketState();

		if ( m_bIsDead )
		{
			SetMotionFrame(_MT_DIE, m_bCurrDir);
			m_dwCurrFrame = m_dwEndFrame - 1;
			m_bInputLock  = TRUE;
		}

		return;
	}
	else
	{
		m_nCurrDelay += nLoopTime;

		if ( m_nCurrDelay > m_nDelay )
		{
			m_nCurrDelay  = 0;

			if ( m_dwCurrFrame < m_dwEndFrame )
			{
				m_dwCurrFrame++;

				PlayActSound();

				if ( (m_bCurrMtn == _MT_SPELL2 || m_bCurrMtn == _MT_SPELL1) && m_bUseEffect )
				{
					m_dwCurrEffectFrame++;
					m_bEffectFrame++;
				}
			}
		}

		UpdatePacketState();

		if ( m_bIsDead )
		{
			SetMotionFrame(_MT_DIE, m_bCurrDir);
			m_dwCurrFrame = m_dwEndFrame - 1;
			m_bInputLock  = TRUE;
			return;
		}

		// 연속적인 프레임 중에서 해야할일.
		if ( m_dwMotionLockTime > _MOTION_LOCKTIME )
		{
			m_dwMotionLockTime = 0;
			m_bMotionLock	   = FALSE;
		}

		if ( m_dwWarModeTime > _WARMODE_TIME )
		{
			m_dwWarModeTime = 0;
			m_bWarMode		= FALSE;
		}

		if ( (m_bCurrMtn == _MT_SPELL2) && m_bUseEffect )
		{
			if ( m_dwCurrFrame >= m_dwEndFrame-1 )
			{
				if ( m_dwCurrEffectFrame - m_dwFstEffectFrame <= (BYTE)(m_bEffectFrameCnt-2) )
				{
					m_nDelay = 70;
					m_dwCurrFrame = m_dwEndFrame - 2;
				}
			}
		}
		else if ( (m_bCurrMtn == _MT_SPELL1) && m_bUseEffect )
		{
			if ( m_dwCurrFrame >= m_dwEndFrame-3 && m_dwCurrFrame < m_dwEndFrame-2 )
			{
				if ( m_dwCurrEffectFrame - m_dwFstEffectFrame < (BYTE)(m_bEffectFrameCnt-4) )
				{
					m_dwCurrFrame = m_dwEndFrame - 4;
				}
			}
			else if ( m_dwCurrFrame >= m_dwEndFrame-2 && m_dwCurrFrame < m_dwEndFrame-1 )
			{
				m_nDelay = 200;
			}
			else if ( m_dwCurrFrame >= m_dwEndFrame-1 )
			{
				m_nDelay = 80;
			}
		}

		if ( m_dwCurrFrame >= m_dwEndFrame )
		{
			m_dwCurrEffectFrame = 0;	
			m_dwFstEffectFrame = 0;
			m_dwEndEffectFrame = 0;
			m_bEffectFrame = 0;
			m_bEffectFrameCnt = _DEFAULT_SPELLFRAME;
			m_bUseEffect = FALSE;
			m_bUseSwordEffect = FALSE;

			m_dwCurrFrame = m_dwEndFrame-1;


			if ( !m_bMotionLock || m_bInputLock )
			{
				m_bInputLock  = FALSE;
				if ( m_bIsDead )
				{
					SetMotionFrame(_MT_DIE, m_bCurrDir);
					m_dwCurrFrame = m_dwEndFrame - 1;
				}
				else if ( m_stFeatureEx.bHorse == _HORSE_NONE )
				{
					if ( m_bWarMode )
						SetMotionFrame(_MT_ATTACKMODE, m_bCurrDir);
					else
						SetMotionFrame(_MT_STAND, m_bCurrDir);
				}
				else
				{
					SetMotionFrame(_MT_HORSESTAND, m_bCurrDir);
				}
			}

			if ( m_bCurrMtn == _MT_STAND || m_bCurrMtn == _MT_HORSESTAND || m_bCurrMtn == _MT_ATTACKMODE )
			{
				POINT ptMouse;
				GetCursorPos(&ptMouse);

				if ( PtInRect(&g_xMainWnd.m_rcWindow, ptMouse) )
				{
					ScreenToClient(g_xMainWnd.GetSafehWnd(), &ptMouse);
					m_bCanRun = FALSE;

					if ( HIBYTE(GetKeyState(VK_RBUTTON)) || ( HIBYTE(GetKeyState(VK_LBUTTON)) && HIBYTE(GetKeyState(VK_CONTROL))) )
					{
						OnRButtonDown(ptMouse);
					}
					else if ( HIBYTE(GetKeyState(VK_LBUTTON)) )
					{
						if ( g_xGameProc.m_pxMouseTargetActor )
						{
							BOOL bIsDead = FALSE;
							if ( g_xGameProc.m_pxMouseTargetActor->m_stFeature.bGender == _GENDER_MAN || g_xGameProc.m_pxMouseTargetActor->m_stFeature.bGender == _GENDER_WOMAN )
							{
								if ( g_xGameProc.m_pxMouseTargetActor->m_bCurrMtn == _MT_DIE || g_xGameProc.m_pxMouseTargetActor->m_bIsDead )
								{
									bIsDead = TRUE;
								}
							}
							else if ( g_xGameProc.m_pxMouseTargetActor->m_stFeature.bGender == _GENDER_MON )
							{
								if ( g_xGameProc.m_pxMouseTargetActor->m_bCurrMtn == _MT_MON_DIE || g_xGameProc.m_pxMouseTargetActor->m_bIsDead )
								{
									bIsDead = TRUE;
								}
							}

							if ( g_xGameProc.m_pxMouseTargetActor->m_stFeature.bGender == _GENDER_MAN || g_xGameProc.m_pxMouseTargetActor->m_stFeature.bGender == _GENDER_WOMAN )
							{
								if ( HIBYTE(GetKeyState(VK_SHIFT)) )
								{
									POINT ptTaretTilePos = {g_xGameProc.m_pxMouseTargetActor->m_nPosX, g_xGameProc.m_pxMouseTargetActor->m_nPosY};
									OnLButtonDown(ptMouse, g_xGameProc.m_pxMouseTargetActor->m_nIdentity, bIsDead , &ptTaretTilePos);
								}
							}
							else if ( g_xGameProc.m_pxMouseTargetActor->m_stFeature.bGender == _GENDER_MON )
							{
								// 경비병도 안때리게.
								BOOL bIsGuard = FALSE;
								BYTE bDress   = g_xGameProc.m_pxMouseTargetActor->m_stFeature.bDress;

								if ( bDress ==  26 || bDress ==  86 || bDress == 113 || bDress == 114 || 
									 bDress == 115 || bDress == 165 || bDress == 166 || bDress == 26 )
								{
									bIsGuard = TRUE;
								}

								if ( bIsGuard || strchr(g_xGameProc.m_pxMouseTargetActor->m_szName, '(') )
								{
									if ( HIBYTE(GetKeyState(VK_SHIFT)) )
									{
										POINT ptTaretTilePos = {g_xGameProc.m_pxMouseTargetActor->m_nPosX, g_xGameProc.m_pxMouseTargetActor->m_nPosY};
										OnLButtonDown(ptMouse, g_xGameProc.m_pxMouseTargetActor->m_nIdentity, bIsDead, &ptTaretTilePos);
									}
								}
								else
								{
									POINT ptTaretTilePos = {g_xGameProc.m_pxMouseTargetActor->m_nPosX, g_xGameProc.m_pxMouseTargetActor->m_nPosY};
									OnLButtonDown(ptMouse, g_xGameProc.m_pxMouseTargetActor->m_nIdentity, bIsDead, &ptTaretTilePos);
								}
							}
						}
						else
						{
							OnLButtonDown(ptMouse);
						}
					}
				}
			}
		}
	}
}




/******************************************************************************************************************

	함수명 : CMyHero::UpdateMove(BOOL bIsMoveTime)

	작성자 : 
	작성일 : 

	목적   : 
	입력   : BOOL bIsMoveTime
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CMyHero::UpdateMove(BOOL bIsMoveTime)
{
	if ( m_bCurrMtn == _MT_WALK || m_bCurrMtn == _MT_RUN || m_bCurrMtn == _MT_HORSEWALK || 
		 m_bCurrMtn == _MT_HORSERUN || m_bCurrMtn == _MT_MOODEPO || m_bCurrMtn == _MT_PUSHBACK )
	{
		m_nCurrDelay = 0;

		// 연속적인 프레임 중에서 해야할일.
		if ( m_dwMotionLockTime > _MOTION_LOCKTIME )
		{
			m_dwMotionLockTime = 0;
			m_bMotionLock	   = FALSE;
		}

		if ( m_dwWarModeTime > _WARMODE_TIME )
		{
			m_dwWarModeTime = 0;
			m_bWarMode		= FALSE;
		}

		if ( bIsMoveTime )
		{
			// 천천히 걷게 만든다.
			BYTE bMoveSkipLevel = 0;

			if ( m_bCurrMtn != _MT_MOODEPO && m_bCurrMtn != _MT_PUSHBACK )
			{
				if ( m_stAbility.wMaxWeight != 0 && m_stAbility.wWeight > m_stAbility.wMaxWeight )
				{
					bMoveSkipLevel = (BYTE)(m_stAbility.wWeight / m_stAbility.wMaxWeight);
				}

				if ( m_stAbility.bMaxWearWeight != 0 && m_stAbility.bWearWeight > m_stAbility.bMaxWearWeight )
				{
					bMoveSkipLevel = (BYTE)(m_stAbility.bWearWeight / m_stAbility.bMaxWearWeight);
				}
			}

			if ( bMoveSkipLevel > 0 )
			{
				bMoveSkipLevel++;
				m_dwCurrMoveSkip++;

				if ( m_dwCurrMoveSkip > 100000 )
				{
					m_dwCurrMoveSkip = 1;
				}

				if ( (m_dwCurrMoveSkip % bMoveSkipLevel) )
				{
					return FALSE;
				}
			}

			if ( m_bCurrMtn == _MT_PUSHBACK )
			{
				m_bBackStepFrame += 2;
				if ( m_bBackStepFrame >= m_bBackStepFrameCnt )
				{
					m_dwCurrFrame++;
					m_bBackStepFrame = m_bBackStepFrameCnt;
				}
			}
			else if ( m_bCurrMtn == _MT_MOODEPO )
			{
				m_dwCurrFrame += 2;
				if ( m_dwCurrFrame >= m_dwEndFrame )
				{
					m_dwCurrFrame = m_dwEndFrame;
				}

				// 밀다가 실패한경우이다. 원위치로 돌려준다.
				if ( m_bRushKung )
				{
					if ( m_dwCurrFrame > m_dwEndFrame - 3 )
					{
						m_bRushKung = FALSE;
						m_nOldPosX = m_nRushKungPosX;
						m_nOldPosY = m_nRushKungPosY;
						m_bOldDir  = m_bCurrDir;
						SetOldPosition();
						SetMotionFrame(_MT_ATTACKMODE, m_bCurrDir);
						return TRUE;
					}					
				}
			}
			else
			{
				m_dwCurrFrame++;
				PlayMoveSound();
			}

			if ( m_bCurrMtn == _MT_PUSHBACK )
			{
				if ( m_bBackStepFrame >= m_bBackStepFrameCnt-m_bMoveNextFrmCnt && !m_bIsMoved )
				{
					SetMoved();
					m_bIsMoved = TRUE;
				}
			}
			else
			{
				if ( m_dwCurrFrame >= m_dwEndFrame-m_bMoveNextFrmCnt && !m_bIsMoved )
				{
					SetMoved();
					m_bIsMoved = TRUE;
				}
			}
		}

		// 연속적인 프레임 중에서 해야할일.
		if ( m_dwCurrFrame >= m_dwEndFrame )
		{
			m_dwCurrFrame = m_dwEndFrame-1;
			m_bIsMoved = FALSE;
			m_pxMap->SetMovedTileBuffer(m_nShiftTileX, m_nShiftTileY);
			m_bMoveSpeed	= 0;
			m_nShiftPixelX	= 0;
			m_nShiftPixelY	= 0;
			m_nShiftTileX	= 0;
			m_nShiftTileY	= 0;
			m_bCanRun = FALSE;
			m_bBackStepFrame = 0;
			m_bBackStepFrameCnt = 0;

			if ( !m_bMotionLock && m_bInputLock )
			{
				m_bInputLock = FALSE;

				switch ( m_bCurrMtn )
				{
				case _MT_WALK:
				case _MT_RUN:
				case _MT_HORSEWALK:
				case _MT_HORSERUN:
					if ( CanRun() )
					{
						m_bCanRun = TRUE;
					}
					break;
				}

				if ( m_stFeatureEx.bHorse == _HORSE_NONE )
				{
					if ( m_bWarMode )
					{
						SetMotionFrame(_MT_ATTACKMODE, m_bCurrDir);
					}
					else		
					{
						SetMotionFrame(_MT_STAND, m_bCurrDir);
					}
				}
				else
				{
					SetMotionFrame(_MT_HORSESTAND, m_bCurrDir);
				}

				if ( m_bCurrMtn == _MT_STAND || m_bCurrMtn == _MT_HORSESTAND || m_bCurrMtn == _MT_ATTACKMODE )
				{
					POINT ptMouse;
					GetCursorPos(&ptMouse);

					if ( PtInRect(&g_xMainWnd.m_rcWindow, ptMouse) )
					{
						ScreenToClient(g_xMainWnd.GetSafehWnd(), &ptMouse);

						if ( HIBYTE(GetKeyState(VK_RBUTTON)) || ( HIBYTE(GetKeyState(VK_LBUTTON)) && HIBYTE(GetKeyState(VK_CONTROL))) )
						{
							OnRButtonDown(ptMouse);
						}
						else if ( HIBYTE(GetKeyState(VK_LBUTTON)) )
						{
							m_bCanRun = FALSE;

							if ( g_xGameProc.m_pxMouseTargetActor )
							{
								BOOL bIsDead = FALSE;
								if ( g_xGameProc.m_pxMouseTargetActor->m_stFeature.bGender == _GENDER_MAN || g_xGameProc.m_pxMouseTargetActor->m_stFeature.bGender == _GENDER_WOMAN )
								{
									if ( g_xGameProc.m_pxMouseTargetActor->m_bCurrMtn == _MT_DIE || g_xGameProc.m_pxMouseTargetActor->m_bIsDead )
									{
										bIsDead = TRUE;
									}
								}
								else if ( g_xGameProc.m_pxMouseTargetActor->m_stFeature.bGender == _GENDER_MON )
								{
									if ( g_xGameProc.m_pxMouseTargetActor->m_bCurrMtn == _MT_MON_DIE || g_xGameProc.m_pxMouseTargetActor->m_bIsDead )
									{
										bIsDead = TRUE;
									}
								}

								if ( g_xGameProc.m_pxMouseTargetActor->m_stFeature.bGender == _GENDER_MAN || g_xGameProc.m_pxMouseTargetActor->m_stFeature.bGender == _GENDER_WOMAN )
								{
									if ( HIBYTE(GetKeyState(VK_SHIFT)) )
									{
										POINT ptTaretTilePos = {g_xGameProc.m_pxMouseTargetActor->m_nPosX, g_xGameProc.m_pxMouseTargetActor->m_nPosY};
										OnLButtonDown(ptMouse, g_xGameProc.m_pxMouseTargetActor->m_nIdentity, bIsDead , &ptTaretTilePos);
									}
								}
								else if ( g_xGameProc.m_pxMouseTargetActor->m_stFeature.bGender == _GENDER_MON )
								{
									// 경비병도 안때리게.
									BOOL bIsGuard = FALSE;
									BYTE bDress   = g_xGameProc.m_pxMouseTargetActor->m_stFeature.bDress;

									if ( bDress ==  26 || bDress ==  86 || bDress == 113 || bDress == 114 || 
										 bDress == 115 || bDress == 165 || bDress == 166 || bDress == 26 )
									{
										bIsGuard = TRUE;
									}

									if ( bIsGuard || strchr(g_xGameProc.m_pxMouseTargetActor->m_szName, '(') )
									{
										if ( HIBYTE(GetKeyState(VK_SHIFT)) )
										{
											POINT ptTaretTilePos = {g_xGameProc.m_pxMouseTargetActor->m_nPosX, g_xGameProc.m_pxMouseTargetActor->m_nPosY};
											OnLButtonDown(ptMouse, g_xGameProc.m_pxMouseTargetActor->m_nIdentity, bIsDead, &ptTaretTilePos);
										}
									}
									else
									{
										POINT ptTaretTilePos = {g_xGameProc.m_pxMouseTargetActor->m_nPosX, g_xGameProc.m_pxMouseTargetActor->m_nPosY};
										OnLButtonDown(ptMouse, g_xGameProc.m_pxMouseTargetActor->m_nIdentity, bIsDead, &ptTaretTilePos);
									}
								}
							}
							else
							{
								OnLButtonDown(ptMouse);
							}
						}
						else
						{
							m_bCanRun = FALSE;
						}
					}
				}
			}
		}
		else
		{
			switch ( m_bCurrMtn )
			{
			case _MT_WALK:
			case _MT_RUN:
			case _MT_HORSEWALK:
			case _MT_HORSERUN:
			case _MT_MOODEPO:
				m_pxMap->ScrollMap(m_bMoveDir, m_dwCurrFrame-m_dwFstFrame, m_bMoveSpeed);			
				break;
			case _MT_PUSHBACK:
				m_pxMap->ScrollMap(m_bMoveDir, m_bBackStepFrame, m_bMoveSpeed);			
				break;
			}
		}
		
		return TRUE;
	}

	return FALSE;
}





/******************************************************************************************************************

	함수명 : CMyHero:DrawActor()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : BOOL bFocused
	         BOOL bShadowAblended
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CMyHero::DrawActor(BOOL bFocused, BOOL bShadowAblended, BOOL bUseScrnPos, BOOL bDrawShadow, BOOL bMyTwice)
{
	// 캐릭터 좌표는 고정.
	if ( m_bMyHeroSetted == FALSE )
	{
		return FALSE;
	}

	if ( g_xGameProc.m_bViewMode == _VIEW__WITH_INVEN )
	{
		m_nScrnPosX = _CHAR_CENTER_XPOS_INVEN - 24; 
		m_nScrnPosY = _CHAR_CENTER_YPOS_INVEN - 16;
	}
	else if ( g_xGameProc.m_bViewMode == _VIEW__WITH_STATUS )
	{
		m_nScrnPosX = _CHAR_CENTER_XPOS_STATUS - 24;
		m_nScrnPosY = _CHAR_CENTER_YPOS_STATUS - 16;
	}
	else
	{
		m_nScrnPosX = _CHAR_CENTER_XPOS - 24;
		m_nScrnPosY = _CHAR_CENTER_YPOS + 16;
	}

//	if ( CHero::DrawActor(m_pxMap, bFocused, bShadowAblended, bUseScrnPos, bDrawShadow) )
	if ( CHero::DrawActor(m_pxMap, bFocused, bShadowAblended, bUseScrnPos, bDrawShadow, bMyTwice ) )
		return TRUE;

	return FALSE;
}



/******************************************************************************************************************

	함수명 : CMyHero::GetPosMouseToTile()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : INT nXPos
	         INT nYPos
	출력   : POINT 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
POINT CMyHero::GetPosMouseToTile(INT nXPos, INT nYPos)
{
	POINT ptTilePos = { 0, 0 };

	if ( m_pxMap )
	{
		ptTilePos.x = m_pxMap->m_nStartViewTileX + (nXPos - m_pxMap->m_nViewPosX) / _CELL_WIDTH;
		ptTilePos.y = m_pxMap->m_nStartViewTileY + (nYPos - m_pxMap->m_nViewPosY) / _CELL_HEIGHT;
	}

	return ptTilePos;
}

POINT CMyHero::GetPosTileToMouse(INT nXPos, INT nYPos)
{
	POINT ptTilePos = { 0, 0 };

	if ( m_pxMap )
	{
		ptTilePos.x = nXPos * _CELL_WIDTH - m_pxMap->m_nStartViewTileX * _CELL_WIDTH + m_pxMap->m_nViewPosX;
		ptTilePos.y = nYPos * _CELL_HEIGHT - m_pxMap->m_nStartViewTileY * _CELL_HEIGHT + m_pxMap->m_nViewPosY;
	}

	return ptTilePos;
}

BOOL CMyHero::CanNextHit()
{
	DWORD	dwCurrTick;
	INT		nLevelFast;
	DWORD	dwNextHit;
	BOOL	bAttackSlow = FALSE;

	if ( ((m_nMinTemp370 & 0xF3A0) == 0x0120) && ((m_nMinTemp800 & 0x2837) == 0x0020 ) )
	{
		nLevelFast = min(m_nMinTemp370, m_stAbility.bLevel*14);
		nLevelFast = min(m_nMinTemp800, nLevelFast + m_shHitSpeed * 60);

		if ( m_stAbility.bHandWeight > m_stAbility.bMaxHandWeight )		
			bAttackSlow = TRUE;

		m_nDelayTemp1400 = m_nDelaySeed1400_1 * m_nDelaySeed1400_2 * m_nDelaySeed1400_3;
		m_nDelayTemp1500 = m_nDelaySeed1500_1 * m_nDelaySeed1500_2 * m_nDelaySeed1500_3;

		if ( ( (m_nDelayTemp1400 & 0x8A8F) == 0x0008 ) && ( (m_nDelayTemp1500 & 0x3FF8) == 0x05D8 ) )
		{
			if ( bAttackSlow )
				dwNextHit = m_nDelayTemp1400  - nLevelFast + m_nDelayTemp1500 ;
			else					
				dwNextHit = m_nDelayTemp1400  - nLevelFast;

			dwCurrTick = timeGetTime();

			if ( dwCurrTick - m_dwLastHitTime > dwNextHit )
			{
				m_dwLastHitTime = dwCurrTick;
				return TRUE;
			}
		}
	}

	return FALSE;
}


BOOL CMyHero::CanWalk()
{
	DWORD dwTime = timeGetTime();
	if ( dwTime - m_dwLastMoveTime < 600 )
	{
		while ( dwTime - m_dwLastMoveTime < 600 )
			dwTime = timeGetTime();
	}
	else 
	{
		m_dwLastMoveTime = dwTime;
	}
	m_dwLastMoveTime = dwTime;

	if ( timeGetTime() - m_dwLastSpellTime > m_dwMagicPKDelayTime )
	{
		return TRUE;
	}
	
	return FALSE;
}


BOOL CMyHero::CanRun()
{
	if ( m_stAbility.wHP < _RUN_MINHEALTH )
	{
		return FALSE;
	}

	// 맞고 나서는 잠시동안 뛸수 없다.
	if ( timeGetTime() - m_dwCanRunTick < 2200 )
	{
		return FALSE;
	}
	
	if ( (timeGetTime() - m_dwLastPKStruckTime < 3000) || (timeGetTime() - m_dwLastSpellTime < m_dwMagicPKDelayTime ) )
	{
		return FALSE;
	}
	
	return TRUE;
}





//---------------------------------------------------------------------------------------------------------------//
//  유저 입력함수.
//---------------------------------------------------------------------------------------------------------------//
/******************************************************************************************************************

	함수명 : CMyHero::OnLButtonDown()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : POINT ptMouse
	         INT nTargetID
	         POINT* lpptTargetPos
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CMyHero::OnLButtonDown(POINT ptMouse, INT nTargetID, BOOL bIsDead, POINT* lpptTargetPos)
{
	POINT ptTargetTile;
	POINT ptMouseTilePos;
	BYTE  bDir;

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	m_bAutoDig = FALSE;
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	// 포커스 문제
	if ( GetFocus() != g_xMainWnd.GetSafehWnd() )
		return FALSE;

	if ( g_xGameProc.m_dwInputDelayTime > 0 )
	{
		return TRUE;
	}

	if ( !g_xGameProc.m_bRender )		
	{
		return TRUE;
	}

	if ( m_nABlendDelay )
	{
		return TRUE;
	}

	if ( g_xGameProc.m_xNotice.IsActive() )
	{
		g_xGameProc.m_xNotice.OnButtonDown(ptMouse);
		return TRUE;
	}

	if ( g_xGameProc.m_xGameMsgBox.OnLButtonDown(ptMouse) )
	{
		return TRUE;
	}

	if ( g_xGameProc.m_xInterface.m_xGameOverWnd.GetGameWndActive() )
	{
		return TRUE;
	}

	if ( g_xGameProc.m_bDiceModeActive )
	{
		return TRUE;
	}

#ifdef _NEWINTERFACE

	if ( g_xGameProc.m_xInterface.m_bIsLargeChat )
	{
		if ( PtInRect(&g_xGameProc.m_xInterface.m_rcLargeChatRgn, ptMouse) )
		{
			return TRUE;
		}
	}

#endif

/*	if ( g_xGameProc.m_xInterface.OnLButtonDown(ptMouse) )
	{
		return TRUE;
	}*/
	INT nInterfaceWndInRect;
	nInterfaceWndInRect = g_xGameProc.m_xInterface.GetWindowInMousePos(ptMouse);
	if ( nInterfaceWndInRect != -1 )
	{
		if ( nInterfaceWndInRect == _WND_ID_STORE )
		{
			if ( g_xGameProc.m_xInterface.m_xStoreWnd.CanMove(ptMouse) )
			{
				return TRUE;
			}
		}
		else
		{
			return TRUE;
		}		
	}

	if ( g_xGameProc.m_xInterface.GetBeltNum(ptMouse) != -1 )
	{
		return TRUE;
	}

	if ( PtInRect(&g_xGameProc.m_xInterface.m_rcMain, ptMouse) )
	{
		return TRUE;
	}

/*	if ( g_xGameProc.m_xInterface.m_stCommonItem.bSetted && g_xGameProc.m_xInterface.m_stCommonItem.bWaitResponse && !g_xGameProc.m_xInterface.m_stCommonItem.bIsEquipItem )
	{
		return TRUE;
	}
*/
	if ( g_xGameProc.m_pxMouseTargetActor && 
		( g_xGameProc.m_pxMouseTargetActor->m_stFeature.bGender == _GENDER_NPC ||
		g_xGameProc.m_pxMouseTargetActor->m_stFeature.bGender == _GENDER_FLAG) )
	{
		return TRUE;
	}

	if ( !m_bMotionLock && !m_bInputLock )
	{
		INT nLeftMsgCnt = m_xPacketQueue.GetCount();
		if ( nLeftMsgCnt > 0 )
		{
			// 행동패킷일경우 함수를 종료한다.
			if ( UpdatePacketState() )
			{
				return TRUE;
			}
		}

		ptMouseTilePos = GetPosMouseToTile(ptMouse.x, ptMouse.y);
		bDir		   = m_pxMap->GetNextDirection(m_nPosX, m_nPosY, ptMouseTilePos.x, ptMouseTilePos.y);

		if ( m_nPosX == ptMouseTilePos.x && m_nPosY == ptMouseTilePos.y )
		{
			bDir = m_bCurrDir;
		}

		INT nLength;

		if ( lpptTargetPos ) 
		{
			nLength = (INT)sqrt((m_nPosX-lpptTargetPos->x)*(m_nPosX-lpptTargetPos->x) + (m_nPosY-lpptTargetPos->y)*(m_nPosY-lpptTargetPos->y));
		}
		else
		{
			nLength = (INT)sqrt((m_nPosX-ptMouseTilePos.x)*(m_nPosX-ptMouseTilePos.x) + (m_nPosY-ptMouseTilePos.y)*(m_nPosY-ptMouseTilePos.y));
		}

		BOOL bHasDot = FALSE;
		if ( m_stFeature.bWeapon == 34 || m_stFeature.bWeapon == 35 || m_stFeature.bWeapon == 36 || m_stFeature.bWeapon == 37 )
		{
			bHasDot = TRUE;
		}

		// 1. SHIFT.(강제 공격)
		if ( HIBYTE(GetKeyState(VK_SHIFT)) && !g_xGameProc.m_pxSavedTargetActor )
		{
			if ( m_stFeatureEx.bHorse == _HORSE_NONE )
			{
				if ( nTargetID != -1 && lpptTargetPos )
				{
					bDir = m_pxMap->GetNextDirection(m_nPosX, m_nPosY, lpptTargetPos->x, lpptTargetPos->y);
				}

				if ( bHasDot )
				{
					SetMotionState(_MT_ONEHSWING, bDir, nTargetID, bIsDead, &ptMouseTilePos);
				}
				else if ( m_bUseErgum && g_xGameProc.TargetInLongAttack(bDir) )
				{
					if ( m_stFeatureEx.bHorse == _HORSE_NONE && !bIsDead )
					{
						// 공격한다.
						ptTargetTile.x = m_nPosX;
						ptTargetTile.y = m_nPosY;
						SetMotionState(_MT_ONEHSWING, bDir, nTargetID, bIsDead, &ptTargetTile);
					}
				}
				else if ( m_bUseHErgum && g_xGameProc.TargetInLongAttack(bDir) )
				{
					if ( m_stFeatureEx.bHorse == _HORSE_NONE && !bIsDead )
					{
						// 공격한다.
						ptTargetTile.x = m_nPosX;
						ptTargetTile.y = m_nPosY;
						SetMotionState(_MT_ONEHSWING, bDir, nTargetID, bIsDead, &ptTargetTile);
					}
				}
				else
				{
					ptTargetTile.x = m_nPosX;
					ptTargetTile.y = m_nPosY;
					SetMotionState(_MT_ONEHSWING, bDir, nTargetID, bIsDead, &ptTargetTile);
				}
			}
		}
		// 2. ALT.(썰기)
		else if ( HIBYTE(GetKeyState(VK_MENU)) && !HIBYTE(GetKeyState(VK_CONTROL)))
		{
			if ( m_stFeatureEx.bHorse == _HORSE_NONE )
			{
				if ( nLength < 2 )
					SetMotionState(_MT_CUT, bDir, nTargetID, bIsDead, &ptMouseTilePos);
				else
					SetMotionState(_MT_CUT, bDir, nTargetID, bIsDead, NULL);
			}
		}
		//3. 표창공격.
		else if ( bHasDot && nTargetID != -1 )
		{
			if ( m_stFeatureEx.bHorse == _HORSE_NONE )
			{
				if ( nTargetID != -1 && lpptTargetPos )
				{
					bDir = m_pxMap->GetNextDirection(m_nPosX, m_nPosY, lpptTargetPos->x, lpptTargetPos->y);
					SetMotionState(_MT_ONEHSWING, bDir, nTargetID, bIsDead, lpptTargetPos);
				}
			}
		}
		// 4. 클릭한 좌표가 Actor 영역 안에 있는가?
		else if ( nTargetID != -1 && lpptTargetPos )
		{
			bDir = m_pxMap->GetNextDirection(m_nPosX, m_nPosY, lpptTargetPos->x, lpptTargetPos->y);

			if ( HIBYTE(GetKeyState(VK_CONTROL)) && HIBYTE(GetKeyState(VK_MENU)) )
			{
				g_xGameProc.m_bFollowChar = TRUE;
				g_xGameProc.m_nIdxFollowChar = nTargetID;
			}
			else if ( nLength < 2 && nLength > 0 )		//1. 타겟 타일의 위치가 1타일 이내인가?
			{
				if ( m_stFeatureEx.bHorse == _HORSE_NONE )
				{
					if ( !bIsDead )
					{
						// 공격한다.
						ptTargetTile.x = m_nPosX;
						ptTargetTile.y = m_nPosY;
						SetMotionState(_MT_ONEHSWING, bDir, nTargetID, bIsDead, &ptTargetTile);
					}
					else
					{
						SetMotionState(_MT_WALK, bDir, nTargetID, bIsDead, lpptTargetPos);
					}
				}
				g_xGameProc.m_bFollowChar = FALSE;
			}
			// Actor가 있는 방향으로 이동 가능한가?(맵속성체크) 
			else if ( m_pxMap->GetNextTileCanMove(m_nPosX, m_nPosY, bDir, 1, &ptTargetTile) && nLength > 0)
			{
				// 1타일 이동한다.
				if ( m_stFeatureEx.bHorse == _HORSE_NONE )		SetMotionState(_MT_WALK, bDir, nTargetID, bIsDead, &ptTargetTile);
				else											SetMotionState(_MT_HORSEWALK, bDir, nTargetID, bIsDead, &ptTargetTile);
				g_xGameProc.m_bFollowChar = FALSE;
			}
			else
			{
				if ( m_stFeatureEx.bHorse == _HORSE_NONE )		SetMotionState(_MT_STAND, bDir);
				else											SetMotionState(_MT_HORSESTAND, bDir);
				g_xGameProc.m_bFollowChar = FALSE;

			}
		}
		// 6. 현재 마우스타일방향으로 이동 가능한가?(맵속성체크)
		else if ( m_pxMap->GetNextTileCanMove(m_nPosX, m_nPosY, bDir, 1, &ptTargetTile) && nLength > 0 )
		{
			// 1타일 이동한다.
			if ( m_stFeatureEx.bHorse == _HORSE_NONE )
				SetMotionState(_MT_WALK, bDir, nTargetID, bIsDead, &ptTargetTile);
			else
				SetMotionState(_MT_HORSEWALK, bDir, nTargetID, bIsDead, &ptTargetTile);
			g_xGameProc.m_bFollowChar = FALSE;
		}
		// 7. 이동 할수 없다면 주변에 이동할수 있는 타일을 찾아내어 목적 타일과의 가장 가까운 타일을 찾아낸다.
		else if ( !m_pxMap->GetNextTileCanMove(m_nPosX, m_nPosY, bDir, 1, &ptTargetTile) )
		{
			if ( m_stFeature.bWeapon == 7 && m_stFeatureEx.bHorse == _HORSE_NONE && 
				 !m_pxMap->GetNextTileCanMove(m_nPosX, m_nPosY, m_bCurrDir, 1, &ptTargetTile))	// 곡괭이.
			{				
				SetMotionState(_MT_ONEHSWING, m_bCurrDir, nTargetID, bIsDead, &ptTargetTile);
			}
			else
			{
				BYTE bSelectedDir = (_MAX_DIRECTION+1);
				INT nDistance	 = 0;
				INT nSelectedDistance = 100;
				for ( BYTE bDirCnt = 0; bDirCnt < _MAX_DIRECTION; bDirCnt++ )
				{
					if ( m_pxMap->GetNextTileCanMove(m_nPosX, m_nPosY, bDirCnt, 1, &ptTargetTile) )
					{
						nDistance = (INT)(sqrt((ptTargetTile.x-ptMouseTilePos.x)*(ptTargetTile.x-ptMouseTilePos.x) + 
										  (ptTargetTile.y-ptMouseTilePos.y)*(ptTargetTile.y-ptMouseTilePos.y)));
						if ( nDistance <= nSelectedDistance )
						{
							nSelectedDistance = nDistance;
							bSelectedDir = bDirCnt;
						}
					}
				}

				if ( bSelectedDir != (_MAX_DIRECTION+1) && nDistance > 0 )
				{
					// 1타일 이동한다.
					m_pxMap->GetNextTileCanMove(m_nPosX, m_nPosY, bSelectedDir, 1, &ptTargetTile);
					if ( m_stFeatureEx.bHorse == _HORSE_NONE )		SetMotionState(_MT_WALK, bSelectedDir, nTargetID, bIsDead, &ptTargetTile);
					else											SetMotionState(_MT_HORSEWALK, bSelectedDir, nTargetID, bIsDead, &ptTargetTile);
				}
				else
				{
					if ( m_stFeatureEx.bHorse == _HORSE_NONE )		SetMotionState(_MT_STAND, bDir);
					else											SetMotionState(_MT_HORSESTAND, bDir);
				}
			}
			g_xGameProc.m_bFollowChar = FALSE;
		}
		else
		{
			if ( m_stFeatureEx.bHorse == _HORSE_NONE )
				SetMotionState(_MT_STAND, bDir);
			else
				SetMotionState(_MT_HORSESTAND, bDir);
			g_xGameProc.m_bFollowChar = FALSE;
		}
	}

	return FALSE;
}



/******************************************************************************************************************

	함수명 : CMyHero::OnRButtonDown()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : POINT ptMouse
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CMyHero::OnRButtonDown(POINT ptMouse)
{
	POINT ptTargetTile;
	POINT ptMouseTilePos;
	BYTE  bDir;

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	m_bAutoDig = FALSE;
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	if ( m_nABlendDelay )
	{
		return TRUE;
	}

	if ( g_xGameProc.m_dwInputDelayTime > 0 )
	{
		return TRUE;
	}

	if ( !g_xGameProc.m_bRender )		
	{
		return TRUE;
	}

	if ( g_xGameProc.m_bDiceModeActive )
	{
		return TRUE;
	}

	// 캐릭터가 못움직이게 고정한다.
	INT nInterfaceWndInRect;
	nInterfaceWndInRect = g_xGameProc.m_xInterface.GetWindowInMousePos(ptMouse);
	if ( nInterfaceWndInRect == 0 && g_xGameProc.m_xInterface.m_xInventoryWnd.GetInvenType() != _ITEM_TYPE_INVENTORY )
	{
		return TRUE;
	}

	if ( GetKeyState(VK_CONTROL) & 0x80 )
	{
		if ( g_xGameProc.m_pxMouseTargetActor && g_xGameProc.m_pxMouseTargetActor->m_nIdentity != m_nIdentity )
		{
			if ( (g_xGameProc.m_pxMouseTargetActor->m_stFeature.bGender == _GENDER_MAN || g_xGameProc.m_pxMouseTargetActor->m_stFeature.bGender == _GENDER_WOMAN) && 
				 !g_xGameProc.m_pxMouseTargetActor->m_bIsDead )
			{
				return TRUE;
			}
		}
	}

/*	if ( g_xGameProc.m_xInterface.OnRButtonDown(ptMouse) )
	{
		return TRUE;
	}
*/
/*	if ( g_xGameProc.m_xInterface.m_bViewMiniMap && g_xGameProc.m_xInterface.m_xMiniMap.OnLButtonDown(ptMouse) )
	{
		return TRUE;
	}
*/
	if ( g_xGameProc.m_xInterface.m_xGameOverWnd.GetGameWndActive() )
	{
		return TRUE;
	}

	if ( g_xGameProc.m_xGameMsgBox.OnRButtonDown(ptMouse) )
	{
		return TRUE;
	}

	if ( !m_bMotionLock && !m_bInputLock )
	{
		INT nLeftMsgCnt = m_xPacketQueue.GetCount();
		if ( nLeftMsgCnt > 0 )
		{
			// 행동패킷일경우 함수를 종료한다.
			if ( UpdatePacketState() )
			{
				return TRUE;
			}
		}
		
		ptMouseTilePos = GetPosMouseToTile(ptMouse.x, ptMouse.y);
		bDir		   = m_pxMap->GetNextDirection(m_nPosX, m_nPosY, ptMouseTilePos.x, ptMouseTilePos.y);			

		//1. 타겟 타일의 위치가 1타일 이내인가?
		if ( (INT)(sqrt((m_nPosX-ptMouseTilePos.x)*(m_nPosX-ptMouseTilePos.x) + (m_nPosY-ptMouseTilePos.y)*(m_nPosY-ptMouseTilePos.y)))
			 < 2 ) 
		{
			// 방향을 바꾼다.
			if ( m_stFeatureEx.bHorse == _HORSE_NONE )		SetMotionState(_MT_STAND, bDir);
			else											SetMotionState(_MT_HORSESTAND, bDir);
		}
		//2. 움직인다.
		else
		{
			// 달릴수 있을때.
			if ( m_bCanRun )
			{
				m_bCanRun = FALSE;

				if ( m_stFeatureEx.bHorse != _HORSE_NONE )
				{
					// 목적지타일과의 방향으로 1, 2, 3타일째의 위치에 방해물이 없을때.
					if ( m_pxMap->GetNextTileCanMove(m_nPosX, m_nPosY, bDir, 1, &ptTargetTile) && 
						 m_pxMap->GetNextTileCanMove(m_nPosX, m_nPosY, bDir, 2, &ptTargetTile) &&
						 m_pxMap->GetNextTileCanMove(m_nPosX, m_nPosY, bDir, 3, &ptTargetTile) )
					{
						// 3타일 이동한다.
						m_pxMap->GetNextTileCanMove(m_nPosX, m_nPosY, bDir, 3, &ptTargetTile);
						SetMotionState(_MT_HORSERUN, bDir, 0, FALSE, &ptTargetTile);
					}
					// 목적지타일과의 방향으로 1타일째의 위치에 방해물이 없을때.
					else if ( m_pxMap->GetNextTileCanMove(m_nPosX, m_nPosY, bDir, 1, &ptTargetTile) )
					{
						SetMotionState(_MT_HORSEWALK, bDir, 0, FALSE, &ptTargetTile);
					}
					// 목적지타일과의 방향으로 1타일째의 위치에 방해물이 있을때.
					else
					{
						BYTE bSelectedDir = (_MAX_DIRECTION+1);
						INT nDistance	 = 0;
						INT nSelectedDistance = 100;
						for ( BYTE bDirCnt = 0; bDirCnt < _MAX_DIRECTION; bDirCnt++ )
						{
							if ( m_pxMap->GetNextTileCanMove(m_nPosX, m_nPosY, bDirCnt, 1, &ptTargetTile) )
							{
								nDistance = (INT)(sqrt((ptTargetTile.x-ptMouseTilePos.x)*(ptTargetTile.x-ptMouseTilePos.x) + 
												  (ptTargetTile.y-ptMouseTilePos.y)*(ptTargetTile.y-ptMouseTilePos.y)));
								if ( nDistance <= nSelectedDistance )
								{
									nSelectedDistance = nDistance;
									bSelectedDir = bDirCnt;
								}
							}
						}
						if ( bSelectedDir != (_MAX_DIRECTION+1) )
						{
							// 1타일 이동한다.
							m_pxMap->GetNextTileCanMove(m_nPosX, m_nPosY, bSelectedDir, 1, &ptTargetTile);
							SetMotionState(_MT_HORSEWALK, bSelectedDir, 0, FALSE, &ptTargetTile);
						}
						else
						{
							SetMotionState(_MT_HORSESTAND, bSelectedDir);
						}
					}
				}
				// 말을 안타고 있을때.
				else
				{
					// 목적지타일과의 방향으로 1, 2타일째의 위치에 방해물이 없을때.
					if ( m_pxMap->GetNextTileCanMove(m_nPosX, m_nPosY, bDir, 1, &ptTargetTile) && 
						 m_pxMap->GetNextTileCanMove(m_nPosX, m_nPosY, bDir, 2, &ptTargetTile) )
					{
						// 2타일 이동한다.
						m_pxMap->GetNextTileCanMove(m_nPosX, m_nPosY, bDir, 2, &ptTargetTile);
						SetMotionState(_MT_RUN, bDir, 0, FALSE, &ptTargetTile);
					}
					// 목적지타일과의 방향으로 1타일째의 위치에 방해물이 없을때.
					else if ( m_pxMap->GetNextTileCanMove(m_nPosX, m_nPosY, bDir, 1, &ptTargetTile) )
					{
						SetMotionState(_MT_WALK, bDir, 0, FALSE, &ptTargetTile);
					}
					// 목적지타일과의 방향으로 1타일째의 위치에 방해물이 있을때.
					else
					{
						BYTE bSelectedDir = (_MAX_DIRECTION+1);
						INT nDistance;
						INT nSelectedDistance = 100;
						for ( BYTE bDirCnt = 0; bDirCnt < _MAX_DIRECTION; bDirCnt++ )
						{
							if ( m_pxMap->GetNextTileCanMove(m_nPosX, m_nPosY, bDirCnt, 1, &ptTargetTile) )
							{
								nDistance = (INT)(sqrt((ptTargetTile.x-ptMouseTilePos.x)*(ptTargetTile.x-ptMouseTilePos.x) + 
												  (ptTargetTile.y-ptMouseTilePos.y)*(ptTargetTile.y-ptMouseTilePos.y)));
								if ( nDistance <= nSelectedDistance )
								{
									nSelectedDistance = nDistance;
									bSelectedDir = bDirCnt;
								}
							}
						}
						if ( bSelectedDir != (_MAX_DIRECTION+1) )
						{
							// 1타일 이동한다.
							m_pxMap->GetNextTileCanMove(m_nPosX, m_nPosY, bSelectedDir, 1, &ptTargetTile);
							SetMotionState(_MT_WALK, bSelectedDir, 0, FALSE, &ptTargetTile);
						}
						else
						{
							SetMotionState(_MT_STAND, bSelectedDir);
						}
					}
				}
			}
			else
			{
				// 목적지타일과의 방향으로 1타일째의 위치에 방해물이 없을때.
				if ( m_pxMap->GetNextTileCanMove(m_nPosX, m_nPosY, bDir, 1, &ptTargetTile) )
				{
					if ( m_stFeatureEx.bHorse == _HORSE_NONE )		SetMotionState(_MT_WALK, bDir, 0, FALSE, &ptTargetTile);
					else											SetMotionState(_MT_HORSEWALK, bDir, 0, FALSE, &ptTargetTile);

				}
				// 목적지타일과의 방향으로 1타일째의 위치에 방해물이 있을때.
				else
				{
					BYTE bSelectedDir = (_MAX_DIRECTION+1);
					INT nDistance;
					INT nSelectedDistance = 100;
					for ( BYTE bDirCnt = 0; bDirCnt < _MAX_DIRECTION; bDirCnt++ )
					{
						if ( m_pxMap->GetNextTileCanMove(m_nPosX, m_nPosY, bDirCnt, 1, &ptTargetTile) )
						{
							nDistance = (INT)(sqrt((ptTargetTile.x-ptMouseTilePos.x)*(ptTargetTile.x-ptMouseTilePos.x) + 
											  (ptTargetTile.y-ptMouseTilePos.y)*(ptTargetTile.y-ptMouseTilePos.y)));
							if ( nDistance <= nSelectedDistance )
							{
								nSelectedDistance = nDistance;
								bSelectedDir = bDirCnt;
							}
						}
					}
					if ( bSelectedDir != (_MAX_DIRECTION+1) )
					{
						// 1타일 이동한다.
						m_pxMap->GetNextTileCanMove(m_nPosX, m_nPosY, bSelectedDir, 1, &ptTargetTile);
						if ( m_stFeatureEx.bHorse == _HORSE_NONE )	SetMotionState(_MT_WALK, bSelectedDir, 0, FALSE, &ptTargetTile);
						else										SetMotionState(_MT_HORSEWALK, bSelectedDir, 0, FALSE, &ptTargetTile);
					}
					else
					{
						if ( m_stFeatureEx.bHorse == _HORSE_NONE )	SetMotionState(_MT_STAND, bDir);
						else										SetMotionState(_MT_HORSESTAND, bDir);
					}
				}
			}
		}
	}

	return FALSE;
}


VOID CMyHero::SetMagic(LPCLIENTMAGICRCD	pstMagic, BYTE bDir, INT nTargetID, FEATURE stTargetFeature, POINT ptTargetPos)
{
	DWORD dwCurrTick = timeGetTime();
	if ( !m_bMotionLock && !m_bInputLock )
	{
		switch ( m_nCurrMagicID )
		{
			case _SKILL_HYPERSWORD:
			{
				m_dwLastSpellTime = dwCurrTick;
				m_dwMagicDelayTime = 200 + pstMagic->stStdMagic.nDelayTime;

				SetMotionFrame(g_xSpriteInfo.GetWeaponMtn(m_stFeature.bWeapon), bDir);
				g_xClientSocket.SendSpellMsg(m_nCurrMagicID, ptTargetPos.x, ptTargetPos.y, nTargetID);
				break;
			}
			case _SKILL_MOOTEBO:
			case _SKILL_PAWHANGBO:
			case _SKILL_PAWHANGBO_HIGH:
			{
				if ( dwCurrTick - m_dwLastRushTime > 3000 )
				{
					SetMotionState(_MT_MOODEPO, bDir, 0, FALSE, &ptTargetPos, m_nCurrMagicID);
				}
				break;
			}
			case _SKILL_KICK:
			case _SKILL_TAWOO:
			{
				if ( dwCurrTick - m_dwLastKickTime > 3000 )
				{
					SetMotionState(_MT_BACKDROPKICK, bDir, 0, FALSE, &ptTargetPos, m_nCurrMagicID);
				}
				break;
			}
			case _SKILL_HANGMAJINBUB:
			case _SKILL_DEJIWONHO:
			case _SKILL_FIRECHARM:
			case _SKILL_MYULSAL:
			case _SKILL_FIRE:
			case _SKILL_FIREBALL10:
			case _SKILL_BALSACHE:
			case _SKILL_ICE:
			case _SKILL_CROSS_ICE:
			case _SKILL_FIREBALL2:
			case _SKILL_SINSU:
			case _SKILL_FIREBALL:
			case _SKILL_SHOOTLIGHTEN:
			case _SKILL_JIKSUNGYE:
			case _SKILL_CONCENFIREBALL:
			case _SKILL_ICEBOLT:
			case _SKILL_SUPERICEBOLT:
			case _SKILL_MAGICARROW:
			case _SKILL_MOONOK:
			case _SKILL_MOONCHAM:
			case _SKILL_MOONCHAM_HIGH:
			case _SKILL_BIGCLOAK:
			case _SKILL_POWERUP:

			case _SKILL_WITH_FIRE:
			case _SKILL_WITH_ICE:
			case _SKILL_WITH_LIGHT:
			case _SKILL_WITH_WIND:
			case _SKILL_WITH_DEF:
			case _SKILL_WITH_MAGIC:
			case _SKILL_WITH_ATT:

			case _SKILL_MAGICUP:
			case _SKILL_MAGICUP_FIRE:
			case _SKILL_MAGICUP_ICE:
			case _SKILL_MAGICUP_LIGHTENING:
			case _SKILL_MAGICUP_WIND:
			case _SKILL_HANDWIND:
			case _SKILL_ANTIMAGIC_FIRE:
			case _SKILL_ANTIMAGIC_ICE:
			case _SKILL_ANTIMAGIC_LIGHTENING:
			case _SKILL_ANTIMAGIC_WIND:
			case _SKILL_PULL:
			case _SKILL_INHALEHP:
			{
				m_dwLastSpellTime = dwCurrTick;
				m_dwMagicDelayTime = 200 + pstMagic->stStdMagic.nDelayTime;

				SetMotionState(_MT_SPELL1, bDir, nTargetID, TRUE, &ptTargetPos, m_nCurrMagicID);
				break;
			}
			case _SKILL_HURRICANE:
			case _SKILL_HURRICANESHOT:
			case _SKILL_HURRICANEBOMB:
			case _SKILL_FIREWIND:	
			case _SKILL_AMYOUNSUL:
			case _SKILL_BIGAM:
			case _SKILL_AMYOUNSUL_HIGH:
			case _SKILL_MONSTERUP:
			case _SKILL_REMOVEPOISON:
			case _SKILL_DEJIWONHO_HIGH:
			case _SKILL_REMOVEPOISON_HIGH:
			case _SKILL_CHANGEPOSITION:
			case _SKILL_TAMMING:
			case _SKILL_TAMMING_HIGH:
			case _SKILL_KILLUNDEAD:
			case _SKILL_HEALLING:
			case _SKILL_HOLYSHIELD:
			case _SKILL_LIGHTWALL:
			case _SKILL_BIGHEALLING:
			case _SKILL_LIGHTFLOWER:
			case _SKILL_LIGHTFLOWERUP:
			case _SKILL_SKELLETON:
			case _SKILL_DOLL:
			case _SKILL_POWERSKELLETON:
			case _SKILL_SNOWWIND:
			case _SKILL_THUNDERSTORM:
			case _SKILL_SHIELD:
			case _SKILL_SHIELD_HIGH:
			case _SKILL_DOSASHIELD:
			case _SKILL_SHOWHP:
			case _SKILL_EARTHFIRE:
			case _SKILL_JISOKGYE:
			case _SKILL_KANGMAK:
			case _SKILL_FIREBOOM:
			case _SKILL_POKBAL:
			case _SKILL_FIREBOOMUP:
			case _SKILL_EARTH_SUMMON:
			case _SKILL_MAGICTRAP:
			case _SKILL_SPACEMOVE:
			case _SKILL_SMALLSPACEMOVE:
			case _SKILL_CLOAK:
			case _SKILL_CLOAK_HIGH:
			case _SKILL_FULLCLOAK:
			case _SKILL_LIGHTENING:
			case _SKILL_CLOUDTHUNDER:
			case _SKILL_TRANSFORM:
			case _SKILL_REVIVE:
			case _SKILL_REVIVE_HIGH:
			case _SKILL_COPY:
			case _SKILL_1000THUNDER:
			{
				if ( m_nCurrMagicID == _SKILL_SHIELD || m_nCurrMagicID == _SKILL_DOSASHIELD || m_nCurrMagicID == _SKILL_SHIELD_HIGH )
				{
					ptTargetPos.x = m_nPosX;
					ptTargetPos.y = m_nPosY;
					nTargetID	  = m_nIdentity;
				}

				m_dwLastSpellTime = dwCurrTick;
				m_dwMagicDelayTime = 200 + pstMagic->stStdMagic.nDelayTime;
				SetMotionState(_MT_SPELL2, bDir, nTargetID, TRUE, &ptTargetPos, m_nCurrMagicID);
				break;
			}
		}
	}

	switch ( m_nCurrMagicID )
	{
	// 염화결.
	case _SKILL_FIRESWORD:
        if ( dwCurrTick - m_dwLastFireHitTime > 10000 )
		{
			g_xClientSocket.SendSpellMsg(m_nCurrMagicID, 0, 0, nTargetID);
			m_dwLastFireHitTime = dwCurrTick;
		}
		break;
	case _SKILL_JUMPSHOT:
        if ( dwCurrTick - m_dwLastJSHitTime > 10000 )
		{
			g_xClientSocket.SendSpellMsg(m_nCurrMagicID, 0, 0, nTargetID);
			m_dwLastJSHitTime = dwCurrTick;
		}
		break;
	case _SKILL_RANDSWING:
        if ( dwCurrTick - m_dwLastRSHitTime > 10000 )
		{
			g_xClientSocket.SendSpellMsg(m_nCurrMagicID, 0, 0, nTargetID);
			m_dwLastRSHitTime = dwCurrTick;
		}
		break;
	case _SKILL_RANDSWING_HIGH:
        if ( dwCurrTick - m_dwLastRSHitTime > 10000 )
		{
			g_xClientSocket.SendSpellMsg(m_nCurrMagicID, 0, 0, nTargetID);
			m_dwLastRSHitTime = dwCurrTick;
		}
		break;
	case _SKILL_MAXDEFENCE:
	case _SKILL_MAXDEFENCE_HIGH:
	case _SKILL_MAXOFENCE:
	case _SKILL_BIGMOUNTAIN:
	case _SKILL_MAXDEFEECEMAGIC:			// 역혈마공
	case _SKILL_MAXDEFEECEMAGIC_HIGH:
	case _SKILL_BANTAN:
	case _SKILL_COPY:
	case _SKILL_FREEMOVE:
        if ( dwCurrTick - m_dwLastSpellTime > 1000 )
		{
			m_nOldPosX		= m_nPosX;
			m_nOldPosY		= m_nPosY;
			m_bOldDir		= m_bCurrDir;
			m_bMotionLock = m_bInputLock = TRUE;

//			m_dwMagicDelayTime = 200 + pstMagic->stStdMagic.nDelayTime;
			m_dwLastSpellTime = dwCurrTick;
			g_xClientSocket.SendSpellMsg(m_nCurrMagicID, 0, 0, nTargetID);
		}
		break;
	// 염화결이외의 검법.
	case _SKILL_MANWOL:
	case _SKILL_MANWOL_HIGH:
	case _SKILL_BANWOL:
	case _SKILL_ERGUM:
	case _SKILL_ERGUM_HIGH:
	case _SKILL_JUMPSHOT_HIGH:
        if ( dwCurrTick - m_dwLastSpellTime > 200 )
		{
			m_dwLastSpellTime = dwCurrTick;
			m_dwMagicDelayTime = 0;
			g_xClientSocket.SendSpellMsg(m_nCurrMagicID, 0, 0, nTargetID);
		}
		break;
	}

	// 공격마법일때 접속종료 못하게하는 Delay.
	switch ( m_nCurrMagicID )
	{
	case _SKILL_MOOTEBO:	case _SKILL_FIRESWORD:		case _SKILL_BANWOL:		case _SKILL_ERGUM:			case _SKILL_FIRECHARM:
	case _SKILL_FIRE:		case _SKILL_FIREBALL2:		case _SKILL_FIREBALL:	case _SKILL_SHOOTLIGHTEN:	case _SKILL_AMYOUNSUL:  case _SKILL_MANWOL:
	case _SKILL_KILLUNDEAD: case _SKILL_LIGHTFLOWER:	case _SKILL_SNOWWIND:	case _SKILL_EARTHFIRE:		case _SKILL_ICE:		
	case _SKILL_ICEBOLT:	case _SKILL_SUPERICEBOLT:	case _SKILL_MAGICARROW:	case _SKILL_MOONOK:			case _SKILL_MOONCHAM:	case _SKILL_LIGHTFLOWERUP:
	case _SKILL_CONCENFIREBALL:
	case _SKILL_HURRICANE:  case _SKILL_HURRICANESHOT:	case _SKILL_HURRICANEBOMB: case _SKILL_CHANGEPOSITION: case _SKILL_REMOVEPOISON: case _SKILL_MONSTERUP:
	case _SKILL_THUNDERSTORM: case _SKILL_CROSS_ICE:	case _SKILL_MYULSAL:	case _SKILL_KANGMAK:		case _SKILL_PAWHANGBO:	case _SKILL_MOONCHAM_HIGH:	
	case _SKILL_ERGUM_HIGH: case _SKILL_MANWOL_HIGH:	case _SKILL_AMYOUNSUL_HIGH: case _SKILL_BIGAM:		case _SKILL_PAWHANGBO_HIGH:
	case _SKILL_REMOVEPOISON_HIGH:						case _SKILL_BALSACHE:	case _SKILL_JIKSUNGYE:		case _SKILL_JISOKGYE:	case _SKILL_JUMPSHOT_HIGH:
		m_dwLastMagicTime = dwCurrTick;
		break;
	}

	// 사람을 공격했을때 움직임 패널티 Delay.
	m_dwMagicPKDelayTime = 0;
	if ( nTargetID )
	{
		if ( stTargetFeature.bGender == 0 || stTargetFeature.bGender == 1 )
			m_dwMagicPKDelayTime = 300 + GetRandomNum(1, 1100);
	}
}


VOID CMyHero::ClientTestSpell(INT nMouseX, INT nMouseY)
{
	if ( m_bCurrMtn != _MT_STAND && m_bCurrMtn != _MT_ATTACKMODE )
	{
		return;
	}

	m_bInputLock = TRUE;	

	m_ptDstMagicTile = GetPosMouseToTile(nMouseX, nMouseY);
	BYTE  bDir		 = m_pxMap->GetNextDirection(m_nPosX, m_nPosY, m_ptDstMagicTile.x, m_ptDstMagicTile.y);
	BYTE  bMtn		 = _MT_SPELL2;

	switch ( m_nTestMagicID )
	{
		case _SKILL_HANGMAJINBUB:
		case _SKILL_DEJIWONHO:
		case _SKILL_DEJIWONHO_HIGH:
		case _SKILL_FIRECHARM:
		case _SKILL_MYULSAL:
		case _SKILL_FIRE:
		case _SKILL_ICE:
		case _SKILL_FIREBALL2:
		case _SKILL_BALSACHE:
		case _SKILL_SINSU:
		case _SKILL_FIREBALL:
		case _SKILL_SHOOTLIGHTEN:
		case _SKILL_JIKSUNGYE:
		case _SKILL_CONCENFIREBALL:
		case _SKILL_ICEBOLT:
		case _SKILL_SUPERICEBOLT:
		case _SKILL_MAGICARROW:
		case _SKILL_MOONOK:
		case _SKILL_MOONCHAM:
		case _SKILL_MOONCHAM_HIGH:
		case _SKILL_BIGCLOAK:
		case _SKILL_CLOAK_HIGH:
		case _SKILL_POWERUP:

		case _SKILL_WITH_FIRE:
		case _SKILL_WITH_ICE:
		case _SKILL_WITH_LIGHT:
		case _SKILL_WITH_WIND:
		case _SKILL_WITH_DEF:
		case _SKILL_WITH_MAGIC:
		case _SKILL_WITH_ATT:

		case _SKILL_MAGICUP:
		case _SKILL_MAGICUP_FIRE:
		case _SKILL_MAGICUP_ICE:
		case _SKILL_MAGICUP_LIGHTENING:
		case _SKILL_MAGICUP_WIND:
		case _SKILL_HANDWIND:
		case _SKILL_ANTIMAGIC_FIRE:
		case _SKILL_ANTIMAGIC_ICE:
		case _SKILL_ANTIMAGIC_LIGHTENING:
		case _SKILL_ANTIMAGIC_WIND:
		case _SKILL_CROSS_ICE:
			bMtn = _MT_SPELL1;
			break;

		case _SKILL_TAWOO:
			bMtn = _MT_BACKDROPKICK;
			break;
	}

	if ( m_nTestMagicID == _SKILL_FIREBALL		|| m_nTestMagicID == _SKILL_FIREBALL2	  || m_nTestMagicID == _SKILL_FIRE		  || m_nTestMagicID == _SKILL_SHOOTLIGHTEN     ||
		 m_nTestMagicID == _SKILL_HANGMAJINBUB  || m_nTestMagicID== _SKILL_DEJIWONHO	  || m_nTestMagicID == _SKILL_FIRECHARM   || m_nTestMagicID == _SKILL_SINSU		       ||
		 m_nTestMagicID == _SKILL_BIGCLOAK		|| m_nTestMagicID == _SKILL_ICE	  		  || m_nTestMagicID == _SKILL_ICEBOLT	  || m_nTestMagicID == _SKILL_SUPERICEBOLT     || 
		 m_nTestMagicID == _SKILL_MAGICARROW    || m_nTestMagicID == _SKILL_MOONOK		  || m_nTestMagicID == _SKILL_MOONCHAM	  ||
		 m_nTestMagicID == _SKILL_POWERUP		|| m_nTestMagicID == _SKILL_MAGICUP		  || m_nTestMagicID == _SKILL_MAGICUP_FIRE  || m_nTestMagicID == _SKILL_MAGICUP_ICE ||m_nTestMagicID==_SKILL_MAGICUP_LIGHTENING  || m_nTestMagicID==_SKILL_MAGICUP_WIND   || 
		 m_nTestMagicID == _SKILL_HANDWIND		||m_nTestMagicID == _SKILL_ANTIMAGIC_FIRE ||m_nTestMagicID ==_SKILL_ANTIMAGIC_ICE ||m_nTestMagicID==_SKILL_ANTIMAGIC_LIGHTENING|| m_nTestMagicID==_SKILL_ANTIMAGIC_WIND ||
		 m_nTestMagicID == _SKILL_WITH_FIRE     ||
		 m_nTestMagicID == _SKILL_WITH_ICE      ||		 
		 m_nTestMagicID == _SKILL_WITH_LIGHT    ||	
		 m_nTestMagicID == _SKILL_WITH_WIND     ||	
		 m_nTestMagicID == _SKILL_WITH_DEF	    ||	
		 m_nTestMagicID == _SKILL_WITH_MAGIC    ||	
		 m_nTestMagicID == _SKILL_WITH_ATT		||
		 m_nTestMagicID == _SKILL_CONCENFIREBALL|| m_nTestMagicID == _SKILL_CROSS_ICE )

	{
		LoadEffect(&g_xGameProc.m_xImage, m_nTestMagicID, bDir);
	}
	else
	{
		LoadEffect(&g_xGameProc.m_xImage, m_nTestMagicID);
	}

	m_bUseEffect = TRUE;

	if ( m_nTestMagicID == _SKILL_SHOWHP)
	{
		m_bEffectFrameCnt = 20;
	}
//	else if ( m_nTestMagicID == _SKILL_LIGHTFLOWER )
//	{
//		m_bEffectFrameCnt = 11;
//	}
	else if ( m_nTestMagicID == _SKILL_LIGHTENING )			
	{
		m_bEffectFrameCnt = 13;
	}
	else if ( m_nTestMagicID == _SKILL_TRANSFORM )
	{
		m_bEffectFrameCnt = 14;
	}
	else if ( m_nTestMagicID == _SKILL_SHIELD && !(m_nCharState & 0X10000000) )
	{
		m_dwShieldTick = timeGetTime();
	}
	else if ( m_nTestMagicID == _SKILL_SHIELD_HIGH && !(m_nCharState & 0X10000000) )
	{
		m_dwShieldTick = timeGetTime();
	}
	else if ( m_nTestMagicID == _SKILL_DOSASHIELD && !(m_nCharState & 0X00080000) )
	{
		m_dwShieldTick = timeGetTime();
	}

	SetMotionFrame(bMtn, bDir);

	SetTimer(g_xMainWnd.GetSafehWnd(), _TIMER_MTESTID, 600, NULL);
}


VOID CMyHero::ClientTestMagic()
{
	if ( m_nTestMagicID == _SKILL_SPACEMOVE|| 
		 m_nTestMagicID == _SKILL_FIREWIND || m_nTestMagicID == _SKILL_CLOAK	   || m_nTestMagicID == _SKILL_SINSU	 || m_nTestMagicID == _SKILL_SKELLETON ||
		 m_nTestMagicID == _SKILL_TRANSFORM|| /*m_nTestMagicID == _SKILL_LIGHTFLOWER || */m_nTestMagicID == _SKILL_LIGHTFLOWERUP || m_nTestMagicID == _SKILL_POWERSKELLETON || 
		 m_nTestMagicID == _SKILL_FULLCLOAK|| m_nTestMagicID == _SKILL_CLOAK_HIGH )
	{
		return;
	}

	if ( m_nTestMagicID == _SKILL_FIRE || m_nTestMagicID == _SKILL_ICE )
	{
		MakeMagicStream(m_nTestMagicID, 0, m_ptDstMagicTile.x, m_ptDstMagicTile.y);
	}
	else if ( m_nTestMagicID == _SKILL_CROSS_ICE )
	{
		POINT ptTar1,ptTar2,ptTar3,ptStart;

		switch ( m_bCurrDir )
		{
		case 0: 
			ptTar1.x = m_nPosX;
			ptTar1.y = m_nPosY - 5;
			ptTar2.x = m_nPosX - 5;
			ptTar2.y = m_nPosY - 5;
			ptTar3.x = m_nPosX + 5;
			ptTar3.y = m_nPosY - 5;
			ptStart.x = m_nPosX;
			ptStart.y = m_nPosY - 1;
			break;
		case 1: 
			ptTar1.x = m_nPosX + 5;
			ptTar1.y = m_nPosY - 5;
			ptTar2.x = m_nPosX;
			ptTar2.y = m_nPosY - 5;
			ptTar3.x = m_nPosX + 5;
			ptTar3.y = m_nPosY;
			ptStart.x = m_nPosX + 1;
			ptStart.y = m_nPosY - 1;
			break;
		case 2: 
			ptTar1.x = m_nPosX + 5;
			ptTar1.y = m_nPosY - 5;
			ptTar2.x = m_nPosX + 5;
			ptTar2.y = m_nPosY;
			ptTar3.x = m_nPosX + 5;
			ptTar3.y = m_nPosY + 5;
			ptStart.x = m_nPosX + 1;
			ptStart.y = m_nPosY;
			break;
		case 3: 
			ptTar1.x = m_nPosX + 5;
			ptTar1.y = m_nPosY + 5;
			ptTar2.x = m_nPosX + 5;
			ptTar2.y = m_nPosY;
			ptTar3.x = m_nPosX;
			ptTar3.y = m_nPosY + 5;
			ptStart.x = m_nPosX + 1;
			ptStart.y = m_nPosY + 1;
			break;
		case 4: 
			ptTar1.x = m_nPosX;
			ptTar1.y = m_nPosY + 5;
			ptTar2.x = m_nPosX + 5;
			ptTar2.y = m_nPosY + 5;
			ptTar3.x = m_nPosX - 5;
			ptTar3.y = m_nPosY + 5;
			ptStart.x = m_nPosX;
			ptStart.y = m_nPosY + 1;
			break;
		case 5: 
			ptTar1.x = m_nPosX - 5;
			ptTar1.y = m_nPosY + 5;
			ptTar2.x = m_nPosX;
			ptTar2.y = m_nPosY + 5;
			ptTar3.x = m_nPosX - 5;
			ptTar3.y = m_nPosY;
			ptStart.x = m_nPosX - 1;
			ptStart.y = m_nPosY + 1;
			break;
		case 6: 
			ptTar1.x = m_nPosX - 5;
			ptTar1.y = m_nPosY;
			ptTar2.x = m_nPosX - 5;
			ptTar2.y = m_nPosY - 5;
			ptTar3.x = m_nPosX - 5;
			ptTar3.y = m_nPosY + 5;
			ptStart.x = m_nPosX - 1;
			ptStart.y = m_nPosY;
			break;
		case 7: 
			ptTar1.x = m_nPosX - 5;
			ptTar1.y = m_nPosY - 5;
			ptTar2.x = m_nPosX;
			ptTar2.y = m_nPosY - 5;
			ptTar3.x = m_nPosX - 5;
			ptTar3.y = m_nPosY;
			ptStart.x = m_nPosX - 1;
			ptStart.y = m_nPosY - 1;
			break;
		}
		MakeMagicStreamEx(_SKILL_CROSS_ICE, ptStart.x, ptStart.y, ptTar1.x, ptTar1.y);
		MakeMagicStreamEx(_SKILL_CROSS_ICE, ptStart.x, ptStart.y, ptTar2.x, ptTar2.y);
		MakeMagicStreamEx(_SKILL_CROSS_ICE, ptStart.x, ptStart.y, ptTar3.x, ptTar3.y);

//		MakeMagicStreamEx(_SKILL_CROSS_ICE, m_ptDstMagicTile.x, m_ptDstMagicTile.y, m_ptDstMagicTile.x, m_ptDstMagicTile.y-5);
//		MakeMagicStreamEx(_SKILL_CROSS_ICE, m_ptDstMagicTile.x, m_ptDstMagicTile.y, m_ptDstMagicTile.x, m_ptDstMagicTile.y+5);
//		MakeMagicStreamEx(_SKILL_CROSS_ICE, m_ptDstMagicTile.x, m_ptDstMagicTile.y, m_ptDstMagicTile.x-5, m_ptDstMagicTile.y);
//		MakeMagicStreamEx(_SKILL_CROSS_ICE, m_ptDstMagicTile.x, m_ptDstMagicTile.y, m_ptDstMagicTile.x+5, m_ptDstMagicTile.y);
	}
	else if ( m_nTestMagicID == _SKILL_CONCENFIREBALL )
	{
		CMagic* pxMagic;
		pxMagic = new CMagic;
		if ( pxMagic->CreateMagic(_SKILL_FIREBALL, m_nPosX, m_nPosY, m_ptDstMagicTile.x, m_ptDstMagicTile.y, NULL, 0) )
			g_xGameProc.m_xMagicList.Insert (pxMagic);						
		else
			delete pxMagic;

		for ( INT nCnt = 0; nCnt < 2; nCnt++ )
		{
			CConcenFireball* pxCocenFireball;
			pxCocenFireball = new CConcenFireball;
			if ( pxCocenFireball->CreateMagic(m_nTestMagicID, m_nPosX, m_nPosY, m_ptDstMagicTile.x, m_ptDstMagicTile.y, NULL, 0, nCnt*30, nCnt) )
				g_xGameProc.m_xMagicList.Insert (pxCocenFireball);
			else
				delete pxCocenFireball;
		}
	}
	else if ( m_nTestMagicID == _SKILL_HURRICANESHOT || m_nTestMagicID == _SKILL_HURRICANEBOMB)
	{
		for (int nI=0; nI<1; nI++)
		{
			CHurricaneMagic* pxHurricaneMagic;
			pxHurricaneMagic = new CHurricaneMagic;

			pxHurricaneMagic->mHurricaneMagic_nId = nI;

			if ( pxHurricaneMagic->CreateMagic(m_nTestMagicID, m_nPosX, m_nPosY, m_ptDstMagicTile.x, m_ptDstMagicTile.y, m_nTestMagicID, NULL, 0) )
			{
				g_xGameProc.m_xGroundMagicList.Insert (pxHurricaneMagic);
			}
			else
				delete pxHurricaneMagic;
		}
	}
	else if ( m_nTestMagicID != _SKILL_EARTHFIRE && m_nTestMagicID != _SKILL_HOLYSHIELD && m_nTestMagicID != _SKILL_LIGHTWALL )
	{
		CMagic* pxMagic;
		pxMagic = new CMagic;
		if ( pxMagic->CreateMagic(m_nTestMagicID, m_nPosX, m_nPosY, m_ptDstMagicTile.x, m_ptDstMagicTile.y, NULL, 0) )
			g_xGameProc.m_xMagicList.Insert (pxMagic);						
		else
			delete pxMagic;
/*
		for ( INT nI=0; nI<18; nI++ )
		{
			for ( INT nJ=4; nJ<18; nJ++ )
			{
				CMagic* pxMagic;
				pxMagic = new CMagic;
				if ( pxMagic->CreateMagic(m_nTestMagicID, m_nPosX, m_nPosY, nI, nJ, NULL, 0) )
					g_xGameProc.m_xMagicList.Insert (pxMagic);						
				else
					delete pxMagic;
			}
		}
*/		if ( m_nTestMagicID == _SKILL_SHOOTLIGHTEN )
		{
			MakeMagicStream(_SKILL_SHOOTLIGHTEN_ADD, m_nTestMagicID, m_ptDstMagicTile.x, m_ptDstMagicTile.y);
		}
	}

//	m_nTestMagicID	   = -1;
//	m_ptDstMagicTile.x = 0;
//	m_ptDstMagicTile.y = 0;
}




/******************************************************************************************************************

	함수명 : CMyHero::OnKeyDown()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : WPARAM wParam
	         LPARAM lParam
	         POINT ptMouse
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CMyHero::OnKeyDown(WPARAM wParam, LPARAM lParam, POINT ptMouse, POINT ptTargetPos, INT nMosueTargetID, FEATURE stTargetFeature)
{
	BYTE				bDir, bMagicKey;
	DWORD				dwCurrTick;
	POINT				ptTargetTile, ptMouseTilePos;
	LPCLIENTMAGICRCD	pstMagic;

	if ( m_nABlendDelay )
	{
		return FALSE;
	}

	if ( g_xGameProc.m_dwInputDelayTime > 0 )
	{
		return FALSE;
	}

	bMagicKey = 0;

	ZeroMemory(&ptTargetTile, sizeof(POINT));

	if ( g_xGameProc.m_bDiceModeActive )
	{
		return TRUE;
	}

	switch ( wParam )
	{
		case VK_F1:		{	bMagicKey = '1';	break;	}
		case VK_F2:		{	bMagicKey = '2';	break;	}
		case VK_F3:		{	bMagicKey = '3';	break;	}
		case VK_F4:		{	bMagicKey = '4';	break;	}
		case VK_F5:		{	bMagicKey = '5';	break;	}
		case VK_F6:		{	bMagicKey = '6';	break;	}
		case VK_F7:		{	bMagicKey = '7';	break;	}
		case VK_F8:		{	bMagicKey = '8';	break;	}
		case VK_F9:		{	bMagicKey = '9';	break;	}
		case VK_F10:	{	bMagicKey = 'A';	break;	}
		case VK_F11:	{	bMagicKey = 'B';	break;	}
		case VK_F12:	{	bMagicKey = 'C';	break;	}
		case 'a':
		case 'A':
		{
#ifdef _DEBUG
			if ( m_nTestMagicID != -1 )
			{
				ClientTestSpell(ptMouse.x, ptMouse.y);
			}
			else
			{
				SetMotionFrame(_MT_ATTACKMODE, 4, 400);

				for ( INT nI=0; nI<5; nI++ )
				{
					CMagic* pxMagic;
					pxMagic = new CMagic;
					if ( pxMagic->CreateMagic(_SKILL_MAXDEFENCE, m_nPosX, m_nPosY, m_nPosX, m_nPosY, &g_xGameProc.m_xMyHero, m_nIdentity) )
						g_xGameProc.m_xMagicList.Insert(pxMagic);
					else
						delete pxMagic;
				}

/*
				CMagic* pxMagic = new CMagic;
				if ( pxMagic->CreateMagic(_SKILL_REFINE_S, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this, m_nIdentity, 0) )
				{
					g_xGameProc.m_xGroundMagicList.Insert (pxMagic);
				}
				else
				{
					delete pxMagic;	
				}

				CRefineAdd* pxRefineAdd;
				pxRefineAdd = new CRefineAdd;
				if ( pxRefineAdd->CreateMagic(_SKILL_REFINEADD, m_nPosX, m_nPosY, m_ptDstMagicTile.x, m_ptDstMagicTile.y, NULL, 0, 0) )
					g_xGameProc.m_xMagicList.Insert (pxRefineAdd);
				else
					delete pxRefineAdd;

				SetMotionFrame(_MT_ATTACKMODE, 4);
				m_bWarMode = TRUE;
				m_dwWarModeTime = 0;
				g_xGameProc.m_dwInputDelayTime	    = 2000;
				g_xGameProc.m_dwCurrInputDelayTime  = 0;

				g_xGameProc.m_xScatter.SetParticles(D3DVECTOR(m_nScrnPosX-2, m_nScrnPosY-30, 0));
*/
			}
			break;
#endif
		}
		case 'l':
		case 'L':
		{
#ifdef _DEBUG
//			CRefineAdd* pxRefineAdd;
//			pxRefineAdd = new CRefineAdd;
//			if ( pxRefineAdd->CreateMagic(_SKILL_REFINEADD, m_nPosX, m_nPosY, m_ptDstMagicTile.x, m_ptDstMagicTile.y, NULL, 0, 0) )
//				g_xGameProc.m_xMagicList.Insert (pxRefineAdd);
//			else
//				delete pxRefineAdd;

			CMagic* pxMagic = new CMagic;
			if ( pxMagic->CreateMagic(_SKILL_REFINE_F, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this, m_nIdentity, 1000) )
			{
				SetMotionFrame(_MT_STAND, 4);
				m_bWarMode = TRUE;
				m_dwWarModeTime = 0;
				g_xGameProc.m_dwInputDelayTime	    = 2000;
				g_xGameProc.m_dwCurrInputDelayTime  = 0;
				g_xGameProc.m_xGroundMagicList.Insert (pxMagic);
			}
			else
			{
				delete pxMagic;	
			}

			break;
#endif
		}
	}
	dwCurrTick = timeGetTime();

	m_nDelayTemp1000 = ( m_nDelaySeed1000_1 * m_nDelaySeed1000_2 + m_nDelaySeed1000_3 ) * 10;		//	1000(마법 딜레이) 만들기 위한 식 
	// 마법이용가능 Delay Time Check.
	if ( (m_nDelayTemp1000 & 0xF20F) == 0x0208 )
	{
		if ( g_xGameProc.m_xInterface.m_stCommonItem.bWaitResponse )
			int ntest = 0;
		if ( dwCurrTick - m_dwLastSpellTime > m_nDelayTemp1000 + m_dwMagicDelayTime )
		{
			// 마법이 제대로 세팅되었는지 Check.
			if ( bMagicKey && (m_stFeatureEx.bHorse == _HORSE_NONE))
			{
				if ( nMosueTargetID == NULL )	ptMouseTilePos = GetPosMouseToTile(ptMouse.x, ptMouse.y);
				else							ptMouseTilePos = ptTargetPos;

				bDir = m_pxMap->GetNextDirection(m_nPosX, m_nPosY, ptMouseTilePos.x, ptMouseTilePos.y);
				INT nAtoI = atoi((char*)&bMagicKey);
				BYTE bKeyNum = 0;

				if ( nAtoI < 10 && nAtoI > 0 )
				{
					bKeyNum = (BYTE)nAtoI;
				}
				else
				{
					bKeyNum = (BYTE)(bMagicKey - 55);
				}

				INT nMagicID = g_xGameProc.m_xInterface.m_xMagicShortcutWnd.GetMagicIDByKey(bKeyNum);

//			char szstr[100];
//			sprintf(szstr, "bMagicKey:%d, bKeyNum:%d, nMagicID:%d", bMagicKey, bKeyNum, nMagicID);

				pstMagic = g_xGameProc.m_xInterface.m_xMagicWnd.GetMagicByMagicKey(nMagicID);

				if ( pstMagic )
				{
					// 반월제외.
					if ( (10 + pstMagic->stStdMagic.bDefSpell) <= m_stAbility.wMP || pstMagic->stStdMagic.wMagicID == _SKILL_BANWOL || pstMagic->stStdMagic.wMagicID == _SKILL_MANWOL || pstMagic->stStdMagic.wMagicID == _SKILL_MANWOL_HIGH || pstMagic->stStdMagic.wMagicID == _SKILL_JUMPSHOT_HIGH )
					{
						m_nCurrMagicID = pstMagic->stStdMagic.wMagicID;

						if ( ( m_nCurrMagicID == 12 || m_nCurrMagicID == 102 || m_nCurrMagicID == 103 ||
							   m_nCurrMagicID == 7 || m_nCurrMagicID == 20 || m_nCurrMagicID == 6 ||
							   m_nCurrMagicID == 77 || m_nCurrMagicID == 120 ) && pstMagic->bLevel >= 4 )
							   m_nCurrMagicID += 10000;

						SetMagic(pstMagic, bDir, nMosueTargetID, stTargetFeature, ptMouseTilePos);
					}
					else
						g_xGameProc.m_xInterface.m_xClientSysMsg.AddSysMsg(g_xMsg.GetMsg(1000));
				}
			}
		}
		else
		{
			int ntest = 0;
		}
	}

#ifdef _DEBUG
	if ( g_xGameProc.m_xInterface.m_xUtilWnd.UseKey(bMagicKey) )
		return TRUE;

#endif

	return TRUE;
}



BOOL CMyHero::OnSysKeyDown(WPARAM wParam, LPARAM lParam, POINT ptMouse, POINT ptTargetPos, INT nMosueTargetID, FEATURE stTargetFeature)
{
	BYTE				bDir, bMagicKey;
	DWORD				dwCurrTick;
	POINT				ptTargetTile, ptMouseTilePos;
	LPCLIENTMAGICRCD	pstMagic;

	if ( m_nABlendDelay )
	{
		return FALSE;
	}

	if ( g_xGameProc.m_dwInputDelayTime > 0 )
	{
		return FALSE;
	}

	if ( g_xGameProc.m_bDiceModeActive )
	{
		return TRUE;
	}

	bMagicKey = 0;

	ZeroMemory(&ptTargetTile, sizeof(POINT));

	switch ( wParam )
	{
	case VK_F10:	{	bMagicKey = 'A';	break;	}
	case VK_F12:	{	bMagicKey = 'C';	break;	}
	}

	dwCurrTick = timeGetTime();
	// 마법이용가능 Delay Time Check.
	if ( dwCurrTick - m_dwLastSpellTime > 1000 + m_dwMagicDelayTime )
	{
		// 마법이 제대로 세팅되었는지 Check.
		if ( bMagicKey && (m_stFeatureEx.bHorse == _HORSE_NONE))
		{
			if ( nMosueTargetID == NULL )	ptMouseTilePos = GetPosMouseToTile(ptMouse.x, ptMouse.y);
			else							ptMouseTilePos = ptTargetPos;

			bDir = m_pxMap->GetNextDirection(m_nPosX, m_nPosY, ptMouseTilePos.x, ptMouseTilePos.y);


			INT nAtoI = atoi((char*)&bMagicKey);
			BYTE bKeyNum = 0;

			if ( nAtoI < 10 && nAtoI > 0 )
			{
				bKeyNum = (BYTE)nAtoI;
			}
			else
			{
				bKeyNum = (BYTE)(bMagicKey - 55);
			}

			INT nMagicID = g_xGameProc.m_xInterface.m_xMagicShortcutWnd.GetMagicIDByKey(bKeyNum);
			pstMagic = g_xGameProc.m_xInterface.m_xMagicWnd.GetMagicByMagicKey(nMagicID);

//			pstMagic = g_xGameProc.m_xInterface.m_xMagicWnd.GetMagicByKey(bMagicKey);

			if ( pstMagic )
			{
				// 반월제외.
				if ( (10 + pstMagic->stStdMagic.bDefSpell) <= m_stAbility.wMP || pstMagic->stStdMagic.wMagicID == _SKILL_BANWOL || pstMagic->stStdMagic.wMagicID == _SKILL_MANWOL || pstMagic->stStdMagic.wMagicID == _SKILL_JUMPSHOT_HIGH )
				{
					m_nCurrMagicID = pstMagic->stStdMagic.wMagicID;

					if ( pstMagic->bLevel >= 4 )
						m_nCurrMagicID += 10000;
					SetMagic(pstMagic, bDir, nMosueTargetID, stTargetFeature, ptMouseTilePos);
				}
				else
					g_xGameProc.m_xInterface.m_xClientSysMsg.AddSysMsg(g_xMsg.GetMsg(1000));
			}
		}
	}

#ifdef _DEBUG
	if ( g_xGameProc.m_xInterface.m_xUtilWnd.UseKey(bMagicKey) )
		return TRUE;

#endif

	return TRUE;
}

BOOL CMyHero::CheckDelay()
{
	DWORD	dwTemp = timeGetTime();

	DWORD	dwCurrTick;
	INT		nLevelFast;
	DWORD	dwNextHit;
	BOOL	bAttackSlow = FALSE;

	if ( ((m_nMinTemp370 & 0xF3A0) == 0x0120) && ((m_nMinTemp800 & 0x2837) == 0x0020 ) )
	{
		nLevelFast = min(m_nMinTemp370, m_stAbility.bLevel*14);
		nLevelFast = min(m_nMinTemp800, nLevelFast + m_shHitSpeed * 60);

		if ( m_stAbility.bHandWeight > m_stAbility.bMaxHandWeight )		
			bAttackSlow = TRUE;

		m_nDelayTemp1400 = m_nDelaySeed1400_1 * m_nDelaySeed1400_2 * m_nDelaySeed1400_3;
		m_nDelayTemp1500 = m_nDelaySeed1500_1 * m_nDelaySeed1500_2 * m_nDelaySeed1500_3;

		if ( ( (m_nDelayTemp1400 & 0x8A8F) == 0x0008 ) && ( (m_nDelayTemp1500 & 0x3FF8) == 0x05D8 ) )
		{
			if ( bAttackSlow )
				dwNextHit = m_nDelayTemp1400  - nLevelFast + m_nDelayTemp1500 ;
			else					
				dwNextHit = m_nDelayTemp1400  - nLevelFast;

			while ( dwTemp - m_dwLastHitUseTime < (dwNextHit * 0.8) )
			{
				dwTemp = timeGetTime();
			}
		}
	}

	while ( dwTemp - m_dwLastWalkTime < 480 )
	{
		dwTemp = timeGetTime();
	}

	while ( dwTemp - m_dwLastMagicUseTime < 800 )
	{
		dwTemp = timeGetTime();
	}

	return TRUE;
}



// 코드 정리 by eriastoa 2006.04.19
VOID
CActor::MonEffectLoad( WORD wDress, BYTE& bMtn, BYTE& bDir )
{					
	// 구분하기 좋도록 wDress로 나눈다
	// 물론 bMtn 으로 나눌 수도 있다
	switch( wDress )
	{
	case 0:		// 돌기둥
	case 3:		// 훈련소
	case 5:		// 이계의 문
	case 11:	// 수호자
	case 15:	// 신전
	case 16:	// 사령부
	case 39:	// 태극기
	case 73:	// 비막원충
	case 104:	// 적월마
	case 127:	// 밤나무
	case 153:	// 트리
	case 179:	// ~ 537 성훈씨
	case 187:	
	case 188:
	case 189:
	case 534:
	case 535:
	case 536:
	case 537:
		{
			bDir = 0;
		}
		break;

	case 10:
		{
			if( bMtn == _MT_MON_SPELL_A )
			{
				CMagic* pxMagic;
				pxMagic = new CMagic;
				if ( pxMagic->CreateMagic(_MONMAGIC_EXPLODE, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this) )
					g_xGameProc.m_xMagicList.Insert (pxMagic);
				else
					delete pxMagic;
			}
		}
		break;

	case 31:
		{
			if( bMtn == _MT_MON_STAND )
			{
				bDir = 0;
			}
		}
		break;

	case 67:	// 촉룡신
		{
			if ( bMtn == _MT_MON_ATTACK_A )
			{
				bDir = 1;
			}
			else
			{
				bDir = 0;
			}
		}
		break;

	case 106:	// 폭안거미
		{
			bDir = 1;
		}
		break;

	case 141:	// 해골진왕
		{
			if( g_xGameProc.m_bShowMonEffect )
			{
				LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_SKELBOSS1+(bMtn-_MT_MON_STAND), bDir);
				m_bUseSwordEffect = TRUE;
			}
		}
		break;

	case 184:	// 누마사령법사
		{
			if( _MONMAGIC_NUMABUBSA1+(bMtn) != _MONMAGIC_NUMABUBSA5 )
			{
				if ( g_xGameProc.m_bShowMonEffect )
				{
					LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_NUMABUBSA1+(bMtn), bDir);
					m_bUseSwordEffect = TRUE;
				}
			}
		}
		break;

	case 186:
		{
			if( bMtn == _MT_MON_ATTACK_A )
			{
				LoadEffect( &g_xGameProc.m_xImage, _MONMAGIC_TADANGGA_ATTACK, bDir );
				m_bUseSwordEffect = TRUE;
			}
			else if( bMtn == _MT_MON_SPELL_A )
			{
				LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_TADANGGA_MAGIC, 0);
				m_bUseSwordEffect = TRUE;
			}
		}
		break;



	case 197:
		{
			if( bMtn == _MT_MON_SPELL_A )
			{
				CMagic* pxMagic;
				pxMagic = new CMagic;
				if ( pxMagic->CreateMagic(_MONMAGIC_YOUKHYUL_MAGIC, m_nPosX, m_nPosY, m_nPosX, m_nPosY, this) )
					g_xGameProc.m_xMagicList.Insert (pxMagic);
				else
					delete pxMagic;
			}			
		}
		break;

	case 213:	// 가무녀 2
		{
			if( bMtn == _MT_MON_ATTACK_A )
			{
				LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_GAMU_B, bDir);
				m_bUseSwordEffect = TRUE;
			}
		}
		break;

	case 211:	// 새벽여왕
		{
			if( bMtn == _MT_MON_ATTACK_A )
			{
				LoadEffect(&g_xGameProc.m_xImage, _MONMAGIC_DAWNQUEEN_B, bDir);
				m_bUseSwordEffect = TRUE;
			}
		}
		break;

	case 530:	// 사북성문1 깨지는 것
	case 531:
	case 532:
	case 533:
	case 538:
		{
			if( bMtn == _MT_MON_DIE )
			{
				bDir = 0;
			}
		}
		break;

	default:
		break;
	}
	
	g_xSpriteInfo.SetMonFrameInfo( wDress );

	if( wDress < 1000 )
	{
		m_dwFstFrame = g_xSpriteInfo.m_stMonSpr[bMtn].wFstFrm + (wDress%10)*_MAX_MON_FRAME + bDir*10;
		m_dwEndFrame = m_dwFstFrame + g_xSpriteInfo.m_stMonSpr[bMtn].wFrmCnt;
		m_nDelay = g_xSpriteInfo.m_stMonSpr[bMtn].wDelay;

		switch( wDress )
		{
		case 182:
			{
				if( bMtn == _MT_MON_DIE )
				{
					m_dwFstFrame = g_xSpriteInfo.m_stMonSpr[bMtn].wFstFrm + (wDress%10)*_MAX_MON_FRAME + bDir*10;
					m_dwEndFrame = m_dwFstFrame + g_xSpriteInfo.m_stMonSpr[bMtn].wFrmCnt;
					m_nDelay = g_xSpriteInfo.m_stMonSpr[bMtn].wDelay;
				}
				else
				{
					WORD wTemp = 185;

					m_dwFstFrame = g_xSpriteInfo.m_stMonSpr[bMtn].wFstFrm + (wTemp%10)*_MAX_MON_FRAME + bDir*10;
					m_dwEndFrame = m_dwFstFrame + g_xSpriteInfo.m_stMonSpr[bMtn].wFrmCnt;
					m_nDelay = g_xSpriteInfo.m_stMonSpr[bMtn].wDelay;
				}
			}
			break;

		case 141:	// 해골진왕
			{
				if( bMtn == _MT_MON_DIE )
				{
					m_dwFstFrame = g_xSpriteInfo.m_stMonSpr[bMtn].wFstFrm + (wDress%10)*_MAX_MON_FRAME + bDir*20;
					m_dwEndFrame = m_dwFstFrame + g_xSpriteInfo.m_stMonSpr[bMtn].wFrmCnt;
					m_nDelay = g_xSpriteInfo.m_stMonSpr[bMtn].wDelay;
				}
			}
			break;

		case 213:	// 가무녀 2
			{
				if( bMtn == _MT_MON_ATTACK_A || bMtn == _MT_MON_ATTACK_B )
				{
					m_dwFstFrame = g_xSpriteInfo.m_stMonSpr[bMtn].wFstFrm + (wDress%10)*_MAX_MON_FRAME + bDir*20;
					m_dwEndFrame = m_dwFstFrame + g_xSpriteInfo.m_stMonSpr[bMtn].wFrmCnt;
					m_nDelay = g_xSpriteInfo.m_stMonSpr[bMtn].wDelay;
				}
			}
			break;
			
		default:
			{
				/*m_dwFstFrame = g_xSpriteInfo.m_stMonSpr[bMtn].wFstFrm + (wDress%10)*_MAX_MON_FRAME + bDir*10;
				m_dwEndFrame = m_dwFstFrame + g_xSpriteInfo.m_stMonSpr[bMtn].wFrmCnt;
				m_nDelay = g_xSpriteInfo.m_stMonSpr[bMtn].wDelay;*/
			}
			break;
		}
	}
	else
	{
		m_dwFstFrame = g_xSpriteInfo.m_stMonSpr[bMtn].wFstFrm + ((wDress-2000)/10)*_MAX_MON_FRAME + bDir*10;
		m_dwEndFrame = m_dwFstFrame + g_xSpriteInfo.m_stMonSpr[bMtn].wFrmCnt;
		m_nDelay = g_xSpriteInfo.m_stMonSpr[bMtn].wDelay;		
	}
}

BOOL
// 코드 정리 by eriastoa 2006.04.20
CActor::SetMonImgIdx( WORD wDress )
{
	if ( wDress < 1000 )
	{
		if ( wDress < 200 || wDress > 500 )
		{
			m_bActorImgIdx = (BYTE)(_IMAGE_MONSTER1 + (BYTE)(wDress / 10));
		}
		else if ( wDress >= 200 && wDress < 210 )
		{
			m_bActorImgIdx = _IMAGE_MONSTER21;
		}
		else
		{
			m_bActorImgIdx = _IMAGE_MONSTER22;
		}
	}
	else
	{
		m_bActorImgIdx = (BYTE)(_IMAGE_DMONSTER1 + (BYTE)((wDress-2000)/100));
	}

	if( m_bActorImgIdx >= _MAX_IMAGE )
	{
		return FALSE;
	}

	return TRUE;
}


VOID
// 그림자 그리기
// 만약에 그림자 파일이 없는데 그림자가 제대로 나오지 않을 경우 
// 하드 코딩으로 그림자를 그리도록 한다
// by eriastoa 2006.05.03
CActor::DrawShadow( INT x, INT y, BOOL bShadowAblended, BYTE bShadowType, BYTE bOpaRate )
{
	g_xMainWnd.DrawWithShadowABlend(
		x, y, m_pxActorImage->m_lpstNewCurrWilImageInfo->shWidth, m_pxActorImage->m_lpstNewCurrWilImageInfo->shHeight,
		(WORD*)m_pxActorImage->m_pbCurrImage, _CLIP_WIDTH, _CLIP_HEIGHT, g_xGameProc.m_wShadowClr,
		bShadowAblended, bShadowType, bOpaRate);	
}

/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"

#define	_SET_BGMVOL				1
#define	_SET_WAVEVOL			0

COptionWnd::COptionWnd()
{
	Init();
}

COptionWnd::~COptionWnd()
{
	Destroy();
}

VOID COptionWnd::Init()
{
	INT nCnt;

	CGameWnd::Init();

	m_bBGMON	= TRUE;
	m_bEffectON	= TRUE;
	m_bEnvirON	= FALSE;
	m_bShadowON	= FALSE;

	mOptionWnd_bAllowGroup = FALSE;

	mOptionWnd_nAttackMode = _ATTACK_ALL;

	mOptionWnd_bMoveBgmVolBtn = FALSE;
	mOptionWnd_bMoveWaveVolBtn = FALSE;
	
	for ( nCnt = 0; nCnt < _MAX_OPTION_BTN; nCnt++ )
	{
		m_xOptionBtn[nCnt].Init();
	}

	mOptionWnd_ptWaveVolBtn.x = 0;
	mOptionWnd_ptBgmVolBtn.x = 0;

	mOptionWnd_nMode = _BASIC_SET;
}

VOID COptionWnd::Destroy()
{
	CGameWnd::Destroy();
}

VOID COptionWnd::CreateOptionWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend)
{
	CreateGameWnd(nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight, bBlend);
	
	m_xOptionBtn[_BTN_ID_OPTIONCLOSE].CreateGameBtn(pxWndImage, 1221, 1222, nStartX+448, nStartY+359, g_xMsg.GetMsg(1052), _BTN_TYPE_FOCUS, 1221, TRUE);
	m_xOptionBtn[_BTN_ID_BGMONOFF].CreateGameBtn	   (pxWndImage, 297, 297, nStartX+430, nStartY+85, "", _BTN_TYPE_FOCUS, -1, TRUE);
	m_xOptionBtn[_BTN_ID_SOUNDONOFF].CreateGameBtn   (pxWndImage, 297, 297, nStartX+430, nStartY+145, "", _BTN_TYPE_FOCUS, -1, TRUE);
	m_xOptionBtn[_NEW_BTN_ID_ANTIPANONOFF].CreateGameBtn     (pxWndImage, 297, 297, nStartX+430, nStartY+205, "", _BTN_TYPE_FOCUS, -1, TRUE);
	m_xOptionBtn[_BTN_ID_SBLENDONOFF].CreateGameBtn   (pxWndImage, 297, 297, nStartX+430, nStartY+235, "", _BTN_TYPE_FOCUS, -1, TRUE);
	m_xOptionBtn[_BTN_ID_BGMVOLUME].CreateGameBtn  (pxWndImage, 303, 303, nStartX+18, nStartY+138, "", _BTN_TYPE_FOCUS, 303, TRUE);
	m_xOptionBtn[_BTN_ID_WAVEVOLUME].CreateGameBtn  (pxWndImage, 303, 303, nStartX+18, nStartY+178, "", _BTN_TYPE_FOCUS, 303, TRUE);
	m_xOptionBtn[_BTN_ID_SHOWMONINMAP].CreateGameBtn  (pxWndImage, 297, 297, nStartX+186, nStartY+55, "", _BTN_TYPE_FOCUS, -1, TRUE);
	m_xOptionBtn[_BTN_ID_ATTACKUSER].CreateGameBtn  (pxWndImage, 297, 297, nStartX+186, nStartY+89, "", _BTN_TYPE_FOCUS, -1, TRUE);
	m_xOptionBtn[_BTN_ID_MAGICLIGHT].CreateGameBtn  (pxWndImage, 297, 297, nStartX+186, nStartY+119, "", _BTN_TYPE_FOCUS, -1, TRUE);
	m_xOptionBtn[_BTN_ID_SHOWBLOODNUM].CreateGameBtn  (pxWndImage, 297, 297, nStartX+186, nStartY+149, "", _BTN_TYPE_FOCUS, -1, TRUE);
	m_xOptionBtn[_BTN_ID_REVIVAL].CreateGameBtn  (pxWndImage, 297, 297, nStartX+186, nStartY+179, "", _BTN_TYPE_FOCUS, -1, TRUE);
	m_xOptionBtn[_BTN_ID_CHUNJIHAPIL].CreateGameBtn  (pxWndImage, 297, 297, nStartX+186, nStartY+179, "", _BTN_TYPE_FOCUS, -1, TRUE);
	m_xOptionBtn[_BTN_ID_EXCHANGEMODE].CreateGameBtn  (pxWndImage, 297, 297, nStartX+186, nStartY+179, "", _BTN_TYPE_FOCUS, -1, TRUE);
	m_xOptionBtn[_BTN_ID_WHISPERMODE].CreateGameBtn  (pxWndImage, 297, 297, nStartX+186, nStartY+179, "", _BTN_TYPE_FOCUS, -1, TRUE);
	m_xOptionBtn[_BTN_ID_GUILDWHISPERMODE].CreateGameBtn  (pxWndImage, 297, 297, nStartX+186, nStartY+179, "", _BTN_TYPE_FOCUS, -1, TRUE);
	m_xOptionBtn[_BTN_ID_GUILDJOINMODE].CreateGameBtn  (pxWndImage, 297, 297, nStartX+186, nStartY+179, "", _BTN_TYPE_FOCUS, -1, TRUE);
	m_xOptionBtn[_BTN_ID_SHOUTMODE].CreateGameBtn  (pxWndImage, 297, 297, nStartX+186, nStartY+179, "", _BTN_TYPE_FOCUS, -1, TRUE);
	m_xOptionBtn[_BTN_ID_ATTACKMODE].CreateGameBtn(pxWndImage, 295, 295, nStartX+448, nStartY+359, "", _BTN_TYPE_FOCUS, -1, TRUE);
	m_xOptionBtn[_BTN_ID_DRAWUSERPIC].CreateGameBtn  (pxWndImage, 297, 297, nStartX+448, nStartY+359, "", _BTN_TYPE_FOCUS, -1, TRUE);
	m_xOptionBtn[_BTN_ID_AUTOPICKUP].CreateGameBtn  (pxWndImage, 1292, 1293, nStartX+448, nStartY+179, "", _BTN_TYPE_FOCUS, 1292, TRUE);
	m_xOptionBtn[_BTN_ID_SHOWDROPITEM].CreateGameBtn(pxWndImage, 1296, 1297, nStartX+186, nStartY+359, "", _BTN_TYPE_FOCUS, 1296, TRUE);
	m_xOptionBtn[_BTN_ID_SHOWHEALTHNUM].CreateGameBtn  (pxWndImage, 1292, 1293, nStartX+448, nStartY+359, "", _BTN_TYPE_FOCUS, 1292, TRUE);
	m_xOptionBtn[_BTN_ID_MONEFFECT].CreateGameBtn  (pxWndImage, 297, 297, nStartX+448, nStartY+359, "", _BTN_TYPE_FOCUS, -1, TRUE);
	m_xOptionBtn[_BTN_ID_SHOWDEYING].CreateGameBtn  (pxWndImage, 297, 297, nStartX+448, nStartY+359, "", _BTN_TYPE_FOCUS, -1, TRUE);
	m_xOptionBtn[_BTN_ID_SHOWHELMET].CreateGameBtn  (pxWndImage, 297, 297, nStartX+448, nStartY+359, "", _BTN_TYPE_FOCUS, -1, TRUE);
	m_xOptionBtn[_BTN_ID_ALLOWGROUP].CreateGameBtn  (pxWndImage, 297, 297, nStartX+448, nStartY+359, "", _BTN_TYPE_FOCUS, -1, TRUE);
	m_xOptionBtn[_BTN_ID_SHOWHEALTHBAR].CreateGameBtn  (pxWndImage, 297, 297, nStartX+448, nStartY+359, "", _BTN_TYPE_FOCUS, -1, TRUE);
	m_xOptionBtn[_BTN_ID_CUTSOMEONE].CreateGameBtn  (pxWndImage, 306, 306, nStartX+448, nStartY+359, "", _BTN_TYPE_FOCUS, -1, TRUE);
	m_xOptionBtn[_BTN_ID_WHOLESHOUTMODE].CreateGameBtn  (pxWndImage, 297, 297, nStartX+448, nStartY+359, "", _BTN_TYPE_FOCUS, -1, TRUE);
	m_xOptionBtn[_BTN_ID_CHANGEWEATHER].CreateGameBtn(pxWndImage, 295, 295, nStartX+448, nStartY+359, "", _BTN_TYPE_FOCUS, 295, TRUE);
	

	SetOptions();

	if ( g_xGameProc.m_xInterface.m_xGroupWnd.m_bAllowGroup )
	{
		m_xOptionBtn[_BTN_ID_ALLOWGROUP].ResetGameBtn(297, 297, -1);
	}
	else
	{
		m_xOptionBtn[_BTN_ID_ALLOWGROUP].ResetGameBtn(301, 301, 299);
	}

	if ( mOptionWnd_bShowHealthbar )
	{
		m_xOptionBtn[_BTN_ID_SHOWHEALTHBAR].ResetGameBtn(297, 297, -1);
	}
	else
	{
		m_xOptionBtn[_BTN_ID_SHOWHEALTHBAR].ResetGameBtn(301, 301, 299);
	}
	

	if ( mOptionWnd_bRevival )
	{
		m_xOptionBtn[_BTN_ID_REVIVAL].ResetGameBtn(297, 297, -1);
	}
	else
	{
		m_xOptionBtn[_BTN_ID_REVIVAL].ResetGameBtn(301, 301, 299);
	}

	if ( mOptionWnd_bChunjihapil )
	{
		m_xOptionBtn[_BTN_ID_CHUNJIHAPIL].ResetGameBtn(297, 297, -1);
	}
	else
	{
		m_xOptionBtn[_BTN_ID_CHUNJIHAPIL].ResetGameBtn(301, 301, 299);
	}

	if ( mOptionWnd_bExchangeMode )
	{
		m_xOptionBtn[_BTN_ID_EXCHANGEMODE].ResetGameBtn(297, 297, -1);
	}
	else
	{
		m_xOptionBtn[_BTN_ID_EXCHANGEMODE].ResetGameBtn(301, 301, 299);
	}

	if ( mOptionWnd_bWhisperMode )
	{
//		g_xGameProc.m_xInterface.m_xInterBtn[ _NEW_BTN_ID_CHATALLDENY].ResetGameBtn(-1, -1, -1);
//		g_xGameProc.m_xInterface.m_xInterBtn[ _NEW_BTN_ID_CHATALLDENY].ChangeBtnTooltip(g_xMsg.GetMsg(2637));
		m_xOptionBtn[_BTN_ID_WHISPERMODE].ResetGameBtn(297, 297, -1);
		g_xGameProc.m_xInterface.m_bChatallDeny = FALSE;
	}
	else
	{
		m_xOptionBtn[_BTN_ID_WHISPERMODE].ResetGameBtn(301, 301, 299);
//		g_xGameProc.m_xInterface.m_xInterBtn[ _NEW_BTN_ID_CHATALLDENY].ResetGameBtn(1338, 1338, 1338);
//		g_xGameProc.m_xInterface.m_xInterBtn[ _NEW_BTN_ID_CHATALLDENY].ChangeBtnTooltip(g_xMsg.GetMsg(2638));
		g_xGameProc.m_xInterface.m_bChatallDeny = TRUE;
	}

	if ( mOptionWnd_bGuildwhisperMode )
	{
		m_xOptionBtn[_BTN_ID_GUILDWHISPERMODE].ResetGameBtn(297, 297, -1);
//		g_xGameProc.m_xInterface.m_xInterBtn[ _NEW_BTN_ID_DENYGUILD].ResetGameBtn(-1, -1, -1);
//		g_xGameProc.m_xInterface.m_xInterBtn[ _NEW_BTN_ID_DENYGUILD].ChangeBtnTooltip(g_xMsg.GetMsg(2639));
		g_xGameProc.m_xInterface.m_bDenyGuild = TRUE;
	}
	else
	{
		m_xOptionBtn[_BTN_ID_GUILDWHISPERMODE].ResetGameBtn(301, 301, 299);
//		g_xGameProc.m_xInterface.m_xInterBtn[ _NEW_BTN_ID_DENYGUILD].ResetGameBtn(1340, 1340, 1340);
//		g_xGameProc.m_xInterface.m_xInterBtn[ _NEW_BTN_ID_DENYGUILD].ChangeBtnTooltip(g_xMsg.GetMsg(2640));
		g_xGameProc.m_xInterface.m_bDenyGuild = FALSE;
	}

	if ( mOptionWnd_bGuildJoinMode )
	{
		m_xOptionBtn[_BTN_ID_GUILDJOINMODE].ResetGameBtn(297, 297, -1);
	}
	else
	{
		m_xOptionBtn[_BTN_ID_GUILDJOINMODE].ResetGameBtn(301, 301, 299);
	}

	if ( mOptionWnd_bShoutMode )
	{
		m_xOptionBtn[_BTN_ID_SHOUTMODE].ResetGameBtn(297, 297, -1);
//		g_xGameProc.m_xInterface.m_xInterBtn[ _NEW_BTN_ID_DENYSHOUT].ResetGameBtn(-1, -1, -1);
//		g_xGameProc.m_xInterface.m_xInterBtn[ _NEW_BTN_ID_DENYSHOUT].ChangeBtnTooltip(g_xMsg.GetMsg(2643));
		g_xGameProc.m_xInterface.m_bDenyGuild = FALSE;
	}
	else
	{
		m_xOptionBtn[_BTN_ID_SHOUTMODE].ResetGameBtn(301, 301, 299);
//		g_xGameProc.m_xInterface.m_xInterBtn[ _NEW_BTN_ID_DENYSHOUT].ResetGameBtn(1342, 1342, 1342);
//		g_xGameProc.m_xInterface.m_xInterBtn[ _NEW_BTN_ID_DENYSHOUT].ChangeBtnTooltip(g_xMsg.GetMsg(2644));
		g_xGameProc.m_xInterface.m_bDenyGuild = FALSE;
	}

	if ( m_bBGMON )
	{
		m_xOptionBtn[_BTN_ID_BGMONOFF].ResetGameBtn(297, 297, -1);
	}
	else
	{
		m_xOptionBtn[_BTN_ID_BGMONOFF].ResetGameBtn(301, 301, 299);
	}

	if ( m_bEffectON )
	{
		m_xOptionBtn[_BTN_ID_SOUNDONOFF].ResetGameBtn(297, 297, -1);
	}
	else
	{
		m_xOptionBtn[_BTN_ID_SOUNDONOFF].ResetGameBtn(301, 301, 299);
	}

	if ( m_bShadowON )
	{
		m_xOptionBtn[_BTN_ID_SBLENDONOFF].ResetGameBtn(297, 297, -1);
	}
	else
	{
		m_xOptionBtn[_BTN_ID_SBLENDONOFF].ResetGameBtn(301, 301, 299);
	}

	if ( m_bReversePanON )
	{
		m_xOptionBtn[_NEW_BTN_ID_ANTIPANONOFF].ResetGameBtn(297, 297, -1);
	}
	else
	{
		m_xOptionBtn[_NEW_BTN_ID_ANTIPANONOFF].ResetGameBtn(301, 301, 299);
	}

	if ( g_xGameProc.m_xInterface.m_xMiniMap.m_bShowMonInfo )
	{
		m_xOptionBtn[_BTN_ID_SHOWMONINMAP].ResetGameBtn(297, 297, -1);
	}
	else
	{
		m_xOptionBtn[_BTN_ID_SHOWMONINMAP].ResetGameBtn(301, 301, 299);
	}

	if ( g_xGameProc.m_bAttackUser )
	{
		m_xOptionBtn[_BTN_ID_ATTACKUSER].ResetGameBtn(297, 297, -1);
	}
	else
	{
		m_xOptionBtn[_BTN_ID_ATTACKUSER].ResetGameBtn(301, 301, 299);
	}

	if ( g_xGameProc.m_bDrawMagicLight )
	{
		m_xOptionBtn[_BTN_ID_MAGICLIGHT].ResetGameBtn(297, 297, -1);
	}
	else
	{
		m_xOptionBtn[_BTN_ID_MAGICLIGHT].ResetGameBtn(301, 301, 299);
	}

	if ( g_xGameProc.m_bShowBloodNum )
	{
		m_xOptionBtn[_BTN_ID_SHOWBLOODNUM].ResetGameBtn(297, 297, -1);
	}
	else
	{
		m_xOptionBtn[_BTN_ID_SHOWBLOODNUM].ResetGameBtn(301, 301, 299);
	}

	if ( g_xGameProc.m_xInterface.m_bShowUserPic )
	{
		m_xOptionBtn[_BTN_ID_DRAWUSERPIC].ResetGameBtn(297, 297, -1);
	}
	else
	{
		m_xOptionBtn[_BTN_ID_DRAWUSERPIC].ResetGameBtn(301, 301, 299);
	}

	if ( g_xGameProc.m_bShowHelmet )
	{
		m_xOptionBtn[_BTN_ID_SHOWHELMET].ResetGameBtn(297, 297, -1);
	}
	else
	{
		m_xOptionBtn[_BTN_ID_SHOWHELMET].ResetGameBtn(301, 301, 299);
	}

	if ( g_xGameProc.m_bShowMonEffect )
	{
		m_xOptionBtn[_BTN_ID_MONEFFECT].ResetGameBtn(297, 297, -1);
	}
	else
	{
		m_xOptionBtn[_BTN_ID_MONEFFECT].ResetGameBtn(301, 301, 299);
	}

	if ( g_xGameProc.m_bShowDeying )
	{
		m_xOptionBtn[_BTN_ID_SHOWDEYING].ResetGameBtn(297, 297, -1);
	}
	else
	{
		m_xOptionBtn[_BTN_ID_SHOWDEYING].ResetGameBtn(301, 301, 299);
	}

	if ( g_xGameProc.m_bAutoPickup )
	{
		m_xOptionBtn[_BTN_ID_AUTOPICKUP].ResetGameBtn(297, 297, -1);
	}
	else
	{
		m_xOptionBtn[_BTN_ID_AUTOPICKUP].ResetGameBtn(301, 301, 299);
	}

	if ( g_xGameProc.m_bDrawGroundItemName )
	{
		m_xOptionBtn[_BTN_ID_SHOWDROPITEM].ResetGameBtn(297, 297, -1);
	}
	else
	{
		m_xOptionBtn[_BTN_ID_SHOWDROPITEM].ResetGameBtn(301, 301, 299);
	}

	if ( g_xGameProc.m_bDrawHealthNum )
	{
		m_xOptionBtn[_BTN_ID_SHOWHEALTHNUM].ResetGameBtn(297, 297, -1);
	}
	else
	{
		m_xOptionBtn[_BTN_ID_SHOWHEALTHNUM].ResetGameBtn(301, 301, 299);
	}
}


VOID COptionWnd::ShowOptionWnd()
{
	INT nCnt;
	ShowGameWnd();

	SetRect(&mOptionWnd_rcBasicTab, m_rcWnd.left+5, m_rcWnd.top+8, m_rcWnd.left+75, m_rcWnd.top+34);
	SetRect(&mOptionWnd_rcAllowTab, m_rcWnd.left+75, m_rcWnd.top+8, m_rcWnd.left+145, m_rcWnd.top+34);
	SetRect(&mOptionWnd_rcChatTab, m_rcWnd.left+145, m_rcWnd.top+8, m_rcWnd.left+215, m_rcWnd.top+34);
	SetRect(&mOptionWnd_rcVisualTab, m_rcWnd.left+215, m_rcWnd.top+8, m_rcWnd.left+285, m_rcWnd.top+34);

	switch(mOptionWnd_nMode)
	{
	case _BASIC_SET:
		ShowBasicSet();
		break;
	case _ALLOW_SET:
		ShowAllowSet();
		break;
	case _CHAT_SET:
		ShowChatSet();
		break;
	case _VISUAL_SET:
		ShowVisualSet();
		break;
	}

	m_xOptionBtn[_BTN_ID_OPTIONCLOSE].ChangeRect(m_rcWnd.left+240, m_rcWnd.top+345);
	m_xOptionBtn[_BTN_ID_OPTIONCLOSE].ShowGameBtn();
/*
	m_xOptionBtn[_BTN_ID_OPTIONCLOSE].ChangeRect(m_rcWnd.left+690, m_rcWnd.top+415);

	// 왼쪽 열
	m_xOptionBtn[_BTN_ID_SHOWMONINMAP].ChangeRect(m_rcWnd.left+186, m_rcWnd.top+55);
	m_xOptionBtn[_BTN_ID_GUILDJOINMODE].ChangeRect(m_rcWnd.left+186, m_rcWnd.top+85);	
	m_xOptionBtn[_BTN_ID_MAGICLIGHT].ChangeRect(m_rcWnd.left+186, m_rcWnd.top+115);
	m_xOptionBtn[_BTN_ID_SHOWBLOODNUM].ChangeRect(m_rcWnd.left+186, m_rcWnd.top+145);
	m_xOptionBtn[_BTN_ID_REVIVAL].ChangeRect(m_rcWnd.left+186, m_rcWnd.top+175);
	m_xOptionBtn[_BTN_ID_CHUNJIHAPIL].ChangeRect(m_rcWnd.left+186, m_rcWnd.top+205);	
	m_xOptionBtn[_BTN_ID_EXCHANGEMODE].ChangeRect(m_rcWnd.left+186, m_rcWnd.top+235);
	m_xOptionBtn[_BTN_ID_SHOWHELMET].ChangeRect(m_rcWnd.left+186, m_rcWnd.top+265);

	// 가운데 열
	m_xOptionBtn[_BTN_ID_SHOUTMODE].ChangeRect(m_rcWnd.left+430, m_rcWnd.top+55);
	m_xOptionBtn[_NEW_BTN_ID_ANTIPANONOFF].ChangeRect(m_rcWnd.left+430, m_rcWnd.top+85);
	m_xOptionBtn[_BTN_ID_SBLENDONOFF].ChangeRect(m_rcWnd.left+430, m_rcWnd.top+115);
	m_xOptionBtn[_BTN_ID_ATTACKMODE].ChangeRect(m_rcWnd.left+430, m_rcWnd.top+145);
	m_xOptionBtn[_BTN_ID_DRAWUSERPIC].ChangeRect(m_rcWnd.left+430, m_rcWnd.top+175);
	m_xOptionBtn[_BTN_ID_WHISPERMODE].ChangeRect(m_rcWnd.left+430, m_rcWnd.top+205);
//	m_xOptionBtn[_BTN_ID_AUTOPICKUP].ChangeRect  (m_rcWnd.left+430, m_rcWnd.top+325);
//	m_xOptionBtn[_BTN_ID_SHOWDROPITEM].ChangeRect  (m_rcWnd.left+186, m_rcWnd.top+355);
//	m_xOptionBtn[_BTN_ID_SHOWHEALTHNUM].ChangeRect  (m_rcWnd.left+430, m_rcWnd.top+355);
	m_xOptionBtn[_BTN_ID_MONEFFECT].ChangeRect(m_rcWnd.left+430, m_rcWnd.top+235);

	// 오른쪽 열
	m_xOptionBtn[_BTN_ID_ATTACKUSER].ChangeRect(m_rcWnd.left+680, m_rcWnd.top+55);
	m_xOptionBtn[_BTN_ID_BGMONOFF].ChangeRect(m_rcWnd.left+680, m_rcWnd.top+85);
	m_xOptionBtn[_BTN_ID_BGMVOLUME].ChangeRect(m_rcWnd.left+18 + mOptionWnd_ptBgmVolBtn.x, m_rcWnd.top+138);
	m_xOptionBtn[_BTN_ID_SOUNDONOFF].ChangeRect(m_rcWnd.left+680, m_rcWnd.top+145);
	m_xOptionBtn[_BTN_ID_WAVEVOLUME].ChangeRect(m_rcWnd.left+18+ mOptionWnd_ptWaveVolBtn.x, m_rcWnd.top+178);
	m_xOptionBtn[_BTN_ID_GUILDWHISPERMODE].ChangeRect(m_rcWnd.left+680, m_rcWnd.top+205);
	m_xOptionBtn[_BTN_ID_SHOWDEYING].ChangeRect(m_rcWnd.left+680, m_rcWnd.top+235);

	m_xOptionBtn[_BTN_ID_OPTIONCLOSE].ShowGameBtn();
	m_xOptionBtn[_BTN_ID_BGMONOFF].ShowGameBtn();
	m_xOptionBtn[_BTN_ID_SOUNDONOFF].ShowGameBtn();
	m_xOptionBtn[_NEW_BTN_ID_ANTIPANONOFF].ShowGameBtn();
	m_xOptionBtn[_BTN_ID_SBLENDONOFF].ShowGameBtn();
	m_xOptionBtn[_BTN_ID_BGMVOLUME].ShowGameBtn();
	m_xOptionBtn[_BTN_ID_WAVEVOLUME].ShowGameBtn();
	m_xOptionBtn[_BTN_ID_SHOWMONINMAP].ShowGameBtn();
	m_xOptionBtn[_BTN_ID_ATTACKUSER].ShowGameBtn();
	m_xOptionBtn[_BTN_ID_MAGICLIGHT].ShowGameBtn();
	m_xOptionBtn[_BTN_ID_SHOWBLOODNUM].ShowGameBtn();
	m_xOptionBtn[_BTN_ID_REVIVAL].ShowGameBtn();
	m_xOptionBtn[_BTN_ID_CHUNJIHAPIL].ShowGameBtn();
	m_xOptionBtn[_BTN_ID_EXCHANGEMODE].ShowGameBtn();
	m_xOptionBtn[_BTN_ID_WHISPERMODE].ShowGameBtn();
	m_xOptionBtn[_BTN_ID_GUILDWHISPERMODE].ShowGameBtn();
	m_xOptionBtn[_BTN_ID_GUILDJOINMODE].ShowGameBtn();
	m_xOptionBtn[_BTN_ID_SHOUTMODE].ShowGameBtn();
	m_xOptionBtn[_BTN_ID_ATTACKMODE].ShowGameBtn();
	m_xOptionBtn[_BTN_ID_DRAWUSERPIC].ShowGameBtn();
	m_xOptionBtn[_BTN_ID_SHOWDEYING].ShowGameBtn();
	m_xOptionBtn[_BTN_ID_SHOWHELMET].ShowGameBtn();
	m_xOptionBtn[_BTN_ID_MONEFFECT].ShowGameBtn();
//	m_xOptionBtn[_BTN_ID_AUTOPICKUP].ShowGameBtn();
//	m_xOptionBtn[_BTN_ID_SHOWDROPITEM].ShowGameBtn();
//	m_xOptionBtn[_BTN_ID_SHOWHEALTHNUM].ShowGameBtn();

	RECT	rcMenu;
	CHAR	pszTmp[MAX_PATH];

	sprintf(pszTmp, g_xMsg.GetMsg(2104));
	SetRect(&rcMenu, m_rcWnd.left+350, m_rcWnd.top+30, m_rcWnd.left+415, m_rcWnd.top+45);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(250, 220, 248), RGB(0, 0, 0), pszTmp);

	sprintf(pszTmp, g_xMsg.GetMsg(2114));
	SetRect(&rcMenu, m_rcWnd.left+20, m_rcWnd.top+89, m_rcWnd.left+175, m_rcWnd.top+110);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	sprintf(pszTmp, g_xMsg.GetMsg(2105));
	SetRect(&rcMenu, m_rcWnd.left+20, m_rcWnd.top+62, m_rcWnd.left+175, m_rcWnd.top+77);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	sprintf(pszTmp, g_xMsg.GetMsg(2107));
	SetRect(&rcMenu, m_rcWnd.left+20, m_rcWnd.top+122, m_rcWnd.left+175, m_rcWnd.top+137);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	sprintf(pszTmp, g_xMsg.GetMsg(2108));
	SetRect(&rcMenu, m_rcWnd.left+20, m_rcWnd.top+152, m_rcWnd.left+175, m_rcWnd.top+167);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	sprintf(pszTmp, g_xMsg.GetMsg(2109));
	SetRect(&rcMenu, m_rcWnd.left+20, m_rcWnd.top+182, m_rcWnd.left+175, m_rcWnd.top+197);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	sprintf(pszTmp, g_xMsg.GetMsg(2110));
	SetRect(&rcMenu, m_rcWnd.left+20, m_rcWnd.top+212, m_rcWnd.left+175, m_rcWnd.top+227);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	sprintf(pszTmp, g_xMsg.GetMsg(2111));
	SetRect(&rcMenu, m_rcWnd.left+20, m_rcWnd.top+242, m_rcWnd.left+175, m_rcWnd.top+257);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	sprintf(pszTmp, g_xMsg.GetMsg(2144));
	SetRect(&rcMenu, m_rcWnd.left+20, m_rcWnd.top+272, m_rcWnd.left+175, m_rcWnd.top+287);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	// 가운데 열
	sprintf(pszTmp, g_xMsg.GetMsg(2115));
	SetRect(&rcMenu, m_rcWnd.left+266, m_rcWnd.top+62, m_rcWnd.left+422, m_rcWnd.top+77);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	sprintf(pszTmp, g_xMsg.GetMsg(2102));	
	SetRect(&rcMenu, m_rcWnd.left+266, m_rcWnd.top+89, m_rcWnd.left+422, m_rcWnd.top+110);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	sprintf(pszTmp, g_xMsg.GetMsg(2103));
	SetRect(&rcMenu, m_rcWnd.left+266, m_rcWnd.top+122, m_rcWnd.left+422, m_rcWnd.top+137);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	if ( mOptionWnd_nAttackMode == 0 )
		sprintf(pszTmp, g_xMsg.GetMsg(2116));
	else if ( mOptionWnd_nAttackMode == 1 )
		sprintf(pszTmp, g_xMsg.GetMsg(2117));
	else if ( mOptionWnd_nAttackMode == 2 )
		sprintf(pszTmp, g_xMsg.GetMsg(2118));
	else if ( mOptionWnd_nAttackMode == 3 )
		sprintf(pszTmp, g_xMsg.GetMsg(2119));
	else if ( mOptionWnd_nAttackMode == 4 )
		sprintf(pszTmp, g_xMsg.GetMsg(2120));
	SetRect(&rcMenu, m_rcWnd.left+266, m_rcWnd.top+152, m_rcWnd.left+422, m_rcWnd.top+167);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	sprintf(pszTmp, g_xMsg.GetMsg(2130));
	SetRect(&rcMenu, m_rcWnd.left+266, m_rcWnd.top+182, m_rcWnd.left+422, m_rcWnd.top+197);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	sprintf(pszTmp, g_xMsg.GetMsg(2112));
	SetRect(&rcMenu, m_rcWnd.left+266, m_rcWnd.top+212, m_rcWnd.left+422, m_rcWnd.top+227);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	sprintf(pszTmp, g_xMsg.GetMsg(2142));
	SetRect(&rcMenu, m_rcWnd.left+266, m_rcWnd.top+242, m_rcWnd.left+422, m_rcWnd.top+257);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);


	// 오른쪽 열
	sprintf(pszTmp, g_xMsg.GetMsg(2106));
	SetRect(&rcMenu, m_rcWnd.left+516, m_rcWnd.top+59, m_rcWnd.left+676, m_rcWnd.top+80);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	sprintf(pszTmp, g_xMsg.GetMsg(2100));
	SetRect(&rcMenu, m_rcWnd.left+516, m_rcWnd.top+89, m_rcWnd.left+676, m_rcWnd.top+110);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);
	
	sprintf(pszTmp, g_xMsg.GetMsg(2101));
	SetRect(&rcMenu, m_rcWnd.left+516, m_rcWnd.top+149, m_rcWnd.left+676, m_rcWnd.top+170);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	sprintf(pszTmp, g_xMsg.GetMsg(2113));
	SetRect(&rcMenu, m_rcWnd.left+516, m_rcWnd.top+209, m_rcWnd.left+676, m_rcWnd.top+230);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	sprintf(pszTmp, g_xMsg.GetMsg(2143));
	SetRect(&rcMenu, m_rcWnd.left+516, m_rcWnd.top+239, m_rcWnd.left+676, m_rcWnd.top+260);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

//	g_xMainWnd.DrawWithGDI(&rcMenu, NULL, RGB(200, 200, 200), 1);


/*
	sprintf(pszTmp, g_xMsg.GetMsg(2139));
	SetRect(&rcMenu, m_rcWnd.left+266, m_rcWnd.top+332, m_rcWnd.left+422, m_rcWnd.top+347);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	sprintf(pszTmp, g_xMsg.GetMsg(2140));
	SetRect(&rcMenu, m_rcWnd.left+20, m_rcWnd.top+362, m_rcWnd.left+175, m_rcWnd.top+377);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	sprintf(pszTmp, g_xMsg.GetMsg(2141));
	SetRect(&rcMenu, m_rcWnd.left+266, m_rcWnd.top+362, m_rcWnd.left+422, m_rcWnd.top+377);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);
*/
}


VOID COptionWnd::ShowBasicSet()
{
	CHAR pszTmp[MAX_PATH];
	RECT rcMenu;

	g_xMainWnd.PutsHan(NULL, mOptionWnd_rcBasicTab, RGB(190, 190, 255), RGB(0, 0, 0), g_xMsg.GetMsg(2149));
	g_xMainWnd.PutsHan(NULL, mOptionWnd_rcAllowTab, RGB(200, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(2150));
	g_xMainWnd.PutsHan(NULL, mOptionWnd_rcChatTab, RGB(200, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(2151));
	g_xMainWnd.PutsHan(NULL, mOptionWnd_rcVisualTab, RGB(200, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(2152));

	m_xOptionBtn[_BTN_ID_ATTACKMODE].ChangeRect(m_rcWnd.left+209, m_rcWnd.top+48);
	m_xOptionBtn[_BTN_ID_ATTACKMODE].ShowGameBtn();

	m_xOptionBtn[_BTN_ID_ATTACKUSER].ChangeRect(m_rcWnd.left+209, m_rcWnd.top+78);
	m_xOptionBtn[_BTN_ID_ATTACKUSER].ShowGameBtn();	

	m_xOptionBtn[_BTN_ID_CHANGEWEATHER].ChangeRect(m_rcWnd.left+209, m_rcWnd.top+319);
	m_xOptionBtn[_BTN_ID_CHANGEWEATHER].ShowGameBtn();

	if ( mOptionWnd_nAttackMode == 0 )
		sprintf(pszTmp, g_xMsg.GetMsg(2116));
	else if ( mOptionWnd_nAttackMode == 1 )
		sprintf(pszTmp, g_xMsg.GetMsg(2117));
	else if ( mOptionWnd_nAttackMode == 2 )
		sprintf(pszTmp, g_xMsg.GetMsg(2118));
	else if ( mOptionWnd_nAttackMode == 3 )
		sprintf(pszTmp, g_xMsg.GetMsg(2119));
	else if ( mOptionWnd_nAttackMode == 4 )
		sprintf(pszTmp, g_xMsg.GetMsg(2120));
	SetRect(&rcMenu, m_rcWnd.left+17, m_rcWnd.top+48, m_rcWnd.left+200, m_rcWnd.top+70);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	RECT rcTemp = { m_rcWnd.left+18 , m_rcWnd.top+138, m_rcWnd.left+202, m_rcWnd.top+160 };

	m_xOptionBtn[_BTN_ID_BGMONOFF].ChangeRect(m_rcWnd.left+209, m_rcWnd.top+108);
	m_xOptionBtn[_BTN_ID_BGMONOFF].ShowGameBtn();

	m_xOptionBtn[_BTN_ID_SOUNDONOFF].ChangeRect(m_rcWnd.left+209, m_rcWnd.top+168);
	m_xOptionBtn[_BTN_ID_SOUNDONOFF].ShowGameBtn();
	
	RECT	rcVolume;
	FLOAT	fVolRate = 0.0f;

	fVolRate = (FLOAT)((FLOAT)mOptionWnd_ptBgmVolBtn.x/(FLOAT)174);
	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(305) )
	{
		SetRect(&rcVolume, 0, 0, 
				(INT)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth*fVolRate),
				g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight);
 		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+18, m_rcWnd.top+138, &rcVolume, (WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
	}

	m_xOptionBtn[_BTN_ID_BGMVOLUME].ChangeRect(m_rcWnd.left+18 + mOptionWnd_ptBgmVolBtn.x, m_rcWnd.top+138);
	m_xOptionBtn[_BTN_ID_BGMVOLUME].ShowGameBtn();

	fVolRate = (FLOAT)((FLOAT)mOptionWnd_ptWaveVolBtn.x/(FLOAT)174);
	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(305) )
	{
		SetRect(&rcVolume, 0, 0, 
				(INT)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth*fVolRate),
				g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight);
 		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+18, m_rcWnd.top+198, &rcVolume, (WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
	}

	m_xOptionBtn[_BTN_ID_WAVEVOLUME].ChangeRect(m_rcWnd.left+18 + mOptionWnd_ptWaveVolBtn.x, m_rcWnd.top+198);
	m_xOptionBtn[_BTN_ID_WAVEVOLUME].ShowGameBtn();

	m_xOptionBtn[_NEW_BTN_ID_ANTIPANONOFF].ChangeRect(m_rcWnd.left+209, m_rcWnd.top+228);
	m_xOptionBtn[_NEW_BTN_ID_ANTIPANONOFF].ShowGameBtn();

	m_xOptionBtn[_BTN_ID_AUTOPICKUP].ChangeRect(m_rcWnd.left+209, m_rcWnd.top+258);
	m_xOptionBtn[_BTN_ID_AUTOPICKUP].ShowGameBtn();

	m_xOptionBtn[_BTN_ID_SHOWDROPITEM].ChangeRect(m_rcWnd.left+209, m_rcWnd.top+288);
	m_xOptionBtn[_BTN_ID_SHOWDROPITEM].ShowGameBtn();
	

	// 강제공격모드
	sprintf(pszTmp, g_xMsg.GetMsg(2106));
	SetRect(&rcMenu, m_rcWnd.left+17, m_rcWnd.top+78, m_rcWnd.left+200, m_rcWnd.top+100);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	// 배경음
	sprintf(pszTmp, g_xMsg.GetMsg(2100));
	SetRect(&rcMenu, m_rcWnd.left+17, m_rcWnd.top+108, m_rcWnd.left+200, m_rcWnd.top+130);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	// 효과음
	sprintf(pszTmp, g_xMsg.GetMsg(2101));
	SetRect(&rcMenu, m_rcWnd.left+17, m_rcWnd.top+168, m_rcWnd.left+200, m_rcWnd.top+190);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	// 사운드 좌우 반전
	sprintf(pszTmp, g_xMsg.GetMsg(2102));
	SetRect(&rcMenu, m_rcWnd.left+17, m_rcWnd.top+228, m_rcWnd.left+200, m_rcWnd.top+250);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	// 자동 줍기
	sprintf(pszTmp, g_xMsg.GetMsg(2139));
	SetRect(&rcMenu, m_rcWnd.left+17, m_rcWnd.top+258, m_rcWnd.left+200, m_rcWnd.top+280);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	// 아이템 이름 보이기
	sprintf(pszTmp, g_xMsg.GetMsg(2136));
	SetRect(&rcMenu, m_rcWnd.left+17, m_rcWnd.top+288, m_rcWnd.left+200, m_rcWnd.top+310);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	RECT rcTmp = {m_rcWnd.left+17, m_rcWnd.top+318, m_rcWnd.left+200, m_rcWnd.top+340};
	g_xMainWnd.DrawWithGDI(&rcTmp, NULL, RGB(0, 0, 0), 2);

}

VOID COptionWnd::ShowAllowSet()
{
	CHAR pszTmp[MAX_PATH];
	RECT rcMenu;

	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(291) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left - 111, m_rcWnd.top - 61, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
	}

	g_xMainWnd.PutsHan(NULL, mOptionWnd_rcBasicTab, RGB(200, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(2149));
	g_xMainWnd.PutsHan(NULL, mOptionWnd_rcAllowTab, RGB(190, 190, 255), RGB(0, 0, 0), g_xMsg.GetMsg(2150));
	g_xMainWnd.PutsHan(NULL, mOptionWnd_rcChatTab, RGB(200, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(2151));
	g_xMainWnd.PutsHan(NULL, mOptionWnd_rcVisualTab, RGB(200, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(2152));

	m_xOptionBtn[_BTN_ID_ALLOWGROUP].ChangeRect(m_rcWnd.left+209, m_rcWnd.top+48);
	m_xOptionBtn[_BTN_ID_ALLOWGROUP].ShowGameBtn();

	m_xOptionBtn[_BTN_ID_GUILDJOINMODE].ChangeRect(m_rcWnd.left+209, m_rcWnd.top+78);
	m_xOptionBtn[_BTN_ID_GUILDJOINMODE].ShowGameBtn();

	m_xOptionBtn[_BTN_ID_REVIVAL].ChangeRect(m_rcWnd.left+209, m_rcWnd.top+108);
	m_xOptionBtn[_BTN_ID_REVIVAL].ShowGameBtn();

	m_xOptionBtn[_BTN_ID_CHUNJIHAPIL].ChangeRect(m_rcWnd.left+209, m_rcWnd.top+138);
	m_xOptionBtn[_BTN_ID_CHUNJIHAPIL].ShowGameBtn();

	m_xOptionBtn[_BTN_ID_EXCHANGEMODE].ChangeRect(m_rcWnd.left+209, m_rcWnd.top+168);
	m_xOptionBtn[_BTN_ID_EXCHANGEMODE].ShowGameBtn();

	// 그룹 추가 허용
	sprintf(pszTmp, g_xMsg.GetMsg(2146));
	SetRect(&rcMenu, m_rcWnd.left+17, m_rcWnd.top+48, m_rcWnd.left+200, m_rcWnd.top+70);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	// 문파 가입 허용
	sprintf(pszTmp, g_xMsg.GetMsg(2114));
	SetRect(&rcMenu, m_rcWnd.left+17, m_rcWnd.top+78, m_rcWnd.left+200, m_rcWnd.top+100);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	// 소생술 허용
	sprintf(pszTmp, g_xMsg.GetMsg(2109));
	SetRect(&rcMenu, m_rcWnd.left+17, m_rcWnd.top+108, m_rcWnd.left+200, m_rcWnd.top+130);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	// 천지합일 허용
	sprintf(pszTmp, g_xMsg.GetMsg(2110));
	SetRect(&rcMenu, m_rcWnd.left+17, m_rcWnd.top+138, m_rcWnd.left+200, m_rcWnd.top+160);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	// 교환 허용
	sprintf(pszTmp, g_xMsg.GetMsg(2111));
	SetRect(&rcMenu, m_rcWnd.left+17, m_rcWnd.top+168, m_rcWnd.left+200, m_rcWnd.top+190);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

}

VOID COptionWnd::ShowChatSet()
{
	CHAR pszTmp[MAX_PATH];
	RECT rcMenu;

	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(292) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left - 111, m_rcWnd.top - 61, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
	}

	g_xMainWnd.PutsHan(NULL, mOptionWnd_rcBasicTab, RGB(200, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(2149));
	g_xMainWnd.PutsHan(NULL, mOptionWnd_rcAllowTab, RGB(200, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(2150));
	g_xMainWnd.PutsHan(NULL, mOptionWnd_rcChatTab, RGB(190, 190, 255), RGB(0, 0, 0), g_xMsg.GetMsg(2151));
	g_xMainWnd.PutsHan(NULL, mOptionWnd_rcVisualTab, RGB(200, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(2152));

	m_xOptionBtn[_BTN_ID_WHISPERMODE].ChangeRect(m_rcWnd.left+209, m_rcWnd.top+48);
	m_xOptionBtn[_BTN_ID_WHISPERMODE].ShowGameBtn();

	m_xOptionBtn[_BTN_ID_SHOUTMODE].ChangeRect(m_rcWnd.left+209, m_rcWnd.top+78);
	m_xOptionBtn[_BTN_ID_SHOUTMODE].ShowGameBtn();

	m_xOptionBtn[_BTN_ID_GUILDWHISPERMODE].ChangeRect(m_rcWnd.left+209, m_rcWnd.top+138);
	m_xOptionBtn[_BTN_ID_GUILDWHISPERMODE].ShowGameBtn();

	m_xOptionBtn[_BTN_ID_CUTSOMEONE].ChangeRect(m_rcWnd.left+209, m_rcWnd.top+168);
	m_xOptionBtn[_BTN_ID_CUTSOMEONE].ShowGameBtn();

	m_xOptionBtn[_BTN_ID_WHOLESHOUTMODE].ChangeRect(m_rcWnd.left+209, m_rcWnd.top+108);
	m_xOptionBtn[_BTN_ID_WHOLESHOUTMODE].ShowGameBtn();

	// 귀엣말 허용
	sprintf(pszTmp, g_xMsg.GetMsg(2112));
	SetRect(&rcMenu, m_rcWnd.left+17, m_rcWnd.top+48, m_rcWnd.left+200, m_rcWnd.top+70);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	// 외치기 허용
	sprintf(pszTmp, g_xMsg.GetMsg(2115));
	SetRect(&rcMenu, m_rcWnd.left+17, m_rcWnd.top+78, m_rcWnd.left+200, m_rcWnd.top+100);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	// 전체외치기 허용
	sprintf(pszTmp, g_xMsg.GetMsg(2164));
	SetRect(&rcMenu, m_rcWnd.left+17, m_rcWnd.top+108, m_rcWnd.left+200, m_rcWnd.top+130);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	// 문파 전음 허용
	sprintf(pszTmp, g_xMsg.GetMsg(2113));
	SetRect(&rcMenu, m_rcWnd.left+17, m_rcWnd.top+138, m_rcWnd.left+200, m_rcWnd.top+160);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	// 특정 유저 귓말 차단
	sprintf(pszTmp, g_xMsg.GetMsg(2160));
	SetRect(&rcMenu, m_rcWnd.left+17, m_rcWnd.top+168, m_rcWnd.left+200, m_rcWnd.top+190);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

}

VOID COptionWnd::ShowVisualSet()
{
	CHAR pszTmp[MAX_PATH];
	RECT rcMenu;

	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(293) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left - 111, m_rcWnd.top - 61, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
	}

	g_xMainWnd.PutsHan(NULL, mOptionWnd_rcBasicTab, RGB(200, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(2149));
	g_xMainWnd.PutsHan(NULL, mOptionWnd_rcAllowTab, RGB(200, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(2150));
	g_xMainWnd.PutsHan(NULL, mOptionWnd_rcChatTab, RGB(200, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(2151));
	g_xMainWnd.PutsHan(NULL, mOptionWnd_rcVisualTab, RGB(190, 190, 255), RGB(0, 0, 0), g_xMsg.GetMsg(2152));

	m_xOptionBtn[_BTN_ID_SHOWBLOODNUM].ChangeRect(m_rcWnd.left+209, m_rcWnd.top+48);
	m_xOptionBtn[_BTN_ID_SHOWBLOODNUM].ShowGameBtn();

	m_xOptionBtn[_BTN_ID_MAGICLIGHT].ChangeRect(m_rcWnd.left+209, m_rcWnd.top+78);
	m_xOptionBtn[_BTN_ID_MAGICLIGHT].ShowGameBtn();

	m_xOptionBtn[_BTN_ID_SBLENDONOFF].ChangeRect(m_rcWnd.left+209, m_rcWnd.top+108);
	m_xOptionBtn[_BTN_ID_SBLENDONOFF].ShowGameBtn();

	m_xOptionBtn[_BTN_ID_SHOWHELMET].ChangeRect(m_rcWnd.left+209, m_rcWnd.top+138);
	m_xOptionBtn[_BTN_ID_SHOWHELMET].ShowGameBtn();

	m_xOptionBtn[_BTN_ID_MONEFFECT].ChangeRect(m_rcWnd.left+209, m_rcWnd.top+168);
	m_xOptionBtn[_BTN_ID_MONEFFECT].ShowGameBtn();

	m_xOptionBtn[_BTN_ID_SHOWDEYING].ChangeRect(m_rcWnd.left+209, m_rcWnd.top+198);
	m_xOptionBtn[_BTN_ID_SHOWDEYING].ShowGameBtn();

	m_xOptionBtn[_BTN_ID_DRAWUSERPIC].ChangeRect(m_rcWnd.left+209, m_rcWnd.top+228);
	m_xOptionBtn[_BTN_ID_DRAWUSERPIC].ShowGameBtn();

	m_xOptionBtn[_BTN_ID_SHOWMONINMAP].ChangeRect(m_rcWnd.left+209, m_rcWnd.top+258);
	m_xOptionBtn[_BTN_ID_SHOWMONINMAP].ShowGameBtn();

	m_xOptionBtn[_BTN_ID_SHOWHEALTHBAR].ChangeRect(m_rcWnd.left+209, m_rcWnd.top+288);
	m_xOptionBtn[_BTN_ID_SHOWHEALTHBAR].ShowGameBtn();

	m_xOptionBtn[_BTN_ID_SHOWHEALTHNUM].ChangeRect(m_rcWnd.left+209, m_rcWnd.top+318);
	m_xOptionBtn[_BTN_ID_SHOWHEALTHNUM].ShowGameBtn();
	
	// 체력변화 표시
	sprintf(pszTmp, g_xMsg.GetMsg(2108));
	SetRect(&rcMenu, m_rcWnd.left+17, m_rcWnd.top+48, m_rcWnd.left+200, m_rcWnd.top+70);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	// 마법광원 표시
	sprintf(pszTmp, g_xMsg.GetMsg(2107));
	SetRect(&rcMenu, m_rcWnd.left+17, m_rcWnd.top+78, m_rcWnd.left+200, m_rcWnd.top+100);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	// 그림자 투명 효과
	sprintf(pszTmp, g_xMsg.GetMsg(2103));
	SetRect(&rcMenu, m_rcWnd.left+17, m_rcWnd.top+108, m_rcWnd.left+200, m_rcWnd.top+130);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	// 투구보이기
	sprintf(pszTmp, g_xMsg.GetMsg(2144));
	SetRect(&rcMenu, m_rcWnd.left+17, m_rcWnd.top+138, m_rcWnd.left+200, m_rcWnd.top+160);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	// 몬스터 이펙트 표시
	sprintf(pszTmp, g_xMsg.GetMsg(2142));
	SetRect(&rcMenu, m_rcWnd.left+17, m_rcWnd.top+168, m_rcWnd.left+200, m_rcWnd.top+190);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	// 염색 표시
	sprintf(pszTmp, g_xMsg.GetMsg(2143));
	SetRect(&rcMenu, m_rcWnd.left+17, m_rcWnd.top+198, m_rcWnd.left+200, m_rcWnd.top+220);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	// 유저그림 보이기
	sprintf(pszTmp, g_xMsg.GetMsg(2130));
	SetRect(&rcMenu, m_rcWnd.left+17, m_rcWnd.top+228, m_rcWnd.left+200, m_rcWnd.top+250);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	// 미니맵 몬스터 표시
	sprintf(pszTmp, g_xMsg.GetMsg(2105));
	SetRect(&rcMenu, m_rcWnd.left+17, m_rcWnd.top+258, m_rcWnd.left+200, m_rcWnd.top+280);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	// 체력바 표시
	sprintf(pszTmp, g_xMsg.GetMsg(2159));
	SetRect(&rcMenu, m_rcWnd.left+17, m_rcWnd.top+288, m_rcWnd.left+200, m_rcWnd.top+310);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	// 몬스터 이펙트 표시
	sprintf(pszTmp, g_xMsg.GetMsg(2138));
	SetRect(&rcMenu, m_rcWnd.left+17, m_rcWnd.top+318, m_rcWnd.left+200, m_rcWnd.top+340);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);
}

BOOL COptionWnd::OnLButtonUp(POINT ptMouse)
{
	INT nCnt;

	if (mOptionWnd_bMoveBgmVolBtn == TRUE)
	{
		mOptionWnd_bMoveBgmVolBtn = FALSE;
		return FALSE;
	}
	else if (mOptionWnd_bMoveWaveVolBtn == TRUE)
	{
		mOptionWnd_bMoveWaveVolBtn = FALSE;
		return FALSE;
	}

	if (ptMouse.x > m_rcWnd.left+516 && ptMouse.x < m_rcWnd.left+202 &&
		ptMouse.y > m_rcWnd.top+138 && ptMouse.y < m_rcWnd.top+160)
	{
		if (ptMouse.x > m_rcWnd.left+18+mOptionWnd_ptBgmVolBtn.x+16 ||
		    (ptMouse.x > m_rcWnd.left+727 && ptMouse.x < m_rcWnd.left+202) )
		{
			mOptionWnd_ptBgmVolBtn.x += 9;
			if (mOptionWnd_ptBgmVolBtn.x > 180)
				mOptionWnd_ptBgmVolBtn.x = 185;
			g_SoundManager.SndmngrPlayWavSound(_SOUND_GLASS_BUTTON, 0, 0);
		}
		else if (ptMouse.x < m_rcWnd.left+18+mOptionWnd_ptBgmVolBtn.x ||
				 (ptMouse.x > m_rcWnd.left+516 && ptMouse.x < m_rcWnd.left+275) )
		{
			mOptionWnd_ptBgmVolBtn.x -= 9;
			if (mOptionWnd_ptBgmVolBtn.x < 0)
				mOptionWnd_ptBgmVolBtn.x = 0;
			g_SoundManager.SndmngrPlayWavSound(_SOUND_GLASS_BUTTON, 0, 0);
		}

		OptionWndSetVolume(_SET_BGMVOL);
		return FALSE;
	}
	else if (ptMouse.x > m_rcWnd.left+516 && ptMouse.x < m_rcWnd.left+202 &&
			 ptMouse.y > m_rcWnd.top+176 && ptMouse.y < m_rcWnd.top+198)
	{
		if (ptMouse.x > m_rcWnd.left+18+mOptionWnd_ptWaveVolBtn.x+16 ||
		    (ptMouse.x > m_rcWnd.left+727 && ptMouse.x < m_rcWnd.left+202) )
		{
			mOptionWnd_ptWaveVolBtn.x += 9;
			if (mOptionWnd_ptWaveVolBtn.x > 180)
				mOptionWnd_ptWaveVolBtn.x = 185;
			g_SoundManager.SndmngrPlayWavSound(_SOUND_GLASS_BUTTON, 0, 0);
		}
		else if (ptMouse.x < m_rcWnd.left+18+mOptionWnd_ptWaveVolBtn.x ||
			     (ptMouse.x > m_rcWnd.left+516 && ptMouse.x < m_rcWnd.left+275) )
		{
			mOptionWnd_ptWaveVolBtn.x -= 9;
			if (mOptionWnd_ptWaveVolBtn.x < 0)
				mOptionWnd_ptWaveVolBtn.x = 0;
			g_SoundManager.SndmngrPlayWavSound(_SOUND_GLASS_BUTTON, 0, 0);
		}
		OptionWndSetVolume(_SET_WAVEVOL);
		return FALSE;
	}
	if ( m_xOptionBtn[_BTN_ID_OPTIONCLOSE].OnLButtonUp(ptMouse) )
		return TRUE;

	switch(mOptionWnd_nMode)
	{
	case _BASIC_SET:
		{
			if ( m_xOptionBtn[_BTN_ID_ATTACKMODE].OnLButtonUp(ptMouse) )
			{
				g_xClientSocket.SendSay(g_xMsg.GetMsg(1422));
			}

			if ( m_xOptionBtn[_BTN_ID_CHANGEWEATHER].OnLButtonUp(ptMouse) )
			{
				DWORD dwFogColor;

				dwFogColor = 0;
				g_xGameProc.m_bFogState++;

				if ( g_xGameProc.m_bFogState > _FOGSTATE_DAWN )
					g_xGameProc.m_bFogState = _FOGSTATE_DAY;

				switch ( g_xGameProc.m_bFogState )
				{
				case _FOGSTATE_DAY:
					{
						g_xGameProc.m_fDarkRate = 255.0f;
						dwFogColor = RGB(g_xGameProc.m_fDarkRate, g_xGameProc.m_fDarkRate, g_xGameProc.m_fDarkRate);
						break;
					}
				case _FOGSTATE_NIGHT:
					{
						g_xGameProc.m_fDarkRate = 15.0f;
						dwFogColor = RGB(g_xGameProc.m_fDarkRate, g_xGameProc.m_fDarkRate, g_xGameProc.m_fDarkRate);
						break;
					}
				case _FOGSTATE_DAWN:
				case _FOGSTATE_EVENING:
					{
						g_xGameProc.m_fDarkRate = 85.0f;
						dwFogColor = RGB(g_xGameProc.m_fDarkRate, g_xGameProc.m_fDarkRate, g_xGameProc.m_fDarkRate);
						break;
					}
				}

				g_xGameProc.m_xLightFog.ChangeLightColor(dwFogColor);
			}
			
			if ( m_xOptionBtn[_BTN_ID_ATTACKUSER].OnLButtonUp(ptMouse) )
			{
				DWORD dwFont = GetChatColor(_CHAT_COLOR3);
				DWORD dwBack = GetChatColor(_CHAT_COLOR8);

				if ( g_xGameProc.m_bAttackUser )
				{
					g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(1516));
					m_xOptionBtn[_BTN_ID_ATTACKUSER].ResetGameBtn(301, 301, 299);
					g_xGameProc.m_bAttackUser = FALSE;
				}
				else
				{
					g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(1515));
					m_xOptionBtn[_BTN_ID_ATTACKUSER].ResetGameBtn(297, 297, -1);
					g_xGameProc.m_bAttackUser = TRUE;
				}
				SetIniFile();
			}
			else if ( m_xOptionBtn[_BTN_ID_BGMONOFF].OnLButtonUp(ptMouse) )
			{
				DWORD dwFont = GetChatColor(_CHAT_COLOR3);
				DWORD dwBack = GetChatColor(_CHAT_COLOR8);

				if ( m_bBGMON == FALSE )
				{
					g_SoundManager.SndmngrSetEnableBGM();
					g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2153));
					g_SoundManager.SndmngrPlayMp3(g_xGameProc.m_xMap.m_pszMapName, TRUE, 0);
					m_xOptionBtn[_BTN_ID_BGMONOFF].ResetGameBtn(297, 297, -1);
					m_bBGMON	= TRUE;
					SetIniFile();
				}
				else
				{
					g_SoundManager.SndmngrStopMp3();
					g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2154));
					g_SoundManager.mSndMngr_bMP3Play = FALSE;
					m_xOptionBtn[_BTN_ID_BGMONOFF].ResetGameBtn(301, 301, 299);
					m_bBGMON	= FALSE;
					SetIniFile();
				}
			}
			else if ( m_xOptionBtn[_BTN_ID_SOUNDONOFF].OnLButtonUp(ptMouse) )
			{
				DWORD dwFont = GetChatColor(_CHAT_COLOR3);
				DWORD dwBack = GetChatColor(_CHAT_COLOR8);

				if ( m_bEffectON == FALSE )
				{
					g_SoundManager.SndmngrSetEnableWavePlay();

					g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2155));
					m_xOptionBtn[_BTN_ID_SOUNDONOFF].ResetGameBtn(297, 297, -1);
					m_bEffectON	= TRUE;
					SetIniFile();
				}
				else
				{
					g_SoundManager.SndmngrStopAllWaveSound();
					g_SoundManager.SndmngrSetDisableWavePlay();

					g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2156));
					m_xOptionBtn[_BTN_ID_SOUNDONOFF].ResetGameBtn(301, 301, 299);
					m_bEffectON	= FALSE;
					SetIniFile();
				}
				break;
			}
			else if ( m_xOptionBtn[_NEW_BTN_ID_ANTIPANONOFF].OnLButtonUp(ptMouse) )
			{
				DWORD dwFont = GetChatColor(_CHAT_COLOR3);
				DWORD dwBack = GetChatColor(_CHAT_COLOR8);

				if ( g_SoundManager.mSndMngr_bRevereLR == FALSE )
				{
//					g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, "[사운드 좌우 반전 On]");
					m_xOptionBtn[_NEW_BTN_ID_ANTIPANONOFF].ResetGameBtn(297, 297, -1);
					m_bReversePanON = TRUE;
					g_SoundManager.mSndMngr_bRevereLR = TRUE;
					SetIniFile();
				}
				else
				{
//					g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, "[사운드 좌우 반전 Off]");
					m_xOptionBtn[_NEW_BTN_ID_ANTIPANONOFF].ResetGameBtn(301, 301, 299);
					m_bReversePanON = FALSE;
					g_SoundManager.mSndMngr_bRevereLR = FALSE;
					SetIniFile();
				}
			}
			else if ( m_xOptionBtn[_BTN_ID_AUTOPICKUP].OnLButtonUp(ptMouse) )
			{
				DWORD dwFont = GetChatColor(_CHAT_COLOR3);
				DWORD dwBack = GetChatColor(_CHAT_COLOR8);

				if ( g_xGameProc.m_bAutoPickup )
				{
					g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2133));
					m_xOptionBtn[_BTN_ID_AUTOPICKUP].ResetGameBtn(301, 301, 299);
					g_xGameProc.m_bAutoPickup = FALSE;
				}
				else
				{
					g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2134));
					m_xOptionBtn[_BTN_ID_AUTOPICKUP].ResetGameBtn(297, 297, -1);
					g_xGameProc.m_bAutoPickup = TRUE;
				}
				SetIniFile();
			}
			else if ( m_xOptionBtn[_BTN_ID_SHOWDROPITEM].OnLButtonUp(ptMouse) )
			{
					DWORD dwFont = GetChatColor(_CHAT_COLOR3);
					DWORD dwBack = GetChatColor(_CHAT_COLOR8);

					if ( g_xGameProc.m_bDrawGroundItemName )
					{
						g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2135));
						m_xOptionBtn[_BTN_ID_SHOWDROPITEM].ResetGameBtn(301, 301, 299);
						g_xGameProc.m_bDrawGroundItemName = FALSE;
					}
					else
					{
						g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2136));
						m_xOptionBtn[_BTN_ID_SHOWDROPITEM].ResetGameBtn(297, 297, -1);
						g_xGameProc.m_bDrawGroundItemName = TRUE;
					}
					SetIniFile();
			}
		}
		break;
	case _ALLOW_SET:
		{
			if ( m_xOptionBtn[_BTN_ID_ALLOWGROUP].OnLButtonUp(ptMouse) )
			{
				(g_xGameProc.m_xInterface.m_xGroupWnd.m_bAllowGroup? g_xGameProc.m_xInterface.m_xGroupWnd.m_bAllowGroup = FALSE : g_xGameProc.m_xInterface.m_xGroupWnd.m_bAllowGroup = TRUE);
				g_xClientSocket.SendGroupMode(g_xGameProc.m_xInterface.m_xGroupWnd.m_bAllowGroup);

				DWORD dwFont = GetChatColor(_CHAT_COLOR3);
				DWORD dwBack = GetChatColor(_CHAT_COLOR8);

				if ( g_xGameProc.m_xInterface.m_xGroupWnd.m_bAllowGroup )
				{
					g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2157));
					g_xGameProc.m_xInterface.m_xGroupWnd.m_xGroupBtn[_BTN_ID_GROUPICON].ResetGameBtn(177, 177, 177);
					m_xOptionBtn[_BTN_ID_ALLOWGROUP].ResetGameBtn(297, 297, -1);
				}
				else
				{
					g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2158));
					g_xGameProc.m_xInterface.m_xGroupWnd.m_xGroupBtn[_BTN_ID_GROUPICON].ResetGameBtn(178, 178, 178);
					m_xOptionBtn[_BTN_ID_ALLOWGROUP].ResetGameBtn(301, 301, 299);
				}
			}
			else if ( m_xOptionBtn[_BTN_ID_GUILDJOINMODE].OnLButtonUp(ptMouse) )
			{
				g_xClientSocket.SendSay(g_xMsg.GetMsg(2128));

				if ( mOptionWnd_bGuildJoinMode )
				{	
					m_xOptionBtn[_BTN_ID_GUILDJOINMODE].ResetGameBtn(297, 297, -1);
				}
				else
				{
					m_xOptionBtn[_BTN_ID_GUILDJOINMODE].ResetGameBtn(301, 301, 299);
				}
			}
			else if ( m_xOptionBtn[_BTN_ID_REVIVAL].OnLButtonUp(ptMouse) )
			{
				g_xClientSocket.SendSay(g_xMsg.GetMsg(2123));

				if ( mOptionWnd_bRevival )
				{
					m_xOptionBtn[_BTN_ID_REVIVAL].ResetGameBtn(297, 297, -1);
				}
				else
				{
					m_xOptionBtn[_BTN_ID_REVIVAL].ResetGameBtn(301, 301, 299);
				}
			}
			else if ( m_xOptionBtn[_BTN_ID_CHUNJIHAPIL].OnLButtonUp(ptMouse) )
			{
				g_xClientSocket.SendSay(g_xMsg.GetMsg(2124));

				if ( mOptionWnd_bChunjihapil )
				{	
					m_xOptionBtn[_BTN_ID_CHUNJIHAPIL].ResetGameBtn(301, 301, 299);
				}
				else
				{
					m_xOptionBtn[_BTN_ID_CHUNJIHAPIL].ResetGameBtn(297, 297, -1);
				}
			}
			else if ( m_xOptionBtn[_BTN_ID_EXCHANGEMODE].OnLButtonUp(ptMouse) )
			{
				g_xClientSocket.SendSay(g_xMsg.GetMsg(2125));

				if ( mOptionWnd_bExchangeMode )
				{	
					m_xOptionBtn[_BTN_ID_EXCHANGEMODE].ResetGameBtn(301, 301, 299);
				}
				else
				{
					m_xOptionBtn[_BTN_ID_EXCHANGEMODE].ResetGameBtn(297, 297, -1);
				}
			}
		}
		break;
	case _CHAT_SET:
		{
			if ( m_xOptionBtn[_BTN_ID_WHISPERMODE].OnLButtonUp(ptMouse) )
			{
				g_xClientSocket.SendSay(g_xMsg.GetMsg(2126));

				if ( mOptionWnd_bWhisperMode )
				{	
					m_xOptionBtn[_BTN_ID_WHISPERMODE].ResetGameBtn(301, 301, 299);
				}
				else
				{
					m_xOptionBtn[_BTN_ID_WHISPERMODE].ResetGameBtn(297, 297, -1);
				}
			}
			else if ( m_xOptionBtn[_BTN_ID_SHOUTMODE].OnLButtonUp(ptMouse) )
			{
				g_xClientSocket.SendSay(g_xMsg.GetMsg(2129));

				if ( mOptionWnd_bShoutMode )
				{	
					m_xOptionBtn[_BTN_ID_SHOUTMODE].ResetGameBtn(301, 301, 299);
				}
				else
				{
					m_xOptionBtn[_BTN_ID_SHOUTMODE].ResetGameBtn(297, 297, -1);
				}
			}
			else if ( m_xOptionBtn[_BTN_ID_WHOLESHOUTMODE].OnLButtonUp(ptMouse) )
			{
				g_xClientSocket.SendSay(g_xMsg.GetMsg(2163));

				if ( mOptionWnd_bWholeShoutMode )
				{	
					m_xOptionBtn[_BTN_ID_WHOLESHOUTMODE].ResetGameBtn(301, 301, 299);
				}
				else
				{
					m_xOptionBtn[_BTN_ID_WHOLESHOUTMODE].ResetGameBtn(297, 297, -1);
				}
			}
			else if ( m_xOptionBtn[_BTN_ID_GUILDWHISPERMODE].OnLButtonUp(ptMouse) )
			{
				g_xClientSocket.SendSay(g_xMsg.GetMsg(2127));

				if ( mOptionWnd_bGuildwhisperMode )
				{	
					m_xOptionBtn[_BTN_ID_GUILDWHISPERMODE].ResetGameBtn(301, 301, 299);
				}
				else
				{
					m_xOptionBtn[_BTN_ID_GUILDWHISPERMODE].ResetGameBtn(297, 297, -1);
				}
			}
			else if ( m_xOptionBtn[_BTN_ID_CUTSOMEONE].OnLButtonUp(ptMouse) )
			{
				g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_CUTWHISPER, _YESNO, g_xMsg.GetMsg(2161), TRUE);
			}
		}	
		break;
	case _VISUAL_SET:
		{
			if ( m_xOptionBtn[_BTN_ID_SHOWBLOODNUM].OnLButtonUp(ptMouse) )
			{
				DWORD dwFont = GetChatColor(_CHAT_COLOR3);
				DWORD dwBack = GetChatColor(_CHAT_COLOR8);

				if ( g_xGameProc.m_bShowBloodNum )
				{
					g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2121));
					m_xOptionBtn[_BTN_ID_SHOWBLOODNUM].ResetGameBtn(301, 301, 299);
					g_xGameProc.m_bShowBloodNum = FALSE;
				}
				else
				{
					g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2122));
					m_xOptionBtn[_BTN_ID_SHOWBLOODNUM].ResetGameBtn(297, 297, -1);
					g_xGameProc.m_bShowBloodNum = TRUE;
				}
				SetIniFile();
			}
			else if ( m_xOptionBtn[_BTN_ID_MAGICLIGHT].OnLButtonUp(ptMouse) )
			{
				DWORD dwFont = GetChatColor(_CHAT_COLOR3);
				DWORD dwBack = GetChatColor(_CHAT_COLOR8);

				if ( g_xGameProc.m_bDrawMagicLight )
				{
					g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(1517));
					m_xOptionBtn[_BTN_ID_MAGICLIGHT].ResetGameBtn(301, 301, 299);
					g_xGameProc.m_bDrawMagicLight = FALSE;
				}
				else
				{
					g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(1518));
					m_xOptionBtn[_BTN_ID_MAGICLIGHT].ResetGameBtn(297, 297, -1);
					g_xGameProc.m_bDrawMagicLight = TRUE;
				}
				SetIniFile();
			}
			else if ( m_xOptionBtn[_BTN_ID_SBLENDONOFF].OnLButtonUp(ptMouse) )
			{
				if ( m_bShadowON == FALSE )
				{
					g_xGameProc.m_bShadowABlend = TRUE;

					m_xOptionBtn[_BTN_ID_SBLENDONOFF].ResetGameBtn(297, 297, -1);
					m_bShadowON	= TRUE;
					SetIniFile();
				}
				else
				{
					g_xGameProc.m_bShadowABlend = FALSE;

					m_xOptionBtn[_BTN_ID_SBLENDONOFF].ResetGameBtn(301, 301, 299);
					m_bShadowON	= FALSE;
					SetIniFile();
				}
			}
			else if ( m_xOptionBtn[_BTN_ID_SHOWHELMET].OnLButtonUp(ptMouse) )
			{
				if ( g_xGameProc.m_bShowHelmet == FALSE )
				{
					g_xGameProc.m_bShowHelmet = TRUE;
					g_xClientSocket.SendSay(g_xMsg.GetMsg(2145));
					m_xOptionBtn[_BTN_ID_SHOWHELMET].ResetGameBtn(297, 297, -1);
					SetIniFile();
				}
				else
				{
					g_xGameProc.m_bShowHelmet = FALSE;
					g_xClientSocket.SendSay(g_xMsg.GetMsg(2145));
					m_xOptionBtn[_BTN_ID_SHOWHELMET].ResetGameBtn(301, 301, 299);
					SetIniFile();
				}
			}
			else if ( m_xOptionBtn[_BTN_ID_MONEFFECT].OnLButtonUp(ptMouse) )
			{
				if ( g_xGameProc.m_bShowMonEffect == FALSE )
				{
					g_xGameProc.m_bShowMonEffect = TRUE;

					m_xOptionBtn[_BTN_ID_MONEFFECT].ResetGameBtn(297, 297, -1);
					
					SetIniFile();
				}
				else
				{
					g_xGameProc.m_bShowMonEffect = FALSE;
					m_xOptionBtn[_BTN_ID_MONEFFECT].ResetGameBtn(301, 301, 299);
					SetIniFile();
				}
			}
			else if ( m_xOptionBtn[_BTN_ID_SHOWHEALTHBAR].OnLButtonUp(ptMouse) )
			{
				if ( mOptionWnd_bShowHealthbar == FALSE )
				{
					mOptionWnd_bShowHealthbar = TRUE;

					m_xOptionBtn[_BTN_ID_SHOWHEALTHBAR].ResetGameBtn(297, 297, -1);
					
					SetIniFile();
				}
				else
				{
					mOptionWnd_bShowHealthbar = FALSE;
					m_xOptionBtn[_BTN_ID_SHOWHEALTHBAR].ResetGameBtn(301, 301, 299);
					SetIniFile();
				}
			}
			else if ( m_xOptionBtn[_BTN_ID_SHOWDEYING].OnLButtonUp(ptMouse) )
			{
				if ( g_xGameProc.m_bShowDeying == FALSE )
				{
					g_xGameProc.m_bShowDeying = TRUE;
					m_xOptionBtn[_BTN_ID_SHOWDEYING].ResetGameBtn(297, 297, -1);
					SetIniFile();
				}
				else
				{
					g_xGameProc.m_bShowDeying = FALSE;
					m_xOptionBtn[_BTN_ID_SHOWDEYING].ResetGameBtn(301, 301, 299);
					SetIniFile();
				}
			}
			else if ( m_xOptionBtn[_BTN_ID_DRAWUSERPIC].OnLButtonUp(ptMouse) )
			{
				DWORD dwFont = GetChatColor(_CHAT_COLOR3);
				DWORD dwBack = GetChatColor(_CHAT_COLOR8);

				if ( g_xGameProc.m_xInterface.m_bShowUserPic )
				{
					g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2131));
					m_xOptionBtn[_BTN_ID_DRAWUSERPIC].ResetGameBtn(301, 301, 299);
					g_xGameProc.m_xInterface.m_bShowUserPic = FALSE;
				}
				else
				{
					g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2132));
					m_xOptionBtn[_BTN_ID_DRAWUSERPIC].ResetGameBtn(297, 297, -1);
					g_xGameProc.m_xInterface.m_bShowUserPic = TRUE;
				}
				SetIniFile();
			}
			else if ( m_xOptionBtn[_BTN_ID_SHOWMONINMAP].OnLButtonUp(ptMouse) )
			{
				DWORD dwFont = GetChatColor(_CHAT_COLOR3);
				DWORD dwBack = GetChatColor(_CHAT_COLOR8);

				if ( g_xGameProc.m_xInterface.m_xMiniMap.m_bShowMonInfo )
				{
					g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2647));
					m_xOptionBtn[_BTN_ID_SHOWMONINMAP].ResetGameBtn(301, 301, 299);
					g_xGameProc.m_xInterface.m_xMiniMap.m_bShowMonInfo = FALSE;
				}
				else
				{
					g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2646));
					m_xOptionBtn[_BTN_ID_SHOWMONINMAP].ResetGameBtn(297, 297, -1);
					g_xGameProc.m_xInterface.m_xMiniMap.m_bShowMonInfo = TRUE;
				}
				SetIniFile();
			}
			else if ( m_xOptionBtn[_BTN_ID_SHOWHEALTHNUM].OnLButtonUp(ptMouse) )
			{
				DWORD dwFont = GetChatColor(_CHAT_COLOR3);
				DWORD dwBack = GetChatColor(_CHAT_COLOR8);

				if ( g_xGameProc.m_bDrawHealthNum )
				{
					g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2137));
					m_xOptionBtn[_BTN_ID_SHOWHEALTHNUM].ResetGameBtn(301, 301, 299);
					g_xGameProc.m_bDrawHealthNum = FALSE;
				}
				else
				{
					g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2138));
					m_xOptionBtn[_BTN_ID_SHOWHEALTHNUM].ResetGameBtn(297, 297, -1);
					g_xGameProc.m_bDrawHealthNum = TRUE;
				}
				SetIniFile();
			}
		}
		break;
	}
/*
	for ( nCnt = 1; nCnt < _MAX_OPTION_BTN; nCnt++ )
	{
		if ( m_xOptionBtn[nCnt].OnLButtonUp(ptMouse) )
		{
			switch( nCnt )
			{
				case _BTN_ID_SHOWMONINMAP:
				{
					DWORD dwFont = GetChatColor(_CHAT_COLOR3);
					DWORD dwBack = GetChatColor(_CHAT_COLOR8);

					if ( g_xGameProc.m_xInterface.m_xMiniMap.m_bShowMonInfo )
					{
						g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2647));
						m_xOptionBtn[_BTN_ID_SHOWMONINMAP].ResetGameBtn(301, 301, 299);
						g_xGameProc.m_xInterface.m_xMiniMap.m_bShowMonInfo = FALSE;
					}
					else
					{
						g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2646));
						m_xOptionBtn[_BTN_ID_SHOWMONINMAP].ResetGameBtn(297, 297, -1);
						g_xGameProc.m_xInterface.m_xMiniMap.m_bShowMonInfo = TRUE;
					}
					SetIniFile();
				}
				break;
				case _BTN_ID_ATTACKUSER:
				{
					DWORD dwFont = GetChatColor(_CHAT_COLOR3);
					DWORD dwBack = GetChatColor(_CHAT_COLOR8);

					if ( g_xGameProc.m_bAttackUser )
					{
						g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(1516));
						m_xOptionBtn[_BTN_ID_ATTACKUSER].ResetGameBtn(301, 301, 299);
						g_xGameProc.m_bAttackUser = FALSE;
					}
					else
					{
						g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(1515));
						m_xOptionBtn[_BTN_ID_ATTACKUSER].ResetGameBtn(297, 297, -1);
						g_xGameProc.m_bAttackUser = TRUE;
					}
					SetIniFile();
				}
				break;
				case _BTN_ID_MAGICLIGHT:
				{
					DWORD dwFont = GetChatColor(_CHAT_COLOR3);
					DWORD dwBack = GetChatColor(_CHAT_COLOR8);

					if ( g_xGameProc.m_bDrawMagicLight )
					{
						g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(1517));
						m_xOptionBtn[_BTN_ID_MAGICLIGHT].ResetGameBtn(301, 301, 299);
						g_xGameProc.m_bDrawMagicLight = FALSE;
					}
					else
					{
						g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(1518));
						m_xOptionBtn[_BTN_ID_MAGICLIGHT].ResetGameBtn(297, 297, -1);
						g_xGameProc.m_bDrawMagicLight = TRUE;
					}
					SetIniFile();
				}
				break;
				case _BTN_ID_SHOWBLOODNUM:
				{
					DWORD dwFont = GetChatColor(_CHAT_COLOR3);
					DWORD dwBack = GetChatColor(_CHAT_COLOR8);

					if ( g_xGameProc.m_bShowBloodNum )
					{
						g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2121));
						m_xOptionBtn[_BTN_ID_SHOWBLOODNUM].ResetGameBtn(301, 301, 299);
						g_xGameProc.m_bShowBloodNum = FALSE;
					}
					else
					{
						g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2122));
						m_xOptionBtn[_BTN_ID_SHOWBLOODNUM].ResetGameBtn(297, 297, -1);
						g_xGameProc.m_bShowBloodNum = TRUE;
					}
					SetIniFile();
				}
				break;
				case _BTN_ID_DRAWUSERPIC:
				{
					DWORD dwFont = GetChatColor(_CHAT_COLOR3);
					DWORD dwBack = GetChatColor(_CHAT_COLOR8);

					if ( g_xGameProc.m_xInterface.m_bShowUserPic )
					{
						g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2131));
						m_xOptionBtn[_BTN_ID_DRAWUSERPIC].ResetGameBtn(301, 301, 299);
						g_xGameProc.m_xInterface.m_bShowUserPic = FALSE;
					}
					else
					{
						g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2132));
						m_xOptionBtn[_BTN_ID_DRAWUSERPIC].ResetGameBtn(297, 297, -1);
						g_xGameProc.m_xInterface.m_bShowUserPic = TRUE;
					}
					SetIniFile();
				}
				break;
				case _BTN_ID_ALLOWGROUP:
				{
					DWORD dwFont = GetChatColor(_CHAT_COLOR3);
					DWORD dwBack = GetChatColor(_CHAT_COLOR8);

					mOptionWnd_bAllowGroup ? mOptionWnd_bAllowGroup = FALSE : mOptionWnd_bAllowGroup = TRUE;
					g_xClientSocket.SendGroupMode(mOptionWnd_bAllowGroup);

					if ( mOptionWnd_bAllowGroup )
					{
						g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2147));
						m_xOptionBtn[_BTN_ID_ALLOWGROUP].ResetGameBtn(297, 297, -1);
					}
					else
					{
						g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2148));
						m_xOptionBtn[_BTN_ID_ALLOWGROUP].ResetGameBtn(301, 301, 299);
					}
				}
				break;
				case _BTN_ID_REVIVAL:
				{
					g_xClientSocket.SendSay(g_xMsg.GetMsg(2123));

					if ( mOptionWnd_bRevival )
					{
						m_xOptionBtn[_BTN_ID_REVIVAL].ResetGameBtn(297, 297, -1);
					}
					else
					{
						m_xOptionBtn[_BTN_ID_REVIVAL].ResetGameBtn(301, 301, 299);
					}
				}
				break;
				case _BTN_ID_CHUNJIHAPIL:
				{
					g_xClientSocket.SendSay(g_xMsg.GetMsg(2124));

					if ( mOptionWnd_bChunjihapil )
					{	
						m_xOptionBtn[_BTN_ID_CHUNJIHAPIL].ResetGameBtn(301, 301, 299);
					}
					else
					{
						m_xOptionBtn[_BTN_ID_CHUNJIHAPIL].ResetGameBtn(297, 297, -1);
					}
				}
				break;
				case _BTN_ID_EXCHANGEMODE:
				{
					g_xClientSocket.SendSay(g_xMsg.GetMsg(2125));

					if ( mOptionWnd_bExchangeMode )
					{	
						m_xOptionBtn[_BTN_ID_EXCHANGEMODE].ResetGameBtn(301, 301, 299);
					}
					else
					{
						m_xOptionBtn[_BTN_ID_EXCHANGEMODE].ResetGameBtn(297, 297, -1);
					}
				}
				break;
				case _BTN_ID_WHISPERMODE:
				{
					g_xClientSocket.SendSay(g_xMsg.GetMsg(2126));

					if ( mOptionWnd_bWhisperMode )
					{	
						m_xOptionBtn[_BTN_ID_WHISPERMODE].ResetGameBtn(301, 301, 299);
					}
					else
					{
						m_xOptionBtn[_BTN_ID_WHISPERMODE].ResetGameBtn(297, 297, -1);
					}
				}
				break;
				case _BTN_ID_GUILDWHISPERMODE:
				{
					g_xClientSocket.SendSay(g_xMsg.GetMsg(2127));

					if ( mOptionWnd_bGuildwhisperMode )
					{	
						m_xOptionBtn[_BTN_ID_GUILDWHISPERMODE].ResetGameBtn(301, 301, 299);
					}
					else
					{
						m_xOptionBtn[_BTN_ID_GUILDWHISPERMODE].ResetGameBtn(297, 297, -1);
					}
				}
				break;
				case _BTN_ID_GUILDJOINMODE:
				{
					g_xClientSocket.SendSay(g_xMsg.GetMsg(2128));

					if ( mOptionWnd_bGuildJoinMode )
					{	
						m_xOptionBtn[_BTN_ID_GUILDJOINMODE].ResetGameBtn(297, 297, -1);
					}
					else
					{
						m_xOptionBtn[_BTN_ID_GUILDJOINMODE].ResetGameBtn(301, 301, 299);
					}
				}
				break;
				case _BTN_ID_SHOUTMODE:
				{
					g_xClientSocket.SendSay(g_xMsg.GetMsg(2129));

					if ( mOptionWnd_bShoutMode )
					{	
						m_xOptionBtn[_BTN_ID_SHOUTMODE].ResetGameBtn(301, 301, 299);
					}
					else
					{
						m_xOptionBtn[_BTN_ID_SHOUTMODE].ResetGameBtn(297, 297, -1);
					}
				}
				break;
				case _BTN_ID_ATTACKMODE:
				{
					g_xClientSocket.SendSay(g_xMsg.GetMsg(1422));
				}
				break;
				case _BTN_ID_BGMONOFF:
				{
					DWORD dwFont = GetChatColor(_CHAT_COLOR3);
					DWORD dwBack = GetChatColor(_CHAT_COLOR8);

					if ( m_bBGMON == FALSE )
					{
						g_SoundManager.SndmngrSetEnableBGM();
						g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, "[배경음 On]");
						g_SoundManager.SndmngrPlayMp3(g_xGameProc.m_xMap.m_pszMapName, TRUE, 0);
						m_xOptionBtn[_BTN_ID_BGMONOFF].ResetGameBtn(297, 297, -1);
						m_bBGMON	= TRUE;
						SetIniFile();
					}
					else
					{
						g_SoundManager.SndmngrStopMp3();
						g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, "[배경음 Off]");
						g_SoundManager.mSndMngr_bMP3Play = FALSE;
						m_xOptionBtn[_BTN_ID_BGMONOFF].ResetGameBtn(301, 301, 299);
						m_bBGMON	= FALSE;
						SetIniFile();
					}
					break;
				}
				case _BTN_ID_SOUNDONOFF:
				{
					DWORD dwFont = GetChatColor(_CHAT_COLOR3);
					DWORD dwBack = GetChatColor(_CHAT_COLOR8);

					if ( m_bEffectON == FALSE )
					{
						g_SoundManager.SndmngrSetEnableWavePlay();

						g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, "[효과음 On]");
						m_xOptionBtn[_BTN_ID_SOUNDONOFF].ResetGameBtn(297, 297, -1);
						m_bEffectON	= TRUE;
						SetIniFile();
					}
					else
					{
						g_SoundManager.SndmngrStopAllWaveSound();
						g_SoundManager.SndmngrSetDisableWavePlay();

						g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, "[효과음 Off]");
						m_xOptionBtn[_BTN_ID_SOUNDONOFF].ResetGameBtn(301, 301, 299);
						m_bEffectON	= FALSE;
						SetIniFile();
					}
					break;
				}
				case _NEW_BTN_ID_ANTIPANONOFF:
				{
					DWORD dwFont = GetChatColor(_CHAT_COLOR3);
					DWORD dwBack = GetChatColor(_CHAT_COLOR8);

					if ( g_SoundManager.mSndMngr_bRevereLR == FALSE )
					{
						g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, "[사운드 좌우 반전 On]");
						m_xOptionBtn[_NEW_BTN_ID_ANTIPANONOFF].ResetGameBtn(297, 297, -1);
						m_bReversePanON = TRUE;
						g_SoundManager.mSndMngr_bRevereLR = TRUE;
						SetIniFile();
					}
					else
					{
						g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, "[사운드 좌우 반전 Off]");
						m_xOptionBtn[_NEW_BTN_ID_ANTIPANONOFF].ResetGameBtn(301, 301, 299);
						m_bReversePanON = FALSE;
						g_SoundManager.mSndMngr_bRevereLR = FALSE;
						SetIniFile();
					}
				}
				break;
				case _BTN_ID_SBLENDONOFF:
				{
					if ( m_bShadowON == FALSE )
					{
						g_xGameProc.m_bShadowABlend = TRUE;

						m_xOptionBtn[_BTN_ID_SBLENDONOFF].ResetGameBtn(297, 297, -1);
						m_bShadowON	= TRUE;
						SetIniFile();
					}
					else
					{
						g_xGameProc.m_bShadowABlend = FALSE;

						m_xOptionBtn[_BTN_ID_SBLENDONOFF].ResetGameBtn(301, 301, 299);
						m_bShadowON	= FALSE;
						SetIniFile();
					}
					break;
				}
				case _BTN_ID_MONEFFECT:
				{
					if ( g_xGameProc.m_bShowMonEffect == FALSE )
					{
						g_xGameProc.m_bShowMonEffect = TRUE;

						m_xOptionBtn[_BTN_ID_MONEFFECT].ResetGameBtn(297, 297, -1);
						
						SetIniFile();
					}
					else
					{
						g_xGameProc.m_bShowMonEffect = FALSE;
						m_xOptionBtn[_BTN_ID_MONEFFECT].ResetGameBtn(301, 301, 299);
						SetIniFile();
					}
					break;
				}
				case _BTN_ID_SHOWDEYING:
				{
					if ( g_xGameProc.m_bShowDeying == FALSE )
					{
						g_xGameProc.m_bShowDeying = TRUE;
						m_xOptionBtn[_BTN_ID_SHOWDEYING].ResetGameBtn(297, 297, -1);
						SetIniFile();
					}
					else
					{
						g_xGameProc.m_bShowDeying = FALSE;
						m_xOptionBtn[_BTN_ID_SHOWDEYING].ResetGameBtn(301, 301, 299);
						SetIniFile();
					}
					break;
				}
				case _BTN_ID_SHOWHELMET:
				{
					if ( g_xGameProc.m_bShowHelmet == FALSE )
					{
						g_xGameProc.m_bShowHelmet = TRUE;

						m_xOptionBtn[_BTN_ID_SHOWHELMET].ResetGameBtn(297, 297, -1);
						SetIniFile();
					}
					else
					{
						g_xGameProc.m_bShowHelmet = FALSE;
						m_xOptionBtn[_BTN_ID_SHOWHELMET].ResetGameBtn(301, 301, 299);
						SetIniFile();
					}
					break;
				}
//				case _BTN_ID_AUTOPICKUP:
//				{
//					DWORD dwFont = GetChatColor(_CHAT_COLOR3);
//					DWORD dwBack = GetChatColor(_CHAT_COLOR8);

//					if ( g_xGameProc.m_bAutoPickup )
//					{
//						g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2133));
//						m_xOptionBtn[_BTN_ID_AUTOPICKUP].ResetGameBtn(301, 301, 299);
//						g_xGameProc.m_bAutoPickup = FALSE;
//					}
//					else
//					{
//						g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2134));
//						m_xOptionBtn[_BTN_ID_AUTOPICKUP].ResetGameBtn(297, 297, -1);
//						g_xGameProc.m_bAutoPickup = TRUE;
//					}
//					SetIniFile();
//				}
//				break;
//				case _BTN_ID_SHOWDROPITEM:
//				{
//					DWORD dwFont = GetChatColor(_CHAT_COLOR3);
//					DWORD dwBack = GetChatColor(_CHAT_COLOR8);
//
//					if ( g_xGameProc.m_bDrawGroundItemName )
//					{
//						g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2135));
//						m_xOptionBtn[_BTN_ID_SHOWDROPITEM].ResetGameBtn(301, 301, 299);
//						g_xGameProc.m_bDrawGroundItemName = FALSE;
//					}
//					else
//					{
//						g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2136));
//						m_xOptionBtn[_BTN_ID_SHOWDROPITEM].ResetGameBtn(297, 297, -1);
//						g_xGameProc.m_bDrawGroundItemName = TRUE;
//					}
//					SetIniFile();
//				}
//				break;
//				case _BTN_ID_SHOWHEALTHNUM:
//				{
//					DWORD dwFont = GetChatColor(_CHAT_COLOR3);
//					DWORD dwBack = GetChatColor(_CHAT_COLOR8);
//
//					if ( g_xGameProc.m_bDrawHealthNum )
//					{
//						g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2137));
//						m_xOptionBtn[_BTN_ID_SHOWHEALTHNUM].ResetGameBtn(301, 301, 299);
//						g_xGameProc.m_bDrawHealthNum = FALSE;
//					}
//					else
//					{
//						g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2138));
//						m_xOptionBtn[_BTN_ID_SHOWHEALTHNUM].ResetGameBtn(297, 297, -1);
//						g_xGameProc.m_bDrawHealthNum = TRUE;
//					}
//					SetIniFile();
//				}
//				break;

			}
			return FALSE;

		}			
	}
*/
	return FALSE;
}

BOOL COptionWnd::OnLButtonDown(POINT ptMouse)
{
	INT nCnt;

	if ( PtInRect(&mOptionWnd_rcBasicTab, ptMouse) )
	{
		mOptionWnd_nMode = _BASIC_SET;
		return TRUE;
	}

	if ( PtInRect(&mOptionWnd_rcAllowTab, ptMouse) )
	{
		mOptionWnd_nMode = _ALLOW_SET;
		return TRUE;
	}

	if ( PtInRect(&mOptionWnd_rcChatTab, ptMouse) )
	{
		mOptionWnd_nMode = _CHAT_SET;
		return TRUE;
	}

	if ( PtInRect(&mOptionWnd_rcVisualTab, ptMouse) )
	{
		mOptionWnd_nMode = _VISUAL_SET;
		return TRUE;
	}
	
	if ( m_xOptionBtn[_BTN_ID_OPTIONCLOSE].OnLButtonDown(ptMouse) )
	{
		return TRUE;
	}

	if (m_xOptionBtn[_BTN_ID_BGMVOLUME].OnLButtonDown(ptMouse) == TRUE)
	{
		g_SoundManager.SndmngrPlayWavSound(_SOUND_GLASS_BUTTON, 0, 0);
		mOptionWnd_bMoveBgmVolBtn = TRUE;
		return TRUE;
	}
	
	if (m_xOptionBtn[_BTN_ID_WAVEVOLUME].OnLButtonDown(ptMouse) == TRUE)
	{
		g_SoundManager.SndmngrPlayWavSound(_SOUND_GLASS_BUTTON, 0, 0);
		mOptionWnd_bMoveWaveVolBtn = TRUE;
		return TRUE;
	}

	switch(mOptionWnd_nMode)
	{
	case _BASIC_SET:
		if ( m_xOptionBtn[_BTN_ID_ATTACKMODE].OnLButtonDown(ptMouse) )
			return TRUE;
		if ( m_xOptionBtn[_BTN_ID_ATTACKUSER].OnLButtonDown(ptMouse) )
			return TRUE;
		if ( m_xOptionBtn[_BTN_ID_BGMVOLUME].OnLButtonDown(ptMouse) )
			return TRUE;
		if ( m_xOptionBtn[_BTN_ID_WAVEVOLUME].OnLButtonDown(ptMouse) )
			return TRUE;
		if ( m_xOptionBtn[_NEW_BTN_ID_ANTIPANONOFF].OnLButtonDown(ptMouse) )
			return TRUE;
		if ( m_xOptionBtn[_BTN_ID_CHANGEWEATHER].OnLButtonDown(ptMouse) )
			return TRUE;
		break;
	case _ALLOW_SET:
		if ( m_xOptionBtn[_BTN_ID_ALLOWGROUP].OnLButtonDown(ptMouse) )
			return TRUE;
		if ( m_xOptionBtn[_BTN_ID_GUILDJOINMODE].OnLButtonDown(ptMouse) )
			return TRUE;
		if ( m_xOptionBtn[_BTN_ID_REVIVAL].OnLButtonDown(ptMouse) )
			return TRUE;
		if ( m_xOptionBtn[_BTN_ID_CHUNJIHAPIL].OnLButtonDown(ptMouse) )
			return TRUE;
		if ( m_xOptionBtn[_BTN_ID_EXCHANGEMODE].OnLButtonDown(ptMouse) )
			return TRUE;
		break;
	case _CHAT_SET:
		if ( m_xOptionBtn[_BTN_ID_WHISPERMODE].OnLButtonDown(ptMouse) )
			return TRUE;
		if ( m_xOptionBtn[_BTN_ID_SHOUTMODE].OnLButtonDown(ptMouse) )
			return TRUE;
		if ( m_xOptionBtn[_BTN_ID_GUILDWHISPERMODE].OnLButtonDown(ptMouse) )
			return TRUE;
		if ( m_xOptionBtn[_BTN_ID_WHOLESHOUTMODE].OnLButtonDown(ptMouse) )
			return TRUE;
		break;
	case _VISUAL_SET:
		if ( m_xOptionBtn[_BTN_ID_SHOWBLOODNUM].OnLButtonDown(ptMouse) )
			return TRUE;
		if ( m_xOptionBtn[_BTN_ID_MAGICLIGHT].OnLButtonDown(ptMouse) )
			return TRUE;
		if ( m_xOptionBtn[_BTN_ID_SBLENDONOFF].OnLButtonDown(ptMouse) )
			return TRUE;
		if ( m_xOptionBtn[_BTN_ID_SHOWHELMET].OnLButtonDown(ptMouse) )
			return TRUE;
		if ( m_xOptionBtn[_BTN_ID_MONEFFECT].OnLButtonDown(ptMouse) )
			return TRUE;
		if ( m_xOptionBtn[_BTN_ID_SHOWDEYING].OnLButtonDown(ptMouse) )
			return TRUE;
		if ( m_xOptionBtn[_BTN_ID_DRAWUSERPIC].OnLButtonDown(ptMouse) )
			return TRUE;
		if ( m_xOptionBtn[_BTN_ID_SHOWMONINMAP].OnLButtonDown(ptMouse) )
			return TRUE;
		if ( m_xOptionBtn[_BTN_ID_SHOWHEALTHBAR].OnLButtonDown(ptMouse) )
			return TRUE;
		break;
	}

	return FALSE;
}

VOID COptionWnd::OnMouseMove(POINT ptMouse)
{
	INT		nCnt;
	FLOAT	fVol;

	if (mOptionWnd_bMoveBgmVolBtn == TRUE)
	{
		mOptionWnd_ptBgmVolBtn = g_xGameProc.m_ptMousePos;

		mOptionWnd_ptBgmVolBtn.x = mOptionWnd_ptBgmVolBtn.x - (m_rcWnd.left+18) - 12;
		
		if (mOptionWnd_ptBgmVolBtn.x < 0)
			mOptionWnd_ptBgmVolBtn.x = 0;
		else if (mOptionWnd_ptBgmVolBtn.x > 174)
			mOptionWnd_ptBgmVolBtn.x = 174;
		
		OptionWndSetVolume(_SET_BGMVOL);
		return;
	}

	if (mOptionWnd_bMoveWaveVolBtn == TRUE)
	{
		mOptionWnd_ptWaveVolBtn = g_xGameProc.m_ptMousePos;

		mOptionWnd_ptWaveVolBtn.x = mOptionWnd_ptWaveVolBtn.x - (m_rcWnd.left+18) - 12;

		if (mOptionWnd_ptWaveVolBtn.x < 0)
			mOptionWnd_ptWaveVolBtn.x = 0;
		else if (mOptionWnd_ptWaveVolBtn.x > 174)
			mOptionWnd_ptWaveVolBtn.x = 174;

		OptionWndSetVolume(_SET_WAVEVOL);
		return;
	}

	for ( nCnt = 0; nCnt < _MAX_OPTION_BTN; nCnt++ )
	{
		m_xOptionBtn[nCnt].OnMouseMove(ptMouse);
	}
}

VOID COptionWnd::SetStatusBtnInit()
{
	INT nCnt;

	mOptionWnd_bMoveBgmVolBtn = FALSE;
	mOptionWnd_bMoveWaveVolBtn = FALSE;

	for ( nCnt = 0; nCnt < _MAX_OPTION_BTN; nCnt++ )
	{
		m_xOptionBtn[nCnt].SetBtnState(_BTN_STATE_NORMAL);
	}
}

VOID COptionWnd::SetIniFile()
{
	CHAR	szVal[MAX_PATH];
	CHAR	szFileName[MAX_PATH];
	BOOL	bResult;

	CHAR*	pStr;

	if ( GetCurrentDirectory(MAX_PATH, szFileName))
	{
		if ( szFileName[0] == '\0' )
			return;

		strcat(szFileName, "\\Config.ini");

		_itoa(m_bEffectON,szVal,10);
		bResult = WritePrivateProfileString(SECTION_OPTIONS, KEY_EFFECTSOUND, szVal, szFileName);		// Effect Sound On or Off

		_itoa(g_SoundManager.mSndMngr_lWavMaxVol ,szVal,10);
		bResult = WritePrivateProfileString(SECTION_OPTIONS, KEY_EFFECTSOUNDLEVEL, szVal, szFileName);	// Effect Sound Volume Level

		_itoa(m_bBGMON,szVal,10);
		bResult = WritePrivateProfileString(SECTION_OPTIONS, KEY_BGM, szVal, szFileName);				// Back Ground Music On or Off

		_itoa(g_SoundManager.mSndMngr_lMp3MaxVol,szVal,10);
		bResult = WritePrivateProfileString(SECTION_OPTIONS, KEY_BGMLEVEL, szVal, szFileName);			// Back Ground Music Volume Level

		_itoa(m_bEnvirON,szVal,10);
		bResult = WritePrivateProfileString(SECTION_OPTIONS,KEY_AMBIENCE, szVal, szFileName);			// Ambience On or Off

		_itoa(m_bShadowON,szVal,10);
		bResult = WritePrivateProfileString(SECTION_OPTIONS,KEY_SHADOWBLEND, szVal, szFileName);		// Shadow Blending On or Off

		_itoa(m_bReversePanON,szVal,10);
		bResult = WritePrivateProfileString(SECTION_OPTIONS, KEY_REVERSEPAN, szVal, szFileName);		// Reverse panning On or Off

		_itoa(g_xGameProc.m_xInterface.m_bAcShow,szVal,10);
		bResult = WritePrivateProfileString(SECTION_OPTIONS, KEY_ACSHOW, szVal, szFileName);		// AcShow

		_itoa(g_xGameProc.m_xInterface.m_bDcScMcShow,szVal,10);
		bResult = WritePrivateProfileString(SECTION_OPTIONS, KEY_DCSHOW, szVal, szFileName);		// DcShow

		_itoa(g_xGameProc.m_xInterface.m_xMiniMap.m_bShowMonInfo,szVal,10);
		bResult = WritePrivateProfileString(SECTION_OPTIONS, KEY_SHOWMON, szVal, szFileName);		// Show Mon In Minimap

		_itoa(g_xGameProc.m_bAttackUser,szVal,10);
		bResult = WritePrivateProfileString(SECTION_OPTIONS, KEY_ATTACKUSER, szVal, szFileName);		// Attack User Mode

		_itoa(g_xGameProc.m_bDrawMagicLight,szVal,10);
		bResult = WritePrivateProfileString(SECTION_OPTIONS, KEY_MAGICLIGHT, szVal, szFileName);		// Magig Light Mode

		_itoa(g_xGameProc.m_bShowBloodNum,szVal,10);
		bResult = WritePrivateProfileString(SECTION_OPTIONS, KEY_SHOWBLOOD, szVal, szFileName);		// Magig Light Mode

		_itoa(g_xGameProc.m_xInterface.m_bShowUserPic,szVal,10);
		bResult = WritePrivateProfileString(SECTION_OPTIONS, KEY_SHOWUSERPIC, szVal, szFileName);		// Magig Light Mode

		_itoa(g_xGameProc.m_bShowMonEffect,szVal,10);
		bResult = WritePrivateProfileString(SECTION_OPTIONS, KEY_SHOWMONEFFECT, szVal, szFileName);		// Magig Light Mode

		_itoa(g_xGameProc.m_bShowDeying,szVal,10);
		bResult = WritePrivateProfileString(SECTION_OPTIONS, KEY_SHOWDEYING, szVal, szFileName);		// Magig Light Mode

		_itoa(g_xGameProc.m_bShowHelmet,szVal,10);
		bResult = WritePrivateProfileString(SECTION_OPTIONS, KEY_SHOWHELMET, szVal, szFileName);		// Magig Light Mode

		_itoa(mOptionWnd_bShowHealthbar,szVal,10);
		bResult = WritePrivateProfileString(SECTION_OPTIONS, KEY_SHOWHEALTHBAR, szVal, szFileName);		// Magig Light Mode

		_itoa(g_xGameProc.m_bAutoPickup,szVal,10);
		bResult = WritePrivateProfileString(SECTION_OPTIONS, KEY_AUTOPICKUP, szVal, szFileName);

		_itoa(g_xGameProc.m_bDrawGroundItemName,szVal,10);
		bResult = WritePrivateProfileString(SECTION_OPTIONS, KEY_SHOWDROPITEM, szVal, szFileName);

		_itoa(g_xGameProc.m_bDrawHealthNum,szVal,10);
		bResult = WritePrivateProfileString(SECTION_OPTIONS, KEY_SHOWHEALTHNUM, szVal, szFileName);
	}
}

VOID COptionWnd::SetOptions()
{
	CHAR	szFileName[MAX_PATH];
	CHAR	szTemp[MAX_PATH];
	CHAR*	pStr;

	ZeroMemory(szFileName, MAX_PATH);
	ZeroMemory(szTemp, MAX_PATH);

	if ( GetCurrentDirectory(MAX_PATH, szFileName) )
	{
		if ( szFileName[0] == '\0' )
		{
			return;
		}

		strcat(szFileName, "\\Config.ini");

		//------------------------------------------------------------------------------------------------------------
		// Effect Sound On/Off.
		GetPrivateProfileString(SECTION_OPTIONS, KEY_EFFECTSOUND, "1", szTemp, MAX_PATH, szFileName);
		if ( szTemp == NULL )
		{
			return;
		}
		m_bEffectON = atoi(szTemp);
		if(m_bEffectON)
		{
			g_SoundManager.SndmngrSetEnableWavePlay();
		}
		else
		{
			g_SoundManager.SndmngrStopAllWaveSound();
			g_SoundManager.SndmngrSetDisableWavePlay();
		}
		//------------------------------------------------------------------------------------------------------------

		//------------------------------------------------------------------------------------------------------------
		// Effect Sound Volume Level.
		GetPrivateProfileString(SECTION_OPTIONS, KEY_EFFECTSOUNDLEVEL, "0", szTemp, MAX_PATH, szFileName);
		if ( szTemp == NULL )
		{
			return;
		}
		g_SoundManager.mSndMngr_lWavMaxVol = atoi(szTemp);
		//------------------------------------------------------------------------------------------------------------

		//------------------------------------------------------------------------------------------------------------
		// Back Ground Music On/Off
		GetPrivateProfileString(SECTION_OPTIONS, KEY_BGM, "1", szTemp, MAX_PATH, szFileName);
		if ( szTemp == NULL )
		{
			return;
		}
		m_bBGMON = atoi(szTemp);
		if(m_bBGMON)
		{
			g_SoundManager.SndmngrSetEnableBGM();
		}
		else
		{
			g_SoundManager.SndmngrStopMp3();
			g_SoundManager.SndmngrSetDisableBGM();
		}

		//------------------------------------------------------------------------------------------------------------
		// Show Mon In Minimap
		GetPrivateProfileString(SECTION_OPTIONS, KEY_SHOWMON, "1", szTemp, MAX_PATH, szFileName);
		if ( szTemp == NULL )
		{
			return;
		}
		g_xGameProc.m_xInterface.m_xMiniMap.m_bShowMonInfo = atoi(szTemp);

		//------------------------------------------------------------------------------------------------------------
		// Attack user Mode
		GetPrivateProfileString(SECTION_OPTIONS, KEY_ATTACKUSER, "1", szTemp, MAX_PATH, szFileName);
		if ( szTemp == NULL )
		{
			return;
		}
		g_xGameProc.m_bAttackUser = atoi(szTemp);

		//------------------------------------------------------------------------------------------------------------
		// Magic Light Mode
		GetPrivateProfileString(SECTION_OPTIONS, KEY_MAGICLIGHT, "1", szTemp, MAX_PATH, szFileName);
		if ( szTemp == NULL )
		{
			return;
		}
		g_xGameProc.m_bDrawMagicLight = atoi(szTemp);


		//------------------------------------------------------------------------------------------------------------
		// Show Blood Num
		GetPrivateProfileString(SECTION_OPTIONS, KEY_SHOWBLOOD, "1", szTemp, MAX_PATH, szFileName);
		if ( szTemp == NULL )
		{
			return;
		}
		g_xGameProc.m_bShowBloodNum = atoi(szTemp);

		//------------------------------------------------------------------------------------------------------------
		// Back Ground Music Volume Level
		GetPrivateProfileString(SECTION_OPTIONS, KEY_BGMLEVEL, "0", szTemp, MAX_PATH, szFileName);
		if ( szTemp == NULL )
		{
			return;
		}
		
		g_SoundManager.mSndMngr_lMp3MaxVol = atoi(szTemp);

		if (g_SoundManager.mSndMngr_lMp3MaxVol > 0 || g_SoundManager.mSndMngr_lMp3MaxVol < -100)
			g_SoundManager.mSndMngr_lMp3MaxVol = 0;

		if (g_SoundManager.mSndMngr_lWavMaxVol > 0 || g_SoundManager.mSndMngr_lWavMaxVol < -100)
			g_SoundManager.mSndMngr_lWavMaxVol = 0;

		mOptionWnd_ptWaveVolBtn.x = (float)(g_SoundManager.mSndMngr_lWavMaxVol + 100) * 1.8;
		mOptionWnd_ptBgmVolBtn.x = (float)(g_SoundManager.mSndMngr_lMp3MaxVol + 100) * 1.8;

		//------------------------------------------------------------------------------------------------------------

		//------------------------------------------------------------------------------------------------------------
		// Ambience On/Off
		GetPrivateProfileString(SECTION_OPTIONS, KEY_AMBIENCE, "0", szTemp, MAX_PATH, szFileName);
		if ( szTemp == NULL )
		{
			return;
		}
		m_bEnvirON = atoi(szTemp);
		//------------------------------------------------------------------------------------------------------------
		
		//------------------------------------------------------------------------------------------------------------
		// Shadow Blending On/Off
		GetPrivateProfileString(SECTION_OPTIONS, KEY_SHADOWBLEND, "0", szTemp, MAX_PATH, szFileName);
		if ( szTemp == NULL )
		{
			return;
		}
		m_bShadowON = atoi(szTemp);
		g_xGameProc.m_bShadowABlend = m_bShadowON;
		//------------------------------------------------------------------------------------------------------------

		// Reverse Panning On/Off
		GetPrivateProfileString(SECTION_OPTIONS, KEY_REVERSEPAN, "0", szTemp, MAX_PATH, szFileName);
		if ( szTemp == NULL )
		{
			return;
		}
		m_bReversePanON = atoi(szTemp);
		g_SoundManager.mSndMngr_bRevereLR = m_bReversePanON;
		//------------------------------------------------------------------------------------------------------------

		// Reverse AC Show On/Off
		GetPrivateProfileString(SECTION_OPTIONS, KEY_ACSHOW, "1", szTemp, MAX_PATH, szFileName);
		if ( szTemp == NULL )
		{
			return;
		}
		g_xGameProc.m_xInterface.m_bAcShow = atoi(szTemp);
		//------------------------------------------------------------------------------------------------------------

		// Reverse DC Show On/Off
		GetPrivateProfileString(SECTION_OPTIONS, KEY_DCSHOW, "1", szTemp, MAX_PATH, szFileName);
		if ( szTemp == NULL )
		{
			return;
		}
		g_xGameProc.m_xInterface.m_bDcScMcShow = atoi(szTemp);
		//------------------------------------------------------------------------------------------------------------

		// Reverse Draw Name On/Off
		GetPrivateProfileString(SECTION_OPTIONS, KEY_DRAWNAME, "0", szTemp, MAX_PATH, szFileName);
		if ( szTemp == NULL )
		{
			return;
		}
		g_xGameProc.m_bDrawName = atoi(szTemp);
		//------------------------------------------------------------------------------------------------------------

		// Reverse InformationMode On/Off
		GetPrivateProfileString(SECTION_OPTIONS, KEY_INFORMATIONMODE, "0", szTemp, MAX_PATH, szFileName);
		if ( szTemp == NULL )
		{
			return;
		}
//		g_xGameProc.m_xInterface.m_nInformationMode = atoi(szTemp);
		//------------------------------------------------------------------------------------------------------------

		// Reverse ShowUserPic On/Off
		GetPrivateProfileString(SECTION_OPTIONS, KEY_SHOWUSERPIC, "1", szTemp, MAX_PATH, szFileName);
		if ( szTemp == NULL )
		{
			return;
		}
		g_xGameProc.m_xInterface.m_bShowUserPic = atoi(szTemp);
		//------------------------------------------------------------------------------------------------------------

		// Reverse ShowHelmet On/Off
		GetPrivateProfileString(SECTION_OPTIONS, KEY_SHOWHELMET, "1", szTemp, MAX_PATH, szFileName);
		if ( szTemp == NULL )
		{
			return;
		}
		g_xGameProc.m_bShowHelmet = atoi(szTemp);
		//------------------------------------------------------------------------------------------------------------

		// Show HealthBar
		GetPrivateProfileString(SECTION_OPTIONS, KEY_SHOWHEALTHBAR, "1", szTemp, MAX_PATH, szFileName);
		if ( szTemp == NULL )
		{
			return;
		}
		mOptionWnd_bShowHealthbar = atoi(szTemp);
		//------------------------------------------------------------------------------------------------------------
		
		// Reverse ShowMonEffect On/Off
		GetPrivateProfileString(SECTION_OPTIONS, KEY_SHOWMONEFFECT, "1", szTemp, MAX_PATH, szFileName);
		if ( szTemp == NULL )
		{
			return;
		}
		g_xGameProc.m_bShowMonEffect = atoi(szTemp);
		//------------------------------------------------------------------------------------------------------------

		// Reverse ShowDeying On/Off
		GetPrivateProfileString(SECTION_OPTIONS, KEY_SHOWDEYING, "1", szTemp, MAX_PATH, szFileName);
		if ( szTemp == NULL )
		{
			return;
		}
		g_xGameProc.m_bShowDeying = atoi(szTemp);
		//------------------------------------------------------------------------------------------------------------

		// Reverse ShowUserPic On/Off
		GetPrivateProfileString(SECTION_OPTIONS, KEY_AUTOPICKUP, "1", szTemp, MAX_PATH, szFileName);
		if ( szTemp == NULL )
		{
			return;
		}
		g_xGameProc.m_bAutoPickup = atoi(szTemp);
		//------------------------------------------------------------------------------------------------------------

		// Reverse ShowUserPic On/Off
		GetPrivateProfileString(SECTION_OPTIONS, KEY_SHOWDROPITEM, "1", szTemp, MAX_PATH, szFileName);
		if ( szTemp == NULL )
		{
			return;
		}
		g_xGameProc.m_bDrawGroundItemName = atoi(szTemp);
		//------------------------------------------------------------------------------------------------------------

		// Reverse ShowUserPic On/Off
		GetPrivateProfileString(SECTION_OPTIONS, KEY_SHOWHEALTHNUM, "1", szTemp, MAX_PATH, szFileName);
		if ( szTemp == NULL )
		{
			return;
		}
		g_xGameProc.m_bDrawHealthNum = atoi(szTemp);
		//------------------------------------------------------------------------------------------------------------
	}
}


VOID COptionWnd::OptionWndSetVolume(BOOL	bIsBgm)
{
	FLOAT	fVol = 0;
	if (bIsBgm == TRUE)
	{
		fVol = (float)mOptionWnd_ptBgmVolBtn.x / 1.8 - 100;
		
		// 볼륨계산   (스크롤버튼위치) / 1.6 
		// 1.6는 스크롤버튼위치 최대값이 160이기 때문에 0~100까지 값을 볼륨으로 갖기 위한 값
		// -100 은 음량의 MAX 가 0 이고 최소가 -100으로 설정하기 위한 보정값.

		g_SoundManager.mSndMngr_lMp3MaxVol = fVol;
		g_SoundManager.mSndMngr_pMp3->Bmmp3SetVolume(g_SoundManager.mSndMngr_lMp3MaxVol);
	}
	else
	{
		fVol = (float)mOptionWnd_ptWaveVolBtn.x / 1.8 - 100;

		g_SoundManager.mSndMngr_lWavMaxVol = fVol;
	}

	SetIniFile();
}


VOID COptionWnd::OptionChanged(INT nRecog, WORD wParam)
{
	BOOL bTemp;

	// 천지합일
	bTemp = nRecog & 0x80000000;
	if ( bTemp != mOptionWnd_bChunjihapil )
	{
		mOptionWnd_bChunjihapil = bTemp;

		if ( mOptionWnd_bChunjihapil )
		{
			m_xOptionBtn[_BTN_ID_CHUNJIHAPIL].ResetGameBtn(297, 297, -1);
		}
		else
		{
			m_xOptionBtn[_BTN_ID_CHUNJIHAPIL].ResetGameBtn(301, 301, 299);
		}
	}

	// 소생술
	bTemp = nRecog & 0x40000000;
	if ( bTemp != mOptionWnd_bRevival )
	{
		mOptionWnd_bRevival = bTemp;

		if ( mOptionWnd_bRevival )
		{
			m_xOptionBtn[_BTN_ID_REVIVAL].ResetGameBtn(297, 297, -1);
		}
		else
		{
			m_xOptionBtn[_BTN_ID_REVIVAL].ResetGameBtn(301, 301, 299);
		}
	}

	// 교환
	bTemp = nRecog & 0x08000000;
	if ( bTemp != mOptionWnd_bExchangeMode )
	{
		mOptionWnd_bExchangeMode = bTemp;

		if ( mOptionWnd_bExchangeMode )
		{
			m_xOptionBtn[_BTN_ID_EXCHANGEMODE].ResetGameBtn(297, 297, -1);
		}
		else
		{
			m_xOptionBtn[_BTN_ID_EXCHANGEMODE].ResetGameBtn(301, 301, 299);
		}
	}

	// 귀엣말
	bTemp = nRecog & 0x04000000;
	if ( bTemp != mOptionWnd_bWhisperMode )
	{
		mOptionWnd_bWhisperMode = bTemp;

		if ( mOptionWnd_bWhisperMode )
		{
			m_xOptionBtn[_BTN_ID_WHISPERMODE].ResetGameBtn(297, 297, -1);
		}
		else
		{
			m_xOptionBtn[_BTN_ID_WHISPERMODE].ResetGameBtn(301, 301, 299);
		}

		if ( g_xGameProc.m_xInterface.m_bChatallDeny == TRUE )
		{
//			g_xGameProc.m_xInterface.m_xInterBtn[ _NEW_BTN_ID_CHATALLDENY].ResetGameBtn(-1, -1, -1);
//			g_xGameProc.m_xInterface.m_xInterBtn[ _NEW_BTN_ID_CHATALLDENY].ChangeBtnTooltip(g_xMsg.GetMsg(2637));
			g_xGameProc.m_xInterface.m_bChatallDeny = FALSE;

		}
		else
		{
//			g_xGameProc.m_xInterface.m_xInterBtn[ _NEW_BTN_ID_CHATALLDENY].ResetGameBtn(1338, 1338, 1338);
//			g_xGameProc.m_xInterface.m_xInterBtn[ _NEW_BTN_ID_CHATALLDENY].ChangeBtnTooltip(g_xMsg.GetMsg(2638));
			g_xGameProc.m_xInterface.m_bChatallDeny = TRUE;
		}
	}

	// 문파전음
	bTemp = nRecog & 0x02000000;
	if ( bTemp != mOptionWnd_bGuildwhisperMode )
	{
		mOptionWnd_bGuildwhisperMode = bTemp;

		if ( mOptionWnd_bGuildwhisperMode )
		{
			m_xOptionBtn[_BTN_ID_GUILDWHISPERMODE].ResetGameBtn(297, 297, -1);
		}
		else
		{
			m_xOptionBtn[_BTN_ID_GUILDWHISPERMODE].ResetGameBtn(301, 301, 299);
		}

		if ( g_xGameProc.m_xInterface.m_bDenyGuild == TRUE )
		{
//			g_xGameProc.m_xInterface.m_xInterBtn[ _NEW_BTN_ID_DENYGUILD].ResetGameBtn(-1, -1, -1);
//			g_xGameProc.m_xInterface.m_xInterBtn[ _NEW_BTN_ID_DENYGUILD].ChangeBtnTooltip(g_xMsg.GetMsg(2639));
			g_xGameProc.m_xInterface.m_bDenyGuild = FALSE;
		}
		else
		{
//			g_xGameProc.m_xInterface.m_xInterBtn[ _NEW_BTN_ID_DENYGUILD].ResetGameBtn(1340, 1340, 1340);
//			g_xGameProc.m_xInterface.m_xInterBtn[ _NEW_BTN_ID_DENYGUILD].ChangeBtnTooltip(g_xMsg.GetMsg(2640));
			g_xGameProc.m_xInterface.m_bDenyGuild = TRUE;
		}
	}

	// 문파가입
	bTemp =  nRecog & 0x01000000;
	if ( bTemp != mOptionWnd_bGuildJoinMode )
	{
		mOptionWnd_bGuildJoinMode = bTemp;

		if ( mOptionWnd_bGuildJoinMode )
		{	
			m_xOptionBtn[_BTN_ID_GUILDJOINMODE].ResetGameBtn(297, 297, -1);
		}
		else
		{
			m_xOptionBtn[_BTN_ID_GUILDJOINMODE].ResetGameBtn(301, 301, 299);
		}
	}

	// 외치기
	bTemp = nRecog & 0x00800000;
	if ( bTemp != mOptionWnd_bShoutMode )
	{
		mOptionWnd_bShoutMode = bTemp;

		if ( mOptionWnd_bShoutMode )
		{	
			m_xOptionBtn[_BTN_ID_SHOUTMODE].ResetGameBtn(297, 297, -1);
		}
		else
		{
			m_xOptionBtn[_BTN_ID_SHOUTMODE].ResetGameBtn(301, 301, 299);
		}

		if ( g_xGameProc.m_xInterface.m_bDenyShout == FALSE )
		{
//			g_xGameProc.m_xInterface.m_xInterBtn[ _NEW_BTN_ID_DENYSHOUT].ResetGameBtn(-1, -1, -1);
//			g_xGameProc.m_xInterface.m_xInterBtn[ _NEW_BTN_ID_DENYSHOUT].ChangeBtnTooltip(g_xMsg.GetMsg(2643));
			g_xGameProc.m_xInterface.m_bDenyGuild = TRUE;
		}
		else
		{
//			g_xGameProc.m_xInterface.m_xInterBtn[ _NEW_BTN_ID_DENYSHOUT].ResetGameBtn(1342, 1342, 1342);
//			g_xGameProc.m_xInterface.m_xInterBtn[ _NEW_BTN_ID_DENYSHOUT].ChangeBtnTooltip(g_xMsg.GetMsg(2644));
			g_xGameProc.m_xInterface.m_bDenyGuild = FALSE;
		}

		g_xGameProc.m_xInterface.m_bDenyShout = !g_xGameProc.m_xInterface.m_bDenyShout;
	}

	// 전체외치기
	bTemp = nRecog & 0x00400000;
	if ( bTemp != mOptionWnd_bWholeShoutMode )
	{
		mOptionWnd_bWholeShoutMode = bTemp;

		if ( mOptionWnd_bWholeShoutMode )
		{	
			m_xOptionBtn[_BTN_ID_WHOLESHOUTMODE].ResetGameBtn(297, 297, -1);
		}
		else
		{
			m_xOptionBtn[_BTN_ID_WHOLESHOUTMODE].ResetGameBtn(301, 301, 299);
		}
	}

	if ( g_xGameProc.m_xInterface.m_xStatusWnd.m_stEquipItem[4].bSetted &&
		 ( g_xGameProc.m_xMyHero.m_bHairImgIdx == _IMAGE_M_HELMET1 || 
		   g_xGameProc.m_xMyHero.m_bHairImgIdx == _IMAGE_M_HELMET2 || 
		   g_xGameProc.m_xMyHero.m_bHairImgIdx == _IMAGE_WM_HELMET1 || 
		   g_xGameProc.m_xMyHero.m_bHairImgIdx == _IMAGE_WM_HELMET2 ))
	{
		// 헬멧을 그리고 있어야 함
		if ( !g_xGameProc.m_bShowHelmet )
			g_xClientSocket.SendSay(g_xMsg.GetMsg(2145));
	}
	else if ( g_xGameProc.m_xInterface.m_xStatusWnd.m_stEquipItem[4].bSetted &&
			  ( g_xGameProc.m_xMyHero.m_bHairImgIdx == _IMAGE_M_HAIR ||
			    g_xGameProc.m_xMyHero.m_bHairImgIdx == _IMAGE_WM_HAIR) )
	{
		// 헬멧을 그리지 않고 있어야 함
		if ( g_xGameProc.m_bShowHelmet )
			g_xClientSocket.SendSay(g_xMsg.GetMsg(2145));
	}

	mOptionWnd_nAttackMode = wParam; //공격방식 0:모두 1:평화 2:그룹단위 3:문파 4:빨갱이
}

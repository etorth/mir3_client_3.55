/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"


CHorseWnd::CHorseWnd()
{
	Init();
}

CHorseWnd::~CHorseWnd()
{
	Destroy();
}

VOID CHorseWnd::Init()
{
	CGameWnd::Init();

	for ( INT nCnt = 0; nCnt < _MAX_HORSE_BTN; nCnt++ )
	{
		m_xHorseBtn[nCnt].Init();
	}
}

VOID CHorseWnd::Destroy()
{
	CGameWnd::Destroy();
}

VOID CHorseWnd::CreateHorseWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove)
{
	CreateGameWnd(nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight);

#ifdef _NEWINTERFACE
	m_xHorseBtn[_BTN_ID_HORSECLOSE].CreateGameBtn(pxWndImage, 1221, 1222, nStartX+236, nStartY+279, "", _BTN_TYPE_FOCUS, 1221, TRUE);
	m_xHorseBtn[_BTN_ID_HORSEUP].CreateGameBtn	 (pxWndImage, 1402, 1403, nStartX+ 19, nStartY+231, "말타기", _BTN_TYPE_FOCUS, 1402, TRUE);
	m_xHorseBtn[_BTN_ID_HORSEDOWN].CreateGameBtn (pxWndImage, 1405, 1406, nStartX+ 77, nStartY+231, "말내리기", _BTN_TYPE_FOCUS, 1405, TRUE);
	m_xHorseBtn[_BTN_ID_HORSEHIDE].CreateGameBtn (pxWndImage, 1408, 1409, nStartX+134, nStartY+231, "말숨기기", _BTN_TYPE_FOCUS, 1408, TRUE);
	m_xHorseBtn[_BTN_ID_HORSEENTER].CreateGameBtn(pxWndImage, 1410, 1411, nStartX+191, nStartY+231, "말꺼내기", _BTN_TYPE_FOCUS, 1410, TRUE);

	m_bOpa = 220;
#else //_NEWINTERFACE
	m_xHorseBtn[_BTN_ID_HORSECLOSE].CreateGameBtn(pxWndImage, 161, 162, nStartX+252, nStartY+293);
	m_xHorseBtn[_BTN_ID_HORSEUP].CreateGameBtn	 (pxWndImage, 860, 861, nStartX+ 28, nStartY+244);
	m_xHorseBtn[_BTN_ID_HORSEDOWN].CreateGameBtn (pxWndImage, 862, 863, nStartX+ 74, nStartY+244);
	m_xHorseBtn[_BTN_ID_HORSEHIDE].CreateGameBtn (pxWndImage, 864, 865, nStartX+133, nStartY+244);
	m_xHorseBtn[_BTN_ID_HORSEENTER].CreateGameBtn(pxWndImage, 866, 867, nStartX+192, nStartY+244);
#endif //_NEWINTERFACE 
}

 	
		
VOID CHorseWnd::ShowHorseWnd()
{
	ShowGameWnd();

#ifdef _NEWINTERFACE
	m_xHorseBtn[_BTN_ID_HORSECLOSE].ChangeRect(m_rcWnd.left+236, m_rcWnd.top+279);
	m_xHorseBtn[_BTN_ID_HORSEUP].ChangeRect	  (m_rcWnd.left+ 19, m_rcWnd.top+232);
	m_xHorseBtn[_BTN_ID_HORSEDOWN].ChangeRect (m_rcWnd.left+ 77, m_rcWnd.top+232);
	m_xHorseBtn[_BTN_ID_HORSEHIDE].ChangeRect (m_rcWnd.left+134, m_rcWnd.top+232);
	m_xHorseBtn[_BTN_ID_HORSEENTER].ChangeRect(m_rcWnd.left+191, m_rcWnd.top+232);
#else //_NEWINTERFACE
	m_xHorseBtn[_BTN_ID_HORSECLOSE].ChangeRect(m_rcWnd.left+252, m_rcWnd.top+293);
	m_xHorseBtn[_BTN_ID_HORSEUP].ChangeRect	  (m_rcWnd.left+ 28, m_rcWnd.top+244);
	m_xHorseBtn[_BTN_ID_HORSEDOWN].ChangeRect (m_rcWnd.left+ 74, m_rcWnd.top+244);
	m_xHorseBtn[_BTN_ID_HORSEHIDE].ChangeRect (m_rcWnd.left+133, m_rcWnd.top+244);
	m_xHorseBtn[_BTN_ID_HORSEENTER].ChangeRect(m_rcWnd.left+192, m_rcWnd.top+244);
#endif //_NEWINTERFACE 

	for ( INT nCnt = _MAX_HORSE_BTN - 1; nCnt >= 0; nCnt-- )
	{
		m_xHorseBtn[nCnt].ShowGameBtn();
	}
}

BOOL CHorseWnd::OnLButtonUp(POINT ptMouse)
{
	if ( m_xHorseBtn[_BTN_ID_HORSECLOSE].OnLButtonUp(ptMouse) )		
		return TRUE;

	if ( m_xHorseBtn[_BTN_ID_HORSEUP].OnLButtonUp(ptMouse) )
	{
		if ( !g_xGameProc.m_xMyHero.m_stFeatureEx.bHorse )
		{
			g_xClientSocket.SendSay ("@이랴");

			// 잠시동안 입력을 막는다. 안 그러면 서버로부터 좌표재설정이 이루어진다.
			g_xGameProc.m_dwInputDelayTime = 300;
			g_xGameProc.m_dwCurrInputDelayTime = 0;
		}
		return FALSE;
	}

	if ( m_xHorseBtn[_BTN_ID_HORSEDOWN].OnLButtonUp(ptMouse) )
	{
		if ( g_xGameProc.m_xMyHero.m_stFeatureEx.bHorse )
		{
			g_xClientSocket.SendSay ("@워워");

			// 잠시동안 입력을 막는다. 안 그러면 서버로부터 좌표재설정이 이루어진다.
			g_xGameProc.m_dwInputDelayTime = 300;
			g_xGameProc.m_dwCurrInputDelayTime = 0;
		}
		return FALSE;
	}

	if ( m_xHorseBtn[_BTN_ID_HORSEHIDE].OnLButtonUp(ptMouse) )
	{
		g_xClientSocket.SendSay ("@말가");
		g_xGameProc.m_dwInputDelayTime = 300;
		g_xGameProc.m_dwCurrInputDelayTime = 0;
		return FALSE;
	}

	if ( m_xHorseBtn[_BTN_ID_HORSEENTER].OnLButtonUp(ptMouse) )
	{
		g_xClientSocket.SendSay ("@워워");
		g_xGameProc.m_dwInputDelayTime = 300;
		g_xGameProc.m_dwCurrInputDelayTime = 0;
		return FALSE;
	}

	return FALSE;
}

BOOL CHorseWnd::OnLButtonDown(POINT ptMouse)
{
	INT nCnt;

	for ( nCnt = 0; nCnt < _MAX_HORSE_BTN; nCnt++ )
	{
		if ( m_xHorseBtn[nCnt].OnLButtonDown(ptMouse) )
			return TRUE;
	}

	return FALSE;
}

VOID CHorseWnd::OnMouseMove(POINT ptMouse)
{
	INT nCnt;

	for ( nCnt = 0; nCnt < _MAX_HORSE_BTN; nCnt++ )
	{
		m_xHorseBtn[nCnt].OnMouseMove(ptMouse);
	}
}

VOID CHorseWnd::SetStatusBtnInit()
{
	INT nCnt;

	for ( nCnt = 0; nCnt < _MAX_HORSE_BTN; nCnt++ )
	{
		m_xHorseBtn[nCnt].SetBtnState(_BTN_STATE_NORMAL);
	}
}


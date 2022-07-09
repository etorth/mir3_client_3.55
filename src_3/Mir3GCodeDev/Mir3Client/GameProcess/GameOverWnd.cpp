/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"


CGameOver::CGameOver()
{
	Init();
}

CGameOver::~CGameOver()
{
	Destroy();
}

VOID CGameOver::Init()
{
	CGameWnd::Init();

	mGameOver_BtnClose.Init();
	mGameOver_BtnLogout.Init();
	mGameOver_BtnExit.Init();
}

VOID CGameOver::Destroy()
{
	CGameWnd::Destroy();
}

VOID CGameOver::CreateGameOverWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend)
{
	CreateGameWnd(nID, pxWndImage, nFrameImgIdx, FALSE, nStartX, nStartY, nWidth, nHeight, bBlend);
	mGameOver_BtnClose.CreateGameBtn(pxWndImage, 1221, 1222, nStartX+220, nStartY+70, g_xMsg.GetMsg(1052), _BTN_TYPE_FOCUS, 1221, TRUE);	
	mGameOver_BtnLogout.CreateGameBtn(pxWndImage, 411, 411, nStartX+30, nStartY+80, "", _BTN_TYPE_NOFOCUS, -1, TRUE);
	mGameOver_BtnExit.CreateGameBtn(pxWndImage, 411, 411, nStartX+110, nStartY+80, "", _BTN_TYPE_NOFOCUS, -1, TRUE);
}

VOID CGameOver::ShowGameOver()
{
	ShowGameWnd();

	mGameOver_BtnClose.ChangeRect(m_rcWnd.left+200, m_rcWnd.top+59);
	mGameOver_BtnLogout.ChangeRect(m_rcWnd.left+23, m_rcWnd.top+67);
	mGameOver_BtnExit.ChangeRect(m_rcWnd.left+114, m_rcWnd.top+67);

	mGameOver_BtnClose.ShowGameBtn();
	mGameOver_BtnExit.ShowGameBtn();
	mGameOver_BtnLogout.ShowGameBtn();

	CHAR pszTmp[MAX_PATH];
	RECT  rcBtnName = {m_rcWnd.left+20, m_rcWnd.top+30, m_rcWnd.left+230, m_rcWnd.top+45};
	
	sprintf(pszTmp, g_xMsg.GetMsg(3500));
	g_xMainWnd.PutsHan(NULL, rcBtnName, RGB(255, 255, 255), RGB(0, 0, 0), pszTmp);

	sprintf(pszTmp, g_xMsg.GetMsg(3501));
	SetRect(&rcBtnName, m_rcWnd.left+23, m_rcWnd.top+67, m_rcWnd.left+92, m_rcWnd.top+88);
	g_xMainWnd.PutsHan(NULL, rcBtnName, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	sprintf(pszTmp, g_xMsg.GetMsg(3502));
	SetRect(&rcBtnName, m_rcWnd.left+114, m_rcWnd.top+67, m_rcWnd.left+183, m_rcWnd.top+88);
	g_xMainWnd.PutsHan(NULL, rcBtnName, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);


}

BOOL CGameOver::OnLButtonUp(POINT ptMouse)
{
	if ( mGameOver_BtnClose.OnLButtonUp(ptMouse) )
		return TRUE;

	if ( mGameOver_BtnExit.OnLButtonUp(ptMouse) )
	{
		if ( g_xGameProc.CanGameOut() )
		{
			WSACleanup();
			g_xGameProc.LoadCredit();

			if ( g_xMainWnd.GetScreenMode() & _DXG_SCREENMODE_WINDOW )
			{
				if ( FAILED(g_xMainWnd.ResetDXG(640, 480, 16, _DXG_SCREENMODE_WINDOW, _DXG_DEVICEMODE_PRIMARY|_DXG_DEVICEMODE_D3D)) )
				{
					MessageBox(g_xMainWnd.GetSafehWnd(), TEXT("DirectDraw RESETUP failed!!!") TEXT("The Program will now exit."), TEXT("MirDXG"), MB_ICONERROR | MB_OK);
				}
			}
			else
			{
				if ( FAILED(g_xMainWnd.ResetDXG(640, 480, 16, _DXG_SCREENMODE_FULLSCREEN, _DXG_DEVICEMODE_PRIMARY|_DXG_DEVICEMODE_D3D)) )
				{
					MessageBox(g_xMainWnd.GetSafehWnd(), TEXT("DirectDraw RESETUP failed!!!") TEXT("The Program will now exit."), TEXT("MirDXG"), MB_ICONERROR | MB_OK);
				}
			}
			return TRUE;
		}
	}

	if ( mGameOver_BtnLogout.OnLButtonUp(ptMouse) )
	{
		if ( g_xGameProc.CanGameOut() )
		{
			g_xClientSocket.SendQueryMsg(CM_SOFTCLOSE);
			g_xGameProc.m_xInterface.SaveItemPos(g_xGameProc.m_xMyHero.m_szName);

			g_xGameProc.m_xInterface.m_xBeltWnd.SaveBeltPosition();
#ifdef _DEBUG
			g_xGameProc.m_xInterface.m_xUtilWnd.SaveUtilSet();
#endif
			g_xGameProc.m_xInterface.m_xMagicShortcutWnd.SaveMagicKeySet();
			g_xGameProc.m_dwFadeTime = 0;
			g_xGameProc.m_bFateState = 2;

			return TRUE;
		}

	}
	return FALSE;
}

BOOL CGameOver::OnLButtonDown(POINT ptMouse)
{
	if ( mGameOver_BtnClose.OnLButtonDown(ptMouse) )
		return TRUE;

	if ( mGameOver_BtnExit.OnLButtonDown(ptMouse) )
		return TRUE;

	if ( mGameOver_BtnLogout.OnLButtonDown(ptMouse) )
		return TRUE;

	return FALSE;
}

VOID CGameOver::OnMouseMove(POINT ptMouse)
{
	mGameOver_BtnClose.OnMouseMove(ptMouse);
	mGameOver_BtnExit.OnMouseMove(ptMouse);
	mGameOver_BtnLogout.OnMouseMove(ptMouse);
}


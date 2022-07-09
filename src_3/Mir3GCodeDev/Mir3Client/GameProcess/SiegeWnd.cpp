/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"


CSiegeWnd::CSiegeWnd()
{
	Init();
}

CSiegeWnd::~CSiegeWnd()
{
	Destroy();
}

VOID CSiegeWnd::Init()
{
	INT nCnt;

	CGameWnd::Init();

	m_ptTarget.x = 0;
	m_ptTarget.y = 0;

	m_nLoadedBullet = 0;
	m_nMaxBullet = 0;
	m_nKind	= 0;

	SetRect(&m_rcMinimap,  0, 0, 0, 0);
	SetRect(&m_rcMinRange,  0, 0, 0, 0);
	SetRect(&m_rcMaxRange,  0, 0, 0, 0);
	SetRect(&m_rcRadar,  0, 0, 0, 0);

	m_bIncrease = TRUE;
	m_nIndex	= 0;

	for ( nCnt = 0; nCnt < _MAX_SIEGE_BTN; nCnt++ )
	{
		m_xSiegeBtn[nCnt].Init();
	}
}

VOID CSiegeWnd::Destroy()
{
	INT nCnt;
	CGameWnd::Destroy();
	for ( nCnt = 0; nCnt < _MAX_SIEGE_BTN; nCnt++ )
	{
		m_xSiegeBtn[nCnt].Destroy();
	}
	Init();
}

VOID CSiegeWnd::CreateSiegeWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove)
{
	CreateGameWnd(nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight);

	m_xSiegeBtn[_BTN_ID_SIEGECLOSE].CreateGameBtn(pxWndImage, 1221, 1222, nStartX+270, nStartY+391, g_xMsg.GetMsg(1052), _BTN_TYPE_FOCUS, 1221, TRUE);
	m_xSiegeBtn[_BTN_ID_ATTACK].CreateGameBtn(pxWndImage, 692, 693, nStartX+14, nStartY+231, g_xMsg.GetMsg(4300), _BTN_TYPE_FOCUS, -1, FALSE);
	m_xSiegeBtn[_BTN_ID_WAIT].CreateGameBtn(pxWndImage, 694, 695, nStartX+67, nStartY+231, g_xMsg.GetMsg(4301), _BTN_TYPE_FOCUS, -1, FALSE);
	m_xSiegeBtn[_BTN_ID_MOVE].CreateGameBtn(pxWndImage, 696, 697, nStartX+117, nStartY+231, g_xMsg.GetMsg(4302), _BTN_TYPE_FOCUS, -1, FALSE);
}	
		
VOID CSiegeWnd::ShowSiegeWnd()
{
	SetRect(&m_rcMinimap,  m_rcWnd.left+6, m_rcWnd.top+65, m_rcWnd.left+186, m_rcWnd.top+250 );

	if ( m_bActive )
	{
		INT	nX, nY;

		LPGROUPPOS lpGroupPos;

		lpGroupPos = g_xGameProc.FindGroupPos(m_nIndex);

		if ( lpGroupPos != NULL )
		{
			g_xGameProc.m_xInterface.m_xMiniMapInSiege.MoveMiniMap(lpGroupPos->nPosX, lpGroupPos->nPosY);
	//		m_xMiniMapInSiege.MoveMiniMap(g_xGameProc.m_xMyHero.m_nPosX, g_xGameProc.m_xMyHero.m_nPosY);
			g_xGameProc.m_xInterface.m_xMiniMapInSiege.RenderMinimapInMain(timeGetTime());

			INT nSX, nSY;
			if ( m_nKind == 1 )
			{
				nSX = (INT)(m_rcMinimap.left + lpGroupPos->nPosX*1.04f - g_xGameProc.m_xInterface.m_xMiniMapInSiege.m_rcView.left*0.7f - 1);
				nSY = (INT)(m_rcMinimap.top + lpGroupPos->nPosY*0.59f - g_xGameProc.m_xInterface.m_xMiniMapInSiege.m_rcView.top*0.58f - 1);

				SetRect(&m_rcMinRange,  nSX-55, nSY-34, nSX+55, nSY+34);
				g_xMainWnd.DrawWithGDI(&m_rcMinRange, NULL, RGB(200, 100, 100), 1);

				SetRect(&m_rcMaxRange,  nSX-80, nSY-50, nSX+80, nSY+50);
				g_xMainWnd.DrawWithGDI(&m_rcMaxRange, NULL, RGB(250, 50, 50), 1);
			}
			else if ( m_nKind > 0 )
			{
				nSX = (INT)(m_rcMinimap.left + lpGroupPos->nPosX*1.04f - g_xGameProc.m_xInterface.m_xMiniMapInSiege.m_rcView.left*0.7f - 1);
				nSY = (INT)(m_rcMinimap.top + lpGroupPos->nPosY*0.59f - g_xGameProc.m_xInterface.m_xMiniMapInSiege.m_rcView.top*0.58f - 1);

				SetRect(&m_rcMinRange,  nSX-28, nSY-16, nSX+28, nSY+16);
				g_xMainWnd.DrawWithGDI(&m_rcMinRange, NULL, RGB(200, 100, 100), 1);

				SetRect(&m_rcMaxRange,  nSX-50, nSY-29, nSX+50, nSY+29);
				g_xMainWnd.DrawWithGDI(&m_rcMaxRange, NULL, RGB(250, 50, 50), 1);
			}


		}
	}
		
	ShowGameWnd();

	m_xSiegeBtn[_BTN_ID_SIEGECLOSE].ChangeRect(m_rcWnd.left+146, m_rcWnd.top+236);
	m_xSiegeBtn[_BTN_ID_ATTACK].ChangeRect(m_rcWnd.left+22, m_rcWnd.top+235);
	m_xSiegeBtn[_BTN_ID_WAIT].ChangeRect(m_rcWnd.left+62, m_rcWnd.top+235);
	m_xSiegeBtn[_BTN_ID_MOVE].ChangeRect(m_rcWnd.left+102, m_rcWnd.top+235);

	INT nCnt;

	RECT rcNum, rcArea, rcDevide;
	CHAR szStr[MAX_PATH];

	SetRect(&rcNum,  m_rcWnd.left+40, m_rcWnd.top+27, m_rcWnd.left+95, m_rcWnd.top+42 );
	sprintf(szStr, "%d", m_nLoadedBullet);	

	g_xMainWnd.PutsHan(NULL, rcNum, RGB(248, 200, 100), RGB(0, 0, 0), szStr);

	sprintf(szStr, "/");
	SetRect(&rcNum,  m_rcWnd.left+95, m_rcWnd.top+27, m_rcWnd.left+100, m_rcWnd.top+42 );
	g_xMainWnd.PutsHan(NULL, rcNum, RGB(255, 255, 255), RGB(0, 0, 0), szStr);

	SetRect(&rcNum,  m_rcWnd.left+100, m_rcWnd.top+27, m_rcWnd.left+150, m_rcWnd.top+42 );

	sprintf(szStr, "%d", m_nMaxBullet);	

	g_xMainWnd.PutsHan(NULL, rcNum, RGB(248, 200, 100), RGB(0, 0, 0), szStr);


	for ( nCnt = 0; nCnt < _MAX_SIEGE_BTN; nCnt++ )
	{
		m_xSiegeBtn[nCnt].ShowGameBtn();
	}
}

BOOL CSiegeWnd::OnLButtonUp(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse)
{
	if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse && !pstCommonItemSet->bIsEquipItem )
	{
		if ( pstCommonItemSet->xItem.m_stItemInfo.stStdItem.wLooks == 310 || pstCommonItemSet->xItem.m_stItemInfo.stStdItem.wLooks == 311 )
		{
			g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_CHARGE_BULLET, _YESNO, g_xMsg.GetMsg(4304), TRUE);
			return FALSE;
		}
	}

	if ( m_xSiegeBtn[_BTN_ID_SIEGECLOSE].OnLButtonUp(ptMouse) )
	{
		m_ptTarget.x = 0;
		m_ptTarget.y = 0;
		return TRUE;
	}

	if ( m_xSiegeBtn[_BTN_ID_ATTACK].OnLButtonUp(ptMouse) )
	{
		INT nLocate;

		if ( m_ptTarget.x != 0 && m_ptTarget.y != 0 )
		{
			nLocate = MAKELONG(m_ptTarget.x, m_ptTarget.y);
			g_xClientSocket.SendAttackShooter(nLocate);
		}
		return FALSE;
	}
	if ( m_xSiegeBtn[_BTN_ID_WAIT].OnLButtonUp(ptMouse) )
	{
		g_xClientSocket.SendWaitShooter();
		return FALSE;
	}
	if ( m_xSiegeBtn[_BTN_ID_MOVE].OnLButtonUp(ptMouse) )
	{
		m_ptTarget.x = 0;
		m_ptTarget.y = 0;
		g_xClientSocket.SendMoveShooter();
		return FALSE;
	}
	return FALSE;
}

BOOL CSiegeWnd::OnLButtonDown(POINT ptMouse)
{
	INT	nCnt;
	POINT ptLoc;

	SetRect(&m_rcRadar,  m_rcMinRange.left, m_rcMinRange.top, m_rcMinRange.right, m_rcMinRange.bottom);
	
	for( nCnt = 0; nCnt < _MAX_SIEGE_BTN; nCnt++ )
	{
		if ( m_xSiegeBtn[nCnt].OnLButtonDown(ptMouse) )		
			return TRUE;
	}
	
	if ( PtInRect(&m_rcMaxRange, ptMouse) )
	{
		if ( PtInRect(&m_rcMinRange, ptMouse) )
			return FALSE;
	}
	else
	{
		return FALSE;
	}
	 
	if ( PtInRect(&m_rcMinimap, ptMouse) )
	{
		if ( PtInRect(&m_rcMinRange, ptMouse) )
		{
			DWORD dwFont = GetChatColor(_CHAT_COLOR3);
			DWORD dwBack = GetChatColor(_CHAT_COLOR8);

			g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(4303));
			
			return FALSE;
		}
		ptLoc.x = ptMouse.x - m_rcWnd.left;
		ptLoc.y = ptMouse.y - m_rcWnd.top;

		m_ptTarget.x = (ptMouse.x + g_xGameProc.m_xInterface.m_xMiniMapInSiege.m_rcView.left*0.7f - m_rcMinimap.left)/1.04f;
		m_ptTarget.y = (ptMouse.y + g_xGameProc.m_xInterface.m_xMiniMapInSiege.m_rcView.top*0.58f - m_rcMinimap.top)/0.59f;

//		m_ptTarget.x = (ptMouse.x + g_xGameProc.m_xInterface.m_xMiniMapInSiege.m_rcView.left - m_rcMinimap.left)/1.5f;
//		m_ptTarget.y = ptMouse.y + g_xGameProc.m_xInterface.m_xMiniMapInSiege.m_rcView.top - m_rcMinimap.top;
	}

	return FALSE;
}

VOID CSiegeWnd::OnMouseMove(POINT ptMouse)
{

	for( INT nCnt = 0; nCnt < _MAX_SIEGE_BTN; nCnt++ )
	{
		m_xSiegeBtn[nCnt].OnMouseMove(ptMouse);
	}
}

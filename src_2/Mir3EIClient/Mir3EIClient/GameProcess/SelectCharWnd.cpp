
#include "StdAfx.h"

#define POS_DRAWSTART_X	25
#define POS_DRAWSTART_Y	45

CSelectCharWnd::CSelectCharWnd()
{
	Init();
}

CSelectCharWnd::~CSelectCharWnd()
{
	Destroy();
}

VOID CSelectCharWnd::CreateSelectCharWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove)
{
	CreateGameWnd(nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight, 0, 0);

	m_xButtonClose.CreateGameBtn(pxWndImage,  1221,  1222, m_rcWnd.left+272, m_rcWnd.top+105);
}

VOID CSelectCharWnd::ShowSelectCharWnd()
{
	RECT tRect = GetGameWndRect();

	ShowGameWnd();

	m_nStartLine = 0;

	int nLineCnt = 0;
	CCharLine* pScriptLine;
	m_ScriptList.MoveCurrentToTop();
	for (int i = 0; i < m_ScriptList.GetCounter(); i++)
	{
		pScriptLine = m_ScriptList.GetCurrentData();

		HFONT		hFont = NULL;
		COLORREF	color = RGB(255, 255, 0);

		if (pScriptLine->m_fIsFocused)
			hFont = g_xMainWnd.CreateGameFont("ËÎÌו", 9, 0, FW_NORMAL, FALSE, TRUE);

			if (pScriptLine->m_fIsSelected)
			color = RGB(255, 0, 0);

		int nLine = 0;
		SIZE tSize = g_xMainWnd.GetStrLength(NULL, NULL, pScriptLine->m_pszScriptText);
		
		pScriptLine->m_Rect.left	= tRect.left + POS_DRAWSTART_X;
		pScriptLine->m_Rect.top		= tRect.top + (nLineCnt - m_nStartLine) * (tSize.cy + 3) + POS_DRAWSTART_Y;
		pScriptLine->m_Rect.right	= pScriptLine->m_Rect.left + tSize.cx;
		pScriptLine->m_Rect.bottom	= pScriptLine->m_Rect.top + tSize.cy;

		if ( nLineCnt <= m_nStartLine + 20 )
			g_xMainWnd.PutsHan(NULL, pScriptLine->m_Rect.left, pScriptLine->m_Rect.top,
			color, RGB(0, 0, 0), pScriptLine->m_pszScriptText, hFont);
	
		nLineCnt ++;
		
		DeleteObject(hFont);

		m_ScriptList.MoveNextNode();
	}

	m_xButtonClose.ShowGameBtn();

}

VOID CSelectCharWnd::Init()
{
	CGameWnd::Init();
}

VOID CSelectCharWnd::Destroy()
{
	CGameWnd::Destroy();
}

BOOL CSelectCharWnd::OnLButtonUp(POINT ptMouse)
{
	RECT tRect = GetGameWndRect();

	if( m_xButtonClose.OnLButtonUp(ptMouse) )
	{
		HideChars();
		return TRUE;
	}

	CCharLine*	pScriptLine;
	m_ScriptList.MoveCurrentToTop();

	for (int i = 0; i < m_ScriptList.GetCounter(); i++)
	{
		pScriptLine = m_ScriptList.GetCurrentData();

		if (PtInRect(&pScriptLine->m_Rect, ptMouse))
		{
			SendCommand( pScriptLine->m_pszScriptText );
		}

		m_ScriptList.MoveNextNode();
	}


	return FALSE;
}

BOOL CSelectCharWnd::OnLButtonDown(POINT ptMouse)
{
	CCharLine*	pScriptLine;
	m_ScriptList.MoveCurrentToTop();

	for (int i = 0; i < m_ScriptList.GetCounter(); i++)
	{
		pScriptLine = m_ScriptList.GetCurrentData();

		if (PtInRect(&pScriptLine->m_Rect, ptMouse))
			pScriptLine->m_fIsSelected	= TRUE;
		else
			pScriptLine->m_fIsSelected	= FALSE;

		m_ScriptList.MoveNextNode();
	}

	return FALSE;
}

VOID CSelectCharWnd::OnMouseMove(POINT ptMouse)
{
	m_xButtonClose.ChangeRect(m_rcWnd.left+272, m_rcWnd.top+105);
	m_xButtonClose.OnMouseMove( ptMouse );
	m_xButtonClose.m_bBtnState = _BTN_STATE_FOCUS;

	CCharLine*	pScriptLine;
	m_ScriptList.MoveCurrentToTop();

	for (int i = 0; i < m_ScriptList.GetCounter(); i++)
	{
		pScriptLine = m_ScriptList.GetCurrentData();

		if (PtInRect(&pScriptLine->m_Rect, ptMouse))
			pScriptLine->m_fIsFocused	= TRUE;
		else
			pScriptLine->m_fIsFocused	= FALSE;

		m_ScriptList.MoveNextNode();
	}

}
VOID CSelectCharWnd::ShowAddChar()
{
	int nX = g_xGameProc.m_pMyHero->m_wPosX;
	int nY = g_xGameProc.m_pMyHero->m_wPosY;

	CActor*	pxActor;
	g_xGameProc.m_xActorList.MoveCurrentToTop();
	for ( int nCnt = 0; nCnt < g_xGameProc.m_xActorList.GetCounter(); nCnt++)
	{
		pxActor = g_xGameProc.m_xActorList.GetCurrentData();
		if( (pxActor->m_stFeature.bGender == _GENDER_MAN || pxActor->m_stFeature.bGender == _GENDER_WOMAN ) &&
			( (pxActor->m_wPosX - nX) * (pxActor->m_wPosX - nX) + 
			(pxActor->m_wPosY - nY) * (pxActor->m_wPosY - nY) <= 100) )
		{
			CCharLine* pCharLine = new CCharLine;

			strcpy( pCharLine->m_pszScriptText, pxActor->m_szName );
			m_ScriptList.AddNode(pCharLine);
		}
		g_xGameProc.m_xActorList.MoveNextNode();
	}	
	SetGameWndActive( TRUE );

}

VOID CSelectCharWnd::ShowDelChar()
{
	CGroupMember*	pxActor;
	for ( int nCnt = 0; nCnt < g_xGameProc.m_xInterface.m_xGroupWnd.m_xGroupList.GetCounter(); nCnt++)
	{
		pxActor = g_xGameProc.m_xInterface.m_xGroupWnd.m_xGroupList.GetCurrentData();
		CCharLine* pCharLine = new CCharLine;
	
		strcpy( pCharLine->m_pszScriptText, pxActor->szMemberName );
		m_ScriptList.AddNode(pCharLine);
		
		g_xGameProc.m_xActorList.MoveNextNode();
	}	
	SetGameWndActive( TRUE );

}

VOID CSelectCharWnd::HideChars()
{
	CCharLine* pCharLine;

	m_ScriptList.MoveCurrentToTop();

	for (int i = 0; i < m_ScriptList.GetCounter(); i++)
	{
		pCharLine = m_ScriptList.GetCurrentData();

		if (pCharLine)
			delete pCharLine;

		m_ScriptList.DeleteCurrentNodeEx();
	}

	SetGameWndActive( FALSE );
}

VOID CSelectCharWnd::SendCommand(CHAR* szCharName)
{
	switch(m_nCommand) 
	{
	case 0:
		g_xLoginSocket.SendCreateGroup( szCharName );
		break;
	case 1:
		g_xLoginSocket.SendAddGroupMember( szCharName );
		break;
	case 2:
		g_xLoginSocket.SendDelGroupMember( szCharName );
		break;
	}
}

/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"


CSettingWnd::CSettingWnd()
{
	Init();
}

CSettingWnd::~CSettingWnd()
{
	Destroy();
}

VOID CSettingWnd::Init()
{
	CGameWnd::Init();

	mSetting_BtnClose.Init();
}

VOID CSettingWnd::Destroy()
{
	CGameWnd::Destroy();
}

VOID CSettingWnd::CreateSettingWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend)
{
	CreateGameWnd(nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight, bBlend);

	mSetting_BtnClose.CreateGameBtn(pxWndImage, 1221, 1222, nStartX+393, nStartY+264, g_xMsg.GetMsg(1052), _BTN_TYPE_FOCUS, 1221, TRUE);
	mSetting_BtnChatSize.CreateGameBtn(pxWndImage, 311, 311, nStartX+393, nStartY+264, "", _BTN_TYPE_NOFOCUS, -1, TRUE);
	mSetting_BtnMessenger.CreateGameBtn(pxWndImage, 311, 311, nStartX+393, nStartY+264, "", _BTN_TYPE_NOFOCUS, -1, TRUE);
	mSetting_BtnGroup.CreateGameBtn(pxWndImage, 311, 311, nStartX+393, nStartY+264, "", _BTN_TYPE_NOFOCUS, -1, TRUE);
	mSetting_BtnGuild.CreateGameBtn(pxWndImage, 311, 311, nStartX+393, nStartY+264, "", _BTN_TYPE_NOFOCUS, -1, TRUE);
	mSetting_BtnUserpic.CreateGameBtn(pxWndImage, 311, 311, nStartX+393, nStartY+264, "", _BTN_TYPE_NOFOCUS, -1, TRUE);
	mSetting_BtnSiege.CreateGameBtn(pxWndImage, 311, 311, nStartX+393, nStartY+264, "", _BTN_TYPE_NOFOCUS, -1, TRUE);
	mSetting_BtnExit.CreateGameBtn(pxWndImage, 311, 311, nStartX+393, nStartY+264, "", _BTN_TYPE_NOFOCUS, -1, TRUE);
	mSetting_BtnOption.CreateGameBtn(pxWndImage, 311, 311, nStartX+393, nStartY+264, "", _BTN_TYPE_NOFOCUS, -1, TRUE);
//	mSetting_BtnUtil.CreateGameBtn(pxWndImage, 311, 311, nStartX+393, nStartY+264, "", _BTN_TYPE_NOFOCUS, -1, TRUE);

}	
		
VOID CSettingWnd::ShowSettingWnd()
{
	CHAR pszTmp[MAX_PATH];
	RECT rcMenu;

	ShowGameWnd();

	mSetting_BtnOption.ChangeRect(m_rcWnd.left+25, m_rcWnd.top+32);
	mSetting_BtnChatSize.ChangeRect(m_rcWnd.left+25, m_rcWnd.top+67);
	mSetting_BtnMessenger.ChangeRect(m_rcWnd.left+25, m_rcWnd.top+102);
	mSetting_BtnGroup.ChangeRect(m_rcWnd.left+25, m_rcWnd.top+137);
	mSetting_BtnGuild.ChangeRect(m_rcWnd.left+25, m_rcWnd.top+172);
	mSetting_BtnUserpic.ChangeRect(m_rcWnd.left+25, m_rcWnd.top+207);
	mSetting_BtnSiege.ChangeRect(m_rcWnd.left+25, m_rcWnd.top+242);
	mSetting_BtnExit.ChangeRect(m_rcWnd.left+25, m_rcWnd.top+277);
	mSetting_BtnClose.ChangeRect(m_rcWnd.left+102, m_rcWnd.top+353);
//	mSetting_BtnUtil.ChangeRect(m_rcWnd.left+25, m_rcWnd.top+312);

	mSetting_BtnChatSize.ShowGameBtn();
	mSetting_BtnMessenger.ShowGameBtn();
	mSetting_BtnGroup.ShowGameBtn();
	mSetting_BtnGuild.ShowGameBtn();
	mSetting_BtnUserpic.ShowGameBtn();
	mSetting_BtnSiege.ShowGameBtn();
	mSetting_BtnExit.ShowGameBtn();
	mSetting_BtnOption.ShowGameBtn();
	mSetting_BtnClose.ShowGameBtn();
//	mSetting_BtnUtil.ShowGameBtn();

	// 옵션창
	sprintf(pszTmp, g_xMsg.GetMsg(4950));
	SetRect(&rcMenu, m_rcWnd.left+24, m_rcWnd.top+35, m_rcWnd.left+116, m_rcWnd.top+50);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	// 채팅확대
	sprintf(pszTmp, g_xMsg.GetMsg(4951));
	SetRect(&rcMenu, m_rcWnd.left+24, m_rcWnd.top+70, m_rcWnd.left+116, m_rcWnd.top+85);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	// 메신저
	sprintf(pszTmp, g_xMsg.GetMsg(4952));
	SetRect(&rcMenu, m_rcWnd.left+24, m_rcWnd.top+105, m_rcWnd.left+116, m_rcWnd.top+120);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	// 그룹창
	sprintf(pszTmp, g_xMsg.GetMsg(4953));
	SetRect(&rcMenu, m_rcWnd.left+24, m_rcWnd.top+140, m_rcWnd.left+116, m_rcWnd.top+155);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	// 문파
	sprintf(pszTmp, g_xMsg.GetMsg(4954));
	SetRect(&rcMenu, m_rcWnd.left+24, m_rcWnd.top+175, m_rcWnd.left+116, m_rcWnd.top+190);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	// 사진등록
	sprintf(pszTmp, g_xMsg.GetMsg(4955));
	SetRect(&rcMenu, m_rcWnd.left+24, m_rcWnd.top+210, m_rcWnd.left+116, m_rcWnd.top+225);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	// 발석거
	sprintf(pszTmp, g_xMsg.GetMsg(4956));
	SetRect(&rcMenu, m_rcWnd.left+24, m_rcWnd.top+245, m_rcWnd.left+116, m_rcWnd.top+260);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

	// 종 료
	sprintf(pszTmp, g_xMsg.GetMsg(4957));
	SetRect(&rcMenu, m_rcWnd.left+24, m_rcWnd.top+280, m_rcWnd.left+116, m_rcWnd.top+295);
	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);

//	// 매크로
//	sprintf(pszTmp, g_xMsg.GetMsg(4958));
//	SetRect(&rcMenu, m_rcWnd.left+24, m_rcWnd.top+315, m_rcWnd.left+116, m_rcWnd.top+330);
//	g_xMainWnd.PutsHan(NULL, rcMenu, RGB(255, 150, 0), RGB(0, 0, 0), pszTmp);
}


BOOL CSettingWnd::OnLButtonUp(POINT ptMouse)
{
	//공통
	if ( mSetting_BtnClose.OnLButtonUp(ptMouse) )
	{
		return TRUE;
	}

	if ( mSetting_BtnChatSize.OnLButtonUp(ptMouse) )
	{
		if ( !g_xGameProc.m_xInterface.m_xChatWnd.GetGameWndActive() )
		{
			if ( g_xGameProc.m_xInterface.m_xChatWnd.mChat_bLargeChat == FALSE )
				g_xGameProc.m_xInterface.m_xChatWnd.ChangeChatSize();
			g_xGameProc.m_xInterface.m_xChatWnd.ActiveEditBox();
		}
		else
		{
			ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_HIDE);
			g_xGameProc.m_xInterface.WindowActivate(_WND_ID_CHAT);
		}

		return FALSE;
	}

	if ( mSetting_BtnMessenger.OnLButtonUp(ptMouse) )
	{
		if ( g_xGameProc.m_xInterface.m_bHasNewMessage == TRUE || g_xGameProc.m_xInterface.m_xMessengerWnd.mMessenger_xReceivedMSGList.GetCount() == 0 )
			g_xClientSocket.SendRefreshMailBox(0);
		if ( !g_xGameProc.m_xInterface.m_xMessengerWnd.GetGameWndActive() )
			g_xGameProc.m_xInterface.WindowActivate(_WND_ID_MESSENGER);
		else
		{
			g_xGameProc.m_xInterface.m_xMessengerWnd.CloseMessengerWnd();
		}
		return FALSE;
	}

	if ( mSetting_BtnGroup.OnLButtonUp(ptMouse) )
	{
		g_xGameProc.m_xInterface.WindowActivate(_WND_ID_GROUP);
		return FALSE;
	}

	if ( mSetting_BtnGuild.OnLButtonUp(ptMouse) )
	{
		if ( !g_xGameProc.m_xInterface.m_xGuildWnd.GetGameWndActive() )
			g_xClientSocket.SendGuildHome();
		else
			g_xGameProc.m_xInterface.WindowActivate(_WND_ID_GUILD);

		return FALSE;
	}

	if ( mSetting_BtnUserpic.OnLButtonUp(ptMouse) )
	{
		g_xGameProc.m_xInterface.WindowActivate(_WND_ID_FACEIMGUP);
		return FALSE;
	}

	if ( mSetting_BtnSiege.OnLButtonUp(ptMouse) )
	{
		if ( g_xGameProc.m_xInterface.m_bHasSiege )
		{
			if ( g_xGameProc.m_xInterface.WindowActivate(_WND_ID_SIEGE) == TRUE )
			{
				g_xClientSocket.SendWantMMap();
			}
			else
			{
			}
		}
		
		return FALSE;
	}

	if ( mSetting_BtnExit.OnLButtonUp(ptMouse) )
	{
		if ( g_xGameProc.CanGameOut() )
		{
			g_xGameProc.m_xInterface.WindowActivate(_WNDIMGIDX_EXIT);
		}
		return FALSE;
	}

	if ( mSetting_BtnOption.OnLButtonUp(ptMouse) )
	{
		g_xGameProc.m_xInterface.WindowActivate(_WND_ID_OPTION);
		return FALSE;
	}

//	if ( mSetting_BtnUtil.OnLButtonUp(ptMouse) )
//	{
//		g_xGameProc.m_xInterface.WindowActivate(_WND_ID_UTIL);
//		return FALSE;
//	}

	return FALSE;
}

BOOL CSettingWnd::OnLButtonDown(POINT ptMouse)
{
	//공통
	if ( mSetting_BtnClose.OnLButtonDown(ptMouse) )
	{
		return TRUE;
	}

	if ( mSetting_BtnChatSize.OnLButtonDown(ptMouse) )
	{
		return TRUE;
	}

	if ( mSetting_BtnMessenger.OnLButtonDown(ptMouse) )
	{
		return TRUE;
	}

	if ( mSetting_BtnGroup.OnLButtonDown(ptMouse) )
	{
		return TRUE;
	}

	if ( mSetting_BtnGuild.OnLButtonDown(ptMouse) )
	{
		return TRUE;
	}

	if ( mSetting_BtnUserpic.OnLButtonDown(ptMouse) )
	{
		return TRUE;
	}

	if ( mSetting_BtnSiege.OnLButtonDown(ptMouse) )
	{
		return TRUE;
	}

	if ( mSetting_BtnExit.OnLButtonDown(ptMouse) )
	{
		return TRUE;
	}
	
	if ( mSetting_BtnOption.OnLButtonDown(ptMouse) )
	{
		return TRUE;
	}

//	if ( mSetting_BtnUtil.OnLButtonDown(ptMouse) )
///	{
//		return TRUE;
//	}
	


	return FALSE;
}

BOOL CSettingWnd::OnMouseMove(POINT ptMouse)
{
	// 공통
	mSetting_BtnClose.OnMouseMove(ptMouse);
	mSetting_BtnChatSize.OnMouseMove(ptMouse);
	mSetting_BtnMessenger.OnMouseMove(ptMouse);
	mSetting_BtnGroup.OnMouseMove(ptMouse);
	mSetting_BtnGuild.OnMouseMove(ptMouse);
	mSetting_BtnUserpic.OnMouseMove(ptMouse);
	mSetting_BtnSiege.OnMouseMove(ptMouse);
	mSetting_BtnExit.OnMouseMove(ptMouse);
	mSetting_BtnOption.OnMouseMove(ptMouse);
//	mSetting_BtnUtil.OnMouseMove(ptMouse);

	return FALSE;
}


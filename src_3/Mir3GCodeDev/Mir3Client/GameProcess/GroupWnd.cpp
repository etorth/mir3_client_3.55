/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/

#include "StdAfx.h"


CGroupWnd::CGroupWnd()
{
	Init();
}

CGroupWnd::~CGroupWnd()
{
	Destroy();
}

VOID CGroupWnd::CreateGroupWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove)
{
	CreateGameWnd(nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight);

	m_xGroupBtn[_BTN_ID_GROUPCLOSE].CreateGameBtn(pxWndImage, 1221, 1222, nStartX+217, nStartY+200, "", _BTN_TYPE_FOCUS, 1221, TRUE);
	m_xGroupBtn[_BTN_ID_GROUPMAKE].CreateGameBtn (pxWndImage, 176, 176, nStartX+ 41, nStartY+193, g_xMsg.GetMsg(1600));
	m_xGroupBtn[_BTN_ID_GROUPADD].CreateGameBtn  (pxWndImage, 172, 172, nStartX+101, nStartY+193, g_xMsg.GetMsg(1601));
	m_xGroupBtn[_BTN_ID_GROUPDEL].CreateGameBtn  (pxWndImage, 174, 174, nStartX+161, nStartY+193, g_xMsg.GetMsg(1602));
	m_xGroupBtn[_BTN_ID_GROUPICON].CreateGameBtn (pxWndImage, 177, 177, nStartX+ 20, nStartY+ 44);
}

/*
BOOL CGroupWnd::bIsMyGroup(CHAR* pszName)
{
	CGroupMember*	pGroupMember = NULL;
	CListNode <	CGroupMember > *pNode;

	if ( m_xGroupList.GetCount() )
	{
		for ( pNode = m_xGroupList.GetHead(); pNode; pNode = pNode->GetNext() )
		{
			pGroupMember = pNode->GetData();

			if ( pGroupMember )
			{
				if ( !strcmp(pszName, pGroupMember->szMemberName) )
				{
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}
*/


VOID CGroupWnd::ShowGroupWnd()
{
	CGroupMember*	pGroupMember = NULL;
	CListNode <	CGroupMember > *pNode;

	RECT tRect = GetGameWndRect();

	INT	 nX = tRect.left +45;
	INT	 nY = tRect.top + 70;
	INT	 i  = 0;
	INT  nYPos;
	RECT rcName = { tRect.left + 44, tRect.top + 25, tRect.left + 150, tRect.top + 40 };

	ShowGameWnd();

	g_xMainWnd.PutsHan(NULL, rcName, RGB(200, 230, 220), RGB(0, 0, 0), g_xGameProc.m_xMyHero.m_szName, NULL);

	if ( m_xGroupList.GetCount() )
	{
		for ( pNode = m_xGroupList.GetHead(); pNode; pNode = pNode->GetNext() )
		{
			pGroupMember = pNode->GetData();

			if ( pGroupMember )
			{
				nYPos = (i / 2) * 20;

				if ( i % 2 ) 
				{
					g_xMainWnd.PutsHan(NULL, nX,     nY+nYPos, RGB(255, 255, 255), RGB(0, 0, 0), pGroupMember->szMemberName);
				}
				else
				{
					g_xMainWnd.PutsHan(NULL, nX+100, nY+nYPos, RGB(255, 255, 255), RGB(0, 0, 0), pGroupMember->szMemberName);
				}

				i++;
			}
		}
	}

	m_xGroupBtn[_BTN_ID_GROUPCLOSE].ChangeRect(m_rcWnd.left+190, m_rcWnd.top+192);
	m_xGroupBtn[_BTN_ID_GROUPMAKE].ChangeRect (m_rcWnd.left+128, m_rcWnd.top+191);
	m_xGroupBtn[_BTN_ID_GROUPADD].ChangeRect  (m_rcWnd.left+ 28, m_rcWnd.top+191);
	m_xGroupBtn[_BTN_ID_GROUPDEL].ChangeRect  (m_rcWnd.left+ 78, m_rcWnd.top+191);
	m_xGroupBtn[_BTN_ID_GROUPICON].ChangeRect (m_rcWnd.left+182, m_rcWnd.top+ 16);

/*	if ( m_bAllowGroup )
	{
		g_xMainWnd.PutsHan(NULL, tRect.left + 110, tRect.top + 52, RGB(200, 230, 220), RGB(0, 0, 0), g_xMsg.GetMsg(1603));
	}
	else
	{
		g_xMainWnd.PutsHan(NULL, tRect.left + 110, tRect.top + 52, RGB(200, 230, 220), RGB(0, 0, 0), g_xMsg.GetMsg(1604));
	}
*/
	for ( INT nCnt = 0; nCnt < _MAX_GROUP_BTN; nCnt++ )
	{
		m_xGroupBtn[nCnt].ShowGameBtn();
	}
}

VOID CGroupWnd::Init()
{
	CGameWnd::Init();

	m_xGroupList.ClearAll();

//	m_bAllowGroup = FALSE;

	for ( INT nCnt = 0; nCnt < _MAX_GROUP_BTN; nCnt++ )
	{
		m_xGroupBtn[nCnt].Init();
	}
}

VOID CGroupWnd::Destroy()
{
	CGameWnd::Destroy();
}

BOOL CGroupWnd::OnLButtonUp(POINT ptMouse)
{
	if ( m_xGroupBtn[_BTN_ID_GROUPCLOSE].OnLButtonUp(ptMouse) )		
	{
		return TRUE;
	}

	if ( m_xGroupBtn[_BTN_ID_GROUPMAKE].OnLButtonUp(ptMouse) )
	{
		g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GROUP, _YESNO, g_xMsg.GetMsg(1605), TRUE, -1, -1, CM_CREATEGROUP);

		return FALSE;
	}

	if ( m_xGroupBtn[_BTN_ID_GROUPADD].OnLButtonUp(ptMouse) )
	{
		g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GROUP, _YESNO, g_xMsg.GetMsg(1605), TRUE, -1, -1, CM_ADDGROUPMEMBER);

		return FALSE;
	}

	if ( m_xGroupBtn[_BTN_ID_GROUPDEL].OnLButtonUp(ptMouse) )
	{
		g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_GROUP, _YESNO, g_xMsg.GetMsg(1606), TRUE, -1, -1, CM_DELGROUPMEMBER);

		return FALSE;
	}

	if ( m_xGroupBtn[_BTN_ID_GROUPICON].OnLButtonUp(ptMouse) )
	{
		(m_bAllowGroup ? m_bAllowGroup = FALSE : m_bAllowGroup = TRUE);
		g_xClientSocket.SendGroupMode(m_bAllowGroup);

		DWORD dwFont = GetChatColor(_CHAT_COLOR3);
		DWORD dwBack = GetChatColor(_CHAT_COLOR8);

		if ( m_bAllowGroup )
		{
			g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2157));
			g_xGameProc.m_xInterface.m_xOptionWnd.m_xOptionBtn[_BTN_ID_ALLOWGROUP].ResetGameBtn(297, 297, -1);
			m_xGroupBtn[_BTN_ID_GROUPICON].ResetGameBtn(177, 177, 177);
		}
		else
		{
			g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2158));
			g_xGameProc.m_xInterface.m_xOptionWnd.m_xOptionBtn[_BTN_ID_ALLOWGROUP].ResetGameBtn(301, 301, 299);
			m_xGroupBtn[_BTN_ID_GROUPICON].ResetGameBtn(178, 178, 178);
		}

		return FALSE;
	}

	return FALSE;
}

BOOL CGroupWnd::OnLButtonDown(POINT ptMouse)
{
	INT nCnt;

	for ( nCnt = 0; nCnt < _MAX_GROUP_BTN; nCnt++ )
	{
		if ( m_xGroupBtn[nCnt].OnLButtonDown(ptMouse) )
		{
			return TRUE;
		}
	}

	return FALSE;
}

VOID CGroupWnd::OnMouseMove(POINT ptMouse)
{
	INT nCnt;

	for ( nCnt = 0; nCnt < _MAX_GROUP_BTN; nCnt++ )
	{
		m_xGroupBtn[nCnt].OnMouseMove(ptMouse);
	}
}

VOID CGroupWnd::SetStatusBtnInit()
{
	INT nCnt;

	for ( nCnt = 0; nCnt < _MAX_GROUP_BTN; nCnt++ )
	{
		m_xGroupBtn[nCnt].SetBtnState(_BTN_STATE_NORMAL);
	}
}


LRESULT CGroupWnd::OnMsgBoxReturn(WPARAM wParam, LPARAM lParam)
{
	BYTE	bMsgReturn;
	WORD	wPacket;

	bMsgReturn	= LOBYTE(HIWORD(wParam));
	wPacket		= LOWORD(wParam);

	if ( wPacket == CM_CREATEGROUP && bMsgReturn == _BTN_YES )
	{
		g_xClientSocket.SendCreateGroup((CHAR*)lParam);
	}
	else if ( wPacket == CM_ADDGROUPMEMBER && bMsgReturn == _BTN_YES )
	{
		g_xClientSocket.SendAddGroupMember((CHAR*)lParam);
	}
	else if ( wPacket == CM_DELGROUPMEMBER && bMsgReturn == _BTN_YES )
	{
		g_xClientSocket.SendDelGroupMember((CHAR*)lParam);
	}

	return 0L;
}

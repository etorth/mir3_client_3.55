/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/

#include "StdAfx.h"

typedef struct tagINTERFACE_BUTTON
{
public:
	int		m_nLeft;
	int		m_nTop;
	int		m_nWidth;
	int		m_nHeight;
	INT		m_btCommand;
} INTERFACE_BUTTON;

#define GROUPBTN_ALLOWGROUP		1
#define GROUPBTN_CREATEGROUP	2
#define GROUPBTN_ADDMEMBER		3
#define GROUPBTN_DELMEMBER		4

INTERFACE_BUTTON GroupWndButton[] = {	{ 24,	45,		24,		24, GROUPBTN_ALLOWGROUP },
										{ 40,	190,	36,		33, GROUPBTN_CREATEGROUP }, 
										{ 100,	190,	36,		33, GROUPBTN_ADDMEMBER }, 
										{ 160,	190,	36,		33, GROUPBTN_DELMEMBER } 
									};

BOOL g_fAllowGroup = TRUE;

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
	CreateGameWnd(nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight, -126, -8);

	m_xButton[0].CreateGameBtn(pxWndImage,  1371-g_fAllowGroup,  1371-g_fAllowGroup, GroupWndButton[0].m_nLeft, GroupWndButton[0].m_nTop);
	m_xButton[1].CreateGameBtn(pxWndImage,  1362,  1363, GroupWndButton[1].m_nLeft, GroupWndButton[1].m_nTop);
	m_xButton[2].CreateGameBtn(pxWndImage,  1365,  1366, GroupWndButton[2].m_nLeft, GroupWndButton[2].m_nTop);
	m_xButton[3].CreateGameBtn(pxWndImage,  1368,  1369, GroupWndButton[3].m_nLeft, GroupWndButton[3].m_nTop);
	m_xButtonClose.CreateGameBtn(pxWndImage,  1221,  1221, 213, 202);

	m_xSelectCharWnd.CreateSelectCharWnd( 100, pxWndImage, 1248, 0, 0, 0, 0, TRUE );
}

VOID CGroupWnd::ShowGroupWnd()
{
	CGroupMember*	pGroupMember;

	RECT tRect = GetGameWndRect();

	int				nX = tRect.left + 45, nY = tRect.top + 100;
	
	ShowGameWnd();

	g_xMainWnd.PutsHan(NULL, tRect.left + 45, tRect.top + 25, RGB(255, 255, 255), RGB(0, 0, 0), g_szUserID, NULL);

	if (m_xGroupList.GetCounter())
	{
		m_xGroupList.MoveCurrentToTop();

		for (int i = 1; i <= m_xGroupList.GetCounter(); i++)
		{
			pGroupMember = m_xGroupList.GetCurrentData();

			g_xMainWnd.PutsHan(NULL, nX, nY, RGB(255, 255, 255), RGB(0, 0, 0), pGroupMember->szMemberName);

			if (i % 2) 
				nX += 100;
			else
			{
				nX -= 100;
				nY += 50;
			}

			m_xGroupList.MoveNextNode();
		}
	}

	//鞫刻BUTTOM
	for(int i = 0; i < 4; i++)
		m_xButton[i].ShowGameBtn();

	if( m_xSelectCharWnd.m_bActive )
		m_xSelectCharWnd.ShowSelectCharWnd();

}

VOID CGroupWnd::Init()
{
	CGameWnd::Init();
	m_xSelectCharWnd.Init();
}

VOID CGroupWnd::Destroy()
{
	m_xSelectCharWnd.Destroy();
	CGameWnd::Destroy();
}

BOOL CGroupWnd::OnLButtonUp(POINT ptMouse)
{
	if( m_xSelectCharWnd.m_bActive )
	{
		m_xSelectCharWnd.OnLButtonUp(ptMouse);
		return FALSE;
	}

	RECT tRect = GetGameWndRect();

	if( m_xButtonClose.OnLButtonUp(ptMouse) )
		return TRUE;

	for(int i = 0; i < 4; i++)
		m_xButton[i].OnLButtonUp(ptMouse);

	for (int i = 0; i < sizeof(GroupWndButton)/sizeof(INTERFACE_BUTTON); i++)
	{
		if (tRect.left + GroupWndButton[i].m_nLeft < ptMouse.x && tRect.left + GroupWndButton[i].m_nLeft + GroupWndButton[i].m_nWidth > ptMouse.x &&
			tRect.top + GroupWndButton[i].m_nTop < ptMouse.y && tRect.top + GroupWndButton[i].m_nTop + GroupWndButton[i].m_nHeight > ptMouse.y)
		{
			switch (GroupWndButton[i].m_btCommand)
			{
				case GROUPBTN_ALLOWGROUP:
					(g_fAllowGroup ? g_fAllowGroup = FALSE : g_fAllowGroup = TRUE);
					m_xButton[0].ResetGameBtn( 1371-g_fAllowGroup, 1371-g_fAllowGroup);
					g_xGameProc.m_pSocket->SendGroupMode(g_fAllowGroup);
					break;
				case GROUPBTN_CREATEGROUP:
					m_xSelectCharWnd.ShowAddChar();
					m_xSelectCharWnd.SetCommand(0);
					break;
				case GROUPBTN_ADDMEMBER:
					m_xSelectCharWnd.ShowAddChar();
					m_xSelectCharWnd.SetCommand(1);
					break;
				case GROUPBTN_DELMEMBER:
					m_xSelectCharWnd.ShowDelChar();
					m_xSelectCharWnd.SetCommand(2);
					break;
			}
		}
	}

	return FALSE;
}

BOOL CGroupWnd::OnLButtonDown(POINT ptMouse)
{
	if( m_xSelectCharWnd.m_bActive )
	{
		m_xSelectCharWnd.OnLButtonDown(ptMouse);
		return FALSE;
	}

	for(int i = 0; i < 4; i++)
		m_xButton[i].OnLButtonDown(ptMouse);

	return FALSE;
}

VOID CGroupWnd::OnMouseMove(POINT ptMouse)
{
	if( m_xSelectCharWnd.m_bActive )
	{
		m_xSelectCharWnd.OnMouseMove(ptMouse);
	}

	m_xButtonClose.ChangeRect(m_rcWnd.left+213, m_rcWnd.top+202);

	for(int i = 0; i < 4; i++)
		m_xButton[i].ChangeRect(m_rcWnd.left+GroupWndButton[i].m_nLeft, m_rcWnd.top+GroupWndButton[i].m_nTop);

	for(int i = 0; i < 4; i++)
		m_xButton[i].OnMouseMove(ptMouse);

}



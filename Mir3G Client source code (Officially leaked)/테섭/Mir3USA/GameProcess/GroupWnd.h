#ifndef _CGROUPWND_H
#define _CGROUPWND_H

class CGroupMember
{
public:
	char		szMemberName[32];
};

class CGroupWnd : public CGameWnd
{ 
public:
	CList<CGroupMember>		m_xGroupList;

	CGameBtn				m_xGroupBtn[_MAX_GROUP_BTN];

	BOOL					m_bAllowGroup;

public:
	CGroupWnd();
	~CGroupWnd();
	virtual VOID Init();
	virtual VOID Destroy();

	VOID	CreateGroupWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove);
	VOID	ShowGroupWnd();

public:
//  메시지 함수.
	BOOL	OnLButtonDown(POINT ptMouse);
	BOOL	OnLButtonUp(POINT ptMouse);
	VOID	OnMouseMove(POINT ptMouse);

	VOID	OnScrollDown();
	VOID	OnScrollUp();
	LRESULT OnMsgBoxReturn(WPARAM wParam, LPARAM lParam);

//	BOOL	bIsMyGroup(CHAR* pszName);

	VOID SetStatusBtnInit();
};

#endif // _CGROUPWND_H
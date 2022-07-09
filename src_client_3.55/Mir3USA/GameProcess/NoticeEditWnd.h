#ifndef _NOTICEEDITWND_H
#define _NOTICEEDITWND_H


class CNoticEditWnd : public CGameWnd
{ 
private:
protected:
	CGameBtn				m_xNoticeBtn[_MAX_NOTICE_BTN];

public:
	CNoticEditWnd();
	~CNoticEditWnd();

	RECT	m_rcEditBox;

	HWND	m_hNoticeEdit;

	BYTE	m_bType;

	virtual VOID Init();
	virtual VOID Destroy();

	VOID	CreateNoticeWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend);
	VOID	ShowNoticeWnd();

	inline VOID	SetEditType(BYTE bType)		// Type == 1 : 공지수정. Type == 0 : 직위수정.
	{
		if ( bType == 0 )
		{
			m_bType = bType;
			ResetWndImg(_WNDIMGIDX_RANKEDIT, m_rcWnd.left, m_rcWnd.top, m_nWidth, m_nHeight);
		}
		else
		{
			m_bType = 1;
			ResetWndImg(_WNDIMGIDX_NOTICEEDIT, m_rcWnd.left, m_rcWnd.top, m_nWidth, m_nHeight);
		}
	}

	VOID	SetStatusBtnInit();

public:
//  메시지 함수.
	BOOL	OnLButtonDown(POINT ptMouse);
	BOOL	OnLButtonUp(POINT ptMouse);
	VOID	OnMouseMove(POINT ptMouse);
};


#endif // _NOTICEEDITWND_H
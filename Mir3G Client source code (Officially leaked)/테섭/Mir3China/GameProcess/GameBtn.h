#ifndef _CGAMEBTN_H
#define _CGAMEBTN_H

class CGameBtn
{ 
public:
	RECT			m_rcBtn;

	CWHWilImageData* m_pxBtnImage;
	INT				m_nFocusImgIdx;			// 이미지 관련 변수들. 
	INT				m_nClickImgIdx;			
	INT				m_nNormalImgIdx;		// 이미지 관련 변수들. 

	BYTE			m_bBtnType;				// 0 : 포커스 상태를 가지지 않는다. 1: 포커스 있음.
	BYTE			m_bBtnState;			// 0 : 그대로... 1: 마우스 포커스상태. 2: 마우스 클릭상태.

	INT				m_nDrawSX;
	INT				m_nDrawSY;

	BOOL			m_bUseFocus;

	char			m_szToolTip[128];		

	void			DrawToolTip();
public:
	__inline RECT GetGameBtnRect()
	{
		return m_rcBtn;
	}
	__inline VOID SetGameBtnRect(INT nSX, INT nSY, INT nEX, INT nEY)
	{
		SetRect(&m_rcBtn, nSX, nSY, nEX, nEY);
	}
	__inline VOID SetBtnState(BYTE bState)
	{
		m_bBtnState = bState;
		if ( m_bBtnType == _BTN_TYPE_NOFOCUS && m_bBtnState == _BTN_STATE_FOCUS )
		{
			m_bBtnState = _BTN_STATE_NORMAL;
		}
	}
	__inline BYTE GetGameBtnState()
	{
		return m_bBtnState;
	}

	__inline CGameBtn()	
	{ 
		Init();
	}

	virtual ~CGameBtn()
	{
		Destroy();
	}

	VOID			Init();
	VOID			Destroy();

	VOID			ChangeRect(INT nStartX, INT nStartY);
	VOID			CreateGameBtn(CWHWilImageData* pxBtnImage, INT nFocusImgIdx, INT nClickImgIdx, 
								   INT nStartX, INT nStartY, CHAR *pszTooltip = NULL, BYTE bBtnType = _BTN_TYPE_FOCUS, 
								   INT nNormalImgIdx = -1, BOOL bUseFocus = FALSE);
	virtual VOID	ShowGameBtn();

	VOID			ResetGameBtn(INT nFocusImgIdx, INT nClickImgIdx, INT nNormalImgIdx = -1);
	VOID			ChangeBtnTooltip(CHAR *pszTooltip);
	
	virtual VOID	OnMouseMove(POINT ptMouse);
	virtual BOOL	OnLButtonDown(POINT ptMouse);
	virtual BOOL	OnLButtonUp(POINT ptMouse, BOOL bUseSound = TRUE);
};



class CMsgBoxBtn : public CGameBtn
{
public:
	CMsgBoxBtn();
	~CMsgBoxBtn();
	virtual VOID ShowGameBtn();
};



class CScrlBar
{
public:
	CScrlBar();
	virtual ~CScrlBar();

public:
	CWHWilImageData*	m_pxScrlImage;		// 스크롤바 이미지파일 포인터.
	INT					m_nScrlImgIdx;		// 스크롤바 이미지.

	FLOAT				m_fScrlRate;		// 0.0f~1.0f사이. 스크롤바의 비율.
	FLOAT				m_fPageRate;		

	INT					m_nPageLine;

	BOOL				m_bGrapsed;			// 스크롤 버튼영역에서 Mouse LButtonDown에 의해서 눌려진상태인지를 판단한다.

	WORD				m_wScrlWidth;
	WORD				m_wScrlHeight;

	WORD				m_wScrlBtnLength;

	RECT				m_rcScrlRgn;		// 스크롤바의 영역.
	RECT				m_rcScrlBtnRgn;		// 스크롤바에서 버튼의 영역.

	DWORD				m_dwTick;

	BOOL				mScrlbar_bType;

	__inline FLOAT GetScrlRate()
	{
		return m_fScrlRate;
	}

	__inline VOID Init()
	{
		m_pxScrlImage		= NULL;
		m_nScrlImgIdx		= 0;

		m_fPageRate			= 0.0f;
		m_fScrlRate			= 0.0f;

		m_nPageLine			= 0;

		m_bGrapsed			= FALSE;

		m_wScrlWidth		= 0;
		m_wScrlHeight		= 0;

		m_wScrlBtnLength	= 0;

		SetRect(&m_rcScrlRgn, 0, 0, 0, 0);
		SetRect(&m_rcScrlBtnRgn, 0, 0, 0, 0);
	}

	VOID	CreateScrlBar(CWHWilImageData* pxImage, INT ImgIdx, INT nPageLine, WORD wScrlWidth, WORD wScrlHeight, WORD wScrlBtnLength, BOOL bType = SCR_TYPE_VERTICAL);
	VOID	ShowScrlBar(INT nX, INT nY, INT nFstPos, INT nCounter);
	BOOL	OnMouseMove(POINT ptMouse);
	BOOL	OnLButtonDown(POINT ptMouse);
	BOOL	OnLButtonUp(POINT ptMouse);
};



#endif // _CGAMEBTN_H
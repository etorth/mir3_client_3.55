#ifndef _CGAMEBTN_H
#define _CGAMEBTN_H

class CGameBtn
{ 
public:
	RECT			m_rcBtn;

	CWHWilImageData* m_pxBtnImage;
	INT				m_nFocusImgIdx;			// �̹��� ���� ������. 
	INT				m_nClickImgIdx;			
	INT				m_nNormalImgIdx;		// �̹��� ���� ������. 

	BYTE			m_bBtnType;				// 0 : ��Ŀ�� ���¸� ������ �ʴ´�. 1: ��Ŀ�� ����.
	BYTE			m_bBtnState;			// 0 : �״��... 1: ���콺 ��Ŀ������. 2: ���콺 Ŭ������.

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
	CWHWilImageData*	m_pxScrlImage;		// ��ũ�ѹ� �̹������� ������.
	INT					m_nScrlImgIdx;		// ��ũ�ѹ� �̹���.

	FLOAT				m_fScrlRate;		// 0.0f~1.0f����. ��ũ�ѹ��� ����.
	FLOAT				m_fPageRate;		

	INT					m_nPageLine;

	BOOL				m_bGrapsed;			// ��ũ�� ��ư�������� Mouse LButtonDown�� ���ؼ� ���������������� �Ǵ��Ѵ�.

	WORD				m_wScrlWidth;
	WORD				m_wScrlHeight;

	WORD				m_wScrlBtnLength;

	RECT				m_rcScrlRgn;		// ��ũ�ѹ��� ����.
	RECT				m_rcScrlBtnRgn;		// ��ũ�ѹٿ��� ��ư�� ����.

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
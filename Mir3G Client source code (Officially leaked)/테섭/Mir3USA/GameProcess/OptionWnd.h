#ifndef _COPTIONWND_H
#define _COPTIONWND_H


class COptionWnd : public CGameWnd
{ 
/* Constructor & Destructor */
public:
	COptionWnd();
	~COptionWnd();

/* Attributes */
public:

	BOOL					m_bBGMON;
	BOOL					m_bEffectON;
	BOOL					m_bEnvirON;
	BOOL					m_bShadowON;
	BOOL					m_bReversePanON;
	BOOL					mOptionWnd_bMoveBgmVolBtn;
	BOOL					mOptionWnd_bMoveWaveVolBtn;
	BOOL					mOptionWnd_bShowMonInMap;
	BOOL					mOptionWnd_bRevival;
	BOOL					mOptionWnd_bChunjihapil;
	BOOL					mOptionWnd_bExchangeMode;
	BOOL					mOptionWnd_bWhisperMode;
	BOOL					mOptionWnd_bGuildwhisperMode;
	BOOL					mOptionWnd_bGuildJoinMode;
	BOOL					mOptionWnd_bShoutMode;
	BOOL					mOptionWnd_bAllowGroup;
	BOOL					mOptionWnd_bShowHealthbar;
	BOOL					mOptionWnd_bWholeShoutMode;
	
	INT						mOptionWnd_nAttackMode;

	

	POINT					mOptionWnd_ptBgmVolBtn;
	POINT					mOptionWnd_ptWaveVolBtn;

	CGameBtn				m_xOptionBtn[_MAX_OPTION_BTN];

	INT						mOptionWnd_nMode;

	RECT					mOptionWnd_rcBasicTab;
	RECT					mOptionWnd_rcAllowTab;
	RECT					mOptionWnd_rcChatTab;
	RECT					mOptionWnd_rcVisualTab;

protected:
	

/* Operation */
public:
	virtual	VOID			Init();
	virtual VOID			Destroy();

	VOID					CreateOptionWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend);
	VOID					ShowOptionWnd();
	VOID					SetIniFile();
	VOID					SetOptions();
	VOID					SetStatusBtnInit();
	VOID					OptionWndSetVolume(BOOL	bIsBgm);

	VOID					OptionChanged(INT nRecog, WORD wParam);

	VOID					ShowBasicSet();
	VOID					ShowAllowSet();
	VOID					ShowChatSet();
	VOID					ShowVisualSet();

//  메시지 함수.
	BOOL					OnLButtonDown(POINT ptMouse);
	BOOL					OnLButtonUp(POINT ptMouse);
	VOID					OnMouseMove(POINT ptMouse);
};


#endif // _COPTIONWND_H
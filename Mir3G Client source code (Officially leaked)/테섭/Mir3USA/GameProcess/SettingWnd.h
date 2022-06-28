#ifndef _SETTINGWND_H
#define _SETTINGWND_H

class CSettingWnd : public CGameWnd
{ 
// Constructor & Destructor
public:
	CSettingWnd();
	~CSettingWnd();
// Attributes
public:
	CGameBtn			mSetting_BtnClose;
	CGameBtn			mSetting_BtnChatSize;
	CGameBtn			mSetting_BtnMessenger;
	CGameBtn			mSetting_BtnGroup;
	CGameBtn			mSetting_BtnGuild;
	CGameBtn			mSetting_BtnUserpic;
	CGameBtn			mSetting_BtnOption;
	CGameBtn			mSetting_BtnSiege;
	CGameBtn			mSetting_BtnExit;
	CGameBtn			mSetting_BtnUtil;


// Operations
public:
	virtual VOID Init();
	virtual VOID Destroy();

	VOID	CreateSettingWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend);
	VOID	ShowSettingWnd();

	BOOL	OnLButtonDown(POINT ptMouse);
	BOOL	OnLButtonUp(POINT ptMouse);
	BOOL	OnMouseMove(POINT ptMouse);
};



#endif // _MESSENGERWND_H
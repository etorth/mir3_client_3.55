#ifndef _MAGICSHORTCUTWND_H
#define _MAGICSHORTCUTWND_H


class CMagicShortcutWnd : public CGameWnd
{ 
public:
	INT		mMSCutwnd_nTabNum;


	INT		mMSCutwnd_nMagicNum[4][12];			//12개 단축키 네 개 셋트

	RECT	mMSCutwnd_rcTab[4];

	INT		mMSCutwnd_nShowMagicNum;

public:
	CMagicShortcutWnd();
	~CMagicShortcutWnd();

	virtual VOID Init();
	virtual VOID Destroy();

	VOID	CreateMagicShortcutWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend);
	VOID	ShowMagicShortcutWnd();

public:
	BOOL	OnLButtonDown(POINT ptMouse);
	BOOL	OnLButtonUp(POINT ptMouse);

	BOOL	OnRButtonDown(POINT ptMouse);

	BOOL	OnMouseMove(POINT ptMouse);

	VOID	SetMagicIcon(INT nMagicID, INT nShortKey);
	INT		GetMagicIDByKey(INT nKey);

	BOOL	SaveMagicKeySet();
	BOOL	LoadMagicKeySet();
};



#endif // _MAGICSHORTCUTWND_H
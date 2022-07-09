#ifndef _CGAMEOVERWND_H
#define _CGAMEOVERWND_H


class CGameOver: public CGameWnd
{ 
private:
protected:
	CGameBtn				mGameOver_BtnClose;
	CGameBtn				mGameOver_BtnLogout;
	CGameBtn				mGameOver_BtnExit;

public:
	CGameOver();
	~CGameOver();

	virtual VOID Init();
	virtual VOID Destroy();

	VOID	CreateGameOverWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend);
	VOID	ShowGameOver();

public:
//  메시지 함수.
	BOOL	OnLButtonDown(POINT ptMouse);
	BOOL	OnLButtonUp(POINT ptMouse);
	VOID	OnMouseMove(POINT ptMouse);
};


#endif // _CGAMEOVERWND_H
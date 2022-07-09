#ifndef _CGAMEWND_H
#define _CGAMEWND_H


class CGameWnd
{ 
public:
	INT				m_nID;					// 윈도우 관리자가 이윈도우를 구분할 식별자.
	RECT			m_rcImgWnd;				// 윈도우의 이미지의영역. 
	RECT			m_rcWnd;				// 윈도우의 화면영역. 

	INT				 m_nFrameImgIdx;		// 이미지 관련 변수들. 
	CWHWilImageData* m_pxWndImage;

	BOOL			m_bActive;				// 윈도우 활성화 여부. 
	BOOL			m_bFocused; 
	BOOL			m_bMoving;				// 윈도우 움직이는지의 여부.
	BOOL			m_bCanMove;				// 윈도우 고정여부.

	INT				m_nWidth;
	INT				m_nHeight;

	POINT			m_bGrabbedMousePos;

// ////////////////////인터페이스 블렌드관련.
	BYTE			m_bBright;
	BYTE			m_bOpa;
	__inline VOID SetBlend(BYTE bBlend)
	{
		switch ( bBlend )
		{
		case 0:
			m_bBright = 150;
			m_bOpa	  = 150;
			break;
		case 1:
			m_bBright = 180;
			m_bOpa	  = 180;
			break;
		case 2:
			m_bBright = 210;
			m_bOpa	  = 210;
			break;
		case 3:
			m_bBright = 255;
			m_bOpa	  = 255;
			break;
		}
	}

public:
	__inline RECT GetGameWndRect()
	{
		return m_rcWnd;
	}
	__inline BOOL GetGameWndActive()
	{
		return m_bActive;
	}

	__inline CGameWnd()	
	{ 
		Init();
	}

	virtual ~CGameWnd()
	{
		Destroy();
	}

	virtual VOID Init();
	virtual VOID Destroy();
	virtual VOID ShowGameWnd(INT nIdx = 0);
	virtual VOID SetGameWndActive(BOOL bActive);

	VOID ResetWndImg(INT nIdx, INT nStartX, INT nStartY, INT nWidth = 0, INT nHeight = 0);
	VOID CreateGameWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, BOOL bCanMove, INT nStartX, INT nStartY, INT nWidth = 0, INT nHeight = 0, BYTE bBlend = 1);
	VOID DestroyGameWnd();
	VOID SetGameWndFocused(BOOL bFocused);
	VOID SetReadyMove(POINT ptMouse);
	VOID MoveGameWnd(POINT ptMouse, BOOL bForceMove = FALSE);
};


#endif // _CGAMEWND_H
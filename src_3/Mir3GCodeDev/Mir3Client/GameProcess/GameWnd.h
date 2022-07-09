#ifndef _CGAMEWND_H
#define _CGAMEWND_H


class CGameWnd
{ 
public:
	INT				m_nID;					// ������ �����ڰ� �������츦 ������ �ĺ���.
	RECT			m_rcImgWnd;				// �������� �̹����ǿ���. 
	RECT			m_rcWnd;				// �������� ȭ�鿵��. 

	INT				 m_nFrameImgIdx;		// �̹��� ���� ������. 
	CWHWilImageData* m_pxWndImage;

	BOOL			m_bActive;				// ������ Ȱ��ȭ ����. 
	BOOL			m_bFocused; 
	BOOL			m_bMoving;				// ������ �����̴����� ����.
	BOOL			m_bCanMove;				// ������ ��������.

	INT				m_nWidth;
	INT				m_nHeight;

	POINT			m_bGrabbedMousePos;

// ////////////////////�������̽� �������.
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
#ifndef _FACEIMGUPWND_H
#define _FACEIMGUPWND_H




class CFaceImgUpWnd : public CGameWnd
{ 
// Constructor & Destructor
public:
	CFaceImgUpWnd();
	~CFaceImgUpWnd();
// Attributes
public:
	CGameBtn				mFaceImgUP_BtnClose;			// �ݱ�
	CGameBtn				mFaceImgUP_BtnUpload;			// ���õ� ���� �ø���
	CGameBtn				mFaceImgUP_BtnReset;			// ��ϵ� ���� ����

	CScrlBar				mFaceImgUP_xReceiveScrBar;

	CList<CHAT>				mFaceImgUP_xFineName;			// ���� ����


	INT						mFaceImgUP_nMouseLacated;
	INT						mFaceImgUP_nSelected;

	INT						mFaceImgUP_nStartLine;
	INT						mFaceImgUP_nMaxLine;

	WORD					*mFaceImgUP_wpFaceImg;
	CWHSurface				m_hbmUserFace;

	RECT					mFaceImgUP_rcCell[11];

	CHAR					mFaceImgUP_szSelectedFileName[MAX_PATH];

	BOOL					mFaceImgUP_bLoadSuccess;

	DWORD					mFaceImgUP_dwTimer;

// Operations
public:
	virtual VOID Init();
	virtual VOID Destroy();

	VOID	CreateFaceImgUpWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend);
	VOID	ShowFaceImgUpWnd();

	BOOL	OnLButtonDown(POINT ptMouse);
	BOOL	OnLButtonUp(POINT ptMouse);

	BOOL	OnRButtonDown(POINT ptMouse);
	BOOL	OnMouseMove(POINT ptMouse);

	BOOL	OnLButtonDoubleClick(POINT ptMouse);

	VOID	OnScrollDown();
	VOID	OnScrollUp();

	VOID	CloseFaceImgUpWnd();

	VOID	FindJPGFile();
};



#endif // _FACEIMGUPWND_H
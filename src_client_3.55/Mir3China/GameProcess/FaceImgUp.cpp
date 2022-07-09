/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"


CFaceImgUpWnd::CFaceImgUpWnd()
{
	Init();
}

CFaceImgUpWnd::~CFaceImgUpWnd()
{
	Destroy();
}

VOID CFaceImgUpWnd::Init()
{
	CGameWnd::Init();

	mFaceImgUP_xReceiveScrBar.Init();

	for (INT nI=0; nI<12; nI++ )
	{
		SetRect(&mFaceImgUP_rcCell[nI], 0, 0, 0, 0);
	}

	mFaceImgUP_xFineName.ClearAll();

	mFaceImgUP_nMouseLacated = -1;
	mFaceImgUP_nSelected = -1;
	mFaceImgUP_nStartLine = 0;
	mFaceImgUP_nMaxLine = 0;

	mFaceImgUP_dwTimer = 0;

	mFaceImgUP_bLoadSuccess = FALSE;
	
	ZeroMemory(mFaceImgUP_szSelectedFileName, MAX_PATH);
}

VOID CFaceImgUpWnd::Destroy()
{
	CloseFaceImgUpWnd();

	CGameWnd::Destroy();
}

VOID CFaceImgUpWnd::CreateFaceImgUpWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend)
{
	CreateGameWnd(nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight, bBlend);

	mFaceImgUP_BtnClose.CreateGameBtn(pxWndImage, 1221, 1222, nStartX+400, nStartY+267, g_xMsg.GetMsg(1052), _BTN_TYPE_FOCUS, 1221, TRUE);
	mFaceImgUP_BtnUpload.CreateGameBtn(pxWndImage, 681, 682, nStartX+59, nStartY+345, g_xMsg.GetMsg(4700), _BTN_TYPE_FOCUS, -1, FALSE);
	mFaceImgUP_BtnReset.CreateGameBtn(pxWndImage, 683, 684, nStartX+179, nStartY+345, g_xMsg.GetMsg(4701), _BTN_TYPE_FOCUS, -1, FALSE);

	mFaceImgUP_xReceiveScrBar.CreateScrlBar(pxWndImage, 1225, _CELL_IN_FACEUP, 12, 260, 14);
}	
		
VOID CFaceImgUpWnd::ShowFaceImgUpWnd()
{
	mFaceImgUP_BtnClose.ChangeRect(m_rcWnd.left+533, m_rcWnd.top+355);
	mFaceImgUP_BtnUpload.ChangeRect(m_rcWnd.left+154, m_rcWnd.top+355);
	mFaceImgUP_BtnReset.ChangeRect(m_rcWnd.left+214, m_rcWnd.top+355);

	ShowGameWnd();

	for (INT nI=0; nI<12; nI++ )
	{
		SetRect(&mFaceImgUP_rcCell[nI], m_rcWnd.left + 26, m_rcWnd.top + 22 + 24*nI, m_rcWnd.left + 264, m_rcWnd.top + 41 + 24*nI);
//		g_xMainWnd.DrawWithGDI(&mFaceImgUP_rcCell[nI], NULL, RGB(200, 200, 200), 1);
	}

	mFaceImgUP_xReceiveScrBar.ShowScrlBar(m_rcWnd.left+273, m_rcWnd.top+30, mFaceImgUP_nStartLine, mFaceImgUP_xFineName.GetCount());

	// 마우스 있는 곳 뒷판
	if ( mFaceImgUP_nMouseLacated != -1 )
	{
		D3DMATERIAL7 mtrl;
		D3DVECTOR	 vecTrans((FLOAT)mFaceImgUP_rcCell[mFaceImgUP_nMouseLacated].left, (FLOAT)mFaceImgUP_rcCell[mFaceImgUP_nMouseLacated].top, 0);
		D3DVECTOR	 vecScale((FLOAT)mFaceImgUP_rcCell[mFaceImgUP_nMouseLacated].right-mFaceImgUP_rcCell[mFaceImgUP_nMouseLacated].left, 
			mFaceImgUP_rcCell[mFaceImgUP_nMouseLacated].bottom-mFaceImgUP_rcCell[mFaceImgUP_nMouseLacated].top, 1);

		D3DUtil_InitMaterial(mtrl, (FLOAT)90/255.0f, (FLOAT)90/255.0f, (FLOAT)90/255.0f);
		mtrl.diffuse.a = 180.0f/255.0f;
		g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
	}

	if ( mFaceImgUP_nSelected != -1 && mFaceImgUP_nSelected-mFaceImgUP_nStartLine >= 0 && mFaceImgUP_nSelected-mFaceImgUP_nStartLine < 12)
	{
		D3DMATERIAL7 mtrl;
		D3DVECTOR	 vecTrans((FLOAT)mFaceImgUP_rcCell[mFaceImgUP_nSelected-mFaceImgUP_nStartLine].left, (FLOAT)mFaceImgUP_rcCell[mFaceImgUP_nSelected-mFaceImgUP_nStartLine].top, 0);
		D3DVECTOR	 vecScale((FLOAT)mFaceImgUP_rcCell[mFaceImgUP_nSelected-mFaceImgUP_nStartLine].right-mFaceImgUP_rcCell[mFaceImgUP_nSelected-mFaceImgUP_nStartLine].left, 
			mFaceImgUP_rcCell[mFaceImgUP_nSelected-mFaceImgUP_nStartLine].bottom-mFaceImgUP_rcCell[mFaceImgUP_nSelected-mFaceImgUP_nStartLine].top, 1);

		D3DUtil_InitMaterial(mtrl, (FLOAT)95/255.0f, (FLOAT)114/255.0f, (FLOAT)120/255.0f);
		mtrl.diffuse.a = 180.0f/255.0f;
		g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
	}

	RECT rcTitle = {m_rcWnd.left + 320 , m_rcWnd.top + 158, m_rcWnd.left + 550, m_rcWnd.top + 173};
	g_xMainWnd.PutsHan(NULL, rcTitle.left, rcTitle.top, RGB(250, 250, 250), 0, g_xMsg.GetMsg(4702));
	rcTitle.top += 15;
	rcTitle.bottom += 15;
	g_xMainWnd.PutsHan(NULL, rcTitle.left, rcTitle.top, RGB(250, 250, 250), 0, g_xMsg.GetMsg(4703));
	rcTitle.top += 15;
	rcTitle.bottom += 15;
	g_xMainWnd.PutsHan(NULL, rcTitle.left, rcTitle.top, RGB(250, 250, 250), 0, g_xMsg.GetMsg(4704));
	rcTitle.top += 15;
	rcTitle.bottom += 15;
	g_xMainWnd.PutsHan(NULL, rcTitle.left, rcTitle.top, RGB(250, 250, 250), 0, g_xMsg.GetMsg(4705));
	rcTitle.top += 15;
	rcTitle.bottom += 15;
	g_xMainWnd.PutsHan(NULL, rcTitle.left, rcTitle.top, RGB(250, 250, 250), 0, g_xMsg.GetMsg(4706));
	rcTitle.top += 15;
	rcTitle.bottom += 15;
	g_xMainWnd.PutsHan(NULL, rcTitle.left, rcTitle.top, RGB(250, 250, 250), 0, g_xMsg.GetMsg(4707));
	rcTitle.top += 15;
	rcTitle.bottom += 15;
	g_xMainWnd.PutsHan(NULL, rcTitle.left, rcTitle.top, RGB(250, 250, 250), 0, g_xMsg.GetMsg(4708));
	rcTitle.top += 15;
	rcTitle.bottom += 15;
	g_xMainWnd.PutsHan(NULL, rcTitle.left, rcTitle.top, RGB(250, 250, 250), 0, g_xMsg.GetMsg(4709));
	rcTitle.top += 15;
	rcTitle.bottom += 15;
	g_xMainWnd.PutsHan(NULL, rcTitle.left, rcTitle.top, RGB(250, 250, 250), 0, g_xMsg.GetMsg(4710));
	rcTitle.top += 15;
	rcTitle.bottom += 15;
	g_xMainWnd.PutsHan(NULL, rcTitle.left, rcTitle.top, RGB(250, 250, 250), 0, g_xMsg.GetMsg(4711));
	rcTitle.top += 15;
	rcTitle.bottom += 15;
	g_xMainWnd.PutsHan(NULL, rcTitle.left, rcTitle.top, RGB(250, 250, 250), 0, g_xMsg.GetMsg(4712));
	rcTitle.top += 15;
	rcTitle.bottom += 15;
	g_xMainWnd.PutsHan(NULL, rcTitle.left, rcTitle.top, RGB(250, 250, 250), 0, g_xMsg.GetMsg(4713));


	CListNode < CHAT > *pNode;
	INT  nLine, nListCnt;

	LPCHAT	pstChat = NULL;

	for ( pNode = mFaceImgUP_xFineName.GetHead(), nListCnt = 0, nLine = 0; pNode; pNode = pNode->GetNext(), nListCnt++ )
	{
		pstChat = pNode->GetData();

		if ( nListCnt < mFaceImgUP_nStartLine || nListCnt > mFaceImgUP_nStartLine + 11 )
			continue;

		if ( pstChat == NULL )
			return ;

		g_xMainWnd.PutsHan(NULL, mFaceImgUP_rcCell[nListCnt-mFaceImgUP_nStartLine].left, mFaceImgUP_rcCell[nListCnt-mFaceImgUP_nStartLine].top + 5, RGB( 250,  250,  250), 0, pstChat->pszChat);

	}

	if ( mFaceImgUP_nSelected != -1 )
	{
		if ( mFaceImgUP_bLoadSuccess )
		{
			RECT rc = {m_rcWnd.left+391, m_rcWnd.top+30, m_rcWnd.left+391+85, m_rcWnd.top+30+104};
			m_hbmUserFace.Draw(g_xMainWnd.GetBackBuffer(), &rc);
		}
	}

	mFaceImgUP_BtnClose.ShowGameBtn();
	mFaceImgUP_BtnUpload.ShowGameBtn();
	mFaceImgUP_BtnReset.ShowGameBtn();
}


BOOL CFaceImgUpWnd::OnLButtonUp(POINT ptMouse)
{
	//공통
	if ( mFaceImgUP_BtnClose.OnLButtonUp(ptMouse) )
	{
		CloseFaceImgUpWnd();
		return FALSE;
	}

	if ( mFaceImgUP_BtnUpload.OnLButtonUp(ptMouse) )
	{
		CListNode < CHAT > *pNode;
		INT  nLine, nListCnt;

		LPCHAT	pstChat = NULL;

		if ( mFaceImgUP_nSelected == -1 )
			return FALSE;

		for ( pNode = mFaceImgUP_xFineName.GetHead(), nListCnt = 0, nLine = 0; pNode; pNode = pNode->GetNext(), nListCnt++ )
		{
			if ( mFaceImgUP_nStartLine + (mFaceImgUP_nSelected - mFaceImgUP_nStartLine ) != nListCnt )
				continue;
			
			pstChat = pNode->GetData();
			break;
		}

		CHAR szFileName[MAX_PATH];

		if ( pstChat == NULL )
			return FALSE;

		sprintf(szFileName, "%s", pstChat->pszChat);


		UINT	nWidth, nHeight;
		BYTE	*buf = NULL;
		buf = g_xGameProc.JpegFileToRGB(szFileName, &nWidth, &nHeight);

		if ( buf == NULL )
		{
			g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], -1, _OK, g_xMsg.GetMsg(4716));
			return FALSE;
		}

		FILE* fp = fopen( szFileName, "rb" );

		if ( !fp)
		{
			return FALSE;
		}

		INT len = filelength( fileno( fp ) );
		CHAR* pszBuf = NULL;
		pszBuf = new char[len];
		
		fread( pszBuf, 1, len, fp );


		if ( len > 4095 )
		{
			g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], -1, _OK, g_xMsg.GetMsg(4714));
		}
		else
		{
			DWORD dwCur = timeGetTime();

			if ( dwCur - mFaceImgUP_dwTimer < 1000 )
				return FALSE;

			mFaceImgUP_dwTimer = dwCur;

			g_xClientSocket.SendFaceImg(pszBuf, len);

			fclose( fp );

			// 암호화해서 저장
			fp = fopen( szFileName, "rb" );
			
			int len = _filelength( _fileno( fp ) );
			char *buf = new char[ len + 8 ];
			if ( !buf )
			{
				fclose( fp );
				return false;
			}

			fread( buf + 8, 1, len, fp );
			fclose( fp );

			if ( !crypto::encrypt( (unsigned char *) buf + 8, len ) )
			{
				delete[] buf;
				return false;
			}

			CHAR szCryptName[MAX_PATH];

			if ( GetCurrentDirectory(MAX_PATH, szCryptName))
			{
				if ( szCryptName[0] == '\0' )
				{
					return FALSE;
				}
			}
			sprintf(szCryptName, "%s\\Data\\%s_%s.fac", szCryptName,  g_szServerName, g_xGameProc.m_xMyHero.m_szName);

			fp = fopen( szCryptName, "wb" );
			if ( !fp )
				return false;

			fwrite( buf, 1, len + 8, fp );
			fclose( fp );

//			DeleteFile(szSave);			//    암호화 끝 파일 지우기

			g_xGameProc.m_xInterface.m_bIsThereUserFile = TRUE;

		}
		delete [] pszBuf;
		
		return FALSE;
	}

	if ( mFaceImgUP_BtnReset.OnLButtonUp(ptMouse) )
	{
		char* pszNullBuf = NULL;

		g_xClientSocket.SendFaceImg(pszNullBuf, 0);
		g_xGameProc.m_xInterface.m_bIsThereUserFile = FALSE;
		g_xGameProc.m_xInterface.m_bLoadUserFace = FALSE;

		CHAR	szName[MAX_PATH];

		if ( GetCurrentDirectory(MAX_PATH, szName))
		{
			if ( szName[0] == '\0' )
			{
				return FALSE;
			}

			sprintf(szName, "%s\\Data\\%s_%s.fac", szName,  g_szServerName, g_xGameProc.m_xMyHero.m_szName);
		}

		DeleteFile(szName);			//    내 fac파일 지우기
		return FALSE;
	}
	

	if ( mFaceImgUP_xReceiveScrBar.OnLButtonUp(ptMouse) )	return FALSE;

	return FALSE;
}

BOOL CFaceImgUpWnd::OnLButtonDown(POINT ptMouse)
{
	//공통
	if ( mFaceImgUP_BtnClose.OnLButtonDown(ptMouse) )
	{
		return FALSE;
	}

	if ( mFaceImgUP_BtnUpload.OnLButtonDown(ptMouse) )
	{
		return FALSE;
	}

	if ( mFaceImgUP_BtnReset.OnLButtonDown(ptMouse) )
	{
		return FALSE;
	}

	if ( mFaceImgUP_xReceiveScrBar.OnLButtonDown(ptMouse) )
	{
		FLOAT	fScrlRate;

		fScrlRate	= mFaceImgUP_xReceiveScrBar.GetScrlRate();
		mFaceImgUP_nStartLine = (INT)((mFaceImgUP_xFineName.GetCount())*fScrlRate);

		if ( mFaceImgUP_nStartLine > mFaceImgUP_nMaxLine - 1 )
			mFaceImgUP_nStartLine = mFaceImgUP_nMaxLine - 1 ;

		return TRUE;
	}


	return FALSE;
}

BOOL CFaceImgUpWnd::OnRButtonDown(POINT ptMouse)
{
	return FALSE;
}

BOOL CFaceImgUpWnd::OnLButtonDoubleClick(POINT ptMouse)
{
	for ( INT nI=0; nI<12; nI++ )
	{
		if ( PtInRect(&mFaceImgUP_rcCell[nI], g_xGameProc.m_ptMousePos) )
		{
			CListNode < CHAT > *pNode;
			INT  nLine, nListCnt;

			LPCHAT	pstChat = NULL;

			for ( pNode = mFaceImgUP_xFineName.GetHead(), nListCnt = 0, nLine = 0; pNode; pNode = pNode->GetNext(), nListCnt++ )
			{
				if ( mFaceImgUP_nStartLine + nI != nListCnt )
					continue;

				mFaceImgUP_nSelected = nListCnt;
				
				if ( nListCnt == mFaceImgUP_nSelected )
				{
					pstChat = pNode->GetData();
				}

				CHAR szFileName[MAX_PATH];
				UINT	 nWidth, nHeight;

				if ( GetCurrentDirectory(MAX_PATH, szFileName))
				{
					if ( szFileName[0] == '\0' )
					{
						return FALSE;
					}

					if ( pstChat == NULL )
						return FALSE;

					sprintf( szFileName, "%s\\%s", szFileName, pstChat->pszChat );

					BYTE	*buf = NULL;
					buf = g_xGameProc.JpegFileToRGB(szFileName, &nWidth, &nHeight);

					if ( buf == NULL )
					{
						m_hbmUserFace.ReleaseSurface();
						return FALSE;
					}

					if ( g_xGameProc.BGRFromRGB(buf, nWidth, nHeight) == FALSE )
					{
						m_hbmUserFace.ReleaseSurface();
						return FALSE;
					}

					if ( g_xGameProc.VertFlipBuf(buf, nWidth * 3, nHeight) == FALSE )
					{
						m_hbmUserFace.ReleaseSurface();
						return FALSE;
					}

					UINT nWidthDW = 0;
					BYTE	*temp = NULL;
					
					temp = g_xGameProc.MakeDwordAlignedBuf(buf,nWidth,nHeight,&nWidthDW);

					if ( temp == NULL )
					{
						m_hbmUserFace.ReleaseSurface();
						return FALSE;
					}
					
					WORD *wpFaceImg = NULL;
					wpFaceImg = new WORD[sizeof(WORD) * nWidth * nHeight];

					INT nNewWidth = int(( nWidth + 3 ) / 4) * 4;
					
					g_xGameProc.Convert24To16(temp, 24, wpFaceImg, nWidth, nHeight);

					m_hbmUserFace.ReleaseSurface();
					m_hbmUserFace.CreateOffScreenSurface(g_xMainWnd.GetDirectDraw(), nNewWidth, nHeight);
					m_hbmUserFace.CopyImageToSurfaceDx(nWidth, nHeight, nNewWidth, wpFaceImg);

					mFaceImgUP_bLoadSuccess = TRUE;

					if ( wpFaceImg != NULL )
					{
						delete [] wpFaceImg;
					}
					sprintf( mFaceImgUP_szSelectedFileName, "%s", szFileName);
				}
			}
			
			break;
		}
	}

	return FALSE;
}

BOOL CFaceImgUpWnd::OnMouseMove(POINT ptMouse)
{

	// 공통
	mFaceImgUP_BtnClose.OnMouseMove(ptMouse);
	mFaceImgUP_BtnUpload.OnMouseMove(ptMouse);
	mFaceImgUP_BtnReset.OnMouseMove(ptMouse);

	if ( mFaceImgUP_xReceiveScrBar.OnMouseMove(ptMouse) )
	{
		FLOAT	fScrlRate;
		fScrlRate	= mFaceImgUP_xReceiveScrBar.GetScrlRate();

		mFaceImgUP_nStartLine = (INT)((mFaceImgUP_xFineName.GetCount())*fScrlRate);
		return TRUE;
	}


	for ( INT nI=0; nI<12; nI++ )
	{
		if ( PtInRect(&mFaceImgUP_rcCell[nI], g_xGameProc.m_ptMousePos) )
		{
			mFaceImgUP_nMouseLacated = nI;
			return FALSE;
		}
	}


	return FALSE;
}

VOID CFaceImgUpWnd::OnScrollDown()
{
	if ( mFaceImgUP_nStartLine > 0 )
		mFaceImgUP_nStartLine--;
}

VOID CFaceImgUpWnd::OnScrollUp()
{
	if ( mFaceImgUP_nStartLine < mFaceImgUP_nMaxLine -2 )
	mFaceImgUP_nStartLine++;
}

VOID CFaceImgUpWnd::CloseFaceImgUpWnd()
{
	mFaceImgUP_nMouseLacated = -1;
	mFaceImgUP_nSelected = -1;
	mFaceImgUP_nStartLine = 0;
	mFaceImgUP_nMaxLine = 0;

	mFaceImgUP_bLoadSuccess = FALSE;

	mFaceImgUP_xFineName.ClearAll();

	ZeroMemory(mFaceImgUP_szSelectedFileName, MAX_PATH);

	g_xGameProc.m_xInterface.DeleteWindowToList(_WND_ID_FACEIMGUP);
	SetGameWndActive(FALSE);
}

VOID CFaceImgUpWnd::FindJPGFile()
{
	CHAR	pszFullPath[MAX_PATH];

	ZeroMemory(pszFullPath, MAX_PATH);

	if ( GetCurrentDirectory(MAX_PATH, pszFullPath) )
	{
		if ( pszFullPath[0] == '\0' )
		{
			return;
		}


		WIN32_FIND_DATA fd;

		HANDLE hfind = FindFirstFile("*.jpg", &fd);

		CHAT* stChat;
		DWORD dwFontColor = RGB(250, 250, 250), dwFontBackColor = RGB(0, 0, 0);

		mFaceImgUP_nMaxLine = 1;

		if ( hfind != INVALID_HANDLE_VALUE )
		{
			do
			{
				FILE* fp = fopen( fd.cFileName, "rb" );

				if ( !fp)
				{
					continue;
				}

				INT len = filelength( fileno( fp ) );

				if ( len <= 4095 )
				{
					stChat = new CHAT;
					stChat->dwFontColor = dwFontColor;
					stChat->dwBackColor = dwFontBackColor;
					strcpy(stChat->pszChat, fd.cFileName);
					
					mFaceImgUP_xFineName.Insert(stChat);

					mFaceImgUP_nMaxLine++;
				}

			}while ( FindNextFile( hfind, &fd ) );
		}
	}
}
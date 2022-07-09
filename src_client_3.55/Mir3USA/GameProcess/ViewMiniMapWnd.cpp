/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"


CViewMiniMapWnd::CViewMiniMapWnd()
{
	Init();
}

CViewMiniMapWnd::~CViewMiniMapWnd()
{
	SAFE_RELEASE(mViewMiniMap_pddsSurface);
	mViewMiniMap_xMinimapData1.Destroy();
	mViewMiniMap_xMinimapData2.Destroy();
	Destroy();
}

VOID CViewMiniMapWnd::Init()
{
	CGameWnd::Init();

	mViewMiniMap_xInfo.ClearAll();
	mViewMiniMap_nMinimapCnt = 0;

	mViewMiniMap_nMunuStart = 0;

	mViewMiniMap_nStartYMap = 0;
	mViewMiniMap_nMapHeight = 0;

	mViewMiniMap_nMapWidth = 0;
	mViewMiniMap_nStartXMap = 0;

	mViewMiniMap_xMinimapData1.Init();
	mViewMiniMap_xMinimapData2.Init();

	mViewMiniMap_xMinimapData1.NewLoad(".\\Data\\MMap.wil");
	mViewMiniMap_xMinimapData2.NewLoad(".\\Data\\FMMap.wil");

	ZeroMemory(&mViewMiniMap_rcMiniMapRect, sizeof(RECT));

	mViewMiniMap_nMiniMapWidth	= 512;
	mViewMiniMap_nMiniMapHeight	= 512;

	mViewMiniMap_nMultiple = _1ST_RATE;

	SetRect(&mViewMiniMap_rcShowMenu, 0, 0, 0, 0);
	SetRect(&mViewMiniMap_rcMap, 0, 0, 0, 0);

	SAFE_RELEASE(mViewMiniMap_pddsSurface);

	mViewMiniMap_BtnClose.Init();
	mViewMiniMap_xScrSelectMenu.Init();
	mViewMiniMap_xScrVerMap.Init();
	mViewMiniMap_xScrHorMap.Init();

	for ( INT nI=0; nI<_MAX_MENU; nI++ )
		ZeroMemory(mViewMiniMap_szMenu[nI], 30);

	ZeroMemory(mViewMiniMap_szSelectedMapName, 30);

	mViewMiniMap_nSelectedMapIdx = -1;
	mViewMiniMap_nSelectedNum = -1;
	mViewMiniMap_bIsLoad = FALSE;
}

VOID CViewMiniMapWnd::Destroy()
{
	CGameWnd::Destroy();
}

VOID CViewMiniMapWnd::CreateViewMiniMapWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove)
{
	CreateGameWnd(nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight);

	mViewMiniMap_BtnClose.CreateGameBtn(pxWndImage, 1221, 1222, nStartX+526, nStartY+326, g_xMsg.GetMsg(1052), _BTN_TYPE_FOCUS, 1221, TRUE);
	mViewMiniMap_Btn2x.CreateGameBtn(pxWndImage, 673, 676, nStartX+526, nStartY+326, g_xMsg.GetMsg(4900), _BTN_TYPE_FOCUS, 673, TRUE);
	mViewMiniMap_Btn1x.CreateGameBtn(pxWndImage, 672, 675, nStartX+526, nStartY+326, g_xMsg.GetMsg(4901), _BTN_TYPE_FOCUS, 672, TRUE);
	mViewMiniMap_BtnHalfx.CreateGameBtn(pxWndImage, 671, 674, nStartX+526, nStartY+326, g_xMsg.GetMsg(4902), _BTN_TYPE_FOCUS, 671, TRUE);
	
	mViewMiniMap_xScrSelectMenu.CreateScrlBar(pxWndImage, 1225, _MAX_MENU, 20, 464, 31);
	mViewMiniMap_xScrVerMap.CreateScrlBar(pxWndImage, 1225, 40, 20, 454, 31);
	mViewMiniMap_xScrHorMap.CreateScrlBar(pxWndImage, 1225, 40, 440, 20, 31, SCR_TYPE_HORIZONTAL);

	mViewMiniMap_Btn2x.ResetGameBtn(673, 676, 673);
	mViewMiniMap_Btn1x.ResetGameBtn(675, 675, 675);
	mViewMiniMap_BtnHalfx.ResetGameBtn(671, 674, 671);
	
	LoadMIF();
}	
		
VOID CViewMiniMapWnd::ShowViewMiniMapWnd()
{
	mViewMiniMap_BtnClose.ChangeRect(m_rcWnd.left+708, m_rcWnd.top+546);
	mViewMiniMap_Btn2x.ChangeRect(m_rcWnd.left+366, m_rcWnd.top+532);
	mViewMiniMap_Btn1x.ChangeRect(m_rcWnd.left+296, m_rcWnd.top+532);
	mViewMiniMap_BtnHalfx.ChangeRect(m_rcWnd.left+226, m_rcWnd.top+532);
	
	SetRect(&mViewMiniMap_rcShowMenu, m_rcWnd.left + 5, m_rcWnd.top + 5, m_rcWnd.left + 170, m_rcWnd.top + 460);
	SetRect(&mViewMiniMap_rcMap, m_rcWnd.left + 180, m_rcWnd.top + 5, m_rcWnd.left + 730, m_rcWnd.top + 460);

	ShowGameWnd();

	for ( INT nI=0; nI<_MAX_MENU; nI++ )
	{
		SetRect(&mViewMiniMap_rcMenu[nI], m_rcWnd.left + 28, m_rcWnd.top + 67 + nI * 30, m_rcWnd.left + 136, m_rcWnd.top + 92 + nI * 30);
	}

	RECT rcSelectMapName;

	SetRect(&rcSelectMapName, m_rcWnd.left + 40, m_rcWnd.top + 26, m_rcWnd.left + 145, m_rcWnd.top + 41);
	
	g_xMainWnd.PutsHan(NULL, rcSelectMapName, RGB(250, 250, 248), 0, mViewMiniMap_szSelectedMapName);
	

	// 마우스 있는 곳 뒷판
	if ( mViewMiniMap_nMouseLocated != -1 )
	{
		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(677) )
		{
			g_xMainWnd.DrawWithImageForComp(mViewMiniMap_rcMenu[mViewMiniMap_nMouseLocated].left, mViewMiniMap_rcMenu[mViewMiniMap_nMouseLocated].top, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
		}
/*
		D3DMATERIAL7 mtrl;
		D3DVECTOR	 vecTrans((FLOAT)mViewMiniMap_rcMenu[mViewMiniMap_nMouseLocated].left, (FLOAT)mViewMiniMap_rcMenu[mViewMiniMap_nMouseLocated].top, 0);
		D3DVECTOR	 vecScale((FLOAT)mViewMiniMap_rcMenu[mViewMiniMap_nMouseLocated].right-mViewMiniMap_rcMenu[mViewMiniMap_nMouseLocated].left, 
			mViewMiniMap_rcMenu[mViewMiniMap_nMouseLocated].bottom-mViewMiniMap_rcMenu[mViewMiniMap_nMouseLocated].top, 1);

		D3DUtil_InitMaterial(mtrl, (FLOAT)108/255.0f, (FLOAT)108/255.0f, (FLOAT)20/255.0f);
		mtrl.diffuse.a = 180.0f/255.0f;
		g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
*/
	}

	if ( mViewMiniMap_nSelectedNum != -1 && mViewMiniMap_nSelectedNum-mViewMiniMap_nMunuStart >= 0 && mViewMiniMap_nSelectedNum-mViewMiniMap_nMunuStart < _MAX_MENU)
	{
		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(678) )
		{
			g_xMainWnd.DrawWithImageForComp(mViewMiniMap_rcMenu[mViewMiniMap_nSelectedNum-mViewMiniMap_nMunuStart].left, mViewMiniMap_rcMenu[mViewMiniMap_nSelectedNum-mViewMiniMap_nMunuStart].top, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
		}
/*		
		D3DMATERIAL7 mtrl;
		D3DVECTOR	 vecTrans((FLOAT)mViewMiniMap_rcMenu[mViewMiniMap_nSelectedNum-mViewMiniMap_nMunuStart].left, (FLOAT)mViewMiniMap_rcMenu[mViewMiniMap_nSelectedNum-mViewMiniMap_nMunuStart].top, 0);
		D3DVECTOR	 vecScale((FLOAT)mViewMiniMap_rcMenu[mViewMiniMap_nSelectedNum-mViewMiniMap_nMunuStart].right-mViewMiniMap_rcMenu[mViewMiniMap_nSelectedNum-mViewMiniMap_nMunuStart].left, 
			mViewMiniMap_rcMenu[mViewMiniMap_nSelectedNum-mViewMiniMap_nMunuStart].bottom-mViewMiniMap_rcMenu[mViewMiniMap_nSelectedNum-mViewMiniMap_nMunuStart].top, 1);

		D3DUtil_InitMaterial(mtrl, (FLOAT)64/255.0f, (FLOAT)5/255.0f, (FLOAT)5/255.0f);
		mtrl.diffuse.a = 180.0f/255.0f;
		g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
*/
	}

	// 기본적인 15개 항목을 셋팅하고 넘어가 준다.
	INT  nLine, nListCnt;
	CListNode < CLIENTMINIMAPVIEWER > *pNode;
	LPCLIENTMINIMAPVIEWER pstViewerInfo = NULL;

	for ( pNode = mViewMiniMap_xInfo.GetHead(), nListCnt = 0, nLine = 0; pNode; pNode = pNode->GetNext(), nListCnt++ )
	{
		if ( nListCnt < mViewMiniMap_nMunuStart || nListCnt > mViewMiniMap_nMunuStart + _MAX_MENU - 1 )
			continue;

		pstViewerInfo = pNode->GetData();

		g_xMainWnd.PutsHan(NULL, mViewMiniMap_rcMenu[nLine], RGB(250, 250, 248), 0, pstViewerInfo->pszMinimapName);
		nLine++;
	}

	// 미니맵 그리기
	if ( mViewMiniMap_nSelectedMapIdx != -1 )
		RenderMiniMap2();

	mViewMiniMap_xScrSelectMenu.ShowScrlBar(m_rcWnd.left+156, m_rcWnd.top+70, mViewMiniMap_nMunuStart, mViewMiniMap_nMinimapCnt);
	mViewMiniMap_xScrVerMap.ShowScrlBar(m_rcWnd.left+723, m_rcWnd.top+30, mViewMiniMap_nStartYMap, mViewMiniMap_nMapHeight);
	mViewMiniMap_xScrHorMap.ShowScrlBar(m_rcWnd.left+208, m_rcWnd.top+560, mViewMiniMap_nStartXMap, mViewMiniMap_nMapWidth);
	
	mViewMiniMap_BtnClose.ShowGameBtn();
	mViewMiniMap_Btn2x.ShowGameBtn();
	mViewMiniMap_Btn1x.ShowGameBtn();
	mViewMiniMap_BtnHalfx.ShowGameBtn();
}

BOOL CViewMiniMapWnd::OnLButtonDown(POINT ptMouse)
{
	if ( mViewMiniMap_BtnClose.OnLButtonDown(ptMouse) )
	{
		return FALSE;
	}

	if ( mViewMiniMap_Btn2x.OnLButtonDown(ptMouse) )
	{
		return FALSE;
	}

	if ( mViewMiniMap_Btn1x.OnLButtonDown(ptMouse) )
	{
		return FALSE;
	}

	if ( mViewMiniMap_BtnHalfx.OnLButtonDown(ptMouse) )
	{
		return FALSE;
	}

	if ( mViewMiniMap_xScrSelectMenu.OnLButtonDown(ptMouse) )
	{
		FLOAT	fScrlRate;

		fScrlRate	= mViewMiniMap_xScrSelectMenu.GetScrlRate();
		mViewMiniMap_nMunuStart = (INT)((mViewMiniMap_nMinimapCnt)*fScrlRate);

		if ( mViewMiniMap_nMunuStart > mViewMiniMap_nMinimapCnt - 1 )
			mViewMiniMap_nMunuStart = mViewMiniMap_nMinimapCnt - 1 ;

		return TRUE;
	}

	if ( mViewMiniMap_xScrVerMap.OnLButtonDown(ptMouse) )
	{
		if ( mViewMiniMap_nMultiple != _HALF_RATE )
		{
			FLOAT	fScrlRate;

			fScrlRate	= mViewMiniMap_xScrVerMap.GetScrlRate();
			mViewMiniMap_nStartYMap = (INT)((mViewMiniMap_nMapHeight)*fScrlRate);

			if ( mViewMiniMap_nStartYMap > mViewMiniMap_nMapHeight )
				mViewMiniMap_nStartYMap = mViewMiniMap_nMapHeight;

			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

	if ( mViewMiniMap_xScrHorMap.OnLButtonDown(ptMouse) )
	{
		FLOAT	fScrlRate;

		fScrlRate	= mViewMiniMap_xScrHorMap.GetScrlRate();
		mViewMiniMap_nStartXMap = (INT)((mViewMiniMap_nMapWidth)*fScrlRate);

		if ( mViewMiniMap_nStartXMap > mViewMiniMap_nMapWidth )
			mViewMiniMap_nStartXMap = mViewMiniMap_nMapWidth ;

		return TRUE;
	}
	
	
	for ( INT nI = 0; nI < _MAX_MENU; nI++ )
	{
		if ( PtInRect(&mViewMiniMap_rcMenu[nI], ptMouse) )
		{
			mViewMiniMap_nSelectedNum = nI + mViewMiniMap_nMunuStart;

			INT  nLine, nListCnt;
			CListNode < CLIENTMINIMAPVIEWER > *pNode;
			LPCLIENTMINIMAPVIEWER pstViewerInfo = NULL;

			for ( pNode = mViewMiniMap_xInfo.GetHead(), nListCnt = 0; pNode; pNode = pNode->GetNext(), nListCnt++ )
			{
				if ( nListCnt == mViewMiniMap_nSelectedNum )
				{
					pstViewerInfo = pNode->GetData();
					mViewMiniMap_nSelectedMapIdx = pstViewerInfo->nMinimapIdx;
					SetMiniMap(mViewMiniMap_nSelectedMapIdx);
					sprintf(mViewMiniMap_szSelectedMapName, pstViewerInfo->pszMinimapName);
					break;
				}
			}
		}
		
	}

	return FALSE;
}

BOOL CViewMiniMapWnd::OnLButtonUp(POINT ptMouse)
{
	if ( mViewMiniMap_BtnClose.OnLButtonUp(ptMouse) )
	{
		return TRUE;
	}

	if ( mViewMiniMap_Btn2x.OnLButtonUp(ptMouse) )
	{
		mViewMiniMap_Btn2x.ResetGameBtn(676, 676, 676);
		mViewMiniMap_Btn1x.ResetGameBtn(672, 675, 672);
		mViewMiniMap_BtnHalfx.ResetGameBtn(671, 674, 671);
		mViewMiniMap_nMultiple = _2ND_RATE;

		if ( mViewMiniMap_nSelectedMapIdx != -1 )
			SetMiniMap(mViewMiniMap_nSelectedMapIdx);
		return FALSE;
	}

	if ( mViewMiniMap_Btn1x.OnLButtonUp(ptMouse) )
	{
		mViewMiniMap_Btn2x.ResetGameBtn(673, 676, 673);
		mViewMiniMap_Btn1x.ResetGameBtn(675, 675, 675);
		mViewMiniMap_BtnHalfx.ResetGameBtn(671, 674, 671);
		mViewMiniMap_nMultiple = _1ST_RATE;

		if ( mViewMiniMap_nSelectedMapIdx != -1 )
			SetMiniMap(mViewMiniMap_nSelectedMapIdx);
		return FALSE;
	}

	if ( mViewMiniMap_BtnHalfx.OnLButtonUp(ptMouse) )
	{
		mViewMiniMap_Btn2x.ResetGameBtn(673, 676, 673);
		mViewMiniMap_Btn1x.ResetGameBtn(672, 675, 672);
		mViewMiniMap_BtnHalfx.ResetGameBtn(674, 674, 674);
		mViewMiniMap_nMultiple = _HALF_RATE;

		if ( mViewMiniMap_nSelectedMapIdx != -1 )
			SetMiniMap(mViewMiniMap_nSelectedMapIdx);
		return FALSE;
	}

	if ( mViewMiniMap_xScrSelectMenu.OnLButtonUp(ptMouse) )
		return FALSE;

	if ( mViewMiniMap_xScrVerMap.OnLButtonUp(ptMouse) )
		return FALSE;

	if ( mViewMiniMap_xScrHorMap.OnLButtonUp(ptMouse) )
		return FALSE;

	return FALSE;
}

BOOL CViewMiniMapWnd::OnMouseMove(POINT ptMouse)
{
	mViewMiniMap_BtnClose.OnMouseMove(ptMouse);
	mViewMiniMap_Btn2x.OnMouseMove(ptMouse);
	mViewMiniMap_Btn1x.OnMouseMove(ptMouse);
	mViewMiniMap_BtnHalfx.OnMouseMove(ptMouse);
	
	if ( mViewMiniMap_xScrSelectMenu.OnMouseMove(ptMouse) )
	{
		FLOAT	fScrlRate;
		fScrlRate	= mViewMiniMap_xScrSelectMenu.GetScrlRate();

		mViewMiniMap_nMunuStart = (INT)((mViewMiniMap_nMinimapCnt)*fScrlRate);
		return TRUE;
	}

	if ( mViewMiniMap_xScrVerMap.OnMouseMove(ptMouse) )
	{
		if ( mViewMiniMap_nMultiple != _HALF_RATE )
		{
			FLOAT	fScrlRate;
			fScrlRate	= mViewMiniMap_xScrVerMap.GetScrlRate();

			mViewMiniMap_nStartYMap = (INT)((mViewMiniMap_nMapHeight)*fScrlRate);
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

	if ( mViewMiniMap_xScrHorMap.OnMouseMove(ptMouse) )
	{
		FLOAT	fScrlRate;
		fScrlRate	= mViewMiniMap_xScrHorMap.GetScrlRate();

		mViewMiniMap_nStartXMap = (INT)((mViewMiniMap_nMapWidth)*fScrlRate);
		return TRUE;
	}

	for ( INT nI = 0; nI < _MAX_MENU; nI++ )
	{
		if ( PtInRect(&mViewMiniMap_rcMenu[nI], ptMouse) )
		{
			mViewMiniMap_nMouseLocated = nI;
			return FALSE;
		}
	}
	mViewMiniMap_nMouseLocated = -1;

	return FALSE;
}

VOID CViewMiniMapWnd::OnScrollDown()
{
	if ( PtInRect(&mViewMiniMap_rcShowMenu, g_xGameProc.m_ptMousePos) )
	{
		if ( mViewMiniMap_nMunuStart > 0 )
			mViewMiniMap_nMunuStart--;
	}

	if ( PtInRect(&mViewMiniMap_rcMap, g_xGameProc.m_ptMousePos) )
	{
		if ( mViewMiniMap_nMultiple != _HALF_RATE )
		{
			if ( mViewMiniMap_nStartYMap > 0 )
				mViewMiniMap_nStartYMap -= 30;

			if ( mViewMiniMap_nStartYMap <= 0 )
				mViewMiniMap_nStartYMap = 0;
		}
	}
}

VOID CViewMiniMapWnd::OnScrollUp()
{
	if ( PtInRect(&mViewMiniMap_rcShowMenu, g_xGameProc.m_ptMousePos) )
	{
		if ( mViewMiniMap_nMunuStart < mViewMiniMap_nMinimapCnt - 1 )
			mViewMiniMap_nMunuStart++;
	}

	if ( PtInRect(&mViewMiniMap_rcMap, g_xGameProc.m_ptMousePos) )
	{
		if ( mViewMiniMap_nMultiple != _HALF_RATE )
		{
			if ( mViewMiniMap_nStartYMap < mViewMiniMap_nMapHeight )
				mViewMiniMap_nStartYMap += 30;

			if ( mViewMiniMap_nStartYMap >= mViewMiniMap_nMapHeight )
				mViewMiniMap_nStartYMap = mViewMiniMap_nMapHeight ;
		}
	}
}

BOOL CViewMiniMapWnd::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	return FALSE;
}

VOID CViewMiniMapWnd::DelAllMIF()
{
}

BOOL CViewMiniMapWnd::LoadMIF()
{
	DelAllMIF();

	// 암호화 루틴해제.
	char* pszBuf = NULL;

	crypto_seed s = {(char) 0xF0, (char) 0x39, (char) 0xAB, (char) 0x8E, 0x9FDE1A93};
	crypto::setSeed(&s);
	FILE *fp = fopen( "Map.Mif", "rb" );

	if ( !fp )
	{
		MessageBox(NULL, (char*)"Message List File Error.", "[Error] - Legend of Mir III", MB_ICONERROR);
		return FALSE;
	}

	int len = _filelength(_fileno(fp));
	pszBuf = new char[len];

	if ( !pszBuf )
	{
		fclose(fp);
		delete [] pszBuf;
		MessageBox(NULL, (char*)"Message List File Error.", "[Error] - Legend of Mir III", MB_ICONERROR);
		return FALSE;
	}

	fread(pszBuf, 1, len, fp);
	fclose(fp);

	if ( !crypto::decrypt((unsigned char *)pszBuf, len) )
	{
		delete[] pszBuf;
		MessageBox(NULL, (char*)"Message List File Error.", "[Error] - Legend of Mir III", MB_ICONERROR);
		return FALSE;
	}

	// 데이타적용.
	CHAR  pszMsgNum[20];
	ZeroMemory(pszMsgNum, 20);

	CHAR* pszComment  = NULL;
	CHAR* pszLineNext = NULL;
	CHAR* pszLine	  = pszBuf + 8;		// Seed를 건너뛴다.

	INT	nLineLen = 0;

	while ( pszLineNext = (char*)strchr(pszLine, '\r') )
	{
		*pszLineNext = '\0';
	
		// Comment.
		if ( pszComment = (char*)strchr(pszLine, ';') )
		{
			*pszComment = '\0';
		}
		// Message
		else if ( (char*)strchr(pszLine, '#') )
		{
			// #을 건너 뛴다.
			pszLine++;

			CHAR* pszMsg = NULL;

			nLineLen = strlen(pszLine)+1;
			pszMsg = new CHAR[nLineLen];
			ZeroMemory(pszMsg, nLineLen);

			sscanf(pszLine, "%s %[^\000]", pszMsgNum, pszMsg);

			CLIENTMINIMAPVIEWER *pObj = new CLIENTMINIMAPVIEWER;
			pObj->nMinimapIdx = atoi(pszMsgNum);
			pObj->pszMinimapName = pszMsg;

			mViewMiniMap_nMinimapCnt++;

			if ( !mViewMiniMap_xInfo.Insert(pObj) )
			{
				delete[] pszBuf;
				CHAR pszError[MAX_PATH];
				sprintf(pszError, "Message List File Error(MsgNum:%d)", atoi(pszMsgNum));
				MessageBox(NULL, (char*)pszError, "[Error] - Legend of Mir III", MB_ICONERROR);
				DelAllMIF();
				return FALSE;
			}
		}

		pszLine = (pszLineNext+2);  // '\r''\n'
	}

	mViewMiniMap_nMinimapCnt -= 17;

	delete [] pszBuf;

	return TRUE;
}


VOID CViewMiniMapWnd::ReadMapNameFromMIF()
{
	if ( mViewMiniMap_bIsLoad == FALSE )
	{
		// 기본적인 15개 항목을 셋팅하고 넘어가 준다.
		INT  nLine, nListCnt;
		CListNode < CLIENTMINIMAPVIEWER > *pNode;
		LPCLIENTMINIMAPVIEWER pstViewerInfo = NULL;

		for ( pNode = mViewMiniMap_xInfo.GetHead(), nListCnt = 0; pNode && nListCnt<_MAX_MENU ; pNode = pNode->GetNext(), nListCnt++ )
		{
			pstViewerInfo = pNode->GetData();

			sprintf(mViewMiniMap_szMenu[nListCnt], pstViewerInfo->pszMinimapName);
		}
		mViewMiniMap_bIsLoad = TRUE;
	}
}

BOOL CViewMiniMapWnd::SetMiniMap(INT nIdx)
{
	INT nWidth, nHeight;

	if ( mViewMiniMap_nMultiple == _1ST_RATE )
	{
		nWidth = 512;
		nHeight = 512;
	}
	else if ( mViewMiniMap_nMultiple == _2ND_RATE )
	{
		nWidth = 256;
		nHeight = 256;
	}
	else if ( mViewMiniMap_nMultiple == _HALF_RATE )
	{
		nWidth = 1024;
		nHeight = 1024;
	}
	else if ( mViewMiniMap_nMultiple == _QUATER_RATE )
	{
		nWidth = 512;
		nHeight = 512;
	}

	if ( nIdx >= 1000 )
	{
		if ( mViewMiniMap_xMinimapData2.NewSetIndex(nIdx-1001) )
		{
 			SetRect(&mViewMiniMap_rcMiniMapRect, 0, 0, mViewMiniMap_xMinimapData2.m_lpstNewCurrWilImageInfo->shWidth, mViewMiniMap_xMinimapData2.m_lpstNewCurrWilImageInfo->shHeight);
			MiniMapSurface(g_xMainWnd.Get3DDevice(), nWidth, nHeight);
			SetMiniMapSize();
			return TRUE;
		}
	}
	else
	{
		if ( mViewMiniMap_xMinimapData1.NewSetIndex(nIdx-1) )
		{
 			SetRect(&mViewMiniMap_rcMiniMapRect, 0, 0, mViewMiniMap_xMinimapData1.m_lpstNewCurrWilImageInfo->shWidth, mViewMiniMap_xMinimapData1.m_lpstNewCurrWilImageInfo->shHeight);
			MiniMapSurface(g_xMainWnd.Get3DDevice(), nWidth, nHeight);
			SetMiniMapSize();
			return TRUE;
		}
	}

	return FALSE;
}


VOID CViewMiniMapWnd::RenderMiniMap()
{
	INT nWidth = mViewMiniMap_rcMiniMapRect.right - mViewMiniMap_rcMiniMapRect.left, nHeight = mViewMiniMap_rcMiniMapRect.bottom - mViewMiniMap_rcMiniMapRect.top;

	INT nViewX = mViewMiniMap_nStartXMap, nViewY = mViewMiniMap_nStartYMap;	
	INT nShowWidth = nWidth + nViewX;
	INT nShowHeight = nHeight + nViewY;

	if ( nViewX < 0 )
		nViewX = 0;
	if ( nViewY < 0 )
		nViewY =0;

	if ( nShowWidth - nViewX > _SCRNMAP_WIDTH )
		nShowWidth = nViewX + _SCRNMAP_WIDTH;

	if ( nShowHeight - nViewY > _SCRNMAP_HEIGHT )
		nShowHeight = nViewY + _SCRNMAP_HEIGHT;

	INT nAddX = 0, nAddY = 0;

	if ( mViewMiniMap_nMultiple == _2ND_RATE )
	{
		if ( nWidth > _SCRNMAP_WIDTH )
			nAddX = -116;
		if ( nHeight >= _SCRNMAP_HEIGHT )
			nAddY = -93;
	}
	else if ( mViewMiniMap_nMultiple == _HALF_RATE )
	{
		nAddX = 214;
		nAddY = 172;
	}
	else if ( mViewMiniMap_nMultiple == _QUATER_RATE )
	{
		nAddX = _SCRNMAP_WIDTH;
		nAddY = _SCRNMAP_HEIGHT;
	} 

	// 비율이 200%일 때 nAddX = -116, nAddY = -93;
	// 비율이 50%일 때 nAddX = 214, nAddY = 170;
	// 비율이 25%일 때 nAddX = _SCRNMAP_WIDTH, nAddY = _SCRNMAP_HEIGHT;

	INT nViewWidth = nShowWidth+nAddX;
	INT nViewHeight = nShowHeight+nAddY;

	if ( nViewWidth - nViewX > nWidth )
		nViewWidth = nWidth - nViewX;

	if ( nViewHeight - nViewY > nHeight )
		nViewHeight = nHeight - nViewY;

	if ( mViewMiniMap_nMultiple == _2ND_RATE )
	{
		if ( nViewWidth - nViewX > 384)
			nViewWidth = nViewX + 384;
		if ( nViewHeight - nViewY > 307 )
			nViewHeight = nViewY + 307;
	}

	RECT rcView = {nViewX, nViewY, nViewWidth, nViewHeight};
	
	// multiple이 1:1이면 원래 크기대로 rcView를 잡아주고 
	// 50% 면 rcView를 원래 크기보다 반씩 작게 해준다.
	if ( mViewMiniMap_nSelectedMapIdx >= 1000 )
	{
		if ( mViewMiniMap_xMinimapData2.NewSetIndex(mViewMiniMap_nSelectedMapIdx-1001) )
		{
			g_xMainWnd.DrawWithImageForComp(&rcView, (WORD*)mViewMiniMap_xMinimapData2.m_pbCurrImage, mViewMiniMap_pddsSurface);
		}
	}
	else
	{
		if ( mViewMiniMap_xMinimapData1.NewSetIndex(mViewMiniMap_nSelectedMapIdx-1) )
		{
			g_xMainWnd.DrawWithImageForComp(&rcView, (WORD*)mViewMiniMap_xMinimapData1.m_pbCurrImage, mViewMiniMap_pddsSurface);
		}
	}

	if ( mViewMiniMap_pddsSurface == NULL )
	{
		return;
	}

	INT nStartX = m_rcWnd.left+187, nStartY = m_rcWnd.top+24;

	//비율이 200%일 때 * 1.3 50%일 때 * 0.7 25%일 때 *0.5
	
	if ( mViewMiniMap_nMultiple == _2ND_RATE )
	{
		nWidth = nWidth * 1.3;
		nHeight = nHeight * 1.3;
	}
	else if ( mViewMiniMap_nMultiple == _HALF_RATE )
	{
		nWidth = nWidth * 0.7;
		nHeight = nHeight * 0.7;
	}
	else if ( mViewMiniMap_nMultiple == _QUATER_RATE )
	{
		nWidth = nWidth * 0.5;
		nHeight = nHeight * 0.5;
	}
	
	RECT rcGdi = {nStartX, nStartY, nStartX+nWidth, nStartY+nHeight};

	if ( nWidth > _SCRNMAP_WIDTH )
		rcGdi.right = _SCRNMAP_WIDTH + nStartX;

	if ( nHeight > _SCRNMAP_HEIGHT )
		rcGdi.bottom = _SCRNMAP_HEIGHT + nStartY;

	// 미니맵 구멍 난 거 메꾸는 까만색 바탕
	g_xMainWnd.DrawWithGDI(&rcGdi, NULL, RGB(10, 10, 10), 2);

	D3DMATERIAL7 mtrl;
	D3DVECTOR	vecTrans((FLOAT)nStartX, (FLOAT)nStartY, 0);
	D3DVECTOR	vecScale((FLOAT)nWidth, (FLOAT)nHeight, 1);

	D3DUtil_InitMaterial(mtrl, (FLOAT)150/255.0f, (FLOAT)150/255.0f, (FLOAT)150/255.0f);
	mtrl.diffuse.a = 255.0f/255.0f;

	g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, mViewMiniMap_pddsSurface);
}

VOID CViewMiniMapWnd::RenderMiniMap2()
{
	INT nStartX = mViewMiniMap_nStartXMap, nStartY = mViewMiniMap_nStartYMap;
	RECT rcView;
	INT nWidth, nHeight;

	if ( mViewMiniMap_nMultiple == _1ST_RATE )
	{
		rcView.left = mViewMiniMap_nStartXMap;
		rcView.top = mViewMiniMap_nStartYMap;
		rcView.right = mViewMiniMap_nStartXMap + 512;
		rcView.bottom = mViewMiniMap_nStartYMap + 512;
	}
	else if ( mViewMiniMap_nMultiple == _2ND_RATE )
	{
		rcView.left = mViewMiniMap_nStartXMap;
		rcView.top = mViewMiniMap_nStartYMap;
		rcView.right = mViewMiniMap_nStartXMap + 256;
		rcView.bottom = mViewMiniMap_nStartYMap + 256;
	}
	else if ( mViewMiniMap_nMultiple == _HALF_RATE )
	{
		rcView.left = mViewMiniMap_nStartXMap;
		rcView.top = mViewMiniMap_nStartYMap;
		rcView.right = mViewMiniMap_nStartXMap + 1024;
		rcView.bottom = mViewMiniMap_nStartYMap + 1024;
	}
	else if ( mViewMiniMap_nMultiple == _QUATER_RATE )
	{
		rcView.right = 512;
		rcView.bottom = 512;
	}

	if ( rcView.right > mViewMiniMap_rcMiniMapRect.right )
		rcView.right = mViewMiniMap_rcMiniMapRect.right;

	if ( rcView.bottom > mViewMiniMap_rcMiniMapRect.bottom )
		rcView.bottom = mViewMiniMap_rcMiniMapRect.bottom;
	
	// multiple이 1:1이면 원래 크기대로 rcView를 잡아주고 
	// 50% 면 rcView를 원래 크기보다 반씩 작게 해준다.
	if ( mViewMiniMap_nSelectedMapIdx >= 1000 )
	{
		if ( mViewMiniMap_xMinimapData2.NewSetIndex(mViewMiniMap_nSelectedMapIdx-1001) )
		{
			g_xMainWnd.DrawWithImageForComp(&rcView, (WORD*)mViewMiniMap_xMinimapData2.m_pbCurrImage, mViewMiniMap_pddsSurface);
		}
	}
	else
	{
		if ( mViewMiniMap_xMinimapData1.NewSetIndex(mViewMiniMap_nSelectedMapIdx-1) )
		{
			g_xMainWnd.DrawWithImageForComp(&rcView, (WORD*)mViewMiniMap_xMinimapData1.m_pbCurrImage, mViewMiniMap_pddsSurface);
		}
	}

	if ( mViewMiniMap_pddsSurface == NULL )
	{
		return;
	}

	INT nScrnX = m_rcWnd.left+197, nScrnY = m_rcWnd.top+16;

	nWidth = _SCRNMAP_WIDTH;
	nHeight = _SCRNMAP_HEIGHT;

	D3DMATERIAL7 mtrl;
	D3DVECTOR	vecTrans((FLOAT)nScrnX, (FLOAT)nScrnY, 0);
	D3DVECTOR	vecScale((FLOAT)nWidth, (FLOAT)nHeight, 1);

	D3DUtil_InitMaterial(mtrl, (FLOAT)150/255.0f, (FLOAT)150/255.0f, (FLOAT)150/255.0f);
	mtrl.diffuse.a = 255.0f/255.0f;

	g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, mViewMiniMap_pddsSurface);
}

HRESULT CViewMiniMapWnd::MiniMapSurface(LPDIRECT3DDEVICE7 pd3dDevice, INT nWidth, INT nHeight)
{
    D3DDEVICEDESC7 ddDesc;
    DDSURFACEDESC2 ddsd;

	mViewMiniMap_nMiniMapWidth  = nWidth;
	mViewMiniMap_nMiniMapHeight = nHeight;
/*
	INT nRealWidth, nRealHeight;

	if ( nWidth >= mViewMiniMap_rcMiniMapRect.right - mViewMiniMap_rcMiniMapRect.left )
	{
		nRealWidth = mViewMiniMap_rcMiniMapRect.right - mViewMiniMap_rcMiniMapRect.left;
	}
	else
	{
		nRealWidth = nWidth;
	}

	if ( nHeight >= mViewMiniMap_rcMiniMapRect.bottom - mViewMiniMap_rcMiniMapRect.top )
	{
		nRealHeight = mViewMiniMap_rcMiniMapRect.bottom - mViewMiniMap_rcMiniMapRect.top;
	}
	else
	{
		nRealHeight = nHeight;
	}
*/	
	SAFE_RELEASE(mViewMiniMap_pddsSurface);

    if( NULL == pd3dDevice )
	{
        return DDERR_INVALIDPARAMS;
	}

    if ( FAILED(pd3dDevice->GetCaps(&ddDesc)) )
	{
        return E_FAIL;
	}

    D3DUtil_InitSurfaceDesc( ddsd );
//	ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
//	ddsd.dwSize			 = sizeof(DDSURFACEDESC2);
    ddsd.dwFlags         = DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH/*|DDSD_TEXTURESTAGE*/;
    ddsd.ddsCaps.dwCaps  = DDSCAPS_TEXTURE;
	ddsd.dwTextureStage  = 0;    
    ddsd.dwWidth         = nWidth;
    ddsd.dwHeight        = nHeight;

    if ( ddDesc.deviceGUID == IID_IDirect3DHALDevice || ddDesc.deviceGUID == IID_IDirect3DTnLHalDevice )
	{
        ddsd.ddsCaps.dwCaps2 = DDSCAPS2_TEXTUREMANAGE;
	}
    else
	{
        ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
	}

	// 직사각형의 텍스춰를 지원하지 않는다면...
    if ( ddDesc.dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_SQUAREONLY )
    {
        if ( ddsd.dwWidth > ddsd.dwHeight ) ddsd.dwHeight = ddsd.dwWidth;
        else                                ddsd.dwWidth  = ddsd.dwHeight;
    }

    HRESULT hr = g_xMainWnd.GetDirectDraw()->CreateSurface(&ddsd, &mViewMiniMap_pddsSurface, NULL);

    if( FAILED(hr) )
	{
        return hr;
	}
	// 컬러키를 세팅한다.
	DDSetColorKey(mViewMiniMap_pddsSurface, RGB(0, 0, 0));

	return S_OK;
}


VOID CViewMiniMapWnd::SetMiniMapSize()
{
	mViewMiniMap_nStartYMap = 0;
	mViewMiniMap_nStartXMap = 0;
			
	if ( mViewMiniMap_nMultiple == _1ST_RATE )
	{
		mViewMiniMap_nMapHeight = mViewMiniMap_rcMiniMapRect.bottom - 512;
		mViewMiniMap_nMapWidth = mViewMiniMap_rcMiniMapRect.right - 512;
	}
	else if ( mViewMiniMap_nMultiple == _2ND_RATE )
	{
		mViewMiniMap_nMapHeight = mViewMiniMap_rcMiniMapRect.bottom - 256;
		mViewMiniMap_nMapWidth = mViewMiniMap_rcMiniMapRect.right - 256;
	}
	else if ( mViewMiniMap_nMultiple == _HALF_RATE )
	{
		mViewMiniMap_nMapHeight = mViewMiniMap_rcMiniMapRect.bottom - 570;
		mViewMiniMap_nMapWidth = mViewMiniMap_rcMiniMapRect.right - 714;
	}
	else if ( mViewMiniMap_nMultiple == _QUATER_RATE )
	{
		mViewMiniMap_nMapHeight = mViewMiniMap_rcMiniMapRect.bottom -800;
		mViewMiniMap_nMapWidth = mViewMiniMap_rcMiniMapRect.right - 1010;
	}

	if ( mViewMiniMap_nMapHeight < 0 )
		mViewMiniMap_nMapHeight = 0;

	if ( mViewMiniMap_nMapWidth < 0 )
		mViewMiniMap_nMapWidth = 0;
}
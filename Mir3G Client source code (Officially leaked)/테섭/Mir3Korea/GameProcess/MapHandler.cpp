/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/
#include "StdAfx.h"



/******************************************************************************************************************

	함수명 : CMapHandler::CMapHandler()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
CMapHandler::CMapHandler()
{
	InitMapHandler();
}



/******************************************************************************************************************

	함수명 : CMapHandler::~CMapHandler()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
CMapHandler::~CMapHandler()
{
	DestroyMapHandler();
}



/******************************************************************************************************************

	함수명 : CMapHandler::InitMapHandler()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CMapHandler::InitMapHandler()
{
	m_pstTileInfo		= NULL;
	m_pstCellInfo		= NULL;
//	m_pcPath			= NULL;
	m_bMapLoaded		= FALSE;
	m_bUseTileBuffer	= FALSE;
//	m_pstDoorInfo		= NULL;
//	m_pbCellIDoorIdx	= NULL;

	m_nStartViewTileX	= 0;	
	m_nStartViewTileY	= 0;
	m_nViewOffsetX		= 0;
	m_nViewOffsetY		= 0;
//	m_bDoorCount		= 0;

	m_ptMovePixelArray[0].x =  8; m_ptMovePixelArray[0].y =  5;
	m_ptMovePixelArray[1].x = 16; m_ptMovePixelArray[1].y = 11;
	m_ptMovePixelArray[2].x = 24; m_ptMovePixelArray[2].y = 16;
	m_ptMovePixelArray[3].x = 32; m_ptMovePixelArray[3].y = 21;
	m_ptMovePixelArray[4].x = 40; m_ptMovePixelArray[4].y = 27;
	m_ptMovePixelArray[5].x = 48; m_ptMovePixelArray[5].y = 32;

	m_bLightSize[0] = 4;
	m_bLightSize[1] = 8;
	m_bLightSize[2] = 12;
	m_bLightSize[3] = 20;

	m_nViewPosX = _VIEW_CELL_X_START;
	m_nViewPosY = _VIEW_CELL_Y_START;

	m_stRGBInfo[0].bRed = 214; m_stRGBInfo[0].bGreen = 198; m_stRGBInfo[0].bBlue = 173;
	m_stRGBInfo[1].bRed = 165; m_stRGBInfo[1].bGreen = 140; m_stRGBInfo[1].bBlue =  90;
	m_stRGBInfo[2].bRed = 115; m_stRGBInfo[2].bGreen =  57; m_stRGBInfo[2].bBlue =  41;
	m_stRGBInfo[3].bRed =  99; m_stRGBInfo[3].bGreen = 198; m_stRGBInfo[3].bBlue = 222;
	m_stRGBInfo[4].bRed =  49; m_stRGBInfo[4].bGreen = 115; m_stRGBInfo[4].bBlue =  41;
	m_stRGBInfo[5].bRed = 255; m_stRGBInfo[5].bGreen = 255; m_stRGBInfo[5].bBlue = 255;
	m_stRGBInfo[6].bRed = 255; m_stRGBInfo[6].bGreen = 255; m_stRGBInfo[6].bBlue = 255;
	m_stRGBInfo[7].bRed = 255; m_stRGBInfo[7].bGreen = 255; m_stRGBInfo[7].bBlue = 255;
	m_stRGBInfo[8].bRed = 255; m_stRGBInfo[8].bGreen = 255; m_stRGBInfo[8].bBlue = 255;
	m_stRGBInfo[9].bRed = 255; m_stRGBInfo[9].bGreen = 255; m_stRGBInfo[9].bBlue = 255;


	ZeroMemory(m_wSavedMapBuffer, sizeof(WORD)*_VIEW_CELL_X_COUNT*_CELL_WIDTH*_VIEW_CELL_Y_COUNT*_CELL_HEIGHT);
	ZeroMemory(m_bAniTileFrame, sizeof(BYTE)*8*16);
	ZeroMemory(m_dwAniSaveTime, sizeof(DWORD)*8);
	ZeroMemory(&m_stMapFileHeader, sizeof(MAPFILEHEADER));
	ZeroMemory(&m_pszMapName, MAX_PATH);

	SetRect(&m_rcView, 0, 0, _VIEW_CELL_X_COUNT*_CELL_WIDTH, _VIEW_CELL_Y_COUNT*_CELL_HEIGHT);
	SetRect(&m_rcMemView, 0, 0, _MEMVIEW_CELL_X_COUNT, _MEMVIEW_CELL_Y_COUNT);
}



/******************************************************************************************************************

	함수명 : CMapHandler::DestroyMapHandler()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CMapHandler::DestroyMapHandler()
{
//	INT nCnt;

	SAFE_DELETEARR(m_pstTileInfo);
	SAFE_DELETEARR(m_pstCellInfo);
//	SAFE_DELETEARR(m_pcPath);
/*	for ( nCnt = 0; nCnt < m_bDoorCount; nCnt++ )
	{
		SAFE_DELETE(m_pstDoorInfo[nCnt].pstDoorImgInfo);
	}
	SAFE_DELETE(m_pstDoorInfo);
	SAFE_DELETE(m_pbCellIDoorIdx);*/

	InitMapHandler();
}



VOID CMapHandler::LoadMemViewBuffer(INT nX, INT nY/*, INT nLoopTime*/)
{
/*	BOOL bIdle = FALSE;
	INT nLimitX = _MEMVIEW_CELL_X_COUNT;
	INT nLimitY = _MEMVIEW_CELL_Y_COUNT;
	if ( nLoopTime < 40 && (g_xGameProc.m_xMyHero.m_bCurrMtn == _MT_STAND || g_xGameProc.m_xMyHero.m_bCurrMtn == _MT_HORSESTAND || g_xGameProc.m_xMyHero.m_bCurrMtn == _MT_ATTACKMODE) )
	{
		nLimitX = _MEMVIEW_CELL_X_COUNT*2;
		nLimitY = _MEMVIEW_CELL_Y_COUNT*2;
		bIdle	= TRUE;
	}
*/

	if ( m_rcMemView.left > nX-_VIEW_CELL_X_COUNT/2 || m_rcMemView.right  < nX+_VIEW_CELL_X_COUNT/2 ||
	     m_rcMemView.top  > nY-_VIEW_CELL_X_COUNT/2 || m_rcMemView.bottom < nY+_VIEW_CELL_X_COUNT/2 /*|| bIdle*/ )
	{
		INT	 nFileIdx, nObjFileIdx1, nObjFileIdx2, nImgIdx, nImgIdx1, nImgIdx2, nArrayNum;

//		SetRect(&m_rcMemView, nX-nLimitX/2, nY-nLimitY/2, nX+nLimitX/2, nY+nLimitY/2);
		SetRect(&m_rcMemView, nX-_MEMVIEW_CELL_X_COUNT/2, nY-_MEMVIEW_CELL_Y_COUNT/2, nX+_MEMVIEW_CELL_X_COUNT/2, nY+_MEMVIEW_CELL_Y_COUNT/2);

		for ( INT nCntX = m_rcMemView.left; nCntX < m_rcMemView.right; nCntX++ )
		{
			for ( INT nCntY = m_rcMemView.top; nCntY < m_rcMemView.bottom; nCntY++ )
			{
				if ( nCntX >= m_stMapFileHeader.shWidth || nCntY >= m_stMapFileHeader.shHeight || nCntX < 0 || nCntY < 0 )
				{
					continue;
				}

				// 타일.
				if( !( nCntX % 2 ) && !( nCntY % 2 ) )
 				{
					nArrayNum = (nCntY/2) + (nCntX/2)*m_stMapFileHeader.shHeight/2;

					nFileIdx= m_pstTileInfo[nArrayNum].bFileIdx;
					nImgIdx = m_pstTileInfo[nArrayNum].wTileIdx;

					// 맵데이타는 15개 단위로 세팅되있다.
					nFileIdx -= nFileIdx/15;

					// 타일 파일이 아니다.
					if ( nFileIdx % 14 <= 2 && nFileIdx <= 69 )
					{
						if( nImgIdx != 65535 )
						{
							g_xGameProc.m_xImage.m_xImageList[nFileIdx].NewSetIndex(nImgIdx);
						}
					}
				}

				// 오브젝트.
				nArrayNum = nCntY + nCntX*m_stMapFileHeader.shHeight;

				if ( m_pstCellInfo[nArrayNum].wFileIdx != 65535 )
				{			
					// 오브젝트1.
					nObjFileIdx1 = (m_pstCellInfo[nArrayNum].wFileIdx & 0XFF00) >> 8;
					nImgIdx1     = m_pstCellInfo[nArrayNum].wObj1;

					// 오브젝트2.
					nObjFileIdx2 = (m_pstCellInfo[nArrayNum].wFileIdx & 0XFF);
					nImgIdx2     = m_pstCellInfo[nArrayNum].wObj2;

					// 맵데이타는 15개 단위로 세팅되있다.
					nObjFileIdx1 -= nObjFileIdx1/15;
					nObjFileIdx2 -= nObjFileIdx2/15;

					// 오브젝트 파일이 아니다.
					if ( nObjFileIdx1 % 14 > 2 && nObjFileIdx1 <= 69 )
					{
						g_xGameProc.m_xImage.m_xImageList[nObjFileIdx1].NewSetIndex(nImgIdx1);
					}
					if ( nObjFileIdx2 % 14 > 2 && nObjFileIdx2 <= 69 )
					{
						g_xGameProc.m_xImage.m_xImageList[nObjFileIdx2].NewSetIndex(nImgIdx2);
					}
				}
			}
		}
	}
}




/******************************************************************************************************************

	함수명 : CMapHandler::LoadNewMapBuffer()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CMapHandler::LoadNewMapBuffer()
{
	INT nFileIdx, nImgIdx;
	INT nXCnt, nYCnt;

	if ( m_bMapLoaded == FALSE )
	{
		return;
	}

	ZeroMemory(m_wSavedMapBuffer, sizeof(WORD)*_VIEW_CELL_X_COUNT*_CELL_WIDTH*_VIEW_CELL_Y_COUNT*_CELL_HEIGHT);

	for ( nXCnt = m_nStartViewTileX; nXCnt < m_nStartViewTileX+_VIEW_CELL_X_COUNT; nXCnt++ )
		for ( nYCnt = m_nStartViewTileY; nYCnt < m_nStartViewTileY+_VIEW_CELL_Y_COUNT; nYCnt++ )
	{
		if ( nXCnt >= m_stMapFileHeader.shWidth || nYCnt >= m_stMapFileHeader.shHeight || nXCnt < 0 || nYCnt < 0 )
		{
			continue; 
		}

		if( !( nXCnt % 2 ) && !( nYCnt % 2 ) && nYCnt < m_nStartViewTileY+_VIEW_CELL_Y_COUNT && m_pstTileInfo )
 		{
 			nFileIdx= m_pstTileInfo[(nYCnt/2) + (nXCnt/2)*m_stMapFileHeader.shHeight/2].bFileIdx;
			nImgIdx = m_pstTileInfo[(nYCnt/2) + (nXCnt/2)*m_stMapFileHeader.shHeight/2].wTileIdx;

			// 맵데이타는 15개 단위로 세팅되있다.
			nFileIdx -= nFileIdx/15;

			// 타일 파일이 아니다.
			if ( nFileIdx % 14 > 2 || nFileIdx > 69 )
			{
				continue;
			}

 			if( nImgIdx != 65535 )
			{
				if ( g_xGameProc.m_xImage.m_xImageList[nFileIdx].NewSetIndex(nImgIdx) )
				{
					g_xMainWnd.DrawWithImageForCompMemToMem(
									(nXCnt-m_nStartViewTileX)*_CELL_WIDTH ,
									(nYCnt-m_nStartViewTileY)*_CELL_HEIGHT,
									g_xGameProc.m_xImage.m_xImageList[nFileIdx].m_lpstNewCurrWilImageInfo->shWidth,
									g_xGameProc.m_xImage.m_xImageList[nFileIdx].m_lpstNewCurrWilImageInfo->shHeight,
									(WORD*)g_xGameProc.m_xImage.m_xImageList[nFileIdx].m_pbCurrImage,
									_VIEW_CELL_X_COUNT*_CELL_WIDTH, _VIEW_CELL_Y_COUNT*_CELL_HEIGHT, m_wSavedMapBuffer);
				}				
			}
		}
	}
}



/******************************************************************************************************************

	함수명 : CMapHandler::LoadMapData()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : CHAR* szMapFile
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CMapHandler::LoadMapData(CHAR* szMapFile)
{
	HANDLE	hFile = INVALID_HANDLE_VALUE;
	INT		nCnt;
	char	szFullPath[128];

	if ( hFile == INVALID_HANDLE_VALUE  )
	{
		sprintf(szFullPath, ".\\Map\\%s.map", szMapFile);
		strcpy(m_pszMapName, szMapFile);
		hFile = CreateFile(szFullPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	}

	if ( hFile != INVALID_HANDLE_VALUE )
	{
		DWORD		dwReadLen;

		FreeMapData();

		ReadFile(hFile, &m_stMapFileHeader, sizeof(MAPFILEHEADER), &dwReadLen, NULL);

		m_pstTileInfo = new TILEINFO[(m_stMapFileHeader.shWidth*m_stMapFileHeader.shHeight)/4];
		ReadFile(hFile, m_pstTileInfo, sizeof(TILEINFO)*(m_stMapFileHeader.shWidth*m_stMapFileHeader.shHeight)/4, &dwReadLen, NULL);
		m_pstCellInfo = new CELLINFO[m_stMapFileHeader.shWidth*m_stMapFileHeader.shHeight];
		ReadFile(hFile, m_pstCellInfo, sizeof(CELLINFO)*(m_stMapFileHeader.shWidth*m_stMapFileHeader.shHeight), &dwReadLen, NULL);

/*		m_pcPath = new CHAR[m_stMapFileHeader.shWidth*m_stMapFileHeader.shHeight];
		ZeroMemory(m_pcPath, sizeof(CHAR)*m_stMapFileHeader.shWidth*m_stMapFileHeader.shHeight);
*/
		m_bMapLoaded = TRUE;
		m_bUseTileBuffer = TRUE;

		if ( m_stMapFileHeader.shWidth < 100 && m_stMapFileHeader.shHeight < 100 )
		{
			m_bUseTileBuffer = FALSE;
		}

		for ( nCnt = 14; nCnt < 70; nCnt++ )
		{
			// 확장맵 이미지 데이타 삭제.
			g_xGameProc.m_xImage.m_xImageList[nCnt].Destroy();
		}
		// 확장맵 이미지데이타 로드.
		if (m_stMapFileHeader.wAttr == 2)
			m_stMapFileHeader.wAttr = 3;
		else if (m_stMapFileHeader.wAttr == 3)
			m_stMapFileHeader.wAttr = 2;						//	정글 설원 속성 변경으로 인한 삽질 -_-;

		BYTE bRegionMapStart = m_stMapFileHeader.wAttr*14+14;

/*		// 메모리에 올릴것.
		for ( nCnt = bRegionMapStart; nCnt < bRegionMapStart+1; nCnt++ )
		{
			g_xGameProc.m_xImage.m_xImageList[bRegionMapStart].NewLoad(g_xGameProc.m_xImage.m_pszFileList[nCnt], 2);
		}
*/
		// 메모리맵, 안되면 캐쉬.
		for ( nCnt = bRegionMapStart; nCnt < bRegionMapStart+14; nCnt++ )
		{
			if ( !g_xGameProc.m_xImage.m_xImageList[nCnt].NewLoad(g_xGameProc.m_xImage.m_pszFileList[nCnt], 1) )
			{
				g_xGameProc.m_xImage.m_xImageList[nCnt].Destroy();
				g_xGameProc.m_xImage.m_xImageList[nCnt].NewLoad(g_xGameProc.m_xImage.m_pszFileList[nCnt]);
			}
		}

		if ( m_bUseTileBuffer )
		{
			LoadNewMapBuffer();
		}

		CloseHandle(hFile);
		return TRUE;
	}

	return FALSE;
}



/******************************************************************************************************************

	함수명 : CMapHandler::FreeMapData()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CMapHandler::FreeMapData()
{
	ZeroMemory(&m_stMapFileHeader, sizeof(MAPFILEHEADER));
	ZeroMemory(m_wSavedMapBuffer, sizeof(WORD)*_VIEW_CELL_X_COUNT*_CELL_WIDTH*_VIEW_CELL_Y_COUNT*_CELL_HEIGHT);
	SAFE_DELETEARR(m_pstTileInfo);
	SAFE_DELETEARR(m_pstCellInfo);
	m_bMapLoaded = FALSE;
/*	for ( INT nCnt = 0; nCnt < m_bDoorCount; nCnt++ )
	{
		SAFE_DELETE(m_pstDoorInfo[nCnt].pstDoorImgInfo);
	}
	SAFE_DELETE(m_pstDoorInfo);
	SAFE_DELETE(m_pbCellIDoorIdx);
	m_bDoorCount = 0;*/
}


/*
BOOL CMapHandler::PathFinding(INT nSX, INT nSY, INT nEX, INT nEY)
{
	// 이전 패스를 지운다.
	ZeroMemory(m_pcPath, sizeof(CHAR)*m_stMapFileHeader.shWidth*m_stMapFileHeader.shHeight);

	CMapNode startNode(nSX, nSY);
	CMapNode goalNode(nEX, nEY);

	m_xPathFinder.SetState( &startNode, &goalNode );

	// 길을 찾는다.
	// 아래 루프는 이동 경로가 클 경우 오래 걸릴 수 있으므로 몇번씩 나누어서 호출할 수 있다.
	INT searchResult;
	while ( (searchResult = m_xPathFinder.SearchStep()) == CAStar<CMapNode>::SEARCH_STATE_SEARCHING );

	if ( searchResult != CAStar<CMapNode>::SEARCH_STATE_SUCCEEDED )
		return FALSE;

	CMapNode *pPath = m_xPathFinder.GetPathFirst();
	m_pcPath[pPath->x + pPath->y*m_stMapFileHeader.shHeight] = PATH;

	while ( pPath = m_xPathFinder.GetPathNext() )
		m_pcPath[pPath->x + pPath->y*m_stMapFileHeader.shHeight] = PATH;

	return TRUE;
}
*/

/******************************************************************************************************************

	함수명 : CMapHandler::ScrollMap()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : INT nCharDir
	         INT nCharFrame
	         INT nSpeed
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CMapHandler::ScrollMap(INT nCharDir, INT nCharFrame, INT nSpeed)
{
	nCharFrame %= 10;

	switch ( nCharDir )
	{
	// 직선 위로 이동.
	case _DIRECTION_LIST_1:	
		m_nViewOffsetY = -(m_ptMovePixelArray[nCharFrame].y * nSpeed);		
		break;
	// 오른쪽위로 이동.
	case _DIRECTION_LIST_2:
		m_nViewOffsetX =  (m_ptMovePixelArray[nCharFrame].x * nSpeed);
		m_nViewOffsetY = -(m_ptMovePixelArray[nCharFrame].y * nSpeed);
		break;
	// 오른쪽으로 이동.
	case _DIRECTION_LIST_3:
		m_nViewOffsetX =  (m_ptMovePixelArray[nCharFrame].x * nSpeed);
		break;
	// 오른쪽아래로 이동.
	case _DIRECTION_LIST_4:
		m_nViewOffsetX =  (m_ptMovePixelArray[nCharFrame].x * nSpeed);
		m_nViewOffsetY =  (m_ptMovePixelArray[nCharFrame].y * nSpeed);
		break;
	// 직선 아래로 이동.
	case _DIRECTION_LIST_5:
		m_nViewOffsetY =  (m_ptMovePixelArray[nCharFrame].y * nSpeed);
		break;
	// 왼쪽아래로 이동.
	case _DIRECTION_LIST_6:
		m_nViewOffsetX = -(m_ptMovePixelArray[nCharFrame].x * nSpeed);
		m_nViewOffsetY =  (m_ptMovePixelArray[nCharFrame].y * nSpeed);
		break;
	// 왼쪽으로 이동.
	case _DIRECTION_LIST_7:
		m_nViewOffsetX = -(m_ptMovePixelArray[nCharFrame].x * nSpeed);
		break;
	// 왼쪽위로 이동.
	case _DIRECTION_LIST_8:
		m_nViewOffsetX = -(m_ptMovePixelArray[nCharFrame].x * nSpeed);
		m_nViewOffsetY = -(m_ptMovePixelArray[nCharFrame].y * nSpeed);
		break;
	}
}



VOID CMapHandler::ScrollMap(INT nCharDir, WORD wCurrDelay, WORD wMoveDelay, INT nSpeed)
{
	if ( wMoveDelay == 0 )
	{
		return;
	}

	FLOAT fViewOffSetX = (FLOAT)((FLOAT)((wCurrDelay+1)/wMoveDelay) * _CELL_WIDTH ) * nSpeed;
	FLOAT fViewOffSetY = (FLOAT)((FLOAT)((wCurrDelay+1)/wMoveDelay) * _CELL_HEIGHT) * nSpeed;

	switch ( nCharDir )
	{
	// 직선 위로 이동.
	case _DIRECTION_LIST_1:	
		m_nViewOffsetY -= (SHORT)-fViewOffSetY;
		break;
	// 오른쪽위로 이동.
	case _DIRECTION_LIST_2:
		m_nViewOffsetX = (SHORT)fViewOffSetX;
		m_nViewOffsetY = (SHORT)-fViewOffSetY;
		break;
	// 오른쪽으로 이동.
	case _DIRECTION_LIST_3:
		m_nViewOffsetX = (SHORT)fViewOffSetX;
		break;
	// 오른쪽아래로 이동.
	case _DIRECTION_LIST_4:
		m_nViewOffsetX = (SHORT)fViewOffSetX;
		m_nViewOffsetY = (SHORT)fViewOffSetY;
		break;
	// 직선 아래로 이동.
	case _DIRECTION_LIST_5:
		m_nViewOffsetY = (SHORT)fViewOffSetY;
		break;
	// 왼쪽아래로 이동.
	case _DIRECTION_LIST_6:
		m_nViewOffsetX = (SHORT)-fViewOffSetX;
		m_nViewOffsetY = (SHORT)fViewOffSetY;
		break;
	// 왼쪽으로 이동.
	case _DIRECTION_LIST_7:
		m_nViewOffsetX = (SHORT)-fViewOffSetX;
		break;
	// 왼쪽위로 이동.
	case _DIRECTION_LIST_8:
		m_nViewOffsetX = (SHORT)fViewOffSetX;
		m_nViewOffsetY = (SHORT)-fViewOffSetY;
		break;
	}
}



/******************************************************************************************************************

	함수명 : CMapHandler::DrawBaseTile()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : INT nX
	         INT nY
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CMapHandler::DrawBaseTile(INT nX, INT nY)
{
	INT nFileIdx;
	INT nImgIdx;

	if ( m_bMapLoaded == FALSE )
	{
		return;
	}

	if ( nX >= m_stMapFileHeader.shWidth || nY >= m_stMapFileHeader.shHeight || nX < 0 || nY < 0 )
	{
		return; 
	}

 	if( !( nX % 2 ) && !( nY % 2 ) && nY < m_nStartViewTileY+_VIEW_CELL_Y_COUNT && m_pstTileInfo )
 	{
		nFileIdx= m_pstTileInfo[(nY/2) + (nX/2)*m_stMapFileHeader.shHeight/2].bFileIdx;
		nImgIdx = m_pstTileInfo[(nY/2) + (nX/2)*m_stMapFileHeader.shHeight/2].wTileIdx;

		// 맵데이타는 15개 단위로 세팅되있다.
		nFileIdx -= nFileIdx/15;

		// 타일 파일이 아니다.
		if ( nFileIdx % 14 > 2 || nFileIdx > 69 )
		{
			return;
		}

		if( nImgIdx != 65535 )
		{
			if ( g_xGameProc.m_xImage.m_xImageList[nFileIdx].NewSetIndex(nImgIdx) )
			{
				g_xMainWnd.DrawWithImageForCompMemToMem(
								(nX-m_nStartViewTileX)*_CELL_WIDTH ,
								(nY-m_nStartViewTileY)*_CELL_HEIGHT,
								g_xGameProc.m_xImage.m_xImageList[nFileIdx].m_lpstNewCurrWilImageInfo->shWidth,
								g_xGameProc.m_xImage.m_xImageList[nFileIdx].m_lpstNewCurrWilImageInfo->shHeight,
								(WORD*)g_xGameProc.m_xImage.m_xImageList[nFileIdx].m_pbCurrImage,
								_VIEW_CELL_X_COUNT*_CELL_WIDTH, _VIEW_CELL_Y_COUNT*_CELL_HEIGHT, m_wSavedMapBuffer);
			}
		}
	}
}



VOID CMapHandler::DrawObjOneCellTile(INT nX, INT nY, BYTE bObjNum)
{	
/*	if ( m_bMapLoaded == FALSE )
	{
		return;
	}
*/
	// 오브젝트가 있을때.
	INT nArrayNum = nY + nX*m_stMapFileHeader.shHeight;

	if ( m_pstCellInfo[nArrayNum].wFileIdx != 65535 )
	{
		INT  nObjFileIdx = 0;
		INT  nImgIdx	 = 0;
		
		// 오브젝트1.
		if ( bObjNum == 0 )
		{
			nObjFileIdx = (m_pstCellInfo[nArrayNum].wFileIdx & 0XFF00) >> 8;
			nImgIdx	    = m_pstCellInfo[nArrayNum].wObj1;
		}
		// 오브젝트2.
		else
		{
			nObjFileIdx = (m_pstCellInfo[nArrayNum].wFileIdx & 0XFF);
			nImgIdx	    = m_pstCellInfo[nArrayNum].wObj2;
		}

		// 맵데이타는 15개 단위로 세팅되있다.
		nObjFileIdx -= nObjFileIdx/15;

		// 오브젝트 파일이 아니다.
		if ( nObjFileIdx % 14 < 3 || nObjFileIdx > 69 )
		{
			return;
		}

		if ( nImgIdx != 65535 )
		{
			CWHWilImageData* pxTileImg = &g_xGameProc.m_xImage.m_xImageList[nObjFileIdx];

			if ( pxTileImg->NewSetIndex(nImgIdx) )
			{
				if ( pxTileImg->m_lpstNewCurrWilImageInfo->shWidth == 48 && pxTileImg->m_lpstNewCurrWilImageInfo->shHeight == 32 )
				{
					BOOL bBlend	 = FALSE;
					BYTE bObjAni = 0;

//					nImgIdx += GetDoorImgIdx(nX, nY);

					// 오브젝트1.
					if ( bObjNum == 0 )
					{
						bObjAni = m_pstCellInfo[nArrayNum].bObj1Ani;
					}
					// 오브젝트2.
					else
					{
						bObjAni = m_pstCellInfo[nArrayNum].bObj2Ani;
					}

					// 애니메이션 오브젝트이면.
					if ( bObjAni != 255 )
					{
						BYTE  bTickType;
						INT	  nAniCnt;
						
						bTickType = (BYTE)((bObjAni & 0X70) >> 4);
						nAniCnt = bObjAni & 0X0F;
						
						if ( (bObjAni & 0X80) >> 7 )
						{
							bBlend = TRUE;
						}

						nImgIdx += m_bAniTileFrame[bTickType][nAniCnt];
					}

					if ( pxTileImg->NewSetIndex(nImgIdx) )
					{
						if ( !bBlend )
						{
							g_xMainWnd.DrawWithImageForCompClipRgn(
							(nX-m_nStartViewTileX)*_CELL_WIDTH +m_nViewPosX-m_nViewOffsetX,
							(nY-m_nStartViewTileY)*_CELL_HEIGHT+m_nViewPosY-pxTileImg->m_lpstNewCurrWilImageInfo->shHeight+_CELL_HEIGHT-m_nViewOffsetY,
							pxTileImg->m_lpstNewCurrWilImageInfo->shWidth,
							pxTileImg->m_lpstNewCurrWilImageInfo->shHeight,
							(WORD*)pxTileImg->m_pbCurrImage,
							_CLIP_WIDTH, _CLIP_HEIGHT);
						}
						else
						{
							INT nStartX = (nX-m_nStartViewTileX)*_CELL_WIDTH +m_nViewPosX-m_nViewOffsetX;
							INT nStartY = (nY-m_nStartViewTileY)*_CELL_HEIGHT+m_nViewPosY-pxTileImg->m_lpstNewCurrWilImageInfo->shHeight+_CELL_HEIGHT-m_nViewOffsetY;

							D3DMATERIAL7 mtrl;
							D3DVECTOR	vecTrans((FLOAT)nStartX, (FLOAT)nStartY, 0);
							D3DVECTOR	vecScale(pxTileImg->m_lpstNewCurrWilImageInfo->shWidth, pxTileImg->m_lpstNewCurrWilImageInfo->shHeight, 1);
							LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_MAP, (WORD)nObjFileIdx, nImgIdx);

							D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)255/255.0f, (FLOAT)255/255.0f);
							mtrl.diffuse.a = 1.0f/255.0f;
							g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr, _BLEND_LIGHTINV);
						}
					}
				}
			}
		}
	}
}


VOID CMapHandler::DrawObjTile(INT nX, INT nY, BYTE bObjNum)
{	
/*	if ( m_bMapLoaded == FALSE )
	{
		return;
	}
*/
	// 오브젝트가 있을때.
	INT nArrayNum = nY + nX*m_stMapFileHeader.shHeight;

	if ( m_pstCellInfo[nArrayNum].wFileIdx != 65535 )
	{
		INT  nObjFileIdx = 0;
		INT  nImgIdx	 = 0;
		
		// 오브젝트1.
		if ( bObjNum == 0 )
		{
			nObjFileIdx = (m_pstCellInfo[nArrayNum].wFileIdx & 0XFF00) >> 8;
			nImgIdx	    = m_pstCellInfo[nArrayNum].wObj1;
		}
		// 오브젝트2.
		else
		{
			nObjFileIdx = (m_pstCellInfo[nArrayNum].wFileIdx & 0XFF);
			nImgIdx	    = m_pstCellInfo[nArrayNum].wObj2;
		}

		// 맵데이타는 15개 단위로 세팅되있다.
		nObjFileIdx -= nObjFileIdx/15;

		// 오브젝트 파일이 아니다.
		if ( nObjFileIdx % 14 < 3 || nObjFileIdx > 69 )
		{
			return;
		}

		if ( nImgIdx != 65535 )
		{
			CWHWilImageData* pxTileImg = &g_xGameProc.m_xImage.m_xImageList[nObjFileIdx];

			if ( pxTileImg->NewSetIndex(nImgIdx) )
			{
				if ( !(pxTileImg->m_lpstNewCurrWilImageInfo->shWidth == 48 && pxTileImg->m_lpstNewCurrWilImageInfo->shHeight == 32) )
				{
					BOOL bBlend	 = FALSE;
					BYTE bObjAni = 0;

//					nImgIdx += GetDoorImgIdx(nX, nY);

					// 오브젝트1.
					if ( bObjNum == 0 )
					{
						bObjAni = m_pstCellInfo[nArrayNum].bObj1Ani;
					}
					// 오브젝트2.
					else
					{
						bObjAni = m_pstCellInfo[nArrayNum].bObj2Ani;
					}

					// 애니메이션 오브젝트이면.
					if ( bObjAni != 255 )
					{
						BYTE  bTickType;
						INT	  nAniCnt;
						
						bTickType = (BYTE)((bObjAni & 0X70) >> 4);
						nAniCnt = bObjAni & 0X0F;
						
						if ( (bObjAni & 0X80) >> 7 )
						{
							bBlend = TRUE;
						}

						nImgIdx += m_bAniTileFrame[bTickType][nAniCnt];
					}

					if ( pxTileImg->NewSetIndex(nImgIdx) )
					{
						if ( !bBlend )
						{
							g_xMainWnd.DrawWithImageForCompClipRgn(
							(nX-m_nStartViewTileX)*_CELL_WIDTH +m_nViewPosX-m_nViewOffsetX,
							(nY-m_nStartViewTileY)*_CELL_HEIGHT+m_nViewPosY-pxTileImg->m_lpstNewCurrWilImageInfo->shHeight+_CELL_HEIGHT-m_nViewOffsetY,
							pxTileImg->m_lpstNewCurrWilImageInfo->shWidth,
							pxTileImg->m_lpstNewCurrWilImageInfo->shHeight,
							(WORD*)pxTileImg->m_pbCurrImage,
							_CLIP_WIDTH, _CLIP_HEIGHT);
						}
						else
						{
							INT nStartX = (nX-m_nStartViewTileX)*_CELL_WIDTH +m_nViewPosX-m_nViewOffsetX;
							INT nStartY = (nY-m_nStartViewTileY)*_CELL_HEIGHT+m_nViewPosY-pxTileImg->m_lpstNewCurrWilImageInfo->shHeight+_CELL_HEIGHT-m_nViewOffsetY;

							D3DMATERIAL7 mtrl;
							D3DVECTOR	vecTrans((FLOAT)nStartX, (FLOAT)nStartY, 0);
							D3DVECTOR	vecScale(pxTileImg->m_lpstNewCurrWilImageInfo->shWidth, pxTileImg->m_lpstNewCurrWilImageInfo->shHeight, 1);
							LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_MAP, (WORD)nObjFileIdx, nImgIdx);

							D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)255/255.0f, (FLOAT)255/255.0f);
							mtrl.diffuse.a = 1.0f/255.0f;
							g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr, _BLEND_LIGHTINV);
						}
					}
				}
			}
		}
	}
}






/******************************************************************************************************************

	함수명 : CMapHandler::DrawOpenDoor()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : INT nX
	         INT nY
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
/*VOID CMapHandler::DrawOpenDoor(INT nX, INT nY)
{
	if ( GetDoorState(nX, nY) )
	{
		BYTE bDoorIndex = m_pbCellIDoorIdx[nX + nY*m_stMapFileHeader.shWidth];
		for ( INT nCnt = 0; nCnt < m_bDoorCount; nCnt++ )
		{
			if ( m_pstDoorInfo[nCnt].bDoorIdx == bDoorIndex )
			{
				for ( INT nLoop = 0; nLoop < m_pstDoorInfo[nCnt].bDoorImgCnt; nLoop++ )
				{
					WORD wPosX = m_pstDoorInfo[nCnt].pstDoorImgInfo[nLoop].wPosX;
					WORD wPosY = m_pstDoorInfo[nCnt].pstDoorImgInfo[nLoop].wPosY;
					if ( nX == wPosX && nY == wPosY )
					{
						WORD wImgIndex = m_pstDoorInfo[nCnt].pstDoorImgInfo[nLoop].wImageNum;						
						// 그림을 그린다.

						// ".\\Data\\housesc.wil"
						m_pxTileImg[4].NewSetIndex(wImgIndex);

						g_xMainWnd.DrawWithImageForCompClipRgn(
						(nX-m_nStartViewTileX)*_CELL_WIDTH +m_nViewPosX-m_nViewOffsetX,
						(nY-m_nStartViewTileY)*_CELL_HEIGHT+m_nViewPosY-m_pxTileImg[4].m_lpstNewCurrWilImageInfo->shHeight+_CELL_HEIGHT-m_nViewOffsetY,
						m_pxTileImg[4].m_lpstNewCurrWilImageInfo->shWidth,
						m_pxTileImg[4].m_lpstNewCurrWilImageInfo->shHeight,
						(WORD*)m_pxTileImg[4].m_pbCurrImage,
						_CLIP_WIDTH, _CLIP_HEIGHT);
						break;
					}
				}
			}
		}
	}
}


VOID CMapHandler::SetDoorIndex()
{
	for ( INT nCnt = 0; nCnt < m_bDoorCount; nCnt++ )
	{
		for ( INT nLoop = 0; nLoop < m_pstDoorInfo[nCnt].bDoorImgCnt; nLoop++ )
		{
			WORD wPosX = m_pstDoorInfo[nCnt].pstDoorImgInfo[nLoop].wPosX;
			WORD wPosY = m_pstDoorInfo[nCnt].pstDoorImgInfo[nLoop].wPosY;
			m_pbCellIDoorIdx[wPosX + wPosY*m_stMapFileHeader.shWidth] = m_pstDoorInfo[nCnt].bDoorIdx;
		}
	}
}


BOOL CMapHandler::GetDoorState(INT nX, INT nY)
{
	if ( (nX == 432 || nX == 433) && (nY == 70 || nY == 71 ||nY == 72 ) )
		int a = 0;
	if ( (m_pstCellInfo[nX + nY*m_stMapFileHeader.shWidth].wLigntNEvent == 65535) ||
		 !(m_pstCellInfo[nX + nY*m_stMapFileHeader.shWidth].wLigntNEvent & 0X08) )
		return FALSE;

	// 문이열려있다.
	return TRUE;
}


VOID CMapHandler::SetDoorState(BYTE bIndex, BOOL bDoorOpen)
{
	for ( INT nCnt = 0; nCnt < m_bDoorCount; nCnt++ )
	{
		if ( m_pstDoorInfo[nCnt].bDoorIdx == bIndex )
		{
			for ( INT nLoop = 0; nLoop < m_pstDoorInfo[nCnt].bDoorImgCnt; nLoop++ )
			{
				WORD wPosX = m_pstDoorInfo[nCnt].pstDoorImgInfo[nLoop].wPosX;
				WORD wPosY = m_pstDoorInfo[nCnt].pstDoorImgInfo[nLoop].wPosY;
				
				if ( bDoorOpen )
					m_pstCellInfo[wPosX + wPosY*m_stMapFileHeader.shWidth].wLigntNEvent = m_pstCellInfo[wPosX + wPosY*m_stMapFileHeader.shWidth].wLigntNEvent | 0X08;
				else
					m_pstCellInfo[wPosX + wPosY*m_stMapFileHeader.shWidth].wLigntNEvent = m_pstCellInfo[wPosX + wPosY*m_stMapFileHeader.shWidth].wLigntNEvent & 0XFFF7;
			}
		}
	}
}
*/



INT	CMapHandler::GetDoor(INT nX, INT nY)
{
	INT nResult = 0;

	if ( m_bMapLoaded == FALSE || m_pstCellInfo == NULL )
	{
		return nResult;
	}

	if ( nX >= m_stMapFileHeader.shWidth || nY >= m_stMapFileHeader.shHeight )
	{
		return nResult;
	}

 	if ( ((m_pstCellInfo[nY + nX*m_stMapFileHeader.shHeight].bDoorIdx & 0X80) > 0) )
	{
		nResult = m_pstCellInfo[nY + nX*m_stMapFileHeader.shHeight].bDoorIdx & 0X7F;
	}

	return nResult;
/*
	INT nResult = 0;

 	if ( m_pstCellInfo[nY + nX*m_stMapFileHeader.shHeight].bDoorIdx )
	{
		nResult = m_pstCellInfo[nY + nX*m_stMapFileHeader.shHeight].bDoorIdx & 0X7F;
	}

	return nResult;
*/}


BOOL CMapHandler::IsDoorOpen(INT nX, INT nY)
{
	if ( m_bMapLoaded == FALSE || m_pstCellInfo == NULL )
	{
		return FALSE;
	}

	if ( nX >= m_stMapFileHeader.shWidth || nY >= m_stMapFileHeader.shHeight )
	{
		return FALSE;
	}

	if ( ((m_pstCellInfo[nY + nX*m_stMapFileHeader.shHeight].bDoorIdx & 0X80) > 0) )
	{
		if ( (m_pstCellInfo[nY + nX*m_stMapFileHeader.shHeight].bDoorOffset & 0X8000) == 0 )
		{
			return FALSE;
		}
	}
	return TRUE;

/*	if ( m_pstCellInfo[nY + nX*m_stMapFileHeader.shHeight].bDoorIdx )
	{
		if ( (m_pstCellInfo[nY + nX*m_stMapFileHeader.shHeight].bDoorOffset & 0X8000) == 0 )
		{
			return FALSE;
		}
	}
	return TRUE;
*/
}


VOID CMapHandler::OpenDoor(INT nX, INT nY, INT nIdx)
{
	if ( m_bMapLoaded == FALSE || m_pstCellInfo == NULL )
	{
		return;
	}

	if ( nX >= m_stMapFileHeader.shWidth || nY >= m_stMapFileHeader.shHeight )
	{
		return;
	}

	for ( INT nCntY = nY-8; nCntY < nY+10; nCntY++ )
	{
		for ( INT nCntX = nX-8; nCntX < nX+10; nCntX++ )
		{
			if ( nCntX >= 0 && nCntY >= 0 && nCntX < m_stMapFileHeader.shWidth && nCntY < m_stMapFileHeader.shHeight )
			{
				if ( ((m_pstCellInfo[nCntY + nCntX*m_stMapFileHeader.shHeight].bDoorIdx & 0X7F) == nIdx) )
				{
					m_pstCellInfo[nCntY + nCntX*m_stMapFileHeader.shHeight].bDoorOffset |= 0X8000;
				}
			}
		}
	}

/*	for ( INT nCntY = nY-8; nCntY < nY+10; nCntY++ )
	{
		for ( INT nCntX = nX-8; nCntX < nX+10; nCntX++ )
		{
			if ( nCntX >= 0 && nCntY >= 0 && nCntX < m_stMapFileHeader.shWidth && nCntY < m_stMapFileHeader.shHeight )
			{
				if ( m_pstCellInfo[nCntY + nCntX*m_stMapFileHeader.shHeight].bDoorIdx )
				{
					m_pstCellInfo[nCntY + nCntX*m_stMapFileHeader.shHeight].bDoorOffset |= 0X8000;
				}
			}
		}
	}
*/
}


VOID CMapHandler::CloseDoor(INT nX, INT nY, INT nIdx)
{
	if ( m_bMapLoaded == FALSE || m_pstCellInfo == NULL )
	{
		return;
	}

	if ( nX >= m_stMapFileHeader.shWidth || nY >= m_stMapFileHeader.shHeight )
	{
		return;
	}

	for ( INT nCntY = nY-8; nCntY < nY+10; nCntY++ )
	{
		for ( INT nCntX = nX-8; nCntX < nX+10; nCntX++ )
		{
			if ( nCntX >= 0 && nCntY >= 0 && nCntX < m_stMapFileHeader.shWidth && nCntY < m_stMapFileHeader.shHeight )
			{
				if ( ((m_pstCellInfo[nCntY + nCntX*m_stMapFileHeader.shHeight].bDoorIdx & 0X7F) == nIdx) )
				{
					m_pstCellInfo[nCntY + nCntX*m_stMapFileHeader.shHeight].bDoorOffset &= 0X7FFF;
				}
			}
		}
	}

/*	for ( INT nCntY = nY-8; nCntY < nY+10; nCntY++ )
	{
		for ( INT nCntX = nX-8; nCntX < nX+10; nCntX++ )
		{
			if ( nCntX >= 0 && nCntY >= 0 && nCntX < m_stMapFileHeader.shWidth && nCntY < m_stMapFileHeader.shHeight )
			{
				if ( m_pstCellInfo[nCntY + nCntX*m_stMapFileHeader.shHeight].bDoorIdx )
				{
					m_pstCellInfo[nCntY + nCntX*m_stMapFileHeader.shHeight].bDoorOffset &= 0X7FFF;
				}
			}
		}
	}
*/
}


INT CMapHandler::GetDoorImgIdx(INT nX, INT nY)
{
	INT nDoorIdx = 0;

	if ( m_bMapLoaded == FALSE || m_pstCellInfo == NULL )
	{
		return nDoorIdx;
	}

	if ( nX >= m_stMapFileHeader.shWidth || nY >= m_stMapFileHeader.shHeight )
	{
		return nDoorIdx;
	}

 	if ( ((m_pstCellInfo[nY + nX*m_stMapFileHeader.shHeight].bDoorOffset & 0X8000) > 0) )
	{		
	 	if ( (m_pstCellInfo[nY + nX*m_stMapFileHeader.shHeight].bDoorIdx & 0X7F) > 0 )
			nDoorIdx += m_pstCellInfo[nY + nX*m_stMapFileHeader.shHeight].bDoorOffset & 0X7FFF;
	}

	return nDoorIdx;
/*
	INT nDoorIdx = 0;
 	if ( (m_pstCellInfo[nY + nX*m_stMapFileHeader.shHeight].bDoorOffset & 0X8000) > 0 )
	{		
	 	if ( m_pstCellInfo[nY + nX*m_stMapFileHeader.shHeight].bDoorIdx )
			nDoorIdx += m_pstCellInfo[nY + nX*m_stMapFileHeader.shHeight].bDoorOffset & 0X7FFF;
	}

	return nDoorIdx;
*/
}



VOID CMapHandler::DrawTile()
{
	if ( m_bMapLoaded == FALSE )
	{
		return;
	}

	if ( m_bMapLoaded == FALSE )
	{
		return;
	}

	for ( INT nY = m_nStartViewTileY; nY < m_nStartViewTileY+_VIEW_CELL_Y_COUNT; nY++ )
	{
		for ( INT nX = m_nStartViewTileX; nX < m_nStartViewTileX+_VIEW_CELL_X_COUNT; nX++ )
		{
			INT nFileIdx, nImgIdx;

			if ( nX >= m_stMapFileHeader.shWidth || nY >= m_stMapFileHeader.shHeight || nX < 0 || nY < 0 )
			{
				continue; 
			}

 			if( !( nX % 2 ) && !( nY % 2 ) && nY < m_nStartViewTileY+_VIEW_CELL_Y_COUNT && m_pstTileInfo )
 			{
				nFileIdx= m_pstTileInfo[(nY/2) + (nX/2)*m_stMapFileHeader.shHeight/2].bFileIdx;
				nImgIdx = m_pstTileInfo[(nY/2) + (nX/2)*m_stMapFileHeader.shHeight/2].wTileIdx;

				// 맵데이타는 15개 단위로 세팅되있다.
				nFileIdx -= nFileIdx/15;

				// 타일 파일이 아니다.
				if ( nFileIdx % 14 > 2 || nFileIdx > 69 )
				{
					continue;
				}

				if ( nImgIdx != 65535 )
				{
					if ( g_xGameProc.m_xImage.m_xImageList[nFileIdx].NewSetIndex(nImgIdx) )
					{
						g_xMainWnd.DrawWithImageForCompClipRgn(
									(nX-m_nStartViewTileX)*_CELL_WIDTH +m_nViewPosX-m_nViewOffsetX,
									(nY-m_nStartViewTileY)*_CELL_HEIGHT+m_nViewPosY-m_nViewOffsetY,
									g_xGameProc.m_xImage.m_xImageList[nFileIdx].m_lpstNewCurrWilImageInfo->shWidth,
									g_xGameProc.m_xImage.m_xImageList[nFileIdx].m_lpstNewCurrWilImageInfo->shHeight,
									(WORD*)g_xGameProc.m_xImage.m_xImageList[nFileIdx].m_pbCurrImage,
									_CLIP_WIDTH, _CLIP_HEIGHT);					
					}
				}
			}
		}
	}
}


/******************************************************************************************************************

	함수명 : CMapHandler::SetMovedTileBuffer()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : INT nMovedTileX
	         INT nMovedTileY
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CMapHandler::SetMovedTileBuffer(INT nMovedTileX, INT nMovedTileY)
{
	if ( m_bMapLoaded == FALSE )
	{
		return;
	}

	m_nStartViewTileX += nMovedTileX;
	m_nStartViewTileY += nMovedTileY;
	m_nViewOffsetX = 0;
	m_nViewOffsetY = 0;

	if ( m_bUseTileBuffer == FALSE )
	{
		return;
	}

	INT nX, nY;

	// 현재 타일버퍼에 있는 메모리를 알맞게 이동시키고 추가되는그림을 그린다.
	// 셀단위가 아닌 타일단위로 업데이트한다.

	// 현재 Y타일이거나, 아래로 갈때.
	if ( nMovedTileY >= 0 )
	{
		if ( nMovedTileX >= 0 )
		{
			// 오른쪽으로 갈때.
			for ( INT nYCnt = 0; nYCnt < _VIEW_CELL_Y_COUNT*_CELL_HEIGHT-_CELL_HEIGHT*nMovedTileY; nYCnt++ )
			{
				memmove(&m_wSavedMapBuffer[(nYCnt*_VIEW_CELL_X_COUNT*_CELL_WIDTH)], 
						&m_wSavedMapBuffer[((nYCnt+_CELL_HEIGHT*nMovedTileY)*_VIEW_CELL_X_COUNT*_CELL_WIDTH)+_CELL_WIDTH*nMovedTileX], 
						sizeof(WORD)*_CELL_WIDTH*(_VIEW_CELL_X_COUNT-nMovedTileX));
			}

			// 그림상으로 오른쪽과 아래부분의 타일을 갱신해줘야한다.
			// 기본타일은 2셀로 이뤄져있고 (오른쪽과 아래는 1셀만의 여유)를 가지기 때문에 1셀씩을 더 읽어줘서 갱신을 시킨다.
			// 아래와 같은 형태이다. '1'은 memmove로 옮겨진 데이타이고 'o'가 새로 갱신시킬 타일그림데이타이다. '0'은 더읽어줄 데이타이다.
			// 11111111111111...0o
			// 11111111111111...0o
			// 11111111111111...0o
			// .................0o
			// .................0o
			// 00000000000000...0o
			// oooooooooooooo...oo
			
			// 기본타일 갱신.
			for ( nX = m_nStartViewTileX+_VIEW_CELL_X_COUNT-nMovedTileX-1; nX < m_nStartViewTileX+_VIEW_CELL_X_COUNT; nX++ )
				for ( nY = m_nStartViewTileY; nY < m_nStartViewTileY+_VIEW_CELL_Y_COUNT; nY++ )		
				{
					DrawBaseTile(nX, nY);
				}
			for ( nX = m_nStartViewTileX; nX < m_nStartViewTileX+_VIEW_CELL_X_COUNT; nX++ )		
				for ( nY = m_nStartViewTileY+_VIEW_CELL_Y_COUNT-nMovedTileY-1; nY < m_nStartViewTileY+_VIEW_CELL_Y_COUNT; nY++ )
				{
					DrawBaseTile(nX, nY);
				}
		}
		else
		{
			// 왼쪽으로 갈때.
			// 왼쪽과 아래부분의 타일을 갱신.
			// o11111111111111...1
			// o11111111111111...1
			// o11111111111111...1
			// o1................1
			// o1................1
			// o00000000000000...0
			// ooooooooooooooo...o

			// 기본타일 갱신.
			// 좌측은 2타일의 여유를 가지므로 1셀씩만 읽고, 아래로는 한타일만의 여유를 가지므로 아래로는 1셀씩을 더 읽어준다.
			for ( INT nYCnt = 0; nYCnt < _VIEW_CELL_Y_COUNT*_CELL_HEIGHT-_CELL_HEIGHT*nMovedTileY; nYCnt++ )
			{
				memmove(&m_wSavedMapBuffer[(nYCnt*_VIEW_CELL_X_COUNT*_CELL_WIDTH)+_CELL_WIDTH*(-nMovedTileX)], 
						&m_wSavedMapBuffer[((nYCnt+_CELL_HEIGHT*nMovedTileY)*_VIEW_CELL_X_COUNT*_CELL_WIDTH)], sizeof(WORD)*_CELL_WIDTH*(_VIEW_CELL_X_COUNT-(-nMovedTileX)));
			}

			for ( nX = m_nStartViewTileX; nX < m_nStartViewTileX+(-nMovedTileX); nX++ )
				for ( nY = m_nStartViewTileY; nY < m_nStartViewTileY+_VIEW_CELL_Y_COUNT; nY++ )		
				{
					DrawBaseTile(nX, nY);
				}
			for ( nX = m_nStartViewTileX; nX < m_nStartViewTileX+_VIEW_CELL_X_COUNT; nX++ )		
				for ( nY = m_nStartViewTileY+_VIEW_CELL_Y_COUNT-nMovedTileY-1; nY < m_nStartViewTileY+_VIEW_CELL_Y_COUNT; nY++ )
				{
					DrawBaseTile(nX, nY);
				}
		}
	}
	// 위로 갈때.
	else
	{
		if ( nMovedTileX >= 0 )
		{
			// 오른쪽으로 갈때.

			// ooooooooooooo...0o
			// 1111111111111...0o
			// ................0o
			// ................0o
			// 1111111111111...0o
			// 1111111111111...0o
			// 1111111111111...0o

			for ( INT nYCnt = (_VIEW_CELL_Y_COUNT*_CELL_HEIGHT)+(_CELL_HEIGHT*nMovedTileY)-1; nYCnt >= 0 ; nYCnt-- )
			{
				memmove(&m_wSavedMapBuffer[((nYCnt+_CELL_HEIGHT*(-nMovedTileY))*_VIEW_CELL_X_COUNT*_CELL_WIDTH)], 
						&m_wSavedMapBuffer[(nYCnt*_VIEW_CELL_X_COUNT*_CELL_WIDTH)+_CELL_WIDTH*nMovedTileX], sizeof(WORD)*_CELL_WIDTH*(_VIEW_CELL_X_COUNT-nMovedTileX));
			}

			for ( nX = m_nStartViewTileX+_VIEW_CELL_X_COUNT-nMovedTileX-1; nX < m_nStartViewTileX+_VIEW_CELL_X_COUNT; nX++ )
				for ( nY = m_nStartViewTileY; nY < m_nStartViewTileY+_VIEW_CELL_Y_COUNT; nY++ )		
				{
					DrawBaseTile(nX, nY);
				}
			for ( nX = m_nStartViewTileX; nX < m_nStartViewTileX+_VIEW_CELL_X_COUNT; nX++ )		
				for ( nY = m_nStartViewTileY; nY < m_nStartViewTileY+(-nMovedTileY); nY++ )
				{
					DrawBaseTile(nX, nY);
				}
		}
		else
		{
			for ( INT nYCnt = (_VIEW_CELL_Y_COUNT*_CELL_HEIGHT)+(_CELL_HEIGHT*nMovedTileY)-1; nYCnt >= 0 ; nYCnt-- )
			{
				// 왼쪽으로 갈때.
				memmove(&m_wSavedMapBuffer[((nYCnt+_CELL_HEIGHT*(-nMovedTileY))*_VIEW_CELL_X_COUNT*_CELL_WIDTH)+_CELL_WIDTH*(-nMovedTileX)], 
 						&m_wSavedMapBuffer[(nYCnt*_VIEW_CELL_X_COUNT*_CELL_WIDTH)], sizeof(WORD)*_CELL_WIDTH*(_VIEW_CELL_X_COUNT-(-nMovedTileX)));
			}

			// oooooooooooooo...o
			// o1111111111111...1
			// o1...............1
			// o1...............1
			// o1111111111111...1
			// o1111111111111...1
			// o1111111111111...1
			for ( nX = m_nStartViewTileX; nX < m_nStartViewTileX+(-nMovedTileX); nX++ )
				for ( nY = m_nStartViewTileY; nY < m_nStartViewTileY+_VIEW_CELL_Y_COUNT; nY++ )		
				{
					DrawBaseTile(nX, nY);
				}
			for ( nX = m_nStartViewTileX; nX < m_nStartViewTileX+_VIEW_CELL_X_COUNT; nX++ )		
				for ( nY = m_nStartViewTileY; nY < m_nStartViewTileY+(-nMovedTileY); nY++ )
				{
					DrawBaseTile(nX, nY);
				}
		}
	}
}


VOID CMapHandler::SetStartViewTile(INT nX, INT nY)
{
	m_nStartViewTileX	= nX;
	m_nStartViewTileY	= nY;
	m_nViewOffsetX		= 0;	
	m_nViewOffsetY		= 0;
}



BYTE CMapHandler::GetTileAttribute(INT nX, INT nY)
{
	if ( m_bMapLoaded == FALSE )
	{
		return _CAN_NOTWALK;
	}

	if ( nX >= m_stMapFileHeader.shWidth || nY >= m_stMapFileHeader.shHeight )
	{
		return _CAN_NOTWALK;
	}

	if ( m_pstCellInfo )
	{
		BYTE bAttr = _CAN_WALK;

		if ( m_pstCellInfo[nY + nX*m_stMapFileHeader.shHeight].bFlag & 0X01 )
			return bAttr;
	}

	return _CAN_NOTWALK;
}



LIGHTINFO CMapHandler::GetTileLightInfo(INT nX, INT nY)
{
	LIGHTINFO stLight = {FALSE, -1, -1};
	
	if ( m_bMapLoaded == FALSE || m_pstCellInfo == NULL )
	{
		return stLight;
	}

	if ( nX >= m_stMapFileHeader.shWidth || nY >= m_stMapFileHeader.shHeight )
	{
		return stLight;
	}

	if ( (m_pstCellInfo[nY + nX*m_stMapFileHeader.shHeight].wLigntNEvent == 0) && ((m_pstCellInfo[nY + nX*m_stMapFileHeader.shHeight].wLigntNEvent & 0X07) != 1) )
		return stLight;

	stLight.bIsLight		= TRUE;
	stLight.cLightSizeType	= (CHAR)((m_pstCellInfo[nY + nX*m_stMapFileHeader.shHeight].wLigntNEvent & 0XC000) >> 14);
	stLight.cLightColorType	= (CHAR)((m_pstCellInfo[nY + nX*m_stMapFileHeader.shHeight].wLigntNEvent & 0X3FF0) >> 4);

	return stLight;	
}


BYTE CMapHandler::GetEventNum(INT nX, INT nY)
{
	BYTE bEventNum;

	bEventNum = 0;
	
	if ( m_bMapLoaded == FALSE || m_pstCellInfo == NULL )
	{
		return bEventNum;
	}

	if ( nX >= m_stMapFileHeader.shWidth || nY >= m_stMapFileHeader.shHeight )
	{
		return bEventNum;
	}

	if ( (m_pstCellInfo[nY + nX*m_stMapFileHeader.shHeight].wLigntNEvent == -1) && ((m_pstCellInfo[nY + nX*m_stMapFileHeader.shHeight].wLigntNEvent & 0X07) != 3) )
		return bEventNum;

	bEventNum	= (BYTE)((m_pstCellInfo[nY + nX*m_stMapFileHeader.shHeight].wLigntNEvent & 0XF0) >> 4);

	return bEventNum;	
}


VOID CMapHandler::GetLastTile(INT nXPos, INT nYPos, BYTE bDir, INT& nTileX, INT& nTileY, INT nGap)
{
	BYTE bLastDir;
	INT  nXGapPos, nYGapPos;

	nXGapPos = nYGapPos = 0;

	if ( bDir < 4 )				bLastDir = (BYTE)(bDir + 4);
	else						bLastDir = (BYTE)(bDir - 4);

	switch ( bLastDir )
	{
	case _DIRECTION_LIST_1:
		{
			nXGapPos = nXPos;
			nYGapPos = nYPos-nGap;
		}
		break;
	case _DIRECTION_LIST_2:
		{
			nXGapPos = nXPos+nGap;
			nYGapPos = nYPos-nGap;
		}
		break;
	case _DIRECTION_LIST_3:
		{
			nXGapPos = nXPos+nGap;
			nYGapPos = nYPos;
		}
		break;
	case _DIRECTION_LIST_4:
		{
			nXGapPos = nXPos+nGap;
			nYGapPos = nYPos+nGap;
		}
		break;
	case _DIRECTION_LIST_5:
		{
			nXGapPos = nXPos;
			nYGapPos = nYPos+nGap;
		}
		break;
	case _DIRECTION_LIST_6:
		{
			nXGapPos = nXPos-nGap;
			nYGapPos = nYPos+nGap;
		}
		break;
	case _DIRECTION_LIST_7:
		{
			nXGapPos = nXPos-nGap;
			nYGapPos = nYPos;
		}
		break;
	case _DIRECTION_LIST_8:
		{
			nXGapPos = nXPos-nGap;
			nYGapPos = nYPos-nGap;
		}
		break;
	}

	nTileX = nXGapPos;
	nTileY = nYGapPos;
}

BOOL CMapHandler::GetNextTileCanMove(INT nXPos, INT nYPos, BYTE bDir, INT nGap, POINT* lpptTarget)
{
	INT  nXGapPos, nYGapPos;
	BYTE bCanMove = _CAN_WALK;

	nXGapPos = nYGapPos = 0;

	if ( m_bMapLoaded == FALSE )
	{
		return FALSE;
	}

	switch ( bDir )
	{
	case _DIRECTION_LIST_1:
		{
			nXGapPos = nXPos;
			nYGapPos = nYPos-nGap;
			bCanMove  = GetTileAttribute(nXGapPos, nYGapPos);
		}
		break;
	case _DIRECTION_LIST_2:
		{
			nXGapPos = nXPos+nGap;
			nYGapPos = nYPos-nGap;
			bCanMove  = GetTileAttribute(nXGapPos, nYGapPos);
		}
		break;
	case _DIRECTION_LIST_3:
		{
			nXGapPos = nXPos+nGap;
			nYGapPos = nYPos;
			bCanMove  = GetTileAttribute(nXGapPos, nYGapPos);
		}
		break;
	case _DIRECTION_LIST_4:
		{
			nXGapPos = nXPos+nGap;
			nYGapPos = nYPos+nGap;
			bCanMove  = GetTileAttribute(nXGapPos, nYGapPos);
		}
		break;
	case _DIRECTION_LIST_5:
		{
			nXGapPos = nXPos;
			nYGapPos = nYPos+nGap;
			bCanMove  = GetTileAttribute(nXGapPos, nYGapPos);
		}
		break;
	case _DIRECTION_LIST_6:
		{
			nXGapPos = nXPos-nGap;
			nYGapPos = nYPos+nGap;
			bCanMove  = GetTileAttribute(nXGapPos, nYGapPos);
		}
		break;
	case _DIRECTION_LIST_7:
		{
			nXGapPos = nXPos-nGap;
			nYGapPos = nYPos;
			bCanMove  = GetTileAttribute(nXGapPos, nYGapPos);
		}
		break;
	case _DIRECTION_LIST_8:
		{
			nXGapPos = nXPos-nGap;
			nYGapPos = nYPos-nGap;
			bCanMove  = GetTileAttribute(nXGapPos, nYGapPos);
		}
		break;
	}

	if ( lpptTarget == NULL )
	{
		return FALSE;
	}

	lpptTarget->x = nXGapPos;
	lpptTarget->y = nYGapPos;

	if ( bCanMove != _CAN_WALK )
	{
		return FALSE;
	}

	if ( g_xGameProc.m_xActorList.GetCount() )
	{
		CActor* pxActor = NULL;
		CListNode <CActor> *pNode;

		for (pNode = g_xGameProc.m_xActorList.GetHead(); pNode; pNode = pNode->GetNext())
		{
			pxActor = pNode->GetData();

			if ( pxActor )
			{
				BOOL bIsDead = FALSE;
				if ( pxActor->m_stFeature.bGender == _GENDER_MAN || pxActor->m_stFeature.bGender == _GENDER_WOMAN )
				{
					if ( pxActor->m_bCurrMtn == _MT_DIE || pxActor->m_bIsDead )
					{
						bIsDead = TRUE;
					}
				}
				else if ( pxActor->m_stFeature.bGender == _GENDER_MON )
				{
					if ( pxActor->m_bCurrMtn == _MT_MON_DIE || pxActor->m_bIsDead )
					{
						bIsDead = TRUE;
					}
				}
				//  사북성문 체크 
				WORD wDress = MAKEWORD(pxActor->m_stFeature.bDress, pxActor->m_stFeature.bHair);

				if ( wDress == 530 || wDress == 531 /*성훈씨*/)
				{
					if ( pxActor->m_bCurrDir == 0 || pxActor->m_bCurrDir == 1 ||
						 pxActor->m_bCurrDir == 2 || pxActor->m_bCurrDir == 3 )
					{
						if ( (( pxActor->m_nPosX == nXGapPos &&  pxActor->m_nPosY == nYGapPos ) ||
							  ( pxActor->m_nPosX - 1 == nXGapPos &&  pxActor->m_nPosY == nYGapPos ) ||
							  ( pxActor->m_nPosX == nXGapPos &&  pxActor->m_nPosY - 1 == nYGapPos ) ||
							  ( pxActor->m_nPosX + 1 == nXGapPos &&  pxActor->m_nPosY - 1 == nYGapPos ) )&& !bIsDead )
						{
							return FALSE;
						}
					}
					else if ( pxActor->m_bCurrDir == 7 )
					{
						if ( (( pxActor->m_nPosX == nXGapPos &&  pxActor->m_nPosY - 2 == nYGapPos ) ||
							  ( pxActor->m_nPosX + 1 == nXGapPos &&  pxActor->m_nPosY - 1 == nYGapPos ) ) && !bIsDead )
						{
							return FALSE;
						}
					}
				}
				else if ( wDress == 532 || wDress == 533 /*성훈씨*/)
				{
					if ( pxActor->m_bCurrDir == 0 || pxActor->m_bCurrDir == 1 ||
						 pxActor->m_bCurrDir == 2 || pxActor->m_bCurrDir == 3 )
					{
						if ( (( pxActor->m_nPosX == nXGapPos &&  pxActor->m_nPosY == nYGapPos ) ||
							  ( pxActor->m_nPosX - 1 == nXGapPos &&  pxActor->m_nPosY - 1== nYGapPos ) ||
							  ( pxActor->m_nPosX == nXGapPos &&  pxActor->m_nPosY - 1 == nYGapPos ) ||
							  ( pxActor->m_nPosX + 1 == nXGapPos &&  pxActor->m_nPosY == nYGapPos ) ||
							  ( pxActor->m_nPosX + 1 == nXGapPos &&  pxActor->m_nPosY + 1 == nYGapPos )) && !bIsDead )
						{
							return FALSE;
						}
					}
					else if ( pxActor->m_bCurrDir == 7 )
					{
						if ( (( pxActor->m_nPosX == nXGapPos &&  pxActor->m_nPosY - 2 == nYGapPos ) ||
							  ( pxActor->m_nPosX - 1 == nXGapPos &&  pxActor->m_nPosY - 1 == nYGapPos ) ) && !bIsDead )
						{
							return FALSE;
						}
					}
				}	// 사북성문 체크 종료
				else if ( wDress == 538 )		// 누마성문 체크
				{
					if ( pxActor->m_bCurrDir == 0 || pxActor->m_bCurrDir == 1 ||
						 pxActor->m_bCurrDir == 2 || pxActor->m_bCurrDir == 3 )
					{
						if ( (( pxActor->m_nPosX == nXGapPos &&  pxActor->m_nPosY == nYGapPos ) ||
							  ( pxActor->m_nPosX - 1 == nXGapPos &&  pxActor->m_nPosY - 1== nYGapPos ) ||
							  ( pxActor->m_nPosX == nXGapPos &&  pxActor->m_nPosY - 1 == nYGapPos ) ||
							  ( pxActor->m_nPosX + 1 == nXGapPos &&  pxActor->m_nPosY == nYGapPos ) ||
							  ( pxActor->m_nPosX + 1 == nXGapPos &&  pxActor->m_nPosY + 1 == nYGapPos ) ||
							  ( pxActor->m_nPosX + 2 == nXGapPos &&  pxActor->m_nPosY +1 == nYGapPos )) && !bIsDead )
						{
							return FALSE;
						}
					}
					else if ( pxActor->m_bCurrDir == 7 )
					{
						if ( (( pxActor->m_nPosX == nXGapPos &&  pxActor->m_nPosY - 2 == nYGapPos ) ||
							  ( pxActor->m_nPosX - 1 == nXGapPos &&  pxActor->m_nPosY - 1 == nYGapPos ) ) && !bIsDead )
						{
							return FALSE;
						}
					}
				}
				else if ( wDress == 534 )		// 목책1 체크
				{
					if ( pxActor->m_bCurrDir == 0 || pxActor->m_bCurrDir == 1 ||
						 pxActor->m_bCurrDir == 2 || pxActor->m_bCurrDir == 3 )
					{
						if ( (( pxActor->m_nPosX == nXGapPos &&  pxActor->m_nPosY == nYGapPos ) ||
							  ( pxActor->m_nPosX == nXGapPos &&  pxActor->m_nPosY - 1 == nYGapPos ) ||
							  ( pxActor->m_nPosX + 1 == nXGapPos &&  pxActor->m_nPosY - 1 == nYGapPos ) ||
							  ( pxActor->m_nPosX - 1 == nXGapPos &&  pxActor->m_nPosY == nYGapPos ) ||
							  ( pxActor->m_nPosX - 1 == nXGapPos &&  pxActor->m_nPosY + 1 == nYGapPos )) && !bIsDead )
						{
							return FALSE;
						}
					}
				}
				else if ( wDress == 535 )		// 목책2 체크
				{
					if ( pxActor->m_bCurrDir == 0 || pxActor->m_bCurrDir == 1 ||
						 pxActor->m_bCurrDir == 2 || pxActor->m_bCurrDir == 3 )
					{
						if ( (( pxActor->m_nPosX == nXGapPos &&  pxActor->m_nPosY == nYGapPos ) ||
							  ( pxActor->m_nPosX + 1 == nXGapPos &&  pxActor->m_nPosY - 1 == nYGapPos ) ||
							  ( pxActor->m_nPosX - 1 == nXGapPos &&  pxActor->m_nPosY + 1 == nYGapPos ) ||
							  ( pxActor->m_nPosX + 1 == nXGapPos &&  pxActor->m_nPosY == nYGapPos ) ||
							  ( pxActor->m_nPosX == nXGapPos &&  pxActor->m_nPosY + 1 == nYGapPos )) && !bIsDead )
						{
							return FALSE;
						}
					}
				}
				else if ( wDress == 536 )		// 목책3 체크
				{
					if ( pxActor->m_bCurrDir == 0 || pxActor->m_bCurrDir == 1 ||
						 pxActor->m_bCurrDir == 2 || pxActor->m_bCurrDir == 3 )
					{
						if ( (( pxActor->m_nPosX == nXGapPos &&  pxActor->m_nPosY == nYGapPos ) ||
							  ( pxActor->m_nPosX + 1 == nXGapPos &&  pxActor->m_nPosY == nYGapPos ) ||
							  ( pxActor->m_nPosX == nXGapPos &&  pxActor->m_nPosY - 1 == nYGapPos ) ||
							  ( pxActor->m_nPosX - 1 == nXGapPos &&  pxActor->m_nPosY - 1 == nYGapPos ) ||
							  ( pxActor->m_nPosX + 1 == nXGapPos &&  pxActor->m_nPosY + 1 == nYGapPos )) && !bIsDead )
						{
							return FALSE;
						}
					}
				}
				else if ( wDress == 537 )		// 목책4 체크
				{
					if ( pxActor->m_bCurrDir == 0 || pxActor->m_bCurrDir == 1 ||
						 pxActor->m_bCurrDir == 2 || pxActor->m_bCurrDir == 3 )
					{
						if ( (( pxActor->m_nPosX == nXGapPos &&  pxActor->m_nPosY == nYGapPos ) ||
							  ( pxActor->m_nPosX - 1 == nXGapPos &&  pxActor->m_nPosY == nYGapPos ) ||
							  ( pxActor->m_nPosX == nXGapPos &&  pxActor->m_nPosY + 1 == nYGapPos ) ||
							  ( pxActor->m_nPosX - 1 == nXGapPos &&  pxActor->m_nPosY - 1 == nYGapPos ) ||
							  ( pxActor->m_nPosX + 1 == nXGapPos &&  pxActor->m_nPosY + 1 == nYGapPos )) && !bIsDead )
						{
							return FALSE;
						}
					}
				}
				else
				{
					if ( pxActor->m_nPosX == nXGapPos &&  pxActor->m_nPosY == nYGapPos && !bIsDead )	
						return FALSE;
				}

			}
		}
	} 

	return TRUE;
}



VOID CMapHandler::SetAniTileFrame(INT nLoopTime)
{
	INT nCnt;

	for ( nCnt = 0; nCnt < 8; nCnt++ )
	{
		m_dwAniSaveTime[nCnt] += nLoopTime;
	}

	if ( m_dwAniSaveTime[0] > _TILE_ANI_DELAY_1 )
	{
		for ( nCnt = 0; nCnt < 16; nCnt++ )
		{
			m_bAniTileFrame[0][nCnt]++;

			if ( m_bAniTileFrame[0][nCnt] >= nCnt )
				m_bAniTileFrame[0][nCnt] = 0;
		}
		m_dwAniSaveTime[0] = 0;
	}

	if ( m_dwAniSaveTime[1] > _TILE_ANI_DELAY_2 )
	{
		for ( nCnt = 0; nCnt < 16; nCnt++ )
		{
			m_bAniTileFrame[1][nCnt]++;

			if ( m_bAniTileFrame[1][nCnt] >= nCnt )
				m_bAniTileFrame[1][nCnt] = 0;
		}
		m_dwAniSaveTime[1] = 0;
	}

	if ( m_dwAniSaveTime[2] > _TILE_ANI_DELAY_3 )
	{
		for ( nCnt = 0; nCnt < 16; nCnt++ )
		{
			m_bAniTileFrame[2][nCnt]++;

			if ( m_bAniTileFrame[2][nCnt] >= nCnt )
				m_bAniTileFrame[2][nCnt] = 0;
		}
		m_dwAniSaveTime[2] = 0;
	}
	
	if ( m_dwAniSaveTime[3] > _TILE_ANI_DELAY_4 )
	{
		for ( nCnt = 0; nCnt < 16; nCnt++ )
		{
			m_bAniTileFrame[3][nCnt]++;

			if ( m_bAniTileFrame[3][nCnt] >= nCnt )
				m_bAniTileFrame[3][nCnt] = 0;
		}
		m_dwAniSaveTime[3] = 0;
	}

	if ( m_dwAniSaveTime[4] > _TILE_ANI_DELAY_5 )
	{
		for ( nCnt = 0; nCnt < 16; nCnt++ )
		{
			m_bAniTileFrame[4][nCnt]++;

			if ( m_bAniTileFrame[4][nCnt] >= nCnt )
				m_bAniTileFrame[4][nCnt] = 0;
		}
		m_dwAniSaveTime[4] = 0;
	}

	if ( m_dwAniSaveTime[5] > _TILE_ANI_DELAY_6 )
	{
		for ( nCnt = 0; nCnt < 16; nCnt++ )
		{
			m_bAniTileFrame[5][nCnt]++;

			if ( m_bAniTileFrame[5][nCnt] >= nCnt )
				m_bAniTileFrame[5][nCnt] = 0;
		}
		m_dwAniSaveTime[5] = 0;
	}

	if ( m_dwAniSaveTime[6] > _TILE_ANI_DELAY_7 )
	{
		for ( nCnt = 0; nCnt < 16; nCnt++ )
		{
			m_bAniTileFrame[6][nCnt]++;

			if ( m_bAniTileFrame[6][nCnt] >= nCnt )
				m_bAniTileFrame[6][nCnt] = 0;
		}
		m_dwAniSaveTime[6] = 0;
	}

	if ( m_dwAniSaveTime[7] > _TILE_ANI_DELAY_8 )
	{
		for ( nCnt = 0; nCnt < 16; nCnt++ )
		{
			m_bAniTileFrame[7][nCnt]++;

			if ( m_bAniTileFrame[7][nCnt] >= nCnt )
				m_bAniTileFrame[7][nCnt] = 0;
		}
		m_dwAniSaveTime[7] = 0;
	}
}


VOID CMapHandler::GetScrnPosFromTilePos(INT nTileX, INT nTileY, INT& nScrnX, INT& nScrnY)
{
	nScrnX = (nTileX - m_nStartViewTileX)*_CELL_WIDTH  - m_nViewOffsetX + m_nViewPosX;
	nScrnY = (nTileY - m_nStartViewTileY)*_CELL_HEIGHT - m_nViewOffsetY + m_nViewPosY;
}


VOID CMapHandler::GetTilePosFromScrnPos(INT nScrnX, INT nScrnY, INT& nTileX, INT& nTileY)
{
	nTileX = m_nStartViewTileX + (nScrnX - m_nViewPosX) / _CELL_WIDTH;
	nTileY = m_nStartViewTileY + (nScrnY - m_nViewPosY) / _CELL_HEIGHT;
}


BYTE CMapHandler::CalcDirection16(INT nFireTileX, INT nFireTileY, INT nDestTileX, INT nDestTileY)
{
	INT nWidth	= nDestTileX - nFireTileX;
	INT nHeight = nDestTileY - nFireTileY;

	FLOAT	rLineLength, rBottomInTriangle;
	INT		nDimension;
	BYTE	bDir;
	rLineLength = (FLOAT)sqrt(nWidth*nWidth+nHeight*nHeight);
	
	// 기본.
	// 7  0  1          
	// 6     2
	// 5  4  3
	// 일단은 4개의 분면(90도기준)으로 나누고 분면에 대한 cos값을 적용한다.
	( nWidth >= 0 ) ?
		( nHeight <  0 ? (rBottomInTriangle=(FLOAT)-nHeight, nDimension=0) : (rBottomInTriangle=(FLOAT) nWidth, nDimension=4) ):
		( nHeight >= 0 ? (rBottomInTriangle=(FLOAT) nHeight, nDimension=8) : (rBottomInTriangle=(FLOAT)-nWidth, nDimension=12) );
	// 6(cos45)  0(cos 0)  0(cos45)
	// 4(cos90)  2(cos 0)  2(cos 0)
	// 4(cos45)  2(cos90)  2(cos45)

	if ( rLineLength == 0.0f )
	{
		return 0;
	}

	FLOAT rCosVal = rBottomInTriangle/rLineLength;

	CONST FLOAT rCosVal16[8] = { 1.0f, 0.980785f, 0.923880f, 0.831470f, 0.707107f, 0.555570f, 0.382683f, 0.195090f };
	
	// 각분면을 3개의 영역으로 나누어서 영역을 재조정한다.
	bDir = 0;
	for ( INT nCnt = 0; nCnt < 8; nCnt++ )
	{
		if( rCosVal <= rCosVal16[nCnt] )
		{
			bDir = (BYTE)(nDimension+(nCnt+1)/2);
		}
		else
		{
			break;
		}
	}
	
	if( bDir >= 16 )					bDir = 0;
	
	return bDir;
}



BYTE CMapHandler::CalcDirection8(INT nFireTileX, INT nFireTileY, INT nDestTileX, INT nDestTileY)
{
	INT nWidth	= nDestTileX - nFireTileX;
	INT nHeight = nDestTileY - nFireTileY;

	FLOAT	rLineLength, rBottomInTriangle;
	INT		nDimension;
	BYTE	bDir;
	rLineLength = (FLOAT)sqrt(nWidth*nWidth+nHeight*nHeight);
	
	// 기본.
	// 7  0  1          
	// 6     2
	// 5  4  3
	// 일단은 4개의 분면(90도기준)으로 나누고 분면에 대한 cos값을 적용한다.
	( nWidth >= 0 ) ?
		( nHeight <  0 ? (rBottomInTriangle=(FLOAT)-nHeight, nDimension=0) : (rBottomInTriangle=(FLOAT) nWidth, nDimension=2) ):
		( nHeight >= 0 ? (rBottomInTriangle=(FLOAT) nHeight, nDimension=4) : (rBottomInTriangle=(FLOAT)-nWidth, nDimension=6) );
	// 6(cos45)  0(cos 0)  0(cos45)
	// 4(cos90)  2(cos 0)  2(cos 0)
	// 4(cos45)  2(cos90)  2(cos45)

	if ( rLineLength == 0.0f )
	{
		return 0;
	}

	FLOAT rCosVal = rBottomInTriangle/rLineLength;
	
//	cos(0), cos(pi/8), cos(pi/4), cos(pi/2)
	CONST FLOAT rCosVal8[4] = { 1.0f, 0.923880f, 0.707107f, 0.382683f };
	
	// 각분면을 3개의 영역으로 나누어서 영역을 재조정한다.
	bDir = 0;
	for ( INT nCnt = 0; nCnt < 4; nCnt++ )
	{
		if( rCosVal <= rCosVal8[nCnt] )
		{
			bDir = (BYTE)(nDimension+(nCnt+1)/2);
		}
		else
		{
			break;
		}
	}
	
	if( bDir >= 8 )					bDir = 0;
	
	return bDir;
}



BYTE CMapHandler::GetNextDirection(INT nSX, INT nSY, INT nTX, INT nTY)
{
	INT nFlagX, nFlagY;
	
	BYTE bDir = _DIRECTION_LIST_5;

	if ( nSX < nTX ) 
	{
		nFlagX = 1;
	}
	else if ( nSX == nTX )
	{
		nFlagX = 0;
	}
	else
	{
		nFlagX = -1;
	}

	if ( abs(nSY - nTY) > 2 )
	{
		if ( ( nSX >= nTX-1 ) && (nSX <= nTX+1) ) 
		{
			nFlagX = 0;
		}
	}

	if ( nSY < nTY ) 
	{
		nFlagY = 1;
	}
	else if ( nSY == nTY )
	{
		nFlagY = 0;
	}
	else
	{
		nFlagY = -1;
	}

	if ( abs(nSX - nTX) > 2 )
	{
		if ( ( nSY >= nTY-1 ) && (nSY <= nTY+1) ) 
		{
			nFlagY = 0;
		}
	}

	if ( (nFlagX == 0) && (nFlagY == -1) )
	{
		bDir = _DIRECTION_LIST_1;
	}
	else if ( (nFlagX == 1) && (nFlagY == -1) )
	{
		bDir = _DIRECTION_LIST_2;
	}
	else if ( (nFlagX == 1) && (nFlagY == 0) )
	{
		bDir = _DIRECTION_LIST_3;
	}
	else if ( (nFlagX == 1) && (nFlagY == 1) )
	{
		bDir = _DIRECTION_LIST_4;
	}
	else if ( (nFlagX == 0) && (nFlagY == 1) )
	{
		bDir = _DIRECTION_LIST_5;
	}
	else if ( (nFlagX == -1) && (nFlagY == 1) )
	{
		bDir = _DIRECTION_LIST_6;
	}
	else if ( (nFlagX == -1) && (nFlagY == 0) )
	{
		bDir = _DIRECTION_LIST_7;
	}
	else if ( (nFlagX == -1) && (nFlagY == -1) )
	{
		bDir = _DIRECTION_LIST_8;
	}

	return bDir;
}
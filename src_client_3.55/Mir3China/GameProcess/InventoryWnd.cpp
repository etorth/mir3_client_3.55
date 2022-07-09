/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"



/******************************************************************************************************************

	CInventoryWnd Class

*******************************************************************************************************************/
/******************************************************************************************************************

	함수명 : CInventoryWnd::CInventoryWnd()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
CInventoryWnd::CInventoryWnd()
{
	Init();
}



/******************************************************************************************************************

	함수명 : CInventoryWnd::~CInventoryWnd()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
CInventoryWnd::~CInventoryWnd()
{
	Destroy();
}


VOID CInventoryWnd::Init()
{
	INT nCnt;
	CGameWnd::Init();
	m_nStartLineNum	= 0;

	m_dwDLClickTime = 0;
	m_dwLClickTime	= 0;
	m_dwRClickTime	= 0;

	m_nMerchantID	= 0;

	m_bType			= _INVEN_TYPE_BAG;

	ZeroMemory(m_stInventoryItem, sizeof(INVENITEMSET)*_MAX_INVEN_ITEM);
	ZeroMemory(m_pszPrice, 20);
	m_nPrice		= -1;

	InitParkItem();

	m_xInvenScrlBar.Init();

	for ( nCnt = 0; nCnt < _MAX_INVEN_BTN; nCnt++ )
	{
		m_xInventoryBtn[nCnt].Init();
	}

	memset(m_shItemSetInfo, -1, _INVEN_TOTAL_CELL*sizeof(SHORT));
}


VOID CInventoryWnd::Destroy()
{
	INT nCnt;
	CGameWnd::Destroy();
	for ( nCnt = 0; nCnt < _MAX_INVEN_BTN; nCnt++ )
	{
		m_xInventoryBtn[nCnt].Destroy();
	}
	Init();
}


/******************************************************************************************************************

	함수명 : CInventoryWnd::CreateInventoryWnd()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : INT nID
	         CWHWilImageData* pxWndImage
	         INT nFrameImgIdx
	         INT nStartX
	         INT nStartY
	         INT nWidth
	         INT nHeight
	         BOOL bCanMove
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CInventoryWnd::CreateInventoryWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove)
{
	// 윈도우 생성.
	CreateGameWnd(nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight, bCanMove);

	// 버튼생성.
	m_xInventoryBtn[_BTN_ID_INVENCLOSE].CreateGameBtn(pxWndImage, 1221, 1222, nStartX+242, nStartY+423, g_xMsg.GetMsg(1052), _BTN_TYPE_FOCUS, 1221, TRUE);
	m_xInventoryBtn[_BTN_ID_FUN1	  ].CreateGameBtn(pxWndImage, 264, 265, nStartX+176, nStartY+22);
	m_xInventoryBtn[_BTN_ID_FUN2	  ].CreateGameBtn(pxWndImage, 267, 268, nStartX+401, nStartY+265);
//	m_xInventoryBtn[_BTN_ID_MINIMAPBOOK].CreateGameBtn(pxWndImage, 1232, 1232, nStartX+211, nStartY+13, g_xMsg.GetMsg(1711), _BTN_TYPE_FOCUS, -1, FALSE);


	m_xInvenScrlBar.CreateScrlBar(pxWndImage, 1225, _NEW_INVEN_CELL_YCNT, 12, 268, 14);

	m_bOpa = 220;
}



/******************************************************************************************************************

	함수명 : CInventoryWnd::SetInvenBtnInit()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CInventoryWnd::SetInvenBtnInit()
{
	for( INT nCnt = 0; nCnt < _MAX_INVEN_BTN; nCnt++ )
	{
		m_xInventoryBtn[nCnt].SetBtnState(_BTN_STATE_NORMAL);
	}
}



/******************************************************************************************************************

	함수명 : CInventoryWnd::ShowInventoryWnd()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CInventoryWnd::ShowInventoryWnd()
{
	// 윈도우 바탕그리기.
	ShowGameWnd();

	RECT rcItmRgn;
	// 스크롤바.
	m_xInvenScrlBar.ShowScrlBar(m_rcWnd.left+254, m_rcWnd.top+70, m_nStartLineNum, _INVEN_MAX_CELL_YCNT - _NEW_INVEN_CELL_YCNT);

	SetRect(&rcItmRgn, _NEW_INVEN_CELL_XSTART + m_rcWnd.left, _NEW_INVEN_CELL_YSTART+ m_rcWnd.top, 
			_NEW_INVEN_CELL_XSTART + m_rcWnd.left + (_NEW_INVENTORY_CELL_WIDTH)*(_INVEN_CELL_XCNT), 
			_NEW_INVEN_CELL_YSTART + m_rcWnd.top + (_NEW_INVENTORY_CELL_HEIGHT)*(_NEW_INVEN_CELL_YCNT) );

	if ( PtInRect(&rcItmRgn, g_xGameProc.m_ptMousePos) )
	{
		if ( g_xGameProc.m_xInterface.m_stCommonItem.bSetted && !g_xGameProc.m_xInterface.m_stCommonItem.bIsHideItem )
		{
			RECT rc;
			RECT rcCell;
			RECT rcInter;
			D3DMATERIAL7 mtrl;
			INT nCell = GetInvenCellNum(g_xGameProc.m_ptMousePos);
			
			if ( CanItemInsert(nCell, &g_xGameProc.m_xInterface.m_stCommonItem.xItem, rcCell) )
			{
				INT nSX = m_rcWnd.left+_NEW_INVEN_CELL_XSTART + rcCell.left*(_NEW_INVENTORY_CELL_WIDTH);
				INT nSY = m_rcWnd.top +_NEW_INVEN_CELL_YSTART + (rcCell.top-m_nStartLineNum)*(_NEW_INVENTORY_CELL_HEIGHT);

				SetRect(&rc, nSX, nSY, nSX+(rcCell.right-rcCell.left)*(_NEW_INVENTORY_CELL_WIDTH), nSY+(rcCell.bottom-rcCell.top)*(_NEW_INVENTORY_CELL_HEIGHT));

				if ( IntersectRect(&rcInter, &rcItmRgn, &rc) )
				{
					D3DVECTOR	vecTrans((FLOAT)rcInter.left, (FLOAT)rcInter.top, 0);
					D3DVECTOR	vecScale((FLOAT)(rcInter.right-rcInter.left), (FLOAT)(rcInter.bottom-rcInter.top), 1);

					D3DUtil_InitMaterial(mtrl, (FLOAT)50/255.0f, (FLOAT)100/255.0f, (FLOAT)50/255.0f);
					mtrl.diffuse.a = 1.0f/255.0f;
					g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
				}
			}
			else
			{
				INT nSX = m_rcWnd.left+_NEW_INVEN_CELL_XSTART + rcCell.left*(_NEW_INVENTORY_CELL_WIDTH);
				INT nSY = m_rcWnd.top +_NEW_INVEN_CELL_YSTART + (rcCell.top-m_nStartLineNum)*(_NEW_INVENTORY_CELL_HEIGHT);

				SetRect(&rc, nSX, nSY, nSX+(rcCell.right-rcCell.left)*(_NEW_INVENTORY_CELL_WIDTH), nSY+(rcCell.bottom-rcCell.top)*(_NEW_INVENTORY_CELL_HEIGHT));

				if ( IntersectRect(&rcInter, &rcItmRgn, &rc) )
				{
					D3DVECTOR	vecTrans((FLOAT)rcInter.left, (FLOAT)rcInter.top, 0);
					D3DVECTOR	vecScale((FLOAT)(rcInter.right-rcInter.left), (FLOAT)(rcInter.bottom-rcInter.top), 1);

					D3DUtil_InitMaterial(mtrl, (FLOAT)100/255.0f, (FLOAT)50/255.0f, (FLOAT)50/255.0f);
					mtrl.diffuse.a = 1.0f/255.0f;
					g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
				}
			}
		}
	}

	ShowInvenItem();

	RECT rcGold;
	rcGold.left = m_rcWnd.left+62; rcGold.top = m_rcWnd.top+408; rcGold.right = m_rcWnd.left+160; rcGold.bottom = m_rcWnd.top+425;

	CHAR szStr[MAX_PATH];
	GetNumWithComma(g_xGameProc.m_xMyHero.m_nGlod, szStr);
//	sprintf(szStr, "%d", g_xGameProc.m_xMyHero.m_nGlod);
	g_xMainWnd.PutsHan(NULL, rcGold, RGB(248, 200, 100), RGB(0, 0, 0), szStr, g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 10, 0, FW_BOLD));

	m_xInventoryBtn[_BTN_ID_INVENCLOSE].ChangeRect(m_rcWnd.left+234, m_rcWnd.top+417);
	m_xInventoryBtn[_BTN_ID_FUN1	  ].ChangeRect(m_rcWnd.left+176, m_rcWnd.top+22);
	m_xInventoryBtn[_BTN_ID_FUN2	  ].ChangeRect(m_rcWnd.left+195, m_rcWnd.top+410);
//	m_xInventoryBtn[_BTN_ID_MINIMAPBOOK].ChangeRect(m_rcWnd.left+222, m_rcWnd.top+13);

	switch ( m_bType )
	{
	case _INVEN_TYPE_BAG:
		{
			m_xInventoryBtn[_BTN_ID_INVENCLOSE].ShowGameBtn();
//			m_xInventoryBtn[_BTN_ID_MINIMAPBOOK].ShowGameBtn();

			RECT rcTitle = {m_rcWnd.left+60, m_rcWnd.top+24, m_rcWnd.left+100, m_rcWnd.top+40};
			g_xMainWnd.PutsHan(NULL, rcTitle, RGB(250, 220, 248), RGB(0, 0, 0), g_xMsg.GetMsg(1701));

			RECT rcWeight = {m_rcWnd.left+94, m_rcWnd.top+24, m_rcWnd.left+220, m_rcWnd.top+40};
			sprintf(szStr, "%s: %d / %d", g_xMsg.GetMsg(2501), g_xGameProc.m_xMyHero.m_stAbility.wWeight, g_xGameProc.m_xMyHero.m_stAbility.wMaxWeight);
			RECT rcWeightBack = {rcWeight.left+1, rcWeight.top+1, rcWeight.right+1, rcWeight.bottom+1};
			g_xMainWnd.PutsHan(NULL, rcWeightBack, RGB(10, 10, 10), RGB(0, 0, 0), szStr);
			g_xMainWnd.PutsHan(NULL, rcWeight, RGB(200, 200, 248), RGB(0, 0, 0), szStr);

			// 원보상점, 포인트상점 포인트
			RECT rcPoint = rcGold;
			rcPoint.top += 19;
			rcPoint.bottom += 19;
			GetNumWithComma( g_xGameProc.m_xMyHero.m_nPoint, szStr );
			g_xMainWnd.PutsHan(NULL, rcPoint, RGB(248, 100, 0), RGB(0, 0, 0), szStr, g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 10, 0, FW_BOLD));
		}
		break;
	case _INVEN_TYPE_REPAIR:
		{
			m_xInventoryBtn[_BTN_ID_INVENCLOSE].ShowGameBtn();
//			m_xInventoryBtn[_BTN_ID_MINIMAPBOOK].ShowGameBtn();
			m_xInventoryBtn[_BTN_ID_FUN2].ShowGameBtn();

			RECT rcGold = {m_rcWnd.left+70, m_rcWnd.top+429, m_rcWnd.left+155, m_rcWnd.top+444};
			g_xMainWnd.PutsHan(NULL, rcGold, RGB(250, 150, 100), RGB(0, 0, 0), m_pszPrice);

			RECT rcTitle = {m_rcWnd.left+60, m_rcWnd.top+24, m_rcWnd.left+220, m_rcWnd.top+40};
			g_xMainWnd.PutsHan(NULL, rcTitle, RGB(250, 250, 200), RGB(0, 0, 0), g_xMsg.GetMsg(1702));
		}
		break;
	case _INVEN_TYPE_SELL:
		{
			m_xInventoryBtn[_BTN_ID_INVENCLOSE].ShowGameBtn();
//			m_xInventoryBtn[_BTN_ID_MINIMAPBOOK].ShowGameBtn();
			m_xInventoryBtn[_BTN_ID_FUN2].ShowGameBtn();

			RECT rcGold = {m_rcWnd.left+70, m_rcWnd.top+429, m_rcWnd.left+155, m_rcWnd.top+444};
			g_xMainWnd.PutsHan(NULL, rcGold, RGB(250, 150, 100), RGB(0, 0, 0), m_pszPrice);
			
			RECT rcTitle = {m_rcWnd.left+60, m_rcWnd.top+24, m_rcWnd.left+220, m_rcWnd.top+40};
			g_xMainWnd.PutsHan(NULL, rcTitle, RGB(250, 250, 200), RGB(0, 0, 0), g_xMsg.GetMsg(1703));
		}
		break;
	case _INVEN_TYPE_STORAGE:
		{
			m_xInventoryBtn[_BTN_ID_INVENCLOSE].ShowGameBtn();
//			m_xInventoryBtn[_BTN_ID_MINIMAPBOOK].ShowGameBtn();
			m_xInventoryBtn[_BTN_ID_FUN2].ShowGameBtn();

			RECT rcTitle = {m_rcWnd.left+60, m_rcWnd.top+24, m_rcWnd.left+220, m_rcWnd.top+40};
			g_xMainWnd.PutsHan(NULL, rcTitle, RGB(250, 250, 200), RGB(0, 0, 0), g_xMsg.GetMsg(1704));
		}
		break;
	}
	// 아이템의 상태치 보여주기.
	// ShowInvenItemState();	
}


INT CInventoryWnd::GetInvenCellNum(POINT ptMouse)
{
	INT		nCntX, nCntY, nCntYMax;
	RECT	rc;

	SetRect(&rc, _NEW_INVEN_CELL_XSTART + m_rcWnd.left, _NEW_INVEN_CELL_YSTART + m_rcWnd.top, 
			_NEW_INVEN_CELL_XSTART + m_rcWnd.left + (_NEW_INVENTORY_CELL_WIDTH)*(_INVEN_CELL_XCNT+1), 
			_NEW_INVEN_CELL_YSTART + m_rcWnd.top + (_NEW_INVENTORY_CELL_HEIGHT)*(_NEW_INVEN_CELL_YCNT+1) );
	nCntYMax = _NEW_INVEN_CELL_YCNT;

	if ( PtInRect(&rc, ptMouse) )
	{
		for ( nCntY = 0; nCntY < nCntYMax; nCntY++ )
		{
			for ( nCntX = 0; nCntX <  _INVEN_CELL_XCNT; nCntX++ )
			{
				INT nSX, nSY;
				nSX = m_rcWnd.left+_NEW_INVEN_CELL_XSTART + nCntX*(_NEW_INVENTORY_CELL_WIDTH);
				nSY = m_rcWnd.top +_NEW_INVEN_CELL_YSTART + nCntY*(_NEW_INVENTORY_CELL_HEIGHT);

				SetRect(&rc, nSX, nSY, nSX+(_NEW_INVENTORY_CELL_WIDTH), nSY+(_NEW_INVENTORY_CELL_HEIGHT));
				
				if ( PtInRect(&rc, ptMouse) )
				{
					return (nCntX+(m_nStartLineNum+nCntY)*_INVEN_CELL_XCNT);
				}
			}
		}
	}

	return -1;
}


INT CInventoryWnd::GetInvenItemNum(POINT ptMouse)
{
	INT		nCurrCell;

	nCurrCell = GetInvenCellNum(ptMouse);

	if ( nCurrCell != -1 && m_shItemSetInfo[nCurrCell] != -1 )
		return m_shItemSetInfo[nCurrCell] % 1000;

	return -1;
}


INT CInventoryWnd::GetEmptyInvenNum()
{
	for ( INT nCnt = 0; nCnt < _MAX_INVEN_ITEM; nCnt++ )
	{
		if ( m_stInventoryItem[nCnt].bSetted == FALSE )
		{
			return nCnt;
		}
	}

	return -1;
}

BOOL CInventoryWnd::CanItemInsert(INT nCellNum, CItem* pxItem, RECT& rcCell)
{
	INT  nCellWidth, nCellHeight;
	
	GetCellWH(pxItem->m_stItemInfo.stStdItem.wLooks, nCellWidth, nCellHeight);

	if ( nCellNum != -1 )
	{
		POINT ptCell = {nCellNum%_INVEN_CELL_XCNT, nCellNum/_INVEN_CELL_XCNT};

		INT	 nSX, nSY;

		nSX	   = m_rcWnd.left+_NEW_INVEN_CELL_XSTART + ptCell.x*(_NEW_INVENTORY_CELL_WIDTH);
		nSY	   = m_rcWnd.top +_NEW_INVEN_CELL_YSTART + ptCell.y*(_NEW_INVENTORY_CELL_HEIGHT);

		SetRect(&rcCell, nSX, nSY, nSX+(_NEW_INVENTORY_CELL_WIDTH), nSY+(_NEW_INVENTORY_CELL_HEIGHT));

		if ( nCellWidth % 2 == 0 )
		{
			if ( g_xGameProc.m_ptMousePos.x > rcCell.left + (rcCell.right - rcCell.left)/2 )
			{
				ptCell.x++;
			}
		}

		if ( nCellHeight % 2 == 0 )
		{
			if ( g_xGameProc.m_ptMousePos.y > rcCell.top + (rcCell.bottom - rcCell.top)/2 )
			{
				ptCell.y++;
			}
		}

		rcCell.left   = ptCell.x - nCellWidth /2;
		rcCell.top    = ptCell.y - nCellHeight/2;
		rcCell.right  = rcCell.left + nCellWidth;
		rcCell.bottom = rcCell.top  + nCellHeight;

		BOOL bCheck = TRUE;

		for ( INT nYCnt = rcCell.top; nYCnt < rcCell.bottom; nYCnt++ )
		{
			if ( nYCnt < 0 )
			{
				bCheck = FALSE;
				break;
			}
			if ( nYCnt >= _INVEN_TOTAL_CELL )
			{
				bCheck = FALSE;
				break;
			}
			for ( INT nXCnt = rcCell.left; nXCnt < rcCell.right; nXCnt++ )
			{
				if ( nXCnt < 0 )
				{
					bCheck = FALSE;
					break;
				}
				if ( nXCnt >= _INVEN_CELL_XCNT )
				{
					bCheck = FALSE;
					break;
				}

				if ( m_shItemSetInfo[nXCnt+nYCnt*_INVEN_CELL_XCNT] != -1 )
				{
					bCheck = FALSE;
					break;
				}				
			}
		}		

		if ( bCheck )
		{
			return TRUE;
		}
	}

	return FALSE;
}

VOID CInventoryWnd::SetItemState(CItem* pxItem, INT nItemNum, LPRECT lprcCell)
{
	INT  nXCnt, nYCnt, nXCntEX, nYCntEX, nCellX, nCellY;
	BOOL bCheck;

	// 원하는곳의 위치에 들어간다.
	if ( nItemNum != -1 && lprcCell)
	{
		for ( nYCnt = lprcCell->top; nYCnt < lprcCell->bottom; nYCnt++ )
		{
			for ( nXCnt = lprcCell->left; nXCnt < lprcCell->right; nXCnt++ )
			{
				m_shItemSetInfo[nXCnt+nYCnt*_INVEN_CELL_XCNT] = (SHORT)nItemNum;

				if ( nXCnt == lprcCell->left && nYCnt == lprcCell->top )
				{
					m_shItemSetInfo[nXCnt+nYCnt*_INVEN_CELL_XCNT] += 1000;
				}
			}
		}

		m_stInventoryItem[nItemNum].bSetted = TRUE;
		m_stInventoryItem[nItemNum].nWidth	= lprcCell->right - lprcCell->left;
		m_stInventoryItem[nItemNum].nHeight	= lprcCell->bottom - lprcCell->top;
		memcpy(&m_stInventoryItem[nItemNum].xItem, pxItem, sizeof(CItem));
	}
	// 비어있는 위치의 젤처음에 들어간다.
	else
	{
		RECT rcCell;
		INT nCellWidth, nCellHeight;
		GetCellWH(pxItem->m_stItemInfo.stStdItem.wLooks, nCellWidth, nCellHeight);
		SetRect(&rcCell, 0, 0, nCellWidth, nCellHeight);

		for ( nYCnt = 0; nYCnt < _INVEN_MAX_CELL_YCNT; nYCnt++ )
		{
			for ( nXCnt = 0; nXCnt < _INVEN_CELL_XCNT; nXCnt++ )
			{
				bCheck = FALSE;

				for ( nYCntEX = rcCell.top; nYCntEX < rcCell.bottom; nYCntEX++ )
				{
					for ( nXCntEX = rcCell.left; nXCntEX < rcCell.right; nXCntEX++ )
					{
						nCellX = nXCntEX + nXCnt;
						nCellY = nYCntEX + nYCnt;

						if ( nCellX < 0 || nCellY < 0 || nCellX >= _INVEN_CELL_XCNT || nCellY >= _INVEN_TOTAL_CELL )
						{
							bCheck = TRUE;
						}
						if ( m_shItemSetInfo[nCellX+nCellY*_INVEN_CELL_XCNT] != -1 )
						{
							bCheck = TRUE;
						}
						
						if ( bCheck )
						{
							continue;
						}
					}
				}		
				
				if ( !bCheck )
				{
					for ( nYCntEX = rcCell.top; nYCntEX < rcCell.bottom; nYCntEX++ )
					{
						for ( nXCntEX = rcCell.left; nXCntEX < rcCell.right; nXCntEX++ )
						{
							nCellX = nXCntEX + nXCnt;
							nCellY = nYCntEX + nYCnt;

							m_shItemSetInfo[nCellX+nCellY*_INVEN_CELL_XCNT] = (SHORT)nItemNum;

							if ( nCellX == nXCnt + rcCell.left && nCellY == nYCnt + rcCell.top )
							{
								m_shItemSetInfo[nCellX+nCellY*_INVEN_CELL_XCNT] += 1000;
							}
						}
					}		

					m_stInventoryItem[nItemNum].bSetted = TRUE;
					m_stInventoryItem[nItemNum].nWidth	= nCellWidth;
					m_stInventoryItem[nItemNum].nHeight	= nCellHeight;
					memcpy(&m_stInventoryItem[nItemNum].xItem, pxItem, sizeof(CItem));
					return;
				}
				
			}
		}			
	}
}

BOOL CInventoryWnd::GetCellWH(WORD wLooks, INT& nCellWidth, INT& nCellHeight)
{
	CWHWilImageData*	pxItemImg;	
	pxItemImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_INVENTORY];

	if ( pxItemImg->NewSetIndex(wLooks) )
	{
		nCellWidth = pxItemImg->m_lpstNewCurrWilImageInfo->shWidth/(_NEW_INVENTORY_CELL_WIDTH);
		if ( pxItemImg->m_lpstNewCurrWilImageInfo->shWidth % (_NEW_INVENTORY_CELL_WIDTH) )
			nCellWidth++;

		nCellHeight = pxItemImg->m_lpstNewCurrWilImageInfo->shHeight/(_NEW_INVENTORY_CELL_HEIGHT);
		if ( pxItemImg->m_lpstNewCurrWilImageInfo->shHeight % (_NEW_INVENTORY_CELL_HEIGHT) )
			nCellHeight++;
		return TRUE;
	}
	nCellWidth  = 0;
	nCellHeight = 0;

	return FALSE;
}

VOID CInventoryWnd::ShowInvenItem()
{
	INT		nCntX, nCntY, nLoopSY, nCurrCell, nItmNum, nCurrItmNum;
	RECT	rcItemCell;

	nLoopSY = m_nStartLineNum - 5;

	if ( nLoopSY < 0 )
	{
		nLoopSY = 0;
	}

	INT		nYCellNum = _NEW_INVEN_CELL_YCNT;

	for ( nCntY = nLoopSY; nCntY < m_nStartLineNum + nYCellNum; nCntY++ )
	{
		for ( nCntX = 0; nCntX <  _INVEN_CELL_XCNT; nCntX++ )
		{
			nCurrCell = nCntX + nCntY*_INVEN_CELL_XCNT;
			nItmNum	  = m_shItemSetInfo[nCurrCell];

			if ( nItmNum >= 1000 )
			{						
				nCurrItmNum = nItmNum % 1000;
				
				if ( m_stInventoryItem[nCurrItmNum].bSetted )
				{
					INT nSX, nSY, nCX, nCY;
					nSX = m_rcWnd.left+_NEW_INVEN_CELL_XSTART + nCntX*(_NEW_INVENTORY_CELL_WIDTH);
					nSY = m_rcWnd.top +_NEW_INVEN_CELL_YSTART+ (nCntY-m_nStartLineNum)*(_NEW_INVENTORY_CELL_HEIGHT);

					rcItemCell.left   = nSX;
					rcItemCell.top    = nSY;
					rcItemCell.right  = nSX + (_NEW_INVENTORY_CELL_WIDTH)  * m_stInventoryItem[nCurrItmNum].nWidth;
					rcItemCell.bottom = nSY + (_NEW_INVENTORY_CELL_HEIGHT) * m_stInventoryItem[nCurrItmNum].nHeight;

//					g_xMainWnd.DrawWithGDI(&rcItemCell, NULL, RGB(200, 200, 200), 1);
					
					CWHWilImageData* pxItemImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_INVENTORY];
					
					if ( pxItemImg->NewSetIndex(m_stInventoryItem[nCurrItmNum].xItem.m_stItemInfo.stStdItem.wLooks) )
					{
						nCX = rcItemCell.left + (rcItemCell.right  - rcItemCell.left)/2;
						nCY = rcItemCell.top  + (rcItemCell.bottom - rcItemCell.top)/2;

						nSX = nCX - pxItemImg->m_lpstNewCurrWilImageInfo->shWidth/2;
						nSY = nCY - pxItemImg->m_lpstNewCurrWilImageInfo->shHeight/2;

						RECT rcImg;
						SetRect(&rcImg, nSX, nSY, nSX+pxItemImg->m_lpstNewCurrWilImageInfo->shWidth, nSY+pxItemImg->m_lpstNewCurrWilImageInfo->shHeight);

						if ( rcImg.top < m_rcWnd.top +_NEW_INVEN_CELL_YSTART )
						{
							rcImg.top = m_rcWnd.top +_NEW_INVEN_CELL_YSTART ;
						}

						if ( rcImg.bottom > m_rcWnd.top + _NEW_INVEN_CELL_YSTART + (_NEW_INVEN_CELL_YCNT)*(_NEW_INVENTORY_CELL_WIDTH) )
						{
							rcImg.bottom = m_rcWnd.top + _NEW_INVEN_CELL_YSTART + (_NEW_INVEN_CELL_YCNT)*(_NEW_INVENTORY_CELL_HEIGHT) ;
						}

						rcImg.top -= nSY;
						rcImg.bottom -= nSY+1;
						rcImg.left -= nSX;
						rcImg.right -= nSX;

//						g_xMainWnd.DrawWithGDI(&rcImg, NULL, RGB(200, 200, 200), 1);

						WORD wClr = 0XFFFF;
						
						if ( m_stInventoryItem[nCurrItmNum].xItem.m_stItemInfo.stStdItem.bStdMode == 10 || m_stInventoryItem[nCurrItmNum].xItem.m_stItemInfo.stStdItem.bStdMode == 11 )
						{
							wClr = g_xMainWnd.ConvertColor24To16(RGB(m_stInventoryItem[nCurrItmNum].xItem.m_stItemInfo.bLevel_R, 
																     LOBYTE(m_stInventoryItem[nCurrItmNum].xItem.m_stItemInfo.wAmount_GB), 
																	 HIBYTE(m_stInventoryItem[nCurrItmNum].xItem.m_stItemInfo.wAmount_GB))); 
						}

						g_xMainWnd.DrawWithImageForComp(nSX, nSY, &rcImg, (WORD*)pxItemImg->m_pbCurrImage, wClr);

						if (m_stInventoryItem[nCurrItmNum].xItem.m_stItemInfo.stStdItem.bThrow >= _MULTIPLE_TYPE_ITEM)
						{
							RECT rc;
							CHAR pszTmp[MAX_PATH];

							if ( nCntY >= m_nStartLineNum  && nCntY < m_nStartLineNum+_NEW_INVEN_CELL_YCNT )
							{
								DWORD	dwCount = m_stInventoryItem[nCurrItmNum].xItem.m_stItemInfo.wAmount_GB;

								INT		nCnt = 0;
								nCnt = log10(dwCount);

								sprintf(pszTmp, "%d", dwCount);
								g_xMainWnd.PutsHan(NULL, rcItemCell.left + 23 - (nCnt * 5), rcItemCell.top + 22, RGB(255, 255, 0), RGB(0,0,0), pszTmp);
							}
						}

						if ( m_stParkItem.bSetted )
						{
							if ( nCurrItmNum == m_stParkItem.nItemNum )
							{
								RECT rcItmRgn;
								RECT rcInter;

								SetRect(&rcItmRgn, _NEW_INVEN_CELL_XSTART + m_rcWnd.left , _NEW_INVEN_CELL_YSTART+ m_rcWnd.top, 
										_NEW_INVEN_CELL_XSTART + m_rcWnd.left + (_NEW_INVENTORY_CELL_WIDTH)*(_INVEN_CELL_XCNT), 
										_NEW_INVEN_CELL_YSTART + m_rcWnd.top + (_NEW_INVENTORY_CELL_HEIGHT)*(_NEW_INVEN_CELL_YCNT));

								if ( IntersectRect(&rcInter, &rcItmRgn, &rcItemCell) )
								{
									D3DMATERIAL7 mtrl;
									D3DVECTOR	vecTrans((FLOAT)rcInter.left, (FLOAT)rcInter.top, 0);
									D3DVECTOR	vecScale((FLOAT)(rcInter.right-rcInter.left), (FLOAT)(rcInter.bottom-rcInter.top), 1);

									D3DUtil_InitMaterial(mtrl, (FLOAT)50/255.0f, (FLOAT)100/255.0f, (FLOAT)200/255.0f);
									mtrl.diffuse.a = 1.0f/255.0f;
									g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);


								}
							}
						}
					}
				}
			}
		}
	}
}


/******************************************************************************************************************

	함수명 : CInventoryWnd::ShowInvenItemState()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CInventoryWnd::ShowInvenItemState()
{
	if ( !g_xGameProc.m_xInterface.m_stCommonItem.bSetted )
	{
		INT nInvenItemNum = GetInvenItemNum(g_xGameProc.m_ptMousePos);
		if ( nInvenItemNum != -1 )
		{
			if ( m_stInventoryItem[nInvenItemNum].bSetted )
			{
				m_stInventoryItem[nInvenItemNum].xItem.ShowItemStatus(g_xGameProc.m_ptMousePos.x + 10, g_xGameProc.m_ptMousePos.y + 10);
			}
		}
	}
}













/******************************************************************************************************************

	함수명 : CInventoryWnd::DeleteInventoryCurrItem()

	작성자 : 
	작성일 : 

	목적   : 인벤토리의 해당셀 아이템을 지운다.
	입력   : INT nInventoryNum
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CInventoryWnd::DeleteInvenItem(INT nInvenItemNum)
{
	BOOL bRtn = FALSE;
	for ( INT nCnt = 0; nCnt <_INVEN_TOTAL_CELL; nCnt++ )
	{
		if ( m_shItemSetInfo[nCnt] == nInvenItemNum || m_shItemSetInfo[nCnt] == nInvenItemNum+1000 )
		{
			m_shItemSetInfo[nCnt] = -1;
			bRtn = TRUE;
		}
	}	
	ZeroMemory(&m_stInventoryItem[nInvenItemNum], sizeof(INVENITEMSET));

	return bRtn;
}



BOOL CInventoryWnd::DeleteInvenItem(INT nMakeIndex, CHAR* szName)
{
	BOOL bRtn = FALSE;
	for ( INT nCnt = 0; nCnt < _MAX_INVEN_ITEM; nCnt++ )
	{
		if ( m_stInventoryItem[nCnt].bSetted )
		{
			if ( m_stInventoryItem[nCnt].xItem.m_stItemInfo.nMakeIndex == nMakeIndex )
			{
				if ( !strcmp(m_stInventoryItem[nCnt].xItem.m_stItemInfo.stStdItem.szName, szName) )
				{
					DeleteInvenItem(nCnt);
					bRtn = TRUE;
					break;
				}
			}
		}	
	}

	return bRtn;
}


/******************************************************************************************************************

	함수명 : CInventoryWnd::DeleteInventoryAllItem()

	작성자 : 
	작성일 : 

	목적   : 인벤토리의 모든 아이템을 지운다.
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CInventoryWnd::DeleteAllInvenItem()
{
	for ( INT nCnt = 0; nCnt < _MAX_INVEN_ITEM; nCnt++ )
	{
		DeleteInvenItem(nCnt);
	}
}



/******************************************************************************************************************

	함수명 : CInventoryWnd::AddInvenItem()

	작성자 : 
	작성일 : 

	목적   : 인벤토리에 아이템을 넣는다.
	입력   : CItem xItem
	         INT nInvenNum
	         BOOL bUseInvenNum
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CInventoryWnd::AddInvenItem(CItem xItem, INT nCellNum, BOOL bUseInvenNum)
{
	RECT rcCell;
	if ( bUseInvenNum )
	{
		if ( CanItemInsert(nCellNum, &xItem, rcCell) )
		{
			SetItemState(&xItem, GetEmptyInvenNum(), &rcCell);
			return;
		}
	}

	SetItemState(&xItem, GetEmptyInvenNum());
}



/******************************************************************************************************************

	함수명 : CInventoryWnd::ExtractInvenItem()

	작성자 : 
	작성일 : 

	목적   : 인벤토리에서 현재 번호의 아이템을 뽑아온다.
	입력   : CItem* pxItem
	         INT nInventoryNum
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CInventoryWnd::ExtractInvenItem(CItem* pxItem, INT nInvenItemNum)
{
	if ( m_stInventoryItem[nInvenItemNum].bSetted )
	{
		memcpy(pxItem, &m_stInventoryItem[nInvenItemNum].xItem, sizeof(CItem));

		DeleteInvenItem(nInvenItemNum);
				
		return TRUE;
	}
	return FALSE;
}



/******************************************************************************************************************

	함수명 : CInventoryWnd::ChangeInvenWithCommonOLD()

	작성자 : 
	작성일 : 

	목적   : 인벤토리의 아이템과 공통(마우스)아이템을 바꾼다.
	입력   : INT nInventoryNum
	         LPCOMMONITEMSET pstCommonItemSet
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CInventoryWnd::ChangeInvenWithCommonOLD(INT nInvenCellNum, INT nInvenItemNum, LPCOMMONITEMSET pstCommonItemSet)
{
	if ( pstCommonItemSet->bSetted )
	{
		// 추가 가방
		if( pstCommonItemSet->bIsInvenExWnd )
		{
			g_xClientSocket.ItemMoveBetweenBags( pstCommonItemSet->xItem.m_stItemInfo.nMakeIndex, pstCommonItemSet->xItem.m_stItemInfo.stStdItem.szName );
			return;
		}

		CItem xInvenItem;
		if ( ExtractInvenItem(&xInvenItem, nInvenItemNum) )
		{
			AddInvenItem(pstCommonItemSet->xItem, nInvenCellNum, TRUE);

			pstCommonItemSet->bSetted			= TRUE;
			pstCommonItemSet->xItem				= xInvenItem;
			pstCommonItemSet->bWaitResponse		= FALSE;
			pstCommonItemSet->bIsEquipItem		= FALSE;
			pstCommonItemSet->bIsDealItem		= FALSE;
			pstCommonItemSet->bIsHideItem		= FALSE;
			pstCommonItemSet->bIsBeltItem		= FALSE;
			pstCommonItemSet->xItem.m_shCellNum = (SHORT)nInvenCellNum; 

			// 추가 가방
			pstCommonItemSet->bIsInvenWnd		= TRUE;
			pstCommonItemSet->bIsInvenExWnd		= FALSE;
		}
	}
}

VOID CInventoryWnd::ChangeInvenWithCommon(INT nInvenCellNum, INT nInvenItemNum, LPCOMMONITEMSET pstCommonItemSet)
{
	if ( pstCommonItemSet->bSetted )
	{
		// 추가 가방
		if( pstCommonItemSet->bIsInvenExWnd )
		{
			g_xClientSocket.ItemMoveBetweenBags( pstCommonItemSet->xItem.m_stItemInfo.nMakeIndex, pstCommonItemSet->xItem.m_stItemInfo.stStdItem.szName );
			return;
		}

		CItem xInvenItem;
		if (!pstCommonItemSet->bIsBeltItem)
		{
			if ( ExtractInvenItem(&xInvenItem, nInvenItemNum) )
			{
				AddInvenItem(pstCommonItemSet->xItem, nInvenCellNum, TRUE);

				pstCommonItemSet->bSetted			= TRUE;
				pstCommonItemSet->xItem				= xInvenItem;
				pstCommonItemSet->bWaitResponse		= FALSE;
				pstCommonItemSet->bIsEquipItem		= FALSE;
				pstCommonItemSet->bIsDealItem		= FALSE;
				pstCommonItemSet->bIsHideItem		= FALSE;
				pstCommonItemSet->bIsBeltItem		= FALSE;
				pstCommonItemSet->xItem.m_shCellNum = (SHORT)nInvenCellNum; 

				// 추가 가방
				pstCommonItemSet->bIsInvenWnd		= TRUE;
				pstCommonItemSet->bIsInvenExWnd		= FALSE;
			}
		}
		else
		{
			ZeroMemory(pstCommonItemSet, sizeof(COMMONITEMSET));
		}
	}
}


/******************************************************************************************************************

	함수명 : CInventoryWnd::SetCommonFromInven()

	작성자 : 
	작성일 : 

	목적   : 인벤토리의 해당번호 아이템을 공통(마우스)아이템으로 세팅한다.
	입력   : INT nInventoryNum
	         LPCOMMONITEMSET pstCommonItemSet
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CInventoryWnd::SetCommonFromInven(INT nInvenCellNum, INT nInvenItemNum, LPCOMMONITEMSET pstCommonItemSet)
{
	CItem xInvenItem;
	if ( ExtractInvenItem(&xInvenItem, nInvenItemNum) )
	{
		pstCommonItemSet->bSetted			= TRUE;
		pstCommonItemSet->xItem				= xInvenItem;
		pstCommonItemSet->bWaitResponse		= FALSE;
		pstCommonItemSet->bIsEquipItem		= FALSE;
		pstCommonItemSet->bIsDealItem		= FALSE;
		pstCommonItemSet->bIsHideItem		= FALSE;
		pstCommonItemSet->bIsBeltItem		= FALSE;
		pstCommonItemSet->xItem.m_shCellNum = (SHORT)nInvenCellNum; 

		// 추가 가방
		pstCommonItemSet->bIsInvenWnd		= TRUE;
		pstCommonItemSet->bIsInvenExWnd		= FALSE;

		g_xGameProc.m_xInterface.ItemClickSound(&pstCommonItemSet->xItem);
	}
}




VOID CInventoryWnd::SetCommonFromGold(LPCOMMONITEMSET pstCommonItemSet)
{
	pstCommonItemSet->bSetted			= TRUE;
	pstCommonItemSet->bWaitResponse		= FALSE;
	pstCommonItemSet->bIsEquipItem		= FALSE;
	pstCommonItemSet->bIsDealItem		= FALSE;
	pstCommonItemSet->bIsHideItem		= FALSE;
	pstCommonItemSet->bIsBeltItem		= FALSE;

	// 추가 가방
	pstCommonItemSet->bIsInvenWnd		= TRUE;
	pstCommonItemSet->bIsInvenExWnd		= FALSE;

	strcpy(pstCommonItemSet->xItem.m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(1050));

	g_SoundManager.SndmngrPlayWavSound(_SOUND_MONEY, 0, 0);

	pstCommonItemSet->xItem.m_stItemInfo.stStdItem.wLooks = 124; 
	pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bStdMode = 124; 
}






/******************************************************************************************************************

	함수명 : CInventoryWnd::SetInvenFromCommonOLD()

	작성자 : 
	작성일 : 

	목적   : 공통(마우스)아이템을 인벤토리의 해당번호로 세팅한다.
	입력   : INT nInventoryNum
	         LPCOMMONITEMSET pstCommonItemSet
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CInventoryWnd::SetInvenFromCommonOLD(INT nInvenCellNum, LPCOMMONITEMSET pstCommonItemSet)
{
	if ( pstCommonItemSet->bSetted )
	{
		// 추가 가방
		if( pstCommonItemSet->bIsInvenExWnd )
		{
			g_xClientSocket.ItemMoveBetweenBags( pstCommonItemSet->xItem.m_stItemInfo.nMakeIndex, pstCommonItemSet->xItem.m_stItemInfo.stStdItem.szName );
			return;
		}

		g_xGameProc.m_xInterface.ItemClickSound(&pstCommonItemSet->xItem);

		AddInvenItem(pstCommonItemSet->xItem, nInvenCellNum, TRUE);
		pstCommonItemSet->xItem.m_shCellNum = (SHORT)nInvenCellNum;

		ZeroMemory(pstCommonItemSet, sizeof(COMMONITEMSET));
	}
}

VOID CInventoryWnd::SetInvenFromCommon(INT nInvenCellNum, LPCOMMONITEMSET pstCommonItemSet)
{
	if ( pstCommonItemSet->bSetted )
	{
		// 추가 가방
		if( pstCommonItemSet->bIsInvenExWnd )
		{
			g_xClientSocket.ItemMoveBetweenBags( pstCommonItemSet->xItem.m_stItemInfo.nMakeIndex, pstCommonItemSet->xItem.m_stItemInfo.stStdItem.szName );
			return;
		}

		g_xGameProc.m_xInterface.ItemClickSound(&pstCommonItemSet->xItem);

		if (!pstCommonItemSet->bIsBeltItem)
			AddInvenItem(pstCommonItemSet->xItem, nInvenCellNum, TRUE);

		pstCommonItemSet->xItem.m_shCellNum = (SHORT)nInvenCellNum;

		ZeroMemory(pstCommonItemSet, sizeof(COMMONITEMSET));
	}
}


LPINVENITEMSET CInventoryWnd::FindInvenItem(WORD wLooks)
{
	for ( INT nCnt = 0; nCnt < _MAX_INVEN_ITEM; nCnt++ )
	{
		if ( m_stInventoryItem[nCnt].bSetted )
		{
			if ( m_stInventoryItem[nCnt].xItem.m_stItemInfo.stStdItem.wLooks == wLooks )
//			if ( !strcmp(m_stInventoryItem[nCnt].xItem.m_stItemInfo.stStdItem.szName, pszItemName) )
			{
				return &m_stInventoryItem[nCnt];
			}
		}		
	}

	return NULL;
}

VOID CInventoryWnd::InitParkItem()
{
	m_nPrice = -1;
	ZeroMemory(m_pszPrice, 20);	
	m_stParkItem.bRecvPrice = _PRICE_NONE;
	m_stParkItem.bSetted  = FALSE;
	m_stParkItem.nCellNum = -1;
	m_stParkItem.nItemNum = -1;
}











/******************************************************************************************************************

	함수명 : CInventoryWnd::OnLButtonDown()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : POINT ptMouse
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CInventoryWnd::OnLButtonDown(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse)
{
	INT nCnt, nInventoryNum;

	RECT rcGold;

	SetRect(&rcGold, m_rcWnd.left+15, m_rcWnd.top+390, m_rcWnd.left+57, m_rcWnd.top+417);
	
	if ( PtInRect(&rcGold, ptMouse) )
	{
		if ( pstCommonItemSet && !pstCommonItemSet->bSetted )
		{			
			SetCommonFromGold(pstCommonItemSet);
		}
		return TRUE;
	}

	if ( m_xInvenScrlBar.OnLButtonDown(ptMouse) )
	{
		FLOAT	fScrlRate;

		fScrlRate	= m_xInvenScrlBar.GetScrlRate();
		m_nStartLineNum = (INT)((_INVEN_MAX_CELL_YCNT- _NEW_INVEN_CELL_YCNT)*fScrlRate);

		return TRUE;
	}

	for( nCnt = 0; nCnt < _MAX_INVEN_BTN; nCnt++ )
	{
		if ( m_xInventoryBtn[nCnt].OnLButtonDown(ptMouse) )		
			return TRUE;
	}

	nInventoryNum	  = GetInvenCellNum(ptMouse);

/*	if ( nInventoryNum == -1 )		m_bCanMove = TRUE;
	else													
	{
		if ( nInventoryNum != -1 )
		{
			if ( m_stInventoryItem[nInventoryNum].bSetted )		m_bCanMove = FALSE;
			else												m_bCanMove = TRUE;				
		}
	}
*/	
	return FALSE;
}



/******************************************************************************************************************

	함수명 : CInventoryWnd::OnLButtonUp()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : LPCOMMONITEMSET pstCommonItemSet
	         POINT ptMouse
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CInventoryWnd::OnLButtonUp(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse)
{
	// 더블클릭.
	if ( timeGetTime() - m_dwLClickTime	< 300 )
	{
		if ( pstCommonItemSet && pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse && !pstCommonItemSet->bIsEquipItem && !pstCommonItemSet->bIsDealItem )
		{
			BYTE bStdMode = pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bStdMode;
			WORD wLooks	  = pstCommonItemSet->xItem.m_stItemInfo.stStdItem.wLooks;

			if ( (bStdMode != 0 && bStdMode != 3) ||
				((bStdMode == 0 || bStdMode == 3) && timeGetTime() - m_dwDLClickTime > 2000) || // 물약류, 전서류...(2초지연)
				 (bStdMode == 0 && timeGetTime() - m_dwDLClickTime > 1000 && 
				 (wLooks == 20 || wLooks == 21 || wLooks == 70 || wLooks == 25 || wLooks == 26 || wLooks == 27 || wLooks == 28 || wLooks == 35 || wLooks == 36 || wLooks == 37 || wLooks == 38
				 || wLooks == 63 || wLooks == 53 || wLooks == 32 ) ) // 선화수등..(1초지연)
				 // 추가 예외 63, 53, 32
			   )
/*			if ( bStdMode != 0 || 
				(bStdMode == 0 && timeGetTime() - m_dwDLClickTime > 2000) ||
				(bStdMode == 0 && timeGetTime() - m_dwDLClickTime > 1000 && (wLooks == 20 || wLooks == 21 || wLooks == 70))
			   )*/
			{
				m_dwLClickTime = timeGetTime();

				if ( bStdMode == 0 || bStdMode == 3 )
				{
					m_dwDLClickTime = timeGetTime();
				}
				OnLButtonDoubleClick(pstCommonItemSet, ptMouse);
				return FALSE;
			}
			else
			{
				g_xGameProc.m_xInterface.m_xClientSysMsg.AddSysMsg(g_xMsg.GetMsg(1051));				
			}
		}
	}

	// 보통클릭.
	m_dwLClickTime = timeGetTime();

	INT nInvenItemNum, nInvenCellNum;

	if ( m_xInvenScrlBar.OnLButtonUp(ptMouse) )
	{
		return FALSE;
	}

	// 인벤토리 윈도우를 닫는다.
	if ( m_xInventoryBtn[_BTN_ID_INVENCLOSE].OnLButtonUp(ptMouse) )
	{
		return TRUE;
	}

//	if ( m_xInventoryBtn[_BTN_ID_MINIMAPBOOK].OnLButtonUp(ptMouse) )
//	{
//		g_xGameProc.m_xInterface.WindowActivate(_WND_ID_VIEWMINIMAP);
//	}

	nInvenCellNum  = GetInvenCellNum(ptMouse);
	nInvenItemNum  = GetInvenItemNum(ptMouse);

	if ( pstCommonItemSet && pstCommonItemSet->bSetted && !strcmp(pstCommonItemSet->xItem.m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(1050)) )
	{
		return FALSE;
	}

	// 현재 아이템이 어떤 응답을 대기중이라면.
	if ( pstCommonItemSet->bSetted && pstCommonItemSet->bWaitResponse )
	{
		return FALSE;
	}

	if ( m_bType == _INVEN_TYPE_BAG )
	{
		// 공통(마우스)아이템에 장착창에서 온 아이템이 있고, 서버로부터 응답신호를 기다리는 중이 아니라면, 아이템 착용을 Off시킨다.
		if ( pstCommonItemSet->bSetted && pstCommonItemSet->bIsEquipItem && !pstCommonItemSet->bWaitResponse && !pstCommonItemSet->bIsDealItem && !pstCommonItemSet->bIsUtilItem )
		{
			if ( nInvenCellNum != -1 )
			{
				g_xClientSocket.SendTakeOnOffItem(CM_TAKEOFFITEM, (BYTE)pstCommonItemSet->xItem.m_shCellNum, pstCommonItemSet->xItem.m_stItemInfo.stStdItem.szName, pstCommonItemSet->xItem.m_stItemInfo.nMakeIndex);
				pstCommonItemSet->bWaitResponse	= TRUE;
				return FALSE;
			}
		}

		if ( pstCommonItemSet->bSetted && pstCommonItemSet->bIsDealItem && !pstCommonItemSet->bWaitResponse && !pstCommonItemSet->bIsEquipItem && !pstCommonItemSet->bIsUtilItem )
		{
			if ( nInvenCellNum != -1 )
			{
				g_xClientSocket.SendDelDealItem(pstCommonItemSet->xItem.m_stItemInfo.stStdItem.szName, pstCommonItemSet->xItem.m_stItemInfo.nMakeIndex);
				pstCommonItemSet->bWaitResponse	= TRUE;
				return FALSE;
			}
		}

		// 인벤토리 셀영역에서 클릭한경우.
		if ( nInvenCellNum != -1 )
		{
			// 클릭한인벤토리에 아이템이 있을경우.
			if ( nInvenItemNum != -1 && m_stInventoryItem[nInvenItemNum].bSetted )
			{
				// 공통(마우스)아이템셋이 비어있으면,
				if ( !pstCommonItemSet->bSetted )
				{				  
					// 마우스에 아이템을 붙인다.
					SetCommonFromInven(nInvenCellNum, nInvenItemNum, pstCommonItemSet);
				}
				// 공통(마우스)아이템셋은 있고, 서버로부터 응답신호를 기다리는 중이 아니며, 장착아이템이 아닐때에.
				else if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse && !pstCommonItemSet->bIsEquipItem && !pstCommonItemSet->bIsDealItem && !pstCommonItemSet->bIsUtilItem )
				{
					ChangeInvenWithCommon(nInvenCellNum, nInvenItemNum, pstCommonItemSet);
				}
			}
			// 클릭한 인벤토리에 아이템이 없을경우.
			else
			{
				// 공통(마우스)아이템셋은 있고, 서버로부터 응답신호를 기다리는 중이 아니면,
				if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse && !pstCommonItemSet->bIsEquipItem && !pstCommonItemSet->bIsDealItem && !pstCommonItemSet->bIsUtilItem )
				{
					SetInvenFromCommon(nInvenCellNum, pstCommonItemSet);
				}
			}
		}
	}
	else
	{
		if ( nInvenCellNum != -1 )
		{
			// 공통(마우스)아이템셋은 있고, 서버로부터 응답신호를 기다리는 중이 아니면,
			if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse && !pstCommonItemSet->bIsEquipItem && !pstCommonItemSet->bIsDealItem )
			{				  
				SetInvenFromCommonOLD(nInvenCellNum, pstCommonItemSet);
			}
			else
			{				
				if ( m_stParkItem.bRecvPrice != _PRICE_RECEIVING )
				{
					if ( nInvenItemNum != -1 && m_stInventoryItem[nInvenItemNum].bSetted )
					{
						m_stParkItem.bSetted = TRUE;
						m_stParkItem.nCellNum = nInvenCellNum;
						m_stParkItem.nItemNum = nInvenItemNum;
						m_stParkItem.bRecvPrice = _PRICE_NONE;

						INT nItem = m_stParkItem.nItemNum;

						 if ( m_bType == _INVEN_TYPE_SELL )
						 {
							 g_xClientSocket.SendQueryPrice(m_stInventoryItem[nItem].xItem.m_stItemInfo.nMakeIndex, m_nMerchantID, m_stInventoryItem[nItem].xItem.m_stItemInfo.stStdItem.szName);
							 m_stParkItem.bRecvPrice = _PRICE_RECEIVING;
						 }
						 else if ( m_bType == _INVEN_TYPE_REPAIR )
						 {
							 g_xClientSocket.SendQueryRepairCost(m_stInventoryItem[nItem].xItem.m_stItemInfo.nMakeIndex, m_nMerchantID, m_stInventoryItem[nItem].xItem.m_stItemInfo.stStdItem.szName);
							 m_stParkItem.bRecvPrice = _PRICE_RECEIVING;
						 }
					}
					else
					{
						InitParkItem();
					}
				}
			}
		}		

		if ( m_xInventoryBtn[_BTN_ID_FUN2].OnLButtonUp(ptMouse) )
		{
			if ( m_stParkItem.bSetted )
			{
				INT nItem = m_stParkItem.nItemNum;

				if ( m_stParkItem.bRecvPrice == _PRICE_RECEIVED )
				{
					 if ( m_bType == _INVEN_TYPE_SELL )
					 {
						 if (m_stInventoryItem[nItem].xItem.m_stItemInfo.stStdItem.bThrow >= _MULTIPLE_TYPE_ITEM)
						 {
							 DWORD	dwCount = m_stInventoryItem[nItem].xItem.m_stItemInfo.wAmount_GB;

							 if (dwCount >  1)
								 g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_SELLMULTIPLEITEM, _YESNO, g_xMsg.GetMsg(1705), TRUE);
							 else
								 g_xClientSocket.SendSellItem(m_stInventoryItem[nItem].xItem.m_stItemInfo.nMakeIndex, m_nMerchantID, m_stInventoryItem[nItem].xItem.m_stItemInfo.stStdItem.szName, 1);
						 }
						 else
						 {
							 g_xClientSocket.SendSellItem(m_stInventoryItem[nItem].xItem.m_stItemInfo.nMakeIndex, m_nMerchantID, m_stInventoryItem[nItem].xItem.m_stItemInfo.stStdItem.szName);
						 }
					 }
					 else if ( m_bType == _INVEN_TYPE_REPAIR )
					 {
						 if ( m_nPrice != -1 )
						 {
							 g_xClientSocket.SendRepairItem(m_stInventoryItem[nItem].xItem.m_stItemInfo.nMakeIndex, m_nMerchantID, m_stInventoryItem[nItem].xItem.m_stItemInfo.stStdItem.szName);
						 }
					 }
				}

				if ( m_bType == _INVEN_TYPE_STORAGE )
				{
					if (m_stInventoryItem[nItem].xItem.m_stItemInfo.stStdItem.bThrow >= _MULTIPLE_TYPE_ITEM)
					{
						DWORD	dwCount = m_stInventoryItem[nItem].xItem.m_stItemInfo.wAmount_GB;

						if (dwCount >  1)
							g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_SAVEMULTIPLEITEM, _YESNO, g_xMsg.GetMsg(1706), TRUE);
						else
						{
							// 추가 창고
							if( g_xGameProc.m_xInterface.m_xStoreWnd.m_bStorageItemEx )
								g_xClientSocket.SendStorageItemEx(m_stInventoryItem[nItem].xItem.m_stItemInfo.nMakeIndex, m_nMerchantID, m_stInventoryItem[nItem].xItem.m_stItemInfo.stStdItem.szName, 1);
							else					
								g_xClientSocket.SendStorageItem(m_stInventoryItem[nItem].xItem.m_stItemInfo.nMakeIndex, m_nMerchantID, m_stInventoryItem[nItem].xItem.m_stItemInfo.stStdItem.szName, 1);
						}
					}
					else
					{
						// 추가 창고
						if( g_xGameProc.m_xInterface.m_xStoreWnd.m_bStorageItemEx )
							g_xClientSocket.SendStorageItemEx(m_stInventoryItem[nItem].xItem.m_stItemInfo.nMakeIndex, m_nMerchantID, m_stInventoryItem[nItem].xItem.m_stItemInfo.stStdItem.szName, 1);
						else				
							g_xClientSocket.SendStorageItem(m_stInventoryItem[nItem].xItem.m_stItemInfo.nMakeIndex, m_nMerchantID, m_stInventoryItem[nItem].xItem.m_stItemInfo.stStdItem.szName);
					}
				}
			}
		}
	}

	return FALSE;
}



/******************************************************************************************************************

	함수명 : CInventoryWnd::OnLButtonDoubleClick()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : LPCOMMONITEMSET pstCommonItemSet
	         POINT ptMouse
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CInventoryWnd::OnLButtonDoubleClick(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse)
{	
	INT nInvenItemNum, nInvenCellNum;

	nInvenCellNum  = GetInvenCellNum(ptMouse);
	nInvenItemNum  = GetInvenItemNum(ptMouse);

	// 현재 아이템이 어떤 응답을 대기중이라면.
	if ( pstCommonItemSet->bSetted && pstCommonItemSet->bWaitResponse )
	{
		return FALSE;
	}

	if ( pstCommonItemSet && pstCommonItemSet->bSetted && !strcmp(pstCommonItemSet->xItem.m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(1050)) )
	{
		return FALSE;
	}

	if ( m_bType == _INVEN_TYPE_BAG )
	{
		if ( nInvenCellNum != -1 )
		{
			// 클릭한인벤토리에 아이템이 있을경우.
			if ( nInvenItemNum != -1 && m_stInventoryItem[nInvenItemNum].bSetted )
			{
				// 공통(마우스)아이템셋이 비어있으면,
				if ( !pstCommonItemSet->bSetted )
				{				  
					// 마우스에 아이템을 붙인다.
					SetCommonFromInven(nInvenCellNum, nInvenItemNum, pstCommonItemSet);
				}
				// 공통(마우스)아이템셋은 있고, 서버로부터 응답신호를 기다리는 중이 아니면,
				else if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse && !pstCommonItemSet->bIsEquipItem && !pstCommonItemSet->bIsDealItem && !pstCommonItemSet->bIsUtilItem )
				{				  
					ChangeInvenWithCommonOLD(nInvenCellNum, nInvenItemNum, pstCommonItemSet);
				}
			}
		}

		if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse && !pstCommonItemSet->bIsEquipItem && !pstCommonItemSet->bIsDealItem && !pstCommonItemSet->bIsUtilItem )
		{
			// 추가 가방
			if( pstCommonItemSet->bIsInvenExWnd )
				return FALSE;
			
			if ( g_xGameProc.m_bUseSpell == FALSE )
			{
				pstCommonItemSet->bWaitResponse = TRUE;
				g_xClientSocket.SendItemIndex(CM_EAT, pstCommonItemSet->xItem.m_stItemInfo.nMakeIndex, pstCommonItemSet->xItem.m_stItemInfo.stStdItem.szName);
				return TRUE;
			}
		}
	}

	return FALSE;
}



/******************************************************************************************************************

	함수명 : CInventoryWnd::Onfve()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : POINT ptMouse
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CInventoryWnd::OnMouseMove(POINT ptMouse)
{
	for( INT nCnt = 0; nCnt < _MAX_INVEN_BTN; nCnt++ )
	{
		m_xInventoryBtn[nCnt].OnMouseMove(ptMouse);
	}

	if ( m_xInvenScrlBar.OnMouseMove(ptMouse) )
	{
		FLOAT	fScrlRate;
		fScrlRate	= m_xInvenScrlBar.GetScrlRate();

		m_nStartLineNum = (INT)((_INVEN_MAX_CELL_YCNT- _NEW_INVEN_CELL_YCNT)*fScrlRate);
		return TRUE;
	}

	return FALSE;
}



/******************************************************************************************************************

	함수명 : CInventoryWnd::OnScrollDown()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CInventoryWnd::OnScrollDown()
{
	if ( m_nStartLineNum > 0 )												m_nStartLineNum--;
}



/******************************************************************************************************************

	함수명 : CInventoryWnd::OnScrollUp()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CInventoryWnd::OnScrollUp()
{
	if ( m_nStartLineNum < _INVEN_MAX_CELL_YCNT - _NEW_INVEN_CELL_YCNT )		m_nStartLineNum++;
}



BOOL CInventoryWnd::OnRButtonDown(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse)
{
	RECT rcGold;

	// 빨리 눌리는것을 방지.
	if ( timeGetTime() - m_dwRClickTime < 500 )
	{
		return TRUE;
	}
	m_dwRClickTime = timeGetTime();

	SetRect(&rcGold, m_rcWnd.left+15, m_rcWnd.top+390, m_rcWnd.left+57, m_rcWnd.top+417);

	if ( PtInRect(&rcGold, ptMouse) )
	{
		if ( pstCommonItemSet && !pstCommonItemSet->bSetted )
		{			
			SetCommonFromGold(pstCommonItemSet);
		}

		return TRUE;
	}

	INT nInvenItemNum, nInvenCellNum;

	nInvenCellNum  = GetInvenCellNum(ptMouse);
	nInvenItemNum  = GetInvenItemNum(ptMouse);

	// 현재 아이템이 어떤 응답을 대기중이라면.
	if ( pstCommonItemSet->bSetted && pstCommonItemSet->bWaitResponse )
	{
		return TRUE;
	}

	if ( m_bType != _INVEN_TYPE_BAG )
	{
		if ( m_stParkItem.bSetted && m_stParkItem.nItemNum == nInvenItemNum )
		{
			INT nItem = m_stParkItem.nItemNum;
			if ( m_stParkItem.bRecvPrice ==  _PRICE_RECEIVED )
			{
				 if ( m_bType == _INVEN_TYPE_SELL )
				 {
					if (m_stInventoryItem[nItem].xItem.m_stItemInfo.stStdItem.bThrow >= _MULTIPLE_TYPE_ITEM)
					{
						DWORD	dwCount = m_stInventoryItem[nItem].xItem.m_stItemInfo.wAmount_GB;

						if (dwCount >  1)
							g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_SELLMULTIPLEITEM, _YESNO, g_xMsg.GetMsg(1705), TRUE);
						else
							g_xClientSocket.SendSellItem(m_stInventoryItem[nItem].xItem.m_stItemInfo.nMakeIndex, m_nMerchantID, m_stInventoryItem[nItem].xItem.m_stItemInfo.stStdItem.szName);
					}
					else
						g_xClientSocket.SendSellItem(m_stInventoryItem[nItem].xItem.m_stItemInfo.nMakeIndex, m_nMerchantID, m_stInventoryItem[nItem].xItem.m_stItemInfo.stStdItem.szName);

					return TRUE;
				 }
				 else if ( m_bType == _INVEN_TYPE_REPAIR )
				 {
					 if ( m_nPrice != -1 )
					 {
						 g_xClientSocket.SendRepairItem(m_stInventoryItem[nItem].xItem.m_stItemInfo.nMakeIndex, m_nMerchantID, m_stInventoryItem[nItem].xItem.m_stItemInfo.stStdItem.szName);
					 }
					 return TRUE;
				 }
			}
			else
			{
				if ( m_bType == _INVEN_TYPE_SELL )
					g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_INVENTORY, _OK, g_xMsg.GetMsg(1455));
				else if ( m_bType == _INVEN_TYPE_REPAIR )
					g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_INVENTORY, _OK, g_xMsg.GetMsg(1708));
			}

			if ( m_bType == _INVEN_TYPE_STORAGE )
			{
				if (m_stInventoryItem[nItem].xItem.m_stItemInfo.stStdItem.bThrow >= _MULTIPLE_TYPE_ITEM)
				{
					DWORD	dwCount = m_stInventoryItem[nItem].xItem.m_stItemInfo.wAmount_GB;

					if (dwCount >  1)
						g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_SAVEMULTIPLEITEM, _YESNO, g_xMsg.GetMsg(1706), TRUE);
					else
					{
						// 추가 창고
						if( g_xGameProc.m_xInterface.m_xStoreWnd.m_bStorageItemEx )
							g_xClientSocket.SendStorageItemEx(m_stInventoryItem[nItem].xItem.m_stItemInfo.nMakeIndex, m_nMerchantID, m_stInventoryItem[nItem].xItem.m_stItemInfo.stStdItem.szName, 1);
						else					
							g_xClientSocket.SendStorageItem(m_stInventoryItem[nItem].xItem.m_stItemInfo.nMakeIndex, m_nMerchantID, m_stInventoryItem[nItem].xItem.m_stItemInfo.stStdItem.szName, 1);
					}
				}
				else
				{
					// 추가 창고
					if( g_xGameProc.m_xInterface.m_xStoreWnd.m_bStorageItemEx )
							g_xClientSocket.SendStorageItemEx(m_stInventoryItem[nItem].xItem.m_stItemInfo.nMakeIndex, m_nMerchantID, m_stInventoryItem[nItem].xItem.m_stItemInfo.stStdItem.szName, 1);
					else				
						g_xClientSocket.SendStorageItem(m_stInventoryItem[nItem].xItem.m_stItemInfo.nMakeIndex, m_nMerchantID, m_stInventoryItem[nItem].xItem.m_stItemInfo.stStdItem.szName);
				}
				
				return TRUE;
			}
		}
	}

	RECT rcItmRgn;

	SetRect(&rcItmRgn, _NEW_INVEN_CELL_XSTART + m_rcWnd.left, _NEW_INVEN_CELL_YSTART+ m_rcWnd.top, 
			_NEW_INVEN_CELL_XSTART + m_rcWnd.left + (_NEW_INVENTORY_CELL_WIDTH)*(_INVEN_CELL_XCNT), 
			_NEW_INVEN_CELL_YSTART + m_rcWnd.top + (_NEW_INVENTORY_CELL_HEIGHT)*(_NEW_INVEN_CELL_YCNT) );

	if ( PtInRect(&rcItmRgn, ptMouse) )
	{
		return TRUE;
	}

	return FALSE;
}

VOID
CInventoryWnd::ChangeItemCount(INT nIdx, DWORD wCount)
{
	CHAR szSysMsg[MAX_PATH];

	if ( g_xGameProc.m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.bThrow == 3 )
	{
		if ( g_xGameProc.m_xInterface.m_stCommonItem.xItem.m_stItemInfo.nMakeIndex == nIdx )
		{
			g_xGameProc.m_xInterface.m_stCommonItem.xItem.m_stItemInfo.wAmount_GB = wCount;
		}
	}
	
	for ( INT nCnt = 0; nCnt < _MAX_INVEN_ITEM; nCnt++ )
	{
		if ( m_stInventoryItem[nCnt].bSetted )
		{
			if (m_stInventoryItem[nCnt].xItem.m_stItemInfo.nMakeIndex == nIdx)
			{
				DWORD	dwCount = 0;
				dwCount = m_stInventoryItem[nCnt].xItem.m_stItemInfo.wAmount_GB;
				
				if (dwCount < wCount)
				{
					INT	nNum = wCount - dwCount;
					sprintf(szSysMsg, g_xMsg.GetMsg(1707), m_stInventoryItem[nCnt].xItem.m_stItemInfo.stStdItem.szName, nNum);
					g_xGameProc.m_xInterface.m_xClientSysMsg.AddSysMsg(szSysMsg);
					g_xGameProc.m_xInterface.ItemClickSound(&m_stInventoryItem[nCnt].xItem);
				}
				
				m_stInventoryItem[nCnt].xItem.m_stItemInfo.wAmount_GB = wCount;

				// 벨트 창에 같은 아이템이 등록되어 있는지를 검사하여 갯수를 변경 시켜 준다.
				INT nBeltNum = 0;

				nBeltNum = g_xGameProc.m_xInterface.m_xBeltWnd.FindSameItemInBelt(m_stInventoryItem[nCnt].xItem);

				if (nBeltNum != -1)
				{
					g_xGameProc.m_xInterface.m_xBeltWnd.m_stBeltItem[nBeltNum].xItem.m_stItemInfo.wAmount_GB = wCount;
				}
			}
		}
	}
}

BOOL
CInventoryWnd::IsThereMultipleItem(CItem xItem)
{
	for ( INT nCnt = 0; nCnt < _MAX_INVEN_ITEM; nCnt++ )
	{
		if ( m_stInventoryItem[nCnt].bSetted )
		{
			if (strcmp(m_stInventoryItem[nCnt].xItem.m_stItemInfo.stStdItem.szName, xItem.m_stItemInfo.stStdItem.szName) == 0)
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}

INT
CInventoryWnd::GetSameItemCount(CItem xItem)
{
	INT nCount = 0;

	for ( INT nCnt = 0; nCnt < _MAX_INVEN_ITEM; nCnt++ )
	{
		if ( m_stInventoryItem[nCnt].bSetted )
		{
			if (xItem.m_stItemInfo.stStdItem.wLooks == m_stInventoryItem[nCnt].xItem.m_stItemInfo.stStdItem.wLooks)
				nCount++;
		}
	}

	return nCount;
}

VOID
CInventoryWnd::SetInvenType(BYTE bType)
{
	m_bType = bType;

	switch ( m_bType )
	{
	case _INVEN_TYPE_BAG:
		{
			m_xInventoryBtn[_BTN_ID_FUN2].ResetGameBtn(-1, -1, -1);
		}
		break;
	case _INVEN_TYPE_REPAIR:
		{
			m_xInventoryBtn[_BTN_ID_FUN2].ResetGameBtn(352, 353, 352);
			m_xInventoryBtn[_BTN_ID_FUN2].ChangeBtnTooltip(g_xMsg.GetMsg(1702));
		}
		break;
	case _INVEN_TYPE_SELL:
		{
			m_xInventoryBtn[_BTN_ID_FUN2].ResetGameBtn(355, 356, 355);
			m_xInventoryBtn[_BTN_ID_FUN2].ChangeBtnTooltip(g_xMsg.GetMsg(1703));
		}
		break;
	case _INVEN_TYPE_STORAGE:
		{
			m_xInventoryBtn[_BTN_ID_FUN2].ResetGameBtn(358, 359, 358);
			m_xInventoryBtn[_BTN_ID_FUN2].ChangeBtnTooltip(g_xMsg.GetMsg(1704));
		}
		break;
	}
}

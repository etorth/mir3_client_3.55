/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"



CExchangeWnd::CExchangeWnd()
{
	Init();
}

CExchangeWnd::~CExchangeWnd()
{
	Destroy();
}

VOID CExchangeWnd::Init()
{
	INT nCnt;

	CGameWnd::Init();

	ZeroMemory(&m_nStartLineNum, sizeof(INT)*2);
	ZeroMemory(&m_nDealGold, sizeof(INT)*2);

	ZeroMemory(&m_pszDealName, 64);
	ZeroMemory(&m_stDealOnItem, sizeof(ITEMSET));

	ZeroMemory(m_stDealItem, sizeof(INVENITEMSET)*_MAX_DEAL_ITEM*2);

	SetRect(&m_rcDealRgn[0], 0, 0, 0, 0);
	SetRect(&m_rcDealRgn[1], 0, 0, 0, 0);

	m_xExchangeBtn.Init();
	mExchange_btnClose.Init();

	m_bIsDealPushed = FALSE;
	m_pstCommonItemSet = NULL;

	memset(m_shItemSetInfo, -1, _DEAL_TOTAL_CELL*sizeof(SHORT)*2);	

	m_xExchangeScrlBar[0].Init();
	m_xExchangeScrlBar[1].Init();
}


VOID CExchangeWnd::Destroy()
{
	CGameWnd::Destroy();
}


VOID CExchangeWnd::CloseExchangeWnd()
{
	ZeroMemory(&m_nStartLineNum, sizeof(INT)*2);
	ZeroMemory(&m_nDealGold, sizeof(INT)*2);
	ZeroMemory(&m_pszDealName, 64);
	ZeroMemory(&m_stDealOnItem, sizeof(ITEMSET));
	ZeroMemory(m_stDealItem, sizeof(INVENITEMSET)*_MAX_DEAL_ITEM*2);

	memset(m_shItemSetInfo, -1, _DEAL_TOTAL_CELL*sizeof(SHORT)*2);	

	m_bIsDealPushed = FALSE;

	m_xExchangeBtn.ChangeBtnTooltip(g_xMsg.GetMsg(1300));
}



VOID CExchangeWnd::CreateExchangeWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove)
{
	CreateGameWnd(nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight);

	SetRect(&m_rcDealRgn[0], m_rcWnd.left, m_rcWnd.top, m_rcWnd.left+(m_rcWnd.right-m_rcWnd.left)/2, m_rcWnd.bottom);
	SetRect(&m_rcDealRgn[1], m_rcWnd.left+(m_rcWnd.right-m_rcWnd.left)/2, m_rcWnd.top, m_rcWnd.right, m_rcWnd.bottom);
	
	m_xExchangeBtn.CreateGameBtn(pxWndImage,372,373, nStartX+227, nStartY+279, g_xMsg.GetMsg(1300), _BTN_TYPE_FOCUS, -1, TRUE);	
	mExchange_btnClose.CreateGameBtn(pxWndImage, 1221, 1222, nStartX+242, nStartY+423, g_xMsg.GetMsg(1052), _BTN_TYPE_FOCUS, 1221, TRUE);
	
	m_xExchangeScrlBar[0].CreateScrlBar(pxWndImage, 1225, _DEAL_CELL_YCNT, 12, 138, 12);
	m_xExchangeScrlBar[1].CreateScrlBar(pxWndImage, 1225, _DEAL_CELL_YCNT, 12, 138, 12);

	m_bOpa = 220;
}

VOID CExchangeWnd::ShowExchangeWnd()
{
	INT		nCnt, nSX, nSY;
	BYTE	bPos;
	RECT	rcItmRgn;

	ShowGameWnd();

	SetRect(&m_rcDealRgn[0], m_rcWnd.left, m_rcWnd.top, m_rcWnd.left+(m_rcWnd.right-m_rcWnd.left)/2, m_rcWnd.bottom);
	SetRect(&m_rcDealRgn[1], m_rcWnd.left+(m_rcWnd.right-m_rcWnd.left)/2, m_rcWnd.top, m_rcWnd.right, m_rcWnd.bottom);

	if ( PtInRect(&m_rcDealRgn[0], g_xGameProc.m_ptMousePos) )
	{
		SetRect(&rcItmRgn, _NEW_LDEAL_CELL_XSTART + m_rcWnd.left, _NEW_LDEAL_CELL_YSTART + m_rcWnd.top, 
				_NEW_LDEAL_CELL_XSTART + m_rcWnd.left + (_NEW_INVENTORY_CELL_WIDTH)*(_NEW_DEAL_CELL_XCNT), 
				_NEW_LDEAL_CELL_YSTART + m_rcWnd.top + (_NEW_INVENTORY_CELL_HEIGHT)*(_NEW_DEAL_CELL_YCNT) );
		bPos = _MY_DEAL;
	}
	else
	{
		SetRect(&rcItmRgn, _RDEAL_CELL_XSTART + m_rcWnd.left, _NEW_RDEAL_CELL_YSTART + m_rcWnd.top, 
				_NEW_RDEAL_CELL_XSTART + m_rcWnd.left + (_NEW_INVENTORY_CELL_WIDTH)*(_NEW_DEAL_CELL_XCNT), 
				_NEW_RDEAL_CELL_YSTART + m_rcWnd.top + (_NEW_INVENTORY_CELL_HEIGHT)*(_NEW_DEAL_CELL_YCNT) );
		bPos = _YOU_DEAL;
	}

	
	if ( PtInRect(&rcItmRgn, g_xGameProc.m_ptMousePos) )
	{
		if ( g_xGameProc.m_xInterface.m_stCommonItem.bSetted && !g_xGameProc.m_xInterface.m_stCommonItem.bIsHideItem )
		{
			RECT rc;
			RECT rcCell;
			RECT rcInter;
			D3DMATERIAL7 mtrl;
			INT nCell = GetDealCellNum(bPos, g_xGameProc.m_ptMousePos);
			
			if ( CanItemInsert(bPos, nCell, &g_xGameProc.m_xInterface.m_stCommonItem.xItem, rcCell) )
			{
				if ( bPos == _MY_DEAL )
				{
					nSX = m_rcWnd.left+_NEW_LDEAL_CELL_XSTART + rcCell.left*(_NEW_INVENTORY_CELL_WIDTH);
					nSY = m_rcWnd.top +_NEW_LDEAL_CELL_YSTART + (rcCell.top-m_nStartLineNum[bPos])*(_NEW_INVENTORY_CELL_HEIGHT);
				}
				else
				{
					nSX = m_rcWnd.left+_NEW_RDEAL_CELL_XSTART + rcCell.left*(_NEW_INVENTORY_CELL_WIDTH);
					nSY = m_rcWnd.top +_NEW_RDEAL_CELL_YSTART + (rcCell.top-m_nStartLineNum[bPos])*(_NEW_INVENTORY_CELL_HEIGHT);
				}

				SetRect(&rc, nSX, nSY, nSX+(rcCell.right-rcCell.left)*(_NEW_INVENTORY_CELL_WIDTH), nSY+(rcCell.bottom-rcCell.top)*(_NEW_INVENTORY_CELL_HEIGHT));

				if ( IntersectRect(&rcInter, &rcItmRgn, &rc) )
				{
					D3DVECTOR	vecTrans((FLOAT)rcInter.left, (FLOAT)rcInter.top, 0);
					D3DVECTOR	vecScale((FLOAT)rcInter.right-rcInter.left, (FLOAT)rcInter.bottom-rcInter.top, 1);

					D3DUtil_InitMaterial(mtrl, (FLOAT)50/255.0f, (FLOAT)100/255.0f, (FLOAT)50/255.0f);
					mtrl.diffuse.a = 1.0f/255.0f;
					g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
				}
			}
			else
			{
				if ( bPos == _MY_DEAL )
				{
					nSX = m_rcWnd.left+_NEW_LDEAL_CELL_XSTART + rcCell.left*(_NEW_INVENTORY_CELL_WIDTH);
					nSY = m_rcWnd.top +_NEW_LDEAL_CELL_YSTART + (rcCell.top-m_nStartLineNum[bPos])*(_NEW_INVENTORY_CELL_HEIGHT);
				}
				else
				{
					nSX = m_rcWnd.left+_NEW_RDEAL_CELL_XSTART + rcCell.left*(_NEW_INVENTORY_CELL_WIDTH);
					nSY = m_rcWnd.top +_NEW_RDEAL_CELL_YSTART + (rcCell.top-m_nStartLineNum[bPos])*(_NEW_INVENTORY_CELL_HEIGHT);
				}

				SetRect(&rc, nSX, nSY, nSX+(rcCell.right-rcCell.left)*(_NEW_INVENTORY_CELL_WIDTH), nSY+(rcCell.bottom-rcCell.top)*(_NEW_INVENTORY_CELL_HEIGHT));

				if ( IntersectRect(&rcInter, &rcItmRgn, &rc) )
				{
					D3DVECTOR	vecTrans((FLOAT)rcInter.left, (FLOAT)rcInter.top, 0);
					D3DVECTOR	vecScale((FLOAT)rcInter.right-rcInter.left, (FLOAT)rcInter.bottom-rcInter.top, 1);

					D3DUtil_InitMaterial(mtrl, (FLOAT)100/255.0f, (FLOAT)50/255.0f, (FLOAT)50/255.0f);
					mtrl.diffuse.a = 1.0f/255.0f;
					g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
				}
			}
		}
	}
/*	for ( INT nCntY = 0; nCntY < _DEAL_CELL_YCNT; nCntY++ )
	{
		for ( INT nCntX = 0; nCntX < _DEAL_CELL_XCNT; nCntX++ )
		{
			RECT rc;
			CHAR szStr[MAX_PATH];
			if ( bPos == _MY_DEAL )
			{
				nSX = m_rcWnd.left+_LDEAL_CELL_XSTART+ nCntX*(_INVENTORY_CELL_WIDTH-2);
				nSY = m_rcWnd.top +_LDEAL_CELL_YSTART+ nCntY*(_INVENTORY_CELL_HEIGHT-2);
			}
			else
			{
				nSX = m_rcWnd.left+_RDEAL_CELL_XSTART+ nCntX*(_INVENTORY_CELL_WIDTH-2);
				nSY = m_rcWnd.top +_RDEAL_CELL_YSTART+ nCntY*(_INVENTORY_CELL_HEIGHT-2);
			}
			SetRect(&rc, nSX, nSY, nSX+(_INVENTORY_CELL_WIDTH-2), nSY+(_INVENTORY_CELL_HEIGHT-2));
			g_xMainWnd.DrawWithGDI(&rc, NULL, RGB(200, 200, 200), 1);
			sprintf(szStr, "%d %d", nCntX, nCntY+m_nStartLineNum[bPos]);
			g_xMainWnd.PutsHan(NULL, nSX, nSY, RGB(248, 200, 100), RGB(0, 0, 0), szStr);
		}
	}
*/

	ShowDealItem();

//	ShowDealItemState(bPos);	

	RECT rc;
	CHAR szStr[MAX_PATH];

	SetRect(&rc, m_rcWnd.left+65, m_rcWnd.top+24, m_rcWnd.left+180, m_rcWnd.top+39);
	g_xMainWnd.PutsHan(NULL, rc, RGB(200, 200, 250), RGB(0, 0, 0), g_xGameProc.m_xMyHero.m_szName);

	SetRect(&rc, m_rcWnd.left+315, m_rcWnd.top+24, m_rcWnd.left+430, m_rcWnd.top+39);
	g_xMainWnd.PutsHan(NULL, rc, RGB(200, 200, 250), RGB(0, 0, 0), m_pszDealName);

	SetRect(&rc, m_rcWnd.left+70, m_rcWnd.top+284, m_rcWnd.left+183, m_rcWnd.top+310);
	GetNumWithComma(m_nDealGold[_MY_DEAL], szStr);

	if ( m_nDealGold[_MY_DEAL] >= 10000000 )
	{
		g_xMainWnd.PutsHan(NULL, rc, RGB( 250,  0,  0), 0, szStr);
	}
	else if ( m_nDealGold[_MY_DEAL] >= 1000000 )
	{
		g_xMainWnd.PutsHan(NULL, rc, RGB( 0,  250,  250), 0, szStr);
	}
	else
	{
		g_xMainWnd.PutsHan(NULL, rc, RGB( 250,  250,  250), 0, szStr);
	}

	SetRect(&rc, m_rcWnd.left+318, m_rcWnd.top+284, m_rcWnd.left+435, m_rcWnd.top+310);
	GetNumWithComma(m_nDealGold[_YOU_DEAL], szStr);
	if ( m_nDealGold[_YOU_DEAL] >= 10000000 )
	{
		g_xMainWnd.PutsHan(NULL, rc, RGB( 250,  0,  0), 0, szStr);
	}
	else if ( m_nDealGold[_YOU_DEAL] >= 1000000 )
	{
		g_xMainWnd.PutsHan(NULL, rc, RGB( 0,  250,  250), 0, szStr);
	}
	else
	{
		g_xMainWnd.PutsHan(NULL, rc, RGB( 250,  250,  250), 0, szStr);
	}

	m_xExchangeScrlBar[0].ShowScrlBar(m_rcWnd.left+226, m_rcWnd.top+70, m_nStartLineNum[0], _DEAL_MAX_CELL_YCNT - _DEAL_CELL_YCNT);
	m_xExchangeScrlBar[1].ShowScrlBar(m_rcWnd.left+467, m_rcWnd.top+70, m_nStartLineNum[1], _DEAL_MAX_CELL_YCNT - _DEAL_CELL_YCNT);

	mExchange_btnClose.ChangeRect(m_rcWnd.left+447, m_rcWnd.top+282);
	m_xExchangeBtn.ShowGameBtn();
	mExchange_btnClose.ShowGameBtn();
}

VOID CExchangeWnd::SetStatusBtnInit()
{
	INT nCnt;

	m_xExchangeBtn.SetBtnState(_BTN_STATE_NORMAL);
}





















VOID CExchangeWnd::DeleteDealItem(BYTE bPos, INT nDealItemNum)
{
	for ( INT nCnt = 0; nCnt <_DEAL_TOTAL_CELL; nCnt++ )
	{
		if ( m_shItemSetInfo[bPos][nCnt] == nDealItemNum || m_shItemSetInfo[bPos][nCnt] == nDealItemNum+1000 )
		{
			m_shItemSetInfo[bPos][nCnt] = -1;
		}
	}	
	ZeroMemory(&m_stDealItem[bPos][nDealItemNum], sizeof(INVENITEMSET));
}



VOID CExchangeWnd::DeleteDealItem(BYTE bPos, INT nMakeIndex, CHAR* szName)
{
	for ( INT nCnt = 0; nCnt < _MAX_DEAL_ITEM; nCnt++ )
	{
		if ( m_stDealItem[bPos][nCnt].bSetted )
		{
			if ( m_stDealItem[bPos][nCnt].xItem.m_stItemInfo.nMakeIndex == nMakeIndex )
			{
				if ( !strcmp(m_stDealItem[bPos][nCnt].xItem.m_stItemInfo.stStdItem.szName, szName) )
				{
					DeleteDealItem(bPos, nCnt);
					break;
				}
			}
		}		
	}
}

VOID CExchangeWnd::AddDealItem(BYTE bPos, CItem xItem, INT nCellNum, BOOL bUseDealNum)
{
	RECT rcCell;
	if ( bUseDealNum )
	{
		if ( CanItemInsert(bPos, nCellNum, &xItem, rcCell) )
		{
			SetItemState(bPos, &xItem, GetEmptyDealNum(bPos), &rcCell);
			return;
		}
	}

	SetItemState(bPos, &xItem, GetEmptyDealNum(bPos));
}


INT CExchangeWnd::GetEmptyDealNum(BYTE bPos)
{
	for ( INT nCnt = 0; nCnt < _MAX_DEAL_ITEM; nCnt++ )
	{
		if ( m_stDealItem[bPos][nCnt].bSetted == FALSE )
		{
			return nCnt;
		}
	}

	return -1;
}

BOOL CExchangeWnd::GetCellWH(WORD wLooks, INT& nCellWidth, INT& nCellHeight)
{
	CWHWilImageData*	pxItemImg;	
	pxItemImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_INVENTORY];

	if ( pxItemImg->NewSetIndex(wLooks) )
	{
		nCellWidth = pxItemImg->m_lpstNewCurrWilImageInfo->shWidth/(_INVENTORY_CELL_WIDTH-2);
		if ( pxItemImg->m_lpstNewCurrWilImageInfo->shWidth % (_INVENTORY_CELL_WIDTH-2) )
			nCellWidth++;

		nCellHeight = pxItemImg->m_lpstNewCurrWilImageInfo->shHeight/(_INVENTORY_CELL_HEIGHT-2);
		if ( pxItemImg->m_lpstNewCurrWilImageInfo->shHeight % (_INVENTORY_CELL_HEIGHT-2) )
			nCellHeight++;

		return TRUE;
	}
	nCellWidth  = 0;
	nCellHeight = 0;

	return FALSE;
}


BOOL CExchangeWnd::CanItemInsert(BYTE bPos, INT nCellNum, CItem* pxItem, RECT& rcCell)
{
	INT  nCellWidth, nCellHeight;
	
	GetCellWH(pxItem->m_stItemInfo.stStdItem.wLooks, nCellWidth, nCellHeight);

	if ( nCellNum != -1 )
	{
		POINT ptCell = {nCellNum%_DEAL_CELL_XCNT, nCellNum/_DEAL_CELL_XCNT};

		INT	 nSX, nSY;

		if ( bPos == _MY_DEAL )
		{
			nSX	   = m_rcWnd.left+_LDEAL_CELL_XSTART + ptCell.x*(_INVENTORY_CELL_WIDTH-2);
			nSY	   = m_rcWnd.top +_LDEAL_CELL_YSTART + ptCell.y*(_INVENTORY_CELL_HEIGHT-2);
		}
		else
		{
			nSX	   = m_rcWnd.left+_RDEAL_CELL_XSTART + ptCell.x*(_INVENTORY_CELL_WIDTH-2);
			nSY	   = m_rcWnd.top +_RDEAL_CELL_YSTART + ptCell.y*(_INVENTORY_CELL_HEIGHT-2);
		}

		SetRect(&rcCell, nSX, nSY, nSX+(_INVENTORY_CELL_WIDTH-2), nSY+(_INVENTORY_CELL_HEIGHT-2));

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
			if ( nYCnt >= _DEAL_MAX_CELL_YCNT )
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
				if ( nXCnt >= _DEAL_CELL_XCNT )
				{
					bCheck = FALSE;
					break;
				}

				if ( m_shItemSetInfo[bPos][nXCnt+nYCnt*_DEAL_CELL_XCNT] != -1 )
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


VOID CExchangeWnd::SetItemState(BYTE bPos, CItem* pxItem, INT nItemNum, LPRECT lprcCell)
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
				m_shItemSetInfo[bPos][nXCnt+nYCnt*_DEAL_CELL_XCNT] = (SHORT)nItemNum;

				if ( nXCnt == lprcCell->left && nYCnt == lprcCell->top )
				{
					m_shItemSetInfo[bPos][nXCnt+nYCnt*_DEAL_CELL_XCNT] += 1000;
				}
			}
		}

		m_stDealItem[bPos][nItemNum].bSetted = TRUE;
		m_stDealItem[bPos][nItemNum].nWidth	 = lprcCell->right - lprcCell->left;
		m_stDealItem[bPos][nItemNum].nHeight = lprcCell->bottom - lprcCell->top;
		memcpy(&m_stDealItem[bPos][nItemNum].xItem, pxItem, sizeof(CItem));
	}
	// 비어있는 위치의 젤처음에 들어간다.
	else
	{
		RECT rcCell;
		INT nCellWidth, nCellHeight;
		GetCellWH(pxItem->m_stItemInfo.stStdItem.wLooks, nCellWidth, nCellHeight);
		SetRect(&rcCell, 0, 0, nCellWidth, nCellHeight);

		for ( nYCnt = 0; nYCnt < _DEAL_MAX_CELL_YCNT; nYCnt++ )
		{
			for ( nXCnt = 0; nXCnt < _DEAL_CELL_XCNT; nXCnt++ )
			{
				bCheck = FALSE;

				for ( nYCntEX = rcCell.top; nYCntEX < rcCell.bottom; nYCntEX++ )
				{
					for ( nXCntEX = rcCell.left; nXCntEX < rcCell.right; nXCntEX++ )
					{
						nCellX = nXCntEX + nXCnt;
						nCellY = nYCntEX + nYCnt;

						if ( nCellX < 0 || nCellY < 0 || nCellX >= _DEAL_CELL_XCNT || nCellY >= _DEAL_MAX_CELL_YCNT )
						{
							bCheck = TRUE;
						}
						if ( m_shItemSetInfo[bPos][nCellX+nCellY*_DEAL_CELL_XCNT] != -1 )
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

							m_shItemSetInfo[bPos][nCellX+nCellY*_DEAL_CELL_XCNT] = (SHORT)nItemNum;

							if ( nCellX == nXCnt + rcCell.left && nCellY == nYCnt + rcCell.top )
							{
								m_shItemSetInfo[bPos][nCellX+nCellY*_DEAL_CELL_XCNT] += 1000;
							}
						}
					}		

					m_stDealItem[bPos][nItemNum].bSetted = TRUE;
					m_stDealItem[bPos][nItemNum].nWidth	= nCellWidth;
					m_stDealItem[bPos][nItemNum].nHeight	= nCellHeight;
					memcpy(&m_stDealItem[bPos][nItemNum].xItem, pxItem, sizeof(CItem));
					return;
				}
				
			}
		}			
	}
}



VOID CExchangeWnd::ShowDealItemState(BYTE bPos)
{
	if ( !g_xGameProc.m_xInterface.m_stCommonItem.bSetted )
	{
		INT nDealItemNum = GetDealItemNum(bPos, g_xGameProc.m_ptMousePos);
		if ( nDealItemNum != -1 )
		{
			if ( m_stDealItem[bPos][nDealItemNum ].bSetted )
			{
				m_stDealItem[bPos][nDealItemNum].xItem.ShowItemStatus(g_xGameProc.m_ptMousePos.x + 10, g_xGameProc.m_ptMousePos.y + 10);
			}
		}
	}
}


VOID CExchangeWnd::ShowDealItemState()
{
	if ( !g_xGameProc.m_xInterface.m_stCommonItem.bSetted )
	{
		BYTE bPos;

		if ( PtInRect(&m_rcDealRgn[0], g_xGameProc.m_ptMousePos) )
		{
			bPos = _MY_DEAL;
		}
		else
		{
			bPos = _YOU_DEAL;
		}

		INT nDealItemNum = GetDealItemNum(bPos, g_xGameProc.m_ptMousePos);
		if ( nDealItemNum != -1 )
		{
			if ( m_stDealItem[bPos][nDealItemNum ].bSetted )
			{
				m_stDealItem[bPos][nDealItemNum].xItem.ShowItemStatus(g_xGameProc.m_ptMousePos.x + 10, g_xGameProc.m_ptMousePos.y + 10);
			}
		}
	}
}



INT CExchangeWnd::GetDealCellNum(BYTE bPos, POINT ptMouse)
{
	INT		nCntX, nCntY;
	RECT	rc;

	if ( bPos == _MY_DEAL )
	{
		SetRect(&rc, _LDEAL_CELL_XSTART + m_rcWnd.left, _LDEAL_CELL_YSTART + m_rcWnd.top, 
				_LDEAL_CELL_XSTART + m_rcWnd.left + (_INVENTORY_CELL_WIDTH-2)*(_DEAL_CELL_XCNT+1), 
				_LDEAL_CELL_YSTART + m_rcWnd.top + (_INVENTORY_CELL_HEIGHT-2)*(_DEAL_CELL_YCNT+1) );
	}
	else
	{
		SetRect(&rc, _RDEAL_CELL_XSTART + m_rcWnd.left, _RDEAL_CELL_YSTART + m_rcWnd.top, 
				_RDEAL_CELL_XSTART + m_rcWnd.left + (_INVENTORY_CELL_WIDTH-2)*(_DEAL_CELL_XCNT+1), 
				_RDEAL_CELL_YSTART + m_rcWnd.top + (_INVENTORY_CELL_HEIGHT-2)*(_DEAL_CELL_YCNT+1) );
	}

	if ( PtInRect(&rc, ptMouse) )
	{
		for ( nCntY = 0; nCntY < _DEAL_CELL_YCNT; nCntY++ )
		{
			for ( nCntX = 0; nCntX <  _DEAL_CELL_XCNT; nCntX++ )
			{
				INT nSX, nSY;

				if ( bPos == _MY_DEAL )
				{
					nSX = m_rcWnd.left+_LDEAL_CELL_XSTART + nCntX*(_INVENTORY_CELL_WIDTH-2);
					nSY = m_rcWnd.top +_LDEAL_CELL_YSTART + nCntY*(_INVENTORY_CELL_HEIGHT-2);
				}
				else
				{
					nSX = m_rcWnd.left+_RDEAL_CELL_XSTART + nCntX*(_INVENTORY_CELL_WIDTH-2);
					nSY = m_rcWnd.top +_RDEAL_CELL_YSTART + nCntY*(_INVENTORY_CELL_HEIGHT-2);
				}

				SetRect(&rc, nSX, nSY, nSX+(_INVENTORY_CELL_WIDTH-2), nSY+(_INVENTORY_CELL_HEIGHT-2));
				if ( PtInRect(&rc, ptMouse) )
				{
					return (nCntX+(m_nStartLineNum[bPos]+nCntY)*_DEAL_CELL_XCNT);
				}
			}
		}
	}

	return -1;
}


INT CExchangeWnd::GetDealItemNum(BYTE bPos, POINT ptMouse)
{
	INT		nCurrCell;

	nCurrCell = GetDealCellNum(bPos, ptMouse);

	if ( nCurrCell != -1 && m_shItemSetInfo[bPos][nCurrCell] != -1 )
		return m_shItemSetInfo[bPos][nCurrCell] % 1000;

	return -1;
}



VOID CExchangeWnd::ShowDealItem()
{
	INT		nCnt, nCntX, nCntY, nLoopSY, nCurrCell, nItmNum, nCurrItmNum;
	RECT	rcItemCell;

	for ( nCnt = 0; nCnt < 2; nCnt++ )
	{
		nLoopSY = m_nStartLineNum[nCnt] - 5;

		if ( nLoopSY < 0 )
		{
			nLoopSY = 0;
		}

		for ( nCntY = nLoopSY; nCntY < m_nStartLineNum[nCnt] + _NEW_DEAL_CELL_YCNT; nCntY++ )
		{
			for ( nCntX = 0; nCntX < _NEW_DEAL_CELL_XCNT; nCntX++ )
			{
				if ( nCntY >= _DEAL_MAX_CELL_YCNT )
				{
					break;
				}

				nCurrCell = nCntX + nCntY*_NEW_DEAL_CELL_XCNT;
				nItmNum	  = m_shItemSetInfo[nCnt][nCurrCell];

				if ( nItmNum >= 1000 )
				{						
					nCurrItmNum = nItmNum % 1000;
					
					if ( m_stDealItem[nCnt][nCurrItmNum].bSetted )
					{
						INT nSX, nSY, nCX, nCY;

						if ( nCnt == _MY_DEAL )
						{
							nSX = m_rcWnd.left+_NEW_LDEAL_CELL_XSTART + nCntX*(_NEW_INVENTORY_CELL_WIDTH);
							nSY = m_rcWnd.top +_NEW_LDEAL_CELL_YSTART + (nCntY-m_nStartLineNum[nCnt])*(_NEW_INVENTORY_CELL_HEIGHT);
						}
						else
						{
							nSX = m_rcWnd.left+_NEW_RDEAL_CELL_XSTART + nCntX*(_NEW_INVENTORY_CELL_WIDTH);
							nSY = m_rcWnd.top +_NEW_RDEAL_CELL_YSTART + (nCntY-m_nStartLineNum[nCnt])*(_NEW_INVENTORY_CELL_HEIGHT);
						}

						rcItemCell.left   = nSX;
						rcItemCell.top    = nSY;
						rcItemCell.right  = nSX + (_NEW_INVENTORY_CELL_WIDTH)  * m_stDealItem[nCnt][nCurrItmNum].nWidth;
						rcItemCell.bottom = nSY + (_NEW_INVENTORY_CELL_HEIGHT) * m_stDealItem[nCnt][nCurrItmNum].nHeight;
						
						CWHWilImageData* pxItemImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_INVENTORY];
						
						if ( pxItemImg->NewSetIndex(m_stDealItem[nCnt][nCurrItmNum].xItem.m_stItemInfo.stStdItem.wLooks) )
						{
							nCX = rcItemCell.left + (rcItemCell.right  - rcItemCell.left)/2;
							nCY = rcItemCell.top  + (rcItemCell.bottom - rcItemCell.top)/2;

							nSX = nCX - pxItemImg->m_lpstNewCurrWilImageInfo->shWidth/2;
							nSY = nCY - pxItemImg->m_lpstNewCurrWilImageInfo->shHeight/2;

							RECT rcImg;
							SetRect(&rcImg, nSX, nSY, nSX+pxItemImg->m_lpstNewCurrWilImageInfo->shWidth, nSY+pxItemImg->m_lpstNewCurrWilImageInfo->shHeight);

							if ( nCnt == _MY_DEAL )
							{
								if ( rcImg.top < m_rcWnd.top +_NEW_LDEAL_CELL_YSTART )
								{
									rcImg.top = m_rcWnd.top +_NEW_LDEAL_CELL_YSTART;
								}

								if ( rcImg.bottom > m_rcWnd.top + _NEW_LDEAL_CELL_YSTART + (_NEW_DEAL_CELL_YCNT)*(_NEW_INVENTORY_CELL_HEIGHT) )
								{
									rcImg.bottom = m_rcWnd.top + _NEW_LDEAL_CELL_YSTART + (_NEW_DEAL_CELL_YCNT)*(_NEW_INVENTORY_CELL_HEIGHT);
								}
							}
							else
							{
								if ( rcImg.top < m_rcWnd.top +_NEW_RDEAL_CELL_YSTART )
								{
									rcImg.top = m_rcWnd.top +_NEW_RDEAL_CELL_YSTART;
								}

								if ( rcImg.bottom > m_rcWnd.top + _NEW_RDEAL_CELL_YSTART + (_NEW_DEAL_CELL_YCNT)*(_NEW_INVENTORY_CELL_HEIGHT) )
								{
									rcImg.bottom = m_rcWnd.top + _NEW_RDEAL_CELL_YSTART + (_NEW_DEAL_CELL_YCNT)*(_NEW_INVENTORY_CELL_HEIGHT);
								}
							}

							rcImg.top -= nSY;
							rcImg.bottom -= nSY + 1;
							rcImg.left -= nSX;
							rcImg.right -= nSX;

							WORD wClr = 0XFFFF;
							
							if ( m_stDealItem[nCnt][nCurrItmNum].xItem.m_stItemInfo.stStdItem.bStdMode == 10 || m_stDealItem[nCnt][nCurrItmNum].xItem.m_stItemInfo.stStdItem.bStdMode == 11 )
							{
								wClr = g_xMainWnd.ConvertColor24To16(RGB(m_stDealItem[nCnt][nCurrItmNum].xItem.m_stItemInfo.bLevel_R, 
																		 LOBYTE(m_stDealItem[nCnt][nCurrItmNum].xItem.m_stItemInfo.wAmount_GB), 
																		 HIBYTE(m_stDealItem[nCnt][nCurrItmNum].xItem.m_stItemInfo.wAmount_GB))); 
							}

							g_xMainWnd.DrawWithImageForComp(nSX, nSY, &rcImg, (WORD*)pxItemImg->m_pbCurrImage, wClr);

							if ( m_stDealItem[nCnt][nCurrItmNum].xItem.m_stItemInfo.stStdItem.bThrow >= _MULTIPLE_TYPE_ITEM)
							{
								if ( nCntY >= m_nStartLineNum[nCnt] && nCntY < m_nStartLineNum[nCnt]+6 )
								{
									RECT rc;
									CHAR pszTmp[MAX_PATH];
									
									sprintf(pszTmp, "%d", m_stDealItem[nCnt][nCurrItmNum].xItem.m_stItemInfo.wAmount_GB);
									g_xMainWnd.PutsHan(NULL, rcItemCell.left + 23, rcItemCell.top + 22, RGB(255, 255, 0), RGB(0,0,0), pszTmp);
								}
							}
						}
					}
				}
			}
		}
	}
}












VOID CExchangeWnd::SetCommonFromDeal(BYTE bPos, INT nDealCellNum, INT nDealItemNum, LPCOMMONITEMSET pstCommonItemSet)
{
	CItem xDealItem;
	if ( ExtractDealItem(bPos, &xDealItem, nDealItemNum) )
	{
		pstCommonItemSet->bSetted			= TRUE;
		pstCommonItemSet->xItem				= xDealItem;
		pstCommonItemSet->bWaitResponse		= FALSE;
		pstCommonItemSet->bIsEquipItem		= FALSE;
		pstCommonItemSet->bIsDealItem		= TRUE;
		pstCommonItemSet->bIsHideItem		= FALSE;
		pstCommonItemSet->bIsBeltItem		= FALSE;
		pstCommonItemSet->xItem.m_shCellNum = (SHORT)nDealCellNum; 

		g_xGameProc.m_xInterface.ItemClickSound(&pstCommonItemSet->xItem);
	}
}


BOOL CExchangeWnd::ExtractDealItem(BYTE bPos, CItem* pxItem, INT nDealItemNum)
{
	if ( m_stDealItem[bPos][nDealItemNum].bSetted )
	{
		memcpy(pxItem, &m_stDealItem[bPos][nDealItemNum].xItem, sizeof(CItem));

		DeleteDealItem(bPos, nDealItemNum);
				
		return TRUE;
	}
	return FALSE;
}


VOID CExchangeWnd::ChangeDealWithCommon(BYTE bPos, INT nDealCellNum, INT nDealItemNum, LPCOMMONITEMSET pstCommonItemSet)
{
	if ( pstCommonItemSet->bSetted )
	{
		CItem xDealItem;
		if ( ExtractDealItem(bPos, &xDealItem, nDealItemNum) )
		{
			AddDealItem(bPos, pstCommonItemSet->xItem, nDealCellNum, TRUE);

			pstCommonItemSet->bSetted			= TRUE;
			pstCommonItemSet->xItem				= xDealItem;
			pstCommonItemSet->bWaitResponse		= FALSE;
			pstCommonItemSet->bIsDealItem		= FALSE;
			pstCommonItemSet->bIsEquipItem		= FALSE;
			pstCommonItemSet->bIsHideItem		= FALSE;
			pstCommonItemSet->bIsBeltItem		= FALSE;
			pstCommonItemSet->xItem.m_shCellNum = (SHORT)nDealCellNum; 
		}
	}
}


VOID CExchangeWnd::SetDealFromCommon(BYTE bPos, INT nDealCellNum, LPCOMMONITEMSET pstCommonItemSet)
{
	if ( pstCommonItemSet->bSetted )
	{
		g_xGameProc.m_xInterface.ItemClickSound(&pstCommonItemSet->xItem);

		AddDealItem(bPos, pstCommonItemSet->xItem, nDealCellNum, TRUE);
		pstCommonItemSet->xItem.m_shCellNum = (SHORT)nDealCellNum;

		ZeroMemory(pstCommonItemSet, sizeof(COMMONITEMSET));
	}
}










VOID CExchangeWnd::SetDealOnItemFromCommon(LPCOMMONITEMSET pstCommonItemSet, INT nCellNum)
{
	if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bIsBeltItem && !pstCommonItemSet->bIsEquipItem )
	{
		m_stDealOnItem.xItem   = pstCommonItemSet->xItem;
		m_stDealOnItem.xItem.m_shCellNum = (SHORT)nCellNum;
		m_stDealOnItem.bSetted = TRUE;
		ZeroMemory(pstCommonItemSet, sizeof(COMMONITEMSET));	
	}
}

VOID CExchangeWnd::SetDealFromDealOnItem()
{
	if ( m_stDealOnItem.bSetted )
	{
		AddDealItem(_MY_DEAL, m_stDealOnItem.xItem, m_stDealOnItem.xItem.m_shCellNum, TRUE);
		ZeroMemory(&m_stDealOnItem, sizeof(ITEMSET));
	}
}







BOOL CExchangeWnd::OnMouseMove(POINT ptMouse)
{
	INT nCnt;

	for ( nCnt = 0; nCnt < 2; nCnt++ )
	{
		if ( m_xExchangeScrlBar[nCnt].OnMouseMove(ptMouse) )
		{
			FLOAT	fScrlRate;
			fScrlRate	= m_xExchangeScrlBar[nCnt].GetScrlRate();

			m_nStartLineNum[nCnt] = (INT)((_DEAL_MAX_CELL_YCNT- _DEAL_CELL_YCNT)*fScrlRate);

			return TRUE;
		}
	}

	m_xExchangeBtn.OnMouseMove(ptMouse);
	mExchange_btnClose.OnMouseMove(ptMouse);
	return TRUE;

	return FALSE;
}

BOOL CExchangeWnd::OnLButtonUp(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse)
{
	BYTE	bPos;
	INT		nCnt;

	if (pstCommonItemSet == NULL)
		return FALSE;

	m_pstCommonItemSet = pstCommonItemSet;

	RECT rcGoldDeal = {m_rcWnd.left+34, m_rcWnd.top+270, m_rcWnd.left+156, m_rcWnd.top+304};
	if ( !strcmp(m_pstCommonItemSet->xItem.m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(1050)) )
	{
		if ( PtInRect(&rcGoldDeal, ptMouse) )
		{
			if ( m_nDealGold[_MY_DEAL] == 0 )
			{
				g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_EXCHANGE, _YESNO, g_xMsg.GetMsg(1304), TRUE, -1, -1, CM_DEALCHGGOLD);
				ZeroMemory(m_pstCommonItemSet, sizeof(COMMONITEMSET));
			}
			else
			{
				g_xGameProc.m_xInterface.m_xClientSysMsg.AddSysMsg(g_xMsg.GetMsg(1302), RGB(50, 255, 255));					
				if ( !strcmp(g_xGameProc.m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(1050)) )
				{
					ZeroMemory(&g_xGameProc.m_xInterface.m_stCommonItem, sizeof(COMMONITEMSET));
				}
			}
		}
		return FALSE;
	}	

	for ( nCnt = 0; nCnt < 2; nCnt++ )
	{
		if ( m_xExchangeScrlBar[nCnt].OnLButtonUp(ptMouse) )
		{
			return FALSE;
		}
	}

	if ( m_bIsDealPushed )
	{
		return FALSE;
	}
	if ( m_xExchangeBtn.OnLButtonUp(ptMouse) )
	{
		if (g_xGameProc.m_xInterface.m_stCommonItem.bIsDealItem == TRUE)
		{
			g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_EXCHANGEMULTIPLEITEM, _OK, g_xMsg.GetMsg(1305), FALSE);
			return FALSE;
		}

		m_xExchangeBtn.ResetGameBtn(374, 374, 374);
		m_xExchangeBtn.ChangeBtnTooltip(g_xMsg.GetMsg(1303));
		g_xClientSocket.SendDealEnd();
		m_bIsDealPushed = TRUE;
		return FALSE;
	}

	if ( mExchange_btnClose.OnLButtonUp(ptMouse) )
	{
		return TRUE;
	}

	if ( PtInRect(&m_rcDealRgn[0], g_xGameProc.m_ptMousePos) )
	{
		bPos = _MY_DEAL;
	}
	else
	{
		bPos = _YOU_DEAL;
	}

	INT nDealItemNum, nDealCellNum;

	if ( bPos == _MY_DEAL )
	{
		m_nDealCellNum  = GetDealCellNum(bPos, ptMouse);
		nDealItemNum  = GetDealItemNum(bPos, ptMouse);

		// 마우스가 Deal영역안에 있을때.
		if ( m_nDealCellNum != -1 )
		{
			// 클릭한Deal영역안에 아이템이 있을경우.
			if ( nDealItemNum != -1 && m_stDealItem[bPos][nDealItemNum].bSetted )
			{
				// 공통(마우스)아이템셋이 비어있으면,
				if ( !m_pstCommonItemSet->bSetted )
				{				  
					// 마우스에 아이템을 붙인다. 그러면 CM_DEALDELITEM을 인벤토리에서 보낸다.
					//SetCommonFromDeal(bPos, m_nDealCellNum, nDealItemNum, m_pstCommonItemSet);
					g_xGameProc.m_xInterface.m_xClientSysMsg.AddSysMsg(g_xMsg.GetMsg(1306), RGB(50, 255, 255));					
				}
				// 공통(마우스)아이템셋은 있고, 서버로부터 응답신호를 기다리는 중이 아니면, 공통아이템을 m_stDealOnItem에 아이템을 세팅해둔다.
				else if ( m_pstCommonItemSet->bSetted && !m_pstCommonItemSet->bWaitResponse )
				{				  
					// 서버로 메시지를 보낼필요는 없다. 아이템을 벗었다가 다시착용한경우.
					if ( m_pstCommonItemSet->bIsDealItem )
					{
						SetDealFromCommon(bPos, m_nDealCellNum, m_pstCommonItemSet);
						ZeroMemory(m_pstCommonItemSet, sizeof(COMMONITEMSET));
					}
					else
					{
						if (m_pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bThrow >= _MULTIPLE_TYPE_ITEM && m_pstCommonItemSet->xItem.m_stItemInfo.wAmount_GB > 1)
						{
							g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_EXCHANGEMULTIPLEITEM, _YESNO, g_xMsg.GetMsg(1307), TRUE);
						}
						else
						{
							INT nCount = 0;
							if (m_pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bThrow >= _MULTIPLE_TYPE_ITEM)
								nCount = 1;
							SetDealOnItemFromCommon(m_pstCommonItemSet, m_nDealCellNum);
							g_xClientSocket.SendAddDealItem(m_stDealOnItem.xItem.m_stItemInfo.stStdItem.szName, m_stDealOnItem.xItem.m_stItemInfo.nMakeIndex, nCount);
							m_pstCommonItemSet->bWaitResponse	= TRUE;
						}
					}
				}
				// 공통(마우스)아이템셋은 있고, 서버로부터 응답신호를 기다리는 중이 아니면,
				// 공통아이템을 m_stDealOnItem 아이템을 세팅해두고, 현재 클릭된 Deal아이템을 공통아이템으로 세팅하고나서,
				// CM_DEALDELITEM메시지를 보낸다.
/*				else if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse )
				{
					SetDealOnItemFromCommon(pstCommonItemSet, nDealCellNum);
					SetCommonFromDeal(bPos, nDealCellNum, nDealItemNum, pstCommonItemSet);
					g_xClientSocket.SendAddDealItem(m_stDealOnItem.xItem.m_stItemInfo.stStdItem.szName, m_stDealOnItem.xItem.m_stItemInfo.nMakeIndex);
					pstCommonItemSet->bWaitResponse	= TRUE;
				}
*/
			}
			// 클릭한 Deal영역에 아이템이 없을경우.
			else
			{
				// 공통(마우스)아이템셋은 있고, 서버로부터 응답신호를 기다리는 중이 아니면, 공통아이템을 m_stDealOnItem에 아이템을 세팅해둔다.
				if ( m_pstCommonItemSet->bSetted && !m_pstCommonItemSet->bWaitResponse )
				{				  
					// 서버로 메시지를 보낼필요는 없다. 아이템을 벗었다가 다시착용한경우.
					if ( m_pstCommonItemSet->bIsDealItem )
					{
						SetDealFromCommon(bPos, m_nDealCellNum, m_pstCommonItemSet);
						ZeroMemory(m_pstCommonItemSet, sizeof(COMMONITEMSET));
					}
					else
					{
						if (m_pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bThrow >= _MULTIPLE_TYPE_ITEM && m_pstCommonItemSet->xItem.m_stItemInfo.wAmount_GB > 1)
						{
							if (!m_pstCommonItemSet->bIsBeltItem)
								g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_EXCHANGEMULTIPLEITEM, _YESNO, g_xMsg.GetMsg(1307), TRUE);
						}
						else
						{
							INT nCount = 0;
							if (m_pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bThrow >= _MULTIPLE_TYPE_ITEM)
								nCount = 1;
							SetDealOnItemFromCommon(m_pstCommonItemSet, m_nDealCellNum);
							g_xClientSocket.SendAddDealItem(m_stDealOnItem.xItem.m_stItemInfo.stStdItem.szName, m_stDealOnItem.xItem.m_stItemInfo.nMakeIndex, nCount);
							m_pstCommonItemSet->bWaitResponse	= TRUE;
						}
					}
				}
			}
		}
	}

	return FALSE;
}

BOOL CExchangeWnd::OnLButtonDown(POINT ptMouse)
{
	INT		nCnt;
	if ( !strcmp(g_xGameProc.m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(1050)) )
	{
		return FALSE;
	}

	for ( nCnt = 0; nCnt < 2; nCnt++ )
	{
		if ( m_xExchangeScrlBar[nCnt].OnLButtonDown(ptMouse) )
		{
			FLOAT	fScrlRate;
			fScrlRate	= m_xExchangeScrlBar[nCnt].GetScrlRate();
			m_nStartLineNum[nCnt] = (INT)((_DEAL_MAX_CELL_YCNT- _DEAL_CELL_YCNT)*fScrlRate);

			return TRUE;
		}
	}

	if ( m_xExchangeBtn.OnLButtonDown(ptMouse) )
		return TRUE;

	if ( mExchange_btnClose.OnLButtonDown(ptMouse) )
		return TRUE;
	

	return FALSE;
}




LRESULT CExchangeWnd::OnMsgBoxReturn(WPARAM wParam, LPARAM lParam)
{
	BYTE	bMsgReturn;
	WORD	wPacket;
//	CHAR pszEditMsg[MAX_PATH];

	bMsgReturn = LOBYTE(HIWORD(wParam));
	wPacket	   = LOWORD(wParam);

	if ( wPacket == CM_DEALCHGGOLD && bMsgReturn == _BTN_YES )
	{
		INT nAtoI = atoi((CHAR*) lParam);

		if ( nAtoI <= g_xGameProc.m_xMyHero.m_nGlod )
		{
			g_xClientSocket.SendChangeDealGold(nAtoI);
		}
	}

	return 0L;
}


VOID CExchangeWnd::OnScrollDown()
{
	if ( PtInRect(&m_rcDealRgn[0], g_xGameProc.m_ptMousePos) )
	{
		if ( m_nStartLineNum[0] > 0 )												
		{
			m_nStartLineNum[0]--;
		}
	}
	else
	{
		if ( m_nStartLineNum[1] > 0 )												
		{
			m_nStartLineNum[1]--;
		}
	}
}

VOID CExchangeWnd::OnScrollUp()
{
	if ( PtInRect(&m_rcDealRgn[0], g_xGameProc.m_ptMousePos) )
	{
		if ( m_nStartLineNum[0] < _DEAL_MAX_CELL_YCNT - _DEAL_CELL_YCNT )		
		{
			m_nStartLineNum[0]++;
		}
	}
	else
	{
		if ( m_nStartLineNum[1] < _DEAL_MAX_CELL_YCNT - _DEAL_CELL_YCNT )		
		{
			m_nStartLineNum[1]++;
		}
	}
}

VOID
CExchangeWnd::FindNDeleteHotKeyItem()
{
	for ( INT nPos = 0; nPos < 2; nPos++)
	{
		for ( INT nCnt = 0; nCnt < _MAX_DEAL_ITEM; nCnt++ )
		{
			if ( m_stDealItem[nPos][nCnt].bSetted )
			{
				if ( m_stDealItem[nPos][nCnt].xItem.m_stItemInfo.stStdItem.bThrow > _MULTIPLE_TYPE_ITEM)
				{
					if (g_xGameProc.m_xInterface.m_xInventoryWnd.GetSameItemCount(m_stDealItem[nPos][nCnt].xItem) != 0)
						continue;

					INT	nNum = 0;
					nNum = g_xGameProc.m_xInterface.m_xBeltWnd.FindSameItemInBelt(m_stDealItem[nPos][nCnt].xItem);

					if (nNum != -1)
						g_xGameProc.m_xInterface.m_xBeltWnd.DeleteBeltItem(nNum);
					
				}
			}		
		}
	}
}
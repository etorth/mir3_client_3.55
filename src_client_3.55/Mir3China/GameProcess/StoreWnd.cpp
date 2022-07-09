/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"


CStoreWnd::CStoreWnd()
{
	Init();
}


CStoreWnd::~CStoreWnd()
{
	Destroy();
}


VOID CStoreWnd::Init()
{
	CGameWnd::Init();

	for ( INT nCnt = 0; nCnt < _MAX_STORE_BTN; nCnt++ )
	{
		m_xStoreBtn[nCnt].Init();
	}

	m_bType = _TYPE_STORE;

	m_nNpcID = -1;

	m_xStoreScrlBar.Init();
	m_xStoreItemList.ClearAll();
	ZeroMemory(m_rcStoreItem, sizeof(RECT)*_NEW_MAX_STORE_ITEM);
	ZeroMemory(m_rcStoreItemDesc, sizeof(RECT)*_NEW_MAX_STORE_ITEM);
	m_nSelStoreItem = -1;
	m_nStoreFstLine = 0;

	m_xDetailItemList.ClearAll();
	ZeroMemory(m_rcDetailItem, sizeof(RECT)*_MAX_STORE_DETAIL_ITEM);
	m_nDetailPage = 0;
	m_nSelDetailItem = -1;
	m_nSelDetailIdx = -1;

	m_bAddType	  = _TYPE_ADDSTORE;
	m_pstStoreAdd = NULL;
	ZeroMemory(&m_rcStoreAddItem, sizeof(RECT));
	ZeroMemory(&m_rcStoreAddItemDesc, sizeof(RECT));

	// 추가 창고
	m_bStorageItemEx = FALSE;
}


VOID CStoreWnd::Destroy()
{
	CGameWnd::Destroy();
}


VOID CStoreWnd::CreateStoreWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove)
{
	INT nLoopX, nLoopY;

	CreateGameWnd(nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight);

	m_xStoreBtn[_BTN_ID_STORECLOSE].CreateGameBtn(pxWndImage, 1221, 1222, nStartX+262, nStartY+183, "", _BTN_TYPE_FOCUS, 1221, FALSE);
	m_xStoreBtn[_BTN_ID_STOREOK].CreateGameBtn(pxWndImage, 393, 394, nStartX+112, nStartY+186, "", _BTN_TYPE_FOCUS, -1, TRUE);
	m_xStoreBtn[_BTN_ID_DETAILCLOSE].CreateGameBtn(pxWndImage, 1221, 1222, nStartX+459, nStartY+159, "", _BTN_TYPE_FOCUS, 1221, FALSE);
	m_xStoreBtn[_BTN_ID_DETAILOK].CreateGameBtn(pxWndImage, 395, 396, nStartX+368, nStartY+163, "", _BTN_TYPE_FOCUS, -1, TRUE);
	m_xStoreBtn[_BTN_ID_DETAILLEFT].CreateGameBtn(pxWndImage, 398, 399, nStartX+326, nStartY+163, "", _BTN_TYPE_FOCUS, -1, TRUE);
	m_xStoreBtn[_BTN_ID_DETAILRIGHT].CreateGameBtn(pxWndImage, 400, 401, nStartX+416, nStartY+163, "", _BTN_TYPE_FOCUS, -1, TRUE);
	m_xStoreBtn[_BTN_ID_STOREADDCLOSE].CreateGameBtn(pxWndImage, 1221, 1222, nStartX+200, nStartY+56, "", _BTN_TYPE_FOCUS, 1221, FALSE);
	m_xStoreBtn[_BTN_ID_STOREADDOK].CreateGameBtn(pxWndImage, 393, 394, nStartX+84, nStartY+60, "", _BTN_TYPE_FOCUS, -1, TRUE);

	m_xStoreScrlBar.CreateScrlBar(pxWndImage, 1225, 5, 12, 93, 12);

	for ( nLoopY = 0; nLoopY < _NEW_MAX_STORE_ITEM; nLoopY++ )
	{
		SetRect(&m_rcStoreItem[nLoopY], 21, 16+(nLoopY*42), 59, 54+(nLoopY*42));
		SetRect(&m_rcStoreItemDesc[nLoopY], 63, 16+(nLoopY*42), 254, 54+(nLoopY*42));
	}

	for ( nLoopY = 0; nLoopY < 3; nLoopY++ )
	{
		for ( nLoopX = 0; nLoopX < 4; nLoopX++ )
		{
			SetRect(&m_rcDetailItem[nLoopY*4+nLoopX], 315+(38*nLoopX), 42+(nLoopY*38), 350+(38*nLoopX), 77+(nLoopY*38));
		}
	}

	m_bOpa = 220;
	SetRect(&m_rcStoreAddItem, 301, 17, 339, 55);
	SetRect(&m_rcStoreAddItemDesc, 348, 17, 497, 55);
}












VOID CStoreWnd::ShowStore()
{
	INT  nLine, nListCnt;
	LPSTOREITEM pstStoreItem = NULL;
	CListNode < STOREITEM > *pNode;

	CHAR pszStr[MAX_PATH];

	// 이미지가 흔들리는 문제때문이다.
	RECT rcWnd;
	if ( m_bType == _TYPE_STOREDETAIL )
	{
		SetRect(&rcWnd, m_rcWnd.left, m_rcWnd.top, m_rcWnd.right, m_rcWnd.bottom);
	}
	else if ( m_bType == _TYPE_STOREONEITEM )
	{
		SetRect(&rcWnd, m_rcWnd.left, m_rcWnd.top, m_rcWnd.right, m_rcWnd.bottom);
	}
	else
	{
		rcWnd = m_rcWnd;
	}

	for ( pNode = m_xStoreItemList.GetHead(), nListCnt = 0, nLine = 0; pNode; pNode = pNode->GetNext(), nListCnt++ )
	{
		// 현재 화면상에 보여줄 부분까지 만들어준다.
		if ( nListCnt >= m_nStoreFstLine )
		{
			pstStoreItem = pNode->GetData();

			if ( pstStoreItem )
			{
				CWHWilImageData* pxItemImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_STORE];
				if ( pxItemImg->NewSetIndex(pstStoreItem->nLooks) )
				{
					RECT rcItem = {m_rcStoreItem[nLine].left+rcWnd.left, m_rcStoreItem[nLine].top+rcWnd.top, 
								   m_rcStoreItem[nLine].right+rcWnd.left, m_rcStoreItem[nLine].bottom+rcWnd.top};
					INT nX = rcItem.left+_INVENTORY_CELL_WIDTH/2-pxItemImg->m_lpstNewCurrWilImageInfo->shWidth/2;
					INT nY = rcItem.top+_INVENTORY_CELL_HEIGHT/2-pxItemImg->m_lpstNewCurrWilImageInfo->shHeight/2;

					if ( nListCnt == m_nSelStoreItem )
					{
						D3DMATERIAL7 mtrl;

						if ( !pstStoreItem->nSubMenu )
						{
							D3DUtil_InitMaterial(mtrl, (FLOAT)80/255.0f, (FLOAT)80/255.0f, (FLOAT)160/255.0f);
						}
						else
						{
							D3DUtil_InitMaterial(mtrl, (FLOAT)40/255.0f, (FLOAT)120/255.0f, (FLOAT)120/255.0f);
						}

						mtrl.diffuse.a = 1.0f/255.0f;
						D3DVECTOR	vecTrans((FLOAT)rcItem.left, (FLOAT)rcItem.top, 0);
						D3DVECTOR	vecScale((FLOAT)(rcItem.right-rcItem.left), (FLOAT)(rcItem.bottom-rcItem.top), 1);
 						g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

						RECT rcItemDesc;
						SetRect(&rcItemDesc, m_rcStoreItemDesc[nLine].left+rcWnd.left, m_rcStoreItemDesc[nLine].top+rcWnd.top, 
								m_rcStoreItemDesc[nLine].right+rcWnd.left, m_rcStoreItemDesc[nLine].bottom+rcWnd.top);
						vecTrans = D3DVECTOR((FLOAT)rcItemDesc.left, (FLOAT)rcItemDesc.top, 0);
						vecScale = D3DVECTOR((FLOAT)(rcItemDesc.right-rcItemDesc.left), (FLOAT)(rcItemDesc.bottom-rcItemDesc.top), 1);
 						g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
						g_xMainWnd.DrawWithGDI(&rcItemDesc, NULL, RGB(250, 200, 150), 1);

						g_xMainWnd.DrawWithImageForCompClipRgn(nX, nY, pxItemImg->m_lpstNewCurrWilImageInfo->shWidth, pxItemImg->m_lpstNewCurrWilImageInfo->shHeight,
															   (WORD*)pxItemImg->m_pbCurrImage, _CLIP_WIDTH, _CLIP_HEIGHT, 0XFFFF, 0XFFFF, TRUE);

						nX = rcItem.right+10;
						nY = rcItem.top+2;
						if ( !pstStoreItem->nNeedLevel || !pstStoreItem->nSubMenu )
						{
							 if ( pstStoreItem->nLooks != 304 )
							 {
								nY = rcItem.top+13;
							 }
						}

						g_xMainWnd.PutsHan(NULL, nX-1, nY-1, RGB(10, 10, 10), 0, pstStoreItem->pszName);
						g_xMainWnd.PutsHan(NULL, nX, nY, RGB(250, 250, 0), 0, pstStoreItem->pszName);
						SIZE sizeLen = g_xMainWnd.GetStrLength(NULL, NULL, pstStoreItem->pszName);
						sprintf(pszStr, g_xMsg.GetMsg(2300), pstStoreItem->nPrice);
						g_xMainWnd.PutsHan(NULL, nX+1+sizeLen.cx, nY-1, RGB(10, 10, 10), 0, pszStr);
						g_xMainWnd.PutsHan(NULL, nX+2+sizeLen.cx, nY, RGB(250, 180, 100), 0, pszStr);

						if ( pstStoreItem->nLooks == 304 )
						{
							PutJobBook(nX, nY, pstStoreItem->nNeedLevel);
						}
						else
						{
							if ( pstStoreItem->nNeedLevel && pstStoreItem->nSubMenu )
							{
								PutNeedLevel(nX, nY, pstStoreItem->nNeed, pstStoreItem->nNeedLevel);
							}
						}
						g_xMainWnd.DrawWithGDI(&rcItem, NULL, RGB(250, 200, 150), 1);
					}
					else
					{
						g_xMainWnd.DrawWithImageForCompClipRgn(nX, nY, pxItemImg->m_lpstNewCurrWilImageInfo->shWidth, pxItemImg->m_lpstNewCurrWilImageInfo->shHeight,
															   (WORD*)pxItemImg->m_pbCurrImage, _CLIP_WIDTH, _CLIP_HEIGHT, 0XFFFF, 0XFFFF, TRUE);

						nX = rcItem.right+10;
						nY = rcItem.top+2;
						if ( !pstStoreItem->nNeedLevel || !pstStoreItem->nSubMenu )
						{
							 if ( pstStoreItem->nLooks != 304 )
							 {
								nY = rcItem.top+13;
							 }
						}

						g_xMainWnd.PutsHan(NULL, nX, nY, RGB(250, 250, 0), 0, pstStoreItem->pszName);
						SIZE sizeLen = g_xMainWnd.GetStrLength(NULL, NULL, pstStoreItem->pszName);
						sprintf(pszStr, g_xMsg.GetMsg(2300), pstStoreItem->nPrice);
						g_xMainWnd.PutsHan(NULL, nX+2+sizeLen.cx, nY, RGB(250, 180, 100), 0, pszStr);

						if ( pstStoreItem->nLooks == 304 )
						{
							PutJobBook(nX, nY, pstStoreItem->nNeedLevel);
						}
						else
						{
							if ( pstStoreItem->nNeedLevel && pstStoreItem->nSubMenu )
							{
								PutNeedLevel(nX, nY, pstStoreItem->nNeed, pstStoreItem->nNeedLevel);
							}
						}

						if ( pstStoreItem->nSubMenu )
						{
							g_xMainWnd.DrawWithGDI(&rcItem, NULL, RGB(180, 180, 180), 1);
						}
					}
				}
			}

			nLine++;

			if ( nLine >= _NEW_MAX_STORE_ITEM )
			{
				break;
			}
		}
	}

	// 스크롤바.
	m_xStoreScrlBar.ShowScrlBar(rcWnd.left+267, rcWnd.top+28, m_nStoreFstLine, m_xStoreItemList.GetCount());
}


VOID CStoreWnd::ShowDetail()
{
	INT  nLine, nListCnt;
	CItem*	    pxItem = NULL;
	CListNode < CItem > *pNodeDetail;

	CHAR pszStr[MAX_PATH];

	for ( INT nLoopY = 0; nLoopY < 3; nLoopY++ )
	{
		for ( INT nLoopX = 0; nLoopX < 4; nLoopX++ )
		{
			SetRect(&m_rcDetailItem[nLoopY*4+nLoopX], 315+(38*nLoopX), 42+(nLoopY*38), 350+(38*nLoopX), 77+(nLoopY*38));			
		}
	}


	for ( pNodeDetail = m_xDetailItemList.GetHead(), nListCnt = 0, nLine = 0; pNodeDetail; pNodeDetail = pNodeDetail->GetNext(), nListCnt++ )
	{
		// 현재 화면상에 보여줄 부분까지 만들어준다.
		if ( nListCnt >= m_nDetailPage*_MAX_STORE_DETAIL_ITEM )
		{
			pxItem = pNodeDetail->GetData();

			if ( pxItem )
			{
				CWHWilImageData* pxItemImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_STORE];
				if ( pxItemImg->NewSetIndex(pxItem->m_stItemInfo.stStdItem.wLooks) )
				{
					RECT rcItem;
					if ( m_bType == _TYPE_STOREDETAIL )
					{
						rcItem.left = m_rcDetailItem[nLine].left+m_rcWnd.left;
						rcItem.top = m_rcDetailItem[nLine].top+m_rcWnd.top;
						rcItem.right = m_rcDetailItem[nLine].right+m_rcWnd.left;
						rcItem.bottom = m_rcDetailItem[nLine].bottom+m_rcWnd.top;
					}
					else
					{
						rcItem.left = m_rcDetailItem[nLine].left+m_rcWnd.left - 294;
						rcItem.top = m_rcDetailItem[nLine].top+m_rcWnd.top + 6;
						rcItem.right = m_rcDetailItem[nLine].right+m_rcWnd.left - 294;
						rcItem.bottom = m_rcDetailItem[nLine].bottom+m_rcWnd.top + 6;
					}

					if ( nListCnt == m_nSelDetailItem ) 
					{
						D3DMATERIAL7 mtrl;
						D3DUtil_InitMaterial(mtrl, (FLOAT)50/255.0f, (FLOAT)150/255.0f, (FLOAT)150/255.0f);
						mtrl.diffuse.a = 1.0f/255.0f;
						D3DVECTOR	vecTrans((FLOAT)rcItem.left, (FLOAT)rcItem.top, 0);
						D3DVECTOR	vecScale((FLOAT)(rcItem.right-rcItem.left), (FLOAT)(rcItem.bottom-rcItem.top), 1);
 						g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
						g_xMainWnd.DrawWithGDI(&rcItem, NULL, RGB(180, 180, 180), 1);
					}

					if ( m_bType == _TYPE_STOREDETAIL )
					{
						pxItem->DrawItem(m_rcDetailItem[nLine].left+m_rcWnd.left, m_rcDetailItem[nLine].top+m_rcWnd.top, _ITEM_TYPE_STORE);
					}
					else
					{
						pxItem->DrawItem(m_rcDetailItem[nLine].left+m_rcWnd.left - 294, m_rcDetailItem[nLine].top+m_rcWnd.top + 6, _ITEM_TYPE_STORE);
					}
					if ( m_bType != _TYPE_KEEP )
					{
						sprintf(pszStr, "%d", pxItem->m_stItemInfo.nDuraMax);
						SetRect(&rcItem, m_rcDetailItem[nLine].left+m_rcWnd.left-1, m_rcDetailItem[nLine].top+20+m_rcWnd.top, 
								m_rcDetailItem[nLine].right+m_rcWnd.left-1, m_rcDetailItem[nLine].bottom+m_rcWnd.top);
						g_xMainWnd.PutsHan(NULL, rcItem, RGB( 10,  10,  10), 0, pszStr, g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 8, 0));
						SetRect(&rcItem, m_rcDetailItem[nLine].left+m_rcWnd.left, m_rcDetailItem[nLine].top+20+m_rcWnd.top+1, 
								m_rcDetailItem[nLine].right+m_rcWnd.left, m_rcDetailItem[nLine].bottom+m_rcWnd.top+1);
						g_xMainWnd.PutsHan(NULL, rcItem, RGB(255, 255, 255), 0, pszStr, g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 8, 0));
					}
				}
			}

			nLine++;

			if ( nLine >= _MAX_STORE_DETAIL_ITEM )
			{
				break;
			}
		}
	}

	if ( m_bType == _TYPE_KEEP )
	{
		INT nMaxDetailPage;
		if ( m_xDetailItemList.GetCount()%_MAX_STORE_DETAIL_ITEM )
		{
			nMaxDetailPage = m_xDetailItemList.GetCount()/_MAX_STORE_DETAIL_ITEM + 1;
		}
		else
		{
			if ( m_xDetailItemList.GetCount() == 0 )
			{
				nMaxDetailPage = 1;
			}
			else
			{
				nMaxDetailPage = m_xDetailItemList.GetCount()/_MAX_STORE_DETAIL_ITEM;
			}
		}	
		RECT rcPageCurr;
		RECT rcPageMax;

		if ( m_bType == _TYPE_STOREDETAIL )
		{
			SetRect(&rcPageCurr, m_rcDetailItem[0].left+m_rcWnd.left+107, m_rcDetailItem[0].top+m_rcWnd.top-19, m_rcDetailItem[0].left+m_rcWnd.left+127, m_rcDetailItem[0].top+m_rcWnd.top-4);
			SetRect(&rcPageMax, m_rcDetailItem[0].left+m_rcWnd.left+133, m_rcDetailItem[0].top+m_rcWnd.top-19, m_rcDetailItem[0].left+m_rcWnd.left+153, m_rcDetailItem[0].top+m_rcWnd.top-4);
		}
		else
		{
			SetRect(&rcPageCurr, m_rcDetailItem[0].left+m_rcWnd.left-250, m_rcDetailItem[0].top+m_rcWnd.top-22, m_rcDetailItem[0].left+m_rcWnd.left-230, m_rcDetailItem[0].top+m_rcWnd.top-7);
			SetRect(&rcPageMax, m_rcDetailItem[0].left+m_rcWnd.left-220, m_rcDetailItem[0].top+m_rcWnd.top-22, m_rcDetailItem[0].left+m_rcWnd.left-180, m_rcDetailItem[0].top+m_rcWnd.top-7);
		}

		sprintf(pszStr, "%d", m_nDetailPage+1);
		g_xMainWnd.PutsHan(NULL, rcPageCurr, RGB(255, 200, 150), 0, pszStr);
		sprintf(pszStr, "/    %d", nMaxDetailPage);
		g_xMainWnd.PutsHan(NULL, rcPageMax, RGB(255, 200, 150), 0, pszStr);
	}
	else
	{
		RECT rcPage;
		SetRect(&rcPage, m_rcDetailItem[0].left+m_rcWnd.left+12, m_rcDetailItem[0].top+m_rcWnd.top-30, m_rcDetailItem[0].left+m_rcWnd.left+148, m_rcDetailItem[0].top+m_rcWnd.top-10);
		sprintf(pszStr, "%d", m_nSelDetailIdx);

		if ( m_nSelDetailIdx != -1 )
		{
			g_xMainWnd.PutsHan(NULL, rcPage, RGB(255, 200, 150), RGB(30, 30, 30), pszStr);
		}
		else
		{
			g_xMainWnd.PutsHan(NULL, rcPage, RGB(255, 200, 150), RGB(30, 30, 30), "...");
		}
	}

/*	
	for ( INT nLoopY = 0; nLoopY < 3; nLoopY++ )
	{
		for ( INT nLoopX = 0; nLoopX < 4; nLoopX++ )
		{
			nCnt = nLoopY*4+nLoopX;
			RECT rcItem;

			SetRect(&rcItem, m_rcDetailItem[nCnt].left+m_rcWnd.left, m_rcDetailItem[nCnt].top+m_rcWnd.top, 
					m_rcDetailItem[nCnt].right+m_rcWnd.left, m_rcDetailItem[nCnt].bottom+m_rcWnd.top);
			g_xMainWnd.DrawWithGDI(&rcItem, NULL, RGB(255, 255, 255), 2);
		}
	}
*/
}


VOID CStoreWnd::ShowStoreAdd()
{
	CWHWilImageData* pxItemImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_STORE];

	if ( m_pstStoreAdd )
	{
		if ( pxItemImg->NewSetIndex(m_pstStoreAdd->nLooks) )
		{		
			CHAR pszStr[MAX_PATH];

			RECT rcItem = {m_rcStoreAddItem.left+m_rcWnd.left, m_rcStoreAddItem.top+m_rcWnd.top, 
						   m_rcStoreAddItem.right+m_rcWnd.left, m_rcStoreAddItem.bottom+m_rcWnd.top};

			INT nX = rcItem.left+_INVENTORY_CELL_WIDTH/2-pxItemImg->m_lpstNewCurrWilImageInfo->shWidth/2;
			INT nY = rcItem.top+_INVENTORY_CELL_HEIGHT/2-pxItemImg->m_lpstNewCurrWilImageInfo->shHeight/2;

			D3DMATERIAL7 mtrl;
			D3DUtil_InitMaterial(mtrl, (FLOAT)80/255.0f, (FLOAT)80/255.0f, (FLOAT)160/255.0f);
			mtrl.diffuse.a = 1.0f/255.0f;
			D3DVECTOR	vecTrans((FLOAT)rcItem.left, (FLOAT)rcItem.top, 0);
			D3DVECTOR	vecScale((FLOAT)(rcItem.right-rcItem.left), (FLOAT)(rcItem.bottom-rcItem.top), 1);
 			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
			g_xMainWnd.DrawWithGDI(&rcItem, NULL, RGB(180, 180, 180), 1);

			RECT rcItemDesc;
			SetRect(&rcItemDesc, m_rcStoreAddItemDesc.left+m_rcWnd.left, m_rcStoreAddItemDesc.top+m_rcWnd.top, 
					m_rcStoreAddItemDesc.right+m_rcWnd.left, m_rcStoreAddItemDesc.bottom+m_rcWnd.top);
			vecTrans = D3DVECTOR((FLOAT)rcItemDesc.left, (FLOAT)rcItemDesc.top, 0);
			vecScale = D3DVECTOR((FLOAT)(rcItemDesc.right-rcItemDesc.left), (FLOAT)(rcItemDesc.bottom-rcItemDesc.top), 1);
 			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
			g_xMainWnd.DrawWithGDI(&rcItemDesc, NULL, RGB(250, 200, 150), 1);

			g_xMainWnd.DrawWithImageForCompClipRgn(nX, nY, pxItemImg->m_lpstNewCurrWilImageInfo->shWidth, pxItemImg->m_lpstNewCurrWilImageInfo->shHeight,
												   (WORD*)pxItemImg->m_pbCurrImage, _CLIP_WIDTH, _CLIP_HEIGHT, 0XFFFF, 0XFFFF, TRUE);

			nX = rcItem.right+16;
			nY = rcItem.top+2;
			if ( !m_pstStoreAdd->nNeedLevel )
			{
				nY = rcItem.top+13;
			}

			g_xMainWnd.PutsHan(NULL, nX-1, nY-1, RGB(10, 10, 10), 0, m_pstStoreAdd->pszName);
			g_xMainWnd.PutsHan(NULL, nX, nY, RGB(250, 250, 0), 0, m_pstStoreAdd->pszName);
			SIZE sizeLen = g_xMainWnd.GetStrLength(NULL, NULL, m_pstStoreAdd->pszName);
			sprintf(pszStr, g_xMsg.GetMsg(2300), m_pstStoreAdd->nPrice);
			g_xMainWnd.PutsHan(NULL, nX+1+sizeLen.cx, nY-1, RGB(10, 10, 10), 0, pszStr);
			g_xMainWnd.PutsHan(NULL, nX+2+sizeLen.cx, nY, RGB(250, 180, 100), 0, pszStr);

			if ( m_pstStoreAdd->nNeedLevel && m_pstStoreAdd->nSubMenu )
			{
				PutNeedLevel(nX, nY, m_pstStoreAdd->nNeed, m_pstStoreAdd->nNeedLevel);
			}
		}
	}
}

		

VOID CStoreWnd::ShowStoreWnd()
{
	INT nCnt;

	ShowGameWnd();

	if ( m_bType == _TYPE_STORE || m_bType == _TYPE_STOREONEITEM || m_bType == _TYPE_STOREDETAIL || m_bType == _TYPE_DRUG )
	{
		m_xStoreBtn[_BTN_ID_STORECLOSE].ChangeRect(m_rcWnd.left+256, m_rcWnd.top+185);
		m_xStoreBtn[_BTN_ID_STOREOK].ChangeRect(m_rcWnd.left+111, m_rcWnd.top+186);

		if ( m_bType == _TYPE_STOREDETAIL )
		{
			m_xStoreBtn[_BTN_ID_DETAILCLOSE].ChangeRect(m_rcWnd.left+452, m_rcWnd.top+168);
			m_xStoreBtn[_BTN_ID_DETAILOK].ChangeRect(m_rcWnd.left+355, m_rcWnd.top+167);
			m_xStoreBtn[_BTN_ID_DETAILLEFT].ChangeRect (m_rcWnd.left+311, m_rcWnd.top+167);
			m_xStoreBtn[_BTN_ID_DETAILRIGHT].ChangeRect(m_rcWnd.left+399, m_rcWnd.top+167);
		}
		else if ( m_bType == _TYPE_STOREONEITEM )
		{
			m_xStoreBtn[_BTN_ID_STOREADDCLOSE].ChangeRect(m_rcWnd.left+478, m_rcWnd.top+65);
			m_xStoreBtn[_BTN_ID_STOREADDOK].ChangeRect(m_rcWnd.left+364, m_rcWnd.top+63);
		}
	}
	else
	{
		m_xStoreBtn[_BTN_ID_DETAILCLOSE].ChangeRect(m_rcWnd.left+162, m_rcWnd.top+168);
		m_xStoreBtn[_BTN_ID_DETAILOK].ChangeRect(m_rcWnd.left+65, m_rcWnd.top+167);
		m_xStoreBtn[_BTN_ID_DETAILLEFT].ChangeRect (m_rcWnd.left+21, m_rcWnd.top+167);
		m_xStoreBtn[_BTN_ID_DETAILRIGHT].ChangeRect(m_rcWnd.left+109, m_rcWnd.top+167);
	}

	if ( m_bType == _TYPE_STORE || m_bType == _TYPE_STOREONEITEM || m_bType == _TYPE_STOREDETAIL || m_bType == _TYPE_DRUG )
	{
		ShowStore();

		m_xStoreBtn[_BTN_ID_STORECLOSE].ShowGameBtn();
		m_xStoreBtn[_BTN_ID_STOREOK].ShowGameBtn();
	}

	if ( m_bType == _TYPE_STOREDETAIL || m_bType == _TYPE_KEEP )
	{
		ShowDetail();

		m_xStoreBtn[_BTN_ID_DETAILCLOSE].ShowGameBtn();
		m_xStoreBtn[_BTN_ID_DETAILOK].ShowGameBtn();
		m_xStoreBtn[_BTN_ID_DETAILLEFT].ShowGameBtn();
		m_xStoreBtn[_BTN_ID_DETAILRIGHT].ShowGameBtn();

	}

	if ( m_bType == _TYPE_STOREONEITEM )
	{
		ShowStoreAdd();
		m_xStoreBtn[_BTN_ID_STORECLOSE].ShowGameBtn();
		m_xStoreBtn[_BTN_ID_STOREOK].ShowGameBtn();
		m_xStoreBtn[_BTN_ID_STOREADDCLOSE].ShowGameBtn();
		m_xStoreBtn[_BTN_ID_STOREADDOK].ShowGameBtn();
	}
}


VOID CStoreWnd::PutJobBook(INT nX, INT nY, INT nNeedLevel)
{
	if ( nNeedLevel >= 0 && nNeedLevel < 5 )
	{
		INT  nCnt;
		BOOL bUseAble = FALSE;
		// 필요능력치.

		if ( g_xGameProc.m_xMyHero.m_bJob == nNeedLevel )
		{
			bUseAble = TRUE;
		}

		CHAR pszNeed[MAX_PATH];
		sprintf(pszNeed, "%s", g_xMsg.GetMsg(nNeedLevel+5170));

		if ( bUseAble )
		{
			g_xMainWnd.PutsHan(NULL, nX, nY+20, RGB(200, 255, 200), 0, pszNeed);
		}
		else
		{
			g_xMainWnd.PutsHan(NULL, nX, nY+20, RGB(255, 30, 30), 0, pszNeed);
		}
	}
}


VOID CStoreWnd::PutNeedLevel(INT nX, INT nY, INT nNeed, INT nNeedLevel)
{
	if ( nNeed >= 0 && nNeed < 12 )
	{
		INT  nCnt;
		BOOL bUseAble = FALSE;
		// 필요능력치.

		switch ( nNeed )
		{
			case 0:
			{
				if ( g_xGameProc.m_xMyHero.m_stAbility.bLevel >= nNeedLevel )
				{
				   bUseAble = TRUE;
				}
				break;
			}
			case 1:
			{
				if ( HIWORD(g_xGameProc.m_xMyHero.m_stAbility.dwDC) >= nNeedLevel )
				{
				   bUseAble = TRUE;
				}
				break;
			}
			case 2:
			{
				bUseAble = TRUE;
				for ( nCnt = 0; nCnt < 4; nCnt++)
				{
					if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[nCnt]) < nNeedLevel )
					{
						bUseAble = FALSE;
						break;
					}
				}
				break;
			}
			case 3:
			{
				bUseAble = TRUE;
				for ( nCnt = 4; nCnt < 7; nCnt++)
				{
					if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[nCnt]) < nNeedLevel )
					{
						bUseAble = FALSE;
						break;
					}
				}
				break;
			}
			case 4:
			{
				bUseAble = TRUE;
				for ( nCnt = 0; nCnt < 7; nCnt++)
				{
					if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[nCnt]) < nNeedLevel )
					{
						bUseAble = FALSE;
						break;
					}
				}
				break;
			}
			case 5:
			{
				if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[0]) >= nNeedLevel )
				{
				   bUseAble = TRUE;
				}
				break;
			}
			case 6:
			{
				if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[1]) >= nNeedLevel )
				{
				   bUseAble = TRUE;
				}
				break;
			}
			case 7:
			{
				if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[2]) >= nNeedLevel )
				{
				   bUseAble = TRUE;
				}
				break;
			}
			case 8:
			{
				if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[3]) >= nNeedLevel )
				{
				   bUseAble = TRUE;
				}
				break;
			}
			case 9:
			{
				if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[4]) >= nNeedLevel )
				{
				   bUseAble = TRUE;
				}
				break;
			}
			case 10:
			{
				if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[5]) >= nNeedLevel )
				{
				   bUseAble = TRUE;
				}
				break;
			}
			case 11:
			{
				if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[6]) >= nNeedLevel )
				{
				   bUseAble = TRUE;
				}
				break;
			}
		}

		CHAR pszNeed[MAX_PATH];

		if ( nNeedLevel > 100 )
			nNeedLevel -= 100;

		sprintf(pszNeed, "%s %d", g_xMsg.GetMsg(nNeed+5140), nNeedLevel);

		if ( bUseAble )
		{
			g_xMainWnd.PutsHan(NULL, nX, nY+20, RGB(240, 240, 255), 0, pszNeed);
		}
		else
		{
			g_xMainWnd.PutsHan(NULL, nX, nY+20, RGB(255, 30, 30), 0, pszNeed);
		}
	}
}


VOID CStoreWnd::ShowDetailItemState()
{
	if ( m_bType == _TYPE_STOREDETAIL || m_bType == _TYPE_KEEP )
	{
		INT nListNum = GetSelDetailItemNum(g_xGameProc.m_ptMousePos);

		if ( nListNum != -1 )
		{
			CItem* pxItem = GetSelDetailItemInfo(nListNum);

			if ( pxItem )
			{
				BOOL bUseStore = FALSE;
				if ( m_bType == _TYPE_STOREDETAIL )
				{
					bUseStore = TRUE;
				}

				if ( pxItem->m_stItemInfo.stStdItem.bStdMode == 10 || pxItem->m_stItemInfo.stStdItem.bStdMode == 11 )
				{
					pxItem->ShowItemStatus(g_xGameProc.m_ptMousePos.x + 10, g_xGameProc.m_ptMousePos.y + 10, bUseStore, TRUE);
				}
				else
				{
					pxItem->ShowItemStatus(g_xGameProc.m_ptMousePos.x + 10, g_xGameProc.m_ptMousePos.y + 10, bUseStore);
				}
			}
		}
	}
}










LPSTOREITEM CStoreWnd::GetSelStoreItemInfo(INT nListNum)
{
	INT  nListCnt;

	LPSTOREITEM pstStoreItem = NULL;
	CListNode < STOREITEM > *pNode;

	for ( pNode = m_xStoreItemList.GetHead(), nListCnt = 0; pNode; pNode = pNode->GetNext(), nListCnt++ )
	{
		if ( nListCnt == nListNum )
		{
			pstStoreItem = pNode->GetData();

			if ( pstStoreItem )
			{
				break;
			}
		}
	}

	return pstStoreItem;
}


INT CStoreWnd::GetSelStoreItemNum(POINT ptMouse)
{
	INT nCnt, nMaxItem;

	nMaxItem = _NEW_MAX_STORE_ITEM;

	for ( nCnt = 0; nCnt < nMaxItem; nCnt++ )
	{
		RECT rcItem;

		SetRect(&rcItem, m_rcStoreItem[nCnt].left+m_rcWnd.left, m_rcStoreItem[nCnt].top+m_rcWnd.top, 
				m_rcStoreItem[nCnt].right+m_rcWnd.left, m_rcStoreItem[nCnt].bottom+m_rcWnd.top);

		RECT rcItemDesc;
		SetRect(&rcItemDesc, m_rcStoreItemDesc[nCnt].left+m_rcWnd.left, m_rcStoreItemDesc[nCnt].top+m_rcWnd.top, 
				m_rcStoreItemDesc[nCnt].right+m_rcWnd.left, m_rcStoreItemDesc[nCnt].bottom+m_rcWnd.top);

		if ( PtInRect(&rcItem, ptMouse) || PtInRect(&rcItemDesc, ptMouse) )
		{
			return nCnt + m_nStoreFstLine;			
		}
	}

	return -1;
}


CItem* CStoreWnd::GetSelDetailItemInfo(INT nListNum)
{
	INT  nListCnt;

	CItem* pxItem = NULL;
	CListNode < CItem > *pNode;

	for ( pNode = m_xDetailItemList.GetHead(), nListCnt = 0; pNode; pNode = pNode->GetNext(), nListCnt++ )
	{
		if ( nListCnt == nListNum )
		{
			pxItem = pNode->GetData();

			if ( pxItem )
			{
				break;
			}
		}
	}

	return pxItem;
}


INT CStoreWnd::GetSelDetailItemNum(POINT ptMouse)
{
	for ( INT nLoopY = 0; nLoopY < 3; nLoopY++ )
	{
		for ( INT nLoopX = 0; nLoopX < 4; nLoopX++ )
		{
			RECT rcItem;
			INT nArray = nLoopY*4+nLoopX;

			if ( m_bType == _TYPE_KEEP )
			{
				SetRect(&rcItem, m_rcDetailItem[nArray].left+m_rcWnd.left - 294, m_rcDetailItem[nArray].top+m_rcWnd.top + 6, 
						m_rcDetailItem[nArray].right+m_rcWnd.left - 294, m_rcDetailItem[nArray].bottom+m_rcWnd.top + 6);
			}
			else
			{
				SetRect(&rcItem, m_rcDetailItem[nArray].left+m_rcWnd.left, m_rcDetailItem[nArray].top+m_rcWnd.top, 
						m_rcDetailItem[nArray].right+m_rcWnd.left, m_rcDetailItem[nArray].bottom+m_rcWnd.top);
			}

			if ( PtInRect(&rcItem, ptMouse) && m_nDetailPage != -1 )
			{
				return nArray + _MAX_STORE_DETAIL_ITEM*m_nDetailPage;
			}
		}
	}

	return -1;
}


VOID CStoreWnd::DeleteDetailItem()
{
	if ( m_nSelDetailItem != -1 )
	{
		INT  nListCnt;

		CItem* pxItem = NULL;
		CListNode < CItem > *pNode;

		for ( pNode = m_xDetailItemList.GetHead(), nListCnt = 0; pNode; pNode = pNode->GetNext(), nListCnt++ )
		{
			if ( nListCnt == m_nSelDetailItem )
			{
				pxItem = pNode->GetData();

				if ( pxItem )
				{
					m_xDetailItemList.RemoveNode(pNode);
					SAFE_DELETE(pxItem);
					break;
				}
			}
		}
	}
}


BOOL CStoreWnd::CanMove(POINT ptMouse)
{
	if ( m_bType == _TYPE_STOREDETAIL )
	{
		RECT rcDetail = {m_rcWnd.left+300, m_rcWnd.top+208, m_rcWnd.right, m_rcWnd.bottom};
		if ( PtInRect(&rcDetail, ptMouse) )
		{
			return FALSE;
		}		
	}
	else if ( m_bType == _TYPE_STOREONEITEM )
	{
		RECT rcOne = {m_rcWnd.left+300, m_rcWnd.top+100, m_rcWnd.right, m_rcWnd.bottom};
		if ( PtInRect(&rcOne, ptMouse) )
		{
			return FALSE;
		}		
	}

	return TRUE;
}


BOOL CStoreWnd::OnLButtonUp(POINT ptMouse)
{
	if ( m_bType == _TYPE_STORE || m_bType == _TYPE_STOREONEITEM || m_bType == _TYPE_STOREDETAIL || m_bType == _TYPE_DRUG )
	{
		if ( m_xStoreBtn[_BTN_ID_STORECLOSE].OnLButtonUp(ptMouse) )		
		{
			return TRUE;
		}
	}

	if ( m_bType == _TYPE_STOREDETAIL || m_bType == _TYPE_STOREONEITEM || m_bType == _TYPE_KEEP )
	{
		if ( m_xStoreBtn[_BTN_ID_DETAILCLOSE].OnLButtonUp(ptMouse) )		
		{
			if ( m_bType == _TYPE_KEEP )
			{
				return TRUE;
			}
			else
			{
				// _TYPE_STORE로 상태변경.
				m_xDetailItemList.ClearAll();
				m_nDetailPage = 0;
				m_bType = _TYPE_STORE;
				ResetWndImg(_WNDIMGIDX_STORE, 0, 220, 292, 224);
				return FALSE;
			}
		}
		else if ( m_xStoreBtn[_BTN_ID_STOREADDCLOSE].OnLButtonUp(ptMouse) )
		{
			// _TYPE_STORE로 상태변경.
			ResetWndImg(_WNDIMGIDX_STORE, 0, 220, 292, 224);
			m_pstStoreAdd = NULL;
			m_bType = _TYPE_STORE;
			m_bAddType	  = _TYPE_ADDDRUG;
			return FALSE;
		}
	}

	if ( m_bType == _TYPE_STORE || m_bType == _TYPE_STOREONEITEM || m_bType == _TYPE_STOREDETAIL || m_bType == _TYPE_DRUG )
	{
		if ( m_xStoreScrlBar.OnLButtonUp(ptMouse) )
		{
			return FALSE;
		}
	}

	if ( m_bType == _TYPE_STORE || m_bType == _TYPE_STOREONEITEM || m_bType == _TYPE_STOREDETAIL || m_bType == _TYPE_DRUG )
	{
		if ( m_xStoreBtn[_BTN_ID_STOREOK].OnLButtonUp(ptMouse) )
		{
			if ( m_nSelStoreItem != -1 )
			{
				LPSTOREITEM pstStoreItem = GetSelStoreItemInfo(m_nSelStoreItem);

				if ( pstStoreItem )
				{
					if ( pstStoreItem->nSubMenu == 2 )
					{
						if ( m_bType == _TYPE_STORE )
						{
							m_bAddType = _TYPE_ADDSTORE;
						}
						else if ( m_bType == _TYPE_DRUG )
						{
							m_bAddType = _TYPE_ADDDRUG;
						}
						m_bType = _TYPE_STOREONEITEM;
						ResetWndImg(_WNDIMGIDX_STOREADD, 0, 220, 516, 224);
						m_pstStoreAdd = GetSelStoreItemInfo(m_nSelStoreItem);
					}
					else
					{
						g_xClientSocket.SendGetDetailItem(m_nNpcID, 0, pstStoreItem->pszName);
					}
					return FALSE;
				}
			}
		}
	}

	if ( m_bType == _TYPE_STOREONEITEM )
	{
		if ( m_xStoreBtn[_BTN_ID_STOREADDOK].OnLButtonUp(ptMouse) )
		{
			if ( m_pstStoreAdd )
			{
				if ( m_bAddType == _TYPE_ADDDRUG )
				{
					g_xClientSocket.SendMakeDrug(m_nNpcID, m_pstStoreAdd->pszName);
				}
				else
				{
					g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_BUYMULTIPLEITEM, _YESNO, g_xMsg.GetMsg(2302), TRUE);
				}
				return FALSE;
			}
		}	
	}

	if ( m_bType == _TYPE_STOREDETAIL || m_bType == _TYPE_KEEP )
	{
		if ( m_xStoreBtn[_BTN_ID_DETAILOK].OnLButtonUp(ptMouse) )
		{
			if ( m_nSelDetailItem != -1 )
			{
				CItem* pxItem = GetSelDetailItemInfo(m_nSelDetailItem);

				if ( pxItem )
				{
					if ( m_bType == _TYPE_STOREDETAIL )
					{
						g_xClientSocket.SendBuyItem(m_nNpcID, pxItem->m_stItemInfo.stStdItem.szName, pxItem->m_stItemInfo.nMakeIndex);
					}
					else
					{
						if (pxItem->m_stItemInfo.stStdItem.bThrow >= _MULTIPLE_TYPE_ITEM)
						{
							DWORD	dwCount = pxItem->m_stItemInfo.wAmount_GB;

							if (dwCount > 1)
								g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_TAKEBACKMULTIPLEITEM, _YESNO, g_xMsg.GetMsg(2301), TRUE);
							else
							{
								// 추가 창고
								if( m_bStorageItemEx )
									g_xClientSocket.SendTakeBackItemEx(m_nNpcID, pxItem->m_stItemInfo.stStdItem.szName, pxItem->m_stItemInfo.nMakeIndex, 1);
								else							
									g_xClientSocket.SendTakeBackItem(m_nNpcID, pxItem->m_stItemInfo.stStdItem.szName, pxItem->m_stItemInfo.nMakeIndex, 1);
							}
						}
						else
						{
							// 추가 창고
							if( m_bStorageItemEx )
									g_xClientSocket.SendTakeBackItemEx(m_nNpcID, pxItem->m_stItemInfo.stStdItem.szName, pxItem->m_stItemInfo.nMakeIndex, 1);
							else
								g_xClientSocket.SendTakeBackItem(m_nNpcID, pxItem->m_stItemInfo.stStdItem.szName, pxItem->m_stItemInfo.nMakeIndex);
						}
					}
					return FALSE;
				}
			}
		}
	}

	if ( m_bType == _TYPE_STOREDETAIL )
	{
		if ( m_xStoreBtn[_BTN_ID_DETAILLEFT].OnLButtonUp(ptMouse) )
		{
			if ( m_nSelDetailIdx > 0 )
			{
				m_nSelDetailIdx--;

				if ( m_nSelStoreItem != -1 )
				{
					LPSTOREITEM pstStoreItem = GetSelStoreItemInfo(m_nSelStoreItem);

					if ( pstStoreItem )
					{
						g_xClientSocket.SendGetDetailItem(m_nNpcID, m_nSelDetailIdx*10, pstStoreItem->pszName);
						m_nSelDetailIdx = -1;
					}
				}
			}

			return FALSE;
		}
	}

	if ( m_bType == _TYPE_KEEP )
	{
		if ( m_xStoreBtn[_BTN_ID_DETAILLEFT].OnLButtonUp(ptMouse) )
		{
			if ( m_nDetailPage > 0 )
			{
				m_nDetailPage--;
			}

			return FALSE;
		}
	}

	if ( m_bType == _TYPE_STOREDETAIL )
	{
		if ( m_xStoreBtn[_BTN_ID_DETAILRIGHT].OnLButtonUp(ptMouse) )
		{
			m_nSelDetailIdx++;

			if ( m_nSelStoreItem != -1 )
			{
				LPSTOREITEM pstStoreItem = GetSelStoreItemInfo(m_nSelStoreItem);

				if ( pstStoreItem )
				{
					g_xClientSocket.SendGetDetailItem(m_nNpcID, m_nSelDetailIdx*10, pstStoreItem->pszName);
					m_nSelDetailIdx = -1;
				}
			}

			return FALSE;
		}
	}

	if ( m_bType == _TYPE_KEEP )
	{
		INT nMaxDetailPage;
		if ( m_xDetailItemList.GetCount()%_MAX_STORE_DETAIL_ITEM )
		{
			nMaxDetailPage = m_xDetailItemList.GetCount()/_MAX_STORE_DETAIL_ITEM + 1;
		}
		else
		{
			nMaxDetailPage = m_xDetailItemList.GetCount()/_MAX_STORE_DETAIL_ITEM;
		}	

		if ( m_xStoreBtn[_BTN_ID_DETAILRIGHT].OnLButtonUp(ptMouse) )
		{
			if ( m_nDetailPage != -1 && m_nDetailPage < nMaxDetailPage-1 )
			{
				m_nDetailPage++;
			}

			return FALSE;
		}
	}

	INT nSel = GetSelStoreItemNum(ptMouse);
	if ( nSel != -1 )
	{
		m_nSelStoreItem = GetSelStoreItemNum(ptMouse);
	}
	nSel = GetSelDetailItemNum(ptMouse);
	if ( nSel != -1 )
	{
		m_nSelDetailItem = GetSelDetailItemNum(ptMouse);
	}

	return FALSE;
}


BOOL CStoreWnd::OnLButtonDown(POINT ptMouse)
{
	INT nCnt;

	if ( m_bType == _TYPE_STORE || m_bType == _TYPE_STOREONEITEM || m_bType == _TYPE_STOREDETAIL || m_bType == _TYPE_DRUG )
	{
		if ( m_xStoreScrlBar.OnLButtonDown(ptMouse) )
		{
			FLOAT	fScrlRate;
			fScrlRate	= m_xStoreScrlBar.GetScrlRate();
			m_nStoreFstLine = (INT)((m_xStoreItemList.GetCount()-1)*fScrlRate);

			return TRUE;
		}
	}


	if ( m_bType == _TYPE_STORE || m_bType == _TYPE_STOREONEITEM || m_bType == _TYPE_STOREDETAIL || m_bType == _TYPE_DRUG )
	{
		if ( m_xStoreBtn[_BTN_ID_STORECLOSE].OnLButtonDown(ptMouse) )
		{
			return TRUE;
		}
		if ( m_xStoreBtn[_BTN_ID_STOREOK].OnLButtonDown(ptMouse) )
		{
			return TRUE;
		}

		if ( m_bType == _TYPE_STOREDETAIL )
		{
			if ( m_xStoreBtn[_BTN_ID_DETAILCLOSE].OnLButtonDown(ptMouse) )
			{
				return TRUE;
			}
			if ( m_xStoreBtn[_BTN_ID_DETAILOK].OnLButtonDown(ptMouse) )
			{
				return TRUE;
			}
			if ( m_xStoreBtn[_BTN_ID_DETAILLEFT].OnLButtonDown(ptMouse) )
			{
				return TRUE;
			}
			if ( m_xStoreBtn[_BTN_ID_DETAILRIGHT].OnLButtonDown(ptMouse) )
			{
				return TRUE;
			}
		}
		else if ( m_bType == _TYPE_STOREONEITEM )
		{
			if ( m_xStoreBtn[_BTN_ID_STOREADDCLOSE].OnLButtonDown(ptMouse) )
			{
				return TRUE;
			}
			if ( m_xStoreBtn[_BTN_ID_STOREADDOK].OnLButtonDown(ptMouse) )
			{
				return TRUE;
			}
		}
	}
	else
	{
		if ( m_xStoreBtn[_BTN_ID_DETAILCLOSE].OnLButtonDown(ptMouse) )
		{
			return TRUE;
		}
		if ( m_xStoreBtn[_BTN_ID_DETAILOK].OnLButtonDown(ptMouse) )
		{
			return TRUE;
		}
		if ( m_xStoreBtn[_BTN_ID_DETAILLEFT].OnLButtonDown(ptMouse) )
		{
			return TRUE;
		}
		if ( m_xStoreBtn[_BTN_ID_DETAILRIGHT].OnLButtonDown(ptMouse) )
		{
			return TRUE;
		}
	}

	INT nSel = GetSelStoreItemNum(ptMouse);
	if ( nSel != -1 )
	{
		m_nSelStoreItem = GetSelStoreItemNum(ptMouse);
	}
	nSel = GetSelDetailItemNum(ptMouse);
	if ( nSel != -1 )
	{
		m_nSelDetailItem = GetSelDetailItemNum(ptMouse);
	}


	return FALSE;
}


BOOL CStoreWnd::OnMouseMove(POINT ptMouse)
{
	INT nCnt;

	if ( m_bType == _TYPE_STORE || m_bType == _TYPE_STOREONEITEM || m_bType == _TYPE_STOREDETAIL || m_bType == _TYPE_DRUG )
	{
		if ( m_xStoreScrlBar.OnMouseMove(ptMouse) )
		{
			FLOAT	fScrlRate;
			fScrlRate = m_xStoreScrlBar.GetScrlRate();
			m_nStoreFstLine = (INT)((m_xStoreItemList.GetCount()-1)*fScrlRate);
			
			return TRUE;
		}
	}

	for ( nCnt = 0; nCnt < _MAX_STORE_BTN; nCnt++ )
	{
		m_xStoreBtn[nCnt].OnMouseMove(ptMouse);
	}

	return FALSE;
}


VOID CStoreWnd::OnScrollDown()
{
	if ( m_bType == _TYPE_STORE || m_bType == _TYPE_STOREONEITEM || m_bType == _TYPE_STOREDETAIL || m_bType == _TYPE_DRUG )
	{
		if ( m_nStoreFstLine > 0 )	
		{
			m_nStoreFstLine--;
		}
	}
}


BOOL CStoreWnd::OnLButtonDoubleClick(POINT ptMouse)
{
	if ( m_bType == _TYPE_STORE || m_bType == _TYPE_STOREONEITEM || m_bType == _TYPE_STOREDETAIL || m_bType == _TYPE_DRUG )
	{
		INT nSel = GetSelStoreItemNum(ptMouse);

		if ( nSel != -1 )
		{
			m_nSelStoreItem = GetSelStoreItemNum(ptMouse);

			LPSTOREITEM pstStoreItem = GetSelStoreItemInfo(m_nSelStoreItem);

			if ( pstStoreItem )
			{
				if ( pstStoreItem->nSubMenu == 2)
				{
					if ( m_bType == _TYPE_STORE )
					{
						m_bAddType = _TYPE_ADDSTORE;
					}
					else if ( m_bType == _TYPE_DRUG )
					{
						m_bAddType = _TYPE_ADDDRUG;
					}

					m_bType = _TYPE_STOREONEITEM;
					ResetWndImg(_WNDIMGIDX_STOREADD, 0, 220, 516, 224);
					m_pstStoreAdd = GetSelStoreItemInfo(m_nSelStoreItem);
				}
				else
				{
					g_xClientSocket.SendGetDetailItem(m_nNpcID, 0, pstStoreItem->pszName);
				}
				return FALSE;
			}
		}
	}

	if ( m_bType == _TYPE_STOREONEITEM )
	{
		RECT rcItem = {m_rcStoreAddItem.left+m_rcWnd.left, m_rcStoreAddItem.top+m_rcWnd.top, 
					   m_rcStoreAddItem.right+m_rcWnd.left, m_rcStoreAddItem.bottom+m_rcWnd.top};

		RECT rcItemDesc;
		SetRect(&rcItemDesc,m_rcStoreAddItemDesc.left+m_rcWnd.left,m_rcStoreAddItemDesc.top+m_rcWnd.top, 
				m_rcStoreAddItemDesc.right+m_rcWnd.left,m_rcStoreAddItemDesc.bottom+m_rcWnd.top);

		if ( PtInRect(&rcItem, ptMouse) || PtInRect(&rcItemDesc, ptMouse) )
		{
			if ( m_pstStoreAdd )
			{
				if ( m_bAddType == _TYPE_ADDDRUG )
				{
					g_xClientSocket.SendMakeDrug(m_nNpcID, m_pstStoreAdd->pszName);
				}
				else
				{
					g_xClientSocket.SendBuyGood(m_nNpcID, m_pstStoreAdd->pszName, m_pstStoreAdd->nStock);
				}
				return FALSE;
			}
		}	
	}

	if ( m_bType == _TYPE_STOREDETAIL || m_bType == _TYPE_KEEP )
	{
		INT nSel = GetSelDetailItemNum(ptMouse);

		if ( nSel != -1 )
		{
			m_nSelDetailItem = GetSelDetailItemNum(ptMouse);

			CItem* pxItem = GetSelDetailItemInfo(m_nSelDetailItem);

			if ( pxItem )
			{
				if ( m_bType == _TYPE_STOREDETAIL )
				{
					g_xClientSocket.SendBuyItem(m_nNpcID, pxItem->m_stItemInfo.stStdItem.szName, pxItem->m_stItemInfo.nMakeIndex);
				}
				else
				{
					if (pxItem->m_stItemInfo.stStdItem.bThrow >= _MULTIPLE_TYPE_ITEM)
					{
						DWORD	dwCount = pxItem->m_stItemInfo.wAmount_GB;

						if (dwCount > 1)
							g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_TAKEBACKMULTIPLEITEM, _YESNO, g_xMsg.GetMsg(2301), TRUE);
						else
							g_xClientSocket.SendTakeBackItem(m_nNpcID, pxItem->m_stItemInfo.stStdItem.szName, pxItem->m_stItemInfo.nMakeIndex, 1);
					}
					else
					{
						g_xClientSocket.SendTakeBackItem(m_nNpcID, pxItem->m_stItemInfo.stStdItem.szName, pxItem->m_stItemInfo.nMakeIndex);
					}
				}
				return FALSE;
			}
		}
	}

	return FALSE;
}


VOID CStoreWnd::OnScrollUp()
{
	if ( m_bType == _TYPE_STORE || m_bType == _TYPE_STOREONEITEM || m_bType == _TYPE_STOREDETAIL || m_bType == _TYPE_DRUG )
	{
		if ( m_nStoreFstLine < (m_xStoreItemList.GetCount()-1) )
		{
			m_nStoreFstLine++;
		}
	}
}


VOID CStoreWnd::SetStatusBtnInit()
{
	INT nCnt;

	for ( nCnt = 0; nCnt < _MAX_STORE_BTN; nCnt++ )
	{
		m_xStoreBtn[nCnt].SetBtnState(_BTN_STATE_NORMAL);
	}
}




//------------------------------------------------------------------------------------------------------------------------------
// 상점.
//------------------------------------------------------------------------------------------------------------------------------
BOOL CStoreWnd::SetStoreItemList(CHAR* pszMsg, INT nCount)
{
	CHAR* pszName		= NULL;
	CHAR* pszSubMenu	= NULL;
	CHAR* pszPrice		= NULL;
	CHAR* pszStock		= NULL;
	CHAR* pszLooks		= NULL;
	CHAR* pszNeed		= NULL;
	CHAR* pszNeedLevel	= NULL;

	LPSTOREITEM pstStoreItem = NULL;

//------------------------------------------------------------------------------------------------------------
	m_xStoreItemList.ClearAll();
	m_nStoreFstLine = 0;
	if ( nCount == 0 )
	{
		m_nSelStoreItem = -1;
	}
	else
	{
		m_nSelStoreItem = 0;
	}

	m_xDetailItemList.ClearAll();
	m_nDetailPage = 0;

	ResetWndImg(_WNDIMGIDX_STORE, 0, 220, 292, 224);
	m_bType = _TYPE_STORE;
//------------------------------------------------------------------------------------------------------------

	if ( strlen(pszMsg)==0 )
	{
		return FALSE;
	}

	for ( INT i = 0 ; i < nCount ; i ++ )
	{
		pszName		= pszMsg;

		pszSubMenu  = strchr(pszName, '/');
		if ( pszSubMenu == NULL )
		{
			return FALSE;
		}
		*pszSubMenu	= '\0';	
		pszSubMenu++;

		pszPrice	= strchr(pszSubMenu, '/');
		if ( pszPrice == NULL )
		{
			return FALSE;
		}
		*pszPrice	= '\0';
		pszPrice++;

		pszStock	= strchr(pszPrice, '/');
		if ( pszStock == NULL )
		{
			return FALSE;
		}
		*pszStock	= '\0';	
		pszStock++;

		pszLooks	= strchr(pszStock, '/');
		if ( pszLooks == NULL )
		{
			return FALSE;
		}
		*pszLooks	= '\0';	
		pszLooks++;

		pszNeed		= strchr(pszLooks, '/');
		if ( pszNeed == NULL )
		{
			return FALSE;
		}
		*pszNeed	= '\0';	
		pszNeed++;

		pszNeedLevel  = strchr(pszNeed, '/');
		if ( pszNeedLevel == NULL )
		{
			return FALSE;
		}
		*pszNeedLevel = '\0';	
		pszNeedLevel++;

		pszMsg		= strchr(pszNeedLevel, '/');
		if ( pszMsg == NULL )
		{
			return FALSE;
		}
		*pszMsg		= '\0';	
		pszMsg++;

		pstStoreItem = new STOREITEM;

		strcpy(pstStoreItem->pszName, pszName);
		pstStoreItem->nSubMenu = atoi(pszSubMenu);
		pstStoreItem->nPrice = atoi(pszPrice);
		pstStoreItem->nStock = atoi(pszStock);
		pstStoreItem->nGrade = 0;
		pstStoreItem->nLooks = atoi(pszLooks);
		pstStoreItem->nNeed  = atoi(pszNeed);
		pstStoreItem->nNeedLevel = atoi(pszNeedLevel);

		m_xStoreItemList.Insert(pstStoreItem);
	}

	return	TRUE;
}


//------------------------------------------------------------------------------------------------------------------------------
// 상점 세부품목.
//------------------------------------------------------------------------------------------------------------------------------
BOOL CStoreWnd::SetDetailItemLst(CHAR* pszMsg, INT nCount, INT nCurrentIdx)
{
	INT		nPos		 = 0;
	INT		nCurrLen	 = 0;
	CHAR*	pszLastMsg	 = NULL;
	CHAR*	pszDecodeMsg = NULL;

	RECT	rcName		 = {0, 0, 0, 0};
	SIZE	sizeLen		 = {0, 0};

	CHAR	pszOrg[8196];
	ZeroMemory(pszOrg, 8196);

	CLIENTITEMRCD*	pstItemRcd = NULL;
	CItem*			pxItem	   = NULL;

//------------------------------------------------------------------------------------------------------------
	m_xDetailItemList.ClearAll();

	m_nDetailPage = 0;
	m_nSelDetailIdx = nCurrentIdx/10;

	if ( nCount == 0 )
	{
		m_nSelDetailItem = -1;
	}
	else
	{
		m_nSelDetailItem = 0;
	}

	m_bType = _TYPE_STOREDETAIL;

	INT nLoopX, nLoopY;

	ResetWndImg(_WNDIMGIDX_ITEMDETAIL, 0, 220, 488, 224);

	for ( nLoopY = 0; nLoopY < 3; nLoopY++ )
	{
		for ( nLoopX = 0; nLoopX < 4; nLoopX++ )
		{
			SetRect(&m_rcDetailItem[nLoopY*4+nLoopX], 310+(38*nLoopX), 47+(nLoopY*38), 347+(38*nLoopX), 84+(nLoopY*38));
		}
	}
//------------------------------------------------------------------------------------------------------------

	if ( strlen(pszMsg) == 0 )
	{
		return FALSE;
	}

	nPos = fnDecode6BitBuf((CHAR*)pszMsg , pszOrg, sizeof(pszOrg));
	pszOrg[nPos] = '\0';

	pszDecodeMsg = pszOrg;

	for ( INT nLoop = 0; nLoop < nCount; nLoop++ )
	{
		pszLastMsg    = pszDecodeMsg;
		pszDecodeMsg  = strchr(pszLastMsg, '/');

		if ( pszDecodeMsg )
		{
			*pszDecodeMsg = '\0';
			pszDecodeMsg++;

			pstItemRcd = new CLIENTITEMRCD;
			pxItem	   = new CItem;

			fnDecode6BitBuf(pszLastMsg, (CHAR*)pstItemRcd, sizeof(CLIENTITEMRCD));

			// [ 0914 / plusplus ] 서버상점리스트 초기화문제때문.
			ZeroMemory(pstItemRcd->Desc, 14);
		
			pxItem->SetItem(*pstItemRcd, 0);

			m_xDetailItemList.Insert(pxItem);
		}
	}

	return TRUE;
}


//------------------------------------------------------------------------------------------------------------------------------
// 창고.
//------------------------------------------------------------------------------------------------------------------------------
BOOL CStoreWnd::SetStorageList(CHAR* pszMsg, INT nCount)
{
	CHAR*			pszLastMsg = NULL;
	POINT			ptTemp	   = {120, 55};

	RECT			rcName	= {0, 0, 0, 0};
	SIZE			sizeLen	= {0, 0};

	CLIENTITEMRCD*	pstItemRcd = NULL;
	CItem*			pxItem	   = NULL;

//------------------------------------------------------------------------------------------------------------
	m_xDetailItemList.ClearAll();

	m_nDetailPage = 0;
	if ( nCount == 0 )
	{
		m_nSelDetailItem = -1;
	}
	else
	{
		m_nSelDetailItem = 0;
	}

	m_bType = _TYPE_KEEP;

	INT nLoopX, nLoopY;

	ResetWndImg(402, 0, 221, 200, 204);

	for ( nLoopY = 0; nLoopY < 3; nLoopY++ )
	{
		for ( nLoopX = 0; nLoopX < 4; nLoopX++ )
		{
			SetRect(&m_rcDetailItem[nLoopY*4+nLoopX], 314+(38*nLoopX), 32+(nLoopY*38), 351+(38*nLoopX), 69+(nLoopY*38));
		}
	}
//------------------------------------------------------------------------------------------------------------

	if ( strlen(pszMsg) == 0 )
	{
		return FALSE;
	}

	for ( INT nLoop = 0; nLoop < nCount; nLoop++ )
	{
		if ( pszMsg )
		{
			pszLastMsg = pszMsg;
			pszMsg	   = strchr(pszLastMsg, '/');

			if ( pszMsg )
			{
				*pszMsg = '\0';
				pszMsg++;

				pstItemRcd = new CLIENTITEMRCD;
				pxItem	   = new CItem;

				fnDecode6BitBuf(pszLastMsg, (char*)pstItemRcd, sizeof(CLIENTITEMRCD));
				
				pxItem->SetItem(*pstItemRcd, 0);	
				
				m_xDetailItemList.Insert(pxItem);
			}
		}
	}

	return TRUE;
}


BOOL CStoreWnd::AddStorageList(CHAR* pszMsg, INT nCount)
{
	CHAR*			pszLastMsg = NULL;
	POINT			ptTemp	   = {120, 55};

	RECT			rcName	= {0, 0, 0, 0};
	SIZE			sizeLen	= {0, 0};

	CLIENTITEMRCD*	pstItemRcd = NULL;
	CItem*			pxItem	   = NULL;

//------------------------------------------------------------------------------------------------------------
	m_nDetailPage = 0;
	if ( nCount == 0 )
	{
		m_nSelDetailItem = -1;
	}
	else
	{
		m_nSelDetailItem = 0;
	}

	m_bType = _TYPE_KEEP;

	INT nLoopX, nLoopY;

	ResetWndImg(402, 0, 221, 200, 204);

	for ( nLoopY = 0; nLoopY < 3; nLoopY++ )
	{
		for ( nLoopX = 0; nLoopX < 4; nLoopX++ )
		{
			SetRect(&m_rcDetailItem[nLoopY*4+nLoopX], 314+(38*nLoopX), 32+(nLoopY*38), 351+(38*nLoopX), 69+(nLoopY*38));
		}
	}
//------------------------------------------------------------------------------------------------------------

	if ( strlen(pszMsg) == 0 )
	{
		return FALSE;
	}

	for ( INT nLoop = 0; nLoop < nCount; nLoop++ )
	{
		if ( pszMsg )
		{
			pszLastMsg = pszMsg;
			pszMsg	   = strchr(pszLastMsg, '/');

			if ( pszMsg )
			{
				*pszMsg = '\0';
				pszMsg++;

				pstItemRcd = new CLIENTITEMRCD;
				pxItem	   = new CItem;

				fnDecode6BitBuf(pszLastMsg, (char*)pstItemRcd, sizeof(CLIENTITEMRCD));
				
				pxItem->SetItem(*pstItemRcd, 0);	
				
				m_xDetailItemList.Insert(pxItem);
			}
		}
	}

	return TRUE;
}


//------------------------------------------------------------------------------------------------------------------------------
// 약방.
//------------------------------------------------------------------------------------------------------------------------------
BOOL CStoreWnd::SetDrugList(CHAR* pszMsg)
{
	CHAR* pszName			= NULL;
	CHAR* pszSubMenu		= NULL;
	CHAR* pszPrice		= NULL;
	CHAR* pszStock		= NULL;
	CHAR* pszLooks		= NULL;
	CHAR* pszNeed		= NULL;
	CHAR* pszNeedLevel	= NULL;

	LPSTOREITEM pstStoreItem = NULL;

//------------------------------------------------------------------------------------------------------------
	m_xStoreItemList.ClearAll();
	m_nStoreFstLine = 0;
	m_nSelStoreItem = 0;

	m_xDetailItemList.ClearAll();
	m_nDetailPage = 0;

	ResetWndImg(_WNDIMGIDX_STORE, 0, 225, 292, 224);
	m_bType = _TYPE_DRUG;

	INT nLoopX, nLoopY;

	for ( nLoopY = 0; nLoopY < 3; nLoopY++ )
	{
		for ( nLoopX = 0; nLoopX < 4; nLoopX++ )
		{
			SetRect(&m_rcDetailItem[nLoopY*4+nLoopX], 323+(38*nLoopX), 43+(nLoopY*38), 360+(38*nLoopX), 80+(nLoopY*38));
		}
	}
//------------------------------------------------------------------------------------------------------------

	if ( strlen(pszMsg)==0 )
	{
		return FALSE;
	}

	while ( *pszMsg != '\0' )
	{
		pszName		= pszMsg;

		pszSubMenu  = strchr(pszName, '/');
		if ( pszSubMenu == NULL )
		{
			return FALSE;
		}
		*pszSubMenu	= '\0';	
		pszSubMenu++;

		pszPrice	= strchr(pszSubMenu, '/');
		if ( pszPrice == NULL )
		{
			return FALSE;
		}
		*pszPrice	= '\0';
		pszPrice++;

		pszStock	= strchr(pszPrice, '/');
		if ( pszStock == NULL )
		{
			return FALSE;
		}
		*pszStock	= '\0';	
		pszStock++;

		pszLooks	= strchr(pszStock, '/');
		if ( pszLooks == NULL )
		{
			return FALSE;
		}
		*pszLooks	= '\0';	
		pszLooks++;

		pszNeed		= strchr(pszLooks, '/');
		if ( pszNeed == NULL )
		{
			return FALSE;
		}
		*pszNeed	= '\0';	
		pszNeed++;

		pszNeedLevel  = strchr(pszNeed, '/');
		if ( pszNeedLevel == NULL )
		{
			return FALSE;
		}
		*pszNeedLevel = '\0';	
		pszNeedLevel++;

		pszMsg		= strchr(pszNeedLevel, '/');
		if ( pszMsg == NULL )
		{
			return FALSE;
		}
		*pszMsg		= '\0';	
		pszMsg++;

		pstStoreItem = new STOREITEM;

		strcpy(pstStoreItem->pszName, pszName);
		pstStoreItem->nSubMenu = atoi(pszSubMenu);
		pstStoreItem->nPrice	 = atoi(pszPrice);
		pstStoreItem->nStock	 = atoi(pszStock);
		pstStoreItem->nGrade	 = 0;
		pstStoreItem->nLooks	 = atoi(pszLooks);
		pstStoreItem->nNeed		 = atoi(pszNeed);
		pstStoreItem->nNeedLevel = atoi(pszNeedLevel);

		m_xStoreItemList.Insert(pstStoreItem);
	}

	return	TRUE;
}

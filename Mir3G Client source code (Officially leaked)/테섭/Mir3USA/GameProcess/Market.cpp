/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"


CMarketWnd::CMarketWnd()
{
	Init();
}

CMarketWnd::~CMarketWnd()
{
	Destroy();
}

VOID CMarketWnd::Init()
{
	CGameWnd::Init();

	mUserMarket_BtnClose.Init();
	mUserMarket_BtnDetailClose.Init();
	mUserMarket_BtnBuy.Init();
	mUserMarket_BtnRegistry.Init();
	mUserMarket_BtnFindItem.Init();
	mUserMarket_BtnFindWriter.Init();
	mUserMarket_BtnRefresh.Init();
	mUserMarket_BtnNext.Init();
	mUserMarket_BtnBefore.Init();

	mUserMarket_nMouseLocated = -1;
	mUserMarket_nSelected = -1;
	mUserMarket_nNpcId = -1;
	mUserMarket_dwLastSendTime = 0;
	mUserMarket_dwIconTimer = 0;

	mUserMarket_nIconFrame = 0;
	mUserMarket_nCurPage = 0;
	mUserMarket_nTotalPage = 0;

	mUserMarket_bReadytoGet = FALSE;

	mUserMarket_bSelectedFindItem = FALSE;
	mUserMarket_bSelectedFindName = FALSE;

	SetRect(&mUserMarket_rcShowItem, 0, 0, 0, 0);
	SetRect(&mUserMarket_rcFindItem, 0, 0, 0, 0);
	SetRect(&mUserMarket_rcFindName, 0, 0, 0, 0);

	m_xMarketItemList.ClearAll();
	mUserMarket_xDesclist.ClearAll();
}

VOID CMarketWnd::Destroy()
{
	CGameWnd::Destroy();
}

VOID CMarketWnd::CreateUserMarketWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend)
{
	CreateGameWnd(nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight, bBlend);

	mUserMarket_BtnClose.CreateGameBtn(pxWndImage, 1221, 1222, nStartX+669, nStartY+389, g_xMsg.GetMsg(1052), _BTN_TYPE_FOCUS, 1221, TRUE);
	mUserMarket_BtnDetailClose.CreateGameBtn(pxWndImage, 774, 774, nStartX+615, nStartY+377, g_xMsg.GetMsg(4400), _BTN_TYPE_FOCUS, -1, FALSE);
	mUserMarket_BtnBuy.CreateGameBtn(pxWndImage, 772, 772, nStartX+555, nStartY+377, g_xMsg.GetMsg(4401), _BTN_TYPE_FOCUS, -1, FALSE);
	mUserMarket_BtnRegistry.CreateGameBtn(pxWndImage, 770, 770, nStartX+505, nStartY+377, g_xMsg.GetMsg(4402), _BTN_TYPE_FOCUS, -1, FALSE);
	mUserMarket_BtnFindItem.CreateGameBtn(pxWndImage, 768, 768, nStartX+403, nStartY+367, g_xMsg.GetMsg(4403), _BTN_TYPE_FOCUS, -1, FALSE);
	mUserMarket_BtnFindWriter.CreateGameBtn(pxWndImage, 768, 768, nStartX+403, nStartY+397, g_xMsg.GetMsg(4404), _BTN_TYPE_FOCUS, -1, FALSE);
	mUserMarket_BtnRefresh.CreateGameBtn(pxWndImage, 766, 766, nStartX+128, nStartY+379, g_xMsg.GetMsg(4405), _BTN_TYPE_FOCUS, -1, FALSE);
	mUserMarket_BtnNext.CreateGameBtn(pxWndImage, 764, 764, nStartX+72, nStartY+379, g_xMsg.GetMsg(4406), _BTN_TYPE_FOCUS, -1, FALSE);
	mUserMarket_BtnBefore.CreateGameBtn(pxWndImage, 762, 762, nStartX+28, nStartY+379, g_xMsg.GetMsg(4407), _BTN_TYPE_FOCUS, -1, FALSE);


	RECT rcServer = {m_rcWnd.left + 14, m_rcWnd.top + 86, m_rcWnd.left + 76, m_rcWnd.top + 101};
	RECT rcItemName = {m_rcWnd.left + 80, m_rcWnd.top + 86, m_rcWnd.left + 214, m_rcWnd.top + 101};
	RECT rcPrice = {m_rcWnd.left + 220, m_rcWnd.top + 86, m_rcWnd.left + 284, m_rcWnd.top + 101};
	RECT rcSeller = {m_rcWnd.left + 290, m_rcWnd.top + 86, m_rcWnd.left + 424, m_rcWnd.top + 101};

	for ( INT nI = 0; nI < _MAX_MARKETCELL; nI++ )
	{
		SetRect(&mUserMarket_rcList[nI], m_rcWnd.left + 14, m_rcWnd.top + 86 + 19 * nI, m_rcWnd.left + 424, m_rcWnd.top + 101 + 19 * nI);
	}

	SetRect(&mUserMarket_rcFindItem, m_rcWnd.left + 229, m_rcWnd.top + 363, m_rcWnd.left + 363, m_rcWnd.top + 380);
	SetRect(&mUserMarket_rcFindName, m_rcWnd.left + 229, m_rcWnd.top + 393, m_rcWnd.left + 363, m_rcWnd.top + 410);
}	
		
VOID CMarketWnd::ShowUserMarketWnd()
{
	ShowGameWnd();

	SetRect(&mUserMarket_rcFindItem, m_rcWnd.left + 242, m_rcWnd.top + 369, m_rcWnd.left + 382, m_rcWnd.top + 386);
	SetRect(&mUserMarket_rcFindName, m_rcWnd.left + 242, m_rcWnd.top + 399, m_rcWnd.left + 382, m_rcWnd.top + 416);

	for ( INT nI = 0; nI < _MAX_MARKETCELL; nI++ )
	{
		SetRect(&mUserMarket_rcList[nI], m_rcWnd.left + 14, m_rcWnd.top + 94 + 19 * nI, m_rcWnd.left + 469, m_rcWnd.top + 112 + 19 * nI);
	}

	RECT rcTitle = {m_rcWnd.left + 40 , m_rcWnd.top + 24, m_rcWnd.left + 228, m_rcWnd.top + 39};
	g_xMainWnd.PutsHan(NULL, rcTitle, RGB(250, 220, 248), 0, g_xMsg.GetMsg(4408));

	mUserMarket_BtnClose.ShowGameBtn();
	mUserMarket_BtnDetailClose.ShowGameBtn();
	mUserMarket_BtnBuy.ShowGameBtn();
	mUserMarket_BtnRegistry.ShowGameBtn();
	mUserMarket_BtnFindItem.ShowGameBtn();
	mUserMarket_BtnFindWriter.ShowGameBtn();
	mUserMarket_BtnRefresh.ShowGameBtn();
	mUserMarket_BtnNext.ShowGameBtn();
	mUserMarket_BtnBefore.ShowGameBtn();

	RECT rcTemp = {m_rcWnd.left + 16 , m_rcWnd.top + 68, m_rcWnd.left + 118, m_rcWnd.top + 83};
	g_xMainWnd.PutsHan(NULL, rcTemp, RGB( 250,  250,  250), 0, g_xMsg.GetMsg(4409));

	RECT rcTemp2 = {m_rcWnd.left + 121, m_rcWnd.top + 68, m_rcWnd.left + 257, m_rcWnd.top + 83};
	g_xMainWnd.PutsHan(NULL, rcTemp2, RGB( 250,  250,  250), 0, g_xMsg.GetMsg(4410));

	RECT rcTemp3 = {m_rcWnd.left + 261, m_rcWnd.top + 68, m_rcWnd.left + 328, m_rcWnd.top + 83};
	g_xMainWnd.PutsHan(NULL, rcTemp3, RGB( 250,  250,  250), 0, g_xMsg.GetMsg(4411));

	RECT rcTemp4 = {m_rcWnd.left + 331, m_rcWnd.top + 68, m_rcWnd.left + 468, m_rcWnd.top + 83};
	g_xMainWnd.PutsHan(NULL, rcTemp4, RGB( 250,  250,  250), 0, g_xMsg.GetMsg(4412));

	// 마우스 있는 곳 뒷판
	if ( mUserMarket_nMouseLocated != -1 )
	{
		D3DMATERIAL7 mtrl;
		D3DVECTOR	 vecTrans((FLOAT)mUserMarket_rcList[mUserMarket_nMouseLocated].left, (FLOAT)mUserMarket_rcList[mUserMarket_nMouseLocated].top, 0);
		D3DVECTOR	 vecScale((FLOAT)mUserMarket_rcList[mUserMarket_nMouseLocated].right-mUserMarket_rcList[mUserMarket_nMouseLocated].left, 
			mUserMarket_rcList[mUserMarket_nMouseLocated].bottom-mUserMarket_rcList[mUserMarket_nMouseLocated].top, 1);

		D3DUtil_InitMaterial(mtrl, (FLOAT)50/255.0f, (FLOAT)50/255.0f, (FLOAT)50/255.0f);
		mtrl.diffuse.a = 180.0f/255.0f;
		g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
	}

	if ( mUserMarket_nSelected != -1 )
	{
		D3DMATERIAL7 mtrl;
		D3DVECTOR	 vecTrans((FLOAT)mUserMarket_rcList[mUserMarket_nSelected].left, (FLOAT)mUserMarket_rcList[mUserMarket_nSelected].top, 0);
		D3DVECTOR	 vecScale((FLOAT)mUserMarket_rcList[mUserMarket_nSelected].right-mUserMarket_rcList[mUserMarket_nSelected].left, 
			mUserMarket_rcList[mUserMarket_nSelected].bottom-mUserMarket_rcList[mUserMarket_nSelected].top, 1);

		D3DUtil_InitMaterial(mtrl, (FLOAT)35/255.0f, (FLOAT)114/255.0f, (FLOAT)156/255.0f);
		mtrl.diffuse.a = 180.0f/255.0f;
		g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
	}

	if ( mUserMarket_bReadytoGet )
	{
		DWORD dwCur = timeGetTime();

		if ( dwCur - mUserMarket_dwIconTimer > 100 )
		{
			mUserMarket_nIconFrame++;
			mUserMarket_dwIconTimer = dwCur;

			if ( mUserMarket_nIconFrame > 9 )
				mUserMarket_nIconFrame = 0;
		}
	}
	else if ( mUserMarket_nIconFrame != 0 )
	{
		DWORD dwCur = timeGetTime();

		if ( dwCur - mUserMarket_dwIconTimer > 150 )
		{
			mUserMarket_nIconFrame++;
			mUserMarket_dwIconTimer = dwCur;

			if ( mUserMarket_nIconFrame > 9 )
				mUserMarket_nIconFrame = 0;
		}
	}

	if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(790 + mUserMarket_nIconFrame))
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+366, m_rcWnd.top+12, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
	}

	LPCLIENTSELLITEM pstMarketItem = NULL;
	CListNode < CLIENTSELLITEM > *pNode;
	INT  nLine, nListCnt;
	RECT rcServer = {m_rcWnd.left + 16, m_rcWnd.top + 96, m_rcWnd.left + 118, m_rcWnd.top + 111};
	RECT rcItemName = {m_rcWnd.left + 121, m_rcWnd.top + 96, m_rcWnd.left + 257, m_rcWnd.top + 111};
	RECT rcPrice = {m_rcWnd.left + 261, m_rcWnd.top + 96, m_rcWnd.left + 328, m_rcWnd.top + 111};
	RECT rcSeller = {m_rcWnd.left + 331, m_rcWnd.top + 96, m_rcWnd.left + 468, m_rcWnd.top + 111};
	CHAR szTemp[25];

	if ( mUserMarket_nCurPage != 0 || mUserMarket_nTotalPage != 0 )
	{
		RECT rcPage = {m_rcWnd.left + 280, m_rcWnd.top + 25, m_rcWnd.left + 350, m_rcWnd.top + 40};
		sprintf( szTemp, "%d / %d", mUserMarket_nCurPage, mUserMarket_nTotalPage);
		g_xMainWnd.PutsHan(NULL, rcPage, RGB( 250,  250,  0), 0, szTemp);
	}

	for ( pNode = m_xMarketItemList.GetHead(), nListCnt = 0, nLine = 0; pNode; pNode = pNode->GetNext(), nListCnt++ )
	{
		pstMarketItem = pNode->GetData();

		g_xMainWnd.PutsHan(NULL, rcServer, RGB( 250,  250,  250), 0, pstMarketItem->szServer);
		
		BOOL bIsOpItem = FALSE;
		BOOL bIsMultiple = FALSE;
		DWORD	dwCount = 0;
		CHAR szTemp[MAX_PATH];

		for ( INT nI=0; nI<14; nI++ )
		{
			if ( pstMarketItem->stItem.Desc[nI] > 0 )
				bIsOpItem = TRUE;
		}

		if ( pstMarketItem->stItem.stStdItem.bThrow >= _MULTIPLE_TYPE_ITEM )
		{
			dwCount = pstMarketItem->stItem.wAmount_GB;
			bIsMultiple = TRUE;
		}

		if ( bIsMultiple )
			sprintf(szTemp, "%s(%d)", pstMarketItem->stItem.stStdItem.szName, dwCount);
		else
			sprintf(szTemp, "%s", pstMarketItem->stItem.stStdItem.szName);

		if ( bIsOpItem )
			g_xMainWnd.PutsHan(NULL, rcItemName, RGB( 255,  250,   0), 0, szTemp);
		else
			g_xMainWnd.PutsHan(NULL, rcItemName, RGB( 250,  250,  250), 0, szTemp);
		
		GetNumWithComma(pstMarketItem->nSellPrice, szTemp);

		if ( pstMarketItem->nSellPrice >= 10000000 )
		{
			g_xMainWnd.PutsHan(NULL, rcPrice, RGB( 250,  0,  0), 0, szTemp);
		}
		else if ( pstMarketItem->nSellPrice >= 1000000 )
		{
			g_xMainWnd.PutsHan(NULL, rcPrice, RGB( 0,  250,  250), 0, szTemp);
		}
		else
		{
			g_xMainWnd.PutsHan(NULL, rcPrice, RGB( 250,  250,  250), 0, szTemp);
		}

		g_xMainWnd.PutsHan(NULL, rcSeller, RGB( 250,  250,  250), 0, pstMarketItem->szSellWho);

		if ( nListCnt == mUserMarket_nSelected )
		{
			// Title
			RECT rcServerDetail = {m_rcWnd.left + 488, m_rcWnd.top + 19, m_rcWnd.left + 618, m_rcWnd.top + 34};
			g_xMainWnd.PutsHan(NULL, rcServerDetail, RGB( 250,  250,  250), 0, pstMarketItem->szSellWho);

			RECT rcSellerDetail = {m_rcWnd.left + 632, m_rcWnd.top + 19, m_rcWnd.left + 706, m_rcWnd.top + 34};
			g_xMainWnd.PutsHan(NULL, rcSellerDetail, RGB( 250,  250,  250), 0, pstMarketItem->szSellDate);

			// 설명
			if ( !mUserMarket_xDesclist.IsEmpty() )
			{
				INT		nCnt, nShowLine;
				LPCHAT	pstChat;
				RECT	rcDesc = {m_rcWnd.left + 483, m_rcWnd.top + 48, m_rcWnd.left + 701, m_rcWnd.top + 60};

				CListNode < CHAT >		*pNode;

				pNode = mUserMarket_xDesclist.GetHead();

				nShowLine = mUserMarket_xDesclist.GetCount();

				for ( nCnt = 0; nCnt < nShowLine; nCnt++ )
				{
					pstChat = *pNode;

					if ( pstChat )
					{
						DWORD dwFontColor = RGB(0, 0, 0);
						INT nX = 0;

						g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(),
										   rcDesc.left+nX+7, rcDesc.top+nCnt*12+5,
										   dwFontColor, pstChat->dwBackColor, pstChat->pszChat);
						g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(),
										   rcDesc.left+nX+9, rcDesc.top+nCnt*12+5,
										   dwFontColor, pstChat->dwBackColor, pstChat->pszChat);
						g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(),
										   rcDesc.left+nX+8, rcDesc.top+nCnt*12+4,
										   dwFontColor, pstChat->dwBackColor, pstChat->pszChat);
						g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(),
										   rcDesc.left+nX+8, rcDesc.top+nCnt*12+6,
										   dwFontColor, pstChat->dwBackColor, pstChat->pszChat);
						g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(),
										   rcDesc.left+nX+8, rcDesc.top+nCnt*12+5,
										   pstChat->dwFontColor, pstChat->dwBackColor, pstChat->pszChat);
					}

					pNode = pNode->GetNext();
				}
			}

			CWHWilImageData* pxItemImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_INVENTORY];

			if ( pxItemImg->NewSetIndex(pstMarketItem->stItem.stStdItem.wLooks) )
			{
				INT nCX = m_rcWnd.left + 600;
				INT nCY = m_rcWnd.top + 252;

				INT nSX = nCX - pxItemImg->m_lpstNewCurrWilImageInfo->shWidth/2;
				INT nSY = nCY - pxItemImg->m_lpstNewCurrWilImageInfo->shHeight/2;

				RECT rcImg;
				if ( pxItemImg->m_lpstNewCurrWilImageInfo->shHeight > 150 )
				{
					SetRect(&rcImg, 0, 0, pxItemImg->m_lpstNewCurrWilImageInfo->shWidth, 145);
					nSY = 200;
				}
				else
					SetRect(&rcImg, 0, 0, pxItemImg->m_lpstNewCurrWilImageInfo->shWidth, pxItemImg->m_lpstNewCurrWilImageInfo->shHeight);

				// 아이템 뒷판 그리기
				RECT rcItemCell = {nSX - 15, nSY - 7, nSX+rcImg.right + 15, nSY+rcImg.bottom + 7};

				SetRect(&mUserMarket_rcShowItem, rcItemCell.left, rcItemCell.top, rcItemCell.right, rcItemCell.bottom );

				g_xMainWnd.DrawWithGDI(&rcItemCell, NULL, RGB(200, 200, 200), 1);

				D3DMATERIAL7 mtrl;
				D3DVECTOR	 vecTrans((FLOAT)rcItemCell.left, (FLOAT)rcItemCell.top, 0);
				D3DVECTOR	 vecScale((FLOAT)rcItemCell.right-rcItemCell.left, rcItemCell.bottom-rcItemCell.top, 1);

				D3DUtil_InitMaterial(mtrl, (FLOAT)30/255.0f, (FLOAT)30/255.0f, (FLOAT)30/255.0f);
				mtrl.diffuse.a = 180.0f/255.0f;
				g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

				
				WORD wClr = 0XFFFF;
				
				if ( pstMarketItem->stItem.stStdItem.bStdMode == 10 || pstMarketItem->stItem.stStdItem.bStdMode == 11 )
				{
					wClr = g_xMainWnd.ConvertColor24To16(RGB(pstMarketItem->stItem.bLevel_R, 
															 LOBYTE(pstMarketItem->stItem.wAmount_GB), 
															 HIBYTE(pstMarketItem->stItem.wAmount_GB))); 
				}

				g_xMainWnd.DrawWithImageForComp(nSX, nSY, &rcImg, (WORD*)pxItemImg->m_pbCurrImage, wClr);

				if ( pstMarketItem->stItem.stStdItem.bThrow >= _MULTIPLE_TYPE_ITEM )
				{
					RECT rc;
					CHAR pszTmp[MAX_PATH];

					DWORD	dwCount = pstMarketItem->stItem.wAmount_GB;

					INT		nCnt = 0;
					nCnt = log10(dwCount);

					sprintf(pszTmp, "%d", dwCount);
					g_xMainWnd.PutsHan(NULL, nSX + 23, nSY + 22, RGB(255, 255, 0), RGB(0,0,0), pszTmp);
				}
			}
		}

		if ( mUserMarket_nMouseLocated == mUserMarket_nSelected && mUserMarket_nSelected != -1 )
			mUserMarket_xShowItem.ShowItemStatus(g_xGameProc.m_ptMousePos.x + 20, g_xGameProc.m_ptMousePos.y + 22, FALSE, FALSE, TRUE);
		
		if ( PtInRect(&mUserMarket_rcShowItem, g_xGameProc.m_ptMousePos) && mUserMarket_nSelected != -1 )
		{
			mUserMarket_xShowItem.ShowItemStatus(mUserMarket_rcShowItem.left + 35, mUserMarket_rcShowItem.top + 22, FALSE, FALSE, TRUE);
		}

		rcServer.top += 19;
		rcServer.bottom += 19;
		rcItemName.top += 19;
		rcItemName.bottom += 19;
		rcPrice.top += 19;
		rcPrice.bottom += 19;
		rcSeller.top += 19;
		rcSeller.bottom += 19;
	}
}

BOOL CMarketWnd::OnLButtonUp(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse)
{
	if ( mUserMarket_BtnClose.OnLButtonUp(ptMouse) )
	{
		CloseMarketWnd();
		return FALSE;
	}

	if ( mUserMarket_BtnDetailClose.OnLButtonUp(ptMouse) )
	{
		DWORD dwCurr = timeGetTime();
		if ( dwCurr - mUserMarket_dwLastSendTime > 1000 )
		{
			LPCLIENTSELLITEM pstMarketItem = NULL;
			CListNode < CLIENTSELLITEM > *pNode;
			INT nListCnt;

			for ( pNode = m_xMarketItemList.GetHead(), nListCnt = 0; pNode; pNode = pNode->GetNext(), nListCnt++ )
			{
				if ( nListCnt == mUserMarket_nSelected )
				{
					g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_WANTTOCANCEL, _YESNO, g_xMsg.GetMsg(4414));
				}
			}
		}
		
		return FALSE;
	}

	if ( mUserMarket_BtnBuy.OnLButtonUp(ptMouse) )
	{
		LPCLIENTSELLITEM pstMarketItem = NULL;
		CListNode < CLIENTSELLITEM > *pNode;
		INT nListCnt;

		DWORD dwCurr = timeGetTime();
		if ( dwCurr - mUserMarket_dwLastSendTime > 1000 )
		{
			LPCLIENTSELLITEM pstMarketItem = NULL;
			CListNode < CLIENTSELLITEM > *pNode;
			INT nListCnt;

			for ( pNode = m_xMarketItemList.GetHead(), nListCnt = 0; pNode; pNode = pNode->GetNext(), nListCnt++ )
			{
				if ( nListCnt == mUserMarket_nSelected )
				{
					pstMarketItem = pNode->GetData();

					if ( pstMarketItem->nSellPrice > g_xGameProc.m_xMyHero.m_nGlod )
					{
						g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_NOTENOUGH, _OK, g_xMsg.GetMsg(4413));
					}
					else
					{
						g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_WANTTOBUY, _YESNO, g_xMsg.GetMsg(4415));
					}
				}
			}
		}
		
		return FALSE;
	}

	if ( mUserMarket_BtnRegistry.OnLButtonUp(ptMouse) )
	{
		if(!g_xGameProc.m_xInterface.m_xMarketUpWnd.GetGameWndActive())
		{
			g_xGameProc.m_xInterface.WindowActivate(_WND_ID_USERMARKETUP);
			g_xGameProc.m_xInterface.m_xMarketUpWnd.mUserMarketUp_nNpcId = mUserMarket_nNpcId;
		}
		return FALSE;
	}

	if ( mUserMarket_BtnFindItem.OnLButtonUp(ptMouse) )
	{
		mUserMarket_bReadytoGet = TRUE;
		SendFindMsg();
	
		return FALSE;
	}

	if ( mUserMarket_BtnFindWriter.OnLButtonUp(ptMouse) )
	{
		mUserMarket_bReadytoGet = TRUE;
		SendFindMsg();

		return FALSE;
	}

	if ( mUserMarket_BtnRefresh.OnLButtonUp(ptMouse) )
	{
		DWORD dwCurr = timeGetTime();
		if ( dwCurr - mUserMarket_dwLastSendTime > 1000 )
		{
			mUserMarket_bReadytoGet = TRUE;
			g_xClientSocket.SendRefreshMarket(mUserMarket_nNpcId);
			mUserMarket_dwLastSendTime = dwCurr;
		}

		return FALSE;
	}

	if ( mUserMarket_BtnNext.OnLButtonUp(ptMouse) )
	{
		DWORD dwCurr = timeGetTime();
		if ( dwCurr - mUserMarket_dwLastSendTime > 1000 )
		{
			mUserMarket_bReadytoGet = TRUE;
			g_xClientSocket.SendNextPageMarket(mUserMarket_nNpcId);
			mUserMarket_dwLastSendTime = dwCurr;
		}
		return FALSE;
	}

	if ( mUserMarket_BtnBefore.OnLButtonUp(ptMouse) )
	{
		DWORD dwCurr = timeGetTime();
		if ( dwCurr - mUserMarket_dwLastSendTime > 1000 )
		{
			mUserMarket_bReadytoGet = TRUE;
			g_xClientSocket.SendPrevPageMarket(mUserMarket_nNpcId);
			mUserMarket_dwLastSendTime = dwCurr;
		}
		return FALSE;
	}

	return FALSE;
}

BOOL CMarketWnd::OnLButtonDown(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse)
{
	if ( mUserMarket_BtnClose.OnLButtonDown(ptMouse) )	return FALSE;
	if ( mUserMarket_BtnDetailClose.OnLButtonDown(ptMouse) )	return FALSE;
	if ( mUserMarket_BtnBuy.OnLButtonDown(ptMouse) )	return FALSE;
	if ( mUserMarket_BtnRegistry.OnLButtonDown(ptMouse) )	return FALSE;
	if ( mUserMarket_BtnFindItem.OnLButtonDown(ptMouse) )	return FALSE;
	if ( mUserMarket_BtnFindWriter.OnLButtonDown(ptMouse) )	return FALSE;

	if ( mUserMarket_BtnRefresh.OnLButtonDown(ptMouse) )	return FALSE;

	if ( mUserMarket_BtnNext.OnLButtonDown(ptMouse) )	return FALSE;
	
	if ( mUserMarket_BtnBefore.OnLButtonDown(ptMouse) )		return FALSE;

	for ( INT nI = 0; nI < _MAX_MARKETCELL; nI++ )
	{
		if ( PtInRect(&mUserMarket_rcList[nI], ptMouse) )
		{
			mUserMarket_nSelected = nI;
			SetItemDesc();
		}
	}

	if ( PtInRect(&mUserMarket_rcFindItem, ptMouse) )
	{
		MoveWindow(g_xChatEditBox.GetSafehWnd(), 
				   g_xMainWnd.m_rcWindow.left+mUserMarket_rcFindItem.left, 
				   g_xMainWnd.m_rcWindow.top+mUserMarket_rcFindItem.top+3, mUserMarket_rcFindItem.right-mUserMarket_rcFindItem.left, 15, TRUE);
		//------------------------------------------------------------------------------------------------------------
		SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETPASSWORDCHAR, NULL, 0);

		SetWindowText(g_xChatEditBox.GetSafehWnd(), "");
		SetFocus(g_xChatEditBox.GetSafehWnd());
		ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);

		g_xChatEditBox.SetHanguelMode();
		g_xChatEditBox.SetEnterUse(FALSE);
		mUserMarket_bSelectedFindItem = TRUE;
		mUserMarket_bSelectedFindName = FALSE;
	}
	else if ( PtInRect(&mUserMarket_rcFindName, ptMouse) )
	{
		MoveWindow(g_xChatEditBox.GetSafehWnd(), 
				   g_xMainWnd.m_rcWindow.left+mUserMarket_rcFindName.left, 
				   g_xMainWnd.m_rcWindow.top+mUserMarket_rcFindName.top+3, mUserMarket_rcFindName.right-mUserMarket_rcFindName.left, 15, TRUE);
		//------------------------------------------------------------------------------------------------------------
		SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETPASSWORDCHAR, NULL, 0);

		SetWindowText(g_xChatEditBox.GetSafehWnd(), "");
		SetFocus(g_xChatEditBox.GetSafehWnd());
		ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);

		g_xChatEditBox.SetHanguelMode();
		g_xChatEditBox.SetEnterUse(FALSE);
		mUserMarket_bSelectedFindItem = FALSE;
		mUserMarket_bSelectedFindName = TRUE;
	}

	return FALSE;
}

BOOL CMarketWnd::OnRButtonDown(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse)
{
	return FALSE;
}

BOOL CMarketWnd::OnMouseMove(POINT ptMouse)
{
	mUserMarket_BtnClose.OnMouseMove(ptMouse);
	mUserMarket_BtnDetailClose.OnMouseMove(ptMouse);
	mUserMarket_BtnBuy.OnMouseMove(ptMouse);
	mUserMarket_BtnRegistry.OnMouseMove(ptMouse);
	mUserMarket_BtnFindItem.OnMouseMove(ptMouse);
	mUserMarket_BtnFindWriter.OnMouseMove(ptMouse);
	mUserMarket_BtnRefresh.OnMouseMove(ptMouse);
	mUserMarket_BtnNext.OnMouseMove(ptMouse);
	mUserMarket_BtnBefore.OnMouseMove(ptMouse);

	for ( INT nI = 0; nI < _MAX_MARKETCELL; nI++ )
	{
		if ( PtInRect(&mUserMarket_rcList[nI], ptMouse) )
		{
			mUserMarket_nMouseLocated = nI;
			return FALSE;
		}
	}
	mUserMarket_nMouseLocated = -1;

	return FALSE;
}


BOOL CMarketWnd::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	switch ( wParam )
	{
		case VK_RETURN:
		{
			if ( mUserMarket_bSelectedFindItem || mUserMarket_bSelectedFindName )
			{
				SendFindMsg();
				return TRUE;
			}
		}
		break;
		case VK_DOWN:
		{
			mUserMarket_nSelected++;
			if ( mUserMarket_nSelected > 12 )
				mUserMarket_nSelected = 12;
			SetItemDesc();
			return TRUE;
		}
		break;
		case VK_UP:
		{
			mUserMarket_nSelected--;
			if ( mUserMarket_nSelected < 0 )
				mUserMarket_nSelected = 0;
			SetItemDesc();
			return TRUE;
		}
		break;
		case VK_RIGHT:
		{
			DWORD dwCurr = timeGetTime();
			if ( dwCurr - mUserMarket_dwLastSendTime > 1000 )
			{
				mUserMarket_bReadytoGet = TRUE;
				g_xClientSocket.SendNextPageMarket(mUserMarket_nNpcId);
				mUserMarket_dwLastSendTime = dwCurr;
			}
			return TRUE;
		}
		break;
		case VK_LEFT:
		{
			DWORD dwCurr = timeGetTime();
			if ( dwCurr - mUserMarket_dwLastSendTime > 1000 )
			{
				mUserMarket_bReadytoGet = TRUE;
				g_xClientSocket.SendPrevPageMarket(mUserMarket_nNpcId);
				mUserMarket_dwLastSendTime = dwCurr;
			}
			return TRUE;
		}
		break;
	}
	return FALSE;
}


VOID CMarketWnd::OnScrollUp()
{
	mUserMarket_nSelected++;
	if ( mUserMarket_nSelected > 12 )
		mUserMarket_nSelected = 12;
	SetItemDesc();
}


VOID CMarketWnd::OnScrollDown()
{
	mUserMarket_nSelected--;
	if ( mUserMarket_nSelected < 0 )
		mUserMarket_nSelected = 0;
	SetItemDesc();
}

VOID CMarketWnd::SetMarketItemList(CHAR* pszMsg, INT nCount, INT nPage, INT nTotalPage)
{
	char *pszNext;
	INT nCnt = 0;
	LPCLIENTSELLITEM pstMarketItem = NULL;

	// 리스트를 새로 받기 때문에 Init해야 할 것들을 Init한다.
	m_xMarketItemList.ClearAll();
	mUserMarket_nMouseLocated = -1;
	mUserMarket_nSelected = 0;
	mUserMarket_bReadytoGet = FALSE;

	if ( nCount <= 0 )
		return;

	mUserMarket_nCurPage = nPage;
	mUserMarket_nTotalPage = nTotalPage;

	char *pszItem = (pszMsg + _DEFBLOCKSIZE);

	do
	{
		if ( pszNext = strchr(pszItem, '/') )
		{
			pstMarketItem = new CLIENTSELLITEM;

			*pszNext = '\0';

			fnDecode6BitBuf(pszItem, (char*)pstMarketItem, sizeof(CLIENTSELLITEM));

			pszItem = pszNext + 1;

			nCnt++;

			m_xMarketItemList.Insert(pstMarketItem);
		}

	} while (nCnt < nCount && pszNext);

	SetItemDesc();
}


VOID CMarketWnd::SetItemDesc()
{
	mUserMarket_xDesclist.ClearAll();

	DWORD dwFontColor = RGB(250, 250, 250), dwFontBackColor = RGB(0, 0, 0);
	LPCLIENTSELLITEM pstMarketItem = NULL;
	CListNode < CLIENTSELLITEM > *pNode;
	INT  nLine, nListCnt;
	INT  nWidth = 217;

	for ( pNode = m_xMarketItemList.GetHead(), nListCnt = 0, nLine = 0; pNode; pNode = pNode->GetNext(), nListCnt++ )
	{
		if ( nListCnt == mUserMarket_nSelected )
		{
			char *szTemp;
			char *szText;
			CHAR szBuf[121];
			INT nLineCount = 0;

			pstMarketItem = pNode->GetData();
			mUserMarket_xShowItem.SetItem(pstMarketItem->stItem, 0);
	
			if ( pstMarketItem->szText[0] )
			{
				sprintf(szBuf, "%s", pstMarketItem->szText);
				szText = pstMarketItem->szText;
				do 
				{
					INT  nCnt;
					CHAT* stChat;
					INT	 nLineCnt;
					CHAR pszDivied[_MAX_STRING_LEN*2];
					CHAR pszArg[9][MAX_PATH];

					if ( szTemp = strchr(szText, 0x0D) )
					{
						*szTemp++ = '\0';
					}

					ZeroMemory(pszDivied, _MAX_STRING_LEN*2);
					ZeroMemory(pszArg,	  MAX_PATH*9);

					g_xMainWnd.StringDivide(nWidth, nLineCnt, szText, pszDivied);

					sscanf(pszDivied, "%[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c", pszArg[0], pszArg[1], pszArg[2], pszArg[3], pszArg[4], pszArg[5], pszArg[6], pszArg[7], pszArg[8], pszArg[9]);

					if ( nLineCnt > 9 )
					{
						nLineCnt = 9;
					}

					// 문자열 삽입.
					for ( nCnt = 0; nCnt < nLineCnt; nCnt++ )
					{
						stChat = new CHAT;
						stChat->dwFontColor = dwFontColor;
						stChat->dwBackColor = dwFontBackColor;
						strcpy(stChat->pszChat, pszArg[nCnt]);
						
						mUserMarket_xDesclist.Insert(stChat);
					}
					szText = szTemp;
					nLineCount++;
				}while(szTemp && nLineCount < 9);

				sprintf(pstMarketItem->szText, "%s", szBuf);
			}
		}
	}
}

VOID CMarketWnd::SendFindMsg()
{
	CHAR szTemp[MAX_PATH];
	CHAR szMsg[MAX_PATH];
	INT  nDevider = 13;

	DWORD dwCurr = timeGetTime();

	if ( dwCurr - mUserMarket_dwLastSendTime > 1000 )
	{
		mUserMarket_dwLastSendTime = dwCurr;
	
		MoveWindow(g_xChatEditBox.GetSafehWnd(), 
				   g_xMainWnd.m_rcWindow.left+_NEW_INPUT_EDITWND_XPOS, g_xMainWnd.m_rcWindow.top+_NEW_INPUT_EDITWND_YPOS,
				   _NEW_INPUT_EDITWND_WIDTH, _NEW_INPUT_EDITWND_HEIGHT, TRUE);
		ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_HIDE);
		GetWindowText(g_xChatEditBox.GetSafehWnd(), szTemp, MAX_PATH);

		g_xChatEditBox.SetEnterUse(TRUE);

		SetWindowText(g_xChatEditBox.GetSafehWnd(), "");
	
		if ( mUserMarket_bSelectedFindItem && szTemp[0] != NULL)
		{
			sprintf(szMsg, "*%c%s%c0", nDevider, szTemp, nDevider);
			mUserMarket_bReadytoGet = TRUE;
			g_xClientSocket.SendSearchMarket(mUserMarket_nNpcId, szMsg);
			mUserMarket_bSelectedFindItem = FALSE;
		}
		else if ( mUserMarket_bSelectedFindName && szTemp[0] != NULL )
		{
			sprintf(szMsg, "%s%c*%c0", szTemp, nDevider, nDevider);
			mUserMarket_bReadytoGet = TRUE;
			g_xClientSocket.SendSearchMarket(mUserMarket_nNpcId, szMsg);
			mUserMarket_bSelectedFindName = FALSE;
		}
		else
		{
			sprintf(szMsg, "*%c*%c0", nDevider, nDevider);
			mUserMarket_bReadytoGet = TRUE;
			g_xClientSocket.SendSearchMarket(mUserMarket_nNpcId, szMsg);
		}
	}
}

VOID CMarketWnd::CloseMarketWnd()
{
	if ( mUserMarket_bSelectedFindItem || mUserMarket_bSelectedFindName )
	{
		MoveWindow(g_xChatEditBox.GetSafehWnd(), 
				   g_xMainWnd.m_rcWindow.left+_NEW_INPUT_EDITWND_XPOS, g_xMainWnd.m_rcWindow.top+_NEW_INPUT_EDITWND_YPOS,
				   _NEW_INPUT_EDITWND_WIDTH, _NEW_INPUT_EDITWND_HEIGHT, TRUE);
		ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_HIDE);
		SetWindowText(g_xChatEditBox.GetSafehWnd(), "");

		g_xChatEditBox.SetEnterUse(TRUE);
	}

	g_xGameProc.m_xInterface.DeleteWindowToList(_WND_ID_USERMARKET);
	SetGameWndActive(FALSE);

	mUserMarket_nSelected = 0;
	mUserMarket_nNpcId = -1;
	mUserMarket_dwLastSendTime = 0;
	mUserMarket_dwIconTimer = 0;

	mUserMarket_nIconFrame = 0;
	mUserMarket_nCurPage = 0;
	mUserMarket_nTotalPage = 0;

	mUserMarket_bReadytoGet = FALSE;

	mUserMarket_bSelectedFindItem = FALSE;
	mUserMarket_bSelectedFindName = FALSE;

	m_xMarketItemList.ClearAll();
	mUserMarket_xDesclist.ClearAll();
}


VOID CMarketWnd::BuyItem()
{
	LPCLIENTSELLITEM pstMarketItem = NULL;
	CListNode < CLIENTSELLITEM > *pNode;
	INT nListCnt;

	for ( pNode = m_xMarketItemList.GetHead(), nListCnt = 0; pNode; pNode = pNode->GetNext(), nListCnt++ )
	{
		if ( nListCnt == mUserMarket_nSelected )
		{
			pstMarketItem = pNode->GetData();

			mUserMarket_bReadytoGet = TRUE;
			g_xClientSocket.SendBuyMarketItem(mUserMarket_nNpcId, pstMarketItem->nSellIndex, pstMarketItem->stItem.stStdItem.szName);
			mUserMarket_dwLastSendTime = timeGetTime();
		}
	}
}

VOID CMarketWnd::TakeBackMarketItem()
{
	DWORD dwCurr = timeGetTime();
	if ( dwCurr - mUserMarket_dwLastSendTime > 1000 )
	{
		LPCLIENTSELLITEM pstMarketItem = NULL;
		CListNode < CLIENTSELLITEM > *pNode;
		INT nListCnt;

		for ( pNode = m_xMarketItemList.GetHead(), nListCnt = 0; pNode; pNode = pNode->GetNext(), nListCnt++ )
		{
			if ( nListCnt == mUserMarket_nSelected )
			{
				pstMarketItem = pNode->GetData();

				mUserMarket_bReadytoGet = TRUE;
				g_xClientSocket.SendTakeBackMarketItem(mUserMarket_nNpcId, pstMarketItem->nSellIndex);
				mUserMarket_dwLastSendTime = dwCurr;
			}
		}
	}
}

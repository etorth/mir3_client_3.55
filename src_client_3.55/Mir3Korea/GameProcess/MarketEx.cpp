// MarketEx.cpp
// 원보상점 2006.06.13 by eriastoa
#include "StdAfx.h"

#ifdef _TEST_SERVER

CMarketExWnd::CMarketExWnd()
{
	Init();
}

CMarketExWnd::~CMarketExWnd()
{
	Destroy();
}

VOID
CMarketExWnd::Init()
{
	CGameWnd::Init();

	mBtnWeapon.Init();		// 무기
	mBtnCloth.Init();		// 의복, 방어구
	mBtnEquip.Init();		// 장신구
	mBtnSkill.Init();		// 기능
	mBtnEtc.Init();			// 기타

	mBtnBuy.Init();			// 구입
	mBtnPresent.Init();		// 선물
	mBtnCancel.Init();		// 취소

	mBtnPrev.Init();		// 이전 페이지
	mBtnNext.Init();		// 다음 페이지
	mBtnClose.Init();		// 닫기

	mBtnPrice.Init();		// 가격
	mBtnItem.Init();		// 항목
	mBtnJob.Init();			// 직업
	
	mBtnSearch.Init();		// 찾기

	for( INT i = 0; i < _MAX_MARKETEX_XCELL5 * _MAX_MARKETEX_YCELL2; ++i )
		SetRect( &mRectItems5x2[ i ], 0, 0, 0, 0 );

	SetRect( &mRectSearch, 0, 0, 0, 0 );
	mbUseSearch		= FALSE;

	mnNpcId			= -1;
	mnSelectItem	= -1;
	mnCurPage		= 0;
	mnTotalPage		= 0;
	mnMouseLocated	= -1;

	mbPriceValue	= -1;
	mbSexValue		= -1;
	mbJobValue		= -1;
	mbItemValue		= 0;	// 중요
}

VOID
CMarketExWnd::Destroy()
{
	CGameWnd::Destroy();

	/*mbUseSearch		= FALSE;

	mnNpcId			= -1;
	mnSelectItem	= -1;
	mnCurPage		= 0;
	mnTotalPage		= 0;
	mnMouseLocated	= -1;

	mbPriceValue	= -1;
	mbSexValue		= -1;
	mbJobValue		= -1;

	mItemList.ClearAll();
	mFindItemLists.ClearAll();
	mAlignItemLists.ClearAll();*/
	mSaleItemLists.ClearAll();
}

VOID
CMarketExWnd::CreateMarketExWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend)
{
	CreateGameWnd( nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight, bBlend );

	// 인덱스 번호는 는 GameInter.wil 에 있는 파일번호
	// + x, y 는 실제 이미지의 상대좌표 -> 따로 좌표를 알아내어서 더해주어야 한다
	
	mBtnWeapon.CreateGameBtn( pxWndImage, 3051, 3050, nStartX + 21, nStartY + 118, g_xMsg.GetMsg( 7101 ), _BTN_TYPE_FOCUS, -1, TRUE );
	mBtnCloth.CreateGameBtn( pxWndImage, 3061, 3060, nStartX + 21, nStartY + 171, g_xMsg.GetMsg( 7102 ), _BTN_TYPE_FOCUS, -1, TRUE );
	mBtnEquip.CreateGameBtn( pxWndImage, 3071, 3070, nStartX + 21, nStartY + 224, g_xMsg.GetMsg( 7103 ), _BTN_TYPE_FOCUS, -1, TRUE );
	mBtnSkill.CreateGameBtn( pxWndImage, 3041, 3040, nStartX + 21, nStartY + 277, g_xMsg.GetMsg( 7104 ), _BTN_TYPE_FOCUS, -1, TRUE );
	mBtnEtc.CreateGameBtn( pxWndImage, 3080, 3081, nStartX + 21, nStartY + 330, g_xMsg.GetMsg( 7105 ), _BTN_TYPE_FOCUS, -1, TRUE );

	mBtnBuy.CreateGameBtn( pxWndImage, 3011, 3010, nStartX + 163, nStartY + 392, g_xMsg.GetMsg( 7106 ), _BTN_TYPE_FOCUS, -1, TRUE );
	mBtnPresent.CreateGameBtn( pxWndImage, 3021, 3020, nStartX + 243, nStartY + 392, g_xMsg.GetMsg( 7107 ), _BTN_TYPE_FOCUS, -1, TRUE );
	mBtnCancel.CreateGameBtn( pxWndImage, 3031, 3030, nStartX + 323, nStartY + 392, g_xMsg.GetMsg( 7108 ), _BTN_TYPE_FOCUS, -1, TRUE );

	mBtnPrev.CreateGameBtn( pxWndImage, 3091, 3091, nStartX + 450, nStartY + 398, g_xMsg.GetMsg( 7109 ), _BTN_TYPE_FOCUS, -1, FALSE );
	mBtnNext.CreateGameBtn( pxWndImage, 3090, 3090, nStartX + 586, nStartY + 398, g_xMsg.GetMsg( 7110 ), _BTN_TYPE_FOCUS, -1, FALSE );
	mBtnClose.CreateGameBtn( pxWndImage, 3100, 3100, nStartX + 668, nStartY + 395, g_xMsg.GetMsg( 7111 ), _BTN_TYPE_FOCUS, -1, FALSE );

	//-- 대만
	mBtnPrice.CreateGameBtn( pxWndImage, 3121, 3122, nStartX + 162, nStartY + 80, g_xMsg.GetMsg( 7112 ), _BTN_TYPE_FOCUS, 3120, TRUE );
	mBtnItem.CreateGameBtn( pxWndImage, 3131, 3132, nStartX + 202, nStartY + 80, g_xMsg.GetMsg( 7113 ), _BTN_TYPE_FOCUS, 3130, TRUE );
	mBtnJob.CreateGameBtn( pxWndImage, 3141, 3142, nStartX + 249, nStartY + 80, g_xMsg.GetMsg( 7114 ), _BTN_TYPE_FOCUS, 3140, TRUE );
	
	//-- 중국
	/*mBtnPrice.CreateGameBtn( pxWndImage, 3161, 3162, nStartX + 162, nStartY + 80, g_xMsg.GetMsg( 7112 ), _BTN_TYPE_FOCUS, 3160, TRUE );
	mBtnItem.CreateGameBtn( pxWndImage, 3181, 3182, nStartX + 202, nStartY + 80, g_xMsg.GetMsg( 7113 ), _BTN_TYPE_FOCUS, 3180, TRUE );
	mBtnJob.CreateGameBtn( pxWndImage, 3171, 3172, nStartX + 249, nStartY + 80, g_xMsg.GetMsg( 7114 ), _BTN_TYPE_FOCUS, 3170, TRUE );*/
	
	mBtnSearch.CreateGameBtn( pxWndImage, 3001, 3000, nStartX + 627, nStartY + 80, g_xMsg.GetMsg( 7115 ), _BTN_TYPE_FOCUS, -1, TRUE );

	SetRect( &mRectSearch, m_rcWnd.left + 484, m_rcWnd.top + 88, m_rcWnd.left + 484 + 129, m_rcWnd.top + 88 + 22 );
	
	INT sx = m_rcWnd.left + 73;
	INT sy = m_rcWnd.top + 119;
	INT w = 104;
	INT h = 115;
	for( INT i = 0; i < _MAX_MARKETEX_YCELL2; ++i )
	{
		for( INT j = 0; j < _MAX_MARKETEX_XCELL5; ++j )
		{
			SetRect( &mRectItems5x2[ i * _MAX_MARKETEX_XCELL5 + j ],
				sx + j * ( 203 - 73 ), sy + i * ( 252 - 119 ), sx + j * ( 203 - 73 ) + w, sy + i * ( 252 - 119 ) + h);
		}
	}

	LoadItemLists();
		
}

VOID
CMarketExWnd::ShowMarketExWnd()
{
	ShowGameWnd();

	mBtnJob.ShowGameBtn();			// 직업
	mBtnItem.ShowGameBtn();			// 항목
	mBtnPrice.ShowGameBtn();		// 가격

	CWHWilImageData* pxTitleImg = &g_xGameProc.m_xImage.m_xImageList[ _IMAGE_INTER ];
	//if( pxTitleImg->NewSetIndex( 3190 ) )	// 타이틀 -- 중국
	if( pxTitleImg->NewSetIndex( 3150 ) )	// 타이틀 -- 대만
	{
		g_xMainWnd.DrawWithImageForComp( m_rcWnd.left + 269, m_rcWnd.top + 22, 184, 36, (WORD*)pxTitleImg->m_pbCurrImage );
	}

	// 마우스 있는 곳 뒷판
	if ( mnMouseLocated != -1 )		// 마우스 움직임
	{
		D3DMATERIAL7 mtrl;
		D3DVECTOR	 vecTrans((FLOAT)mRectItems5x2[mnMouseLocated].left, (FLOAT)mRectItems5x2[mnMouseLocated].top, 0);
		D3DVECTOR	 vecScale((FLOAT)mRectItems5x2[mnMouseLocated].right-mRectItems5x2[mnMouseLocated].left, 
			mRectItems5x2[mnMouseLocated].bottom-mRectItems5x2[mnMouseLocated].top, 1);

		D3DUtil_InitMaterial(mtrl, (FLOAT)50/255.0f, (FLOAT)50/255.0f, (FLOAT)50/255.0f);
		mtrl.diffuse.a = 180.0f/255.0f;
		g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
	}
	if ( mnSelectItem != -1 )		// 선택된 아이템
	{
		D3DMATERIAL7 mtrl;
		D3DVECTOR	 vecTrans((FLOAT)mRectItems5x2[mnSelectItem].left, (FLOAT)mRectItems5x2[mnSelectItem].top, 0);
		D3DVECTOR	 vecScale((FLOAT)mRectItems5x2[mnSelectItem].right-mRectItems5x2[mnSelectItem].left, 
			mRectItems5x2[mnSelectItem].bottom-mRectItems5x2[mnSelectItem].top, 1);

		D3DUtil_InitMaterial(mtrl, (FLOAT)35/255.0f, (FLOAT)114/255.0f, (FLOAT)156/255.0f);
		mtrl.diffuse.a = 180.0f/255.0f;
		g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
	}

	// 페이지 정보 그리기
	if( mnCurPage != 0 || mnTotalPage != 0 )
	{
		CHAR szTemp[ 32 ];
		RECT rcPage = {m_rcWnd.left + 488, m_rcWnd.top + 396, m_rcWnd.left + 488 + 82, m_rcWnd.top + 396 + 21};
		sprintf( szTemp, "%d / %d", mnCurPage, mnTotalPage);
		g_xMainWnd.PutsHan(NULL, rcPage, RGB( 250,  250,  0), 0, szTemp);
	}

	// 아이템 그리기
	LPCLIENTSELLITEM pstMarketItem = NULL;
	CListNode < CLIENTSELLITEM > *pNode;

	// 이미지 데이터 포인터 가져오기
	CWHWilImageData* pxItemImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_INVENTORY];
	CWHWilImageData* pxSaleImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_MARKETEX];
	INT index, nCX, nCY, nSX, nSY;
	RECT rcImg, rcItemCell, rcShowItem, rcPrice, rcItemName;
	CHAR szPrice[ MAX_PATH ];

	// // 아이템 정보 출력 2006.10.23
	CItem* pSelectedItem = NULL;
	RECT rtSelected;

	for( pNode = mItemList.GetTail(), index = mItemList.GetCount() - 1; pNode; pNode = pNode->GetPrev(), --index )
	{
		pstMarketItem = pNode->GetData();
		
		// 아이템 그리기
		if( pxSaleImg->NewSetIndex(pstMarketItem->stItem.stStdItem.wLooks) )
		{
			nCX = mRectItems5x2[ index ].left + ( mRectItems5x2[ index ].right - mRectItems5x2[ index ].left ) / 2;
			nCY = mRectItems5x2[ index ].top + ( mRectItems5x2[ index ].bottom - mRectItems5x2[ index ].top ) / 2;
			nSX = nCX - pxSaleImg->m_lpstNewCurrWilImageInfo->shWidth/2;
			nSY = nCY - pxSaleImg->m_lpstNewCurrWilImageInfo->shHeight/2;
			
			SetRect(&rcImg, 0, 0, pxSaleImg->m_lpstNewCurrWilImageInfo->shWidth, pxSaleImg->m_lpstNewCurrWilImageInfo->shHeight);
			
			// 아이템 뒷판 그리기
			SetRect( &rcItemCell, nSX - 15, nSY - 7, nSX+rcImg.right + 15, nSY+rcImg.bottom + 7);
			SetRect(&rcShowItem, rcItemCell.left, rcItemCell.top, rcItemCell.right, rcItemCell.bottom );
			
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
			g_xMainWnd.DrawWithImageForComp(nSX, nSY, &rcImg, (WORD*)pxSaleImg->m_pbCurrImage, wClr);
			
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
		// 중복된 이미지 따로 구분해서 인벤토리에서 그리기
		else if ( pxItemImg->NewSetIndex(pstMarketItem->stItem.stStdItem.wLooks) )
		{
			nCX = mRectItems5x2[ index ].left + ( mRectItems5x2[ index ].right - mRectItems5x2[ index ].left ) / 2;
			nCY = mRectItems5x2[ index ].top + ( mRectItems5x2[ index ].bottom - mRectItems5x2[ index ].top ) / 2;
			nSX = nCX - pxItemImg->m_lpstNewCurrWilImageInfo->shWidth/2;
			nSY = nCY - pxItemImg->m_lpstNewCurrWilImageInfo->shHeight/2;
			
			SetRect(&rcImg, 0, 0, pxItemImg->m_lpstNewCurrWilImageInfo->shWidth, pxItemImg->m_lpstNewCurrWilImageInfo->shHeight);
			
			// 아이템 뒷판 그리기
			SetRect( &rcItemCell, nSX - 15, nSY - 7, nSX+rcImg.right + 15, nSY+rcImg.bottom + 7);
			SetRect(&rcShowItem, rcItemCell.left, rcItemCell.top, rcItemCell.right, rcItemCell.bottom );
			
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
		
		// 아이템 이름
		SetRect( &rcItemName, mRectItems5x2[ index ].left, mRectItems5x2[ index ].top,
			mRectItems5x2[ index ].left + mRectItems5x2[ index ].right - mRectItems5x2[ index ].left, mRectItems5x2[ index ].top + 20 );
		g_xMainWnd.PutsHan( NULL, rcItemName, RGB( 250,  250,  250), 0, pstMarketItem->stItem.stStdItem.szName );
		
		// 아이템 가격
		SetRect( &rcPrice, mRectItems5x2[ index ].left, mRectItems5x2[ index ].top + mRectItems5x2[ index ].bottom - mRectItems5x2[ index ].top - 20,
			mRectItems5x2[ index ].left + mRectItems5x2[ index ].right - mRectItems5x2[ index ].left,
			mRectItems5x2[ index ].top + mRectItems5x2[ index ].bottom - mRectItems5x2[ index ].top );
		GetNumWithComma( pstMarketItem->nSellPrice, szPrice );
		if( pstMarketItem->nSellPrice >= 10000000 )
		{
			g_xMainWnd.PutsHan(NULL, rcPrice, RGB( 250,  0,  0), 0, szPrice);
		}
		else if( pstMarketItem->nSellPrice >= 1000000 )
		{
			g_xMainWnd.PutsHan(NULL, rcPrice, RGB( 0,  250,  250), 0, szPrice);
		}
		else
		{
			g_xMainWnd.PutsHan(NULL, rcPrice, RGB( 250,  250,  250), 0, szPrice);
		}
		
		// 아이템 정보 출력
		if ( PtInRect(&rcShowItem, g_xGameProc.m_ptMousePos) && mnSelectItem != -1 )
		{
			rtSelected = rcShowItem;
			rtSelected.left += 35;
			rtSelected.top += 20;
			//mShowItems5x2[ index ].ShowItemStatus(rcShowItem.left + 35, rcShowItem.top + 22, TRUE, FALSE, TRUE);
			pSelectedItem = &mShowItems5x2[ index ];
		}
	}

	// 아이템 정보 출력 2006.10.23
	if( pSelectedItem )
	{
		pSelectedItem->ShowItemStatus(rtSelected.left, rtSelected.top, TRUE, FALSE, TRUE);
		pSelectedItem = NULL;
	}

	mBtnWeapon.ShowGameBtn();		// 무기
	mBtnCloth.ShowGameBtn();		// 의복, 방어구
	mBtnEquip.ShowGameBtn();		// 장신구
	mBtnSkill.ShowGameBtn();		// 기능
	mBtnEtc.ShowGameBtn();			// 기타

	mBtnBuy.ShowGameBtn();			// 구입
	mBtnPresent.ShowGameBtn();		// 선물
	mBtnCancel.ShowGameBtn();		// 취소

	mBtnPrev.ShowGameBtn();			// 이전 페이지
	mBtnNext.ShowGameBtn();			// 다음 페이지
	mBtnClose.ShowGameBtn();		// 닫기
	
	mBtnSearch.ShowGameBtn();		// 찾기
	
}

VOID
CMarketExWnd::CloseMarketExWnd()
{
	MoveWindow( g_xChatEditBox.GetSafehWnd(),
		g_xMainWnd.m_rcWindow.left + _NEW_INPUT_EDITWND_XPOS, g_xMainWnd.m_rcWindow.top + _NEW_INPUT_EDITWND_YPOS,
		_NEW_INPUT_EDITWND_WIDTH, _NEW_INPUT_EDITWND_HEIGHT, TRUE );
	SetWindowText( g_xChatEditBox.GetSafehWnd(), "" );
	ShowWindow( g_xChatEditBox.GetSafehWnd(), SW_HIDE );
	g_xChatEditBox.SetEnterUse( TRUE );
	
	g_xGameProc.m_xInterface.DeleteWindowToList( m_nID );
	SetGameWndActive( FALSE );

	mbUseSearch		= FALSE;

	mnNpcId			= -1;
	mnSelectItem	= -1;
	mnCurPage		= 0;
	mnTotalPage		= 0;
	mnMouseLocated	= -1;

	mbPriceValue	= -1;
	mbSexValue		= -1;
	mbJobValue		= -1;

	mItemList.ClearAll();
	mFindItemLists.ClearAll();
	mAlignItemLists.ClearAll();
}

VOID
CMarketExWnd::FindItems()
{
	CHAR szName[ MAX_PATH ];
		
	MoveWindow( g_xChatEditBox.GetSafehWnd(),
		g_xMainWnd.m_rcWindow.left + _NEW_INPUT_EDITWND_XPOS, g_xMainWnd.m_rcWindow.top + _NEW_INPUT_EDITWND_YPOS,
		_NEW_INPUT_EDITWND_WIDTH, _NEW_INPUT_EDITWND_HEIGHT, TRUE );
	GetWindowText( g_xChatEditBox.GetSafehWnd(), szName, MAX_PATH );
	SetWindowText( g_xChatEditBox.GetSafehWnd(), "" );
	ShowWindow( g_xChatEditBox.GetSafehWnd(), SW_HIDE );
	g_xChatEditBox.SetEnterUse( TRUE );

	if ( mbUseSearch && szName[0] != NULL )
	{
		// 아이템 찾기
		mFindItemLists.ClearAll();
		
		LPSALEITEM pstMarketItem = NULL;
		CListNode < SALEITEM > *pNode;
		
		for ( pNode = mSaleItemLists.GetHead(); pNode; pNode = pNode->GetNext() )
		{
			if ( strcmp( szName, pNode->GetData()->stdItem.szName ) == 0 )
			{
				LPSALEITEM pSaleItem = new SALEITEM;
				*pSaleItem = *( pNode->GetData() );
				
				mFindItemLists.Insert( pSaleItem );
			}
		}

		INT nPage = 1;
		INT nTotalPage = mFindItemLists.GetCount() / ( _MAX_MARKETEX_XCELL5 * _MAX_MARKETEX_YCELL2 ) + 1;
		SetMarketExItemList( nPage, nTotalPage );
	}

	mbUseSearch = FALSE;
}

VOID
CMarketExWnd::SetMarketExItemList( INT nPage, INT nTotalPage )
{
	mItemList.ClearAll();
	mnSelectItem = 0;

	mnCurPage = nPage;
	mnTotalPage = nTotalPage;

	INT nCnt = 0;
	INT nIndex = ( nPage - 1 ) * _MAX_MARKETEX_XCELL5 * _MAX_MARKETEX_YCELL2;
	
	LPCLIENTSELLITEM pstMarketItem = NULL;
	while( TRUE )
	{
		if( nIndex >= mFindItemLists.GetCount() || nCnt >= _MAX_MARKETEX_XCELL5 * _MAX_MARKETEX_YCELL2 )
			break;
		
		pstMarketItem = new CLIENTSELLITEM;
		ZeroMemory( pstMarketItem, sizeof( CLIENTSELLITEM ) );
		SetSaleItem( nIndex, pstMarketItem, mFindItemLists[ nIndex ]->GetData() );
		mShowItems5x2[ nCnt ].SetItem( pstMarketItem->stItem, 0 );

		// 아이템 설명 추가
		// 2006.09.28
		mShowItems5x2[ nCnt ].m_nSellIndex = pstMarketItem->nSellIndex;
		
		mItemList.Insert( pstMarketItem );
		++nIndex;
		++nCnt;
	}		
}

VOID
CMarketExWnd::SetSaleItem( INT nIndex, CLIENTSELLITEM* pstMarketItem, SALEITEM* pSaleItem )
{
	pstMarketItem->nSellIndex			= pSaleItem->nIdentity; // 고유번호 - 아이템 구매시 필요하다
	pstMarketItem->nSellPrice			= pSaleItem->nSalePrice;
	sprintf( pstMarketItem->szItemName, "%s", pSaleItem->stdItem.szName );
		
	pstMarketItem->stItem.bLevel_R		= pSaleItem->bLevel_R;
	for( INT i = 0; i < 14; ++i )
		pstMarketItem->stItem.Desc[ i ] = pSaleItem->Desc[ i ];
	pstMarketItem->stItem.nDura			= pSaleItem->wDura;
	pstMarketItem->stItem.nDuraMax		= pSaleItem->wDuraMax;
	pstMarketItem->stItem.nMakeIndex	= pSaleItem->wIndex;
	pstMarketItem->stItem.ExpireTime	= pSaleItem->bPermitPeriod;
	pstMarketItem->stItem.stStdItem		= pSaleItem->stdItem;
	pstMarketItem->stItem.wAmount_GB	= 0;
}

VOID
// 선택 되어져 있는 아이템을 산다
CMarketExWnd::BuyItem()
{
	LPCLIENTSELLITEM pstMarketItem = NULL;
	CListNode < CLIENTSELLITEM > *pNode;
	INT nListCnt;
	INT nCount = 1; // 갯수

	for ( pNode = mItemList.GetHead(), nListCnt = 0; pNode; pNode = pNode->GetNext(), nListCnt++ )
	{
		if ( nListCnt == mnSelectItem )
		{
			pstMarketItem = pNode->GetData();

			g_xClientSocket.SendBuyMarketExItem( pstMarketItem->nSellIndex, nCount );
			break;
		}
	}
}

VOID
// 선택되어져 있는 아이템을 선물한다
CMarketExWnd::PresentItem( CHAR* pCharName )
{
	LPCLIENTSELLITEM pstMarketItem = NULL;
	CListNode < CLIENTSELLITEM > *pNode;
	INT nListCnt;
	INT nCount = 1; // 갯수

	for ( pNode = mItemList.GetHead(), nListCnt = 0; pNode; pNode = pNode->GetNext(), nListCnt++ )
	{
		if ( nListCnt == mnSelectItem )
		{
			pstMarketItem = pNode->GetData();

			g_xClientSocket.SendGiftMarketExItem( pstMarketItem->nSellIndex, nCount, pCharName );
			break;
		}
	}
}

VOID
CMarketExWnd::SetGameWndActive( BOOL bActive )
{
	CGameWnd::SetGameWndActive( bActive );

	if( bActive )
	{
		mFindItemLists.ClearAll();
		
		LPSALEITEM pstMarketItem = NULL;
		CListNode < SALEITEM > *pNode;
		
		for ( pNode = mSaleItemLists.GetHead(); pNode; pNode = pNode->GetNext() )
		{
			LPSALEITEM pSaleItem = new SALEITEM;
			*pSaleItem = *( pNode->GetData() );
				
			mFindItemLists.Insert( pSaleItem );
		}

		INT nTotalPage = mSaleItemLists.GetCount() / ( _MAX_MARKETEX_XCELL5 * _MAX_MARKETEX_YCELL2 ) + 1;
		INT nPage = 1;

		SetMarketExItemList( nPage, nTotalPage );		
	}
}

VOID
CMarketExWnd::SetAlignMarketExItemList( ALIGN_MARKETEX_ITEM align, BOOL bListClear )
{
	// 1 무기
	// 2 의복 / 방어구
	// 3 장신구
	// 4 기능
	// 5 기타 / 븍수

	if( bListClear )
		mFindItemLists.ClearAll();
	
	CListNode < SALEITEM > *pNode;
	INT nValue = 0;
	
	for ( pNode = mSaleItemLists.GetHead(); pNode; pNode = pNode->GetNext() )
	{
		nValue = pNode->GetData()->nIdentity / 100000000;
		if( nValue == ( INT )align )
		{
			LPSALEITEM pSaleItem = new SALEITEM;
			*pSaleItem = *( pNode->GetData() );
			
			mFindItemLists.Insert( pSaleItem );
		}
	} //-- END for

	INT nPage = 1;
	INT nTotalPage = mFindItemLists.GetCount() / ( _MAX_MARKETEX_XCELL5 * _MAX_MARKETEX_YCELL2 ) + 1;
	SetMarketExItemList( nPage, nTotalPage );
}

VOID
//-- 가격별로 정렬
CMarketExWnd::SetAlignItemListFromPrice( ALIGN_MARKETEX_ITEM_PRICE price )
{
	//--
	mAlignItemLists.ClearAll();
	INT size = mFindItemLists.GetCount();
	LPSALEITEM pItem = new SALEITEM[ size ];

	// 배열에 복사
	INT nCnt = 0;
	CListNode< SALEITEM >* pNode = NULL;
	for ( pNode = mFindItemLists.GetHead(); pNode; pNode = pNode->GetNext(), ++nCnt )
	{
		pItem[ nCnt ] = *( pNode->GetData() );
	}

	// selection sort
	SALEITEM temp;
	INT index = 0;
	for( INT n = 0; n < nCnt - 1; ++n )
	{
		index = n;
		for( INT j = n + 1; j < nCnt; ++j )
		{
			if( price == MI_ALIGN_PRICE_UPPER )
			{
				if( pItem[ j ].nSalePrice < pItem[ index ].nSalePrice )
					index = j;
			}
			else if( price == MI_ALIGN_PRICE_LOWER )
			{
				if( pItem[ j ].nSalePrice > pItem[ index ].nSalePrice )
					index = j;				
			}
		}

		temp = pItem[ index ];
		pItem[ index ] = pItem[ n ];
		pItem[ n ] = temp;
	}

	// sorted items copy to mFindItemLists
	mFindItemLists.ClearAll();
	for( INT i = 0; i < nCnt; ++i )
	{
		LPSALEITEM pSaleItem = new SALEITEM;
		*pSaleItem = pItem[ i ];
		mFindItemLists.Insert( pSaleItem );
	}

	delete [] pItem;

	INT nPage = 1;
	INT nTotalPage = mFindItemLists.GetCount() / ( _MAX_MARKETEX_XCELL5 * _MAX_MARKETEX_YCELL2 ) + 1;
	SetMarketExItemList( nPage, nTotalPage );
}


VOID
//-- 성별로 정렬
CMarketExWnd::SetAlignItemListFromSex( ALIGN_MARKETEX_ITEM_SEX sex )
{
	CListNode < SALEITEM > *pNode;
	INT nValue = -1;
	INT nJob = -1;
	INT nSex = -1;
	INT alignIntSex = ( INT )sex;

	// search - sex
	mAlignItemLists.ClearAll();
	for ( pNode = mFindItemLists.GetHead(); pNode; pNode = pNode->GetNext() )
	{
		nValue = pNode->GetData()->nIdentity / 100000000;
		nJob = ( pNode->GetData()->nIdentity - nValue * 100000000 ) / 10000000;
		nSex = ( pNode->GetData()->nIdentity - nValue * 100000000 - nJob * 10000000 ) / 1000000;

		if( nSex == ( INT )sex )
		{
			LPSALEITEM pSaleItem = new SALEITEM;
			*pSaleItem = *( pNode->GetData() );
			
			mAlignItemLists.Insert( pSaleItem );
		}
	} //-- END for

	// 나머지
	while( TRUE )
	{
		++alignIntSex;
		if( alignIntSex == ( INT )MAX_MI_ALIGN_SEX )			alignIntSex = ( INT )MI_ALIGN_SEX_COMMON;
		else if( alignIntSex > ( INT )MI_ALIGN_SEX_COMMON )		alignIntSex = ( INT )MI_ALIGN_SEX_MALE;

		if( ( INT )sex == alignIntSex ) break;

		for ( pNode = mFindItemLists.GetHead(); pNode; pNode = pNode->GetNext() )
		{
			nValue = pNode->GetData()->nIdentity / 100000000;
			nJob = ( pNode->GetData()->nIdentity - nValue * 100000000 ) / 10000000;
			nSex = ( pNode->GetData()->nIdentity - nValue * 100000000 - nJob * 10000000 ) / 1000000;
			
			if( nSex == ( INT )alignIntSex )
			{
				LPSALEITEM pSaleItem = new SALEITEM;
				*pSaleItem = *( pNode->GetData() );
				
				mAlignItemLists.Insert( pSaleItem );
			}
		} //-- END for
	}

	// copy
	mFindItemLists.ClearAll();
	for( pNode = mAlignItemLists.GetHead(); pNode; pNode = pNode->GetNext() )
	{
		LPSALEITEM pSaleItem = new SALEITEM;
		*pSaleItem = *( pNode->GetData() );
		
		mFindItemLists.Insert( pSaleItem );		
	}

	INT nPage = 1;
	INT nTotalPage = mFindItemLists.GetCount() / ( _MAX_MARKETEX_XCELL5 * _MAX_MARKETEX_YCELL2 ) + 1;
	SetMarketExItemList( nPage, nTotalPage );
}

VOID
//-- 직업별로 정렬
CMarketExWnd::SetAlignItemListFromJob( ALIGN_MARKETEX_ITEM_JOB job )
{
	CListNode < SALEITEM > *pNode;
	INT nValue = -1;
	INT nJob = -1;
	INT alignIntJob = ( INT )job;

	// search - job
	mAlignItemLists.ClearAll();
	for ( pNode = mFindItemLists.GetHead(); pNode; pNode = pNode->GetNext() )
	{
		nValue = pNode->GetData()->nIdentity / 100000000;
		nJob = ( pNode->GetData()->nIdentity - nValue * 100000000 ) / 10000000;

		if( nJob == ( INT )job )
		{
			LPSALEITEM pSaleItem = new SALEITEM;
			*pSaleItem = *( pNode->GetData() );
			
			mAlignItemLists.Insert( pSaleItem );
		}
	} //-- END for

	// 나머지
	while( TRUE )
	{
		++alignIntJob;
		if( alignIntJob == ( INT )MAX_MI_ALIGN_JOB )			alignIntJob = ( INT )MI_ALIGN_JOB_COMMON;
		else if( alignIntJob > ( INT )MI_ALIGN_JOB_COMMON )		alignIntJob = ( INT )MI_ALIGN_JOB_JUNSA;

		if( ( INT )job == alignIntJob ) break;

		for ( pNode = mFindItemLists.GetHead(); pNode; pNode = pNode->GetNext() )
		{
			nValue = pNode->GetData()->nIdentity / 100000000;
			nJob = ( pNode->GetData()->nIdentity - nValue * 100000000 ) / 10000000;
			
			if( nJob == ( INT )alignIntJob )
			{
				LPSALEITEM pSaleItem = new SALEITEM;
				*pSaleItem = *( pNode->GetData() );
				
				mAlignItemLists.Insert( pSaleItem );
			}
		} //-- END for
	}

	// copy
	mFindItemLists.ClearAll();
	for( pNode = mAlignItemLists.GetHead(); pNode; pNode = pNode->GetNext() )
	{
		LPSALEITEM pSaleItem = new SALEITEM;
		*pSaleItem = *( pNode->GetData() );
		
		mFindItemLists.Insert( pSaleItem );		
	}

	INT nPage = 1;
	INT nTotalPage = mFindItemLists.GetCount() / ( _MAX_MARKETEX_XCELL5 * _MAX_MARKETEX_YCELL2 ) + 1;
	SetMarketExItemList( nPage, nTotalPage );
}

VOID
CMarketExWnd::SetAlignItemListFromItem( ALIGN_MARKETEX_ITEM item )
{
	/*
	INT nItemValue = ( INT )item;
	mAlignItemLists.ClearAll();
	SetAlignMarketExItemList( item, FALSE );

	while( TRUE )
	{
		++nItemValue;
		if( nItemValue == ( INT )MAX_MI_ALIGN ) nItemValue = MI_ALIGN_WEAPON;
		if( ( INT )item == nItemValue ) break;

		SetAlignMarketExItemList( ( ALIGN_MARKETEX_ITEM )nItemValue, FALSE );
	}
	*/

	mAlignItemLists.ClearAll();
	INT nItemValue = ( INT )item;

	CListNode < SALEITEM > *pNode;
	INT nValue = 0;
	
	for ( pNode = mFindItemLists.GetHead(); pNode; pNode = pNode->GetNext() )
	{
		nValue = pNode->GetData()->nIdentity / 100000000;
		if( nValue == ( INT )item )
		{
			LPSALEITEM pSaleItem = new SALEITEM;
			*pSaleItem = *( pNode->GetData() );
			
			mAlignItemLists.Insert( pSaleItem );
		}
	} //-- END for

	while( TRUE )
	{
		++nItemValue;
		if( nItemValue == MAX_MI_ALIGN ) nItemValue = ( INT )MI_ALIGN_WEAPON;
		if( nItemValue == ( INT )item ) break;
		
		for ( pNode = mFindItemLists.GetHead(); pNode; pNode = pNode->GetNext() )
		{
			nValue = pNode->GetData()->nIdentity / 100000000;
			if( nValue == ( INT )nItemValue )
			{
				LPSALEITEM pSaleItem = new SALEITEM;
				*pSaleItem = *( pNode->GetData() );
				
				mAlignItemLists.Insert( pSaleItem );
			}
		} //-- END for
	}

	// copy
	mFindItemLists.ClearAll();
	for( pNode = mAlignItemLists.GetHead(); pNode; pNode = pNode->GetNext() )
	{
		LPSALEITEM pSaleItem = new SALEITEM;
		*pSaleItem = *( pNode->GetData() );
		
		mFindItemLists.Insert( pSaleItem );		
	}

	INT nPage = 1;
	INT nTotalPage = mFindItemLists.GetCount() / ( _MAX_MARKETEX_XCELL5 * _MAX_MARKETEX_YCELL2 ) + 1;
	SetMarketExItemList( nPage, nTotalPage );
}

BOOL
CMarketExWnd::LoadItemLists()
{
	HANDLE hFile = CreateFile( "SaleItem.dat", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	if( hFile != INVALID_HANDLE_VALUE )
	{
		INT nCnt = 0;
		DWORD dwReadLen = 0;
		ReadFile( hFile, &nCnt, sizeof( INT ), &dwReadLen, NULL ); // 갯수

		while( TRUE )
		{
			LPSALEITEM pSaleItem = new SALEITEM;
			ZeroMemory( pSaleItem, sizeof( SALEITEM ) );
			if( ReadFile( hFile, pSaleItem, sizeof( SALEITEM ), &dwReadLen, NULL ) && dwReadLen == 0 )
				break;

			mSaleItemLists.Insert( pSaleItem );
		}
		CloseHandle(hFile);

		return TRUE;
	}

	MessageBox( NULL, "SaleItem.dat", "Load Error", MB_OK );
	return FALSE;
}

VOID
CMarketExWnd::DeleteItemLists()
{
}



BOOL
CMarketExWnd::OnLButtonDown( LPCOMMONITEMSET lpCommonItemSet, POINT ptMouse )
{
	if( mBtnWeapon.OnLButtonDown( ptMouse ) )		{ return TRUE; }
	if( mBtnCloth.OnLButtonDown( ptMouse ) )		{ return TRUE; }
	if( mBtnEquip.OnLButtonDown( ptMouse ) )		{ return TRUE; }
	if( mBtnSkill.OnLButtonDown( ptMouse ) )		{ return TRUE; }
	if( mBtnEtc.OnLButtonDown( ptMouse ) )			{ return TRUE; }

	if( mBtnBuy.OnLButtonDown( ptMouse ) )			{ return TRUE; }
	if( mBtnPresent.OnLButtonDown( ptMouse ) )		{ return TRUE; }
	if( mBtnCancel.OnLButtonDown( ptMouse ) )		{ return TRUE; }
	
	if( mBtnPrev.OnLButtonDown( ptMouse ) )			{ return TRUE; }
	if( mBtnNext.OnLButtonDown( ptMouse ) )			{ return TRUE; }
	if( mBtnClose.OnLButtonDown( ptMouse ) )		{ return TRUE; }
	
	if( mBtnPrice.OnLButtonDown( ptMouse ) )		{ return TRUE; }
	if( mBtnItem.OnLButtonDown( ptMouse ) )			{ return TRUE; }
	if( mBtnJob.OnLButtonDown( ptMouse ) )			{ return TRUE; }

	if( mBtnSearch.OnLButtonDown( ptMouse ) )		{ return TRUE; }

	// 아이템
	for( INT i = 0; i < _MAX_MARKETEX_XCELL5 * _MAX_MARKETEX_YCELL2; ++i )
	{
		if( PtInRect( &mRectItems5x2[ i ], ptMouse ) )
		{
			mnSelectItem = i;
		}
	}

	// 마우스 클릭시 에디트 박스 포커스 처리
	if( PtInRect( &mRectSearch, ptMouse) )
	{
		MoveWindow( g_xChatEditBox.GetSafehWnd(),
			g_xMainWnd.m_rcWindow.left + mRectSearch.left, g_xMainWnd.m_rcWindow.top + mRectSearch.top,
			mRectSearch.right - mRectSearch.left, 15, TRUE );

		SendMessage( g_xChatEditBox.GetSafehWnd(), EM_SETPASSWORDCHAR, NULL, 0 );
		SetWindowText( g_xChatEditBox.GetSafehWnd(), "" );
		SetFocus( g_xChatEditBox.GetSafehWnd() );
		ShowWindow( g_xChatEditBox.GetSafehWnd(), SW_SHOW );
		g_xChatEditBox.SetHanguelMode();
		g_xChatEditBox.SetEnterUse( FALSE );
		mbUseSearch = TRUE;
	}	

	return FALSE;
}

BOOL
CMarketExWnd::OnLButtonUp( LPCOMMONITEMSET lpCommonItemSet, POINT ptMouse )
{
	// return TRUE 하면 창이 닫혀 버린다

	if( mBtnWeapon.OnLButtonUp( ptMouse ) )
	{
		SetAlignMarketExItemList( MI_ALIGN_WEAPON );
		return FALSE;
	}
	
	if( mBtnCloth.OnLButtonUp( ptMouse ) )
	{
		SetAlignMarketExItemList( MI_ALIGN_CLOTH);
		return FALSE;
	}

	if( mBtnEquip.OnLButtonUp( ptMouse ) )
	{
		SetAlignMarketExItemList( MI_ALIGN_EQUIP );
		return FALSE;
	}

	if( mBtnSkill.OnLButtonUp( ptMouse ) )
	{
		SetAlignMarketExItemList( MI_ALIGN_SKILL );
		return FALSE;
	}

	if( mBtnEtc.OnLButtonUp( ptMouse ) )
	{
		SetAlignMarketExItemList( MI_ALIGN_ETC );
		return FALSE;
	}

	// 구매
	if( mBtnBuy.OnLButtonUp( ptMouse ) )
	{
		LPCLIENTSELLITEM pstMarketItem = NULL;
		CListNode< CLIENTSELLITEM > *pNode;
		INT nListCnt;
		for( pNode = mItemList.GetHead(), nListCnt = 0; pNode; pNode = pNode->GetNext(), ++nListCnt )
		{
			if( nListCnt == mnSelectItem )
			{
				pstMarketItem = pNode->GetData();
				if( pstMarketItem->nSellPrice > g_xGameProc.m_xMyHero.m_nPoint )
				{
					g_xGameProc.m_xGameMsgBox.CreateMsgBox(
						&g_xGameProc.m_xImage.m_xImageList[ _IMAGE_INTER ], _WND_ID_NOTENOUGH, _OK, g_xMsg.GetMsg( 7116 ) );
				}
				else
				{
					g_xGameProc.m_xGameMsgBox.CreateMsgBox(
						&g_xGameProc.m_xImage.m_xImageList[ _IMAGE_INTER ], _WND_ID_WANTTOBUY_MARKETEX, _YESNO, g_xMsg.GetMsg( 4415 ) );
				}
			}
		}

		return FALSE;
	}

	// 선물
	if( mBtnPresent.OnLButtonUp( ptMouse ) )
	{
		LPCLIENTSELLITEM pstMarketItem = NULL;
		CListNode< CLIENTSELLITEM > *pNode;
		INT nListCnt;
		for( pNode = mItemList.GetHead(), nListCnt = 0; pNode; pNode = pNode->GetNext(), ++nListCnt )
		{
			if( nListCnt == mnSelectItem )
			{
				pstMarketItem = pNode->GetData();
				if( pstMarketItem->nSellPrice > g_xGameProc.m_xMyHero.m_nPoint )
				{
					g_xGameProc.m_xGameMsgBox.CreateMsgBox(
						&g_xGameProc.m_xImage.m_xImageList[ _IMAGE_INTER ], _WND_ID_NOTENOUGH, _OK, g_xMsg.GetMsg( 7116 ) );
				}
				else
				{
					// Msg 를 선물용 멘트로 바꾸어야 한다
					g_xGameProc.m_xGameMsgBox.CreateMsgBox(
						&g_xGameProc.m_xImage.m_xImageList[ _IMAGE_INTER ], _WND_ID_WANTTOPRESENT_MARKETEX, _YESNO, g_xMsg.GetMsg( 7117 ), TRUE );
				}
			}
		}

		return FALSE;
	}

	if( mBtnCancel.OnLButtonUp( ptMouse ) )		{ return FALSE; }

	if( mBtnPrev.OnLButtonUp( ptMouse ) )
	{
		--mnCurPage;
		if( mnCurPage < 1 ) mnCurPage = 1;
		SetMarketExItemList( mnCurPage, mnTotalPage );

		return FALSE;
	}

	if( mBtnNext.OnLButtonUp( ptMouse ) )
	{
		++mnCurPage;
		if( mnCurPage > mnTotalPage ) mnCurPage = mnTotalPage;
		SetMarketExItemList( mnCurPage, mnTotalPage );

		return FALSE;
	}
	
	if( mBtnClose.OnLButtonUp( ptMouse ) )
	{
		CloseMarketExWnd();
		return FALSE;
	}
	
	if( mBtnPrice.OnLButtonUp( ptMouse ) )
	{
		++mbPriceValue;
		if( mbPriceValue == ( BYTE )MAX_MI_ALIGN_PRICE )		mbPriceValue = ( BYTE )MI_ALIGN_PRICE_UPPER;
		SetAlignItemListFromPrice( ( ALIGN_MARKETEX_ITEM_PRICE )mbPriceValue );
		return FALSE;
	}

	if( mBtnItem.OnLButtonUp( ptMouse ) )
	{
		/*
		//-- sex
		++mbSexValue;
		if( mbSexValue == ( BYTE )MAX_MI_ALIGN_SEX )		mbSexValue = ( BYTE )MI_ALIGN_SEX_COMMON;
		else if( mbSexValue > ( BYTE )MI_ALIGN_SEX_COMMON ) mbSexValue = ( BYTE )MI_ALIGN_SEX_MALE;
		SetAlignItemListFromSex( ( ALIGN_MARKETEX_ITEM_SEX ) mbSexValue );
		*/

		++mbItemValue;
		if( mbItemValue == ( BYTE )MAX_MI_ALIGN )			mbItemValue = ( BYTE )MI_ALIGN_WEAPON;
		SetAlignItemListFromItem( ( ALIGN_MARKETEX_ITEM )mbItemValue );
		return FALSE;
	}

	if( mBtnJob.OnLButtonUp( ptMouse ) )
	{ 
		++mbJobValue;
		if( mbJobValue == ( BYTE )MAX_MI_ALIGN_JOB )		mbJobValue = ( BYTE )MI_ALIGN_JOB_COMMON;
		else if( mbJobValue > ( BYTE )MI_ALIGN_JOB_COMMON ) mbJobValue = ( BYTE )MI_ALIGN_JOB_JUNSA;
		SetAlignItemListFromJob( ( ALIGN_MARKETEX_ITEM_JOB ) mbJobValue );
		return FALSE;
	}

	// 찾기
	if( mBtnSearch.OnLButtonUp( ptMouse ) )
	{
		if( mbUseSearch )
		{
			FindItems();
			mbUseSearch = FALSE; // - 다른 정렬을 누르게 되면!
		}
		
		return FALSE;
	}

	return FALSE;
}

BOOL
CMarketExWnd::OnMouseMove( POINT ptMouse )
{
	mBtnWeapon.OnMouseMove( ptMouse );
	mBtnCloth.OnMouseMove( ptMouse );
	mBtnEquip.OnMouseMove( ptMouse );
	mBtnSkill.OnMouseMove( ptMouse );
	mBtnEtc.OnMouseMove( ptMouse );

	mBtnBuy.OnMouseMove( ptMouse );
	mBtnPresent.OnMouseMove( ptMouse );
	mBtnCancel.OnMouseMove( ptMouse );
	
	mBtnPrev.OnMouseMove( ptMouse );
	mBtnNext.OnMouseMove( ptMouse );
	mBtnClose.OnMouseMove( ptMouse );
	
	mBtnPrice.OnMouseMove( ptMouse );
	mBtnItem.OnMouseMove( ptMouse );
	mBtnJob.OnMouseMove( ptMouse );
	
	mBtnSearch.OnMouseMove( ptMouse );

	// 아이템
	for( INT i = 0; i < _MAX_MARKETEX_XCELL5 * _MAX_MARKETEX_YCELL2; ++i )
	{
		if( PtInRect( &mRectItems5x2[ i ], ptMouse ) )
		{
			mnMouseLocated = i;
			return FALSE;
		}
	}

	return FALSE;
}

BOOL
CMarketExWnd::OnKeyDown( WPARAM wParam, LPARAM lParam )
{
	switch( wParam )
	{
	case VK_RETURN:
		{
			if( mbUseSearch )
			{
				FindItems();
				mbUseSearch = FALSE;
				return TRUE;
			}
		}
	}

	return FALSE;
}

VOID
CMarketExWnd::OnScrollDown()
{
	--mnSelectItem;
	if( mnSelectItem < 0 ) mnSelectItem = 0;
}

VOID
CMarketExWnd::OnScrollUp()
{
	++mnSelectItem;
	if( mnSelectItem > _MAX_MARKETEX_XCELL5 * _MAX_MARKETEX_YCELL2 - 1 )
		mnSelectItem = _MAX_MARKETEX_XCELL5 * _MAX_MARKETEX_YCELL2 - 1;
}

#endif
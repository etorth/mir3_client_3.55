#include "stdAfx.h"

// exclude file from build

/*

// GameOverWnd
CTestWnd::CTestWnd()
{
	Init();
}

CTestWnd::~CTestWnd()
{
	Destroy();
}

VOID
CTestWnd::Init()
{
	CGameWnd::Init();

	m_BtnClose.Init();
	m_BtnLogout.Init();
	m_BtnExit.Init();
	
	m_iChildLeftOffset = 0;
	m_iChildRightOffset = 0;
	m_iChildUpOffset = 0;
	m_iChildDownOffset = 0;
	m_iChildStartXOffset = 0;
	m_iChildStartYOffset = 0;
	memset( m_strChildPosInfo, 0, 260 );

	m_iStartX = 0;
	m_iStartY = 0;
	m_iWidth = 0;
	m_iHeight = 0;
	memset( m_strParentPosInfo, 0, 260 );
}

VOID
CTestWnd::Destroy()
{
	CGameWnd::Destroy();

	m_BtnClose.Destroy();
	m_BtnLogout.Destroy();
	m_BtnExit.Destroy();
}

VOID
CTestWnd::CreateTestWnd( 
					INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx,
					INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend )
{
	m_iStartX = nStartX;
	m_iStartY = nStartY;
	m_iWidth = nWidth;
	m_iHeight = nHeight;
	
	CGameWnd::CreateGameWnd( nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight, bBlend );

	m_BtnClose.CreateGameBtn( pxWndImage, 1221, 1222, nStartX, nStartY, g_xMsg.GetMsg( 1052 ), _BTN_TYPE_FOCUS, 1221, TRUE );
	m_BtnLogout.CreateGameBtn( pxWndImage, 411, 411, nStartX, nStartY, NULL, _BTN_TYPE_FOCUS, 411, TRUE );
	m_BtnExit.CreateGameBtn( pxWndImage, 411, 411, nStartX, nStartY, NULL, _BTN_TYPE_FOCUS, 411, TRUE );
}

VOID
CTestWnd::ShowTestWnd()
{
	CGameWnd::CreateGameWnd( m_nID, m_pxWndImage, m_nFrameImgIdx, m_bCanMove, m_iStartX, m_iStartY, m_iWidth, m_iHeight, 3 );

	GetChildPosInfo();
	GetParentPosInfo();

	ShowGameWnd();

	m_BtnClose.ChangeRect( m_rcWnd.left + 201, m_rcWnd.top + 59 );
	m_BtnClose.ShowGameBtn();

	m_BtnExit.ChangeRect( m_rcWnd.left + 114, m_rcWnd.top + 67 );
	m_BtnExit.ShowGameBtn();

	m_BtnLogout.ChangeRect( m_rcWnd.left + 23, m_rcWnd.top + 67 );
	m_BtnLogout.ShowGameBtn();

	CHAR pszTemp[ MAX_PATH ];
	RECT rcBtnName =
	{
		m_rcWnd.left + 20, m_rcWnd.top + 29,
		m_rcWnd.left + 230, m_rcWnd.top + 45,
	};

	sprintf( pszTemp, g_xMsg.GetMsg( 3500 ) );
	g_xMainWnd.PutsHan( NULL, rcBtnName, RGB( 255, 255, 255 ), RGB( 0, 0, 0 ), pszTemp );

	sprintf(pszTemp, g_xMsg.GetMsg(3501));
	SetRect(&rcBtnName, m_rcWnd.left+22, m_rcWnd.top+69, m_rcWnd.left+92, m_rcWnd.top+88);
	g_xMainWnd.PutsHan(NULL, rcBtnName, RGB(255, 150, 0), RGB(0, 0, 0), pszTemp);

	sprintf(pszTemp, g_xMsg.GetMsg(3502));
	SetRect(&rcBtnName, m_rcWnd.left+114, m_rcWnd.top+69, m_rcWnd.left+183, m_rcWnd.top+88);
	g_xMainWnd.PutsHan(NULL, rcBtnName, RGB(255, 150, 0), RGB(0, 0, 0), pszTemp);

}

BOOL
CTestWnd::OnLButtonDown( POINT ptMouse )
{
	if( m_BtnClose.OnLButtonDown( ptMouse ) )	return TRUE;
	if( m_BtnLogout.OnLButtonDown( ptMouse ) )	return TRUE;
	if( m_BtnExit.OnLButtonDown( ptMouse ) )	return TRUE;

	return FALSE;
}

BOOL
CTestWnd::OnLButtonUp( POINT ptMouse )
{
	if( m_BtnClose.OnLButtonUp( ptMouse ) )		return TRUE;
	if( m_BtnLogout.OnLButtonUp( ptMouse ) )	return TRUE;
	if( m_BtnExit.OnLButtonUp( ptMouse ) )		return TRUE;

	return FALSE;
}

VOID
CTestWnd::OnMouseMove( POINT ptMouse )
{
	m_BtnClose.OnMouseMove( ptMouse );
	m_BtnLogout.OnMouseMove( ptMouse );
	m_BtnExit.OnMouseMove( ptMouse );
}

VOID
CTestWnd::MoveTestWnd( POINT ptMouse )
{
	CGameWnd::MoveGameWnd( ptMouse );

	m_iStartX = m_rcWnd.left;
	m_iStartY = m_rcWnd.top;
}

CHAR*
// 자식 윈도우의 부모윈도우 시작 위치에 대한 상대위치가 저장된 정보를 생성, 리턴
CTestWnd::GetChildPosInfo()
{
	if( GetAsyncKeyState( VK_LEFT ) )		m_iChildLeftOffset -= 1;
	if( GetAsyncKeyState( VK_RIGHT ) )		m_iChildRightOffset += 1;
	if( GetAsyncKeyState( VK_UP ) )			m_iChildUpOffset -= 1;
	if( GetAsyncKeyState( VK_DOWN ) )		m_iChildDownOffset += 1;

	m_iChildStartXOffset = m_iChildLeftOffset + m_iChildRightOffset;
	m_iChildStartYOffset = m_iChildUpOffset + m_iChildDownOffset;

	// 자식 윈도우 정보
	sprintf( m_strChildPosInfo, " # Child Window Info : %d %d\0", m_iChildStartXOffset, m_iChildStartYOffset );
	g_xMainWnd.PutsHan( NULL, 10, 10, RGB(200, 225, 250), RGB(0, 0, 0), m_strChildPosInfo );

	return m_strChildPosInfo;
}

CHAR*
// 부모 윈도우의 시작 위치가 저장된 정보를 생성, 리턴
CTestWnd::GetParentPosInfo()
{
	if( GetAsyncKeyState( VK_NUMPAD4 ) )	m_iStartX -= 1;
	if( GetAsyncKeyState( VK_NUMPAD6 ) )	m_iStartX += 1;
	if( GetAsyncKeyState( VK_NUMPAD8 ) )	m_iStartY -= 1;
	if( GetAsyncKeyState( VK_NUMPAD2 ) )	m_iStartY += 1;

	// 부모 윈도우 정보
	sprintf( m_strParentPosInfo, " # Parent Window Info : %d %d\0", m_iStartX, m_iStartY );
	g_xMainWnd.PutsHan( NULL, 10, 50, RGB(200, 225, 250), RGB(0, 0, 0), m_strParentPosInfo );

	return m_strParentPosInfo;
}










// InventoryWnd
CTestWnd::CTestWnd()
{
	Init();
}

CTestWnd::~CTestWnd()
{
	Destroy();
}

VOID
CTestWnd::Init()
{
	CGameWnd::Init();

	memset( m_iisInventoryItem, -1, sizeof( INVENITEMSET ) * MAX_INVENTORY_CELL );

	m_BtnClose.Init();
	m_ScrlBar.Init();
	m_iFstLine = 0;
	m_iCurrentCellNum = -1;

	m_iChildLeftOffset = 0;
	m_iChildRightOffset = 0;
	m_iChildUpOffset = 0;
	m_iChildDownOffset = 0;
	m_iChildStartXOffset = 0;
	m_iChildStartYOffset = 0;
	memset( m_strChildPosInfo, 0, 260 );

	m_iStartX = 0;
	m_iStartY = 0;
	m_iWidth = 0;
	m_iHeight = 0;
	memset( m_strParentPosInfo, 0, 260 );
}

VOID
CTestWnd::Destroy()
{
	CGameWnd::Destroy();

	m_BtnClose.Destroy();
}

VOID
CTestWnd::CreateTestWnd( 
					INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx,
					INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend )
{
	m_iStartX = nStartX;
	m_iStartY = nStartY;
	m_iWidth = nWidth;
	m_iHeight = nHeight;
	
	CGameWnd::CreateGameWnd( nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight, bBlend );

	m_BtnClose.CreateGameBtn( pxWndImage, 1221, 1222, nStartX, nStartY, g_xMsg.GetMsg( 1052 ), _BTN_TYPE_FOCUS, 1221, TRUE );

	m_ScrlBar.CreateScrlBar( pxWndImage, 154, SHOW_INVENTORY_CELL, 12, 278, 14 );
}

VOID
CTestWnd::ShowTestWnd()
{
	//CGameWnd::CreateGameWnd( m_nID, m_pxWndImage, m_nFrameImgIdx, m_bCanMove, m_iStartX, m_iStartY, m_iWidth, m_iHeight, 3 );

	GetChildPosInfo();
	GetParentPosInfo();

	ShowGameWnd();

	m_BtnClose.ChangeRect( m_rcWnd.left + 235, m_rcWnd.top + 416 );
	m_BtnClose.ShowGameBtn();

	// 남아있는 갯수 92개, 총 100개, 보이는것 8개
	m_ScrlBar.ShowScrlBar( m_rcWnd.left + 257, m_rcWnd.top + 70, m_iFstLine, MAX_INVENTORY_CELL - SHOW_INVENTORY_CELL );

	ShowInventoryItem();
}

BOOL
CTestWnd::OnLButtonDown( LPCOMMONITEMSET pCommonItemSet, POINT ptMouse )
{
	if( m_BtnClose.OnLButtonDown( ptMouse ) ) return TRUE;
	if( m_ScrlBar.OnLButtonDown( ptMouse ) )
	{
		// 남아있는 갯수 92 개
		FLOAT fScrlRate = m_ScrlBar.GetScrlRate();
		m_iFstLine = ( INT )( ( MAX_INVENTORY_CELL - SHOW_INVENTORY_CELL ) * fScrlRate );
		
		return TRUE;
	}

	m_iCurrentCellNum = GetInvenItemNum( ptMouse );

	if( m_iCurrentCellNum != -1 )
	{
		SetItemToInvenFromCommon( pCommonItemSet );
	}
	
	return FALSE;
}

BOOL
CTestWnd::OnLButtonUp( POINT ptMouse )
{
	if( m_BtnClose.OnLButtonUp( ptMouse ) )		return TRUE;
	if( m_ScrlBar.OnLButtonUp( ptMouse ) )		return FALSE;

	return FALSE;
}

BOOL
CTestWnd::OnMouseMove( POINT ptMouse )
{
	m_BtnClose.OnMouseMove( ptMouse );
	
	if( m_ScrlBar.OnMouseMove( ptMouse ) )
	{
		FLOAT fScrlRate = m_ScrlBar.GetScrlRate();
		m_iFstLine = ( INT )( ( MAX_INVENTORY_CELL - SHOW_INVENTORY_CELL ) * fScrlRate );
	}

	return FALSE;
}

VOID
CTestWnd::MoveTestWnd( POINT ptMouse )
{
	CGameWnd::MoveGameWnd( ptMouse );

	m_iStartX = m_rcWnd.left;
	m_iStartY = m_rcWnd.top;
}

VOID
CTestWnd::OnScrollDown()
{
	if( m_iFstLine > 0 ) --m_iFstLine;
}

VOID
CTestWnd::OnScrollUp()
{
	// 보이는것은 8개
	// 총 100개
	// m_iFstLine 은 0 에서 91 까지
	if( m_iFstLine < MAX_INVENTORY_CELL - SHOW_INVENTORY_CELL - 1 ) ++m_iFstLine;
}

INT
// 마우스 포인터에 해당하는 아이템을 가져온다
CTestWnd::GetInvenItemNum( POINT ptMouse )
{
	INT iCurrCell = GetInvenCellNum( ptMouse );

	return iCurrCell;

//	if( iCurrCell != -1 && m_iisInventoryItem[ iCurrCell ] != -1 )
//		return iCurrCell;

//	return -1;
}

INT
// 마우스 포인터에 해당하는 아이템의 인덱스를 가져온다
CTestWnd::GetInvenCellNum( POINT ptMouse )
{
	// 인벤토리 안의 아이템이 들어갈 수 있는 영역을 설정한다
	RECT rc;
	SetRect( &rc,
		m_rcWnd.left + INVENTORY_ITEM_STARTX, m_rcWnd.top + INVENTORY_ITEM_STARTY,
		m_rcWnd.left + INVENTORY_ITEM_STARTX + ITEM_CELL_WIDTH * ( INVENTORY_ITEM_XNUM + 1 ),
		m_rcWnd.top + INVENTORY_ITEM_STARTY + ITEM_CELL_HEIGHT * ( INVENTORY_ITEM_YNUM + 1 ) );

	// 인벤토리 안의 아이템이 들어갈 수 있는 영역 안에 마우스 포인터가 위치한다면
	if( PtInRect( &rc, ptMouse ) )
	{
		for( INT y = 0; y < INVENTORY_ITEM_YNUM; ++y )
		{
			for( INT x = 0; x < INVENTORY_ITEM_XNUM; ++x )
			{
				// 각 아이템 영역의 시작위치를 계산한다
				INT iSX = m_rcWnd.left + INVENTORY_ITEM_STARTX + ( x * ITEM_CELL_WIDTH );
				INT iSY = m_rcWnd.top + INVENTORY_ITEM_STARTY + ( y * ITEM_CELL_HEIGHT );

				// 각 아이템의 영역정보를 세팅한다
				SetRect( &rc, iSX, iSY, iSX + ITEM_CELL_WIDTH, iSY + ITEM_CELL_HEIGHT );

				// 해당 아이템의 영역안에 마우스 포인터가 위치한다면
				if( PtInRect( &rc, ptMouse ) )
				{
					// 인벤토리 아이템의 인덱스를 리턴한다
					return x + ( ( m_iFstLine + y ) * INVENTORY_ITEM_XNUM );
				}
			}
		}
	}

	return -1;
}

INT
// 비어있는 인벤토리 인덱스를 가져온다
CTestWnd::GetEmptyInvenNum()
{
	for( INT i = 0; i < MAX_INVENTORY_CELL; ++i )
	{
		if( m_iisInventoryItem[ i ].bSetted == FALSE ) return i;
	}

	return -1;
}

BOOL
// 마우스에 장착되어 있는 아이템을 인벤토리 클릭한 위치에 장착한다
CTestWnd::SetItemToInvenFromCommon( LPCOMMONITEMSET pCommonItemSet )
{
	if( pCommonItemSet->bSetted == TRUE &&
		m_iisInventoryItem[ m_iCurrentCellNum ].bSetted == -1 )
	{
		if( CanItemInsertToInventory( pCommonItemSet ) )
		{
			AddItemToInventory( pCommonItemSet );

			// 사운드 플레이
			g_xGameProc.m_xInterface.ItemClickSound( &pCommonItemSet->xItem );

			return TRUE;
		}
	}

	return FALSE;
}

BOOL
// 인벤토리에 아이템을 넣을 수 있는가?
CTestWnd::CanItemInsertToInventory( LPCOMMONITEMSET pCommonItemSet )
{
	// 여기서 아이템이 차지하는 셀의 크기에 따라서 남아있는 인벤토리의 영역에
	// 맞게 들어갈 것인가를 체크해야 한다

	//return FALSE;

	return TRUE;
}

VOID
// 선택된 인벤토리 아이템의 인덱스 위치에 아이템을 추가한다
CTestWnd::AddItemToInventory( LPCOMMONITEMSET pCommonItemSet )
{
	INT nCellWidth = 0;
	INT nCellHeight = 0;

	CWHWilImageData* pxItemImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_INVENTORY];
	if( pxItemImg->NewSetIndex( pCommonItemSet->xItem.m_stItemInfo.stStdItem.wLooks ) )
	{
		nCellWidth = pxItemImg->m_lpstNewCurrWilImageInfo->shWidth / ITEM_CELL_WIDTH;
		if ( pxItemImg->m_lpstNewCurrWilImageInfo->shWidth % ITEM_CELL_WIDTH )
			nCellWidth++;

		nCellHeight = pxItemImg->m_lpstNewCurrWilImageInfo->shHeight/(ITEM_CELL_HEIGHT);
		if ( pxItemImg->m_lpstNewCurrWilImageInfo->shHeight % (ITEM_CELL_HEIGHT) )
			nCellHeight++;
	}

	m_iisInventoryItem[ m_iCurrentCellNum ].bSetted = TRUE;
	m_iisInventoryItem[ m_iCurrentCellNum ].nWidth = nCellWidth;
	m_iisInventoryItem[ m_iCurrentCellNum ].nHeight = nCellHeight;
	memcpy( &m_iisInventoryItem[ m_iCurrentCellNum ].xItem, &pCommonItemSet->xItem, sizeof( CItem ) );
}


VOID
// 인벤토리 아이템 보이기
CTestWnd::ShowInventoryItem()
{
	RECT rc;
	INT iIndex = 0;
	
	for( INT y = m_iFstLine; y < m_iFstLine + INVENTORY_ITEM_YNUM; ++y )
	{
		for( INT x = 0; x < INVENTORY_ITEM_XNUM; ++x )
		{
			iIndex = x + y * INVENTORY_ITEM_XNUM;

			if( m_iisInventoryItem[ iIndex ].bSetted != -1 )
			{
				INT iSX = m_rcWnd.left + INVENTORY_ITEM_STARTX + ( x * ITEM_CELL_WIDTH );
				INT iSY = m_rcWnd.top + INVENTORY_ITEM_STARTY + ( ( y - m_iFstLine ) * ITEM_CELL_HEIGHT );

				rc.left = iSX;
				rc.top = iSY;
				rc.right = iSX + ITEM_CELL_WIDTH * m_iisInventoryItem[ iIndex ].nWidth;
				rc.bottom = iSY + ITEM_CELL_HEIGHT * m_iisInventoryItem[ iIndex ].nHeight;

				CWHWilImageData* pItemImg = &g_xGameProc.m_xImage.m_xImageList[ _IMAGE_ITEM_INVENTORY ];

				WORD wColor = g_xMainWnd.ConvertColor24To16(
					RGB(
					m_iisInventoryItem[ iIndex ].xItem.m_stItemInfo.bLevel_R,
					LOBYTE( m_iisInventoryItem[ iIndex ].xItem.m_stItemInfo.wAmount_GB ),
					HIBYTE( m_iisInventoryItem[ iIndex ].xItem.m_stItemInfo.wAmount_GB ) )
					);

				// 현재 아이템의 룩업 테이블 인덱스를 세팅한다
				// 세팅가능하다면 진행 ( ? )
				if( pItemImg->NewSetIndex( m_iisInventoryItem[ iIndex ].xItem.m_stItemInfo.stStdItem.wLooks ) )
				{
					// 여기서 에러난다 왜?
					//g_xMainWnd.DrawWithImageForComp( iSX, iSY, &rc, ( WORD* )pItemImg->m_pbCurrImage, wColor );
				}
			}
		}
	}
}




CHAR*
// 자식 윈도우의 부모윈도우 시작 위치에 대한 상대위치가 저장된 정보를 생성, 리턴
CTestWnd::GetChildPosInfo()
{
	if( GetAsyncKeyState( VK_LEFT ) )		m_iChildLeftOffset -= 1;
	if( GetAsyncKeyState( VK_RIGHT ) )		m_iChildRightOffset += 1;
	if( GetAsyncKeyState( VK_UP ) )			m_iChildUpOffset -= 1;
	if( GetAsyncKeyState( VK_DOWN ) )		m_iChildDownOffset += 1;

	m_iChildStartXOffset = m_iChildLeftOffset + m_iChildRightOffset;
	m_iChildStartYOffset = m_iChildUpOffset + m_iChildDownOffset;

	// 자식 윈도우 정보
	sprintf( m_strChildPosInfo, " # Child Window Info : %d %d\0", m_iChildStartXOffset, m_iChildStartYOffset );
	g_xMainWnd.PutsHan( NULL, 10, 30, RGB(200, 225, 250), RGB(0, 0, 0), m_strChildPosInfo );

	// 스크롤 정보
	CHAR str[ MAX_PATH ];
	sprintf( str, " # ScrollBar Info : FstLine( %d )\0", m_iFstLine );
	g_xMainWnd.PutsHan( NULL, 10, 50, RGB(200, 225, 250), RGB(0, 0, 0), str );

	// 마우스로 클릭한 곳의 아이템 가방 인덱스
	sprintf( str, " # Clicked Inventory Index : %d\0", m_iCurrentCellNum );
	g_xMainWnd.PutsHan( NULL, 10, 70, RGB(200, 225, 250), RGB(0, 0, 0), str );
	
	return m_strChildPosInfo;
}

CHAR*
// 부모 윈도우의 시작 위치가 저장된 정보를 생성, 리턴
CTestWnd::GetParentPosInfo()
{
	if( GetAsyncKeyState( VK_NUMPAD4 ) )	m_iStartX -= 1;
	if( GetAsyncKeyState( VK_NUMPAD6 ) )	m_iStartX += 1;
	if( GetAsyncKeyState( VK_NUMPAD8 ) )	m_iStartY -= 1;
	if( GetAsyncKeyState( VK_NUMPAD2 ) )	m_iStartY += 1;

	// 부모 윈도우 정보
	sprintf( m_strParentPosInfo, " # Parent Window Info : %d %d\0", m_iStartX, m_iStartY );
	g_xMainWnd.PutsHan( NULL, 10, 10, RGB(200, 225, 250), RGB(0, 0, 0), m_strParentPosInfo );

	return m_strParentPosInfo;
}
 





*/
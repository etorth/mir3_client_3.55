/******************************************************************************************************************
                                                                                                                   
	¸ðµâ¸í:																											
																													
	ÀÛ¼ºÀÚ:																											
	ÀÛ¼ºÀÏ:																											
																													
	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤ ³»¿ë																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"

#define _BTN_POS_X  288
#define _BTN_POS_Y  12



/******************************************************************************************************************

	CStatusWnd Class

*******************************************************************************************************************/
/******************************************************************************************************************

	ÇÔ¼ö¸í : CStatusWnd::CStatusWnd()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : 
	Ãâ·Â   : 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
CStatusWnd::CStatusWnd()
{
	Init();
}



/******************************************************************************************************************

	ÇÔ¼ö¸í : CStatusWnd::~CStatusWnd()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : 
	Ãâ·Â   : 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
CStatusWnd::~CStatusWnd()
{
	Destory();
}


VOID CStatusWnd::Init()
{
	INT nCnt;
	CGameWnd::Init();

	m_bType	= _TYPE_EQUIP;
	m_nStartLineNum = 0;
	m_pstMyMagic = NULL;
	m_bMyMagicCnt = 0;
	ZeroMemory(&m_bMagicIdxTable, _MAX_MAGIC_SKILL);
	ZeroMemory(&m_rcCell, sizeof(RECT)*_EQUIP_MAX_CELL);
	ZeroMemory(&m_rcMagicCell, sizeof(RECT)*_MAGIC_MAX_CELL);
	ZeroMemory(&m_stEquipItem, sizeof(ITEMSET)*_EQUIP_MAX_CELL);
	ZeroMemory(&m_stTakeOnItemSet, sizeof(CItem));
	ZeroMemory(&m_szEquipItemIdx, sizeof(m_szEquipItemIdx));

	for ( nCnt  = 0; nCnt < _MAX_STAUTS_BTN; nCnt ++ )
	{
		m_xStatusBtn[nCnt].Init();
	}
	for ( nCnt  = 0; nCnt < 2; nCnt ++ )
	{
		m_xMagicScrlBtn[nCnt].Init();
	}

}

VOID CStatusWnd::Destory()
{
	CGameWnd::Destroy();
	SAFE_DELETE(m_pstMyMagic);
	Init();
}


/******************************************************************************************************************

	ÇÔ¼ö¸í : CStatusWnd::CreateStatusWnd()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : 
	ÀÔ·Â   : INT nID
	         CWHWilImageData* pxWndImage
	         INT nFrameImgIdx
	         INT nStartX
	         INT nStartY
	         INT nWidth
	         INT nHeight
	         BOOL bCanMove
	Ãâ·Â   : VOID 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
VOID CStatusWnd::CreateStatusWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove)
{
	CreateGameWnd(nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight, -92, -24);

	// ¹öÆ°ÃÊ±âÈ­.
	m_xStatusBtn[_BTN_ID_STATUSCLOSE].CreateGameBtn(pxWndImage,  1221,  1222, nStartX+_BTN_POS_X, nStartY+_BTN_POS_Y);
//	m_xStatusBtn[_BTN_ID_STATUS].CreateGameBtn(pxWndImage,  212,  213, nStartX+_BTN_ID_STATUS_X, nStartY+_BTN_ID_STATUS_Y);
//	m_xStatusBtn[_BTN_ID_STATUSMAGIC].CreateGameBtn(pxWndImage,  99, 100, nStartX+_BTN_ID_STATUSMAGIC_X, nStartY+_BTN_ID_STATUSMAGIC_Y);

	SetRect(&m_rcCell[_U_DRESS],		100,	100,	160,  210);//ÒÂ·þ 
	SetRect(&m_rcCell[_U_WEAPON],		50,		80,		 95,  170);//ÎäÆ÷
	SetRect(&m_rcCell[_U_RIGHTHAND],	90,		265,	90+_INVENTORY_CELL_WIDTH,	265+_INVENTORY_CELL_HEIGHT);//À¯Öò
	SetRect(&m_rcCell[_U_NECKLACE],		168,	88,		168+_INVENTORY_CELL_WIDTH,	88+_INVENTORY_CELL_HEIGHT);//ÏîÁ´
	SetRect(&m_rcCell[_U_HELMET],		115,	70,		135,  85);//Í·¿ø
	SetRect(&m_rcCell[_U_ARMRINGL],		10,		155,	10+_INVENTORY_CELL_WIDTH,	155+_INVENTORY_CELL_HEIGHT);//×ó±Û»·
	SetRect(&m_rcCell[_U_ARMRINGR],		168,	155,	168+_INVENTORY_CELL_WIDTH,	155+_INVENTORY_CELL_HEIGHT);//ÓÒ±Û»·
	SetRect(&m_rcCell[_U_RINGL],		10,		195,	10+_INVENTORY_CELL_WIDTH,	195+_INVENTORY_CELL_HEIGHT);//×óÖ¸»·
	SetRect(&m_rcCell[_U_RINGR],		168,	195,	168+_INVENTORY_CELL_WIDTH,	195+_INVENTORY_CELL_HEIGHT);//ÓÒÖ¸»·
	SetRect(&m_rcCell[_U_CHARM],		130,	265,	130+_INVENTORY_CELL_WIDTH,	265+_INVENTORY_CELL_HEIGHT);//·û
	SetRect(&m_rcCell[_U_SHOES],		10,		265,	10+_INVENTORY_CELL_WIDTH,	265+_INVENTORY_CELL_HEIGHT);//Ð¬


	// ¸¶¹ý¹öÆ°ÃÊ±âÈ­.
	m_xMagicScrlBtn[0].CreateGameBtn(pxWndImage, 74, 75, nStartX+232, nStartY+147);
	m_xMagicScrlBtn[1].CreateGameBtn(pxWndImage, 74, 75, nStartX+232, nStartY+253);

	// ¸¶¹ýÃ¢ÃÊ±âÈ­.
	SetRect(&m_rcMagicCell[0], 39,  77, 74, 112);
	SetRect(&m_rcMagicCell[1], 39, 115, 74, 149);
	SetRect(&m_rcMagicCell[2], 39, 152, 74, 186);
	SetRect(&m_rcMagicCell[3], 39, 188, 74, 223);
	SetRect(&m_rcMagicCell[4], 39, 225, 74, 260);

	// ¸¶¹ý º¯¼ö ÃÊ±âÈ­.
	m_pstMyMagic  = NULL;
	m_bMyMagicCnt = 0;
}



/******************************************************************************************************************

	ÇÔ¼ö¸í : CStatusWnd::ShowStatusWnd()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : 
	Ãâ·Â   : VOID 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
VOID CStatusWnd::ShowStatusWnd()
{
	RECT rcID;
	switch ( m_bType )
	{
	case _TYPE_EQUIP:
		ShowCharEquipWnd();//Equip-×°±¸
		SetRect(&rcID, m_rcWnd.left+170, m_rcWnd.top+38, m_rcWnd.left+300, m_rcWnd.top+50);
		g_xMainWnd.PutsHan(NULL, rcID, RGB(255, 250, 180), RGB(0, 0, 0), g_xGameProc.m_pMyHero->m_szName, NULL);
		
		rcID.top		+= 15;
		rcID.bottom		+= 15;

		g_xMainWnd.PutsHan(NULL, rcID, RGB(255, 250, 180), RGB(0, 0, 0), g_xGameProc.m_pMyHero->m_szGuildName, NULL);

		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(204) )
		{
			g_xMainWnd.DrawWithImageForComp(
											m_rcWnd.left+187, 
											m_rcWnd.top+266, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage));
		}


//		g_xMainWnd.DrawWithGDI(m_rcWnd, NULL, RGB(255, 250, 180), 1);

		break;
	case _TYPE_STATUS:
		//×°±¸
		ShowCharEquipWnd();
		//½ÇÉ«Ãû
		SetRect(&rcID, m_rcWnd.left+170, m_rcWnd.top+38, m_rcWnd.left+300, m_rcWnd.top+50);
		g_xMainWnd.PutsHan(NULL, rcID, RGB(255, 250, 180), RGB(0, 0, 0), g_xGameProc.m_pMyHero->m_szName, g_xMainWnd.CreateGameFont("±Ã¼­Ã¼", 10, 0, FW_BOLD));

		//×´Ì¬£¨ÎÄ×Ö£©
		ShowCharStatus();

		//ÕâÊÇÊ²Ã´£¿£¿
		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(203) )
		{
			g_xMainWnd.DrawWithImageForComp(
											m_rcWnd.left+187, 
											m_rcWnd.top+266, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage));
		}

//		g_xMainWnd.DrawWithGDI(m_rcWnd, NULL, RGB(255, 250, 180), 1);

		break;
	case _TYPE_SETMAGIC:
		ShowCharSetMagicWnd();
		SetRect(&rcID, m_rcWnd.left+81, m_rcWnd.top+38, m_rcWnd.left+173, m_rcWnd.top+50);
		g_xMainWnd.PutsHan(NULL, rcID, RGB(255, 250, 180), RGB(0, 0, 0), g_xGameProc.m_pMyHero->m_szName, g_xMainWnd.CreateGameFont("±Ã¼­Ã¼", 10, 0, FW_BOLD));
		break;
	}

	m_xStatusBtn[_BTN_ID_STATUSCLOSE].ShowGameBtn();
//	m_xStatusBtn[_BTN_ID_STATUS].ShowGameBtn();
//	m_xStatusBtn[_BTN_ID_STATUSMAGIC].ShowGameBtn();
}



/******************************************************************************************************************

	ÇÔ¼ö¸í : CStatusWnd::SetStatusBtnInit()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : 
	Ãâ·Â   : VOID 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
VOID CStatusWnd::SetStatusBtnInit()
{
	m_xStatusBtn[_BTN_ID_STATUSCLOSE].SetBtnState(_BTN_STATE_NORMAL);
//	m_xStatusBtn[_BTN_ID_STATUS].SetBtnState(_BTN_STATE_NORMAL);
//	m_xStatusBtn[_BTN_ID_STATUSMAGIC].SetBtnState(_BTN_STATE_NORMAL);
}











/******************************************************************************************************************

	Ä³¸¯ÅÍ ÀåÂøÃ¢°ü·Ã.

*******************************************************************************************************************/
/******************************************************************************************************************

	ÇÔ¼ö¸í : CStatusWnd::ShowCharEquipWnd()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : 
	Ãâ·Â   : VOID 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
VOID CStatusWnd::ShowCharEquipWnd()
{
	INT nStartX, nStartY;

	ShowGameWnd();

	// ÏÔÊ¾ÄÐÅ®ÈËÎï
	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].NewSetIndex(g_xGameProc.m_pMyHero->m_stFeature.bGender) )
	{
		g_xMainWnd.DrawWithImageForComp(
						m_rcWnd.left+_EQUIP_CHAR_X+g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shPX, 
						m_rcWnd.top+_EQUIP_CHAR_Y+g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shPY, 
						g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shWidth, 
						g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shHeight,
						(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_pbCurrImage));
	}

	// ÎïÆ·.
	for ( INT nCnt = 0; nCnt < _EQUIP_MAX_CELL; nCnt++ )
	{
		if ( m_stEquipItem[nCnt].bSetted )
		{
			if ( nCnt!=_U_HELMET && nCnt!=_U_WEAPON && nCnt!=_U_DRESS )
			{
				nStartX = m_rcWnd.left+m_rcCell[nCnt].left;
				nStartY = m_rcWnd.top+m_rcCell[nCnt].top;

				m_stEquipItem[nCnt].xItem.DrawItem(nStartX, nStartY);
			}
			else
			{
				//ÒÂ·þºÍÍ·¿ø
				nStartX = m_rcWnd.left+_EQUIP_CHAR_X;
				nStartY = m_rcWnd.top+_EQUIP_CHAR_Y;

				m_stEquipItem[nCnt].xItem.DrawItem(nStartX, nStartY, _ITEM_TYPE_EQUIP);
			}
		}
		//for debug
		RECT rc;
		INT l = m_rcWnd.left + m_rcCell[nCnt].left;
		INT	t = m_rcWnd.top + m_rcCell[nCnt].top;
		INT	r = m_rcWnd.left + m_rcCell[nCnt].right;
		INT	b = m_rcWnd.top + m_rcCell[nCnt].bottom;
		SetRect(&rc, l, t, r, b);
		g_xMainWnd.DrawWithGDI(rc, NULL, RGB(0, 0, 255), 1);
		CHAR szNum[8];
		sprintf( szNum, "%d", nCnt );
		g_xMainWnd.PutsHan(NULL, rc, RGB(255,0,0), 0, szNum);

	}

	//×°±¸tool tip
	ShowEquipItemState();
}



/******************************************************************************************************************

	ÇÔ¼ö¸í : CStatusWnd::ShowEquipItemState()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : 
	Ãâ·Â   : VOID 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
VOID CStatusWnd::ShowEquipItemState()
{
	INT nEquipNum = GetEquipNum(g_xGameProc.m_ptMousePos);

	if ( nEquipNum != -1 )
	{
		if ( m_stEquipItem[nEquipNum].bSetted )
		{
			m_stEquipItem[nEquipNum].xItem.ShowItemStatus(m_rcWnd.left+37, m_rcWnd.top+288);
		}		
	}
}



/******************************************************************************************************************

	ÇÔ¼ö¸í : CStatusWnd::GetEquipNum()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : 
	ÀÔ·Â   : POINT ptMouse
	Ãâ·Â   : INT 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
INT CStatusWnd::GetEquipNum(POINT ptMouse)
{
	RECT rc;
	for ( INT nCnt = 0; nCnt < _EQUIP_MAX_CELL; nCnt++ )
	{
		SetRect(&rc, m_rcWnd.left+m_rcCell[nCnt].left, m_rcWnd.top+m_rcCell[nCnt].top, 
			    m_rcWnd.left+m_rcCell[nCnt].left+(m_rcCell[nCnt].right-m_rcCell[nCnt].left), m_rcWnd.top+m_rcCell[nCnt].top+(m_rcCell[nCnt].bottom-m_rcCell[nCnt].top));
		if ( PtInRect(&rc, ptMouse) )
		{
			return nCnt;
		}
	}

	return -1;
}



/******************************************************************************************************************

	ÇÔ¼ö¸í : CStatusWnd::CheckEquipItem()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : 
	ÀÔ·Â   : CItem* pxItem
	         BYTE bEquipCell
	         POINT ptMouse
	Ãâ·Â   : BOOL 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
BOOL CStatusWnd::CheckEquipItem(CItem* pxItem, BYTE bEquipCell, POINT ptMouse)
{
	RECT rc;

	for ( INT nCnt = 0; nCnt < _EQUIP_MAX_CELL; nCnt++ )
	{
		SetRect(&rc, m_rcWnd.left+m_rcCell[nCnt].left, m_rcWnd.top+m_rcCell[nCnt].top, 
			    m_rcWnd.left+m_rcCell[nCnt].left+(m_rcCell[nCnt].right-m_rcCell[nCnt].left), m_rcWnd.top+m_rcCell[nCnt].top+(m_rcCell[nCnt].bottom-m_rcCell[nCnt].top));
		if ( PtInRect(&rc, ptMouse) )
		{
			if ( pxItem->m_bAttr == _U_ARMRINGL || pxItem->m_bAttr == _U_ARMRINGR )
			{
				if ( pxItem->m_stItemInfo.stStdItem.bStdMode == 25 )
				{
					if ( _U_ARMRINGL == bEquipCell )
						return TRUE;
				}
				else
				{
					if ( _U_ARMRINGL == bEquipCell || _U_ARMRINGR == bEquipCell )			return TRUE;
				}
			}
			else if ( pxItem->m_bAttr == _U_RINGL || pxItem->m_bAttr ==  _U_RINGR )
			{
				if ( _U_RINGL == bEquipCell || _U_RINGR == bEquipCell )					return TRUE;
			}
			else if ( pxItem->m_bAttr == bEquipCell )
			{
				return TRUE;
			}		
			else if ( pxItem->m_bAttr == bEquipCell)
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}



/******************************************************************************************************************

	ÇÔ¼ö¸í : CStatusWnd::DeleteEquipItem()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : 
	ÀÔ·Â   : INT nEquipNum
	Ãâ·Â   : VOID 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
VOID CStatusWnd::DeleteEquipItem(INT nEquipNum)
{
	ZeroMemory(&m_stEquipItem[nEquipNum], sizeof(ITEMSET));
}



VOID CStatusWnd::DeleteEquipItem(INT nMakeIndex, CHAR* szName)
{
	for ( INT nCnt = 0; nCnt < _EQUIP_MAX_CELL; nCnt++ )
	{
		if ( m_stEquipItem[nCnt].bSetted )
		{
			if ( m_stEquipItem[nCnt].xItem.m_stItemInfo.nMakeIndex == nMakeIndex )
			{
				if ( !strcmp(m_stEquipItem[nCnt].xItem.m_stItemInfo.stStdItem.szName, szName) )
				{
					DeleteEquipItem(nCnt);
					break;
				}
			}
		}		
	}
}



/******************************************************************************************************************

	ÇÔ¼ö¸í : CStatusWnd::DeleteAllEquipItem()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : 
	Ãâ·Â   : VOID 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
VOID CStatusWnd::DeleteAllEquipItem()
{
	for ( INT nCnt = 0; nCnt < _EQUIP_MAX_CELL; nCnt++ )
	{
		ZeroMemory(&m_stEquipItem[nCnt], sizeof(ITEMSET));
	}
}



/******************************************************************************************************************

	ÇÔ¼ö¸í : CStatusWnd::AddEquipItem()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : 
	ÀÔ·Â   : CItem xItem
	         INT nEquipNum
	         BOOL bUseEquipNum
	Ãâ·Â   : BOOL 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
BOOL CStatusWnd::AddEquipItem(CItem xItem, INT nEquipNum, BOOL bUseEquipNum)
{
	if ( bUseEquipNum )
	{
		if ( !m_stEquipItem[nEquipNum].bSetted )
		{
			m_stEquipItem[nEquipNum].bSetted = TRUE;
			m_stEquipItem[nEquipNum].xItem = xItem;
			m_stEquipItem[nEquipNum].xItem.m_shCellNum = nEquipNum;

			return TRUE;
		}
	}

	for ( INT nCnt = 0; nCnt < _EQUIP_MAX_CELL; nCnt++ )
	{
		if ( !m_stEquipItem[nCnt].bSetted )
		{
			m_stEquipItem[nCnt].bSetted = TRUE;
			m_stEquipItem[nCnt].xItem = xItem;
			m_stEquipItem[nCnt].xItem.m_shCellNum = nCnt;

			return TRUE;
		}
	}
	return FALSE;
}



/******************************************************************************************************************

	ÇÔ¼ö¸í : CStatusWnd::ExtractEquipItem()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : 
	ÀÔ·Â   : CItem* pxItem
	         INT nEquipNum
	Ãâ·Â   : BOOL 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
BOOL CStatusWnd::ExtractEquipItem(CItem* pxItem, INT nEquipNum)
{
	if ( m_stEquipItem[nEquipNum].bSetted )
	{
		memcpy(pxItem, &m_stEquipItem[nEquipNum].xItem, sizeof(CItem));
		DeleteEquipItem(nEquipNum);
				
		return TRUE;
	}
	return FALSE;
}





/******************************************************************************************************************

	ÇÔ¼ö¸í : CStatusWnd::ChangeEquipWithCommon()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : 
	ÀÔ·Â   : INT nEquipNum
	         LPCOMMONITEMSET pstCommonItemSet
	Ãâ·Â   : VOID 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
VOID CStatusWnd::ChangeEquipWithCommon(INT nEquipNum, LPCOMMONITEMSET pstCommonItemSet)
{
	if ( pstCommonItemSet->bSetted )
	{
		CItem xEquipItem;
		if ( ExtractEquipItem(&xEquipItem, nEquipNum) )
		{
			AddEquipItem(pstCommonItemSet->xItem, nEquipNum, TRUE);

			pstCommonItemSet->bSetted			= TRUE;
			pstCommonItemSet->xItem				= xEquipItem;
			pstCommonItemSet->bWaitResponse		= FALSE;
			pstCommonItemSet->bIsEquipItem		= TRUE;
			pstCommonItemSet->bIsHideItem		= FALSE;
			pstCommonItemSet->bIsBeltItem		= FALSE;
			pstCommonItemSet->xItem.m_shCellNum = nEquipNum; 
		}
	}
}




/******************************************************************************************************************

	ÇÔ¼ö¸í : CStatusWnd::SetCommonFromEquip()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : 
	ÀÔ·Â   : INT nEquipNum
	         LPCOMMONITEMSET pstCommonItemSet
	Ãâ·Â   : VOID 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
VOID CStatusWnd::SetCommonFromEquip(INT nEquipNum, LPCOMMONITEMSET pstCommonItemSet)
{
	CItem xEquipItem;
	if ( ExtractEquipItem(&xEquipItem, nEquipNum) )
	{
		pstCommonItemSet->bSetted			= TRUE;
		pstCommonItemSet->xItem				= xEquipItem;
		pstCommonItemSet->bWaitResponse		= FALSE;
		pstCommonItemSet->bIsEquipItem		= TRUE;
		pstCommonItemSet->bIsHideItem		= FALSE;
		pstCommonItemSet->bIsBeltItem		= FALSE;
		pstCommonItemSet->xItem.m_shCellNum = nEquipNum; 
	}	
}



/******************************************************************************************************************

	ÇÔ¼ö¸í : CStatusWnd::SetEquipFromCommon()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : 
	ÀÔ·Â   : INT nEquipNum
	         LPCOMMONITEMSET pstCommonItemSet
	Ãâ·Â   : VOID 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
VOID CStatusWnd::SetEquipFromCommon(INT nEquipNum, LPCOMMONITEMSET pstCommonItemSet)
{
	if ( pstCommonItemSet->bSetted )
	{
		pstCommonItemSet->xItem.m_shCellNum = nEquipNum;
		AddEquipItem(pstCommonItemSet->xItem, nEquipNum);
		ZeroMemory(pstCommonItemSet, sizeof(COMMONITEMSET));
	}
}



/******************************************************************************************************************

	ÇÔ¼ö¸í : CStatusWnd::SetTakeOnFromEquip()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : 
	ÀÔ·Â   : INT nEquipNum
	Ãâ·Â   : VOID 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
VOID CStatusWnd::SetTakeOnFromEquip(INT nEquipNum)
{
	if ( m_stEquipItem[nEquipNum].bSetted )
	{
		m_stTakeOnItemSet.xItem	  = m_stEquipItem[nEquipNum].xItem;
		m_stTakeOnItemSet.bSetted = TRUE;
		m_stTakeOnItemSet.xItem.m_shCellNum = nEquipNum;
		ZeroMemory(&m_stEquipItem[nEquipNum], sizeof(ITEMSET));	
	}
}



/******************************************************************************************************************

	ÇÔ¼ö¸í : CStatusWnd::SetTakeOnFromCommon()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : 
	ÀÔ·Â   : LPCOMMONITEMSET pstCommonItemSet
	Ãâ·Â   : VOID 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
VOID CStatusWnd::SetTakeOnFromCommon(INT nEquipNum, LPCOMMONITEMSET pstCommonItemSet)
{
	if ( pstCommonItemSet->bSetted )
	{
		m_stTakeOnItemSet.xItem   = pstCommonItemSet->xItem;
		m_stTakeOnItemSet.bSetted = TRUE;
		m_stTakeOnItemSet.xItem.m_shCellNum = nEquipNum;
		ZeroMemory(pstCommonItemSet, sizeof(COMMONITEMSET));	
	}
}



/******************************************************************************************************************

	ÇÔ¼ö¸í : CStatusWnd::SetEquipFromTakeOn()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : 
	Ãâ·Â   : VOID 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
VOID CStatusWnd::SetEquipFromTakeOn()
{
	if ( m_stTakeOnItemSet.bSetted )
	{
		AddEquipItem(m_stTakeOnItemSet.xItem, m_stTakeOnItemSet.xItem.m_shCellNum, TRUE);
		ZeroMemory(&m_stTakeOnItemSet, sizeof(ITEMSET));
	}
}





















/******************************************************************************************************************

	Ä³¸¯ÅÍ »óÅÂÁ¤º¸Ã¢°ü·Ã.

*******************************************************************************************************************/
/******************************************************************************************************************

	ÇÔ¼ö¸í : CStatusWnd::ShowCharStatus()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : 
	Ãâ·Â   : VOID 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
VOID CStatusWnd::ShowCharStatus()
{
	CHAR	szBuff[MAX_PATH];

	POINT	ptStart = {m_rcWnd.left+255+15, m_rcWnd.top+67};

	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "LEVEL", g_xMainWnd.CreateGameFont("ËÎÌå", 9, 0, FW_BOLD));
	sprintf(szBuff, "%d", g_xGameProc.m_pMyHero->m_stAbility.bLevel);
	g_xMainWnd.PutsHan(NULL, ptStart.x+53, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;

	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "HP", g_xMainWnd.CreateGameFont("ËÎÌå", 9, 0, FW_BOLD));
	sprintf(szBuff, "%d / %d", g_xGameProc.m_pMyHero->m_stAbility.wHP, g_xGameProc.m_pMyHero->m_stAbility.wMaxHP);
	g_xMainWnd.PutsHan(NULL, ptStart.x+53, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;

	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "MP", g_xMainWnd.CreateGameFont("ËÎÌå", 9, 0, FW_BOLD));
	sprintf(szBuff, "%d / %d", g_xGameProc.m_pMyHero->m_stAbility.wMP, g_xGameProc.m_pMyHero->m_stAbility.wMaxMP);
	g_xMainWnd.PutsHan(NULL, ptStart.x+53, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);
	
	ptStart.y += 20;

	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "AC", g_xMainWnd.CreateGameFont("ËÎÌå", 9, 0, FW_BOLD));
	sprintf(szBuff, "%d-%d", LOBYTE(g_xGameProc.m_pMyHero->m_stAbility.wAC), HIBYTE(g_xGameProc.m_pMyHero->m_stAbility.wAC));
	g_xMainWnd.PutsHan(NULL, ptStart.x+53, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;

	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "MAC", g_xMainWnd.CreateGameFont("ËÎÌå", 9, 0, FW_BOLD));
	sprintf(szBuff, "%d-%d", LOBYTE(g_xGameProc.m_pMyHero->m_stAbility.wMAC), HIBYTE(g_xGameProc.m_pMyHero->m_stAbility.wMAC));
	g_xMainWnd.PutsHan(NULL, ptStart.x+53, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;

	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "DC", g_xMainWnd.CreateGameFont("ËÎÌå", 9, 0, FW_BOLD));
	sprintf(szBuff, "%d-%d", LOBYTE(g_xGameProc.m_pMyHero->m_stAbility.wDC), HIBYTE(g_xGameProc.m_pMyHero->m_stAbility.wDC));
	g_xMainWnd.PutsHan(NULL, ptStart.x+53, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;

	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "MC", g_xMainWnd.CreateGameFont("ËÎÌå", 9, 0, FW_BOLD));
	sprintf(szBuff, "%d-%d", LOBYTE(g_xGameProc.m_pMyHero->m_stAbility.wMC), HIBYTE(g_xGameProc.m_pMyHero->m_stAbility.wMC));
	g_xMainWnd.PutsHan(NULL, ptStart.x+53, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;

	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "SC", g_xMainWnd.CreateGameFont("ËÎÌå", 9, 0, FW_BOLD));
	sprintf(szBuff, "%d-%d", LOBYTE(g_xGameProc.m_pMyHero->m_stAbility.wSC), HIBYTE(g_xGameProc.m_pMyHero->m_stAbility.wSC));
	g_xMainWnd.PutsHan(NULL, ptStart.x+53, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.x = m_rcWnd.left+255+145;
	ptStart.y = m_rcWnd.top+67;

	FLOAT fExpRate = (FLOAT)((FLOAT)g_xGameProc.m_pMyHero->m_stAbility.dwExp/(FLOAT)g_xGameProc.m_pMyHero->m_stAbility.dwMaxExp);
	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "°æÇè", g_xMainWnd.CreateGameFont("ËÎÌå", 9, 0, FW_BOLD));
	sprintf(szBuff, "%.2f%s", fExpRate*100, "%%");
	g_xMainWnd.PutsHan(NULL, ptStart.x+55, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;

	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "°¡¹æ¹«°Ô", g_xMainWnd.CreateGameFont("ËÎÌå", 9, 0, FW_BOLD));
	sprintf(szBuff, "%d / %d", g_xGameProc.m_pMyHero->m_stAbility.wWeight, g_xGameProc.m_pMyHero->m_stAbility.wMaxWeight);
	g_xMainWnd.PutsHan(NULL, ptStart.x+55, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;

	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "Âø¿ë¹«°Ô", g_xMainWnd.CreateGameFont("ËÎÌå", 9, 0, FW_BOLD));
	sprintf(szBuff, "%d / %d", g_xGameProc.m_pMyHero->m_stAbility.bWearWeight, g_xGameProc.m_pMyHero->m_stAbility.bMaxWearWeight);
	g_xMainWnd.PutsHan(NULL, ptStart.x+55, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;

	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "¾ç¼Õ¹«°Ô", g_xMainWnd.CreateGameFont("ËÎÌå", 9, 0, FW_BOLD));
	sprintf(szBuff, "%d / %d", g_xGameProc.m_pMyHero->m_stAbility.bHandWeight, g_xGameProc.m_pMyHero->m_stAbility.bMaxHandWeight);
	g_xMainWnd.PutsHan(NULL, ptStart.x+55, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;

	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "Á¤È®", g_xMainWnd.CreateGameFont("ËÎÌå", 9, 0, FW_BOLD));
	sprintf(szBuff, "+%d%", g_xGameProc.m_pMyHero->m_stSubAbility.bHitPoint);
	g_xMainWnd.PutsHan(NULL, ptStart.x+55, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;

	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "¹ÎÃ¸", g_xMainWnd.CreateGameFont("ËÎÌå", 9, 0, FW_BOLD));
	sprintf(szBuff, "+%d%", g_xGameProc.m_pMyHero->m_stSubAbility.bSpeedPoint);
	g_xMainWnd.PutsHan(NULL, ptStart.x+55, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;
	
	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "¸¶¹ýÈ¸ÇÇ", g_xMainWnd.CreateGameFont("ËÎÌå", 9, 0, FW_BOLD));
	sprintf(szBuff, "+%d%", g_xGameProc.m_pMyHero->m_stSubAbility.wAntiMagic*10);
	g_xMainWnd.PutsHan(NULL, ptStart.x+55, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;
	
	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "Áßµ¶È¸ÇÇ", g_xMainWnd.CreateGameFont("ËÎÌå", 9, 0, FW_BOLD));
	sprintf(szBuff, "+%d%", g_xGameProc.m_pMyHero->m_stSubAbility.bAntiPoison*10);
	g_xMainWnd.PutsHan(NULL, ptStart.x+55, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;
	
	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "Áßµ¶È¸º¹", g_xMainWnd.CreateGameFont("ËÎÌå", 9, 0, FW_BOLD));
	sprintf(szBuff, "+%d%", g_xGameProc.m_pMyHero->m_stSubAbility.bPoisonRecover*10);
	g_xMainWnd.PutsHan(NULL, ptStart.x+55, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;
	
	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "Ã¼·ÂÈ¸º¹", g_xMainWnd.CreateGameFont("ËÎÌå", 9, 0, FW_BOLD));
	sprintf(szBuff, "+%d%", g_xGameProc.m_pMyHero->m_stSubAbility.bHealthRecover*10);
	g_xMainWnd.PutsHan(NULL, ptStart.x+55, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;
	
	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), "¸¶·ÂÈ¸º¹", g_xMainWnd.CreateGameFont("ËÎÌå", 9, 0, FW_BOLD));
	sprintf(szBuff, "+%d%", g_xGameProc.m_pMyHero->m_stSubAbility.bSpellRecover*10);
	g_xMainWnd.PutsHan(NULL, ptStart.x+55, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);
}














/******************************************************************************************************************

	Ä³¸¯ÅÍ ¸¶¹ýÃ¢°ü·Ã.

*******************************************************************************************************************/
VOID CStatusWnd::ShowCharSetMagicWnd()
{
	INT nLine, nCnt, nStartX, nStartY;
	CHAR szKey[MAX_PATH];
	CHAR szLevel[MAX_PATH];

/*	CHAR* szSkillName[] =
	{ 
		"¹Ý¿ù°Ë¹ý",   "¾Ï¿¬¼ú",   "È­¿°Ç³",   "Ç×¸¶Áø¹ý", "´ëÁö¿øÈ£",   "¿°»çÀå",	"¹«ÅÂº¸",     "·ÚÈ¥°Ý",   "¾Æ°øÇà¹ý", "»çÀÚÀ±È¸", "È­¿°Àå",	    "È¸º¹¼ú",
		"°á°è",	      "´ëÈ¸º¹",   "·Ú¼³È­",   "·ÚÀÎÀå",   "¹é°ñ¼ÒÈ¯¼ú", "ºù¼³Ç³",	"´ëÀº½Å",     "ÁÖ¼úÀÇ¸·", "Å½±âÆÄ¿¬", "Áö¿°¼ú",   "Æø»ì°è",     "Æø¿­ÆÄ",
		"±Ý°­È­¿°Àå", "¿¹µµ",	  "¾î°Ë¼ú",	  "°­°Ý",	  "¿°È­°á",     "Àº½Å",		"½Å¼ö¼ÒÈ¯",	  "ÀÏ±¤°Ë¹ý",  "¿Ü¼ö°Ë¹ý",
	};
*/
	ShowGameWnd();

	for ( nCnt = 0; nCnt < _MAGIC_MAX_CELL; nCnt++ )
	{
		nLine = nCnt + m_nStartLineNum;

		if ( nLine >= m_bMyMagicCnt )			break;

		nStartX = m_rcWnd.left+m_rcMagicCell[nCnt].left;
		nStartY = m_rcWnd.top +m_rcMagicCell[nCnt].top;

		INT nMagicImgIdx = m_pstMyMagic[nLine].stStdMagic.wMagicID * 2;
		g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].NewSetIndex(nMagicImgIdx);
		g_xMainWnd.DrawWithImageForComp(
										nStartX, 
										nStartY, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_pbCurrImage));

		g_xMainWnd.PutsHan(NULL, nStartX+50, nStartY+5, RGB(255, 255, 220), RGB(0, 0, 0), m_pstMyMagic[nLine].stStdMagic.szMagicName);

		if ( m_pstMyMagic[nLine].bUseKey != 0 )
		{
			nMagicImgIdx = m_pstMyMagic[nLine].stStdMagic.wMagicID * 2 + 1;
			g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].NewSetIndex(nMagicImgIdx);
			g_xMainWnd.DrawWithImageForComp(
											nStartX, 
											nStartY, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_lpstNewCurrWilImageInfo->shWidth, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_pbCurrImage));

			sprintf(szKey, "F%c", (char)m_pstMyMagic[nLine].bUseKey);
			g_xMainWnd.PutsHan(NULL, nStartX+140, nStartY+7, RGB(255, 255, 255), RGB(125, 125, 255), szKey);
		}

	
		if ( m_pstMyMagic[nLine].bLevel < 3 )
		{
			sprintf(szLevel, "%d        %d/%d", m_pstMyMagic[nLine].bLevel, m_pstMyMagic[nLine].nCurrTrain, m_pstMyMagic[nLine].stStdMagic.nTrain[m_pstMyMagic[nLine].bLevel]);
			g_xMainWnd.PutsHan(NULL, nStartX+50, nStartY+23, RGB(255, 255, 220), RGB(0, 0, 0), szLevel);
		}
		else
		{
			sprintf(szLevel, "%d        ", m_pstMyMagic[nLine].bLevel);
			g_xMainWnd.PutsHan(NULL, nStartX+50, nStartY+23, RGB(255, 255, 220), RGB(0, 0, 0), szLevel);
		}

		m_xMagicScrlBtn[0].ShowGameBtn();
		m_xMagicScrlBtn[1].ShowGameBtn();
	}
}



/******************************************************************************************************************

	ÇÔ¼ö¸í : CStatusWnd::SetMagicKey()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : 
	ÀÔ·Â   : POINT ptMouse
	         BYTE bKey
	Ãâ·Â   : BOOL 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
BOOL CStatusWnd::SetMagicKey(POINT ptMouse, BYTE bKey)
{
	RECT rc;
	INT  nCnt, nLine;
	for ( nCnt = 0; nCnt < _MAGIC_MAX_CELL; nCnt++ )
	{
		nLine = nCnt + m_nStartLineNum;

		if ( nLine >= m_bMyMagicCnt )			break;

		rc.left   = m_rcWnd.left + m_rcMagicCell[nCnt].left;
		rc.top	  = m_rcWnd.top  + m_rcMagicCell[nCnt].top;
		rc.right  = m_rcWnd.left + m_rcMagicCell[nCnt].right;
		rc.bottom = m_rcWnd.top	 + m_rcMagicCell[nCnt].bottom;

		if ( PtInRect(&rc, ptMouse) )
		{
			for ( INT nLoop = 0; nLoop < m_bMyMagicCnt; nLoop++ )
			{
				if ( m_pstMyMagic[nLoop].bUseKey == bKey )
				{
					m_pstMyMagic[nLoop].bUseKey = 0;
					g_xGameProc.m_pSocket->SendMagicKeyChange(m_pstMyMagic[nLoop].bUseKey, m_pstMyMagic[nLoop].stStdMagic.wMagicID);
				}
			}

			if ( m_pstMyMagic[nLine].bUseKey != bKey )
			{
				m_pstMyMagic[nLine].bUseKey = bKey;

				g_xGameProc.m_pSocket->SendMagicKeyChange(m_pstMyMagic[nLine].bUseKey, m_pstMyMagic[nLine].stStdMagic.wMagicID);
			}
			return TRUE;
		}
	}

	return FALSE;
}



/******************************************************************************************************************

	ÇÔ¼ö¸í : CStatusWnd::GetMagicByKey()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : 
	ÀÔ·Â   : BYTE bKey
	Ãâ·Â   : LPCLIENTMAGICRCD 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
LPCLIENTMAGICRCD CStatusWnd::GetMagicByKey(BYTE bKey)
{
	LPCLIENTMAGICRCD pstMagic = NULL;

	for ( INT nCnt = 0; nCnt < m_bMyMagicCnt; nCnt++ )
	{
		pstMagic = &m_pstMyMagic[nCnt];
		if ( pstMagic->bUseKey == bKey )
		{
			break;
		}
	}
	return pstMagic;
}






















/******************************************************************************************************************

	Message Function.

*******************************************************************************************************************/

/******************************************************************************************************************

	ÇÔ¼ö¸í : CStatusWnd::OnKeyDown()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : 
	ÀÔ·Â   : WPARAM wParam
	         LPARAM lParam
	         POINT ptMouse
	Ãâ·Â   : BOOL 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
BOOL CStatusWnd::OnKeyDown(WPARAM wParam, LPARAM lParam, POINT ptMouse)
{
	INT	 nLine, nCnt;
	BOOL bCheck;
	RECT rc;

	if ( !PtInRect(&m_rcWnd, ptMouse) )		return TRUE;

	bCheck = FALSE;

	for ( nCnt = 0; nCnt < _MAGIC_MAX_CELL; nCnt++ )
	{
		nLine = nCnt + m_nStartLineNum;

		rc.left  = m_rcWnd.left + m_rcMagicCell[nCnt].left;
		rc.top	 = m_rcWnd.top  + m_rcMagicCell[nCnt].top;
		rc.right = m_rcWnd.left + m_rcMagicCell[nCnt].right;
		rc.bottom= m_rcWnd.top	+ m_rcMagicCell[nCnt].bottom;
		if ( PtInRect(&rc, ptMouse) )
		{
			bCheck = TRUE;
			break;
		}
	}

	if ( !bCheck ) 							return TRUE;

	if ( m_bType == _TYPE_SETMAGIC )
	{
		switch ( wParam )
		{
		case VK_F1:		SetMagicKey(ptMouse, '1');		return TRUE;
		case VK_F2:		SetMagicKey(ptMouse, '2');		return TRUE;
		case VK_F3:		SetMagicKey(ptMouse, '3');		return TRUE;
		case VK_F4:		SetMagicKey(ptMouse, '4');		return TRUE;
		case VK_F5:		SetMagicKey(ptMouse, '5');		return TRUE;
		case VK_F6:		SetMagicKey(ptMouse, '6');		return TRUE;
		case VK_F7:		SetMagicKey(ptMouse, '7');		return TRUE;
		case VK_F8:		SetMagicKey(ptMouse, '8');		return TRUE;
		}
	}

	return FALSE;
}



/******************************************************************************************************************

	ÇÔ¼ö¸í : CStatusWnd::OnLButtonUp()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : 
	ÀÔ·Â   : POINT ptMouse
	Ãâ·Â   : BOOL 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
BOOL CStatusWnd::OnLButtonUp(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse)
{
	INT nEquipNum;

	m_xStatusBtn[_BTN_ID_STATUSCLOSE].ChangeRect(m_rcWnd.left+_BTN_POS_X, m_rcWnd.top+_BTN_POS_Y);
//	m_xStatusBtn[_BTN_ID_STATUS     ].ChangeRect(m_rcWnd.left+_BTN_ID_STATUS_X, m_rcWnd.top+_BTN_ID_STATUS_Y);
//	m_xStatusBtn[_BTN_ID_STATUSMAGIC].ChangeRect(m_rcWnd.left+_BTN_ID_STATUSMAGIC_X, m_rcWnd.top+_BTN_ID_STATUSMAGIC_Y);
	
	if ( m_xStatusBtn[_BTN_ID_STATUSCLOSE].OnLButtonUp(ptMouse) )		return TRUE;
/*	if ( m_xStatusBtn[_BTN_ID_STATUS].OnLButtonUp(ptMouse) )
	{
		if ( m_bType == _TYPE_STATUS )
		{
			ResetWndImg(_WNDIMGIDX_ITEMSET);
			m_bType = _TYPE_EQUIP;
			m_xStatusBtn[_BTN_ID_STATUS].ResetGameBtn(212, 213);
		}
		else
		{
			ResetWndImg(_WNDIMGIDX_STATUS);
			m_bType = _TYPE_STATUS; 
			m_xStatusBtn[_BTN_ID_STATUS].ResetGameBtn(210, 211);

			if ( m_rcWnd.right > 800 )
			{
				m_rcWnd.left  = 260;
				m_rcWnd.right = 800;
			}
		}
	}*/
	if ( m_xStatusBtn[_BTN_ID_STATUSMAGIC].OnLButtonUp(ptMouse) )
	{
		m_bType = _TYPE_SETMAGIC;
		ResetWndImg(_WNDIMGIDX_SKILLSET);
	}

	if ( m_bType == _TYPE_SETMAGIC )
	{
		m_xMagicScrlBtn[0].ChangeRect(m_rcWnd.left+232, m_rcWnd.top+147);
		m_xMagicScrlBtn[1].ChangeRect(m_rcWnd.left+232, m_rcWnd.top+253);
		if ( m_xMagicScrlBtn[0].OnLButtonUp(ptMouse) )
		{
			if ( m_nStartLineNum > 0 )									m_nStartLineNum--;
		}

		if ( m_xMagicScrlBtn[1].OnLButtonUp(ptMouse) )
		{
			if ( m_nStartLineNum < m_bMyMagicCnt-_MAGIC_MAX_CELL)		m_nStartLineNum++;
		}
	}

	// ÀåÂøÃ¢ È°¼ºÈ­ µÆÀ»°æ¿ì.
	if ( m_bType == _TYPE_EQUIP || m_bType == _TYPE_STATUS )
	{
		nEquipNum = GetEquipNum(ptMouse);
		// ¸¶¿ì½º°¡ ÀåÂøÃ¢¿µ¿ª¿¡ ÀÖÀ»¶§.
		if ( nEquipNum != -1)
		{
			// Å¬¸¯ÇÑÀåÂøÃ¢¿¡ ¾ÆÀÌÅÛÀÌ ÀÖÀ»°æ¿ì.
			if ( m_stEquipItem[nEquipNum].bSetted )
			{
				// °øÅë(¸¶¿ì½º)¾ÆÀÌÅÛ¼ÂÀÌ ºñ¾îÀÖÀ¸¸é,
				if ( !pstCommonItemSet->bSetted )
				{				  
					// ¸¶¿ì½º¿¡ ¾ÆÀÌÅÛÀ» ºÙ¿©³õÀ¸¸é ÀÎº¥Åä¸® À©µµ¿¡¼­ Å¬¸¯ÇÏ´Â¼ø°£ CM_TAKEOFFITEM¸Þ½ÃÁö¸¦ º¸³½´Ù.
					SetCommonFromEquip(nEquipNum, pstCommonItemSet);
				}
				// °øÅë(¸¶¿ì½º)¾ÆÀÌÅÛ¼ÂÀº ÀÖ°í, ¼­¹ö·ÎºÎÅÍ ÀÀ´ä½ÅÈ£¸¦ ±â´Ù¸®´Â ÁßÀÌ ¾Æ´Ï¸é,
				// °øÅë¾ÆÀÌÅÛÀ» m_stTakeOnItemSet¿¡ ¾ÆÀÌÅÛÀ» ¼¼ÆÃÇØµÎ°í, ÇöÀç Å¬¸¯µÈ ÀåÂøÃ¢ ¾ÆÀÌÅÛÀ» °øÅë¾ÆÀÌÅÛÀ¸·Î ¼¼ÆÃÇÏ°í³ª¼­,
				// CM_TAKEONITEM¸Þ½ÃÁö¸¦ º¸³½´Ù.
				else if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse )
				{
					// º¸³»±âÀü ¿µ¿ªÀÌ ¼­·Î ¸Â´Â°¡(¹ÝÁöÀÚ¸®¿¡ ¹ÝÁö°¡ Àßµé¾î°¬´ÂÁö)¸¦ Ã¼Å©ÇÑ´Ù.
					if ( CheckEquipItem(&pstCommonItemSet->xItem, nEquipNum, ptMouse) )
					{
						SetTakeOnFromCommon(nEquipNum, pstCommonItemSet);
						SetCommonFromEquip(nEquipNum, pstCommonItemSet);					
						g_xGameProc.m_pSocket->SendTakeOnOffItem(CM_TAKEONITEM, nEquipNum, m_stTakeOnItemSet.xItem.m_stItemInfo.stStdItem.szName, m_stTakeOnItemSet.xItem.m_stItemInfo.nMakeIndex);
						pstCommonItemSet->bWaitResponse	= TRUE;
					}
				}
			}
			// Å¬¸¯ÇÑ ÀåÂøÃ¢¿¡ ¾ÆÀÌÅÛÀÌ ¾øÀ»°æ¿ì.
			else
			{
				// °øÅë(¸¶¿ì½º)¾ÆÀÌÅÛ¼ÂÀº ÀÖ°í, ¼­¹ö·ÎºÎÅÍ ÀÀ´ä½ÅÈ£¸¦ ±â´Ù¸®´Â ÁßÀÌ ¾Æ´Ï¸é, °øÅë¾ÆÀÌÅÛÀ» m_stTakeOnItemSet¿¡ ¾ÆÀÌÅÛÀ» ¼¼ÆÃÇØµÐ´Ù.
				if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse )
				{	
					if ( CheckEquipItem(&pstCommonItemSet->xItem, nEquipNum, ptMouse) )
					{
						// ¼­¹ö·Î ¸Þ½ÃÁö¸¦ º¸³¾ÇÊ¿ä´Â ¾ø´Ù. ¾ÆÀÌÅÛÀ» ¹þ¾ú´Ù°¡ ´Ù½ÃÂø¿ëÇÑ°æ¿ì.
						if ( pstCommonItemSet->bIsEquipItem )
						{
							SetEquipFromCommon(pstCommonItemSet->xItem.m_shCellNum, pstCommonItemSet);
							ZeroMemory(pstCommonItemSet, sizeof(COMMONITEMSET));
						}
						else
						{
							SetTakeOnFromCommon(nEquipNum, pstCommonItemSet);
							g_xGameProc.m_pSocket->SendTakeOnOffItem(CM_TAKEONITEM, nEquipNum, m_stTakeOnItemSet.xItem.m_stItemInfo.stStdItem.szName, m_stTakeOnItemSet.xItem.m_stItemInfo.nMakeIndex);
							pstCommonItemSet->bWaitResponse	= TRUE;
						}
					}
				}
			}
		}
	}

	return FALSE;
}



/******************************************************************************************************************

	ÇÔ¼ö¸í : CStatusWnd::OnMouseMove()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : 
	ÀÔ·Â   : POINT ptMouse
	Ãâ·Â   : VOID 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
VOID CStatusWnd::OnMouseMove(POINT ptMouse)
{
	if ( m_bType == _TYPE_SETMAGIC )
	{
		m_xMagicScrlBtn[0].ChangeRect(m_rcWnd.left+232, m_rcWnd.top+147);
		m_xMagicScrlBtn[1].ChangeRect(m_rcWnd.left+232, m_rcWnd.top+253);
		m_xMagicScrlBtn[0].OnMouseMove(ptMouse);
		m_xMagicScrlBtn[1].OnMouseMove(ptMouse);
	}

	m_xStatusBtn[_BTN_ID_STATUSCLOSE   ].ChangeRect(m_rcWnd.left+_BTN_POS_X, m_rcWnd.top+_BTN_POS_Y);
//	m_xStatusBtn[_BTN_ID_STATUS		   ].ChangeRect(m_rcWnd.left+_BTN_ID_STATUS_X, m_rcWnd.top+_BTN_ID_STATUS_Y);
//	m_xStatusBtn[_BTN_ID_STATUSMAGIC   ].ChangeRect(m_rcWnd.left+_BTN_ID_STATUSMAGIC_X, m_rcWnd.top+_BTN_ID_STATUSMAGIC_Y);
	m_xStatusBtn[_BTN_ID_STATUSCLOSE   ].OnMouseMove(ptMouse);
//	m_xStatusBtn[_BTN_ID_STATUS		   ].OnMouseMove(ptMouse);
//	m_xStatusBtn[_BTN_ID_STATUSMAGIC   ].OnMouseMove(ptMouse);
}



/******************************************************************************************************************

	ÇÔ¼ö¸í : CStatusWnd::OnLButtonDown()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : 
	ÀÔ·Â   : LPCOMMONITEMSET pstCommonItemSet
	         POINT ptMouse
	Ãâ·Â   : BOOL 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
BOOL CStatusWnd::OnLButtonDown(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse)
{
	INT nEquipNum;

	m_xStatusBtn[_BTN_ID_STATUSCLOSE   ].ChangeRect(m_rcWnd.left+_BTN_POS_X, m_rcWnd.top+_BTN_POS_Y);
//	m_xStatusBtn[_BTN_ID_STATUS	       ].ChangeRect(m_rcWnd.left+_BTN_ID_STATUS_X, m_rcWnd.top+_BTN_ID_STATUS_Y);
//	m_xStatusBtn[_BTN_ID_STATUSMAGIC   ].ChangeRect(m_rcWnd.left+_BTN_ID_STATUSMAGIC_X, m_rcWnd.top+_BTN_ID_STATUSMAGIC_Y);

	if ( m_xStatusBtn[_BTN_ID_STATUSCLOSE   ].OnLButtonDown(ptMouse) )		return TRUE;
//	if ( m_xStatusBtn[_BTN_ID_STATUS	    ].OnLButtonDown(ptMouse) )		return TRUE;
//	if ( m_xStatusBtn[_BTN_ID_STATUSMAGIC   ].OnLButtonDown(ptMouse) )		return TRUE;

	if ( m_bType == _TYPE_SETMAGIC )
	{
		m_xMagicScrlBtn[0].ChangeRect(m_rcWnd.left+232, m_rcWnd.top+147);
		m_xMagicScrlBtn[1].ChangeRect(m_rcWnd.left+232, m_rcWnd.top+253);
		if ( m_xMagicScrlBtn[0].OnLButtonDown(ptMouse) )					return TRUE;
		if ( m_xMagicScrlBtn[1].OnLButtonDown(ptMouse) )					return TRUE;
	}

	nEquipNum = GetEquipNum(ptMouse);

	if ( nEquipNum == -1 )		m_bCanMove = TRUE;
	else						
	{
		if ( m_stEquipItem[nEquipNum].bSetted )		m_bCanMove = FALSE;
		else										m_bCanMove = TRUE;				
	}

	return FALSE;
}



/******************************************************************************************************************

	ÇÔ¼ö¸í : CStatusWnd::OnScrollDown()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : 
	Ãâ·Â   : VOID 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
VOID CStatusWnd::OnScrollDown()
{
	if ( m_bType == _TYPE_SETMAGIC )
	{
		if ( m_nStartLineNum > 0 )										m_nStartLineNum--;
	}
}



/******************************************************************************************************************

	ÇÔ¼ö¸í : CStatusWnd::OnScrollUp()

	ÀÛ¼ºÀÚ : 
	ÀÛ¼ºÀÏ : 

	¸ñÀû   : 
	Ãâ·Â   : VOID 

	[ÀÏÀÚ][¼öÁ¤ÀÚ] : ¼öÁ¤³»¿ë

*******************************************************************************************************************/
VOID CStatusWnd::OnScrollUp()
{
	if ( m_bType == _TYPE_SETMAGIC )
	{
		if ( m_nStartLineNum < m_bMyMagicCnt-_MAGIC_MAX_CELL)			m_nStartLineNum++;
	}
}


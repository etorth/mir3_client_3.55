/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/


#include "StdAfx.h"



CItem::CItem()
{
	m_shCellNum	= 0;
	m_bAttr		= 0;
	m_nStateCnt = 0;
	ZeroMemory(m_stItemState, sizeof(ITEMSTATE)*_ITEM_MAX_STATE);	
}


CItem::~CItem()
{
}

BOOL CItem::SetItem(CLIENTITEMRCD stItemInfo, SHORT shInventoryNum)
{
	m_stItemInfo = stItemInfo;
	m_shCellNum = shInventoryNum;
/*
a:무기
b:옷
c:반지 팔찌 목걸이
g:기타
*/
/*
#define _U_DRESS					0
#define _U_WEAPON					1
#define _U_RIGHTHAND				2
#define _U_NECKLACE					3
#define _U_HELMET					4
#define _U_ARMRINGL					5
#define _U_ARMRINGR					6            
#define _U_RINGL					7 
#define _U_RINGR					8 
#define _U_CHARM					9
#define _U_UNEQUIP					100
*/

	switch ( m_stItemInfo.stStdItem.bStdMode )
	{
	// 무기.
	case 5:		
	case 6:		
	case 54:	// 표창.
	case 55:	// 눈덩이
	case 56:	// 무기추가.
		m_bAttr = _U_WEAPON;
		break;
	// 옷.
	case 10:
	case 11:
		m_bAttr = _U_DRESS;
		break;
	case 15:
		m_bAttr = _U_HELMET;
		break;
	case 19:
	case 20:
	case 21:
	case 57:	// 목걸이추가.
		m_bAttr = _U_NECKLACE;
		break;
	case 22:
	case 23:
		m_bAttr = _U_RINGL;
		break;
	case 24:
	case 26:
		m_bAttr = _U_ARMRINGL;
		break;
	case 28:	// 낙인 - 원보상점 - 테섭에도 적용할 것 - 2006.07.06 추가
	case 30:	// 초, 횃불.
		m_bAttr = _U_RIGHTHAND;
		break;
	// 독가루, 부적.
	case 25:
		m_bAttr = _U_CHARM;
		break;
	// 신발.
	case 53:
		m_bAttr = _U_BOOTS;
		break;
	case 60:
		m_bAttr = _U_ETC;
		break;
	}	

	return TRUE;
}


BOOL CItem::DrawItem(INT nX, INT nY, BYTE bItemType, BOOL bDrawCount)
{
	CWHWilImageData*	pxItemImg;	
	BOOL bDrawItem = FALSE;
	INT	nAmountX = nX;
	INT nAmountY = nY;

	switch ( bItemType )
	{
	case _ITEM_TYPE_STORE:
		pxItemImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_STORE];
		bDrawItem = pxItemImg->NewSetIndex(m_stItemInfo.stStdItem.wLooks);
		if ( bDrawItem )
		{
			nX = nX+_INVENTORY_CELL_WIDTH/2-pxItemImg->m_lpstNewCurrWilImageInfo->shWidth/2;
			nY = nY+_INVENTORY_CELL_HEIGHT/2-pxItemImg->m_lpstNewCurrWilImageInfo->shHeight/2;
		}
		break;
	case _ITEM_TYPE_INVENTORY:
		pxItemImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_INVENTORY];
		bDrawItem = pxItemImg->NewSetIndex(m_stItemInfo.stStdItem.wLooks);
		if ( bDrawItem )
		{
			nX = nX+_INVENTORY_CELL_WIDTH/2-pxItemImg->m_lpstNewCurrWilImageInfo->shWidth/2;
			nY = nY+_INVENTORY_CELL_HEIGHT/2-pxItemImg->m_lpstNewCurrWilImageInfo->shHeight/2;
		}
		break;
	case _ITEM_TYPE_EQUIP:
		pxItemImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_EQUIP];
		bDrawItem = pxItemImg->NewSetIndex(m_stItemInfo.stStdItem.wLooks);
		if ( bDrawItem )
		{
			nX += g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_EQUIP].m_lpstNewCurrWilImageInfo->shPX;
			nY += g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_EQUIP].m_lpstNewCurrWilImageInfo->shPY;
		}
		break;
	}
		
	if ( bDrawItem )
	{

		WORD wClr = 0XFFFF;
		
		if ( m_stItemInfo.stStdItem.bStdMode == 10 || m_stItemInfo.stStdItem.bStdMode == 11 /*|| m_stItemInfo.stStdItem.bStdMode == 15 */)
		{
			wClr = g_xMainWnd.ConvertColor24To16(RGB(m_stItemInfo.bLevel_R, 
													 LOBYTE(m_stItemInfo.wAmount_GB), 
													 HIBYTE(m_stItemInfo.wAmount_GB)));
		}

		RECT rcTemp;
		SetRect(&rcTemp, nX, nY, nX + pxItemImg->m_lpstNewCurrWilImageInfo->shWidth, nY+pxItemImg->m_lpstNewCurrWilImageInfo->shHeight);

 		g_xMainWnd.DrawWithImageForCompClipRgn(
						nX,
						nY,
						pxItemImg->m_lpstNewCurrWilImageInfo->shWidth,
						pxItemImg->m_lpstNewCurrWilImageInfo->shHeight,
						(WORD*)pxItemImg->m_pbCurrImage, _CLIP_WIDTH, 600, wClr);

		if (bDrawCount == TRUE)
		{
			if (m_stItemInfo.stStdItem.bThrow >= _MULTIPLE_TYPE_ITEM)
			{
				RECT rc;
				CHAR pszTmp[MAX_PATH];

				DWORD	dwCount = m_stItemInfo.wAmount_GB;

				INT		nCnt = 0;
				nCnt = log10(dwCount);

				rc.left = nAmountX + 25 - (nCnt * 5);
				rc.top = nAmountY + 23;


				sprintf(pszTmp, "%d", dwCount);
				g_xMainWnd.PutsHan(NULL, rc.left, rc.top, RGB(255, 255, 0), RGB(0,0,0), pszTmp);
			}	
		}
	}
	return TRUE;
}

BOOL CItem::DrawItemUseColorIdx(INT nX, INT nY, INT nColorIdx, BYTE bItemType, BOOL bDrawCount)
{
	CWHWilImageData*	pxItemImg;	
	BOOL bDrawItem = FALSE;
	INT	nAmountX = nX;
	INT nAmountY = nY;

	switch ( bItemType )
	{
	case _ITEM_TYPE_STORE:
		pxItemImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_STORE];
		bDrawItem = pxItemImg->NewSetIndex(m_stItemInfo.stStdItem.wLooks);
		if ( bDrawItem )
		{
			nX = nX+_INVENTORY_CELL_WIDTH/2-pxItemImg->m_lpstNewCurrWilImageInfo->shWidth/2;
			nY = nY+_INVENTORY_CELL_HEIGHT/2-pxItemImg->m_lpstNewCurrWilImageInfo->shHeight/2;
		}
		break;
	case _ITEM_TYPE_INVENTORY:
		pxItemImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_INVENTORY];
		bDrawItem = pxItemImg->NewSetIndex(m_stItemInfo.stStdItem.wLooks);
		if ( bDrawItem )
		{
			nX = nX+_INVENTORY_CELL_WIDTH/2-pxItemImg->m_lpstNewCurrWilImageInfo->shWidth/2;
			nY = nY+_INVENTORY_CELL_HEIGHT/2-pxItemImg->m_lpstNewCurrWilImageInfo->shHeight/2;
		}
		break;
	case _ITEM_TYPE_EQUIP:
		pxItemImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_EQUIP];
		bDrawItem = pxItemImg->NewSetIndex(m_stItemInfo.stStdItem.wLooks);
		if ( bDrawItem )
		{
			nX += g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_EQUIP].m_lpstNewCurrWilImageInfo->shPX;
			nY += g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_EQUIP].m_lpstNewCurrWilImageInfo->shPY;
		}
		break;
	}
		
	if ( bDrawItem )
	{
		WORD wClr = 0XFFFF;
		
		switch ( nColorIdx )
		{
			case 0:
				wClr = RGB(255, 255, 255);
				break;
			case 1:
				wClr = 49345;
				break;
			case 2:
				wClr = 47039;
				break;
			case 3:
				wClr = 15709;
				break;
			case 4:
				wClr = 20382;
				break;
			case 5:
				wClr = 50900;
				break;
			case 6:
				wClr = 0;
				break;
			case 7:
				wClr = 56027;
				break;
		}

		RECT rcTemp;
		SetRect(&rcTemp, nX, nY, nX + pxItemImg->m_lpstNewCurrWilImageInfo->shWidth, nY+pxItemImg->m_lpstNewCurrWilImageInfo->shHeight);

 		g_xMainWnd.DrawWithImageForCompClipRgn(
						nX,
						nY,
						pxItemImg->m_lpstNewCurrWilImageInfo->shWidth,
						pxItemImg->m_lpstNewCurrWilImageInfo->shHeight,
						(WORD*)pxItemImg->m_pbCurrImage, _CLIP_WIDTH, 600, wClr);

		if (bDrawCount == TRUE)
		{
			if (m_stItemInfo.stStdItem.bThrow >= _MULTIPLE_TYPE_ITEM)
			{
				RECT rc;
				CHAR pszTmp[MAX_PATH];

				DWORD	dwCount = m_stItemInfo.wAmount_GB;

				INT		nCnt = 0;
				nCnt = log10(dwCount);

				rc.left = nAmountX + 25 - (nCnt * 5);
				rc.top = nAmountY + 23;


				sprintf(pszTmp, "%d", dwCount);
				g_xMainWnd.PutsHan(NULL, rc.left, rc.top, RGB(255, 255, 0), RGB(0,0,0), pszTmp);
			}	
		}
	}
	return TRUE;
}

VOID CItem::SetItemStatus(BOOL bUseStore, BOOL bUseEquip)
{
	m_nStateCnt = 0;
	ZeroMemory(m_stItemState, sizeof(ITEMSTATE)*_ITEM_MAX_STATE);	

	if ( m_stItemInfo.stStdItem.szName )
	{
		switch ( m_stItemInfo.stStdItem.bStdMode )
		{
			// 남자옷, 여자옷.
			case 10:
			case 11:
			{
				SetClothStatus(bUseStore, bUseEquip);
				break;
			}
			// 무기.
			case 5:		
			case 6:	
			case 54:
			case 55:	//눈덩이
			case 56:	// 무기추가.
			{
				SetWeaponStatus(bUseStore, bUseEquip);
				break;
			}
			case 15:	//모자,투구
			case 19:	//목걸이
			case 57:	// 목걸이추가.
			case 20:
			case 21:  
			case 22:	//반지
			case 23:  
			case 24:	//팔찌
			case 26:  
			case 28:	// 낙인 - 원보상점 - 2006.07.06 추가
			{
				SetAccessoryStatus(bUseStore, bUseEquip);
				break;
			}
			case 53:	//신발
			{
				SetBootsStatus(bUseStore, bUseEquip);
				break;
			}
			default:
			{
				SetEtcStatus(bUseStore, bUseEquip);
				break;
			}
		}
	}
}

VOID CItem::SetClothStatus(BOOL bUseStore, BOOL bUseEquip)
{
	INT	 nCnt; 
	BOOL bUseAble  = FALSE;

	// 1. 이름.
	if ( strlen(m_stItemInfo.Prefix) )
	{		
		sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%s %s", g_xMsg.GetMsg(2515), m_stItemInfo.Prefix, m_stItemInfo.stStdItem.szName);
	}
	else
	{
		sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%s", g_xMsg.GetMsg(2515), m_stItemInfo.stStdItem.szName);
	}
	m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
	m_stItemState[m_nStateCnt].dwFont = RGB(255, 250,   0);
	m_nStateCnt++;

	// 2. 내구.
	INT nDura	 = RoundFunc(m_stItemInfo.nDura, 1000);
	INT nDuraMax = RoundFunc(m_stItemInfo.nDuraMax, 1000);
	if ( bUseStore )
	{
		nDura	 = RoundFunc(m_stItemInfo.nDura, 1000);
		nDuraMax = RoundFunc(m_stItemInfo.stStdItem.wDuraMax, 1000);	
	}
	sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d/%d", g_xMsg.GetMsg(2500), nDura, nDuraMax);
	m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
	if ( nDura <= 1 ) 
	{
		m_stItemState[m_nStateCnt].dwFont = RGB(255,  50,  50);
	}
	else
	{
		m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 255);
	}
	m_nStateCnt++;

	// 3. 무게.
	sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d", g_xMsg.GetMsg(2501), m_stItemInfo.stStdItem.bWeight);
	m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
	m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
	m_nStateCnt++;

	// 파괴.
	if ( m_stItemInfo.stStdItem.wDC + m_stItemInfo.Desc[2] > 0 )
	{
		m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
		if ( m_stItemInfo.Desc[2] > 0 )
		{
			// 옵션 Plus.
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d-%d (+%d)", g_xMsg.GetMsg(1061), LOBYTE(m_stItemInfo.stStdItem.wDC), HIBYTE(m_stItemInfo.stStdItem.wDC)+m_stItemInfo.Desc[2], m_stItemInfo.Desc[2]);
			m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
		}
		else
		{
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d-%d ", g_xMsg.GetMsg(1061), LOBYTE(m_stItemInfo.stStdItem.wDC), HIBYTE(m_stItemInfo.stStdItem.wDC));
			m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
		}
		m_nStateCnt++;

		if (bUseEquip)
			g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[0] = TRUE;
	}

	// 4. 방어.
	m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
	if ( m_stItemInfo.Desc[0] > 0 )
	{
		// 옵션 Plus.
		sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d-%d (+%d)", g_xMsg.GetMsg(5177), LOBYTE(m_stItemInfo.stStdItem.wAC), HIBYTE(m_stItemInfo.stStdItem.wAC)+m_stItemInfo.Desc[0], m_stItemInfo.Desc[0]);
		m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
	}
	else
	{
		sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d-%d", g_xMsg.GetMsg(5177), LOBYTE(m_stItemInfo.stStdItem.wAC), HIBYTE(m_stItemInfo.stStdItem.wAC));
		m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
	}
	m_nStateCnt++;

	if (bUseEquip)
		g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[1] = TRUE;

	// 마법방어
	if ( m_stItemInfo.stStdItem.wMAC + m_stItemInfo.Desc[1] > 0 )
	{
		if ( m_stItemInfo.Desc[1] > 0)
		{
			// 옵션 Plus.
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d-%d (+%d)", g_xMsg.GetMsg(1406), LOBYTE(m_stItemInfo.stStdItem.wMAC), HIBYTE(m_stItemInfo.stStdItem.wMAC)+m_stItemInfo.Desc[1], m_stItemInfo.Desc[1]);
			m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
		}
		else
		{
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d-%d", g_xMsg.GetMsg(1406), LOBYTE(m_stItemInfo.stStdItem.wMAC), HIBYTE(m_stItemInfo.stStdItem.wMAC));
			m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
		}
		m_nStateCnt++;
		if (bUseEquip)
			g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[4] = TRUE;
	}

	// 마법
	if ( m_stItemInfo.stStdItem.wMC + m_stItemInfo.Desc[3] > 0 )
	{
		m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
		if ( m_stItemInfo.Desc[3] > 0 )
		{
			// 옵션 Plus.
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d-%d (+%d)", g_xMsg.GetMsg(5100+m_stItemInfo.stStdItem.MCType), LOBYTE(m_stItemInfo.stStdItem.wMC), HIBYTE(m_stItemInfo.stStdItem.wMC)+m_stItemInfo.Desc[3], m_stItemInfo.Desc[3]);
			m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
		}
		else
		{
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d-%d ", g_xMsg.GetMsg(5100+m_stItemInfo.stStdItem.MCType), LOBYTE(m_stItemInfo.stStdItem.wMC), HIBYTE(m_stItemInfo.stStdItem.wMC));
			m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
		}
		m_nStateCnt++;


		if (bUseEquip)
		{
			if (m_stItemInfo.stStdItem.MCType == 0) //전계열
			{
				g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[2] = TRUE;
				g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[3] = TRUE;
			}
			else if (m_stItemInfo.stStdItem.MCType == 1) //자연계열
			{
				g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[2] = TRUE;
			}
			else // 영혼계
			{
				g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[3] = TRUE;
			}
		}
	}

	if ( m_stItemInfo.Desc[8] > 0 )
	{
		m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
		// 옵션 Plus.
		sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%d", g_xMsg.GetMsg(2518), m_stItemInfo.Desc[8] * 10);
		m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
		m_nStateCnt++;
	}
	
	if ( m_stItemInfo.Desc[9] > 0 )
	{
		m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
		// 옵션 Plus.
		sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%d", g_xMsg.GetMsg(2519), m_stItemInfo.Desc[9] * 10);
		m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
		m_nStateCnt++;
	}

	// 원소 파괴
	if (( m_stItemInfo.Desc[11] > 0 ) || (m_stItemInfo.stStdItem.bAtomDCType> 0))
	{
		CHAR szTemp[MAX_PATH], szTemp2[MAX_PATH];

		sprintf(szTemp2, "%s:", g_xMsg.GetMsg(5178));
		m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 0);

		byte btAtomType = m_stItemInfo.stStdItem.bAtomDCType;

		if ( btAtomType != m_stItemInfo.Desc[11] && btAtomType != 0 )
		{
			CHAR szTemp3[MAX_PATH];
			sprintf(szTemp3, " %s+%d", g_xMsg.GetMsg(btAtomType+5160), m_stItemInfo.stStdItem.wAtomDC);
			strcat(szTemp2, szTemp3);
		}

		if (m_stItemInfo.Desc[11] > 0)
			btAtomType = m_stItemInfo.Desc[11];

		if ( m_stItemInfo.Desc[12] > 0 )
		{
			if ( btAtomType == m_stItemInfo.stStdItem.bAtomDCType )
				sprintf(szTemp, " %s+%d", g_xMsg.GetMsg(btAtomType+5160), m_stItemInfo.stStdItem.wAtomDC+m_stItemInfo.Desc[12]);
			else
				sprintf(szTemp, " %s+%d", g_xMsg.GetMsg(btAtomType+5160), m_stItemInfo.Desc[12]);

			strcat(szTemp2, szTemp);
		}

		m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 0);
		sprintf(m_stItemState[m_nStateCnt].pszDesc, szTemp2);

		if (bUseEquip)
			g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[btAtomType+4] = TRUE;

		m_nStateCnt++;
	}

	// 강한원소
	if ( m_stItemInfo.Desc[5] > 0 || m_stItemInfo.stStdItem.sAtomACGood )
	{
		INT nMask = 1;
		CHAR szTemp[MAX_PATH], szTemp2[MAX_PATH];
		BOOL bFind = FALSE;

		sprintf(szTemp2, "%s:", g_xMsg.GetMsg(5179));

		for ( INT nI=0; nI<7; nI++)
		{
			BOOL bCheck = FALSE;
			if ( m_stItemInfo.Desc[5] & nMask )
			{
				bCheck = TRUE;
				bFind = TRUE;
				if ( m_stItemInfo.stStdItem.sAtomACGood == nI+1 )
					sprintf(szTemp, " %sx3", g_xMsg.GetMsg(5161+nI));
				else
					sprintf(szTemp, " %sx2", g_xMsg.GetMsg(5161+nI));

				if (bUseEquip)
					g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[12+nI] = TRUE;

			}
			else if ( m_stItemInfo.stStdItem.sAtomACGood == nI+1 )
			{
				bCheck = TRUE;
				bFind = TRUE;
				sprintf(szTemp, " %sx2", g_xMsg.GetMsg(5161+nI));

				if (bUseEquip)
					g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[12+nI] = TRUE;
			}

			if ( bCheck )
				strcat(szTemp2, szTemp);

			nMask <<= 1;
		}

		if ( bFind )
		{
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s", szTemp2);
			m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 0);
			m_nStateCnt++;
		}
	}
	
	// 약한원소
	if ( m_stItemInfo.Desc[6] > 0 || m_stItemInfo.stStdItem.sAtomACBad )
	{
		INT nMask = 1;
		CHAR szTemp[MAX_PATH], szTemp2[MAX_PATH];
		BOOL bFind = FALSE;

		sprintf(szTemp2, "%s:", g_xMsg.GetMsg(5180));

		for ( INT nI=0; nI<7; nI++)
		{
			BOOL bCheck = FALSE;
			if ( m_stItemInfo.Desc[6] & nMask )
			{
				bCheck = TRUE;
				bFind = TRUE;
				if ( m_stItemInfo.stStdItem.sAtomACBad == nI+1 )
					sprintf(szTemp, " %sx3", g_xMsg.GetMsg(5161+nI));
				else
					sprintf(szTemp, " %sx2", g_xMsg.GetMsg(5161+nI));

				if (bUseEquip)
					g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[19+nI] = TRUE;

			}
			else if ( m_stItemInfo.stStdItem.sAtomACBad == nI+1 )
			{
				bCheck = TRUE;
				bFind = TRUE;
				sprintf(szTemp, " %sx2", g_xMsg.GetMsg(5161+nI));

				if (bUseEquip)
					g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[19+nI] = TRUE;
			}

			if ( bCheck )
				strcat(szTemp2, szTemp);

			nMask <<= 1;
		}

		if ( bFind )
		{
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s", szTemp2);
			m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
			m_nStateCnt++;
		}
	}

	if ( m_stItemInfo.stStdItem.sAtomACBad > 0 && m_stItemInfo.stStdItem.sAtomACBad < 7)
	{
		INT nAmount = m_stItemInfo.stStdItem.sAtomACBad;
		sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s:%sx2", g_xMsg.GetMsg(5179), g_xMsg.GetMsg(5160+nAmount));
		m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
		m_nStateCnt++;
		if (bUseEquip)
			g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[nAmount+18] = TRUE;
	}

	if ( m_stItemInfo.Desc[11] > 0 )
	{
		m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 0);

		sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d-%d (+%d)", g_xMsg.GetMsg(m_stItemInfo.Desc[11]+5160), LOBYTE(m_stItemInfo.stStdItem.wAtomDC), HIBYTE(m_stItemInfo.stStdItem.wAtomDC) + m_stItemInfo.Desc[12], m_stItemInfo.Desc[12]);

		m_nStateCnt++;

		if (bUseEquip)
			g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[m_stItemInfo.Desc[11]+4] = TRUE;
	}

	// 8. 필요능력치.
	switch ( m_stItemInfo.stStdItem.bNeed )
	{
		case 0:
		{
			if ( g_xGameProc.m_xMyHero.m_stAbility.bLevel >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}

			if ( m_stItemInfo.stStdItem.bNeedLevel > 100 && g_xGameProc.m_xMyHero.m_stAbility.bLevel >= m_stItemInfo.stStdItem.bNeedLevel - 100 )
			{
			   bUseAble = TRUE;
			}

			if ( m_stItemInfo.stStdItem.bNeedLevel == 0 )
			{
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s", g_xMsg.GetMsg(2516));
			}
			else if ( m_stItemInfo.stStdItem.bNeedLevel > 100 )
			{
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d (%s)", g_xMsg.GetMsg(5140), m_stItemInfo.stStdItem.bNeedLevel-100, g_xMsg.GetMsg(2517));
			}
			else
			{
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d", g_xMsg.GetMsg(5140), m_stItemInfo.stStdItem.bNeedLevel);
			}
			break;
		}
		case 1:
		{
			if ( HIWORD(g_xGameProc.m_xMyHero.m_stAbility.dwDC) >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5141), m_stItemInfo.stStdItem.bNeedLevel);
			break;
		}
		case 2:
		{
			bUseAble = TRUE;
			for ( nCnt = 0; nCnt < 4; nCnt++)
			{
				if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[nCnt]) < m_stItemInfo.stStdItem.bNeedLevel )
				{
					bUseAble = FALSE;
					break;
				}
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5142), m_stItemInfo.stStdItem.bNeedLevel);
			break;
		}
		case 3:
		{
			bUseAble = TRUE;
			for ( nCnt = 4; nCnt < 7; nCnt++)
			{
				if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[nCnt]) < m_stItemInfo.stStdItem.bNeedLevel )
				{
					bUseAble = FALSE;
					break;
				}
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5143), m_stItemInfo.stStdItem.bNeedLevel);
			break;
		}
		case 4:
		{
			bUseAble = TRUE;
			for ( nCnt = 0; nCnt < 7; nCnt++)
			{
				if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[nCnt]) < m_stItemInfo.stStdItem.bNeedLevel )
				{
					bUseAble = FALSE;
					break;
				}
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5144), m_stItemInfo.stStdItem.bNeedLevel);
			break;
		}
		case 5:
		{
			if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[0]) >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5145), m_stItemInfo.stStdItem.bNeedLevel);
			break;
		}
		case 6:
		{
			if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[1]) >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5146), m_stItemInfo.stStdItem.bNeedLevel);
			break;
		}
		case 7:
		{
			if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[2]) >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5147), m_stItemInfo.stStdItem.bNeedLevel);
			break;
		}
		case 8:
		{
			if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[3]) >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5148), m_stItemInfo.stStdItem.bNeedLevel);

			break;
		}
		case 9:
		{
			if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[4]) >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5149), m_stItemInfo.stStdItem.bNeedLevel);

			break;
		}
		case 10:
		{
			if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[5]) >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5150), m_stItemInfo.stStdItem.bNeedLevel);

			break;
		}
		case 11:
		{
			if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[6]) >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5151), m_stItemInfo.stStdItem.bNeedLevel);

			break;
		}
	}
	m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);

	if ( ( m_stItemInfo.stStdItem.bNeed == 0 && m_stItemInfo.stStdItem.bNeedLevel == 0 ||
		 m_stItemInfo.stStdItem.bNeed == 0 && m_stItemInfo.stStdItem.bNeedLevel > 100 ) && bUseAble )
	{
		m_stItemState[m_nStateCnt].dwFont = RGB(  0, 200,   0);
	}
	else if ( bUseAble )
	{
		m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
	}
	else
	{
		m_stItemState[m_nStateCnt].dwFont = RGB(255, 0, 0);
	}
	m_nStateCnt++;

	if ( m_stItemInfo.stStdItem.nNeedFame > 0 )
	{
		sprintf(m_stItemState[m_nStateCnt].pszDesc, g_xMsg.GetMsg(2520), m_stItemInfo.stStdItem.nNeedFame);
		m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);

		if ( g_xGameProc.m_xMyHero.m_nFame >= m_stItemInfo.stStdItem.nNeedFame )
			m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 255);
		else
			m_stItemState[m_nStateCnt].dwFont = RGB(255, 0, 0);

		m_nStateCnt++;
	}
}

VOID CItem::SetBootsStatus(BOOL bUseStore, BOOL bUseEquip)
{
	INT	 nCnt; 
	BOOL bUseAble  = FALSE;

	// 1. 이름.
	if ( strlen(m_stItemInfo.Prefix) )
	{		
		sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%s %s", g_xMsg.GetMsg(2515), m_stItemInfo.Prefix, m_stItemInfo.stStdItem.szName);
	}
	else
	{
		sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%s", g_xMsg.GetMsg(2515), m_stItemInfo.stStdItem.szName);
	}
	m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
	m_stItemState[m_nStateCnt].dwFont = RGB(255, 250,   0);
	m_nStateCnt++;

	// 2. 내구.
	INT nDura	 = RoundFunc(m_stItemInfo.nDura, 1000);
	INT nDuraMax = RoundFunc(m_stItemInfo.nDuraMax, 1000);
	if ( bUseStore )
	{
		nDura	 = RoundFunc(m_stItemInfo.nDura, 1000);
		nDuraMax = RoundFunc(m_stItemInfo.stStdItem.wDuraMax, 1000);	
	}
	sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d/%d", g_xMsg.GetMsg(2500), nDura, nDuraMax);
	m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
	if ( nDura <= 1 ) 
	{
		m_stItemState[m_nStateCnt].dwFont = RGB(255,  50,  50);
	}
	else
	{
		m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 255);
	}
	m_nStateCnt++;

	// 3. 무게.
	sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d", g_xMsg.GetMsg(2501), m_stItemInfo.stStdItem.bWeight);
	m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
	m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
	m_nStateCnt++;

	// 4. 편안함.
	if ( m_stItemInfo.stStdItem.wDC + m_stItemInfo.Desc[0] > 0 )
	{
		m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
		if ( m_stItemInfo.Desc[0] > 0 )
		{
			// 옵션 Plus.
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d (+%d)", g_xMsg.GetMsg(2502), m_stItemInfo.stStdItem.wDC+m_stItemInfo.Desc[0], m_stItemInfo.Desc[0]);
			m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
		}
		else
		{
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d", g_xMsg.GetMsg(2502), m_stItemInfo.stStdItem.wDC);
			m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
		}
		m_nStateCnt++;
	}

	// 5. 착용무게.
	if ( LOBYTE(m_stItemInfo.stStdItem.wMC) + m_stItemInfo.Desc[1] > 0 )
	{
		m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
		if ( m_stItemInfo.Desc[1] > 0 )
		{
			// 옵션 Plus.
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d (+%d)", g_xMsg.GetMsg(1063), LOBYTE(m_stItemInfo.stStdItem.wMC) + m_stItemInfo.Desc[1], m_stItemInfo.Desc[1]);
			m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
		}
		else
		{
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d", g_xMsg.GetMsg(1063), LOBYTE(m_stItemInfo.stStdItem.wMC));
			m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
		}
		m_nStateCnt++;
	}

	// 5. 양손무게.
	if ( HIBYTE(m_stItemInfo.stStdItem.wMC) + m_stItemInfo.Desc[2] > 0 )
	{
		m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
		
		if ( m_stItemInfo.Desc[2] > 0 )
		{
			// 옵션 Plus.
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d (+%d)", g_xMsg.GetMsg(1064), HIBYTE(m_stItemInfo.stStdItem.wMC)+m_stItemInfo.Desc[2], m_stItemInfo.Desc[2]);
			m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
		}
		else
		{
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d", g_xMsg.GetMsg(1064), HIBYTE(m_stItemInfo.stStdItem.wMC));
			m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
		}
		m_nStateCnt++;
	}

	// 강한원소
	if ( m_stItemInfo.Desc[5] > 0 || m_stItemInfo.stStdItem.sAtomACGood )
	{
		INT nMask = 1;
		CHAR szTemp[MAX_PATH], szTemp2[MAX_PATH];
		BOOL bFind = FALSE;

		sprintf(szTemp2, "%s:", g_xMsg.GetMsg(5179));

		for ( INT nI=0; nI<7; nI++)
		{
			BOOL bCheck = FALSE;
			if ( m_stItemInfo.Desc[5] & nMask )
			{
				bCheck = TRUE;
				bFind = TRUE;
				if ( m_stItemInfo.stStdItem.sAtomACGood == nI+1 )
					sprintf(szTemp, " %sx2", g_xMsg.GetMsg(5161+nI));
				else
					sprintf(szTemp, " %sx1", g_xMsg.GetMsg(5161+nI));

				if (bUseEquip)
					g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[12+nI] = TRUE;

			}
			else if ( m_stItemInfo.stStdItem.sAtomACGood == nI+1 )
			{
				bCheck = TRUE;
				bFind = TRUE;
				sprintf(szTemp, " %sx1", g_xMsg.GetMsg(5161+nI));

				if (bUseEquip)
					g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[12+nI] = TRUE;
			}

			if ( bCheck )
				strcat(szTemp2, szTemp);

			nMask <<= 1;
		}

		if ( bFind )
		{
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s", szTemp2);
			m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 0);
			m_nStateCnt++;
		}
	}

	if ( m_stItemInfo.Desc[8] > 0 )
	{
		m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
		// 옵션 Plus.
		sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%d", g_xMsg.GetMsg(2518), m_stItemInfo.Desc[8] * 10);
		m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
		m_nStateCnt++;
	}
	
	if ( m_stItemInfo.Desc[9] > 0 )
	{
		m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
		// 옵션 Plus.
		sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%d", g_xMsg.GetMsg(2519), m_stItemInfo.Desc[9] * 10);
		m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
		m_nStateCnt++;
	}

	// 약한원소
	if ( m_stItemInfo.Desc[6] > 0 || m_stItemInfo.stStdItem.sAtomACBad )
	{
		INT nMask = 1;
		CHAR szTemp[MAX_PATH], szTemp2[MAX_PATH];
		BOOL bFind = FALSE;

		sprintf(szTemp2, "%s:", g_xMsg.GetMsg(5180));

		for ( INT nI=0; nI<7; nI++)
		{
			BOOL bCheck = FALSE;
			if ( m_stItemInfo.Desc[6] & nMask )
			{
				bCheck = TRUE;
				bFind = TRUE;
				if ( m_stItemInfo.stStdItem.sAtomACBad == nI+1 )
					sprintf(szTemp, " %sx2", g_xMsg.GetMsg(5161+nI));
				else
					sprintf(szTemp, " %sx1", g_xMsg.GetMsg(5161+nI));

				if (bUseEquip)
					g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[19+nI] = TRUE;

			}
			else if ( m_stItemInfo.stStdItem.sAtomACBad == nI+1 )
			{
				bCheck = TRUE;
				bFind = TRUE;
				sprintf(szTemp, " %sx1", g_xMsg.GetMsg(5161+nI));

				if (bUseEquip)
					g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[19+nI] = TRUE;
			}

			if ( bCheck )
				strcat(szTemp2, szTemp);

			nMask <<= 1;
		}

		if ( bFind )
		{
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s", szTemp2);
			m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
			m_nStateCnt++;
		}
	}


	// 6. 필요능력치.
	switch ( m_stItemInfo.stStdItem.bNeed )
	{
		case 0:
		{
			if ( g_xGameProc.m_xMyHero.m_stAbility.bLevel >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}

			if ( m_stItemInfo.stStdItem.bNeedLevel > 100 && g_xGameProc.m_xMyHero.m_stAbility.bLevel >= m_stItemInfo.stStdItem.bNeedLevel - 100 )
			{
			   bUseAble = TRUE;
			}

			if ( m_stItemInfo.stStdItem.bNeedLevel == 0 )
			{
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s", g_xMsg.GetMsg(2516));
			}
			else if ( m_stItemInfo.stStdItem.bNeedLevel > 100 )
			{
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d (%s)", g_xMsg.GetMsg(5140), m_stItemInfo.stStdItem.bNeedLevel-100, g_xMsg.GetMsg(2517));
			}
			else
			{
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d", g_xMsg.GetMsg(5140), m_stItemInfo.stStdItem.bNeedLevel);
			}

			break;
		}
		case 1:
		{
			if ( HIWORD(g_xGameProc.m_xMyHero.m_stAbility.dwDC) >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5141), m_stItemInfo.stStdItem.bNeedLevel);
			break;
		}
		case 2:
		{
			bUseAble = TRUE;
			for ( nCnt = 0; nCnt < 4; nCnt++)
			{
				if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[nCnt]) < m_stItemInfo.stStdItem.bNeedLevel )
				{
					bUseAble = FALSE;
					break;
				}
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5142), m_stItemInfo.stStdItem.bNeedLevel);
			break;
		}
		case 3:
		{
			bUseAble = TRUE;
			for ( nCnt = 4; nCnt < 7; nCnt++)
			{
				if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[nCnt]) < m_stItemInfo.stStdItem.bNeedLevel )
				{
					bUseAble = FALSE;
					break;
				}
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5143), m_stItemInfo.stStdItem.bNeedLevel);
			break;
		}
		case 4:
		{
			bUseAble = TRUE;
			for ( nCnt = 0; nCnt < 7; nCnt++)
			{
				if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[nCnt]) < m_stItemInfo.stStdItem.bNeedLevel )
				{
					bUseAble = FALSE;
					break;
				}
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5144), m_stItemInfo.stStdItem.bNeedLevel);
			break;
		}
		case 5:
		{
			if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[0]) >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5145), m_stItemInfo.stStdItem.bNeedLevel);
			break;
		}
		case 6:
		{
			if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[1]) >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5146), m_stItemInfo.stStdItem.bNeedLevel);
			break;
		}
		case 7:
		{
			if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[2]) >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5147), m_stItemInfo.stStdItem.bNeedLevel);
			break;
		}
		case 8:
		{
			if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[3]) >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5148), m_stItemInfo.stStdItem.bNeedLevel);

			break;
		}
		case 9:
		{
			if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[4]) >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5149), m_stItemInfo.stStdItem.bNeedLevel);

			break;
		}
		case 10:
		{
			if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[5]) >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5150), m_stItemInfo.stStdItem.bNeedLevel);

			break;
		}
		case 11:
		{
			if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[6]) >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5151), m_stItemInfo.stStdItem.bNeedLevel);

			break;
		}
	}
	m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);

	if ( ( m_stItemInfo.stStdItem.bNeed == 0 && m_stItemInfo.stStdItem.bNeedLevel == 0 ||
		 m_stItemInfo.stStdItem.bNeed == 0 && m_stItemInfo.stStdItem.bNeedLevel > 100 ) && bUseAble )
	{
		m_stItemState[m_nStateCnt].dwFont = RGB(  0, 200,   0);
	}
	else if ( bUseAble )
	{
		m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
	}
	else
	{
		m_stItemState[m_nStateCnt].dwFont = RGB(255, 0, 0);
	}
	m_nStateCnt++;

	if ( m_stItemInfo.stStdItem.nNeedFame > 0 )
	{
		sprintf(m_stItemState[m_nStateCnt].pszDesc, g_xMsg.GetMsg(2520), m_stItemInfo.stStdItem.nNeedFame);
		m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);

		if ( g_xGameProc.m_xMyHero.m_nFame >= m_stItemInfo.stStdItem.nNeedFame )
			m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 255);
		else
			m_stItemState[m_nStateCnt].dwFont = RGB(255, 0, 0);

		m_nStateCnt++;
	}
}

VOID CItem::SetWeaponStatus(BOOL bUseStore, BOOL bUseEquip)
{
	INT	 nCnt; 
	BOOL bUseAble  = FALSE;

	// 1. 이름.
	if ( strlen(m_stItemInfo.Prefix) )
	{
		if ( m_stItemInfo.Desc[10] != 0 )
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s (*)%s %s", g_xMsg.GetMsg(2515), m_stItemInfo.Prefix, m_stItemInfo.stStdItem.szName);
		else
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s %s %s", g_xMsg.GetMsg(2515), m_stItemInfo.Prefix, m_stItemInfo.stStdItem.szName);
	}
	else
	{
		if ( m_stItemInfo.Desc[10] != 0 )
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s (*)%s", g_xMsg.GetMsg(2515), m_stItemInfo.stStdItem.szName);
		else
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s %s", g_xMsg.GetMsg(2515), m_stItemInfo.stStdItem.szName);
	}

	m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
	m_stItemState[m_nStateCnt].dwFont = RGB(255, 250,   0);
	m_nStateCnt++;

	// 전용아이템 표시
	if ( (m_stItemInfo.stStdItem.bItemDesc & 128) )
	{
		sprintf(m_stItemState[m_nStateCnt].pszDesc, g_xMsg.GetMsg(2521));
			
		m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
		m_stItemState[m_nStateCnt].dwFont = RGB( 58, 191, 241);
		m_nStateCnt++;
	}

	// 2. 내구.
	INT nDura	 = RoundFunc(m_stItemInfo.nDura, 1000);
	INT nDuraMax = RoundFunc(m_stItemInfo.nDuraMax, 1000);
	if ( bUseStore )
	{
		nDura	 = RoundFunc(m_stItemInfo.nDura, 1000);
		nDuraMax = RoundFunc(m_stItemInfo.stStdItem.wDuraMax, 1000);	
	}
	if ( m_stItemInfo.stStdItem.bStdMode != 54  && m_stItemInfo.stStdItem.bStdMode != 55 /*눈덩이*/ )
	{
		sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d/%d", g_xMsg.GetMsg(2500), nDura, nDuraMax);
	}
	else // 표창.
	{
		nDura	 = RoundFunc(m_stItemInfo.nDura, 100);
		sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d", g_xMsg.GetMsg(2503), nDura);
	}
	m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
	if ( nDura <= 1 ) 
	{
		m_stItemState[m_nStateCnt].dwFont = RGB(255,  50,  50);
	}
	else
	{
		m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 255);
	}
	m_nStateCnt++;

	// 3. 무게.
	sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d", g_xMsg.GetMsg(2501), m_stItemInfo.stStdItem.bWeight);
	m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
	m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
	m_nStateCnt++;

	// 4. 파괴.
	if ( m_stItemInfo.stStdItem.wDC + m_stItemInfo.Desc[0] > 0 )
	{
		m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
		if ( m_stItemInfo.Desc[0] > 0 )
		{
			// 옵션 Plus.
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d-%d (+%d)", g_xMsg.GetMsg(1061), LOBYTE(m_stItemInfo.stStdItem.wDC), HIBYTE(m_stItemInfo.stStdItem.wDC)+m_stItemInfo.Desc[0], m_stItemInfo.Desc[0]);
			m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
		}
		else
		{
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d-%d ", g_xMsg.GetMsg(1061), LOBYTE(m_stItemInfo.stStdItem.wDC), HIBYTE(m_stItemInfo.stStdItem.wDC));
			m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
		}

		if (bUseEquip)
			g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[0] = TRUE;

		m_nStateCnt++;
	}

	// 확장 제련
	if ( m_stItemInfo.Desc[2] > 0 )
	{
		BYTE bDesc = atoi(&m_stItemInfo.Desc[2]);

		BYTE bKind, bLevel;

		bLevel = m_stItemInfo.Desc[2] & 0xF0;
		bLevel = bLevel >> 4;

		bKind = m_stItemInfo.Desc[2] & 0x0F;

		m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
		if ( m_stItemInfo.Desc[2] > 0 )
		{
			// 옵션 Plus.
			sprintf(m_stItemState[m_nStateCnt].pszDesc, g_xMsg.GetMsg(2521+bKind), bLevel);
			m_stItemState[m_nStateCnt].dwFont = RGB(255, 150, 94);
		}
		m_nStateCnt++;
	}

	// 마법
	if ( m_stItemInfo.stStdItem.wMC + m_stItemInfo.Desc[1] > 0 )
	{
		m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
		if ( m_stItemInfo.Desc[1] > 0 )
		{
			// 옵션 Plus.
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d-%d (+%d)", g_xMsg.GetMsg(5100+m_stItemInfo.stStdItem.MCType), LOBYTE(m_stItemInfo.stStdItem.wMC), HIBYTE(m_stItemInfo.stStdItem.wMC)+m_stItemInfo.Desc[1], m_stItemInfo.Desc[1]);
			m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
		}
		else
		{
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d-%d ", g_xMsg.GetMsg(5100+m_stItemInfo.stStdItem.MCType), LOBYTE(m_stItemInfo.stStdItem.wMC), HIBYTE(m_stItemInfo.stStdItem.wMC));
			m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
		}
		m_nStateCnt++;

		if (bUseEquip)
		{
			if (m_stItemInfo.stStdItem.MCType == 0) //전계열
			{
				g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[2] = TRUE;
				g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[3] = TRUE;
			}
			else if (m_stItemInfo.stStdItem.MCType == 1) //자연계열
			{
				g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[2] = TRUE;
			}
			else // 영혼계
			{
				g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[3] = TRUE;
			}
		}
	}

	// 원소 파괴
	if (( m_stItemInfo.Desc[11] > 0 ) || (m_stItemInfo.stStdItem.bAtomDCType> 0))
	{
		byte btAtomType = m_stItemInfo.stStdItem.bAtomDCType;

		if (m_stItemInfo.Desc[11] > 0)
			btAtomType = m_stItemInfo.Desc[11];

		if ( m_stItemInfo.Desc[12] > 0 )
		{
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %s+%d", g_xMsg.GetMsg(5178), g_xMsg.GetMsg(btAtomType+5160), m_stItemInfo.stStdItem.wAtomDC+m_stItemInfo.Desc[12]);
		}
		else
		{
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %s+%d", g_xMsg.GetMsg(5178), g_xMsg.GetMsg(btAtomType+5160), m_stItemInfo.stStdItem.wAtomDC);
		}

		m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 0);

		if (bUseEquip)
			g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[btAtomType+4] = TRUE;

		m_nStateCnt++;
	}

	// 6. 신성 및 강도.
	if ( m_stItemInfo.stStdItem.sSpecialPower + m_stItemInfo.Desc[7] > 0 )
	{
		m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
		if ( m_stItemInfo.stStdItem.bShape == 19 || (m_stItemInfo.stStdItem.bShape == 18 && m_stItemInfo.stStdItem.bStdMode == 56))
		{
			if ( m_stItemInfo.Desc[7] > 0 )
			{
				// 옵션 Plus.
				m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
//				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d (+%d)", g_xMsg.GetMsg(5054), m_stItemInfo.stStdItem.sSpecialPower+m_stItemInfo.Desc[7], m_stItemInfo.Desc[7]);
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d (+%d)", g_xMsg.GetMsg(2504), m_stItemInfo.stStdItem.sSpecialPower+m_stItemInfo.Desc[7], m_stItemInfo.Desc[7]);
			}
			else
			{
				m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
//				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d", g_xMsg.GetMsg(5054), m_stItemInfo.stStdItem.sSpecialPower);
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d", g_xMsg.GetMsg(2504), m_stItemInfo.stStdItem.sSpecialPower);
			}
		}
		else
		{
			if ( m_stItemInfo.Desc[7] > 0 )
			{
				// 옵션 Plus.
				m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d (+%d)", g_xMsg.GetMsg(2504), m_stItemInfo.stStdItem.sSpecialPower+m_stItemInfo.Desc[7], m_stItemInfo.Desc[7]);
			}
			else
			{
				m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d", g_xMsg.GetMsg(2504), m_stItemInfo.stStdItem.sSpecialPower);
			}
		}
		m_nStateCnt++;
	}

	// 7. 정확.
	if ( HIBYTE(m_stItemInfo.stStdItem.wAC) + m_stItemInfo.Desc[5] > 0 )
	{
		m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
		if ( m_stItemInfo.Desc[5] > 0 )
		{
			// 옵션 Plus.
			m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d (+%d)", g_xMsg.GetMsg(1053), HIBYTE(m_stItemInfo.stStdItem.wAC)+m_stItemInfo.Desc[5], m_stItemInfo.Desc[5]);
		}
		else
		{
			INT nAccuracy = HIBYTE(m_stItemInfo.stStdItem.wAC);

			if ( nAccuracy > 100 )
			{
				nAccuracy -= 100;
				nAccuracy = nAccuracy * -1;
			}

			m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d", g_xMsg.GetMsg(1053), nAccuracy);
		}
		m_nStateCnt++;
	}

	// 8. 공격속도.
	if ( HIBYTE(m_stItemInfo.stStdItem.wMAC) + m_stItemInfo.Desc[6] > 0 )
	{
		m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);

		if ( HIBYTE(m_stItemInfo.stStdItem.wMAC) + m_stItemInfo.Desc[6] > 10 )
		{
			if ( m_stItemInfo.Desc[6] > 0 )
			{
				// 옵션 Plus.
				m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%d (+%d)", g_xMsg.GetMsg(2505), HIBYTE(m_stItemInfo.stStdItem.wMAC)-10+m_stItemInfo.Desc[6], m_stItemInfo.Desc[6]-10);
			}
			else
			{
				m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%d", g_xMsg.GetMsg(2505), HIBYTE(m_stItemInfo.stStdItem.wMAC)-10);
			}
		}
		else
		{
			if ( m_stItemInfo.Desc[6] > 0 )
			{
				// 옵션 Plus.
				m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: -%d (-%d)", g_xMsg.GetMsg(2505), HIBYTE(m_stItemInfo.stStdItem.wMAC)+m_stItemInfo.Desc[6], m_stItemInfo.Desc[6]);
			}
			else
			{
				m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: -%d", g_xMsg.GetMsg(2505), HIBYTE(m_stItemInfo.stStdItem.wMAC) );
			}
		}

		m_nStateCnt++;
	}

	// 9. 행운.
	if ( LOBYTE(m_stItemInfo.stStdItem.wAC) + m_stItemInfo.Desc[3] > 0 )
	{
		m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
		if ( m_stItemInfo.Desc[3] > 0 )
		{
			// 옵션 Plus.
			m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%d (+%d)", g_xMsg.GetMsg(2506), LOBYTE(m_stItemInfo.stStdItem.wAC)+m_stItemInfo.Desc[3], m_stItemInfo.Desc[3]);
		}
		else
		{
			m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%d", g_xMsg.GetMsg(2506), LOBYTE(m_stItemInfo.stStdItem.wAC));
		}

		m_nStateCnt++;
	}

	// 10. 저주.
	if ( LOBYTE(m_stItemInfo.stStdItem.wMAC) + m_stItemInfo.Desc[4] > 0 )
	{
		m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
		if ( m_stItemInfo.Desc[4] > 0 )
		{
			// 옵션 Plus.
			m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%d (+%d)", g_xMsg.GetMsg(2507), LOBYTE(m_stItemInfo.stStdItem.wMAC)+m_stItemInfo.Desc[4], m_stItemInfo.Desc[4]);
		}
		else
		{
			m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%d", g_xMsg.GetMsg(2507), LOBYTE(m_stItemInfo.stStdItem.wMAC));
		}
		m_nStateCnt++;
	}

	// 스킬 레벨
	if ( m_stItemInfo.stStdItem.bStdMode != 54 && m_stItemInfo.stStdItem.bStdMode != 55/*눈덩이*/ )	// 표창검사.
	{
		m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
		m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);

		INT	 nLevel = 0;
		for ( INT nCnt=0; nCnt<35; nCnt++ )
		{
			if ( g_nWeaponLevelTable[nCnt] <= m_stItemInfo.bLevel_R && g_nWeaponLevelTable[nCnt+1] > m_stItemInfo.bLevel_R )
			{
				break;
			}
		}

		nLevel = nCnt+1;

		if ( nLevel >= 17 )
		{
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s : MAX", g_xMsg.GetMsg(2508));
			m_nStateCnt++;
		}
		else
		{
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s : %d", g_xMsg.GetMsg(2508), nLevel);

			m_nStateCnt++;

			// 수련치
			UINT  wSwordTrainPoint = m_stItemInfo.wAmount_GB;
			wSwordTrainPoint = wSwordTrainPoint + (60000 * m_stItemInfo.bLevel_R);
			
	//		INT	  nExpIdx = (m_stItemInfo.ColorR + 1) / 4;
			INT	  nExpIdx = nLevel - 1;

			if (nExpIdx > 0)
			{
				for ( INT nIdx=0; nIdx < nLevel-1 && nIdx < 35; nIdx++ )
					wSwordTrainPoint -= g_nWeaponExpTable[nIdx];
			}

			float fPoint = float(wSwordTrainPoint) * 100 / float(g_nWeaponExpTable[nExpIdx]);
			
			m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
			m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s : %.2f %%", g_xMsg.GetMsg(2509), fPoint);
			m_nStateCnt++;
		}
	}
	
	// 11. 필요능력치.
	switch ( m_stItemInfo.stStdItem.bNeed )
	{
		case 0:
		{
			if ( g_xGameProc.m_xMyHero.m_stAbility.bLevel >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}

			if ( m_stItemInfo.stStdItem.bNeedLevel > 100 && g_xGameProc.m_xMyHero.m_stAbility.bLevel >= m_stItemInfo.stStdItem.bNeedLevel - 100 )
			{
			   bUseAble = TRUE;
			}

			if ( m_stItemInfo.stStdItem.bNeedLevel == 0 )
			{
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s", g_xMsg.GetMsg(2516));
			}
			else if ( m_stItemInfo.stStdItem.bNeedLevel > 100 )
			{
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d (%s)", g_xMsg.GetMsg(5140), m_stItemInfo.stStdItem.bNeedLevel-100, g_xMsg.GetMsg(2517));
			}
			else
			{
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d", g_xMsg.GetMsg(5140), m_stItemInfo.stStdItem.bNeedLevel);
			}

			break;
		}
		case 1:
		{
			if ( HIWORD(g_xGameProc.m_xMyHero.m_stAbility.dwDC) >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5141), m_stItemInfo.stStdItem.bNeedLevel);
			break;
		}
		case 2:
		{
			bUseAble = TRUE;
			for ( nCnt = 0; nCnt < 4; nCnt++)
			{
				if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[nCnt]) < m_stItemInfo.stStdItem.bNeedLevel )
				{
					bUseAble = FALSE;
					break;
				}
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5142), m_stItemInfo.stStdItem.bNeedLevel);
			break;
		}
		case 3:
		{
			bUseAble = TRUE;
			for ( nCnt = 4; nCnt < 7; nCnt++)
			{
				if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[nCnt]) < m_stItemInfo.stStdItem.bNeedLevel )
				{
					bUseAble = FALSE;
					break;
				}
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5143), m_stItemInfo.stStdItem.bNeedLevel);
			break;
		}
		case 4:
		{
			bUseAble = TRUE;
			for ( nCnt = 0; nCnt < 7; nCnt++)
			{
				if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[nCnt]) < m_stItemInfo.stStdItem.bNeedLevel )
				{
					bUseAble = FALSE;
					break;
				}
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5144), m_stItemInfo.stStdItem.bNeedLevel);
			break;
		}
		case 5:
		{
			if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[0]) >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5145), m_stItemInfo.stStdItem.bNeedLevel);
			break;
		}
		case 6:
		{
			if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[1]) >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5146), m_stItemInfo.stStdItem.bNeedLevel);
			break;
		}
		case 7:
		{
			if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[2]) >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5147), m_stItemInfo.stStdItem.bNeedLevel);
			break;
		}
		case 8:
		{
			if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[3]) >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5148), m_stItemInfo.stStdItem.bNeedLevel);

			break;
		}
		case 9:
		{
			if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[4]) >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5149), m_stItemInfo.stStdItem.bNeedLevel);

			break;
		}
		case 10:
		{
			if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[5]) >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5150), m_stItemInfo.stStdItem.bNeedLevel);

			break;
		}
		case 11:
		{
			if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[6]) >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5151), m_stItemInfo.stStdItem.bNeedLevel);

			break;
		}
	}
	m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);

	if ( ( m_stItemInfo.stStdItem.bNeed == 0 && m_stItemInfo.stStdItem.bNeedLevel == 0 ||
		 m_stItemInfo.stStdItem.bNeed == 0 && m_stItemInfo.stStdItem.bNeedLevel > 100 ) && bUseAble )
	{
		m_stItemState[m_nStateCnt].dwFont = RGB(  0, 200,   0);
	}
	else if ( bUseAble )
	{
		m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
	}
	else
	{
		m_stItemState[m_nStateCnt].dwFont = RGB(255, 0, 0);
	}
	m_nStateCnt++;

	if ( m_stItemInfo.stStdItem.nNeedFame > 0 )
	{
		sprintf(m_stItemState[m_nStateCnt].pszDesc, g_xMsg.GetMsg(2520), m_stItemInfo.stStdItem.nNeedFame);
		m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);

		if ( g_xGameProc.m_xMyHero.m_nFame >= m_stItemInfo.stStdItem.nNeedFame )
			m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 255);
		else
			m_stItemState[m_nStateCnt].dwFont = RGB(255, 0, 0);

		m_nStateCnt++;
	}
}

VOID CItem::SetAccessoryStatus(BOOL bUseStore, BOOL bUseEquip)
{
	INT	 nCnt; 
	BOOL bUseAble = FALSE;

	// 1. 이름.
	if ( strlen(m_stItemInfo.Prefix) )
	{		
		sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%s %s", g_xMsg.GetMsg(2515), m_stItemInfo.Prefix, m_stItemInfo.stStdItem.szName);
	}
	else
	{
		sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%s", g_xMsg.GetMsg(2515), m_stItemInfo.stStdItem.szName);
	}
	m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
	m_stItemState[m_nStateCnt].dwFont = RGB(255, 250,   0);
	m_nStateCnt++;

	// 2. 내구.
	INT nDura	 = RoundFunc(m_stItemInfo.nDura, 1000);
	INT nDuraMax = RoundFunc(m_stItemInfo.nDuraMax, 1000);
	if ( bUseStore )
	{
		nDura	 = RoundFunc(m_stItemInfo.nDura, 1000);
		nDuraMax = RoundFunc(m_stItemInfo.stStdItem.wDuraMax, 1000);	
	}
	sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d/%d", g_xMsg.GetMsg(2500), nDura, nDuraMax);
	m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
	if ( nDura <= 1 ) 
	{
		m_stItemState[m_nStateCnt].dwFont = RGB(255,  50,  50);
	}
	else
	{
		m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 255);
	}
	m_nStateCnt++;

	// 3. 무게.
	sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d", g_xMsg.GetMsg(2501), m_stItemInfo.stStdItem.bWeight);
	m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
	m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
	m_nStateCnt++;

	// 파괴.
	if ( m_stItemInfo.stStdItem.wDC + m_stItemInfo.Desc[2] > 0 )
	{
		m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
		if ( m_stItemInfo.Desc[2] > 0 )
		{
			// 옵션 Plus.
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d-%d (+%d)", g_xMsg.GetMsg(1061), LOBYTE(m_stItemInfo.stStdItem.wDC), HIBYTE(m_stItemInfo.stStdItem.wDC)+m_stItemInfo.Desc[2], m_stItemInfo.Desc[2]);
			m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
		}
		else
		{
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d-%d ", g_xMsg.GetMsg(1061), LOBYTE(m_stItemInfo.stStdItem.wDC), HIBYTE(m_stItemInfo.stStdItem.wDC));
			m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
		}
		m_nStateCnt++;

		if (bUseEquip)
			g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[0] = TRUE;
	}

	// 4. 특화 상태치.
	switch ( m_stItemInfo.stStdItem.bStdMode )
	{
		case 19:			// 목걸이
		{
			if ( HIBYTE(m_stItemInfo.stStdItem.wAC) + m_stItemInfo.Desc[0] > 0 )
			{
				m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
				if ( m_stItemInfo.Desc[0] > 0 )
				{
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%d%% (+%d%%)", g_xMsg.GetMsg(1055), (HIBYTE(m_stItemInfo.stStdItem.wAC)+m_stItemInfo.Desc[0])*10, m_stItemInfo.Desc[0]*10);
					m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
				}
				else
				{
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%d%%", g_xMsg.GetMsg(1055), HIBYTE(m_stItemInfo.stStdItem.wAC)*10);
					m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
				}
				m_nStateCnt++;
			}

			if ( LOBYTE(m_stItemInfo.stStdItem.wMAC) > 0 )
			{
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%d", g_xMsg.GetMsg(2507), LOBYTE(m_stItemInfo.stStdItem.wMAC));
				m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
				m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
				m_nStateCnt++;
			}

			if ( HIBYTE(m_stItemInfo.stStdItem.wMAC) + m_stItemInfo.Desc[1] > 0 )
			{
				m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
				if ( m_stItemInfo.Desc[1] > 0 )
				{
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%d (+%d)", g_xMsg.GetMsg(2506), HIBYTE(m_stItemInfo.stStdItem.wMAC)+m_stItemInfo.Desc[1], m_stItemInfo.Desc[1]);
					m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
				}
				else
				{
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%d", g_xMsg.GetMsg(2506), HIBYTE(m_stItemInfo.stStdItem.wMAC));		
					m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
				}
				m_nStateCnt++;
			}

			// 공격 원소
			if ( ( m_stItemInfo.Desc[5] > 0 && m_stItemInfo.Desc[6] > 0 ) || 
				 ( m_stItemInfo.Desc[11] > 0 ) || (m_stItemInfo.stStdItem.bAtomDCType> 0) )
			{
				CHAR szTemp[MAX_PATH], szTemp2[MAX_PATH];
				BOOL bFind = FALSE;

				sprintf(szTemp2, "%s:", g_xMsg.GetMsg(5178));

				if (( m_stItemInfo.Desc[11] > 0 ) || (m_stItemInfo.stStdItem.bAtomDCType> 0))
				{
					m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 0);

					byte btAtomType = m_stItemInfo.stStdItem.bAtomDCType;

					if ( btAtomType != m_stItemInfo.Desc[11] && btAtomType != 0 )
					{
						CHAR szTemp3[MAX_PATH];
						sprintf(szTemp3, " %s+%d", g_xMsg.GetMsg(btAtomType+5160), m_stItemInfo.stStdItem.wAtomDC);
						strcat(szTemp2, szTemp3);
					}

					if (m_stItemInfo.Desc[11] > 0)
						btAtomType = m_stItemInfo.Desc[11];

					if ( m_stItemInfo.Desc[12] > 0 )
					{
						bFind = TRUE;
						if ( btAtomType == m_stItemInfo.stStdItem.bAtomDCType )
							sprintf(szTemp, " %s+%d", g_xMsg.GetMsg(btAtomType+5160), m_stItemInfo.stStdItem.wAtomDC+m_stItemInfo.Desc[12]);
						else
							sprintf(szTemp, " %s+%d", g_xMsg.GetMsg(btAtomType+5160), m_stItemInfo.Desc[12]);
					}

					if (bUseEquip)
						g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[btAtomType+4] = TRUE;
				}

				if ( bFind )
					strcat(szTemp2, szTemp);

				bFind = FALSE;

				m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 0);

				BYTE btAtomType = m_stItemInfo.Desc[5];

				if ( m_stItemInfo.Desc[6] > 0 )
				{
					bFind = TRUE;
					sprintf(szTemp, " %s+%d", g_xMsg.GetMsg(btAtomType+5160), m_stItemInfo.Desc[6]);
				
					if (bUseEquip)
						g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[btAtomType+4] = TRUE;
				}

				if ( bFind )
					strcat(szTemp2, szTemp);

				m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 0);
				sprintf(m_stItemState[m_nStateCnt].pszDesc, szTemp2);

				m_nStateCnt++;
			}

			// 강한원소
			if ( m_stItemInfo.stStdItem.sAtomACGood > 0 && m_stItemInfo.stStdItem.sAtomACGood < 7)
			{
				INT nIdx = m_stItemInfo.stStdItem.sAtomACGood;
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %sx1", g_xMsg.GetMsg(5179), g_xMsg.GetMsg(5160+nIdx));
				m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 0);
				m_nStateCnt++;

				if (bUseEquip)
					g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[nIdx+11] = TRUE;
			}

			// 약한원소
			if ( m_stItemInfo.stStdItem.sAtomACBad > 0 && m_stItemInfo.stStdItem.sAtomACBad < 7)
			{
				INT nIdx = m_stItemInfo.stStdItem.sAtomACBad;
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %sx1", g_xMsg.GetMsg(5180), g_xMsg.GetMsg(5160+nIdx));
				m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
				m_nStateCnt++;

				if (bUseEquip)
					g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[nIdx+18] = TRUE;
			}

			break;
		}
		case 20:				// 목걸이
		{
			if ( HIBYTE(m_stItemInfo.stStdItem.wAC) + m_stItemInfo.Desc[0] > 0 )
			{
				m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
				if ( m_stItemInfo.Desc[0] > 0 )
				{
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%d (+%d)", g_xMsg.GetMsg(1053), HIBYTE(m_stItemInfo.stStdItem.wAC)+m_stItemInfo.Desc[0], m_stItemInfo.Desc[0]);
					m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
				}
				else
				{
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%d", g_xMsg.GetMsg(1053), HIBYTE(m_stItemInfo.stStdItem.wAC));
					m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
				}
				m_nStateCnt++;
			}
	
			if ( HIBYTE(m_stItemInfo.stStdItem.wMAC) + m_stItemInfo.Desc[1] > 0 )
			{
				m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
				if ( m_stItemInfo.Desc[1] > 0 )
				{
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%d (+%d)", g_xMsg.GetMsg(1054), HIBYTE(m_stItemInfo.stStdItem.wMAC)+m_stItemInfo.Desc[1], m_stItemInfo.Desc[1]);
					m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
				}
				else
				{
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%d", g_xMsg.GetMsg(1054), HIBYTE(m_stItemInfo.stStdItem.wMAC));
					m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
				}
				m_nStateCnt++;
			}

			// 공격 원소
			if ( ( m_stItemInfo.Desc[5] > 0 && m_stItemInfo.Desc[6] > 0 ) || 
				 ( m_stItemInfo.Desc[11] > 0 ) || (m_stItemInfo.stStdItem.bAtomDCType> 0) )
			{
				CHAR szTemp[MAX_PATH], szTemp2[MAX_PATH];
				BOOL bFind = FALSE;

				sprintf(szTemp2, "%s:", g_xMsg.GetMsg(5178));

				if (( m_stItemInfo.Desc[11] > 0 ) || (m_stItemInfo.stStdItem.bAtomDCType> 0))
				{
					m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 0);

					byte btAtomType = m_stItemInfo.stStdItem.bAtomDCType;

					if ( btAtomType != m_stItemInfo.Desc[11] && btAtomType != 0 )
					{
						CHAR szTemp3[MAX_PATH];
						sprintf(szTemp3, " %s+%d", g_xMsg.GetMsg(btAtomType+5160), m_stItemInfo.stStdItem.wAtomDC);
						strcat(szTemp2, szTemp3);
					}

					if (m_stItemInfo.Desc[11] > 0)
						btAtomType = m_stItemInfo.Desc[11];

					if ( m_stItemInfo.Desc[12] > 0 )
					{
						bFind = TRUE;
						if ( btAtomType == m_stItemInfo.stStdItem.bAtomDCType )
							sprintf(szTemp, " %s+%d", g_xMsg.GetMsg(btAtomType+5160), m_stItemInfo.stStdItem.wAtomDC+m_stItemInfo.Desc[12]);
						else
							sprintf(szTemp, " %s+%d", g_xMsg.GetMsg(btAtomType+5160), m_stItemInfo.Desc[12]);
					}

					if (bUseEquip)
						g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[btAtomType+4] = TRUE;
				}

				if ( bFind )
					strcat(szTemp2, szTemp);

				bFind = FALSE;

				m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 0);

				BYTE btAtomType = m_stItemInfo.Desc[5];

				if ( m_stItemInfo.Desc[6] > 0 )
				{
					bFind = TRUE;
					sprintf(szTemp, " %s+%d", g_xMsg.GetMsg(btAtomType+5160), m_stItemInfo.Desc[6]);
				
					if (bUseEquip)
						g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[btAtomType+4] = TRUE;
				}

				if ( bFind )
					strcat(szTemp2, szTemp);

				m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 0);
				sprintf(m_stItemState[m_nStateCnt].pszDesc, szTemp2);

				m_nStateCnt++;
			}

			// 강한원소
			if ( m_stItemInfo.stStdItem.sAtomACGood > 0 && m_stItemInfo.stStdItem.sAtomACGood < 7)
			{
				INT nIdx = m_stItemInfo.stStdItem.sAtomACGood;
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %sx1", g_xMsg.GetMsg(5179), g_xMsg.GetMsg(5160+nIdx));
				m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 0);
				m_nStateCnt++;

				if (bUseEquip)
					g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[nIdx+11] = TRUE;
			}

			// 약한원소
			if ( m_stItemInfo.stStdItem.sAtomACBad > 0 && m_stItemInfo.stStdItem.sAtomACBad < 7)
			{
				INT nIdx = m_stItemInfo.stStdItem.sAtomACBad;
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %sx1", g_xMsg.GetMsg(5180), g_xMsg.GetMsg(5160+nIdx));
				m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
				m_nStateCnt++;

				if (bUseEquip)
					g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[nIdx+18] = TRUE;
			}

			break;
		}
		case 24: 		// 팔찌
		{
			if ( HIBYTE(m_stItemInfo.stStdItem.wAC) + m_stItemInfo.Desc[0] > 0 )
			{
				m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
				if ( m_stItemInfo.Desc[0] > 0 )
				{
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%d (+%d)", g_xMsg.GetMsg(1053), HIBYTE(m_stItemInfo.stStdItem.wAC)+m_stItemInfo.Desc[0], m_stItemInfo.Desc[0]);
					m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
				}
				else
				{
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%d", g_xMsg.GetMsg(1053), HIBYTE(m_stItemInfo.stStdItem.wAC));
					m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
				}
				m_nStateCnt++;
			}
	
			if ( HIBYTE(m_stItemInfo.stStdItem.wMAC) + m_stItemInfo.Desc[1] > 0 )
			{
				m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
				if ( m_stItemInfo.Desc[1] > 0 )
				{
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%d (+%d)", g_xMsg.GetMsg(1054), HIBYTE(m_stItemInfo.stStdItem.wMAC)+m_stItemInfo.Desc[1], m_stItemInfo.Desc[1]);
					m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
				}
				else
				{
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%d", g_xMsg.GetMsg(1054), HIBYTE(m_stItemInfo.stStdItem.wMAC));
					m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
				}
				m_nStateCnt++;
			}

			// 원소 파괴
			if (( m_stItemInfo.Desc[11] > 0 ) || (m_stItemInfo.stStdItem.bAtomDCType> 0))
			{
				CHAR szTemp[MAX_PATH], szTemp2[MAX_PATH];

				sprintf(szTemp2, "%s:", g_xMsg.GetMsg(5178));
				m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 0);

				byte btAtomType = m_stItemInfo.stStdItem.bAtomDCType;

				if ( btAtomType != m_stItemInfo.Desc[11] && btAtomType != 0 )
				{
					CHAR szTemp3[MAX_PATH];
					sprintf(szTemp3, " %s+%d", g_xMsg.GetMsg(btAtomType+5160), m_stItemInfo.stStdItem.wAtomDC);
					strcat(szTemp2, szTemp3);
				}

				if (m_stItemInfo.Desc[11] > 0)
					btAtomType = m_stItemInfo.Desc[11];

				if ( m_stItemInfo.Desc[12] > 0 )
				{
					if ( btAtomType == m_stItemInfo.stStdItem.bAtomDCType )
						sprintf(szTemp, " %s+%d", g_xMsg.GetMsg(btAtomType+5160), m_stItemInfo.stStdItem.wAtomDC+m_stItemInfo.Desc[12]);
					else
						sprintf(szTemp, " %s+%d", g_xMsg.GetMsg(btAtomType+5160), m_stItemInfo.Desc[12]);

					strcat(szTemp2, szTemp);
				}
				
				m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 0);
				sprintf(m_stItemState[m_nStateCnt].pszDesc, szTemp2);

				if (bUseEquip)
					g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[btAtomType+4] = TRUE;

				m_nStateCnt++;
			}


			// 강한원소
			if ( m_stItemInfo.Desc[5] > 0 || m_stItemInfo.stStdItem.sAtomACGood )
			{
				INT nMask = 1;
				CHAR szTemp[MAX_PATH], szTemp2[MAX_PATH];
				BOOL bFind = FALSE;

				sprintf(szTemp2, "%s:", g_xMsg.GetMsg(5179));

				for ( INT nI=0; nI<7; nI++)
				{
					BOOL bCheck = FALSE;
					if ( m_stItemInfo.Desc[5] & nMask )
					{
						bCheck = TRUE;
						bFind = TRUE;
						if ( m_stItemInfo.stStdItem.sAtomACGood == nI+1 )
							sprintf(szTemp, " %sx2", g_xMsg.GetMsg(5161+nI));
						else
							sprintf(szTemp, " %sx1", g_xMsg.GetMsg(5161+nI));

						if (bUseEquip)
							g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[12+nI] = TRUE;

					}
					else if ( m_stItemInfo.stStdItem.sAtomACGood == nI+1 )
					{
						bCheck = TRUE;
						bFind = TRUE;
						sprintf(szTemp, " %sx1", g_xMsg.GetMsg(5161+nI));

						if (bUseEquip)
							g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[12+nI] = TRUE;
					}

					if ( bCheck )
						strcat(szTemp2, szTemp);

					nMask <<= 1;
				}

				if ( bFind )
				{
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s", szTemp2);
					m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 0);
					m_nStateCnt++;
				}
			}
			
			// 약한원소
			if ( m_stItemInfo.Desc[6] > 0 || m_stItemInfo.stStdItem.sAtomACBad )
			{
				INT nMask = 1;
				CHAR szTemp[MAX_PATH], szTemp2[MAX_PATH];
				BOOL bFind = FALSE;

				sprintf(szTemp2, "%s:", g_xMsg.GetMsg(5180));

				for ( INT nI=0; nI<7; nI++)
				{
					BOOL bCheck = FALSE;
					if ( m_stItemInfo.Desc[6] & nMask )
					{
						bCheck = TRUE;
						bFind = TRUE;
						if ( m_stItemInfo.stStdItem.sAtomACBad == nI+1 )
							sprintf(szTemp, " %sx2", g_xMsg.GetMsg(5161+nI));
						else
							sprintf(szTemp, " %sx1", g_xMsg.GetMsg(5161+nI));

						if (bUseEquip)
							g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[19+nI] = TRUE;

					}
					else if ( m_stItemInfo.stStdItem.sAtomACBad == nI+1 )
					{
						bCheck = TRUE;
						bFind = TRUE;
						sprintf(szTemp, " %sx1", g_xMsg.GetMsg(5161+nI));

						if (bUseEquip)
							g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[19+nI] = TRUE;
					}

					if ( bCheck )
						strcat(szTemp2, szTemp);

					nMask <<= 1;
				}

				if ( bFind )
				{
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s", szTemp2);
					m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
					m_nStateCnt++;
				}
			}
			break;
		}
		case 21:				// 목걸이
		{
			if ( HIBYTE(m_stItemInfo.stStdItem.wAC) + m_stItemInfo.Desc[0] > 0 )
			{
				m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
				if ( m_stItemInfo.Desc[0] > 0 )
				{
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%d%% (+%d%%)", g_xMsg.GetMsg(1058), (HIBYTE(m_stItemInfo.stStdItem.wAC)+m_stItemInfo.Desc[0])*10, m_stItemInfo.Desc[0]*10);
					m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
				}
				else
				{
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%d%%", g_xMsg.GetMsg(1058), HIBYTE(m_stItemInfo.stStdItem.wAC)*10);
					m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
				}
				m_nStateCnt++;
			}
			if ( HIBYTE(m_stItemInfo.stStdItem.wMAC) + m_stItemInfo.Desc[1] > 0 )
			{
				m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
				if ( m_stItemInfo.Desc[1] > 0 )
				{
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%d%% (+%d%%)", g_xMsg.GetMsg(1059), (HIBYTE(m_stItemInfo.stStdItem.wMAC)+m_stItemInfo.Desc[1])*10, m_stItemInfo.Desc[1]*10);
					m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
				}
				else
				{
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%d%%", g_xMsg.GetMsg(1059), HIBYTE(m_stItemInfo.stStdItem.wMAC)*10);
					m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
				}
				m_nStateCnt++;
			}

			// 공격 원소
			if ( ( m_stItemInfo.Desc[5] > 0 && m_stItemInfo.Desc[6] > 0 ) || 
				 ( m_stItemInfo.Desc[11] > 0 ) || (m_stItemInfo.stStdItem.bAtomDCType> 0) )
			{
				CHAR szTemp[MAX_PATH], szTemp2[MAX_PATH];
				BOOL bFind = FALSE;

				sprintf(szTemp2, "%s:", g_xMsg.GetMsg(5178));

				if (( m_stItemInfo.Desc[11] > 0 ) || (m_stItemInfo.stStdItem.bAtomDCType> 0))
				{
					m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 0);

					byte btAtomType = m_stItemInfo.stStdItem.bAtomDCType;

					if ( btAtomType != m_stItemInfo.Desc[11] && btAtomType != 0 )
					{
						CHAR szTemp3[MAX_PATH];
						sprintf(szTemp3, " %s+%d", g_xMsg.GetMsg(btAtomType+5160), m_stItemInfo.stStdItem.wAtomDC);
						strcat(szTemp2, szTemp3);
					}

					if (m_stItemInfo.Desc[11] > 0)
						btAtomType = m_stItemInfo.Desc[11];

					if ( m_stItemInfo.Desc[12] > 0 )
					{
						bFind = TRUE;
						if ( btAtomType == m_stItemInfo.stStdItem.bAtomDCType )
							sprintf(szTemp, " %s+%d", g_xMsg.GetMsg(btAtomType+5160), m_stItemInfo.stStdItem.wAtomDC+m_stItemInfo.Desc[12]);
						else
							sprintf(szTemp, " %s+%d", g_xMsg.GetMsg(btAtomType+5160), m_stItemInfo.Desc[12]);
					}

					if (bUseEquip)
						g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[btAtomType+4] = TRUE;
				}

				if ( bFind )
					strcat(szTemp2, szTemp);

				bFind = FALSE;

				m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 0);

				BYTE btAtomType = m_stItemInfo.Desc[5];

				if ( m_stItemInfo.Desc[6] > 0 )
				{
					bFind = TRUE;
					sprintf(szTemp, " %s+%d", g_xMsg.GetMsg(btAtomType+5160), m_stItemInfo.Desc[6]);
				
					if (bUseEquip)
						g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[btAtomType+4] = TRUE;
				}

				if ( bFind )
					strcat(szTemp2, szTemp);

				m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 0);
				sprintf(m_stItemState[m_nStateCnt].pszDesc, szTemp2);

				m_nStateCnt++;
			}

			// 강한원소
			if ( m_stItemInfo.stStdItem.sAtomACGood > 0 && m_stItemInfo.stStdItem.sAtomACGood < 7)
			{
				INT nIdx = m_stItemInfo.stStdItem.sAtomACGood;
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %sx1", g_xMsg.GetMsg(5179), g_xMsg.GetMsg(5160+nIdx));
				m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 0);
				m_nStateCnt++;

				if (bUseEquip)
					g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[nIdx+11] = TRUE;
			}

			// 약한원소
			if ( m_stItemInfo.stStdItem.sAtomACBad > 0 && m_stItemInfo.stStdItem.sAtomACBad < 7)
			{
				INT nIdx = m_stItemInfo.stStdItem.sAtomACBad;
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %sx1", g_xMsg.GetMsg(5180), g_xMsg.GetMsg(5160+nIdx));
				m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
				m_nStateCnt++;

				if (bUseEquip)
					g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[nIdx+18] = TRUE;
			}

			if ( LOBYTE(m_stItemInfo.stStdItem.wAC) > 0 )
			{
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%d ", g_xMsg.GetMsg(2505), LOBYTE(m_stItemInfo.stStdItem.wAC));
				m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
				m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
				m_nStateCnt++;
			}
			if ( LOBYTE(m_stItemInfo.stStdItem.wMAC) > 0 )
			{
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: -%d ", g_xMsg.GetMsg(2505), LOBYTE(m_stItemInfo.stStdItem.wMAC));
				m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
				m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
				m_nStateCnt++;
			}
			break;
		}
		case 23:					// 반지(중독회피?)
		{
			if ( HIBYTE(m_stItemInfo.stStdItem.wAC) + m_stItemInfo.Desc[0] > 0 )
			{
				m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
				if ( m_stItemInfo.Desc[0] > 0 )
				{
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%d%% (+%d%%)", g_xMsg.GetMsg(1056), (HIBYTE(m_stItemInfo.stStdItem.wAC)+m_stItemInfo.Desc[0])*10, m_stItemInfo.Desc[0]*10) ;
					m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
				}
				else
				{
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%d%% ", g_xMsg.GetMsg(1056), HIBYTE(m_stItemInfo.stStdItem.wAC)*10);
					m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
				}
				m_nStateCnt++;
			}
			if ( HIBYTE(m_stItemInfo.stStdItem.wMAC) + m_stItemInfo.Desc[1] > 0 )
			{
				m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
				if ( m_stItemInfo.Desc[1] > 0 )
				{
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%d%% (+%d%%)", g_xMsg.GetMsg(1057), (HIBYTE(m_stItemInfo.stStdItem.wMAC)+m_stItemInfo.Desc[1])*10, m_stItemInfo.Desc[1]*10);
					m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
				}
				else
				{
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%d%% ", g_xMsg.GetMsg(1057), HIBYTE(m_stItemInfo.stStdItem.wMAC)*10);
					m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
				}
				m_nStateCnt++;
			}

			// 공격 원소
			if ( ( m_stItemInfo.Desc[5] > 0 && m_stItemInfo.Desc[6] > 0 ) || 
				 ( m_stItemInfo.Desc[11] > 0 ) || (m_stItemInfo.stStdItem.bAtomDCType> 0) )
			{
				CHAR szTemp[MAX_PATH], szTemp2[MAX_PATH];
				BOOL bFind = FALSE;

				sprintf(szTemp2, "%s:", g_xMsg.GetMsg(5178));

				if (( m_stItemInfo.Desc[11] > 0 ) || (m_stItemInfo.stStdItem.bAtomDCType> 0))
				{
					m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 0);

					byte btAtomType = m_stItemInfo.stStdItem.bAtomDCType;

					if ( btAtomType != m_stItemInfo.Desc[11] && btAtomType != 0 )
					{
						CHAR szTemp3[MAX_PATH];
						sprintf(szTemp3, " %s+%d", g_xMsg.GetMsg(btAtomType+5160), m_stItemInfo.stStdItem.wAtomDC);
						strcat(szTemp2, szTemp3);
					}

					if (m_stItemInfo.Desc[11] > 0)
						btAtomType = m_stItemInfo.Desc[11];

					if ( m_stItemInfo.Desc[12] > 0 )
					{
						bFind = TRUE;
						if ( btAtomType == m_stItemInfo.stStdItem.bAtomDCType )
							sprintf(szTemp, " %s+%d", g_xMsg.GetMsg(btAtomType+5160), m_stItemInfo.stStdItem.wAtomDC+m_stItemInfo.Desc[12]);
						else
							sprintf(szTemp, " %s+%d", g_xMsg.GetMsg(btAtomType+5160), m_stItemInfo.Desc[12]);
					}

					if (bUseEquip)
						g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[btAtomType+4] = TRUE;
				}

				if ( bFind )
					strcat(szTemp2, szTemp);

				bFind = FALSE;

				m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 0);

				BYTE btAtomType = m_stItemInfo.Desc[5];

				if ( m_stItemInfo.Desc[6] > 0 )
				{
					bFind = TRUE;
					sprintf(szTemp, " %s+%d", g_xMsg.GetMsg(btAtomType+5160), m_stItemInfo.Desc[6]);
				
					if (bUseEquip)
						g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[btAtomType+4] = TRUE;
				}

				if ( bFind )
					strcat(szTemp2, szTemp);

				m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 0);
				sprintf(m_stItemState[m_nStateCnt].pszDesc, szTemp2);

				m_nStateCnt++;
			}

			// 강한원소
			if ( m_stItemInfo.stStdItem.sAtomACGood > 0 && m_stItemInfo.stStdItem.sAtomACGood < 7)
			{
				INT nIdx = m_stItemInfo.stStdItem.sAtomACGood;
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %sx1", g_xMsg.GetMsg(5179), g_xMsg.GetMsg(5160+nIdx));
				m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 0);
				m_nStateCnt++;

				if (bUseEquip)
					g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[nIdx+11] = TRUE;
			}

			// 약한원소
			if ( m_stItemInfo.stStdItem.sAtomACBad > 0 && m_stItemInfo.stStdItem.sAtomACBad < 7)
			{
				INT nIdx = m_stItemInfo.stStdItem.sAtomACBad;
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %sx1", g_xMsg.GetMsg(5180), g_xMsg.GetMsg(5160+nIdx));
				m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
				m_nStateCnt++;

				if (bUseEquip)
					g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[nIdx+18] = TRUE;
			}

			if ( LOBYTE(m_stItemInfo.stStdItem.wAC) > 0 )
			{
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%d ", g_xMsg.GetMsg(2505), LOBYTE(m_stItemInfo.stStdItem.wAC));
				m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
				m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
				m_nStateCnt++;
			}
			if ( LOBYTE(m_stItemInfo.stStdItem.wMAC) > 0 )
			{				
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: -%d ", g_xMsg.GetMsg(2505), LOBYTE(m_stItemInfo.stStdItem.wMAC));
				m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
				m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
				m_nStateCnt++;
			}
			break;
		}
		case 15: case 26:
		{
			// 방어.
			m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);

			if ( m_stItemInfo.stStdItem.wAC + m_stItemInfo.Desc[0] > 0 )
			{
				if (m_stItemInfo.Desc[0] > 0)
				{
					// 옵션 Plus.
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d-%d (+%d)", g_xMsg.GetMsg(5177), LOBYTE(m_stItemInfo.stStdItem.wAC), HIBYTE(m_stItemInfo.stStdItem.wAC)+m_stItemInfo.Desc[0], m_stItemInfo.Desc[0]);
					m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
				}
				else
				{
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d-%d", g_xMsg.GetMsg(5177), LOBYTE(m_stItemInfo.stStdItem.wAC), HIBYTE(m_stItemInfo.stStdItem.wAC));
					m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
				}
				m_nStateCnt++;

				if (bUseEquip)
					g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[1] = TRUE;

			}
			
			// 마항.
			if ( m_stItemInfo.stStdItem.wMAC + m_stItemInfo.Desc[1] > 0 )
			{
				if ( m_stItemInfo.Desc[1] > 0)
				{
					// 옵션 Plus.
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d-%d (+%d)", g_xMsg.GetMsg(1406), LOBYTE(m_stItemInfo.stStdItem.wMAC), HIBYTE(m_stItemInfo.stStdItem.wMAC)+m_stItemInfo.Desc[1], m_stItemInfo.Desc[1]);
					m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
				}
				else
				{
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d-%d", g_xMsg.GetMsg(1406), LOBYTE(m_stItemInfo.stStdItem.wMAC), HIBYTE(m_stItemInfo.stStdItem.wMAC));
					m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
				}
				m_nStateCnt++;

				if (bUseEquip)
					g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[4] = TRUE;
			}
			
			// 원소 파괴
			if (( m_stItemInfo.Desc[11] > 0 ) || (m_stItemInfo.stStdItem.bAtomDCType> 0))
			{
				CHAR szTemp[MAX_PATH], szTemp2[MAX_PATH];

				sprintf(szTemp2, "%s:", g_xMsg.GetMsg(5178));
				m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 0);

				byte btAtomType = m_stItemInfo.stStdItem.bAtomDCType;

				if ( btAtomType != m_stItemInfo.Desc[11] && btAtomType != 0 )
				{
					CHAR szTemp3[MAX_PATH];
					sprintf(szTemp3, " %s+%d", g_xMsg.GetMsg(btAtomType+5160), m_stItemInfo.stStdItem.wAtomDC);
					strcat(szTemp2, szTemp3);
				}

				if (m_stItemInfo.Desc[11] > 0)
					btAtomType = m_stItemInfo.Desc[11];

				if ( m_stItemInfo.Desc[12] > 0 )
				{
					if ( btAtomType == m_stItemInfo.stStdItem.bAtomDCType )
						sprintf(szTemp, " %s+%d", g_xMsg.GetMsg(btAtomType+5160), m_stItemInfo.stStdItem.wAtomDC+m_stItemInfo.Desc[12]);
					else
						sprintf(szTemp, " %s+%d", g_xMsg.GetMsg(btAtomType+5160), m_stItemInfo.Desc[12]);
					strcat(szTemp2, szTemp);
				}
				
				m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 0);
				sprintf(m_stItemState[m_nStateCnt].pszDesc, szTemp2);

				if (bUseEquip)
					g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[btAtomType+4] = TRUE;

				m_nStateCnt++;
			}


			// 강한원소
			if ( m_stItemInfo.Desc[5] > 0 || m_stItemInfo.stStdItem.sAtomACGood )
			{
				INT nMask = 1;
				CHAR szTemp[MAX_PATH], szTemp2[MAX_PATH];
				BOOL bFind = FALSE;

				sprintf(szTemp2, "%s:", g_xMsg.GetMsg(5179));

				for ( INT nI=0; nI<7; nI++)
				{
					BOOL bCheck = FALSE;
					if ( m_stItemInfo.Desc[5] & nMask )
					{
						bCheck = TRUE;
						bFind = TRUE;
						if ( m_stItemInfo.stStdItem.sAtomACGood == nI+1 )
							sprintf(szTemp, " %sx2", g_xMsg.GetMsg(5161+nI));
						else
							sprintf(szTemp, " %sx1", g_xMsg.GetMsg(5161+nI));

						if (bUseEquip)
							g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[12+nI] = TRUE;

					}
					else if ( m_stItemInfo.stStdItem.sAtomACGood == nI+1 )
					{
						bCheck = TRUE;
						bFind = TRUE;
						sprintf(szTemp, " %sx1", g_xMsg.GetMsg(5161+nI));

						if (bUseEquip)
							g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[12+nI] = TRUE;
					}

					if ( bCheck )
						strcat(szTemp2, szTemp);

					nMask <<= 1;
				}

				if ( bFind )
				{
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s", szTemp2);
					m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 0);
					m_nStateCnt++;
				}
			}
			
			// 약한원소
			if ( m_stItemInfo.Desc[6] > 0 || m_stItemInfo.stStdItem.sAtomACBad )
			{
				INT nMask = 1;
				CHAR szTemp[MAX_PATH], szTemp2[MAX_PATH];
				BOOL bFind = FALSE;

				sprintf(szTemp2, "%s:", g_xMsg.GetMsg(5180));

				for ( INT nI=0; nI<7; nI++)
				{
					BOOL bCheck = FALSE;
					if ( m_stItemInfo.Desc[6] & nMask )
					{
						bCheck = TRUE;
						bFind = TRUE;
						if ( m_stItemInfo.stStdItem.sAtomACBad == nI+1 )
							sprintf(szTemp, " %sx2", g_xMsg.GetMsg(5161+nI));
						else
							sprintf(szTemp, " %sx1", g_xMsg.GetMsg(5161+nI));

						if (bUseEquip)
							g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[19+nI] = TRUE;

					}
					else if ( m_stItemInfo.stStdItem.sAtomACBad == nI+1 )
					{
						bCheck = TRUE;
						bFind = TRUE;
						sprintf(szTemp, " %sx1", g_xMsg.GetMsg(5161+nI));

						if (bUseEquip)
							g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[19+nI] = TRUE;
					}

					if ( bCheck )
						strcat(szTemp2, szTemp);

					nMask <<= 1;
				}

				if ( bFind )
				{
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s", szTemp2);
					m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
					m_nStateCnt++;
				}
			}
			break;
		}
		case 28:	// 낙인 - 원보상점 - 2006.07.06 추가
		case 22:
		{
			// 방어.
			m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);

			if ( m_stItemInfo.stStdItem.wAC + m_stItemInfo.Desc[0] > 0 )
			{
				if (m_stItemInfo.Desc[0] > 0)
				{
					// 옵션 Plus.
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d-%d (+%d)", g_xMsg.GetMsg(5177), LOBYTE(m_stItemInfo.stStdItem.wAC), HIBYTE(m_stItemInfo.stStdItem.wAC)+m_stItemInfo.Desc[0], m_stItemInfo.Desc[0]);
					m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
				}
				else
				{
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d-%d", g_xMsg.GetMsg(5177), LOBYTE(m_stItemInfo.stStdItem.wAC), HIBYTE(m_stItemInfo.stStdItem.wAC));
					m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
				}
				m_nStateCnt++;

				if (bUseEquip)
					g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[1] = TRUE;

			}
			
			// 마항.
			if ( m_stItemInfo.stStdItem.wMAC + m_stItemInfo.Desc[1] > 0 )
			{
				if ( m_stItemInfo.Desc[1] > 0)
				{
					// 옵션 Plus.
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d-%d (+%d)", g_xMsg.GetMsg(1406), LOBYTE(m_stItemInfo.stStdItem.wMAC), HIBYTE(m_stItemInfo.stStdItem.wMAC)+m_stItemInfo.Desc[1], m_stItemInfo.Desc[1]);
					m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
				}
				else
				{
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d-%d", g_xMsg.GetMsg(1406), LOBYTE(m_stItemInfo.stStdItem.wMAC), HIBYTE(m_stItemInfo.stStdItem.wMAC));
					m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
				}
				m_nStateCnt++;

				if (bUseEquip)
					g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[4] = TRUE;
			}

			// 공격 원소
			if ( ( m_stItemInfo.Desc[5] > 0 && m_stItemInfo.Desc[6] > 0 ) || 
				 ( m_stItemInfo.Desc[11] > 0 ) || (m_stItemInfo.stStdItem.bAtomDCType> 0) )
			{
				CHAR szTemp[MAX_PATH], szTemp2[MAX_PATH];
				BOOL bFind = FALSE;

				sprintf(szTemp2, "%s:", g_xMsg.GetMsg(5178));

				if (( m_stItemInfo.Desc[11] > 0 ) || (m_stItemInfo.stStdItem.bAtomDCType> 0))
				{
					m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 0);

					byte btAtomType = m_stItemInfo.stStdItem.bAtomDCType;

					if ( btAtomType != m_stItemInfo.Desc[11] && btAtomType != 0 )
					{
						CHAR szTemp3[MAX_PATH];
						sprintf(szTemp3, " %s+%d", g_xMsg.GetMsg(btAtomType+5160), m_stItemInfo.stStdItem.wAtomDC);
						strcat(szTemp2, szTemp3);
					}

					if (m_stItemInfo.Desc[11] > 0)
						btAtomType = m_stItemInfo.Desc[11];

					if ( m_stItemInfo.Desc[12] > 0 )
					{
						bFind = TRUE;
						if ( btAtomType == m_stItemInfo.stStdItem.bAtomDCType )
							sprintf(szTemp, " %s+%d", g_xMsg.GetMsg(btAtomType+5160), m_stItemInfo.stStdItem.wAtomDC+m_stItemInfo.Desc[12]);
						else
							sprintf(szTemp, " %s+%d", g_xMsg.GetMsg(btAtomType+5160), m_stItemInfo.Desc[12]);
					}

					if (bUseEquip)
						g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[btAtomType+4] = TRUE;
				}

				if ( bFind )
					strcat(szTemp2, szTemp);

				bFind = FALSE;

				m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 0);

				BYTE btAtomType = m_stItemInfo.Desc[5];

				if ( m_stItemInfo.Desc[6] > 0 )
				{
					bFind = TRUE;
					sprintf(szTemp, " %s+%d", g_xMsg.GetMsg(btAtomType+5160), m_stItemInfo.Desc[6]);
				
					if (bUseEquip)
						g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[btAtomType+4] = TRUE;
				}

				if ( bFind )
					strcat(szTemp2, szTemp);

				m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 0);
				sprintf(m_stItemState[m_nStateCnt].pszDesc, szTemp2);

				m_nStateCnt++;
			}

			// 강한원소
			if ( m_stItemInfo.stStdItem.sAtomACGood > 0 && m_stItemInfo.stStdItem.sAtomACGood < 7)
			{
				INT nIdx = m_stItemInfo.stStdItem.sAtomACGood;
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %sx1", g_xMsg.GetMsg(5179), g_xMsg.GetMsg(5160+nIdx));
				m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 0);
				m_nStateCnt++;

				if (bUseEquip)
					g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[nIdx+11] = TRUE;
			}

			// 약한원소
			if ( m_stItemInfo.stStdItem.sAtomACBad > 0 && m_stItemInfo.stStdItem.sAtomACBad < 7)
			{
				INT nIdx = m_stItemInfo.stStdItem.sAtomACBad;
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %sx1", g_xMsg.GetMsg(5180), g_xMsg.GetMsg(5160+nIdx));
				m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
				m_nStateCnt++;

				if (bUseEquip)
					g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[nIdx+18] = TRUE;
			}
			break;
		}
	}

	// 마법
	if ( m_stItemInfo.stStdItem.wMC + m_stItemInfo.Desc[3] > 0 )
	{
		m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
		if ( m_stItemInfo.Desc[3] > 0 )
		{
			// 옵션 Plus.
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d-%d (+%d)", g_xMsg.GetMsg(5100+m_stItemInfo.stStdItem.MCType), LOBYTE(m_stItemInfo.stStdItem.wMC), HIBYTE(m_stItemInfo.stStdItem.wMC)+m_stItemInfo.Desc[3], m_stItemInfo.Desc[3]);
			m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
		}
		else
		{
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d-%d ", g_xMsg.GetMsg(5100+m_stItemInfo.stStdItem.MCType), LOBYTE(m_stItemInfo.stStdItem.wMC), HIBYTE(m_stItemInfo.stStdItem.wMC));
			m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
		}
		m_nStateCnt++;

		if (bUseEquip)
		{
			if (m_stItemInfo.stStdItem.MCType == 0) //전계열
			{
				g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[2] = TRUE;
				g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[3] = TRUE;
			}
			else if (m_stItemInfo.stStdItem.MCType == 1) //자연계열
			{
				g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[2] = TRUE;
			}
			else // 영혼계
			{
				g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[3] = TRUE;
			}
		}
	}

	// 7. 필요능력치.
	switch ( m_stItemInfo.stStdItem.bNeed )
	{
		case 0:
		{
			if ( g_xGameProc.m_xMyHero.m_stAbility.bLevel >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}

			if ( m_stItemInfo.stStdItem.bNeedLevel > 100 && g_xGameProc.m_xMyHero.m_stAbility.bLevel >= m_stItemInfo.stStdItem.bNeedLevel - 100 )
			{
			   bUseAble = TRUE;
			}

			if ( m_stItemInfo.stStdItem.bNeedLevel == 0 )
			{
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s", g_xMsg.GetMsg(2516));
			}
			else if ( m_stItemInfo.stStdItem.bNeedLevel > 100 )
			{
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d (%s)", g_xMsg.GetMsg(5140), m_stItemInfo.stStdItem.bNeedLevel-100, g_xMsg.GetMsg(2517));
			}
			else
			{
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d", g_xMsg.GetMsg(5140), m_stItemInfo.stStdItem.bNeedLevel);
			}

			break;
		}
		case 1:
		{
			if ( HIWORD(g_xGameProc.m_xMyHero.m_stAbility.dwDC) >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5141), m_stItemInfo.stStdItem.bNeedLevel);
			break;
		}
		case 2:
		{
			bUseAble = TRUE;
			if ( HIWORD(g_xGameProc.m_xMyHero.m_stAbility.dwMC) < m_stItemInfo.stStdItem.bNeedLevel )
				bUseAble = FALSE;
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5142), m_stItemInfo.stStdItem.bNeedLevel);
			break;
		}
		case 3:
		{
			bUseAble = TRUE;
			if ( HIWORD(g_xGameProc.m_xMyHero.m_stAbility.dwSC) < m_stItemInfo.stStdItem.bNeedLevel )
				bUseAble = FALSE;
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5143), m_stItemInfo.stStdItem.bNeedLevel);
			break;
		}
		case 4:
		{
			bUseAble = TRUE;
			for ( nCnt = 0; nCnt < 7; nCnt++)
			{
				if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[nCnt]) < m_stItemInfo.stStdItem.bNeedLevel )
				{
					bUseAble = FALSE;
					break;
				}
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5144), m_stItemInfo.stStdItem.bNeedLevel);
			break;
		}
		case 5:
		{
			if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[0]) >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5145), m_stItemInfo.stStdItem.bNeedLevel);
			break;
		}
		case 6:
		{
			if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[1]) >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5146), m_stItemInfo.stStdItem.bNeedLevel);
			break;
		}
		case 7:
		{
			if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[2]) >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5147), m_stItemInfo.stStdItem.bNeedLevel);
			break;
		}
		case 8:
		{
			if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[3]) >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5148), m_stItemInfo.stStdItem.bNeedLevel);

			break;
		}
		case 9:
		{
			if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[4]) >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5149), m_stItemInfo.stStdItem.bNeedLevel);

			break;
		}
		case 10:
		{
			if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[5]) >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5150), m_stItemInfo.stStdItem.bNeedLevel);

			break;
		}
		case 11:
		{
			if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[6]) >= m_stItemInfo.stStdItem.bNeedLevel )
			{
			   bUseAble = TRUE;
			}
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%d ", g_xMsg.GetMsg(5151), m_stItemInfo.stStdItem.bNeedLevel);

			break;
		}
	}
	m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);

	if ( ( m_stItemInfo.stStdItem.bNeed == 0 && m_stItemInfo.stStdItem.bNeedLevel == 0 ||
		 m_stItemInfo.stStdItem.bNeed == 0 && m_stItemInfo.stStdItem.bNeedLevel > 100 ) && bUseAble )
	{
		m_stItemState[m_nStateCnt].dwFont = RGB(  0, 200,   0);
	}
	else if ( bUseAble )
	{
		m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
	}
	else
	{
		m_stItemState[m_nStateCnt].dwFont = RGB(255, 0, 0);
	}
	m_nStateCnt++;

	if ( m_stItemInfo.stStdItem.nNeedFame > 0 )
	{
		sprintf(m_stItemState[m_nStateCnt].pszDesc, g_xMsg.GetMsg(2520), m_stItemInfo.stStdItem.nNeedFame);
		m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);

		if ( g_xGameProc.m_xMyHero.m_nFame >= m_stItemInfo.stStdItem.nNeedFame )
			m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 255);
		else
			m_stItemState[m_nStateCnt].dwFont = RGB(255, 0, 0);

		m_nStateCnt++;
	}
}

VOID CItem::SetEtcStatus(BOOL bUseStore, BOOL bUseEquip)
{
	INT	 nCnt; 
	INT  nDuraMax;
	if ( !bUseStore )
	{
		nDuraMax = m_stItemInfo.nDuraMax;
	}
	else
	{
		nDuraMax = m_stItemInfo.stStdItem.wDuraMax;
	}

	// 1. 이름.
	if ( strlen(m_stItemInfo.Prefix) )
	{		
		sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%s %s", g_xMsg.GetMsg(2515), m_stItemInfo.Prefix, m_stItemInfo.stStdItem.szName);
	}
	else
	{
		// 추석맞이 이벤트용.
		CHAR pszEventItm[20];
		for ( INT nCnt = 0; nCnt < 10; nCnt++ )
		{
			sprintf(pszEventItm, "%s%d", g_xMsg.GetMsg(1409), nCnt);
			if ( !strcmp(m_stItemInfo.stStdItem.szName, pszEventItm) )
			{
				sprintf(m_stItemState[m_nStateCnt].pszDesc, g_xMsg.GetMsg(2510));
				break;
			}
		}
		if ( !m_stItemState[m_nStateCnt].pszDesc[0] )
		{
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s%s", g_xMsg.GetMsg(2515), m_stItemInfo.stStdItem.szName);
		}
	}
	m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
	m_stItemState[m_nStateCnt].dwFont = RGB(255, 250,   0);
	m_nStateCnt++;

	// 무게.
	if (m_stItemInfo.stStdItem.bThrow == _MULTIPLE_TYPE_ITEM)
	{
		DWORD	dwCount = m_stItemInfo.wAmount_GB;

		sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d", g_xMsg.GetMsg(2501), dwCount / 10);
		m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
		m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
		m_nStateCnt++;
		sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d", g_xMsg.GetMsg(2503), dwCount);
	}
	else if (m_stItemInfo.stStdItem.bThrow > _MULTIPLE_TYPE_ITEM)			//  물약
	{
		DWORD	dwCount = m_stItemInfo.wAmount_GB;

		sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d", g_xMsg.GetMsg(2501), m_stItemInfo.stStdItem.bWeight * dwCount);
		m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
		m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
		m_nStateCnt++;
		sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d", g_xMsg.GetMsg(2503), dwCount);
	}
	else
		sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d", g_xMsg.GetMsg(2501), m_stItemInfo.stStdItem.bWeight);

	m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
	m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
	m_nStateCnt++;


	switch ( m_stItemInfo.stStdItem.bStdMode )
	{
		case 0:			// 물약.
		{
			if ( m_stItemInfo.stStdItem.wAC > 0 )
			{
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%dHP ", g_xMsg.GetMsg(1058), m_stItemInfo.stStdItem.wAC);
				m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
				m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
				m_nStateCnt++;
			}

			if ( m_stItemInfo.stStdItem.wMAC > 0 )
			{
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%dMP ", g_xMsg.GetMsg(1059), m_stItemInfo.stStdItem.wMAC);
				m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
				m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
				m_nStateCnt++;
			}
			break;
		}
		case 4:
		case 51:		// 각종책들.
		{
			for ( nCnt = 0; nCnt < 3; nCnt++ )
			{
				if ( nCnt == m_stItemInfo.stStdItem.bShape )
				{
					// 책종류.
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s", g_xMsg.GetMsg(nCnt+5170));

					if ( nCnt != g_xGameProc.m_xMyHero.m_bJob )
					{
						m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
						m_stItemState[m_nStateCnt].dwFont = RGB(255,   0,   0);
					}
					else
					{
						m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
						m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
					}
					m_nStateCnt++;

					// 필요능력치
					if ( m_stItemInfo.stStdItem.wDuraMax == 0 )
						sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %s", g_xMsg.GetMsg(5140), g_xMsg.GetMsg(5182));
					else
						sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d", g_xMsg.GetMsg(5140), m_stItemInfo.stStdItem.wDuraMax);
					
					m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
					if ( g_xGameProc.m_xMyHero.m_stAbility.bLevel >= m_stItemInfo.stStdItem.wDuraMax )
					{
						m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
					}
					else
					{
						m_stItemState[m_nStateCnt].dwFont = RGB(255, 0, 0);
					}
					m_nStateCnt++;
				}
			}
			break;
		}
		case 25:		// 각종 독가루.
		{
			if ( m_stItemInfo.stStdItem.bShape != 9 )
			{
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d/%d", g_xMsg.GetMsg(2511), RoundFunc(m_stItemInfo.nDura, 10), RoundFunc(nDuraMax, 10));
				m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
				m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 255);
				m_nStateCnt++;
			}

			if ( m_stItemInfo.stStdItem.bShape == 20 )
			{
				BOOL bUseAble = FALSE;

				if ( g_xGameProc.m_xMyHero.m_stAbility.bLevel >= m_stItemInfo.stStdItem.bNeedLevel )
				{
				   bUseAble = TRUE;
				}

				if ( m_stItemInfo.stStdItem.bNeedLevel > 100 && g_xGameProc.m_xMyHero.m_stAbility.bLevel >= m_stItemInfo.stStdItem.bNeedLevel - 100 )
				{
				   bUseAble = TRUE;
				}

				if ( m_stItemInfo.stStdItem.bNeedLevel == 0 )
				{
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s", g_xMsg.GetMsg(2516));
				}
				else if ( m_stItemInfo.stStdItem.bNeedLevel > 100 )
				{
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d (%s)", g_xMsg.GetMsg(5140), m_stItemInfo.stStdItem.bNeedLevel-100, g_xMsg.GetMsg(2517));
				}
				else
				{
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d", g_xMsg.GetMsg(5140), m_stItemInfo.stStdItem.bNeedLevel);
				}
				m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
				m_stItemState[m_nStateCnt].dwFont = RGB(250, 250, 250);
				m_nStateCnt++;
			}

			break;
		}
		case 30:		// 횃불과 초.
		{
			// 내구.
			INT nDuraApp	= RoundFunc(m_stItemInfo.nDura, 1000);
			INT nDuraMaxApp = RoundFunc(nDuraMax, 1000);
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d/%d", g_xMsg.GetMsg(2500), RoundFunc(m_stItemInfo.nDura, 1000), RoundFunc(nDuraMax, 1000));
			m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
			if ( nDuraApp <= 1 ) 
			{
				m_stItemState[m_nStateCnt].dwFont = RGB(255,  50,  50);
			}
			else
			{
				m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 255);
			}
			m_nStateCnt++;
			break;
		}
		case 40:		// 각종고기들(고기덩어리)
		{
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d/%d", g_xMsg.GetMsg(2512), RoundFunc(m_stItemInfo.nDura, 1000), RoundFunc(nDuraMax, 1000));
			m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
			m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 255);
			m_nStateCnt++;
			break;
		}
		case 42:		// 각종약재들.
		{
			sprintf(m_stItemState[m_nStateCnt].pszDesc, g_xMsg.GetMsg(2513));
			m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
			m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
			m_nStateCnt++;
			break;
		}
		case 43:		// 각종광석들.
		{
			sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d", g_xMsg.GetMsg(2514), RoundFunc(m_stItemInfo.nDura, 1000));
			m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
			m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 255);
			m_nStateCnt++;
			break;
		}
		case 60:
		{
			if ( m_stItemInfo.stStdItem.bShape == 3 )
			{
				// 체력증가량
				m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
				m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%d", g_xMsg.GetMsg(2518), m_stItemInfo.stStdItem.wAC*m_stItemInfo.nDura/nDuraMax );
				m_nStateCnt++;

				// 마력증가량
				m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
				m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
				sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: +%d", g_xMsg.GetMsg(2519), m_stItemInfo.stStdItem.wMAC*m_stItemInfo.nDura/nDuraMax );
				m_nStateCnt++;
			}
			else
			{
				// 4. 방어.
				m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);
				if ( m_stItemInfo.Desc[0] > 0 )
				{
					// 옵션 Plus.               
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d-%d (+%d)", g_xMsg.GetMsg(5177), LOBYTE(m_stItemInfo.stStdItem.wAC), HIBYTE(m_stItemInfo.stStdItem.wAC)+m_stItemInfo.Desc[0], m_stItemInfo.Desc[0]);
					m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
				}
				else
				{
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d-%d", g_xMsg.GetMsg(5177), LOBYTE(m_stItemInfo.stStdItem.wAC), HIBYTE(m_stItemInfo.stStdItem.wAC));
					m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
				}
				m_nStateCnt++;

				if (bUseEquip)
					g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[1] = TRUE;
				
				// 마법방어
				if ( m_stItemInfo.stStdItem.wMAC + m_stItemInfo.Desc[1] > 0 )
				{
					if ( m_stItemInfo.Desc[1] > 0)
					{
						// 옵션 Plus.
						sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d-%d (+%d)", g_xMsg.GetMsg(1406), LOBYTE(m_stItemInfo.stStdItem.wMAC), HIBYTE(m_stItemInfo.stStdItem.wMAC)+m_stItemInfo.Desc[1], m_stItemInfo.Desc[1]);
						m_stItemState[m_nStateCnt].dwFont = RGB(150, 255, 200);
					}
					else
					{
						sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d-%d", g_xMsg.GetMsg(1406), LOBYTE(m_stItemInfo.stStdItem.wMAC), HIBYTE(m_stItemInfo.stStdItem.wMAC));
						m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
					}
					m_nStateCnt++;
					if (bUseEquip)
						g_xGameProc.m_xInterface.m_xStatusWnd.m_bCheckShow[4] = TRUE;
				}

				if ( LOBYTE(m_stItemInfo.stStdItem.bNeedLevel) > 0 )
				{
					BOOL bUseAble = FALSE;
					// 필요레벨.
					if ( g_xGameProc.m_xMyHero.m_stAbility.bLevel >= LOBYTE(m_stItemInfo.stStdItem.bNeedLevel) )
					{
					   bUseAble = TRUE;
					}

					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d", g_xMsg.GetMsg(5140), LOBYTE(m_stItemInfo.stStdItem.bNeedLevel));

					if ( bUseAble )
					{
						m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
					}
					else
					{
						m_stItemState[m_nStateCnt].dwFont = RGB(255, 0, 0);
					}
					m_nStateCnt++;
				}

			}
			break;
		}
		case 3:			// 특수한물약 OR 각종전서들.
		{
			if ( m_stItemInfo.stStdItem.bShape == 13 || m_stItemInfo.stStdItem.bShape == 15 ||
				 m_stItemInfo.stStdItem.bShape == 12 )
			{
				BOOL bUseAble = FALSE;
				// 6. 필요레벨.
				if ( g_xGameProc.m_xMyHero.m_stAbility.bLevel >= LOBYTE(m_stItemInfo.stStdItem.bNeedLevel) )
				{
				   bUseAble = TRUE;
				}

				if ( LOBYTE(m_stItemInfo.stStdItem.bNeedLevel) == 0 )
				{
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s", g_xMsg.GetMsg(2516));
				}
				else
				{
					sprintf(m_stItemState[m_nStateCnt].pszDesc, "%s: %d", g_xMsg.GetMsg(5140), LOBYTE(m_stItemInfo.stStdItem.bNeedLevel));
				}

				if ( bUseAble )
				{
					m_stItemState[m_nStateCnt].dwFont = RGB(255, 255, 255);
				}
				else
				{
					m_stItemState[m_nStateCnt].dwFont = RGB(255, 0, 0);
				}
				m_nStateCnt++;
			}
		}
		break;
		case 1:			// 말린고기.
		case 2:			// 주먹밥.
		case 31:		// 각종묶음시리즈.
		case 44:		// 상점에는 없는 특수 아이템.
		case 45:		// 땅에 떨어질때 바뀌는 기능성 아이템.
		case 46:		// 기능은 없는 단순아이템.
		default:
		{
			break;
		}
	}

	if ( m_stItemInfo.stStdItem.nNeedFame > 0 )
	{
		sprintf(m_stItemState[m_nStateCnt].pszDesc, g_xMsg.GetMsg(2520), m_stItemInfo.stStdItem.nNeedFame);
		m_stItemState[m_nStateCnt].dwBack = RGB(  0,   0,   0);

		if ( g_xGameProc.m_xMyHero.m_nFame >= m_stItemInfo.stStdItem.nNeedFame )
			m_stItemState[m_nStateCnt].dwFont = RGB(128, 255, 255);
		else
			m_stItemState[m_nStateCnt].dwFont = RGB(255, 0, 0);

		m_nStateCnt++;
	}
}

VOID CItem::ShowItemStatus(INT nX, INT nY, BOOL bUseStore, BOOL bClothShow, BOOL bUseEquip)
{
	INT		nCnt;
	SIZE	sizeBoard = {0, 0};
	SIZE	sizeLen	  = {0, 0};

	SetItemStatus(bUseStore, bUseEquip);

	for ( nCnt = 0; nCnt < m_nStateCnt; nCnt++ )
	{
		if ( m_stItemState[nCnt].pszDesc[0] != '\0' )
		{
			sizeLen = g_xMainWnd.GetStrLength(NULL, NULL, m_stItemState[nCnt].pszDesc);

			if ( sizeLen.cx > sizeBoard.cx )
			{
				sizeBoard.cx = sizeLen.cx;
			}
			sizeBoard.cy += 15;//sizeLen.cy;
		}
	}

	RECT rcB = {nX-5, nY-5, nX+sizeBoard.cx+5, nY+sizeBoard.cy+2};

	if ( bClothShow )
	{
		CWHWilImageData* pxItemImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_INVENTORY];
		if ( pxItemImg->NewSetIndex(m_stItemInfo.stStdItem.wLooks) )
		{
			rcB.right += pxItemImg->m_lpstNewCurrWilImageInfo->shWidth + 10;
			if ( (rcB.bottom - rcB.top) < pxItemImg->m_lpstNewCurrWilImageInfo->shHeight )
			{
				rcB.bottom = rcB.top+pxItemImg->m_lpstNewCurrWilImageInfo->shHeight + 10;
			}

		}
	}

	INT  nW  = rcB.right - rcB.left;
	INT  nH  = rcB.bottom - rcB.top;

	RECT rc = rcB;

	if ( rcB.right > 800 )
	{
		INT nWGap = rcB.right - 800;
		SetRect(&rc, rcB.left - nWGap, rcB.top, rcB.right - nWGap, rcB.bottom);
	}

	// 뒷판 그리기.
	D3DVECTOR	 vecTrans((FLOAT)(rc.left), (FLOAT)(rc.top), 0);
	D3DVECTOR	 vecScale((FLOAT)(nW), (FLOAT)(nH), 1);
	D3DMATERIAL7 mtrl;

	D3DUtil_InitMaterial(mtrl, (FLOAT)100/255.0f, (FLOAT)100/255.0f, (FLOAT)50/255.0f);
	mtrl.diffuse.a = 230.0f/255.0f;
	g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

	g_xMainWnd.DrawWithGDI(&rc, NULL, RGB(150, 150, 50), 1);

	INT nClothSX = 0; 
	INT nClothSY = 0; 
	INT nClothWidth  = 0; 
	INT nClothHeight = 0;

	if ( bClothShow )
	{
		CWHWilImageData* pxItemImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_INVENTORY];
		if ( pxItemImg->NewSetIndex(m_stItemInfo.stStdItem.wLooks) )
		{
			nClothWidth  = pxItemImg->m_lpstNewCurrWilImageInfo->shWidth;
			nClothHeight = pxItemImg->m_lpstNewCurrWilImageInfo->shHeight;
			nClothSX = 5;
			nClothSY = ((rc.bottom - rc.top)-nClothHeight)/2;

			WORD wClr = g_xMainWnd.ConvertColor24To16(RGB(m_stItemInfo.bLevel_R, LOBYTE(m_stItemInfo.wAmount_GB), HIBYTE(m_stItemInfo.wAmount_GB)));
			g_xMainWnd.DrawWithImageForCompClipRgn(rc.left+nClothSX, rc.top+nClothSY, pxItemImg->m_lpstNewCurrWilImageInfo->shWidth, pxItemImg->m_lpstNewCurrWilImageInfo->shHeight,
												   (WORD*)pxItemImg->m_pbCurrImage, _CLIP_WIDTH, _CLIP_HEIGHT, wClr, 0XFFFF, TRUE);
		}
	}

	// 아이템상태 텍스트.
	for ( nCnt = 0; nCnt < m_nStateCnt; nCnt++ )
	{
		if ( m_stItemState[nCnt].pszDesc[0] != '\0' )
		{
			g_xMainWnd.PutsHan(NULL, rc.left+5+nClothSX+nClothWidth, rc.top+5+nCnt*15, m_stItemState[nCnt].dwFont, m_stItemState[nCnt].dwBack, m_stItemState[nCnt].pszDesc);	
		}
	}
}

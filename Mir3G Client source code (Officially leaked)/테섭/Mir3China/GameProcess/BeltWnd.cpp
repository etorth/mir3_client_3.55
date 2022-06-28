/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/

#include "StdAfx.h"

CBeltWnd::CBeltWnd()
{
	Init();
}

CBeltWnd::~CBeltWnd()
{
	Destroy();
}


VOID CBeltWnd::Init()
{
	mBelt_nMode			= _HORIZONTAL_MODE;
	m_shBeltHeight		= 0;
	m_bBeltState		= _BELT_STATE_STAY;
	ZeroMemory(m_rcBeltCell, sizeof(RECT) *_BELT_MAX_CELL );
	ZeroMemory(m_stBeltItem, sizeof(ITEMSET)*_MAX_BELT_ITEM );
}


VOID CBeltWnd::Destroy()
{
}


VOID CBeltWnd::CreateBeltWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend)
{
	INT nCnt;
	// 윈도우 생성.
	CreateGameWnd(nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight, bBlend);

	// 버튼생성.
	m_xBeltBtnClose.CreateGameBtn(pxWndImage, 322, 322, nStartX+258, nStartY+35, g_xMsg.GetMsg(1052), _BTN_TYPE_FOCUS, -1, TRUE);
	m_xBeltBtnRotate.CreateGameBtn(pxWndImage, 323, 323, nStartX+258, nStartY+35, g_xMsg.GetMsg(1100), _BTN_TYPE_FOCUS, -1, TRUE);

	for ( nCnt = 0; nCnt < _MAX_BELT_ITEM; nCnt++ )
	{
		SetRect(&m_rcBeltCell[nCnt], (nCnt*42)+17, 6, (nCnt*42)+54, 6+36);
	}

	if ( mBelt_nMode == _HORIZONTAL_MODE )
	{
		SetRect(&m_rcWnd, m_rcWnd.left, m_rcWnd.top, m_rcWnd.left+274, m_rcWnd.top+50); 
	}
	else
	{
		SetRect(&m_rcWnd, m_rcWnd.left, m_rcWnd.top, m_rcWnd.left+50, m_rcWnd.top+274); 
	}
}


VOID CBeltWnd::ShowBeltWnd()
{
	INT nX, nY, nCnt;

	m_bBeltState = _BELT_STATE_UP;
	
	if ( mBelt_nMode == _HORIZONTAL_MODE )
	{
		ShowGameWnd();
	}
	else
	{
		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(321) )
		{
			g_xMainWnd.DrawWithImageForComp(m_rcWnd.left, m_rcWnd.top, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
		}

	}
	

	for ( nCnt = 0; nCnt < _MAX_BELT_ITEM; nCnt++ )
	{
		if ( mBelt_nMode == _HORIZONTAL_MODE )
			SetRect(&m_rcBeltCell[nCnt], m_rcWnd.left+ (nCnt*39)+24, m_rcWnd.top + 7, m_rcWnd.left + (nCnt*39)+58, m_rcWnd.top + 7+36);
		else
			SetRect(&m_rcBeltCell[nCnt], m_rcWnd.left+6, m_rcWnd.top + (nCnt*39)+ 24, m_rcWnd.left + 42, m_rcWnd.top + (nCnt*39) + 60);
	}

	if ( m_bBeltState != _BELT_STATE_STAY )
	{
			// 벨트 아이템 그리기.
		for ( nCnt = 0; nCnt < _MAX_BELT_ITEM; nCnt++ )
		{
			if ( m_stBeltItem[nCnt].bSetted )
			{
				nX = m_rcBeltCell[nCnt].left;
				nY = m_rcBeltCell[nCnt].top;

				m_stBeltItem[nCnt].xItem.DrawItem(nX, nY);
			}
		}
	}

	if ( mBelt_nMode == _HORIZONTAL_MODE )
	{
		m_xBeltBtnClose.ChangeRect(m_rcWnd.left+3, m_rcWnd.top+8);
		m_xBeltBtnRotate.ChangeRect(m_rcWnd.left+3, m_rcWnd.top+29);
	}
	else
	{
		m_xBeltBtnClose.ChangeRect(m_rcWnd.left+29, m_rcWnd.top+4);
		m_xBeltBtnRotate.ChangeRect(m_rcWnd.left+8, m_rcWnd.top+4);
	}

	m_xBeltBtnClose.ShowGameBtn();
	m_xBeltBtnRotate.ShowGameBtn();
}

BOOL CBeltWnd::OnLButtonDown(POINT ptMouse)
{
	if (m_xBeltBtnClose.OnLButtonDown(ptMouse))
	{
		return TRUE;
	}

	if (m_xBeltBtnRotate.OnLButtonDown(ptMouse))
	{
		return TRUE;
	}

	INT nBeltInventoryNum = GetBeltNum(ptMouse);
	//-----------------------------------------------------------------------------------------------------------------
	if ( nBeltInventoryNum != -1 )
	{
		if (m_stBeltItem[nBeltInventoryNum].bSetted == FALSE)
		{
			m_bCanMove = TRUE;
			return FALSE;
		}
		else
			return TRUE;
	}

	m_bCanMove = TRUE;
	return FALSE;
}

BOOL CBeltWnd::OnLButtonUp(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse)
{
	INT nBeltInventoryNum = GetBeltNum(ptMouse);
	//-----------------------------------------------------------------------------------------------------------------

	if ( nBeltInventoryNum != -1 )
	{
		if ( m_stBeltItem[nBeltInventoryNum].bSetted )
		{
			if ( !g_xGameProc.m_xInterface.m_stCommonItem.bSetted )
			{				  
				SetCommonFromBelt(nBeltInventoryNum, &g_xGameProc.m_xInterface.m_stCommonItem);
			}
			else if ( g_xGameProc.m_xInterface.m_stCommonItem.bSetted && !g_xGameProc.m_xInterface.m_stCommonItem.bWaitResponse && !g_xGameProc.m_xInterface.m_stCommonItem.bIsEquipItem && !g_xGameProc.m_xInterface.m_stCommonItem.bIsUtilItem )
			{		
				if ( strcmp(g_xGameProc.m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(1050)) &&
					(g_xGameProc.m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.bStdMode == 0 || g_xGameProc.m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.bStdMode == 3) )
				{
					ChangeBeltWithCommon(nBeltInventoryNum, &g_xGameProc.m_xInterface.m_stCommonItem);
				}
			}
		}
		else
		{
			if ( g_xGameProc.m_xInterface.m_stCommonItem.bSetted && !g_xGameProc.m_xInterface.m_stCommonItem.bWaitResponse && !g_xGameProc.m_xInterface.m_stCommonItem.bIsEquipItem )
			{				  
				if ( strcmp(g_xGameProc.m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(1050)) &&
					(g_xGameProc.m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.bStdMode == 0 || g_xGameProc.m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.bStdMode == 3) )
				{
					SetBeltFromCommon(nBeltInventoryNum, &g_xGameProc.m_xInterface.m_stCommonItem);
				}
			}
		}
	}

	// 윈도우를 닫는다.
	if ( m_xBeltBtnClose.OnLButtonUp(ptMouse) )
	{
		return TRUE;
	}

	if ( m_xBeltBtnRotate.OnLButtonUp(ptMouse) )
	{
		mBelt_nMode = !mBelt_nMode;

		if ( mBelt_nMode == _HORIZONTAL_MODE )
		{
			SetRect(&m_rcWnd, m_rcWnd.left, m_rcWnd.top, m_rcWnd.left+274, m_rcWnd.top+50); 
		}
		else
		{
			SetRect(&m_rcWnd, m_rcWnd.left, m_rcWnd.top, m_rcWnd.left+50, m_rcWnd.top+274); 
		}
		return FALSE;
	}


	return FALSE;
}


BOOL CBeltWnd::OnLButtonDoubleClick(POINT ptMouse)
{
	INT nBeltInventoryNum = GetBeltNum(ptMouse);

	if ( nBeltInventoryNum != -1 )
	{
		BYTE bStdMode = g_xGameProc.m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.bStdMode;
		WORD wLooks   = g_xGameProc.m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.wLooks;

		if ( (bStdMode != 0 && bStdMode != 3) ||
			((bStdMode == 0 || bStdMode == 3) && timeGetTime() - g_xGameProc.m_xInterface.m_xInventoryWnd.m_dwDLClickTime > 2000) || // 물약류, 전서류...(2초지연)
			 (bStdMode == 0 && timeGetTime() - g_xGameProc.m_xInterface.m_xInventoryWnd.m_dwDLClickTime > 1000 && 
			 (wLooks == 20 || wLooks == 21 || wLooks == 70 || wLooks == 25 || wLooks == 26 || wLooks == 27 || wLooks == 28 || wLooks == 35 || wLooks == 36 || wLooks == 37 || wLooks == 38 ) // 선화수등..(1초지연)
		   ))
		{
			if ( g_xGameProc.m_xInterface.m_stCommonItem.bSetted && !g_xGameProc.m_xInterface.m_stCommonItem.bWaitResponse && !g_xGameProc.m_xInterface.m_stCommonItem.bIsEquipItem && g_xGameProc.m_bUseSpell == FALSE )
			{			
				if ( strcmp(g_xGameProc.m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(1050)) &&
					(bStdMode == 0 || bStdMode == 3) )
				{
					g_xGameProc.m_xInterface.m_stCommonItem.bWaitResponse = TRUE;
					g_xClientSocket.SendItemIndex(CM_EAT, g_xGameProc.m_xInterface.m_stCommonItem.xItem.m_stItemInfo.nMakeIndex, g_xGameProc.m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName);
					g_xGameProc.m_xInterface.m_xInventoryWnd.m_dwDLClickTime = timeGetTime();
					return TRUE;
				}
			}
		}

		CHAR szSysMsg[MAX_PATH];
		if ( g_xGameProc.m_xInterface.m_stCommonItem.bSetted )
		{
			sprintf(szSysMsg, "%s", g_xMsg.GetMsg(1051));
		}
		else
		{
			sprintf(szSysMsg, g_xMsg.GetMsg(1066), nBeltInventoryNum+1);
		}		
		g_xGameProc.m_xInterface.m_xClientSysMsg.AddSysMsg(szSysMsg);
	}

	return FALSE;
}

BOOL CBeltWnd::OnMouseMove(POINT ptMouse)
{
	m_xBeltBtnClose.OnMouseMove(ptMouse);
	m_xBeltBtnRotate.OnMouseMove(ptMouse);

	return FALSE;
}

VOID CBeltWnd::MoveBeltWnd(POINT ptMouse)
{
	INT nImgWidth  = m_rcImgWnd.right - m_rcImgWnd.left;
	INT nImgHeight = m_rcImgWnd.bottom - m_rcImgWnd.top;
	if ( (m_bActive && m_bFocused && m_bCanMove) )
	{
		INT nSX = ptMouse.x-m_bGrabbedMousePos.x;
		INT nSY = ptMouse.y-m_bGrabbedMousePos.y;

		if ( (nSY + m_nHeight) > 570  )
		{
			nSY = 565 - m_nHeight;
		}

		INT nTempWidth  = m_rcWnd.right - m_rcWnd.left;
		INT nTempHeight = m_rcWnd.bottom - m_rcWnd.top;
		SetRect(&m_rcWnd, nSX, nSY, nSX+nTempWidth, nSY+nTempHeight); 

		SetRect(&m_rcImgWnd, 
				nSX - (nImgWidth - m_nWidth )/2, 
				nSY - (nImgHeight- m_nHeight)/2, 
				nSX - (nImgWidth - m_nWidth )/2 + nImgWidth, 
				nSY - (nImgHeight- m_nHeight)/2 + nImgHeight);
	}
}

BOOL CBeltWnd::ProceessKeyDownMessage(WPARAM wParam, LPARAM lParam)
{
	int		nBeltInventoryNum = -1;

	if ( HIBYTE(GetKeyState('Z')) )
	{
		// 창 보여주기
		if (g_xGameProc.m_xInterface.WindowActivate(_WND_ID_BELT) == TRUE)
			m_bBeltState = _BELT_STATE_UP;
		else
			m_bBeltState = _BELT_STATE_STAY;
	}

	if ( wParam == 229 )
	{
		switch ( lParam )
		{
			case 131073:
			{
				if ( HIBYTE(GetKeyState(VK_SHIFT)) )
				{
					CHAR pszStr[2] = {'!'};
					g_xGameProc.m_xInterface.m_xChatWnd.ActiveEditBox();
					g_xChatEditBox.SetHanguelMode();
					SetFocus(g_xChatEditBox.GetSafehWnd());
					ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);
					SetWindowText(g_xChatEditBox.GetSafehWnd(), pszStr);

					SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETSEL, 1 , 1);
					g_xChatEditBox.SetHanguelMode();
				}
				else
				{
					nBeltInventoryNum = 0;
				}
				break;
			}
			case 196609:
			{
				if ( HIBYTE(GetKeyState(VK_SHIFT)) )
				{
					CHAR pszStr[2] = {'@'};

					g_xGameProc.m_xInterface.m_xChatWnd.ActiveEditBox();
					g_xGameProc.m_xInterface.m_xChatWnd.ActiveEditBox();
					g_xChatEditBox.SetHanguelMode();
					SetFocus(g_xChatEditBox.GetSafehWnd());
					ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);
					SetWindowText(g_xChatEditBox.GetSafehWnd(), pszStr);

					SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETSEL, 1 , 1);
					g_xChatEditBox.SetHanguelMode();
				}
				else
				{
					nBeltInventoryNum = 1;		
				}
				break;
			}
			case 262145:			nBeltInventoryNum = 2;		break;
			case 327681:			nBeltInventoryNum = 3;		break;
			case 393217:			nBeltInventoryNum = 4;		break;
			case 458753:			nBeltInventoryNum = 5;		break;
		}
	}
	else
	{
		switch ( wParam )
		{
			case '1':			// !
			{
				if ( HIBYTE(GetKeyState(VK_SHIFT)) )
				{
					CHAR pszStr[2] = {'!'};
					g_xGameProc.m_xInterface.m_xChatWnd.ActiveEditBox();
					g_xChatEditBox.SetHanguelMode();
					SetFocus(g_xChatEditBox.GetSafehWnd());
					ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);
					SetWindowText(g_xChatEditBox.GetSafehWnd(), pszStr);

					SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETSEL, 1 , 1);
					g_xChatEditBox.SetHanguelMode();
				}
				else
				{
					nBeltInventoryNum = 0;
				}
				break;
			}
			case '2':			// @
			{
				if ( HIBYTE(GetKeyState(VK_SHIFT)) )
				{
					CHAR pszStr[2] = {'@'};

					g_xGameProc.m_xInterface.m_xChatWnd.ActiveEditBox();
					g_xGameProc.m_xInterface.m_xChatWnd.ActiveEditBox();
					g_xChatEditBox.SetHanguelMode();
					SetFocus(g_xChatEditBox.GetSafehWnd());
					ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);
					SetWindowText(g_xChatEditBox.GetSafehWnd(), pszStr);

					SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETSEL, 1 , 1);
					g_xChatEditBox.SetHanguelMode();
				}
				else
				{
					nBeltInventoryNum = 1;		
				}
				break;
			}
			case '3':			nBeltInventoryNum = 2;		break;
			case '4':			nBeltInventoryNum = 3;		break;
			case '5':			nBeltInventoryNum = 4;		break;
			case '6':			nBeltInventoryNum = 5;		break;
		}
	}

	if ( nBeltInventoryNum != -1 )
	{
		BYTE bStdMode = m_stBeltItem[nBeltInventoryNum].xItem.m_stItemInfo.stStdItem.bStdMode;
		WORD wLooks   = m_stBeltItem[nBeltInventoryNum].xItem.m_stItemInfo.stStdItem.wLooks;

		BOOL bAttack = FALSE;

//		if ( (g_xGameProc.m_xMyHero.m_bCurrMtn == _MT_ONEVSWING || g_xGameProc.m_xMyHero.m_bCurrMtn == _MT_TWOVSWING || g_xGameProc.m_xMyHero.m_bCurrMtn == _MT_ONEHSWING || g_xGameProc.m_xMyHero.m_bCurrMtn == _MT_TWOHSWING || g_xGameProc.m_xMyHero.m_bCurrMtn == _MT_SPEARVSWING || g_xGameProc.m_xMyHero.m_bCurrMtn == _MT_SPEARHSWING ) && !g_xGameProc.m_xMyHero.m_bInputLock)   // 물약류, 전서류...(2초지연)
//			bAttack = TRUE;

		DWORD dwtemp = timeGetTime() - g_xGameProc.m_xInterface.m_xInventoryWnd.m_dwDLClickTime;
		if ( (bStdMode != 0 && bStdMode != 3) ||
			((bStdMode == 0 || bStdMode == 3) && timeGetTime() - g_xGameProc.m_xInterface.m_xInventoryWnd.m_dwDLClickTime > 2000 /*&& !bAttack*/) || // 물약류, 전서류...(2초지연)
			 (bStdMode == 0 && timeGetTime() - g_xGameProc.m_xInterface.m_xInventoryWnd.m_dwDLClickTime > 1000 && 
			 (wLooks == 20 || wLooks == 21 || wLooks == 70 || wLooks == 25 || wLooks == 26 || wLooks == 27 || wLooks == 28 || wLooks == 35 || wLooks == 36 || wLooks == 37 || wLooks == 38 ) // 선화수등..(1초지연)
		   ))
		{
			if ( m_stBeltItem[nBeltInventoryNum].bSetted && g_xGameProc.m_bUseSpell == FALSE )
			{
				if ( !g_xGameProc.m_xInterface.m_stCommonItem.bSetted )
				{
					SetCommonFromBelt(nBeltInventoryNum, &g_xGameProc.m_xInterface.m_stCommonItem);
				}
				else if ( g_xGameProc.m_xInterface.m_stCommonItem.bSetted && !g_xGameProc.m_xInterface.m_stCommonItem.bWaitResponse && !g_xGameProc.m_xInterface.m_stCommonItem.bIsEquipItem && !g_xGameProc.m_xInterface.m_stCommonItem.bIsUtilItem )
				{		
					if ( strcmp(g_xGameProc.m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(1050)) &&
						(g_xGameProc.m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.bStdMode == 0 || g_xGameProc.m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.bStdMode == 3) )
					{
						ChangeBeltItem(nBeltInventoryNum, &g_xGameProc.m_xInterface.m_stCommonItem);
						return TRUE;
					}
				}
			}
			else
			{
				if ( g_xGameProc.m_xInterface.m_stCommonItem.bSetted && !g_xGameProc.m_xInterface.m_stCommonItem.bWaitResponse && !g_xGameProc.m_xInterface.m_stCommonItem.bIsEquipItem )
				{				  
					if ( strcmp(g_xGameProc.m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(1050)) &&
						(g_xGameProc.m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.bStdMode == 0 || g_xGameProc.m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.bStdMode == 3) )
					{
						INT nIdx = FindSameItemInBelt(g_xGameProc.m_xInterface.m_stCommonItem.xItem);
						if ( nIdx != -1 )
						{
							DeleteBeltItem(nIdx);
							SetBeltFromCommon(nBeltInventoryNum, &g_xGameProc.m_xInterface.m_stCommonItem);
						}
						SetBeltFromCommon(nBeltInventoryNum, &g_xGameProc.m_xInterface.m_stCommonItem);
					}
				}				
			}

			if ( strcmp(g_xGameProc.m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(1050)) && g_xGameProc.m_xInterface.m_stCommonItem.bSetted && !g_xGameProc.m_xInterface.m_stCommonItem.bWaitResponse && !g_xGameProc.m_xInterface.m_stCommonItem.bIsEquipItem )
			{			
				if ( g_xGameProc.m_bUseSpell == FALSE )
				{
					g_xGameProc.m_xInterface.m_stCommonItem.bWaitResponse = TRUE;
					g_xGameProc.m_xInterface.m_stCommonItem.bIsHideItem	= TRUE;
					g_xClientSocket.SendItemIndex(CM_EAT, g_xGameProc.m_xInterface.m_stCommonItem.xItem.m_stItemInfo.nMakeIndex, g_xGameProc.m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName);

					if ( g_xGameProc.m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.bStdMode == 0 || g_xGameProc.m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.bStdMode == 3 )
					{
						g_xGameProc.m_xInterface.m_xInventoryWnd.m_dwDLClickTime = timeGetTime();
					}

					return TRUE;
				}
			}
		}

		CHAR szSysMsg[MAX_PATH];
		if ( m_stBeltItem[nBeltInventoryNum].bSetted )
		{
			sprintf(szSysMsg, "%s", g_xMsg.GetMsg(1051));
		}
		else
		{
			sprintf(szSysMsg, g_xMsg.GetMsg(1066), nBeltInventoryNum+1);
		}		
		g_xGameProc.m_xInterface.m_xClientSysMsg.AddSysMsg(szSysMsg);

		return TRUE;
	}
	return FALSE;
}	

INT CBeltWnd::GetBeltNum(POINT ptMouse)
{
	RECT	rc;
	if ( m_bBeltState != _BELT_STATE_STAY )
	{
		for ( INT nCnt = 0; nCnt < _MAX_BELT_ITEM; nCnt++ )
		{
			SetRect(&rc, m_rcBeltCell[nCnt].left, m_rcBeltCell[nCnt].top, 
					m_rcBeltCell[nCnt].left+_INVENTORY_CELL_WIDTH, m_rcBeltCell[nCnt].top+_INVENTORY_CELL_HEIGHT);
			if ( PtInRect(&rc, ptMouse) )
			{
				return nCnt;
			}
		}
	}

	return -1;
}

VOID CBeltWnd::SetBeltFromCommon(INT nBeltInventoryNum, LPCOMMONITEMSET pstCommonItemSet)
{
	CHAR szSysMsg[MAX_PATH];

	if ( pstCommonItemSet->bSetted )
	{
		if (pstCommonItemSet->bIsDealItem)
		{
			g_xGameProc.m_xInterface.m_xExchangeWnd.SetDealFromCommon(0, 0, pstCommonItemSet);
			g_xGameProc.m_xInterface.ItemClickSound(&pstCommonItemSet->xItem);
			ZeroMemory(pstCommonItemSet, sizeof(LPCOMMONITEMSET));
			return;
		}

		if (FindSameItemInBelt(pstCommonItemSet->xItem) != -1)
		{
			sprintf(szSysMsg, g_xMsg.GetMsg(1067), pstCommonItemSet->xItem.m_stItemInfo.stStdItem.szName);
			g_xGameProc.m_xInterface.m_xClientSysMsg.AddSysMsg(szSysMsg);
			return;
		}

		g_xGameProc.m_xInterface.ItemClickSound(&pstCommonItemSet->xItem);

		pstCommonItemSet->xItem.m_shCellNum = (SHORT)nBeltInventoryNum;

		if (!pstCommonItemSet->bIsBeltItem)
		{
			g_xGameProc.m_xInterface.m_xInventoryWnd.AddInvenItem(pstCommonItemSet->xItem, pstCommonItemSet->xItem.m_shCellNum, FALSE);

			sprintf(szSysMsg, g_xMsg.GetMsg(1068), pstCommonItemSet->xItem.m_stItemInfo.stStdItem.szName, nBeltInventoryNum+1);
			g_xGameProc.m_xInterface.m_xClientSysMsg.AddSysMsg(szSysMsg);
			AddBeltItem(pstCommonItemSet->xItem, nBeltInventoryNum);
		}
		else
		{
			AddBeltItem(pstCommonItemSet->xItem, nBeltInventoryNum);
		}
		ZeroMemory(pstCommonItemSet, sizeof(LPCOMMONITEMSET));
	}
}

BOOL CBeltWnd::ChangeBeltItem(INT nBeltNum, LPCOMMONITEMSET pstCommonItemSet)
{
	m_stBeltItem[nBeltNum].bSetted = TRUE;
	m_stBeltItem[nBeltNum].xItem = pstCommonItemSet->xItem;

	g_xGameProc.m_xInterface.m_xInventoryWnd.AddInvenItem(pstCommonItemSet->xItem, pstCommonItemSet->xItem.m_shCellNum, FALSE);

	ZeroMemory(pstCommonItemSet, sizeof(LPCOMMONITEMSET));

	return TRUE;
}

VOID CBeltWnd::ChangeBeltWithCommon(INT nBeltInventoryNum, LPCOMMONITEMSET pstCommonItemSet)
{
	if ( pstCommonItemSet->bSetted )
	{
		CItem xBeltItem;

		if (strcmp(m_stBeltItem[nBeltInventoryNum].xItem.m_stItemInfo.stStdItem.szName, pstCommonItemSet->xItem.m_stItemInfo.stStdItem.szName) == 0)
		{
			g_xGameProc.m_xInterface.m_xClientSysMsg.AddSysMsg(g_xMsg.GetMsg(1069));
			return;
		}

		if ( ExtractBeltItem(&xBeltItem, nBeltInventoryNum) )
		{
			AddBeltItem(pstCommonItemSet->xItem, nBeltInventoryNum, TRUE);

			if (!pstCommonItemSet->bIsBeltItem)
				g_xGameProc.m_xInterface.m_xInventoryWnd.AddInvenItem(pstCommonItemSet->xItem, 0, FALSE);

			pstCommonItemSet->bSetted			= TRUE;
			pstCommonItemSet->xItem				= xBeltItem;
			pstCommonItemSet->bWaitResponse		= FALSE;
			pstCommonItemSet->bIsDealItem		= FALSE;
			pstCommonItemSet->bIsEquipItem		= FALSE;
			pstCommonItemSet->bIsHideItem		= FALSE;
			pstCommonItemSet->bIsBeltItem		= TRUE;
			pstCommonItemSet->xItem.m_shCellNum = (SHORT)nBeltInventoryNum; 
		}
	}
}

VOID CBeltWnd::SetCommonFromBelt(INT nBeltInventoryNum, LPCOMMONITEMSET pstCommonItemSet)
{
	CItem xBeltItem;
	if ( ExtractBeltItem(&xBeltItem, nBeltInventoryNum) )
	{
		pstCommonItemSet->bSetted			= TRUE;
		pstCommonItemSet->xItem				= xBeltItem;
		pstCommonItemSet->bWaitResponse		= FALSE;
		pstCommonItemSet->bIsEquipItem		= FALSE;
		pstCommonItemSet->bIsDealItem		= FALSE;
		pstCommonItemSet->bIsHideItem		= FALSE;
		pstCommonItemSet->bIsBeltItem		= TRUE;
		pstCommonItemSet->xItem.m_shCellNum = (SHORT)nBeltInventoryNum; 

		g_xGameProc.m_xInterface.ItemClickSound(&pstCommonItemSet->xItem);
	}
}	

VOID CBeltWnd::SetBeltFromCommonOLD(INT nBeltInventoryNum, LPCOMMONITEMSET pstCommonItemSet)
{
	if ( pstCommonItemSet->bSetted )
	{
		if (pstCommonItemSet->bIsDealItem)
		{
			g_xGameProc.m_xInterface.m_xExchangeWnd.SetDealFromCommon(0, 0, pstCommonItemSet);
			g_xGameProc.m_xInterface.ItemClickSound(&pstCommonItemSet->xItem);
			ZeroMemory(pstCommonItemSet, sizeof(LPCOMMONITEMSET));
			return;
		}

		g_xGameProc.m_xInterface.ItemClickSound(&pstCommonItemSet->xItem);

		pstCommonItemSet->xItem.m_shCellNum = (SHORT)nBeltInventoryNum;
		AddBeltItem(pstCommonItemSet->xItem, nBeltInventoryNum);

		ZeroMemory(pstCommonItemSet, sizeof(LPCOMMONITEMSET));
	}
}

VOID CBeltWnd::ChangeBeltWithCommonOLD(INT nBeltInventoryNum, LPCOMMONITEMSET pstCommonItemSet)
{
	if ( pstCommonItemSet->bSetted )
	{
		CItem xBeltItem;
		if ( ExtractBeltItem(&xBeltItem, nBeltInventoryNum) )
		{
			AddBeltItem(pstCommonItemSet->xItem, nBeltInventoryNum, TRUE);

			pstCommonItemSet->bSetted			= TRUE;
			pstCommonItemSet->xItem				= xBeltItem;
			pstCommonItemSet->bWaitResponse		= FALSE;
			pstCommonItemSet->bIsDealItem		= FALSE;
			pstCommonItemSet->bIsEquipItem		= FALSE;
			pstCommonItemSet->bIsHideItem		= FALSE;
			pstCommonItemSet->bIsBeltItem		= TRUE;
			pstCommonItemSet->xItem.m_shCellNum = (SHORT)nBeltInventoryNum; 
		}
	}
}

BOOL CBeltWnd::AddBeltItem(CItem xItem, INT nBeltNum, BOOL bUseBeltNum)
{
	if ( bUseBeltNum )
	{
		if ( !m_stBeltItem[nBeltNum].bSetted )
		{
			m_stBeltItem[nBeltNum].bSetted = TRUE;
			m_stBeltItem[nBeltNum].xItem = xItem;

			return TRUE;
		}
	}

	for ( INT nCnt = 0; nCnt < _MAX_BELT_ITEM; nCnt++ )
	{
		if ( !m_stBeltItem[nCnt].bSetted )
		{
			m_stBeltItem[nCnt].bSetted = TRUE;
			m_stBeltItem[nCnt].xItem = xItem;

			return TRUE;
		}
	}
	return FALSE;
}

int
CBeltWnd::FindSameItemInBelt(CItem xItem)
{
	for (int nI=0; nI<_MAX_BELT_ITEM; nI++)
	{
		if ( m_stBeltItem[nI].bSetted )
		{
			if (strcmp(m_stBeltItem[nI].xItem.m_stItemInfo.stStdItem.szName, xItem.m_stItemInfo.stStdItem.szName) == 0)
				return nI;
		}
	}
	return -1;
}

BOOL CBeltWnd::ExtractBeltItem(CItem* pxItem, INT nBeltInventoryNum)
{
	if ( m_stBeltItem[nBeltInventoryNum].bSetted )
	{
		memcpy(pxItem, &m_stBeltItem[nBeltInventoryNum].xItem, sizeof(CItem));
		DeleteBeltItem(nBeltInventoryNum);
				
		return TRUE;
	}
	return FALSE;
}

VOID CBeltWnd::DeleteBeltItem(INT nBeltInventoryNum)
{
	ZeroMemory(&m_stBeltItem[nBeltInventoryNum], sizeof(ITEMSET));
}

VOID CBeltWnd::SetStatusBtnInit()
{
	m_xBeltBtnClose.SetBtnState(_BTN_STATE_NORMAL);
}

VOID CBeltWnd::SaveBeltPosition()
{
	CHAR	szVal[MAX_PATH];
	CHAR	szFileName[MAX_PATH];
	CHAR	szTemp[MAX_PATH];
	BOOL	bResult;

	ZeroMemory(szFileName, MAX_PATH);
	ZeroMemory(szTemp, MAX_PATH);

	if ( GetCurrentDirectory(MAX_PATH, szFileName) )
	{
		if ( szFileName[0] == '\0' )
		{
			return;
		}

		strcat(szFileName, "\\Config.ini");

		_itoa(m_rcWnd.left,szVal,10);
		bResult = WritePrivateProfileString(SECTION_OPTIONS, KEY_BELTPOSITIONX, szVal, szFileName);

		_itoa(m_rcWnd.top,szVal,10);
		bResult = WritePrivateProfileString(SECTION_OPTIONS, KEY_BELTPOSITIONY, szVal, szFileName);

		_itoa(mBelt_nMode,szVal,10);
		bResult = WritePrivateProfileString(SECTION_OPTIONS, KEY_BELTMODE, szVal, szFileName);
	}
}

POINT CBeltWnd::LoadBeltPosition()
{
	CHAR	szFileName[MAX_PATH];
	CHAR	szTemp[MAX_PATH];
	CHAR*	pStr;
	POINT   ptLoc = {73, 413};

	ZeroMemory(szFileName, MAX_PATH);
	ZeroMemory(szTemp, MAX_PATH);

	if ( GetCurrentDirectory(MAX_PATH, szFileName) )
	{
		if ( szFileName[0] == '\0' )
		{
			return ptLoc;
		}

		strcat(szFileName, "\\Config.ini");
		GetPrivateProfileString(SECTION_OPTIONS, KEY_BELTPOSITIONX, "73", szTemp, MAX_PATH, szFileName);
		if ( szTemp == NULL )
		{
			return ptLoc;
		}
		ptLoc.x = atoi(szTemp);

		GetPrivateProfileString(SECTION_OPTIONS, KEY_BELTPOSITIONY, "413", szTemp, MAX_PATH, szFileName);
		if ( szTemp == NULL )
		{
			return ptLoc;
		}
		ptLoc.y = atoi(szTemp);

		GetPrivateProfileString(SECTION_OPTIONS, KEY_BELTMODE, "1", szTemp, MAX_PATH, szFileName);
		if ( szTemp == NULL )
		{
			return ptLoc;
		}
		mBelt_nMode = atoi(szTemp);


		return ptLoc;
	}

	return ptLoc;
}

/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"


CMarketUpWnd::CMarketUpWnd()
{
	Init();
}

CMarketUpWnd::~CMarketUpWnd()
{
	Destroy();
}

VOID CMarketUpWnd::Init()
{
	CGameWnd::Init();

	mUserMarketUp_hDescEdit = NULL;
	mUserMarketUp_nPrice = 0;
	mUserMarketUp_nNpcId = 0;

	mUserMarketUp_BtnClose.Init();
	mUserMarketUp_BtnCancel.Init();
	mUserMarketUp_BtnRegistry.Init();

	mUserMarketUp_bItemSet = FALSE;
	mUserMarketUp_bSetItemPrice = FALSE;

	SetRect(&mUserMarketUp_rcShowItem, 0, 0, 0, 0);
	SetRect(&mUserMarketUp_rcGold, 0, 0, 0, 0);
}

VOID CMarketUpWnd::Destroy()
{
	CGameWnd::Destroy();

	if ( mUserMarketUp_hDescEdit )
	{
		DestroyWindow(mUserMarketUp_hDescEdit);
		mUserMarketUp_hDescEdit = NULL;
	}
}

VOID CMarketUpWnd::CreateUserMarketWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend)
{
	CreateGameWnd(nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight, bBlend);

	mUserMarketUp_BtnClose.CreateGameBtn(pxWndImage, 1221, 1222, nStartX+368, nStartY+265, g_xMsg.GetMsg(1052), _BTN_TYPE_FOCUS, 1221, TRUE);
	mUserMarketUp_BtnCancel.CreateGameBtn(pxWndImage, 782, 782, nStartX+329, nStartY+240, g_xMsg.GetMsg(4501), _BTN_TYPE_FOCUS, -1, FALSE);
	mUserMarketUp_BtnRegistry.CreateGameBtn(pxWndImage, 784, 784, nStartX+259, nStartY+240, g_xMsg.GetMsg(4502), _BTN_TYPE_FOCUS, -1, FALSE);

	SetRect(&mUserMarketUp_rcEditBox, m_rcWnd.left+13, m_rcWnd.top+72, m_rcWnd.left+240, m_rcWnd.top+227);

	mUserMarketUp_hDescEdit = CreateWindowEx(NULL, _T("EDIT"), "", WS_POPUP | ES_LEFT | ES_AUTOVSCROLL | ES_MULTILINE,
								   g_xMainWnd.m_rcWindow.left + mUserMarketUp_rcEditBox.left, 
								   g_xMainWnd.m_rcWindow.top + mUserMarketUp_rcEditBox.top, 
								   mUserMarketUp_rcEditBox.right - mUserMarketUp_rcEditBox.left, 
								   mUserMarketUp_rcEditBox.bottom - mUserMarketUp_rcEditBox.top, 
								   g_xMainWnd.GetSafehWnd(), NULL, g_xMainWnd.GetSafehInstance(), NULL);

	if ( mUserMarketUp_hDescEdit )
	{
		UpdateWindow(mUserMarketUp_hDescEdit);
		ShowWindow(mUserMarketUp_hDescEdit, SW_HIDE);
		SendMessage(mUserMarketUp_hDescEdit, EM_LIMITTEXT, (WPARAM)4000, 0);

		SendMessage(mUserMarketUp_hDescEdit, WM_SETFONT, (WPARAM)g_xChatEditBox.m_hFontChatEdit, MAKELPARAM(TRUE, 0));
	}
}	
		
VOID CMarketUpWnd::ShowUserMarketUpWnd()
{
	ShowGameWnd();

	if ( !g_xGameProc.m_xInterface.IsTopWindow(m_nID) )
	{
		g_xGameProc.m_xInterface.m_xChatWnd.MoveEditBox();

		if ( mUserMarketUp_hDescEdit )
		{
			ShowWindow(mUserMarketUp_hDescEdit, SW_HIDE);
		}
		SetFocus(g_xMainWnd.GetSafehWnd());
		g_xChatEditBox.SetEnterUse(TRUE);
	}

	RECT rcTitle = {m_rcWnd.left + 60, m_rcWnd.top + 37, m_rcWnd.left + 154, m_rcWnd.top + 52};
	g_xMainWnd.PutsHan(NULL, rcTitle, RGB(250, 220, 248), 0, g_xMsg.GetMsg(4503));

	SetRect(&mUserMarketUp_rcEditBox, m_rcWnd.left+13, m_rcWnd.top+72, m_rcWnd.left+240, m_rcWnd.top+227);

	SetRect(&mUserMarketUp_rcGold, m_rcWnd.left + 25, m_rcWnd.top + 240, m_rcWnd.left + 190, m_rcWnd.top + 282);
	SetRect(&mUserMarketUp_rcShowItem, m_rcWnd.left + 247, m_rcWnd.top + 47, m_rcWnd.left + 395, m_rcWnd.top + 203);

	mUserMarketUp_BtnClose.ChangeRect(m_rcWnd.left+363, m_rcWnd.top+249);
	mUserMarketUp_BtnCancel.ChangeRect(m_rcWnd.left+312, m_rcWnd.top+250);
	mUserMarketUp_BtnRegistry.ChangeRect(m_rcWnd.left+272, m_rcWnd.top+250);

	mUserMarketUp_BtnClose.ShowGameBtn();
	mUserMarketUp_BtnCancel.ShowGameBtn();
	mUserMarketUp_BtnRegistry.ShowGameBtn();

	if ( !mUserMarketUp_bItemSet )
	{
		RECT rcDesc1 = {m_rcWnd.left + 250, m_rcWnd.top + 107, m_rcWnd.left + 390, m_rcWnd.top + 123};
		g_xMainWnd.PutsHan(NULL, rcDesc1, RGB(248, 200, 100), RGB(0,0,0), g_xMsg.GetMsg(4504));
		RECT rcDesc2 = {m_rcWnd.left + 250, m_rcWnd.top + 127, m_rcWnd.left + 390, m_rcWnd.top + 143};
		g_xMainWnd.PutsHan(NULL, rcDesc2, RGB(248, 200, 100), RGB(0,0,0), g_xMsg.GetMsg(4505));

		mUserMarketUp_nPrice = 0;
		return;
	}

	if ( mUserMarketUp_nPrice != 0 )
	{
		CHAR szStr[MAX_PATH];

		RECT rcGold = {m_rcWnd.left + 70, m_rcWnd.top + 257, m_rcWnd.left + 180, m_rcWnd.top + 272};
		
		GetNumWithComma(mUserMarketUp_nPrice, szStr);
		g_xMainWnd.PutsHan(NULL, rcGold, RGB(248, 200, 100), RGB(0,0,0), szStr);
	}


	CWHWilImageData* pxItemImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_INVENTORY];

	if ( pxItemImg->NewSetIndex(mUserMarketUp_xItem.m_stItemInfo.stStdItem.wLooks) )
	{
		INT nCX = m_rcWnd.left + 325;
		INT nCY = m_rcWnd.top + 145;

		INT nSX = nCX - pxItemImg->m_lpstNewCurrWilImageInfo->shWidth/2;
		INT nSY = nCY - pxItemImg->m_lpstNewCurrWilImageInfo->shHeight/2;

		RECT rcImg;
		if ( pxItemImg->m_lpstNewCurrWilImageInfo->shHeight > 170 )
		{
			SetRect(&rcImg, 0, 0, pxItemImg->m_lpstNewCurrWilImageInfo->shWidth, 140);
			nSY = 78;
		}
		else
			SetRect(&rcImg, 0, 0, pxItemImg->m_lpstNewCurrWilImageInfo->shWidth, pxItemImg->m_lpstNewCurrWilImageInfo->shHeight);

		RECT rcItemCell = {nSX - 15, nSY - 7, nSX+rcImg.right + 15, nSY+rcImg.bottom + 7};
		g_xMainWnd.DrawWithGDI(&rcItemCell, NULL, RGB(200, 200, 200), 1);

		D3DMATERIAL7 mtrl;
		D3DVECTOR	 vecTrans((FLOAT)rcItemCell.left, (FLOAT)rcItemCell.top, 0);
		D3DVECTOR	 vecScale((FLOAT)rcItemCell.right-rcItemCell.left, rcItemCell.bottom-rcItemCell.top, 1);

		D3DUtil_InitMaterial(mtrl, (FLOAT)30/255.0f, (FLOAT)30/255.0f, (FLOAT)30/255.0f);
		mtrl.diffuse.a = 180.0f/255.0f;
		g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

		WORD wClr = 0XFFFF;
		
		if ( mUserMarketUp_xItem.m_stItemInfo.stStdItem.bStdMode == 10 || mUserMarketUp_xItem.m_stItemInfo.stStdItem.bStdMode == 11 )
		{
			wClr = g_xMainWnd.ConvertColor24To16(RGB(mUserMarketUp_xItem.m_stItemInfo.bLevel_R, 
													 LOBYTE(mUserMarketUp_xItem.m_stItemInfo.wAmount_GB), 
													 HIBYTE(mUserMarketUp_xItem.m_stItemInfo.wAmount_GB))); 
		}

		g_xMainWnd.DrawWithImageForComp(nSX, nSY, &rcImg, (WORD*)pxItemImg->m_pbCurrImage, wClr);

		if ( mUserMarketUp_xItem.m_stItemInfo.stStdItem.bThrow >= _MULTIPLE_TYPE_ITEM )
		{
			RECT rc;
			CHAR pszTmp[MAX_PATH];

			DWORD	dwCount = mUserMarketUp_xItem.m_stItemInfo.wAmount_GB;

			sprintf(pszTmp, "%d", dwCount);
			g_xMainWnd.PutsHan(NULL, nSX + 23, nSY + 22, RGB(255, 255, 0), RGB(0,0,0), pszTmp);
		}

		if ( PtInRect(&mUserMarketUp_rcShowItem, g_xGameProc.m_ptMousePos) )
		{
			mUserMarketUp_xItem.ShowItemStatus(nSX + 25, nSY + 22, FALSE, FALSE, TRUE);
		}
	}

}

BOOL CMarketUpWnd::OnLButtonUp(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse)
{
	if ( mUserMarketUp_BtnClose.OnLButtonUp(ptMouse) )
	{
		mUserMarketUp_bItemSet = FALSE;
		mUserMarketUp_nPrice = 0;
		return TRUE;
	}

	if ( mUserMarketUp_BtnCancel.OnLButtonUp(ptMouse) )
	{
		mUserMarketUp_bItemSet = FALSE;
		mUserMarketUp_nPrice = 0;
		return FALSE;
	}

	if ( mUserMarketUp_BtnRegistry.OnLButtonUp(ptMouse) )
	{
		g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_WANTTOREGISTRY, _YESNO, g_xMsg.GetMsg(4506));
		return FALSE;
	}	

	if ( PtInRect(&mUserMarketUp_rcGold, g_xGameProc.m_ptMousePos) )
	{
		if ( g_xGameProc.m_xInterface.m_bIsLargeChat == FALSE )
		{
			MoveWindow(g_xChatEditBox.GetSafehWnd(), 
					   g_xMainWnd.m_rcWindow.left+_NEW_INPUT_EDITWND_XPOS, g_xMainWnd.m_rcWindow.top+_NEW_INPUT_EDITWND_YPOS,
					   _NEW_INPUT_EDITWND_WIDTH, _NEW_INPUT_EDITWND_HEIGHT, TRUE);
		}
		else
		{
			MoveWindow(g_xChatEditBox.GetSafehWnd(), 
					   g_xMainWnd.m_rcWindow.left+_NEW_INPUT_EDITWND_XPOS, g_xMainWnd.m_rcWindow.top+_NEW_INPUT_LARGEEDITWND_YPOS,
					   _NEW_INPUT_LARGEEDITWND_WIDTH, _NEW_INPUT_EDITWND_HEIGHT, TRUE);
		}
		if ( mUserMarketUp_hDescEdit )
		{
			ShowWindow(mUserMarketUp_hDescEdit, SW_HIDE);
		}
		SetFocus(g_xMainWnd.GetSafehWnd());
		g_xChatEditBox.SetEnterUse(TRUE);

		mUserMarketUp_bSetItemPrice = TRUE;
		g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_SETVALUE, _YESNO, g_xMsg.GetMsg(4500), TRUE);
		
		return FALSE;
	}

	if ( !g_xGameProc.m_xInterface.m_stCommonItem.bSetted || pstCommonItemSet->bIsDealItem || pstCommonItemSet->bIsBeltItem || pstCommonItemSet->bIsEquipItem ||
		 !strcmp(pstCommonItemSet->xItem.m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(1050)) )
		return FALSE;

	if ( PtInRect(&mUserMarketUp_rcShowItem, g_xGameProc.m_ptMousePos) )
	{
		mUserMarketUp_xItem = pstCommonItemSet->xItem;
		mUserMarketUp_bItemSet = TRUE;

		g_xGameProc.m_xInterface.ItemClickSound(&mUserMarketUp_xItem);

		g_xGameProc.m_xInterface.m_xInventoryWnd.AddInvenItem(pstCommonItemSet->xItem, pstCommonItemSet->xItem.m_shCellNum, FALSE);

		ZeroMemory(&g_xGameProc.m_xInterface.m_stCommonItem, sizeof(COMMONITEMSET));
	}
	return FALSE;
}

BOOL CMarketUpWnd::OnLButtonDown(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse)
{
	if ( mUserMarketUp_BtnClose.OnLButtonDown(ptMouse) )
		return TRUE;

	if ( mUserMarketUp_BtnCancel.OnLButtonDown(ptMouse) )
		return TRUE;

	if ( mUserMarketUp_BtnRegistry.OnLButtonDown(ptMouse) )
		return TRUE;


	return FALSE;
}

BOOL CMarketUpWnd::OnRButtonDown(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse)
{
	return FALSE;
}

BOOL CMarketUpWnd::OnMouseMove(POINT ptMouse)
{
	mUserMarketUp_BtnClose.OnMouseMove(ptMouse);
	mUserMarketUp_BtnCancel.OnMouseMove(ptMouse);
	mUserMarketUp_BtnRegistry.OnMouseMove(ptMouse);

	RECT rcTemp = {mUserMarketUp_rcEditBox.left - 15, mUserMarketUp_rcEditBox.top - 15, mUserMarketUp_rcEditBox.right + 15, mUserMarketUp_rcEditBox.bottom + 15};
	if ( PtInRect(&rcTemp, g_xGameProc.m_ptMousePos) && g_xGameProc.m_xInterface.m_stCommonItem.bSetted )
	{
		ShowWindow(mUserMarketUp_hDescEdit, SW_HIDE);
	}
	else
	{
		if ( mUserMarketUp_bSetItemPrice == FALSE && g_xGameProc.m_xInterface.IsTopWindow(m_nID) )
			ShowWindow(mUserMarketUp_hDescEdit, SW_SHOW);
	}

	return FALSE;
}


BOOL CMarketUpWnd::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	return FALSE;
}


VOID CMarketUpWnd::CloseMarketUpWnd()
{
	if ( g_xGameProc.m_xInterface.m_bIsLargeChat == FALSE )
	{
		MoveWindow(g_xChatEditBox.GetSafehWnd(), 
				   g_xMainWnd.m_rcWindow.left+_NEW_INPUT_EDITWND_XPOS, g_xMainWnd.m_rcWindow.top+_NEW_INPUT_EDITWND_YPOS,
				   _NEW_INPUT_EDITWND_WIDTH, _NEW_INPUT_EDITWND_HEIGHT, TRUE);
	}
	else
	{
		MoveWindow(g_xChatEditBox.GetSafehWnd(), 
				   g_xMainWnd.m_rcWindow.left+_NEW_INPUT_EDITWND_XPOS, g_xMainWnd.m_rcWindow.top+_NEW_INPUT_LARGEEDITWND_YPOS,
				   _NEW_INPUT_LARGEEDITWND_WIDTH, _NEW_INPUT_EDITWND_HEIGHT, TRUE);
	}

	if ( mUserMarketUp_hDescEdit )
	{
		ShowWindow(mUserMarketUp_hDescEdit, SW_HIDE);
		SetWindowText(mUserMarketUp_hDescEdit, "");
	}
	g_xGameProc.m_xInterface.DeleteWindowToList(_WND_ID_USERMARKETUP);
	SetGameWndActive(FALSE);

	SetFocus(g_xMainWnd.GetSafehWnd());
	g_xChatEditBox.SetEnterUse(TRUE);

	mUserMarketUp_nPrice = 0;
	mUserMarketUp_nNpcId = 0;

	mUserMarketUp_bItemSet = FALSE;
	mUserMarketUp_bSetItemPrice = FALSE;
}


VOID CMarketUpWnd::RegistMyItem()
{
	TCHAR  pszMessage[4000];

	ZeroMemory(pszMessage, 4000);

	if ( mUserMarketUp_hDescEdit )
	{
		INT nLen	  = 0;
		TCHAR  pszEditMessage[4000];

		ZeroMemory(pszEditMessage, 4000);
		
		TCHAR* pszCheck = NULL;
		TCHAR* pszNextCheck = NULL;

		GetWindowText(mUserMarketUp_hDescEdit, pszEditMessage, 4000);

		pszCheck = pszEditMessage;

		while ( pszNextCheck = strchr(pszCheck, '\n') )
		{			
			*pszNextCheck = '\0';

			if ( *pszCheck == '\r' )
			{
				g_xMainWnd.StringPlus(&pszMessage[nLen], " \r", "");
				nLen += 2;
			}
			else
			{
				g_xMainWnd.StringPlus(&pszMessage[nLen], pszCheck, "");
				nLen += pszNextCheck - pszCheck;
			}

			pszNextCheck++;
			pszCheck = pszNextCheck;
		}

		if ( pszCheck[0] )
		{
			g_xMainWnd.StringPlus(&pszMessage[nLen], pszCheck, "");
		}

	}

	if ( mUserMarketUp_bItemSet && mUserMarketUp_nPrice != 0 )
	{
		CLIENTADDSELLITEM stSellItem;

		sprintf(stSellItem.szItemName, "%s", mUserMarketUp_xItem.m_stItemInfo.stStdItem.szName);
		stSellItem.nItemMakeIdx = mUserMarketUp_xItem.m_stItemInfo.nMakeIndex;
		stSellItem.nPrice = mUserMarketUp_nPrice;
		sprintf(stSellItem.szDesc, "%s", pszMessage);

		DWORD	dwCount = 0;

		if ( mUserMarketUp_xItem.m_stItemInfo.stStdItem.bThrow >= _MULTIPLE_TYPE_ITEM )
			dwCount = mUserMarketUp_xItem.m_stItemInfo.wAmount_GB;

		g_xClientSocket.SendMyItemtoMarket(mUserMarketUp_nNpcId, stSellItem, dwCount);

		CloseMarketUpWnd();
	}
}

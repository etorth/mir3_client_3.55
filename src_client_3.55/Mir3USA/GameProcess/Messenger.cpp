/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"


CMessengerWnd::CMessengerWnd()
{
	Init();
}

CMessengerWnd::~CMessengerWnd()
{
	Destroy();
}

VOID CMessengerWnd::Init()
{
	CGameWnd::Init();

	mMessenger_BtnClose.Init();
	mMessenger_BtnDelete.Init();		
	mMessenger_BtnRefresh.Init();		
	mMessenger_BtnToSendBox.Init();	
	mMessenger_BtnToGiftBox.Init();	
	mMessenger_BtnToWriteBox.Init();	
	mMessenger_BtnToReadBox.Init();	
	mMessenger_BtnToReceiveBox.Init();	
	mMessenger_BtnDeleteThis.Init();
	mMessenger_BtnReturn.Init();
	mMessenger_BtnNext.Init();			
	mMessenger_BtnPrev.Init();			
	mMessenger_BtnResetPaper.Init();	
	mMessenger_BtnSendPaper.Init();	
	mMessenger_BtnResetGift.Init();
	mMessenger_BtnSendGift.Init();
	mMessenger_BtnTakeBack.Init();

	mMessenger_xReceivedMSGList.ClearAll();
	mMessenger_xSendMSGList.ClearAll();

	mMessenger_xReceiveScrBar.Init();
	mMessenger_xSendScrBar.Init();
	mMessenger_xReadScrBar.Init();

	mMessenger_nMode		   = 0;
	mMessenger_nReceiveSelected	   = -1;
	mMessenger_nSendSelected   = -1;
	mMessenger_nReceiveStartLine = 0;
	mMessenger_nSendStartLine = 0;
	mMessenger_dwLastSendTimer = 0;

	mMessenger_nReadStartLine = 0;

	mMessenger_xReceivedMsg.ClearAll();
	mMessenger_xSendMsg.ClearAll();
	
	mMessenger_hWriteMsg = NULL;

	mMessenger_bWirteID = FALSE;
	mMessenger_bWriteMsg = FALSE;

	mMessenger_bItemReceive = FALSE;
	mMessenger_bMoneyReceive = FALSE;

	SetRect(&mMessenger_rcReadGift, 0, 0, 0, 0);
	

	SetRect(&mMessenger_rcWriteID, 0, 0, 0, 0);
	SetRect(&mMessenger_rcWriteMsg, 0, 0, 0, 0);


	mMessenger_hGiftMsg = NULL;
	mMessenger_bGiftID = FALSE;
	mMessenger_bGiftMsg = FALSE;
	mMessenger_bGiftItemSet = FALSE;

	mMessenger_nReadMode = _RECEIVED_MODE;

	ZeroMemory(mMessenger_szGiftID, 25);
	ZeroMemory(mMessenger_szWriteID, 25);
	ZeroMemory(mMessenger_szReadID, 25);
	ZeroMemory(mMessenger_szDate, 20);
	


	mMessenger_xReceivedContain.ClearAll();


	mMessenger_nMoney = 0;
	mMessenger_bSetMoney = FALSE;


	for (INT nI=0; nI<7; nI++ )
	{
		SetRect(&mMessenger_rcTitle[nI], 0, 0, 0, 0);
		SetRect(&mMessenger_rcCheck[nI], 0, 0, 0, 0);
		SetRect(&mMessenger_rcCell[nI], 0, 0, 0, 0);
	}

	mMessenger_nReceiveChecked = -1;
	mMessenger_nSendChecked = -1;

	mMessenger_bSettingMoney = FALSE;
}

VOID CMessengerWnd::Destroy()
{
	CloseMessengerWnd();

	if ( mMessenger_hWriteMsg )
	{
		DestroyWindow(mMessenger_hWriteMsg);
		mMessenger_hWriteMsg = NULL;
	}

	if ( mMessenger_hGiftMsg )
	{
		DestroyWindow(mMessenger_hGiftMsg);
		mMessenger_hGiftMsg = NULL;
	}

	CGameWnd::Destroy();
}

VOID CMessengerWnd::CreateMessengerWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend)
{
	CreateGameWnd(nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight, bBlend);

	mMessenger_BtnClose.CreateGameBtn(pxWndImage, 1221, 1222, nStartX+393, nStartY+264, g_xMsg.GetMsg(1052), _BTN_TYPE_FOCUS, 1221, TRUE);
	mMessenger_BtnDelete.CreateGameBtn(pxWndImage, 212, 212, nStartX+305, nStartY+256, g_xMsg.GetMsg(4600),_BTN_TYPE_FOCUS, -1, FALSE);
	mMessenger_BtnRefresh.CreateGameBtn(pxWndImage, 214, 214, nStartX+266, nStartY+256, g_xMsg.GetMsg(4601), _BTN_TYPE_FOCUS, -1, FALSE);
	mMessenger_BtnToSendBox.CreateGameBtn(pxWndImage, 230, 230, nStartX+372, nStartY+14, g_xMsg.GetMsg(4602), _BTN_TYPE_FOCUS, -1, FALSE);
	mMessenger_BtnToGiftBox.CreateGameBtn(pxWndImage, 232, 232, nStartX+329, nStartY+14, g_xMsg.GetMsg(4603), _BTN_TYPE_FOCUS, -1, FALSE);
	mMessenger_BtnToWriteBox.CreateGameBtn(pxWndImage, 234, 234, nStartX+286, nStartY+14, g_xMsg.GetMsg(4604), _BTN_TYPE_FOCUS, -1, FALSE);
	mMessenger_BtnToReadBox.CreateGameBtn(pxWndImage, 236, 236, nStartX+243, nStartY+14, g_xMsg.GetMsg(4605), _BTN_TYPE_FOCUS, -1, FALSE);
	mMessenger_BtnToReceiveBox.CreateGameBtn(pxWndImage, 238, 238, nStartX+200, nStartY+14, g_xMsg.GetMsg(4606), _BTN_TYPE_FOCUS, -1, FALSE);
	mMessenger_BtnDeleteThis.CreateGameBtn(pxWndImage, 212, 212, nStartX+326, nStartY+256, g_xMsg.GetMsg(4607), _BTN_TYPE_FOCUS, -1, FALSE);
	mMessenger_BtnReturn.CreateGameBtn(pxWndImage, 246, 246, nStartX+286, nStartY+256, g_xMsg.GetMsg(4612), _BTN_TYPE_FOCUS, -1, FALSE);
	mMessenger_BtnNext.CreateGameBtn(pxWndImage, 242, 242, nStartX+114, nStartY+257, g_xMsg.GetMsg(4608), _BTN_TYPE_NOFOCUS, -1, TRUE);
	mMessenger_BtnPrev.CreateGameBtn(pxWndImage, 244, 244, nStartX+54, nStartY+257, g_xMsg.GetMsg(4609), _BTN_TYPE_NOFOCUS, -1, TRUE);
	mMessenger_BtnResetPaper.CreateGameBtn(pxWndImage, 272, 272, nStartX+326, nStartY+256, g_xMsg.GetMsg(4610), _BTN_TYPE_FOCUS, -1, FALSE);
	mMessenger_BtnSendPaper.CreateGameBtn(pxWndImage, 274, 274, nStartX+286, nStartY+256, g_xMsg.GetMsg(4611), _BTN_TYPE_FOCUS, -1, FALSE);
	mMessenger_BtnResetGift.CreateGameBtn(pxWndImage, 252, 252, nStartX+326, nStartY+256, g_xMsg.GetMsg(4610), _BTN_TYPE_FOCUS, -1, FALSE);
	mMessenger_BtnSendGift.CreateGameBtn(pxWndImage, 254, 254, nStartX+286, nStartY+256, g_xMsg.GetMsg(4611), _BTN_TYPE_FOCUS, -1, FALSE);
	mMessenger_BtnTakeBack.CreateGameBtn(pxWndImage, 272, 272, nStartX+286, nStartY+256, g_xMsg.GetMsg(4610), _BTN_TYPE_FOCUS, -1, FALSE);
	
	mMessenger_xReceiveScrBar.CreateScrlBar(pxWndImage, 1225, _CELL_IN_VIEW, 12, 143, 14);
	mMessenger_xSendScrBar.CreateScrlBar(pxWndImage, 1225, _CELL_IN_VIEW, 12, 143, 14);
	mMessenger_xReadScrBar.CreateScrlBar(pxWndImage, 1225, _CELL_IN_VIEW, 12, 143, 14);

	SetRect(&mMessenger_rcGiftEditBox, m_rcWnd.left+24, m_rcWnd.top+92, m_rcWnd.left+206, m_rcWnd.top+234);

	mMessenger_hWriteMsg = CreateWindowEx(NULL, _T("EDIT"), "", WS_POPUP | ES_LEFT | ES_AUTOVSCROLL | ES_MULTILINE,
								   g_xMainWnd.m_rcWindow.left + mMessenger_rcWriteMsg.left, 
								   g_xMainWnd.m_rcWindow.top + mMessenger_rcWriteMsg.top, 
								   mMessenger_rcWriteMsg.right - mMessenger_rcWriteMsg.left, 
								   mMessenger_rcWriteMsg.bottom - mMessenger_rcWriteMsg.top, 
								   g_xMainWnd.GetSafehWnd(), NULL, g_xMainWnd.GetSafehInstance(), NULL);

	if ( mMessenger_hWriteMsg )
	{
		UpdateWindow(mMessenger_hWriteMsg);
		ShowWindow(mMessenger_hWriteMsg, SW_HIDE);
		SendMessage(mMessenger_hWriteMsg, EM_LIMITTEXT, (WPARAM)500, 0);

		SendMessage(mMessenger_hWriteMsg, WM_SETFONT, (WPARAM)g_xChatEditBox.m_hFontChatEdit, MAKELPARAM(TRUE, 0));
	}

	mMessenger_hGiftMsg = CreateWindowEx(NULL, _T("EDIT"), "", WS_POPUP | ES_LEFT | ES_AUTOVSCROLL | ES_MULTILINE,
								   g_xMainWnd.m_rcWindow.left + mMessenger_rcGiftEditBox.left, 
								   g_xMainWnd.m_rcWindow.top + mMessenger_rcGiftEditBox.top, 
								   mMessenger_rcGiftEditBox.right - mMessenger_rcGiftEditBox.left, 
								   mMessenger_rcGiftEditBox.bottom - mMessenger_rcGiftEditBox.top, 
								   g_xMainWnd.GetSafehWnd(), NULL, g_xMainWnd.GetSafehInstance(), NULL);

	if ( mMessenger_hGiftMsg )
	{
		UpdateWindow(mMessenger_hGiftMsg);
		ShowWindow(mMessenger_hGiftMsg, SW_HIDE);
		SendMessage(mMessenger_hGiftMsg, EM_LIMITTEXT, (WPARAM)500, 0);

		SendMessage(mMessenger_hGiftMsg, WM_SETFONT, (WPARAM)g_xChatEditBox.m_hFontChatEdit, MAKELPARAM(TRUE, 0));
	}

	for (INT nI=0; nI<7; nI++ )
	{
		SetRect(&mMessenger_rcTitle[nI], m_rcWnd.left + 138, m_rcWnd.top + 64 + 24*nI, m_rcWnd.left + 358, m_rcWnd.top + 83 + 24*nI);
		SetRect(&mMessenger_rcCheck[nI], m_rcWnd.left + 22, m_rcWnd.top + 72 + 24*nI, m_rcWnd.left + 35, m_rcWnd.top + 87 + 24*nI);
		SetRect(&mMessenger_rcCell[nI], m_rcWnd.left + 43, m_rcWnd.top + 69 + 24*nI, m_rcWnd.left +	366, m_rcWnd.top + 88 + 24*nI);
	}

	SetRect(&mMessenger_rcReadGift, m_rcWnd.left + 230, m_rcWnd.top + 60, m_rcWnd.left + 250, m_rcWnd.top + 80);

	SetRect(&mMessenger_rcWriteID, m_rcWnd.left + 24, m_rcWnd.top + 69, m_rcWnd.left + 206, m_rcWnd.top + 86);
	SetRect(&mMessenger_rcWriteMsg, m_rcWnd.left + 24, m_rcWnd.top + 91, m_rcWnd.left + 401, m_rcWnd.top + 234);

	SetRect(&mMessenger_rcGiftID, m_rcWnd.left + 24, m_rcWnd.top + 69, m_rcWnd.left + 207, m_rcWnd.top + 84);

	SetRect(&mMessenger_rcGiftShowItem, m_rcWnd.left + 214, m_rcWnd.top + 65, m_rcWnd.left + 402, m_rcWnd.top + 236);
}	
		
VOID CMessengerWnd::ShowMessengerWnd()
{
	ShowGameWnd();

	// 공통으로 보여 줘야 할 부분

	// 제목 그리기

	switch(mMessenger_nMode)
	{
	case _RECEIVED_BOX:
		ShowReceivedBox();
		break;
	case _READ_BOX:
		ShowReadBox();
		break;
	case _WRITE_BOX:
		ShowWriteBox();
		break;
	case _GIFT_BOX:
		ShowGiftBox();
		break;
	case _SEND_BOX:
		ShowSendBox();
		break;
	}
	
	// 공통 버튼 그림
	mMessenger_BtnToReceiveBox.ChangeRect(m_rcWnd.left+199, m_rcWnd.top+18);
	mMessenger_BtnToReadBox.ChangeRect(m_rcWnd.left+241, m_rcWnd.top+18);
	mMessenger_BtnToWriteBox.ChangeRect(m_rcWnd.left+284, m_rcWnd.top+18);
	mMessenger_BtnToGiftBox.ChangeRect(m_rcWnd.left+327, m_rcWnd.top+18);
	mMessenger_BtnToSendBox.ChangeRect(m_rcWnd.left+370, m_rcWnd.top+18);
	mMessenger_BtnToSendBox.ShowGameBtn();
	mMessenger_BtnToGiftBox.ShowGameBtn();
	mMessenger_BtnToWriteBox.ShowGameBtn();
	mMessenger_BtnToReadBox.ShowGameBtn();
	mMessenger_BtnToReceiveBox.ShowGameBtn();
}

VOID CMessengerWnd::ShowReceivedBox()
{
	mMessenger_BtnRefresh.ChangeRect(m_rcWnd.left+304, m_rcWnd.top+265);
	mMessenger_BtnDelete.ChangeRect(m_rcWnd.left+344, m_rcWnd.top+265);

	mMessenger_xReceiveScrBar.ShowScrlBar(m_rcWnd.left+414, m_rcWnd.top+67, mMessenger_nReceiveStartLine, mMessenger_nReceiveMaxLine);

	RECT rc = {m_rcWnd.left + 34 , m_rcWnd.top + 24, m_rcWnd.left + 176, m_rcWnd.top + 39};
	g_xMainWnd.PutsHan(NULL, rc, RGB(250, 220, 248), 0, g_xMsg.GetMsg(4618));

	// 받은 쪽지함 탭 활성화 그림
	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(238) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+199, m_rcWnd.top+18, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
	}

	for ( INT nI=0; nI<7; nI++ )			 //good
	{
		if ( mMessenger_nReceiveChecked == mMessenger_nReceiveStartLine+nI && nI < mMessenger_nReceiveStartLine+7 )
		{
			if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(221) )
			{
				g_xMainWnd.DrawWithImageForComp(mMessenger_rcCheck[nI].left, mMessenger_rcCheck[nI].top+2, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
												(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
			}
		}
	}

	for ( nI=0; nI<7; nI++ )
	{
		SetRect(&mMessenger_rcTitle[nI], m_rcWnd.left + 138, m_rcWnd.top + 69+ 24*nI, m_rcWnd.left + 358, m_rcWnd.top + 88 + 24*nI);
		SetRect(&mMessenger_rcCheck[nI], m_rcWnd.left + 22, m_rcWnd.top + 72 + 24*nI, m_rcWnd.left + 35, m_rcWnd.top + 87 + 24*nI);
		SetRect(&mMessenger_rcCell[nI], m_rcWnd.left + 43, m_rcWnd.top + 69 + 24*nI, m_rcWnd.left +	366, m_rcWnd.top + 88 + 24*nI);
	}


	// 마우스 있는 곳 뒷판
	if ( mMessenger_nMouseLacated != -1 )
	{
		D3DMATERIAL7 mtrl;
		D3DVECTOR	 vecTrans((FLOAT)mMessenger_rcCell[mMessenger_nMouseLacated].left, (FLOAT)mMessenger_rcCell[mMessenger_nMouseLacated].top, 0);
		D3DVECTOR	 vecScale((FLOAT)mMessenger_rcCell[mMessenger_nMouseLacated].right-mMessenger_rcCell[mMessenger_nMouseLacated].left, 
			mMessenger_rcCell[mMessenger_nMouseLacated].bottom-mMessenger_rcCell[mMessenger_nMouseLacated].top, 1);

		D3DUtil_InitMaterial(mtrl, (FLOAT)70/255.0f, (FLOAT)70/255.0f, (FLOAT)70/255.0f);
		mtrl.diffuse.a = 180.0f/255.0f;
		g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
	}

	if ( mMessenger_nReceiveSelected != -1 && mMessenger_nReceiveSelected-mMessenger_nReceiveStartLine >= 0 && mMessenger_nReceiveSelected-mMessenger_nReceiveStartLine < 7)
	{
		D3DMATERIAL7 mtrl;
		D3DVECTOR	 vecTrans((FLOAT)mMessenger_rcCell[mMessenger_nReceiveSelected-mMessenger_nReceiveStartLine].left, (FLOAT)mMessenger_rcCell[mMessenger_nReceiveSelected-mMessenger_nReceiveStartLine].top, 0);
		D3DVECTOR	 vecScale((FLOAT)mMessenger_rcCell[mMessenger_nReceiveSelected-mMessenger_nReceiveStartLine].right-mMessenger_rcCell[mMessenger_nReceiveSelected-mMessenger_nReceiveStartLine].left, 
			mMessenger_rcCell[mMessenger_nReceiveSelected-mMessenger_nReceiveStartLine].bottom-mMessenger_rcCell[mMessenger_nReceiveSelected-mMessenger_nReceiveStartLine].top, 1);

		D3DUtil_InitMaterial(mtrl, (FLOAT)35/255.0f, (FLOAT)114/255.0f, (FLOAT)156/255.0f);
		mtrl.diffuse.a = 180.0f/255.0f;
		g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
	}


	CListNode < CLIENTDHLTITLE > *pNode;
	INT  nLine, nListCnt;
	LPCLIENTDHLTITLE pstDhlTitle = NULL;
	RECT rcName = { m_rcWnd.left + 43, m_rcWnd.top + 71, m_rcWnd.left + 137, m_rcWnd.top + 86};
	RECT rcTitle = { m_rcWnd.left + 141, m_rcWnd.top + 71, m_rcWnd.left + 362, m_rcWnd.top + 86};

	BOOL	bNewMessage = FALSE;

	for ( pNode = mMessenger_xReceivedMSGList.GetHead(), nListCnt = 0, nLine = 0; pNode; pNode = pNode->GetNext(), nListCnt++ )
	{
		pstDhlTitle = pNode->GetData();

		if ( pstDhlTitle->wReadCheck == FALSE )
			bNewMessage = TRUE;

		if ( nListCnt < mMessenger_nReceiveStartLine || nListCnt > mMessenger_nReceiveStartLine + 6 )
			continue;

		g_xMainWnd.PutsHan(NULL, rcName, RGB( 250,  250,  250), 0, pstDhlTitle->szWho);
		g_xMainWnd.PutsHan(NULL, rcTitle, RGB( 250,  250,  250), 0, pstDhlTitle->szTitle);

		if ( pstDhlTitle->wDhlType == 0 )
		{
			INT nImg;
			if ( pstDhlTitle->wReadCheck )
				nImg = 218;
			else
				nImg = 217;

			if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(nImg) )
			{
				g_xMainWnd.DrawWithImageForComp(rcTitle.left+241, rcTitle.top, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
												(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
			}

		}
		else if ( pstDhlTitle->wDhlType == 1 )
		{
			INT nImg;
			POINT ptLoc;
			if ( pstDhlTitle->wReadCheck )
			{
				ptLoc.x = rcTitle.left+239;
				ptLoc.y = rcTitle.top+2;
				nImg = 220;
			}
			else
			{
				ptLoc.x = rcTitle.left+239;
				ptLoc.y = rcTitle.top;
				nImg = 219;
			}

			if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(nImg) )
			{
				g_xMainWnd.DrawWithImageForComp(ptLoc.x, ptLoc.y, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
												(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
			}

		}

		rcName.top += 24;
		rcName.bottom += 24;
		rcTitle.top += 24;
		rcTitle.bottom += 24;
	}


	if ( bNewMessage == FALSE )
		g_xGameProc.m_xInterface.m_bHasNewMessage = FALSE;

	mMessenger_BtnClose.ShowGameBtn();
	mMessenger_BtnDelete.ShowGameBtn();
	mMessenger_BtnRefresh.ShowGameBtn();
}

VOID CMessengerWnd::ShowReadBox()
{
	mMessenger_BtnDeleteThis.ChangeRect(m_rcWnd.left+344, m_rcWnd.top+265);
	mMessenger_BtnReturn.ChangeRect(m_rcWnd.left+304, m_rcWnd.top+265);
	mMessenger_BtnNext.ChangeRect(m_rcWnd.left+74, m_rcWnd.top+263);
	mMessenger_BtnPrev.ChangeRect(m_rcWnd.left+34, m_rcWnd.top+263);

	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(240) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+1, m_rcWnd.top + 55, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
	}

	if ( mMessenger_nReadMode == _RECEIVED_MODE )
		mMessenger_nReadMaxLine = mMessenger_xReceivedMsg.GetCount();
	else
		mMessenger_nReadMaxLine = mMessenger_xSendMsg.GetCount();

	RECT rcTitle = {m_rcWnd.left + 34 , m_rcWnd.top + 24, m_rcWnd.left + 176, m_rcWnd.top + 39};
	g_xMainWnd.PutsHan(NULL, rcTitle, RGB(250, 220, 248), 0, g_xMsg.GetMsg(4619));

	mMessenger_xReadScrBar.ShowScrlBar(m_rcWnd.left+414, m_rcWnd.top+67, mMessenger_nReadStartLine, mMessenger_nReadMaxLine);

	if ( mMessenger_bItemReceive )
	{
		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(219) )
		{
			g_xMainWnd.DrawWithImageForComp(m_rcWnd.left + 230, m_rcWnd.top + 67, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
		}

		if ( PtInRect(&mMessenger_rcReadGift, g_xGameProc.m_ptMousePos) )
		{
			mMessenger_xReceivedItem.ShowItemStatus(mMessenger_rcReadGift.left + 15, mMessenger_rcReadGift.top + 15, FALSE, FALSE, TRUE);
		}

	}
	else if ( mMessenger_bMoneyReceive )
	{
		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(219) )
		{
			g_xMainWnd.DrawWithImageForComp(m_rcWnd.left + 230, m_rcWnd.top + 60, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
		}

		if ( PtInRect(&mMessenger_rcReadGift, g_xGameProc.m_ptMousePos) )
		{
			RECT rcDesc = { mMessenger_rcReadGift.left + 10, mMessenger_rcReadGift.top + 15, mMessenger_rcReadGift.left + 100, mMessenger_rcReadGift.top + 35 };
			CHAR szTemp[MAX_PATH];

			sprintf( szTemp, "%s %d", g_xMsg.GetMsg(1050), mMessenger_nMoneyGift);

			D3DVECTOR	 vecTrans((FLOAT)(rcDesc.left), (FLOAT)(rcDesc.top), 0);
			D3DVECTOR	 vecScale((FLOAT)(rcDesc.right - rcDesc.left), (FLOAT)(rcDesc.bottom - rcDesc.top), 1);
			D3DMATERIAL7 mtrl;

			D3DUtil_InitMaterial(mtrl, (FLOAT)100/255.0f, (FLOAT)100/255.0f, (FLOAT)50/255.0f);
			mtrl.diffuse.a = 230.0f/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

			g_xMainWnd.DrawWithGDI(&rcDesc, NULL, RGB(150, 150, 50), 1);

			g_xMainWnd.PutsHan(NULL, rcDesc, RGB( 250,  250,  0), 0, szTemp);
//			mMessenger_xReceivedItem.ShowItemStatus(mMessenger_rcReadGift.left + 15, mMessenger_rcReadGift.top + 15, FALSE, FALSE, TRUE);
		}
	}

	if ( mMessenger_nReadMode == _RECEIVED_MODE )
	{
		// 설명
		if ( !mMessenger_xReceivedMsg.IsEmpty() )
		{
			INT		nCnt, nShowLine;
			LPCHAT	pstChat;
			RECT	rcID = {m_rcWnd.left + 23, m_rcWnd.top + 68, m_rcWnd.left + 206, m_rcWnd.top + 83};
			RECT	rcDesc = {m_rcWnd.left + 23, m_rcWnd.top + 88, m_rcWnd.left + 400, m_rcWnd.top + 229};
			RECT	rcDate = {m_rcWnd.left + 217, m_rcWnd.top + 68, m_rcWnd.left + 402, m_rcWnd.top + 83};

			g_xMainWnd.PutsHan(NULL, rcID, RGB( 250,  250,  250), 0, mMessenger_szReadID);
			g_xMainWnd.PutsHan(NULL, rcDate, RGB( 250,  250,  250), 0, mMessenger_szDate);
			
			CListNode < CHAT >		*pNode;

			pNode = mMessenger_xReceivedMsg.GetHead();

			nShowLine = mMessenger_xReceivedMsg.GetCount();

			mMessenger_nReadStartLine;
			mMessenger_nReadMaxLine;

			for ( nCnt = 0; nCnt < nShowLine; nCnt++ )
			{
				if ( nCnt < mMessenger_nReadStartLine || nCnt > mMessenger_nReadStartLine + 10)
				{
					pNode = pNode->GetNext();
					continue;
				}

				pstChat = *pNode;

				if ( pstChat )
				{
					DWORD dwFontColor = RGB(0, 0, 0);
					INT nX = 0;

					g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(),
									   rcDesc.left+nX+7, rcDesc.top+(nCnt-mMessenger_nReadStartLine)*12+5,
									   dwFontColor, pstChat->dwBackColor, pstChat->pszChat);
					g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(),
									   rcDesc.left+nX+9, rcDesc.top+(nCnt-mMessenger_nReadStartLine)*12+5,
									   dwFontColor, pstChat->dwBackColor, pstChat->pszChat);
					g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(),
									   rcDesc.left+nX+8, rcDesc.top+(nCnt-mMessenger_nReadStartLine)*12+4,
									   dwFontColor, pstChat->dwBackColor, pstChat->pszChat);
					g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(),
									   rcDesc.left+nX+8, rcDesc.top+(nCnt-mMessenger_nReadStartLine)*12+6,
									   dwFontColor, pstChat->dwBackColor, pstChat->pszChat);
					g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(),
									   rcDesc.left+nX+8, rcDesc.top+(nCnt-mMessenger_nReadStartLine)*12+5,
									   pstChat->dwFontColor, pstChat->dwBackColor, pstChat->pszChat);
				}
				pNode = pNode->GetNext();
			}
		}

		CListNode < CLIENTDHLTITLE > *pNode;
		INT  nLine, nListCnt;
		LPCLIENTDHLTITLE pstDhlTitle = NULL;
		BOOL	bNewMessage = FALSE;

		for ( pNode = mMessenger_xReceivedMSGList.GetHead(), nListCnt = 0, nLine = 0; pNode; pNode = pNode->GetNext(), nListCnt++ )
		{
			pstDhlTitle = pNode->GetData();

			if ( pstDhlTitle->wReadCheck == FALSE )
				bNewMessage = TRUE;

		}

		if ( bNewMessage == FALSE )
			g_xGameProc.m_xInterface.m_bHasNewMessage = FALSE;
	}
	else if ( mMessenger_nReadMode == _SEND_MODE )
	{
		// 설명
		if ( !mMessenger_xSendMsg.IsEmpty() )
		{
			INT		nCnt, nShowLine;
			LPCHAT	pstChat;
			RECT	rcID = {m_rcWnd.left + 68, m_rcWnd.top + 60, m_rcWnd.left + 216, m_rcWnd.top + 77};
			RECT	rcDesc = {m_rcWnd.left + 21, m_rcWnd.top + 84, m_rcWnd.left + 394, m_rcWnd.top + 225};
			RECT	rcDate = {m_rcWnd.left + 275, m_rcWnd.top + 62, m_rcWnd.left + 377, m_rcWnd.top + 79};

			g_xMainWnd.PutsHan(NULL, rcID, RGB( 250,  250,  250), 0, mMessenger_szReadID);
			g_xMainWnd.PutsHan(NULL, rcDate, RGB( 250,  250,  250), 0, mMessenger_szDate);
			
			
			CListNode < CHAT >		*pNode;

			pNode = mMessenger_xSendMsg.GetHead();

			nShowLine = mMessenger_xSendMsg.GetCount();

			for ( nCnt = 0; nCnt < nShowLine; nCnt++ )
			{
				if ( nCnt < mMessenger_nReadStartLine || nCnt > mMessenger_nReadStartLine + 10)
				{
					pNode = pNode->GetNext();
					continue;
				}

				pstChat = *pNode;

				if ( pstChat )
				{
					DWORD dwFontColor = RGB(0, 0, 0);
					INT nX = 0;

					g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(),
									   rcDesc.left+nX+7, rcDesc.top+(nCnt-mMessenger_nReadStartLine)*12+5,
									   dwFontColor, pstChat->dwBackColor, pstChat->pszChat);
					g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(),
									   rcDesc.left+nX+9, rcDesc.top+(nCnt-mMessenger_nReadStartLine)*12+5,
									   dwFontColor, pstChat->dwBackColor, pstChat->pszChat);
					g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(),
									   rcDesc.left+nX+8, rcDesc.top+(nCnt-mMessenger_nReadStartLine)*12+4,
									   dwFontColor, pstChat->dwBackColor, pstChat->pszChat);
					g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(),
									   rcDesc.left+nX+8, rcDesc.top+(nCnt-mMessenger_nReadStartLine)*12+6,
									   dwFontColor, pstChat->dwBackColor, pstChat->pszChat);
					g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(),
									   rcDesc.left+nX+8, rcDesc.top+(nCnt-mMessenger_nReadStartLine)*12+5,
									   pstChat->dwFontColor, pstChat->dwBackColor, pstChat->pszChat);
				}

				pNode = pNode->GetNext();
			}
		}
	}

	// 읽기창 탭 활성화 그림
	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(236) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+241, m_rcWnd.top+18, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
	}

	mMessenger_BtnClose.ShowGameBtn();
	mMessenger_BtnDeleteThis.ShowGameBtn();
	mMessenger_BtnReturn.ShowGameBtn();
	mMessenger_BtnNext.ShowGameBtn();
	mMessenger_BtnPrev.ShowGameBtn();
	
}

VOID CMessengerWnd::ShowWriteBox()
{
	mMessenger_BtnResetPaper.ChangeRect(m_rcWnd.left+344, m_rcWnd.top+265);
	mMessenger_BtnSendPaper.ChangeRect(m_rcWnd.left+304, m_rcWnd.top+265);

	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(270) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+1, m_rcWnd.top + 55, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
	}

	RECT rcTitle = {m_rcWnd.left + 34 , m_rcWnd.top + 24, m_rcWnd.left + 176, m_rcWnd.top + 39};
	g_xMainWnd.PutsHan(NULL, rcTitle, RGB(250, 220, 248), 0, g_xMsg.GetMsg(4620));

	if ( mMessenger_bWirteID )
	{
		CHAR szTemp[MAX_PATH];
		GetWindowText(g_xChatEditBox.GetSafehWnd(), szTemp, MAX_PATH);

		if ( szTemp[0] != NULL )
			sprintf(mMessenger_szWriteID, szTemp);
	}

	if ( mMessenger_szWriteID[0] != NULL )
		g_xMainWnd.PutsHan(NULL, mMessenger_rcWriteID.left, mMessenger_rcWriteID.top, RGB(250, 250, 250), 0, mMessenger_szWriteID);

	ShowWindow(mMessenger_hWriteMsg, SW_SHOW);

	MoveWindow(mMessenger_hWriteMsg, g_xMainWnd.m_rcWindow.left + mMessenger_rcWriteMsg.left, 
	 		   g_xMainWnd.m_rcWindow.top + mMessenger_rcWriteMsg.top, 
			   mMessenger_rcWriteMsg.right - mMessenger_rcWriteMsg.left, 
			   mMessenger_rcWriteMsg.bottom - mMessenger_rcWriteMsg.top, TRUE);

	// 쓰기창 탭 활성화 그림H
	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(234) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+284, m_rcWnd.top+18, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
	}

	mMessenger_BtnClose.ShowGameBtn();
	mMessenger_BtnResetPaper.ShowGameBtn();
	mMessenger_BtnSendPaper.ShowGameBtn();	
}

VOID CMessengerWnd::ShowGiftBox()
{
	mMessenger_BtnResetGift.ChangeRect(m_rcWnd.left+344, m_rcWnd.top+265);
	mMessenger_BtnSendGift.ChangeRect(m_rcWnd.left+304, m_rcWnd.top+265);

	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(250) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+1, m_rcWnd.top + 55, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
	}

	if ( mMessenger_bGiftID && !mMessenger_bSettingMoney )
	{
		CHAR szTemp[MAX_PATH];
		GetWindowText(g_xChatEditBox.GetSafehWnd(), szTemp, MAX_PATH);

		if ( szTemp[0] != NULL )
			sprintf(mMessenger_szGiftID, szTemp);
	}

	if ( mMessenger_szGiftID[0] != NULL )
		g_xMainWnd.PutsHan(NULL, mMessenger_rcGiftID, RGB(250, 250, 250), 0, mMessenger_szGiftID);

	ShowWindow(mMessenger_hGiftMsg, SW_SHOW);
/*
	if ( mMessenger_bGiftID )
		ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);
	else
		ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_HIDE);
*/
	// 선물함 탭 활성화 그림
	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(232) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+327, m_rcWnd.top+18, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
	}

	mMessenger_BtnClose.ShowGameBtn();
	mMessenger_BtnResetGift.ShowGameBtn();
	mMessenger_BtnSendGift.ShowGameBtn();


	RECT rcTitle = {m_rcWnd.left + 34 , m_rcWnd.top + 24, m_rcWnd.left + 176, m_rcWnd.top + 39};
	g_xMainWnd.PutsHan(NULL, rcTitle, RGB(250, 220, 248), 0, g_xMsg.GetMsg(4617));

	if ( !mMessenger_bGiftItemSet )
	{
		RECT rcDesc1 = {m_rcWnd.left + 234, m_rcWnd.top + 105, m_rcWnd.left + 392, m_rcWnd.top + 120};
		g_xMainWnd.PutsHan(NULL, rcDesc1, RGB(248, 200, 100), RGB(0,0,0), g_xMsg.GetMsg(4614));
		RECT rcDesc2 = {m_rcWnd.left + 234, m_rcWnd.top + 123, m_rcWnd.left + 392, m_rcWnd.top + 138};
		g_xMainWnd.PutsHan(NULL, rcDesc2, RGB(248, 200, 100), RGB(0,0,0), g_xMsg.GetMsg(4615));
		return;
	}

	CWHWilImageData* pxItemImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_INVENTORY];

	if ( pxItemImg->NewSetIndex(mMessenger_xItem.m_stItemInfo.stStdItem.wLooks) )
	{
		INT nCX = m_rcWnd.left + 315;
		INT nCY = m_rcWnd.top + 138;

		INT nSX = nCX - pxItemImg->m_lpstNewCurrWilImageInfo->shWidth/2;
		INT nSY = nCY - pxItemImg->m_lpstNewCurrWilImageInfo->shHeight/2;

		RECT rcImg;
		if ( pxItemImg->m_lpstNewCurrWilImageInfo->shHeight > 170 )
		{
			SetRect(&rcImg, 0, 0, pxItemImg->m_lpstNewCurrWilImageInfo->shWidth, 130);
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
		
		if ( mMessenger_xItem.m_stItemInfo.stStdItem.bStdMode == 10 || mMessenger_xItem.m_stItemInfo.stStdItem.bStdMode == 11 )
		{
			wClr = g_xMainWnd.ConvertColor24To16(RGB(mMessenger_xItem.m_stItemInfo.bLevel_R, 
													 LOBYTE(mMessenger_xItem.m_stItemInfo.wAmount_GB), 
													 HIBYTE(mMessenger_xItem.m_stItemInfo.wAmount_GB))); 
		}

		g_xMainWnd.DrawWithImageForComp(nSX, nSY, &rcImg, (WORD*)pxItemImg->m_pbCurrImage, wClr);

		if ( mMessenger_xItem.m_stItemInfo.stStdItem.bThrow >= _MULTIPLE_TYPE_ITEM )
		{
			RECT rc;
			CHAR pszTmp[MAX_PATH];

			DWORD	dwCount = mMessenger_xItem.m_stItemInfo.wAmount_GB;

			sprintf(pszTmp, "%d", dwCount);
			g_xMainWnd.PutsHan(NULL, nSX + 23, nSY + 22, RGB(255, 255, 0), RGB(0,0,0), pszTmp);
		}

		if ( PtInRect(&mMessenger_rcGiftShowItem, g_xGameProc.m_ptMousePos) )
		{
			mMessenger_xItem.ShowItemStatus(nSX + 25, nSY + 22, FALSE, FALSE, TRUE);
		}
	}

	if ( mMessenger_bSetMoney )
	{
		INT nCX = m_rcWnd.left + 300;
		INT nCY = m_rcWnd.top + 160;
		RECT rcGold = { m_rcWnd.left + 280, m_rcWnd.top + 153, m_rcWnd.left + 350, m_rcWnd.top + 168 };

		CHAR szTmp[MAX_PATH];

		sprintf(szTmp, "%d", mMessenger_nMoney);
		g_xMainWnd.PutsHan(NULL, rcGold, RGB( 250,  250,  250), 0, szTmp);
	}

}

VOID CMessengerWnd::ShowSendBox()
{
	mMessenger_BtnDelete.ChangeRect(m_rcWnd.left+344, m_rcWnd.top+265);
	mMessenger_BtnTakeBack.ChangeRect(m_rcWnd.left+344, m_rcWnd.top+265);
	mMessenger_BtnRefresh.ChangeRect(m_rcWnd.left+344, m_rcWnd.top+265);

	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(260) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+1, m_rcWnd.top + 55, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
	}

	mMessenger_BtnRefresh.ChangeRect(m_rcWnd.left+264, m_rcWnd.top+265);
	mMessenger_BtnTakeBack.ChangeRect(m_rcWnd.left+304, m_rcWnd.top+265);
	mMessenger_BtnDelete.ChangeRect(m_rcWnd.left+344, m_rcWnd.top+265);

	RECT rc = {m_rcWnd.left + 34 , m_rcWnd.top + 24, m_rcWnd.left + 176, m_rcWnd.top + 39};
	g_xMainWnd.PutsHan(NULL, rc, RGB(250, 220, 248), 0, g_xMsg.GetMsg(4621));

	mMessenger_xSendScrBar.ShowScrlBar(m_rcWnd.left+414, m_rcWnd.top+67, mMessenger_nSendStartLine, mMessenger_nSendMaxLine);

	for ( INT nI=0; nI<7; nI++ )			 //good
	{
		if ( mMessenger_nSendChecked == mMessenger_nSendStartLine+nI && nI < mMessenger_nSendStartLine+7 )
		{
			if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(221) )
			{
				g_xMainWnd.DrawWithImageForComp(mMessenger_rcCheck[nI].left, mMessenger_rcCheck[nI].top+2, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
												(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
			}
		}
	}

	// 마우스 있는 곳 뒷판
	if ( mMessenger_nMouseLacated != -1 )
	{
		D3DMATERIAL7 mtrl;
		D3DVECTOR	 vecTrans((FLOAT)mMessenger_rcCell[mMessenger_nMouseLacated].left, (FLOAT)mMessenger_rcCell[mMessenger_nMouseLacated].top, 0);
		D3DVECTOR	 vecScale((FLOAT)mMessenger_rcCell[mMessenger_nMouseLacated].right-mMessenger_rcCell[mMessenger_nMouseLacated].left, 
			mMessenger_rcCell[mMessenger_nMouseLacated].bottom-mMessenger_rcCell[mMessenger_nMouseLacated].top, 1);

		D3DUtil_InitMaterial(mtrl, (FLOAT)70/255.0f, (FLOAT)70/255.0f, (FLOAT)70/255.0f);
		mtrl.diffuse.a = 180.0f/255.0f;
		g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
	}

	if ( mMessenger_nSendSelected != -1 && mMessenger_nSendSelected-mMessenger_nSendStartLine >= 0 && mMessenger_nSendSelected-mMessenger_nSendStartLine < 7)
	{
		D3DMATERIAL7 mtrl;
		D3DVECTOR	 vecTrans((FLOAT)mMessenger_rcCell[mMessenger_nSendSelected-mMessenger_nSendStartLine].left, (FLOAT)mMessenger_rcCell[mMessenger_nSendSelected-mMessenger_nSendStartLine].top, 0);
		D3DVECTOR	 vecScale((FLOAT)mMessenger_rcCell[mMessenger_nSendSelected-mMessenger_nSendStartLine].right-mMessenger_rcCell[mMessenger_nSendSelected-mMessenger_nSendStartLine].left, 
			mMessenger_rcCell[mMessenger_nSendSelected-mMessenger_nSendStartLine].bottom-mMessenger_rcCell[mMessenger_nSendSelected-mMessenger_nSendStartLine].top, 1);

		D3DUtil_InitMaterial(mtrl, (FLOAT)35/255.0f, (FLOAT)114/255.0f, (FLOAT)156/255.0f);
		mtrl.diffuse.a = 180.0f/255.0f;
		g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
	}


	CListNode < CLIENTDHLTITLE > *pNode;
	INT  nLine, nListCnt;
	LPCLIENTDHLTITLE pstDhlTitle = NULL;
	RECT rcName = { m_rcWnd.left + 43, m_rcWnd.top + 71, m_rcWnd.left + 137, m_rcWnd.top + 86};
	RECT rcTitle = { m_rcWnd.left + 141, m_rcWnd.top + 71, m_rcWnd.left + 362, m_rcWnd.top + 86};

	for ( pNode = mMessenger_xSendMSGList.GetHead(), nListCnt = 0, nLine = 0; pNode; pNode = pNode->GetNext(), nListCnt++ )
	{
		pstDhlTitle = pNode->GetData();

		if ( nListCnt < mMessenger_nSendStartLine || nListCnt > mMessenger_nSendStartLine + 6 )
			continue;

		g_xMainWnd.PutsHan(NULL, rcName, RGB( 250,  250,  250), 0, pstDhlTitle->szWho);
		g_xMainWnd.PutsHan(NULL, rcTitle, RGB( 250,  250,  250), 0, pstDhlTitle->szTitle);

		if ( pstDhlTitle->wDhlType == 0 )
		{
			INT nImg;
			if ( pstDhlTitle->wReadCheck )
				nImg = 218;
			else
				nImg = 217;

			if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(nImg) )
			{
				g_xMainWnd.DrawWithImageForComp(rcTitle.left+241, rcTitle.top, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
												(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
			}

		}
		else if ( pstDhlTitle->wDhlType == 1 )
		{
			INT nImg;
			POINT ptLoc;
			if ( pstDhlTitle->wReadCheck )
			{
				ptLoc.x = rcTitle.left+239;
				ptLoc.y = rcTitle.top+2;
				nImg = 220;
			}
			else
			{
				ptLoc.x = rcTitle.left+239;
				ptLoc.y = rcTitle.top;
				nImg = 219;
			}

			if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(nImg) )
			{
				g_xMainWnd.DrawWithImageForComp(ptLoc.x, ptLoc.y, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
												(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
			}

		}

		rcName.top += 24;
		rcName.bottom += 24;
		rcTitle.top += 24;
		rcTitle.bottom += 24;
	}

	// 보낸 쪽지함 탭 활성화 그림
	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(230) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+370, m_rcWnd.top+18, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
	}

	mMessenger_BtnClose.ShowGameBtn();
	mMessenger_BtnDelete.ShowGameBtn();
	mMessenger_BtnTakeBack.ShowGameBtn();
	mMessenger_BtnRefresh.ShowGameBtn();
}


BOOL CMessengerWnd::OnLButtonUp(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse)
{
	//공통
	if ( mMessenger_BtnClose.OnLButtonUp(ptMouse) )
	{
		CloseMessengerWnd();
		return FALSE;
	}

	if ( mMessenger_BtnToSendBox.OnLButtonUp(ptMouse) )		return FALSE;
	if ( mMessenger_BtnToGiftBox.OnLButtonUp(ptMouse) ) return FALSE;
	if ( mMessenger_BtnToWriteBox.OnLButtonUp(ptMouse) ) return FALSE;
	if ( mMessenger_BtnToReadBox.OnLButtonUp(ptMouse) ) return FALSE;
	if ( mMessenger_BtnToReceiveBox.OnLButtonUp(ptMouse) ) return FALSE;

	switch( mMessenger_nMode )
	{
	case _RECEIVED_BOX:
		{
			CListNode < CLIENTDHLTITLE > *pNode;
			INT  nLine, nListCnt;
			LPCLIENTDHLTITLE pstDhlTitle = NULL;

			if ( mMessenger_BtnDelete.OnLButtonUp(ptMouse) )
			{
				if ( mMessenger_nReadMode == _RECEIVED_MODE )
				{
					for ( pNode = mMessenger_xReceivedMSGList.GetHead(), nListCnt = 0, nLine = 0; pNode; pNode = pNode->GetNext(), nListCnt++ )
					{
						if ( mMessenger_nReceiveChecked != nListCnt )
							continue;

						pstDhlTitle = pNode->GetData();
						mMessenger_nReceiveChecked = -1;
						g_xClientSocket.SendDeleteDhl(pstDhlTitle->nIndex, _RECEIVED_MODE);
					}
				}
				return FALSE;
			}

			if ( mMessenger_BtnRefresh.OnLButtonUp(ptMouse) )
			{
				g_xClientSocket.SendRefreshMailBox(0);
				return FALSE;
			}

			if ( mMessenger_xReceiveScrBar.OnLButtonUp(ptMouse) )	return FALSE;
		}
		break;
	case _READ_BOX:
		{
			CListNode < CLIENTDHLTITLE > *pNode;
			INT  nLine, nListCnt;
			LPCLIENTDHLTITLE pstDhlTitle = NULL;


			if ( mMessenger_xReadScrBar.OnLButtonUp(ptMouse) )	return FALSE;

			if ( mMessenger_BtnDeleteThis.OnLButtonUp(ptMouse) )
			{
				if ( mMessenger_nReadMode == _RECEIVED_MODE )
				{
					for ( pNode = mMessenger_xReceivedMSGList.GetHead(), nListCnt = 0, nLine = 0; pNode; pNode = pNode->GetNext(), nListCnt++ )
					{
						if ( mMessenger_nReceiveSelected != nListCnt )
							continue;

						pstDhlTitle = pNode->GetData();
						g_xClientSocket.SendDeleteDhl(pstDhlTitle->nIndex, _RECEIVED_MODE);
						ZeroMemory(mMessenger_szReadID, 25);
						ZeroMemory(mMessenger_szDate, 20);
						mMessenger_xReceivedMsg.ClearAll();
						mMessenger_nReceiveSelected = -1;
						mMessenger_nMode = _RECEIVED_BOX;
					}
				}
				else if ( mMessenger_nReadMode == _SEND_MODE )
				{
					for ( pNode = mMessenger_xSendMSGList.GetHead(), nListCnt = 0, nLine = 0; pNode; pNode = pNode->GetNext(), nListCnt++ )
					{
						if ( mMessenger_nSendSelected != nListCnt )
							continue;

						pstDhlTitle = pNode->GetData();
						g_xClientSocket.SendDeleteDhl(pstDhlTitle->nIndex, _SEND_MODE);
						ZeroMemory(mMessenger_szReadID, 25);
						ZeroMemory(mMessenger_szDate, 20);
						mMessenger_xSendMsg.ClearAll();
						mMessenger_nSendSelected = -1;
						mMessenger_nMode = _SEND_BOX;
					}
				}

				return FALSE;
			}

			if ( mMessenger_BtnReturn.OnLButtonUp(ptMouse) )
			{
				if ( mMessenger_nReadMode == _RECEIVED_MODE )
				{
					sprintf(mMessenger_szWriteID, "%s", mMessenger_szReadID);
					mMessenger_nMode = _WRITE_BOX;
					return FALSE;
				}
			}


			if ( mMessenger_BtnNext.OnLButtonUp(ptMouse) )
			{
				if ( mMessenger_nReadMode == _RECEIVED_MODE )
				{
					for ( pNode = mMessenger_xReceivedMSGList.GetHead(), nListCnt = 0, nLine = 0; pNode; pNode = pNode->GetNext(), nListCnt++ )
					{
						if ( mMessenger_nReceiveSelected + 1 != nListCnt )
							continue;

						pstDhlTitle = pNode->GetData();

						if ( g_xGameProc.m_xInterface.m_xMessengerWnd.ReadReceivedMsg(pstDhlTitle->nIndex) )
						{
							sprintf(mMessenger_szReadID, pstDhlTitle->szWho);
							sprintf(mMessenger_szDate, pstDhlTitle->szSentDate);
							mMessenger_nReceiveSelected++;
							pstDhlTitle->wReadCheck = TRUE;
							mMessenger_nMode = _READ_BOX;
							mMessenger_nReadMode = _RECEIVED_MODE;
							return FALSE;
						}
						else if ( timeGetTime() - mMessenger_dwLastSendTimer > 1000 )
						{
							g_xClientSocket.SendReadADhl(pstDhlTitle->nIndex, _RECEIVED_MODE);
							mMessenger_dwLastSendTimer = timeGetTime();

							sprintf(mMessenger_szReadID, pstDhlTitle->szWho);
							sprintf(mMessenger_szDate, pstDhlTitle->szSentDate);

							mMessenger_nReceiveSelected++;
							pstDhlTitle->wReadCheck = TRUE;
							mMessenger_nReadMode = _RECEIVED_MODE;
							return FALSE;
						}
					}
				}
				else if ( mMessenger_nReadMode == _SEND_MODE )
				{
					for ( pNode = mMessenger_xSendMSGList.GetHead(), nListCnt = 0, nLine = 0; pNode; pNode = pNode->GetNext(), nListCnt++ )
					{
						if ( mMessenger_nSendSelected + 1 != nListCnt )
							continue;

						pstDhlTitle = pNode->GetData();

						if ( g_xGameProc.m_xInterface.m_xMessengerWnd.ReadSendMsg(pstDhlTitle->nIndex) )
						{
							sprintf(mMessenger_szReadID, pstDhlTitle->szWho);
							sprintf(mMessenger_szDate, pstDhlTitle->szSentDate);
							mMessenger_nSendSelected++;
							mMessenger_nMode = _READ_BOX;
							mMessenger_nReadMode = _SEND_MODE;
							return FALSE;
						}
						else if ( timeGetTime() - mMessenger_dwLastSendTimer > 1000 )
						{
							g_xClientSocket.SendReadADhl(pstDhlTitle->nIndex, _RECEIVED_MODE);
							mMessenger_dwLastSendTimer = timeGetTime();
							sprintf(mMessenger_szReadID, pstDhlTitle->szWho);
							sprintf(mMessenger_szDate, pstDhlTitle->szSentDate);
							mMessenger_nSendSelected++;
							mMessenger_nReadMode = _SEND_MODE;
							return FALSE;
						}
					}
				}
				return FALSE;
			}

			if ( mMessenger_BtnPrev.OnLButtonUp(ptMouse) )
			{
				if ( mMessenger_nReadMode == _RECEIVED_MODE )
				{
					for ( pNode = mMessenger_xReceivedMSGList.GetHead(), nListCnt = 0, nLine = 0; pNode; pNode = pNode->GetNext(), nListCnt++ )
					{
						if ( mMessenger_nReceiveSelected - 1 != nListCnt )
							continue;

						pstDhlTitle = pNode->GetData();

						if ( g_xGameProc.m_xInterface.m_xMessengerWnd.ReadReceivedMsg(pstDhlTitle->nIndex) )
						{
							sprintf(mMessenger_szReadID, pstDhlTitle->szWho);
							sprintf(mMessenger_szDate, pstDhlTitle->szSentDate);
							mMessenger_nReceiveSelected--;
							pstDhlTitle->wReadCheck = TRUE;
							mMessenger_nMode = _READ_BOX;
							mMessenger_nReadMode = _RECEIVED_MODE;
							return FALSE;
						}
						else if ( timeGetTime() - mMessenger_dwLastSendTimer > 1000 )
						{
							g_xClientSocket.SendReadADhl(pstDhlTitle->nIndex, _RECEIVED_MODE);
							mMessenger_dwLastSendTimer = timeGetTime();

							sprintf(mMessenger_szReadID, pstDhlTitle->szWho);
							sprintf(mMessenger_szDate, pstDhlTitle->szSentDate);

							mMessenger_nReceiveSelected--;
							pstDhlTitle->wReadCheck = TRUE;
							mMessenger_nReadMode = _RECEIVED_MODE;
							return FALSE;
						}
					}
				}
				else if ( mMessenger_nReadMode == _SEND_MODE )
				{
					for ( pNode = mMessenger_xSendMSGList.GetHead(), nListCnt = 0, nLine = 0; pNode; pNode = pNode->GetNext(), nListCnt++ )
					{
						if ( mMessenger_nSendSelected - 1 != nListCnt )
							continue;

						pstDhlTitle = pNode->GetData();

						if ( g_xGameProc.m_xInterface.m_xMessengerWnd.ReadSendMsg(pstDhlTitle->nIndex) )
						{
							sprintf(mMessenger_szReadID, pstDhlTitle->szWho);
							sprintf(mMessenger_szDate, pstDhlTitle->szSentDate);
							mMessenger_nSendSelected--;
							mMessenger_nMode = _READ_BOX;
							mMessenger_nReadMode = _SEND_MODE;
							return FALSE;
						}
						else if ( timeGetTime() - mMessenger_dwLastSendTimer > 1000 )
						{
							g_xClientSocket.SendReadADhl(pstDhlTitle->nIndex, _RECEIVED_MODE);
							mMessenger_dwLastSendTimer = timeGetTime();
							sprintf(mMessenger_szReadID, pstDhlTitle->szWho);
							sprintf(mMessenger_szDate, pstDhlTitle->szSentDate);
							mMessenger_nSendSelected--;
							mMessenger_nReadMode = _SEND_MODE;
							return FALSE;
						}
					}
				}
				return FALSE;
			}
		}
		break;
	case _WRITE_BOX:
		{
			if ( mMessenger_BtnResetPaper.OnLButtonUp(ptMouse) )
			{
				SetWindowText(g_xChatEditBox.GetSafehWnd(), "");
				SetWindowText(mMessenger_hWriteMsg, "");
				return FALSE;
			}
			if ( mMessenger_BtnSendPaper.OnLButtonUp(ptMouse) )
			{
				SendMSG();
				return FALSE;
			}
		}
		break;
	case _GIFT_BOX:
		{
			
			if ( mMessenger_BtnResetGift.OnLButtonUp(ptMouse) )
			{
				SetWindowText(g_xChatEditBox.GetSafehWnd(), "");
				SetWindowText(mMessenger_hGiftMsg, "");
				mMessenger_bGiftItemSet = FALSE;
				mMessenger_bSetMoney = FALSE;
				mMessenger_nMoney = 0;
				return FALSE;
			}

			if ( mMessenger_BtnSendGift.OnLButtonUp(ptMouse) )
			{
				SendMyItem();
				return FALSE;
			}

			if ( !g_xGameProc.m_xInterface.m_stCommonItem.bSetted || pstCommonItemSet->bIsDealItem || pstCommonItemSet->bIsBeltItem )
				return FALSE;

			if ( !strcmp(g_xGameProc.m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(1050)) )
			{
				mMessenger_xItem = pstCommonItemSet->xItem;
				mMessenger_bGiftItemSet = TRUE;
				ZeroMemory(&g_xGameProc.m_xInterface.m_stCommonItem, sizeof(COMMONITEMSET));
				g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_SENDMONEY, _YESNO, g_xMsg.GetMsg(4616), TRUE);
				mMessenger_bSettingMoney = TRUE;
				return FALSE;
			}

			if ( PtInRect(&mMessenger_rcGiftShowItem, g_xGameProc.m_ptMousePos) )
			{
				mMessenger_xItem = pstCommonItemSet->xItem;
				mMessenger_bGiftItemSet = TRUE;

				g_xGameProc.m_xInterface.ItemClickSound(&mMessenger_xItem);

				g_xGameProc.m_xInterface.m_xInventoryWnd.AddInvenItem(pstCommonItemSet->xItem, pstCommonItemSet->xItem.m_shCellNum, FALSE);

				ZeroMemory(&g_xGameProc.m_xInterface.m_stCommonItem, sizeof(COMMONITEMSET));

				mMessenger_bSetMoney = FALSE;
				mMessenger_nMoney = 0;
			}
		}
		break;
	case _SEND_BOX:
		{
			CListNode < CLIENTDHLTITLE > *pNode;
			INT  nLine, nListCnt;
			LPCLIENTDHLTITLE pstDhlTitle = NULL;

			if ( mMessenger_BtnDelete.OnLButtonUp(ptMouse) )
			{
				for ( pNode = mMessenger_xSendMSGList.GetHead(), nListCnt = 0, nLine = 0; pNode; pNode = pNode->GetNext(), nListCnt++ )
				{
					if ( mMessenger_nSendChecked != nListCnt )
						continue;

					pstDhlTitle = pNode->GetData();
					mMessenger_nSendChecked = -1;
					g_xClientSocket.SendDeleteDhl(pstDhlTitle->nIndex, _SEND_MODE);
				}
				return FALSE;
			}

			if ( mMessenger_BtnRefresh.OnLButtonUp(ptMouse) )
			{
				g_xClientSocket.SendRefreshMailBox(2);
				return FALSE;
			}

			if ( mMessenger_BtnTakeBack.OnLButtonUp(ptMouse) )
			{
				for ( pNode = mMessenger_xSendMSGList.GetHead(), nListCnt = 0, nLine = 0; pNode; pNode = pNode->GetNext(), nListCnt++ )
				{
					if ( mMessenger_nSendChecked != nListCnt )
						continue;

					pstDhlTitle = pNode->GetData();
					mMessenger_nSendChecked = -1;
					g_xClientSocket.SendCancelDhl(pstDhlTitle->nIndex);
				}
				return FALSE;
			}

			if ( mMessenger_xSendScrBar.OnLButtonUp(ptMouse) )	return FALSE;
		}
		break;
	}

	return FALSE;
}

BOOL CMessengerWnd::OnLButtonDown(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse)
{
	//공통
	if ( mMessenger_BtnClose.OnLButtonDown(ptMouse) )
	{
		return FALSE;
	}

	if ( mMessenger_BtnToSendBox.OnLButtonDown(ptMouse) )
	{
		if ( mMessenger_xSendMSGList.GetCount() == 0 )
		{
			g_xClientSocket.SendRefreshMailBox(2);
		}
		mMessenger_nMode = _SEND_BOX;
//		mMessenger_nReadMode = _SEND_MODE;
		ChangeEditBoxLoc();
		return FALSE;
	}

	if ( mMessenger_BtnToGiftBox.OnLButtonDown(ptMouse) )
	{
		mMessenger_nMode = _GIFT_BOX;
		ChangeEditBoxLoc();
		return FALSE;
	}

	if ( mMessenger_BtnToWriteBox.OnLButtonDown(ptMouse) )
	{
		mMessenger_nMode = _WRITE_BOX;
		ChangeEditBoxLoc();
		return FALSE;
	}

	if ( mMessenger_BtnToReadBox.OnLButtonDown(ptMouse) )
	{
		mMessenger_nMode = _READ_BOX;
		ChangeEditBoxLoc();
		return FALSE;
	}

	if ( mMessenger_BtnToReceiveBox.OnLButtonDown(ptMouse) )
	{
		mMessenger_nMode = _RECEIVED_BOX;
		mMessenger_nReadMode = _RECEIVED_MODE;
		ChangeEditBoxLoc();
		return FALSE;
	}

	switch(mMessenger_nMode)
	{
	case _RECEIVED_BOX:
		{
			if ( mMessenger_BtnDelete.OnLButtonDown(ptMouse) )	return FALSE;
			if ( mMessenger_BtnRefresh.OnLButtonDown(ptMouse) )	return FALSE;
			if ( mMessenger_xReceiveScrBar.OnLButtonDown(ptMouse) )
			{
				FLOAT	fScrlRate;

				fScrlRate	= mMessenger_xReceiveScrBar.GetScrlRate();
				mMessenger_nReceiveStartLine = (INT)((mMessenger_nReceiveMaxLine)*fScrlRate);

				if ( mMessenger_nReceiveStartLine > mMessenger_nReceiveMaxLine - 1 )
					mMessenger_nReceiveStartLine = mMessenger_nReceiveMaxLine - 1 ;

				return TRUE;
			}

			for ( INT nI = 0; nI < 7; nI++ )
			{
				if ( PtInRect(&mMessenger_rcCheck[nI], ptMouse) )
				{
					if ( nI+mMessenger_nReceiveStartLine == mMessenger_nReceiveChecked )
						mMessenger_nReceiveChecked = -1;
					else
						mMessenger_nReceiveChecked = nI+mMessenger_nReceiveStartLine;
					return FALSE;
				}
			}
		}
		break;
	case _READ_BOX:
		{
			if ( mMessenger_xReadScrBar.OnLButtonDown(ptMouse) )
			{
				FLOAT	fScrlRate;

				fScrlRate	= mMessenger_xReadScrBar.GetScrlRate();
				mMessenger_nReadStartLine = (INT)((mMessenger_nReadMaxLine)*fScrlRate);

				if ( mMessenger_nReadStartLine > mMessenger_nReadMaxLine - 1 )
					mMessenger_nReadStartLine = mMessenger_nReadMaxLine - 1 ;

				return TRUE;
			}

			if ( mMessenger_BtnDeleteThis.OnLButtonDown(ptMouse) )	return FALSE;
			if ( mMessenger_BtnReturn.OnLButtonDown(ptMouse) )	return FALSE;
			if ( mMessenger_BtnNext.OnLButtonDown(ptMouse) )	return TRUE;
			if ( mMessenger_BtnPrev.OnLButtonDown(ptMouse) )	return TRUE;
		}
		break;
	case _WRITE_BOX:
		{
			if ( mMessenger_BtnResetPaper.OnLButtonDown(ptMouse) )	return FALSE;
			if ( mMessenger_BtnSendPaper.OnLButtonDown(ptMouse) ) return FALSE;

			if ( PtInRect(&mMessenger_rcWriteID, ptMouse) )
			{
				MoveWindow(g_xChatEditBox.GetSafehWnd(), 
						   g_xMainWnd.m_rcWindow.left+mMessenger_rcWriteID.left, 
						   g_xMainWnd.m_rcWindow.top+mMessenger_rcWriteID.top, mMessenger_rcWriteID.right-mMessenger_rcWriteID.left, 15, TRUE);
				//------------------------------------------------------------------------------------------------------------
				SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETPASSWORDCHAR, NULL, 0);

				if ( mMessenger_szWriteID[0] != NULL )
					SetWindowText(g_xChatEditBox.GetSafehWnd(), mMessenger_szWriteID);
				else
					SetWindowText(g_xChatEditBox.GetSafehWnd(), "");
				SetFocus(g_xChatEditBox.GetSafehWnd());
				ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);

				g_xChatEditBox.SetHanguelMode();
				g_xChatEditBox.SetEnterUse(FALSE);
				mMessenger_bWirteID = TRUE;
				mMessenger_bWriteMsg = FALSE;
			}

			if ( PtInRect(&mMessenger_rcWriteMsg, ptMouse) )
			{
				if ( mMessenger_bWirteID )
				{
					CHAR szTemp[MAX_PATH];
					GetWindowText(g_xChatEditBox.GetSafehWnd(), szTemp, MAX_PATH);

					if ( szTemp[0] != NULL )
						sprintf(mMessenger_szWriteID, szTemp);
				}

				ShowWindow(mMessenger_hWriteMsg, SW_SHOW);
				UpdateWindow(mMessenger_hWriteMsg);

				MoveWindow(mMessenger_hWriteMsg, g_xMainWnd.m_rcWindow.left + mMessenger_rcWriteMsg.left, 
	 					   g_xMainWnd.m_rcWindow.top + mMessenger_rcWriteMsg.top, 
						   mMessenger_rcWriteMsg.right - mMessenger_rcWriteMsg.left, 
						   mMessenger_rcWriteMsg.bottom - mMessenger_rcWriteMsg.top, TRUE);

				SetFocus(mMessenger_hWriteMsg);

				mMessenger_bWriteMsg = TRUE;
				mMessenger_bWirteID = FALSE;
			}
		}
		break;
	case _GIFT_BOX:
		{
			if ( mMessenger_BtnResetGift.OnLButtonDown(ptMouse) )	return FALSE;
			if ( mMessenger_BtnSendGift.OnLButtonDown(ptMouse) )	return FALSE;

			if ( PtInRect(&mMessenger_rcGiftID, ptMouse) )
			{
				MoveWindow(g_xChatEditBox.GetSafehWnd(), 
						   g_xMainWnd.m_rcWindow.left+mMessenger_rcGiftID.left, 
						   g_xMainWnd.m_rcWindow.top+mMessenger_rcGiftID.top, mMessenger_rcGiftID.right-mMessenger_rcGiftID.left, 15, TRUE);
				//------------------------------------------------------------------------------------------------------------
				SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETPASSWORDCHAR, NULL, 0);

				if ( mMessenger_szGiftID[0] != NULL )
					SetWindowText(g_xChatEditBox.GetSafehWnd(), mMessenger_szGiftID);
				else
					SetWindowText(g_xChatEditBox.GetSafehWnd(), "");
				SetFocus(g_xChatEditBox.GetSafehWnd());
				ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);

				g_xChatEditBox.SetHanguelMode();
				g_xChatEditBox.SetEnterUse(FALSE);
				mMessenger_bGiftID = TRUE;
				mMessenger_bGiftMsg = FALSE;
			}

			if ( PtInRect(&mMessenger_rcGiftEditBox, ptMouse) )
			{
				if ( mMessenger_bGiftID )
				{
					CHAR szTemp[MAX_PATH];
					GetWindowText(g_xChatEditBox.GetSafehWnd(), szTemp, MAX_PATH);

					if ( szTemp[0] != NULL )
						sprintf(mMessenger_szGiftID, szTemp);
				}

				ShowWindow(mMessenger_hGiftMsg, SW_SHOW);
				UpdateWindow(mMessenger_hGiftMsg);

				MoveWindow(mMessenger_hGiftMsg, g_xMainWnd.m_rcWindow.left + mMessenger_rcGiftEditBox.left, 
	 					   g_xMainWnd.m_rcWindow.top + mMessenger_rcGiftEditBox.top, 
						   mMessenger_rcGiftEditBox.right - mMessenger_rcGiftEditBox.left, 
						   mMessenger_rcGiftEditBox.bottom - mMessenger_rcGiftEditBox.top, TRUE);

				SetFocus(mMessenger_hGiftMsg);

				mMessenger_bGiftMsg = TRUE;
				mMessenger_bGiftID = FALSE;
			}
		}
		break;
	case _SEND_BOX:
		{
			if ( mMessenger_BtnTakeBack.OnLButtonDown(ptMouse) )	return FALSE;
			if ( mMessenger_BtnDelete.OnLButtonDown(ptMouse) )	return FALSE;
			if ( mMessenger_BtnRefresh.OnLButtonDown(ptMouse) )	return FALSE;
			if ( mMessenger_xSendScrBar.OnLButtonDown(ptMouse) )
			{
				FLOAT	fScrlRate;

				fScrlRate	= mMessenger_xSendScrBar.GetScrlRate();
				mMessenger_nSendStartLine = (INT)((mMessenger_nSendMaxLine)*fScrlRate);

				if ( mMessenger_nSendStartLine > mMessenger_nSendMaxLine - 1 )
					mMessenger_nSendStartLine = mMessenger_nSendMaxLine - 1 ;

				return TRUE;
			}

			for ( INT nI = 0; nI < 7; nI++ )
			{
				if ( PtInRect(&mMessenger_rcCheck[nI], ptMouse) )
				{
					if ( mMessenger_nSendChecked == nI+mMessenger_nSendStartLine )
						mMessenger_nSendChecked = -1;
					else
						mMessenger_nSendChecked = nI+mMessenger_nSendStartLine;
					return FALSE;
				}
			}
		}
		break;
	}
	


	return FALSE;
}

BOOL CMessengerWnd::OnRButtonDown(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse)
{
	return FALSE;
}

BOOL CMessengerWnd::OnLButtonDoubleClick(POINT ptMouse)
{
	if ( mMessenger_nMode == _RECEIVED_BOX )
	{
		INT nI = 0;
		for ( nI=0; nI<7; nI++ )
		{
			if ( PtInRect(&mMessenger_rcTitle[nI], g_xGameProc.m_ptMousePos) )
			{
				CListNode < CLIENTDHLTITLE > *pNode;
				INT  nLine, nListCnt;
				LPCLIENTDHLTITLE pstDhlTitle = NULL;

				for ( pNode = mMessenger_xReceivedMSGList.GetHead(), nListCnt = 0, nLine = 0; pNode; pNode = pNode->GetNext(), nListCnt++ )
				{
					if ( mMessenger_nReceiveStartLine + nI != nListCnt )
						continue;

					pstDhlTitle = pNode->GetData();

					if ( g_xGameProc.m_xInterface.m_xMessengerWnd.ReadReceivedMsg(pstDhlTitle->nIndex) )
					{
						sprintf(mMessenger_szReadID, pstDhlTitle->szWho);
						sprintf(mMessenger_szDate, pstDhlTitle->szSentDate);
						mMessenger_nReceiveSelected = nI + mMessenger_nReceiveStartLine;
						pstDhlTitle->wReadCheck = TRUE;
						mMessenger_nMode = _READ_BOX;
						mMessenger_nReadMode = _RECEIVED_MODE;
						return TRUE;
					}
					else if ( timeGetTime() - mMessenger_dwLastSendTimer > 1000 )
					{
						g_xClientSocket.SendReadADhl(pstDhlTitle->nIndex, _RECEIVED_MODE);
						mMessenger_dwLastSendTimer = timeGetTime();

						sprintf(mMessenger_szReadID, pstDhlTitle->szWho);
						sprintf(mMessenger_szDate, pstDhlTitle->szSentDate);

						mMessenger_nReceiveSelected = nI + mMessenger_nReceiveStartLine;
						pstDhlTitle->wReadCheck = TRUE;
						mMessenger_nReadMode = _RECEIVED_MODE;
					}
					break;
				}
			}
		}
	}
	else if ( mMessenger_nMode == _SEND_BOX )
	{
		INT nI = 0;
		for ( nI=0; nI<7; nI++ )
		{
			if ( PtInRect(&mMessenger_rcTitle[nI], g_xGameProc.m_ptMousePos) )
			{
				CListNode < CLIENTDHLTITLE > *pNode;
				INT  nLine, nListCnt;
				LPCLIENTDHLTITLE pstDhlTitle = NULL;

				for ( pNode = mMessenger_xSendMSGList.GetHead(), nListCnt = 0, nLine = 0; pNode; pNode = pNode->GetNext(), nListCnt++ )
				{
					if ( mMessenger_nSendStartLine + nI != nListCnt )
						continue;

					pstDhlTitle = pNode->GetData();

					if ( g_xGameProc.m_xInterface.m_xMessengerWnd.ReadSendMsg(pstDhlTitle->nIndex) )
					{
						sprintf(mMessenger_szReadID, pstDhlTitle->szWho);
						sprintf(mMessenger_szDate, pstDhlTitle->szSentDate);
						mMessenger_nSendSelected = nI + mMessenger_nSendStartLine;
						mMessenger_nMode = _READ_BOX;
						mMessenger_nReadMode = _SEND_MODE;
						return TRUE;
					}
					else if ( timeGetTime() - mMessenger_dwLastSendTimer > 1000 )
					{
						g_xClientSocket.SendReadADhl(pstDhlTitle->nIndex, _SEND_MODE);
						mMessenger_dwLastSendTimer = timeGetTime();

						sprintf(mMessenger_szReadID, pstDhlTitle->szWho);
						sprintf(mMessenger_szDate, pstDhlTitle->szSentDate);

						mMessenger_nSendSelected = nI + mMessenger_nSendStartLine;
						mMessenger_nReadMode = _SEND_MODE;
						return TRUE;
					}
					break;
				}
			}
		}
	}
	return FALSE;
}

BOOL CMessengerWnd::OnMouseMove(POINT ptMouse)
{

	// 공통
	mMessenger_BtnClose.OnMouseMove(ptMouse);
	mMessenger_BtnToSendBox.OnMouseMove(ptMouse);
	mMessenger_BtnToGiftBox.OnMouseMove(ptMouse);
	mMessenger_BtnToWriteBox.OnMouseMove(ptMouse);
	mMessenger_BtnToReadBox.OnMouseMove(ptMouse);
	mMessenger_BtnToReceiveBox.OnMouseMove(ptMouse);

	switch(mMessenger_nMode)
	{
	case _RECEIVED_BOX:
		{
			if ( mMessenger_xReceiveScrBar.OnMouseMove(ptMouse) )
			{
				FLOAT	fScrlRate;
				fScrlRate	= mMessenger_xReceiveScrBar.GetScrlRate();

				mMessenger_nReceiveStartLine = (INT)((mMessenger_nReceiveMaxLine)*fScrlRate);
				return TRUE;
			}

			for ( INT nI=0; nI<7; nI++ )
			{
				if ( PtInRect(&mMessenger_rcCell[nI], g_xGameProc.m_ptMousePos) )
				{
					mMessenger_nMouseLacated = nI;
					return FALSE;
				}
			}

			mMessenger_BtnDelete.OnMouseMove(ptMouse);
			mMessenger_BtnRefresh.OnMouseMove(ptMouse);

			mMessenger_nMouseLacated = -1;
		}
		break;
	case _READ_BOX:
		{
			if ( mMessenger_xReadScrBar.OnMouseMove(ptMouse) )
			{
				FLOAT	fScrlRate;
				fScrlRate	= mMessenger_xReadScrBar.GetScrlRate();

				mMessenger_nReadStartLine = (INT)((mMessenger_nReadMaxLine)*fScrlRate);
				return TRUE;
			}

			mMessenger_BtnDeleteThis.OnMouseMove(ptMouse);
			mMessenger_BtnReturn.OnMouseMove(ptMouse);
			mMessenger_BtnNext.OnMouseMove(ptMouse);
			mMessenger_BtnPrev.OnMouseMove(ptMouse);
		}
		break;
	case _WRITE_BOX:
		{
			mMessenger_BtnResetPaper.OnMouseMove(ptMouse);
			mMessenger_BtnSendPaper.OnMouseMove(ptMouse);
		}
		break;
	case _GIFT_BOX:
		{
			mMessenger_BtnResetGift.OnMouseMove(ptMouse);
			mMessenger_BtnSendGift.OnMouseMove(ptMouse);
		}
		break;
	case _SEND_BOX:
		{
			mMessenger_BtnDelete.OnMouseMove(ptMouse);
			mMessenger_BtnRefresh.OnMouseMove(ptMouse);
			mMessenger_BtnTakeBack.OnMouseMove(ptMouse);

			if ( mMessenger_xSendScrBar.OnMouseMove(ptMouse) )
			{
				FLOAT	fScrlRate;
				fScrlRate	= mMessenger_xSendScrBar.GetScrlRate();

				mMessenger_nSendStartLine = (INT)((mMessenger_nSendMaxLine)*fScrlRate);
				return TRUE;
			}

			for ( INT nI=0; nI<7; nI++ )
			{
				if ( PtInRect(&mMessenger_rcCell[nI], g_xGameProc.m_ptMousePos) )
				{
					mMessenger_nMouseLacated = nI;
					return FALSE;
				}
			}
		}
		break;
	}

	return FALSE;
}

VOID CMessengerWnd::OnScrollDown()
{
	switch(mMessenger_nMode)
	{
	case _READ_BOX:
		{
			if ( mMessenger_nReadStartLine > 0 )
				mMessenger_nReadStartLine--;
		}
		break;
	case _RECEIVED_BOX:
		{
			if ( mMessenger_nReceiveStartLine > 0 )
				mMessenger_nReceiveStartLine--;
		}
		break;
	case _SEND_BOX:
		{
			if ( mMessenger_nSendStartLine > 0 )
				mMessenger_nSendStartLine--;
		}
		break;
	}
}

VOID CMessengerWnd::OnScrollUp()
{
	switch(mMessenger_nMode)
	{
	case _READ_BOX:
		{
			if ( mMessenger_nReadStartLine < mMessenger_nReadMaxLine - 1 )
				mMessenger_nReadStartLine++;
		}
		break;
	case _RECEIVED_BOX:
		{
			if ( mMessenger_nReceiveStartLine < mMessenger_nReceiveMaxLine - 1 )
				mMessenger_nReceiveStartLine++;
		}
		break;
	case _SEND_BOX:
		{
			if ( mMessenger_nSendStartLine < mMessenger_nSendMaxLine - 1 )
				mMessenger_nSendStartLine++;
		}
		break;
	}
}

BOOL CMessengerWnd::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	CHAR szTemp[MAX_PATH];

	switch(mMessenger_nMode)
	{
	case _WRITE_BOX:
		{
			switch ( wParam )
			{
				case VK_RETURN:
				{
					return TRUE;
				}
			}
		}
		break;
	}
	return FALSE;
}


VOID CMessengerWnd::SetReceivedMSGList(CHAR* pszMsg, INT nCount)
{
	char *pszNext;
	INT nCnt = 0;
	LPCLIENTDHLTITLE pstDhltitle;

	// 리스트를 새로 받기 때문에 Init해야 할 것들을 Init한다.
	mMessenger_xReceivedMSGList.ClearAll();

	if ( nCount <= 0 )
		return;

	char *pszItem = (pszMsg + _DEFBLOCKSIZE);

	do
	{
		if ( pszNext = strchr(pszItem, '/') )
		{
			pstDhltitle = new CLIENTDHLTITLE;

			*pszNext = '\0';

			fnDecode6BitBuf(pszItem, (char*)pstDhltitle, sizeof(CLIENTDHLTITLE));

			pszItem = pszNext + 1;

			nCnt++;

			mMessenger_xReceivedMSGList.Insert(pstDhltitle);
		}

	} while (nCnt < nCount && pszNext);

	mMessenger_nReceiveMaxLine = nCnt;
}

VOID CMessengerWnd::AddReceivedMsg(LPCLIENTDHLCONTAIN pstDhlMsg)
{
	mMessenger_xSendMsg.ClearAll();

	mMessenger_xReceivedContain.Insert(pstDhlMsg);

	ReadReceivedMsg(pstDhlMsg->nIndex);
}


VOID CMessengerWnd::SetSendMSGList(CHAR* pszMsg, INT nCount)
{
	char *pszNext;
	INT nCnt = 0;
	LPCLIENTDHLTITLE pstDhltitle;

	// 리스트를 새로 받기 때문에 Init해야 할 것들을 Init한다.
	mMessenger_xSendMSGList.ClearAll();

	if ( nCount <= 0 )
		return;

	char *pszItem = (pszMsg + _DEFBLOCKSIZE);

	do
	{
		if ( pszNext = strchr(pszItem, '/') )
		{
			pstDhltitle = new CLIENTDHLTITLE;

			*pszNext = '\0';

			fnDecode6BitBuf(pszItem, (char*)pstDhltitle, sizeof(CLIENTDHLTITLE));

			pszItem = pszNext + 1;

			nCnt++;

			mMessenger_xSendMSGList.Insert(pstDhltitle);
		}

	} while (nCnt < nCount && pszNext);

	mMessenger_nSendMaxLine = nCnt;
}

VOID CMessengerWnd::AddSendMsg(LPCLIENTDHLCONTAIN pstDhlMsg)
{
	mMessenger_xSendMsg.ClearAll();

	mMessenger_xReceivedContain.Insert(pstDhlMsg);

	ReadSendMsg(pstDhlMsg->nIndex);
}

BOOL CMessengerWnd::ReadReceivedMsg(INT nIndex)
{
	CListNode < CLIENTDHLCONTAIN > *pNode;
	LPCLIENTDHLCONTAIN pstContain = NULL;

	mMessenger_xReceivedMsg.ClearAll();

	for ( pNode = mMessenger_xReceivedContain.GetHead(); pNode; pNode = pNode->GetNext() )
	{
		pstContain = pNode->GetData();

		if ( nIndex == pstContain->nIndex )
		{
			if ( pstContain->szText[0] )
			{
				char *szTemp;
				char *szText;
				CHAR szBuf[501];
				INT	 nWidth = 355;
				DWORD dwFontColor = RGB(250, 250, 250), dwFontBackColor = RGB(0, 0, 0);

				sprintf(szBuf, "%s", pstContain->szText);
				szText = pstContain->szText;
				do 
				{
					INT  nCnt;
					CHAT* stChat;
					INT	 nLineCnt;
					CHAR pszDivied[_MAX_STRING_LEN*2];
					CHAR pszArg[11][MAX_PATH];

					if ( szTemp = strchr(szText, 0x0D) )
					{
						*szTemp++ = '\0';
					}

					ZeroMemory(pszDivied, _MAX_STRING_LEN*2);
					ZeroMemory(pszArg,	  MAX_PATH*11);

					g_xMainWnd.StringDivide(nWidth, nLineCnt, szText, pszDivied);

					sscanf(pszDivied, "%[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c", pszArg[0], pszArg[1], pszArg[2], pszArg[3], pszArg[4], pszArg[5], pszArg[6], pszArg[7], pszArg[8], pszArg[9], pszArg[10], pszArg[11]);

					if ( nLineCnt > 11 )
					{
						nLineCnt = 11;
					}

					// 문자열 삽입.
					for ( nCnt = 0; nCnt < nLineCnt; nCnt++ )
					{
						stChat = new CHAT;
						stChat->dwFontColor = dwFontColor;
						stChat->dwBackColor = dwFontBackColor;
						strcpy(stChat->pszChat, pszArg[nCnt]);
						
						mMessenger_xReceivedMsg.Insert(stChat);
					}
					szText = szTemp;
				}while(szTemp);
				sprintf(pstContain->szText, "%s", szBuf);
				pstContain->wReadCheck = FALSE;
			}

			if ( pstContain->stItemInfo.stStdItem.szName[0] != NULL )
			{
				mMessenger_bMoneyReceive = FALSE;
				mMessenger_bItemReceive = TRUE;
				mMessenger_xReceivedItem.m_stItemInfo = pstContain->stItemInfo;
			}
			else if ( pstContain->nMoney != 0 )
			{
				mMessenger_bItemReceive = FALSE;
				mMessenger_bMoneyReceive = TRUE;
				mMessenger_nMoneyGift = pstContain->nMoney;
			}
			else
			{
				mMessenger_bMoneyReceive = FALSE;
				mMessenger_bItemReceive = FALSE;
			}

			mMessenger_nReadStartLine = 0;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CMessengerWnd::ReadSendMsg(INT nIndex)
{
	CListNode < CLIENTDHLCONTAIN > *pNode;
	LPCLIENTDHLCONTAIN pstContain = NULL;

	mMessenger_xSendMsg.ClearAll();

	for ( pNode = mMessenger_xSendContain.GetHead(); pNode; pNode = pNode->GetNext() )
	{
		pstContain = pNode->GetData();

		if ( nIndex == pstContain->nIndex )
		{
			if ( pstContain->szText[0] )
			{
				char *szTemp;
				char *szText;
				CHAR szBuf[501];
				INT	 nWidth = 355;
				DWORD dwFontColor = RGB(250, 250, 250), dwFontBackColor = RGB(0, 0, 0);

				sprintf(szBuf, "%s", pstContain->szText);
				szText = pstContain->szText;
				do 
				{
					INT  nCnt;
					CHAT* stChat;
					INT	 nLineCnt;
					CHAR pszDivied[_MAX_STRING_LEN*2];
					CHAR pszArg[11][MAX_PATH];

					if ( szTemp = strchr(szText, 0x0D) )
					{
						*szTemp++ = '\0';
					}

					ZeroMemory(pszDivied, _MAX_STRING_LEN*2);
					ZeroMemory(pszArg,	  MAX_PATH*11);

					g_xMainWnd.StringDivide(nWidth, nLineCnt, szText, pszDivied);

					sscanf(pszDivied, "%[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c", pszArg[0], pszArg[1], pszArg[2], pszArg[3], pszArg[4], pszArg[5], pszArg[6], pszArg[7], pszArg[8], pszArg[9], pszArg[10], pszArg[11]);

					if ( nLineCnt > 11 )
					{
						nLineCnt = 11;
					}

					// 문자열 삽입.
					for ( nCnt = 0; nCnt < nLineCnt; nCnt++ )
					{
						stChat = new CHAT;
						stChat->dwFontColor = dwFontColor;
						stChat->dwBackColor = dwFontBackColor;
						strcpy(stChat->pszChat, pszArg[nCnt]);
						
						mMessenger_xSendMsg.Insert(stChat);
					}
					szText = szTemp;
				}while(szTemp);
				sprintf(pstContain->szText, "%s", szBuf);
				pstContain->wReadCheck = FALSE;
			}
			mMessenger_nReadStartLine = 0;
			return TRUE;
		}
	}
	return FALSE;
}

VOID CMessengerWnd::SendMSG()
{
	TCHAR   pszMessage[500];
	CHAR	szTemp[MAX_PATH];

	ZeroMemory(pszMessage, 500);

	GetWindowText(g_xChatEditBox.GetSafehWnd(), szTemp, MAX_PATH);

	if ( szTemp[0] != NULL )
		sprintf(mMessenger_szWriteID, szTemp);

	if ( mMessenger_hWriteMsg )
	{
		INT nLen	  = 0;
		TCHAR  pszEditMessage[500];

		ZeroMemory(pszEditMessage, 500);
		
		TCHAR* pszCheck = NULL;
		TCHAR* pszNextCheck = NULL;

		GetWindowText(mMessenger_hWriteMsg, pszEditMessage, 500);

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

	if ( pszMessage[0] && mMessenger_szWriteID[0] != NULL )
	{
		CLIENTNEWDHL stDhl;

		ZeroMemory(&stDhl, sizeof(CLIENTNEWDHL));
		sprintf(stDhl.szName, mMessenger_szWriteID);
		sprintf(stDhl.szMemo, pszMessage);

		TCHAR* pszNextCheck = NULL;
		if ( pszNextCheck = strchr(pszMessage, '\r') )
		{
			*pszNextCheck = '\0';

			if ( strlen(pszMessage) > 30 )
			{
				strncpy(stDhl.szTitle, pszMessage, 28);
				strcat(stDhl.szTitle, g_xMsg.GetMsg(4613));
			}
			else
			{
				sprintf(stDhl.szTitle, pszMessage);
			}
		}
		else
		{
			if ( strlen(&pszMessage[0]) > 30 )
			{
				strncpy(stDhl.szTitle, &pszMessage[0], 28);
				strcat(stDhl.szTitle, g_xMsg.GetMsg(4613));
			}
			else
			{
				sprintf(stDhl.szTitle, &pszMessage[0]);
			}
		}

		g_xClientSocket.SendNewDhl(stDhl);
		ZeroMemory(mMessenger_szWriteID, 25);
		SetWindowText(g_xChatEditBox.GetSafehWnd(), "");
		SetWindowText(mMessenger_hWriteMsg, "");
	}
}

VOID CMessengerWnd::SendMyItem()
{
	TCHAR  pszMessage[500];

	ZeroMemory(pszMessage, 500);

	if ( mMessenger_hGiftMsg )
	{
		INT nLen	  = 0;
		TCHAR  pszEditMessage[500];

		ZeroMemory(pszEditMessage, 500);
		
		TCHAR* pszCheck = NULL;
		TCHAR* pszNextCheck = NULL;

		GetWindowText(mMessenger_hGiftMsg, pszEditMessage, 500);

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

	if ( pszMessage[0] && mMessenger_szGiftID[0] != NULL && mMessenger_bGiftItemSet )
	{
		CLIENTNEWDHL stDhl;

		ZeroMemory(&stDhl, sizeof(CLIENTNEWDHL));
		sprintf(stDhl.szName, mMessenger_szGiftID);
		sprintf(stDhl.szMemo, pszMessage);

		TCHAR* pszNextCheck = NULL;
		if ( pszNextCheck = strchr(pszMessage, '\r') )
		{
			*pszNextCheck = '\0';

			if ( strlen(pszMessage) > 30 )
			{
				strncpy(stDhl.szTitle, pszMessage, 28);
				strcat(stDhl.szTitle, g_xMsg.GetMsg(4613));
			}
			else
			{
				sprintf(stDhl.szTitle, pszMessage);
			}
		}
		else
		{
			if ( strlen(&pszMessage[0]) > 30 )
			{
				strncpy(stDhl.szTitle, &pszMessage[0], 28);
				strcat(stDhl.szTitle, g_xMsg.GetMsg(4613));
			}
			else
			{
				sprintf(stDhl.szTitle, &pszMessage[0]);
			}
		}

		if ( mMessenger_bSetMoney == FALSE )
		{
			sprintf(stDhl.szSendItem, mMessenger_xItem.m_stItemInfo.stStdItem.szName);
			stDhl.nItemMakeIndex = mMessenger_xItem.m_stItemInfo.nMakeIndex;
		}
		else
		{
			stDhl.nMoney = mMessenger_nMoney;
		}

		g_xClientSocket.SendNewDhl(stDhl);

		ZeroMemory(mMessenger_szGiftID, 25);
		SetWindowText(g_xChatEditBox.GetSafehWnd(), "");
		SetWindowText(mMessenger_hGiftMsg, "");
		mMessenger_bGiftItemSet = FALSE;
		mMessenger_nMoney = 0;
		mMessenger_bSetMoney = FALSE;
	}
}

VOID CMessengerWnd::ChangeEditBoxLoc()
{
	mMessenger_bWirteID = FALSE;

	if ( mMessenger_nMode != _WRITE_BOX )
	{
		ShowWindow(mMessenger_hWriteMsg, SW_HIDE);
	}

	if ( mMessenger_nMode != _GIFT_BOX )
	{
		ShowWindow(mMessenger_hGiftMsg, SW_HIDE);
		MoveWindow(mMessenger_hGiftMsg, g_xMainWnd.m_rcWindow.left + mMessenger_rcGiftEditBox.left, 
	 			   g_xMainWnd.m_rcWindow.top + mMessenger_rcGiftEditBox.top, 
				   mMessenger_rcGiftEditBox.right - mMessenger_rcGiftEditBox.left, 
				   mMessenger_rcGiftEditBox.bottom - mMessenger_rcGiftEditBox.top, TRUE);
	}


	if ( mMessenger_nMode != _WRITE_BOX && mMessenger_nMode != _GIFT_BOX )
	{
		INT	 nMoveGapX, nMoveGapY;
		RECT rc, rcEdit;

		rc = g_xMainWnd.m_rcWindow;

		GetWindowRect(g_xChatEditBox.GetSafehWnd(), &rcEdit);

		nMoveGapX = g_xMainWnd.m_rcWindow.left;
		nMoveGapY = g_xMainWnd.m_rcWindow.top;

		MoveWindow(g_xChatEditBox.GetSafehWnd(), 
				   g_xGameProc.m_xInterface.m_xChatWnd.m_rcWnd.left + nMoveGapX + 20, g_xGameProc.m_xInterface.m_xChatWnd.m_rcWnd.top + nMoveGapY + 8, rcEdit.right-rcEdit.left, rcEdit.bottom-rcEdit.top, TRUE);

		

//		if ( g_xGameProc.m_xInterface.m_bIsLargeChat == FALSE )
//		{
//			MoveWindow(g_xChatEditBox.GetSafehWnd(), 
//					   g_xMainWnd.m_rcWindow.left+_NEW_INPUT_EDITWND_XPOS, g_xMainWnd.m_rcWindow.top+_NEW_INPUT_EDITWND_YPOS,
//					   _NEW_INPUT_EDITWND_WIDTH, _NEW_INPUT_EDITWND_HEIGHT, TRUE);
//		}
//		else
//		{
//			MoveWindow(g_xChatEditBox.GetSafehWnd(), 
//					   g_xMainWnd.m_rcWindow.left+_NEW_INPUT_EDITWND_XPOS, g_xMainWnd.m_rcWindow.top+_NEW_INPUT_LARGEEDITWND_YPOS,
//					   _NEW_INPUT_LARGEEDITWND_WIDTH, _NEW_INPUT_EDITWND_HEIGHT, TRUE);
//		}
//
		SetWindowText(g_xChatEditBox.GetSafehWnd(), "");

		SetFocus(g_xMainWnd.GetSafehWnd());
		g_xChatEditBox.SetEnterUse(TRUE);

		ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_HIDE);
	}
}


VOID CMessengerWnd::CloseMessengerWnd()
{
	SetWindowText(g_xChatEditBox.GetSafehWnd(), "");

	ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_HIDE);
	ShowWindow(mMessenger_hWriteMsg, SW_HIDE);
	SetWindowText(mMessenger_hWriteMsg, "");

	ShowWindow(mMessenger_hGiftMsg, SW_HIDE);
	SetWindowText(mMessenger_hGiftMsg, "");

	g_xGameProc.m_xInterface.DeleteWindowToList(_WND_ID_MESSENGER);
	SetGameWndActive(FALSE);

	SetFocus(g_xMainWnd.GetSafehWnd());
	g_xChatEditBox.SetEnterUse(TRUE);

	mMessenger_bWirteID = FALSE;
	mMessenger_bWriteMsg = FALSE;

	mMessenger_bGiftID = FALSE;
	mMessenger_bGiftMsg = FALSE;
	mMessenger_bGiftItemSet = FALSE;

	mMessenger_bSetMoney = FALSE;
	mMessenger_nMoney = 0;
}
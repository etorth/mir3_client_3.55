/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"


CChatWnd::CChatWnd()
{
	Init();
}

CChatWnd::~CChatWnd()
{
	Destroy();
}

VOID CChatWnd::Init()
{
	CGameWnd::Init();

	mChat_nNumMiddleImg = 10;
	mChat_bLargeChat	= FALSE;

	mChat_nMode			= _CHAT_MODE_NORMAL;
	mChat_nFstLine		= 0;
	mChat_nMaxShowLine	= 0;

	SetRect(&mChat_rcChat, 0, 0, 0, 0);

	mChat_xChatlist.ClearAll();
	mChat_xScrlChat.Init();

	for ( INT nCnt = 0; nCnt < _MAX_CHATLINE; nCnt++ )
	{
		SetRect(&mChat_rcChatLine[nCnt], 0, 0, 0, 0);
	}

	ZeroMemory(m_pszLastCapture, MAX_PATH);


	SAFE_RELEASE(mChat_pddsSurface);
}

VOID CChatWnd::Destroy()
{
	CGameWnd::Destroy();
}

VOID CChatWnd::CreateChatWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend)
{
	CreateGameWnd(nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight, bBlend);

	mChat_BtnExpand.CreateGameBtn(pxWndImage, 151, 151, nStartX+352, nStartY+7, g_xMsg.GetMsg(4870), _BTN_TYPE_NOFOCUS, -1, TRUE);
	mChat_BtnClose.CreateGameBtn(pxWndImage, 169, 169, nStartX+352, nStartY+7, g_xMsg.GetMsg(4871), _BTN_TYPE_FOCUS, -1, TRUE);
	mChat_BtnMode.CreateGameBtn(pxWndImage, 155, 166, nStartX+352, nStartY+7, g_xMsg.GetMsg(4872), _BTN_TYPE_FOCUS, 153, TRUE);	
	mChat_BtnRotate.CreateGameBtn(pxWndImage, 163, 165, nStartX+352, nStartY+7, g_xMsg.GetMsg(4873), _BTN_TYPE_FOCUS, 163, TRUE);

	mChat_xScrlChat.CreateScrlBar(pxWndImage, 154, _MAX_CHATLINE, 12, 105, 12);

	for ( INT nCnt = 0; nCnt < _MAX_CHATLINE; nCnt++ )
	{
		SetRect(&mChat_rcChatLine[nCnt], 118, (294+nCnt*15), 440, (309+nCnt*15));
	}

	SetRect(&mChat_rcChat, m_rcWnd.left + 19, m_rcWnd.top + 25, m_rcWnd.right - 22, m_rcWnd.bottom - 24);
}	
		
VOID CChatWnd::ShowChatWnd()
{
	if ( mChat_bLargeChat )
	{
		mChat_nMaxShowLine = mChat_nNumMiddleImg + 3;

		////////////////////////////////////////////////////////////
		if ( mChat_pddsSurface == NULL )
		{
			return;
		}

		D3DMATERIAL7 mtrl;

		INT nStartY = (mChat_nSurfaceH - ( m_rcWnd.bottom - m_rcWnd.top ) )/ 2;

		D3DVECTOR	 vecTrans((FLOAT)mChat_nSX + m_rcWnd.left, (FLOAT)m_rcWnd.top - nStartY, (FLOAT)0);
		D3DVECTOR	 vecScale((FLOAT)mChat_nSurfaceW, (FLOAT)mChat_nSurfaceH, 1);

		D3DUtil_InitMaterial(mtrl, (FLOAT)m_bBright/255.0f, (FLOAT)m_bBright/255.0f, (FLOAT)m_bBright/255.0f);
		mtrl.diffuse.a = (FLOAT)100/255.0f;

		g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, mChat_pddsSurface);

		mChat_BtnRotate.ChangeRect(m_rcWnd.left+344, m_rcWnd.bottom-38);
		mChat_BtnMode.ChangeRect(m_rcWnd.left+9, m_rcWnd.top+4);

		mChat_BtnRotate.ShowGameBtn();

		if ( mChat_nFstLine == mChat_xChatlist.GetCount() )
		{
			mChat_nFstLine -= 1;
		}

		mChat_xScrlChat.ShowScrlBar(m_rcWnd.left + 342, m_rcWnd.top + 22, mChat_nFstLine, mChat_xChatlist.GetCount());

		SetRect(&mChat_rcChat, m_rcWnd.left + 19, m_rcWnd.top + 25, m_rcWnd.right - 22, m_rcWnd.bottom - 24);

		ShowChatList();

		mChat_BtnClose.ChangeRect(m_rcWnd.left+49, m_rcWnd.top+4);	

		mChat_BtnMode.ShowGameBtn();
		mChat_BtnClose.ShowGameBtn();
	}
	else
	{
		ShowGameWnd();
	}

	mChat_BtnExpand.ChangeRect(m_rcWnd.left+344, m_rcWnd.bottom-22);

	mChat_BtnExpand.ShowGameBtn();

	if ( mChat_bLargeChat )
	{

	}
}


BOOL CChatWnd::OnLButtonUp(POINT ptMouse)
{
	if ( mChat_BtnExpand.OnLButtonUp(ptMouse) )
	{
		ChangeChatSize();
		return FALSE;
	}

	if ( mChat_bLargeChat )
	{
		if ( mChat_BtnMode.OnLButtonUp(ptMouse) )
		{
			mChat_nMode++;
			if ( mChat_nMode > _CHAT_MODE_GUILD )
				mChat_nMode = _CHAT_MODE_NORMAL;

			DWORD dwFont = GetChatColor(_CHAT_COLOR3);
			DWORD dwBack = GetChatColor(_CHAT_COLOR8);

			switch ( mChat_nMode )
			{
			case _CHAT_MODE_NORMAL:
				MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2626));
				mChat_BtnMode.ResetGameBtn(155, 166, 153);
				break;
			case _CHAT_MODE_GROUP:
				MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2627));
				mChat_BtnMode.ResetGameBtn(157, 167, 156);
				break;
			case _CHAT_MODE_GUILD:
				MsgAdd(dwFont, dwBack, g_xMsg.GetMsg(2628));
				mChat_BtnMode.ResetGameBtn(159, 168, 158);
				break;
			}
			return FALSE;
		}

		if ( mChat_BtnClose.OnLButtonUp(ptMouse) )
		{
			ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_HIDE);
			return TRUE;
		}

		if ( mChat_BtnRotate.OnLButtonUp(ptMouse) )
		{
			mChat_nNumMiddleImg -= 2;
			if ( mChat_nNumMiddleImg < 4 )
				mChat_nNumMiddleImg = 12;

			SetChatWndTextr(g_xMainWnd.Get3DDevice());			
			return FALSE;
		}
	}


	if ( mChat_xScrlChat.OnLButtonUp(ptMouse) )
	{
		return FALSE;
	}


	return FALSE;
}

BOOL CChatWnd::OnLButtonDown(POINT ptMouse)
{
	if ( SetCaputeString(ptMouse) )
		return TRUE;

	if ( mChat_BtnExpand.OnLButtonDown(ptMouse) )
		return TRUE;

	if ( mChat_bLargeChat )
	{
		if ( mChat_BtnMode.OnLButtonDown(ptMouse) )
			return TRUE;
		if ( mChat_BtnClose.OnLButtonDown(ptMouse) )
			return TRUE;

		if ( mChat_BtnRotate.OnLButtonDown(ptMouse) )
			return TRUE;
	}

	if ( mChat_xScrlChat.OnLButtonDown(ptMouse) )
	{
		FLOAT	fScrlRate;

		fScrlRate = mChat_xScrlChat.GetScrlRate();

		mChat_nFstLine = (INT)((mChat_xChatlist.GetCount()-1)*fScrlRate);

		return TRUE;
	}


	return FALSE;
}

BOOL CChatWnd::OnMouseMove(POINT ptMouse)
{
	mChat_BtnExpand.OnMouseMove(ptMouse);

	if ( mChat_bLargeChat )
	{
		mChat_BtnMode.OnMouseMove(ptMouse);
		mChat_BtnClose.OnMouseMove(ptMouse);
		mChat_BtnRotate.OnMouseMove(ptMouse);
	}

	if ( mChat_xScrlChat.OnMouseMove(ptMouse) )	
	{
		FLOAT	fScrlRate;

		fScrlRate = mChat_xScrlChat.GetScrlRate();
		mChat_nFstLine  = (INT)((mChat_xChatlist.GetCount()-1)*fScrlRate);
		return TRUE;
	}

	return FALSE;
}

VOID CChatWnd::MoveEditBox()
{
	INT	 nMoveGapX, nMoveGapY;
	RECT rc, rcEdit;

	rc = g_xMainWnd.m_rcWindow;

	GetWindowRect(g_xChatEditBox.GetSafehWnd(), &rcEdit);

	nMoveGapX = g_xMainWnd.m_rcWindow.left;
	nMoveGapY = g_xMainWnd.m_rcWindow.top;

	MoveWindow(g_xChatEditBox.GetSafehWnd(), 
			   g_xGameProc.m_xInterface.m_xChatWnd.m_rcWnd.left + nMoveGapX + 20,
			   g_xGameProc.m_xInterface.m_xChatWnd.m_rcWnd.bottom + nMoveGapY - 20, 
			   rcEdit.right-rcEdit.left, rcEdit.bottom-rcEdit.top, TRUE);
}

VOID CChatWnd::OnScrollDown()
{
	if ( mChat_nFstLine > 0 )	
	{
		mChat_nFstLine--;
	}
}

VOID CChatWnd::OnScrollUp()
{

	if ( mChat_nFstLine < (mChat_xChatlist.GetCount()-1) )
	{
		mChat_nFstLine++;
	}

}

VOID CChatWnd::SetChatWndTextr(LPDIRECT3DDEVICE7 pd3dDevice)
{
    D3DDEVICEDESC7 ddDesc;
    DDSURFACEDESC2 ddsd;

	// Surface Clear.
	SAFE_RELEASE(mChat_pddsSurface);
	mChat_nSurfaceW = mChat_nSurfaceH = mChat_nSX = mChat_nSY = 0;

	// Surface Make.
    if ( NULL == pd3dDevice )
	{
        return;
	}

    if ( FAILED(pd3dDevice->GetCaps(&ddDesc)) )
	{
        return;
	}

	// Window Image의 크기.
	const INT nRW = 360;
	const INT nTH = 56;
	const INT nMH = 15;
	const INT nBH = 40;

	INT nRH = nTH + (nMH*mChat_nNumMiddleImg) + nBH;
	INT nH  = 1;
	INT nW  = 1;

    for ( nH = 1; nRH > nH; nH <<= 1 );
    for ( nW = 1; nRW > nW; nW <<= 1 );

	mChat_nSurfaceW = nW;
	mChat_nSurfaceH = nH;

    D3DUtil_InitSurfaceDesc(ddsd);
    ddsd.dwFlags         = DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps  = DDSCAPS_TEXTURE;
	ddsd.dwTextureStage  = 0;
    ddsd.dwWidth         = mChat_nSurfaceW;
    ddsd.dwHeight        = mChat_nSurfaceH;

    if ( ddDesc.deviceGUID == IID_IDirect3DHALDevice || ddDesc.deviceGUID == IID_IDirect3DTnLHalDevice )
	{
        ddsd.ddsCaps.dwCaps2 = DDSCAPS2_TEXTUREMANAGE;
	}
    else
	{
        ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
	}

	// 직사각형의 텍스춰를 지원하지 않는다면...
    if ( ddDesc.dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_SQUAREONLY )
    {
        if ( ddsd.dwWidth > ddsd.dwHeight ) ddsd.dwHeight = ddsd.dwWidth;
        else                                ddsd.dwWidth  = ddsd.dwHeight;
    }

    HRESULT hr = g_xMainWnd.GetDirectDraw()->CreateSurface(&ddsd, &mChat_pddsSurface, NULL);

    if( FAILED(hr) )
	{
		mChat_nSurfaceW = mChat_nSurfaceH = 0;
        return;
	}

	// 컬러키를 세팅한다.
	DDSetColorKey(mChat_pddsSurface, RGB(0, 0, 0));

	// 까만색으로 채운다.
	DDBLTFX ddbltfx;
	ZeroMemory(&ddbltfx, sizeof(ddbltfx));
	ddbltfx.dwSize      = sizeof(ddbltfx);
//	ddbltfx.dwFillColor = RGB(10, 10, 10);
	ddbltfx.dwFillColor = RGB(0, 0, 0);
	mChat_pddsSurface->Blt(NULL, NULL, NULL, DDBLT_COLORFILL, &ddbltfx);

	INT	nTopImgIdx, nMiddleImgIdx, nBottomImgIdx;

	nTopImgIdx = 160;	
	nMiddleImgIdx = 162;
	nBottomImgIdx = 164;

	RECT rc = {0, 0, 0, 0};
	INT  nSX = mChat_nSurfaceW/2 - nRW/2;
	INT  nSY = mChat_nSurfaceH/2 - nRH/2;
	INT	 nCountShow = 0;
	INT	 nSumHeight = 0;

	// 인터페이스를 그린다.
	// 상단 이미지.
	if ( m_pxWndImage->NewSetIndex(nTopImgIdx) )
	{
		SetRect(&rc, 0, 0, m_pxWndImage->m_lpstNewCurrWilImageInfo->shWidth, nSY+m_pxWndImage->m_lpstNewCurrWilImageInfo->shHeight);
		g_xMainWnd.DrawWithImageForComp(nSX, nSY, &rc, (WORD*)m_pxWndImage->m_pbCurrImage, 0XFFFF, 0XFFFF, mChat_pddsSurface);
		nSY += nTH;
		nSumHeight += nTH;
	}

	// 중단 이미지.
	do
	{
		if ( m_pxWndImage->NewSetIndex(nMiddleImgIdx) )
		{
			SetRect(&rc, 0, 0, m_pxWndImage->m_lpstNewCurrWilImageInfo->shWidth, nSY+m_pxWndImage->m_lpstNewCurrWilImageInfo->shHeight);
			g_xMainWnd.DrawWithImageForComp(nSX, nSY, &rc, (WORD*)m_pxWndImage->m_pbCurrImage, 0XFFFF, 0XFFFF, mChat_pddsSurface);
			nSY += nMH;
			nSumHeight += nMH;
		}
		nCountShow++;
	} while ( nCountShow < mChat_nNumMiddleImg );

	// 하단 이미지.
	if ( m_pxWndImage->NewSetIndex(nBottomImgIdx) )
	{
		SetRect(&rc, 0, 0, m_pxWndImage->m_lpstNewCurrWilImageInfo->shWidth, nSY+m_pxWndImage->m_lpstNewCurrWilImageInfo->shHeight);
		g_xMainWnd.DrawWithImageForComp(nSX, nSY, &rc, (WORD*)m_pxWndImage->m_pbCurrImage, 0XFFFF, 0XFFFF, mChat_pddsSurface);
		nSY += nBH;
		nSumHeight += nBH;
	}

	mChat_nSX = -nSX;
	mChat_nSY = -nSY;

	mChat_bLargeChat = TRUE;

	INT nChage = nSumHeight - (m_rcWnd.bottom - m_rcWnd.top);
	INT nTempHeight = m_rcWnd.top - nChage;
	SetRect(&m_rcWnd, m_rcWnd.left, nTempHeight, 
		m_rcWnd.right, nTempHeight + nSumHeight);

	mChat_BtnExpand.ResetGameBtn(152, 152);

	mChat_xScrlChat.m_wScrlHeight = ( nSumHeight - nBH ) - 38;
}



VOID CChatWnd::MoveChatWnd(POINT ptMouse)
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


VOID CChatWnd::ChangeToSmallChat()
{
	mChat_BtnExpand.ResetGameBtn(151, 151);
	SetRect(&m_rcWnd, m_rcWnd.left, m_rcWnd.bottom - 26, m_rcWnd.right, m_rcWnd.bottom); 
}


VOID CChatWnd::ActiveEditBox()
{
	if ( !GetGameWndActive() )
		g_xGameProc.m_xInterface.WindowActivate(_WND_ID_CHAT);

	INT	 nMoveGapX, nMoveGapY;
	RECT rc, rcEdit = {319, 747, 640, 762};

	rc = g_xMainWnd.m_rcWindow;

	nMoveGapX = g_xMainWnd.m_rcWindow.left;
	nMoveGapY = g_xMainWnd.m_rcWindow.top;

	if ( mChat_bLargeChat )
	{
		MoveWindow(g_xChatEditBox.GetSafehWnd(), 
				   g_xGameProc.m_xInterface.m_xChatWnd.m_rcWnd.left + nMoveGapX + 20, g_xGameProc.m_xInterface.m_xChatWnd.m_rcWnd.bottom + nMoveGapY - 20, rcEdit.right-rcEdit.left, rcEdit.bottom-rcEdit.top, TRUE);
	}
	else
	{
		MoveWindow(g_xChatEditBox.GetSafehWnd(), 
				   g_xGameProc.m_xInterface.m_xChatWnd.m_rcWnd.left + nMoveGapX + 20, g_xGameProc.m_xInterface.m_xChatWnd.m_rcWnd.top + nMoveGapY + 8, rcEdit.right-rcEdit.left, rcEdit.bottom-rcEdit.top, TRUE);
	}
	g_xChatEditBox.SetHanguelMode();
	SetFocus(g_xChatEditBox.GetSafehWnd());
	ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);

	if ( mChat_nMode == _CHAT_MODE_GUILD )
	{
		SetWindowText(g_xChatEditBox.GetSafehWnd(), "!~");
		INT nLen = strlen("!~");
		SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETSEL, nLen , nLen);
	}
	else if ( mChat_nMode == _CHAT_MODE_GROUP )
	{
		SetWindowText(g_xChatEditBox.GetSafehWnd(), "!!");
		INT nLen = strlen("!!");
		SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETSEL, nLen , nLen);
	}
}


VOID CChatWnd::MsgAdd(DWORD dwFontColor, DWORD dwFontBackColor, CHAR* pszMsg)
{
	if ( pszMsg )
	{
		if ( pszMsg[0] != NULL )
		{
			INT  nCnt;
			CHAT* stChat;
			INT	 nLineCnt;
			CHAR pszDivided[_MAX_STRING_LEN*2];
			CHAR pszArg[5][MAX_PATH];
			
			ZeroMemory(pszDivided, _MAX_STRING_LEN*2);
			ZeroMemory(pszArg,	  MAX_PATH*5);
			
			g_xMainWnd.StringDivide(mChat_rcChat.right-mChat_rcChat.left, nLineCnt, pszMsg, pszDivided);
			sscanf(pszDivided, "%[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c", pszArg[0], pszArg[1], pszArg[2], pszArg[3], pszArg[4]);

			if ( nLineCnt > 5 )		
			{
				nLineCnt = 5;
			}

			// 문자열 삽입.
			for ( nCnt = 0; nCnt < nLineCnt; nCnt++ )
			{
				if ( mChat_xChatlist.GetCount() - mChat_nFstLine == mChat_nMaxShowLine )
				{
					mChat_nFstLine++;
				}

				stChat = new CHAT;
				stChat->dwFontColor = dwFontColor;
				stChat->dwBackColor = dwFontBackColor;
				strcpy(stChat->pszChat, pszArg[nCnt]);
				
				mChat_xChatlist.Insert(stChat);
			}

			CListNode < CHAT >		*pNode;
			CHAT*					pstChat = NULL;

			while ( mChat_xChatlist.GetCount() >= _MAX_SAVECHATLINE )
			{
				pNode = mChat_xChatlist.GetHead();
				pstChat = mChat_xChatlist.RemoveNode(pNode);

				if ( pstChat )
				{
					delete((CHAT*) pstChat);
					pstChat = NULL;
				}

				if ( mChat_nFstLine > 0 )
				{
					mChat_nFstLine--;
				}
			}
		}
	}
}


VOID CChatWnd::ShowChatList()
{
	if ( !mChat_xChatlist.IsEmpty() )
	{
		INT		nCnt, nShowLine;
		LPCHAT	pstChat;

		CListNode < CHAT >		*pNode;

		pNode = mChat_xChatlist.GetHead();
		for ( INT nCount=0; nCount < mChat_nFstLine; nCount++)
			pNode = pNode->GetNext();

		nShowLine = mChat_xChatlist.GetCount() - mChat_nFstLine;
		
		for ( nCnt = 0; nCnt < nShowLine && nCnt < mChat_nNumMiddleImg + 3; nCnt++ )
		{
			pstChat = *pNode;

			if ( pstChat )
			{
				g_xMainWnd.PutsHan(g_xMainWnd.GetBackBuffer(),
								   mChat_rcChat.left, mChat_rcChat.top+nCnt*15,
								   pstChat->dwFontColor, pstChat->dwBackColor, pstChat->pszChat);
			}

			pNode = pNode->GetNext();
		}
	}
}


VOID CChatWnd::SetCaputeString(CHAR* pszChat)
{
	CHAR  pszString[MAX_PATH];
	CHAR* pszCapture;
	CHAR* pszCut;

	strcpy(pszString, pszChat);

	pszCapture = pszString;

	if ( pszCapture[0] == '/' )
	{
		pszCapture++;
		
		while ( pszCut = strchr(pszCapture, ' ') )
		{
			pszCut++;
			if ( *pszCut )
			{
				*pszCut = '\0';
				break;
			}
			else
			{
				sprintf(m_pszLastCapture, "/%s", pszCapture);
				return;
			}
			pszCapture = pszCut;
		}

		if ( *pszCapture )
		{
			if ( pszCut = strchr(pszCapture, ' ') )
			{
				*pszCut = '\0';
			}

			sprintf(m_pszLastCapture, "/%s ", pszCapture);
		}
	}
}


VOID CChatWnd::SetHearList()
{
/*	CListNode < CHAT > *pNode;

	INT		nCnt;
	LPCHAT	pstChat = NULL;

	for ( pNode = m_xHearList.GetHead(), nCnt = 0; pNode; pNode = pNode->GetNext(), nCnt++ )
	{
		pstChat = pNode->GetData();

		if ( nCnt == m_nSelHearNum )
		{
			if ( pstChat )
			{
				sprintf(m_pszLastCapture, "/%s", pstChat->pszChat);

				SetFocus(g_xChatEditBox.GetSafehWnd());
				ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);
				SetWindowText(g_xChatEditBox.GetSafehWnd(), m_pszLastCapture);

				INT nLen = strlen(m_pszLastCapture);
				SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETSEL, nLen , nLen);
				g_xChatEditBox.SetHanguelMode();

				break;
			}
		}
	}
*/
}


VOID CChatWnd::ChatListClear()
{
	CListNode < CHAT >	*pNode;
	CListNode < CHAT >	*pNodeTemp;
	CHAT*				pstChat = NULL;

	for ( pNode = mChat_xChatlist.GetHead(); pNode; )
	{
		pNodeTemp = pNode->GetNext();

		pstChat = mChat_xChatlist.RemoveNode(pNode);

		if ( pstChat )
		{
			delete((CHAT*) pstChat);
			pstChat = NULL;
		}
		pNode = pNodeTemp;
	}
}


VOID CChatWnd::ChangeChatSize()
{
	if ( !mChat_bLargeChat )
	{
		SetChatWndTextr(g_xMainWnd.Get3DDevice());
		mChat_bLargeChat = TRUE;
	}
	else
	{
		ChangeToSmallChat();
		mChat_bLargeChat = FALSE;
	}
}


BOOL CChatWnd::SetCaputeString(POINT ptMouse)
{
	INT		nCnt, nChatMaxLine;
	BOOL	bInRect = FALSE;
	BOOL	bEnpty  = FALSE;

	nChatMaxLine = _MAX_CHATLINE;

	for ( nCnt = 0; nCnt < nChatMaxLine; nCnt++ )
	{
		bInRect = FALSE;
		if ( PtInRect(&mChat_rcChatLine[nCnt], ptMouse) )
			bInRect = TRUE;

		INT nIdx = nChatMaxLine - ( mChat_nNumMiddleImg + 3 );
		INT nNum = nCnt - nIdx;

		if ( bInRect == TRUE && nNum >= 0)
		{
			if ( mChat_xChatlist.IsEmpty() )
				bEnpty = TRUE;
			
			if ( !bEnpty )
			{
				CListNode < CHAT >		*pNode;
				LPCHAT					pstChat = NULL;

				pNode = mChat_xChatlist.GetHead();
				for ( INT nCount=0; nCount < mChat_nFstLine+nNum && pNode != NULL ; nCount++)
					pNode = pNode->GetNext();

				if ( pNode != NULL )
					pstChat = *pNode;

				if ( pstChat )
				{
					CHAR  pszString[MAX_PATH];
					CHAR* pszCapture;
					CHAR* pszCut;

					strcpy(pszString, pstChat->pszChat);

					pszCapture = pszString;

					if ( pszString[0] == '/' )
					{
						pszCapture = &pszString[1];
					}
					else if ( *pszString == '(' && *(pszString+1) == '!' && *(pszString+2) == ')' )
					{
						pszCapture = &pszString[3];
					}

					pszCut = strchr(pszCapture, ' ');

					if ( !pszCut )
					{
						pszCut = strchr(pszCapture, ':');
					}

					if ( pszCut )
					{
						*pszCut = NULL;

						pszCut = strchr(pszCapture, ':');
						if ( pszCut ) 
						{
							*pszCut = NULL;
						}

						pszCut = strchr(pszCapture, '=');
						if ( pszCut && *(pszCut+1) == '>' )
						{
							*pszCut = NULL;
						}

						sprintf(m_pszLastCapture, "/%s ", pszCapture);

						SetFocus(g_xChatEditBox.GetSafehWnd());
						ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);
						SetWindowText(g_xChatEditBox.GetSafehWnd(), m_pszLastCapture);

						INT nLen = strlen(m_pszLastCapture);
						SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETSEL, nLen , nLen);
						g_xChatEditBox.SetHanguelMode();

						return TRUE;
					}
				}
			}
		}
	}

	return FALSE;

}

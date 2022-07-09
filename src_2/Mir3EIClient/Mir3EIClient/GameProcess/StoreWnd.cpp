/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/

#include "StdAfx.h"

/////////////////////////////////////////////////////
#define MAX_KINDS_LINE			4
#define MAX_ITEMLIST_LINE		10
#define ITEMLIST_LINENUM		4				
#define LINE_GAP				5
/////////////////////////////////////////////////////

//KINDS
#define POS_KINDS_X				20
#define POS_KINDS_Y				16

#define POS_ITEMIMAGE_X			20
#define	POS_ITEMIMAGE_Y			16
#define POS_ITEMIMAGE_HEIGHT	42

#define LEFT_KIND_RECT			20
#define RIGHT_KIND_RECT			256
#define TOP_KIND_RECT			16
#define BOTTOM_KIND_RECT		182

//ITEMLIST
#define POS_ITEMLIST_LINE_X		314
#define POS_ITEMLIST_LINE_Y		42

#define ITEMCELL_WIDTH			38
#define ITEMCELL_HEIGHT			38

#define LEFT_ITEM_RECT			314
#define RIGHT_ITEM_RECT			465
#define TOP_ITEM_RECT			42
#define BOTTOM_ITEM_RECT		154

#define POS_X				84			// ex (전:POS_X,POS_Y)(GOLD:POS__X,POS_Y)
#define POS_Y				246			// ex (무게:POS_X,POS__Y)(가방무게:POS__X,POS__Y)
#define POS__Y				270
#define POS__X				246

#define MAX_MSG_LENGTH		MAX_PATH*12  // (10Kb)


CStoreWnd::CStoreWnd()
{
	POINT	Temp;

	m_nIsReadyToDisplay = 0;
	m_nCurrentItemTop = 0;
	m_nCurrentKindTop = 0;
	m_nMaxItemLine = 0;
	m_nMaxKindLine = 0;

	Temp.x = POS_KINDS_X;
	Temp.y = POS_KINDS_Y;


	m_xKindBtn.InitTxtBtn(MAX_KINDS_LINE,Temp,LINE_GAP);

	Temp.x = POS_ITEMLIST_LINE_X;
	Temp.y = POS_ITEMLIST_LINE_Y + 17;


	m_xItemLstBtn.InitTxtBtn(MAX_ITEMLIST_LINE,Temp,LINE_GAP);
	m_bSelectedKind=FALSE;
	m_bSelectedItem=FALSE;

	m_xKindRect.left = LEFT_KIND_RECT;
	m_xKindRect.top	= TOP_KIND_RECT;
	m_xKindRect.right = RIGHT_KIND_RECT;
	m_xKindRect.bottom = BOTTOM_KIND_RECT;

	m_xItemRect.left = LEFT_ITEM_RECT;
	m_xItemRect.top	= TOP_ITEM_RECT;
	m_xItemRect.right = RIGHT_ITEM_RECT;
	m_xItemRect.bottom = BOTTOM_ITEM_RECT;


}

CStoreWnd::~CStoreWnd()
{
}

VOID CStoreWnd::CreateStoreWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY,INT nWidth, INT nHeight, BOOL bCanMove)
{
	CreateGameWnd(nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight, -110, -18);

	//initial buttons
	m_xStoreBtn[IDC_BTN_SELECT	].CreateGameBtn( pxWndImage, 1263, 1264, 103, 183);
	m_xStoreBtn[IDC_BTN_CLOSE1	].CreateGameBtn( pxWndImage, 1221, 1222, 256, 184);
	m_xStoreBtn[IDC_BTN_BUY		].CreateGameBtn( pxWndImage, 1265, 1266, 355, 161);
	m_xStoreBtn[IDC_BTN_CLOSE2	].CreateGameBtn( pxWndImage, 1221, 1222, 448, 160);
	m_xStoreBtn[IDC_BTN_PREPAGE	].CreateGameBtn( pxWndImage, 1268, 1269, 312, 161);
	m_xStoreBtn[IDC_BTN_NEXTPAGE].CreateGameBtn( pxWndImage, 1270, 1271, 404, 161);

}	


VOID CStoreWnd::ShowStoreWnd()
{
	RECT tRect;
	CMTxtBtn* xtBtn;
	ShowGameWnd();
	OnUpdateQueue();
	if(m_nIsReadyToDisplay>0)
	{
		tRect = GetGameWndRect();
		if(m_nIsReadyToDisplay & 1)
		{	
			// 鞫刻膠틔蘆잚
			INT x, y;
			for(int i = 0 ; i <MAX_KINDS_LINE; i++)
			{
				RECT rcKinds;
				RECT rcItemImg;

				xtBtn = m_xKindBtn.GetButton( m_nCurrentKindTop + i);
				if( xtBtn == NULL )
					break;

				//draw item image
				x = tRect.left + POS_ITEMIMAGE_X;
				y = tRect.top + POS_ITEMIMAGE_Y + POS_ITEMIMAGE_HEIGHT * i;
				SetRect( &rcItemImg, x, y, x + 36, y + 36 );
				g_xMainWnd.DrawWithGDI(rcItemImg, NULL, RGB(255, 0, 0), 1);
				
				g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_INVENTORY].NewSetIndex(xtBtn->nImgID);
				g_xMainWnd.DrawWithImageForCompClipRgn(	x+3, y,
					g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_INVENTORY].m_lpstNewCurrWilImageInfo->shWidth,g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_INVENTORY].m_lpstNewCurrWilImageInfo->shHeight,
					(WORD*)g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_INVENTORY].m_pbCurrImage,800,600);
	
				//draw text
				x += 44;
				SetRect( &rcKinds, x, y, x + 188, y + 36);
				g_xMainWnd.PutsHan(NULL,rcKinds.left,rcKinds.top + LINE_GAP,(!xtBtn->bIsClicked?xtBtn->nColor:xtBtn->cColor),RGB(0,0,0),xtBtn->Txt);
				g_xMainWnd.DrawWithGDI(rcKinds, NULL, RGB(255, 0, 0), 1);

				m_xKindBtn.m_pTxtBtn.MoveNextNode();
			}

		}
		if( m_nIsReadyToDisplay & 2 )
		{	
			INT x, y;
			for(int i = 0 ; i <m_nMaxItemLine; i++)
			{
				RECT rcItem;

				xtBtn = m_xItemLstBtn.GetButton( i);
				if( xtBtn == NULL )
					break;

				//draw item image
				x = tRect.left + POS_ITEMLIST_LINE_X + ITEMCELL_WIDTH * (i % ITEMLIST_LINENUM) ;
				y = tRect.top + POS_ITEMLIST_LINE_Y + ITEMCELL_HEIGHT * (i / ITEMLIST_LINENUM);
				SetRect( &rcItem, x, y, x + ITEMCELL_WIDTH, y + ITEMCELL_HEIGHT );
				g_xMainWnd.DrawWithGDI(rcItem, NULL, RGB(255, 0, 0), 1);

				g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_INVENTORY].NewSetIndex(xtBtn->nImgID);
				g_xMainWnd.DrawWithImageForCompClipRgn(	x+3, y+1,
					g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_INVENTORY].m_lpstNewCurrWilImageInfo->shWidth,g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_INVENTORY].m_lpstNewCurrWilImageInfo->shHeight,
					(WORD*)g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_INVENTORY].m_pbCurrImage,800,600);

				//draw text
				g_xMainWnd.PutsHan(NULL,rcItem.left,rcItem.top + LINE_GAP,(!xtBtn->bIsClicked?xtBtn->nColor:xtBtn->cColor),RGB(0,0,0),xtBtn->Txt);

				m_xKindBtn.m_pTxtBtn.MoveNextNode();
			}

		}

		if( m_bActive && m_nIsReadyToDisplay )
		{
			for( int i = 0; i < 6; i++ )
				m_xStoreBtn[ i ].ShowGameBtn();
		}

	}
}


BOOL CStoreWnd::OnLButtonUp(POINT ptMouse)
{
	RECT tRect;
	POINT tPos;
	CMTxtBtn* tBtn;
	tRect = GetGameWndRect();			// Get Window Rect
	tPos.x = tRect.left;
	tPos.y = tRect.top;

	if( m_xStoreBtn[IDC_BTN_CLOSE1	].OnLButtonUp(ptMouse) )//밑균
	{
		return TRUE;
	}
	if( m_xStoreBtn[IDC_BTN_CLOSE2	].OnLButtonUp(ptMouse) )//밑균Itemlist
	{
		ResetWndImg( _WNDIMGIDX_STORE, 290, 224, -110, -18 );
		m_nIsReadyToDisplay &= ~2;
		return FALSE;
	}

	if(PtInRect(&m_xKindRect, ptMouse))
	{	// 목록 List
		tBtn = m_xKindBtn.ClickCheck(tPos,ptMouse,m_nCurrentKindTop);
		if(tBtn!=NULL)
		{
			tBtn = m_xKindBtn.ClickCheck(tPos,ptMouse,m_nCurrentKindTop);
			if(tBtn->nColor==RGB(255,255,0))
			{
				//뫘뻣썹충
				ResetWndImg( _WNDIMGIDX_STORE + 1/*tBtn->nSubMenu*/, 486, 224, -11, -18 );
				SendDeTailGoodsList(0,tBtn->Param);
			}
			else
			{
				// 메규가 없냐?
				// 그럼 그냥 선텍. 사기 가능.
			}
		}
		else
		{
			m_nIsReadyToDisplay = 1;
			m_bSelectedKind= FALSE;
		}
	}
	if(PtInRect(&m_xItemRect, ptMouse))
	{	
		m_xItemLstBtn.ClickFree();

		INT x, y;
		RECT rcItem;
		m_bSelectedItem = FALSE;
		int i;
		for( i = 0; i < m_nMaxItemLine; i++ )
		{
			x = tRect.left + POS_ITEMLIST_LINE_X + ITEMCELL_WIDTH * (i % ITEMLIST_LINENUM) ;
			y = tRect.top + POS_ITEMLIST_LINE_Y + ITEMCELL_HEIGHT * (i / ITEMLIST_LINENUM);
			SetRect( &rcItem, x, y, x + ITEMCELL_WIDTH, y + ITEMCELL_HEIGHT );
			if( PtInRect(&rcItem, ptMouse) )
			{
				m_xItemLstBtn.SetClick( i );
				m_bSelectedItem = TRUE;
				break;
			}
		}
		if( m_bSelectedItem )
		{
			tBtn = m_xItemLstBtn.GetButton( i );
			SendButThisITme(tBtn);
		}
		
	}
	return FALSE;
}

VOID CStoreWnd::OnMouseMove(POINT ptMouse)
{
	RECT tRect = GetGameWndRect();			// Get Window Rect

	m_xKindRect.left	= tRect.left+LEFT_KIND_RECT;
	m_xKindRect.top		= tRect.top+TOP_KIND_RECT;
	m_xKindRect.right	= tRect.left+RIGHT_KIND_RECT;
	m_xKindRect.bottom	= tRect.top+BOTTOM_KIND_RECT;

	m_xItemRect.left	= tRect.left+LEFT_ITEM_RECT;
	m_xItemRect.top		= tRect.top+TOP_ITEM_RECT;
	m_xItemRect.right	= tRect.left+RIGHT_ITEM_RECT;
	m_xItemRect.bottom	= tRect.top+BOTTOM_ITEM_RECT;

	int x = tRect.left;
	int y = tRect.top;
	m_xStoreBtn[IDC_BTN_SELECT	].ChangeRect( x+103, y+183);
	m_xStoreBtn[IDC_BTN_CLOSE1	].ChangeRect( x+256, y+184);
	m_xStoreBtn[IDC_BTN_BUY		].ChangeRect( x+355, y+161);
	m_xStoreBtn[IDC_BTN_CLOSE2	].ChangeRect( x+448, y+160);
	m_xStoreBtn[IDC_BTN_PREPAGE	].ChangeRect( x+312, y+161);
	m_xStoreBtn[IDC_BTN_NEXTPAGE].ChangeRect( x+404, y+161);

}

BOOL CStoreWnd::OnLButtonDown(POINT ptMouse)
{
	RECT tRect;
	POINT tPos;
	tRect = GetGameWndRect();			// Get Window Rect
	tPos.x = tRect.left;
	tPos.y = tRect.top;


	if(PtInRect(&m_xKindRect, ptMouse))
	{
		m_xKindBtn.ClickFree();
		m_xKindBtn.ClickCheck(tPos,ptMouse,m_nCurrentKindTop);
	}
	if(PtInRect(&m_xItemRect, ptMouse))
	{
		m_xItemLstBtn.ClickFree();

		INT x, y;
		RECT rcItem;
		for( int i = 0; i < m_nMaxItemLine; i++ )
		{
			x = tRect.left + POS_ITEMLIST_LINE_X + ITEMCELL_WIDTH * (i % ITEMLIST_LINENUM) ;
			y = tRect.top + POS_ITEMLIST_LINE_Y + ITEMCELL_HEIGHT * (i / ITEMLIST_LINENUM);
			SetRect( &rcItem, x, y, x + ITEMCELL_WIDTH, y + ITEMCELL_HEIGHT );
			if( PtInRect(&rcItem, ptMouse) )
			{
				m_xItemLstBtn.SetClick( i );
				break;
			}
		}
	}
	return FALSE;
}

BOOL CStoreWnd::SetBuyKinds(CHAR* Msg,INT Count)   // Eatch Button Divider '\n
{
	CNPCTxtAnalysis	tTxtAnalysis;				// 단지 GetValidStr함수를 사용하기 위해서..
	CHAR*	pszStr = new CHAR [MAX_MSG_LENGTH];

	if(m_nIsReadyToDisplay & 1)
	{
		m_xKindBtn.ReleaseButtons();
		m_bSelectedKind = FALSE;
		// 저장된 키 날리기
		m_nIsReadyToDisplay= 0;	// Kinds List 설정이 풀렸음을 알림
	}

	ZeroMemory(pszStr,MAX_MSG_LENGTH);
	strcpy(pszStr,Msg);

	m_nMaxKindLine = Count;

	for(int i = 0 ; i < Count ; i ++)
	{
		CHAR* szTemp;
		CHAR szGName[64];
		CHAR szGSubMenu[16];
		CHAR szGPrice[16];
		CHAR szGStock[16];
		CHAR szGLook[16];
		CHAR szGFlag[16];
		CHAR szGNeedLevel[16];
		INT  nSubMenuCount;
		INT	 nLook; 

		szTemp = tTxtAnalysis.GetValidStr(pszStr,szGName,'/');
		strcpy(pszStr,szTemp);
		szTemp = tTxtAnalysis.GetValidStr(pszStr,szGSubMenu,'/');
		strcpy(pszStr,szTemp);
		nSubMenuCount = atoi(szGSubMenu);
		szTemp = tTxtAnalysis.GetValidStr(pszStr,szGPrice,'/');
		strcpy(pszStr,szTemp);
		szTemp = tTxtAnalysis.GetValidStr(pszStr,szGStock,'/');
		strcpy(pszStr,szTemp);
		szTemp = tTxtAnalysis.GetValidStr(pszStr,szGLook,'/');
		strcpy(pszStr,szTemp);
		nLook = atoi(szGLook);
		szTemp = tTxtAnalysis.GetValidStr(pszStr,szGFlag,'/');
		strcpy(pszStr,szTemp);
		szTemp = tTxtAnalysis.GetValidStr(pszStr,szGNeedLevel,'/');
		strcpy(pszStr,szTemp);

		szTemp = new CHAR[16];
		szTemp[15]=NULL;

		RECT	rcKinds;
		SetRect(&rcKinds, 0, 0, 232, 36 );//button rect

		CHAR szParam[35];
		strcpy(szParam,szGName);	// 임시 Parameter를 아이템이름과 같이 처리함.

		if(nSubMenuCount>0)
		{	
			sprintf(szTemp,"%-14s",szGName);
			m_xKindBtn.AddButton(szTemp,rcKinds,i,szParam,RGB(255,255,0),RGB(255,0,0),nLook, nSubMenuCount);	// Add Button to class
		}
		else
		{	
			sprintf(szTemp,"%-14s",szGName);
			m_xKindBtn.AddButton(szTemp,rcKinds,i,szParam,RGB(180,180,0),RGB(255,0,0),nLook);	// Add Button to class
		}

	}
	m_xKindBtn.ClickFreeAllBtn();

	m_nIsReadyToDisplay = 1;		// Kinds List가 설정되었음을 알림
	delete[] pszStr;
	return	TRUE;
}

BOOL CStoreWnd::SetBuyItemLst(CHAR* Msg,INT Count)
{
	CNPCTxtAnalysis	tTxtAnalysis;				// 단지 GetValidStr함수를 사용하기 위해서..
	CHAR*	szTemp = NULL;
	CHAR	szDetailitem[MAX_PATH];

	ZeroMemory(szDetailitem,MAX_PATH);

	m_xItemLstBtn.ReleaseButtons();
	m_xItems.ClearAllNodes();

	m_nCurrentItemTop = 0;
	m_nMaxItemLine = Count;

	for ( INT nLoop = 0; nLoop < Count; nLoop++ )
	{
		szTemp = tTxtAnalysis.GetValidStr(Msg,szDetailitem,'/');
		strcpy(Msg, szTemp);
				
		CLIENTITEMRCD* pxClItem;
		pxClItem =	new	CLIENTITEMRCD;

		fnDecode6BitBuf(szDetailitem, (char*)pxClItem, sizeof(CLIENTITEMRCD));
		
		//		szTemp	 =	new CHAR[50];
		CHAR szTemp1[50];	// 가격
		CHAR szTemp2[50];	// 기타
		
		ZeroMemory(szTemp1,50);
		ZeroMemory(szTemp2,50);
		
		m_xItems.AddNode(pxClItem);

		sprintf(szTemp1,"%d",pxClItem->nDuraMax);

		RECT	rcItem;
		INT x = (nLoop % ITEMLIST_LINENUM) * ITEMCELL_WIDTH;
		INT y = (nLoop / ITEMLIST_LINENUM) * ITEMCELL_HEIGHT;
		SetRect(&rcItem, x, y, x + ITEMCELL_WIDTH, y + ITEMCELL_HEIGHT);

		// Parameter ...
		CHAR szParam[35];
		ZeroMemory(szParam,35);
		sprintf(szParam, "%d", pxClItem->nMakeIndex);	// 임시 Parameter를 아이템이름과 같이 처리함.

		m_xItemLstBtn.AddButton(szTemp1,szTemp2,rcItem,nLoop,szParam,RGB(180,180,0),RGB(255,0,0), pxClItem->stStdItem.wLooks);	// Add Button to class

	}
	m_nIsReadyToDisplay=m_nIsReadyToDisplay|2;		// Item List 설정이 됬음을 알림
		//
	return TRUE;
}

VOID CStoreWnd::OnScrollDown()
{
	POINT tPos;

	tPos = g_xGameProc.m_ptMousePos;
	if(PtInRect(&m_xKindRect,tPos))
	{
		m_nCurrentKindTop=m_nCurrentKindTop > 0 ? m_nCurrentKindTop - 1: 0;
	}

	if(PtInRect(&m_xItemRect,tPos))
	{
		m_nCurrentItemTop=m_nCurrentItemTop>0 ? m_nCurrentItemTop - 1 : 0;
	}
}

VOID CStoreWnd::OnScrollUp()
{
	POINT tPos;

	tPos = g_xGameProc.m_ptMousePos;
	if(PtInRect(&m_xKindRect, tPos))
	{
		m_nCurrentKindTop=m_nCurrentKindTop < m_nMaxKindLine-1 ? m_nCurrentKindTop + 1: m_nMaxKindLine-1;
	}

	if(PtInRect(&m_xItemRect, tPos))
	{
		m_nCurrentItemTop=m_nCurrentItemTop < m_nMaxItemLine-1 ? m_nCurrentItemTop + 1 : m_nMaxItemLine-1;
	}
}

BOOL CStoreWnd::SetSellKinds(CInventoryWnd* pxInvenWnd,CHAR Kind,INT nStdMode)
{
	if(pxInvenWnd!=NULL)
	{
	}
	return FALSE;
}

BOOL CStoreWnd::SetSellItemLst(CInventoryWnd* pxInvenWnd,CHAR Kind,BYTE nStdMode,CHAR bKind)
{
	CLIENTITEMRCD*	pxItem;
	RECT	tRect;
	SIZE	tSize;
	CHAR szTemp1[50];
	CHAR szTemp2[50];
	CHAR szParam[50];
	INT nCount=0;
//	if(여관이 아니냐?)
//	{	// 여관이 아니면 걸러서 넣어야 한다.
		if(pxInvenWnd!=NULL)
		{
			for(int i=0 ; i<60; i++)
			{
				pxItem = &pxInvenWnd->m_stInventoryItem[i].xItem.m_stItemInfo;
//				if(bKind==pxItem->szMakeIndex[0])
				{
					if(bKind!='a' && bKind!='A' && bKind!='b' && bKind!='B')
					{
						if(nStdMode==pxItem->stStdItem.bStdMode)
						{	// 기타는 다시 걸러 주어야 한다.
							m_xItems.AddNode(pxItem);
							strcpy(szTemp1,pxItem->stStdItem.szName);
							itoa(pxItem->nDura,szTemp2,10);
							strcpy(szParam,pxItem->stStdItem.szName);

							tSize = g_xMainWnd.GetStrLength(NULL,NULL,szTemp1);
							tRect.top = 0;
							tRect.left = 0;											// List Button 의 경우, Left  = 0;
							tRect.right = m_xItemRect.right - m_xItemRect.left;		//
							tRect.bottom = tSize.cy;

							m_xItemLstBtn.AddButton(szTemp1,szTemp2,tRect,nCount,szParam,RGB(180,180,0),RGB(255,0,0));
							nCount++;
						}
					}
					else
					{
						// 무기나 갑옷은 그냥 넣어도 무관..
						m_xItems.AddNode(pxItem);
						strcpy(szTemp1,pxItem->stStdItem.szName);
						itoa(pxItem->nDura,szTemp2,10);
						strcpy(szParam,pxItem->stStdItem.szName);

						tSize = g_xMainWnd.GetStrLength(NULL,NULL,szTemp1);
						tRect.top = 0;
						tRect.left = 0;											// List Button 의 경우, Left  = 0;
						tRect.right = m_xItemRect.right - m_xItemRect.left;		//
						tRect.bottom = tSize.cy;

						m_xItemLstBtn.AddButton(szTemp1,szTemp2,tRect,nCount,szParam,RGB(180,180,0),RGB(255,0,0));
						nCount++;
					}
				}
			}
		}
//	}
//	else
//	{	// 여관 이면 마구 넣어도 된다.
//		for(int i=0 ; i<60; i++)
//		{
//			pxItem = &pxInvenWnd->m_stInventoryItem[i].xItem.m_stItemInfo;
			// 무기나 갑옷은 그냥 넣어도 무관..
//			m_xItems.AddNode(pxItem);
//			strcpy(szTemp1,pxItem->stStdItem.szName);
//			itoa(pxItem->nDura,szTemp2,10);
//			strcpy(szParam,pxItem->stStdItem.szName);

//			tSize = g_xMainWnd.GetStrLength(NULL,NULL,szTemp1);
//			tRect.top = 0;
//			tRect.left = 0;											// List Button 의 경우, Left  = 0;
//			tRect.right = m_xItemRect.right - m_xItemRect.left;		//
//			tRect.bottom = tSize.cy;
//
//			m_xItemLstBtn.AddButton(szTemp1,szTemp2,tRect,nCount,szParam,RGB(180,180,0),RGB(255,0,0));
//			nCount++;
//		}
//	}
	return FALSE;
}


BOOL CStoreWnd::OnUpdateQueue(VOID)
{
	if(m_xPacketQueue.GetCount()>0)
	{
		INT nPos;
		CHAR  szDecodeMsg[MAX_MSG_LENGTH];

		LPPACKETMSG	lpPacketMsg;
		lpPacketMsg =(LPPACKETMSG) m_xPacketQueue.PopQ();
		if(lpPacketMsg->stDefMsg.nRecog == m_nNpcID)
		{
			switch(lpPacketMsg->stDefMsg.wIdent)
			{
			case SM_SENDGOODSLIST:
				{
					nPos = fnDecode6BitBuf(lpPacketMsg->szEncodeData, szDecodeMsg, sizeof(szDecodeMsg));
					szDecodeMsg[nPos] = NULL;
					SetBuyKinds(szDecodeMsg,lpPacketMsg->stDefMsg.wIdent);
					break;
				}
			case SM_SENDDETAILGOODSLIST:
				{
					nPos = fnDecode6BitBuf(lpPacketMsg->szEncodeData, szDecodeMsg, sizeof(szDecodeMsg));
					szDecodeMsg[nPos] = NULL;
					SetBuyItemLst(szDecodeMsg,(lpPacketMsg->stDefMsg).wParam);	
					break;
				}
			case SM_BUYITEM_SUCCESS:
				{
					sprintf(szDecodeMsg, "찜냥묘");
					DWORD dwFont = GetChatColor(_CHAT_COLOR4);
					DWORD dwBack = GetChatColor(_CHAT_COLOR3);
					g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, szDecodeMsg);
					break;

				}
			case SM_BUYITEM_FAIL:
				{
					sprintf(szDecodeMsg, "뭔찜呵겨");
					DWORD dwFont = GetChatColor(_CHAT_COLOR4);
					DWORD dwBack = GetChatColor(_CHAT_COLOR3);
					g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, szDecodeMsg);
					break;
				}
			}
		}
		else
		{
			// 해당 NPC가 아님
			// 해야할것
			// NPC창을 닫을것
			// NPC를 갱신 할것
			m_xPacketQueue.PushQ((BYTE*)lpPacketMsg);
			return FALSE;
		}
		SAFE_DELETE(lpPacketMsg);
		return TRUE;
	}
	return FALSE;
}

VOID CStoreWnd::SendDeTailGoodsList(INT nIndex,CHAR* szItemName)
{
	g_xGameProc.m_pSocket->SendGetDetailItem(m_nNpcID, nIndex, szItemName);
}

VOID CStoreWnd::SendButThisITme(CMTxtBtn* tBtn)
{
	if( tBtn == NULL )
		return;

	g_xGameProc.m_pSocket->SendBuyItem(m_nNpcID,m_xItems.GetCurrentData()->stStdItem.szName,tBtn->Param);					// MOON

}
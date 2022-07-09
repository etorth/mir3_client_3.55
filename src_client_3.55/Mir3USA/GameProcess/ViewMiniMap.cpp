/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"


CUtilWnd::CUtilWnd()
{
	Init();
}

CUtilWnd::~CUtilWnd()
{
	Destroy();
}

VOID CUtilWnd::Init()
{
	CGameWnd::Init();

	mUtil_bMode = _SET_ITEM_MODE;

	mUtil_BtnDownofHP1.Init();
	mUtil_BtnDownofHP2.Init();
	mUtil_BtnDownofHP3.Init();
	mUtil_BtnDownofHP4.Init();

	mUtil_BtnDownofMP1.Init();
	mUtil_BtnDownofMP2.Init();
	mUtil_BtnDownofMP3.Init();
	mUtil_BtnDownofMP4.Init();

	mUtil_BtnDownofHPMP.Init();
	
	mUtil_BtnDownofScroll2.Init();

	mUtil_BtnItemMode.Init();
	mUtil_BtnMagicMode.Init();

	mUtil_BtnClose.Init();

	mUtil_nSettedItemCount = 0;
	mUtil_nKindofSettedItem = 0;

	mUtil_nFocusedValue = 0;

	mUtil_dwItemUseTimer = 0;
	mUtil_dwMagicUseTimer = 0;
	mUtil_dwItemTakeonTimer = 0;

	ZeroMemory(mUtil_xUtilItemInfo, sizeof(CLIENTUTILITEMINFO)*10);
	ZeroMemory(mUtil_xUtilItemInfo2, sizeof(CLIENTUTILITEMINFO)*4);
	ZeroMemory(mUtil_xUtilMagicInfo, sizeof(CLIENTUTILMAGICINFO)*10);

	for (INT nI=0; nI<10; nI++ )
	{
		SetRect(&mUtil_rcCheck[nI], 0, 0, 0, 0);
		SetRect(&mUtil_rcItem[nI], 0, 0, 0, 0);
		SetRect(&mUtil_rcValue[nI], 0, 0, 0, 0);
		SetRect(&mUtil_rcPriority[nI], 0, 0, 0, 0);
		SetRect(&mUtil_rcName[nI], 0, 0, 0, 0);
	}

	for ( nI=0; nI<4; nI++ )
	{
		SetRect(&mUtil_rcMenu[nI], 0, 0, 0, 0);
	}	
}

VOID CUtilWnd::Destroy()
{
	CGameWnd::Destroy();
}

VOID CUtilWnd::CreateUtilWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend)
{
	CreateGameWnd(nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight, bBlend);

	mUtil_BtnClose.CreateGameBtn(pxWndImage, 1221, 1222, nStartX+526, nStartY+326, g_xMsg.GetMsg(1052), _BTN_TYPE_FOCUS, 1221, TRUE);

	mUtil_BtnDownofHP1.CreateGameBtn(pxWndImage, 2150, 2150, nStartX+125, nStartY+93, g_xMsg.GetMsg(4800), _BTN_TYPE_FOCUS, -1, FALSE);
	mUtil_BtnDownofHP2.CreateGameBtn(pxWndImage, 2150, 2150, nStartX+125, nStartY+136, g_xMsg.GetMsg(4800), _BTN_TYPE_FOCUS, -1, FALSE);
	mUtil_BtnDownofHP3.CreateGameBtn(pxWndImage, 2150, 2150, nStartX+125, nStartY+179, g_xMsg.GetMsg(4800), _BTN_TYPE_FOCUS, -1, FALSE);
	mUtil_BtnDownofHP4.CreateGameBtn(pxWndImage, 2154, 2150, nStartX+125, nStartY+222, g_xMsg.GetMsg(4800), _BTN_TYPE_FOCUS, -1, FALSE);

	mUtil_BtnDownofHPMP.CreateGameBtn(pxWndImage, 2154, 2154, nStartX+125, nStartY+265, g_xMsg.GetMsg(4801), _BTN_TYPE_FOCUS, -1, FALSE);

	mUtil_BtnDownofMP1.CreateGameBtn(pxWndImage, 2152, 2152, nStartX+395, nStartY+93, g_xMsg.GetMsg(4802), _BTN_TYPE_FOCUS, -1, FALSE);
	mUtil_BtnDownofMP2.CreateGameBtn(pxWndImage, 2152, 2152, nStartX+395, nStartY+136, g_xMsg.GetMsg(4802), _BTN_TYPE_FOCUS, -1, FALSE);
	mUtil_BtnDownofMP3.CreateGameBtn(pxWndImage, 2152, 2152, nStartX+395, nStartY+179, g_xMsg.GetMsg(4802), _BTN_TYPE_FOCUS, -1, FALSE);
	mUtil_BtnDownofMP4.CreateGameBtn(pxWndImage, 2156, 2152, nStartX+395, nStartY+222, g_xMsg.GetMsg(4802), _BTN_TYPE_FOCUS, -1, FALSE);

	mUtil_BtnDownofScroll2.CreateGameBtn(pxWndImage, 2156, 2156, nStartX+395, nStartY+265, g_xMsg.GetMsg(4803), _BTN_TYPE_FOCUS, -1, FALSE);

	mUtil_BtnDownofCharm1.CreateGameBtn(pxWndImage, 2150, 2150, nStartX+128, nStartY+99, g_xMsg.GetMsg(4804), _BTN_TYPE_FOCUS, -1, FALSE);
	mUtil_BtnDownofCharm2.CreateGameBtn(pxWndImage, 2150, 2150, nStartX+128, nStartY+152, g_xMsg.GetMsg(4804), _BTN_TYPE_FOCUS, -1, FALSE);

	mUtil_BtnDownofPoison1.CreateGameBtn(pxWndImage, 2154, 2154, nStartX+128, nStartY+205, g_xMsg.GetMsg(4805), _BTN_TYPE_FOCUS, -1, FALSE);
	mUtil_BtnDownofPoison2.CreateGameBtn(pxWndImage, 2154, 2154, nStartX+128, nStartY+258, g_xMsg.GetMsg(4805), _BTN_TYPE_FOCUS, -1, FALSE);

	mUtil_BtnItemMode.CreateGameBtn(pxWndImage, 2138, 2138, nStartX+64, nStartY+321, g_xMsg.GetMsg(4806), _BTN_TYPE_FOCUS, -1, FALSE);
	mUtil_BtnMagicMode.CreateGameBtn(pxWndImage, 2136, 2136, nStartX+144, nStartY+321, g_xMsg.GetMsg(4807), _BTN_TYPE_FOCUS, -1, FALSE);
}	
		
VOID CUtilWnd::ShowUtilWnd()
{
	mUtil_BtnClose.ChangeRect(m_rcWnd.left+526, m_rcWnd.top+340);
	
	mUtil_BtnItemMode.ChangeRect(m_rcWnd.left+64, m_rcWnd.top+335);
	mUtil_BtnMagicMode.ChangeRect(m_rcWnd.left+144, m_rcWnd.top+335);

	ShowGameWnd();
	
	if ( mUtil_bMode == _SET_ITEM_MODE )
	{
		ShowItemSetMode();
	}
	else if ( mUtil_bMode == _SET_MAGIC_MODE )
	{
		ShowMagicSetMode();
	}

	mUtil_BtnClose.ShowGameBtn();
	mUtil_BtnItemMode.ShowGameBtn();
	mUtil_BtnMagicMode.ShowGameBtn();
}


VOID CUtilWnd::ShowItemSetMode()
{
	mUtil_BtnDownofHP1.ChangeRect(m_rcWnd.left+125, m_rcWnd.top+76);
	mUtil_BtnDownofHP2.ChangeRect(m_rcWnd.left+125, m_rcWnd.top+120);
	mUtil_BtnDownofHP3.ChangeRect(m_rcWnd.left+125, m_rcWnd.top+162);
	mUtil_BtnDownofHP4.ChangeRect(m_rcWnd.left+125, m_rcWnd.top+205);
	
	mUtil_BtnDownofHPMP.ChangeRect(m_rcWnd.left+125, m_rcWnd.top+248);

	mUtil_BtnDownofMP1.ChangeRect(m_rcWnd.left+395, m_rcWnd.top+76);
	mUtil_BtnDownofMP2.ChangeRect(m_rcWnd.left+395, m_rcWnd.top+120);
	mUtil_BtnDownofMP3.ChangeRect(m_rcWnd.left+395, m_rcWnd.top+162);
	mUtil_BtnDownofMP4.ChangeRect(m_rcWnd.left+395, m_rcWnd.top+205);

	mUtil_BtnDownofScroll2.ChangeRect(m_rcWnd.left+395, m_rcWnd.top+248);


	for ( INT nI=0; nI<5; nI++ )
	{
		SetRect(&mUtil_rcCheck[nI], m_rcWnd.left+36, m_rcWnd.top+76 + nI * 43, m_rcWnd.left+59, m_rcWnd.top+94 + nI * 43);
		SetRect(&mUtil_rcItem[nI], m_rcWnd.left+86, m_rcWnd.top+65+ nI * 43, m_rcWnd.left+121, m_rcWnd.top+100 + nI * 43);
		SetRect(&mUtil_rcValue[nI], m_rcWnd.left+161, m_rcWnd.top+76 + nI * 43, m_rcWnd.left+198, m_rcWnd.top+94 + nI * 43);
		SetRect(&mUtil_rcPriority[nI], m_rcWnd.left+235, m_rcWnd.top+76 + nI * 43, m_rcWnd.left+258, m_rcWnd.top+94 + nI * 43);
		SetRect(&mUtil_rcName[nI], m_rcWnd.left+338, m_rcWnd.top+78 + nI * 25, m_rcWnd.left+424, m_rcWnd.top+96 + nI * 25);
	}

	for ( nI=5; nI<10; nI++ )
	{
		SetRect(&mUtil_rcCheck[nI], m_rcWnd.left+306, m_rcWnd.top+76 + (nI - 5) * 43, m_rcWnd.left+329, m_rcWnd.top+94 + (nI - 5) * 43);
		SetRect(&mUtil_rcItem[nI], m_rcWnd.left+355, m_rcWnd.top+65+ (nI - 5) * 43, m_rcWnd.left+391, m_rcWnd.top+100 + (nI - 5) * 43);
		SetRect(&mUtil_rcValue[nI], m_rcWnd.left+432, m_rcWnd.top+76 + (nI - 5) * 43, m_rcWnd.left+468, m_rcWnd.top+94 + (nI - 5) * 43);
		SetRect(&mUtil_rcPriority[nI], m_rcWnd.left+505, m_rcWnd.top+76 + (nI - 5) * 43, m_rcWnd.left+528, m_rcWnd.top+94 + (nI - 5) * 43);
		SetRect(&mUtil_rcName[nI], m_rcWnd.left+338, m_rcWnd.top+78 + nI * 25, m_rcWnd.left+424, m_rcWnd.top+96 + nI * 25);
	}

	// 탭 활성화 그림
	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(2138) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+64, m_rcWnd.top+335, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
	}

	if ( g_xGameProc.m_xMyHero.m_bJob != _JOB_DOSA )
	{
		// 전사, 술사일 경우 탭 그림 감춤
		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(2158) )
		{
			g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+11, m_rcWnd.top+326, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
		}
	}


	RECT rcText;

	rcText.left = m_rcWnd.left+18;
	rcText.right = m_rcWnd.left+80;
	rcText.top = m_rcWnd.top+38;
	rcText.bottom = m_rcWnd.top+58;
	g_xMainWnd.PutsHan(NULL, rcText, RGB(0, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(4808));

	rcText.left = m_rcWnd.left+82;
	rcText.right = m_rcWnd.left+147;
	g_xMainWnd.PutsHan(NULL, rcText, RGB(0, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(4809));

	rcText.left = m_rcWnd.left+149;
	rcText.right = m_rcWnd.left+213;
	g_xMainWnd.PutsHan(NULL, rcText, RGB(0, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(4810));

	rcText.left = m_rcWnd.left+215;
	rcText.right = m_rcWnd.left+277;
	g_xMainWnd.PutsHan(NULL, rcText, RGB(0, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(4811));

	rcText.left = m_rcWnd.left+287;
	rcText.right = m_rcWnd.left+351;
	g_xMainWnd.PutsHan(NULL, rcText, RGB(0, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(4808));

	rcText.left = m_rcWnd.left+353;
	rcText.right = m_rcWnd.left+417;
	g_xMainWnd.PutsHan(NULL, rcText, RGB(0, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(4809));

	rcText.left = m_rcWnd.left+419;
	rcText.right = m_rcWnd.left+483;
	g_xMainWnd.PutsHan(NULL, rcText, RGB(0, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(4810));

	rcText.left = m_rcWnd.left+485;
	rcText.right = m_rcWnd.left+547;
	g_xMainWnd.PutsHan(NULL, rcText, RGB(0, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(4811));


	CWHWilImageData* pxItemImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_ITEM_INVENTORY];

	for ( nI=0; nI<10; nI++ )
	{
		// 활성화 그리기
		if ( mUtil_xUtilItemInfo[nI].bCheck )
		{
			if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(2134))
			{
				g_xMainWnd.DrawWithImageForComp(mUtil_rcCheck[nI].left, mUtil_rcCheck[nI].top, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
												(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
			}
		}

		// 우선순위 그리기
		if ( mUtil_xUtilItemInfo[nI].nPriority > 0 )
		{
			if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(2139+mUtil_xUtilItemInfo[nI].nPriority))
			{
				g_xMainWnd.DrawWithImageForComp(mUtil_rcPriority[nI].left, mUtil_rcPriority[nI].top, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
												(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
			}
		}

		// 설정값
		if ( mUtil_xUtilItemInfo[nI].nValue > 0 )
		{
			CHAR szTemp[MAX_PATH];

			sprintf(szTemp, "%d", mUtil_xUtilItemInfo[nI].nValue);
			g_xMainWnd.PutsHan(NULL, mUtil_rcValue[nI], RGB(200, 200, 200), RGB(0, 0, 0), szTemp);
		}

		if ( mUtil_xUtilItemInfo[nI].xItem.m_stItemInfo.stStdItem.wLooks != 0 )
		{
			mUtil_xUtilItemInfo[nI].xItem.DrawItem(mUtil_rcItem[nI].left, mUtil_rcItem[nI].top);
		}
	}


//  선택메뉴 아이템 그리기
	if ( mUtil_nSettedItemCount > 0 )
	{
		if ( mUtil_rcMenu[0].left < 50 )
			int ntest = 0;

		INT nWidth = 0;
		// 바탕 3d로 찍기.
		switch(mUtil_nSettedItemCount)
		{
		case 1:
			nWidth = 38;
			break;
		case 2:
			nWidth = 38 * 2;
			break;
		case 3:
			nWidth = 38 * 3;
			break;
		case 4:
			nWidth = 38 * 4;
			break;
		}

		INT		nStartX = 0;
		INT		nStartY = 0;

		if ( mUtil_nKindofSettedItem == 5 || mUtil_nKindofSettedItem == 10 )
			nStartY = m_rcWnd.top + 100 + (4 * 43);
		else
			nStartY = m_rcWnd.top + 100 + ( mUtil_nKindofSettedItem % 5 - 1) * 43;

		if ( mUtil_nKindofSettedItem == 1 || mUtil_nKindofSettedItem == 2 || mUtil_nKindofSettedItem == 3 ||
			 mUtil_nKindofSettedItem == 4 || mUtil_nKindofSettedItem == 5 )
			nStartX = m_rcWnd.left + 125;
		else
			nStartX = m_rcWnd.left + 395;
			

		D3DVECTOR	 vecTrans((FLOAT)(nStartX), (FLOAT)(nStartY), 0);
		D3DVECTOR	 vecScale((FLOAT)(nWidth), (FLOAT)(38), 1);
		D3DMATERIAL7 mtrl;

		D3DUtil_InitMaterial(mtrl, (FLOAT)100/255.0f, (FLOAT)100/255.0f, (FLOAT)50/255.0f);
		mtrl.diffuse.a = 150.0f/255.0f;
		g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

		// 메뉴 아이템
		for ( INT nCnt = 0; nCnt < mUtil_nSettedItemCount; nCnt++ )
		{
			mUtil_xItem[nCnt].DrawItem(mUtil_rcMenu[nCnt].left, mUtil_rcMenu[nCnt].top);
		}
	}
	
	mUtil_BtnDownofHP1.ShowGameBtn();
	mUtil_BtnDownofHP2.ShowGameBtn();
	mUtil_BtnDownofHP3.ShowGameBtn();
	mUtil_BtnDownofHP4.ShowGameBtn();
	mUtil_BtnDownofMP1.ShowGameBtn();
	mUtil_BtnDownofMP2.ShowGameBtn();
	mUtil_BtnDownofMP3.ShowGameBtn();
	mUtil_BtnDownofMP4.ShowGameBtn();
	mUtil_BtnDownofHPMP.ShowGameBtn();	
	mUtil_BtnDownofScroll2.ShowGameBtn();
}


VOID CUtilWnd::ShowMagicSetMode()
{
	mUtil_BtnDownofCharm1.ChangeRect(m_rcWnd.left+129, m_rcWnd.top+82);
	mUtil_BtnDownofCharm2.ChangeRect(m_rcWnd.left+129, m_rcWnd.top+134);

	mUtil_BtnDownofPoison1.ChangeRect(m_rcWnd.left+129, m_rcWnd.top+188);
	mUtil_BtnDownofPoison2.ChangeRect(m_rcWnd.left+129, m_rcWnd.top+241);

	// 바탕
	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(2160) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left-229, m_rcWnd.top-68, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
	}

	RECT rcText;

	rcText.left = m_rcWnd.left+18;
	rcText.right = m_rcWnd.left+83;
	rcText.top = m_rcWnd.top+38;
	rcText.bottom = m_rcWnd.top+58;
	g_xMainWnd.PutsHan(NULL, rcText, RGB(0, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(4808));
	
	rcText.left = m_rcWnd.left+83;
	rcText.right = m_rcWnd.left+149;
	g_xMainWnd.PutsHan(NULL, rcText, RGB(0, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(4809));
	
	rcText.left = m_rcWnd.left+149;
	rcText.right = m_rcWnd.left+215;
	g_xMainWnd.PutsHan(NULL, rcText, RGB(0, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(4811));
	
	rcText.left = m_rcWnd.left+272;
	rcText.right = m_rcWnd.left+334;
	g_xMainWnd.PutsHan(NULL, rcText, RGB(0, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(4808));
	
	rcText.left = m_rcWnd.left+334;
	rcText.right = m_rcWnd.left+427;
	g_xMainWnd.PutsHan(NULL, rcText, RGB(0, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(4840));
	
	rcText.left = m_rcWnd.left+427;
	rcText.right = m_rcWnd.left+487;
	g_xMainWnd.PutsHan(NULL, rcText, RGB(0, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(4810));
	
	rcText.left = m_rcWnd.left+487;
	rcText.right = m_rcWnd.left+547;
	g_xMainWnd.PutsHan(NULL, rcText, RGB(0, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(4811));

	for ( INT nI=0; nI<10; nI++ )
	{
		SetRect(&mUtil_rcCheck[nI], m_rcWnd.left+291, m_rcWnd.top+63 + nI * 25, m_rcWnd.left+317, m_rcWnd.top+79 + nI * 25);
		SetRect(&mUtil_rcValue[nI], m_rcWnd.left+438, m_rcWnd.top+65 + nI * 25, m_rcWnd.left+474, m_rcWnd.top+81 + nI * 25);
		SetRect(&mUtil_rcPriority[nI], m_rcWnd.left+504, m_rcWnd.top+63 + nI * 25, m_rcWnd.left+528, m_rcWnd.top+79 + nI * 25);
		SetRect(&mUtil_rcName[nI], m_rcWnd.left+338, m_rcWnd.top+65 + nI * 25, m_rcWnd.left+424, m_rcWnd.top+81 + nI * 25);
	}

	for ( nI=0; nI<4; nI++ )
	{
		SetRect(&mUtil_rcCheck2[nI], m_rcWnd.left+38, m_rcWnd.top+81 + nI * 53, m_rcWnd.left+63, m_rcWnd.top+101 + nI * 53);
		SetRect(&mUtil_rcItem[nI], m_rcWnd.left+89, m_rcWnd.top+72 + nI * 53, m_rcWnd.left+127, m_rcWnd.top+107 + nI * 53);
		SetRect(&mUtil_rcPriority2[nI], m_rcWnd.left+165, m_rcWnd.top+81 + nI * 53, m_rcWnd.left+189, m_rcWnd.top+101 + nI * 53);
	}

	// 탭 활성화 그림
	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(2136) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+144, m_rcWnd.top+335, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
	}

	for ( nI=0; nI<4; nI++ )
	{
		// 활성화 그리기
		if ( mUtil_xUtilItemInfo2[nI].bCheck )
		{
			if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(2134))
			{
				g_xMainWnd.DrawWithImageForComp(mUtil_rcCheck2[nI].left, mUtil_rcCheck2[nI].top, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
												(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
			}
		}

		// 우선순위 그리기
		if ( mUtil_xUtilItemInfo2[nI].nPriority > 0 )
		{
			INT nAtoI = atoi((char*)&mUtil_xUtilItemInfo2[nI].nPriority);
			BYTE bKey;
			if ( nAtoI < 10 && nAtoI > 0 )
			{
				bKey = (BYTE)nAtoI;
			}
			else
			{
				bKey = (BYTE)(mUtil_xUtilItemInfo2[nI].nPriority - 55);
			}

			if ( m_pxWndImage->NewSetIndex(1659+bKey) )
			{
				g_xMainWnd.DrawWithImageForComp(mUtil_rcPriority2[nI].left, mUtil_rcPriority2[nI].top, 
												m_pxWndImage->m_lpstNewCurrWilImageInfo->shWidth, 
												m_pxWndImage->m_lpstNewCurrWilImageInfo->shHeight,
												(WORD*)(m_pxWndImage->m_pbCurrImage));
			}

//			if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(2139+mUtil_xUtilItemInfo2[nI].nPriority))
//			{
//				g_xMainWnd.DrawWithImageForComp(mUtil_rcPriority2[nI].left, mUtil_rcPriority2[nI].top, 
//												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
//												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
//												(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
//			}
		}

		if ( mUtil_xUtilItemInfo2[nI].xItem.m_stItemInfo.stStdItem.wLooks != 0 )
		{
			mUtil_xUtilItemInfo2[nI].xItem.DrawItem(mUtil_rcItem[nI].left, mUtil_rcItem[nI].top);
		}
	}

	for ( nI=0; nI<10; nI++ )
	{
		// 활성화 그리기
		if ( mUtil_xUtilMagicInfo[nI].bCheck )
		{
			if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(2134))
			{
				g_xMainWnd.DrawWithImageForComp(mUtil_rcCheck[nI].left, mUtil_rcCheck[nI].top, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
												(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
			}
		}

		// 우선순위 그리기
		if ( mUtil_xUtilMagicInfo[nI].nPriority > 0 )
		{
			if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(2139+mUtil_xUtilMagicInfo[nI].nPriority))
			{
				g_xMainWnd.DrawWithImageForComp(mUtil_rcPriority[nI].left, mUtil_rcPriority[nI].top, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
												(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
			}
		}

		// 설정값
		if ( mUtil_xUtilMagicInfo[nI].nValue > 0 )
		{
			CHAR szTemp[MAX_PATH];

			sprintf(szTemp, "%d", mUtil_xUtilMagicInfo[nI].nValue);
			g_xMainWnd.PutsHan(NULL, mUtil_rcValue[nI], RGB(200, 200, 200), RGB(0, 0, 0), szTemp);
		}

		if ( strlen(mUtil_xUtilMagicInfo[nI].szName) > 0 )
		{
			g_xMainWnd.PutsHan(NULL, mUtil_rcName[nI], RGB(200, 200, 200), RGB(0, 0, 0), mUtil_xUtilMagicInfo[nI].szName);
		}
	}

//  선택메뉴 아이템 그리기
	if ( mUtil_nSettedItemCount > 0 )
	{
		if ( mUtil_rcMenu[0].left < 50 )
			int ntest = 0;

		INT nWidth = 0;
		// 바탕 3d로 찍기.
		switch(mUtil_nSettedItemCount)
		{
		case 1:
			nWidth = 38;
			break;
		case 2:
			nWidth = 38 * 2;
			break;
		case 3:
			nWidth = 38 * 3;
			break;
		case 4:
			nWidth = 38 * 4;
			break;
		case 5:
			nWidth = 38 * 5;
			break;
		case 6:
			nWidth = 38 * 6;
			break;
		case 7:
			nWidth = 38 * 7;
			break;
		}

		INT		nStartX = m_rcWnd.left + 128;
		INT		nStartY = 0;
/*
		mUtil_rcMenu[0].left = m_rcWnd.left + 128;
		mUtil_rcMenu[0].right = mUtil_rcMenu[0].left + 38;
		mUtil_rcMenu[0].top = m_rcWnd.top + 90 + 52 * ( mUtil_nKindofSettedItem - 11 ); 
		mUtil_rcMenu[0].bottom = mUtil_rcMenu[0].top + 38;
*/

		nStartY = m_rcWnd.top + 90 + 52 * (mUtil_nKindofSettedItem - 11);
			

		D3DVECTOR	 vecTrans((FLOAT)(nStartX), (FLOAT)(nStartY), 0);
		D3DVECTOR	 vecScale((FLOAT)(nWidth), (FLOAT)(38), 1);
		D3DMATERIAL7 mtrl;

		D3DUtil_InitMaterial(mtrl, (FLOAT)100/255.0f, (FLOAT)100/255.0f, (FLOAT)50/255.0f);
		mtrl.diffuse.a = 150.0f/255.0f;
		g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

		// 메뉴 아이템
		for ( INT nCnt = 0; nCnt < mUtil_nSettedItemCount; nCnt++ )
		{
			mUtil_xItem[nCnt].DrawItem(mUtil_rcMenu[nCnt].left, mUtil_rcMenu[nCnt].top);
		}
	}

	mUtil_BtnDownofCharm1.ShowGameBtn();
	mUtil_BtnDownofCharm2.ShowGameBtn();
	mUtil_BtnDownofPoison1.ShowGameBtn();
	mUtil_BtnDownofPoison2.ShowGameBtn();
}

BOOL CUtilWnd::OnLButtonDown(POINT ptMouse)
{
	if ( g_xGameProc.m_xMyHero.m_bJob == _JOB_DOSA )
	{
		if ( mUtil_BtnItemMode.OnLButtonDown(ptMouse) )
		{
			mUtil_bMode = _SET_ITEM_MODE;
			mUtil_nSettedItemCount = 0;
			mUtil_nKindofSettedItem = 0;
			return FALSE;
		}

		if ( mUtil_BtnMagicMode.OnLButtonDown(ptMouse) )
		{
			mUtil_bMode = _SET_MAGIC_MODE;
			mUtil_nSettedItemCount = 0;
			mUtil_nKindofSettedItem = 0;
			return FALSE;
		}
	}

	if ( mUtil_BtnClose.OnLButtonDown(ptMouse) )
	{
		return FALSE;
	}

	if ( mUtil_bMode == _SET_ITEM_MODE )
	{
		return LBtnDownOnItemSetMode(ptMouse);
	}
	else if ( mUtil_bMode == _SET_MAGIC_MODE )
	{
		return LBtnDownOnMagicSetMode(ptMouse);
	}


	return FALSE;
}

BOOL CUtilWnd::LBtnDownOnItemSetMode(POINT ptMouse)
{
	// 선택메뉴 선택 처리
	if ( mUtil_nKindofSettedItem != 0 )
	{
		for ( INT nI=0; nI<mUtil_nSettedItemCount; nI++ )
		{
			if ( PtInRect(&mUtil_rcMenu[nI], ptMouse) )
			{
				mUtil_xUtilItemInfo[mUtil_nKindofSettedItem-1].xItem.SetItem(mUtil_xItem[nI].m_stItemInfo, 0);
			}
		}
	}
	
	mUtil_nSettedItemCount = 0;
	mUtil_nKindofSettedItem = 0;

	for ( INT nI=0; nI<10; nI++ )
	{
		if ( PtInRect(&mUtil_rcCheck[nI], ptMouse) )
		{
			mUtil_xUtilItemInfo[nI].bCheck = !mUtil_xUtilItemInfo[nI].bCheck;
			break;
		}
	}

	if ( mUtil_BtnDownofHP1.OnLButtonDown(ptMouse) )
	{
		mUtil_nSettedItemCount = 0;
		SetMenuItemToHPItem();
		mUtil_nKindofSettedItem = 1;
		SetMenuRect();
		return FALSE;
	}

	if ( mUtil_BtnDownofHP2.OnLButtonDown(ptMouse) )
	{
		mUtil_nSettedItemCount = 0;
		SetMenuItemToHPItem();
		mUtil_nKindofSettedItem = 2;
		SetMenuRect();
		return FALSE;
	}

	if ( mUtil_BtnDownofHP3.OnLButtonDown(ptMouse) )
	{
		mUtil_nSettedItemCount = 0;
		SetMenuItemToHPItem();
		mUtil_nKindofSettedItem = 3;
		SetMenuRect();
		return FALSE;
	}

	if ( mUtil_BtnDownofMP1.OnLButtonDown(ptMouse) )
	{
		mUtil_nSettedItemCount = 0;
		SetMenuItemToMPItem();
		mUtil_nKindofSettedItem = 6;
		SetMenuRect();
		return FALSE;
	}

	if ( mUtil_BtnDownofMP2.OnLButtonDown(ptMouse) )
	{
		mUtil_nSettedItemCount = 0;
		SetMenuItemToMPItem();
		mUtil_nKindofSettedItem = 7;
		SetMenuRect();
		return FALSE;
	}

	if ( mUtil_BtnDownofMP3.OnLButtonDown(ptMouse) )
	{
		mUtil_nSettedItemCount = 0;
		SetMenuItemToMPItem();
		mUtil_nKindofSettedItem = 8;
		SetMenuRect();
		return FALSE;
	}

	if ( mUtil_BtnDownofHP4.OnLButtonDown(ptMouse) )
	{
		mUtil_nSettedItemCount = 0;
		SetMenuItemToHPItem();
		mUtil_nKindofSettedItem = 4;
		SetMenuRect();
		return FALSE;
	}

	if ( mUtil_BtnDownofHPMP.OnLButtonDown(ptMouse) )
	{
		mUtil_nSettedItemCount = 0;
		SetMenuItemToHPMPItem();
		mUtil_nKindofSettedItem = 5;
		SetMenuRect();
		return FALSE;
	}

	if ( mUtil_BtnDownofMP4.OnLButtonDown(ptMouse) )
	{
		mUtil_nSettedItemCount = 0;
		SetMenuItemToMPItem();
		mUtil_nKindofSettedItem = 9;
		SetMenuRect();
		return FALSE;
	}

	if ( mUtil_BtnDownofScroll2.OnLButtonDown(ptMouse) )
	{
		mUtil_nSettedItemCount = 0;
		SetMenuItemToScrollItem();
		mUtil_nKindofSettedItem = 10;
		SetMenuRect();
		return FALSE;
	}

	mUtil_nSettedItemCount = 0;
	mUtil_nKindofSettedItem = 0;

	for ( nI=0; nI<4; nI++ )
		SetRect(&mUtil_rcMenu[nI], 0, 0, 0, 0);

	return FALSE;
}

BOOL CUtilWnd::LBtnDownOnMagicSetMode(POINT ptMouse)
{
	// 선택메뉴 선택 처리
	if ( mUtil_nKindofSettedItem != 0 )
	{
		for ( INT nI=0; nI<mUtil_nSettedItemCount; nI++ )
		{
			if ( PtInRect(&mUtil_rcMenu[nI], ptMouse) )
			{
				mUtil_xUtilItemInfo2[mUtil_nKindofSettedItem-11].xItem.SetItem(mUtil_xItem[nI].m_stItemInfo, 0);
			}
		}
	}

	for ( INT nI=0; nI<10; nI++ )
	{
		if ( PtInRect(&mUtil_rcCheck[nI], ptMouse) )
		{
			mUtil_xUtilMagicInfo[nI].bCheck = !mUtil_xUtilMagicInfo[nI].bCheck;
			break;
		}
	}

	for ( nI=0; nI<4; nI++ )
	{
		if ( PtInRect(&mUtil_rcCheck2[nI], ptMouse) )
		{
			mUtil_xUtilItemInfo2[nI].bCheck = !mUtil_xUtilItemInfo2[nI].bCheck;
			break;
		}
	}

	if ( mUtil_BtnDownofCharm1.OnLButtonDown(ptMouse) )
	{
		mUtil_nSettedItemCount = 0;
		SetMenuItemToCharmItem();
		mUtil_nKindofSettedItem = 11;
		SetMenuRect();
		return FALSE;
	}

	if ( mUtil_BtnDownofCharm2.OnLButtonDown(ptMouse) )
	{
		mUtil_nSettedItemCount = 0;
		SetMenuItemToCharmItem();
		mUtil_nKindofSettedItem = 12;
		SetMenuRect();
		return FALSE;
	}

	if ( mUtil_BtnDownofPoison1.OnLButtonDown(ptMouse) )
	{
		mUtil_nSettedItemCount = 0;
		SetMenuItemToPoisonItem();
		mUtil_nKindofSettedItem = 13;
		SetMenuRect();
		return FALSE;
	}

	if ( mUtil_BtnDownofPoison2.OnLButtonDown(ptMouse) )
	{
		mUtil_nSettedItemCount = 0;
		SetMenuItemToPoisonItem();
		mUtil_nKindofSettedItem = 14;
		SetMenuRect();
		return FALSE;
	}

	mUtil_nSettedItemCount = 0;
	mUtil_nKindofSettedItem = 0;

	return FALSE;
}

BOOL CUtilWnd::OnLButtonUp(POINT ptMouse)
{
	if ( g_xGameProc.m_xMyHero.m_bJob == _JOB_DOSA )
	{
		if ( mUtil_BtnItemMode.OnLButtonUp(ptMouse) )
		{
			return FALSE;
		}
			
		if ( mUtil_BtnMagicMode.OnLButtonUp(ptMouse) )
		{
			return FALSE;
		}
	}

	if ( mUtil_BtnClose.OnLButtonUp(ptMouse) )
	{
		return TRUE;
	}

	if ( mUtil_bMode == _SET_ITEM_MODE )
	{
		return LBtnUpOnItemSetMode(ptMouse);
	}
	else if ( mUtil_bMode == _SET_MAGIC_MODE )
	{
		return LBtnUpOnMagicSetMode(ptMouse);
	}
	
	return FALSE;
}

BOOL CUtilWnd::LBtnUpOnItemSetMode(POINT ptMouse)
{
	for ( INT nI=0; nI<10; nI++ )
	{
		if ( PtInRect(&mUtil_rcValue[nI], g_xGameProc.m_ptMousePos) )
		{
			mUtil_nFocusedValue = nI;
			g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_SETUTIL, _YESNO, g_xMsg.GetMsg(4812), TRUE);
			break;
		}

		if ( PtInRect(&mUtil_rcPriority[nI], g_xGameProc.m_ptMousePos) )
		{
			mUtil_nFocusedValue = nI;
			g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_SETPRIORITY, _YESNO, g_xMsg.GetMsg(4813), TRUE);
			break;
		}
	}

	if ( mUtil_BtnDownofHP1.OnLButtonUp(ptMouse) )
	{
		return FALSE;
	}

	if ( mUtil_BtnDownofHP2.OnLButtonUp(ptMouse) )
	{
		return FALSE;
	}

	if ( mUtil_BtnDownofHP3.OnLButtonUp(ptMouse) )
	{
		return FALSE;
	}

	if ( mUtil_BtnDownofMP1.OnLButtonUp(ptMouse) )
	{
		return FALSE;
	}

	if ( mUtil_BtnDownofMP2.OnLButtonUp(ptMouse) )
	{
		return FALSE;
	}

	if ( mUtil_BtnDownofMP3.OnLButtonUp(ptMouse) )
	{
		return FALSE;
	}

	if ( mUtil_BtnDownofHP4.OnLButtonUp(ptMouse) )
	{
		return FALSE;
	}

	if ( mUtil_BtnDownofHPMP.OnLButtonUp(ptMouse) )
	{
		return FALSE;
	}

	if ( mUtil_BtnDownofMP4.OnLButtonUp(ptMouse) )
	{
		return FALSE;
	}

	if ( mUtil_BtnDownofScroll2.OnLButtonUp(ptMouse) )
	{
		return FALSE;
	}

	return FALSE;
}

BOOL CUtilWnd::LBtnUpOnMagicSetMode(POINT ptMouse)
{
	for ( INT nI=0; nI<10; nI++ )
	{
		if ( PtInRect(&mUtil_rcValue[nI], g_xGameProc.m_ptMousePos) )
		{
			mUtil_nFocusedValue = nI;
			g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_SETUTIL, _YESNO, g_xMsg.GetMsg(4812), TRUE);
			break;
		}

		if ( PtInRect(&mUtil_rcPriority[nI], g_xGameProc.m_ptMousePos) )
		{
			mUtil_nFocusedValue = nI;
			g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_SETPRIORITY, _YESNO, g_xMsg.GetMsg(4813), TRUE);
			break;
		}

		if ( PtInRect(&mUtil_rcName[nI], g_xGameProc.m_ptMousePos) )
		{
			mUtil_nFocusedValue = nI;
			g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_SETNAME, _YESNO, g_xMsg.GetMsg(4814), TRUE);
			break;
		}
	}

	for ( nI=0; nI<4; nI++ )
	{
		if ( PtInRect(&mUtil_rcPriority2[nI], g_xGameProc.m_ptMousePos) )
		{
			mUtil_nFocusedValue = nI;
			g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_SETPRIORITY2, _YESNO, g_xMsg.GetMsg(4815), TRUE);
			break;
		}
	}


	if ( mUtil_BtnDownofCharm1.OnLButtonUp(ptMouse) )
	{
		return FALSE;
	}

	if ( mUtil_BtnDownofCharm2.OnLButtonUp(ptMouse) )
	{
		return FALSE;
	}

	if ( mUtil_BtnDownofPoison1.OnLButtonUp(ptMouse) )
	{
		return FALSE;
	}

	if ( mUtil_BtnDownofPoison2.OnLButtonUp(ptMouse) )
	{
		return FALSE;
	}

	return FALSE;
}

BOOL CUtilWnd::OnMouseMove(POINT ptMouse)
{
	mUtil_BtnClose.OnMouseMove(ptMouse);

	if ( g_xGameProc.m_xMyHero.m_bJob == _JOB_DOSA )
	{
		mUtil_BtnItemMode.OnMouseMove(ptMouse);
		mUtil_BtnMagicMode.OnMouseMove(ptMouse);
	}

	if ( mUtil_bMode == _SET_ITEM_MODE )
	{
		return MouseMoveOnItemSetMode(ptMouse);
	}
	else if ( mUtil_bMode == _SET_MAGIC_MODE )
	{
		return MouseMoveOnMagicSetMode(ptMouse);
	}

	return FALSE;
}

BOOL CUtilWnd::MouseMoveOnItemSetMode(POINT ptMouse)
{
	mUtil_BtnDownofHP1.OnMouseMove(ptMouse);
	mUtil_BtnDownofHP2.OnMouseMove(ptMouse);
	mUtil_BtnDownofHP3.OnMouseMove(ptMouse);
	mUtil_BtnDownofHP4.OnMouseMove(ptMouse);
	mUtil_BtnDownofMP1.OnMouseMove(ptMouse);
	mUtil_BtnDownofMP2.OnMouseMove(ptMouse);
	mUtil_BtnDownofMP3.OnMouseMove(ptMouse);
	mUtil_BtnDownofMP4.OnMouseMove(ptMouse);
	mUtil_BtnDownofHPMP.OnMouseMove(ptMouse);
	mUtil_BtnDownofScroll2.OnMouseMove(ptMouse);

	return FALSE;
}

BOOL CUtilWnd::MouseMoveOnMagicSetMode(POINT ptMouse)
{
	mUtil_BtnDownofCharm1.OnMouseMove(ptMouse);
	mUtil_BtnDownofCharm2.OnMouseMove(ptMouse);
	mUtil_BtnDownofPoison1.OnMouseMove(ptMouse);
	mUtil_BtnDownofPoison2.OnMouseMove(ptMouse);

	return FALSE;
}

BOOL CUtilWnd::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	for (INT nI=0; nI<10; nI++)
	{
		if ( mUtil_bMode == _SET_ITEM_MODE )
		{
			if ( PtInRect(&mUtil_rcPriority[nI], g_xGameProc.m_ptMousePos) )
			{
				INT nVal = wParam - 48;

				if ( nVal > 0 && nVal < 11 )
				{
					for ( INT nJ=0; nJ<10; nJ++ )
					{
						if ( mUtil_xUtilItemInfo[nJ].nPriority == nVal )
							mUtil_xUtilItemInfo[nJ].nPriority = 0;
					}
				}

				switch ( nVal )
				{
				case 1:		mUtil_xUtilItemInfo[nI].nPriority = 1;	return TRUE;
				case 2:		mUtil_xUtilItemInfo[nI].nPriority = 2;	return TRUE;
				case 3:		mUtil_xUtilItemInfo[nI].nPriority = 3;	return TRUE;
				case 4:		mUtil_xUtilItemInfo[nI].nPriority = 4;	return TRUE;
				case 5:		mUtil_xUtilItemInfo[nI].nPriority = 5;	return TRUE;
				case 6:		mUtil_xUtilItemInfo[nI].nPriority = 6;	return TRUE;
				case 7:		mUtil_xUtilItemInfo[nI].nPriority = 7;	return TRUE;
				case 8:		mUtil_xUtilItemInfo[nI].nPriority = 8;	return TRUE;
				case 9:		mUtil_xUtilItemInfo[nI].nPriority = 9;	return TRUE;
				case 0: 	mUtil_xUtilItemInfo[nI].nPriority = 10;	return TRUE;
				}
			}
		}
		else if ( mUtil_bMode == _SET_MAGIC_MODE )
		{
			if ( PtInRect(&mUtil_rcPriority[nI], g_xGameProc.m_ptMousePos) )
			{
				INT nVal = wParam - 48;

				if ( nVal > 0 && nVal < 11 )
				{
					for ( INT nJ=0; nJ<10; nJ++ )
					{
						if ( mUtil_xUtilMagicInfo[nJ].nPriority == nVal )
							mUtil_xUtilMagicInfo[nJ].nPriority = 0;
					}
				}

				switch ( nVal )
				{
				case 1:		mUtil_xUtilMagicInfo[nI].nPriority = 1;	return TRUE;
				case 2:		mUtil_xUtilMagicInfo[nI].nPriority = 2;	return TRUE;
				case 3:		mUtil_xUtilMagicInfo[nI].nPriority = 3;	return TRUE;
				case 4:		mUtil_xUtilMagicInfo[nI].nPriority = 4;	return TRUE;
				case 5:		mUtil_xUtilMagicInfo[nI].nPriority = 5;	return TRUE;
				case 6:		mUtil_xUtilMagicInfo[nI].nPriority = 6;	return TRUE;
				case 7:		mUtil_xUtilMagicInfo[nI].nPriority = 7;	return TRUE;
				case 8:		mUtil_xUtilMagicInfo[nI].nPriority = 8;	return TRUE;
				case 9:		mUtil_xUtilMagicInfo[nI].nPriority = 9;	return TRUE;
				case 0: 	mUtil_xUtilMagicInfo[nI].nPriority = 10;	return TRUE;
				}
			}
			else if ( PtInRect(&mUtil_rcPriority2[nI], g_xGameProc.m_ptMousePos) )
			{

				switch ( wParam )
				{
				case VK_F1:		SetKey('1');		return TRUE;
				case VK_F2:		SetKey('2');		return TRUE;
				case VK_F3:		SetKey('3');		return TRUE;
				case VK_F4:		SetKey('4');		return TRUE;
				case VK_F5:		SetKey('5');		return TRUE;
				case VK_F6:		SetKey('6');		return TRUE;
				case VK_F7:		SetKey('7');		return TRUE;
				case VK_F8:		SetKey('8');		return TRUE;
				case VK_F9:		SetKey('9');		return TRUE;
				case VK_F10:	SetKey('A');		return TRUE;
				case VK_F11:	SetKey('B');		return TRUE;
				case VK_F12:	SetKey('C');		return TRUE;
				}
/*
				INT nVal = wParam - 48;

				if ( nVal > 0 && nVal < 5 )
				{
					for ( INT nJ=0; nJ<4; nJ++ )
					{
						if ( mUtil_xUtilItemInfo2[nJ].nPriority == nVal )
							mUtil_xUtilItemInfo2[nJ].nPriority = 0;
					}
				}

				switch ( nVal )
				{
				case 1:		mUtil_xUtilItemInfo2[nI].nPriority = 1;	return TRUE;
				case 2:		mUtil_xUtilItemInfo2[nI].nPriority = 2;	return TRUE;
				case 3:		mUtil_xUtilItemInfo2[nI].nPriority = 3;	return TRUE;
				case 4:		mUtil_xUtilItemInfo2[nI].nPriority = 4;	return TRUE;
				}
*/
			}
		}
	}
	return FALSE;
}


VOID CUtilWnd::SetMenuItemToHPItem()
{
	// 체력회복약(소)
	mUtil_xItem[0].m_stItemInfo.stStdItem.bShape = 0;
	mUtil_xItem[0].m_stItemInfo.stStdItem.wLooks = 5;
	mUtil_xItem[0].m_stItemInfo.stStdItem.wAC = 30;
	mUtil_xItem[0].m_stItemInfo.stStdItem.wMAC = 0;
	mUtil_xItem[0].m_stItemInfo.stStdItem.bWeight = 1;
	sprintf( mUtil_xItem[0].m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(4816));

	// 체력회복약(중)
	mUtil_xItem[1].m_stItemInfo.stStdItem.bShape = 0;
	mUtil_xItem[1].m_stItemInfo.stStdItem.wLooks = 6;
	mUtil_xItem[1].m_stItemInfo.stStdItem.wAC = 70;
	mUtil_xItem[1].m_stItemInfo.stStdItem.wMAC = 0;
	mUtil_xItem[1].m_stItemInfo.stStdItem.bWeight = 1;
	sprintf( mUtil_xItem[1].m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(4817));

	// 체력회복약(대)
	mUtil_xItem[2].m_stItemInfo.stStdItem.bShape = 0;
	mUtil_xItem[2].m_stItemInfo.stStdItem.wLooks = 7;
	mUtil_xItem[2].m_stItemInfo.stStdItem.wAC = 110;
	mUtil_xItem[2].m_stItemInfo.stStdItem.wMAC = 0;
	mUtil_xItem[2].m_stItemInfo.stStdItem.bWeight = 2;
	sprintf( mUtil_xItem[2].m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(4818));

	// 체력회복약(특)
	mUtil_xItem[3].m_stItemInfo.stStdItem.bShape = 0;
	mUtil_xItem[3].m_stItemInfo.stStdItem.wLooks = 8;
	mUtil_xItem[3].m_stItemInfo.stStdItem.wAC = 170;
	mUtil_xItem[3].m_stItemInfo.stStdItem.wMAC = 0;
	mUtil_xItem[3].m_stItemInfo.stStdItem.bWeight = 3;
	sprintf( mUtil_xItem[3].m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(4819));

	mUtil_nSettedItemCount = 4;
}

VOID CUtilWnd::SetMenuItemToHPMPItem()
{
	// 선화수
	mUtil_xItem[0].m_stItemInfo.stStdItem.bShape = 1;
	mUtil_xItem[0].m_stItemInfo.stStdItem.wLooks = 20;
	mUtil_xItem[0].m_stItemInfo.stStdItem.wAC = 70;
	mUtil_xItem[0].m_stItemInfo.stStdItem.wMAC = 110;
	mUtil_xItem[0].m_stItemInfo.stStdItem.bWeight = 1;
	sprintf( mUtil_xItem[0].m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(4820));

	// 선화수(중)
	mUtil_xItem[1].m_stItemInfo.stStdItem.bShape = 1;
	mUtil_xItem[1].m_stItemInfo.stStdItem.wLooks = 21;
	mUtil_xItem[1].m_stItemInfo.stStdItem.wAC = 110;
	mUtil_xItem[1].m_stItemInfo.stStdItem.wMAC = 180;
	mUtil_xItem[1].m_stItemInfo.stStdItem.bWeight = 1;
	sprintf( mUtil_xItem[1].m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(4821));

	mUtil_nSettedItemCount = 2;
}

VOID CUtilWnd::SetMenuItemToMPItem()
{
	// 마력회복약(소)
	mUtil_xItem[0].m_stItemInfo.stStdItem.bShape = 0;
	mUtil_xItem[0].m_stItemInfo.stStdItem.wLooks = 15;
	mUtil_xItem[0].m_stItemInfo.stStdItem.wAC = 0;
	mUtil_xItem[0].m_stItemInfo.stStdItem.wMAC = 40;
	mUtil_xItem[0].m_stItemInfo.stStdItem.bWeight = 1;
	sprintf( mUtil_xItem[0].m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(4822));

	// 마력회복약(중)
	mUtil_xItem[1].m_stItemInfo.stStdItem.bShape = 0;
	mUtil_xItem[1].m_stItemInfo.stStdItem.wLooks = 16;
	mUtil_xItem[1].m_stItemInfo.stStdItem.wAC = 0;
	mUtil_xItem[1].m_stItemInfo.stStdItem.wMAC = 110;
	mUtil_xItem[1].m_stItemInfo.stStdItem.bWeight = 1;
	sprintf( mUtil_xItem[1].m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(4823));

	// 마력회복약(대)
	mUtil_xItem[2].m_stItemInfo.stStdItem.bShape = 0;
	mUtil_xItem[2].m_stItemInfo.stStdItem.wLooks = 17;
	mUtil_xItem[2].m_stItemInfo.stStdItem.wAC = 0;
	mUtil_xItem[2].m_stItemInfo.stStdItem.wMAC = 180;
	mUtil_xItem[2].m_stItemInfo.stStdItem.bWeight = 2;
	sprintf( mUtil_xItem[2].m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(4824));

	// 마력회복약(특)
	mUtil_xItem[3].m_stItemInfo.stStdItem.bShape = 0;
	mUtil_xItem[3].m_stItemInfo.stStdItem.wLooks = 18;
	mUtil_xItem[3].m_stItemInfo.stStdItem.wAC = 0;
	mUtil_xItem[3].m_stItemInfo.stStdItem.wMAC = 250;
	mUtil_xItem[3].m_stItemInfo.stStdItem.bWeight = 3;
	sprintf( mUtil_xItem[3].m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(4825));

	mUtil_nSettedItemCount = 4;
}

VOID CUtilWnd::SetMenuItemToScrollItem()
{
	// 아공도약서
	mUtil_xItem[0].m_stItemInfo.stStdItem.bShape = 2;
	mUtil_xItem[0].m_stItemInfo.stStdItem.wLooks = 205;
	mUtil_xItem[0].m_stItemInfo.stStdItem.bWeight = 1;
	mUtil_xItem[0].m_stItemInfo.stStdItem.wAC = 0;
	mUtil_xItem[0].m_stItemInfo.stStdItem.wMAC = 0;
	sprintf( mUtil_xItem[0].m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(4826));

	// 초공전서
	mUtil_xItem[1].m_stItemInfo.stStdItem.bShape = 3;
	mUtil_xItem[1].m_stItemInfo.stStdItem.wLooks = 207;
	mUtil_xItem[1].m_stItemInfo.stStdItem.bWeight = 1;
	mUtil_xItem[1].m_stItemInfo.stStdItem.wAC = 0;
	mUtil_xItem[1].m_stItemInfo.stStdItem.wMAC = 0;
	sprintf( mUtil_xItem[1].m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(4827));

	mUtil_nSettedItemCount = 2;
}

VOID CUtilWnd::SetMenuItemToCharmItem()
{
	// 부적(소)
	mUtil_xItem[0].m_stItemInfo.stStdItem.bShape = 5;
	mUtil_xItem[0].m_stItemInfo.stStdItem.wLooks = 330;
	mUtil_xItem[0].m_stItemInfo.stStdItem.bWeight = 1;
	mUtil_xItem[0].m_stItemInfo.stStdItem.wAC = 0;
	mUtil_xItem[0].m_stItemInfo.stStdItem.wMAC = 0;
	sprintf( mUtil_xItem[0].m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(4828));

	// 부적(중)
	mUtil_xItem[1].m_stItemInfo.stStdItem.bShape = 5;
	mUtil_xItem[1].m_stItemInfo.stStdItem.wLooks = 330;
	mUtil_xItem[1].m_stItemInfo.stStdItem.bWeight = 3;
	mUtil_xItem[1].m_stItemInfo.stStdItem.wAC = 0;
	mUtil_xItem[1].m_stItemInfo.stStdItem.wMAC = 0;
	sprintf( mUtil_xItem[1].m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(4829));

	// 신성의 부적(소)
	mUtil_xItem[2].m_stItemInfo.stStdItem.bShape = 7;
	mUtil_xItem[2].m_stItemInfo.stStdItem.wLooks = 330;
	mUtil_xItem[2].m_stItemInfo.stStdItem.bWeight = 1;
	mUtil_xItem[2].m_stItemInfo.stStdItem.wAC = 0;
	mUtil_xItem[2].m_stItemInfo.stStdItem.wMAC = 0;
	sprintf( mUtil_xItem[2].m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(4830));

	// 부적(화)
	mUtil_xItem[3].m_stItemInfo.stStdItem.bShape = 5;
	mUtil_xItem[3].m_stItemInfo.stStdItem.wLooks = 330;
	mUtil_xItem[3].m_stItemInfo.stStdItem.bWeight = 1;
	mUtil_xItem[3].m_stItemInfo.stStdItem.wAC = 0;
	mUtil_xItem[3].m_stItemInfo.stStdItem.wMAC = 0;
	sprintf( mUtil_xItem[3].m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(4831));

	// 부적(빙)
	mUtil_xItem[4].m_stItemInfo.stStdItem.bShape = 5;
	mUtil_xItem[4].m_stItemInfo.stStdItem.wLooks = 330;
	mUtil_xItem[4].m_stItemInfo.stStdItem.bWeight = 1;
	mUtil_xItem[4].m_stItemInfo.stStdItem.wAC = 0;
	mUtil_xItem[4].m_stItemInfo.stStdItem.wMAC = 0;
	sprintf( mUtil_xItem[4].m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(4832));

	// 부적(뢰)
	mUtil_xItem[5].m_stItemInfo.stStdItem.bShape = 5;
	mUtil_xItem[5].m_stItemInfo.stStdItem.wLooks = 330;
	mUtil_xItem[5].m_stItemInfo.stStdItem.bWeight = 1;
	mUtil_xItem[5].m_stItemInfo.stStdItem.wAC = 0;
	mUtil_xItem[5].m_stItemInfo.stStdItem.wMAC = 0;
	sprintf( mUtil_xItem[5].m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(4833));

	// 부적(풍)
	mUtil_xItem[6].m_stItemInfo.stStdItem.bShape = 5;
	mUtil_xItem[6].m_stItemInfo.stStdItem.wLooks = 330;
	mUtil_xItem[6].m_stItemInfo.stStdItem.bWeight = 1;
	mUtil_xItem[6].m_stItemInfo.stStdItem.wAC = 0;
	mUtil_xItem[6].m_stItemInfo.stStdItem.wMAC = 0;
	sprintf( mUtil_xItem[6].m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(4834));

	mUtil_nSettedItemCount = 7;
}

VOID CUtilWnd::SetMenuItemToPoisonItem()
{
	// 회색독가루(소)
	mUtil_xItem[0].m_stItemInfo.stStdItem.bShape = 1;
	mUtil_xItem[0].m_stItemInfo.stStdItem.wLooks = 131;
	mUtil_xItem[0].m_stItemInfo.stStdItem.bWeight = 1;
	mUtil_xItem[0].m_stItemInfo.stStdItem.wAC = 0;
	mUtil_xItem[0].m_stItemInfo.stStdItem.wMAC = 0;
	sprintf( mUtil_xItem[0].m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(4835));

	// 회색독가루(중)
	mUtil_xItem[1].m_stItemInfo.stStdItem.bShape = 1;
	mUtil_xItem[1].m_stItemInfo.stStdItem.wLooks = 131;
	mUtil_xItem[1].m_stItemInfo.stStdItem.bWeight = 2;
	mUtil_xItem[1].m_stItemInfo.stStdItem.wAC = 0;
	mUtil_xItem[1].m_stItemInfo.stStdItem.wMAC = 0;
	sprintf( mUtil_xItem[1].m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(4836));

	// 황색독가루(소)
	mUtil_xItem[2].m_stItemInfo.stStdItem.bShape = 2;
	mUtil_xItem[2].m_stItemInfo.stStdItem.wLooks = 130;
	mUtil_xItem[2].m_stItemInfo.stStdItem.bWeight = 1;
	mUtil_xItem[2].m_stItemInfo.stStdItem.wAC = 0;
	mUtil_xItem[2].m_stItemInfo.stStdItem.wMAC = 0;
	sprintf( mUtil_xItem[2].m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(4837));

	// 황색독가루(중)
	mUtil_xItem[3].m_stItemInfo.stStdItem.bShape = 2;
	mUtil_xItem[3].m_stItemInfo.stStdItem.wLooks = 130;
	mUtil_xItem[3].m_stItemInfo.stStdItem.bWeight = 3;
	mUtil_xItem[3].m_stItemInfo.stStdItem.wAC = 0;
	mUtil_xItem[3].m_stItemInfo.stStdItem.wMAC = 0;
	sprintf( mUtil_xItem[3].m_stItemInfo.stStdItem.szName, g_xMsg.GetMsg(4838));

	mUtil_nSettedItemCount = 4;
}

VOID CUtilWnd::ShowMenuItemState()
{
	if ( mUtil_bMode == _SET_ITEM_MODE )
	{
		for ( INT nI=0; nI<10; nI++ )
		{
			if ( PtInRect(&mUtil_rcItem[nI], g_xGameProc.m_ptMousePos) )
			{
				if ( mUtil_xUtilItemInfo[nI].xItem.m_stItemInfo.stStdItem.wLooks != 0 )
				{
					mUtil_xUtilItemInfo[nI].xItem.ShowItemStatus(mUtil_rcItem[nI].left + 30, mUtil_rcItem[nI].top + 30);
				}
			}
		}
	}
	else
	{
		for ( INT nI=0; nI<4; nI++ )
		{
			if ( PtInRect(&mUtil_rcItem[nI], g_xGameProc.m_ptMousePos) )
			{
				if ( mUtil_xUtilItemInfo2[nI].xItem.m_stItemInfo.stStdItem.wLooks != 0 )
				{
					mUtil_xUtilItemInfo2[nI].xItem.ShowItemStatus(mUtil_rcItem[nI].left + 30, mUtil_rcItem[nI].top + 30);
				}
			}
		}

	}

	if ( mUtil_nSettedItemCount > 0 )
	{
		RECT	rcItem[4];
		for ( INT nI=0; nI<mUtil_nSettedItemCount; nI++ )
		{
			if ( PtInRect(&mUtil_rcMenu[nI], g_xGameProc.m_ptMousePos) )
			{
				mUtil_xItem[nI].ShowItemStatus(mUtil_rcMenu[nI].left + 40, mUtil_rcMenu[nI].top + 40);
			}
		}
	}
}


VOID CUtilWnd::SetMenuRect()
{
	if ( mUtil_nKindofSettedItem == 1 || mUtil_nKindofSettedItem == 2 || mUtil_nKindofSettedItem == 3
		|| mUtil_nKindofSettedItem == 4 || mUtil_nKindofSettedItem == 5 ) // 왼쪽
	{
		mUtil_rcMenu[0].left = m_rcWnd.left + 125;
		mUtil_rcMenu[0].right = mUtil_rcMenu[0].left + 38;
		mUtil_rcMenu[0].top = m_rcWnd.top + 100 + 43 * (mUtil_nKindofSettedItem - 1);
		mUtil_rcMenu[0].bottom = mUtil_rcMenu[0].top + 38;

		mUtil_rcMenu[1].left = m_rcWnd.left + 125 + 38;
		mUtil_rcMenu[1].right = mUtil_rcMenu[1].left + 38;
		mUtil_rcMenu[1].top = mUtil_rcMenu[0].top;
		mUtil_rcMenu[1].bottom = mUtil_rcMenu[0].bottom;

		mUtil_rcMenu[2].left = m_rcWnd.left + 125 + 38*2;
		mUtil_rcMenu[2].right = mUtil_rcMenu[2].left + 38;
		mUtil_rcMenu[2].top = mUtil_rcMenu[0].top;
		mUtil_rcMenu[2].bottom = mUtil_rcMenu[0].bottom;

		mUtil_rcMenu[3].left = m_rcWnd.left + 125 + 38*3;
		mUtil_rcMenu[3].right = mUtil_rcMenu[3].left + 38;
		mUtil_rcMenu[3].top = mUtil_rcMenu[0].top;
		mUtil_rcMenu[3].bottom = mUtil_rcMenu[0].bottom;

	}
	else if ( mUtil_nKindofSettedItem == 6 || mUtil_nKindofSettedItem == 7 || mUtil_nKindofSettedItem == 8
			 || mUtil_nKindofSettedItem == 9 || mUtil_nKindofSettedItem == 10 ) // 오른쪽
	{
		mUtil_rcMenu[0].left = m_rcWnd.left + 395;
		mUtil_rcMenu[0].right = mUtil_rcMenu[0].left + 38;
		mUtil_rcMenu[0].top = m_rcWnd.top + 100 + 43 * ( mUtil_nKindofSettedItem - 6 ); 
		mUtil_rcMenu[0].bottom = mUtil_rcMenu[0].top + 38;

		mUtil_rcMenu[1].left = m_rcWnd.left + 395 + 38;
		mUtil_rcMenu[1].right = mUtil_rcMenu[1].left + 38;
		mUtil_rcMenu[1].top = mUtil_rcMenu[0].top;
		mUtil_rcMenu[1].bottom = mUtil_rcMenu[0].bottom;

		mUtil_rcMenu[2].left = m_rcWnd.left + 395 + 38 * 2;
		mUtil_rcMenu[2].right = mUtil_rcMenu[2].left + 38;
		mUtil_rcMenu[2].top = mUtil_rcMenu[0].top;
		mUtil_rcMenu[2].bottom = mUtil_rcMenu[0].bottom;

		mUtil_rcMenu[3].left = m_rcWnd.left + 395 + 38 * 3;
		mUtil_rcMenu[3].right = mUtil_rcMenu[3].left + 38;
		mUtil_rcMenu[3].top = mUtil_rcMenu[0].top;
		mUtil_rcMenu[3].bottom = mUtil_rcMenu[0].bottom;
	}
	else if ( mUtil_nKindofSettedItem == 11 || mUtil_nKindofSettedItem == 12 )
	{
		mUtil_rcMenu[0].left = m_rcWnd.left + 128;
		mUtil_rcMenu[0].right = mUtil_rcMenu[0].left + 38;
		mUtil_rcMenu[0].top = m_rcWnd.top + 90 + 52 * ( mUtil_nKindofSettedItem - 11 ); 
		mUtil_rcMenu[0].bottom = mUtil_rcMenu[0].top + 38;

		mUtil_rcMenu[1].left = m_rcWnd.left + 128 + 38;
		mUtil_rcMenu[1].right = mUtil_rcMenu[1].left + 38;
		mUtil_rcMenu[1].top = mUtil_rcMenu[0].top;
		mUtil_rcMenu[1].bottom = mUtil_rcMenu[0].bottom;

		mUtil_rcMenu[2].left = m_rcWnd.left + 128 + 38 * 2;
		mUtil_rcMenu[2].right = mUtil_rcMenu[2].left + 38;
		mUtil_rcMenu[2].top = mUtil_rcMenu[0].top;
		mUtil_rcMenu[2].bottom = mUtil_rcMenu[0].bottom;

		mUtil_rcMenu[3].left = m_rcWnd.left + 128 + 38 * 3;
		mUtil_rcMenu[3].right = mUtil_rcMenu[3].left + 38;
		mUtil_rcMenu[3].top = mUtil_rcMenu[0].top;
		mUtil_rcMenu[3].bottom = mUtil_rcMenu[0].bottom;

		mUtil_rcMenu[4].left = m_rcWnd.left + 128 + 38 * 4;
		mUtil_rcMenu[4].right = mUtil_rcMenu[4].left + 38;
		mUtil_rcMenu[4].top = mUtil_rcMenu[0].top;
		mUtil_rcMenu[4].bottom = mUtil_rcMenu[0].bottom;

		mUtil_rcMenu[5].left = m_rcWnd.left + 128 + 38 * 5;
		mUtil_rcMenu[5].right = mUtil_rcMenu[5].left + 38;
		mUtil_rcMenu[5].top = mUtil_rcMenu[0].top;
		mUtil_rcMenu[5].bottom = mUtil_rcMenu[0].bottom;

		mUtil_rcMenu[6].left = m_rcWnd.left + 128 + 38 * 6;
		mUtil_rcMenu[6].right = mUtil_rcMenu[6].left + 38;
		mUtil_rcMenu[6].top = mUtil_rcMenu[0].top;
		mUtil_rcMenu[6].bottom = mUtil_rcMenu[0].bottom;
	}
	else if ( mUtil_nKindofSettedItem == 13 || mUtil_nKindofSettedItem == 14 )
	{
		mUtil_rcMenu[0].left = m_rcWnd.left + 128;
		mUtil_rcMenu[0].right = mUtil_rcMenu[0].left + 38;
		mUtil_rcMenu[0].top = m_rcWnd.top + 194 + 52 * ( mUtil_nKindofSettedItem - 13 ); 
		mUtil_rcMenu[0].bottom = mUtil_rcMenu[0].top + 38;

		mUtil_rcMenu[1].left = m_rcWnd.left + 128 + 38;
		mUtil_rcMenu[1].right = mUtil_rcMenu[1].left + 38;
		mUtil_rcMenu[1].top = mUtil_rcMenu[0].top;
		mUtil_rcMenu[1].bottom = mUtil_rcMenu[0].bottom;

		mUtil_rcMenu[2].left = m_rcWnd.left + 128 + 38 * 2;
		mUtil_rcMenu[2].right = mUtil_rcMenu[2].left + 38;
		mUtil_rcMenu[2].top = mUtil_rcMenu[0].top;
		mUtil_rcMenu[2].bottom = mUtil_rcMenu[0].bottom;

		mUtil_rcMenu[3].left = m_rcWnd.left + 128 + 38 * 3;
		mUtil_rcMenu[3].right = mUtil_rcMenu[3].left + 38;
		mUtil_rcMenu[3].top = mUtil_rcMenu[0].top;
		mUtil_rcMenu[3].bottom = mUtil_rcMenu[0].bottom;
	}
}


VOID CUtilWnd::ProcessUtilFunc()
{
	DWORD dwCurTime = timeGetTime();

	if ( dwCurTime - mUtil_dwItemUseTimer > 2000 )
	{
		mUtil_dwItemUseTimer = dwCurTime;
		for ( INT nI=0; nI<10; nI++ )
		{
			for (INT nJ=0; nJ<10; nJ++ )
			{
				if ( mUtil_xUtilItemInfo[nJ].nPriority == nI+1 )
				{
					if ( mUtil_xUtilItemInfo[nJ].bCheck )
					{
						// 마력 검사
						if ( nJ == 5 || nJ == 6 || nJ == 7)
						{
							if ( g_xGameProc.m_xMyHero.m_stAbility.wMP < mUtil_xUtilItemInfo[nJ].nValue && mUtil_xUtilItemInfo[nJ].xItem.m_stItemInfo.stStdItem.wLooks != 0 )
							{
								// 아이템사용
								for ( INT nCnt = 0; nCnt < _MAX_INVEN_ITEM; nCnt++ )
								{
									if ( g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nCnt].bSetted )
									{
										if ( mUtil_xUtilItemInfo[nJ].xItem.m_stItemInfo.stStdItem.wLooks == g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nCnt].xItem.m_stItemInfo.stStdItem.wLooks)
										{
											if ( !g_xGameProc.m_xInterface.m_stCommonItem.bSetted )
											{
												g_xGameProc.m_xInterface.m_stCommonItem.bSetted = TRUE;
												g_xGameProc.m_xInterface.m_stCommonItem.xItem = g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nCnt].xItem;
												g_xGameProc.m_xInterface.m_stCommonItem.bWaitResponse		= TRUE;
												g_xGameProc.m_xInterface.m_stCommonItem.bIsEquipItem		= FALSE;
												g_xGameProc.m_xInterface.m_stCommonItem.bIsDealItem		= FALSE;
												g_xGameProc.m_xInterface.m_stCommonItem.bIsHideItem		= TRUE;
												g_xGameProc.m_xInterface.m_stCommonItem.bIsBeltItem		= FALSE;
												g_xGameProc.m_xInterface.m_stCommonItem.bIsUtilItem 	= TRUE;

												g_xClientSocket.SendItemIndex(CM_EAT, g_xGameProc.m_xInterface.m_stCommonItem.xItem.m_stItemInfo.nMakeIndex, g_xGameProc.m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName);
												mUtil_dwItemUseTimer = dwCurTime;
											}
										}
									}
								}
							}
						}
						else			// 체력 검사
						{
							if ( g_xGameProc.m_xMyHero.m_stAbility.wHP < mUtil_xUtilItemInfo[nJ].nValue )
							{
								// 아이템사용
								for ( INT nCnt = 0; nCnt <= _MAX_INVEN_ITEM; nCnt++ )
								{
									if ( g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nCnt].bSetted )
									{
										if ( mUtil_xUtilItemInfo[nJ].xItem.m_stItemInfo.stStdItem.wLooks == g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nCnt].xItem.m_stItemInfo.stStdItem.wLooks)
										{
											if ( !g_xGameProc.m_xInterface.m_stCommonItem.bSetted )
											{
												g_xGameProc.m_xInterface.m_stCommonItem.bSetted = TRUE;
												g_xGameProc.m_xInterface.m_stCommonItem.xItem = g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nCnt].xItem;
												g_xGameProc.m_xInterface.m_stCommonItem.bWaitResponse		= TRUE;
												g_xGameProc.m_xInterface.m_stCommonItem.bIsEquipItem		= FALSE;
												g_xGameProc.m_xInterface.m_stCommonItem.bIsDealItem		= FALSE;
												g_xGameProc.m_xInterface.m_stCommonItem.bIsHideItem		= TRUE;
												g_xGameProc.m_xInterface.m_stCommonItem.bIsBeltItem		= FALSE;
												g_xGameProc.m_xInterface.m_stCommonItem.bIsUtilItem 	= TRUE;

												g_xClientSocket.SendItemIndex(CM_EAT, g_xGameProc.m_xInterface.m_stCommonItem.xItem.m_stItemInfo.nMakeIndex, g_xGameProc.m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.szName);

												if ( nJ == 9 ) // 전서 시리즈
													mUtil_xUtilItemInfo[nJ].bCheck = FALSE;
												mUtil_dwItemUseTimer = dwCurTime;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	if ( dwCurTime - mUtil_dwMagicUseTimer > 2000 )
	{
		mUtil_dwMagicUseTimer = dwCurTime;

		// 마법 사용
		for ( INT nI=0; nI<10; nI++ )
		{
			for ( INT nJ=0; nJ<10; nJ++ )
			{
				if ( mUtil_xUtilMagicInfo[nJ].nPriority == nI+1 )
				{
					if ( mUtil_xUtilMagicInfo[nJ].bCheck )
					{
						CActor*					pxActor = NULL;
						CListNode < CActor >	*pNodeActor;
						BOOL					bFindTarget = FALSE;
						INT						nTargetId = 0;
						FEATURE					stTargetFeature;
						WORD					wTargetHP = 0;
						BYTE					bTargetDir = 0;
						POINT					ptTarget;

						if ( strcmp(mUtil_xUtilMagicInfo[nJ].szName, g_xGameProc.m_xMyHero.m_szName) == 0 )
						{
							stTargetFeature = g_xGameProc.m_xMyHero.m_stFeature;
							nTargetId = g_xGameProc.m_xMyHero.m_nIdentity;
							wTargetHP = g_xGameProc.m_xMyHero.m_wHP;
							bTargetDir = g_xGameProc.m_xMyHero.m_pxMap->GetNextDirection(g_xGameProc.m_xMyHero.m_nPosX, g_xGameProc.m_xMyHero.m_nPosY, g_xGameProc.m_xMyHero.m_nPosX, g_xGameProc.m_xMyHero.m_nPosY);
							ptTarget.x = g_xGameProc.m_xMyHero.m_nPosX;
							ptTarget.y = g_xGameProc.m_xMyHero.m_nPosY;
							bFindTarget = TRUE;
						}
						else
						{
							for ( pNodeActor = g_xGameProc.m_xActorList.GetHead(); pNodeActor; pNodeActor = pNodeActor->GetNext() )
							{
								pxActor = pNodeActor->GetData();

								if ( pxActor )
								{
									if ( strcmp( pxActor->m_szName, mUtil_xUtilMagicInfo[nJ].szName ) == 0 )
									{
										stTargetFeature = pxActor->m_stFeature;
										nTargetId = pxActor->m_nIdentity;
										wTargetHP = pxActor->m_wHP;
										bTargetDir = g_xGameProc.m_xMyHero.m_pxMap->GetNextDirection(g_xGameProc.m_xMyHero.m_nPosX, g_xGameProc.m_xMyHero.m_nPosY, pxActor->m_nPosX, pxActor->m_nPosY);
										ptTarget.x = pxActor->m_nPosX;
										ptTarget.y = pxActor->m_nPosY;
										bFindTarget = TRUE;
										break;
									}
								}
							}
						}

						if ( wTargetHP < mUtil_xUtilMagicInfo[nJ].nValue && bFindTarget)
						{
							// 마법 사용

							LPCLIENTMAGICRCD pstMagicRCD = NULL;
							CListNode < CLIENTMAGICRCD > *pNode;
							INT	nListCnt = 0;
							BOOL bFind = FALSE;

							for ( nListCnt = 0; nListCnt < _MAX_TYPE_MAGIC && bFind == FALSE ; nListCnt++ )
							{
								for ( pNode = g_xGameProc.m_xInterface.m_xMagicWnd.m_xMyMagicList[nListCnt].GetHead(); pNode; pNode = pNode->GetNext() )
								{
									pstMagicRCD = pNode->GetData();

									if ( pstMagicRCD )
									{
										if ( strcmp( pstMagicRCD->stStdMagic.szMagicName, g_xMsg.GetMsg(4839)) == 0 )
										{
											bFind = TRUE;
											break;
										}
									}
								}
							}
							
							if ( pstMagicRCD && bFind )
							{
								// 반월제외.
								if ( (10 + pstMagicRCD->stStdMagic.bDefSpell) <= g_xGameProc.m_xMyHero.m_stAbility.wMP || pstMagicRCD->stStdMagic.wMagicID == _SKILL_BANWOL || pstMagic->stStdMagic.wMagicID == _SKILL_MANWOL )
								{
									g_xGameProc.m_xMyHero.m_nCurrMagicID = pstMagicRCD->stStdMagic.wMagicID;
									g_xGameProc.m_xMyHero.SetMagic(pstMagicRCD, bTargetDir, nTargetId, stTargetFeature, ptTarget);
								}
							}
						}
					}
				}
			}
		}
	}
}

BOOL CUtilWnd::SaveUtilSet()
{
	HANDLE	hFile;
	CHAR	szItemFile[MAX_PATH];

	ZeroMemory(szItemFile, MAX_PATH);
	g_xMainWnd.StringPlus(szItemFile, ".\\Data\\", g_xGameProc.m_xMyHero.m_szName, ".uts", "");
	hFile = CreateFile(szItemFile, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if ( hFile != INVALID_HANDLE_VALUE )
	{
		DWORD		dwWriteLen;

		WriteFile(hFile, mUtil_xUtilItemInfo, sizeof(CLIENTUTILITEMINFO)*10, &dwWriteLen, NULL);
		WriteFile(hFile, mUtil_xUtilItemInfo2, sizeof(CLIENTUTILITEMINFO)*4, &dwWriteLen, NULL);
		WriteFile(hFile, mUtil_xUtilMagicInfo, sizeof(CLIENTUTILMAGICINFO)*10, &dwWriteLen, NULL);

		CloseHandle(hFile);
		return TRUE;
	}
	return FALSE;
}


BOOL CUtilWnd::LoadUtilSet()
{
	HANDLE	hFile;
	CHAR	szItemFile[MAX_PATH];

	ZeroMemory(szItemFile, MAX_PATH);
	g_xMainWnd.StringPlus(szItemFile, ".\\Data\\", g_xGameProc.m_xMyHero.m_szName, ".uts", "");
	hFile = CreateFile(szItemFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if ( hFile != INVALID_HANDLE_VALUE )
	{
		DWORD		dwReadLen;

		ReadFile(hFile, &mUtil_xUtilItemInfo, sizeof(CLIENTUTILITEMINFO)*10, &dwReadLen, NULL);
		ReadFile(hFile, &mUtil_xUtilItemInfo2, sizeof(CLIENTUTILITEMINFO)*4, &dwReadLen, NULL);
		ReadFile(hFile, &mUtil_xUtilMagicInfo, sizeof(CLIENTUTILMAGICINFO)*10, &dwReadLen, NULL);

		CloseHandle(hFile);
		return TRUE;
	}
	return FALSE;
}


VOID CUtilWnd::SetKey(BYTE bKey)
{
	RECT rc, rcMagic;
	INT  nCnt, nLine, nAtoI, nListCnt;
	BYTE bKeyNum;
	LPCLIENTMAGICRCD pstMagicRCD = NULL;
	CListNode < CLIENTMAGICRCD > *pNode;

	for ( nCnt = 0; nCnt < 4; nCnt++ )
	{
		if ( PtInRect(&mUtil_rcPriority2[nCnt], g_xGameProc.m_ptMousePos) )
		{
			// 현재 눌려져 있는 키가 쓰인가 체크.
			for ( nListCnt = 0; nListCnt < _MAX_TYPE_MAGIC; nListCnt++ )
			{
				for ( pNode = g_xGameProc.m_xInterface.m_xMagicWnd.m_xMyMagicList[nListCnt].GetHead(); pNode; pNode = pNode->GetNext() )
				{
					pstMagicRCD = pNode->GetData();

					if ( pstMagicRCD )
					{
						nAtoI = atoi((char*)&(pstMagicRCD->bUseKey));

						if ( nAtoI < 10 && nAtoI > 0 )
						{
							bKeyNum = (BYTE)nAtoI;
						}
						else
						{
							bKeyNum = (BYTE)(pstMagicRCD->bUseKey- 55);
						}

						if ( pstMagicRCD->bUseKey == bKey )
						{
							pstMagicRCD->bUseKey = 0;

							if ( bKeyNum > 0 && bKeyNum <= _MAGIC_MAX_KEY )
							{
								g_xGameProc.m_xInterface.m_xMagicWnd.m_bMagicKeyTable[bKeyNum-1] = 0;
							}

							g_xClientSocket.SendMagicKeyChange(pstMagicRCD->bUseKey, pstMagicRCD->stStdMagic.wMagicID);
						}
					}
				}
			}

			CheckKey(bKey);

			// 키 셋팅
			mUtil_xUtilItemInfo2[nCnt].nPriority = bKey;
		}
	}
}


VOID CUtilWnd::CheckKey(BYTE bKey)
{
	for ( INT nCnt=0; nCnt<4; nCnt++ )
	{
		if ( mUtil_xUtilItemInfo2[nCnt].nPriority == bKey )
			mUtil_xUtilItemInfo2[nCnt].nPriority = 0;
	}
}

BOOL CUtilWnd::UseKey(BYTE bKey)
{
	DWORD dwCurTime = timeGetTime();
	if ( dwCurTime - mUtil_dwItemTakeonTimer > 2000 )
	{
		for ( INT nCnt=0; nCnt<4; nCnt++ )
		{
			if ( mUtil_xUtilItemInfo2[nCnt].nPriority == bKey )
			{
				for ( INT nCnt2 = 0; nCnt2 <= _MAX_INVEN_ITEM; nCnt2++ )
				{
					if ( g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nCnt2].bSetted )
					{
						if ( mUtil_xUtilItemInfo2[nCnt].xItem.m_stItemInfo.stStdItem.wLooks == g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nCnt2].xItem.m_stItemInfo.stStdItem.wLooks )
						{
							if ( !g_xGameProc.m_xInterface.m_stCommonItem.bSetted )
							{

								INT nMakeIdx = g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nCnt2].xItem.m_stItemInfo.nMakeIndex;
								CHAR szItemName[MAX_PATH];
								sprintf( szItemName, g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nCnt2].xItem.m_stItemInfo.stStdItem.szName);
								
								g_xGameProc.m_xInterface.m_xStatusWnd.m_stTakeOnItemSet.xItem	  = g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nCnt2].xItem;
								g_xGameProc.m_xInterface.m_xStatusWnd.m_stTakeOnItemSet.bSetted = TRUE;
								g_xGameProc.m_xInterface.m_xStatusWnd.m_stTakeOnItemSet.xItem.m_shCellNum = _U_CHARM;
								g_xGameProc.m_xInterface.m_xInventoryWnd.DeleteInvenItem(nMakeIdx, szItemName);

								g_xGameProc.m_xInterface.m_xStatusWnd.SetCommonFromEquip(_U_CHARM, &g_xGameProc.m_xInterface.m_stCommonItem);
								g_xGameProc.m_xInterface.m_stCommonItem.bIsHideItem = TRUE;

								g_xClientSocket.SendTakeOnOffItem(CM_TAKEONITEM, _U_CHARM, szItemName, nMakeIdx);
								mUtil_dwItemTakeonTimer = dwCurTime;
								return TRUE;
							}
						}
					}
				}
			}
		}
	}

	return FALSE;
}
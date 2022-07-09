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

	mUtil_BtnDownofHP.Init();
	mUtil_BtnDownofMP.Init();
	mUtil_BtnDownofScroll.Init();

	mUtil_BtnItemMode.Init();
	mUtil_BtnMagicMode.Init();
	mUtil_BtnEtcMode.Init();

	mUtil_BtnClose.Init();

	mUtil_nSettedItemCount = 0;
	mUtil_nKindofSettedItem = 0;

	mUtil_nFocusedValue = 0;

	mUtil_dwItemUseTimer = 0;
	mUtil_dwMagicUseTimer = 0;
	mUtil_dwItemTakeonTimer = 0;
	mUtil_dwScrollUseTimer = 0;

	mUtil_nPageInCharm = 0;

	mUtil_bGrayPotion = FALSE;

	ZeroMemory(mUtil_xUtilItemInfo, sizeof(CLIENTUTILITEMINFO)*10);
	ZeroMemory(mUtil_xUtilItemInfo2, sizeof(CLIENTUTILITEMINFO)*4);
	ZeroMemory(mUtil_xUtilMagicInfo, sizeof(CLIENTUTILMAGICINFO)*10);

	ZeroMemory(mUtil_szHPpotion, 16);
	ZeroMemory(mUtil_szScroll, 16);
	ZeroMemory(mUtil_szMPpotion, 16);

	for (INT nI=0; nI<10; nI++ )
	{
		SetRect(&mUtil_rcCheck[nI], 0, 0, 0, 0);
		SetRect(&mUtil_rcItem[nI], 0, 0, 0, 0);
		SetRect(&mUtil_rcValue[nI], 0, 0, 0, 0);
		SetRect(&mUtil_rcPriority[nI], 0, 0, 0, 0);
		SetRect(&mUtil_rcName[nI], 0, 0, 0, 0);
	}

	for ( nI=0; nI<20; nI++ )
	{
		mUtil_BtnDownofMagicKind[nI].Init();
		mUtil_BtnDownofCharmSize[nI].Init();
		mUtil_BtnDownofCharmKind[nI].Init();
	}

	for ( nI=0; nI<4; nI++ )
	{
		SetRect(&mUtil_rcMenu[nI], 0, 0, 0, 0);
	}

	mUtil_BtnChangeWeather.Init();
	mUtil_bShowSysTime = FALSE;

	mUtil_nSeletedMenu = 0;

	mUtil_bShowHumanHP = 0;
}

VOID CUtilWnd::Destroy()
{
	CGameWnd::Destroy();
}

VOID CUtilWnd::CreateUtilWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend)
{
	CreateGameWnd(nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight, bBlend);

	mUtil_BtnClose.CreateGameBtn(pxWndImage, 1221, 1222, nStartX+526, nStartY+326, g_xMsg.GetMsg(1052), _BTN_TYPE_FOCUS, 1221, TRUE);
	mUtil_BtnItemMode.CreateGameBtn(pxWndImage, 807, 807, nStartX+64, nStartY+321, g_xMsg.GetMsg(4806), _BTN_TYPE_FOCUS, -1, FALSE);
	mUtil_BtnMagicMode.CreateGameBtn(pxWndImage, 808, 808, nStartX+144, nStartY+321, g_xMsg.GetMsg(4807), _BTN_TYPE_FOCUS, -1, FALSE);

	pxWndImage = &(g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1]);

	mUtil_BtnDownofHP.CreateGameBtn(pxWndImage, 4, 5, nStartX+526, nStartY+326, "", _BTN_TYPE_FOCUS, 4, TRUE);
	mUtil_BtnDownofScroll.CreateGameBtn(pxWndImage, 4, 5, nStartX+526, nStartY+326, "", _BTN_TYPE_FOCUS, 4, TRUE);
	mUtil_BtnDownofMP.CreateGameBtn(pxWndImage, 4, 5, nStartX+526, nStartY+326, "", _BTN_TYPE_FOCUS, 4, TRUE);

	for ( INT nI=0; nI<20; nI++ )
	{
		mUtil_BtnDownofMagicKind[nI].CreateGameBtn(pxWndImage, 7, 7, nStartX+128, nStartY+99, g_xMsg.GetMsg(4804), _BTN_TYPE_FOCUS, -1, FALSE);
		mUtil_BtnDownofCharmSize[nI].CreateGameBtn(pxWndImage, 7, 7, nStartX+128, nStartY+99, g_xMsg.GetMsg(4804), _BTN_TYPE_FOCUS, -1, FALSE);
		mUtil_BtnDownofCharmKind[nI].CreateGameBtn(pxWndImage, 7, 7, nStartX+128, nStartY+99, g_xMsg.GetMsg(4804), _BTN_TYPE_FOCUS, -1, FALSE);
	}

	mUtil_BtnEtcMode.CreateGameBtn(pxWndImage, 12, 13, nStartX+224, nStartY+321, g_xMsg.GetMsg(4881), _BTN_TYPE_FOCUS, 12, FALSE);

	mUtil_BtnLeftfCharm.CreateGameBtn(pxWndImage, 8, 9, nStartX+128, nStartY+152, "", _BTN_TYPE_FOCUS, 8, FALSE);
	mUtil_BtnRightCharm.CreateGameBtn(pxWndImage, 10, 11, nStartX+128, nStartY+152, "", _BTN_TYPE_FOCUS, 10, FALSE);

	mUtil_BtnChangeWeather.CreateGameBtn(pxWndImage, 18, 19, nStartX+144, nStartY+321, g_xMsg.GetMsg(4807), _BTN_TYPE_FOCUS, 18, FALSE);

	SetRect(&mUtil_rcHPValue, m_rcWnd.left+65, m_rcWnd.top+58, m_rcWnd.left+140, m_rcWnd.top+73);
	SetRect(&mUtil_rcScrollValue, m_rcWnd.left+65, m_rcWnd.top+93, m_rcWnd.left+140, m_rcWnd.top+108);
	SetRect(&mUtil_rcMPValue, m_rcWnd.left+65, m_rcWnd.top+128, m_rcWnd.left+140, m_rcWnd.top+143);

	for ( nI=0; nI<40; nI++ )
	{
		sprintf(mUtil_szCharmName[nI], g_xMsg.GetMsg(4864));
		sprintf(mUtil_szCharmKind[nI], g_xMsg.GetMsg(4858));
		sprintf(mUtil_szMagicName[nI], g_xMsg.GetMsg(4864));
	}

}	
		
VOID CUtilWnd::ShowUtilWnd()
{
	mUtil_BtnClose.ChangeRect(m_rcWnd.left+518, m_rcWnd.top+343);
	
	mUtil_BtnItemMode.ChangeRect(m_rcWnd.left+67, m_rcWnd.top+342);
	mUtil_BtnMagicMode.ChangeRect(m_rcWnd.left+147, m_rcWnd.top+342);
	mUtil_BtnEtcMode.ChangeRect(m_rcWnd.left+228, m_rcWnd.top+342);

	ShowGameWnd();

	mUtil_BtnClose.ShowGameBtn();

	if ( mUtil_bMode == _SET_ITEM_MODE )
	{
		ShowItemSetMode();
	}
	else if ( mUtil_bMode == _SET_MAGIC_MODE )
	{
		ShowMagicSetMode();
	}
	else if ( mUtil_bMode == _SET_ETC_MODE )
	{
		ShowEtcSetMode();
	}
	
	mUtil_BtnEtcMode.ShowGameBtn();
	mUtil_BtnMagicMode.ShowGameBtn();
	mUtil_BtnItemMode.ShowGameBtn();
}


VOID CUtilWnd::ShowItemSetMode()
{
	mUtil_BtnDownofHP.ChangeRect(m_rcWnd.left+254, m_rcWnd.top+57);
	mUtil_BtnDownofScroll.ChangeRect(m_rcWnd.left+254, m_rcWnd.top+92);
	mUtil_BtnDownofMP.ChangeRect(m_rcWnd.left+254, m_rcWnd.top+127);
	// 바탕
	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(830) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left-230, m_rcWnd.top-68, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
	}

	// 바탕
	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].NewSetIndex(0) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+10, m_rcWnd.top+40, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_pbCurrImage);
	}


	RECT rcTitle = { m_rcWnd.left + 50, m_rcWnd.top + 9, m_rcWnd.left + 200, m_rcWnd.top + 24 };
	g_xMainWnd.PutsHan(NULL, rcTitle, RGB(230, 230, 0), RGB(0, 0, 0), g_xMsg.GetMsg(4843));

	RECT rcText;

	// 왼쪽 물약 부분

	// 체력회복약
	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].NewSetIndex(1) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+30, m_rcWnd.top+55, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_pbCurrImage);
	}

	rcText.left = m_rcWnd.left+33;
	rcText.right = m_rcWnd.left+56;
	rcText.top = m_rcWnd.top+58;
	rcText.bottom = rcText.top+15;
	g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 255, 255), RGB(0, 0, 0), "HP");


	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].NewSetIndex(2) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+65, m_rcWnd.top+55, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_pbCurrImage);
	}

	CHAR szTemp[16];

	sprintf(szTemp, "%d", mUtil_nHPValue);

	rcText.left = m_rcWnd.left+65;
	rcText.right = m_rcWnd.left+140;
	rcText.top = m_rcWnd.top+58;
	rcText.bottom = rcText.top+15;
	g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 255, 255), RGB(0, 0, 0), szTemp);

	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].NewSetIndex(3) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+155, m_rcWnd.top+55, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_pbCurrImage);
	}

	rcText.left = m_rcWnd.left+155;
	rcText.right = m_rcWnd.left+250;
	rcText.top = m_rcWnd.top+58;
	rcText.bottom = rcText.top+15;
	g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 255, 255), RGB(0, 0, 0), mUtil_szHPpotion);


	// 전서
	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].NewSetIndex(1) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+30, m_rcWnd.top+90, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_pbCurrImage);
	}

	rcText.left = m_rcWnd.left+33;
	rcText.right = m_rcWnd.left+56;
	rcText.top = m_rcWnd.top+93;
	rcText.bottom = rcText.top+15;	
	g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 255, 255), RGB(0, 0, 0), g_xMsg.GetMsg(4882));


	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].NewSetIndex(2) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+65, m_rcWnd.top+90, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_pbCurrImage);
	}

	sprintf(szTemp, "%d", mUtil_nScrollValue);

	rcText.left = m_rcWnd.left+65;
	rcText.right = m_rcWnd.left+140;
	rcText.top = m_rcWnd.top+93;
	rcText.bottom = rcText.top+15;
	g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 255, 255), RGB(0, 0, 0), szTemp);

	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].NewSetIndex(3) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+155, m_rcWnd.top+90, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_pbCurrImage);
	}

	rcText.left = m_rcWnd.left+155;
	rcText.right = m_rcWnd.left+250;
	rcText.top = m_rcWnd.top+93;
	rcText.bottom = rcText.top+15;
	g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 255, 255), RGB(0, 0, 0), mUtil_szScroll);

	// 마약
	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].NewSetIndex(1) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+30, m_rcWnd.top+125, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_pbCurrImage);
	}

	rcText.left = m_rcWnd.left+33;
	rcText.right = m_rcWnd.left+56;
	rcText.top = m_rcWnd.top+128;
	rcText.bottom = rcText.top+15;	
	g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 255, 255), RGB(0, 0, 0), "MP");


	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].NewSetIndex(2) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+65, m_rcWnd.top+125, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_pbCurrImage);
	}

	sprintf(szTemp, "%d", mUtil_nMPValue);

	rcText.left = m_rcWnd.left+65;
	rcText.right = m_rcWnd.left+140;
	rcText.top = m_rcWnd.top+128;
	rcText.bottom = rcText.top+15;
	g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 255, 255), RGB(0, 0, 0), szTemp);

	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].NewSetIndex(3) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+155, m_rcWnd.top+125, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_pbCurrImage);
	}

	rcText.left = m_rcWnd.left+155;
	rcText.right = m_rcWnd.left+250;
	rcText.top = m_rcWnd.top+128;
	rcText.bottom = rcText.top+15;
	g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 255, 255), RGB(0, 0, 0), mUtil_szMPpotion);

	// 오른쪽 힐 부분
	rcText.left = m_rcWnd.left+294;
	rcText.right = m_rcWnd.left+348;
	rcText.top = m_rcWnd.top+52;
	rcText.bottom = rcText.top+15;
	g_xMainWnd.PutsHan(NULL, rcText, RGB(0, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(4808));
	
	rcText.left = m_rcWnd.left+349;
	rcText.right = m_rcWnd.left+432;
	g_xMainWnd.PutsHan(NULL, rcText, RGB(0, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(4840));
	
	rcText.left = m_rcWnd.left+433;
	rcText.right = m_rcWnd.left+490;
	g_xMainWnd.PutsHan(NULL, rcText, RGB(0, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(4810));
	
	rcText.left = m_rcWnd.left+490;
	rcText.right = m_rcWnd.left+547;
	g_xMainWnd.PutsHan(NULL, rcText, RGB(0, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(4811));

	for ( INT nI=0; nI<10; nI++ )
	{
		SetRect(&mUtil_rcCheck[nI], m_rcWnd.left+308, m_rcWnd.top+75 + nI * 25, m_rcWnd.left+333, m_rcWnd.top+93 + nI * 25);
		SetRect(&mUtil_rcValue[nI], m_rcWnd.left+446, m_rcWnd.top+75 + nI * 25, m_rcWnd.left+480, m_rcWnd.top+93 + nI * 25);
		SetRect(&mUtil_rcPriority[nI], m_rcWnd.left+507, m_rcWnd.top+75 + nI * 25, m_rcWnd.left+530, m_rcWnd.top+93 + nI * 25);
		SetRect(&mUtil_rcName[nI], m_rcWnd.left+348, m_rcWnd.top+75 + nI * 25, m_rcWnd.left+434, m_rcWnd.top+93 + nI * 25);		
	}
/*
	for ( nI=0; nI<4; nI++ )
	{
		SetRect(&mUtil_rcCheck2[nI], m_rcWnd.left+37, m_rcWnd.top+89 + nI * 49, m_rcWnd.left+61, m_rcWnd.top+107 + nI * 49);
		SetRect(&mUtil_rcItem[nI], m_rcWnd.left+85, m_rcWnd.top+80 + nI * 49, m_rcWnd.left+127, m_rcWnd.top+107 + nI * 49);
		SetRect(&mUtil_rcPriority2[nI], m_rcWnd.left+160, m_rcWnd.top+89 + nI * 49, m_rcWnd.left+195, m_rcWnd.top+106 + nI * 49);
	}
*/
/*	// 탭 활성화 그림
	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(808) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+148, m_rcWnd.top+342, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
	}
*/
	// 마법 
	for ( nI=0; nI<10; nI++ )
	{
		// 활성화 그리기
		if ( mUtil_xUtilMagicInfo[nI].bCheck )
		{
			if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(806))
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
			if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(809+mUtil_xUtilMagicInfo[nI].nPriority))
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

	// 메뉴 그리기
	if ( mUtil_nSeletedMenu != 0 )
	{
		INT nWidth = 0, nHeight = 0, nStartX = 0, nStartY = 0, nI = 0;
		switch(mUtil_nSeletedMenu)
		{
			case _HPSET:
			{
				for ( nI = 0; nI<mUtil_nMenuCount; nI++ )
				{
					D3DMATERIAL7 mtrl;
					D3DVECTOR	 vecTrans((FLOAT)mUtil_rcMenu[nI].left, (FLOAT)mUtil_rcMenu[nI].top, 0);
					D3DVECTOR	 vecScale((FLOAT)mUtil_rcMenu[nI].right-mUtil_rcMenu[nI].left, 
						mUtil_rcMenu[nI].bottom-mUtil_rcMenu[nI].top, 1);

					D3DUtil_InitMaterial(mtrl, (FLOAT)100/255.0f, (FLOAT)100/255.0f, (FLOAT)100/255.0f);
					mtrl.diffuse.a = 230.0f/255.0f;
					g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

					g_xMainWnd.DrawWithGDI(&mUtil_rcMenu[nI], NULL, RGB(130, 130, 130), 1);

					if ( PtInRect(&mUtil_rcMenu[nI], g_xGameProc.m_ptMousePos) )
					{
						D3DMATERIAL7 mtrl;
						D3DVECTOR	 vecTrans((FLOAT)mUtil_rcMenu[nI].left, (FLOAT)mUtil_rcMenu[nI].top, 0);
						D3DVECTOR	 vecScale((FLOAT)mUtil_rcMenu[nI].right-mUtil_rcMenu[nI].left, 
							mUtil_rcMenu[nI].bottom-mUtil_rcMenu[nI].top, 1);

						D3DUtil_InitMaterial(mtrl, (FLOAT)120/255.0f, (FLOAT)120/255.0f, (FLOAT)120/255.0f);
						mtrl.diffuse.a = 230.0f/255.0f;
						g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

						g_xMainWnd.DrawWithGDI(&mUtil_rcMenu[nI], NULL, RGB(200, 200, 200), 1);
					}

					g_xMainWnd.PutsHan(NULL, mUtil_rcMenu[nI], RGB(255, 255, 0), RGB(0, 0, 0), g_xMsg.GetMsg(6050+nI));
				}
				break;
			}
			case _SCROLLSET:
			{
				for ( nI = 0; nI<mUtil_nMenuCount; nI++ )
				{
					D3DMATERIAL7 mtrl;
					D3DVECTOR	 vecTrans((FLOAT)mUtil_rcMenu[nI].left, (FLOAT)mUtil_rcMenu[nI].top, 0);
					D3DVECTOR	 vecScale((FLOAT)mUtil_rcMenu[nI].right-mUtil_rcMenu[nI].left, 
						mUtil_rcMenu[nI].bottom-mUtil_rcMenu[nI].top, 1);

					D3DUtil_InitMaterial(mtrl, (FLOAT)100/255.0f, (FLOAT)100/255.0f, (FLOAT)100/255.0f);
					mtrl.diffuse.a = 230.0f/255.0f;
					g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

					g_xMainWnd.DrawWithGDI(&mUtil_rcMenu[nI], NULL, RGB(130, 130, 130), 1);

					if ( PtInRect(&mUtil_rcMenu[nI], g_xGameProc.m_ptMousePos) )
					{
						D3DMATERIAL7 mtrl;
						D3DVECTOR	 vecTrans((FLOAT)mUtil_rcMenu[nI].left, (FLOAT)mUtil_rcMenu[nI].top, 0);
						D3DVECTOR	 vecScale((FLOAT)mUtil_rcMenu[nI].right-mUtil_rcMenu[nI].left, 
							mUtil_rcMenu[nI].bottom-mUtil_rcMenu[nI].top, 1);

						D3DUtil_InitMaterial(mtrl, (FLOAT)120/255.0f, (FLOAT)120/255.0f, (FLOAT)120/255.0f);
						mtrl.diffuse.a = 230.0f/255.0f;
						g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

						g_xMainWnd.DrawWithGDI(&mUtil_rcMenu[nI], NULL, RGB(200, 200, 200), 1);
					}

					g_xMainWnd.PutsHan(NULL, mUtil_rcMenu[nI], RGB(255, 255, 0), RGB(0, 0, 0), g_xMsg.GetMsg(6060+nI));
				}
				break;
			}
			case _MPSET:
			{
				for ( nI = 0; nI<mUtil_nMenuCount; nI++ )
				{
					D3DMATERIAL7 mtrl;
					D3DVECTOR	 vecTrans((FLOAT)mUtil_rcMenu[nI].left, (FLOAT)mUtil_rcMenu[nI].top, 0);
					D3DVECTOR	 vecScale((FLOAT)mUtil_rcMenu[nI].right-mUtil_rcMenu[nI].left, 
						mUtil_rcMenu[nI].bottom-mUtil_rcMenu[nI].top, 1);

					D3DUtil_InitMaterial(mtrl, (FLOAT)100/255.0f, (FLOAT)100/255.0f, (FLOAT)100/255.0f);
					mtrl.diffuse.a = 230.0f/255.0f;
					g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

					g_xMainWnd.DrawWithGDI(&mUtil_rcMenu[nI], NULL, RGB(130, 130, 130), 1);

					if ( PtInRect(&mUtil_rcMenu[nI], g_xGameProc.m_ptMousePos) )
					{
						D3DMATERIAL7 mtrl;
						D3DVECTOR	 vecTrans((FLOAT)mUtil_rcMenu[nI].left, (FLOAT)mUtil_rcMenu[nI].top, 0);
						D3DVECTOR	 vecScale((FLOAT)mUtil_rcMenu[nI].right-mUtil_rcMenu[nI].left, 
							mUtil_rcMenu[nI].bottom-mUtil_rcMenu[nI].top, 1);

						D3DUtil_InitMaterial(mtrl, (FLOAT)120/255.0f, (FLOAT)120/255.0f, (FLOAT)120/255.0f);
						mtrl.diffuse.a = 230.0f/255.0f;
						g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

						g_xMainWnd.DrawWithGDI(&mUtil_rcMenu[nI], NULL, RGB(200, 200, 200), 1);
					}

					g_xMainWnd.PutsHan(NULL, mUtil_rcMenu[nI], RGB(255, 255, 0), RGB(0, 0, 0), g_xMsg.GetMsg(6070+nI));
				}
				break;
			}
		}
	}			


	mUtil_BtnDownofHP.ShowGameBtn();
	mUtil_BtnDownofMP.ShowGameBtn();
	mUtil_BtnDownofScroll.ShowGameBtn();
}


VOID CUtilWnd::ShowMagicSetMode()
{
	for ( INT nI=0; nI<10; nI++ )
	{
		mUtil_BtnDownofMagicKind[nI].ChangeRect(m_rcWnd.left+117, m_rcWnd.top+83+24*nI);		
		mUtil_BtnDownofCharmKind[nI].ChangeRect(m_rcWnd.left+229, m_rcWnd.top+83+24*nI);
		mUtil_BtnDownofCharmSize[nI].ChangeRect(m_rcWnd.left+264, m_rcWnd.top+83+24*nI);
	}

	for ( nI=10; nI<20; nI++ )
	{
		mUtil_BtnDownofMagicKind[nI].ChangeRect(m_rcWnd.left+391, m_rcWnd.top+83+24*(nI-10));
		mUtil_BtnDownofCharmKind[nI].ChangeRect(m_rcWnd.left+503, m_rcWnd.top+83+24*(nI-10));
		mUtil_BtnDownofCharmSize[nI].ChangeRect(m_rcWnd.left+539, m_rcWnd.top+83+24*(nI-10));
	}

	mUtil_BtnLeftfCharm.ChangeRect(m_rcWnd.left+380, m_rcWnd.top+341);
	mUtil_BtnRightCharm.ChangeRect(m_rcWnd.left+430, m_rcWnd.top+341);

	// 바탕
	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].NewSetIndex(6) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+10, m_rcWnd.top+40, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_pbCurrImage);
	}

	// 오른쪽바탕
	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].NewSetIndex(6) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+284, m_rcWnd.top+40, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_pbCurrImage);
	}

	RECT rcTitle = { m_rcWnd.left + 50, m_rcWnd.top + 9, m_rcWnd.left + 200, m_rcWnd.top + 24 };
	CHAR szTitle[MAX_PATH];
	sprintf( szTitle, "%s ( %d / 2 )", g_xMsg.GetMsg(4844), mUtil_nPageInCharm+1 );
	g_xMainWnd.PutsHan(NULL, rcTitle, RGB(230, 230, 0), RGB(0, 0, 0), szTitle);

	RECT rcText;

	rcText.top = m_rcWnd.top+52;
	rcText.bottom = rcText.top+15;
//	g_xMainWnd.PutsHan(NULL, rcText, RGB(0, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(4808));

	// 왼쪽 부적 부분
	rcText.left = m_rcWnd.left+20;
	rcText.right = m_rcWnd.left+113;
	g_xMainWnd.PutsHan(NULL, rcText, RGB(0, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(4883));
	
	rcText.left = m_rcWnd.left+130;
	rcText.right = m_rcWnd.left+225;
	g_xMainWnd.PutsHan(NULL, rcText, RGB(0, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(4884));
	
	rcText.left = m_rcWnd.left+241;
	rcText.right = m_rcWnd.left+271;
	g_xMainWnd.PutsHan(NULL, rcText, RGB(0, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(4885));


	// 오른쪽 부적 부분
	rcText.left = m_rcWnd.left+293;
	rcText.right = m_rcWnd.left+386;
	g_xMainWnd.PutsHan(NULL, rcText, RGB(0, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(4883));
	
	rcText.left = m_rcWnd.left+404;
	rcText.right = m_rcWnd.left+500;
	g_xMainWnd.PutsHan(NULL, rcText, RGB(0, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(4884));
	
	rcText.left = m_rcWnd.left+514;
	rcText.right = m_rcWnd.left+546;
	g_xMainWnd.PutsHan(NULL, rcText, RGB(0, 200, 200), RGB(0, 0, 0), g_xMsg.GetMsg(4885));
/*
	// 탭 활성화 그림
	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(808) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+148, m_rcWnd.top+342, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
	}
*/
/*
	CListNode < CLIENTMAGICRCD > *pNode;
	LPCLIENTMAGICRCD pstMagicRCD = NULL;

	RECT rcMagicName = {m_rcWnd.left+18, m_rcWnd.top+81, m_rcWnd.left+114, m_rcWnd.top+96};
	CHAR szTemp[MAX_PATH];
	INT nMax = 0, nStart = mUtil_nPageInCharm * 10;

	for ( INT nCnt = 0; nCnt < _MAX_TYPE_MAGIC && nMax < 10 * (mUtil_nPageInCharm + 1); nCnt++ )
	{
		for ( pNode = g_xGameProc.m_xInterface.m_xMagicWnd.m_xMyMagicList[nCnt].GetHead(); pNode && nMax < 10 * (mUtil_nPageInCharm + 1); pNode = pNode->GetNext() )
		{
			nMax++;
			if ( nMax <= nStart )
				continue;

			pstMagicRCD = pNode->GetData();

			if ( pstMagicRCD )
			{
				sprintf(szTemp, "%s", pstMagicRCD ->stStdMagic.szMagicName);
				g_xMainWnd.PutsHan(NULL, rcMagicName, RGB(255, 255, 255), RGB(0, 0, 0), szTemp);
				rcMagicName.top += 24;
				rcMagicName.bottom += 24;
			}
		}
	}
*/

	// 무공이름 그리기 
	RECT rcMagicName = {m_rcWnd.left+18, m_rcWnd.top+81, m_rcWnd.left+114, m_rcWnd.top+96};

	for ( nI=0; nI<10; nI++ )
	{
		g_xMainWnd.PutsHan(NULL, rcMagicName, RGB(255, 255, 255), RGB(0, 0, 0), mUtil_szMagicName[nI+mUtil_nPageInCharm*20]);
		rcMagicName.top += 24;
		rcMagicName.bottom += 24;
	}

	rcMagicName.top = m_rcWnd.top+81;
	rcMagicName.bottom = m_rcWnd.top+96;

	rcMagicName.left = m_rcWnd.left + 292;
	rcMagicName.right = m_rcWnd.left + 388;

	for ( nI=10; nI<20; nI++ )
	{
		g_xMainWnd.PutsHan(NULL, rcMagicName, RGB(255, 255, 255), RGB(0, 0, 0), mUtil_szMagicName[nI+mUtil_nPageInCharm*20]);
		rcMagicName.top += 24;
		rcMagicName.bottom += 24;
	}


	// 부적이름,종류 그리기 
	RECT rcCharmName = {m_rcWnd.left+132, m_rcWnd.top+81, m_rcWnd.left+224, m_rcWnd.top+96};
	RECT rcCharmSize = {m_rcWnd.left+242, m_rcWnd.top+81, m_rcWnd.left+260, m_rcWnd.top+96};

	for ( INT nCnt = mUtil_nPageInCharm * 20; nCnt < mUtil_nPageInCharm * 20 + 10; nCnt++ )
	{
		g_xMainWnd.PutsHan(NULL, rcCharmName, RGB(255, 255, 255), RGB(0, 0, 0), mUtil_szCharmName[nCnt]);
		g_xMainWnd.PutsHan(NULL, rcCharmSize, RGB(255, 255, 255), RGB(0, 0, 0), mUtil_szCharmKind[nCnt]);

		rcCharmName.top += 24;
		rcCharmName.bottom += 24;

		rcCharmSize.top += 24;
		rcCharmSize.bottom += 24;
	}

	rcCharmName.top =  m_rcWnd.top + 81;
	rcCharmName.bottom =  m_rcWnd.top + 96;
	rcCharmName.left = m_rcWnd.left + 406;
	rcCharmName.right = m_rcWnd.left + 498;

	rcCharmSize.top =  m_rcWnd.top + 81;
	rcCharmSize.bottom =  m_rcWnd.top + 96;
	rcCharmSize.left = m_rcWnd.left + 516;
	rcCharmSize.right = m_rcWnd.left + 534;
	
	for ( nCnt = mUtil_nPageInCharm * 20 + 10; nCnt < mUtil_nPageInCharm * 20 + 20; nCnt++ )
	{
		g_xMainWnd.PutsHan(NULL, rcCharmName, RGB(255, 255, 255), RGB(0, 0, 0), mUtil_szCharmName[nCnt]);
		g_xMainWnd.PutsHan(NULL, rcCharmSize, RGB(255, 255, 255), RGB(0, 0, 0), mUtil_szCharmKind[nCnt]);

		rcCharmName.top += 24;
		rcCharmName.bottom += 24;

		rcCharmSize.top += 24;
		rcCharmSize.bottom += 24;
	}

/*
	// 선택메뉴 그리기
	if ( mUtil_nSeletedMenu > 0 )
	{
		if ( mUtil_rcMenu[0].left < 50 )
			int ntest = 0;

		INT		nWidth = 0;
		INT		nHeight = 0;
		INT		nStartX = m_rcWnd.left + 128;
		INT		nStartY = 0;
		INT		nMsgStartIdx = 0, nMsgMaxIdx = 0;
		INT		nI = 0, nIMax = 0;

		if ( mUtil_nSeletedMenu >= 24 && mUtil_nSeletedMenu <= 34 )
		{
			nStartY = m_rcWnd.top + 82 + 24 * (mUtil_nSeletedMenu - 23);
			nStartX = m_rcWnd.left + 119;
			nWidth = 93;
			nHeight = 165;
			nMsgStartIdx = 6000;
			nMsgMaxIdx = 6010;
			nIMax = 11;
		}
		else if ( mUtil_nSeletedMenu >= 11 && mUtil_nSeletedMenu <= 20 )
		{
			nStartY = m_rcWnd.top + 82 + 24 * (mUtil_nSeletedMenu - 11);
			nStartX = m_rcWnd.left + 236;
			nWidth = 20;
			nHeight = 60;
			nMsgStartIdx = 4858;
			nMsgMaxIdx = 4862;
			nIMax = 5;
		}

		D3DVECTOR	 vecTrans((FLOAT)(nStartX), (FLOAT)(nStartY), 0);
		D3DVECTOR	 vecScale((FLOAT)(nWidth), (FLOAT)(nHeight), 1);
		D3DMATERIAL7 mtrl;

		D3DUtil_InitMaterial(mtrl, (FLOAT)70/255.0f, (FLOAT)70/255.0f, (FLOAT)70/255.0f);
		mtrl.diffuse.a = 220.0f/255.0f;
		g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

		// 마우스뒷판
		for ( nI = 0; nI< nIMax; nI++ )
		{
			if ( PtInRect(&mUtil_rcMenu[nI], g_xGameProc.m_ptMousePos) )
			{
				D3DMATERIAL7 mtrl;
				D3DVECTOR	 vecTrans((FLOAT)mUtil_rcMenu[nI].left, (FLOAT)mUtil_rcMenu[nI].top, 0);
				D3DVECTOR	 vecScale((FLOAT)mUtil_rcMenu[nI].right-mUtil_rcMenu[nI].left, 
					mUtil_rcMenu[nI].bottom-mUtil_rcMenu[nI].top, 1);

				D3DUtil_InitMaterial(mtrl, (FLOAT)100/255.0f, (FLOAT)100/255.0f, (FLOAT)100/255.0f);
				mtrl.diffuse.a = 180.0f/255.0f;
				g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

				g_xMainWnd.DrawWithGDI(&mUtil_rcMenu[nI], NULL, RGB(200, 200, 200), 1);
			}
		}

		// 메뉴 아이템
		RECT rcText = { nStartX, nStartY, nStartX + nWidth, nStartY + 15 };
		for ( INT nCnt = nMsgStartIdx; nCnt < nMsgMaxIdx; nCnt++ )
		{
			g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 255, 0), RGB(0, 0, 0), g_xMsg.GetMsg(nCnt));
			rcText.top += 15;
			rcText.bottom += 15;
		}
	}
*/
	//부적크기
	if ( mUtil_nSeletedMenu >= 44 && mUtil_nSeletedMenu <= 63 )
	{
		for ( INT nI=0; nI<4; nI++ )
		{
			D3DVECTOR	 vecTrans((FLOAT)(mUtil_rcMenu[nI].left), (FLOAT)(mUtil_rcMenu[nI].top), 0);
			D3DVECTOR	 vecScale((FLOAT)(mUtil_rcMenu[nI].right-mUtil_rcMenu[nI].left), (FLOAT)(mUtil_rcMenu[nI].bottom-mUtil_rcMenu[nI].top), 1);
			D3DMATERIAL7 mtrl;

			D3DUtil_InitMaterial(mtrl, (FLOAT)70/255.0f, (FLOAT)70/255.0f, (FLOAT)70/255.0f);
			mtrl.diffuse.a = 220.0f/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
			g_xMainWnd.PutsHan(NULL, mUtil_rcMenu[nI], RGB(230, 230, 0), RGB(0, 0, 0), g_xMsg.GetMsg(4858+nI));
		}

		// 마우스뒷판
		for ( nI = 0; nI< 4; nI++ )
		{
			if ( PtInRect(&mUtil_rcMenu[nI], g_xGameProc.m_ptMousePos) )
			{
				D3DMATERIAL7 mtrl;
				D3DVECTOR	 vecTrans((FLOAT)mUtil_rcMenu[nI].left, (FLOAT)mUtil_rcMenu[nI].top, 0);
				D3DVECTOR	 vecScale((FLOAT)mUtil_rcMenu[nI].right-mUtil_rcMenu[nI].left, 
					mUtil_rcMenu[nI].bottom-mUtil_rcMenu[nI].top, 1);

				D3DUtil_InitMaterial(mtrl, (FLOAT)100/255.0f, (FLOAT)100/255.0f, (FLOAT)100/255.0f);
				mtrl.diffuse.a = 180.0f/255.0f;
				g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

				g_xMainWnd.DrawWithGDI(&mUtil_rcMenu[nI], NULL, RGB(200, 200, 200), 1);
				g_xMainWnd.PutsHan(NULL, mUtil_rcMenu[nI], RGB(230, 230, 0), RGB(0, 0, 0), g_xMsg.GetMsg(4858+nI));
			}
		}
	}

	//부적이름
	if ( mUtil_nSeletedMenu >= 24 && mUtil_nSeletedMenu <= 43 )
	{
		for ( INT nI=0; nI<11; nI++ )
		{
			D3DVECTOR	 vecTrans((FLOAT)(mUtil_rcMenu[nI].left), (FLOAT)(mUtil_rcMenu[nI].top), 0);
			D3DVECTOR	 vecScale((FLOAT)(mUtil_rcMenu[nI].right-mUtil_rcMenu[nI].left), (FLOAT)(mUtil_rcMenu[nI].bottom-mUtil_rcMenu[nI].top), 1);
			D3DMATERIAL7 mtrl;

			D3DUtil_InitMaterial(mtrl, (FLOAT)70/255.0f, (FLOAT)70/255.0f, (FLOAT)70/255.0f);
			mtrl.diffuse.a = 220.0f/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
			g_xMainWnd.PutsHan(NULL, mUtil_rcMenu[nI], RGB(230, 230, 0), RGB(0, 0, 0), g_xMsg.GetMsg(6000+nI));
		}

		// 마우스뒷판
		for ( nI = 0; nI< 11; nI++ )
		{
			if ( PtInRect(&mUtil_rcMenu[nI], g_xGameProc.m_ptMousePos) )
			{
				D3DMATERIAL7 mtrl;
				D3DVECTOR	 vecTrans((FLOAT)mUtil_rcMenu[nI].left, (FLOAT)mUtil_rcMenu[nI].top, 0);
				D3DVECTOR	 vecScale((FLOAT)mUtil_rcMenu[nI].right-mUtil_rcMenu[nI].left, 
					mUtil_rcMenu[nI].bottom-mUtil_rcMenu[nI].top, 1);

				D3DUtil_InitMaterial(mtrl, (FLOAT)100/255.0f, (FLOAT)100/255.0f, (FLOAT)100/255.0f);
				mtrl.diffuse.a = 180.0f/255.0f;
				g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

				g_xMainWnd.DrawWithGDI(&mUtil_rcMenu[nI], NULL, RGB(200, 200, 200), 1);
				g_xMainWnd.PutsHan(NULL, mUtil_rcMenu[nI], RGB(230, 230, 0), RGB(0, 0, 0), g_xMsg.GetMsg(6000+nI));
			}
		}
	}

	//무공이름
	if ( mUtil_nSeletedMenu >= 4 && mUtil_nSeletedMenu <= 23 )
	{
		for ( INT nI=0; nI<26; nI++ )
		{
			D3DVECTOR	 vecTrans((FLOAT)(mUtil_rcMenu[nI].left), (FLOAT)(mUtil_rcMenu[nI].top), 0);
			D3DVECTOR	 vecScale((FLOAT)(mUtil_rcMenu[nI].right-mUtil_rcMenu[nI].left), (FLOAT)(mUtil_rcMenu[nI].bottom-mUtil_rcMenu[nI].top), 1);
			D3DMATERIAL7 mtrl;

			D3DUtil_InitMaterial(mtrl, (FLOAT)70/255.0f, (FLOAT)70/255.0f, (FLOAT)70/255.0f);
			mtrl.diffuse.a = 220.0f/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
			g_xMainWnd.PutsHan(NULL, mUtil_rcMenu[nI], RGB(230, 230, 0), RGB(0, 0, 0), g_xMsg.GetMsg(6080+nI));
		}

		// 마우스뒷판
		for ( nI = 0; nI< 26; nI++ )
		{
			if ( PtInRect(&mUtil_rcMenu[nI], g_xGameProc.m_ptMousePos) )
			{
				D3DMATERIAL7 mtrl;
				D3DVECTOR	 vecTrans((FLOAT)mUtil_rcMenu[nI].left, (FLOAT)mUtil_rcMenu[nI].top, 0);
				D3DVECTOR	 vecScale((FLOAT)mUtil_rcMenu[nI].right-mUtil_rcMenu[nI].left, 
					mUtil_rcMenu[nI].bottom-mUtil_rcMenu[nI].top, 1);

				D3DUtil_InitMaterial(mtrl, (FLOAT)100/255.0f, (FLOAT)100/255.0f, (FLOAT)100/255.0f);
				mtrl.diffuse.a = 180.0f/255.0f;
				g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

				g_xMainWnd.DrawWithGDI(&mUtil_rcMenu[nI], NULL, RGB(200, 200, 200), 1);
				g_xMainWnd.PutsHan(NULL, mUtil_rcMenu[nI], RGB(230, 230, 0), RGB(0, 0, 0), g_xMsg.GetMsg(6080+nI));
			}
		}
	}

	for ( nI=0; nI<20; nI++ )
	{
		mUtil_BtnDownofMagicKind[nI].ShowGameBtn();
		mUtil_BtnDownofCharmSize[nI].ShowGameBtn();
		mUtil_BtnDownofCharmKind[nI].ShowGameBtn();
	}

	mUtil_BtnRightCharm.ShowGameBtn();
	mUtil_BtnLeftfCharm.ShowGameBtn();
	
}


VOID CUtilWnd::ShowEtcSetMode()
{
	mUtil_BtnChangeWeather.ChangeRect(m_rcWnd.left+124, m_rcWnd.top+55);

	// 바탕
	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].NewSetIndex(17) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+10, m_rcWnd.top+40, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_pbCurrImage);
	}

	// 시스템 시간 표시
	CHAR szMenu[MAX_PATH];

	RECT rcTitle = { m_rcWnd.left + 50, m_rcWnd.top + 9, m_rcWnd.left + 200, m_rcWnd.top + 24 };
	g_xMainWnd.PutsHan(NULL, rcTitle, RGB(230, 230, 0), RGB(0, 0, 0), g_xMsg.GetMsg(4886));

	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].NewSetIndex(14) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+18, m_rcWnd.top+55, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_pbCurrImage);
	}

	rcTitle.left = m_rcWnd.left+18;
	rcTitle.right = m_rcWnd.left+114;
	rcTitle.top = m_rcWnd.top+58;
	rcTitle.bottom = rcTitle.top+15;

	sprintf( szMenu, "%s", g_xMsg.GetMsg(4865+g_xGameProc.m_bFogState));
	g_xMainWnd.PutsHan(NULL, rcTitle, RGB(255, 255, 255), RGB(0, 0, 0), szMenu);

	
	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].NewSetIndex(14) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+18, m_rcWnd.top+85, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_pbCurrImage);
	}

	rcTitle.top = m_rcWnd.top+88;
	rcTitle.bottom = rcTitle.top+15;
	g_xMainWnd.PutsHan(NULL, rcTitle, RGB(255, 255, 255), RGB(0, 0, 0), g_xMsg.GetMsg(4869));

	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].NewSetIndex(15+mUtil_bShowSysTime) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+135, m_rcWnd.top+85, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_pbCurrImage);
	}
	
	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].NewSetIndex(14) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+18, m_rcWnd.top+115, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_pbCurrImage);
	}

	rcTitle.top = m_rcWnd.top+118;
	rcTitle.bottom = rcTitle.top+15;
	g_xMainWnd.PutsHan(NULL, rcTitle, RGB(255, 255, 255), RGB(0, 0, 0), g_xMsg.GetMsg(4880));

	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].NewSetIndex(15+mUtil_bShowMagicTime) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+135, m_rcWnd.top+115, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_pbCurrImage);
	}


	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].NewSetIndex(14) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+18, m_rcWnd.top+145, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_pbCurrImage);
	}

	rcTitle.top = m_rcWnd.top+148;
	rcTitle.bottom = rcTitle.top+15;
	g_xMainWnd.PutsHan(NULL, rcTitle, RGB(255, 255, 255), RGB(0, 0, 0), g_xMsg.GetMsg(4889));

	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].NewSetIndex(15+mUtil_bShowHumanHP) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+135, m_rcWnd.top+145, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_pbCurrImage);
	}

	

	SetRect(&mUtil_rchowSysTime, m_rcWnd.left+136, m_rcWnd.top+88, m_rcWnd.left+160, m_rcWnd.top+106);	
	SetRect(&mUtil_rcMagicTime, m_rcWnd.left+136, m_rcWnd.top+118, m_rcWnd.left+160, m_rcWnd.top+136);	
	SetRect(&mUtil_rcShowHumanHP, m_rcWnd.left+136, m_rcWnd.top+148, m_rcWnd.left+160, m_rcWnd.top+166);	

	mUtil_BtnChangeWeather.ShowGameBtn();

}

BOOL CUtilWnd::OnLButtonDown(POINT ptMouse)
{
	if ( mUtil_BtnItemMode.OnLButtonDown(ptMouse) && mUtil_nSeletedMenu == -1 )
	{
		return FALSE;
	}

	if ( mUtil_BtnMagicMode.OnLButtonDown(ptMouse) )
	{
		return FALSE;
	}

	if ( mUtil_BtnEtcMode.OnLButtonDown(ptMouse) )
	{
		return FALSE;
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
	else if ( mUtil_bMode == _SET_ETC_MODE )
	{
		return LBtnDownOnEtcSetMode(ptMouse);
	}


	return FALSE;
}

BOOL CUtilWnd::LBtnDownOnItemSetMode(POINT ptMouse)
{
	if ( mUtil_BtnDownofHP.OnLButtonDown(ptMouse) )
		return FALSE;

	if ( mUtil_BtnDownofScroll.OnLButtonDown(ptMouse) )
		return FALSE;

	if ( mUtil_BtnDownofMP.OnLButtonDown(ptMouse) )
		return FALSE;

	return FALSE;
}

BOOL CUtilWnd::LBtnDownOnMagicSetMode(POINT ptMouse)
{
	for ( INT nI=0; nI<20; nI++ )
	{
		if ( mUtil_BtnDownofMagicKind[nI].OnLButtonDown(ptMouse) )
			return FALSE;

		if ( mUtil_BtnDownofCharmSize[nI].OnLButtonDown(ptMouse) )
			return FALSE;

		if ( mUtil_BtnDownofCharmKind[nI].OnLButtonDown(ptMouse) )
			return FALSE;
	}

	if ( mUtil_BtnLeftfCharm.OnLButtonDown(ptMouse) )
		return FALSE;

	if ( mUtil_BtnRightCharm.OnLButtonDown(ptMouse) )
		return FALSE;
		
	return FALSE;
}

BOOL CUtilWnd::LBtnDownOnEtcSetMode(POINT ptMouse)
{
	if ( mUtil_BtnChangeWeather.OnLButtonDown(ptMouse) )
		return FALSE;

	return FALSE;
}

BOOL CUtilWnd::OnLButtonUp(POINT ptMouse)
{
	if ( mUtil_BtnItemMode.OnLButtonUp(ptMouse) )
	{
		mUtil_bMode = _SET_ITEM_MODE;
		mUtil_nSettedItemCount = 0;
		mUtil_nKindofSettedItem = 0;
		return FALSE;
	}
		
	if ( mUtil_BtnMagicMode.OnLButtonUp(ptMouse) )
	{
		mUtil_bMode = _SET_MAGIC_MODE;
		mUtil_nSettedItemCount = 0;
		mUtil_nKindofSettedItem = 0;
		return FALSE;
	}

	if ( mUtil_BtnEtcMode.OnLButtonUp(ptMouse) )
	{
		mUtil_bMode = _SET_ETC_MODE;
		return FALSE;
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
	else if ( mUtil_bMode == _SET_ETC_MODE )
	{
		return LBtnUpOnEtcSetMode(ptMouse);
	}
	
	return FALSE;
}

BOOL CUtilWnd::LBtnUpOnItemSetMode(POINT ptMouse)
{
	if ( PtInRect(&mUtil_rcHPValue, ptMouse) )
	{
		g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_SETUTILHP, _YESNO, g_xMsg.GetMsg(4812), TRUE);
		return FALSE;
	}

	if ( PtInRect(&mUtil_rcScrollValue, ptMouse) )
	{
		g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_SETUTILSCROLL, _YESNO, g_xMsg.GetMsg(4812), TRUE);
		return FALSE;
	}

	if ( PtInRect(&mUtil_rcMPValue, ptMouse) )
	{
		g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_SETUTILMP, _YESNO, g_xMsg.GetMsg(4812), TRUE);
		return FALSE;
	}
	
	if ( mUtil_BtnDownofHP.OnLButtonUp(ptMouse) )
	{
		mUtil_nSeletedMenu = _HPSET;
		SetMenuRect();
		return FALSE;
	}

	if ( mUtil_BtnDownofScroll.OnLButtonUp(ptMouse) )
	{
		mUtil_nSeletedMenu = _SCROLLSET;
		SetMenuRect();
		return FALSE;
	}

	if ( mUtil_BtnDownofMP.OnLButtonUp(ptMouse) )
	{
		mUtil_nSeletedMenu = _MPSET;
		SetMenuRect();
		return FALSE;
	}

	// 자동힐 On/Off
	for ( INT nI=0; nI<10; nI++ )
	{
		if ( PtInRect(&mUtil_rcCheck[nI], ptMouse) )
		{
			mUtil_xUtilMagicInfo[nI].bCheck = !mUtil_xUtilMagicInfo[nI].bCheck;
			break;
		}
	}

	for ( nI=0; nI<10; nI++ )
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

	if ( mUtil_nSeletedMenu == _HPSET )
	{
		for ( INT nI=0; nI<mUtil_nMenuCount; nI++ )
		{
			if ( PtInRect(&mUtil_rcMenu[nI], g_xGameProc.m_ptMousePos) )
			{
				sprintf(mUtil_szHPpotion, g_xMsg.GetMsg(6050+nI));
				mUtil_nSeletedMenu = 0;
				return FALSE;
			}
		}
	}
	else if ( mUtil_nSeletedMenu == _SCROLLSET )
	{
		for ( INT nI=0; nI<mUtil_nMenuCount; nI++ )
		{
			if ( PtInRect(&mUtil_rcMenu[nI], g_xGameProc.m_ptMousePos) )
			{
				sprintf(mUtil_szScroll, g_xMsg.GetMsg(6060+nI));
				mUtil_nSeletedMenu = 0;
				return FALSE;
			}
		}
	}
	else if ( mUtil_nSeletedMenu == _MPSET )
	{
		for ( INT nI=0; nI<mUtil_nMenuCount; nI++ )
		{
			if ( PtInRect(&mUtil_rcMenu[nI], g_xGameProc.m_ptMousePos) )
			{
				sprintf(mUtil_szMPpotion, g_xMsg.GetMsg(6070+nI));
				mUtil_nSeletedMenu = 0;
				return FALSE;
			}
		}
	}

	mUtil_nSeletedMenu = 0;

	return FALSE;
}

BOOL CUtilWnd::LBtnUpOnMagicSetMode(POINT ptMouse)
{
	for ( INT nI=0; nI<20; nI++ )
	{
		if ( mUtil_BtnDownofMagicKind[nI].OnLButtonUp(ptMouse) )
		{
			mUtil_nSeletedMenu = nI + 4;
			SetMenuRect();
			return FALSE;
		}

		if ( mUtil_BtnDownofCharmKind[nI].OnLButtonUp(ptMouse) )
		{
			mUtil_nSeletedMenu = nI + 24;
			SetMenuRect();
			return FALSE;
		}

		if ( mUtil_BtnDownofCharmSize[nI].OnLButtonUp(ptMouse) )
		{
			mUtil_nSeletedMenu = nI + 44;
			SetMenuRect();
			return FALSE;
		}
	}

	if ( mUtil_nSeletedMenu >= 4 && mUtil_nSeletedMenu <= 23 )
	{
		for ( nI=0; nI<26; nI++ )
		{
			if ( PtInRect(&mUtil_rcMenu[nI], ptMouse) )
			{
				sprintf( mUtil_szMagicName[mUtil_nSeletedMenu-4+mUtil_nPageInCharm*20], g_xMsg.GetMsg(6080+nI) );
				mUtil_nSeletedMenu = 0;
				return FALSE;
			}
		}
	}

	if ( mUtil_nSeletedMenu >= 24 && mUtil_nSeletedMenu <= 43 )
	{
		for ( nI=0; nI<11; nI++ )
		{
			if ( PtInRect(&mUtil_rcMenu[nI], ptMouse) )
			{
				sprintf( mUtil_szCharmName[mUtil_nSeletedMenu-24+mUtil_nPageInCharm*20], g_xMsg.GetMsg(6000+nI) );
				mUtil_nSeletedMenu = 0;
				return FALSE;
			}
		}
	}

	if ( mUtil_nSeletedMenu >= 44 && mUtil_nSeletedMenu <= 63 )
	{
		for ( nI=0; nI<4; nI++ )
		{
			if ( PtInRect(&mUtil_rcMenu[nI], ptMouse) )
			{
				sprintf( mUtil_szCharmKind[mUtil_nSeletedMenu-44+mUtil_nPageInCharm*20], g_xMsg.GetMsg(4858+nI) );
				mUtil_nSeletedMenu = 0;
				return FALSE;
			}
		}
	}

	mUtil_nSeletedMenu = 0;

	if ( mUtil_BtnLeftfCharm.OnLButtonUp(ptMouse) )
	{
		if ( mUtil_nPageInCharm == 1 )
			mUtil_nPageInCharm--;
		return FALSE;
	}

	if ( mUtil_BtnRightCharm.OnLButtonUp(ptMouse) )
	{
		if ( mUtil_nPageInCharm == 0 )
			mUtil_nPageInCharm++;
		return FALSE;
	}


	return FALSE;
}

BOOL CUtilWnd::LBtnUpOnEtcSetMode(POINT ptMouse)
{
	if ( mUtil_BtnChangeWeather.OnLButtonUp(ptMouse) )
	{
		DWORD dwFogColor;

		dwFogColor = 0;
		g_xGameProc.m_bFogState++;

		if ( g_xGameProc.m_bFogState > _FOGSTATE_DAWN )
			g_xGameProc.m_bFogState = _FOGSTATE_DAY;

		switch ( g_xGameProc.m_bFogState )
		{
		case _FOGSTATE_DAY:
			{
				g_xGameProc.m_fDarkRate = 255.0f;
				dwFogColor = RGB(g_xGameProc.m_fDarkRate, g_xGameProc.m_fDarkRate, g_xGameProc.m_fDarkRate);
				break;
			}
		case _FOGSTATE_NIGHT:
			{
				g_xGameProc.m_fDarkRate = 15.0f;
				dwFogColor = RGB(g_xGameProc.m_fDarkRate, g_xGameProc.m_fDarkRate, g_xGameProc.m_fDarkRate);
				break;
			}
		case _FOGSTATE_DAWN:
		case _FOGSTATE_EVENING:
			{
				g_xGameProc.m_fDarkRate = 85.0f;
				dwFogColor = RGB(g_xGameProc.m_fDarkRate, g_xGameProc.m_fDarkRate, g_xGameProc.m_fDarkRate);
				break;
			}
		}

		g_xGameProc.m_xLightFog.ChangeLightColor(dwFogColor);

		return FALSE;
	}

	if ( PtInRect(&mUtil_rchowSysTime, ptMouse) )
	{
		mUtil_bShowSysTime = !mUtil_bShowSysTime;
		g_xGameProc.m_ShowAddOn = mUtil_bShowSysTime;
		return FALSE;
	}

	if ( PtInRect(&mUtil_rcMagicTime, ptMouse) )
	{
		mUtil_bShowMagicTime = !mUtil_bShowMagicTime;
		return FALSE;
	}

	if ( PtInRect(&mUtil_rcShowHumanHP, ptMouse) )
	{
		mUtil_bShowHumanHP = !mUtil_bShowHumanHP;
		return FALSE;
	}

	return FALSE;
}


BOOL CUtilWnd::OnMouseMove(POINT ptMouse)
{
	mUtil_BtnClose.OnMouseMove(ptMouse);
	mUtil_BtnEtcMode.OnMouseMove(ptMouse);
	mUtil_BtnItemMode.OnMouseMove(ptMouse);
	mUtil_BtnMagicMode.OnMouseMove(ptMouse);

	if ( mUtil_bMode == _SET_ITEM_MODE )
	{
		return MouseMoveOnItemSetMode(ptMouse);
	}
	else if ( mUtil_bMode == _SET_MAGIC_MODE )
	{
		return MouseMoveOnMagicSetMode(ptMouse);
	}
	else if ( mUtil_bMode == _SET_ETC_MODE )
	{
		return MouseMoveOnEtcSetMode(ptMouse);
	}

	return FALSE;
}

BOOL CUtilWnd::MouseMoveOnItemSetMode(POINT ptMouse)
{
	return FALSE;
}

BOOL CUtilWnd::MouseMoveOnMagicSetMode(POINT ptMouse)
{
	for ( INT nI=0; nI<20; nI++ )
	{
		mUtil_BtnDownofMagicKind[nI].OnMouseMove(ptMouse);
		mUtil_BtnDownofCharmSize[nI].OnMouseMove(ptMouse);
		mUtil_BtnDownofCharmKind[nI].OnMouseMove(ptMouse);
	}

	mUtil_BtnLeftfCharm.OnMouseMove(ptMouse);
	mUtil_BtnRightCharm.OnMouseMove(ptMouse);

	return FALSE;
}

BOOL CUtilWnd::MouseMoveOnEtcSetMode(POINT ptMouse)
{
	mUtil_BtnChangeWeather.OnMouseMove(ptMouse);

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
		}
	}

	for (nI=0; nI<4; nI++)
	{
		if ( PtInRect(&mUtil_rcPriority2[nI], g_xGameProc.m_ptMousePos) )
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
		}
	}
	return FALSE;
}

BOOL CUtilWnd::OnSysKeyDown(WPARAM wParam, LPARAM lParam)
{
	for (INT nI=0; nI<4; nI++)
	{
		if ( PtInRect(&mUtil_rcPriority2[nI], g_xGameProc.m_ptMousePos) )
		{
			switch ( wParam )
			{
			case VK_F10:		SetKey('A');		return TRUE;
			case VK_F12:		SetKey('C');		return TRUE;
			}
		}
	}
	return FALSE;
}


VOID CUtilWnd::SetMenuItemToHPItem()
{
	mUtil_nSettedItemCount = 9;
}

VOID CUtilWnd::SetMenuItemToHPMPItem()
{

	mUtil_nSettedItemCount = 3;
}

VOID CUtilWnd::SetMenuItemToMPItem()
{
	mUtil_nSettedItemCount = 8;
}

VOID CUtilWnd::SetMenuItemToScrollItem()
{
	mUtil_nSettedItemCount = 2;
}

VOID CUtilWnd::SetMenuItemToCharmItem()
{
	mUtil_nSettedItemCount = 11;
}

VOID CUtilWnd::SetMenuItemToPoisonItem()
{
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
}


VOID CUtilWnd::SetMenuRect()
{
	if ( mUtil_nSeletedMenu == _HPSET )
	{
		mUtil_rcMenu[0].left = m_rcWnd.left + 157;
		mUtil_rcMenu[0].right = mUtil_rcMenu[0].left + 93;
		mUtil_rcMenu[0].top = m_rcWnd.top + 55;
		mUtil_rcMenu[0].bottom = mUtil_rcMenu[0].top + 15;

		mUtil_rcMenu[1].left = m_rcWnd.left + 157;
		mUtil_rcMenu[1].right = mUtil_rcMenu[1].left + 93;
		mUtil_rcMenu[1].top = mUtil_rcMenu[0].top + 15;
		mUtil_rcMenu[1].bottom = mUtil_rcMenu[0].bottom + 15;

		mUtil_rcMenu[2].left = m_rcWnd.left + 157;
		mUtil_rcMenu[2].right = mUtil_rcMenu[1].left + 93;
		mUtil_rcMenu[2].top = mUtil_rcMenu[1].top + 15;
		mUtil_rcMenu[2].bottom = mUtil_rcMenu[1].bottom + 15;

		mUtil_nMenuCount = 3;
	}
	else if ( mUtil_nSeletedMenu == _SCROLLSET )
	{
		mUtil_rcMenu[0].left = m_rcWnd.left + 157;
		mUtil_rcMenu[0].right = mUtil_rcMenu[0].left + 93;
		mUtil_rcMenu[0].top = m_rcWnd.top + 90;
		mUtil_rcMenu[0].bottom = mUtil_rcMenu[0].top + 15;

		mUtil_rcMenu[1].left = m_rcWnd.left + 157;
		mUtil_rcMenu[1].right = mUtil_rcMenu[1].left + 93;
		mUtil_rcMenu[1].top = mUtil_rcMenu[0].top + 15;
		mUtil_rcMenu[1].bottom = mUtil_rcMenu[0].bottom + 15;

		mUtil_rcMenu[2].left = m_rcWnd.left + 157;
		mUtil_rcMenu[2].right = mUtil_rcMenu[1].left + 93;
		mUtil_rcMenu[2].top = mUtil_rcMenu[1].top + 15;
		mUtil_rcMenu[2].bottom = mUtil_rcMenu[1].bottom + 15;

		mUtil_nMenuCount = 3;
	}
	else if ( mUtil_nSeletedMenu == _MPSET )
	{
		mUtil_rcMenu[0].left = m_rcWnd.left + 157;
		mUtil_rcMenu[0].right = mUtil_rcMenu[0].left + 93;
		mUtil_rcMenu[0].top = m_rcWnd.top + 126;
		mUtil_rcMenu[0].bottom = mUtil_rcMenu[0].top + 15;

		mUtil_rcMenu[1].left = m_rcWnd.left + 157;
		mUtil_rcMenu[1].right = mUtil_rcMenu[1].left + 93;
		mUtil_rcMenu[1].top = mUtil_rcMenu[0].top + 15;
		mUtil_rcMenu[1].bottom = mUtil_rcMenu[0].bottom + 15;

		mUtil_nMenuCount = 2;
	}
	else if ( mUtil_nSeletedMenu >= 4 && mUtil_nSeletedMenu <= 13 )
	{
		for ( INT nI=0; nI<26; nI++ )
		{
			mUtil_rcMenu[nI].left = m_rcWnd.left + 20;
			mUtil_rcMenu[nI].right = mUtil_rcMenu[nI].left + 90;
			mUtil_rcMenu[nI].top = m_rcWnd.top - 8 + 15*nI;
			mUtil_rcMenu[nI].bottom = mUtil_rcMenu[nI].top + 15;
		}
	}
	else if ( mUtil_nSeletedMenu >= 14 && mUtil_nSeletedMenu <= 23 )
	{
		for ( INT nI=0; nI<26; nI++ )
		{
			mUtil_rcMenu[nI].left = m_rcWnd.left + 294;
			mUtil_rcMenu[nI].right = mUtil_rcMenu[nI].left + 90;
			mUtil_rcMenu[nI].top = m_rcWnd.top - 8 + 15*nI;
			mUtil_rcMenu[nI].bottom = mUtil_rcMenu[nI].top + 15;
		}
	}
	else if ( mUtil_nSeletedMenu >= 24 && mUtil_nSeletedMenu <= 33 )		// 왼쪽 부족종류 클릭 메뉴
	{
		for ( INT nI=0; nI<11; nI++ )
		{
			mUtil_rcMenu[nI].left = m_rcWnd.left + 130;
			mUtil_rcMenu[nI].right = mUtil_rcMenu[nI].left + 95;
			mUtil_rcMenu[nI].top = m_rcWnd.top + 10 + 16*nI + 16*(mUtil_nSeletedMenu-24);
			mUtil_rcMenu[nI].bottom = mUtil_rcMenu[nI].top + 15;
		}
	}
	else if ( mUtil_nSeletedMenu >= 34 && mUtil_nSeletedMenu <= 43 )		// 오른쪽 부족종류 클릭 메뉴
	{
		for ( INT nI=0; nI<10; nI++ )
		{
			mUtil_rcMenu[nI].left = m_rcWnd.left + 404;
			mUtil_rcMenu[nI].right = mUtil_rcMenu[nI].left + 95;
			mUtil_rcMenu[nI].top = m_rcWnd.top + 10 + 16*nI + 16*(mUtil_nSeletedMenu-34);
			mUtil_rcMenu[nI].bottom = mUtil_rcMenu[nI].top + 15;
		}
	}
	else if ( mUtil_nSeletedMenu >= 44 && mUtil_nSeletedMenu <= 53 )		// 왼쪽 부족종류 클릭 메뉴
	{
		for ( INT nI=0; nI<4; nI++ )
		{
			mUtil_rcMenu[nI].left = m_rcWnd.left + 240;
			mUtil_rcMenu[nI].right = mUtil_rcMenu[nI].left + 20;
			mUtil_rcMenu[nI].top = m_rcWnd.top + 35 + 16*nI + 24*(mUtil_nSeletedMenu-44);
			mUtil_rcMenu[nI].bottom = mUtil_rcMenu[nI].top + 15;
		}
	}
	else if ( mUtil_nSeletedMenu >= 54 && mUtil_nSeletedMenu <= 63 )		// 오쪽 부족종류 클릭 메뉴
	{
		for ( INT nI=0; nI<4; nI++ )
		{
			mUtil_rcMenu[nI].left = m_rcWnd.left + 514;
			mUtil_rcMenu[nI].right = mUtil_rcMenu[nI].left + 20;
			mUtil_rcMenu[nI].top = m_rcWnd.top + 35 + 16*nI + 24*(mUtil_nSeletedMenu-54);
			mUtil_rcMenu[nI].bottom = mUtil_rcMenu[nI].top + 15;
		}
	}

/*
	if ( mUtil_nKindofSettedItem == 1 || mUtil_nKindofSettedItem == 2 || mUtil_nKindofSettedItem == 3
		|| mUtil_nKindofSettedItem == 4 || mUtil_nKindofSettedItem == 5 ) // 왼쪽
	{
		mUtil_rcMenu[0].left = m_rcWnd.left + 125;
		mUtil_rcMenu[0].right = mUtil_rcMenu[0].left + 38;
		mUtil_rcMenu[0].top = m_rcWnd.top + 106 + 48 * (mUtil_nKindofSettedItem - 1);
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

		mUtil_rcMenu[4].left = m_rcWnd.left + 125 + 38*4;
		mUtil_rcMenu[4].right = mUtil_rcMenu[4].left + 38;
		mUtil_rcMenu[4].top = mUtil_rcMenu[0].top;
		mUtil_rcMenu[4].bottom = mUtil_rcMenu[0].bottom;

		mUtil_rcMenu[5].left = m_rcWnd.left + 125 + 38*5;
		mUtil_rcMenu[5].right = mUtil_rcMenu[5].left + 38;
		mUtil_rcMenu[5].top = mUtil_rcMenu[0].top;
		mUtil_rcMenu[5].bottom = mUtil_rcMenu[0].bottom;

		mUtil_rcMenu[6].left = m_rcWnd.left + 125;
		mUtil_rcMenu[6].right = mUtil_rcMenu[6].left + 38;
		mUtil_rcMenu[6].top = mUtil_rcMenu[0].top + 38;
		mUtil_rcMenu[6].bottom = mUtil_rcMenu[0].bottom + 38;

		mUtil_rcMenu[7].left = m_rcWnd.left + 125 + 38;
		mUtil_rcMenu[7].right = mUtil_rcMenu[7].left + 38;
		mUtil_rcMenu[7].top = mUtil_rcMenu[0].top + 38;
		mUtil_rcMenu[7].bottom = mUtil_rcMenu[0].bottom + 38;

		mUtil_rcMenu[8].left = m_rcWnd.left + 125 + 38*2;
		mUtil_rcMenu[8].right = mUtil_rcMenu[8].left + 38;
		mUtil_rcMenu[8].top = mUtil_rcMenu[0].top + 38;
		mUtil_rcMenu[8].bottom = mUtil_rcMenu[0].bottom + 38;
	}
	else if ( mUtil_nKindofSettedItem == 6 || mUtil_nKindofSettedItem == 7 || mUtil_nKindofSettedItem == 8
			 || mUtil_nKindofSettedItem == 9 || mUtil_nKindofSettedItem == 10 ) // 오른쪽
	{
		mUtil_rcMenu[0].left = m_rcWnd.left + 400;
		mUtil_rcMenu[0].right = mUtil_rcMenu[0].left + 38;
		mUtil_rcMenu[0].top = m_rcWnd.top + 106 + 48 * ( mUtil_nKindofSettedItem - 6 ); 
		mUtil_rcMenu[0].bottom = mUtil_rcMenu[0].top + 38;

		mUtil_rcMenu[1].left = m_rcWnd.left + 400 + 38;
		mUtil_rcMenu[1].right = mUtil_rcMenu[1].left + 38;
		mUtil_rcMenu[1].top = mUtil_rcMenu[0].top;
		mUtil_rcMenu[1].bottom = mUtil_rcMenu[0].bottom;

		mUtil_rcMenu[2].left = m_rcWnd.left + 400 + 38 * 2;
		mUtil_rcMenu[2].right = mUtil_rcMenu[2].left + 38;
		mUtil_rcMenu[2].top = mUtil_rcMenu[0].top;
		mUtil_rcMenu[2].bottom = mUtil_rcMenu[0].bottom;

		mUtil_rcMenu[3].left = m_rcWnd.left + 400 + 38 * 3;
		mUtil_rcMenu[3].right = mUtil_rcMenu[3].left + 38;
		mUtil_rcMenu[3].top = mUtil_rcMenu[0].top;
		mUtil_rcMenu[3].bottom = mUtil_rcMenu[0].bottom;

		mUtil_rcMenu[4].left = m_rcWnd.left + 400;
		mUtil_rcMenu[4].right = mUtil_rcMenu[4].left + 38;
		mUtil_rcMenu[4].top = mUtil_rcMenu[0].top + 38;
		mUtil_rcMenu[4].bottom = mUtil_rcMenu[0].bottom + 38;

		mUtil_rcMenu[5].left = m_rcWnd.left + 400 + 38;
		mUtil_rcMenu[5].right = mUtil_rcMenu[5].left + 38;
		mUtil_rcMenu[5].top = mUtil_rcMenu[0].top + 38;
		mUtil_rcMenu[5].bottom = mUtil_rcMenu[0].bottom + 38;

		mUtil_rcMenu[6].left = m_rcWnd.left + 400 + 38 * 2;
		mUtil_rcMenu[6].right = mUtil_rcMenu[6].left + 38;
		mUtil_rcMenu[6].top = mUtil_rcMenu[0].top + 38;
		mUtil_rcMenu[6].bottom = mUtil_rcMenu[0].bottom + 38;

		mUtil_rcMenu[7].left = m_rcWnd.left + 400 + 38 * 3;
		mUtil_rcMenu[7].right = mUtil_rcMenu[7].left + 38;
		mUtil_rcMenu[7].top = mUtil_rcMenu[0].top + 38;
		mUtil_rcMenu[7].bottom = mUtil_rcMenu[0].bottom + 38;
	}
	else if ( mUtil_nKindofSettedItem >= 11 && mUtil_nKindofSettedItem <= 20 )
	{
		mUtil_rcMenu[0].left = m_rcWnd.left + 235;
		mUtil_rcMenu[0].right = mUtil_rcMenu[0].left + 20;
		mUtil_rcMenu[0].top = m_rcWnd.top + 82 + 24 * ( mUtil_nKindofSettedItem - 11 ); 
		mUtil_rcMenu[0].bottom = mUtil_rcMenu[0].top + 15;

		mUtil_rcMenu[1].left = m_rcWnd.left + 235;
		mUtil_rcMenu[1].right = mUtil_rcMenu[0].left + 20;
		mUtil_rcMenu[1].top = mUtil_rcMenu[0].top + 15;
		mUtil_rcMenu[1].bottom = mUtil_rcMenu[0].bottom + 15;

		mUtil_rcMenu[2].left = m_rcWnd.left + 235;
		mUtil_rcMenu[2].right = mUtil_rcMenu[0].left + 20;
		mUtil_rcMenu[2].top = mUtil_rcMenu[1].top + 15;
		mUtil_rcMenu[2].bottom = mUtil_rcMenu[1].bottom + 15;

		mUtil_rcMenu[3].left = m_rcWnd.left + 235;
		mUtil_rcMenu[3].right = mUtil_rcMenu[0].left + 20;
		mUtil_rcMenu[3].top = mUtil_rcMenu[2].top + 15;
		mUtil_rcMenu[3].bottom = mUtil_rcMenu[2].bottom + 15;
	}
	else if ( mUtil_nKindofSettedItem == 21 || mUtil_nKindofSettedItem == 22 )
	{
		mUtil_rcMenu[0].left = m_rcWnd.left + 128;
		mUtil_rcMenu[0].right = mUtil_rcMenu[0].left + 38;
		mUtil_rcMenu[0].top = m_rcWnd.top + 194 + 52 * ( mUtil_nKindofSettedItem - 21 ); 
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
	else if ( mUtil_nKindofSettedItem >= 23 || mUtil_nKindofSettedItem <= 32 )
	{
		mUtil_rcMenu[0].left = m_rcWnd.left + 119;
		mUtil_rcMenu[0].right = mUtil_rcMenu[0].left + 93;
		mUtil_rcMenu[0].top = m_rcWnd.top + 82 + 24 * ( mUtil_nKindofSettedItem - 23 ); 
		mUtil_rcMenu[0].bottom = mUtil_rcMenu[0].top + 15;

		mUtil_rcMenu[1].left = m_rcWnd.left + 119;
		mUtil_rcMenu[1].right = mUtil_rcMenu[0].left + 93;
		mUtil_rcMenu[1].top = mUtil_rcMenu[0].top + 15;
		mUtil_rcMenu[1].bottom = mUtil_rcMenu[0].bottom + 15;

		mUtil_rcMenu[2].left = m_rcWnd.left + 119;
		mUtil_rcMenu[2].right = mUtil_rcMenu[0].left + 93;
		mUtil_rcMenu[2].top = mUtil_rcMenu[1].top + 15;
		mUtil_rcMenu[2].bottom = mUtil_rcMenu[1].bottom + 15;

		mUtil_rcMenu[3].left = m_rcWnd.left + 119;
		mUtil_rcMenu[3].right = mUtil_rcMenu[0].left + 93;
		mUtil_rcMenu[3].top = mUtil_rcMenu[2].top + 15;
		mUtil_rcMenu[3].bottom = mUtil_rcMenu[2].bottom + 15;

		mUtil_rcMenu[4].left = m_rcWnd.left + 119;
		mUtil_rcMenu[4].right = mUtil_rcMenu[0].left + 93;
		mUtil_rcMenu[4].top = mUtil_rcMenu[3].top + 15;
		mUtil_rcMenu[4].bottom = mUtil_rcMenu[3].bottom + 15;

		mUtil_rcMenu[5].left = m_rcWnd.left + 119;
		mUtil_rcMenu[5].right = mUtil_rcMenu[0].left + 93;
		mUtil_rcMenu[5].top = mUtil_rcMenu[4].top + 15;
		mUtil_rcMenu[5].bottom = mUtil_rcMenu[4].bottom + 15;

		mUtil_rcMenu[6].left = m_rcWnd.left + 119;
		mUtil_rcMenu[6].right = mUtil_rcMenu[0].left + 93;
		mUtil_rcMenu[6].top = mUtil_rcMenu[5].top + 15;
		mUtil_rcMenu[6].bottom = mUtil_rcMenu[5].bottom + 15;

		mUtil_rcMenu[7].left = m_rcWnd.left + 119;
		mUtil_rcMenu[7].right = mUtil_rcMenu[0].left + 93;
		mUtil_rcMenu[7].top = mUtil_rcMenu[6].top + 15;
		mUtil_rcMenu[7].bottom = mUtil_rcMenu[6].bottom + 15;

		mUtil_rcMenu[8].left = m_rcWnd.left + 119;
		mUtil_rcMenu[8].right = mUtil_rcMenu[0].left + 93;
		mUtil_rcMenu[8].top = mUtil_rcMenu[7].top + 15;
		mUtil_rcMenu[8].bottom = mUtil_rcMenu[7].bottom + 15;

		mUtil_rcMenu[9].left = m_rcWnd.left + 119;
		mUtil_rcMenu[9].right = mUtil_rcMenu[0].left + 93;
		mUtil_rcMenu[9].top = mUtil_rcMenu[8].top + 15;
		mUtil_rcMenu[9].bottom = mUtil_rcMenu[8].bottom + 15;

		mUtil_rcMenu[10].left = m_rcWnd.left + 119;
		mUtil_rcMenu[10].right = mUtil_rcMenu[0].left + 93;
		mUtil_rcMenu[10].top = mUtil_rcMenu[9].top + 15;
		mUtil_rcMenu[10].bottom = mUtil_rcMenu[9].bottom + 15;
	}
*/
}


VOID CUtilWnd::ProcessUtilFunc()
{
	DWORD dwCurTime = timeGetTime();
/*
	if ( dwCurTime - mUtil_dwItemUseTimer > 1000 )
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
						if ( nJ == 5 || nJ == 6 || nJ == 7 || nJ == 8 )
						{
							if ( g_xGameProc.m_xMyHero.m_stAbility.wMP < mUtil_xUtilItemInfo[nJ].nValue && mUtil_xUtilItemInfo[nJ].xItem.m_stItemInfo.stStdItem.wLooks != 0 && g_xGameProc.m_xMyHero.m_stAbility.wHP != 0 )
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
												if ( g_xGameProc.m_bUseSpell == FALSE )
												{
													g_xGameProc.m_xInterface.m_stCommonItem.bSetted = TRUE;
													g_xGameProc.m_xInterface.m_stCommonItem.xItem = g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nCnt].xItem;
	//												g_xGameProc.m_xInterface.m_stCommonItem.bWaitResponse		= TRUE;
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
						}
						else			// 체력 검사
						{
							if ( g_xGameProc.m_xMyHero.m_stAbility.wHP < mUtil_xUtilItemInfo[nJ].nValue && g_xGameProc.m_xMyHero.m_stAbility.wHP != 0)
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
												if ( g_xGameProc.m_bUseSpell == FALSE )
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

	//												if ( nJ == 9 ) // 전서 시리즈
	//													mUtil_xUtilItemInfo[nJ].bCheck = FALSE;
													mUtil_dwItemUseTimer = dwCurTime;
												}
											}
											else
											{
												INT test = 0;
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
*/
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

						if ( wTargetHP < mUtil_xUtilMagicInfo[nJ].nValue && bFindTarget && wTargetHP != 0 )
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
								if ( (10 + pstMagicRCD->stStdMagic.bDefSpell) <= g_xGameProc.m_xMyHero.m_stAbility.wMP || pstMagicRCD->stStdMagic.wMagicID == _SKILL_BANWOL || pstMagicRCD->stStdMagic.wMagicID == _SKILL_MANWOL || pstMagicRCD->stStdMagic.wMagicID == _SKILL_MANWOL_HIGH || pstMagicRCD->stStdMagic.wMagicID == _SKILL_JUMPSHOT_HIGH )
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

	char	*pszName = NULL;
	pszName = g_xGameProc.CheckAbnormalName(g_xGameProc.m_xMyHero.m_szName);

	g_xMainWnd.StringPlus(szItemFile, ".\\Data\\", pszName, ".utl", "");
	hFile = CreateFile(szItemFile, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if ( hFile != INVALID_HANDLE_VALUE )
	{
		DWORD		dwWriteLen;

		WriteFile(hFile, mUtil_xUtilMagicInfo, sizeof(CLIENTUTILMAGICINFO)*10, &dwWriteLen, NULL);
		WriteFile(hFile, &mUtil_nHPValue, sizeof(INT), &dwWriteLen, NULL);
		WriteFile(hFile, &mUtil_nScrollValue, sizeof(INT), &dwWriteLen, NULL);
		WriteFile(hFile, &mUtil_nMPValue, sizeof(INT), &dwWriteLen, NULL);
		WriteFile(hFile, mUtil_szHPpotion, 16, &dwWriteLen, NULL);
		WriteFile(hFile, mUtil_szScroll, 16, &dwWriteLen, NULL);
		WriteFile(hFile, mUtil_szMPpotion, 16, &dwWriteLen, NULL);
		WriteFile(hFile, mUtil_szMagicName, 40*16, &dwWriteLen, NULL);
		WriteFile(hFile, mUtil_szCharmKind, 40*4, &dwWriteLen, NULL);
		WriteFile(hFile, mUtil_szCharmName, 40*16, &dwWriteLen, NULL);
		WriteFile(hFile, &mUtil_bShowSysTime, sizeof(BOOL), &dwWriteLen, NULL);
		WriteFile(hFile, &g_xGameProc.m_bFogState, sizeof(BOOL), &dwWriteLen, NULL);
		WriteFile(hFile, &mUtil_bShowMagicTime, sizeof(BOOL), &dwWriteLen, NULL);
		WriteFile(hFile, &mUtil_bShowHumanHP, sizeof(BOOL), &dwWriteLen, NULL);
		

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
	
	char	*pszName = NULL;
	pszName = g_xGameProc.CheckAbnormalName(g_xGameProc.m_xMyHero.m_szName);

	g_xMainWnd.StringPlus(szItemFile, ".\\Data\\", pszName, ".utl", "");
	hFile = CreateFile(szItemFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if ( hFile != INVALID_HANDLE_VALUE )
	{
		DWORD		dwReadLen;

		ReadFile(hFile, mUtil_xUtilMagicInfo, sizeof(CLIENTUTILMAGICINFO)*10, &dwReadLen, NULL);
		ReadFile(hFile, &mUtil_nHPValue, sizeof(INT), &dwReadLen, NULL);
		ReadFile(hFile, &mUtil_nScrollValue, sizeof(INT), &dwReadLen, NULL);
		ReadFile(hFile, &mUtil_nMPValue, sizeof(INT), &dwReadLen, NULL);
		ReadFile(hFile, mUtil_szHPpotion, 16, &dwReadLen, NULL);
		ReadFile(hFile, mUtil_szScroll, 16, &dwReadLen, NULL);
		ReadFile(hFile, mUtil_szMPpotion, 16, &dwReadLen, NULL);
		ReadFile(hFile, mUtil_szMagicName, 40*16, &dwReadLen, NULL);
		ReadFile(hFile, mUtil_szCharmKind, 40*4, &dwReadLen, NULL);
		ReadFile(hFile, mUtil_szCharmName, 40*16, &dwReadLen, NULL);
		ReadFile(hFile, &mUtil_bShowSysTime, sizeof(BOOL), &dwReadLen, NULL);
		ReadFile(hFile, &g_xGameProc.m_bFogState, sizeof(BOOL), &dwReadLen, NULL);
		ReadFile(hFile, &mUtil_bShowMagicTime, sizeof(BOOL), &dwReadLen, NULL);
		ReadFile(hFile, &mUtil_bShowHumanHP, sizeof(BOOL), &dwReadLen, NULL);

		g_xGameProc.m_ShowAddOn = mUtil_bShowSysTime;

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
			mUtil_xUtilItemInfo2[nCnt].nValue = bKey;
		}
	}
}


VOID CUtilWnd::CheckKey(BYTE bKey)
{
	for ( INT nCnt=0; nCnt<4; nCnt++ )
	{
		if ( mUtil_xUtilItemInfo2[nCnt].nValue == bKey )
			mUtil_xUtilItemInfo2[nCnt].nValue = 0;
	}
}

BOOL CUtilWnd::UseKey(BYTE bKey)
{
	DWORD dwCurTime = timeGetTime();
	if ( dwCurTime - mUtil_dwItemTakeonTimer > 2000 && bKey != 0)
	{
		for ( INT nCnt=0; nCnt<4; nCnt++ )
		{
			if ( mUtil_xUtilItemInfo2[nCnt].nValue == bKey && mUtil_xUtilItemInfo2[nCnt].bCheck )
			{
				for ( INT nCnt2 = 0; nCnt2 <= _MAX_INVEN_ITEM; nCnt2++ )
				{
					if ( g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nCnt2].bSetted )
					{
						if ( strcmp( mUtil_xUtilItemInfo2[nCnt].xItem.m_stItemInfo.stStdItem.szName, g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nCnt2].xItem.m_stItemInfo.stStdItem.szName) == 0 )
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

VOID CUtilWnd::UseCharm(INT nMagicID)
{
	CHAR	szMagicName[20], szCharmName[20];

	CListNode < CLIENTMAGICRCD > *pNode;
	LPCLIENTMAGICRCD pstMagicRCD = NULL;
	INT nIdx = 0;

	for ( INT nCnt = 0; nCnt < _MAX_TYPE_MAGIC; nCnt++ )
	{
		for ( pNode = g_xGameProc.m_xInterface.m_xMagicWnd.m_xMyMagicList[nCnt].GetHead(); pNode; pNode = pNode->GetNext() )
		{
			pstMagicRCD = pNode->GetData();

			if ( pstMagicRCD )
			{
				if ( pstMagicRCD->stStdMagic.wMagicID == nMagicID )
				{
					sprintf(szMagicName, pstMagicRCD->stStdMagic.szMagicName);
					break;
				}
			}
		}
	}


	BOOL bFind = FALSE;

	for ( INT nI=0; nI<40 && bFind == FALSE; nI++ )
	{
		if ( strcmp( szMagicName, mUtil_szMagicName[nI] ) == 0 )
		{
			sprintf( szCharmName, "%s%s%s%s", mUtil_szCharmName[nI],  g_xMsg.GetMsg(4887), mUtil_szCharmKind[nI],  g_xMsg.GetMsg(4888) );
			bFind = TRUE;
			break;
		}
	}

	// '독가루자동'을 선택한 경우
	// 회색독가루와 황색독가루를 번갈아 사용하는데 한가지밖에 없으면 그것이라도 계속 사용

	if ( strcmp( mUtil_szCharmName[nI], g_xMsg.GetMsg(6010) ) == 0 )
	{
		if ( mUtil_bGrayPotion == TRUE )
		{
			// 회색독가루를 사용했다면 황색독가루를 찾는다.

			// 황색독가루를 착용하고 있는 경우는 바로 사용한다.
			CHAR szTempName[MAX_PATH];
			INT  nLen = strlen(g_xGameProc.m_xInterface.m_xStatusWnd.m_stEquipItem[_U_CHARM].xItem.m_stItemInfo.stStdItem.szName) - 4;

			if ( nLen > 0 )
			{
				strncpy(szTempName, g_xGameProc.m_xInterface.m_xStatusWnd.m_stEquipItem[_U_CHARM].xItem.m_stItemInfo.stStdItem.szName, nLen );
				szTempName[nLen] = 0;
				if ( strcmp( g_xMsg.GetMsg(6009), szTempName) == 0 )
				{
					//황색독가루를 착용하고 있는 경우. 황색독가루 사용
					mUtil_bGrayPotion = FALSE;

					return;
				}
			}
			
			// 황색독가루를 착용하고 있지 않은 경우 가방에서 찾는다.
			bFind = FALSE;
			for ( INT nJ=0; nJ<3 && bFind == FALSE; nJ++ )
			{
				// '소'부터 사용중인지 찾고 가방에서 찾고..'중' '대'로 넘어가면서 실행
				sprintf( szCharmName, "%s%s%s%s", g_xMsg.GetMsg(6009),  g_xMsg.GetMsg(4887), g_xMsg.GetMsg(4859+nJ),  g_xMsg.GetMsg(4888) );

				//  가방에서 독가루찾기
				for ( INT nX = 0; nX< _MAX_INVEN_ITEM; nX++ )
				{
					if ( g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nX].bSetted )
					{
						if ( strcmp( szCharmName, g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nX].xItem.m_stItemInfo.stStdItem.szName ) == 0 )
						{
							INT nMakeIdx = g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nX].xItem.m_stItemInfo.nMakeIndex;
							CHAR szItemName[MAX_PATH];
							sprintf( szItemName, g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nX].xItem.m_stItemInfo.stStdItem.szName);
							
							g_xGameProc.m_xInterface.m_xStatusWnd.m_stTakeOnItemSet.xItem	  = g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nX].xItem;
							g_xGameProc.m_xInterface.m_xStatusWnd.m_stTakeOnItemSet.bSetted = TRUE;
							g_xGameProc.m_xInterface.m_xStatusWnd.m_stTakeOnItemSet.xItem.m_shCellNum = _U_CHARM;
							g_xGameProc.m_xInterface.m_xInventoryWnd.DeleteInvenItem(nMakeIdx, szItemName);

							g_xGameProc.m_xInterface.m_xStatusWnd.SetCommonFromEquip(_U_CHARM, &g_xGameProc.m_xInterface.m_stCommonItem);
							g_xGameProc.m_xInterface.m_stCommonItem.bIsHideItem = TRUE;

							g_xClientSocket.SendTakeOnOffItem(CM_TAKEONITEM, _U_CHARM, szItemName, nMakeIdx);
							mUtil_dwItemTakeonTimer = g_dwCurrTime;

							bFind = TRUE;
							mUtil_bGrayPotion = FALSE;
							return;
						}
					}
				}
			}

			// 황색독가루가 없을 경우
			// 회색독가루를 착용하고 있으면 그냥 사용하고
			// 착용하고 있지 않을 경우 '소'부터 가방에서 찾는다

			szTempName[MAX_PATH];
			nLen = strlen(g_xGameProc.m_xInterface.m_xStatusWnd.m_stEquipItem[_U_CHARM].xItem.m_stItemInfo.stStdItem.szName) - 4;

			strncpy(szTempName, g_xGameProc.m_xInterface.m_xStatusWnd.m_stEquipItem[_U_CHARM].xItem.m_stItemInfo.stStdItem.szName, nLen );
			szTempName[nLen] = 0;
			if ( strcmp( g_xMsg.GetMsg(6008), szTempName) == 0 )
			{
				//회색독가루를 착용하고 있는 경우. 회색독가루 사용
				mUtil_bGrayPotion = TRUE;
				return;
			}
			else
			{
				bFind = FALSE;
				for ( INT nJ=0; nJ<3 && bFind == FALSE; nJ++ )
				{
					// '소'부터 사용중인지 찾고 가방에서 찾고..'중' '대'로 넘어가면서 실행
					sprintf( szCharmName, "%s%s%s%s", g_xMsg.GetMsg(6009),  g_xMsg.GetMsg(4887), g_xMsg.GetMsg(4859+nJ),  g_xMsg.GetMsg(4888) );

					//  가방에서 독가루찾기
					for ( INT nX = 0; nX< _MAX_INVEN_ITEM; nX++ )
					{
						if ( g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nX].bSetted )
						{
							if ( strcmp( szCharmName, g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nX].xItem.m_stItemInfo.stStdItem.szName ) == 0 )
							{
								INT nMakeIdx = g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nX].xItem.m_stItemInfo.nMakeIndex;
								CHAR szItemName[MAX_PATH];
								sprintf( szItemName, g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nX].xItem.m_stItemInfo.stStdItem.szName);
								
								g_xGameProc.m_xInterface.m_xStatusWnd.m_stTakeOnItemSet.xItem	  = g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nX].xItem;
								g_xGameProc.m_xInterface.m_xStatusWnd.m_stTakeOnItemSet.bSetted = TRUE;
								g_xGameProc.m_xInterface.m_xStatusWnd.m_stTakeOnItemSet.xItem.m_shCellNum = _U_CHARM;
								g_xGameProc.m_xInterface.m_xInventoryWnd.DeleteInvenItem(nMakeIdx, szItemName);

								g_xGameProc.m_xInterface.m_xStatusWnd.SetCommonFromEquip(_U_CHARM, &g_xGameProc.m_xInterface.m_stCommonItem);
								g_xGameProc.m_xInterface.m_stCommonItem.bIsHideItem = TRUE;

								g_xClientSocket.SendTakeOnOffItem(CM_TAKEONITEM, _U_CHARM, szItemName, nMakeIdx);
								mUtil_dwItemTakeonTimer = g_dwCurrTime;

								bFind = TRUE;
								return;
							}
						}
					}
				}
			}
		}
		else if ( mUtil_bGrayPotion == FALSE )
		{
			// 황색독가루를 사용했다면 회색독가루를 찾는다.

			// 회색독가루를 착용하고 있는 경우는 바로 사용한다.
			CHAR szTempName[MAX_PATH];
			
			INT  nLen = strlen(g_xGameProc.m_xInterface.m_xStatusWnd.m_stEquipItem[_U_CHARM].xItem.m_stItemInfo.stStdItem.szName) - 4;

			if ( nLen > 0 )
			{
				strncpy(szTempName, g_xGameProc.m_xInterface.m_xStatusWnd.m_stEquipItem[_U_CHARM].xItem.m_stItemInfo.stStdItem.szName, nLen );
				szTempName[nLen] = 0;
				if ( strcmp( g_xMsg.GetMsg(6008), szTempName) == 0 )
				{
					//회색독가루를 착용하고 있는 경우. 회색독가루 사용
					mUtil_bGrayPotion = TRUE;
					return;
				}
			}
			
			// 회색독가루를 착용하고 있지 않은 경우 가방에서 찾는다.

			bFind = FALSE;
			for ( INT nJ=0; nJ<3 && bFind == FALSE; nJ++ )
			{
				// '소'부터 사용중인지 찾고 가방에서 찾고..'중' '대'로 넘어가면서 실행
				sprintf( szCharmName, "%s%s%s%s", g_xMsg.GetMsg(6008),  g_xMsg.GetMsg(4887), g_xMsg.GetMsg(4859+nJ),  g_xMsg.GetMsg(4888) );

				//  가방에서 독가루찾기
				for ( INT nX = 0; nX< _MAX_INVEN_ITEM; nX++ )
				{
					if ( g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nX].bSetted )
					{
						if ( strcmp( szCharmName, g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nX].xItem.m_stItemInfo.stStdItem.szName ) == 0 )
						{
							INT nMakeIdx = g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nX].xItem.m_stItemInfo.nMakeIndex;
							CHAR szItemName[MAX_PATH];
							sprintf( szItemName, g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nX].xItem.m_stItemInfo.stStdItem.szName);
							
							g_xGameProc.m_xInterface.m_xStatusWnd.m_stTakeOnItemSet.xItem	  = g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nX].xItem;
							g_xGameProc.m_xInterface.m_xStatusWnd.m_stTakeOnItemSet.bSetted = TRUE;
							g_xGameProc.m_xInterface.m_xStatusWnd.m_stTakeOnItemSet.xItem.m_shCellNum = _U_CHARM;
							g_xGameProc.m_xInterface.m_xInventoryWnd.DeleteInvenItem(nMakeIdx, szItemName);

							g_xGameProc.m_xInterface.m_xStatusWnd.SetCommonFromEquip(_U_CHARM, &g_xGameProc.m_xInterface.m_stCommonItem);
							g_xGameProc.m_xInterface.m_stCommonItem.bIsHideItem = TRUE;

							g_xClientSocket.SendTakeOnOffItem(CM_TAKEONITEM, _U_CHARM, szItemName, nMakeIdx);
							mUtil_dwItemTakeonTimer = g_dwCurrTime;

							bFind = TRUE;
							mUtil_bGrayPotion = TRUE;
							return;
						}
					}
				}
			}

			// 회색독가루가 없을 경우
			// 황색독가루를 착용하고 있으면 그냥 사용하고
			// 착용하고 있지 않을 경우 '소'부터 가방에서 찾는다

			if ( strlen(g_xGameProc.m_xInterface.m_xStatusWnd.m_stEquipItem[_U_CHARM].xItem.m_stItemInfo.stStdItem.szName) > 0 )
				strncpy(szTempName, g_xGameProc.m_xInterface.m_xStatusWnd.m_stEquipItem[_U_CHARM].xItem.m_stItemInfo.stStdItem.szName, strlen(g_xGameProc.m_xInterface.m_xStatusWnd.m_stEquipItem[_U_CHARM].xItem.m_stItemInfo.stStdItem.szName) - 5 );
				
			if ( strcmp( g_xMsg.GetMsg(6009), szTempName) == 0 )
			{
				//황색독가루를 착용하고 있는 경우. 황색독가루 사용
				mUtil_bGrayPotion = FALSE;
				return;
			}
			else
			{
				bFind = FALSE;
				for ( INT nJ=0; nJ<3 && bFind == FALSE; nJ++ )
				{
					// '소'부터 사용중인지 찾고 가방에서 찾고..'중' '대'로 넘어가면서 실행
					sprintf( szCharmName, "%s%s%s%s", g_xMsg.GetMsg(6009),  g_xMsg.GetMsg(4887), g_xMsg.GetMsg(4859+nJ),  g_xMsg.GetMsg(4888) );

					//  가방에서 독가루찾기
					for ( INT nX = 0; nX< _MAX_INVEN_ITEM; nX++ )
					{
						if ( g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nX].bSetted )
						{
							if ( strcmp( szCharmName, g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nX].xItem.m_stItemInfo.stStdItem.szName ) == 0 )
							{
								INT nMakeIdx = g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nX].xItem.m_stItemInfo.nMakeIndex;
								CHAR szItemName[MAX_PATH];
								sprintf( szItemName, g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nX].xItem.m_stItemInfo.stStdItem.szName);
								
								g_xGameProc.m_xInterface.m_xStatusWnd.m_stTakeOnItemSet.xItem	  = g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nX].xItem;
								g_xGameProc.m_xInterface.m_xStatusWnd.m_stTakeOnItemSet.bSetted = TRUE;
								g_xGameProc.m_xInterface.m_xStatusWnd.m_stTakeOnItemSet.xItem.m_shCellNum = _U_CHARM;
								g_xGameProc.m_xInterface.m_xInventoryWnd.DeleteInvenItem(nMakeIdx, szItemName);

								g_xGameProc.m_xInterface.m_xStatusWnd.SetCommonFromEquip(_U_CHARM, &g_xGameProc.m_xInterface.m_stCommonItem);
								g_xGameProc.m_xInterface.m_stCommonItem.bIsHideItem = TRUE;

								g_xClientSocket.SendTakeOnOffItem(CM_TAKEONITEM, _U_CHARM, szItemName, nMakeIdx);
								mUtil_dwItemTakeonTimer = g_dwCurrTime;

								bFind = TRUE;
								return;
							}
						}
					}
				}
			}
		}
	}

	if ( strcmp( mUtil_szCharmKind[nI], g_xMsg.GetMsg(4858) ) == 0 )
	{
		bFind = FALSE;
		for ( INT nJ=0; nJ<3 && bFind == FALSE; nJ++ )
		{
			// '소'부터 사용중인지 찾고 가방에서 찾고..'중' '대'로 넘어가면서 실행
			sprintf( szCharmName, "%s%s%s%s", mUtil_szCharmName[nI],  g_xMsg.GetMsg(4887), g_xMsg.GetMsg(4859+nJ),  g_xMsg.GetMsg(4888) );

			if ( strcmp( szCharmName, g_xGameProc.m_xInterface.m_xStatusWnd.m_stEquipItem[_U_CHARM].xItem.m_stItemInfo.stStdItem.szName ) == 0 )
			{
				bFind = TRUE;
				return;
			}
			else
			{
				//  가방에서 부적찾기
				for ( INT nX = 0; nX< _MAX_INVEN_ITEM; nX++ )
				{
					if ( g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nX].bSetted )
					{
						if ( strcmp( szCharmName, g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nX].xItem.m_stItemInfo.stStdItem.szName ) == 0 )
						{
							INT nMakeIdx = g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nX].xItem.m_stItemInfo.nMakeIndex;
							CHAR szItemName[MAX_PATH];
							sprintf( szItemName, g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nX].xItem.m_stItemInfo.stStdItem.szName);
							
							g_xGameProc.m_xInterface.m_xStatusWnd.m_stTakeOnItemSet.xItem	  = g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nX].xItem;
							g_xGameProc.m_xInterface.m_xStatusWnd.m_stTakeOnItemSet.bSetted = TRUE;
							g_xGameProc.m_xInterface.m_xStatusWnd.m_stTakeOnItemSet.xItem.m_shCellNum = _U_CHARM;
							g_xGameProc.m_xInterface.m_xInventoryWnd.DeleteInvenItem(nMakeIdx, szItemName);

							g_xGameProc.m_xInterface.m_xStatusWnd.SetCommonFromEquip(_U_CHARM, &g_xGameProc.m_xInterface.m_stCommonItem);
							g_xGameProc.m_xInterface.m_stCommonItem.bIsHideItem = TRUE;

							g_xClientSocket.SendTakeOnOffItem(CM_TAKEONITEM, _U_CHARM, szItemName, nMakeIdx);
							mUtil_dwItemTakeonTimer = g_dwCurrTime;

							bFind = TRUE;
							return;
						}
					}
				}
			}
		}
	}


	// 부적 크기를 사용자가 지정하여 사용하는 경우

	// 사용하려는 부적을 이미 사용하고 있는 경우
	if ( strcmp( szCharmName, g_xGameProc.m_xInterface.m_xStatusWnd.m_stEquipItem[_U_CHARM].xItem.m_stItemInfo.stStdItem.szName ) == 0 )
	{
		return;
	}

	// 셋팅한 부적을 현재 사용하고 있지 않을 경우 부적찾기
	for ( INT nX = 0; nX< _MAX_INVEN_ITEM; nX++ )
	{
		if ( g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nX].bSetted )
		{
			if ( strcmp( szCharmName, g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nX].xItem.m_stItemInfo.stStdItem.szName ) == 0 )
			{
				INT nMakeIdx = g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nX].xItem.m_stItemInfo.nMakeIndex;
				CHAR szItemName[MAX_PATH];
				sprintf( szItemName, g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nX].xItem.m_stItemInfo.stStdItem.szName);
				
				g_xGameProc.m_xInterface.m_xStatusWnd.m_stTakeOnItemSet.xItem	  = g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nX].xItem;
				g_xGameProc.m_xInterface.m_xStatusWnd.m_stTakeOnItemSet.bSetted = TRUE;
				g_xGameProc.m_xInterface.m_xStatusWnd.m_stTakeOnItemSet.xItem.m_shCellNum = _U_CHARM;
				g_xGameProc.m_xInterface.m_xInventoryWnd.DeleteInvenItem(nMakeIdx, szItemName);

				g_xGameProc.m_xInterface.m_xStatusWnd.SetCommonFromEquip(_U_CHARM, &g_xGameProc.m_xInterface.m_stCommonItem);
				g_xGameProc.m_xInterface.m_stCommonItem.bIsHideItem = TRUE;

				g_xClientSocket.SendTakeOnOffItem(CM_TAKEONITEM, _U_CHARM, szItemName, nMakeIdx);
				mUtil_dwItemTakeonTimer = g_dwCurrTime;
				return;
			}
		}
	}
}


VOID CUtilWnd::UseHPPotion()
{
	INT nCnt = 0, nMsgStart = 0;

	//전서 먼저 검사
	if ( g_dwCurrTime - mUtil_dwScrollUseTimer > 30000 && mUtil_nScrollValue > g_xGameProc.m_xMyHero.m_wHP && 
		( strcmp(mUtil_szScroll, g_xMsg.GetMsg(6060) ) == 0  || 
		  strcmp(mUtil_szScroll, g_xMsg.GetMsg(6061) ) == 0  || 
		  strcmp(mUtil_szScroll, g_xMsg.GetMsg(6062) ) == 0)  )
	{
		if ( g_xGameProc.m_xMyHero.m_wHP < mUtil_nScrollValue )
		{
			// 전서찾기
			for ( INT nCnt = 0; nCnt < _MAX_INVEN_ITEM; nCnt++ )
			{
				if ( g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nCnt].bSetted )
				{
					if ( strcmp( mUtil_szScroll, g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nCnt].xItem.m_stItemInfo.stStdItem.szName ) == 0 )
					{
						if ( !g_xGameProc.m_xInterface.m_stCommonItem.bSetted )
						{
							if ( g_xGameProc.m_bUseSpell == FALSE )
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
								mUtil_dwScrollUseTimer = g_dwCurrTime;

								ZeroMemory(mUtil_szScroll, 16);

								return ;
							}
						}
					}
				}
			}
		}
	}

	INT nHPMAX = 0;
	if ( g_xGameProc.m_xMyHero.m_wMAXHP >= mUtil_nHPValue )
		nHPMAX = mUtil_nHPValue;
	else
		nHPMAX = g_xGameProc.m_xMyHero.m_wMAXHP;
	
	INT nDamage = nHPMAX - g_xGameProc.m_xMyHero.m_wHP;
	
	if ( g_dwCurrTime - mUtil_dwItemUseTimer < 1000 )
		return;

	if ( g_xGameProc.m_xMyHero.m_wHP >= g_xGameProc.m_xMyHero.m_wMAXHP )
		return;

	if ( mUtil_nHPValue > g_xGameProc.m_xMyHero.m_wHP && ( strcmp(mUtil_szHPpotion, g_xMsg.GetMsg(6050) ) == 0  || strcmp(mUtil_szHPpotion, g_xMsg.GetMsg(6051) ) == 0 || strcmp(mUtil_szHPpotion, g_xMsg.GetMsg(6052) ) == 0) )
	{
		CHAR szPotionName[MAX_PATH];

		if ( nDamage >= 30 && nDamage < 70 )
		{
			nCnt = 1;
			nMsgStart = 4859;
		}
		else if ( nDamage >= 70 && nDamage < 110 )
		{
			nCnt = 2;
			nMsgStart = 4860;
		}
		else if ( nDamage >= 110 && nDamage < 170)
		{
			nCnt = 3;
			nMsgStart = 4861;
		}
		else if ( nDamage >= 170 && nDamage < 250)
		{
			nCnt = 4;
			nMsgStart = 4862;
		}
		else if ( nDamage >= 250 )
		{
			nCnt = 5;
			nMsgStart = 4863;
		}

		for ( INT nI=0; nI<nCnt; nI++ )
		{
			if ( strcmp(mUtil_szHPpotion, g_xMsg.GetMsg(6052) ) != 0 )
				sprintf( szPotionName, "%s%s%s%s", mUtil_szHPpotion,  g_xMsg.GetMsg(4887), g_xMsg.GetMsg(nMsgStart-nI),  g_xMsg.GetMsg(4888) );
			else if ( nDamage >= 170 ) // 만년설삼일 경우는 데미지가 170이상일 경우에만 약을 먹는다
				sprintf( szPotionName, "%s", mUtil_szHPpotion);

			// 물약찾기
			for ( INT nCnt = 0; nCnt < _MAX_INVEN_ITEM; nCnt++ )
			{
				if ( g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nCnt].bSetted )
				{
					if ( strcmp( szPotionName, g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nCnt].xItem.m_stItemInfo.stStdItem.szName ) == 0 )
					{
						if ( !g_xGameProc.m_xInterface.m_stCommonItem.bSetted )
						{
							if ( g_xGameProc.m_bUseSpell == FALSE )
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

								mUtil_dwItemUseTimer = g_dwCurrTime;
								return ;
							}
						}
					}
				}
			}
		}
	}
}

VOID CUtilWnd::UseMPPotion()
{
	INT nCnt = 0, nMsgStart = 0;
	INT nAmount = mUtil_nMPValue - g_xGameProc.m_xMyHero.m_wMP;

	if ( mUtil_nMPValue > 0 && ( strcmp(mUtil_szMPpotion, g_xMsg.GetMsg(6070) ) == 0  || strcmp(mUtil_szMPpotion, g_xMsg.GetMsg(6071) ) == 0) )
	{
		CHAR szPotionName[MAX_PATH];

		if ( nAmount >= 40 && nAmount < 110 )
		{
			nCnt = 1;
			nMsgStart = 4859;
		}
		else if ( nAmount >= 110 && nAmount < 180 )
		{
			nCnt = 2;
			nMsgStart = 4860;
		}
		else if ( nAmount >= 180 && nAmount < 250 )
		{
			nCnt = 3;
			nMsgStart = 4861;
		}
		else if ( nAmount >= 250 )
		{
			nCnt = 4;
			nMsgStart = 4862;
		}


		for ( INT nI=0; nI<nCnt; nI++ )
		{
			sprintf( szPotionName, "%s%s%s%s", mUtil_szMPpotion,  g_xMsg.GetMsg(4887), g_xMsg.GetMsg(nMsgStart-nI),  g_xMsg.GetMsg(4888) );

			// 물약찾기
			for ( INT nCnt = 0; nCnt < _MAX_INVEN_ITEM; nCnt++ )
			{
				if ( g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nCnt].bSetted )
				{
					if ( strcmp( szPotionName, g_xGameProc.m_xInterface.m_xInventoryWnd.m_stInventoryItem[nCnt].xItem.m_stItemInfo.stStdItem.szName ) == 0 )
					{
						if ( !g_xGameProc.m_xInterface.m_stCommonItem.bSetted )
						{
							if ( g_xGameProc.m_bUseSpell == FALSE )
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
								mUtil_dwItemUseTimer = g_dwCurrTime;
								return ;
							}
						}
					}
				}
			}
		}
	}
}
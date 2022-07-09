/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"


/******************************************************************************************************************

	CStatusWnd Class

*******************************************************************************************************************/
/******************************************************************************************************************

	함수명 : CStatusWnd::CStatusWnd()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
CStatusWnd::CStatusWnd()
{
	Init();
}



/******************************************************************************************************************

	함수명 : CStatusWnd::~CStatusWnd()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
CStatusWnd::~CStatusWnd()
{
	Destory();
}


VOID CStatusWnd::Init()
{
	INT nCnt;
	CGameWnd::Init();

	m_dwLClickTime = 0;

	m_bType	= _TYPE_EQUIP;
	ZeroMemory(&m_rcCell, sizeof(RECT)*_EQUIP_MAX_CELL);
	ZeroMemory(&m_stEquipItem, sizeof(ITEMSET)*_EQUIP_MAX_CELL);
	ZeroMemory(&m_stTakeOnItemSet, sizeof(ITEMSET));
	ZeroMemory(&m_szEquipItemIdx, sizeof(m_szEquipItemIdx));

	m_dwLastShineTick = 0;
	m_dwShineCurrDelay = 0;
	m_dwCurrShineFrm = 0;

	// 절대검
	m_nLastSwordFrame = 0;
	m_dwLastSwordTick = 0;

	m_nFameIdx		= 0;
	m_dwFameTimer	= 0;

	m_nCharmEftFrm	= 0;
	m_dwCharmTimer  = 0;

	m_nOsungEftIdx	= 0;
	m_dwOsungEftTimer = 0;

	m_nSwordEftIdx	= 0;
	m_dwSwordEftTimer = 0;

	m_nGhostAmorEftIdx = 0;
	m_dwGhostAmorTimer = 0;

	for ( nCnt  = 0; nCnt < _MAX_STAUTS_BTN; nCnt ++ )
	{
		m_xStatusBtn[nCnt].Init();
	}

	for ( INT nX=0; nX<26; nX++)
		m_bCheckShow[nX] = FALSE;
}

VOID CStatusWnd::Destory()
{
	CGameWnd::Destroy();
	Init();
}


/******************************************************************************************************************

	함수명 : CStatusWnd::CreateStatusWnd()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : INT nID
	         CWHWilImageData* pxWndImage
	         INT nFrameImgIdx
	         INT nStartX
	         INT nStartY
	         INT nWidth
	         INT nHeight
	         BOOL bCanMove
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CStatusWnd::CreateStatusWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove)
{
	CreateGameWnd(nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight, bCanMove);

	// 버튼초기화.
	m_xStatusBtn[_BTN_ID_STATUSCLOSE].CreateGameBtn(pxWndImage,  1221,  1222, nStartX+205, nStartY+422, g_xMsg.GetMsg(1052), _BTN_TYPE_FOCUS, 1221, FALSE);
	
	// 장착창 초기화.
	SetRect(&m_rcCell[_U_NECKLACE], 170, 88, 170+_INVENTORY_CELL_WIDTH,  88+_INVENTORY_CELL_HEIGHT);
	SetRect(&m_rcCell[_U_RIGHTHAND], 90, 265,  90+_INVENTORY_CELL_WIDTH, 265+_INVENTORY_CELL_HEIGHT);
	SetRect(&m_rcCell[_U_CHARM],	130, 265, 130+_INVENTORY_CELL_WIDTH, 265+_INVENTORY_CELL_HEIGHT);
	SetRect(&m_rcCell[_U_ARMRINGL],  12, 155,  12+_INVENTORY_CELL_WIDTH, 155+_INVENTORY_CELL_HEIGHT);
	SetRect(&m_rcCell[_U_ARMRINGR], 170, 155, 170+_INVENTORY_CELL_WIDTH, 155+_INVENTORY_CELL_HEIGHT);
	SetRect(&m_rcCell[_U_RINGL],	 12, 195,  12+_INVENTORY_CELL_WIDTH, 195+_INVENTORY_CELL_HEIGHT);
	SetRect(&m_rcCell[_U_RINGR],    170, 195, 170+_INVENTORY_CELL_WIDTH, 195+_INVENTORY_CELL_HEIGHT);
	SetRect(&m_rcCell[_U_HELMET],	 95,  70, 133,  104);
	SetRect(&m_rcCell[_U_DRESS], 	 95, 114, 145,  204);
	SetRect(&m_rcCell[_U_WEAPON],	 40,  70,  90,  165);
	SetRect(&m_rcCell[_U_BOOTS],	 12, 255,  12+_INVENTORY_CELL_WIDTH, 255+_INVENTORY_CELL_HEIGHT);
	SetRect(&m_rcCell[_U_ETC],		130, 265, 130+_INVENTORY_CELL_WIDTH, 265+_INVENTORY_CELL_HEIGHT);
	

	for ( INT nI=0; nI<9; nI++)
		SetRect(&m_rcAbility[nI], 210, 84 + 24*nI, 288, 102 + 24*nI);

	m_bOpa = 220;

	for ( nI=0; nI<3; nI++ )
	{
		for ( INT nJ=0; nJ<7; nJ++ )
		{
			SetRect(&m_rcAtomTooltip[nI][nJ], 62+(nJ*37), 374+(30*nI), 98+(nJ*37), 393+(30*nI));
		}
	}	
}



/******************************************************************************************************************

	함수명 : CStatusWnd::ShowStatusWnd()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CStatusWnd::ShowStatusWnd()
{
	RECT rcID;

	ShowCharEquipWnd();

	if ( _TYPE_STATUS != m_bType)
	{
		if ( g_xGameProc.m_xMyHero.m_szGuildName[0] )
			SetRect(&rcID, m_rcWnd.left+100, m_rcWnd.top+14, m_rcWnd.left+230, m_rcWnd.top+34);
		else
			SetRect(&rcID, m_rcWnd.left+100, m_rcWnd.top+30, m_rcWnd.left+230, m_rcWnd.top+50);

		g_xMainWnd.PutsHan(NULL, rcID, RGB(220, 255, 220), RGB(0, 0, 0), g_xGameProc.m_xMyHero.m_szName, g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));
		SetRect(&rcID, m_rcWnd.left+100, m_rcWnd.top+14, m_rcWnd.left+230, m_rcWnd.top+34);

		if ( g_xGameProc.m_xMyHero.m_szGuildName[0] )
		{
			rcID.top		+= 15;
			rcID.bottom		+= 15;
			g_xMainWnd.PutsHan(NULL, rcID, RGB(255, 250, 180), RGB(0, 0, 0), g_xGameProc.m_xMyHero.m_szGuildName);

			if ( g_xGameProc.m_xMyHero.m_szRankName[0] )
			{
				rcID.top		+= 14;
				rcID.bottom		+= 14;
				g_xMainWnd.PutsHan(NULL, rcID, RGB(255, 200, 150), RGB(0, 0, 0), g_xGameProc.m_xMyHero.m_szRankName);			
			}
		}

		if ( g_xGameProc.m_xMyHero.m_szMateName[0] )
		{
			SetRect(&rcID, m_rcWnd.left+118, m_rcWnd.top+66, m_rcWnd.left+227, m_rcWnd.top+82);
			g_xMainWnd.PutsHan(NULL, rcID, RGB(244, 62, 235), RGB(0, 0, 0), g_xGameProc.m_xMyHero.m_szMateName);

			if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(1298) )
			{
				g_xMainWnd.DrawWithImageForComp(
												rcID.left - 18, 
												rcID.top + 3, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
												(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage));
			}
		}
	}

	switch ( m_bType )
	{
/*		case _TYPE_EQUIP:
		{
			if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(1282) )
			{
				g_xMainWnd.DrawWithImageForComp(
												m_rcWnd.left+176, 
												m_rcWnd.top+265, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
												(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage));
			}
			break;
		}
*/		case _TYPE_STATUS:
		{
			ShowCharStatus();

/*			if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(1285) )
			{
				g_xMainWnd.DrawWithImageForComp(
												m_rcWnd.left+176, 
												m_rcWnd.top+265, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
												(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage));
			}
*/
			break;
		}
	}
	if ( m_bType == _TYPE_STATUS)
	{
		m_xStatusBtn[_BTN_ID_STATUSCLOSE].ChangeRect(m_rcWnd.left+201, m_rcWnd.top+422);
	}
	else
	{
		m_xStatusBtn[_BTN_ID_STATUSCLOSE].ChangeRect(m_rcWnd.left+288, m_rcWnd.top+15);
	}

	m_xStatusBtn[_BTN_ID_STATUSCLOSE].ShowGameBtn();

//	ShowEquipItemState();
}



/******************************************************************************************************************

	함수명 : CStatusWnd::SetStatusBtnInit()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CStatusWnd::SetStatusBtnInit()
{
	m_xStatusBtn[_BTN_ID_STATUSCLOSE].SetBtnState(_BTN_STATE_NORMAL);
}











/******************************************************************************************************************

	캐릭터 장착창관련.

*******************************************************************************************************************/
/******************************************************************************************************************

	함수명 : CStatusWnd::ShowCharEquipWnd()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CStatusWnd::ShowCharEquipWnd()
{
	INT nStartX, nStartY;

	SetRect(&m_rcCell[_U_NECKLACE], m_rcWnd.left+175, m_rcWnd.top+128, m_rcWnd.left+175+_INVENTORY_CELL_WIDTH,  m_rcWnd.top+128+_INVENTORY_CELL_HEIGHT);
	SetRect(&m_rcCell[_U_RIGHTHAND], m_rcWnd.left+95, m_rcWnd.top+284,  m_rcWnd.left+95+_INVENTORY_CELL_WIDTH, m_rcWnd.top+284+_INVENTORY_CELL_HEIGHT);
	SetRect(&m_rcCell[_U_CHARM],	m_rcWnd.left+175, m_rcWnd.top+246, m_rcWnd.left+175+_INVENTORY_CELL_WIDTH, m_rcWnd.top+284+_INVENTORY_CELL_HEIGHT);
	SetRect(&m_rcCell[_U_ARMRINGL],  m_rcWnd.left+12, m_rcWnd.top+168,  m_rcWnd.left+12+_INVENTORY_CELL_WIDTH, m_rcWnd.top+168+_INVENTORY_CELL_HEIGHT);
	SetRect(&m_rcCell[_U_ARMRINGR], m_rcWnd.left+175, m_rcWnd.top+168, m_rcWnd.left+175+_INVENTORY_CELL_WIDTH, m_rcWnd.top+168+_INVENTORY_CELL_HEIGHT);
	SetRect(&m_rcCell[_U_RINGL],	 m_rcWnd.left+12, m_rcWnd.top+208,  m_rcWnd.left+12+_INVENTORY_CELL_WIDTH, m_rcWnd.top+208+_INVENTORY_CELL_HEIGHT);
	SetRect(&m_rcCell[_U_RINGR],    m_rcWnd.left+175, m_rcWnd.top+208, m_rcWnd.left+175+_INVENTORY_CELL_WIDTH, m_rcWnd.top+208+_INVENTORY_CELL_HEIGHT);
	SetRect(&m_rcCell[_U_HELMET],	 m_rcWnd.left+95,  m_rcWnd.top+85, m_rcWnd.left+133,  m_rcWnd.top+118);
	SetRect(&m_rcCell[_U_DRESS], 	 m_rcWnd.left+95, m_rcWnd.top+120, m_rcWnd.left+145,  m_rcWnd.top+210);
	SetRect(&m_rcCell[_U_WEAPON],	 m_rcWnd.left+40,  m_rcWnd.top+70,  m_rcWnd.left+90,  m_rcWnd.top+165);
	SetRect(&m_rcCell[_U_BOOTS],	 m_rcWnd.left+12, m_rcWnd.top+272,  m_rcWnd.left+12+_INVENTORY_CELL_WIDTH, m_rcWnd.top+272+_INVENTORY_CELL_HEIGHT);
	SetRect(&m_rcCell[_U_ETC],		m_rcWnd.left+137, m_rcWnd.top+283, m_rcWnd.left+137+_INVENTORY_CELL_WIDTH, m_rcWnd.top+283+_INVENTORY_CELL_HEIGHT);	

	for ( INT nI=0; nI<3; nI++ )
	{
		for ( INT nJ=0; nJ<7; nJ++ )
		{
			SetRect(&m_rcAtomTooltip[nI][nJ], m_rcWnd.left+62+(nJ*37), m_rcWnd.top+384+(30*nI), m_rcWnd.left+98+(nJ*37), m_rcWnd.top+406+(30*nI));
		}
	}

	ShowGameWnd();
	
	INT nImgIdx = 1860 + g_xGameProc.m_xMyHero.m_stSubAbility.bFameIdx*20 + m_nFameIdx - 10;
	INT nStX, nStY;

	if ( g_dwCurrTime - m_dwFameTimer > 100 )
	{
		m_dwFameTimer = g_dwCurrTime;
		m_nFameIdx++;

		if ( g_xGameProc.m_xMyHero.m_stSubAbility.bFameIdx == 3 )
		{
			if ( m_nFameIdx > 10 )
				m_nFameIdx = 0;
		}
		else if ( g_xGameProc.m_xMyHero.m_stSubAbility.bFameIdx == 7 ) 
		{
			if ( m_nFameIdx > 11 )
				m_nFameIdx = 0;
			nStX = 258;
			nStY = 35;
		}
		else
		{
			if ( m_nFameIdx > 9 )
				m_nFameIdx = 0;
			nStX = 257;
			nStY = 35;
		}
	}

	if ( g_xGameProc.m_xMyHero.m_stSubAbility.bFameIdx == 6 )
	{
		nStX = 245;
		nStY = 24;
	}
	else if ( g_xGameProc.m_xMyHero.m_stSubAbility.bFameIdx == 7 ) 
	{
		nStX = 241;
		nStY = 20;
	}
	else
	{
		nStX = 256;
		nStY = 36;
	}

	if ( g_xGameProc.m_xMyHero.m_stSubAbility.bFameIdx > 0 && g_xGameProc.m_xMyHero.m_stSubAbility.bFameIdx < 8 )
	{
		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(nImgIdx) )
		{
			D3DMATERIAL7	mtrl;
			D3DVECTOR		vecTrans;
			D3DVECTOR		vecScale;

			INT nSX = m_rcWnd.left+nStX+g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shPX;
			INT nSY = m_rcWnd.top +nStY+g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shPY;
			vecTrans = D3DVECTOR((FLOAT)nSX, (FLOAT)nSY, 0);
			vecScale = D3DVECTOR((FLOAT)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight, 1);
			LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_INTER, nImgIdx);
			D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)255/255.0f, (FLOAT)255/255.0f);
			mtrl.diffuse.a = (FLOAT)1.0f/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr, _BLEND_LIGHT);
		}
	}
/*

	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(nImgIdx) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+233, m_rcWnd.top+19, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
	}
*/
	// 남자인지, 여자인지구분.
	if ( m_bType == _TYPE_STATUS)
	{
		return; 
	}

	if ( g_xGameProc.m_xInterface.m_stCommonItem.bSetted )
	{
		D3DMATERIAL7	mtrl;
		D3DVECTOR		vecTrans;
		D3DVECTOR		vecScale;
		switch( g_xGameProc.m_xInterface.m_stCommonItem.xItem.m_stItemInfo.stStdItem.bStdMode )
		{
			case 60:	// 장미
				{
					if ( PtInRect(&m_rcCell[_U_ETC], g_xGameProc.m_ptMousePos) )
					{
						CWHWilImageData* pxImageInter = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER];
						if ( pxImageInter->NewSetIndex(192) )
						{
							vecTrans = D3DVECTOR((FLOAT)m_rcCell[_U_ETC].left-1, (FLOAT)m_rcCell[_U_ETC].top+2, 0);
							vecScale = D3DVECTOR((FLOAT)pxImageInter->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxImageInter->m_lpstNewCurrWilImageInfo->shHeight, 1);

							LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_INTER, 192);

							D3DUtil_InitMaterial(mtrl, (FLOAT)m_bBright/255.0f, (FLOAT)m_bBright/255.0f, (FLOAT)m_bBright/255.0f);
							mtrl.diffuse.a = (FLOAT)20/255.0f;
							g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr);
						}
					}
				}
				break;
			case 53:	// 신발
				{
					if ( PtInRect(&m_rcCell[_U_BOOTS], g_xGameProc.m_ptMousePos) )
					{
						CWHWilImageData* pxImageInter = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER];
						if ( pxImageInter->NewSetIndex(195) )
						{
							vecTrans = D3DVECTOR((FLOAT)m_rcCell[_U_BOOTS].left+2, (FLOAT)m_rcCell[_U_BOOTS].top-23, 0);
							vecScale = D3DVECTOR((FLOAT)pxImageInter->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxImageInter->m_lpstNewCurrWilImageInfo->shHeight, 1);

							LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_INTER, 195);

							D3DUtil_InitMaterial(mtrl, (FLOAT)m_bBright/255.0f, (FLOAT)m_bBright/255.0f, (FLOAT)m_bBright/255.0f);
							mtrl.diffuse.a = (FLOAT)20/255.0f;
							g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr);
						}
					}
				}
				break;
			case 20:	// 목걸이
			case 21:	// 목걸이
			case 19:	// 목걸이
			case 57:	// 목걸이
				{
					if ( PtInRect(&m_rcCell[_U_NECKLACE], g_xGameProc.m_ptMousePos) )
					{
						CWHWilImageData* pxImageInter = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER];
						if ( pxImageInter->NewSetIndex(191) )
						{
							vecTrans = D3DVECTOR((FLOAT)m_rcCell[_U_NECKLACE].left+1, (FLOAT)m_rcCell[_U_NECKLACE].top+1, 0);
							vecScale = D3DVECTOR((FLOAT)pxImageInter->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxImageInter->m_lpstNewCurrWilImageInfo->shHeight, 1);

							LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_INTER, 191);

							D3DUtil_InitMaterial(mtrl, (FLOAT)m_bBright/255.0f, (FLOAT)m_bBright/255.0f, (FLOAT)m_bBright/255.0f);
							mtrl.diffuse.a = (FLOAT)0/255.0f;
							g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr);
						}
					}
				}
				break;
			case 22:	//반지
			case 23:	//반지
				{
					if ( PtInRect(&m_rcCell[_U_RINGL], g_xGameProc.m_ptMousePos) )
					{
						CWHWilImageData* pxImageInter = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER];
						if ( pxImageInter->NewSetIndex(190) )
						{
							vecTrans = D3DVECTOR((FLOAT)m_rcCell[_U_RINGL].left+2, (FLOAT)m_rcCell[_U_RINGL].top+1, 0);
							vecScale = D3DVECTOR((FLOAT)pxImageInter->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxImageInter->m_lpstNewCurrWilImageInfo->shHeight, 1);

							LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_INTER, 190);

							D3DUtil_InitMaterial(mtrl, (FLOAT)m_bBright/255.0f, (FLOAT)m_bBright/255.0f, (FLOAT)m_bBright/255.0f);
							mtrl.diffuse.a = (FLOAT)20/255.0f;
							g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr);
						}
					}
					else if ( PtInRect(&m_rcCell[_U_RINGR], g_xGameProc.m_ptMousePos) )
					{
						CWHWilImageData* pxImageInter = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER];
						if ( pxImageInter->NewSetIndex(190) )
						{
							vecTrans = D3DVECTOR((FLOAT)m_rcCell[_U_RINGR].left+1, (FLOAT)m_rcCell[_U_RINGR].top+1, 0);
							vecScale = D3DVECTOR((FLOAT)pxImageInter->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxImageInter->m_lpstNewCurrWilImageInfo->shHeight, 1);

							LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_INTER, 190);

							D3DUtil_InitMaterial(mtrl, (FLOAT)m_bBright/255.0f, (FLOAT)m_bBright/255.0f, (FLOAT)m_bBright/255.0f);
							mtrl.diffuse.a = (FLOAT)1/255.0f;
							g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr);
						}
					}
					
				}
				break;
			case 25:	//독가루, 부적
				{
					if ( PtInRect(&m_rcCell[_U_CHARM], g_xGameProc.m_ptMousePos) )
					{
						CWHWilImageData* pxImageInter = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER];
						if ( pxImageInter->NewSetIndex(196) )
						{
							vecTrans = D3DVECTOR((FLOAT)m_rcCell[_U_CHARM].left+1, (FLOAT)m_rcCell[_U_CHARM].top + 2, 0);
							vecScale = D3DVECTOR((FLOAT)pxImageInter->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxImageInter->m_lpstNewCurrWilImageInfo->shHeight, 1);

							LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_INTER, 196);

							D3DUtil_InitMaterial(mtrl, (FLOAT)m_bBright/255.0f, (FLOAT)m_bBright/255.0f, (FLOAT)m_bBright/255.0f);
							mtrl.diffuse.a = (FLOAT)20/255.0f;
							g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr);
						}
					}
				}
				break;
			case 30:	//초, 횃불
				{
					if ( PtInRect(&m_rcCell[_U_RIGHTHAND], g_xGameProc.m_ptMousePos) )
					{
						CWHWilImageData* pxImageInter = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER];
						if ( pxImageInter->NewSetIndex(193) )
						{
							vecTrans = D3DVECTOR((FLOAT)m_rcCell[_U_RIGHTHAND].left+1, (FLOAT)m_rcCell[_U_RIGHTHAND].top+1, 0);
							vecScale = D3DVECTOR((FLOAT)pxImageInter->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxImageInter->m_lpstNewCurrWilImageInfo->shHeight, 1);

							LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_INTER, 193);

							D3DUtil_InitMaterial(mtrl, (FLOAT)m_bBright/255.0f, (FLOAT)m_bBright/255.0f, (FLOAT)m_bBright/255.0f);
							mtrl.diffuse.a = (FLOAT)20/255.0f;
							g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr);
						}
					}
				}
				break;
			case 24:	//팔찌
			case 26:	//팔찌
				{
					if ( PtInRect(&m_rcCell[_U_ARMRINGL], g_xGameProc.m_ptMousePos) )
					{
						CWHWilImageData* pxImageInter = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER];
						if ( pxImageInter->NewSetIndex(194) )
						{
							vecTrans = D3DVECTOR((FLOAT)m_rcCell[_U_ARMRINGL].left+2, (FLOAT)m_rcCell[_U_ARMRINGL].top+1, 0);
							vecScale = D3DVECTOR((FLOAT)pxImageInter->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxImageInter->m_lpstNewCurrWilImageInfo->shHeight, 1);

							LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_INTER, 194);

							D3DUtil_InitMaterial(mtrl, (FLOAT)m_bBright/255.0f, (FLOAT)m_bBright/255.0f, (FLOAT)m_bBright/255.0f);
							mtrl.diffuse.a = (FLOAT)20/255.0f;
							g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr);
						}
					}
					else if ( PtInRect(&m_rcCell[_U_ARMRINGR], g_xGameProc.m_ptMousePos) )
					{
						CWHWilImageData* pxImageInter = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER];
						if ( pxImageInter->NewSetIndex(194) )
						{
							vecTrans = D3DVECTOR((FLOAT)m_rcCell[_U_ARMRINGR].left+1, (FLOAT)m_rcCell[_U_ARMRINGR].top+1, 0);
							vecScale = D3DVECTOR((FLOAT)pxImageInter->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxImageInter->m_lpstNewCurrWilImageInfo->shHeight, 1);

							LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_INTER, 194);

							D3DUtil_InitMaterial(mtrl, (FLOAT)m_bBright/255.0f, (FLOAT)m_bBright/255.0f, (FLOAT)m_bBright/255.0f);
							mtrl.diffuse.a = (FLOAT)20/255.0f;
							g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr);
						}
					}
				}
				break;
		}
	}

	// 후광있는 옷인가를 확인한다. Wil파일 이미지리스트상에서 확인.
	WORD wLooks = m_stEquipItem[_U_DRESS].xItem.m_stItemInfo.stStdItem.wLooks;
	WORD w33Img[6] = {982, 992, 1002, 1012, 1022, 1032};	// Equip.wil
	WORD wBLightImg[6] = {100, 110, 101, 111, 102, 112};	// ProgUse.wil
	for ( INT nCnt = 0; nCnt < 6; nCnt++ )
	{
		if( wLooks == w33Img[nCnt] )
		{
			CWHWilImageData* pxPrgUse = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE];
			if ( pxPrgUse->NewSetIndex(wBLightImg[nCnt]) )
			{
				D3DMATERIAL7	mtrl;
				D3DVECTOR		vecTrans;
				D3DVECTOR		vecScale;

				INT nSX = m_rcWnd.left+_NEW_EQUIP_CHAR_X+pxPrgUse->m_lpstNewCurrWilImageInfo->shPX;
				INT nSY = m_rcWnd.top +_NEW_EQUIP_CHAR_Y+pxPrgUse->m_lpstNewCurrWilImageInfo->shPY;
				vecTrans = D3DVECTOR((FLOAT)nSX, (FLOAT)nSY, 0);
				vecScale = D3DVECTOR((FLOAT)pxPrgUse->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxPrgUse->m_lpstNewCurrWilImageInfo->shHeight, 1);
				LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_PROGUSE, wBLightImg[nCnt]);
				D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)180/255.0f, (FLOAT)100/255.0f);
				mtrl.diffuse.a = (FLOAT)1.0f/255.0f;
				g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr, _BLEND_LIGHT);
			}
			break;
		}
	}

	// 후광있는 옷인가를 확인한다. Wil파일 이미지리스트상에서 확인.
	wLooks = m_stEquipItem[_U_DRESS].xItem.m_stItemInfo.stStdItem.wLooks;
	WORD w44Img[6] = {983, 993, 1003, 1013, 1023, 1033};	// Equip.wil
	WORD wBLightImg44[6] = {120, 130, 121, 131, 122, 132};	// ProgUse.wil
	for ( nCnt = 0; nCnt < 6; nCnt++ )
	{
		if( wLooks == w44Img[nCnt] )
		{
			CWHWilImageData* pxPrgUse = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE];
			if ( pxPrgUse->NewSetIndex(wBLightImg44[nCnt]) )
			{
				D3DMATERIAL7	mtrl;
				D3DVECTOR		vecTrans;
				D3DVECTOR		vecScale;

				INT nSX = m_rcWnd.left+_NEW_EQUIP_CHAR_X+pxPrgUse->m_lpstNewCurrWilImageInfo->shPX;
				INT nSY = m_rcWnd.top +_NEW_EQUIP_CHAR_Y+pxPrgUse->m_lpstNewCurrWilImageInfo->shPY;
				vecTrans = D3DVECTOR((FLOAT)nSX, (FLOAT)nSY, 0);
				vecScale = D3DVECTOR((FLOAT)pxPrgUse->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxPrgUse->m_lpstNewCurrWilImageInfo->shHeight, 1);
				LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_PROGUSE, wBLightImg44[nCnt]);
				D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)255/255.0f, (FLOAT)255/255.0f);
				mtrl.diffuse.a = (FLOAT)1.0f/255.0f;
				g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr, _BLEND_LIGHT);
			}
			break;
		}
	}

	// 후광있는 옷인가를 확인한다. Wil파일 이미지리스트상에서 확인. (경갑옷)
	wLooks = m_stEquipItem[_U_DRESS].xItem.m_stItemInfo.stStdItem.wLooks;
	WORD w11Img[2] = {942, 952};	// Equip.wil
	WORD wBLightImg11[2] = {160, 161};	// ProgUse.wil
	for ( nCnt = 0; nCnt < 2; nCnt++ )
	{
		if( wLooks == w11Img[nCnt] )
		{
			CWHWilImageData* pxPrgUse = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE];
			if ( pxPrgUse->NewSetIndex(wBLightImg11[nCnt]) )
			{
				D3DMATERIAL7	mtrl;
				D3DVECTOR		vecTrans;
				D3DVECTOR		vecScale;

				INT nSX = m_rcWnd.left+_NEW_EQUIP_CHAR_X+pxPrgUse->m_lpstNewCurrWilImageInfo->shPX;
				INT nSY = m_rcWnd.top +_NEW_EQUIP_CHAR_Y+pxPrgUse->m_lpstNewCurrWilImageInfo->shPY;
				vecTrans = D3DVECTOR((FLOAT)nSX, (FLOAT)nSY, 0);
				vecScale = D3DVECTOR((FLOAT)pxPrgUse->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxPrgUse->m_lpstNewCurrWilImageInfo->shHeight, 1);
				LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_PROGUSE, wBLightImg11[nCnt]);
				D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)255/255.0f, (FLOAT)255/255.0f);
				mtrl.diffuse.a = (FLOAT)1.0f/255.0f;
				g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr, _BLEND_LIGHT);
			}
			break;
		}
	}

	// 후광있는 옷인가를 확인한다. Wil파일 이미지리스트상에서 확인. (귀문보갑)
	wLooks = m_stEquipItem[_U_DRESS].xItem.m_stItemInfo.stStdItem.wLooks;
	WORD w51Img[2] = {984, 994};	// Equip.wil
	WORD wBLightImg51[2] = {190, 191};	// ProgUse.wil
	for ( nCnt = 0; nCnt < 2; nCnt++ )
	{
		if( wLooks == w51Img[nCnt] )
		{
			CWHWilImageData* pxPrgUse = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE];
			if ( pxPrgUse->NewSetIndex(wBLightImg51[nCnt]) )
			{
				D3DMATERIAL7	mtrl;
				D3DVECTOR		vecTrans;
				D3DVECTOR		vecScale;

				INT nSX = m_rcWnd.left+_NEW_EQUIP_CHAR_X+pxPrgUse->m_lpstNewCurrWilImageInfo->shPX;
				INT nSY = m_rcWnd.top +_NEW_EQUIP_CHAR_Y+pxPrgUse->m_lpstNewCurrWilImageInfo->shPY;
				vecTrans = D3DVECTOR((FLOAT)nSX, (FLOAT)nSY, 0);
				vecScale = D3DVECTOR((FLOAT)pxPrgUse->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxPrgUse->m_lpstNewCurrWilImageInfo->shHeight, 1);
				LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_PROGUSE, wBLightImg51[nCnt]);
				D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)255/255.0f, (FLOAT)255/255.0f);
				mtrl.diffuse.a = (FLOAT)1.0f/255.0f;
				g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr, _BLEND_LIGHT);
			}

			break;
		}
	}

	// 후광있는 옷인가를 확인한다. Wil파일 이미지리스트상에서 확인. (귀령신갑)
	wLooks = m_stEquipItem[_U_DRESS].xItem.m_stItemInfo.stStdItem.wLooks;
	WORD w50Img[2] = {985, 995};	// Equip.wil
	WORD wBLightImg50[2] = {171, 181};	// ProgUse.wil
	for ( nCnt = 0; nCnt < 2; nCnt++ )
	{
		if( wLooks == w50Img[nCnt] )
		{
			CWHWilImageData* pxPrgUse = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE];
			if ( pxPrgUse->NewSetIndex(wBLightImg50[nCnt]) )
			{
				D3DMATERIAL7	mtrl;
				D3DVECTOR		vecTrans;
				D3DVECTOR		vecScale;

				INT nSX = m_rcWnd.left+_NEW_EQUIP_CHAR_X+pxPrgUse->m_lpstNewCurrWilImageInfo->shPX;
				INT nSY = m_rcWnd.top +_NEW_EQUIP_CHAR_Y+pxPrgUse->m_lpstNewCurrWilImageInfo->shPY;
				vecTrans = D3DVECTOR((FLOAT)nSX, (FLOAT)nSY, 0);
				vecScale = D3DVECTOR((FLOAT)pxPrgUse->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxPrgUse->m_lpstNewCurrWilImageInfo->shHeight, 1);
				LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_PROGUSE, wBLightImg50[nCnt]);
				D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)255/255.0f, (FLOAT)255/255.0f);
				mtrl.diffuse.a = (FLOAT)1.0f/255.0f;
				g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr, _BLEND_LIGHT);
			}

			break;
		}
	}

	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].NewSetIndex(g_xGameProc.m_xMyHero.m_stFeature.bGender) )
	{
		g_xMainWnd.DrawWithImageForComp(
						m_rcWnd.left+_NEW_EQUIP_CHAR_X+g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shPX, 
						m_rcWnd.top+_NEW_EQUIP_CHAR_Y+g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shPY, 
						g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shWidth, 
						g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shHeight,
						(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_pbCurrImage));
	}

	// 아이템 그리기.
	for ( nCnt = 0; nCnt < _EQUIP_MAX_CELL; nCnt++ )
	{
		if ( m_stEquipItem[nCnt].bSetted )
		{
			if ( nCnt!=_U_HELMET && nCnt!=_U_WEAPON && nCnt!=_U_DRESS )
			{
				nStartX = m_rcCell[nCnt].left;
				nStartY = m_rcCell[nCnt].top;

				if ( nCnt ==_U_CHARM )
					nStartY = m_rcCell[nCnt].top + 38;

				if ( m_stEquipItem[nCnt].xItem.m_stItemInfo.Desc[8] == 1 &&
					m_stEquipItem[nCnt].xItem.m_stItemInfo.stStdItem.bStdMode != 5 && m_stEquipItem[nCnt].xItem.m_stItemInfo.stStdItem.bStdMode != 6 && 
					m_stEquipItem[nCnt].xItem.m_stItemInfo.stStdItem.bStdMode != 10 &&
					m_stEquipItem[nCnt].xItem.m_stItemInfo.stStdItem.bStdMode != 11 && 
					m_stEquipItem[nCnt].xItem.m_stItemInfo.stStdItem.bStdMode != 15 && 
					m_stEquipItem[nCnt].xItem.m_stItemInfo.stStdItem.bStdMode != 53 )
				{
					if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(197) )
					{
 						g_xMainWnd.DrawWithImageForComp(
										m_rcCell[nCnt].left - 1, m_rcCell[nCnt].top - 2,
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth,
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage));
					}

					m_stEquipItem[nCnt].xItem.DrawItem(nStartX, nStartY);

					RenderShine(m_rcCell[nCnt].left, m_rcCell[nCnt].top);
				}
				else
				{
					m_stEquipItem[nCnt].xItem.DrawItem(nStartX, nStartY);
				}

				// 속성 부적 이펙트
				if ( nCnt == _U_CHARM )
				{
					if ( m_stEquipItem[nCnt].xItem.m_stItemInfo.stStdItem.FuncType != 0 && m_stEquipItem[nCnt].xItem.m_stItemInfo.stStdItem.bShape ==  9 )
					{
						INT nImgIdx = 2020 + (m_stEquipItem[nCnt].xItem.m_stItemInfo.stStdItem.FuncType-1)*10 + m_nCharmEftFrm;
						INT nStX, nStY;

						INT nDura = RoundFunc(m_stEquipItem[nCnt].xItem.m_stItemInfo.nDura, 100) * 255 / RoundFunc(m_stEquipItem[nCnt].xItem.m_stItemInfo.stStdItem.wDuraMax, 100);

						INT nOnTime;

						if ( nDura > 230 )
							nOnTime = 30;
						else if ( nDura > 220 )
							nOnTime = 35;
						else if ( nDura > 210 )
							nOnTime = 40;
						else if ( nDura > 200 )
							nOnTime = 45;
						else if ( nDura > 190 )
							nOnTime = 50;
						else if ( nDura > 180 )
							nOnTime = 55;
						else if ( nDura > 170 )
							nOnTime = 60;
						else if ( nDura > 160 )
							nOnTime = 65;
						else if ( nDura > 150 )
							nOnTime = 70;
						else if ( nDura > 140 )
							nOnTime = 75;
						else if ( nDura > 130 )
							nOnTime = 80;
						else if ( nDura > 120 )
							nOnTime = 85;
						else if ( nDura > 110 )
							nOnTime = 90;
						else if ( nDura > 100 )
							nOnTime = 95;
						else if ( nDura > 90 )
							nOnTime = 100;
						else if ( nDura > 80 )
							nOnTime = 105;
						else if ( nDura > 70 )
							nOnTime = 110;
						else if ( nDura > 60 )
							nOnTime = 115;
						else if ( nDura > 50 )
							nOnTime = 120;
						else if ( nDura > 40 )
							nOnTime = 125;
						else if ( nDura > 30 )
							nOnTime = 130;
						else if ( nDura > 20 )
							nOnTime = 135;
						else
							nOnTime = 140;

						nDura += 20;

						if ( m_stEquipItem[nCnt].xItem.m_stItemInfo.stStdItem.FuncType == 1 )
						{
							nStX = 170;
							nStY = 288;
						}
						else if ( m_stEquipItem[nCnt].xItem.m_stItemInfo.stStdItem.FuncType == 2 )
						{
							nStX = 170;
							nStY = 288;
						}
						else if ( m_stEquipItem[nCnt].xItem.m_stItemInfo.stStdItem.FuncType == 3 )
						{
							nStX = 170;
							nStY = 288;
						}
						else if ( m_stEquipItem[nCnt].xItem.m_stItemInfo.stStdItem.FuncType == 4 )
						{
							nStX = 170;
							nStY = 288;
						}
						
						if ( g_dwCurrTime - m_dwCharmTimer > nOnTime )
						{
							m_dwCharmTimer = g_dwCurrTime;
							m_nCharmEftFrm++;
						}

						if ( m_nCharmEftFrm > 9 )
							m_nCharmEftFrm = 0;

						if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(nImgIdx) )
						{
							D3DMATERIAL7	mtrl;
							D3DVECTOR		vecTrans;
							D3DVECTOR		vecScale;

							INT nSX = m_rcWnd.left+nStX+g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shPX;
							INT nSY = m_rcWnd.top +nStY+g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shPY;
							vecTrans = D3DVECTOR((FLOAT)nSX, (FLOAT)nSY, 0);
							vecScale = D3DVECTOR((FLOAT)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight, 1);
							LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_INTER, nImgIdx);
							D3DUtil_InitMaterial(mtrl, (FLOAT)nDura/255.0f, (FLOAT)nDura/255.0f, (FLOAT)nDura/255.0f);
							mtrl.diffuse.a = (FLOAT)1.0f/255.0f;
							g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr, _BLEND_LIGHT);
						}
					}
				}
				else if ( nCnt == _U_ETC )
				{
					if ( m_stEquipItem[_U_ETC].xItem.m_stItemInfo.stStdItem.wLooks == 79 )
					{
						if ( g_dwCurrTime - m_dwOsungEftTimer > 100 )
						{
							m_dwOsungEftTimer = g_dwCurrTime;
							m_nOsungEftIdx++;
						}

						if ( m_nOsungEftIdx > 5 )
							m_nOsungEftIdx = 0;

						nImgIdx = m_nOsungEftIdx + 600;

						if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(nImgIdx) )
						{
							D3DMATERIAL7	mtrl;
							D3DVECTOR		vecTrans;
							D3DVECTOR		vecScale;

							INT nSX = m_rcWnd.left+162+g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shPX;
							INT nSY = m_rcWnd.top +299+g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shPY;
							vecTrans = D3DVECTOR((FLOAT)nSX, (FLOAT)nSY, 0);
							vecScale = D3DVECTOR((FLOAT)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight, 1);
							LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_INTER, nImgIdx);
							D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)255/255.0f, (FLOAT)255/255.0f);
							mtrl.diffuse.a = (FLOAT)1.0f/255.0f;
							g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr, _BLEND_LIGHT);
						}
					}
				}
			}
			else if ( nCnt == _U_WEAPON )
			{
				nStartX = m_rcWnd.left+_NEW_EQUIP_CHAR_X;
				nStartY = m_rcWnd.top+_NEW_EQUIP_CHAR_Y;

				m_stEquipItem[nCnt].xItem.DrawItemUseColorIdx(nStartX, nStartY, g_xGameProc.m_xMyHero.m_stFeatureEx.bWeaponColor, _ITEM_TYPE_EQUIP);
			}
			else
			{
				nStartX = m_rcWnd.left+_NEW_EQUIP_CHAR_X;
				nStartY = m_rcWnd.top+_NEW_EQUIP_CHAR_Y;

				m_stEquipItem[nCnt].xItem.DrawItem(nStartX, nStartY, _ITEM_TYPE_EQUIP);
			}
		}
	}

	// 2006.07.03 - 신규의복 이펙트

	// 호신보갑. 상태창 이펙트
	wLooks = m_stEquipItem[_U_DRESS].xItem.m_stItemInfo.stStdItem.wLooks;
	WORD wHosinbogab[2] = {961, 971};	// Equip.wil
	WORD wBLightHosinbogab[2] = {730, 731};	// ProgUse.wil
	for ( nCnt = 0; nCnt < 2; nCnt++ )
	{
		if( wLooks == wHosinbogab[nCnt] )
		{
			CWHWilImageData* pxPrgUse = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE];
			if ( pxPrgUse->NewSetIndex(wBLightHosinbogab[nCnt]) )
			{
				D3DMATERIAL7	mtrl;
				D3DVECTOR		vecTrans;
				D3DVECTOR		vecScale;

				INT nSX = m_rcWnd.left+_NEW_USERSTATUS_CHAR_X+pxPrgUse->m_lpstNewCurrWilImageInfo->shPX-1;
				INT nSY = m_rcWnd.top +_NEW_USERSTATUS_CHAR_Y+pxPrgUse->m_lpstNewCurrWilImageInfo->shPY-4;
				vecTrans = D3DVECTOR((FLOAT)nSX, (FLOAT)nSY, 0);
				vecScale = D3DVECTOR((FLOAT)pxPrgUse->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxPrgUse->m_lpstNewCurrWilImageInfo->shHeight, 1);
				LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_PROGUSE, wBLightHosinbogab[nCnt]);
				D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)255/255.0f, (FLOAT)255/255.0f);
				mtrl.diffuse.a = (FLOAT)1.0f/255.0f;
				g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr, _BLEND_LIGHT);
			}
			break;
		}
	}


	// 용린은갑. 상태창 이펙트
	wLooks = m_stEquipItem[_U_DRESS].xItem.m_stItemInfo.stStdItem.wLooks;
	WORD wYonglin[2] = {962, 972};	// Equip.wil
	
	for ( nCnt = 0; nCnt < 2; nCnt++ )
	{
		if( wLooks == wYonglin[nCnt] )
		{
			CWHWilImageData* pxPrgUse = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE];

			if ( g_dwCurrTime - m_dwYonglinEftTimer > 80 )
			{
				m_dwYonglinEftTimer = g_dwCurrTime;
				m_nYonglinEftIdx++;
				
				if ( m_nYonglinEftIdx > 9 )
					m_nYonglinEftIdx = 0;
			}	

			INT nIdx = m_nYonglinEftIdx;

			if ( g_xGameProc.m_xMyHero.m_stFeature.bGender == _GENDER_MAN )
				nIdx += 740;
			else
				nIdx += 750;

			if ( pxPrgUse->NewSetIndex(nIdx) )
			{
				D3DMATERIAL7	mtrl;
				D3DVECTOR		vecTrans;
				D3DVECTOR		vecScale;

				INT nSX = m_rcWnd.left+_NEW_USERSTATUS_CHAR_X+pxPrgUse->m_lpstNewCurrWilImageInfo->shPX;
				INT nSY = m_rcWnd.top +_NEW_USERSTATUS_CHAR_Y+pxPrgUse->m_lpstNewCurrWilImageInfo->shPY;
				vecTrans = D3DVECTOR((FLOAT)nSX, (FLOAT)nSY, 0);
				vecScale = D3DVECTOR((FLOAT)pxPrgUse->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxPrgUse->m_lpstNewCurrWilImageInfo->shHeight, 1);
				LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_PROGUSE, nIdx);
				D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)255/255.0f, (FLOAT)255/255.0f);
				mtrl.diffuse.a = (FLOAT)1.0f/255.0f;
				g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr, _BLEND_LIGHT);
			}
			break;
		}
	}

	// 용린보갑 상태창 이펙트
	wLooks = m_stEquipItem[_U_DRESS].xItem.m_stItemInfo.stStdItem.wLooks;
	WORD wYongbo[2] = {963, 973};	// Equip.wil
	
	for ( nCnt = 0; nCnt < 2; nCnt++ )
	{
		if( wLooks == wYongbo[nCnt] )
		{
			CWHWilImageData* pxPrgUse = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE];

			if ( g_dwCurrTime - m_dwMyungEftTimer > 90 )
			{
				m_dwMyungEftTimer = g_dwCurrTime;
				m_nMyungEftIdx++;
				
				if ( m_nMyungEftIdx > 14 )
					m_nMyungEftIdx = 0;
			}	

			INT nIdx = m_nMyungEftIdx;

			if ( g_xGameProc.m_xMyHero.m_stFeature.bGender == _GENDER_MAN )
				nIdx += 770;
			else
				nIdx += 790;

			if ( pxPrgUse->NewSetIndex(nIdx) )
			{
				D3DMATERIAL7	mtrl;
				D3DVECTOR		vecTrans;
				D3DVECTOR		vecScale;

				INT nSX = m_rcWnd.left+_NEW_USERSTATUS_CHAR_X+pxPrgUse->m_lpstNewCurrWilImageInfo->shPX-1;
				INT nSY = m_rcWnd.top +_NEW_USERSTATUS_CHAR_Y+pxPrgUse->m_lpstNewCurrWilImageInfo->shPY-4;
				vecTrans = D3DVECTOR((FLOAT)nSX, (FLOAT)nSY, 0);
				vecScale = D3DVECTOR((FLOAT)pxPrgUse->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxPrgUse->m_lpstNewCurrWilImageInfo->shHeight, 1);
				LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_PROGUSE, nIdx);
				D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)255/255.0f, (FLOAT)255/255.0f);
				mtrl.diffuse.a = (FLOAT)1.0f/255.0f;
				g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr, _BLEND_LIGHT);
			}
			break;
		}
	}

	// 명광봉의 상태창 이펙트
	wLooks = m_stEquipItem[_U_DRESS].xItem.m_stItemInfo.stStdItem.wLooks;
	WORD wMyung[2] = {964, 974};	// Equip.wil
	
	for ( nCnt = 0; nCnt < 2; nCnt++ )
	{
		if( wLooks == wMyung[nCnt] )
		{
			CWHWilImageData* pxPrgUse = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE];

			if ( g_dwCurrTime - m_dwMyungEftTimer > 100 )
			{
				m_dwMyungEftTimer = g_dwCurrTime;
				m_nMyungEftIdx++;
				
				if ( m_nMyungEftIdx > 14 )
					m_nMyungEftIdx = 0;
			}	

			INT nIdx = m_nMyungEftIdx;

			if ( g_xGameProc.m_xMyHero.m_stFeature.bGender == _GENDER_MAN )
				nIdx += 810;
			else
				nIdx += 830;

			if ( pxPrgUse->NewSetIndex(nIdx) )
			{
				D3DMATERIAL7	mtrl;
				D3DVECTOR		vecTrans;
				D3DVECTOR		vecScale;

				INT nSX = m_rcWnd.left+_NEW_USERSTATUS_CHAR_X+pxPrgUse->m_lpstNewCurrWilImageInfo->shPX-1;
				INT nSY = m_rcWnd.top +_NEW_USERSTATUS_CHAR_Y+pxPrgUse->m_lpstNewCurrWilImageInfo->shPY-4;
				vecTrans = D3DVECTOR((FLOAT)nSX, (FLOAT)nSY, 0);
				vecScale = D3DVECTOR((FLOAT)pxPrgUse->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxPrgUse->m_lpstNewCurrWilImageInfo->shHeight, 1);
				LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_PROGUSE, nIdx);
				D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)255/255.0f, (FLOAT)255/255.0f);
				mtrl.diffuse.a = (FLOAT)1.0f/255.0f;
				g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr, _BLEND_LIGHT);
			}
			break;
		}
	}

	// 적관마의 상태창 이펙트
	wLooks = m_stEquipItem[_U_DRESS].xItem.m_stItemInfo.stStdItem.wLooks;
	WORD wReddevil[2] = {965, 975};	// Equip.wil
	
	for ( nCnt = 0; nCnt < 2; nCnt++ )
	{
		if( wLooks == wReddevil[nCnt] )
		{
			CWHWilImageData* pxPrgUse = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE];

			if ( g_dwCurrTime - m_dwMyungEftTimer > 80 )
			{
				m_dwMyungEftTimer = g_dwCurrTime;
				m_nMyungEftIdx++;
				
				if ( m_nMyungEftIdx > 14 )
					m_nMyungEftIdx = 0;
			}	

			INT nIdx = m_nMyungEftIdx;

			if ( g_xGameProc.m_xMyHero.m_stFeature.bGender == _GENDER_MAN )
				nIdx += 850;
			else
				nIdx += 870;

			if ( pxPrgUse->NewSetIndex(nIdx) )
			{
				D3DMATERIAL7	mtrl;
				D3DVECTOR		vecTrans;
				D3DVECTOR		vecScale;

				INT nSX = m_rcWnd.left+_NEW_USERSTATUS_CHAR_X+pxPrgUse->m_lpstNewCurrWilImageInfo->shPX-1;
				INT nSY = m_rcWnd.top +_NEW_USERSTATUS_CHAR_Y+pxPrgUse->m_lpstNewCurrWilImageInfo->shPY-4;
				vecTrans = D3DVECTOR((FLOAT)nSX, (FLOAT)nSY, 0);
				vecScale = D3DVECTOR((FLOAT)pxPrgUse->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxPrgUse->m_lpstNewCurrWilImageInfo->shHeight, 1);
				LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_PROGUSE, nIdx);
				D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)255/255.0f, (FLOAT)255/255.0f);
				mtrl.diffuse.a = (FLOAT)1.0f/255.0f;
				g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr, _BLEND_LIGHT);
			}
			break;
		}
	}

	// 적룡신갑. 상태창 이펙트
	wLooks = m_stEquipItem[_U_DRESS].xItem.m_stItemInfo.stStdItem.wLooks;
	WORD wReddragon[2] = {966, 976};	// Equip.wil
	
	for ( nCnt = 0; nCnt < 2; nCnt++ )
	{
		if( wLooks == wReddragon[nCnt] )
		{
			CWHWilImageData* pxPrgUse = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE];

			if ( g_dwCurrTime - m_dwReddragonEftTimer > 90 )
			{
				m_dwReddragonEftTimer = g_dwCurrTime;
				m_nReddragonEftIdx++;
				
				if ( m_nReddragonEftIdx > 9 )
					m_nReddragonEftIdx = 0;
			}	

			INT nIdx = m_nReddragonEftIdx;

			if ( g_xGameProc.m_xMyHero.m_stFeature.bGender == _GENDER_MAN )
				nIdx += 900;
			else
				nIdx += 910;

			if ( pxPrgUse->NewSetIndex(nIdx) )
			{
				D3DMATERIAL7	mtrl;
				D3DVECTOR		vecTrans;
				D3DVECTOR		vecScale;

				INT nSX, nSY;
				nSX = m_rcWnd.left+_NEW_USERSTATUS_CHAR_X+pxPrgUse->m_lpstNewCurrWilImageInfo->shPX;
				nSY = m_rcWnd.top +_NEW_USERSTATUS_CHAR_Y+pxPrgUse->m_lpstNewCurrWilImageInfo->shPY;
				
				vecTrans = D3DVECTOR((FLOAT)nSX, (FLOAT)nSY - 6.0f, 0);
				vecScale = D3DVECTOR((FLOAT)pxPrgUse->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxPrgUse->m_lpstNewCurrWilImageInfo->shHeight, 1);
				LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_PROGUSE, nIdx);
				D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)255/255.0f, (FLOAT)255/255.0f);
				mtrl.diffuse.a = (FLOAT)1.0f/255.0f;
				g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr, _BLEND_LIGHT);
			}
			break;
		}
	}

	//-- 신규의복 이펙트

/*
	// 후광있는 옷인가를 확인한다. Wil파일 이미지리스트상에서 확인. (봉황비천의)
	wLooks = m_stEquipItem[_U_DRESS].xItem.m_stItemInfo.stStdItem.wLooks;
	WORD w51Img_2[2] = {985, 995};	// Equip.wil
	WORD wBLightImg51_2[2] = {170, 180};	// ProgUse.wil
	for ( nCnt = 0; nCnt < 2; nCnt++ )
	{
		if( wLooks == w51Img_2[nCnt] )
		{
			CWHWilImageData* pxPrgUse = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE];
			if ( pxPrgUse->NewSetIndex(wBLightImg51_2[nCnt]) )
			{
				D3DMATERIAL7	mtrl;
				D3DVECTOR		vecTrans;
				D3DVECTOR		vecScale;

				INT nSX = m_rcWnd.left+_NEW_EQUIP_CHAR_X+pxPrgUse->m_lpstNewCurrWilImageInfo->shPX;
				INT nSY = m_rcWnd.top +_NEW_EQUIP_CHAR_Y+pxPrgUse->m_lpstNewCurrWilImageInfo->shPY;
				vecTrans = D3DVECTOR((FLOAT)nSX, (FLOAT)nSY, 0);
				vecScale = D3DVECTOR((FLOAT)pxPrgUse->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxPrgUse->m_lpstNewCurrWilImageInfo->shHeight, 1);
				LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_PROGUSE, wBLightImg51_2[nCnt]);
				D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)255/255.0f, (FLOAT)255/255.0f);
				mtrl.diffuse.a = (FLOAT)1.0f/255.0f;
				g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr, _BLEND_LIGHT);
			}
			break;
		}
	}
*/

	// 절대검
	if ( m_stEquipItem[_U_WEAPON].xItem.m_stItemInfo.stStdItem.wLooks == 1076 )
	{
		if ( m_nLastSwordFrame == 0 )
			m_nLastSwordFrame = 420;

		DWORD dwTime = timeGetTime();

		if ( dwTime - m_dwLastSwordTick > 115 )
		{
			 m_nLastSwordFrame++;
			 m_dwLastSwordTick = dwTime;
		}

		if ( m_nLastSwordFrame >= 430 )
			m_nLastSwordFrame = 420;

		CWHWilImageData* pxPrgUse = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE];
		if ( pxPrgUse->NewSetIndex(m_nLastSwordFrame) )
		{
			D3DMATERIAL7	mtrl;
			D3DVECTOR		vecTrans;
			D3DVECTOR		vecScale;

			INT nSX = m_rcWnd.left+_NEW_EQUIP_CHAR_X+pxPrgUse->m_lpstNewCurrWilImageInfo->shPX;
			INT nSY = m_rcWnd.top +_NEW_EQUIP_CHAR_Y+pxPrgUse->m_lpstNewCurrWilImageInfo->shPY;
			vecTrans = D3DVECTOR((FLOAT)nSX, (FLOAT)nSY, 0);
			vecScale = D3DVECTOR((FLOAT)pxPrgUse->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxPrgUse->m_lpstNewCurrWilImageInfo->shHeight, 1);
			LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_PROGUSE, m_nLastSwordFrame);
			D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)180/255.0f, (FLOAT)100/255.0f);
			mtrl.diffuse.a = (FLOAT)1.0f/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr, _BLEND_LIGHT);
		}
	}


/*
	nImgIdx = 2090 + m_nSwordEftIdx;

	if ( g_dwCurrTime - m_dwSwordEftTimer > 100 )
	{
		m_dwSwordEftTimer = g_dwCurrTime;
		m_nSwordEftIdx++;

		if ( m_nSwordEftIdx > 9 )
			m_nSwordEftIdx = 0;
	}

	nStX = 144;
	nStY = 222;
	
	if ( 1 )
	{
		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(nImgIdx) )
		{
			D3DMATERIAL7	mtrl;
			D3DVECTOR		vecTrans;
			D3DVECTOR		vecScale;

			int NTEST = g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shPY;

			INT nSX = m_rcWnd.left+nStX+g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shPX;
			INT nSY = m_rcWnd.top +nStY+g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shPY;
			vecTrans = D3DVECTOR((FLOAT)nSX, (FLOAT)nSY, 0);
			vecScale = D3DVECTOR((FLOAT)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight, 1);
			LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_INTER, nImgIdx);
			D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)255/255.0f, (FLOAT)255/255.0f);
			mtrl.diffuse.a = (FLOAT)1.0f/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr, _BLEND_LIGHT);
		}
	}
*/

	// 머리종류.
	if ( g_xGameProc.m_xMyHero.m_stFeature.bHair > 0 && g_xGameProc.m_xMyHero.m_stFeature.bHair <= 10 && !m_stEquipItem[_U_HELMET].bSetted )
	{
		BYTE bHair = (BYTE)(g_xGameProc.m_xMyHero.m_stFeature.bGender*10 + (g_xGameProc.m_xMyHero.m_stFeature.bHair-1) + 60);

		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].NewSetIndex(bHair) )
		{
			g_xMainWnd.DrawWithImageForComp(
							m_rcWnd.left+_NEW_EQUIP_CHAR_X+g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shPX, 
							m_rcWnd.top+_NEW_EQUIP_CHAR_Y+g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shPY, 
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shWidth, 
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shHeight,
							(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_pbCurrImage), 
							g_xGameProc.m_xMyHero.m_stFeatureEx.wHairColor, 0XFFFF);
		}
	}

	// 후광있는 옷인가를 확인한다. Wil파일 이미지리스트상에서 확인. (귀령신갑)
	wLooks = m_stEquipItem[_U_DRESS].xItem.m_stItemInfo.stStdItem.wLooks;
	WORD w58Img[2] = {986, 996};	// Equip.wil
	WORD wBLightImg58[2] = {281, 291};	// ProgUse.wil

	switch ( g_xGameProc.m_xMyHero.m_bJob )
	{
	case _JOB_JUNSA:
		wBLightImg58[0] = 280;
		wBLightImg58[1] = 290;
		break;
	case _JOB_SULSA:
		wBLightImg58[0] = 281;
		wBLightImg58[1] = 291;
		break;
	case _JOB_DOSA:
		wBLightImg58[0] = 282;
		wBLightImg58[1] = 292;
		break;
	}

	for ( nCnt = 0; nCnt < 2; nCnt++ )
	{
		if( wLooks == w58Img[nCnt] )
		{
			CWHWilImageData* pxPrgUse = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE];
			if ( pxPrgUse->NewSetIndex(wBLightImg58[nCnt]) )
			{
				D3DMATERIAL7	mtrl;
				D3DVECTOR		vecTrans;
				D3DVECTOR		vecScale;

				INT nSX = m_rcWnd.left+_NEW_EQUIP_CHAR_X+pxPrgUse->m_lpstNewCurrWilImageInfo->shPX;
				INT nSY = m_rcWnd.top +_NEW_EQUIP_CHAR_Y+pxPrgUse->m_lpstNewCurrWilImageInfo->shPY;
				vecTrans = D3DVECTOR((FLOAT)nSX, (FLOAT)nSY, 0);
				vecScale = D3DVECTOR((FLOAT)pxPrgUse->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxPrgUse->m_lpstNewCurrWilImageInfo->shHeight, 1);
				LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_PROGUSE, wBLightImg58[nCnt]);
				D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)255/255.0f, (FLOAT)255/255.0f);
				mtrl.diffuse.a = (FLOAT)1.0f/255.0f;
				g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr, _BLEND_LIGHT);
			}
			break;
		}
	}

	CHAR	szBuff[MAX_PATH];

	POINT	ptStart = {m_rcWnd.left+276, m_rcWnd.top+160};
	RECT	rcText = {m_rcWnd.left+246, m_rcWnd.top+159, m_rcWnd.left+275, m_rcWnd.top+174};
	RECT	rcTextRight = {m_rcWnd.left+282, m_rcWnd.top+159, m_rcWnd.left+312, m_rcWnd.top+174}, rcTextCenter = {m_rcWnd.left+245, m_rcWnd.top+111, m_rcWnd.left+312, m_rcWnd.top+126};

	for ( nI=0; nI<9; nI++)
	{
		SetRect(&m_rcAbility[nI], m_rcWnd.left+220, m_rcWnd.top + 106 + 24*nI, m_rcWnd.left+316, m_rcWnd.top+128 + 24*nI);
	}

	sprintf(szBuff, "%d", g_xGameProc.m_xMyHero.m_stAbility.bLevel);
	g_xMainWnd.PutsHan(NULL, rcTextCenter, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	rcTextCenter.top += 24;
	rcTextCenter.bottom += 24;

	DOUBLE dExpRate = 0;

	if ( g_xGameProc.m_xMyHero.m_stAbility.dlngMaxExp != 0 )
	{
		dExpRate = ((DOUBLE)(LONGLONG)g_xGameProc.m_xMyHero.m_stAbility.dlngExp/(DOUBLE)(LONGLONG)g_xGameProc.m_xMyHero.m_stAbility.dlngMaxExp);		
		if ( dExpRate < 0 )
			dExpRate = 0;
	}
	sprintf(szBuff, "%.2f%s", dExpRate*100, "%");
	g_xMainWnd.PutsHan(NULL, rcTextCenter, RGB(255, 0, 0), RGB(0, 0, 0), szBuff);

	sprintf(szBuff, "%d", g_xGameProc.m_xMyHero.m_stAbility.wHP);
	g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);
	sprintf(szBuff, "/");
	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);
	sprintf(szBuff, "%d", g_xGameProc.m_xMyHero.m_stAbility.wMaxHP);
	g_xMainWnd.PutsHan(NULL, rcTextRight, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	rcText.top += 24;
	rcText.bottom += 24;
	rcTextRight.top += 24;
	rcTextRight.bottom += 24;
	ptStart.y += 24;
	sprintf(szBuff, "%d", g_xGameProc.m_xMyHero.m_stAbility.wMP);
	g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);
	sprintf(szBuff, "/");
	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);
	sprintf(szBuff, "%d", g_xGameProc.m_xMyHero.m_stAbility.wMaxMP);
	g_xMainWnd.PutsHan(NULL, rcTextRight, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	rcText.top += 24;
	rcText.bottom += 24;
	rcTextRight.top += 24;
	rcTextRight.bottom += 24;
	ptStart.y += 24;
	sprintf(szBuff, "%d", g_xGameProc.m_xMyHero.m_stAbility.wWeight);
	g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);
	sprintf(szBuff, "/");
	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);
	sprintf(szBuff, "%d", g_xGameProc.m_xMyHero.m_stAbility.wMaxWeight);
	g_xMainWnd.PutsHan(NULL, rcTextRight, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	rcText.top += 24;
	rcText.bottom += 24;
	rcTextRight.top += 24;
	rcTextRight.bottom += 24;
	ptStart.y += 24;
	sprintf(szBuff, "%d", g_xGameProc.m_xMyHero.m_stAbility.bWearWeight);
	g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);
	sprintf(szBuff, "/");
	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);
	sprintf(szBuff, "%d", g_xGameProc.m_xMyHero.m_stAbility.bMaxWearWeight);
	g_xMainWnd.PutsHan(NULL, rcTextRight, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	rcText.top += 24;
	rcText.bottom += 24;
	rcTextRight.top += 24;
	rcTextRight.bottom += 24;
	ptStart.y += 24;
	sprintf(szBuff, "%d", g_xGameProc.m_xMyHero.m_stAbility.bHandWeight);
	g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);
	sprintf(szBuff, "/");
	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);
	sprintf(szBuff, "%d", g_xGameProc.m_xMyHero.m_stAbility.bMaxHandWeight);
	g_xMainWnd.PutsHan(NULL, rcTextRight, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	rcTextCenter.top += 144;
	rcTextCenter.bottom += 144;
	sprintf(szBuff, "+%d%", g_xGameProc.m_xMyHero.m_stSubAbility.bHitPoint);
	g_xMainWnd.PutsHan(NULL, rcTextCenter, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	rcTextCenter.top += 24;
	rcTextCenter.bottom += 24;
	sprintf(szBuff, "+%d%", g_xGameProc.m_xMyHero.m_stSubAbility.bSpeedPoint);
	g_xMainWnd.PutsHan(NULL, rcTextCenter, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	rcText.left = m_rcWnd.left+11;
	rcText.right = m_rcWnd.left+69;
	rcText.top = m_rcWnd.top+342;
	rcText.bottom = m_rcWnd.top+357;

	// 파괴
	sprintf(szBuff, "%s", g_xMsg.GetMsg(1061));
	g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	rcText.left += 47;
	rcText.right += 47;

	sprintf(szBuff, "%d-%d", LOWORD(g_xGameProc.m_xMyHero.m_stAbility.dwDC), HIWORD(g_xGameProc.m_xMyHero.m_stAbility.dwDC));
	if (m_bCheckShow[0])
		g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 128,   0), RGB(0, 0, 0), szBuff);
	else
		g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	rcText.left = m_rcWnd.left+13;
	rcText.right = m_rcWnd.left+71;
	rcText.top += 25;
	rcText.bottom += 25;

	// 자연계마법
	sprintf(szBuff, "%s", g_xMsg.GetMsg(5101));
	g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	rcText.left += 47;
	rcText.right += 47;

	sprintf(szBuff, "%d-%d", LOWORD(g_xGameProc.m_xMyHero.m_stAbility.dwMC), HIWORD(g_xGameProc.m_xMyHero.m_stAbility.dwMC));
	if (m_bCheckShow[2])
		g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 128,   0), RGB(0, 0, 0), szBuff);
	else
		g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);
	
	rcText.left = m_rcWnd.left+118;
	rcText.right = m_rcWnd.left+178;

	// 영혼계마법
	sprintf(szBuff, "%s", g_xMsg.GetMsg(5102));
	g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	rcText.left += 45;
	rcText.right += 45;

	sprintf(szBuff, "%d-%d", LOWORD(g_xGameProc.m_xMyHero.m_stAbility.dwSC), HIWORD(g_xGameProc.m_xMyHero.m_stAbility.dwSC));
	if (m_bCheckShow[3])
		g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 128,   0), RGB(0, 0, 0), szBuff);
	else
		g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	rcText.left = m_rcWnd.left+118;
	rcText.right = m_rcWnd.left+178;
	rcText.top = m_rcWnd.top+342;
	rcText.bottom = m_rcWnd.top+357;

	// 방어
	sprintf(szBuff, "%s", g_xMsg.GetMsg(1060));
	g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	rcText.left += 45;
	rcText.right += 45;

	sprintf(szBuff, "%d-%d", LOBYTE(g_xGameProc.m_xMyHero.m_stAbility.wAC), HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.wAC));
	if (m_bCheckShow[1])
		g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 128,   0), RGB(0, 0, 0), szBuff);
	else
		g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	rcText.left = m_rcWnd.left+218;
	rcText.right = m_rcWnd.left+278;
	rcText.top = m_rcWnd.top+367;
	rcText.bottom = m_rcWnd.top+382;

	// 마법방어
	sprintf(szBuff, "%s", g_xMsg.GetMsg(1406));
	g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	rcText.left += 52;
	rcText.right += 52;

	sprintf(szBuff, "%d-%d", LOBYTE(g_xGameProc.m_xMyHero.m_stAbility.wMAC), HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.wMAC));
	if (m_bCheckShow[4])
		g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 128,   0), RGB(0, 0, 0), szBuff);
	else
		g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	rcText.left = m_rcWnd.left+11;
	rcText.right = m_rcWnd.left+61;
	rcText.top = m_rcWnd.top+390;
	rcText.bottom = m_rcWnd.top+405;

	sprintf(szBuff, "%s", g_xMsg.GetMsg(5178));
	g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);
	//	공격원소

	rcText.top = m_rcWnd.top + 390;
	rcText.bottom = rcText.top + 15;

	if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[6]) > 0 )
	{
		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(1516) )
		{
 			g_xMainWnd.DrawWithImageForComp(
							m_rcWnd.left + 285, m_rcWnd.top + 386,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
							(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage));
		}

		rcText.left = m_rcWnd.left + 303;
		rcText.right = rcText.left + 20;

		sprintf(szBuff, "+%d", HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[6]));
		if (m_bCheckShow[11])
			g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 128,   0), RGB(0, 0, 0), szBuff);
		else
			g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

		if ( PtInRect(&m_rcAtomTooltip[0][6], g_xGameProc.m_ptMousePos) )
		{
			RECT	rcToolTip;
			sprintf(szBuff, "%s", g_xMsg.GetMsg(5167));
			SetRect(&rcToolTip, m_rcAtomTooltip[0][6].left + 10, m_rcAtomTooltip[0][6].top - 10, m_rcAtomTooltip[0][6].right + 35 , m_rcAtomTooltip[0][6].bottom - 5);
			D3DMATERIAL7 mtrl;
			D3DVECTOR	vecTrans((FLOAT)rcToolTip.left, (FLOAT)rcToolTip.top, 0);
			D3DVECTOR	vecScale((FLOAT)rcToolTip.right-rcToolTip.left, rcToolTip.bottom-rcToolTip.top, 1);

			D3DUtil_InitMaterial(mtrl, (FLOAT)80/255.0f, (FLOAT)60/255.0f, (FLOAT)40/255.0f);
			mtrl.diffuse.a = 150.0f/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

			g_xMainWnd.PutsHan(NULL, rcToolTip, RGB(255, 255, 255), RGB(0, 0, 0), szBuff, NULL);
			g_xMainWnd.DrawWithGDI(&rcToolTip, NULL, RGB(100, 75, 50), 1);
		}
	}

	if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[5]) > 0 )
	{
		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(1515) )
		{
 			g_xMainWnd.DrawWithImageForComp(
							m_rcWnd.left + 248, m_rcWnd.top + 386,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
							(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage));
		}

		rcText.left = m_rcWnd.left + 266;
		rcText.right = rcText.left + 20;

		sprintf(szBuff, "+%d", HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[5]));
		if (m_bCheckShow[10])
			g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 128,   0), RGB(0, 0, 0), szBuff);
		else
			g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

		if ( PtInRect(&m_rcAtomTooltip[0][5], g_xGameProc.m_ptMousePos) )
		{
			RECT	rcToolTip;
			sprintf(szBuff, "%s", g_xMsg.GetMsg(5166));
			SetRect(&rcToolTip, m_rcAtomTooltip[0][5].left + 10, m_rcAtomTooltip[0][5].top - 10, m_rcAtomTooltip[0][5].right + 35 , m_rcAtomTooltip[0][5].bottom - 10);
			D3DMATERIAL7 mtrl;
			D3DVECTOR	vecTrans((FLOAT)rcToolTip.left, (FLOAT)rcToolTip.top, 0);
			D3DVECTOR	vecScale((FLOAT)rcToolTip.right-rcToolTip.left, rcToolTip.bottom-rcToolTip.top, 1);

			D3DUtil_InitMaterial(mtrl, (FLOAT)80/255.0f, (FLOAT)60/255.0f, (FLOAT)40/255.0f);
			mtrl.diffuse.a = 150.0f/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

			g_xMainWnd.PutsHan(NULL, rcToolTip, RGB(255, 255, 255), RGB(0, 0, 0), szBuff, NULL);
			g_xMainWnd.DrawWithGDI(&rcToolTip, NULL, RGB(100, 75, 50), 1);
		}
	}

	if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[4]) > 0 )
	{
		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(1514) )
		{
 			g_xMainWnd.DrawWithImageForComp(
							m_rcWnd.left + 211, m_rcWnd.top + 386,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
							(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage));
		}

		rcText.left = m_rcWnd.left + 229;
		rcText.right = rcText.left + 20;

		sprintf(szBuff, "+%d", HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[4]));
		if (m_bCheckShow[9])
			g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 128,   0), RGB(0, 0, 0), szBuff);
		else
			g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

		if ( PtInRect(&m_rcAtomTooltip[0][4], g_xGameProc.m_ptMousePos) )
		{
			RECT	rcToolTip;
			sprintf(szBuff, "%s", g_xMsg.GetMsg(5165));
			SetRect(&rcToolTip, m_rcAtomTooltip[0][4].left + 10, m_rcAtomTooltip[0][4].top - 10, m_rcAtomTooltip[0][4].right + 35 , m_rcAtomTooltip[0][4].bottom - 5);
			D3DMATERIAL7 mtrl;
			D3DVECTOR	vecTrans((FLOAT)rcToolTip.left, (FLOAT)rcToolTip.top, 0);
			D3DVECTOR	vecScale((FLOAT)rcToolTip.right-rcToolTip.left, rcToolTip.bottom-rcToolTip.top, 1);

			D3DUtil_InitMaterial(mtrl, (FLOAT)80/255.0f, (FLOAT)60/255.0f, (FLOAT)40/255.0f);
			mtrl.diffuse.a = 150.0f/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

			g_xMainWnd.PutsHan(NULL, rcToolTip, RGB(255, 255, 255), RGB(0, 0, 0), szBuff, NULL);
			g_xMainWnd.DrawWithGDI(&rcToolTip, NULL, RGB(100, 75, 50), 1);
		}
	}

	if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[3]) > 0 )
	{
		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(1513) )
		{
 			g_xMainWnd.DrawWithImageForComp(
							m_rcWnd.left + 174, m_rcWnd.top + 386,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
							(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage));
		}

		rcText.left = m_rcWnd.left + 192;
		rcText.right = rcText.left + 20;

		sprintf(szBuff, "+%d", HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[3]));
		if (m_bCheckShow[8])
			g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 128,   0), RGB(0, 0, 0), szBuff);
		else
			g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

		if ( PtInRect(&m_rcAtomTooltip[0][3], g_xGameProc.m_ptMousePos) )
		{
			RECT	rcToolTip;
			sprintf(szBuff, "%s", g_xMsg.GetMsg(5164));
			SetRect(&rcToolTip, m_rcAtomTooltip[0][3].left + 10, m_rcAtomTooltip[0][3].top - 10, m_rcAtomTooltip[0][3].right + 35 , m_rcAtomTooltip[0][3].bottom - 10);
			D3DMATERIAL7 mtrl;
			D3DVECTOR	vecTrans((FLOAT)rcToolTip.left, (FLOAT)rcToolTip.top, 0);
			D3DVECTOR	vecScale((FLOAT)rcToolTip.right-rcToolTip.left, rcToolTip.bottom-rcToolTip.top, 1);

			D3DUtil_InitMaterial(mtrl, (FLOAT)80/255.0f, (FLOAT)60/255.0f, (FLOAT)40/255.0f);
			mtrl.diffuse.a = 150.0f/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

			g_xMainWnd.PutsHan(NULL, rcToolTip, RGB(255, 255, 255), RGB(0, 0, 0), szBuff, NULL);
			g_xMainWnd.DrawWithGDI(&rcToolTip, NULL, RGB(100, 75, 50), 1);
		}
	}

	if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[2]) > 0 )
	{
		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(1512) )
		{
 			g_xMainWnd.DrawWithImageForComp(
							m_rcWnd.left + 137, m_rcWnd.top + 386,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
							(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage));
		}

		rcText.left = m_rcWnd.left + 155;
		rcText.right = rcText.left + 20;

		sprintf(szBuff, "+%d", HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[2]));
		if (m_bCheckShow[7])
			g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 128,   0), RGB(0, 0, 0), szBuff);
		else
			g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

		if ( PtInRect(&m_rcAtomTooltip[0][2], g_xGameProc.m_ptMousePos) )
		{
			RECT	rcToolTip;
			sprintf(szBuff, "%s", g_xMsg.GetMsg(5163));
			SetRect(&rcToolTip, m_rcAtomTooltip[0][2].left + 10, m_rcAtomTooltip[0][2].top - 10, m_rcAtomTooltip[0][2].right + 35 , m_rcAtomTooltip[0][2].bottom - 10);
			D3DMATERIAL7 mtrl;
			D3DVECTOR	vecTrans((FLOAT)rcToolTip.left, (FLOAT)rcToolTip.top, 0);
			D3DVECTOR	vecScale((FLOAT)rcToolTip.right-rcToolTip.left, rcToolTip.bottom-rcToolTip.top, 1);

			D3DUtil_InitMaterial(mtrl, (FLOAT)80/255.0f, (FLOAT)60/255.0f, (FLOAT)40/255.0f);
			mtrl.diffuse.a = 150.0f/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

			g_xMainWnd.PutsHan(NULL, rcToolTip, RGB(255, 255, 255), RGB(0, 0, 0), szBuff, NULL);
			g_xMainWnd.DrawWithGDI(&rcToolTip, NULL, RGB(100, 75, 50), 1);
		}
	}

	if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[1]) > 0 )
	{
		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(1511) )
		{
 			g_xMainWnd.DrawWithImageForComp(
							m_rcWnd.left + 100, m_rcWnd.top + 386,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
							(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage));
		}
		rcText.left = m_rcWnd.left + 118;
		rcText.right = rcText.left + 20;

		sprintf(szBuff, "+%d", HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[1]));
		if (m_bCheckShow[6])
			g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 128,   0), RGB(0, 0, 0), szBuff);
		else
			g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

		if ( PtInRect(&m_rcAtomTooltip[0][1], g_xGameProc.m_ptMousePos) )
		{
			RECT	rcToolTip;
			sprintf(szBuff, "%s", g_xMsg.GetMsg(5162));
			SetRect(&rcToolTip, m_rcAtomTooltip[0][1].left + 10, m_rcAtomTooltip[0][1].top - 10, m_rcAtomTooltip[0][1].right + 35 , m_rcAtomTooltip[0][1].bottom - 10);
			D3DMATERIAL7 mtrl;
			D3DVECTOR	vecTrans((FLOAT)rcToolTip.left, (FLOAT)rcToolTip.top, 0);
			D3DVECTOR	vecScale((FLOAT)rcToolTip.right-rcToolTip.left, rcToolTip.bottom-rcToolTip.top, 1);

			D3DUtil_InitMaterial(mtrl, (FLOAT)80/255.0f, (FLOAT)60/255.0f, (FLOAT)40/255.0f);
			mtrl.diffuse.a = 150.0f/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

			g_xMainWnd.PutsHan(NULL, rcToolTip, RGB(255, 255, 255), RGB(0, 0, 0), szBuff, NULL);
			g_xMainWnd.DrawWithGDI(&rcToolTip, NULL, RGB(100, 75, 50), 1);
		}
	}

	if ( HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[0]) > 0)
	{
		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(1510) )
		{
 			g_xMainWnd.DrawWithImageForComp(
							m_rcWnd.left + 63, m_rcWnd.top + 386,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
							(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage));
		}
		rcText.left = m_rcWnd.left + 81;
		rcText.right = rcText.left + 20;

		sprintf(szBuff, "+%d", HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[0]));
		if (m_bCheckShow[5])
			g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 128,   0), RGB(0, 0, 0), szBuff);
		else
			g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

		if ( PtInRect(&m_rcAtomTooltip[0][0], g_xGameProc.m_ptMousePos) )
		{
			RECT	rcToolTip;
			sprintf(szBuff, "%s", g_xMsg.GetMsg(5161));
			SetRect(&rcToolTip, m_rcAtomTooltip[0][0].left + 10, m_rcAtomTooltip[0][0].top - 10, m_rcAtomTooltip[0][0].right + 35 , m_rcAtomTooltip[0][0].bottom - 10);
			D3DMATERIAL7 mtrl;
			D3DVECTOR	vecTrans((FLOAT)rcToolTip.left, (FLOAT)rcToolTip.top, 0);
			D3DVECTOR	vecScale((FLOAT)rcToolTip.right-rcToolTip.left, rcToolTip.bottom-rcToolTip.top, 1);

			D3DUtil_InitMaterial(mtrl, (FLOAT)80/255.0f, (FLOAT)60/255.0f, (FLOAT)40/255.0f);
			mtrl.diffuse.a = 150.0f/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

			g_xMainWnd.PutsHan(NULL, rcToolTip, RGB(255, 255, 255), RGB(0, 0, 0), szBuff, NULL);
			g_xMainWnd.DrawWithGDI(&rcToolTip, NULL, RGB(100, 75, 50), 1);
		}
	}

	rcText.left = m_rcWnd.left+11;
	rcText.right = m_rcWnd.left+61;
	rcText.top = m_rcWnd.top+414;
	rcText.bottom = m_rcWnd.top+429;
	
	sprintf(szBuff, "%s", g_xMsg.GetMsg(5179));
	g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);
	//  강한원소

	rcText.top = m_rcWnd.top + 415;
	rcText.bottom = rcText.top + 15;

	if ( g_xGameProc.m_xMyHero.m_stAbility.ATOM_AC_GOOD[6] > 0 )
	{
		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(1516) )
		{
 			g_xMainWnd.DrawWithImageForComp(
							m_rcWnd.left + 285, m_rcWnd.top + 411,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
							(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage));
		}

		rcText.left = m_rcWnd.left + 303;
		rcText.right = rcText.left + 20;
		sprintf(szBuff, "x%d", g_xGameProc.m_xMyHero.m_stAbility.ATOM_AC_GOOD[6]);
		if (m_bCheckShow[18])
			g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 128,   0), RGB(0, 0, 0), szBuff);
		else
			g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

		if ( PtInRect(&m_rcAtomTooltip[1][6], g_xGameProc.m_ptMousePos) )
		{
			RECT	rcToolTip;
			sprintf(szBuff, "%s", g_xMsg.GetMsg(5167));
			SetRect(&rcToolTip, m_rcAtomTooltip[1][6].left + 10, m_rcAtomTooltip[1][6].top - 10, m_rcAtomTooltip[1][6].right + 35 , m_rcAtomTooltip[1][6].bottom - 10);
			D3DMATERIAL7 mtrl;
			D3DVECTOR	vecTrans((FLOAT)rcToolTip.left, (FLOAT)rcToolTip.top, 0);
			D3DVECTOR	vecScale((FLOAT)rcToolTip.right-rcToolTip.left, rcToolTip.bottom-rcToolTip.top, 1);

			D3DUtil_InitMaterial(mtrl, (FLOAT)80/255.0f, (FLOAT)60/255.0f, (FLOAT)40/255.0f);
			mtrl.diffuse.a = 150.0f/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

			g_xMainWnd.PutsHan(NULL, rcToolTip, RGB(255, 255, 255), RGB(0, 0, 0), szBuff, NULL);
			g_xMainWnd.DrawWithGDI(&rcToolTip, NULL, RGB(100, 75, 50), 1);
		}
	}

	if ( g_xGameProc.m_xMyHero.m_stAbility.ATOM_AC_GOOD[5] > 0 )
	{
		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(1515) )
		{
 			g_xMainWnd.DrawWithImageForComp(
							m_rcWnd.left + 248, m_rcWnd.top + 411,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
							(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage));
		}

		rcText.left = m_rcWnd.left + 266;
		rcText.right = rcText.left + 20;
		sprintf(szBuff, "x%d", g_xGameProc.m_xMyHero.m_stAbility.ATOM_AC_GOOD[5]);
		if (m_bCheckShow[17])
			g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 128,   0), RGB(0, 0, 0), szBuff);
		else
			g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

		if ( PtInRect(&m_rcAtomTooltip[1][5], g_xGameProc.m_ptMousePos) )
		{
			RECT	rcToolTip;
			sprintf(szBuff, "%s", g_xMsg.GetMsg(5166));
			SetRect(&rcToolTip, m_rcAtomTooltip[1][5].left + 10, m_rcAtomTooltip[1][5].top - 10, m_rcAtomTooltip[1][5].right + 35 , m_rcAtomTooltip[1][5].bottom - 10);
			D3DMATERIAL7 mtrl;
			D3DVECTOR	vecTrans((FLOAT)rcToolTip.left, (FLOAT)rcToolTip.top, 0);
			D3DVECTOR	vecScale((FLOAT)rcToolTip.right-rcToolTip.left, rcToolTip.bottom-rcToolTip.top, 1);

			D3DUtil_InitMaterial(mtrl, (FLOAT)80/255.0f, (FLOAT)60/255.0f, (FLOAT)40/255.0f);
			mtrl.diffuse.a = 150.0f/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

			g_xMainWnd.PutsHan(NULL, rcToolTip, RGB(255, 255, 255), RGB(0, 0, 0), szBuff, NULL);
			g_xMainWnd.DrawWithGDI(&rcToolTip, NULL, RGB(100, 75, 50), 1);
		}
	}

	if ( g_xGameProc.m_xMyHero.m_stAbility.ATOM_AC_GOOD[4] > 0 )
	{
		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(1514) )
		{
 			g_xMainWnd.DrawWithImageForComp(
							m_rcWnd.left + 211, m_rcWnd.top + 411,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
							(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage));
		}

		rcText.left = m_rcWnd.left + 229;
		rcText.right = rcText.left + 20;
		sprintf(szBuff, "x%d", g_xGameProc.m_xMyHero.m_stAbility.ATOM_AC_GOOD[4]);
		if (m_bCheckShow[16])
			g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 128,   0), RGB(0, 0, 0), szBuff);
		else
			g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

		if ( PtInRect(&m_rcAtomTooltip[1][4], g_xGameProc.m_ptMousePos) )
		{
			RECT	rcToolTip;
			sprintf(szBuff, "%s", g_xMsg.GetMsg(5165));
			SetRect(&rcToolTip, m_rcAtomTooltip[1][4].left + 10, m_rcAtomTooltip[1][4].top - 10, m_rcAtomTooltip[1][4].right + 35 , m_rcAtomTooltip[1][4].bottom - 10);
			D3DMATERIAL7 mtrl;
			D3DVECTOR	vecTrans((FLOAT)rcToolTip.left, (FLOAT)rcToolTip.top, 0);
			D3DVECTOR	vecScale((FLOAT)rcToolTip.right-rcToolTip.left, rcToolTip.bottom-rcToolTip.top, 1);

			D3DUtil_InitMaterial(mtrl, (FLOAT)80/255.0f, (FLOAT)60/255.0f, (FLOAT)40/255.0f);
			mtrl.diffuse.a = 150.0f/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

			g_xMainWnd.PutsHan(NULL, rcToolTip, RGB(255, 255, 255), RGB(0, 0, 0), szBuff, NULL);
			g_xMainWnd.DrawWithGDI(&rcToolTip, NULL, RGB(100, 75, 50), 1);
		}
	}

	if ( g_xGameProc.m_xMyHero.m_stAbility.ATOM_AC_GOOD[3] > 0 )
	{
		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(1513) )
		{
 			g_xMainWnd.DrawWithImageForComp(
							m_rcWnd.left + 174, m_rcWnd.top + 411,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
							(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage));
		}

		rcText.left = m_rcWnd.left + 192;
		rcText.right = rcText.left + 20;
		sprintf(szBuff, "x%d", g_xGameProc.m_xMyHero.m_stAbility.ATOM_AC_GOOD[3]);
		if (m_bCheckShow[15])
			g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 128,   0), RGB(0, 0, 0), szBuff);
		else
			g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

		if ( PtInRect(&m_rcAtomTooltip[1][3], g_xGameProc.m_ptMousePos) )
		{
			RECT	rcToolTip;
			sprintf(szBuff, "%s", g_xMsg.GetMsg(5164));
			SetRect(&rcToolTip, m_rcAtomTooltip[1][3].left + 10, m_rcAtomTooltip[1][3].top - 10, m_rcAtomTooltip[1][3].right + 35 , m_rcAtomTooltip[1][3].bottom - 10);
			D3DMATERIAL7 mtrl;
			D3DVECTOR	vecTrans((FLOAT)rcToolTip.left, (FLOAT)rcToolTip.top, 0);
			D3DVECTOR	vecScale((FLOAT)rcToolTip.right-rcToolTip.left, rcToolTip.bottom-rcToolTip.top, 1);

			D3DUtil_InitMaterial(mtrl, (FLOAT)80/255.0f, (FLOAT)60/255.0f, (FLOAT)40/255.0f);
			mtrl.diffuse.a = 150.0f/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

			g_xMainWnd.PutsHan(NULL, rcToolTip, RGB(255, 255, 255), RGB(0, 0, 0), szBuff, NULL);
			g_xMainWnd.DrawWithGDI(&rcToolTip, NULL, RGB(100, 75, 50), 1);
		}
	}

	if ( g_xGameProc.m_xMyHero.m_stAbility.ATOM_AC_GOOD[2] > 0 )
	{
		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(1512) )
		{
 			g_xMainWnd.DrawWithImageForComp(
							m_rcWnd.left + 137, m_rcWnd.top + 411,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
							(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage));
		}

		rcText.left = m_rcWnd.left + 155;
		rcText.right = rcText.left + 20;
		sprintf(szBuff, "x%d", g_xGameProc.m_xMyHero.m_stAbility.ATOM_AC_GOOD[2]);
		if (m_bCheckShow[14])
			g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 128,   0), RGB(0, 0, 0), szBuff);
		else
			g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

		if ( PtInRect(&m_rcAtomTooltip[1][2], g_xGameProc.m_ptMousePos) )
		{
			RECT	rcToolTip;
			sprintf(szBuff, "%s", g_xMsg.GetMsg(5163));
			SetRect(&rcToolTip, m_rcAtomTooltip[1][2].left + 10, m_rcAtomTooltip[1][2].top - 10, m_rcAtomTooltip[1][2].right + 35 , m_rcAtomTooltip[1][2].bottom - 10);
			D3DMATERIAL7 mtrl;
			D3DVECTOR	vecTrans((FLOAT)rcToolTip.left, (FLOAT)rcToolTip.top, 0);
			D3DVECTOR	vecScale((FLOAT)rcToolTip.right-rcToolTip.left, rcToolTip.bottom-rcToolTip.top, 1);

			D3DUtil_InitMaterial(mtrl, (FLOAT)80/255.0f, (FLOAT)60/255.0f, (FLOAT)40/255.0f);
			mtrl.diffuse.a = 150.0f/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

			g_xMainWnd.PutsHan(NULL, rcToolTip, RGB(255, 255, 255), RGB(0, 0, 0), szBuff, NULL);
			g_xMainWnd.DrawWithGDI(&rcToolTip, NULL, RGB(100, 75, 50), 1);
		}
	}

	if ( g_xGameProc.m_xMyHero.m_stAbility.ATOM_AC_GOOD[1] > 0 )
	{
		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(1511) )
		{
 			g_xMainWnd.DrawWithImageForComp(
							m_rcWnd.left + 100, m_rcWnd.top + 411,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
							(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage));
		}

		rcText.left = m_rcWnd.left + 118;
		rcText.right = rcText.left + 20;
		sprintf(szBuff, "x%d", g_xGameProc.m_xMyHero.m_stAbility.ATOM_AC_GOOD[1]);
		if (m_bCheckShow[13])
			g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 128,   0), RGB(0, 0, 0), szBuff);
		else
			g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

		if ( PtInRect(&m_rcAtomTooltip[1][1], g_xGameProc.m_ptMousePos) )
		{
			RECT	rcToolTip;
			sprintf(szBuff, "%s", g_xMsg.GetMsg(5162));
			SetRect(&rcToolTip, m_rcAtomTooltip[1][1].left + 10, m_rcAtomTooltip[1][1].top - 10, m_rcAtomTooltip[1][1].right + 35 , m_rcAtomTooltip[1][1].bottom - 10);
			D3DMATERIAL7 mtrl;
			D3DVECTOR	vecTrans((FLOAT)rcToolTip.left, (FLOAT)rcToolTip.top, 0);
			D3DVECTOR	vecScale((FLOAT)rcToolTip.right-rcToolTip.left, rcToolTip.bottom-rcToolTip.top, 1);

			D3DUtil_InitMaterial(mtrl, (FLOAT)80/255.0f, (FLOAT)60/255.0f, (FLOAT)40/255.0f);
			mtrl.diffuse.a = 150.0f/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

			g_xMainWnd.PutsHan(NULL, rcToolTip, RGB(255, 255, 255), RGB(0, 0, 0), szBuff, NULL);
			g_xMainWnd.DrawWithGDI(&rcToolTip, NULL, RGB(100, 75, 50), 1);
		}
	}

	if ( g_xGameProc.m_xMyHero.m_stAbility.ATOM_AC_GOOD[0] > 0 )
	{
		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(1510) )
		{
 			g_xMainWnd.DrawWithImageForComp(
							m_rcWnd.left + 63, m_rcWnd.top + 411,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
							(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage));
		}
		rcText.left = m_rcWnd.left + 81;
		rcText.right = rcText.left + 20;
		sprintf(szBuff, "x%d", g_xGameProc.m_xMyHero.m_stAbility.ATOM_AC_GOOD[0]);
		if (m_bCheckShow[12])
			g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 128,   0), RGB(0, 0, 0), szBuff);
		else
			g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

		if ( PtInRect(&m_rcAtomTooltip[1][0], g_xGameProc.m_ptMousePos) )
		{
			RECT	rcToolTip;
			sprintf(szBuff, "%s", g_xMsg.GetMsg(5161));
			SetRect(&rcToolTip, m_rcAtomTooltip[1][0].left + 10, m_rcAtomTooltip[1][0].top - 10, m_rcAtomTooltip[1][0].right + 35 , m_rcAtomTooltip[1][0].bottom - 10);
			D3DMATERIAL7 mtrl;
			D3DVECTOR	vecTrans((FLOAT)rcToolTip.left, (FLOAT)rcToolTip.top, 0);
			D3DVECTOR	vecScale((FLOAT)rcToolTip.right-rcToolTip.left, rcToolTip.bottom-rcToolTip.top, 1);

			D3DUtil_InitMaterial(mtrl, (FLOAT)80/255.0f, (FLOAT)60/255.0f, (FLOAT)40/255.0f);
			mtrl.diffuse.a = 150.0f/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

			g_xMainWnd.PutsHan(NULL, rcToolTip, RGB(255, 255, 255), RGB(0, 0, 0), szBuff, NULL);
			g_xMainWnd.DrawWithGDI(&rcToolTip, NULL, RGB(100, 75, 50), 1);
		}
	}

	rcText.left = m_rcWnd.left+12;
	rcText.right = m_rcWnd.left+62;
	rcText.top = m_rcWnd.top+440;
	rcText.bottom = m_rcWnd.top+455;
	
	sprintf(szBuff, "%s", g_xMsg.GetMsg(5180));
	g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);
	//  약한원소

	rcText.top = m_rcWnd.top + 439;
	rcText.bottom = rcText.top + 15;

	if ( g_xGameProc.m_xMyHero.m_stAbility.ATOM_AC_BAD[6] > 0 )
	{
		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(1526) )
		{
 			g_xMainWnd.DrawWithImageForComp(
							m_rcWnd.left + 285, m_rcWnd.top + 436,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
							(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage));
		}

		rcText.left = m_rcWnd.left + 303;
		rcText.right = rcText.left + 20;
		sprintf(szBuff, "x%d", g_xGameProc.m_xMyHero.m_stAbility.ATOM_AC_BAD[6]);
		if (m_bCheckShow[25])
			g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 128,   0), RGB(0, 0, 0), szBuff);
		else
			g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

		if ( PtInRect(&m_rcAtomTooltip[2][6], g_xGameProc.m_ptMousePos) )
		{
			RECT	rcToolTip;
			sprintf(szBuff, "%s", g_xMsg.GetMsg(5167));
			SetRect(&rcToolTip, m_rcAtomTooltip[2][6].left + 10, m_rcAtomTooltip[2][6].top - 10, m_rcAtomTooltip[2][6].right + 35 , m_rcAtomTooltip[2][6].bottom - 10);
			D3DMATERIAL7 mtrl;
			D3DVECTOR	vecTrans((FLOAT)rcToolTip.left, (FLOAT)rcToolTip.top, 0);
			D3DVECTOR	vecScale((FLOAT)rcToolTip.right-rcToolTip.left, rcToolTip.bottom-rcToolTip.top, 1);

			D3DUtil_InitMaterial(mtrl, (FLOAT)80/255.0f, (FLOAT)60/255.0f, (FLOAT)40/255.0f);
			mtrl.diffuse.a = 150.0f/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

			g_xMainWnd.PutsHan(NULL, rcToolTip, RGB(255, 255, 255), RGB(0, 0, 0), szBuff, NULL);
			g_xMainWnd.DrawWithGDI(&rcToolTip, NULL, RGB(100, 75, 50), 1);
		}
	}

	if ( g_xGameProc.m_xMyHero.m_stAbility.ATOM_AC_BAD[5] > 0 )
	{
		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(1525) )
		{
 			g_xMainWnd.DrawWithImageForComp(
							m_rcWnd.left + 248, m_rcWnd.top + 436,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
							(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage));
		}

		rcText.left = m_rcWnd.left + 266;
		rcText.right = rcText.left + 20;
		sprintf(szBuff, "x%d", g_xGameProc.m_xMyHero.m_stAbility.ATOM_AC_BAD[5]);
		if (m_bCheckShow[24])
			g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 128,   0), RGB(0, 0, 0), szBuff);
		else
			g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

		if ( PtInRect(&m_rcAtomTooltip[2][5], g_xGameProc.m_ptMousePos) )
		{
			RECT	rcToolTip;
			sprintf(szBuff, "%s", g_xMsg.GetMsg(5166));
			SetRect(&rcToolTip, m_rcAtomTooltip[2][5].left + 10, m_rcAtomTooltip[2][5].top - 10, m_rcAtomTooltip[2][5].right + 35 , m_rcAtomTooltip[2][5].bottom - 10);
			D3DMATERIAL7 mtrl;
			D3DVECTOR	vecTrans((FLOAT)rcToolTip.left, (FLOAT)rcToolTip.top, 0);
			D3DVECTOR	vecScale((FLOAT)rcToolTip.right-rcToolTip.left, rcToolTip.bottom-rcToolTip.top, 1);

			D3DUtil_InitMaterial(mtrl, (FLOAT)80/255.0f, (FLOAT)60/255.0f, (FLOAT)40/255.0f);
			mtrl.diffuse.a = 150.0f/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

			g_xMainWnd.PutsHan(NULL, rcToolTip, RGB(255, 255, 255), RGB(0, 0, 0), szBuff, NULL);
			g_xMainWnd.DrawWithGDI(&rcToolTip, NULL, RGB(100, 75, 50), 1);
		}
	}

	if ( g_xGameProc.m_xMyHero.m_stAbility.ATOM_AC_BAD[4] > 0 )
	{
		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(1524) )
		{
 			g_xMainWnd.DrawWithImageForComp(
							m_rcWnd.left + 211, m_rcWnd.top + 436,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
							(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage));
		}
		
		rcText.left = m_rcWnd.left + 229;
		rcText.right = rcText.left + 20;
		sprintf(szBuff, "x%d", g_xGameProc.m_xMyHero.m_stAbility.ATOM_AC_BAD[4]);
		if (m_bCheckShow[23])
			g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 128,   0), RGB(0, 0, 0), szBuff);
		else
			g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

		if ( PtInRect(&m_rcAtomTooltip[2][4], g_xGameProc.m_ptMousePos) )
		{
			RECT	rcToolTip;
			sprintf(szBuff, "%s", g_xMsg.GetMsg(5165));
			SetRect(&rcToolTip, m_rcAtomTooltip[2][4].left + 10, m_rcAtomTooltip[2][4].top - 10, m_rcAtomTooltip[2][4].right + 35 , m_rcAtomTooltip[2][4].bottom - 10);
			D3DMATERIAL7 mtrl;
			D3DVECTOR	vecTrans((FLOAT)rcToolTip.left, (FLOAT)rcToolTip.top, 0);
			D3DVECTOR	vecScale((FLOAT)rcToolTip.right-rcToolTip.left, rcToolTip.bottom-rcToolTip.top, 1);

			D3DUtil_InitMaterial(mtrl, (FLOAT)80/255.0f, (FLOAT)60/255.0f, (FLOAT)40/255.0f);
			mtrl.diffuse.a = 150.0f/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

			g_xMainWnd.PutsHan(NULL, rcToolTip, RGB(255, 255, 255), RGB(0, 0, 0), szBuff, NULL);
			g_xMainWnd.DrawWithGDI(&rcToolTip, NULL, RGB(100, 75, 50), 1);
		}
	}

	if ( g_xGameProc.m_xMyHero.m_stAbility.ATOM_AC_BAD[3] > 0 )
	{
		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(1523) )
		{
 			g_xMainWnd.DrawWithImageForComp(
							m_rcWnd.left + 174, m_rcWnd.top + 436,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
							(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage));
		}
		
		rcText.left = m_rcWnd.left + 192;
		rcText.right = rcText.left + 20;
		sprintf(szBuff, "x%d", g_xGameProc.m_xMyHero.m_stAbility.ATOM_AC_BAD[3]);
		if (m_bCheckShow[22])
			g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 128,   0), RGB(0, 0, 0), szBuff);
		else
			g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

		if ( PtInRect(&m_rcAtomTooltip[2][3], g_xGameProc.m_ptMousePos) )
		{
			RECT	rcToolTip;
			sprintf(szBuff, "%s", g_xMsg.GetMsg(5164));
			SetRect(&rcToolTip, m_rcAtomTooltip[2][3].left + 10, m_rcAtomTooltip[2][3].top - 10, m_rcAtomTooltip[2][3].right + 35 , m_rcAtomTooltip[2][3].bottom - 10);
			D3DMATERIAL7 mtrl;
			D3DVECTOR	vecTrans((FLOAT)rcToolTip.left, (FLOAT)rcToolTip.top, 0);
			D3DVECTOR	vecScale((FLOAT)rcToolTip.right-rcToolTip.left, rcToolTip.bottom-rcToolTip.top, 1);

			D3DUtil_InitMaterial(mtrl, (FLOAT)80/255.0f, (FLOAT)60/255.0f, (FLOAT)40/255.0f);
			mtrl.diffuse.a = 150.0f/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

			g_xMainWnd.PutsHan(NULL, rcToolTip, RGB(255, 255, 255), RGB(0, 0, 0), szBuff, NULL);
			g_xMainWnd.DrawWithGDI(&rcToolTip, NULL, RGB(100, 75, 50), 1);
		}
	}

	if ( g_xGameProc.m_xMyHero.m_stAbility.ATOM_AC_BAD[2] > 0 )
	{
		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(1522) )
		{
 			g_xMainWnd.DrawWithImageForComp(
							m_rcWnd.left + 137, m_rcWnd.top + 436,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
							(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage));
		}

		rcText.left = m_rcWnd.left + 155;
		rcText.right = rcText.left + 20;
		sprintf(szBuff, "x%d", g_xGameProc.m_xMyHero.m_stAbility.ATOM_AC_BAD[2]);
		if (m_bCheckShow[21])
			g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 128,   0), RGB(0, 0, 0), szBuff);
		else
			g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

		if ( PtInRect(&m_rcAtomTooltip[2][2], g_xGameProc.m_ptMousePos) )
		{
			RECT	rcToolTip;
			sprintf(szBuff, "%s", g_xMsg.GetMsg(5163));
			SetRect(&rcToolTip, m_rcAtomTooltip[2][2].left + 10, m_rcAtomTooltip[2][2].top - 10, m_rcAtomTooltip[2][2].right + 35 , m_rcAtomTooltip[2][2].bottom - 10);
			D3DMATERIAL7 mtrl;
			D3DVECTOR	vecTrans((FLOAT)rcToolTip.left, (FLOAT)rcToolTip.top, 0);
			D3DVECTOR	vecScale((FLOAT)rcToolTip.right-rcToolTip.left, rcToolTip.bottom-rcToolTip.top, 1);

			D3DUtil_InitMaterial(mtrl, (FLOAT)80/255.0f, (FLOAT)60/255.0f, (FLOAT)40/255.0f);
			mtrl.diffuse.a = 150.0f/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

			g_xMainWnd.PutsHan(NULL, rcToolTip, RGB(255, 255, 255), RGB(0, 0, 0), szBuff, NULL);
			g_xMainWnd.DrawWithGDI(&rcToolTip, NULL, RGB(100, 75, 50), 1);
		}
	}	

	if ( g_xGameProc.m_xMyHero.m_stAbility.ATOM_AC_BAD[1] > 0 )
	{
		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(1521) )
		{
 			g_xMainWnd.DrawWithImageForComp(
							m_rcWnd.left + 100, m_rcWnd.top + 436,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
							(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage));
		}

		rcText.left = m_rcWnd.left + 118;
		rcText.right = rcText.left + 20;
		sprintf(szBuff, "x%d", g_xGameProc.m_xMyHero.m_stAbility.ATOM_AC_BAD[1]);
		if (m_bCheckShow[20])
			g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 128,   0), RGB(0, 0, 0), szBuff);
		else
			g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

		if ( PtInRect(&m_rcAtomTooltip[2][1], g_xGameProc.m_ptMousePos) )
		{
			RECT	rcToolTip;
			sprintf(szBuff, "%s", g_xMsg.GetMsg(5162));
			SetRect(&rcToolTip, m_rcAtomTooltip[2][1].left + 10, m_rcAtomTooltip[2][1].top - 10, m_rcAtomTooltip[2][1].right + 35 , m_rcAtomTooltip[2][1].bottom - 10);
			D3DMATERIAL7 mtrl;
			D3DVECTOR	vecTrans((FLOAT)rcToolTip.left, (FLOAT)rcToolTip.top, 0);
			D3DVECTOR	vecScale((FLOAT)rcToolTip.right-rcToolTip.left, rcToolTip.bottom-rcToolTip.top, 1);

			D3DUtil_InitMaterial(mtrl, (FLOAT)80/255.0f, (FLOAT)60/255.0f, (FLOAT)40/255.0f);
			mtrl.diffuse.a = 150.0f/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

			g_xMainWnd.PutsHan(NULL, rcToolTip, RGB(255, 255, 255), RGB(0, 0, 0), szBuff, NULL);
			g_xMainWnd.DrawWithGDI(&rcToolTip, NULL, RGB(100, 75, 50), 1);
		}
	}

	if ( g_xGameProc.m_xMyHero.m_stAbility.ATOM_AC_BAD[0] > 0 )
	{
		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(1520) )
		{
 			g_xMainWnd.DrawWithImageForComp(
							m_rcWnd.left + 63, m_rcWnd.top + 436,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth,
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
							(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage));
		}

		rcText.left = m_rcWnd.left + 81;
		rcText.right = rcText.left + 20;
		sprintf(szBuff, "x%d", g_xGameProc.m_xMyHero.m_stAbility.ATOM_AC_BAD[0]);
		if (m_bCheckShow[19])
			g_xMainWnd.PutsHan(NULL, rcText, RGB(255, 128,   0), RGB(0, 0, 0), szBuff);
		else
			g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

		if ( PtInRect(&m_rcAtomTooltip[2][0], g_xGameProc.m_ptMousePos) )
		{
			RECT	rcToolTip;
			sprintf(szBuff, "%s", g_xMsg.GetMsg(5161));
			SetRect(&rcToolTip, m_rcAtomTooltip[2][0].left + 10, m_rcAtomTooltip[2][0].top - 10, m_rcAtomTooltip[2][0].right + 35 , m_rcAtomTooltip[2][0].bottom - 10);
			D3DMATERIAL7 mtrl;
			D3DVECTOR	vecTrans((FLOAT)rcToolTip.left, (FLOAT)rcToolTip.top, 0);
			D3DVECTOR	vecScale((FLOAT)rcToolTip.right-rcToolTip.left, rcToolTip.bottom-rcToolTip.top, 1);

			D3DUtil_InitMaterial(mtrl, (FLOAT)80/255.0f, (FLOAT)60/255.0f, (FLOAT)40/255.0f);
			mtrl.diffuse.a = 150.0f/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

			g_xMainWnd.PutsHan(NULL, rcToolTip, RGB(255, 255, 255), RGB(0, 0, 0), szBuff, NULL);
			g_xMainWnd.DrawWithGDI(&rcToolTip, NULL, RGB(100, 75, 50), 1);
		}
	}

	for ( nI=0; nI<26; nI++)
		m_bCheckShow[nI]= FALSE;

	BOOL	bChecked = FALSE;
	CHAR	pszBuff[MAX_PATH];

	for ( nI=0; nI<9; nI++ )
	{	
		if ( PtInRect(&m_rcAbility[nI], g_xGameProc.m_ptMousePos) )
		{
			bChecked = TRUE;
			break;
		}
	}

	if ( bChecked == TRUE)
	{
		switch (nI)
		{
			case 0:
				sprintf(pszBuff, "%s", g_xMsg.GetMsg(2400));
				break;
			case 1:
				sprintf(pszBuff, "%s", g_xMsg.GetMsg(2401));
				break;
			case 2:
				sprintf(pszBuff, "%s", "HP");
				break;
			case 3:
				sprintf(pszBuff, "%s", "MP");
				break;
			case 4:
				sprintf(pszBuff, "%s", g_xMsg.GetMsg(2404));
				break;
			case 5:
				sprintf(pszBuff, "%s", g_xMsg.GetMsg(2402));
				break;
			case 6:
				sprintf(pszBuff, "%s", g_xMsg.GetMsg(2403));
				break;
			case 7:
				sprintf(pszBuff, "%s", g_xMsg.GetMsg(1053));
				break;
			case 8:
				sprintf(pszBuff, "%s", g_xMsg.GetMsg(1054));
				break;
		}
		SIZE sizeLen = g_xMainWnd.GetStrLength(NULL, NULL, pszBuff);
		RECT rcStats;

		SetRect(&rcStats, m_rcAbility[nI].left - 10, m_rcAbility[nI].top - 15, m_rcAbility[nI].left - 10 + sizeLen.cx, m_rcAbility[nI].bottom - 15 );

		D3DMATERIAL7 mtrl;
		D3DVECTOR	vecTrans((FLOAT)rcStats.left, (FLOAT)rcStats.top, 0);
		D3DVECTOR	vecScale((FLOAT)rcStats.right-rcStats.left, rcStats.bottom-rcStats.top, 1);

		D3DUtil_InitMaterial(mtrl, (FLOAT)80/255.0f, (FLOAT)60/255.0f, (FLOAT)40/255.0f);
		mtrl.diffuse.a = 150.0f/255.0f;
		g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

		g_xMainWnd.PutsHan(NULL, rcStats, RGB(255, 255, 255), RGB(0, 0, 0), pszBuff, NULL);
		g_xMainWnd.DrawWithGDI(&rcStats, NULL, RGB(100, 75, 50), 1);
	}
}



/******************************************************************************************************************

	함수명 : CStatusWnd::ShowEquipItemState()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CStatusWnd::ShowEquipItemState()
{
	if ( m_bType == _TYPE_STATUS )
	{
		return; 
	}

	INT nEquipNum = GetEquipNum(g_xGameProc.m_ptMousePos);

	if ( nEquipNum != -1 )
	{
		if ( m_stEquipItem[nEquipNum].bSetted )
		{
			INT nStartX = m_rcCell[nEquipNum].left;
			INT nStartY = m_rcCell[nEquipNum].top;

			m_stEquipItem[nEquipNum].xItem.ShowItemStatus(nStartX+15, nStartY+15, FALSE, FALSE, TRUE);
		}		
	}
}



/******************************************************************************************************************

	함수명 : CStatusWnd::GetEquipNum()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : POINT ptMouse
	출력   : INT 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
INT CStatusWnd::GetEquipNum(POINT ptMouse)
{
	RECT rc;
	for ( INT nCnt = 0; nCnt < _EQUIP_MAX_CELL; nCnt++ )
	{
		SetRect(&rc, m_rcCell[nCnt].left, m_rcCell[nCnt].top, 
			    m_rcCell[nCnt].left+(m_rcCell[nCnt].right-m_rcCell[nCnt].left), m_rcCell[nCnt].top+(m_rcCell[nCnt].bottom-m_rcCell[nCnt].top));
		if ( PtInRect(&rc, ptMouse) )
		{
			return nCnt;
		}
	}

	return -1;
}



/******************************************************************************************************************

	함수명 : CStatusWnd::CheckEquipItem()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : CItem* pxItem
	         BYTE bEquipCell
	         POINT ptMouse
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CStatusWnd::CheckEquipItem(CItem* pxItem, BYTE bEquipCell, POINT ptMouse)
{
	RECT rc;

	for ( INT nCnt = 0; nCnt < _EQUIP_MAX_CELL; nCnt++ )
	{
		SetRect(&rc, m_rcCell[nCnt].left, m_rcCell[nCnt].top, 
			    m_rcCell[nCnt].left+(m_rcCell[nCnt].right-m_rcCell[nCnt].left), m_rcCell[nCnt].top+(m_rcCell[nCnt].bottom-m_rcCell[nCnt].top));
		if ( PtInRect(&rc, ptMouse) )
		{
			if ( pxItem->m_bAttr == _U_ARMRINGL || pxItem->m_bAttr == _U_ARMRINGR || pxItem->m_bAttr == _U_CHARM )
			{
				if ( pxItem->m_stItemInfo.stStdItem.bStdMode == 25 )
				{
					if ( _U_ARMRINGL == bEquipCell || _U_CHARM == bEquipCell )
						return TRUE;
				}
				else
				{
					if ( _U_ARMRINGL == bEquipCell || _U_ARMRINGR == bEquipCell )
						return TRUE;
				}
			}
			else if ( pxItem->m_bAttr == _U_RINGL || pxItem->m_bAttr ==  _U_RINGR )
			{
				if ( _U_RINGL == bEquipCell || _U_RINGR == bEquipCell )
					return TRUE;
			}
			else if ( pxItem->m_bAttr == _U_ETC )
			{
				if ( bEquipCell == _U_ETC )
					return TRUE;
			}
			else if ( pxItem->m_bAttr == bEquipCell )
			{
				return TRUE;
			}			
		}
	}

	return FALSE;
}



/******************************************************************************************************************

	함수명 : CStatusWnd::DeleteEquipItem()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : INT nEquipNum
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CStatusWnd::DeleteEquipItem(INT nEquipNum)
{
	ZeroMemory(&m_stEquipItem[nEquipNum], sizeof(ITEMSET));
}



BOOL CStatusWnd::DeleteEquipItem(INT nMakeIndex, CHAR* szName)
{
	BOOL bRtn = FALSE;

	for ( INT nCnt = 0; nCnt < _EQUIP_MAX_CELL; nCnt++ )
	{
		if ( m_stEquipItem[nCnt].bSetted )
		{
			if ( m_stEquipItem[nCnt].xItem.m_stItemInfo.nMakeIndex == nMakeIndex )
			{
				if ( !strcmp(m_stEquipItem[nCnt].xItem.m_stItemInfo.stStdItem.szName, szName) )
				{
					DeleteEquipItem(nCnt);
					bRtn = TRUE;
					break;
				}
			}
		}		
	}

	return bRtn;
}



/******************************************************************************************************************

	함수명 : CStatusWnd::DeleteAllEquipItem()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CStatusWnd::DeleteAllEquipItem()
{
	for ( INT nCnt = 0; nCnt < _EQUIP_MAX_CELL; nCnt++ )
	{
		ZeroMemory(&m_stEquipItem[nCnt], sizeof(ITEMSET));
	}
}



/******************************************************************************************************************

	함수명 : CStatusWnd::AddEquipItem()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : CItem xItem
	         INT nEquipNum
	         BOOL bUseEquipNum
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CStatusWnd::AddEquipItem(CItem xItem, INT nEquipNum, BOOL bUseEquipNum)
{
	if ( bUseEquipNum )
	{
		if ( !m_stEquipItem[nEquipNum].bSetted )
		{
			m_stEquipItem[nEquipNum].bSetted = TRUE;
			m_stEquipItem[nEquipNum].xItem = xItem;
			m_stEquipItem[nEquipNum].xItem.m_shCellNum = (SHORT)nEquipNum;

			return TRUE;
		}
	}

	for ( INT nCnt = 0; nCnt < _EQUIP_MAX_CELL; nCnt++ )
	{
		if ( !m_stEquipItem[nCnt].bSetted && nCnt == xItem.m_bAttr )
		{
			m_stEquipItem[nCnt].bSetted = TRUE;
			m_stEquipItem[nCnt].xItem = xItem;
			m_stEquipItem[nCnt].xItem.m_shCellNum = (SHORT)nCnt;

			return TRUE;
		}
	}
	return FALSE;
}



/******************************************************************************************************************

	함수명 : CStatusWnd::ExtractEquipItem()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : CItem* pxItem
	         INT nEquipNum
	출력   : BOOL 

	[일자][수정자] : 수정내용

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

	함수명 : CStatusWnd::ChangeEquipWithCommon()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : INT nEquipNum
	         LPCOMMONITEMSET pstCommonItemSet
	출력   : VOID 

	[일자][수정자] : 수정내용

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
			pstCommonItemSet->bIsDealItem		= FALSE;
			pstCommonItemSet->bIsEquipItem		= TRUE;
			pstCommonItemSet->bIsHideItem		= FALSE;
			pstCommonItemSet->bIsBeltItem		= FALSE;
			pstCommonItemSet->xItem.m_shCellNum = (SHORT)nEquipNum; 
		}
	}
}




/******************************************************************************************************************

	함수명 : CStatusWnd::SetCommonFromEquip()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : INT nEquipNum
	         LPCOMMONITEMSET pstCommonItemSet
	출력   : VOID 

	[일자][수정자] : 수정내용

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
		pstCommonItemSet->bIsDealItem		= FALSE;
		pstCommonItemSet->bIsHideItem		= FALSE;
		pstCommonItemSet->bIsBeltItem		= FALSE;
		pstCommonItemSet->xItem.m_shCellNum = (SHORT)nEquipNum; 

		g_xGameProc.m_xInterface.ItemClickSound(&pstCommonItemSet->xItem);
	}	
}



/******************************************************************************************************************

	함수명 : CStatusWnd::SetEquipFromCommon()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : INT nEquipNum
	         LPCOMMONITEMSET pstCommonItemSet
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CStatusWnd::SetEquipFromCommon(INT nEquipNum, LPCOMMONITEMSET pstCommonItemSet)
{
	if ( pstCommonItemSet->bSetted )
	{
		g_xGameProc.m_xInterface.ItemClickSound(&pstCommonItemSet->xItem);

		pstCommonItemSet->xItem.m_shCellNum = (SHORT)nEquipNum;
		AddEquipItem(pstCommonItemSet->xItem, nEquipNum);
		ZeroMemory(pstCommonItemSet, sizeof(COMMONITEMSET));
	}
}



/******************************************************************************************************************

	함수명 : CStatusWnd::SetTakeOnFromEquip()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : INT nEquipNum
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CStatusWnd::SetTakeOnFromEquip(INT nEquipNum)
{
	if ( m_stEquipItem[nEquipNum].bSetted )
	{
		m_stTakeOnItemSet.xItem	  = m_stEquipItem[nEquipNum].xItem;
		m_stTakeOnItemSet.bSetted = TRUE;
		m_stTakeOnItemSet.xItem.m_shCellNum = (SHORT)nEquipNum;
		ZeroMemory(&m_stEquipItem[nEquipNum], sizeof(ITEMSET));	
	}
}



/******************************************************************************************************************

	함수명 : CStatusWnd::SetTakeOnFromCommon()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : LPCOMMONITEMSET pstCommonItemSet
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CStatusWnd::SetTakeOnFromCommon(INT nEquipNum, LPCOMMONITEMSET pstCommonItemSet)
{
	if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bIsDealItem && !pstCommonItemSet->bIsBeltItem )
	{
		m_stTakeOnItemSet.xItem   = pstCommonItemSet->xItem;
		m_stTakeOnItemSet.bSetted = TRUE;
		m_stTakeOnItemSet.xItem.m_shCellNum = (SHORT)nEquipNum;

		// 추가 가방
		m_stTakeOnItemSet.bIsInvenExWnd = pstCommonItemSet->bIsInvenExWnd;

		ZeroMemory(pstCommonItemSet, sizeof(COMMONITEMSET));	
	}
}



/******************************************************************************************************************

	함수명 : CStatusWnd::SetEquipFromTakeOn()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : VOID 

	[일자][수정자] : 수정내용

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

	캐릭터 상태정보창관련.

*******************************************************************************************************************/
/******************************************************************************************************************

	함수명 : CStatusWnd::ShowCharStatus()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CStatusWnd::ShowCharStatus()
{
	CHAR	szBuff[MAX_PATH];

	POINT	ptStart = {m_rcWnd.left+20, m_rcWnd.top+70};
/*
	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), g_xMsg.GetMsg(1053), g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));
	sprintf(szBuff, "+%d%", g_xGameProc.m_xMyHero.m_stSubAbility.bHitPoint);
	g_xMainWnd.PutsHan(NULL, ptStart.x+55, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	g_xMainWnd.PutsHan(NULL, ptStart.x+100, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), g_xMsg.GetMsg(1054), g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));
	sprintf(szBuff, "+%d%", g_xGameProc.m_xMyHero.m_stSubAbility.bSpeedPoint);
	g_xMainWnd.PutsHan(NULL, ptStart.x+160, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 14;
	
	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), g_xMsg.GetMsg(1055), g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));
	sprintf(szBuff, "+%d%", g_xGameProc.m_xMyHero.m_stSubAbility.wAntiMagic*10);
	g_xMainWnd.PutsHan(NULL, ptStart.x+55, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	g_xMainWnd.PutsHan(NULL, ptStart.x+100, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), g_xMsg.GetMsg(1056), g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));
	sprintf(szBuff, "+%d%", g_xGameProc.m_xMyHero.m_stSubAbility.bAntiPoison*10);
	g_xMainWnd.PutsHan(NULL, ptStart.x+160, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 14;
	
	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), g_xMsg.GetMsg(1057), g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));
	sprintf(szBuff, "+%d%", g_xGameProc.m_xMyHero.m_stSubAbility.bPoisonRecover*10);
	g_xMainWnd.PutsHan(NULL, ptStart.x+55, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	g_xMainWnd.PutsHan(NULL, ptStart.x+100, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), g_xMsg.GetMsg(1058), g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));
	sprintf(szBuff, "+%d", g_xGameProc.m_xMyHero.m_stSubAbility.bHealthRecover);
	g_xMainWnd.PutsHan(NULL, ptStart.x+160, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 14;
	
	g_xMainWnd.PutsHan(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), g_xMsg.GetMsg(1059), g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));
	sprintf(szBuff, "+%d", g_xGameProc.m_xMyHero.m_stSubAbility.bSpellRecover);
	g_xMainWnd.PutsHan(NULL, ptStart.x+55, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;
	g_xMainWnd.PutsHanA(NULL, ptStart.x, ptStart.y, RGB(100, 200, 250), RGB(0, 0, 0), g_xMsg.GetMsg(2406), g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));

	ptStart.y += 14;
	g_xMainWnd.PutsHanA(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), g_xMsg.GetMsg(5161), g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));
	sprintf(szBuff, "%d-%d", LOBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[0]), HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[0]));
	g_xMainWnd.PutsHan(NULL, ptStart.x+55, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	g_xMainWnd.PutsHanA(NULL, ptStart.x+100, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), g_xMsg.GetMsg(5162), g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));
	sprintf(szBuff, "%d-%d", LOBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[1]), HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[1]));
	g_xMainWnd.PutsHan(NULL, ptStart.x+160, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 14;
	g_xMainWnd.PutsHanA(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), g_xMsg.GetMsg(5163), g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));
	sprintf(szBuff, "%d-%d", LOBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[2]), HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[2]));
	g_xMainWnd.PutsHan(NULL, ptStart.x+55, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	g_xMainWnd.PutsHanA(NULL, ptStart.x+100, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), g_xMsg.GetMsg(5164), g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));
	sprintf(szBuff, "%d-%d", LOBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[3]), HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_DC[3]));
	g_xMainWnd.PutsHan(NULL, ptStart.x+160, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;

	g_xMainWnd.PutsHanA(NULL, ptStart.x, ptStart.y, RGB(255, 200, 0), RGB(0, 0, 0), g_xMsg.GetMsg(2407), g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));

	ptStart.y += 14;

	g_xMainWnd.PutsHanA(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), g_xMsg.GetMsg(5161), g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));
	sprintf(szBuff, "%d-%d", LOBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_MC[0]), HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_MC[0]));
	g_xMainWnd.PutsHan(NULL, ptStart.x+55, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	g_xMainWnd.PutsHanA(NULL, ptStart.x+100, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), g_xMsg.GetMsg(5162), g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));
	sprintf(szBuff, "%d-%d", LOBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_MC[1]), HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_MC[1]));
	g_xMainWnd.PutsHan(NULL, ptStart.x+155, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 14;
	g_xMainWnd.PutsHanA(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), g_xMsg.GetMsg(5163), g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));
	sprintf(szBuff, "%d-%d", LOBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_MC[2]), HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_MC[2]));
	g_xMainWnd.PutsHan(NULL, ptStart.x+55, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	g_xMainWnd.PutsHanA(NULL, ptStart.x+100, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), g_xMsg.GetMsg(5164), g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));
	sprintf(szBuff, "%d-%d", LOBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_MC[3]), HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_MC[3]));
	g_xMainWnd.PutsHan(NULL, ptStart.x+155, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;

	g_xMainWnd.PutsHanA(NULL, ptStart.x, ptStart.y, RGB(255, 200, 0), RGB(0, 0, 0), g_xMsg.GetMsg(2408), g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));

	ptStart.y += 14;
	g_xMainWnd.PutsHanA(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), g_xMsg.GetMsg(5165), g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));
	sprintf(szBuff, "%d-%d", LOBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_MC[4]), HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_MC[4]));
	g_xMainWnd.PutsHan(NULL, ptStart.x+68, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 14;
	g_xMainWnd.PutsHanA(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), g_xMsg.GetMsg(5166), g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));
	sprintf(szBuff, "%d-%d", LOBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_MC[5]), HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_MC[5]));
	g_xMainWnd.PutsHan(NULL, ptStart.x+68, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 14;
	g_xMainWnd.PutsHanA(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), g_xMsg.GetMsg(5167), g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));
	sprintf(szBuff, "%d-%d", LOBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_MC[6]), HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_MC[6]));
	g_xMainWnd.PutsHan(NULL, ptStart.x+68, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;

	g_xMainWnd.PutsHanA(NULL, ptStart.x, ptStart.y, RGB(0, 255, 200), RGB(0, 0, 0), g_xMsg.GetMsg(2409), g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));

	ptStart.y += 14;

	g_xMainWnd.PutsHanA(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), g_xMsg.GetMsg(5161), g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));
	sprintf(szBuff, "%d-%d", LOBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_MAC[0]), HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_MAC[0]));
	g_xMainWnd.PutsHan(NULL, ptStart.x+68, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	g_xMainWnd.PutsHanA(NULL, ptStart.x+100, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), g_xMsg.GetMsg(5162), g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));
	sprintf(szBuff, "%d-%d", LOBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_MAC[1]), HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_MAC[1]));
	g_xMainWnd.PutsHan(NULL, ptStart.x+155, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 14;
	g_xMainWnd.PutsHanA(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), g_xMsg.GetMsg(5163), g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));
	sprintf(szBuff, "%d-%d", LOBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_MAC[2]), HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_MAC[2]));
	g_xMainWnd.PutsHan(NULL, ptStart.x+68, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	g_xMainWnd.PutsHanA(NULL, ptStart.x+100, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), g_xMsg.GetMsg(5164), g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));
	sprintf(szBuff, "%d-%d", LOBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_MAC[3]), HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_MAC[3]));
	g_xMainWnd.PutsHan(NULL, ptStart.x+155, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;

	g_xMainWnd.PutsHanA(NULL, ptStart.x, ptStart.y, RGB(0, 255, 200), RGB(0, 0, 0), g_xMsg.GetMsg(2410), g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));

	ptStart.y += 14;
	g_xMainWnd.PutsHanA(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), g_xMsg.GetMsg(5165), g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));
	sprintf(szBuff, "%d-%d", LOBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_MAC[4]), HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_MAC[4]));
	g_xMainWnd.PutsHan(NULL, ptStart.x+68, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 14;
	g_xMainWnd.PutsHanA(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), g_xMsg.GetMsg(5166), g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));
	sprintf(szBuff, "%d-%d", LOBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_MAC[5]), HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_MAC[5]));
	g_xMainWnd.PutsHan(NULL, ptStart.x+68, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 14;
	g_xMainWnd.PutsHanA(NULL, ptStart.x, ptStart.y, RGB(200, 225, 250), RGB(0, 0, 0), g_xMsg.GetMsg(5167), g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD)	);
	sprintf(szBuff, "%d-%d", LOBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_MAC[6]), HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.ATOM_MAC[6]));
	g_xMainWnd.PutsHan(NULL, ptStart.x+68, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 20;

	g_xMainWnd.PutsHanA(NULL, ptStart.x, ptStart.y, RGB(255, 0, 0), RGB(0, 0, 0), g_xMsg.GetMsg(1060), g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));
	sprintf(szBuff, "%d-%d", LOBYTE(g_xGameProc.m_xMyHero.m_stAbility.wAC), HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.wAC));
	g_xMainWnd.PutsHan(NULL, ptStart.x+68, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);

	ptStart.y += 16;

	g_xMainWnd.PutsHanA(NULL, ptStart.x, ptStart.y, RGB(255, 0, 0), RGB(0, 0, 0), g_xMsg.GetMsg(1061), g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));
	sprintf(szBuff, "%d-%d", LOBYTE(g_xGameProc.m_xMyHero.m_stAbility.wDC), HIBYTE(g_xGameProc.m_xMyHero.m_stAbility.wDC));
	g_xMainWnd.PutsHan(NULL, ptStart.x+68, ptStart.y, RGB(250, 250, 250), RGB(0, 0, 0), szBuff);
*/

}



























/******************************************************************************************************************

	Message Function.

*******************************************************************************************************************/
/******************************************************************************************************************

	함수명 : CStatusWnd::OnLButtonUp()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : POINT ptMouse
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CStatusWnd::OnLButtonUp(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse)
{
	// 더블클릭.
	if ( timeGetTime() - m_dwLClickTime	< 300 )
	{
		if ( pstCommonItemSet && pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse && !pstCommonItemSet->bIsDealItem )
		{
			BYTE bStdMode = pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bStdMode;
			WORD wLooks	  = pstCommonItemSet->xItem.m_stItemInfo.stStdItem.wLooks;

			if ( bStdMode != 5 && bStdMode != 6 && bStdMode != 10 && bStdMode != 11 && bStdMode != 15 && bStdMode != 53 )
			{
				m_dwLClickTime = timeGetTime();

				OnLButtonDoubleClick(pstCommonItemSet, ptMouse);
				return FALSE;
			}
			else
			{
				g_xGameProc.m_xInterface.m_xClientSysMsg.AddSysMsg(g_xMsg.GetMsg(2413));
			}
		}
	}

	// 보통클릭.
	m_dwLClickTime = timeGetTime();

	INT nEquipNum;

	if ( m_xStatusBtn[_BTN_ID_STATUSCLOSE].OnLButtonUp(ptMouse) )		return TRUE;

	BOOL bEquipActive = FALSE;

	if ( m_bType == _TYPE_EQUIP || m_bType == _TYPE_STATUS )
	{
		bEquipActive = TRUE;
	}

	// 장착창 활성화 됐을경우.
	if ( bEquipActive )
	{
		nEquipNum = GetEquipNum(ptMouse);
		// 마우스가 장착창영역에 있을때.
		if ( nEquipNum != -1)
		{
			// 클릭한장착창에 아이템이 있을경우.
			if ( m_stEquipItem[nEquipNum].bSetted )
			{
				// 공통(마우스)아이템셋이 비어있으면,
				if ( !pstCommonItemSet->bSetted )
				{				  
					// 마우스에 아이템을 붙여놓으면 인벤토리 윈도에서 클릭하는순간 CM_TAKEOFFITEM메시지를 보낸다.
					SetCommonFromEquip(nEquipNum, pstCommonItemSet);
				}
				// 공통(마우스)아이템셋은 있고, 서버로부터 응답신호를 기다리는 중이 아니면,
				// 공통아이템을 m_stTakeOnItemSet에 아이템을 세팅해두고, 현재 클릭된 장착창 아이템을 공통아이템으로 세팅하고나서,
				// CM_TAKEONITEM메시지를 보낸다.
				else if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse && !pstCommonItemSet->bIsEquipItem && !pstCommonItemSet->bIsUtilItem )
				{
					// 보내기전 영역이 서로 맞는가(반지자리에 반지가 잘들어갔는지)를 체크한다.
					if ( CheckEquipItem(&pstCommonItemSet->xItem, (BYTE)nEquipNum, ptMouse) )
					{
						SetTakeOnFromCommon(nEquipNum, pstCommonItemSet);
						SetCommonFromEquip(nEquipNum, pstCommonItemSet);					
						g_xClientSocket.SendTakeOnOffItem(CM_TAKEONITEM, (BYTE)nEquipNum, m_stTakeOnItemSet.xItem.m_stItemInfo.stStdItem.szName, m_stTakeOnItemSet.xItem.m_stItemInfo.nMakeIndex);
						pstCommonItemSet->bWaitResponse	= TRUE;
						return FALSE;
					}
				}
			}
			// 클릭한 장착창에 아이템이 없을경우.
			else
			{
				// 공통(마우스)아이템셋은 있고, 서버로부터 응답신호를 기다리는 중이 아니면, 공통아이템을 m_stTakeOnItemSet에 아이템을 세팅해둔다.
				if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse )
				{	
					if ( CheckEquipItem(&pstCommonItemSet->xItem, (BYTE)nEquipNum, ptMouse) )
					{
						// 서버로 메시지를 보낼필요는 없다. 아이템을 벗었다가 다시착용한경우.
						if ( pstCommonItemSet->bIsEquipItem )
						{
							SetEquipFromCommon(pstCommonItemSet->xItem.m_shCellNum, pstCommonItemSet);
							ZeroMemory(pstCommonItemSet, sizeof(COMMONITEMSET));
						}
						else
						{
							SetTakeOnFromCommon(nEquipNum, pstCommonItemSet);
							g_xClientSocket.SendTakeOnOffItem(CM_TAKEONITEM, (BYTE)nEquipNum, m_stTakeOnItemSet.xItem.m_stItemInfo.stStdItem.szName, m_stTakeOnItemSet.xItem.m_stItemInfo.nMakeIndex);
							pstCommonItemSet->bWaitResponse	= TRUE;
							return FALSE;
						}
					}
				}
			}
		}
	}

	return FALSE;
}



/******************************************************************************************************************

	함수명 : CStatusWnd::OnMouseMove()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : POINT ptMouse
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CStatusWnd::OnMouseMove(POINT ptMouse)
{
	m_xStatusBtn[_BTN_ID_STATUSCLOSE].OnMouseMove(ptMouse);
}



/******************************************************************************************************************

	함수명 : CStatusWnd::OnLButtonDown()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : LPCOMMONITEMSET pstCommonItemSet
	         POINT ptMouse
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CStatusWnd::OnLButtonDown(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse)
{
	INT nEquipNum;

	if ( m_xStatusBtn[_BTN_ID_STATUSCLOSE].OnLButtonDown(ptMouse) )	
		return TRUE;

	nEquipNum = GetEquipNum(ptMouse);

	return FALSE;
}

BOOL CStatusWnd::OnLButtonDoubleClick(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse)
{
	if ( pstCommonItemSet->bSetted && pstCommonItemSet->bWaitResponse )
	{
		return FALSE;
	}

	if ( !pstCommonItemSet->bIsEquipItem )
	{
		return FALSE;
	}

	INT nEquipNum = GetEquipNum(ptMouse);

	if ( !CheckEquipItem(&pstCommonItemSet->xItem, (BYTE)nEquipNum, ptMouse) )
		return FALSE;

	if ( pstCommonItemSet->bSetted && !pstCommonItemSet->bWaitResponse && !pstCommonItemSet->bIsDealItem )
	{			
		pstCommonItemSet->bWaitResponse = TRUE;
		SetEquipFromCommon(nEquipNum, pstCommonItemSet);
		g_xClientSocket.UseWearItem(CM_USEWEARITEM, nEquipNum);
		return TRUE;
	}

	return FALSE;
}

VOID CStatusWnd::RenderShine(INT nX, INT nY)
{
	LPGROUNDITEM pstItem = NULL;
	DWORD		 dwCurrTick = timeGetTime();

	if ( dwCurrTick - m_dwLastShineTick > 2000 )
	{
		if ( dwCurrTick - m_dwShineCurrDelay > 70 )
		{
			m_dwCurrShineFrm++;
			m_dwShineCurrDelay = timeGetTime();

			if ( m_dwCurrShineFrm > 9 )
			{
				m_dwLastShineTick = dwCurrTick;
				m_dwCurrShineFrm = 0;
				return;
			}
		}
		else
		{
			int n=0;
		}

		CWHWilImageData* pxShineImg = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE];
		if ( pxShineImg->NewSetIndex(m_dwCurrShineFrm+40) )
		{
			D3DMATERIAL7 mtrl;

			D3DVECTOR	vecTrans((FLOAT)nX, (FLOAT)nY, 0);
			D3DVECTOR	vecScale((FLOAT)pxShineImg->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxShineImg->m_lpstNewCurrWilImageInfo->shHeight, 0.0f);

			LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_PARTICLE, _IMAGE_PROGUSE, m_dwCurrShineFrm+40);

			D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)255/255.0f, (FLOAT)255/255.0f);
			mtrl.diffuse.a = 1.0f/255.0f;

			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr);
		}
	}
	return;
}

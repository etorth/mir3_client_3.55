/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"



CUserStateWnd::CUserStateWnd()
{
	Init();
}

CUserStateWnd::~CUserStateWnd()
{
	Destroy();
}

VOID CUserStateWnd::Init()
{
	CGameWnd::Init();

	m_xUStateCloseBtn.Init();
	m_xUStateGroupBtn.Init();
	m_xUStateWhisperBtn.Init();
	m_xUStateGiftBtn.Init();

	m_dwLastShineTick = 0;
	m_dwShineCurrDelay = 0;
	m_dwCurrShineFrm = 0;

	m_nFameIdx = 0;
	m_dwFameTimer = 0;

	// 절대검
	m_nLastSwordFrame = 0;
	m_dwLastSwordTick = 0;

	m_nCharmEftFrm	= 0;
	m_dwCharmTimer  = 0;

	m_nGhostAmorEftIdx = 0;
	m_dwGhostAmorTimer = 0;

	m_nOsungEftIdx = 0;
	m_dwOsungEftTimer = 0;

	m_nYonglinEftIdx = 0;
	m_dwYonglinEftTimer = 0;

	m_nMyungEftIdx = 0;
	m_dwMyungEftTimer = 0;

	m_nReddragonEftIdx = 0;
	m_dwReddragonEftTimer = 0;

	ZeroMemory(&m_stUserEquipItem, sizeof(ITEMSET)*_EQUIP_MAX_CELL);
	ZeroMemory(&m_stUserState, sizeof(USERSTATE));
	ZeroMemory(&m_rcUserCell, sizeof(RECT)*_EQUIP_MAX_CELL);
	ZeroMemory(&m_stUserFeature, sizeof(FEATURE));

	ZeroMemory(&m_pszUserName, 25);
	ZeroMemory(&m_pszGuildName, 30);
	ZeroMemory(&m_pszGuildRankName, 15);
	ZeroMemory(&m_pszMateName, 25);
}


VOID CUserStateWnd::Destroy()
{
	CGameWnd::Destroy();
}


VOID CUserStateWnd::CreateUserStateWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove)
{
	CreateGameWnd(nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight);

	m_xUStateCloseBtn.CreateGameBtn(pxWndImage,  1221,  1222, nStartX+201, nStartY+280, g_xMsg.GetMsg(1052), _BTN_TYPE_FOCUS, 1221, FALSE);
	m_xUStateGroupBtn.CreateGameBtn(pxWndImage,  201,  202, nStartX+201, nStartY+280, g_xMsg.GetMsg(4930), _BTN_TYPE_FOCUS, -1, TRUE);
	m_xUStateWhisperBtn.CreateGameBtn(pxWndImage,  203,  204, nStartX+201, nStartY+280, g_xMsg.GetMsg(4931), _BTN_TYPE_FOCUS, -1, TRUE);
	m_xUStateGiftBtn.CreateGameBtn(pxWndImage,  205,  206, nStartX+201, nStartY+280, g_xMsg.GetMsg(4932), _BTN_TYPE_FOCUS, -1, TRUE);
	// 장착창 초기화.
	SetRect(&m_rcUserCell[_U_NECKLACE], 175, 127, 175+_INVENTORY_CELL_WIDTH, 127+_INVENTORY_CELL_HEIGHT);
	SetRect(&m_rcUserCell[_U_RIGHTHAND], 97, 282,  97+_INVENTORY_CELL_WIDTH, 282+_INVENTORY_CELL_HEIGHT);
	SetRect(&m_rcUserCell[_U_CHARM],	177, 282,  177+_INVENTORY_CELL_WIDTH, 282+_INVENTORY_CELL_HEIGHT);
	SetRect(&m_rcUserCell[_U_ARMRINGL],  14, 166,  14+_INVENTORY_CELL_WIDTH, 166+_INVENTORY_CELL_HEIGHT);
	SetRect(&m_rcUserCell[_U_ARMRINGR], 175, 166, 175+_INVENTORY_CELL_WIDTH, 166+_INVENTORY_CELL_HEIGHT);
	SetRect(&m_rcUserCell[_U_RINGL],	 14, 206,  14+_INVENTORY_CELL_WIDTH, 206+_INVENTORY_CELL_HEIGHT);
	SetRect(&m_rcUserCell[_U_RINGR],    175, 206, 175+_INVENTORY_CELL_WIDTH, 206+_INVENTORY_CELL_HEIGHT);
	SetRect(&m_rcUserCell[_U_HELMET],	 100,  80, 130,  115);
	SetRect(&m_rcUserCell[_U_DRESS], 	  85, 125, 145,  210);
	SetRect(&m_rcUserCell[_U_WEAPON],	  35,  55,  80,  158);
	SetRect(&m_rcUserCell[_U_BOOTS],	 14, 271,  14+_INVENTORY_CELL_WIDTH, 271+_INVENTORY_CELL_HEIGHT);
	SetRect(&m_rcUserCell[_U_ETC],	 137, 282, 137+_INVENTORY_CELL_WIDTH, 282+_INVENTORY_CELL_HEIGHT);

	m_bOpa = 220;
}


VOID CUserStateWnd::ShowUserStateWnd()
{
	INT		nStartX, nStartY;
	
	ShowGameWnd();

	INT nImgIdx = 1860 + m_stUserState.m_bTitlenumber*20 + m_nFameIdx - 10;
	INT nStX, nStY;

	if ( g_dwCurrTime - m_dwFameTimer > 100 )
	{
		m_dwFameTimer = g_dwCurrTime;
		m_nFameIdx++;

		if ( m_stUserState.m_bTitlenumber == 3 )
		{
			if ( m_nFameIdx > 10 )
				m_nFameIdx = 0;
		}
		else if ( m_stUserState.m_bTitlenumber == 7 ) 
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
			nStX = 207;
			nStY = 35;
		}
	}

	if ( m_stUserState.m_bTitlenumber == 6 )
	{
		nStX = 224;
		nStY = 24;
	}
	else if ( m_stUserState.m_bTitlenumber == 7 ) 
	{
		nStX = 219;
		nStY = 19;
	}
	else
	{
		nStX = 235;
		nStY = 35;
	}

	if ( m_stUserState.m_bTitlenumber > 0 && m_stUserState.m_bTitlenumber < 8 )
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


	INT nFlagIdx = 1689 + m_stUserState.m_bGuildFlag;
	if ( g_xGameProc.m_xInterface.m_pxInterImg->NewSetIndex(nFlagIdx) )
	{
		WORD wClr = 0XFFFF;
		wClr = g_xMainWnd.ConvertColor24To16(RGB(m_stUserState.m_bFlagColorB*16, 
												 m_stUserState.m_bFlagColorG*16,
												 m_stUserState.m_bFlagColorR*16));

 		g_xMainWnd.DrawWithImageForCompClipRgn(m_rcWnd.left+212, m_rcWnd.top+150,
														  g_xGameProc.m_xInterface.m_pxInterImg->m_lpstNewCurrWilImageInfo->shWidth,
														  g_xGameProc.m_xInterface.m_pxInterImg->m_lpstNewCurrWilImageInfo->shHeight,
														  (WORD*)g_xGameProc.m_xInterface.m_pxInterImg->m_pbCurrImage, _CLIP_WIDTH, 600, wClr, 0XFFFF, 20);
	}

	INT nCnt;

	// 후광있는 옷인가를 확인한다. Wil파일 이미지리스트상에서 확인.
	WORD wLooks = m_stUserEquipItem[_U_DRESS].xItem.m_stItemInfo.stStdItem.wLooks;
	WORD w33Img[6] = {982, 992, 1002, 1012, 1022, 1032};	// Equip.wil
	WORD wBLightImg[6] = {100, 110, 101, 111, 102, 112};	// ProgUse.wil
	for ( nCnt = 0; nCnt < 6; nCnt++ )
	{
		if( wLooks == w33Img[nCnt] )
		{
			CWHWilImageData* pxPrgUse = &g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE];
			if ( pxPrgUse->NewSetIndex(wBLightImg[nCnt]) )
			{
				D3DMATERIAL7	mtrl;
				D3DVECTOR		vecTrans;
				D3DVECTOR		vecScale;

				INT nSX = m_rcWnd.left+_NEW_USERSTATUS_CHAR_X+pxPrgUse->m_lpstNewCurrWilImageInfo->shPX;
				INT nSY = m_rcWnd.top +_NEW_USERSTATUS_CHAR_Y+pxPrgUse->m_lpstNewCurrWilImageInfo->shPY;
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
	wLooks = m_stUserEquipItem[_U_DRESS].xItem.m_stItemInfo.stStdItem.wLooks;
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

				INT nSX = m_rcWnd.left+_NEW_USERSTATUS_CHAR_X+pxPrgUse->m_lpstNewCurrWilImageInfo->shPX;
				INT nSY = m_rcWnd.top +_NEW_USERSTATUS_CHAR_Y+pxPrgUse->m_lpstNewCurrWilImageInfo->shPY;
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

	// 후광있는 옷인가를 확인한다. Wil파일 이미지리스트상에서 확인.
	wLooks = m_stUserEquipItem[_U_DRESS].xItem.m_stItemInfo.stStdItem.wLooks;
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

				INT nSX = m_rcWnd.left+_NEW_USERSTATUS_CHAR_X+pxPrgUse->m_lpstNewCurrWilImageInfo->shPX;
				INT nSY = m_rcWnd.top +_NEW_USERSTATUS_CHAR_Y+pxPrgUse->m_lpstNewCurrWilImageInfo->shPY;
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

	// 후광있는 옷인가를 확인한다. Wil파일 이미지리스트상에서 확인.
	wLooks = m_stUserEquipItem[_U_DRESS].xItem.m_stItemInfo.stStdItem.wLooks;
	WORD w50Img[2] = {984, 994};	// Equip.wil
	WORD wBLightImg50[2] = {190, 191};	// ProgUse.wil
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

				INT nSX = m_rcWnd.left+_NEW_USERSTATUS_CHAR_X+pxPrgUse->m_lpstNewCurrWilImageInfo->shPX;
				INT nSY = m_rcWnd.top +_NEW_USERSTATUS_CHAR_Y+pxPrgUse->m_lpstNewCurrWilImageInfo->shPY;
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

	// 후광있는 옷인가를 확인한다. Wil파일 이미지리스트상에서 확인.
	wLooks = m_stUserEquipItem[_U_DRESS].xItem.m_stItemInfo.stStdItem.wLooks;
	WORD w51Img_2[2] = {985, 995};	// Equip.wil
	WORD wBLightImg51_2[2] = {171, 181};	// ProgUse.wil
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

				INT nSX = m_rcWnd.left+_NEW_USERSTATUS_CHAR_X+pxPrgUse->m_lpstNewCurrWilImageInfo->shPX;
				INT nSY = m_rcWnd.top +_NEW_USERSTATUS_CHAR_Y+pxPrgUse->m_lpstNewCurrWilImageInfo->shPY;
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
/*
	// 후광있는 옷인가를 확인한다. Wil파일 이미지리스트상에서 확인.
	wLooks = m_stUserEquipItem[_U_DRESS].xItem.m_stItemInfo.stStdItem.wLooks;
	WORD w51Img[2] = {985, 995};	// Equip.wil
	WORD wBLightImg51[2] = {171, 181};	// ProgUse.wil
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

				INT nSX = m_rcWnd.left+_NEW_USERSTATUS_CHAR_X+pxPrgUse->m_lpstNewCurrWilImageInfo->shPX;
				INT nSY = m_rcWnd.top +_NEW_USERSTATUS_CHAR_Y+pxPrgUse->m_lpstNewCurrWilImageInfo->shPY;
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
*/

	// 남자인지, 여자인지구분.
	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].NewSetIndex(m_stUserFeature.bGender) )
	{
		g_xMainWnd.DrawWithImageForComp(
						m_rcWnd.left+_NEW_USERSTATUS_CHAR_X+g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shPX, 
						m_rcWnd.top+_NEW_USERSTATUS_CHAR_Y+g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shPY, 
						g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shWidth, 
						g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shHeight,
						(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_pbCurrImage));
	}

	// 아이템 그리기.
	for ( nCnt = 0; nCnt < _EQUIP_MAX_CELL; nCnt++ )
	{
		if ( m_stUserEquipItem[nCnt].bSetted )
		{
//			m_stUserEquipItem[nCnt].xItem.m_stItemInfo.stStdItem.wLooks = 1;
			if ( nCnt!=_U_HELMET && nCnt!=_U_WEAPON && nCnt!=_U_DRESS )
			{
				nStartX = m_rcWnd.left+m_rcUserCell[nCnt].left;
				nStartY = m_rcWnd.top+m_rcUserCell[nCnt].top;
				
				if ( m_stUserEquipItem[nCnt].xItem.m_stItemInfo.Desc[8] == 1 &&
					m_stUserEquipItem[nCnt].xItem.m_stItemInfo.stStdItem.bStdMode != 5 && m_stUserEquipItem[nCnt].xItem.m_stItemInfo.stStdItem.bStdMode != 6 && 
					m_stUserEquipItem[nCnt].xItem.m_stItemInfo.stStdItem.bStdMode != 10 &&
					m_stUserEquipItem[nCnt].xItem.m_stItemInfo.stStdItem.bStdMode != 11 && 
					m_stUserEquipItem[nCnt].xItem.m_stItemInfo.stStdItem.bStdMode != 15 && 
					m_stUserEquipItem[nCnt].xItem.m_stItemInfo.stStdItem.bStdMode != 53 )
				{
					m_stUserEquipItem[nCnt].xItem.DrawItem(nStartX, nStartY);
					
					RenderShine(nStartX, nStartY);
				}
				else
				{
					m_stUserEquipItem[nCnt].xItem.DrawItem(nStartX, nStartY);
				}
				
				// 속성 부적 이펙트
				if ( nCnt == _U_CHARM )
				{
					if ( m_stUserEquipItem[nCnt].xItem.m_stItemInfo.stStdItem.FuncType != 0 && m_stUserEquipItem[nCnt].xItem.m_stItemInfo.stStdItem.bShape ==  9 )
					{
						INT nImgIdx = 2020 + (m_stUserEquipItem[nCnt].xItem.m_stItemInfo.stStdItem.FuncType-1)*10 + m_nCharmEftFrm;
						INT nStX, nStY;
						
						INT nDura = RoundFunc(m_stUserEquipItem[nCnt].xItem.m_stItemInfo.nDura, 100) * 255 / RoundFunc(m_stUserEquipItem[nCnt].xItem.m_stItemInfo.stStdItem.wDuraMax, 100);
						
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
						
						if ( m_stUserEquipItem[nCnt].xItem.m_stItemInfo.stStdItem.FuncType == 1 )
						{
							nStX = 170;
							nStY = 288;
						}
						else if ( m_stUserEquipItem[nCnt].xItem.m_stItemInfo.stStdItem.FuncType == 2 )
						{
							nStX = 170;
							nStY = 288;
						}
						else if ( m_stUserEquipItem[nCnt].xItem.m_stItemInfo.stStdItem.FuncType == 3 )
						{
							nStX = 170;
							nStY = 288;
						}
						else if ( m_stUserEquipItem[nCnt].xItem.m_stItemInfo.stStdItem.FuncType == 4 )
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
				// 79 = 지존패 by eriastoa 2006.04.25 드디어 찾았다
				if ( m_stUserEquipItem[_U_ETC].xItem.m_stItemInfo.stStdItem.wLooks == 79 )
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
				nStartX = m_rcWnd.left+_NEW_USERSTATUS_CHAR_X;
				nStartY = m_rcWnd.top+_NEW_USERSTATUS_CHAR_Y;

				m_stUserEquipItem[nCnt].xItem.DrawItemUseColorIdx(nStartX, nStartY, m_stUserState.m_bWeaponColor, _ITEM_TYPE_EQUIP);
			}
			// 옷
			else
			{
				nStartX = m_rcWnd.left+_NEW_USERSTATUS_CHAR_X;
				nStartY = m_rcWnd.top+_NEW_USERSTATUS_CHAR_Y;

				m_stUserEquipItem[nCnt].xItem.DrawItem(nStartX, nStartY, _ITEM_TYPE_EQUIP);
			}
		}
	}

	// 머리종류.
	if ( m_stUserFeature.bHair > 0 && m_stUserFeature.bHair <= 10 && !m_stUserEquipItem[_U_HELMET].bSetted)
	{
		BYTE bHair = (BYTE)(m_stUserFeature.bGender*10 + (m_stUserFeature.bHair-1) + 60);

		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].NewSetIndex(bHair) )
		{
			g_xMainWnd.DrawWithImageForComp(
							m_rcWnd.left+_NEW_USERSTATUS_CHAR_X+g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shPX, 
							m_rcWnd.top+_NEW_USERSTATUS_CHAR_Y+g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shPY, 
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shWidth, 
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_lpstNewCurrWilImageInfo->shHeight,
							(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_PROGUSE].m_pbCurrImage), 
							m_stUserState.wHairColor, 0XFFFF);
		}
	}

	// 후광있는 옷인가를 확인한다. Wil파일 이미지리스트상에서 확인. (귀혼마갑)
	// 귀혼마갑 상태창 이펙트
	wLooks = m_stUserEquipItem[_U_DRESS].xItem.m_stItemInfo.stStdItem.wLooks;
	WORD w58Img[2] = {986, 996};	// Equip.wil
	WORD wBLightImg58[2] = {281, 291};	// ProgUse.wil

	switch ( m_stUserState.bJob )
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

				INT nSX = m_rcWnd.left+_NEW_EQUIP_CHAR_X+pxPrgUse->m_lpstNewCurrWilImageInfo->shPX + 2;
				INT nSY = m_rcWnd.top +_NEW_EQUIP_CHAR_Y+pxPrgUse->m_lpstNewCurrWilImageInfo->shPY + 2;
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



	// 호신보갑. 상태창 이펙트
	wLooks = m_stUserEquipItem[_U_DRESS].xItem.m_stItemInfo.stStdItem.wLooks;
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
	wLooks = m_stUserEquipItem[_U_DRESS].xItem.m_stItemInfo.stStdItem.wLooks;
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

			if ( m_stUserFeature.bGender == _GENDER_MAN )
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
	wLooks = m_stUserEquipItem[_U_DRESS].xItem.m_stItemInfo.stStdItem.wLooks;
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

			if ( m_stUserFeature.bGender == _GENDER_MAN )
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
	wLooks = m_stUserEquipItem[_U_DRESS].xItem.m_stItemInfo.stStdItem.wLooks;
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

			if ( m_stUserFeature.bGender == _GENDER_MAN )
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
	wLooks = m_stUserEquipItem[_U_DRESS].xItem.m_stItemInfo.stStdItem.wLooks;
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

			if ( m_stUserFeature.bGender == _GENDER_MAN )
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
	wLooks = m_stUserEquipItem[_U_DRESS].xItem.m_stItemInfo.stStdItem.wLooks;
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

			if ( m_stUserFeature.bGender == _GENDER_MAN )
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
	

	// 절대검
	if ( m_stUserEquipItem[_U_WEAPON].xItem.m_stItemInfo.stStdItem.wLooks == 1076 )
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

			INT nSX = m_rcWnd.left+_NEW_USERSTATUS_CHAR_X+pxPrgUse->m_lpstNewCurrWilImageInfo->shPX;
			INT nSY = m_rcWnd.top +_NEW_USERSTATUS_CHAR_Y+pxPrgUse->m_lpstNewCurrWilImageInfo->shPY;
			vecTrans = D3DVECTOR((FLOAT)nSX, (FLOAT)nSY, 0);
			vecScale = D3DVECTOR((FLOAT)pxPrgUse->m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)pxPrgUse->m_lpstNewCurrWilImageInfo->shHeight, 1);
			LPDIRECTDRAWSURFACE7 lpddsTextr = g_xGameProc.m_xImage.GetTextrImg(_TEXTR_FILE_INTER, _IMAGE_PROGUSE, m_nLastSwordFrame);
			D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)180/255.0f, (FLOAT)100/255.0f);
			mtrl.diffuse.a = (FLOAT)1.0f/255.0f;
			g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, lpddsTextr, _BLEND_LIGHT);
		}
	}

	//	ShowUserItemState();

	RECT	rcID;

	if (m_pszGuildName[0])
		SetRect(&rcID, m_rcWnd.left+80, m_rcWnd.top+15, m_rcWnd.left+205, m_rcWnd.top+31);
	else
		SetRect(&rcID, m_rcWnd.left+80, m_rcWnd.top+30, m_rcWnd.left+205, m_rcWnd.top+50);

	g_xMainWnd.PutsHan(NULL, rcID, RGB(220, 255, 220), RGB(0, 0, 0), m_pszUserName, g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));

	if ( m_pszGuildName[0] )
	{
		CHAR	pszGuild[50];
		ZeroMemory(pszGuild, 50);

		sprintf(pszGuild, "%s", m_pszGuildName);

		rcID.top		+= 15;
		rcID.bottom		+= 15;
		g_xMainWnd.PutsHan(NULL, rcID, RGB(255, 250, 180), RGB(0, 0, 0), pszGuild);

		if ( m_pszGuildRankName[0] )
		{
			sprintf(pszGuild, "%s", m_pszGuildRankName);
			rcID.top		+= 14;
			rcID.bottom		+= 14;
			g_xMainWnd.PutsHan(NULL, rcID, RGB(255, 200, 150), RGB(0, 0, 0), pszGuild);
		}
	}

	if ( m_pszMateName[0] )
	{
		SetRect(&rcID, m_rcWnd.left+96, m_rcWnd.top+67, m_rcWnd.left+206, m_rcWnd.top+82);
		g_xMainWnd.PutsHan(NULL, rcID, RGB(244, 62, 235), RGB(0, 0, 0), m_pszMateName);

		if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(1298) )
		{
			g_xMainWnd.DrawWithImageForComp(
											rcID.left - 18, 
											rcID.top + 1, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage));
		}
	}



	m_xUStateCloseBtn.ChangeRect(m_rcWnd.left+246, m_rcWnd.top+330);
	m_xUStateGroupBtn.ChangeRect(m_rcWnd.left+24, m_rcWnd.top+327);
	m_xUStateWhisperBtn.ChangeRect(m_rcWnd.left+64, m_rcWnd.top+327);
	m_xUStateGiftBtn.ChangeRect(m_rcWnd.left+104, m_rcWnd.top+327);

	m_xUStateCloseBtn.ShowGameBtn();
	m_xUStateGroupBtn.ShowGameBtn();
	m_xUStateWhisperBtn.ShowGameBtn();
	m_xUStateGiftBtn.ShowGameBtn();
}


VOID CUserStateWnd::SetStatusBtnInit()
{
	m_xUStateCloseBtn.SetBtnState(_BTN_STATE_NORMAL);
}


VOID CUserStateWnd::SetUserState(LPUSERSTATE pstUserState)
{
	CItem xItem;
	
	// 필요한 부분을 초기화한다.
	ZeroMemory(&m_stUserEquipItem, sizeof(ITEMSET)*_EQUIP_MAX_CELL);
	ZeroMemory(&m_stUserState, sizeof(USERSTATE));
	ZeroMemory(&m_stUserFeature, sizeof(FEATURE));

	ZeroMemory(&m_pszUserName, 25);
	ZeroMemory(&m_pszGuildName, 30);
	ZeroMemory(&m_pszGuildRankName, 15);

	// 받은정보 대입.
	memcpy(&m_stUserState, pstUserState, sizeof(USERSTATE));
	memcpy(&m_stUserFeature, &m_stUserState.nFeature, sizeof(FEATURE));

	m_stUserFeature.bDress = m_stUserFeature.bDress & 15;

	// 상대 케릭터 정보 머리모양 안나오는것 
	// 주석처리 한 후 나온다. 왜 연산을 한것일까? 누가 했을까? 궁금하네.
	//m_stUserFeature.bHair = m_stUserFeature.bHair & 0x00111111;

	memcpy(m_pszUserName, &m_stUserState.pszUserName, 24);
	memcpy(m_pszGuildName, &m_stUserState.pszGuildName, 29);
	memcpy(m_pszGuildRankName, &m_stUserState.pszGuildRankName, 14);
	memcpy(m_pszMateName, &m_stUserState.pszMateName, 25);

	for ( INT nCnt = 0; nCnt < _EQUIP_MAX_CELL; nCnt++ )
	{
		if ( m_stUserState.stEquipItem[nCnt].stStdItem.szName[0] != NULL )
		{
			xItem.SetItem(m_stUserState.stEquipItem[nCnt], 0);
			AddEquipItem(xItem, nCnt);
		}
	}
}


BOOL CUserStateWnd::AddEquipItem(CItem xItem, INT nEquipNum)
{
	if ( !m_stUserEquipItem[nEquipNum].bSetted )
	{
		m_stUserEquipItem[nEquipNum].bSetted = TRUE;
		m_stUserEquipItem[nEquipNum].xItem = xItem;
		m_stUserEquipItem[nEquipNum].xItem.m_shCellNum = (SHORT)nEquipNum;

		return TRUE;
	}
	return FALSE;
}

INT CUserStateWnd::GetEquipNum(POINT ptMouse)
{
	RECT rc;
	for ( INT nCnt = 0; nCnt < _EQUIP_MAX_CELL; nCnt++ )
	{
		SetRect(&rc, m_rcWnd.left+m_rcUserCell[nCnt].left, m_rcWnd.top+m_rcUserCell[nCnt].top, 
			    m_rcWnd.left+m_rcUserCell[nCnt].left+(m_rcUserCell[nCnt].right-m_rcUserCell[nCnt].left), m_rcWnd.top+m_rcUserCell[nCnt].top+(m_rcUserCell[nCnt].bottom-m_rcUserCell[nCnt].top));
		if ( PtInRect(&rc, ptMouse) )
		{
			return nCnt;
		}
	}

	return -1;
}

VOID CUserStateWnd::ShowUserItemState()
{
	INT nEquipNum = GetEquipNum(g_xGameProc.m_ptMousePos);

	if ( nEquipNum != -1 )
	{
		if ( m_stUserEquipItem[nEquipNum].bSetted )
		{
			INT nStartX = m_rcWnd.left+m_rcUserCell[nEquipNum].left;
			INT nStartY = m_rcWnd.top +m_rcUserCell[nEquipNum].top;

			m_stUserEquipItem[nEquipNum].xItem.ShowItemStatus(nStartX+15, nStartY+15);
		}		
	}
}


BOOL CUserStateWnd::OnLButtonUp(POINT ptMouse)
{
	if ( m_xUStateCloseBtn.OnLButtonUp(ptMouse) )		
	{
		return TRUE;
	}

	if ( m_xUStateGroupBtn.OnLButtonUp(ptMouse) )		
	{
		if ( g_xGameProc.m_xInterface.m_xGroupWnd.m_xGroupList.GetCount() > 0 )
		{
			g_xClientSocket.SendAddGroupMember(m_pszUserName);
		}
		else
		{
			g_xClientSocket.SendCreateGroup(m_pszUserName);
		}

		return FALSE;
	}

	if ( m_xUStateWhisperBtn.OnLButtonUp(ptMouse) )		
	{
		SetFocus(g_xChatEditBox.GetSafehWnd());
		ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);

		CHAR szTemp[MAX_PATH];

		sprintf(szTemp, "/%s ", m_pszUserName);

		SetWindowText(g_xChatEditBox.GetSafehWnd(), szTemp);

		INT nLen = strlen(szTemp);
		SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETSEL, nLen , nLen);
		g_xChatEditBox.SetHanguelMode();
		g_xGameProc.m_xInterface.m_xChatWnd.ActiveEditBox();

		return FALSE;
	}

	if ( m_xUStateGiftBtn.OnLButtonUp(ptMouse) )		
	{
		if ( !g_xGameProc.m_xInterface.m_xMessengerWnd.GetGameWndActive() )
		{
			g_xGameProc.m_xInterface.WindowActivate(_WND_ID_MESSENGER);

			g_xGameProc.m_xInterface.m_xMessengerWnd.mMessenger_nMode = _WRITE_BOX;
			sprintf( g_xGameProc.m_xInterface.m_xMessengerWnd.mMessenger_szWriteID, m_pszUserName);
		}

		return FALSE;
	}

	return FALSE;
}


BOOL CUserStateWnd::OnLButtonDown(POINT ptMouse)
{
	if ( m_xUStateCloseBtn.OnLButtonDown(ptMouse) )	
	{
		return TRUE;
	}

	if ( m_xUStateGroupBtn.OnLButtonDown(ptMouse) )	
	{
		return TRUE;
	}

	if ( m_xUStateWhisperBtn.OnLButtonDown(ptMouse) )	
	{
		return TRUE;
	}

	if ( m_xUStateGiftBtn.OnLButtonDown(ptMouse) )	
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CUserStateWnd::OnLButtonDoubleClick(POINT ptMouse)
{
	if ( m_pszGuildName[0] )
	{
		RECT rcGuild = { m_rcWnd.left + 80, m_rcWnd.top+30, m_rcWnd.left + 205, m_rcWnd.top+46};

		if ( PtInRect(&rcGuild, ptMouse) )
		{
			CHAR szGuild[MAX_PATH];

			g_xGameProc.m_xInterface.m_xChatWnd.ActiveEditBox();
			sprintf(szGuild, &m_pszGuildName[0]);
			SetFocus(g_xChatEditBox.GetSafehWnd());
			ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);
			SetWindowText(g_xChatEditBox.GetSafehWnd(), szGuild);

			INT nLen = strlen(szGuild);
			SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETSEL, nLen , nLen);
			g_xChatEditBox.SetHanguelMode();
		}
	}


	return FALSE;
}


VOID CUserStateWnd::OnMouseMove(POINT ptMouse)
{
	m_xUStateCloseBtn.OnMouseMove(ptMouse);
	m_xUStateGroupBtn.OnMouseMove(ptMouse);
	m_xUStateWhisperBtn.OnMouseMove(ptMouse);
	m_xUStateGiftBtn.OnMouseMove(ptMouse);
}

VOID CUserStateWnd::RenderShine(INT nX, INT nY)
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

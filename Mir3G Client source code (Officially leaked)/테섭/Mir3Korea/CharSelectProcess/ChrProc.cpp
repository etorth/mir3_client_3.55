#include "StdAfx.h"



//-----------------------------------------------------------------------------------------------------------------
// Procedure 관리함수.
//-----------------------------------------------------------------------------------------------------------------
/******************************************************************************************************************
[생성자]
*******************************************************************************************************************/
CChrProcess::CChrProcess()
{
	Init();
}


/******************************************************************************************************************
[소멸자]
*******************************************************************************************************************/
CChrProcess::~CChrProcess()
{
	DeleteProc();
}


/******************************************************************************************************************
변수및 모든객체를 초기화.
*******************************************************************************************************************/
VOID CChrProcess::Init()
{
	m_nPageNum = 0;

	m_xMsgBox.InitMsgBox();
	m_xImageInter.Init();
	m_xImageChr.Init();
	m_xAvi.Init();

	ZeroMemory(&m_ptMousePos, sizeof(POINT));

	m_hBrush = NULL;

 	D3DVECTOR vNorm(0, 0, -1);
	m_avBillBoard[0]  = D3DVERTEX(D3DVECTOR(-0.5f, 0.5f, 0), vNorm, 0, 0);
	m_avBillBoard[1]  = D3DVERTEX(D3DVECTOR(-0.5f,-0.5f, 0), vNorm, 0, 1);
	m_avBillBoard[2]  = D3DVERTEX(D3DVECTOR( 0.5f, 0.5f, 0), vNorm, 1, 0);
	m_avBillBoard[3]  = D3DVERTEX(D3DVECTOR( 0.5f,-0.5f, 0), vNorm, 1, 1);

	ZeroMemory(m_stSelectChrInfo, _MAX_CHAR*sizeof(CHARINFO));
	ZeroMemory(m_stCreateChrInfo, _MAX_CHAR*sizeof(CHARINFO));
	ZeroMemory(m_stChrSprInfo   , _MAX_SPR_KIND*sizeof(CHARSPRINFO));
	m_bChrProcState = _CHR_PROC_SELECT;

	m_bBGMPlay     = FALSE;
	m_bBGMPlayTime = 0;			
	
	m_nSelectedChr = _SELECTED_NONE;
	SetRect(&m_rcSelectChrInfo, 0, 0, 0, 0);
	ZeroMemory(&m_stSelShowInfo, sizeof(SELCHRSHOWINFO));
	
	m_nCreatedChr  = _SELECTED_FST_CHR;
	m_nDividedExplain = 0;
	SetRect(&m_rcChrExplain, 0, 0, 0, 0);
	ZeroMemory(&m_pszChrExplain, 15*MAX_PATH);

	m_nCharCnt = 0;
	m_nTotalPageNum = 0;

	m_bFrontSetofSelChar = TRUE;
	m_bMoreTwoChar = FALSE;

	INT nCnt;

	for ( nCnt = 0; nCnt < _MAX_CHR_SELECT_BTN; nCnt++ )
	{
		m_xSelectBtn[nCnt].Init();
	}

	for ( nCnt = 0; nCnt < _CHR_CHR_CREATE_BTN; nCnt++ )
	{
		m_xCreateBtn[nCnt].Init();
	}

	m_dwWaitTick = 0;
}


/******************************************************************************************************************
필요한 데이타를 초기화하고 로드한다.
Prcedure가 시작되기전에 호출되어야 한다.
Load()->RenderScene()->SetNextProc()의 형태이다.
*******************************************************************************************************************/
VOID CChrProcess::Load()
{
	Init();

	m_xImageInter.NewLoad(".\\Data\\gameinter.wil");
	m_xImageChr.NewLoad(".\\Data\\Interface1c.wil");

	// EditBox설정(Password상태해제).
	ZeroMemory(g_xChatEditBox.m_szInputMsg, sizeof(g_xChatEditBox.m_szInputMsg));
	SetWindowText(g_xChatEditBox.GetSafehWnd(), "");
	SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETPASSWORDCHAR, NULL, 0);
	g_xChatEditBox.SetLimitText(13);
	g_xChatEditBox.SetEnterUse(FALSE);
	MoveWindow(g_xChatEditBox.GetSafehWnd(), g_xMainWnd.m_rcWindow.left+288, g_xMainWnd.m_rcWindow.top+405, 75, 13, TRUE);
	ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_HIDE);

	if ( m_hBrush != NULL )
	{
		DeleteObject(m_hBrush);
		m_hBrush = NULL;
	}
	m_hBrush = CreateSolidBrush(RGB(0, 0, 0));

	g_xClientSocket.ConnectToServer(g_xMainWnd.GetSafehWnd(), g_szServerIP, g_nServerPort);

	m_xSelectBtn[_MAX_CHR_SELECT_CREATE].CreateGameBtn(&m_xImageChr, 51, 51, 440,  93, NULL, _BTN_TYPE_FOCUS, 52, TRUE);
	m_xSelectBtn[_MAX_CHR_SELECT_DELETE].CreateGameBtn(&m_xImageChr, 53, 53,  79, 243, NULL, _BTN_TYPE_FOCUS, 54, TRUE);
	m_xSelectBtn[_MAX_CHR_SELECT_START]. CreateGameBtn(&m_xImageChr, 55, 55, 259,  49, NULL, _BTN_TYPE_FOCUS, 56, TRUE);
	m_xSelectBtn[_MAX_CHR_SELECT_QUIT].  CreateGameBtn(&m_xImageChr, 57, 57,  28, 438, NULL, _BTN_TYPE_FOCUS, 58, TRUE);
	m_xSelectBtn[_MAX_CHR_SELECT_NEXT].  CreateGameBtn(&m_xImageInter, 1155, 1154, 550, 400, NULL, _BTN_TYPE_FOCUS, 1153, FALSE);
	m_xSelectBtn[_MAX_CHR_SELECT_BEFORE].CreateGameBtn(&m_xImageInter, 1152, 1152, 500, 400, NULL, _BTN_TYPE_FOCUS, 1152, FALSE);
	

	m_xCreateBtn[_CHR_CHR_CREATE_WARIOR].  CreateGameBtn(&m_xImageChr, 92, 93, 266, 419, NULL, _BTN_TYPE_FOCUS, 91, TRUE);
	m_xCreateBtn[_CHR_CHR_CREATE_MAGICIAN].CreateGameBtn(&m_xImageChr, 95, 96, 308, 419, NULL, _BTN_TYPE_FOCUS, 94, TRUE);
	m_xCreateBtn[_CHR_CHR_CREATE_CLERIC].  CreateGameBtn(&m_xImageChr, 98, 99, 352, 419, NULL, _BTN_TYPE_FOCUS, 97, TRUE);
	m_xCreateBtn[_CHR_CHR_CREATE_MAKE].    CreateGameBtn(&m_xImageChr, 86, 87, 450, 444, NULL, _BTN_TYPE_FOCUS, 85, TRUE);
	m_xCreateBtn[_CHR_CHR_CREATE_CANCEL].  CreateGameBtn(&m_xImageChr, 89, 90, 491, 444, NULL, _BTN_TYPE_FOCUS, 88, TRUE);
	m_xCreateBtn[_CHR_CHR_CREATE_ARCHER].  CreateGameBtn(&m_xImageChr, 101, 102, 390, 419, NULL, _BTN_TYPE_FOCUS, 100, TRUE);

	SetChrSelSprite();

	m_bBGMPlay	   = TRUE;
	m_bBGMPlayTime = 0;

	SndObjDestroy(m_stEffctWav[0]);
	SndObjDestroy(m_stEffctWav[1]);
	SndObjDestroy(m_stEffctWav[2]);
	m_stEffctWav[0] = SndObjCreate(g_SoundManager.mSound_lpds, ".\\Sound\\CreateChr.wav", 10);
	m_stEffctWav[1] = SndObjCreate(g_SoundManager.mSound_lpds, ".\\Sound\\SelChr.wav"   , 10);
	m_stEffctWav[2] = SndObjCreate(g_SoundManager.mSound_lpds, ".\\Sound\\StartGame.wav", 10);

	SndObjDestroy(m_stCreateWav[0][0]);
	SndObjDestroy(m_stCreateWav[0][1]);
	SndObjDestroy(m_stCreateWav[0][2]);
	SndObjDestroy(m_stCreateWav[1][0]);
	SndObjDestroy(m_stCreateWav[1][1]);
	SndObjDestroy(m_stCreateWav[1][2]);
	m_stCreateWav[0][0] = SndObjCreate(g_SoundManager.mSound_lpds, ".\\Sound\\JMCre.wav", 10);
	m_stCreateWav[0][1] = SndObjCreate(g_SoundManager.mSound_lpds, ".\\Sound\\SMCre.wav", 10);
	m_stCreateWav[0][2] = SndObjCreate(g_SoundManager.mSound_lpds, ".\\Sound\\DMCre.wav", 10);
	m_stCreateWav[1][0] = SndObjCreate(g_SoundManager.mSound_lpds, ".\\Sound\\JWCre.wav", 10);
	m_stCreateWav[1][1] = SndObjCreate(g_SoundManager.mSound_lpds, ".\\Sound\\SWCre.wav", 10);
	m_stCreateWav[1][2] = SndObjCreate(g_SoundManager.mSound_lpds, ".\\Sound\\DWCre.wav", 10);

	// 배열의 순서 -> 성별, 직업.
	SndObjDestroy(m_stSelectWav[0][0]);
	SndObjDestroy(m_stSelectWav[0][1]);
	SndObjDestroy(m_stSelectWav[0][2]);
	SndObjDestroy(m_stSelectWav[1][0]);
	SndObjDestroy(m_stSelectWav[1][1]);
	SndObjDestroy(m_stSelectWav[1][2]);

	// 남자, 전사.
	m_stSelectWav[0][0] = SndObjCreate(g_SoundManager.mSound_lpds, ".\\Sound\\JMMSel.wav", 10);
	// 여자, 전사.
	m_stSelectWav[1][0] = SndObjCreate(g_SoundManager.mSound_lpds, ".\\Sound\\JWMSel.wav", 10);
	// 남자, 술사.
	m_stSelectWav[0][1] = SndObjCreate(g_SoundManager.mSound_lpds, ".\\Sound\\SMMSel.wav", 10);
	// 여자, 술사.
	m_stSelectWav[1][1] = SndObjCreate(g_SoundManager.mSound_lpds, ".\\Sound\\SWMSel.wav", 10);
	// 남자, 도사.
	m_stSelectWav[0][2] = SndObjCreate(g_SoundManager.mSound_lpds, ".\\Sound\\DMMSel.wav", 10);
	// 여자, 도사.
	m_stSelectWav[1][2] = SndObjCreate(g_SoundManager.mSound_lpds, ".\\Sound\\DWMSel.wav", 10);

	m_xMsgBox.CreateMsgBox(&m_xImageInter, 0, _NONE, g_xMsg.GetMsg(200), FALSE, 155, 150);
	m_dwWaitTick = timeGetTime();
		
}


/******************************************************************************************************************
소멸이 필요한 객체를 정리.
Procedure가 종료되거나, 현상태에서 프로그램을 종료시킬때 호출된다.
*******************************************************************************************************************/
VOID CChrProcess::DeleteProc()
{
	m_xImageInter.Destroy();
	m_xImageChr.Destroy();

	g_xClientSocket.DisconnectToServer();

	if ( m_hBrush != NULL )
	{
		DeleteObject(m_hBrush);
		m_hBrush = NULL;
	}

	m_xAvi.Release();

	// Edit Box설정을 원래대로 되돌린다.
	g_xChatEditBox.SetEnterUse(TRUE);
}


/******************************************************************************************************************
다음 Procedure로 세팅.
호출되면 다음루프부터는 Procedure가 바뀐다.
*******************************************************************************************************************/
VOID CChrProcess::SetNextProc()
{
	DeleteProc();
 	g_xClientSocket.m_pxDefProc = g_xMainWnd.m_pxDefProcess = &g_xGameProc;
	g_xGameProc.Load();
	g_bProcState = _GAME_PROC; 
//	SetTimer(g_xMainWnd.GetSafehWnd(), _TIMER_SYSTIME, 1000, NULL);
	g_xMainWnd.m_bIsActiveChanged = FALSE;
}


//-----------------------------------------------------------------------------------------------------------------
// 화면 Render관련 함수.
//-----------------------------------------------------------------------------------------------------------------
/******************************************************************************************************************
3D 평면판에 텍스춰를 올려서 그린다.
lpDevice   : 초기 DX3D세팅시 얻은 3D장치Device.
pvTrans    : 찍을좌표를 정의한 벡터의 포인터.(픽셀좌표)
pvScale    : 이미지의 크기를 정의한 벡터의 포인터.
pmtrl	   : 적용된 Matrial의 포인터.
lpddsTextr : 텍스춰로 쓰일 Surface.
bBlendType : 화면에 보여줄 형태.
*******************************************************************************************************************/
HRESULT CChrProcess::DrawBillBoard(LPDIRECT3DDEVICE7 lpDevice, D3DVECTOR* pvTrans, D3DVECTOR* pvScale, /*D3DVECTOR vRot, */D3DMATERIAL7* pmtrl, /*FLOAT fRotRad, */LPDIRECTDRAWSURFACE7 lpddsTextr, BYTE bBlendType)
{
	if ( lpDevice )
	{
		D3DMATRIX matTrans;
		D3DMATRIX matScale;
		D3DMATRIX matRot;
		D3DMATRIX matWorld;
		D3DMATRIX matWorldOriginal;

		pvTrans->x =  pvTrans->x+pvScale->x/2-320;
		pvTrans->y = -pvTrans->y-pvScale->y/2+240;
		lpDevice->SetMaterial(pmtrl);

		if( SUCCEEDED(lpDevice->BeginScene()) )
		{
			lpDevice->GetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

			D3DUtil_SetTranslateMatrix(matTrans, *pvTrans);
			D3DUtil_SetScaleMatrix(matScale, pvScale->x, pvScale->y, pvScale->z);
			D3DMath_MatrixMultiply(matWorld, matScale, matTrans);
			lpDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);

			SetBlendRenderState(lpDevice, bBlendType, pmtrl);

			lpDevice->SetTexture(0, lpddsTextr);

			lpDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_VERTEX, m_avBillBoard, 4, NULL);

			ResetBlendenderState(lpDevice);

			lpDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

			lpDevice->EndScene();

			return S_OK;
		}
	}
	return E_FAIL;
}


/******************************************************************************************************************
캐릭터의 효과.

- 렌더링 시점에서 텍스쳐를 만들어서 그리고 다시 파괴하는 루프가 과연 어느정도의 부하를 가지고 있을까?
- 부하가 상당할 것 같은데... ( by eriastoa 06.03.27 )
*******************************************************************************************************************/
VOID CChrProcess::DrawCharEffect(INT nIdx, INT nX, INT nY)
{
	if ( g_xMainWnd.Get3DDevice() )
	{
		D3DWILTextr_CreateEmptyTexture(m_xImageChr.m_szWilFileName, nIdx, 
									   m_xImageChr.m_lpstNewCurrWilImageInfo->shWidth,
									   m_xImageChr.m_lpstNewCurrWilImageInfo->shHeight,
									   (WORD*)m_xImageChr.m_pbCurrImage, D3DTEXTR_TRANSPARENTBLACK);
		D3DWILTextr_Restore(m_xImageChr.m_szWilFileName, nIdx, g_xMainWnd.Get3DDevice());

		D3DVECTOR vTrans;
		D3DMATRIX matTrans;
		D3DMATRIX matScale;
		D3DMATRIX matWorld;
		D3DMATRIX matWorldOriginal;
		D3DMATERIAL7 mtrl;

		D3DUtil_InitMaterial(mtrl, (FLOAT)255.0f/255.0f, (FLOAT)255.0f/255.0f, (FLOAT)255.0f/255.0f);
		mtrl.diffuse.a = 0/255.0f;
		g_xMainWnd.Get3DDevice()->SetMaterial(&mtrl);

		vTrans.x = (FLOAT) nX+(FLOAT)m_xImageChr.m_lpstNewCurrWilImageInfo->shWidth /2+m_xImageChr.m_lpstNewCurrWilImageInfo->shPX-320; 
		vTrans.y = (FLOAT)-nY-(FLOAT)m_xImageChr.m_lpstNewCurrWilImageInfo->shHeight/2-m_xImageChr.m_lpstNewCurrWilImageInfo->shPY+240; 
		vTrans.z = 0.0f;

		if( SUCCEEDED(g_xMainWnd.Get3DDevice()->BeginScene()))
		{
			g_xMainWnd.Get3DDevice()->GetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

			D3DUtil_SetTranslateMatrix(matTrans, vTrans);
			D3DUtil_SetScaleMatrix(matScale, (FLOAT)m_xImageChr.m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)m_xImageChr.m_lpstNewCurrWilImageInfo->shHeight, 1.0f);
			D3DMath_MatrixMultiply(matWorld, matScale, matTrans);
			g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);
			
			SetBlendRenderState(g_xMainWnd.Get3DDevice(), _BLEND_LIGHT, &mtrl);

			g_xMainWnd.Get3DDevice()->SetTexture(0, D3DWILTextr_GetSurface(m_xImageChr.m_szWilFileName, nIdx));

			g_xMainWnd.Get3DDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_VERTEX, m_avBillBoard, 4, NULL);

			ResetBlendenderState(g_xMainWnd.Get3DDevice());

			g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

			g_xMainWnd.Get3DDevice()->EndScene();
		}

		D3DWILTextr_Invalidate(m_xImageChr.m_szWilFileName, nIdx);
		D3DWILTextr_DestroyTexture(m_xImageChr.m_szWilFileName, nIdx);
	}
}


/******************************************************************************************************************
Procedure의 메인루프.
*******************************************************************************************************************/
VOID CChrProcess::RenderScene(INT nLoopTime)
{	
	Clear(RGB(0, 0, 0));

	if ( g_xMainWnd.m_bIsActiveChanged )
	{
		if ( g_xMainWnd.GetScreenMode() & _DXG_SCREENMODE_FULLSCREEN )
		{
			g_xGameProc.m_bRender = FALSE;
			g_xMainWnd.m_bIsWindowReady = FALSE;

			SetFocus(g_xMainWnd.GetSafehWnd());

			if ( FAILED(g_xMainWnd.ResetDXG(640, 480, 16, _DXG_SCREENMODE_FULLSCREEN, _DXG_DEVICEMODE_PRIMARY|_DXG_DEVICEMODE_D3D)) )
			{
				MessageBox(g_xMainWnd.GetSafehWnd(), TEXT("DirectDraw RESETUP failed!!!") TEXT("The Program will now exit."), TEXT("MirDXG"), MB_ICONERROR | MB_OK);
			}
			
			g_xMainWnd.m_bIsWindowReady = TRUE;
		}

		g_xMainWnd.m_bIsActiveChanged = FALSE;
	}

	switch ( m_bChrProcState )
	{
		case _CHR_PROC_SELECT:
		{
			RenderSelect(nLoopTime);
			m_xMsgBox.RenderMsgBox(m_ptMousePos);
			break;
		}
		case _CHR_PROC_CREATE:
		{
			RenderCreate(nLoopTime);
			m_xMsgBox.RenderMsgBox(m_ptMousePos);
			break;
		}
		case _CHR_PROC_CREATEIN:
		{
			if ( !m_xAvi.Draw(g_xMainWnd.GetBackBuffer()) )
			{
				Sleep(100);
				m_xAvi.Release();
				m_bChrProcState = _CHR_PROC_CREATE;

				m_bBGMPlay	   = TRUE;
				m_bBGMPlayTime = 0;

				// 남자전사의 설명창 로드.
				SetCharExplain(_GENDER_MAN, _JOB_JUNSA);

//				g_SoundManager.SndmngrPlayMp3(".\\Sound\\CreateChr.mp3", TRUE);

				SetWindowText(g_xChatEditBox.GetSafehWnd(), "");
				SetFocus(g_xChatEditBox.GetSafehWnd());
				MoveWindow(g_xChatEditBox.GetSafehWnd(), g_xMainWnd.m_rcWindow.left+288, g_xMainWnd.m_rcWindow.top+405, 75, 13, TRUE);
				ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);

				SetChrInfo(&m_stCreateChrInfo[0], _GENDER_MAN, _JOB_JUNSA, 0);
				SetMotion(0, _CHR_MT_CC);

				SetChrInfo(&m_stCreateChrInfo[1], _GENDER_WOMAN, _JOB_JUNSA, 0);
				SetMotion(1, _CHR_MT_CC);
			}
			break;
		}
		case _CHR_PROC_CREATEOUT:
		{
			if ( !m_xAvi.Draw(g_xMainWnd.GetBackBuffer()) )
			{		
//				m_xAvi.Release();
				m_bChrProcState = _CHR_PROC_SELECT;

				m_bBGMPlay	   = TRUE;
				m_bBGMPlayTime = 0;

				if ( m_nSelectedChr != _SELECTED_NONE )
				{
					SetMotion(m_nSelectedChr, _CHR_MT_SM);
				}
			}
			break;
		}
		case _CHR_PROC_START:
		{
			if ( !m_xAvi.Draw(g_xMainWnd.GetBackBuffer()) )
			{		
				SetNextProc();
			}
			break;
		}
	}
}


/******************************************************************************************************************
Character Select 부분의 메인루프.
*******************************************************************************************************************/
VOID CChrProcess::RenderSelect(INT nLoopTime)
{
	INT nCnt;

	// 1초후에 BGM Play.
	if ( m_bBGMPlay )
	{
		m_bBGMPlayTime += nLoopTime;

		if ( m_bBGMPlayTime > 1000 )
		{
			g_SoundManager.SndmngrPlayMp3(".\\Sound\\SelChr.mp3", TRUE);
			m_bBGMPlay     = FALSE;
			m_bBGMPlayTime = 0;
		}
	}

	// 배경.
	if ( m_xImageChr.NewSetIndex(_CHR_PROC_IMG_SELECT) )
	{
		g_xMainWnd.DrawWithImageForComp(0, 0, m_xImageChr.m_lpstNewCurrWilImageInfo->shWidth, m_xImageChr.m_lpstNewCurrWilImageInfo->shHeight,
										(WORD*)(m_xImageChr.m_pbCurrImage));
	}

	int	nSelectIdx;
	// 캐릭터.
	for ( nCnt=0 ; nCnt < _MAX_SHOW_CHAR; nCnt++ )
	{
/*
		if (m_bFrontSetofSelChar == FALSE)
			nSelectIdx = nCnt + 2;
		else
			nSelectIdx = nCnt;
*/
		nSelectIdx = 2*m_nPageNum + nCnt;

		if ( m_stSelectChrInfo[nSelectIdx].bSetted )
		{
			LPCHARINFO		pstChrInfo = &m_stSelectChrInfo[nSelectIdx];
			LPCHARSPRINFO	pstSprInfo = m_stSelectChrInfo[nSelectIdx].stCurrFrmInfo.pstCurrSprInfo;

			if ( pstSprInfo )
			{
				pstChrInfo->stCurrFrmInfo.wCurrDelay += nLoopTime;

				if ( pstChrInfo->stCurrFrmInfo.wCurrDelay > pstSprInfo->wDelay )
				{
					pstChrInfo->stCurrFrmInfo.wCurrDelay = 0;
					pstChrInfo->stCurrFrmInfo.wCurrFrm++;

					// 사운드 플레이.
					if ( pstChrInfo->stCurrFrmInfo.wCurrFrm ==  pstSprInfo->wFstFrm+1 )
					{
						if ( pstChrInfo->stCurrFrmInfo.wCurrMtn == _CHR_MT_SM )
						{
							SndObjPlay(0, 0, m_stSelectWav[pstChrInfo->bGender][pstChrInfo->bClass], 0);
						}
					}

					SetCharRect(nSelectIdx, pstChrInfo->stCurrFrmInfo.wCurrMtn);

					if ( pstChrInfo->stCurrFrmInfo.wCurrFrm > pstSprInfo->wEndFrm )
					{
						// 애니메이션이 끝난후 다른동작과 연결되는 경우가 있다.
						if ( pstChrInfo->stCurrFrmInfo.wCurrMtn == _CHR_MT_SM )
						{
							SetMotion(nSelectIdx, _CHR_MT_SS);
						}
						else if ( pstChrInfo->stCurrFrmInfo.wCurrMtn == _CHR_MT_R )
						{
							SetMotion(nSelectIdx, _CHR_MT_NS);
						}
						else
						{
							pstChrInfo->stCurrFrmInfo.wCurrFrm = pstSprInfo->wFstFrm;
						}
					}
				}

				INT nPosX, nPosY;

				// 그림자.
				if ( m_xImageChr.NewSetIndex(pstChrInfo->stCurrFrmInfo.wCurrFrm+20) )
				{
					nPosX = pstChrInfo->stCurrFrmInfo.nPosX+m_xImageChr.m_lpstNewCurrWilImageInfo->shPX;
					nPosY = pstChrInfo->stCurrFrmInfo.nPosY+m_xImageChr.m_lpstNewCurrWilImageInfo->shPY;
					g_xMainWnd.DrawWithABlendCompDataWithBackBuffer(nPosX, nPosY, 
																	m_xImageChr.m_lpstNewCurrWilImageInfo->shWidth, m_xImageChr.m_lpstNewCurrWilImageInfo->shHeight,
																	(WORD*)(m_xImageChr.m_pbCurrImage), 640, 480);
				}

				// 캐릭터.
				if ( m_xImageChr.NewSetIndex(pstChrInfo->stCurrFrmInfo.wCurrFrm) )
				{
					nPosX = pstChrInfo->stCurrFrmInfo.nPosX+m_xImageChr.m_lpstNewCurrWilImageInfo->shPX;
					nPosY = pstChrInfo->stCurrFrmInfo.nPosY+m_xImageChr.m_lpstNewCurrWilImageInfo->shPY;

					if ( pstChrInfo->stCurrFrmInfo.bBlend )
					{
						g_xMainWnd.DrawWithImageForComp(nPosX, nPosY, 
														m_xImageChr.m_lpstNewCurrWilImageInfo->shWidth, m_xImageChr.m_lpstNewCurrWilImageInfo->shHeight,
														(WORD*)(m_xImageChr.m_pbCurrImage));
					}
					else
					{
						g_xMainWnd.DrawWithImageForCompClipRgnColor(nPosX, nPosY, m_xImageChr.m_lpstNewCurrWilImageInfo->shWidth, m_xImageChr.m_lpstNewCurrWilImageInfo->shHeight,
																	(WORD*)(m_xImageChr.m_pbCurrImage), 640, 480, _STATE_GRAY, FALSE, FALSE);
					}
				}

				// 캐릭터 효과.
				if ( m_xImageChr.NewSetIndex(pstChrInfo->stCurrFrmInfo.wCurrFrm+40) )
				{
					nPosX = pstChrInfo->stCurrFrmInfo.nPosX;
					nPosY = pstChrInfo->stCurrFrmInfo.nPosY;
					DrawCharEffect(pstChrInfo->stCurrFrmInfo.wCurrFrm+40, nPosX, nPosY);
				}
			}
		}
	}

	for ( nCnt = 0; nCnt < _MAX_CHR_SELECT_BTN; nCnt++ )
	{
		if (m_bMoreTwoChar == FALSE)
		{
			if ( nCnt == _MAX_CHR_SELECT_BEFORE || nCnt == _MAX_CHR_SELECT_NEXT )
				continue;
/*			if (m_bFrontSetofSelChar == TRUE)
			{
				if (nCnt == _MAX_CHR_SELECT_NEXT)
				{
					m_xSelectBtn[nCnt].ShowGameBtn();
				}
			}
			else
			{
				if (nCnt == _MAX_CHR_SELECT_BEFORE)
				{
					m_xSelectBtn[nCnt].ShowGameBtn();
				}
			}
*/
		}


//		if ( nCnt != _MAX_CHR_SELECT_BEFORE && nCnt != _MAX_CHR_SELECT_NEXT )
			m_xSelectBtn[nCnt].ShowGameBtn();

		// 버튼이미지(클릭)가 없는관계로...
		RECT* prcBtn = &m_xSelectBtn[nCnt].m_rcBtn;
		if ( PtInRect(prcBtn, m_ptMousePos) )
		{
			if ( nCnt == _MAX_CHR_SELECT_BEFORE || nCnt == _MAX_CHR_SELECT_NEXT )
				continue;

			D3DVECTOR	 vecTrans((FLOAT)prcBtn->left, (FLOAT)prcBtn->top, 0);
			D3DVECTOR	 vecScale((FLOAT)prcBtn->right-prcBtn->left, (FLOAT)prcBtn->bottom-prcBtn->top, 1);

			D3DMATERIAL7 mtrl;
			D3DUtil_InitMaterial(mtrl, (FLOAT)150/255.0f, (FLOAT)100/255.0f, (FLOAT)50/255.0f);
			mtrl.diffuse.a = 50.0f/255.0f;
			DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

			g_xMainWnd.DrawWithGDI(prcBtn, NULL, RGB(200, 150, 100), 1);
		}
	}

	ShowSelectedChrInfo();
}


/******************************************************************************************************************
Character Create 부분의 메인루프.
*******************************************************************************************************************/
VOID CChrProcess::RenderCreate(INT nLoopTime)
{
	INT nCnt;

	// 1초후에 BGM Play.
	if ( m_bBGMPlay )
	{
		m_bBGMPlayTime += nLoopTime;

		if ( m_bBGMPlayTime > 1000 )
		{
			g_SoundManager.SndmngrPlayMp3(".\\Sound\\CreateChr.mp3", TRUE);
			m_bBGMPlay	   = FALSE;
			m_bBGMPlayTime = 0;
		}
	}

	// 배경.
	if ( m_xImageChr.NewSetIndex(_CHR_PROC_IMG_CREATE) )
	{
		g_xMainWnd.DrawWithImageForComp(0, 0, m_xImageChr.m_lpstNewCurrWilImageInfo->shWidth, m_xImageChr.m_lpstNewCurrWilImageInfo->shHeight,
										(WORD*)(m_xImageChr.m_pbCurrImage));
	}

	ShowCharExplain();

	// 캐릭터.
	for ( nCnt = 0; nCnt < _MAX_CHAR; nCnt++ )
	{
		if ( m_stCreateChrInfo[nCnt].bSetted )
		{
			LPCHARINFO		pstChrInfo = &m_stCreateChrInfo[nCnt];
			LPCHARSPRINFO	pstSprInfo = m_stCreateChrInfo[nCnt].stCurrFrmInfo.pstCurrSprInfo;

			if ( pstSprInfo )
			{
				pstChrInfo->stCurrFrmInfo.wCurrDelay += nLoopTime;

				if ( pstChrInfo->stCurrFrmInfo.wCurrDelay > pstSprInfo->wDelay )
				{
					if ( nCnt == m_nCreatedChr )
					{
						if ( pstChrInfo->bClass != _JOB_GUNGSA )
						{
							if ( pstChrInfo->stCurrFrmInfo.wCurrFrm == pstSprInfo->wFstFrm )
							{
								SndObjPlay(0, 0, m_stCreateWav[pstChrInfo->bGender][pstChrInfo->bClass], 0);
							}
						}
					}

					pstChrInfo->stCurrFrmInfo.wCurrDelay = 0;
					pstChrInfo->stCurrFrmInfo.wCurrFrm++;

					SetCharRect(nCnt, pstChrInfo->stCurrFrmInfo.wCurrMtn);

					if ( pstChrInfo->stCurrFrmInfo.wCurrFrm > pstSprInfo->wEndFrm )
					{
						pstChrInfo->stCurrFrmInfo.wCurrFrm = pstSprInfo->wFstFrm;
					}
				}

				INT nPosX, nPosY;

				// 그림자.
				if ( pstChrInfo->bClass == _JOB_GUNGSA )
				{
					if ( pstChrInfo->bGender == 0 )
					{
						if ( m_xImageChr.NewSetIndex(2032) )
						{
							g_xMainWnd.DrawWithABlendCompDataWithBackBuffer(50, 379, 
																			m_xImageChr.m_lpstNewCurrWilImageInfo->shWidth, m_xImageChr.m_lpstNewCurrWilImageInfo->shHeight,
																			(WORD*)(m_xImageChr.m_pbCurrImage), 640, 480);
						}
					}
					else
					{
						if ( m_xImageChr.NewSetIndex(2042) )
						{
							g_xMainWnd.DrawWithABlendCompDataWithBackBuffer(350, 379, 
																			m_xImageChr.m_lpstNewCurrWilImageInfo->shWidth, m_xImageChr.m_lpstNewCurrWilImageInfo->shHeight,
																			(WORD*)(m_xImageChr.m_pbCurrImage), 640, 480);
						}
					}
				}
				else if ( m_xImageChr.NewSetIndex(pstChrInfo->stCurrFrmInfo.wCurrFrm+20) )
				{
					nPosX = pstChrInfo->stCurrFrmInfo.nPosX+m_xImageChr.m_lpstNewCurrWilImageInfo->shPX;
					nPosY = pstChrInfo->stCurrFrmInfo.nPosY+m_xImageChr.m_lpstNewCurrWilImageInfo->shPY;
					g_xMainWnd.DrawWithABlendCompDataWithBackBuffer(nPosX, nPosY, 
																	m_xImageChr.m_lpstNewCurrWilImageInfo->shWidth, m_xImageChr.m_lpstNewCurrWilImageInfo->shHeight,
																	(WORD*)(m_xImageChr.m_pbCurrImage), 640, 480);
				}

				//캐릭터.
				if ( m_nCreatedChr == nCnt )
				{
					if ( m_xImageChr.NewSetIndex(pstChrInfo->stCurrFrmInfo.wCurrFrm) )
					{
						nPosX = pstChrInfo->stCurrFrmInfo.nPosX+m_xImageChr.m_lpstNewCurrWilImageInfo->shPX;
						nPosY = pstChrInfo->stCurrFrmInfo.nPosY+m_xImageChr.m_lpstNewCurrWilImageInfo->shPY;
						g_xMainWnd.DrawWithImageForComp(nPosX, nPosY, 
														m_xImageChr.m_lpstNewCurrWilImageInfo->shWidth, m_xImageChr.m_lpstNewCurrWilImageInfo->shHeight,
														(WORD*)(m_xImageChr.m_pbCurrImage));
					}

					if ( pstChrInfo->stCurrFrmInfo.wCurrFrm == 2030 )
					{
						nPosX = pstChrInfo->stCurrFrmInfo.nPosX+m_xImageChr.m_lpstNewCurrWilImageInfo->shPX;
						nPosY = pstChrInfo->stCurrFrmInfo.nPosY+m_xImageChr.m_lpstNewCurrWilImageInfo->shPY;
						if ( m_xImageChr.NewSetIndex(4) )
						DrawCharEffect(4, nPosX + 11 , nPosY - 70);
					}
					else if ( pstChrInfo->stCurrFrmInfo.wCurrFrm == 2040  )
					{
						nPosX = pstChrInfo->stCurrFrmInfo.nPosX+m_xImageChr.m_lpstNewCurrWilImageInfo->shPX;
						nPosY = pstChrInfo->stCurrFrmInfo.nPosY+m_xImageChr.m_lpstNewCurrWilImageInfo->shPY;
						DrawCharEffect(pstChrInfo->stCurrFrmInfo.wCurrFrm+1, nPosX - 15, nPosY - 76);
					}

				}
				else
				{
					if ( m_xImageChr.NewSetIndex(pstChrInfo->stCurrFrmInfo.pstCurrSprInfo->wFstFrm) )
					{
						nPosX = pstChrInfo->stCurrFrmInfo.nPosX+m_xImageChr.m_lpstNewCurrWilImageInfo->shPX;
						nPosY = pstChrInfo->stCurrFrmInfo.nPosY+m_xImageChr.m_lpstNewCurrWilImageInfo->shPY;
						g_xMainWnd.DrawWithImageForCompClipRgnColor(nPosX, nPosY, m_xImageChr.m_lpstNewCurrWilImageInfo->shWidth, m_xImageChr.m_lpstNewCurrWilImageInfo->shHeight,
																	(WORD*)(m_xImageChr.m_pbCurrImage), 640, 480, _STATE_GRAY, FALSE, FALSE);
					}
				}

				// 캐릭터 효과.
				if ( m_nCreatedChr == nCnt )
				{
					if ( m_xImageChr.NewSetIndex(pstChrInfo->stCurrFrmInfo.wCurrFrm+40) )
					{
						nPosX = pstChrInfo->stCurrFrmInfo.nPosX;
						nPosY = pstChrInfo->stCurrFrmInfo.nPosY;
						DrawCharEffect(pstChrInfo->stCurrFrmInfo.wCurrFrm+40, nPosX, nPosY);
					}
				}
			}
		}
	}

	// 돌그림자.
	if ( m_xImageChr.NewSetIndex(_CHR_PROC_IMG_CREATE_STONE_S) )
	{
		g_xMainWnd.DrawWithABlendCompDataWithBackBuffer(201, 434, 
													    m_xImageChr.m_lpstNewCurrWilImageInfo->shWidth, m_xImageChr.m_lpstNewCurrWilImageInfo->shHeight,
														(WORD*)(m_xImageChr.m_pbCurrImage), 640, 480);
	}
	// 돌.
	if ( m_xImageChr.NewSetIndex(_CHR_PROC_IMG_CREATE_STONE) )
	{
		g_xMainWnd.DrawWithImageForComp(247, 384, m_xImageChr.m_lpstNewCurrWilImageInfo->shWidth, m_xImageChr.m_lpstNewCurrWilImageInfo->shHeight,
										(WORD*)(m_xImageChr.m_pbCurrImage));
	}

	for ( nCnt = 0; nCnt < _CHR_CHR_CREATE_BTN; nCnt++ )
	{
		m_xCreateBtn[nCnt].ShowGameBtn();
		m_xCreateBtn[_CHR_CHR_CREATE_WARIOR].ChangeRect(260, 420);
		m_xCreateBtn[_CHR_CHR_CREATE_MAGICIAN].ChangeRect(296, 420);
		m_xCreateBtn[_CHR_CHR_CREATE_CLERIC].ChangeRect(333, 420);
		m_xCreateBtn[_CHR_CHR_CREATE_ARCHER].ChangeRect(369, 420);
	}

	// Tool Tip.
	RECT	rcTemp;

	for ( nCnt = 0; nCnt < _CHR_CHR_CREATE_BTN; nCnt++ )
	{
		RECT* prcBtn = &m_xCreateBtn[nCnt].m_rcBtn;
		if ( PtInRect(prcBtn, m_ptMousePos) )
		{
			CHAR	szTemp[MAX_PATH];
			POINT	ptShow;

			switch ( nCnt )
			{
			case 0:
				strcpy(szTemp, g_xMsg.GetMsg(201));
				ptShow.x = 289;
				ptShow.y = 438;
				break;
			case 1:
				strcpy(szTemp, g_xMsg.GetMsg(202));
				ptShow.x = 332;
				ptShow.y = 438;
				break;
			case 2:
				strcpy(szTemp, g_xMsg.GetMsg(203));
				ptShow.x = 376;
				ptShow.y = 438;
				break;
			case 3:
				strcpy(szTemp, g_xMsg.GetMsg(204));
				ptShow.x = 469;
				ptShow.y = 458;
				break;
			case 4:
				strcpy(szTemp, g_xMsg.GetMsg(205));
				ptShow.x = 510;
				ptShow.y = 458;
				break;
			}

			if ( nCnt == 5 )
				break;

			SetRect(&rcTemp, ptShow.x+10, ptShow.y+2, ptShow.x+10+strlen(szTemp)*6, ptShow.y+17);

			D3DVECTOR	 vecTrans((FLOAT)rcTemp.left, (FLOAT)rcTemp.top, 0);
			D3DVECTOR	 vecScale((FLOAT)rcTemp.right-rcTemp.left, (FLOAT)rcTemp.bottom-rcTemp.top, 1);

			D3DMATERIAL7 mtrl;
			D3DUtil_InitMaterial(mtrl, (FLOAT)125/255.0f, (FLOAT)125/255.0f, (FLOAT)75/255.0f);
			mtrl.diffuse.a = 50.0f/255.0f;
			DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

			g_xMainWnd.DrawWithGDI(&rcTemp, NULL, RGB(180, 180, 120), 1);

			g_xMainWnd.PutsHan(NULL,rcTemp.left+1, rcTemp.top+1, RGB( 25,  25,  25),RGB(0, 0, 0), szTemp);
			g_xMainWnd.PutsHan(NULL,rcTemp.left+3, rcTemp.top+1, RGB( 25,  25,  25),RGB(0, 0, 0), szTemp);
			g_xMainWnd.PutsHan(NULL,rcTemp.left+1, rcTemp.top+3, RGB( 25,  25,  25),RGB(0, 0, 0), szTemp);
			g_xMainWnd.PutsHan(NULL,rcTemp.left+3, rcTemp.top+3, RGB( 25,  25,  25),RGB(0, 0, 0), szTemp);
			g_xMainWnd.PutsHan(NULL,rcTemp.left+2, rcTemp.top+2, RGB(255, 255, 180),RGB(0, 0, 0), szTemp);
		}
	}

	SetRect(&rcTemp, 287, 404, 364, 419);
	g_xMainWnd.DrawWithGDI(&rcTemp, NULL, RGB(120, 90, 60), 1);
}










//-----------------------------------------------------------------------------------------------------------------
// Character Select부분.
//-----------------------------------------------------------------------------------------------------------------
/******************************************************************************************************************
선택된 Character의 정보를 출력.
*******************************************************************************************************************/
VOID CChrProcess::ShowSelectedChrInfo()
{
	if ( m_nSelectedChr != _SELECTED_NONE && m_nSelectedChr < _MAX_CHAR )
	{
		INT nHeight = m_rcSelectChrInfo.bottom-m_rcSelectChrInfo.top;
		BOOL bOtherServer = FALSE;
		
		if ( strcmp(g_szServerName, m_stSelShowInfo.pszServerName) != 0  )
		{
			bOtherServer = TRUE;
			nHeight += 20;
		}
		D3DVECTOR vecTrans((FLOAT)m_rcSelectChrInfo.left, (FLOAT)m_rcSelectChrInfo.top, 0);
		D3DVECTOR vecScale((FLOAT)m_rcSelectChrInfo.right-m_rcSelectChrInfo.left, (FLOAT)nHeight, 1);

		D3DMATERIAL7 mtrl;
		D3DUtil_InitMaterial(mtrl, (FLOAT)50/255.0f, (FLOAT)50/255.0f, (FLOAT)25/255.0f);
		mtrl.diffuse.a = 100.0f/255.0f;
		DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

		if ( bOtherServer )
		{
			RECT rcTemp = {m_rcSelectChrInfo.left, m_rcSelectChrInfo.top, m_rcSelectChrInfo.right, m_rcSelectChrInfo.bottom + 20};
			g_xMainWnd.DrawWithGDI(&rcTemp, NULL, RGB(100, 100, 80), 1);
		}
		else
			g_xMainWnd.DrawWithGDI(&m_rcSelectChrInfo, NULL, RGB(100, 100, 80), 1);

		g_xMainWnd.PutsHan(NULL, m_rcSelectChrInfo.left+10, m_rcSelectChrInfo.top+10, RGB(255, 200, 150), RGB(0, 0, 0), m_stSelShowInfo.pszName , g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));
		g_xMainWnd.PutsHan(NULL, m_rcSelectChrInfo.left+10, m_rcSelectChrInfo.top+30, RGB(150, 240, 150), RGB(0, 0, 0), m_stSelShowInfo.pszLevel, g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));
		g_xMainWnd.PutsHan(NULL, m_rcSelectChrInfo.left+10, m_rcSelectChrInfo.top+50, RGB(255, 255, 175), RGB(0, 0, 0), m_stSelShowInfo.pszJob  , g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));

		if ( bOtherServer )
		{
			CHAR szTemp[MAX_PATH];
			sprintf(szTemp, "서버    %s", m_stSelShowInfo.pszServerName);
			g_xMainWnd.PutsHan(NULL, m_rcSelectChrInfo.left+10, m_rcSelectChrInfo.top+70, RGB(255, 255, 175), RGB(0, 0, 0), szTemp, g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD));
		}
	}
}


/******************************************************************************************************************
선택된 Character의 정보를 입력.
*******************************************************************************************************************/
VOID CChrProcess::SetSelectChrShowInfo()
{
	SIZE	sizeLen1;
	SIZE	sizeLen2;
	SIZE	sizeLen3;
	POINT	ptPos = {79, 108};
	INT		nHeight = 0;
	
	if ( m_nSelectedChr != _SELECTED_NONE && m_nSelectedChr < _MAX_CHAR )
	{
		sprintf(m_stSelShowInfo.pszServerName, "%s", m_stSelectChrInfo[m_nSelectedChr].pszServerName);
		
		sprintf(m_stSelShowInfo.pszName, "%s   %s", g_xMsg.GetMsg(206), m_stSelectChrInfo[m_nSelectedChr].pszChrName);
		sizeLen1 = g_xMainWnd.GetStrLength(NULL, g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD), m_stSelShowInfo.pszName);

		if ( m_stSelectChrInfo[m_nSelectedChr].bUpgradeLevel == 1 )
			SetRect(&m_rcSelectChrInfo, ptPos.x, ptPos.y, ptPos.x+sizeLen1.cx+20, ptPos.y+20*4+10);
		else
			SetRect(&m_rcSelectChrInfo, ptPos.x, ptPos.y, ptPos.x+sizeLen1.cx+20, ptPos.y+20*3+10);

		sprintf(m_stSelShowInfo.pszLevel, "%s   %d", g_xMsg.GetMsg(207), m_stSelectChrInfo[m_nSelectedChr].bLevel);
		
		switch ( m_stSelectChrInfo[m_nSelectedChr].bClass )
		{
			case _JOB_JUNSA:
				sprintf(m_stSelShowInfo.pszJob, g_xMsg.GetMsg(208));
				break;
			case _JOB_SULSA:
				sprintf(m_stSelShowInfo.pszJob, g_xMsg.GetMsg(209));
				break;
			case _JOB_DOSA:
				sprintf(m_stSelShowInfo.pszJob, g_xMsg.GetMsg(210));
				break;
		}

		if ( m_stSelectChrInfo[m_nSelectedChr].bUpgradeLevel == 1 )
		{
			sprintf(m_stSelShowInfo.pszHighLevel, g_xMsg.GetMsg(238));
			nHeight = ptPos.y+20*4+10;
		}
		else
		{
			nHeight = ptPos.y+20*3+10;
		}

		sizeLen2 = g_xMainWnd.GetStrLength(NULL, g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD), m_stSelShowInfo.pszJob);
		sizeLen3 = g_xMainWnd.GetStrLength(NULL, g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_BOLD), m_stSelShowInfo.pszServerName);
//		sizeLen3.cx += 45;

		if ( sizeLen2.cx > sizeLen1.cx )
		{
			SetRect(&m_rcSelectChrInfo, ptPos.x, ptPos.y, ptPos.x+sizeLen2.cx+20, nHeight);
		}

		if ( sizeLen3.cx > sizeLen1.cx )
		{
			SetRect(&m_rcSelectChrInfo, ptPos.x, ptPos.y, ptPos.x+sizeLen3.cx+20, nHeight);			
		}
	}
}


/******************************************************************************************************************
CHARINFO 구조체의 정보를 대입.
*******************************************************************************************************************/
VOID CChrProcess::SetChrInfo(LPCHARINFO pstChrInfo, BYTE bGender, BYTE bJob, BYTE bLevel, CHAR* pszName)
{
	pstChrInfo->bSetted = TRUE;
	pstChrInfo->bGender = bGender;
	pstChrInfo->bClass  = bJob;
	pstChrInfo->bLevel  = bLevel;

	POINT ptPos = GetChrCreatePos(bGender, bJob);
	pstChrInfo->stCurrFrmInfo.nPosX = ptPos.x;
	pstChrInfo->stCurrFrmInfo.nPosY = ptPos.y;

	ZeroMemory(pstChrInfo->pszChrName, 25);

	if ( pszName )
	{
		strcpy(pstChrInfo->pszChrName, pszName);
	}
}









//-----------------------------------------------------------------------------------------------------------------
// Character Create부분.
//-----------------------------------------------------------------------------------------------------------------
/******************************************************************************************************************
선택된 직업에 대한 설명정보를 얻어온다.
*******************************************************************************************************************/
BOOL CChrProcess::SetCharExplain(BYTE bGender, BYTE bJob)
{
	if ( (bGender >= 0 && bGender < 2) && (bJob >= 0 && bJob < 4) )
	{
		INT nCnt;
		CHAR pszJobExplain[1024];
		CHAR pszJobExplainEx[2048];

		ZeroMemory(pszJobExplain, 1024);
		ZeroMemory(pszJobExplainEx, 2048);
		ZeroMemory(&m_pszChrExplain, 15*MAX_PATH);

		switch ( bGender )
		{
			case _GENDER_MAN:
			{
				strcpy(m_pszChrExplain[0], g_xMsg.GetMsg(211));
				break;
			}
			case _GENDER_WOMAN:
			{
				strcpy(m_pszChrExplain[0], g_xMsg.GetMsg(212));
				break;
			}			
		}

		switch ( bJob )
		{
			case _JOB_JUNSA:
			{
				strcat(m_pszChrExplain[0], g_xMsg.GetMsg(213));
				g_xMainWnd.StringDivide(_CHR_EXPLAIN_WIDTH, m_nDividedExplain, g_xMsg.GetMsg(216+bJob), pszJobExplainEx);
				break;
			}
			case _JOB_SULSA:
			{
				strcat(m_pszChrExplain[0], g_xMsg.GetMsg(214));
				g_xMainWnd.StringDivide(_CHR_EXPLAIN_WIDTH, m_nDividedExplain, g_xMsg.GetMsg(216+bJob), pszJobExplainEx);
				break;
			}
			case _JOB_DOSA:
			{
				strcat(m_pszChrExplain[0], g_xMsg.GetMsg(215));
				g_xMainWnd.StringDivide(_CHR_EXPLAIN_WIDTH, m_nDividedExplain, g_xMsg.GetMsg(216+bJob), pszJobExplainEx);
				break;
			}
			case _JOB_GUNGSA:
			{
				strcpy(m_pszChrExplain[0], g_xMsg.GetMsg(237));
				g_xMainWnd.StringDivide(_CHR_EXPLAIN_WIDTH, m_nDividedExplain, g_xMsg.GetMsg(236), pszJobExplainEx);
				break;
			}
		}

		

		// 첫줄까지 더해준다.
		m_nDividedExplain += 1;
		
		sscanf(pszJobExplainEx, "%[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c", 
			   m_pszChrExplain[1], m_pszChrExplain[ 2], m_pszChrExplain[ 3], m_pszChrExplain[ 4], m_pszChrExplain[ 5], m_pszChrExplain[ 6], m_pszChrExplain[ 7], m_pszChrExplain[ 8], 
			   m_pszChrExplain[9], m_pszChrExplain[10], m_pszChrExplain[11], m_pszChrExplain[12], m_pszChrExplain[13], m_pszChrExplain[14]);

		return TRUE;
	}
	return FALSE;
}


/******************************************************************************************************************
선택된 직업에 대한 설명정보를 화면상에 출력.
*******************************************************************************************************************/
VOID CChrProcess::ShowCharExplain()
{
	if ( m_nCreatedChr != _SELECTED_NONE && m_nCreatedChr < _MAX_CHAR )
	{
		RECT rcShow = {100, 15, 100+_CHR_EXPLAIN_WIDTH+20, 15+(m_nDividedExplain+1)*18+20};	

		D3DVECTOR vecTrans((FLOAT)rcShow.left, (FLOAT)rcShow.top, 0);
		D3DVECTOR vecScale((FLOAT)rcShow.right-rcShow.left, (FLOAT)rcShow.bottom-rcShow.top, 1);

		D3DMATERIAL7 mtrl;
		D3DUtil_InitMaterial(mtrl, (FLOAT)50/255.0f, (FLOAT)50/255.0f, (FLOAT)50/255.0f);
		mtrl.diffuse.a = 50.0f/255.0f;
		DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
		g_xMainWnd.DrawWithGDI(&rcShow, NULL, RGB(150, 150, 150), 1);

		switch ( m_stCreateChrInfo[m_nSelectedChr].bClass )
		{
			case _JOB_JUNSA:
				g_xMainWnd.PutsHan(NULL, rcShow.left + 10, rcShow.top + 10, RGB(250, 200, 150), RGB(0,0,0), m_pszChrExplain[0], g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 10, 0, FW_BOLD));
				break;
			case _JOB_SULSA:
				g_xMainWnd.PutsHan(NULL, rcShow.left + 10, rcShow.top + 10, RGB(250, 170, 170), RGB(0,0,0), m_pszChrExplain[0], g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 10, 0, FW_BOLD));
				break;
			case _JOB_DOSA:
				g_xMainWnd.PutsHan(NULL, rcShow.left + 10, rcShow.top + 10, RGB(150, 220, 150), RGB(0,0,0), m_pszChrExplain[0], g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 10, 0, FW_BOLD));
				break;
			case _JOB_GUNGSA:
				g_xMainWnd.PutsHan(NULL, rcShow.left + 10, rcShow.top + 10, RGB(150, 220, 250), RGB(0,0,0), m_pszChrExplain[0], g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 10, 0, FW_BOLD));
				break;
		}
		
		for ( INT nCnt = 1; nCnt < m_nDividedExplain; nCnt++ )
		{
			g_xMainWnd.PutsHan(NULL, rcShow.left+10, rcShow.top+35+18*(nCnt-1), RGB(250, 250, 255), RGB(0, 0, 0), m_pszChrExplain[nCnt]);
		}
	}
}


/******************************************************************************************************************
캐릭터의 화면상의 위치를 결정.(이미지정보의 중심점이 서로 일치하지 않기 때문.)
*******************************************************************************************************************/
POINT CChrProcess::GetChrCreatePos(BYTE bGender, BYTE bJob)
{
	POINT ptRet		  = { 110, 100 };
	POINT ptPos[2][4] = { { {110, 110}, {110, 120}, {110, 120}, {110, 120} }, { {400, 160}, {420, 115}, {425, 118}, {420, 118} } };

	if ( (bGender >= 0 && bGender < 2) && (bJob >= 0 && bJob < 4) )
	{
		ptRet = ptPos[bGender][bJob];
	}

	return ptRet;
}


/******************************************************************************************************************
생성시킬 Character의 이름검사(영문).
*******************************************************************************************************************/
BOOL CChrProcess::IsAlphabet(CHAR cChar)
{
	if ( ( (cChar >= 'a') && (cChar <= 'z') ) || ( (cChar >= 'A') && (cChar <= 'Z') ) )
	{
		return TRUE;
	}

	return FALSE;
}


/******************************************************************************************************************
생성시킬 Character의 이름검사(숫자).
*******************************************************************************************************************/
BOOL CChrProcess::IsNumeric(CHAR cChar)
{
	INT nNum = cChar-'0';

	if ( nNum >= 0 && nNum <= 9 )
	{
		return TRUE;
	}

	return FALSE;
}


/******************************************************************************************************************
생성시킬 Character의 이름검사(한글).
*******************************************************************************************************************/
BOOL CChrProcess::IsHangul(CHAR* pszChar)
{
	CHAR	cChar;
	CHAR	cNextChar;
	WORD	wchDBCS;

	cChar	  = *pszChar;
	cNextChar = *(pszChar+1);

	if ( cChar & 0x800 )
	{
		if ( (wchDBCS = (cChar << 8) + cNextChar) > 0xCAA0 )
		{
			// 한자.
			return FALSE;
		}
		else
		{
			if ( (wchDBCS >= 0xafa1 ) && (wchDBCS <= 0xc7ff) )
			{
				return TRUE;	// Hangul	단 KS완성형에 한함.
			}
			else
			{
				return FALSE;
			}
		}
	}

	return FALSE;
}


/******************************************************************************************************************
생성시킬 Character의 이름이 타당한지의 여부를 판별한다.
*******************************************************************************************************************/
BOOL CChrProcess::CreateNameValidate(CHAR* pszName)
{
	if ( pszName != NULL )
	{
		CHAR* pszTemp = pszName;
		// 필터링.
		while ( *pszName )
		{
			if ( (*pszName == ' ') ||
				 (*pszName == '/') || (*pszName == '@') || (*pszName == '?') ||
				 (*pszName == '\'')|| (*pszName == '"') || (*pszName == '\\')||
				 (*pszName == '.') || (*pszName == ',') || (*pszName == ':') ||
				 (*pszName == ';') || (*pszName == '`') || (*pszName == '~') ||
				 (*pszName == '!') || (*pszName == '#') || (*pszName == '$') ||
				 (*pszName == '%') || (*pszName == '^') || (*pszName == '&') ||
				 (*pszName == '*') || (*pszName == '(') || (*pszName == ')') ||
				 (*pszName == '-') || (*pszName == '_') || (*pszName == '+') ||
				 (*pszName == '=') || (*pszName == '|') || (*pszName == '[') ||
				 (*pszName == '{') || (*pszName == ']') || (*pszName == '}') )

			{
				return FALSE;
			}

			if ( !IsAlphabet(*pszName) )	
			{
				if ( !IsNumeric(*pszName) )
				{
					if ( !IsHangul(pszName) )
					{
						return	FALSE;
					}
					else
					{
						// 한글일경우 2바이트 단위로 계산된다.
						pszName++;
					}
				}
			}

			pszName++;
		}

		return TRUE;
	}

	return FALSE;
}









//-----------------------------------------------------------------------------------------------------------------
// Character 정보 관련부분.
//-----------------------------------------------------------------------------------------------------------------
/******************************************************************************************************************
캐릭터의 선택영역을 설정한다.(마우스 클릭등으로 선택된 캐릭터을 얻어올 수 있게 하기 위해)
*******************************************************************************************************************/
VOID CChrProcess::SetCharRect(INT nNum, BYTE bMtn)
{
	if ( nNum > _MAX_CHAR || bMtn >= _CHR_MAX_MT)
	{
		return;
	}

	LPCHARINFO pstChrInfo = NULL;

	if ( m_bChrProcState == _CHR_PROC_SELECT )
	{
		pstChrInfo = &m_stSelectChrInfo[nNum];
	}
	else if ( m_bChrProcState == _CHR_PROC_CREATE )
	{
		pstChrInfo = &m_stCreateChrInfo[nNum];
	}

	if ( pstChrInfo && pstChrInfo->bSetted )
	{
		pstChrInfo->stCurrFrmInfo.pstCurrSprInfo = GetCharSprInfo(pstChrInfo->bGender, pstChrInfo->bClass, bMtn);

		if ( pstChrInfo->stCurrFrmInfo.pstCurrSprInfo )
		{			
			//캐릭터.
			if ( m_xImageChr.NewSetIndex(pstChrInfo->stCurrFrmInfo.wCurrFrm) )
			{
				INT nPosX = pstChrInfo->stCurrFrmInfo.nPosX+m_xImageChr.m_lpstNewCurrWilImageInfo->shPX;
				INT nPosY = pstChrInfo->stCurrFrmInfo.nPosY+m_xImageChr.m_lpstNewCurrWilImageInfo->shPY;

				SetRect(&pstChrInfo->stCurrFrmInfo.rcChrRgn, nPosX, nPosY, 
						nPosX + m_xImageChr.m_lpstNewCurrWilImageInfo->shWidth, 
						nPosY + m_xImageChr.m_lpstNewCurrWilImageInfo->shHeight);
			}
		}
	}
}


/******************************************************************************************************************
캐릭터의 현재 동작에 대한 정보를 입력.
*******************************************************************************************************************/
VOID CChrProcess::SetMotion(INT nNum, BYTE bMtn)
{
	if ( nNum > _MAX_CHAR || bMtn >= _CHR_MAX_MT)
	{
		return;
	}

	LPCHARINFO pstChrInfo = NULL;

	if ( m_bChrProcState == _CHR_PROC_SELECT || m_bChrProcState == _CHR_PROC_CREATEOUT )
	{
		pstChrInfo = &m_stSelectChrInfo[nNum];
	}
	else if ( m_bChrProcState == _CHR_PROC_CREATE )
	{
		pstChrInfo = &m_stCreateChrInfo[nNum];
	}

	if ( pstChrInfo && pstChrInfo->bSetted )
	{
		pstChrInfo->stCurrFrmInfo.pstCurrSprInfo = GetCharSprInfo(pstChrInfo->bGender, pstChrInfo->bClass, bMtn);

		if ( pstChrInfo->stCurrFrmInfo.pstCurrSprInfo )
		{
			pstChrInfo->stCurrFrmInfo.wCurrMtn   = bMtn;
			pstChrInfo->stCurrFrmInfo.wCurrFrm   = pstChrInfo->stCurrFrmInfo.pstCurrSprInfo->wFstFrm;
			pstChrInfo->stCurrFrmInfo.wCurrDelay = 0;

			if ( pstChrInfo->stCurrFrmInfo.wCurrMtn == _CHR_MT_NS )
			{
				pstChrInfo->stCurrFrmInfo.bBlend = 0;
			}
			else
			{
				pstChrInfo->stCurrFrmInfo.bBlend = 255;
			}
		}
	}
}


/******************************************************************************************************************
CHARSPRINFO 구조체의 정보대입함수.
*******************************************************************************************************************/
VOID CChrProcess::SetCharSprInfo(LPCHARSPRINFO pstChrSpr, WORD wFstFrm, WORD wEndFrm, WORD wDelay)
{
	pstChrSpr->wFstFrm = wFstFrm;
	pstChrSpr->wEndFrm = wEndFrm;
	pstChrSpr->wDelay  = wDelay;
}


/******************************************************************************************************************
캐릭터의 프레임정보 입력.
*******************************************************************************************************************/
VOID CChrProcess::SetChrSelSprite()
{
	// 프레임의 구성.

	// 남자전사.
	SetCharSprInfo(&m_stChrSprInfo[0],  200,  210, 120);	// _CHR_MT_NS (Normal Stand ) 선택 안될시의 유휴.
	SetCharSprInfo(&m_stChrSprInfo[1],  260,  279, 120);	// _CHR_MT_SM (Select Motion) 선택 시의 동작.
	SetCharSprInfo(&m_stChrSprInfo[2],  320,  331, 120);	// _CHR_MT_SS (Select Stand ) 선택 후의 유휴.
	SetCharSprInfo(&m_stChrSprInfo[3],  380,  387, 120);	// _CHR_MT_R  (Return       ) 선택 안될때로 돌아가기.
	SetCharSprInfo(&m_stChrSprInfo[4],  440,  457, 120);	// _CHR_MT_CC (Char Create  ) 캐릭 생성시의 유휴.

	// 여자전사.
	SetCharSprInfo(&m_stChrSprInfo[5],  500,  510, 120);
	SetCharSprInfo(&m_stChrSprInfo[6],  560,  570, 120);
	SetCharSprInfo(&m_stChrSprInfo[7],  620,  630, 120);
	SetCharSprInfo(&m_stChrSprInfo[8],  680,  691, 120);
	SetCharSprInfo(&m_stChrSprInfo[9],  740,  755, 120);

	// 남자술사.
	SetCharSprInfo(&m_stChrSprInfo[10],  800,  810, 120);
	SetCharSprInfo(&m_stChrSprInfo[11],  860,  871, 120);
	SetCharSprInfo(&m_stChrSprInfo[12],  920,  930, 120);
	SetCharSprInfo(&m_stChrSprInfo[13],  980,  990, 120);
	SetCharSprInfo(&m_stChrSprInfo[14], 1040, 1054, 120);

	// 여자술사.
	SetCharSprInfo(&m_stChrSprInfo[15], 1100, 1110, 120);
	SetCharSprInfo(&m_stChrSprInfo[16], 1160, 1177, 120);
	SetCharSprInfo(&m_stChrSprInfo[17], 1220, 1230, 120);
	SetCharSprInfo(&m_stChrSprInfo[18], 1280, 1288, 120);
	SetCharSprInfo(&m_stChrSprInfo[19], 1340, 1356, 120);

	// 남자도사.
	SetCharSprInfo(&m_stChrSprInfo[20], 1400, 1410, 120);
	SetCharSprInfo(&m_stChrSprInfo[21], 1460, 1476, 120);
	SetCharSprInfo(&m_stChrSprInfo[22], 1520, 1539, 120);
	SetCharSprInfo(&m_stChrSprInfo[23], 1580, 1591, 120);
	SetCharSprInfo(&m_stChrSprInfo[24], 1640, 1656, 120);

	// 여자도사.
	SetCharSprInfo(&m_stChrSprInfo[25], 1700, 1710, 120);
	SetCharSprInfo(&m_stChrSprInfo[26], 1760, 1776, 120);
	SetCharSprInfo(&m_stChrSprInfo[27], 1820, 1830, 120);
	SetCharSprInfo(&m_stChrSprInfo[28], 1880, 1889, 120);
	SetCharSprInfo(&m_stChrSprInfo[29], 1940, 1954, 120);

	// 남자궁사.
	SetCharSprInfo(&m_stChrSprInfo[30],  0, 0, 0);	// _CHR_MT_NS (Normal Stand ) 선택 안될시의 유휴.
	SetCharSprInfo(&m_stChrSprInfo[31],  0, 0, 0);	// _CHR_MT_SM (Select Motion) 선택 시의 동작.
	SetCharSprInfo(&m_stChrSprInfo[32],  0, 0, 0);	// _CHR_MT_SS (Select Stand ) 선택 후의 유휴.
	SetCharSprInfo(&m_stChrSprInfo[33],  0, 0, 0);	// _CHR_MT_R  (Return       ) 선택 안될때로 돌아가기.
	SetCharSprInfo(&m_stChrSprInfo[34],  2030,  2030, 120);	// _CHR_MT_CC (Char Create  ) 캐릭 생성시의 유휴.

	// 여자궁사.
	SetCharSprInfo(&m_stChrSprInfo[35],  0, 0, 0);
	SetCharSprInfo(&m_stChrSprInfo[36],  0, 0, 0);
	SetCharSprInfo(&m_stChrSprInfo[37],  0, 0, 0);
	SetCharSprInfo(&m_stChrSprInfo[38],  0, 0, 0);
	SetCharSprInfo(&m_stChrSprInfo[39],  2040,  2040, 120);
}


/******************************************************************************************************************
성별, 직업, 동작으로 캐릭터의 프레임정보를 얻어온다.
*******************************************************************************************************************/
LPCHARSPRINFO CChrProcess::GetCharSprInfo(BYTE bGender, BYTE bJob, BYTE bMtn)
{
	INT nSprArray = bJob*10 + bGender*5 + bMtn;

	if ( nSprArray >= 0 && nSprArray < _MAX_SPR_KIND )
	{
		return 	(&m_stChrSprInfo[nSprArray]);
	}

	return NULL;
}










//-----------------------------------------------------------------------------------------------------------------
// 패킷관련 함수정의.
//-----------------------------------------------------------------------------------------------------------------
/******************************************************************************************************************
로긴서버에 접속성공.
*******************************************************************************************************************/
VOID CChrProcess::OnConnectToServer()
{
	g_xClientSocket.OnQueryChar();
}


/******************************************************************************************************************
dll Error Msg 파일로부터 에러문장을 얻어온다.
*******************************************************************************************************************/
/*VOID CChrProcess::GetErrorMsg(INT nMsg, CHAR* pszMsg)
{
	HINSTANCE hLib;
	hLib = LoadLibrary(_LOGINMSG);

	if ( hLib )
	{
		LoadString(hLib, nMsg, pszMsg, MAX_PATH);
		FreeLibrary(hLib);
	}
}*/


/******************************************************************************************************************
패킷을 자른다.
*******************************************************************************************************************/
CHAR* CChrProcess::OnMessageReceive(CHAR* pszBuf, INT nLen)
{
	CHAR* pszStart = pszBuf;
	CHAR* pszEnd;

	while ( pszEnd = (CHAR*)memchr(pszStart, '!', nLen) )
	{
		*pszEnd++ = '\0';

		OnSocketMessageReceive(pszStart+1);

		nLen -= pszEnd - pszStart;
		
		if ( !(pszStart = (CHAR*)memchr(pszEnd, '#', nLen)) )
		{
			return NULL;
		}
	}

	return pszStart;
}


/******************************************************************************************************************
#...!로 잘라진 패킷을 분석한다.
*******************************************************************************************************************/
VOID CChrProcess::OnSocketMessageReceive(CHAR* pszMsg)
{
	_TDEFAULTMESSAGE	tdm;

	fnDecodeMessage(&tdm, pszMsg);

	switch ( tdm.wIdent )
	{
		case SM_QUERYCHR:
		{
			DWORD	dwTime;
			dwTime = timeGetTime();
			
			while(dwTime - m_dwWaitTick < 500)
			{
				dwTime = timeGetTime();
			}
			m_xMsgBox.InitMsgBox();
			ZeroMemory(m_stSelectChrInfo, _MAX_CHAR*sizeof(CHARINFO));
			m_nSelectedChr = _SELECTED_NONE;

			if ( tdm.nRecog )
			{
				INT		nPos = 0;

				CHAR	pszDecodeMsg[1024];

				CHAR*   pszID	 = NULL;
				CHAR*   pszJob	 = NULL;
				CHAR*   pszFace	 = NULL;
				CHAR*   pszLevel = NULL;
				CHAR*   pszSex	 = NULL;
				CHAR*   pszNext	 = NULL;
				CHAR*	pszServerName = NULL;
				CHAR*   pszUpgrade = NULL; //lee wun gyo

				ZeroMemory(pszDecodeMsg, sizeof(pszDecodeMsg));

				nPos = fnDecode6BitBuf((pszMsg + _DEFBLOCKSIZE), pszDecodeMsg, sizeof(pszDecodeMsg));
				pszDecodeMsg[nPos] = '\0';

				m_nCharCnt = tdm.nRecog;

				m_nTotalPageNum = (m_nCharCnt - 1) / 2 + 1;

				if ( m_nCharCnt > _MAX_CHAR )
				{
					m_nCharCnt = _MAX_CHAR;
				}

				if (m_nCharCnt > 2)
					m_bMoreTwoChar = TRUE;
				else
					m_bMoreTwoChar = FALSE;

				pszNext = &pszDecodeMsg[0];

				for ( INT nCnt = 0; nCnt < m_nCharCnt; nCnt++ )
				{
					if ( *pszNext == '*' )
					{
						pszID = ++pszNext;
					}
					else
					{
						pszID = pszNext;
					}

					if ( pszJob = strchr(pszID, '/') )
					{
						*pszJob = '\0';
						pszJob++;

						strcpy(m_stSelectChrInfo[nCnt].pszChrName, pszID);

						m_stSelectChrInfo[nCnt].bClass = atoi(pszJob);
						
						if ( pszFace = strchr(pszJob, '/') )
						{
							*pszFace = '\0';
							pszFace++;

							if ( pszLevel = strchr(pszFace, '/') )
							{
								*pszLevel = '\0';
								pszLevel++;

								m_stSelectChrInfo[nCnt].bLevel = atoi(pszLevel);

								if ( pszSex = strchr(pszLevel, '/') )
								{
									*pszSex = '\0';
									pszSex++;

									m_stSelectChrInfo[nCnt].bGender = atoi(pszSex);
									m_stSelectChrInfo[nCnt].bSetted = TRUE;

									BYTE bMtn = _CHR_MT_NS;

									if ( m_nCharCnt == 1 )
									{
										bMtn = _CHR_MT_SM;
										m_stSelectChrInfo[nCnt].stCurrFrmInfo.bBlend = 255;
										m_stSelectChrInfo[nCnt].stCurrFrmInfo.nPosX  = 300;
										m_stSelectChrInfo[nCnt].stCurrFrmInfo.nPosY  = 210;
									}
									else
									{
										if ( nCnt%2 == 0  )
										{
											bMtn = _CHR_MT_SM;
											m_stSelectChrInfo[nCnt].stCurrFrmInfo.bBlend = 255;
											m_stSelectChrInfo[nCnt].stCurrFrmInfo.nPosX  = 250;
											m_stSelectChrInfo[nCnt].stCurrFrmInfo.nPosY  = 210;
										}
										else if ( nCnt%2 == 1 )
										{
											m_stSelectChrInfo[nCnt].stCurrFrmInfo.nPosX = 350;
											m_stSelectChrInfo[nCnt].stCurrFrmInfo.nPosY = 250;
										}
									}

									m_nSelectedChr = _SELECTED_FST_CHR;

									m_bFrontSetofSelChar = TRUE;

									SetSelectChrShowInfo();

									SetMotion(nCnt, bMtn);
///////// 서버 통합 버전
									if ( pszServerName = strchr(pszSex, '/') )
									{
										*pszServerName = '\0';  //lee wun gyo
										pszServerName++;
									}

									if ( pszUpgrade = strchr(pszServerName, '/') )
									{
										*pszUpgrade = '\0';  //lee wun gyo
										pszUpgrade++;
										m_stSelectChrInfo[nCnt].bUpgradeLevel = atoi(pszUpgrade);
									}

									strcpy(m_stSelectChrInfo[nCnt].pszServerName, pszServerName);

									if ( pszNext = strchr(pszUpgrade, '/') ) //lee wun gyo
									{
										pszNext++;
									}


///////// 서버 통합 버전
//									if ( pszNext = strchr(pszSex, '/') )
//									{
//										pszNext++;
//									}
///////////원버전


								}
							}
						}
					}
				}
			}
			else
			{
				m_xMsgBox.CreateMsgBox(&m_xImageInter, 0, _OK, g_xMsg.GetMsg(219), FALSE, 140, 110);
			}
			break;
		}
		case SM_QUERYCHR_FAIL:
		{
			m_xMsgBox.CreateMsgBox(&m_xImageInter, 0, _OK, g_xMsg.GetMsg(220), FALSE, 140, 110);
			break;
		}
		case SM_NEWCHR_SUCCESS:
		{
			g_SoundManager.SndmngrStopMp3();
			m_bChrProcState = _CHR_PROC_CREATEOUT;
			m_bBGMPlay		= FALSE;

//			SndObjPlay(0, 0, m_stEffctWav[1], 0);

//			m_xAvi.Create(g_xMainWnd.GetDirectDraw(), g_SoundManager.mSound_lpds, ".\\Data\\CreateChr.dat", FALSE, TRUE);
//			m_xAvi.Start();

			SetFocus(g_xMainWnd.GetSafehWnd());
			ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_HIDE);

			g_xClientSocket.OnQueryChar();
			m_xMsgBox.CreateMsgBox(&m_xImageInter, 0, _NONE, g_xMsg.GetMsg(200), FALSE, 155, 150);
			m_dwWaitTick = timeGetTime();
			break;
		}
		case SM_NEWCHR_FAIL:
		{
			INT nMsgNum = -1;

			switch ( tdm.nRecog )
			{
				case 2:
				{
					nMsgNum = 224;
					break;
				}
				case 3:
				{
					nMsgNum = 226;
					break;
				}
				case 4:
				{
					nMsgNum = 232;
					break;
				}
				default:
				{
					nMsgNum = 232;
					break;
				}
			}
			m_xMsgBox.CreateMsgBox(&m_xImageInter, 0, _OK, g_xMsg.GetMsg(nMsgNum), FALSE, 140, 110);
			break;
		}
		case SM_DELCHR_SUCCESS:
		{
			g_xClientSocket.OnQueryChar();
			m_xMsgBox.CreateMsgBox(&m_xImageInter, 0, _NONE, g_xMsg.GetMsg(200), FALSE, 155, 150);
			m_dwWaitTick = timeGetTime();

			break;
		}
		case SM_DELCHR_FAIL:
		{
			m_xMsgBox.CreateMsgBox(&m_xImageInter, 0, _OK, g_xMsg.GetMsg(227), FALSE, 140, 110);

			g_xClientSocket.OnQueryChar();
			m_xMsgBox.CreateMsgBox(&m_xImageInter, 0, _NONE, g_xMsg.GetMsg(200), FALSE, 155, 150);
			m_dwWaitTick = timeGetTime();

			break;
		}
		case SM_STARTPLAY:
		{
			INT		nPos = 0;
			CHAR	pszDecodeMsg[256];

			ZeroMemory(pszDecodeMsg, sizeof(pszDecodeMsg));

			nPos = fnDecode6BitBuf((pszMsg + _DEFBLOCKSIZE), pszDecodeMsg, sizeof(pszDecodeMsg));
			pszDecodeMsg[nPos] = '\0';

			CHAR* pszIP   = NULL;
			CHAR* pszPort = NULL;

			pszIP = &pszDecodeMsg[0];

			if ( pszPort = strchr(pszIP, '/') )
			{
				*pszPort = '\0';
				pszPort++;

				strcpy(g_szPreServerIP, g_szServerIP);
				g_nPreServerPort = g_nServerPort;

				strcpy(g_szServerIP, pszIP);
				g_nServerPort = atoi(pszPort);

				if ( m_nSelectedChr != _SELECTED_NONE && m_nSelectedChr < _MAX_CHAR )
				{
					strcpy(g_szCharName, m_stSelectChrInfo[m_nSelectedChr].pszChrName);
					g_nUpgradeLevel = m_stSelectChrInfo[m_nSelectedChr].bUpgradeLevel;
				}

				g_SoundManager.SndmngrStopMp3();
				m_bChrProcState = _CHR_PROC_START;
				m_bBGMPlay	    = FALSE;

				SndObjPlay(0, 0, m_stEffctWav[2], 0);

				m_xAvi.Create(g_xMainWnd.GetDirectDraw(), g_SoundManager.mSound_lpds, ".\\Data\\StartGame.dat", FALSE);
				m_xAvi.Start();
				 
			}
			break;
		}
		case SM_CHANGENAME:
		{
			if ( tdm.nRecog == 0 )
			{
				g_xClientSocket.OnQueryChar();
			}
			else if ( tdm.nRecog == 1 )
			{
				m_xMsgBox.CreateMsgBox(&m_xImageInter, 20, _YESNO, g_xMsg.GetMsg(234), TRUE, 140, 110);
			}
			break;
		}
		case SM_STARTFAIL:
		{
			if ( tdm.nRecog == 0 )
			{
				m_xMsgBox.CreateMsgBox(&m_xImageInter, 0, _OK, g_xMsg.GetMsg(221), FALSE, 140, 110);
			}
			else if ( tdm.nRecog == 1 )
			{
				m_xMsgBox.CreateMsgBox(&m_xImageInter, 20, _YESNO, g_xMsg.GetMsg(235), TRUE, 140, 110);
			}
			else if ( tdm.nRecog == 2 )
			{
				m_xMsgBox.CreateMsgBox(&m_xImageInter, 0, _OK, g_xMsg.GetMsg(238), FALSE, 140, 110);
			}
			break;
		}
		case SM_OUTOFCONNECTION:
		{
			m_xMsgBox.CreateMsgBox(&m_xImageInter, 0, _OK, g_xMsg.GetMsg(222), FALSE, 140, 110);
			break;
		}
	}
}










//-----------------------------------------------------------------------------------------------------------------
// 윈도우 메시지 관련 함수정의.
//-----------------------------------------------------------------------------------------------------------------
/******************************************************************************************************************
메시지 Procedure.
*******************************************************************************************************************/
LRESULT CChrProcess::DefMainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch ( uMsg )
	{
		case WM_CTLCOLOREDIT:
		{
			if ( (HWND)lParam == g_xChatEditBox.GetSafehWnd() )
			{
				if ( m_hBrush != NULL )
				{
					SetBkColor((HDC)wParam, RGB(0, 0, 0));
					SetTextColor((HDC)wParam, RGB(255, 255, 255));
					UnrealizeObject(m_hBrush);
					SetBrushOrgEx((HDC)wParam, 0, 0, NULL);
					return (LRESULT)m_hBrush;
				}
			}
			break;
		}
		case WM_DESTROY:
			OnDestroy(wParam, lParam);
			break;
		case WM_KEYDOWN:
			OnKeyDown(wParam, lParam);
			break;
		case WM_SYSKEYDOWN:
#ifndef _DEBUG
			return 0L;
#endif
			break;
		case ID_SOCKCLIENT_EVENT_MSG:
			g_xClientSocket.OnSocketMessage(wParam, lParam);
			break;
		case WM_LBUTTONDOWN:
			OnLButtonDown(wParam, lParam);
			break;
		case WM_LBUTTONUP:
			OnLButtonUp(wParam, lParam);
			break;
		case WM_RBUTTONDOWN:
			SetFocus(g_xChatEditBox.GetSafehWnd());
			break;
		case WM_MOUSEMOVE:
			OnMouseMove(wParam, lParam);
			break;
		case WM_MOVE:
			OnMove(wParam, lParam);
			break;
		case _WM_MSGBOX_RETURN:
			OnMsgBoxReturn(wParam, lParam);
			break;
	}

	g_SoundManager.SndmngrMessageProc(hWnd, uMsg, wParam, lParam);

	return CWHDefProcess::DefMainWndProc(hWnd, uMsg, wParam, lParam);
}


/******************************************************************************************************************
프로그램 종료시.
*******************************************************************************************************************/
LRESULT CChrProcess::OnDestroy(WPARAM wParam, LPARAM lParam)
{
//	DeleteProc();
	DestroyFindHack();
	WSACleanup();
//	ReleaseFontList();
	return 0L;
}


HRESULT	CChrProcess::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	if ( m_xMsgBox.OnKeyDown(wParam, lParam) )
	{
		return 0L;
	}

	switch ( wParam )
	{
		case VK_RETURN:
		{
			if ( m_bChrProcState == _CHR_PROC_CREATE )
			{
				if ( m_nCreatedChr != _SELECTED_NONE && m_nCreatedChr < _MAX_CHAR )
				{
					CHAR pszCreateChr[MAX_PATH];
					ZeroMemory(pszCreateChr, MAX_PATH);
					GetWindowText(g_xChatEditBox.GetSafehWnd(), pszCreateChr, MAX_PATH);
					SetWindowText(g_xChatEditBox.GetSafehWnd(), "");

					INT nLen = strlen(pszCreateChr);

					if ( pszCreateChr[0] != '\0' )
					{
						if ( nLen > 13 )
						{
							m_xMsgBox.CreateMsgBox(&m_xImageInter, 0, _OK, g_xMsg.GetMsg(223), FALSE, 140, 110);
						}
						else if ( CreateNameValidate(pszCreateChr) )
						{
							g_xClientSocket.OnNewChar(pszCreateChr, 1, m_stCreateChrInfo[m_nCreatedChr].bClass, m_stCreateChrInfo[m_nCreatedChr].bGender);
						}
						else
						{
							m_xMsgBox.CreateMsgBox(&m_xImageInter, 0, _OK, g_xMsg.GetMsg(225), FALSE, 140, 110);
						}
					}
				}

				SetFocus(g_xChatEditBox.GetSafehWnd());
				MoveWindow(g_xChatEditBox.GetSafehWnd(), g_xMainWnd.m_rcWindow.left+288, g_xMainWnd.m_rcWindow.top+405, 75, 13, TRUE);
				ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);
			}
			break;
		}
	}

	if ( HIBYTE(GetKeyState('S')) && m_bChrProcState == _CHR_PROC_SELECT )
	{
		if ( m_nSelectedChr != _SELECTED_NONE && m_nSelectedChr < _MAX_CHAR )
		{
//     통합 버전
			CHAR szTemp[MAX_PATH];
			sprintf(szTemp, "%s/%s", m_stSelectChrInfo[m_nSelectedChr].pszChrName, m_stSelectChrInfo[m_nSelectedChr].pszServerName );
			g_xClientSocket.OnSelChar(szTemp);
//     통합 버전
/* 원래 버전
			g_xClientSocket.OnSelChar(m_stSelectChrInfo[m_nSelectedChr].pszChrName);
*/
		}
		else
		{
			m_xMsgBox.CreateMsgBox(&m_xImageInter, 0, _OK, g_xMsg.GetMsg(230), FALSE, 140, 110);
		}


	}


	return 0L;
}


LRESULT	CChrProcess::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	INT nCnt;

	m_ptMousePos.x = LOWORD(lParam);
	m_ptMousePos.y = HIWORD(lParam);

	if ( m_xMsgBox.OnLButtonDown(m_ptMousePos) )
	{
		return 0L;
	}

	if ( m_bChrProcState == _CHR_PROC_SELECT )
	{
		INT		nSelectIdx;

		for ( nCnt = 0; nCnt < _MAX_CHAR; nCnt++ )
		{
/*
			if (m_bFrontSetofSelChar == FALSE)
				nSelectIdx = nCnt + 2;
			else
				nSelectIdx = nCnt;
*/
			nSelectIdx = 2*m_nPageNum + nCnt;

			if ( m_stSelectChrInfo[nSelectIdx].bSetted )
			{
				if ( PtInRect(&m_stSelectChrInfo[nSelectIdx].stCurrFrmInfo.rcChrRgn, m_ptMousePos) )
				{
					if ( m_nSelectedChr != nSelectIdx )
					{
						SetMotion(nSelectIdx, _CHR_MT_SM);

						if ( nSelectIdx == 0 )
						{
							if ( m_stSelectChrInfo[1].bSetted )
							{
								SetMotion(1, _CHR_MT_R);
							}
						}
						else if ( nSelectIdx == 1 )
						{
							if ( m_stSelectChrInfo[0].bSetted )
							{
								SetMotion(0, _CHR_MT_R);
							}
						}
						else if ( nSelectIdx == 2 )
						{
							if ( m_stSelectChrInfo[3].bSetted )
							{
								SetMotion(3, _CHR_MT_R);
							}
						}
						else if ( nSelectIdx == 3 )
						{
							if ( m_stSelectChrInfo[2].bSetted )
							{
								SetMotion(2, _CHR_MT_R);
							}
						}
						else if ( nSelectIdx == 4 )
						{
							if ( m_stSelectChrInfo[5].bSetted )
							{
								SetMotion(5, _CHR_MT_R);
							}
						}
						else if ( nSelectIdx == 5 )
						{
							if ( m_stSelectChrInfo[4].bSetted )
							{
								SetMotion(4, _CHR_MT_R);
							}
						}
						else if ( nSelectIdx == 6 )
						{
							if ( m_stSelectChrInfo[7].bSetted )
							{
								SetMotion(7, _CHR_MT_R);
							}
						}
						else if ( nSelectIdx == 7 )
						{
							if ( m_stSelectChrInfo[6].bSetted )
							{
								SetMotion(6, _CHR_MT_R);
							}
						}
						else if ( nSelectIdx == 8 )
						{
							if ( m_stSelectChrInfo[9].bSetted )
							{
								SetMotion(9, _CHR_MT_R);
							}
						}
						else if ( nSelectIdx == 9 )
						{
							if ( m_stSelectChrInfo[8].bSetted )
							{
								SetMotion(8, _CHR_MT_R);
							}
						}
						else if ( nSelectIdx == 10 )
						{
							if ( m_stSelectChrInfo[11].bSetted )
							{
								SetMotion(11, _CHR_MT_R);
							}
						}
						else if ( nSelectIdx == 11 )
						{
							if ( m_stSelectChrInfo[10].bSetted )
							{
								SetMotion(10, _CHR_MT_R);
							}
						}
						else if ( nSelectIdx == 12 )
						{
							if ( m_stSelectChrInfo[13].bSetted )
							{
								SetMotion(13, _CHR_MT_R);
							}
						}
						else if ( nSelectIdx == 13 )
						{
							if ( m_stSelectChrInfo[12].bSetted )
							{
								SetMotion(12, _CHR_MT_R);
							}
						}
						else if ( nSelectIdx == 14 )
						{
							if ( m_stSelectChrInfo[15].bSetted )
							{
								SetMotion(15, _CHR_MT_R);
							}
						}
						else if ( nSelectIdx == 15 )
						{
							if ( m_stSelectChrInfo[14].bSetted )
							{
								SetMotion(14, _CHR_MT_R);
							}
						}
					}

					m_nSelectedChr = nSelectIdx;

					SetSelectChrShowInfo();
					break;
				}
			}
		}

		for ( nCnt = 0; nCnt < _MAX_CHR_SELECT_BTN; nCnt++ )
		{
			m_xSelectBtn[nCnt].OnLButtonDown(m_ptMousePos);
		}
	}
	else if ( m_bChrProcState == _CHR_PROC_CREATE )
	{
		SetFocus(g_xChatEditBox.GetSafehWnd());

		for ( nCnt = 0; nCnt < _MAX_CHAR; nCnt++ )
		{
			if ( m_stCreateChrInfo[nCnt].bSetted )
			{
				if ( PtInRect(&m_stCreateChrInfo[nCnt].stCurrFrmInfo.rcChrRgn, m_ptMousePos) )
				{
					if ( m_nCreatedChr != nCnt )
					{
						SetMotion(nCnt, _CHR_MT_CC);
					}

					m_nCreatedChr = nCnt;

					if ( m_nCreatedChr != _SELECTED_NONE )
					{
						SetCharExplain(m_nCreatedChr, m_stCreateChrInfo[nCnt].bClass);
					}
				}
			}
		}

		for ( INT nCnt = 0; nCnt < _CHR_CHR_CREATE_BTN; nCnt++ )
		{
			m_xCreateBtn[nCnt].OnLButtonDown(m_ptMousePos);
		}
	}

	return 0L;
}


LRESULT	CChrProcess::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	INT nCnt;

	m_ptMousePos.x = LOWORD(lParam);
	m_ptMousePos.y = HIWORD(lParam);

	if ( m_xMsgBox.OnLButtonUp(m_ptMousePos) )
	{
		return 0L;
	}

	if ( m_bChrProcState == _CHR_PROC_SELECT )
	{
		if ( m_xSelectBtn[_MAX_CHR_SELECT_CREATE].OnLButtonUp(m_ptMousePos) )
		{
			BOOL bGoInCreate = FALSE;
			
			for ( nCnt = 0; nCnt < _MAX_SHOW_CHAR; nCnt++ )
			{
				if ( !m_stSelectChrInfo[nCnt].bSetted )
				{
					bGoInCreate = TRUE;
					break;
				}
			}

			if ( bGoInCreate )
			{
				g_SoundManager.SndmngrStopMp3();
				m_bChrProcState = _CHR_PROC_CREATEIN;
				m_bBGMPlay	    = FALSE;

				SndObjPlay(0, 0, m_stEffctWav[0], 0);

				m_xAvi.Create(g_xMainWnd.GetDirectDraw(), g_SoundManager.mSound_lpds, ".\\Data\\CreateChr.dat", FALSE);
				m_xAvi.Start();
			}
			else
			{
				m_xMsgBox.CreateMsgBox(&m_xImageInter, 0, _OK, g_xMsg.GetMsg(226), FALSE, 140, 110);
			}
		}
		else if ( m_xSelectBtn[_MAX_CHR_SELECT_START].OnLButtonUp(m_ptMousePos) )
		{
			if ( m_nSelectedChr != _SELECTED_NONE && m_nSelectedChr < _MAX_CHAR )
			{
//     통합 버전
				CHAR szTemp[MAX_PATH];
				sprintf(szTemp, "%s/%s/%d", m_stSelectChrInfo[m_nSelectedChr].pszChrName, m_stSelectChrInfo[m_nSelectedChr].pszServerName, m_stSelectChrInfo[m_nSelectedChr].bUpgradeLevel);
				g_xClientSocket.OnSelChar(szTemp);
//     통합 버전
/* 원래 버전
				g_xClientSocket.OnSelChar(m_stSelectChrInfo[m_nSelectedChr].pszChrName);
*/
			}
			else
			{
				m_xMsgBox.CreateMsgBox(&m_xImageInter, 0, _OK, g_xMsg.GetMsg(230), FALSE, 140, 110);
			}
		}
		else if ( m_xSelectBtn[_MAX_CHR_SELECT_QUIT].OnLButtonUp(m_ptMousePos) )
		{
			DeleteProc();
			g_xMainWnd.m_pxDefProcess = &g_xGameProc;
			g_bProcState = _GAME_PROC;	
			g_xGameProc.m_bCreditShow = TRUE;
			g_xGameProc.m_xImage.m_xImageList[70].NewLoad(".\\Data\\GameInter.wil");
			g_xGameProc.LoadCredit();
			ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_HIDE);

//			SendMessage(g_xMainWnd.GetSafehWnd(), WM_DESTROY, NULL, NULL);
		}
		else if ( m_xSelectBtn[_MAX_CHR_SELECT_DELETE].OnLButtonUp(m_ptMousePos) )
		{
			if ( m_nSelectedChr != _SELECTED_NONE )
			{
				m_xMsgBox.CreateMsgBox(&m_xImageInter, 1, _YESNO, g_xMsg.GetMsg(228), TRUE, 140, 110, 1, TRUE);
//				m_xMsgBox.CreateMsgBox(&m_xImageInter, 1, _YESNO, g_xMsg.GetMsg(228), FALSE, 140, 110);
			}
			else
			{
				m_xMsgBox.CreateMsgBox(&m_xImageInter, 0, _OK, g_xMsg.GetMsg(227), FALSE, 140, 110);
			}
		}
		else if ( m_xSelectBtn[_MAX_CHR_SELECT_NEXT].OnLButtonUp(m_ptMousePos, FALSE) )
		{
			BYTE	bMtn;
			INT		nCnt;

			if (m_bMoreTwoChar == FALSE)
				return 0L;

			if ( m_nPageNum == m_nTotalPageNum - 1 )
				return 0L;

			if ( m_nPageNum < m_nTotalPageNum )
			{
				m_nPageNum++;
				m_xSelectBtn[_MAX_CHR_SELECT_NEXT].OnLButtonUp(m_ptMousePos);
				bMtn = _CHR_MT_SM;
				nCnt = 2*m_nPageNum;
				SetMotion(m_nSelectedChr, _CHR_MT_NS);
				m_nSelectedChr = 2*m_nPageNum;
				SetSelectChrShowInfo();
				SetMotion(nCnt, bMtn);

				m_bFrontSetofSelChar = FALSE;
				if ( m_nPageNum == m_nTotalPageNum - 1 )
					m_xSelectBtn[_MAX_CHR_SELECT_NEXT].ResetGameBtn(1155, 1155, 1155);

				m_xSelectBtn[_MAX_CHR_SELECT_BEFORE].ResetGameBtn(1152, 1151, 1150);
			}


/*
			if (m_bFrontSetofSelChar ==  TRUE)
			{
				m_xSelectBtn[_MAX_CHR_SELECT_NEXT].OnLButtonUp(m_ptMousePos);
				bMtn = _CHR_MT_SM;
				nCnt = _SELECTED_TRD_CHR;
				SetMotion(m_nSelectedChr, _CHR_MT_NS);
				m_nSelectedChr = _SELECTED_TRD_CHR;
				SetSelectChrShowInfo();
				SetMotion(nCnt, bMtn);

				m_bFrontSetofSelChar = FALSE;
				m_xSelectBtn[_MAX_CHR_SELECT_NEXT].ResetGameBtn(1155, 1155, 1155);
				m_xSelectBtn[_MAX_CHR_SELECT_BEFORE].ResetGameBtn(1152, 1151, 1150);
			}
			else
				return 0L;
*/
		}
		else if ( m_xSelectBtn[_MAX_CHR_SELECT_BEFORE].OnLButtonUp(m_ptMousePos, FALSE) )
		{
			BYTE	bMtn;
			INT		nCnt;

			if (m_bMoreTwoChar == FALSE)
				return 0L;

			if ( m_nPageNum > 0 )
			{
				m_nPageNum--;
				m_xSelectBtn[_MAX_CHR_SELECT_BEFORE].OnLButtonUp(m_ptMousePos);
				bMtn = _CHR_MT_SM;
				nCnt = 2*m_nPageNum;
				SetMotion(m_nSelectedChr, _CHR_MT_NS);
				m_nSelectedChr = 2*m_nPageNum;
				SetSelectChrShowInfo();
				SetMotion(nCnt, bMtn);

				m_bFrontSetofSelChar = FALSE;
				if ( m_nPageNum == 0 )
					m_xSelectBtn[_MAX_CHR_SELECT_BEFORE].ResetGameBtn(1152, 1152, 1152);

				m_xSelectBtn[_MAX_CHR_SELECT_NEXT].ResetGameBtn(1155, 1154, 1153);
			}

/*
			if (m_bFrontSetofSelChar ==  FALSE)
			{
				m_xSelectBtn[_MAX_CHR_SELECT_BEFORE].OnLButtonUp(m_ptMousePos);
				bMtn = _CHR_MT_SM;
				nCnt = _SELECTED_FST_CHR;
				SetMotion(m_nSelectedChr, _CHR_MT_NS);
				m_nSelectedChr = _SELECTED_FST_CHR;
				SetSelectChrShowInfo();
				SetMotion(nCnt, bMtn);

				m_bFrontSetofSelChar = TRUE;
				m_xSelectBtn[_MAX_CHR_SELECT_BEFORE].ResetGameBtn(1152, 1152, 1152);
				m_xSelectBtn[_MAX_CHR_SELECT_NEXT].ResetGameBtn(1155, 1154, 1153);
			}
			else
				return 0L;
*/
		}
	}
	else if ( m_bChrProcState == _CHR_PROC_CREATE )
	{
		RECT rcTemp;
		SetRect(&rcTemp, 294, 404, 371, 419);

		if ( PtInRect(&rcTemp, m_ptMousePos) )
		{
			SetFocus(g_xChatEditBox.GetSafehWnd());
			MoveWindow(g_xChatEditBox.GetSafehWnd(), g_xMainWnd.m_rcWindow.left+288, g_xMainWnd.m_rcWindow.top+405, 75, 13, TRUE);
			ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);
		}
		else if ( m_xCreateBtn[_CHR_CHR_CREATE_CANCEL].OnLButtonUp(m_ptMousePos) )
		{
			g_SoundManager.SndmngrStopMp3();
			m_bChrProcState = _CHR_PROC_CREATEOUT;
			m_bBGMPlay		= FALSE;

//			SndObjPlay(0, 0, m_stEffctWav[1], 0);

//			m_xAvi.Create(g_xMainWnd.GetDirectDraw(), g_SoundManager.mSound_lpds, ".\\Data\\CreateChr.dat", FALSE, TRUE);
//			m_xAvi.Start();

			SetFocus(g_xMainWnd.GetSafehWnd());
			ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_HIDE);

			g_xClientSocket.OnQueryChar();
//			m_xMsgBox.CreateMsgBox(&m_xImageInter, 0, _NONE, g_xMsg.GetMsg(200), FALSE, 140, 110);
//			m_dwWaitTick = timeGetTime();
		}
		else if ( m_xCreateBtn[_CHR_CHR_CREATE_WARIOR].OnLButtonUp(m_ptMousePos) )
		{
			SetChrInfo(&m_stCreateChrInfo[0], _GENDER_MAN, _JOB_JUNSA, 0);
			SetMotion(0, _CHR_MT_CC);

			SetChrInfo(&m_stCreateChrInfo[1], _GENDER_WOMAN, _JOB_JUNSA, 0);
			SetMotion(1, _CHR_MT_CC);

			if ( m_nCreatedChr !=_SELECTED_NONE )
			{
				SetCharExplain(m_nCreatedChr, _JOB_JUNSA);
			}
		}
		else if ( m_xCreateBtn[_CHR_CHR_CREATE_MAGICIAN].OnLButtonUp(m_ptMousePos) )
		{
			SetChrInfo(&m_stCreateChrInfo[0], _GENDER_MAN, _JOB_SULSA, 0);
			SetMotion(0, _CHR_MT_CC);

			SetChrInfo(&m_stCreateChrInfo[1], _GENDER_WOMAN, _JOB_SULSA, 0);
			SetMotion(1, _CHR_MT_CC);

			if ( m_nCreatedChr != _SELECTED_NONE )
			{
				SetCharExplain(m_nCreatedChr, _JOB_SULSA);
			}
		}
		else if ( m_xCreateBtn[_CHR_CHR_CREATE_CLERIC].OnLButtonUp(m_ptMousePos) )
		{
			SetChrInfo(&m_stCreateChrInfo[0], _GENDER_MAN, _JOB_DOSA, 0);
			SetMotion(0, _CHR_MT_CC);

			SetChrInfo(&m_stCreateChrInfo[1], _GENDER_WOMAN, _JOB_DOSA, 0);
			SetMotion(1, _CHR_MT_CC);

			if ( m_nCreatedChr != _SELECTED_NONE )
			{
				SetCharExplain(m_nCreatedChr, _JOB_DOSA);
			}
		}
		else if ( m_xCreateBtn[_CHR_CHR_CREATE_ARCHER].OnLButtonUp(m_ptMousePos) )
		{
			SetChrInfo(&m_stCreateChrInfo[0], _GENDER_MAN, _JOB_GUNGSA, 0);
			SetMotion(0, _CHR_MT_CC);

			SetChrInfo(&m_stCreateChrInfo[1], _GENDER_WOMAN, _JOB_GUNGSA, 0);
			SetMotion(1, _CHR_MT_CC);

			if ( m_nCreatedChr != _SELECTED_NONE )
			{
				SetCharExplain(m_nCreatedChr, _JOB_GUNGSA);
			}
		}
		else if ( m_xCreateBtn[_CHR_CHR_CREATE_MAKE].OnLButtonUp(m_ptMousePos) )
		{
			if ( m_nCreatedChr != _SELECTED_NONE && m_nCreatedChr < _MAX_CHAR && m_stCreateChrInfo[m_nCreatedChr].bClass != _JOB_GUNGSA )
			{
				CHAR pszCreateChr[MAX_PATH];
				ZeroMemory(pszCreateChr, MAX_PATH);
				GetWindowText(g_xChatEditBox.GetSafehWnd(), pszCreateChr, MAX_PATH);
				SetWindowText(g_xChatEditBox.GetSafehWnd(), "");

				INT nLen = strlen(pszCreateChr);

				if ( pszCreateChr[0] != '\0' )
				{
					if ( nLen > 13 )
					{
						m_xMsgBox.CreateMsgBox(&m_xImageInter, 0, _OK, g_xMsg.GetMsg(223), FALSE, 140, 110);
					}
					else if ( CreateNameValidate(pszCreateChr) )
					{
						g_xClientSocket.OnNewChar(pszCreateChr, 1, m_stCreateChrInfo[m_nCreatedChr].bClass, m_stCreateChrInfo[m_nCreatedChr].bGender);
					}
					else
					{
						m_xMsgBox.CreateMsgBox(&m_xImageInter, 0, _OK, g_xMsg.GetMsg(225), FALSE, 140, 110);
					}
				}
			}
		}
	}

	return 0L;
}


LRESULT	CChrProcess::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	m_ptMousePos.x = LOWORD(lParam);
	m_ptMousePos.y = HIWORD(lParam);

	m_xMsgBox.OnMouseMove(m_ptMousePos);

	if ( m_bChrProcState == _CHR_PROC_SELECT )
	{
		for ( INT nCnt = 0; nCnt < _MAX_SHOW_CHAR; nCnt++ )
		{
			m_xSelectBtn[nCnt].OnMouseMove(m_ptMousePos);
		}
	}
	else if ( m_bChrProcState == _CHR_PROC_CREATE )
	{
		for ( INT nCnt = 0; nCnt < _CHR_CHR_CREATE_BTN; nCnt++ )
		{
			m_xCreateBtn[nCnt].OnMouseMove(m_ptMousePos);
		}
	}

	return 0L;
}


LRESULT	CChrProcess::OnMsgBoxReturn(WPARAM wParam, LPARAM lParam)
{
	if ( HIBYTE(HIWORD(wParam))== 1 && LOBYTE(HIWORD(wParam)) == _BTN_YES )
	{
		if ( m_nSelectedChr != _SELECTED_NONE && m_nSelectedChr < _MAX_CHAR )
		{
			CHAR szTemp[MAX_PATH];
			sprintf(szTemp, "%s/%s/%s/%d",  m_stSelectChrInfo[m_nSelectedChr].pszChrName, lParam, m_stSelectChrInfo[m_nSelectedChr].pszServerName, m_stSelectChrInfo[m_nSelectedChr].bUpgradeLevel);
			g_xClientSocket.OnDelChar(szTemp);
			g_xClientSocket.OnQueryChar();
			m_xMsgBox.CreateMsgBox(&m_xImageInter, 0, _NONE, g_xMsg.GetMsg(200), FALSE, 155, 150);
			m_dwWaitTick = timeGetTime();
		}
	}
	else if ( HIBYTE(HIWORD(wParam))== 20 && LOBYTE(HIWORD(wParam)) == _BTN_YES )
	{
		CHAR szTemp[MAX_PATH], szNewName[MAX_PATH];

		sprintf(szNewName, "%s", lParam);

		if ( CreateNameValidate(szNewName) )
		{
			m_xMsgBox.CreateMsgBox(&m_xImageInter, 0, _OK, g_xMsg.GetMsg(225), FALSE, 140, 110);
			sprintf(szTemp, "%s/%s/%s/%s",  g_szUserID, m_stSelectChrInfo[m_nSelectedChr].pszChrName, szNewName, m_stSelectChrInfo[m_nSelectedChr].pszServerName );
			g_xClientSocket.OnChangeCharName(szTemp);
			m_dwWaitTick = timeGetTime();
		}
		else
		{
			m_xMsgBox.CreateMsgBox(&m_xImageInter, 0, _OK, g_xMsg.GetMsg(225), FALSE, 140, 110);
		}
	}

	if ( m_bChrProcState == _CHR_PROC_CREATE )
	{
		MoveWindow(g_xChatEditBox.GetSafehWnd(), g_xMainWnd.m_rcWindow.left+288, g_xMainWnd.m_rcWindow.top+405, 75, 13, TRUE);
		ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);
		SetFocus(g_xChatEditBox.GetSafehWnd());
	}

	g_xChatEditBox.SetEnterUse(FALSE);

	return 0L;
}


LRESULT	CChrProcess::OnMove(WPARAM wParam, LPARAM lParam)
{
	if ( m_bChrProcState == _CHR_PROC_CREATE )
	{
		SetFocus(g_xMainWnd.GetSafehWnd());
		ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_HIDE);
	}

	return 0L;
}

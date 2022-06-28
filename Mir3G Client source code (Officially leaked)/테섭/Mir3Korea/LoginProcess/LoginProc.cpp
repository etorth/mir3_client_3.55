#include "StdAfx.h"


//-----------------------------------------------------------------------------------------------------------------
// Procedure �����Լ�.
//-----------------------------------------------------------------------------------------------------------------
/******************************************************************************************************************
[������]
*******************************************************************************************************************/
CLoginProcess::CLoginProcess()
{
	Init();
}


/******************************************************************************************************************
[�Ҹ���]
*******************************************************************************************************************/
CLoginProcess::~CLoginProcess()
{
	DeleteProc();
}


/******************************************************************************************************************
������ ��簴ü�� �ʱ�ȭ.
*******************************************************************************************************************/
VOID CLoginProcess::Init()
{
	m_xMsgBox.InitMsgBox();
	m_xImageInter.Init();
	m_xImageLogin.Init();
	m_xAvi.Init();

	m_bProcState = _LOGINPROC_LOGO;
	m_bBackState = _LOGINBACK_LOGO;
	m_nSvrPort   = _LOGIN_SERVER_PORT_DATA;

	m_bLoginInputState = _LOGININPUT_ID;
	SetRect(&m_rcEditID, 0, 0, 0, 0);
	SetRect(&m_rcEditPW, 0, 0, 0, 0);

	ZeroMemory(&m_ptMousePos, sizeof(POINT));

	ZeroMemory(m_pszID, MAX_PATH);
	ZeroMemory(m_pszPW, MAX_PATH);

	ZeroMemory(&m_pszSvrIP, MAX_PATH);

	m_stSvrList.ClearAll();
	SetRect(&m_rcSvrListRgn, 0, 0, 0, 0);
	m_nClickedSvr = -1;

	m_nFadeProcTime = 0;

	m_hBrush = NULL;

	for ( INT nCnt = 0; nCnt < _MAX_LOGIN_BTN; nCnt++ )
	{
		m_xLoginBtn[nCnt].Init();
	}

 	D3DVECTOR vNorm(0, 0, -1);
	m_avBillBoard[0]  = D3DVERTEX(D3DVECTOR(-0.5f, 0.5f, 0), vNorm, 0, 0);
	m_avBillBoard[1]  = D3DVERTEX(D3DVECTOR(-0.5f,-0.5f, 0), vNorm, 0, 1);
	m_avBillBoard[2]  = D3DVERTEX(D3DVECTOR( 0.5f, 0.5f, 0), vNorm, 1, 0);
	m_avBillBoard[3]  = D3DVERTEX(D3DVECTOR( 0.5f,-0.5f, 0), vNorm, 1, 1);

	m_dwBGMPlayTime = 0;
	m_bBGMPlay		= TRUE;

	m_nBackIdx	= 0;

//	m_xClientSysMsg.Init();

}




BOOL CLoginProcess::LoadNoticeText()
{
	// ���帮��Ʈ �ʱ�ȭ.
	m_xNoticeList.ClearAll();

	// �������� ����.
	SetRect(&m_rcNotice, 23, 120, 247, 353);

	INT nW = m_rcNotice.right - m_rcNotice.left;

	INT nCnt;
	INT nLineCnt = 0;
	CHAR pszDivied[_MAX_STRING_LEN*2];
	CHAR pszArg[10][MAX_PATH];
	ZeroMemory(pszDivied, _MAX_STRING_LEN*2);
	ZeroMemory(pszArg,	  MAX_PATH*10);

	FILE *fp = fopen("Notice.txt", "rb");
	if ( !fp )
	{
		return FALSE;
	}

	CHAR	pszLine[MAX_PATH];
	CHAR	pszGet[MAX_PATH];
	CHAR*	pszNext = NULL;
	CHAR*	pszMark = NULL;
	CHAR*	pszStr  = NULL;

	while ( fgets(pszLine, MAX_PATH, fp) )
	{
		if ( pszLine[0] != ';' )
		{
			if ( pszNext = (CHAR*)strchr(pszLine, '\r') )
			{
				*pszNext = '\0';
			}

			pszStr = pszLine;

			INT	nSize   = 9;
			INT nBC     = 0;
			INT nFC     = 2;
			INT nWeight = FW_NORMAL;

			// ��Ʈ������.
			if ( pszMark = (CHAR*)strchr(pszLine, '!') )
			{
				ZeroMemory(pszGet, MAX_PATH);
				sscanf(++pszMark, "%s %*[^\0]", pszGet);
				nSize = atoi(pszGet);
			}

			// ��ƮBackColor.
			if ( pszMark = (CHAR*)strchr(pszLine, '@') )
			{
				ZeroMemory(pszGet, MAX_PATH);
				sscanf(++pszMark, "%s %*[^\0]", pszGet);
				nBC = atoi(pszGet);
			}

			// ��ƮColor.
			if ( pszMark = (CHAR*)strchr(pszLine, '#') )
			{
				ZeroMemory(pszGet, MAX_PATH);
				sscanf(++pszMark, "%s %*[^\0]", pszGet);
				nFC = atoi(pszGet);
			}

			// ��ƮBold.(�β���)
			if ( (CHAR*)strchr(pszLine, '$') )
			{
				nWeight = FW_BOLD;
			}

			// ����.
			if ( pszMark = (CHAR*)strchr(pszLine, '*') )
			{
				pszStr = ++pszMark;
			}

			ZeroMemory(pszDivied, _MAX_STRING_LEN*2);
			ZeroMemory(pszArg,	  MAX_PATH*10);
			g_xMainWnd.StringDivide(nW, nLineCnt, pszStr, pszDivied, g_xMainWnd.CreateGameFont(NULL, nSize, 0, nWeight));
			sscanf(pszDivied, "%[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c",
				   pszArg[0], pszArg[1], pszArg[2], pszArg[3], pszArg[4], 
				   pszArg[5], pszArg[6], pszArg[7], pszArg[8], pszArg[9]);

			if ( nLineCnt > 10 )
			{
				nLineCnt = 10;
			}

			for ( nCnt = 0; nCnt < nLineCnt; nCnt++ )
			{
				LPNOTICE pstNotice = new NOTICE;
				pstNotice->nBC  = nBC;
				pstNotice->nFC  = nFC;
				pstNotice->nSize = nSize;
				pstNotice->nWeight = nWeight;
				strcpy(pstNotice->pszMsg, pszArg[nCnt]);
				m_xNoticeList.Insert(pstNotice);
			}
		}
	}

	fclose( fp );
	DeleteFile("Notice.txt");

	return TRUE;
}


VOID CLoginProcess::ShowNotice(INT nLoopTime)
{
	if ( m_xNoticeList.GetCount() > 0 && m_bProcState == _LOGINPROC_LOGIN )
	{
		// ȭ�����.
		LPNOTICE pstNotice   = NULL;
		CListNode < NOTICE > *pNode;

		INT nCnt;

		RECT rc = {m_rcNotice.left-5, m_rcNotice.top-5, m_rcNotice.right+5, m_rcNotice.bottom};
		INT nW = rc.right - rc.left;
		INT nH = rc.bottom - rc.top;

		D3DVECTOR	 vecTrans(rc.left, rc.top, 0);
		D3DVECTOR	 vecScale(nW, nH, 1);
		D3DMATERIAL7 mtrl;

/// ���� ��ġ
		INT nRed, nGreen, nBlue;
		INT nRedLine, nGreenLine, nBlueLine;

		switch ( m_nBackIdx )
		{
		case 20:
		case 27:
			nRed = 57;
			nGreen = 77;
			nBlue = 51;
			nRedLine = 43;
			nGreenLine = 55;
			nBlueLine = 38;
			break;
		case 21:
		case 22:
		case 23:
		case 30:
			nRed = 75;
			nGreen = 50;
			nBlue = 0;
			nRedLine = 100;
			nGreenLine = 75;
			nBlueLine = 50;
			break;
		case 24:
		case 25:
		case 26:
			nRed = 25;
			nGreen = 78;
			nBlue = 104;
			nRedLine = 40;
			nGreenLine = 95;
			nBlueLine = 120;
			break;
		case 28:
			nRed = 40;
			nGreen = 30;
			nBlue = 98;
			nRedLine = 27;
			nGreenLine = 20;
			nBlueLine = 65;
			break;
		case 29:
			nRed = 54;
			nGreen = 90;
			nBlue = 143;
			nRedLine = 37;
			nGreenLine = 62;
			nBlueLine = 99;
			break;
		case 31:
		case 32:
		case 33:
			nRed = 10;
			nGreen = 10;
			nBlue = 10;
			nRedLine = 5;
			nGreenLine = 5;
			nBlueLine = 5;
			break;
		}

		D3DUtil_InitMaterial(mtrl, (FLOAT)nRed/255.0f, (FLOAT)nGreen/255.0f, (FLOAT)nBlue/255.0f);
		mtrl.diffuse.a = 100.0f/255.0f;
		DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
		g_xMainWnd.DrawWithGDI(&rc, NULL, RGB(nRedLine, nGreenLine, nBlueLine), 1);
/// ���� ��ġ

/*
		D3DUtil_InitMaterial(mtrl, (FLOAT)75/255.0f, (FLOAT)50/255.0f, (FLOAT)0/255.0f);
		mtrl.diffuse.a = 100.0f/255.0f;
		DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
		g_xMainWnd.DrawWithGDI(&rc, NULL, RGB(100, 75, 50), 1);
*/
		static INT nScrlY = 0;
		static INT nSum   = -1500;

		if ( nLoopTime < 10000 )
		{
			nSum += nLoopTime;
		}

		if ( nSum > 100 )
		{
			nSum = 0;

			if ( m_xNoticeList.GetCount()*14 > nH )
			{
				nScrlY--;

				if ( abs(nScrlY) >= (m_xNoticeList.GetCount()-1)*14 )
				{
					nScrlY = nH-14;
				}
			}
		}

		for ( pNode = m_xNoticeList.GetHead(), nCnt = 0; pNode; pNode = pNode->GetNext(), nCnt++ )
		{
			pstNotice = pNode->GetData();

			if ( pstNotice )
			{
				if ( m_rcNotice.top+(nCnt*14)+nScrlY >= m_rcNotice.top && m_rcNotice.top+((nCnt+1)*14)+nScrlY < m_rcNotice.bottom )
				{
					g_xMainWnd.PutsHan(NULL, m_rcNotice.left, m_rcNotice.top+(nCnt*14)+nScrlY, 
									   GetChatColor(pstNotice->nFC), GetChatColor(pstNotice->nBC), 
									   pstNotice->pszMsg, g_xMainWnd.CreateGameFont(NULL, pstNotice->nSize, 0, pstNotice->nWeight));
				}
			}
		}
	}
}


VOID CLoginProcess::ReleaseNoticeText()
{
	// �������׺κ� �ʱ�ȭ.
}



/******************************************************************************************************************
�ʿ��� ����Ÿ�� �ʱ�ȭ�ϰ� �ε��Ѵ�.
Prcedure�� ���۵Ǳ����� ȣ��Ǿ�� �Ѵ�.
Load()->RenderScene()->SetNextProc()�� �����̴�.
*******************************************************************************************************************/
VOID CLoginProcess::Load()
{
	Init();

	SetSvrBtn();

	if ( g_execCmds.szServerIP[0] )
	{
		SetSvrIP(g_execCmds.szServerIP);
	}
	if ( g_execCmds.nPort != -1 )
	{
		SetSvrPort(g_execCmds.nPort);
	}

	if ( g_stInfoShop.bSetted )
	{
		SetSvrIP(g_stInfoShop.pszAddr);
		SetSvrPort(g_stInfoShop.nPort);
	}

	strcpy(g_szServerIP, m_pszSvrIP);

	m_xImageInter.NewLoad(".\\Data\\gameinter.wil");
	m_xImageLogin.NewLoad(".\\Data\\Interface1c.wil");

	ZeroMemory(g_xChatEditBox.m_szInputMsg, sizeof(g_xChatEditBox.m_szInputMsg));

	if ( m_hBrush != NULL )
	{
		DeleteObject(m_hBrush);
		m_hBrush = NULL;
	}
	m_hBrush = CreateSolidBrush(RGB(0, 0, 0));

	m_xAvi.Create(g_xMainWnd.GetDirectDraw(), g_SoundManager.mSound_lpds, ".\\Data\\wemade.dat", FALSE);
	m_xAvi.SetDestRect(0, 60, 640, 420);
	m_xAvi.Start();
	
	m_xLoginBtn[_LOGIN_BTN_CONN]. CreateGameBtn(&m_xImageLogin, 11, 11, 459, 436, NULL, _BTN_TYPE_FOCUS, 10, TRUE);
	m_xLoginBtn[_LOGIN_BTN_REG].  CreateGameBtn(&m_xImageLogin, 13, 13, 139, 379, NULL, _BTN_TYPE_FOCUS, 12, TRUE);
	m_xLoginBtn[_LOGIN_BTN_CHGPW].CreateGameBtn(&m_xImageLogin, 15, 15, 279, 379, NULL, _BTN_TYPE_FOCUS, 14, TRUE);
	m_xLoginBtn[_LOGIN_BTN_QUIT]. CreateGameBtn(&m_xImageLogin, 17, 17, 439, 379, NULL, _BTN_TYPE_FOCUS, 16, TRUE);

	SetRect(&m_rcEditID, 128, 440, 227, 454);
	SetRect(&m_rcEditPW, 326, 440, 425, 454);

	g_xChatEditBox.SetLimitText(24);
	// Enter Key�Է¿� ���ؼ� Game Procedure���� ���� ������ �����Ѵ�.
	g_xChatEditBox.SetEnterUse(FALSE);

	LoadNoticeText();

	g_xClientSocket.ConnectToServer(g_xMainWnd.GetSafehWnd(), m_pszSvrIP, m_nSvrPort);

	SndObjDestroy(m_stOpenSnd);
	m_stOpenSnd = SndObjCreate(g_SoundManager.mSound_lpds, ".\\Sound\\Opening.wav", 10);

	// ���ȭ�� �����ϰ� �׷��� �׸� �ε���
	m_nBackIdx = GetRandomNum(20,32);





	
}


/******************************************************************************************************************
�Ҹ��� �ʿ��� ��ü�� ����.
Procedure�� ����ǰų�, �����¿��� ���α׷��� �����ų�� ȣ��ȴ�.
*******************************************************************************************************************/
VOID CLoginProcess::DeleteProc()
{
	m_xImageInter.Destroy();
	m_xImageLogin.Destroy();

	g_xClientSocket.DisconnectToServer();

	if ( m_hBrush != NULL )
	{
		DeleteObject(m_hBrush);
		m_hBrush = NULL;
	}

	m_stSvrList.ClearAll();

	m_xAvi.Release();

	// Edit Box������ ������� �ǵ�����.
	g_xChatEditBox.SetEnterUse(TRUE);

//	m_xClientSysMsg.Destroy();

	m_dwBGMPlayTime = 0;
	m_bBGMPlay		= TRUE;



}


/******************************************************************************************************************
���� Procedure�� ����.
ȣ��Ǹ� �����������ʹ� Procedure�� �ٲ��.
*******************************************************************************************************************/
VOID CLoginProcess::SetNextProc()
{
	DeleteProc();
	g_xClientSocket.m_pxDefProc = g_xMainWnd.m_pxDefProcess = &g_xChrSelProc;
	g_xChrSelProc.Load();
	g_bProcState = _CHAR_SEL_PROC;

	SndObjStop(m_stOpenSnd);
	SndObjDestroy(m_stOpenSnd);
}


//-----------------------------------------------------------------------------------------------------------------
// ȭ�� Render���� �Լ�.
//-----------------------------------------------------------------------------------------------------------------
/******************************************************************************************************************
3D ����ǿ� �ؽ��縦 �÷��� �׸���.
lpDevice   : �ʱ� DX3D���ý� ���� 3D��ġDevice.
pvTrans    : ������ǥ�� ������ ������ ������.(�ȼ���ǥ)
pvScale    : �̹����� ũ�⸦ ������ ������ ������.
pmtrl	   : ����� Matrial�� ������.
lpddsTextr : �ؽ���� ���� Surface.
bBlendType : ȭ�鿡 ������ ����.
*******************************************************************************************************************/
HRESULT CLoginProcess::DrawBillBoard(LPDIRECT3DDEVICE7 lpDevice, D3DVECTOR* pvTrans, D3DVECTOR* pvScale, /*D3DVECTOR vRot, */D3DMATERIAL7* pmtrl, /*FLOAT fRotRad, */LPDIRECTDRAWSURFACE7 lpddsTextr, BYTE bBlendType)
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
Procedure�� ���η���.
*******************************************************************************************************************/
VOID CLoginProcess::RenderScene(INT nLoopTime)
{	
	Clear(RGB(0, 0, 0));

	RenderBackground(nLoopTime);

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

	// ���ӽ� ���÷��� - Movie
	// by eriastoa 2006.05.25
	if( m_bProcState == 0 ) g_xMainWnd.PutsHan( NULL, 120, 350, RGB( 255, 255, 255 ), RGB( 0, 0, 0 ), g_xMsg.GetMsg( 126 ) );


	switch ( m_bProcState )
	{
		case _LOGINPROC_LOGIN:
		{
			RenderLogin();
			break;
		}
		case _LOGINPROC_SVRSEL:
		{
			RenderSvrSel();
			break;
		}
		case _LOGINPROC_FADE:
		{
			RenderFade(nLoopTime);
			break;
		}
	}

	ShowNotice(nLoopTime);

	m_xMsgBox.RenderMsgBox(m_ptMousePos);

	//Ŭ���̾�Ʈ�޽���(���ʻ��).
	//m_xClientSysMsg.ShowSysMsg(nLoopTime, 30, 340);
}


/******************************************************************************************************************
����� �׸���.
����� Logo Avi -> Login Avi -> Still Image �� ������ �׷�����.
*******************************************************************************************************************/
VOID CLoginProcess::RenderBackground(INT nLoopTime)
{
	switch ( m_bBackState )
	{
		case _LOGINBACK_LOGO:
		{
			g_xMainWnd.m_bIsActiveChanged = FALSE;

			if ( !m_xAvi.Draw( g_xMainWnd.GetBackBuffer() ) )
			{
				m_bProcState = _LOGINPROC_LOGIN;
				m_bBackState = _LOGINBACK_LOGIN;

				m_bLoginInputState = _LOGININPUT_ID;

				SetEditFocus();

/*				m_xAvi.Create(g_xMainWnd.GetDirectDraw(), g_SoundManager.mSound_lpds, ".\\Data\\ei_login.dat", FALSE);
				m_xAvi.SetDestRect(0, 60, 640, 420);
				m_xAvi.Start();*/
				
				m_bBackState = _LOGINBACK_STILL;

				Sleep(100);

				m_xAvi.Release();
			}
			break;
		}
		case _LOGINBACK_LOGIN:
		{
			if ( !m_xAvi.Draw(g_xMainWnd.GetBackBuffer()) )
			{		
				m_bBackState = _LOGINBACK_STILL;
				Sleep(100);
				m_xAvi.Release();
			}
			break;
		}
		case _LOGINBACK_STILL:
		{
			// 1.2���Ŀ� BGM Play.
			if ( m_bBGMPlay )
			{
				m_dwBGMPlayTime += nLoopTime;

				if ( m_dwBGMPlayTime > 1200 )
				{
					SndObjPlay(0, 0, m_stOpenSnd, DSBPLAY_LOOPING);
					m_bBGMPlay     = FALSE;
					m_dwBGMPlayTime = 0;
				}
			}

			if ( m_xImageLogin.NewSetIndex(m_nBackIdx) )
//			if ( m_xImageLogin.NewSetIndex(0) )
			{
				g_xMainWnd.DrawWithImageForComp(0, 0, m_xImageLogin.m_lpstNewCurrWilImageInfo->shWidth, m_xImageLogin.m_lpstNewCurrWilImageInfo->shHeight,
												(WORD*)(m_xImageLogin.m_pbCurrImage));
			}
			break;
		}	
	}
}


/******************************************************************************************************************
Login ȭ�鿡 �ʿ��� �κ��� �׷��ش�.
����� ID, PW, ��ư, ���.
*******************************************************************************************************************/
VOID CLoginProcess::RenderLogin()
{
	D3DVECTOR	 vecTrans(0.0f, 372.0f, 0);
	D3DVECTOR	 vecScale(640.0f, 48.0f, 1);

	D3DMATERIAL7 mtrl;
	D3DUtil_InitMaterial(mtrl, (FLOAT)50/255.0f, (FLOAT)50/255.0f, (FLOAT)60/255.0f);
	mtrl.diffuse.a = 100.0f/255.0f;

	DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
	RECT rc = {0, 372, 640, 420};
	g_xMainWnd.DrawWithGDI(&rc, NULL, RGB(100, 100, 100), 1);

	for ( INT nCnt = 0; nCnt < _MAX_LOGIN_BTN; nCnt++ )
	{
		m_xLoginBtn[nCnt].ShowGameBtn();
	}

	// �����ϱ� ��ư�̹����� ���°����...
	RECT* prcBtn = &m_xLoginBtn[_LOGIN_BTN_CONN].m_rcBtn;
	if ( PtInRect(prcBtn, m_ptMousePos) )
	{
		vecTrans = D3DVECTOR((FLOAT)prcBtn->left, (FLOAT)prcBtn->top, 0);
		vecScale = D3DVECTOR((FLOAT)prcBtn->right-prcBtn->left, (FLOAT)prcBtn->bottom-prcBtn->top, 1);

		D3DUtil_InitMaterial(mtrl, (FLOAT)150/255.0f, (FLOAT)100/255.0f, (FLOAT)50/255.0f);
		mtrl.diffuse.a = 50.0f/255.0f;
		DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

		g_xMainWnd.DrawWithGDI(prcBtn, NULL, RGB(200, 150, 100), 1);
	}


	if ( m_xImageLogin.NewSetIndex(_LOGINIMG_IDPW) )
	{
		g_xMainWnd.DrawWithImageForComp(100, 436, m_xImageLogin.m_lpstNewCurrWilImageInfo->shWidth, m_xImageLogin.m_lpstNewCurrWilImageInfo->shHeight,
										(WORD*)(m_xImageLogin.m_pbCurrImage));
	}

	// ���ڿ��� ���̰� ĭ(100)���� ũ�� �����ϰ� �߶� �����ش�.
	CHAR pszTmp[MAX_PATH];
	INT  nLen = 0; 
	ZeroMemory(pszTmp, MAX_PATH);

	if ( m_bLoginInputState != _LOGININPUT_PW )
	{
		nLen = strlen(m_pszPW);
		memset(pszTmp, '*', nLen);

		SIZE sizeLen = g_xMainWnd.GetStrLength(NULL, NULL, pszTmp);
		if ( sizeLen.cx > 100 )
		{
			for ( INT nCnt = nLen; nCnt > 0; nCnt-- )
			{
				pszTmp[nCnt] = '\0';

				sizeLen = g_xMainWnd.GetStrLength(NULL, NULL, pszTmp);

				if ( sizeLen.cx < 100 )
				{
					break;
				}
			}
		}
		g_xMainWnd.PutsHan(NULL, 326, 440, RGB(255, 255, 255), RGB(0,0,0), pszTmp);
	}

	if ( m_bLoginInputState != _LOGININPUT_ID )
	{
		nLen = strlen(m_pszID);
		strcpy(pszTmp, m_pszID);

		// ���ڿ��� ���̰� ĭ(100)���� ũ�� �����ϰ� �ڸ���.
		SIZE sizeLen = g_xMainWnd.GetStrLength(NULL, NULL, pszTmp);
		if ( sizeLen.cx > 100 )
		{
			for ( INT nCnt = nLen; nCnt > 0; nCnt-- )
			{
				pszTmp[nCnt] = '\0';

				sizeLen = g_xMainWnd.GetStrLength(NULL, NULL, pszTmp);

				if ( sizeLen.cx < 100 )
				{
					break;
				}
			}
		}
		g_xMainWnd.PutsHan(NULL, 128, 440, RGB(255, 255, 255), RGB(0,0,0), pszTmp);
	}

//	DrawEffect(5, 30, 440);

	SetRect(&rc, 580, 0, 640, 60);
	g_xMainWnd.DrawWithGDI(&rc, NULL, RGB(255, 200,  0), 3);
	g_xMainWnd.PutsHan(NULL, 598, 17, RGB(10, 10, 10), RGB(0, 0, 0), g_xMsg.GetMsg(100), g_xMainWnd.CreateGameFont("�ü�ü", 9, 0));
	g_xMainWnd.PutsHan(NULL, 592, 33, RGB(10, 10, 10), RGB(0, 0, 0), g_xMsg.GetMsg(101), g_xMainWnd.CreateGameFont("�ü�ü", 9, 0));





	

}


/******************************************************************************************************************
���� ���ÿ� �ʿ��� �κ��� �ο��ش�.
�����̸��� ���ÿ��ε�.
*******************************************************************************************************************/
VOID CLoginProcess::RenderSvrSel()
{
	INT			 nSvrListWidth  = m_rcSvrListRgn.right-m_rcSvrListRgn.left;
	INT			 nSvrListHeight = m_rcSvrListRgn.bottom-m_rcSvrListRgn.top;
	D3DVECTOR	 vecTrans((FLOAT)m_rcSvrListRgn.left, (FLOAT)m_rcSvrListRgn.top, 0);
	D3DVECTOR	 vecScale((FLOAT)nSvrListWidth, (FLOAT)nSvrListHeight, 1);

	D3DMATERIAL7 mtrl;
	D3DUtil_InitMaterial(mtrl, (FLOAT)100/255.0f, (FLOAT)100/255.0f, (FLOAT)100/255.0f);
	mtrl.diffuse.a = 120.0f/255.0f;

	DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
	g_xMainWnd.DrawWithGDI(&m_rcSvrListRgn, NULL, RGB(150, 150, 150), 1);

	INT						nCnt;
	CListNode < SVRLIST >	*pNode;
	LPSVRLIST				pstSvrList = NULL;

	for ( pNode = m_stSvrList.GetHead(), nCnt = 0; pNode; pNode = pNode->GetNext(), nCnt++ )
	{
		pstSvrList = pNode->GetData();

		if ( pstSvrList )
		{
			if ( m_nClickedSvr == -1 )
			{
				if ( PtInRect(&pstSvrList->rcRgn, m_ptMousePos) )
				{
					nSvrListWidth  = pstSvrList->rcRgn.right-pstSvrList->rcRgn.left;
					nSvrListHeight = pstSvrList->rcRgn.bottom-pstSvrList->rcRgn.top;
					vecTrans = D3DVECTOR((FLOAT)pstSvrList->rcRgn.left, (FLOAT)pstSvrList->rcRgn.top, 0);
					vecScale = D3DVECTOR((FLOAT)nSvrListWidth, (FLOAT)nSvrListHeight, 1);

					D3DUtil_InitMaterial(mtrl, (FLOAT)100/255.0f, (FLOAT)100/255.0f, (FLOAT)100/255.0f);
					mtrl.diffuse.a = 50.0f/255.0f;
					DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
					g_xMainWnd.PutsHan(NULL, pstSvrList->rcRgn.left+_SVRLIST_GAP_X, pstSvrList->rcRgn.top+_SVRLIST_GAP_Y/2, RGB(0, 0, 255), RGB(0, 0, 0), pstSvrList->pszCaption);

					g_xMainWnd.DrawWithGDI(&pstSvrList->rcRgn, NULL, RGB(100, 100, 200), 1);
				}
				else
				{
					g_xMainWnd.PutsHan(NULL, pstSvrList->rcRgn.left+_SVRLIST_GAP_X, pstSvrList->rcRgn.top+_SVRLIST_GAP_Y/2, RGB(30, 30, 30), RGB(0, 0, 0), pstSvrList->pszCaption);
				}
			}
			else
			{
				if ( m_nClickedSvr == nCnt )
				{
					nSvrListWidth  = pstSvrList->rcRgn.right-pstSvrList->rcRgn.left;
					nSvrListHeight = pstSvrList->rcRgn.bottom-pstSvrList->rcRgn.top;
					vecTrans = D3DVECTOR((FLOAT)pstSvrList->rcRgn.left, (FLOAT)pstSvrList->rcRgn.top, 0);
					vecScale = D3DVECTOR((FLOAT)nSvrListWidth, (FLOAT)nSvrListHeight, 1);

					D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)100/255.0f, (FLOAT)100/255.0f);
					mtrl.diffuse.a = 50.0f/255.0f;
					DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);
					g_xMainWnd.PutsHan(NULL, pstSvrList->rcRgn.left+_SVRLIST_GAP_X, pstSvrList->rcRgn.top+_SVRLIST_GAP_Y/2, RGB(255, 100, 100), RGB(0, 0, 0), pstSvrList->pszCaption);

					g_xMainWnd.DrawWithGDI(&pstSvrList->rcRgn, NULL, RGB(255, 100, 100), 1);
				}
				else
				{
					g_xMainWnd.PutsHan(NULL, pstSvrList->rcRgn.left+_SVRLIST_GAP_X, pstSvrList->rcRgn.top+_SVRLIST_GAP_Y/2, RGB(30, 30, 30), RGB(0, 0, 0), pstSvrList->pszCaption);
				}
			}
		}
	}
}


/******************************************************************************************************************
������ ���õǾ����� ���� Procedure�� ȭ���� ��ȯ�ϱ����� ������ο����� �κ��� ó���Ѵ�.
*******************************************************************************************************************/
VOID CLoginProcess::RenderFade(INT nLoopTime)
{
	m_nFadeProcTime += nLoopTime;

	if ( m_nFadeProcTime < 2000 )
	{
		FLOAT		 fRate = 255.0f - (FLOAT)((FLOAT)m_nFadeProcTime*255.0f)/2000;

		D3DVECTOR	 vecTrans(0.0f, 0.0f, 0);
		D3DVECTOR	 vecScale(640.0f, 480.0f, 1);

		D3DMATERIAL7 mtrl;
		D3DUtil_InitMaterial(mtrl, fRate/255.0f, fRate/255.0f, fRate/255.0f);
		mtrl.diffuse.a = 100/255.0f;

		DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL, 6);
	}
	else
	{
		Clear(RGB(0, 0, 0));
		SetNextProc();
	}	
}


//-----------------------------------------------------------------------------------------------------------------
// �α��� �κ� �Լ�.
//-----------------------------------------------------------------------------------------------------------------
/******************************************************************************************************************
�α��� ȭ�鿡�� ID, PW�� ��ġ�� ���� Edit Box�� �Ӽ��� ���Ѵ�.
*******************************************************************************************************************/
VOID CLoginProcess::SetEditFocus()
{
	if ( m_bLoginInputState == _LOGININPUT_ID )
	{
		GetWindowText(g_xChatEditBox.GetSafehWnd(), m_pszPW, MAX_PATH);
		SetWindowText(g_xChatEditBox.GetSafehWnd(), m_pszID);

		MoveWindow(g_xChatEditBox.GetSafehWnd(), 
				   g_xMainWnd.m_rcWindow.left+m_rcEditID.left, g_xMainWnd.m_rcWindow.top+m_rcEditID.top, m_rcEditID.right-m_rcEditID.left, m_rcEditID.bottom-m_rcEditID.top, TRUE);

		SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETPASSWORDCHAR, NULL, 0);
	}
	else
	{
		GetWindowText(g_xChatEditBox.GetSafehWnd(), m_pszID, MAX_PATH);
		SetWindowText(g_xChatEditBox.GetSafehWnd(), m_pszPW);

		MoveWindow(g_xChatEditBox.GetSafehWnd(), 
				   g_xMainWnd.m_rcWindow.left+m_rcEditPW.left, g_xMainWnd.m_rcWindow.top+m_rcEditPW.top, m_rcEditPW.right-m_rcEditPW.left, m_rcEditPW.bottom-m_rcEditPW.top, TRUE);

		SendMessage(g_xChatEditBox.GetSafehWnd(), EM_SETPASSWORDCHAR, (WPARAM)'*', 0);
	}
	if ( g_xMainWnd.m_bIsWindowActive )
	{
		g_xChatEditBox.SetSelectAll();
		SetFocus(g_xChatEditBox.GetSafehWnd());
		ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);
	}
}


//-----------------------------------------------------------------------------------------------------------------
// �������� �κ� �Լ�.
//-----------------------------------------------------------------------------------------------------------------
/******************************************************************************************************************
�������ù�ư�� ���� ������ Mir3.Ini���Ϸ� �����Է�.
*******************************************************************************************************************/
VOID CLoginProcess::SetSvrBtn()
{
	CHAR	pszFullPath[MAX_PATH];
	CHAR	pszTemp[MAX_PATH];
	INT		nSvrCount;

	GetCurrentDirectory(MAX_PATH, pszFullPath);
	strcat(pszFullPath+strlen(pszFullPath), "\\\0");
 	strcat(pszFullPath, _MIR3EI_INI_FILE_NAME);

	GetPrivateProfileString(_MIR3EI_INI_SECTION, _LOGIN_SERVER_NAME, _LOGIN_GATE_SERVER_IP, m_pszSvrIP, 16, pszFullPath);

	m_nSvrPort = GetPrivateProfileInt(_MIR3EI_INI_SECTION, _LOGIN_SERVER_PORT, _LOGIN_SERVER_PORT_DATA, pszFullPath);
	nSvrCount  = GetPrivateProfileInt(_MIR3EI_SRV_SECTION, _SERVER_COUNT, 0, pszFullPath);							

	INT	 nCnt;
	SIZE sizeLenSave  = {0, 0};
	SIZE sizeLenCurr  = {0, 0};
	m_stSvrList.ClearAll();

	for ( nCnt = 0; nCnt < nSvrCount; nCnt++ )
	{
		LPSVRLIST pstSvrList = new SVRLIST;

		if ( pstSvrList )
		{
			ZeroMemory(pstSvrList, sizeof(SVRLIST));

			sprintf(pszTemp, "%s%d%s", "server", nCnt+1, "caption");
			GetPrivateProfileString(_MIR3EI_SRV_SECTION, (LPCTSTR)pszTemp, NULL, pstSvrList->pszCaption, MAX_PATH, pszFullPath);

			sprintf(pszTemp, "%s%d%s", "server", nCnt+1, "name");
			GetPrivateProfileString(_MIR3EI_SRV_SECTION, (LPCTSTR)pszTemp, NULL, pstSvrList->pszName, MAX_PATH, pszFullPath);

			sizeLenCurr = g_xMainWnd.GetStrLength(NULL, NULL, pstSvrList->pszCaption);

			if ( sizeLenCurr.cx > sizeLenSave.cx )
			{
				sizeLenSave = sizeLenCurr;
			}

			m_stSvrList.Insert(pstSvrList);
		}
	}

	INT nListCnt = m_stSvrList.GetCount();

	SetRect(&m_rcSvrListRgn, _SVRLIST_SX-_SVRLIST_GAP_X, _SVRLIST_SY-_SVRLIST_GAP_Y, _SVRLIST_SX+sizeLenSave.cx+_SVRLIST_GAP_X, _SVRLIST_SY+(sizeLenSave.cy+_SVRLIST_GAP_Y)*nListCnt);

	CListNode < SVRLIST >	*pNode;
	LPSVRLIST				pstSvrList = NULL;

	for ( pNode = m_stSvrList.GetHead(), nCnt = 0; pNode; pNode = pNode->GetNext(), nCnt++ )
	{
		pstSvrList = pNode->GetData();

		if ( pstSvrList )
		{
			SetRect(&pstSvrList->rcRgn, _SVRLIST_SX-_SVRLIST_GAP_X, _SVRLIST_SY+(sizeLenSave.cy+_SVRLIST_GAP_Y)*nCnt-_SVRLIST_GAP_Y/2,
				    _SVRLIST_SX+sizeLenSave.cx+_SVRLIST_GAP_X, _SVRLIST_SY+(sizeLenSave.cy+_SVRLIST_GAP_Y)*(nCnt+1)-_SVRLIST_GAP_Y/2);
		}
	}
}


/******************************************************************************************************************
���콺��ǥ�� �������ù�ư�� ����Ʈ��ȣ�� ���´�.
*******************************************************************************************************************/
INT CLoginProcess::GetSvrNum(POINT ptMouse)
{
	INT						nCnt;
	CListNode < SVRLIST >	*pNode;
	LPSVRLIST				pstSvrList = NULL;

	for ( pNode = m_stSvrList.GetHead(), nCnt = 0; pNode; pNode = pNode->GetNext(), nCnt++ )
	{
		pstSvrList = pNode->GetData();

		if ( pstSvrList )
		{
			if ( PtInRect(&pstSvrList->rcRgn, ptMouse) )
			{
				return nCnt;
			}
		}
	}

	return -1;
}


/******************************************************************************************************************
����Ʈ��ȣ�� �������ù�ư�� ������ ���´�.
*******************************************************************************************************************/
LPSVRLIST CLoginProcess::GetSvrList(INT nNum)
{
	INT						nCnt;
	CListNode < SVRLIST >	*pNode;
	LPSVRLIST				pstSvrList = NULL;

	for ( pNode = m_stSvrList.GetHead(), nCnt = 0; pNode; pNode = pNode->GetNext(), nCnt++ )
	{
		pstSvrList = pNode->GetData();

		if ( pstSvrList )
		{
			if ( nNum == nCnt )
			{
				return pstSvrList;
			}
		}
	}

	return NULL;
}










//-----------------------------------------------------------------------------------------------------------------
// ��Ŷ���� �Լ�����.
//-----------------------------------------------------------------------------------------------------------------
/******************************************************************************************************************
�α伭���� ���Ӽ���.
*******************************************************************************************************************/
VOID CLoginProcess::OnConnectToServer()
{
}


/******************************************************************************************************************
dll Error Msg ���Ϸκ��� ���������� ���´�.
*******************************************************************************************************************/
/*VOID CLoginProcess::GetErrorMsg(INT nMsg, CHAR* pszMsg)
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
��Ŷ�� �ڸ���.
*******************************************************************************************************************/
CHAR* CLoginProcess::OnMessageReceive(CHAR* pszBuf, INT nLen)
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
#...!�� �߶��� ��Ŷ�� �м��Ѵ�.
*******************************************************************************************************************/
VOID CLoginProcess::OnSocketMessageReceive(CHAR* pszMsg)
{
	INT					nMsgNum;

	_TDEFAULTMESSAGE	tdm;

	fnDecodeMessage(&tdm, pszMsg);

	switch ( tdm.wIdent )
	{
		case SM_ID_NOTFOUND:
		{
			m_xMsgBox.CreateMsgBox(&m_xImageInter, LOGIN_WNDID_INPUT, _OK, g_xMsg.GetMsg(112), FALSE, 140, 110);
			break;
		}
		case SM_PASSWD_FAIL:
		{ 
			switch ( tdm.nRecog )
			{ 
			case -1:
				nMsgNum = 113;	// -1	�н����� Ʋ��
				break;
			case -2:
				nMsgNum = 114;	// �н����带 5ȸ ���� �� 10���� ������ �ʾ���
				break;
			case -3:
				nMsgNum = 116;	// ���� ���̵� ����
				break;
			case -5:
				nMsgNum = 117;	// ���̵� ������
				break;
			case -6:
				nMsgNum = 112;	// ���̵� ����
				break;
			case -7:			
				nMsgNum = 118;	// Mir2 ID�� Ȩ���������� �Ǹ��� �ؾ߸��մϴ�.
				return;
			default:
				nMsgNum = 116;	// ������ �˼� ����.
				break;
			}
			m_xMsgBox.CreateMsgBox(&m_xImageInter, LOGIN_WNDID_INPUT, _OK, g_xMsg.GetMsg(nMsgNum), FALSE, 140, 110);
			break;
		}
		case SM_CERTIFICATION_FAIL:
		{
			m_xMsgBox.CreateMsgBox(&m_xImageInter, LOGIN_WNDID_INPUT, _OK, g_xMsg.GetMsg(119), FALSE, 140, 110);
			break;
		}
		case SM_PASSOK_WRONGSSN:
		{
			INT nID = LOGIN_WNDID_GAMEOUT;

#ifdef _DEBUG
			nID = LOGIN_WNDID_INPUT;
#endif

			switch ( tdm.nRecog )
			{
				// �ùٸ��� �ʴ� �ֹε�Ϲ�ȣ �Դϴ�.
				case 1:
				{
					m_xMsgBox.CreateMsgBox(&m_xImageInter, nID, _OK, g_xMsg.GetMsg(124), FALSE, 140, 110);
					break;
				}
				// �� 15�� �̸��� ����ڴ� �̿��Ҽ� �����ϴ�. 
				case 2:
				{
					m_xMsgBox.CreateMsgBox(&m_xImageInter, nID, _OK, g_xMsg.GetMsg(125), FALSE, 140, 110);
					break;
				}
				default:
				{
					m_xMsgBox.CreateMsgBox(&m_xImageInter, nID, _OK, g_xMsg.GetMsg(122), FALSE, 140, 110);
					break;
				}
			}
			break;
		}
		case SM_NOT_IN_SERVICE:
		{
			m_xMsgBox.CreateMsgBox(&m_xImageInter, LOGIN_WNDID_GAMEOUT, _OK, g_xMsg.GetMsg(123), FALSE, 140, 110);
			break;
		}
		case SM_PASSOK_SELECTSERVER:
		{
			ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_HIDE);
			SetFocus(g_xMainWnd.GetSafehWnd());

			strcpy(g_szUserID, m_pszID);

			m_bProcState = _LOGINPROC_SVRSEL;

			int m_nAvailIDDay  = tdm.nRecog;
			int m_nAvailIPDay  = tdm.wParam;
			int m_nAvailIPHour = tdm.wTag;
			int m_nAvailIDHour = tdm.wSeries;

			CHAR pszTmpMsg[MAX_PATH];

			if ( m_nAvailIDDay > 0 )
			{
				g_nPaySystem = _KIND_PRIVATE_FIXED_MONEY;
				//����������
				if ( m_nAvailIDDay == 1 )
				{
					m_xMsgBox.CreateMsgBox(&m_xImageInter, LOGIN_WNDID_INPUT, _OK, g_xMsg.GetMsg(102), FALSE, 140, 110);
				}
				else if ( m_nAvailIDDay <= 3 )
				{
					sprintf(pszTmpMsg, g_xMsg.GetMsg(103), m_nAvailIDDay);
					m_xMsgBox.CreateMsgBox(&m_xImageInter, LOGIN_WNDID_INPUT, _OK, pszTmpMsg, FALSE, 140, 110);
				}
			}
			else if ( m_nAvailIPDay > 0 )
			{
				g_nPaySystem = _KIND_IP_FIXED_MONEY;
				//IP������
				if ( m_nAvailIPDay == 1 )
				{
					m_xMsgBox.CreateMsgBox(&m_xImageInter, LOGIN_WNDID_INPUT, _OK, g_xMsg.GetMsg(105), FALSE, 140, 110);
				}
				else if ( m_nAvailIPDay <= 3 )
				{
					sprintf(pszTmpMsg, g_xMsg.GetMsg(104), m_nAvailIPDay);
					m_xMsgBox.CreateMsgBox(&m_xImageInter, LOGIN_WNDID_INPUT, _OK, pszTmpMsg, FALSE, 140, 110);						
				}
			}
			else if ( m_nAvailIPHour > 0 )
			{
				g_nPaySystem = _KIND_IP_FIXED_TIME;
				//IP������
				if ( m_nAvailIPHour <= 100 )
				{
					sprintf(pszTmpMsg, g_xMsg.GetMsg(106), m_nAvailIPHour);
					m_xMsgBox.CreateMsgBox(&m_xImageInter, LOGIN_WNDID_INPUT, _OK, pszTmpMsg, FALSE, 140, 110);						
				}
			}
			else if ( m_nAvailIDHour > 0 )
			{
				g_nPaySystem = _KIND_PRIVATE_FIXED_TIME;
				//����������
				sprintf(pszTmpMsg, g_xMsg.GetMsg(107), m_nAvailIDHour);
				m_xMsgBox.CreateMsgBox(&m_xImageInter, LOGIN_WNDID_INPUT, _OK, pszTmpMsg, FALSE, 140, 110);						
			}
/*			else
			{
				sprintf(pszTmpMsg, "IDDAY:%d IPDAY:%d IDHOUR:%d IPHOUR:%d", m_nAvailIDDay, m_nAvailIPDay, m_nAvailIDHour, m_nAvailIPHour);
				m_xMsgBox.CreateMsgBox(&m_xImageInter, LOGIN_WNDID_INPUT, _OK, pszTmpMsg, FALSE, 140, 110);						
			}*/

//			sprintf(pszTmpMsg, "IDDAY:[%d]  IPDAY:[%d]  IDHOUR:[%d]  IPHOUR:[%d]", m_nAvailIDDay, m_nAvailIPDay, m_nAvailIDHour, m_nAvailIPHour);
//			m_xClientSysMsg.AddSysMsg(pszTmpMsg);

			break;
		}
		case SM_CHGPASSWD_SUCCESS:
		{
			break;
		}
		case SM_CHGPASSWD_FAIL:
		{
			break;	
		}
		case SM_SELECTSERVER_OK:
		{
			CHAR  pszDecodeMsg[256];
			CHAR* pszIP		= NULL;
			CHAR* pszPort	= NULL;
			CHAR* pszIdenty	= NULL;

			ZeroMemory(pszDecodeMsg, sizeof(pszDecodeMsg));
			fnDecode6BitBuf((pszMsg + _DEFBLOCKSIZE), pszDecodeMsg, sizeof(pszDecodeMsg));

			pszIP = pszDecodeMsg;

			if ( pszPort = strchr(pszIP, '/') )
			{
				*pszPort = '\0';
				pszPort++;

				if ( pszIdenty = strchr(pszPort, '/') )
				{
					*pszIdenty = '\0';
					pszIdenty++;

					strcpy(g_szPreServerIP, g_szServerIP);
					g_nPreServerPort = g_nServerPort;

					strcpy(g_szServerIP, pszDecodeMsg);
					g_nServerPort = atoi(pszPort);
					g_nCertifyCode = tdm.nRecog;

					m_bProcState = _LOGINPROC_FADE;
				}
			}
			break;
		}
		case SM_OUTOFCONNECTION:
		{
			m_xMsgBox.CreateMsgBox(&m_xImageInter, LOGIN_WNDID_INPUT, _OK, g_xMsg.GetMsg(121), FALSE, 140, 110);
			break;
		}
	}
}










//-----------------------------------------------------------------------------------------------------------------
// ������ �޽��� ���� �Լ�����.
//-----------------------------------------------------------------------------------------------------------------
/******************************************************************************************************************
�޽��� Procedure.
*******************************************************************************************************************/
LRESULT CLoginProcess::DefMainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
		case WM_SYSKEYDOWN:
#ifndef _DEBUG
			return 0L;
#endif
			break;
		case WM_KEYDOWN:
			OnKeyDown(wParam, lParam);
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
	return CWHDefProcess::DefMainWndProc(hWnd, uMsg, wParam, lParam);
}


/******************************************************************************************************************
���α׷� �����.
*******************************************************************************************************************/
LRESULT CLoginProcess::OnDestroy(WPARAM wParam, LPARAM lParam)
{
//	DeleteProc();
	DestroyFindHack();
	WSACleanup();
//	ReleaseFontList();
	return 0L;
}


HRESULT	CLoginProcess::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	if ( m_xMsgBox.OnKeyDown(wParam, lParam) )
	{
		return 0L;
	}

	switch ( wParam )
	{
		case VK_TAB:
		{
			if ( m_bProcState == _LOGINPROC_LOGIN )
			{
				if ( m_bLoginInputState == _LOGININPUT_ID )
				{
					m_bLoginInputState = _LOGININPUT_PW;
					SetEditFocus();
				}
				else
				{
					m_bLoginInputState = _LOGININPUT_ID;
					SetEditFocus();
				}
			}
			break;
		}
		case VK_RETURN:
		{
			if ( m_bProcState == _LOGINPROC_LOGIN )
			{
				// TABŰ�� �����ϴ�.
				if ( m_bLoginInputState == _LOGININPUT_ID )
				{
					m_bLoginInputState = _LOGININPUT_PW;
					SetEditFocus();
				}
				else
				{
					m_bLoginInputState = _LOGININPUT_ID;
					SetEditFocus();
				}

				if ( m_bLoginInputState == _LOGININPUT_ID && m_pszID[0] != '\0' && m_pszPW[0] != '\0' )
				{
					// ID�� PW�� Ʋ���� ��쿡 PW�Է»��·� �����Ѵ�.
					m_bLoginInputState = _LOGININPUT_SETTED;

					// �����ϱ� ��ư�� �����Ͱ� ����.
					g_xClientSocket.OnLogin(m_pszID, m_pszPW);
					SetFocus(g_xMainWnd.GetSafehWnd());
					ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_HIDE);
					return 0L;
				}
			}
			break;
		}

// ���� ������ Ű����� ����
// by eriastoa 2006.04.04
#ifdef _TEST_SERVER
		case VK_F1:
		case VK_F2:
		case VK_F3:
		case VK_F4:
			if( m_bProcState == _LOGINPROC_SVRSEL )
			{
				if( wParam == VK_F1 )			m_nClickedSvr = 0;
				else if( wParam == VK_F2 )		m_nClickedSvr = 1;
				else if( wParam == VK_F3 )		m_nClickedSvr = 2;
				else if( wParam == VK_F4 )		m_nClickedSvr = 3;
				
				LPSVRLIST pstSvrList = GetSvrList(m_nClickedSvr);
				if ( pstSvrList ) 
				{
					g_xClientSocket.OnSelectServer(pstSvrList->pszName);
					strcpy(g_szServerName, pstSvrList->pszName);
				}
				m_nClickedSvr = -1;
			}
			break;
#endif
	}

	return 0L;
}


LRESULT	CLoginProcess::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	m_ptMousePos.x = LOWORD(lParam);
	m_ptMousePos.y = HIWORD(lParam);

	if ( m_xMsgBox.OnLButtonDown(m_ptMousePos) )
	{
		return 0L;
	}

	if ( m_bProcState == _LOGINPROC_LOGIN )
	{
		if ( PtInRect(&m_rcEditID, m_ptMousePos) )
		{
			m_bLoginInputState = _LOGININPUT_ID;
			SetEditFocus();
		}
		else if ( PtInRect(&m_rcEditPW, m_ptMousePos) )
		{
			m_bLoginInputState = _LOGININPUT_PW;
			SetEditFocus();
		}
		else
		{
			m_xLoginBtn[_LOGIN_BTN_CONN] .OnLButtonDown(m_ptMousePos);
			m_xLoginBtn[_LOGIN_BTN_REG]  .OnLButtonDown(m_ptMousePos);
			m_xLoginBtn[_LOGIN_BTN_CHGPW].OnLButtonDown(m_ptMousePos);
			m_xLoginBtn[_LOGIN_BTN_QUIT] .OnLButtonDown(m_ptMousePos);
		}
	}
	else if ( m_bProcState == _LOGINPROC_SVRSEL )
	{
		m_nClickedSvr = GetSvrNum(m_ptMousePos);
	}

	return 0L;
}


LRESULT	CLoginProcess::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	m_ptMousePos.x = LOWORD(lParam);
	m_ptMousePos.y = HIWORD(lParam);

	if ( m_xMsgBox.OnLButtonUp(m_ptMousePos) )
	{
		return 0L;
	}

	if ( m_bProcState == _LOGINPROC_LOGIN )
	{
		CHAR	pszFullPath[MAX_PATH];
		CHAR	pszURL[MAX_PATH];

		ZeroMemory(pszFullPath, MAX_PATH);
		ZeroMemory(pszURL, MAX_PATH);

		GetCurrentDirectory(MAX_PATH, pszFullPath);
		strcat(pszFullPath + strlen(pszFullPath), "\\\0");
 		strcat(pszFullPath, _MIR3EI_INI_FILE_NAME);

		if ( m_xLoginBtn[_LOGIN_BTN_CONN].OnLButtonUp(m_ptMousePos) )
		{
			if ( m_bLoginInputState == _LOGININPUT_ID )
			{
				m_bLoginInputState = _LOGININPUT_PW;
				SetEditFocus();
			}
			else
			{
				m_bLoginInputState = _LOGININPUT_ID;
				SetEditFocus();
			}

			g_xClientSocket.OnLogin(m_pszID, m_pszPW);
			SetFocus(g_xMainWnd.GetSafehWnd());
			ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_HIDE);
		}
		else if (m_xLoginBtn[_LOGIN_BTN_REG].OnLButtonUp(m_ptMousePos) )
		{
			GetPrivateProfileString(_MIR3EI_INI_SECTION, _URL_ACCOUNT, _URL_NEW_ACCOUNT, pszURL, MAX_PATH, pszFullPath);
			ShellExecute(NULL, NULL, pszURL, NULL, NULL, SW_SHOWNORMAL);

			SendMessage(g_xMainWnd.GetSafehWnd(), WM_DESTROY, NULL, NULL);
		}
		else if ( m_xLoginBtn[_LOGIN_BTN_CHGPW].OnLButtonUp(m_ptMousePos) )
		{
			GetPrivateProfileString(_MIR3EI_INI_SECTION, _URL_CHANGEPWD, _URL_CHANGE_PASSWORD, pszURL, MAX_PATH, pszFullPath);
			ShellExecute(NULL, NULL, pszURL, NULL, NULL, SW_SHOWNORMAL);

			SendMessage(g_xMainWnd.GetSafehWnd(), WM_DESTROY, NULL, NULL);
		}
		else if ( m_xLoginBtn[_LOGIN_BTN_QUIT].OnLButtonUp(m_ptMousePos) )
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
	}
	else if ( m_bProcState == _LOGINPROC_SVRSEL )
	{
		if ( m_nClickedSvr != -1 )
		{
			INT nClickedSvr = GetSvrNum(m_ptMousePos);

			if ( m_nClickedSvr == nClickedSvr )
			{
				LPSVRLIST pstSvrList = GetSvrList(m_nClickedSvr);

				if ( pstSvrList ) 
				{
					g_xClientSocket.OnSelectServer(pstSvrList->pszName);
					strcpy(g_szServerName, pstSvrList->pszName);
				}
			}

			m_nClickedSvr = -1;
		}
	}

	return 0L;
}


LRESULT	CLoginProcess::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	m_ptMousePos.x = LOWORD(lParam);
	m_ptMousePos.y = HIWORD(lParam);

	m_xMsgBox.OnMouseMove(m_ptMousePos);

	if ( m_bProcState == _LOGINPROC_LOGIN )
	{
		m_xLoginBtn[_LOGIN_BTN_CONN] .OnMouseMove(m_ptMousePos);
		m_xLoginBtn[_LOGIN_BTN_REG]  .OnMouseMove(m_ptMousePos);
		m_xLoginBtn[_LOGIN_BTN_CHGPW].OnMouseMove(m_ptMousePos);
		m_xLoginBtn[_LOGIN_BTN_QUIT] .OnMouseMove(m_ptMousePos);
	}

	return 0L;
}


LRESULT	CLoginProcess::OnMsgBoxReturn(WPARAM wParam, LPARAM lParam)
{
	BYTE bWndID		= HIBYTE(HIWORD(wParam));
	BYTE bMsgReturn	= LOBYTE(HIWORD(wParam));
	WORD wPacket	= LOWORD(wParam);

	switch ( bWndID )
	{
		case LOGIN_WNDID_INPUT:
		{
			if ( m_bProcState == _LOGINPROC_LOGIN )
			{
				// �Է»��¸� �缳���Ѵ�. ->PW�� ����� ID�� ���¸� �����Ѵ�.
				ZeroMemory(m_pszPW, MAX_PATH);
				SetWindowText(g_xChatEditBox.GetSafehWnd(), m_pszID);

				m_bLoginInputState = _LOGININPUT_PW;
				SetEditFocus();
				g_xChatEditBox.SetEnterUse(FALSE);
			}
			break;
		}
		case LOGIN_WNDID_GAMEOUT:
		{
			SendMessage(g_xMainWnd.GetSafehWnd(), WM_DESTROY, NULL, NULL);
			break;
		}
	}

	return 0L;
}


LRESULT	CLoginProcess::OnMove(WPARAM wParam, LPARAM lParam)
{
	if ( m_bProcState == _LOGINPROC_LOGIN )
	{
		SetFocus(g_xMainWnd.GetSafehWnd());
		ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_HIDE);
	}

	return 0L;
}


VOID CLoginProcess::DrawEffect(INT nIdx, INT nX, INT nY)
{
	if ( g_xMainWnd.Get3DDevice() )
	{
		if ( m_xImageLogin.NewSetIndex(nIdx) )
		{
			D3DWILTextr_CreateEmptyTexture(m_xImageLogin.m_szWilFileName, nIdx, 
										   m_xImageLogin.m_lpstNewCurrWilImageInfo->shWidth,
										   m_xImageLogin.m_lpstNewCurrWilImageInfo->shHeight,
										   (WORD*)m_xImageLogin.m_pbCurrImage, D3DTEXTR_TRANSPARENTBLACK);
			D3DWILTextr_Restore(m_xImageLogin.m_szWilFileName, nIdx, g_xMainWnd.Get3DDevice());

			D3DVECTOR vTrans;
			D3DMATRIX matTrans;
			D3DMATRIX matScale;
			D3DMATRIX matWorld;
			D3DMATRIX matWorldOriginal;
			D3DMATERIAL7 mtrl;

			D3DUtil_InitMaterial(mtrl, (FLOAT)255.0f/255.0f, (FLOAT)255.0f/255.0f, (FLOAT)255.0f/255.0f);
			mtrl.diffuse.a = 255/255.0f;
			g_xMainWnd.Get3DDevice()->SetMaterial(&mtrl);

			vTrans.x = (FLOAT) nX+(FLOAT)m_xImageLogin.m_lpstNewCurrWilImageInfo->shWidth /2+m_xImageLogin.m_lpstNewCurrWilImageInfo->shPX-320; 
			vTrans.y = (FLOAT)-nY-(FLOAT)m_xImageLogin.m_lpstNewCurrWilImageInfo->shHeight/2-m_xImageLogin.m_lpstNewCurrWilImageInfo->shPY+240; 
			vTrans.z = 0.0f;

			if( SUCCEEDED(g_xMainWnd.Get3DDevice()->BeginScene()))
			{
				g_xMainWnd.Get3DDevice()->GetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

				D3DUtil_SetTranslateMatrix(matTrans, vTrans);
				D3DUtil_SetScaleMatrix(matScale, (FLOAT)m_xImageLogin.m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)m_xImageLogin.m_lpstNewCurrWilImageInfo->shHeight, 1.0f);
				D3DMath_MatrixMultiply(matWorld, matScale, matTrans);
				g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);
				
				SetBlendRenderState(g_xMainWnd.Get3DDevice(), _BLEND_LIGHT, &mtrl);

				g_xMainWnd.Get3DDevice()->SetTexture(0, D3DWILTextr_GetSurface(m_xImageLogin.m_szWilFileName, nIdx));

				g_xMainWnd.Get3DDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_VERTEX, m_avBillBoard, 4, NULL);

				ResetBlendenderState(g_xMainWnd.Get3DDevice());

				g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

				g_xMainWnd.Get3DDevice()->EndScene();
			}

			D3DWILTextr_Invalidate(m_xImageLogin.m_szWilFileName, nIdx);
			D3DWILTextr_DestroyTexture(m_xImageLogin.m_szWilFileName, nIdx);
		}
	}
}





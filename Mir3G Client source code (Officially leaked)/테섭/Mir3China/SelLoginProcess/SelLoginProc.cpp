#include "StdAfx.h"

#define _PROFILE_FILENAME			"/SelLogin.ini"

//-----------------------------------------------------------------------------------------------------------------
// Procedure 관리함수.
//-----------------------------------------------------------------------------------------------------------------
/******************************************************************************************************************
[생성자]
*******************************************************************************************************************/
CSelLoginProcess::CSelLoginProcess()
{
	Init();
}


/******************************************************************************************************************
[소멸자]
*******************************************************************************************************************/
CSelLoginProcess::~CSelLoginProcess()
{
	DeleteProc();
}


/******************************************************************************************************************
변수및 모든객체를 초기화.
*******************************************************************************************************************/
VOID CSelLoginProcess::Init()
{
	m_nSvrBtnCount = 0;
	m_nSelectedSvrBtn = -1;
	m_nMenuStart = 0;

	m_nAreaBtnCount = 0;
	m_nSelectedAreaBtn = -1;
	m_xScrSelectMenu.Init();

	m_nSerNameCnt = 0;

	m_pObj = NULL;

	for ( INT nI=0; nI<40; nI++ )
	{
		ZeroMemory(&m_ptAreaBtn[nI], sizeof(POINT));
		ZeroMemory(&m_rcAreaBtn[nI], sizeof(RECT));
		ZeroMemory(&m_rcSvrBtn[nI], sizeof(RECT));
//		ZeroMemory(&m_xServerInfo[nI], sizeof(SERVERINFO));
		ZeroMemory(&m_szServerName[nI], sizeof(MAX_PATH));
		ZeroMemory(&m_szScreenName[nI], sizeof(MAX_PATH));
	}

	m_xServerInfo.ClearAll();

	ZeroMemory(&m_ptMousePos, sizeof(POINT));

	m_xImageLogin.Init();

	m_lpddsTextr = NULL;

}




/******************************************************************************************************************
필요한 데이타를 초기화하고 로드한다.
Prcedure가 시작되기전에 호출되어야 한다.
Load()->RenderScene()->SetNextProc()의 형태이다.
*******************************************************************************************************************/
VOID CSelLoginProcess::Load()
{
	Init();
	m_xImageLogin.NewLoad(".\\Data\\LoginInterface.wil");

	GetCurrentDirectory( sizeof( m_szProfileFullName ), m_szProfileFullName );
	lstrcat( m_szProfileFullName, _PROFILE_FILENAME );

	INT nCount = GetPrivateProfileInt( "ServerGroup", "Count", 0, m_szProfileFullName );

	m_xCloseBtn.CreateGameBtn(&m_xImageLogin, 3, 4, 760, 13, g_xMsg.GetMsg(1052), _BTN_TYPE_FOCUS, 3, TRUE);
	m_xScrSelectMenu.CreateScrlBar(&m_xImageLogin, 15, 10, 20, 447, 31);

	for ( INT nI=0; nI<nCount; nI++ )
	{
		CHAR szTemp[MAX_PATH], szData[MAX_PATH];
		char *pszLocation;
		sprintf( szTemp, "Server%d", nI+1);		
		GetPrivateProfileString( "ServerGroup", szTemp, "", szData, MAX_PATH, m_szProfileFullName );

		// 버튼 좌표 얻기
		if ( pszLocation = strchr(szData, ',') )
		{
			*pszLocation ++ = '\0';
			if ( szData[0] == NULL )
			{
			}
			else
			{
				strcpy(m_szScreenName[nI], szData);
			}
			strcpy(szData, pszLocation);

			pszLocation =  strchr(szData, ',');
			*pszLocation ++ = '\0';
			
			strcpy(m_szServerName[nI], szData);
			strcpy(szData, pszLocation);

			if ( pszLocation = strchr(szData, ',') )
				*pszLocation ++ = '\0';

			POINT ptLoc;
			m_ptAreaBtn[nI].x = atoi(szData);
			m_ptAreaBtn[nI].y = atoi(pszLocation);
			SetRect(&m_rcAreaBtn[nI], m_ptAreaBtn[nI].x, m_ptAreaBtn[nI].y, m_ptAreaBtn[nI].x + 40, m_ptAreaBtn[nI].y + 40);
			m_nAreaBtnCount++;
		}
	}
}


/******************************************************************************************************************
소멸이 필요한 객체를 정리.
Procedure가 종료되거나, 현상태에서 프로그램을 종료시킬때 호출된다.
*******************************************************************************************************************/
VOID CSelLoginProcess::DeleteProc()
{
	m_xImageLogin.Destroy();
	
	g_xClientSocket.DisconnectToServer();
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
HRESULT CSelLoginProcess::DrawBillBoard(LPDIRECT3DDEVICE7 lpDevice, D3DVECTOR* pvTrans, D3DVECTOR* pvScale, /*D3DVECTOR vRot, */D3DMATERIAL7* pmtrl, /*FLOAT fRotRad, */LPDIRECTDRAWSURFACE7 lpddsTextr, BYTE bBlendType)
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

//			lpDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_VERTEX, m_avBillBoard, 4, NULL);

			ResetBlendenderState(lpDevice);

			lpDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

			lpDevice->EndScene();

			return S_OK;
		}
	}
	return E_FAIL;
}


/******************************************************************************************************************
Procedure의 메인루프.
*******************************************************************************************************************/
VOID CSelLoginProcess::RenderScene(INT nLoopTime)
{
	Clear(RGB(0, 0, 0));

	if ( m_xImageLogin.NewSetIndex(0) )
	{
		g_xMainWnd.DrawWithImageForComp(0, 0, m_xImageLogin.m_lpstNewCurrWilImageInfo->shWidth, m_xImageLogin.m_lpstNewCurrWilImageInfo->shHeight,
										(WORD*)(m_xImageLogin.m_pbCurrImage));
	}

	m_xCloseBtn.ShowGameBtn();

	for ( INT nX=0; nX<m_nAreaBtnCount; nX++ )
	{
		if ( m_ptAreaBtn[nX].x !=0 || m_ptAreaBtn[nX].y != 0 )
		{
			if ( m_szScreenName[nX][0] != NULL )
			{
				RECT rcTitle = { m_ptAreaBtn[nX].x + 5, m_ptAreaBtn[nX].y + 25, m_ptAreaBtn[nX].x + 50, m_ptAreaBtn[nX].y + 40 };
				DWORD dwFontColor = RGB(0, 0, 0);
				g_xMainWnd.PutsHan(NULL, rcTitle.left - 1, rcTitle.top, dwFontColor, RGB(0, 0, 0), m_szScreenName[nX]);
				g_xMainWnd.PutsHan(NULL, rcTitle.left + 1, rcTitle.top, dwFontColor, RGB(0, 0, 0), m_szScreenName[nX]);
				g_xMainWnd.PutsHan(NULL, rcTitle.left , rcTitle.top + 1, dwFontColor, RGB(0, 0, 0), m_szScreenName[nX]);
				g_xMainWnd.PutsHan(NULL, rcTitle.left , rcTitle.top - 1, dwFontColor, RGB(0, 0, 0), m_szScreenName[nX]);
				g_xMainWnd.PutsHan(NULL, rcTitle.left , rcTitle.top, RGB(240, 240, 240), RGB(0, 0, 0), m_szScreenName[nX]);
			}

			RECT rcBtn = { m_ptAreaBtn[nX].x, m_ptAreaBtn[nX].y, m_ptAreaBtn[nX].x + 33, m_ptAreaBtn[nX].y + 21 };
			if ( nX == m_nSelectedAreaBtn )
			{
				if ( m_xImageLogin.NewSetIndex(13) )
				{
					g_xMainWnd.DrawWithImageForComp(m_ptAreaBtn[nX].x - 3, m_ptAreaBtn[nX].y - 3, m_xImageLogin.m_lpstNewCurrWilImageInfo->shWidth, m_xImageLogin.m_lpstNewCurrWilImageInfo->shHeight,
													(WORD*)(m_xImageLogin.m_pbCurrImage));
				}
			}
			else if ( PtInRect(&rcBtn, m_ptMousePos) )
			{
				if ( m_xImageLogin.NewSetIndex(12) )
				{
					g_xMainWnd.DrawWithImageForComp(m_ptAreaBtn[nX].x, m_ptAreaBtn[nX].y, m_xImageLogin.m_lpstNewCurrWilImageInfo->shWidth, m_xImageLogin.m_lpstNewCurrWilImageInfo->shHeight,
													(WORD*)(m_xImageLogin.m_pbCurrImage));
				}
			}
			else
			{
				if ( m_xImageLogin.NewSetIndex(11) )
				{
					g_xMainWnd.DrawWithImageForComp(m_ptAreaBtn[nX].x, m_ptAreaBtn[nX].y, m_xImageLogin.m_lpstNewCurrWilImageInfo->shWidth, m_xImageLogin.m_lpstNewCurrWilImageInfo->shHeight,
													(WORD*)(m_xImageLogin.m_pbCurrImage));
				}
			}
		}

		if ( nX != m_nSelectedAreaBtn )
			continue; 

		if ( m_xImageLogin.NewSetIndex(1) )
		{
			if ( g_xMainWnd.Get3DDevice() )
			{
				D3DVECTOR vTrans;
				D3DMATRIX matTrans;
				D3DMATRIX matScale;
				D3DMATRIX matWorld;
				D3DMATRIX matWorldOriginal;
				D3DMATERIAL7 mtrl;				
				D3DVECTOR		vecTrans;
				D3DVECTOR		vecScale;

				vecTrans = D3DVECTOR(m_ptAreaBtn[nX].x - 45 , m_ptAreaBtn[nX].y - 45, 0);
				vecScale = D3DVECTOR((FLOAT)m_xImageLogin.m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)m_xImageLogin.m_lpstNewCurrWilImageInfo->shHeight, 1);

				INT nFileType = 3, nFileIdx = 1, nImgIdx = 1;

				if ( !m_pObj )
				{
					m_pObj = new sTextureNode;

					sprintf( m_pObj->szKey, "%05d%05d%05d", 3, 1, 1);
					m_pObj->nFileType	= 3;
					m_pObj->nFileIdx	= 1;
					m_pObj->nImgIdx	= 1;
					m_pObj->pImg		= &m_xImageLogin;
					m_pObj->pSurface	= NULL;

					if ( m_pObj->pSurface == NULL )
					{
						if ( RestoreImg(m_pObj) == E_FAIL )
						{
							SAFE_DELETE(m_pObj);
						}
					}
				}

				if ( m_lpddsTextr == NULL )
					m_lpddsTextr = m_pObj->pSurface;

				D3DUtil_InitMaterial(mtrl, (FLOAT)((FLOAT)255/255.0f), (FLOAT)((FLOAT)255/255.0f), (FLOAT)((FLOAT)255/255.0f));
				mtrl.diffuse.a = (0)/255.0f;
				g_xMainWnd.Get3DDevice()->SetMaterial(&mtrl);

				vTrans.x = (FLOAT) m_ptAreaBtn[nX].x-55+(FLOAT)((FLOAT)m_xImageLogin.m_lpstNewCurrWilImageInfo->shWidth /2.0f)+(FLOAT)m_xImageLogin.m_lpstNewCurrWilImageInfo->shPX-400.0f; 
				vTrans.y = (FLOAT)-(m_ptAreaBtn[nX].y-120)-(FLOAT)((FLOAT)m_xImageLogin.m_lpstNewCurrWilImageInfo->shHeight/2.0f)-(FLOAT)m_xImageLogin.m_lpstNewCurrWilImageInfo->shPY+300.0f; 
				vTrans.z = 0;

 				D3DVECTOR vNorm(0, 0, -1);
				D3DVERTEX			m_avMagic[4];
				m_avMagic[0]  = D3DVERTEX(D3DVECTOR(-0.5f, 0.5f, 0), vNorm, 0, 0);
				m_avMagic[1]  = D3DVERTEX(D3DVECTOR(-0.5f,-0.5f, 0), vNorm, 0, 1);
				m_avMagic[2]  = D3DVERTEX(D3DVECTOR( 0.5f, 0.5f, 0), vNorm, 1, 0);
				m_avMagic[3]  = D3DVERTEX(D3DVECTOR( 0.5f,-0.5f, 0), vNorm, 1, 1);
				
				if ( SUCCEEDED(g_xMainWnd.Get3DDevice()->BeginScene()) )
				{
					g_xMainWnd.Get3DDevice()->GetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

					D3DUtil_SetTranslateMatrix(matTrans, vTrans);
					D3DUtil_SetScaleMatrix(matScale, (FLOAT)m_xImageLogin.m_lpstNewCurrWilImageInfo->shWidth, (FLOAT)m_xImageLogin.m_lpstNewCurrWilImageInfo->shHeight, 1.0f);
					D3DMath_MatrixMultiply(matWorld, matScale, matTrans);
					g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);

					SetBlendRenderState(g_xMainWnd.Get3DDevice(), 2, &mtrl);

					g_xMainWnd.Get3DDevice()->SetTexture(0, m_lpddsTextr);
					g_xMainWnd.Get3DDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_VERTEX, m_avMagic, 4, NULL);

					ResetBlendenderState(g_xMainWnd.Get3DDevice());

					g_xMainWnd.Get3DDevice()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

					g_xMainWnd.Get3DDevice()->EndScene();
				}
			}
		}
	}

	m_xScrSelectMenu.ShowScrlBar(204, 84, m_nMenuStart, m_nSvrBtnCount);

	if ( m_nSvrBtnCount > 0 )
	{
		RECT rcTitle = { 28, 20, 200, 35 };
		g_xMainWnd.PutsHan(NULL, rcTitle, RGB(250, 250, 250), RGB(0, 0, 0), m_szServerName[m_nSelectedAreaBtn]);
		for ( nX=0; nX<m_nSvrBtnCount && nX<20; nX++ )
		{
			INT  nLine, nListCnt;
			CListNode < SERVERINFO > *pNode;
			LPSERVERINFO pstServerInfo = NULL;

			for ( pNode = m_xServerInfo.GetHead(), nListCnt = 0; pNode ; pNode = pNode->GetNext(), nListCnt++ )
			{
				if ( nListCnt == m_nMenuStart + nX )
				{
					pstServerInfo = pNode->GetData();
					break;
				}
			}
			

/*			if ( m_nSvrBtnCount > 20 && PtInRect(&m_rcSvrBtn[nX], m_ptMousePos) )
			{
				if ( nX < 20 )
				{
					if ( m_xImageLogin.NewSetIndex(9) )
					{
						g_xMainWnd.DrawWithImageForComp(m_rcSvrBtn[nX].left - 15, m_rcSvrBtn[nX].top - 5, m_xImageLogin.m_lpstNewCurrWilImageInfo->shWidth, m_xImageLogin.m_lpstNewCurrWilImageInfo->shHeight,
														(WORD*)(m_xImageLogin.m_pbCurrImage));
					}
				}
				else
				{
					if ( m_xImageLogin.NewSetIndex(10) )
					{
						g_xMainWnd.DrawWithImageForComp(m_rcSvrBtn[nX].left - 2, m_rcSvrBtn[nX].top - 5, m_xImageLogin.m_lpstNewCurrWilImageInfo->shWidth, m_xImageLogin.m_lpstNewCurrWilImageInfo->shHeight,
														(WORD*)(m_xImageLogin.m_pbCurrImage));
					}
				}

				g_xMainWnd.PutsHan(NULL, m_rcSvrBtn[nX], RGB(250, 250, 250), RGB(0, 0, 0), m_xServerInfo[nX].szServerName);
			}
			else
*/			if ( PtInRect(&m_rcSvrBtn[nX], m_ptMousePos) )
			{
				if ( pstServerInfo != NULL )
				{
					if ( strcmp(pstServerInfo->szServerName, "empty") != 0 )
					{
						if ( m_xImageLogin.NewSetIndex(8) )
						{
							g_xMainWnd.DrawWithImageForComp(m_rcSvrBtn[nX].left + 7, m_rcSvrBtn[nX].top - 5, m_xImageLogin.m_lpstNewCurrWilImageInfo->shWidth, m_xImageLogin.m_lpstNewCurrWilImageInfo->shHeight,
															(WORD*)(m_xImageLogin.m_pbCurrImage));
						}
						
						
						g_xMainWnd.PutsHan(NULL, m_rcSvrBtn[nX], RGB(250, 250, 250), RGB(0, 0, 0), pstServerInfo->szServerName);
					}
				}
//				g_xMainWnd.PutsHan(NULL, m_rcSvrBtn[nX], RGB(250, 250, 250), RGB(0, 0, 0), m_xServerInfo[nX].szServerName);
			}
			else
			{
/*				if ( nX < 20 && m_nSvrBtnCount > 20 )
				{
					if ( m_xImageLogin.NewSetIndex(5) )
					{
						g_xMainWnd.DrawWithImageForComp(m_rcSvrBtn[nX].left - 15, m_rcSvrBtn[nX].top - 5, m_xImageLogin.m_lpstNewCurrWilImageInfo->shWidth, m_xImageLogin.m_lpstNewCurrWilImageInfo->shHeight,
														(WORD*)(m_xImageLogin.m_pbCurrImage));
					}
				}
				else if ( m_nSvrBtnCount > 20 )
				{
					if ( m_xImageLogin.NewSetIndex(6) )
					{
						g_xMainWnd.DrawWithImageForComp(m_rcSvrBtn[nX].left - 2, m_rcSvrBtn[nX].top - 5, m_xImageLogin.m_lpstNewCurrWilImageInfo->shWidth, m_xImageLogin.m_lpstNewCurrWilImageInfo->shHeight,
														(WORD*)(m_xImageLogin.m_pbCurrImage));
					}
				}
				else
				{
*/
				if ( pstServerInfo != NULL )
				{
					if ( strcmp(pstServerInfo->szServerName, "empty") != 0 )
					{
						if ( m_xImageLogin.NewSetIndex(7) )
						{
							g_xMainWnd.DrawWithImageForComp(m_rcSvrBtn[nX].left + 7, m_rcSvrBtn[nX].top - 5, m_xImageLogin.m_lpstNewCurrWilImageInfo->shWidth, m_xImageLogin.m_lpstNewCurrWilImageInfo->shHeight,
															(WORD*)(m_xImageLogin.m_pbCurrImage));
						}
	//				}
	//				g_xMainWnd.DrawWithGDI(&m_rcSvrBtn[nX], NULL, RGB(200, 200, 200), 1);
					
						g_xMainWnd.PutsHan(NULL, m_rcSvrBtn[nX], RGB(250, 250, 250), RGB(0, 0, 0), pstServerInfo->szServerName);
					}
				}
//				g_xMainWnd.PutsHan(NULL, m_rcSvrBtn[nX], RGB(250, 250, 250), RGB(0, 0, 0), m_xServerInfo[nX].szServerName);			
			}
		}
	}
}


//-----------------------------------------------------------------------------------------------------------------
// 윈도우 메시지 관련 함수정의.
//-----------------------------------------------------------------------------------------------------------------
/******************************************************************************************************************
메시지 Procedure.
*******************************************************************************************************************/
LRESULT CSelLoginProcess::DefMainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch ( uMsg )
	{
		case WM_DESTROY:
			OnDestroy(wParam, lParam);
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
		case WM_MOUSEWHEEL:
			OnWheel(wParam, lParam);
	}
	return CWHDefProcess::DefMainWndProc(hWnd, uMsg, wParam, lParam);
}


/******************************************************************************************************************
프로그램 종료시.
*******************************************************************************************************************/
LRESULT CSelLoginProcess::OnDestroy(WPARAM wParam, LPARAM lParam)
{
	WSACleanup();
	return 0L;
}


LRESULT	CSelLoginProcess::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	POINT ptMouse;

	ptMouse.x = LOWORD(lParam);
	ptMouse.y = HIWORD(lParam);

	for ( INT nI=0; nI<m_nAreaBtnCount; nI++ )
	{
		if ( PtInRect(&m_rcAreaBtn[nI], ptMouse) )
		{
			m_nSelectedAreaBtn = nI;
			LoadServerList();
		}
	}

	for ( nI=0; nI<m_nSvrBtnCount; nI++ )
	{
		if ( PtInRect(&m_rcSvrBtn[nI], ptMouse) )
		{
			m_nSelectedSvrBtn = nI + m_nMenuStart;

			if ( m_nSelectedSvrBtn < m_nSerNameCnt )
				MakeIniFile();
		}
	}

	if ( m_xScrSelectMenu.OnLButtonDown(ptMouse) )
	{
		FLOAT	fScrlRate;

		fScrlRate	= m_xScrSelectMenu.GetScrlRate();
		m_nMenuStart = (INT)((m_nSvrBtnCount)*fScrlRate);

		if ( m_nMenuStart > m_nSvrBtnCount - 1 )
			m_nMenuStart = m_nSvrBtnCount - 1 ;

		return TRUE;
	}


	if ( m_xCloseBtn.OnLButtonDown(ptMouse) )		
		return TRUE;

	return 0L;
}


LRESULT	CSelLoginProcess::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	POINT ptMouse;

	ptMouse.x = LOWORD(lParam);
	ptMouse.y = HIWORD(lParam);

	if ( m_xCloseBtn.OnLButtonUp(ptMouse) )
	{
		BOOL bRestart = FALSE;
		QuitProgram(bRestart);
	}
		
	if ( m_xScrSelectMenu.OnLButtonUp(ptMouse) )
		return FALSE;

	return 0L;
}


LRESULT	CSelLoginProcess::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	m_ptMousePos.x = LOWORD(lParam);
	m_ptMousePos.y = HIWORD(lParam);

	if ( m_xScrSelectMenu.OnMouseMove(m_ptMousePos) )
	{
		FLOAT	fScrlRate;
		fScrlRate	= m_xScrSelectMenu.GetScrlRate();

		m_nMenuStart = (INT)((m_nSvrBtnCount)*fScrlRate);
		return TRUE;
	}

	return 0L;
}

LRESULT	CSelLoginProcess::OnWheel(WPARAM wParam, LPARAM lParam)
{
	INT nDelta;

	nDelta = ( (INT)wParam < 0 ) ? -1 : 1;
	if ( nDelta > 0 )
	{
		if ( m_nMenuStart > 0 )
			m_nMenuStart--;
	}
	else
	{
		if ( m_nMenuStart < m_nSerNameCnt - 1 )
			m_nMenuStart++;
	}

	return 0L;
}



VOID CSelLoginProcess::OnConnectToServer()
{
}


CHAR* CSelLoginProcess::OnMessageReceive(CHAR* pszBuf, INT nLen)
{
	return pszBuf;
}

HRESULT CSelLoginProcess::RestoreImg(sTextureNode* pstTextrNode)
{
    D3DDEVICEDESC7		ddDesc;
    DDSURFACEDESC2		ddsd;
	LPDIRECT3DDEVICE7	pd3dDevice = g_xMainWnd.Get3DDevice();
	DWORD				dwWidth, dwHeight;
	WORD*				pwSrc;

	if ( pstTextrNode == NULL )
	{
		return E_FAIL;
	}

	if ( pd3dDevice == NULL )
	{
		return E_FAIL;
	}

    if ( FAILED(pd3dDevice->GetCaps(&ddDesc)) )
	{
        return E_FAIL;
	}

	dwWidth = dwHeight = 0;
	pwSrc	= NULL;
	if ( pstTextrNode->pImg->NewSetIndex(pstTextrNode->nImgIdx) )
	{
		dwWidth  = pstTextrNode->pImg->m_lpstNewCurrWilImageInfo->shWidth;
		dwHeight = pstTextrNode->pImg->m_lpstNewCurrWilImageInfo->shHeight;
		pwSrc	 = (WORD*)pstTextrNode->pImg->m_pbCurrImage;			
	}
	else
	{
        return E_FAIL;
	}

//  D3DUtil_InitSurfaceDesc( ddsd );
    ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
    ddsd.dwSize          = sizeof(ddsd);
    ddsd.dwFlags         = DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps  = DDSCAPS_TEXTURE;
    ddsd.dwWidth         = dwWidth;
    ddsd.dwHeight        = dwHeight;

    if ( ddDesc.deviceGUID == IID_IDirect3DHALDevice || ddDesc.deviceGUID == IID_IDirect3DTnLHalDevice )
	{
        ddsd.ddsCaps.dwCaps2 = DDSCAPS2_TEXTUREMANAGE;
	}
    else
	{
        ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
	}

	// 2의 제곱수로 세팅.
    if ( ddDesc.dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_POW2 )
    {
        for ( ddsd.dwWidth =1; dwWidth>ddsd.dwWidth;   ddsd.dwWidth<<=1  );
        for ( ddsd.dwHeight=1; dwHeight>ddsd.dwHeight; ddsd.dwHeight<<=1 );
    }

    DWORD dwMaxWidth  = ddDesc.dwMaxTextureWidth;
    DWORD dwMaxHeight = ddDesc.dwMaxTextureHeight;
    ddsd.dwWidth  = min(ddsd.dwWidth,  (dwMaxWidth  ? dwMaxWidth  : 256));
    ddsd.dwHeight = min(ddsd.dwHeight, (dwMaxHeight ? dwMaxHeight : 256));

	// 직사각형의 텍스춰를 지원하지 않는다면.
    if ( ddDesc.dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_SQUAREONLY )
    {
        if ( ddsd.dwWidth > ddsd.dwHeight )
		{
			ddsd.dwHeight = ddsd.dwWidth;
		}
        else 
		{
			ddsd.dwWidth  = ddsd.dwHeight;
		}
    }

    LPDIRECTDRAW7 pDD =	g_xMainWnd.GetDirectDraw();

	if ( pDD == NULL )
	{
		return E_FAIL;
	}

    if ( FAILED(pDD->CreateSurface(&ddsd, &pstTextrNode->pSurface, NULL)) )
	{
        return E_FAIL;
	}

	if ( ddsd.dwWidth == dwWidth && ddsd.dwHeight == dwHeight )
	{
		if ( CopyDToS(dwWidth, dwHeight, pwSrc, pstTextrNode->pSurface) == E_FAIL )
		{
			SAFE_RELEASE(pstTextrNode->pSurface);
			return E_FAIL;
		}
	}
	else
	{
		if ( CopyDToSToS(dwWidth, dwHeight, pwSrc, pstTextrNode->pSurface) == E_FAIL )
		{
			SAFE_RELEASE(pstTextrNode->pSurface);
			return E_FAIL;
		}
	}

	// 컬러키를 세팅한다.
	DDSetColorKey(pstTextrNode->pSurface, RGB(0, 0, 0));

    return S_OK;
}


HRESULT CSelLoginProcess::CopyDToSToS(DWORD dwWidth, DWORD dwHeight, WORD* pwSrc, LPDIRECTDRAWSURFACE7 lpddsDst)
{
	HRESULT					hr;
    DDSURFACEDESC2			ddsd;
    LPDIRECTDRAWSURFACE7	pddsTempSurface;
	LPDIRECTDRAW7			pDD = g_xMainWnd.GetDirectDraw();

	if ( pDD == NULL )
	{
		return E_FAIL;
	}

    ddsd.dwSize = sizeof(DDSURFACEDESC2);
    lpddsDst->GetSurfaceDesc(&ddsd);
    ddsd.dwFlags         = DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps  = DDSCAPS_TEXTURE|DDSCAPS_SYSTEMMEMORY;
    ddsd.ddsCaps.dwCaps2 = 0L;
    ddsd.dwWidth         = dwWidth;
    ddsd.dwHeight        = dwHeight;

    if ( FAILED(pDD->CreateSurface(&ddsd, &pddsTempSurface, NULL)) )
    {
        return E_FAIL;
    }

	LONG	lWidth;
    DDSURFACEDESC2	ddsdLock;
	ZeroMemory(&ddsdLock, sizeof(DDSURFACEDESC2));
	ddsdLock.dwSize = sizeof(DDSURFACEDESC2);
	if ( FAILED(pddsTempSurface->Lock(NULL, &ddsdLock, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL)) )
	{
		SAFE_RELEASE(pddsTempSurface);
		return E_FAIL;
	}
    WORD* pwdDst = (WORD*)ddsdLock.lpSurface;
	lWidth		 = ddsdLock.lPitch >> 1;
			
	INT nWidthStart		= 0;
	INT nWidthEnd		= 0;
	INT nCurrWidth		= 0;
	INT nCntCopyWord	= 0;
	INT nYCnt			= 0;
	INT nLastWidth		= 0;

	// y축에 대해서 실제로 루핑시킬 Count만을 정한다.
	for ( nYCnt = 0; nYCnt < dwHeight ; nYCnt++ )
	{
		// 한라인의 길이를 얻어온다.(단위는 워드)
		nWidthEnd += pwSrc[nWidthStart];
		nWidthStart++;
		
		// 라인의 길이만큼 화면에 뿌려준다.
		for ( INT x = nWidthStart; x < nWidthEnd ; )
		{
			if ( pwSrc[x] == 0xC0 )
			{
				x++;
				nCntCopyWord = pwSrc[x];
				x++;

				nLastWidth = nCurrWidth;
				nCurrWidth += nCntCopyWord;

				memset(&pwdDst[((nYCnt) * lWidth) + (nLastWidth)], 0, sizeof(WORD)*nCntCopyWord);
			}
			else if ( pwSrc[x] == 0xC1 || pwSrc[x] == 0xC2 || pwSrc[x] == 0xC3 )
			{
				x++;
				nCntCopyWord = pwSrc[x];
				x++;

				nLastWidth = nCurrWidth;
				nCurrWidth += nCntCopyWord;

				memcpy(&pwdDst[((nYCnt) * lWidth) + (nLastWidth)], &pwSrc[x], sizeof(WORD)*nCntCopyWord);

				x += nCntCopyWord;
			}
		}
		// 라인의 끝을 다음 라인의 시작으로 옮겨준다.
		nWidthEnd++;

		nWidthStart	= nWidthEnd;
		nCurrWidth = 0;
	}

	pddsTempSurface->Unlock(NULL);

	while ( TRUE )
	{
		hr = lpddsDst->Blt(NULL, pddsTempSurface, NULL, DDBLT_WAIT, NULL);

		if ( hr == DDERR_SURFACELOST )
		{
			lpddsDst->Restore();
		}

		if ( hr != DDERR_WASSTILLDRAWING )
		{
			SAFE_RELEASE(pddsTempSurface);
		    return S_OK;
		}
	} 
	
	return E_FAIL;
}


HRESULT CSelLoginProcess::CopyDToS(DWORD dwWidth, DWORD dwHeight, WORD* pwSrc, LPDIRECTDRAWSURFACE7 lpddsDst)
{
	RECT			rc;
	HRESULT			hr;
	DDSURFACEDESC2	ddsd;
	
	LONG	lWidth;
	ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
	ddsd.dwSize = sizeof(DDSURFACEDESC2);
	if ( FAILED(lpddsDst->Lock(NULL, &ddsd, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL)) )
	{
		return E_FAIL;
	}

    WORD* pwdDst = (WORD*)ddsd.lpSurface;
	lWidth		 = ddsd.lPitch >> 1;

	INT nWidthStart		= 0;
	INT nWidthEnd		= 0;
	INT nCurrWidth		= 0;
	INT nCntCopyWord	= 0;
	INT nYCnt			= 0;
	INT nLastWidth		= 0;

	// y축에 대해서 실제로 루핑시킬 Count만을 정한다.
	for ( nYCnt = 0 ; nYCnt < dwHeight ; nYCnt++ )
	{
		// 한라인의 길이를 얻어온다.(단위는 워드)
		nWidthEnd += pwSrc[nWidthStart];
		nWidthStart++;
		
		// 라인의 길이만큼 화면에 뿌려준다.
		for ( INT x = nWidthStart; x < nWidthEnd ; )
		{
			if ( pwSrc[x] == 0xC0 )
			{
				x++;
				nCntCopyWord = pwSrc[x];
				x++;

				nLastWidth = nCurrWidth;
				nCurrWidth += nCntCopyWord;

				memset(&pwdDst[((nYCnt) * lWidth) + (nLastWidth)], 0, sizeof(WORD)*nCntCopyWord);
			}
			else if ( pwSrc[x] == 0xC1 || pwSrc[x] == 0xC2 || pwSrc[x] == 0xC3 )
			{
				x++;
				nCntCopyWord = pwSrc[x];
				x++;

				nLastWidth = nCurrWidth;
				nCurrWidth += nCntCopyWord;

				memcpy(&pwdDst[((nYCnt) * lWidth) + (nLastWidth)], &pwSrc[x], sizeof(WORD)*nCntCopyWord);

				x += nCntCopyWord;
			}
		}
		// 라인의 끝을 다음 라인의 시작으로 옮겨준다.
		nWidthEnd++;

		nWidthStart	= nWidthEnd;
		nCurrWidth = 0;
	}

	lpddsDst->Unlock(NULL);

	return S_OK;
}

VOID CSelLoginProcess::LoadServerList()
{
	CHAR szGroup[MAX_PATH], szData[MAX_PATH], szKey[MAX_PATH];
	char *pszLocation;
	INT nLineLen = 0, nI = 0;

	m_nSerNameCnt = 0;
	m_nSelectedSvrBtn = -1;
	m_nMenuStart = 0;

	sprintf(szGroup, "ServerGroup%d", m_nSelectedAreaBtn+1);

//	for ( INT nI=0; nI<m_nSvrBtnCount; nI++ )
//		ZeroMemory(&m_xServerInfo[nI], sizeof(SERVERINFO));
	m_xServerInfo.ClearAll();
	
	m_nSvrBtnCount = GetPrivateProfileInt( szGroup, "Count", 0, m_szProfileFullName );

	if ( ( m_nSvrBtnCount == 0 ) )
		return;

//	if ( m_nSvrBtnCount >= 20 )
//	{
		for ( nI=0; nI<m_nSvrBtnCount; nI++ )
		{
			sprintf(szKey, "Server%d", nI+1);

			if ( GetPrivateProfileString ( szGroup, szKey, "", szData, sizeof(szData), m_szProfileFullName ) )
			{
				CHAR* pszServer = NULL;
				CHAR* pszLogin = NULL;
				CHAR* pszPatch = NULL;

				SERVERINFO *pObj = new SERVERINFO;

				// 서버그룹 이름만 뽑아내는 부분
				if ( pszLocation = strchr(szData, ',') )
				{
					*pszLocation ++ = '\0';		//szData; -> 이름
//					strcpy( m_xServerInfo[nI].szServerName, szData );

					nLineLen = strlen(szData)+1;
					pszServer = new CHAR[nLineLen];
					ZeroMemory(pszServer, nLineLen);

					sprintf(pszServer, szData);
					sprintf(pObj->szServerName, pszServer);
//					pObj->szServerName = pszServer;
					
//					if ( nI>=20 )
//						SetRect(&m_rcSvrBtn[nI], 115, 70+25*(nI-20), 200, 85+25*(nI-20));
//					else
//						SetRect(&m_rcSvrBtn[nI], 10, 70+25*nI, 200, 85+25*nI);

					if ( nI<20 )
						SetRect(&m_rcSvrBtn[nI], 10, 70+25*nI, 200, 85+25*nI);

					strcpy( szData, pszLocation );
				}

				if ( pszLocation = strchr(szData, ',') )
				{
					*pszLocation ++ = '\0';		//szData; -> 이름

//					strcpy( m_xServerInfo[nI].szLoginSectionName, szData );

					nLineLen = strlen(szData)+1;
					pszLogin = new CHAR[nLineLen];
					ZeroMemory(pszLogin, nLineLen);

					sprintf(pszLogin, szData);

					
					sprintf(pObj->szLoginSectionName , pszLogin);
//					pObj->szLoginSectionName = pszLogin;
					
//					strcpy( m_xServerInfo[nI].szPatchSectionName, pszLocation );

					nLineLen = strlen(pszLocation)+1;
					pszPatch = new CHAR[nLineLen];
					ZeroMemory(pszPatch, nLineLen);

					sprintf(pszPatch, pszLocation);

					sprintf(pObj->szPatchSectionName, pszPatch);
//					pObj->szLoginSectionName = pszPatch;
				}

				m_nSerNameCnt++;
				if ( !m_xServerInfo.Insert(pObj) )
				{
					delete[] pszServer;
					delete[] pszLogin;
					delete[] pszPatch;
					CHAR pszError[MAX_PATH];
					sprintf(pszError, "SelLogin.txt File Error");
					MessageBox(NULL, (char*)pszError, "[Error] - Legend of Mir III", MB_ICONERROR);
	//				DelAllMIF();
					return;
				}
			}
		}
//	}
//	else
//	{
/*		for ( nI=0; nI<m_nSvrBtnCount; nI++ )
		{
			sprintf(szKey, "Server%d", nI+1);

			if ( GetPrivateProfileString ( szGroup, szKey, "", szData, sizeof(szData), m_szProfileFullName ) )
			{
				// 서버그룹 이름만 뽑아내는 부분
				if ( pszLocation = strchr(szData, ',') )
				{
					*pszLocation ++ = '\0';		//szData; -> 이름
					strcpy( m_xServerInfo[nI].szServerName, szData );

					SetRect(&m_rcSvrBtn[nI], 50, 70+25*nI, 165, 85+25*nI);

					strcpy( szData, pszLocation );
				}

				if ( pszLocation = strchr(szData, ',') )
				{
					*pszLocation ++ = '\0';		//szData; -> 이름
					strcpy( m_xServerInfo[nI].szLoginSectionName, szData );
					strcpy( m_xServerInfo[nI].szPatchSectionName, pszLocation );
				}

			}
		}
*/
//	}
}

VOID CSelLoginProcess::MakeIniFile()
{
	INT  nLine, nListCnt;
	CListNode < SERVERINFO > *pNode;
	LPSERVERINFO pstServerInfo = NULL;

	for ( pNode = m_xServerInfo.GetHead(), nListCnt = 0; pNode ; pNode = pNode->GetNext(), nListCnt++ )
	{
		if ( nListCnt < m_nSelectedSvrBtn )
			continue;

		pstServerInfo = pNode->GetData();
		break;
	}

	if ( strcmp(pstServerInfo->szLoginSectionName, "empty") == 0 )
		return; 

	GetPrivateProfileString( pstServerInfo->szLoginSectionName, "ServerAddr", "", 
									m_MirInfo.szLoginSvrAddr, sizeof( m_MirInfo.szLoginSvrAddr ), m_szProfileFullName );
	GetPrivateProfileString( pstServerInfo->szLoginSectionName, "Param1", "", 
									m_MirInfo.szParam1, sizeof( m_MirInfo.szParam1 ), m_szProfileFullName );
	GetPrivateProfileString( pstServerInfo->szLoginSectionName, "Param2", "", 
									m_MirInfo.szParam2, sizeof( m_MirInfo.szParam2 ), m_szProfileFullName );
	GetPrivateProfileString( pstServerInfo->szLoginSectionName, "Param3", "", 
									m_MirInfo.szParam3, sizeof( m_MirInfo.szParam3 ), m_szProfileFullName );
	GetPrivateProfileString( pstServerInfo->szLoginSectionName, "ServerList", "", 
									m_MirInfo.szServerList, sizeof( m_MirInfo.szServerList ), m_szProfileFullName );

	WriteMirProfile();

	GetPrivateProfileString( pstServerInfo->szPatchSectionName, "ServerIP", "", 
									m_MirPatchInfo.szServerIP, sizeof( m_MirPatchInfo.szServerIP ), m_szProfileFullName );
	GetPrivateProfileString( pstServerInfo->szPatchSectionName, "BaseDirectory", "", 
									m_MirPatchInfo.szBaseDirectory, sizeof( m_MirPatchInfo.szBaseDirectory ), m_szProfileFullName );
/*
	GetPrivateProfileString( m_xServerInfo[m_nSelectedSvrBtn].szLoginSectionName, "ServerAddr", "", 
									m_MirInfo.szLoginSvrAddr, sizeof( m_MirInfo.szLoginSvrAddr ), m_szProfileFullName );
	GetPrivateProfileString( m_xServerInfo[m_nSelectedSvrBtn].szLoginSectionName, "Param1", "", 
									m_MirInfo.szParam1, sizeof( m_MirInfo.szParam1 ), m_szProfileFullName );
	GetPrivateProfileString( m_xServerInfo[m_nSelectedSvrBtn].szLoginSectionName, "Param2", "", 
									m_MirInfo.szParam2, sizeof( m_MirInfo.szParam2 ), m_szProfileFullName );
	GetPrivateProfileString( m_xServerInfo[m_nSelectedSvrBtn].szLoginSectionName, "Param3", "", 
									m_MirInfo.szParam3, sizeof( m_MirInfo.szParam3 ), m_szProfileFullName );
	GetPrivateProfileString( m_xServerInfo[m_nSelectedSvrBtn].szLoginSectionName, "ServerList", "", 
									m_MirInfo.szServerList, sizeof( m_MirInfo.szServerList ), m_szProfileFullName );

	WriteMirProfile();

	GetPrivateProfileString( m_xServerInfo[m_nSelectedSvrBtn].szPatchSectionName, "ServerIP", "", 
									m_MirPatchInfo.szServerIP, sizeof( m_MirPatchInfo.szServerIP ), m_szProfileFullName );
	GetPrivateProfileString( m_xServerInfo[m_nSelectedSvrBtn].szPatchSectionName, "BaseDirectory", "", 
									m_MirPatchInfo.szBaseDirectory, sizeof( m_MirPatchInfo.szBaseDirectory ), m_szProfileFullName );
*/
	WriteMirPatchProfile();

	BOOL bRestart = TRUE;
	QuitProgram(bRestart);
}

VOID CSelLoginProcess::WriteMirProfile()
{
	char		szMirProfileName[256];
	char		*pszServer = m_MirInfo.szServerList;
	UINT		nIndex = 1;
	char		szCount[8];

	GetCurrentDirectory( sizeof( szMirProfileName ), szMirProfileName );
	lstrcat( szMirProfileName, _MIRPROFILE_FILENAME );

	WritePrivateProfileString( "Initial", "ServerAddr", m_MirInfo.szLoginSvrAddr, szMirProfileName );
	WritePrivateProfileString( "Initial", "Param1", m_MirInfo.szParam1, szMirProfileName );
	WritePrivateProfileString( "Initial", "Param2", m_MirInfo.szParam2, szMirProfileName );
	WritePrivateProfileString( "Initial", "Param3", m_MirInfo.szParam3, szMirProfileName );

	while ( pszServer = GetCaptionName( nIndex, pszServer, szMirProfileName ) )
		nIndex++;
	
	_itoa( nIndex, szCount, 10 );

	WritePrivateProfileString( "Server", "ServerCount", szCount, szMirProfileName );
}

VOID CSelLoginProcess::WriteMirPatchProfile()
{
	char szMirProfileName[256];

	GetCurrentDirectory( sizeof( szMirProfileName ), szMirProfileName );
	lstrcat( szMirProfileName, _MIRPATCHPROFILE_FILENAME );

	WritePrivateProfileString( "PATCH_FTP", "ServerIP", m_MirPatchInfo.szServerIP, szMirProfileName );
	WritePrivateProfileString( "PATCH_FTP", "BaseDirectory", m_MirPatchInfo.szBaseDirectory, szMirProfileName );
	WritePrivateProfileString( "PATCH_FTP", "PORT", "21", szMirProfileName );
	WritePrivateProfileString( "PATCH_FTP", "userid", "anonymous", szMirProfileName );
	WritePrivateProfileString( "PATCH_FTP", "passwd", "user@host.com", szMirProfileName );
	WritePrivateProfileString( "PATCH_FTP", "ListFile", "!plist.lst", szMirProfileName );
}


char *CSelLoginProcess::GetCaptionName( int nIndex, char *pszText, char *pszFileName )
{
	char *pszStart	= strchr( pszText, '(' );
	char *pszEnd	= NULL;
	char *pszDevide	= NULL;
	char szKey[32];

	if ( !pszStart ) return NULL;

	pszEnd = strchr( ++pszStart, ')' );

	if ( pszEnd )
	{
		pszDevide = strchr( pszStart, '/' );

		if ( !pszDevide ) return NULL;

		*pszDevide++	= '\0';
		*pszEnd++		= '\0';

		sprintf( szKey, "server%dcaption", nIndex);
		WritePrivateProfileString( "Server", szKey, pszStart, pszFileName );
		sprintf( szKey, "server%dname", nIndex);
		WritePrivateProfileString( "Server", szKey, pszDevide, pszFileName );

		return strchr( pszEnd, '(' );
	}

	return NULL;
}

VOID CSelLoginProcess::QuitProgram(BOOL bRestart)
{
	if ( bRestart )
	{
#ifdef _TEST_SERVER
#else
	if ( g_execCmds.bNotPatchd == TRUE )
	{
		char szFileName[MAX_PATH];

		GetCurrentDirectory(MAX_PATH, szFileName);

		strcat(szFileName, ".\\Mir3Patch.exe");
	
		STARTUPINFO			si = {sizeof( STARTUPINFO ), 0,};
		PROCESS_INFORMATION	pi = {0,};

		if ( !CreateProcess( szFileName, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi ) )
		{
			MessageBox(NULL, "Patch Error", "Legend Of Mir 3", MB_OK|MB_ICONSTOP);
		}

		SendMessage(g_xMainWnd.GetSafehWnd(), WM_DESTROY, NULL, NULL);
	}
	else
	{
		SetNextProc();
	}
#endif
	}
	else
	{
		DeleteProc();
		SendMessage(g_xMainWnd.GetSafehWnd(), WM_DESTROY, NULL, NULL);
	}
}

VOID CSelLoginProcess::SetNextProc()
{
	DeleteProc();
	g_xClientSocket.m_pxDefProc = g_xMainWnd.m_pxDefProcess = &g_xLoginProc;
	g_xLoginProc.Load();
	g_bProcState = _LOGIN_PROC;
	if ( g_execCmds.bFullScreen )
		g_xMainWnd.ResetDXG(640, 480, 16, _DXG_SCREENMODE_FULLSCREEN, _DXG_DEVICEMODE_PRIMARY|_DXG_DEVICEMODE_D3D);
	else
		g_xMainWnd.ResetDXG(640, 480, 16, _DXG_SCREENMODE_WINDOW, _DXG_DEVICEMODE_PRIMARY|_DXG_DEVICEMODE_D3D);
}

#include "StdAfx.h"

LONG				g_OriginWndProc;

CClientSocket		g_xClientSocket;
CWHDXGraphicWindow	g_xMainWnd;
SoundManager		g_SoundManager;
CSprite				g_xSpriteInfo;
CChatEdit			g_xChatEditBox;
StringSplitter		g_xStringSplitter;
CLoginProcess		g_xLoginProc;
CSelLoginProcess	g_xSelLoginProc;
CChrProcess			g_xChrSelProc;
CGameProcess		g_xGameProc;
CMsg				g_xMsg;

CMsg				g_xItemMsg;		// 아이템 설명 추가
/***** Exported global variable ********************************************/


INT					g_nCertifyCode;
char				g_szUserID[25];
char				g_szCharName[25];
char				g_szServerName[20];
BYTE				g_nUpgradeLevel;  //lee wun gyo
char				g_szServerIP[16];
INT					g_nServerPort;
INT					g_nVersion;
char				g_szPreServerIP[16];
INT					g_nPreServerPort;
DWORD				g_dwCurrTime;

BOOL				g_bTextrRistricted = FALSE;
BYTE				g_bProcState	   = _LOGIN_PROC;
BOOL				g_bAvi;

INT					g_nPaySystem = 0;

#define _WINDOW_NAME			"Legend Of Mir 3"


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MSG	msg;

	g_xMsg.LoadMsg();
	g_xItemMsg.LoadMsg( "SALEITEMDETAIL.dat" );	// 아이템 설명 추가

	// Global Variables Init.
//	g_nVersion		 = 20050111;
	g_nVersion		 = 20040922;
	g_nCertifyCode	 = 0;
	g_nServerPort	 = 0;
	g_nPreServerPort = 0;
	strcpy(g_szUserID,	   "");
	strcpy(g_szCharName,   "");
	strcpy(g_szServerName, "");
	strcpy(g_szServerIP,   "");
	strcpy(g_szPreServerIP,"");
	g_execCmds.bNotPatchd = TRUE;	// Patch ON
	
	g_nUpgradeLevel = 0; //lee wun gyo

	// ORZ CMDLINE: 최초 설정.
	if ( !ParseCmdLine() )
	{
		return -1;
	}

	g_bAvi = TRUE;

	g_xMainWnd.m_stDisplayInfo.nRefreshRate = g_execCmds.nRefreshRate;

	if ( FindWindow(NULL,_WINDOW_NAME) != NULL )
	{
		return -1;
	}

	HANDLE		hFile;
	INT			nPatchState;
	CHAR		szFullPath[MAX_PATH];
	CHAR		szFileName[MAX_PATH];

#ifdef _TEST_SERVER
#else
//	if ( g_execCmds.bNotPatchd == TRUE )
//	{
//		char szFileName[MAX_PATH];

//		GetCurrentDirectory(MAX_PATH, szFileName);

//		strcat(szFileName, ".\\Mir3FtpSelect.exe");
	
//		STARTUPINFO			si = {sizeof( STARTUPINFO ), 0,};
//		PROCESS_INFORMATION	pi = {0,};

//		if ( !CreateProcess( szFileName, lpCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi ) )
//		{
//			MessageBox(NULL, "SelPatch Error", "Legend Of Mir 3", MB_OK|MB_ICONSTOP);
//		}

//		return -1;
//	}
#endif

	BOOL bCreate;
	BOOL bLarge;

	if ( g_execCmds.bNotSelPatchd == FALSE )
	{
		bLarge = TRUE;
	}
	else
	{
		bLarge = TRUE;
	}

#ifdef _DEBUG
	if ( g_execCmds.bFullScreen )
	{
		bCreate = g_xMainWnd.Create(hInstance, _WINDOW_NAME, NULL, MAKEINTRESOURCE(IDI_ICON), _DXG_SCREENMODE_FULLSCREEN, _DXG_DEVICEMODE_PRIMARY|_DXG_DEVICEMODE_D3D);
	}
	else
	{
		bCreate = g_xMainWnd.Create(hInstance, _WINDOW_NAME, NULL, MAKEINTRESOURCE(IDI_ICON), _DXG_SCREENMODE_WINDOW, _DXG_DEVICEMODE_PRIMARY|_DXG_DEVICEMODE_D3D);
	}
#else
	bCreate = g_xMainWnd.Create(hInstance, _WINDOW_NAME, NULL, MAKEINTRESOURCE(IDI_ICON), _DXG_SCREENMODE_FULLSCREEN, _DXG_DEVICEMODE_PRIMARY|_DXG_DEVICEMODE_D3D);
#endif

	if ( bCreate == FALSE )
	{
		return -1;
	}

//	SetFontList();	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 에디트박스 생성.
	g_xChatEditBox.Create(g_xMainWnd.GetSafehInstance(), g_xMainWnd.GetSafehWnd(), 0, 0, 0, 0);
	ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_HIDE);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
    if ( FAILED(g_SoundManager.UsndInitDirectSound(g_xMainWnd.GetSafehWnd())) )
		g_SoundManager.mSndMngr_bInit = FALSE;
	else
	{
		g_SoundManager.mSndMngr_bInit = TRUE;

		g_SoundManager.ReadWaveFileList("SoundList.wwl");
		g_SoundManager.SndmngrReadBGMFileList("Bgmlist.wwl");
	}

	if ( !g_xSpriteInfo.SetInfo() )
	{
		return -1;
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Random Seed초기화.
	srand((unsigned)time(NULL));
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Windows Socket DLL을 초기화한다.
	WSAData wsd;
	if( WSAStartup( MAKEWORD(2, 2), &wsd ) != 0 )
	{
		return -1;
	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  시작하면서 로그인 프로시져로 세팅한다.
	if ( g_execCmds.bNotSelPatchd == TRUE )
	{
		g_xClientSocket.m_pxDefProc = g_xMainWnd.m_pxDefProcess = &g_xLoginProc;
		g_xLoginProc.Load();
		g_bProcState = _LOGIN_PROC;
#ifdef _DEBUG
		if ( g_execCmds.bFullScreen )
			g_xMainWnd.ResetDXG(640, 480, 16, _DXG_SCREENMODE_FULLSCREEN, _DXG_DEVICEMODE_PRIMARY|_DXG_DEVICEMODE_D3D);
		else
			g_xMainWnd.ResetDXG(640, 480, 16, _DXG_SCREENMODE_WINDOW, _DXG_DEVICEMODE_PRIMARY|_DXG_DEVICEMODE_D3D);
#else
		g_xMainWnd.ResetDXG(640, 480, 16, _DXG_SCREENMODE_FULLSCREEN, _DXG_DEVICEMODE_PRIMARY|_DXG_DEVICEMODE_D3D);
#endif
	}
	else
	{
		g_xClientSocket.m_pxDefProc = g_xMainWnd.m_pxDefProcess = &g_xSelLoginProc;
		g_xSelLoginProc.Load();
		g_bProcState = _SELLOGIN_PROC;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	DWORD dwLastTime, dwTime, dwDelay;
	dwLastTime = dwTime = dwDelay = 0;

//	WORD wClr = g_xMainWnd.ConvertColor24To16(RGB(255, 150, 150));
/*
	SYSTEMTIME	stTime1;
	GetLocalTime(&stTime1);

	CHAR pszTime1[100];
	sprintf(pszTime1, "[시작 : %d년 %d월 %d일 %d시 %d분 %d초]", 
			stTime1.wYear, stTime1.wMonth, stTime1.wDay, stTime1.wHour, stTime1.wMinute, stTime1.wSecond);
*/

	g_bTextrRistricted = CehckTextrRistricted();

	while (TRUE)
    {
        if ( PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) )
        {
            if ( 0 == GetMessage(&msg, NULL, 0, 0) )
                return (int) msg.wParam;

	        TranslateMessage(&msg);
            DispatchMessage(&msg);
		}
        else
        {
			dwTime = timeGetTime();
			g_dwCurrTime = dwTime;
			dwDelay = dwTime - dwLastTime;
			dwLastTime = dwTime;
//
//			Sleep(500);

			if ( dwDelay!=0 && g_xMainWnd.m_bIsWindowReady )
			{
				switch ( g_bProcState )
				{
				case _SELLOGIN_PROC:
					g_xSelLoginProc.RenderScene(dwDelay);
					break;
				case _LOGIN_PROC:
					g_xLoginProc.RenderScene(dwDelay);
					break;
				case _CHAR_SEL_PROC:
					g_xChrSelProc.RenderScene(dwDelay);
					break;
				case _GAME_PROC:
					{
						if ( g_OriginWndProc == GetWindowLong(g_xMainWnd.GetSafehWnd(), GWL_WNDPROC) )
						{
							if ( g_xMainWnd.m_bIsWindowActive )
							{
								g_xGameProc.RenderScene(dwDelay);
							}
							else
							{
								g_xGameProc.ProcessRecvPacket();
								g_xGameProc.ProcessDelQue();
							}
							break;
						}
					}
				}

				// 스크린샷.
				if ( GetAsyncKeyState( VK_SNAPSHOT ) )
				{
					SYSTEMTIME	stTime;
					GetLocalTime(&stTime);

					CHAR pszTime[100];
					sprintf(pszTime, "[%sServer %s] - %d/%d/%d %d:%d:%d", 
							g_szServerName, g_szCharName, stTime.wYear, stTime.wMonth, stTime.wDay, stTime.wHour, stTime.wMinute, stTime.wSecond);

					g_xMainWnd.PutsHan(NULL, 0, 0, RGB( 10,  10,  10), RGB(0, 0, 0), pszTime);
					g_xMainWnd.PutsHan(NULL, 1, 1, RGB(255, 200, 150), RGB(0, 0, 0), pszTime);

					scScreenCapture7( g_xMainWnd.GetBackBuffer() ); 
				}

				if ( FAILED(g_xMainWnd.Present()) )
				{
					g_xMainWnd.RestoreSurfaces();
				}
			}
		}
	}

	return msg.wParam;
}

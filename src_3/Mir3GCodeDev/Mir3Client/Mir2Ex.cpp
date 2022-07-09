#include "StdAfx.h"

CClientSocket		g_xClientSocket;
CWHDXGraphicWindow	g_xMainWnd;
SoundManager		g_SoundManager;
CSprite				g_xSpriteInfo;
CChatEdit			g_xChatEditBox;
CLoginProcess		g_xLoginProc;
CChrProcess			g_xChrSelProc;
CGameProcess		g_xGameProc;
CMsg				g_xMsg;

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


int FindHack()
{
/*
	HINSTANCE	hFindHackDLL;
	bool		(*pFunc)(char *);

	if ( hFindHackDLL = LoadLibrary("npchk.dll") )
	{
		if ( pFunc = (bool(*)(char*))GetProcAddress(hFindHackDLL, "CheckCRC") )
		{
			if ( pFunc("findhack.exe") )
			{
				FreeLibrary(hFindHackDLL);
				_spawnl(P_WAIT, "findhack.exe", "findhack.exe", NULL);
				return IDYES;
			}
			else
				return MessageBox(NULL, g_xMsg.GetMsg(5), "Error", MB_YESNO|MB_ICONSTOP);
		}
	}
	
	return MessageBox(NULL, g_xMsg.GetMsg(5), "Error", MB_YESNO|MB_ICONSTOP);
*/

	HINSTANCE	hFindHackDLL;
	bool		(*pFunc)(char *);
	char			*pFd;

	// �������ڴ� �Ʒ��� ����.
	pFd = "FindHack.exe";   // ���ε��� ���α׷���
	////////////////////////////////////////////////////

	g_xGameProc.m_hFindHackDll = LoadLibrary("npchk.dll");
	if (g_xGameProc.m_hFindHackDll == NULL)
	{
		return IDYES;
	}
	else 
	{
		bool (*pFunc)(char*);
		pFunc = (bool (*)(char*))GetProcAddress(g_xGameProc.m_hFindHackDll, "CheckCRC");

		if (pFunc == NULL)
		{
			return IDYES;
		}

		if (pFd != "")
		{
			if (pFunc(pFd))
			{
				if (g_xGameProc.m_hFindHackDll != NULL)
				{
					if (FreeLibrary(g_xGameProc.m_hFindHackDll )) 
						g_xGameProc.m_hFindHackDll = NULL;
					else 
						return IDYES;
				}

				int		nResult;
				nResult = spawnl(P_WAIT,"findhack.exe", "findhack.exe", NULL);

				if (nResult == 1024)
					return IDYES;
				else
					return IDYES;
			}
			else
				return IDYES;
		}
		else
			return IDYES;
	}
}

BOOL PlayTutorial()
{
	CHAR	pszVal[MAX_PATH];
	CHAR	pszFileName[MAX_PATH];

	CHAR*	pStr;

	INT		nTutorialVal;

	if ( GetCurrentDirectory(MAX_PATH, pszFileName) )
	{
		if ( pszFileName[0] != '\0' )
		{
			strcat(pszFileName, "\\Config.ini");

			nTutorialVal = GetPrivateProfileInt("Options", "Tutorial", 1, pszFileName);

			if ( nTutorialVal == 1 )
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}


VOID SetTutorialDisable()
{
	CHAR	pszVal[MAX_PATH];
	CHAR	pszFileName[MAX_PATH];

	CHAR*	pStr;

	if ( GetCurrentDirectory(MAX_PATH, pszFileName) )
	{
		if ( pszFileName[0] != '\0' )
		{
			strcat(pszFileName, "\\Config.ini");
			_itoa(0, pszVal, 10);
			WritePrivateProfileString("Options", "Tutorial", pszVal, pszFileName);
		}
	}
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MSG	msg;

	HANDLE hMutex = CreateMutex( NULL, FALSE, "Mutex_For_Single_Instance_[Legend_Of_Mir_III]" );

	if ( GetLastError() == ERROR_ALREADY_EXISTS )
	{
		//
		// �̹� �ν��Ͻ��� �� ����

		CloseHandle( hMutex );
		return 0;
	}
	
	g_xMsg.LoadMsg();

	// Global Variables Init.
	g_nVersion		 = 20050527;
	g_nCertifyCode	 = 0;
	g_nServerPort	 = 0;
	g_nPreServerPort = 0;
	strcpy(g_szUserID,	   "");
	strcpy(g_szCharName,   "");
	strcpy(g_szServerName, "");
	strcpy(g_szServerIP,   "");
	strcpy(g_szPreServerIP,"");
	g_execCmds.bNotPatchd = false;	// Patch ON


	// Tutorial Run
/*	if ( PlayTutorial() )
	{
		if ( MessageBox(NULL, g_xMsg.GetMsg(0), "Legend Of Mir 3", MB_YESNO) == IDYES )
		{
			if ( MessageBox(NULL, g_xMsg.GetMsg(1), "Legend Of Mir 3", MB_YESNO) == IDNO )
			{
				SetTutorialDisable();
			}

			STARTUPINFO			si = {sizeof( STARTUPINFO ), 0,};
			PROCESS_INFORMATION	pi = {0,};
			if ( CreateProcess("Manual.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi) )
			{
				return -1;
			}
		}
		else
		{
			if ( MessageBox(NULL, g_xMsg.GetMsg(1), "Legend Of Mir 3", MB_YESNO) == IDNO )
			{
				SetTutorialDisable();
			}
		}
	}
*/
	// ORZ CMDLINE: ���� ����.
	if ( !ParseCmdLine() )
	{
		return -1;
	}
	// * lks test

	g_bAvi = TRUE;

	g_xMainWnd.m_stDisplayInfo.nRefreshRate = g_execCmds.nRefreshRate;

/*	if ( g_execCmds.szServerIP[0] )
	{
		g_xLoginProc.SetSvrIP(g_execCmds.szServerIP);
	}
*/
	if ( FindWindow(NULL,_WINDOW_NAME) != NULL )
	{
		return -1;
	}

	HANDLE		hFile;
	INT			nPatchState;
	CHAR		szFullPath[MAX_PATH];
	CHAR		szFileName[MAX_PATH];

	if ( !g_execCmds.bNotPatchd )
	{
		char szFileName[MAX_PATH];

		GetCurrentDirectory(MAX_PATH, szFileName);
		strcat(szFileName, MIR2_PATCH_FILE_NAME);
	
		STARTUPINFO			si = {sizeof( STARTUPINFO ), 0,};
		PROCESS_INFORMATION	pi = {0,};

		if ( !CreateProcess( szFileName, lpCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi ) )
		{
			MessageBox(NULL, g_xMsg.GetMsg(3), "Legend Of Mir 3", MB_OK|MB_ICONSTOP);
		}

		return -1;
	}

	if ( FindHack() == IDOK )
	{
//		return -1;
	}

	BOOL bCreate;

	if ( g_execCmds.bFullScreen )
	{
		bCreate = g_xMainWnd.Create(hInstance, _WINDOW_NAME, NULL, MAKEINTRESOURCE(IDI_ICON), _DXG_SCREENMODE_FULLSCREEN, _DXG_DEVICEMODE_PRIMARY|_DXG_DEVICEMODE_D3D);
	}
	else
	{
		bCreate = g_xMainWnd.Create(hInstance, _WINDOW_NAME, NULL, MAKEINTRESOURCE(IDI_ICON), _DXG_SCREENMODE_WINDOW, _DXG_DEVICEMODE_PRIMARY|_DXG_DEVICEMODE_D3D);
	}

	if ( bCreate == FALSE )
	{
		return -1;
	}

//	SetFontList();	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����Ʈ�ڽ� ����.
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
//  Random Seed�ʱ�ȭ.
	srand((unsigned)time(NULL));
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Windows Socket DLL�� �ʱ�ȭ�Ѵ�.
	WSAData wsd;
	if( WSAStartup( MAKEWORD(2, 2), &wsd ) != 0 )
	{
		return -1;
	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  �����ϸ鼭 �α��� ���ν����� �����Ѵ�.
	g_xClientSocket.m_pxDefProc = g_xMainWnd.m_pxDefProcess = &g_xLoginProc;
	g_xLoginProc.Load();
	g_bProcState = _LOGIN_PROC;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	DWORD dwLastTime, dwTime, dwDelay;
	dwLastTime = dwTime = dwDelay = 0;

//	WORD wClr = g_xMainWnd.ConvertColor24To16(RGB(255, 150, 150));
/*
	SYSTEMTIME	stTime1;
	GetLocalTime(&stTime1);

	CHAR pszTime1[100];
	sprintf(pszTime1, "[���� : %d�� %d�� %d�� %d�� %d�� %d��]", 
			stTime1.wYear, stTime1.wMonth, stTime1.wDay, stTime1.wHour, stTime1.wMinute, stTime1.wSecond);
*/

	g_bTextrRistricted = CehckTextrRistricted();

	// ���ӽð� ����
	// by eriastoa 2006.05.25
	SetTimer( g_xMainWnd.GetSafehWnd(), _NOTICE_TIMER, 1000*60*60, NULL ); // 1�� : 1000	1000(1��)*60(60��)*60(60��)
	
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

//			Sleep(500);

			if ( dwDelay!=0 && g_xMainWnd.m_bIsWindowReady )
			{
				switch ( g_bProcState )
				{
				case _LOGIN_PROC:
					g_xLoginProc.RenderScene(dwDelay);
					break;
				case _CHAR_SEL_PROC:
					g_xChrSelProc.RenderScene(dwDelay);
					break;
				case _GAME_PROC:
					{

//						if ( g_xMainWnd.m_bIsWindowActive )
//						{
							g_xGameProc.RenderScene(dwDelay);

/*#ifdef _DEBUG
							SYSTEMTIME	stTime2;
							GetLocalTime(&stTime2);
							CHAR pszTime2[100];
							sprintf(pszTime2, "[���� : %d�� %d�� %d�� %d�� %d�� %d��]", 
									stTime2.wYear, stTime2.wMonth, stTime2.wDay, stTime2.wHour, stTime2.wMinute, stTime2.wSecond);
							g_xMainWnd.PutsHan(NULL, 0, 16, RGB( 200,  200,  200), RGB(0, 0, 0), pszTime2);
#endif*/

//						}
//						else
//						{
//							g_xGameProc.ProcessRecvPacket();
//							g_xGameProc.ProcessDelQue();
//						}
						break;
					}
				}

				// ��ũ����.
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

	// ���ӽð� ����
	// ������ ���÷��� by eriastoa 2006.05.25
	KillTimer( g_xMainWnd.GetSafehWnd(), _NOTICE_TIMER );

	return msg.wParam;
}

#include "StdAfx.h"

CNPGameLib			*pNpgl;
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

HINSTANCE			g_hDll;
HKCRYPT				g_hKcrypt;

#define _WINDOW_NAME			"Legend Of Mir 3"


BOOL InitGameGuard()
{
	BOOL bAppExit = FALSE;
	DWORD dwResult = pNpgl->Init();
	if (dwResult != NPGAMEMON_SUCCESS)
		{
	TCHAR msg[256];
	LPCSTR lpszMsg;

	// '6. 주요에러코드'를 참조하여 상황에 맞는 메시지를 출력해줍니다.
	switch (dwResult)
	{
		case NPGAMEMON_ERROR_EXIST:
			lpszMsg = "GameGuard is already running. Try rebooting first and executing the game again.";
			break;
		case NPGAMEMON_ERROR_GAME_EXIST:
			lpszMsg = "Game execution is duplicated or GameGuard is already running. Close the game then try again.";
			break;
		case NPGAMEMON_ERROR_INIT:
			lpszMsg = "GameGuard initialization error. Try rebooting and executing the game or close the program considered to cause a collision.";
			break;
		case NPGAMEMON_ERROR_AUTH_GAMEGUARD:
		case NPGAMEMON_ERROR_NFOUND_GG:
		case NPGAMEMON_ERROR_AUTH_INI:
		case NPGAMEMON_ERROR_NFOUND_INI:
			lpszMsg = "GameGuard file does not exist or is corrupted. Please install the GameGuard setup file.";
			break;
		case NPGAMEMON_ERROR_CRYPTOAPI:
			lpszMsg = "Window system files might be corrupted. Please reinstall the Internet Explorer(IE).";
			break;
		case NPGAMEMON_ERROR_EXECUTE:
			lpszMsg = "Fail to run GameGuard. Please reinstall the GameGuard setup file.";
			break;
		case NPGAMEMON_ERROR_ILLEGAL_PRG:
			lpszMsg = "Illegal program detected. Close all the unnecessary programs before running the game.";
			break;
		case NPGMUP_ERROR_ABORT:
			lpszMsg = "GameGuard update has been aborted. Please check the status of Internet network or personal firewall settings when unable to connect continuously.";
			break;
		case NPGMUP_ERROR_CONNECT:
		case NPGMUP_ERROR_DOWNCFG:
			lpszMsg = "Fail to connect the GameGuard update server. Please try again after a while, or check personal Firewall settings if any.";
			break;
		case NPGMUP_ERROR_AUTH:
			lpszMsg = "Fail to complete GameGuard update. Suspend Anti-Virus program temporarily and try the game, or check the settings of PC management programs if any.";
			break;
		case NPGAMEMON_ERROR_NPSCAN:
			lpszMsg = "Fail to load modules for checking virus and hacking tools. It might be a shortage of memory or virus infection.";
			break;
		default:
			// 적절한 종료 메시지 출력
			lpszMsg = "Error occurred while running GameGuard. Please send all *.erl files in GameGuard folder to game@inca.co.kr via email.";
			break;
	}

	wsprintf(msg, "GameGuard execute error : %lu", dwResult);
	MessageBox(NULL, lpszMsg, msg, MB_OK);
 
	// 게임에 맞게 종료 코드
	bAppExit = true;

	return FALSE;
    }

	return TRUE;
}


BOOL OpenKeyCrypt()
{
	BOOL	bRet = FALSE;

	g_hKcrypt = NPKOpenDriver();

	if ( g_hKcrypt > 0 )
		bRet = TRUE;
	else
	{
		DWORD	dwError = GetLastError();
		CHAR	szErrMsg[MAX_PATH];

		if ( dwError == NPK_ERROR_NOTADMIN )
			sprintf( szErrMsg, "Permission Error" );
		else
		{
			HLOCAL	hlocal = NULL;
			
			BOOL fOk = ::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, 
										NULL, 
										dwError, 
										MAKELANGID(LANG_KOREAN, SUBLANG_ENGLISH_US), 
										(PTSTR) &hlocal, 
										0, 
										NULL);
		
			if(fOk)
			{
			}
		}
	}
	return bRet;
}

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
	// 키크립트
	HINSTANCE	hFindHackDLL;
	bool		(*pFunc)(char *);
	char			*pFd;
	
	// 전달인자는 아래와 같다.
	pFd = "FindHack.exe";   // 파인드핵 프로그램명
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
		// 이미 인스턴스가 떠 있음

		CloseHandle( hMutex );
		return 0;
	}

	g_xMsg.LoadMsg();

	// Global Variables Init.
	g_nVersion		 = 20040922;
	g_nCertifyCode	 = 0;
	g_nServerPort	 = 0;
	g_nPreServerPort = 0;
	strcpy(g_szUserID,	   "");
	strcpy(g_szCharName,   "");
	strcpy(g_szServerName, "");
	strcpy(g_szServerIP,   "");
	strcpy(g_szPreServerIP,"");
	g_execCmds.bNotPatchd = false;	// Patch ON

	g_nUpgradeLevel = 0; //lee wun gyo


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
	// ORZ CMDLINE: 최초 설정.
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

#ifndef _TEST_SERVER
	//~Mir3Patch.dat		 <-- 이 화일이 있으면 Mir3Patch.exe로 이름을 바꾸고 그것을 실행한다.
	nPatchState = 1;
	GetCurrentDirectory(MAX_PATH,szFullPath);
	GetCurrentDirectory(MAX_PATH,szFileName);
	strcat(szFullPath,MIR2_PATCH_DAT_NAME);
	strcat(szFileName,MIR2_PATCH_FILE_NAME);
	hFile = CreateFile(szFullPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(GetLastError()==ERROR_FILE_NOT_FOUND)
	{
		// Dat 화일이 없다.
		hFile = CreateFile(szFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if(GetLastError()==ERROR_FILE_NOT_FOUND)
		{	
			// Exe 화일이 없다.
			MessageBox(g_xMainWnd.GetSafehWnd(), g_xMsg.GetMsg(2), "Information", MB_OK);
			nPatchState = 0;
		}
		else
		{	
			// Exe 로 Dat 만들기
			CloseHandle(hFile);
			DeleteFile(szFullPath);
			CopyFile(szFileName,szFullPath,TRUE);
		}
		CloseHandle(hFile);
	}
	else
	{
		// Dat 화일이 있다.
		hFile = CreateFile(szFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if(GetLastError()==ERROR_FILE_NOT_FOUND)
		{	
			// Exe 화일이 없다.
			CloseHandle(hFile);
			DeleteFile(szFileName);
			CopyFile(szFullPath,szFileName,TRUE);
		}
	}
#endif
	CHAR szExePath[MAX_PATH], szPatchPath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,szExePath);

	sprintf( szPatchPath, "%s\\Mir3Patch.exe", szExePath);
	sprintf( szExePath, "%s\\Mir3.exe", szExePath);
	
/*
	if ( NPKGetAppCompatFlag(szPatchPath) != apcfNone)
	{	
		NPKSetAppCompatFlag(szPatchPath, apcfNone);
	}

	if ( NPKGetAppCompatFlag(szExePath) != apcfNone)
	{	
		NPKSetAppCompatFlag(szExePath, apcfNone);
	}
*/
	if ( !g_execCmds.bNotPatchd )
	{
		char szFileName[MAX_PATH];

		GetCurrentDirectory(MAX_PATH, szFileName);

#ifdef _TEST_SERVER
		strcat(szFileName, MIR2_TS_PATCH_FILE_NAME);
#else
		strcat(szFileName, MIR2_PATCH_FILE_NAME);
#endif
	
		STARTUPINFO			si = {sizeof( STARTUPINFO ), 0,};
		PROCESS_INFORMATION	pi = {0,};

		if ( !CreateProcess( szFileName, lpCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi ) )
		{
			MessageBox(NULL, g_xMsg.GetMsg(3), "Legend Of Mir 3", MB_OK|MB_ICONSTOP);
		}

		return -1;
	}
/*	pNpgl = new CNPGameLib("Mir3UK");

	if ( InitGameGuard() == FALSE)
	{
		return -1;
	}
*/
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
// 에디트박스 생성.
	g_xChatEditBox.Create(g_xMainWnd.GetSafehInstance(), g_xMainWnd.GetSafehWnd(), 0, 0, 0, 0);
	ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_HIDE);

	GetCurrentDirectory(MAX_PATH,szExePath);
/*	NPKSetDrvPath(szExePath);
	if ( OpenKeyCrypt() )
	{
		int ntset = 0;
	}

	if ( NPKRegCryptMsg(g_hKcrypt, g_xChatEditBox.GetSafehWnd(), WM_USER +1094) )
	{
		int sdf = 0;
	}
*/
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
	sprintf(pszTime1, "[시작 : %d년 %d월 %d일 %d시 %d분 %d초]", 
			stTime1.wYear, stTime1.wMonth, stTime1.wDay, stTime1.wHour, stTime1.wMinute, stTime1.wSecond);
*/

	g_bTextrRistricted = CehckTextrRistricted();

	// 게임가드 핸들 호출
//	pNpgl->SetHwnd(g_xMainWnd.GetSafehWnd());

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

						if ( g_xMainWnd.m_bIsWindowActive )
						{
							g_xGameProc.RenderScene(dwDelay);
/*							g_xMainWnd.PutsHan(NULL, 0, 0, RGB(200, 200, 200), RGB(0, 0, 0), pszTime1);
							SYSTEMTIME	stTime2;
							GetLocalTime(&stTime2);
							CHAR pszTime2[100];
							sprintf(pszTime2, "[현재 : %d년 %d월 %d일 %d시 %d분 %d초]", 
									stTime2.wYear, stTime2.wMonth, stTime2.wDay, stTime2.wHour, stTime2.wMinute, stTime2.wSecond);
							g_xMainWnd.PutsHan(NULL, 0, 16, RGB( 200,  200,  200), RGB(0, 0, 0), pszTime2);
*/						}
						else
						{
							g_xGameProc.ProcessRecvPacket();
							g_xGameProc.ProcessDelQue();
						}
						break;
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

//	if (pNpgl) delete pNpgl;

	return msg.wParam;
}

bool CALLBACK NPGameMonCallback(DWORD dwMsg, DWORD dwArg)
{
	TCHAR msg[128];
	LPCTSTR lpszMsg = NULL;
	BOOL	bAppExit = FALSE;

	GG_AUTH_DATA	m_AuthData;


	CHAR szTemp[MAX_PATH];

	DWORD dwFont = GetChatColor(_CHAT_COLOR3);
	DWORD dwBack = GetChatColor(_CHAT_COLOR8);

	switch (dwMsg)
	{
		case NPGAMEMON_CHECK_CSAUTH2:
			memcpy(&m_AuthData, (PVOID)dwArg, sizeof(GG_AUTH_DATA));
			
//			g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, "send!");

			sprintf( szTemp, "%d/%d/%d/%d", m_AuthData.dwIndex, m_AuthData.dwValue1, m_AuthData.dwValue2, m_AuthData.dwValue3);
			g_xClientSocket.SendGameGuard(szTemp);

		// 서버로 인증 패킷을 전송
//			SendToServer(&m_AuthData);
			return true;

		case NPGAMEMON_COMM_ERROR:
		case NPGAMEMON_COMM_CLOSE:
			bAppExit = true;
			return false;
		case NPGAMEMON_INIT_ERROR:
			bAppExit = true; // 종료 코드
			wsprintf(msg, "GameGuard initialization error : %lu", dwArg);
			lpszMsg = msg;
			break;
		case NPGAMEMON_SPEEDHACK:
			bAppExit = true; // 종료 코드
			lpszMsg = "Speedhack detected.";
			break;
		case NPGAMEMON_GAMEHACK_KILLED:
			// bAppExit = true; // 종료 코드, 종료 또는 계속 진행
			lpszMsg = "Gamehack detected.";
			break;
		case NPGAMEMON_GAMEHACK_DETECT:
			bAppExit = true; // 종료 코드
			lpszMsg = "Gamehack detected.";
			break;
		case NPGAMEMON_GAMEHACK_DOUBT:
			bAppExit = true; // 종료 코드
			lpszMsg = "GameGuard file corrupted.";
			break;
	}

	if (lpszMsg)
	{
		MessageBox(g_xMainWnd.GetSafehWnd(), lpszMsg, "nProtect GameGuard", MB_OK); // 또는 게임 UI 사용
	}

	// 게임 종료시에만 false를 리턴
	if (bAppExit)
	{
		SendMessage(g_xMainWnd.GetSafehWnd(), WM_DESTROY, NULL, NULL);			
		return false;
	}

    return true;
}

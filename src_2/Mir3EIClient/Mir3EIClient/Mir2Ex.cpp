#include "StdAfx.h"

CMirSound			g_xSound;
CWHDXGraphicWindow	g_xMainWnd;
CLoginProcess		g_xLoginProc;
CCharacterProcess	g_xChrSelProc;
CGameProcess		g_xGameProc;
CSprite				g_xSpriteInfo;
CChatEdit			g_xChatEditBox;
CClientSocket		g_xLoginSocket;

//TEAM
CTeamManage			g_xTeamManage;

INT					g_nCertifyCode;
char				g_szUserID[20];
char				g_szCharName[20];
char				g_szServerIP[16];
INT					g_nServerPort;
char				g_szLoginServerIP[16];
INT					g_nLoginServerPort;

INT					g_nVersion;


BYTE				g_bProcState = _LOGIN_PROC;


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MSG	msg;

	g_xMainWnd.Create(hInstance, "Legend Of Mir 3", NULL, MAKEINTRESOURCE(IDI_ICON), _DXG_SCREENMODE_WINDOW, _DXG_DEVICEMODE_PRIMARY|_DXG_DEVICEMODE_D3D|_DXG_DEVICEMODE_ZBUFFER);
	ShowWindow(g_xMainWnd.GetSafehWnd(), SW_HIDE);

	g_xSound.InitMirSound(g_xMainWnd.GetSafehWnd());
	g_xSpriteInfo.SetInfo();

	g_xChatEditBox.Create(g_xMainWnd.GetSafehInstance(), g_xMainWnd.GetSafehWnd(), 0, 0, 0, 0);
	ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_HIDE);

	//  Random Seed초기화.
	srand((unsigned)time(NULL));

	// Windows Socket DLL을 초기화한다.
	WSAData wsd;
	if( WSAStartup( MAKEWORD(2, 2), &wsd ) != 0 )
		return -1;

	//login
	g_xLoginSocket.m_pxDefProc = g_xMainWnd.m_pxDefProcess = &g_xLoginProc;
	g_xLoginProc.Load();
	g_bProcState = _LOGIN_PROC;

	g_nVersion = 20030704;//경굶뵀


	DWORD dwLastTime, dwTime, dwDelay;
	dwLastTime = dwTime = dwDelay = 0;


/*	CAirWave m_xWave;
	m_xWave.InitAirWave();
*/
//	m_xWave.DropAirWaveMap( 180, 50, 40, -100 );


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
			dwDelay = dwTime - dwLastTime;
			dwLastTime = dwTime;

			if ( dwDelay!=0 /*&& g_xMainWnd.m_bIsWindowActive && g_xMainWnd.m_bIsWindowReady */)
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
				//ydq	g_xGameProc.RenderScene(dwDelay);
					g_xTeamManage.RenderScene(dwDelay);
					break;
				}
				Sleep(15);//for debug

				if ( FAILED(g_xMainWnd.Present()) )
				{
					g_xMainWnd.RestoreSurfaces();
				}
			}
		}
	}

	return msg.wParam;
}

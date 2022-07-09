#ifndef _EXTERN_H
#define _EXTERN_H

extern CClientSocket		g_xClientSocket;
extern CWHDXGraphicWindow	g_xMainWnd;
extern SoundManager			g_SoundManager;
extern CSprite				g_xSpriteInfo;
extern CChatEdit			g_xChatEditBox;
extern CLoginProcess		g_xLoginProc;
extern CChrProcess			g_xChrSelProc;
extern CGameProcess			g_xGameProc;

extern BYTE					g_bProcState;
extern INT					g_nCertifyCode;			// Global Certification Code
extern char					g_szUserID[25];			// Global User ID
extern char					g_szServerIP[16];		// Global Current Connection Server IP
extern INT					g_nServerPort;			// Global Current Connection Server Port
extern BYTE					g_nUpgradeLevel;   //lee wun gyo
extern char					g_szCharName[25];		// Global Charector Name
extern char					g_szServerName[20];
extern INT					g_nVersion;				// Global Client Program Version Number
extern char					g_szPreServerIP[16];	// Global Previous Connection Server IP
extern INT					g_nPreServerPort;
extern DWORD				g_dwCurrTime;			// Current Time;
extern BOOL					g_bTextrRistricted;
extern INT					g_nPaySystem;			// 요금 관련
extern CMsg					g_xMsg;


#endif // _EXTERN_H
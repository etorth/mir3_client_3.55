#ifndef _EXTERN_H
#define _EXTERN_H

extern CWHDXGraphicWindow	g_xMainWnd;
extern CLoginProcess		g_xLoginProc;
extern CCharacterProcess	g_xChrSelProc;
extern CGameProcess			g_xGameProc;
extern CSprite				g_xSpriteInfo;
extern CChatEdit			g_xChatEditBox;
extern CMirSound			g_xSound;

extern CClientSocket		g_xLoginSocket;//登陆和选角专使用
//TEAM
extern CTeamManage			g_xTeamManage;

extern BYTE					g_bProcState;
extern INT					g_nCertifyCode;			// Global Certification Code
extern char					g_szUserID[20];			// Global User ID
extern char					g_szServerIP[16];		// Global Current Connection Server IP
extern INT					g_nServerPort;			// Global Current Connection Server Port
extern char					g_szCharName[20];		// Global Charector Name
extern INT					g_nVersion;				// Global Client Program Version Number

extern char					g_szLoginServerIP[16];
extern INT					g_nLoginServerPort;

#endif // _EXTERN_H
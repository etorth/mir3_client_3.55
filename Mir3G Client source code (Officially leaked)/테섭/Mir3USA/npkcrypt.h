#ifndef NPKCRYPT_H
#define NPKCRYPT_H

#ifndef NPKAPI
#define NPKAPI	extern "C" __declspec(dllimport)
#endif

typedef INT HKCRYPT;
typedef VOID (CALLBACK *FCryptAction)(PVOID, LPBYTE, DWORD);

#define KEYHOOK_NONE		0
#define KEYHOOK_INTERRUPT	1
#define KEYHOOK_FILTER		2
#define KEYHOOK_DEFAULT		(KEYHOOK_INTERRUPT | KEYHOOK_FILTER)

#define WM_HOOKNOTIFY		(WM_APP+14)

// ���� �����ڵ� ����
#define NPK_ERROR_BASE			0x20000000
#define NPK_ERROR_NOTADMIN		0xE0010001
#define NPK_ERROR_DRIVERVERSION	0xE0010002
#define NPK_ERROR_VERIFYVERSION	0xE0010003
#define NPK_ERROR_KEYSTATUSFAIL	0xE0010004

#define NPKSECOPT_NONE			0
#define NPKSECOPT_CRYPTRC4		2
#define NPKSECOPT_UPPERCASE		4

typedef struct _KEY_LOGGER_INFO
{
	BOOLEAN		bExistIdtHooker;
	BOOLEAN		bExistDebugger;
	ULONG 		lReserved;
	UCHAR 		szReserved[32];
} KEY_LOGGER_INFO, *PKEY_LOGGER_INFO;

typedef enum _APPCOMPATFLAG
{
	apcfNone = -1,
	apcfWin95,
	apcfWin98,
	apcfWinNT4SP5,
	apcfWin2000
} APPCOMPATFLAG, *PAPPCOMPATFLAG;

NPKAPI
HKCRYPT WINAPI NPKOpenDriver();

NPKAPI
HKCRYPT WINAPI NPKOpenDriverEx(UINT nHookType);

NPKAPI
BOOL WINAPI NPKCloseDriver(HKCRYPT hKCrypt);

NPKAPI
VOID WINAPI NPKSetDrvPath(PSTR szPath);

NPKAPI
BOOL WINAPI NPKLoadAtStartup(BOOL bLoadAtStartUp);

NPKAPI
BOOL WINAPI NPKRegCryptMsg(HKCRYPT hKCrypt, HWND hWnd, UINT nCallBackMsg);

NPKAPI
BOOL WINAPI NPKRegCryptFunc(HKCRYPT hKCrypt, HWND hWnd, FCryptAction fnCryptAction, PVOID pUserData);

NPKAPI
BOOL WINAPI NPKUnregCrypt(HKCRYPT hKCrypt, HWND hWnd);

NPKAPI
BOOL WINAPI NPKSetKeyMode(DWORD dwMode);

NPKAPI
BOOL WINAPI NPKSetKbdLock(BOOL bLock);

NPKAPI
APPCOMPATFLAG WINAPI NPKGetAppCompatFlag(LPCTSTR szFileName);

NPKAPI
BOOL WINAPI NPKSetAppCompatFlag(LPCTSTR szFileName, APPCOMPATFLAG apcfNewValue);

NPKAPI
VOID WINAPI NPKRegNotifyWindow(HKCRYPT hkcrypt, HWND hWnd);

NPKAPI
INT NPKGetWindowText(HWND hWnd, LPTSTR lpString, INT nMaxCount);

NPKAPI
BOOL WINAPI NPKSetSecOpt(HKCRYPT hKCrypt, HWND hWnd, DWORD dwSecOpt);

NPKAPI
DWORD WINAPI NPKGetSecOpt(HKCRYPT hKCrypt, HWND hWnd);

#endif

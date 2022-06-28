#ifndef _GFUN_H_
#define _GFUN_H_



// 여러 Class에서 쓸수 있는 함수및 구조체를 공용으로 모아놓은 파일이다.

typedef struct tagCHAT
{
	DWORD	dwFontColor;
	DWORD	dwBackColor;
	CHAR	pszChat[_MAX_STRING_LEN];
}CHAT, *LPCHAT;

typedef struct tagITEMSTATE
{
	DWORD	dwFont;
	DWORD	dwBack;
	CHAR	pszDesc[60];
}ITEMSTATE, *LPITEMSTATE;

typedef struct tagFontList
{
	CHAR	pszDesc[MAX_PATH];
}FONTLIST, *LPFONTLIST;

// gameguard auth data
typedef struct _GG_AUTH_DATA
{
	DWORD dwIndex;
	DWORD dwValue1;
	DWORD dwValue2;
	DWORD dwValue3;
} GG_AUTH_DATA, *PGG_AUTH_DATA;


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
typedef struct tagEVENTIMG
{
	INT		nType;
	INT		nEventID;
	WORD	wFrameNum;
	WORD	wOutDelay;

	DWORD   dwTick;

	DWORD	dwLifeTime;

	INT		nTileX;
	INT		nTileY;

	BOOL	bUseAlpha;
}EVENTIMG, *LPEVENTIMG;
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

typedef struct tagGROUPPOS
{
	INT		nID;
	INT		nPosX;
	INT		nPosY;
	BOOL	bMon;
	DWORD	dwLastRecvTick;
}GROUPPOS, *LPGROUPPOS;


typedef struct tagTEXTUREFILE
{
	WORD					wFileIdx;
	WORD					wImgIdx;
	LPDIRECTDRAWSURFACE7	lpddsTextr;
}TEXTUREFILE, *LPTEXTUREFILE;


typedef struct tagDICEINFO
{
	BOOL					bSetted;
	INT						nCurrFrm;
	INT						nPlayTime;
	INT						nCurrDelay;
	INT						nTotalDelay;
	INT						nFrameDelay;
	INT						nResult;
	INT						nPosX;
	INT						nPosY;
}DICEINFO, *LPDICEINFO;


typedef struct tagINFOSHOP
{
	BOOL	bSetted;
	CHAR	pszAddr[MAX_PATH];
	INT		nPort;

	BOOL	bIsKornet;
	CHAR	pszCPIPcode[MAX_PATH];
	CHAR	pszSVCcode[MAX_PATH];
	CHAR	pszLoginID[MAX_PATH];
	CHAR	pszCheckSum[MAX_PATH];

	tagINFOSHOP()
	{
		bSetted = FALSE;
		
		ZeroMemory(pszAddr, MAX_PATH);
		nPort = -1;

		bIsKornet = FALSE;
		ZeroMemory(pszCPIPcode, MAX_PATH);
		ZeroMemory(pszSVCcode, MAX_PATH);
		ZeroMemory(pszLoginID, MAX_PATH);
		ZeroMemory(pszCheckSum, MAX_PATH);
	};
}INFOSHOP, *LPINFOSHOP;


typedef struct tagCLIENTADDSELLITEM
{
	CHAR			szItemName[25];
	INT				nItemMakeIdx;
	INT				nPrice;
	CHAR			szDesc[121];
}CLIENTADDSELLITEM, *LPCLIENTADDSELLITEM;


typedef struct tagCLIENTNEWDHL
{
	CHAR			szName[25];
	INT				nMoney;
	CHAR			szSendItem[25];
	INT				nItemMakeIndex;
	CHAR			szTitle[31];
	CHAR			szMemo[501];
}CLIENTNEWDHL, *LPCLIENTNEWDHL;

typedef struct tagCLIENTDHLTITLE
{
	INT				nIndex;
	WORD			wDhlType;
	WORD			wReadCheck;
	CHAR			szWho[25];
	CHAR			szTitle[31];
	CHAR			szSentDate[15];
}CLIENTDHLTITLE, *LPCLIENTDHLTITLE;

static INFOSHOP	g_stInfoShop;

// 추석맞이 이벤트용.
extern BYTE g_bWeaponEnergyColor[7][3];

extern INT	g_nWeaponExpTable[];
extern INT	g_nWeaponLevelTable[36];

extern char  g_pszGood[];
extern char  g_pszFail[];
extern char  g_pszLng[];
extern char  g_pszUlng[];
extern char  g_pszWid[];
extern char  g_pszUWid[];
extern char  g_pszFir[];
extern char  g_pszUFir[];
extern char  g_pszUPwr[];
extern char  g_pszUDig[];

// 추가무공.
extern char  g_pszRnd[];
extern char  g_pszURnd[];
extern char  g_pszBks[];
extern char  g_pszUBks[];
extern char  g_pszMan[];
extern char  g_pszUMan[];
extern char  g_pszHRnd[];
extern char  g_pszUHRnd[];
extern char  g_pszUHPwr[];
extern char  g_pszHLng[];
extern char  g_pszHMan[];
extern char  g_pszUHMan[];


extern CHAR** g_ppszClientMsg;
extern INT    g_ClientMsgNum;
BOOL SetClientMsgList();
VOID DestroyClientMsgList();

DWORD GetChatColor(BYTE bIdx);
DWORD GetUserNameColor(BYTE bIdx);
WORD GetMonDyeingColor(BYTE bIdx);
INT	GetRandomNum(INT nFrom, INT nTo);
BOOL CehckTextrRistricted();
VOID GetNumWithComma(INT nNum, CHAR* pszOut = NULL);

/*
static CList<FONTLIST>	g_xFontList;
static INT				g_nFontNum;
VOID SetFontList();
VOID ReleaseFontList();
VOID SetMir3DefFont(BOOL bPlus = TRUE);
*/

#define FLOG0( file, txt ) \
{\
FILE *fp = fopen( file, "ab" );\
if ( fp )\
{\
	fprintf( fp, "%s\r\n", txt );\
	fclose( fp );\
}\
}\

#define FLOG1( file, txt, int1 ) \
{\
FILE *fp = fopen( file, "ab" );\
if ( fp )\
{\
	fprintf( fp, "%s [%d]\r\n", txt, int1 );\
	fclose( fp );\
}\
}\

#define FLOG2( file, txt, int1, int2 ) \
{\
FILE *fp = fopen( file, "ab" );\
if ( fp )\
{\
	fprintf( fp, "%s [%d] [%d]\r\n", txt, int1, int2 );\
	fclose( fp );\
}\
}\

#define FLOG2STR( file, txt, int1, str2 ) \
{\
FILE *fp = fopen( file, "ab" );\
if ( fp )\
{\
	fprintf( fp, "%s [%d] [%s]\r\n", txt, int1, str2 );\
	fclose( fp );\
}\
}\

INT   RoundFunc(INT nDividend, INT nDivisor);

VOID  DestroyFindHack();

#endif // _GFUN_H_


#define _DEFBLOCKSIZE		16
#define _FEATURESIZE		6
#define _CHARDESCSIZE		22
//#define _FEATURESIZEEX		8
#define _FEATURESIZEEX		14	// 추가의상 이펙트 nEft 추가
//#define _FEATURESIZEEX		19		// 아이콘 nIcon
#define _MESSAGEBODYWLSIZE  22

typedef struct tag_TDEFAULTMESSAGE
{
	int		nRecog;
	WORD	wIdent;
	WORD	wParam;
	WORD	wTag;
	WORD	wSeries;
} _TDEFAULTMESSAGE, *_LPTDEFAULTMESSAGE;

typedef struct tag_TSHORTMSSEAGE
{
	WORD	wIdent;
	WORD	wMsg;
} _TSHORTMSSEAGE, *_LPTSHORTMSSEAGE;


typedef struct tagPACKETMSG
{
	_TDEFAULTMESSAGE	stDefMsg;
	CHAR				szEncodeData[_MAX_STRING_LEN];
}PACKETMSG, *LPPACKETMSG;

typedef struct tag_TMSGHEADER
{
	int		nCode;
	int		nSocket;
	WORD	wUserGateIndex;
	WORD	wIdent;
	WORD	wUserListIndex;
	WORD	wTemp;
	int		nLength;
} _TMSGHEADER, *_LPTMSGHEADER;

/*typedef struct tagTGateToSvrHeader
{
	char	szPrefix;				// Always is '%'
	char	szID;					// Identifier.
	BYTE	btGateIndex;			// Gate server index.
	int		nSocket;				// Socket(owner of msg) in gate server.
	WORD	wDataLength;			// Length of msg that following header.
} TGateToSvrHeader, *LPTGateToSvrHeader; 

#define GTS_HEADER_SIZE		sizeof(TGateToSvrHeader) */

void WINAPI fnMakeDefMessage(_LPTDEFAULTMESSAGE lptdm, WORD wIdent, int nRecog, WORD wParam, WORD wTag, WORD wSeries);
int  WINAPI fnEncode6BitBuf(unsigned char *pszSrc, char *pszDest, int nSrcLen, int nDestLen);
int  WINAPI fnDecode6BitBuf(char *pszSrc, char *pszDest, int nDestLen);
int  WINAPI fnDecode6BitBufOriginal(char *pszSrc, char *pszDest, int nDestLen);
int  WINAPI fnEncodeMessage(_LPTDEFAULTMESSAGE lptdm, char *pszBuf, int nLen);
int  WINAPI fnDecodeMessage(_LPTDEFAULTMESSAGE lptdm, char *pszBuf);

int  WINAPI fnDecodeMessageGameProcess(_LPTDEFAULTMESSAGE lptdm, char *pszBuf);  //이운교 20051031
int  WINAPI fnDecode6BitBufGameMessage(char *pszSrc, char *pszDest, int nDestLen);	//이운교 20051031
int  WINAPI fnEncode6BitBufGameMessage(unsigned char *pszSrc, char *pszDest, int nSrcLen, int nDestLen); //이운교 20051031
int  WINAPI fnEncode6BitBufGameString(unsigned char *pszSrc, char *pszDest, int nSrcLen, int nDestLen); //이운교 20051031

#include "StdAfx.h"


char  g_pszGood[]	= "GOOD";
char  g_pszFail[]	= "FAIL";
char  g_pszLng[]	= "LNG";
char  g_pszUlng[]	= "ULNG";
char  g_pszWid[]	= "WID";
char  g_pszUWid[]	= "UWID";
char  g_pszFir[]	= "FIR";
char  g_pszUFir[]	= "UFIR";
char  g_pszUPwr[]	= "PWR";
char  g_pszUDig[]	= "DIG";
// 추가무공.
char  g_pszRnd[]	= "RND";
char  g_pszURnd[]	= "URND";
char  g_pszBks[]	= "BKS";
char  g_pszUBks[]	= "UBKS";
char  g_pszMan[]	= "MAN";
char  g_pszUMan[]	= "UMAN";
// 고급무공
char  g_pszHRnd[]	= "HRND";
char  g_pszUHRnd[]	= "UHRND";
char  g_pszUHPwr[]	= "HPWR";
char  g_pszHLng[]	= "HLNG";
char  g_pszHMan[]	= "HMAN";
char  g_pszUHMan[]	= "UHMAN";
char  g_pszHWID[]	= "HWID";
char  g_pszUHWID[]	= "UHWID";

CHAR** g_ppszClientMsg = NULL;
INT    g_ClientMsgNum = 0;

BYTE g_bWeaponEnergyColor[7][3] = 
{
	{240, 180, 100},
	{100, 140, 190},
	{ 50,  70, 200},
	{140, 200, 150},
	{200, 200, 200},
	{160, 100, 180},
	{200, 220, 130}
};

INT	g_nWeaponExpTable[] = 
{
	180000, 180000, 180000, 240000, 240000, 240000, 240000, 300000, 300000, 300000, 300000, 
	360000, 360000, 360000, 360000, 420000, 420000, 420000, 420000, 480000, 480000, 480000, 480000,
	540000, 540000, 540000, 540000, 600000, 600000, 600000, 600000, 660000, 660000, 660000, 660000, 720000
};

INT g_nWeaponLevelTable[36] = 
{
	0, 3, 6, 9, 13, 17, 21, 25, 30, 35, 40, 45, 51, 57, 63, 69, 76, 83, 90, 97, 105, 113, 121, 129, 138, 147, 156, 165, 175, 185, 195, 205, 216, 227, 238, 249
};

DWORD GetChatColor(BYTE bIdx)
{
	DWORD dwClr = 0;

	switch ( bIdx )
	{
	case _CHAT_COLOR1:		dwClr = RGB(  0,   0,   0);		break;
	case _CHAT_COLOR2:		dwClr = RGB( 10,  10,  10);		break;
	case _CHAT_COLOR3:		dwClr = RGB(255, 255, 255);		break;
	case _CHAT_COLOR4:		dwClr = RGB(255,   0,   0);		break;
	case _CHAT_COLOR5:		dwClr = RGB(  0, 255,   0);		break;
	case _CHAT_COLOR6:		dwClr = RGB(150, 150, 255);		break;
	case _CHAT_COLOR7:		dwClr = RGB(255, 255,  80);		break;
	case _CHAT_COLOR8:		dwClr = RGB(255, 128,   0);		break;
	}

	return dwClr;
}


WORD GetMonDyeingColor(BYTE bIdx)
{
	WORD wClr = 0XFFFF;

	switch ( bIdx )
	{
	case 0:		wClr = g_xMainWnd.ConvertColor24To16(RGB(255, 255, 255));		break;	// 백색.
	case 1:		wClr = g_xMainWnd.ConvertColor24To16(RGB(100, 100, 200));		break;	// 적갈색.
	case 2:		wClr = g_xMainWnd.ConvertColor24To16(RGB(180,  90,  90));		break;	// 검푸른색.
	case 3:		wClr = g_xMainWnd.ConvertColor24To16(RGB( 70, 155, 255));		break;	// 황금색.
	case 4:		wClr = g_xMainWnd.ConvertColor24To16(RGB(255, 128, 128));		break;	// 푸른색계통.
	case 5:		wClr = g_xMainWnd.ConvertColor24To16(RGB(120, 120, 255));		break;	// 적색계통.
	case 6:		wClr = g_xMainWnd.ConvertColor24To16(RGB(100, 100, 100));		break;	// 회색.
	case 7:		wClr = g_xMainWnd.ConvertColor24To16(RGB(180, 180, 180));		break;	// 암회색.
	case 8:		wClr = g_xMainWnd.ConvertColor24To16(RGB(180, 180, 100));		break;	// 연푸른색.
	case 9:		wClr = g_xMainWnd.ConvertColor24To16(RGB(116,  54, 234));		break;	// 붉은색계열.
	}

	return wClr;
}



DWORD GetUserNameColor(BYTE bIdx)
{
	DWORD dwClr = 0;

	switch ( bIdx )
	{
	case _USER_NAMECLR1:		dwClr = RGB(255, 255, 255);		break;	// 255
	case _USER_NAMECLR2:		dwClr = RGB(255, 255,   0);		break;	// 251
	case _USER_NAMECLR3:		dwClr = RGB(255,   0,   0);		break;	// 249
	case _USER_NAMECLR4:		dwClr = RGB(255,   0,   0);		break;	// 125
	case _USER_NAMECLR5:		dwClr = RGB(165,  99,  57);		break;	// 47
	case _USER_NAMECLR6:		dwClr = RGB(  0,   0, 255);		break;	// 180
	case _USER_NAMECLR7:		dwClr = RGB(239, 107,   0);		break;	// 69
	case _USER_NAMECLR8:		dwClr = RGB(  0, 148,   0);		break;	// 221
	case _USER_NAMECLR9:		dwClr = RGB(  0, 255, 255);		break;	// 254
	case _USER_NAMECLR10:		dwClr = RGB(140, 214, 239);		break;	// 147
	case _USER_NAMECLR11:		dwClr = RGB( 57, 181, 239);		break;	// 154
	case _USER_NAMECLR12:		dwClr = RGB(119, 136, 255);		break;	// 229
	case _USER_NAMECLR13:		dwClr = RGB(  0, 123, 222);		break;	// 168
	case _USER_NAMECLR14:		dwClr = RGB(  0,   0, 255);		break;	// 252
	}

	return dwClr;
}


INT	GetRandomNum(INT nFrom, INT nTo)
{
	INT nRandNum = 0;

	INT nRand = ((INT)rand()-(INT)rand());

	if ( nRand < 0 )
		nRand = -nRand;

	nRandNum = nRand % (nTo-nFrom+1) + nFrom;

	return nRandNum;
}


BOOL CehckTextrRistricted()
{	
    D3DDEVICEDESC7		ddDesc;

    if ( SUCCEEDED(g_xMainWnd.Get3DDevice()->GetCaps(&ddDesc)) )
	{
		// 정사각형의 텍스춰.
		if ( ddDesc.dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_SQUAREONLY )
		{	
			return TRUE;
		}

		// 256*256.
		if ( ddDesc.dwMaxTextureWidth <= 256 || ddDesc.dwMaxTextureHeight <= 256 )
		{
			return TRUE;
		}
	}	

	return FALSE;
}


INT RoundFunc(INT nDividend, INT nDivisor)
{
	if ( nDivisor )
	{
		return (INT)(((FLOAT)nDividend/(FLOAT)nDivisor) + 0.5f);
	}

	return 0XFFFF;
}


VOID GetNumWithComma(INT nNum, CHAR* pszOut)
{
	NUMBERFMT nFmt = { 0, 0, 3, ".", ",", 1 };

	CHAR pszNum[MAX_PATH];
	itoa(nNum, pszNum, 10);

	GetNumberFormat(NULL, NULL, pszNum, &nFmt, pszOut, MAX_PATH);
}



VOID DestroyFindHack()
{
// find hack관련.
	HWND hWnd = NULL;
	hWnd = FindWindow( "TfrmNPMON", "WWW.NPROTECT.COM" );
	if ( hWnd != NULL )
	{
		UINT Msg = WM_USER+10010;
		SendMessage(hWnd, Msg, 0, 0);
	}
}

BOOL SetClientMsgList()
{
	DestroyClientMsgList();

	// 암호화 루틴해제.
	char* pszBuf = NULL;

	crypto_seed s = {(char) 0xF0, (char) 0x39, (char) 0xAB, (char) 0x8E, 0x9FDE1A93};
	crypto::setSeed( &s );

	FILE *fp = fopen( "CMList.Dat", "rb" );

	if ( !fp )
	{
		MessageBox(NULL, (char*)"Message List File Error.", "[Error] - Legend of Mir III", MB_ICONERROR);
		return FALSE;
	}

	int len = _filelength( _fileno( fp ) );
	pszBuf = new char[ len ];

	if ( !pszBuf )
	{
		fclose( fp );
		delete [] pszBuf;
		MessageBox(NULL, (char*)"Message List File Error.", "[Error] - Legend of Mir III", MB_ICONERROR);
		return FALSE;
	}

	fread( pszBuf, 1, len, fp );
	fclose( fp );

	if ( !crypto::decrypt( (unsigned char *)pszBuf, len ) )
	{
		delete[] pszBuf;
		MessageBox(NULL, (char*)"Message List File Error.", "[Error] - Legend of Mir III", MB_ICONERROR);
		return FALSE;
	}

	// 데이타적용.
	CHAR  pszMsgNum[20];
	ZeroMemory(pszMsgNum, 20);

	CHAR* pszComment  = NULL;
	CHAR* pszLineNext = NULL;
	CHAR* pszLine	  = pszBuf + 8;		// Seed를 건너뛴다.

	INT	nLineLen = 0;
	INT	nMsgNum	 = 0;

	while ( pszLineNext = (char*)strchr(pszLine, '\r') )
	{
		*pszLineNext = '\0';
	
		// Comment.
		if ( pszComment = (char*)strchr(pszLine, ';') )
		{
			*pszComment = '\0';
		}
		// Message
		else if ( (char*)strchr(pszLine, '#') )
		{
			nMsgNum++;
			nLineLen = strlen(pszLine)+1;

			g_ppszClientMsg = (CHAR**)realloc(g_ppszClientMsg, sizeof(CHAR*)*nMsgNum);			

			if ( !g_ppszClientMsg )
			{
				MessageBox(NULL, (char*)"Message List File Error.", "[Error] - Legend of Mir III", MB_ICONERROR);
				return FALSE;
			}

			g_ppszClientMsg[nMsgNum-1] = new CHAR[nLineLen];
			ZeroMemory(g_ppszClientMsg[nMsgNum-1], nLineLen);

			sscanf(pszLine, "%s %s", pszMsgNum, g_ppszClientMsg[nMsgNum-1]);

			g_ClientMsgNum = nMsgNum;
		}

		pszLine = (pszLineNext+2);  // '\r''\n'
	}	

	delete [] pszBuf;

	return TRUE;
}

VOID DestroyClientMsgList()
{
	// 메모리 해제.
	for ( INT nCnt = 0; nCnt < g_ClientMsgNum; nCnt++ )
	{
		SAFE_DELETEARR(g_ppszClientMsg[nCnt]);
	}

	g_ClientMsgNum = 0;

	SAFE_DELETE(g_ppszClientMsg);
}

/*
VOID SetFontList()
{
	// 초기화.
	g_xFontList.ClearAll();
	g_nFontNum = 0;

	// Config.ini에서 필요한 정보를 얻어서 대입한다.
	CHAR	szFileName[MAX_PATH];
	CHAR	szTemp[MAX_PATH];
	CHAR*	pStr;

	ZeroMemory(szFileName, MAX_PATH);
	ZeroMemory(szTemp, MAX_PATH);

	if ( GetCurrentDirectory(MAX_PATH, szFileName) )
	{
		if ( szFileName[0] == '\0' )
		{
			return;
		}

		strcat(szFileName, "\\Config.ini");

		//------------------------------------------------------------------------------------------------------------
		// Get Default Font Num...
		g_nFontNum = GetPrivateProfileInt("Options", "FontNum", 0, szFileName);							
		//------------------------------------------------------------------------------------------------------------

		INT		nFontCount;
		nFontCount = GetPrivateProfileInt("FontList", "FontCount", 1, szFileName);							

		for ( INT nCnt = 0; nCnt < nFontCount; nCnt++ )
		{
			LPFONTLIST pstFontList = new FONTLIST;
			ZeroMemory(pstFontList, sizeof(FONTLIST));

			if ( pstFontList )
			{
				ZeroMemory(pstFontList, sizeof(FONTLIST));

				sprintf(szTemp, "Font%d", nCnt);
				GetPrivateProfileString("FontList", (LPCTSTR)szTemp, NULL, pstFontList->pszDesc, MAX_PATH, szFileName);

				g_xFontList.Insert(pstFontList);
			}
		}

		SetMir3DefFont(FALSE);
	}
}


VOID SetMir3DefFont(BOOL bPlus)
{
	// 리스트에 있는 폰트를 순환시킨다.
	LPFONTLIST pstFontList = NULL;
	CListNode < FONTLIST >	*pNode;
	INT nCnt = 0;
	for ( pNode = g_xFontList.GetHead(); pNode; pNode = pNode->GetNext() )
	{
		pstFontList = pNode->GetData();

		if ( pstFontList )
		{
			if ( nCnt == g_nFontNum )
			{
				g_xMainWnd.SetDefFont(pstFontList->pszDesc);

				if ( bPlus )
				{
					g_nFontNum++;
					if ( g_nFontNum >= g_xFontList.GetCount() )
					{
						g_nFontNum = 0;
					}
				}

				CHAR	szFileName[MAX_PATH];
				ZeroMemory(szFileName, MAX_PATH);

				if ( GetCurrentDirectory(MAX_PATH, szFileName) )
				{
					if ( szFileName[0] == '\0' )
					{
						return;
					}

					strcat(szFileName, "\\Config.ini");

					CHAR szVal[MAX_PATH];
					_itoa(g_nFontNum, szVal, 10);
					WritePrivateProfileString("Options", "FontNum", szVal, szFileName);
				}

				break;
			}

			nCnt++;
		}
	}
}


VOID ReleaseFontList()
{
	// 메모리해제. 프로그램 종료시 호출한다.
	g_xFontList.ClearAll();
	g_nFontNum = 0;
}
*/
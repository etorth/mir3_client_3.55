

#include "stdafx.h"
#include "CmdLineParser.h"
#include "ddraw.h"


sExecCmds g_execCmds;


static unsigned int  __w, __h, __bpp, __rr;
static bool __availble;
static char __recommend[256];



static HRESULT WINAPI EnumModeCallback( DDSURFACEDESC *pDesc, void *pContext )
{
#ifdef _DEBUG
	char __szBuf[256];
	sprintf( __szBuf, "<ORZ DisplayMode> %d x %d, %d bpp, %d hz\n",
		pDesc->dwWidth,
		pDesc->dwHeight,
		pDesc->ddpfPixelFormat.dwRGBBitCount,
		pDesc->dwRefreshRate );
	OutputDebugString( __szBuf );
#endif

	if ( pDesc->dwWidth == __w							&& 
		 pDesc->dwHeight == __h							&&
		 pDesc->ddpfPixelFormat.dwRGBBitCount == __bpp )
	{
		if ( pDesc->dwRefreshRate == __rr )
		{
			__availble = true;
		}
		else
		{
			if ( !__recommend[0] )
				sprintf( __recommend, "%d", pDesc->dwRefreshRate );
			else
				sprintf( __recommend + strlen( __recommend ), ", %d", pDesc->dwRefreshRate );
		}
	}

	return DDENUMRET_OK;
}


static bool IsAvailableRefreshRate( int w, int h, int bpp, int rr )
{
	__w		= w;
	__h		= h;
	__bpp	= bpp;
	__rr	= rr;

	IDirectDraw *pDD;
	if ( FAILED( DirectDrawCreate( NULL, &pDD, NULL ) ) )
		return false;

	if ( FAILED( pDD->EnumDisplayModes( DDEDM_REFRESHRATES, 
										NULL,
										NULL,
										EnumModeCallback ) ) )
	{
		pDD->Release();
		return false;
	}

	pDD->Release();
	return __availble;
}


/*
	Command Line Usage> mir3.exe [options]
	
	-m [window or fullscreen]
	-r [refresh rate]
	-s [server address] 
	-p [server port] 
*/
bool ParseCmdLine()
{
	//Edited by ralph 2003 10 28
	CHAR	pszFullPath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, pszFullPath);


	strcat(pszFullPath, MIR3_MODEINI_NAME);
	

	//mode.ini파일 체크해서 없으면 생성
   if( (_access( pszFullPath, 0 )) == -1 )
   {
		WritePrivateProfileString(_MIR3EI_INI_SECTION,_FULLMODE, "1",pszFullPath);
   }

	for ( int i = 1; i < __argc; i++ )
	{		
		if ( !(__argv[i][0] == '-') && !(__argv[i][0] == '/') )
		{
/*			// 규격커맨드가 없는 전달인자.
			// 카운트에 따라 인포샵의 IP, Port전달로 쓰인다.
			// if ( !strcmp(__argv[3], "") )
			{
				g_stInfoShop.bSetted = TRUE;

				if ( !strcmp(__argv[1], "/KWG") )
				{
					// 코넷.
					g_stInfoShop.bIsKornet = TRUE;
					strcpy(g_stInfoShop.pszAddr, _KORNET_IP);
					g_stInfoShop.nPort = _KORNET_PORT;

					strcpy(g_stInfoShop.pszCPIPcode, __argv[2]);
					strcpy(g_stInfoShop.pszSVCcode, __argv[3]);
					strcpy(g_stInfoShop.pszLoginID, __argv[4]);
					strcpy(g_stInfoShop.pszCheckSum, __argv[5]);
				}
				else
				{
					// 일반 인포샵.
					g_stInfoShop.bIsKornet = FALSE;
					strcpy(g_stInfoShop.pszAddr, __argv[2]);
					g_stInfoShop.nPort = atoi( __argv[3] );
				}
			}*/
			continue;
		}
		
		switch ( __argv[i][1] )
		{
		case 'u':
		case 'U':
			g_execCmds.bNotPatchd = true;
			g_execCmds.bFullScreen = GetPrivateProfileInt(_MIR3EI_INI_SECTION, _FULLMODE, 1, pszFullPath);	
			break;

		case 'm':
			g_execCmds.bNotPatchd = true;
			g_execCmds.bFullScreen = false;
			break;
		case 'M':
			char	szVal[10];
			if ( i + 1 >= __argc )
				break;
			
			if ( stricmp( __argv[++i], "WINDOW" ) == 0 )
			{
				_itoa(0,szVal,10);
				WritePrivateProfileString(_MIR3EI_INI_SECTION,_FULLMODE, szVal,pszFullPath);
				g_execCmds.bFullScreen = false;
			}
			else
			{
				_itoa(1,szVal,10);
				WritePrivateProfileString(_MIR3EI_INI_SECTION,_FULLMODE,szVal,pszFullPath);
				g_execCmds.bFullScreen = true;  
			}
			break;
		case 'p':
		case 'P':
			if ( i + 1 >= __argc )
				break;

			g_execCmds.nPort = atoi( __argv[++i] );
			break;

		case 'r':			
		case 'R':			
			if ( i + 1 >= __argc )
				break;

			g_execCmds.nRefreshRate = atoi( __argv[++i] );
			if ( !IsAvailableRefreshRate( 800, 600, 16, g_execCmds.nRefreshRate ) )
			{
				char szBuf[1024];
				sprintf(szBuf, g_xMsg.GetMsg(10000), g_execCmds.nRefreshRate, __recommend);
				
				if ( MessageBox( NULL, 
								 szBuf, 
								 "Legend Of Mir 3", 
								 MB_ICONINFORMATION | MB_YESNO ) == IDNO )
				{
					return false;
				}

				g_execCmds.nRefreshRate = 0;
			}
			break;
			
		case 's':
		case 'S':
			if ( i + 1 >= __argc )
				break;

			strcpy( g_execCmds.szServerIP, __argv[++i] );
			break;
		}
	}

	return true;
}

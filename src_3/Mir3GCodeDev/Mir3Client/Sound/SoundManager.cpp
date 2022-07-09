/*
		FileName            : SoundManager.cpp
		Description         : DirectSound
		Author/Date         : Lee Kyoung Soo / 2000.05.29
		Modification History:
		-----------------------------------------------------
		01.					SoundManager::SoundManager();
		02.					SoundManager::~SoundManager()

		11.USound*			SoundManager::SndmngrLoadSound();

		21.char*			SoundManager::SndmngrSeekFileName();
		22.void				SoundManager::ReadWaveFileList();
		23.void				SoundManager::SndmngrReadBGMFileList();
		24.char*			SoundManager::SndmngrFindBgmFileName();

		31.void				SoundManager::SndmngrPlayWavSound();
		32.void				SoundManager::SndmngrStopWavSound();
		33.BOOL				SoundManager::SndmngrChgVolnPan();
		34.void				SoundManager::SndmngrSetEnableWavePlay();
		35.void				SoundManager::SndmngrSetDisableWavePlay();


		41.void				SoundManager::SndmngrPlayMp3();
		41-1.void			SoundManager::SndmngrPlayMp3();
		42.BOOL				SoundManager::SndmngrBGMOff();
		43.void				SoundManager::SndmngrStopMp3();
		44.BOOL				SoundManager::SndmngrIsPlayingBGM();
		45.VOID				SoundManager::SndmngrSetEnableBGM();

		51.HRESULT			SoundManager::SndmngrMessageProc();
*/

#include "StdAfx.h"

#define	SECTION_SOUND_FILE	"SOUND_FILE"

/***** Func01 *** Lee Kyoung Soo / 2000.05.29 *******************************/
SoundManager::SoundManager()
{
	int		nI, nJ;

	for (nI=0; nI<SOUND_TILE_X; nI++)
	{
		for (nJ=0; nJ<SOUND_TILE_Y; nJ++)
		{
			mSndMngr_lVolumeBuffer[nI][nJ] = (long)-sqrt(pow((double)abs(nI - SOUND_TILE_CENTER_X), 2) + pow((double)abs(nJ - SOUND_TILE_CENTER_Y),2)) * 150;
		}
	}

	for (nI=0; nI<MAX_SOUND; nI++)
		mSndMngr_pIdxBuffer[nI] = NULL;
	
	mSndMngr_nSoundVolume	= 0;
	mSndMngr_bMusicOn		= FALSE;
	mSndMngr_bInit			= FALSE;
	mSndMngr_lWavMaxVol		= 0;
	mSndMngr_bMP3Play		= TRUE;
	mSndMngr_bWavePlay		= TRUE;
	mSndMngr_bRevereLR		= FALSE;

	mSndMngr_pMp3 = new CBMMp3;
}

/***** Func02 *** Lee Kyoung Soo / 2001.08.13 *******************************/
SoundManager::~SoundManager()
{
	for (int nI=0; nI<MAX_SOUND; nI++)
	{
		if (mSndMngr_pIdxBuffer[nI] != NULL)
		{
			mSndMngr_pIdxBuffer[nI] = NULL;
		}
	}
	if(mSndMngr_pMp3!=NULL)
		delete mSndMngr_pMp3;
}

/***** Func11 *** Lee Kyoung Soo / 2001.08.13 *******************************/
int
SoundManager::SndmngrLoadSound(
	int				nIdx)
{
	if (mSndMngr_bInit == FALSE) return -1;

	char			szFullPath[255];
	char*			fname;
	
	fname = SndmngrSeekFileName(nIdx);

	if (fname == NULL)
		return -1;

	strcpy(szFullPath,"Sound\\");
	strcat(szFullPath,fname);

	for (int nI=0; nI<MAX_SOUND; nI++)
	{
		if (mSndMngr_pIdxBuffer[nI] == NULL)
		{
			mSndMngr_pIdxBuffer[nI] = SndObjCreate(mSound_lpds, szFullPath, 10);
			if (mSndMngr_pIdxBuffer[nI] == NULL)
				return -1;
			else
				return nI;
		}
	}

	DWORD	dwTime;

	dwTime = timeGetTime();								// 현재 시간을 구한다.

	for (nI=0; nI<MAX_SOUND; nI++)
	{
		if (mSndMngr_pIdxBuffer[nI] != NULL)
		{
			if (dwTime - mSndMngr_pIdxBuffer[nI]->dwTimer > 1000)
			{
				SndObjDestroy(mSndMngr_pIdxBuffer[nI]);
				mSndMngr_pIdxBuffer[nI] = NULL;
				mSndMngr_pIdxBuffer[nI] = SndObjCreate(mSound_lpds, szFullPath, 10);
				if (mSndMngr_pIdxBuffer[nI] == NULL)
					return -1;
				else
					return nI;
			}
		}
	}
	return -1;
}

/***** Func21 *** Lee Kyoung Soo / 2002.10.28 *******************************/
char*
SoundManager::SndmngrSeekFileName(
	int				wavnum)
{
	unsigned int	i;

	if(mSndMngr_bInit && mSndMngr_bWavePlay)
	{
		for(i=0;i<mSndMngr_pWavListHeader.FieldCount;i++)
		{
			if (mSndMngr_pWavList == NULL)
				continue;
			if(wavnum == mSndMngr_pWavList[i].ID && mSndMngr_pWavList[i].Des[0] != '\0') 
			{
				return mSndMngr_pWavList[i].Des;
			}
		}
	}
	return NULL;
}

/***** Func22 *** Lee Kyoung Soo / 2002.10.28 *******************************/
void
SoundManager::ReadWaveFileList(char* fName)
{
	unsigned int i;
	int Count;
	DWORD dwReadSize;
	WAVELIST* l_WavList;

	HANDLE hFile = ::CreateFile(fName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile!=INVALID_HANDLE_VALUE)
	{
		//	Header Reading
		ReadFile(hFile,&mSndMngr_pWavListHeader,sizeof(WAVELISTHEADER),&dwReadSize,NULL);
	
		mSndMngr_pWavList = new WAVELIST[mSndMngr_pWavListHeader.FieldCount];

		INT		 nWavCnt = 0;
		WAVELIST stWaveList;

		for ( INT nCnt = 0; nCnt < mSndMngr_pWavListHeader.ListCount; nCnt++ )
		{
			ZeroMemory(&stWaveList, sizeof(WAVELIST));
			ReadFile(hFile, &stWaveList, sizeof(WAVELIST), &dwReadSize, NULL);
			if ( stWaveList.ID != 0 )
			{
				mSndMngr_pWavList[nWavCnt] = stWaveList;
				nWavCnt++;
			}
		}

		CloseHandle(hFile);
	}
	else
	{
		mSndMngr_bWavePlay = FALSE;
	}
}

/***** Func23 *** Lee Kyoung Soo / 2002.10.28 *******************************/
void
SoundManager::SndmngrReadBGMFileList(char* fName)
{
	unsigned int i;
	int Count;
	DWORD dwReadSize;
	BGMLIST* l_BGMList;

	HANDLE hFile = ::CreateFile(fName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile!=INVALID_HANDLE_VALUE)
	{
		//	Header Reading
		ReadFile(hFile,&mSndMngr_pBGMListHeader,sizeof(BGMLISTHEADER),&dwReadSize,NULL);

		mSndMngr_pBGMList = new BGMLIST[mSndMngr_pBGMListHeader.FieldCount];
		ReadFile(hFile, mSndMngr_pBGMList , sizeof(BGMLIST)*mSndMngr_pBGMListHeader.FieldCount, &dwReadSize, NULL);

		//	fclose(hFile);	
		CloseHandle(hFile);
	}
	else
	{
		mSndMngr_bMP3Play = FALSE;
	}
}

/***** Func24 *** Lee Kyoung Soo / 2002.10.28 *******************************/
char*
SoundManager::SndmngrFindBgmFileName(CHAR* szMapName)
{
	INT	nCnt;

	if(mSndMngr_pBGMList!=NULL)
	{
		for(nCnt = 0; nCnt < mSndMngr_pBGMListHeader.FieldCount; nCnt ++)
		{
			if(strcmp(szMapName,mSndMngr_pBGMList[nCnt].ID+1)==0 && mSndMngr_pBGMList[nCnt].Des[0] != '\0')
				return mSndMngr_pBGMList[nCnt].Des;
		}
	}
	return NULL;
}

/***** Fun31 *** Lee Kyoung Soo / 2001.08.13 *******************************/
int
SoundManager::SndmngrPlayWavSound(
	int				nIdx,
	int				nScrnX,
	int				nScrnY,
	BOOL			bLooping /*=FALSE*/)
{
	int				nRtn = -1, nNewIdx;
	DWORD			dwPlayFlags = 0;

	if (!mSndMngr_bInit || !mSndMngr_bWavePlay) return -1;

	if (bLooping == TRUE)
		dwPlayFlags = DSBPLAY_LOOPING;

	// find wave buffer
	for (int nI=0; nI<MAX_SOUND; nI++)
	{
		if (mSndMngr_pIdxBuffer[nI] != NULL)
		{
			if (mSndMngr_pIdxBuffer[nI]->nIdx == nIdx)
			{
				nRtn = SndObjPlay(nScrnX, nScrnY,  mSndMngr_pIdxBuffer[nI], dwPlayFlags, TRUE);
				return nRtn;
			}
		}
	}

	nNewIdx = SndmngrLoadSound(nIdx);

	if (nNewIdx != -1)
	{
		if (mSndMngr_pIdxBuffer[nNewIdx] == NULL)
			return -1;

		nRtn = SndObjPlay(nScrnX, nScrnY,  mSndMngr_pIdxBuffer[nNewIdx], dwPlayFlags, TRUE);
		mSndMngr_pIdxBuffer[nNewIdx]->nIdx = nIdx;
		mSndMngr_pIdxBuffer[nNewIdx]->dwTimer = timeGetTime();
		return nRtn;
	}

	return nRtn;
}

/***** Func32 *** Lee Kyoung Soo / 2000.05.29 *******************************/
void
SoundManager::SndmngrStopWavSound(
	int				nIdx,
	int				nBufIdx)
{
	if (mSndMngr_bInit == FALSE || mSndMngr_bWavePlay == FALSE) return;

	for (int nI=0; nI<MAX_SOUND; nI++)
	{
		if (mSndMngr_pIdxBuffer[nI] == NULL) continue;
		if (mSndMngr_pIdxBuffer[nI]->nIdx == nIdx)
		{
			IDirectSoundBuffer *pDSB = SndObjGetBuffer(mSndMngr_pIdxBuffer[nI], nBufIdx);

			pDSB->Stop();
			return ;
		}
	}
}

/***** Func32-1 *** Lee Kyoung Soo / 2000.05.29 *******************************/
void
SoundManager::SndmngrStopWavSound(
	int				nIdx)
	
{
	if (mSndMngr_bInit == FALSE || mSndMngr_bWavePlay == FALSE) return;

	for (int nI=0; nI<MAX_SOUND; nI++)
	{
		if (mSndMngr_pIdxBuffer[nI] == NULL) continue;
		if (mSndMngr_pIdxBuffer[nI]->nIdx == nIdx)
		{
			SndObjStop(mSndMngr_pIdxBuffer[nI]);
			return;
		}
	}
}

/***** Func33 *** Lee Kyoung Soo / 2002.10.28 *******************************/
BOOL
SoundManager::SndmngrChgVolnPan(
	INT nWavIdx,
	INT nBufferIdx,
	INT nScrnX,
	INT nScrnY)

{
	if (mSndMngr_bInit == FALSE || mSndMngr_bWavePlay == FALSE) return FALSE;

	for (int nI=0; nI<MAX_SOUND; nI++)
	{
		if (mSndMngr_pIdxBuffer[nI] == NULL) continue;
		if (mSndMngr_pIdxBuffer[nI]->nIdx == nWavIdx)
		{
			IDirectSoundBuffer *pDSB = SndObjGetBuffer(mSndMngr_pIdxBuffer[nI], nBufferIdx);

			SndObjSetVolnPan(nScrnX, nScrnY, pDSB);
			return TRUE;
		}
	}

	return FALSE;

}

/***** Func34 *** Lee Kyoung Soo / 2002.10.28 *******************************/
void
SoundManager::SndmngrSetEnableWavePlay(VOID)
{
	mSndMngr_bWavePlay = TRUE;
}

/***** Func35 *** Lee Kyoung Soo / 2002.10.28 *******************************/
void
SoundManager::SndmngrSetDisableWavePlay(VOID)
{
	mSndMngr_bWavePlay = FALSE;
}

/***** Func36 *** Lee Kyoung Soo / 2002.10.28 *******************************/
void
SoundManager::SndmngrStopAllWaveSound(void)
{
	if (mSndMngr_bInit == FALSE || mSndMngr_bWavePlay == FALSE) return;

	for(int i = 0;i<MAX_SOUND;i++)
	{
		if (mSndMngr_pIdxBuffer[i] != NULL)
			SndObjStop(mSndMngr_pIdxBuffer[i]);
	}
}

/***** Func36 *** Lee Kyoung Soo / 2002.10.28 *******************************/
void		
SoundManager::SndmngrReleaseAllWaveSound(void)
{
	if (mSndMngr_bInit == FALSE || mSndMngr_bWavePlay == FALSE) return;

	for(int i = 0;i<MAX_SOUND;i++)
	{
		if (mSndMngr_pIdxBuffer[i] != NULL)
		{
			SndObjDestroy(mSndMngr_pIdxBuffer[i]);
			mSndMngr_pIdxBuffer[i] = NULL;
		}
	}
}


/***** Func41 *** Lee Kyoung Soo / 2002.10.28 *******************************/
void
SoundManager::SndmngrPlayMp3(
	CHAR*	szMapName, 
	BOOL	Looped,
	INT		nIndex)
{
	if(mSndMngr_bMP3Play && mSndMngr_bInit)
	{
		CHAR*		szMp3FileName;
		CHAR		szFullName[MAX_PATH];
		strcpy(szFullName,"SOUND\\");

		szMp3FileName = NULL;
		
		szMp3FileName = SndmngrFindBgmFileName(szMapName);
		if(szMp3FileName!=NULL)
		{			
			if((strcmp(szMp3FileName,"none")!=0))
			{
				strcat(szFullName,szMp3FileName);

				if (mSndMngr_pMp3 != NULL)
				{
					if((strcmp(szMp3FileName,"nobgm")!=0))
					{									
						mSndMngr_pMp3->Bmmp3LoadMp3(szFullName,g_xMainWnd.GetSafehWnd());
						mSndMngr_pMp3->Bmmp3OnPlay(mSndMngr_lMp3MaxVol, Looped);			
					}
				}
			}
		}
	}
}

/***** Func41-1 *** Lee Kyoung Soo / 2002.10.28 *******************************/
void
SoundManager::SndmngrPlayMp3(CHAR* pszFileName,BOOL Loop)
{
	if (mSndMngr_pMp3 == NULL)
		return;

	if(mSndMngr_bInit)
	{
		mSndMngr_pMp3->Bmmp3LoadMp3(pszFileName,g_xMainWnd.GetSafehWnd());
		mSndMngr_pMp3->Bmmp3OnPlay(mSndMngr_lMp3MaxVol,Loop);			
	}
}

/***** Func43 *** Lee Kyoung Soo / 2002.10.28 *******************************/
void
SoundManager::SndmngrStopMp3(VOID)
{
	if (mSndMngr_pMp3 == NULL || mSndMngr_bInit == FALSE)
		return;
	mSndMngr_pMp3->Bmmp3OnStop();
}

/***** Func44 *** Lee Kyoung Soo / 2002.10.28 *******************************/
BOOL
SoundManager::SndmngrIsPlayingBGM(void)
{
	if (mSndMngr_pMp3 == NULL || mSndMngr_bInit == FALSE)
		return FALSE;

	return mSndMngr_pMp3->IsbePlaying();
}

/***** Func45 *** Lee Kyoung Soo / 2002.10.28 *******************************/
VOID
SoundManager::SndmngrSetEnableBGM(VOID)
{
	if(mSndMngr_bInit)
		mSndMngr_bMP3Play = TRUE;
}

/***** Func46 *** Lee Kyoung Soo / 2002.10.28 *******************************/
VOID
SoundManager::SndmngrSetDisableBGM(VOID)
{
	mSndMngr_bMP3Play = FALSE;
}

/***** Func51 *** Lee Kyoung Soo / 2002.10.28 *******************************/
HRESULT
SoundManager::SndmngrMessageProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
		case WM_DSHOW_NOTIFY:
			{
				if (mSndMngr_pMp3 != NULL)
				{
					mSndMngr_pMp3->Bmmp3MessageProcess();
					break;
				}
			}
	}
	return 0l;
}


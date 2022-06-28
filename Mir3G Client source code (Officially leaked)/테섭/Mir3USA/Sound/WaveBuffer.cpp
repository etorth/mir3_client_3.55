/*
		FileName            : USoundManager.cpp
		Description         : DirectSound
		Author/Date         : Lee Kyoung Soo / 2002.10.30
		Modification History:
		-----------------------------------------------------
		11.IDirectSoundBuffer*	DSLoadSoundBuffer();
		12.IDirectSoundBuffer*	DSLoad3DSoundBuffer();
		13.BOOL					DSReloadSoundBuffer();
		14.BOOL					DSGetWaveResource();
		15.BOOL					DSGetWaveFile();

		21.SNDOBJ*				SndObjCreate();
		22.void					SndObjDestroy();
		23.IDirectSoundBuffer*	SndObjGetFreeBuffer();

		31.BOOL					SndObjPlay();
		32.BOOL					SndObjStop();

		51.BOOL					DSFillSoundBuffer();
		52.BOOL					DSParseWaveResource();

		61.int					CalsVolume();
		62.int					CalsPan();
		63.IDirectSoundBuffer*	SndObjGetBuffer();
		64.void					SndObjSetVolnPan();



*/

//#define WIN32_LEAN_AND_MEAN
#include "StdAfx.h"

static const char c_szWAV[] = "WAVE";

#define	CENTER_OF_TILE_WIDTH_IN_SOUNDBUFFER		24
#define TILE_WIDTH_IN_SOUNDBUFFER				47
#define TILE_HEIGHT_IN_SOUNDBUFFER				31
#define	CENTER_OF_TILE_WIDTH_IN_SOUNDBUFFER		24
#define	CENTER_OF_TILE_HEIGHT_IN_SOUNDBUFFER	16

#define PANNING_VALUE_PER_TILE					600

// DSLoadSoundBuffer - Loads a .WAV into a sound buffer and returns the sound buffer
/***** Func11 *** Lee Kyoung Soo / 2002.10.30 *******************************/
IDirectSoundBuffer*
DSLoadSoundBuffer(
	IDirectSound	*pDS,
	LPCTSTR			lpName)
{
	if ( pDS == NULL )
	{
		return NULL;
	}

    IDirectSoundBuffer *pDSB = NULL;
    DSBUFFERDESC dsBD = {0};
    BYTE *pbWaveData;
    void *pvBase;

    dsBD.dwSize = sizeof(dsBD);
    dsBD.dwFlags = DSBCAPS_STATIC | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME
                        | DSBCAPS_LOCSOFTWARE;

    if (DSGetWaveResource(NULL, lpName, &dsBD.lpwfxFormat, &pbWaveData, &dsBD.dwBufferBytes))
    {
        if (SUCCEEDED(IDirectSound_CreateSoundBuffer(pDS, &dsBD, &pDSB, NULL)))
        {
            if (!DSFillSoundBuffer(pDSB, pbWaveData, dsBD.dwBufferBytes))
            {
                IDirectSoundBuffer_Release(pDSB);
                pDSB = NULL;
            }
        }
        else
        {
            pDSB = NULL;
        }
    }
	else if (DSGetWaveFile(NULL, lpName, &dsBD.lpwfxFormat, &pbWaveData,
                        &dsBD.dwBufferBytes, &pvBase))
    {
        if (SUCCEEDED(IDirectSound_CreateSoundBuffer(pDS, &dsBD, &pDSB, NULL)))
        {
            if (!DSFillSoundBuffer(pDSB, pbWaveData, dsBD.dwBufferBytes))
            {
                IDirectSoundBuffer_Release(pDSB);
                pDSB = NULL;
            }
        }
        else
        {
            pDSB = NULL;
        }
		UnmapViewOfFile (pvBase);
    }

    return pDSB;
}


// DSLoad3DSoundBuffer - Loads a .WAV into a 3D sound buffer and returns the sound buffer
/***** Func12 *** Lee Kyoung Soo / 2002.10.30 *******************************/
IDirectSoundBuffer*
DSLoad3DSoundBuffer(
	IDirectSound	*pDS,
	LPCTSTR			lpName)
{
	if ( pDS == NULL )
	{
		return NULL;
	}

    IDirectSoundBuffer *pDSB = NULL;
    DSBUFFERDESC dsBD = {0};
    BYTE *pbWaveData;
    void *pvBase;

    dsBD.dwSize = sizeof(dsBD);
    dsBD.dwFlags = DSBCAPS_STATIC | DSBCAPS_CTRL3D | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN
                        | DSBCAPS_CTRLFREQUENCY | DSBCAPS_LOCSOFTWARE
                        | DSBCAPS_STICKYFOCUS;

    if (DSGetWaveResource(NULL, lpName, &dsBD.lpwfxFormat, &pbWaveData, &dsBD.dwBufferBytes))
    {
        if (SUCCEEDED(IDirectSound_CreateSoundBuffer(pDS, &dsBD, &pDSB, NULL)))
        {
            if (!DSFillSoundBuffer(pDSB, pbWaveData, dsBD.dwBufferBytes))
            {
                IDirectSoundBuffer_Release(pDSB);
                pDSB = NULL;
            }
        }
        else
        {
            pDSB = NULL;
        }
    }
	else if (DSGetWaveFile(NULL, lpName, &dsBD.lpwfxFormat, &pbWaveData,
                        &dsBD.dwBufferBytes, &pvBase))
    {
        if (SUCCEEDED(IDirectSound_CreateSoundBuffer(pDS, &dsBD, &pDSB, NULL)))
        {
            if (!DSFillSoundBuffer(pDSB, pbWaveData, dsBD.dwBufferBytes))
            {
                IDirectSoundBuffer_Release(pDSB);
                pDSB = NULL;
            }
        }
        else
        {
            pDSB = NULL;
        }
		UnmapViewOfFile (pvBase);
    }

    return pDSB;
}


// DSReloadSoundBuffer
/***** Func13 *** Lee Kyoung Soo / 2002.10.30 *******************************/
BOOL
DSReloadSoundBuffer(
	IDirectSoundBuffer	*pDSB,
	LPCTSTR				lpName)
{
    BOOL result=FALSE;
    BYTE *pbWaveData;
    DWORD cbWaveSize;
    void *pvBase;

    if (DSGetWaveResource(NULL, lpName, NULL, &pbWaveData, &cbWaveSize))
    {
        if (SUCCEEDED(IDirectSoundBuffer_Restore(pDSB)) &&
            DSFillSoundBuffer(pDSB, pbWaveData, cbWaveSize))
		{
			result = TRUE;
        }
    }
	else if( DSGetWaveFile(NULL, lpName, NULL, &pbWaveData, &cbWaveSize, &pvBase))
    {
        if (SUCCEEDED(IDirectSoundBuffer_Restore(pDSB)) &&
            DSFillSoundBuffer(pDSB, pbWaveData, cbWaveSize))
		{
			result = TRUE;
        }
        UnmapViewOfFile (pvBase);
    }

    return result;
}

/***** Func14 *** Lee Kyoung Soo / 2002.10.30 *******************************/
BOOL
DSGetWaveResource(
	HMODULE			hModule,
	LPCTSTR			lpName,
    WAVEFORMATEX	**ppWaveHeader,
	BYTE			**ppbWaveData,
	DWORD			*pcbWaveSize)
{
    HRSRC hResInfo;
    HGLOBAL hResData;
    void * pvRes;

    if (((hResInfo = FindResource(hModule, lpName, c_szWAV)) != NULL) &&
        ((hResData = LoadResource(hModule, hResInfo)) != NULL) &&
        ((pvRes = LockResource(hResData)) != NULL) &&
        DSParseWaveResource(pvRes, ppWaveHeader, ppbWaveData, pcbWaveSize))
    {
        return TRUE;
    }

    return FALSE;

}

/***** Func15 *** Lee Kyoung Soo / 2002.10.30 *******************************/
BOOL
DSGetWaveFile(
	HMODULE			hModule,
	LPCTSTR			lpName,
    WAVEFORMATEX	**ppWaveHeader,
	BYTE			**ppbWaveData,
	DWORD			*pcbWaveSize,
	void			**ppvBase)
{
    void *pvRes;
    HANDLE hFile, hMapping;

    *ppvBase = NULL;

    hFile = CreateFile (lpName, GENERIC_READ, FILE_SHARE_READ, 
	                    NULL, OPEN_EXISTING, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	hMapping = CreateFileMapping (hFile, NULL, PAGE_READONLY, 0, 0, NULL);
    if (hMapping == INVALID_HANDLE_VALUE)
    {
        CloseHandle (hFile); 
        return FALSE;
    }

    CloseHandle (hFile);

    pvRes = MapViewOfFile (hMapping, FILE_MAP_READ, 0, 0, 0);
    if (pvRes == NULL)
    {
        CloseHandle (hMapping);
        return FALSE;
    }

    CloseHandle (hMapping);

    if (DSParseWaveResource(pvRes, ppWaveHeader, ppbWaveData, pcbWaveSize) == FALSE)
    {
        UnmapViewOfFile (pvRes);
        return FALSE;
    }

    *ppvBase = pvRes;
    return TRUE;
}

/***** Func21 *** Lee Kyoung Soo / 2002.10.30 *******************************/
SNDOBJ*
SndObjCreate(
	IDirectSound	*pDS,
	LPCTSTR			lpName,
	int				iConcurrent)
{
	if ( pDS == NULL )
	{
		return NULL;
	}
	// 사운드 오브젝트를 생성함에 있어서 바로 재생하여 사용할 수 있는 버퍼를 넘겨줄 수 있어야 한다.
	
    SNDOBJ *pSO = NULL;
    LPWAVEFORMATEX pWaveHeader;
    BOOL fFound = FALSE;
    BYTE *pbData;
    DWORD cbData;
    void * pvBase;

	LPDIRECTSOUNDBUFFER Buffer;

    if (DSGetWaveResource(NULL, lpName, &pWaveHeader, &pbData, &cbData))
        fFound = TRUE;
    if (DSGetWaveFile(NULL, lpName, &pWaveHeader, &pbData, &cbData, &pvBase))
    {
        fFound = TRUE;
        UnmapViewOfFile( pvBase );
    }

    if( fFound )
    {
        if (iConcurrent < 1)
            iConcurrent = 1;

        if ((pSO = (SNDOBJ *)LocalAlloc(LPTR, sizeof(SNDOBJ) +
	    (iConcurrent-1) * sizeof(IDirectSoundBuffer *))) != NULL)
        {
            int i;

            pSO->iAlloc = iConcurrent;
            pSO->pbWaveData = pbData;
            pSO->cbWaveSize = cbData;
            pSO->Buffers[0] = DSLoadSoundBuffer(pDS, lpName);

			for (i = 1; i < pSO->iAlloc; i++)
			{
				if (FAILED(IDirectSound_DuplicateSoundBuffer(pDS,
						pSO->Buffers[0], &pSO->Buffers[i])))
				{
					pSO->Buffers[i] = DSLoadSoundBuffer(pDS, lpName);
					if (!pSO->Buffers[i])
					{
						SndObjDestroy(pSO);
						pSO = NULL;
						break;
					}
				}
			}
        }
    }

    return pSO;
}

/***** Func22 *** Lee Kyoung Soo / 2002.10.30 *******************************/
void
SndObjDestroy(
	SNDOBJ		*pSO)
{
    if (pSO)
    {
        int i;

        for (i=0; i<pSO->iAlloc; i++)
        {
            if (pSO->Buffers[i])
            {
                IDirectSoundBuffer_Release(pSO->Buffers[i]);
                pSO->Buffers[i] = NULL;
            }
        }
        LocalFree((HANDLE)pSO);
    }
}

/***** Func23 *** Lee Kyoung Soo / 2002.10.30 *******************************/
IDirectSoundBuffer*
SndObjGetFreeBuffer(
	SNDOBJ		*pSO,
	BOOL		bNext /* = TRUE */)
{
    IDirectSoundBuffer *pDSB;

    if (pSO == NULL)
        return NULL;

    if (pDSB = pSO->Buffers[pSO->iCurrent])
    {
        HRESULT hres;
        DWORD dwStatus;

        hres = IDirectSoundBuffer_GetStatus(pDSB, &dwStatus);

        if (FAILED(hres))
            dwStatus = 0;

        if ((dwStatus & DSBSTATUS_PLAYING) == DSBSTATUS_PLAYING)
        {
            if (pSO->iAlloc > 1)
            {
				BOOL	bSearching = TRUE;
				int		nCount = 0;
				while(bSearching == TRUE)
				{
					if (bNext == TRUE)
						pSO->iCurrent++;
					if (pSO->iCurrent >= pSO->iAlloc)
						pSO->iCurrent = 0;

					pDSB = pSO->Buffers[pSO->iCurrent];

					hres = IDirectSoundBuffer_GetStatus(pDSB, &dwStatus);

					if (SUCCEEDED(hres) && (dwStatus & DSBSTATUS_PLAYING) == DSBSTATUS_PLAYING)
					{
						nCount++;
						if (nCount == 10)
							return NULL;
						else
							continue;
						// 다음 버퍼를 검색했는데 플레이 중인 경우가 열번이면 플레이 하지 않는다.
					}
					else
						bSearching = FALSE;
				}
            }
            else
            {
                pDSB = NULL;
            }
        }
		else
		{
			int test = 0;
		}

        if (pDSB && (dwStatus & DSBSTATUS_BUFFERLOST))
        {
            if (FAILED(IDirectSoundBuffer_Restore(pDSB)) ||
                !DSFillSoundBuffer(pDSB, pSO->pbWaveData, pSO->cbWaveSize))
            {
                pDSB = NULL;
            }
        }
    }

    return pDSB;
}

/***** Func31 *** Lee Kyoung Soo / 2002.10.30 *******************************/
int
SndObjPlay(
	int			nScrnX,
	int			nScrnY,
	SNDOBJ		*pSO,
	DWORD		dwPlayFlags,
	BOOL		bNext /* = TRUE */)
{
    BOOL		result = FALSE;

	INT			nScreenLocationX, nScreenLocationY;
	INT			nVolume, nPan;

    if (pSO == NULL)
        return -1;

	IDirectSoundBuffer *pDSB = SndObjGetFreeBuffer(pSO, bNext);
	if (pDSB != NULL)
	{
		SndObjSetVolnPan(nScrnX, nScrnY, pDSB);
		result = SUCCEEDED(IDirectSoundBuffer_Play(pDSB, 0, 0, dwPlayFlags));
	}

    return pSO->iCurrent;
}

/***** Func32 *** Lee Kyoung Soo / 2002.10.30 *******************************/
BOOL
SndObjStop(
	SNDOBJ		*pSO)
{
    int i;

    if (pSO == NULL)
        return FALSE;

    for (i=0; i<pSO->iAlloc; i++)
    {
        IDirectSoundBuffer_Stop(pSO->Buffers[i]);
        IDirectSoundBuffer_SetCurrentPosition(pSO->Buffers[i], 0);
    }

    return TRUE;
}

/***** Func51 *** Lee Kyoung Soo / 2002.10.30 *******************************/
BOOL
DSFillSoundBuffer(
	IDirectSoundBuffer	*pDSB,
	BYTE			*pbWaveData,
	DWORD			cbWaveSize)
{
    if (pDSB && pbWaveData && cbWaveSize)
    {
        LPVOID pMem1, pMem2;
        DWORD dwSize1, dwSize2;

        if (SUCCEEDED(IDirectSoundBuffer_Lock(pDSB, 0, cbWaveSize,
            &pMem1, &dwSize1, &pMem2, &dwSize2, 0)))
        {
            CopyMemory(pMem1, pbWaveData, dwSize1);

            if ( 0 != dwSize2 )
                CopyMemory(pMem2, pbWaveData+dwSize1, dwSize2);

            IDirectSoundBuffer_Unlock(pDSB, pMem1, dwSize1, pMem2, dwSize2);
            return TRUE;
        }
    }

    return FALSE;
}

/***** Func52 *** Lee Kyoung Soo / 2002.10.30 *******************************/
BOOL
DSParseWaveResource(
	void			*pvRes,
	WAVEFORMATEX	**ppWaveHeader,
	BYTE			**ppbWaveData,
	DWORD			*pcbWaveSize)
{
    DWORD *pdw;
    DWORD *pdwEnd;
    DWORD dwRiff;
    DWORD dwType;
    DWORD dwLength;

    if (ppWaveHeader)
        *ppWaveHeader = NULL;

    if (ppbWaveData)
        *ppbWaveData = NULL;

    if (pcbWaveSize)
        *pcbWaveSize = 0;

    pdw = (DWORD *)pvRes;
    dwRiff = *pdw++;
    dwLength = *pdw++;
    dwType = *pdw++;

    if (dwRiff != mmioFOURCC('R', 'I', 'F', 'F'))
        goto exit;      // not even RIFF

    if (dwType != mmioFOURCC('W', 'A', 'V', 'E'))
        goto exit;      // not a WAV

    pdwEnd = (DWORD *)((BYTE *)pdw + dwLength-4);

    while (pdw < pdwEnd)
    {
        dwType = *pdw++;
        dwLength = *pdw++;

        switch (dwType)
        {
        case mmioFOURCC('f', 'm', 't', ' '):
            if (ppWaveHeader && !*ppWaveHeader)
            {
                if (dwLength < sizeof(WAVEFORMAT))
                    goto exit;      // not a WAV

                *ppWaveHeader = (WAVEFORMATEX *)pdw;

                if ((!ppbWaveData || *ppbWaveData) &&
                    (!pcbWaveSize || *pcbWaveSize))
                {
                    return TRUE;
                }
            }
            break;

        case mmioFOURCC('d', 'a', 't', 'a'):
            if ((ppbWaveData && !*ppbWaveData) ||
                (pcbWaveSize && !*pcbWaveSize))
            {
                if (ppbWaveData)
                    *ppbWaveData = (LPBYTE)pdw;

                if (pcbWaveSize)
                    *pcbWaveSize = dwLength;

                if (!ppWaveHeader || *ppWaveHeader)
                    return TRUE;
            }
            break;
        }

        pdw = (DWORD *)((BYTE *)pdw + ((dwLength+1)&~1));
    }

exit:
    return FALSE;
}


/***** Func61 *** Lee Kyoung Soo / 2002.10.30 *******************************/
int	CalsVolume(int nLocationX, int nLocationY)
{
	int nVolume;

	int	nTileX, nTileY;

	if (nLocationX == 0 && nLocationY == 0)						// 0,0 의 위치를 갖는 소리는 일반효과음으로 처리하여 최대음량 리턴
		return 0;

	nTileX = (nLocationX + CENTER_OF_TILE_WIDTH_IN_SOUNDBUFFER) / TILE_WIDTH_IN_SOUNDBUFFER;
	nTileY = (nLocationY + CENTER_OF_TILE_HEIGHT_IN_SOUNDBUFFER) / TILE_HEIGHT_IN_SOUNDBUFFER;

	if (nTileX < 0 || nTileX> SOUND_TILE_X ||					// 화면 바깥의 소리 출력을 요구하면 최소 음량을 리턴	
		nTileY < 0 || nTileY> SOUND_TILE_Y)
		return MIN_VOLUME;

	if (nTileX >= SOUND_TILE_CENTER_X-2 &&					// 중앙 근처 1타일씩은 중앙과 같은 볼륨을 같도록 함
		nTileX <= SOUND_TILE_CENTER_X +2)
		nTileX = SOUND_TILE_CENTER_X;
	
	if (nTileY >= SOUND_TILE_CENTER_Y-2 &&					// 중앙 근처 1타일씩은 중앙과 같은 볼륨을 같도록 함
		nTileY <= SOUND_TILE_CENTER_Y+2)
		nTileY = SOUND_TILE_CENTER_Y;

	if (nTileX >= SOUND_TILE_X)
		nTileX = SOUND_TILE_X - 1;

	if (nTileY >= SOUND_TILE_Y)
		nTileY = SOUND_TILE_Y - 1;

	nVolume = g_SoundManager.mSndMngr_lVolumeBuffer[nTileX][nTileY];			// 미리 계산한 사운드 값에서 적절한 값 찾아 리턴

	if (nVolume < MIN_VOLUME)
		nVolume = MIN_VOLUME;

	return nVolume;
}

/***** Func62 *** Lee Kyoung Soo / 2002.10.30 *******************************/
int	CalsPan(int nLocationX, int nLocationY)
{
	int nTileX, nTileY;

	if (nLocationX == 0 && nLocationY == 0)									// 0,0 의 위치를 갖는 소리는 일반효과음으로 처리하여 중간값 리턴
		return 0;

	if (nLocationX == 808)
	{
		int nsl=0;
	}

	nTileX = (nLocationX + CENTER_OF_TILE_WIDTH_IN_SOUNDBUFFER) / TILE_WIDTH_IN_SOUNDBUFFER;
	nTileY = (nLocationY + CENTER_OF_TILE_HEIGHT_IN_SOUNDBUFFER) / TILE_HEIGHT_IN_SOUNDBUFFER;

	if (nTileX < 0)
		return 10000;
	else if (nTileX >= SOUND_TILE_X)
		return -10000;

	if (nTileX == (SOUND_TILE_CENTER_X-1) ||								// 중앙 근처 1타일 씩은 중앙과 같은 panning값을 갖도록 한다.
		nTileX == (SOUND_TILE_CENTER_X +1) )
		nTileX = SOUND_TILE_CENTER_X;

	int nPans = (nTileX - SOUND_TILE_CENTER_X) * PANNING_VALUE_PER_TILE;

	if (g_SoundManager.mSndMngr_bRevereLR == TRUE)
		return -nPans;
	else
		return nPans;
}

/***** Func63 *** Lee Kyoung Soo / 2002.10.30 *******************************/
IDirectSoundBuffer*
SndObjGetBuffer(
	SNDOBJ		*pSO,
	int			nIdx)
{
    IDirectSoundBuffer *pDSB;

    if (pSO == NULL)
        return NULL;

    pDSB = pSO->Buffers[nIdx];
	if (pDSB == NULL)
		return NULL;
	else
		return pDSB;
}

/***** Func64 *** Lee Kyoung Soo / 2002.10.30 *******************************/
void
SndObjSetVolnPan(
	int					nScrnX,
	int					nScrnY,
	IDirectSoundBuffer	*pDSB)
{
	int		nScreenLocationX, nScreenLocationY;
	int		nVolume, nPan;

	if (pDSB == NULL)
		return;

	if (nScrnX == 0 && nScrnY == 0)
	{
		nScreenLocationX = 0;
		nScreenLocationY = 0;
	}
	else
	{
		g_xGameProc.m_xMap.GetScrnPosFromTilePos(nScrnX, nScrnY, nScreenLocationX, nScreenLocationY);
	}

	nVolume = CalsVolume(nScreenLocationX, nScreenLocationY);
	nPan = CalsPan(nScreenLocationX, nScreenLocationY);
	pDSB->SetPan(-nPan);
	nVolume += g_SoundManager.mSndMngr_lWavMaxVol * 40;

	if (nVolume < -10000)
		nVolume = -10000;

	pDSB->SetVolume((long)nVolume);
}
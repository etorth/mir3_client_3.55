// File:       SoundManager.h

#ifndef __SoundManager_H__
#define __SoundManager_H__


#define	MAX_SOUND			50
#define	SOUND_TILE_X		17
#define	SOUND_TILE_Y		15
#define	SOUND_TILE_CENTER_X 8
#define	SOUND_TILE_CENTER_Y 7


class SoundManager : public DSound
{
// Constructor & Destructor
public:
	SoundManager();
	virtual ~SoundManager();

// Attributes
public:
	BOOL					mSndMngr_bInit;
	BOOL					mSndMngr_bMusicOn;
	BOOL					mSndMngr_bSoundOn;
	BOOL					mSndMngr_bWavePlay;
	int						mSndMngr_nSoundVolume;

	LONG					mSndMngr_lWavMaxVol;
	LONG					mSndMngr_lMp3MaxVol;

	long					mSndMngr_lVolumeBuffer[SOUND_TILE_X][SOUND_TILE_Y];

	WAVELISTHEADER			mSndMngr_pWavListHeader;
	WAVELIST*				mSndMngr_pWavList;

	HSNDOBJ					mSndMngr_pIdxBuffer[MAX_SOUND];
	

	CBMMp3*					mSndMngr_pMp3;						// Object of BGM(Mp3)

	BGMLISTHEADER			mSndMngr_pBGMListHeader;
	BGMLIST*				mSndMngr_pBGMList;

	BOOL					mSndMngr_bMP3Play;
	CHAR					mSndMngr_szNextMp3[MAX_PATH];

	BOOL					mSndMngr_bRevereLR;

// Operations
public:
	int						SndmngrLoadSound(int nIdx);
	int						SndmngrPlayWavSound(int nIdx, int nScrnX, int nScrnY, BOOL bLooping = FALSE);
	void					SndmngrStopWavSound(int nIdx, int nBufIdx);
	void					SndmngrStopWavSound(int nIdx);

	char*					SndmngrSeekFileName(int wavnum);
	void					ReadWaveFileList(char* fName);

	BOOL					SndmngrChgVolnPan(INT nWavIdx,INT nBufferIdx,INT nTileLocationX,INT nTileLocationY);

	void					SndmngrPlayMp3(CHAR* szMapName, BOOL Looped, INT nIndex);
	HRESULT					SndmngrMessageProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void					SndmngrPlayMp3(CHAR* pszFileName,BOOL Loop);
	void					SndmngrStopMp3(VOID);
	BOOL					SndmngrIsPlayingBGM(void);
	void					SndmngrReadBGMFileList(char* fName);
	char*					SndmngrFindBgmFileName(CHAR* szMapName);
	VOID					SndmngrSetEnableBGM(VOID);
	VOID					SndmngrSetDisableBGM(VOID);
	void					SndmngrSetEnableWavePlay(VOID);
	void					SndmngrSetDisableWavePlay(VOID);
	void					SndmngrStopAllWaveSound(void);
	void					SndmngrReleaseAllWaveSound(void);
};

extern SoundManager		g_SoundManager;	
#endif // __SoundManager_H__
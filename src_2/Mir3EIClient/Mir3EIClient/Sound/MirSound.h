// MirSound.h: interface for the CMirSound class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIRSOUND_H__4F9FCB9C_4210_464E_81FF_F4BDEA07785B__INCLUDED_)
#define AFX_MIRSOUND_H__4F9FCB9C_4210_464E_81FF_F4BDEA07785B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_AMBIANCE_COUNT	9


class CMirSound  
{
public:
	BOOL		ChgPlayingSet(INT nWavIdx,INT nBufferIdx,INT Sx,INT Sy,INT Dx,INT Dy);
	BOOL		FreeNotUseBuffer(VOID);
	BOOL		InitMirSound(HWND hWnd);
	CSBuffer*	FindBuffer(int nNum,BOOL ForLoad=TRUE);
	CSound*		GetSoundObject(VOID){return m_pSound;}

	void		StopAllSound(void);
	void		StopSound(int nNum);
	void		StopSound(int nNum,int BufIdx);

	void		PlayAmbianceWav(int WavNum);
	void		StopBkMusicMp3(void);
	void		PlayBkMusicMp3(BOOL Looped, CHAR* szMapName);
	BOOL		FindBGMFileName(CHAR*szMapName, CHAR* szMp3FileName);

	void		PlayMagicEffect(POINT Target,POINT Chr,int Wavnum);
	INT			PlayActorWav(INT Sx,INT Sy,INT Dx,INT Dy,int Wavnum,INT lVolume=100,BOOL bLooping=FALSE);	// lVolume = 100% ~ 1%   

	BOOL		BGMFadeOut(LONG lTime=(5000)/*5ÃÊ*/,LONG	lMinVol=(-5000)); 
	BOOL		BGMFadeIn(LONG lMaxVol=-100);
	VOID		EndFading(INT nState);

	VOID		SetInWarMode(VOID);
	VOID		SetInPeaceMode(VOID);
	BOOL		SetMasterVol(INT nVolume);
	BOOL		SetBGMVol(INT nVolume);
	BOOL		SetWavVol(INT nVolume);

	HRESULT		MessageProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	CMirSound();
	virtual ~CMirSound();
	///////////////////////////////////////////////////////////////////
	VOID		SetDisableBGM(VOID);			// Can't play BGM
	VOID		SetEnableBGM(VOID);			// Can Play BGM
	VOID		SetDisablePlay(VOID);		// Can't play Wav
	VOID		SetEnablePlay(VOID);		// Can play Wav
	VOID		SetDisableAmbiance(VOID);	// can't play Ambiance
	VOID		SetEnableAmbiance(INT nMapNum,INT nCount);	// can play Ambiance
	VOID		Enable3D(VOID);				// Using 3D effect

	CBMMp3*		m_pMp3;						// Object of BGM(Mp3)
	CSBuffer*	m_pAmbianceBuffer[MAX_AMBIANCE_COUNT];		// Only Ambiance's Buffer
	BOOL		m_bRunningTimer;
	LONG		m_lWavMaxVol;
	LONG		m_lMp3MaxVol;
	INT			m_nAmbienceNum;
	INT			m_nAmbianceCount;

private:

	HWND		m_hWnd;
	BOOL		m_bPlay;					// Sound°¡ ³ª¿Íµµ µÅ´Â°Å?
	BOOL		m_bBGMPlay;					// BGM ÀÌ Play µÇ¾îµµ µÅ´Â°¡?
	BOOL		m_bAmbiance;				// Ambiance Wave°¡ Play µÇ¾îµµ µÅ´Â°¡?
	BOOL		m_3DEnable;					// 3D Sound Effect Enable
	INT			m_nUseCount;				// »ç¿ë µÅ°í ÀÖ´Â Sound(Wav) Buffer Count
	CSound*		m_pSound;					// Object of Sound
	CSBuffer**	m_ppBuffer;					// Object of Sound Buffer
	CSBuffer	m_CommonWavBuffer;			// Common use Wave Buffer
	BOOL		m_bIsWarMode;

	WAVELISTHEADER*	m_pWavListHeader;
	WAVELIST**	m_ppWavList;				//wavÎÄ¼þÁÐ±í
	WAVELISTHEADER* m_pBgmListHeader;
	CHAR*		m_pBgmFileList;				//±³¾°ÒôÀÖÁÐ±í


	char*		SeekFileName(int wavnum);
	void		ReadWavFileList(char* fName);
	void		ReadBgmFileList(char* fName);
	int			CalsVolume(int Dis);
	int			CalsPan(int Dir,int Dis);
	float		CalsDistanceX(POINT Src,POINT Chr);
	float		CalsDistanceY(POINT Src,POINT Chr);
	INT			CalsDistance(POINT Src,POINT Chr);
	INT			CalsDirection(POINT Src,POINT Chr);
};

#endif // !defined(AFX_MIRSOUND_H__4F9FCB9C_4210_464E_81FF_F4BDEA07785B__INCLUDED_)

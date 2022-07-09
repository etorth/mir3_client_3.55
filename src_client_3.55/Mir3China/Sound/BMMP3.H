// CBMMp3.h: interface for the CBMMp3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBMMp3_H__E7B9DE69_5CF3_4A3A_AE0D_D13BD100E109__INCLUDED_)
#define AFX_CBMMp3_H__E7B9DE69_5CF3_4A3A_AE0D_D13BD100E109__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#define	WM_DSHOW_NOTIFY	WM_APP+500  // Pivate message

class CBMMp3  
{
/* Constructor & Destructor */
public:
	CBMMp3();
	virtual ~CBMMp3();

/* Attributes */
public:
	LONG					mBmmp3_lVolume;
	BOOL					mBmmp3_bLooping;			// Is this Mp3 Media Looping Play?
	BOOL					mBmmp3_bLaterPlay;
	LONG					mBmmp3_lDelay;
	CHAR					mBmmp3_szFileName[MAX_PATH];

private:
	IBasicAudio				*mBmmp3_pBasicAudio;
	IMediaControl			*mBmmp3_pMediaControl;
	IMediaSeeking			*mBmmp3_pMediaSeeking;
	IMediaPosition			*mBmmp3_pMediaPosition;
	IMediaEventEx			*mBmmp3_pMediaEventEx;
	IGraphBuilder			*mBmmp3_pGraphBuilder;

	BOOL					mBmmp3_bIsPlaying;		// Is this Mp3 Media playing?
	BOOL					mBmmp3_bInited;			// Is this class initialized?
//	BOOL					m_bLooping;			// Is this Mp3 Media Looping Play?
	HWND					mBmmp3_hWnd;		// Handle of this class's owner
	BOOL					mBmmp3_bIsLoadMp3;
	INT						mBmmp3_nTimerID;

/* Operation */
public:
	BOOL					Bmmp3LoadMp3(CHAR*	szFileName,HWND hWnd);
	BOOL					Bmmp3OnPlay(LONG lVolume,BOOL Looping);
	BOOL					Bmmp3OnStop(VOID);
	BOOL					Bmmp3OnPause(VOID);
	BOOL					Bmmp3Init(HWND hWnd);
	BOOL					Bmmp3SetVolume(LONG lVolume);
	LONG					Bmmp3GetVolume(VOID);
	BOOL					Bmmp3SetNotifyWindow(LONG lMsg,LONG lOnOff);
	BOOL					Bmmp3SetNotifyFlags(LONG lFlag);
	HRESULT					Bmmp3MessageProcess(VOID);
	VOID					Bmmp3Release(VOID);
	BOOL					Bmmp3CleanGraph();
	BOOL					Bmmp3JustReplay();

	__inline BOOL	IsPlaying(VOID)
	{
		return mBmmp3_bInited;
	}
	__inline BOOL	IsbePlaying(VOID)
	{
		return mBmmp3_bIsPlaying;
	}
};

#endif // !defined(AFX_CBMMp3_H__E7B9DE69_5CF3_4A3A_AE0D_D13BD100E109__INCLUDED_)

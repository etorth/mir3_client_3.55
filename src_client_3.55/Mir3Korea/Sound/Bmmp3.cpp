/*
		FileName            : BMMP3.cpp
		Description         : BMMP3 class
		Author/Date         : 
		Modification History: 2002.08.29 - add Bmmp3JustReplay(), Bmmp3CleanGraph()
		-----------------------------------------------------
		01.						CBMMp3();
		02.						~CBMMp3();
		03.BOOL					Bmmp3Init();
		04.BOOL					Bmmp3LoadMp3();
		06.BOOL					Bmmp3OnPlay();
		09.BOOL					Bmmp3OnStop();
		10.BOOL					Bmmp3OnPause();
		11.HRESULT				Bmmp3MessageProcess();
		12.VOID					Bmmp3Release();
		13.BOOL					Bmmp3SetVolume();
		14.LONG					Bmmp3GetVolume();
		15.BOOL					Bmmp3SetNotifyWindow();
		16.BOOL					Bmmp3SetNotifyFlags();
		17.BOOL					Bmmp3JustReplay();
		18.BOOL					Bmmp3CleanGraph();
*/

#include "stdafx.h"
#include <malloc.h> 

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/***** Func01 ****************************************************************/
CBMMp3::CBMMp3()
{
	CoInitialize(NULL);
	mBmmp3_pBasicAudio = NULL;
	mBmmp3_pMediaControl= NULL;
	mBmmp3_pMediaSeeking= NULL;
	mBmmp3_pMediaPosition= NULL;
	mBmmp3_pMediaEventEx= NULL;
	mBmmp3_pGraphBuilder= NULL;
	mBmmp3_bIsPlaying = FALSE;		// Is this Mp3 Media playing?
	mBmmp3_bInited = FALSE;			// Is this class initialized?
	mBmmp3_bLooping = FALSE;			// Is this Mp3 Media Looping Play?
	mBmmp3_hWnd = NULL;				// Handle of this class's owner
	mBmmp3_bIsLoadMp3 = FALSE;
	mBmmp3_bLaterPlay = FALSE;
	mBmmp3_lDelay = 0;
}

/***** Func02 ****************************************************************/
CBMMp3::~CBMMp3()
{
	Bmmp3Release();
	CoUninitialize();
}

/***** Func03 ****************************************************************/
BOOL CBMMp3::Bmmp3Init(HWND hWnd)
{
	HRESULT	hResult;
	mBmmp3_bInited = TRUE;
	mBmmp3_hWnd = hWnd;
	
	if(SUCCEEDED(CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC, IID_IGraphBuilder, (LPVOID *)&mBmmp3_pGraphBuilder)))
	{
		if ( mBmmp3_pGraphBuilder != NULL )
		{
			hResult = mBmmp3_pGraphBuilder->QueryInterface(IID_IMediaControl, (void **)&mBmmp3_pMediaControl);
			if(FAILED(hResult))
				mBmmp3_bInited = FALSE;

			hResult = mBmmp3_pGraphBuilder->QueryInterface(IID_IBasicAudio, (void **)&mBmmp3_pBasicAudio);
			if(FAILED(hResult))
				mBmmp3_bInited = FALSE;

			hResult = mBmmp3_pGraphBuilder->QueryInterface(IID_IMediaSeeking,(void **)&mBmmp3_pMediaSeeking);
			if(FAILED(hResult))
				mBmmp3_bInited = FALSE;

			hResult = mBmmp3_pGraphBuilder->QueryInterface(IID_IMediaEventEx,(void **)&mBmmp3_pMediaEventEx);
			if(FAILED(hResult))
				mBmmp3_bInited = FALSE;

			hResult = mBmmp3_pGraphBuilder->QueryInterface(IID_IMediaPosition,(void **)&mBmmp3_pMediaPosition);
			if(FAILED(hResult))
				mBmmp3_bInited = FALSE;
		}
		else
		{
			mBmmp3_bInited = FALSE;
		}
	}
	else
	{
		mBmmp3_bInited = FALSE;
	}
	return mBmmp3_bInited;
}

/***** Func04 ****************************************************************/
BOOL CBMMp3::Bmmp3LoadMp3(CHAR*	szFileName,HWND hWnd)
{
	WCHAR	wcFileName[MAX_PATH];

	if (mBmmp3_bIsPlaying == TRUE)
		Bmmp3OnStop();

	if (Bmmp3Init(hWnd))
	{
		MultiByteToWideChar(CP_ACP, 0, szFileName, -1, wcFileName, MAX_PATH);
		strcpy(mBmmp3_szFileName,szFileName);
		if(mBmmp3_pGraphBuilder!=NULL)
		{
			if(SUCCEEDED(mBmmp3_pGraphBuilder->RenderFile(wcFileName, NULL)))
				mBmmp3_bIsLoadMp3 = TRUE;
			else
				mBmmp3_bIsLoadMp3 = FALSE;
		}
		else
			mBmmp3_bIsLoadMp3 = FALSE;
	}

	return TRUE;
}

/***** Func06 ****************************************************************/
BOOL CBMMp3::Bmmp3OnPlay(LONG lVolume,BOOL Looping)
{
	if(mBmmp3_bInited && mBmmp3_bIsLoadMp3)
	{
		if(mBmmp3_bIsPlaying)
		{
			Bmmp3OnStop();
		}

		mBmmp3_bLooping = Looping;

		if(mBmmp3_pMediaControl!=NULL)
		{
			if (FAILED(mBmmp3_pMediaControl->Run()))
				return FALSE;
			Bmmp3SetVolume(lVolume);
			Bmmp3SetNotifyWindow(WM_DSHOW_NOTIFY,0x00);
			mBmmp3_bIsPlaying = TRUE;
		}
		else
			return FALSE;
	}
	else
		return FALSE;
	return TRUE;
}

/***** Func09 ****************************************************************/
BOOL CBMMp3::Bmmp3OnStop(VOID)
{
	if (mBmmp3_bInited && mBmmp3_bIsLoadMp3)
	{
		if(mBmmp3_bIsPlaying)
		{
			Bmmp3SetNotifyFlags(AM_MEDIAEVENT_NONOTIFY);	// WM_DSHOW_NOTIFY 를 발생시키지 않음
			if(mBmmp3_pMediaControl!=NULL && mBmmp3_pMediaPosition!=NULL)
			{
				if(FAILED(mBmmp3_pMediaControl->Pause()))
				{
					return FALSE;
				}

				if(FAILED(mBmmp3_pMediaControl->Stop()))
				{
					return FALSE;
				}

				mBmmp3_pMediaPosition->put_CurrentPosition(0);	// 처음으로 돌리다.
				mBmmp3_bIsPlaying = FALSE;
				Bmmp3Release();
			}
			else
				return FALSE;
		}
		else
			return FALSE;
	}
	return TRUE;
}

/***** Func10 ****************************************************************/
BOOL CBMMp3::Bmmp3OnPause(VOID)
{
	if(mBmmp3_bInited&&mBmmp3_bIsLoadMp3)
	{
		if(mBmmp3_bIsPlaying)
		{
			if(mBmmp3_pMediaControl!=NULL)
			{
				if(FAILED(mBmmp3_pMediaControl->Pause()))
					return FALSE;
				mBmmp3_bIsPlaying = TRUE;
			}
			else
				return FALSE;
		}
		else
			return FALSE;
	}
	return TRUE;
}

/***** Func11 ****************************************************************/
HRESULT CBMMp3::Bmmp3MessageProcess(VOID)
{
	LONG evCode, evParam1, evParam2;
	if(mBmmp3_pMediaEventEx!=NULL)
	{
		while(SUCCEEDED(mBmmp3_pMediaEventEx->GetEvent(&evCode, &evParam1, &evParam2,0)))
		{
			switch(evCode)
			{
			case EC_WINDOW_DESTROYED:
				Bmmp3OnStop();
				break;
			case EC_COMPLETE:					//스트림의 랜더링을 마치면 오는 신호
				if(mBmmp3_bLooping)
				{
					mBmmp3_bIsPlaying = FALSE;
					Bmmp3JustReplay();
					return 0l;
				}
				else 
				{
					return 0l;
				}
				break;
			case EC_ACTIVATE:
				break;
			}
			mBmmp3_pMediaEventEx->FreeEventParams(evCode, evParam1, evParam2);
		}
	}
	return 0l;
}

/***** Func12 ****************************************************************/
VOID CBMMp3::Bmmp3Release(VOID)
{
	if(mBmmp3_bIsPlaying)
		Bmmp3OnStop();

//	Bmmp3CleanGraph();

	timeKillEvent(mBmmp3_nTimerID);

	if(mBmmp3_pMediaPosition!=NULL)
	{
		mBmmp3_pMediaPosition->Release();
		mBmmp3_pMediaPosition = NULL;
	}
	if(mBmmp3_pMediaEventEx!=NULL)
	{
		mBmmp3_pMediaEventEx->Release();
		mBmmp3_pMediaEventEx = NULL;
	}
	if(mBmmp3_pMediaSeeking!=NULL)
	{
		mBmmp3_pMediaSeeking->Release();
		mBmmp3_pMediaSeeking = NULL;
	}
	if(mBmmp3_pBasicAudio!=NULL)
	{
		mBmmp3_pBasicAudio->Release();
		mBmmp3_pBasicAudio = NULL;
	}
	if(mBmmp3_pMediaControl!=NULL)
	{
		mBmmp3_pMediaControl->Release();
		mBmmp3_pMediaControl = NULL;
	}
	if(mBmmp3_pGraphBuilder!=NULL)
	{
		mBmmp3_pGraphBuilder->Release();
		mBmmp3_pGraphBuilder= NULL;
	}
	
	mBmmp3_bInited = FALSE;
}

/***** Func13 ****************************************************************/
BOOL CBMMp3::Bmmp3SetVolume(LONG lVolume)
{
	lVolume = lVolume * 40;
	if(mBmmp3_bInited && mBmmp3_bIsLoadMp3)
	{
		if(mBmmp3_pBasicAudio!=NULL)
			if(FAILED(mBmmp3_pBasicAudio->put_Volume(lVolume)))
				return FALSE;
	}
	return TRUE;
}

/***** Func14 ****************************************************************/
LONG CBMMp3::Bmmp3GetVolume(VOID)
{
	LONG	lResult = 0;;
	if(mBmmp3_bInited && mBmmp3_bIsLoadMp3)
	{
		if(mBmmp3_bIsPlaying)
		{
			if(mBmmp3_pBasicAudio!=NULL)
				mBmmp3_pBasicAudio->get_Volume(&lResult);
		}
	}
	return lResult;
}

/***** Func15 ****************************************************************/
////////////////////////////////////////////////////////////////
// Set Message that is Event occur
// lMsg : Long
// cOnOff : BYTE  (ex) On = 0x00     Off = 0x01
/////////////////////////////////////////////////////////////////
BOOL CBMMp3::Bmmp3SetNotifyWindow(LONG lMsg,LONG lOnOff)
{
	if(mBmmp3_pMediaEventEx!=NULL)
	{
		if(FAILED(mBmmp3_pMediaEventEx->SetNotifyWindow((OAHWND)mBmmp3_hWnd, lMsg ,0))) return FALSE;
		if(Bmmp3SetNotifyFlags(lOnOff)) return FALSE;
	}
	return TRUE;
}

/***** Func16 ****************************************************************/
BOOL CBMMp3::Bmmp3SetNotifyFlags(LONG lFlag)
{
	if(mBmmp3_pMediaEventEx!=NULL)
	{
		if(FAILED(mBmmp3_pMediaEventEx->SetNotifyFlags(lFlag))) return FALSE;
	}
	return TRUE;
}

/***** Func17 *** Lee Kyoung Soo / 2002.08.29 **********************************/
BOOL
CBMMp3::Bmmp3JustReplay()
{
	if(mBmmp3_pMediaControl!=NULL && mBmmp3_pMediaPosition!=NULL)
	{
		if(FAILED(mBmmp3_pMediaControl->Pause()))
		{
#ifdef _DEBUG
			_ASSERT(0);
#endif //_DEBUG
			return FALSE;
		}

		mBmmp3_pMediaPosition->put_CurrentPosition(0);	// 처음으로 돌리다.

		if(FAILED(mBmmp3_pMediaControl->Run()))
		{
#ifdef _DEBUG
			_ASSERT(0);
#endif //_DEBUG
			return FALSE;
		}

		mBmmp3_bIsPlaying = TRUE;
		return TRUE;
	}
#ifdef _DEBUG
	_ASSERT(0);
#endif //_DEBUG
	return FALSE;
}

/***** Func18 *** Lee Kyoung Soo / 2002.08.29  **********************************/
//  인  자 : 없음
//  리턴값 : 성공여부
//  설  명 : 그래프에 있는 모든 필터들을 제거한다
//------------------------------------------------------------------------------
BOOL
CBMMp3::Bmmp3CleanGraph()
{
	int nFiltCount = 0;
	int nPos = 0;

	IEnumFilters *pFilterEnum;
	IBaseFilter  **ppFilters;

	// 그래프 내의 모든 필터를 얻기 위해 EnumFilters 포인터를 얻는다.
	if ( mBmmp3_pGraphBuilder )
	{
		if (mBmmp3_pGraphBuilder->EnumFilters (&pFilterEnum) != S_OK)
			return false;

		// 필터의 갯수를 파악
		while (S_OK == pFilterEnum->Skip (1))
		nFiltCount++;

		ppFilters = reinterpret_cast <IBaseFilter **> 
		(_alloca (sizeof (IBaseFilter *) * nFiltCount));

		pFilterEnum->Reset ();

		// 필터에 대한 포인터를 모두 얻어온다
		while (S_OK == pFilterEnum->Next (1, &(ppFilters[nPos++]), NULL));
		SAFE_RELEASE (pFilterEnum);

		// 모든 필터를 그래프에서 제거한다
		for (nPos = 0; nPos < nFiltCount; nPos++)
		{
			mBmmp3_pGraphBuilder->RemoveFilter (ppFilters[nPos]);

			// ref count 수 만큼 한다
			while (int nI = ppFilters[nPos]->Release () != 0);
		}
	}
	return true;
}

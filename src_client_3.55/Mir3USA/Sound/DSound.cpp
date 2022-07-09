/*
		FileName            : DSound.cpp
		Description         : DirectSound
		Author/Date         : Lee Kyoung Soo / 2002.10.29
		Modification History:
		-----------------------------------------------------
		01.					DSound::DSound();
		02.					DSound::~DSound()

		11.HRESULT			DSound::UsndInitDirectSound();

		31.void				DSound::UsndTurnListener();
*/

//#include <dmusicc.h>
//#include <dmusici.h>
//#include "../../Global.h"
//#include "DSound.h"
//#include "../../Error/UErrorGlobal.h"

#include "StdAfx.h"

#ifndef _RELEASE_POINTER
#define _RELEASE_POINTER
#define RELEASE_POINTER(p) \
{\
	if (p != NULL) \
	{	\
		p->Release(); \
		p = NULL; \
	} \
}
#endif //_RELEASE_POINTER

//#pragma comment(lib, "dsound.lib")

/***** Static members *****************************************************/
LPDIRECTSOUND			DSound::mSound_lpds = NULL;				// Direct Sound
LPDIRECTSOUND3DLISTENER DSound::mSound_lp3DListener = NULL;		// 3D Listener
HWND					DSound::mSound_hWnd = NULL;				// Handle of window

/*
struct _SOUNT_INT
{
	~_SOUNT_INT()
	{
	    RELEASE_POINTER(DSound::mSound_lp3DListener);
	    RELEASE_POINTER(DSound::mSound_lpds);
	}
} SOUND_INIT;
*/

/***** Func01 *** Lee Kyoung Soo / 2002.10.29 *******************************/
DSound::DSound()
{
	mSound_bIsMID = FALSE;
}

/***** Func02 *** Lee Kyoung Soo / 2002.10.29 *******************************/
DSound::~DSound()
{
    RELEASE_POINTER(mSound_lp3DListener);
    RELEASE_POINTER(mSound_lpds);
}

/***** Func11 *** Lee Kyoung Soo / 2002.10.29 *******************************/
HRESULT
DSound::UsndInitDirectSound(
	HWND		hWnd )
{
	if (mSound_lpds) return(S_OK);
	mSound_hWnd = hWnd;

    DSBUFFERDESC        dsbd;
    LPDIRECTSOUNDBUFFER lpdsbPrimary;
    WAVEFORMATEX        wfm;

    if( FAILED( DirectSoundCreate( NULL, &mSound_lpds, NULL ) ) )
        return E_FAIL;

    // Set cooperative level.
    if( FAILED( mSound_lpds->SetCooperativeLevel( mSound_hWnd, DSSCL_NORMAL ) ) )
        return E_FAIL;

    // Create primary buffer.
    ZeroMemory( &dsbd, sizeof( DSBUFFERDESC ) );
    dsbd.dwSize  = sizeof( DSBUFFERDESC );
    dsbd.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;
    
    if( FAILED( mSound_lpds->CreateSoundBuffer( &dsbd, &lpdsbPrimary, NULL ) ) )
        return E_FAIL;

    // Set primary buffer format.
    ZeroMemory( &wfm, sizeof( WAVEFORMATEX ) ); 
    wfm.wFormatTag      = WAVE_FORMAT_PCM; 
    wfm.nChannels       = 2; 
    wfm.nSamplesPerSec  = 44100; 
    wfm.wBitsPerSample  = 16; 
    wfm.nBlockAlign     = wfm.wBitsPerSample / 8 * wfm.nChannels;
    wfm.nAvgBytesPerSec = wfm.nSamplesPerSec * wfm.nBlockAlign;

    lpdsbPrimary->SetFormat( &wfm ); 

    // Get listener interface.
    if( FAILED( lpdsbPrimary->QueryInterface( IID_IDirectSound3DListener,
                                              (VOID**)&mSound_lp3DListener ) ) )
    {
        lpdsbPrimary->Release();
        return E_FAIL;
    }
    lpdsbPrimary->Release(); lpdsbPrimary = NULL;

    return(S_OK);
}

/***** Func31 *** Lee Kyoung Soo / 2002.10.29 *******************************/
void
DSound::UsndTurnListener(
	D3DVALUE	lx,
	D3DVALUE	ly,
	D3DVALUE	lz )
{
    HRESULT		hr = mSound_lp3DListener->SetOrientation(
                                lx, ly, lz, 
                                0.0, 1.0, 0.0,
                                DS3D_IMMEDIATE );
}  // TurnListener()


// File:       DSound.h

#ifndef __DSound_H__
#define __DSound_H__

class DSound
{
// Constructor & Destructor
public:
	DSound();
	virtual ~DSound();

// Attributes
public:
	static LPDIRECTSOUND			mSound_lpds;			// Direct Sound
	static LPDIRECTSOUND3DLISTENER	mSound_lp3DListener;	// 3D Listener
	static HWND						mSound_hWnd;			// Handle of window
	BOOL							mSound_bIsMID;

// Operations
public:
	
	static HRESULT			UsndInitDirectSound(HWND hWnd);

	virtual int				UsndLoadSound(LPTSTR szFullPath) { return(0); }
	virtual void			UsndPlaySound(int nScrnX, int nScrnY, BOOL bReset = TRUE) {}
	virtual void			UsndStopSound() {}
	virtual void			UsndSetVolume(long lVolume) {}
	virtual void			UsndSetPan(long lPan) {}

	void					UsndTurnListener(D3DVALUE lx, D3DVALUE ly, D3DVALUE lz );


};


#endif // __DSound_H__
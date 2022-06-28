/******************************************************************************************************************
                                                                                                                   
	����:																											
																													
	�ۼ���:																											
	�ۼ���:																											
																													
	[����][������] : ���� ����																						
                                                                                                                   
*******************************************************************************************************************/


#include "stdafx.h"
#include "WHEngine.h"
#include <windows.h>


/*********************************************************************************************

	// ORZ: ���� ���� ��ũ��

 *********************************************************************************************/
#define ALPHA_565_MASK1		0xf81f07e0
#define ALPHA_565_MASK2		0x07e0f81f


/*********************************************************************************************

	// ORZ: ���� ��ũ�� �Լ� ����

	- �ҽ� ���!

 *********************************************************************************************/
#define IS_OUTSIDE( nX, nY, nXSize, nYSize )\
	( nX > 800 || nX + nXSize < 0 || nY > 600 || nY + nYSize < 0 )

#define CREATE_CLIP_REGION( nX, nY, nXSize, nYSize )\
	if ( nX + nXSize > 800 )	{ rc.right	= 800 -nX; }\
	else						{ rc.right	= nXSize; }\
	if ( nX < 0 )				{ rc.left	= -nX; nX = 0; }\
	else						{ rc.left	= 0; }\
	if ( nY + nYSize > 600 )	{ rc.bottom	= 600 - nY; }\
	else						{ rc.bottom	= nYSize; }\
	if ( nY < 0 )				{ rc.top	= -nY; nY = 0; }\
	else						{ rc.top	= 0; }\
\
	imgW = rc.right - rc.left;\
	imgH = rc.bottom - rc.top;

#define SURFACE_LOCK( surface )\
	ddsd.dwSize = sizeof( DDSURFACEDESC2 );\
	if ( FAILED( surface->Lock( NULL, &ddsd, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL ) ) ) return FALSE;\
	ddsd.lPitch >>= 1;

#define SURFACE_UNLOCK( surface )\
	surface->Unlock( NULL );



/*********************************************************************************************

	// ORZ: ���� �ζ��� �Լ�

 *********************************************************************************************/
__forceinline void putAlpha32Pixel( WORD *dst, WORD src, byte srclevel )
{
	static DWORD src1, src2, dst1, dst2;

	int dstlevel = 32 - srclevel;

	src1 = src;
	src2 = src1;
	
	src1 &=	 ALPHA_565_MASK1;
	src1 >>= 5;
	src1 *=  srclevel;
	src1 &=  ALPHA_565_MASK1;
	
	src2 &=  ALPHA_565_MASK2;
	src2 *=  srclevel;
	src2 >>= 5;
	src2 &=  ALPHA_565_MASK2;
	src2 |=  src1;
	
	dst1 = *dst;
	dst2 = dst1;
	
	dst1 &=  ALPHA_565_MASK1;
	dst1 >>= 5;
	dst1 *=  dstlevel;
	dst1 &=  ALPHA_565_MASK1;
	
	dst2 &=  ALPHA_565_MASK2;		
	dst2 *=  dstlevel;
	dst2 >>= 5;
	dst2 &=  ALPHA_565_MASK2;
	dst2 |=  dst1;
	
	*dst++ = (WORD) (dst2 + src2);
}


__forceinline void putAlpha32( WORD *dst, WORD *src, int len, byte srclevel )
{
	static DWORD src1, src2, dst1, dst2;

	int dstlevel = 32 - srclevel;

	if ( len & 1 )
	{
		src1 = *src++;
		src2 = src1;
		
		src1 &=	 ALPHA_565_MASK1;
		src1 >>= 5;
		src1 *=  srclevel;
		src1 &=  ALPHA_565_MASK1;

		src2 &=  ALPHA_565_MASK2;
		src2 *=  srclevel;
		src2 >>= 5;
		src2 &=  ALPHA_565_MASK2;
		src2 |=  src1;
		
		dst1 = *dst;
		dst2 = dst1;

		dst1 &=  ALPHA_565_MASK1;
		dst1 >>= 5;
		dst1 *=  dstlevel;
		dst1 &=  ALPHA_565_MASK1;

		dst2 &=  ALPHA_565_MASK2;		
		dst2 *=  dstlevel;
		dst2 >>= 5;
		dst2 &=  ALPHA_565_MASK2;
		dst2 |=  dst1;
		
		*dst++ = (WORD) (dst2 + src2);
	}

	for ( int i = 0; i < len >> 1; i++ )
	{
		src1 = *((DWORD *) src);
		src2 = src1;
		
		src1 &=	 ALPHA_565_MASK1;
		src1 >>= 5;
		src1 *=  srclevel;
		src1 &=  ALPHA_565_MASK1;

		src2 &=  ALPHA_565_MASK2;
		src2 *=  srclevel;
		src2 >>= 5;
		src2 &=  ALPHA_565_MASK2;
		src2 |=  src1;
		
		dst1 = *((DWORD *) dst);
		dst2 = dst1;

		dst1 &=  ALPHA_565_MASK1;
		dst1 >>= 5;
		dst1 *=  dstlevel;
		dst1 &=  ALPHA_565_MASK1;

		dst2 &=  ALPHA_565_MASK2;			
		dst2 *=  dstlevel;
		dst2 >>= 5;
		dst2 &=  ALPHA_565_MASK2;
		dst2 |=  dst1;
		
		*((DWORD *) dst) = dst2 + src2;

		dst += 2;
		src += 2;
	}
}


/******************************************************************************************************************

	CWHDXGraphicWindow Functions

*******************************************************************************************************************/


static BYTE						g_bNumDevices = 0;
static DXG_ENUM_DEVICEINFO		g_stDXGEnumDeviceInfo[_MAX_DEVICES];

static INT						DXGModesSortCallback(const VOID* arg1, const VOID* arg2);
static BOOL		WINAPI			DXGDriverEnumCallbackEx(GUID* pGUID, LPSTR szDesc, LPSTR szName, LPVOID pContext, HMONITOR hm);
static HRESULT	WINAPI			DXGEnumDisplayModeCallback(DDSURFACEDESC2* pddsd, VOID* pParentInfo);
static HRESULT	WINAPI			DXG3DDeviceEnumCallback(TCHAR* szDesc, TCHAR* szName, D3DDEVICEDESC7* pDesc, VOID* pParentInfo);
static HRESULT	WINAPI			DXGEnumZBufferFormatsCallback(DDPIXELFORMAT* pddpf, VOID* pContext);


// DX ���� üũ��.
extern DWORD GetDXVersion();



CWHDXGraphicWindow* CWHDXGraphicWindow::m_pxDXGWnd = NULL;

CWHDXGraphicWindow* GetDXGWindowPtr()
{
	return CWHDXGraphicWindow::m_pxDXGWnd;
}


/******************************************************************************************************************

	�Լ��� : CWHDXGraphicWindow::CWHDXGraphicWindow()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : WORD wWidth
	         WORD wHeight
	         WORD wBpp
	���   : 

	[����][������] : ��������

*******************************************************************************************************************/
CWHDXGraphicWindow::CWHDXGraphicWindow(WORD wWidth, WORD wHeight, WORD wBpp)
{
	m_pDD				= NULL;
	m_pD3D				= NULL;
	m_hDefGameFont		= NULL;
	m_pd3dDevice		= NULL;
	m_pddsZBuffer		= NULL;
    m_pddsFrontBuffer	= NULL;
    m_pddsBackBuffer	= NULL;
//	����Ʈ������ ����� ���ؼ� Ŭ���۸� �����Ѵ�.
	m_lpcClipper		= NULL;

	ZeroMemory(m_pszDefFont, MAX_PATH);

	m_stDisplayInfo.wWidth	= wWidth;
	m_stDisplayInfo.wHeight	= wHeight;
	m_stDisplayInfo.wBPP	= wBpp;
	m_bScreenModeFlag		= _DXG_SCREENMODE_WINDOW;
	m_bDeviceModeFlag		= _DXG_DEVICEMODE_PRIMARY;

	SetRect(&m_rcWindow, 0, 0, 0, 0);
	ZeroMemory(&m_stBitsMaskInfo, sizeof(DXG_MASKINFO));

	m_pxDXGWnd = this;

	m_bIsWindowActive = FALSE;
	m_bIsWindowReady = FALSE;
	m_bIsActiveChanged = FALSE;

	m_dwTextureTotal	= 0;
	m_dwTextureFree		= 0;
	m_dwVideoTotal		= 0;
	m_dwVideoFree		= 0;

	m_pxDefProcess = NULL;
}


VOID CWHDXGraphicWindow::UsedAndFreeMemoryCheck()
{
	DDSCAPS2     ddsCaps2; 

	ZeroMemory(&ddsCaps2, sizeof(ddsCaps2));

	ddsCaps2.dwCaps = DDSCAPS_TEXTURE;
	m_pDD->GetAvailableVidMem(&ddsCaps2, &m_dwTextureTotal, &m_dwTextureFree); 

	ZeroMemory(&ddsCaps2, sizeof(ddsCaps2));

	ddsCaps2.dwCaps = DDSCAPS_VIDEOMEMORY;
	m_pDD->GetAvailableVidMem(&ddsCaps2, &m_dwVideoTotal, &m_dwVideoFree); 
} 


/******************************************************************************************************************

	�Լ��� : CWHDXGraphicWindow::~CWHDXGraphicWindow()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	���   : 

	[����][������] : ��������

*******************************************************************************************************************/
CWHDXGraphicWindow::~CWHDXGraphicWindow()
{
	FreeDXGEnumModeResources();
    DestroyDXGObjects();

	m_pxDefProcess = NULL;
	m_pxDXGWnd = NULL;
}


/******************************************************************************************************************

	�Լ��� : CWHDXGraphicWindow::Create()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : LPTSTR lpCaption
	         CHAR *pszMenuName
	         BYTE bScreenModeFlag
	         BYTE bDeviceModeFlag
	���   : BOOL 

	[����][������] : ��������

*******************************************************************************************************************/
BOOL CWHDXGraphicWindow::Create(HINSTANCE hInst, LPTSTR lpCaption, CHAR *pszMenuName, CHAR* pszIconName, BYTE bScreenModeFlag, BYTE bDeviceModeFlag)
{
	DWORD	dwStyle;

	if ( !CWHWindow::Create(hInst, lpCaption, pszMenuName, pszIconName) )
	{
		MessageBox(m_hWnd, TEXT("[CWHDXGraphicWindow::Create]") TEXT("Window create failed."), "MirDXG", MB_ICONERROR | MB_OK);
		return FALSE;
	}

	DWORD	dwVer = GetDXVersion();

	if ( dwVer < 0x700 )
	{
		TCHAR	pszStrInfo[MAX_PATH];
		if ( dwVer == 0x000 )
		{
//			strcpy(pszStrInfo, "Direct X �� ������� �ʽ��ϴ�.\nDirect X Version 7.0�̻��� ��ġ�Ͽ��ֽʽÿ�.\n");
			strcpy(pszStrInfo, "Cannot Find Direct-X.\n Need Direct X Version 7.0 Over.\n");
		}
		else
		{
//			strcpy(pszStrInfo, "Direct X 8.0���� ���������Դϴ�.\nDirect X Version 7.0�̻��� ��ġ�Ͽ��ֽʽÿ�.\n");
			strcpy(pszStrInfo, "Direct X Version is under 8.0.\n Please Setup Direct X Version 7.0 Over.\n");
		}
		MessageBox(m_hWnd, pszStrInfo, TEXT("Mir3EI"), MB_ICONINFORMATION | MB_OK);
//		return FALSE;
	}

	m_bScreenModeFlag		= bScreenModeFlag;
	m_bDeviceModeFlag		= bDeviceModeFlag;

	if ( m_bScreenModeFlag & _DXG_SCREENMODE_WINDOW )
	{
		dwStyle  = GetWindowStyle(m_hWnd);
		dwStyle &= ~WS_POPUP;
		dwStyle |= WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX;
		SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);
//		ShowWindow(m_hWnd, SW_HIDE);
//		SetWindowLongPtr(m_hWnd, GWL_STYLE, dwStyle);
	}
	else
	{
		dwStyle  = GetWindowStyle(m_hWnd);
		dwStyle &= ~dwStyle;
		dwStyle |= WS_POPUP | WS_SYSMENU;
		SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);
		ShowWindow(m_hWnd, SW_HIDE);
//		SetWindowLongPtr(m_hWnd, GWL_STYLE, dwStyle);
	}

	HRESULT	hr;
	if ( hr = SUCCEEDED(DirectDrawEnumerateEx(DXGDriverEnumCallbackEx, NULL,
											  DDENUM_ATTACHEDSECONDARYDEVICES | DDENUM_DETACHEDSECONDARYDEVICES | DDENUM_NONDISPLAYDEVICES)) )
	{
		if ( hr = SUCCEEDED(CreateDXG()) )
		{
			m_bIsWindowReady = TRUE;
			SetDefFont();
			return TRUE;
		}
		else
		{
			MessageBox(m_hWnd, TEXT("[CWHDXGraphicWindow::Create]") TEXT("DirectGraphic create failed."), "MirDXG", MB_ICONERROR | MB_OK);
			return FALSE;
		}
	}

	return FALSE;
}


/******************************************************************************************************************

	�Լ��� : CWHDXGraphicWindow::MainWndProcDXG()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : HWND hWnd
	         UINT uMsg
	         WPARAM wParam
	         LPARAM lParam
	���   : LRESULT 

	[����][������] : ��������

*******************************************************************************************************************/
LRESULT CWHDXGraphicWindow::MainWndProcDXG(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch (uMsg)
	{
		case WM_CREATE:
		{
			RegisterHotKey( hWnd, 0, MOD_ALT, VK_F4 );
//			RegisterHotKey( hWnd, 1, MOD_ALT, VK_TAB );
			break;
		}

		case WM_HOTKEY:
		{
			switch ( wParam )
			{
			case 0:		// F4
				SendMessage(hWnd, WM_DESTROY, 0, 0);
				break;
//			case 1:		// TAB
//				break;
			}
			break;
		}

		case WM_SYSKEYDOWN:
			return OnSysKeyDown(wParam, lParam);

		case WM_MOVE:
			return OnMove(wParam, lParam);

		case WM_SIZE:
			return OnSize(wParam, lParam);

		case WM_DESTROY:
		{
			UnregisterHotKey( hWnd, 0 );
			UnregisterHotKey( hWnd, 1 );
			return OnDestroy();
		}

        case WM_SETCURSOR:
			return OnSetCursor();   

 //      case WM_GETMINMAXINFO:			
//			return OnGetMinMaxInfo(wParam, lParam);

		default:
			break;
	}

    return CWHWindow::MainWndProc(hWnd, uMsg, wParam, lParam);
}


LRESULT CWHDXGraphicWindow::OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam)
{
	if ( m_hWnd )
	{
		MINMAXINFO* pMinMax = (MINMAXINFO*) lParam;

		DWORD dwFrameWidth    = GetSystemMetrics( SM_CXSIZEFRAME );
		DWORD dwFrameHeight   = GetSystemMetrics( SM_CYSIZEFRAME );
		DWORD dwMenuHeight;
		if( GetMenu( m_hWnd ) )
			dwMenuHeight    = GetSystemMetrics( SM_CYMENU );
		else
			dwMenuHeight    = 0;					

		DWORD dwCaptionHeight = GetSystemMetrics( SM_CYCAPTION );

		pMinMax->ptMinTrackSize.x = m_stDisplayInfo.wWidth  + dwFrameWidth * 2;
		pMinMax->ptMinTrackSize.y = m_stDisplayInfo.wHeight + dwFrameHeight * 2 + 
									dwMenuHeight + dwCaptionHeight;

		pMinMax->ptMaxTrackSize.x = pMinMax->ptMinTrackSize.x;
		pMinMax->ptMaxTrackSize.y = pMinMax->ptMinTrackSize.y;
	}

    return 0L;
}


LRESULT CWHDXGraphicWindow::OnSetCursor()
{
    SetCursor(LoadCursor(NULL, IDC_ARROW));
    return 0L;
}



/******************************************************************************************************************

	�Լ��� : CWHDXGraphicWindow::OnSize()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : WPARAM wParam
	         LPARAM lParam
	���   : LRESULT 

	[����][������] : ��������

*******************************************************************************************************************/
LRESULT CWHDXGraphicWindow::OnSize(WPARAM wParam, LPARAM lParam)
{
    if ( SIZE_MAXHIDE == wParam || SIZE_MINIMIZED == wParam )
        m_bIsWindowActive = FALSE;
    else
	{
		if ( m_bIsWindowActive == FALSE )
		{
			m_bIsActiveChanged = TRUE;
		}
        m_bIsWindowActive = TRUE;
	}

	UpdateBoundsWnd();
 	return 0L;
}



/******************************************************************************************************************

	�Լ��� : CWHDXGraphicWindow::OnMove()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : WPARAM wParam
	         LPARAM lParam
	���   : LRESULT 

	[����][������] : ��������

*******************************************************************************************************************/
LRESULT CWHDXGraphicWindow::OnMove(WPARAM wParam, LPARAM lParam)
{
	UpdateBoundsWnd();
	return 0L;
}


/******************************************************************************************************************

	�Լ��� : CWHDXGraphicWindow::OnDestroy()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	���   : BOOL 

	[����][������] : ��������

*******************************************************************************************************************/
LRESULT CWHDXGraphicWindow::OnDestroy()
{
	return CWHWindow::OnDestroy();
}


/******************************************************************************************************************

	�Լ��� : CWHDXGraphicWindow::OnSysKeyDown()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : WPARAM wParam
	         LPARAM lParam
	���   : LRESULT 

	[����][������] : ��������

*******************************************************************************************************************/
LRESULT CWHDXGraphicWindow::OnSysKeyDown(WPARAM wParam, LPARAM lParam)
{
	if ( wParam == VK_RETURN )
	{
		m_bIsWindowReady = FALSE;

		if ( m_bScreenModeFlag & _DXG_SCREENMODE_WINDOW )
		{
			if ( FAILED(ResetDXG(_SCREEN_WIDTH, _SCREEN_HEIGHT, _SCREEN_BPP, _DXG_SCREENMODE_FULLSCREEN, _DXG_DEVICEMODE_PRIMARY|_DXG_DEVICEMODE_D3D)) )
			{
				MessageBox(m_hWnd, TEXT("DirectDraw RESETUP failed!!!") TEXT("The Program will now exit."), TEXT("MirDXG"), MB_ICONERROR | MB_OK);
			}
		}
		else
		{
			if ( FAILED(ResetDXG(_SCREEN_WIDTH, _SCREEN_HEIGHT, _SCREEN_BPP, _DXG_SCREENMODE_WINDOW, _DXG_DEVICEMODE_PRIMARY|_DXG_DEVICEMODE_D3D)) )
			{
				MessageBox(m_hWnd, TEXT("DirectDraw RESETUP failed!!!") TEXT("The Program will now exit."), TEXT("MirDXG"), MB_ICONERROR | MB_OK);
			}
		}

		m_bIsWindowReady = TRUE;
	}

	return 0L;
}


/******************************************************************************************************************

	�Լ��� : CWHDXGraphicWindow::FindDriverAndDevice()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	���   : DWORD 

	[����][������] : ��������

*******************************************************************************************************************/
BYTE CWHDXGraphicWindow::FindDriverAndDevice()
{
	BYTE bNum = 0;
	CHAR bCnt;
	 
	if ( m_bDeviceModeFlag & _DXG_DEVICEMODE_PRIMARY )
	{
		for ( bCnt = 0; bCnt < g_bNumDevices; bCnt++ )
		{
			if ( !g_stDXGEnumDeviceInfo[bCnt].pDriverGUID )
			{
				if ( g_stDXGEnumDeviceInfo[bCnt].f3DHardware )
					return bCnt;
				else
					bNum = bCnt;
			}
		}
	}
	else
	{
		for ( bCnt = g_bNumDevices-1; bCnt >= 0; bCnt-- )
		{
			// ���� ī�尡 2���̻�
			if( g_bNumDevices > 2 )
			{
				if ( g_stDXGEnumDeviceInfo[0].dwNumModes != g_stDXGEnumDeviceInfo[bCnt].dwNumModes )
				{
					if ( g_stDXGEnumDeviceInfo[bCnt].f3DHardware )
						return bCnt;
					else											
					{
						bNum = bCnt;
						break;
					}
				}
			}
			else
			{
				if ( g_stDXGEnumDeviceInfo[bCnt].f3DHardware )
					return bCnt;
				else
					bNum = bCnt;
			}
		}
	}

	return bNum;
}


/******************************************************************************************************************

	�Լ��� : CWHDXGraphicWindow::DestroyDXGObjects()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	���   : HRESULT 

	[����][������] : ��������

*******************************************************************************************************************/
HRESULT CWHDXGraphicWindow::DestroyDXGObjects()
{
//	HRESULT	hr;
	LONG	lDDRefCnt  = 0L;
    LONG	lD3DRefCnt = 0L;

	if ( !(m_bScreenModeFlag & _DXG_SCREENMODE_WINDOW) )
	{
		m_pDD->RestoreDisplayMode();
//		if ( FAILED(hr = m_pDD->RestoreDisplayMode()) )
//			return E_FAIL;
	}
    if ( m_pDD )
	{
		m_pDD->SetCooperativeLevel(m_hWnd, DDSCL_NORMAL);
//		if ( FAILED(hr = m_pDD->SetCooperativeLevel(m_hWnd, DDSCL_NORMAL)) )
//			return E_FAIL;
	}

    if ( m_pd3dDevice )
	{
		m_pd3dDevice->Release();
//        if ( 0 < ( lD3DRefCnt = m_pd3dDevice->Release() ) )
//			return E_FAIL;
	}
    m_pd3dDevice = NULL;

    SAFE_RELEASE(m_pddsBackBuffer);
    SAFE_RELEASE(m_pddsFrontBuffer);
    SAFE_RELEASE(m_pddsZBuffer);
//	����Ʈ������ ����� ���ؼ� Ŭ���۸� �����Ѵ�.
	SAFE_RELEASE(m_lpcClipper);
    SAFE_RELEASE(m_pD3D);

    if ( m_pDD )
    {
		lDDRefCnt = m_pDD->Release();
//        if ( 0 < ( lDDRefCnt = m_pDD->Release() ) )
//			return E_FAIL;
    }
    m_pDD = NULL;

	if ( m_hDefGameFont != NULL )
	{
		DeleteObject(m_hDefGameFont);
		m_hDefGameFont = NULL; 
//		ZeroMemory(m_pszDefFont, MAX_PATH);
	}

	return S_OK;
//    return ( lDDRefCnt==0 && lD3DRefCnt==0 ) ? S_OK : E_FAIL;
}


/******************************************************************************************************************

	�Լ��� : CWHDXGraphicWindow::FreeDXGEnumModeResources()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CWHDXGraphicWindow::FreeDXGEnumModeResources()
{	
    for ( BYTE bCnt = 0; bCnt < g_bNumDevices; bCnt++ )
    {
        SAFE_DELETE( g_stDXGEnumDeviceInfo[bCnt].pddsdModes );
    }
}


/******************************************************************************************************************

	�Լ��� : CWHDXGraphicWindow::CreateDXG()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	���   : HRESULT 

	[����][������] : ��������

*******************************************************************************************************************/
HRESULT CWHDXGraphicWindow::CreateDXG() 
{
    HRESULT hr;

	BYTE bSelecedDevice = FindDriverAndDevice();

	if ( g_stDXGEnumDeviceInfo[bSelecedDevice].f3DHardware == FALSE )
	{
		MessageBox(m_hWnd, 
//				   TEXT("3D �ϵ���� ���ӱ���� ����� �� �����ϴ�. ������ ���������� ������� ���� �� �� �ֽ��ϴ�.\n"),
				   TEXT("Cannot use 3D Hardware acceleration.\n"),
			       TEXT("Mir3EI"), MB_ICONINFORMATION | MB_OK);
	}

	if ( SUCCEEDED(hr = DirectDrawCreateEx(g_stDXGEnumDeviceInfo[bSelecedDevice].pDriverGUID, (VOID**)&m_pDD, IID_IDirectDraw7, NULL)) ) 
//	if ( SUCCEEDED(hr = DirectDrawCreateEx(NULL, (VOID**)&m_pDD, IID_IDirectDraw7, NULL)) ) 
	{
		if ( m_bScreenModeFlag & _DXG_SCREENMODE_WINDOW )
		{
			if ( FAILED(hr = m_pDD->SetCooperativeLevel(m_hWnd, DDSCL_NORMAL)) )
				return E_FAIL;
		}
		else
		{
			if ( FAILED(hr = m_pDD->SetCooperativeLevel(m_hWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN /*| DDSCL_ALLOWREBOOT*/)) )
				return E_FAIL;

			if ( FAILED(hr = m_pDD->SetDisplayMode(m_stDisplayInfo.wWidth, m_stDisplayInfo.wHeight, m_stDisplayInfo.wBPP, 0, 0)) )
				return E_FAIL;		
		}

		if ( FAILED(hr == CreatePrimarySurface()) )
		{
			MessageBox(m_hWnd, TEXT("[CWHDXGraphicWindow::CreateDXG]") TEXT("Primary surface create failed."), TEXT("MirDXG"), MB_ICONERROR | MB_OK);
			return E_FAIL;
		}

		UpdateBoundsWnd();

		if ( m_bDeviceModeFlag & _DXG_DEVICEMODE_D3D )
		{
			if ( FAILED( hr = m_pDD->QueryInterface(IID_IDirect3D7, (VOID**)&m_pD3D)) )		
				return E_FAIL;

			if ( FAILED(hr = m_pD3D->CreateDevice(*g_stDXGEnumDeviceInfo[bSelecedDevice].pDeviceGUID, m_pddsBackBuffer, &m_pd3dDevice)) )
//			if ( FAILED(hr = m_pD3D->CreateDevice(IID_IDirect3DHALDevice, m_pddsBackBuffer, &m_pd3dDevice)) )
				return E_FAIL;

			D3DVIEWPORT7 d3dVP = { 0, 0, m_stDisplayInfo.wWidth, m_stDisplayInfo.wHeight, 0.0f, 1.0f };

			if ( FAILED( hr = m_pd3dDevice->SetViewport(&d3dVP)) )							return hr;

			if ( m_bDeviceModeFlag & _DXG_DEVICEMODE_ZBUFFER )
			{
//				if ( FAILED(hr = CreateZBuffer(&IID_IDirect3DHALDevice)) )
				if ( FAILED(hr = CreateZBuffer(g_stDXGEnumDeviceInfo[bSelecedDevice].pDeviceGUID)) )
				{
					MessageBox(m_hWnd, TEXT("[CWHDXGraphicWindow::CreateDXG]") TEXT("ZBuffer create failed."), TEXT("MirDXG"), MB_ICONERROR | MB_OK);
					return E_FAIL;
				}
			}
		}

		m_stBitsMaskInfo = GetRGBMaskInfoIN16Bits(m_pddsBackBuffer);
		Init3DDeviceObjects();

		return S_OK;
	}

	return hr;
}


/******************************************************************************************************************

	�Լ��� : CDXGraphic::ResetDXG()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : WORD wWidth
	         WORD wHeight
	         WORD wBPP
	         BYTE bScreenModeFlag
	         BYTE bDeviceModeFlag
	���   : HRESULT 

	[����][������] : ��������

*******************************************************************************************************************/
HRESULT CWHDXGraphicWindow::ResetDXG(WORD wWidth, WORD wHeight, WORD wBPP, BYTE bScreenModeFlag, BYTE bDeviceModeFlag)
{
    HRESULT hr;
    DWORD	dwStyle;

//	if ( m_bDeviceModeFlag == bDeviceModeFlag && m_bScreenModeFlag == bScreenModeFlag && 
//		 m_stDisplayInfo.wWidth == wWidth && m_stDisplayInfo.wHeight == wHeight && m_stDisplayInfo.wBPP == wBPP )
//		return E_FAIL;													    

    if ( FAILED(DestroyDXGObjects()) )
	{
		MessageBox(m_hWnd, TEXT("[CWHDXGraphicWindow::ResetDXG]") TEXT("DirectGraphic reset failed."), "MirDXG", MB_ICONERROR | MB_OK);
		return E_FAIL;
	}

	m_stDisplayInfo.wWidth	= wWidth;
	m_stDisplayInfo.wHeight	= wHeight;
	m_stDisplayInfo.wBPP	= wBPP;
	m_bScreenModeFlag		= bScreenModeFlag;
	m_bDeviceModeFlag		= bDeviceModeFlag;

	if ( m_bScreenModeFlag & _DXG_SCREENMODE_WINDOW )
	{
		dwStyle  = GetWindowStyle(m_hWnd);
		dwStyle &= ~WS_POPUP;
		dwStyle |= WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX;
		SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);
	}
	else
	{
		dwStyle  = GetWindowStyle(m_hWnd);
		dwStyle &= ~dwStyle;
		dwStyle |= WS_POPUP | WS_SYSMENU;
		SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);
	}

	if ( hr = FAILED(CreateDXG()) )
	{
		MessageBox(m_hWnd, TEXT("[CWHDXGraphicWindow::ResetDXG]") TEXT("DirectGraphic create failed."), "MirDXG", MB_ICONERROR | MB_OK);
		return E_FAIL;
	}

	SetDefFont();

	return S_OK;
}


HRESULT CWHDXGraphicWindow::Clear(DWORD dwColor)
{
    DDBLTFX ddbltfx;
	HRESULT hr;

    if ( NULL == m_pddsBackBuffer )
	{
        return E_POINTER;
	}

    ZeroMemory(&ddbltfx, sizeof(ddbltfx));
    ddbltfx.dwSize      = sizeof(ddbltfx);
    ddbltfx.dwFillColor = dwColor;

	while ( TRUE )
	{
		hr = m_pddsBackBuffer->Blt(NULL, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx);

		if ( hr == DDERR_SURFACELOST )
		{
			m_pddsBackBuffer->Restore();
		}

//		if ( hr == DD_OK )
		if ( hr != DDERR_WASSTILLDRAWING )
		{
		    return S_OK;
		}
	} 
}


/******************************************************************************************************************

	�Լ��� : CWHDXGraphicWindow:: marySurface()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	���   : HRESULT 

	[����][������] : ��������

*******************************************************************************************************************/
HRESULT CWHDXGraphicWindow::CreatePrimarySurface()
{		
    DDSURFACEDESC2	ddsd;
    HRESULT			hr;

	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);

	if ( m_bScreenModeFlag & _DXG_SCREENMODE_WINDOW )
	{
		RECT				rcWork;
		RECT				rcTemp;

	    GetWindowRect(m_hWnd, &rcTemp);
		
		// Ŭ���̾�Ʈ������ ũ�⸦ ��ºκ��� �������� ������ ������ �ִ�.
		// ȭ���ػ� ��, Ŭ���̾�Ʈ �簢�� ������ ũ�⸦ ���´�.
		SetRect(&rcTemp, 0, 0, m_stDisplayInfo.wWidth, m_stDisplayInfo.wHeight);

		// Ŭ���̾�Ʈ �簢�� ����ũ�⿡�� ������ ��ü������ ũ��� ��ȯ�Ѵ�.
		AdjustWindowRectEx(&rcTemp, GetWindowStyle(m_hWnd), GetMenu(m_hWnd) != NULL, GetWindowExStyle(m_hWnd));

		// ������ ��ü����ũ��� �����츦 �����Ѵ�. �� ������ǥ�� ���õȴ�.
		SetWindowPos(m_hWnd, NULL, 0, 0, rcTemp.right-rcTemp.left, rcTemp.bottom-rcTemp.top,
					 SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);

		// HWND_NOTOPMOST�� �����ϱ� ���ؼ��̴�.
		SetWindowPos(m_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);

		// ����ȭ�鿵���� ũ�⸦ ���´�..
		SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWork, 0);
		GetWindowRect(m_hWnd, &rcTemp);
		if ( rcTemp.left < rcWork.left )	
		{
			rcTemp.left = rcWork.left;
		}
		if ( rcTemp.top  < rcWork.top )			
		{
			rcTemp.top  = rcWork.top;
		}

		// �������� ������ǥ�� �����Ѵ�.
		SetWindowPos(m_hWnd, NULL, rcTemp.left, rcTemp.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);

/*		ddsd.dwFlags        = DDSD_CAPS;
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

		if ( FAILED(hr = m_pDD->CreateSurface(&ddsd, &m_pddsFrontBuffer, NULL)) )			return E_FAIL;

		ddsd.dwFlags        = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;

		if ( m_bDeviceModeFlag & _DXG_DEVICEMODE_D3D )
			ddsd.ddsCaps.dwCaps |= DDSCAPS_3DDEVICE;

		ddsd.dwWidth    = m_stDisplayInfo.wWidth;
		ddsd.dwHeight   = m_stDisplayInfo.wHeight;

		if ( FAILED(hr = m_pDD->CreateSurface(&ddsd, &m_pddsBackBuffer, NULL)) )			return E_FAIL;
*/	
		ddsd.dwFlags           = DDSD_CAPS;
		ddsd.ddsCaps.dwCaps    = DDSCAPS_PRIMARYSURFACE;
		if ( m_bDeviceModeFlag & _DXG_DEVICEMODE_D3D )
			ddsd.ddsCaps.dwCaps |= DDSCAPS_3DDEVICE;
		if ( FAILED(hr = m_pDD->CreateSurface(&ddsd, &m_pddsFrontBuffer, NULL)) )			return E_FAIL;

		ZeroMemory(&ddsd, sizeof(ddsd));
		ddsd.dwSize = sizeof(ddsd);
		ddsd.dwFlags        = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;

		if ( m_bDeviceModeFlag & _DXG_DEVICEMODE_D3D )
			ddsd.ddsCaps.dwCaps |= DDSCAPS_3DDEVICE;

		ddsd.dwWidth    = m_stDisplayInfo.wWidth;
		ddsd.dwHeight   = m_stDisplayInfo.wHeight;

		if ( FAILED(hr = m_pDD->CreateSurface(&ddsd, &m_pddsBackBuffer, NULL)) )			return E_FAIL;
	}
	else
	{
/*		ddsd.dwFlags           = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
		ddsd.ddsCaps.dwCaps    = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
		ddsd.dwBackBufferCount = 1;
		if ( m_bDeviceModeFlag & _DXG_DEVICEMODE_D3D )
			ddsd.ddsCaps.dwCaps |= DDSCAPS_3DDEVICE;

		if ( FAILED(hr = m_pDD->CreateSurface(&ddsd, &m_pddsFrontBuffer, NULL)) )			return E_FAIL;

		DDSCAPS2 ddscaps;
		ZeroMemory(&ddscaps, sizeof(ddscaps));
		ddscaps.dwCaps = DDSCAPS_BACKBUFFER;

		if ( FAILED(hr = m_pddsFrontBuffer->GetAttachedSurface(&ddscaps, &m_pddsBackBuffer)) )
			return E_FAIL;
*/

		ddsd.dwFlags           = DDSD_CAPS;
		ddsd.ddsCaps.dwCaps    = DDSCAPS_PRIMARYSURFACE;
		if ( m_bDeviceModeFlag & _DXG_DEVICEMODE_D3D )
			ddsd.ddsCaps.dwCaps |= DDSCAPS_3DDEVICE;
		if ( FAILED(hr = m_pDD->CreateSurface(&ddsd, &m_pddsFrontBuffer, NULL)) )			return E_FAIL;

		ZeroMemory(&ddsd, sizeof(ddsd));
		ddsd.dwSize = sizeof(ddsd);
		ddsd.dwFlags        = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;

		if ( m_bDeviceModeFlag & _DXG_DEVICEMODE_D3D )
			ddsd.ddsCaps.dwCaps |= DDSCAPS_3DDEVICE;

		ddsd.dwWidth    = m_stDisplayInfo.wWidth;
		ddsd.dwHeight   = m_stDisplayInfo.wHeight;

		if ( FAILED(hr = m_pDD->CreateSurface(&ddsd, &m_pddsBackBuffer, NULL)) )			return E_FAIL;
	}
//	����Ʈ������ ����� ���ؼ� Ŭ���۸� �����Ѵ�.////////////////////////////////////////////////////////////////
	if ( FAILED(hr = m_pDD->CreateClipper(0, &m_lpcClipper, NULL)) )	
	{
		return E_FAIL;
	}
	if ( FAILED(hr = m_lpcClipper->SetHWnd(0, m_hWnd)) )
	{
		m_lpcClipper->Release();
		return E_FAIL;
	}
	if ( FAILED(hr = m_pddsFrontBuffer->SetClipper(m_lpcClipper)) )
	{
		m_lpcClipper->Release();
		return E_FAIL;
	}
//	m_pDD->FlipToGDISurface();
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	return S_OK;
}


/******************************************************************************************************************

	�Լ��� : CWHDXGraphicWindow::UpdateBoundsWnd()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CWHDXGraphicWindow::UpdateBoundsWnd()
{
	if ( m_bScreenModeFlag & _DXG_SCREENMODE_WINDOW )
	{
        GetClientRect(m_hWnd, &m_rcWindow);
        ClientToScreen(m_hWnd, (POINT*)&m_rcWindow);
        ClientToScreen(m_hWnd, (POINT*)&m_rcWindow+1);
    }
    else
    {
        SetRect(&m_rcWindow, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
    }
}


/******************************************************************************************************************

	�Լ��� : CWHDXGraphicWindow::CreateZBuffer()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : GUID* pDeviceGUID
	���   : HRESULT 

	[����][������] : ��������

*******************************************************************************************************************/
HRESULT CWHDXGraphicWindow::CreateZBuffer(const GUID* pDeviceGUID)
{
    HRESULT hr;

    D3DDEVICEDESC7 ddDesc;
    m_pd3dDevice->GetCaps(&ddDesc);
    if (ddDesc.dpcTriCaps.dwRasterCaps & D3DPRASTERCAPS_ZBUFFERLESSHSR)
        return S_OK;

    DDSURFACEDESC2 ddsd;
	ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
    ddsd.dwSize = sizeof(ddsd);
    m_pddsBackBuffer->GetSurfaceDesc(&ddsd);

    ddsd.dwFlags				= DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS | DDSD_PIXELFORMAT;
    ddsd.ddsCaps.dwCaps			= DDSCAPS_ZBUFFER;
    ddsd.ddpfPixelFormat.dwSize = 0;

    if ( FAILED(hr = m_pD3D->EnumZBufferFormats(*pDeviceGUID, DXGEnumZBufferFormatsCallback, (VOID*)&ddsd.ddpfPixelFormat)) )
	        return E_FAIL;

    if ( 0 == ddsd.ddpfPixelFormat.dwSize )
    {
        ddsd.ddpfPixelFormat.dwRGBBitCount = 16;
        if ( FAILED(hr = m_pD3D->EnumZBufferFormats(*pDeviceGUID, DXGEnumZBufferFormatsCallback,  (VOID*)&ddsd.ddpfPixelFormat)) )
	        return E_FAIL;
        if ( 0 == ddsd.ddpfPixelFormat.dwSize )
	        return E_FAIL;
    }

    if ( FAILED(hr = m_pDD->CreateSurface(&ddsd, &m_pddsZBuffer, NULL)) )		return E_FAIL;
    if ( FAILED(hr = m_pddsBackBuffer->AddAttachedSurface(m_pddsZBuffer)) )     return E_FAIL;

    if ( FAILED(hr = m_pd3dDevice->SetRenderTarget(m_pddsBackBuffer, 0L)) )
    {
        return E_FAIL;
    }

    return S_OK;
}


HRESULT CWHDXGraphicWindow::Init3DDeviceObjects()
{
    // Set the transform matrices
    D3DMATRIX matWorld, matView, matProj;

	FLOAT fHalfWidth  = (FLOAT)((FLOAT)m_stDisplayInfo.wWidth /2.0f);
	FLOAT fHalfHeight = (FLOAT)((FLOAT)m_stDisplayInfo.wHeight/2.0f);

	// ���� 800*600ȭ�鿡 �°� 3D ��ǥ�踦 �����Ѵ�.
 	D3DVECTOR vEyePt    = D3DVECTOR(0, 0, (FLOAT)-fHalfHeight);
    D3DVECTOR vLookatPt = D3DVECTOR(0, 0, 0);
    D3DVECTOR vUpVec    = D3DVECTOR(0, 1, 0);
    D3DUtil_SetIdentityMatrix(matWorld);
    D3DUtil_SetViewMatrix(matView, vEyePt, vLookatPt, vUpVec);
    D3DUtil_SetProjectionMatrix(matProj, g_PI/2, fHalfHeight/fHalfWidth, -0.1f, 1.0f);

	// MATRIAL�� �ʱ�ȭ�� �����Ѵ�.
    D3DMATERIAL7 mtrl;
	ZeroMemory(&mtrl, sizeof(mtrl));
	mtrl.diffuse.r = mtrl.diffuse.g = mtrl.diffuse.b = 0.1f;
	mtrl.ambient.r = mtrl.ambient.g = mtrl.ambient.b = 1.0f;
    m_pd3dDevice->SetMaterial(&mtrl);

	if ( !m_pd3dDevice )
	{
		return E_FAIL;
	}

    m_pd3dDevice->SetTransform(D3DTRANSFORMSTATE_WORLD,      &matWorld);
    m_pd3dDevice->SetTransform(D3DTRANSFORMSTATE_VIEW,       &matView);
    m_pd3dDevice->SetTransform(D3DTRANSFORMSTATE_PROJECTION, &matProj);

	// RenderState�� �ʱⰪ ����.
	m_pd3dDevice->SetRenderState(D3DRENDERSTATE_AMBIENT, 0xFFFFFFFF);
    m_pd3dDevice->SetRenderState(D3DRENDERSTATE_DITHERENABLE, FALSE); 
	m_pd3dDevice->SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_NONE); 	
	m_pd3dDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, D3DZB_FALSE);
	m_pd3dDevice->SetRenderState(D3DRENDERSTATE_FILLMODE, D3DFILL_SOLID);
//	m_pd3dDevice->SetRenderState(D3DRENDERSTATE_FILLMODE, D3DFILL_WIREFRAME);
//	m_pd3dDevice->SetRenderState(D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD);
	
    // TextureStageState�� �ʱⰪ ����.
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE); 
    m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP,   D3DTOP_MODULATE);

    m_pd3dDevice->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTFN_POINT); 
    m_pd3dDevice->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTFG_POINT);
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_MIPFILTER, D3DTFP_NONE);

    return S_OK;
}


/******************************************************************************************************************

	�Լ��� : CWHDXGraphicWindow::CreateGameFont()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : LPCSTR szFontName
	         INT nXsize
	         INT nYsize
	         BYTE bFontType
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
HFONT CWHDXGraphicWindow::CreateGameFont(LPCSTR szFontName, INT nHeight, INT nWidth, INT nWeight, BOOL bItalic, BOOL bULine, BOOL bStrikeOut, DWORD dwCharSet)
{
	INT nYsize;

	// ��Ʈũ�� ���߱�.
	if ( m_pddsBackBuffer )
	{
		HDC hDC;
		if ( SUCCEEDED( m_pddsBackBuffer->GetDC(&hDC) ) )
		{
			nYsize = -MulDiv(nHeight, GetDeviceCaps(hDC, LOGPIXELSY), 72); 
			m_pddsBackBuffer->ReleaseDC(hDC);
		}
	}

	if ( szFontName )
	{
		return CreateFont(nYsize, nWidth, 0, 0, nWeight, bItalic, bULine, bStrikeOut, dwCharSet, 
						  OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
						  DEFAULT_QUALITY, DEFAULT_PITCH, szFontName);
	}
	else
	{
		if ( m_pszDefFont[0] != '\0' )
		{
			return CreateFont(nYsize, nWidth, 0, 0, nWeight, bItalic, bULine, bStrikeOut, dwCharSet, 
							  OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
							  DEFAULT_QUALITY, DEFAULT_PITCH, m_pszDefFont);
		}
		else
		{
			return CreateFont(nYsize, nWidth, 0, 0, nWeight, bItalic, bULine, bStrikeOut, dwCharSet, 
							  OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
							  DEFAULT_QUALITY, DEFAULT_PITCH, "����");
		}
	}
}

VOID CWHDXGraphicWindow::SetDefFont(CHAR* pszFont, INT nFontSize)
{
	// �̹� �⺻��Ʈ�� �����Ǿ� ������ ���� ����� �ֵ��� Clear.
	if ( m_hDefGameFont != NULL )
	{
		DeleteObject(m_hDefGameFont); 
		m_hDefGameFont = NULL;
	}

	if ( pszFont == NULL )
	{
		if ( m_pszDefFont[0] != '\0' )
		{
			m_hDefGameFont	= CreateGameFont(m_pszDefFont, 9);
		}
		else
		{
			m_hDefGameFont	= CreateGameFont("����", 9);
			ZeroMemory(m_pszDefFont, MAX_PATH);
		}
	}
	else
	{
		m_hDefGameFont	= CreateGameFont(pszFont, 9);
		strcpy(m_pszDefFont, pszFont);
	}	
}



VOID CWHDXGraphicWindow::StringPlus(CHAR* szResult, CHAR* szSrc, ...)
{
	INT nCnt = 0;

	va_list vaMarker;
	CHAR*	pszString;


//	ZeroMemory(szResult, strlen(szResult));
	va_start(vaMarker, szSrc);
	pszString = szSrc;
	
	while ( TRUE )
	{		
		strcpy(&szResult[strlen(szResult)], pszString);
		if ( !strcmp(pszString,  "") )		break;
		pszString = (CHAR*)va_arg(vaMarker, CHAR*);
	}

	va_end(vaMarker);
}


BOOL CWHDXGraphicWindow::BelongStr(CHAR* pszSrc, CHAR* pszCmp)
{
	INT nCmpLen = strlen(pszCmp);
	INT nSrcLen = strlen(pszSrc);

	if ( nCmpLen > nSrcLen ) 
	{
		return FALSE;
	}

	CHAR* pszCheck = NULL;
	while ( pszCheck = strchr(pszSrc, pszCmp[0]) )
	{
		if ( !memcmp(pszCheck, pszCmp, nCmpLen) )
		{
			return TRUE;
		}
		pszSrc = pszCheck+1;
	}

	return FALSE;
}

CHAR* CWHDXGraphicWindow::IntToStr(INT nNum)
{
	static CHAR szResult[MAX_PATH];
	ZeroMemory(szResult, MAX_PATH);
	_itoa(nNum, szResult, 10);
	return szResult;
}




/******************************************************************************************************************

	�Լ��� : CWHDXGraphicWindow::PutsHan()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : LPDIRECTDRAWSURFACE7 pSurface
	         INT nX
	         INT nY
	         COLORREF foreColor
	         COLORREF backColor
	         CHAR* szFormat
	         ...
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CWHDXGraphicWindow::PutsHan(LPDIRECTDRAWSURFACE7 pSurface, INT nX, INT nY, COLORREF foreColor, COLORREF backColor, CHAR* szText, HFONT hFont)
{
	HDC		hDC;
	HFONT	hOldFont;

    if ( NULL == pSurface )
	{
		pSurface = m_pddsBackBuffer;
	}
			
    if ( NULL == pSurface )
	{
		return;
	}

	if ( NULL == hFont )
	{
		hFont = m_hDefGameFont;
	}

	HRESULT hr = pSurface->GetDC(&hDC);

	if ( FAILED( hr ) )
	{
		return;
	}

	if (backColor == RGB( 0, 0, 0 ))
		SetBkMode(hDC, TRANSPARENT);	
	else
		SetBkColor(hDC, backColor);

	INT ntet = GetLastError();

	hOldFont = (HFONT)SelectObject(hDC, hFont);

	SetTextColor(hDC, foreColor);

	nY--;	//������, ENG, USA

	TextOut(hDC, nX, nY, szText, strlen(szText));

	SelectObject(hDC, hOldFont);

	if ( hFont != m_hDefGameFont )
	{
		DeleteObject(hFont);
		hFont = NULL;
	}
	
	pSurface->ReleaseDC(hDC);
}

VOID CWHDXGraphicWindow::PutsHanA(LPDIRECTDRAWSURFACE7 pSurface, INT nX, INT nY, COLORREF foreColor, COLORREF backColor, CHAR* szText, HFONT hFont)
{
	HDC		hDC;
	HFONT	hOldFont;

    if (NULL == pSurface)
	{
		pSurface = m_pddsBackBuffer;
	}
			
    if ( NULL == pSurface )
	{
		return;
	}

	if ( NULL == hFont )
	{
		hFont = m_hDefGameFont;
	}

	HRESULT hr = pSurface->GetDC(&hDC);

	if ( FAILED( hr ) )
	{
		return;
	}

	if (backColor == RGB( 0, 0, 0 ))		SetBkMode(hDC, TRANSPARENT);	
	else									SetBkColor(hDC, backColor);

	hOldFont = (HFONT)SelectObject(hDC, hFont);

	SetTextColor(hDC, foreColor);

	TextOut(hDC, nX, nY, szText, strlen(szText));

	SelectObject(hDC, hOldFont);

	if ( hFont != m_hDefGameFont )
	{
		DeleteObject(hFont);
		hFont = NULL;
	}

	pSurface->ReleaseDC(hDC);
}

/******************************************************************************************************************

	�Լ��� : CWHDXGraphicWindow::PutsHan()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : LPDIRECTDRAWSURFACE7 pSurface
	         INT nX
	         INT nY
	         COLORREF foreColor
	         COLORREF backColor
	         CHAR* szFormat
	         ...
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
VOID CWHDXGraphicWindow::PutsHan(LPDIRECTDRAWSURFACE7 pSurface, RECT rc, COLORREF foreColor, COLORREF backColor, CHAR* szText, HFONT hFont)
{
	HDC		hDC;
	HFONT	hOldFont;

    if (NULL == pSurface)
	{
		pSurface = m_pddsBackBuffer;
	}
			
    if ( NULL == pSurface )
	{
		return;
	}

	if ( NULL == hFont )
	{
		hFont = m_hDefGameFont;
	}

	HRESULT hr = pSurface->GetDC(&hDC);

	if ( FAILED( hr ) )
	{
		return;
	}

	if (backColor == RGB( 0, 0, 0 ))		SetBkMode(hDC, TRANSPARENT);	
	else									SetBkColor(hDC, backColor);

	hOldFont = (HFONT)SelectObject(hDC, hFont);

	SetTextColor(hDC, foreColor);

	DrawText(hDC, szText, -1, &rc, DT_CENTER|DT_VCENTER|DT_SINGLELINE);

	SelectObject(hDC, hOldFont);

	if ( hFont != m_hDefGameFont )
	{
		DeleteObject(hFont);
		hFont = NULL;
	}
	
	pSurface->ReleaseDC(hDC);
}


VOID CWHDXGraphicWindow::PutsHanLeft(LPDIRECTDRAWSURFACE7 pSurface, RECT rc, COLORREF foreColor, COLORREF backColor, CHAR* szText, HFONT hFont)
{
	HDC		hDC;
	HFONT	hOldFont;

    if (NULL == pSurface)
	{
		pSurface = m_pddsBackBuffer;
	}
			
    if ( NULL == pSurface )
	{
		return;
	}

	if ( NULL == hFont )
	{
		hFont = m_hDefGameFont;
	}

	HRESULT hr = pSurface->GetDC(&hDC);

	if ( FAILED( hr ) )
	{
		return;
	}

	if (backColor == RGB( 0, 0, 0 ))		SetBkMode(hDC, TRANSPARENT);	
	else									SetBkColor(hDC, backColor);

	hOldFont = (HFONT)SelectObject(hDC, hFont);

	SetTextColor(hDC, foreColor);

	DrawText(hDC, szText, -1, &rc, DT_LEFT|DT_VCENTER|DT_SINGLELINE);

	SelectObject(hDC, hOldFont);

	if ( hFont != m_hDefGameFont )
	{
		DeleteObject(hFont);
		hFont = NULL;
	}
	
	pSurface->ReleaseDC(hDC);
}

VOID CWHDXGraphicWindow::PutsHanEx(LPDIRECTDRAWSURFACE7 pSurface, RECT rc, COLORREF foreColor, COLORREF backColor, CHAR* szText, HFONT hFont)
{
	HDC		hDC;
	HFONT	hOldFont;
	

    if (NULL == pSurface)
		pSurface = m_pddsBackBuffer;
			
    if ( NULL == pSurface )
		return;

	if ( NULL == hFont )
		hFont = m_hDefGameFont;

	HRESULT hr = pSurface->GetDC(&hDC);

	if ( FAILED( hr ) )
	{
		return;
	}

	if (backColor == RGB( 0, 0, 0 ))		SetBkMode(hDC, TRANSPARENT);	
	else									SetBkColor(hDC, backColor);

	hOldFont = (HFONT)SelectObject(hDC, hFont);

	SetTextColor(hDC, foreColor);

	// ��Ʈ�� �����ϴ� �ѿ����� ���Ѵ�.
	SIZE sizeTmp;
	GetTextExtentPoint32(hDC, szText, strlen(szText), &sizeTmp);

	// �����϶�.
	if ( sizeTmp.cx < rc.right-rc.left )
		DrawText(hDC, szText, strlen(szText), &rc, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	else
	{
		INT nHeight = DrawTextEx(hDC, szText, strlen(szText), &rc, DT_LEFT|DT_WORDBREAK|DT_CALCRECT, NULL);
		RECT rcTmp;
		rcTmp.top	 = rc.top+(rc.bottom-rc.top)/2 - nHeight/2;
		rcTmp.bottom = rcTmp.top + nHeight;
		rcTmp.left   = rc.left;
		rcTmp.right  = rc.right;
		DrawText(hDC, szText, strlen(szText), &rcTmp, DT_LEFT|DT_WORDBREAK);
	}

	SelectObject(hDC, hOldFont);

 	if ( hFont != m_hDefGameFont )
	{
		DeleteObject(hFont);
		hFont = NULL;
	}

	pSurface->ReleaseDC(hDC);
}


SIZE CWHDXGraphicWindow::GetStrLength(LPDIRECTDRAWSURFACE7 pSurface, HFONT hFont, CHAR* szFormat)
{
	HDC		hDC;
	SIZE	sSize;
	
	sSize.cx = 0;
	sSize.cy = 0;

	HFONT	hOldFont;

	if ( NULL == pSurface )
	{
		pSurface = m_pddsBackBuffer;
	}
			
    if ( NULL == pSurface )	
	{
		return sSize;
	}

	if ( NULL == hFont )
	{
		hFont = m_hDefGameFont;
	}

	HRESULT hr = pSurface->GetDC(&hDC);

	if ( FAILED( hr ) )
	{
		return sSize;
	}

	hOldFont = (HFONT)SelectObject(hDC, hFont);

	GetTextExtentPoint32(hDC,szFormat,strlen(szFormat),&sSize);

	SelectObject(hDC, hOldFont);
	
	if ( hFont != m_hDefGameFont )
	{
		DeleteObject(hFont);
		hFont = NULL;
	}

	pSurface->ReleaseDC(hDC);

	return sSize;
}


/*BOOL CWHDXGraphicWindow::StringDivideLen(INT nDivideLen, INT& nDividedLine, CHAR* szSrc,CDLList<CHAR*>* m_pxpStr)
{
	CHAR szTmpCheck[MAX_PATH];
	CHAR szResult[MAX_PATH];
	
	nDividedLine = 1;

	INT nStartLen	= 0;
	INT nEndLen		= 0;
	INT nResultLen	= 0;
	INT nWordCheck	= 0;

	if ( szSrc[0] != NULL )
	{
		ZeroMemory(szResult,MAX_PATH);

		for ( INT nCnt = 0; nCnt < (INT)strlen(szSrc); nCnt++)
		{
			ZeroMemory(szTmpCheck, MAX_PATH);
			nEndLen = nCnt+1;

			// ����κб����� ���ڿ��� �д´�.
			memcpy(&szTmpCheck, &szSrc[nStartLen], nEndLen-nStartLen);
			INT nsLen;
			nsLen = strlen(szTmpCheck);

			// ������� �о�� �κ��� �����̸� �Ѿ����.
			if (nsLen > nDivideLen )
			{
				// ���� 2����Ʈ ���ڶ��. 
				if ( szSrc[nEndLen-1] < 0 )
				{
					// ���� �տ����ڰ� 2����Ʈ ���ڰ� �ƴ϶��
					if ( !(nWordCheck%2) )
					{
						nStartLen += strlen(szTmpCheck)-1;
						nCnt--;
						CHAR* pszNewLine;
						pszNewLine = new CHAR[nResultLen+1];
						memcpy(pszNewLine,szResult,nResultLen);
						pszNewLine[nResultLen]=NULL;
						m_pxpStr->AddNode(pszNewLine);
						nResultLen = 0;
						nDividedLine++;
					}
					else
					{
						nStartLen += strlen(szTmpCheck)-2;
						nCnt -= 2;
						CHAR* pszNewLine;
						pszNewLine = new CHAR[nResultLen];
						memcpy(pszNewLine,szResult,nResultLen-1);
						pszNewLine[nResultLen-1]=NULL;
						m_pxpStr->AddNode(pszNewLine);
						nResultLen = 0;
						nDividedLine++;
						nWordCheck--;
					}
				}
				// 1����Ʈ ����. 
				// ���纸�� �ѹ���Ʈ�պκб����� ������ָ� �ȴ�.
				else
				{
					nStartLen += strlen(szTmpCheck)-1;
					nCnt--;
					CHAR* pszNewLine;
					pszNewLine = new CHAR[nResultLen+1];
					memcpy(pszNewLine,szResult,nResultLen);
					pszNewLine[nResultLen]=NULL;
					m_pxpStr->AddNode(pszNewLine);
					nResultLen=0;
					nDividedLine++;
				}
			}
			else if(szSrc[nEndLen-1]=='\n')	// ��������     \n�����ϸ�  Error ????
			{
				nStartLen += strlen(szTmpCheck)-1;
				CHAR* pszNewLine;
				pszNewLine = new CHAR[nResultLen+1];
				memcpy(pszNewLine,szResult,nResultLen);
				pszNewLine[nResultLen]=NULL;
				m_pxpStr->AddNode(pszNewLine);
				nResultLen=0;
				nDividedLine++;
			}
			else
			{
				if ( szSrc[nEndLen-1] < 0 )
					nWordCheck++;

				szResult[nResultLen] = szSrc[nEndLen-1];
				nResultLen++;
			}
		}
		if(nResultLen!=0)
		{
			CHAR* pszNewLine;
			pszNewLine = new CHAR[nResultLen+1];
			memcpy(pszNewLine,szResult,nResultLen);
			pszNewLine[nResultLen]=NULL;
			m_pxpStr->AddNode(pszNewLine);
			nDividedLine++;
			nResultLen=0;
		}
		return TRUE;
	}
	return FALSE;
}
*/


BOOL CWHDXGraphicWindow::StringDivide(INT nDivideWidth, INT& nDividedLine, CHAR* szSrc, CHAR* szResult, HFONT hFont)
{
	CHAR szTmpCheck[MAX_PATH];
	
	INT nStartLen, nEndLen, nResultLen, nWordCheck;

	nStartLen = nEndLen = nResultLen = nWordCheck = 0;
	nDividedLine = 1;


	HDC		hDC;
	HFONT	hOldFont;
	
	if ( NULL == hFont || m_pddsBackBuffer == NULL )
	{
		hFont = m_hDefGameFont;
	}

	m_pddsBackBuffer->GetDC(&hDC);
//	if ( FAILED( m_pddsBackBuffer->GetDC(&hDC) ) )
//	{
//		return FALSE;
//	}

	hOldFont = (HFONT)SelectObject(hDC, hFont);	

	if ( szSrc[0] != '\0' )
	{
		for ( INT nCnt = 0; nCnt < (INT)strlen(szSrc); nCnt++)
		{
			ZeroMemory(szTmpCheck, MAX_PATH);

			nEndLen = nCnt+1;

/*			// ���࿡ ����ũ�Ⱑ �ִ� ����ũ�⸦ �Ѿ�� �ִ�ġ�� �����ش�.
			if ( nEndLen >= MAX_PATH )
			{
				szResult[MAX_PATH-1] = NULL;
				break;
			}
*/
			// ����κб����� ���ڿ��� �д´�.
			memcpy(&szTmpCheck, &szSrc[nStartLen], nEndLen-nStartLen);

			SIZE sizeLen = {0, 0};

			GetTextExtentPoint32(hDC, szTmpCheck, strlen(szTmpCheck), &sizeLen);

			// ������� �о�� �κ��� �����̸� �Ѿ����.
			if ( sizeLen.cx > nDivideWidth )
			{
				// ���� 2����Ʈ ���ڶ��. 
				if ( szSrc[nEndLen-1] < 0 )
				{
					// ���� �տ����ڰ� 2����Ʈ ���ڰ� �ƴ϶��
					if ( !(nWordCheck%2) )
					{
						nStartLen += strlen(szTmpCheck)-1;
						nCnt--;
						szResult[nResultLen] = '`';
						nResultLen++;
						nDividedLine++;
					}
					else
					{
						nStartLen += strlen(szTmpCheck)-2;
						nCnt -= 2;
						szResult[nResultLen-1] = '`';
						nDividedLine++;
						nWordCheck--;
					}
				}
				// 1����Ʈ ����. 
				// ���纸�� �ѹ���Ʈ�պκб����� ������ָ� �ȴ�.
				else
				{
					nStartLen += strlen(szTmpCheck)-1;
					nCnt--;
					szResult[nResultLen] = '`';
					nResultLen++;
					nDividedLine++;
				}
			}
			else
			{
				if ( szSrc[nEndLen-1] < 0 )
				{
					nWordCheck++;


					szResult[nResultLen] = szSrc[nEndLen-1];
					nResultLen++;

					nWordCheck++;

					nCnt++;
					nEndLen = nCnt+1;
					szResult[nResultLen] = szSrc[nEndLen-1];
					nResultLen++;
				}
				else
				{
					szResult[nResultLen] = szSrc[nEndLen-1];
					nResultLen++;
				}
			}
		}
	}

	if ( szSrc[0] == '\0' )
	{
		*szResult = '\0';
	}

	SelectObject(hDC, hOldFont);
	
	if ( hFont != m_hDefGameFont )
	{
		DeleteObject(hFont);
		hFont = NULL;
	}

	m_pddsBackBuffer->ReleaseDC(hDC);

	return TRUE;

}


/******************************************************************************************************************

	�Լ��� : CWHDXGraphicWindow::GetRGBMaskInfoIN16Bits()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : LPDIRECTDRAWSURFACE7 pSurface
	���   : DXG_MASKINFO 

	[����][������] : ��������

*******************************************************************************************************************/
DXG_MASKINFO CWHDXGraphicWindow::GetRGBMaskInfoIN16Bits(LPDIRECTDRAWSURFACE7 pSurface)
{	
	DDPIXELFORMAT ddpf;
	DXG_MASKINFO stRGBMaskInfo;

	ZeroMemory(&stRGBMaskInfo, sizeof(DXG_MASKINFO));

	if ( pSurface == NULL )		pSurface = m_pddsBackBuffer;

    if ( pSurface )
	{
		memset(&ddpf, 0, sizeof(ddpf));
		ddpf.dwSize = sizeof(ddpf);
		ddpf.dwFlags = DDPF_RGB;
		pSurface->GetPixelFormat(&ddpf);

		stRGBMaskInfo.dwRMask = ddpf.dwRBitMask;
		stRGBMaskInfo.dwGMask = ddpf.dwGBitMask;
		stRGBMaskInfo.dwBMask = ddpf.dwBBitMask;

		DWORD dwCnt;
		DWORD dwMask;
		for ( dwCnt = 0, dwMask = ddpf.dwRBitMask; !( dwMask & 1 ); dwCnt++, dwMask >>= 1 );
		stRGBMaskInfo.bRShift	= (BYTE) dwCnt;
		for ( dwCnt = 0; ( ( dwMask>>dwCnt ) & 1 ); dwCnt++ );
		stRGBMaskInfo.bRCnt		= (BYTE) dwCnt;

		for ( dwCnt = 0, dwMask = ddpf.dwGBitMask; !( dwMask & 1 ); dwCnt++, dwMask >>= 1 );
		stRGBMaskInfo.bGShift	= (BYTE) dwCnt;
		for ( dwCnt = 0; ( ( dwMask>>dwCnt ) & 1 ); dwCnt++ );
		stRGBMaskInfo.bGCnt		= (BYTE) dwCnt;

		for ( dwCnt = 0, dwMask = ddpf.dwBBitMask; !( dwMask & 1 ); dwCnt++, dwMask >>= 1 );
		stRGBMaskInfo.bBShift	= (BYTE) dwCnt;
		for ( dwCnt = 0; ( ( dwMask>>dwCnt ) & 1 ); dwCnt++ );
		stRGBMaskInfo.bBCnt		= (BYTE) dwCnt;
	}

	return stRGBMaskInfo;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �׸��� �Լ��� ����.

WORD CWHDXGraphicWindow::ConvertColor24To16(COLORREF dwColor)
{
	WORD wRet;

	INT nRed  = RGB_GETRED(dwColor);
	INT nGreen = RGB_GETGREEN(dwColor);
	INT nBlue   = RGB_GETBLUE(dwColor);
	
	nRed = (nRed*(1<<m_stBitsMaskInfo.bRCnt))/(1<<8);
	nGreen = (nGreen*(1<<m_stBitsMaskInfo.bGCnt))/(1<<8);
	nBlue = (nBlue*(1<<m_stBitsMaskInfo.bBCnt))/(1<<8);

	wRet = (nRed << m_stBitsMaskInfo.bRShift) | (nGreen << m_stBitsMaskInfo.bGShift) | (nBlue << m_stBitsMaskInfo.bBShift); 
	return wRet;
}


/******************************************************************************************************************

	�Լ��� : CWHDXGraphicWindow::DrawWithGDI()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : RECT rc
	         LPDIRECTDRAWSURFACE7 pSurface
	         DWORD dwColor
	         DWORD dwPenStyleFlg
	         BYTE bKind
	���   : HRESULT 

	[����][������] : ��������

*******************************************************************************************************************/
HRESULT CWHDXGraphicWindow::DrawWithGDI(RECT* prc, LPDIRECTDRAWSURFACE7 pSurface, DWORD dwColor, BYTE bKind)
{
	POINT	pt;
	HDC		hDC;
	HPEN	hPen, hOldPen;
	HBRUSH	hBrush, hOldBrush;
	HRESULT hr;

	if ( pSurface == NULL )
	{
		pSurface = m_pddsBackBuffer;
	}

	if ( pSurface == NULL )
	{
		return E_FAIL;
	}

	if ( FAILED(hr = pSurface->GetDC(&hDC)) )
	{
		return E_FAIL;
	}

	switch ( bKind )
	{
	case 0:
		{
			hPen = CreatePen(PS_SOLID, NULL, dwColor);
		
			hOldPen = (HPEN)SelectObject(hDC, hPen);

			MoveToEx(hDC, prc->left, prc->top, &pt);
			LineTo(hDC, prc->right, prc->bottom);

			SelectObject(hDC, hOldPen);
			DeleteObject(hPen);
			hPen = NULL;
		}
		break;
	case 1:
		{
			hBrush = CreateSolidBrush(dwColor);

			hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

			FrameRect(hDC, prc, hBrush);

			SelectObject(hDC, hOldBrush);
			DeleteObject(hBrush);
			hBrush = NULL;
		}
		break;
	case 2:
		{
			hBrush = CreateSolidBrush(dwColor);

			hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

			FillRect(hDC, prc, hBrush);

			SelectObject(hDC, hOldBrush);
			DeleteObject(hBrush);
			hBrush = NULL;
		}
		break;
	case 3:
		{
			hBrush = CreateSolidBrush(dwColor);

			hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

			Ellipse(hDC, prc->left, prc->top, prc->right, prc->bottom);

			SelectObject(hDC, hOldBrush);
			DeleteObject(hBrush);
			hBrush = NULL;
		}
		break;
	case 4:
		{
			hPen = CreatePen(PS_SOLID, NULL, dwColor);
		
			hOldPen = (HPEN)SelectObject(hDC, hPen);

			Ellipse(hDC, prc->left, prc->top, prc->right, prc->bottom);

			SelectObject(hDC, hOldPen);
			DeleteObject(hPen);
			hPen = NULL;
		}
		break;
	default:
		break;
	}

	pSurface->ReleaseDC(hDC);

	return S_OK;
}


/******************************************************************************************************************

	�Լ��� : CWHDXGraphicWindow::DrawSprite()

	�ۼ��� : 
	�ۼ��� : 

	����   : �Ϲ����� �׸���. ���ȼ��� �׸���. ��ũ������ Ŭ����, �ҽ����� Ŭ����
	�Է�   : INT nX
	         INT nY
	         INT nXSize
	         INT nYSize
	         WORD* pwSrc
	���   : VOID 

	[����][������] : ��������

*******************************************************************************************************************/
BOOL CWHDXGraphicWindow::DrawWithImage(INT nX, INT nY, INT nXSize, INT nYSize, WORD* pwSrc)
{
	RECT			rc;
	DDSURFACEDESC2	ddsd;

	INT	nWidth		= nXSize;
	INT	nHeight		= nYSize;
	INT	nXOffset	= 0;
	INT	nYOffset	= 0;
	INT	nStartX		= 0;
	INT	nStartY		= 0;
	INT	nEndX		= m_stDisplayInfo.wWidth -1;
	INT	nEndY		= m_stDisplayInfo.wHeight-1;

	if ( m_pddsBackBuffer != NULL )
	{
		if (nX < nStartX )
		{ 
			nXOffset = nStartX - nX;
			nWidth	 = nXSize - nXOffset;
		}
		if ( (nX+nXSize-1) > nEndX )
			nWidth	 = nEndX - nX - nXOffset + 1;		
		if ( nY < nStartY )
		{ 
			nYOffset	= nStartY - nY;
			nHeight		= nYSize - nYOffset;
		}
		if ( (nY+nYSize-1) > nEndY )
			nHeight	= nEndY - nY - nYOffset + 1;

		if ( (nWidth > 0) && (nHeight > 0) )
		{
			rc.left		= nXOffset;
			rc.right	= nXOffset + nWidth;
			rc.top		= nYOffset;
			rc.bottom	= nYOffset + nHeight;
 
			LONG	lWidth;
			ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
			ddsd.dwSize = sizeof(DDSURFACEDESC2);
			if ( FAILED(m_pddsBackBuffer->Lock(NULL, &ddsd, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL)) )
			{
				return FALSE;
			}

			WORD* pwdDst = (WORD*)ddsd.lpSurface;
			lWidth		 = ddsd.lPitch >> 1;

			for ( INT y=rc.top ; y < rc.bottom ; y++ )
			{
				for ( INT x=rc.left ; x < rc.right ; x++ )
				{
					if ( pwSrc[y * nXSize + x] != 0 )
					{
						pwdDst[((y+nY) * lWidth) + (nX+x)] = pwSrc[y * nXSize + x];
					}
				}
			}

			m_pddsBackBuffer->Unlock(NULL);
		}
		return TRUE;
	}
	return FALSE;
}


BOOL CWHDXGraphicWindow::DrawWithImagePerLineClipRgn(INT nX, INT nY, INT nXSize, INT nYSize, WORD* pwSrc, WORD wClipWidth, WORD wClipHeight)
{
	RECT			rc;
	DDSURFACEDESC2	ddsd;

	INT	nWidth		= nXSize;
	INT	nHeight		= nYSize;
	INT	nXOffset	= 0;
	INT	nYOffset	= 0;
	INT	nStartX		= 0;
	INT	nStartY		= 0;
	INT	nEndX		= wClipWidth  - 1;
	INT	nEndY		= wClipHeight - 1;

	if ( m_pddsBackBuffer != NULL )
	{
		if (nX < nStartX )
		{ 
			nXOffset = nStartX - nX;
			nWidth	 = nXSize - nXOffset;
		}
		if ( (nX+nXSize-1) > nEndX )
			nWidth	 = nEndX - nX - nXOffset + 1;		
		if ( nY < nStartY )
		{ 
			nYOffset	= nStartY - nY;
			nHeight		= nYSize - nYOffset;
		}
		if ( (nY+nYSize-1) > nEndY )
			nHeight	= nEndY - nY - nYOffset + 1;

		if ( (nWidth > 0) && (nHeight > 0) )
		{
			rc.left		= nXOffset;
			rc.right	= nXOffset + nWidth;
			rc.top		= nYOffset;
			rc.bottom	= nYOffset + nHeight;

			LONG	lWidth;
			ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
			ddsd.dwSize = sizeof(DDSURFACEDESC2);
			if ( FAILED(m_pddsBackBuffer->Lock(NULL, &ddsd, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL)) )
			{
				return FALSE;
			}

			WORD* pwdDst = (WORD*)ddsd.lpSurface;
			lWidth		 = ddsd.lPitch >> 1;

			for ( INT y=rc.top ; y < rc.bottom ; y++ )
			{
				memcpy(&pwdDst[((y+nY) * lWidth) + (nX + rc.left)], &pwSrc[y * nXSize + rc.left], (rc.right-rc.left)*2);
			}

			m_pddsBackBuffer->Unlock(NULL);
		}
		return TRUE;
	}
	return FALSE;
}



/******************************************************************************************************************

	�Լ��� : CWHDXGraphicWindow::DrawWithSurface()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : LPDIRECTDRAWSURFACE7 pddsSrc
	         RECT* prcSrc
	         RECT* prcDst
	���   : BOOL 

	[����][������] : ��������

*******************************************************************************************************************/
BOOL CWHDXGraphicWindow::DrawWithSurface(INT nX, INT nY, INT nXSize, INT nYSize, LPDIRECTDRAWSURFACE7 pddsSrc)
{
	RECT	rc;
	RECT	rcDst;
	INT		nXOffset	= 0;
	INT		nYOffset	= 0;
	INT		nWidth		= nXSize;
	INT		nHeight		= nYSize;
	INT		nStartX		= 0;
	INT		nStartY		= 0;

	INT		nEndX		= m_stDisplayInfo.wWidth -1;
	INT		nEndY		= m_stDisplayInfo.wHeight-1;;


	if ( m_pddsBackBuffer != NULL )
	{
		if (nX < nStartX )
		{ 
			nXOffset	= nStartX - nX;
			nWidth		= nXSize - nXOffset;
		}
		if ( (nX+nXSize-1) > nEndX )
			nWidth		= nEndX - nX - nXOffset + 1;		
		if ( nY < nStartY )
		{ 
			nYOffset	= nStartY - nY;
			nHeight		= nYSize - nYOffset;
		}		
		if ( (nY+nYSize-1) > nEndY )
			nHeight	= nEndY - nY - nYOffset + 1;

		if ( (nWidth > 0) && (nHeight > 0) )
		{
			rc.left		 = nXOffset;
			rc.right	 = nXOffset+nWidth;
			rc.top		 = nYOffset;
			rc.bottom	 = nYOffset+nHeight;

			rcDst.left	 = rc.left+nX;
			rcDst.top	 = rc.top+nY;
			rcDst.right  = rc.right+nX;
			rcDst.bottom = rc.bottom+nY;

			m_pddsBackBuffer->Blt(&rcDst, pddsSrc, &rc, DDBLT_WAIT|DDBLT_KEYSRC, NULL);
		}
		return TRUE;
	}
	return FALSE;
}


BOOL CWHDXGraphicWindow::DrawWithImageForCompMemToMem(INT nX, INT nY, INT nXSize, INT nYSize, WORD* pwSrc, INT nDstXSize, INT nDstYSize, WORD* pwDst, WORD wChooseColor1, WORD wChooseColor2)
{
	RECT			rc;

	INT	nWidth		= nXSize;
	INT	nHeight		= nYSize;
	INT	nXOffset	= 0;
	INT	nYOffset	= 0;
	INT	nStartX		= 0;
	INT	nStartY		= 0;
	INT	nEndX		= nDstXSize - 1;
	INT	nEndY		= nDstYSize - 1;

	if ( pwDst != NULL )
	{
		if (nX < nStartX )
		{ 
			nXOffset	= nStartX - nX;
			nWidth		= nXSize - nXOffset;
		}
		if ( (nX+nXSize-1) > nEndX )
			nWidth		= nEndX - nX - nXOffset + 1;		
		if ( nY < nStartY )		{ 
			nYOffset	= nStartY - nY;
			nHeight		= nYSize - nYOffset;
		}		
		if ( (nY+nYSize-1) > nEndY )
			nHeight	= nEndY - nY - nYOffset + 1;

		if ( (nWidth > 0) && (nHeight > 0) )
		{
			rc.left		= nXOffset;
			rc.right	= nXOffset+nWidth;
			rc.top		= nYOffset;
			rc.bottom	= nYOffset+nHeight;

			INT nWidthStart	= 0;
			INT nWidthEnd	= 0;
			INT nCurrWidth  = 0;
			INT nCntCopyWord = 0;
			INT nYCnt =0;
			INT nLastWidth = 0;

			FLOAT rBlueRate, rGreenRate, bRedRate;
			BYTE  bRedSrc, bGreenSrc, bBlueSrc;
			BYTE  bRedWantedColor, bGreenWantedColor, bBlueWantedColor;
			WORD  wPixel;

			// y�� Ŭ����.
			for ( nYCnt=0 ; nYCnt < rc.top ; nYCnt++ )
			{
				nWidthEnd += pwSrc[nWidthStart];
				nWidthStart++;
				nWidthEnd++;
				nWidthStart	= nWidthEnd;
			}

			// y�࿡ ���ؼ� ������ ���ν�ų Count���� ���Ѵ�.
			for ( nYCnt=rc.top ; nYCnt < rc.bottom ; nYCnt++ )
			{
				// �Ѷ����� ���̸� ���´�.(������ ����)
				nWidthEnd += pwSrc[nWidthStart];
				nWidthStart++;

				// ������ ���̸�ŭ ȭ�鿡 �ѷ��ش�.
				for ( INT x = nWidthStart; x < nWidthEnd ; )
				{
					if ( pwSrc[x] == 0xC0 )
					{
						x++;
						nCntCopyWord = pwSrc[x];
						x++;
						nCurrWidth += nCntCopyWord;
					}
					else if ( pwSrc[x] == 0xC1 )
					{
						x++;
						nCntCopyWord = pwSrc[x];
						x++;

						nLastWidth = nCurrWidth;
						nCurrWidth += nCntCopyWord;

						if ( rc.left > nCurrWidth || rc.right < nLastWidth )
						{
							x += nCntCopyWord;
						}
						else
						{
							// rc.left���� �������� ī���� ������ �ɸ� ���.
							if ( nLastWidth < rc.left && rc.left <= nCurrWidth )
							{
								if ( ((nYCnt+nY) * nDstXSize) + (rc.left+nX) < 0 )
									return FALSE;

								x += (rc.left-nLastWidth);
								memcpy(&pwDst[((nYCnt+nY) * nDstXSize) + (rc.left+nX)], &pwSrc[x], sizeof(WORD)*(nCurrWidth-rc.left));
								x += (nCurrWidth-rc.left);
							}
							// rc.right���� �������� ī���� ������ �ɸ� ���.
							else if ( nLastWidth <= rc.right && rc.right < nCurrWidth )
							{
								memcpy(&pwDst[((nYCnt+nY) * nDstXSize) + (nLastWidth+nX)], &pwSrc[x], sizeof(WORD)*(rc.right-nLastWidth));
								x += nCntCopyWord;
							}
							else
							{
								memcpy(&pwDst[((nYCnt+nY) * nDstXSize) + (nLastWidth+nX)], &pwSrc[x], sizeof(WORD)*nCntCopyWord);
								x += nCntCopyWord;
							}
						}
					}
					else if ( pwSrc[x] == 0xC2 || pwSrc[x] == 0xC3 )
					{
						WORD wDyingKind, wChooseColor;
						wDyingKind = pwSrc[x];
						switch ( wDyingKind )
						{
						case 0xC2: 
							wChooseColor = wChooseColor1;
							break;
						case 0xC3: 
							wChooseColor = wChooseColor2;
							break;
						}
						x++;
						nCntCopyWord = pwSrc[x];
						x++;

						nLastWidth = nCurrWidth;
						nCurrWidth += nCntCopyWord;

						if ( rc.left > nCurrWidth || rc.right < nLastWidth )
						{
							x += nCntCopyWord;
						}
						else
						{
							// rc.left���� �������� ī���� ������ �ɸ� ���.
							if ( nLastWidth < rc.left && rc.left <= nCurrWidth )
							{
								x += (rc.left-nLastWidth);
								for ( INT nCheck = 0; nCheck < nCurrWidth-rc.left; nCheck++ )
								{
									wPixel	  = wChooseColor;
									bBlueWantedColor  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenWantedColor = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedWantedColor   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									wPixel	  = pwSrc[x+nCheck];
									bBlueSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenSrc = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
									rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
									bRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

									bBlueWantedColor = (BYTE)(((FLOAT)bBlueWantedColor*rBlueRate));
									bGreenWantedColor = (BYTE)(((FLOAT)bGreenWantedColor*rGreenRate));
									bRedWantedColor = (BYTE)(((FLOAT)bRedWantedColor*bRedRate));

									if ( bBlueWantedColor > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
										bBlueWantedColor = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
									if ( bGreenWantedColor > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
										bGreenWantedColor = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
									if ( bRedWantedColor > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
										bRedWantedColor = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);

									if ( ((nYCnt+nY) * nDstXSize) + (nLastWidth+nX+nCheck) < 0 )
										return FALSE;

									pwDst[((nYCnt+nY) * nDstXSize) + (nLastWidth+nX+nCheck)] = ((bRedWantedColor  <<m_stBitsMaskInfo.bRShift) |
																							    (bGreenWantedColor<<m_stBitsMaskInfo.bGShift) |
																								(bBlueWantedColor <<m_stBitsMaskInfo.bBShift));			
								}
								x += (nCurrWidth-rc.left);
							}
							// rc.right���� �������� ī���� ������ �ɸ� ���.
							else if ( nLastWidth <= rc.right && rc.right < nCurrWidth )
							{
								for ( INT nCheck = 0; nCheck < rc.right-nLastWidth; nCheck++ )
								{
									wPixel	  = wChooseColor;
									bBlueWantedColor  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenWantedColor = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedWantedColor   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									wPixel	  = pwSrc[x+nCheck];
									bBlueSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenSrc = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
									rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
									bRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

									bBlueWantedColor = (BYTE)(((FLOAT)bBlueWantedColor*rBlueRate));
									bGreenWantedColor = (BYTE)(((FLOAT)bGreenWantedColor*rGreenRate));
									bRedWantedColor = (BYTE)(((FLOAT)bRedWantedColor*bRedRate));

									if ( bBlueWantedColor > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
										bBlueWantedColor = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
									if ( bGreenWantedColor > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
										bGreenWantedColor = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
									if ( bRedWantedColor > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
										bRedWantedColor = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);

									pwDst[((nYCnt+nY) * nDstXSize) + (nLastWidth+nX+nCheck)] = ((bRedWantedColor  <<m_stBitsMaskInfo.bRShift) |
																								(bGreenWantedColor<<m_stBitsMaskInfo.bGShift) |
																								(bBlueWantedColor <<m_stBitsMaskInfo.bBShift));			
								}
								x += nCntCopyWord;
							}
							else
							{
								for ( INT nCheck = 0; nCheck < nCntCopyWord; nCheck++ )
								{
									wPixel	  = wChooseColor;
									bBlueWantedColor  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenWantedColor = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedWantedColor   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									wPixel	  = pwSrc[x+nCheck];
									bBlueSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenSrc = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
									rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
									bRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

									bBlueWantedColor = (BYTE)(((FLOAT)bBlueWantedColor*rBlueRate));
									bGreenWantedColor = (BYTE)(((FLOAT)bGreenWantedColor*rGreenRate));
									bRedWantedColor = (BYTE)(((FLOAT)bRedWantedColor*bRedRate));

									if ( bBlueWantedColor > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
										bBlueWantedColor = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
									if ( bGreenWantedColor > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
										bGreenWantedColor = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
									if ( bRedWantedColor > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
										bRedWantedColor = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);

									pwDst[((nYCnt+nY) * nDstXSize) + (nLastWidth+nX+nCheck)] = ((bRedWantedColor  <<m_stBitsMaskInfo.bRShift) |
																								(bGreenWantedColor<<m_stBitsMaskInfo.bGShift) |
																								(bBlueWantedColor <<m_stBitsMaskInfo.bBShift));			
								}
								x += nCntCopyWord;
							}
						}
					}	
					else
					{
						return FALSE;
					}
				}
				// ������ ���� ���� ������ �������� �Ű��ش�.
				nWidthEnd++;

				nWidthStart	= nWidthEnd;
				nCurrWidth = 0;
			}
		}

		return TRUE;
	}
	return FALSE;
}


BOOL CWHDXGraphicWindow::DrawWithImageForComp(INT nX, INT nY, RECT* prcSrc, WORD* pwSrc, WORD wChooseColor1, WORD wChooseColor2, LPDIRECTDRAWSURFACE7 pddsDst)
{
	RECT			rc;
	DDSURFACEDESC2	ddsd;
	LPDIRECTDRAWSURFACE7 ddsDst;

	if ( !prcSrc || !pwSrc )
	{
		return FALSE;
	}

	if ( pddsDst )
	{
		ddsDst = pddsDst;
	}
	else
	{
		ddsDst = m_pddsBackBuffer;
	}

	INT	nWidth		= prcSrc->right-prcSrc->left;
	INT	nHeight		= prcSrc->bottom-prcSrc->top;
	INT	nXOffset	= prcSrc->left;
	INT	nYOffset	= prcSrc->top;
	INT	nStartX		= 0;
	INT	nStartY		= 0;
	INT	nEndX		= m_stDisplayInfo.wWidth -1;
	INT	nEndY		= m_stDisplayInfo.wHeight-1;

	if ( ddsDst != NULL )
	{
		if (nX < nStartX )
		{ 
			if ( nXOffset < -nX )
			{
				nXOffset = -nX;
			}
			nWidth	 = prcSrc->right - nXOffset;
		}
		if ( (nX+prcSrc->right-prcSrc->left-1) > nEndX )
		{
			nWidth	= nEndX - nX - nXOffset + 1;		
		}
		if ( nY < nStartY )	
		{ 
			if ( nYOffset < -nY )
			{
				nYOffset = -nY;
			}
			nHeight	 = prcSrc->bottom - nYOffset;
		}		
		if ( (nY+prcSrc->bottom-prcSrc->top-1) > nEndY )
		{
			nHeight	= nEndY - nY - nYOffset + 1;
		}

		if ( (nWidth > 0) && (nHeight > 0) )
		{
			rc.left		= nXOffset;
			rc.right	= nXOffset+nWidth;
			rc.top		= nYOffset;
			rc.bottom	= nYOffset+nHeight;

			LONG	lWidth;
			ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
			ddsd.dwSize = sizeof(DDSURFACEDESC2);
			if ( FAILED(ddsDst->Lock(NULL, &ddsd, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL)) )
			{
				return FALSE;
			}

			WORD* pwdDst = (WORD*)ddsd.lpSurface;
			lWidth		 = ddsd.lPitch >> 1;

			INT nWidthStart	= 0;
			INT nWidthEnd	= 0;
			INT nCurrWidth  = 0;
			INT nCntCopyWord = 0;
			INT nYCnt =0;
			INT nLastWidth = 0;

			FLOAT rBlueRate, rGreenRate, bRedRate;
			BYTE  bRedSrc, bGreenSrc, bBlueSrc;
			BYTE  bRedWantedColor, bGreenWantedColor, bBlueWantedColor;
			WORD  wPixel;

			// y�� Ŭ����.
			for ( nYCnt=0 ; nYCnt < rc.top ; nYCnt++ )
			{
				nWidthEnd += pwSrc[nWidthStart];
				nWidthStart++;
				nWidthEnd++;
				nWidthStart	= nWidthEnd;
			}

			// y�࿡ ���ؼ� ������ ���ν�ų Count���� ���Ѵ�.
			for ( nYCnt=rc.top ; nYCnt < rc.bottom ; nYCnt++ )
			{
				// �Ѷ����� ���̸� ���´�.(������ ����)
				nWidthEnd += pwSrc[nWidthStart];
				nWidthStart++;

				// ������ ���̸�ŭ ȭ�鿡 �ѷ��ش�.
				for ( INT x = nWidthStart; x < nWidthEnd ; )
				{
					if ( pwSrc[x] == 0xC0 )
					{
						x++;
						nCntCopyWord = pwSrc[x];
						x++;
						nCurrWidth += nCntCopyWord;
					}
					else if ( pwSrc[x] == 0xC1 )
					{
						x++;
						nCntCopyWord = pwSrc[x];
						x++;

						nLastWidth = nCurrWidth;
						nCurrWidth += nCntCopyWord;

						if ( rc.left > nCurrWidth || rc.right < nLastWidth )
						{
							x += nCntCopyWord;
						}
						else
						{
							// rc.left���� �������� ī���� ������ �ɸ� ���.
							if ( nLastWidth < rc.left && rc.left <= nCurrWidth )
							{
								if ( ((nYCnt+nY) * lWidth) + (rc.left+nX) < 0 )
									return FALSE;

								x += (rc.left-nLastWidth);
								memcpy(&pwdDst[((nYCnt+nY) * lWidth) + (rc.left+nX)], &pwSrc[x], sizeof(WORD)*(nCurrWidth-rc.left));
								x += (nCurrWidth-rc.left);
							}
							// rc.right���� �������� ī���� ������ �ɸ� ���.
							else if ( nLastWidth <= rc.right && rc.right < nCurrWidth )
							{
								memcpy(&pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX)], &pwSrc[x], sizeof(WORD)*(rc.right-nLastWidth));
								x += nCntCopyWord;
							}
							else
							{
								memcpy(&pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX)], &pwSrc[x], sizeof(WORD)*nCntCopyWord);
								x += nCntCopyWord;
							}
						}
					}
					else if ( pwSrc[x] == 0xC2 || pwSrc[x] == 0xC3 )
					{
						WORD wDyingKind, wChooseColor;
						wDyingKind = pwSrc[x];
						switch ( wDyingKind )
						{
						case 0xC2: 
							wChooseColor = wChooseColor1;
							break;
						case 0xC3: 
							wChooseColor = wChooseColor2;
							break;
						}
						x++;
						nCntCopyWord = pwSrc[x];
						x++;

						nLastWidth = nCurrWidth;
						nCurrWidth += nCntCopyWord;

						if ( rc.left > nCurrWidth || rc.right < nLastWidth )
						{
							x += nCntCopyWord;
						}
						else
						{
							// rc.left���� �������� ī���� ������ �ɸ� ���.
							if ( nLastWidth < rc.left && rc.left <= nCurrWidth )
							{
								x += (rc.left-nLastWidth);
								for ( INT nCheck = 0; nCheck < nCurrWidth-rc.left; nCheck++ )
								{
									wPixel	  = wChooseColor;
									bBlueWantedColor  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenWantedColor = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedWantedColor   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									wPixel	  = pwSrc[x+nCheck];
									bBlueSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenSrc = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
									rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
									bRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

									bBlueWantedColor = (BYTE)(((FLOAT)bBlueWantedColor*rBlueRate));
									bGreenWantedColor = (BYTE)(((FLOAT)bGreenWantedColor*rGreenRate));
									bRedWantedColor = (BYTE)(((FLOAT)bRedWantedColor*bRedRate));

									if ( bBlueWantedColor > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
										bBlueWantedColor = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
									if ( bGreenWantedColor > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
										bGreenWantedColor = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
									if ( bRedWantedColor > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
										bRedWantedColor = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);

									if ( ((nYCnt+nY) * lWidth) + (nLastWidth+nX+nCheck) < 0 )
										return FALSE;

									pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX+nCheck)] = ((bRedWantedColor  <<m_stBitsMaskInfo.bRShift) |
																										  (bGreenWantedColor<<m_stBitsMaskInfo.bGShift) |
																										  (bBlueWantedColor <<m_stBitsMaskInfo.bBShift));			
								}
								x += (nCurrWidth-rc.left);
							}
							// rc.right���� �������� ī���� ������ �ɸ� ���.
							else if ( nLastWidth <= rc.right && rc.right < nCurrWidth )
							{
								for ( INT nCheck = 0; nCheck < rc.right-nLastWidth; nCheck++ )
								{
									wPixel	  = wChooseColor;
									bBlueWantedColor  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenWantedColor = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedWantedColor   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									wPixel	  = pwSrc[x+nCheck];
									bBlueSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenSrc = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
									rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
									bRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

									bBlueWantedColor = (BYTE)(((FLOAT)bBlueWantedColor*rBlueRate));
									bGreenWantedColor = (BYTE)(((FLOAT)bGreenWantedColor*rGreenRate));
									bRedWantedColor = (BYTE)(((FLOAT)bRedWantedColor*bRedRate));

									if ( bBlueWantedColor > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
										bBlueWantedColor = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
									if ( bGreenWantedColor > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
										bGreenWantedColor = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
									if ( bRedWantedColor > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
										bRedWantedColor = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);

									pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX+nCheck)] = ((bRedWantedColor  <<m_stBitsMaskInfo.bRShift) |
																										  (bGreenWantedColor<<m_stBitsMaskInfo.bGShift) |
																										  (bBlueWantedColor <<m_stBitsMaskInfo.bBShift));			
								}
								x += nCntCopyWord;
							}
							else
							{
								for ( INT nCheck = 0; nCheck < nCntCopyWord; nCheck++ )
								{
									wPixel	  = wChooseColor;
									bBlueWantedColor  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenWantedColor = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedWantedColor   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									wPixel	  = pwSrc[x+nCheck];
									bBlueSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenSrc = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
									rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
									bRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

									bBlueWantedColor = (BYTE)(((FLOAT)bBlueWantedColor*rBlueRate));
									bGreenWantedColor = (BYTE)(((FLOAT)bGreenWantedColor*rGreenRate));
									bRedWantedColor = (BYTE)(((FLOAT)bRedWantedColor*bRedRate));

									if ( bBlueWantedColor > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
										bBlueWantedColor = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
									if ( bGreenWantedColor > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
										bGreenWantedColor = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
									if ( bRedWantedColor > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
										bRedWantedColor = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);

									pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX+nCheck)] = ((bRedWantedColor  <<m_stBitsMaskInfo.bRShift) |
																										  (bGreenWantedColor<<m_stBitsMaskInfo.bGShift) |
																									 	  (bBlueWantedColor <<m_stBitsMaskInfo.bBShift));			
								}
								x += nCntCopyWord;
							}
						}
					}	
					else
					{
						ddsDst->Unlock(NULL);
						return FALSE;
					}
				}
				// ������ ���� ���� ������ �������� �Ű��ش�.
				nWidthEnd++;

				nWidthStart	= nWidthEnd;
				nCurrWidth = 0;
			}
		}

		m_pddsBackBuffer->Unlock(NULL);
		return TRUE;
	}
	return FALSE;
}


BOOL CWHDXGraphicWindow::DrawWithImageForComp(
	INT nX, INT nY, INT nXSize, INT nYSize, WORD* pwSrc, WORD wChooseColor1, WORD wChooseColor2)
{
	RECT			rc;
	int				imgW;
	int				imgH;
	DDSURFACEDESC2	ddsd;

	if ( IS_OUTSIDE( nX, nY, nXSize, nYSize ) )
		return TRUE;

	CREATE_CLIP_REGION( nX, nY, nXSize, nYSize );

	LONG	lWidth;
	ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
	ddsd.dwSize = sizeof(DDSURFACEDESC2);
	if ( FAILED(m_pddsBackBuffer->Lock(NULL, &ddsd, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL)) )
	{
		return FALSE;
	}

	lWidth = ddsd.lPitch >> 1;

	WORD *dst = (WORD *) ddsd.lpSurface + (nY * lWidth) + nX;
	WORD *src = (WORD *) pwSrc;
	WORD *nxt, *tmp;
	
	int   y, pixelCnt, pixelPos, curPos;
	WORD  cc;         // choosecolor	
	BYTE  Rc, Gc, Bc; // choosecolor's RGB
	BYTE  Rs, Gs, Bs; // sourcecolor's RGB
	float Rr, Gr, Br; // sourcecolor's RGB Rate

	// Y ��ǥ Ŭ����
	for ( y = 0; y < rc.top; y++ )
		src	+= *src + 1;

	for ( y = nY; y < nY + imgH; y++ )
	{
		nxt		= src + *src++ + 1;
		curPos	= 0;

		while ( src < nxt )
		{
			if ( *src == 0xC0 )
			{
				++src;
				curPos += *src++;
			}
			else if ( *src == 0xC1 )
			{
				++src;
				pixelCnt = *src++;

				if ( curPos + pixelCnt > rc.left && curPos < rc.right )
				{
					// ���� Ŭ����
					if ( curPos < rc.left )
					{
						src		 += (rc.left - curPos);
						pixelCnt -= (rc.left - curPos);
						curPos	  = rc.left;
					}
								
					// ���� Ŭ����
					if ( curPos + pixelCnt > rc.right )
						memcpy( dst + curPos - rc.left, src, (rc.right - curPos) << 1 );
					else
						memcpy( dst + curPos - rc.left, src, pixelCnt << 1 );
				}

				src    += pixelCnt;
				curPos += pixelCnt;
			}
			else if ( *src == 0xC2 || *src == 0xC3 )				
			{
				cc = *src == 0xC2 ? wChooseColor1 : wChooseColor2;

				// ���� RGB
				Rc = (BYTE)((cc & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);
				Gc = (BYTE)((cc & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
				Bc = (BYTE)((cc & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);

				++src;
				pixelCnt = *src++;


				if ( curPos + pixelCnt > rc.left && curPos < rc.right )
				{				
					// ���� Ŭ����
					if ( curPos < rc.left )
					{
						src		 += (rc.left - curPos);
						pixelCnt -= (rc.left - curPos);
						curPos	  = rc.left;
					}

					tmp = dst + curPos - rc.left;

					for ( pixelPos = 0; pixelPos < pixelCnt; pixelPos++ )
					{
						// ���� Ŭ����
						if ( curPos + pixelPos > rc.right )
							break;

						cc = src[pixelPos];
						
						// ���� RGB
						Rs = (BYTE)((cc & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);
						Gs = (BYTE)((cc & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
						Bs = (BYTE)((cc & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
						
						// ���� RGB Rate
						Rr = (float)((float) Rs / (float)(m_stBitsMaskInfo.dwRMask >> m_stBitsMaskInfo.bRShift));
						Gr = (float)((float) Gs / (float)(m_stBitsMaskInfo.dwGMask >> m_stBitsMaskInfo.bGShift));
						Br = (float)((float) Bs / (float)(m_stBitsMaskInfo.dwBMask >> m_stBitsMaskInfo.bBShift));
						
						// ���� ���� RGB
						Rs = (BYTE)((float) Rc * Rr);
						Gs = (BYTE)((float) Gc * Gr);
						Bs = (BYTE)((float) Bc * Br);
						
						*tmp++ = Rs << m_stBitsMaskInfo.bRShift |
								 Gs << m_stBitsMaskInfo.bGShift |
								 Bs << m_stBitsMaskInfo.bBShift;
					}
				}

				src	   += pixelCnt;
				curPos += pixelCnt;
			}
			else
			{
				m_pddsBackBuffer->Unlock(NULL);
				return FALSE;
			}
		}

		dst += lWidth;
	}
	
	m_pddsBackBuffer->Unlock(NULL);

	return TRUE;
}



BOOL CWHDXGraphicWindow::DrawWithImageForCompClipRgnBase(INT nX, INT nY, INT nXSize, INT nYSize, WORD* pwSrc, WORD wClipWidth, WORD wClipHeight, WORD wChooseColor1, WORD wChooseColor2)
{
	RECT			rc;
	DDSURFACEDESC2	ddsd;

	INT	nWidth		= nXSize;
	INT	nHeight		= nYSize;
	INT	nXOffset	= 0;
	INT	nYOffset	= 0;
	INT	nStartX		= 0;
	INT	nStartY		= 0;
	INT	nEndX		= wClipWidth -1;
	INT	nEndY		= wClipHeight-1;

	if ( m_pddsBackBuffer != NULL )
	{
		if (nX < nStartX )
		{ 
			nXOffset	= nStartX - nX;
			nWidth		= nXSize - nXOffset;
		}
		if ( (nX+nXSize-1) > nEndX )
			nWidth		= nEndX - nX - nXOffset + 1;		
		if ( nY < nStartY )	
		{ 
			nYOffset	= nStartY - nY;
			nHeight		= nYSize - nYOffset;
		}		
		if ( (nY+nYSize-1) > nEndY )
			nHeight	= nEndY - nY - nYOffset + 1;

		if ( (nWidth > 0) && (nHeight > 0) )
		{
			rc.left		= nXOffset;
			rc.right	= nXOffset+nWidth;
			rc.top		= nYOffset;
			rc.bottom	= nYOffset+nHeight;

			LONG	lWidth;
			ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
			ddsd.dwSize = sizeof(DDSURFACEDESC2);
			if ( FAILED(m_pddsBackBuffer->Lock(NULL, &ddsd, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL)) )
			{
				return FALSE;
			}

			WORD* pwdDst = (WORD*)ddsd.lpSurface;
			lWidth		 = ddsd.lPitch >> 1;

			INT nWidthStart	= 0;
			INT nWidthEnd	= 0;
			INT nCurrWidth  = 0;
			INT nCntCopyWord = 0;
			INT nYCnt =0;
			INT nLastWidth = 0;

			FLOAT rBlueRate, rGreenRate, bRedRate;
			BYTE  bRedSrc, bGreenSrc, bBlueSrc;
			BYTE  bRedWantedColor, bGreenWantedColor, bBlueWantedColor;
			WORD  wPixel;

			// y�� Ŭ����.
  			for ( nYCnt=0 ; nYCnt < rc.top ; nYCnt++ )
			{
				nWidthEnd += pwSrc[nWidthStart];
				nWidthStart++;
				nWidthEnd++;
				nWidthStart	= nWidthEnd;
			}

			// y�࿡ ���ؼ� ������ ���ν�ų Count���� ���Ѵ�.
			for ( nYCnt=rc.top ; nYCnt < rc.bottom ; nYCnt++ )
			{
				// �Ѷ����� ���̸� ���´�.(������ ����)
				nWidthEnd += pwSrc[nWidthStart];
				nWidthStart++;

				// ������ ���̸�ŭ ȭ�鿡 �ѷ��ش�.
				for ( INT x = nWidthStart; x < nWidthEnd ; )
				{
					if ( pwSrc[x] == 0xC0 )
					{
						x++;
						nCntCopyWord = pwSrc[x];
						x++;
						nCurrWidth += nCntCopyWord;
					}
					else if ( pwSrc[x] == 0xC1 )
					{
						x++;
						nCntCopyWord = pwSrc[x];
						x++;

						nLastWidth = nCurrWidth;
						nCurrWidth += nCntCopyWord;

						if ( rc.left > nCurrWidth || rc.right < nLastWidth )
						{
							x += nCntCopyWord;
						}
						else
						{
							// rc.left���� �������� ī���� ������ �ɸ� ���.
							if ( nLastWidth < rc.left && rc.left <= nCurrWidth )
							{
								if ( ((nYCnt+nY) * lWidth) + (rc.left+nX) < 0 )
									return FALSE;

								x += (rc.left-nLastWidth);
								memcpy(&pwdDst[((nYCnt+nY) * lWidth) + (rc.left+nX)], &pwSrc[x], sizeof(WORD)*(nCurrWidth-rc.left));
								x += (nCurrWidth-rc.left);
							}
							// rc.right���� �������� ī���� ������ �ɸ� ���.
							else if ( nLastWidth <= rc.right && rc.right < nCurrWidth )
							{
								memcpy(&pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX)], &pwSrc[x], sizeof(WORD)*(rc.right-nLastWidth));
								x += nCntCopyWord;
							}
							else
							{
								memcpy(&pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX)], &pwSrc[x], sizeof(WORD)*nCntCopyWord);
								x += nCntCopyWord;
							}
						}
					}
					else if ( pwSrc[x] == 0xC2 || pwSrc[x] == 0xC3 )
					{
						WORD wDyingKind, wChooseColor;
						wDyingKind = pwSrc[x];
						switch ( wDyingKind )
						{
						case 0xC2: 
							wChooseColor = wChooseColor1;
							break;
						case 0xC3: 
							wChooseColor = wChooseColor2;
							break;
						}
						x++;
						nCntCopyWord = pwSrc[x];
						x++;

						nLastWidth = nCurrWidth;
						nCurrWidth += nCntCopyWord;

						if ( rc.left > nCurrWidth || rc.right < nLastWidth )
						{
							x += nCntCopyWord;
						}
						else
						{
							// rc.left���� �������� ī���� ������ �ɸ� ���.
							if ( nLastWidth < rc.left && rc.left <= nCurrWidth )
							{
								x += (rc.left-nLastWidth);
								for ( INT nCheck = 0; nCheck < nCurrWidth-rc.left; nCheck++ )
								{
									wPixel	  = wChooseColor;
									bBlueWantedColor  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenWantedColor = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedWantedColor   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									wPixel	  = pwSrc[x+nCheck];
									bBlueSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenSrc = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
									rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
									bRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

									bBlueWantedColor = (BYTE)(((FLOAT)bBlueWantedColor*rBlueRate));
									bGreenWantedColor = (BYTE)(((FLOAT)bGreenWantedColor*rGreenRate));
									bRedWantedColor = (BYTE)(((FLOAT)bRedWantedColor*bRedRate));

									if ( bBlueWantedColor > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
										bBlueWantedColor = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
									if ( bGreenWantedColor > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
										bGreenWantedColor = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
									if ( bRedWantedColor > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
										bRedWantedColor = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);

									if ( ((nYCnt+nY) * lWidth) + (nLastWidth+nX+nCheck) < 0 )
										return FALSE;

									pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX+nCheck)] = ((bRedWantedColor  <<m_stBitsMaskInfo.bRShift) |
																										  (bGreenWantedColor<<m_stBitsMaskInfo.bGShift) |
																									 	  (bBlueWantedColor <<m_stBitsMaskInfo.bBShift));			
								}
								x += (nCurrWidth-rc.left);
							}
							// rc.right���� �������� ī���� ������ �ɸ� ���.
							else if ( nLastWidth <= rc.right && rc.right < nCurrWidth )
							{
								for ( INT nCheck = 0; nCheck < rc.right-nLastWidth; nCheck++ )
								{
									wPixel	  = wChooseColor;
									bBlueWantedColor  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenWantedColor = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedWantedColor   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									wPixel	  = pwSrc[x+nCheck];
									bBlueSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenSrc = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
									rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
									bRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

									bBlueWantedColor = (BYTE)(((FLOAT)bBlueWantedColor*rBlueRate));
									bGreenWantedColor = (BYTE)(((FLOAT)bGreenWantedColor*rGreenRate));
									bRedWantedColor = (BYTE)(((FLOAT)bRedWantedColor*bRedRate));

									if ( bBlueWantedColor > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
										bBlueWantedColor = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
									if ( bGreenWantedColor > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
										bGreenWantedColor = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
									if ( bRedWantedColor > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
										bRedWantedColor = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);

									pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX+nCheck)] = ((bRedWantedColor  <<m_stBitsMaskInfo.bRShift) |
																										  (bGreenWantedColor<<m_stBitsMaskInfo.bGShift) |
																									 	  (bBlueWantedColor <<m_stBitsMaskInfo.bBShift));			
								}
								x += nCntCopyWord;
							}
							else
							{
								for ( INT nCheck = 0; nCheck < nCntCopyWord; nCheck++ )
								{
									wPixel	  = wChooseColor;
									bBlueWantedColor  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenWantedColor = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedWantedColor   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									wPixel	  = pwSrc[x+nCheck];
									bBlueSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenSrc = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
									rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
									bRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

									bBlueWantedColor = (BYTE)(((FLOAT)bBlueWantedColor*rBlueRate));
									bGreenWantedColor = (BYTE)(((FLOAT)bGreenWantedColor*rGreenRate));
									bRedWantedColor = (BYTE)(((FLOAT)bRedWantedColor*bRedRate));

									if ( bBlueWantedColor > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
										bBlueWantedColor = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
									if ( bGreenWantedColor > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
										bGreenWantedColor = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
									if ( bRedWantedColor > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
										bRedWantedColor = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);

									pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX+nCheck)] = ((bRedWantedColor  <<m_stBitsMaskInfo.bRShift) |
																										  (bGreenWantedColor<<m_stBitsMaskInfo.bGShift) |
																									 	  (bBlueWantedColor <<m_stBitsMaskInfo.bBShift));			
								}
								x += nCntCopyWord;
							}
						}
					}	
					else
					{
						m_pddsBackBuffer->Unlock(NULL);
						return FALSE;
					}
				}
				// ������ ���� ���� ������ �������� �Ű��ش�.
				nWidthEnd++;

				nWidthStart	= nWidthEnd;
				nCurrWidth = 0;
			}
		}

		m_pddsBackBuffer->Unlock(NULL);
		return TRUE;
	}
	return FALSE;
}

BOOL CWHDXGraphicWindow::DrawWithImageForCompClipRgnBaseNoColor(INT nX, INT nY, INT nXSize, INT nYSize, WORD* pwSrc, WORD wClipWidth, WORD wClipHeight)
{
	RECT			rc;
	DDSURFACEDESC2	ddsd;

	INT	nWidth		= nXSize;
	INT	nHeight		= nYSize;
	INT	nXOffset	= 0;
	INT	nYOffset	= 0;
	INT	nStartX		= 0;
	INT	nStartY		= 0;
	INT	nEndX		= wClipWidth -1;
	INT	nEndY		= wClipHeight-1;

	if ( m_pddsBackBuffer != NULL )
	{
		if (nX < nStartX )
		{ 
			nXOffset	= nStartX - nX;
			nWidth		= nXSize - nXOffset;
		}
		if ( (nX+nXSize-1) > nEndX )
			nWidth		= nEndX - nX - nXOffset + 1;		
		if ( nY < nStartY )	
		{ 
			nYOffset	= nStartY - nY;
			nHeight		= nYSize - nYOffset;
		}		
		if ( (nY+nYSize-1) > nEndY )
			nHeight	= nEndY - nY - nYOffset + 1;

		if ( (nWidth > 0) && (nHeight > 0) )
		{
			rc.left		= nXOffset;
			rc.right	= nXOffset+nWidth;
			rc.top		= nYOffset;
			rc.bottom	= nYOffset+nHeight;

			LONG	lWidth;
			ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
			ddsd.dwSize = sizeof(DDSURFACEDESC2);
			if ( FAILED(m_pddsBackBuffer->Lock(NULL, &ddsd, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL)) )
			{
				return FALSE;
			}

			WORD* pwdDst = (WORD*)ddsd.lpSurface;
			lWidth		 = ddsd.lPitch >> 1;

			INT nWidthStart	= 0;
			INT nWidthEnd	= 0;
			INT nCurrWidth  = 0;
			INT nCntCopyWord = 0;
			INT nYCnt =0;
			INT nLastWidth = 0;

			// y�� Ŭ����.
  			for ( nYCnt=0 ; nYCnt < rc.top ; nYCnt++ )
			{
				nWidthEnd += pwSrc[nWidthStart];
				nWidthStart++;
				nWidthEnd++;
				nWidthStart	= nWidthEnd;
			}

			// y�࿡ ���ؼ� ������ ���ν�ų Count���� ���Ѵ�.
			for ( nYCnt=rc.top ; nYCnt < rc.bottom ; nYCnt++ )
			{
				// �Ѷ����� ���̸� ���´�.(������ ����)
				nWidthEnd += pwSrc[nWidthStart];
				nWidthStart++;

				// ������ ���̸�ŭ ȭ�鿡 �ѷ��ش�.
				for ( INT x = nWidthStart; x < nWidthEnd ; )
				{
					if ( pwSrc[x] == 0xC0 )
					{
						x++;
						nCntCopyWord = pwSrc[x];
						x++;
						nCurrWidth += nCntCopyWord;
					}
					else 
					{
						x++;
						nCntCopyWord = pwSrc[x];
						x++;

						nLastWidth = nCurrWidth;
						nCurrWidth += nCntCopyWord;

						if ( rc.left > nCurrWidth || rc.right < nLastWidth )
						{
							x += nCntCopyWord;
						}
						else
						{
							// rc.left���� �������� ī���� ������ �ɸ� ���.
							if ( nLastWidth < rc.left && rc.left <= nCurrWidth )
							{
								if ( ((nYCnt+nY) * lWidth) + (rc.left+nX) < 0 )
									return FALSE;

								x += (rc.left-nLastWidth);
								memcpy(&pwdDst[((nYCnt+nY) * lWidth) + (rc.left+nX)], &pwSrc[x], sizeof(WORD)*(nCurrWidth-rc.left));
								x += (nCurrWidth-rc.left);
							}
							// rc.right���� �������� ī���� ������ �ɸ� ���.
							else if ( nLastWidth <= rc.right && rc.right < nCurrWidth )
							{
								memcpy(&pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX)], &pwSrc[x], sizeof(WORD)*(rc.right-nLastWidth));
								x += nCntCopyWord;
							}
							else
							{
								memcpy(&pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX)], &pwSrc[x], sizeof(WORD)*nCntCopyWord);
								x += nCntCopyWord;
							}
						}
					}
				}


				// ������ ���� ���� ������ �������� �Ű��ش�.
				nWidthEnd++;

				nWidthStart	= nWidthEnd;
				nCurrWidth = 0;
			}
		}

		m_pddsBackBuffer->Unlock(NULL);
		return TRUE;
	}
	return FALSE;
}


BOOL CWHDXGraphicWindow::DrawWithABlendCompDataWithBackBuffer(INT nX, INT nY, 
															  INT nXSize, INT nYSize, WORD* pwSrc,
															  WORD wClipWidth, WORD wClipHeight,
															  WORD wChooseColor1, WORD wChooseColor2, BYTE bOpa)
{
	RECT			rc;
	DDSURFACEDESC2	ddsd;

	INT	nWidth		= nXSize;
	INT	nHeight		= nYSize;
	INT	nXOffset	= 0;
	INT	nYOffset	= 0;
	INT	nStartX		= 0;
	INT	nStartY		= 0;
	INT	nEndX		= wClipWidth -1;
	INT	nEndY		= wClipHeight-1;

	WORD wDyingKind, wChooseColor;

	if ( m_pddsBackBuffer != NULL )
	{
		if (nX < nStartX )
		{ 
			nXOffset	= nStartX - nX;
			nWidth		= nXSize - nXOffset;
		}
		if ( (nX+nXSize-1) > nEndX )
			nWidth		= nEndX - nX - nXOffset + 1;		
		if ( nY < nStartY )	
		{ 
			nYOffset	= nStartY - nY;
			nHeight		= nYSize - nYOffset;
		}		
		if ( (nY+nYSize-1) > nEndY )
			nHeight	= nEndY - nY - nYOffset + 1;

		if ( (nWidth > 0) && (nHeight > 0) )
		{
			rc.left		= nXOffset;
			rc.right	= nXOffset+nWidth;
			rc.top		= nYOffset;
			rc.bottom	= nYOffset+nHeight;

			LONG	lWidth;
			ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
			ddsd.dwSize = sizeof(DDSURFACEDESC2);
			if ( FAILED(m_pddsBackBuffer->Lock(NULL, &ddsd, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL)) )
			{
				return FALSE;
			}

			WORD* pwdDst = (WORD*)ddsd.lpSurface;
			lWidth		 = ddsd.lPitch >> 1;

			INT nWidthStart	= 0;
			INT nWidthEnd	= 0;
			INT nCurrWidth  = 0;
			INT nCntCopyWord = 0;
			INT nYCnt =0;
			INT nLastWidth = 0;

			BYTE bRedDst, bGreenDst, bBlueDst;
			BYTE bRedSrc, bGreenSrc, bBlueSrc;
			BYTE bRedWantedColor, bGreenWantedColor, bBlueWantedColor;
			WORD wPixel;
			FLOAT rBlueRate, rGreenRate, bRedRate;

			// y�� Ŭ����.
  			for ( nYCnt=0 ; nYCnt < rc.top ; nYCnt++ )
			{
				nWidthEnd += pwSrc[nWidthStart];
				nWidthStart++;
				nWidthEnd++;
				nWidthStart	= nWidthEnd;
			}

			// y�࿡ ���ؼ� ������ ���ν�ų Count���� ���Ѵ�.
			for ( nYCnt=rc.top ; nYCnt < rc.bottom ; nYCnt++ )
			{
				// �Ѷ����� ���̸� ���´�.(������ ����)
				nWidthEnd += pwSrc[nWidthStart];
				nWidthStart++;

				// ������ ���̸�ŭ ȭ�鿡 �ѷ��ش�.
				for ( INT x = nWidthStart; x < nWidthEnd ; )
				{
					if ( pwSrc[x] == 0xC0 )
					{
						x++;
						nCntCopyWord = pwSrc[x];
						x++;
						nCurrWidth += nCntCopyWord;
					}
					else if ( pwSrc[x] == 0xC1 )
					{
						x++;
						nCntCopyWord = pwSrc[x];
						x++;

						nLastWidth = nCurrWidth;
						nCurrWidth += nCntCopyWord;

						if ( rc.left > nCurrWidth || rc.right < nLastWidth )
						{
							x += nCntCopyWord;
						}
						else
						{
							// rc.left���� �������� ī���� ������ �ɸ� ���.
							if ( nLastWidth < rc.left && rc.left <= nCurrWidth )
							{
								x += (rc.left-nLastWidth);
								for ( INT nCheck = 0; nCheck < nCurrWidth-rc.left; nCheck++ )
								{
									wPixel	   = pwSrc[x+nCheck];
									bBlueSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedSrc    = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									wPixel	   = pwdDst[((nYCnt+nY) * lWidth) + (rc.left+nX+nCheck)];
									bBlueDst   = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenDst  = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedDst    = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									bBlueDst   = (BYTE)((bOpa*(bBlueDst -bBlueSrc )+100*bBlueSrc  ) / 100);
									bGreenDst  = (BYTE)((bOpa*(bGreenDst-bGreenSrc)+100*bGreenSrc ) / 100);
									bRedDst    = (BYTE)((bOpa*(bRedDst  -bRedSrc  )+100*bRedSrc   ) / 100);

									if ( ((nYCnt+nY) * lWidth) + (rc.left+nX+nCheck) < 0 )
										return FALSE;

									pwdDst[((nYCnt+nY) * lWidth) + (rc.left+nX+nCheck)] = ((bRedDst  <<m_stBitsMaskInfo.bRShift) |
																									   (bGreenDst<<m_stBitsMaskInfo.bGShift) |
																									   (bBlueDst <<m_stBitsMaskInfo.bBShift));										
								}
								x += (nCurrWidth-rc.left);
							}
							// rc.right���� �������� ī���� ������ �ɸ� ���.
							else if ( nLastWidth <= rc.right && rc.right < nCurrWidth )
							{
								for ( INT nCheck = 0; nCheck < rc.right-nLastWidth; nCheck++ )
								{
									wPixel	   = pwSrc[x+nCheck];
									bBlueSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedSrc    = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									wPixel	   = pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX+nCheck)];
									bBlueDst   = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenDst  = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedDst    = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									bBlueDst   = (BYTE)((bOpa*(bBlueDst -bBlueSrc )+100*bBlueSrc  ) / 100);
									bGreenDst  = (BYTE)((bOpa*(bGreenDst-bGreenSrc)+100*bGreenSrc ) / 100);
									bRedDst    = (BYTE)((bOpa*(bRedDst  -bRedSrc  )+100*bRedSrc   ) / 100);

									pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX+nCheck)] = ((bRedDst  <<m_stBitsMaskInfo.bRShift) |
																									      (bGreenDst<<m_stBitsMaskInfo.bGShift) |
																										  (bBlueDst <<m_stBitsMaskInfo.bBShift));			
								}
								x += nCntCopyWord;
							}
							else
							{
								for ( INT nCheck = 0; nCheck < nCntCopyWord; nCheck++ )
								{
									wPixel	   = pwSrc[x+nCheck];
									bBlueSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedSrc    = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									wPixel	   = pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX+nCheck)];
									bBlueDst   = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenDst  = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedDst    = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									bBlueDst   = (BYTE)((bOpa*(bBlueDst -bBlueSrc )+100*bBlueSrc  ) / 100);
									bGreenDst  = (BYTE)((bOpa*(bGreenDst-bGreenSrc)+100*bGreenSrc ) / 100);
									bRedDst    = (BYTE)((bOpa*(bRedDst  -bRedSrc  )+100*bRedSrc   ) / 100);

									pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX+nCheck)] = ((bRedDst  <<m_stBitsMaskInfo.bRShift) |
																									      (bGreenDst<<m_stBitsMaskInfo.bGShift) |
																										  (bBlueDst <<m_stBitsMaskInfo.bBShift));			
								}
								x += nCntCopyWord;
							}
						}
					}
					else if ( pwSrc[x] == 0xC2 || pwSrc[x] == 0xC3 )
					{
						wDyingKind = pwSrc[x];
						switch ( wDyingKind )
						{
						case 0xC2: 
							wChooseColor = wChooseColor1;
							break;
						case 0xC3: 
							wChooseColor = wChooseColor2;
							break;
						}
						x++;
						nCntCopyWord = pwSrc[x];
						x++;

						nLastWidth = nCurrWidth;
						nCurrWidth += nCntCopyWord;

						if ( rc.left > nCurrWidth || rc.right < nLastWidth )
						{
							x += nCntCopyWord;
						}
						else
						{
							// rc.left���� �������� ī���� ������ �ɸ� ���.
							if ( nLastWidth < rc.left && rc.left <= nCurrWidth )
							{
								x += (rc.left-nLastWidth);
								for ( INT nCheck = 0; nCheck < nCurrWidth-rc.left; nCheck++ )
								{
									wPixel	  = wChooseColor;
									bBlueWantedColor  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenWantedColor = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedWantedColor   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									wPixel	  = pwSrc[x+nCheck];
									bBlueSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenSrc = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
									rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
									bRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

									bBlueWantedColor = (BYTE)(((FLOAT)bBlueWantedColor*rBlueRate));
									bGreenWantedColor = (BYTE)(((FLOAT)bGreenWantedColor*rGreenRate));
									bRedWantedColor = (BYTE)(((FLOAT)bRedWantedColor*bRedRate));

									if ( bBlueWantedColor > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
										bBlueWantedColor = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
									if ( bGreenWantedColor > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
										bGreenWantedColor = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
									if ( bRedWantedColor > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
										bRedWantedColor = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);


									wPixel  = pwdDst[((nYCnt+nY) * lWidth) + (rc.left+nX+nCheck)];
									bBlueDst   = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenDst  = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedDst    = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									bBlueDst   = (BYTE)((bOpa*(bBlueDst -bBlueWantedColor )+100*bBlueWantedColor ) / 100);
									bGreenDst  = (BYTE)((bOpa*(bGreenDst-bGreenWantedColor)+100*bGreenWantedColor) / 100);
									bRedDst    = (BYTE)((bOpa*(bRedDst  -bRedWantedColor  )+100*bRedWantedColor  ) / 100);

									if ( ((nYCnt+nY) * lWidth) + (rc.left+nX+nCheck) < 0 )
										return FALSE;

									pwdDst[((nYCnt+nY) * lWidth) + (rc.left+nX+nCheck)] = ((bRedDst  <<m_stBitsMaskInfo.bRShift) |
																									   (bGreenDst<<m_stBitsMaskInfo.bGShift) |
																									   (bBlueDst <<m_stBitsMaskInfo.bBShift));
								}
								x += (nCurrWidth-rc.left);
							}
							// rc.right���� �������� ī���� ������ �ɸ� ���.
							else if ( nLastWidth <= rc.right && rc.right < nCurrWidth )
							{
								for ( INT nCheck = 0; nCheck < rc.right-nLastWidth; nCheck++ )
								{
									wPixel	  = wChooseColor;
									bBlueWantedColor  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenWantedColor = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedWantedColor   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									wPixel	  = pwSrc[x+nCheck];
									bBlueSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenSrc = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
									rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
									bRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

									bBlueWantedColor = (BYTE)(((FLOAT)bBlueWantedColor*rBlueRate));
									bGreenWantedColor = (BYTE)(((FLOAT)bGreenWantedColor*rGreenRate));
									bRedWantedColor = (BYTE)(((FLOAT)bRedWantedColor*bRedRate));

									if ( bBlueWantedColor > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
										bBlueWantedColor = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
									if ( bGreenWantedColor > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
										bGreenWantedColor = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
									if ( bRedWantedColor > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
										bRedWantedColor = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);


									wPixel  = pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX+nCheck)];
									bBlueDst   = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenDst  = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedDst    = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									bBlueDst   = (BYTE)((bOpa*(bBlueDst -bBlueWantedColor )+100*bBlueWantedColor ) / 100);
									bGreenDst  = (BYTE)((bOpa*(bGreenDst-bGreenWantedColor)+100*bGreenWantedColor) / 100);
									bRedDst    = (BYTE)((bOpa*(bRedDst  -bRedWantedColor  )+100*bRedWantedColor  ) / 100);

									pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX+nCheck)] = ((bRedDst  <<m_stBitsMaskInfo.bRShift) |
																									      (bGreenDst<<m_stBitsMaskInfo.bGShift) |
																										  (bBlueDst <<m_stBitsMaskInfo.bBShift));			
								}
								x += nCntCopyWord;
							}
							else
							{
								for ( INT nCheck = 0; nCheck < nCntCopyWord; nCheck++ )
								{
									wPixel	  = wChooseColor;
									bBlueWantedColor  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenWantedColor = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedWantedColor   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									wPixel	  = pwSrc[x+nCheck];
									bBlueSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenSrc = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
									rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
									bRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

									bBlueWantedColor = (BYTE)(((FLOAT)bBlueWantedColor*rBlueRate));
									bGreenWantedColor = (BYTE)(((FLOAT)bGreenWantedColor*rGreenRate));
									bRedWantedColor = (BYTE)(((FLOAT)bRedWantedColor*bRedRate));

									if ( bBlueWantedColor > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
										bBlueWantedColor = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
									if ( bGreenWantedColor > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
										bGreenWantedColor = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
									if ( bRedWantedColor > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
										bRedWantedColor = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);


									wPixel  = pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX+nCheck)];
									bBlueDst   = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenDst  = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedDst    = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									bBlueDst   = (BYTE)((bOpa*(bBlueDst -bBlueWantedColor )+100*bBlueWantedColor ) / 100);
									bGreenDst  = (BYTE)((bOpa*(bGreenDst-bGreenWantedColor)+100*bGreenWantedColor) / 100);
									bRedDst    = (BYTE)((bOpa*(bRedDst  -bRedWantedColor  )+100*bRedWantedColor  ) / 100);

									pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX+nCheck)] = ((bRedDst  <<m_stBitsMaskInfo.bRShift) |
																									      (bGreenDst<<m_stBitsMaskInfo.bGShift) |
																										  (bBlueDst <<m_stBitsMaskInfo.bBShift));			
								}
								x += nCntCopyWord;
							}
						}
					}	
					else
					{
						m_pddsBackBuffer->Unlock(NULL);
						return FALSE;
					}
				}
				// ������ ���� ���� ������ �������� �Ű��ش�.
				nWidthEnd++;

				nWidthStart	= nWidthEnd;
				nCurrWidth = 0;
			}
		}

		m_pddsBackBuffer->Unlock(NULL);
		return TRUE;
	}
	return FALSE;
}



BOOL CWHDXGraphicWindow::DrawWithABlendCompDataWithBackBufferEx(INT nX, INT nY, 
															  INT nXSize, INT nYSize, WORD* pwSrc,
															  WORD wClipWidth, WORD wClipHeight,
															  WORD wChooseColor1, WORD wChooseColor2, BYTE bOpa)
{
	RECT			rc;
	int				imgW;
	int				imgH;
	DDSURFACEDESC2	ddsd;

	if ( IS_OUTSIDE( nX, nY, nXSize, nYSize ) )
		return TRUE;

	CREATE_CLIP_REGION( nX, nY, nXSize, nYSize );

	LONG	lWidth;
	ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
	ddsd.dwSize = sizeof(DDSURFACEDESC2);
	if ( FAILED(m_pddsBackBuffer->Lock(NULL, &ddsd, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL)) )
	{
		return FALSE;
	}

	WORD* pwdDst = (WORD*)ddsd.lpSurface;
	lWidth		 = ddsd.lPitch >> 1;

	WORD *dst = (WORD *) ddsd.lpSurface + (nY * lWidth) + nX;
	WORD *src = (WORD *) pwSrc;
	WORD *nxt, *tmp;
	
	int   y, pixelCnt, pixelPos, curPos;
	WORD  cc;				// choosecolor
	BYTE  Rc, Gc, Bc;		// choosecolor's RGB
	BYTE  Rs, Gs, Bs;		// sourcecolor's RGB
	float Rr, Gr, Br;		// sourcecolor's RGB Rate
	WORD  finalColor;		// final RGB

	// Y�� Ŭ����
	for ( y = 0; y < rc.top; y++ )
		src	+= *src + 1;

	for ( y = nY; y < nY + imgH; y++ )
	{
		nxt		= src + *src++ + 1;
		curPos	= 0;

		while ( src < nxt )
		{
			if ( *src == 0xC0 )
			{
				++src;
				curPos += *src++;
			}
			else if ( *src == 0xC1 )
			{
				++src;
				pixelCnt = *src++;

				if ( curPos + pixelCnt > rc.left && curPos < rc.right )
				{
					// ���� Ŭ����
					if ( curPos < rc.left )
					{
						src		 += (rc.left - curPos);
						pixelCnt -= (rc.left - curPos);
						curPos	  = rc.left;
					}
								
					// ���� Ŭ����
					if ( curPos + pixelCnt > rc.right )
						putAlpha32( dst + curPos - rc.left, src, rc.right - curPos, bOpa );
					else
						putAlpha32( dst + curPos - rc.left, src, pixelCnt, bOpa );
				}

				src    += pixelCnt;
				curPos += pixelCnt;
			}
			else if ( *src == 0xC2 || *src == 0xC3 )				
			{
				cc = *src == 0xC2 ? wChooseColor1 : wChooseColor2;

				// ���� RGB
				Rc = (BYTE)((cc & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);
				Gc = (BYTE)((cc & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
				Bc = (BYTE)((cc & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);

				++src;
				pixelCnt = *src++;


				if ( curPos + pixelCnt > rc.left && curPos < rc.right )
				{				
					// ���� Ŭ����
					if ( curPos < rc.left )
					{
						src		 += (rc.left - curPos);
						pixelCnt -= (rc.left - curPos);
						curPos	  = rc.left;
					}

					tmp = dst + curPos - rc.left;

					for ( pixelPos = 0; pixelPos < pixelCnt; pixelPos++ )
					{
						// ���� Ŭ����
						if ( curPos + pixelPos > rc.right )
							break;

						cc = src[pixelPos];
						
						// ���� RGB
						Rs = (BYTE)((cc & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);
						Gs = (BYTE)((cc & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
						Bs = (BYTE)((cc & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
						
						// ���� RGB Rate
						Rr = (float)((float) Rs / (float)(m_stBitsMaskInfo.dwRMask >> m_stBitsMaskInfo.bRShift));
						Gr = (float)((float) Gs / (float)(m_stBitsMaskInfo.dwGMask >> m_stBitsMaskInfo.bGShift));
						Br = (float)((float) Bs / (float)(m_stBitsMaskInfo.dwBMask >> m_stBitsMaskInfo.bBShift));
						
						// ���� ���� RGB
						Rs = (BYTE)((float) Rc * Rr);
						Gs = (BYTE)((float) Gc * Gr);
						Bs = (BYTE)((float) Bc * Br);

						finalColor = Rs << m_stBitsMaskInfo.bRShift | 
									 Gs << m_stBitsMaskInfo.bGShift | 
									 Bs << m_stBitsMaskInfo.bBShift;

						putAlpha32Pixel( tmp++, finalColor, bOpa );
					}
				}

				src	   += pixelCnt;
				curPos += pixelCnt;
			}
			else
			{
				m_pddsBackBuffer->Unlock(NULL);
				return FALSE;
			}
		}

		dst += lWidth;
	}
	
	m_pddsBackBuffer->Unlock(NULL);

	return TRUE;
}


BOOL CWHDXGraphicWindow::DrawWithShadowABlend(INT nX, INT nY, INT nXSize, INT nYSize, WORD* pwSrc, WORD wClipWidth, WORD wClipHeight,
											  WORD* pwShadowClrSrc, BOOL bBlend, BYTE bShadowType, BYTE bOpa)

{
	RECT			rc;
	DDSURFACEDESC2	ddsd;

	INT	nXOffset = 0;
	INT	nYOffset = 0;
	INT	nStartX	 = 0;
	INT	nStartY	 = 0;
	INT	nWidth	 = nXSize;
	INT	nHeight	 = nYSize;
	INT	nEndX	 = wClipWidth -1;
	INT	nEndY	 = wClipHeight-1;

	// ���� �ʴ� �׸���.
	if ( bShadowType == 48 )
	{
		return FALSE;
	}

	if ( m_pddsBackBuffer != NULL )
	{
		rc.left		= 0;
		rc.top		= 0;
		rc.right	= nWidth;
		rc.bottom	= nHeight;

		LONG	lWidth;
		ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
		ddsd.dwSize = sizeof(DDSURFACEDESC2);
		if ( FAILED(m_pddsBackBuffer->Lock(NULL, &ddsd, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL)) )
		{
			return FALSE;
		}

		WORD* pwdDst = (WORD*)ddsd.lpSurface;
		lWidth		 = ddsd.lPitch >> 1;

		INT nWidthStart	 = 0;
		INT nWidthEnd	 = 0;
		INT nCurrWidth   = 0;
		INT nCntCopyWord = 0;
		INT nYCnt		 = 0;
		INT nLastWidth   = 0;
		INT nDstXPos	 = 0;
		INT nDstYPos	 = 0;

		RECT rcScrnShadow;

		if ( bShadowType == 49 )
		{
			SetRect(&rcScrnShadow, nX, nY, nX+nHeight/2+nWidth, nY+nHeight/2);
		}
		else if ( bShadowType == 50 )
		{
			SetRect(&rcScrnShadow, nX, nY, nX+nWidth, nY+nHeight);
		}

		// y�࿡ ���ؼ� ������ ���ν�ų Count���� ���Ѵ�.
		for ( nYCnt=rc.top ; nYCnt < rc.bottom ; nYCnt++ )
		{
			// �Ѷ����� ���̸� ���´�.(������ ����)
			nWidthEnd += pwSrc[nWidthStart];
			nWidthStart++;

			if ( bShadowType == 49 )
			{
				nDstYPos = nYCnt-nYCnt/2+nY;
			}
			else if ( bShadowType == 50 )
			{
				nDstYPos = nYCnt+nY;
			}

			if ( nDstYPos < 0 || nDstYPos >= wClipHeight || (bShadowType==49 && nYCnt%2) )
			{
				// ������ ���� ���� ������ �������� �Ű��ش�.
				nWidthEnd++;
				nWidthStart	= nWidthEnd;
				nCurrWidth = 0;
				continue;
			}

			// ������ ���̸�ŭ ȭ�鿡 �ѷ��ش�.
			for ( INT x = nWidthStart; x < nWidthEnd ; )
			{
				if ( pwSrc[x] == 0xC0 )
				{
					x++;
					nCntCopyWord = pwSrc[x];
					x++;
					nCurrWidth += nCntCopyWord;
				}
				else if ( pwSrc[x] == 0xC1 || pwSrc[x] == 0xC2 || pwSrc[x] == 0xC3 )
				{
					x++;
					nCntCopyWord = pwSrc[x];
					x++;

					nLastWidth = nCurrWidth;
					nCurrWidth += nCntCopyWord;

					if ( bShadowType == 49 )
					{
						nDstXPos = (nLastWidth+nX+(rc.bottom-nYCnt)/2);
					}
					else if ( bShadowType == 50 )
					{
						nDstXPos = (nLastWidth+nX);
					}

					if ( !bBlend ) 
					{
						// ���� �ɸ���.
						if ( nDstXPos < 0 && nDstXPos+nCntCopyWord >= 0 )
						{
							for ( INT nCheck = 0; nCheck < nCntCopyWord; nCheck++ )
							{
								if ( nDstXPos+nCheck >= 0 && nDstXPos+nCheck < wClipWidth )
								{
									pwdDst[(nDstYPos * lWidth) + nDstXPos+nCheck] = *pwShadowClrSrc;
								}
							}
							x += nCntCopyWord;
						}
						// ������ �ɸ���.
						else if ( nDstXPos < wClipWidth && nDstXPos+nCntCopyWord >= wClipWidth )
						{
							for ( INT nCheck = 0; nCheck < nCntCopyWord; nCheck++ )
							{
								if ( nDstXPos+nCheck >= 0 && nDstXPos+nCheck < wClipWidth )
								{
									pwdDst[(nDstYPos * lWidth) + nDstXPos+nCheck] = *pwShadowClrSrc;

								}
							}
							x += nCntCopyWord;
						}
						// �Ȱɸ���.
						else if ( nDstXPos >= 0 && nDstXPos+nCntCopyWord < wClipWidth )
						{
							memcpy(&pwdDst[(nDstYPos * lWidth) + nDstXPos], pwShadowClrSrc, sizeof(WORD)*nCntCopyWord);
							x += nCntCopyWord;
						}
						else
						{
							x += nCntCopyWord;
						}
					}
					else
					{
						// ���� �ɸ���.
						if ( nDstXPos < 0 && nDstXPos+nCntCopyWord >= 0 )
						{
							if ( (nDstYPos * lWidth) + nDstXPos < 0 )
							{
								return	FALSE;
							}
							putAlpha32( &pwdDst[(nDstYPos * lWidth) + nDstXPos], pwShadowClrSrc, nCntCopyWord, bOpa );

							x += nCntCopyWord;
						}
						// ������ �ɸ���.
						else if ( nDstXPos < wClipWidth && nDstXPos+nCntCopyWord >= wClipWidth )
						{
							putAlpha32( &pwdDst[(nDstYPos * lWidth) + nDstXPos], pwShadowClrSrc, nDstXPos+nCntCopyWord-wClipWidth, bOpa );

							x += nCntCopyWord;
						}
						// �Ȱɸ���.
						else if ( nDstXPos >= 0 && nDstXPos+nCntCopyWord < wClipWidth )
						{
							putAlpha32( &pwdDst[(nDstYPos * lWidth) + nDstXPos], pwShadowClrSrc, nCntCopyWord, bOpa );

							x += nCntCopyWord;
						}
						else
						{
							x += nCntCopyWord;
						}
					}
				}
				else
				{
					m_pddsBackBuffer->Unlock(NULL);
					return FALSE;
				}
			}
			// ������ ���� ���� ������ �������� �Ű��ش�.
			nWidthEnd++;

			nWidthStart	= nWidthEnd;
			nCurrWidth = 0;
		}
			
		m_pddsBackBuffer->Unlock(NULL);
		return TRUE;
	}
	return FALSE;
}


VOID CWHDXGraphicWindow::DrawWithShadowABlend(INT nX, INT nY, INT nXSize, INT nYSize, INT nPX, INT nPY, WORD* pwSrc, WORD wClipWidth, WORD wClipHeight,
											  WORD* pwShadowClrSrc, BOOL bBlend, BYTE bOpa)
{
	DDSURFACEDESC2	ddsd;

	// ȭ��(800*600)������ ��������ǥ�� �ƴ� ���� �߽��� ��ǥ(���� ���߾����̴�.)
	INT	  nScrnCenterX   = nX - nPX + 24;
	INT	  nScrnCenterY   = nY - nPY + 16;
	INT	  nRealCenterX   = nX - nScrnCenterX;
	INT	  nRealCenterY   = nY - nScrnCenterY;
	INT	  nShadowCenterX = nX;
	INT	  nShadowCenterY = nY-nRealCenterY/2;

	RECT  rcSrc		  = {0, 0, nXSize, nYSize};
	WORD wSahdowColor = pwShadowClrSrc[0];

	if ( m_pddsBackBuffer != NULL )
	{
		LONG	lWidth;
		ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
		ddsd.dwSize = sizeof(DDSURFACEDESC2);
		if ( FAILED(m_pddsBackBuffer->Lock(NULL, &ddsd, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL)) )
		{
			return;
		}

		WORD* pwdDst = (WORD*)ddsd.lpSurface;
		lWidth		 = ddsd.lPitch >> 1;

		if ( pwdDst )
		{
			INT nWidthStart	 = 0;
			INT nWidthEnd	 = 0;
			INT nCurrWidth   = 0;
			INT nLastWidth	 = 0;
			INT nCntCopyWord = 0;
			INT nYCnt		 = 0;

			INT nDstYPos = nShadowCenterY;

			for ( nYCnt = rcSrc.top ; nYCnt < rcSrc.bottom ; nYCnt++ )
			{
				if ( nDstYPos >= wClipHeight )
				{
					m_pddsBackBuffer->Unlock(NULL);
					return;
				}
				// y�� Ŭ���ι� ���پ� �ǳʶٱ�.
				if ( nYCnt%2 == 0 ||  nDstYPos < 0 )
				{
					nWidthEnd += pwSrc[nWidthStart];
					nWidthStart++;
					nWidthEnd++;
					nWidthStart	= nWidthEnd;

					nDstYPos++;
				}
				else
				{
					// �Ѷ����� ���̸� ���´�.(������ ����)
					nWidthEnd += pwSrc[nWidthStart];
					nWidthStart++;

					// ������ ���̸�ŭ ȭ�鿡 �ѷ��ش�.
					for ( INT x = nWidthStart; x < nWidthEnd ; )
					{
						if ( pwSrc[x] == 0xC0 )
						{		
							x++;
							nCntCopyWord = pwSrc[x];
							x++;
							nCurrWidth += nCntCopyWord;
						}
						else
						{
							x++;
							nCntCopyWord = pwSrc[x];
							x++;
							nLastWidth = nCurrWidth;
							nCurrWidth += nCntCopyWord;

							if ( bBlend )
							{
								if ((nShadowCenterX+nLastWidth+((-nRealCenterY/2)-nYCnt/2)) < 0 && (nShadowCenterX+nCurrWidth+((-nRealCenterY/2)-nYCnt/2)) >= 0 )
								{
								}
								else if ((nShadowCenterX+nLastWidth+((-nRealCenterY/2)-nYCnt/2)) < wClipWidth && (nShadowCenterX+nCurrWidth+((-nRealCenterY/2)-nYCnt/2)) >= wClipWidth )
								{
								}
								else if ( (nShadowCenterX+nCurrWidth+((-nRealCenterY/2)-nYCnt/2)) < 0 )
								{
								}
								else if ( (nShadowCenterX+nCurrWidth+((-nRealCenterY/2)-nYCnt/2)) >= wClipWidth )
								{
								}
								else
								{
									putAlpha32( &pwdDst[nDstYPos*lWidth + (nShadowCenterX+nLastWidth+((-nRealCenterY/2)-nYCnt/2))], pwShadowClrSrc, nCntCopyWord, bOpa );
								}
							}
							else
							{
								if ((nShadowCenterX+nLastWidth+((-nRealCenterY/2)-nYCnt/2)) < 0 && (nShadowCenterX+nCurrWidth+((-nRealCenterY/2)-nYCnt/2)) >= 0 )
								{
								}
								else if ((nShadowCenterX+nLastWidth+((-nRealCenterY/2)-nYCnt/2)) < wClipWidth && (nShadowCenterX+nCurrWidth+((-nRealCenterY/2)-nYCnt/2)) >= wClipWidth )
								{
								}
								else if ( (nShadowCenterX+nCurrWidth+((-nRealCenterY/2)-nYCnt/2)) < 0 )
								{
								}
								else if ( (nShadowCenterX+nCurrWidth+((-nRealCenterY/2)-nYCnt/2)) >= wClipWidth )
								{
								}
								else
								{
									memcpy(&pwdDst[nDstYPos*lWidth + (nShadowCenterX+nLastWidth+((-nRealCenterY/2)-nYCnt/2))], pwShadowClrSrc, sizeof(WORD)*nCntCopyWord);
								}
							}
							x += nCntCopyWord;
						}
					}
					// ������ ���� ���� ������ �������� �Ű��ش�.
					nWidthEnd++;

					nWidthStart	= nWidthEnd;
					nCurrWidth = 0;
				}
			}
			m_pddsBackBuffer->Unlock(NULL);
		}
	}
}


BOOL CWHDXGraphicWindow::DrawWithABlendCompDataWithLightedColor(INT nX, INT nY, 
															    INT nXSize, INT nYSize, WORD* pwSrc,
															    WORD wClipWidth, WORD wClipHeight,
															    WORD wChooseColor1, WORD wChooseColor2)
{
	RECT			rc;
	DDSURFACEDESC2	ddsd;

	INT	nWidth		= nXSize;
	INT	nHeight		= nYSize;
	INT	nXOffset	= 0;
	INT	nYOffset	= 0;
	INT	nStartX		= 0;
	INT	nStartY		= 0;
	INT	nEndX		= wClipWidth -1;
	INT	nEndY		= wClipHeight-1;

	FLOAT fBright = 0.5f;

	if ( m_pddsBackBuffer != NULL )
	{
		if (nX < nStartX )
		{ 
			nXOffset	= nStartX - nX;
			nWidth		= nXSize - nXOffset;
		}
		if ( (nX+nXSize-1) > nEndX )
			nWidth		= nEndX - nX - nXOffset + 1;		
		if ( nY < nStartY )	
		{ 
			nYOffset	= nStartY - nY;
			nHeight		= nYSize - nYOffset;
		}		
		if ( (nY+nYSize-1) > nEndY )
			nHeight	= nEndY - nY - nYOffset + 1;

		if ( (nWidth > 0) && (nHeight > 0) )
		{
			rc.left		= nXOffset;
			rc.right	= nXOffset+nWidth;
			rc.top		= nYOffset;
			rc.bottom	= nYOffset+nHeight;

			LONG	lWidth;
			ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
			ddsd.dwSize = sizeof(DDSURFACEDESC2);
			if ( FAILED(m_pddsBackBuffer->Lock(NULL, &ddsd, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL)) )
			{
				return FALSE;
			}

			WORD* pwdDst = (WORD*)ddsd.lpSurface;
			lWidth		 = ddsd.lPitch >> 1;

			INT nWidthStart	= 0;
			INT nWidthEnd	= 0;
			INT nCurrWidth  = 0;
			INT nCntCopyWord = 0;
			INT nYCnt =0;
			INT nLastWidth = 0;

			BYTE  bRedWantedColor, bGreenWantedColor, bBlueWantedColor;
			BYTE bRedSrc, bGreenSrc, bBlueSrc;
			WORD wPixel;
			WORD wDyingKind, wChooseColor;
			FLOAT rBlueRate, rGreenRate, bRedRate;

			// y�� Ŭ����.
  			for ( nYCnt=0 ; nYCnt < rc.top ; nYCnt++ )
			{
				nWidthEnd += pwSrc[nWidthStart];
				nWidthStart++;
				nWidthEnd++;
				nWidthStart	= nWidthEnd;
			}

			// y�࿡ ���ؼ� ������ ���ν�ų Count���� ���Ѵ�.
			for ( nYCnt=rc.top ; nYCnt < rc.bottom ; nYCnt++ )
			{
				// �Ѷ����� ���̸� ���´�.(������ ����)
				nWidthEnd += pwSrc[nWidthStart];
				nWidthStart++;

				// ������ ���̸�ŭ ȭ�鿡 �ѷ��ش�.
				for ( INT x = nWidthStart; x < nWidthEnd ; )
				{
					if ( pwSrc[x] == 0xC0 )
					{
						x++;
						nCntCopyWord = pwSrc[x];
						x++;
						nCurrWidth += nCntCopyWord;
					}
					else if ( pwSrc[x] == 0xC1 )
					{
						x++;
						nCntCopyWord = pwSrc[x];
						x++;

						nLastWidth = nCurrWidth;
						nCurrWidth += nCntCopyWord;

						if ( rc.left > nCurrWidth || rc.right < nLastWidth )
						{
							x += nCntCopyWord;
						}
						else
						{
							// rc.left���� �������� ī���� ������ �ɸ� ���.
							if ( nLastWidth < rc.left && rc.left <= nCurrWidth )
							{
								x += (rc.left-nLastWidth);
								for ( INT nCheck = 0; nCheck < nCurrWidth-rc.left; nCheck++ )
								{
									wPixel = pwSrc[x+nCheck];
									bBlueSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenSrc = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
									rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
									bRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

									bBlueSrc = (BYTE)((FLOAT)bBlueSrc + ((FLOAT)bBlueSrc*rBlueRate*fBright));
									bGreenSrc = (BYTE)((FLOAT)bGreenSrc + ((FLOAT)bGreenSrc*rGreenRate*fBright));
									bRedSrc = (BYTE)((FLOAT)bRedSrc + ((FLOAT)bRedSrc*bRedRate*fBright));

									if ( bBlueSrc > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
										bBlueSrc = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
									if ( bGreenSrc > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
										bGreenSrc = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
									if ( bRedSrc > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
										bRedSrc = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);

									if ( ((nYCnt+nY) * lWidth) + (nLastWidth+nX+nCheck) < 0 )
										return FALSE;

									pwdDst[((nYCnt+nY) * lWidth) + (rc.left+nX+nCheck)] = ((bBlueSrc <<m_stBitsMaskInfo.bBShift) |
																						   (bGreenSrc<<m_stBitsMaskInfo.bGShift) |
																						   (bRedSrc  <<m_stBitsMaskInfo.bRShift));			
								}
								x += (nCurrWidth-rc.left);
							}
							// rc.right���� �������� ī���� ������ �ɸ� ���.
							else if ( nLastWidth <= rc.right && rc.right < nCurrWidth )
							{
								for ( INT nCheck = 0; nCheck < rc.right-nLastWidth; nCheck++ )
								{
									wPixel = pwSrc[x+nCheck];
									bBlueSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenSrc = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
									rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
									bRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

									bBlueSrc = (BYTE)((FLOAT)bBlueSrc + ((FLOAT)bBlueSrc*rBlueRate*fBright));
									bGreenSrc = (BYTE)((FLOAT)bGreenSrc + ((FLOAT)bGreenSrc*rGreenRate*fBright));
									bRedSrc = (BYTE)((FLOAT)bRedSrc + ((FLOAT)bRedSrc*bRedRate*fBright));

									if ( bBlueSrc > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
										bBlueSrc = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
									if ( bGreenSrc > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
										bGreenSrc = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
									if ( bRedSrc > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
										bRedSrc = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);

									pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX+nCheck)] = ((bBlueSrc <<m_stBitsMaskInfo.bBShift) |
																						      (bGreenSrc<<m_stBitsMaskInfo.bGShift) |
																							  (bRedSrc  <<m_stBitsMaskInfo.bRShift));			
								}
								x += nCntCopyWord;
							}
							else
							{
								for ( INT nCheck = 0; nCheck < nCntCopyWord; nCheck++ )
								{
									wPixel = pwSrc[x+nCheck];
									bBlueSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenSrc = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
									rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
									bRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

									bBlueSrc = (BYTE)((FLOAT)bBlueSrc + ((FLOAT)bBlueSrc*rBlueRate*fBright));
									bGreenSrc = (BYTE)((FLOAT)bGreenSrc + ((FLOAT)bGreenSrc*rGreenRate*fBright));
									bRedSrc = (BYTE)((FLOAT)bRedSrc + ((FLOAT)bRedSrc*bRedRate*fBright));

									if ( bBlueSrc > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
										bBlueSrc = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
									if ( bGreenSrc > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
										bGreenSrc = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
									if ( bRedSrc > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
										bRedSrc = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);

									pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX+nCheck)] = ((bBlueSrc <<m_stBitsMaskInfo.bBShift) |
																						      (bGreenSrc<<m_stBitsMaskInfo.bGShift) |
																							  (bRedSrc  <<m_stBitsMaskInfo.bRShift));			
								}
								x += nCntCopyWord;
							}
						}
					}
					else if ( pwSrc[x] == 0xC2 || pwSrc[x] == 0xC3 )
					{
						wDyingKind = pwSrc[x];
						switch ( wDyingKind )
						{
						case 0xC2: 
							wChooseColor = wChooseColor1;
							break;
						case 0xC3: 
							wChooseColor = wChooseColor2;
							break;
						}
						x++;
						nCntCopyWord = pwSrc[x];
						x++;

						nLastWidth = nCurrWidth;
						nCurrWidth += nCntCopyWord;

						if ( rc.left > nCurrWidth || rc.right < nLastWidth )
						{
							x += nCntCopyWord;
						}
						else
						{
							// rc.left���� �������� ī���� ������ �ɸ� ���.
							if ( nLastWidth < rc.left && rc.left <= nCurrWidth )
							{
								x += (rc.left-nLastWidth);
								for ( INT nCheck = 0; nCheck < nCurrWidth-rc.left; nCheck++ )
								{
									wPixel	  = wChooseColor;
									bBlueWantedColor  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenWantedColor = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedWantedColor   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									wPixel	  = pwSrc[x+nCheck];
									bBlueSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenSrc = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
									rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
									bRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

									bBlueWantedColor = (BYTE)(((FLOAT)bBlueWantedColor*rBlueRate));
									bGreenWantedColor = (BYTE)(((FLOAT)bGreenWantedColor*rGreenRate));
									bRedWantedColor = (BYTE)(((FLOAT)bRedWantedColor*bRedRate));

									if ( bBlueWantedColor > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
										bBlueWantedColor = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
									if ( bGreenWantedColor > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
										bGreenWantedColor = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
									if ( bRedWantedColor > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
										bRedWantedColor = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);

									bBlueSrc = bBlueWantedColor;
									bGreenSrc = bGreenWantedColor;
									bRedSrc = bRedWantedColor;

									rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
									rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
									bRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

									bBlueSrc = (BYTE)((FLOAT)bBlueSrc + ((FLOAT)bBlueSrc*rBlueRate*fBright));
									bGreenSrc = (BYTE)((FLOAT)bGreenSrc + ((FLOAT)bGreenSrc*rGreenRate*fBright));
									bRedSrc = (BYTE)((FLOAT)bRedSrc + ((FLOAT)bRedSrc*bRedRate*fBright));

									if ( bBlueSrc > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
										bBlueSrc = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
									if ( bGreenSrc > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
										bGreenSrc = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
									if ( bRedSrc > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
										bRedSrc = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);

									if ( ((nYCnt+nY) * lWidth) + (rc.left+nX+nCheck) < 0 )
										return FALSE;

									pwdDst[((nYCnt+nY) * lWidth) + (rc.left+nX+nCheck)] = ((bBlueSrc <<m_stBitsMaskInfo.bBShift) |
																						   (bGreenSrc<<m_stBitsMaskInfo.bGShift) |
																						   (bRedSrc  <<m_stBitsMaskInfo.bRShift));			
								}
								x += (nCurrWidth-rc.left);
							}
							// rc.right���� �������� ī���� ������ �ɸ� ���.
							else if ( nLastWidth <= rc.right && rc.right < nCurrWidth )
							{
								for ( INT nCheck = 0; nCheck < rc.right-nLastWidth; nCheck++ )
								{
									wPixel	  = wChooseColor;
									bBlueWantedColor  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenWantedColor = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedWantedColor   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									wPixel	  = pwSrc[x+nCheck];
									bBlueSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenSrc = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
									rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
									bRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

									bBlueWantedColor = (BYTE)(((FLOAT)bBlueWantedColor*rBlueRate));
									bGreenWantedColor = (BYTE)(((FLOAT)bGreenWantedColor*rGreenRate));
									bRedWantedColor = (BYTE)(((FLOAT)bRedWantedColor*bRedRate));

									if ( bBlueWantedColor > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
										bBlueWantedColor = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
									if ( bGreenWantedColor > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
										bGreenWantedColor = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
									if ( bRedWantedColor > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
										bRedWantedColor = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);

									bBlueSrc = bBlueWantedColor;
									bGreenSrc = bGreenWantedColor;
									bRedSrc = bRedWantedColor;

									rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
									rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
									bRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

									bBlueSrc = (BYTE)((FLOAT)bBlueSrc + ((FLOAT)bBlueSrc*rBlueRate*fBright));
									bGreenSrc = (BYTE)((FLOAT)bGreenSrc + ((FLOAT)bGreenSrc*rGreenRate*fBright ));
									bRedSrc = (BYTE)((FLOAT)bRedSrc + ((FLOAT)bRedSrc*bRedRate*fBright));

									if ( bBlueSrc > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
										bBlueSrc = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
									if ( bGreenSrc > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
										bGreenSrc = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
									if ( bRedSrc > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
										bRedSrc = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);

									pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX+nCheck)] = ((bBlueSrc <<m_stBitsMaskInfo.bBShift) |
																						      (bGreenSrc<<m_stBitsMaskInfo.bGShift) |
																							  (bRedSrc  <<m_stBitsMaskInfo.bRShift));			
								}
								x += nCntCopyWord;
							}
							else
							{
								for ( INT nCheck = 0; nCheck < nCntCopyWord; nCheck++ )
								{
									wPixel	  = wChooseColor;
									bBlueWantedColor  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenWantedColor = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedWantedColor   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									wPixel	  = pwSrc[x+nCheck];
									bBlueSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenSrc = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
									rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
									bRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

									bBlueWantedColor = (BYTE)(((FLOAT)bBlueWantedColor*rBlueRate));
									bGreenWantedColor = (BYTE)(((FLOAT)bGreenWantedColor*rGreenRate));
									bRedWantedColor = (BYTE)(((FLOAT)bRedWantedColor*bRedRate));

									if ( bBlueWantedColor > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
										bBlueWantedColor = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
									if ( bGreenWantedColor > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
										bGreenWantedColor = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
									if ( bRedWantedColor > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
										bRedWantedColor = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);

									bBlueSrc = bBlueWantedColor;
									bGreenSrc = bGreenWantedColor;
									bRedSrc = bRedWantedColor;

									rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
									rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
									bRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

									bBlueSrc = (BYTE)((FLOAT)bBlueSrc + ((FLOAT)bBlueSrc*rBlueRate*fBright));
									bGreenSrc = (BYTE)((FLOAT)bGreenSrc + ((FLOAT)bGreenSrc*rGreenRate*fBright));
									bRedSrc = (BYTE)((FLOAT)bRedSrc + ((FLOAT)bRedSrc*bRedRate*fBright));

									if ( bBlueSrc > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
										bBlueSrc = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
									if ( bGreenSrc > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
										bGreenSrc = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
									if ( bRedSrc > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
										bRedSrc = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);

									pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX+nCheck)] = ((bBlueSrc <<m_stBitsMaskInfo.bBShift) |
																						      (bGreenSrc<<m_stBitsMaskInfo.bGShift) |
																							  (bRedSrc  <<m_stBitsMaskInfo.bRShift));			
								}
								x += nCntCopyWord;
							}
						}
					}	
					else
					{
						m_pddsBackBuffer->Unlock(NULL);
						return FALSE;
					}
				}
				// ������ ���� ���� ������ �������� �Ű��ش�.
				nWidthEnd++;

				nWidthStart	= nWidthEnd;
				nCurrWidth = 0;
			}
		}

		m_pddsBackBuffer->Unlock(NULL);
		return TRUE;
	}
	return FALSE;
}



BOOL CWHDXGraphicWindow::DrawWithImageForCompClipRgnColor(INT nX, INT nY, INT nXSize, INT nYSize, WORD* pwSrc, WORD wClipWidth, WORD wClipHeight, WORD wColor, BOOL bFocused, BOOL bBlend)
{
	RECT			rc;
	DDSURFACEDESC2	ddsd;

	INT	nWidth		= nXSize;
	INT	nHeight		= nYSize;
	INT	nXOffset	= 0;
	INT	nYOffset	= 0;
	INT	nStartX		= 0;
	INT	nStartY		= 0;
	INT	nEndX		= wClipWidth -1;
	INT	nEndY		= wClipHeight-1;

	if ( m_pddsBackBuffer != NULL )
	{
		if (nX < nStartX )
		{ 
			nXOffset	= nStartX - nX;
			nWidth		= nXSize - nXOffset;
		}
		if ( (nX+nXSize-1) > nEndX )
			nWidth		= nEndX - nX - nXOffset + 1;		
		if ( nY < nStartY )	
		{ 
			nYOffset	= nStartY - nY;
			nHeight		= nYSize - nYOffset;
		}		
		if ( (nY+nYSize-1) > nEndY )
			nHeight	= nEndY - nY - nYOffset + 1;

		if ( (nWidth > 0) && (nHeight > 0) )
		{
			rc.left		= nXOffset;
			rc.right	= nXOffset+nWidth;
			rc.top		= nYOffset;
			rc.bottom	= nYOffset+nHeight;

			LONG	lWidth;
			ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
			ddsd.dwSize = sizeof(DDSURFACEDESC2);
			if ( FAILED(m_pddsBackBuffer->Lock(NULL, &ddsd, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL)) )
			{
				return FALSE;
			}

			WORD* pwdDst = (WORD*)ddsd.lpSurface;
			lWidth		 = ddsd.lPitch >> 1;

			INT nWidthStart	= 0;
			INT nWidthEnd	= 0;
			INT nCurrWidth  = 0;
			INT nCntCopyWord = 0;
			INT nYCnt =0;
			INT nLastWidth = 0;

			BYTE  bRedStateColor,  bGreenStateColor,  bBlueStateColor;
			BYTE  bRedSrc, bGreenSrc, bBlueSrc;
			BYTE  bBlueDst, bGreenDst, bRedDst;
			WORD  wPixel;
			FLOAT rBlueRate, rGreenRate, rRedRate;
			FLOAT rbLightRate = 0.0f;

			// y�� Ŭ����.
  			for ( nYCnt=0 ; nYCnt < rc.top ; nYCnt++ )
			{
				nWidthEnd += pwSrc[nWidthStart];
				nWidthStart++;
				nWidthEnd++;
				nWidthStart	= nWidthEnd;
			}

			// y�࿡ ���ؼ� ������ ���ν�ų Count���� ���Ѵ�.
			for ( nYCnt=rc.top ; nYCnt < rc.bottom ; nYCnt++ )
			{
				// �Ѷ����� ���̸� ���´�.(������ ����)
				nWidthEnd += pwSrc[nWidthStart];
				nWidthStart++;

				// ������ ���̸�ŭ ȭ�鿡 �ѷ��ش�.
				for ( INT x = nWidthStart; x < nWidthEnd ; )
				{
					if ( pwSrc[x] == 0xC0 )
					{
						x++;
						nCntCopyWord = pwSrc[x];
						x++;
						nCurrWidth += nCntCopyWord;
					}
					else if ( pwSrc[x] == 0xC1 || pwSrc[x] == 0xC2 || pwSrc[x] == 0xC3 )
					{
						x++;
						nCntCopyWord = pwSrc[x];
						x++;

						nLastWidth = nCurrWidth;
						nCurrWidth += nCntCopyWord;

						if ( rc.left > nCurrWidth || rc.right < nLastWidth )
						{
							x += nCntCopyWord;
						}
						else
						{
							// rc.left���� �������� ī���� ������ �ɸ� ���.
							if ( nLastWidth < rc.left && rc.left <= nCurrWidth )
							{
								x += (rc.left-nLastWidth);
								for ( INT nCheck = 0; nCheck < nCurrWidth-rc.left; nCheck++ )
								{
									wPixel = wColor;
									bBlueStateColor  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenStateColor = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedStateColor   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									wPixel = pwSrc[x+nCheck];
									bBlueSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenSrc = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									// Focus����.
									if ( bFocused )			rbLightRate = 0.6f;
									else					rbLightRate = 0.0f;

									if ( !wColor )	
									{
										BYTE bTemp = (BYTE)(bBlueSrc+(bGreenSrc>>1)+bRedSrc)/3;
										bTemp = bTemp + (BYTE)(bTemp*rbLightRate);
										if ( bTemp > 31 )	bTemp = 31;
										bBlueStateColor = bRedStateColor = bTemp;
										bGreenStateColor = bTemp<<1;
									}
									else
									{
										rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
										rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
										rRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

										bBlueStateColor  = ( (BYTE)((FLOAT)bBlueStateColor *rBlueRate ) + (BYTE)((FLOAT)bBlueStateColor *rBlueRate *rbLightRate) );
										bGreenStateColor = ( (BYTE)((FLOAT)bGreenStateColor*rGreenRate) + (BYTE)((FLOAT)bGreenStateColor*rGreenRate*rbLightRate) );
										bRedStateColor   = ( (BYTE)((FLOAT)bRedStateColor  *rRedRate  ) + (BYTE)((FLOAT)bRedStateColor  *rRedRate  *rbLightRate) );					

										if ( bBlueStateColor > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
											bBlueStateColor = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
										if ( bGreenStateColor > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
											bGreenStateColor = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
										if ( bRedStateColor > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
											bRedStateColor = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);
									}

									if ( bBlend )
									{
										wPixel	   = pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX+nCheck)];
										bBlueDst   = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
										bGreenDst  = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
										bRedDst    = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

										bBlueDst   = (BYTE)((50*(bBlueDst -bBlueStateColor )+100*bBlueStateColor  ) / 100);
										bGreenDst  = (BYTE)((50*(bGreenDst-bGreenStateColor)+100*bGreenStateColor ) / 100);
										bRedDst    = (BYTE)((50*(bRedDst  -bRedStateColor  )+100*bRedStateColor   ) / 100);
									}
									else
									{
										bBlueDst   = bBlueStateColor;
										bGreenDst  = bGreenStateColor;
										bRedDst    = bRedStateColor;
									}

									if ( ((nYCnt+nY) * lWidth) + (rc.left+nX+nCheck) < 0 )
										return FALSE;

									pwdDst[((nYCnt+nY) * lWidth) + (rc.left+nX+nCheck)] = ((bBlueDst <<m_stBitsMaskInfo.bBShift) |
																									   (bGreenDst<<m_stBitsMaskInfo.bGShift) |
																									   (bRedDst  <<m_stBitsMaskInfo.bRShift));			
								}
								x += (nCurrWidth-rc.left);
							}
							// rc.right���� �������� ī���� ������ �ɸ� ���.
							else if ( nLastWidth <= rc.right && rc.right < nCurrWidth )
							{
								for ( INT nCheck = 0; nCheck < rc.right-nLastWidth; nCheck++ )
								{
									wPixel = wColor;
									bBlueStateColor  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenStateColor = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedStateColor   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									wPixel = pwSrc[x+nCheck];
									bBlueSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenSrc = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									// Focus����.
									if ( bFocused )			rbLightRate = 0.6f;
									else					rbLightRate = 0.0f;

									if ( !wColor )	
									{
										BYTE bTemp = (BYTE)(bBlueSrc+(bGreenSrc>>1)+bRedSrc)/3;
										bTemp = bTemp + (BYTE)(bTemp*rbLightRate);
										if ( bTemp > 31 )	bTemp = 31;
										bBlueStateColor = bRedStateColor = bTemp;
										bGreenStateColor = bTemp<<1;
									}
									else
									{
										rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
										rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
										rRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

										bBlueStateColor  = ( (BYTE)((FLOAT)bBlueStateColor *rBlueRate ) + (BYTE)((FLOAT)bBlueStateColor *rBlueRate *rbLightRate) );
										bGreenStateColor = ( (BYTE)((FLOAT)bGreenStateColor*rGreenRate) + (BYTE)((FLOAT)bGreenStateColor*rGreenRate*rbLightRate) );
										bRedStateColor   = ( (BYTE)((FLOAT)bRedStateColor  *rRedRate  ) + (BYTE)((FLOAT)bRedStateColor  *rRedRate  *rbLightRate) );					

										if ( bBlueStateColor > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
											bBlueStateColor = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
										if ( bGreenStateColor > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
											bGreenStateColor = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
										if ( bRedStateColor > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
											bRedStateColor = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);
									}

									if ( bBlend )
									{
										wPixel	   = pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX+nCheck)];
										bBlueDst   = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
										bGreenDst  = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
										bRedDst    = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

										bBlueDst   = (BYTE)((50*(bBlueDst -bBlueStateColor )+100*bBlueStateColor  ) / 100);
										bGreenDst  = (BYTE)((50*(bGreenDst-bGreenStateColor)+100*bGreenStateColor ) / 100);
										bRedDst    = (BYTE)((50*(bRedDst  -bRedStateColor  )+100*bRedStateColor   ) / 100);
									}
									else
									{
										bBlueDst   = bBlueStateColor;
										bGreenDst  = bGreenStateColor;
										bRedDst    = bRedStateColor;
									}

									pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX+nCheck)] = ((bBlueDst <<m_stBitsMaskInfo.bRShift) |
																									      (bGreenDst<<m_stBitsMaskInfo.bGShift) |
																										  (bRedDst  <<m_stBitsMaskInfo.bBShift));			
								}
								x += nCntCopyWord;
							}
							else
							{
								for ( INT nCheck = 0; nCheck < nCntCopyWord; nCheck++ )
								{
									wPixel = wColor;
									bBlueStateColor  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenStateColor = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedStateColor   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									wPixel = pwSrc[x+nCheck];
									bBlueSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenSrc = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									// Focus����.
									if ( bFocused )			rbLightRate = 0.6f;
									else					rbLightRate = 0.0f;

									if ( !wColor )	
									{
										BYTE bTemp = (BYTE)(bBlueSrc+(bGreenSrc>>1)+bRedSrc)/3;
										bTemp = bTemp + (BYTE)(bTemp*rbLightRate);
										if ( bTemp > 31 )	bTemp = 31;
										bBlueStateColor = bRedStateColor = bTemp;
										bGreenStateColor = bTemp<<1;
									}
									else
									{
										rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
										rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
										rRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

										bBlueStateColor  = ( (BYTE)((FLOAT)bBlueStateColor *rBlueRate ) + (BYTE)((FLOAT)bBlueStateColor *rBlueRate *rbLightRate) );
										bGreenStateColor = ( (BYTE)((FLOAT)bGreenStateColor*rGreenRate) + (BYTE)((FLOAT)bGreenStateColor*rGreenRate*rbLightRate) );
										bRedStateColor   = ( (BYTE)((FLOAT)bRedStateColor  *rRedRate  ) + (BYTE)((FLOAT)bRedStateColor  *rRedRate  *rbLightRate) );					

										if ( bBlueStateColor > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
											bBlueStateColor = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
										if ( bGreenStateColor > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
											bGreenStateColor = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
										if ( bRedStateColor > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
											bRedStateColor = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);
									}

									if ( bBlend )
									{
										wPixel	   = pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX+nCheck)];
										bBlueDst   = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
										bGreenDst  = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
										bRedDst    = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

										bBlueDst   = (BYTE)((50*(bBlueDst -bBlueStateColor )+100*bBlueStateColor  ) / 100);
										bGreenDst  = (BYTE)((50*(bGreenDst-bGreenStateColor)+100*bGreenStateColor ) / 100);
										bRedDst    = (BYTE)((50*(bRedDst  -bRedStateColor  )+100*bRedStateColor   ) / 100);
									}
									else
									{
										bBlueDst   = bBlueStateColor;
										bGreenDst  = bGreenStateColor;
										bRedDst    = bRedStateColor;
									}

									pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX+nCheck)] = ((bBlueDst <<m_stBitsMaskInfo.bBShift) |
																									      (bGreenDst<<m_stBitsMaskInfo.bGShift) |
																										  (bRedDst  <<m_stBitsMaskInfo.bRShift));			
								}
								x += nCntCopyWord;
							}
						}
					}
					else
					{
						m_pddsBackBuffer->Unlock(NULL);
						return FALSE;
					}
				}
				// ������ ���� ���� ������ �������� �Ű��ش�.
				nWidthEnd++;

				nWidthStart	= nWidthEnd;
				nCurrWidth = 0;
			}
		}

		m_pddsBackBuffer->Unlock(NULL);
		return TRUE;
	}
	return FALSE;
}



BOOL CWHDXGraphicWindow::DrawWithImageForCompClipRgnColor(INT nX, INT nY, INT nXSize, INT nYSize, WORD* pwSrc, WORD wClipWidth, WORD wClipHeight,WORD wColor , WORD wChooseColor1, WORD wChooseColor2)
{
	RECT			rc;
	DDSURFACEDESC2	ddsd;

	INT	nWidth		= nXSize;
	INT	nHeight		= nYSize;
	INT	nXOffset	= 0;
	INT	nYOffset	= 0;
	INT	nStartX		= 0;
	INT	nStartY		= 0;
	INT	nEndX		= wClipWidth -1;
	INT	nEndY		= wClipHeight-1;

	INT FiveMiddle	= 0xf;
	INT SixMiddle	= 0x1f;

	BYTE bsBlueColor,bsGreenColor,bsRedColor;
	BYTE bdBlueColor,bdGreenColor,bdRedColor;

	bdBlueColor  = (BYTE)((wColor & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
	bdGreenColor = (BYTE)((wColor & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
	bdRedColor   = (BYTE)((wColor & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

	if ( m_pddsBackBuffer != NULL )
	{
		if (nX < nStartX )
		{ 
			nXOffset	= nStartX - nX;
			nWidth		= nXSize - nXOffset;
		}
		if ( (nX+nXSize-1) > nEndX )
			nWidth		= nEndX - nX - nXOffset + 1;		
		if ( nY < nStartY )	
		{ 
			nYOffset	= nStartY - nY;
			nHeight		= nYSize - nYOffset;
		}		
		if ( (nY+nYSize-1) > nEndY )
			nHeight	= nEndY - nY - nYOffset + 1;

		if ( (nWidth > 0) && (nHeight > 0) )
		{
			rc.left		= nXOffset;
			rc.right	= nXOffset+nWidth;
			rc.top		= nYOffset;
			rc.bottom	= nYOffset+nHeight;

			LONG	lWidth;
			ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
			ddsd.dwSize = sizeof(DDSURFACEDESC2);
			if ( FAILED(m_pddsBackBuffer->Lock(NULL, &ddsd, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL)) )
			{
				return FALSE;
			}

			WORD* pwdDst = (WORD*)ddsd.lpSurface;
			lWidth		 = ddsd.lPitch >> 1;

			INT nWidthStart	= 0;
			INT nWidthEnd	= 0;
			INT nCurrWidth  = 0;
			INT nCntCopyWord = 0;
			INT nYCnt =0;
			INT nLastWidth = 0;

			FLOAT rBlueRate, rGreenRate, bRedRate;
			BYTE  bRedSrc, bGreenSrc, bBlueSrc;
			BYTE  bRedWantedColor, bGreenWantedColor, bBlueWantedColor;
			WORD  wPixel;

			// y�� Ŭ����.
			for ( nYCnt=0 ; nYCnt < rc.top ; nYCnt++ )
			{
				nWidthEnd += pwSrc[nWidthStart];
				nWidthStart++;
				nWidthEnd++;
				nWidthStart	= nWidthEnd;
			}

			// y�࿡ ���ؼ� ������ ���ν�ų Count���� ���Ѵ�.
			for ( nYCnt=rc.top ; nYCnt < rc.bottom ; nYCnt++ )
			{
				// �Ѷ����� ���̸� ���´�.(������ ����)
				nWidthEnd += pwSrc[nWidthStart];
				nWidthStart++;

				// ������ ���̸�ŭ ȭ�鿡 �ѷ��ش�.
				for ( INT x = nWidthStart; x < nWidthEnd ; )
				{
					if ( pwSrc[x] == 0xC0 )
					{
						x++;
						nCntCopyWord = pwSrc[x];
						x++;
						nCurrWidth += nCntCopyWord;
					}
					else if ( pwSrc[x] == 0xC1 )
					{
						x++;
						nCntCopyWord = pwSrc[x];	// ����
						x++;

						nLastWidth = nCurrWidth;
						nCurrWidth += nCntCopyWord;

						if ( rc.left > nCurrWidth || rc.right < nLastWidth )
						{
							x += nCntCopyWord;		// ���� ���� ���� ���
						}
						else
						{
							// rc.left���� �������� ī���� ������ �ɸ� ���.
							if ( nLastWidth < rc.left && rc.left <= nCurrWidth )
							{
								x += (rc.left-nLastWidth);

								for(WORD i = 0 ; i < (sizeof(WORD)*(nCurrWidth-rc.left)/2);i++)
								{
									bsBlueColor  = (BYTE)((pwSrc[x+i] & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bsGreenColor = (BYTE)((pwSrc[x+i] & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bsRedColor   = (BYTE)((pwSrc[x+i] & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									BYTE	temp;

									temp = (bsRedColor+(bsGreenColor>>1)+bsBlueColor)/3;

									bsBlueColor = temp>0 ? (temp&bdBlueColor) : 0;
									bsGreenColor = temp>0 ? (temp&(bdGreenColor<<1)) : 0;
									bsRedColor = temp>0 ? (temp&bdRedColor) :  0;

									if ( bsBlueColor >= 32 )  bsBlueColor = 31;
									if ( bsGreenColor >= 64 )  bsGreenColor = 63;
									if ( bsRedColor >= 32 )  bsRedColor = 31;

									if ( ((nYCnt+nY) * lWidth) + (rc.left+nX) + i < 0 )
										return FALSE;

									pwdDst[((nYCnt+nY) * lWidth) + (rc.left+nX) + i] = (bsBlueColor<<m_stBitsMaskInfo.bBShift) |  (bsGreenColor<<m_stBitsMaskInfo.bGShift) | (bsRedColor<<m_stBitsMaskInfo.bRShift);
								}

								x += (nCurrWidth-rc.left);
							}
							// rc.right���� �������� ī���� ������ �ɸ� ���.
							else if ( nLastWidth <= rc.right && rc.right < nCurrWidth )
							{
								for(WORD i = 0 ; i < (sizeof(WORD)*(rc.right-nLastWidth));i++)
								{
									bsBlueColor  = (BYTE)((pwSrc[x+i] & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bsGreenColor = (BYTE)((pwSrc[x+i] & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bsRedColor   = (BYTE)((pwSrc[x+i] & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);
									
									BYTE	temp;

									temp = (bsRedColor+(bsGreenColor>>1)+bsBlueColor)/3;

									bsBlueColor = temp>0 ? (temp&bdBlueColor) : 0;
									bsGreenColor = temp>0 ? (temp&(bdGreenColor<<1)) : 0;
									bsRedColor = temp>0 ? (temp&bdRedColor) :  0;

									if ( bsBlueColor >= 32 )  bsBlueColor = 31;
									if ( bsGreenColor >= 64 )  bsGreenColor = 63;
									if ( bsRedColor >= 32 )  bsRedColor = 31;
									
									pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX) + i] = (bsBlueColor<<m_stBitsMaskInfo.bBShift) |  (bsGreenColor<<m_stBitsMaskInfo.bGShift) | (bsRedColor<<m_stBitsMaskInfo.bRShift);
								}
//								memcpy(&pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX)], &pwSrc[x], sizeof(WORD)*(rc.right-nLastWidth));
								x += nCntCopyWord;
							}
							else
							{
								for(WORD i = 0 ; i < (sizeof(WORD)*nCntCopyWord/2);i++)
								{
									bsBlueColor  = (BYTE)((pwSrc[x+i] & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bsGreenColor = (BYTE)((pwSrc[x+i] & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bsRedColor   = (BYTE)((pwSrc[x+i] & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									BYTE	temp;

									temp = (bsRedColor+(bsGreenColor>>1)+bsBlueColor)/3;

									bsBlueColor = temp>0 ? (temp&bdBlueColor) : 0;
									bsGreenColor = temp>0 ? (temp&(bdGreenColor<<1)) : 0;
									bsRedColor = temp>0 ? (temp&bdRedColor) :  0;

									if ( bsBlueColor >= 32 )  bsBlueColor = 31;
									if ( bsGreenColor >= 64 )  bsGreenColor = 63;
									if ( bsRedColor >= 32 )  bsRedColor = 31;

									pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX) + i] = (bsBlueColor<<m_stBitsMaskInfo.bBShift) |  (bsGreenColor<<m_stBitsMaskInfo.bGShift) | (bsRedColor<<m_stBitsMaskInfo.bRShift);
								}
								x += nCntCopyWord;
							}
						}
					}
					else if ( pwSrc[x] == 0xC2 || pwSrc[x] == 0xC3 )
					{
						WORD wDyingKind, wChooseColor;
						wDyingKind = pwSrc[x];
						switch ( wDyingKind )
						{
						case 0xC2: 
							wChooseColor = wChooseColor1;
							break;
						case 0xC3: 
							wChooseColor = wChooseColor2;
							break;
						}
						x++;
						nCntCopyWord = pwSrc[x];
						x++;

						nLastWidth = nCurrWidth;
						nCurrWidth += nCntCopyWord;

						if ( rc.left > nCurrWidth || rc.right < nLastWidth )
						{
							x += nCntCopyWord;
						}
						else
						{
							// rc.left���� �������� ī���� ������ �ɸ� ���.
							if ( nLastWidth < rc.left && rc.left <= nCurrWidth )
							{
								x += (rc.left-nLastWidth);
								for ( INT nCheck = 0; nCheck < nCurrWidth-rc.left; nCheck++ )
								{
									wPixel	  = wChooseColor;
									bBlueWantedColor  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenWantedColor = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedWantedColor   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									wPixel	  = pwSrc[x+nCheck];
									bBlueSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenSrc = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
									rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
									bRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

									bBlueWantedColor = (BYTE)(((FLOAT)bBlueWantedColor*rBlueRate));
									bGreenWantedColor = (BYTE)(((FLOAT)bGreenWantedColor*rGreenRate));
									bRedWantedColor = (BYTE)(((FLOAT)bRedWantedColor*bRedRate));

									if ( bBlueWantedColor > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
										bBlueWantedColor = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
									if ( bGreenWantedColor > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
										bGreenWantedColor = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
									if ( bRedWantedColor > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
										bRedWantedColor = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);

									BYTE	temp;

									temp = (bsRedColor+(bGreenWantedColor>>1)+bBlueWantedColor)/3;

									bBlueWantedColor = temp>0 ? (temp&bdBlueColor) : 0;
									bGreenWantedColor = temp>0 ? (temp&(bdGreenColor<<1)) : 0;
									bRedWantedColor = temp>0 ? (temp&bdRedColor) :  0;

									if ( bBlueWantedColor >= 32 )  bBlueWantedColor = 31;
									if ( bGreenWantedColor >= 64 )  bGreenWantedColor = 63;
									if ( bRedWantedColor >= 32 )  bRedWantedColor = 31;

									if ( ((nYCnt+nY) * lWidth) + (nLastWidth+nX+nCheck) < 0 )
										return FALSE;

									pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX+nCheck)] = ((bRedWantedColor  <<m_stBitsMaskInfo.bRShift) |
																										  (bGreenWantedColor<<m_stBitsMaskInfo.bGShift) |
																										  (bBlueWantedColor <<m_stBitsMaskInfo.bBShift));			
								}
								x += (nCurrWidth-rc.left);
							}
							// rc.right���� �������� ī���� ������ �ɸ� ���.
							else if ( nLastWidth <= rc.right && rc.right < nCurrWidth )
							{
								for ( INT nCheck = 0; nCheck < rc.right-nLastWidth; nCheck++ )
								{
									wPixel	  = wChooseColor;
									bBlueWantedColor  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenWantedColor = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedWantedColor   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									wPixel	  = pwSrc[x+nCheck];
									bBlueSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenSrc = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
									rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
									bRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

									bBlueWantedColor = (BYTE)(((FLOAT)bBlueWantedColor*rBlueRate));
									bGreenWantedColor = (BYTE)(((FLOAT)bGreenWantedColor*rGreenRate));
									bRedWantedColor = (BYTE)(((FLOAT)bRedWantedColor*bRedRate));

									if ( bBlueWantedColor > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
										bBlueWantedColor = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
									if ( bGreenWantedColor > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
										bGreenWantedColor = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
									if ( bRedWantedColor > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
										bRedWantedColor = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);

									BYTE	temp;

									temp = (bsRedColor+(bGreenWantedColor>>1)+bBlueWantedColor)/3;

									bBlueWantedColor = temp>0 ? (temp&bdBlueColor) : 0;
									bGreenWantedColor = temp>0 ? (temp&(bdGreenColor<<1)) : 0;
									bRedWantedColor = temp>0 ? (temp&bdRedColor) :  0;

									if ( bBlueWantedColor >= 32 )  bBlueWantedColor = 31;
									if ( bGreenWantedColor >= 64 )  bGreenWantedColor = 63;
									if ( bRedWantedColor >= 32 )  bRedWantedColor = 31;

									pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX+nCheck)] = ((bRedWantedColor  <<m_stBitsMaskInfo.bRShift) |
																										  (bGreenWantedColor<<m_stBitsMaskInfo.bGShift) |
																										  (bBlueWantedColor <<m_stBitsMaskInfo.bBShift));			
								}
								x += nCntCopyWord;
							}
							else
							{
								for ( INT nCheck = 0; nCheck < nCntCopyWord; nCheck++ )
								{
									wPixel	  = wChooseColor;
									bBlueWantedColor  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenWantedColor = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedWantedColor   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									wPixel	  = pwSrc[x+nCheck];
									bBlueSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenSrc = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
									rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
									bRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

									bBlueWantedColor = (BYTE)(((FLOAT)bBlueWantedColor*rBlueRate));
									bGreenWantedColor = (BYTE)(((FLOAT)bGreenWantedColor*rGreenRate));
									bRedWantedColor = (BYTE)(((FLOAT)bRedWantedColor*bRedRate));

									if ( bBlueWantedColor > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
										bBlueWantedColor = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
									if ( bGreenWantedColor > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
										bGreenWantedColor = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
									if ( bRedWantedColor > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
										bRedWantedColor = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);

									BYTE	temp;

									temp = (bsRedColor+(bGreenWantedColor>>1)+bBlueWantedColor)/3;

									bBlueWantedColor = temp>0 ? (temp&bdBlueColor) : 0;
									bGreenWantedColor = temp>0 ? (temp&(bdGreenColor<<1)) : 0;
									bRedWantedColor = temp>0 ? (temp&bdRedColor) :  0;

									if ( bBlueWantedColor >= 32 )  bBlueWantedColor = 31;
									if ( bGreenWantedColor >= 64 )  bGreenWantedColor = 63;
									if ( bRedWantedColor >= 32 )  bRedWantedColor = 31;

									pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX+nCheck)] = ((bRedWantedColor  <<m_stBitsMaskInfo.bRShift) |
																										  (bGreenWantedColor<<m_stBitsMaskInfo.bGShift) |
																									 	  (bBlueWantedColor <<m_stBitsMaskInfo.bBShift));			
								}
								x += nCntCopyWord;
							}
						}
					}	
					else
					{
						m_pddsBackBuffer->Unlock(NULL);
						return FALSE;
					}
				}
				// ������ ���� ���� ������ �������� �Ű��ش�.
				nWidthEnd++;

				nWidthStart	= nWidthEnd;
				nCurrWidth = 0;
			}
		}

		m_pddsBackBuffer->Unlock(NULL);
		return TRUE;
	}
	return FALSE;
}



BOOL CWHDXGraphicWindow::DrawWithImageForCompClipRgnGray(INT nX, INT nY, INT nXSize, INT nYSize, WORD* pwSrc , WORD wClipWidth, WORD wClipHeight, WORD wChooseColor1, WORD wChooseColor2)
{
	RECT			rc;
	DDSURFACEDESC2	ddsd;

	INT	nWidth		= nXSize;
	INT	nHeight		= nYSize;
	INT	nXOffset	= 0;
	INT	nYOffset	= 0;
	INT	nStartX		= 0;
	INT	nStartY		= 0;
	INT	nEndX		= wClipWidth -1;
	INT	nEndY		= wClipHeight-1;

	INT FiveMiddle	= 0xf;
	INT SixMiddle	= 0x1f;

	BYTE bsBlueColor,bsGreenColor,bsRedColor;
	BYTE bdBlueColor,bdGreenColor,bdRedColor;

	bdBlueColor  = 0x0f;
	bdGreenColor = 0x1f;
	bdRedColor   = 0x0f;

	if ( m_pddsBackBuffer != NULL )
	{
		if (nX < nStartX )
		{ 
			nXOffset	= nStartX - nX;
			nWidth		= nXSize - nXOffset;
		}
		if ( (nX+nXSize-1) > nEndX )
			nWidth		= nEndX - nX - nXOffset + 1;		
		if ( nY < nStartY )	
		{ 
			nYOffset	= nStartY - nY;
			nHeight		= nYSize - nYOffset;
		}		
		if ( (nY+nYSize-1) > nEndY )
			nHeight	= nEndY - nY - nYOffset + 1;

		if ( (nWidth > 0) && (nHeight > 0) )
		{
			rc.left		= nXOffset;
			rc.right	= nXOffset+nWidth;
			rc.top		= nYOffset;
			rc.bottom	= nYOffset+nHeight;

			LONG	lWidth;
			ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
			ddsd.dwSize = sizeof(DDSURFACEDESC2);
			if ( FAILED(m_pddsBackBuffer->Lock(NULL, &ddsd, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL)) )
			{
				return FALSE;
			}

			WORD* pwdDst = (WORD*)ddsd.lpSurface;
			lWidth		 = ddsd.lPitch >> 1;

			INT nWidthStart	= 0;
			INT nWidthEnd	= 0;
			INT nCurrWidth  = 0;
			INT nCntCopyWord = 0;
			INT nYCnt =0;
			INT nLastWidth = 0;

			FLOAT rBlueRate, rGreenRate, bRedRate;
			BYTE  bRedSrc, bGreenSrc, bBlueSrc;
			BYTE  bRedWantedColor, bGreenWantedColor, bBlueWantedColor;
			WORD  wPixel;

			// y�� Ŭ����.
			for ( nYCnt=0 ; nYCnt < rc.top ; nYCnt++ )
			{
				nWidthEnd += pwSrc[nWidthStart];
				nWidthStart++;
				nWidthEnd++;
				nWidthStart	= nWidthEnd;
			}

			// y�࿡ ���ؼ� ������ ���ν�ų Count���� ���Ѵ�.
			for ( nYCnt=rc.top ; nYCnt < rc.bottom ; nYCnt++ )
			{
				// �Ѷ����� ���̸� ���´�.(������ ����)
				nWidthEnd += pwSrc[nWidthStart];
				nWidthStart++;

				// ������ ���̸�ŭ ȭ�鿡 �ѷ��ش�.
				for ( INT x = nWidthStart; x < nWidthEnd ; )
				{
					if ( pwSrc[x] == 0xC0 )
					{
						x++;
						nCntCopyWord = pwSrc[x];
						x++;
						nCurrWidth += nCntCopyWord;
					}
					else if ( pwSrc[x] == 0xC1 )
					{
						x++;
						nCntCopyWord = pwSrc[x];	// ����
						x++;

						nLastWidth = nCurrWidth;
						nCurrWidth += nCntCopyWord;

						if ( rc.left > nCurrWidth || rc.right < nLastWidth )
						{
							x += nCntCopyWord;		// ���� ���� ���� ���
						}
						else
						{
							// rc.left���� �������� ī���� ������ �ɸ� ���.
							if ( nLastWidth < rc.left && rc.left <= nCurrWidth )
							{
								x += (rc.left-nLastWidth);

								for(WORD i = 0 ; i < (sizeof(WORD)*(nCurrWidth-rc.left)/2);i++)
								{
									bsBlueColor  = (BYTE)((pwSrc[x+i] & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bsGreenColor = (BYTE)((pwSrc[x+i] & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bsRedColor   = (BYTE)((pwSrc[x+i] & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									// Draw Gray 									
									BYTE	temp;

									temp = (bsRedColor+bsGreenColor/2+bsBlueColor)/3;

									bsBlueColor = temp>0 ? (temp) : 0;
									bsGreenColor = temp>0 ? (temp<<1) : 0;
									bsRedColor = temp>0 ? (temp) :  0;									

									if ( ((nYCnt+nY) * lWidth) + (rc.left+nX) + i < 0 )
										return FALSE;

									pwdDst[((nYCnt+nY) * lWidth) + (rc.left+nX) + i] = (bsBlueColor<<m_stBitsMaskInfo.bBShift) |  (bsGreenColor<<m_stBitsMaskInfo.bGShift) | (bsRedColor<<m_stBitsMaskInfo.bRShift);
								}

								x += (nCurrWidth-rc.left);
							}
							// rc.right���� �������� ī���� ������ �ɸ� ���.
							else if ( nLastWidth <= rc.right && rc.right < nCurrWidth )
							{
								for(WORD i = 0 ; i < (sizeof(WORD)*(rc.right-nLastWidth));i++)
								{
									bsBlueColor  = (BYTE)((pwSrc[x+i] & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bsGreenColor = (BYTE)((pwSrc[x+i] & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bsRedColor   = (BYTE)((pwSrc[x+i] & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									// Draw Gray 									

									BYTE	temp;

									temp = (bsRedColor+bsGreenColor/2+bsBlueColor)/3;

									bsBlueColor = temp>0 ? (temp) : 0;
									bsGreenColor = temp>0 ? (temp<<1) : 0;
									bsRedColor = temp>0 ? (temp) :  0;

									pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX) + i] = (bsBlueColor<<m_stBitsMaskInfo.bBShift) |  (bsGreenColor<<m_stBitsMaskInfo.bGShift) | (bsRedColor<<m_stBitsMaskInfo.bRShift);
								}
//								memcpy(&pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX)], &pwSrc[x], sizeof(WORD)*(rc.right-nLastWidth));
								x += nCntCopyWord;
							}
							else
							{
								for(WORD i = 0 ; i < (sizeof(WORD)*nCntCopyWord/2);i++)
								{
									bsBlueColor  = (BYTE)((pwSrc[x+i] & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bsGreenColor = (BYTE)((pwSrc[x+i] & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bsRedColor   = (BYTE)((pwSrc[x+i] & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);
									// Draw Gray 
									BYTE	temp;

									temp = (bsRedColor+bsGreenColor/2+bsBlueColor)/3;

									bsBlueColor = temp>0 ? (temp) : 0;
									bsGreenColor = temp>0 ? (temp<<1) : 0;
									bsRedColor = temp>0 ? (temp) :  0;

									pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX) + i] = (bsBlueColor<<m_stBitsMaskInfo.bBShift) |  (bsGreenColor<<m_stBitsMaskInfo.bGShift) | (bsRedColor<<m_stBitsMaskInfo.bRShift);
								}
								x += nCntCopyWord;
							}
						}
					}
					else if ( pwSrc[x] == 0xC2 || pwSrc[x] == 0xC3 )
					{
						WORD wDyingKind, wChooseColor;
						wDyingKind = pwSrc[x];
						switch ( wDyingKind )
						{
						case 0xC2: 
							wChooseColor = wChooseColor1;
							break;
						case 0xC3: 
							wChooseColor = wChooseColor2;
							break;
						}
						x++;
						nCntCopyWord = pwSrc[x];
						x++;

						nLastWidth = nCurrWidth;
						nCurrWidth += nCntCopyWord;

						if ( rc.left > nCurrWidth || rc.right < nLastWidth )
						{
							x += nCntCopyWord;
						}
						else
						{
							// rc.left���� �������� ī���� ������ �ɸ� ���.
							if ( nLastWidth < rc.left && rc.left <= nCurrWidth )
							{
								x += (rc.left-nLastWidth);
								for ( INT nCheck = 0; nCheck < nCurrWidth-rc.left; nCheck++ )
								{
									wPixel	  = wChooseColor;
									bBlueWantedColor  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenWantedColor = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedWantedColor   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									wPixel	  = pwSrc[x+nCheck];
									bBlueSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenSrc = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
									rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
									bRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

									bBlueWantedColor = (BYTE)(((FLOAT)bBlueWantedColor*rBlueRate));
									bGreenWantedColor = (BYTE)(((FLOAT)bGreenWantedColor*rGreenRate));
									bRedWantedColor = (BYTE)(((FLOAT)bRedWantedColor*bRedRate));

									if ( bBlueWantedColor > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
										bBlueWantedColor = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
									if ( bGreenWantedColor > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
										bGreenWantedColor = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
									if ( bRedWantedColor > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
										bRedWantedColor = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);

									// Draw Gray 
									BYTE	temp;
									temp = (bRedWantedColor+bGreenWantedColor/2+bBlueWantedColor)/3;

									bBlueWantedColor = temp>0 ? (temp) : 0;
									bGreenWantedColor = temp>0 ? (temp<<1) : 0;
									bRedWantedColor = temp>0 ? (temp) :  0;

									if ( ((nYCnt+nY) * lWidth) + (nLastWidth+nX+nCheck) < 0 )
										return FALSE;

									pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX+nCheck)] = ((bRedWantedColor  <<m_stBitsMaskInfo.bRShift) |
																										  (bGreenWantedColor<<m_stBitsMaskInfo.bGShift) |
																										  (bBlueWantedColor <<m_stBitsMaskInfo.bBShift));			
								}
								x += (nCurrWidth-rc.left);
							}
							// rc.right���� �������� ī���� ������ �ɸ� ���.
							else if ( nLastWidth <= rc.right && rc.right < nCurrWidth )
							{
								for ( INT nCheck = 0; nCheck < rc.right-nLastWidth; nCheck++ )
								{
									wPixel	  = wChooseColor;
									bBlueWantedColor  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenWantedColor = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedWantedColor   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									wPixel	  = pwSrc[x+nCheck];
									bBlueSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenSrc = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
									rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
									bRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

									bBlueWantedColor = (BYTE)(((FLOAT)bBlueWantedColor*rBlueRate));
									bGreenWantedColor = (BYTE)(((FLOAT)bGreenWantedColor*rGreenRate));
									bRedWantedColor = (BYTE)(((FLOAT)bRedWantedColor*bRedRate));

									if ( bBlueWantedColor > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
										bBlueWantedColor = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
									if ( bGreenWantedColor > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
										bGreenWantedColor = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
									if ( bRedWantedColor > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
										bRedWantedColor = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);

									// Draw Gray 
									BYTE	temp;
									temp = (bRedWantedColor+bGreenWantedColor/2+bBlueWantedColor)/3;

									bBlueWantedColor = temp>0 ? (temp) : 0;
									bGreenWantedColor = temp>0 ? (temp<<1) : 0;
									bRedWantedColor = temp>0 ? (temp) :  0;

									pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX+nCheck)] = ((bRedWantedColor  <<m_stBitsMaskInfo.bRShift) |
																										  (bGreenWantedColor<<m_stBitsMaskInfo.bGShift) |
																										  (bBlueWantedColor <<m_stBitsMaskInfo.bBShift));			
								}
								x += nCntCopyWord;
							}
							else
							{
								for ( INT nCheck = 0; nCheck < nCntCopyWord; nCheck++ )
								{
									wPixel	  = wChooseColor;
									bBlueWantedColor  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenWantedColor = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedWantedColor   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									wPixel	  = pwSrc[x+nCheck];
									bBlueSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
									bGreenSrc = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
									bRedSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

									rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
									rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
									bRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

									bBlueWantedColor = (BYTE)(((FLOAT)bBlueWantedColor*rBlueRate));
									bGreenWantedColor = (BYTE)(((FLOAT)bGreenWantedColor*rGreenRate));
									bRedWantedColor = (BYTE)(((FLOAT)bRedWantedColor*bRedRate));

									if ( bBlueWantedColor > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
										bBlueWantedColor = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
									if ( bGreenWantedColor > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
										bGreenWantedColor = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
									if ( bRedWantedColor > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
										bRedWantedColor = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);
									
									// Draw Gray 
									BYTE	temp;
									temp = (bRedWantedColor+bGreenWantedColor/2+bBlueWantedColor)/3;

									bBlueWantedColor = temp>0 ? (temp) : 0;
									bGreenWantedColor = temp>0 ? (temp<<1) : 0;
									bRedWantedColor = temp>0 ? (temp) :  0;

									pwdDst[((nYCnt+nY) * lWidth) + (nLastWidth+nX+nCheck)] = ((bRedWantedColor  <<m_stBitsMaskInfo.bRShift) |
																										  (bGreenWantedColor<<m_stBitsMaskInfo.bGShift) |
																									 	  (bBlueWantedColor <<m_stBitsMaskInfo.bBShift));			
								}
								x += nCntCopyWord;
							}
						}
					}	
					else
					{
						m_pddsBackBuffer->Unlock(NULL);
						return FALSE;
					}
				}
				// ������ ���� ���� ������ �������� �Ű��ش�.
				nWidthEnd++;

				nWidthStart	= nWidthEnd;
				nCurrWidth = 0;
			}
		}

		m_pddsBackBuffer->Unlock(NULL);
		return TRUE;
	}
	return FALSE;
}


VOID CWHDXGraphicWindow::DrawWithGrayBackBuffer()
{
	DDSURFACEDESC2	ddsd;
	RECT			rc = {0, 0, 800, 500};

	if ( m_pddsBackBuffer == NULL )			return;

	LONG	lWidth;
	ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
	ddsd.dwSize = sizeof(DDSURFACEDESC2);
	if ( FAILED(m_pddsBackBuffer->Lock(NULL, &ddsd, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL)) )
	{
		return;
	}

	lWidth = ddsd.lPitch >> 1;

	WORD *pwdSrc, *pwdDst;
	BYTE bsBlueColor, bsGreenColor, bsRedColor;
	pwdDst = (WORD*)ddsd.lpSurface;
	pwdSrc = (WORD*)ddsd.lpSurface;

	for ( INT y=rc.top ; y < rc.bottom ; y++ )
	{
		for ( INT x=rc.left ; x < rc.right ; x++ )
		{
			bsBlueColor  = (BYTE)((pwdSrc[y * lWidth + x] & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
			bsGreenColor = (BYTE)((pwdSrc[y * lWidth + x] & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
			bsRedColor   = (BYTE)((pwdSrc[y * lWidth + x] & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

			// Draw Gray 									
			BYTE	temp;

			temp = (bsRedColor+bsGreenColor/2+bsBlueColor)/3;

			bsBlueColor  = temp>0 ? (temp)    : 0;
			bsGreenColor = temp>0 ? (temp<<1) : 0;
			bsRedColor   = temp>0 ? (temp)    : 0;									

			pwdDst[y * lWidth + x] = (bsBlueColor<<m_stBitsMaskInfo.bBShift) |  (bsGreenColor<<m_stBitsMaskInfo.bGShift) | (bsRedColor<<m_stBitsMaskInfo.bRShift);
		}
	}

	m_pddsBackBuffer->Unlock(NULL);
}



/******************************************************************************************************************

	�Լ��� : CWHDXGraphicWindow::DrawWithImageForCompClipRgnToMem()

	�ۼ��� : 
	�ۼ��� : 

	����   : ����� �ҽ� �̹����� ���ϴ� ������ ������ Ǯ�� ���·� ���޹��� �޸�(pwDst)�� ī���Ѵ�.

	�Է�   : INT nStartX
	         INT nStartY
	         INT nWantedXSize
	         INT nWantedYSize
	         WORD* pwSrc
	         WORD wClipWidth
	         WORD wClipHeight
	         WORD wChooseColor1
	         WORD wChooseColor2
	���   : BOOL

	[����][������] : ��������

*******************************************************************************************************************/
BOOL CWHDXGraphicWindow::DrawWithImageForCompColorToMem(RECT rcWanted, WORD* pwSrc, WORD wColor, WORD* pwDst)
{
	if ( rcWanted.left < 0 || rcWanted.right < 0 || rcWanted.top < 0 || rcWanted.bottom < 0 ||
		 rcWanted.right - rcWanted.left < 0 || rcWanted.bottom - rcWanted.top < 0 || pwDst == NULL )
		 return FALSE;

	INT nWidthStart		= 0;
	INT nWidthEnd		= 0;
	INT nCurrWidth		= 0;
	INT nCntCopyWord	= 0;
	INT nYCnt			= 0;
	INT nLastWidth		= 0;

	// y�� Ŭ����.
  	for ( nYCnt=0 ; nYCnt < rcWanted.top ; nYCnt++ )
	{
 		nWidthEnd += pwSrc[nWidthStart];
		nWidthStart++;
		nWidthEnd++;
		nWidthStart	= nWidthEnd;
	}

	INT nNewCurrWidth = 0;

	FLOAT rBlueRate, rGreenRate, rRedRate;
	BYTE  bRedSrc, bGreenSrc, bBlueSrc;
	BYTE  bRedStateColor, bGreenStateColor, bBlueStateColor;
	WORD  wPixel;

	// y�࿡ ���ؼ� ������ ���ν�ų Count���� ���Ѵ�.
	for ( nYCnt=rcWanted.top ; nYCnt < rcWanted.bottom ; nYCnt++ )
	{
		// �Ѷ����� ���̸� ���´�.(������ ����)
		nWidthEnd += pwSrc[nWidthStart];
		nWidthStart++;

		// ������ ���̸�ŭ ȭ�鿡 �ѷ��ش�.
		for ( INT x = nWidthStart; x < nWidthEnd ; )
		{
			if ( pwSrc[x] == 0xC0 )
			{
				x++;
				nCntCopyWord = pwSrc[x];
				x++;
				nLastWidth = nCurrWidth;
				nCurrWidth += nCntCopyWord;

				// rcWanted.left���� �������� ī���� ������ �ɸ� ���.
				if ( nLastWidth <= rcWanted.left && nCurrWidth >= rcWanted.right )
				{
					if ( ((nYCnt-rcWanted.top) * (rcWanted.right-rcWanted.left))  + nNewCurrWidth < 0 )
						return FALSE;

					memset(&pwDst[((nYCnt-rcWanted.top) * (rcWanted.right-rcWanted.left))  + nNewCurrWidth], 0, sizeof(WORD)*(rcWanted.right-rcWanted.left));
					nNewCurrWidth += rcWanted.right-rcWanted.left;
				}
				else if ( nLastWidth < rcWanted.left && nCurrWidth > rcWanted.left )
				{
					memset(&pwDst[((nYCnt-rcWanted.top) * (rcWanted.right-rcWanted.left)) + nNewCurrWidth], 0, sizeof(WORD)*(nCurrWidth-rcWanted.left));
					nNewCurrWidth += nCurrWidth-rcWanted.left;
				}
				else if ( nLastWidth >= rcWanted.left && nCurrWidth <= rcWanted.right )
				{
					memset(&pwDst[((nYCnt-rcWanted.top) * (rcWanted.right-rcWanted.left))  + nNewCurrWidth], 0, sizeof(WORD)*(nCntCopyWord));
					nNewCurrWidth += nCntCopyWord;
				}
				// rcWanted.right���� �������� ī���� ������ �ɸ� ���.
				else if ( nLastWidth < rcWanted.right && nCurrWidth > rcWanted.right )
				{
					memset(&pwDst[((nYCnt-rcWanted.top) * (rcWanted.right-rcWanted.left)) + nNewCurrWidth], 0, sizeof(WORD)*(rcWanted.right-nLastWidth));
					nNewCurrWidth += rcWanted.right-nLastWidth;
				}
			}
			else if ( pwSrc[x] == 0xC1 || pwSrc[x] == 0xC2 || pwSrc[x] == 0xC3 )
			{
				x++;
				nCntCopyWord = pwSrc[x];
				x++;

				nLastWidth = nCurrWidth;
				nCurrWidth += nCntCopyWord;

				if ( rcWanted.left > nCurrWidth || rcWanted.right < nLastWidth )
				{
					x += nCntCopyWord;
				}
				else
				{
					// rcWanted.left���� �������� ī���� ������ �ɸ� ���.
					if ( nLastWidth <= rcWanted.left && nCurrWidth >= rcWanted.right )
					{
						x += (rcWanted.left-nLastWidth);
						for ( INT nCheck = 0; nCheck < rcWanted.right-rcWanted.left; nCheck++ )
						{
							wPixel = wColor;
							bBlueStateColor  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
							bGreenStateColor = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
							bRedStateColor   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

							wPixel = pwSrc[x+nCheck];
							bBlueSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
							bGreenSrc = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
							bRedSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

							if ( !wColor )	
							{
								BYTE bTemp = (BYTE)(bBlueSrc+(bGreenSrc>>1)+bRedSrc)/3;
								if ( bTemp > 31 )	bTemp = 31;
								bBlueStateColor = bRedStateColor = bTemp;
								bGreenStateColor = bTemp<<1;
							}
							else
							{
								rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
								rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
								rRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

								bBlueStateColor  = (BYTE)((FLOAT)bBlueStateColor *rBlueRate );
								bGreenStateColor = (BYTE)((FLOAT)bGreenStateColor*rGreenRate);
								bRedStateColor   = (BYTE)((FLOAT)bRedStateColor  *rRedRate  );

								if ( bBlueStateColor > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
									bBlueStateColor = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
								if ( bGreenStateColor > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
									bGreenStateColor = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
								if ( bRedStateColor > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
									bRedStateColor = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);
							}

							if ( !bRedStateColor && !bGreenStateColor && !bBlueStateColor )		bRedStateColor = bGreenStateColor = bBlueStateColor = 1;

							if ( ((nYCnt-rcWanted.top) * (rcWanted.right-rcWanted.left)) + (nNewCurrWidth+nCheck) < 0 )
								return FALSE;

							pwDst[((nYCnt-rcWanted.top) * (rcWanted.right-rcWanted.left)) + (nNewCurrWidth+nCheck)] = ((bRedStateColor  <<m_stBitsMaskInfo.bRShift) |
																													   (bGreenStateColor<<m_stBitsMaskInfo.bGShift) |
																													   (bBlueStateColor <<m_stBitsMaskInfo.bBShift));			
						}
						nNewCurrWidth += rcWanted.right-rcWanted.left;
						x += (nCurrWidth-rcWanted.left);
					}
					else if ( nLastWidth < rcWanted.left && nCurrWidth > rcWanted.left )
					{
						x += (rcWanted.left-nLastWidth);
						for ( INT nCheck = 0; nCheck < nCurrWidth-rcWanted.left; nCheck++ )
						{
							wPixel = wColor;
							bBlueStateColor  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
							bGreenStateColor = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
							bRedStateColor   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

							wPixel = pwSrc[x+nCheck];
							bBlueSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
							bGreenSrc = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
							bRedSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

							if ( !wColor )	
							{
								BYTE bTemp = (BYTE)(bBlueSrc+(bGreenSrc>>1)+bRedSrc)/3;
								if ( bTemp > 31 )	bTemp = 31;
								bBlueStateColor = bRedStateColor = bTemp;
								bGreenStateColor = bTemp<<1;
							}
							else
							{
								rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
								rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
								rRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

								bBlueStateColor  = (BYTE)((FLOAT)bBlueStateColor *rBlueRate );
								bGreenStateColor = (BYTE)((FLOAT)bGreenStateColor*rGreenRate);
								bRedStateColor   = (BYTE)((FLOAT)bRedStateColor  *rRedRate  );

								if ( bBlueStateColor > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
									bBlueStateColor = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
								if ( bGreenStateColor > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
									bGreenStateColor = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
								if ( bRedStateColor > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
									bRedStateColor = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);
							}

							if ( !bRedStateColor && !bGreenStateColor && !bBlueStateColor )		bRedStateColor = bGreenStateColor = bBlueStateColor = 1;

							pwDst[((nYCnt-rcWanted.top) * (rcWanted.right-rcWanted.left)) + (nNewCurrWidth+nCheck)] = ((bRedStateColor  <<m_stBitsMaskInfo.bRShift) |
																													   (bGreenStateColor<<m_stBitsMaskInfo.bGShift) |
																													   (bBlueStateColor <<m_stBitsMaskInfo.bBShift));										
						}
						nNewCurrWidth += nCurrWidth-rcWanted.left;
						x += (nCurrWidth-rcWanted.left);
					}
					else if ( nLastWidth >= rcWanted.left && nCurrWidth <= rcWanted.right )
					{
						for ( INT nCheck = 0; nCheck < nCntCopyWord; nCheck++ )
						{
							wPixel = wColor;
							bBlueStateColor  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
							bGreenStateColor = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
							bRedStateColor   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

							wPixel = pwSrc[x+nCheck];
							bBlueSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
							bGreenSrc = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
							bRedSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

							if ( !wColor )	
							{
								BYTE bTemp = (BYTE)(bBlueSrc+(bGreenSrc>>1)+bRedSrc)/3;
								if ( bTemp > 31 )	bTemp = 31;
								bBlueStateColor = bRedStateColor = bTemp;
								bGreenStateColor = bTemp<<1;
							}
							else
							{
								if ( nCheck == 17 )
									int b = 0;

								rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
								rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
								rRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

								bBlueStateColor  = (BYTE)((FLOAT)bBlueStateColor *rBlueRate );
								bGreenStateColor = (BYTE)((FLOAT)bGreenStateColor*rGreenRate);
								bRedStateColor   = (BYTE)((FLOAT)bRedStateColor  *rRedRate  );

								if ( bBlueStateColor > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
									bBlueStateColor = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
								if ( bGreenStateColor > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
									bGreenStateColor = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
								if ( bRedStateColor > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
									bRedStateColor = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);
							}

							if ( !bRedStateColor && !bGreenStateColor && !bBlueStateColor )		bRedStateColor = bGreenStateColor = bBlueStateColor = 1;

							pwDst[((nYCnt-rcWanted.top) * (rcWanted.right-rcWanted.left)) + (nNewCurrWidth+nCheck)] = ((bRedStateColor  <<m_stBitsMaskInfo.bRShift) |
																													   (bGreenStateColor<<m_stBitsMaskInfo.bGShift) |
																													   (bBlueStateColor <<m_stBitsMaskInfo.bBShift));			
						}
						nNewCurrWidth += nCntCopyWord;
						x += nCntCopyWord;
					}
					// rcWanted.right���� �������� ī���� ������ �ɸ� ���.
					else if ( nLastWidth < rcWanted.right && nCurrWidth > rcWanted.right )
					{
						for ( INT nCheck = 0; nCheck < rcWanted.right-nLastWidth; nCheck++ )
						{
							wPixel = wColor;
							bBlueStateColor  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
							bGreenStateColor = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
							bRedStateColor   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

							wPixel = pwSrc[x+nCheck];
							bBlueSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
							bGreenSrc = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
							bRedSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

							if ( !wColor )	
							{
								BYTE bTemp = (BYTE)(bBlueSrc+(bGreenSrc>>1)+bRedSrc)/3;
								if ( bTemp > 31 )	bTemp = 31;
								bBlueStateColor = bRedStateColor = bTemp;
								bGreenStateColor = bTemp<<1;
							}
							else
							{
								rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
								rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
								rRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

								bBlueStateColor  = (BYTE)((FLOAT)bBlueStateColor *rBlueRate );
								bGreenStateColor = (BYTE)((FLOAT)bGreenStateColor*rGreenRate);
								bRedStateColor   = (BYTE)((FLOAT)bRedStateColor  *rRedRate  );

								if ( bBlueStateColor > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
									bBlueStateColor = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
								if ( bGreenStateColor > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
									bGreenStateColor = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
								if ( bRedStateColor > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
									bRedStateColor = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);
							}

							if ( !bRedStateColor && !bGreenStateColor && !bBlueStateColor )		bRedStateColor = bGreenStateColor = bBlueStateColor = 1;

							pwDst[((nYCnt-rcWanted.top) * (rcWanted.right-rcWanted.left)) + (nNewCurrWidth+nCheck)] = ((bRedStateColor  <<m_stBitsMaskInfo.bRShift) |
																													   (bGreenStateColor<<m_stBitsMaskInfo.bGShift) |
																													   (bBlueStateColor <<m_stBitsMaskInfo.bBShift));			
						}
						nNewCurrWidth += rcWanted.right-nLastWidth;
						x += nCntCopyWord;
					}
					else
					{
						x += nCntCopyWord;
					}
				}
			}	
			else
			{
				return FALSE;
			}
		}
		// ������ ���� ���� ������ �������� �Ű��ش�.
		nWidthEnd++;

		nWidthStart	= nWidthEnd;
		nCurrWidth = 0;
		nNewCurrWidth = 0;
	}
	return TRUE;
}




BOOL CWHDXGraphicWindow::DrawWithImageForCompToMem(RECT rcWanted, WORD* pwSrc, WORD wChooseColor1, WORD wChooseColor2, WORD* pwDst)
{
	if ( rcWanted.left < 0 || rcWanted.right < 0 || rcWanted.top < 0 || rcWanted.bottom < 0 ||
		 rcWanted.right - rcWanted.left < 0 || rcWanted.bottom - rcWanted.top < 0 || pwDst == NULL )
		 return FALSE;

	INT nWidthStart		= 0;
	INT nWidthEnd		= 0;
	INT nCurrWidth		= 0;
	INT nCntCopyWord	= 0;
	INT nYCnt			= 0;
	INT nLastWidth		= 0;

	// y�� Ŭ����.
  	for ( nYCnt=0 ; nYCnt < rcWanted.top ; nYCnt++ )
	{
 		nWidthEnd += pwSrc[nWidthStart];
		nWidthStart++;
		nWidthEnd++;
		nWidthStart	= nWidthEnd;
	}

	INT nNewCurrWidth = 0;

	FLOAT rBlueRate, rGreenRate, bRedRate;
	BYTE  bRedSrc, bGreenSrc, bBlueSrc;
	BYTE  bRedWantedColor, bGreenWantedColor, bBlueWantedColor;
	WORD  wPixel;

	// y�࿡ ���ؼ� ������ ���ν�ų Count���� ���Ѵ�.
	for ( nYCnt=rcWanted.top ; nYCnt < rcWanted.bottom ; nYCnt++ )
	{
		// �Ѷ����� ���̸� ���´�.(������ ����)
		nWidthEnd += pwSrc[nWidthStart];
		nWidthStart++;

		// ������ ���̸�ŭ ȭ�鿡 �ѷ��ش�.
		for ( INT x = nWidthStart; x < nWidthEnd ; )
		{
			if ( pwSrc[x] == 0xC0 )
			{
				x++;
				nCntCopyWord = pwSrc[x];
				x++;
				nLastWidth = nCurrWidth;
				nCurrWidth += nCntCopyWord;

				// rcWanted.left���� �������� ī���� ������ �ɸ� ���.
				if ( nLastWidth <= rcWanted.left && nCurrWidth >= rcWanted.right )
				{
					if ( ((nYCnt-rcWanted.top) * (rcWanted.right-rcWanted.left))  + nNewCurrWidth < 0 )
						return FALSE;

					memset(&pwDst[((nYCnt-rcWanted.top) * (rcWanted.right-rcWanted.left))  + nNewCurrWidth], 0, sizeof(WORD)*(rcWanted.right-rcWanted.left));
					nNewCurrWidth += rcWanted.right-rcWanted.left;
				}
				else if ( nLastWidth < rcWanted.left && nCurrWidth > rcWanted.left )
				{
					memset(&pwDst[((nYCnt-rcWanted.top) * (rcWanted.right-rcWanted.left)) + nNewCurrWidth], 0, sizeof(WORD)*(nCurrWidth-rcWanted.left));
					nNewCurrWidth += nCurrWidth-rcWanted.left;
				}
				else if ( nLastWidth >= rcWanted.left && nCurrWidth <= rcWanted.right )
				{
					memset(&pwDst[((nYCnt-rcWanted.top) * (rcWanted.right-rcWanted.left))  + nNewCurrWidth], 0, sizeof(WORD)*(nCntCopyWord));
					nNewCurrWidth += nCntCopyWord;
				}
				// rcWanted.right���� �������� ī���� ������ �ɸ� ���.
				else if ( nLastWidth < rcWanted.right && nCurrWidth > rcWanted.right )
				{
					memset(&pwDst[((nYCnt-rcWanted.top) * (rcWanted.right-rcWanted.left)) + nNewCurrWidth], 0, sizeof(WORD)*(rcWanted.right-nLastWidth));
					nNewCurrWidth += rcWanted.right-nLastWidth;
				}
			}
			else if ( pwSrc[x] == 0xC1 )
			{
				x++;
				nCntCopyWord = pwSrc[x];
				x++;

				nLastWidth = nCurrWidth;
				nCurrWidth += nCntCopyWord;

				if ( rcWanted.left > nCurrWidth || rcWanted.right < nLastWidth )
				{
					x += nCntCopyWord;
				}
				else
				{
					// rcWanted.left���� �������� ī���� ������ �ɸ� ���.
					if ( nLastWidth <= rcWanted.left && nCurrWidth >= rcWanted.right )
					{
						if ( ((nYCnt-rcWanted.top) * (rcWanted.right-rcWanted.left)) + nNewCurrWidth < 0 )
							return FALSE;

						x += (rcWanted.left-nLastWidth);
						memcpy(&pwDst[((nYCnt-rcWanted.top) * (rcWanted.right-rcWanted.left)) + nNewCurrWidth], &pwSrc[x], sizeof(WORD)*(rcWanted.right-rcWanted.left));
						nNewCurrWidth += rcWanted.right-rcWanted.left;
						x += (nCurrWidth-rcWanted.left);
					}
					else if ( nLastWidth < rcWanted.left && nCurrWidth > rcWanted.left )
					{
						x += (rcWanted.left-nLastWidth);
						memcpy(&pwDst[((nYCnt-rcWanted.top) * (rcWanted.right-rcWanted.left)) + nNewCurrWidth], &pwSrc[x], sizeof(WORD)*(nCurrWidth-rcWanted.left));
						nNewCurrWidth += nCurrWidth-rcWanted.left;
						x += (nCurrWidth-rcWanted.left);
					}
					else if ( nLastWidth >= rcWanted.left && nCurrWidth <= rcWanted.right )
					{
						memcpy(&pwDst[((nYCnt-rcWanted.top) * (rcWanted.right-rcWanted.left)) + nNewCurrWidth], &pwSrc[x], sizeof(WORD)*nCntCopyWord);
						nNewCurrWidth += nCntCopyWord;
						x += nCntCopyWord;
					}
					// rcWanted.right���� �������� ī���� ������ �ɸ� ���.
					else if ( nLastWidth < rcWanted.right && nCurrWidth > rcWanted.right )
					{
						memcpy(&pwDst[((nYCnt-rcWanted.top) * (rcWanted.right-rcWanted.left)) + nNewCurrWidth], &pwSrc[x], sizeof(WORD)*(rcWanted.right-nLastWidth));
						nNewCurrWidth += rcWanted.right-nLastWidth;
						x += nCntCopyWord;
					}
					else
					{
						x += nCntCopyWord;
					}
				}
			}
			else if ( pwSrc[x] == 0xC2 || pwSrc[x] == 0xC3 )
			{
				WORD wDyingKind, wChooseColor;
				wDyingKind = pwSrc[x];
				switch ( wDyingKind )
				{
				case 0xC2: 
					wChooseColor = wChooseColor1;
					break;
				case 0xC3: 
					wChooseColor = wChooseColor2;
					break;
				}
				x++;
				nCntCopyWord = pwSrc[x];
				x++;

				nLastWidth = nCurrWidth;
				nCurrWidth += nCntCopyWord;

				if ( rcWanted.left > nCurrWidth || rcWanted.right < nLastWidth )
				{
					x += nCntCopyWord;
				}
				else
				{
					// rcWanted.left���� �������� ī���� ������ �ɸ� ���.
					if ( nLastWidth <= rcWanted.left && nCurrWidth >= rcWanted.right )
					{
						x += (rcWanted.left-nLastWidth);
						for ( INT nCheck = 0; nCheck < rcWanted.right-rcWanted.left; nCheck++ )
						{
							wPixel	  = wChooseColor;
							bBlueWantedColor  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
							bGreenWantedColor = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
							bRedWantedColor   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

							wPixel	  = pwSrc[x+nCheck];
							bBlueSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
							bGreenSrc = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
							bRedSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

							rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
							rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
							bRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

							bBlueWantedColor = (BYTE)(((FLOAT)bBlueWantedColor*rBlueRate));
							bGreenWantedColor = (BYTE)(((FLOAT)bGreenWantedColor*rGreenRate));
							bRedWantedColor = (BYTE)(((FLOAT)bRedWantedColor*bRedRate));

							if ( bBlueWantedColor > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
								bBlueWantedColor = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
							if ( bGreenWantedColor > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
								bGreenWantedColor = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
							if ( bRedWantedColor > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
								bRedWantedColor = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);

							if ( ((nYCnt-rcWanted.top) * (rcWanted.right-rcWanted.left)) + (nNewCurrWidth+nCheck) < 0 )
								return FALSE;

							pwDst[((nYCnt-rcWanted.top) * (rcWanted.right-rcWanted.left)) + (nNewCurrWidth+nCheck)] = ((bRedWantedColor  <<m_stBitsMaskInfo.bRShift) |
																													   (bGreenWantedColor<<m_stBitsMaskInfo.bGShift) |
																													   (bBlueWantedColor <<m_stBitsMaskInfo.bBShift));			
						}
						nNewCurrWidth += rcWanted.right-rcWanted.left;
						x += (nCurrWidth-rcWanted.left);
					}
					else if ( nLastWidth < rcWanted.left && nCurrWidth > rcWanted.left )
					{
						x += (rcWanted.left-nLastWidth);
						for ( INT nCheck = 0; nCheck < nCurrWidth-rcWanted.left; nCheck++ )
						{
							wPixel	  = wChooseColor;
							bBlueWantedColor  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
							bGreenWantedColor = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
							bRedWantedColor   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

							wPixel	  = pwSrc[x+nCheck];
							bBlueSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
							bGreenSrc = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
							bRedSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

							rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
							rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
							bRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

							bBlueWantedColor = (BYTE)(((FLOAT)bBlueWantedColor*rBlueRate));
							bGreenWantedColor = (BYTE)(((FLOAT)bGreenWantedColor*rGreenRate));
							bRedWantedColor = (BYTE)(((FLOAT)bRedWantedColor*bRedRate));

							if ( bBlueWantedColor > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
								bBlueWantedColor = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
							if ( bGreenWantedColor > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
								bGreenWantedColor = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
							if ( bRedWantedColor > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
								bRedWantedColor = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);

							pwDst[((nYCnt-rcWanted.top) * (rcWanted.right-rcWanted.left)) + (nNewCurrWidth+nCheck)] = ((bRedWantedColor  <<m_stBitsMaskInfo.bRShift) |
																													   (bGreenWantedColor<<m_stBitsMaskInfo.bGShift) |
																													   (bBlueWantedColor <<m_stBitsMaskInfo.bBShift));										
						}
						nNewCurrWidth += nCurrWidth-rcWanted.left;
						x += (nCurrWidth-rcWanted.left);
					}
					else if ( nLastWidth >= rcWanted.left && nCurrWidth <= rcWanted.right )
					{
						for ( INT nCheck = 0; nCheck < nCntCopyWord; nCheck++ )
						{
							wPixel	  = wChooseColor;
							bBlueWantedColor  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
							bGreenWantedColor = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
							bRedWantedColor   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

							wPixel	  = pwSrc[x+nCheck];
							bBlueSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
							bGreenSrc = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
							bRedSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

							rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
							rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
							bRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

							bBlueWantedColor = (BYTE)(((FLOAT)bBlueWantedColor*rBlueRate));
							bGreenWantedColor = (BYTE)(((FLOAT)bGreenWantedColor*rGreenRate));
							bRedWantedColor = (BYTE)(((FLOAT)bRedWantedColor*bRedRate));

							if ( bBlueWantedColor > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
								bBlueWantedColor = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
							if ( bGreenWantedColor > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
								bGreenWantedColor = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
							if ( bRedWantedColor > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
								bRedWantedColor = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);

							pwDst[((nYCnt-rcWanted.top) * (rcWanted.right-rcWanted.left)) + (nNewCurrWidth+nCheck)] = ((bRedWantedColor  <<m_stBitsMaskInfo.bRShift) |
																													   (bGreenWantedColor<<m_stBitsMaskInfo.bGShift) |
																													   (bBlueWantedColor <<m_stBitsMaskInfo.bBShift));			
						}
						nNewCurrWidth += nCntCopyWord;
						x += nCntCopyWord;
					}
					// rcWanted.right���� �������� ī���� ������ �ɸ� ���.
					else if ( nLastWidth < rcWanted.right && nCurrWidth > rcWanted.right )
					{
						for ( INT nCheck = 0; nCheck < rcWanted.right-nLastWidth; nCheck++ )
						{
							wPixel	  = wChooseColor;
							bBlueWantedColor  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
							bGreenWantedColor = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
							bRedWantedColor   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

							wPixel	  = pwSrc[x+nCheck];
							bBlueSrc  = (BYTE)((wPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
							bGreenSrc = (BYTE)((wPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
							bRedSrc   = (BYTE)((wPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

							rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
							rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
							bRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

							bBlueWantedColor = (BYTE)(((FLOAT)bBlueWantedColor*rBlueRate));
							bGreenWantedColor = (BYTE)(((FLOAT)bGreenWantedColor*rGreenRate));
							bRedWantedColor = (BYTE)(((FLOAT)bRedWantedColor*bRedRate));

							if ( bBlueWantedColor > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
								bBlueWantedColor = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
							if ( bGreenWantedColor > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
								bGreenWantedColor = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
							if ( bRedWantedColor > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
								bRedWantedColor = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);


							pwDst[((nYCnt-rcWanted.top) * (rcWanted.right-rcWanted.left)) + (nNewCurrWidth+nCheck)] = ((bRedWantedColor  <<m_stBitsMaskInfo.bRShift) |
																													   (bGreenWantedColor<<m_stBitsMaskInfo.bGShift) |
																													   (bBlueWantedColor <<m_stBitsMaskInfo.bBShift));			
						}
						nNewCurrWidth += rcWanted.right-nLastWidth;
						x += nCntCopyWord;
					}
					else
					{
						x += nCntCopyWord;
					}
				}
			}	
			else
			{
				return FALSE;
			}
		}
		// ������ ���� ���� ������ �������� �Ű��ش�.
		nWidthEnd++;

		nWidthStart	= nWidthEnd;
		nCurrWidth = 0;
		nNewCurrWidth = 0;
	}
	return TRUE;
}











BOOL CWHDXGraphicWindow::DrawWithImageForComp(RECT* prcSrc, WORD* pwSrc, LPDIRECTDRAWSURFACE7 pddsDst)
{
	DDSURFACEDESC2		ddsd;

	LONG	lWidth;
	ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
	ddsd.dwSize = sizeof(DDSURFACEDESC2);
	if ( FAILED(pddsDst->Lock(NULL, &ddsd, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL)) )
	{
		return FALSE;
	}

	WORD* pwdDst = (WORD*)ddsd.lpSurface;
	lWidth		 = ddsd.lPitch >> 1;

	INT nYCnt		= 0;
	INT nWidthStart	= 0;
	INT nWidthEnd	= 0;
	INT nCurrWidth  = 0;
	INT nLastWidth	= 0;
	INT nCntCopyWord= 0;

	// y�� Ŭ����.
	for ( nYCnt=0 ; nYCnt < prcSrc->top ; nYCnt++ )
	{
		nWidthEnd += pwSrc[nWidthStart];
		nWidthStart++;
		nWidthEnd++;
		nWidthStart	= nWidthEnd;
	}

	// y�࿡ ���ؼ� ������ ���ν�ų Count���� ���Ѵ�.
	for ( nYCnt=prcSrc->top; nYCnt < prcSrc->bottom ; nYCnt++ )
	{
		// �Ѷ����� ���̸� ���´�.(������ ����)
		nWidthEnd += pwSrc[nWidthStart];
		nWidthStart++;

		// ������ ���̸�ŭ ȭ�鿡 �ѷ��ش�.
		for ( INT x = nWidthStart; x < nWidthEnd ; )
		{
			if ( pwSrc[x] == 0xC0 )
			{
				x++;
				nCntCopyWord = pwSrc[x];
				x++;
				nLastWidth = nCurrWidth;
				nCurrWidth += nCntCopyWord;
			}
			else if ( pwSrc[x] == 0xC1 )
			{
				x++;
				nCntCopyWord = pwSrc[x];
				x++;

				nLastWidth = nCurrWidth;
				nCurrWidth += nCntCopyWord;

				// prcSrc->left���� �������� ī���� ������ �ɸ� ���.
				if ( nLastWidth <= prcSrc->left && prcSrc->left <= nCurrWidth )
				{
					if ( ((nYCnt-prcSrc->top) * lWidth) < 0 )
						return FALSE;

					if ( prcSrc->right <= nCurrWidth )
					{
						x += (prcSrc->left-nLastWidth);
						memcpy(&pwdDst[((nYCnt-prcSrc->top) * lWidth)], &pwSrc[x], sizeof(WORD)*(prcSrc->right-prcSrc->left));
						x += (nCurrWidth-prcSrc->left);
					}
					else
					{
						x += (prcSrc->left-nLastWidth);
						memcpy(&pwdDst[((nYCnt-prcSrc->top) * lWidth)], &pwSrc[x], sizeof(WORD)*(nCurrWidth-prcSrc->left));
						x += (nCurrWidth-prcSrc->left);
					}
				}
				// prcSrc->right���� �������� ī���� ������ �ɸ� ���.
				else if ( nLastWidth < prcSrc->right && prcSrc->right < nCurrWidth )
				{
					memcpy(&pwdDst[((nYCnt-prcSrc->top) * lWidth) + (nLastWidth-prcSrc->left)], &pwSrc[x], sizeof(WORD)*(prcSrc->right-nLastWidth));
					x += nCntCopyWord;
				}
				// prcSrc->left���������� �ִ°��.
				else if ( nLastWidth < prcSrc->left && nCurrWidth <= prcSrc->left )
				{
					x += nCntCopyWord;
				}
				// prcSrc->right���������� �ִ°��.
				else if ( nLastWidth >= prcSrc->right && nCurrWidth > prcSrc->right )
				{
					x += nCntCopyWord;
				}
				// prcSrc->left���� prcSrc->right�� ���̿� �ִ°��.
				else
				{
					memcpy(&pwdDst[((nYCnt-prcSrc->top) * lWidth) + (nLastWidth-prcSrc->left)], &pwSrc[x], sizeof(WORD)*nCntCopyWord);
					x += nCntCopyWord;
				}
			}
			else
			{
				pddsDst->Unlock(NULL);
				return FALSE;
			}
		}
		// ������ ���� ���� ������ �������� �Ű��ش�.
		nWidthEnd++;

		nWidthStart	= nWidthEnd;
		nCurrWidth = 0;
	}

	pddsDst->Unlock(NULL);
	return TRUE;
}















/******************************************************************************************************************

	�Լ��� : CWHDXGraphicWindow::DrawWithABlendF2orIntersectCompData()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : INT nX					: ����ۻ��� �׸�������ġ.
	         INT nY					
	         INT nSrcXSize			: �����׸��� ������.
	         INT nSrcYSize
	         WORD* pwSrc			: �����׸��� ����Ÿ.
	         INT nDstXSize			: Ÿ�ٱ׸��� ������.
	         INT nDstYSize
	         WORD* pwDst			: Ÿ�ٱ׸��� ����Ÿ.
	         WORD wSrcChooseColor1	: �����׸��� ���� �̹���1 �÷�.
	         WORD wSrcChooseColor2
	         WORD wDstChooseColor1	: Ÿ�ٱ׸��� ���� �̹���1 �÷�.
	         WORD wDstChooseColor2
	���   : BOOL 

	[����][������] : ��������

*******************************************************************************************************************/
BOOL CWHDXGraphicWindow::DrawWithABlendForIntersectCompData(INT nSrcX, INT nSrcY, 
															INT nSrcXSize, INT nSrcYSize, WORD* pwSrc,
															INT nDstX, INT nDstY,
															INT nDstXSize, INT nDstYSize, WORD* pwDst,
															WORD wClipWidth, WORD wClipHeight,
															BYTE bOpa, BOOL bFocused,
															WORD wSrcChooseColor1, WORD wSrcChooseColor2, 
															WORD wDstChooseColor1, WORD wDstChooseColor2,
															WORD wSrcColor, WORD wDstColor)
{
	DDSURFACEDESC2	ddsd;
	RECT rcSrc, rcDst;
	RECT rcSrcIntersect = { 0, 0, 0, 0 };
	RECT rcDstIntersect = { 0, 0, 0, 0 };
	WORD* pwdDst = NULL;

	INT	nSrcWidth	= nSrcXSize;
	INT	nSrcHeight	= nSrcYSize;
	INT	nXSrcOffset	= 0;
	INT	nYSrcOffset	= 0;

	INT	nDstWidth	= nDstXSize;
	INT	nDstHeight	= nDstYSize;
	INT	nXDstOffset	= 0;
	INT	nYDstOffset	= 0;

	INT	nEndX		= wClipWidth -1;
	INT	nEndY		= wClipHeight-1;
	INT	nStartX		= 0;
	INT	nStartY		= 0;

	WORD* pwDstSave = NULL;
	WORD* pwSrcSave = NULL;

	if ( m_pddsBackBuffer != NULL )
	{
		// Source�� ȭ��Ŭ������ ����.
		if ( nSrcX < nStartX )
		{ 
			nXSrcOffset	= nStartX - nSrcX;
			nSrcWidth	= nSrcXSize - nXSrcOffset;
		}
		if ( (nSrcX+nSrcXSize-1) > nEndX )
			nSrcWidth	= nEndX - nSrcX - nXSrcOffset + 1;		
		if ( nSrcY < nStartY )	
		{ 
			nYSrcOffset	= nStartY - nSrcY;
			nSrcHeight	= nSrcYSize - nYSrcOffset;
		}		
		if ( (nSrcY+nSrcYSize-1) > nEndY )
			nSrcHeight	= nEndY - nSrcY - nYSrcOffset + 1;

		if ( (nSrcWidth > 0) && (nSrcHeight > 0) )
		{
			// Source������ ����.
			rcSrc.left		= nXSrcOffset;
			rcSrc.right		= nXSrcOffset+nSrcWidth;
			rcSrc.top		= nYSrcOffset;
			rcSrc.bottom	= nYSrcOffset+nSrcHeight;

			// Destination�� ȭ��Ŭ������ ����.
			if ( nDstX < nStartX )
			{ 
				nXDstOffset	= nStartX - nDstX;
				nDstWidth	= nDstXSize - nXDstOffset;
			}
			if ( (nDstX+nDstXSize-1) > nEndX )
				nDstWidth	= nEndX - nDstX - nXDstOffset + 1;		
			if ( nDstY < nStartY )	
			{ 
				nYDstOffset	= nStartY - nDstY;
				nDstHeight	= nDstYSize - nYDstOffset;
			}		
			if ( (nDstY+nDstYSize-1) > nEndY )
				nDstHeight	= nEndY - nDstY - nYDstOffset + 1;

			if ( (nDstWidth > 0) && (nDstHeight > 0) )
			{
				// Destination������ ����.
				rcDst.left		= nXDstOffset;
				rcDst.right		= nXDstOffset+nDstWidth;
				rcDst.top		= nYDstOffset;
				rcDst.bottom	= nYDstOffset+nDstHeight;

				// ���̹����� ��ġ�� ������ ���Ѵ�.
				RECT rcTemp;

				// �ҽ������� ������� ����Ʈ������ ���Ѵ�.
				rcTemp.left = rcDst.left + (nDstX-nSrcX);
				rcTemp.top = rcDst.top + (nDstY-nSrcY);
				rcTemp.right = rcDst.right + (nDstX-nSrcX);
				rcTemp.bottom = rcDst.bottom + (nDstY-nSrcY);

				// �ҽ� ��Ʈ������ �������� �� �� �簢���� �����簢���� ���Ѵ�.
				IntersectRect(&rcSrcIntersect, &rcSrc, &rcTemp);

				// ����Ʈ������ ������� �ҽ������� ���Ѵ�.
				rcTemp.left = rcSrc.left + (nSrcX-nDstX);
				rcTemp.top = rcSrc.top + (nSrcY-nDstY);
				rcTemp.right = rcSrc.right + (nSrcX-nDstX);
				rcTemp.bottom = rcSrc.bottom + (nSrcY-nDstY);

				// ����Ʈ ��Ʈ������ �������� �� �� �簢���� �����簢���� ���Ѵ�.
				IntersectRect(&rcDstIntersect, &rcTemp, &rcDst);

				LONG	lWidth;
				ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
				ddsd.dwSize = sizeof(DDSURFACEDESC2);
				if ( FAILED(m_pddsBackBuffer->Lock(NULL, &ddsd, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL)) )
				{
					return FALSE;
				}

				WORD* pwdDst = (WORD*)ddsd.lpSurface;
				lWidth		 = ddsd.lPitch >> 1;

				pwSrcSave = new WORD[(rcSrcIntersect.right-rcSrcIntersect.left)*(rcSrcIntersect.bottom-rcSrcIntersect.top)];
				pwDstSave = new WORD[(rcDstIntersect.right-rcDstIntersect.left)*(rcDstIntersect.bottom-rcDstIntersect.top)];

				if ( wSrcColor == 0XFFFF && wDstColor == 0XFFFF )
				{
					DrawWithImageForCompToMem(rcSrcIntersect, (WORD*)pwSrc, wSrcChooseColor1, wSrcChooseColor2, pwSrcSave);
					DrawWithImageForCompToMem(rcDstIntersect, (WORD*)pwDst, wDstChooseColor1, wDstChooseColor2, pwDstSave);
				}
				else if ( wSrcColor != 0XFFFF && wDstColor == 0XFFFF )
				{
					DrawWithImageForCompColorToMem(rcSrcIntersect, (WORD*)pwSrc, wSrcColor, pwSrcSave);
					DrawWithImageForCompToMem(rcDstIntersect, (WORD*)pwDst, wDstChooseColor1, wDstChooseColor2, pwDstSave);
				}
				else if ( wSrcColor == 0XFFFF && wDstColor != 0XFFFF )
				{
					DrawWithImageForCompToMem(rcSrcIntersect, (WORD*)pwSrc, wSrcChooseColor1, wSrcChooseColor2, pwSrcSave);
					DrawWithImageForCompColorToMem(rcDstIntersect, (WORD*)pwDst, wDstColor, pwDstSave);
				}
				else
				{
					DrawWithImageForCompColorToMem(rcSrcIntersect, (WORD*)pwSrc, wSrcColor, pwSrcSave);
					DrawWithImageForCompColorToMem(rcDstIntersect, (WORD*)pwDst, wDstColor, pwDstSave);
				}

				BYTE bRedDst, bGreenDst, bBlueDst;
				BYTE bRedSrc, bGreenSrc, bBlueSrc;
				WORD wSrcPixel, wDstPixel;
				FLOAT rBlueRate, rGreenRate, bRedRate;

				for ( INT nYCnt = 0; nYCnt < rcSrcIntersect.bottom - rcSrcIntersect.top; nYCnt++ )
					for ( INT nXCnt = 0; nXCnt < rcSrcIntersect.right - rcSrcIntersect.left; nXCnt++ )
				{
					wSrcPixel = pwSrcSave[nYCnt*(rcSrcIntersect.right - rcSrcIntersect.left) + nXCnt];
					wDstPixel = pwDstSave[nYCnt*(rcDstIntersect.right - rcDstIntersect.left) + nXCnt];
					if ( wSrcPixel != 0 && wDstPixel != 0 )
					{
						bBlueSrc  = (BYTE)((wSrcPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
						bGreenSrc = (BYTE)((wSrcPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
						bRedSrc   = (BYTE)((wSrcPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

						if ( bFocused )
						{
							rBlueRate = (FLOAT)((FLOAT)bBlueSrc / (FLOAT)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift));
							rGreenRate = (FLOAT)((FLOAT)bGreenSrc / (FLOAT)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift));
							bRedRate = (FLOAT)((FLOAT)bRedSrc / (FLOAT)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift));

							bBlueSrc = (BYTE)((FLOAT)bBlueSrc + ((FLOAT)bBlueSrc*rBlueRate));
							bGreenSrc = (BYTE)((FLOAT)bGreenSrc + ((FLOAT)bGreenSrc*rGreenRate));
							bRedSrc = (BYTE)((FLOAT)bRedSrc + ((FLOAT)bRedSrc*bRedRate));

							if ( bBlueSrc > (m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift) )
								bBlueSrc = (BYTE)(m_stBitsMaskInfo.dwBMask>>m_stBitsMaskInfo.bBShift);
							if ( bGreenSrc > (m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift) )
								bGreenSrc = (BYTE)(m_stBitsMaskInfo.dwGMask>>m_stBitsMaskInfo.bGShift);
							if ( bRedSrc > (m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift) )
								bRedSrc = (BYTE)(m_stBitsMaskInfo.dwRMask>>m_stBitsMaskInfo.bRShift);

							// ��Ŀ���� ������ Opacity���� �����ش�.
							bOpa = 40;
						}

						bBlueDst  = (BYTE)((wDstPixel & m_stBitsMaskInfo.dwBMask) >> m_stBitsMaskInfo.bBShift);
						bGreenDst = (BYTE)((wDstPixel & m_stBitsMaskInfo.dwGMask) >> m_stBitsMaskInfo.bGShift);
						bRedDst   = (BYTE)((wDstPixel & m_stBitsMaskInfo.dwRMask) >> m_stBitsMaskInfo.bRShift);

						bBlueDst  = (BYTE)((bOpa*(bBlueDst -bBlueSrc )+100*bBlueSrc ) / 100);
						bGreenDst = (BYTE)((bOpa*(bGreenDst-bGreenSrc)+100*bGreenSrc) / 100);
						bRedDst   = (BYTE)((bOpa*(bRedDst  -bRedSrc  )+100*bRedSrc  ) / 100);

						pwdDst[((nYCnt+nSrcY+rcSrcIntersect.top) * lWidth) + (rcSrcIntersect.left+nSrcX+nXCnt)] = 
												((bRedDst  <<m_stBitsMaskInfo.bRShift) |
												 (bGreenDst<<m_stBitsMaskInfo.bGShift) |
												 (bBlueDst <<m_stBitsMaskInfo.bBShift));
					}
				}

				SAFE_DELETEARR(pwSrcSave);
				SAFE_DELETEARR(pwDstSave);

				m_pddsBackBuffer->Unlock(NULL);
				return TRUE;
			}
		}
	}
	return FALSE;
}





/******************************************************************************************************************

	�Լ��� : CWHDXGraphicWindow::Present()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : LPRECT lprcDest
	         LPRECT lprcSrc
	         BYTE bCntRgn
	���   : HRESULT 

	[����][������] : ��������

*******************************************************************************************************************/
HRESULT CWHDXGraphicWindow::Present()
{
	HRESULT hr;

	if ( NULL == m_pddsFrontBuffer || NULL == m_pddsBackBuffer )
	{
		return E_POINTER;
	}

	while ( TRUE )
	{
		hr = m_pddsFrontBuffer->Blt(&m_rcWindow, m_pddsBackBuffer, NULL, DDBLT_WAIT, NULL);
/*		if ( m_bScreenModeFlag & _DXG_SCREENMODE_WINDOW )
		{
			hr = m_pddsFrontBuffer->Blt(&m_rcWindow, m_pddsBackBuffer, NULL, DDBLT_WAIT, NULL);
		}
		else
		{
			hr = m_pddsFrontBuffer->Flip(NULL, DDFLIP_WAIT );
		}
*/
		if ( hr == DDERR_SURFACELOST )
		{
			m_pddsFrontBuffer->Restore();
			m_pddsBackBuffer->Restore();
		}

		if ( hr != DDERR_WASSTILLDRAWING )
		{
			return hr;
		}
/*		if ( hr == DD_OK )
		{
			return hr;
		}
*/	} 
}



/******************************************************************************************************************

	�Լ��� : RestoreSurfaces()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	���   : HRESULT 

	[����][������] : ��������

*******************************************************************************************************************/
HRESULT CWHDXGraphicWindow::RestoreSurfaces()
{
    HRESULT hr;

	if ( !m_pDD )
		return E_FAIL;

    if ( FAILED(hr = m_pDD->RestoreAllSurfaces()) )
        return hr;

    return S_OK;
}













/******************************************************************************************************************

  Callback Function

*******************************************************************************************************************/


/******************************************************************************************************************

	�Լ��� : WINAPI DXGDriverEnumCallbackEx()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : GUID *pGUID
	         LPSTR szDesc
	         LPSTR szName
	         LPVOID pContext
	         HMONITOR hm
	���   : static BOOL 

	[����][������] : ��������

*******************************************************************************************************************/
static BOOL WINAPI DXGDriverEnumCallbackEx(GUID *pGUID, LPSTR szDesc, LPSTR szName, LPVOID pContext, HMONITOR hm)
{
    LPDIRECTDRAW7			pDD	 = NULL;
    LPDIRECT3D7				pD3D = NULL;
	DXG_ENUM_DEVICEINFO		stDXGEnumDeviceInfo;
    HRESULT					hr;

    if ( FAILED(hr = DirectDrawCreateEx(NULL, (VOID**) &pDD, IID_IDirectDraw7, NULL)) )
	{
		MessageBox(NULL, TEXT("[DXGDriverEnumCallbackEx]") TEXT("Can't create DDraw during enumeration!"), "MirDXG", MB_ICONERROR | MB_OK);
        return D3DENUMRET_OK;
	}

    if ( FAILED(hr = pDD->QueryInterface(IID_IDirect3D7, (VOID**) &pD3D)) )
    {
		SAFE_RELEASE(pDD);
		MessageBox(NULL, TEXT("[DXGDriverEnumCallbackEx]") TEXT("Can't query IDirect3D7 during enumeration!"), "MirDXG", MB_ICONERROR | MB_OK);
        return D3DENUMRET_OK;
    }

    ZeroMemory(&stDXGEnumDeviceInfo, sizeof(DXG_ENUM_DEVICEINFO));
    lstrcpyn(stDXGEnumDeviceInfo.szDriverDesc, szDesc, 255);

    stDXGEnumDeviceInfo.ddDriverCaps.dwSize = sizeof(DDCAPS);
    stDXGEnumDeviceInfo.ddHELCaps.dwSize    = sizeof(DDCAPS);
    pDD->GetCaps(&stDXGEnumDeviceInfo.ddDriverCaps, &stDXGEnumDeviceInfo.ddHELCaps);

    if ( pGUID )
    {
        stDXGEnumDeviceInfo.guidDriver  = (*pGUID);
        stDXGEnumDeviceInfo.pDriverGUID = &stDXGEnumDeviceInfo.guidDriver;
    }

    if ( FAILED(hr = pDD->EnumDisplayModes(0, NULL, &stDXGEnumDeviceInfo, DXGEnumDisplayModeCallback)) )
	{
		MessageBox(NULL, TEXT("[DXGDriverEnumCallbackEx]") TEXT("Can't enumerate displaymode!"), "MirDXG", MB_ICONERROR | MB_OK);
	}

    qsort(stDXGEnumDeviceInfo.pddsdModes, stDXGEnumDeviceInfo.dwNumModes, sizeof(DDSURFACEDESC2), DXGModesSortCallback);

    if ( FAILED(hr = pD3D->EnumDevices(DXG3DDeviceEnumCallback, &stDXGEnumDeviceInfo)) )
	{
		MessageBox(NULL, TEXT("[DXGDriverEnumCallbackEx]") TEXT("Can't enumerate device!"), "MirDXG", MB_ICONERROR | MB_OK);
	}

    SAFE_DELETE(stDXGEnumDeviceInfo.pddsdModes);
	SAFE_RELEASE(pD3D);
	SAFE_RELEASE(pDD);

	return DDENUMRET_OK;
}


/******************************************************************************************************************

	�Լ��� : WINAPI DXGEnumDisplayModeCallback()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : DDSURFACEDESC2* pddsd
	         VOID* pParentInfo
	���   : static HRESULT 

	[����][������] : ��������

*******************************************************************************************************************/
static HRESULT WINAPI DXGEnumDisplayModeCallback(DDSURFACEDESC2* pddsd, VOID* pParentInfo)
{
    DXG_ENUM_DEVICEINFO* pDevice = (DXG_ENUM_DEVICEINFO*) pParentInfo;

    DDSURFACEDESC2* pddsdNewModes = new DDSURFACEDESC2[pDevice->dwNumModes+1];
    memcpy(pddsdNewModes, pDevice->pddsdModes, pDevice->dwNumModes * sizeof(DDSURFACEDESC2));
//    SAFE_DELETE(pDevice->pddsdModes);
	delete pDevice->pddsdModes;
    pDevice->pddsdModes = pddsdNewModes;

    pDevice->pddsdModes[pDevice->dwNumModes++] = (*pddsd);

    return DDENUMRET_OK;
}


/******************************************************************************************************************

	�Լ��� : DXGModesSortCallback()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : const VOID* arg1
	         const VOID* arg2
	���   : static int 

	[����][������] : ��������

*******************************************************************************************************************/
static int DXGModesSortCallback(const VOID* arg1, const VOID* arg2)
{
    DDSURFACEDESC2* p1 = (DDSURFACEDESC2*)arg1;
    DDSURFACEDESC2* p2 = (DDSURFACEDESC2*)arg2;

    if ( p1->dwWidth < p2->dwWidth )        return -1;
    if ( p1->dwWidth > p2->dwWidth )        return +1;

    if ( p1->dwHeight < p2->dwHeight )      return -1;
    if ( p1->dwHeight > p2->dwHeight )      return +1;

    if ( p1->ddpfPixelFormat.dwRGBBitCount < p2->ddpfPixelFormat.dwRGBBitCount )        return -1;
    if ( p1->ddpfPixelFormat.dwRGBBitCount > p2->ddpfPixelFormat.dwRGBBitCount )        return +1;

    return 0;
}


/******************************************************************************************************************

	�Լ��� : WINAPI DXG3DDeviceEnumCallback()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : TCHAR* szDesc
	         TCHAR* szName
	         D3DDEVICEDESC7* pDesc
	         VOID* pParentInfo
	���   : static HRESULT 

	[����][������] : ��������

*******************************************************************************************************************/
static HRESULT WINAPI DXG3DDeviceEnumCallback(TCHAR* szDesc, TCHAR* szName, D3DDEVICEDESC7* pDesc, VOID* pParentInfo)
{
    DXG_ENUM_DEVICEINFO* pDriverInfo = (DXG_ENUM_DEVICEINFO*)pParentInfo;
    DXG_ENUM_DEVICEINFO* pDeviceInfo = &g_stDXGEnumDeviceInfo[g_bNumDevices];
    ZeroMemory(pDeviceInfo, sizeof(DXG_ENUM_DEVICEINFO));

    pDeviceInfo->f3DHardware = pDesc->dwDevCaps & D3DDEVCAPS_HWRASTERIZATION;
    memcpy(&pDeviceInfo->ddDeviceDesc, pDesc, sizeof(D3DDEVICEDESC7));

    pDeviceInfo->ddDriverCaps       = pDriverInfo->ddDriverCaps;
    pDeviceInfo->ddHELCaps          = pDriverInfo->ddHELCaps;
    pDeviceInfo->guidDevice         = pDesc->deviceGUID;
    pDeviceInfo->pDeviceGUID        = &pDeviceInfo->guidDevice;
    pDeviceInfo->pddsdModes         = new DDSURFACEDESC2[pDriverInfo->dwNumModes];

    if ( pDriverInfo->pDriverGUID )
    {
        pDeviceInfo->guidDriver  = pDriverInfo->guidDriver;
        pDeviceInfo->pDriverGUID = &pDeviceInfo->guidDriver;
    }
    else
    {
        pDeviceInfo->pDriverGUID = NULL;
    }
    lstrcpyn(pDeviceInfo->szDriverDesc, pDriverInfo->szDriverDesc, 255);
    lstrcpyn(pDeviceInfo->szDeviceDesc, szName, 255);

    for ( DWORD dwCnt=0; dwCnt<pDriverInfo->dwNumModes; dwCnt++ )
    {
        DDSURFACEDESC2 ddsdMode = pDriverInfo->pddsdModes[dwCnt];
        DWORD dwRenderDepths    = pDeviceInfo->ddDeviceDesc.dwDeviceRenderBitDepth;
        DWORD dwDepth           = ddsdMode.ddpfPixelFormat.dwRGBBitCount;

        if ( ( ( dwDepth == 32 ) && ( dwRenderDepths & DDBD_32 ) ) ||
             ( ( dwDepth == 24 ) && ( dwRenderDepths & DDBD_24 ) ) ||
             ( ( dwDepth == 16 ) && ( dwRenderDepths & DDBD_16 ) ) )
        {
            pDeviceInfo->pddsdModes[pDeviceInfo->dwNumModes++] = ddsdMode;
        }
    }

    if ( 0 == pDeviceInfo->dwNumModes )
        return D3DENUMRET_OK;

    g_bNumDevices++;
    if ( NULL != pDeviceInfo->pDriverGUID && FALSE == pDeviceInfo->f3DHardware )
            return D3DENUMRET_OK;

    return D3DENUMRET_OK;
}


/******************************************************************************************************************

	�Լ��� : WINAPI DXGEnumZBufferFormatsCallback()

	�ۼ��� : 
	�ۼ��� : 

	����   : 
	�Է�   : DDPIXELFORMAT* pddpf
	         VOID* pContext
	���   : static HRESULT 

	[����][������] : ��������

*******************************************************************************************************************/
static HRESULT WINAPI DXGEnumZBufferFormatsCallback(DDPIXELFORMAT* pddpf, VOID* pContext)
{
    DDPIXELFORMAT* pddpfOut = (DDPIXELFORMAT*) pContext;

    if ( pddpfOut->dwRGBBitCount == pddpf->dwRGBBitCount )
    {
        (*pddpfOut) = (*pddpf);
        return D3DENUMRET_CANCEL;
    }

    return D3DENUMRET_OK;
}
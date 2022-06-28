#include "stdafx.h"
//#include <list.h> // ORZLIST


#ifdef _DEBUG
static int g_nCachedMemory;
#endif


#define MAX_LISTCOUNT			200

#define _MODE_NONE				255
#define _MODE_CACHE				0
#define _MODE_MEMMAP			1
#define _MODE_MEMLOAD			2

#define _VER_SIZE				sizeof(LONG)


static int						g_nLastTick;
static CWHWilImageData *		g_listImage[MAX_LISTCOUNT];
static int						g_nListCount;


void CWHWilImageData::CheckAllCachedImage()
{
	if ( GetTickCount() - g_nLastTick > WILCACHE_CHECKALLTIME )
	{
		for ( int i = 0; i < g_nListCount; i++ )
		{
			if ( g_listImage[i]->m_bCacheMode == _MODE_CACHE )
			{
				g_listImage[i]->FreeOldImages();
			}
		}
	
		g_nLastTick = GetTickCount();
	}
}


CWHWilImageData::CWHWilImageData()
{
	Init();
	// 현재 이미지 노드 추가
#ifdef _DEBUG
	if ( g_nListCount >= MAX_LISTCOUNT )
	{
		MessageBox( NULL, 
					"야옹야옹~~\n\nWHWilImage.cpp 파일 안의 MAX_LISTCOUNT 값을 변경해주세요.",
					"야옹이",
					MB_ICONINFORMATION );
	}
#endif
	g_listImage[ g_nListCount++ ] = this;
}


CWHWilImageData::~CWHWilImageData()
{	
	Destroy();

	// 현재 이미지 노드 삭제
	for ( int i = 0; i < MAX_LISTCOUNT; i++ )
	{
		if ( g_listImage[i] == this )
		{
			memmove( &g_listImage[i], &g_listImage[i + 1], 4 * (g_nListCount - i - 1) );
			g_nListCount--;
		}
	}
}


void CWHWilImageData::Init()
{
	m_bCacheMode				= _MODE_NONE;
	m_hWilFile					= INVALID_HANDLE_VALUE;
	m_pIndexList				= NULL;
	m_nLastCheckTime			= NULL;
	m_nIndexCount				= 0;

	m_pbStartData				= NULL;
	m_lpstNewCurrWilImageInfo	= NULL;
	m_pbCurrImage				= NULL;
	m_szWilFileName[0]			= NULL;

	m_bNewVer					= FALSE;

	memset( &m_WixInfo, 0, sizeof( m_WixInfo ) );
}


void CWHWilImageData::Destroy()
{
	m_szWilFileName[0]			= '\0';
	m_lpstNewCurrWilImageInfo	= NULL;
	m_pbCurrImage				= NULL;
	
	if ( m_bCacheMode == _MODE_CACHE )
	{
		m_nLastCheckTime = 0;
		
		if ( m_pIndexList )
		{
			sWilImageIndex *pObj;
			
			for ( int i = 0; i < m_nIndexCount; i++ )
			{
				pObj = &m_pIndexList[i];
				
				if ( pObj->pData )
				{
					delete[] pObj->pData;
					pObj->pData = NULL;
				}
			}
			
			delete[] m_pIndexList;
			m_pIndexList = NULL;
		}
		m_nIndexCount = 0;
		
		if ( m_hWilFile != INVALID_HANDLE_VALUE )
		{
			CloseHandle( m_hWilFile );
			m_hWilFile = INVALID_HANDLE_VALUE;
		}
	}
	else if ( m_bCacheMode == _MODE_MEMMAP )
	{
		if ( m_pbStartData )
		{
			UnmapViewOfFile( m_pbStartData );
			m_pbStartData = NULL;
		}

		if ( m_WixInfo.pnPosition )
		{
			delete[] m_WixInfo.pnPosition;
			m_WixInfo.pnPosition = NULL;
		}

		memset( &m_WixInfo, 0, sizeof( m_WixInfo ) );
	}
	else if ( m_bCacheMode == _MODE_MEMLOAD )
	{		
		if ( m_pbStartData )
		{
			SAFE_DELETEARR(m_pbStartData);
		}

		if ( m_WixInfo.pnPosition )
		{
			delete[] m_WixInfo.pnPosition;
			m_WixInfo.pnPosition = NULL;
		}

		memset( &m_WixInfo, 0, sizeof( m_WixInfo ) );
	}

	Init();
}


BOOL CWHWilImageData::NewLoad( char *pWilPath, BYTE bCacheMode )
{
	Init();

	if ( bCacheMode == _MODE_CACHE )
	{
		return NewLoad_Cache( pWilPath );
	}
	else if ( bCacheMode == _MODE_MEMMAP )
	{
		return NewLoad_MemoryMap( pWilPath );
	}
	else if ( bCacheMode == _MODE_MEMLOAD )
	{
		return NewLoad_MemLoad( pWilPath );
	}

	return FALSE;
}


BOOL CWHWilImageData::NewSetIndex( DWORD nIndex )
{
	if ( m_bCacheMode == _MODE_CACHE )
	{
		return NewSetIndex_Cache( nIndex );
	}
	else if ( m_bCacheMode == _MODE_MEMMAP || m_bCacheMode == _MODE_MEMLOAD )
	{
		return NewSetIndex_Load( nIndex );
	}

	return FALSE;
}


LONG CWHWilImageData::GetVersion(BYTE bFileKind, INT nImgCnt)
{	
	LONG lRet = 0;

	if ( bFileKind == 0 )		// Wil
	{
		lRet = (_WIL_VER + nImgCnt) |  _WIL_MAGIC_CODE;
	}
	else	// Wix
	{
		lRet = (_WIX_VER + nImgCnt) |  _WIX_MAGIC_CODE;
	}

	return lRet;
}

BOOL CWHWilImageData::NewLoad_Cache( char *pWilPath )
{
	m_bCacheMode = _MODE_CACHE;

	// 스택 변수 선언
	char			szWixPath[MAX_PATH];
	HANDLE			hWixFile;	
	DWORD			nReadLen;
	NEWWIXIMAGEINFO	WixInfo;

	// Wix 파일 열기
	strcpy( m_szWilFileName, pWilPath );
	strcpy( szWixPath, pWilPath );
	strcpy( szWixPath + strlen( szWixPath ) - 3, "wix" );
	hWixFile = CreateFile( szWixPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	if ( hWixFile == INVALID_HANDLE_VALUE )
	{
		return FALSE;
	}

	// Wix 헤더 열기.
	ReadFile( hWixFile, &WixInfo, sizeof( WixInfo ) - 4, &nReadLen, NULL );

	// Wil 파일 열기.
	m_hWilFile = CreateFile( pWilPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	if ( m_hWilFile == INVALID_HANDLE_VALUE )
	{
		CloseHandle( hWixFile );
		return FALSE;
	}

	WILFILEHEADER stWilHeader;
	LONG		  lVer = 0;

	ReadFile( m_hWilFile, &stWilHeader, sizeof(WILFILEHEADER), &nReadLen, NULL );

	if ( stWilHeader.shVer == _NEW_VER )
	{
		ReadFile( m_hWilFile, &lVer, sizeof(LONG), &nReadLen, NULL );
		if ( lVer != GetVersion(0, stWilHeader.nImageCount) )
		{
			CloseHandle( m_hWilFile );
			CloseHandle( hWixFile );
			return FALSE;
		}

		ReadFile( hWixFile, &lVer, sizeof(LONG), &nReadLen, NULL );
		if ( lVer != GetVersion(1, stWilHeader.nImageCount) )
		{
			CloseHandle( m_hWilFile );
			CloseHandle( hWixFile );
			return FALSE;
		}

		m_bNewVer = TRUE;
	}

	m_nIndexCount	= WixInfo.nIndexCount;
	m_pIndexList	= new sWilImageIndex[ m_nIndexCount ];
	if ( !m_pIndexList )
	{
		delete[] m_pIndexList;
		m_pIndexList = NULL;
		CloseHandle( m_hWilFile );
		CloseHandle( hWixFile );
		return FALSE;
	}

	memset( m_pIndexList, 0, sizeof( sWilImageIndex ) * m_nIndexCount );

	for ( int i = 0; i < m_nIndexCount; i++ )
	{
		ReadFile( hWixFile, &m_pIndexList[i].nPosition, 4, &nReadLen, NULL );
	}

	CloseHandle( hWixFile );
	
	return TRUE;
}


BOOL CWHWilImageData::NewLoad_MemoryMap( char *pWilPath )
{	
	m_bCacheMode = _MODE_MEMMAP;

	char			szWixPath[MAX_PATH];
	HANDLE			hWixFile;	
	HANDLE			hFile;	
	DWORD			nReadLen;

	// Wix 파일 열기
	strcpy( m_szWilFileName, pWilPath );
	strcpy( szWixPath, pWilPath );
	strcpy( szWixPath + strlen( szWixPath ) - 3, "wix" );
	hWixFile = CreateFile( szWixPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	if ( hWixFile == INVALID_HANDLE_VALUE )
	{
		return FALSE;
	}

	// Wix 헤더 열기.
	ReadFile( hWixFile, &m_WixInfo, sizeof( m_WixInfo ) - 4, &nReadLen, NULL );

	// Wil 파일 열기.
	hFile = CreateFile( pWilPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	if ( hFile == INVALID_HANDLE_VALUE )
	{
		memset( &m_WixInfo, 0, sizeof( m_WixInfo ) );
		CloseHandle( hWixFile );
		return FALSE;
	}

	WILFILEHEADER stWilHeader;
	LONG		  lVer = 0;

	ReadFile( hFile, &stWilHeader, sizeof(WILFILEHEADER), &nReadLen, NULL );

	if ( stWilHeader.shVer == _NEW_VER )
	{
		ReadFile( hFile, &lVer, sizeof(LONG), &nReadLen, NULL );
		if ( lVer != GetVersion(0, stWilHeader.nImageCount) )
		{
			memset( &m_WixInfo, 0, sizeof( m_WixInfo ) );
			CloseHandle( hWixFile );
			CloseHandle( hFile );
			return FALSE;
		}

		ReadFile( hWixFile, &lVer, sizeof(LONG), &nReadLen, NULL );
		if ( lVer != GetVersion(1, stWilHeader.nImageCount) )
		{
			memset( &m_WixInfo, 0, sizeof( m_WixInfo ) );
			CloseHandle( hWixFile );
			CloseHandle( hFile );
			return FALSE;
		}

		m_bNewVer = TRUE;
	}

	// Wix 헤더 열고 인덱스 리스트 초기화
	m_WixInfo.pnPosition = new INT[ m_WixInfo.nIndexCount ];
	if ( !m_WixInfo.pnPosition )
	{
		m_WixInfo.pnPosition = NULL;
		CloseHandle( hFile );
		CloseHandle( hWixFile );
		return FALSE;
	}

	ReadFile( hWixFile, m_WixInfo.pnPosition, 4 * m_WixInfo.nIndexCount, &nReadLen, NULL );

	// 메모리 맵 포인터 저장
	HANDLE hMap = CreateFileMapping( hFile, NULL, PAGE_READONLY, NULL, NULL, NULL );
	if ( hMap == NULL )
	{
		memset( &m_WixInfo, 0, sizeof( m_WixInfo ) );
		CloseHandle( hWixFile );
		CloseHandle( hFile );
		return FALSE;
	}
	
	m_pbStartData = (BYTE *) MapViewOfFile( hMap, FILE_MAP_READ, NULL, NULL, NULL );
	CloseHandle( hMap );
	CloseHandle( hFile );
	CloseHandle( hWixFile );

	if ( !m_pbStartData )
	{
		memset( &m_WixInfo, 0, sizeof( m_WixInfo ) );
		return FALSE;
	}

	return TRUE;
}


BOOL CWHWilImageData::NewLoad_MemLoad( char *pWilPath )
{	
	m_bCacheMode = _MODE_MEMLOAD;

	char			szWixPath[MAX_PATH];
	HANDLE			hWixFile;	
	HANDLE			hFile;	
	DWORD			nReadLen;
	NEWWIXIMAGEINFO	WixInfo;

	// Wix 파일 열기
	strcpy( m_szWilFileName, pWilPath );
	strcpy( szWixPath, pWilPath );
	strcpy( szWixPath + strlen( szWixPath ) - 3, "wix" );
	hWixFile = CreateFile( szWixPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	if ( hWixFile == INVALID_HANDLE_VALUE )
	{
		return FALSE;
	}

	// Wix 헤더 열기.
	ReadFile( hWixFile, &WixInfo, sizeof( WixInfo ) - 4, &nReadLen, NULL );

	// Wil 파일 열기.
	hFile = CreateFile( pWilPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	if ( hFile == INVALID_HANDLE_VALUE )
	{
		CloseHandle(hWixFile);
		return FALSE;
	}

	WILFILEHEADER stWilHeader;
	LONG		  lVer = 0;

	ReadFile( hFile, &stWilHeader, sizeof(WILFILEHEADER), &nReadLen, NULL );

	if ( stWilHeader.shVer == _NEW_VER )
	{
		ReadFile( hFile, &lVer, sizeof(LONG), &nReadLen, NULL );
		if ( lVer != GetVersion(0, stWilHeader.nImageCount) )
		{
			CloseHandle(hFile);
			CloseHandle(hWixFile);
			return FALSE;
		}

		ReadFile( hWixFile, &lVer, sizeof(LONG), &nReadLen, NULL );
		if ( lVer != GetVersion(1, stWilHeader.nImageCount) )
		{
			CloseHandle(hFile);
			CloseHandle(hWixFile);
			return FALSE;
		}

		m_bNewVer = TRUE;
	}
	
	m_WixInfo.pnPosition = new INT[m_WixInfo.nIndexCount];
	if ( !m_WixInfo.pnPosition )
	{
		m_WixInfo.pnPosition = NULL;
		CloseHandle( hWixFile );
		CloseHandle( hFile );
		return FALSE;
	}

	ReadFile(hWixFile, m_WixInfo.pnPosition, sizeof(INT)*m_WixInfo.nIndexCount, &nReadLen, NULL);

	DWORD dwFileSize;
	dwFileSize = GetFileSize(hFile, NULL);
	m_pbStartData = new BYTE[dwFileSize];
	ReadFile(hFile, m_pbStartData, dwFileSize, &nReadLen, NULL);

	NewSetIndex_Load(0);						// 0번 인덱스로 세팅한다.

	CloseHandle(hFile);
	CloseHandle(hWixFile);

	return TRUE;
}


BOOL CWHWilImageData::NewSetIndex_Cache( DWORD nIndex )
{	
//	_ASSERT( nIndex >= 0 && nIndex < (DWORD) m_nIndexCount );
	if ( nIndex < 0 || nIndex >= (DWORD) m_nIndexCount )
	{
		return FALSE;
	}

	m_pbCurrImage = NULL;

	sWilImageIndex *pObj = &m_pIndexList[ nIndex ];

	if ( !pObj->nPosition )
	{
		return FALSE;
	}

	if ( pObj->Header.shWidth > 4096 || pObj->Header.shHeight > 4096 )
	{
		return FALSE;
	}

	// 할당되지 않은 메모리라면
	if ( !pObj->pData )
	{
		SetFilePointer( m_hWilFile, pObj->nPosition, 0, FILE_BEGIN );

		DWORD nReadLen;
		ReadFile( m_hWilFile, &pObj->Header, sizeof( pObj->Header ), &nReadLen, NULL );

		pObj->pData = new BYTE[ pObj->Header.dwImageLength * 2 ];
		if ( !pObj->pData )
		{
			return FALSE;
		}

		if ( m_bNewVer )
		{
			SetFilePointer( m_hWilFile, pObj->nPosition+sizeof( pObj->Header )+_VER_SIZE, 0, FILE_BEGIN );
		}

		ReadFile( m_hWilFile, pObj->pData, pObj->Header.dwImageLength * 2, &nReadLen, NULL );
	}

	// 접근 시간 갱신
	pObj->nLastTick = GetTickCount();
	
	// 인덱스 대입
	m_lpstNewCurrWilImageInfo	= &pObj->Header;
	m_pbCurrImage				= pObj->pData;

	// 지정된 시간만큼 사용되지 않은 이미지 메모리를 해제한다.
	if ( GetTickCount() - m_nLastCheckTime >= WILCACHE_CHECKTIME )
	{
		FreeOldImages();
		m_nLastCheckTime = GetTickCount();
	}

	return TRUE;
}


BOOL CWHWilImageData::NewSetIndex_Load( DWORD nIndex )
{
//	_ASSERT( nIndex >= 0 && nIndex < (DWORD) m_WixInfo.nIndexCount );
	if ( nIndex < 0 || nIndex >= (DWORD) m_WixInfo.nIndexCount )
	{
		return FALSE;
	}

	m_pbCurrImage = NULL;

	if ( !m_WixInfo.pnPosition[nIndex] )
	{
		return FALSE;
	}

	m_lpstNewCurrWilImageInfo = (NEWWILIMAGEINFO *) (m_pbStartData + m_WixInfo.pnPosition[nIndex]);

	if ( m_lpstNewCurrWilImageInfo->shWidth > 4096 || m_lpstNewCurrWilImageInfo->shHeight > 4096 )
	{
		return FALSE;
	}

	m_pbCurrImage = (BYTE *) m_lpstNewCurrWilImageInfo + sizeof( NEWWILIMAGEINFO );

	if ( m_bNewVer )
	{
		m_pbCurrImage += _VER_SIZE;
	}

	return TRUE;
}


void CWHWilImageData::FreeOldImages()
{
	sWilImageIndex *pObj;

	for ( int i = 0; i < m_nIndexCount; i++ )
	{
		pObj = &m_pIndexList[i];

		if ( pObj && pObj->pData && (GetTickCount() - pObj->nLastTick >= WILCACHE_SAVETIME) )
		{			
			delete[] pObj->pData;
			pObj->pData = NULL;		
		}
	}
}
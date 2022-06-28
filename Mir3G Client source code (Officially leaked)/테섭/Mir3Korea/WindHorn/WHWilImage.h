

/**********************************************************************************
	CWHWilImageData 클래스 (Cached Image Version)

	<NewLoad, NewSetIndex>
	- 속도를 위하 ReadFile, SetFilePointer의 리턴 값 검사를 하지 않는다.
***********************************************************************************/
#pragma once


#ifdef _DEBUG
	// 전체 오브젝트의 인덱스 리스트 검사 주기
	#define WILCACHE_CHECKALLTIME	100000
	// 현재 오브젝트의 인덱스 리스트 검사 주기	
	#define WILCACHE_CHECKTIME		15000	
	// 이 시간이 지나면 인덱스를 삭제한다.
	#define WILCACHE_SAVETIME		300000
#else
	// 전체 오브젝트의 인덱스 리스트 검사 주기
	#define WILCACHE_CHECKALLTIME	100000
	// 현재 오브젝트의 인덱스 리스트 검사 주기	
	#define WILCACHE_CHECKTIME		15000	
	// 이 시간이 지나면 인덱스를 삭제한다.
	#define WILCACHE_SAVETIME		300000
#endif

#define _OLD_VER		17
#define _NEW_VER		5000
#define _WIL_VER		20020
#define _WIX_VER		20021
#define _WIL_MAGIC_CODE	0XC02A1173
#define _WIX_MAGIC_CODE	0XB13A11F0

/**********************************************************************************
	Image Structures
***********************************************************************************/
#pragma pack(1)
typedef struct tagNEWWILFILEIMAGEINFO
{
	SHORT	shWidth;
	SHORT	shHeight;
	SHORT	shPX;
	SHORT	shPY;
	CHAR	bShadow;					
	SHORT	shShadowPX;
	SHORT	shShadowPY;
	DWORD	dwImageLength;
}NEWWILIMAGEINFO, *LPNEWWILIMAGEINFO;

typedef struct tagWILFILEHEADER
{
	SHORT	shComp;
	CHAR	szTitle[20];
	SHORT	shVer;
	INT		nImageCount;
}WILFILEHEADER, *LPWILFILEHEADER;

typedef struct tagNEWWIXFILEIMAGEINFO
{
	CHAR	szTitle[20];
	INT		nIndexCount;
	INT*	pnPosition;
}NEWWIXIMAGEINFO, *LPNEWWIXIMAGEINFO;
#pragma pack(8)



/**********************************************************************************
	Image Class
***********************************************************************************/
class CWHWilImageData
{
public:
	struct sWilImageIndex
	{
		int				nLastTick;
		int				nPosition;
		NEWWILIMAGEINFO	Header;
		BYTE			*pData;
	};

public:
	BYTE				m_bCacheMode;

	BOOL				m_bNewVer;

	// 캐쉬 멤버
	HANDLE				m_hWilFile;
	sWilImageIndex *	m_pIndexList;
	int					m_nIndexCount;
	DWORD				m_nLastCheckTime;

	// 메모리 맵 멤버
	NEWWIXIMAGEINFO		m_WixInfo;
	BYTE *				m_pbStartData;

	//
	// 공통 멤버
	//
	NEWWILIMAGEINFO *	m_lpstNewCurrWilImageInfo;
	BYTE *				m_pbCurrImage;
	char				m_szWilFileName[MAX_PATH];

public:
	static void CheckAllCachedImage();

	CWHWilImageData();
	virtual ~CWHWilImageData();

	void Init();
	void Destroy();

	BOOL NewLoad( char *pWilPath, BYTE bCacheMode = 0 );
	BOOL NewSetIndex( DWORD nIndex );

protected:
	LONG GetVersion(BYTE bFileKind, INT nImgCnt);

	BOOL NewLoad_Cache( char *pWilPath );
	BOOL NewLoad_MemoryMap( char *pWilPath );
	BOOL NewLoad_MemLoad( char *pWilPath );

	BOOL NewSetIndex_Cache( DWORD nIndex );
	BOOL NewSetIndex_Load( DWORD nIndex );
		
	void FreeOldImages();
};


/**********************************************************************************
	CWHWilImageData Ŭ���� (Cached Image Version)

	<NewLoad, NewSetIndex>
	- �ӵ��� ���� ReadFile, SetFilePointer�� ���� �� �˻縦 ���� �ʴ´�.
***********************************************************************************/
#pragma once


#ifdef _DEBUG
	// ��ü ������Ʈ�� �ε��� ����Ʈ �˻� �ֱ�
	#define WILCACHE_CHECKALLTIME	100000
	// ���� ������Ʈ�� �ε��� ����Ʈ �˻� �ֱ�	
	#define WILCACHE_CHECKTIME		15000	
	// �� �ð��� ������ �ε����� �����Ѵ�.
	#define WILCACHE_SAVETIME		300000
#else
	// ��ü ������Ʈ�� �ε��� ����Ʈ �˻� �ֱ�
	#define WILCACHE_CHECKALLTIME	100000
	// ���� ������Ʈ�� �ε��� ����Ʈ �˻� �ֱ�	
	#define WILCACHE_CHECKTIME		15000	
	// �� �ð��� ������ �ε����� �����Ѵ�.
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

	// ĳ�� ���
	HANDLE				m_hWilFile;
	sWilImageIndex *	m_pIndexList;
	int					m_nIndexCount;
	DWORD				m_nLastCheckTime;

	// �޸� �� ���
	NEWWIXIMAGEINFO		m_WixInfo;
	BYTE *				m_pbStartData;

	//
	// ���� ���
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
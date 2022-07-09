#include "StdAfx.h"



CWHWilImageData::CWHWilImageData()
{
	Init();
}


CWHWilImageData::~CWHWilImageData()
{
	Destroy();
}


VOID CWHWilImageData::Init()
{
	m_bIsMemMapped		= FALSE;
	m_bIsCompressed		= FALSE;
	m_pbStartData		= NULL;	

	ZeroMemory(&m_stNewWixImgaeInfo, sizeof(WIXIMAGEINFO));

	ZeroMemory(&m_szWilFileName, sizeof(MAX_PATH));

	m_nCurrImageIdx		= -1;								// 초기 세팅치가 설정되지 않은상태.
	m_pbCurrImage		= NULL;
	m_lpstCurrWilImageInfo = NULL;

	m_lpstNewCurrWilImageInfo = NULL;
}


VOID CWHWilImageData::Destroy()
{
	if ( m_pbStartData ) 
	{
		if ( m_bIsMemMapped )
		{
			UnmapViewOfFile(m_pbStartData);
			m_pbStartData = NULL;
			m_bIsMemMapped = FALSE;
		}
		else
		{
			SAFE_DELETE(m_pbStartData);
		}
	}


	SAFE_DELETE(m_stNewWixImgaeInfo.pnPosition);
	ZeroMemory(&m_stNewWixImgaeInfo, sizeof(NEWWIXIMAGEINFO));

	Init();
}



BOOL CWHWilImageData::NewSetIndex(DWORD dwIndex)
{
	m_nCurrImageIdx = dwIndex;

	if ( (INT)dwIndex >= 0 && (INT)dwIndex < m_stNewWixImgaeInfo.nIndexCount )
	{
		int nPos;
		if ( m_bIsCompressed )
			nPos = m_stNewWixImgaeInfo.pnPosition[dwIndex+1];
		else
			nPos = m_stNewWixImgaeInfo.pnPosition[dwIndex];
	
		if( nPos == 0)
			return FALSE;

		BYTE* pbTmpData = (BYTE*)(m_pbStartData + nPos);

		m_lpstNewCurrWilImageInfo = (LPNEWWILIMAGEINFO)pbTmpData;
		m_pbCurrImage = (BYTE*)(pbTmpData + sizeof(NEWWILIMAGEINFO));

		return TRUE;
	}
	return FALSE;
}

int ValidateLength(int arg0, int nLen)
{
	int i = nLen;
	if( arg0 == 0 )
	{
		i += 20020;
		i |= 3223982451;
	}
	else
	{
        i += 20021;
        i |= 2973372912;
	}
	return i;
}

BOOL CWHWilImageData::NewLoad(CHAR* szWilFile, BOOL bComp)
{
	if( m_bIsMemMapped )
		return TRUE;

	m_bIsCompressed	= bComp;

	HANDLE	hWilFile;
	HANDLE	hWixFile;
	HANDLE	hWilMappedFile;
	DWORD	dwReadLen;
	CHAR	szWixFile[MAX_PATH];
	CHAR	szMsg[MAX_PATH];
	NEWWILFILEHEADER stNewWilFileHeader;


	strcpy(szWixFile, szWilFile);
	strcpy(szWixFile+strlen(szWixFile)-3, "wix");
	strcpy(m_szWilFileName, szWilFile);

	hWixFile= CreateFile(szWixFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if ( hWixFile != INVALID_HANDLE_VALUE )
	{
		ReadFile(hWixFile, &m_stNewWixImgaeInfo, sizeof(NEWWIXIMAGEINFO)-sizeof(INT)/*횅茄角0x16*/, &dwReadLen, NULL);

		m_stNewWixImgaeInfo.pnPosition = new INT[m_stNewWixImgaeInfo.nIndexCount];
		ReadFile(hWixFile, m_stNewWixImgaeInfo.pnPosition, sizeof(INT)*m_stNewWixImgaeInfo.nIndexCount, &dwReadLen, NULL);

		hWilFile = CreateFile(szWilFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );

		if ( hWilFile != INVALID_HANDLE_VALUE )
		{
			
			ReadFile(hWilFile, &stNewWilFileHeader, sizeof(NEWWILFILEHEADER), &dwReadLen, NULL);

			if ( dwReadLen )
			{
				hWilMappedFile = CreateFileMapping(hWilFile, NULL, PAGE_READONLY, NULL, NULL, NULL);

				m_pbStartData = (BYTE*)MapViewOfFile(hWilMappedFile, FILE_MAP_READ, NULL, NULL, NULL);

				if ( !m_pbStartData )
				{
					// Debug
					MessageBox(NULL, "CreateFileMapping Failed", "Mir2EX :: Error", MB_ICONERROR | MB_OK);
					CloseHandle(hWilFile);
					CloseHandle(hWixFile);
					m_bIsMemMapped = FALSE;
					return FALSE;
				}
				m_bIsMemMapped = TRUE;
				CloseHandle(hWilMappedFile);
			}
			else
			{
				DWORD dwFileSize;
				dwFileSize = GetFileSize(hWilFile, NULL);
				m_pbStartData = new BYTE[dwFileSize];
				ReadFile(hWilFile, m_pbStartData, dwFileSize, &dwReadLen, NULL);
			}

			NewSetIndex(0);						// 0번 인덱스로 세팅한다.
			CloseHandle(hWilFile);
			return TRUE;
		}

		wsprintf(szMsg, "Cannot find %s file", szWixFile);
		// Debug
		MessageBox(NULL, szMsg, "Mir2EX :: Error", MB_ICONERROR | MB_OK);
		CloseHandle(hWixFile);
		return FALSE;
	}

	wsprintf(szMsg, "Cannot find %s file\n", szWixFile);
	// Debug
//	MessageBox(NULL, szMsg, "Mir2EX :: Error", MB_ICONERROR | MB_OK);
	OutputDebugString(szMsg);

	return FALSE;

}

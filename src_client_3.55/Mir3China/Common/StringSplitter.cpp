

#include "StdAfx.h"

StringSplitter::StringSplitter()
{
	m_nMaxLine		= SPLT_MAXLINECOUNT;
	m_nLineWidth	= SPLT_MAXLINEWIDTH;

	m_nLineCount	= 0;
	memset( m_pLineArray, 0, sizeof( m_pLineArray ) );
}


StringSplitter::~StringSplitter()
{
	for ( int i = 0; i < m_nLineCount; i++ )
		delete[] m_pLineArray[i];
}


void StringSplitter::SetMaxLine( int nMaxLine )
{
	if ( nMaxLine > SPLT_MAXLINECOUNT )
		nMaxLine = SPLT_MAXLINECOUNT;

	m_nMaxLine = nMaxLine;
}

void StringSplitter::Reset()
{
	for ( int i = 0; i < m_nLineCount; i++ )
		delete[] m_pLineArray[i];

	m_nLineCount	= 0;
	memset( m_pLineArray, 0, sizeof( m_pLineArray ) );
}


void StringSplitter::SetLineWidth( int nLineWidth )
{
//	nLineWidth /= 5.98;

	if ( nLineWidth > SPLT_MAXLINEWIDTH )
		nLineWidth = SPLT_MAXLINEWIDTH;

	m_nLineWidth = nLineWidth;
}


int StringSplitter::Split( char *pBuffer, HFONT hFont )
{
	int nBufferWidth = strlen( pBuffer );

	HDC		hDC;
	HFONT	hOldFont;

	if ( NULL == hFont )
	{
		hFont = g_xMainWnd.m_hDefGameFont;
	}
	
	g_xMainWnd.GetBackBuffer()->GetDC(&hDC);
	hOldFont = (HFONT)SelectObject(hDC, hFont);	

	CHAR	szTemp[MAX_PATH*2];
	ZeroMemory(szTemp, MAX_PATH*2);

	INT		nCnt = 0;
	BOOL	bTwoByteUsing = FALSE;
	BOOL	bNoLine = FALSE;
	

	while ( nBufferWidth > 0 )
	{
		if ( m_nLineCount >= m_nMaxLine )
			break;

		SIZE sizeLen = {0, 0};

		GetTextExtentPoint32(hDC, szTemp, strlen(szTemp), &sizeLen);

		if ( sizeLen.cx >= m_nLineWidth ||  pBuffer[nCnt] == '\0' )
		{
			if ( bTwoByteUsing == TRUE )
			{
				m_pLineArray[ m_nLineCount ] = new char[ nCnt ];
				memset( m_pLineArray[ m_nLineCount ], 0, nCnt );

				memcpy( m_pLineArray[ m_nLineCount ], szTemp, nCnt - 1 );
				m_pLineArray[ m_nLineCount ][ nCnt - 1] = '\0';

				m_nLineCount++;
				ZeroMemory(szTemp, MAX_PATH*2);
				nBufferWidth -= (nCnt-1);
				pBuffer		 += nCnt-1;
				nCnt=0;
				bTwoByteUsing = !bTwoByteUsing;
				continue;
			}
			else
			{
				m_pLineArray[ m_nLineCount ] = new char[ nCnt + 1];
				memset( m_pLineArray[ m_nLineCount ], 0, nCnt + 1);

				memcpy( m_pLineArray[ m_nLineCount ], szTemp, nCnt  );
				m_pLineArray[ m_nLineCount ][ nCnt ] = '\0';

				m_nLineCount++;
				ZeroMemory(szTemp, MAX_PATH*2);
				nBufferWidth -= nCnt;
				pBuffer		 += nCnt;
				nCnt=0;
				continue;
			}
		}	
		else
		{
			if ( !bTwoByteUsing ) 
			{
				if ( pBuffer[nCnt] & 0x80)  // || bTwoByteUsing == TRUE )
				{
					bTwoByteUsing = true;  //!bTwoByteUsing;
					sprintf( &szTemp[nCnt], "%c", pBuffer[nCnt]);
					nCnt++;
				}
				else
				{
					sprintf( &szTemp[nCnt], "%c", pBuffer[nCnt]);
					nCnt++;
				}
			} 
			else 
			{
				bTwoByteUsing = false;
				sprintf( &szTemp[nCnt], "%c", pBuffer[nCnt]);
				nCnt++;
			}
			
		}
	}

	SelectObject(hDC, hOldFont);
	
	if ( hFont != g_xMainWnd.m_hDefGameFont )
	{
		DeleteObject(hFont);
		hFont = NULL;
	}

	g_xMainWnd.GetBackBuffer()->ReleaseDC(hDC);

	return m_nLineCount;

/*
		if ( bLastBuf )
		{
			m_pLineArray[ m_nLineCount ][ m_nLineWidth - 1] = '\0';
			pBuffer		 += m_nLineWidth - 1;
			nBufferWidth -= m_nLineWidth + 1;
		}
		else
		{
			m_pLineArray[ m_nLineCount ][ m_nLineWidth ] = '\0';
			pBuffer		 += m_nLineWidth;
			nBufferWidth -= m_nLineWidth;
		}

		nCnt++;
	}

/*
	while ( nBufferWidth > 0 )
	{
		if ( m_nLineCount >= m_nMaxLine )
			break;

		m_pLineArray[ m_nLineCount ] = new char[ m_nLineWidth + 1 ];
		memset( m_pLineArray[ m_nLineCount ], 0, m_nLineWidth + 1 );

		BOOL bLastBuf = FALSE;

		char test[MAX_PATH];

//		sprintf(&test[0], pBuffer[0]);


		GetTextExtentPoint32(hDC, szTmpCheck, strlen(szTmpCheck), &sizeLen);

		

		test[0] = pBuffer[0];

		for ( INT nI=0; nI< m_nLineWidth; nI++ )
		{
			if ( pBuffer[nI] & 0x80 )
			{
				if ( nI+1 == m_nLineWidth )
				{
					bLastBuf = TRUE;
				}
				else
				{
					m_pLineArray[ m_nLineCount ][nI] = pBuffer[nI];
//					sprintf( &m_pLineArray[ m_nLineCount ][nI], "%c", pBuffer[nI] );
					nI++;
					
					m_pLineArray[ m_nLineCount ][nI] = pBuffer[nI];
//					sprintf( &m_pLineArray[ m_nLineCount ][nI], pBuffer );
					
				}
			}
			else
			{
				m_pLineArray[ m_nLineCount ][nI] = pBuffer[nI];
//				sprintf( &m_pLineArray[ m_nLineCount ][nI], pBuffer );
				
			}
		}

		if ( bLastBuf )
		{
			m_pLineArray[ m_nLineCount ][ m_nLineWidth - 1] = '\0';
			pBuffer		 += m_nLineWidth - 1;
			nBufferWidth -= m_nLineWidth + 1;
		}
		else
		{
			m_pLineArray[ m_nLineCount ][ m_nLineWidth ] = '\0';
			pBuffer		 += m_nLineWidth;
			nBufferWidth -= m_nLineWidth;
		}

		m_nLineCount++;

/*
		if ( pBuffer[m_nLineWidth] & 0x80 )
		{
			memcpy( m_pLineArray[ m_nLineCount ], pBuffer, m_nLineWidth - 1 );
			m_pLineArray[ m_nLineCount ][ m_nLineWidth - 1] = '\0';
		
			m_nLineCount++;

			pBuffer		 += ( m_nLineWidth - 1); 
			nBufferWidth -= ( m_nLineWidth + 1);
		}
		else
		{
			memcpy( m_pLineArray[ m_nLineCount ], pBuffer, m_nLineWidth );
			m_pLineArray[ m_nLineCount ][ m_nLineWidth ] = '\0';
		
			m_nLineCount++;

			pBuffer		 += m_nLineWidth;
			nBufferWidth -= m_nLineWidth;
		}
*/
	
}




char * StringSplitter::operator []( int nArrayIndex )
{
	if ( nArrayIndex >= m_nLineCount )
		return NULL;

	return m_pLineArray[ nArrayIndex ];
}

int StringSplitter::GetLineCount()
{
	return m_nLineCount;
}

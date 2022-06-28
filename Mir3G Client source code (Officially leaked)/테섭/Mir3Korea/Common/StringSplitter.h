

#ifndef _STRINGSPLITTER_H
#define _STRINGSPLITTER_H


#define SPLT_MAXLINECOUNT	256
#define SPLT_MAXLINEWIDTH	800


class StringSplitter
{
private:
	// Input Variables
	int		m_nMaxLine;
	int		m_nLineWidth;

	// Output Variables
	int		m_nLineCount;
	char *	m_pLineArray[ SPLT_MAXLINECOUNT ];

public:
	StringSplitter();
	virtual ~StringSplitter();

	// Setting Variables
	void	SetMaxLine( int nMaxLine );
	void	SetLineWidth( int nLineWidth );

	// Core Function!
	int		Split( char *pBuffer , HFONT hFont = NULL );

	// Init();
	void	Reset();

public:
	int	 GetLineCount();	
	char * operator []( int nArrayIndex );
};

#endif // _STRINGSPLITTER_H



/*
	Vector (Dynamic Array)

	Date:
		2001/07/20 

	Note:
		User must call ClearAll() function if it is no longer needed.
*/
#ifndef __ORZ_DATASTRUCTURE_VECTOR__
#define __ORZ_DATASTRUCTURE_VECTOR__


template< class T >
class CVector
{
protected:
	T ** m_ppVectorArray;

	int  m_nCapacity;
	int  m_nIncrease;

public:
	CVector();
	CVector( int nCapacity, int nIncrease );
	virtual ~CVector();

	void ClearAll( bool bClearData = true, bool bDeleteArray = false );

	int  GetCapacity();
	int  GetIncrease();
	void SetIncrease( int nIncrease );

	bool Create( int nCapacity = -1, int nIncrease = -1 );
	bool Expand();

	inline	T *& operator[]( int nArray );
};


template< class T >
CVector< T >::CVector()
{
	m_ppVectorArray	= NULL;
	
	m_nCapacity		= 0;
	m_nIncrease		= 0;
}


template< class T >
CVector< T >::CVector( int nCapacity, int nIncrease )
{
	m_ppVectorArray	= NULL;
	
	m_nCapacity		= nCapacity;
	m_nIncrease		= nIncrease;

	Create();
}


template< class T >
CVector< T >::~CVector()
{
}


template< class T >
void CVector< T >::ClearAll( bool bClearData, bool bDeleteArray )
{
	if ( m_ppVectorArray )
	{
		if ( bClearData )
		{
			for ( int nIndex = 0; nIndex < m_nCapacity; nIndex++ )
			{
				if ( m_ppVectorArray[ nIndex ] )
				{
					if ( bDeleteArray )
						delete[] m_ppVectorArray[ nIndex ];
					else
						delete m_ppVectorArray[ nIndex ];
				}
			}
		}

		HeapFree( GetProcessHeap(), 0, m_ppVectorArray );
		m_ppVectorArray	= NULL;
	}
}


template< class T >
int CVector< T >::GetCapacity()
{
	return m_nCapacity;
}


template< class T >
int CVector< T >::GetIncrease()
{
	return m_nIncrease;
}


template< class T >
void CVector< T >::SetIncrease( int nIncrease )
{
	m_nIncrease = nIncrease;
}


template< class T >
bool CVector< T >::Create( int nCapacity, int nIncrease )
{
	if ( m_ppVectorArray )
		return true;

	if ( nCapacity > 0 )
		m_nCapacity = nCapacity;

	if ( nIncrease > 0 )
		m_nIncrease = nIncrease;

	m_ppVectorArray = (T **) HeapAlloc( GetProcessHeap(), 
										HEAP_ZERO_MEMORY, 
 									    sizeof( T * ) * m_nCapacity );

	return m_ppVectorArray ? true : false;
}


template< class T >
bool CVector< T >::Expand()
{
	m_ppVectorArray = (T **) HeapReAlloc( GetProcessHeap(),
									      HEAP_ZERO_MEMORY,
										  m_ppVectorArray,
										  sizeof( T * ) *  (m_nCapacity + m_nIncrease) );

	return m_ppVectorArray ? m_nCapacity = m_nCapacity + m_nIncrease, true : false;
}


template< class T >
T *& CVector< T >::operator []( int nArray )
{
	return m_ppVectorArray[ nArray ];
}


#endif

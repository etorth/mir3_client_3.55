

/*
	A* Path Finding Algorithm

	Date:
		2002/02/25

	Note:
		클래스 T는 아래의 함수들을 구현하여야 한다.
		
		class T
		{
		public:
			int  GetGoalEstimate( T *pGoal );
			bool GetSuccessors( CAStar< T > *pFinder, T *pParent );
			int  GetCost( T *pState );

			bool IsSameState( T *pState );
			bool IsGoal( T *pState );
		};
*/
#ifndef __ORZ_ALGORITHM_ASTAR_PATH_FINDING__
#define __ORZ_ALGORITHM_ASTAR_PATH_FINDING__


#include "pqueue.h"
#include "list.h"


#define ASTAR_DEF_CAPACITY	100
#define ASTAR_DEF_INCREASE	100


template< class T > 
class CAStar
{
protected:
	class CNode
	{
	public:	
		CNode *pParent;
		CNode *pChild;

		T   state;		// 노드 데이터
		int	f, g, h;	// 이 노드의 비용(Cost) (f = g + h)

	public:
		CNode() 
		: pParent( NULL ), pChild( NULL ), f( 0 ), g( 0 ), h( 0 ) 
		{
		}
	};

public:
	int	  m_nState;
	int   m_nSteps;

	CNode *m_pStart;
	CNode *m_pGoal;
	CNode *m_pCurSolutionNode;

	CPriorityQueue< CNode >	m_openQueue;
	CList< CNode >			m_closedList;
	CList< CNode >			m_successors;

public:
	enum
	{
		SEARCH_STATE_NOT_INITIALIZED,
		SEARCH_STATE_SEARCHING,
		SEARCH_STATE_SUCCEEDED,
		SEARCH_STATE_FAILED,
		SEARCH_STATE_OUT_OF_MEMORY,
		SEARCH_STATE_INVALID
	};

	CAStar( int nCapacity = ASTAR_DEF_CAPACITY, int nIncrease = ASTAR_DEF_INCREASE );
	virtual ~CAStar();
	
	void ClearAll();
	void ClearUnusedNodes();
	void Reset();

	bool SetState( T *pStart, T *pGoal );
	int  SearchStep();
	bool AddSuccessor( T *pState );

	T *  GetPathFirst();
	T *  GetPathNext();
	int  GetStepCount();

protected:
	static int __cbCmpCost( void *pArg, CNode *pFirst, CNode *pSecond );
};


template< class T >
CAStar< T >::CAStar( int nCapacity, int nIncrease )
: m_openQueue( nCapacity, nIncrease )
{
	m_nState			= SEARCH_STATE_NOT_INITIALIZED;
	m_nSteps			= 0;
	m_pStart			= NULL;
	m_pGoal				= NULL;
	m_pCurSolutionNode	= NULL;

	m_openQueue.SetCompareFunction( __cbCmpCost, NULL );
}


template< class T >
CAStar< T >::~CAStar()
{
	ClearAll();
}


template< class T >
void CAStar< T >::ClearAll()
{
	if ( m_nState == SEARCH_STATE_SUCCEEDED )
	{
		if ( m_pStart->pChild )
		{
			CNode *pTemp;
			
			do
			{
				pTemp	 = m_pStart;
				m_pStart = m_pStart->pChild;
				delete pTemp;
				
			} while ( m_pStart != m_pGoal );
			
			delete m_pStart;
		}
		else
		{
			// 시작점이 목표지점이므로 시작/끝 노드만 지워준다.
			delete m_pStart;
			delete m_pGoal;
		}
	}
	else
	{
		m_openQueue.ClearAll();
		m_closedList.ClearAll();

		if ( m_pGoal )
			delete m_pGoal;
	}

	m_pStart = NULL;
	m_pGoal  = NULL;
	
	m_successors.ClearAll( false );
}


template< class T >
void CAStar< T >::ClearUnusedNodes()
{
	// OPEN 목록의 사용되지 않은 노드 삭제
	int openIndex;
	for ( openIndex = 0; openIndex < m_openQueue.GetCount(); openIndex++ )
	{
		if ( !m_openQueue[openIndex]->pChild )
			delete m_openQueue.DequeueIndex( openIndex-- );
	}

	m_openQueue.ClearAll( false );

	// CLOSED 목록의 사용되지 않은 노드 삭제
	CListNode< CNode > *pNode, *pTemp;
	for ( pNode = m_closedList.GetHead(); pNode; )
	{
		if ( !pNode->GetData()->pChild )
		{
			pTemp = pNode->GetNext();
			delete m_closedList.RemoveNode( pNode );
			pNode = pTemp;
			continue;
		}

		pNode = pNode->GetNext();
	}

	m_closedList.ClearAll( false );
}


template< class T >
void CAStar< T >::Reset()
{
	ClearAll();

	m_openQueue.ResetVector();
}


template< class T >
bool CAStar< T >::SetState( T *pStart, T *pGoal )
{
	if ( m_pStart || m_pGoal )
		Reset();

	m_pStart = new CNode;
	if ( !m_pStart )
		return false;

	m_pGoal  = new CNode;
	if ( !m_pGoal )
	{
		delete m_pStart;
		m_pStart = NULL;
		return false;
	}

	m_pStart->state = *pStart;
	m_pGoal ->state = *pGoal;

	m_nState = SEARCH_STATE_SEARCHING;
	m_nSteps = 0;

	// 시작점을 OPEN 목록에 추가
	m_pStart->g = 0;
	m_pStart->h = pStart->GetGoalEstimate( pGoal );
	m_pStart->f = m_pStart->g + m_pStart->h;
	
	m_openQueue.Enqueue( m_pStart );

	return true;
}


template< class T >
int CAStar< T >::SearchStep()
{
	if ( m_nState == SEARCH_STATE_NOT_INITIALIZED	||
		 m_nState == SEARCH_STATE_SUCCEEDED			|| 
		 m_nState == SEARCH_STATE_FAILED )
	{
		return m_nState;
	}

	// OPEN 노드가 하나도 없다는 것은 더이상 찾을 경로가 없다는 뜻이다.
	if ( !m_openQueue.GetCount() )
	{
		return m_nState = SEARCH_STATE_FAILED;
	}

	++m_nSteps;

	// 가장 유망한 노드를 꺼낸다. (f 값이 가장 낮은 노드)
	CNode *pNode = m_openQueue.Dequeue();

	if ( pNode->f > 250 )
	{
		// 사용되지 않은 노드(OPEN/CLOSED 리스트) 삭제
		ClearUnusedNodes();

		return m_nState = SEARCH_STATE_FAILED;
	}

	// 현재 노드가 목표지점이라면
	if ( pNode->state.IsGoal( &m_pGoal->state ) )
	{
		m_pGoal->pParent = pNode->pParent;

		// 경로를 역추적해서 완성한다.
		if ( pNode != m_pStart )
		{
			delete pNode;

			CNode *pNodeChild  = m_pGoal;
			CNode *pNodeParent = m_pGoal->pParent;

			do
			{
				pNodeParent->pChild = pNodeChild;

				pNodeChild  = pNodeParent;
				pNodeParent = pNodeParent->pParent;

			} while ( pNodeChild != m_pStart );
		}

		// 사용되지 않은 노드(OPEN/CLOSED 리스트) 삭제
		ClearUnusedNodes();

		return m_nState = SEARCH_STATE_SUCCEEDED;
	}

	// 이전 노드(Successor) 목록 해제
	m_successors.ClearAll( false );

	// 현재 노드의 Successor들을 얻어온다. (타일 기반이라면 인접한 타일들이다.)
	if ( !pNode->state.GetSuccessors( this, pNode->pParent ? &pNode->pParent->state : NULL ) )
	{
		delete pNode;
		m_successors.ClearAll( true );
		ClearAll();
		return m_nState = SEARCH_STATE_OUT_OF_MEMORY;
	}

	int g;			// cost G
	int openIndex;	// pqueue index
	CListNode< CNode > *pSuccessorNode, *pClosedNode, *pTemp;
	CNode *pSuccessor;
	
	// 얻어온 모든 노드(Successor)들을 조사한다.
	for ( pSuccessorNode = m_successors.GetHead(); pSuccessorNode; )
	{
		pSuccessor = pSuccessorNode->GetData();

		g = pNode->g + pNode->state.GetCost( &pSuccessor->state );

		// 이미 같은 노드가 존재하며 더 나은 결과가 아니라면 무시한다.
		for ( openIndex = 0; openIndex < m_openQueue.GetCount(); openIndex++ )
		{
			if ( m_openQueue[openIndex]->state.IsSameState( &pSuccessor->state ) )
				break;
		}

		if ( openIndex < m_openQueue.GetCount() )
		{
			if ( m_openQueue[openIndex]->g <= g )
			{
				pTemp = pSuccessorNode->GetNext();
				delete m_successors.RemoveNode( pSuccessorNode );
				pSuccessorNode = pTemp;
				continue;
			}

			// 더 나은 결과라면 이전 데이터를 삭제한다.	
			delete m_openQueue.DequeueIndex( openIndex );
		}

		// CLOSED 리스트 역시 같은 노드가 존재하는지 검사하여 처리한다.
		for ( pClosedNode = m_closedList.GetHead(); pClosedNode; pClosedNode = pClosedNode->GetNext() )
		{
			if ( pClosedNode->GetData()->state.IsSameState( &pSuccessor->state ) )
				break;
		}

		if ( pClosedNode )
		{
			if ( pClosedNode->GetData()->g <= g )
			{
				pTemp = pSuccessorNode->GetNext();
				delete m_successors.RemoveNode( pSuccessorNode );
				pSuccessorNode = pTemp;
				continue;
			}

			delete m_closedList.RemoveNode( pClosedNode );
		}

		// 여기까지 왔으면 현재 노드(Successor)가 지금까지의 가장 유망한 경로이다.
		pSuccessor->pParent	= pNode;
		pSuccessor->g		= g;
		pSuccessor->h		= pSuccessor->state.GetGoalEstimate( &m_pGoal->state );
		pSuccessor->f		= pSuccessor->g + pSuccessor->h;

		m_openQueue.Enqueue( pSuccessor );

		// 다음 노드(Successor)를 검사한다.
		pSuccessorNode = pSuccessorNode->GetNext();
	}

	// 처리된 노드는 CLOSED 목록에 집어넣는다.
	m_closedList.Insert( pNode );

	return m_nState;
}


// class T의 GetSuccessors 함수에서 이 함수를 호출해야 한다.
template< class T >
bool CAStar< T >::AddSuccessor( T *pState )
{
	CNode *pNode = new CNode;
	if ( !pNode )
		return false;

	pNode->state = *pState;
	m_successors.Insert( pNode );

	return true;
}


template< class T >
T * CAStar< T >::GetPathFirst()
{
	if ( !m_pStart )
		return NULL;

	m_pCurSolutionNode = m_pStart;

	return &m_pCurSolutionNode->state;
}


template< class T >
T * CAStar< T >::GetPathNext()
{
	if ( !m_pCurSolutionNode || !m_pCurSolutionNode->pChild )
		return NULL;

	T *pState = &m_pCurSolutionNode->pChild->state;

	m_pCurSolutionNode = m_pCurSolutionNode->pChild;

	return pState;
}


template< class T >
int CAStar< T >::GetStepCount()
{
	return m_nSteps;
}


template< class T >
int CAStar< T >::__cbCmpCost( void *pArg, CNode *pFirst, CNode *pSecond )
{
	return pSecond->f - pFirst->f;
}


#endif

#include "StdAfx.h"

//#include "pathFinding.h"
//#include "global.h"
//extern GLOBAL_VARIABLES g_var;


inline int GetMap( int x, int y )
{
	POINT	ptTarget = {0, 0};
	INT		nWidth, nHeight;
	CHAR	cRet = 9;

	nWidth  = g_xGameProc.m_xMap.m_stMapFileHeader.shWidth;
	nHeight = g_xGameProc.m_xMap.m_stMapFileHeader.shHeight;


	if ( x < 0 || x >= nWidth || y < 0 || y >= nHeight )
		return cRet;

	
//	if ( g_xGameProc.m_xMap.GetNextTileCanMove(x, y, 0, 0, &ptTarget) )
	if ( g_xGameProc.m_xMap.GetTileAttribute(x, y) == _CAN_WALK )
	{
		cRet = 1;
	}

	return cRet;
}


inline void AddSuccessor( int x, int y, CAStar< CMapNode > *pAStar, CMapNode *pParent )
{
//	if ( abs(x - pAStar->m_pStart->state.x) > 16 || abs(y - pAStar->m_pStart->state.y) > 16 )
//		return;

	int parentX = -1; 
	int parentY = -1; 
	CMapNode newNode;

	if( pParent )
	{
		parentX = pParent->x;
		parentY = pParent->y;
	}	

	if ( (GetMap( x, y ) < 9 ) && !((parentX == x) && (parentY == y) ) )
	{
		newNode = CMapNode( x, y );
		pAStar->AddSuccessor( &newNode );
		
		// 추가한 노드(방문할 노드를 옅은 색으로 표시)
//		g_xGameProc.m_xMap.m_pcPath[x + y*g_xGameProc.m_xMap.m_stMapFileHeader.shHeight] = VISIT;
	}
}


bool CMapNode::GetSuccessors( CAStar< CMapNode > *pAStar, CMapNode *pParent )
{
	// 12시부터 시계방향으로 8방향 추가
	AddSuccessor(     x, y - 1, pAStar, pParent );	// 12
	AddSuccessor( x + 1, y - 1, pAStar, pParent );	// 1
	AddSuccessor( x + 1,     y, pAStar, pParent );	// 3
	AddSuccessor( x + 1, y + 1, pAStar, pParent );	// 5
	AddSuccessor(     x, y + 1, pAStar, pParent );	// 6
	AddSuccessor( x - 1, y + 1, pAStar, pParent );	// 7
	AddSuccessor( x - 1,     y, pAStar, pParent );	// 9
	AddSuccessor( x - 1, y - 1, pAStar, pParent );	// 11

	return true;
}


int CMapNode::GetGoalEstimate( CMapNode *pGoal )
{
	int xd = x - pGoal->x;
	int yd = y - pGoal->y;
	int baseHeuristic = abs( xd ) + abs( yd );

	return baseHeuristic * baseHeuristic/* * g_var.heuristic*/;
}


int CMapNode::GetCost( CMapNode *pState )
{
	if ( pState->x - x == 0 || pState->y - y == 0 )
		return GetMap( x, y );
	
	return GetMap( x, y ) + PENALTY;
}


bool CMapNode::IsSameState( CMapNode *pState )
{
	return (x == pState->x) && (y == pState->y);
}


bool CMapNode::IsGoal( CMapNode *pState )
{
	return (x == pState->x) && (y == pState->y);
}
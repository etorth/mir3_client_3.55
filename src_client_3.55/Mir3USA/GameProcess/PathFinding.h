

#pragma once


//#include <windows.h>
//#include "astar.h"

#define BEST		1
#define PENALTY		1
#define WORST		10

#define START		101
#define GOAL		102
#define PATH		111
#define VISIT		112


class CMapNode
{
public:
	int x, y;

	CMapNode() { x = y = 0; }
	CMapNode( int px, int py ) { x = px; y = py; }

	virtual int  GetGoalEstimate( CMapNode *pGoal );
	virtual bool GetSuccessors( CAStar< CMapNode > *pAStar, CMapNode *pState );
	virtual int  GetCost( CMapNode *pState );
	
	virtual bool IsSameState( CMapNode *pState );
	virtual bool IsGoal( CMapNode *pState );
};

// TestActor.h

#ifndef _TESTACTOR_H_
#define _TESTACTOR_H_

class CTestActor
{
public:
	CTestActor();
	~CTestActor();

	VOID Init();
	VOID Destroy();

	BOOL CreateTestActor();
	VOID UpdateTestActor( INT nLoopTime, BOOL bIsMoveTime );
	VOID RenderTestActor();

	BOOL OnLButtonDown( POINT ptMouse );
	VOID OnWheel();




public:
	VOID CreateActor( WORD wIndex, INT x, INT y );
	VOID CreateActorAllDirection( WORD wIndex, INT x, INT y );
	VOID MotionTest( CActor* pFindActor );

};

#endif
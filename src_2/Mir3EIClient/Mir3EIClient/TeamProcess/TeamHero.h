#pragma once
class CTeamProcess;

class CTeamHero : public CMyHero
{
public:
	CTeamHero(void);
	~CTeamHero(void);

public:
	//动作函数,发送MyHero的行走,魔法命令 AutoTargeting(), OnLButtonDown()...调用
	virtual VOID  SetMotionState(BYTE bMtn, BYTE bDir, INT nMouseTargetID = NULL, BOOL bIsDead = FALSE, LPPOINT lpptPos = NULL, SHORT shSkill = -1);

	//处理状态改变
	virtual BOOL UpdatePacketState();

	//更新运动状态,绘制动作和特效,
	/*virtual*/ VOID UpdateMotionState(INT nLoopTime, BOOL bIsMoveTime);
	/*virtual*/ BOOL UpdateMove(BOOL bIsMoveTime);
	//退回到前一个状态, 接收到"+FAIL"行走失败命令后调用这个函数
	/*virtual*/ BOOL  SetOldPosition();

	//  鼠标消息.
	/*virtual*/ BOOL OnLButtonDown(POINT ptMouse, INT nTargetID = -1, BOOL bIsDead = FALSE, POINT* lpptTargetPos = NULL);
//	virtual BOOL OnRButtonDown(POINT ptMouse);
//	virtual BOOL OnKeyDown(WPARAM wParam, LPARAM lParam, POINT ptMouse, POINT ptTargetPos, INT nMosueTargetID, FEATURE stTargetFeature);


};

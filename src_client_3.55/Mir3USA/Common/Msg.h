#pragma once


#include <indexmap.h>


// 해쉬 테이블 크기
#define MAX_HASHSIZE	1024


class CMsg
{
public:
	struct stMsgNode
	{
		char	szKey[16];
		int		nMsgIdx;
		char*	pszMsg;

		stMsgNode()
		{
			nMsgIdx = -1;
			pszMsg = NULL;
			ZeroMemory(szKey, 16);
		}
	};
	
	CIndexMap< stMsgNode >	m_xlistMsg;

public:
	CMsg();
	virtual ~CMsg();

	BOOL LoadMsg();
	char* GetMsg(int nIdx);
	void DelMsg(int nIdx);
	void DelAllMsg();

protected:
	static char* __cbTextureKey(stMsgNode *pNode);	
	stMsgNode* FindMsg(int nIdx);
};
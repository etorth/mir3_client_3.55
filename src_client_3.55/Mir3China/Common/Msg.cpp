#include "StdAfx.h"


CMsg::CMsg()
{
	m_xlistMsg.InitHashTable(MAX_HASHSIZE, IHT_ROUNDUP);
	m_xlistMsg.SetGetKeyFunction(__cbTextureKey);
}


CMsg::~CMsg()
{
	DelAllMsg();
	m_xlistMsg.UninitHashTable();
}


char* CMsg::GetMsg(int nIdx)
{
	stMsgNode *pObj = FindMsg(nIdx);

	if ( pObj )
	{		
		return pObj->pszMsg;
	}

#ifdef _DEBUG
	_ASSERT(0);
#endif

	return NULL;
}


void CMsg::DelMsg(int nIdx)
{
	stMsgNode *pObj = FindMsg(nIdx);
	if ( pObj )
	{
		SAFE_DELETEARR(pObj->pszMsg);
		m_xlistMsg.Remove(pObj);
		SAFE_DELETE(pObj);
	}
}


BOOL CMsg::LoadMsg()
{
	DelAllMsg();

	// 암호화 루틴해제.
	char* pszBuf = NULL;

	crypto_seed s = {(char) 0xF0, (char) 0x39, (char) 0xAB, (char) 0x8E, 0x9FDE1A93};
	crypto::setSeed(&s);
	FILE *fp = fopen( "CMList.Dat", "rb" );

	if ( !fp )
	{
		MessageBox(NULL, (char*)"Message List File Error.", "[Error] - Legend of Mir III", MB_ICONERROR);
		return FALSE;
	}

	int len = _filelength(_fileno(fp));
	pszBuf = new char[len];

	if ( !pszBuf )
	{
		fclose(fp);
		delete [] pszBuf;
		MessageBox(NULL, (char*)"Message List File Error.", "[Error] - Legend of Mir III", MB_ICONERROR);
		return FALSE;
	}

	fread(pszBuf, 1, len, fp);
	fclose(fp);

	if ( !crypto::decrypt((unsigned char *)pszBuf, len) )
	{
		delete[] pszBuf;
		MessageBox(NULL, (char*)"Message List File Error.", "[Error] - Legend of Mir III", MB_ICONERROR);
		return FALSE;
	}

	// 데이타적용.
	CHAR  pszMsgNum[20];
	ZeroMemory(pszMsgNum, 20);

	CHAR* pszComment  = NULL;
	CHAR* pszLineNext = NULL;
	CHAR* pszLine	  = pszBuf + 8;		// Seed를 건너뛴다.

	INT	nLineLen = 0;

	while ( pszLineNext = (char*)strchr(pszLine, '\r') )
	{
		*pszLineNext = '\0';
	
		// Comment.
		if ( pszComment = (char*)strchr(pszLine, ';') )
		{
			*pszComment = '\0';
		}
		// Message
		else if ( (char*)strchr(pszLine, '#') )
		{
			// #을 건너 뛴다.
			pszLine++;

			CHAR* pszMsg = NULL;

			nLineLen = strlen(pszLine)+1;
			pszMsg = new CHAR[nLineLen];
			ZeroMemory(pszMsg, nLineLen);

			sscanf(pszLine, "%s %[^\000]", pszMsgNum, pszMsg);

			stMsgNode *pObj = new stMsgNode;
			strcpy(pObj->szKey, pszMsgNum);
			pObj->nMsgIdx = atoi(pszMsgNum);
			pObj->pszMsg = pszMsg;

			if ( !m_xlistMsg.Insert(pObj) )
			{
				delete[] pszBuf;
				CHAR pszError[MAX_PATH];
				sprintf(pszError, "Message List File Error(MsgNum:%d)", atoi(pszMsgNum));
				MessageBox(NULL, (char*)pszError, "[Error] - Legend of Mir III", MB_ICONERROR);
				DelAllMsg();
				return FALSE;
			}
		}

		pszLine = (pszLineNext+2);  // '\r''\n'
	}	

	delete [] pszBuf;

	return TRUE;
}

BOOL CMsg::LoadMsg( CHAR* pFile )
{
	DelAllMsg();

	// 암호화 루틴해제.
	char* pszBuf = NULL;

	crypto_seed s = {(char) 0xF0, (char) 0x39, (char) 0xAB, (char) 0x8E, 0x9FDE1A93};
	crypto::setSeed(&s);
	FILE *fp = fopen( pFile, "rb" );

	if ( !fp )
	{
		MessageBox(NULL, (char*)"Message List File Error.", "[Error] - Legend of Mir III", MB_ICONERROR);
		return FALSE;
	}

	int len = _filelength(_fileno(fp));
	pszBuf = new char[len];

	if ( !pszBuf )
	{
		fclose(fp);
		delete [] pszBuf;
		MessageBox(NULL, (char*)"Message List File Error.", "[Error] - Legend of Mir III", MB_ICONERROR);
		return FALSE;
	}

	fread(pszBuf, 1, len, fp);
	fclose(fp);

	if ( !crypto::decrypt((unsigned char *)pszBuf, len) )
	{
		delete[] pszBuf;
		MessageBox(NULL, (char*)"Message List File Error.", "[Error] - Legend of Mir III", MB_ICONERROR);
		return FALSE;
	}

	// 데이타적용.
	CHAR  pszMsgNum[20];
	ZeroMemory(pszMsgNum, 20);

	CHAR* pszComment  = NULL;
	CHAR* pszLineNext = NULL;
	CHAR* pszLine	  = pszBuf + 8;		// Seed를 건너뛴다.

	INT	nLineLen = 0;

	while ( pszLineNext = (char*)strchr(pszLine, '\r') )
	{
		*pszLineNext = '\0';
	
		// Comment.
		if ( pszComment = (char*)strchr(pszLine, ';') )
		{
			*pszComment = '\0';
		}
		// Message
		else if ( (char*)strchr(pszLine, '#') )
		{
			// #을 건너 뛴다.
			pszLine++;

			CHAR* pszMsg = NULL;

			nLineLen = strlen(pszLine)+1;
			pszMsg = new CHAR[nLineLen];
			ZeroMemory(pszMsg, nLineLen);

			sscanf(pszLine, "%s %[^\000]", pszMsgNum, pszMsg);

			stMsgNode *pObj = new stMsgNode;
			strcpy(pObj->szKey, pszMsgNum);
			pObj->nMsgIdx = atoi(pszMsgNum);
			pObj->pszMsg = pszMsg;

			if ( !m_xlistMsg.Insert(pObj) )
			{
				delete[] pszBuf;
				CHAR pszError[MAX_PATH];
				sprintf(pszError, "Message List File Error(MsgNum:%d)", atoi(pszMsgNum));
				MessageBox(NULL, (char*)pszError, "[Error] - Legend of Mir III", MB_ICONERROR);
				DelAllMsg();
				return FALSE;
			}
		}

		pszLine = (pszLineNext+2);  // '\r''\n'
	}	

	delete [] pszBuf;

	return TRUE;
}

void CMsg::DelAllMsg()
{
	CListNode< stMsgNode >	*pNode = m_xlistMsg.GetHead();
	CListNode< stMsgNode >	*pTemp;
	stMsgNode				*pObj = NULL;

	while ( pNode )
	{
		pObj = pNode->GetData();

		pTemp = pNode->GetNext();

		SAFE_DELETEARR(pObj->pszMsg);
		m_xlistMsg.Remove(pObj);
		SAFE_DELETE(pObj);

		pNode = pTemp;
	}
}


char * CMsg::__cbTextureKey(CMsg::stMsgNode *pNode)
{
	return pNode->szKey;
}


CMsg::stMsgNode* CMsg::FindMsg(int nIdx)
{
	char szKey[16];
	sprintf(szKey, "%d", nIdx);
	
	return m_xlistMsg.SearchKey(szKey);
}

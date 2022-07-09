/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"



/******************************************************************************************************************

	ClientSysMsg Class

*******************************************************************************************************************/

ClientSysMsg::ClientSysMsg()
{
	Init();
}

ClientSysMsg::~ClientSysMsg()
{
	Destroy();
}

VOID ClientSysMsg::Init()
{
	m_nSysMsgCurrDelay	= 0;
}

VOID ClientSysMsg::Destroy()
{
	m_stSysMsg.ClearAllNodes();
	Init();
}

VOID ClientSysMsg::AddSysMsg(CHAR* szStr, DWORD dwFontClr)
{
	DWORD dwFont = GetChatColor(_CHAT_COLOR3);
	DWORD dwBack = GetChatColor(_CHAT_COLOR8);
	g_xGameProc.m_xInterface.MsgAdd(dwFont, dwBack, szStr);
	return;

	LPCONSTSTRING pstMsg = NULL;
	while ( m_stSysMsg.GetCounter() >= _MAX_SYSMSG )
	{
		m_stSysMsg.MoveCurrentToTop();
		pstMsg = m_stSysMsg.GetCurrentData();

		if ( pstMsg ) 
		{
			m_stSysMsg.DeleteCurrentNodeEx();
			SAFE_DELETE((LPCONSTSTRING)pstMsg);
		}
	}

	m_stSysMsg.MoveCurrentToTail();
	pstMsg = new CONSTSTRING;
	strcpy(pstMsg->szMsg, szStr);
	pstMsg->dwFontClr = dwFontClr;
	m_stSysMsg.AddNode(pstMsg);
	m_nSysMsgCurrDelay = 0;
}

VOID ClientSysMsg::ShowSysMsg(INT nLoopTime, INT nX, INT nY)
{
	INT nDelay = 6000;
	LPCONSTSTRING pstMsg = NULL;
	m_nSysMsgCurrDelay += nLoopTime;

	m_stSysMsg.MoveCurrentToTop();
	for ( INT nCnt = 0; nCnt < m_stSysMsg.GetCounter(); nCnt++ )
	{
		LPCONSTSTRING pstMsg = m_stSysMsg.GetCurrentData();

		if ( pstMsg )
		{
			if ( pstMsg->dwFontClr == RGB(50, 255, 255) )
			{
				SIZE sizeLen = g_xMainWnd.GetStrLength(NULL, NULL, pstMsg->szMsg);
				RECT rc = {nX-3, nY+nCnt*15-1, nX+sizeLen.cx+3, nY+(nCnt+1)*15-2};

				D3DMATERIAL7 mtrl;
				D3DVECTOR	 vecTrans((FLOAT)rc.left, (FLOAT)rc.top, 0);
				D3DVECTOR	 vecScale((FLOAT)rc.right-rc.left, rc.bottom-rc.top, 1);

				D3DUtil_InitMaterial(mtrl, (FLOAT)255/255.0f, (FLOAT)150/255.0f, (FLOAT)100/255.0f);
				mtrl.diffuse.a = 120.0f/255.0f;
				g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL, 6);
//				g_xMainWnd.DrawWithGDI(&rc, NULL, RGB(100, 50, 50), 1);

				g_xMainWnd.PutsHan(NULL, nX+1, nY+nCnt*15+1, RGB(10, 10, 10), RGB(0, 0, 0), pstMsg->szMsg);
				g_xMainWnd.PutsHan(NULL, nX, nY+nCnt*15, pstMsg->dwFontClr, RGB(0, 0, 0), pstMsg->szMsg);
			}
			else
			{
				g_xMainWnd.PutsHan(NULL, nX+1, nY+nCnt*15+1, RGB(10, 10, 10), RGB(0, 0, 0), pstMsg->szMsg);
				g_xMainWnd.PutsHan(NULL, nX, nY+nCnt*15, pstMsg->dwFontClr, RGB(0, 0, 0), pstMsg->szMsg);
			}
		}
		m_stSysMsg.MoveNextNode();
	}

	if ( m_stSysMsg.GetCounter() > 6 )	
	{
		nDelay = 3000;
	}

	if ( m_nSysMsgCurrDelay > nDelay )
	{
		m_stSysMsg.MoveCurrentToTop();
		if ( m_stSysMsg.GetCounter() )
		{
			pstMsg = m_stSysMsg.GetCurrentData();

			if ( pstMsg )
			{
				m_stSysMsg.DeleteCurrentNodeEx();
				SAFE_DELETE((LPCONSTSTRING)pstMsg);
			}
		}
		m_nSysMsgCurrDelay = 0;
	}
}

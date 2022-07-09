#include "stdafx.h"
#include ".\teammanage.h"

CTeamManage::CTeamManage(void)
{
	m_dwLastEventFilter = ID_SOCKCLIENT_EVENT_MSG_1;
}

CTeamManage::~CTeamManage(void)
{
	m_xTeamProcList.ClearAllNodes();
}


VOID CTeamManage::OnConnectToServer()
{
	//some wrong
	assert(0);
}

char* CTeamManage::OnMessageReceive(CHAR* pszPacketMsg)
{
	//some wrong
	assert(0);
	return NULL;
}

LRESULT CTeamManage::DefMainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch ( uMsg )
	{
	case WM_KEYUP:
		OnKeyDown(wParam, lParam);//处理加人和减人和命令
		break;
	default:
		break;
	}

	LRESULT result = g_xGameProc.DefMainWndProc( hWnd, uMsg, wParam, lParam );
	
	CTeamProcess *pTeamProc = NULL;
	m_xTeamProcList.MoveCurrentToTop();
	for ( INT nCnt = 0; nCnt < m_xTeamProcList.GetCounter(); nCnt++ )
	{
		pTeamProc = m_xTeamProcList.GetCurrentData();
		if( pTeamProc )
			pTeamProc->DefMainWndProc( hWnd, uMsg, wParam, lParam );
	}
	
	
	return result;
}

LRESULT CTeamManage::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	switch ( wParam )
	{
		case 'P':
			if( GetKeyState(VK_LCONTROL) & 0x8000 )//加人
			{
				CTeamProcess *pTeamProc = new CTeamProcess;
				m_xTeamProcList.AddNode( pTeamProc );
				m_dwLastEventFilter++;
				pTeamProc->Load(m_dwLastEventFilter);//连接服务器
			}
			break;
		case 'O':
			if( GetKeyState(VK_LCONTROL) & 0x8000 )//断开Active hero
			{
				CTeamProcess *pTeamProc = NULL;
				m_xTeamProcList.MoveCurrentToTop();
				for ( INT nCnt = 0; nCnt < m_xTeamProcList.GetCounter(); nCnt++ )
				{
					pTeamProc = m_xTeamProcList.GetCurrentData();
					if( pTeamProc && pTeamProc->m_pMyHero->m_bActive )
					{
						m_xTeamProcList.DeleteCurrentNodeEx();
						pTeamProc->DeleteProc();//断开连接
						delete pTeamProc;//释放内存
						break;
					}
					m_xTeamProcList.MoveNextNode();
				}
			}
			break;
		case VK_TAB:
			if( GetKeyState(VK_LCONTROL) & 0x8000 )
			{
				CTeamProcess *pTeamProc = NULL;
				m_xTeamProcList.MoveCurrentToTop();
				pTeamProc = m_xTeamProcList.GetCurrentData();
				if( pTeamProc == NULL )
					break;
				
				//交换,hero 和 socket,进一个应该清除对话框数据,由显示对话框时申请数据
				//CMyHero使用了虚函数,因而头部时虚表,交换MyHero时g_xGameProc.m_pMyHero的虚表不能改变
				DWORD Vtab1, Vtab2;
				memcpy( &Vtab1, g_xGameProc.m_pMyHero, sizeof(VOID*) );
				memcpy( &Vtab2, pTeamProc->m_pMyHero, sizeof(VOID*) );

				CMyHero* pTempHero = g_xGameProc.m_pMyHero;
				CClientSocket* pTempSocket = g_xGameProc.m_pSocket;
				
				g_xGameProc.m_pMyHero = pTeamProc->m_pMyHero;
				g_xGameProc.m_pSocket = pTeamProc->m_pSocket;
				g_xGameProc.m_pMyHero->AdjustMyPostion();

				pTeamProc->m_pMyHero = (CTeamHero*)(pTempHero);
				pTeamProc->m_pSocket = pTempSocket;
				pTeamProc->m_pMyHero->SetProc( pTeamProc );

				//复原虚表
				memcpy( g_xGameProc.m_pMyHero, &Vtab1, sizeof(VOID*) );
				memcpy( pTeamProc->m_pMyHero, &Vtab2, sizeof(VOID*) );


				g_xGameProc.m_xInterface.MsgAdd(_CLR_RED, _CLR_BLACK, "交换角色" );
			}
			break;
		default:
			break;
	}

	return 0;
}

VOID CTeamManage::RenderScene(INT nLoopTime)
{
	g_xGameProc.RenderScene( nLoopTime );

	CTeamProcess *pTeamProc = NULL;
	m_xTeamProcList.MoveCurrentToTop();
	for ( INT nCnt = 0; nCnt < m_xTeamProcList.GetCounter(); nCnt++ )
	{
		pTeamProc = m_xTeamProcList.GetCurrentData();
		if( pTeamProc )
			pTeamProc->RenderScene( nLoopTime );
		
		m_xTeamProcList.MoveNextNode();
	}

}

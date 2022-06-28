#include "stdafx.h"

CWHQueue PacketQ;

CClientSocket::CClientSocket()
{
	m_sockClient = INVALID_SOCKET;
	m_pxDefProc	 = NULL;

	m_sendID = 1;
}

CClientSocket::~CClientSocket()
{
	m_pxDefProc	 = NULL;
	if ( m_sockClient != INVALID_SOCKET )
	{
		closesocket(m_sockClient);
	}
	m_sockClient = INVALID_SOCKET;
}

unsigned long CClientSocket::GetINetAddr(CHAR* pszDotAddress)
{
	if ( inet_addr(pszDotAddress) == -1L )
	{
		struct hostent* pHostEnt;

		pHostEnt = gethostbyname(pszDotAddress);
		return *(unsigned long*)pHostEnt->h_addr_list[0];
	}
	
	return inet_addr(pszDotAddress);
}

BOOL CClientSocket::ConnectToServer(HWND hWnd, CHAR* szID, INT nPort)
{
	SOCKADDR_IN		sockAddr;
	CHAR strError[256]; 

	if ( m_sockClient == INVALID_SOCKET )
	{
		m_sockClient = socket(AF_INET, SOCK_STREAM, 0);

		if ( m_sockClient == INVALID_SOCKET )
		{
			wsprintf(strError, "socket() generated error %d\n", WSAGetLastError());
			OutputDebugString(strError);
			return FALSE;
		}

		sockAddr.sin_family		 = AF_INET;
		sockAddr.sin_port		 = htons( (WORD)nPort );
		sockAddr.sin_addr.s_addr = inet_addr(szID);

		if ( WSAAsyncSelect(m_sockClient, hWnd, ID_SOCKCLIENT_EVENT_MSG, FD_CONNECT|FD_READ|FD_CLOSE ) == SOCKET_ERROR)
		{
			wsprintf(strError, "WSAAsyncSelect() generated error %d\n", WSAGetLastError());
			OutputDebugString(strError);
			return FALSE;
		}

		if ( connect(m_sockClient, (const struct sockaddr FAR*)&sockAddr, sizeof(sockAddr)) == SOCKET_ERROR )
		{
			switch ( WSAGetLastError() )
			{
				case WSAEWOULDBLOCK:
					OutputDebugString( "This socket is Non-Blocking Mode\r\n" );
					break;
			}
		}

		m_sendID = 1;
	}

	return TRUE;
}

BOOL CClientSocket::DisconnectToServer()
{
	if ( m_sockClient != INVALID_SOCKET )
	{
		closesocket(m_sockClient);
		m_sockClient = INVALID_SOCKET;

		return TRUE;
	}

	return FALSE;
}

VOID CClientSocket::SendActMsg(WORD wIdent, INT nX, INT nY, INT nDir, DWORD dwTime)
{
	fnMakeDefMessage(&m_sendDefMsg, wIdent, MAKELONG(nX, nY), LOWORD(dwTime), (WORD)nDir, HIWORD(dwTime));
	SendPacket(&m_sendDefMsg, NULL);
}

VOID CClientSocket::SendHitMsg(WORD wIdent, INT nX, INT nY, INT nDir, WORD wHitStyle, INT nTargetID)
{
	DWORD dwTime = timeGetTime();

	fnMakeDefMessage(&m_sendDefMsg, wIdent, MAKELONG(nX, nY), LOWORD(dwTime), (WORD)nDir, HIWORD(dwTime));

	CHAR szTarget[MAX_PATH];
	sprintf(szTarget, "%d", nTargetID);

	SendPacket(&m_sendDefMsg, szTarget);
}

VOID CClientSocket::SendRideMsg(WORD wIdent, INT nDir, BOOL bRide)
{
	fnMakeDefMessage(&m_sendDefMsg, wIdent, 0, (WORD)nDir, (WORD)bRide, 0);
	SendPacket(&m_sendDefMsg, NULL);
}

//VOID CClientSocket::SendRunLogin(CHAR* szLoginID, CHAR* szCharName, INT nCertification, INT VersionNum)
VOID CClientSocket::SendRunLogin(CHAR* szLoginID, CHAR* szCharName, INT nCertification, INT VersionNum, INT nUpgradeLevel) //lee wun gyo
{
	CHAR				szEncodeMsg[512];
	CHAR				szLoginInfo[512];
	CHAR				szPacket[512];
	//lee wun gyo..
	wsprintf(szLoginInfo, "**%s/%s/%d/%d/%d/1/%d", szLoginID, szCharName, 
					(nCertification ^ 0x44a031f3) ^ 0x7a12f43f, 
					(nCertification ^ VersionNum) ^ 0x5580af27,
					VersionNum ^ 0xfa0280af, nUpgradeLevel);

	int nPos = fnEncode6BitBuf((BYTE*)szLoginInfo, szEncodeMsg, lstrlen(szLoginInfo), sizeof(szEncodeMsg));
	//int nPos = fnEncode6BitBufGameString((BYTE*)szLoginInfo, szEncodeMsg, lstrlen(szLoginInfo), sizeof(szEncodeMsg));
	szEncodeMsg[nPos] = '\0';

	((m_sendID >= 9) ? m_sendID = 1 : m_sendID++);
	wsprintf(szPacket, "#%d%s!", m_sendID, szEncodeMsg);

	send(m_sockClient, szPacket, strlen(szPacket), 0);
}

BOOL CClientSocket::CheckSocketError(LPARAM lParam)
{
	switch ( WSAGETSELECTERROR(lParam) )
	{
		case WSANOTINITIALISED:
			return FALSE;
		case WSAENETDOWN:
			return FALSE;
		case WSAEADDRINUSE:
			return FALSE;
		case WSAEINTR:
			return FALSE;
		case WSAEINPROGRESS:
			return FALSE;
		case WSAEALREADY:
			return FALSE;
		case WSAEADDRNOTAVAIL:
			return FALSE;
		case WSAEAFNOSUPPORT:
			return FALSE;
		case WSAECONNREFUSED:
			return FALSE;
		case WSAETIMEDOUT:
			return FALSE;
		case WSAEFAULT:
			return FALSE;
		case WSAEINVAL:
			return FALSE;
		case WSAEISCONN:
			return FALSE;
		case WSAENETUNREACH:
			return FALSE;
		case WSAENOBUFS:
			return FALSE;
		case WSAENOTSOCK:
			return FALSE;
		case WSAEWOULDBLOCK:
			return FALSE;
		case WSAEACCES:
			return FALSE;
	}

	return TRUE;
}

VOID CClientSocket::SendQueryMsg(WORD wIdent)
{
	fnMakeDefMessage(&m_sendDefMsg, wIdent, 0, 0, 0, 0);
	SendPacket(&m_sendDefMsg, NULL);
}

VOID CClientSocket::SendTakeOnOffItem(WORD wIdent, BYTE bEquipNum, CHAR* szItemName, INT nItemIdx)
{
	// 추가 가방
	WORD wSeries = 0;
	if( g_xGameProc.m_xInterface.m_xStatusWnd.m_stTakeOnItemSet.bIsInvenExWnd )
		wSeries = 1;

	fnMakeDefMessage(&m_sendDefMsg, wIdent, nItemIdx, bEquipNum, 0, wSeries);
	SendPacket(&m_sendDefMsg, szItemName);
}

VOID CClientSocket::SendQueryName(INT nRecog, INT nX, INT nY)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_QUERYUSERNAME, nRecog, (WORD)nX, (WORD)nY, 0);
	SendPacket(&m_sendDefMsg, NULL);
}

VOID CClientSocket::SendQueryMonsterInfo(INT nRecog, INT nX, INT nY)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_QUERYMONSTERINFO, nRecog, (WORD)nX, (WORD)nY, 0);
	SendPacket(&m_sendDefMsg, NULL);
}

VOID CClientSocket::SendNPCClick(INT nRecog)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_CLICKNPC, nRecog, 0, 0, 0);
	SendPacket(&m_sendDefMsg, NULL);
}

VOID CClientSocket::SendWantMMap()
{
	fnMakeDefMessage(&m_sendDefMsg, CM_WANTMINIMAP, 0, 0, 0, 0);
	SendPacket(&m_sendDefMsg, NULL);
}

VOID CClientSocket::SendSellItem(INT nItemIdx, INT nMerchantID, CHAR* pszItemName, INT nCount)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_USERSELLITEM, nMerchantID, LOWORD(nItemIdx), HIWORD(nItemIdx), nCount);

	SendPacket(&m_sendDefMsg, pszItemName);
}

VOID CClientSocket::SendQueryPrice(INT nItemIdx, INT nMerchantID, CHAR* pszItemName)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_MERCHANTQUERYSELLPRICE, nMerchantID, LOWORD(nItemIdx), HIWORD(nItemIdx), 0);

	SendPacket(&m_sendDefMsg, pszItemName);
}

VOID CClientSocket::SendRepairItem(INT nItemIdx, INT nMerchantID, CHAR* pszItemName)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_USERREPAIRITEM, nMerchantID, LOWORD(nItemIdx), HIWORD(nItemIdx), 0);

	SendPacket(&m_sendDefMsg, pszItemName);
}

VOID CClientSocket::SendQueryRepairCost(INT nItemIdx, INT nMerchantID, CHAR* pszItemName)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_MERCHANTQUERYREPAIRCOST, nMerchantID, LOWORD(nItemIdx), HIWORD(nItemIdx), 0);

	SendPacket(&m_sendDefMsg, pszItemName);
}

VOID CClientSocket::SendStorageItem(INT nItemIdx, INT nMerchantID, CHAR* pszItemName, INT nCount)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_USERSTORAGEITEM, nMerchantID, LOWORD(nItemIdx), HIWORD(nItemIdx), nCount);

	SendPacket(&m_sendDefMsg, pszItemName);
}

// 추가 창고
VOID
CClientSocket::SendStorageItemEx(INT nItemIdx, INT nMerchantID, CHAR* pszItemName, INT nCount)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_USERSTORAGEITEMEX, nMerchantID, LOWORD(nItemIdx), HIWORD(nItemIdx), nCount);
	SendPacket(&m_sendDefMsg, pszItemName);
}

VOID CClientSocket::SendMagicKeyChange(INT nKeyNum, INT nMagicID)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_MAGICKEYCHANGE, nMagicID, (WORD)nKeyNum, 0, 0);
	SendPacket(&m_sendDefMsg, NULL);
}

VOID CClientSocket::SendItemIndex(WORD wIdent, INT nItemIndex, CHAR* pszItemName)
{
	DWORD dwTime = timeGetTime();
	fnMakeDefMessage(&m_sendDefMsg, wIdent, nItemIndex, LOWORD(dwTime), 0, HIWORD(dwTime));
	SendPacket(&m_sendDefMsg, pszItemName);
}

VOID CClientSocket::UseWearItem(WORD wIdent, INT nLocation)
{
	fnMakeDefMessage(&m_sendDefMsg, wIdent, nLocation, 0, 0, 0);
	SendPacket(&m_sendDefMsg, NULL);
}

VOID CClientSocket::SendDropGold(INT nGold)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_DROPGOLD, nGold, 0, 0, 0);
	SendPacket(&m_sendDefMsg, NULL);
}

VOID CClientSocket::SendDropMultipleItem(INT nItemIndex, INT nCount, CHAR* pszItemName)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_DROPCOUNTITEM, nItemIndex, 0, 0, (WORD)nCount);
	SendPacket(&m_sendDefMsg, pszItemName);
}

VOID CClientSocket::SendPickUp(INT nX, INT nY)
{
	// 말을 타고 있을 때는 아이템을 주울 수 없다
	if( g_xGameProc.m_xMyHero.m_stFeatureEx.bHorse != _HORSE_NONE )
		return;	

	fnMakeDefMessage(&m_sendDefMsg, CM_PICKUP, 0, (WORD)nX, (WORD)nY, 0);
	SendPacket(&m_sendDefMsg, NULL);
}

VOID CClientSocket::SendButchAnimal(INT nX, INT nY, INT nDir, INT nActorID)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_BUTCH, nActorID, (WORD)nX, (WORD)nY, (WORD)nDir);
	SendPacket(&m_sendDefMsg, NULL);
}

// 퀘스트창관련.
VOID CClientSocket::SendQueryQuest(VOID)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_QUERYQUESTDIARY, 0, 0, 0, 0);
	SendPacket(&m_sendDefMsg, NULL);
}

VOID CClientSocket::SendQuerySubQuest(int nIdx)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_QUERYSUBQUESTDIARY, 0, 0, 0, (WORD)nIdx);
	SendPacket(&m_sendDefMsg, NULL);
}

VOID CClientSocket::SendQueryDetail(int nIdx,int SubIdx)// ser : unit recog : sub id
{
	fnMakeDefMessage(&m_sendDefMsg, CM_QUESTDIARYDETAIL, SubIdx, 0, 0, (WORD)nIdx);
	SendPacket(&m_sendDefMsg, NULL);
}

// 교환창관련.
VOID CClientSocket::SendDealTry(CHAR* szName)
{
// 내캐릭터의 앞에 있는 만약에 다른 플레이어캐릭터라면 캐릭터의 이름을 뽑아온다.
	fnMakeDefMessage(&m_sendDefMsg, CM_DEALTRY, 0, 0, 0, 0);
	SendPacket(&m_sendDefMsg, szName);
}

VOID CClientSocket::SendCancelDeal()
{
	fnMakeDefMessage(&m_sendDefMsg, CM_DEALCANCEL, 0, 0, 0, 0);
	SendPacket(&m_sendDefMsg, NULL);
}

VOID CClientSocket::SendAddDealItem(CHAR* szItemName, INT nMakeIdx, INT nCount)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_DEALADDITEM, nMakeIdx, 0, 0, nCount);
	SendPacket(&m_sendDefMsg, szItemName);
}

VOID CClientSocket::SendDelDealItem(CHAR* szItemName, INT nMakeIdx)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_DEALDELITEM, nMakeIdx, 0, 0, 0);
	SendPacket(&m_sendDefMsg, szItemName);
}

VOID CClientSocket::SendChargeItem(CHAR* szItemName, INT nCount, INT nMakeIdx)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_CHARGESHOOTER, nMakeIdx, (WORD)nCount, 0, 0);
	SendPacket(&m_sendDefMsg, szItemName);
}

VOID CClientSocket::SendChangeDealGold(INT nGold)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_DEALCHGGOLD, nGold, 0, 0, 0);
	SendPacket(&m_sendDefMsg, NULL);
}

VOID CClientSocket::SendDealEnd()
{
	fnMakeDefMessage(&m_sendDefMsg, CM_DEALEND, 0, 0, 0, 0);
	SendPacket(&m_sendDefMsg, NULL);
}



void ErrMsgBox( int nErrCode )
{
	void *pMsg;
	
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		nErrCode,
		MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),
		(char *) &pMsg,
		0,
		NULL );
	
	MessageBox(g_xMainWnd.GetSafehWnd(), (char*)pMsg, "[Network Error] - Legend of Mir III", MB_ICONERROR);
	
	HeapFree(GetProcessHeap(), 0, pMsg);
}

LRESULT CClientSocket::OnSocketMessage(WPARAM wParam, LPARAM lParam)
{
	if ( !CheckSocketError(lParam) )
	{
		if ( MessageBox(g_xMainWnd.GetSafehWnd(), g_xMsg.GetMsg(132), "Legend Of Mir 3", MB_YESNO) == IDYES )
		{
			Sleep(2000);
			m_sockClient = INVALID_SOCKET;
			g_xClientSocket.ConnectToServer(g_xMainWnd.GetSafehWnd(), g_xLoginProc.m_pszSvrIP, g_xLoginProc.m_nSvrPort);
		}
		else
		{
//		ErrMsgBox( WSAGETSELECTERROR( lParam ) );
			SendMessage(g_xMainWnd.GetSafehWnd(), WM_DESTROY, 0, 0);
		}
		return 0L;
		
	}

	switch ( WSAGETSELECTEVENT( lParam ) )
	{
		case FD_CONNECT:
			OnConnect( (SOCKET) wParam );
			break;

		case FD_CLOSE:
			OnClose( (SOCKET) wParam );
			break;

		case FD_READ:
			OnRecv( (SOCKET) wParam );
			break;
	}

	return 0L;
}

void CClientSocket::OnConnect( SOCKET sdHost )
{
	//
	// 수신 버퍼를 초기화한다.
	//
	m_recvBuf.ClearAll();

	//
	// 연결된 프로세스 핸들러 함수를 호출한다.
	//
	if ( !m_pxDefProc )
		return;

	switch ( g_bProcState )
	{
	case _GAME_PROC:
		//SendRunLogin( g_szUserID, g_szCharName, g_nCertifyCode, g_nVersion );
		SendRunLogin( g_szUserID, g_szCharName, g_nCertifyCode, g_nVersion, g_nUpgradeLevel);  //lee wun gyo
		break;

	default:
		m_pxDefProc->OnConnectToServer();
		break;
	}
}

void CClientSocket::OnClose( SOCKET sdHost )
{
	DisconnectToServer();
}

void CClientSocket::OnRecv( SOCKET sdHost )
{
	char recvBuf[8192];
	int  recvLen;

	recvLen = recv( sdHost, recvBuf, sizeof( recvBuf ), 0 );
	if ( recvLen <= 0 )
	{
		return;
	}

	//
	// Urgent Code(*)를 확인한다.
	//
	char *pUrgentCode = (char *) memchr( recvBuf, '*', recvLen );
	bool bSend = false;

	while ( pUrgentCode )
	{
		if ( !bSend )
		{
			send( g_xClientSocket.m_sockClient, "*", 1, 0 );
			bSend = true;
		}

		recvLen--;
		memmove( pUrgentCode, pUrgentCode + 1, recvLen - (pUrgentCode - recvBuf) );

		pUrgentCode = (char *) memchr( recvBuf, '*', recvLen );
	}

	m_recvBuf.Append( recvBuf, recvLen );

	//
	// 게임 프로세스가 아니면 직접 핸들러 함수를 호출해준다.
	//
	if ( g_bProcState != _GAME_PROC && m_pxDefProc )
	{
		char *pNext = m_pxDefProc->OnMessageReceive( m_recvBuf.Buffer(), m_recvBuf.Length() );
		
		if ( pNext )
			m_recvBuf.Remove( pNext - m_recvBuf );
		else
			m_recvBuf.ClearAll();
	}
}

VOID CClientSocket::SendPacket(_TDEFAULTMESSAGE* lpDefMsg, char *pszData, INT nLen)
{
	fnEncodeMessage(lpDefMsg, m_sendHeader, sizeof(m_sendHeader));

	((m_sendID >= 9) ? m_sendID = 1 : m_sendID++);

	if (pszData)
	{	
		if ( nLen == 0 )
			fnEncode6BitBuf((unsigned char *)pszData, m_sendBody, strlen(pszData), sizeof(m_sendBody));
		else
			fnEncode6BitBuf((unsigned char *)pszData, m_sendBody, nLen, sizeof(m_sendBody));
		
		/*
		if ( nLen == 0 )
		{
			if((lpDefMsg->wIdent >= 2000  )&&(lpDefMsg->wIdent <= 2004))
			{
				fnEncode6BitBuf((unsigned char *)pszData, m_sendBody, strlen(pszData), sizeof(m_sendBody));
			}
			else if((lpDefMsg->wIdent >= 100  )&&(lpDefMsg->wIdent <= 104))
			{
				fnEncode6BitBuf((unsigned char *)pszData, m_sendBody, strlen(pszData), sizeof(m_sendBody));
			}
			else
			{
				fnEncode6BitBufGameString((unsigned char *)pszData, m_sendBody, strlen(pszData), sizeof(m_sendBody));
			}
		}
		else
		{
			if((lpDefMsg->wIdent >= 2000  )&&(lpDefMsg->wIdent <= 2004))
			{
				fnEncode6BitBuf((unsigned char *)pszData, m_sendBody, nLen, sizeof(m_sendBody));
			}
			else if((lpDefMsg->wIdent >= 100  )&&(lpDefMsg->wIdent <= 104))
			{
				fnEncode6BitBuf((unsigned char *)pszData, m_sendBody, nLen, sizeof(m_sendBody));
			}
			else
			{
				fnEncode6BitBufGameString((unsigned char *)pszData, m_sendBody, nLen, sizeof(m_sendBody));
			}

			
		}

*/
		sprintf(m_sendPacket, "#%d%s%s!", m_sendID, m_sendHeader, m_sendBody);
	}
	else
		sprintf(m_sendPacket, "#%d%s!", m_sendID, m_sendHeader);

	send(m_sockClient, m_sendPacket, strlen(m_sendPacket), 0);
}

VOID CClientSocket::SendPacket2(_TDEFAULTMESSAGE* lpDefMsg, char *pszData, INT nSize)
{
	fnEncodeMessage(lpDefMsg, m_sendHeader, sizeof(m_sendHeader));

	((m_sendID >= 9) ? m_sendID = 1 : m_sendID++);

	if (pszData)
	{
		fnEncode6BitBuf((unsigned char *)pszData, m_sendBody, nSize, sizeof(m_sendBody));
//		fnEncode6BitBufGameString((unsigned char *)pszData, m_sendBody, nSize, sizeof(m_sendBody));
		sprintf(m_sendPacket, "#%d%s%s!", m_sendID, m_sendHeader, m_sendBody);
	}
	else
		sprintf(m_sendPacket, "#%d%s!", m_sendID, m_sendHeader);

	send(m_sockClient, m_sendPacket, strlen(m_sendPacket), 0);
}


// **************************************************************************************
//
//		For Login Process
//
// **************************************************************************************

VOID CClientSocket::OnLogin(char *pszID, char *pszPassword)
{
	char				szPacket[64];
	
	fnMakeDefMessage(&m_sendDefMsg, CM_IDPASSWORD, 0, 0, 0, 0);
	wsprintf(szPacket, "%s/%s", pszID, pszPassword);

	SendPacket(&m_sendDefMsg, szPacket);
}

VOID CClientSocket::OnSelectServer(char *pszServerName)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_SELECTSERVER, 0, 0, 0, 0);
	SendPacket(&m_sendDefMsg, pszServerName);
}

VOID CClientSocket::OnChangePassword(char *pszID, char *pszOldPassword, char *pszNewPassword)
{
	char				szPacket[64];
	char				cDivider;

	cDivider = 0x09;
	fnMakeDefMessage(&m_sendDefMsg, CM_CHANGEPASSWORD, 0, 0, 0, 0);

	wsprintf(szPacket, "%s%c%s%c%s", pszID, cDivider, pszOldPassword, cDivider, pszNewPassword);

	SendPacket(&m_sendDefMsg, szPacket);
}

VOID CClientSocket::OnNewAccount(char *pszNewAccount)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_ADDNEWUSER, 0, 0, 0, 0);
	SendPacket(&m_sendDefMsg, pszNewAccount);
}

// **************************************************************************************
//
//		For Character Select Process
//
// **************************************************************************************

VOID CClientSocket::OnQueryChar()
{
	char szPacket[32];

	fnMakeDefMessage(&m_sendDefMsg, CM_QUERYCHR, 0, 0, 0, 0);

	wsprintf(szPacket, "%s/%d", g_szUserID, g_nCertifyCode);

	SendPacket(&m_sendDefMsg, szPacket);
}

VOID CClientSocket::OnNewChar( char *pszId, int nHair, int nJob, int nSex )
{
	char szPacket[64];

	fnMakeDefMessage(&m_sendDefMsg, CM_NEWCHR, 0, 0, 0, 0);

	wsprintf( szPacket, "%s/%s/%d/%d/%d", g_szUserID, pszId, nHair, nJob, nSex );

	SendPacket(&m_sendDefMsg, szPacket);
}

VOID CClientSocket::OnDelChar(char *pszCharName)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_DELCHR, 0, 0, 0, 0);
	SendPacket(&m_sendDefMsg, pszCharName);
}

VOID CClientSocket::OnSelChar( char *pszCharName)
{
	char szPacket[64];

	fnMakeDefMessage(&m_sendDefMsg, CM_SELCHR, 0, 0, 0, 0);

	//wsprintf( szPacket, "%s/%s", g_szUserID, pszCharName );
	wsprintf( szPacket, "%s/%s/%d", g_szUserID, pszCharName, g_nUpgradeLevel );  //lee wun gyo

	SendPacket(&m_sendDefMsg, szPacket);
}

// **************************************************************************************
//
//		For Game Playing
//
// **************************************************************************************

void CClientSocket::SendNoticeOK()
{
	fnMakeDefMessage(&m_sendDefMsg, CM_LOGINNOTICEOK, 0, 0, 0, 0);
	SendPacket(&m_sendDefMsg, NULL);
}

VOID CClientSocket::SendSay(CHAR *pszSay)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_SAY, 0, 0, 0, 0);
	SendPacket(&m_sendDefMsg, pszSay);
}

VOID CClientSocket::SendSpellMsg(INT nMagicID, INT nTargetX, INT nTargetY, INT nTargetID)
{
//wParam  : 마법 ID(wtag)
//lParam1 : 타겟X
//lParam2 : 타겟Y
//lParam3 : 타겟 오브젝트 id(wTag)
//lParam4 : ...(wSeries)

	if ( g_xGameProc.m_xMyHero.m_bJob == _JOB_DOSA )
		g_xGameProc.m_xInterface.m_xUtilWnd.UseCharm(nMagicID);

	DWORD dwTime = timeGetTime();
	CHAR szMsg[12];

	ZeroMemory(&szMsg, sizeof(12));

	sprintf(szMsg, "%d", dwTime);

	fnMakeDefMessage(&m_sendDefMsg, CM_SPELL, MAKELONG(nTargetX, nTargetY), LOWORD(nTargetID), (WORD)nMagicID, HIWORD(nTargetID));
	g_xGameProc.m_bUseSpell = TRUE;
	g_xGameProc.m_dwSpellTimer = dwTime;
	SendPacket(&m_sendDefMsg, szMsg);
}


VOID CClientSocket::SendThrowMsg(WORD wIdent, INT nTargetX, INT nTargetY, INT nTargetID)
{
	DWORD dwTime = timeGetTime();
	CHAR szMsg[12];

	ZeroMemory(&szMsg, sizeof(12));

	sprintf(szMsg, "%d", dwTime);

	fnMakeDefMessage(&m_sendDefMsg, wIdent, MAKELONG(nTargetX, nTargetY), LOWORD(nTargetID), 0, HIWORD(nTargetID));
	SendPacket(&m_sendDefMsg, szMsg);
}

VOID CClientSocket::SendOpenDoor(INT nX, INT nY, INT nIdx)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_OPENDOOR, nIdx, (WORD)nX, (WORD)nY, 0);
	SendPacket(&m_sendDefMsg, NULL);
}

void CClientSocket::SendNPCMessage(WORD wIdent, DWORD dwNpcId, INT reg, char *pszMsg)
{
	fnMakeDefMessage(&m_sendDefMsg, wIdent, dwNpcId, 0, 0, (WORD)reg);
	SendPacket(&m_sendDefMsg, pszMsg);
}

void CClientSocket::SendGetDetailItem(DWORD dwNpcId, INT nIndex, CHAR* szItemName)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_USERGETDETAILITEM, dwNpcId,(WORD)nIndex, 0, 0);
	SendPacket(&m_sendDefMsg, szItemName);
}

void CClientSocket::SendBuyItem(DWORD dwNpcId, CHAR* szItemName, INT nItem)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_USERBUYITEM, dwNpcId, LOWORD(nItem),HIWORD(nItem), 0);
	SendPacket(&m_sendDefMsg, szItemName);
}

void CClientSocket::SendBuyGood(DWORD dwNpcId, CHAR* szItemName, INT nItem, INT nCount)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_USERBUYITEM, dwNpcId,LOWORD(nItem), HIWORD(nItem), nCount);
	SendPacket(&m_sendDefMsg, szItemName);
}

void CClientSocket::SendMakeDrug(DWORD dwNpcId, CHAR* szItemName)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_USERMAKEDRUGITEM, dwNpcId, 0, 0, 0);
	SendPacket(&m_sendDefMsg, szItemName);
}

void  CClientSocket::SendTakeBackItem(DWORD dwNpcId, CHAR* szItemName, INT nItem, INT nCount)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_USERTAKEBACKSTORAGEITEM, dwNpcId,LOWORD(nItem), HIWORD(nItem), nCount);
	SendPacket(&m_sendDefMsg, szItemName);
}

// 추가 창고
VOID
CClientSocket::SendTakeBackItemEx(DWORD dwNpcId, CHAR* szItemName, INT nItem, INT nCount)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_USERTAKEBACKSTORAGEITEMEX, dwNpcId,LOWORD(nItem), HIWORD(nItem), nCount);
	SendPacket(&m_sendDefMsg, szItemName);
}

VOID
// 추가 가방 2006.08.18 가방간 아이템 이동
CClientSocket::ItemMoveBetweenBags( INT nItemMakeIndex, CHAR* pItemName )
{
	WORD wParam		= LOWORD( nItemMakeIndex );
	WORD wTag		= HIWORD( nItemMakeIndex );
	fnMakeDefMessage( &m_sendDefMsg, CM_ITEMMOVEBETWEENBAGS, 0, wParam, wTag, 0 );
	SendPacket( &m_sendDefMsg, pItemName );
}

// *** For Group
void CClientSocket::SendCreateGroup(char *pszWho)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_CREATEGROUP, 0, 0, 0, 0);
	SendPacket(&m_sendDefMsg, pszWho);
}

void CClientSocket::SendGroupMode(BOOL fFlag)
{
	if (fFlag)
		fnMakeDefMessage(&m_sendDefMsg, CM_GROUPMODE, 0, 1, 0, 0); // On
	else
		fnMakeDefMessage(&m_sendDefMsg, CM_GROUPMODE, 0, 0, 0, 0); // Off

	SendPacket(&m_sendDefMsg, NULL);
}

void CClientSocket::SendAddGroupMember(char *pszWho)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_ADDGROUPMEMBER, 0, 0, 0, 0);
	SendPacket(&m_sendDefMsg, pszWho);
}

void CClientSocket::SendDelGroupMember(char *pszWho)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_DELGROUPMEMBER, 0, 0, 0, 0);
	SendPacket(&m_sendDefMsg, pszWho);
}

// 타인상태보기.
VOID CClientSocket::SendQueryUserState(INT nID, INT nX, INT nY)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_QUERYUSERSTATE, nID, (WORD)nX, (WORD)nY, 0);
	SendPacket(&m_sendDefMsg, NULL);
}

// *** For Guild
void CClientSocket::SendGuildHome()
{
	fnMakeDefMessage(&m_sendDefMsg, CM_GUILDHOME, 0, 0, 0, 0);
	SendPacket(&m_sendDefMsg, NULL);
}

void CClientSocket::SendGuildMemberList()
{
	fnMakeDefMessage(&m_sendDefMsg, CM_GUILDMEMBERLIST, 0, 0, 0, 0);
	SendPacket(&m_sendDefMsg, NULL);
}

void CClientSocket::SendGuildAddMem(char *pszWho)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_GUILDADDMEMBER, 0, 0, 0, 0);
	SendPacket(&m_sendDefMsg, pszWho);
}

void CClientSocket::SendGuildDelMem(char *pszWho)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_GUILDDELMEMBER, 0, 0, 0, 0);
	SendPacket(&m_sendDefMsg, pszWho);
}

void CClientSocket::SendGuildUpdateNotice(char *pszNotice)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_GUILDUPDATENOTICE, 0, 0, 0, 0);
	SendPacket(&m_sendDefMsg, pszNotice);
}

void CClientSocket::SendGuildUpdateGrade(char *pszRank)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_GUILDUPDATERANKINFO, 0, 0, 0, 0);
	SendPacket(&m_sendDefMsg, pszRank);
}

// *** For Siege
VOID CClientSocket::SendAttackShooter(INT nLocate)
{
 	fnMakeDefMessage(&m_sendDefMsg, CM_ATTACKSHOOTER, nLocate, 0, 0, 0);
	SendPacket(&m_sendDefMsg, NULL);
}

VOID CClientSocket::SendMoveShooter()
{
 	fnMakeDefMessage(&m_sendDefMsg, CM_MOVESHOOTER, 0, 0, 0, 0);
	SendPacket(&m_sendDefMsg, NULL);
}

VOID CClientSocket::SendWaitShooter()
{
 	fnMakeDefMessage(&m_sendDefMsg, CM_WAITSHOOTER, 0, 0, 0, 0);
	SendPacket(&m_sendDefMsg, NULL);
}

VOID CClientSocket::SendChargeShooter(INT nAmount)
{
 	fnMakeDefMessage(&m_sendDefMsg, CM_CHARGESHOOTER, nAmount, 0, 0, 0);
	SendPacket(&m_sendDefMsg, NULL);
}

// *** For Market
VOID CClientSocket::SendNextPageMarket(INT nNpcId)
{
	// 포인트상점
	if( g_xGameProc.m_xInterface.m_xMarketWnd.mUserMarket_bIsPointMarket )
		fnMakeDefMessage( &m_sendDefMsg, CM_NEXTPAGEUSERPOINTMARKET, nNpcId, 0, 0, 0 );
	else
		fnMakeDefMessage(&m_sendDefMsg, CM_NEXTPAGEUSERMARKET, nNpcId, 0, 0, 0);
	SendPacket(&m_sendDefMsg, NULL);
}

VOID CClientSocket::SendPrevPageMarket(INT nNpcId)
{
	if( g_xGameProc.m_xInterface.m_xMarketWnd.mUserMarket_bIsPointMarket )
		fnMakeDefMessage(&m_sendDefMsg, CM_PREVPAGEUSERPOINTMARKET, nNpcId, 0, 0, 0);
	else
		fnMakeDefMessage(&m_sendDefMsg, CM_PREVPAGEUSERMARKET, nNpcId, 0, 0, 0);
	SendPacket(&m_sendDefMsg, NULL);
}

VOID CClientSocket::SendRefreshMarket(INT nNpcId)
{
	if( g_xGameProc.m_xInterface.m_xMarketWnd.mUserMarket_bIsPointMarket )
		fnMakeDefMessage(&m_sendDefMsg, CM_REFRESHPAGEUSERPOINTMARKET, nNpcId, 0, 0, 0);
	else
		fnMakeDefMessage(&m_sendDefMsg, CM_REFRESHPAGEUSERMARKET, nNpcId, 0, 0, 0);
	SendPacket(&m_sendDefMsg, NULL);
}

VOID CClientSocket::SendBuyMarketItem(INT nNpcId, INT nSellIdx, CHAR* szName)
{
	if( g_xGameProc.m_xInterface.m_xMarketWnd.mUserMarket_bIsPointMarket )
		fnMakeDefMessage(&m_sendDefMsg, CM_BUYITEMUSERPOINTMARKET, nNpcId, LOWORD(nSellIdx), HIWORD(nSellIdx), 0);
	else
		fnMakeDefMessage(&m_sendDefMsg, CM_BUYITEMUSERMARKET, nNpcId, LOWORD(nSellIdx), HIWORD(nSellIdx), 0);
	SendPacket(&m_sendDefMsg, szName);
}

VOID CClientSocket::SendSearchMarket(INT nNpcId, CHAR* szMsg)
{
	if( g_xGameProc.m_xInterface.m_xMarketWnd.mUserMarket_bIsPointMarket )
		fnMakeDefMessage(&m_sendDefMsg, CM_SEARCHPAGEUSERPOINTMARKET, nNpcId, 0, 0, 0);
	else
		fnMakeDefMessage(&m_sendDefMsg, CM_SEARCHPAGEUSERMARKET, nNpcId, 0, 0, 0);
	SendPacket(&m_sendDefMsg, szMsg);
}

VOID CClientSocket::SendMyItemtoMarket(INT nNpcId, CLIENTADDSELLITEM stSellItem, INT nCount)
{
	CHAR				szInfo[512];
	INT					nDevider = 13;

	wsprintf(szInfo, "%s%c%d%c%d%c%s", stSellItem.szItemName, nDevider, stSellItem.nItemMakeIdx, nDevider, stSellItem.nPrice, nDevider, stSellItem.szDesc);

	if( g_xGameProc.m_xInterface.m_xMarketWnd.mUserMarket_bIsPointMarket )
		fnMakeDefMessage(&m_sendDefMsg, CM_ADDITEMUSERPOINTMARKET, nNpcId, LOWORD(nCount), HIWORD(nCount), 0);
	else
		fnMakeDefMessage(&m_sendDefMsg, CM_ADDITEMUSERMARKET, nNpcId, LOWORD(nCount), HIWORD(nCount), 0);
	SendPacket(&m_sendDefMsg, szInfo);
}

VOID CClientSocket::SendTakeBackMarketItem(INT nNpcId, INT nSellIdx)
{
	if( g_xGameProc.m_xInterface.m_xMarketWnd.mUserMarket_bIsPointMarket )
		fnMakeDefMessage(&m_sendDefMsg, CM_CANCELITEMUSERPOINTMARKET, nNpcId, LOWORD(nSellIdx), HIWORD(nSellIdx), 0);
	else
		fnMakeDefMessage(&m_sendDefMsg, CM_CANCELITEMUSERMARKET, nNpcId, LOWORD(nSellIdx), HIWORD(nSellIdx), 0);
	SendPacket(&m_sendDefMsg, NULL);
}

VOID
// 포인트 로드 요청
CClientSocket::SendReloadUserPoint()
{
	fnMakeDefMessage( &m_sendDefMsg, CM_RELOADUSERPOINT, 0, 0, 0, 0 );
	SendPacket( &m_sendDefMsg, NULL );
}

// 원보상점
VOID
// 상점 아이템 구매
CClientSocket::SendBuyMarketExItem( INT nIdentity, INT nCount )
{
	INT nRecog = nIdentity;
	WORD wParam = nCount;

	fnMakeDefMessage( &m_sendDefMsg, CM_BUYITEM, nRecog, wParam, 0, 0 );
	SendPacket( &m_sendDefMsg, NULL );
}

VOID
// 선물 보내기
CClientSocket::SendGiftMarketExItem( INT nIdentity, INT nCount, CHAR* pCharName )
{
	INT nRecog = nIdentity;
	WORD wParam = nCount;
	CHAR szName[ 25 ];
	sprintf( szName, "%s", pCharName );

	fnMakeDefMessage( &m_sendDefMsg, CM_SENDITEMGIFT, nRecog, wParam, 0, 0 );
	SendPacket( &m_sendDefMsg, szName );
}


// *** For Messenger
VOID CClientSocket::SendNewDhl(CLIENTNEWDHL stNewDhl)
{
	CHAR				szInfo[600];

	fnMakeDefMessage(&m_sendDefMsg, CM_SENDNEWDHL, 0, 0, 0, 0);
	SendPacket2(&m_sendDefMsg, (char*)(&stNewDhl), sizeof(CLIENTNEWDHL));
}

VOID CClientSocket::SendRefreshMailBox(INT nIdx)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_REFRESHDHLBOX, 0, nIdx, 0, 0);	
	SendPacket(&m_sendDefMsg, NULL);
}

VOID CClientSocket::SendReadADhl(INT nIdx, INT nWhere)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_READDHLMESSAGE, nIdx, nWhere, 0, 0);	
	SendPacket(&m_sendDefMsg, NULL);
}

VOID CClientSocket::SendDeleteDhl(INT nIdx, INT nWhere)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_DELETEINBOXDHL, nIdx, nWhere, 0, 0);	
	SendPacket(&m_sendDefMsg, NULL);
}

VOID CClientSocket::SendCancelDhl(INT nIdx)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_CANCELSENTDHL, nIdx, 0, 0, 0);	
	SendPacket(&m_sendDefMsg, NULL);
}

VOID CClientSocket::SendMagicCode(CHAR* pszMsg)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_ACCPETMAGICCODE, 0, 0, 0, 0);
	SendPacket(&m_sendDefMsg, pszMsg);
}

VOID CClientSocket::SendFaceImg(CHAR* pszMsg, INT nFileLen)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_UPDATEFACEIMAGE, 0, 0, 0, 0);
	SendPacket(&m_sendDefMsg, pszMsg, nFileLen);
}

VOID CClientSocket::RequestFaceImg(CHAR* pszCharName)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_REQUESTFACEIMAGE, 0, 0, 0, 0);
	SendPacket(&m_sendDefMsg, pszCharName);
}

VOID CClientSocket::SendCardNum(CHAR* pszCharName)
{
	fnMakeDefMessage(&m_sendDefMsg, CM_CARDIDPASSWORD, 0, 0, 0, 0);
	SendPacket(&m_sendDefMsg, pszCharName);
}

VOID CClientSocket::SendSetXY()
{
	fnMakeDefMessage(&m_sendDefMsg, CM_REQUESTSETXY, 0, 0, 0, 0);
	SendPacket(&m_sendDefMsg, NULL);
}

#ifndef _CLIENTSOCKET_H
#define _CLIENTSOCKET_H

#define ID_SOCKCLIENT_EVENT_MSG		WM_USER + 1000

#include <assert.h>
#include "orzlib/streambf.h"

class CClientSocket
{
public:
	//
	// 수신 버퍼
	//
	CStreamBuffer< char >	m_recvBuf;

	//
	// SendPacket() 호출마다 Stack Variable 사용을 피하기 위해 미리 선언한다.
	//
	int						m_sendID;
	_TDEFAULTMESSAGE		m_sendDefMsg;
	char					m_sendHeader[32];
	char					m_sendBody	[8192];
	char					m_sendPacket[8192 * 2];	

public:
	CClientSocket();
	virtual ~CClientSocket();

	SOCKET			m_sockClient;
	CWHDefProcess*	m_pxDefProc;

public:
	unsigned long GetINetAddr(CHAR* pszDotAddress);

	BOOL		InitSocket(HWND hWnd);	
	BOOL		ConnectToServer(HWND hWnd, CHAR* szID, INT nPort);
	BOOL		CheckSocketError(LPARAM lParam);
	BOOL		DisconnectToServer();
//	VOID		SendToServer(CHAR *pszPacket);
	VOID		SendPacket(_TDEFAULTMESSAGE* lpDefMsg, char *pszData, INT nLen = 0);
	VOID		SendPacket2(_TDEFAULTMESSAGE* lpDefMsg, char *pszData, INT nSize);

	// For Login
	VOID		OnLogin(char *pszID, char *pszPassword);
	VOID		OnSelectServer(char *pszServerName);
	VOID		OnChangePassword(char *pszID, char *pszOldPassword, char *pszNewPassword);
	VOID		OnNewAccount(char *pszNewAccount);

	// For Character Select
	VOID		OnQueryChar();
	VOID		OnNewChar( char *pszId, int nHair, int nJob, int nSex );
	VOID		OnDelChar( char *pszCharName );
	VOID		OnSelChar( char *pszCharName );
	VOID		OnChangeCharName(char *pszName);

	// 퀘스트창.
	VOID		SendQueryQuest(VOID);
	VOID		SendQuerySubQuest(int nIdx);
	VOID		SendQueryDetail(int nIdx,int SubIdx);

	// For Game playing
	void		SendNoticeOK();

	void		SendNPCMessage(WORD wIdent,DWORD dwNpcId,INT reg,CHAR* szTxt);			// MOON
	void		SendGetDetailItem(DWORD dwNpcId,INT nIndex,CHAR* szItemName);			// MOON
//	void		SendBuyItem(DWORD dwNpcId,CHAR* szItemName,CHAR* szItemIndex);			// MOON
	void		SendBuyItem(DWORD dwNpcId, CHAR* szItemName, INT nItem);
	void		SendBuyGood(DWORD dwNpcId, CHAR* szItemName, INT nItem, INT nCount = 1);
	void		SendMakeDrug(DWORD dwNpcId, CHAR* szItemName);
	void		SendTakeBackItem(DWORD dwNpcId, CHAR* szItemName, INT nItem, INT nCount = 0);

	VOID		SendOpenDoor(INT nX, INT nY, INT nIdx);
	VOID		SendQueryMsg(WORD wIdent);
	VOID		SendActMsg(WORD wIdent, INT nX, INT nY, INT nDir, DWORD dwTime = 0);	
	VOID		SendHitMsg(WORD wIdent, INT nX, INT nY, INT nDir, WORD wHitStyle, INT nTargetID);	
	VOID		SendRideMsg(WORD wIdent, INT nDir, BOOL bRide);
	VOID		SendSpellMsg(INT nMagicID, INT nTargetX, INT nTargetY, INT nTargetID);
	VOID		SendThrowMsg(WORD wIdent, INT nTargetX, INT nTargetY, INT nTargetID);

	VOID		SendSay(CHAR *pszSay);
//	VOID		SendRunLogin(CHAR* szLoginID, CHAR* szCharName, INT nCertification, INT VersionNum);
	VOID		SendRunLogin(CHAR* szLoginID, CHAR* szCharName, INT nCertification, INT VersionNum, INT nUpgradeLevel);  // lee wun gyo
	VOID		SendTakeOnOffItem(WORD wIdent, BYTE bEquipNum, CHAR* szItemName, INT nItemIdx);
	VOID		SendQueryName(INT nRecog, INT nX, INT nY);
	VOID		SendQueryMonsterInfo(INT nRecog, INT nX, INT nY);
	VOID		SendMagicKeyChange(INT nKeyNum, INT nMagicID);
	VOID		SendItemIndex(WORD wIdent, INT nItemIndex, CHAR* pszItemName);
	VOID		UseWearItem(WORD wIdent, INT nLocation);
	VOID		SendPickUp(INT nX, INT nY);
	VOID		SendButchAnimal(INT nX, INT nY, INT nDir, INT nActorID);
	VOID		SendNPCClick(INT nRecog);

	VOID		SendDropGold(INT nGold);
	VOID		SendDropMultipleItem(INT nItemIndex, INT nCount, CHAR* pszItemName);

	VOID		SendWantMMap();

	VOID		SendSellItem(INT nItemIdx, INT nMerchantID, CHAR* pszItemName, INT nCount = 0);
	VOID		SendQueryPrice(INT nItemIdx, INT nMerchantID, CHAR* pszItemName);
    VOID		SendRepairItem(INT nItemIdx, INT nMerchantID, CHAR* pszItemName);
    VOID		SendQueryRepairCost(INT nItemIdx, INT nMerchantID, CHAR* pszItemName);
    VOID		SendStorageItem(INT nItemIdx, INT nMerchantID, CHAR* pszItemName, INT nCount = 0);
	VOID		SendChargeItem(CHAR* szItemName, INT nCount, INT nMakeIdx);

	void		SendCreateGroup(char *pszWho);
	void		SendGroupMode(BOOL fFlag);
	void		SendAddGroupMember(char *pszWho);
	void		SendDelGroupMember(char *pszWho);


	// 다른유저 상태 보기.
	VOID		SendQueryUserState(INT nID, INT nX, INT nY);

	// 창고 관련
	VOID		SendInvenItemToStorage(CHAR* szItemName, INT nMakeIdx, WORD wLocate, INT nCount, WORD wSlotNum);

	// 교환창관련.
	VOID		SendDealTry(CHAR* szName);
	VOID		SendCancelDeal();
	VOID		SendAddDealItem(CHAR* szItemName, INT nMakeIdx, INT nCount = 0);
	VOID		SendDelDealItem(CHAR* szItemName, INT nMakeIdx);
	VOID		SendChangeDealGold(INT nGold);
	VOID		SendDealEnd();

	// 발석거 관련
	VOID		SendAttackShooter(INT nLocate);
	VOID		SendMoveShooter();
	VOID		SendWaitShooter();
	VOID		SendChargeShooter(INT nAmount);

	// 아이템거래
	VOID		SendNextPageMarket(INT nNpcId);
	VOID		SendPrevPageMarket(INT nNpcId);
	VOID		SendRefreshMarket(INT nNpcId);
	VOID		SendBuyMarketItem(INT nNpcId, INT nSellIdx, CHAR* szName);
	VOID		SendSearchMarket(INT nNpcId, CHAR* szMsg);
	VOID		SendMyItemtoMarket(INT nNpcId, CLIENTADDSELLITEM stSellItem, INT nCount);
	VOID		SendTakeBackMarketItem(INT nNpcId, INT nSellIdx);

	// 메신저
	VOID		SendNewDhl(CLIENTNEWDHL stNewDhl);
	VOID		SendRefreshMailBox(INT nIdx);
	VOID		SendReadADhl(INT nIdx, INT nWhere);
	VOID		SendDeleteDhl(INT nIdx, INT nWhere);
	VOID		SendCancelDhl(INT nIdx);

	// FaceUp
	VOID		SendFaceImg(CHAR* pszMsg, INT nFileLen);
	VOID		RequestFaceImg(CHAR* pszCharName);

	void		SendGuildHome();
	void		SendGuildMemberList();
	void		SendGuildAddMem(char *pszWho);
	void		SendGuildDelMem(char *pszWho);
	void		SendGuildUpdateNotice(char *pszNotice);
	void		SendGuildUpdateGrade(char *pszRank);

    // Game Guard
	VOID		SendGameGuard(CHAR* pszData);

	VOID		SendMagicCode(CHAR* pszMsg);

	VOID		SendSetXY();
	LRESULT		OnSocketMessage(WPARAM wParam, LPARAM lParam);
	void		OnConnect( SOCKET sdHost );
	void		OnClose( SOCKET sdHost );
	void		OnRecv( SOCKET sdHost );

protected:
};

#endif // _CLIENTSOCKET_H
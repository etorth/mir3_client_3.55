#ifndef _CUSERSTATEWND_H
#define _CUSERSTATEWND_H

#pragma pack(1)

typedef struct tagUSERSTATE
{
	INT		nFeature;
	CHAR	pszUserName[25];
	INT		nNameClr;
	WORD    wHairColor;
	CHAR	pszGuildName[30];
	CHAR	pszGuildRankName[14];
	BYTE	m_bGuildFlag;
    BYTE	m_bFlagColorR;
    BYTE	m_bFlagColorG;
    BYTE	m_bFlagColorB;
	BYTE	m_bWeaponColor;
	CLIENTITEMRCD	stEquipItem[_EQUIP_MAX_CELL];
	CHAR	pszMateName[25];
	BYTE	m_bTitlenumber;
	BYTE	bJob;
}USERSTATE, *LPUSERSTATE;

#pragma pack(8)


class CUserStateWnd : public CGameWnd
{ 
private:
protected:
	CGameBtn				m_xUStateCloseBtn;
	CGameBtn				m_xUStateGroupBtn;
	CGameBtn				m_xUStateWhisperBtn;
	CGameBtn				m_xUStateGiftBtn;

	USERSTATE				m_stUserState;
	FEATURE					m_stUserFeature;

	RECT					m_rcUserCell[_EQUIP_MAX_CELL];
	ITEMSET					m_stUserEquipItem[_EQUIP_MAX_CELL];

	CHAR					m_pszUserName[25];
	CHAR					m_pszGuildName[30];
	CHAR					m_pszGuildRankName[15];
	CHAR					m_pszMateName[25];

	DWORD					m_dwLastShineTick;
	DWORD					m_dwShineCurrDelay;
	DWORD					m_dwCurrShineFrm;

	DWORD					m_dwLastSwordTick;
	INT						m_nLastSwordFrame;

	INT						m_nFameIdx;
	DWORD					m_dwFameTimer;

	INT					m_nCharmEftFrm;
	INT					m_dwCharmTimer;

	INT					m_nGhostAmorEftIdx;
	DWORD				m_dwGhostAmorTimer;

	INT					m_nOsungEftIdx;
	DWORD				m_dwOsungEftTimer;

	// 2006.07.03 - 신규의복 이펙트
	INT					m_nYonglinEftIdx;
	DWORD				m_dwYonglinEftTimer;

	INT					m_nMyungEftIdx;
	DWORD				m_dwMyungEftTimer;

	INT					m_nReddragonEftIdx;
	DWORD				m_dwReddragonEftTimer;

public:
	CUserStateWnd();
	~CUserStateWnd();
	VOID	CreateUserStateWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove);
	VOID	ShowUserStateWnd();

	VOID	SetUserState(LPUSERSTATE pstUserState);
	VOID	SetStatusBtnInit();
	VOID	ShowUserItemState();
	BOOL	AddEquipItem(CItem xItem, INT nEquipNum);
	INT		GetEquipNum(POINT ptMouse);

	virtual VOID Init();
	virtual VOID Destroy();

public:
//  메시지 함수.
	BOOL	OnLButtonDown(POINT ptMouse);
	BOOL	OnLButtonDoubleClick(POINT ptMouse);
	BOOL	OnLButtonUp(POINT ptMouse);
	VOID	OnMouseMove(POINT ptMouse);

	VOID	OnScrollDown();
	VOID	OnScrollUp();

	VOID	RenderShine(INT nX, INT nY);
};


#endif // _CUSERSTATEWND_H

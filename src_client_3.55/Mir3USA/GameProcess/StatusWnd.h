#ifndef _CSTATUSWND_H
#define _CSTATUSWND_H



class CStatusWnd : public CGameWnd
{ 
private:
protected:
	BYTE				m_bType;						// 0 : ����â. 1 : ĳ���� ����â.  2 : ĳ���� ���� ����â.
	CGameBtn			m_xStatusBtn[_MAX_STAUTS_BTN];

	RECT				m_rcCell[_EQUIP_MAX_CELL];

	RECT				m_rcAbility[9];

public:
	CHAR				m_szEquipItemIdx[_EQUIP_MAX_CELL][12];
	ITEMSET				m_stEquipItem[_EQUIP_MAX_CELL];
	ITEMSET				m_stTakeOnItemSet;				// ������ų�������� ���뿩�� �޽����� ���������� �ӽ������� �����Ѵ�.
	BOOL				m_bCheckShow[26];				// �������� � ��ġ�� �÷��ִ��� �����ֱ� ���� �÷���
														// 0: �ı� 1:��� 2:�ڿ��踶�� 3:��ȥ�踶�� 4:�������
														// 5~11 : ���ݿ��� ȭ~ȯ��
														// 12~18 :  ���ѿ��� ȭ~ȯ��
														// 19~25 :  ���ѿ��� ȭ~ȯ��

	RECT				m_rcAtomTooltip[3][7];
	DWORD				m_dwLClickTime;

	DWORD				m_dwLastShineTick;
	DWORD				m_dwShineCurrDelay;
	DWORD				m_dwCurrShineFrm;

	DWORD				m_dwLastSwordTick;
	INT					m_nLastSwordFrame;

	INT					m_nFameIdx;
	DWORD				m_dwFameTimer;

	INT					m_nTestFame;

	INT					m_nCharmEftFrm;
	INT					m_dwCharmTimer;

	DWORD				m_dwSwordEftTimer;
	INT					m_nSwordEftIdx;

	INT					m_nGhostAmorEftIdx;
	DWORD				m_dwGhostAmorTimer;

	INT					m_nOsungEftIdx;
	DWORD				m_dwOsungEftTimer;
public:
	CStatusWnd();
	~CStatusWnd();

	virtual VOID Init();
	virtual VOID Destory();

	__inline VOID SetStatusWndType(BYTE bType)
	{
		m_bType = bType;
		switch ( m_bType )
		{
		case _TYPE_EQUIP:
			ResetWndImg(_NEW_WNDIMGIDX_ITEMSET, m_rcWnd.left, m_rcWnd.top, 310, 466);
			break;
		case _TYPE_STATUS:
			ResetWndImg(_NEW_WNDIMGIDX_STATUS, m_rcWnd.left, m_rcWnd.top, 310, 466);
			m_rcWnd.left -= 241;
			m_rcWnd.right-= 241;
			break;
		}
	}
	__inline BYTE GetStatusWndType()
	{
		return m_bType;
	}

	VOID	CreateStatusWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove);
	VOID	ShowStatusWnd();
	VOID	SetStatusBtnInit();

public:
	VOID	ShowCharEquipWnd();
	VOID	ShowEquipItemState();
	BOOL	CheckEquipItem(CItem* pxItem, BYTE bEquipCell, POINT ptMouse);
	INT		GetEquipNum(POINT ptMouse);
	BOOL	CheckIsItemExisted(INT nEquipNum);
	VOID	DeleteEquipItem(INT nEquipNum);
	BOOL	DeleteEquipItem(INT nMakeIndex, CHAR* szName);
	VOID	DeleteAllEquipItem();
	BOOL	AddEquipItem(CItem xItem, INT nEquipNum, BOOL bUseEquipNum = TRUE);
	BOOL	ExtractEquipItem(CItem* pxItem, INT nEquipNum);
	VOID	ChangeEquipWithCommon(INT nEquipNum, LPCOMMONITEMSET pstCommonItemSet);
	VOID	SetEquipFromCommon(INT nEquipNum, LPCOMMONITEMSET pstCommonItemSet);
	VOID	SetCommonFromEquip(INT nEquipNum, LPCOMMONITEMSET pstCommonItemSet);
	VOID	SetTakeOnFromEquip(INT nEquipNum);
	VOID	SetTakeOnFromCommon(INT nEquipNum, LPCOMMONITEMSET pstCommonItemSet);
	VOID	SetEquipFromTakeOn();

	VOID	ShowCharStatus();

	BOOL	OnLButtonDown(LPCOMMONITEMSET pstItemSet, POINT ptMouse);
	BOOL	OnLButtonUp(LPCOMMONITEMSET pstItemSet, POINT ptMouse);
	VOID	OnMouseMove(POINT ptMouse);
	BOOL	OnLButtonDoubleClick(LPCOMMONITEMSET pstCommonItemSet, POINT ptMouse);


	VOID	RenderShine(INT nX, INT nY);
};


#endif // _CSTATUSWND_H
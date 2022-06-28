#ifndef _CMAGICWND_H
#define _CMAGICWND_H



#pragma pack(1)
typedef struct tagSTANDARDMAGIC
{
	WORD	wMagicID;
	char	szMagicName[31];
	BYTE	bEffectType;
	BYTE	bEffect;
	WORD	wSpell;
	WORD	wMinPower;
	BYTE	btNeed[6];
	INT		nTrain[6];
	BYTE	btMaxTrainLevel;
	BYTE	btJob;
	INT		nDelayTime;
	BYTE	bDefSpell;
	BYTE	btDefMinPower;
	WORD	wMaxPower;
	BYTE	btDefMaxPower;
	char	szDesc[16];
}STANDARDMAGIC, *LPSTANDARDMAGIC;

typedef struct tagCLIENTMAGICRCD
{
	INT				nCurrTrain;
	CHAR			bUseKey;
	BYTE			bLevel;
	STANDARDMAGIC	stStdMagic;
}CLIENTMAGICRCD, *LPCLIENTMAGICRCD;

typedef struct tagMAGICICONPOS
{
	INT				nMagicID;
	INT				nPosX;
	INT				nPosY;
}MAGICICONPOS, *LPMAGICICONPOS;
#pragma pack(8)



class CMagicWnd : public CGameWnd
{ 
private:
protected:
	BYTE					m_bTypeMagic;						// Type ==> 0(화), 1(빙), 2(뢰), 3(풍), 4(신성), 5(암흑), 6(환영), 7(무)
	INT						m_nStartLineNum[_MAX_TYPE_MAGIC];	// 0(화), 1(빙), 2(뢰), 3(풍), 4(신성), 5(암흑), 6(환영), 7(무) 마법창의 처음 라인의 번호. (마법리스트에 들어있는개수만큼 스크롤할수있다..)

	RECT					m_rcMagicCell[_MAGIC_MAX_CELL];		// 마법세팅창의 각셀들의 영역.
	CGameBtn				m_xMagicCloseBtn;
	CGameBtn				m_xMagicTypeBtn[_MAX_TYPE_MAGIC];	// 0(화), 1(빙), 2(뢰), 3(풍), 4(신성), 5(암흑), 6(환영), 7(무)

	CScrlBar				m_xWndScrBar;

public:
	CList<CLIENTMAGICRCD>	m_xMyMagicList[_MAX_TYPE_MAGIC];	// 0(화), 1(빙), 2(뢰), 3(풍), 4(신성), 5(암흑), 6(환영), 7(무)
	BYTE					m_bMyMagicCnt;						// 전체마법의 갯수.

	BYTE					m_bMagicKeyTable[_MAGIC_MAX_KEY];
	INT 					m_nShowMagicNum;
	CHAR*					m_pszMagicExplain;

	MAGICICONPOS			m_xMagicIconPos[_MAX_TYPE_MAGIC][_MAX_MAGICSLOT];

	INT						m_nSelectedMagic[_MAX_TYPE_MAGIC];

	BOOL					m_bWantSetKey;
	POINT					m_ptSetKey;

	RECT					m_rcSetKey;


	INT						m_nStartPos;
	INT						m_nMaxPos;

public:

	CMagicWnd();
	~CMagicWnd();

	virtual VOID		Init();
	virtual VOID		Destroy();

	BOOL				DecryptMem();
	VOID				ShowMagicTxt(INT nMagicID);

	VOID				CreateMagicWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend);
	VOID				ShowMagicWnd();

	VOID				SetStatusBtnInit();

	VOID				SetMyMagic(INT nMagicCnt, CHAR* pszMagic);
	VOID				DelMyMagic(INT nMagicID);
	BYTE				GetMagicType(INT nMagicID);
	LPCLIENTMAGICRCD	FindMagicRCD(INT nMagicID);
	VOID				AddNewMagic(CHAR* pszMagic);
	VOID				MagicExpUp(INT nMagicID, INT nCurrTrain, BYTE bLevel);
	VOID				SetMagicTypeBtn();

	VOID				ShowCharSetMagicWnd();
	BOOL				SetMagicKey(POINT ptMouse, BYTE bKey);
	BOOL				SetMagicKeybyMouseBtn(BYTE bKey);
	LPCLIENTMAGICRCD	GetMagicByKey(BYTE bKey);
	LPCLIENTMAGICRCD	GetMagicByMagicKey(INT nMagicKey);
	INT					GetMagicByPoint(POINT ptMouse);

	VOID				SetMagicIconPos();
	VOID				ShowSetKeyWnd();

	VOID				OnScrollDown();
	VOID				OnScrollUp();
	
public:
//  메시지 함수.
	BOOL	OnKeyDown(WPARAM wParam, LPARAM lParam, POINT ptMouse);
	BOOL	OnSysKeyDown(WPARAM wParam, LPARAM lParam, POINT ptMouse);

	BOOL	OnLButtonDown(POINT ptMouse);
	BOOL	OnLButtonUp(POINT ptMouse);
	VOID	OnMouseMove(POINT ptMouse);
	BOOL	OnLButtonDoubleClick(POINT ptMouse);
};


#endif // _CMAGICWND_H
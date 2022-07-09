#ifndef _CITEM_H
#define	_CITEM_H


#pragma pack(1)
typedef struct tagSTANDARDITEM // »õ¼­¹ö
{
	CHAR			szName[30];

	BYTE			bStdMode;          
	BYTE			bShape;            
	BYTE			bWeight;           
	BYTE			bAniCount;
	
	CHAR			sSpecialPower;

	BYTE			bItemDesc;

	WORD			wLooks;            
	WORD			wDuraMax;

	WORD			wAC;	
	WORD			wMAC;
	WORD			wDC;
	
	BYTE			MCType;
	WORD			wMC;

	BYTE			bAtomDCType;
	WORD			wAtomDC;

	CHAR			sAtomACGood;
	CHAR			sAtomACBad;

	BYTE			bNeed;             
	BYTE			bNeedLevel;        

	INT				nPrice;
	BYTE			FuncType;
	BYTE			bThrow;
	INT				nNeedFame;
}STANDARDITEM, *LPSTANDARDITEM;
typedef struct tagCLIENTITEMRCD	 
{
	STANDARDITEM	stStdItem;
	INT				nMakeIndex;
	WORD			nDura;
	INT				nDuraMax;

	BYTE			bLevel_R;
	WORD			wAmount_GB;

	CHAR			Prefix[13];	 //0629
	CHAR			Desc[14];
}CLIENTITEMRCD, *LPCLIENTITEMRCD;


typedef struct tagGROUNDITEM
{
	INT				nRecog;
	INT				nTileX;
	INT				nTileY;
	WORD			wLooks;
	INT				nThrow;
	DWORD			dwLastShineTick;
	DWORD			dwRandShineDelay;
	DWORD			dwShineCurrDelay;
	DWORD			dwCurrShineFrm;
	CHAR			szItemName[40];
}GROUNDITEM, *LPGROUNDITEM;
#pragma pack(8)


class CItem
{ 
public:
	CItem();
	~CItem();

private:
public:
	BYTE				m_bAttr;
	SHORT				m_shCellNum;
	CLIENTITEMRCD		m_stItemInfo;

	INT					m_nStateCnt;
	ITEMSTATE			m_stItemState[_ITEM_MAX_STATE];	

protected:
public:
	BOOL		SetItem(CLIENTITEMRCD stItemInfo, SHORT shInventoryNum);
	VOID		SetItemStatus(BOOL bUseStore, BOOL bUseEquip);
	VOID		SetClothStatus(BOOL bUseStore, BOOL bUseEquip);
	VOID		SetWeaponStatus(BOOL bUseStore, BOOL bUseEquip);
	VOID		SetAccessoryStatus(BOOL bUseStore, BOOL bUseEquip);
	VOID		SetEtcStatus(BOOL bUseStore, BOOL bUseEquip);
	VOID		SetBootsStatus(BOOL bUseStore, BOOL bUseEquip);
	BOOL		DrawItem(INT nX, INT nY, BYTE bItemType = _ITEM_TYPE_INVENTORY, BOOL bDrawCount = TRUE);
	BOOL		DrawItemUseColorIdx(INT nX, INT nY, INT nColorIdx, BYTE bItemType = _ITEM_TYPE_INVENTORY, BOOL bDrawCount = TRUE);	
	VOID		ShowItemStatus(INT nX, INT nY, BOOL bUseStore = FALSE, BOOL bClothShow = FALSE, BOOL bUseEquip = FALSE);
};



#endif //_CITEM_H
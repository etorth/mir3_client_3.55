#ifndef _CITEM_H
#define	_CITEM_H


#pragma pack(1)
//typedef struct tagSTANDARDITEM
//{
//	CHAR			szName[20];
//
//	DWORD			dwUnknown1;
//	DWORD			dwUnknown2;
//	SHORT			sUnknown3;//30
//
//	BYTE			bStdMode; //(pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bStdMode == 0 || pstCommonItemSet->xItem.m_stItemInfo.stStdItem.bStdMode == 3)
//							  //这是可以放在belt上的物品,也是可以"捆"的物品,魔法水,回城卷等
//	BYTE			bShape;            
//	BYTE			bWeight;           
//	BYTE			bAniCount;//34
//	
//	BYTE			sSpecialPower;           
//
//	BYTE			bNeedIdentify;
//
//	WORD			wLooks;            
//	WORD			wDuraMax;//持久 40
//
//	WORD			wAC;			
//	WORD			wMAC;	//44		
//
//	WORD			wDC;			
//	WORD			wMC;//48			
//
//	WORD			wSC;			
//	BYTE			bNeed;             
//	BYTE			bNeedLevel; //52       
//
//	int				nUnkown4;
//	WORD			wUnkown5;
//	int				nUnkown6;
//	WORD			wUnkown7;
//
//	int				nPrice;//56
//}STANDARDITEM, *LPSTANDARDITEM;

//8/8 参照数据库
typedef struct tagSTANDARDITEM
{
	char		szName[20];			// 酒捞袍 捞抚 (玫窍力老八)
	char		szPrefixName[10];
	BYTE		bStdMode;          //
	BYTE		bShape;            // 屈怕喊 捞抚 (枚八)
	BYTE		bWeight;           // 公霸
	BYTE		bAniCount;         // 1焊促 农搁 局聪皋捞记 登绰 酒捞袍
	BYTE		bSource;           // 犁龙 (0篮 扁夯, 1焊促 农搁 歹 窜窜窃)
	BYTE		bNeedIdentify;     // $01 (酒捞错萍颇捞 救 等 巴)
	WORD		wLooks;             // 弊覆 锅龋
	WORD		wDuraMax;

	WORD		wAC;				// 规绢仿
	WORD		wMAC;				// 付亲仿
	WORD		wDC;				// 单固瘤
	WORD		wMC;				// 贱荤狼 付过 颇况
	WORD		wSC;				// 档荤狼 沥脚仿
	WORD		wUnkown1;
	WORD		wUnkown2;

	BYTE		bNeed;             // 0:Level, 1:DC, 2:MC, 3:SC
	BYTE		bNeedLevel;        // 1..60 level value...
	UINT		nPrice;
	WORD		wStock;
}STANDARDITEM, *LPSTANDARDITEM;

typedef struct tagCLIENTITEMRCD
{
	STANDARDITEM	stStdItem;
	int				nMakeIndex;
	WORD			nDura;
	WORD			nDuraMax;//耐力
	BYTE			bDrugNum;//ydq 数量
	BYTE			bDrugNum2;

	BYTE			b1;
	BYTE			b2;
	BYTE			b3;
	BYTE			b4;
	BYTE			b5;
	BYTE			b6;
	BYTE			b7;
	BYTE			b8;

}CLIENTITEMRCD, *LPCLIENTITEMRCD;

typedef struct tagGROUNDITEM
{
	INT				nRecog;
	SHORT			shTileX;
	SHORT			shTileY;
	WORD			wLooks;
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
	BYTE			m_bAttr;
	SHORT			m_shCellNum;//单元格位置
	CLIENTITEMRCD	m_stItemInfo;

protected:
public:
	BOOL		SetItem(CLIENTITEMRCD stItemInfo, SHORT shInventoryNum);
	BOOL		DrawItem(INT nX, INT nY, BYTE bItemType = _ITEM_TYPE_INVENTORY);
	VOID		ShowItemStatus(INT nX, INT nY);
public:
};



#endif //_CITEM_H
// MarketEx.h
// �������� 2006.06.13 by eriastoa

#ifndef _MARKETEX_H_
#define _MARKETEX_H_

#define _MAX_MARKETEX_XCELL5			5
#define _MAX_MARKETEX_YCELL2			2

typedef struct tagSALEITEM
{
	INT				nIdentity;			// ������ ������ȣ
	STANDARDITEM	stdItem;
	WORD			wIndex;
	WORD			wDura;
	WORD			wDuraMax;

	BYTE			Desc[ 14 ];
	BYTE			bLevel_R;
	BYTE			bLevel_G;
	BYTE			bLevel_B;

	BYTE			bPermitPeriod;		// ���Ⱓ
	INT				nSalePrice;			// ����

} SALEITEM, *LPSALEITEM;

enum ALIGN_MARKETEX_ITEM
{
	MI_ALIGN_WEAPON = 1,
	MI_ALIGN_CLOTH,
	MI_ALIGN_EQUIP,
	MI_ALIGN_SKILL,
	MI_ALIGN_ETC,

	MAX_MI_ALIGN,
};

enum ALIGN_MARKETEX_ITEM_PRICE
{
	MI_ALIGN_PRICE_UPPER = 0,
	MI_ALIGN_PRICE_LOWER,

	MAX_MI_ALIGN_PRICE,
};

enum ALIGN_MARKETEX_ITEM_SEX
{
	MI_ALIGN_SEX_MALE = 0,
	MI_ALIGN_SEX_FEMALE,

	MAX_MI_ALIGN_SEX,

	MI_ALIGN_SEX_COMMON = 9,
};

enum ALIGN_MARKETEX_ITEM_JOB
{
	MI_ALIGN_JOB_JUNSA = 0,
	MI_ALIGN_JOB_SULSA,
	MI_ALIGN_JOB_DOSA,

	MAX_MI_ALIGN_JOB,

	MI_ALIGN_JOB_COMMON = 9,
};

class CMarketExWnd : public CGameWnd
{
public:
	CMarketExWnd();
	virtual ~CMarketExWnd();

	CGameBtn				mBtnWeapon;		// ����
	CGameBtn				mBtnCloth;		// �Ǻ�, ��
	CGameBtn				mBtnEquip;		// ��ű�
	CGameBtn				mBtnSkill;		// ���
	CGameBtn				mBtnEtc;		// ��Ÿ

	CGameBtn				mBtnBuy;		// ����
	CGameBtn				mBtnPresent;	// ����
	CGameBtn				mBtnCancel;		// ���

	CGameBtn				mBtnPrev;		// ���� ������
	CGameBtn				mBtnNext;		// ���� ������
	CGameBtn				mBtnClose;		// �ݱ�

	CGameBtn				mBtnPrice;		// ����
	CGameBtn				mBtnItem;		// �׸�
	CGameBtn				mBtnJob;		// ����
	
	CGameBtn				mBtnSearch;		// ã��

	RECT					mRectItems5x2[ _MAX_MARKETEX_XCELL5 * _MAX_MARKETEX_YCELL2 ];		// 5x2
	CItem					mShowItems5x2[ _MAX_MARKETEX_XCELL5 * _MAX_MARKETEX_YCELL2 ];			// ���̴� ������

	RECT					mRectSearch;	// ã�� ����
	BOOL					mbUseSearch;	// ã��?

	INT						mnNpcId;		// NPC ID
	INT						mnSelectItem;	// ���� ������
	INT						mnCurPage;		// ���� ������
	INT						mnTotalPage;	// ��ü ������
	INT						mnMouseLocated;	// ���콺 ��ġ �ε���

	BYTE					mbPriceValue;
	BYTE					mbJobValue;
	BYTE					mbSexValue;
	BYTE					mbItemValue;

	CList< CLIENTSELLITEM > mItemList;		// ������ ����Ʈ

	CList< SALEITEM >		mAlignItemLists; // ����, ����, ���� ���Ŀ� ����Ʈ
	CList< SALEITEM >		mFindItemLists; // ã�� ������ ����Ʈ
	CList< SALEITEM >		mSaleItemLists;	// ��ü ������ ����Ʈ

public:
	virtual VOID		Init();
	virtual VOID		Destroy();

	VOID				CreateMarketExWnd( INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend);
	VOID				ShowMarketExWnd();
	VOID				CloseMarketExWnd();

	VOID				FindItems();
	VOID				SetMarketExItemList( INT nPage, INT nTotalPage );
	VOID				SetSaleItem( INT nIndex, CLIENTSELLITEM* pstMarketItem, SALEITEM* pSaleItem );
	VOID				BuyItem();
	VOID				PresentItem( CHAR* pCharName );
	VOID				SetGameWndActive( BOOL bActive );
	VOID				SetAlignMarketExItemList( ALIGN_MARKETEX_ITEM align, BOOL bListClear = TRUE );
	VOID				SetAlignItemListFromPrice( ALIGN_MARKETEX_ITEM_PRICE price );
	VOID				SetAlignItemListFromSex( ALIGN_MARKETEX_ITEM_SEX sex );
	VOID				SetAlignItemListFromJob( ALIGN_MARKETEX_ITEM_JOB job );
	VOID				SetAlignItemListFromItem( ALIGN_MARKETEX_ITEM item );

	BOOL				LoadItemLists();
	VOID				DeleteItemLists();

	BOOL				OnLButtonDown( LPCOMMONITEMSET lpCommonItemSet, POINT ptMouse );
	BOOL				OnLButtonUp( LPCOMMONITEMSET lpCommonItemSet, POINT ptMouse );
	BOOL				OnMouseMove( POINT ptMouse );
	BOOL				OnKeyDown( WPARAM wParam, LPARAM lParam );
	VOID				OnScrollDown();
	VOID				OnScrollUp();
};

#endif

// MarketEx.h
// 원보상점 2006.06.13 by eriastoa

#ifndef _MARKETEX_H_
#define _MARKETEX_H_

#define _MAX_MARKETEX_XCELL5			5
#define _MAX_MARKETEX_YCELL2			2

typedef struct tagSALEITEM
{
	INT				nIdentity;			// 아이템 고유번호
	STANDARDITEM	stdItem;
	WORD			wIndex;
	WORD			wDura;
	WORD			wDuraMax;

	BYTE			Desc[ 14 ];
	BYTE			bLevel_R;
	BYTE			bLevel_G;
	BYTE			bLevel_B;

	BYTE			bPermitPeriod;		// 사용기간
	INT				nSalePrice;			// 가격

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

	CGameBtn				mBtnWeapon;		// 무기
	CGameBtn				mBtnCloth;		// 의복, 방어구
	CGameBtn				mBtnEquip;		// 장신구
	CGameBtn				mBtnSkill;		// 기능
	CGameBtn				mBtnEtc;		// 기타

	CGameBtn				mBtnBuy;		// 구입
	CGameBtn				mBtnPresent;	// 선물
	CGameBtn				mBtnCancel;		// 취소

	CGameBtn				mBtnPrev;		// 이전 페이지
	CGameBtn				mBtnNext;		// 다음 페이지
	CGameBtn				mBtnClose;		// 닫기

	CGameBtn				mBtnPrice;		// 가격
	CGameBtn				mBtnItem;		// 항목
	CGameBtn				mBtnJob;		// 직업
	
	CGameBtn				mBtnSearch;		// 찾기

	RECT					mRectItems5x2[ _MAX_MARKETEX_XCELL5 * _MAX_MARKETEX_YCELL2 ];		// 5x2
	CItem					mShowItems5x2[ _MAX_MARKETEX_XCELL5 * _MAX_MARKETEX_YCELL2 ];			// 보이는 아이템

	RECT					mRectSearch;	// 찾기 영역
	BOOL					mbUseSearch;	// 찾기?

	INT						mnNpcId;		// NPC ID
	INT						mnSelectItem;	// 선택 아이템
	INT						mnCurPage;		// 현재 페이지
	INT						mnTotalPage;	// 전체 페이지
	INT						mnMouseLocated;	// 마우스 위치 인덱스

	BYTE					mbPriceValue;
	BYTE					mbJobValue;
	BYTE					mbSexValue;
	BYTE					mbItemValue;

	CList< CLIENTSELLITEM > mItemList;		// 아이템 리스트

	CList< SALEITEM >		mAlignItemLists; // 가격, 직업, 성별 정렬용 리스트
	CList< SALEITEM >		mFindItemLists; // 찾은 아이템 리스트
	CList< SALEITEM >		mSaleItemLists;	// 전체 아이템 리스트

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

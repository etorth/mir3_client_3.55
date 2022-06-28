#ifndef _CQUESTWND_H
#define _CQUESTWND_H


typedef struct _Tag_Sub_Quest
{
	INT		nIndex;
	CHAR	pszTitle[512];
	RECT	rcBtn;
	BOOL	boDone;
	BOOL	boSelected;
	BOOL	boFilledExplanation;
	CHAR    szExplanation[1024];
}	_SUB_QUEST,*P_SUB_QUEST;

typedef struct _Tag_Main_Quest
{
	INT		nIndex;
	CHAR	pszTitle[512];
	BOOL	boDone;
	BOOL	boExpand;
	BOOL	boFilledSubQuest;
	BOOL	boSelected;
	BOOL	boFilledExplanation;
	RECT	rcBtn;
	CPDLList<_SUB_QUEST>*	pSubQuest;
	INT			nSubQuestCnt;
	CHAR    szExplanation[1024];
}	_MAIN_QUEST,* P_MAIN_QUEST;

class CQuestWnd : public CGameWnd
{
private:
	BOOL					m_boReadQuestList;
	INT						m_nTopLineCnt;
	INT						m_nLastLinenum;
	INT						m_nExpLineTop;
	INT						m_nExpandCnt;
	CHAR				   *m_pszExplannation;
	CWHWilImageData*		m_pxWndImage;
	CScrlBar				m_xQuestScrlBar;
	CScrlBar				m_xQuestScrlBarInSmall;
protected:
	CGameBtn				m_xQuestBtn[2];
	P_MAIN_QUEST			m_xpSelectedMainQuest;
public:
	CQuestWnd();
	~CQuestWnd();

	virtual VOID Init();
	virtual VOID Destroy();

	BOOL	SetMainQuest(CHAR *szMQuest, INT nCount);
	BOOL	SetSubQuest(CHAR *szSubQuest, INT nQuestIdx, INT nCount);
	VOID	SetSubDetail(CHAR* szDecodeMsg,INT nUnit,INT nSubIdx);

	BOOL	AddMainQuest(CHAR *szMQuest,INT nConut = 1);					//	Add Main Quest
	BOOL	AddSubQuest(CHAR *szSubQuest, INT nQuestIdx, INT nCount = 1);	//	Add Sub Quest
	VOID	ReSetQuestList(VOID);
	VOID	ExpandQuest(VOID);

	VOID	CreateQuestWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove);
	VOID	ShowQuestWnd();

	VOID	SetStatusBtnInit();
	VOID	SetGameWndActive(BOOL bActive);
	__inline	BOOL	IsInRect(RECT rcRect,POINT ptPoint)
	{
		rcRect.left		= rcRect.left	- ptPoint.x;
		rcRect.top		= rcRect.top	- ptPoint.y;
		rcRect.right	= rcRect.right	- ptPoint.x;
		rcRect.bottom	= rcRect.bottom	- ptPoint.y;
		if((rcRect.left <= 0) && (rcRect.top <= 0) && (rcRect.right >=0) && (rcRect.bottom >= 0) )
			return TRUE;
		return FALSE;
	}
	BOOL	SortMainQuest(VOID);
	BOOL	SortSubQuest(P_MAIN_QUEST pMQuest);
public:
//  메시지 함수.
	BOOL	OnLButtonDown(POINT ptMouse);
	BOOL	OnLButtonUp(POINT ptMouse);
	BOOL	OnDblClick(POINT ptMouse);
	VOID	OnMouseMove(POINT ptMouse);

	VOID	OnScrollDown();
	VOID	OnScrollUp();
public:
	CPDLList<_MAIN_QUEST>	m_xQuest;
private:
	BOOL	IsExistMainQuest(INT Idx);
	BOOL	IsExistSubQuest(INT MIdx,INT SIdx);
};


#endif // _CQUESTWND_H
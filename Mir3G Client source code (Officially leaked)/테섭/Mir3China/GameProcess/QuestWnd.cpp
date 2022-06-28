/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/


#include "StdAfx.h"
#define _MAX_LINE_COUNT				19
#define EXPAND_TICK					100
#define MAX_QUESTTEXT_WIDTH			160

#define RGB_DONE_NORMAL				RGB(100,25,25)
#define RGB_DONE_SELECT				RGB(50,25,25)
#define RGB_DO_NORMAL				RGB(150,25,25)
#define RGB_DO_SELECT				RGB(200,25,25)

#define MAX_WIDTH_MAIN_QUEST		200
#define MAX_WIDTH_SUB_QUEST			180

CQuestWnd::CQuestWnd()
{
	Init();
}

CQuestWnd::~CQuestWnd()
{
	Destroy();
}

VOID CQuestWnd::Init()
{
	CGameWnd::Init();
	m_boReadQuestList		= FALSE;
	m_nTopLineCnt			= 0;
	m_nLastLinenum			= 0;
	m_nExpandCnt			= 0;
	m_pszExplannation		= NULL;
	m_xpSelectedMainQuest	= NULL;
	m_xQuestBtn[0].Init();
	m_xQuestBtn[1].Init();
	m_xQuestScrlBar.Init();
	m_xQuestScrlBarInSmall.Init();
}

VOID CQuestWnd::Destroy()
{
	ReSetQuestList();
	CGameWnd::Destroy();
}

VOID CQuestWnd::CreateQuestWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove)
{
	m_pxWndImage = pxWndImage;
	CreateGameWnd(nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight);

#ifdef _NEWINTERFACE
	m_xQuestBtn[0].CreateGameBtn(pxWndImage, 1422, 1423, nStartX+292, nStartY+75, g_xMsg.GetMsg(2200), _BTN_TYPE_FOCUS, 1422, TRUE);
	m_xQuestBtn[1].CreateGameBtn(pxWndImage, 1425, 1426, nStartX+292, nStartY+107, "", _BTN_TYPE_FOCUS, 1425, TRUE);
	m_xQuestScrlBar.CreateScrlBar(pxWndImage, 1225, 5, 12, 182, 14);
	m_xQuestScrlBarInSmall.CreateScrlBar(pxWndImage, 1428, 30, 12, 10, 14);

	m_bOpa = 220;
#else //_NEWINTERFACE
	m_xQuestBtn[0].CreateGameBtn(pxWndImage, 723, 724, nStartX+290, nStartY+59);
	m_xQuestBtn[1].CreateGameBtn(pxWndImage, 721, 722, nStartX+290, nStartY+89);
#endif //_NEWINTERFACE 
}

VOID CQuestWnd::ShowQuestWnd()
{
	INT				nLineCnt	= 0;
	INT				nExplainLine= 0;
	INT				nLinenum	= 0;
	INT				nCnt;
	INT				nLoop;
	INT				nCount;
	INT				nLength = 0;
	BOOL			boFlag =TRUE;
	SIZE			XDrawTxt;
	RECT			rcBtn;
	POINT			ptTxtStart	=	{65,90};
	P_MAIN_QUEST	pMQuest;
	static	DWORD	dwTick		= 0;
	static	DWORD	dwTickCnt	= 0;
	DWORD			dwTemp		= 0;
	DWORD			CurrentTick;
	CHAR			szTemp[1024];

	pMQuest			= NULL;
	//		m_rcWnd
#ifdef _NEWINTERFACE
	RECT			ptExplan	=	{84,347,170,70};
#else //_NEWINTERFACE
	RECT			ptExplan	=	{80,310,170,70};
#endif //_NEWINTERFACE 	

	ShowGameWnd();

#ifdef _NEWINTERFACE
	m_xQuestScrlBar.ShowScrlBar(m_rcWnd.left+272, m_rcWnd.top+160, m_nTopLineCnt, m_nLastLinenum );
#else //_NEWINTERFACE
#endif //_NEWINTERFACE 	

	dwTemp = timeGetTime();
	CurrentTick = dwTemp - dwTick;
	dwTick = dwTemp;
	dwTickCnt += CurrentTick;

#ifdef _NEWINTERFACE
	m_xQuestBtn[0].ChangeRect(m_rcWnd.left+267, m_rcWnd.top+75);
	m_xQuestBtn[1].ChangeRect(m_rcWnd.left+267, m_rcWnd.top+107);

	for(nCnt = 1; nCnt >= 0; nCnt--)
		m_xQuestBtn[nCnt].ShowGameBtn();

	m_xQuest.MoveCurrentToTop();
	if(m_boReadQuestList)
	{
		while ( boFlag ) 
		{
			if ( nLineCnt < _MAX_LINE_COUNT) 
			{
				pMQuest = m_xQuest.GetCurrentData();
				// Put Main Quest
				nCount		= 0;
				nLinenum	= 0;
/*				if(!pMQuest->boExpand)
					g_xMainWnd.PutsHan(NULL, m_rcWnd.left + ptTxtStart.x - 10, m_rcWnd.top + ptTxtStart.y + nLineCnt*15 +15 * (nLinenum-m_nTopLineCnt), pMQuest->boSelected ? (pMQuest->boDone ? RGB_DONE_SELECT:RGB_DO_SELECT): (pMQuest->boDone ? RGB_DONE_NORMAL:RGB_DO_NORMAL), RGB(0,0,0), "+");
					else
					g_xMainWnd.PutsHan(NULL, m_rcWnd.left + ptTxtStart.x - 10, m_rcWnd.top + ptTxtStart.y + nLineCnt*15 +15 * (nLinenum-m_nTopLineCnt), pMQuest->boSelected ? (pMQuest->boDone ? RGB_DONE_SELECT:RGB_DO_SELECT): (pMQuest->boDone ? RGB_DONE_NORMAL:RGB_DO_NORMAL), RGB(0,0,0), "-");
*/
				XDrawTxt = g_xMainWnd.GetStrLength(NULL, NULL,pMQuest->pszTitle);
				if(XDrawTxt.cx > MAX_WIDTH_MAIN_QUEST)
				{
					nLength = strlen(pMQuest->pszTitle);
					for(nLoop = 0; nLoop < nLength; nLoop++)
					{
						if(pMQuest->pszTitle[nLoop]<0)
						{
							szTemp[nCount++]	= pMQuest->pszTitle[nLoop++];
							szTemp[nCount]		= pMQuest->pszTitle[nLoop];
							szTemp[nCount+1]	= NULL;
						}
						else
						{
							szTemp[nCount]		= pMQuest->pszTitle[nLoop];
							szTemp[nCount+1]	= NULL;
						}
						XDrawTxt = g_xMainWnd.GetStrLength(NULL, NULL, szTemp);
						if(XDrawTxt.cx >= MAX_QUESTTEXT_WIDTH)
						{
							if(((nLinenum+nLineCnt)>m_nTopLineCnt)&&((nLinenum+nLineCnt - m_nTopLineCnt)<_MAX_LINE_COUNT))
								g_xMainWnd.PutsHan(NULL, m_rcWnd.left + ptTxtStart.x, m_rcWnd.top + ptTxtStart.y + nLineCnt*15 +15 * (nLinenum-m_nTopLineCnt), pMQuest->boSelected ? (pMQuest->boDone ? RGB_DONE_SELECT:RGB_DO_SELECT): (pMQuest->boDone ? RGB_DONE_NORMAL:RGB_DO_NORMAL), RGB(0,0,0), szTemp);
							nCount = 0;
							nLinenum++;
						}
						else
							nCount++;
					}
					if(nCount!=0)
					{
							if(((nLinenum+nLineCnt)>m_nTopLineCnt)&&((nLinenum+nLineCnt - m_nTopLineCnt)<_MAX_LINE_COUNT))
								g_xMainWnd.PutsHan(NULL, m_rcWnd.left + ptTxtStart.x, m_rcWnd.top + ptTxtStart.y + nLineCnt*15 +15 * (nLinenum-m_nTopLineCnt), pMQuest->boSelected ? (pMQuest->boDone ? RGB_DONE_SELECT:RGB_DO_SELECT): (pMQuest->boDone ? RGB_DONE_NORMAL:RGB_DO_NORMAL), RGB(0,0,0), szTemp);
							nLinenum++;
					}
					if(((nLinenum+nLineCnt)>m_nTopLineCnt)&&((nLinenum+nLineCnt - m_nTopLineCnt)<_MAX_LINE_COUNT))
					{
						SetRect(&rcBtn,m_rcWnd.left + ptTxtStart.x,
							m_rcWnd.top + ptTxtStart.y + nLineCnt*15,
							m_rcWnd.left + ptTxtStart.x + MAX_QUESTTEXT_WIDTH,
							m_rcWnd.top + ptTxtStart.y + nLineCnt*15 + 15*nLinenum);
						pMQuest->rcBtn = rcBtn;
					}
					else
					{
						SetRect(&rcBtn,0,0,0,0);
						pMQuest->rcBtn = rcBtn;
					}
				}
				else
				{
					if(((nLinenum+nLineCnt)>=m_nTopLineCnt)&&((nLinenum+nLineCnt - m_nTopLineCnt)<_MAX_LINE_COUNT))
					{
						SetRect(&rcBtn,m_rcWnd.left + ptTxtStart.x,
							m_rcWnd.top + ptTxtStart.y + (nLineCnt-m_nTopLineCnt)*15,
							m_rcWnd.left + ptTxtStart.x + XDrawTxt.cx,
							m_rcWnd.top + ptTxtStart.y + (nLineCnt-m_nTopLineCnt)*15 + XDrawTxt.cy);
						g_xMainWnd.PutsHan(NULL,rcBtn,pMQuest->boSelected ? (pMQuest->boDone ? RGB_DONE_SELECT:RGB_DO_SELECT): (pMQuest->boDone ? RGB_DONE_NORMAL:RGB_DO_NORMAL) ,RGB(0,0,0),pMQuest->pszTitle);						
					}
					else
					{
						SetRect(&rcBtn,0,0,0,0);
					}
					pMQuest->rcBtn = rcBtn;
					nLinenum++;
				}
				nLineCnt+=nLinenum;
				
				if ( pMQuest->boExpand ) 
				{
					if ( pMQuest->boFilledSubQuest ) 
					{
						pMQuest->pSubQuest->MoveCurrentToTop();
						for ( nCnt = 0; (nCnt < pMQuest->nSubQuestCnt) && nCnt < m_nExpandCnt ; nCnt++ ) 
						{
							nCount		= 0;
							nLinenum	= 0;
							XDrawTxt = g_xMainWnd.GetStrLength(NULL, NULL,pMQuest->pSubQuest->GetCurrentData()->pszTitle);				
							if(((nLinenum+nLineCnt)>=m_nTopLineCnt)&&((nLinenum+nLineCnt - m_nTopLineCnt)<_MAX_LINE_COUNT))
								g_xMainWnd.PutsHan(NULL, m_rcWnd.left + ptTxtStart.x +5 , m_rcWnd.top + ptTxtStart.y + (nLinenum+nLineCnt - m_nTopLineCnt)*15, pMQuest->boSelected ? (pMQuest->boDone ? RGB_DONE_SELECT:RGB_DO_SELECT): (pMQuest->boDone ? RGB_DONE_NORMAL:RGB_DO_NORMAL), RGB(0,0,0), "-");
							if(XDrawTxt.cx>MAX_WIDTH_SUB_QUEST+10)
							{
								nLength = strlen(pMQuest->pSubQuest->GetCurrentData()->pszTitle);
								for(nLoop = 0; nLoop < nLength; nLoop++)
								{
									g_xMainWnd.PutsHan(NULL, m_rcWnd.left + ptTxtStart.x , m_rcWnd.top + ptTxtStart.y + nLineCnt*15,pMQuest->pSubQuest->GetCurrentData()->boSelected ? (pMQuest->boDone ? RGB_DONE_SELECT:RGB_DO_SELECT): (pMQuest->boDone ? RGB_DONE_NORMAL:RGB_DO_NORMAL), RGB(0,0,0), "-");
									if(pMQuest->pSubQuest->GetCurrentData()->pszTitle[nLoop]<0)
									{
										szTemp[nCount++]	= pMQuest->pSubQuest->GetCurrentData()->pszTitle[nLoop++];
										szTemp[nCount]		= pMQuest->pSubQuest->GetCurrentData()->pszTitle[nLoop];
										szTemp[nCount+1]	= NULL;
									}
									else
									{
										szTemp[nCount]		= pMQuest->pSubQuest->GetCurrentData()->pszTitle[nLoop];
										szTemp[nCount+1]	= NULL;
									}
									XDrawTxt = g_xMainWnd.GetStrLength(NULL, NULL, szTemp);
									if(XDrawTxt.cx >= MAX_QUESTTEXT_WIDTH+10)
									{
										if(((nLinenum+nLineCnt)>=m_nTopLineCnt)&&((nLinenum+nLineCnt - m_nTopLineCnt)<_MAX_LINE_COUNT))
											g_xMainWnd.PutsHan(NULL, m_rcWnd.left + ptTxtStart.x + 10, m_rcWnd.top + ptTxtStart.y + nLineCnt*15 +15 * (nLinenum- m_nTopLineCnt),pMQuest->pSubQuest->GetCurrentData()->boSelected ? (pMQuest->boDone ? RGB_DONE_SELECT:RGB_DO_SELECT): (pMQuest->boDone ? RGB_DONE_NORMAL:RGB_DO_NORMAL), RGB(0,0,0), szTemp);
										nCount = 0;
										nLinenum++;
									}
									else
										nCount++;
								}
								if(nCount!=0)
								{
									if(((nLinenum+nLineCnt)>=m_nTopLineCnt)&&((nLinenum+nLineCnt - m_nTopLineCnt)<_MAX_LINE_COUNT))
										g_xMainWnd.PutsHan(NULL, m_rcWnd.left + ptTxtStart.x +10, m_rcWnd.top + ptTxtStart.y + nLineCnt*15 +15 * (nLinenum-m_nTopLineCnt), pMQuest->pSubQuest->GetCurrentData()->boSelected ? (pMQuest->boDone ? RGB_DONE_SELECT:RGB_DO_SELECT): (pMQuest->boDone ? RGB_DONE_NORMAL:RGB_DO_NORMAL), RGB(0,0,0), szTemp);
									nLinenum++;

								}
								SetRect(&rcBtn,m_rcWnd.left + ptTxtStart.x+ 10,
									m_rcWnd.top + ptTxtStart.y + nLineCnt*15,
									m_rcWnd.left + ptTxtStart.x + 10 + MAX_QUESTTEXT_WIDTH,
									m_rcWnd.top + ptTxtStart.y + nLineCnt*15 + 15 * nLinenum);
								pMQuest->pSubQuest->GetCurrentData()->rcBtn = rcBtn;
								nLineCnt += nLinenum;
							}
							else
							{
								if(((nLinenum+nLineCnt)>=m_nTopLineCnt)&&((nLinenum+nLineCnt - m_nTopLineCnt)<_MAX_LINE_COUNT))
								{
									SetRect(&rcBtn,m_rcWnd.left + ptTxtStart.x + 10,
											m_rcWnd.top + ptTxtStart.y + (nLineCnt-m_nTopLineCnt)*15,
											m_rcWnd.left + ptTxtStart.x + XDrawTxt.cx + 10,
											m_rcWnd.top + ptTxtStart.y + (nLineCnt-m_nTopLineCnt)*15 + XDrawTxt.cy );
									g_xMainWnd.PutsHan(NULL,rcBtn, pMQuest->pSubQuest->GetCurrentData()->boSelected ? ( pMQuest->pSubQuest->GetCurrentData()->boDone ? RGB_DONE_SELECT :RGB_DO_SELECT) :( pMQuest->pSubQuest->GetCurrentData()->boDone ? RGB_DONE_NORMAL :RGB_DO_NORMAL),RGB(0,0,0),pMQuest->pSubQuest->GetCurrentData()->pszTitle);
									pMQuest->pSubQuest->GetCurrentData()->rcBtn = rcBtn;
								}
								nLineCnt++;
							}
							if(dwTickCnt >= EXPAND_TICK)
							{
								m_nExpandCnt++;
								m_nExpandCnt = m_nExpandCnt > pMQuest->nSubQuestCnt ? pMQuest->nSubQuestCnt : m_nExpandCnt;
								dwTickCnt = 0;
							}
							pMQuest->pSubQuest->MoveNextNode();
						}
					}
				}
			}
			else
			{
				SetRect(&rcBtn,0,0,0,0);
				pMQuest->rcBtn = rcBtn;
			}
			if(m_xQuest.IsCurrentTail())
				boFlag = FALSE;
			m_xQuest.MoveNextNode();
		}
		m_nLastLinenum = nLineCnt;

		if(m_pszExplannation!=NULL && *m_pszExplannation!=NULL)	// 임시 설명찍기
		{
			if ( m_pxWndImage->NewSetIndex(1427) )
			{
				g_xMainWnd.DrawWithImageForComp(m_rcWnd.left + ptExplan.left - 15, m_rcWnd.top + ptExplan.top -16,
												(m_pxWndImage->m_lpstNewCurrWilImageInfo->shWidth), (m_pxWndImage->m_lpstNewCurrWilImageInfo->shHeight),
												(WORD*)m_pxWndImage->m_pbCurrImage);
			}
			nExplainLine	= 0;
			nCount		= 0;
			XDrawTxt = g_xMainWnd.GetStrLength(NULL, NULL, m_pszExplannation);
			if(XDrawTxt.cx > MAX_QUESTTEXT_WIDTH)
			{
				nLength = strlen(m_pszExplannation);
				for(nCnt = 0; nCnt < nLength; nCnt++)
				{
					if(m_pszExplannation[nCnt]<0)
					{
						szTemp[nCount++]	= m_pszExplannation[nCnt++];
						szTemp[nCount]		= m_pszExplannation[nCnt];
						szTemp[nCount+1]	= NULL;
					}
					else
					{
						szTemp[nCount]		= m_pszExplannation[nCnt];
						szTemp[nCount+1]	= NULL;
					}
					XDrawTxt = g_xMainWnd.GetStrLength(NULL, NULL, szTemp);
					if(XDrawTxt.cx >= MAX_QUESTTEXT_WIDTH)
					{
						if(m_nExpLineTop<=nExplainLine && nExplainLine<m_nExpLineTop+3)
							g_xMainWnd.PutsHan(NULL, m_rcWnd.left + ptExplan.left, m_rcWnd.top + ptExplan.top +15 * (nExplainLine-m_nExpLineTop), RGB(0,0,125), RGB(0,0,0), szTemp);
						nCount = 0;
						nExplainLine++;

					}
					else
						nCount++;
				}
				if(nCount!=0)
				{
					if(m_nExpLineTop<=nExplainLine && nExplainLine<m_nExpLineTop+3)
						g_xMainWnd.PutsHan(NULL, m_rcWnd.left + ptExplan.left, m_rcWnd.top + ptExplan.top +15 * (nExplainLine-m_nExpLineTop), RGB(0,0,125), RGB(0,0,0), szTemp);
				}

				m_xQuestScrlBarInSmall.ShowScrlBar(m_rcWnd.left + ptExplan.left + 167, m_rcWnd.top + ptExplan.top - 2, m_nExpLineTop, m_nExpandCnt );
			}
			else
			{
				g_xMainWnd.PutsHan(NULL, m_rcWnd.left + ptExplan.left, m_rcWnd.top + ptExplan.top +15 * nExplainLine, RGB(0,0,125), RGB(0,0,0), m_pszExplannation);
			}
		}
	}
#else //_NEWINTERFACE
	m_xQuestBtn[0].ChangeRect(m_rcWnd.left+290, m_rcWnd.top+59);
	m_xQuestBtn[1].ChangeRect(m_rcWnd.left+290, m_rcWnd.top+89);

	for(nCnt = 1; nCnt >= 0; nCnt--)
		m_xQuestBtn[nCnt].ShowGameBtn();

	m_xQuest.MoveCurrentToTop();
	if(m_boReadQuestList)
	{
		while ( boFlag ) 
		{
			if ( nLineCnt < _MAX_LINE_COUNT) 
			{
				pMQuest = m_xQuest.GetCurrentData();
				// Put Main Quest
				nCount		= 0;
				nLinenum	= 0;
/*				if(!pMQuest->boExpand)
					g_xMainWnd.PutsHan(NULL, m_rcWnd.left + ptTxtStart.x - 10, m_rcWnd.top + ptTxtStart.y + nLineCnt*15 +15 * (nLinenum-m_nTopLineCnt), pMQuest->boSelected ? (pMQuest->boDone ? RGB_DONE_SELECT:RGB_DO_SELECT): (pMQuest->boDone ? RGB_DONE_NORMAL:RGB_DO_NORMAL), RGB(0,0,0), "+");
					else
					g_xMainWnd.PutsHan(NULL, m_rcWnd.left + ptTxtStart.x - 10, m_rcWnd.top + ptTxtStart.y + nLineCnt*15 +15 * (nLinenum-m_nTopLineCnt), pMQuest->boSelected ? (pMQuest->boDone ? RGB_DONE_SELECT:RGB_DO_SELECT): (pMQuest->boDone ? RGB_DONE_NORMAL:RGB_DO_NORMAL), RGB(0,0,0), "-");
*/
				XDrawTxt = g_xMainWnd.GetStrLength(NULL, NULL,pMQuest->pszTitle);
				if(XDrawTxt.cx > MAX_WIDTH_MAIN_QUEST)
				{
					nLength = strlen(pMQuest->pszTitle);
					for(nLoop = 0; nLoop < nLength; nLoop++)
					{
						if(pMQuest->pszTitle[nLoop]<0)
						{
							szTemp[nCount++]	= pMQuest->pszTitle[nLoop++];
							szTemp[nCount]		= pMQuest->pszTitle[nLoop];
							szTemp[nCount+1]	= NULL;
						}
						else
						{
							szTemp[nCount]		= pMQuest->pszTitle[nLoop];
							szTemp[nCount+1]	= NULL;
						}
						XDrawTxt = g_xMainWnd.GetStrLength(NULL, NULL, szTemp);
						if(XDrawTxt.cx >= MAX_QUESTTEXT_WIDTH)
						{
							if(((nLinenum+nLineCnt)>m_nTopLineCnt)&&((nLinenum+nLineCnt - m_nTopLineCnt)<_MAX_LINE_COUNT))
								g_xMainWnd.PutsHan(NULL, m_rcWnd.left + ptTxtStart.x, m_rcWnd.top + ptTxtStart.y + nLineCnt*15 +15 * (nLinenum-m_nTopLineCnt), pMQuest->boSelected ? (pMQuest->boDone ? RGB_DONE_SELECT:RGB_DO_SELECT): (pMQuest->boDone ? RGB_DONE_NORMAL:RGB_DO_NORMAL), RGB(0,0,0), szTemp);
							nCount = 0;
							nLinenum++;
						}
						else
							nCount++;
					}
					if(nCount!=0)
					{
							if(((nLinenum+nLineCnt)>m_nTopLineCnt)&&((nLinenum+nLineCnt - m_nTopLineCnt)<_MAX_LINE_COUNT))
								g_xMainWnd.PutsHan(NULL, m_rcWnd.left + ptTxtStart.x, m_rcWnd.top + ptTxtStart.y + nLineCnt*15 +15 * (nLinenum-m_nTopLineCnt), pMQuest->boSelected ? (pMQuest->boDone ? RGB_DONE_SELECT:RGB_DO_SELECT): (pMQuest->boDone ? RGB_DONE_NORMAL:RGB_DO_NORMAL), RGB(0,0,0), szTemp);
							nLinenum++;
					}
					if(((nLinenum+nLineCnt)>m_nTopLineCnt)&&((nLinenum+nLineCnt - m_nTopLineCnt)<_MAX_LINE_COUNT))
					{
						SetRect(&rcBtn,m_rcWnd.left + ptTxtStart.x,
							m_rcWnd.top + ptTxtStart.y + nLineCnt*15,
							m_rcWnd.left + ptTxtStart.x + MAX_QUESTTEXT_WIDTH,
							m_rcWnd.top + ptTxtStart.y + nLineCnt*15 + 15*nLinenum);
						pMQuest->rcBtn = rcBtn;
					}
					else
					{
						SetRect(&rcBtn,0,0,0,0);
						pMQuest->rcBtn = rcBtn;
					}
				}
				else
				{
					if(((nLinenum+nLineCnt)>=m_nTopLineCnt)&&((nLinenum+nLineCnt - m_nTopLineCnt)<_MAX_LINE_COUNT))
					{
						SetRect(&rcBtn,m_rcWnd.left + ptTxtStart.x,
							m_rcWnd.top + ptTxtStart.y + (nLineCnt-m_nTopLineCnt)*15,
							m_rcWnd.left + ptTxtStart.x + XDrawTxt.cx,
							m_rcWnd.top + ptTxtStart.y + (nLineCnt-m_nTopLineCnt)*15 + XDrawTxt.cy);
						g_xMainWnd.PutsHan(NULL,rcBtn,pMQuest->boSelected ? (pMQuest->boDone ? RGB_DONE_SELECT:RGB_DO_SELECT): (pMQuest->boDone ? RGB_DONE_NORMAL:RGB_DO_NORMAL) ,RGB(0,0,0),pMQuest->pszTitle);						
					}
					else
					{
						SetRect(&rcBtn,0,0,0,0);
					}
					pMQuest->rcBtn = rcBtn;
					nLinenum++;
				}
				nLineCnt+=nLinenum;
				
				if ( pMQuest->boExpand ) 
				{
					if ( pMQuest->boFilledSubQuest ) 
					{
						pMQuest->pSubQuest->MoveCurrentToTop();
						for ( nCnt = 0; (nCnt < pMQuest->nSubQuestCnt) && nCnt < m_nExpandCnt ; nCnt++ ) 
						{
							nCount		= 0;
							nLinenum	= 0;
							XDrawTxt = g_xMainWnd.GetStrLength(NULL, NULL,pMQuest->pSubQuest->GetCurrentData()->pszTitle);				
							if(((nLinenum+nLineCnt)>=m_nTopLineCnt)&&((nLinenum+nLineCnt - m_nTopLineCnt)<_MAX_LINE_COUNT))
								g_xMainWnd.PutsHan(NULL, m_rcWnd.left + ptTxtStart.x +5 , m_rcWnd.top + ptTxtStart.y + (nLinenum+nLineCnt - m_nTopLineCnt)*15, pMQuest->boSelected ? (pMQuest->boDone ? RGB_DONE_SELECT:RGB_DO_SELECT): (pMQuest->boDone ? RGB_DONE_NORMAL:RGB_DO_NORMAL), RGB(0,0,0), "-");
							if(XDrawTxt.cx>MAX_WIDTH_SUB_QUEST+10)
							{
								nLength = strlen(pMQuest->pSubQuest->GetCurrentData()->pszTitle);
								for(nLoop = 0; nLoop < nLength; nLoop++)
								{
									g_xMainWnd.PutsHan(NULL, m_rcWnd.left + ptTxtStart.x , m_rcWnd.top + ptTxtStart.y + nLineCnt*15,pMQuest->pSubQuest->GetCurrentData()->boSelected ? (pMQuest->boDone ? RGB_DONE_SELECT:RGB_DO_SELECT): (pMQuest->boDone ? RGB_DONE_NORMAL:RGB_DO_NORMAL), RGB(0,0,0), "-");
									if(pMQuest->pSubQuest->GetCurrentData()->pszTitle[nLoop]<0)
									{
										szTemp[nCount++]	= pMQuest->pSubQuest->GetCurrentData()->pszTitle[nLoop++];
										szTemp[nCount]		= pMQuest->pSubQuest->GetCurrentData()->pszTitle[nLoop];
										szTemp[nCount+1]	= NULL;
									}
									else
									{
										szTemp[nCount]		= pMQuest->pSubQuest->GetCurrentData()->pszTitle[nLoop];
										szTemp[nCount+1]	= NULL;
									}
									XDrawTxt = g_xMainWnd.GetStrLength(NULL, NULL, szTemp);
									if(XDrawTxt.cx >= MAX_QUESTTEXT_WIDTH+10)
									{
										if(((nLinenum+nLineCnt)>=m_nTopLineCnt)&&((nLinenum+nLineCnt - m_nTopLineCnt)<_MAX_LINE_COUNT))
											g_xMainWnd.PutsHan(NULL, m_rcWnd.left + ptTxtStart.x + 10, m_rcWnd.top + ptTxtStart.y + nLineCnt*15 +15 * (nLinenum- m_nTopLineCnt),pMQuest->pSubQuest->GetCurrentData()->boSelected ? (pMQuest->boDone ? RGB_DONE_SELECT:RGB_DO_SELECT): (pMQuest->boDone ? RGB_DONE_NORMAL:RGB_DO_NORMAL), RGB(0,0,0), szTemp);
										nCount = 0;
										nLinenum++;
									}
									else
										nCount++;
								}
								if(nCount!=0)
								{
									if(((nLinenum+nLineCnt)>=m_nTopLineCnt)&&((nLinenum+nLineCnt - m_nTopLineCnt)<_MAX_LINE_COUNT))
										g_xMainWnd.PutsHan(NULL, m_rcWnd.left + ptTxtStart.x +10, m_rcWnd.top + ptTxtStart.y + nLineCnt*15 +15 * (nLinenum-m_nTopLineCnt), pMQuest->pSubQuest->GetCurrentData()->boSelected ? (pMQuest->boDone ? RGB_DONE_SELECT:RGB_DO_SELECT): (pMQuest->boDone ? RGB_DONE_NORMAL:RGB_DO_NORMAL), RGB(0,0,0), szTemp);
									nLinenum++;

								}
								SetRect(&rcBtn,m_rcWnd.left + ptTxtStart.x+ 10,
									m_rcWnd.top + ptTxtStart.y + nLineCnt*15,
									m_rcWnd.left + ptTxtStart.x + 10 + MAX_QUESTTEXT_WIDTH,
									m_rcWnd.top + ptTxtStart.y + nLineCnt*15 + 15 * nLinenum);
								pMQuest->pSubQuest->GetCurrentData()->rcBtn = rcBtn;
								nLineCnt += nLinenum;
							}
							else
							{
								if(((nLinenum+nLineCnt)>=m_nTopLineCnt)&&((nLinenum+nLineCnt - m_nTopLineCnt)<_MAX_LINE_COUNT))
								{
									SetRect(&rcBtn,m_rcWnd.left + ptTxtStart.x + 10,
											m_rcWnd.top + ptTxtStart.y + (nLineCnt-m_nTopLineCnt)*15,
											m_rcWnd.left + ptTxtStart.x + XDrawTxt.cx + 10,
											m_rcWnd.top + ptTxtStart.y + (nLineCnt-m_nTopLineCnt)*15 + XDrawTxt.cy );
									g_xMainWnd.PutsHan(NULL,rcBtn, pMQuest->pSubQuest->GetCurrentData()->boSelected ? ( pMQuest->pSubQuest->GetCurrentData()->boDone ? RGB_DONE_SELECT :RGB_DO_SELECT) :( pMQuest->pSubQuest->GetCurrentData()->boDone ? RGB_DONE_NORMAL :RGB_DO_NORMAL),RGB(0,0,0),pMQuest->pSubQuest->GetCurrentData()->pszTitle);
									pMQuest->pSubQuest->GetCurrentData()->rcBtn = rcBtn;
								}
								nLineCnt++;
							}
							if(dwTickCnt >= EXPAND_TICK)
							{
								m_nExpandCnt++;
								m_nExpandCnt = m_nExpandCnt > pMQuest->nSubQuestCnt ? pMQuest->nSubQuestCnt : m_nExpandCnt;
								dwTickCnt = 0;
							}
							pMQuest->pSubQuest->MoveNextNode();
						}
					}
				}
			}
			else
			{
				SetRect(&rcBtn,0,0,0,0);
				pMQuest->rcBtn = rcBtn;
			}
			if(m_xQuest.IsCurrentTail())
				boFlag = FALSE;
			m_xQuest.MoveNextNode();
		}
		m_nLastLinenum = nLineCnt;

		if(m_pszExplannation!=NULL && *m_pszExplannation!=NULL)	// 임시 설명찍기
		{
			if ( m_pxWndImage->NewSetIndex(705) )
			{
				g_xMainWnd.DrawWithImageForComp(m_rcWnd.left + ptExplan.left - 15, m_rcWnd.top + ptExplan.top -16,
												(m_pxWndImage->m_lpstNewCurrWilImageInfo->shWidth), (m_pxWndImage->m_lpstNewCurrWilImageInfo->shHeight),
												(WORD*)m_pxWndImage->m_pbCurrImage);
			}
			nExplainLine	= 0;
			nCount		= 0;
			XDrawTxt = g_xMainWnd.GetStrLength(NULL, NULL, m_pszExplannation);
			if(XDrawTxt.cx > MAX_QUESTTEXT_WIDTH)
			{
				nLength = strlen(m_pszExplannation);
				for(nCnt = 0; nCnt < nLength; nCnt++)
				{
					if(m_pszExplannation[nCnt]<0)
					{
						szTemp[nCount++]	= m_pszExplannation[nCnt++];
						szTemp[nCount]		= m_pszExplannation[nCnt];
						szTemp[nCount+1]	= NULL;
					}
					else
					{
						szTemp[nCount]		= m_pszExplannation[nCnt];
						szTemp[nCount+1]	= NULL;
					}
					XDrawTxt = g_xMainWnd.GetStrLength(NULL, NULL, szTemp);
					if(XDrawTxt.cx >= MAX_QUESTTEXT_WIDTH)
					{
						if(m_nExpLineTop<=nExplainLine && nExplainLine<m_nExpLineTop+3)
							g_xMainWnd.PutsHan(NULL, m_rcWnd.left + ptExplan.left, m_rcWnd.top + ptExplan.top +15 * (nExplainLine-m_nExpLineTop), RGB(0,0,125), RGB(0,0,0), szTemp);
						nCount = 0;
						nExplainLine++;

					}
					else
						nCount++;
				}
				if(nCount!=0)
					if(m_nExpLineTop<=nExplainLine && nExplainLine<m_nExpLineTop+3)
						g_xMainWnd.PutsHan(NULL, m_rcWnd.left + ptExplan.left, m_rcWnd.top + ptExplan.top +15 * (nExplainLine-m_nExpLineTop), RGB(0,0,125), RGB(0,0,0), szTemp);

			}
			else
			{
				g_xMainWnd.PutsHan(NULL, m_rcWnd.left + ptExplan.left, m_rcWnd.top + ptExplan.top +15 * nExplainLine, RGB(0,0,125), RGB(0,0,0), m_pszExplannation);
			}
		}
	}
#endif //_NEWINTERFACE 
}

BOOL CQuestWnd::OnLButtonUp(POINT ptMouse)
{
	INT nCnt;
	INT nLoop;
	P_MAIN_QUEST	pMQuest	= NULL;
	P_SUB_QUEST		pSQuest = NULL;
	m_pszExplannation = NULL;

#ifdef _NEWINTERFACE
	if ( m_xQuestScrlBar.OnLButtonUp(ptMouse) )
	{
		return FALSE;
	}

	if ( m_xQuestScrlBarInSmall.OnLButtonDown(ptMouse) )
	{
		return FALSE;
	}
#else //_NEWINTERFACE
#endif //_NEWINTERFACE 

	if ( m_xQuestBtn[1].OnLButtonUp(ptMouse) )
		return TRUE;		// exit Btn

	if ( m_boReadQuestList ) {
		m_xQuest.MoveCurrentToTop();
		for ( nCnt = 0 ; nCnt < m_xQuest.GetCounter() ; nCnt++ ){
			m_xQuest.GetCurrentData()->boSelected = FALSE;				// 선택된거 풀기
			if(IsInRect(m_xQuest.GetCurrentData()->rcBtn, ptMouse)){
				pMQuest = m_xQuest.GetCurrentData();			
				m_xQuest.GetCurrentData()->boSelected = TRUE;
			}
			if(m_xQuest.GetCurrentData()->boExpand && m_xQuest.GetCurrentData()->boFilledSubQuest){
				m_xQuest.GetCurrentData()->pSubQuest->MoveCurrentToTop();
				for( nLoop = 0; nLoop < m_xQuest.GetCurrentData()->nSubQuestCnt ; nLoop++ ){
					if(m_xQuest.GetCurrentData()->pSubQuest!=NULL){
						pSQuest = m_xQuest.GetCurrentData()->pSubQuest->GetCurrentData();
						if(IsInRect(pSQuest->rcBtn, ptMouse)){		// 나중에 클릭했을때 특별한 Event가 있으면 추가
							m_pszExplannation = pSQuest->szExplanation;
							if(*m_pszExplannation == NULL){
								g_xClientSocket.SendQueryDetail(m_xQuest.GetCurrentData()->nIndex,pSQuest->nIndex);
							}
								
						}

						m_xQuest.GetCurrentData()->pSubQuest->MoveNextNode();
					}						
				}				
			}
			m_xQuest.MoveNextNode();
		}
	}

	if(pMQuest!=NULL){
		m_pszExplannation = pMQuest->szExplanation;
		m_xpSelectedMainQuest = pMQuest;
	}

	if(m_xQuestBtn[0].OnLButtonUp(ptMouse))
		ExpandQuest();
	else
		if(pMQuest==NULL)
			m_xpSelectedMainQuest = NULL;

	return FALSE;
}

BOOL CQuestWnd::OnLButtonDown(POINT ptMouse)
{
	INT nCnt;
	INT nLoop;
	P_MAIN_QUEST	pMQuest;	
	P_SUB_QUEST		pSQuest;

	pMQuest = NULL;
	pSQuest= NULL;

#ifdef _NEWINTERFACE
	if ( m_xQuestScrlBar.OnLButtonDown(ptMouse) )
	{
		FLOAT	fScrlRate;

		fScrlRate	= m_xQuestScrlBar.GetScrlRate();
		m_nTopLineCnt = (INT)((m_nLastLinenum - 1)*fScrlRate);
		return TRUE;
	}
#else //_NEWINTERFACE
#endif //_NEWINTERFACE 

	m_xQuestBtn[0].OnLButtonDown(ptMouse);
	if ( m_xQuestBtn[1].OnLButtonDown(ptMouse) )		return TRUE;	// exit Btn
	if ( m_boReadQuestList ) 
	{
		m_xQuest.MoveCurrentToTop();
		for ( nCnt = 0 ; nCnt < m_xQuest.GetCounter() ; nCnt++ )
		{
			if(IsInRect(m_xQuest.GetCurrentData()->rcBtn, ptMouse))
				m_xQuest.GetCurrentData()->boSelected = TRUE;
			if(m_xQuest.GetCurrentData()->boExpand && m_xQuest.GetCurrentData()->boFilledSubQuest)
			{
				m_xQuest.GetCurrentData()->pSubQuest->MoveCurrentToTop();
				for( nLoop = 0; nLoop < m_xQuest.GetCurrentData()->nSubQuestCnt ; nLoop++ )
				{
					pSQuest = m_xQuest.GetCurrentData()->pSubQuest->GetCurrentData();
					pSQuest->boSelected = FALSE;
					if(IsInRect(pSQuest->rcBtn, ptMouse))
						pSQuest->boSelected = TRUE;
					m_xQuest.GetCurrentData()->pSubQuest->MoveNextNode();
				}
			}
			m_xQuest.MoveNextNode();
		}
	}
	return FALSE;
}

VOID CQuestWnd::OnMouseMove(POINT ptMouse)
{
#ifdef _NEWINTERFACE
	if ( m_xQuestScrlBar.OnMouseMove(ptMouse) )
	{
		FLOAT	fScrlRate;
		fScrlRate	= m_xQuestScrlBar.GetScrlRate();
		m_nTopLineCnt = (INT)((m_nLastLinenum - 1)*fScrlRate);
		return;
	}
#else //_NEWINTERFACE
#endif //_NEWINTERFACE 

	m_xQuestBtn[0].ChangeRect(m_rcWnd.left+290, m_rcWnd.top+59);
	m_xQuestBtn[0].OnMouseMove(ptMouse);

	m_xQuestBtn[1].ChangeRect(m_rcWnd.left+290, m_rcWnd.top+89);
	m_xQuestBtn[1].OnMouseMove(ptMouse);
}

BOOL CQuestWnd::OnDblClick(POINT ptMouse)
{
	INT nCnt;
	P_MAIN_QUEST	pMQuest;
	P_SUB_QUEST		pSQuest;

	pMQuest	= NULL;
	pSQuest = NULL;

	if ( m_boReadQuestList ) {
		m_xQuest.MoveCurrentToTop();
		for ( nCnt = 0 ; nCnt < m_xQuest.GetCounter() ; nCnt++ ){
			if(IsInRect(m_xQuest.GetCurrentData()->rcBtn, ptMouse))
				pMQuest = m_xQuest.GetCurrentData();			
			m_xQuest.MoveNextNode();
		}
	}

	if(pMQuest!=NULL){
		m_xpSelectedMainQuest = pMQuest;
		ExpandQuest();
	}
	return TRUE;
}

VOID CQuestWnd::ExpandQuest(VOID)
{
	INT nCnt;
	if(m_xpSelectedMainQuest!=NULL){
		m_xQuest.MoveCurrentToTop();
		for( nCnt = 0 ; nCnt < m_xQuest.GetCounter() ; nCnt++){
			m_xQuest.GetCurrentData()->boExpand = FALSE;
			m_xQuest.MoveNextNode();
		}
		m_xpSelectedMainQuest->boExpand = TRUE;
		m_nExpandCnt = 1;
		if(!m_xpSelectedMainQuest->boFilledSubQuest){
			//읽어 올것을 서버로부터 요청
			g_xClientSocket.SendQuerySubQuest(m_xpSelectedMainQuest->nIndex);
		}
	}
}

VOID CQuestWnd::SetStatusBtnInit()
{
	m_xQuestBtn[0].SetBtnState(_BTN_STATE_NORMAL);
	m_xQuestBtn[1].SetBtnState(_BTN_STATE_NORMAL);
}



VOID CQuestWnd::OnScrollDown()
{
	POINT	ptMouse;
	RECT	rcExplan;
	RECT	rcTemp;
	memcpy(&rcTemp,&m_rcWnd,sizeof(RECT));
	rcTemp.bottom = m_rcWnd.top + 310;
	SetRect(&rcExplan,m_rcWnd.left+80, m_rcWnd.top+310,m_rcWnd.left+250,m_rcWnd.top+380);

	if(m_boReadQuestList)
	{
		GetCursorPos(&ptMouse);
		ScreenToClient(g_xMainWnd.GetSafehWnd(),&ptMouse);

		if(m_pszExplannation!=NULL)
		{
			if(IsInRect(rcExplan,ptMouse))
			{
				m_nExpLineTop--;
				m_nExpLineTop = m_nExpLineTop < 0 ? 0 : m_nExpLineTop;
			}
		}

		if(IsInRect(rcTemp,ptMouse))
		{
			m_nTopLineCnt--;
			m_nTopLineCnt = m_nTopLineCnt <= 0 ? 0 : m_nTopLineCnt;
		}
	}
}

VOID CQuestWnd::OnScrollUp()
{
	POINT	ptMouse;
	RECT	rcExplan;
	RECT	rcTemp;
	memcpy(&rcTemp,&m_rcWnd,sizeof(RECT));
	rcTemp.bottom = m_rcWnd.top + 310;
	SetRect(&rcExplan,m_rcWnd.left+80, m_rcWnd.top+310,m_rcWnd.left+250,m_rcWnd.top+380);

	if(m_boReadQuestList)
	{
		GetCursorPos(&ptMouse);
		ScreenToClient(g_xMainWnd.GetSafehWnd(),&ptMouse);

		if(m_pszExplannation!=NULL)
		{
			if(IsInRect(rcExplan,ptMouse))
			{
				m_nExpLineTop++;
				m_nExpLineTop = m_nExpLineTop >= 4 ? 3 : m_nExpLineTop;
			}
		}

		if(IsInRect(rcTemp,ptMouse))
		{
			m_nTopLineCnt++;
			m_nTopLineCnt = m_nTopLineCnt >= m_nLastLinenum ? m_nLastLinenum-1 : m_nTopLineCnt;
		}
	}
}

VOID CQuestWnd::SetGameWndActive(BOOL bActive)
{
	m_bActive = bActive;

	if(bActive){
		if(!m_boReadQuestList)
			g_xClientSocket.SendQueryQuest();		// 처음 Main QuestList를 읽어온다.	
	}
}


BOOL CQuestWnd::SetMainQuest(CHAR *pszMQuest,INT nCount)
{
	INT				nIdx;
	BOOL			boDone;
	INT				nSubCnt;
	INT				nCnt;
	CHAR			*pszIdx = pszMQuest;
	CHAR			*pszTitle;
	CHAR			*pszSubCount;
	CHAR			*pszDone;
	CHAR			*pszExplanation;
	P_MAIN_QUEST	pMainQuest	= NULL;

	ReSetQuestList();

	if((strlen(pszMQuest)<=0) || (nCount<=0))
		return FALSE;

	for( nCnt = 0; nCnt < nCount ; nCnt++){

		pMainQuest	= new _MAIN_QUEST;
		pszTitle	= strchr(pszIdx,'/');
		*pszTitle	= NULL;
		nIdx		= atoi(pszIdx);
		pszTitle++;
		pszSubCount	= strchr(pszTitle,'/');
		*pszSubCount= NULL;
		pszSubCount++;
		pszDone		= strchr(pszSubCount,'/');
		*pszDone	= NULL;
		nSubCnt		= atoi(pszSubCount);
		pszDone++;
		pszExplanation		= strchr(pszDone,'/');
		if(pszExplanation!=NULL){	// 설명이 없을 경우 대비
			*pszExplanation		= NULL;
			pszExplanation++;
			if((*pszExplanation)!='/'){
				pszIdx		= strchr(pszExplanation,'/');
				if(pszIdx!=NULL){
					*pszIdx				= NULL;
					pszIdx++;		
				}
			}
			else{
				*pszExplanation = NULL;
				pszExplanation++;
				pszIdx = pszExplanation;
			}
		}
		boDone		= atoi(pszDone);

		ZeroMemory(pMainQuest,sizeof(_MAIN_QUEST));

		pMainQuest->nIndex			= nIdx;
		pMainQuest->boDone			= boDone;
		pMainQuest->nSubQuestCnt	= nSubCnt;
		pMainQuest->boExpand		= FALSE;
		pMainQuest->boFilledSubQuest= FALSE;
		if(pMainQuest->pSubQuest != NULL) pMainQuest->pSubQuest->ClearAllNodes();
		strcpy(pMainQuest->pszTitle, pszTitle);
		if(pszExplanation!=NULL){
			strcpy(pMainQuest->szExplanation,pszExplanation);
			pMainQuest->boFilledExplanation = TRUE;
		}
		else{
			ZeroMemory(pMainQuest->szExplanation,1024);
			pMainQuest->boFilledExplanation = FALSE;
		}
		m_xQuest.AddNode(pMainQuest);
		pMainQuest = NULL;
	}
	m_nLastLinenum = m_xQuest.GetCounter();
	m_boReadQuestList = TRUE;
	SortMainQuest();
	return TRUE;
}


BOOL CQuestWnd::SetSubQuest(CHAR* pszSubQuest,INT nQuestIdx, INT nCount)
{
	INT				nIdx;
	BOOL			boDone;
	BOOL			boSwitch;
	INT				nCnt;
	CHAR			*pszIdx = pszSubQuest;
	CHAR			*pszTitle;
	CHAR			*pszExplanation;
	P_SUB_QUEST		pSubQuest	= NULL;
	P_MAIN_QUEST	pMainQuest	= NULL;

	if(!m_boReadQuestList){
		g_xClientSocket.SendQueryQuest();
		return FALSE;
	}

	if((strlen(pszSubQuest)<=0) || (nCount<=0))
		return FALSE;

	boSwitch	= TRUE;
	nCnt		= 0;

	m_xQuest.MoveCurrentToTop();
	while(boSwitch || nCnt < m_xQuest.GetCounter()){
		if(m_xQuest.GetCurrentData()->nIndex == nQuestIdx){
			pMainQuest = m_xQuest.GetCurrentData();
			boSwitch = FALSE;
		}
		nCnt++;
		m_xQuest.MoveNextNode();
	}

	if(pMainQuest->pSubQuest==NULL)
		pMainQuest->pSubQuest = new CPDLList<_SUB_QUEST>;
	else
		pMainQuest->pSubQuest->ClearAllNodes();

	for( nCnt = 0; nCnt < nCount ; nCnt++){
		pszExplanation = NULL;
		pSubQuest = new _SUB_QUEST;
		ZeroMemory(pSubQuest,sizeof(_SUB_QUEST));
		pszTitle	= strchr(pszIdx,'/');
		*pszTitle	= NULL;
		nIdx		= atoi(pszIdx);
		pszTitle++;
		pszIdx		= strchr(pszTitle,'/');
		*pszIdx		= NULL;
		pszIdx++;
		boDone		= FALSE;

		pSubQuest->nIndex	= nIdx;
		if(pMainQuest->boDone)
			pSubQuest->boDone	= pMainQuest->boDone;
		else
			pSubQuest->boDone	= boDone;
		pMainQuest->boFilledSubQuest		= TRUE;
		strcpy(pSubQuest->pszTitle, pszTitle);
		if(pszExplanation!=NULL){
			strcpy(pSubQuest->szExplanation, pszExplanation);
			pSubQuest->boFilledExplanation = TRUE;
		}
		else{
			ZeroMemory(pSubQuest->szExplanation,1024);
			pSubQuest->boFilledExplanation = FALSE;
		}
		pMainQuest->pSubQuest->AddNode(pSubQuest);
		pSubQuest = NULL;

	}
	pMainQuest->nSubQuestCnt =nCount;
	return TRUE;
}

VOID CQuestWnd::SetSubDetail(CHAR* szDecodeMsg,INT nUint,INT nSubIdx)
{
	INT	nCnt;
	_SUB_QUEST*	pSQuest=NULL;

	m_xQuest.MoveCurrentToTop();
	while(1)
	{
		if(m_xQuest.GetCurrentData()->nIndex == nUint){
			if(m_xQuest.GetCurrentData()->pSubQuest!=NULL){
				m_xQuest.GetCurrentData()->pSubQuest->MoveCurrentToTop();
				for(nCnt = 0; nCnt < m_xQuest.GetCurrentData()->pSubQuest->GetCounter(); nCnt++){
					if(m_xQuest.GetCurrentData()->pSubQuest->GetCurrentData()->nIndex==nSubIdx)
						pSQuest = m_xQuest.GetCurrentData()->pSubQuest->GetCurrentData();
					m_xQuest.GetCurrentData()->pSubQuest->MoveNextNode();
				}
				break;
			}
			else
				break;
		}
		if(m_xQuest.IsCurrentTail()) break;
		m_xQuest.MoveNextNode();
	}

	if(pSQuest!=NULL)
	{
		pSQuest->boFilledExplanation = TRUE;
		strcpy(pSQuest->szExplanation ,szDecodeMsg);
	}
}


VOID CQuestWnd::ReSetQuestList(VOID)
{
	INT nCnt;
	m_boReadQuestList = FALSE;
	if(m_xQuest.GetCounter() != 0){
		m_xQuest.MoveCurrentToTop();
		for( nCnt = 0; nCnt < m_xQuest.GetCounter() ; nCnt++ ){
			if(m_xQuest.GetCurrentData()->pSubQuest!=NULL){
				m_xQuest.GetCurrentData()->pSubQuest->ClearAllNodes();
				m_xQuest.MoveNextNode();
			}
		}
	}
	m_xQuest.ClearAllNodes();
}


BOOL CQuestWnd::SortMainQuest(VOID)
{
	INT						nCnt;
	INT						nLoop;
	INT						nCount;
	P_MAIN_QUEST			*xTemp;
	P_MAIN_QUEST			xSwap;


	nCount = m_xQuest.GetCounter();

	xTemp = new P_MAIN_QUEST[nCount];

	// Copy
	m_xQuest.MoveCurrentToTop();
	for( nCnt = 0; nCnt < nCount ; nCnt++){
		xTemp[nCnt] = m_xQuest.GetCurrentData();
		m_xQuest.DeleteCurrentNodeEx();
	}
	// Sort
	for( nCnt = 0; nCnt<nCount-1 ; nCnt++){
		for(nLoop = nCnt+1; nLoop < nCount ; nLoop++){
			if(xTemp[nCnt]->nIndex > xTemp[nLoop]->nIndex){
				xSwap=xTemp[nCnt];
				xTemp[nCnt]=xTemp[nLoop];
				xTemp[nLoop]=xSwap;
			}
		}
	}

	// Copy
	for( nCnt = 0; nCnt < nCount ; nCnt++){
		xTemp[nCnt]->boExpand = FALSE;
		m_xQuest.AddNode(xTemp[nCnt]);
	}

	return TRUE;
}

BOOL CQuestWnd::SortSubQuest(P_MAIN_QUEST pMQuest)
{
	INT						nCnt;
	INT						nLoop;
	INT						nCount;
	P_SUB_QUEST				*pSQuest;
	P_SUB_QUEST				xSwap;

	nLoop = 0;

	if(pMQuest==NULL || pMQuest->pSubQuest==NULL)
		return FALSE;
	nCount = pMQuest->pSubQuest->GetCounter();
	pSQuest = new P_SUB_QUEST[nCount];

	// Copy
	pMQuest->pSubQuest->MoveCurrentToTop();
	for( nCnt = 0; nCnt < nCount; nCnt++){
		pSQuest[nCnt] = pMQuest->pSubQuest->GetCurrentData();
		pMQuest->pSubQuest->DeleteCurrentNodeEx();
	}
	// Sort
	for( nCnt = 0; nCnt < nCount-1; nCnt++){
		for(nLoop = nCnt+1; nLoop < nCount; nCount++){
			if(pSQuest[nCnt]->nIndex > pSQuest[nLoop]->nIndex){
				xSwap = pSQuest[nCnt];
				pSQuest[nCnt] = pSQuest[nLoop];
				pSQuest[nLoop] = xSwap;
			}
		}
	}
	// Copy
	for( nCnt = 0; nCnt < nCount; nCnt++){
		pSQuest[nLoop]->boSelected = FALSE;
		pMQuest->pSubQuest->AddNode(pSQuest[nLoop]);
	}
	return TRUE;
}

BOOL CQuestWnd::AddMainQuest(CHAR *pszMQuest,INT nCount)						//	Add Main Quest
{
	INT				nIdx;
//	BOOL			boDone;
//	INT				nSubCnt;
	INT				nCnt;
	CHAR			*pszIdx = pszMQuest;
	CHAR			*pszTitle;
//	CHAR			*pszSubCount;
//	CHAR			*pszDone;
//	CHAR			*pszExplanation;
	P_MAIN_QUEST	pMainQuest	= NULL;

	if(!m_boReadQuestList){
		g_xClientSocket.SendQueryQuest();		
		return FALSE;
	}

	if((strlen(pszMQuest)<=0) || (nCount<=0))
		return FALSE;

	for( nCnt = 0; nCnt < nCount && pszIdx!=NULL; nCnt++){

		pszTitle	= strchr(pszIdx,'/');
		*pszTitle	= NULL;
		nIdx		= atoi(pszIdx);
		if(IsExistMainQuest(nIdx))
			return FALSE;
		pszTitle++;
		pszIdx	= strchr(pszTitle,'/');
		if(pszIdx!=NULL){
			*pszIdx= NULL;
			pszIdx++;
		}
/*		pszSubCount++;
		pszDone		= strchr(pszSubCount,'/');
		*pszDone	= NULL;
		nSubCnt		= atoi(pszSubCount);
		pszDone++;
		pszExplanation		= strchr(pszDone,'/');
		if(pszExplanation!=NULL){
			*pszExplanation		= NULL;
			pszExplanation++;
			if((*pszExplanation)!='/'){
				pszIdx		= strchr(pszExplanation,'/');
				if(pszIdx!=NULL){
					*pszIdx				= NULL;
					pszIdx++;		
				}
			}
			else{
				*pszExplanation = NULL;
				pszExplanation++;
				pszIdx = pszExplanation;
			}
		}
		boDone		= atoi(pszDone);*/

		pMainQuest	= new _MAIN_QUEST;
		ZeroMemory(pMainQuest,sizeof(_MAIN_QUEST));

		pMainQuest->nIndex			= nIdx;
		pMainQuest->boDone			= FALSE;
		pMainQuest->nSubQuestCnt	= 0;
		pMainQuest->boExpand		= FALSE;
		pMainQuest->boFilledSubQuest= FALSE;
		if(pMainQuest->pSubQuest != NULL) pMainQuest->pSubQuest->ClearAllNodes();
		strcpy(pMainQuest->pszTitle, pszTitle);
/*		if(pszExplanation!=NULL){
			strcpy(pMainQuest->szExplanation, pszExplanation);
			pMainQuest->boFilledExplanation = TRUE;
		}
		else{
*/			ZeroMemory(pMainQuest->szExplanation,1024);
			pMainQuest->boFilledExplanation = FALSE;
//		}
		m_xQuest.AddNode(pMainQuest);
		pMainQuest = NULL;
	}
	m_nLastLinenum = m_xQuest.GetCounter();
	m_boReadQuestList = TRUE;
	SortMainQuest();
	return TRUE;
}

BOOL CQuestWnd::AddSubQuest(CHAR *pszSubQuest, INT nQuestIdx, INT nCount)	//	Add Sub Quest
{
	INT				nIdx;
	BOOL			boDone;
	BOOL			boSwitch;
	INT				nCnt;
	INT				nQIdx;
	CHAR			*pszIdx = pszSubQuest;
	CHAR			*pszTitle;
	CHAR			*pszDone;
	CHAR			*pszExplanation = NULL;
	P_SUB_QUEST		pSubQuest	= NULL;
	P_MAIN_QUEST	pMainQuest	= NULL;

	if(!m_boReadQuestList){
		g_xClientSocket.SendQueryQuest();		
		return FALSE;
	}
	if((strlen(pszSubQuest)<=0) || (nCount<=0))
		return FALSE;

	boSwitch	= TRUE;
	nCnt		= 0;

	pszIdx = strchr(pszSubQuest,'/');
	*pszIdx = NULL;
	pszIdx ++;
	nQIdx = atoi(pszSubQuest);

	m_xQuest.MoveCurrentToTop();
	while(boSwitch && nCnt < m_xQuest.GetCounter()){
		if(m_xQuest.GetCurrentData()->nIndex == nQIdx){
			pMainQuest = m_xQuest.GetCurrentData();
			boSwitch = FALSE;
		}
		nCnt++;
		m_xQuest.MoveNextNode();
	}

	if(pMainQuest==NULL)
		return FALSE;

	if(pMainQuest->pSubQuest==NULL)
		pMainQuest->pSubQuest = new CPDLList<_SUB_QUEST>;

	for( nCnt = 0; nCnt < nCount ; nCnt++){
		pszTitle		= NULL;
		pszDone			= NULL;
		pszExplanation	= NULL;
		pszTitle	= strchr(pszIdx,'/');
		*pszTitle	= NULL;
		nIdx		= atoi(pszIdx);
		if(IsExistSubQuest(nQuestIdx,nIdx))
			return FALSE;
		pszTitle++;
		pszExplanation		= strchr(pszTitle,'/');
		if(pszExplanation!=NULL){
			*pszExplanation		= NULL;
			pszExplanation++;
			if((*pszExplanation)!='/'){
				pszIdx		= strchr(pszExplanation,'/');
				if(pszIdx!=NULL){
					*pszIdx				= NULL;
					pszIdx++;		
				}
			}
			else{
				*pszExplanation = NULL;
				pszExplanation++;
				pszIdx = pszExplanation;
			}
		}
		boDone = FALSE;
		pSubQuest = new _SUB_QUEST;
		ZeroMemory(pSubQuest,sizeof(_SUB_QUEST));

		pSubQuest->nIndex	= nIdx;
		if(pMainQuest->boDone)
			pSubQuest->boDone	= pMainQuest->boDone;
		else
			pSubQuest->boDone	= boDone;
		pMainQuest->boFilledSubQuest		= TRUE;
		strcpy(pSubQuest->pszTitle , pszTitle);
		if(pszExplanation!=NULL){
			strcpy(pSubQuest->szExplanation, pszExplanation);
			pSubQuest->boFilledExplanation = TRUE;
		}
		else{
			ZeroMemory(pSubQuest->szExplanation,1024);
			pSubQuest->boFilledExplanation = FALSE;
		}
		pMainQuest->pSubQuest->AddNode(pSubQuest);
		pSubQuest = NULL;
		pMainQuest->nSubQuestCnt++;
	}
	return TRUE;
}


BOOL CQuestWnd::IsExistMainQuest(INT Idx)
{
	INT nCnt=0;
	BOOL boSwitch = TRUE;
	P_MAIN_QUEST pMainQuest = NULL;
	m_xQuest.MoveCurrentToTop();
	while(boSwitch && nCnt < m_xQuest.GetCounter()){
		if(m_xQuest.GetCurrentData()->nIndex == Idx){
			pMainQuest = m_xQuest.GetCurrentData();
			boSwitch = FALSE;
		}
		nCnt++;
		m_xQuest.MoveNextNode();
	}

	if(pMainQuest!=NULL)
		return TRUE;
	else
		return FALSE;
}
BOOL CQuestWnd::IsExistSubQuest(INT MIdx,INT SIdx)
{
	INT nCnt=0;
	BOOL boSwitch = TRUE;
	P_MAIN_QUEST pMainQuest = NULL;
	P_SUB_QUEST	pSubQuest = NULL;
	m_xQuest.MoveCurrentToTop();
	while(boSwitch && nCnt < m_xQuest.GetCounter()){
		if(m_xQuest.GetCurrentData()->nIndex == MIdx){
			pMainQuest = m_xQuest.GetCurrentData();
			boSwitch = FALSE;
		}
		nCnt++;
		m_xQuest.MoveNextNode();
	}
	if(pMainQuest==NULL)
		return FALSE;
	boSwitch = TRUE;
	nCnt =0;
	if(pMainQuest->pSubQuest!=NULL){
		pMainQuest->pSubQuest->MoveCurrentToTop();
		while(boSwitch && nCnt < pMainQuest->pSubQuest->GetCounter()){
			if(pMainQuest->pSubQuest->GetCurrentData()->nIndex == SIdx){
				pSubQuest = pMainQuest->pSubQuest->GetCurrentData();
				boSwitch = FALSE;
			}
			nCnt++;
			pMainQuest->pSubQuest->MoveNextNode();
		}
	}
	else
		return FALSE;
	if(pSubQuest!=NULL)
		return TRUE;
	else
		return FALSE;
}

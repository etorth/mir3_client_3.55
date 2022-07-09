// 최대 버튼의 수

#include "stdafx.h"
#define MAX_TXT_BUTTON_COUNT	5

/////////////////////////////////////////////////////////////////////////
//	CTextButton : 생성자
/////////////////////////////////////////////////////////////////////////
CTextButton::CTextButton()
{
	m_pTxtBtn.ClearAllNodes();
	m_nTxtHeight = 0;
	m_nMaxLine = 0;
	m_bIsReady = FALSE;
	m_IsUseSubTxt = FALSE;
}

/////////////////////////////////////////////////////////////////////////
//	~CTextButton : 소멸자
/////////////////////////////////////////////////////////////////////////
CTextButton::~CTextButton()
{
	ReleaseButtons();
}

/////////////////////////////////////////////////////////////////////////
//	AddButton : Text 버튼을 추가한다.
/////////////////////////////////////////////////////////////////////////
// pszTxt: 화면에 표시될 Text
// xRect: 버튼으로 인식될 Rect 영역
// nLinePos: 찍힐곳의 Line Count
// pszParam: 클릭 되었을때 쓰일 Parameter값
/////////////////////////////////////////////////////////////////////////
BOOL	CTextButton::AddButton(CHAR *pszTxt,RECT xRect,INT nLinePos,CHAR *pszParam,COLORREF nColor,COLORREF cColor,INT nImgID,INT nSubMenu)
{
	if(m_bIsReady)
	{
		SIZE tSize;
		CMTxtBtn* tCMTxtBtn;
		tCMTxtBtn = new  CMTxtBtn;
		tSize = g_xMainWnd.GetStrLength(NULL,NULL,pszTxt);
		m_nTxtHeight  = xRect.bottom - xRect.top;
		strcpy(tCMTxtBtn->Txt,pszTxt);
		tCMTxtBtn->xRect = xRect;
		tCMTxtBtn->nLinePos = nLinePos;
		strcpy(tCMTxtBtn->Param,pszParam);
		tCMTxtBtn->bIsClicked = FALSE;
		tCMTxtBtn->nColor = nColor;
		tCMTxtBtn->cColor = cColor;
		tCMTxtBtn->nImgID = nImgID;
		tCMTxtBtn->nSubMenu = nSubMenu;

		m_pTxtBtn.AddNode(tCMTxtBtn);
		return TRUE;
	}
	else 
		return FALSE;
}

BOOL	CTextButton::AddButton(CHAR *pszTxt,CHAR *pszTxt2,RECT xRect,INT nLinePos,CHAR *pszParam,COLORREF nColor,COLORREF cColor,INT nImgID,INT nSubMenu)
{
	if(m_bIsReady)
	{
		SIZE tSize;
		CMTxtBtn* tCMTxtBtn;
		tCMTxtBtn = new  CMTxtBtn;
		tSize = g_xMainWnd.GetStrLength(NULL,NULL,pszTxt);
		m_nTxtHeight  = tSize.cy;

		strcpy(tCMTxtBtn->Txt,pszTxt);
		strcpy(tCMTxtBtn->sTxt,pszTxt2);

		tCMTxtBtn->xRect = xRect;
		tCMTxtBtn->nLinePos = nLinePos;

		strcpy(tCMTxtBtn->Param,pszParam);
		tCMTxtBtn->bIsClicked = FALSE;
		tCMTxtBtn->nColor = nColor;
		tCMTxtBtn->cColor = cColor;
		tCMTxtBtn->nImgID = nImgID;
		tCMTxtBtn->nSubMenu = nSubMenu;

		m_pTxtBtn.AddNode(tCMTxtBtn);
		m_IsUseSubTxt = TRUE;
		return TRUE;
	}
	else 
		return FALSE;
}

/////////////////////////////////////////////////////////////////////////
//	ClickCheck : Button Click 에 의한 Click Checking 을 한다.
/////////////////////////////////////////////////////////////////////////
// xPos: 실제 마우스 좌표를 받아 올것
// xWndPos: 실제 Text가 쓰이기 시작 하는 곳의 좌표를 받어 올것
// CurrentTopLine: 현제 Window 상에 찍히는 가장 윗줄
/////////////////////////////////////////////////////////////////////////
CMTxtBtn*	CTextButton::ClickCheck(POINT xWndPos,POINT	xPos,INT CurrentTopLine)
{
	if(m_bIsReady)
	{
		m_pTxtBtn.MoveCurrentToPos(CurrentTopLine);
		for(int i = CurrentTopLine; i< CurrentTopLine+m_nMaxLine;i++)
		{
			if(IsCurrsorOnThisButton(m_pTxtBtn.GetCurrentData(),xWndPos,xPos,CurrentTopLine))
			{
				m_nSelect = i;
				m_pTxtBtn.GetCurrentData()->bIsClicked = !m_pTxtBtn.GetCurrentData()->bIsClicked;
				return m_pTxtBtn.GetCurrentData();
			}
			m_pTxtBtn.MoveNextNode();
		}
	}
	return NULL;
}

CMTxtBtn*	CTextButton::SetClick(INT nPos)
{
	if(m_bIsReady)
	{
		m_pTxtBtn.MoveCurrentToPos( nPos );
		if( m_pTxtBtn.GetCurrentData() )
		{
			m_nSelect = nPos;
			m_pTxtBtn.GetCurrentData()->bIsClicked = !m_pTxtBtn.GetCurrentData()->bIsClicked;
			return m_pTxtBtn.GetCurrentData();
		}
	}
	return NULL;
}


/////////////////////////////////////////////////////////////////////////
//	ReleaseButtons : 이미 잡혀 있는 모든 버튼들을 날린다.
/////////////////////////////////////////////////////////////////////////
BOOL CTextButton::ReleaseButtons(VOID)
{
	if(m_bIsReady)
	{
		m_pTxtBtn.ClearAllNodes();
		m_nTxtHeight = 0;
		return TRUE;
	}
	else
		return FALSE;
}

/////////////////////////////////////////////////////////////////////////
//	InitTxtBtn : 본 클래스를 사용 할수 있도록 준비 한다.
/////////////////////////////////////////////////////////////////////////
// nTextHeight: 실제 Text의 Height  
// WndRect: 윈도우의 크기  
// nMaxLine: 찍을수 있는 최대 라인수
/////////////////////////////////////////////////////////////////////////
BOOL CTextButton::InitTxtBtn(INT nMaxLine,POINT StartPos,INT nLineGap)
{
	m_bIsReady = TRUE;
	m_nMaxLine = nMaxLine;
	m_xStartPos = StartPos;
	m_nLineGap = nLineGap;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////
//	GetButton : 해당 Button의 포인터를 얻는다.
/////////////////////////////////////////////////////////////////////////
// nIndex : Index
/////////////////////////////////////////////////////////////////////////
CMTxtBtn* CTextButton::GetButton(INT nIndex)
{
	m_pTxtBtn.MoveCurrentToPos(nIndex);
	if( nIndex == m_pTxtBtn.GetCurrPosition() )
		return m_pTxtBtn.GetCurrentData();

	return NULL;
}

/////////////////////////////////////////////////////////////////////////
//	GetButtonCount : Button의 수를 얻는다.
/////////////////////////////////////////////////////////////////////////
INT CTextButton::GetButtonCount(VOID)
{
	return m_pTxtBtn.GetCounter();
}

VOID CTextButton::ClickFreeAllBtn(VOID)
{
	m_pTxtBtn.MoveCurrentToTop();
	for(int i = 0 ; i < m_pTxtBtn.GetCounter() ; i++)
	{
		m_pTxtBtn.GetCurrentData()->bIsClicked = FALSE;
		m_pTxtBtn.MoveNextNode();
	}
	m_nSelect = -1;
}

VOID CTextButton::ClickFree(VOID)
{
	if( m_nSelect != -1 )
	{
		m_pTxtBtn.MoveCurrentToPos( m_nSelect );
		m_pTxtBtn.GetCurrentData()->bIsClicked = FALSE;
		m_nSelect = -1;
	}
}

/////////////////////////////////////////////////////////////////////////
//	ClickCheck : Button Click 에 의한 Click Checking 을 한다.
/////////////////////////////////////////////////////////////////////////
// xPos: 실제 마우스 좌표를 받아 올것
// xWndPos: 실제 Text가 쓰이기 시작 하는 곳의 좌표를 받어 올것
// CurrentTopLine: 현제 Window 상에 찍히는 가장 윗줄
/////////////////////////////////////////////////////////////////////////


CMTxtBtn* CTextButton::ButtonDownCheck(POINT xWndPos,POINT xPos,INT CurrentTopLine)
{
///	CMTxtBtn*	xResult=NULL;
/*	int			nTempX,nTempY;
	int			StdPosX,StdPosY;	// 움직이는 윈도우내에서 기준 점을 계산 한다.*/
	
	if(m_bIsReady)
	{
		m_pTxtBtn.MoveCurrentToTop();
		for(int i = 0; i<m_pTxtBtn.ListLength();i++)
		{
			if((m_pTxtBtn.GetCurrentData()->nLinePos >= CurrentTopLine) && (m_pTxtBtn.GetCurrentData()->nLinePos <= CurrentTopLine+m_nMaxLine))
			{
				if(IsCurrsorOnThisButton(m_pTxtBtn.GetCurrentData(),xWndPos,xPos,CurrentTopLine))
				{
					m_nSelect = i;
					m_pTxtBtn.GetCurrentData()->bIsClicked = TRUE; 
					return m_pTxtBtn.GetCurrentData();
				}
				m_pTxtBtn.GetCurrentData()->bIsClicked = FALSE;
			}
			m_pTxtBtn.MoveNextNode();
		}
	}
	return NULL;
}


CMTxtBtn* CTextButton::ButtonUpCheck(POINT xWndPos,POINT xPos,INT CurrentTopLine)
{	
	if(m_bIsReady)
	{
		m_pTxtBtn.MoveCurrentToTop();
		for(int i = 0; i<m_pTxtBtn.ListLength();i++)
		{
			if((m_pTxtBtn.GetCurrentData()->nLinePos >= CurrentTopLine) && (m_pTxtBtn.GetCurrentData()->nLinePos <= CurrentTopLine+m_nMaxLine))
			{
				if(IsCurrsorOnThisButton(m_pTxtBtn.GetCurrentData(),xWndPos,xPos,CurrentTopLine))
				{
					m_nSelect = i;
					m_pTxtBtn.GetCurrentData()->bIsClicked = FALSE;   
					return m_pTxtBtn.GetCurrentData();
				}
			}
			m_pTxtBtn.MoveNextNode();
		}
	}
	return NULL;
}



BOOL CTextButton::IsCurrsorOnThisButton(CMTxtBtn* pBtn,POINT xWndPos,POINT xPos,INT CurrentTopLine)
{
	RECT rcButton;
	rcButton.top	= xWndPos.y + (pBtn->nLinePos - CurrentTopLine)*(m_nTxtHeight+m_nLineGap) + m_xStartPos.y;		// 가변 위치에서의 Top을 구한다.
	rcButton.left	= xWndPos.x + pBtn->xRect.left + m_xStartPos.x;													// 가변 위치에서의 Left를 구한다.
	rcButton.right	= rcButton.left + pBtn->xRect.right;
	rcButton.bottom	= rcButton.top	+ pBtn->xRect.bottom;
			
	if( PtInRect(&rcButton, xPos) )
		return TRUE;

	return FALSE;
}
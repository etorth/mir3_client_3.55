/*
		FileName            : NPCWnd.cpp
		Description         : NPCWnd class
		Author/Date         : 
		Modification History: 
		-----------------------------------------------------
		01.						CNPCWnd();
		02.						~CNPCWnd();
		03.VOID					Init();
		04.VOID					Destroy();
		10.VOID					CreateNPCChatWnd();
		11.VOID					SetStatusBtnInit();
		12.VOID					ShowNPCChatWnd();
		13.BOOL					OnLButtonDown();
		14.BOOL					OnLButtonUp();
		15.LRESULT				OnMsgBoxReturn();
		16.BOOL					OnMouseMove();
		17.void					ResetDialog();
		18.VOID					OnScrollDown();
		19.VOID					OnScrollUp();
		20.BOOL					ClickCommandProcess();
		21.VOID					SetWndRectExtend();
		22.VOID					SetWndRectReduce();
		23.VOID					SetNpcEditBoxPos();
		24.VOID					OnEnterKeyDown();
		25.BOOL					OnMsgInputted();
		26.void					NpcWndCountLineNumInScript();
		27.char*				NpcWndCheckText();
*/

#include "StdAfx.h"

#define MAX_NPCSTR_HEIGHT		129		
#define MAX_SHOW_LINE			14
#define MAX_SHOW_LINE_NO_IMG	18
#define POS_DRAWSTART_Y			40
#define LINE_GAP				4		

#define BUILD_GUILD				"@@BUILDGUILDNOW"			// 문파 설립
#define GUILD_WAR				"@@GUILDWAR"				// 문쟁 신청
#define WITHDRAWAL_CASTLE		"@@WITHDRAWAL"				// 돈을 찾는다.
#define RECEIPT_CASTLE			"@@RECEIPTS"				// 돈을 맡긴다.

#define	HEIGHT_BOTTOM_WINDOW	64

#define MAX_CHAR_INLINE			50
#define HALF_CHAR_INLINE		33
#define LINENUM_PICTUREHEIGHT	7

COLORREF ScriptTxtColor[] = {	RGB(0, 0, 0),		// 0 : Black
								RGB(255, 0, 0),		// 1 : Red
								RGB(0, 128, 0),		// 2 : Green
								RGB(128, 128, 0), 	// 3 : Olive
								RGB(128, 128, 128), // 4 : Gray
								RGB(128, 0, 0),		// 5 : Marron
								RGB(0, 128, 128),	// 6 : Teal
								RGB(0, 0, 128),		// 7 : Navy
								RGB(192, 192, 192),	// 8 : Silver
								RGB(128, 0, 128),	// 9 : Purple
								RGB(0, 255, 0),		// 10 : Lime
								RGB(0, 0, 255),		// 11 : Blue
								RGB(255, 255, 255),	// 12 : White
								RGB(255, 0, 255),	// 13 : Fuchsia
								RGB(0, 255, 255),	// 14 : Aqua
								RGB(255, 255, 0),	// 15 : Yellow
								RGB(1, 1, 1),		// 16 : Default
							};


CList<CScriptLine>	ScriptList;
char					szQuestNPCName[64];

/***** Func-- **********************************************************************/
char*
CNPCWnd::CheckText(char *pszScript)
{
	char	*pszText = NULL;

	if (pszScript)
	{
		int		nLen = strlen(pszScript);
		int		nCurrLen = 0;
		
		pszText = pszScript;

		while (*pszText && nCurrLen < nLen)
		{
			if (*pszText == '\\' || *pszText == '<' || *pszText == '{')
				return pszText;

			// 문자열 중간에 '_'를 ' '로 치환해 준다.
			if (*pszText == '_')
				*pszText = ' ';

			pszText++;
			nCurrLen++;
		}
	}

	return pszText;
}

/***** Func-- **********************************************************************/
char*
CNPCWnd::AddScriptLine(char *pszLine, int nLineLen, int nType)
{
	CScriptLine* pScriptLine = new CScriptLine;

	if (pScriptLine)
	{
		pScriptLine->m_btScriptType = (BYTE)nType;

		switch (nType)
		{
			case SCRIPT_GENTEXT:
			{
				pScriptLine->m_pszScriptText	= new char[nLineLen + 1];

				memcpy(pScriptLine->m_pszScriptText, pszLine, nLineLen);
				pScriptLine->m_pszScriptText[nLineLen] = '\0';

				ScriptList.Insert (pScriptLine);

				return NULL;
			}
			case SCRIPT_RETURN:
			{
				ScriptList.Insert (pScriptLine);

				return NULL;
			}
			case SCRIPT_BUTTON:
			{
				char *pszEndCmd;
				char *pszDevide;

				if (pszEndCmd = (char *)strchr(pszLine, '>'))
				{
					*pszEndCmd = '\0';

					if (pszDevide = (char *)strchr(pszLine, '/'))
					{
						*pszDevide = '\0';

						pScriptLine->m_pszScriptCommand = new char[pszEndCmd - pszDevide + 1];
						pScriptLine->m_pszScriptText	= new char[pszDevide - pszLine + 1];
						
						strcpy(pScriptLine->m_pszScriptCommand, ++pszDevide);
						strcpy(pScriptLine->m_pszScriptText, ++pszLine);

						ScriptList.Insert (pScriptLine);
					}

					return ++pszEndCmd;
				}

				return NULL;
			}
			case SCRIPT_TAG:
			{
				char *pszEndCmd;
				char *pszDevide;

				if (pszEndCmd = (char *)strchr(pszLine, '}'))
				{
					*pszEndCmd = '\0';

					if (pszDevide = (char *)strchr(pszLine, '/'))
					{
						*pszDevide = '\0';

						pScriptLine->m_pszScriptCommand = new char[pszEndCmd - pszDevide + 1];
						pScriptLine->m_pszScriptText	= new char[pszDevide - pszLine + 1];
						
						strcpy(pScriptLine->m_pszScriptCommand, ++pszDevide);
						strcpy(pScriptLine->m_pszScriptText, ++pszLine);

						ScriptList.Insert (pScriptLine);
					}

					return ++pszEndCmd;
				}

				return NULL;
			}
		}
	}

	delete pScriptLine;

	return NULL;
}

/***** Func-- **********************************************************************/
void
CNPCWnd::DevideScript(char *pszScript)
{
	char *pszText = pszScript;
	char *pszPaser;
	int  nLineLen = 0;
	int	 nLen = strlen(pszScript);

	while (pszText!=NULL && *pszText && (pszText - pszScript) < nLen)
	{
		if (pszPaser = CheckText(pszText))
		{
			nLineLen = pszPaser - pszText;

			switch (*pszPaser)
			{
				case '\\':
				{
					if (nLineLen >= 1)
						AddScriptLine(pszText, nLineLen, SCRIPT_GENTEXT);

					AddScriptLine(NULL, 0, SCRIPT_RETURN);
					
					pszText = ++pszPaser;

					break;
				}
				case '<':
				{
					if (nLineLen >= 1)
						AddScriptLine(pszText, nLineLen, SCRIPT_GENTEXT);

					pszText = AddScriptLine(pszPaser, nLineLen, SCRIPT_BUTTON);

					break;
				}
				case '{':
				{
					if (nLineLen >= 1)
						AddScriptLine(pszText, nLineLen, SCRIPT_GENTEXT);

					pszText = AddScriptLine(pszPaser, nLineLen, SCRIPT_TAG);

					break;
				}
				default:
				{
					pszText = AddScriptLine(pszText, nLineLen, SCRIPT_GENTEXT);
					break;
				}
			}
		}
	}
	NpcWndScriptInit();
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/***** Func01 ****************************************************************/
CNPCWnd::CNPCWnd()
{
	m_nStartLine	= 0;
	m_dwLastNPCTick = 0;
}

/***** Func02 ****************************************************************/
CNPCWnd::~CNPCWnd()
{
	CScriptLine*	pScriptLine = NULL;
 	CListNode<CScriptLine> 	*pNode;

	for (pNode = ScriptList.GetHead(); pNode; pNode = pNode->GetNext())
	{
		pScriptLine = pNode->GetData();
		pScriptLine->m_pszScriptText = NULL;
		pScriptLine->m_pszScriptCommand = NULL;
	}
	ResetDialog();
}

/***** Func03 ****************************************************************/
VOID
CNPCWnd::Init()
{
	INT nCnt;
	CGameWnd::Init();

	m_xNPCScrlBar.Init();

	mNpcwnd_bBright		= 180;
	mNpcwnd_bOpa		= 180;
	m_nStartLine		= 0;
	m_dwLastNPCTick		= 0;
	mNpcwnd_bHasImage = FALSE;

	mNpcwnd_nNumMiddleWindow		= 13;		//lks_mark
	mNpcwnd_bShowFlickeringDownBtn	= FALSE;
	mNpcwnd_bShowFlickeringTimer	= 0;

	mNpcwnd_nHeightMiddleWindow		= 20;
	mNpcwnd_nSumOfTopBottomLine		= 8;
	mNpcwnd_nMaxMiddleWndCount		= 13;

//	m_bCanClose	= FALSE;
	m_bCanClose	= TRUE;
	m_nNpcId	= -1;

	ZeroMemory(m_pszSaveCmd, MAX_PATH);

	for ( nCnt = 0; nCnt < _MAX_NPC_BTN; nCnt++ )
	{
		m_xNPCBtn[nCnt].Init();
	}

	SAFE_RELEASE(m_pddsSurface);
	m_nSurfaceW = m_nSurfaceH = m_nSX = m_nSY = 0;
}

/***** Func04 ****************************************************************/
VOID CNPCWnd::Destroy()
{
	INT nCnt;
	CGameWnd::Destroy();

	for ( nCnt = 0; nCnt < _MAX_NPC_BTN; nCnt++ )
	{
		m_xNPCBtn[nCnt].Destroy();
	}

	m_xNPCImage.Destroy();
	Init();
}


VOID CNPCWnd::SetNPCWndTextr(LPDIRECT3DDEVICE7 pd3dDevice)
{
    D3DDEVICEDESC7 ddDesc;
    DDSURFACEDESC2 ddsd;

	// Surface Clear.
	SAFE_RELEASE(m_pddsSurface);
	m_nSurfaceW = m_nSurfaceH = m_nSX = m_nSY = 0;

	// Surface Make.
    if ( NULL == pd3dDevice )
	{
        return;
	}

    if ( FAILED(pd3dDevice->GetCaps(&ddDesc)) )
	{
        return;
	}

	// Window Image의 크기.
	const INT nRW = 386;
	const INT nTH = 140;
	const INT nMH = 20;
	const INT nBH = 64;

	INT nRH = nTH + (nMH*mNpcwnd_nNumMiddleWindow) + nBH;
	INT nH  = 1;
	INT nW  = 1;

    for ( nH = 1; nRH > nH; nH <<= 1 );
    for ( nW = 1; nRW > nW; nW <<= 1 );

	m_nSurfaceW = nW;
	m_nSurfaceH = nH;

    D3DUtil_InitSurfaceDesc(ddsd);
    ddsd.dwFlags         = DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps  = DDSCAPS_TEXTURE;
	ddsd.dwTextureStage  = 0;    
    ddsd.dwWidth         = m_nSurfaceW;
    ddsd.dwHeight        = m_nSurfaceH;

    if ( ddDesc.deviceGUID == IID_IDirect3DHALDevice || ddDesc.deviceGUID == IID_IDirect3DTnLHalDevice )
	{
        ddsd.ddsCaps.dwCaps2 = DDSCAPS2_TEXTUREMANAGE;
	}
    else
	{
        ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
	}

	// 직사각형의 텍스춰를 지원하지 않는다면...
    if ( ddDesc.dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_SQUAREONLY )
    {
        if ( ddsd.dwWidth > ddsd.dwHeight ) ddsd.dwHeight = ddsd.dwWidth;
        else                                ddsd.dwWidth  = ddsd.dwHeight;
    }

    HRESULT hr = g_xMainWnd.GetDirectDraw()->CreateSurface(&ddsd, &m_pddsSurface, NULL);

    if( FAILED(hr) )
	{
		m_nSurfaceW = m_nSurfaceH = 0;
        return;
	}

	// 컬러키를 세팅한다.
	DDSetColorKey(m_pddsSurface, RGB(0, 0, 0));

	// 까만색으로 채운다.
	DDBLTFX ddbltfx;
	ZeroMemory(&ddbltfx, sizeof(ddbltfx));
	ddbltfx.dwSize      = sizeof(ddbltfx);
//	ddbltfx.dwFillColor = RGB(10, 10, 10);
	ddbltfx.dwFillColor = RGB(0, 0, 0);
	m_pddsSurface->Blt(NULL, NULL, NULL, DDBLT_COLORFILL, &ddbltfx);

	INT	nTopImgIdx, nMiddleImgIdx, nBottomImgIdx;

	if ( mNpcwnd_bHasImage == TRUE )
	{
		nTopImgIdx = _WNDIMGIDX_NPCCHAT_TOP_NOFACE;
	}
	else
	{
		nTopImgIdx = _WNDIMGIDX_NPCCHAT_TOP_NOFACE;
	}

	nMiddleImgIdx = _WNDIMGIDX_NPCCHAT_MIDDLE;

	if ( mNpcwnd_bShowScroll == TRUE )
	{
		nBottomImgIdx = _WNDIMGIDX_NPCCHAT_BOTTOM;
	}
	else
	{
		nBottomImgIdx = _WNDIMGIDX_NPCCHAT_BOTTOM;
	}

	RECT rc = {0, 0, 0, 0};
	INT  nSX = m_nSurfaceW/2 - nRW/2;
	INT  nSY = m_nSurfaceH/2 - nRH/2;
	INT	 nCountShow = 0;

	m_nSX = -nSX;
	m_nSY = -nSY;

	// 인터페이스를 그린다.
	// 상단 이미지.
	if ( m_pxWndImage->NewSetIndex(nTopImgIdx) )
	{
		SetRect(&rc, 0, 0, m_pxWndImage->m_lpstNewCurrWilImageInfo->shWidth, nSY+m_pxWndImage->m_lpstNewCurrWilImageInfo->shHeight);
		g_xMainWnd.DrawWithImageForComp(nSX, nSY, &rc, (WORD*)m_pxWndImage->m_pbCurrImage, 0XFFFF, 0XFFFF, m_pddsSurface);
		nSY += nTH;
	}

	// 중단 이미지.
	do
	{
		if ( m_pxWndImage->NewSetIndex(nMiddleImgIdx) )
		{
			SetRect(&rc, 0, 0, m_pxWndImage->m_lpstNewCurrWilImageInfo->shWidth, nSY+m_pxWndImage->m_lpstNewCurrWilImageInfo->shHeight);
			g_xMainWnd.DrawWithImageForComp(nSX+3, nSY, &rc, (WORD*)m_pxWndImage->m_pbCurrImage, 0XFFFF, 0XFFFF, m_pddsSurface);
			nSY += nMH;
		}
		nCountShow++;
	} while ( nCountShow < mNpcwnd_nNumMiddleWindow );

	// 하단 이미지.
	if ( m_pxWndImage->NewSetIndex(nBottomImgIdx) )
	{
		SetRect(&rc, 0, 0, m_pxWndImage->m_lpstNewCurrWilImageInfo->shWidth, nSY+m_pxWndImage->m_lpstNewCurrWilImageInfo->shHeight);
		g_xMainWnd.DrawWithImageForComp(nSX+1, nSY, &rc, (WORD*)m_pxWndImage->m_pbCurrImage, 0XFFFF, 0XFFFF, m_pddsSurface);
		nSY += nBH;
	}
}


VOID CNPCWnd::ShowNpcWnd()
{
	if ( m_pddsSurface == NULL )
	{
		return;
	}

	D3DMATERIAL7 mtrl;

	D3DVECTOR	 vecTrans((FLOAT)m_nSX, (FLOAT)m_nSY, (FLOAT)0);
	D3DVECTOR	 vecScale((FLOAT)m_nSurfaceW, (FLOAT)m_nSurfaceH, 1);

	D3DUtil_InitMaterial(mtrl, (FLOAT)m_bBright/255.0f, (FLOAT)m_bBright/255.0f, (FLOAT)m_bBright/255.0f);
	mtrl.diffuse.a = (FLOAT)m_bOpa/255.0f;

	g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, m_pddsSurface);
}


/***** Func10 ****************************************************************/
VOID CNPCWnd::CreateNPCChatWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove)
{
	Init();
	CreateGameWnd(nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight);
	CreateNpcwnd(pxWndImage);
		
	m_xNPCBtn[_BTN_ID_NPCCLOSE].CreateGameBtn(pxWndImage, 1221, 1222, nStartX+242, nStartY+280, g_xMsg.GetMsg(1052), _BTN_TYPE_FOCUS, 1221, TRUE);
	m_xNPCBtn[_BTN_ID_NPCSCRLUP].CreateGameBtn(pxWndImage, 386, 387, nStartX+290, nStartY+145, NULL, _BTN_TYPE_FOCUS, 386);
	m_xNPCBtn[_BTN_ID_NPCSCRLDN].CreateGameBtn(pxWndImage, 384, 385, nStartX+306, nStartY+136, NULL, _BTN_TYPE_FOCUS, 384);

	m_bOpa = 220;

	m_xNPCImage.Init();
	m_xNPCImage.NewLoad(".\\Data\\NPCFace.WIL");

	m_xNPCScrlBar.CreateScrlBar(pxWndImage, 320, MAX_SHOW_LINE_NO_IMG, 12, 122, 12);
}

/***** Func10-1 ****************************************************************/
VOID CNPCWnd::CreateNpcwnd(CWHWilImageData* pxWndImage)
{
	int		nWidth = 0;
	int		nHeight = 0;
	int		nStartX = 0, nStartY = 0;
	RECT	rcImg = {0, 0, 0, 0};
	
	m_pxWndImage	= pxWndImage;
///top image load
	nWidth = 386, nHeight = 140;
	if ( m_pxWndImage->NewSetIndex(_WNDIMGIDX_NPCCHAT_TOP_NOFACE) )
	{
		SetRect(&rcImg, 0, 0, 
				m_pxWndImage->m_lpstNewCurrWilImageInfo->shWidth,
				m_pxWndImage->m_lpstNewCurrWilImageInfo->shHeight);
	}

	( ! nWidth )  ?	nWidth = rcImg.right -rcImg.left: nWidth  = nWidth;
	( ! nHeight ) ?	nHeight =rcImg.bottom-rcImg.top : nHeight = nHeight;
	
	SetRect(&mNpcwnd_rcTopImg, 
			nStartX - (rcImg.right - rcImg.left - nWidth )/2, 
			nStartY - (rcImg.bottom - rcImg.top - nHeight)/2, 
			nStartX - (rcImg.right - rcImg.left - nWidth )/2 + (rcImg.right - rcImg.left), 
			nStartY - (rcImg.bottom - rcImg.top - nHeight)/2 + (rcImg.bottom - rcImg.top));

	SetRect(&mNpcwnd_rcTopWnd, nStartX, nStartY, nStartX+nWidth, nStartY+nHeight);

//MIDDLE IMAGE LOAD
	nWidth = 386, nHeight = 20;
	nStartX = 0, nStartY = mNpcwnd_rcTopWnd.bottom+1;
	if ( m_pxWndImage->NewSetIndex(_WNDIMGIDX_NPCCHAT_MIDDLE) )
	{
		SetRect(&rcImg, 0, 0, 
				m_pxWndImage->m_lpstNewCurrWilImageInfo->shWidth,
				m_pxWndImage->m_lpstNewCurrWilImageInfo->shHeight);
	}

	( ! nWidth )  ?	nWidth = rcImg.right -rcImg.left: nWidth  = nWidth;
	( ! nHeight ) ?	nHeight =rcImg.bottom-rcImg.top : nHeight = nHeight;
	
	SetRect(&mNpcwnd_rcMiddleImg, 
			nStartX - (rcImg.right - rcImg.left - nWidth )/2, 
			nStartY - (rcImg.bottom - rcImg.top - nHeight)/2, 
			nStartX - (rcImg.right - rcImg.left - nWidth )/2 + (rcImg.right - rcImg.left), 
			nStartY - (rcImg.bottom - rcImg.top - nHeight)/2 + (rcImg.bottom - rcImg.top));

	SetRect(&mNpcwnd_rcMiddleWnd, nStartX, nStartY, nStartX+nWidth, nStartY+nHeight);

//BOTTOM IMAGE LOAD
	nWidth = 386,nHeight = 64;
	nStartX = 0, nStartY = mNpcwnd_rcMiddleWnd.bottom;
	if ( m_pxWndImage->NewSetIndex(_WNDIMGIDX_NPCCHAT_BOTTOM) )
	{
		SetRect(&rcImg, 0, 0, 
				m_pxWndImage->m_lpstNewCurrWilImageInfo->shWidth,
				m_pxWndImage->m_lpstNewCurrWilImageInfo->shHeight);
	}

	( ! nWidth )  ?	nWidth = rcImg.right -rcImg.left: nWidth  = nWidth;
	( ! nHeight ) ?	nHeight =rcImg.bottom-rcImg.top : nHeight = nHeight;
	
	SetRect(&mNpcwnd_rcBottomImg, 
			nStartX - (rcImg.right - rcImg.left - nWidth )/2, 
			nStartY - (rcImg.bottom - rcImg.top - nHeight)/2, 
			nStartX - (rcImg.right - rcImg.left - nWidth )/2 + (rcImg.right - rcImg.left), 
			nStartY - (rcImg.bottom - rcImg.top - nHeight)/2 + (rcImg.bottom - rcImg.top));

	SetRect(&mNpcwnd_rcBottomWnd, nStartX, nStartY, nStartX+nWidth, nStartY+nHeight);	
}

/***** Func11 ****************************************************************/
VOID CNPCWnd::SetStatusBtnInit()
{
	for( INT nCnt = 0; nCnt < _MAX_NPC_BTN; nCnt++ )
	{
		m_xNPCBtn[nCnt].SetBtnState(_BTN_STATE_NORMAL);
	}
}


VOID CNPCWnd::SetGameWndActive(BOOL bActive)
{
	if ( !bActive )
	{
//		m_bCanClose	= FALSE;
		m_bCanClose = TRUE;
	}
	CGameWnd::SetGameWndActive(bActive);

	if ( m_bActive == FALSE )
	{
		m_nNpcId = -1;
	}
}

/***** Func11-1 ****************************************************************/
VOID CNPCWnd::ShowGameWnd()
{
	int	nCountShow = 0;
	INT	nTopImgIdx, nMiddleImgIdx, nBottomImgIdx;

	if (mNpcwnd_bHasImage == TRUE)
		nTopImgIdx = _WNDIMGIDX_NPCCHAT_TOP_NOFACE;
	else
		nTopImgIdx = _WNDIMGIDX_NPCCHAT_TOP_NOFACE;

	nMiddleImgIdx = _WNDIMGIDX_NPCCHAT_MIDDLE;

	if (mNpcwnd_bShowScroll == TRUE)
		nBottomImgIdx = _WNDIMGIDX_NPCCHAT_BOTTOM;
	else
		nBottomImgIdx = _WNDIMGIDX_NPCCHAT_BOTTOM;

	if ( m_bActive )
	{
		if ( g_bTextrRistricted )
		{
			if ( m_pxWndImage->NewSetIndex(nTopImgIdx) )
			{
 				g_xMainWnd.DrawWithImageForCompClipRgn(mNpcwnd_rcTopImg.left, mNpcwnd_rcTopImg.top, m_pxWndImage->m_lpstNewCurrWilImageInfo->shWidth, m_pxWndImage->m_lpstNewCurrWilImageInfo->shHeight,
													   (WORD*)m_pxWndImage->m_pbCurrImage, _CLIP_WIDTH, 600);
			}

			do
			{
				if ( m_pxWndImage->NewSetIndex(nMiddleImgIdx) )
				{
 					g_xMainWnd.DrawWithImageForCompClipRgn(mNpcwnd_rcMiddleImg.left, mNpcwnd_rcMiddleImg.top-1+mNpcwnd_nHeightMiddleWindow*nCountShow, m_pxWndImage->m_lpstNewCurrWilImageInfo->shWidth, m_pxWndImage->m_lpstNewCurrWilImageInfo->shHeight,
														   (WORD*)m_pxWndImage->m_pbCurrImage, _CLIP_WIDTH, 600);
					nCountShow++;
				}
			} while(nCountShow < mNpcwnd_nNumMiddleWindow);

			if (nCountShow != 0)
				nCountShow--;

			if ( m_pxWndImage->NewSetIndex(nBottomImgIdx) )
			{
 				g_xMainWnd.DrawWithImageForCompClipRgn(mNpcwnd_rcBottomImg.left, mNpcwnd_rcBottomImg.top-1+mNpcwnd_nHeightMiddleWindow*nCountShow, m_pxWndImage->m_lpstNewCurrWilImageInfo->shWidth, m_pxWndImage->m_lpstNewCurrWilImageInfo->shHeight,
													   (WORD*)m_pxWndImage->m_pbCurrImage, _CLIP_WIDTH, 600);
			}

		}
		else
		{
			ShowNpcWnd();
		}
	}
}

/***** Func12 ****************************************************************/
VOID CNPCWnd::ShowNPCChatWnd()
{
	SIZE					tSize, tStringX;
	RECT					tRect;
	CScriptLine*			pScriptLine = NULL;
	int						nLineCnt = 0;
	int						nLine = 0;
	int						POS_DRAWSTART_X					= 35;
	int						POS_DRAWSTART_X_ADD_IMAGE_SIZE	= 150;
	int						MAX_NPCSTR_WIDTH				= 305;
	int						HALF_NPCSTR_WIDTH				= 198;
	CListNode <CScriptLine> *pNode;
	COLORREF				TextColor;
	HFONT					hFont = NULL;
	int						nLengthWidth;
	int						nHeight = 0;
	RECT					rcRectScript = {0, 0, 0, 0};
	
	tRect = GetGameWndRect();				// Get Window Rect

	ShowGameWnd();


	TextColor = ScriptTxtColor[12];

	for (pNode = ScriptList.GetHead(); pNode; pNode = pNode->GetNext())
	{
		pScriptLine = pNode->GetData();

		switch (pScriptLine->m_btScriptType)
		{
			case SCRIPT_GENTEXT:
			{
				char	szTempText[1024];

				tSize = g_xMainWnd.GetStrLength(NULL, NULL, pScriptLine->m_pszScriptText);

				if (nLineCnt < LINENUM_PICTUREHEIGHT)
					nLengthWidth = HALF_NPCSTR_WIDTH;
				else
					nLengthWidth = MAX_NPCSTR_WIDTH;

				if (nLine + tSize.cx > nLengthWidth)
				{
					int nLen	= strlen(pScriptLine->m_pszScriptText);
					int nCount	= 0;

					for (int i = 0; i < nLen; i++)
					{
						if (pScriptLine->m_pszScriptText[i] < 0)
						{
							szTempText[nCount++]	=  pScriptLine->m_pszScriptText[i++];
							szTempText[nCount]		=  pScriptLine->m_pszScriptText[i];
							szTempText[nCount + 1]	= '\0';
						}
						else
						{
							szTempText[nCount]		=  pScriptLine->m_pszScriptText[i];
							szTempText[nCount + 1]	= '\0';
						}

						tSize = g_xMainWnd.GetStrLength(NULL, NULL, szTempText);
						
						if (mNpcwnd_bHasImage == TRUE && nLineCnt < LINENUM_PICTUREHEIGHT && nLine + tSize.cx >= nLengthWidth && mNpcwnd_bShowScroll == FALSE)
						{
							if (nLineCnt >= m_nStartLine && nLineCnt <= m_nStartLine + mNpcwnd_nMaxShowLine)		//이미지가 있는 곳에서 찍는 루틴
								g_xMainWnd.PutsHan(NULL, tRect.left + POS_DRAWSTART_X_ADD_IMAGE_SIZE + nLine, tRect.top + ((nLineCnt - m_nStartLine) * (tSize.cy + LINE_GAP)) + POS_DRAWSTART_Y,
													TextColor, RGB(0, 0, 0), szTempText);
							nLineCnt++;
							nLine	= 0;
							nCount	= 0;
						}
						else if (nLine + tSize.cx >= MAX_NPCSTR_WIDTH)
						{
							if (nLineCnt >= m_nStartLine && nLineCnt <= m_nStartLine + mNpcwnd_nMaxShowLine)		//이미지가 없는 곳에서 찍기 때문에 x좌표가 앞 쪽으로 이동해야 함
							{
								if(mNpcwnd_bShowScroll == TRUE && mNpcwnd_bHasImage == TRUE)
									nHeight = tRect.top + (nLineCnt - m_nStartLine + LINENUM_PICTUREHEIGHT) * (tSize.cy + LINE_GAP) + POS_DRAWSTART_Y;
								else
									nHeight = tRect.top + (nLineCnt - m_nStartLine) * (tSize.cy + LINE_GAP) + POS_DRAWSTART_Y;

								if ( pScriptLine->m_pszScriptText[i+1] != ' ' && szTempText[nCount] != ' ' && szTempText[nCount-1] == ' ')
								{
									szTempText[nCount]		=  ' ';
									i--;
								}
								else if ( pScriptLine->m_pszScriptText[i+1] != ' ' && szTempText[nCount] != ' ' )
								{
									szTempText[nCount]		=  '-';
									i--;
								}

								g_xMainWnd.PutsHan(NULL, tRect.left + POS_DRAWSTART_X + nLine, nHeight,
													TextColor, RGB(0, 0, 0), szTempText);
							}

							nLineCnt++;
							nLine	= 0;
							nCount	= 0;
						}
						else
						{
							nCount++;
						}
					}

					if (nCount)
					{
						if (mNpcwnd_bHasImage == TRUE && nLineCnt < LINENUM_PICTUREHEIGHT && mNpcwnd_bShowScroll == FALSE)		// 마지막 남은 글자를 이미지 옆에 찍을 때
						{
							g_xMainWnd.PutsHan(NULL, tRect.left + POS_DRAWSTART_X_ADD_IMAGE_SIZE + nLine, tRect.top + ((nLineCnt - m_nStartLine) * (tSize.cy + LINE_GAP)) + POS_DRAWSTART_Y,
												TextColor, RGB(0, 0, 0), szTempText);
						}
						else if (nLineCnt >= m_nStartLine && nLineCnt <= m_nStartLine + mNpcwnd_nMaxShowLine)		// 마지막 남은 글자를 이미지 없는 곳에 찍을 때
						{
							if(mNpcwnd_bShowScroll == TRUE && mNpcwnd_bHasImage == TRUE)
								nHeight = tRect.top + (nLineCnt - m_nStartLine + LINENUM_PICTUREHEIGHT) * (tSize.cy + LINE_GAP) + POS_DRAWSTART_Y;
							else
								nHeight = tRect.top + (nLineCnt - m_nStartLine) * (tSize.cy + LINE_GAP) + POS_DRAWSTART_Y;
							g_xMainWnd.PutsHan(NULL, tRect.left + POS_DRAWSTART_X + nLine, nHeight,
												TextColor, RGB(0, 0, 0), szTempText);
						}
						nLine += tSize.cx;
					}
				}
				else
				{
					if (mNpcwnd_bHasImage == TRUE && nLineCnt < LINENUM_PICTUREHEIGHT && mNpcwnd_bShowScroll == FALSE)		//텍스트가 화면 길이에 한 번도 미치지 못할 때면서 이미지 옆에 찍을 때
					{
						g_xMainWnd.PutsHan(NULL, tRect.left + POS_DRAWSTART_X_ADD_IMAGE_SIZE + nLine, tRect.top + ((nLineCnt - m_nStartLine) * (tSize.cy + LINE_GAP)) + POS_DRAWSTART_Y,
											TextColor, RGB(0, 0, 0), pScriptLine->m_pszScriptText);
					}
					else if (nLineCnt >= m_nStartLine && nLineCnt <= m_nStartLine + mNpcwnd_nMaxShowLine)		// 텍스트가 화면 길이에 한 번도 미치지 못할 때면서 이미지 없는 곳에 찍을 때
					{
						if(mNpcwnd_bShowScroll == TRUE && mNpcwnd_bHasImage == TRUE)
							nHeight = tRect.top + (nLineCnt - m_nStartLine + LINENUM_PICTUREHEIGHT) * (tSize.cy + LINE_GAP) + POS_DRAWSTART_Y;
						else
							nHeight = tRect.top + (nLineCnt - m_nStartLine) * (tSize.cy + LINE_GAP) + POS_DRAWSTART_Y;
						g_xMainWnd.PutsHan(NULL, tRect.left + POS_DRAWSTART_X + nLine, nHeight,
											TextColor, RGB(0, 0, 0), pScriptLine->m_pszScriptText);
					}
					nLine += tSize.cx;
				}

				break;
			}
			case SCRIPT_RETURN:
				nLineCnt++;
				nLine = 0;
				break;
			case SCRIPT_BUTTON:
			{
				char		szTempText[1024];

				HFONT		hFont = NULL;

				COLORREF	color = RGB(255, 255, 0);

				if (pScriptLine->m_fIsFocused)
					hFont = g_xMainWnd.CreateGameFont("굴려", 9, 0, FW_NORMAL, FALSE, TRUE);

				if (pScriptLine->m_fIsSelected)
					color = RGB(255, 0, 0);

				tSize = g_xMainWnd.GetStrLength(NULL, NULL, pScriptLine->m_pszScriptText);

				if (nLineCnt < LINENUM_PICTUREHEIGHT)
					nLengthWidth = HALF_NPCSTR_WIDTH;
				else
					nLengthWidth = MAX_NPCSTR_WIDTH;

				if (nLine + tSize.cx > nLengthWidth)
				{
					int nLen	= strlen(pScriptLine->m_pszScriptText);
					int nCount	= 0;
					int nRow	= 0;

					for (int i = 0; i < nLen; i++)
					{
						if (pScriptLine->m_pszScriptText[i] < 0)
						{
							szTempText[nCount++]	=  pScriptLine->m_pszScriptText[i++];
							szTempText[nCount]		=  pScriptLine->m_pszScriptText[i];
							szTempText[nCount + 1]	= '\0';
						}
						else
						{
							szTempText[nCount]		=  pScriptLine->m_pszScriptText[i];
							szTempText[nCount + 1]	= '\0';
						}

						tSize = g_xMainWnd.GetStrLength(NULL, NULL, szTempText);


						if (mNpcwnd_bHasImage == TRUE && nLineCnt < LINENUM_PICTUREHEIGHT && nLine + tSize.cx >= nLengthWidth && mNpcwnd_bShowScroll == FALSE)
						{
							if (pScriptLine->m_fIsFocused)
								hFont = g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_NORMAL, FALSE, TRUE);

							if (nLineCnt >= m_nStartLine && nLineCnt <= m_nStartLine + mNpcwnd_nMaxShowLine)		//이미지가 있는 곳에서 찍는 루틴
								g_xMainWnd.PutsHan(NULL, tRect.left + POS_DRAWSTART_X_ADD_IMAGE_SIZE + nLine, tRect.top + ((nLineCnt - m_nStartLine) * (tSize.cy + LINE_GAP)) + POS_DRAWSTART_Y,
													color, RGB(0, 0, 0), szTempText, hFont);
							rcRectScript.left = tRect.left + POS_DRAWSTART_X_ADD_IMAGE_SIZE + nLine;
							rcRectScript.top = tRect.top + ((nLineCnt - m_nStartLine) * (tSize.cy + LINE_GAP)) + POS_DRAWSTART_Y;
							rcRectScript.right = rcRectScript.left + tSize.cx;
							rcRectScript.bottom = rcRectScript.top + tSize.cy;
							NpcWndSetScriptsRect(pScriptLine, rcRectScript);

							tStringX = g_xMainWnd.GetStrLength(NULL, NULL, szTempText);
							nLineCnt++;
							nRow++;
							nLine	= 0;
							nCount	= 0;
						}
						else if (nLine + tSize.cx >= MAX_NPCSTR_WIDTH)
						{
							if (nLineCnt >= m_nStartLine && nLineCnt <= m_nStartLine + mNpcwnd_nMaxShowLine)		//이미지가 없는 곳에서 찍기 때문에 x좌표가 앞 쪽으로 이동해야 함
							{
								if(mNpcwnd_bShowScroll == TRUE && mNpcwnd_bHasImage == TRUE)
								{
									nHeight = tRect.top + (nLineCnt - m_nStartLine + LINENUM_PICTUREHEIGHT) * (tSize.cy + LINE_GAP) + POS_DRAWSTART_Y;
								}
								else
									nHeight = tRect.top + (nLineCnt - m_nStartLine) * (tSize.cy + LINE_GAP) + POS_DRAWSTART_Y;

								if (pScriptLine->m_fIsFocused)
									hFont = g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_NORMAL, FALSE, TRUE);

								if ( pScriptLine->m_pszScriptText[i+1] != ' ' && szTempText[nCount] != ' ' && szTempText[nCount-1] == ' ')
								{
									szTempText[nCount]		=  ' ';
									i--;
								}
								else if ( pScriptLine->m_pszScriptText[i+1] != ' ' && szTempText[nCount] != ' ' )
								{
									szTempText[nCount]		=  '-';
									i--;
								}

								g_xMainWnd.PutsHan(NULL, tRect.left + POS_DRAWSTART_X + nLine, nHeight,
													color, RGB(0, 0, 0), szTempText, hFont);
								rcRectScript.left = tRect.left + POS_DRAWSTART_X + nLine;
								rcRectScript.top = nHeight;
								rcRectScript.right = rcRectScript.left + tSize.cx;
								rcRectScript.bottom = rcRectScript.top + tSize.cy;
								NpcWndSetScriptsRect(pScriptLine, rcRectScript);

							}
							nLineCnt++;
							nRow++;
							nLine	= 0;
							nCount	= 0;
						}
						else
							nCount++;
					}
					if (nCount)
					{
						if (mNpcwnd_bHasImage == TRUE && nLineCnt < LINENUM_PICTUREHEIGHT && mNpcwnd_bShowScroll == FALSE)		// 마지막 남은 글자를 이미지 옆에 찍을 때
						{
							if (pScriptLine->m_fIsFocused)
								hFont = g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_NORMAL, FALSE, TRUE);

							g_xMainWnd.PutsHan(NULL, tRect.left + POS_DRAWSTART_X_ADD_IMAGE_SIZE + nLine, tRect.top + ((nLineCnt - m_nStartLine) * (tSize.cy + LINE_GAP)) + POS_DRAWSTART_Y,
												color, RGB(0, 0, 0), szTempText, hFont);
							rcRectScript.left = tRect.left + POS_DRAWSTART_X_ADD_IMAGE_SIZE + nLine;
							rcRectScript.top = tRect.top + ((nLineCnt - m_nStartLine) * (tSize.cy + LINE_GAP)) + POS_DRAWSTART_Y;
							rcRectScript.right = rcRectScript.left + tSize.cx;
							rcRectScript.bottom = rcRectScript.top + tSize.cy;
							NpcWndSetScriptsRect(pScriptLine, rcRectScript);
						}
						else if (nLineCnt >= m_nStartLine && nLineCnt <= m_nStartLine + mNpcwnd_nMaxShowLine)		// 마지막 남은 글자를 이미지 없는 곳에 찍을 때
						{
							if(mNpcwnd_bShowScroll == TRUE && mNpcwnd_bHasImage == TRUE)
							{
								nHeight = tRect.top + (nLineCnt - m_nStartLine + LINENUM_PICTUREHEIGHT) * (tSize.cy + LINE_GAP) + POS_DRAWSTART_Y;
							}
							else
								nHeight = tRect.top + (nLineCnt - m_nStartLine) * (tSize.cy + LINE_GAP) + POS_DRAWSTART_Y;

							if (pScriptLine->m_fIsFocused)
								hFont = g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_NORMAL, FALSE, TRUE);

							g_xMainWnd.PutsHan(NULL, tRect.left + POS_DRAWSTART_X + nLine, nHeight,
												color, RGB(0, 0, 0), szTempText, hFont);
							rcRectScript.left = tRect.left + POS_DRAWSTART_X + nLine;
							rcRectScript.top = nHeight;
							rcRectScript.right = rcRectScript.left + tSize.cx;
							rcRectScript.bottom = rcRectScript.top + tSize.cy;
							NpcWndSetScriptsRect(pScriptLine, rcRectScript);
						}
						nLine += tSize.cx;
						nRow++;
					}
				}
				else
				{
					if (mNpcwnd_bHasImage == TRUE && nLineCnt < LINENUM_PICTUREHEIGHT && mNpcwnd_bShowScroll == FALSE)		//텍스트가 화면 길이에 한 번도 미치지 못할 때면서 이미지 옆에 찍을 때
					{
						if (pScriptLine->m_fIsFocused)
							hFont = g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_NORMAL, FALSE, TRUE);

						g_xMainWnd.PutsHan(NULL, tRect.left + POS_DRAWSTART_X_ADD_IMAGE_SIZE + nLine, tRect.top + ((nLineCnt - m_nStartLine) * (tSize.cy + LINE_GAP)) + POS_DRAWSTART_Y,
											color, RGB(0, 0, 0), pScriptLine->m_pszScriptText, hFont);
						rcRectScript.left = tRect.left + POS_DRAWSTART_X_ADD_IMAGE_SIZE + nLine;
						rcRectScript.top = tRect.top + ((nLineCnt - m_nStartLine) * (tSize.cy + LINE_GAP)) + POS_DRAWSTART_Y;
						rcRectScript.right = rcRectScript.left + tSize.cx;
						rcRectScript.bottom = rcRectScript.top + tSize.cy;
						NpcWndSetScriptsRect(pScriptLine, rcRectScript);
					}
					else if (nLineCnt >= m_nStartLine && nLineCnt <= m_nStartLine + mNpcwnd_nMaxShowLine)		// 텍스트가 화면 길이에 한 번도 미치지 못할 때면서 이미지 없는 곳에 찍을 때
					{
						if(mNpcwnd_bShowScroll == TRUE && mNpcwnd_bHasImage == TRUE)
						{
							nHeight = tRect.top + (nLineCnt - m_nStartLine + LINENUM_PICTUREHEIGHT) * (tSize.cy + LINE_GAP) + POS_DRAWSTART_Y;
						}
						else
						{
							nHeight = tRect.top + (nLineCnt - m_nStartLine) * (tSize.cy + LINE_GAP) + POS_DRAWSTART_Y;
						}

						if (pScriptLine->m_fIsFocused)
							hFont = g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 9, 0, FW_NORMAL, FALSE, TRUE);

						g_xMainWnd.PutsHan(NULL, tRect.left + POS_DRAWSTART_X + nLine, nHeight,
											color, RGB(0, 0, 0), pScriptLine->m_pszScriptText, hFont);
						rcRectScript.left = tRect.left + POS_DRAWSTART_X + nLine;
						rcRectScript.top = nHeight;
						rcRectScript.right = rcRectScript.left + tSize.cx;
						rcRectScript.bottom = rcRectScript.top + tSize.cy;
						NpcWndSetScriptsRect(pScriptLine, rcRectScript);
					}
					nLine += tSize.cx;
				}

				DeleteObject(hFont);
				
				break;
			}
			case SCRIPT_TAG:
			{
				if (strcmp(pScriptLine->m_pszScriptText, "FCOLOR") == 0)
				{
					int nColor = atoi(pScriptLine->m_pszScriptCommand);

					TextColor = ScriptTxtColor[nColor];
				}
				else if (strcmp(pScriptLine->m_pszScriptText, "NPCIMG") == 0)
				{
/*					int nIndex = atoi(pScriptLine->m_pszScriptCommand);

					if (m_xNPCImage.NewSetIndex(nIndex))
					{
						g_xMainWnd.DrawWithImageForComp(40, 30, m_xNPCImage.m_lpstNewCurrWilImageInfo->shWidth, 
																m_xNPCImage.m_lpstNewCurrWilImageInfo->shHeight, 
																(WORD *)m_xNPCImage.m_pbCurrImage);
					}
*/					// NPC 이미지 안 보여줌
				}
				else if (strcmp(pScriptLine->m_pszScriptText, "NOTCLOSE") == 0)
				{
					m_bCanClose = FALSE;
				}
				break;
			}
		}
	}
	
	m_nMaxLine = nLineCnt;

	m_xNPCBtn[_BTN_ID_NPCCLOSE].ShowGameBtn();

	if (mNpcwnd_bShowScroll == TRUE)
	{
		if ( m_nMaxLine - m_nStartLine > mNpcwnd_nMaxShowLine)
		{
			if (mNpcwnd_bShowFlickeringDownBtn == TRUE)
				m_xNPCBtn[_BTN_ID_NPCSCRLDN].ShowGameBtn();
			if (mNpcwnd_bShowFlickeringTimer == 16)
			{
				mNpcwnd_bShowFlickeringDownBtn == TRUE ? mNpcwnd_bShowFlickeringDownBtn = FALSE : mNpcwnd_bShowFlickeringDownBtn = TRUE;
				mNpcwnd_bShowFlickeringTimer = 0;
			}
			mNpcwnd_bShowFlickeringTimer++;
		}
		else
			m_xNPCBtn[_BTN_ID_NPCSCRLDN].ShowGameBtn();

		m_xNPCBtn[_BTN_ID_NPCSCRLUP].ShowGameBtn();
	}
}

/***** Func13 ****************************************************************/
BOOL CNPCWnd::OnLButtonDown(POINT ptMouse)
{
	CScriptLine*	pScriptLine = NULL;
	CListNode <CScriptLine> *pNode;

	if ( m_xNPCScrlBar.OnLButtonDown(ptMouse) )
	{
		FLOAT	fScrlRate;

		fScrlRate	= m_xNPCScrlBar.GetScrlRate();
		m_nStartLine = (INT)((m_nMaxLine-1)*fScrlRate);

		return TRUE;
	}

	if ( m_xNPCBtn[_BTN_ID_NPCCLOSE].OnLButtonDown(ptMouse) )		
		return TRUE;

	if ( m_nStartLine > 0 )
	{
		if ( m_xNPCBtn[_BTN_ID_NPCSCRLUP].OnLButtonDown(ptMouse) )
		{
			return TRUE;
		}
	}

	if ( m_nStartLine < m_nMaxLine-1 )
	{
		if ( m_xNPCBtn[_BTN_ID_NPCSCRLDN].OnLButtonDown(ptMouse) )
		{
			return TRUE;
		}
	}

	for (pNode = ScriptList.GetHead(); pNode; pNode = pNode->GetNext())
	{
		pScriptLine = pNode->GetData();

		if (pScriptLine->m_btScriptType == SCRIPT_BUTTON)
		{
			pScriptLine->m_fIsSelected = FALSE;
			for (int nI=0; nI<5; nI++)
			{
				if (PtInRect(&pScriptLine->m_rcScriptRect[nI], ptMouse))
					pScriptLine->m_fIsSelected = TRUE;
			}
		}
	}

	return FALSE;
}

/***** Func14 ****************************************************************/
BOOL CNPCWnd::OnLButtonUp(POINT ptMouse)
{
	CScriptLine*			pScriptLine = NULL;
	CListNode<CScriptLine> 	*pNode;

	if ( m_xNPCBtn[_BTN_ID_NPCCLOSE].OnLButtonUp(ptMouse) && m_bCanClose )
	{
		return TRUE;
	}

	if ( m_nStartLine > 0 && mNpcwnd_bShowScroll == TRUE)
	{
		if ( m_xNPCBtn[_BTN_ID_NPCSCRLUP].OnLButtonUp(ptMouse) )
		{
			m_nStartLine--;

			if (m_nStartLine < 0)
			{
				m_nStartLine = 0;
			}
			NpcWndSetScriptsRectInit();

			return FALSE;
		}
	}

	if ( m_nStartLine < m_nMaxLine && mNpcwnd_bShowScroll == TRUE)
	{
		if ( m_xNPCBtn[_BTN_ID_NPCSCRLDN].OnLButtonUp(ptMouse) )
		{
			m_nStartLine++;

			if (m_nStartLine > m_nMaxLine)
			{
				m_nStartLine = m_nMaxLine;
			}
			NpcWndSetScriptsRectInit();

			return FALSE;
		}
	}

	if ( m_xNPCScrlBar.OnLButtonUp(ptMouse) )
	{
		return FALSE;
	}


	for (pNode = ScriptList.GetHead(); pNode; pNode = pNode->GetNext())
	{
		pScriptLine = pNode->GetData();

		if (pScriptLine->m_btScriptType == SCRIPT_BUTTON)
		{
			pScriptLine->m_fIsSelected = FALSE;
			for (int nI=0; nI<5; nI++)
			{
				if (PtInRect(&pScriptLine->m_rcScriptRect[nI], ptMouse))
					pScriptLine->m_fIsSelected = TRUE;
			}

			if (pScriptLine->m_fIsSelected == TRUE && timeGetTime()-m_dwLastNPCTick > 1000 )
			{
				if (pScriptLine->m_pszScriptCommand[0] == '@' && pScriptLine->m_pszScriptCommand[1] == '@' && pScriptLine->m_pszScriptCommand[2] == '*')
				{
					ZeroMemory(m_pszSaveCmd, MAX_PATH);
					strcpy(m_pszSaveCmd, pScriptLine->m_pszScriptCommand);

					if (strcmp(pScriptLine->m_pszScriptCommand, "@@*buildguildnow") == 0)
					{
						g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_NPCCHAT, _YESNO, g_xMsg.GetMsg(2000), TRUE, -1, -1, CM_MERCHANTDLGSELECT, TRUE);
					}
					else
					{
						if ( strstr(pScriptLine->m_pszScriptCommand, "enter_stgpasswd") != NULL || 
							 strstr(pScriptLine->m_pszScriptCommand, "Input_stgpasswd") != NULL ||
							 strstr(pScriptLine->m_pszScriptCommand, "Change_stgpasswd") != NULL ||
							 strstr(pScriptLine->m_pszScriptCommand, "confirm_passwd") != NULL )
						{
							CHAR szNum[5];
							INT nI=3;

							while ( pScriptLine->m_pszScriptCommand[nI] != '_' && nI<11 )
							{
								sprintf( &szNum[nI-3], "%c", pScriptLine->m_pszScriptCommand[nI]);
								nI++;
							}
							if ( nI >= 10 )
							{
								g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_NPCCHAT, _YESNO, pScriptLine->m_pszScriptText, TRUE, -1, -1, CM_MERCHANTDLGSELECT, TRUE, 10);
							}
							else
							{
								szNum[nI-3] = 0;
								g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_NPCCHAT, _YESNO, pScriptLine->m_pszScriptText, TRUE, -1, -1, CM_MERCHANTDLGSELECT, TRUE, atoi(szNum));
							}
						}
						else 
						{
							g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_NPCCHAT, _YESNO, pScriptLine->m_pszScriptText, TRUE, -1, -1, CM_MERCHANTDLGSELECT, TRUE);
						}
					}
				}
				else if (pScriptLine->m_pszScriptCommand[0] == '@' && pScriptLine->m_pszScriptCommand[1] == '@')
				{
					ZeroMemory(m_pszSaveCmd, MAX_PATH);
					strcpy(m_pszSaveCmd, pScriptLine->m_pszScriptCommand);

					if (strcmp(pScriptLine->m_pszScriptCommand, "@@buildguildnow") == 0)
					{
						g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_NPCCHAT, _YESNO, g_xMsg.GetMsg(2000), TRUE, -1, -1, CM_MERCHANTDLGSELECT);
					}
					else if (strcmp(pScriptLine->m_pszScriptCommand, "@@guildwar") == 0)
					{
						g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_NPCCHAT, _YESNO, pScriptLine->m_pszScriptText, TRUE, -1, -1, CM_MERCHANTDLGSELECT, FALSE);
					}
					else
					{
						g_xGameProc.m_xGameMsgBox.CreateMsgBox(&g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER], _WND_ID_NPCCHAT, _YESNO, pScriptLine->m_pszScriptText, TRUE, -1, -1, CM_MERCHANTDLGSELECT, FALSE, 50);
					}
				}
				else
				{
					g_xClientSocket.SendNPCMessage(CM_MERCHANTDLGSELECT,(DWORD)m_nNpcId, 0, pScriptLine->m_pszScriptCommand);
				}

				m_dwLastNPCTick = timeGetTime();
			}
		}

		pScriptLine->m_fIsSelected = FALSE;
	}

	return FALSE;
}

/***** Func15 ****************************************************************/
LRESULT CNPCWnd::OnMsgBoxReturn(WPARAM wParam, LPARAM lParam)
{
	SHORT	shMsgReturn;
	WORD	wPacket;

	shMsgReturn = LOBYTE(HIWORD(wParam));
	wPacket		= LOWORD(wParam);

	if ( shMsgReturn == _BTN_YES && wPacket == CM_MERCHANTDLGSELECT )
	{
		CHAR	pszSend[MAX_PATH];
		sprintf(pszSend, "%s\r%s", m_pszSaveCmd, (CHAR*)lParam);
		
		g_xClientSocket.SendNPCMessage(CM_MERCHANTDLGSELECT,(DWORD)m_nNpcId, 0, pszSend);
		ZeroMemory(m_pszSaveCmd, MAX_PATH);
	}

	g_xChatEditBox.SetLimitText(90);

	return 0L;
}

/***** Func16 ****************************************************************/
BOOL CNPCWnd::OnMouseMove(POINT ptMouse)
{
	CScriptLine*	pScriptLine = NULL;
 	CListNode<CScriptLine> 	*pNode;

	for( INT nCnt = 0; nCnt < _MAX_NPC_BTN; nCnt++ )
	{
		m_xNPCBtn[nCnt].OnMouseMove(ptMouse);
	}

	if ( m_xNPCScrlBar.OnMouseMove(ptMouse) )
	{
		FLOAT	fScrlRate;
		fScrlRate	= m_xNPCScrlBar.GetScrlRate();
		m_nStartLine = (INT)((m_nMaxLine-1)*fScrlRate);
		
		return TRUE;
	}

	for (pNode = ScriptList.GetHead(); pNode; pNode = pNode->GetNext())
	{
		pScriptLine = pNode->GetData();

		if (pScriptLine->m_btScriptType == SCRIPT_BUTTON)
		{
			pScriptLine->m_fIsFocused = FALSE;
			for (int nI=0; nI<5; nI++)
			{
				if (PtInRect(&pScriptLine->m_rcScriptRect[nI], ptMouse))
					pScriptLine->m_fIsFocused = TRUE;
			}
		}
	}

	return FALSE;
}

/***** Func17 ****************************************************************/
void CNPCWnd::ResetDialog()
{
	CScriptLine*	pScriptLine = NULL;
 	CListNode<CScriptLine> 	*pNode;
 	CListNode<CScriptLine> 	*pNodeTemp;

	for (pNode = ScriptList.GetHead(); pNode; )
	{
		pNodeTemp = pNode->GetNext();

		pScriptLine = ScriptList.RemoveNode(pNode);

		if (pScriptLine)
			delete pScriptLine;

		pNode = pNodeTemp;
	}

	m_nStartLine	= 0;
	m_nMaxLine		= mNpcwnd_nMaxShowLine;
}

/***** Func18 ****************************************************************/
VOID CNPCWnd::OnScrollDown()
{
//	if (m_nMaxLine > MAX_SHOW_LINE)
	if (mNpcwnd_bShowScroll == TRUE)
	{
		m_nStartLine--;

		if (m_nStartLine < 0)
		{
			m_nStartLine = 0;
		}
		NpcWndSetScriptsRectInit();
	}
}

/***** Func19 ****************************************************************/
VOID CNPCWnd::OnScrollUp()
{
//	if (m_nMaxLine > MAX_SHOW_LINE)
	if (mNpcwnd_bShowScroll == TRUE)
	{
		m_nStartLine++;

		if (m_nStartLine > m_nMaxLine-1)
		{
			m_nStartLine = m_nMaxLine;
		}
		NpcWndSetScriptsRectInit();
	}
}


/***** Func21 ****************************************************************/
VOID CNPCWnd::SetWndRectExtend(VOID)
{
//	m_rectExtended = m_rcWnd;
//	m_rcWnd.left = 0;
//	m_rcWnd.top = 0;
//	m_rcWnd.right = 800;
//	m_rcWnd.bottom = 560;
}

/***** Func22 ****************************************************************/
VOID CNPCWnd::SetWndRectReduce(VOID)
{
//	m_rcWnd = m_rectExtended;
}

/***** Func23 ****************************************************************/
VOID CNPCWnd::SetNpcEditBoxPos(VOID)
{
	// Edit Box 관련
//	m_rcEditBoxFrame.left = 247;
//	m_rcEditBoxFrame.top = 256;
//	m_rcEditBoxFrame.right = 467;
//	m_rcEditBoxFrame.bottom = 272;
//	MoveWindow(g_xChatEditBox.GetSafehWnd(), g_xMainWnd.m_rcWindow.left + m_rcWnd.left + m_rcEditBoxFrame.left, 
//		g_xMainWnd.m_rcWindow.top + m_rcWnd.top + m_rcEditBoxFrame.top, 
//		m_rcEditBoxFrame.right - m_rcEditBoxFrame.left, 
//		m_rcEditBoxFrame.bottom - m_rcEditBoxFrame.top, TRUE);
//	SetWindowText(g_xChatEditBox.GetSafehWnd(),NULL);
//	g_xChatEditBox.SetLimitText(30);
//	SetFocus(g_xChatEditBox.GetSafehWnd());
//	ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_SHOW);
}

/***** Func24 ****************************************************************/
VOID CNPCWnd::OnEnterKeyDown(VOID)
{
	CHAR	szTxt[MAX_PATH];
	ZeroMemory(szTxt,MAX_PATH);

/*	if(m_xMsgBox.IsActive())
	{
		SetWndRectReduce();
		GetWindowText(g_xChatEditBox.GetSafehWnd(),szTxt,MAX_PATH);
		if(szTxt[0]==NULL)
		{
			strncpy(szTxt,g_xChatEditBox.m_szInputMsg,strlen(g_xChatEditBox.m_szInputMsg));
		}
		// For Editbox to Chatting
		SetFocus(g_xMainWnd.GetSafehWnd());
		ShowWindow(g_xChatEditBox.GetSafehWnd(), SW_HIDE);
		g_xChatEditBox.SetLimitText(90);// 체팅창 Limit length 로 바꾸어 준다.
		MoveWindow(g_xChatEditBox.GetSafehWnd(), g_xMainWnd.m_rcWindow.left+_INPUT_EDITWND_XPOS, 
			g_xMainWnd.m_rcWindow.top+_INPUT_EDITWND_YPOS, _INPUT_EDITWND_WIDTH, _INPUT_EDITWND_HEIGHT, TRUE);
		switch(m_nNpcMsgState)
		{
		case 1:
		case 2:
			// 문파 생성
			// 문쟁 신청
			{
				CHAR szMsg[MAX_PATH*2];
				strcpy(szMsg,m_pClickedTxtBtn->Param);
				strcat(szMsg,"/\0");
				strcat(szMsg,szTxt);
				SendCommandToSrv(szMsg);
			break;
			}
		case 3:
		case 4:
			{
			// 성자금 찾기
			// 성자금 맞기기
			break;
			}
		}
		g_xChatEditBox.m_szInputMsg[0] = NULL;
		SetWindowText(g_xChatEditBox.GetSafehWnd(),NULL);
		m_xMsgBox.HideMessageBox(); 
	}								*/
}

/***** Func25 ****************************************************************/
BOOL CNPCWnd::OnMsgInputted(VOID)
{
/*	if(!m_xMsgBox.IsActive())
		return FALSE; 
	OnEnterKeyDown(); */
	return FALSE;
}

/***** Func26 ******* Lee Kyoung Soo / 2002.09.04  ***************************/
void
CNPCWnd::NpcWndCountLineNumInScript(char *pszScript)
{
	char *pszText = pszScript;
	char *pszPaser;
	int  nLineLen = 0;
	int	 nLen = strlen(pszScript);
	int	 nCheckCnt = 0;

	mNpcwnd_bHasImage = 0;
	mNpcwnd_nCharCount = 0;
	mNpcwnd_nLineCnt = 0;	
	mNpcwnd_nNumMiddleWindow = 0;
	mNpcwnd_bShowScroll = FALSE;
	
	while (pszText!=NULL && *pszText && (pszText - pszScript) < nLen)
	{
		if (pszPaser = NpcWndCheckText(pszText, &nCheckCnt))
		{
			nLineLen = pszPaser - pszText;

			switch (*pszPaser)
			{
				case '\\':
				{
					if (mNpcwnd_nCharCount == 0)
					{
						mNpcwnd_nLineCnt++;
						break;
					}
					if (mNpcwnd_nCharCount < 3)
					{
						mNpcwnd_nLineCnt++;
						break;
					}
					if (mNpcwnd_bHasImage == TRUE && mNpcwnd_nLineCnt < LINENUM_PICTUREHEIGHT)
					{
						int nLineCount = mNpcwnd_nCharCount / HALF_CHAR_INLINE;
						mNpcwnd_nLineCnt += nLineCount;
						if (nLineCount >= LINENUM_PICTUREHEIGHT)
						{
							mNpcwnd_nLineCnt = LINENUM_PICTUREHEIGHT;
							mNpcwnd_nCharCount -= LINENUM_PICTUREHEIGHT * HALF_CHAR_INLINE;
							nLineCount = mNpcwnd_nCharCount / MAX_CHAR_INLINE;
							mNpcwnd_nLineCnt += nLineCount;
							if (mNpcwnd_nCharCount % MAX_CHAR_INLINE != 0)
								mNpcwnd_nLineCnt++;
							mNpcwnd_nCharCount = 0;
							break;
						}
						if (mNpcwnd_nCharCount % HALF_CHAR_INLINE != 0)
							mNpcwnd_nLineCnt++;
						mNpcwnd_nCharCount = 0;
						break;
					}
					else
					{
						int nLineCount = mNpcwnd_nCharCount / MAX_CHAR_INLINE;
						mNpcwnd_nLineCnt += nLineCount;
						if (mNpcwnd_nCharCount % MAX_CHAR_INLINE != 0)
							mNpcwnd_nLineCnt++;
						mNpcwnd_nCharCount = 0;
						break;
					}
					break;
				}
				case '}':
				{
					break;
				}
			}
		}
		if (nLen == nCheckCnt)
			break;
		if (nLen < nCheckCnt)
			return;
	}

	if (mNpcwnd_nCharCount!=0)
	{
		if (mNpcwnd_bHasImage == TRUE && mNpcwnd_nLineCnt < LINENUM_PICTUREHEIGHT)
		{
			int nLineCount = mNpcwnd_nCharCount / HALF_CHAR_INLINE;
			mNpcwnd_nLineCnt += nLineCount;
			if (nLineCount >= LINENUM_PICTUREHEIGHT)
			{
				mNpcwnd_nLineCnt = LINENUM_PICTUREHEIGHT;
				mNpcwnd_nCharCount -= LINENUM_PICTUREHEIGHT * HALF_CHAR_INLINE;
				nLineCount = mNpcwnd_nCharCount / MAX_CHAR_INLINE;
				mNpcwnd_nLineCnt += nLineCount;
				if (mNpcwnd_nCharCount % MAX_CHAR_INLINE != 0)
					mNpcwnd_nLineCnt++;
				mNpcwnd_nCharCount = 0;
			}
			else if (mNpcwnd_nCharCount % HALF_CHAR_INLINE != 0)
			{
				mNpcwnd_nLineCnt++;
				mNpcwnd_nCharCount = 0;
			}
		}
		else
		{
			int nLineCount = mNpcwnd_nCharCount / MAX_CHAR_INLINE;
			mNpcwnd_nLineCnt += nLineCount;
			if (mNpcwnd_nCharCount % MAX_CHAR_INLINE != 0)
				mNpcwnd_nLineCnt++;
			mNpcwnd_nCharCount = 0;
		}
	}
	
	mNpcwnd_nNumMiddleWindow = mNpcwnd_nLineCnt - mNpcwnd_nSumOfTopBottomLine;

	if (mNpcwnd_nNumMiddleWindow < 0)
		mNpcwnd_nNumMiddleWindow = 0;


	if (mNpcwnd_nNumMiddleWindow > mNpcwnd_nMaxMiddleWndCount)
	{
		mNpcwnd_bShowScroll = TRUE;
		mNpcwnd_nNumMiddleWindow = mNpcwnd_nMaxMiddleWndCount;
	}

	if (mNpcwnd_bHasImage == TRUE && mNpcwnd_bShowScroll == TRUE)
		mNpcwnd_nMaxShowLine = MAX_SHOW_LINE;
	else 
		mNpcwnd_nMaxShowLine = MAX_SHOW_LINE_NO_IMG;


	int nHeight = mNpcwnd_rcMiddleWnd.bottom - mNpcwnd_rcMiddleWnd.top;

	SetRect(&mNpcwnd_rcMiddleWnd, mNpcwnd_rcMiddleWnd.left, mNpcwnd_rcTopWnd.bottom, 
		mNpcwnd_rcMiddleWnd.right, mNpcwnd_rcTopWnd.bottom + (mNpcwnd_nNumMiddleWindow == 0 ? 1 : mNpcwnd_nNumMiddleWindow) * mNpcwnd_nHeightMiddleWindow);

	SetRect(&mNpcwnd_rcBottomWnd, mNpcwnd_rcBottomWnd.left, mNpcwnd_rcMiddleWnd.bottom , mNpcwnd_rcBottomWnd.right, mNpcwnd_rcMiddleWnd.bottom + HEIGHT_BOTTOM_WINDOW);

	SetRect(&m_rcWnd, mNpcwnd_rcTopWnd.left, mNpcwnd_rcTopWnd.top,
						 mNpcwnd_rcBottomWnd.right, mNpcwnd_rcBottomWnd.bottom);

	m_xNPCBtn[_BTN_ID_NPCCLOSE].ChangeRect(m_rcWnd.left+351, m_rcWnd.bottom - 39);
	m_xNPCBtn[_BTN_ID_NPCSCRLUP].ChangeRect(m_rcWnd.left+183, m_rcWnd.bottom - 48);
	m_xNPCBtn[_BTN_ID_NPCSCRLDN].ChangeRect(m_rcWnd.left+183, m_rcWnd.bottom - 30);

	SetNPCWndTextr(g_xMainWnd.Get3DDevice());

}

/***** Func27 ******* Lee Kyoung Soo / 2002.09.04  ***************************/
char*
CNPCWnd::NpcWndCheckText(char *pszScript, int *nCnt)
{
	char	*pszText = NULL;

	pszScript = pszScript + *nCnt;

	if (pszScript)
	{
		int		nLen = strlen(pszScript);
		
		pszText = pszScript;

		while (*pszText)
		{
			*nCnt += 1;
			if (*pszText == '{')
			{
				char	szCheckImg[1024];
				int		nCount = 0;
				while(*pszText != '}')
				{
					szCheckImg[nCount++] = *pszText;
					pszText++;
					*nCnt += 1;
				}
				if (strncmp(szCheckImg, "{NPCIMG", 7) == 0)
				{
					mNpcwnd_bHasImage = FALSE;			// NPC 이미지 안 보여줌
					return pszText;
				}
				else
					return pszText;
				
			}
			else if (*pszText == '\\' || *pszText == '}')
			{
				return pszText;
			}
			else if (*pszText == '@')
			{
				while(*pszText != '>' && *pszText != NULL)
				{
					pszText++;
					*nCnt += 1;
				}
				mNpcwnd_nCharCount = mNpcwnd_nCharCount - 2;
				return pszText;
			}
			pszText++;
			mNpcwnd_nCharCount++;
		}
	}
	return pszText;
}

/***** Func28 ******* Lee Kyoung Soo / 2002.09.04  ***************************/
BOOL
CNPCWnd::NpcWndSetScriptsRect(CScriptLine* pScriptLine, RECT rcRect)
{
	for (int nI=0; nI<5; nI++)
	{
		if (pScriptLine->m_rcScriptRect[nI].left <= 0 && pScriptLine->m_rcScriptRect[nI].right <= 0
			&& pScriptLine->m_rcScriptRect[nI].top <= 0 && pScriptLine->m_rcScriptRect[nI].bottom <= 0)
		{
			SetRect(&pScriptLine->m_rcScriptRect[nI], rcRect.left, rcRect.top, rcRect.right, rcRect.bottom);
			break;
		}
	}
	return FALSE;
}

/***** Func28 ******* Lee Kyoung Soo / 2002.09.04  ***************************/
void
CNPCWnd::NpcWndScriptInit()
{
	CScriptLine*	pScriptLine = NULL;
 	CListNode<CScriptLine> 	*pNode;

	for (pNode = ScriptList.GetHead(); pNode; pNode = pNode->GetNext())
	{
		pScriptLine = pNode->GetData();
		pScriptLine->m_fIsFocused = FALSE;
		pScriptLine->m_fIsSelected = FALSE;
		for (int nI=0; nI < 5; nI++)
			SetRect(&pScriptLine->m_rcScriptRect[nI], 0, 0, 0, 0);
	}
}

/***** Func29 ******* Lee Kyoung Soo / 2002.09.11  ***************************/
void
CNPCWnd::NpcWndSetScriptsRectInit()
{
	CScriptLine*	pScriptLine = NULL;
 	CListNode<CScriptLine> 	*pNode;

	for (pNode = ScriptList.GetHead(); pNode; pNode = pNode->GetNext())
	{
		pScriptLine = pNode->GetData();
		for (int nI=0; nI < 5; nI++)
			SetRect(&pScriptLine->m_rcScriptRect[nI], 0, 0, 0, 0);
	}
}

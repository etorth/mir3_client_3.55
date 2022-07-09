/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"


CMagicWnd::CMagicWnd()
{
	Init();
}

CMagicWnd::~CMagicWnd()
{
	Destroy();
}

VOID CMagicWnd::Init()
{
	INT nCnt;

	CGameWnd::Init();

	for ( nCnt = 0; nCnt < _MAX_MAGIC_BTN; nCnt++ )
	{
		m_xMagicCloseBtn.Init();
	}

	for ( nCnt = 0; nCnt < _MAX_TYPE_MAGIC; nCnt++ )
	{
		m_xMagicTypeBtn[nCnt].Init();
	}

	for ( nCnt = 0; nCnt < _MAX_TYPE_MAGIC; nCnt++ )
	{
		m_xMyMagicList[nCnt].ClearAll();
	}
	m_bMyMagicCnt = 0;

	ZeroMemory(&m_bMagicKeyTable, _MAGIC_MAX_KEY);
	ZeroMemory(&m_rcMagicCell, sizeof(RECT)*_MAGIC_MAX_CELL);
	ZeroMemory(&m_rcSetKey, sizeof(RECT));

	ZeroMemory(&m_ptSetKey, sizeof(POINT) );
	
	m_pszMagicExplain = NULL;

	m_bTypeMagic = 0;

	m_nShowMagicNum = -1;

	m_nStartPos = 0;
	m_nMaxPos = 275;

	m_xWndScrBar.Init();

	SetMagicIconPos();

	for ( nCnt=0; nCnt < _MAX_TYPE_MAGIC; nCnt++ )
	{
		m_nSelectedMagic[nCnt] = -1;
	}

	m_bWantSetKey = FALSE;
}

BOOL CMagicWnd::DecryptMem()
{
	crypto_seed s = {(char) 0xF0, (char) 0x39, (char) 0xAB, (char) 0x8E, 0x9FDE1A93};
	crypto::setSeed( &s );
	FILE *fp = fopen( "Magic.exp", "rb" );
	if ( !fp )
		return false;

	int len = _filelength( _fileno( fp ) );
	m_pszMagicExplain = new char[ len ];
	if ( !m_pszMagicExplain )
	{
		fclose( fp );
		delete[] m_pszMagicExplain;
		return false;
	}

	fread( m_pszMagicExplain, 1, len, fp );
	fclose( fp );

	if ( !crypto::decrypt( (unsigned char *) m_pszMagicExplain, len ) )
	{
		delete[] m_pszMagicExplain;
		return false;
	}

	return true;
}


VOID CMagicWnd::Destroy()
{
	CGameWnd::Destroy();
//	SAFE_DELETEARR(m_pstMyMagic);
	SAFE_DELETEARR(m_pszMagicExplain);
	Init();
}

VOID CMagicWnd::CreateMagicWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend)
{
	Init();

	CreateGameWnd(nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight, bBlend);

	m_xMagicCloseBtn.CreateGameBtn(pxWndImage, 1221, 1222, nStartX+235, nStartY+305, g_xMsg.GetMsg(1052), _BTN_TYPE_FOCUS, 1221, TRUE);

	m_xMagicTypeBtn[0].CreateGameBtn(pxWndImage, 720, 720, nStartX+8, nStartY+ 10, g_xMsg.GetMsg(5050));
	m_xMagicTypeBtn[1].CreateGameBtn(pxWndImage, 722, 722, nStartX+41, nStartY+ 10, g_xMsg.GetMsg(5051));
	m_xMagicTypeBtn[2].CreateGameBtn(pxWndImage, 724, 724, nStartX+74, nStartY+ 10, g_xMsg.GetMsg(5052));
	m_xMagicTypeBtn[3].CreateGameBtn(pxWndImage, 726, 726, nStartX+107, nStartY+10, g_xMsg.GetMsg(5053));
	m_xMagicTypeBtn[4].CreateGameBtn(pxWndImage, 728, 728, nStartX+140, nStartY+10, g_xMsg.GetMsg(5054));
	m_xMagicTypeBtn[5].CreateGameBtn(pxWndImage, 730, 730, nStartX+173, nStartY+10, g_xMsg.GetMsg(5055));
	m_xMagicTypeBtn[6].CreateGameBtn(pxWndImage, 732, 732, nStartX+206, nStartY+10, g_xMsg.GetMsg(5056));
	m_xMagicTypeBtn[7].CreateGameBtn(pxWndImage, 734, 734, nStartX+239, nStartY+10, g_xMsg.GetMsg(5057));

	// 마법창초기화.
	SetRect(&m_rcMagicCell[0],  55,  27,  94,  66);
	SetRect(&m_rcMagicCell[1],  55,  73,  94, 112);
	SetRect(&m_rcMagicCell[2],  55, 119,  94, 158);
	SetRect(&m_rcMagicCell[3],  55, 165,  94, 204);
	SetRect(&m_rcMagicCell[4],  55, 211,  94, 250);
	SetRect(&m_rcMagicCell[5],  55, 257,  94, 296);

	m_xWndScrBar.CreateScrlBar(pxWndImage, 1672, 8, 12, 280, 14);

	DecryptMem();
}

VOID CMagicWnd::OnScrollDown()
{
	if ( m_nStartPos > 0 )
	{
		m_nStartPos-= 30;

		if ( m_nStartPos < 0 )
			m_nStartPos = 0;
	}
}


VOID CMagicWnd::OnScrollUp()
{
	if ( m_nStartPos < m_nMaxPos)
	{
		m_nStartPos+= 30;

		if ( m_nStartPos > 275 )
			m_nStartPos = 275;
	}
}

VOID CMagicWnd::ShowMagicWnd()
{
	INT nCnt;
	RECT rcKey;

	ShowGameWnd();

	if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(711+m_bTypeMagic))
	{
		RECT rcImg = {0, m_nStartPos, g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, m_nStartPos+331};
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+18, m_rcWnd.top+63-m_nStartPos, &rcImg, (WORD*)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
	}

	m_xWndScrBar.ShowScrlBar(m_rcWnd.left+337, m_rcWnd.top+84, m_nStartPos, m_nMaxPos);

	ShowCharSetMagicWnd();

	m_xMagicCloseBtn.ChangeRect(m_rcWnd.left+313, m_rcWnd.top+418);

	m_xMagicCloseBtn.ShowGameBtn();

 	m_xMagicTypeBtn[0].ChangeRect(m_rcWnd.left+46, m_rcWnd.top+30);
	m_xMagicTypeBtn[1].ChangeRect(m_rcWnd.left+80, m_rcWnd.top+30);
	m_xMagicTypeBtn[2].ChangeRect(m_rcWnd.left+114, m_rcWnd.top+30);
	m_xMagicTypeBtn[3].ChangeRect(m_rcWnd.left+148, m_rcWnd.top+30);
	m_xMagicTypeBtn[4].ChangeRect(m_rcWnd.left+182, m_rcWnd.top+30);
	m_xMagicTypeBtn[5].ChangeRect(m_rcWnd.left+216, m_rcWnd.top+30);
	m_xMagicTypeBtn[6].ChangeRect(m_rcWnd.left+250, m_rcWnd.top+30);
	m_xMagicTypeBtn[7].ChangeRect(m_rcWnd.left+284, m_rcWnd.top+30);

	for ( nCnt = _MAX_TYPE_MAGIC-1; nCnt >= 0; nCnt-- )
	{
		m_xMagicTypeBtn[nCnt].ShowGameBtn();

		if ( nCnt != m_bTypeMagic)
			continue;

		INT nSelectedTab = 721 + m_bTypeMagic*2;

		if (g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(nSelectedTab))
		{
			g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+46 + m_bTypeMagic * 34, m_rcWnd.top+30, g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
											g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
											(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage);
		}
	}

	if ( m_bWantSetKey )
	{
		ShowSetKeyWnd();
	}

	
//	RECT rcSelectTab = {m_rcWnd.left + m_bTypeMagic*34 + 12, m_rcWnd.top + 12 , m_rcWnd.left + m_bTypeMagic*34 + 38, m_rcWnd.top + 36};

//	g_xMainWnd.DrawWithGDI(&rcSelectTab, NULL, RGB(200, 200, 0), 1);


	ShowMagicTxt(m_nShowMagicNum);
}



/******************************************************************************************************************

	캐릭터 마법창관련.

*******************************************************************************************************************/
VOID CMagicWnd::ShowCharSetMagicWnd()
{
	INT  nLine, nCnt, nStartX, nStartY, nMagicImgIdx;
	CHAR szLevel[MAX_PATH];
	RECT rcText, rcAdd;
	BYTE bKey;

	LPCLIENTMAGICRCD pstMagicRCD = NULL;
	CListNode < CLIENTMAGICRCD > *pNode;

	for ( pNode = m_xMyMagicList[m_bTypeMagic].GetHead(), nCnt = 0, nLine = 0; pNode; pNode = pNode->GetNext(), nCnt++ )
	{
		// 현재 화면상에 보여줄 부분까지 만들어준다.
		if ( nCnt >= m_nStartLineNum[m_bTypeMagic] )
		{
			pstMagicRCD = pNode->GetData();

			if ( pstMagicRCD )
			{
				nStartX = m_rcWnd.left+m_rcMagicCell[nLine].left;
				nStartY = m_rcWnd.top +m_rcMagicCell[nLine].top;

				for (INT nI=0; nI<_MAX_MAGICSLOT; nI++)
				{
					if (m_xMagicIconPos[m_bTypeMagic][nI].nMagicID == pstMagicRCD->stStdMagic.wMagicID)
					{
						nStartX = m_rcWnd.left+m_xMagicIconPos[m_bTypeMagic][nI].nPosX;
						nStartY = m_rcWnd.top+m_xMagicIconPos[m_bTypeMagic][nI].nPosY - m_nStartPos;
						break;
					}
				}

				if ( nI == m_nSelectedMagic[m_bTypeMagic] )
				{
					RECT rc;
					SetRect(&rc, nStartX-1, nStartY-1, nStartX+35, nStartY+35);

					if ( rc.top > m_rcWnd.top + 62 && rc.top < m_rcWnd.top + 352 )
						g_xMainWnd.DrawWithGDI(&rc, NULL, RGB(200, 200, 0), 1);

					if ( pstMagicRCD )
					{
						sprintf(szLevel, "%s", pstMagicRCD->stStdMagic.szMagicName);
						SetRect(&rcText, m_rcWnd.left+20, m_rcWnd.top+418, m_rcWnd.left+100, m_rcWnd.top+433);
						g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szLevel);

						if ( pstMagicRCD->bLevel < 5 )
						{
							sprintf(szLevel, "Level : %d", pstMagicRCD->bLevel);
							SetRect(&rcText, m_rcWnd.left+20, m_rcWnd.top+433, m_rcWnd.left+100, m_rcWnd.top+448);
							g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szLevel);
							sprintf(szLevel, "Exp : %d/%d", pstMagicRCD->nCurrTrain, pstMagicRCD->stStdMagic.nTrain[pstMagicRCD->bLevel]);
							SetRect(&rcText, m_rcWnd.left+100, m_rcWnd.top+433, m_rcWnd.left+280, m_rcWnd.top+448);
							g_xMainWnd.PutsHan(NULL, rcText.left, rcText.top, RGB(250, 250, 250), RGB(0, 0, 0), szLevel);
						}
						else if ( pstMagicRCD->bLevel == 10 )
						{
						}
						else
						{
							sprintf(szLevel, "Level : Max");
							SetRect(&rcText, m_rcWnd.left+30, m_rcWnd.top+433, m_rcWnd.left+110, m_rcWnd.top+448);
							g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 250), RGB(0, 0, 0), szLevel);
						}
					}
				}

				if ( pstMagicRCD->bLevel == 10 )
				{
					nMagicImgIdx = 1000 + m_bTypeMagic;
				}
				else
				{
					nMagicImgIdx = (pstMagicRCD->stStdMagic.wMagicID-1) * 2;
				}

				if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].NewSetIndex(nMagicImgIdx) )
				{
//					if ( nStartY < 64 )
					if ( nStartY - m_rcWnd.top < 64 )
					{
						RECT rcImg = {0, 64-(nStartY - m_rcWnd.top), g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_lpstNewCurrWilImageInfo->shWidth, 
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_lpstNewCurrWilImageInfo->shHeight};
						g_xMainWnd.DrawWithImageForComp(nStartX, nStartY, &rcImg, (WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_pbCurrImage));
					}
					else if ( nStartY - m_rcWnd.top > 355 )
					{
						RECT rcImg = {0, 0, g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_lpstNewCurrWilImageInfo->shWidth, 
							g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_lpstNewCurrWilImageInfo->shHeight - ((nStartY - m_rcWnd.top) - 355)};
						g_xMainWnd.DrawWithImageForComp(nStartX, nStartY, &rcImg, (WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_pbCurrImage));
					}
					else
					{
						g_xMainWnd.DrawWithImageForComp(
														nStartX, 
														nStartY, 
														g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_lpstNewCurrWilImageInfo->shWidth, 
														g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_lpstNewCurrWilImageInfo->shHeight,
														(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_pbCurrImage));
					}

				}
/*
				if ( pstMagicRCD->bUseKey != 0 )
				{
					if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].NewSetIndex(nMagicImgIdx) )
					{
						if ( nStartY - m_rcWnd.top < 64 )
						{
							RECT rcImg = {0, 64-(nStartY - m_rcWnd.top), g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_lpstNewCurrWilImageInfo->shWidth, 
								g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_lpstNewCurrWilImageInfo->shHeight};
							g_xMainWnd.DrawWithImageForComp(nStartX, nStartY, &rcImg, (WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_pbCurrImage));
						}
						else if ( nStartY - m_rcWnd.top > 355 )
						{
							RECT rcImg = {0, 0, g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_lpstNewCurrWilImageInfo->shWidth, 
								g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_lpstNewCurrWilImageInfo->shHeight - ((nStartY - m_rcWnd.top) - 355)};
							g_xMainWnd.DrawWithImageForComp(nStartX, nStartY, &rcImg, (WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_pbCurrImage));
						}
						else
						{
							g_xMainWnd.DrawWithImageForComp(
															nStartX, 
															nStartY, 
															g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_lpstNewCurrWilImageInfo->shWidth, 
															g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_lpstNewCurrWilImageInfo->shHeight,
															(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_pbCurrImage));
						}
					}

					INT nAtoI = atoi((char*)&pstMagicRCD->bUseKey);
					if ( nAtoI < 10 && nAtoI > 0 )
					{
						bKey = (BYTE)nAtoI;
					}
					else
					{
						bKey = (BYTE)(pstMagicRCD->bUseKey - 55);
					}

					if ( m_pxWndImage->NewSetIndex(1659+bKey) )
					{
						if ( nStartY - m_rcWnd.top < 64 )
						{
							RECT rcImg = {0, 64-(nStartY - m_rcWnd.top), m_pxWndImage->m_lpstNewCurrWilImageInfo->shWidth, 
								m_pxWndImage->m_lpstNewCurrWilImageInfo->shHeight};
							g_xMainWnd.DrawWithImageForComp(nStartX, nStartY, &rcImg, (WORD*)(m_pxWndImage->m_pbCurrImage));
						}
						else if ( nStartY - m_rcWnd.top > 355 )
						{
							RECT rcImg = {0, 0, m_pxWndImage->m_lpstNewCurrWilImageInfo->shWidth, 
								m_pxWndImage->m_lpstNewCurrWilImageInfo->shHeight - ((nStartY - m_rcWnd.top) - 355)};
							g_xMainWnd.DrawWithImageForComp(nStartX, nStartY, &rcImg, (WORD*)(m_pxWndImage->m_pbCurrImage));
						}
						else
						{
							g_xMainWnd.DrawWithImageForComp(
															nStartX, 
															nStartY, 
															m_pxWndImage->m_lpstNewCurrWilImageInfo->shWidth, 
															m_pxWndImage->m_lpstNewCurrWilImageInfo->shHeight,
															(WORD*)(m_pxWndImage->m_pbCurrImage));
						}
					}
				}
*/
				if ( pstMagicRCD->bLevel != 10 )
				{
					sprintf(szLevel, "%d", pstMagicRCD->bLevel);

					SetRect(&rcText, nStartX+34, nStartY+33, nStartX+49, nStartY+48);
					if ( rcText.top - m_rcWnd.top > 56 && rcText.top - m_rcWnd.top < 385 )
					{
						g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 250, 100), RGB(0, 0, 0), szLevel, g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 8, 0, FW_NORMAL));
					}
				}
			}

			nLine++;

			if ( nLine >= _MAGIC_MAX_CELL )
			{
				break;
			}
		}
	}
}


BYTE CMagicWnd::GetMagicType(INT nMagicID)
{
	// 0(화), 1(빙), 2(뢰), 3(풍), 4(신성), 5(암흑), 6(환영), 7(무)
	BYTE bRet = 7;

	switch ( nMagicID )
	{
		case 1: case 5: case 9: case 23: case 22: case 47: case 113:
		{
			bRet = 0;		// 화  ->화염장, 금강화염장, 염사장, 폭열파, 지염술. 폭열파업, 집중화염장, 만천화우
			break;
		}
		case 39: case 40: case 53: case 33: case 110:
		{
			bRet = 1;		// 빙  ->빙월장, 빙월진천장, 빙사장, 빙설풍, 빙렬파
			break;
		}
		case 41: case 11: case 10: case 24: case 63: case 64: case 66: case 111: case 133: case 134:
		{
			bRet = 2;		// 뢰  ->비격장, 강격, 뢰인장, 뢰설화, 뢰벽, 뢰설화업, 비격트랩, 뢰화난무, 천뢰, 운중뢰격
			break;
		}
		case 67: case 8: case 31: case 72: case 73: case 74: case 114: case 145:
		{
			bRet = 3;		// 풍  ->장풍, 화염풍, 주술의막, 허리케인, 풍진참, 격풍, 고급주술의막
			break;
		}
		case 2: case 29: case 77: case 37: case 38: case 120: case 122: case 129: case 136:
		{
			bRet = 4;		// 신성->회복, 대회복, 소생술, 월영옥, 월영파, 정화술, 선천기공, 양생술
			break;
		}
		case  6: case 13: case 18: case 19: case 14: case 15: case 16:  case 48:  case 78:
		case 85: case 86: case 87: case 88: case 89: case 90: case 91: case 92: case 93:
		case 94: case 95: case 96: case 97: case 98: case 99: case 100: case 101: case 121: case 124: case 135: case 147: case 148: case 149:
		{
			bRet = 5;		// 암흑->암연, 폭살계, 은신술, 대은신술, 항마, 대지, 결계, 대지소환술, 둔갑술, 항마(화, 빙, 뢰, 풍), 강마진법(화, 빙, 뢰, 풍), , 맹호강세(공업, 화, 빙, 뢰, 풍, 방어, 마법, 공격), 기환술, 멸살계, 대암연술, 고급대지원호, 고급은신술, 고급월영파
			break;
		}
		case 17: case 30: case 20: case 21: case 32: case 105: case 104: case 112: case 123: case 127: case 137: case 146:
		{
			bRet = 6;		// 환영->백골소환, 신수, 뢰혼격, 아공행법, 사자윤회, 최종소환, 진백골소환, 지역아공, 역혈마공, 전이술, 허상분신, 분열혼, 고급역혈마공
			break;
		}
		case  4:  case 3: case 25: case 27: case 26: case 7: case 12: case 34: case 35: case 36: case 102: case 103: case 106: case 109: case 125: case 126: case 128: case 132: case 131: case 130: case 138: case 139: case 150: case 141: case 142: case 143: case 144:
		{
			bRet = 7;		// 무  ->일광, 외수, 반월, 무태보, 염화결, 예도, 어검, 연월참, 맹룡승천세, 무상각, 철포삼, 회선참, 광마결, 파황보, 격산타우, 반탄강기, 금강부동, 운기요상, 쾌도난마, 태산압정, 발사체, 직선계, 폭발형, 지속계, 고급연월참, 고급맹룡승천세, 고급파황보
			break;
		}
		default:
		{
			break;
		}
	}

	return bRet;
}


VOID CMagicWnd::SetMyMagic(INT nMagicCnt, CHAR* pszMagic)
{
	INT					nCnt;
	CHAR*				pszNextMagic;
	LPCLIENTMAGICRCD	pstMagicRCD;

	for ( nCnt = 0; nCnt < _MAX_TYPE_MAGIC; nCnt++ )
	{
		m_xMyMagicList[nCnt].ClearAll();
	}

	m_bMyMagicCnt = (BYTE)nMagicCnt;

	for ( INT nLoop = 0; nLoop < m_bMyMagicCnt; nLoop++ )
	{
		if ( pszNextMagic = strchr(pszMagic, '/') )
		{
			*pszNextMagic = '\0';

			pstMagicRCD = NULL;
			pstMagicRCD = new CLIENTMAGICRCD;
			ZeroMemory(pstMagicRCD, sizeof(CLIENTMAGICRCD));

			fnDecode6BitBuf(pszMagic, (char*)pstMagicRCD, sizeof(CLIENTMAGICRCD));

			// 키설정.
			BYTE bKey;
			INT nAtoI = atoi((char*)(&pstMagicRCD->bUseKey));
			if ( nAtoI < 10 && nAtoI > 0 )
			{
				bKey = (BYTE)nAtoI;
			}
			else
			{
				bKey = (BYTE)(pstMagicRCD->bUseKey- 55);
			}
			if ( bKey > 0 && bKey <= _MAGIC_MAX_KEY )
			{
				m_bMagicKeyTable[bKey-1] = (BYTE)pstMagicRCD->stStdMagic.wMagicID;
			}

			// 리스트삽입.
			m_xMyMagicList[GetMagicType(pstMagicRCD->stStdMagic.wMagicID)].Insert(pstMagicRCD);

			pszMagic = pszNextMagic + 1;
		}
	}

	for ( nCnt = 0; nCnt < _MAX_TYPE_MAGIC; nCnt++ )
	{
		if ( m_xMyMagicList[nCnt].GetCount() != 0 )
		{
			m_bTypeMagic = nCnt;
			break;
		}
	}

	SetMagicTypeBtn();
}


VOID CMagicWnd::DelMyMagic(INT nMagicID)
{
	BYTE bTypeMagic  = GetMagicType(nMagicID);
	LPCLIENTMAGICRCD pstMagicRCD = NULL;
	CListNode < CLIENTMAGICRCD > *pNode;

	for ( pNode = m_xMyMagicList[bTypeMagic].GetHead(); pNode; pNode = pNode->GetNext() )
	{
		pstMagicRCD = pNode->GetData();

		if ( pstMagicRCD )
		{
			if ( pstMagicRCD->stStdMagic.wMagicID == nMagicID )
			{
				m_xMyMagicList[bTypeMagic].RemoveNode(pNode);
				SAFE_DELETE(pstMagicRCD);

				break;
			}
		}
	}

	SetMagicTypeBtn();

	// 현재 선택되있는 타입체크.
	if ( m_xMyMagicList[m_bTypeMagic].GetCount() == 0 )
	{
		for ( INT nCnt = 0; nCnt < _MAX_TYPE_MAGIC; nCnt++ )
		{
			if ( m_xMyMagicList[nCnt].GetCount() != 0 )
			{
				m_bTypeMagic = nCnt;
				break;
			}
		}
		m_xMagicTypeBtn[m_bTypeMagic].ResetGameBtn(720+(m_bTypeMagic*2), 720+(m_bTypeMagic*2), 720+(m_bTypeMagic*2));
	}
}


VOID CMagicWnd::AddNewMagic(CHAR* pszMagic)
{
	m_bMyMagicCnt++;

	LPCLIENTMAGICRCD pstMagicRCD = NULL;
	pstMagicRCD = new CLIENTMAGICRCD;

	fnDecode6BitBuf(pszMagic, (char*)pstMagicRCD, sizeof(CLIENTMAGICRCD));

	BYTE bKey = (BYTE)atoi((char*)&(pstMagicRCD->bUseKey));
	if ( bKey > 0 && bKey <= _MAGIC_MAX_KEY )
	{
		m_bMagicKeyTable[bKey-1] = (BYTE)pstMagicRCD->stStdMagic.wMagicID;
	}

	// 리스트삽입.
	m_xMyMagicList[GetMagicType(pstMagicRCD->stStdMagic.wMagicID)].Insert(pstMagicRCD);

	SetMagicTypeBtn();

	// 현재 선택되있는 타입체크.
	if ( m_xMyMagicList[m_bTypeMagic].GetCount() == 0 )
	{
		for ( INT nCnt = 0; nCnt < _MAX_TYPE_MAGIC; nCnt++ )
		{
			if ( m_xMyMagicList[nCnt].GetCount() != 0 )
			{
				m_bTypeMagic = nCnt;
				break;
			}
		}
		m_xMagicTypeBtn[m_bTypeMagic].ResetGameBtn(720+(m_bTypeMagic*2), 720+(m_bTypeMagic*2), 720+(m_bTypeMagic*2));
	}
}


VOID CMagicWnd::SetMagicTypeBtn()
{
	INT  nListCnt;
	LPCLIENTMAGICRCD pstMagicRCD = NULL;
	CListNode < CLIENTMAGICRCD > *pNode;

	for ( nListCnt = 0; nListCnt < _MAX_TYPE_MAGIC; nListCnt++ )
	{
		// 무공이 있다는 형태로 표시.
		if ( m_xMyMagicList[nListCnt].GetCount() != 0 )
		{
			m_xMagicTypeBtn[nListCnt].ResetGameBtn(720+(nListCnt*2), 720+(nListCnt*2), 720+(nListCnt*2));
		}
		else
		{
			m_xMagicTypeBtn[nListCnt].ResetGameBtn(720+(nListCnt*2), 720+(nListCnt*2));
		}

	}

	// 현재 선택되있는 타입체크.
	if ( m_xMyMagicList[m_bTypeMagic].GetCount() != 0 )
	{
		m_xMagicTypeBtn[m_bTypeMagic].ResetGameBtn(720+(m_bTypeMagic*2), 720+(m_bTypeMagic*2), 720+(m_bTypeMagic*2));
	}
}


VOID CMagicWnd::MagicExpUp(INT nMagicID, INT nCurrTrain, BYTE bLevel)
{
	LPCLIENTMAGICRCD pstMagicRCD = FindMagicRCD(nMagicID);

	if ( pstMagicRCD )
	{
		pstMagicRCD->nCurrTrain	= nCurrTrain;
		pstMagicRCD->bLevel		= bLevel;
	}
}



LPCLIENTMAGICRCD CMagicWnd::FindMagicRCD(INT nMagicID)
{
	BYTE bTypeMagic  = GetMagicType(nMagicID);
	LPCLIENTMAGICRCD pstMagicRCD = NULL;
	CListNode < CLIENTMAGICRCD > *pNode;

	for ( pNode = m_xMyMagicList[bTypeMagic].GetHead(); pNode; pNode = pNode->GetNext() )
	{
		pstMagicRCD = pNode->GetData();

		if ( pstMagicRCD )
		{
			if ( pstMagicRCD->stStdMagic.wMagicID == nMagicID )
			{
				return pstMagicRCD;
			}
		}
	}

	return NULL;
}



/******************************************************************************************************************

	함수명 : CMagicWnd::SetMagicKey()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : POINT ptMouse
	         BYTE bKey
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CMagicWnd::SetMagicKey(POINT ptMouse, BYTE bKey)
{
	RECT rc, rcMagic;
	INT  nCnt, nLine, nAtoI, nListCnt;
	BYTE bKeyNum;
	LPCLIENTMAGICRCD pstMagicRCD = NULL;
	CListNode < CLIENTMAGICRCD > *pNode;

	for ( nCnt = 0; nCnt < _MAX_MAGICSLOT; nCnt++ )
	{
		rc.left  = m_rcWnd.left + m_xMagicIconPos[m_bTypeMagic][nCnt].nPosX;
		rc.top	 = m_rcWnd.top  + m_xMagicIconPos[m_bTypeMagic][nCnt].nPosY - m_nStartPos;
		rc.right = m_rcWnd.left + m_xMagicIconPos[m_bTypeMagic][nCnt].nPosX + 40;
		rc.bottom= m_rcWnd.top	+ m_xMagicIconPos[m_bTypeMagic][nCnt].nPosY + 40 - m_nStartPos;

		if ( PtInRect(&rc, ptMouse) )
		{
/*			// 현재 눌려져 있는 키가 쓰인가 체크.
			for ( nListCnt = 0; nListCnt < _MAX_TYPE_MAGIC; nListCnt++ )
			{
				for ( pNode = m_xMyMagicList[nListCnt].GetHead(); pNode; pNode = pNode->GetNext() )
				{
					pstMagicRCD = pNode->GetData();

					if ( pstMagicRCD )
					{
						nAtoI = atoi((char*)&(pstMagicRCD->bUseKey));

						if ( nAtoI < 10 && nAtoI > 0 )
						{
							bKeyNum = (BYTE)nAtoI;
						}
						else
						{
							bKeyNum = (BYTE)(pstMagicRCD->bUseKey- 55);
						}

						if ( pstMagicRCD->bUseKey == bKey )
						{
							pstMagicRCD->bUseKey = 0;

							if ( bKeyNum > 0 && bKeyNum <= _MAGIC_MAX_KEY )
							{
								m_bMagicKeyTable[bKeyNum-1] = 0;
							}

							g_xClientSocket.SendMagicKeyChange(pstMagicRCD->bUseKey, pstMagicRCD->stStdMagic.wMagicID);
							g_xGameProc.m_xInterface.m_xUtilWnd.CheckKey(bKey);
						}
					}
				}
			}
*/
			for ( pNode = m_xMyMagicList[m_bTypeMagic].GetHead(); pNode; pNode = pNode->GetNext() )
			{
				pstMagicRCD = pNode->GetData();

				if ( pstMagicRCD )
				{
//					if ( pstMagicRCD->bUseKey != bKey )
//					{
						// 새로운키 적용.
						if ( pstMagicRCD->stStdMagic.wMagicID == m_xMagicIconPos[m_bTypeMagic][nCnt].nMagicID )
						{
							nAtoI = atoi((char*)&bKey);

							if ( nAtoI < 10 && nAtoI > 0 )
							{
								bKeyNum = (BYTE)nAtoI;
							}
							else
							{
								bKeyNum = (BYTE)(bKey - 55);
							}

							g_xGameProc.m_xInterface.m_xMagicShortcutWnd.SetMagicIcon(pstMagicRCD->stStdMagic.wMagicID, bKeyNum);
							return TRUE;

/*							nAtoI = atoi((char*)&(pstMagicRCD->bUseKey));
							if ( nAtoI < 10 && nAtoI > 0 )
							{
								bKeyNum = (BYTE)nAtoI;
							}
							else
							{
								bKeyNum = (BYTE)(pstMagicRCD->bUseKey- 55);
							}
							if ( bKeyNum > 0 && bKeyNum <= _MAGIC_MAX_KEY )
							{
								m_bMagicKeyTable[bKeyNum-1] = 0;
							}

							pstMagicRCD->bUseKey = bKey;

							nAtoI = atoi((char*)&bKey);

							if ( nAtoI < 10  && nAtoI > 0 )
							{
								bKeyNum = (BYTE)nAtoI;
							}
							else
							{
								bKeyNum = (BYTE)(bKey - 55);
							}

							if ( bKeyNum > 0 && bKeyNum <= _MAGIC_MAX_KEY )
							{
								m_bMagicKeyTable[bKeyNum-1] = (BYTE)pstMagicRCD->stStdMagic.wMagicID;
							}

							g_xClientSocket.SendMagicKeyChange(pstMagicRCD->bUseKey, pstMagicRCD->stStdMagic.wMagicID);
							g_xGameProc.m_xInterface.m_xUtilWnd.CheckKey(bKey);

							return TRUE;
*/

						}
//					}
				}
			}
		}
	}

	return FALSE;
}




BOOL CMagicWnd::SetMagicKeybyMouseBtn(BYTE bKey)
{
	RECT rc, rcMagic;
	INT  nCnt, nLine, nAtoI, nListCnt;
	BYTE bKeyNum;
	LPCLIENTMAGICRCD pstMagicRCD = NULL;
	CListNode < CLIENTMAGICRCD > *pNode;

	for ( nListCnt = 0; nListCnt < _MAX_TYPE_MAGIC; nListCnt++ )
	{
		for ( pNode = m_xMyMagicList[nListCnt].GetHead(); pNode; pNode = pNode->GetNext() )
		{
			pstMagicRCD = pNode->GetData();

			if ( pstMagicRCD )
			{
				nAtoI = atoi((char*)&(pstMagicRCD->bUseKey));

				if ( nAtoI < 10 && nAtoI > 0 )
				{
					bKeyNum = (BYTE)nAtoI;
				}
				else
				{
					bKeyNum = (BYTE)(pstMagicRCD->bUseKey- 55);
				}

				if ( pstMagicRCD->bUseKey == bKey )
				{
					pstMagicRCD->bUseKey = 0;

					if ( bKeyNum > 0 && bKeyNum <= _MAGIC_MAX_KEY )
					{
						m_bMagicKeyTable[bKeyNum-1] = 0;
					}

					g_xClientSocket.SendMagicKeyChange(pstMagicRCD->bUseKey, pstMagicRCD->stStdMagic.wMagicID);
					g_xGameProc.m_xInterface.m_xUtilWnd.CheckKey(bKey);
				}
			}
		}
	}

	BOOL bFind = FALSE;
	for ( pNode = m_xMyMagicList[m_bTypeMagic].GetHead(); bFind == FALSE && pNode; pNode = pNode->GetNext() )
	{
		pstMagicRCD = pNode->GetData();
		if ( m_xMagicIconPos[m_bTypeMagic][m_nSelectedMagic[m_bTypeMagic]].nMagicID == pstMagicRCD->stStdMagic.wMagicID )
			bFind = TRUE;
	}

	if ( pstMagicRCD )
	{
		if ( pstMagicRCD->bUseKey != bKey )
		{
			// 새로운키 적용.
			nAtoI = atoi((char*)&(pstMagicRCD->bUseKey));
			if ( nAtoI < 10 && nAtoI > 0 )
			{
				bKeyNum = (BYTE)nAtoI;
			}
			else
			{
				bKeyNum = (BYTE)(pstMagicRCD->bUseKey- 55);
			}
			if ( bKeyNum > 0 && bKeyNum <= _MAGIC_MAX_KEY )
			{
				m_bMagicKeyTable[bKeyNum-1] = 0;
			}

			pstMagicRCD->bUseKey = bKey;

			nAtoI = atoi((char*)&bKey);

			if ( nAtoI < 10  && nAtoI > 0 )
			{
				bKeyNum = (BYTE)nAtoI;
			}
			else
			{
				bKeyNum = (BYTE)(bKey - 55);
			}

			if ( bKeyNum > 0 && bKeyNum <= _MAGIC_MAX_KEY )
			{
				m_bMagicKeyTable[bKeyNum-1] = (BYTE)pstMagicRCD->stStdMagic.wMagicID;
			}

			g_xClientSocket.SendMagicKeyChange(pstMagicRCD->bUseKey, pstMagicRCD->stStdMagic.wMagicID);
			g_xGameProc.m_xInterface.m_xUtilWnd.CheckKey(bKey);
		}
	}

	return FALSE;
}


/******************************************************************************************************************

	함수명 : CMagicWnd::GetMagicByKey()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : BYTE bKey
	출력   : LPCLIENTMAGICRCD 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
LPCLIENTMAGICRCD CMagicWnd::GetMagicByKey(BYTE bKey)
{
	INT  nCnt, nLine, nAtoI, nListCnt;
	BYTE bKeyNum;
	LPCLIENTMAGICRCD pstMagicRCD = NULL;
	CListNode < CLIENTMAGICRCD > *pNode;

	for ( nListCnt = 0; nListCnt < _MAX_TYPE_MAGIC; nListCnt++ )
	{
		for ( pNode = m_xMyMagicList[nListCnt].GetHead(); pNode; pNode = pNode->GetNext() )
		{
			pstMagicRCD = pNode->GetData();

			if ( pstMagicRCD )
			{
				if ( pstMagicRCD->bUseKey == bKey )
				{
					return pstMagicRCD;
				}
			}
		}
	}
	return NULL;
}

LPCLIENTMAGICRCD CMagicWnd::GetMagicByMagicKey(INT nMagicKey)
{
	INT  nCnt, nLine, nAtoI, nListCnt;
	BYTE bKeyNum;
	LPCLIENTMAGICRCD pstMagicRCD = NULL;
	CListNode < CLIENTMAGICRCD > *pNode;

	for ( nListCnt = 0; nListCnt < _MAX_TYPE_MAGIC; nListCnt++ )
	{
		for ( pNode = m_xMyMagicList[nListCnt].GetHead(); pNode; pNode = pNode->GetNext() )
		{
			pstMagicRCD = pNode->GetData();

			if ( pstMagicRCD )
			{
				if ( pstMagicRCD->stStdMagic.wMagicID == nMagicKey )
				{
					return pstMagicRCD;
				}
			}
		}
	}
	return NULL;
}

INT CMagicWnd::GetMagicByPoint(POINT ptMouse)
{
	RECT rc;
	INT  nListCnt, nCnt, nLine;
	LPCLIENTMAGICRCD pstMagicRCD = NULL;
	CListNode < CLIENTMAGICRCD > *pNode;

	for ( nCnt = 0; nCnt < _MAGIC_MAX_CELL; nCnt++ )
	{
		rc.left   = m_rcWnd.left + m_rcMagicCell[nCnt].left;
		rc.top	  = m_rcWnd.top  + m_rcMagicCell[nCnt].top;
		rc.right  = m_rcWnd.left + m_rcMagicCell[nCnt].right;
		rc.bottom = m_rcWnd.top	 + m_rcMagicCell[nCnt].bottom;

		if ( PtInRect(&rc, ptMouse) )
		{
			for ( pNode = m_xMyMagicList[m_bTypeMagic].GetHead(), nListCnt = 0, nLine = 0; pNode; pNode = pNode->GetNext(), nListCnt++ )
			{
				// 현재 화면상에 보여줄 부분까지 만들어준다.
				if ( nListCnt >= m_nStartLineNum[m_bTypeMagic] )
				{
					if ( nLine == nCnt )
					{
						pstMagicRCD = pNode->GetData();

						if ( pstMagicRCD )
						{							
							return pstMagicRCD->stStdMagic.wMagicID;
						}
					}

					nLine++;

					if ( nLine >= _MAGIC_MAX_CELL )
					{
						break;
					}
				}
			}

			break;
		}
	}

	return -1;
}



VOID CMagicWnd::ShowMagicTxt(INT nMagicID)
{
	BYTE		 bFindState = 0;

	CHAR	pszLine[MAX_PATH*5];
	CHAR	pszDivided[MAX_PATH*5];
	CHAR	pszArg[20][MAX_PATH];
	INT		nLineCnt;
	CHAR*	pszCurr;
	CHAR*	pszStart;
	INT		nLen;

	SIZE	sizeBoard = {0, 0};
	SIZE	sizeLen	  = {0, 0};


	if ( nMagicID == -1 )
	{
		return;
	}
	
	INT		nStartX = g_xGameProc.m_ptMousePos.x + 20;
	INT		nStartY = g_xGameProc.m_ptMousePos.y + 20;

	if ( nStartX + 170 > 800 )
		nStartX = 800 - 170;

	pszStart = pszCurr = m_pszMagicExplain+8;

	if ( pszStart )
	{
		while ( pszCurr )
		{
			if ( pszCurr = strchr(pszStart, '\r') )
			{
				pszCurr++;
				if ( *pszCurr == '\n' )
				{
					pszCurr++;
					// 하나의 라인이다.
					nLen = pszCurr - pszStart;
					memcpy(pszLine, pszStart, nLen);

					nLen -= 2;

					if ( nLen < 0 )
					{
						nLen = 0;
					}

					pszLine[nLen] = NULL;

					if ( *(pszLine) != ';' )
					{
						if ( *(pszLine) == '#' )
						{
							if ( nMagicID == atoi(pszLine+1) )
							{
								bFindState = 1;
							}
							else
							{
								if ( bFindState == 1 )
								{
									bFindState = 0;
									break;
								}
							}
						}

						if ( bFindState == 1 && *(pszLine) != '#' )
						{
							ZeroMemory(pszDivided, MAX_PATH*5);
							ZeroMemory(pszArg,	  MAX_PATH*20);
							g_xMainWnd.StringDivide(165, nLineCnt, pszLine, pszDivided);
							sscanf(pszDivided, "%[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c", 
								   pszArg[0], pszArg[1], pszArg[2], pszArg[3], pszArg[4], pszArg[5], pszArg[6], pszArg[7], pszArg[8], pszArg[9], 
								   pszArg[10], pszArg[11], pszArg[12], pszArg[13], pszArg[14], pszArg[15], pszArg[16], pszArg[17], pszArg[18], pszArg[19]);


							for ( INT nCnt = 0; nCnt < nLineCnt; nCnt++ )
							{
								sizeLen = g_xMainWnd.GetStrLength(NULL, NULL, pszArg[nCnt]);

								if ( sizeLen.cx > sizeBoard.cx )
								{
									sizeBoard.cx = sizeLen.cx + 7;
								}
								sizeBoard.cy += 15;
							}
						}
					}

					pszStart = pszCurr;
				}
				else
				{
					return;
				}
			}
		}
	}
	sizeBoard.cy += 30;

	// 뒷판 그리기.

	if ( nStartX + sizeBoard.cx > 800 )
		nStartX = 800 - sizeBoard.cx;

	if ( nStartY + sizeBoard.cy > 600 )
		nStartY = 600 - sizeBoard.cy;

	D3DVECTOR	 vecTrans((FLOAT)(nStartX-2), (FLOAT)(nStartY), 0);
	D3DVECTOR	 vecScale((FLOAT)(sizeBoard.cx), (FLOAT)(sizeBoard.cy), 1);
	D3DMATERIAL7 mtrl;

	D3DUtil_InitMaterial(mtrl, (FLOAT)100/255.0f, (FLOAT)100/255.0f, (FLOAT)50/255.0f);
	mtrl.diffuse.a = 150.0f/255.0f;
	g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);							

	bFindState = 0;
	pszStart = pszCurr = m_pszMagicExplain+8;

	if ( pszStart )
	{
		while ( pszCurr )
		{
			if ( pszCurr = strchr(pszStart, '\r') )
			{
				pszCurr++;
				if ( *pszCurr == '\n' )
				{
					pszCurr++;
					// 하나의 라인이다.
					nLen = pszCurr - pszStart;
					memcpy(pszLine, pszStart, nLen);

					nLen -= 2;

					if ( nLen < 0 )
					{
						nLen = 0;
					}

					pszLine[nLen] = NULL;

					if ( *(pszLine) != ';' )
					{
						if ( *(pszLine) == '#' )
						{
							if ( nMagicID == atoi(pszLine+1) )
							{
								bFindState = 1;
							}
							else
							{
								if ( bFindState == 1 )
								{
									bFindState = 0;
									break;
								}
							}
						}

						if ( bFindState == 1 && *(pszLine) != '#' )
						{
							ZeroMemory(pszDivided, MAX_PATH*5);
							ZeroMemory(pszArg,	  MAX_PATH*20);
							g_xMainWnd.StringDivide(165, nLineCnt, pszLine, pszDivided);
							sscanf(pszDivided, "%[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c %[^`]%*c", 
								   pszArg[0], pszArg[1], pszArg[2], pszArg[3], pszArg[4], pszArg[5], pszArg[6], pszArg[7], pszArg[8], pszArg[9], 
								   pszArg[10], pszArg[11], pszArg[12], pszArg[13], pszArg[14], pszArg[15], pszArg[16], pszArg[17], pszArg[18], pszArg[19]);

							for ( INT nCnt = 0; nCnt < nLineCnt; nCnt++ )
							{
								nStartY += 15;

								HFONT hFont = NULL;
								if ( pszArg[nCnt][0] == '[' )
								{
									hFont =  g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 10, 0, FW_BOLD);
									g_xMainWnd.PutsHan(NULL, nStartX-1, nStartY-1, RGB(10, 10, 10), RGB(0, 0, 0), pszArg[nCnt], hFont);

									hFont =  g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 10, 0, FW_BOLD);
									g_xMainWnd.PutsHan(NULL, nStartX+1, nStartY-1, RGB(10, 10, 10), RGB(0, 0, 0), pszArg[nCnt], hFont);

									hFont =  g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 10, 0, FW_BOLD);
									g_xMainWnd.PutsHan(NULL, nStartX-1, nStartY+1, RGB(10, 10, 10), RGB(0, 0, 0), pszArg[nCnt], hFont);

									hFont =  g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 10, 0, FW_BOLD);
									g_xMainWnd.PutsHan(NULL, nStartX+1, nStartY+1, RGB(10, 10, 10), RGB(0, 0, 0), pszArg[nCnt], hFont);

									hFont =  g_xMainWnd.CreateGameFont(g_xMsg.GetMsg(1074), 10, 0, FW_BOLD);
									g_xMainWnd.PutsHan(NULL, nStartX, nStartY, RGB(250, 200, 150), RGB(0, 0, 0), pszArg[nCnt], hFont);

									nStartY += 15;
								}
								else
								{
									g_xMainWnd.PutsHan(NULL, nStartX, nStartY, RGB(250, 250, 250), RGB(0, 0, 0), pszArg[nCnt]);
								}							
							}
						}
					}

					pszStart = pszCurr;
				}
				else
				{
					return;
				}
			}
		}
	}

	RECT	rcText;
	CHAR	szLevel[MAX_PATH];
	LPCLIENTMAGICRCD pstMagicRCD = NULL;
	CListNode < CLIENTMAGICRCD > *pNode;

	for ( pNode = m_xMyMagicList[m_bTypeMagic].GetHead(); pNode; pNode = pNode->GetNext() )
	{
		pstMagicRCD = pNode->GetData();

		if ( pstMagicRCD && pstMagicRCD->stStdMagic.wMagicID == nMagicID )
		{
			if ( pstMagicRCD->bLevel < 5 )
			{
				sprintf(szLevel, "%d/%d", pstMagicRCD->nCurrTrain, pstMagicRCD->stStdMagic.nTrain[pstMagicRCD->bLevel]);

				SetRect(&rcText, nStartX, nStartY, nStartX+120, nStartY+15);
				g_xMainWnd.PutsHan(NULL, rcText.left, rcText.top , RGB(250, 20, 20), RGB(0, 0, 0), szLevel);
			}
			else if ( pstMagicRCD->bLevel == 10 )
			{
			}
			else
			{
				sprintf(szLevel, "Level : Max");

				SetRect(&rcText, nStartX, nStartY, nStartX+80, nStartY+15);
				g_xMainWnd.PutsHan(NULL, rcText, RGB(250, 20, 20), RGB(0, 0, 0), szLevel);
			}
		}
	}

}











/******************************************************************************************************************

	함수명 : CMagicWnd::OnKeyDown()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : WPARAM wParam
	         LPARAM lParam
	         POINT ptMouse
	출력   : BOOL 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
BOOL CMagicWnd::OnKeyDown(WPARAM wParam, LPARAM lParam, POINT ptMouse)
{
	INT	 nLine, nCnt;
	BOOL bCheck;
	RECT rc;

	if ( !PtInRect(&m_rcWnd, ptMouse) )
		return TRUE;

	bCheck = FALSE;

	for ( nCnt = 0; nCnt < _MAX_MAGICSLOT; nCnt++ )
	{
		nLine = nCnt + m_nStartLineNum[m_bTypeMagic];

		rc.left  = m_rcWnd.left + m_xMagicIconPos[m_bTypeMagic][nCnt].nPosX;
		rc.top	 = m_rcWnd.top  + m_xMagicIconPos[m_bTypeMagic][nCnt].nPosY - m_nStartPos;
		rc.right = m_rcWnd.left + m_xMagicIconPos[m_bTypeMagic][nCnt].nPosX + 40;
		rc.bottom= m_rcWnd.top	+ m_xMagicIconPos[m_bTypeMagic][nCnt].nPosY + 40 - m_nStartPos;
		if ( PtInRect(&rc, ptMouse) )
		{
			bCheck = TRUE;
			break;
		}
	}

	if ( !bCheck )
 		return TRUE;

	switch ( wParam )
	{
	case VK_F1:		SetMagicKey(ptMouse, '1');		return TRUE;
	case VK_F2:		SetMagicKey(ptMouse, '2');		return TRUE;
	case VK_F3:		SetMagicKey(ptMouse, '3');		return TRUE;
	case VK_F4:		SetMagicKey(ptMouse, '4');		return TRUE;
	case VK_F5:		SetMagicKey(ptMouse, '5');		return TRUE;
	case VK_F6:		SetMagicKey(ptMouse, '6');		return TRUE;
	case VK_F7:		SetMagicKey(ptMouse, '7');		return TRUE;
	case VK_F8:		SetMagicKey(ptMouse, '8');		return TRUE;
	case VK_F9:		SetMagicKey(ptMouse, '9');		return TRUE;
	case VK_F10:	SetMagicKey(ptMouse, 'A');		return TRUE;
	case VK_F11:	SetMagicKey(ptMouse, 'B');		return TRUE;
	case VK_F12:	SetMagicKey(ptMouse, 'C');		return TRUE;
	}

	return FALSE;
}


BOOL CMagicWnd::OnSysKeyDown(WPARAM wParam, LPARAM lParam, POINT ptMouse)
{
	INT	 nLine, nCnt;
	BOOL bCheck;
	RECT rc;

	if ( !PtInRect(&m_rcWnd, ptMouse) )		return FALSE;

	bCheck = FALSE;

	for ( nCnt = 0; nCnt < _MAX_MAGICSLOT; nCnt++ )
	{
		rc.left  = m_rcWnd.left + m_xMagicIconPos[m_bTypeMagic][nCnt].nPosX;
		rc.top	 = m_rcWnd.top  + m_xMagicIconPos[m_bTypeMagic][nCnt].nPosY - m_nStartPos;
		rc.right = m_rcWnd.left + m_xMagicIconPos[m_bTypeMagic][nCnt].nPosX + 40;
		rc.bottom= m_rcWnd.top	+ m_xMagicIconPos[m_bTypeMagic][nCnt].nPosY + 40 - m_nStartPos;

		if ( PtInRect(&rc, ptMouse) )
		{
			bCheck = TRUE;
			break;
		}
	}

	if ( !bCheck ) 							return TRUE;

	switch ( wParam )
	{
	case VK_F10:	SetMagicKey(ptMouse, 'A');		return TRUE;
	case VK_F12:	SetMagicKey(ptMouse, 'C');		return TRUE;
	}

	return FALSE;
}


BOOL CMagicWnd::OnLButtonUp(POINT ptMouse)
{
	if ( m_xWndScrBar.OnLButtonUp(ptMouse) )	return FALSE;

	if ( m_xMagicCloseBtn.OnLButtonUp(ptMouse) )		
	{
		if ( g_xGameProc.m_xInterface.m_xMagicShortcutWnd.GetGameWndActive() )
		{
			g_xGameProc.m_xInterface.WindowActivate(_WND_ID_MAGICSHORTCUT);
		}

		m_bWantSetKey = FALSE;
		return TRUE;
	}

	for ( INT nCnt = 0; nCnt < _MAX_TYPE_MAGIC; nCnt++ )
	{
//		if ( m_xMyMagicList[nCnt].GetCount() != 0 )
//		{
			if ( m_xMagicTypeBtn[nCnt].OnLButtonUp(ptMouse) )
			{
				m_bTypeMagic = nCnt;
				SetMagicTypeBtn();
				break;
			}
//		}
	}

	if ( m_bWantSetKey )
	{
		INT nCnt, nMagicImgIdx;
		INT nCol = 0, nSetkeyX, nSetkeyY;
		RECT rcKey[3][4];

		nSetkeyX = m_ptSetKey.x + m_rcWnd.left;
		nSetkeyY = m_ptSetKey.y + m_rcWnd.top + 40;

		for ( INT nY=0; nY<3; nY++ )
		{
			for ( INT nX=0; nX<4; nX++ )
			{
				SetRect(&rcKey[nY][nX], nSetkeyX+nX*40, nSetkeyY+nY*40, nSetkeyX+(nX+1)*40, nSetkeyY+(nY+1)*40);
				if ( PtInRect(&rcKey[nY][nX], ptMouse) )
				{
					BYTE bKey = nY*4 + nX + 1;

					switch(bKey)
					{
						case 1:
							SetMagicKeybyMouseBtn('1');
							return FALSE;
						case 2:
							SetMagicKeybyMouseBtn('2');
							return FALSE;
						case 3:
							SetMagicKeybyMouseBtn('3');
							return FALSE;
						case 4:
							SetMagicKeybyMouseBtn('4');
							return FALSE;
						case 5:
							SetMagicKeybyMouseBtn('5');
							return FALSE;
						case 6:
							SetMagicKeybyMouseBtn('6');
							return FALSE;
						case 7:
							SetMagicKeybyMouseBtn('7');
							return FALSE;
						case 8:
							SetMagicKeybyMouseBtn('8');
							return FALSE;
						case 9:
							SetMagicKeybyMouseBtn('9');
							return FALSE;
						case 10:
							SetMagicKeybyMouseBtn('A');
							return FALSE;
						case 11:
							SetMagicKeybyMouseBtn('B');
							return FALSE;
						case 12:
							SetMagicKeybyMouseBtn('C');
							return FALSE;
					}
				}
			}
		}
	}

	return FALSE;
}


BOOL CMagicWnd::OnLButtonDown(POINT ptMouse)
{
	INT  nCnt;
	RECT rcIcon;
	POINT ptTemp;

	if ( m_xWndScrBar.OnLButtonDown(ptMouse) )
	{
		FLOAT	fScrlRate;

		fScrlRate	= m_xWndScrBar.GetScrlRate();
		m_nStartPos = (INT)((m_nMaxPos)*fScrlRate);

		if ( m_nStartPos > m_nMaxPos - 1 )
			m_nStartPos = m_nMaxPos - 1 ;

		return TRUE;
	}

	if ( m_bWantSetKey )
	{
		if ( PtInRect(&m_rcSetKey, ptMouse) )
		{
			ptTemp.x = ptMouse.x - m_rcSetKey.left;
			ptTemp.y = ptMouse.y - m_rcSetKey.top;

			ptTemp.x /= 40;
			ptTemp.y /= 40;
		}
		else
			m_bWantSetKey = FALSE;
	}	

	if ( m_xMagicCloseBtn.OnLButtonDown(ptMouse) )
	{
		return TRUE;
	}

	for ( nCnt = 0; nCnt < _MAX_TYPE_MAGIC; nCnt++ )
	{
//		if ( m_xMyMagicList[nCnt].GetCount() != 0 )
//		{
			if ( m_xMagicTypeBtn[nCnt].OnLButtonDown(ptMouse) )
			{
				return TRUE;
			}
//		}
	}

	if ( !m_bWantSetKey )
	{
		for ( nCnt = 0; nCnt < _MAX_MAGICSLOT; nCnt++ )
		{
			rcIcon.left  = m_rcWnd.left + m_xMagicIconPos[m_bTypeMagic][nCnt].nPosX;
			rcIcon.top	 = m_rcWnd.top  + m_xMagicIconPos[m_bTypeMagic][nCnt].nPosY - m_nStartPos;
			rcIcon.right = m_rcWnd.left + m_xMagicIconPos[m_bTypeMagic][nCnt].nPosX + 40;
			rcIcon.bottom= m_rcWnd.top	+ m_xMagicIconPos[m_bTypeMagic][nCnt].nPosY + 40 - m_nStartPos;

			if ( PtInRect(&rcIcon, ptMouse) )
			{
				m_nSelectedMagic[m_bTypeMagic] = nCnt;
			}
		}

	}
	return FALSE;
}

BOOL CMagicWnd::OnLButtonDoubleClick(POINT ptMouse)
{
	INT nCnt = 0;
	RECT rcIcon;
	LPCLIENTMAGICRCD pstMagicRCD = NULL;
	CListNode < CLIENTMAGICRCD > *pNode;

	for ( nCnt = 0; nCnt < _MAX_MAGICSLOT; nCnt++ )
	{
		rcIcon.left  = m_rcWnd.left + m_xMagicIconPos[m_bTypeMagic][nCnt].nPosX;
		rcIcon.top	 = m_rcWnd.top  + m_xMagicIconPos[m_bTypeMagic][nCnt].nPosY - m_nStartPos;
		rcIcon.right = m_rcWnd.left + m_xMagicIconPos[m_bTypeMagic][nCnt].nPosX + 40;
		rcIcon.bottom= m_rcWnd.top	+ m_xMagicIconPos[m_bTypeMagic][nCnt].nPosY + 40;

		if ( PtInRect(&rcIcon, ptMouse) )
		{
			for ( pNode = m_xMyMagicList[m_bTypeMagic].GetHead(); pNode; pNode = pNode->GetNext() )
			{
				pstMagicRCD = pNode->GetData();

				if ( pstMagicRCD )
				{
					if ( pstMagicRCD->stStdMagic.wMagicID == m_xMagicIconPos[m_bTypeMagic][nCnt].nMagicID )
					{
						INT nStartX, nStartY;
						if ( ptMouse.x + 160 > m_rcWnd.right )
							nStartX = m_rcWnd.right - 160;
						else
							nStartX = ptMouse.x;

						if ( ptMouse.y + 160 > m_rcWnd.right )
							nStartY = m_rcWnd.bottom - 120;
						else
							nStartY = ptMouse.y;

						SetRect(&m_rcSetKey,  nStartX,  nStartY+40, nStartX+160, nStartY+160);

						m_bWantSetKey = TRUE;
						m_ptSetKey.x = nStartX - m_rcWnd.left;
						m_ptSetKey.y = nStartY - m_rcWnd.top;
						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}

VOID CMagicWnd::OnMouseMove(POINT ptMouse)
{
	INT nCnt;
	RECT rc;
	LPCLIENTMAGICRCD pstMagicRCD = NULL;
	CListNode < CLIENTMAGICRCD > *pNode;

	m_xMagicCloseBtn.OnMouseMove(ptMouse);

	if ( m_xWndScrBar.OnMouseMove(ptMouse) )
	{
		FLOAT	fScrlRate;
		fScrlRate	= m_xWndScrBar.GetScrlRate();

		m_nStartPos = (INT)((m_nMaxPos)*fScrlRate);
		return;
	}


	for ( nCnt = 0; nCnt < _MAX_TYPE_MAGIC; nCnt++ )
	{
		m_xMagicTypeBtn[nCnt].OnMouseMove(ptMouse);
	}
/*
	INT nMagicNum = GetMagicByPoint(ptMouse);
	if ( nMagicNum != -1 )
	{
		m_nShowMagicNum = (SHORT)nMagicNum;
	}
*/
	for ( nCnt = 0; nCnt < _MAX_MAGICSLOT; nCnt++ )
	{
		rc.left  = m_rcWnd.left + m_xMagicIconPos[m_bTypeMagic][nCnt].nPosX;
		rc.top	 = m_rcWnd.top  + m_xMagicIconPos[m_bTypeMagic][nCnt].nPosY - m_nStartPos;
		rc.right = m_rcWnd.left + m_xMagicIconPos[m_bTypeMagic][nCnt].nPosX + 40;
		rc.bottom= m_rcWnd.top	+ m_xMagicIconPos[m_bTypeMagic][nCnt].nPosY + 40 - m_nStartPos;

		if ( PtInRect(&rc, ptMouse) )
		{
			m_nShowMagicNum = m_xMagicIconPos[m_bTypeMagic][nCnt].nMagicID;
			return;
//			for ( pNode = m_xMyMagicList[m_bTypeMagic].GetHead(); pNode; pNode = pNode->GetNext() )
//			{
//				pstMagicRCD = pNode->GetData();

//				if ( pstMagicRCD )
//				{
//					if ( pstMagicRCD->stStdMagic.wMagicID == m_xMagicIconPos[m_bTypeMagic][nCnt].nMagicID )
//					{
//						m_nShowMagicNum = pstMagicRCD->stStdMagic.wMagicID;
//						return;
//					}
//				}
//			}
		}
	}

	m_nShowMagicNum = -1;
}

VOID CMagicWnd::SetStatusBtnInit()
{
	m_xMagicCloseBtn.SetBtnState(_BTN_STATE_NORMAL);
}





VOID CMagicWnd::SetMagicIconPos()
{
	// 화계열
	m_xMagicIconPos[0][0].nMagicID = _SKILL_FIREBALL;
	m_xMagicIconPos[0][0].nPosX = 29;
	m_xMagicIconPos[0][0].nPosY = 79;

	m_xMagicIconPos[0][1].nMagicID = _SKILL_FIREBALL2;
	m_xMagicIconPos[0][1].nPosX = 29;
	m_xMagicIconPos[0][1].nPosY = 139;

	m_xMagicIconPos[0][2].nMagicID = _SKILL_FIRE;
	m_xMagicIconPos[0][2].nPosX = 89;
	m_xMagicIconPos[0][2].nPosY = 199;

	m_xMagicIconPos[0][3].nMagicID = _SKILL_FIREBOOM;
	m_xMagicIconPos[0][3].nPosX = 149;
	m_xMagicIconPos[0][3].nPosY = 259;

	m_xMagicIconPos[0][4].nMagicID = _SKILL_EARTHFIRE;
	m_xMagicIconPos[0][4].nPosX = 89;
	m_xMagicIconPos[0][4].nPosY = 259;

	m_xMagicIconPos[0][5].nMagicID = _SKILL_FIREBALL10;
	m_xMagicIconPos[0][5].nPosX = 29;
	m_xMagicIconPos[0][5].nPosY = 319;

	// 빙계열
	m_xMagicIconPos[1][0].nMagicID = _SKILL_ICEBOLT;
	m_xMagicIconPos[1][0].nPosX = 29;
	m_xMagicIconPos[1][0].nPosY = 79;

	m_xMagicIconPos[1][1].nMagicID = _SKILL_SUPERICEBOLT;
	m_xMagicIconPos[1][1].nPosX = 29;
	m_xMagicIconPos[1][1].nPosY = 139;

	m_xMagicIconPos[1][2].nMagicID = _SKILL_ICE;
	m_xMagicIconPos[1][2].nPosX = 89;
	m_xMagicIconPos[1][2].nPosY = 199;

	m_xMagicIconPos[1][3].nMagicID = _SKILL_SNOWWIND;
	m_xMagicIconPos[1][3].nPosX = 149;
	m_xMagicIconPos[1][3].nPosY = 259;

	m_xMagicIconPos[1][4].nMagicID = _SKILL_CROSS_ICE;
	m_xMagicIconPos[1][4].nPosX = 89;
	m_xMagicIconPos[1][4].nPosY = 259;

	// 뢰계열
	m_xMagicIconPos[2][0].nMagicID = _SKILL_MAGICARROW;
	m_xMagicIconPos[2][0].nPosX = 29;
	m_xMagicIconPos[2][0].nPosY = 79;

	m_xMagicIconPos[2][1].nMagicID = _SKILL_LIGHTENING;
	m_xMagicIconPos[2][1].nPosX = 29;
	m_xMagicIconPos[2][1].nPosY = 139;

	m_xMagicIconPos[2][2].nMagicID = _SKILL_SHOOTLIGHTEN;
	m_xMagicIconPos[2][2].nPosX = 89;
	m_xMagicIconPos[2][2].nPosY = 199;

	m_xMagicIconPos[2][3].nMagicID = _SKILL_LIGHTFLOWER;
	m_xMagicIconPos[2][3].nPosX = 149;
	m_xMagicIconPos[2][3].nPosY = 259;

	m_xMagicIconPos[2][4].nMagicID = _SKILL_THUNDERSTORM;
	m_xMagicIconPos[2][4].nPosX = 149;
	m_xMagicIconPos[2][4].nPosY = 319;

	m_xMagicIconPos[2][5].nMagicID = _SKILL_1000THUNDER;
	m_xMagicIconPos[2][5].nPosX = 89;
	m_xMagicIconPos[2][5].nPosY = 319;

	m_xMagicIconPos[2][6].nMagicID = _SKILL_CLOUDTHUNDER;
	m_xMagicIconPos[2][6].nPosX = 28;
	m_xMagicIconPos[2][6].nPosY = 319;

	// 풍계열
	m_xMagicIconPos[3][0].nMagicID = _SKILL_HANDWIND;
	m_xMagicIconPos[3][0].nPosX = 29;
	m_xMagicIconPos[3][0].nPosY = 79;

	m_xMagicIconPos[3][1].nMagicID = _SKILL_FIREWIND;
	m_xMagicIconPos[3][1].nPosX = 149;
	m_xMagicIconPos[3][1].nPosY = 139;

	m_xMagicIconPos[3][2].nMagicID = _SKILL_HURRICANEBOMB;
	m_xMagicIconPos[3][2].nPosX = 29;
	m_xMagicIconPos[3][2].nPosY = 139;

	m_xMagicIconPos[3][3].nMagicID = _SKILL_HURRICANESHOT;
	m_xMagicIconPos[3][3].nPosX = 89;
	m_xMagicIconPos[3][3].nPosY = 199;

	m_xMagicIconPos[3][4].nMagicID = _SKILL_SHIELD;
	m_xMagicIconPos[3][4].nPosX = 149;
	m_xMagicIconPos[3][4].nPosY = 199;

	m_xMagicIconPos[3][5].nMagicID = _SKILL_HURRICANE;
	m_xMagicIconPos[3][5].nPosX = 89;
	m_xMagicIconPos[3][5].nPosY = 259;

	m_xMagicIconPos[3][6].nMagicID = _SKILL_KANGMAK;
	m_xMagicIconPos[3][6].nPosX = 89;
	m_xMagicIconPos[3][6].nPosY = 319;

	m_xMagicIconPos[3][7].nMagicID = _SKILL_SHIELD_HIGH;
	m_xMagicIconPos[3][7].nPosX = 149;
	m_xMagicIconPos[3][7].nPosY = 199;

	// 신성
	m_xMagicIconPos[4][0].nMagicID = _SKILL_HEALLING;
	m_xMagicIconPos[4][0].nPosX = 29;
	m_xMagicIconPos[4][0].nPosY = 79;

	m_xMagicIconPos[4][1].nMagicID = _SKILL_MOONOK;
	m_xMagicIconPos[4][1].nPosX = 89;
	m_xMagicIconPos[4][1].nPosY = 139;

	m_xMagicIconPos[4][2].nMagicID = _SKILL_BIGHEALLING;
	m_xMagicIconPos[4][2].nPosX = 29;
	m_xMagicIconPos[4][2].nPosY = 199;

	m_xMagicIconPos[4][3].nMagicID = _SKILL_MOONCHAM;
	m_xMagicIconPos[4][3].nPosX = 89;
	m_xMagicIconPos[4][3].nPosY = 199;	

	m_xMagicIconPos[4][4].nMagicID = _SKILL_REVIVE;
	m_xMagicIconPos[4][4].nPosX = 29;
	m_xMagicIconPos[4][4].nPosY = 259;

	m_xMagicIconPos[4][5].nMagicID = _SKILL_REMOVEPOISON;
	m_xMagicIconPos[4][5].nPosX = 149;
	m_xMagicIconPos[4][5].nPosY = 259;

	m_xMagicIconPos[4][6].nMagicID = _SKILL_DOSASHIELD;
	m_xMagicIconPos[4][6].nPosX = 149;
	m_xMagicIconPos[4][6].nPosY = 319;

	m_xMagicIconPos[4][7].nMagicID = _SKILL_INHALEHP;
	m_xMagicIconPos[4][7].nPosX = 29;
	m_xMagicIconPos[4][7].nPosY = 319;

	m_xMagicIconPos[4][8].nMagicID = _SKILL_HEALX;
	m_xMagicIconPos[4][8].nPosX = 29;
	m_xMagicIconPos[4][8].nPosY = 379;

	// 암흑
	m_xMagicIconPos[5][0].nMagicID = _SKILL_AMYOUNSUL;
	m_xMagicIconPos[5][0].nPosX = 29;
	m_xMagicIconPos[5][0].nPosY = 79;

	m_xMagicIconPos[5][1].nMagicID = _SKILL_FIRECHARM;
	m_xMagicIconPos[5][1].nPosX = 29;
	m_xMagicIconPos[5][1].nPosY = 139;

	m_xMagicIconPos[5][2].nMagicID = _SKILL_HOLYSHIELD;
	m_xMagicIconPos[5][2].nPosX = 149;
	m_xMagicIconPos[5][2].nPosY = 259;

	m_xMagicIconPos[5][3].nMagicID = _SKILL_HANGMAJINBUB;
	m_xMagicIconPos[5][3].nPosX = 89;
	m_xMagicIconPos[5][3].nPosY = 199;

	m_xMagicIconPos[5][4].nMagicID = _SKILL_CLOAK;
	m_xMagicIconPos[5][4].nPosX = 149;
	m_xMagicIconPos[5][4].nPosY = 139;

	m_xMagicIconPos[5][5].nMagicID = _SKILL_DEJIWONHO;
	m_xMagicIconPos[5][5].nPosX = 89;
	m_xMagicIconPos[5][5].nPosY = 259;

	m_xMagicIconPos[5][6].nMagicID = _SKILL_BIGCLOAK;
	m_xMagicIconPos[5][6].nPosX = 149;
	m_xMagicIconPos[5][6].nPosY = 199;

	m_xMagicIconPos[5][7].nMagicID = _SKILL_MAGICUP;
	m_xMagicIconPos[5][7].nPosX = 89;
	m_xMagicIconPos[5][7].nPosY = 319;

	m_xMagicIconPos[5][8].nMagicID = _SKILL_POWERUP;
	m_xMagicIconPos[5][8].nPosX = 89;
	m_xMagicIconPos[5][8].nPosY = 379;

	m_xMagicIconPos[5][9].nMagicID = _SKILL_FULLCLOAK;
	m_xMagicIconPos[5][9].nPosX = 149;
	m_xMagicIconPos[5][9].nPosY = 379;

	m_xMagicIconPos[5][10].nMagicID = _SKILL_MYULSAL;
	m_xMagicIconPos[5][10].nPosX = 29;
	m_xMagicIconPos[5][10].nPosY = 379;

	m_xMagicIconPos[5][11].nMagicID = _SKILL_BIGAM;
	m_xMagicIconPos[5][11].nPosX = 29;
	m_xMagicIconPos[5][11].nPosY = 449;

	m_xMagicIconPos[5][12].nMagicID = _SKILL_DEJIWONHO_HIGH;
	m_xMagicIconPos[5][12].nPosX = 89;
	m_xMagicIconPos[5][12].nPosY = 259;

	m_xMagicIconPos[5][13].nMagicID = _SKILL_CLOAK_HIGH;
	m_xMagicIconPos[5][13].nPosX = 149;
	m_xMagicIconPos[5][13].nPosY = 139;

	m_xMagicIconPos[5][14].nMagicID = _SKILL_MOONCHAM_HIGH;
	m_xMagicIconPos[5][14].nPosX = 29;
	m_xMagicIconPos[5][14].nPosY = 379;
// 환영
	m_xMagicIconPos[6][0].nMagicID = _SKILL_SKELLETON;
	m_xMagicIconPos[6][0].nPosX = 29;
	m_xMagicIconPos[6][0].nPosY = 79;

	m_xMagicIconPos[6][1].nMagicID = _SKILL_TAMMING;
	m_xMagicIconPos[6][1].nPosX = 149;
	m_xMagicIconPos[6][1].nPosY = 79;

	m_xMagicIconPos[6][2].nMagicID = _SKILL_SPACEMOVE;
	m_xMagicIconPos[6][2].nPosX = 209;
	m_xMagicIconPos[6][2].nPosY = 139;

	m_xMagicIconPos[6][3].nMagicID = _SKILL_SINSU;
	m_xMagicIconPos[6][3].nPosX = 29;
	m_xMagicIconPos[6][3].nPosY = 139;

	m_xMagicIconPos[6][4].nMagicID = _SKILL_KILLUNDEAD;
	m_xMagicIconPos[6][4].nPosX = 149;
	m_xMagicIconPos[6][4].nPosY = 199;

	m_xMagicIconPos[6][5].nMagicID = _SKILL_SMALLSPACEMOVE;
	m_xMagicIconPos[6][5].nPosX = 209;
	m_xMagicIconPos[6][5].nPosY = 199;

	m_xMagicIconPos[6][6].nMagicID = _SKILL_POWERSKELLETON;
	m_xMagicIconPos[6][6].nPosX = 29;
	m_xMagicIconPos[6][6].nPosY = 199;

	m_xMagicIconPos[6][7].nMagicID = _SKILL_MONSTERUP;
	m_xMagicIconPos[6][7].nPosX = 89;
	m_xMagicIconPos[6][7].nPosY = 259;

	m_xMagicIconPos[6][8].nMagicID = _SKILL_MAXDEFEECEMAGIC;
	m_xMagicIconPos[6][8].nPosX = 149;
	m_xMagicIconPos[6][8].nPosY = 319;

	m_xMagicIconPos[6][9].nMagicID = _SKILL_DOLL;
	m_xMagicIconPos[6][9].nPosX = 29;
	m_xMagicIconPos[6][9].nPosY = 319;

	m_xMagicIconPos[6][10].nMagicID = _SKILL_COPY;
	m_xMagicIconPos[6][10].nPosX = 209;
	m_xMagicIconPos[6][10].nPosY = 319;

	m_xMagicIconPos[6][11].nMagicID = _SKILL_MAXDEFEECEMAGIC_HIGH;
	m_xMagicIconPos[6][11].nPosX = 149;
	m_xMagicIconPos[6][11].nPosY = 319;

//	x 12, y 40;
	// 무속성
	m_xMagicIconPos[7][0].nMagicID = _SKILL_ONESWORD;
	m_xMagicIconPos[7][0].nPosX = 29;
	m_xMagicIconPos[7][0].nPosY = 79;

	m_xMagicIconPos[7][1].nMagicID = _SKILL_MOOTEBO;
	m_xMagicIconPos[7][1].nPosX = 149;
	m_xMagicIconPos[7][1].nPosY = 259;

	m_xMagicIconPos[7][2].nMagicID = _SKILL_ILKWANG;
	m_xMagicIconPos[7][2].nPosX = 269;
	m_xMagicIconPos[7][2].nPosY = 79;

	m_xMagicIconPos[7][3].nMagicID = _SKILL_YEDO;
	m_xMagicIconPos[7][3].nPosX = 29;
	m_xMagicIconPos[7][3].nPosY = 139;

	m_xMagicIconPos[7][4].nMagicID = _SKILL_KICK;
	m_xMagicIconPos[7][4].nPosX = 269;
	m_xMagicIconPos[7][4].nPosY = 259;

	m_xMagicIconPos[7][5].nMagicID = _SKILL_ERGUM;
	m_xMagicIconPos[7][5].nPosX = 29;
	m_xMagicIconPos[7][5].nPosY = 199;

	m_xMagicIconPos[7][6].nMagicID = _SKILL_BANWOL;
	m_xMagicIconPos[7][6].nPosX = 29;
	m_xMagicIconPos[7][6].nPosY = 259;

	m_xMagicIconPos[7][7].nMagicID = _SKILL_FIRESWORD;
	m_xMagicIconPos[7][7].nPosX = 89;
	m_xMagicIconPos[7][7].nPosY = 319;

	m_xMagicIconPos[7][8].nMagicID = _SKILL_JUMPSHOT;
	m_xMagicIconPos[7][8].nPosX = 29;
	m_xMagicIconPos[7][8].nPosY = 319;

	m_xMagicIconPos[7][9].nMagicID = _SKILL_RANDSWING;
	m_xMagicIconPos[7][9].nPosX = 89;
	m_xMagicIconPos[7][9].nPosY = 379;

	m_xMagicIconPos[7][10].nMagicID = _SKILL_MANWOL;
	m_xMagicIconPos[7][10].nPosX = 29;
	m_xMagicIconPos[7][10].nPosY = 379;

	m_xMagicIconPos[7][11].nMagicID = _SKILL_CHANGEPOSITION;
	m_xMagicIconPos[7][11].nPosX = 149;
	m_xMagicIconPos[7][11].nPosY = 319;

	m_xMagicIconPos[7][12].nMagicID = _SKILL_MAXDEFENCE;
	m_xMagicIconPos[7][12].nPosX = 209;
	m_xMagicIconPos[7][12].nPosY = 379;

	m_xMagicIconPos[7][13].nMagicID = _SKILL_MAXOFENCE;
	m_xMagicIconPos[7][13].nPosX = 209;
	m_xMagicIconPos[7][13].nPosY = 439;

	m_xMagicIconPos[7][14].nMagicID = _SKILL_PULL;
	m_xMagicIconPos[7][14].nPosX = 149;
	m_xMagicIconPos[7][14].nPosY = 379;

	m_xMagicIconPos[7][15].nMagicID = _SKILL_PAWHANGBO;
	m_xMagicIconPos[7][15].nPosX = 149;
	m_xMagicIconPos[7][15].nPosY = 439;

	m_xMagicIconPos[7][16].nMagicID = _SKILL_TAWOO;
	m_xMagicIconPos[7][16].nPosX = 269;
	m_xMagicIconPos[7][16].nPosY = 379;

	m_xMagicIconPos[7][17].nMagicID = _SKILL_BANTAN;
	m_xMagicIconPos[7][17].nPosX = 209;
	m_xMagicIconPos[7][17].nPosY = 499;

	m_xMagicIconPos[7][18].nMagicID = _SKILL_FREEMOVE;
	m_xMagicIconPos[7][18].nPosX = 149;
	m_xMagicIconPos[7][18].nPosY = 499;

	m_xMagicIconPos[7][19].nMagicID = _SKILL_POTIONUP;
	m_xMagicIconPos[7][19].nPosX = 29;
	m_xMagicIconPos[7][19].nPosY = 499;

	m_xMagicIconPos[7][20].nMagicID = _SKILL_HYPERSWORD;
	m_xMagicIconPos[7][20].nPosX = 89;
	m_xMagicIconPos[7][20].nPosY = 559;

	m_xMagicIconPos[7][21].nMagicID = _SKILL_BIGMOUNTAIN;
	m_xMagicIconPos[7][21].nPosX = 209;
	m_xMagicIconPos[7][21].nPosY = 559;

	m_xMagicIconPos[7][22].nMagicID = _SKILL_RANDSWING_HIGH;
	m_xMagicIconPos[7][22].nPosX = 89;
	m_xMagicIconPos[7][22].nPosY = 379;

	m_xMagicIconPos[7][23].nMagicID = _SKILL_JUMPSHOT_HIGH;
	m_xMagicIconPos[7][23].nPosX = 29;
	m_xMagicIconPos[7][23].nPosY = 319;

	m_xMagicIconPos[7][24].nMagicID = _SKILL_PAWHANGBO_HIGH;
	m_xMagicIconPos[7][24].nPosX = 149;
	m_xMagicIconPos[7][24].nPosY = 439;

	m_xMagicIconPos[7][25].nMagicID = _SKILL_BALSACHE;
	m_xMagicIconPos[7][25].nPosX = 29;
	m_xMagicIconPos[7][25].nPosY = 619;

	m_xMagicIconPos[7][26].nMagicID = _SKILL_JIKSUNGYE;
	m_xMagicIconPos[7][26].nPosX = 89;
	m_xMagicIconPos[7][26].nPosY = 619;

	m_xMagicIconPos[7][27].nMagicID = _SKILL_POKBAL;
	m_xMagicIconPos[7][27].nPosX = 149;
	m_xMagicIconPos[7][27].nPosY = 619;

	m_xMagicIconPos[7][28].nMagicID = _SKILL_JISOKGYE;
	m_xMagicIconPos[7][28].nPosX = 209;
	m_xMagicIconPos[7][28].nPosY = 619;

}

VOID CMagicWnd::ShowSetKeyWnd()
{
	INT nCnt, nMagicImgIdx, nX, nY;
	INT nCol = 0, nStartX, nStartY;

	nStartX = m_ptSetKey.x + m_rcWnd.left;
	nStartY = m_ptSetKey.y + m_rcWnd.top + 40;

	D3DVECTOR	 vecTrans((FLOAT)(nStartX), (FLOAT)(nStartY), 0);
	D3DVECTOR	 vecScale((FLOAT)(160), (FLOAT)(120), 1);
	D3DMATERIAL7 mtrl;

	D3DUtil_InitMaterial(mtrl, (FLOAT)100/255.0f, (FLOAT)100/255.0f, (FLOAT)50/255.0f);
	mtrl.diffuse.a = 150.0f/255.0f;
	g_xGameProc.m_xImage.DrawBillBoard(g_xMainWnd.Get3DDevice(), &vecTrans, &vecScale, &mtrl, NULL);

	for ( nY = 0; nY < 3; nY++ )
	{
		for ( nX = 0; nX < 4; nX++ )
		{
			nCnt = nY*4 + nX;

			if ( m_bMagicKeyTable[nCnt] )
			{
				nMagicImgIdx = (m_bMagicKeyTable[nCnt]-1) * 2;

				if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].NewSetIndex(nMagicImgIdx) )
				{
					g_xMainWnd.DrawWithImageForComp(
													nStartX + (40 * nX), 
													nStartY + (40 * nY), 
													g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_lpstNewCurrWilImageInfo->shWidth, 
													g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_lpstNewCurrWilImageInfo->shHeight,
													(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_pbCurrImage));
				}
			}

			if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].NewSetIndex(1660+nCnt) )
			{
				g_xMainWnd.DrawWithImageForComp(
												nStartX + (40 * nX), 
												nStartY + (40 * nY), 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shWidth, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_lpstNewCurrWilImageInfo->shHeight,
												(WORD*)(g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER].m_pbCurrImage));
			}
		}
	}
}

/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"



/******************************************************************************************************************

	CMagicShortcutWnd Class

*******************************************************************************************************************/
/******************************************************************************************************************

	함수명 : CMagicShortcutWnd::CMagicShortcutWnd()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
CMagicShortcutWnd::CMagicShortcutWnd()
{
	Init();
}

CMagicShortcutWnd::~CMagicShortcutWnd()
{
	Destroy();
}


VOID CMagicShortcutWnd::Init()
{
	mMSCutwnd_nTabNum = 0;
	mMSCutwnd_nShowMagicNum = -1;

	for ( INT nI=0; nI<4; nI++ )
	{
		for ( INT nJ=0; nJ<12; nJ++ )
		{
			mMSCutwnd_nMagicNum[nI][nJ] = -1;
		}
	}
}


VOID CMagicShortcutWnd::Destroy()
{
	INT nCnt;
	CGameWnd::Destroy();
	Init();
}

VOID CMagicShortcutWnd::CreateMagicShortcutWnd(INT nID, CWHWilImageData* pxWndImage, INT nFrameImgIdx, INT nStartX, INT nStartY, INT nWidth, INT nHeight, BOOL bCanMove, BYTE bBlend)
{
	pxWndImage = &(g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1]);
	// 윈도우 생성.
	CreateGameWnd(nID, pxWndImage, nFrameImgIdx, bCanMove, nStartX, nStartY, nWidth, nHeight, bBlend);
}

VOID CMagicShortcutWnd::ShowMagicShortcutWnd()
{
	// 윈도우 바탕그리기.
	ShowGameWnd(_IMAGE_INTER1);

	for ( INT nI=0; nI<4; nI++ )
	{
		SetRect(&mMSCutwnd_rcTab[nI], m_rcWnd.left+44+34*nI, m_rcWnd.top+11, m_rcWnd.left+77+34*nI, m_rcWnd.top+38);
	}

	// 현재 선택된 탭 그리기
	if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].NewSetIndex(mMSCutwnd_nTabNum+21) )
	{
		g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+44+mMSCutwnd_nTabNum*34, m_rcWnd.top+11,
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shWidth, 
										g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shHeight,
										(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_pbCurrImage);
	}

	for ( nI=0; nI<3; nI++ )
	{
		for ( INT nJ=0; nJ<4; nJ++ )
		{
			// 무공 아이콘 그리기
			INT nMagicImgIdx = (mMSCutwnd_nMagicNum[mMSCutwnd_nTabNum][nI*4+nJ]-1) * 2;
			if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].NewSetIndex(nMagicImgIdx) )
			{
				g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+20+nJ*49, m_rcWnd.top+51+nI*49,
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_lpstNewCurrWilImageInfo->shWidth, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_lpstNewCurrWilImageInfo->shHeight,
												(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_MICON].m_pbCurrImage);
			}

			// 단축키 그림 그리기
			if ( g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].NewSetIndex(30+nI*4+nJ) )
			{
				g_xMainWnd.DrawWithImageForComp(m_rcWnd.left+20+nJ*49, m_rcWnd.top+51+nI*49,
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shWidth, 
												g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_lpstNewCurrWilImageInfo->shHeight,
												(WORD *)g_xGameProc.m_xImage.m_xImageList[_IMAGE_INTER1].m_pbCurrImage);
			}

		}
	}

	g_xGameProc.m_xInterface.m_xMagicWnd.ShowMagicTxt(mMSCutwnd_nShowMagicNum);

}

BOOL CMagicShortcutWnd::OnLButtonDown(POINT ptMouse)
{
	return FALSE;
}

BOOL CMagicShortcutWnd::OnLButtonUp(POINT ptMouse)
{
	for ( INT nI=0; nI<4; nI++ )
	{
		if ( PtInRect(&mMSCutwnd_rcTab[nI], ptMouse) )
		{
			mMSCutwnd_nTabNum = nI;
		}
	}

	return FALSE;
}

BOOL CMagicShortcutWnd::OnMouseMove(POINT ptMouse)
{
	RECT rcIcon;
	for ( INT nI=0; nI<3; nI++ )
	{
		for ( INT nJ=0; nJ<4; nJ++ )
		{
			SetRect(&rcIcon, m_rcWnd.left + nJ*49 + 18, m_rcWnd.top + nI*48 + 50, 
							 m_rcWnd.left + nJ*49 + 56, m_rcWnd.top + nI*48 + 88);

			if ( PtInRect(&rcIcon, ptMouse) )
			{
				mMSCutwnd_nShowMagicNum = mMSCutwnd_nMagicNum[mMSCutwnd_nTabNum][nI*4+nJ];
				return TRUE;
			}
		}
	}

	mMSCutwnd_nShowMagicNum = -1;
	return FALSE;
}



BOOL CMagicShortcutWnd::OnRButtonDown(POINT ptMouse)
{
	return FALSE;
}

VOID CMagicShortcutWnd::SetMagicIcon(INT nMagicID, INT nShortKey)
{
	for ( INT nI=0; nI<12; nI++ )
	{
		if ( mMSCutwnd_nMagicNum[mMSCutwnd_nTabNum][nI] == nMagicID )
		{
			mMSCutwnd_nMagicNum[mMSCutwnd_nTabNum][nI] = -1;
		}
	}

	mMSCutwnd_nMagicNum[mMSCutwnd_nTabNum][nShortKey-1] = nMagicID;
}

INT CMagicShortcutWnd::GetMagicIDByKey(INT nKey)
{
	return mMSCutwnd_nMagicNum[mMSCutwnd_nTabNum][nKey-1];
}

BOOL CMagicShortcutWnd::SaveMagicKeySet()
{
	HANDLE	hFile;
	CHAR	szItemFile[MAX_PATH];

	ZeroMemory(szItemFile, MAX_PATH);

	char	*pszName = NULL;
	pszName = g_xGameProc.CheckAbnormalName(g_xGameProc.m_xMyHero.m_szName);

	if ( strlen(pszName) == 0 )
		return FALSE;

	g_xMainWnd.StringPlus(szItemFile, ".\\Data\\", pszName, ".mcs", "");
	hFile = CreateFile(szItemFile, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if ( hFile != INVALID_HANDLE_VALUE )
	{
		DWORD		dwWriteLen;

		WriteFile(hFile, &mMSCutwnd_nMagicNum, sizeof(INT)*4*12, &dwWriteLen, NULL);
		WriteFile(hFile, &mMSCutwnd_nTabNum, sizeof(INT), &dwWriteLen, NULL);

		CloseHandle(hFile);
		return TRUE;
	}
	return FALSE;
}

BOOL CMagicShortcutWnd::LoadMagicKeySet()
{
	HANDLE	hFile;
	CHAR	szItemFile[MAX_PATH];

	ZeroMemory(szItemFile, MAX_PATH);
	
	char	*pszName = NULL;
	pszName = g_xGameProc.CheckAbnormalName(g_xGameProc.m_xMyHero.m_szName);

	if ( strlen(pszName) == 0 )
		return FALSE;

	g_xMainWnd.StringPlus(szItemFile, ".\\Data\\", pszName, ".mcs", "");
	hFile = CreateFile(szItemFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if ( hFile != INVALID_HANDLE_VALUE )
	{
		DWORD		dwReadLen;

		ReadFile(hFile, &mMSCutwnd_nMagicNum, sizeof(INT)*4*12, &dwReadLen, NULL);
		ReadFile(hFile, &mMSCutwnd_nTabNum, sizeof(INT), &dwReadLen, NULL);

		CloseHandle(hFile);
		return TRUE;
	}
	return FALSE;
}

/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"
char*	g_pszFileList[150];



/******************************************************************************************************************

	CImageHandler Class

*******************************************************************************************************************/
/******************************************************************************************************************

	함수명 : CImageHandler::CImageHandler()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
CImageHandler::CImageHandler()
{
	INT		nCnt;

	ZeroMemory(m_xImageList, sizeof(CWHWilImageData)*_MAX_IMAGE);

	ZeroMemory(m_nLoadedMagic, sizeof(INT)*_MAX_MAGIC);

	for ( nCnt = 0; nCnt < _MAX_TEXTR_FILE; nCnt++ )
	{
		m_xTextrFileList[nCnt].ClearAllNodes();
	}
}



/******************************************************************************************************************

	함수명 : CImageHandler::~CImageHandler()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
CImageHandler::~CImageHandler()
{
	DeleteAllImage();
}



/******************************************************************************************************************

	함수명 : CImageHandler::LoadAllImage()

	작성자 : 
	작성일 : 

	목적   : 
	입력   : BOOL bIsMemMapped
	         BOOL bComp
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CImageHandler::LoadAllImage(BOOL bIsMemMapped, BOOL bComp)
{
	/* IMAGE DEFINE문과 일치해야한다.--------------------------------------------------------------*/
	CHAR* szFileList[] = 
	{
		".\\Data\\tilesc.wil",								//0
		".\\Data\\tiles30c.wil",							//1
		".\\Data\\Tiles5c.wil",								//2
		".\\Data\\smtilesc.wil",							//3
		".\\Data\\housesc.wil",								//4
		".\\Data\\cliffsc.wil",								//5
		".\\Data\\dungeonsc.wil",							//6
		".\\Data\\innersc.wil",								//7
		".\\Data\\furnituresc.wil",							//8
		".\\Data\\wallsc.wil",								//9
		".\\Data\\smobjectsc.wil",							//10
		".\\Data\\animationsc.wil",							//11
		".\\Data\\object1c.wil",							//12
		".\\Data\\object2c.wil",							//13

		".\\Data\\Wood\\tilesc.wil",						//14
		".\\Data\\Wood\\tiles30c.wil",						//15
		".\\Data\\Wood\\Tiles5c.wil",						//16
		".\\Data\\Wood\\smtilesc.wil",						//17
		".\\Data\\Wood\\housesc.wil",						//18
		".\\Data\\Wood\\cliffsc.wil",						//19
		".\\Data\\Wood\\dungeonsc.wil",						//20
		".\\Data\\Wood\\innersc.wil",						//21
		".\\Data\\Wood\\furnituresc.wil",					//22
		".\\Data\\Wood\\wallsc.wil",						//23
		".\\Data\\Wood\\smobjectsc.wil",					//24
		".\\Data\\Wood\\animationsc.wil",					//25
		".\\Data\\Wood\\object1c.wil",						//26
		".\\Data\\Wood\\object2c.wil",						//27

		".\\Data\\Sand\\tilesc.wil",						//28
		".\\Data\\Sand\\tiles30c.wil",						//29
		".\\Data\\Sand\\Tiles5c.wil",						//30
		".\\Data\\Sand\\smtilesc.wil",						//31
		".\\Data\\Sand\\housesc.wil",						//32
		".\\Data\\Sand\\cliffsc.wil",						//33
		".\\Data\\Sand\\dungeonsc.wil",						//34
		".\\Data\\Sand\\innersc.wil",						//35
		".\\Data\\Sand\\furnituresc.wil",					//36
		".\\Data\\Sand\\wallsc.wil",						//37
		".\\Data\\Sand\\smobjectsc.wil",					//38
		".\\Data\\Sand\\animationsc.wil",					//39
		".\\Data\\Sand\\object1c.wil",						//40
		".\\Data\\Sand\\object2c.wil",						//41

		".\\Data\\Snow\\tilesc.wil",						//42
		".\\Data\\Snow\\tiles30c.wil",						//43
		".\\Data\\Snow\\Tiles5c.wil",						//44
		".\\Data\\Snow\\smtilesc.wil",						//45
		".\\Data\\Snow\\housesc.wil",						//46
		".\\Data\\Snow\\cliffsc.wil",						//47
		".\\Data\\Snow\\dungeonsc.wil",						//48
		".\\Data\\Snow\\innersc.wil",						//49
		".\\Data\\Snow\\furnituresc.wil",					//50
		".\\Data\\Snow\\wallsc.wil",						//51
		".\\Data\\Snow\\smobjectsc.wil",					//52
		".\\Data\\Snow\\animationsc.wil",					//53
		".\\Data\\Snow\\object1c.wil",						//54
		".\\Data\\Snow\\object2c.wil",						//55

		".\\Data\\Forest\\tilesc.wil",						//56
		".\\Data\\Forest\\tiles30c.wil",					//57
		".\\Data\\Forest\\Tiles5c.wil",						//58
		".\\Data\\Forest\\smtilesc.wil",					//59
		".\\Data\\Forest\\housesc.wil",						//60
		".\\Data\\Forest\\cliffsc.wil",						//61
		".\\Data\\Forest\\dungeonsc.wil",					//62
		".\\Data\\Forest\\innersc.wil",						//63
		".\\Data\\Forest\\furnituresc.wil",					//64
		".\\Data\\Forest\\wallsc.wil",						//65
		".\\Data\\Forest\\smobjectsc.wil",					//66
		".\\Data\\Forest\\animationsc.wil",					//67
		".\\Data\\Forest\\object1c.wil",					//68
		".\\Data\\Forest\\object2c.wil",					//69

		".\\Data\\GameInter.wil",							//70
		".\\Data\\M-Hum.wil",								//71
		".\\Data\\M-Weapon1.wil",							//72
		".\\Data\\M-Weapon2.wil",							//73
		".\\Data\\M-Weapon3.wil",							//74
		".\\Data\\M-Weapon4.wil",							//75
		".\\Data\\M-Weapon5.wil",							//76
		".\\Data\\WM-Hum.wil",								//77
		".\\Data\\WM-Weapon1.wil",							//78
		".\\Data\\WM-Weapon2.wil",							//79
		".\\Data\\WM-Weapon3.wil",							//80
		".\\Data\\WM-Weapon4.wil",							//81
		".\\Data\\WM-Weapon5.wil",							//82

		".\\Data\\Magic.wil",								//83
		".\\Data\\Inventory.wil",							//84
		".\\Data\\Equip.wil",								//85
		".\\Data\\Ground.wil",								//86
		".\\Data\\MIcon.wil",								//87
		".\\Data\\ProgUse.wil",								//88
		".\\Data\\Horse.wil",								//89

		".\\Data\\Mon-1.wil",								//90
		".\\Data\\Mon-2.wil",								//91
		".\\Data\\Mon-3.wil",								//92
		".\\Data\\Mon-4.wil",								//93
		".\\Data\\Mon-5.wil",								//94
		".\\Data\\Mon-6.wil",								//95
		".\\Data\\Mon-7.wil",								//96
		".\\Data\\Mon-8.wil",								//97
		".\\Data\\Mon-9.wil",								//98
		".\\Data\\Mon-10.wil",								//99
		".\\Data\\Mon-11.wil",								//100
		".\\Data\\Mon-12.wil",								//101
		".\\Data\\Mon-13.wil",								//102
		".\\Data\\Mon-14.wil",								//103
		".\\Data\\Mon-15.wil",								//104
		".\\Data\\Mon-16.wil",								//105
		".\\Data\\Mon-17.wil",								//106
		".\\Data\\Mon-18.wil",								//107
		".\\Data\\Mon-19.wil",								//108
		".\\Data\\Mon-20.wil",								//109
		".\\Data\\MonS-1.wil",								//110
		".\\Data\\MonS-2.wil",								//111
		".\\Data\\MonS-3.wil",								//112
		".\\Data\\MonS-4.wil",								//113
		".\\Data\\MonS-5.wil",								//114
		".\\Data\\MonS-6.wil",								//115
		".\\Data\\MonS-7.wil",								//116
		".\\Data\\MonS-8.wil",								//117
		".\\Data\\MonS-9.wil",								//118
		".\\Data\\MonS-10.wil",								//119
		".\\Data\\MonS-11.wil",								//120
		".\\Data\\MonS-12.wil",								//121
		".\\Data\\MonS-13.wil",								//122
		".\\Data\\MonS-14.wil",								//123
		".\\Data\\MonS-15.wil",								//124
		".\\Data\\MonS-16.wil",								//125
		".\\Data\\MonS-17.wil",								//126
		".\\Data\\MonS-18.wil",								//127
		".\\Data\\MonS-19.wil",								//128
		".\\Data\\MonS-20.wil",								//129

		".\\Data\\NPC.wil",									//130
		".\\Data\\MonMagic.wil",							//131
		".\\Data\\MonImg.wil",								//132	밍膠庫獗
		".\\Data\\M-Hair.wil",								//133
		".\\Data\\M-Helmet1.wil",							//134
		".\\Data\\WM-Hair.wil",								//135
		".\\Data\\WM-Helmet1.wil",							//136
		".\\Data\\DMon-1.wil",								//137
		".\\Data\\DMonS-1.wil",								//138
		".\\Data\\MagicEx.wil",								//139
		".\\Data\\MonMagicEx.wil",							//140
		".\\Data\\StoreItem.wil",							//141
		".\\Data\\MonMagicEx2.wil",							//142
		".\\Data\\Mon-54.wil",								//143
		".\\Data\\Flag.wil",								//144
		".\\Data\\MonMagicEx3.wil",							//145
		".\\Data\\M-Helmet2.wil",							//146
		".\\Data\\WM-Helmet2.wil",							//147
		".\\Data\\MonMagicEx4.wil",							//148
		".\\Data\\MagicEx2.wil"								//149
	};

	InitAllImage();

	memcpy( g_pszFileList, szFileList, _MAX_IMAGE*sizeof(char*) );
	for ( INT nCnt = 0; nCnt < 14; nCnt++ )
		m_xImageList[nCnt].NewLoad(szFileList[nCnt], false);

	for ( INT nCnt = 70; nCnt < 141; nCnt++ )
		m_xImageList[nCnt].NewLoad(szFileList[nCnt], true);

}


VOID CImageHandler::InitAllImage()
{
	INT nCnt;
	for ( nCnt = 0; nCnt < _MAX_IMAGE; nCnt++ )
		m_xImageList[nCnt].Init();

	ZeroMemory(m_nLoadedMagic, sizeof(INT)*_MAX_MAGIC);

 	D3DVECTOR vNorm(0, 0, -1);
	m_avBillBoard[0]  = D3DVERTEX(D3DVECTOR(-0.5f, 0.5f, 0), vNorm, 0, 0);
	m_avBillBoard[1]  = D3DVERTEX(D3DVECTOR(-0.5f,-0.5f, 0), vNorm, 0, 1);
	m_avBillBoard[2]  = D3DVERTEX(D3DVECTOR( 0.5f, 0.5f, 0), vNorm, 1, 0);
	m_avBillBoard[3]  = D3DVERTEX(D3DVECTOR( 0.5f,-0.5f, 0), vNorm, 1, 1);

	for ( nCnt = 0; nCnt < _MAX_TEXTR_FILE; nCnt++ )
	{
		m_xTextrFileList[nCnt].ClearAllNodes();
	}
}


/******************************************************************************************************************

	함수명 : CImageHandler::DeleteAllImage()

	작성자 : 
	작성일 : 

	목적   : 
	출력   : VOID 

	[일자][수정자] : 수정내용

*******************************************************************************************************************/
VOID CImageHandler::DeleteAllImage()
{
	INT nCnt;

	for ( nCnt = 0; nCnt < _MAX_IMAGE; nCnt++ )
		m_xImageList[nCnt].Destroy();

	ZeroMemory(m_nLoadedMagic, sizeof(INT)*_MAX_MAGIC);

	for ( nCnt = 0; nCnt < _MAX_TEXTR_FILE; nCnt++ )
	{
		m_xTextrFileList[nCnt].ClearAllNodes();
	}
}





VOID CImageHandler::AddTextr(WORD wFileType, WORD wFileIdx, WORD wImgIdx)
{
	if ( wFileType < _MAX_TEXTR_FILE )
	{
		if ( m_xImageList[wFileIdx].NewSetIndex(wImgIdx) )
		{
			if ( D3DWILTextr_CreateEmptyTexture(m_xImageList[wFileIdx].m_szWilFileName, wImgIdx, 
											    m_xImageList[wFileIdx].m_lpstNewCurrWilImageInfo->shWidth,
												m_xImageList[wFileIdx].m_lpstNewCurrWilImageInfo->shHeight,
												(WORD*)m_xImageList[wFileIdx].m_pbCurrImage, D3DTEXTR_TRANSPARENTBLACK) )
			{
				LPTEXTUREFILE pstTexFile = new TEXTUREFILE;
				pstTexFile->wFileIdx	 = wFileIdx;
				pstTexFile->wImgIdx		 = wImgIdx;
				pstTexFile->lpddsTextr	 = D3DWILTextr_RestoreEx(m_xImageList[wFileIdx].m_szWilFileName, wImgIdx, g_xMainWnd.Get3DDevice());

				m_xTextrFileList[wFileType].AddNode(pstTexFile);

				return;
			}
		}		
	}
}

VOID CImageHandler::DelTextr(WORD wFileType, WORD wFileIdx, WORD wImgIdx)
{
	if ( wFileType < _MAX_TEXTR_FILE )
	{
		D3DWILTextr_Invalidate(m_xImageList[wFileIdx].m_szWilFileName, wImgIdx);
		D3DWILTextr_DestroyTexture(m_xImageList[wFileIdx].m_szWilFileName, wImgIdx);

		m_xTextrFileList[wFileType].MoveCurrentToTop();
		for ( INT nCnt = 0; nCnt < m_xTextrFileList[wFileType].GetCounter(); nCnt++ )
		{
			LPTEXTUREFILE pstTexFile = m_xTextrFileList[wFileType].GetCurrentData();

			if ( pstTexFile->wFileIdx == wFileIdx && pstTexFile->wImgIdx == wImgIdx )
			{
				m_xTextrFileList[wFileType].DeleteCurrentNodeEx();
				return;
			}

			m_xTextrFileList[wFileType].MoveNextNode();
		}
	}
}

LPDIRECTDRAWSURFACE7 CImageHandler::GetTextrImg(WORD wFileType, WORD wFileIdx, WORD wImgIdx)
{
	if ( wFileType < _MAX_TEXTR_FILE )
	{
		m_xTextrFileList[wFileType].MoveCurrentToTop();
		for ( INT nCnt = 0; nCnt < m_xTextrFileList[wFileType].GetCounter(); nCnt++ )
		{
			LPTEXTUREFILE pstTexFile = m_xTextrFileList[wFileType].GetCurrentData();

			if ( pstTexFile->wFileIdx == wFileIdx && pstTexFile->wImgIdx == wImgIdx )
			{
				return pstTexFile->lpddsTextr;				
			}

			m_xTextrFileList[wFileType].MoveNextNode();
		}
	}

	return NULL;
}

VOID CImageHandler::DelAllTextrFileList()
{
	INT		nCnt;
	for ( nCnt = 0; nCnt < _MAX_TEXTR_FILE; nCnt++ )
	{
		m_xTextrFileList[nCnt].ClearAllNodes();
	}
}



HRESULT CImageHandler::DrawBillBoard(LPDIRECT3DDEVICE7 lpDevice, D3DVECTOR vTrans, D3DVECTOR vScale, /*D3DVECTOR vRot, */D3DMATERIAL7 mtrl, /*FLOAT fRotRad, */LPDIRECTDRAWSURFACE7 lpddsTextr)
{
	if ( lpDevice )
	{
		if( SUCCEEDED(lpDevice->BeginScene()) )
		{
			D3DMATRIX matTrans;
			D3DMATRIX matScale;
			D3DMATRIX matRot;

			D3DMATRIX matWorld;
			D3DMATRIX matTempWorld;

			D3DMATRIX matWorldOriginal;

			lpDevice->GetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

			vTrans.x = vTrans.x+vScale.x/2-400;
			vTrans.y = -vTrans.y-vScale.y/2+300;

			D3DUtil_SetTranslateMatrix(matTrans, vTrans);
			D3DUtil_SetScaleMatrix(matScale, vScale.x, vScale.y, vScale.z);
//			D3DUtil_SetRotationMatrix(matRot, vRot, fRotRad);
			D3DMath_MatrixMultiply(/*matTempWorld*/matWorld, matScale, matTrans);
//			D3DMath_MatrixMultiply(matWorld, matRot, matTempWorld);
			lpDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);

			SetBlendRenderState(lpDevice, _BLEND_NORMAL, mtrl);
			lpDevice->SetMaterial(&mtrl);

			lpDevice->SetTexture(0, lpddsTextr);

			lpDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_VERTEX, m_avBillBoard, 4, NULL);

			// 원상복귀.
			ZeroMemory(&mtrl, sizeof(mtrl));
			mtrl.diffuse.r = mtrl.diffuse.g = mtrl.diffuse.b = 0.1f;
			mtrl.ambient.r = mtrl.ambient.g = mtrl.ambient.b = 1.0f;
			lpDevice->SetMaterial(&mtrl);

			ResetBlendenderState(lpDevice);
			lpDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);
		}
		lpDevice->EndScene();
		return S_OK;
	}
	return E_FAIL;
}

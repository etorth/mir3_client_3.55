/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#include "StdAfx.h"



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
: m_helper( m_xImageList )
{
	ZeroMemory(m_xImageList, sizeof(CWHWilImageData)*_MAX_IMAGE);
	ZeroMemory(m_pszFileList, _MAX_IMAGE*MAX_PATH);
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
	InitAllImage();

/*	for ( INT nCnt = 0; nCnt < 4; nCnt++ )
	{
		m_xImageList[nCnt].NewLoad(m_pszFileList[nCnt]);
	}
*/
	for ( INT nCnt = 0; nCnt < 14; nCnt++ )
	{
		if ( !m_xImageList[nCnt].NewLoad(m_pszFileList[nCnt], 1) )
		{
			m_xImageList[nCnt].Destroy();
			m_xImageList[nCnt].NewLoad(m_pszFileList[nCnt]);
		}
	}

	for ( nCnt = 70; nCnt < _MAX_IMAGE; nCnt++ )
	{
		m_xImageList[nCnt].NewLoad(m_pszFileList[nCnt]);
	}
}


VOID CImageHandler::InitAllImage()
{
	/* IMAGE DEFINE문과 일치해야한다.--------------------------------------------------------------*/
	//~~~ 배경이미지. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	strcpy(m_pszFileList[0], ".\\Data\\tilesc.wil");							//0
	strcpy(m_pszFileList[1], ".\\Data\\tiles30c.wil");							//1
	strcpy(m_pszFileList[2], ".\\Data\\Tiles5c.wil");							//2
	strcpy(m_pszFileList[3], ".\\Data\\smtilesc.wil");							//3
	strcpy(m_pszFileList[4], ".\\Data\\housesc.wil");							//4
	strcpy(m_pszFileList[5], ".\\Data\\cliffsc.wil");							//5
	strcpy(m_pszFileList[6], ".\\Data\\dungeonsc.wil");							//6
	strcpy(m_pszFileList[7], ".\\Data\\innersc.wil");							//7
	strcpy(m_pszFileList[8], ".\\Data\\furnituresc.wil");						//8
	strcpy(m_pszFileList[9], ".\\Data\\wallsc.wil");							//9
	strcpy(m_pszFileList[10], ".\\Data\\smobjectsc.wil");						//10
	strcpy(m_pszFileList[11], ".\\Data\\animationsc.wil");						//11
	strcpy(m_pszFileList[12], ".\\Data\\object1c.wil");							//12
	strcpy(m_pszFileList[13], ".\\Data\\object2c.wil");							//13
	// 푸른지역.
	strcpy(m_pszFileList[14], ".\\Data\\Wood\\tilesc.wil");						//14
	strcpy(m_pszFileList[15], ".\\Data\\Wood\\tiles30c.wil");					//15
	strcpy(m_pszFileList[16], ".\\Data\\Wood\\Tiles5c.wil");					//16
	strcpy(m_pszFileList[17], ".\\Data\\Wood\\smtilesc.wil");					//17
	strcpy(m_pszFileList[18], ".\\Data\\Wood\\housesc.wil");					//18
	strcpy(m_pszFileList[19], ".\\Data\\Wood\\cliffsc.wil");					//19
	strcpy(m_pszFileList[20], ".\\Data\\Wood\\dungeonsc.wil");					//20
	strcpy(m_pszFileList[21], ".\\Data\\Wood\\innersc.wil");					//21
	strcpy(m_pszFileList[22], ".\\Data\\Wood\\furnituresc.wil");				//22
	strcpy(m_pszFileList[23], ".\\Data\\Wood\\wallsc.wil");						//23
	strcpy(m_pszFileList[24], ".\\Data\\Wood\\smobjectsc.wil");					//24
	strcpy(m_pszFileList[25], ".\\Data\\Wood\\animationsc.wil");				//25
	strcpy(m_pszFileList[26], ".\\Data\\Wood\\object1c.wil");					//26
	strcpy(m_pszFileList[27], ".\\Data\\Wood\\object2c.wil");					//27
	// 사막지역.
	strcpy(m_pszFileList[28], ".\\Data\\Sand\\tilesc.wil");						//28
	strcpy(m_pszFileList[29], ".\\Data\\Sand\\tiles30c.wil");					//29
	strcpy(m_pszFileList[30], ".\\Data\\Sand\\Tiles5c.wil");					//30
	strcpy(m_pszFileList[31], ".\\Data\\Sand\\smtilesc.wil");					//31
	strcpy(m_pszFileList[32], ".\\Data\\Sand\\housesc.wil");					//32
	strcpy(m_pszFileList[33], ".\\Data\\Sand\\cliffsc.wil");					//33
	strcpy(m_pszFileList[34], ".\\Data\\Sand\\dungeonsc.wil");					//34
	strcpy(m_pszFileList[35], ".\\Data\\Sand\\innersc.wil");					//35
	strcpy(m_pszFileList[36], ".\\Data\\Sand\\furnituresc.wil");				//36
	strcpy(m_pszFileList[37], ".\\Data\\Sand\\wallsc.wil");						//37
	strcpy(m_pszFileList[38], ".\\Data\\Sand\\smobjectsc.wil");					//38
	strcpy(m_pszFileList[39], ".\\Data\\Sand\\animationsc.wil");				//39
	strcpy(m_pszFileList[40], ".\\Data\\Sand\\object1c.wil");					//40
	strcpy(m_pszFileList[41], ".\\Data\\Sand\\object2c.wil");					//41

	// 설원지역.
	strcpy(m_pszFileList[42], ".\\Data\\Snow\\tilesc.wil");						//42
	strcpy(m_pszFileList[43], ".\\Data\\Snow\\tiles30c.wil");					//43
	strcpy(m_pszFileList[44], ".\\Data\\Snow\\Tiles5c.wil");					//44
	strcpy(m_pszFileList[45], ".\\Data\\Snow\\smtilesc.wil");					//45
	strcpy(m_pszFileList[46], ".\\Data\\Snow\\housesc.wil");					//46
	strcpy(m_pszFileList[47], ".\\Data\\Snow\\cliffsc.wil");					//47
	strcpy(m_pszFileList[48], ".\\Data\\Snow\\dungeonsc.wil");					//48
	strcpy(m_pszFileList[49], ".\\Data\\Snow\\innersc.wil");					//49
	strcpy(m_pszFileList[50], ".\\Data\\Snow\\furnituresc.wil");				//50
	strcpy(m_pszFileList[51], ".\\Data\\Snow\\wallsc.wil");						//51
	strcpy(m_pszFileList[52], ".\\Data\\Snow\\smobjectsc.wil");					//52
	strcpy(m_pszFileList[53], ".\\Data\\Snow\\animationsc.wil");				//53
	strcpy(m_pszFileList[54], ".\\Data\\Snow\\object1c.wil");					//54
	strcpy(m_pszFileList[55], ".\\Data\\Snow\\object2c.wil");					//55

	// 정글지역.
	strcpy(m_pszFileList[56], ".\\Data\\Forest\\tilesc.wil");					//56
	strcpy(m_pszFileList[57], ".\\Data\\Forest\\tiles30c.wil");					//57
	strcpy(m_pszFileList[58], ".\\Data\\Forest\\Tiles5c.wil");					//58
	strcpy(m_pszFileList[59], ".\\Data\\Forest\\smtilesc.wil");					//59
	strcpy(m_pszFileList[60], ".\\Data\\Forest\\housesc.wil");					//60
	strcpy(m_pszFileList[61], ".\\Data\\Forest\\cliffsc.wil");					//61
	strcpy(m_pszFileList[62], ".\\Data\\Forest\\dungeonsc.wil");				//62
	strcpy(m_pszFileList[63], ".\\Data\\Forest\\innersc.wil");					//63
	strcpy(m_pszFileList[64], ".\\Data\\Forest\\furnituresc.wil");				//64
	strcpy(m_pszFileList[65], ".\\Data\\Forest\\wallsc.wil");					//65
	strcpy(m_pszFileList[66], ".\\Data\\Forest\\smobjectsc.wil");				//66
	strcpy(m_pszFileList[67], ".\\Data\\Forest\\animationsc.wil");				//67
	strcpy(m_pszFileList[68], ".\\Data\\Forest\\object1c.wil");					//68
	strcpy(m_pszFileList[69], ".\\Data\\Forest\\object2c.wil");					//69

	//~~~ 인터페이스이미지. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	strcpy(m_pszFileList[70], ".\\Data\\GameInter.wil");						//70 

	//~~~ 남자이미지. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	strcpy(m_pszFileList[71], ".\\Data\\M-Hum.wil");							//71 	
	strcpy(m_pszFileList[72], ".\\Data\\M-Weapon1.wil");						//72
	strcpy(m_pszFileList[73], ".\\Data\\M-Weapon2.wil");						//73
	strcpy(m_pszFileList[74], ".\\Data\\M-Weapon3.wil");						//74
	strcpy(m_pszFileList[75], ".\\Data\\M-Weapon4.wil");						//75

	//~~~ 여자이미지. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	strcpy(m_pszFileList[76], ".\\Data\\WM-Hum.wil");							//76
	strcpy(m_pszFileList[77], ".\\Data\\WM-Weapon1.wil");						//77
	strcpy(m_pszFileList[78], ".\\Data\\WM-Weapon2.wil");						//78
	strcpy(m_pszFileList[79], ".\\Data\\WM-Weapon3.wil");						//79
	strcpy(m_pszFileList[80], ".\\Data\\WM-Weapon4.wil");						//80

	//~~~ 아이템 및 인터페이스, 마법, 기타이미지. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	strcpy(m_pszFileList[81], ".\\Data\\Magic.wil");							//81
	strcpy(m_pszFileList[82], ".\\Data\\Inventory.wil");						//82
	strcpy(m_pszFileList[83], ".\\Data\\Equip.wil");							//83
	strcpy(m_pszFileList[84], ".\\Data\\Ground.wil");							//84
	strcpy(m_pszFileList[85], ".\\Data\\MIcon.wil");							//85
	strcpy(m_pszFileList[86], ".\\Data\\ProgUse.wil");							//86
	strcpy(m_pszFileList[87], ".\\Data\\Horse.wil");							//87

	//~~~ 몬스터이미지. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	strcpy(m_pszFileList[88], ".\\Data\\Mon-1.wil");							//88
	strcpy(m_pszFileList[89], ".\\Data\\Mon-2.wil");							//89
	strcpy(m_pszFileList[90], ".\\Data\\Mon-3.wil");							//90
	strcpy(m_pszFileList[91], ".\\Data\\Mon-4.wil");							//91
	strcpy(m_pszFileList[92], ".\\Data\\Mon-5.wil");							//92
	strcpy(m_pszFileList[93], ".\\Data\\Mon-6.wil");							//93
	strcpy(m_pszFileList[94], ".\\Data\\Mon-7.wil");							//94
	strcpy(m_pszFileList[95], ".\\Data\\Mon-8.wil");							//95
	strcpy(m_pszFileList[96], ".\\Data\\Mon-9.wil");							//96
	strcpy(m_pszFileList[97], ".\\Data\\Mon-10.wil");							//97
	strcpy(m_pszFileList[98], ".\\Data\\Mon-11.wil");							//98
	strcpy(m_pszFileList[99], ".\\Data\\Mon-12.wil");							//99
	strcpy(m_pszFileList[100], ".\\Data\\Mon-13.wil");							//100
	strcpy(m_pszFileList[101], ".\\Data\\Mon-14.wil");							//101
	strcpy(m_pszFileList[102], ".\\Data\\Mon-15.wil");							//102
	strcpy(m_pszFileList[103], ".\\Data\\Mon-16.wil");							//103				
	strcpy(m_pszFileList[104], ".\\Data\\Mon-17.wil");							//104
	strcpy(m_pszFileList[105], ".\\Data\\Mon-18.wil");							//105
	strcpy(m_pszFileList[106], ".\\Data\\Mon-19.wil");							//106
	strcpy(m_pszFileList[107], ".\\Data\\Mon-20.wil");							//107

	//~~~ 몬스터그림자이미지. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	strcpy(m_pszFileList[108], ".\\Data\\MonS-1.wil");							//108
	strcpy(m_pszFileList[109], ".\\Data\\MonS-2.wil");							//109
	strcpy(m_pszFileList[110], ".\\Data\\MonS-3.wil");							//110
	strcpy(m_pszFileList[111], ".\\Data\\MonS-4.wil");							//111
	strcpy(m_pszFileList[112], ".\\Data\\MonS-5.wil");							//112
	strcpy(m_pszFileList[113], ".\\Data\\MonS-6.wil");							//113
	strcpy(m_pszFileList[114], ".\\Data\\MonS-7.wil");							//114
	strcpy(m_pszFileList[115], ".\\Data\\MonS-8.wil");							//115
	strcpy(m_pszFileList[116], ".\\Data\\MonS-9.wil");							//116
	strcpy(m_pszFileList[117], ".\\Data\\MonS-10.wil");							//117
	strcpy(m_pszFileList[118], ".\\Data\\MonS-11.wil");							//118
	strcpy(m_pszFileList[119], ".\\Data\\MonS-12.wil");							//119
	strcpy(m_pszFileList[120], ".\\Data\\MonS-13.wil");							//120
	strcpy(m_pszFileList[121], ".\\Data\\MonS-14.wil");							//121
	strcpy(m_pszFileList[122], ".\\Data\\MonS-15.wil");							//122
	strcpy(m_pszFileList[123], ".\\Data\\MonS-16.wil");							//123
	strcpy(m_pszFileList[124], ".\\Data\\MonS-17.wil");							//124
	strcpy(m_pszFileList[125], ".\\Data\\MonS-18.wil");							//125
	strcpy(m_pszFileList[126], ".\\Data\\MonS-19.wil");							//126
	strcpy(m_pszFileList[127], ".\\Data\\MonS-20.wil");							//127

	//~~~ NPC 이미지. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	strcpy(m_pszFileList[128], ".\\Data\\NPC.wil");								//128

	//~~~ 몬스터마법 이미지. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	strcpy(m_pszFileList[129], ".\\Data\\MonMagic.wil");						//129
	strcpy(m_pszFileList[130], ".\\Data\\MonImg.wil");							//130
	strcpy(m_pszFileList[131], ".\\Data\\M-Hair.wil");							//131
	strcpy(m_pszFileList[132], ".\\Data\\M-Helmet1.wil");						//132	
	strcpy(m_pszFileList[133], ".\\Data\\WM-Hair.wil");							//133
	strcpy(m_pszFileList[134], ".\\Data\\WM-Helmet1.wil");						//134

	//~~~ 염색몬스터. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	strcpy(m_pszFileList[135], ".\\Data\\DMon-1.wil");							//135
	strcpy(m_pszFileList[136], ".\\Data\\DMonS-1.wil");							//136

	strcpy(m_pszFileList[137], ".\\Data\\MagicEx.wil");							//137
	strcpy(m_pszFileList[138], ".\\Data\\MonMagicEx.wil");						//138
	strcpy(m_pszFileList[139], ".\\Data\\StoreItem.wil");						//139
	strcpy(m_pszFileList[140], ".\\Data\\MonMagicEx2.wil");						//140

	//~~~ 사북성문. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	strcpy(m_pszFileList[141], ".\\Data\\Mon-54.wil");							//141

	//~~~ 깃발 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	strcpy(m_pszFileList[142], ".\\Data\\Flag.wil");							//142

	//~~~ MonMagicEx3 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	strcpy(m_pszFileList[143], ".\\Data\\MonMagicEx3.wil");						//143

	//~~~ 헬멧 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	strcpy(m_pszFileList[144], ".\\Data\\M-Helmet2.wil");						//144
	strcpy(m_pszFileList[145], ".\\Data\\WM-Helmet2.wil");						//145

	//~~~ 무기 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	strcpy(m_pszFileList[146], ".\\Data\\M-Weapon5.wil");						//146
	strcpy(m_pszFileList[147], ".\\Data\\WM-Weapon5.wil");						//147

	//~~~ MonMagicEx4 (누마공성전) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	strcpy(m_pszFileList[148], ".\\Data\\MonMagicEx4.wil");						//148

	//~~~ MonMagicEx4 (누마공성전) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	strcpy(m_pszFileList[149], ".\\Data\\MagicEx2.wil");						//149

	strcpy(m_pszFileList[150], ".\\Data\\Mon-21.wil");							//150
	strcpy(m_pszFileList[151], ".\\Data\\MonS-21.wil");							//151

	strcpy(m_pszFileList[152], ".\\Data\\HorseS.wil");							//152
	strcpy(m_pszFileList[153], ".\\Data\\M-Weapon10.wil");						//153
	strcpy(m_pszFileList[154], ".\\Data\\WM-Weapon10.wil");						//154

	strcpy(m_pszFileList[155], ".\\Data\\Mon-22.wil");							//155
	strcpy(m_pszFileList[156], ".\\Data\\MonS-22.wil");							//156

	strcpy(m_pszFileList[157], ".\\Data\\MagicEx3.wil");						//157

	strcpy(m_pszFileList[158], ".\\Data\\MonMagicEx5.wil");						//158

	strcpy(m_pszFileList[159], ".\\Data\\GameInter1.wil");						//159

//	strcpy(m_pszFileList[160], ".\\Data\\M-SHum.wil");							//160
//	strcpy(m_pszFileList[161], ".\\Data\\WM-SHum.wil");							//160

	for ( INT nCnt = 0; nCnt < _MAX_IMAGE; nCnt++ )
	{
		m_xImageList[nCnt].Init();
	}

 	D3DVECTOR vNorm(0, 0, -1);
	m_avBillBoard[0]  = D3DVERTEX(D3DVECTOR(-0.5f, 0.5f, 0), vNorm, 0, 0);
	m_avBillBoard[1]  = D3DVERTEX(D3DVECTOR(-0.5f,-0.5f, 0), vNorm, 0, 1);
	m_avBillBoard[2]  = D3DVERTEX(D3DVECTOR( 0.5f, 0.5f, 0), vNorm, 1, 0);
	m_avBillBoard[3]  = D3DVERTEX(D3DVECTOR( 0.5f,-0.5f, 0), vNorm, 1, 1);
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
	{
		m_xImageList[nCnt].Destroy();
	}

	DelAllTextrFileList();
}

LPDIRECTDRAWSURFACE7 CImageHandler::AddTextr(WORD wFileType, WORD wFileIdx, INT nImgIdx)
{
	if ( wFileType >= _MAX_TEXTR_FILE || wFileIdx >= _MAX_IMAGE )
	{
		return NULL;
	}

	return m_helper.AddTexture( wFileType, wFileIdx, (WORD)nImgIdx );
}

LPDIRECTDRAWSURFACE7 CImageHandler::GetTextrImg(WORD wFileType, WORD wFileIdx, INT nImgIdx)
{
	if ( wFileType >= _MAX_TEXTR_FILE || wFileIdx >= _MAX_IMAGE )
	{
		return NULL;
	}

	return m_helper.GetTexture( wFileType, wFileIdx, (WORD)nImgIdx );
}

VOID CImageHandler::DelAllTextrFileList()
{
	m_helper.DelAllTexture();
}



HRESULT CImageHandler::DrawBillBoard(LPDIRECT3DDEVICE7 lpDevice, D3DVECTOR* pvTrans, D3DVECTOR* pvScale, /*D3DVECTOR vRot, */D3DMATERIAL7* pmtrl, /*FLOAT fRotRad, */LPDIRECTDRAWSURFACE7 lpddsTextr, BYTE bBlendType)
{
	if ( lpDevice )
	{
		D3DMATRIX matTrans;
		D3DMATRIX matScale;
		D3DMATRIX matRot;
		D3DMATRIX matWorld;
		D3DMATRIX matWorldOriginal;

		pvTrans->x = pvTrans->x+pvScale->x/2-400;
		pvTrans->y = -pvTrans->y-pvScale->y/2+300;
		lpDevice->SetMaterial(pmtrl);

		if( SUCCEEDED(lpDevice->BeginScene()) )
		{
			lpDevice->GetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

			D3DUtil_SetTranslateMatrix(matTrans, *pvTrans);
			D3DUtil_SetScaleMatrix(matScale, pvScale->x, pvScale->y, pvScale->z);
			D3DMath_MatrixMultiply(matWorld, matScale, matTrans);
			lpDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);

			SetBlendRenderState(lpDevice, bBlendType, pmtrl);

			lpDevice->SetTexture(0, lpddsTextr);

			lpDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_VERTEX, m_avBillBoard, 4, NULL);

			ResetBlendenderState(lpDevice);

			lpDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorldOriginal);

			lpDevice->EndScene();

			return S_OK;
		}
	}
	return E_FAIL;
}

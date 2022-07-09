/******************************************************************************************************************
                                                                                                                   
	모듈명:																											
																													
	작성자:																											
	작성일:																											
																													
	[일자][수정자] : 수정 내용																						
                                                                                                                   
*******************************************************************************************************************/



#ifndef _CIMAGEHANDLER_H
#define _CIMAGEHANDLER_H


#include "ImageHandlerHelper.h"


class CImageHandler
{
public:
	CImageHandler();
	~CImageHandler();

public:
	CWHWilImageData			m_xImageList[_MAX_IMAGE];
	CHAR					m_pszFileList[_MAX_IMAGE][MAX_PATH];
	CImageHandlerHelper		m_helper;	

	D3DVERTEX				m_avBillBoard[4];
public:
	VOID InitAllImage();
	VOID LoadAllImage(BOOL bIsMemMapped = TRUE, BOOL bComp = TRUE);
	VOID DeleteAllImage();

	LPDIRECTDRAWSURFACE7 AddTextr(WORD wFileType, WORD wFileIdx, INT nImgIdx);
	LPDIRECTDRAWSURFACE7 GetTextrImg(WORD wFileType, WORD wFileIdx, INT nImgIdx);
	VOID DelAllTextrFileList();
	
	HRESULT DrawBillBoard(LPDIRECT3DDEVICE7 lpDevice, D3DVECTOR* pvTrans, D3DVECTOR* pvScale, /*D3DVECTOR vRot, */D3DMATERIAL7* pmtrl, /*FLOAT fRotRad, */LPDIRECTDRAWSURFACE7 lpddsTextr, BYTE bBlendType = _BLEND_NORMAL);
};



#endif // _CIMAGEHANDLER_H
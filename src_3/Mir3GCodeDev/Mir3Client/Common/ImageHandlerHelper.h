#pragma once


#include <indexmap.h>


// �ؽ� ���̺� ũ��
#define MAX_HASHSIZE	1024
// ��ü ������Ʈ�� �ε��� ����Ʈ �˻� �ֱ�
#define TEXTURE_CHECKALLTIME	60000	
// �� �ð��� ������ �ε����� �����Ѵ�.
#define TEXTURE_SAVETIME		300000


class CImageHandlerHelper
{
public:
	struct sTextureNode
	{
		char					szKey[16];
		WORD					nFileType, nFileIdx, nImgIdx;
		CWHWilImageData*		pImg;
		IDirectDrawSurface7*	pSurface;
		DWORD					nLastTick;
	};
	
	CWHWilImageData	*			m_pListImage;
	DWORD						m_nLastTick;

	CIndexMap< sTextureNode >	m_listTexture;

public:
	CImageHandlerHelper( CWHWilImageData *pListImage );
	virtual ~CImageHandlerHelper();

	void CheckAllCachedTexture();
	void DelAllTexture();

	IDirectDrawSurface7 * AddTexture( WORD nFileType, WORD nFileIdx, WORD nImgIdx );
	IDirectDrawSurface7 * GetTexture( WORD nFileType, WORD nFileIdx, WORD nImgIdx );
	void DelTexture( WORD nFileType, WORD nFileIdx, WORD nImgIdx );	


	HRESULT RestoreImg(sTextureNode* pstTextrNode);
	HRESULT CopyDToSToS(DWORD dwWidth, DWORD dwHeight, WORD* pwSrc, LPDIRECTDRAWSURFACE7 lpDst);
	HRESULT CopyDToS(DWORD dwWidth, DWORD dwHeight, WORD* pwSrc, LPDIRECTDRAWSURFACE7 lpDst);


protected:
	static char * __cbTextureKey( sTextureNode *pNode );	
	sTextureNode * FindTexture( WORD nFileType, WORD nFileIdx, WORD nImgIdx );
};
/******************************************************************************************************************
                                                                                                                   
	����:																											
																													
	�ۼ���:																											
	�ۼ���:																											
																													
	[����][������] : ���� ����																						
                                                                                                                   
*******************************************************************************************************************/


#ifndef _MAPHANDLER_
#define	_MAPHANDLER_


#pragma pack(1)
typedef struct tagRGBINFO
{
	BYTE	bRed;
	BYTE	bGreen;
	BYTE	bBlue;
}RGBINFO, *LPRGBINFO;

typedef struct tagLIGHTINFO
{
	BOOL	bIsLight;
	CHAR	cLightSizeType;
	CHAR	cLightColorType;
}LIGHTINFO, *LPLIGHTINFO;

// ������ �ε����� ��������.
// ���� �ִ� ������ ��ü �ʿ� ���õ� ������ �����Ѵ�.
typedef struct tagMAPFILEHEADER
{
	CHAR	szDesc[20];
	WORD	wAttr;
	SHORT	shWidth;
	SHORT	shHeight;
	CHAR	cEventFileIdx;
	CHAR	cFogColor;
}MAPFILEHEADER, *LPMAPFILEHEADER;

typedef struct tagTILEINFO
{
	BYTE	bFileIdx;
	WORD	wTileIdx;
}TILEINFO, *LPTILEINFO;

typedef struct tagCELLINFO
{
	BYTE	bFlag;
	BYTE	bObj1Ani;
	BYTE	bObj2Ani;
	WORD	wFileIdx;
	WORD	wObj1;
	WORD	wObj2;
	BYTE	bDoorIdx;
	WORD	bDoorOffset;
	WORD	wLigntNEvent;
}CELLINFO, *LPCELLINFO;
/*
typedef struct tagDOORIMAGEINFO
{
	WORD	wPosX;
	WORD	wPosY;
	WORD	wImageNum;
}DOORIMAGEINFO, *LPDOORIMAGEINFO;

typedef struct tagDOORINFO
{
	BYTE			bDoorIdx;
	BYTE			bDoorImgCnt;
	LPDOORIMAGEINFO	pstDoorImgInfo;
}DOORINFO, *LPDOORINFO;
*/
#pragma pack(8)


class CMapHandler
{
private:
protected:
public:
	BOOL			m_bMapLoaded;

	CHAR			m_pszMapName[MAX_PATH];

	LPTILEINFO		m_pstTileInfo;
	LPCELLINFO		m_pstCellInfo;

//	CHAR*			 m_pcPath;
//	CAStar<CMapNode> m_xPathFinder;


	MAPFILEHEADER	m_stMapFileHeader;				// �ε��� �������� ���.

	// ĳ������ �̵��� ���õȴ�.
	INT				m_nStartViewTileX;				// �俵���� ���� X Tile ��ǥ.(���� ��ũ�� ���� Ÿ�� ��ǥ���� ���� �� ū �������̴�.)
	INT				m_nStartViewTileY;				// �俵���� ���� ��ũ�� �������� ����, ���� 1Ÿ�Ͼ��� �������� �д�.
	INT				m_nViewOffsetX;					// ��ũ���� X���� ����.(ĳ������ �ȱ⵿���� ������.)
	INT				m_nViewOffsetY;				

	INT				m_nViewPosX;
	INT				m_nViewPosY;

	RECT			m_rcView;						// �ʱ⺻Ÿ���� �׷��� ����.(ȭ��Ŭ������ ���ؼ�)
	RECT			m_rcMemView;

	POINT			m_ptMovePixelArray[6];			// �̵��� ���� �ȼ����� ��������Ÿ.

	BOOL			m_bUseTileBuffer;				// �����ص� Ÿ�Ϲ����̹����� �̿��Ѱ��ΰ��� ����.

	BYTE			m_bLightSize[4];
	RGBINFO			m_stRGBInfo[10];

	WORD			m_wSavedMapBuffer[_VIEW_CELL_X_COUNT*_CELL_WIDTH*_VIEW_CELL_Y_COUNT*_CELL_HEIGHT];				// �⺻Ÿ�ϰ� SMŸ���� ����� ����. �ڱ� ĳ���Ͱ� �̵��ϱ����� ���ŵ��� �ʴ´�.


	DWORD			m_dwAniSaveTime[8];
	BYTE			m_bAniTileFrame[8][16];

	CWHWilImageData*	m_pxTileImg[_MAX_TILE_FILE];
/*
	BYTE			m_bDoorCount;
	LPDOORINFO		m_pstDoorInfo;
	BYTE*			m_pbCellIDoorIdx;
*/

public:
	CMapHandler();
	~CMapHandler();
	VOID			InitMapHandler();				// Ŭ���� ���� �ʱ�ȭ.
	VOID			DestroyMapHandler();			// Ŭ���� ���� �ʱ�ȭ�� �޸� ����.

	VOID			LoadMemViewBuffer(INT nX, INT nY/*, INT nLoopTime*/);

	BOOL			LoadMapData(CHAR* szMapFile);	// ����Ǵ� ���� ����Ÿ�� �ε�.(���� �ٲ𶧸��� �ҷ�����.)
	VOID			LoadNewMapBuffer();				// ���� ó�� �ε��Ǿ����� Ÿ��, SMŸ�� ��Ϲ��ۿ� ������ ������ �����Ѵ�.

	VOID			FreeMapData();					// ����Ǵ� ���� ����Ÿ�� ����.(���� �ٲ𶧸��� �ҷ�����.)

	VOID			DrawBaseTile(INT nX, INT nY);	// �⺻Ÿ���� �׸���.
	VOID			DrawObjTile(INT nX, INT nY, BYTE bObjNum);
	VOID			DrawObjOneCellTile(INT nX, INT nY, BYTE bObjNum);

//	VOID			DrawOpenDoor(INT nX, INT nY);
//	VOID			SetDoorIndex();

	VOID			ScrollMap(INT nCharDir, INT nCharFrame, INT nSpeed);		// ĳ���� �̵��� ���� Scroll���� ������ ����.
	VOID			ScrollMap(INT nCharDir, WORD wCurrDelay, WORD wMoveDelay, INT nSpeed);
	VOID			SetMovedTileBuffer(INT nMovedTileX, INT nMovedTileY);		// ĳ���� �̵��� ���� ���ŵǴ� �⺻ �̹���(Ÿ��, SMŸ��)�� ����.
	VOID			DrawTile();

	VOID			SetStartViewTile(INT nX, INT nY);							// �׸��� �俵���� �ʱ�ġ����.

	BOOL			GetNextTileCanMove(INT nXPos, INT nYPos, BYTE bDir, INT nGap, POINT* lpptTarget);
	VOID			GetLastTile(INT nXPos, INT nYPos, BYTE bDir, INT& nTileX, INT& nTileY, INT nGap = 1);

/////////////////////////////////////////////////////////////////////////////////////////////////////
	VOID			GetScrnPosFromTilePos(INT nScrnX, INT nScrnY, INT& nTileX, INT& nTileY);
	VOID			GetTilePosFromScrnPos(INT nScrnX, INT nScrnY, INT& nTileX, INT& nTileY);

	BYTE			CalcDirection16(INT nFireTileX, INT nFireTileY, INT nDestTileX, INT nDestTileY);
	BYTE			CalcDirection8(INT nFireTileX, INT nFireTileY, INT nDestTileX, INT nDestTileY);
	BYTE			GetNextDirection(INT nSX, INT nSY, INT nTX, INT nTY);

	BOOL			PathFinding(INT nSX, INT nSY, INT nEX, INT nEY);

//  ���� Ÿ�Ͽ� ���� �ʼӼ� ��� �Լ���.
	BYTE			GetTileAttribute(INT nX, INT nY);
	BYTE			GetEventNum(INT nX, INT nY);
//	BOOL			GetDoorState(INT nX, INT nY);

	INT				GetDoor(INT nX, INT nY);
	VOID			OpenDoor(INT nX, INT nY, INT nIdx);
	VOID			CloseDoor(INT nX, INT nY, INT nIdx);
	INT				GetDoorImgIdx(INT nX, INT nY);
	BOOL			IsDoorOpen(INT nX, INT nY);

	LIGHTINFO		GetTileLightInfo(INT nX, INT nY);
//	VOID			SetDoorState(BYTE bIndex, BOOL bDoorOpen);
	VOID			SetAniTileFrame(INT nLoopTime);
};


#endif //_MAPHANDLER_

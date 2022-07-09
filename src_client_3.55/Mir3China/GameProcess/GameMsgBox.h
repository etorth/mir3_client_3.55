#ifndef _CGAMEMSGBOX_H_
#define _CGAMEMSGBOX_H_

//---------------------------------------------------------------------------------------------------------------//
// ��ư�� ����.
#define _OK				0
#define _YESNO			1
#define _NONE			2
//---------------------------------------------------------------------------------------------------------------//

//---------------------------------------------------------------------------------------------------------------//
// ��ư�� ����.
#define _BTN_YES		0
#define _BTN_OK			1
#define _BTN_NO			2
//---------------------------------------------------------------------------------------------------------------//

//---------------------------------------------------------------------------------------------------------------//
#define _MAX_MSGBTN		3
//---------------------------------------------------------------------------------------------------------------//

//---------------------------------------------------------------------------------------------------------------//
// ��ǥ���� ����.
#define _SCREEN_X		800
#define _SCREEN_Y		492

#define _BTN_YES_X		51
#define _BTN_YES_Y		125

#define _BTN_OK_X		147
#define _BTN_OK_Y		125

#define _BTN_NO_X		244
#define _BTN_NO_Y		125

#define _STR_SX			24	
#define _STR_SY			23
#define _STR_EX			333
#define _STR_EY			120

#define _NEW_BTN_YES_X	40
#define _NEW_BTN_YES_Y	145

#define _NEW_BTN_OK_X	114
#define _NEW_BTN_OK_Y	145

#define _NEW_BTN_NO_X	188
#define _NEW_BTN_NO_Y	145

#define _NEW_STR_SX		23	
#define _NEW_STR_SY		28
#define _NEW_STR_EX		285
#define _NEW_STR_EY		135

#define _NEW_STR_SX_SMALL		35	
#define _NEW_STR_SY_SMALL		35
#define _NEW_STR_EX_SMALL		290
#define _NEW_STR_EY_SMALL		128

//---------------------------------------------------------------------------------------------------------------//

//---------------------------------------------------------------------------------------------------------------//
typedef struct tagBTNINFO
{
	BOOL		bActive;
	CGameBtn	xGameBtn;
}BTNINFO, *LPBTNINFO;
//---------------------------------------------------------------------------------------------------------------//

class CGameMsgBox
{
private:
	INT						m_nGameWndID;										// �޽����ڽ��� ���ϰ��� ���� �����������̽� ���̵�.
	INT						m_nBoxImgIdx;										// �޽����ڽ������� �̹���.
	RECT					m_rcMsg;											// ȭ��� �޽����ڽ��� �簢 ����.
	RECT					m_rcStr;											// ȭ��� ��Ʈ���� ǥ�õ� �簢����.
	BOOL					m_bActive;											// �޽����ڽ��� Ȱ��ȭ ����.
	CHAR					m_pszMsg[MAX_PATH];									// �޽����ڽ��� ǥ�õ� ��Ʈ��.
	CHAR					m_pszEditMsg[MAX_PATH];								// 
	BTNINFO					m_stBtn[_MAX_MSGBTN];
	CWHWilImageData*		m_pxMsgBoxImage;
	WORD					m_wPacketNum;

	VOID ReleaseMsgBox();														// �޸� ����.

	BYTE					m_bFocusBtn;

	POINT					m_temp;

public:
	 CGameMsgBox();
	~CGameMsgBox();

	VOID InitMsgBox();															// �ʱ�ȭ
	__inline BOOL IsActive()
	{
		return m_bActive;
	}

	VOID CreateMsgBox(CWHWilImageData* pxMsgBoxImage, INT nWndID, INT nType, CHAR* pszStr, BOOL bUseInput = FALSE, INT nXPos = -1, INT nYPos = -1, WORD wIdent = 0XFFFF, BOOL bSecret = FALSE, INT nMaxChar = 0);	// �޽����ڽ� ������ �ʱ�ȭ.
	BOOL RenderMsgBox(POINT ptMouse);											// Active ���¸� �����Ѵ�.
	BOOL OnLButtonDown(POINT ptMouse);
	BOOL OnRButtonDown(POINT ptMouse);
	BOOL OnLButtonUp(POINT ptMouse);
	VOID OnMouseMove(POINT ptMouse);
	BOOL OnKeyDown(WPARAM wParam, LPARAM lParam);
};

/////////////////////////////////////////////////////////////////////////////
#endif  //_CGAMEMSGBOX_H_

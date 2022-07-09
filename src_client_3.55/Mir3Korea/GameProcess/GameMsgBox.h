#ifndef _CGAMEMSGBOX_H_
#define _CGAMEMSGBOX_H_

//---------------------------------------------------------------------------------------------------------------//
// 버튼의 유형.
#define _OK				0
#define _YESNO			1
#define _NONE			2
//---------------------------------------------------------------------------------------------------------------//

//---------------------------------------------------------------------------------------------------------------//
// 버튼의 종류.
#define _BTN_YES		0
#define _BTN_OK			1
#define _BTN_NO			2
//---------------------------------------------------------------------------------------------------------------//

//---------------------------------------------------------------------------------------------------------------//
#define _MAX_MSGBTN		3
//---------------------------------------------------------------------------------------------------------------//

//---------------------------------------------------------------------------------------------------------------//
// 좌표관련 정의.
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
	INT						m_nGameWndID;										// 메시지박스의 리턴값을 받을 게임인터페이스 아이디.
	INT						m_nBoxImgIdx;										// 메시지박스프레임 이미지.
	RECT					m_rcMsg;											// 화면상에 메시지박스의 사각 영역.
	RECT					m_rcStr;											// 화면상에 스트링이 표시될 사각영역.
	BOOL					m_bActive;											// 메시지박스의 활성화 여부.
	CHAR					m_pszMsg[MAX_PATH];									// 메시지박스에 표시될 스트링.
	CHAR					m_pszEditMsg[MAX_PATH];								// 
	BTNINFO					m_stBtn[_MAX_MSGBTN];
	CWHWilImageData*		m_pxMsgBoxImage;
	WORD					m_wPacketNum;

	VOID ReleaseMsgBox();														// 메모리 해제.

	BYTE					m_bFocusBtn;

	POINT					m_temp;

public:
	 CGameMsgBox();
	~CGameMsgBox();

	VOID InitMsgBox();															// 초기화
	__inline BOOL IsActive()
	{
		return m_bActive;
	}

	VOID CreateMsgBox(CWHWilImageData* pxMsgBoxImage, INT nWndID, INT nType, CHAR* pszStr, BOOL bUseInput = FALSE, INT nXPos = -1, INT nYPos = -1, WORD wIdent = 0XFFFF, BOOL bSecret = FALSE, INT nMaxChar = 0);	// 메시지박스 생성과 초기화.
	BOOL RenderMsgBox(POINT ptMouse);											// Active 상태를 리턴한다.
	BOOL OnLButtonDown(POINT ptMouse);
	BOOL OnRButtonDown(POINT ptMouse);
	BOOL OnLButtonUp(POINT ptMouse);
	VOID OnMouseMove(POINT ptMouse);
	BOOL OnKeyDown(WPARAM wParam, LPARAM lParam);
};

/////////////////////////////////////////////////////////////////////////////
#endif  //_CGAMEMSGBOX_H_

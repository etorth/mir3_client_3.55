#ifndef _CCLIENTMSG_H
#define _CCLIENTMSG_H


#define _MAX_SYSMSG 8
typedef struct tagCONSTSTRING
{
	CHAR	szMsg[MAX_PATH];
	DWORD	dwFontClr;
}CONSTSTRING, *LPCONSTSTRING;

class ClientSysMsg
{ 
private:
public:
	INT						m_nSysMsgCurrDelay;
	CPDLList<CONSTSTRING>	m_stSysMsg;

	ClientSysMsg();
	~ClientSysMsg();
	VOID		Init();
	VOID		Destroy();
	VOID		AddSysMsg(CHAR* szStr, DWORD dwFontClr = RGB(180, 255, 180));
	VOID		ShowSysMsg(INT nLoopTime, INT nX, INT nY);
};



#endif _CCLIENTMSG_H_
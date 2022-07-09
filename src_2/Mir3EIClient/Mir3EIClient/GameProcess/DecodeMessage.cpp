#include "StdAfx.h"
#include "decodemessage.h"

extern "C" int sub_42F760(char* buf);
extern "C" void SetWord(DWORD dw);

CDecodeMessage::CDecodeMessage(void)
{
	Init();
}

void CDecodeMessage::Init()
{
	key = 0;
	ch2 = 0;
	ch1 = 0;

	DWORD t = time(NULL);
	SetWord( t );
}

CDecodeMessage::~CDecodeMessage(void)
{
}

short CDecodeMessage::DecodeMessageHead(_TDEFAULTMESSAGE* tdm)
{
	unsigned char tmpInt[4];
	int tmpTdm[3];
	unsigned char* p = (unsigned char*)tdm;

	*(short*)(p+4)  = *(short*)(p+4) ^ key;
	tmpInt[3] = *(p+11);
	tmpInt[2] = *(p+9);
	tmpInt[1] = *(p+7);
	tmpInt[0] = *(p+5);
	tmpTdm[0] = *(int*)tmpInt;

	tmpInt[3] = *(p+6);
	tmpInt[2] = *(p+1);
	tmpInt[1] = *(p+4) ^ ch1;
	tmpInt[0] = *(p+0) ^ ch2;
	tmpTdm[1] = *(int*)tmpInt;

	tmpInt[3] = *(p+10);
	tmpInt[2] = *(p+3);
	tmpInt[1] = *(p+8);
	tmpInt[0] = *(p+2);
	tmpTdm[2] = *(int*)tmpInt;

	memcpy(tdm, tmpTdm, sizeof(_TDEFAULTMESSAGE));
	return tdm->wIdent;
}

void CDecodeMessage::GetDecodeKey(char* szSource)
{
	char buf1[21];
	char buf2[21];
	char buf3[21];

	memcpy( buf1, szSource, 20 );
	buf1[20] = 0;
	memcpy( buf2, szSource+20, 20 );
	buf2[20] = 0;
	memcpy( buf3, szSource+40, 20 );
	buf3[20] = 0;
	int i = sub_42F760( buf1 );
	int j = sub_42F760( buf2 );//²»Çå³þ
	int k = sub_42F760( buf3 );

	ch1 = HIBYTE( k );
	ch2 = LOBYTE( k );
	key = i;
}


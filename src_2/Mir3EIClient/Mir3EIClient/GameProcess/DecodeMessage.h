#pragma once

class CDecodeMessage
{
public:
	CDecodeMessage(void);
	~CDecodeMessage(void);
	
	void Init();
	short DecodeMessageHead(_TDEFAULTMESSAGE* tdm);
	void GetDecodeKey(char* szSource);
private:
	short key;
	char ch1;
	char ch2;

};



#pragma once


struct sExecCmds
{
	bool bNotPatchd;
	bool bFullScreen;
	int  nRefreshRate;	// if 0, program use default display adapter. (maybe 60hz)
	char szServerIP[16];
	int  nPort;

	sExecCmds()
	{
		bNotPatchd		= false;
		bFullScreen		= true;
		nRefreshRate	= 0;
		szServerIP[0]	= NULL;
		nPort			= -1;
	};
};


extern sExecCmds g_execCmds;


bool ParseCmdLine();



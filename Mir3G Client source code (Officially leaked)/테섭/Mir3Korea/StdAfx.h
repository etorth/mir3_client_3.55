// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#define _LOGIN_PROC		0
#define _SVR_SEL_PROC	1
#define _CHAR_SEL_PROC	2
#define _GAME_PROC		3

#ifndef WM_MOUSEWHEEL
#define WM_MOUSEWHEEL WM_MOUSELAST+1 
#endif

#pragma comment(lib,"imm32.lib")
#pragma comment(lib,"Version.lib")
#pragma comment(lib, "WS2_32.lib")
#pragma comment(lib, "Vfw32.lib")			// AVI
#pragma comment(lib, "quartz.lib")			// DirectShow

#include <string>
#include <control.h>
#include <vfw.h>
#include <io.h>
#include <process.h>
#include <setjmp.h>


#pragma comment( lib, "jpeglib2.lib" )
extern "C"
{
#include "jpeglib.h"
}

#include "Resource.h"

#include ".\WindHorn\WHEngine.h"

#pragma comment(lib, "strmbasd.lib")		// DirectShow

#include ".\OrzLib\list.h"
#include ".\OrzLib\pqueue.h"
#include ".\OrzLib\astar.h"
#include ".\GameProcess\PathFinding.h"
#include ".\Common\Msg.h"

#include "Define.h"
#include "GFun.h"
#include "CmdLineParser.h"

#include ".\Sound\TypeDef.h"
#include ".\Sound\BMMP3.h"
#include ".\avi\avi.h"

#include ".\Sound\WaveBuffer.h"
#include ".\Sound\DSound.h"
#include ".\Sound\SoundManager.h"

#include ".\Common\DblList.h"
#include ".\Common\DLinkedList.h"
#include ".\Common\ScreenCapture.h"
#include ".\Common\EnDecode.h"

#include ".\GameProcess\GameBtn.h"
#include ".\GameProcess\GameMsgBox.h"
#include ".\Common\NoticeBox.h"
#include ".\Common\ChatEditBox.h"
#include ".\Common\ClientSocket.h"
#include ".\Common\ImageHandler.h"
#include ".\Common\Queue.h"
#include ".\Common\crypto.h"
#include ".\GameProcess\SprDfn.h"
#include ".\GameProcess\Particle.h"
#include ".\GameProcess\MiniMap.h"
#include ".\GameProcess\MiniMapInSiege.h"

#include ".\GameProcess\ClientSysMsg.h"
#include ".\GameProcess\Item.h"
#include ".\GameProcess\MapHandler.h"
//#include ".\GameProcess\GameBtn.h"
#include ".\GameProcess\GameWnd.h"
#include ".\GameProcess\InventoryWnd.h"
#include ".\GameProcess\StatusWnd.h"
#include ".\GameProcess\ExchangeWnd.h"
#include ".\GameProcess\NoticeEditWnd.h"
#include ".\GameProcess\GuildWnd.h"
#include ".\GameProcess\GameOverWnd.h"
#include ".\GameProcess\GroupWnd.h"
#include ".\GameProcess\ChatPopWnd.h"
#include ".\GameProcess\QuestWnd.h"
#include ".\GameProcess\OptionWnd.h"
#include ".\GameProcess\HorseWnd.h"
#include ".\GameProcess\MagicWnd.h"
#include ".\GameProcess\Actor.h"
#include ".\GameProcess\UserStateWnd.h"
#include ".\GameProcess\BeltWnd.h"
#include ".\GameProcess\SiegeWnd.h"
#include ".\GameProcess\Market.h"
#include ".\GameProcess\MarketUp.h"
#include ".\GameProcess\Messenger.h"
#include ".\GameProcess\FaceImgUp.h"
#include ".\GameProcess\UtilWnd.h"
#include ".\GameProcess\ViewMiniMapWnd.h"
#include ".\GameProcess\ChatWnd.h"
#include ".\GameProcess\SettingWnd.h"
#include ".\GameProcess\MagicShortcutWnd.h"


// TestFolder\MyWnd.h / .cpp
// by eriastoa 2006.03.28
#include "TestFolder/TestWnd.h"




// TestActor.h / .cpp
// by eriastoa 2006.04.03
#include "TestFolder/TestActor.h"


// TestMagic.h / .cpp
// by eriastoa 2006.04.04
#include "TestFolder/TestMagic.h"

// 몬스터 정보 보기 위해서 추가
// by eriastoa 2006.04.05
#include <vector>
#include <string>
using namespace std;




#include ".\GameProcess\NpcWnd.h"
#include ".\GameProcess\StoreWnd.h"




#include ".\GameProcess\LightFog.h"
#include ".\GameProcess\Actor.h"
#include ".\GameProcess\Magic.h"
#include ".\GameProcess\Interface.h"
#include ".\GameProcess\GameProc.h"

#include ".\LoginProcess\LoginProc.h"

#include ".\CharSelectProcess\ChrProc.h"

#include "Extern.h"




//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)


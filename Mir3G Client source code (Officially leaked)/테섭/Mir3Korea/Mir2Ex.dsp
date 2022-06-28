# Microsoft Developer Studio Project File - Name="Mir2Ex" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Mir2Ex - Win32 Test Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Mir2Ex.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Mir2Ex.mak" CFG="Mir2Ex - Win32 Test Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Mir2Ex - Win32 Test Debug" (based on "Win32 (x86) Application")
!MESSAGE "Mir2Ex - Win32 Test Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Mir2Ex", BAAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Mir2Ex - Win32 Test Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Mir2Ex___Win32_Test_Debug"
# PROP BASE Intermediate_Dir "Mir2Ex___Win32_Test_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Mir2Ex___Win32_Test_Debug"
# PROP Intermediate_Dir "Mir2Ex___Win32_Test_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Gm /GX /ZI /Od /I "./OrzLib" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /Gm /GX /ZI /Od /I "./OrzLib" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_TEST_SERVER" /D "_TEST_SERVER_DEBUG" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG"
# ADD RSC /l 0x412 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"C:\미르의전설3\Mir3.exe" /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libcmt.lib" /out:"h:\Mir3\테섭\Mir3KoreaTest\Mir3TestD.exe" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none /map /nodefaultlib

!ELSEIF  "$(CFG)" == "Mir2Ex - Win32 Test Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Mir2Ex___Win32_Test_Release"
# PROP BASE Intermediate_Dir "Mir2Ex___Win32_Test_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Mir2Ex___Win32_Test_Release"
# PROP Intermediate_Dir "Mir2Ex___Win32_Test_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /GX /O2 /I "./OrzLib" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# SUBTRACT BASE CPP /WX
# ADD CPP /nologo /GX /O2 /I "./OrzLib" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_TEST_SERVER" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /out:"C:\미르의전설3\Mir3.exe"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"libcmt.lib" /out:"h:\Mir3\테섭\Mir3KoreaTest\Mir3Test.exe"
# SUBTRACT LINK32 /debug

!ENDIF 

# Begin Target

# Name "Mir2Ex - Win32 Test Debug"
# Name "Mir2Ex - Win32 Test Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CmdLineParser.cpp
# End Source File
# Begin Source File

SOURCE=.\GFun.cpp
# End Source File
# Begin Source File

SOURCE=.\Mir2Ex.cpp
# End Source File
# Begin Source File

SOURCE=.\Resource.rc
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CmdLineParser.h
# End Source File
# Begin Source File

SOURCE=.\Define.h
# End Source File
# Begin Source File

SOURCE=.\Extern.h
# End Source File
# Begin Source File

SOURCE=.\GFun.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Common\Typedeftxt.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\icon100.ico
# End Source File
# Begin Source File

SOURCE=.\Mir2Ex.ico
# End Source File
# Begin Source File

SOURCE=".\바탕화면 아이콘(256).bmp"
# End Source File
# End Group
# Begin Group "Login Process"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LoginProcess\LoginProc.cpp
# End Source File
# Begin Source File

SOURCE=.\LoginProcess\LoginProc.h
# End Source File
# End Group
# Begin Group "Game Precess"

# PROP Default_Filter ""
# Begin Group "Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GameProcess\Actor.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\BeltWnd.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\ChatPopWnd.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\ChatWnd.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\ClientSysMsg.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\ExchangeWnd.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\FaceImgUp.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\GameBtn.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\GameMsgBox.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\GameOverWnd.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\GameProc.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\GameWnd.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\GroupWnd.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\GuildWnd.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\HorseWnd.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\Interface.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\InventoryWnd.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\Item.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\LightFog.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\Magic.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\MagicShortcutWnd.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\MagicWnd.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\MapHandler.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\Market.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\MarketUp.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\Messenger.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\MessengerGift.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\MessengerRead.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\MessengerWrite.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\MiniMap.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\MiniMapInSiege.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\NoticeEditWnd.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\NPCWnd.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\OptionWnd.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\Particle.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\PathFinding.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\QuestWnd.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\SettingWnd.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\SiegeWnd.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\SprDfn.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\StatusWnd.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\StoreWnd.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\UserStateWnd.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\UtilWnd.h
# End Source File
# Begin Source File

SOURCE=.\GameProcess\ViewMiniMapWnd.h
# End Source File
# End Group
# Begin Group "Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GameProcess\Actor.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\BeltWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\ChatPopWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\ChatWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\ClientSysMsg.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\ExchangeWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\FaceImgUp.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\GameBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\GameMsgBox.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\GameOverWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\GameProc.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\GameWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\GroupWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\GuildWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\HorseWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\Interface.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\InventoryWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\Item.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\LightFog.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\Magic.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\MagicShortcutWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\MagicWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\MapHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\Market.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\MarketUp.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\Messenger.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\MiniMap.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\MiniMapInSiege.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\NoticeEditWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\NPCWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\OptionWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\Particle.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\PathFinding.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\QuestWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\SettingWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\SiegeWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\SprDfn.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\StatusWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\StoreWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\UserStateWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\UtilWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GameProcess\ViewMiniMapWnd.cpp
# End Source File
# End Group
# End Group
# Begin Group "Common "

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Common\ChatEditBox.cpp
# End Source File
# Begin Source File

SOURCE=.\Common\ChatEditBox.h
# End Source File
# Begin Source File

SOURCE=.\Common\ClientSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\Common\ClientSocket.h
# End Source File
# Begin Source File

SOURCE=.\Common\crypto.cpp
# End Source File
# Begin Source File

SOURCE=.\Common\crypto.h
# End Source File
# Begin Source File

SOURCE=.\Common\DblList.cpp
# End Source File
# Begin Source File

SOURCE=.\Common\DblList.h
# End Source File
# Begin Source File

SOURCE=.\Common\DLinkedList.cpp
# End Source File
# Begin Source File

SOURCE=.\Common\DLinkedList.h
# End Source File
# Begin Source File

SOURCE=.\Common\EnDecode.cpp
# End Source File
# Begin Source File

SOURCE=.\Common\EnDecode.h
# End Source File
# Begin Source File

SOURCE=.\Common\ImageHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\Common\ImageHandler.h
# End Source File
# Begin Source File

SOURCE=.\Common\ImageHandlerHelper.cpp
# End Source File
# Begin Source File

SOURCE=.\Common\ImageHandlerHelper.h
# End Source File
# Begin Source File

SOURCE=.\Common\list.h
# End Source File
# Begin Source File

SOURCE=.\Common\Msg.cpp
# End Source File
# Begin Source File

SOURCE=.\Common\Msg.h
# End Source File
# Begin Source File

SOURCE=.\Common\NoticeBox.cpp
# End Source File
# Begin Source File

SOURCE=.\Common\NoticeBox.h
# End Source File
# Begin Source File

SOURCE=.\OrzLib\prime.cpp
# End Source File
# Begin Source File

SOURCE=.\Common\Protocol.h
# End Source File
# Begin Source File

SOURCE=.\Common\Queue.cpp
# End Source File
# Begin Source File

SOURCE=.\Common\Queue.h
# End Source File
# Begin Source File

SOURCE=.\Common\ScreenCapture.cpp
# End Source File
# Begin Source File

SOURCE=.\Common\ScreenCapture.h
# End Source File
# End Group
# Begin Group "Chr Select Process"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CharSelectProcess\ChrProc.cpp
# End Source File
# Begin Source File

SOURCE=.\CharSelectProcess\ChrProc.h
# End Source File
# End Group
# Begin Group "Sound"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Sound\BMMP3.cpp
# End Source File
# Begin Source File

SOURCE=.\Sound\BMMP3.h
# End Source File
# Begin Source File

SOURCE=.\Sound\DSound.cpp
# End Source File
# Begin Source File

SOURCE=.\Sound\DSound.h
# End Source File
# Begin Source File

SOURCE=.\Sound\SoundManager.cpp
# End Source File
# Begin Source File

SOURCE=.\Sound\SoundManager.h
# End Source File
# Begin Source File

SOURCE=.\Sound\TypeDef.h
# End Source File
# Begin Source File

SOURCE=.\Sound\WaveBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\Sound\WaveBuffer.h
# End Source File
# End Group
# Begin Group "Avi"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AVI\Avi.cpp
# End Source File
# Begin Source File

SOURCE=.\AVI\Avi.h
# End Source File
# End Group
# Begin Group "TestFolder"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TestFolder\TestActor.cpp
# End Source File
# Begin Source File

SOURCE=.\TestFolder\TestActor.h
# End Source File
# Begin Source File

SOURCE=.\TestFolder\TestMagic.cpp
# End Source File
# Begin Source File

SOURCE=.\TestFolder\TestMagic.h
# End Source File
# Begin Source File

SOURCE=.\TestFolder\TestSourceBackup.cpp

!IF  "$(CFG)" == "Mir2Ex - Win32 Test Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Mir2Ex - Win32 Test Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TestFolder\TestSourceBackup.h

!IF  "$(CFG)" == "Mir2Ex - Win32 Test Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Mir2Ex - Win32 Test Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TestFolder\TestWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\TestFolder\TestWnd.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\CMList.txt
# End Source File
# Begin Source File

SOURCE=.\MInfo.txt
# End Source File
# Begin Source File

SOURCE=.\MiniMap.txt
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project

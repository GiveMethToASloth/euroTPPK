//#include "EuroTPPK.h"
//
//bool ListOnce = false; // Players
//bool GainOnce = false; // Authing
//PKInfoStruct PKInfo;
//LastPKStruct LPK;
//AUTHNUMBER Authn;
//
//#define INTERNET_OPEN_TYPE_PRECONFIG      0
////#define INTERNET_FLAG_EXISTING_CONNECT 536870912
//
//typedef void* (WINAPI* __InternetOpen) (char*, DWORD, DWORD, DWORD, DWORD);
//typedef void* (WINAPI* __InternetOpenUrl) (void*, char*, DWORD, DWORD, DWORD, DWORD);
//typedef void  (WINAPI* __InternetCloseHandle) (HANDLE);
//typedef BOOL(WINAPI* __InternetReadFileA) (HANDLE, LPVOID, DWORD, LPDWORD);
//
//char* GetSiteText(char* Addr, char* Para) {
//	HANDLE hInternet = NULL;
//	HANDLE hInternetUrl = NULL;
//	HANDLE hURL;
//	char szString[2049] = { 0 };
//	char szSite[1024] = { 0 };
//	sprintf(szSite, "%s?%s", Addr, Para);
//
//	HANDLE gHandle = LoadLibrary("wininet");
//	if (!gHandle)
//		return 0;
//
//	__InternetOpen fp1;
//	fp1 = (__InternetOpen)(DWORD)GetProcAddress((HINSTANCE)gHandle, "InternetOpenA");
//	__InternetOpenUrl fp2;
//	fp2 = (__InternetOpenUrl)(DWORD)GetProcAddress((HINSTANCE)gHandle, "InternetOpenUrlA");
//	__InternetCloseHandle fp3;
//	fp3 = (__InternetCloseHandle)(DWORD)GetProcAddress((HINSTANCE)gHandle, "InternetCloseHandle");
//	__InternetReadFileA fp4;
//	fp4 = (__InternetReadFileA)(DWORD)GetProcAddress((HINSTANCE)gHandle, "InternetReadFile");
//	if (!fp1 || !fp2 || !fp3 || !fp4)
//		return 0;
//
//	DWORD dwBytes = 0;
//	hInternet = fp1(0, INTERNET_OPEN_TYPE_PRECONFIG, 0, 0, 0);
//	if (hInternet == NULL) return 0;
//	hInternetUrl = fp2(hInternet, szSite, NULL, 0, INTERNET_FLAG_EXISTING_CONNECT, 0);
//	if (hInternetUrl == NULL) return 0;
//	fp4(hInternetUrl, &szString, 2048, &dwBytes); // 2048 = max. 2kb
//	if (hInternetUrl == NULL) return NULL;
//
//	fp3(hInternetUrl);
//	fp3(hInternet);
//	return szString;
//} // Closing GetText
//
//typedef void* (WINAPI* __InternetOpen) (char*, DWORD, DWORD, DWORD, DWORD);
//typedef void* (WINAPI* __InternetOpenUrl) (void*, char*, DWORD, DWORD, DWORD, DWORD);
//
//BOOL ConnectURL(char* szURL) {
//	HANDLE hURL;
//	HANDLE hInternetSession;
//	HANDLE gHandle = LoadLibrary("wininet");
//
//	__InternetOpen fp1;
//	fp1 = (__InternetOpen)(DWORD)GetProcAddress((HINSTANCE)gHandle, "InternetOpenA");
//	__InternetOpenUrl fp2;
//	fp2 = (__InternetOpenUrl)(DWORD)GetProcAddress((HINSTANCE)gHandle, "InternetOpenUrlA");
//	__InternetCloseHandle fp3;
//	fp3 = (__InternetCloseHandle)(DWORD)GetProcAddress((HINSTANCE)gHandle, "InternetCloseHandle");
//	if (!gHandle || !fp1 || !fp2 || !fp3) return 0;
//
//	hInternetSession = fp1("EuroTPPK", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
//	hURL = fp2(hInternetSession, szURL, NULL, 0, 0, 0);
//	fp3(hURL);
//	fp3(hInternetSession);
//	delete szURL;
//	return TRUE;// (BOOL)FreeLibrary((HINSTANCE)gHandle);
//}
//
//void Decrypt(char* buffer, char* String, int xorer) {
//	for (int i = 0; i < strlen(String); i++) {
//		buffer[i] = ((char)String[i]) ^ -+xorer;
//	}
//}
//
//// start of urls to use
//char* AuthURL() {
//	char* Buffer = (char*)malloc(512);
//	for (int i = 0; i < 512; i++)
//		Buffer[i] = 0x00;
//	// http://www.europk.org/EuroTPPK/AT.php
//	// http://www.europk.se/EuroTPPK/Au.php
//	// http://eupk.ath.cx/EuroTPPK/Az.php
//  //  Decrypt(Buffer,"…ÏÚÚ‚‚‚Û€‡š…žÛš‡’Ú°€‡š¡¥¥¾Ú´¡Û……",11); // org
////Decrypt(Buffer,"…ÏÚÚ‚‚‚Û€‡š…žÛ†Ú°€‡š¡¥¥¾Ú´€Û……",11); // se
//	Decrypt(Buffer, "…ÏÚÚ€…žÛ”Û–Ú°€‡š¡¥¥¾Ú´Û……", 11); // cx
//	return Buffer;
//}
//char* GetKey() {
//	char* Buffer = (char*)malloc(512);
//	for (int i = 0; i < 512; i++)
//		Buffer[i] = 0x00;
//	// &key=BG8H8GJJHH88JKJKJGFDF6 EUPK
//	// &key=ewexrbqqngvdr6c3pfkmu87 IHPK
//	Decrypt(Buffer, "ÓžŒÈ·²Í½Í²¿¿½½ÍÍ¿¾¿¾¿²³±³Ã", 11); // EUPK
//	return Buffer;
//}
///*char* HcpkURL() {
//	char* Buffer=(char*)malloc(512);
//	for(int i=0;i<512;i++)
//		Buffer[i] = 0x00;
//		// http://www.hcpk.net/889B7CCLL93332B0752F593.php
//	Decrypt(Buffer,"…ÏÚÚ‚‚‚Û–…žÛ›ÚÍÍÌ·Â¶¶¹¹ÌÆÆÆÇ·ÅÂÀÇ³ÀÌÆÛ……",11);
//	return Buffer;
//}*/
///*char* IhpkURL() {
//	char* Buffer=(char*)malloc(512);
//	for(int i=0;i<512;i++)
//		Buffer[i] = 0x00;
//		// http://ihpk.net/authing/auth.php
//	Decrypt(Buffer,"…ÏÚÚœ…žÛ›Ú”€œ›’Ú”€Û……",11);
//	return Buffer;
//}*/
/////////////////////////// URLS
//
//void GA(void) // Getting Adress
//{
//	if (ListOnce)
//		return;
//	char Buffer[2048] = { 0 };
//	char Parameter[1024];
//	char* argv[1024];
//	sprintf(Parameter, "action=version");
//	strcpy(Buffer, GetSiteText(AuthURL(), Parameter));
//	DWORD argc = MakeParameter(Buffer, argv, '|', true);
//	Authn.LifeAddr1 = atoi(argv[1]);
//	show = true;
//}
//
////void CheckAuth(void) {
////	char Parameter[512];
////	char Buffer[512];
////	sprintf(Parameter, "action=check&a=%s&r=%s", GetGameInfo()->szAccountName, GetGameInfo()->szRealmName);
////	sprintf(Buffer, "%s", GetSiteText(AuthURL(), Parameter));
////	if (Buffer[0] == 'N' && Buffer[1] == 'A' && Buffer[2] == 'H') {
////	}
////	else {
////		TerminateProcess(GetCurrentProcess(), 0);
////		//UninstallPatches();
////		RemovePatchs();
////	}
////}
//// Members
//void GetMembers(void)
//{
//	char* argv[1024] = { 0 };
//	char Parameter[512];
//	char Buffer[1024];
//	int argc;
//	LinkedItem* linkeditem;
//	for (linkeditem = PlayerFriendList->GetFirstItem(); linkeditem != NULL; linkeditem = PlayerFriendList->RemoveItem(linkeditem)) {
//	}
//	sprintf(Parameter, "action=gplist&r=%s", GetGameInfo()->szRealmName);
//	strcpy(Buffer, GetSiteText(AuthURL(), Parameter));
//	argc = MakeParameter(Buffer, argv, '|', false);
//	for (int i = 0; i < argc; i++) {
//		PlayerFriendList->AddItem(argv[i]);
//	}
//	return;
//}
//
//void GetBlackList(void)
//{
//	char* argv[1024] = { 0 };
//	char Parameter[512];
//	char Buffer[1024];
//	int argc;
//	LinkedItem* linkeditem;
//	for (linkeditem = PlayerEnemyList->GetFirstItem(); linkeditem != NULL; linkeditem = PlayerEnemyList->RemoveItem(linkeditem)) {
//	}
//	sprintf(Parameter, "action=gblist&r=%s", GetGameInfo()->szRealmName);
//	strcpy(Buffer, GetSiteText(AuthURL(), Parameter));
//	argc = MakeParameter(Buffer, argv, '|', false);
//
//	for (int i = 0; i < argc; i++) {
//		PlayerEnemyList->AddItem(argv[i]);
//	}
//	return;
//}
//
//void Spammers(void)
//{
//	return;
//	char* argv[1024] = { 0 };
//	char Parameter[512];
//	char Buffer[1024];
//	int argc;
//	LinkedItem* linkeditem;
//	for (linkeditem = PlayerSpamList->GetFirstItem(); linkeditem != NULL; linkeditem = PlayerSpamList->RemoveItem(linkeditem)) {
//	}
//	//sprintf(Parameter,"action=gplist&r=%s",GetGameInfo()->szRealmName);
//	//strcpy(Buffer,GetSiteText(AuthURL(),Parameter));
//	argc = MakeParameter(v_SpamNames, argv, ',', false);
//	for (int i = 0; i < argc; i++) {
//		PlayerSpamList->AddItem(argv[i]);
//	}
//	return;
//}
//
//int GetLevelByN(char* Name) {
//	RosterUnit* pUnit = (RosterUnit*)*(DWORD*)0x6FBCC080;
//	while (pUnit != NULL) {
//		if (!_strcmpi(pUnit->szName, Name))
//			return pUnit->wLevel;
//		pUnit = pUnit->pNext;
//	}
//
//	return -1;
//}
//char* GetClassByN(char* Name) {
//	RosterUnit* pUnit = (RosterUnit*)*(DWORD*)0x6FBCC080;
//	while (pUnit != NULL) {
//		if (!_strcmpi(pUnit->szName, Name))
//			return GetD2ClassName(pUnit->dwClassId);
//		pUnit = pUnit->pNext;
//	}
//
//	return NULL;
//}
//
//void PlayerStats(void)
//{
//	GainOnce = false;
//	if (GainOnce)
//		return;
//	GainOnce = true;
//	if (TimeOn <= 1000) {
//		char Buffer[2048] = { 0 };
//		char Parameter[1024];
//		char* argv[1024];
//		sprintf(Parameter, "action=info&a=%s&c=%s&r=%s&l=%d&t=%s", GetGameInfo()->szAccountName, GetGameInfo()->szCharName, GetGameInfo()->szRealmName, GetLevelByN(GetGameInfo()->szCharName), GetClassByN(GetGameInfo()->szCharName));
//		strcpy(Buffer, GetSiteText(AuthURL(), Parameter));
//		DWORD argc = MakeParameter(Buffer, argv, '|', true);
//
//		strcpy(PKInfo.ForumName, argv[0]);
//		PKInfo.TotalKills = atoi(argv[1]);
//		PKInfo.TotalScore = atoi(argv[2]);
//		PKInfo.Rank = atoi(argv[3]);
//		strcpy(PKInfo.LastUse, argv[4]);
//		PKInfo.Ready = true;
//		TimeOn++;
//		//PrintLastPK();
//		return;
//	}
//}
//void PlayerStatsNew(void)
//{
//	char Buffer[2048] = { 0 };
//	char Parameter[1024];
//	char* argv[1024];
//	sprintf(Parameter, "action=info&a=%s&c=%s&r=%s&l=%d&t=%s", GetGameInfo()->szAccountName, GetGameInfo()->szCharName, GetGameInfo()->szRealmName, GetLevelByN(GetGameInfo()->szCharName), GetClassByN(GetGameInfo()->szCharName));
//	strcpy(Buffer, GetSiteText(AuthURL(), Parameter));
//	DWORD argc = MakeParameter(Buffer, argv, '|', true);
//	strcpy(PKInfo.ForumName, argv[0]);
//	PKInfo.TotalKills = atoi(argv[1]);
//	PKInfo.TotalScore = atoi(argv[2]);
//	PKInfo.Rank = atoi(argv[3]);
//	TimeOn1++;
//	Killed = true;
//	return;
//}
//
//void LastPKNew(void)
//{
//	char Buffer[2048] = { 0 };
//	char Parameter[1024];
//	char* argv[1024];
//	strcpy(Buffer, GetSiteText(AuthURL(), "action=lpk"));
//	DWORD argc = MakeParameter(Buffer, argv, '|', true);
//	strcpy(LPK.killer, argv[0]);
//	strcpy(LPK.killed, argv[1]);
//	strcpy(LPK.level, argv[2]);
//	strcpy(LPK.type, argv[3]);
//	strcpy(LPK.time, argv[4]);
//	return;
//}
//
///*
//DWORD WINAPI PrintPkStats1(void* p) {
//	char *szBuffer= (char*)p;
//	char Buffer[2048]={0};
//	char Parameter[1024];
//	char* argv[1024];
//sprintf(Parameter,"action=info&a=%s&c=%s&r=%s",GetGameInfo()->szAccountName,GetGameInfo()->szCharName,GetGameInfo()->szRealmName);
//strcpy(Buffer,GetSiteText(AuthURL(),Parameter));
//DWORD argc=MakeParameter(Buffer,argv,'|',true);
//	strcpy(PKInfo.ForumName,argv[0]);
//	PKInfo.TotalKills=atoi(argv[1]);
//	PKInfo.TotalScore=atoi(argv[2]);
//	PKInfo.Rank=atoi(argv[3]);
//	PKInfo.Ready=true;
////	TimeOn1++;
//return true;
//}
//
//BOOL UpdatePKInfo() {
//	CreateThread(0,0,PrintPkStats1,0,0,0);
//	return true;
//}
//*/
//void GetPlayers() {
//	if (!ListOnce) {
//		if (v_ItemLevel) {
//			InstallItemlvl();
//			ItemLevel = true;
//		}
//		else { UninstallItemlvl(); };
//
//		Sleep(15);
//		GetMembers();
//		GetBlackList();
//		Spammers();
//
//		//PlayerStats(); // Prints Welcome & Stats
//		GA(); // Fetches adresses.
////		PKInfo.Ready=true;
//		TimeOn++;
//		ListOnce = true;
//		//PrintLists(); // Prints Friends : Enemys
//		return;
//	}
//	if (ListOnce == true) {
//		return;
//	}
//}
//bool CheckPlayerFriend(char* Name) {
//	LinkedItem* linkeditem;
//	for (linkeditem = PlayerFriendList->GetFirstItem(); linkeditem != NULL; linkeditem = PlayerFriendList->GetNextItem(linkeditem)) {
//		if (!_strcmpi(linkeditem->Name, Name))
//			return true;
//	}
//	return false;
//}
//bool CheckSpammerName(char* Name) {
//	LinkedItem* linkeditem;
//	for (linkeditem = PlayerSpamList->GetFirstItem(); linkeditem != NULL; linkeditem = PlayerSpamList->GetNextItem(linkeditem)) {
//		if (!_strcmpi(linkeditem->Name, Name))
//			return true;
//	}
//	return false;
//}
//
////HANDLE hInternetSession;
//HANDLE hURL;
//
//bool CheckPlayerEnemy(char* Name) {
//	LinkedItem* linkeditem;
//	for (linkeditem = PlayerEnemyList->GetFirstItem(); linkeditem != NULL; linkeditem = PlayerEnemyList->GetNextItem(linkeditem)) {
//		if (!_strcmpi(linkeditem->Name, Name))
//			return true;
//	}
//
//	return false;
//}
//
//DWORD WINAPI SubmitThread(void* p) {
//	char* szBuffer = (char*)p;
//	if (!ConnectURL(szBuffer))
//		PrintMessage("Error: Can't submit the kill", 1);
//	delete szBuffer;
//	return TRUE;
//}
//
//void SendPK(char* PKname, int Level, char* Class)
//{
//	GameStructInfo* pInfo = (GameStructInfo*)GetGameInfo();
//	RosterUnit* pUnit = (RosterUnit*)*(DWORD*)0x6FBCC080;
//	char szTime[64] = { 0 };
//	char szBuffer[2024] = { 0 };
//	char Type[1024] = { 0 };
//	time_t ttTime;
//	time(&ttTime);
//	if (IsExpansion())
//		strcpy(Type, "Expansion");
//	else strcpy(Type, "Classic");
//	strftime(szTime, 1024, "%b %d %Y - %H:%M:%S", localtime(&ttTime));
//	sprintf(szBuffer, "%s?action=add&t=%s&d=%s&c=%s&l=%d&k=%s&r=%s&g=%s%s",
//		AuthURL(), szTime, PKname, Class, Level, pInfo->szAccountName, pInfo->szRealmName, Type, GetKey());
//	ConnectURL(szBuffer);
//	return;
//}
//
//BOOL AddURL(char* PKname, int Level, char* Class)
//{
//	GameStructInfo* pInfo = (GameStructInfo*)GetGameInfo();
//	RosterUnit* pUnit = (RosterUnit*)*(DWORD*)0x6FBCC080; // Updated
//	char szTime[64] = { 0 };
//	char* szBuffer = (char*)malloc(2024);
//	memset(szBuffer, 0, 2024);
//	time_t ttTime;
//	time(&ttTime);
//	char Type[1024] = { 0 };
//	if (IsExpansion())
//		strcpy(Type, "Expansion");
//	else strcpy(Type, "Classic");
//	strftime(szTime, 1024, "%b %d %Y - %H:%M:%S", localtime(&ttTime));
//	sprintf(szBuffer, "%s?action=add&t=%s&d=%s&c=%s&l=%d&k=%s&r=%s&g=%s%s",
//		AuthURL(),
//		szTime,
//		PKname,
//		Class,
//		Level,
//		pInfo->szAccountName,
//		pInfo->szRealmName,
//		Type,
//		GetKey()
//	);
//
//	CreateThread(0, 0, SubmitThread, (LPVOID)szBuffer, 0, 0);
//	delete szBuffer;
//	delete szTime;
//	return true;
//}
//
//void SS(void) {
//	ssTimer++;
//	D2WIN_TakeScreenshot();
//	PrintMessage("Screen Captured", 8);
//	return;
//}
//
//DWORD WINAPI PrintThread(void* p) {
//	char* szBuffer = (char*)p;
//	char Buffer[2048] = { 0 };
//	sprintf(Buffer, "::ÿc  %s", GetSiteText(AuthURL(), "action=lpk"));
//	PrintMessage(Buffer, 3);
//	return 0;
//}
//
//void PrintLastPK() {
//	CreateThread(0, 0, PrintThread, 0, 0, 0);
//	return;
//}
///*
//DWORD WINAPI PrintPkStats(void* p) {
//	GainOnce=false;
//	if(GainOnce)
//	return TRUE;
//	GainOnce=true;
//	char *szBuffer= (char*)p;
//	char Buffer[2048]={0};
//	char Parameter[512];
//sprintf(Parameter,"action=info&a=%s&c=%s&r=%s&l=%s",GetGameInfo()->szAccountName,GetGameInfo()->szCharName,GetGameInfo()->szRealmName);
//sprintf(Buffer,"ÿc3::ÿc1 EuroPK:ÿc9 %s",GetSiteText(GetURLBase(),Parameter));
//	PrintMessage(Buffer,0);
//	return 0;
//}
//
//void PrintPkStats() {
//	CreateThread(0,0,PrintPkStats,0,0,0);
//	return;
//}
//*/
//DWORD WINAPI FriendThread(void* p) {
//	char* argv[1024] = { 0 };
//	char Parameter[512];
//	char Buffer[1024];
//	int argc;
//
//	LinkedItem* linkeditem;
//	for (linkeditem = PlayerFriendList->GetFirstItem(); linkeditem != NULL; linkeditem = PlayerFriendList->RemoveItem(linkeditem)) {
//	}
//	sprintf(Parameter, "action=gplist&r=%s", GetGameInfo()->szRealmName);
//	strcpy(Buffer, GetSiteText(AuthURL(), Parameter));
//	argc = MakeParameter(Buffer, argv, '\n', false);
//
//	for (int i = 0; i < argc; i++) {
//		PlayerFriendList->AddItem(argv[i]);
//		Sleep(50);
//	}
//	return 0;
//}
//
//bool CheckIfAllowed() {
//	GainOnce = false;
//	if (GainOnce)
//		return TRUE;
//	char Parameter[512];
//	char Buffer[512];
//	sprintf(Parameter, "action=check&a=%s&r=%s", GetGameInfo()->szAccountName, GetGameInfo()->szRealmName);
//	sprintf(Buffer, "%s", GetSiteText(AuthURL(), Parameter));
//	if (Buffer[0] == 'N' && Buffer[1] == 'A' && Buffer[2] == 'H')
//		return true;
//	return false;
//}
//
//DWORD WINAPI EnemyThread(void* p) {
//	char* argv[1024] = { 0 };
//	char Parameter[512];
//	char Buffer[1024];
//	int argc;
//	LinkedItem* linkeditem;
//	for (linkeditem = PlayerEnemyList->GetFirstItem(); linkeditem != NULL; linkeditem = PlayerEnemyList->RemoveItem(linkeditem)) {
//	}
//
//	sprintf(Parameter, "action=gblist&r=%s", GetGameInfo()->szRealmName);
//	strcpy(Buffer, GetSiteText(AuthURL(), Parameter));
//	argc = MakeParameter(Buffer, argv, '\n', false);
//
//	for (int i = 0; i < argc; i++) {
//		PlayerEnemyList->AddItem(argv[i]);
//	}
//	return 0;
//}
//
///*
//DWORD WINAPI IHPKThread(void* p) {
//char* argv[1024]={0};
//char Parameter[512];
//char Buffer[1024];
//int argc;
//
//LinkedItem* linkeditem;
//	for(linkeditem = PlayerIHPKList->GetFirstItem();linkeditem != NULL;linkeditem = PlayerIHPKList->RemoveItem(linkeditem)){
//		}
//sprintf(Parameter,"action=gflist&r=%s",GetGameInfo()->szRealmName);
//strcpy(Buffer,GetSiteText(IhpkURL(),Parameter));
//argc=MakeParameter(Buffer,argv,'\n',false);
//
//for(int i=0;i<argc;i++) {
//	PlayerIHPKList->AddItem(argv[i]);
//					Sleep(50);
//}
//return 0;
//}
//
//DWORD WINAPI HCPKThread(void* p) {
// char* argv[2048]={0};
//char Parameter[2048];
//char Buffer[2048];
//int argc;
//LinkedItem* linkeditem;
//	for(linkeditem = PlayerHCPKList->GetFirstItem();linkeditem != NULL;linkeditem = PlayerHCPKList->RemoveItem(linkeditem)){
//		}
//
//sprintf(Parameter,"action=gplist&r=%s",GetGameInfo()->szRealmName);
//strcpy(Buffer,GetSiteText(HcpkURL(),Parameter));
//argc=MakeParameter(Buffer,argv,'\n',false);
//
//for(int i=0;i<argc;i++) {
//	PlayerHCPKList->AddItem(argv[i]);
//	Sleep(50);
//	}
//return 0;
//}
//*/
//
///*
//
//DWORD WINAPI PrintPlayerStats(void* p) {
//	GainOnce=false;
//	if(GainOnce)
//	return TRUE;
//	GainOnce=true;
//	char *szBuffer= (char*)p;
//	char Buffer[2048]={0};
//	char Parameter[1024];
//	char* argv[1024];
//sprintf(Parameter,"action=info&a=%s&c=%s&r=%s",GetGameInfo()->szAccountName,GetGameInfo()->szCharName,GetGameInfo()->szRealmName);
//strcpy(Buffer,GetSiteText(AuthURL(),Parameter));
//DWORD argc=MakeParameter(Buffer,argv,'|',true);
//	strcpy(PKInfo.ForumName,argv[0]);
//	PKInfo.TotalKills=atoi(argv[1]);
//	PKInfo.TotalScore=atoi(argv[2]);
//	PKInfo.Rank=atoi(argv[3]);
//	PKInfo.Ready=true;
//	TimeOn++;
//return true;
//}
//*/
///*
//bool CheckIHPKEnemy(char* Name) {
//	LinkedItem* linkeditem;
//	for(linkeditem = PlayerIHPKList->GetFirstItem();linkeditem != NULL;linkeditem = PlayerIHPKList->GetNextItem(linkeditem)){
//		if(!_strcmpi(linkeditem->Name,Name))
//			return true;
//	}
//
//return false;
//}*/
//
///*
//BOOL OpenURL(char* szURL) {
//   HANDLE hURL;
//   HANDLE hInternetSession;
//
//   HANDLE gHandle = LoadLibrary("wininet");
//   if(!gHandle)
//	  return false;
//
//   __InternetOpen fp1;
//   fp1=(__InternetOpen)(DWORD)GetProcAddress((HINSTANCE)gHandle,"InternetOpenA");
//   __InternetOpenUrl fp2;
//   fp2=(__InternetOpenUrl)(DWORD)GetProcAddress((HINSTANCE)gHandle,"InternetOpenUrlA");
//
//   if(!fp1 || !fp2)
//	  return false;
//
//   hInternetSession = fp1("Microsoft Internet Explorer",INTERNET_OPEN_TYPE_PRECONFIG,NULL,NULL,0);
//   hURL = fp2(hInternetSession,szURL,NULL,0,0,0);
//   CloseHandle(hURL);
//   CloseHandle(hInternetSession);
//   return (BOOL)FreeLibrary((HINSTANCE)gHandle);
//}
//
//void Size(void)
//{
//HANDLE hFile;
//DWORD FileSize;
//hFile =CreateFileA("houdini.dll",.....);
//
//FileSize=GetFileSize(hFile,NULL); // <- return the file size
//
////CloseFile(hFile);
//CloseHandle(hFile);
//}
//*/
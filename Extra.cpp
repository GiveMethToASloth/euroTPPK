#include "EuroTPPK.h"

Control* pD2WinEditBox;

BOOL _stdcall EditBoxCallBack(Control* hwnd, DWORD arg2, DWORD arg3) {
	return true;
}

void wcscpy2(wchar_t* dest, char* src)
{
	do { *dest++ = *src; } while (*src++);
}
wchar_t wszGameName[32];
wchar_t wszGamePassword[32];
void SaveGameName()
{
	GameStructInfo* gi = D2CLIENT_GetGameInfo();
	if (*gi->szGameName) {
		wcscpy2(wszGameName, gi->szGameName);
		wcscpy2(wszGamePassword, gi->szGamePassword);
	}
}

void SetAllFalse(void)
{
	//	TerminateThread(AutoPartyMemberThread,0);
	//	TerminateThread(AutoPartyThread,0);
	HostPlayer = false;
	TakeNextTP = false;
	CampOn = false;
	CampUnitOn = false;
	Flash = false;
	GotBo = false;
	GotBc = false;
	GotSh = false;
	GotCa = false;
	GotOak = false;
	GotHu = false;
	GotEs = false;
	GotHs = false;
	GotEnch = false;
	GotCAr = false;
	GotSa = false;
	GotFa = false;
	GotFade = false;
	EnchBot = false;
	CastMissles = false;
	AutoPK = false;
	Units = false;
	NPCisSeleceted = false;
	hammerduel = false;
	Killed = false;
	BookTimer = 0;
	//Authn.totalVars = 0;
	return;
}
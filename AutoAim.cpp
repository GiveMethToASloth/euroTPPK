#include "EuroTPPK.h"

void AutoAim::GetNextPlayer() {
	int i = 0;
	int B = Current;
	Init();
	while (i < B && pUnit != NULL) {
		pUnit = pUnit->pNext;
		i++;
	}
	if (pUnit == NULL) { Current = 1; Init(); }
	else
		Current = B + 1;
}
long AutoAim::GetPlayerX() {
	if (pUnit == NULL)  Init();
	return pUnit->Xpos;
}
long AutoAim::GetPlayerY() {
	if (pUnit == NULL)  Init();
	return pUnit->Ypos;
}
int AutoAim::GetPlayerLevel() {
	if (pUnit == NULL) Init();
	return pUnit->wLevel;
}
int AutoAim::GetPlayerArea() {
	if (pUnit == NULL) Init();
	return pUnit->dwLevelId;
}
bool AutoAim::SelectPlayer(DWORD PID) {
	pUnit = (RosterUnit*)*(DWORD*)PlayerRoster;//0x6FBCC080;
	while (pUnit) {
		if (pUnit->dwUnitId == PID)
			return true;
		pUnit = pUnit->pNext;
	}
	return false;
}
bool AutoAim::SelectPlayerByName(char* Name) {
	pUnit = (RosterUnit*)*(DWORD*)PlayerRoster;//0x6FBCC080;
	while (pUnit) {
		if (!_strcmpi(pUnit->szName, Name))
			return true;
		pUnit = pUnit->pNext;
	}
	return false;
}

void AutoAim::Init() {
	pUnit = (RosterUnit*)*(DWORD*)PlayerRoster;//0x6FBCC080;
	Current = 1;
}

DWORD AutoAim::GetPlayerID() {
	if (pUnit == NULL) { Init(); return pUnit->dwUnitId; }
	return pUnit->dwUnitId;
}
char* AutoAim::GetPlayerNAME() {
	if (pUnit == NULL)  Init();
	return pUnit->szName2;
}
DWORD AutoAim::GetPlayerCLASS() {
	if (pUnit == NULL) Init();
	return pUnit->dwClassId;
}
//bool AutoAim::IsPlayerFriend() {
//	if (pUnit == NULL) Init();
//	return CheckPlayerFriend(GetPlayerNAME());
//}
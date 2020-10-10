#pragma once

DWORD GetPlayerID(UnitAny* pUnit);

WORD GetPlayerX(DWORD dwUnitId);
WORD GetPlayerY(DWORD dwUnitId);
POINT GetPlayerPosition(DWORD dwUnitId);
WORD GetPlayerXTarget(DWORD dwUnitId);
WORD GetPlayerYTarget(DWORD dwUnitId);
POINT GetPlayerTargetPosition(DWORD dwUnitId);
int GetLevelByName(char* Name);
char* GetClassByName(char* Name);
int GetIDByName(char* Name);
char* GetNameByID(DWORD dwUnitId);
bool GetPlayerRoster(RosterUnit* pUnit, DWORD nUnitId);
RosterUnit* FindPartyByName(char szName[0x16]);
RosterUnit* FindPartyById(DWORD dwUnitId);
int GetPvPStatus(DWORD nUnitId);
bool IsValidMonster(UnitAny* pUnit);
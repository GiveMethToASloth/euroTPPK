#include "EuroTPPK.h"

DWORD GetPlayerID(UnitAny* pUnit) {
  if (pUnit) {
    return pUnit->dwUnitId;
  }
  return NULL;
}

WORD GetPlayerX(DWORD dwUnitId) {
  UnitAny* pUnit = D2CLIENT_FindServerSideUnit(dwUnitId, UNIT_TYPE_PLAYER);
  if (pUnit != NULL)
    return pUnit->pPath->xPos;
  return 0;
}

WORD GetPlayerY(DWORD dwUnitId) {
  UnitAny* pUnit = D2CLIENT_FindServerSideUnit(dwUnitId, UNIT_TYPE_PLAYER);
  if (pUnit != NULL)
    return pUnit->pPath->yPos;
  return 0;
}

POINT GetPlayerPosition(DWORD dwUnitId) {
  UnitAny* pUnit = D2CLIENT_FindServerSideUnit(dwUnitId, UNIT_TYPE_PLAYER);
  if (pUnit != NULL) {
    return { LONG(pUnit->pPath->xPos), LONG(pUnit->pPath->yPos) };
  }
  return { NULL, NULL };
}

WORD GetPlayerXTarget(DWORD dwUnitId) {
  UnitAny* pUnit = D2CLIENT_FindServerSideUnit(dwUnitId, UNIT_TYPE_PLAYER);
  if (pUnit != NULL)
    return pUnit->pPath->xTarget;
  return 0;
}

WORD GetPlayerYTarget(DWORD dwUnitId) {
  UnitAny* pUnit = D2CLIENT_FindServerSideUnit(dwUnitId, UNIT_TYPE_PLAYER);
  if (pUnit != NULL)
    return pUnit->pPath->yTarget;
  return 0;
}

POINT GetPlayerTargetPosition(DWORD dwUnitId) {
  UnitAny* pUnit = D2CLIENT_FindServerSideUnit(dwUnitId, UNIT_TYPE_PLAYER);
  if (pUnit != NULL) {
    return { LONG(pUnit->pPath->xTarget), LONG(pUnit->pPath->yTarget) };
  }
  return { NULL, NULL };
}

int GetLevelByName(char* Name) {
  RosterUnit* pUnit = *p_D2CLIENT_PlayerUnitList;
  while (pUnit != NULL) {
    if (!_strcmpi(pUnit->szName, Name))
      return pUnit->wLevel;
    pUnit = pUnit->pNext;
  }

  return -1;
}

char* GetClassByName(char* Name) {
  RosterUnit* pUnit = *p_D2CLIENT_PlayerUnitList;
  while (pUnit != NULL) {
    if (!_strcmpi(pUnit->szName, Name))
      return GetD2ClassName(pUnit->dwClassId);
    pUnit = pUnit->pNext;
  }

  return NULL;
}

int GetIDByName(char* Name) {
  RosterUnit* pUnit = *p_D2CLIENT_PlayerUnitList;
  while (pUnit != NULL) {
    if (!_strcmpi(pUnit->szName, Name))
      return pUnit->dwUnitId;
    pUnit = pUnit->pNext;
  }
  return -1;
}

char* GetNameByID(DWORD dwUnitId) {
  RosterUnit* pUnit = *p_D2CLIENT_PlayerUnitList;
  while (pUnit != NULL) {
    if (pUnit->dwUnitId == dwUnitId) {
      return pUnit->szName;
    }
    pUnit = pUnit->pNext;
  }
  return "UNKNOWN";
}

bool GetPlayerRoster(RosterUnit* pUnit, DWORD nUnitId)
{
  for (RosterUnit* pUnit = D2CLIENT_PlayerList; pUnit; pUnit = pUnit->pNext)
    if (pUnit->dwUnitId == nUnitId)
      return true;
  return false;
}

RosterUnit* FindPartyByName(char szName[0x16])
{
  for (RosterUnit* pUnit = *p_D2CLIENT_PlayerUnitList; pUnit; pUnit = pUnit->pNext) {
    if (!_stricmp(szName, pUnit->szName)) {
      return pUnit;
    }
  }

  return NULL;
}

RosterUnit* FindPartyById(DWORD dwUnitId)
{
  for (RosterUnit* pUnit = *p_D2CLIENT_PlayerUnitList; pUnit; pUnit = pUnit->pNext) {
    if (pUnit->dwUnitId == dwUnitId) {
      return pUnit;
    }
  }

  return NULL;
}

int GetPvPStatus(DWORD nUnitId)
{
  RosterUnit* pUnit;

  for (pUnit = D2CLIENT_PlayerList; pUnit; pUnit = pUnit->pNext)
    if (pUnit->dwUnitId == nUnitId)
      break;

  if (!pUnit)
    return PVP_HOSTILE;

  UnitAny* mypUnit = D2CLIENT_GetPlayerUnit();

  RosterUnit* prPlayer;

  for (prPlayer = D2CLIENT_PlayerList; prPlayer; prPlayer = prPlayer->pNext)
    if (prPlayer->dwUnitId == mypUnit->dwUnitId)
      break;

  if (D2CLIENT_HostiledByMe(nUnitId, mypUnit->dwUnitId) || D2CLIENT_HostiledByUnit(mypUnit->dwUnitId))
    return PVP_HOSTILE;

  if (prPlayer && pUnit && pUnit->wPartyId != 0xFFFF && prPlayer->wPartyId == pUnit->wPartyId)
    return PVP_FRIENDLY;

  return PVP_NEUTRAL;
}

bool IsValidMonster(UnitAny* pUnit)
{
  if (!pUnit)
    return false;

  //Check to see if unit is dead.
  if ((pUnit->dwMode == 0) || (pUnit->dwMode == 12))
    return false;

  if ((pUnit->dwTxtFileNo >= 110) && (pUnit->dwTxtFileNo <= 113) || (pUnit->dwTxtFileNo == 608) && (pUnit->dwMode == 8))
    return false;

  // Ignore burrowing maggots
  if ((pUnit->dwTxtFileNo == 68) && (pUnit->dwMode == 14))
    return false;

  if (((pUnit->dwTxtFileNo == 258) || (pUnit->dwTxtFileNo == 261)) && (pUnit->dwMode == 14))
    return false;

  DWORD badMonIds[] = { 277, 283, 326, 327, 328, 329, 330, 410, 411, 412, 413, 414, 415, 416, 366, 406,
  351, 352, 353, 266, 408, 516, 517, 518, 519, 522, 523, 543, 545 };

  for (DWORD n = 0; n < ArraySize(badMonIds) - 1; n++)
  {
    if (pUnit->dwTxtFileNo == badMonIds[n])
      return false;
  }

  if (D2COMMON_GetUnitStat(pUnit, 172, 0) == 2)
    return false;

  wchar_t* name = D2CLIENT_GetUnitName(pUnit);
  char tmp[52];

  WToC(name, tmp);

  if ((strcmp(tmp, "an evil force") == 0) || (strcmp(tmp, "dummy") == 0) || (strcmp(tmp, "Maggot") == 0))
    return false;

  return true;
}
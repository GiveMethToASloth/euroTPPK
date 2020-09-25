#include "EuroTPPK.h"

bool GetPlayerRoster(RosterUnit* pUnit, DWORD nUnitId)
{
	for (RosterUnit* pUnit = D2CLIENT_PlayerList; pUnit; pUnit = pUnit->pNext)
		if (pUnit->dwUnitId == nUnitId)
			return true;
	return false;
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
#include "EuroTPPK.h"
#include <vector>
bool bFoundRejs;

int GetItemLocation(UnitAny* pItem)
{
	if (!pItem || !pItem->pItemData)
		return -1;

	switch (pItem->pItemData->ItemLocation)
	{
	case STORAGE_INVENTORY:
		return STORAGE_INVENTORY;

	case STORAGE_TRADE:
		if (pItem->pItemData->NodePage == NODEPAGE_STORAGE)
			return STORAGE_TRADE;

	case STORAGE_CUBE:
		return STORAGE_CUBE;

	case STORAGE_STASH:
		return STORAGE_STASH;

	case STORAGE_NULL:
		switch (pItem->pItemData->NodePage)
		{
		case NODEPAGE_EQUIP:
			return STORAGE_EQUIP;

		case NODEPAGE_BELTSLOTS:
			return STORAGE_BELT;
		}
	}

	return STORAGE_NULL;
}

UnitAny* __fastcall FindItem(DWORD dwCode, int nLoc)
{
	UnitAny* pPlayer = D2CLIENT_GetPlayerUnit();

	if (pPlayer) {
		if (pPlayer->pInventory) {
			UnitAny* pItem = D2COMMON_GetItemFromInventory(pPlayer->pInventory);
			while (pItem) {
				if (pItem->pItemData) {
					if (pItem->dwTxtFileNo == dwCode) {
						if (pItem->dwTxtFileNo == 518 && D2COMMON_GetUnitStat(pItem, STAT_AMMOQUANTITY, 0) == 0)
							continue;

						if (GetItemLocation(pItem) == nLoc)
							return pItem;
					}
					pItem = D2COMMON_GetNextItemFromInventory(pItem);
				}
			}
		}
	}
}

void UseItem(UnitAny* pItem) {
#pragma pack(push,1)
	struct pInvBelt {
		BYTE header;
		DWORD dwUnitId;
		DWORD dwX;
		DWORD dwY;
	};
#pragma pack(pop)
	if (pItem) {
		int nLoc = GetItemLocation(pItem);
		if (nLoc == STORAGE_INVENTORY) {
			pInvBelt pPacket = { 0x20, pItem->dwUnitId, D2CLIENT_GetPlayerUnit()->pPath->xPos, D2CLIENT_GetPlayerUnit()->pPath->yPos };
			D2NET_SendPacket(sizeof(pPacket), 1, (BYTE*)&pPacket);
		}
		else if (nLoc == STORAGE_BELT) {
			pInvBelt pPacket = { 0x26, pItem->dwUnitId, NULL, NULL };
			D2NET_SendPacket(sizeof(pPacket), 1, (BYTE*)&pPacket);
		}
	}
}

void UsePot(int nType)
{
	UnitAny* pPlayer = D2CLIENT_GetPlayerUnit();

	if (!pPlayer || pPlayer->pInventory->pCursorItem)
		return;

	char lpszText[100];

	if (nType == 0) sprintf(lpszText, "Drinking (Life) Potion!");
	else if (nType == 1) sprintf(lpszText, "Drinking (Mana) Potion!");
	else sprintf(lpszText, "Drinking (Rejuv) Potion!");

	std::vector<DWORD> PotCodes;

	switch (nType) {
	case 0:
		for (int i = 591; i > 586; i--)
			if (D2COMMON_GetUnitState(pPlayer, AFFECT_HEALTHPOT))
				return;
			else
				PotCodes.push_back(i);
		break;

	case 1:
		for (int i = 596; i > 591; i--)
			if (D2COMMON_GetUnitState(pPlayer, AFFECT_MANAPOT))
				return;
			else
				PotCodes.push_back(i);
		break;

	case 2:
		for (int i = 516; i > 514; i--)
			PotCodes.push_back(i);
		break;
	}

	UnitAny* pPot = nullptr;

	for (int i = 0; i < PotCodes.size(); i++) {
		pPot = FindItem(PotCodes[i], STORAGE_STASH);
		if (!pPot) pPot = FindItem(PotCodes[i], STORAGE_BELT);
		if (!pPot) pPot = FindItem(PotCodes[i], STORAGE_INVENTORY);
		if (!pPot) pPot = FindItem(PotCodes[i], STORAGE_CUBE);
		if (!pPot) continue;

		if (lpszText && lpszText[0])
		{
			OverheadMsg* pMsg = D2COMMON_GenerateOverheadMsg(NULL, lpszText, *p_D2CLIENT_OverheadTrigger);
			if (pMsg)
			{
				D2COMMON_FixOverheadMsg(pMsg, NULL);
				pPlayer->pOMsg = pMsg;
			}
		}

		UseItem(pPot);
		//LastPotion = GetTickCount64();
	}
}
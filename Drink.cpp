#include "EuroTPPK.h"
bool	bFoundRejs;

DWORD FindLife(void) {
UnitAny *pPlayer = D2CLIENT_GetPlayerUnit ();
	if(pPlayer) {
		if(pPlayer->pInventory) {
			UnitAny* p = D2COMMON_GetItemFromInventory(pPlayer->pInventory);
			while(p) {
				if(p->pItemData) {
					if(p->pItemData->ItemLocation != STORAGE_CUBE || p->pItemData->ItemLocation != STORAGE_STASH) {
					ItemTxt* pTxt=D2COMMON_GetItemText(p->dwTxtFileNo); //use to get itemcode
							if(pTxt) {
								char szCode[4];
								strncpy(szCode,pTxt->szCode,3);
								szCode[3]='\0';
									if(!_strcmpi(szCode,"hp5"))
										return p->dwUnitId; 
									if(!_strcmpi(szCode,"hp4"))
										return p->dwUnitId; 
									if(!_strcmpi(szCode,"hp3"))
										return p->dwUnitId; 
									if(!_strcmpi(szCode,"hp2"))
										return p->dwUnitId; 
									if(!_strcmpi(szCode,"hp1"))
									return p->dwUnitId; 
								else
									bFoundRejs=true; } }
				p=D2COMMON_GetNextItemFromInventory(p); 
			}
		}
	}
	}}
DWORD FindMana(void) {
	UnitAny *pPlayer = D2CLIENT_GetPlayerUnit ();
	if(pPlayer) {
		if(pPlayer->pInventory) {
			UnitAny* p = D2COMMON_GetItemFromInventory(pPlayer->pInventory);
			while(p) {
				if(p->pItemData) {
						if(p->pItemData->ItemLocation != STORAGE_CUBE || p->pItemData->ItemLocation != STORAGE_STASH) {
					ItemTxt* pTxt=D2COMMON_GetItemText(p->dwTxtFileNo); //use to get itemcode
							if(pTxt) {
								char szCode[4];
								strncpy(szCode,pTxt->szCode,3);
								szCode[3]='\0';
									if(!_strcmpi(szCode,"mp5"))
										return p->dwUnitId; 
									if(!_strcmpi(szCode,"mp4"))
										return p->dwUnitId; 
									if(!_strcmpi(szCode,"mp3"))
										return p->dwUnitId; 
									if(!_strcmpi(szCode,"mp2"))
										return p->dwUnitId;
									if(!_strcmpi(szCode,"mp1"))
										return p->dwUnitId;
								else
									bFoundRejs=true; } }
					p=D2COMMON_GetNextItemFromInventory(p);
			}
		}
	}
	}}
DWORD FindRejuv(void) {
	UnitAny *pPlayer = D2CLIENT_GetPlayerUnit ();
	if(pPlayer) {
		if(pPlayer->pInventory) {
			UnitAny* p = D2COMMON_GetItemFromInventory(pPlayer->pInventory);
			while(p) {
				if(p->pItemData) {
						if(p->pItemData->ItemLocation != STORAGE_CUBE || p->pItemData->ItemLocation != STORAGE_STASH) {
					ItemTxt* pTxt=D2COMMON_GetItemText(p->dwTxtFileNo); //use to get itemcode
							if(pTxt) {
								char szCode[4];
								strncpy(szCode,pTxt->szCode,3);
								szCode[3]='\0';
									if(!_strcmpi(szCode,"rvs"))
										return p->dwUnitId; 
									if(!_strcmpi(szCode,"rvl"))
										return p->dwUnitId; 
								else
									bFoundRejs=true; } }
					p=D2COMMON_GetNextItemFromInventory(p);
			}
		}
	}
	}}
BOOL DrinkLife(VOID) {
	UnitAny *pPlayer = D2CLIENT_GetPlayerUnit ();
	if(pPlayer) {
			BYTE DrinkLifePotion[13] = {0x26,0,0,0,0,0,0,0x00,0x00,0,0,0x00,0x00};
			BYTE DrinkLifePotion2[13] = {0x20,0,0,0,0,0,0,0x00,0x00,0,0,0x00,0x00};
			*(WORD*)&DrinkLifePotion2[5]=pPlayer->pPath->xPos;
			*(WORD*)&DrinkLifePotion2[9]=pPlayer->pPath->yPos;
			*(WORD*)&DrinkLifePotion[5]=0;
			*(WORD*)&DrinkLifePotion[9]=0;
			DWORD ID=FindLife();
			if(ID) {
				*(DWORD*)&DrinkLifePotion[1]=ID;
				*(DWORD*)&DrinkLifePotion2[1]=ID;
				SendGAMEPacket(DrinkLifePotion,sizeof(DrinkLifePotion));
				SendGAMEPacket(DrinkLifePotion2,sizeof(DrinkLifePotion2));
				//PrintMessage("::ÿc  Drinking (Life) Potion!",3);
				
				char lpszText[100];
				sprintf(lpszText,"Drinking (Life) Potion!");
	if(lpszText && lpszText[0])
		{
			UnitAny* pUnit = D2CLIENT_GetPlayerUnit();
            OverheadMsg* pMsg = D2COMMON_GenerateOverheadMsg(NULL, lpszText, *p_D2CLIENT_OverheadTrigger);
            if(pMsg)
				{
					D2COMMON_FixOverheadMsg(pMsg, NULL);
                    pUnit->pOMsg = pMsg;
                    }
	}


				return TRUE; }
			if(!ID) {
			if(v_PrintFailed)
		PrintMessage("::ÿc  Couldnt find any (Life) Potions!",1);
			}
        }
    }
BOOL DrinkMana(VOID) {
	UnitAny *pPlayer = D2CLIENT_GetPlayerUnit ();
	if(pPlayer) {
			BYTE DrinkMana[13] = {0x26,0,0,0,0,0,0,0x00,0x00,0,0,0x00,0x00};
			BYTE DrinkMana2[13] = {0x20,0,0,0,0,0,0,0x00,0x00,0,0,0x00,0x00};
			*(WORD*)&DrinkMana[5]=0;
			*(WORD*)&DrinkMana[9]=0;
			*(WORD*)&DrinkMana2[5]=pPlayer->pPath->xPos;
			*(WORD*)&DrinkMana2[9]=pPlayer->pPath->yPos;
			DWORD ID=FindMana();
			if(ID) {
				*(DWORD*)&DrinkMana[1]=ID;
				*(DWORD*)&DrinkMana2[1]=ID;
				SendGAMEPacket(DrinkMana,sizeof(DrinkMana));
				SendGAMEPacket(DrinkMana2,sizeof(DrinkMana2));
				//PrintMessage("::ÿc  Drinking (Mana) Potion!",3);
				char lpszText[100];
				sprintf(lpszText,"Drinking (Mana) Potion!");
				if(lpszText && lpszText[0])
		{
			UnitAny* pUnit = D2CLIENT_GetPlayerUnit();
            OverheadMsg* pMsg = D2COMMON_GenerateOverheadMsg(NULL, lpszText, *p_D2CLIENT_OverheadTrigger);
            if(pMsg)
				{
					D2COMMON_FixOverheadMsg(pMsg, NULL);
                    pUnit->pOMsg = pMsg;
                    }
	}

				return TRUE; }
			if(!ID) {
			if(v_PrintFailed)
		PrintMessage("::ÿc  Couldnt find any (Mana) Potions!",3);
			}
        }
    }
BOOL DrinkRejLife(VOID) {
	UnitAny *pPlayer = D2CLIENT_GetPlayerUnit ();
	if(pPlayer) {
			BYTE DrinkLifePotion[13] = {0x26,0,0,0,0,0,0,0x00,0x00,0,0,0x00,0x00};
			BYTE DrinkLifePotion2[13] = {0x20,0,0,0,0,0,0,0x00,0x00,0,0,0x00,0x00};
			*(WORD*)&DrinkLifePotion2[5]=pPlayer->pPath->xPos;
			*(WORD*)&DrinkLifePotion2[9]=pPlayer->pPath->yPos;
			*(WORD*)&DrinkLifePotion[5]=0;
			*(WORD*)&DrinkLifePotion[9]=0;
			DWORD ID=FindRejuv();
			if(ID) {
				*(DWORD*)&DrinkLifePotion[1]=ID;
				*(DWORD*)&DrinkLifePotion2[1]=ID;
				SendGAMEPacket(DrinkLifePotion,sizeof(DrinkLifePotion));
				SendGAMEPacket(DrinkLifePotion2,sizeof(DrinkLifePotion2));
			//	PrintMessage("::ÿc  Drinking (Rejuvenation) Potion!",3);
				char lpszText[100];
	sprintf(lpszText,"Drinking (Rejuvenation) Potion!");
	if(lpszText && lpszText[0])
		{
			UnitAny* pUnit = D2CLIENT_GetPlayerUnit();
            OverheadMsg* pMsg = D2COMMON_GenerateOverheadMsg(NULL, lpszText, *p_D2CLIENT_OverheadTrigger);
            if(pMsg)
				{
					D2COMMON_FixOverheadMsg(pMsg, NULL);
                    pUnit->pOMsg = pMsg;
                    }
	}


				return TRUE; }
			if(!ID) {
			if(v_PrintFailed)
		PrintMessage("::ÿc  Couldnt find any (Rejuvenation) Potions!",1);
			}
        }
    }
BOOL DrinkRejMana(VOID) {
	UnitAny *pPlayer = D2CLIENT_GetPlayerUnit ();
	if(pPlayer) {
			BYTE DrinkLifePotion[13] = {0x26,0,0,0,0,0,0,0x00,0x00,0,0,0x00,0x00};
			BYTE DrinkLifePotion2[13] = {0x20,0,0,0,0,0,0,0x00,0x00,0,0,0x00,0x00};
			*(WORD*)&DrinkLifePotion2[5]=pPlayer->pPath->xPos;
			*(WORD*)&DrinkLifePotion2[9]=pPlayer->pPath->yPos;
			*(WORD*)&DrinkLifePotion[5]=0;
			*(WORD*)&DrinkLifePotion[9]=0;
			DWORD ID=FindRejuv();
			if(ID) {
				*(DWORD*)&DrinkLifePotion[1]=ID;
				*(DWORD*)&DrinkLifePotion2[1]=ID;
				SendGAMEPacket(DrinkLifePotion,sizeof(DrinkLifePotion));
				SendGAMEPacket(DrinkLifePotion2,sizeof(DrinkLifePotion2));
				//PrintMessage("::ÿc  Drinking (Rejuvenation) Potion!",3);
								char lpszText[100];
	sprintf(lpszText,"Drinking (Rejuvenation) Potion!");
	if(lpszText && lpszText[0])
		{
			UnitAny* pUnit = D2CLIENT_GetPlayerUnit();
            OverheadMsg* pMsg = D2COMMON_GenerateOverheadMsg(NULL, lpszText, *p_D2CLIENT_OverheadTrigger);
            if(pMsg)
				{
					D2COMMON_FixOverheadMsg(pMsg, NULL);
                    pUnit->pOMsg = pMsg;
                    }
	}


				return TRUE; }
			if(!ID) {
				if(v_PrintFailed)
		PrintMessage("::ÿc  Couldnt find any (Rejuvenation) Potions!",1);
			}
        }
    }

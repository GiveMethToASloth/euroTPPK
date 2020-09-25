#include "EuroTPPK.h"
#define _VARS_DEF

DWORD WINAPI AutoPartyThread(LPVOID lpParameter)
{
	while(!GameReady ())
		SleepEx(10, true);

	while(true)
	{
		SleepEx(10, true);

     //   if (!v_EnchAutoParty)
	//		continue;

		BnetData *pData = *p_D2LAUNCH_BnData;
		//if (cPOIP && strlen(pData->szGamePass) == 0)
		//	continue;

		if (!GameReady ())
			continue;
		if (!v_EnchAutoParty)
			continue;

		UnitAny *pPlayer = D2CLIENT_GetPlayerUnit ();

		for (RosterUnit* pUnit = *p_D2CLIENT_PlayerList; pUnit; pUnit = pUnit->pNext)
		{
			if (pUnit->dwUnitId == pPlayer->dwUnitId)//We cannot party ourselves!!
				continue;//Continue loop if it is our RosterUnit

			switch(pUnit->dwPartyFlags)//Switch the party flags of this player
			{
				case PARTY_INVITED_YOU://They invited us to a party! Let's accept!
					D2CLIENT_clickParty(pUnit, clickParty_Accept);//Accept Party invitation
				break;
				case PARTY_NOT_IN_PARTY://They aren't in a party:( Let's invite them!:)
					D2CLIENT_clickParty(pUnit, clickParty_Invite);//Invite Player/
				break;
			}
		}
    }
}
DWORD WINAPI SpamMessage(LPVOID lpParameter)
{
	for(INT i = 0; i < v_SpamMessage.GetSize() && i <= 20; i++)
				{
					Say((LPSTR)v_SpamMessage[i]->Buffers[0]);
					Sleep(30);
				}
	return TRUE;
}


DWORD WINAPI PKMessage(LPVOID lpParameter)
{

			for(INT i = 0; i < v_DeathMessage.GetSize() && i <= 20; i++)
				{
					Say((LPSTR)v_DeathMessage[i]->Buffers[0]);
					Sleep(30);
				}
return TRUE;
}

		


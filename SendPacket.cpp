#include "EuroTPPK.h"
#include "Vars.h"
#define _VARS_DEF
DWORD AA, LeftAA;
DWORD SniffPacket;
DWORD Farcast;
bool CCursor = false;
bool Hammer = false;
bool sniff = false;
bool hammerduel = false;
bool BlindSpotAA = false;
bool bMaxedBreaks;
// Trigger hook
bool InputMessage(char** Msg, int argc)
{
	if (!_strcmpi(Msg[0], "reload")) {
		ReadConfigFile();
		PrintMessage("::ÿc  Reloaded Config!", 2);
		return true;
	}
	if (!_strcmpi(Msg[0], "resize")) {
		ToggleResolution(1300, 700, 3);
		ResizeD2();
		return true;
	}

	if (!_strcmpi(Msg[0], "Test")) {
		if (Test)
			Test = false;
		else Test = true;
		return true;
	}
	if (!_strcmpi(Msg[0], "aim")) {
		PrintConsoleString("Test !!!");
		return true;
	}
	// .chicken
	if (!_strcmpi(Msg[0], "chicken") && argc == 1) {
		PrintMessage("::ÿc  Syntax is .chicken drink <on/off>", 2);
		PrintMessage("::ÿc  Syntax is .chicken drink timer <ms>", 2);
		PrintMessage("::ÿc  Syntax is .chicken printfaileddrinks <on/off>", 2);
		PrintMessage("::ÿc  Syntax is .chicken drink life <%%>", 2);
		PrintMessage("::ÿc  Syntax is .chicken drink mana <%%>", 2);
		PrintMessage("::ÿc  Syntax is .chicken drink liferej <%%>", 2);
		PrintMessage("::ÿc  Syntax is .chicken drink manarej <%%>", 2);
		PrintMessage("::", 2);
		PrintMessage("::ÿc  Syntax is .chicken town life <%%>", 2);
		PrintMessage("::ÿc  Syntax is .chicken town mana <%%>", 2);
		PrintMessage("::", 2);
		PrintMessage("::ÿc  Syntax is .chicken quit life <%%>", 2);
		PrintMessage("::ÿc  Syntax is .chicken quit mana <%%>", 2);
		PrintMessage("", 2);
		PrintMessage("::ÿc  Syntax is .chicken hostile <0-4>", 2);
		PrintMessage("::ÿc  Syntax is .chicken aim <0-4>", 2);
		return true;
	}
	// .chicken drink
	if (!_strcmpi(Msg[0], "chicken") && (!_strcmpi(Msg[1], "drink") && argc == 2)) {
		PrintMessage("::ÿc  Syntax is .chicken drink <on/off>", 2);
		PrintMessage("::ÿc  Syntax is .chicken drink timer <ms>", 2);
		PrintMessage("::ÿc  Syntax is .chicken drink life <%%>", 2);
		PrintMessage("::ÿc  Syntax is .chicken drink mana <%%>", 2);
		PrintMessage("::ÿc  Syntax is .chicken drink liferej <%%>", 2);
		PrintMessage("::ÿc  Syntax is .chicken drink manarej <%%>", 2);
		return true;
	}
	// .chicken drink timer
	if (!_strcmpi(Msg[0], "chicken") && (!_strcmpi(Msg[1], "drink") && (!_strcmpi(Msg[2], "timer") && argc == 3))) {
		PrintMessage("::ÿc  Syntax is .chicken drink timer <ms>", 2);
		return true;
	}
	// .chicken drink life
	if (!_strcmpi(Msg[0], "chicken") && (!_strcmpi(Msg[1], "drink") && (!_strcmpi(Msg[2], "life") && argc == 3))) {
		PrintMessage("::ÿc  Syntax is .chicken drink life <%%>", 2);
		return true;
	}
	// .chicken drink mana
	if (!_strcmpi(Msg[0], "chicken") && (!_strcmpi(Msg[1], "drink") && (!_strcmpi(Msg[2], "mana") && argc == 3))) {
		PrintMessage("::ÿc  Syntax is .chicken drink mana <%%>", 2);
		return true;
	}
	// .chicken drink lifeRej
	if (!_strcmpi(Msg[0], "chicken") && (!_strcmpi(Msg[1], "drink") && (!_strcmpi(Msg[2], "liferej") && argc == 3))) {
		PrintMessage("::ÿc  Syntax is .chicken drink liferej <%%>", 2);
		return true;
	}
	// .chicken drink ManaRej
	if (!_strcmpi(Msg[0], "chicken") && (!_strcmpi(Msg[1], "drink") && (!_strcmpi(Msg[2], "manarej") && argc == 3))) {
		PrintMessage("::ÿc  Syntax is .chicken drink manarej <%%>", 2);
		return true;
	}
	// .
	if (!_strcmpi(Msg[0], "chicken") && (!_strcmpi(Msg[1], "town") && argc == 2)) {
		PrintMessage("::ÿc  Syntax is .chicken town life <%%>", 2);
		PrintMessage("::ÿc  Syntax is .chicken town mana <%%>", 2);
		return true;
	}
	// .chicken town life
	if (!_strcmpi(Msg[0], "chicken") && (!_strcmpi(Msg[1], "town") && (!_strcmpi(Msg[2], "life") && argc == 3))) {
		PrintMessage("::ÿc  Syntax is .chicken town life <%%>", 2);
		return true;
	}
	// .chicken town mana
	if (!_strcmpi(Msg[0], "chicken") && (!_strcmpi(Msg[1], "town") && (!_strcmpi(Msg[2], "mana") && argc == 3))) {
		PrintMessage("::ÿc  Syntax is .chicken town mana <%%>", 2);
		return true;
	}
	// .chicken quit
	if (!_strcmpi(Msg[0], "chicken") && (!_strcmpi(Msg[1], "town") && argc == 2)) {
		PrintMessage("::ÿc  Syntax is .chicken town life <%%>", 2);
		PrintMessage("::ÿc  Syntax is .chicken town mana <%%>", 2);
		return true;
	}
	// .chicken quit life
	if (!_strcmpi(Msg[0], "chicken") && (!_strcmpi(Msg[1], "quit") && (!_strcmpi(Msg[2], "life") && argc == 3))) {
		PrintMessage("::ÿc  Syntax is .chicken quit life <%%>", 2);
		return true;
	}
	// .chicken quit mana
	if (!_strcmpi(Msg[0], "chicken") && (!_strcmpi(Msg[1], "quit") && (!_strcmpi(Msg[2], "mana") && argc == 3))) {
		PrintMessage("::ÿc  Syntax is .chicken quit mana <%%>", 2);
		return true;
	}
	// .chicken hostile
	if (!_strcmpi(Msg[0], "chicken") && (!_strcmpi(Msg[1], "hostile") && argc == 2)) {
		PrintMessage("::ÿc  Syntax is .chicken hostile <0-4>", 2);
		return true;
	}
	// .chicken aim
	if (!_strcmpi(Msg[0], "chicken") && (!_strcmpi(Msg[1], "aim") && argc == 2)) {
		PrintMessage("::ÿc  Syntax is .chicken aim <0-4>", 2);
		return true;
	}
	// .bp
	if (!_strcmpi(Msg[0], "bp") && argc != 2) {
		PrintMessage("::ÿc  Syntax is .bp <on/off>", 2);
		return true;
	}
	// .questflags
	if (!_strcmpi(Msg[0], "questflags") && argc != 2) {
		PrintMessage("::ÿc  Syntax is .questflags <on/off>", 2);
		return true;
	}
	// .invite members
	if (!_strcmpi(Msg[0], "invitemembers") && argc != 2) {
		PrintMessage("::ÿc  Syntax is .invitemembers <on/off>", 2);
		return true;
	}
	// .loot members
	if (!_strcmpi(Msg[0], "lootmembers") && argc != 2) {
		PrintMessage("::ÿc  Syntax is .lootmembers <on/off>", 2);
		return true;
	}
	// .modifiers
	if (!_strcmpi(Msg[0], "Modifiers") && argc != 2) {
		PrintMessage("::ÿc  Syntax is .modifiers <on/off>", 2);
		return true;
	}
	// .Aimbox
	if (!_strcmpi(Msg[0], "aimbox") && argc != 2) {
		PrintMessage("::ÿc  Syntax is .aimbox <on/off>", 2);
		return true;
	}
	// .Enchbot
	if (!_strcmpi(Msg[0], "enchbot") && argc != 2) {
		PrintMessage("::ÿc  Syntax is .enchbot <on/off>", 2);
		return true;
	}
	// .winamp
	if (!_strcmpi(Msg[0], "winamp") && argc != 2) {
		PrintMessage("::ÿc  Syntax is .winamp <on/off>", 2);
		return true;
	}
	// .cc
	if (!_strcmpi(Msg[0], "cc") && argc != 2) {
		PrintMessage("::ÿc  Syntax is .cc <on/off>", 2);
		return true;
	}
	// .bp
	if (!_strcmpi(Msg[0], "ap") && argc != 2) {
		PrintMessage("::ÿc  Syntax is .ap <on/off>", 2);
		return true;
	}
	if (!_strcmpi(Msg[0], "clipcursor") && argc != 2) {
		PrintMessage("::ÿc  Syntax is .clipcursor <on/off>", 2);
		return true;
	}
	if (!_strcmpi(Msg[0], "farcast") && argc != 2) {
		PrintMessage("::ÿc  Syntax is .farcast <on/off>", 2);
		return true;
	}
	if (!_strcmpi(Msg[0], "hammer") && argc != 2) {
		PrintMessage("::ÿc  Syntax is .hammer <on/off>", 2);
		return true;
	}
	if (!_strcmpi(Msg[0], "hammerduel") && argc != 2) {
		PrintMessage("::ÿc  Syntax is .hammerduel <on/off>", 2);
		return true;
	}
	if (!_strcmpi(Msg[0], "setbp") && argc != 3) {
		PrintMessage("::ÿc  Syntax is .setbp <type> <value>", 2);
		return true;
	}
	if (!_strcmpi(Msg[0], "aa") && argc != 2) {
		PrintMessage("::ÿc  Syntax is .aa <type>", 2);
		return true;
	}

	// Chicken good!
	if (!_strcmpi(Msg[0], "chicken"))
	{
		if (!_strcmpi(Msg[1], "drink"))
		{
			if (!_strcmpi(Msg[2], "on"))
			{
				if (!v_AutoDrink) {
					PrintMessage("::ÿc  Drinking Enabled!", 2);
					v_AutoDrink = 1;
					return true;
				}
				else if (v_AutoDrink) {
					return true;
				}
			}
			else if (!_strcmpi(Msg[2], "off"))
			{
				if (v_AutoDrink) {
					PrintMessage("::ÿc  Drinking Disabled!", 2);
					v_AutoDrink = 0;
					return true;
				}
				else if (!v_AutoDrink) {
					return true;
				}
			}
			if (!_strcmpi(Msg[2], "timer") && argc == 4)
			{
				v_DrinkRejuTimer = atoi(Msg[3]);
				char Buffer[200];
				sprintf(Buffer, "::ÿc  Set DrinkRejuvTimer to %i", v_DrinkRejuTimer);
				PrintMessage(Buffer, 2);
				return true;
			}
			if (!_strcmpi(Msg[2], "Life") && argc == 4)
			{
				v_AutoDrinkLife = atoi(Msg[3]);
				char Buffer[20];
				sprintf(Buffer, "::ÿc  Set DrinkLife to %i", v_AutoDrinkLife);
				PrintMessage(Buffer, 2);
				return true;
			}
			if (!_strcmpi(Msg[2], "Mana") && argc == 4)
			{
				v_AutoDrinkMana = atoi(Msg[3]);
				char Buffer[20];
				sprintf(Buffer, "::ÿc  DrinkMana is set to %i", v_AutoDrinkMana);
				PrintMessage(Buffer, 2);
				return true;
			}
			if (!_strcmpi(Msg[2], "liferej") && argc == 4)
			{
				v_AutoDrinkReju = atoi(Msg[3]);
				char Buffer[20];
				sprintf(Buffer, "::ÿc  DrinkLifeRej is set to %i", v_AutoDrinkReju);
				PrintMessage(Buffer, 2);
				return true;
			}
			/*		if(!_strcmpi(Msg[2],"manarej") && argc==4)
						{
						v_AutoDrinkManaRej=atoi(Msg[3]);
						char Buffer[20];
						sprintf(Buffer,"::ÿc  DrinkManaRej is set to %i",v_AutoDrinkManaRej);
						PrintMessage(Buffer,2);
						return true;
						}*/
		}
		if (!_strcmpi(Msg[1], "town"))
		{
			if (!_strcmpi(Msg[2], "life") && argc == 4)
			{
				v_TownLifePercent = atoi(Msg[3]);
				char Buffer[20];
				sprintf(Buffer, "::ÿc  TownLifeChicken is set to %i", v_TownLifePercent);
				PrintMessage(Buffer, 2);
				return true;
			}
			if (!_strcmpi(Msg[2], "mana") && argc == 4)
			{
				v_TownManaPercent = atoi(Msg[3]);
				char Buffer[20];
				sprintf(Buffer, "::ÿc  TownManaChicken is set to %i", v_TownManaPercent);
				PrintMessage(Buffer, 2);
				return true;
			}
		}
		if (!_strcmpi(Msg[1], "quit"))
		{
			if (!_strcmpi(Msg[2], "life") && argc == 4)
			{
				v_QuitLifePercent = atoi(Msg[3]);
				char Buffer[20];
				sprintf(Buffer, "::ÿc  QuitLife is set to %i", v_QuitLifePercent);
				PrintMessage(Buffer, 2);
				return true;
			}
			if (!_strcmpi(Msg[2], "mana") && argc == 4)
			{
				v_QuitManaPercent = atoi(Msg[3]);
				char Buffer[20];
				sprintf(Buffer, "::ÿc  QuitMana is set to %i", v_QuitManaPercent);
				PrintMessage(Buffer, 2);
				return true;
			}
		}
		if (!_strcmpi(Msg[1], "quit"))
		{
			if (!_strcmpi(Msg[2], "life") && argc == 4)
			{
				v_QuitLifePercent = atoi(Msg[3]);
				char Buffer[20];
				sprintf(Buffer, "::ÿc  QuitLife is set to %i", v_QuitLifePercent);
				PrintMessage(Buffer, 2);
				return true;
			}
			if (!_strcmpi(Msg[2], "mana") && argc == 4)
			{
				v_QuitManaPercent = atoi(Msg[3]);
				char Buffer[20];
				sprintf(Buffer, "::ÿc  QuitMana is set to %i", v_QuitManaPercent);
				PrintMessage(Buffer, 2);
				return true;
			}
		}
		if (!_strcmpi(Msg[1], "hostile") && argc == 3)
		{
			v_HostileChicken = atoi(Msg[2]);
			if (v_HostileChicken == 0) {
				PrintMessage("::ÿc  Hostile Chicken is set to OFF", 2);
			}
			if (v_HostileChicken == 1) {
				PrintMessage("::ÿc  Hostile Chicken is set to TP", 2);
			}
			if (v_HostileChicken == 2) {
				PrintMessage("::ÿc  Hostile Chicken is set to TELE", 2);
			}
			if (v_HostileChicken == 3) {
				PrintMessage("::ÿc  Hostile Chicken is set to EXIT", 2);
			}
			if (v_HostileChicken == 4) {
				PrintMessage("::ÿc  Hostile Chicken is set to WARN", 2);
			}
			return true;
		}
		if (!_strcmpi(Msg[1], "aim") && argc == 3)
		{
			v_AimChicken = atoi(Msg[2]);
			if (v_AimChicken == 0)
				PrintMessage("::ÿc  Aim Chicken is set to OFF", 2);
			if (v_AimChicken == 1)
				PrintMessage("::ÿc  Aim Chicken is set to TP", 2);
			if (v_AimChicken == 2)
				PrintMessage("::ÿc  Aim Chicken is set to TELE", 2);
			if (v_AimChicken == 3)
				PrintMessage("::ÿc  Aim Chicken is set to EXIT", 2);
			if (v_AimChicken == 4) {
				PrintMessage("::ÿc  Aim Chicken is set to WARN", 2);
			}
			return true;
		}
		if (!_strcmpi(Msg[1], "printfaileddrinks")) {
			if (!_strcmpi(Msg[2], "on")) {
				v_PrintFailed = 1;
				PrintMessage("::ÿc  Activated Showing of Failed Drinks", 2);
				return true;
			}
			if (!_strcmpi(Msg[2], "off")) {
				v_PrintFailed = 0;
				PrintMessage("::ÿc  Deactivated Showing of Failed Drinks", 2);
				return true;
			}
		}
	}  // Chicken ends

	if (!_strcmpi(Msg[0], "bp")) {
		if (!_strcmpi(Msg[1], "on")) {
			MaxBPs();
			v_MaxBPs = true;
			PrintMessage("::ÿc  Loaded Maxed Breakpoints", 2);
			return true;
		}
		if (!_strcmpi(Msg[1], "off")) {
			UnloadMaxBPs();
			v_MaxBPs = false;
			PrintMessage("::ÿc  Unloaded Maxed Breakpoints", 2);
			return true;
		}
	}
	if (!_strcmpi(Msg[0], "questflags")) {
		if (!_strcmpi(Msg[1], "on")) {
			v_ShowQuestPackets = 1;
			PrintMessage("::ÿc  Activated Questflag Notifications", 2);
			return true;
		}
		if (!_strcmpi(Msg[1], "off")) {
			v_ShowQuestPackets = false;
			PrintMessage("::ÿc  Deactivated Questflag Notifications", 2);
			return true;
		}
	}

	if (!_strcmpi(Msg[0], "invitemembers")) {
		if (!_strcmpi(Msg[1], "on")) {
			v_InviteMembers = true;
			PrintMessage("::ÿc  Activated Automatic Invitation of Members", 2);
			return true;
		}
		if (!_strcmpi(Msg[1], "off")) {
			v_InviteMembers = false;
			PrintMessage("::ÿc  Deactivated Automatic Invitation of Members", 2);
			return true;
		}
	}
	if (!_strcmpi(Msg[0], "lootmembers")) {
		if (!_strcmpi(Msg[1], "on")) {
			v_LootMembers = true;
			PrintMessage("::ÿc  Activated Automatic Looting of Members", 2);
			return true;
		}
		if (!_strcmpi(Msg[1], "off")) {
			v_LootMembers = false;
			PrintMessage("::ÿc  Deactivated Automatic Looting of Members", 2);
			return true;
		}
	}
	if (!_strcmpi(Msg[0], "modifiers")) {
		if (!_strcmpi(Msg[1], "on")) {
			//cfg.DrawModifiers=1;
			PrintMessage("::ÿc  Activated Showing of Modifiers", 2);
			return true;
		}
		if (!_strcmpi(Msg[1], "off")) {
			//cfg.DrawModifiers=0;
			PrintMessage("::ÿc  Deactivated Showing of Modifiers", 2);
			return true;
		}
	}
	if (!_strcmpi(Msg[0], "aimbox")) {
		if (!_strcmpi(Msg[1], "on")) {
			v_AimBox = 1;
			PrintMessage("::ÿc  Activated Showing of Aimbox", 2);
			return true;
		}
		if (!_strcmpi(Msg[1], "off")) {
			v_AimBox = 0;
			PrintMessage("::ÿc  Deactivated Showing of Aimxbox", 2);
			return true;
		}
	}
	if (!_strcmpi(Msg[0], "winamp")) {
		if (!_strcmpi(Msg[1], "on")) {
			v_DrawSongTitle = 1;
			PrintMessage("::ÿc  Activated Showing of Winamp Track", 2);
			return true;
		}
		if (!_strcmpi(Msg[1], "off")) {
			v_DrawSongTitle = 0;
			PrintMessage("::ÿc  Deactivated Showing of Winamp Track", 2);
			return true;
		}
	}
	if (!_strcmpi(Msg[0], "enchbot")) {
		if (!_strcmpi(Msg[1], "on")) {
			char Buffer[200];
			if (!EnchBot) {
				EnchBot = true;
				PrintMessage("::ÿc  Enchbot Activated", 2);
				sprintf(Buffer, "EuTPPK Enchant bot Activated! Commands: %s , %s", v_EnchantMe, v_EnchantMerc/*,v_EnchantAll*/);
				PrintChat(Buffer);
				CreateThread(0, 0, AutoPartyThread, 0, 0, 0);
				return true;
			}
			else {
				return false;
			}
		}
		if (!_strcmpi(Msg[1], "off")) {
			if (EnchBot) {
				PrintMessage("::ÿc  Enchbot Deactivated", 2);
				PrintChat("Enchbot Deactivated!");
				TerminateThread(AutoPartyThread, 0);
				EnchBot = false;
				return true;
			}
			else {
				return false;
			}
		}
	}

	if (!_strcmpi(Msg[0], "help")) {
		PrintMessage("::ÿc  Commands:", 2);

		PrintMessage("::ÿc  .reload", 2);
		PrintMessage("::ÿc  .chicken <type> <value>", 2);

		PrintMessage("::ÿc  .bp <on/off>", 2);
		PrintMessage("::ÿc  .questflags <on/off>", 2);

		PrintMessage("::ÿc  .invitemembers <on/off>", 2);
		PrintMessage("::ÿc  .lootmembers <on/off>", 2);
		PrintMessage("::ÿc  .ap <on/off>", 2);

		PrintMessage("::ÿc  .modifiers <on/off>", 2);

		PrintMessage("::ÿc  .aimbox <on/off>", 2);
		PrintMessage("::ÿc  .enchbot <on/off>", 2);
		PrintMessage("::ÿc  .winamp <on/off>", 2);
		PrintMessage("::ÿc  .clipcursor <on/off>", 2);

		PrintMessage("::ÿc  .hammer <on/off>", 2);
		PrintMessage("::ÿc  .hammerduel <on/off>", 2);
		//PrintMessage("::ÿc  .farcast <on/off>",2);
		PrintMessage("::ÿc  .setbp <type> <value>", 2);
		PrintMessage("::ÿc  .aa <type>", 2);

		return true;
	}

	if (!_strcmpi(Msg[0], "units")) {
		if (Units) {
			Units = false;
			PrintMessage("::ÿc  Removing Unit Numbers & Type.", 2);
			return true;
		}
		else {
			Units = true;
			PrintMessage("::ÿc  Showing Unit Numbers & Type.", 2);
			return true;
		}
	}

	/*
	if(!_strcmpi(Msg[0],"cc")) {
		CCursor=false;
				RECT WindowRect;
				GetWindowRect(D2GFX_GetHwnd(),&WindowRect );
				ClipCursor( &WindowRect );
				PrintMessage("::ÿc  Clipping Cursor.",2);
			return true;
			}
			else  {
			CCursor=true;
			PrintMessage("::ÿc  Releasing Cursor.",2);
			ClipCursor( 0 );
			return true;
			}
	*/
	if (!_strcmpi(Msg[0], "clipcursor")) {
		if (!_strcmpi(Msg[1], "on")) {
			RECT WindowRect;
			GetWindowRect(D2GFX_GetHwnd(), &WindowRect);
			ClipCursor(&WindowRect);
			PrintMessage("::ÿc  Clipping Cursor.", 2);
			return true;
		}
		if (!_strcmpi(Msg[1], "off")) {
			ClipCursor(0);
			Set = false;
			PrintMessage("::ÿc  Releasing Cursor.", 2);
			return true;
		}
	}

	if (!_strcmpi(Msg[0], "ap")) {
		if (!_strcmpi(Msg[1], "on")) {
			CreateThread(0, 0, AutoPartyThread, 0, 0, 0);
			PrintMessage("::ÿc  Activating Autoparty.", 2);
		}
		if (!_strcmpi(Msg[1], "off")) {
			TerminateThread(AutoPartyThread, 0);
			PrintMessage("::ÿc  Deactivating Autoparty.", 2);
		}
	}
	if (!_strcmpi(Msg[0], "hammer")) {
		if (!_strcmpi(Msg[1], "on")) {
			PrintMessage("::ÿc  Autohammer Activated.", 2);
			GetD2MousePos(Camp);
			Hammer = true;
			return true;
		}
		if (!_strcmpi(Msg[1], "off")) {
			Hammer = false;
			PrintMessage("::ÿc  Autohammer Deactivated.", 2);
			HoldRightUp(Camp.x, Camp.y);
			return true;
		}
	}

	if (!_strcmpi(Msg[0], "aa")) {
		if (!_strcmpi(Msg[1], "blindspot")) {
			char lpszText[100];
			sprintf(lpszText, "Aiming @ Blindspot of Target: %s", Auto.GetPlayerNAME());
			if (lpszText && lpszText[0])
			{
				UnitAny* pUnit = D2CLIENT_GetPlayerUnit();
				OverheadMsg* pMsg = D2COMMON_GenerateOverheadMsg(NULL, lpszText, *p_D2CLIENT_OverheadTrigger);
				if (pMsg)
				{
					D2COMMON_FixOverheadMsg(pMsg, NULL);
					pUnit->pOMsg = pMsg;
				}
			}
			v_AAType = 3;
			Farcast = false;
			return true;
		}
		if (!_strcmpi(Msg[1], "namelock")) {
			char lpszText[100];
			sprintf(lpszText, "Namelocked Target: %s", Auto.GetPlayerNAME());
			if (lpszText && lpszText[0])
			{
				UnitAny* pUnit = D2CLIENT_GetPlayerUnit();
				OverheadMsg* pMsg = D2COMMON_GenerateOverheadMsg(NULL, lpszText, *p_D2CLIENT_OverheadTrigger);
				if (pMsg)
				{
					D2COMMON_FixOverheadMsg(pMsg, NULL);
					pUnit->pOMsg = pMsg;
				}
			}

			Farcast = true;
			v_AAType = 2;
			return true;
		}
		if (!_strcmpi(Msg[1], "cords")) {
			char lpszText[100];
			sprintf(lpszText, "Aiming @ cords of Target: %s", Auto.GetPlayerNAME());
			if (lpszText && lpszText[0])
			{
				UnitAny* pUnit = D2CLIENT_GetPlayerUnit();
				OverheadMsg* pMsg = D2COMMON_GenerateOverheadMsg(NULL, lpszText, *p_D2CLIENT_OverheadTrigger);
				if (pMsg)
				{
					D2COMMON_FixOverheadMsg(pMsg, NULL);
					pUnit->pOMsg = pMsg;
				}
			}

			v_AAType = 1;
			Farcast = false;
			return true;
		}
	}

	// BPS
	if (!_strcmpi(Msg[0], "setbp")) {
		if (!_strcmpi(Msg[1], "ias")) {
			v_BPIAS = atoi(Msg[2]);
			char Buffer[200];
			sprintf(Buffer, "::ÿc  Set IAS to %i", v_BPIAS);
			PrintMessage(Buffer, 2);
			MaximizeIAS();
			return true;
		}
		if (!_strcmpi(Msg[1], "fcr")) {
			v_BPFCR = atoi(Msg[2]);
			char Buffer[200];
			sprintf(Buffer, "::ÿc  Set FCR to %i", v_BPFCR);
			PrintMessage(Buffer, 2);
			MaximizeFCR();
			return true;
		}
		if (!_strcmpi(Msg[1], "fbr")) {
			v_BPFBR = atoi(Msg[2]);
			char Buffer[200];
			sprintf(Buffer, "::ÿc  Set FBR to %i", v_BPFBR);
			PrintMessage(Buffer, 2);
			MaximizeFBR();
			return true;
		}
		if (!_strcmpi(Msg[1], "fhr")) {
			v_BPFHR = atoi(Msg[2]);
			char Buffer[200];
			sprintf(Buffer, "::ÿc  Set FHR to %i", v_BPFHR);
			PrintMessage(Buffer, 2);
			MaximizeFHR();
			return true;
		}
	}

	if (!_strcmpi(Msg[0], "hammerduel")) {
		if (!_strcmpi(Msg[1], "on")) {
			hammerduel = true;
			PrintMessage("::ÿc  Activating Hammerdin Duelhelper.", 2);
			return true;
		}
		if (!_strcmpi(Msg[1], "off")) {
			hammerduel = false;
			PrintMessage("::ÿc  Deactivating Hammerdin Duelhelper.", 2);
			return true;
		}
	}

	if (!_strcmpi(Msg[0], "sniff"))
	{
		if (!_strcmpi(Msg[1], "in"))
		{
			SniffPacket = atoi(Msg[2]);
			char Buffer[200];
			sprintf(Buffer, "::ÿc  Sniffing %i", SniffPacket);
			sniff = true;
			PrintMessage(Buffer, 2);
			return true;
		}
	}

	return false;
}
bool Input(char* Text) {
	char* argv[32];
	char Buffer2[100];
	bool Called = false;

	if (Text[0] == '.') {
		strcpy(Buffer2, Text + 1);
		int argc = MakeParameter(Buffer2, argv, ' ', FALSE);
		if (InputMessage(argv, argc))
			return false;
		PrintMessage("::ÿc  Command not found!", 2);
		return false; // Return false, so it wont print
		return false;
	}
	return true;
}

DWORD __fastcall SendPacket(byte* data, DWORD len) {
	if (data[0] == 0x15) {
		char* bdata = (char*)data + 3;
		if (strlen(bdata) > 1)
			if (!Input(bdata))
				return -1;
	}

	if (hammerduel) {
		if (GameReady())
			if (!IsTownLevel(GetPlayerArea())) {
				if (data[0] == 0x3c) // Set Skill
					if (data[1] == D2S_BLESSEDHAMMER) {
						PrintMessage("Selected hammer -> Conc", 1);
						SetSkill(D2S_CONCENTRATION, bLeft);
						keybd_event(VK_SHIFT, 1, 0, 0);
					}
				if (data[1] == D2S_CHARGE) {
					PrintMessage("Selected Charge -> Vigor", 1);
					SetSkill(D2S_VIGOR, bLeft);
					keybd_event(VK_SHIFT, 1, 1, 0);
				}
				if (data[1] == D2S_TELEPORT) {
					PrintMessage("Selected Teleport -> Conc", 1);
					SetSkill(D2S_CONCENTRATION, bLeft);
					keybd_event(VK_SHIFT, 1, 1, 0);
				}
				/*	if(data[1] != D2S_BLESSEDHAMMER || D2S_CHARGE || D2S_TELEPORT)
					{ keybd_event (VK_SHIFT, 0, 1, 0); }*/
			}
	}
	BYTE NPCFollow[17] = { 0x59,0x01,0,0,0,0x00,0x00,0x00,0x00,0,0,0x00,0x00 ,0,0,0x00,0x00 };
	//if (NPCisSeleceted) {
	//	if (!FindUnit(NPCID, UNIT_MONSTER))
	//		return false;
	//	if (GetSkill(0xda)) {
	//		if (data[0] == 0x0c || data[0] == 0x0e || data[0] == 0x0f) {
	//			/*WORD MeX = D2CLIENT_MouseX;
	//			WORD MeY = D2CLIENT_MouseY;*/
	//			WORD MeX = GetPlayerX(D2CLIENT_GetPlayerUnit()->dwUnitId);
	//			WORD MeY = GetPlayerY(D2CLIENT_GetPlayerUnit()->dwUnitId);

	//			memcpy(&NPCFollow[5], &NPCID, sizeof(DWORD));
	//			memcpy(&NPCFollow[9], &MeX, sizeof(WORD));
	//			memcpy(&NPCFollow[13], &MeY, sizeof(WORD));
	//			SendGAMEPacket(NPCFollow, 17);
	//			//PrintMessage("::ÿc  Walking NPC...",3);
	//			char lpszText[100];
	//			sprintf(lpszText, "Walking NPC");
	//			if (lpszText && lpszText[0])
	//			{
	//				UnitAny* pUnit = D2CLIENT_GetPlayerUnit();
	//				OverheadMsg* pMsg = D2COMMON_GenerateOverheadMsg(NULL, lpszText, *p_D2CLIENT_OverheadTrigger);
	//				if (pMsg)
	//				{
	//					D2COMMON_FixOverheadMsg(pMsg, NULL);
	//					pUnit->pOMsg = pMsg;
	//				}
	//			}
	//			return -1;
	//		}
	//	}
	//}

	if (v_AAType == 2) {
		if (AA) {
			// Leftskill
			if (LeftAA)
				if (data[0] == 0x05 || data[0] == 0x08) {
					byte Packet[9] = { 0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
					*(DWORD*)&Packet[5] = Auto.GetPlayerID();
					SendGAMEPacket(Packet, 9);
					return -1;
				}
			// Rightskill
			if (!LeftAA)
				if (data[0] == 0x0c || data[0] == 0x0e || data[0] == 0x0f) {
					byte Packet[9] = { 0x0d,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
					*(DWORD*)&Packet[5] = Auto.GetPlayerID();
					SendGAMEPacket(Packet, 9);
					return -1;
				}
		}
	}
	if (data[0] == 0x3c)

		if (data[1] != D2S_TELEPORT)
			if (!bMaxedBreaks)
				MaximizeFCR();
	//D2CLIENT_GetPlayerUnit()->wFrameRate = 1000;
	return true; // closes sendpacket
}
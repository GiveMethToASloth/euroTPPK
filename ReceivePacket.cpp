#include "EuroTPPK.h"
#include "Vars.h"
#define AFFECT_JUST_PORTALED 102
bool bLeft;
bool EnchBot;
bool Teleported;
bool talk = false;
bool talk1 = false;
bool talk2 = false;

bool GotBo;
bool GotBc;
bool GotOak;
bool GotCa;
bool GotHu;
bool GotEs;
bool GotHs;
bool GotSh;
bool GotEnch;
bool GotCAr;
bool GotSa;
bool GotFa;
bool GotFade;

bool EnchListedPlayers() {
	LinkedItem* linkeditem;
	char Buffer[200];
	for (linkeditem = EnchList->GetFirstItem(); linkeditem != NULL; linkeditem = EnchList->GetNextItem(linkeditem))
	{
		SetSkill(D2S_ENCHANT, bLeft);
		BYTE* aPacket = new BYTE[9];
		aPacket[0] = bLeft ? 0x06 : 0x0D;
		*(DWORD*)&aPacket[1] = 0x00;
		*(DWORD*)&aPacket[5] = linkeditem->dwUnitId; // ??
		D2NET_SendPacket(9, 1, aPacket);
		Sleep(300);
		delete aPacket;
	}
	return TRUE;
}

bool EnchListedUnits() {
	LinkedItem* linkeditem;
	char Buffer[200];
	for (linkeditem = EnchList->GetFirstItem(); linkeditem != NULL; linkeditem = EnchList->GetNextItem(linkeditem))
	{
		SetSkill(D2S_ENCHANT, bLeft);
		BYTE* aPacket = new BYTE[9];
		aPacket[0] = bLeft ? 0x06 : 0x0D;
		*(DWORD*)&aPacket[1] = 0x01;
		*(DWORD*)&aPacket[5] = linkeditem->dwUnitId; // ??
		D2NET_SendPacket(9, 1, aPacket);
		Sleep(300);
		delete aPacket;
	}
	EnchListedPlayers();
	return TRUE;
}

DWORD WINAPI AutoPartyMemberThread(LPVOID P) {
	while (!GameReady())
		SleepEx(10, true);

	while (true)
	{
		TickCount();
		return 0;
	}
}

int RandomNumber(int high, int low)
{
	return ((rand() % high - low) + low + 1);
}

int GetLevelByName(char* Name) {
	RosterUnit* pUnit = (RosterUnit*)*(DWORD*)0x6FBCC080;
	while (pUnit != NULL) {
		if (!_strcmpi(pUnit->szName, Name))
			return pUnit->wLevel;
		pUnit = pUnit->pNext;
	}

	return -1;
}

char* GetClassByName(char* Name) {
	RosterUnit* pUnit = (RosterUnit*)*(DWORD*)0x6FBCC080;
	while (pUnit != NULL) {
		if (!_strcmpi(pUnit->szName, Name))
			return GetD2ClassName(pUnit->dwClassId);
		pUnit = pUnit->pNext;
	}

	return NULL;
}

int GetIDByName(char* Name) {
	RosterUnit* pUnit = (RosterUnit*)*(DWORD*)0x6FBCC080;
	UnitAny* Me = (UnitAny*)D2CLIENT_GetPlayerUnit();
	while (pUnit != NULL) {
		if (!_strcmpi(pUnit->szName, Name))
			return pUnit->dwUnitId;
		pUnit = pUnit->pNext;
	}
	return -1;
}

char* GetNameByID(DWORD PID) {
	RosterUnit* pUnit = (RosterUnit*)*(DWORD*)0x6FBCC080;
	while (pUnit) {
		if (pUnit->dwUnitId == PID) {
			return pUnit->szName;
		}
		pUnit = pUnit->pNext;
	}
	return "UNKNOWN";
}

bool __fastcall OnGamePacketReceived(LPBYTE aPacket, DWORD aLen)
{
	//if (aPacket[0] == 0x0E)
	//{
	//	char Buffer[100];
	//	UnitAny* TPUnit = (UnitAny*)FindUnit(*(LPDWORD)&aPacket[2], (DWORD)aPacket[1]);
	//	if (TPUnit && TPUnit->dwTxtFileNo == 0x3B) {
	//		//PrintMessage("OBJECT",8);
	//		aPacket[2] = 0xff;
	//		return FALSE;
	//	}
	//}
	if (aPacket[0] == 0x51)
	{
		if (aPacket[1] == UNIT_TYPE_OBJECT && *(LPWORD)&aPacket[6] == 0x3B) {
			aPacket[12] = 2;
		}
	}
	return TRUE;
}

DWORD __fastcall RecvPacket(byte* data, DWORD len) {
	char curTime[200];
	time_t ttTime;
	time(&ttTime);
	strftime(curTime, 100, "[%H:%M]", localtime(&ttTime));

	char Buffer[0x100];
	// Aurastacking drophack fix.
	/*if (data[0] == 0xAA)
	{
		*(DWORD*)(data + data[6]) = -1;
		data[6] += 4;
	}*/

	/*if (data[0] == 0x5b && data[1] == 0x24 && (*(DWORD*)&data[3] == D2CLIENT_GetPlayerUnit()->dwUnitId)) {
		if (GameReady())
		{
			//CheckAuth();
			SayOverHead("EuroTPPK 3.4");
			sprintf(Buffer, "%s Joined game %s", curTime, D2CLIENT_GetGameInfo()->szGameName);
			PrintConsoleString(Buffer);
			Auto.Init();
			RevealAct();
			//GetPlayers();
			nGameTimer = GetTickCount();
			SaveGameName();
			dwCurrentExp = D2COMMON_GetUnitStat(D2CLIENT_GetPlayerUnit(), 13, 0);
			TimeOn++;
			TimeOn1++;
			if (v_MaxBPs)
				MaxBPs();
			// Prot
		//	if(PlayerFriendList->GetItemCount()==0) {
		//		RemovePatchs();
			//	UninstallPatches();
		//	}

			if (IsDebuggerPresent())
			{
				PrintMessage("Debugger is present", 7);
				TerminateProcess(GetCurrentProcess(), 0);
			}
		}
	}*/
	// Anti Flash
	if (data[0] == 0x15)
	{
		if (*(DWORD*)&data[2] == D2CLIENT_GetPlayerUnit()->dwUnitId)
			data[10] = 0;
	}

	/*if (Units)
		if (data[0] == 0x77)
			if (data[1] == 0x0c) {
				data[1] = 0xff;
				PrintMessage("Left Trade", 5);
			}*/

			// Add Modifyers
	if (data[0] == 0xA8) {
		if (data[1] == 0x00) {
			if (*(DWORD*)&data[2] == D2CLIENT_GetPlayerUnit()->dwUnitId) {
				if (data[6] == 0x13) {
					if (data[7] == AFFECT_BATTLEORDERS) {
						if (!GotBo) {
							GotBo = true;
							Authn.totalVars += 1;
						}
					}
				}
				if (data[7] == AFFECT_BATTLECOMMAND) {
					if (!GotBc) {
						GotBc = true;
						Authn.totalVars += 1;
					}
				}
				if (data[7] == AFFECT_OAKSAGE) {
					if (!GotOak) {
						GotOak = true;
						Authn.totalVars += 1;
					}
				}
				if (data[6] == 0x0d) {
					if (data[7] == AFFECT_SHOUT) {
						if (!GotSh) {
							GotSh = true;
							Authn.totalVars += 1;
						}
					}
				}
				if (data[6] == 0x18) {
					if (data[7] == AFFECT_CYCLONEARMOR) {
						if (!GotCa) {
							GotCa = true;
							Authn.totalVars += 1;
						}
					}
				}
				if (data[6] == 0x0e) {
					if (data[7] == AFFECT_HURRICANE) {
						if (!GotHu) {
							GotHu = true;
							Authn.totalVars += 1;
						}
					}
				}
				if (data[6] == 0x0e) {
					if (data[7] == AFFECT_ENERGYSHIELD) {
						if (!GotEs) {
							GotEs = true;
							Authn.totalVars += 1;
						}
					}
				}
				if (data[6] == 0x10) {
					if (data[7] == AFFECT_HOLYSHIELD) {
						if (!GotHs) {
							GotHs = true;
							Authn.totalVars += 1;
						}
					}
				}
				if (data[6] == 0x12)
					if (data[7] == AFFECT_ENCHANT) {
						if (!GotEnch) {
							GotEnch = true;
							Authn.totalVars += 1;
						}
					}
				if (data[6] == 0x11)
					if (data[7] == AFFECT_CHILLINGARMOR) {
						if (!GotCAr) {
							GotCAr = true;
							Authn.totalVars += 1;
						}
					}
				if (data[6] == 0x11)
					if (data[7] == AFFECT_SHIVERARMOR) {
						if (!GotSa) {
							GotSa = true;
							Authn.totalVars += 1;
						}
					}
				if (data[6] == 0x11)
					if (data[7] == AFFECT_FROZENARMOR) {
						if (!GotFa) {
							GotFa = true;
							Authn.totalVars += 1;
						}
					}
				if (data[6] == 0x1d)
					if (data[7] == AFFECT_FADE) {
						if (!GotFade) {
							GotFade = true;
							Authn.totalVars += 1;
						}
					}
			}
		}
	}

	// Getting Oak from item
	if (data[0] == 0xA8) {
		if (data[1] == 0x01) {
			if (*(DWORD*)&data[2] == D2CLIENT_GetPlayerUnit()->dwUnitId) {
				if (data[7] == AFFECT_OAKSAGE) {
					if (!GotOak) {
						Authn.totalVars += 1;
						GotOak = true;
					}
				}
			}
		}
	}

	// Remove BO BC OAK
	if (data[0] == 0xA9) {
		if (data[1] == 0x00) {
			if (*(DWORD*)&data[2] == D2CLIENT_GetPlayerUnit()->dwUnitId) {
				if (data[6] == AFFECT_BATTLEORDERS) {
					if (GotBo) {
						Authn.totalVars -= 1;
						GotBo = false;
					}
				}
				if (data[6] == AFFECT_BATTLECOMMAND) {
					if (GotBc) {
						GotBc = false;
						Authn.totalVars -= 1;
					}
				}
				if (data[6] == AFFECT_ENERGYSHIELD) {
					if (GotEs) {
						GotEs = false;
						Authn.totalVars -= 1;
					}
				}
				if (data[6] == AFFECT_HOLYSHIELD) {
					if (GotHs) {
						GotHs = false;
						Authn.totalVars -= 1;
					}
				}
				if (data[6] == AFFECT_HURRICANE) {
					if (GotHu) {
						GotHu = false;
						Authn.totalVars -= 1;
					}
				}
				if (data[6] == AFFECT_SHOUT) {
					if (GotSh) {
						GotSh = false;
						Authn.totalVars -= 1;
					}
				}
				if (data[6] == AFFECT_CYCLONEARMOR) {
					if (GotCa) {
						GotCa = false;
						Authn.totalVars -= 1;
					}
				}
				if (data[6] == AFFECT_ENCHANT) {
					if (GotEnch) {
						GotEnch = false;
						Authn.totalVars -= 1;
					}
				}
				if (data[6] == AFFECT_CHILLINGARMOR) {
					if (GotCAr) {
						GotCAr = false;
						Authn.totalVars -= 1;
					}
				}
				if (data[6] == AFFECT_SHIVERARMOR) {
					if (GotSa) {
						GotSa = false;
						Authn.totalVars -= 1;
					}
				}
				if (data[6] == AFFECT_FADE) {
					if (GotFa) {
						GotFa = false;
						Authn.totalVars -= 1;
					}
				}
			}
		}
	}

	// Removing Oak made by item.
	if (data[0] == 0xA9) {
		if (data[1] == 0x01) {
			if (data[6] == 0xA1) {
				if (GotOak) {
					GotOak = false;
					Authn.totalVars -= 1;
				}
			}
		}
	}

	// New TP
	/*if (data[0] == 0x60)
		if (!IsTownLevel(GetPlayerArea()))
			if (TakeNextTP)
				if (FindUnit(*(DWORD*)&data[3], UNIT_OBJECT)) {
					UnitAny* TPUnit = (UnitAny*)FindUnit(*(DWORD*)&data[3], UNIT_OBJECT);
					if (TPUnit->pObjectPath)
						if (GetDistance(GetPosition().x, GetPosition().y, TPUnit->pObjectPath->dwPosX, TPUnit->pObjectPath->dwPosY) < 7) {
							BYTE TakeTP[9] = { 0x13,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
							*(DWORD*)&TakeTP[5] = *(DWORD*)&data[3];
							SendGAMEPacket(TakeTP, sizeof(TakeTP));
							TakeNextTP = false;
							if (!IsTownLevel(GetPlayerArea())) {
								TakeNextTP = true;
								if (MakeTP()) {
									TakeNextTP = true;
								}
							}
							char lpszText[100];
							sprintf(lpszText, "Townportal's Left: %d", GetTPs());
							SayOverHead(lpszText);

							CampOn = false;
							CampUnitOn = false;

							if (HostPlayer) {
								//					PrintMessage("::ÿc  Attempting to go up the Portal",3);
								HostileAll();
								//Hostile(Auto.GetPlayerID());
								HostPlayer = false;
								//PrintMessage("::ÿc  Hostiled!",3);
								SayOverHead("Hostiled!");
							}
						}
				}*/

				//Camping
				/*if (data[0] == 0x59)
					if (CampOn) {
						DWORD PlayerID = *(DWORD*)&data[1];
						if (GetPlayerID() != PlayerID) // om det inte är jag
							if (!CheckPlayerFriend(GetNameByID(PlayerID))) {
								Auto.SelectPlayer(PlayerID);
								//PrintMessage("Camp: Player found!",0);
								if (MakeTP()) {
									TakeNextTP = true;
									HostPlayer = true;
									CampOn = false;
									//	 PrintMessage("ÿc3::ÿc  TPPK'ing now this fucking hoe :o",0);
									//	 PrintMessage("::ÿc  Casting TP",3);
								}
								else {
									SayOverHead("TPPK Failed");
									//	PrintMessage("::ÿc  TPPK Faild!",3);
								}
							}
					}*/
					/*if (data[0] == 0x59)
						if (CampUnitOn) {
							char Buffer[200];
							DWORD PlayerID = *(DWORD*)&data[1];
							DWORD TargetID = Auto.GetPlayerID();
							if (PlayerID == TargetID) {
								if (!CheckPlayerFriend(GetNameByID(PlayerID))) {
									sprintf(Buffer, "%s Just Arrived!", (GetNameByID(Auto.GetPlayerID())));
									SayOverHead(Buffer);
									if (MakeTP()) {
										TakeNextTP = true;
										HostPlayer = true;
										CampUnitOn = false;
									}
								}
							}
							else {
								SayOverHead("That wasn't the Target!");
							}
						}
					*/

					// Anti AutoAim :)
				/*if (data[0] == 0x4c && data[1] == 0x00 && data[9] == 0x00 && !IsTownLevel(GetPlayerArea())) {
					char Buffer[200];
					DWORD ID = *(DWORD*)&data[10];
					DWORD AimID = *(DWORD*)&data[2];
					if (ID == GetPlayerID()) {
						if (v_AimChicken == 0) { // nada
							return 0;
						}
						if (v_AimChicken == 1) { // TP
							sprintf(Buffer, "Chickening with TP, %s Just Aimed at you!", (GetNameByID(AimID)));
							SayOverHead(Buffer);
							//PrintMessage(Buffer,FONTCOLOR_WHITE);
							if (!MakeTP())
								D2CLIENT_ExitGame();
							else TakeNextTP = true;
						}
						if (v_AimChicken == 2) { // TELE
							TakeNextTP = false;
							Teleported = false;
							if (GetSkill(D2S_TELEPORT)) {
								SetSkill(D2S_TELEPORT, bLeft);
								sprintf(Buffer, "Chickening with teleport, %s Just Aimed at you!", (GetNameByID(AimID)));
								SayOverHead(Buffer);
								//PrintMessage(Buffer,FONTCOLOR_WHITE);
								BYTE Packet2[] = { 0xc,00,00,00,00 };
								*(DWORD*)&Packet2[1] = GetPosition().x + RandomNumber(30, -30), 2;
								*(DWORD*)&Packet2[3] = GetPosition().y + RandomNumber(30, -30), 2;
								SendGAMEPacket(Packet2, sizeof(Packet2));
							}
							else  SayOverHead("Chickening Walk, No Teleport skill found!");
							//PrintMessage("::ÿc  Chickening Walk, No Teleport skill found!",1);
						}
						if (v_AimChicken == 3) { // Leave Game
							TakeNextTP = false;
							//SetAllFalse();
							D2CLIENT_ExitGame();
						}
						if (v_AimChicken == 4) { // Warn
							sprintf(Buffer, "%s Just Aimed at you!", (GetNameByID(AimID)));
							SayOverHead(Buffer);
							//PrintMessage(Buffer,FONTCOLOR_WHITE);
						}
					}
				}*/

				//Player Join
				/*if (data[0] == 0x5a) {
					if (data[1] == 0x02) {
						data[1] = 0xff;
						char Buffer[500];
						char Buffer1[500];
						char account[17], * name;
						char acco[10], * acc;
						name = (CHAR*)data + 8;
						acc = (CHAR*)data + 24;

						if (Auto.GetPlayerNAME() == "m" || Auto.GetPlayerNAME() == "'" || Auto.GetPlayerNAME() == "")
							Auto.GetNextPlayer();
						if (!strcmp(name, D2CLIENT_GetPlayerUnit()->pPlayerData->szName)) {
							if (!GainOnce) {
								PlayerStats();
								//LastPKNew();
							}
							return FALSE;
						}
						if (EnchBot)
							if (v_NotifyJoin)
								sprintf(Buffer, "/w %s EuroTPPK Enchbot is activated, usage <%s> <%s> <%s>", name, v_EnchantMe, v_EnchantMerc, v_EnchantAll);
						//BNCLIENT_SendBNMessage(Buffer);

						if (CheckPlayerFriend(name)) {
							sprintf(Buffer, "%s %s(*%s) a level %d %s has joined our world.", curTime, name, acc, GetLevelByName(name), GetClassByName(name));
							PrintMessage(Buffer, 4);
							sprintf(Buffer1, "%s is a EuroPK Member!", name);
							PrintMessageBottomLeft(Buffer1, 2);

							BYTE data[7];
							data[0] = 0x5D;
							*(LPWORD)&data[1] = 0x0101;
							*(LPDWORD)&data[3] = GetIDByName(name);
							SendGAMEPacket(data, 7);
							PrintMessageBottomLeft("Auto-Looted EuroPK Member", 3);

							BYTE data1[6];
							*(LPWORD)&data1[0] = 0x065E;
							*(LPDWORD)&data1[2] = GetIDByName(name);
							SendGAMEPacket(data1, 6);
							PrintMessageBottomLeft("Auto-Invited EuroPK Member!", 2);

							return TRUE;
						}
						if (CheckPlayerEnemy(acc)) {
							sprintf(Buffer, "%s %s(*%s) a level %d %s has joined our world.", curTime, name, acc, GetLevelByName(name), GetClassByName(name));
							PrintMessage(Buffer, 4);
							sprintf(Buffer1, "%s is on the BlackList!", name);
							PrintMessageBottomLeft(Buffer1, 1);
							return TRUE;
						}
						if (!strcmp(name, D2CLIENT_GetPlayerUnit()->pPlayerData->szName)) {
							return FALSE;
						}

						if (!CheckPlayerEnemy(name) && !CheckPlayerFriend(name)) {
							sprintf(Buffer, "%s %s(*%s) a level %d %s has joined our world.\n", curTime, name, acc, GetLevelByName(name), GetClassByName(name));
							PrintMessage(Buffer, 4);
							return TRUE;
						}
						data[1] = 0xff;
					}
				}*/

				// Player leave
				/*if (data[0] == 0x5a) {
					if (data[1] == 0x03) {
						char Buffer[200];
						char account[17], * name;
						char acco[10], * acc;
						name = (CHAR*)data + 8;
						acc = (CHAR*)data + 24;
						RosterUnit* pUnit = (RosterUnit*)*(DWORD*)0x6FBCC080;
						if (!strcmp(name, D2CLIENT_GetPlayerUnit()->pPlayerData->szName)) {
							return FALSE;
						}
						else {
							if (!strcmp(name, Auto.GetPlayerNAME()))
								Auto.GetNextPlayer();
							sprintf(Buffer, "%s %s(*%s) left our world. Diablo's minions weaken.", curTime, name, acc);
							PrintMessage(Buffer, 4);
						}

						data[1] = 0xff;
					}
				}*/
				/*
				02:07:35:498 GS 608:  0x8D   AssignPlayerToParty
					 UID:                2917678393
					 PartyNumber:        -1
				 8d   7   Assign Player To Party   8d [DWORD Player Id] [WORD Party Id]
				*/
				/*	if(data[0] == 0x8d )
						if(data[7] == 0x07)
							PrintMessage("Left Party",1);
				*/

				//Player hostiles
	/*if (data[0] == 0x5a)
		if (data[1] == 0x07 && data[2] == 0x08 && (!IsTownLevel(GetPlayerArea()))) {
			{
				DWORD PlayerID = *(DWORD*)&data[3];
				char Buffer[512];
				if (v_HostileChicken == 0) { //nothing
					return TRUE;
				}
				if (v_HostileChicken == 1) { //TP
					TakeNextTP = true;
					HostPlayer = false;
					sprintf(Buffer, "::ÿc  Chickening to town, hostiled by %s", (GetNameByID(PlayerID)));
					//PrintMessage(Buffer,1);
					SayOverHead(Buffer);
					if (!MakeTP()) {
						TakeNextTP = false;
						//	PrintMessage("::ÿc  Abort FastTP! Couldn't cast a TP!",1);
						//	PrintMessage("::ÿc  Calling ExitGame buy TPS!!!",1);
						D2CLIENT_ExitGame();
						return TRUE;
					}
					else return TRUE;//PrintMessage("::ÿc  FastTP!",3);
				}
				if (v_HostileChicken == 2) { //Teleport
					TakeNextTP = false;
					if (CampOn) return FALSE;
					if (CampUnitOn) return FALSE;
					if (GetSkill(D2S_TELEPORT)) {
						SetSkill(D2S_TELEPORT, bLeft);
						sprintf(Buffer, "Chickening with teleport, hostiled by %s", (GetNameByID(PlayerID)));
						//	PrintMessage(Buffer,1);
						SayOverHead(Buffer);
						BYTE Packet2[] = { 0xc,00,00,00,00 };
						*(DWORD*)&Packet2[1] = GetPosition().x + 15, 2;
						*(DWORD*)&Packet2[3] = GetPosition().y - 10, 2;
						SendGAMEPacket(Packet2, sizeof(Packet2));
						PrintMessage(Buffer, 0);
						return TRUE;
					}
					else PrintMessage("::ÿc  Chickening Walk, No Teleport skill found!", 1);
					TakeNextTP = true;
					HostPlayer = false;
					sprintf(Buffer, "Chickening to town, hostiled by %s", (GetNameByID(PlayerID)));
					//PrintMessage(Buffer,1);
					SayOverHead(Buffer);
				}
				if (v_HostileChicken == 3) { // Leave Game
					TakeNextTP = false;
					D2CLIENT_ExitGame();
					return TRUE;
				}
				if (v_HostileChicken == 4) { //WARN
					sprintf(Buffer, "Hostiled by %s!", (GetNameByID(PlayerID)));
					//PrintMessage(Buffer,1);
					SayOverHead(Buffer);
					return TRUE;
				}
			}
		}*/

		/*if (v_FastTele) {
			if (data[0] == 0x15)
			{
				UnitAny* pUnit = D2CLIENT_GetPlayerUnit();
				if (*(DWORD*)&data[2] == pUnit->dwUnitId)
				{
					bMaxedBreaks = false;
					MaximizeFCRTeleport();
					switch (pUnit->dwMode)
					{
					case PLAYER_MODE_BEING_HIT:
					case PLAYER_MODE_ATTACK1:
					case PLAYER_MODE_ATTACK2:
					case PLAYER_MODE_BLOCK:
					case PLAYER_MODE_CAST:
					case PLAYER_MODE_THROW:
					case PLAYER_MODE_KICK:
					case PLAYER_MODE_USESKILL1:
					case PLAYER_MODE_USESKILL2:
					case PLAYER_MODE_USESKILL3:
					case PLAYER_MODE_USESKILL4:
					case PLAYER_MODE_SEQUENCE:
					case PLAYER_MODE_BEING_KNOCKBACK:
						pUnit->dwFrameRemain = 0;
						break;
					}

						//if(pUnit->dwMode == PLAYER_MODE_DEATH || pUnit->dwMode == PLAYER_MODE_STAND_OUTTOWN ||
						//	pUnit->dwMode == PLAYER_MODE_WALK_OUTTOWN || pUnit->dwMode == PLAYER_MODE_RUN ||
						//	pUnit->dwMode == PLAYER_MODE_STAND_INTOWN || pUnit->dwMode == PLAYER_MODE_WALK_INTOWN ||
						//	pUnit->dwMode == PLAYER_MODE_DEAD || pUnit->dwMode == PLAYER_MODE_SEQUENCE ||
						//	pUnit->dwMode == PLAYER_MODE_BEING_KNOCKBACK)
						//	return TRUE;

						//pUnit->dwFrameRemain = 0;
				}
			}
		}*/
		// Blocks the After taking a TP Delay.
	/*if (data[0] == 0xA7)
	{
		if (data[6] == AFFECT_JUST_PORTALED)
			return -1;
	}*/

	// questPacket
	/*if (data[0] == 0x89)
		if (v_ShowQuestPackets)
		{
			char Buffer[200];
			if (data[1] == 0) {
				PrintMessage("Quest: Den Of Evil", FONTCOLOR_WHITE);
				return TRUE;
			}
			if (data[1] == 1) {
				PrintMessage("Quest: Tristram", FONTCOLOR_WHITE);
				return TRUE;
			}
			if (data[1] == 3) {
				PrintMessage("Quest: Tal-Rashas Tomb", FONTCOLOR_WHITE);
				return TRUE;
			}
			if (data[1] == 6) {
				PrintMessage("Quest: Claw-Viper Temple", FONTCOLOR_WHITE);
				return TRUE;
			}
			if (data[1] == 7) {
				PrintMessage("Quest: Summoner", FONTCOLOR_WHITE);
				return TRUE;
			}
			if (data[1] == 8) {
				PrintMessage("Quest: Duriel", FONTCOLOR_WHITE);
				return TRUE;
			}
			if (data[1] == 11) {
				PrintMessage("Quest: Mephisto", FONTCOLOR_WHITE);
				return TRUE;
			}
			if (data[1] == 12) {
				PrintMessage("Quest: Diablo", FONTCOLOR_WHITE);
				return TRUE;
			}
			if (data[1] == 13) {
				PrintMessage("Quest: Classic Diablo", FONTCOLOR_WHITE);
				return TRUE;
			}
			if (data[1] == 14) {
				PrintMessage("Quest: Hellfroge", FONTCOLOR_WHITE);
				return TRUE;
			}
			if (data[1] == 15) {
				PrintMessage("Quest: Shenk", FONTCOLOR_WHITE);
				return TRUE;
			}
			if (data[1] == 16) {
				PrintMessage("Quest: Anya", FONTCOLOR_WHITE);
				return TRUE;
			}
			if (data[1] == 17) {
				PrintMessage("Quest: Nilathak", FONTCOLOR_WHITE);
				return TRUE;
			}
			if (data[1] == 18) {
				PrintMessage("Quest: Ancients", FONTCOLOR_WHITE);
				return TRUE;
			}
			if (data[1] == 19) {
				PrintMessage("Quest: Baal", FONTCOLOR_WHITE);
				return TRUE;
			}
			else {
				sprintf(Buffer, "data was %d Please report this to Jonas", data[1]);
				PrintMessage(Buffer, FONTCOLOR_WHITE);
				return TRUE;
			}
		}*/

		// Leech Bot
		// Modifys talk.
		//if (!EnchBot)
		//	if (data[0] == 0x26) {
		//		if (data[1] == 0x01) {   // Normal Talk [0x05 = over head] [
		////	char Buffer[300];
		//			char* argv[300] = { 0 };
		//			LPSTR MyName = D2CLIENT_GetPlayerUnit()->pPlayerData->szName;
		//			LPSTR lpPlayerName = (LPSTR)&data[10];
		//			LPSTR lpMessage = (LPSTR)&data[strlen(lpPlayerName) + 11];
		//			if (CheckSpammerName(lpPlayerName)) {
		//				data[1] = 0xff;
		//				return true;
		//			}
		//			/*if(CheckPlayerFriend(lpPlayerName)) {
		//			sprintf(Buffer,"%sÿc2 %sÿc0: %s\n",curTime,lpPlayerName,lpMessage);
		//			PrintMessage(Buffer,4);
		//			return TRUE;
		//			}
		//			if(CheckPlayerEnemy(lpPlayerName)) {
		//			sprintf(Buffer,"%sÿc1 %sÿc0: %s\n",curTime,lpPlayerName,lpMessage);
		//			PrintMessage(Buffer,4);
		//			return TRUE;
		//			}
		//			else {
		//			sprintf(Buffer,"%sÿc4 %sÿc0: %s\n",curTime,lpPlayerName,lpMessage);
		//			PrintMessage(Buffer,4);
		//			return TRUE;
		//				}*/
		//		}
		//	}
		//return TRUE;

		/*if (data[0] == 0x26)
		{
			if (data[1] == 0xff) {
				LPSTR MyName = D2CLIENT_GetPlayerUnit()->pPlayerData->szName;
				LPSTR lpPlayerName = (LPSTR)&data[10];
				LPSTR lpMessage = (LPSTR)&data[strlen(lpPlayerName) + 11];
				RosterUnit* lpPlayer = FindPartyByName(lpPlayerName);
				UnitAny* pUnit = (UnitAny*)FindUnit(GetIDByName(lpPlayerName), UNIT_TYPE_PLAYER);
				UnitAny* pMe = (UnitAny*)FindUnit(GetIDByName(MyName), UNIT_TYPE_PLAYER);

				if (!_stricmp(lpMessage, MyName)) {
					talk = true;
				}
				if (talk)
					if (!_stricmp(lpMessage, "Hi")) {
						talk1 = true;
					}
				if (talk1)
					if (!_stricmp(lpMessage, "Sup")) {
						talk2 = true;
					}
				if (talk && talk1 && talk2)
					while (D2CLIENT_GetPlayerUnit());
			}
		}*/

		//Ench
		//if (EnchBot) {
		//	if (data[0] == 0x26)
		//	{
		//		LPSTR MyName = D2CLIENT_GetPlayerUnit()->pPlayerData->szName;
		//		LPSTR lpPlayerName = (LPSTR)&data[10];
		//		LPSTR lpMessage = (LPSTR)&data[strlen(lpPlayerName) + 11];
		//		RosterUnit* lpPlayer = FindPartyByName(lpPlayerName);
		//		UnitAny* pUnit = (UnitAny*)FindUnit(GetIDByName(lpPlayerName), UNIT_TYPE_PLAYER);
		//		UnitAny* pMe = (UnitAny*)FindUnit(GetIDByName(MyName), UNIT_TYPE_PLAYER);
		//		char Buffer[100];

		//		if (!_stricmp(lpMessage, v_EnchantMe)) {
		//			if (FindUnit(GetIDByName(lpPlayerName), 0) != NULL) {
		//				UnitAny* pUnit = (UnitAny*)FindUnit(GetIDByName(lpPlayerName), UNIT_TYPE_PLAYER);
		//				if (D2CLIENT_GetPlayerUnit())
		//					if (GetSkill(D2S_ENCHANT))
		//						SetSkill(D2S_ENCHANT, bLeft);
		//				BYTE* aPacket = new BYTE[9];
		//				aPacket[0] = bLeft ? 0x06 : 0x0D;
		//				*(DWORD*)&aPacket[1] = pUnit->dwType;
		//				*(DWORD*)&aPacket[5] = pUnit->dwUnitId;
		//				D2NET_SendPacket(9, 1, aPacket);
		//				delete aPacket;
		//				return TRUE;
		//			}
		//			PrintChat("Couldn't find you!");
		//			return FALSE;
		//		}
		//		if (!_stricmp(lpMessage, v_EnchantMerc)) {
		//			if (D2CLIENT_GetPlayerUnit() && D2CLIENT_GetPlayerUnit()->pAct)
		//			{
		//				for (Room1* pRoom = D2CLIENT_GetPlayerUnit()->pAct->pRoom1; pRoom; pRoom = pRoom->pRoomNext)
		//				{
		//					for (UnitAny* pUnit = pRoom->pUnitFirst; pUnit; pUnit = pUnit->pListNext)
		//					{
		//						if (pUnit->dwType == UNIT_MONSTER)
		//							if (pUnit->dwTxtFileNo == MERC_A1 || pUnit->dwTxtFileNo == MERC_A2 || pUnit->dwTxtFileNo == MERC_A3 || pUnit->dwTxtFileNo == MERC_A5)
		//								if (D2CLIENT_GetMonsterOwner(pUnit->dwUnitId) == GetIDByName(lpPlayerName))
		//								{
		//									SetSkill(D2S_ENCHANT, bLeft);
		//									BYTE* aPacket = new BYTE[9];
		//									aPacket[0] = bLeft ? 0x06 : 0x0D;
		//									*(DWORD*)&aPacket[1] = pUnit->dwType;
		//									*(DWORD*)&aPacket[5] = pUnit->dwUnitId;
		//									D2NET_SendPacket(9, 1, aPacket);
		//									delete aPacket;
		//									return TRUE;
		//								}
		//					}
		//				}
		//				PrintChat("Couldn't find your mercenary!");
		//				return FALSE;
		//			}
		//		}
		//		if (!_stricmp(lpMessage, v_EnchantAll)) {
		//			LinkedItem* linkeditem;
		//			for (linkeditem = EnchList->GetFirstItem(); linkeditem != NULL; linkeditem = EnchList->RemoveItem(linkeditem)) {}
		//			if (D2CLIENT_GetPlayerUnit() && D2CLIENT_GetPlayerUnit()->pAct)
		//			{
		//				for (Room1* pRoom = D2CLIENT_GetPlayerUnit()->pAct->pRoom1; pRoom; pRoom = pRoom->pRoomNext)
		//				{
		//					for (UnitAny* pUnit = pRoom->pUnitFirst; pUnit; pUnit = pUnit->pListNext)
		//					{
		//						if (pUnit->dwType == UNIT_PLAYER && pUnit->dwUnitId != D2CLIENT_GetPlayerUnit()->dwUnitId)
		//							if (pUnit->dwUnitId == GetIDByName(lpPlayerName))
		//							{
		//								EnchList->AddItem1(pUnit->dwUnitId);
		//							}
		//						if (pUnit->dwType == UNIT_MONSTER)
		//							if (D2CLIENT_GetMonsterOwner(pUnit->dwUnitId) == GetIDByName(lpPlayerName))
		//							{
		//								EnchList->AddItem1(pUnit->dwUnitId);
		//							}
		//					}
		//				}
		//			}
		//			EnchListedUnits();
		//			return TRUE;
		//		}

		//		/*		if(!_stricmp(lpMessage, v_EnchantAll )) {
		//			//	PrintMessage("got EnchAll trigger",1);
		//				if(D2CLIENT_GetPlayerUnit() && D2CLIENT_GetPlayerUnit()->pAct)
		//			{
		//				for(Room1* pRoom = D2CLIENT_GetPlayerUnit()->pAct->pRoom1; pRoom; pRoom = pRoom->pRoomNext)
		//				{
		//					for(UnitAny* pUnit = pRoom->pUnitFirst; pUnit; pUnit = pUnit->pListNext)
		//					{
		//						if(pUnit->dwType == UNIT_PLAYER && pUnit->dwUnitId!=D2CLIENT_GetPlayerUnit()->dwUnitId)
		//							{
		//									SetSkill(D2S_ENCHANT, bLeft);
		//									BYTE *aPacket = new BYTE[9];
		//									aPacket[0] = bLeft ? 0x06 : 0x0D;
		//									*(DWORD*)&aPacket[1] = pUnit->dwType;
		//									*(DWORD*)&aPacket[5] = pUnit->dwUnitId;
		//									D2NET_SendPacket(9, 1, aPacket);
		//									delete aPacket;
		//									Sleep(80);
		//								}
		//							if(pUnit->dwType == UNIT_MONSTER) {
		//								if(D2CLIENT_GetMonsterOwner(pUnit->dwUnitId) == GetIDByName(lpPlayerName))
		//								{
		//									SetSkill(D2S_ENCHANT, bLeft);
		//									BYTE *aPacket = new BYTE[9];
		//									aPacket[0] = bLeft ? 0x06 : 0x0D;
		//									*(DWORD*)&aPacket[1] = pUnit->dwType;
		//									*(DWORD*)&aPacket[5] = pUnit->dwUnitId;
		//									D2NET_SendPacket(9, 1, aPacket);
		//									delete aPacket;
		//									Sleep(80);
		//								}
		//							}
		//					}
		//				}
		//				}
		//				} */
		//	}
		//} // enchs
		/*
		jOhan säger:
		thezoidberg
		jOhan säger:
		tupac10
		jOhan säger:
		captainfry // tupac10
		*/
		// PK logging etc..
		/*if (data[0] == 0x5a && data[1] == 0x06) {
			char* opfer = (char*)&data[0x8];
			char* Killer = (char*)&data[0x18];
			char Buf[100] = { 0 };

			if (!_strcmpi(GetGameInfo()->szCharName, Killer)) {
				if (!((*p_D2LAUNCH_BnData)->nCharFlags & PLAYER_TYPE_HARDCORE))
					return TRUE;

				if (GetLevelByName(opfer) >= v_LogPksOver) {
					TimeOn1 = 0;
					TimeOn1++;
					ssTimer++;
					SendPK(opfer, GetLevelByName(opfer), GetClassByName(opfer));
					PlayerStatsNew();
					if (v_UseDeathMessage)
						CreateThread(0, 0, PKMessage, 0, 0, 0);
				}
			}
		}*/
		/*if (sniff)
		{
			if (data[0] == SniffPacket) {
				char Buffer[100];
				DWORD data0 = data[0];
				DWORD data1 = data[1];
				DWORD data2 = data[2];
				DWORD data3 = data[3];
				DWORD data4 = data[4];
				DWORD data5 = data[5];
				DWORD data6 = data[6];
				DWORD data7 = data[7];
				DWORD data8 = data[8];
				DWORD data9 = data[9];
				DWORD data10 = data[10];
				sprintf(Buffer, "%d %d %d %d %d %d %d %d %d %d %d", data0, data1, data2, data3, data4, data5, data6, data7, data8, data9, data10);
				PrintMessage(Buffer, 4);
			}
		}*/

	return true; //end of ReceivePacket
}

/*
	char Buffer[1024];
	char Buffer2[1024];
	strcpy(Buffer2,cfg.Message);
	strcpy(Buffer,cfg.Message);
	if(strstr(Buffer2,"%TargetName%")!=0)
		strcpy(Buffer,ReplaceString(Buffer2,"%TargetName%",opfer));
		strcpy(Buffer2,Buffer);
		if(strstr(Buffer2,"%TargetLevel%")!=NULL)
			strcpy(Buffer,ReplaceString(Buffer2,"%TargetLevel%",mitoa(GetLevelByName(opfer))));
			strcpy(Buffer2,Buffer);
			if(strstr(Buffer2,"%MyName%")!=NULL)
				strcpy(Buffer,ReplaceString(Buffer2,"%MyName%",GetGameInfo()->szCharName));
				strcpy(Buffer2,Buffer);
					if(strstr(Buffer2,"%MyLevel%")!=NULL)
						strcpy(Buffer,ReplaceString(Buffer2,"%MyLevel%",mitoa(GetLevelByName(GetGameInfo()->szCharName))));
						char* argv[500]={0};
						int argc=MakeParameter(Buffer,argv, 'ÿ',false);
						for(int i=0;i<argc;i++) {
						PrintChat(argv[i]);
						Sleep(100);
						return TRUE;
						}
					return TRUE;
}
		}
return TRUE;		}
*/

/*	if(!((*p_D2LAUNCH_BnData)->nCharFlags & PLAYER_TYPE_HARDCORE)) {
PrintMessage("::ÿc  Softcore kills doesn't count!!",1);
return TRUE;
}*/
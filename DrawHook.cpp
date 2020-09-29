#include "EuroTPPK.h"
// config forcing
bool ServerInfo = false;
bool TargetList = false;
bool PlyerInfo = false;
bool InfoToggle = false;
bool Target = false;
bool Set = false;
bool Done = false;
bool lol = false;
bool Killed = false;
POINT EnemyList;
POINT EnemyMoveList;

int LastLvl = 0; // for maphack revealing
int LastLvl1 = 0;
DWORD TimeOn;
DWORD TimeOn1;
DWORD BookTimer;
DWORD ssTimer;
bool Units = false;
Vector GlobalVectors;

void D2DrawLine(int x, int y, int x2, int y2, DWORD color) {
	D2GFX_DrawLine(x, y, x2, y2, color, 0xff);
}

void GiveFinger(void) {
	PrintChat(" ................/´¯/)");
	PrintChat(" ............. /.¯.// ");
	PrintChat(" ........... /. ..// ");
	PrintChat(" .../´¯`/.. . ../´¯¯`·¸ ");
	PrintChat(" ../../ / . .. / . . /¨/¯`\ ");
	PrintChat(" . (..( . . ´ .. ´ ¯:/.. ..) ");
	PrintChat(" ..\. . . . . . . . ` . . / ");
	PrintChat("I JuSt TuRn You iNto my BiTch ThAnkS ");
}

extern DWORD GetUnitIDByXY(LONG Wx, LONG Wy, Room2* pRoom2) {
	UnitAny* pUnit;
	if (!pRoom2)
		return 0;
	if (!pRoom2->pRoom1)
		return 0;
	if (!pRoom2->pRoom1->pUnitFirst)
		return 0;
	pUnit = pRoom2->pRoom1->pUnitFirst;
	if (!pUnit->pObjectPath)
		return 0;
	while (pUnit) {
		if (pUnit->dwType != UNIT_PLAYER)
			if (Wx == pUnit->pObjectPath->dwPosX)
				if (Wy == pUnit->pObjectPath->dwPosY)
					return pUnit->dwUnitId;
		pUnit = pUnit->pListNext;
	}
	return 0;
}

Level* GetLevelPointerD(ActMisc* pActMisc, int nLevel)
{
	if ((!pActMisc) || (nLevel < 0))
		return false;

	for (Level* pLevel = pActMisc->pLevelFirst; pLevel; pLevel = pLevel->pNextLevel)
	{
		if (!pLevel)
			continue;

		if ((pLevel->dwLevelNo == nLevel) && (pLevel->dwSizeX > 0))
			return pLevel;
	}
	return D2COMMON_GetLevel(pActMisc, nLevel);
}

void DrawPlayerBlob(int xpos, int ypos, int col) {
	static char blines[][2] = { 0,-2, 4,-4, 8,-2, 4,0, 8,2, 4,4, 0,2, -4,4, -8,2, -4,0, -8,-2, -4,-4, 0,-2 };
	for (int i = 0; i < ARRAYSIZE(blines) - 1; i++) {
		D2GFX_DrawLine(xpos + blines[i][0], ypos + blines[i][1], xpos + blines[i + 1][0], ypos + blines[i + 1][1], col, 0xff);
	}
	POINT Player = { D2CLIENT_GetPlayerUnit()->pPath->xPos, D2CLIENT_GetPlayerUnit()->pPath->yPos };
	MapToScreenCoords(Player);
	ScreenToAutomapRelative(&Player, Player.x, Player.y);
	D2GFX_DrawLine(Player.x, Player.y, xpos, ypos, col, 0xff);
}

#define QUESTCOLOR 155
#define OTHER	   152
#define	WP		   132

int wpIds[] = { 119, 157 };
int i;
void Enum()
{
	Room2* pRoom2;
	PresetUnit* pUnit;

	POINT wp;
	POINT me;

	if (!pRoom2) return;
	if (!pRoom2->pRoom1) return;
	if (!pRoom2->pRoom1->pUnitFirst) return;
	//pUnit=pRoom2->pRoom1->pUnitFirst;
	if (pUnit) {
		//	if(pUnit->dwType==UNIT_OBJECT) {
			//if(pUnit->dwUnitId==wpIds[i]) {
		wp.x = pUnit->dwPosX;
		wp.y = pUnit->dwPosY;
		me.x = D2CLIENT_GetPlayerUnit()->wX;
		me.y = D2CLIENT_GetPlayerUnit()->wY;
		POINT meCalc, wpCalc;
		MapToScreenCoords(meCalc);
		MapToScreenCoords(wpCalc);

		//					ScreenToAutomapRelative(&meCalc,me.x,me.y);
		//					ScreenToAutomapRelative(&wpCalc,wp.x,wp.y);

		//		D2DrawLine(meCalc.x,meCalc.y,wpCalc.x,wpCalc.y,11);
		//		DrawPlayerBlob(wpCalc.x,wpCalc.y,8);
		return;
		//	 }
		//}
		pUnit = pUnit->pPresetNext;
		return;
	}
}

#define DRAW(f,c) if(fileno==f) { DrawPlayerBlob(xpos,ypos,c);\
    if(c==QUESTCOLOR){GlobalVectors.QuestID=ObjID;GlobalVectors.QuestPos.x=rx;GlobalVectors.QuestPos.y=ry;}\
    if(c==OTHER){GlobalVectors.OtherID=ObjID;GlobalVectors.OtherPos.x=rx;GlobalVectors.OtherPos.y=ry;}\
    if(c==WP){GlobalVectors.WPID=ObjID;GlobalVectors.WPPos.x=rx;GlobalVectors.WPPos.y=ry;}}

void MiniMapCell(int xpos, int ypos, int actnum, int lvlnum, int fileno, long rx, long ry, DWORD ObjID) {
	struct BlobStruct {
		DWORD Act;
		DWORD Area;
		DWORD dwNumber;
		DWORD Color;
	};
	lvlnum = D2CLIENT_GetPlayerUnit()->pAct->pRoom1->pRoom2->pLevel->dwLevelNo;
	actnum = D2CLIENT_GetPlayerUnit()->dwAct + 1;

	if (actnum == 1) { // Act 1
		if (lvlnum == LEVEL_ROGUE_ENCAMPMENT)
			DRAW(148, QUESTCOLOR) // Akara
			DRAW(119, WP) // Town WP

			if (lvlnum == LEVEL_BLOOD_MOOR) {
				DRAW(3, QUESTCOLOR)
					DRAW(266, OTHER)
			}
		if (lvlnum == LEVEL_DEN_OF_EVIL)
			DRAW(4, OTHER)

			if (lvlnum == LEVEL_HOLE_LEVEL_1) {
				DRAW(5, OTHER)
			}

		if (lvlnum == LEVEL_COLD_PLAINS) {
			DRAW(119, WP)
				//	DRAW(2,OTHER) // MAYBE NOT§
		}
		if (lvlnum == LEVEL_TAMOE_HIGHLAND)
			DRAW(3, OTHER)

			if (lvlnum == LEVEL_BURIAL_GROUNDS)
				DRAW(805, QUESTCOLOR) //raven

				if (lvlnum == LEVEL_OUTER_CLOISTER)
					DRAW(24, QUESTCOLOR)

					if (lvlnum == LEVEL_BARRACKS)
						DRAW(108, OTHER)
						DRAW(14, QUESTCOLOR)

						if (lvlnum == LEVEL_JAIL_LEVEL_1)
							//		DRAW(14,QUESTCOLOR)

							if (lvlnum == LEVEL_JAIL_LEVEL_3)
								DRAW(13, OTHER)

								if (lvlnum == LEVEL_CATHEDRAL) {
									DRAW(15, OTHER)
										DRAW(119, WP)
								}

		if (lvlnum == LEVEL_CATACOMBS_LEVEL_1) {
			DRAW(18, QUESTCOLOR)
				//	DRAW(16,OTHER)
		}
		if (lvlnum == LEVEL_STONY_FIELD) {
			DRAW(1, OTHER)
				//	DRAW(737,QUESTCOLOR) //red wp
		}
		if (lvlnum == LEVEL_DARK_WOOD) {
			DRAW(30, QUESTCOLOR)
				DRAW(1, OTHER)
		}
		if (lvlnum == LEVEL_BLACK_MARSH) {
			DRAW(10, QUESTCOLOR)
				DRAW(119, WP)
				DRAW(3, OTHER)
		}
		if (lvlnum == LEVEL_FORGOTTEN_TOWER) {
			DRAW(12, QUESTCOLOR)
				DRAW(11, OTHER)
		}
		if (lvlnum == LEVEL_TOWER_CELLAR_LEVEL_1)
			DRAW(8, OTHER)
			DRAW(9, QUESTCOLOR)

			if (lvlnum == LEVEL_TOWER_CELLAR_LEVEL_2)
				DRAW(8, OTHER)
				DRAW(9, QUESTCOLOR)

				if (lvlnum == LEVEL_TOWER_CELLAR_LEVEL_3)
					DRAW(8, OTHER)
					DRAW(9, QUESTCOLOR)

					if (lvlnum == LEVEL_TOWER_CELLAR_LEVEL_4)
						DRAW(8, OTHER)
						DRAW(9, QUESTCOLOR)

						if (lvlnum == LEVEL_TOWER_CELLAR_LEVEL_5) {
							DRAW(8, OTHER)
								DRAW(580, QUESTCOLOR)
						}
		if (lvlnum == LEVEL_UNDERGROUND_PASSAGE_LEVEL_1)
			DRAW(4, OTHER)
			DRAW(4, QUESTCOLOR)

			//	if(lvlnum==LEVEL_TAMOE_HIGHLAND)
			if (lvlnum == LEVEL_MONASTERY_GATE)
				DRAW(24, OTHER)

				if (lvlnum == LEVEL_BLACK_MARSH)
					DRAW(10, QUESTCOLOR)

					if (lvlnum == LEVEL_TRISTRAM)
						DRAW(268, OTHER)
						DRAW(26, QUESTCOLOR)

						if (lvlnum == LEVEL_CATACOMBS_LEVEL_2 || lvlnum == LEVEL_CATACOMBS_LEVEL_3 || lvlnum == LEVEL_CATACOMBS_LEVEL_4)
							DRAW(17, OTHER)
							DRAW(18, QUESTCOLOR)
							DRAW(157, WP)

							if (lvlnum == LEVEL_CATACOMBS_LEVEL_4)
								DRAW(156, QUESTCOLOR)
	} // clsing Act1 vectors
	else if (actnum == 2) {
		DRAW(178, QUESTCOLOR)
			DRAW(156, WP)
			DRAW(323, WP)
			DRAW(288, WP)
			DRAW(402, WP)
			DRAW(298, WP)
			DRAW(357, QUESTCOLOR)
			if (lvlnum == LEVEL_DRY_HILLS)
				DRAW(33, QUESTCOLOR) // Halls of the dead
				DRAW(36, QUESTCOLOR) // Halls of the dead
				if (lvlnum == LEVEL_LOST_CITY)
					DRAW(74, OTHER) // Anc. Tunnels
					if (lvlnum == LEVEL_ANCIENT_TUNNELS)
						DRAW(22, OTHER) // Exit Anc. Tunnels
						DRAW(397, QUESTCOLOR) // Exit Anc. Tunnels
						if (lvlnum == LEVEL_HAREM_LEVEL_1)
							DRAW(29, QUESTCOLOR) // Level 2
							DRAW(25, OTHER) //Luth GOlain
							if (lvlnum == LEVEL_HAREM_LEVEL_2)
								DRAW(27, OTHER) //Back to Harem Level 1
								DRAW(29, QUESTCOLOR) // Down to Palace Cellar lvl 1
								if (lvlnum == LEVEL_PALACE_CELLAR_LEVEL_1)
									DRAW(27, OTHER) //Back to Harem Level 2
									DRAW(32, QUESTCOLOR) //Palace cellar lvl 2
									if (lvlnum == LEVEL_PALACE_CELLAR_LEVEL_2)
										DRAW(31, OTHER) //Back to Cellar lvl 1
										DRAW(32, OTHER) //Downt to cellar lvl 3
										if (lvlnum == LEVEL_PALACE_CELLAR_LEVEL_3)
											DRAW(31, OTHER) //Back to Cellar lvl 2
											if (lvlnum == LEVEL_HALLS_OF_THE_DEAD_LEVEL_1)
												DRAW(45, OTHER) // MAGGOT ENTRANCE
												DRAW(46, QUESTCOLOR)
												if (lvlnum == LEVEL_HALLS_OF_THE_DEAD_LEVEL_2)
													DRAW(45, OTHER) // MAGGOT ENTRANCE
													DRAW(46, QUESTCOLOR)
													if (lvlnum == LEVEL_HALLS_OF_THE_DEAD_LEVEL_3)
														DRAW(354, QUESTCOLOR)
														if (lvlnum == LEVEL_FAR_OASIS)
															DRAW(47, QUESTCOLOR) // MAGGOT ENTRANCE
															if (lvlnum == LEVEL_MAGGOT_LAIR_LEVEL_1)
																DRAW(48, OTHER) // MAGGOT ENTRANCE
																DRAW(49, QUESTCOLOR) // MAGGOT lvl 2
																if (lvlnum == LEVEL_MAGGOT_LAIR_LEVEL_2)
																	DRAW(48, OTHER) // MAGGOT LVL 1
																	DRAW(49, QUESTCOLOR) // MAGGOT lvl 3
																	if (lvlnum == LEVEL_MAGGOT_LAIR_LEVEL_3)
																		DRAW(48, OTHER) // MAGGOT LVL 2
																		DRAW(356, QUESTCOLOR) // cHEST
																		if (lvlnum == LEVEL_SEWERS_LEVEL_1)
																			DRAW(22, OTHER) // lvl 1
																			DRAW(23, QUESTCOLOR) // lvl 2
																			if (lvlnum == LEVEL_SEWERS_LEVEL_2)
																				DRAW(22, OTHER) // lvl 1
																				if (lvlnum == LEVEL_SEWERS_LEVEL_3)
																					DRAW(22, OTHER)
																					DRAW(356, QUESTCOLOR)
																					DRAW(355, QUESTCOLOR)
																					if (lvlnum == LEVEL_ROCKY_WASTE)
																						DRAW(34, OTHER)
																						if (lvlnum == LEVEL_VALLEY_OF_SNAKES)
																							DRAW(37, QUESTCOLOR) // lvl 1
																							if (lvlnum == LEVEL_CLAW_VIPER_TEMPLE_LEVEL_1)
																								DRAW(46, QUESTCOLOR) // lvl 1
																								if (lvlnum == LEVEL_CLAW_VIPER_TEMPLE_LEVEL_2)
																									DRAW(149, QUESTCOLOR) // lvl 1
																									if (lvlnum == LEVEL_TAL_RASHAS_TOMB1 || lvlnum == LEVEL_TAL_RASHAS_TOMB2 || LEVEL_TAL_RASHAS_TOMB3 || LEVEL_TAL_RASHAS_TOMB4 || LEVEL_TAL_RASHAS_TOMB5 || LEVEL_TAL_RASHAS_TOMB6 || LEVEL_TAL_RASHAS_TOMB7)
																										DRAW(152, QUESTCOLOR) // orifice
																										DRAW(45, OTHER)
																										if (lvlnum == LEVEL_DURIELS_LAIR)
																											DRAW(251, QUESTCOLOR) // lvl 1
	} //clsing Act2 Vectors
	else if (actnum == 3) {
		DRAW(237, WP)
			DRAW(324, WP)
			DRAW(237, WP)
			DRAW(255, QUESTCOLOR) //Ormus
			if (lvlnum == LEVEL_SPIDER_FOREST)
				DRAW(51, OTHER)
				if (lvlnum == LEVEL_KURAST_BAZAAR)
					DRAW(195, QUESTCOLOR)
					if (lvlnum == LEVEL_RUINED_TEMPLE)
						DRAW(193, QUESTCOLOR)
						if (lvlnum == LEVEL_TRAVINCAL)
							DRAW(64, QUESTCOLOR) // entrance to durance
							if (lvlnum == LEVEL_DURANCE_OF_HATE_LEVEL_1)
								DRAW(66, OTHER)
								DRAW(65, OTHER)
								DRAW(66, OTHER)
								DRAW(67, QUESTCOLOR)
								DRAW(68, QUESTCOLOR)
								if (lvlnum == LEVEL_DURANCE_OF_HATE_LEVEL_2)
									DRAW(65, OTHER)
									DRAW(66, OTHER)
									DRAW(67, QUESTCOLOR)
									DRAW(68, QUESTCOLOR)
									if (lvlnum == LEVEL_DURANCE_OF_HATE_LEVEL_3)
										DRAW(66, OTHER)
										DRAW(242, QUESTCOLOR)
										DRAW(342, WP)
	} // closing Act3
	else if (actnum == 4) {
		DRAW(405, QUESTCOLOR)
			DRAW(398, WP)
			DRAW(238, WP)
			if (lvlnum == LEVEL_PLAINS_OF_DESPAIR)
				DRAW(256, QUESTCOLOR)
				if (lvlnum == LEVEL_RIVER_OF_FLAME)
					DRAW(376, QUESTCOLOR)
					//	DRAW(70,OTHER)
					if (lvlnum == LEVEL_CHAOS_SANCTUM)
						DRAW(255, QUESTCOLOR) // DIABLO
						if (lvlnum == LEVEL_CITY_OF_THE_DAMNED)
							DRAW(69, QUESTCOLOR) // DIABLO
	} // closing Act4
	else {
		DRAW(255, QUESTCOLOR)
			DRAW(429, WP)
			DRAW(496, WP)
			DRAW(494, WP)
			DRAW(511, WP) // Glacial Trail
			DRAW(513, QUESTCOLOR)
			DRAW(563, QUESTCOLOR)
			DRAW(81, OTHER) // Go out!
			DRAW(82, QUESTCOLOR) // Way to throne
			if (lvlnum == LEVEL_BLOODY_FOOTHILLS)
				DRAW(776, QUESTCOLOR)// way to Shenk
				if (lvlnum == LEVEL_RIGID_HIGHLANDS)
					//	DRAW(434,QUESTCOLOR)
					//	DRAW(473,OTHER)
					if (lvlnum == LEVEL_ARREAT_PLATEAU) {
						DRAW(71, QUESTCOLOR)
					}
		if (lvlnum == LEVEL_TUNDRA_WASTELANDS)
			DRAW(71, QUESTCOLOR)
			if (lvlnum == LEVEL_ROCKY_SUMMIT)
				DRAW(546, QUESTCOLOR)
				DRAW(547, WP)
				DRAW(564, OTHER)
				if (lvlnum == LEVEL_HALLS_OF_DEATHS_CALLING)
					DRAW(77, QUESTCOLOR)// way to Nila
					if (lvlnum == LEVEL_HALLS_OF_VAUGHT)
						DRAW(462, QUESTCOLOR)// WHere nila sits.
						if (lvlnum == LEVEL_CRYSTALIZED_CAVERN_LEVEL_1) // CRYSTALINE PASSAGE
						//	DRAW(73,QUESTCOLOR)// Way to frozen river from crystaline passage
							DRAW(75, QUESTCOLOR)// Way to frozen river from crystaline passage
							DRAW(74, OTHER)// Way to Glacial Trail.
							if (lvlnum == LEVEL_CELLAR_OF_PITY)
								DRAW(460, QUESTCOLOR)// Pathing to Anya.
								DRAW(73, OTHER)
								if (lvlnum == LEVEL_THE_WORLDSTONE_CHAMBER)
									DRAW(544, QUESTCOLOR)// Pathing to Baal.
	} // Closing Act5
	 // Always draw the below
	DRAW(267, OTHER) // Stash
}

void NewEnum()
{
	UnitAny* pUnit = D2CLIENT_GetPlayerUnit();
	Level* pLevel = GetLevelPointerD(pUnit->pAct->pMisc, GetPlayerArea());
	for (Room2* pRoom2 = pLevel->pRoom2First; pRoom2; pRoom2 = (Room2*)pRoom2->pRoom2Next) {
		for (PresetUnit* unit = pRoom2->pPreset; unit; unit = unit->pPresetNext) {
			BOOL add_room = FALSE;
			if (!pRoom2->pRoom1)
			{
				add_room = TRUE;
				D2COMMON_AddRoomData(D2CLIENT_GetPlayerUnit()->pAct, pRoom2->pLevel->dwLevelNo, pRoom2->dwPosX, pRoom2->dwPosY, D2CLIENT_GetPlayerUnit()->pPath->pRoom1);
			}
			PresetUnit pu;
			POINT Calc;
			pu.dwTxtFileNo = unit->dwTxtFileNo;
			pu.dwType = unit->dwType;
			pu.dwPosX = unit->dwPosX + pRoom2->dwPosX * 5;
			pu.dwPosY = unit->dwPosY + pRoom2->dwPosY * 5;
			Calc.x = pu.dwPosX;
			Calc.y = pu.dwPosY;
			DWORD UnitID = GetUnitIDByXY(pu.dwPosX, pu.dwPosY, pRoom2);
			POINT DrawCalc;
			if (D2CLIENT_GetUiVar(0x19)) {
				return;
			}
			MapToScreenCoords(Calc);
			ScreenToAutomapRelative(&DrawCalc, Calc.x, Calc.y);
			MiniMapCell(DrawCalc.x, DrawCalc.y, D2CLIENT_GetPlayerUnit()->dwAct + 1, GetPlayerArea(), pu.dwTxtFileNo, pu.dwPosX, pu.dwPosY, UnitID);
			if (Units) {
				DrawTextToScreen(mitoa(unit->dwTxtFileNo), Calc.x, Calc.y, 1, 4); // Prints Type
				DrawTextToScreen(mitoa(unit->dwType), Calc.x, Calc.y + 10, 2, 4);; // PrintsUnitTypes

				AutomapToScreenRelative(&DrawCalc, Calc.x, Calc.y);
				//MiniMapCell(DrawCalc.x, DrawCalc.y, D2CLIENT_GetPlayerUnit()->dwAct + 1, GetPlayerArea(), pu.dwTxtFileNo, pu.dwPosX, pu.dwPosY, UnitID);
			}
		}
	}
}

extern int Players() {
	int i;
	RosterUnit* pUnit = *p_D2CLIENT_PlayerUnitList;
	for (i = 0; pUnit != NULL; i++)
		pUnit = pUnit->pNext;
	return i;
}

void DrawPos(void)
{
	char MyPos[100];
	sprintf(MyPos, "%d:%d", GetPosition().x, GetPosition().y);
	DrawTextToScreen(MyPos, 115, 550, 1, 4);
}

void DrawPlines(void)
{
	/*if (!D2CLIENT_GetUiVar(2)) {
		if (!D2CLIENT_GetUiVar(1)) {
			if (!D2CLIENT_GetUiVar(0x18)) {
				POINT Player;
				POINT Target;
				if (Auto.GetPlayerID() != GetPlayerID())
					if (FindUnit(Auto.GetPlayerID(), 0))
						if (((UnitAny*)FindUnit(Auto.GetPlayerID(), 0))->pPath) {
							UnitAny* NearstPlayer = (UnitAny*)FindUnit(Auto.GetPlayerID(), 0);
							if (NearstPlayer->pPlayerData) {
								if (!CheckPlayerFriend(NearstPlayer->pPlayerData->szName)) {
									Player.x = GetPlayerX(GetPlayerID());
									Player.y = GetPlayerY(GetPlayerID());
									Target.x = NearstPlayer->pPath->xPos;
									Target.y = NearstPlayer->pPath->yPos;
									POINT DrawCalc, TargetCalc;
									MapToScreenCoords(Player);
									ScreenToAutomapRelative(&DrawCalc, Player.x, Player.y);
									MapToScreenCoords(Target);
									ScreenToAutomapRelative(&TargetCalc, Target.x, Target.y);
									D2DrawLine(DrawCalc.x, DrawCalc.y, TargetCalc.x, TargetCalc.y, 11);
									//DrawPlayerBlob(TargetCalc.x,TargetCalc.y,8);
								}
								if (Units) {
									POINT DrawCalc, TargetCalc;
									Player.x = NearstPlayer->pPath->xPos;
									Player.y = NearstPlayer->pPath->yPos;
									Target.x = NearstPlayer->pPath->xTarget;
									Target.y = NearstPlayer->pPath->yTarget;

									MapToScreenCoords(Player);
									ScreenToAutomapRelative(&DrawCalc, Player.x, Player.y);
									MapToScreenCoords(Target);
									ScreenToAutomapRelative(&TargetCalc, Target.x, Target.y);
									D2DrawLine(DrawCalc.x, DrawCalc.y, TargetCalc.x, TargetCalc.y, 222);
								}
							}
						}
			}
		}
	}*/
}

void  AbsToScreenCoords(POINT& rMapPosition)
{
	D2COMMON_AbsScreenToMap(&rMapPosition.x, &rMapPosition.y);
	rMapPosition.x -= D2CLIENT_GetMouseXOffset();
	rMapPosition.y -= D2CLIENT_GetMouseYOffset();
}

//void TestDraw(void)
//{
//	if (Units) {
//		//MapToScreenCoords(Target);
//	//	ScreenToAutomapRelative(&TargetCalc,Target.x,Target.y);
//	//	D2DrawLine(DrawCalc.x,DrawCalc.y,TargetCalc.x,TargetCalc.y,11);
//	//			DrawTextToScreen("OKIII",800/2-strlen("OK")*8,700/2,3,2);
////					char Buffer[200];
////					sprintf(Buffer,"Player: %d:%d / %d:%d",Player.x,Player.y,GetPlayerX(GetPlayerID()),GetPlayerY(GetPlayerID()));
//	//	DrawTextToScreen(Buffer,115,400,2,4);
////		sprintf(Buffer,"Target: %d:%d",Target.x,Target.y);
//	//	DrawTextToScreen(Buffer,115,420,2,4);
//
//		char MyPos[100];
//		sprintf(MyPos, "%d:%d", D2CLIENT_MouseX, D2CLIENT_MouseY);
//		DrawTextToScreen(MyPos, 115, 540, 2, 4);
//
//		if (D2CLIENT_AutomapOn) {
//			POINT Player;
//			POINT Player2;
//			POINT Target;
//			Player.x = GetPlayerX(GetPlayerID());
//			Player.y = GetPlayerY(GetPlayerID());
//
//			Player2.x = D2CLIENT_GetPlayerUnit()->pPath->xOffset;
//			Player2.y = D2CLIENT_GetPlayerUnit()->pPath->yOffset;
//
//			Target.x = D2CLIENT_GetPlayerUnit()->pPath->xTarget;
//			Target.y = D2CLIENT_GetPlayerUnit()->pPath->yTarget;
//
//			ScreenToAutomapRelative(&Target, Target.x, Target.y);
//			D2DrawLine(Player.x, Player.y, Target.x, Target.y, 11);
//
//			//	DrawPlayerBlob(TargetCalc.x,TargetCalc.y,0x62);
//			//	D2DrawLine(DrawCalc.x,DrawCalc.y,TargetCalc.x,TargetCalc.y,11);
//
//			char MyPos[100];
//			sprintf(MyPos, "Target: %d:%d", Target.x, Target.y);
//			DrawTextToScreen(MyPos, 115, 450, 1, 4);
//			sprintf(MyPos, "Position: %d:%d", Player.x, Player.y);
//			DrawTextToScreen(MyPos, 115, 470, 2, 4);
//			sprintf(MyPos, "Mouse: %d:%d", D2CLIENT_MouseX, D2CLIENT_MouseY);
//			DrawTextToScreen(MyPos, 115, 490, 2, 4);
//		}
//	}
//}

//void DrawYonTarget(void)
//{
//	if (v_AimBox)
//		if (!D2CLIENT_GetUiVar(0x1a)) {
//			if (!D2CLIENT_GetUiVar(0x19)) {
//				if (!D2CLIENT_GetUiVar(2)) {
//					if (!D2CLIENT_GetUiVar(1)) {
//						if (!D2CLIENT_GetUiVar(0x18)) {
//							if (Auto.GetPlayerID() != GetPlayerID() || Auto.GetPlayerID() != NULL) {
//								// Drawing [Y] on him
//								if (FindUnit(Auto.GetPlayerID(), 0)) {
//									POINT PlayerPos;
//									UnitAny* TargetUnit = (UnitAny*)FindUnit(Auto.GetPlayerID(), 0);
//									RosterUnit* pUnit = (RosterUnit*)*(DWORD*)0x6FBCC080;
//									pUnit = pUnit->pNext;
//									if (TargetUnit->dwUnitId != GetPlayerID()) {
//										PlayerPos.x = TargetUnit->pPath->xPos;
//										PlayerPos.y = TargetUnit->pPath->yPos;
//										MapToScreenCoords(PlayerPos);
//
//										if (PlayerPos.x != NULL && PlayerPos.y != NULL && CheckPlayerFriend(Auto.GetPlayerNAME())) {
//											D2GFX_DrawRectangle(PlayerPos.x - 30, PlayerPos.y - 55, PlayerPos.x + 20, PlayerPos.y + 35, 132, 0);
//											D2DrawRectFrame(PlayerPos.x - 30, PlayerPos.y - 55, PlayerPos.x + 20, PlayerPos.y + 35);
//
//											DrawTextToScreen(mitoa(GetUnitStat(TargetUnit, STAT_COLDABSORBPERCENT)), PlayerPos.x - 26, PlayerPos.y + 45, 3, 4);
//											DrawTextToScreen(mitoa(GetUnitStat(TargetUnit, STAT_FIREABSORBPERCENT)), PlayerPos.x - 8, PlayerPos.y + 45, 1, 4);
//											DrawTextToScreen(mitoa(GetUnitStat(TargetUnit, STAT_LIGHTNINGABSORBPERCENT)), PlayerPos.x + 10, PlayerPos.y + 45, 9, 4);
//
//											//D2GFX_DrawRectangle(PlayerPos.x-28,PlayerPos.y-60,PlayerPos.x+25,PlayerPos.y+40,132,0);
//											//D2DrawRectFrame(PlayerPos.x-28,PlayerPos.y-60,PlayerPos.x+25,PlayerPos.y+40);
//										}
//										else {
//											if (PlayerPos.x != NULL && PlayerPos.y != NULL) {
//												D2GFX_DrawRectangle(PlayerPos.x - 30, PlayerPos.y - 55, PlayerPos.x + 20, PlayerPos.y + 35, v_AimBoxColor, 0);
//												D2DrawRectFrame(PlayerPos.x - 30, PlayerPos.y - 55, PlayerPos.x + 20, PlayerPos.y + 35);
//
//												DrawTextToScreen(mitoa(GetUnitStat(TargetUnit, STAT_COLDABSORBPERCENT)), PlayerPos.x - 26, PlayerPos.y + 45, 3, 4);
//												DrawTextToScreen(mitoa(GetUnitStat(TargetUnit, STAT_FIREABSORBPERCENT)), PlayerPos.x - 8, PlayerPos.y + 45, 1, 4);
//												DrawTextToScreen(mitoa(GetUnitStat(TargetUnit, STAT_LIGHTNINGABSORBPERCENT)), PlayerPos.x + 10, PlayerPos.y + 45, 9, 4);
//											}
//											//if(Units) {
//							  /*  DrawTextToScreen(mitoa(GetUnitStat(TargetUnit, STAT_COLDABSORBPERCENT)),PlayerPos.x-25,PlayerPos.y-55,3,4);
//								DrawTextToScreen(mitoa(GetUnitStat(TargetUnit, STAT_FIREABSORBPERCENT)),PlayerPos.x-10,PlayerPos.y-55,1,4);
//								DrawTextToScreen(mitoa(GetUnitStat(TargetUnit, STAT_LIGHTNINGABSORBPERCENT)),PlayerPos.x+5,PlayerPos.y-55,9,4);*/
//								//	}
//										}
//									}
//								}
//							}
//						}
//					}
//				}
//			}
//		}
//}
//Test to draw Absorbs above target
//void DrawAbsAboveTarget(void)
//{
//	POINT Player;
//	POINT Target;
//	if (Auto.GetPlayerID() != GetPlayerID())
//		if (FindUnit(Auto.GetPlayerID(), 0))
//			if (((UnitAny*)FindUnit(Auto.GetPlayerID(), 0))->pPath) {
//				UnitAny* NearstPlayer = (UnitAny*)FindUnit(Auto.GetPlayerID(), 0);
//				if (NearstPlayer->pPlayerData) {
//					Player.x = GetPlayerX(GetPlayerID());
//					Player.y = GetPlayerY(GetPlayerID());
//					Target.x = NearstPlayer->pPath->xPos;
//					Target.y = NearstPlayer->pPath->yPos;
//					POINT DrawCalc, TargetCalc;
//					MapToScreenCoords(Player);
//					ScreenToAutomapRelative(&DrawCalc, Player.x, Player.y);
//					MapToScreenCoords(Target);
//					ScreenToAutomapRelative(&TargetCalc, Target.x, Target.y);
//					DrawTextToScreen(mitoa(GetUnitStat(NearstPlayer, STAT_COLDABSORBPERCENT)), Target.x - 30, Target.y - 55, 3, 6);
//				}
//			}
//}

/// test to draw absorbs above target

void Screenhooks(void) {
	if (!D2CLIENT_GetUiVar(0x01)) {
		//if(!D2CLIENT_GetUiVar(0x18))  {
		UnitAny* pUnit = D2CLIENT_GetPlayerUnit();
		char Buffer[100];
		/*DWORD	MaxLife = GetMaxLife();
		DWORD	MaxMana = GetMaxMana();*/
		/*DWORD	CurrentLife = GetCurrentLife();
		DWORD	CurrentMana = GetCurrentMana();*/
		/*DWORD	LifePercent = GetPercent(CurrentLife, MaxLife);
		DWORD	ManaPercent = GetPercent(CurrentMana, MaxMana);*/

		D2GFX_DrawRectangle(50, 532, 91, 549, 0, 100);
		D2DrawRectFrame(50, 532, 91, 549);

		D2GFX_DrawRectangle(715, 532, 756, 549, 0, 100);
		D2DrawRectFrame(715, 532, 755, 549);

		int nLifePercent = std::abs((float)((double)(D2COMMON_GetUnitStat(pUnit, 6, 0) >> 8) / (double)(D2COMMON_GetUnitStat(pUnit, 7, 0) >> 8)) * 100);
		int nManaPercent = std::abs((float)((double)(D2COMMON_GetUnitStat(pUnit, 8, 0) >> 8) / (double)(D2COMMON_GetUnitStat(pUnit, 9, 0) >> 8)) * 100);

		sprintf(Buffer, "%i% %", nLifePercent);
		DrawTextToScreen(Buffer, 56, 547, 1, 0);
		sprintf(Buffer, "%i% %", nManaPercent);
		DrawTextToScreen(Buffer, 722, 547, 3, 0);
	}
}

void RevealActOnce(void)
{
	if (GetPlayerArea() != LastLvl)
	{
		UnitAny* pUnit = D2CLIENT_GetPlayerUnit();
		Level* pLevel = GetLevelPointerD(pUnit->pAct->pMisc, GetPlayerArea());
		RevealLevel(pLevel);
		LastLvl = GetPlayerArea();
		GlobalVectors.OtherPos.x = 0;
		GlobalVectors.OtherPos.y = 0;
		GlobalVectors.QuestPos.x = 0;
		GlobalVectors.QuestPos.y = 0;
		GlobalVectors.WPPos.x = 0;
		GlobalVectors.WPPos.y = 0;
	}
}

void AutoTeleDraw(void)
{
	if (AutoTele) {
		DrawTextToScreen("AutoTele is active!", 800 / 2 - strlen("AutoTele is active!") * 8, 700 / 2, 3, 2);
		if (D2CLIENT_AutomapOn) {
			POINT LastPos = { 0,0 };
			for (int i = 0; aPath[i].x != NULL; i++) {
				POINT DrawCalc;
				POINT Calc = { aPath[i].x,aPath[i].y };
				MapToScreenCoords(Calc);
				ScreenToAutomapRelative(&DrawCalc, Calc.x, Calc.y);
				DrawBlob(DrawCalc.x, DrawCalc.y, 0x62);
				if (LastPos.x && LastPos.y)
					D2GFX_DrawLine(LastPos.x, LastPos.y, DrawCalc.x, DrawCalc.y, 0x62, 0xff);
				LastPos.x = DrawCalc.x;
				LastPos.y = DrawCalc.y;
			}
		}
	}
}

void DrawUIVars(void)
{
	UnitAny* pUnit = D2CLIENT_GetPlayerUnit();
	if (D2CLIENT_GetUiVar(2)) {
		/*   if  (D2COMMON_GetQuestFlag(D2CLIENT_GetQuestInfo(), 4, 10))
			 TextHook(100, 390, 0, false, 0, -1, "ÿc1*ÿc0King Killedÿc1*");*/
		char Buffer[200];
		// Fire 180 base
		int fire = D2COMMON_GetUnitStat((UnitAny*)pUnit, 39, 0);
		sprintf(Buffer, "%d", fire);
		DrawTextToScreen(Buffer, 402, 410, 1, 1);
		// Cold
		int cold = D2COMMON_GetUnitStat((UnitAny*)pUnit, 43, 0);
		sprintf(Buffer, "%d", cold);
		DrawTextToScreen(Buffer, 402, 432, 3, 1);
		//Light
		int light = D2COMMON_GetUnitStat((UnitAny*)pUnit, 41, 0);
		sprintf(Buffer, "%d", light);
		DrawTextToScreen(Buffer, 402, 456, 9, 1);
		// Psn
		int psn = D2COMMON_GetUnitStat((UnitAny*)pUnit, 45, 0);
		sprintf(Buffer, "%d", psn);
		DrawTextToScreen(Buffer, 402, 480, 2, 1);

		//     D2GFX_DrawRectangle(88,390,200,490,0,1);
		//     D2DrawRectFrame(88,390,200,490);

			 //D2GFX_DrawRectangle(715,532,756,549,0,100);
			 //D2DrawRectFrame(715,532,755,549);
	}
}

//void DrawPlayerInventoryHook(void)
//{
//	// Player View Hook things =D
//	if (DrawPlayerInventory) {
//		UnitAny* PlayerUnit = (UnitAny*)FindUnit(Auto.GetPlayerID(), 0);
//
//		int xPlayer = 530;
//		int yPlayer = 311;
//		if (!PlayerUnit || PlayerUnit->pPath && GetDistanceSquared(PlayerX(), PlayerY(), PlayerUnit->pPath->xPos, PlayerUnit->pPath->yPos) > 2000) {
//			DrawPlayerInventory = false;
//			ToggleInventory(false);
//			UninstallPatches();
//		}
//		else {
//			if (IsInventoryOpen() == false) {
//				UninstallPatches();
//				DrawPlayerInventory = false;
//			}
//			DrawTextToScreen(Auto.GetPlayerNAME(), xPlayer, yPlayer, 4, 0);
//		}
//	}
//	/*if (ToggleInfo && TargetInfo && FindUnit(Auto.GetPlayerID(), UNIT_PLAYER))
//		DrawStatBox(Auto.GetPlayerID());
//	else if (ToggleInfo) DrawStatBox(GetPlayerID());*/
//}

void DrawWelcomeText(void)
{
	if (PKInfo.Ready)
		if (TimeOn <= 1000) {
			char Buffer[2048] = { 0 };
			sprintf(Buffer, "Welcome %s to EuroTPPK", PKInfo.ForumName);
			DrawTextToScreen(Buffer, 800 / 2 - 110, 500 / 20, FONTCOLOR_WHITE, 1);
			sprintf(Buffer, "Kills %d Score %d Rank %d", PKInfo.TotalKills, PKInfo.TotalScore, PKInfo.Rank);
			DrawTextToScreen(Buffer, 800 / 2 - 90, 800 / 20, FONTCOLOR_WHITE, 1);
		}
	if (TimeOn1 <= 1000) {
		Killed = true;
		char Buffer[1024] = { 0 };
		sprintf(Buffer, "Kills %d Score %d Rank %d", PKInfo.TotalKills, PKInfo.TotalScore, PKInfo.Rank);
		DrawTextToScreen(Buffer, 800 / 2 - 90, 800 / 20, FONTCOLOR_WHITE, 1);
	}

	else PKInfo.Ready = false;
	TimeOn++;
	TimeOn1++;
	Killed = false;
}

//

bool CONFBOX;
bool TARGETS;
DWORD Count = 0;
void ResetCount() { Count = 0; }
bool Precasts = false;
bool OneClick = false;
bool LevelBox = false;
int ClickTimer;
bool ConfigPlayerInfo = false;

void Boxes(void) {
	//Targets
	int x1 = 170;
	int y1 = 531;
	int x2 = 219;
	int y2 = 549;
	// Configs
	int a1 = 225;
	int b1 = 531;
	int a2 = 267;
	int b2 = 549;
	// Precasts
	int c1 = 273;
	int d1 = 531;
	int c2 = 324;
	int d2 = 549;
	// Experience Levels
	int e1 = 330;
	int f1 = 531;
	int e2 = 362;
	int f2 = 549;
	// Winamp Box
	int g1 = 368;
	int h1 = 531;
	int g2 = 415;
	int h2 = 549;
	// Console
	int i1 = 421;
	int j1 = 531;
	int i2 = 470;
	int j2 = 549;

	// CONFIGS
	if (!ConfigPlayerInfo) {
		D2GFX_DrawRectangle(a1, b1, a2, b2, 0, 100);
		D2DrawRectFrame(a1, b1, a2, b2);
		DrawTextToScreen("Config", a1 + 3, b2 - 2, FONTCOLOR_WHITE, 6);
	}

	// TARGETS
	if (!TargetList) {
		D2GFX_DrawRectangle(x1, y1, x2, y2, 0, 100);
		D2DrawRectFrame(x1, y1, x2, y2);
		DrawTextToScreen("Targets", x1 + 3, y2 - 2, FONTCOLOR_WHITE, 6);
	}

	// PRECASTS
	if (!Precasts) {
		D2GFX_DrawRectangle(c1, d1, c2, d2, 0, 100);
		D2DrawRectFrame(c1, d1, c2, d2);
		DrawTextToScreen("Precasts", c1 + 3, d2 - 2, FONTCOLOR_WHITE, 6);
	}

	// Level
	if (!LevelBox) {
		D2GFX_DrawRectangle(e1, f1, e2, f2, 0, 100);
		D2DrawRectFrame(e1, f1, e2, f2);
		DrawTextToScreen("Level", e1 + 3, f2 - 2, FONTCOLOR_WHITE, 6);
	}

	// Winamp
	if (!v_DrawSongTitle) {
		D2GFX_DrawRectangle(g1, h1, g2, h2, 0, 100);
		D2DrawRectFrame(g1, h1, g2, h2);
		DrawTextToScreen("Winamp", g1 + 3, h2 - 2, FONTCOLOR_WHITE, 6);
	}

	// Console
	if (!v_ConsoleLogs) {
		D2GFX_DrawRectangle(i1, j1, i2, j2, 0, 100);
		D2DrawRectFrame(i1, j1, i2, j2);
		DrawTextToScreen("Console", i1 + 3, j2 - 2, FONTCOLOR_WHITE, 6);
	}

	// CONFIGS
	int col = 0;
	if (!ConfigPlayerInfo) {
		if (D2CLIENT_MouseX >= a1 && D2CLIENT_MouseX <= a2) {
			if (D2CLIENT_MouseY >= b1 && D2CLIENT_MouseY <= b2) {
				if (KEYDOWN(vK_BoxKey)) {
					ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
					if (KEYDOWN(MK_LBUTTON)) {
						ConfigPlayerInfo = true;
						return;
					}
				}
			}
		}
	}

	// TARGETS
	if (!TargetList) {
		if (D2CLIENT_MouseX >= x1 && D2CLIENT_MouseX <= x2) {
			if (D2CLIENT_MouseY >= y1 && D2CLIENT_MouseY <= y2) {
				if (KEYDOWN(vK_BoxKey)) {
					ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
					if (KEYDOWN(MK_LBUTTON)) {
						TargetList = true;
						currentTarget = true;
						return;
					}
				}
			}
		}
	}

	// Precasts
	if (!Precasts) {
		if (D2CLIENT_MouseX >= c1 && D2CLIENT_MouseX <= c2) {
			if (D2CLIENT_MouseY >= d1 && D2CLIENT_MouseY <= d2) {
				if (KEYDOWN(vK_BoxKey)) {
					ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
					if (KEYDOWN(MK_LBUTTON)) {
						Precasts = true;
						return;
					}
				}
			}
		}
	}

	// EXP
	if (!LevelBox) {
		if (D2CLIENT_MouseX >= e1 && D2CLIENT_MouseX <= e2) {
			if (D2CLIENT_MouseY >= f1 && D2CLIENT_MouseY <= f2) {
				if (KEYDOWN(vK_BoxKey)) {
					ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
					if (KEYDOWN(MK_LBUTTON)) {
						LevelBox = true;
						return;
					}
				}
			}
		}
	}
	// Winamp
	if (!v_DrawSongTitle) {
		if (D2CLIENT_MouseX >= g1 && D2CLIENT_MouseX <= g2) {
			if (D2CLIENT_MouseY >= h1 && D2CLIENT_MouseY <= h2) {
				if (KEYDOWN(vK_BoxKey)) {
					ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
					if (KEYDOWN(MK_LBUTTON)) {
						v_DrawSongTitle = true;
						return;
					}
				}
			}
		}
	}
	// Console
	if (!v_ConsoleLogs) {
		if (D2CLIENT_MouseX >= i1 && D2CLIENT_MouseX <= i2) {
			if (D2CLIENT_MouseY >= j1 && D2CLIENT_MouseY <= j2) {
				if (KEYDOWN(vK_BoxKey)) {
					ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
					if (KEYDOWN(MK_LBUTTON)) {
						v_ConsoleLogs = true;
						return;
					}
				}
			}
		}
	}
}

void DT(void) {
	char Buffer[200];
	if (Killed)
		if (TimeOn1 < 1000) {
			if (v_AutoScreenShot)
				D2WIN_TakeScreenshot();
			PrintMessage("Screen Captured", 8);
			Killed = false;
			return;
		}
	/*UnitAny* pUnit = D2CLIENT_GetPlayerUnit();
	sprintf(Buffer, "FrameRate: %d", pUnit->wFrameRate);
	DrawTextToScreen(Buffer, 300, 100, 2, 0);
	sprintf(Buffer, "FrameRemain: %d", pUnit->dwFrameRemain);
	DrawTextToScreen(Buffer, 300, 110, 1, 0);*/

	if (D2CLIENT_GetUiVar(0x01))
	{
		D2GFX_DrawRectangle(530, 275, 595, 295, 0, 80);
		D2DrawRectFrame(530, 275, 595, 295);
		DrawTextToScreen("EuroTPPK", 533, 293, 4, 0);
	}
	while (D2CLIENT_GetUiVar(0x09))  // MainMenu
	{
		ClipCursor(0);
		return;
	}
}

void DrawAutomapInfos(void)
{
	DrawMonsters();	// Draws monsters on Automap
	DrawAutomapText(); // Draws Levelnames and Tomb
	//TestDraw();			// TEST
	NewEnum();
	DrawOriginal();
	//DrawPlines();		 // Draws Targeted playerline
	//DrawYonTarget();
	DrawUIVars();
}

void GameDraw()
{
	if (!D2CLIENT_GetUiVar(0x18)) {
		ConfBoxx();
		ExpBox();
		PreCastsBox();
		TargetInfoBoxxx();
		MovableTargets();
		WinAmpBox();
	}
	DrawMessageConsole();
	DrawConsole();

	//RevealActOnce();
	/*TestDraw();*/
	DT();
	Screenhooks();
	Boxes();
	//DrawPlayerInventoryHook();

	DrawWelcomeText();
	WelcomeBox();

	//if (D2CLIENT_AutomapOn) // The Automap is tabbed ON
	//	AutoTeleDraw();		 // Draw while auto teleporting
}

VOID ScreenToAutomap(POINT* ptPos, int x, int y)
{
	ptPos->x = ((x - y) / 2 / (*(INT*)p_D2CLIENT_Divisor)) - (*p_D2CLIENT_Offset).x + 8;
	ptPos->y = ((x + y) / 4 / (*(INT*)p_D2CLIENT_Divisor)) - (*p_D2CLIENT_Offset).y - 8;
	if (D2CLIENT_GetAutomapSize())
	{
		--ptPos->x;
		ptPos->y += 5;
	}
}
VOID DrawCross(INT nX, INT nY, DWORD dwColor, BOOL Automap)
{
	POINT nPos = { nX, nY };
	if (Automap)
	{
		if (!p_D2CLIENT_AutomapOn)
			return;
		ScreenToAutomap(&nPos, nX * 32, nY * 32);
	}

	CHAR szLines[][2] = { 0,-2, 4,-4, 8,-2, 4,0, 8,2, 4,4, 0,2, -4,4, -8,2, -4,0, -8,-2, -4,-4, 0,-2 };
	for (INT x = 0; x < ArraySize(szLines) - 1; x++)
		D2GFX_DrawLine(nPos.x + szLines[x][0], nPos.y + szLines[x][1], nPos.x + szLines[x + 1][0], nPos.y + szLines[x + 1][1], dwColor, -1);
}

void TextHook(INT xPos, INT yPos, DWORD dwColor, BOOL Automap, INT dwFont, INT dwCenter, LPSTR Text, ...)
{
	//Setup a point variable
	POINT nPos = { xPos, yPos };
	DWORD dwOldSize, wWidth, dwFileNo;

	//Check if we are drawing this on Automap
	if (Automap)
	{
		if (!p_D2CLIENT_AutomapOn)
			return;
		ScreenToAutomap(&nPos, xPos * 32, yPos * 32);
	}

	CHAR szBuffer[800] = "";
	va_list Args;
	va_start(Args, Text);
	vsprintf_s(szBuffer, Text, Args);
	va_end(Args);
	int i;
	wchar_t wBuffer[0x130];
	MultiByteToWideChar(0, 1, szBuffer, 100, wBuffer, 100);
	/*for (int i = 0; szBuffer[i]; i++) wBuffer[i] = szBuffer[i];
		wBuffer[i] = 0;*/

	dwOldSize = D2WIN_SetTextSize(dwFont);
	if (dwCenter != -1)
	{
		D2WIN_GetTextWidthFileNo(wBuffer, &wWidth, &dwFileNo);
		nPos.x -= (wWidth >> dwCenter);
	}

	D2WIN_DrawText(wBuffer, nPos.x, nPos.y, dwColor, -1);
	D2WIN_SetTextSize(dwOldSize);
}

void BoxHook(INT x, INT y, INT xSize, INT ySize, DWORD dwColor, DWORD Trans, BOOL Automap)
{
	POINT Start = { x, y };
	POINT End = { xSize, ySize };
	if (Automap)
	{
		if (!p_D2CLIENT_AutomapOn)
			return;
		ScreenToAutomap(&Start, x * 32, y * 32);
	}

	return D2GFX_DrawRectangle(Start.x, Start.y, End.x + Start.x, End.y + Start.y, dwColor, Trans);
}
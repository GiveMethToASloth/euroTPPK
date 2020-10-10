#include "EuroTPPK.h"
#include "Area.h"
#define QUANTITY_STAT_ID	70

void GameLoopPatch()
{
  if (GameReady())
    TimerTick();
}

void GameEndPatch()
{
  SetAllFalse();
  LevelNames.RemoveAll();
}

/*
if (D2CLIENT_GetAutomapSize()) {
xpos += 1;
ypos -= 5;
}
xpos = (xpos + D2CLIENT_xyAutomapDraw.x -  * D2CLIENT_nAutomapScale;
ypos = (ypos + D2CLIENT_xyAutomapDraw.y +  * D2CLIENT_nAutomapScale;
int xpos2 = ((ypos*2)+xpos)/32;
int ypos2 = ((ypos*2)-xpos)/32;
*/

/*
VOID ScreenToAutomap(POINT *ptPos, int x, int y)
{
  ptPos->x = ((x - y)/2/(*(INT*)p_D2CLIENT_Divisor))-(*p_D2CLIENT_Offset).x+8;
  ptPos->y = ((x + y)/4/(*(INT*)p_D2CLIENT_Divisor))-(*p_D2CLIENT_Offset).y-8;
  if(D2CLIENT_GetAutomapSize())
  {
    --ptPos->x;
    ptPos->y += 5;
  }
}

*/

DWORD attack = 0x6FB0B050 - 0x6fab0000;
void __declspec(naked) __fastcall AttackToWrapper(DWORD Buf) {
  __asm {
    push 0 // EBX was ever zero!!11
    push ecx
    call attack
    retn
  }
}

DWORD GetExpLeft() {
  UnitAny* pUnit = D2CLIENT_GetPlayerUnit();

  if (pUnit)
    return DWORD(D2COMMON_GetExpToAchiveLvl(1, int(D2COMMON_GetUnitStat(pUnit, 0x0C, 0)))) - D2COMMON_GetUnitStat(pUnit, 0x0D, 0);
  //D2COMMON_GetUnitState3(2, D2COMMON_GetUnitState2(pUnit, 0x0C, 0));
  return NULL;
}

void AttackTo(DWORD PlayerStruct) {
  attack = 0x6FB0B050 - 0x6fab0000 + (DWORD)LoadLibrary("D2Client.dll");
  byte Attack[28] = { 0x46,00,00,00, // RIGHT 0x46 LEFT 0xE5
      0x00,00,00,00, // PLAYER STRUCT HIER EINTRAGEN
      0x00,00,00,00, // Unused?!
      0x00,00,00,00, // X Coordinates.. (in WORD)
      0x00,00,00,00, // Y Coordinates.. (in WORD)
      0x03,00,00,00, // Right Attack?
      0x04,00,00,00, // Dito?
  };
  *(DWORD*)&Attack[0x04] = *(DWORD*)0x6FBCC3D0;

  *(WORD*)&Attack[12] = ((UnitAny*)PlayerStruct)->pPath->xPos;
  *(WORD*)&Attack[16] = ((UnitAny*)PlayerStruct)->pPath->yPos;

  AttackToWrapper((DWORD)Attack);
}

void AttackToTele(WORD x, WORD y) {
  byte Attack[28] = { 0x46,00,00,00,
      0x00,00,00,00, // PLAYER STRUCT HIER EINTRAGEN
      0x00,00,00,00, // Unused?!
      0x00,00,00,00, // X Coordinates.. (in WORD)
      0x00,00,00,00, // Y Coordinates.. (in WORD)
      0x03,00,00,00, // Constant?
      0x04,00,00,00, // Dito?
  };
  *(DWORD*)&Attack[0x04] = *(DWORD*)0x6FBCC3D0;

  *(WORD*)&Attack[12] = x;
  *(WORD*)&Attack[16] = y;

  AttackToWrapper((DWORD)Attack);
}

void TeleportToTele(long x, long y) {
  BYTE Packet1[] = { 0x3c,0x36,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF };
  SendGAMEPacket(Packet1, sizeof(Packet1));

  AttackToTele(x, y);
}

BOOL SetSkill(WORD wSkillId, BOOL bLeft) //used
{
  if (!D2CLIENT_GetPlayerUnit()) return FALSE;

  BYTE aPacket[9];

  aPacket[0] = 0x3C;
  *(WORD*)&aPacket[1] = wSkillId;
  aPacket[3] = 0;
  aPacket[4] = (bLeft) ? 0x80 : 0;
  *(DWORD*)&aPacket[5] = 0xFFFFFFFF;

  D2NET_SendPacket(9, 1, aPacket);
  return TRUE;
}

void FlashPlayer(DWORD ID) {
  BYTE UPDATE[9] = { 0x4b, 0,0,0,0,     0,0,0,0 };
  memcpy(&UPDATE[5], &ID, 4);
  SendGAMEPacket(UPDATE, 9);
}

void PrintLists(void)
{
  PrintMessage(false, FONTCOLOR_WHITE, ":: Friends: %d  Enemys: %d Spammers: %d", PlayerFriendList->GetItemCount(), PlayerEnemyList->GetItemCount(), PlayerSpamList->GetItemCount());
}

bool IsInventoryOpen() {
  int State = *(DWORD*)0x6FBCC1D0; //  1.11 6FBCC3E4
  if (State == 1) return true;
  else false;
  return false;
}
DWORD GUI = 0x6FB52E90; // 1.11 6FB1A5B0

void  ToggleInventory(bool on) {
  if (on)
    if (IsInventoryOpen() == false)
      _asm CALL GUI
  if (!on)
    if (IsInventoryOpen())
      _asm CALL GUI
}

DWORD __declspec(naked) IsExpansion() {
  __asm {
    //MOV EAX,DWORD PTR DS:[6FBCA2F4]
    mov eax, 0x6FBB330C/*6FBCA2F4*/
    mov eax, [eax]
    retn
  }
}

GameStructInfo* GetGameInfo() {
  GameStructInfo* Addresse = D2CLIENT_GetGameInfo();
  GameStructInfo* Returne;
  __asm {
    push eax
    mov eax, [Addresse]
    mov eax, [eax]
    mov[Returne], eax
    pop eax
  }
  return Returne;
}

void Tele(WORD x, WORD y) {
  DWORD ID;
  BYTE TELE[5] = { 0x5f, 0,0,   0,0 };
  BYTE UPDATE[9] = { 0x4b, 0,0,0,0,     0,0,0,0 };
  ID = GetPlayerID(D2CLIENT_GetPlayerUnit());
  memcpy(&UPDATE[5], &ID, 4);
  memcpy(&TELE[1], &x, 2);
  memcpy(&TELE[3], &y, 2);
  SendGAMEPacket(TELE, 5);
  SendGAMEPacket(UPDATE, 9);
}

DWORD GetTileLevelNo(Room2* lpRoom2, DWORD dwTileNo)
{
  for (RoomTile* pRoomTile = lpRoom2->pRoomTiles; pRoomTile; pRoomTile = pRoomTile->pNext)
  {
    if (*(pRoomTile->nNum) == dwTileNo)
      return pRoomTile->pRoom2->pLevel->dwLevelNo;
  }

  return NULL;
}

Level* GetLevel(DWORD dwLevelNo)
{
  for (Level* pLevel = D2CLIENT_GetPlayerUnit()->pAct->pMisc->pLevelFirst; pLevel; pLevel = pLevel->pNextLevel)
    if (pLevel->dwLevelNo == dwLevelNo)
      return pLevel;

  return D2COMMON_GetLevel(D2CLIENT_GetPlayerUnit()->pAct->pMisc, dwLevelNo);
}

INT GetSkill(WORD wSkillId)
{
  if (!D2CLIENT_GetPlayerUnit()) return 0;

  for (Skill* pSkill = D2CLIENT_GetPlayerUnit()->pInfo->pFirstSkill; pSkill; pSkill = pSkill->pNextSkill)
    if (pSkill->pSkillInfo->wSkillId == wSkillId)
      return D2COMMON_GetSkillLevel(D2CLIENT_GetPlayerUnit(), pSkill, TRUE);

  return 0;
}

int MakeParameter(char* szInput, char** argv, char splitchar, bool bSkipQuote) {
  char* p = szInput;
  int i = 0;
  while (*szInput != '\0') {
    bool bQuoteOn = FALSE;
    while ((*szInput != splitchar || bQuoteOn) && *szInput != '\0') {
      if (*szInput == '\"' || *szInput == '\'' || *szInput == '´' || *szInput == '`')
        if (bSkipQuote)
          bQuoteOn = !bQuoteOn;
      szInput++;
    }
    if (*szInput != '\0')
      *szInput++ = '\0'; //seperate char-arrays
    argv[i++] = p; //set pointer to parameter
    ++p += (szInput - p);
  } //adjust p to next parameter
  return i;
}

// Getting Distance from units.
DWORD GetDistance(DWORD x1, DWORD y1, DWORD x2, DWORD y2) {
  return (DWORD)sqrt((double)((((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)))));
}

DWORD GetDistanceSquared(DWORD x1, DWORD y1, DWORD x2, DWORD y2) {
  return (DWORD)sqrt((double)(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2))));
}

BYTE CalcPercent(DWORD dwVal, DWORD dwMaxVal, BYTE iMin)
{
  if (dwVal == 0 || dwMaxVal == 0)
    return NULL;

  BYTE iRes = (double(dwVal) / double(dwMaxVal)) * 100.0;

  if (iRes == 100)
    iRes = 100;

  return max(iRes, iMin);
}

/*
 void ExitGame() {
DWORD ExitAddr=(DWORD)LoadLibrary("D2Client.dll")+0x7AB00;
     __asm {
      call ExitAddr
     }
 }*/

 //Getting Mouse Positon
void GetD2MousePos(POINT& Pointer) {
  typedef unsigned short(__fastcall* pPos)();

  DWORD MouseX = D2CLIENT_MouseX;
  DWORD MouseY = D2CLIENT_MouseY;
  pPos pPosX = (pPos)MouseY;
  pPos pPosY = (pPos)MouseX;
  Pointer.x = pPosX();
  Pointer.y = pPosY();
}

void HoldRightUp(long X, long Y) {
  SendMessage((HWND)D2GFX_GetHwnd(), WM_RBUTTONUP, 0, MAKELONG(X, Y));
}

//id and name converting

void Hostile(DWORD ID) {
  BYTE Hostile[7] = { 0x5d,0x04,0x01,0,0,0,0 };
  *(DWORD*)&Hostile[3] = ID;
  SendGAMEPacket(Hostile, sizeof(Hostile));
}

void HostileAll()
{
  int i;
  RosterUnit* pUnit = *p_D2CLIENT_PlayerUnitList;
  BYTE Hostile[7] = { 0x5d,0x04,0x01,0,0,0,0 };

  /*if (GetLevelByN(D2CLIENT_GetPlayerUnit()->pPlayerData->szName) > 8) {
    for (i = 0; pUnit != NULL; i++)
    {
      if (pUnit->dwUnitId != D2CLIENT_GetPlayerUnit()->dwUnitId)
        if (pUnit->wLevel >= 9)
        {
          *(DWORD*)&Hostile[3] = pUnit->dwUnitId;
          SendGAMEPacket(Hostile, sizeof(Hostile));
        }
      pUnit = pUnit->pNext;
    }
    UnhostMembers();
  }*/
}

void UnhostMembers()
{
  /*int i;
  RosterUnit* pUnit = *p_D2CLIENT_PlayerUnitList;
  BYTE UnHostile[7] = { 0x5d,0x04,0x00,0,0,0,0 };
  for (i = 0; pUnit != NULL; i++)
  {
    if (CheckPlayerFriend(GetNameByID(pUnit->dwUnitId)))
    {
      *(DWORD*)&UnHostile[3] = pUnit->dwUnitId;
      SendGAMEPacket(UnHostile, sizeof(UnHostile));
    }
    pUnit = pUnit->pNext;
  }*/
}

//DWORD GetClientHandle() {
//return (DWORD)LoadLibrary("D2Client.dll");
//}
//
//int __declspec(naked) D2CLIENT_GetPlayerXOffset2() {
//	__asm {
//			call GetClientHandle
//			add eax, 0x5D650
//			call eax
//			ret
//	}
//}
//
//int __declspec(naked) D2CLIENT_GetPlayerYOffset2() {
//	__asm {
//			call GetClientHandle
//			add eax, 0x5D670
//			call eax
//			ret
//	}
//}

//
/*Level* GetLevel(DWORD dwLevelNo)
{
  for(Level* pLevel = D2CLIENT_GetPlayerUnit()->pAct->pMisc->pLevelFirst; pLevel; pLevel = pLevel->pNextLevel)
    if (pLevel->dwLevelNo == dwLevelNo)
      return pLevel;

  return D2COMMON_GetLevel(D2CLIENT_GetPlayerUnit()->pAct->pMisc, dwLevelNo);
}*/
//

void fpEnumUnits(fp EnumFunction, DWORD Type) {
  Level* pLevel = GetLevel(D2CLIENT_GetPlayerUnit()->pAct->pMisc->pLevelFirst->dwLevelNo);

  //(//for(Room2 *pRoom2 = pLevel->pRoom2First;pRoom2;pRoom2=(Room2*)pRoom2->pRoom2Other) { // nin
  for (Room2* pRoom2 = pLevel->pRoom2First; pRoom2; pRoom2 = (Room2*)pRoom2->pRoom2Next) {
    for (Room1* pRoom1 = pRoom2->pRoom1; pRoom1; pRoom1 = pRoom1->pRoomNext) {
      //	for(UnitAny* pUnit = pRoom1->pUnitFirst;pUnit;pUnit=pUnit->pListNext) {
      for (UnitAny* pUnit = pRoom2->pRoom1->pUnitFirst; pUnit; pUnit = pUnit->pListNext) {
        if (pUnit)
          if (pUnit->dwType == Type || Type == UNIT_ALL)
            if (!EnumFunction(pUnit))
              return;
      }
    }
  }
}

enum { CLASS_AMAZON = 0, CLASS_SORCERESS, CLASS_NECROMANCER, CLASS_PALADIN, CLASS_BARBARIAN, CLASS_DRUID, CLASS_ASSASSIN };

char* GetD2ClassName(DWORD ClassID) {
  switch (ClassID) {
  case CLASS_AMAZON:
    return "Amazon";
  case CLASS_SORCERESS:
    return "Sorceress";
  case CLASS_NECROMANCER:
    return "Necromancer";
  case CLASS_PALADIN:
    return "Paladin";
  case CLASS_BARBARIAN:
    return "Barbarian";
  case CLASS_DRUID:
    return "Druid";
  case CLASS_ASSASSIN:
    return "Assassin";
  default:
    return "Unknown";
  }
}

char* D2ClassName(DWORD ClassID) {
  switch (ClassID) {
  case CLASS_AMAZON:
    return "Ama";
  case CLASS_SORCERESS:
    return "Sor";
  case CLASS_NECROMANCER:
    return "Nec";
  case CLASS_PALADIN:
    return "Pal";
  case CLASS_BARBARIAN:
    return "Bar";
  case CLASS_DRUID:
    return "Dru";
  case CLASS_ASSASSIN:
    return "Ass";
  default:
    return "Unknown";
  }
}

char* GetD2LevelName(DWORD LevelID) {
  switch (LevelID) {
  case LEVEL_NONE:
    return "Area Not Known";
    //Act 1
  case LEVEL_ROGUE_ENCAMPMENT:
    return "Rogue Encampent";
  case LEVEL_BLOOD_MOOR:
    return "Blood Moor";
  case LEVEL_COLD_PLAINS:
    return "Cold Plains";
  case LEVEL_STONY_FIELD:
    return "Stony Field";
  case LEVEL_DARK_WOOD:
    return "Dark Wood";
  case LEVEL_BLACK_MARSH:
    return "Black Marsh";
  case LEVEL_TAMOE_HIGHLAND:
    return "Tamoe Highland";
  case LEVEL_DEN_OF_EVIL:
    return "Den Of Evil";
  case LEVEL_CAVE_LEVEL_1:
    return "Cave Level 1";
  case LEVEL_UNDERGROUND_PASSAGE_LEVEL_1:
    return "Underground Passage 1";
  case LEVEL_UNDERGROUND_PASSAGE_LEVEL_2:
    return "Underground Passage 2";
  case LEVEL_HOLE_LEVEL_1:
    return "Hole 1";
  case LEVEL_HOLE_LEVEL_2:
    return "Hole 2";
  case LEVEL_PIT_LEVEL_1:
    return "Pit 1";
  case LEVEL_PIT_LEVEL_2:
    return "Pit 2";
  case LEVEL_CAVE_LEVEL_2:
    return "Cave 1";
  case LEVEL_BURIAL_GROUNDS:
    return "Burial Grounds";
  case LEVEL_CRYPT:
    return "Crypt";
  case LEVEL_MAUSOLEUM:
    return "Mausoleum";
  case LEVEL_FORGOTTEN_TOWER:
    return "Forgotten Tower";
  case LEVEL_TOWER_CELLAR_LEVEL_1:
    return "Forgotten Tower 1";
  case LEVEL_TOWER_CELLAR_LEVEL_2:
    return "Forgotten Tower 2";
  case LEVEL_TOWER_CELLAR_LEVEL_3:
    return "Forgotten Tower 3";
  case LEVEL_TOWER_CELLAR_LEVEL_4:
    return "Forgotten Tower 4";
  case LEVEL_TOWER_CELLAR_LEVEL_5:
    return "Forgotten Tower 5";
  case LEVEL_MONASTERY_GATE:
    return "Monastery Gate";
  case LEVEL_OUTER_CLOISTER:
    return "Outer Cloister";
  case LEVEL_BARRACKS:
    return "Barracks";
  case LEVEL_JAIL_LEVEL_1:
    return "Jail 1";
  case LEVEL_JAIL_LEVEL_2:
    return "Jail 2";
  case LEVEL_JAIL_LEVEL_3:
    return "Jail 3";
  case LEVEL_INNER_CLOISTER:
    return "Inner Cloister";
  case LEVEL_CATHEDRAL:
    return "Cathedral";
  case LEVEL_CATACOMBS_LEVEL_1:
    return "Catacombs 1";
  case LEVEL_CATACOMBS_LEVEL_2:
    return "Catacombs 2";
  case LEVEL_CATACOMBS_LEVEL_3:
    return "Catacombs 3";
  case LEVEL_CATACOMBS_LEVEL_4:
    return "Catacombs 4";
  case LEVEL_TRISTRAM:
    return "Tristram";
  case LEVEL_MOO_MOO_FARM:
    return "Cow Level";
    //Act 1 End
    //Act 2 Start
  case LEVEL_LUT_GHOLEIN:
    return "Lut Gholein";
  case LEVEL_ROCKY_WASTE:
    return "Rocky Waste";
  case LEVEL_DRY_HILLS:
    return "Dry Hills";
  case LEVEL_FAR_OASIS:
    return "Far Oasis";
  case LEVEL_LOST_CITY:
    return "Lost City";
  case LEVEL_VALLEY_OF_SNAKES:
    return "Valley of Snakes";
  case LEVEL_CANYON_OF_THE_MAGI:
    return "Canyon of the Magi";
  case LEVEL_SEWERS_LEVEL_1:
    return "Sewers Level 1";
  case LEVEL_SEWERS_LEVEL_2:
    return "Sewers Level 2";
  case LEVEL_SEWERS_LEVEL_3:
    return "Sewers Level 3";
  case LEVEL_HAREM_LEVEL_1:
    return "Harem Level 1";
  case LEVEL_HAREM_LEVEL_2:
    return "Harem Level 2";
  case LEVEL_PALACE_CELLAR_LEVEL_1:
    return "Palace Cellar 1";
  case LEVEL_PALACE_CELLAR_LEVEL_2:
    return "Palace Cellar 2";
  case LEVEL_PALACE_CELLAR_LEVEL_3:
    return "Palace Cellar 3";
  case LEVEL_STONY_TOMB_LEVEL_1:
    return "Stony Tomb 1";
  case LEVEL_HALLS_OF_THE_DEAD_LEVEL_1:
    return "Halls of Dead 1";
  case LEVEL_HALLS_OF_THE_DEAD_LEVEL_2:
    return "Hallsof Dead 2";
  case LEVEL_CLAW_VIPER_TEMPLE_LEVEL_1:
    return "Claw Viper Temple 1";
  case LEVEL_STONY_TOMB_LEVEL_2:
    return "Stony Tomb 2";
  case LEVEL_HALLS_OF_THE_DEAD_LEVEL_3:
    return "Halls of Dead 3";
  case LEVEL_CLAW_VIPER_TEMPLE_LEVEL_2:
    return "Claw Viper Temple 2";
  case LEVEL_MAGGOT_LAIR_LEVEL_1:
    return "Maggot Lair 1";
  case LEVEL_MAGGOT_LAIR_LEVEL_2:
    return "Maggot Lair 2";
  case LEVEL_MAGGOT_LAIR_LEVEL_3:
    return "Maggot Lair 3";
  case LEVEL_ANCIENT_TUNNELS:
    return "Ancient Tunnels";
  case LEVEL_TAL_RASHAS_TOMB1:
    return "Tal Rashas Tomb";
  case LEVEL_TAL_RASHAS_TOMB2:
    return "Tal Rashas Tomb";
  case LEVEL_TAL_RASHAS_TOMB3:
    return "Tal Rashas Tomb";
  case LEVEL_TAL_RASHAS_TOMB4:
    return "Tal Rashas Tomb";
  case LEVEL_TAL_RASHAS_TOMB5:
    return "Tal Rashas Tomb";
  case LEVEL_TAL_RASHAS_TOMB6:
    return "Tal Rashas Tomb";
  case LEVEL_TAL_RASHAS_TOMB7:
    return "Tal Rashas Tomb";
  case LEVEL_DURIELS_LAIR:
    return "Duriels Lair";
  case LEVEL_ARCANE_SANCTUARY:
    return "Arcane Sanctuary";
    //Act 2 End
    //Act 3 Start
  case LEVEL_KURAST_DOCKTOWN:
    return "Kurast Dockown";
  case LEVEL_SPIDER_FOREST:
    return "Spider Forest";
  case LEVEL_GREAT_MARSH:
    return "Great Marsh";
  case LEVEL_FLAYER_JUNGLE:
    return "Flayer Jungle";
  case LEVEL_LOWER_KURAST:
    return "Lower Kurast";
  case LEVEL_KURAST_BAZAAR:
    return "Kurast Bazaar";
  case LEVEL_UPPER_KURAST:
    return "Upper Kurast";
  case LEVEL_KURAST_CAUSEWAY:
    return "Kurast Causeway";
  case LEVEL_TRAVINCAL:
    return "Travincal";
  case LEVEL_SPIDER_CAVE:
    return "Spider Cave";
  case LEVEL_SPIDER_CAVERN:
    return "Spider Cavern";
  case LEVEL_SWAMPY_PIT_LEVEL_1:
    return "Swampy Pit 1";
  case LEVEL_SWAMPY_PIT_LEVEL_2:
    return "Swampy Pit 2";
  case LEVEL_FLAYER_DUNGEON_LEVEL_1:
    return "Flayer Dungeon 1";
  case LEVEL_FLAYER_DUNGEON_LEVEL_2:
    return "Flayer Dungeon 2";
  case LEVEL_SWAMPY_PIT_LEVEL_3:
    return "Swampy Pit 3";
  case LEVEL_FLAYER_DUNGEON_LEVEL_3:
    return "Flayer Dungeon 3";
  case LEVEL_RUINED_TEMPLE:
    return "Ruined Temple";
  case LEVEL_DISUSED_FANE:
    return "Disused Fane";
  case LEVEL_FORGOTTEN_RELIQUARY:
    return "F. Reliquary";
  case LEVEL_FORGOTTEN_TEMPLE:
    return "Forgotten Temple";
  case LEVEL_RUINED_FANE:
    return "Ruined Fane";
  case LEVEL_DISUSED_RELIQUARY:
    return "D. Reliquary";
  case LEVEL_DURANCE_OF_HATE_LEVEL_1:
    return "Durance of Hate 1";
  case LEVEL_DURANCE_OF_HATE_LEVEL_2:
    return "Durance of Hate 2";
  case LEVEL_DURANCE_OF_HATE_LEVEL_3:
    return "Durance of Hate 3";
    //Act 3 End
    //Act 4 Start
  case LEVEL_THE_PANDEMONIUM_FORTRESS:
    return "P. Fortess";
  case LEVEL_OUTER_STEPPES:
    return "Outer Steppes";
  case LEVEL_PLAINS_OF_DESPAIR:
    return "P. of Despair";
  case LEVEL_CITY_OF_THE_DAMNED:
    return "City of Damned";
  case LEVEL_RIVER_OF_FLAME:
    return "River Of Flame";
  case LEVEL_CHAOS_SANCTUM:
    return "Chaos Sanctum";
    //Act 4 End
    //Act 5 Start
  case LEVEL_HARROGATH:
    return "Harrogath";
  case LEVEL_BLOODY_FOOTHILLS:
    return "Bloody Foothills";
  case LEVEL_RIGID_HIGHLANDS:
    return "Fridgid Highlands";
  case LEVEL_ARREAT_PLATEAU:
    return "Arreat Plateau";
  case LEVEL_CRYSTALIZED_CAVERN_LEVEL_1:
    return "Crystalline Passage";
  case LEVEL_CELLAR_OF_PITY:
    return "Cellar of Pitty";
  case LEVEL_CRYSTALIZED_CAVERN_LEVEL_2:
    return "Glacial T.";
  case LEVEL_ECHO_CHAMBER: //
    return "Halls of Pain";
  case LEVEL_TUNDRA_WASTELANDS:
    return "Frozen Tundra";
  case LEVEL_GLACIAL_CAVES_LEVEL_1:
    return "Ancients Way";
  case LEVEL_GLACIAL_CAVES_LEVEL_2:
    return "Glacial Caves 2";
  case LEVEL_ROCKY_SUMMIT:
    return "Rocky Summit";
  case LEVEL_NIHLATHAKS_TEMPLE:
    return "Nihlathaks Temple";
  case LEVEL_HALLS_OF_ANGUISH:
    return "Halls of Anguish";
  case LEVEL_HALLS_OF_DEATHS_CALLING: //
    return "Deaths Calling";
  case LEVEL_HALLS_OF_VAUGHT:
    return "Halls of Vaught";
  case LEVEL_HELL1: //
    return "Hell 1";
  case LEVEL_HELL2: //
    return "Hell 2";
  case LEVEL_HELL3: //
    return "Hell 3";
  case LEVEL_THE_WORLDSTONE_KEEP_LEVEL_1:
    return "Worldstone Keep 1";
  case LEVEL_THE_WORLDSTONE_KEEP_LEVEL_2:
    return "Worldstone Keep 2";
  case LEVEL_THE_WORLDSTONE_KEEP_LEVEL_3:
    return "Worldstone Keep 3";
  case LEVEL_THRONE_OF_DESTRUCTION:
    return "Throne of Destruction";
  case LEVEL_THE_WORLDSTONE_CHAMBER:
    return "Worldstone Chamber";
    // Act 5 End
  default:
    return "Unknown";
  }
}

DWORD GetPlayerArea(VOID)
{
  if (D2CLIENT_GetPlayerUnit())
    if (D2CLIENT_GetPlayerUnit()->pPath)
      if (D2CLIENT_GetPlayerUnit()->pPath->pRoom1)
        if (D2CLIENT_GetPlayerUnit()->pPath->pRoom1->pRoom2)
          if (D2CLIENT_GetPlayerUnit()->pPath->pRoom1->pRoom2->pLevel)
            return D2CLIENT_GetPlayerUnit()->pPath->pRoom1->pRoom2->pLevel->dwLevelNo;
  return NULL;
}

BOOL IsTownLevel(INT nLevel)
{
  if (nLevel == MAP_A1_ROGUE_ENCAMPMENT ||
    nLevel == MAP_A2_LUT_GHOLEIN ||
    nLevel == MAP_A3_KURAST_DOCKS ||
    nLevel == MAP_A4_THE_PANDEMONIUM_FORTRESS ||
    nLevel == MAP_A5_HARROGATH)
    return TRUE;
  return FALSE;
}

//TPBook finding function
UnitAny* FindTPBook(VOID) {
  UnitAny* pPlayer = D2CLIENT_GetPlayerUnit();
  if (pPlayer) {
    if (pPlayer->pInventory) {
      UnitAny* pItem = D2COMMON_GetItemFromInventory(pPlayer->pInventory);
      bool bFoundTPBook = false;
      while (pItem) {
        if (pItem->pItemData) {
          ItemTxt* pTxt = D2COMMON_GetItemText(pItem->dwTxtFileNo);
          if (pTxt) {
            char szCode[4];
            strncpy(szCode, pTxt->szCode, 3);
            szCode[3] = '\0';
            if (!_strcmpi(szCode, "tbk"))
              if (D2COMMON_GetUnitStat(pItem, QUANTITY_STAT_ID, 0))
                return pItem;
              else
                bFoundTPBook = true;
          }
        }
        pItem = D2COMMON_GetNextItemFromInventory(pItem);
      }
      if (bFoundTPBook) {
        PrintMessage(false, FONTCOLOR_RED, "::ÿc  Your TP books are empty!");
        return nullptr;
      }
    }
  }
  PrintMessage(false, FONTCOLOR_RED, "::ÿc  Couldn't find any TP book.");
  return nullptr;
}

//Get amount of TP's in the Book.
DWORD GetTPs() {
  UnitAny* pPlayer = D2CLIENT_GetPlayerUnit();
  if (pPlayer)
    if (pPlayer->pInventory) {
      UnitAny* pItem = D2COMMON_GetItemFromInventory(pPlayer->pInventory);
      bool bFoundTPBook = false;
      while (pItem) {
        if (pItem->pItemData) {
          ItemTxt* pTxt = D2COMMON_GetItemText(pItem->dwTxtFileNo);
          if (pTxt) {
            char szCode[4];
            strncpy(szCode, pTxt->szCode, 3);
            szCode[3] = '\0';
            if (!_strcmpi(szCode, "tbk"))
              if (D2COMMON_GetUnitStat(pItem, QUANTITY_STAT_ID, 0))
                return D2COMMON_GetUnitStat(pItem, QUANTITY_STAT_ID, 0);
              else
                return 0;
          }
        }
        pItem = D2COMMON_GetNextItemFromInventory(pItem);
      }
    }
  return NULL;
}

// Create a TP based on the FindTPBook values.
bool MakeTP(void) {
  if (!IsTownLevel(GetPlayerArea())) {
    UnitAny* pPlayer = D2CLIENT_GetPlayerUnit();
    if (pPlayer) {
      if (pPlayer->pPath) {
        UnitAny* pItem = FindTPBook();
        if (pItem) {
          UseItem(pItem);
          return true;
        }
      }
    }
  }
  return false;
}

/*if(TakeNextTP) {
  if(CheckInTown())
    TakeNextTP=false;
}*//*
Act* GetAct() {
DWORD ActBase = (DWORD)LoadLibrary("D2Client.dll") +0x11C01C;
if(D2CLIENT_GetPlayerUnit()->dwAct!=NULL)
      return (D2CLIENT_GetPlayerUnit()->dwAct);
}*/
/*
void GetAct(int ID) {
  DWORD ID=D2CLIENT_GetPlayerUnit()->pAct->pRoom1->pRoom2->pLevel->dwLevelNo;
if(ID>=LEVEL_ROGUE_ENCAMPMENT&&ID<LEVEL_LUT_GHOLEIN)
  return 1;
if(ID>=LEVEL_LUT_GHOLEIN&&ID<LEVEL_KURAST_DOCKTOWN)
  return 2;
if(ID>=LEVEL_KURAST_DOCKTOWN&&ID<LEVEL_THE_PANDEMONIUM_FORTRESS)
  return 3;
if(ID>=LEVEL_HARROGATH)
  return 5;
if(ID>=LEVEL_THE_PANDEMONIUM_FORTRESS&&ID<LEVEL_HARROGATH);
  return 4;
return 5;
}
*/
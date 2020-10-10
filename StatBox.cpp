#include "EuroTPPK.h"

bool ToggleInfo = false;
bool TargetInfo = false;

StatBox sInfo[] = {
  {STAT_STRENGTH,"Strength",1,2},
  {STAT_ENERGY,"Energie",1,2},
  {STAT_DEXTERITY,"Dexterity",1,2},
  {STAT_STAMINA,"Stamina",1,2,true},
  {STAT_MAXSTAMINA,"MaxStamina",1,2,true},
  {STAT_LEVEL,"Level",1,2},
  {STAT_GOLD,"Gold",1,2},
  {STAT_GOLDBANK,"GoldBank",1,2},
  {STAT_TOBLOCK,"To Block",1,2},
  {STAT_DAMAGEREDUCTION,"Damage Reduction",8,4}, //
  {STAT_MAGICDAMAGEREDUCTION,"Magic Damage Reduction",8,4},
  {STAT_DAMAGERESIST,"Damage Resist",8,4},
  {STAT_MAXMAGICRESIST,"Max Magic Resist",8,4},//
  {STAT_FIRERESIST,"Fire Resist",1,4},
  {STAT_MAXFIRERESIST,"Max Fire Resist",1,4},
  {STAT_LIGHTNINGRESIST,"Lighting Resist",8,4},
  {STAT_MAXLIGHTNINGRESIST,"Max Lighting Resist",8,4},
  {STAT_COLDRESIST,"Cold Resist",3,4},
  {STAT_MAXCOLDRESIST,"Max Cold Resist",3,4},
  {STAT_POISONRESIST,"Poison Resist",2,4},
  {STAT_MAXPOISONRESIST,"Max Posion Resist",2,4},
  {STAT_VELOCITYPERCENT,"Velocity Percent",1,2},
  {STAT_MAGICFIND,"Magic Find",1,4},
  {STAT_IAS,"IAS",0,4},
  {STAT_FASTERRUNWALK,"Faster Run/Walk",0,4},
  {STAT_FASTERHITRECOVERY,"Fast Hit Recovery",0,4},
  {STAT_FASTERBLOCK,"Faster Block",0,4},
  {STAT_FASTERCAST,"Fast CastRate",0,4},
  {STAT_CRUSHINGBLOW,"Crushing Blow",0,4},
  {STAT_DEADLYSTRIKE,"Deadly Strike",0,4},
  {STAT_FIREABSORBPERCENT,"Fire Absorb Percent",1,4},
  {STAT_FIREABSORB,"Fire Absorb",1,4},
  {STAT_LIGHTNINGABSORBPERCENT,"Lighting Absorb Percent",8,4},
  {STAT_LIGHTNINGABSORB,"Lighting Absorb",8,4},
  {STAT_COLDABSORBPERCENT,"Cold Absorb Percent",3,4},
  {STAT_COLDABSORB,"Cold Absorb",3,4},
};

void DrawStatBox(DWORD UnitID) {
  int x = 480;
  int y = 100;
  int totalx = 155;
  int totaly = 10;

  UnitAny* pUnit = D2CLIENT_GetPlayerUnit();
  /*UnitAny* pUnit = D2CLIENT_FindServerSideUnit(GetPlayerID(), UNIT_PLAYER);*/
  if (!pUnit) {
    TargetInfo = false;
    ToggleInfo = false;
    return;
  }
  for (int i = 0; i < ARRAYSIZE(sInfo); i++)
    totaly += 10;

  // Drawing the boarder..
  D2GFX_DrawRectangle(x, y, x + totalx, y + totaly, 142, 0);
  D2DrawRectFrame(x, y, x + totalx, y + totaly);
  y += 5;
  for (int i = 0; i < ARRAYSIZE(sInfo); i++) {
    y = y + 10;
    char Buffer[200];
    int value = D2COMMON_GetUnitStat((UnitAny*)pUnit, sInfo[i].Statnumber, 0);
    if (sInfo[i].shift)
      value = value >> 8;
    sprintf(Buffer, "%s: ÿc%d%d", sInfo[i].StatInfo, sInfo[i].StatColor, value);
    DrawTextToScreen(Buffer, x + 5, y, sInfo[i].StringColor, 6);
  }
}
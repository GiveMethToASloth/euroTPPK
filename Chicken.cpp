#include "EuroTPPK.h"

int DrankHealthPot;
int DrankManaPot;
// int LeaveGame;
int DrankRejLife;
int DrankRejMana;

bool TakeNextTP = FALSE;

DWORD GetLifeMana(bool bLife)
{
  UnitAny* pUnit = D2CLIENT_GetPlayerUnit();
  if (pUnit) {
    if (!bLife) {
      return DWORD(CalcPercent(D2COMMON_GetUnitStat(pUnit, STAT_MANA, 0) >> 8, D2COMMON_GetUnitStat(pUnit, STAT_MAXMANA, 0) >> 8));
    }
    else {
      return DWORD(CalcPercent(D2COMMON_GetUnitStat(pUnit, STAT_HP, 0) >> 8, D2COMMON_GetUnitStat(pUnit, STAT_MAXHP, 0) >> 8));
    }
  }
}

void ChickenCheck(void) {
  if (GameReady()) {
    if (!IsTownLevel(GetPlayerArea())) {
      UnitAny* pUnit = D2CLIENT_GetPlayerUnit();
      if (pUnit->dwMode == PLAYER_MODE_DEAD || pUnit->dwMode == PLAYER_MODE_DEATH)
        return;
      DWORD dwLifePer = GetLifeMana(true);
      DWORD dwManaPer = GetLifeMana(false);

      if (v_QuitLifePercent != 0) {
        if (v_QuitLifePercent != 0 && dwLifePer <= (int)v_QuitLifePercent) {
          D2CLIENT_ExitGame();
        }
      }

      if (v_QuitManaPercent != 0) {
        if (v_QuitManaPercent != 0 && dwManaPer <= (int)v_QuitManaPercent) {
          D2CLIENT_ExitGame();
        }
      }

      if (v_TownLifePercent != 0 && dwLifePer <= v_TownLifePercent) {
        if (!v_TakeNextTP)
          if (MakeTP()) {
            char lpszText[100];
            sprintf(lpszText, "Chickens to town (Life)");
            SayOverHead(lpszText);
            v_TakeNextTP = true;
          }
      }

      if (v_TownManaPercent != 0) {
        if (v_TownManaPercent != 0 && dwManaPer <= (int)v_TownManaPercent) {
          if (!TakeNextTP) {
            if (MakeTP()) {
              //PrintMessage("::ÿc  Chickens to town (MANA)",1);
              char lpszText[100];
              sprintf(lpszText, "Chickens to town (Mana)");
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
              TakeNextTP = true;
            }
          }
        }
      }
    }
  }
}

void DrinkCheck(void) {
  if (GameReady()) {
    if (!IsTownLevel(GetPlayerArea())) {
      if (v_AutoDrink) {
        DWORD dwLifePer = GetLifeMana(true);
        DWORD dwManaPer = GetLifeMana(false);

        if (v_AutoDrinkLife != 0 && dwLifePer <= v_AutoDrinkLife) {
          if (GetTickCount64() - DrankHealthPot > v_DrinkLifeTimer) {
            UsePot(0);
            DrankHealthPot = GetTickCount64();
          }
        }

        if (v_AutoDrinkMana != 0 && dwManaPer <= (int)v_AutoDrinkMana) {
          if (GetTickCount64() - DrankManaPot > (int)v_DrinkManaTimer) {
            UsePot(1);
            DrankManaPot = GetTickCount64();
          }
        }

        if (v_AutoDrinkReju != 0 && dwLifePer <= (int)v_AutoDrinkReju) {
          if (GetTickCount64() - DrankRejLife > (int)v_DrinkRejuTimer) {
            UsePot(2);
            DrankRejLife = GetTickCount64();
          }
        }

        //if (v_AutoDrinkManaRej != 0 && ManaPercent <= (int)v_AutoDrinkManaRej) {
        //	if (GetTickCount() - DrankRejMana > (int)v_DrinkRejuTimer) {
        //		DrinkRejMana();
        //		DrankRejMana = GetTickCount();
        //	}
        //}
      }
    }
  }
}
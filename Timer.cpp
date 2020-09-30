#include "EuroTPPK.h"
HANDLE TimerHandle;
DWORD GlobalNPCID = 0;
bool Flash = false;
int FlashDelay;
int Missled;
int Delay = 0;
bool CastMissles = false;
bool AutoPK = false;
bool Test = true;

BOOL ClickMap(DWORD dwClickType, WORD wX, WORD wY, BOOL bShift)
{
  POINT Click = { wX, wY };

  D2COMMON_MapToAbsScreen(&Click.x, &Click.y);

  Click.x -= *p_D2CLIENT_MouseOffsetX;
  Click.y -= *p_D2CLIENT_MouseOffsetY;

  D2CLIENT_clickMap(dwClickType, Click.x, Click.y, bShift ? 0x0C : 8);

  return TRUE;
}

void TimerTick()
{
  ChickenCheck(); //starting Chicken.
  DrinkCheck(); //starting Drinking.

  if (IsTownLevel(GetPlayerArea())) {
    SetInTownVars();
  }
  //Delay++;
  Count++;
  /*if (!strcmp(Auto.GetPlayerNAME(), D2CLIENT_GetPlayerUnit()->pPlayerData->szName))
  {
    RosterUnit* pUnit = (RosterUnit*)*(DWORD*)0x6FBCC080;
    if (pUnit)
      Auto.GetNextPlayer();
    if (!pUnit)
      return;
  }
  if (Auto.GetPlayerLevel() == 0 || Auto.GetPlayerLevel() > 100) {
    RosterUnit* pUnit = (RosterUnit*)*(DWORD*)0x6FBCC080;
    if (pUnit) {
      Auto.GetNextPlayer();
    }
  }
  if (TakeNextTP)
  {
    if (IsTownLevel(GetPlayerArea()))
      TakeNextTP = false;
  }
  if (Hammer)
  {
    GetD2MousePos(Camp);
    ClickMap(0, Camp.x, Camp.y, 1);
  }
  if (CampOn)
  {
    D2CLIENT_clickMap(3, Camp.x, Camp.y, 8);
  }
  if (CampUnitOn)
  {
    D2CLIENT_clickMap(3, Camp.x, Camp.y, 8);
  }*/
  //if(Flash)
  //    {
  //    if(FindUnit(Auto.GetPlayerID(),0)!=NULL)
  //        {
  //        FlashPlayer(Auto.GetPlayerID());
  //		FlashDelay=0;
  //        }
  //    if(FindUnit(Auto.GetPlayerID(),0)==NULL)
  //        {
  //        FlashDelay=-1;
  //        }
  //}
  /*
  if(Test) {
  UnitAny *pUnit = D2CLIENT_GetPlayerUnit ();
  switch(pUnit->dwMode)
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
            //pUnit->dwFrameRemain = 0;
            pUnit->wFrameRate = 600;
            break;
          }
  }
  */
  /*if (AutoPK)
  {
    AutoPK = false;
    Missled = 0;
    CastMissles = true;
    PrintMessage("Starting AutoPK", 8);
  }
  if (CastMissles)
    if (cfg.Missles <= Missled)
    {
      CastMissles = false;
      PrintMessage("Lets kill the bitch! ", 1);
      HostPlayer = true;
      if (MakeTP())
        TakeNextTP = true;
    }
  */
  /*if (CastMissles)
  {
    if (cfg.Missles >= Missled)
    {
      if (Delay > cfg.AutoDelay)
      {
        if (GetDistance(GetPlayerX(GetPlayerID()), GetPlayerY(GetPlayerID()), GetPlayerX(Auto.GetPlayerID()), GetPlayerY(Auto.GetPlayerID())) < 300)
          AttackTo(FindUnit(Auto.GetPlayerID(), 0));
        Missled++;
        Delay = 0;
        PrintMessage("Casting..", 3);
      }
    }
    return;
  }*/
}

void SetInTownVars() {
  if (v_TakeNextTP) v_TakeNextTP = false;
}
#include "EuroTPPK.h"

PacketedAttack Attacks[] =
{
  { D2S_ATTACK, true},
  { D2S_AMPLIFYDAMAGE, false },
  { D2S_BERSERK, false },
  { D2S_BLIZZARD,false },
  { D2S_BONESPEAR,false },
  { D2S_BONESPIRIT,false },
  { D2S_CHAINLIGHTNING,false },
  { D2S_CHARGE,false },
  { D2S_CHARGEDSTRIKE,false },
  { D2S_CONCENTRATE, true },
  { D2S_DOUBLETHROW,true },
  { D2S_FIREBALL, false },
  { D2S_FIREBOLT, false },
  { D2S_WAKEOFFIRE,false },
  { D2S_FISTOFTHEHEAVENS, false },
  { D2S_GLACIALSPIKE,false },
  { D2S_GUIDEDARROW,false },
  { D2S_ICEBLAST,false },
  { D2S_LIGHTNING,false },
  { D2S_LIGHTNINGFURY,false },
  { D2S_LIGHTNINGSENTRY,false },
  { D2S_METEOR,false },
  { D2S_MINDBLAST,false },
  { D2S_MULTIPLESHOT,false },
  { D2S_SMITE,true },
  { D2S_TEETH,false },
  { D2S_TORNADO,false },
  { D2S_VOLCANO,false }
};

bool CheckReady(bool bTownCheck, bool bCheckCasting) {
  if (bTownCheck) {
    if (IsTownLevel(GetPlayerArea())) {
      return false;
    }
  }
  if (bCheckCasting) {
    for (int i = 7; i < 16; i++) {
      if (D2CLIENT_GetPlayerUnit()->dwMode == i) {
        return false;
      }
    }
  }
  return true;
}

void AutoAim::Attack(DWORD dwXPos, DWORD dwYPos, bool bLeft, bool bShift, bool bAttackUnit, UnitAny* pUnit) {
  if (!CheckReady(false, true)) {
    return;
  }
  if (bAttackUnit && !pUnit) {
    return;
  }
  AttackStruct Attack;
  if (!bShift) {
    Attack.dwAttackType = bLeft ? 0xE5 : 0x66;
  }
  else {
    Attack.dwAttackType = bLeft ? 0xC5 : 0x46;
  }
  Attack.lpPlayerUnit = D2CLIENT_GetPlayerUnit();
  Attack.dwTargetX = dwXPos;
  Attack.dwTargetY = dwYPos;
  Attack.lpTargetUnit = pUnit;
  Attack_STUB(&Attack, bAttackUnit);
}

void AutoAim::AttackTarget(bool bLeft) {
  if (CheckReady(true, true)) {
    UnitAny* pUnit = D2CLIENT_FindServerSideUnit(pRoster->dwUnitId, UNIT_TYPE_PLAYER);
    if (pUnit) {
      for (auto& attack : Attacks) {
        if (
          bLeft && D2CLIENT_GetPlayerUnit()->pInfo->pLeftSkill->pSkillInfo->wSkillId == attack.SkillID ||
          !bLeft && D2CLIENT_GetPlayerUnit()->pInfo->pRightSkill->pSkillInfo->wSkillId == attack.SkillID
          ) {
          return Attack(NULL, NULL, bLeft, attack.Shift, true, pUnit);
        }
      }
      return Attack(GetPlayerX(), GetPlayerY(), bLeft, false, false, NULL);
    }
  }
}

void AutoAim::AttackNearest(bool bLeft) {
}

void AutoAim::GetNextPlayer() {
  int i = 0;
  int B = Current;
  Init();
  while (i < B && pRoster != NULL) {
    pRoster = pRoster->pNext;
    i++;
  }
  if (pRoster == NULL) { Current = 1; Init(); }
  else
    Current = B + 1;
}

long AutoAim::GetPlayerX() {
  if (pRoster == NULL) Init();
  return pRoster->Xpos;
}

long AutoAim::GetPlayerY() {
  if (pRoster == NULL) Init();
  return pRoster->Ypos;
}

int AutoAim::GetPlayerLevel() {
  if (pRoster == NULL) Init();
  return pRoster->wLevel;
}

int AutoAim::GetPlayerArea() {
  if (pRoster == NULL) Init();
  return pRoster->dwLevelId;
}

bool AutoAim::SelectPlayer(DWORD PID) {
  pRoster = *p_D2CLIENT_PlayerUnitList;
  while (pRoster) {
    if (pRoster->dwUnitId == PID)
      return true;
    pRoster = pRoster->pNext;
  }
  return false;
}

bool AutoAim::SelectPlayerByName(char* Name) {
  pRoster = *p_D2CLIENT_PlayerUnitList;
  while (pRoster) {
    if (!_strcmpi(pRoster->szName, Name))
      return true;
    pRoster = pRoster->pNext;
  }
  return false;
}

void AutoAim::Init() {
  pRoster = *p_D2CLIENT_PlayerUnitList;
  Current = 1;
}

DWORD AutoAim::GetPlayerID() {
  if (pRoster == NULL) { Init(); return pRoster->dwUnitId; }
  return pRoster->dwUnitId;
}

char* AutoAim::GetPlayerNAME() {
  if (pRoster == NULL)  Init();
  return pRoster->szName2;
}

DWORD AutoAim::GetPlayerCLASS() {
  if (pRoster == NULL) Init();
  return pRoster->dwClassId;
}

//bool AutoAim::IsPlayerFriend() {
//	if (pUnit == NULL) Init();
//	return CheckPlayerFriend(GetPlayerNAME());
//}
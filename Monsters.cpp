#include "EuroTPPK.h"
#include "ArrayEx.h"
int AreaLocaleIds[] = { 0, 5055, 5054, 5053, 5052, 5051, 5050, 5049, 3714, 5047, 5046, 5045, 5044, 5043, 5042, 5041, 5040, 5039, 5038, 5037, 5036, 5035, 5034, 5033, 5032, 5031, 5030, 5029, 5028, 5027, 5026, 5025, 5024, 5023, 5022, 5021, 5020, 5019, 5018, 788, 852, 851, 850, 849, 848, 847, 846, 845, 844, 843, 842, 841, 840, 839, 838, 837, 836, 835, 834, 833, 832, 831, 830, 829, 828, 827, 826, 826, 826, 826, 826, 826, 826, 825, 824, 820, 819, 818, 817, 816, 815, 814, 813, 812, 810, 811, 809, 808, 806, 805, 807, 804, 845, 844, 803, 802, 801, 800, 799, 798, 797, 796, 795, 790, 792, 793, 794, 791, 789, 22646, 22647, 22648, 22649, 22650, 22651, 22652, 22653, 22654, 22655, 22656, 22657, 22660, 21865, 21866, 21867, 22658, 22659, 22662, 22663, 22664, 22665, 22667, 22666, 11155, 11156, 11157, 5018 };

void DrawMonsters() {
  //Grab Player Unit and check if valid
  UnitAny* pUnit = D2CLIENT_GetPlayerUnit();
  if (!pUnit || !pUnit->pAct) return;
  //Check to see if we are in-town, if so return.
  int dwLevelNo = pUnit->pPath->pRoom1->pRoom2->pLevel->dwLevelNo;
  if ((dwLevelNo == 0) || (dwLevelNo == 1) || (dwLevelNo == 40) || (dwLevelNo == 75) || (dwLevelNo == 103) || (dwLevelNo == 109)) return;
  for (Room1* pRoom1 = pUnit->pAct->pRoom1; pRoom1; pRoom1 = pRoom1->pRoomNext) {
    for (UnitAny* pMonster = pRoom1->pUnitFirst; pMonster; pMonster = pMonster->pListNext) {
      if (!IsValidMonster(pMonster))
        continue;
      if (pMonster->dwType == UNIT_MONSTER) {
        DWORD dwColor = v_MonsterColor;
        if (pMonster->pMonsterData->fBoss & 1 || pMonster->pMonsterData->fChamp & 1)
          dwColor = v_ChampionMonsterColor;
        const char szImmunities[][5] = { "ÿc7i", "ÿc8i", "ÿc1i", "ÿc9i", "ÿc3i", "ÿc2i" };
        DWORD dwImmunities[] = { 36,37,39,41,43,45 };
        char szMonTxt[40] = "";
        for (int i = 0; i < 6; i++) {
          DWORD dwImmune = D2COMMON_GetUnitStat(pMonster, dwImmunities[i], 0);
          if (dwImmune >= 100) {
            strcat_s(szMonTxt, szImmunities[i]);
          }
          DrawCross(pMonster->pPath->xPos, pMonster->pPath->yPos, dwColor, true);
          if (v_DrawImunities)
            if (strlen(szMonTxt) > 0)
              TextHook(pMonster->pPath->xPos - 3, pMonster->pPath->yPos, 0, true, 6, 2, "%s", szMonTxt);
        }
      }
    }
  }
}

void DrawAutomapText()
{
  UnitAny* pUnit = D2CLIENT_GetPlayerUnit();
  wchar_t* pLocaleText;
  if (!LevelNames.IsEmpty())
  {
    int townLevels[6] = { 1, 40, 75, 103, 109, 132 };

    for (int i = 0; i < LevelNames.GetSize(); i++)
    {
      LevelNameInfo* pInfo = LevelNames.ElementAt(i);

      if (pInfo->nAct != pUnit->dwAct)
        continue;

      char nLevelName[70];
      pLocaleText = D2LANG_GetLocaleText(AreaLocaleIds[pInfo->nLevelId]);
      WToC(pLocaleText, nLevelName);

      if (pInfo->nLevelId == pUnit->pAct->pMisc->dwStaffTombLevel)
        strcat_s(nLevelName, sizeof(nLevelName), "*");

      TextHook(pInfo->nX, pInfo->nY, 0, true, 6, 1, "%s", nLevelName);
    }
  }
}

// arrows vector

DWORD __declspec(naked) __fastcall D2CLIENT_GetUnitName_STUB(DWORD UnitAny)
{
  __asm
  {
    mov eax, ecx
    jmp D2CLIENT_GetUnitName_I
  }
}
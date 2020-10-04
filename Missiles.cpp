#include "EuroTPPK.h"

void DrawMissiles() {
  //Grab Player Unit and check if valid
  UnitAny* pUnit = D2CLIENT_GetPlayerUnit();
  if (!pUnit || !pUnit->pAct || pUnit->pPath->pRoom1->pRoom2->pLevel->dwLevelNo == 0) return;
  for (Room1* pRoom1 = pUnit->pAct->pRoom1; pRoom1; pRoom1 = pRoom1->pRoomNext) {
    for (UnitAny* pMissile = pRoom1->pUnitFirst; pMissile; pMissile = pMissile->pListNext) {
      if (pMissile->dwType == UNIT_TYPE_MISSILE) {
        DWORD dwColor = -1;
        if (pUnit->dwUnitId == pMissile->dwOwnerId) //Check if it is my own missile
          dwColor = v_MyMissile; //151; //Set the missile color to cYourMissileColor
        //Now lets see if it is another player's missile.
        if ((pMissile->dwOwnerType == UNIT_PLAYER) && (dwColor == -1)) {
          switch (GetPvPStatus(pMissile->dwOwnerId)) {
          case PVP_NEUTRAL: {
            dwColor = v_NeutralMissile; //153;
          } break;
          case PVP_HOSTILE: {
            dwColor = v_EnemyMissile; //98;
          } break;
          case PVP_FRIENDLY: {
            dwColor = v_FriendMissile; //132;
          } break;
          }
        }
        if ((pMissile->dwOwnerType == UNIT_MONSTER) && (dwColor == -1)) {
          UnitAny* pOwner = D2CLIENT_FindServerSideUnit(pMissile->dwOwnerId, pMissile->dwOwnerType);
          if (!pOwner)
            dwColor = 98;
          else if (D2CLIENT_GetMonsterOwner(pOwner->dwUnitId) != -1) {
            switch (GetPvPStatus(D2CLIENT_GetMonsterOwner(pOwner->dwUnitId))) {
            case PVP_NEUTRAL: {
              dwColor = v_NeutralMissile;
            } break;
            case PVP_HOSTILE: {
              dwColor = v_EnemyMissile;
            } break;
            case PVP_FRIENDLY: {
              dwColor = v_FriendMissile;
            } break;
            }
          }
        }
        BoxHook(pMissile->pPath->xPos - 3, pMissile->pPath->yPos - 3, 3, 3, dwColor, 5, true);
      }
    }
  }
}
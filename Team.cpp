#include "EuroTPPK.h"
/*
reminder when updating:  Authn.LifeAddr1 is returned in DEC from 0x6FBCC080 in internet.cpp*/
DWORD PlayerRoster = 0x11C080;
//DWORD PlayerRoster=0x6FBCC080;

//DWORD  __declspec(naked) __fastcall D2CLIENT_CheckLoot(DWORD pUnit) {
//	__asm {
//		mov eax, ecx
//		call D2CLIENT_CheckLootASM
//		retn
//	}
//}

/*void TickCount() {
  RosterUnit* pMe = FindPartyById(D2CLIENT_GetPlayerUnit()->dwUnitId);

  for (RosterUnit* pUnit = *p_D2CLIENT_PlayerUnitList; pUnit; pUnit = pUnit->pNext)
  {
    if (!pUnit)
      break;
    if (!pMe)
      break;
    if (!D2CLIENT_GetPlayerUnit())
      break;
    if (pUnit->dwUnitId == pMe->dwUnitId)
      continue;
    if (!CheckPlayerFriend(pUnit->szName))
      continue;

    DWORD dwFlags = GetPvPStatus(pUnit->dwUnitId);

    if (dwFlags & PVP_ALLIED || dwFlags & PVP_ALLIED_WITH_YOU)
      continue;

    if (dwFlags & PVP_INVITED_BY_YOU)
      continue;

    if (dwFlags & PVP_INVITED_YOU)
      continue;
    // test

 //       if(v_LootMembers)

    // Loot
    if (!D2CLIENT_CheckLoot((DWORD)pUnit)) {
      BYTE data[7];
      data[0] = 0x5D;
      *(LPWORD)&data[1] = 0x0101;
      *(LPDWORD)&data[3] = pUnit->dwUnitId;
      SendGAMEPacket(data, 7);
      PrintMessageBottomLeft("Auto-Looted EuroPK Member", 3);
      for (INT i = 0; i < 100; i++)
      {
        if (D2CLIENT_CheckLoot((DWORD)pUnit))
          break;
        else
          Sleep(1);
      }
    }
    if (v_InviteMembers)
      if (!(dwFlags & PVP_ALLIED || dwFlags & PVP_ALLIED_WITH_YOU ||
        dwFlags & PVP_INVITED_YOU || dwFlags & PVP_INVITED_BY_YOU))
      {
        BYTE data[6];
        *(LPWORD)&data[0] = 0x065E;
        *(LPDWORD)&data[2] = pUnit->dwUnitId;
        SendGAMEPacket(data, 6);

        PrintMessageBottomLeft("Auto-Invited EuroPK Member!", 2);

        for (INT i = 0; i < 100; i++)
        {
          DWORD dwFlags = GetPvPStatus(pUnit->dwUnitId);
          if (dwFlags & PVP_INVITED_BY_YOU)
            break;
          else
            Sleep(100);
        }
      }
  }
  Sleep(1);
}*/

//DWORD __fastcall GameDrawPlayerBlobAndName(UnitAny* pUnit)
//{
//	if (!pUnit)
//		return 0x62;
//
//	if (pUnit->dwType == UNIT_TYPE_PLAYER)
//	{
//		DWORD	dwFlags1 = GetPvpFlags(pUnit->dwUnitId);
//
//		if (dwFlags1 & PVP_HOSTILED_BY_YOU || dwFlags1 & PVP_HOSTILED_YOU)
//			return 8;
//		if (dwFlags1 & PVP_ALLIED_WITH_YOU)
//			return 2;
//		if (dwFlags1 & !PVP_ALLIED || dwFlags1 & !PVP_ALLIED_WITH_YOU)
//			return 0;
//		/*	if(pUnit->dwUnitId == Auto.GetPlayerID())
//				return 0x6C;
//
//			DWORD dwFlags = GetPvpFlags(pUnit->dwUnitId);
//			if(dwFlags & PVP_HOSTILED_BY_YOU || dwFlags & PVP_HOSTILED_YOU)
//				return 0x66;*/
//	}
//
//	return 0x62;
//}

// Resolution stuff functions etc...
DWORD __declspec(naked) GetSizeX() {
  _asm mov eax, [0x6FBA4FC4]
    _asm ret
}

DWORD __declspec(naked) GetSizeY() {
  _asm mov eax, [0x6FBA4FC8]
    _asm ret
}

DWORD __declspec(naked) GetScreenSize() {
  _asm mov eax, [0x6FBCC3E4]
    _asm ret
}
DWORD ResolutionStuff = 0x6FAE703E;
DWORD XG;
DWORD YG;
DWORD GUI2 = 0x6FB1A5B0;

void __declspec(naked) ResizeD2() {
  //6FAE6FE0   $ E8 CB5FFDFF    CALL <JMP.&D2gfx.#10063>
  __asm {
    call GUI2
    ret
    /*
    mov eax, 0x6FAE6FE0
    call eax
    ret*/
  }
}

DWORD NewJump = 0x6FB15F90;
DWORD aCall = 0x6FB01710;

void __declspec(naked) __fastcall NewSize(DWORD H, DWORD W) {
  __asm {
    MOV DWORD PTR DS : [0x6FBA4FC4] , ecx // H
    MOV DWORD PTR DS : [0x6FBA4FC8] , edx // W
    MOV DWORD PTR DS : [0x6FBD3394] , ECX
    MOV DWORD PTR DS : [0x6FBD3390] , EDX
    MOV DWORD PTR DS : [0x6FBA4FCC] , ECX
    MOV DWORD PTR DS : [0x6FBCC3E4] , eax

    jmp NewJump
    ret
  }
}
DWORD ChangeWindowCall = 0x6F8F30D0;
void __declspec(naked) __fastcall NewResolution(DWORD Size) {
  __asm {
    MOV DWORD PTR DS : [0x6FBCC3E4] , 0
    push ecx
    call ChangeWindowCall
    retn
  }
}

void ToggleResolution(int x, int y, int mode) {
  NewResolution(mode);
  NewSize(x, y);
  //	ResizeD2();
}
bool Resized = false;
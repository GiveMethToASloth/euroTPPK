#include "EuroTPPK.h"

DWORD __declspec(naked) __fastcall D2CLIENT_clickParty_ASM(DWORD RosterUnit, DWORD Mode)
{
  __asm
  {
    mov eax, ecx
    jmp D2CLIENT_clickParty_I
  }
}

DWORD __declspec(naked) GetPlayerID(VOID) {
  __asm {
    MOV EAX, DWORD PTR DS : [0x6FBCC3D0]
    MOV ECX, DWORD PTR DS : [EAX + 0xC]
    mov eax, ecx
    ret
  }
}
DWORD SendPacketAddr = 0x91A0; // 6FB291A0-6FBF0000
void SendGAMEPacket(BYTE* Packet, DWORD PacketSize) {
  DWORD size1 = PacketSize;
  __asm {
    pushad
    mov eax, Packet
    push Packet
    mov ebx, size1
    mov edx, 0x6FB291A0
    call edx
    popad
  }
}

void __declspec(naked) __fastcall Attack_STUB(AttackStruct* Attack, bool AttackingUnit)
{
  __asm
  {
    push esi;
    mov esi, ecx;
    push edx;
    call D2CLIENT_Attack;
    pop esi;
    ret;
  }
}

//DWORD p_D2CLIENT_pUnitTableM=0x6FBCA960; // 6FBCA960 || 6FBCA960-6FAB0000
//DWORD D2CLIENT_GetUnitFromId_M=0x6FACE550; // 6FACE550-6FAB0000
//DWORD p_D2CLIENT_pUnitTableM = 0x11A960;
//DWORD D2CLIENT_GetUnitFromId_M = 0x1E550;
//DWORD __declspec(naked) __fastcall D2CLIENT_GetUnitFromId_STUB(DWORD unitid, DWORD unittype)
//{
//	__asm
//	{
//		pop eax;
//		push edx; // unittype
//		push eax; // return address
//
//		shl edx, 9;
//		mov eax, p_D2CLIENT_pUnitTableM;
//		add edx, eax;
//		mov eax, ecx; // unitid
//		and eax, 0x7F;
//		jmp D2CLIENT_GetUnitFromId_M;
//	}
//}

WORD GetPlayerX(DWORD ID) {
  UnitAny* pUnit = D2CLIENT_FindServerSideUnit(ID, UNIT_TYPE_PLAYER);
  if (pUnit != NULL)
    return pUnit->pPath->xPos;
  return 0;
}
WORD GetPlayerY(DWORD ID) {
  UnitAny* pUnit = D2CLIENT_FindServerSideUnit(ID, UNIT_TYPE_PLAYER);
  if (pUnit != NULL)
    return pUnit->pPath->yPos;
  return 0;
}
//WORD GetPlayerXTarget(DWORD ID) {
//	UnitAny* pUnit = (UnitAny*)D2CLIENT_GetUnitFromId_STUB(ID, 0);
//	if (pUnit != NULL)
//		return pUnit->pPath->xTarget;
//	return 0;
//}
//WORD GetPlayerYTarget(DWORD ID) {
//	UnitAny* pUnit = (UnitAny*)D2CLIENT_GetUnitFromId_STUB(ID, 0);
//	if (pUnit != NULL)
//		return pUnit->pPath->yTarget;
//	return 0;
//}

DWORD D2CLIENT_TestPvpFlag_M = 0x30DD0;

DWORD __declspec(naked) __fastcall TestPvpFlag_STUB(DWORD planum1, DWORD planum2, DWORD flagmask)
{
  __asm {
    push esi
    push[esp + 8] // flagmask
    mov esi, edx
    mov edx, ecx
    call D2CLIENT_TestPvpFlag_M
    pop esi
    ret 4
  }
}

//DWORD LifeAddr=0x6FD856E0;/*(0x6FD5BB60); 1876448992*/
//int LifeAddr = Authn.LifeAddr1;
// local 0x6FD856E0 internet 0x6FD856E9

//DWORD __declspec(naked) GetCurrentLife() {
//	__asm {
//		mov eax, 0x6FBCC3D0
//		mov eax, [eax]
//		push 0
//		push 6
//		push eax
//		call DWORD PTR DS : [Authn.LifeAddr1]/*[LifeAddr]*/
//		sar eax, 8
//		ret
//	}
//}
//
//DWORD __declspec(naked) GetMaxLife() {
//	__asm {
//		mov eax, 0x6FBCC3D0
//		mov eax, [eax]
//		push 0
//		push 7
//		push eax
//		call DWORD PTR DS : [Authn.LifeAddr1]/*[LifeAddr]*/
//		sar eax, 8
//		ret
//	}
//}
//DWORD __declspec(naked) GetCurrentMana() {
//	__asm {
//		mov eax, 0x6FBCC3D0
//		mov eax, [eax]
//		push 0
//		push 8
//		push eax
//		call DWORD PTR DS : [Authn.LifeAddr1]/*[LifeAddr]*/
//		sar eax, 8
//		ret
//	}
//}
//
//DWORD __declspec(naked) GetMaxMana() {
//	__asm {
//		mov eax, 0x6FBCC3D0
//		mov eax, [eax]
//		push 0
//		push 9
//		push eax
//		call DWORD PTR DS : [Authn.LifeAddr1]/*[LifeAddr]*/
//		sar eax, 8
//		ret
//	}
//}

void __fastcall NextGameNamePatch(Control* box, BOOL(__stdcall* FunCallBack)(Control*, DWORD, DWORD))
{
  D2WIN_SetControlText(box, wszGameName);
  D2WIN_SelectEditBoxText(box);
  D2WIN_SetEditBoxProc(box, FunCallBack);
}
void __fastcall NextGamePasswordPatch(Control* box, BOOL(__stdcall* FunCallBack)(Control*, DWORD, DWORD))
{
  D2WIN_SetControlText(box, wszGamePassword);
  D2WIN_SelectEditBoxText(box);
  D2WIN_SetEditBoxProc(box, FunCallBack);
}

DWORD __declspec(naked) __fastcall D2CLIENT_GetUIVar_STUB(DWORD varno)
{
  __asm
  {
    mov eax, ecx;
    jmp D2CLIENT_GetUiVar_I;
  }
}

//VOID __declspec(naked) GameShake1_STUB()
//{
//	__asm
//	{
//		//cmp v_NoShake, 0;
//		je OldCode;
//
//		add dword ptr[esp], 0xC;
//		ret;
//
//	OldCode:
//		mov[ecx], esi;
//		mov ecx, [esp + 0x1C];
//		ret;
//	}
//}

//VOID __stdcall GameShake(LPDWORD lpX, LPDWORD lpY)
//{
//	D2CLIENT_CalculateShake(lpX, lpY);
//
//	*p_D2CLIENT_xShake = 0;
//	*p_D2CLIENT_yShake = 0;
//}

VOID __declspec(naked) __fastcall D2COMMON_DisplayOverheadMsg_ASM(DWORD pUnit)
{
  __asm
  {
    LEA ESI, [ECX + 0xA4]
    MOV EAX, [ECX + 0xA4]

    PUSH EAX
    PUSH 0
    call D2COMMON_DisplayOverheadMsg_I

    RETN
  }
}

void __declspec(naked) __fastcall GameEndPatch_ASM()
{
  __asm {
    call GameEndPatch
    //original code
    mov ecx, 0xb4
    ret
  }
}

void __declspec(naked) GameLoopPatch_ASM()
{
  __asm
  {
    pushad;
    call GameLoopPatch;
    popad;

    push D2CLIENT_GameLoop;
    ret;
  }
}

void __declspec(naked) D2Login_ASM() {
  __asm {
    pushad
    call D2Login
    popad
    CALL DWORD PTR DS : [EAX + 0x8] //    bnclient.6FF3F5DC            ; bnclient.6FF2BDD0
    XOR ECX, ECX
    retn
  }
}

//void __declspec(naked) GameDrawPlayerBlob_STUB()
//{
//	__asm
//	{
//		mov ecx, esi;
//		call GameDrawPlayerBlobAndName;
//		mov cl, al;
//
//		ret;
//	}
//}
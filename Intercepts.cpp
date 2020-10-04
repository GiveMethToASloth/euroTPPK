#include "EuroTPPK.h"

//RosterUnit* FindPartyById1(DWORD dwUnitId)
//{
//	for (RosterUnit* pUnit = *p_D2CLIENT_PlayerUnitList; pUnit; pUnit = pUnit->pNext)
//		if (pUnit->dwUnitId == dwUnitId)
//			return pUnit;
//	_asm nop
//	_asm fnop
//	return NULL;
//}

//DWORD GetPvpFlags1(DWORD dwPlayerId)
//{
//	DWORD dwFlags1 = 0;
//	UnitAny* Me = (UnitAny*)D2CLIENT_GetPlayerUnit();
//	for (RosterUnit* pUnit = *p_D2CLIENT_PlayerUnitList; pUnit; pUnit = pUnit->pNext)
//	{
//		if (pUnit->dwUnitId != dwPlayerId)
//			continue;
//
//		if (pUnit->dwUnitId != Me->dwUnitId)
//		{
//			if (TestPvpFlag(dwPlayerId, Me->dwUnitId, 8))
//				dwFlags1 |= PVP_HOSTILED_YOU;
//
//			if (TestPvpFlag(Me->dwUnitId, dwPlayerId, 8))
//				dwFlags1 |= PVP_HOSTILED_BY_YOU;
//
//			if (pUnit->dwPartyFlags == 2)
//				dwFlags1 |= PVP_INVITED_YOU;
//
//			if (pUnit->dwPartyFlags == 4)
//				dwFlags1 |= PVP_INVITED_BY_YOU;
//
//			if (pUnit->wPartyId != 0xFFFF && pUnit->dwPartyFlags == 1)
//			{
//				RosterUnit* pMe = FindPartyById1(Me->dwUnitId);
//				if (pMe->wPartyId == 0xFFFF)
//					dwFlags1 |= PVP_ALLIED;
//				else if (pMe->wPartyId == pUnit->wPartyId)
//					dwFlags1 |= PVP_ALLIED;
//			}
//
//			return dwFlags1;
//		}
//	}
//
//	return dwFlags1;
//}

DWORD BreakItUp = 0x6F9B/*704B*/; // 704B+6FBF0000 6FBF704B 6FBF6F9B-6FBF0000
DWORD DontBreak = 0x6F9E/*704E*/; // 6FBF704E 0x704E+6FBF0000 6FBF6F9E-6FBF0000

void __declspec(naked) SendPacketIntercept_STUB() {
  __asm {
    pushad
    MOV ECX, DWORD PTR SS : [ESP + 0x30 - 4]
    MOV EDX, DWORD PTR SS : [ESP + 0x28 - 4]
    call SendPacket
    cmp eax, -1
    je Breakit
    popad
    test eax, eax
    je Breakit2

    jmp DontBreak

    retn

    Breakit :
    popad
      Breakit2 :
    xor eax, eax
      jmp BreakItUp
  }
}

void __declspec(naked) KeyHookIntercept_STUB() {
  __asm
  {
    mov cl, [edi + 0x08];
    mov dl, [edi + 0x0C + 3];
    and dl, 0x40;
    call KeyHook;
    test byte ptr[edi + 0x0C + 3], 0x40;
    ret;
  }
}

//void __declspec(naked) GameLightRadius_STUB()
//{
//	__asm
//	{
//		cmp esi, 1;
//		je OldCode;
//
//		mov eax, 0xFF
//			mov byte ptr[esp + 0x4], al;
//		mov byte ptr[esp + 0x4 + 1], al;
//		mov byte ptr[esp + 0x4 + 2], al;
//
//		add dword ptr[esp], 0x82;
//		ret;
//
//	OldCode:
//		mov byte ptr[esp + 0x4 + 1], 0;
//		ret;
//	}
//}

void __declspec(naked) GameDrawAutomapInfo_STUB()
{
  __asm
  {
    PUSHAD;
    CALL DrawAutomapInfos;
    POPAD;
    POP EDI;
    POP ESI;
    RET;
  }
}

/* GameDraw_STUB ()
 * Created By: Sheppard
 */
void __declspec(naked) GameDraw_STUB()
{
  __asm
  {
    call GameDraw;
    POP EBX;
    MOV ESP, EBP;
    POP EBP;
    ret
  }
}
//DWORD GetCommonBase() {
//	return (DWORD)LoadLibrary("D2Common.dll");
//}
//DWORD dwFlags1 = 0;
//int __fastcall PlayerMap(UnitAny* pUnit, DWORD color) {
//	if (pUnit)
//
//		dwFlags1 = GetPvpFlags1(pUnit->dwUnitId);
//
//	if (dwFlags1 & PVP_HOSTILED_BY_YOU || dwFlags1 & PVP_HOSTILED_YOU)
//		return 8;
//	if (dwFlags1 & PVP_ALLIED_WITH_YOU)
//		return 2;
//	//if(dwFlags1 & PVP_ALLIED)
//	//	return 1;
//	if (dwFlags1 & !PVP_ALLIED || dwFlags1 & !PVP_ALLIED_WITH_YOU)
//		return 0;
//
//	//	if(pUnit->dwUnitId==Auto.GetPlayerID() && !CheckPlayerFriend(Auto.GetPlayerNAME())) {
//	//		return 8;
//	//	}
//	//	else if(pUnit->pPlayerData && pUnit->dwUnitId!=GetPlayerID()) {
//	//	if(CheckPlayerFriend(pUnit->pPlayerData->szName)) {
//	//		return 3;
////}
//		//	return 3;
////}
//	return color;
//}
//void __declspec(naked) PlayerMapIntercept() {
//	__asm {
//		// Saving return address
//		pop edi
//		pushad
//		mov ecx, [esp + 0x20]
//		mov edx, [esp + 0x20 + 0xc]
//		Call PlayerMap
//		lea esi, [esp + 0x0c + 0x20]
//		mov[esi], eax // Overwriting Target Color .. :D
//		lea esi, [esp + 0x20 + 0x20]
//		mov[esi], 120
//		popad
//		call GetCommonBase
//		add eax, 0x56D80
//		call eax
//		push edi
//		retn
//	}
//}

//int GeneralColor;

//void __fastcall PlayerBlobHook(UnitAny* pUnit) {
//	if (pUnit != NULL)
//		if (pUnit->dwUnitId != GetPlayerID()) {
//			dwFlags1 = GetPvpFlags1(pUnit->dwUnitId);
//
//			if (dwFlags1 & PVP_HOSTILED_BY_YOU || dwFlags1 & PVP_HOSTILED_YOU)
//				GeneralColor = 8;
//			if (dwFlags1 & PVP_ALLIED_WITH_YOU)
//				GeneralColor = 2;
//			//if(dwFlags1 & PVP_ALLIED)
//			//	return 1;
//			if (dwFlags1 & !PVP_ALLIED || dwFlags1 & !PVP_ALLIED_WITH_YOU)
//				GeneralColor = 0;
//
//			/*if(Auto.GetPlayerID()==pUnit->dwUnitId && !CheckPlayerFriend(Auto.GetPlayerNAME()))
//					{
//						GeneralColor=11;
//						return;
//					}
//					else if(pUnit->pPlayerData && pUnit->dwUnitId!=GetPlayerID()) {
//						if(CheckPlayerFriend(pUnit->pPlayerData->szName)) {
//							GeneralColor=0x97;*/
//		}
//	return;
//	//}
////}
//
//	GeneralColor = *(BYTE*)0x6FBCC301/*0x6FBCC1A1*/;
//}
////}

//DWORD PlayerPatchJMP=0x6FB0CEC1; //0x6FACFFA1   6FB0CEC1
//DWORD CallOne=0x6FB0D5A0;//0x6FACBB10
//DWORD MoveOn=0x6FBCC1D8; //0x6FBCC3E0
//DWORD CSS;
//
//void __fastcall PlayPatchLeft(WORD X,WORD Y) {
//	if(AA && LeftAA) {
//	if(Auto.GetPlayerID()==GetPlayerID()) {
//		DWORD xY=Y;
//		DWORD xX=X;
//	__asm {
//		mov ecx, xX
//		mov edx, xY
//	}
//	 return;
//	}
//	DWORD mX=GetPlayerX(Auto.GetPlayerID());
//	DWORD mY=GetPlayerY(Auto.GetPlayerID());
//	if(v_AAType==3) {
//	mX=GetPlayerX(Auto.GetPlayerID());
//	mY=GetPlayerY(Auto.GetPlayerID());
//	mY=mY+4;
//	}
//	__asm {
//
//	mov ecx, mX
//	mov edx, mY
//	}
//	}
//	else if (CSS) {
//		__asm {
//		mov ecx, ecx
//		mov edx, edx
//		}
//	}
//}
//
//void __fastcall PlayPatch(WORD X,WORD Y) {
//	if(AA) {
//	if(Auto.GetPlayerID()==GetPlayerID() || GetDistance(GetPlayerX(GetPlayerID()),GetPlayerY(GetPlayerID()),GetPlayerX(Auto.GetPlayerID()),GetPlayerY(Auto.GetPlayerID()))>3000) {
//		DWORD xY=Y;
//		DWORD xX=X;
//	__asm {
//		mov ecx, xX
//		mov edx, xY
//	}
//	 return;
//	}
//	DWORD mX=GetPlayerX(Auto.GetPlayerID());
//	DWORD mY=GetPlayerY(Auto.GetPlayerID());
//	if(v_AAType==3) {
//	mX=GetPlayerX(Auto.GetPlayerID());
//	mY=GetPlayerY(Auto.GetPlayerID());
//	mY=mY+4;
//	}
//	__asm {
//	mov ecx, mX
//	mov edx, mY
//	}
//	}
//	else if (CSS) {
//		__asm {
//		mov ecx, ecx
//		mov edx, edx
//		}
//	}
//}
//void __declspec(naked) PlayerPatch() {
//	__asm {
//		MOV eax,DWORD PTR DS:[MoveOn]
//		mov [eax],1
//		call CallOne
//  //      jmp jumpout
//		mov eax,[CSS]
//		test eax,eax
//		jne ChangeAim
//		mov eax,[AA]
//		test eax,eax
//		je jumpout
//
//ChangeAim:
//		pushad
//
//		MOV ECX, DWORD PTR SS:[ESP+0x58]
//		MOV EDX, DWORD PTR SS:[ESP+0x5C]
//		MOV EBX, DWORD PTR SS:[ESP+0x54]
//		MOV EBP, DWORD PTR SS:[ESP+0x58+4+4]
//
//		MOV EAX,LeftAA
//		cmp eax, 1
//		je Left
//
//		cmp ebx, 0x03
//		je da
//
//		cmp ebx, 0x04
//		je da
//jmp weg
//da:
//		call PlayPatch
//		MOV DWORD PTR SS:[ESP+0x58],ECX
//		MOV DWORD PTR SS:[ESP+0x5C],EDX
//
//		jmp weg
//Left:
//
//		cmp ebp, 0x0C
//		jne weg
//
//		cmp ebx, 0x0
//		je keep
//
//		cmp ebx, 0x01
//		je keep
//
//
//
//		jmp weg
//keep:
//		call PlayPatch
//		MOV DWORD PTR SS:[ESP+0x58],ECX
//		MOV DWORD PTR SS:[ESP+0x5c],EDX
//weg:
//		popad
//jumpout:
//		jmp PlayerPatchJMP
//	}
//}
//
//
//void __declspec(naked) PlayerBlobIntercept() {
//	__asm {
//		pop edi
//		pushad
//		mov ecx, [esp+0x4+0x20]
//		call PlayerBlobHook
//		popad
//		mov cl, byte ptr [GeneralColor]
//		push edi
//		retn
//	}
//}

void __declspec(naked) GameFailToJoin_STUB()
{
  __asm
  {
    cmp esi, 4000;
    ret;
  }
}

// not used
/*
wchar_t *wcscpy2(wchar_t *dst, char *src)
{
wchar_t *res = dst;
while (*dst++ = (BYTE)*src++) ;
return res;
}

PartyPlayer * __stdcall D2CLIENT_GetNextPartyPlayer(PartyPlayer *pla)
{
__asm {
mov eax,[pla]
call [D2CLIENT_xGetNextPartyPlayer]
}
}
void __fastcall PlayerJoinMsgPatch(wchar_t *name, wchar_t **acc)
{
static wchar_t temp[128];
PartyPlayer *parpla = 0;
while (parpla = D2CLIENT_GetNextPartyPlayer(parpla)) {
  if (!wcscmp(name, wcscpy2(temp, parpla->name2))) break;
}
static wchar_t *typestrs[] = {L"Amazon", L"Sorceress", L"Necromancer", L"Paladin", L"Barbarian", L"Druid", L"Assassin"};
if (parpla) {
  wsprintfW(temp, L"%s, lvl %d %s", *acc, parpla->chrlvl, typestrs[parpla->chrtype]);
*acc = temp;
}
}
void __declspec(naked) PlayerJoinMsgPatch_ASM()
{
__asm {
mov ecx,[esp+4]
lea edx,[esp+8]
call PlayerJoinMsgPatch
// FCF,FCC,E37,E38,E39,E3A,E3C,E3D
mov ecx,0xE3B
ret
  }
}
*/

/*DWORD DrawCall=0x6FAC32C0-0x6FA80000;
void __declspec(naked)  DrawIntercept_STUB() {
  __asm {
    pushad // Saving to stack
    call DrawHook // calling my function
    popad // Poping it back
    call DrawCall
    RETN
    }
}
*/

void __declspec(naked) OnGamePacketReceived_STUB()
{
  __asm
  {
    pushad;

    call RecvPacket;
    test eax, eax;

    popad;
    jnz OldCode;

    mov edx, 0;

  OldCode:
    jmp D2NET_ReceivePacket_I;
  }
}
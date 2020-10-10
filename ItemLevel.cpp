#include "EuroTPPK.h"
#define INITVAB(l,n) l=l+(DWORD)LoadLibrary(n);

DWORD addr = 0xAC236/*76B66*/; // 76B66+6FAB0000=6FB26B66 ||6FB5C236-6FAB0000
byte Backup[6];
bool BackUped = false;
bool ItemLevel = false;

wchar_t* __cdecl wsprintfW2(wchar_t* dest, char* fmt, ...)
{
  va_list va;
  va_start(va, fmt);
  int len = wvsprintf((char*)dest, fmt, va);
  for (int i = len; i >= 0; i--) {
    dest[i] = ((char*)dest)[i];
  }
  return dest;
}

wchar_t* __fastcall ColourD2String(wchar_t* str, DWORD col)
{
  memmove(str + 3, str, (wcslen(str) + 1) * sizeof(wchar_t));
  str[0] = 0xff;
  str[1] = 'c';
  str[2] = '0' + (int)col;
  return str;
}

void __fastcall ItemNamePatch(wchar_t* name, UnitAny* item)
{
  wchar_t Buffer[100] = { 0 };
  wsprintfW2(Buffer, " [%d]", item->pItemData->dwItemLevel);
  wcscat(name, Buffer);
  if (Units) {
    UnitAny* pPlayer = D2CLIENT_GetPlayerUnit();
    UnitAny* p = D2COMMON_GetItemFromInventory(pPlayer->pInventory);
    ItemTxt* pTxt = D2COMMON_GetItemText(p->dwTxtFileNo);
    if (pTxt) {
      char szCode[4];
      strncpy(szCode, pTxt->szCode, 3);
      szCode[3] = '\0';
      if (!_strcmpi(szCode, "rvl"))
        wchar_t Buffer[100] = { 0 };
      wchar_t PreBuffer[100] = { 0 };
      //wsprintfW2(Buffer,"(X)");
      //wcscat(name,Buffer);
      ColourD2String(name, FONTCOLOR_PURPLE);
    }
  }

  int nSockets = D2COMMON_GetUnitStat(item, 194, 0);
  if (nSockets > 0 && (v_ItemSockets))
  {
    wchar_t Buffer[100] = { 0 };
    wsprintfW2(Buffer, "(%i)", nSockets);
    wcscat(name, Buffer);
  }
  if (item->pItemData->dwFlags & 0x400000 && (v_ItemEthPrefix))
  {
    wchar_t Buffer[100];
    wsprintfW2(Buffer, "(Eth)");
  }

  // item level

//		wsprintfW((name+wcslen(name)), " (%ld)", item->pItemData->nItemLevel);
}

void __declspec(naked) ItemNamePatch_ASM()
{
  __asm {
    //ebx = ptr unit item
    //edi = ptr item name string
    mov ecx, edi
    mov edx, ebx
    call ItemNamePatch
    mov al, [ebp + 0x12a]
    ret
  }
}

void InstallItemlvl() {
  if (!BackUped) {
    INITVAB(addr, "d2client.dll")
      WriteBytes(&Backup, (void*)addr, 6); BackUped = true;
  }
  PatchCall(addr, (DWORD)ItemNamePatch_ASM, 6);
}

void UninstallItemlvl() {
  if (BackUped) {
    WriteBytes((void*)addr, &Backup, 6);
  }
}
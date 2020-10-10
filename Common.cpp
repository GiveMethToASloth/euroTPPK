#include "EuroTPPK.h"

//PrintMessage Command
void PrintMessage(bool bBottom, int nColor, char* szText, ...)
{
  char szStr[0x200];
  va_list vaArgs;
  va_start(vaArgs, szText);
  vsprintf_s(szStr, 0x200, szText, vaArgs);
  va_end(vaArgs);
  wchar_t* wzBuffer = AnsiToUnicode(szStr);
  bBottom ? D2CLIENT_PrintPartyString(wzBuffer, nColor) : D2CLIENT_PrintGameString(wzBuffer, nColor);
};

void PrintChat(char* Message) {
  byte CharPacket[100] = {};
  sprintf((char*)CharPacket, "%c%c%c%s%c%c%c", 0x15, 0x01, 0x00, Message, 0x00, 0x00, 0x00);
  SendGAMEPacket(CharPacket, strlen(Message) + 6);
}

bool Say(char* lpMessage, ...)
{
  char szBuffer[0x400] = "";
  va_list Args;

  if (!GameReady())
    return false;

  va_start(Args, lpMessage);
  vsprintf(szBuffer, lpMessage, Args);
  va_end(Args);

  BYTE* aPacket = new BYTE[(int)strlen(szBuffer) + 6];
  memset(aPacket, 0, (int)strlen(szBuffer) + 6);

  aPacket[0] = 0x15;
  *(WORD*)&aPacket[1] = 1;
  memcpy(aPacket + 3, szBuffer, (int)strlen(szBuffer));

  D2NET_SendPacket((int)strlen(szBuffer) + 6, 1, aPacket);
  delete[] aPacket;

  return true;
}

bool SayOverHead(char* lpMessage, ...)
{
  char szBuffer[0x400] = "";
  va_list Args;

  if (!GameReady())
    return false;

  va_start(Args, lpMessage);
  vsprintf(szBuffer, lpMessage, Args);
  va_end(Args);

  if (lpMessage && lpMessage[0])
  {
    UnitAny* pUnit = D2CLIENT_GetPlayerUnit();
    OverheadMsg* pMsg = D2COMMON_GenerateOverheadMsg(NULL, lpMessage, *p_D2CLIENT_OverheadTrigger);
    if (pMsg)
    {
      D2COMMON_FixOverheadMsg(pMsg, NULL);
      pUnit->pOMsg = pMsg;
    }
  }
  return true;
}

char* mitoa(int integer) {
  char Buffer[100] = { 0 };
  sprintf_s(Buffer, "%d", integer);
  return Buffer;
}

wchar_t* AnsiToUnicode(const char* szStr) {
  wchar_t* wzBuf = nullptr;
  int nLen = MultiByteToWideChar(CP_ACP, 0, szStr, -1, wzBuf, 0);
  wzBuf = new wchar_t[nLen];
  MultiByteToWideChar(CP_ACP, 0, szStr, -1, wzBuf, nLen);
  return wzBuf;
}

char* UnicodeToAnsi(const wchar_t* wzStr)
{
  char* buf = NULL;
  int len = WideCharToMultiByte(CP_ACP, 0, wzStr, -1, buf, 0, "?", NULL);
  buf = new char[len];
  WideCharToMultiByte(CP_ACP, 0, wzStr, -1, buf, len, "?", NULL);
  return buf;
}

char* ReplaceString(char* source, char* old, char* newtext) {
  char* original = new char[strlen(source)];
  strcpy(original, source);
  char* temp = new char[256];
  int old_length = strlen(old);
  int i, j, k, location = -1;
  for (i = 0; source[i] && (location == -1); ++i)
    for (j = i, k = 0; source[j] == old[k]; j++, k++)
      if (!old[k + 1])
        location = i;
  if (location != -1) {
    for (j = 0; j < location; j++)
      temp[j] = source[j];
    for (i = 0; newtext[i]; i++, j++)
      temp[j] = newtext[i];
    for (k = location + old_length; source[k]; k++, j++)
      temp[j] = source[k];
    temp[j] = NULL;
    for (i = 0; source[i] = temp[i]; i++);
  }
  delete[] original;
  return temp;
}

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
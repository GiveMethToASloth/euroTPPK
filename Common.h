#pragma once

void PrintMessage(bool bBottom, int nColor, char* szText, ...);
void PrintChat(char* Message);
bool Say(char* lpMessage, ...);
bool SayOverHead(char* lpMessage, ...);
char* mitoa(int integer);
wchar_t* AnsiToUnicode(const char* szStr);
char* UnicodeToAnsi(const wchar_t* wzStr);
char* ReplaceString(char* source, char* old, char* newtext);
wchar_t* __cdecl wsprintfW2(wchar_t* dest, char* fmt, ...);
wchar_t* __fastcall ColourD2String(wchar_t* str, DWORD col);
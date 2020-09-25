#include "EuroTPPK.h"

void wcscpy2(wchar_t *dest, char *src)
{
	do { *dest++ = *src; }while(*src++);
}wchar_t wszGameName[32];
wchar_t wszGamePassword[32];
void SaveGameName()
{
	GameStructInfo *gi = GetGameInfo();
	if(*gi->szGameName) {
		wcscpy2(wszGameName, gi->szGameName);
		wcscpy2(wszGamePassword, gi->szGamePassword);
	}
}
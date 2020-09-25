#ifndef _SETTINGS_H
#define _SETTINGS_H

typedef struct ConfigVar_t
{
	LPSTR VarName[3];
	LPVOID Buffers[10];
} CONFIGVAR, *PCONFIGVAR;


typedef struct DefineVar_t
{
	LPSTR Name;
	LPSTR StringReplace;
} DEFINEVAR, *PDEFINEVAR;

typedef struct ConsoleMessage_t
{
	LPWSTR Message;
	DWORD TimeStamp;
} CONSOLEMESSAGE, *PCONSOLEMESSAGE;

BOOL ReadConfigFile();
BOOL ReadDefinesFile(CArrayEx<PDEFINEVAR, PDEFINEVAR> *pDefines, INT nSize);
BOOL ReplaceDefineVars(LPSTR lpString, CArrayEx<PDEFINEVAR, PDEFINEVAR> *pDefines);

#endif
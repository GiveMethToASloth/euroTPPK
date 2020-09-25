#include "EuroTPPK.h"

BOOL ReadBPConfig()
{	
	CHAR lpSectionNames[8192] = { NULL };
	CHAR szPath[MAX_PATH] = { NULL };

	GetModuleFileName((HMODULE)Global.hDll, szPath, MAX_PATH);
	*(strrchr(szPath,'\\')+1) = NULL;
	strcat(szPath,"BPManager.ini");

	GetPrivateProfileSectionNames(lpSectionNames, sizeof(lpSectionNames), szPath);

	for(CHAR* pSection = lpSectionNames; *pSection; pSection = pSection + strlen(pSection) + 1)
	{
		CHAR lpSectionEntrys[8192] = {NULL};
		GetPrivateProfileSection(pSection, lpSectionEntrys, sizeof(lpSectionEntrys), szPath);

		if(strrchr(pSection, ' ') && strrchr(pSection, ' ') - pSection)
		{

			CHAR szCharacter[64] = {NULL};
			DWORD dwCharLen = (DWORD)strrchr(pSection, ' ') - (DWORD)pSection;
			memcpy(szCharacter, pSection, dwCharLen);
			
			DWORD dwClassId = GetClassIdFromName(szCharacter);
			DWORD dwStatId	= atoi(strstr(pSection," ")+1);

			if(dwClassId != -1 && dwStatId)
			{
				for(CHAR* pEntry = lpSectionEntrys; *pEntry; pEntry = pEntry + strlen(pEntry) + 1)
				{
					if(strrchr(pEntry, '=') && strrchr(pEntry, '-') && strrchr(pEntry, '=') - pEntry)
					{
						CHAR szEntry[64] = { NULL };
						DWORD dwLen = strrchr(pEntry, '=') - pEntry;
						memcpy(szEntry, pEntry, dwLen);

						CHAR lpEntry[8192] = {NULL};
						GetPrivateProfileString(pSection, szEntry, "-", lpEntry, sizeof(lpEntry), szPath);
						
						if(*lpEntry)
						{
							DWORD dwMin = NULL;
							DWORD dwMax = NULL;
							DWORD dwNew = NULL;

							CHAR szBuffer[8192] = {NULL};
							memcpy(szBuffer, pEntry, strrchr(pEntry,'-') - pEntry);

							dwMin = atoi(szBuffer);

							memset(szBuffer, NULL, sizeof(szBuffer));
							memcpy(szBuffer, pEntry + (strrchr(pEntry,'-') - pEntry) + 1, strrchr(pEntry, '=') - strrchr(pEntry, '-'));

							dwMax = atoi(szBuffer);
							dwNew = atoi(lpEntry);

							if(dwMin >= dwMax)
							{
								CHAR szError[1024] = {NULL};
								sprintf(szError,"Error while parsing Min and Max Value!\nMin is higher or equal to Max!\nSection: %s\nEntry: %s",pSection, pEntry);
								MessageBox(NULL, szError, "Entry Error", MB_ICONWARNING);
								continue;
							}
														
							Configuration* pConfig = new Configuration;
							pConfig->dwClassId	= dwClassId;
							pConfig->dwStat		= dwStatId;
							pConfig->dwMin		= dwMin;
							pConfig->dwMax		= dwMax;
							pConfig->dwNew		= dwNew;

							Global.Cfg.Add(pConfig);
						}
					}
					else
					{
						CHAR szError[1024] = {NULL};
						sprintf(szError,"Error while parsing Entry: %s\nSection: %s", pEntry, pSection);
						MessageBox(NULL, szError, "Entry Error", MB_ICONWARNING);
					}
				}
			}
			else
			{
				CHAR szError[1024] = {NULL};
				sprintf(szError,"Error while parsing Section: %s", pSection);
				MessageBox(NULL, szError, "Section Error", MB_ICONWARNING);
			}
		}
	}

	if(Global.Cfg.IsEmpty())
		return FALSE;

	return TRUE;
}
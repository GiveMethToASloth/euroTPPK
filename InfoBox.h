#ifndef INFOBOX_H
#define INFOBOX_H

struct InfoBox {
	char* Message;
	char* Data;
};
struct AutomapInfo
{
	char* Message;
	char* Data;
};
extern void		DrawOriginal(void);
extern bool		ToggleInfo;
extern			DWORD nGameTimer;


#endif
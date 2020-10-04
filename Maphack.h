#ifndef _MAPFUNC_H
#define _MAPFUNC_H

bool RevealAct();
bool GameReady(void);
bool RevealLevel(Level* pLevel);

AutomapLayer* InitAutomapLayer(DWORD levelno);
AutomapLayer* __fastcall D2CLIENT_InitAutomapLayer_STUB(DWORD nLayerNo);

void DrawPresets(Room2* pRoom2);

#endif

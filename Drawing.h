#pragma once

extern void __fastcall D2DrawRectFrameWrap(RECT* pRect);
extern void D2DrawRectFrame(int x, int y, int x2, int y2);
extern void BoxHook(int x, int y, int xSize, int ySize, DWORD dwColor, DWORD dwTrans, bool bAutomap);
extern void TextHook(int xPos, int yPos, DWORD dwColor, bool bAutomap, int dwFont, int dwCenter, std::string szText, ...);
extern void DrawTextToScreen(char* szwText, int x, int y, int color, int font);
extern void D2DrawLine(int x, int y, int x2, int y2, DWORD color);
extern void DrawCross(int nX, int nY, DWORD dwColor, bool bAutomap);
extern void DrawPlayerBlob(int xpos, int ypos, int col);
extern void DrawBlob(int xpos, int ypos, int col);
extern POINT GetTextSize(std::string szStr, unsigned int nFont);
extern void AutomapToScreen(POINT* ptPos, int xpos, int ypos);
extern void AutomapToScreenRelative(POINT* pos, int x, int y);
extern void MapToScreenCoords(POINT& rMapPosition);
extern void ScreenToAutomap(POINT* ptPos, int x, int y);
extern void ScreenToAutomapRelative(POINT* pos, int x, int y);
extern void AbsToScreenCoords(POINT& rMapPosition);
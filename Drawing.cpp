#include "EuroTPPK.h"

void __declspec(naked) __fastcall D2DrawRectFrameWrap(RECT* pRect) {
  __asm {
    mov eax, ecx
    call D2CLIENT_DrawRectFrame
    ret
  }
}

void D2DrawRectFrame(int x, int y, int x2, int y2) {
  RECT Frame;
  Frame.left = x;
  Frame.top = y;
  Frame.right = x2;
  Frame.bottom = y2;
  D2DrawRectFrameWrap(&Frame);
}

void BoxHook(int x, int y, int xSize, int ySize, DWORD dwColor, DWORD dwTrans, bool bAutomap)
{
  POINT Start = { x, y };
  POINT End = { xSize, ySize };
  if (bAutomap)
  {
    if (!p_D2CLIENT_AutomapOn)
      return;
    ScreenToAutomap(&Start, x * 32, y * 32);
  }

  return D2GFX_DrawRectangle(Start.x, Start.y, End.x + Start.x, End.y + Start.y, dwColor, dwTrans);
}

void TextHook(int xPos, int yPos, DWORD dwColor, bool bAutomap, int dwFont, int dwCenter, std::string szText, ...) {
  //Setup a point variable
  POINT nPos = { xPos, yPos };
  DWORD dwOldSize, wWidth, dwFileNo;

  //Check if we are drawing this on Automap
  if (bAutomap)
  {
    if (!p_D2CLIENT_AutomapOn)
      return;
    ScreenToAutomap(&nPos, xPos * 32, yPos * 32);
  }

  CHAR szBuffer[800] = "";
  va_list Args;
  va_start(Args, szText);
  vsprintf_s(szBuffer, szText.c_str(), Args);
  va_end(Args);

  wchar_t* wBuffer = AnsiToUnicode(szBuffer);

  dwOldSize = D2WIN_SetTextSize(dwFont);
  if (dwCenter != -1)
  {
    D2WIN_GetTextWidthFileNo(wBuffer, &wWidth, &dwFileNo);
    nPos.x -= (wWidth >> dwCenter);
  }

  D2WIN_DrawText(wBuffer, nPos.x, nPos.y, dwColor, -1);
  D2WIN_SetTextSize(dwOldSize);
}

//Draw Text To Screen Permanent
void DrawTextToScreen(char* szwText, int x, int y, int color, int font) {
  wchar_t Buffer[100];

  MultiByteToWideChar(0, 1, szwText, 50, Buffer, 100);
  DWORD dwOld = D2WIN_SetTextSize(font);
  //DWORD dwXLength = D2WIN_GetTextLength(Buffer);
  D2WIN_DrawText(Buffer, x, y, color, 0);
  D2WIN_SetTextSize(dwOld);
}

void D2DrawLine(int x, int y, int x2, int y2, DWORD color) {
  D2GFX_DrawLine(x, y, x2, y2, color, 0xff);
}

void DrawCross(int nX, int nY, DWORD dwColor, bool bAutomap) {
  POINT nPos = { nX, nY };
  if (bAutomap) {
    if (!p_D2CLIENT_AutomapOn)
      return;
    ScreenToAutomap(&nPos, nX * 32, nY * 32);
  }

  char szLines[][2] = { 0,-2, 4,-4, 8,-2, 4,0, 8,2, 4,4, 0,2, -4,4, -8,2, -4,0, -8,-2, -4,-4, 0,-2 };
  for (int i = 0; i < ArraySize(szLines) - 1; i++) {
    D2GFX_DrawLine(nPos.x + szLines[i][0], nPos.y + szLines[i][1], nPos.x + szLines[i + 1][0], nPos.y + szLines[i + 1][1], dwColor, -1);
  }
}

void DrawPlayerBlob(int xpos, int ypos, int col) {
  DrawBlob(xpos, ypos, col);
  POINT Player = { D2CLIENT_GetPlayerUnit()->pPath->xPos, D2CLIENT_GetPlayerUnit()->pPath->yPos };
  MapToScreenCoords(Player);
  ScreenToAutomapRelative(&Player, Player.x, Player.y);
  D2GFX_DrawLine(Player.x, Player.y, xpos, ypos, col, 0xff);
}

void DrawBlob(int xpos, int ypos, int col) {
  static char blines[][2] = { 0,-2, 4,-4, 8,-2, 4,0, 8,2, 4,4, 0,2, -4,4, -8,2, -4,0, -8,-2, -4,-4, 0,-2 };
  for (int i = 0; i < ArraySize(blines) - 1; i++) {
    D2GFX_DrawLine(xpos + blines[i][0], ypos + blines[i][1], xpos + blines[i + 1][0], ypos + blines[i + 1][1], col, 0xff);
  }
}

POINT GetTextSize(std::string szStr, unsigned int nFont) {
  DWORD dwWidth = NULL;
  DWORD dwHeight = NULL;
  DWORD dwFileNo = NULL;
  POINT ptSiz{ 0, 0 };
  wchar_t* wzStr = AnsiToUnicode(szStr.c_str());
  DWORD dwOldFnt = D2WIN_SetTextSize(nFont);
  D2WIN_GetTextWidthFileNo(wzStr, &dwWidth, &dwFileNo);
  dwHeight = DWORD(D2WIN_GetTextHeight());
  D2WIN_SetTextSize(dwOldFnt);
  ptSiz = { LONG(dwWidth), LONG(dwHeight) };
  delete[] wzStr;
  return ptSiz;
}

void AutomapToScreen(POINT* ptPos, int xpos, int ypos) {
  if (D2CLIENT_GetAutomapSize()) {
    xpos += 1;
    ypos -= 5;
  }
  xpos = (xpos + (*p_D2CLIENT_Offset).x + 8) * (*(INT*)p_D2CLIENT_Divisor);
  ypos = (ypos + (*p_D2CLIENT_Offset).y - 8) * (*(INT*)p_D2CLIENT_Divisor);
  int xpos2 = ((ypos * 2) + xpos) / 32;
  int ypos2 = ((ypos * 2) - xpos) / 32;
}

void AutomapToScreenRelative(POINT* pos, int x, int y) {
  x += D2CLIENT_GetMouseXOffset();
  y += D2CLIENT_GetMouseYOffset();
  AutomapToScreen(pos, y * 2 + x, y * 2 - x);
}

void MapToScreenCoords(POINT& rMapPosition) {
  D2COMMON_MapToAbsScreen(&rMapPosition.x, &rMapPosition.y);
  rMapPosition.x -= D2CLIENT_GetMouseXOffset();
  rMapPosition.y -= D2CLIENT_GetMouseYOffset();
}

void ScreenToAutomap(POINT* ptPos, int x, int y) {
  ptPos->x = ((x - y) / 2 / (*(INT*)p_D2CLIENT_Divisor)) - (*p_D2CLIENT_Offset).x + 8;
  ptPos->y = ((x + y) / 4 / (*(INT*)p_D2CLIENT_Divisor)) - (*p_D2CLIENT_Offset).y - 8;
  if (D2CLIENT_GetAutomapSize()) {
    --ptPos->x;
    ptPos->y += 5;
  }
}

void ScreenToAutomapRelative(POINT* pos, int x, int y) {
  x += D2CLIENT_GetMouseXOffset();
  y += D2CLIENT_GetMouseYOffset();
  ScreenToAutomap(pos, y * 2 + x, y * 2 - x);
}

void AbsToScreenCoords(POINT& rMapPosition) {
  D2COMMON_AbsScreenToMap(&rMapPosition.x, &rMapPosition.y);
  rMapPosition.x -= D2CLIENT_GetMouseXOffset();
  rMapPosition.y -= D2CLIENT_GetMouseYOffset();
}
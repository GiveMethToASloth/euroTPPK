#include "EuroTPPK.h"

bool ExpBoxMoved = false;
bool MooExp = false;
bool Moved1Exp = false;
POINT ExpBoxPoint;

char* ConvertIntegers(int in) {
  char Buffer[60] = { 0 };
  char Buffer2[100];
  sprintf(Buffer, "%d", in);

  switch (strlen(Buffer)) {
  case 1:
    sprintf(Buffer2, "%c", Buffer[0]);
    break;
  case 2:
    sprintf(Buffer2, "%c%c", Buffer[0], Buffer[1]);
    break;
  case 3:
    sprintf(Buffer2, "%c%c%c", Buffer[0], Buffer[1], Buffer[2]);
    break;
  case 4:
    sprintf(Buffer2, "%c,%c%c%c", Buffer[0], Buffer[1], Buffer[2], Buffer[3]);
    break;
  case 5:
    sprintf(Buffer2, "%c%c,%c%c%c", Buffer[0], Buffer[1], Buffer[2], Buffer[3], Buffer[4]);
    break;
  case 6:
    sprintf(Buffer2, "%c%c%c,%c%c%c", Buffer[0], Buffer[1], Buffer[2], Buffer[3], Buffer[4], Buffer[5]);
    break;
  case 7:
    sprintf(Buffer2, "%c,%c%c%c,%c%c%c", Buffer[0], Buffer[1], Buffer[2], Buffer[3], Buffer[4], Buffer[5], Buffer[6]);
    break;
  case 8:
    sprintf(Buffer2, "%c%c,%c%c%c,%c%c%c", Buffer[0], Buffer[1], Buffer[2], Buffer[3], Buffer[4], Buffer[5], Buffer[6], Buffer[7]);
    break;
  case 9:
    sprintf(Buffer2, "%c%c%c,%c%c%c,%c%c%c", Buffer[0], Buffer[1], Buffer[2], Buffer[3], Buffer[4], Buffer[5], Buffer[6], Buffer[7], Buffer[8]);
    break;
  case 10:
    sprintf(Buffer2, "%c,%c%c%c,%c%c%c,%c%c%c", Buffer[0], Buffer[1], Buffer[2], Buffer[3], Buffer[4], Buffer[5], Buffer[6], Buffer[7], Buffer[8], Buffer[9]);
    break;
  default:
    break;
  }
  return Buffer2;
}

void ExpBox(void) {
  UnitAny* pUnit = D2CLIENT_GetPlayerUnit();
  if (!pUnit) return;
  DWORD dwLevel = D2COMMON_GetUnitStat(pUnit, 12, 0);
  DWORD dwExp = D2COMMON_GetUnitStat(pUnit, 13, 0);
  DWORD dwMaxExp = DWORD(D2COMMON_GetExpToAchiveLvl(1, int(dwLevel)));
  DWORD dwExpLastLvl = DWORD(D2COMMON_GetExpToAchiveLvl(1, int(dwLevel - 1)));
  DWORD dwExpRemain = DWORD(D2COMMON_GetExpToAchiveLvl(1, dwLevel)) - dwExp;
  DWORD dwExpPercent = DWORD(abs((double(dwExp - dwExpLastLvl) / double(dwMaxExp - dwExpLastLvl)) * 100.0));
  DWORD dwGainedExp = dwExp - dwCurrentExp;
  DWORD dwGamesRemain = 0;

  char szExpPercent[50];
  sprintf_s(szExpPercent, "%d", dwExpPercent);

  char szGainedExp[200];
  sprintf(szGainedExp, "%s", ConvertIntegers(dwGainedExp));

  char szGamesLeft[200];
  if (dwMaxExp != NULL && dwGainedExp != NULL) dwGamesRemain = dwMaxExp / dwGainedExp;
  if (dwCurrentExp != 0) sprintf_s(szGamesLeft, 200, "%d", dwGamesRemain);

  char szExpRemaining[20];
  sprintf(szExpRemaining, "%s", ConvertIntegers(dwExpRemain));

  char Buf[512];
  if (!D2CLIENT_GetUiVar(0x01))
    if (!D2CLIENT_GetUiVar(0x1a))
      if (!D2CLIENT_GetUiVar(0x19))
        if (!D2CLIENT_GetUiVar(0x02))
          //if(!D2CLIENT_GetUiVar(0x18))
          if (LevelBox) {
            char Buf[200];
            int x, x1, y, y2, xstar, xstar2, ystar, ystar2, xs, x1s, ys, y1s, y2s;
            //	x=650;
            //	y=410;
            xstar = 645;  // 95 lång
            xstar2 = 740; //

            ystar = 330; // 50 hög 325
            ystar2 = 390; // 375

            if (!Moo)
              if (!MooTarget)
                if (!Moved1Exp)
                  if (!MooPre)
                    if (!MooWinAmp)
                      if (!MooInfoTarget)
                        if (D2CLIENT_MouseX >= xstar && D2CLIENT_MouseX <= xstar2) {
                          if (D2CLIENT_MouseY >= ystar && D2CLIENT_MouseY <= ystar2 - 13) {
                            if (KEYDOWN(vK_BoxKey)) {
                              ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
                              if (KEYDOWN(MK_LBUTTON)) {
                                ExpBoxMoved = true;
                              }
                            }
                          }
                        }

            int fontNew = 0;
            // FOR THE CROSS
            if (!Moved1Exp)
              if (!MooTarget)
                if (!Moo)
                  if (!MooPre)
                    if (!MooWinAmp)
                      if (!MooInfoTarget)
                        if (D2CLIENT_MouseX >= xstar2 - 10 && D2CLIENT_MouseX <= xstar2) {
                          if (D2CLIENT_MouseY >= ystar && D2CLIENT_MouseY <= ystar + 13) {
                            fontNew = 5;
                            ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
                            //	if(KEYDOWN(vK_BoxKey)) {
                            if (KEYDOWN(MK_LBUTTON)) {
                              LevelBox = false;
                              ExpBoxMoved = false;
                              Moved1Exp = false;
                              //}
                            }
                          }
                        }

            if (!ExpBoxMoved) // draw first box.
            {
              D2GFX_DrawRectangle(xstar, ystar, xstar2, ystar2, 0, 1);
              D2DrawRectFrame(xstar, ystar, xstar2, ystar2);
              // DOT
              DrawTextToScreen("X", xstar2 - 10, ystar + 13, fontNew, 6);

              if (!Moved1Exp) {
                DrawTextToScreen("Experience", xstar + 5, ystar + 12, FONTCOLOR_GOLD, 6);
                y = ystar + 14;
                x = xstar + 5;
                x1 = xstar + 22;
                y += 10;
                sprintf(Buf, "Total: %s%%", szExpPercent);
                DrawTextToScreen(Buf, x, y, FONTCOLOR_WHITE, 6);
                y += 10;
                sprintf(Buf, "Gained: %s", szGainedExp);
                DrawTextToScreen(Buf, x, y, FONTCOLOR_WHITE, 6);
                y += 10;
                sprintf(Buf, "Left: %s", szExpRemaining);
                DrawTextToScreen(Buf, x, y, FONTCOLOR_WHITE, 6);
                y += 10;
                sprintf(Buf, "Games: %s", szGamesLeft);
                DrawTextToScreen(Buf, x, y, FONTCOLOR_WHITE, 6);
              }
            }

            if (ExpBoxMoved) {
              if (!Moved1Exp)
                if (!MooWinAmp)
                  if (!MooInfoTarget)
                    if (D2CLIENT_MouseX >= xstar && D2CLIENT_MouseX <= xstar2) {
                      if (D2CLIENT_MouseY >= ystar && D2CLIENT_MouseY <= ystar2) {
                        if (KEYDOWN(vK_BoxKey)) {
                          ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
                          if (KEYDOWN(MK_LBUTTON)) {
                            MooExp = true;
                            Moved1Exp = true;
                          }
                        }
                      }
                    }
              if (!Moo)
                if (!MooPre)
                  if (!MooTarget)
                    if (Moved1Exp)
                      if (!MooWinAmp)
                        if (!MooInfoTarget)
                          if (D2CLIENT_MouseX >= ExpBoxPoint.x && D2CLIENT_MouseX <= ExpBoxPoint.x + 95) {
                            if (D2CLIENT_MouseY >= ExpBoxPoint.y && D2CLIENT_MouseY <= ExpBoxPoint.y + 50) {
                              if (KEYDOWN(vK_BoxKey)) {
                                ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
                                if (KEYDOWN(MK_LBUTTON)) {
                                  MooExp = true;
                                }
                              }
                            }
                          }

              //CROSS STARt
              if (ExpBoxMoved) {
                if (!MooPre)
                  if (!Moo)
                    if (!MooTarget)
                      if (!MooExp)
                        if (!MooWinAmp)
                          if (!MooInfoTarget)
                            //	if(Moved1Exp)*/
                            if (D2CLIENT_MouseX >= ExpBoxPoint.x + 85 && D2CLIENT_MouseX <= ExpBoxPoint.x + 95) {
                              if (D2CLIENT_MouseY >= ExpBoxPoint.y && D2CLIENT_MouseY <= ExpBoxPoint.y + 15) {
                                fontNew = 5;
                                ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
                                //	if(KEYDOWN(vK_BoxKey))  {
                                if (KEYDOWN(MK_LBUTTON)) {
                                  LevelBox = false;
                                  ExpBoxMoved = false;
                                  Moved1Exp = false;
                                }//}
                              }
                            }
              }// CROSS END

              if (MooExp) {
                if (!MooPre) {
                  if (!Moo) {
                    if (!MooWinAmp) {
                      if (!MooTarget) {
                        if (!MooInfoTarget) {
                          if (KEYDOWN(vK_BoxKey)) {
                            ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
                            while (KEYDOWN(MK_LBUTTON)) {
                              GetD2MousePos(ExpBoxPoint);
                              D2GFX_DrawRectangle(ExpBoxPoint.x, ExpBoxPoint.y, ExpBoxPoint.x + 95, ExpBoxPoint.y + 60, 0, 1);
                              D2DrawRectFrame(ExpBoxPoint.x, ExpBoxPoint.y, ExpBoxPoint.x + 95, ExpBoxPoint.y + 60);

                              DrawTextToScreen("X", ExpBoxPoint.x + 85, ExpBoxPoint.y + 13, fontNew, 6);

                              y = ExpBoxPoint.y + 15;

                              DrawTextToScreen("Experience", ExpBoxPoint.x + 5, y - 3, FONTCOLOR_GOLD, 6);

                              y = ExpBoxPoint.y + 14;
                              x = ExpBoxPoint.x + 5;
                              y += 10;
                              sprintf(Buf, "Total: %s%%", szExpPercent);
                              DrawTextToScreen(Buf, x, y, FONTCOLOR_WHITE, 6);
                              y += 10;
                              sprintf(Buf, "Gained: %s", szGainedExp);
                              DrawTextToScreen(Buf, x, y, FONTCOLOR_WHITE, 6);
                              y += 10;
                              sprintf(Buf, "Left: %s", szExpRemaining);
                              DrawTextToScreen(Buf, x, y, FONTCOLOR_WHITE, 6);
                              y += 10;
                              sprintf(Buf, "Games: %s", szGamesLeft);
                              DrawTextToScreen(Buf, x, y, FONTCOLOR_WHITE, 6);
                              return;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }

              MooExp = false;
              D2GFX_DrawRectangle(ExpBoxPoint.x, ExpBoxPoint.y, ExpBoxPoint.x + 95, ExpBoxPoint.y + 60, 0, 1);
              D2DrawRectFrame(ExpBoxPoint.x, ExpBoxPoint.y, ExpBoxPoint.x + 95, ExpBoxPoint.y + 60);

              DrawTextToScreen("X", ExpBoxPoint.x + 85, ExpBoxPoint.y + 13, fontNew, 6);

              y = ExpBoxPoint.y + 15;

              DrawTextToScreen("Experience", ExpBoxPoint.x + 5, y - 3, FONTCOLOR_GOLD, 6);

              y = ExpBoxPoint.y + 14;
              x = ExpBoxPoint.x + 5;

              y += 10;

              sprintf(Buf, "Total: %s%%", szExpPercent);
              DrawTextToScreen(Buf, x, y, FONTCOLOR_WHITE, 6);
              y += 10;
              sprintf(Buf, "Gained: %s", szGainedExp);
              DrawTextToScreen(Buf, x, y, FONTCOLOR_WHITE, 6);
              y += 10;
              sprintf(Buf, "Left: %s", szExpRemaining);
              DrawTextToScreen(Buf, x, y, FONTCOLOR_WHITE, 6);
              y += 10;
              sprintf(Buf, "Games: %s", szGamesLeft);
              DrawTextToScreen(Buf, x, y, FONTCOLOR_WHITE, 6);
            }
          }
  return;
}
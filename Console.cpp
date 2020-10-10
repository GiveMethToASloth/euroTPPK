#include "EuroTPPK.h"

VOID PrintConsoleString(LPSTR lpMessage, ...)
{
  CHAR szOutput[0x400] = "";
  PCONSOLEMESSAGE Msg;
  va_list Args;

  if (!GameReady())
    return;

  va_start(Args, lpMessage);
  vsprintf(szOutput, lpMessage, Args);
  va_end(Args);

  Msg = new CONSOLEMESSAGE;
  Msg->Message = new WCHAR[strlen(szOutput) + 1];
  memset(Msg->Message, 0, strlen(szOutput) * sizeof(WCHAR));

  MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szOutput, (INT)strlen(szOutput), Msg->Message, (INT)strlen(szOutput));
  Msg->TimeStamp = GetTickCount();

  Msg->Message[strlen(szOutput)] = L'\0';

  if (v_ConsoleList.GetSize() == 10)// TODO: Revert to max message log size
  {
    delete v_ConsoleList[0]->Message;
    delete v_ConsoleList[0];

    v_ConsoleList.RemoveAt(0);
    v_ConsoleList.FreeExtra();
  }

  v_ConsoleList.Add(Msg);
}

INT GetConsoleSize()
{
  if (v_ConsoleList.IsEmpty())
    return 0;

  INT nSize = 0;

  for (INT i = ((v_ConsoleList.GetSize() > 3) ? v_ConsoleList.GetSize() - 3 : 0); i < v_ConsoleList.GetSize(); i++)
  {
    if ((GetTickCount() - v_ConsoleList[i]->TimeStamp) < v_ConsoleDelay)
      nSize++;
  }

  return nSize;
}

BOOL DrawConsole()
{
  CArrayEx<PCONSOLEMESSAGE, PCONSOLEMESSAGE> TempMessages;

  if (v_ConsoleList.IsEmpty() || (D2CLIENT_GetUiVar((UI_MSGS)) && D2CLIENT_GetUiVar((UI_CHAT))))
    return TRUE;

  //	if(Test)
  //	{
  //		if(D2CLIENT_GetUiVar((UI_MSGS)))
  //		{
  //			v_ConsoleLogs = FALSE;
  //			return FALSE;
  //		}

  //		int x,y,x2,y2;
  /*
      x=223;
      y=177;
      x2=560;
      y2=360; */

      //	D2GFX_DrawRectangle(x,y,x2,y2,0,1);
      //	D2DrawRectFrame(x,y,x2,y2);

      /*	D2GFX_DrawRectangle(42, 30, 758, 450, 15, 2);
        D2GFX_DrawLine(42, 30, 758, 30, 4, -1);
        D2GFX_DrawLine(758, 30, 758, 450, 4, -1);
        D2GFX_DrawLine(758, 450, 42, 450, 4, -1);
        D2GFX_DrawLine(5, 450, 42, 30, 4, -1);
      */

      //	DWORD dwOldSize = D2WIN_SetTextSize(D2FONT_SMALL);
      //	for(INT i = 0; i < v_ConsoleList.GetSize(); i++)
          //D2WIN_DrawText(v_ConsoleList[i]->Message, 42, 50 + (i * 16), 0, -1);
      //		D2WIN_DrawText(v_ConsoleList[i]->Message, x, y + (i * 10), 0, -1);
      //	D2WIN_SetTextSize(dwOldSize);
    //	}
  if (v_ConsoleLogs)
  {
    for (INT i = ((v_ConsoleList.GetSize() > 10) ? v_ConsoleList.GetSize() - 10 : 0); i < v_ConsoleList.GetSize(); i++)
    {
      if (v_ConsoleDelay == 0 || ((GetTickCount() - v_ConsoleList[i]->TimeStamp) < v_ConsoleDelay))
        TempMessages.Add(v_ConsoleList[i]);
    }

    if (TempMessages.IsEmpty())
      return TRUE;

    INT nConsoleHeight = (TempMessages.GetSize() - 1) * 15;
    INT nConsoleWidth = 385;
    int x, y, x2, y2;
    int yNew = y + 12;
    int fontNew;

    x = 223; // 337 Wigth
    y = 177; // 183 Height
    x2 = 500;
    y2 = 295;
    fontNew = 0;
    // close box temporary

//if(!Moved1Pre)
    if (!MooTarget)
      if (!MooExp)
        if (!Moo)
          if (!MooWinAmp)
            if (!MooInfoTarget)
              if (D2CLIENT_MouseX >= x2 - 10 && D2CLIENT_MouseX <= x2) {
                if (D2CLIENT_MouseY >= y && D2CLIENT_MouseY <= y + 13) {
                  fontNew = 5;
                  ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
                  if (KEYDOWN(MK_LBUTTON)) {
                    v_ConsoleLogs = false;
                    //	PreBoxxMoved=false;
                    //	Moved1Pre=false;
                  }
                }
              }

    D2GFX_DrawRectangle(x, y, x2, y2, 0, 1);
    D2DrawRectFrame(x, y, x2, y2);
    DrawTextToScreen("X", x2 - 12, y + 13, fontNew, 6);
    DrawTextToScreen("Console", x + 5, y + 12, FONTCOLOR_GOLD, 6);
    yNew += 10;

    /*D2GFX_DrawRectangle(127, 525 - nConsoleHeight, 672, 550, 15, 2);
    D2GFX_DrawLine(127, 525 - nConsoleHeight, 672, 525 - nConsoleHeight, 4, -1);
    D2GFX_DrawLine(672, 525 - nConsoleHeight, 672, 550, 4, -1);
    D2GFX_DrawLine(672, 550, 127, 550, 4, -1);
    D2GFX_DrawLine(127, 550, 127, 525 - nConsoleHeight, 4, -1);*/

    DWORD dwSize = D2WIN_SetTextSize(D2FONT_SMALL);
    for (INT i = 0; i < TempMessages.GetSize(); i++)
      //D2WIN_DrawText(TempMessages[i]->Message, 127, (540 - nConsoleHeight) + (i * 16) + 4, 0, -1);
      D2WIN_DrawText(TempMessages[i]->Message, x + 2, y + 20 + (i * 10) + 4, 0, -1);
    D2WIN_SetTextSize(dwSize);
  }

  return TRUE;
}

BOOL DrawMessageConsole()
{
  CArrayEx<PCONSOLEMESSAGE, PCONSOLEMESSAGE> TempMessages;

  if (v_ConsoleList.IsEmpty() || (D2CLIENT_GetUiVar((UI_MSGS)) && D2CLIENT_GetUiVar((UI_CHAT))))
    return TRUE;

  if (v_ConsoleLogs)
  {
    if (D2CLIENT_GetUiVar((UI_MSGS)))
    {
      v_ConsoleLogs = FALSE;
      return FALSE;
    }

    D2GFX_DrawRectangle(42, 30, 758, 450, 15, 2);
    D2GFX_DrawLine(42, 30, 758, 30, 4, -1);
    D2GFX_DrawLine(758, 30, 758, 450, 4, -1);
    D2GFX_DrawLine(758, 450, 42, 450, 4, -1);
    D2GFX_DrawLine(5, 450, 42, 30, 4, -1);

    DWORD dwOldSize = D2WIN_SetTextSize(D2FONT_SMOOTH);
    for (INT i = 0; i < v_ConsoleList.GetSize(); i++)
      D2WIN_DrawText(v_ConsoleList[i]->Message, 42, 50 + (i * 16), 0, -1);
    D2WIN_SetTextSize(dwOldSize);
  }
  else
  {
    for (INT i = ((v_ConsoleList.GetSize() > 3) ? v_ConsoleList.GetSize() - 3 : 0); i < v_ConsoleList.GetSize(); i++)
    {
      if (v_ConsoleDelay == 0 || ((GetTickCount() - v_ConsoleList[i]->TimeStamp) < v_ConsoleDelay))
        TempMessages.Add(v_ConsoleList[i]);
    }

    if (TempMessages.IsEmpty())
      return TRUE;

    INT nConsoleHeight = (TempMessages.GetSize() - 1) * 15;
    INT nConsoleWidth = 385;

    D2GFX_DrawRectangle(127, 525 - nConsoleHeight, 672, 550, 15, 2);
    D2GFX_DrawLine(127, 525 - nConsoleHeight, 672, 525 - nConsoleHeight, 4, -1);
    D2GFX_DrawLine(672, 525 - nConsoleHeight, 672, 550, 4, -1);
    D2GFX_DrawLine(672, 550, 127, 550, 4, -1);
    D2GFX_DrawLine(127, 550, 127, 525 - nConsoleHeight, 4, -1);

    DWORD dwSize = D2WIN_SetTextSize(D2FONT_SMOOTH);
    for (INT i = 0; i < TempMessages.GetSize(); i++)
      D2WIN_DrawText(TempMessages[i]->Message, 127, (540 - nConsoleHeight) + (i * 16) + 4, 0, -1);
    D2WIN_SetTextSize(dwSize);
  }

  return TRUE;
}
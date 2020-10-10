#include "EuroTPPK.h"

bool show = true;
void WelcomeBox(void) {
  if (show) {
    char Buf[1024];
    int x, y, x2, y2;

    x = 223;
    y = 177;
    x2 = 560;
    y2 = 360;

    // FOR THE CROSS
    int fontNew = 0;
    if (D2CLIENT_MouseX >= x2 - 10 && D2CLIENT_MouseX <= x2) {
      if (D2CLIENT_MouseY >= y && D2CLIENT_MouseY <= y + 13) {
        fontNew = 5;
        ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
        if (KEYDOWN(MK_LBUTTON)) {
          show = false;
        }
      }
    }
    int yNew = y + 12;
    D2GFX_DrawRectangle(x, y, x2, y2, 0, 1);
    D2DrawRectFrame(x, y, x2, y2);
    DrawTextToScreen("X", x2 - 12, y + 13, fontNew, 6);
    DrawTextToScreen("EuroTPPK", x + 5, y + 12, FONTCOLOR_GOLD, 6);
    yNew += 10;

    sprintf(Buf, "Welcome to EuroTPPK,%s !\n", PKInfo.ForumName);
    DrawTextToScreen(Buf, x + 5, yNew, FONTCOLOR_WHITE, 6);
    yNew += 15;
    DrawTextToScreen("[Private]\n", x + 5, yNew, FONTCOLOR_GOLD, 6);
    yNew += 10;
    sprintf(Buf, "Your last use was %s\n", PKInfo.LastUse);
    DrawTextToScreen(Buf, x + 5, yNew, FONTCOLOR_WHITE, 6);
    yNew += 10;
    sprintf(Buf, "You have %d Kills %d Score and are ranked %d of 9\n", PKInfo.TotalKills, PKInfo.TotalScore, PKInfo.Rank);
    DrawTextToScreen(Buf, x + 5, yNew, FONTCOLOR_WHITE, 6);
    yNew += 15;
    DrawTextToScreen("[Info]\n", x + 5, yNew, FONTCOLOR_GOLD, 6);
    yNew += 10;
    /*sprintf(Buf, "Loaded %d Members, %d Blacklisted and %d Spammers\n", PlayerFriendList->GetItemCount(), PlayerEnemyList->GetItemCount(), PlayerSpamList->GetItemCount());
    DrawTextToScreen(Buf, x + 5, yNew, FONTCOLOR_WHITE, 6);
    yNew += 15;*/
    DrawTextToScreen("[Latest PKs]", x + 5, yNew, FONTCOLOR_GOLD, 6);
  }
}
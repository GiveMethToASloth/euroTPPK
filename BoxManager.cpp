#include "EuroTPPK.h"

void BoxManager::FixName(std::string& szName) {
  std::transform(szName.begin(), szName.end(), szName.begin(), tolower);
  std::replace(szName.begin(), szName.end(), ' ', '-');
}

void BoxManager::AddBox(Box* box) {
  std::string szName = box->GetBoxName();
  FixName(szName);
  boxList[szName] = box;
}

void BoxManager::RemoveBox(Box* box) {
  std::string szName = box->GetBoxName();
  FixName(szName);
  boxList.erase(szName);
}

void BoxManager::OpenBoxes() {
  for (std::map<std::string, Box*>::iterator it = boxList.begin(); it != boxList.end(); ++it) {
    POINT ptPos = (*it).second->GetTabbedPos();
    POINT ptSize = (*it).second->GetTabbedSize();

    if (IsMouseInBounds(ptPos.x, ptPos.y, ptPos.x + ptSize.x, ptPos.y + ptSize.y)) {
      ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
      if (KEYDOWN(MK_LBUTTON)) {
        (*it).second->SetOpenBox(true);
      }
      else if (KEYDOWN(MK_RBUTTON)) {
        (*it).second->SetOpenBox(false);
      }
    }
  }
}

void BoxManager::MoveBoxes() {
  for (std::map<std::string, Box*>::iterator it = boxList.begin(); it != boxList.end(); ++it) {
    POINT ptPos = (*it).second->GetOpenPos();
    POINT ptSize = (*it).second->GetOpenSize();
    POINT ptDist = { long(ptSize.x / 2), long(ptSize.y / 2) };

    if (IsMouseInBounds(ptPos.x, ptPos.y, ptSize.x + ptPos.x, ptSize.y + ptPos.y)) {
      if (KEYDOWN(MK_LBUTTON)) {
        PrintConsoleString("%d", D2CLIENT_MouseX - ptDist.x);
        (*it).second->SetOpenPos({ LONG(D2CLIENT_MouseX - ptDist.x), LONG(D2CLIENT_MouseY - ptDist.y) });
      }
    }
  }
}

void BoxManager::DrawTabbedBoxes() {
  for (map<string, Box*>::iterator it = boxList.begin(); it != boxList.end(); ++it) {
    POINT ptPos = (*it).second->GetTabbedPos();
    POINT ptSize = (*it).second->GetTabbedSize();
    char szName[0x16] = "";

    D2GFX_DrawRectangle(ptPos.x, ptPos.y, ptPos.x + ptSize.x, ptPos.y + ptSize.y, 0, 100);
    D2DrawRectFrame(ptPos.x, ptPos.y, ptPos.x + ptSize.x, ptPos.y + ptSize.y);
    strcpy_s(szName, (*it).second->GetBoxName().c_str());
    DrawTextToScreen(szName, ptPos.x + 3, ptPos.y + ptSize.y - 2, (*it).second->IsBoxOpen() ? FONTCOLOR_GREY : FONTCOLOR_WHITE, 6);
  }
}

void BoxManager::DrawBoxes() {
  if (!D2CLIENT_GetUiVar(0x01))
    if (!D2CLIENT_GetUiVar(0x1a))
      if (!D2CLIENT_GetUiVar(0x19))
        if (!D2CLIENT_GetUiVar(0x02))
          if (!D2CLIENT_GetUiVar(0x18))
            for (auto box : boxList) {
              if (box.second->IsBoxOpen()) {
                POINT ptPos = box.second->GetOpenPos();
                POINT ptSize = box.second->GetOpenSize();
                char szName[0x16] = "";

                D2GFX_DrawRectangle(ptPos.x, ptPos.y, ptPos.x + ptSize.x, ptPos.y + ptSize.y, 0, 100);
                D2DrawRectFrame(ptPos.x, ptPos.y, ptPos.x + ptSize.x + 2, ptPos.y + ptSize.y);
                strcpy_s(szName, box.second->GetBoxName().c_str());
                DrawTextToScreen(szName, ptPos.x + 5, ptPos.y - 5, FONTCOLOR_WHITE, 6);
                int y = ptPos.y + 2;
                for (auto info : box.second->GetBoxInfo()) {
                  char szInfo[200] = "";
                  strcpy_s(szInfo, info.c_str());
                  DrawTextToScreen(szInfo, ptPos.x + 5, y += 12, FONTCOLOR_WHITE, 6);
                }
              }
            }
}
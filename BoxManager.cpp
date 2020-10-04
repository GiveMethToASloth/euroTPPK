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
  for (map<string, Box*>::iterator it = boxList.begin(); it != boxList.end(); ++it) {
    POINT ptPos = (*it).second->GetTabbedCoords();
    POINT ptSize = (*it).second->GetTabbedSize();

    if (
      D2CLIENT_MouseX > ptPos.x && D2CLIENT_MouseX < ptPos.x + ptSize.x &&
      D2CLIENT_MouseY > ptPos.y && D2CLIENT_MouseY < ptPos.y + ptSize.y
      ) {
      ClickMapConfig(9, D2CLIENT_MouseX, D2CLIENT_MouseY, 1);
      if (KEYDOWN(MK_LBUTTON)) {
        (*it).second->OpenBox(true);
      }
      else if (KEYDOWN(MK_RBUTTON)) {
        (*it).second->OpenBox(false);
      }
    }
  }
}

void BoxManager::DrawTabbedBoxes() {
  for (map<string, Box*>::iterator it = boxList.begin(); it != boxList.end(); ++it) {
    POINT ptPos = (*it).second->GetTabbedCoords();
    POINT ptSize = (*it).second->GetTabbedSize();
    char szName[0x16] = "";

    D2GFX_DrawRectangle(ptPos.x, ptPos.y, ptPos.x + ptSize.x, ptPos.y + ptSize.y, 0, 100);
    D2DrawRectFrame(ptPos.x, ptPos.y, ptPos.x + ptSize.x, ptPos.y + ptSize.y);
    strcpy_s(szName, (*it).second->GetBoxName().c_str());
    DrawTextToScreen(szName, ptPos.x + 3, ptPos.y + ptSize.y - 2, FONTCOLOR_WHITE, 6);
  }
}

void BoxManager::DrawBoxes() {
  for (auto box : boxList) {
    if (box.second->IsBoxOpen()) {
      POINT ptPos = box.second->GetOpenCoords();
      POINT ptSize = box.second->GetOpenSize();
      char szName[0x16] = "";

      D2GFX_DrawRectangle(ptPos.x, ptPos.y, ptPos.x + ptSize.x, ptPos.y + ptSize.y, 0, 100);
      D2DrawRectFrame(ptPos.x, ptPos.y, ptPos.x + ptSize.x, ptPos.y + ptSize.y);
      strcpy_s(szName, box.second->GetBoxName().c_str());
      DrawTextToScreen(szName, ptPos.x + 5, ptPos.y + 3, FONTCOLOR_WHITE, 6);
    }
  }
}
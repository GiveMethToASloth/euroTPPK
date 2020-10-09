#include "EuroTPPK.h"

std::map<std::string, Box*> boxes = {
  {"config", pBoxConfig = new Box("Config", 248, 530, 645, 395)},
  {"target", pBoxTarget = new Box("Targets", 296, 530, 325, 395)},
  {"precast", pBoxPrecast = new Box("Precast", 351, 530, 325, 395)},
  {"level", pBoxLevel = new Box("Level", 406, 530, 325, 395)},
  {"console", pBoxLevel = new Box("Console", 447, 530, 325, 395)},
  {"discord", pBoxLevel = new Box("Discord", 502, 530, 325, 395)}
};

void InitBoxes() {
  if (!boxManager) {
    boxManager = new BoxManager();

    for (const auto box : boxes) {
      boxManager->AddBox(box.second);
    }
  }
}

void ConfigBox() {
  if (pBoxConfig) {
    std::vector<std::string> szBoxInfo;
    char szBuffer[200];

    sprintf_s(szBuffer, "AA: %s", !AA ? "Off" : LeftAA ? "On, Left" : "On, Right");
    szBoxInfo.push_back(szBuffer);

    if (v_TownLifePercent != 0) {
      sprintf_s(szBuffer, "Town (Life): %d", v_TownLifePercent);
    }
    else {
      sprintf_s(szBuffer, "Town (Life): Off");
    }
    szBoxInfo.push_back(szBuffer);

    if (v_QuitLifePercent != 0) {
      sprintf_s(szBuffer, "Quit (Life): %d", v_QuitLifePercent);
    }
    else {
      sprintf_s(szBuffer, "Quit (Life): Off");
    }
    szBoxInfo.push_back(szBuffer);
    if (v_AimChicken == 0)
      sprintf_s(szBuffer, "OnAim: OFF");
    else if (v_AimChicken == 1)
      sprintf_s(szBuffer, "OnAim: TP");
    else if (v_AimChicken == 2)
      sprintf_s(szBuffer, "OnAim: TELE");
    else if (v_AimChicken == 3)
      sprintf_s(szBuffer, "OnAim: QUIT");
    else if (v_AimChicken == 4)
      sprintf_s(szBuffer, "OnAim: WARN");
    szBoxInfo.push_back(szBuffer);
    if (v_HostileChicken == 0)
      sprintf_s(szBuffer, "OnHostile: OFF");
    else if (v_HostileChicken == 1)
      sprintf_s(szBuffer, "OnHostile: TP");
    else if (v_HostileChicken == 2)
      sprintf_s(szBuffer, "OnHostile: TELE");
    else if (v_HostileChicken == 3)
      sprintf_s(szBuffer, "OnHostile: QUIT");
    else if (v_HostileChicken == 4)
      sprintf_s(szBuffer, "OnHostile: WARN");
    szBoxInfo.push_back(szBuffer);
    sprintf_s(szBuffer, "Drink: %s", v_AutoDrink != 0 ? "ON" : "OFF");
    szBoxInfo.push_back(szBuffer);
    if (GetTPs() == 0) {
      BookTimer++;
      if (BookTimer < 1000) {
        DrawTextToScreen("No Valid TP Tome!", 800 / 2 - strlen("No Valid TP Tome!") * 8, 700 / 2, 3, 6);
      }
    }
    sprintf_s(szBuffer, "TP's Left: %d", GetTPs());
    szBoxInfo.push_back(szBuffer);
    pBoxConfig->SetBoxInfo(szBoxInfo);
  }
}

//
//void UpdateBoxes() {
//}
//
//std::vector<std::string> UpdateConfigBox() {
//  std::vector<std::string> szboxInfo;
//  char szBuffer[200];
//
//  sprintf_s(szBuffer, "AA: %s", !AA ? "Off" : LeftAA ? "On, Left" : "On, Right");
//  szboxInfo.push_back(szBuffer);
//
//  if (v_TownLifePercent != 0) {
//    sprintf_s(szBuffer, "Town (Life): %d", v_TownLifePercent);
//  }
//  else {
//    sprintf_s(szBuffer, "Town (Life): Off");
//  }
//  szboxInfo.push_back(szBuffer);
//
//  if (v_QuitLifePercent != 0) {
//    sprintf_s(szBuffer, "Quit (Life): %d", v_QuitLifePercent);
//  }
//  else {
//    sprintf_s(szBuffer, "Quit (Life): Off");
//  }
//  szboxInfo.push_back(szBuffer);
//
//  return szboxInfo;
//}
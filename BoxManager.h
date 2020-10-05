#pragma once
#include <map>
#include <algorithm>

class Box;

class BoxManager
{
private:
  std::map<std::string, Box*> boxList;
  bool bMouseDown;
  POINT lastLocation;
  void FixName(std::string& szName);
public:
  BoxManager() {}
  ~BoxManager() {
    while (boxList.size() > 0) {
      Box* box = boxList.begin()->second;
      delete box;
    }
  }
  void AddBox(Box* box);
  void RemoveBox(Box* box);

  void OpenBoxes();
  void MoveBoxes();

  void DrawTabbedBoxes();
  void DrawBoxes();
};
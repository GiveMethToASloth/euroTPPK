#pragma once
#include <string>
#include <vector>

struct BoxInfo {
  std::string szBoxTitle;
  std::vector<std::string> szBoxInfo;
  bool bIsOpen;
  DWORD dwTabbedXPos;
  DWORD dwTabbedYPos;
  DWORD dwTabbedXSize;
  DWORD dwTabbedYSize;
  DWORD dwOpenXPos;
  DWORD dwOpenYPos;
  DWORD dwOpenXSize;
  DWORD dwOpenYSize;
};

class Box
{
private:
  friend class BoxManager;
  BoxInfo* boxInfo;

public:
  Box(BoxInfo* boxInfo) : boxInfo(boxInfo) {};
  ~Box() {};

  std::string GetBoxName() { return boxInfo->szBoxTitle; }
  bool IsBoxOpen() { return boxInfo->bIsOpen; }
  void OpenBox(bool bOpen) {
    if (bOpen) {
      if (!boxInfo->bIsOpen) {
        boxInfo->bIsOpen = true;
      }
    }
    else
      boxInfo->bIsOpen = false;
  };
  std::vector<std::string> GetBoxInfo() { return boxInfo->szBoxInfo; }
  void UpdateBox(BoxInfo* boxInfo) {
    this->boxInfo = boxInfo;
  }
  POINT GetTabbedCoords() {
    return { long(boxInfo->dwTabbedXPos), long(boxInfo->dwTabbedYPos) };
  }
  void SetTabbedCoords(DWORD dwTabbedXPos, DWORD dwTabbedYPos) {
    boxInfo->dwTabbedXPos = dwTabbedXPos;
    boxInfo->dwTabbedYPos = dwTabbedYPos;
  }
  POINT GetTabbedSize() {
    return { long(boxInfo->dwTabbedXSize), long(boxInfo->dwTabbedYSize) };
  }
  void SetTabbedSize(DWORD dwTabbedXSize, DWORD dwTabbedYSize) {
    boxInfo->dwTabbedXSize = dwTabbedXSize;
    boxInfo->dwTabbedYSize = dwTabbedYSize;
  }
  POINT GetOpenCoords() {
    return { long(boxInfo->dwOpenXPos), long(boxInfo->dwOpenYPos) };
  }
  void SetOpenCoords(DWORD dwOpenXPos, DWORD dwOpenYPos) {
    boxInfo->dwTabbedXPos = dwOpenXPos;
    boxInfo->dwTabbedYPos = dwOpenYPos;
  }
  POINT GetOpenSize() {
    return { long(boxInfo->dwOpenXSize), long(boxInfo->dwOpenYSize) };
  }
  void SetOpenSize(DWORD dwOpenXSize, DWORD dwOpenYSize) {
    boxInfo->dwOpenXSize = dwOpenXSize;
    boxInfo->dwOpenYSize = dwOpenYSize;
  }
};
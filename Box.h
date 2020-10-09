#pragma once
#include <string>
#include <vector>

class Box
{
private:
  friend class BoxManager;
  std::string szBoxTitle;
  std::vector<std::string> szBoxInfo;
  bool bIsOpen;
  DWORD dwTabbedXPos;
  DWORD dwTabbedYPos;
  DWORD dwOpenXPos;
  DWORD dwOpenYPos;

public:
  Box(std::string szBoxTitle, DWORD dwTabbedXPos, DWORD dwTabbedYPos, DWORD dwOpenXPos, DWORD dwOpenYPos)
    : szBoxTitle(szBoxTitle), dwTabbedXPos(dwTabbedXPos), dwTabbedYPos(dwTabbedYPos), dwOpenXPos(dwOpenXPos), dwOpenYPos(dwOpenYPos) {
    bIsOpen = false;
  };
  ~Box() {};

  std::string GetBoxName() { return szBoxTitle; }
  void SetBoxName(std::string szBoxTitle) { this->szBoxTitle = szBoxTitle; }

  std::vector<std::string> GetBoxInfo() { return szBoxInfo; }
  void SetBoxInfo(std::vector<std::string> szBoxInfo) { this->szBoxInfo = szBoxInfo; }

  bool IsBoxOpen() { return bIsOpen; }
  void SetOpenBox(bool bIsOpen) { this->bIsOpen = bIsOpen; }

  POINT GetTabbedPos() { return { long(this->dwTabbedXPos), long(this->dwTabbedYPos) }; }
  void SetTabbedPos(POINT ptTabbedPos) { this->dwTabbedXPos = ptTabbedPos.x; this->dwTabbedYPos = ptTabbedPos.y; }

  POINT GetTabbedSize() {
    POINT ptSiz = { 0, 0 };
    ptSiz = GetTextSize(szBoxTitle, 6);
    ptSiz.x += 6;
    ptSiz.y += 6;
    return ptSiz;
  }

  POINT GetOpenPos() { return { long(this->dwOpenXPos), long(this->dwOpenYPos) }; }
  void SetOpenPos(POINT ptOpenPos) { this->dwOpenXPos = ptOpenPos.x; this->dwOpenYPos = ptOpenPos.y; }

  POINT GetOpenSize() {
    POINT ptSiz = { 0, 0 };
    for (const auto& szStr : szBoxInfo) {
      POINT ptTmp = GetTextSize(szStr, 6);
      if (ptTmp.x > ptSiz.x) {
        ptSiz.x = ptTmp.x;
      }
      if (ptTmp.y > ptSiz.y) {
        ptSiz.y = ptTmp.y;
      }
    }
    ptSiz.x += 6;
    ptSiz.y = 12 * szBoxInfo.size() + 6;
    return ptSiz;
  }
};
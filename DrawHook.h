extern bool PlayerInfo;
extern DWORD TimeOn;
extern DWORD TimeOn1;
extern DWORD BookTimer;
extern DWORD ssTimer;
extern int Players();
extern bool Killed;
extern bool TargetList;
extern bool LevelBox;
extern bool Target;
extern bool Units;
extern bool Set;
extern bool Precasts;
extern DWORD GetUnitIDByXY(LONG Wx, LONG Wy, Room2* pRoom2);
extern bool IsMouseInBounds(DWORD dwXPos, DWORD dwYPos, DWORD dwXPos2, DWORD dwYPos2);
void D2DrawLine(int x, int y, int x2, int y2, DWORD color);
extern bool OneClick;
extern int ClickTimer;
void Enum();
#define KEYDOWN(vk_code)				((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
extern void ResetCount();
extern bool TARGETS;
extern DWORD Count;

//extern POINT EnemyList;

extern bool ConfigPlayerInfo;

//void Targets(void);
void Boxes(void);

void GameDraw();
void DrawUIVars(void);
void DrawAutomapInfos(void);
void RevealActOnce(void);
//void DrawModifiers(void);
void DrawPos(void);
void DrawPlines(void);
//void DrawYonTarget(void);
void AutoTeleDraw(void);
void Screenhooks(void);
//void EnumObjects(void);
//void DrawAbsAboveTarget(void);
//void UpdateVectors(void);

//void DrawPlayerInventoryHook(void);
void DrawWelcomeText(void);

void GiveFinger(void);
//void pk(void);

DWORD __fastcall D2CLIENT_GetUnitName_STUB(DWORD UnitAny);
VOID ScreenToAutomap(POINT* ptPos, int x, int y);
VOID DrawCross(INT nX, INT nY, DWORD dwColor, BOOL Automap);
void TextHook(INT xPos, INT yPos, DWORD dwColor, BOOL Automap, INT dwFont, BOOL dwCenter, LPSTR Text, ...);
void BoxHook(INT x, INT y, INT xSize, INT ySize, DWORD dwColor, DWORD Trans, BOOL Automap);
//void TestDraw(void);
struct Vector {
  POINT WPPos;
  POINT OtherPos;
  POINT QuestPos;

  DWORD WPID;
  DWORD OtherID;
  DWORD QuestID;
};
extern Vector GlobalVectors;
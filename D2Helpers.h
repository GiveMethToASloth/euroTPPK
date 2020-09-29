void HostileAll();
void UnhostMembers();
BOOL Say(LPSTR lpMessage, ...);
BOOL SayOverHead(LPSTR lpMessage, ...);
void GameEndPatch();
void GameLoopPatch();
BOOL SetSkill(WORD wSkillId, BOOL bLeft);
RosterUnit* FindPartyByName(LPSTR szName);
void AttackTo(DWORD PlayerStruct);
void AutomapToScreenRelative(POINT* pos, int x, int y);
extern void TeleportToTele(long x, long y);
void FlashPlayer(DWORD ID);
bool IsInventoryOpen();
void  ToggleInventory(bool on);
void PrintLists(void);
char* ReplaceString(char* source, char* old, char* newtext);
void PrintChat(char* Message);
DWORD GetExpLeft();
//void SendBNMessage(char* lpMsg);
GameStructInfo* GetGameInfo();
DWORD IsExpansion();
void Tele(WORD x, WORD y);
Level* GetLevel(DWORD dwLevelNo);
DWORD	GetTileLevelNo(Room2* lpRoom2, DWORD dwTileNo);
void DrawBlob(int xpos, int ypos, int col);
DWORD GetDistance(DWORD x1, DWORD y1, DWORD x2, DWORD y2);
DWORD GetDistanceSquared(DWORD x1, DWORD y1, DWORD x2, DWORD y2);
POINT GetPosition();
void GetD2MousePos(POINT& Pointer);
void HoldRightUp(long X, long Y);
int GetPercent(DWORD Current, DWORD Max);
INT		GetSkill(WORD wSkillId);

int MakeParameter(char* szInput, char** argv, char splitchar, bool bSkipQuote);
char* GetNameByID(DWORD PID);
void Hostile(DWORD ID);
void PrintMessage(char* Message, char Color);
void PrintMessageBottomLeft(char* Message, char Color);
VOID DrawTextToScreen(char* szwText, int x, int y, int color, int font);
void D2DrawRectFrame(int x, int y, int x2, int y2);
void  MapToScreenCoords(POINT& rMapPosition);
VOID AutomapToScreen(POINT* ptPos, int xpos, int ypos);

extern void ScreenToAutomapRelative(POINT* pos, int x, int y);
typedef bool(_stdcall* fp)(UnitAny* pUnit);
void fpEnumUnits(fp EnumFunction, DWORD Type);

char* GetD2ClassName(DWORD ClassID);
char* D2ClassName(DWORD ClassID);
char* GetD2LevelName(DWORD LevelID);
bool MakeTP(void);
DWORD GetTPs();
DWORD GetPlayerArea(VOID);

char* mitoa(int integer);

BOOL	IsTownLevel(INT nLevel);

void HostileAll();
void UnhostMembers();
void GameEndPatch();
void GameLoopPatch();
BOOL SetSkill(WORD wSkillId, BOOL bLeft);
void AttackTo(DWORD PlayerStruct);
extern void TeleportToTele(long x, long y);
void FlashPlayer(DWORD ID);
bool IsInventoryOpen();
void  ToggleInventory(bool on);
void PrintLists(void);
DWORD GetExpLeft();
//void SendBNMessage(char* lpMsg);
GameStructInfo* GetGameInfo();
DWORD IsExpansion();
void Tele(WORD x, WORD y);
Level* GetLevel(DWORD dwLevelNo);
DWORD	GetTileLevelNo(Room2* lpRoom2, DWORD dwTileNo);
DWORD GetDistance(DWORD x1, DWORD y1, DWORD x2, DWORD y2);
DWORD GetDistanceSquared(DWORD x1, DWORD y1, DWORD x2, DWORD y2);
void GetD2MousePos(POINT& Pointer);
void HoldRightUp(long X, long Y);
BYTE CalcPercent(DWORD dwVal, DWORD dwMaxVal, BYTE iMin = 0);
INT		GetSkill(WORD wSkillId);

int MakeParameter(char* szInput, char** argv, char splitchar, bool bSkipQuote);
char* GetNameByID(DWORD PID);
void Hostile(DWORD ID);

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

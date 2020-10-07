void OnKey();
void __fastcall KeyHook(BYTE keycode, BYTE repeat);
LONG __stdcall WindowProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
extern DWORD NPCID;
extern bool HostPlayer;
extern bool MoveBox;
extern bool NPCisSeleceted;
extern 	POINT Camp;
extern bool CampOn;
extern bool CampUnitOn;
DWORD WINAPI TeleportThread(LPVOID P);
DWORD WINAPI TeleportMe(LPVOID P);

WORD GetCurrentSkill(BOOL bLeft);
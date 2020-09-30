extern int Delay;
extern bool AutoPK;
extern bool Flash;
extern bool CastMissles;
extern HANDLE TimerHandle;
//	DWORD WINAPI TimerTickThread(LPVOID P);
void SetInTownVars();
void TimerTick();
extern bool Test;

#define KEYDOWN(vk_code)				((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
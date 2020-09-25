
DWORD __fastcall RecvPacket(byte* Packet,DWORD len);
extern DWORD WINAPI AutoPartyMemberThread(LPVOID P);
extern	bool EnchBot;
extern DWORD InGame;

extern	bool GotBo;
extern bool GotSh;
extern	bool GotBc;
extern bool GotCa;
extern bool GotHu;
extern	bool GotOak;
extern bool GotEs;
extern bool GotHs;
extern	bool EnchBot;
extern bool GotEnch;
extern bool GotCAr;
extern bool GotSa;
extern bool GotFa;
extern bool GotFade;
extern bool bLeft;
bool __fastcall OnGamePacketReceived(LPBYTE aPacket, DWORD aLen);
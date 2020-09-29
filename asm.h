DWORD GetPlayerID(VOID);
void SendGAMEPacket(BYTE* Packet, DWORD PacketSize);
DWORD __fastcall D2CLIENT_clickParty_ASM(DWORD RosterUnit, DWORD Mode);
//DWORD __fastcall D2CLIENT_GetUnitFromId_STUB(DWORD unitid, DWORD unittype);
WORD GetPlayerX(DWORD ID);
WORD GetPlayerY(DWORD ID);
//WORD GetPlayerXTarget(DWORD ID);
//WORD GetPlayerYTarget(DWORD ID);
DWORD __fastcall TestPvpFlag_STUB(DWORD planum1, DWORD planum2, DWORD flagmask);
extern DWORD SendPacketAddr;
//extern DWORD p_D2CLIENT_pUnitTableM;
extern DWORD D2CLIENT_GetUnitFromId_M;
extern DWORD D2CLIENT_xPlayerUnit;
//void GameDrawPlayerBlob_STUB();

//DWORD GetMaxMana();
//DWORD GetMaxLife();
//DWORD GetCurrentMana();
//DWORD GetCurrentLife();

void __fastcall NextGameNamePatch(Control* box, BOOL(__stdcall* FunCallBack)(Control*, DWORD, DWORD));
void __fastcall NextGamePasswordPatch(Control* box, BOOL(__stdcall* FunCallBack)(Control*, DWORD, DWORD));

DWORD __fastcall D2CLIENT_GetUIVar_STUB(DWORD varno);
//void GameShake1_STUB();
//void __stdcall GameShake(LPDWORD lpX, LPDWORD lpY);
void  __fastcall D2COMMON_DisplayOverheadMsg_ASM(DWORD pUnit);
void __fastcall GameEndPatch_ASM();
void GameLoopPatch_ASM();
void D2Login_ASM();
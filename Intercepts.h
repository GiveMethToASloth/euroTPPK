//#define FindUnit D2CLIENT_GetUnitFromId_STUB
void OnGamePacketReceived_STUB();
void SendPacketIntercept_STUB();
void PlayerJoinMsgPatch_ASM();

extern DWORD BreakItUp;
extern DWORD DontBreak;
void OnGamePacketReceived_STUB();
void KeyHookIntercept_STUB();
void DrawIntercept_STUB();
extern DWORD DrawCall;
//void GameLightRadius_STUB();
void GameFailToJoin_STUB();
void GameDraw_STUB();
void GameDrawAutomapInfo_STUB();

//void PlayerMapIntercept();
//void  PlayerBlobIntercept();
//void PlayerPatch();
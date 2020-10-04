PatchHook pHooks[] = {
  {PatchJmp, GetDllOffset("D2Client.dll", 0x5ADB3), (DWORD)GameDrawAutomapInfo_STUB, 5},
  {PatchJmp, GetDllOffset("D2Client.dll", 0x572D8), (DWORD)GameDraw_STUB, 6},
  {PatchCall, GetDllOffset("D2Client.dll", 0x6A847), (DWORD)KeyHookIntercept_STUB, 7},
  {PatchCall, GetDllOffset("D2Client.dll", 0x56FAA), (DWORD)OnKey_STUB, 5},

  //{PatchCall, GetDllOffset("D2Client.dll", 0x5F8F7),(DWORD)GameLightRadius_STUB, 5},

  /*{PatchJmp, GetDllOffset("D2Net.dll", 0x78525), (DWORD)SendPacketIntercept_STUB,5},*/
  {PatchCall, GetDllOffset("D2Client.dll", 0x5F802),(DWORD)OnGamePacketReceived_STUB, 5},

  /*{PatchCall, GetDllOffset("D2Client.dll", 0xBB5B6), (DWORD)GameShake1_STUB, 6},
  {PatchCall, GetDllOffset("D2Client.dll", 0x7CA82), (DWORD)GameShake, 5},*/
  //{PatchCall, GetDllOffset("D2Client.dll", 0x3FC1E),(DWORD)PlayerMapIntercept, 5},
  //{PatchCall, GetDllOffset("D2Client.dll", 0x3F69D),(DWORD)PlayerBlobIntercept, 6},
  //{PatchCall, GetDllOffset("D2Client.dll", 0x3F69D), (DWORD)GameDrawPlayerBlob_STUB, 6}, // nya 6FB01BFD | 6FAEF69D-6FAB0000
  //{PatchJmp, GetDllOffset("D2Client.dll",  0x5CEB7), (DWORD)PlayerPatch, 15},
  //{PatchCall, GetDllOffset("D2Client.dll", 0x7BB5E), (DWORD)GameFailToJoin_STUB, 6},

  /*{PatchCall, GetDllOffset("D2Multi.dll", 0x45EFE), (DWORD)NextGameNamePatch, 5},
  {PatchCall, GetDllOffset("D2Multi.dll", 0x45F39), (DWORD)NextGamePasswordPatch, 5},
  {PatchCall, GetDllOffset("D2Multi.dll", 0x46153), (DWORD)NextGameNamePatch, 5},
  {PatchCall, GetDllOffset("D2Multi.dll", 0x4618E), (DWORD)NextGamePasswordPatch, 5},
  {PatchCall,  GetDllOffset("D2Client.dll", 0x25A1B3),(DWORD)GameEndPatch_ASM, 5 },*/
  {PatchCall,  GetDllOffset("D2Client.dll", 0x4F28B),(DWORD)GameLoopPatch_ASM, 6,}
};
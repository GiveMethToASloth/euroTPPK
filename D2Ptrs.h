#include "ArrayEx.h"
#include "D2Structs.h"

#ifdef _DEFINE_VARS

enum { DLLNO_D2CLIENT, DLLNO_D2COMMON, DLLNO_D2GFX, DLLNO_D2LANG, DLLNO_D2WIN, DLLNO_D2NET, DLLNO_D2GAME, DLLNO_D2LAUNCH, DLLNO_FOG, DLLNO_BNCLIENT, DLLNO_STORM, DLLNO_D2CMP, DLLNO_D2MULTI };

#define DLLOFFSET(a1,b1) ((DLLNO_##a1)|((b1)<<8))
#define FUNCPTR(d1,v1,t1,t2,o1)	typedef t1 d1##_##v1##_t t2; d1##_##v1##_t *d1##_##v1 = (d1##_##v1##_t *)DLLOFFSET(d1,o1);
#define VARPTR(d1,v1,t1,o1)		typedef t1 d1##_##v1##_t;    d1##_##v1##_t *p_##d1##_##v1 = (d1##_##v1##_t *)DLLOFFSET(d1,o1);
#define ASMPTR(d1,v1,o1)			DWORD d1##_##v1 = DLLOFFSET(d1,o1);

#else

#define FUNCPTR(d1,v1,t1,t2,o1)	typedef t1 d1##_##v1##_t t2; extern d1##_##v1##_t *d1##_##v1;
#define VARPTR(d1,v1,t1,o1)		typedef t1 d1##_##v1##_t;    extern d1##_##v1##_t *p_##d1##_##v1;
#define ASMPTR(d1,v1,o1)			extern DWORD d1##_##v1;

#endif
#define _D2PTRS_START	D2CLIENT_GetMonsterTxt

FUNCPTR(D2CLIENT, GetMonsterTxt, MonsterTxt* __fastcall, (DWORD monno), 0x63832) // Updated
FUNCPTR(D2CLIENT, PrintGameString, void __stdcall, (wchar_t* wMessage, int nColor), 0x9E3A0) // Updated
FUNCPTR(D2CLIENT, PrintPartyString, void __stdcall, (wchar_t* wMessage, int nColor), 0x9E5C0) // Updated
//FUNCPTR(D2CLIENT, PrintGameString2, void __stdcall, (char* szMessage), 0x73EE0) // Updated
//FUNCPTR(BNCLIENT, SendBNMessage, void __fastcall, (LPSTR lpMessage), 0x13BE0) // 0x14070+6FF20000 6FF34070 6FF33BE0-6FF20000

//FUNCPTR(D2CLIENT, GetPlayerXOffset, int __stdcall, (), 0x5D670) // Updated
//FUNCPTR(D2CLIENT, GetPlayerYOffset, int __stdcall, (), 0x5D680) // Updated

FUNCPTR(D2CLIENT, SetSelectedUnit_I, void __fastcall, (UnitAny* pUnit), 0x66DE0) // Updated
FUNCPTR(D2CLIENT, GetSelectedUnit, UnitAny* __stdcall, (), 0x67A10) // Updated
FUNCPTR(D2CLIENT, GetDifficulty, BYTE __stdcall, (), 0x4DCD0) // Updated
//FUNCPTR(D2CLIENT, GetUnknownFlag, DWORD __fastcall, (), 0x30080) // Updated
FUNCPTR(D2CLIENT, GetGameInfo, GameStructInfo* __stdcall, (), 0x4B7A0) // Updated
FUNCPTR(D2CLIENT, GetAutomapSize, DWORD __stdcall, (), 0x5A710) // Updated
FUNCPTR(D2CLIENT, NewAutomapCell, AutomapCell* __fastcall, (), 0x57C30) // Updated
FUNCPTR(D2CLIENT, AddAutomapCell, void __fastcall, (AutomapCell* aCell, AutomapCell** node), 0x57B00) // Updated
FUNCPTR(D2CLIENT, RevealAutomapRoom, void __stdcall, (Room1* pRoom1, DWORD dwClipFlag, AutomapLayer* aLayer), 0x58F40) // Updated
FUNCPTR(D2CLIENT, InitAutomapLayer_I, AutomapLayer* __fastcall, (DWORD nLayerNo), 0x58D40) // Updated
FUNCPTR(D2CLIENT, GetMonsterOwner, DWORD __fastcall, (DWORD nMonsterId), 0x79150) // Updated
FUNCPTR(D2CLIENT, GetUiVar_I, DWORD __fastcall, (DWORD dwVarNo), 0x538D0) // Updated
//FUNCPTR(D2CLIENT, SetUIState, DWORD __fastcall, (DWORD varno, DWORD howset, DWORD unknown1), 0x55F20) // Updated
//FUNCPTR(D2CLIENT, GetItemNameString, bool __fastcall, (UnitAny* pItem, wchar_t* wItemName, int nLen), 0x8C060) // Update
//FUNCPTR(D2CLIENT, CalculateShake, void __stdcall, (DWORD* dwPosX, DWORD* dwPosY), 0xBB4F0) // Update
FUNCPTR(D2CLIENT, GetPlayerUnit, UnitAny* __stdcall, (), 0x63DD0) // Update
//FUNCPTR(D2CLIENT, InitLevel_I, AutomapLayer* __fastcall, (), 0x40650) // Update
FUNCPTR(D2CLIENT, DrawRectFrame, VOID __fastcall, (DWORD Rect), 0x52E50) // Update
FUNCPTR(D2CLIENT, ExitGame, VOID __fastcall, (VOID), 0x4DD60) // Update
FUNCPTR(D2CLIENT, Attack, VOID __stdcall, (AttackStruct* Attack, BOOL AttackingUnit), 0x61700) // Update
FUNCPTR(D2CLIENT, GetItemName, BOOL __fastcall, (UnitAny* pItem, wchar_t* wBuffer, DWORD dwSize), 0x8C060) // Update
FUNCPTR(D2CLIENT, AcceptTrade, VOID __fastcall, (VOID), 0xB9070) // Update
FUNCPTR(D2CLIENT, CancelTrade, VOID __fastcall, (VOID), 0xB90B0) // Update
FUNCPTR(D2CLIENT, GetMouseXOffset, DWORD __fastcall, (VOID), 0x5AFC0) // Updated
FUNCPTR(D2CLIENT, GetMouseYOffset, DWORD __fastcall, (VOID), 0x5AFB0) // Updated

FUNCPTR(D2CLIENT, ClearScreen, VOID __fastcall, (VOID), 0xB4620) // Updated
FUNCPTR(D2CLIENT, GetQuestInfo, VOID* __stdcall, (VOID), 0xB32D0) // Updated
//FUNCPTR(D2CLIENT, UnitTestSelect, DWORD __stdcall, (UnitAny* pUnit, DWORD _1, DWORD _2, DWORD _3), 0x20010) // Updated
FUNCPTR(D2CLIENT, FindServerSideUnit, UnitAny* __fastcall, (DWORD dwId, DWORD dwType), 0x63990) // Updated
FUNCPTR(D2CLIENT, FindClientSideUnit, UnitAny* __fastcall, (DWORD dwId, DWORD dwType), 0x639b0) // Updated
FUNCPTR(D2CLIENT, SetUIVar, DWORD __fastcall, (DWORD varno, DWORD howset, DWORD unknown1), 0x55F20) // Updated
FUNCPTR(D2CLIENT, clickMap, VOID __fastcall, (DWORD MouseFlag, DWORD x, DWORD y, DWORD Type), 0x62D00) // Updated

FUNCPTR(D2CLIENT, GetCursorItem, UnitAny* __fastcall, (VOID), 0x680A0) // Updated
FUNCPTR(D2CLIENT, LeftClickItem, VOID __stdcall, (UnitAny* pPlayer, Inventory* pInventory, INT x, INT y, DWORD dwClickType, InventoryLayout* pLayout, DWORD Location), 0x8FFE0) // Updated
FUNCPTR(D2CLIENT, CloseNPCInteract, VOID __fastcall, (VOID), 0xB3F10) // Updated
FUNCPTR(D2CLIENT, CloseInteract, VOID __fastcall, (VOID), 0x4C6B0) // Updated
//FUNCPTR(D2CLIENT, ChatBoxHandler, DWORD __stdcall, (MSG* pMsg), 0x86F80) // Updated
FUNCPTR(D2CLIENT, InitInventory, VOID __fastcall, (VOID), 0x845A0) // Updated
//FUNCPTR(D2CLIENT, FixShopActions, VOID __fastcall, (VOID), 0x19D90) // Updated
FUNCPTR(D2CLIENT, submitItem, VOID __fastcall, (DWORD dwItemId), 0xB2370) // Updated
FUNCPTR(D2CLIENT, GetUnitHPPercent, DWORD __fastcall, (DWORD dwUnitId), 0x79080) // Updated
//FUNCPTR(D2CLIENT, GetMercUnit, UnitAny* __fastcall, (VOID), 0xB1B30) // Updated
FUNCPTR(D2CLIENT, ShopAction, VOID __fastcall, (UnitAny* pItem, UnitAny* pNpc, UnitAny* pNpc2, DWORD dwSell, DWORD dwItemCost, DWORD dwMode, DWORD _2, DWORD _3), 0xB3870) // Updated
FUNCPTR(D2CLIENT, GetCurrentInteractingNPC, UnitAny* __fastcall, (VOID), 0xB1620) // Updated
FUNCPTR(D2CLIENT, PerformGoldDialogAction, VOID __fastcall, (VOID), 0x54080)
FUNCPTR(D2CLIENT, LeaveParty, VOID __fastcall, (VOID), 0x79FC0)
FUNCPTR(D2CLIENT, Transmute, VOID __fastcall, (VOID), 0x8A0D0)

FUNCPTR(D2CLIENT, HostiledByMe, bool __fastcall, (DWORD id1, DWORD id2), 0x7A070)
FUNCPTR(D2CLIENT, HostiledByUnit, bool __fastcall, (DWORD id), 0x7A170)
FUNCPTR(D2CLIENT, SendInteract, void __fastcall, (DWORD pUnitType, DWORD pUnitId), 0x80930)

VARPTR(D2CLIENT, MouseOffsetY, int, 0x3A5208) // Updated
VARPTR(D2CLIENT, MouseOffsetX, int, 0x3A520C) // Updated
//FUNCPTR(D2CLIENT, CalcShake, void __stdcall, (DWORD* xpos, DWORD* ypos), 0xBB4F0) //added
VARPTR(D2CLIENT, Divisor, int, 0x311254) // Updated
//VARPTR(D2CLIENT, yShake, int, 0xFD114) // Updated
VARPTR(D2CLIENT, GameInfo, GameStructInfo*, 0x3A0438); // Updated
VARPTR(D2CLIENT, Ping, DWORD, 0x3A04A4) // Updated
VARPTR(D2CLIENT, FPS, DWORD, 0x3BB390) // Updated
//VARPTR(D2CLIENT, WaypointTab, DWORD, 0x3BF081) // Updated
//VARPTR(D2CLIENT, xShake, int, 0x11B9B4) // Updated
VARPTR(D2CLIENT, SelectedInvItem, UnitAny*, 0x3BCBF4) // Updated
VARPTR(D2CLIENT, Offset, POINT, 0x3A5198) // Updated
//VARPTR(D2CLIENT, FirstAutomapLayer, AutomapLayer*, 0x11C2B0) // Updated
VARPTR(D2CLIENT, AutomapLayer, AutomapLayer*, 0x3A5164) // Updated
//VARPTR(D2CLIENT, AutomapYPosition, int, 0x11C30C) // Updated
VARPTR(D2CLIENT, PlayerUnit, UnitAny*, 0x3A6A70) // Updated
VARPTR(D2CLIENT, PlayerUnitList, RosterUnit*, 0x3BB5C0) // Updated
//VARPTR(D2CLIENT, QuestTab, DWORD, 0x11D50D) // Updated
VARPTR(D2CLIENT, MouseX, DWORD, 0x3A6AB0)// Updated
VARPTR(D2CLIENT, MouseY, DWORD, 0x3A6AAC) // Updated
VARPTR(D2CLIENT, MapId, DWORD, 0x3A0638)// Updated
VARPTR(D2CLIENT, bWeapSwitch, DWORD, 0x3BCC4C) // Updated
//VARPTR(D2CLIENT, WaypointTable, DWORD, 0x3BF081) // Updated
VARPTR(D2CLIENT, bTradeAccepted, DWORD, 0x3BCE18) // Updated
VARPTR(D2CLIENT, bTradeBlock, DWORD, 0x3BCE28) // Updated
//VARPTR(D2CLIENT, TradeFlag, DWORD, 0x11C1F4) // Updated
VARPTR(D2CLIENT, ScreenSizeX, DWORD, 0x31146C) // Updated
VARPTR(D2CLIENT, ScreenSizeY, DWORD, 0x311470) // Updated
VARPTR(D2CLIENT, ChatMsg, wchar_t*, 0x3BB638) // Updated
VARPTR(D2CLIENT, AlwaysRun, DWORD, 0x3A0660) // Updated
//VARPTR(D2CLIENT, RecentTradeName, wchar_t*, 0x12334C) // Updated
VARPTR(D2CLIENT, RecentTradeId, DWORD, 0x3C0E7C) // Updated
//VARPTR(D2CLIENT, SelectedUnit, UnitAny*, 0x11C1D8) // Updated
VARPTR(D2CLIENT, ItemPriceList, DWORD, 0x3C0D43) // Updated
//VARPTR(D2CLIENT, RepairCosts, DWORD, 0x11B67B) // Updated
VARPTR(D2CLIENT, RecentInteractId, DWORD, 0x3C0D25) // Updated
VARPTR(D2CLIENT, NPCMenu, NPCMenu*, 0x326C48) // Updated
VARPTR(D2CLIENT, NPCMenuAmount, DWORD, 0x325A74) // Updated
//VARPTR(D2CLIENT, ScreenCovered, DWORD, 0x11C1D0) // Updated
VARPTR(D2CLIENT, InventoryLayout, InventoryLayout*, 0x3BCB88) // Updated
VARPTR(D2CLIENT, StashLayout, InventoryLayout*, 0x3BCA78) // Updated 100BC0 100BC0
VARPTR(D2CLIENT, StoreLayout, InventoryLayout*, 0x3BCB58) // Updated
VARPTR(D2CLIENT, CubeLayout, InventoryLayout*, 0x3BCB70) // Updated
VARPTR(D2CLIENT, TradeLayout, InventoryLayout*, 0x3BCA30) // Updated
VARPTR(D2CLIENT, MercLayout, InventoryLayout*, 0x3BCD4C) // Updated
//VARPTR(D2CLIENT, StoreTable, DWORD, 0x101638) // Updated
//VARPTR(D2CLIENT, ChatTextBuffer, wchar_t*, 0x11FC40) // Updated
VARPTR(D2CLIENT, RegularCursorType, DWORD, 0x3A6AF0) // Updated
VARPTR(D2CLIENT, ShopCursorType, DWORD, 0x3BCBF0) // Updated
VARPTR(D2CLIENT, OverheadTrigger, DWORD, 0x3BF20E) // Updated xxxxxxx
VARPTR(D2CLIENT, ExpCharFlag, DWORD, 0x3A04F4) // Updated
//VARPTR(D2CLIENT, ChatBoxFlag, DWORD, 0x11BF4C) // Updated
//VARPTR(D2CLIENT, MercStrIndex, WORD, 0x325494) // Updated
VARPTR(D2CLIENT, MercReviveCost, DWORD, 0x3C0DD0) // Updated
//VARPTR(D2CLIENT, ShopPerformFlag_I, DWORD, 0x11B56B) // Updated
//VARPTR(D2CLIENT, ShopPerformFlag_II, DWORD, 0x11B667) // Updated
VARPTR(D2CLIENT, GoldDialogAmount, DWORD, 0x3A2A68) // Updated
VARPTR(D2CLIENT, GoldDialogAction, DWORD, 0x3A279C) // Updated

//VARPTR(D2CLIENT, xMapShake, int, 0x11B9B4)
//VARPTR(D2CLIENT, yMapShake, int, 0xFD114)
//VARPTR(D2CLIENT, fAutomapOn, DWORD, 0x3A27E8)
//VARPTR(D2CLIENT, ptAutomap, POINT, 0x11C2D8)

//ASMPTR(D2CLIENT, GenerateSpell_I, 0x4F800) //6FAFF800 6FAFFF08  |. E8 F3F8FFFF    CALL D2Client.6FAFF800                   ; \D2Client.6FAFF800
//ASMPTR(D2CLIENT, TestPvpFlag_I, 0x30DD0) // Updated
ASMPTR(D2CLIENT, GameLoop, 0x4C990) //Updated 1.14d
ASMPTR(D2CLIENT, LoadUIImage_I, 0x788B0) // Updated
ASMPTR(D2CLIENT, LoadAct_1, 0x59150) // Updated
ASMPTR(D2CLIENT, LoadAct_2, 0x62D00) // Updated
ASMPTR(D2CLIENT, GetUnitName_I, 0x64A60) // Updated
ASMPTR(D2CLIENT, InputCall_I, 0x787B0) // Updated
ASMPTR(D2CLIENT, Interact_I, 0x2B2E0) // Updated
ASMPTR(D2CLIENT, clickParty_I, 0x79EB0) // Updated
//ASMPTR(D2CLIENT, clickLocPtrs, 0xDCAE4) // Updated
ASMPTR(D2CLIENT, ClickShopItem_I, 0xB2653) // Updated
ASMPTR(D2CLIENT, ShopAction_I, 0x7D030) // Updated
ASMPTR(D2CLIENT, clickBelt_I, 0x98870) // Updated
ASMPTR(D2CLIENT, clickBeltRight_I, 0x98A90) // Updated
ASMPTR(D2CLIENT, clickItemRight_I, 0x87740) // Updated
ASMPTR(D2CLIENT, GetItemDesc_I, 0x2E380) // Updated
ASMPTR(D2CLIENT, MercItemAction_I, 0x785B0) // Updated
//ASMPTR(D2CLIENT, Attack_I, 0xDC6E4) // Updated
ASMPTR(D2CLIENT, AssignPlayer_I, 0x66200)

//ASMPTR(D2CLIENT, OverrideShrinePatch_ORIG, 0x3A3150) // 0x6FAC6A72-6FAB0000

//6FB37206   > B9 40FCBC6F    MOV ECX,D2Client.6FBCFC40
ASMPTR(D2CLIENT, Say_I, 0x7CBDA)
//ASMPTR(D2CLIENT, PlaySound_I, 0x31FA0) // Updated
//ASMPTR(D2CLIENT, PerfomNpcAction_1, 0x191C0) // Updated
//ASMPTR(D2CLIENT, TakeWP_I, 0x797E0) // Updated & Actually it's the D2CLIENT_SendPacketWithTheSize9(DWORD dwArg1, DWORD dwArg2)
//ASMPTR(D2CLIENT, clickMap_1, 0x102B7C) // Updated
//ASMPTR(D2CLIENT, clickMap_2, 0x11C1D8) // Updated
//ASMPTR(D2CLIENT, clickMap_3, 0x5D5A0) // Updated
//ASMPTR(D2CLIENT, clickMap_4, 0x5CEF9) // Updated

//FUNCPTR(D2CLIENT, CheckLootASM, BOOL __fastcall, (DWORD* pUnit), 0x78910) // 0x6FADE730 - 0x6fab0000 6FB28910-0x6fab0000
//FUNCPTR(D2COMMON, GetRoomInfo, DWORD __stdcall, (UnitAny* PlayerUnit), -10366)
FUNCPTR(D2COMMON, AddRoomData, void __stdcall, (Act* ptAct, int LevelId, int Xpos, int Ypos, Room1* pRoom), 0x21A070) // Updated
FUNCPTR(D2COMMON, RemoveRoomData, void __stdcall, (Act* ptAct, int LevelId, int Xpos, int Ypos, Room1* pRoom), 0x21A0C0) // Updated
FUNCPTR(D2COMMON, GetLevelTxt, LevelTxt* __stdcall, (DWORD levelno), 0x21DB70) // Updated
FUNCPTR(D2COMMON, GetObjectTxt, ObjectTxt* __stdcall, (DWORD objno), 0x240E90) // Updated
FUNCPTR(D2COMMON, GetLayer, AutomapLayer2* __fastcall, (DWORD dwLevelNo), 0x21E470) // Updated
FUNCPTR(D2COMMON, GetLevel, Level* __fastcall, (ActMisc* pMisc, DWORD dwLevelNo), 0x242AE0) // Updated
FUNCPTR(D2COMMON, InitLevel, void __stdcall, (Level* pLevel), 0x2424A0) // updated
FUNCPTR(D2COMMON, GetItemFromInventory, UnitAny* __stdcall, (Inventory* inv), 0x23B2C0) // Updated
FUNCPTR(D2COMMON, GetNextItemFromInventory, UnitAny* __stdcall, (UnitAny* pItem), 0x23DFA0)// Updated
FUNCPTR(D2COMMON, GetItemText, ItemTxt* __stdcall, (DWORD dwItemNo), 0x2335F0) // Updated
FUNCPTR(D2COMMON, GetUnitStat, DWORD __stdcall, (UnitAny* pUnit, DWORD dwStat, DWORD dwStat2), 0x225480) // Updated
FUNCPTR(D2COMMON, GetUnitState, int __stdcall, (UnitAny* pUnit, DWORD dwStateNo), 0x239DF0) // Updated
FUNCPTR(D2COMMON, GetUnitState2, int __stdcall, (UnitAny* pUnit, DWORD dwStat, DWORD unknown), 0x2253b0) // Added
FUNCPTR(D2COMMON, GetUnitState3, int __stdcall, (DWORD unknown, DWORD unknown2), 0x264780) // Added // 10152 10680
//FUNCPTR(D2COMMON, GetUnitX, int __stdcall, (Path* pPath), -10178) // Updated
//FUNCPTR(D2COMMON, GetUnitY, int __stdcall, (Path* pPath), -10191) // Updated
FUNCPTR(D2COMMON, MapToAbsScreen, void __stdcall, (long* pX, long* pY), 0x243260)// Updated //
FUNCPTR(D2COMMON, AbsScreenToMap, void __stdcall, (long* ptMouseX, long* ptMouseY), 0x243510)// Updated
//FUNCPTR(D2COMMON, AddLevel, BOOL __stdcall, (Level* pLevel), 0x56550) // Updated
FUNCPTR(D2COMMON, LoadAct, Act* __stdcall, (DWORD ActNumber, DWORD MapId, DWORD Unk, DWORD Unk_2, DWORD Unk_3, DWORD Unk_4, DWORD TownLevelId, DWORD Func_1, DWORD Func_2), 0x2194A0)
FUNCPTR(D2COMMON, GetRoomFromUnit, Room1* __stdcall, (UnitAny* ptUnit), 0x220BB0) // Updated
FUNCPTR(D2COMMON, GetSkillLevel, INT __stdcall, (UnitAny* pUnit, Skill* pSkill, BOOL bTotal), 0x2442A0) // Updated
FUNCPTR(D2COMMON, CheckUnitCollision, DWORD __stdcall, (UnitAny* pUnitA, UnitAny* pUnitB, DWORD dwBitMask), 0x222AA0) // Updated
//FUNCPTR(D2COMMON, GetBaseStat, DWORD __stdcall, (UnitAny* Unit, DWORD dwStat, DWORD dwUkn), -10494) // Updated
//FUNCPTR(D2COMMON, GetCursorItem, UnitAny* __stdcall, (Inventory* ptInventory), -10310) // Updated
//FUNCPTR(D2COMMON, GetItemFlag, DWORD __stdcall, (UnitAny* Item, DWORD dwFlagMask, DWORD dwLineNo, char* szFileName), -10554) // Updated
//FUNCPTR(D2COMMON, GetItemUnit, UnitAny* __stdcall, (DWORD dwId), -10852) // Updated
FUNCPTR(D2COMMON, GetStatList, StatList* __stdcall, (UnitAny* pUnit, DWORD dwUnk, DWORD dwMaxEntries), 0x2257D0) // Updated
FUNCPTR(D2COMMON, CopyStatList, DWORD __stdcall, (StatList* pStatList, Stat* pStatArray, DWORD dwMaxEntries), 0x225C90) // Updated
//FUNCPTR(D2COMMON, GetItemQuality, DWORD __stdcall, (UnitAny* pItem), -10276) // Updated
//FUNCPTR(D2COMMON, GetItemNameString, void __stdcall, (UnitAny* pItem, char* szItemName, int nLen), 0x2C440) // ??? Updated
FUNCPTR(D2COMMON, GetItemMagicalMods, CHAR* __stdcall, (WORD wPrefixNum), 0x233EE0) // Updated
FUNCPTR(D2COMMON, CheckWaypoint, DWORD __stdcall, (DWORD WaypointTable, DWORD dwLevelId), 0x260E50) // Updated
FUNCPTR(D2COMMON, GetItemPrice, DWORD __stdcall, (UnitAny* MyUnit, UnitAny* pItem, DWORD U1_, DWORD U2_, DWORD U3_, DWORD U4_), 0x22FDC0) // Updated
FUNCPTR(D2COMMON, GetQuestFlag, INT __stdcall, (VOID* QuestInfo, DWORD dwQuest, DWORD dwFlag), 0x25C310) // Updated
FUNCPTR(D2COMMON, GenerateOverheadMsg, OverheadMsg* __stdcall, (DWORD dwUnk, CHAR* szMsg, DWORD dwTrigger), 0x261110) // Updated
FUNCPTR(D2COMMON, FixOverheadMsg, VOID __stdcall, (OverheadMsg* pMsg, DWORD dwUnk), 0x261230) // Updated
FUNCPTR(D2COMMON, CheckCollision, DWORD __stdcall, (Room1* pRoom, DWORD dwX, DWORD dwY, DWORD dwBitMask), 0x24CB30) // Updated
//FUNCPTR(D2COMMON, GetUnitMaxHP, DWORD __stdcall, (UnitAny* pUnit), -10445) // Updated
//FUNCPTR(D2COMMON, CheckUnitSlot, DWORD __stdcall, (Inventory* pInventory, DWORD dwSlot), -10099)
FUNCPTR(D2COMMON, GetExpToAchiveLvl, int __stdcall, (int ClassId, int ExpLvl), 0x211800)
FUNCPTR(D2COMMON, GetDistance, int __stdcall, (UnitAny* Unit, WORD x, WORD y), 0x2417F0)
VARPTR(D2CLIENT, PlayerList, RosterUnit*, 0x3BB5C0) //added
//VARPTR(D2CLIENT, pUnitTable, POINT, 0x11A960) //added
//VARPTR(D2COMMON, sqptDataTable, DWORD, 0x9B500) // Updated
ASMPTR(D2COMMON, DisplayOverheadMsg_I, 0x2611A0) // Updated
ASMPTR(D2COMMON, checkCollision_I, 0x58370) // Updated

FUNCPTR(D2NET, SendPacket, bool __stdcall, (size_t aLen, DWORD arg1, BYTE* aPacket), 0x12AE50) // Updated
FUNCPTR(D2NET, ReceivePacket, void __fastcall, (BYTE* aPacket, DWORD aLen), 0x12AEB0) // Updated
FUNCPTR(D2NET, ReceivePacket_I, void __stdcall, (BYTE* aPacket, DWORD aLen), 0x12B920) // Updated

FUNCPTR(D2GFX, DrawAutomapCell, void __stdcall, (CellContext* context, DWORD xpos, DWORD ypos, RECT* cliprect, DWORD bright), 0xF6510)
//FUNCPTR(D2GFX, DrawAutomapCell2, void __stdcall, (CellContext* context, DWORD xpos, DWORD ypos, DWORD bright2, DWORD bright, BYTE* coltab), -10024)
FUNCPTR(D2GFX, DrawRectangle, void __stdcall, (int X1, int Y1, int X2, int Y2, DWORD dwColor, DWORD dwTrans), 0xF6300) // Updated
FUNCPTR(D2GFX, DrawLine, void __stdcall, (int X1, int Y1, int X2, int Y2, DWORD dwColor, DWORD dwUnk), 0xF6380) // Updated
FUNCPTR(D2GFX, GetScreenSize, DWORD __stdcall, (), 0xF5160)  // Updated
VARPTR(D2LAUNCH, BnData, BnetData*, 0x3795D4); // Updated

FUNCPTR(D2MULTI, PrintChannelText, void __fastcall, (int unused, char* szText, DWORD dwColor), 0x47AB0) // Updated
FUNCPTR(D2MULTI, DoChat, VOID __fastcall, (VOID), 0x42810) // Updated
//FUNCPTR(D2MULTI, WhisperIntercept_Jump, VOID __fastcall, (VOID), 0xFC3C + 8)
VARPTR(D2MULTI, ChatBoxMsg, CHAR*, 0x37AE40) // Updated

FUNCPTR(D2CMP, InitCellFile, void __stdcall, (void* cellfile, CellFile** outptr, char* srcfile, DWORD lineno, DWORD filever, char* filename), 0x201340)
FUNCPTR(D2CMP, DeleteCellFile, void __stdcall, (CellFile* cellfile), 0x201A50)

ASMPTR(D2CLIENT, GetUnitFromId_I, 0x3A5E70)
ASMPTR(D2LANG, Say_II, 0x126800)
FUNCPTR(D2LANG, GetLocaleText, wchar_t* __fastcall, (WORD nLocaleTxtNo), 0x124A30)
FUNCPTR(D2WIN, DrawSprites, VOID __fastcall, (VOID), 0xF9870)
FUNCPTR(D2WIN, SetControlText, void* __fastcall, (Control* box, wchar_t* txt), 0xFF5A0) // Updated
FUNCPTR(D2WIN, GetTextWidthFileNo, DWORD __fastcall, (wchar_t* wStr, DWORD* dwWidth, DWORD* dwFileNo), 0x102520) // Updated
FUNCPTR(D2WIN, SetTextSize, DWORD __fastcall, (DWORD dwSize), 0x102EF0) // Updated
FUNCPTR(D2WIN, DrawText, void __fastcall, (wchar_t* wStr, int xPos, int yPos, DWORD dwColor, DWORD dwUnk), 0x102320) // Updated
//FUNCPTR(D2WIN, GetTextLength, DWORD __fastcall, (wchar_t* szwText), -10132)
FUNCPTR(D2GFX, GetHwnd, HWND __stdcall, (), 0xF59A0) // Updated

FUNCPTR(D2WIN, TakeScreenshot, void __fastcall, (), 0xFA7A0)
//FUNCPTR(D2MULTI, PrintChannelText, void __stdcall, (const char* szText, DWORD dwColor), 0xF8C0) // Updated.
//FUNCPTR(D2MULTI, SayChannelText, void __stdcall, (const char* szText), 0xFE50) // Clientside

VARPTR(D2CLIENT, AutomapOn, DWORD, 0x3A27E8)  // me

//FOR BOX
//FUNCPTR(D2WIN, CreateEditBox, Control* __fastcall, (DWORD style, int ypos, int xpos, DWORD arg4, DWORD arg5, DWORD arg6, DWORD arg7, DWORD arg8, DWORD arg9, DWORD size, void* buf), -10115)
FUNCPTR(D2WIN, DestroyEditBox, DWORD __fastcall, (Control* box), 0xFDAA0)
//FUNCPTR(D2WIN, GetEditBoxText, wchar_t* __fastcall, (Control* box), -10075)
//FUNCPTR(D2WIN, AddEditBoxChar, DWORD __fastcall, (Control* box, BYTE keycode), -10176)
//FUNCPTR(D2WIN, SetEditBoxText, void* __fastcall, (Control* box, wchar_t* txt), -10095)
FUNCPTR(D2WIN, SetEditBoxProc, void __fastcall, (Control* box, BOOL(__stdcall* FunCallBack)(Control*, DWORD, DWORD)), 0xFDAD0)
FUNCPTR(D2WIN, SelectEditBoxText, void __fastcall, (Control* box), 0xfdd00)

//
//VARPTR(D2CLIENT, ServerIp, char, 0xDFFB0/*0x6FB8FFB0*/)
//VARPTR(D2CLIENT, pAct, Act*, 0x11C01C/*0x6FBCC01C*/) //me // 0x11C2D0+6FAB0000 = 6FBCC2D0 0x6FBCC01C-6FAB0000
VARPTR(D2WIN, FirstControl, Control*, 0x3D55BC) // Updated
VARPTR(D2WIN, FocusedControl, Control*, 0x3D55CC) // Updated

//6F8ED848   E8 33FEFFFF      CALL D2Win.6F8ED680

#define _D2PTRS_END	p_D2WIN_FocusedControl

#undef FUNCPTR
#undef VARPTR
#undef ASMPTR

#define D2CLIENT_AutomapOn					(*p_D2CLIENT_AutomapOn)
#define GetItemFlag(Unit, Flag)				(D2COMMON_GetItemFlag(Unit, Flag, 0, "?"))
#define GetUnitStat(unit, stat)				(D2COMMON_GetUnitStat(unit, stat, 0))
//#define GetBaseStat(unit, stat)				(D2COMMON_GetBaseStat(unit, stat, 0))
#define D2CLIENT_GetUIState(dwVarNo)		(D2CLIENT_GetUIVar_STUB(dwVarNo))
#define D2CLIENT_GetUiVar(dwVarNo)		(D2CLIENT_GetUIVar_STUB(dwVarNo))
#define D2CLIENT_InitAutomapLayer(layerlvl)	((AutomapLayer*)D2CLIENT_InitAutomapLayer_STUB(layerlvl))
#define D2CLIENT_GetUnitName(x)				(wchar_t*)D2CLIENT_GetUnitName_STUB((DWORD)x)
#define D2CLIENT_SetSelectedUnit(x)			(D2CLIENT_SetSelectedUnit_STUB((DWORD)x))
#define D2CLIENT_LoadUIImage(x)				((CellFile*)D2CLIENT_LoadUIImage_ASM(x))
#define D2CLIENT_Interact_(x)				(D2CLIENT_Interact_ASM((DWORD)x))
#define D2CLIENT_clickParty(x,y)			(D2CLIENT_clickParty_ASM((DWORD)x, (DWORD)y))
#define D2CLIENT_ClickShopItem(x,y,z)		(D2CLIENT_ClickShopItem_ASM(x,y,z))
#define D2CLIENT_RightClickItem(X,Y,LOCATION, PLAYER, INVENTORYDATA) D2CLIENT_clickItemRight_ASM(X,Y,LOCATION, (DWORD)PLAYER, (DWORD)INVENTORYDATA)
#define D2CLIENT_clickBeltRight(pPlayer, pInventory, dwShift, dwPotPos)	D2CLIENT_clickBeltRight_ASM((DWORD)pPlayer, (DWORD)pInventory, dwShift, dwPotPos)
#define D2CLIENT_GetItemDesc(pUnit, pBuffer) D2CLIENT_GetItemDesc_ASM((DWORD)pUnit, pBuffer)
#define D2COMMON_DisplayOverheadMsg(pUnit)			D2COMMON_DisplayOverheadMsg_ASM((DWORD)pUnit)
#define D2CLIENT_MercItemAction(bPacketType, dwSlotId)	D2CLIENT_MercItemAction_ASM(bPacketType, dwSlotId)
#define D2CLIENT_PickItem(Unit)				(D2CLIENT_PickItem_ASM((DWORD)Unit))
#define D2WIN_GetHwnd						D2GFX_GetHwnd
#define D2CLIENT_ScreenSizeX                (*p_D2CLIENT_ScreenSizeX)
#define D2CLIENT_ScreenSizeY                (*p_D2CLIENT_ScreenSizeY)

//Vars
#define D2CLIENT_AutomapOn						 (*p_D2CLIENT_AutomapOn)
#define D2CLIENT_Ping							 (*p_D2CLIENT_Ping)
#define D2CLIENT_FPS							 (*p_D2CLIENT_FPS)
//#define D2CLIENT_ServerIP						 (*p_D2CLIENT_ServerIp)
#define D2CLIENT_PlayerUnit						 (*p_D2CLIENT_PlayerUnit)
//#define D2CLIENT_pUnitTable						 (*p_D2CLIENT_pUnitTable)
//#define D2CLIENT_GetUnitFromId(unitid, unittype) ((UnitAny *)D2CLIENT_GetUnitFromId_STUB(unitid, unittype))
//#define D2CLIENT_Act							 (*p_D2CLIENT_pAct)
#define D2CLIENT_PlayerList						 (*p_D2CLIENT_PlayerList)
//#define D2CLIENT_xShake							 (*p_D2CLIENT_xShake)
//#define D2CLIENT_yShake							 (*p_D2CLIENT_yShake)

#define D2CLIENT_MouseX							 (*p_D2CLIENT_MouseX)
#define D2CLIENT_MouseY							 (*p_D2CLIENT_MouseY)

#define TestPvpFlag(dwId1, dwId2, dwFlag)		 (TestPvpFlag_STUB(dwId1, dwId2, dwFlag))
/*
D2VARPTR(D2CLIENT, pSkip, DWORD, 0x1032C8)*/
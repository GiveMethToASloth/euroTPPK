#include "Settings.h"
#include "Console.h"
#ifdef _VARS_DEF

#define MYVAR(type, name)			type v##_##name;
#define DEFINEVAR(type, name)		type name;
#define MYCARRAY(type, name)		CArrayEx<type, type> v_##name;
#define MYTOGGLE(name)				bool v_##name; INT vK_##name;
#define MYKEY(name)					int vK_##name;
CArrayEx<LevelNameInfo*, LevelNameInfo*> LevelNames;

#else

#define MYVAR(d1, v1)				extern d1 v_##v1;
#define DEFINEVAR(type, name)		extern type name;
#define MYCARRAY(type, name)		extern CArrayEx<type, type> v_##name;
#define MYTOGGLE(name)				extern bool v_##name;// extern INT vK_##name;
#define MYKEY(name)					extern int vK_##name;
extern CArrayEx<LevelNameInfo*, LevelNameInfo*> LevelNames;

#endif

//CArrayEx<LevelNameInfo*, LevelNameInfo*> LevelNames;
DEFINEVAR(CHAR, szLastGameName[1024])
//MYCARRAY(LevelNameInfo*, LevelNameInfo)
MYCARRAY(PCONFIGVAR, DeathMessage)
MYCARRAY(PCONFIGVAR, SpamMessage)
MYCARRAY(PCONSOLEMESSAGE, ConsoleList)
MYVAR(DWORD, ConsoleDelay)
// VARS
MYVAR(BOOL, AutoDrink)
MYVAR(BOOL, PrintFailed)

MYVAR(bool, TakeNextTP)
MYVAR(INT, AutoDrinkMana)
MYVAR(INT, AutoDrinkLife)
MYVAR(INT, AutoDrinkReju)
MYVAR(BOOL, ConsoleLogs)
MYVAR(DWORD, DrinkLifeTimer)
MYVAR(DWORD, DrinkManaTimer)
MYVAR(DWORD, DrinkRejuTimer)
MYVAR(DWORD, TownLifePercent)
MYVAR(DWORD, TownManaPercent)
MYVAR(DWORD, QuitLifePercent)
MYVAR(DWORD, QuitManaPercent)

MYVAR(INT, HostileChicken)
MYVAR(INT, AimChicken)

MYVAR(LPSTR, EnchantMe)
MYVAR(LPSTR, EnchantMerc)
MYVAR(LPSTR, EnchantAll)
MYVAR(BOOL, EnchAutoParty)
MYVAR(BOOL, NotifyJoin)
MYVAR(BOOL, DrawSongTitle)

MYVAR(DWORD, MonsterColor)
MYVAR(DWORD, ChampionMonsterColor)
MYVAR(BOOL, DrawImunities)
MYVAR(DWORD, MyMissile)
MYVAR(DWORD, FriendMissile)
MYVAR(DWORD, NeutralMissile)
MYVAR(DWORD, EnemyMissile)

MYVAR(BOOL, AimBox)
MYVAR(DWORD, AimBoxColor)

MYVAR(BOOL, FastTele)

MYVAR(INT, BPIAS)
MYVAR(int, BPFCR)
MYVAR(INT, BPFHR)
MYVAR(INT, BPFBR)

MYVAR(BOOL, ItemLevel)
MYVAR(BOOL, ItemSockets)
MYVAR(BOOL, ItemEthPrefix)

MYVAR(INT, AAType)

MYVAR(DWORD, FLASHCYCLE)
MYVAR(DWORD, AIMCYCLE)
MYVAR(INT, AutoPKMissiles)
MYVAR(BOOL, ShowQuestPackets)

MYVAR(BOOL, InviteMembers)
MYVAR(BOOL, LootMembers)

MYVAR(INT, LogPksOver)
MYVAR(LPSTR, SpamNames)
MYVAR(BOOL, AutoScreenShot)

MYVAR(BOOL, MaxBPs)
MYVAR(BOOL, UseDeathMessage)

// KEYS
MYVAR(LPSTR, TriggerChar)
MYKEY(FastTP)
MYKEY(TPPKGo)
MYKEY(Camp)
MYKEY(CampTarget)
MYKEY(TargetBox)
MYKEY(NextTarget)
MYKEY(AutoAimToggle)
MYKEY(AimKeyToggle)
MYKEY(FlashTarget)
MYKEY(ItemViewer)
MYKEY(DrawPlayerInfo)
MYKEY(SpamButton)
MYKEY(SilentExit)
MYKEY(NormalExit)
MYKEY(WalkPlayer)
MYKEY(WalkAndHostile)
MYKEY(DrawPlayerHooks)
MYKEY(AimAndAttack)
MYKEY(AutoPK)
MYKEY(OpenStash)
MYKEY(BoxKey)
MYKEY(NPCAdd)
MYKEY(TeleNext)
MYKEY(TelePre)
MYKEY(TeleWP)
MYKEY(EnchbotToggle)
MYKEY(NextSong)
MYKEY(PrevSong)
MYKEY(PlaySong)
MYKEY(StopSong)
MYKEY(PrintSong)

#undef MYVAR
#undef MYCARRAY
#undef MYKEY

#undef _VARS_DEF

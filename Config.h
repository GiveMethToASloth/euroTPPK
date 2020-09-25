struct tConfig {
// CHICKEN PART
	int ChickenOnHostile;
	int ChickenOnAim;
	int TownLifeChicken;
	int TownManaChicken;
	int Drink;
	int DrinkLifeTimer;
	int DrinkManaTimer;
	int DrinkRejuvTimer;

	int PrintFailedDrinks;
	int DrinkLife;
	int DrinkMana;
    int DrinkLifeRej;
    int DrinkManaRej;
	int QuitLife;
	int QuitMana;
// ItemLevel
    bool ItemLevel;
    bool ItemSockets;
    bool ItemEth;
// enchbot
    byte EnchBotToggle;
    char EnchMe[512];
    char EnchMerc[512];
    char EnchAll[512];
    bool AutoParty;
    bool PMOnJoin;
    //
    int LootMembers;
    int InviteMembers;
//  playerlists
//  int GetFriends;
//  int GetEnemys;
//  int GetHCPK;
//  int GetIHPK;
    int FastTele;
// Key Config

    byte Trigger;
    byte FastTP;
    byte TPPK;
    byte Targetlist;
    byte NextTarget;
    byte TestCommands;
    byte Camp;
    byte CampUnit;
    byte PlayerInfoToggle;
    byte ItemViewer;
    byte TeleToPlayerHost;
    byte TeleToPlayer;
    byte FastExit;
 //   byte Hostile;
    byte SilentExit;
    byte AimToggle;
    byte AimSlotToggle;
    byte LastLevelPath;
    byte NextLevelPath;
    byte WPPath;
    byte AimButton; 
    byte AutoPK;
    byte StashKey;
    byte InfoToggle;
    byte TargetInfo;
	byte WindowKey;
	byte NPC;
    int Missles;
    int AutoDelay;
    int ShowQuestFlags;
	int LogPKsOver;
    int DrawModifiers;
    int MaxBPs;
	int MaxIAS;
	int MaxFCR;
	int MaxFBR;
	int MaxFHR;
//	int MaxFRW;
	bool AutoSS;

    //bool PlayerInfo;
    int AimBoxColor;
    bool AimBoxEnabled;
//maphack
    int MonsterColor;
    int ChampionMonsterColor;
    int DrawImunities;
    int MyMissile;
    int FriendMissile;
    int NeutralMissile;
    int EnemyMissile;
// AD
    char ADMessage[5120];
    byte ADKey;
// Flash
    int FlashDelay;
    byte FlashKey;
// TPPK Messages
    int PKMessage;
    char Message[512];
// Winamp
    BYTE WNext;
    BYTE WPrev;
    BYTE WSong;
    BYTE WPlay;
    BYTE WStop;
    BOOL ShowSong;

	char SpamNames[512];
	int AAType;
/*
	char OnKillMessage1[5120];
	char OnKillMessage2[5120];
	char OnKillMessage3[5120];
	char OnKillMessage4[5120];
	char OnKillMessage5[5120];
	char OnKillMessage6[5120];
	char OnKillMessage7[5120];
	char OnKillMessage8[5120];
	*/
};
extern tConfig cfg;
void ReadConfig();
//Pickit
/*
#define		CONFIG_UNSET	0xFF

// config struct;
typedef struct Config_p {
	char				Section[128];
	char				Description[128];
	BOOL				Pickup;
	BOOL				Hide;
	ITEMSTRUCT			item;

} CONFIGSTRUCT;*/
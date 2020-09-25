#include "EuroTPPK.h"
#define _CFGFILE_ "eu.ini"
char cfgPath[259]={0};

tConfig cfg;

int IncKillCounter();
int GetKillCounter();
int MakeParameter(char* szInput, char** argv, char splitchar, bool bSkipQuote);
char* GetRandomeMsg(char* tCharName, int tlevel);
char* GetConfigString(char* szSection, char* Item);
DWORD GetKeyConfig(char* szSection,char* Item);
BOOL GetBoolConfig(char* szSection,char* szItem);
char* GetRandomeKillMsg(char* tCharName);
int GetConfigInt(char* Section,char* szItem);

bool GetConfigEntry(char* cfgfile,char* Buffer,char* Section,char* szVar) {
	
char mypath[266]={0};
	    char var[512],
         value[512],
         line[512],
		 mszVar[512];
	sprintf_s(mypath,"%s\\%s",szModulePath,cfgfile);
	sprintf_s(mszVar,"%s[%s]",Section,szVar);
    FILE *fp = fopen(mypath, "r");

    if (fp) {
        while (fgets(line, sizeof(line), fp)) {
           memset(var, 0, sizeof(var));
           memset(value, 0, sizeof(value));
           if (sscanf(line, "%[^ \t=]%*[\t ]=%*[\t ]%[^\n]", var, value) == 2) {
				   if(!_strcmpi(mszVar,var)) {
						strcpy(Buffer,value);
						Buffer[strlen(value)]='\0';
						return true;
				   }
           }
        }
        fclose(fp);
    }
strcpy(Buffer,'\0'); 
return false;
}
char BufferStr[512]={0};
char* GetConfigStr(char* Section,char* szItem) {
	GetConfigEntry(_CFGFILE_,BufferStr,Section,szItem);
	return BufferStr;
}

int GetConfigInt(char* Section,char* szItem) {
	char Buf[10]={0};
	GetConfigEntry(_CFGFILE_,Buf,Section,szItem);
	int szReturn = atoi(Buf);
	delete Buf;
	return szReturn;
}

DWORD GetKeyConfig(char* szSection,char* Item) {
	char mypath[300];
	char Buffer[300];
GetConfigEntry(_CFGFILE_,Buffer,szSection,Item);

if(!_strcmpi("~",Buffer)) return '~';
if(!_strcmpi("\\",Buffer)) return '\\';
if(!_strcmpi(";",Buffer)) return ';';
if(!_strcmpi("`",Buffer)) return '`';
if(!_strcmpi("´",Buffer)) return '´';
if(!_strcmpi("'",Buffer)) return '\'';
if(!_strcmpi("[",Buffer)) return '[';
if(!_strcmpi("]",Buffer)) return ']';
if(!_strcmpi("A",Buffer)) return 'A';
if(!_strcmpi("B",Buffer)) return 'B';
if(!_strcmpi("C",Buffer)) return 'C';
if(!_strcmpi("D",Buffer)) return 'D';
if(!_strcmpi("E",Buffer)) return 'E';
if(!_strcmpi("F",Buffer)) return 'F';
if(!_strcmpi("G",Buffer)) return 'G';
if(!_strcmpi("H",Buffer)) return 'H';
if(!_strcmpi("I",Buffer)) return 'I';
if(!_strcmpi("J",Buffer)) return 'J';
if(!_strcmpi("K",Buffer)) return 'K';
if(!_strcmpi("L",Buffer)) return 'L';
if(!_strcmpi("M",Buffer)) return 'M';
if(!_strcmpi("N",Buffer)) return 'N';
if(!_strcmpi("O",Buffer)) return 'O';
if(!_strcmpi("P",Buffer)) return 'P';
if(!_strcmpi("Q",Buffer)) return 'Q';
if(!_strcmpi("R",Buffer)) return 'R';
if(!_strcmpi("S",Buffer)) return 'S';
if(!_strcmpi("T",Buffer)) return 'T';
if(!_strcmpi("U",Buffer)) return 'U';
if(!_strcmpi("V",Buffer)) return 'V';
if(!_strcmpi("W",Buffer)) return 'W';
if(!_strcmpi("X",Buffer)) return 'X';
if(!_strcmpi("Y",Buffer)) return 'Y';
if(!_strcmpi("Z",Buffer)) return 'Z';
if(!_strcmpi("Å",Buffer)) return 'Å';
if(!_strcmpi("+",Buffer)) return '+';
if(!_strcmpi("#",Buffer)) return '#';

if(!_strcmpi("<",Buffer)) return '<';
if(!_strcmpi(">",Buffer)) return '>';

if(!_strcmpi("VK_0",Buffer)) return '0';
if(!_strcmpi("VK_1",Buffer)) return '1';
if(!_strcmpi("VK_2",Buffer)) return '2';
if(!_strcmpi("VK_3",Buffer)) return '3';
if(!_strcmpi("VK_4",Buffer)) return '4';
if(!_strcmpi("VK_5",Buffer)) return '5';
if(!_strcmpi("VK_6",Buffer)) return '6';
if(!_strcmpi("VK_7",Buffer)) return '7';
if(!_strcmpi("VK_8",Buffer)) return '8';
if(!_strcmpi("VK_9",Buffer)) return '9';
if(!_strcmpi("VK_NUMPAD0",Buffer)) return VK_NUMPAD0;
if(!_strcmpi("VK_NUMPAD1",Buffer)) return VK_NUMPAD1;
if(!_strcmpi("VK_NUMPAD2",Buffer)) return VK_NUMPAD2;
if(!_strcmpi("VK_NUMPAD3",Buffer)) return VK_NUMPAD3;
if(!_strcmpi("VK_NUMPAD4",Buffer)) return VK_NUMPAD4;
if(!_strcmpi("VK_NUMPAD5",Buffer)) return VK_NUMPAD5;
if(!_strcmpi("VK_NUMPAD6",Buffer)) return VK_NUMPAD6;
if(!_strcmpi("VK_NUMPAD7",Buffer)) return VK_NUMPAD7;
if(!_strcmpi("VK_NUMPAD8",Buffer)) return VK_NUMPAD8;
if(!_strcmpi("VK_NUMPAD9",Buffer)) return VK_NUMPAD9;
if(!_strcmpi("VK_F1",Buffer)) return VK_F1;
if(!_strcmpi("VK_F2",Buffer)) return VK_F2;
if(!_strcmpi("VK_F3",Buffer)) return VK_F3;
if(!_strcmpi("VK_F4",Buffer)) return VK_F4;
if(!_strcmpi("VK_F5",Buffer)) return VK_F5;
if(!_strcmpi("VK_F6",Buffer)) return VK_F6;
if(!_strcmpi("VK_F7",Buffer)) return VK_F7;
if(!_strcmpi("VK_F8",Buffer)) return VK_F8;
if(!_strcmpi("VK_F9",Buffer)) return VK_F9;
if(!_strcmpi("VK_F10",Buffer)) return VK_F10;
if(!_strcmpi("VK_F11",Buffer)) return VK_F11;
if(!_strcmpi("VK_F12",Buffer)) return VK_F12;
if(!_strcmpi("VK_HOME",Buffer)) return VK_HOME;
if(!_strcmpi("VK_DELETE",Buffer)) return VK_DELETE;
if(!_strcmpi("VK_INSERT",Buffer)) return VK_INSERT;
if(!_strcmpi("VK_END",Buffer)) return VK_END;
if(!_strcmpi("VK_TAB",Buffer)) return VK_TAB;
if(!_strcmpi("VK_SHIFT",Buffer)) return VK_SHIFT;
if(!_strcmpi("VK_RETURN",Buffer)) return VK_RETURN;
if(!_strcmpi("VK_CONTROL",Buffer)) return VK_CONTROL;
if(!_strcmpi("VK_ESCAPE",Buffer)) return VK_ESCAPE;
if(!_strcmpi("VK_SPACE",Buffer)) return VK_SPACE;
if(!_strcmpi("VK_LEFT",Buffer)) return VK_LEFT;
if(!_strcmpi("VK_UP",Buffer)) return VK_UP;
if(!_strcmpi("VK_RIGHT",Buffer)) return VK_RIGHT;
if(!_strcmpi("VK_DOWN",Buffer)) return VK_DOWN;
if(!_strcmpi("VK_MULTIPLY",Buffer)) return VK_MULTIPLY;
if(!_strcmpi("VK_ADD",Buffer)) return VK_ADD;
if(!_strcmpi("VK_SUBTRACT",Buffer)) return VK_SUBTRACT;
if(!_strcmpi("VK_DECIMAL",Buffer)) return VK_DECIMAL;
if(!_strcmpi("VK_DIVIDE",Buffer)) return VK_DIVIDE;
if(!_strcmpi("VK_ALT",Buffer)) return VK_MENU;

//if(!_strcmpi(".",Buffer)) return VK_OEM_PERIOD;
//if(!_strcmpi(",",Buffer)) return VK_OEM_COMMA;
if(!_strcmpi(".",Buffer)) return '.';
if(!_strcmpi(",",Buffer)) return ',';
return -1;
}

void ReadConfig() {
/*Chickens
	v_HostileChicken=GetConfigInt("Chicken","Hostile");
	v_AimChicken=GetConfigInt("Chicken","Aim");
	v_TownLifePercent=GetConfigInt("Chicken","TownLifeChicken");
	v_TownManaPercent=GetConfigInt("Chicken","TownManaChicken");
	v_QuitLifePercent=GetConfigInt("Chicken","QuitLife");
	v_QuitManaPercent=GetConfigInt("Chicken","QuitMana");
	v_AutoDrink=GetConfigInt("Chicken","Drink");
//	v_AutoDrinkLifeTimer=GetConfigInt("Chicken","DrinkLifeTimer");
	v_AutoDrinkManaTimer=GetConfigInt("Chicken","DrinkManaTimer");
	v_DrinkRejuTimer=GetConfigInt("Chicken","DrinkRejuvTimer");
	v_PrintFailed=GetConfigInt("Chicken","PrintFailedDrinks");
	v_AutoDrinkLife=GetConfigInt("Chicken","DrinkLife");
	v_AutoDrinkMana=GetConfigInt("Chicken","DrinkMana");
    v_AutoDrinkReju=GetConfigInt("Chicken","DrinkLifeRej");
	v_AutoDrinkManaRej=GetConfigInt("Chicken","DrinkManaRej");
//KeyBindings
	cefg.Trigger=GetKeyConfig("KeySettings","Trigger");
	cefg.FastTP=GetKeyConfig("KeySettings","FastTP");
	cefg.TPPK=GetKeyConfig("KeySettings","TPPK");
	cefg.Targetlist=GetKeyConfig("KeySettings","Targetlist");
	cefg.NextTarget=GetKeyConfig("KeySettings","NextTarget");
	cefg.TestCommands=GetKeyConfig("KeySettings","TestCommands");
	cefg.Camp=GetKeyConfig("KeySettings","Camp");
	cefg.CampUnit=GetKeyConfig("KeySettings","CampUnit");
	cefg.ItemViewer=GetKeyConfig("KeySettings","ItemViewer");
	cefg.AimToggle=GetKeyConfig("KeySettings","AimToggle");
	cefg.AimSlotToggle=GetKeyConfig("KeySettings","AimSlotToggle");
    cefg.ADKey=GetKeyConfig("KeySettings","Spam");
    cefg.FlashKey=GetKeyConfig("KeySettings","Flash");
    cefg.SilentExit=GetKeyConfig("KeySettings","SilentExit");
  //  cefg.Hostile=GetKeyConfig("KeySettings","Hostile");
    cefg.FastExit=GetKeyConfig("KeySettings","FastExit");
    cefg.TeleToPlayer=GetKeyConfig("KeySettings","TeleToPlayer");
    cefg.TeleToPlayerHost=GetKeyConfig("KeySettings","TeleToPlayerHost");
    cefg.StashKey=GetKeyConfig("KeySettings","StashKey");
    cefg.InfoToggle=GetKeyConfig("KeySettings","StatInfo");
	vK_BoxKey=GetKeyConfig("KeySettings","WindowKey");
	cefg.NPC=GetKeyConfig("KeySettings","NPC");

//MH Settings
	cefg.MonsterColor=GetConfigInt("Maphack","MonsterColor");
	cefg.ChampionMonsterColor=GetConfigInt("Maphack","ChampionMonsterColor");
    cefg.DrawImunities=GetConfigInt("Maphack","DrawImunities");
    cefg.MyMissile=GetConfigInt("Maphack","MyMissile");
    cefg.FriendMissile=GetConfigInt("Maphack","FriendMissile");
    cefg.NeutralMissile=GetConfigInt("Maphack","NeutralMissile");
    cefg.EnemyMissile=GetConfigInt("Maphack","EnemyMissile");
// Screenhooks
	PlayerInfo=GetConfigInt("ScreenHooks","PlayerInfo");
//	PlayerInfoToggle=GetKeyConfig("KeySettings","PlayerInfoToggle");
//	cefg.GameInfo=GetConfigInt("ScreenHooks","StatInfo");
    cefg.DrawModifiers=GetConfigInt("ScreenHooks","DrawModifiers");


//  Enchbot
	cefg.EnchBotToggle=GetKeyConfig("Enchbot","Toggle");
	strcpy(v_EnchantMe,GetConfigStr("Enchbot","EnchMe"));
	strcpy(v_EnchantMerc,GetConfigStr("Enchbot","EnchMerc"));
	strcpy(v_EnchantAll,GetConfigStr("Enchbot","EnchAll"));
    cefg.PMOnJoin=GetConfigInt("Enchbot","PMOnJoin");
    cefg.AutoParty=GetConfigInt("Enchbot","Autoparty");
//  Settings
	v_FastTele=GetConfigInt("Settings","FastTele");
	cefg.ItemLevel=GetConfigInt("Settings","ItemLevel");
    v_ItemSockets=GetConfigInt("Settings","ItemSockets");
    ItemEthPrefix=GetConfigInt("Settings","ItemEth");
    v_MaxBPs=GetConfigInt("Settings","MaxBPs");
	v_AutoScreenShot=GetConfigInt("Settings","AutoScreenShot");

	v_BPIAS=GetConfigInt("BP","IAS");
	v_BPFCR=GetConfigInt("BP","FCR");
	v_BPFHR=GetConfigInt("BP","FHR");
	v_BPFBR=GetConfigInt("BP","FBR");
//	cefg.MaxFRW=GetConfigInt("BP","FRW");

    strcpy(cefg.ADMessage,GetConfigStr("Settings","SpamMessage"));
    cefg.FlashDelay=GetConfigInt("Settings","FlashDelay");
    cefg.PKMessage=GetConfigInt("Settings","MessageOnKill");
    strcpy(cefg.Message,GetConfigStr("Settings","OnKillMessage"));
    v_ShowQuestPackets=GetConfigInt("Settings","ShowQuestFlags");
    v_InviteMembers=GetConfigInt("Settings","InviteMembers");
    v_LootMembers=GetConfigInt("Settings","LootMembers");
    v_LogPksOver=GetConfigInt("Settings","LogPKsOver");
	*/
	strcpy(cfg.SpamNames,GetConfigStr("Settings","SpamNames"));
	/*
	v_LootMembers=GetConfigInt("Settings","AAType");

// TargetBox

	v_AimBox=GetConfigInt("AimBox","Enabled");
	v_AimBoxColor=GetConfigInt("Aimbox","Color");

	cefg.AimButton=GetKeyConfig("KeySettings","AimButton");
	cefg.AutoPK=GetKeyConfig("KeySettings","AutoPK");
	cefg.Missles=GetConfigInt("Settings","AutoPKMissles");
	cefg.AutoDelay=GetConfigInt("Settings","AimDelay")/5;
//AutoTele
	cefg.NextLevelPath=GetKeyConfig("AutoTele","NextLevel");
	cefg.LastLevelPath=GetKeyConfig("AutoTele","LastLevel");
	cefg.WPPath=GetKeyConfig("AutoTele","WP");
//Winamp
    cefg.WStop=GetKeyConfig("Winamp","Stop");
    cefg.WPlay=GetKeyConfig("Winamp","Play");
    cefg.WNext=GetKeyConfig("Winamp","Next");
    cefg.WPrev=GetKeyConfig("Winamp","Prev");
    cefg.WSong=GetKeyConfig("Winamp","PrintTitle");
    v_DrawSongTitle=GetConfigInt("Winamp","ShowTitle");
	}
*/

}
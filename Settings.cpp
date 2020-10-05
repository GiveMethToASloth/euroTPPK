#include "EuroTPPK.h"

#define _CFGFILE_ "eu.ini"

CONFIGVAR ConfigVars[] = {
  /*	{{"Anti-Flash"},				{&v_AntiFlash,					&vK_AntiFlash}},
    {{"Anti-Tppk"},					{&v_AntiTppk,					&vK_AntiTppk}},
    {{"Fast Teleport"},				{&v_FastTeleport,				&vK_FastTeleport}},
    {{"Fast Portal Open"},			{&v_FastTpOpen,					&vK_FastTpOpen}},
    {{"No Quest Box"},				{&v_NoQuestBox,					&vK_NoQuestBox}},
    {{"No TP Delay"},				{&v_NoTpDelay,					&vK_NoTpDelay}},
    {{"Full Light Radius"},			{&v_FullLightRadius,			&vK_FullLightRadius}},
    {{"Block Minimize"},			{&v_BlockMinimize,				&vK_BlockMinimize}},
    {{"Life/Mana Orbs"},			{&v_LifeManaOrbs,				&vK_LifeManaOrbs}},
    {{"Auto Reveal Automap"},		{&v_AutoRevealAutomap,			&vK_AutoRevealAutomap}},
    {{"No Screen Shake"},			{&v_NoShake,					&vK_NoShake}},
    {{"Chicken Life"},				{&v_ChickenLife,				&vK_ChickenLife}},
    {{"Chicken Mana"},				{&v_ChickenMana,				&vK_ChickenMana}},
    {{"Auto Health Pot"},			{&v_AutoLifePot,				&vK_AutoLifePot}},
    {{"Auto Mana Pot"},				{&v_AutoManaPot,				&vK_AutoManaPot}},
    {{"Left Attack"},				{&v_LeftAttack,					&vK_LeftAttack}},
    {{"Use Death Message"},			{&v_UseDeathMessage,			&vK_UseDeathMessage}},
    {{"Life/Mana Percents"},		{&v_LifeManaPercents,			&vK_LifeManaPercents}},
    {{"Show Automap Monsters"},		{&v_AutomapMonsters,			&vK_AutomapMonsters}},
    {{"Show Automap Missiles"},		{&v_AutomapMissiles,			&vK_AutomapMissiles}},
    {{"Show Hidden Monsters"},		{&v_ShowHiddenMonsters,			&vK_ShowHiddenMonsters}},
    {{"Show Hidden Items"},			{&v_ShowHiddenItems,			&vK_ShowHiddenItems}},
    {{"Auto-Party"},				{&v_AutoParty,					&vK_AutoParty}},
    {{"Right Click Swap"},			{&v_RightClickSwap,				&vK_RightClickSwap}},
    {{"Auto-Loot Members"},			{&v_AutoLoot,					&vK_AutoLoot}},
    {{"Enchant Bot"},				{&v_EnchantBot,					&vK_EnchantBot}},
    {{"Display Level Names"},		{&v_LevelNames,					&vK_LevelNames}},

    {{"Console Message Delay"},		{&v_ConsoleDelay}},
    {{"Fail To Join Delay"},		{&v_FailToJoinDelay}},
    {{"Chicken Life Percent"},		{&v_ChickenLifePercent}},
    {{"Chicken Mana Percent"},		{&v_ChickenManaPercent}},
    {{"Auto Health Pot Percent"},	{&v_AutoLifePercent}},
    {{"Auto Mana Pot Percent"},		{&v_AutoManaPercent}},
    {{"Auto Health pot Delay"},		{&v_AutoLifeDelay}},
    {{"Auto Mana Pot Delay"},		{&v_AutoManaDelay}},
    {{"Use Life Rejuvs"},			{&v_UseRejuvsLife}},
    {{"Use Mana Rejuvs"},			{&v_UseRejuvsMana}},
    {{"Death Message"},				{&v_DeathMessage}},
    {{"Automap Infos"},				{&v_AutomapInfos}},
    {{"Monster Colors"},			{&v_MonsterColors}},
    {{"Item Colors"},				{&v_ItemColors}},
    {{"Flash Cycle Delay"},			{&v_FlashCycleDelay}},
    {{"Target List Delay"},			{&v_TargetListDelay}},
    {{"Player Missile Color"},		{&v_PlayerMissileColor}},
    {{"Hostile Missile Color"},		{&v_HostileMissileColor}},
    {{"Party Missile Color"},		{&v_PartyMissileColor}},
    {{"Normal Missile Color"},		{&v_NormalMissileColor}},
    {{"Normal Monster Color"},		{&v_NormalMonsterColor}},
    {{"Champion Monster Color"},	{&v_ChampionMonsterColor}},
    {{"Ethereal Item Prefix"},		{&v_EtherealPrefix}},
    {{"Ethereal Item Postfix"},		{&v_EtherealPostfix}},
    {{"Show Socket Numbers"},		{&v_ShowSockets}},
    {{"Show Item Levels"},			{&v_ShowItemLevel}},
    {{"Last Game Name"},			{&v_LastGameName}},
    {{"Enchant Me Phrase"},			{&v_EnchantMe}},
    {{"Enchant Merc Phrase"},		{&v_EnchantMerc}},
    {{"Enchant All Phrase"},		{&v_EnchantAll}},
    {{"Hostile Player Color"},		{&v_HostilePlayerColor}},
    {{"Target Player Color"},		{&v_TargetPlayerColor}},
    {{"Display Inventory Gold"},	{&v_InventoryGold}},
    {{"Range Check"},				{&v_UnitCheck}},
    */
    // VARS

    {{"Trigger Character"},			{&v_TriggerChar}},
    {{"Auto Drink"},				{&v_AutoDrink}},
    {{"Print Failed Drinks"},		{&v_PrintFailed}},

    {{"Drink Life Percent"},			{&v_AutoDrinkLife}},
    {{"Drink Reju Percen"},				{&v_AutoDrinkReju}},
    {{"Drink Mana Percent"},			{&v_AutoDrinkMana}},

    {{"Drink Life Timer"},			{&v_DrinkLifeTimer}},
    {{"Drink Mana Timer"},			{&v_DrinkManaTimer}},
    {{"Drink Reju Timer"},			{&v_DrinkRejuTimer}},

    {{"Town Life Percent"},			{&v_TownLifePercent}},
    {{"Town Mana Percent"},			{&v_TownManaPercent}},

    {{"Quit Life Percent"},			{&v_QuitLifePercent}},
    {{"Quit Mana Percent"},			{&v_QuitManaPercent}},

    {{"Hostile Chicken"},			{&v_HostileChicken}},
    {{"Aim Chicken"},				{&v_AimChicken}},

    {{"Chicken Mana"},			{&v_EnchantMe}},
    {{"Chicken Rejuvenation"},	{&v_EnchantMe}},
    {{"Chicken Life"},			{&v_EnchantMe}},

    {{"Enchant Me Phrase"},			{&v_EnchantMe}},
    {{"Enchant Merc Phrase"},		{&v_EnchantMerc}},
    {{"Enchant All Phrase"},		{&v_EnchantAll}},
    {{"Enchant AutoParty"},			{&v_EnchAutoParty}},
    {{"Notify On Join"},			{&v_NotifyJoin}},

    {{"Draw Song Title"},			{&v_DrawSongTitle}},

    // Do below in cars
    {{"Normal Monster Color"},		{&v_MonsterColor}},
    {{"Champion Monster Color"},	{&v_ChampionMonsterColor}},
    {{"Player Missile Color"},		{&v_MyMissile}},
    {{"Hostile Missile Color"},		{&v_EnemyMissile}},
    {{"Party Missile Color"},		{&v_FriendMissile}},
    {{"Normal Missile Color"},		{&v_NeutralMissile}},
    {{"Show Monster Imunities"},	{&v_DrawImunities}},

    {{"Aim Box"},					{&v_AimBox}},
    {{"Aim Box Color"},				{&v_AimBoxColor}},

    {{"Breakpoint IAS"},			{&v_BPIAS}},
    {{"Breakpoint FCR"},			{&v_BPFCR}},
    {{"Breakpoint FBR"},			{&v_BPFBR}},
    {{"Breakpoint FHR"},			{&v_BPFHR}},

    {{"Show Item Level"},			{&v_ItemLevel}},
    {{"Show Item Sockets"},			{&v_ItemSockets}},
    {{"Show Etheral Prefix"},		{&v_ItemEthPrefix}},
    {{"Flash Cycle Delay"},			{&v_FLASHCYCLE}},
    {{"Aim Cycle Delay"},			{&v_AIMCYCLE}},
    {{"Auto PK Missiles"},			{&v_AutoPKMissiles}},
    {{"Show Quest Packets"},			{&v_ShowQuestPackets}},
    {{"Invite Members"},				{&v_InviteMembers}},
    {{"Loot Members"},				{&v_LootMembers}},
    {{"Log PKs Over Level"},			{&v_LogPksOver}},
    {{"Spammer Names"},				{&v_SpamNames}},
    {{"Auto Screenshot"},			{&v_AutoScreenShot}},
    {{"Max Breakpoints"},			{&v_MaxBPs}},
    {{"Fast Teleport"},				{&v_FastTele}},
    {{"Auto Aim Type"},				{&v_AAType}},

    {{"Use Death Message"},			{&v_UseDeathMessage}},
    {{"Death Message"},				{&v_DeathMessage}},
    {{"Spam Message"},				{&v_SpamMessage}},

    // KEYS

    {{"TP To Town"},				{&vK_FastTP}},
    {{"TPPK Go"},					{&vK_TPPKGo}},
    {{"Camp"},						{&vK_Camp}},
    {{"Camp Target Player"},		{&vK_CampTarget}},

    {{"Target Box"},				{&vK_TargetBox}},
    {{"Next Target"},				{&vK_NextTarget}},

    {{"Auto Aim Toggle"},			{&vK_AutoAimToggle}},
    {{"Auto Aim Button Toggle"},	{&vK_AimKeyToggle}},

    {{"Flash Target"},				{&vK_FlashTarget}},
    {{"View Targets Items"},		{&vK_ItemViewer}},
    {{"Player Info Box"},			{&vK_DrawPlayerInfo}},
    {{"Spam Button"},				{&vK_SpamButton}},
    {{"Silent Exit"},				{&vK_SilentExit}},
    {{"Normal Exit"},				{&vK_NormalExit}},

    {{"Walk Player"},				{&vK_WalkPlayer}},
    {{"Walk and Hostile Player"},	{&vK_WalkAndHostile}},

    {{"Draw Player Hooks"},			{&vK_DrawPlayerHooks}},
    {{"Aim and Attack Target"},		{&vK_AimAndAttack}},
    {{"Auto PK"},					{&vK_AutoPK}},
    {{"Stash Button"},				{&vK_OpenStash}},

    {{"Box Key"},					{&vK_BoxKey}},
    {{"Move Box Key"},    {&vK_MoveBoxKey}},
    {{"NPC Add Button"},			{&vK_NPCAdd}},

    {{"Tele to Next Level"},		{&vK_TeleNext}},
    {{"Tele to Prev Level"},		{&vK_TelePre}},
    {{"Tele to Way Point"},			{&vK_TeleWP}},

    {{"Enchant Bot Toggle"},		{&vK_EnchbotToggle}},
    //{{"Enchant Bot"},				{&v_EnchantBot,					&vK_EnchantBot}},

    {{"Next Song"},					{&vK_NextSong}},
    {{"Previous Song"},				{&vK_PrevSong}},
    {{"Play Song"},					{&vK_PlaySong}},
    {{"Stop Song"},					{&vK_StopSong}},
    {{"Print Song Title"},			{&vK_PrintSong}},
};

DWORD ReadFileD(HANDLE hFile, LPVOID buf, DWORD len)
{
  DWORD numdone = 0;
  ReadFile(hFile, buf, len, &numdone, NULL);
  return numdone;
}
LPSTR ReadFileLine(LPSTR lpBuffer, INT nLength, HANDLE hFile)
{
  char ch, * p = lpBuffer;
  while (--nLength)
  {
    if (!ReadFileD(hFile, &ch, 1)) break;
    if ((*p++ = ch) == '\n') break;
  }
  *p = 0;
  return lpBuffer[0] ? lpBuffer : 0;
}

BOOL isescapechar(INT nChar)
{
  if (nChar == '\0')
    return TRUE;

  if (nChar == '\r')
    return TRUE;

  if (nChar == '\n')
    return TRUE;

  return FALSE;
}

BOOL ReadDefinesFile(CArrayEx<PDEFINEVAR, PDEFINEVAR>* pDefines, INT nSize)
{
  PDEFINEVAR Var;
  HANDLE hFile;
  CHAR szFileLine[200] = "";
  CHAR szLineVars[2][0x40] = { "" };
  CHAR szPath[MAX_PATH] = "";
  INT nPos = 0, nLoc = 0;
  char Buffer[512];

  if (nSize < 26)
    return FALSE;

  //GetModuleDirectory(szPath, MAX_PATH);
  //strcat(szPath, "\\eu.ini");
  sprintf_s(szPath, "%s\\eu.ini", szModulePath);

  hFile = CreateFileA(szPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  if (hFile == INVALID_HANDLE_VALUE)
    return FALSE;

  while (ReadFileLine(szFileLine, 200, hFile))
  {
    memset(szLineVars[0], 0, 0x40);
    memset(szLineVars[1], 0, 0x40);

    if (strlen(szFileLine) < 2)
      continue;

    __try
    {
      for (INT i = 0; i < (INT)strlen(szFileLine); i++)
      {
        if (szFileLine[i] == '/' && szFileLine[i + 1] == '/')
          break;

        if (szFileLine[i] == ':')
        {
          nPos++;
          nLoc = 0;

          while (++i < (INT)strlen(szFileLine) && isspace(szFileLine[i]));
        }

        if (!isescapechar(szFileLine[i]))
        {
          szLineVars[nPos][nLoc] = szFileLine[i];
          nLoc++;
        }
      }
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
      sprintf(Buffer, "Error during Defines string parsing, string %s", szFileLine);
      //PrintMessage(Buffer,8);
      //PrintConsoleString("ÿc1Error during Defines string parsing, string %s", szFileLine);
    }

    nLoc = nPos = 0;

    __try
    {
      Var = new DEFINEVAR;
      Var->Name = new CHAR[strlen(szLineVars[0]) + 1];
      Var->StringReplace = new CHAR[strlen(szLineVars[1]) + 1];

      memset(Var->Name, 0, strlen(szLineVars[0]) + 1);
      memset(Var->StringReplace, 0, strlen(szLineVars[1]) + 1);

      memcpy(Var->Name, szLineVars[0], strlen(szLineVars[0]));
      memcpy(Var->StringReplace, szLineVars[1], strlen(szLineVars[1]));

      pDefines[_strlwr(szLineVars[0])[0] - 'a'].Add(Var);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
      sprintf(Buffer, "Error during defines var adding, string %s", szFileLine);
      //PrintMessage(Buffer,8);
      //PrintConsoleString("ÿc1Error during defines var adding, string %s", szFileLine);
    }
  }

  CloseHandle(hFile);

  return TRUE;
}

BOOL ReplaceDefineVars(LPSTR lpString, CArrayEx<PDEFINEVAR, PDEFINEVAR>* pDefines)
{
  CArrayEx<PDEFINEVAR, PDEFINEVAR> Def;
  CHAR szTemp[0x40] = "";

  memcpy(szTemp, lpString, strlen(lpString));
  if (_strlwr(szTemp)[0] < 'a' || _strlwr(szTemp)[0] > 'z')
    return FALSE;

  Def = pDefines[_strlwr(szTemp)[0] - 'a'];

  for (INT i = 0; i < Def.GetSize(); i++)
  {
    if (!_stricmp(lpString, Def[i]->Name))
    {
      sprintf(lpString, "%s", Def[i]->StringReplace);
      return TRUE;
    }
  }

  return TRUE;
}

BOOL ReadConfigFile()
{
  CArrayEx<PDEFINEVAR, PDEFINEVAR> Defines[26];
  CHAR szPath[MAX_PATH] = "";
  CHAR szFileLine[400] = "";
  HANDLE hFile;
  INT nLine = 0;
  sprintf_s(szPath, "%s\\eu.ini", szModulePath);

  //GetModuleDirectory(szPath, MAX_PATH);
  //strcat(szPath, "eu.ini");

  hFile = CreateFileA(szPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  if (hFile == INVALID_HANDLE_VALUE)
    return FALSE;

  ReadDefinesFile(Defines, 26);
  char Buffer[512];
  while (ReadFileLine(szFileLine, 400, hFile))
  {
    INT nVarPos = 0, nLoc = 0, nArrayPos = 0;
    CHAR szVarName[40] = "", szArray[2][40] = { "" }, szValues[4][400] = { "" };
    BOOL VarSet = FALSE, ArraySet = FALSE, ValueSet = FALSE;
    nLine++;

    for (INT i = 0; i < (INT)strlen(szFileLine); i++)
    {
      if (!strncmp(szFileLine, "//", 2))
        break;

      if (!VarSet)
      {
        if (szFileLine[i] == '[' || szFileLine[i] == ':')
        {
          VarSet = TRUE;
        }
        else
        {
          szVarName[i] = szFileLine[i];
          continue;
        }
      }

      if (szFileLine[i] == '[')
      {
        nLoc = 0;
        ArraySet++;
        for (INT j = i + 1; j < (INT)strlen(szFileLine); j++)
        {
          if (szFileLine[j] == ']')
          {
            nArrayPos++;
            break;
          }

          szArray[nArrayPos][nLoc] = szFileLine[j];
          nLoc++;
        }
      }

      if (szFileLine[i] == ':')
      {
        while (++i < (INT)strlen(szFileLine) && isspace(szFileLine[i]));
        ValueSet++;

        nLoc = 0;
        for (INT j = i; j < (INT)strlen(szFileLine); j++)
        {
          if (szFileLine[j] == ',')
          {
            nLoc = 0;
            nVarPos++;
            ValueSet++;

            while (++j < (INT)strlen(szFileLine) && isspace(szFileLine[j]));
          }

          if (!isescapechar(szFileLine[j]))
          {
            szValues[nVarPos][nLoc] = szFileLine[j];
            nLoc++;
          }
        }

        break;
      }
    }

    for (INT i = 0; i < ArraySet; i++)
      ReplaceDefineVars(szArray[i], Defines);
    for (INT i = 0; i < ValueSet; i++)
      ReplaceDefineVars(szValues[i], Defines);

    for (INT i = 0; i < ArraySize(ConfigVars); i++)
    {
      if (!_stricmp(ConfigVars[i].VarName[0], szVarName))
      {
        PCONFIGVAR pVar = ArraySet ? new CONFIGVAR : &ConfigVars[i];
        if (ArraySet)
          memset(pVar, 0, sizeof(CONFIGVAR));

        for (INT j = 0; j < ValueSet; j++)
        {
          if (szValues[j][0] == '"')
          {
            for (INT k = (INT)strlen(szValues[j]) - 1; k > 0; k--)
              if (szValues[j][k] == '"')
                szValues[j][k] = 0;

            if (pVar->Buffers[j])
            {
              LPSTR* lpBuffer = (LPSTR*)pVar->Buffers[j];
              *lpBuffer = new CHAR[strlen(szValues[j] + 1) + 1];
              memset(*lpBuffer, 0, strlen(szValues[j] + 1) + 1);
              memcpy(*lpBuffer, szValues[j] + 1, strlen(szValues[j] + 1) + 1);
            }
            else
            {
              pVar->Buffers[j] = new CHAR[strlen(szValues[j] + 1) + 1];
              memset(pVar->Buffers[j], 0, strlen(szValues[j] + 1) + 1);
              memcpy(pVar->Buffers[j], szValues[j] + 1, strlen(szValues[j] + 1));
            }
          }
          else if (!strncmp(szValues[j], "0x", 2))
          {
            LPSTR t = "";
            if (!pVar->Buffers[j])  pVar->Buffers[j] = new INT;
            *(PINT)pVar->Buffers[j] = strtoul(szValues[j] + 2, &t, 16);
          }
          else
          {
            if (!pVar->Buffers[j]) pVar->Buffers[j] = new INT;
            *(PINT)pVar->Buffers[j] = atoi(szValues[j]);

            if (atoi(szValues[j]) == 0 && strlen(szValues[j]) > 1)

              sprintf(Buffer, "Warning: Undefined string in configuration file (Line %d) %s", nLine, szValues[j]);
            //PrintMessage(Buffer,1);
          }
        }

        if (ArraySet)
        {
          CArrayEx<PCONFIGVAR, PCONFIGVAR>* ArrayArray = (CArrayEx<PCONFIGVAR, PCONFIGVAR>*)ConfigVars[i].Buffers[0];
          ArrayArray->Add(pVar);

          pVar->VarName[0] = new CHAR[strlen(szArray[0])];
          pVar->VarName[1] = new CHAR[strlen(szArray[1])];

          sprintf(pVar->VarName[0], "%s", szArray[0]);
          sprintf(pVar->VarName[1], "%s", szArray[1]);
        }

        break;
      }
    }
  }

  CloseHandle(hFile);

  return TRUE;
}
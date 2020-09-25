#include "EuroTPPK.h"
#include "Area.h"
#define QUANTITY_STAT_ID	70

BOOL SayOverHead(LPSTR lpMessage, ...)
{
	CHAR szBuffer[0x400] = "";
	va_list Args;

	if (!GameReady())
		return FALSE;

	va_start(Args, lpMessage);
	vsprintf(szBuffer, lpMessage, Args);
	va_end(Args);

	if (lpMessage && lpMessage[0])
	{
		UnitAny* pUnit = D2CLIENT_GetPlayerUnit();
		OverheadMsg* pMsg = D2COMMON_GenerateOverheadMsg(NULL, lpMessage, *p_D2CLIENT_OverheadTrigger);
		if (pMsg)
		{
			D2COMMON_FixOverheadMsg(pMsg, NULL);
			pUnit->pOMsg = pMsg;
		}
	}
	return TRUE;
}

BOOL Say(LPSTR lpMessage, ...)
{
	CHAR szBuffer[0x400] = "";
	va_list Args;

	if (!GameReady())
		return FALSE;

	va_start(Args, lpMessage);
	vsprintf(szBuffer, lpMessage, Args);
	va_end(Args);

	LPBYTE aPacket = new BYTE[(INT)strlen(szBuffer) + 6];
	memset(aPacket, 0, (INT)strlen(szBuffer) + 6);

	aPacket[0] = 0x15;
	*(LPWORD)&aPacket[1] = 1;
	memcpy(aPacket + 3, szBuffer, (INT)strlen(szBuffer));

	D2NET_SendPacket((INT)strlen(szBuffer) + 6, 1, aPacket);
	delete[] aPacket;

	return TRUE;
}
void GameLoopPatch()
{
	if (GameReady())
		TimerTick();
}

void GameEndPatch()
{
	SetAllFalse();
	LevelNames.RemoveAll();
}

/*
if (D2CLIENT_GetAutomapSize()) {
xpos += 1;
ypos -= 5;
}
xpos = (xpos + D2CLIENT_xyAutomapDraw.x -  * D2CLIENT_nAutomapScale;
ypos = (ypos + D2CLIENT_xyAutomapDraw.y +  * D2CLIENT_nAutomapScale;
int xpos2 = ((ypos*2)+xpos)/32;
int ypos2 = ((ypos*2)-xpos)/32;
*/

VOID AutomapToScreen(POINT* ptPos, int xpos, int ypos)
{
	if (D2CLIENT_GetAutomapSize()) {
		xpos += 1;
		ypos -= 5;
	}
	xpos = (xpos + (*p_D2CLIENT_Offset).x + 8) * (*(INT*)p_D2CLIENT_Divisor);
	ypos = (ypos + (*p_D2CLIENT_Offset).y - 8) * (*(INT*)p_D2CLIENT_Divisor);
	int xpos2 = ((ypos * 2) + xpos) / 32;
	int ypos2 = ((ypos * 2) - xpos) / 32;
}

void AutomapToScreenRelative(POINT* pos, int x, int y)
{
	x += D2CLIENT_GetMouseXOffset();
	y += D2CLIENT_GetMouseYOffset();
	AutomapToScreen(pos, y * 2 + x, y * 2 - x);
}

/*
VOID ScreenToAutomap(POINT *ptPos, int x, int y)
{
	ptPos->x = ((x - y)/2/(*(INT*)p_D2CLIENT_Divisor))-(*p_D2CLIENT_Offset).x+8;
	ptPos->y = ((x + y)/4/(*(INT*)p_D2CLIENT_Divisor))-(*p_D2CLIENT_Offset).y-8;
	if(D2CLIENT_GetAutomapSize())
	{
		--ptPos->x;
		ptPos->y += 5;
	}
}

*/

DWORD attack = 0x6FB0B050 - 0x6fab0000;
void __declspec(naked) __fastcall AttackToWrapper(DWORD Buf) {
	__asm {
		push 0 // EBX was ever zero!!11
		push ecx
		call attack
		retn
	}
}
DWORD GetExpLeft() {
	UnitAny* pUnit = D2CLIENT_GetPlayerUnit();

	DWORD Experience[] =
	{
		0, 500, 1500, 3750, 7875, 14175, 22680, 32886, 44396, 57715, 72144, 90180, 112725, 140906, 176132, 220165, 275207, 344008,
		430010, 537513, 671891, 839864, 1049830, 1312287, 1640359, 2050449, 2563061, 3203826, 3902260, 4663553, 5493363,
		6397855, 7383752, 8458379, 9629723, 10906488, 12298162, 13815086, 15468534, 17270791, 19235252, 21376515, 23710491,
		26254525, 29027522, 32050088, 35344686, 38935798, 42850109, 47116709, 51767302, 56836449, 62361819, 68384473, 74949165,
		82104680, 89904191, 98405658, 107672256, 117772849, 128782495, 140783010, 153863570, 168121381, 183662396, 200602101,
		219066380, 239192444, 261129853, 285041630, 311105466, 339515048, 370481492, 404234916, 441026148, 481128591, 524840254,
		572485967, 624419793, 681027665, 742730244, 809986056, 883294891, 963201521, 1050299747, 1145236814, 1248718217,
		1361512946, 1484459201, 1618470619, 1764543065, 1923762030, 2097310703, 2286478756, 2492671933, 2717422497, 2962400612,
		3229426756, 3520485254
	};

	return Experience[D2COMMON_GetUnitStat(pUnit, 0x0C, 0)];
	//D2COMMON_GetUnitState3(2, D2COMMON_GetUnitState2(pUnit, 0x0C, 0));
}

void AttackTo(DWORD PlayerStruct) {
	attack = 0x6FB0B050 - 0x6fab0000 + (DWORD)LoadLibrary("D2Client.dll");
	byte Attack[28] = { 0x46,00,00,00, // RIGHT 0x46 LEFT 0xE5
			0x00,00,00,00, // PLAYER STRUCT HIER EINTRAGEN
			0x00,00,00,00, // Unused?!
			0x00,00,00,00, // X Coordinates.. (in WORD)
			0x00,00,00,00, // Y Coordinates.. (in WORD)
			0x03,00,00,00, // Right Attack?
			0x04,00,00,00, // Dito?
	};
	*(DWORD*)&Attack[0x04] = *(DWORD*)0x6FBCC3D0;

	*(WORD*)&Attack[12] = ((UnitAny*)PlayerStruct)->pPath->xPos;
	*(WORD*)&Attack[16] = ((UnitAny*)PlayerStruct)->pPath->yPos;

	AttackToWrapper((DWORD)Attack);
}

void AttackToTele(WORD x, WORD y) {
	byte Attack[28] = { 0x46,00,00,00,
			0x00,00,00,00, // PLAYER STRUCT HIER EINTRAGEN
			0x00,00,00,00, // Unused?!
			0x00,00,00,00, // X Coordinates.. (in WORD)
			0x00,00,00,00, // Y Coordinates.. (in WORD)
			0x03,00,00,00, // Constant?
			0x04,00,00,00, // Dito?
	};
	*(DWORD*)&Attack[0x04] = *(DWORD*)0x6FBCC3D0;

	*(WORD*)&Attack[12] = x;
	*(WORD*)&Attack[16] = y;

	AttackToWrapper((DWORD)Attack);
}
void TeleportToTele(long x, long y) {
	BYTE Packet1[] = { 0x3c,0x36,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF };
	SendGAMEPacket(Packet1, sizeof(Packet1));

	AttackToTele(x, y);
}
RosterUnit* FindPartyByName(LPSTR szName)
{
	for (RosterUnit* pUnit = *p_D2CLIENT_PlayerUnitList; pUnit; pUnit = pUnit->pNext)
		if (!_stricmp(szName, pUnit->szName))
			return pUnit;

	return NULL;
}

BOOL SetSkill(WORD wSkillId, BOOL bLeft) //used
{
	if (!D2CLIENT_GetPlayerUnit()) return FALSE;

	BYTE aPacket[9];

	aPacket[0] = 0x3C;
	*(WORD*)&aPacket[1] = wSkillId;
	aPacket[3] = 0;
	aPacket[4] = (bLeft) ? 0x80 : 0;
	*(DWORD*)&aPacket[5] = 0xFFFFFFFF;

	D2NET_SendPacket(9, 1, aPacket);
	return TRUE;
}
void FlashPlayer(DWORD ID) {
	BYTE UPDATE[9] = { 0x4b, 0,0,0,0,     0,0,0,0 };
	memcpy(&UPDATE[5], &ID, 4);
	SendGAMEPacket(UPDATE, 9);
}

void PrintLists(void)
{
	char Buffer[200];
	sprintf(Buffer, ":: Friends: %d  Enemys: %d Spammers: %d", PlayerFriendList->GetItemCount(), PlayerEnemyList->GetItemCount(), PlayerSpamList->GetItemCount());
	PrintMessage(Buffer, FONTCOLOR_WHITE);
}

bool IsInventoryOpen() {
	int State = *(DWORD*)0x6FBCC1D0; //  1.11 6FBCC3E4
	if (State == 1) return true;
	else false;
	return false;
}
DWORD GUI = 0x6FB52E90; // 1.11 6FB1A5B0

void  ToggleInventory(bool on) {
	if (on)
		if (IsInventoryOpen() == false)
			_asm CALL GUI
	if (!on)
		if (IsInventoryOpen())
			_asm CALL GUI
}
char* ReplaceString(char* source, char* old, char* newtext)
{
	char* original = new char[strlen(source)];
	strcpy(original, source);
	char* temp = new char[256];
	int old_length = strlen(old);
	int i, j, k, location = -1;
	for (i = 0; source[i] && (location == -1); ++i)
		for (j = i, k = 0; source[j] == old[k]; j++, k++)
			if (!old[k + 1])
				location = i;
	if (location != -1)
	{
		for (j = 0; j < location; j++)
			temp[j] = source[j];
		for (i = 0; newtext[i]; i++, j++)
			temp[j] = newtext[i];
		for (k = location + old_length; source[k]; k++, j++)
			temp[j] = source[k];
		temp[j] = NULL;
		for (i = 0; source[i] = temp[i]; i++);
	}
	delete original;
	return temp;
}

DWORD __declspec(naked) IsExpansion() {
	__asm {
		//MOV EAX,DWORD PTR DS:[6FBCA2F4]
		mov eax, 0x6FBB330C/*6FBCA2F4*/
		mov eax, [eax]
		retn
	}
}

GameStructInfo* GetGameInfo() {
	DWORD Addresse = 0x11B908/*10D618*/; // 0x10D618+6FAB0000 6FBBD618 ||6FBCB908-6FAB0000
	Addresse = Addresse + (DWORD)LoadLibrary("D2Client.dll");
	GameStructInfo* Returne;
	__asm {
		push eax
		mov eax, [Addresse]
		mov eax, [eax]
		mov[Returne], eax
		pop eax
	}
	return Returne;
}

void PrintChat(char* Message) {
	byte CharPacket[100] = {};
	sprintf((char*)CharPacket, "%c%c%c%s%c%c%c", 0x15, 0x01, 0x00, Message, 0x00, 0x00, 0x00);
	SendGAMEPacket(CharPacket, strlen(Message) + 6);
}

void Tele(WORD x, WORD y) {
	DWORD ID;
	BYTE TELE[5] = { 0x5f, 0,0,   0,0 };
	BYTE UPDATE[9] = { 0x4b, 0,0,0,0,     0,0,0,0 };
	ID = GetPlayerID();
	memcpy(&UPDATE[5], &ID, 4);
	memcpy(&TELE[1], &x, 2);
	memcpy(&TELE[3], &y, 2);
	SendGAMEPacket(TELE, 5);
	SendGAMEPacket(UPDATE, 9);
}

DWORD GetTileLevelNo(Room2* lpRoom2, DWORD dwTileNo)
{
	for (RoomTile* pRoomTile = lpRoom2->pRoomTiles; pRoomTile; pRoomTile = pRoomTile->pNext)
	{
		if (*(pRoomTile->nNum) == dwTileNo)
			return pRoomTile->pRoom2->pLevel->dwLevelNo;
	}

	return NULL;
}

Level* GetLevel(DWORD dwLevelNo)
{
	for (Level* pLevel = D2CLIENT_GetPlayerUnit()->pAct->pMisc->pLevelFirst; pLevel; pLevel = pLevel->pNextLevel)
		if (pLevel->dwLevelNo == dwLevelNo)
			return pLevel;

	return D2COMMON_GetLevel(D2CLIENT_GetPlayerUnit()->pAct->pMisc, dwLevelNo);
}

void DrawBlob(int xpos, int ypos, int col) {
	static char blines[][2] = { 0,-2, 4,-4, 8,-2, 4,0, 8,2, 4,4, 0,2, -4,4, -8,2, -4,0, -8,-2, -4,-4, 0,-2 };
	for (int i = 0; i < ARRAYSIZE(blines) - 1; i++) {
		D2GFX_DrawLine(xpos + blines[i][0], ypos + blines[i][1], xpos + blines[i + 1][0], ypos + blines[i + 1][1], col, 0xff);
	}
}

INT GetSkill(WORD wSkillId)
{
	if (!D2CLIENT_GetPlayerUnit()) return 0;

	for (Skill* pSkill = D2CLIENT_GetPlayerUnit()->pInfo->pFirstSkill; pSkill; pSkill = pSkill->pNextSkill)
		if (pSkill->pSkillInfo->wSkillId == wSkillId)
			return D2COMMON_GetSkillLevel(D2CLIENT_GetPlayerUnit(), pSkill, TRUE);

	return 0;
}

int MakeParameter(char* szInput, char** argv, char splitchar, bool bSkipQuote) {
	char* p = szInput;
	int i = 0;
	while (*szInput != '\0') {
		bool bQuoteOn = FALSE;
		while ((*szInput != splitchar || bQuoteOn) && *szInput != '\0') {
			if (*szInput == '\"' || *szInput == '\'' || *szInput == '´' || *szInput == '`')
				if (bSkipQuote)
					bQuoteOn = !bQuoteOn;
			szInput++;
		}
		if (*szInput != '\0')
			*szInput++ = '\0'; //seperate char-arrays
		argv[i++] = p; //set pointer to parameter
		++p += (szInput - p);
	} //adjust p to next parameter
	return i;
}

// Getting Distance from units.
DWORD GetDistance(DWORD x1, DWORD y1, DWORD x2, DWORD y2) {
	return (DWORD)sqrt((double)((((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)))));
}

DWORD GetDistanceSquared(DWORD x1, DWORD y1, DWORD x2, DWORD y2) {
	return (DWORD)sqrt((double)(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2))));
}

//Getting my position
POINT GetPosition() {
	POINT mp;
	UnitAny* PlayerUnit = D2CLIENT_GetPlayerUnit();
	mp.x = PlayerUnit->pPath->xPos;
	mp.y = PlayerUnit->pPath->yPos;
	return mp;
}
int GetPercent(DWORD Current, DWORD Max) {
	float Cur1 = (int)Current;
	float Max1 = (int)Max;
	return (Cur1 / Max * 100);
}
/*
 void ExitGame() {
DWORD ExitAddr=(DWORD)LoadLibrary("D2Client.dll")+0x7AB00;
		 __asm {
			call ExitAddr
		 }
 }*/
 //Getting Mouse Positon
void GetD2MousePos(POINT& Pointer) {
	typedef unsigned short(__fastcall* pPos)();

	DWORD MouseX = D2CLIENT_MouseX;
	DWORD MouseY = D2CLIENT_MouseY;
	pPos pPosX = (pPos)MouseY;
	pPos pPosY = (pPos)MouseX;
	Pointer.x = pPosX();
	Pointer.y = pPosY();
}
void HoldRightUp(long X, long Y) {
	SendMessage((HWND)D2GFX_GetHwnd(), WM_RBUTTONUP, 0, MAKELONG(X, Y));
}

//id and name converting

void Hostile(DWORD ID) {
	BYTE Hostile[7] = { 0x5d,0x04,0x01,0,0,0,0 };
	*(DWORD*)&Hostile[3] = ID;
	SendGAMEPacket(Hostile, sizeof(Hostile));
}

void HostileAll()
{
	int i;
	RosterUnit* pUnit = (RosterUnit*)*(DWORD*)PlayerRoster;
	BYTE Hostile[7] = { 0x5d,0x04,0x01,0,0,0,0 };

	/*if (GetLevelByN(D2CLIENT_GetPlayerUnit()->pPlayerData->szName) > 8) {
		for (i = 0; pUnit != NULL; i++)
		{
			if (pUnit->dwUnitId != D2CLIENT_GetPlayerUnit()->dwUnitId)
				if (pUnit->wLevel >= 9)
				{
					*(DWORD*)&Hostile[3] = pUnit->dwUnitId;
					SendGAMEPacket(Hostile, sizeof(Hostile));
				}
			pUnit = pUnit->pNext;
		}
		UnhostMembers();
	}*/
}
void UnhostMembers()
{
	/*int i;
	RosterUnit* pUnit = (RosterUnit*)*(DWORD*)PlayerRoster;
	BYTE UnHostile[7] = { 0x5d,0x04,0x00,0,0,0,0 };
	for (i = 0; pUnit != NULL; i++)
	{
		if (CheckPlayerFriend(GetNameByID(pUnit->dwUnitId)))
		{
			*(DWORD*)&UnHostile[3] = pUnit->dwUnitId;
			SendGAMEPacket(UnHostile, sizeof(UnHostile));
		}
		pUnit = pUnit->pNext;
	}*/
}

//PrintMessage Command
void PrintMessage(char* Message, char Color)
{
	typedef void(_stdcall* pPrint)(wchar_t* Text, char Color);
	pPrint Print = (pPrint)(DWORD)(0x6FB21740 - 0x6fab0000 + (DWORD)LoadLibrary("D2Client.dll"));
	wchar_t Buffer[0x130];
	MultiByteToWideChar(0, 1, Message, 100, Buffer, 100);
	Print(Buffer, Color);
};
void PrintMessageBottomLeft(char* Message, char Color)
{
	typedef void(_stdcall* pPrint)(wchar_t* Text, char Color);
	pPrint Print = (pPrint)(DWORD)(0x6FB21500 - 0x6fab0000 + (DWORD)LoadLibrary("D2Client.dll"));
	wchar_t Buffer[0x130];
	MultiByteToWideChar(0, 1, Message, 100, Buffer, 100);
	Print(Buffer, Color);
};

//Draw Text To Screen Permanent
VOID DrawTextToScreen(char* szwText, int x, int y, int color, int font) {
	wchar_t Buffer[100];

	MultiByteToWideChar(0, 1, szwText, 50, Buffer, 100);
	DWORD dwOld = D2WIN_SetTextSize(font);
	//DWORD dwXLength = D2WIN_GetTextLength(Buffer);
	D2WIN_DrawText(Buffer, x, y, color, 0);
	D2WIN_SetTextSize(dwOld);
}

//DWORD GetClientHandle() {
//return (DWORD)LoadLibrary("D2Client.dll");
//}
//
//int __declspec(naked) D2CLIENT_GetPlayerXOffset2() {
//	__asm {
//			call GetClientHandle
//			add eax, 0x5D650
//			call eax
//			ret
//	}
//}
//
//int __declspec(naked) D2CLIENT_GetPlayerYOffset2() {
//	__asm {
//			call GetClientHandle
//			add eax, 0x5D670
//			call eax
//			ret
//	}
//}

void  MapToScreenCoords(POINT& rMapPosition)
{
	D2COMMON_MapToAbsScreen(&rMapPosition.x, &rMapPosition.y);
	rMapPosition.x -= D2CLIENT_GetMouseXOffset();
	rMapPosition.y -= D2CLIENT_GetMouseYOffset();
}
void ScreenToAutomapRelative(POINT* pos, int x, int y)
{
	x += D2CLIENT_GetMouseXOffset();
	y += D2CLIENT_GetMouseYOffset();
	ScreenToAutomap(pos, y * 2 + x, y * 2 - x);
}
//
/*Level* GetLevel(DWORD dwLevelNo)
{
	for(Level* pLevel = D2CLIENT_GetPlayerUnit()->pAct->pMisc->pLevelFirst; pLevel; pLevel = pLevel->pNextLevel)
		if (pLevel->dwLevelNo == dwLevelNo)
			return pLevel;

	return D2COMMON_GetLevel(D2CLIENT_GetPlayerUnit()->pAct->pMisc, dwLevelNo);
}*/
//

void fpEnumUnits(fp EnumFunction, DWORD Type) {
	Level* pLevel = GetLevel(D2CLIENT_GetPlayerUnit()->pAct->pMisc->pLevelFirst->dwLevelNo);

	//(//for(Room2 *pRoom2 = pLevel->pRoom2First;pRoom2;pRoom2=(Room2*)pRoom2->pRoom2Other) { // nin
	for (Room2* pRoom2 = pLevel->pRoom2First; pRoom2; pRoom2 = (Room2*)pRoom2->pRoom2Next) {
		for (Room1* pRoom1 = pRoom2->pRoom1; pRoom1; pRoom1 = pRoom1->pRoomNext) {
			//	for(UnitAny* pUnit = pRoom1->pUnitFirst;pUnit;pUnit=pUnit->pListNext) {
			for (UnitAny* pUnit = pRoom2->pRoom1->pUnitFirst; pUnit; pUnit = pUnit->pListNext) {
				if (pUnit)
					if (pUnit->dwType == Type || Type == UNIT_ALL)
						if (!EnumFunction(pUnit))
							return;
			}
		}
	}
}

void __declspec(naked) __fastcall D2DrawRectFrameWrap(LPRECT pRect) {
	__asm {
		mov eax, ecx
		call D2CLIENT_DrawRectFrame
		ret
	}
}

void D2DrawRectFrame(int x, int y, int x2, int y2) {
	RECT Frame;
	Frame.left = x;
	Frame.top = y;
	Frame.right = x2;
	Frame.bottom = y2;
	D2DrawRectFrameWrap(&Frame);
}

char* mitoa(int integer) {
	char Buffer[100] = { 0 };
	sprintf_s(Buffer, "%d", integer);
	return Buffer;
}

enum { CLASS_AMAZON = 0, CLASS_SORCERESS, CLASS_NECROMANCER, CLASS_PALADIN, CLASS_BARBARIAN, CLASS_DRUID, CLASS_ASSASSIN };

char* GetD2ClassName(DWORD ClassID) {
	switch (ClassID) {
	case CLASS_AMAZON:
		return "Amazon";
	case CLASS_SORCERESS:
		return "Sorceress";
	case CLASS_NECROMANCER:
		return "Necromancer";
	case CLASS_PALADIN:
		return "Paladin";
	case CLASS_BARBARIAN:
		return "Barbarian";
	case CLASS_DRUID:
		return "Druid";
	case CLASS_ASSASSIN:
		return "Assassin";
	default:
		return "Unknown";
	}
}

char* D2ClassName(DWORD ClassID) {
	switch (ClassID) {
	case CLASS_AMAZON:
		return "Ama";
	case CLASS_SORCERESS:
		return "Sor";
	case CLASS_NECROMANCER:
		return "Nec";
	case CLASS_PALADIN:
		return "Pal";
	case CLASS_BARBARIAN:
		return "Bar";
	case CLASS_DRUID:
		return "Dru";
	case CLASS_ASSASSIN:
		return "Ass";
	default:
		return "Unknown";
	}
}

char* GetD2LevelName(DWORD LevelID) {
	switch (LevelID) {
	case LEVEL_NONE:
		return "Area Not Known";
		//Act 1
	case LEVEL_ROGUE_ENCAMPMENT:
		return "Rogue Encampent";
	case LEVEL_BLOOD_MOOR:
		return "Blood Moor";
	case LEVEL_COLD_PLAINS:
		return "Cold Plains";
	case LEVEL_STONY_FIELD:
		return "Stony Field";
	case LEVEL_DARK_WOOD:
		return "Dark Wood";
	case LEVEL_BLACK_MARSH:
		return "Black Marsh";
	case LEVEL_TAMOE_HIGHLAND:
		return "Tamoe Highland";
	case LEVEL_DEN_OF_EVIL:
		return "Den Of Evil";
	case LEVEL_CAVE_LEVEL_1:
		return "Cave Level 1";
	case LEVEL_UNDERGROUND_PASSAGE_LEVEL_1:
		return "Underground Passage 1";
	case LEVEL_UNDERGROUND_PASSAGE_LEVEL_2:
		return "Underground Passage 2";
	case LEVEL_HOLE_LEVEL_1:
		return "Hole 1";
	case LEVEL_HOLE_LEVEL_2:
		return "Hole 2";
	case LEVEL_PIT_LEVEL_1:
		return "Pit 1";
	case LEVEL_PIT_LEVEL_2:
		return "Pit 2";
	case LEVEL_CAVE_LEVEL_2:
		return "Cave 1";
	case LEVEL_BURIAL_GROUNDS:
		return "Burial Grounds";
	case LEVEL_CRYPT:
		return "Crypt";
	case LEVEL_MAUSOLEUM:
		return "Mausoleum";
	case LEVEL_FORGOTTEN_TOWER:
		return "Forgotten Tower";
	case LEVEL_TOWER_CELLAR_LEVEL_1:
		return "Forgotten Tower 1";
	case LEVEL_TOWER_CELLAR_LEVEL_2:
		return "Forgotten Tower 2";
	case LEVEL_TOWER_CELLAR_LEVEL_3:
		return "Forgotten Tower 3";
	case LEVEL_TOWER_CELLAR_LEVEL_4:
		return "Forgotten Tower 4";
	case LEVEL_TOWER_CELLAR_LEVEL_5:
		return "Forgotten Tower 5";
	case LEVEL_MONASTERY_GATE:
		return "Monastery Gate";
	case LEVEL_OUTER_CLOISTER:
		return "Outer Cloister";
	case LEVEL_BARRACKS:
		return "Barracks";
	case LEVEL_JAIL_LEVEL_1:
		return "Jail 1";
	case LEVEL_JAIL_LEVEL_2:
		return "Jail 2";
	case LEVEL_JAIL_LEVEL_3:
		return "Jail 3";
	case LEVEL_INNER_CLOISTER:
		return "Inner Cloister";
	case LEVEL_CATHEDRAL:
		return "Cathedral";
	case LEVEL_CATACOMBS_LEVEL_1:
		return "Catacombs 1";
	case LEVEL_CATACOMBS_LEVEL_2:
		return "Catacombs 2";
	case LEVEL_CATACOMBS_LEVEL_3:
		return "Catacombs 3";
	case LEVEL_CATACOMBS_LEVEL_4:
		return "Catacombs 4";
	case LEVEL_TRISTRAM:
		return "Tristram";
	case LEVEL_MOO_MOO_FARM:
		return "Cow Level";
		//Act 1 End
		//Act 2 Start
	case LEVEL_LUT_GHOLEIN:
		return "Lut Gholein";
	case LEVEL_ROCKY_WASTE:
		return "Rocky Waste";
	case LEVEL_DRY_HILLS:
		return "Dry Hills";
	case LEVEL_FAR_OASIS:
		return "Far Oasis";
	case LEVEL_LOST_CITY:
		return "Lost City";
	case LEVEL_VALLEY_OF_SNAKES:
		return "Valley of Snakes";
	case LEVEL_CANYON_OF_THE_MAGI:
		return "Canyon of the Magi";
	case LEVEL_SEWERS_LEVEL_1:
		return "Sewers Level 1";
	case LEVEL_SEWERS_LEVEL_2:
		return "Sewers Level 2";
	case LEVEL_SEWERS_LEVEL_3:
		return "Sewers Level 3";
	case LEVEL_HAREM_LEVEL_1:
		return "Harem Level 1";
	case LEVEL_HAREM_LEVEL_2:
		return "Harem Level 2";
	case LEVEL_PALACE_CELLAR_LEVEL_1:
		return "Palace Cellar 1";
	case LEVEL_PALACE_CELLAR_LEVEL_2:
		return "Palace Cellar 2";
	case LEVEL_PALACE_CELLAR_LEVEL_3:
		return "Palace Cellar 3";
	case LEVEL_STONY_TOMB_LEVEL_1:
		return "Stony Tomb 1";
	case LEVEL_HALLS_OF_THE_DEAD_LEVEL_1:
		return "Halls of Dead 1";
	case LEVEL_HALLS_OF_THE_DEAD_LEVEL_2:
		return "Hallsof Dead 2";
	case LEVEL_CLAW_VIPER_TEMPLE_LEVEL_1:
		return "Claw Viper Temple 1";
	case LEVEL_STONY_TOMB_LEVEL_2:
		return "Stony Tomb 2";
	case LEVEL_HALLS_OF_THE_DEAD_LEVEL_3:
		return "Halls of Dead 3";
	case LEVEL_CLAW_VIPER_TEMPLE_LEVEL_2:
		return "Claw Viper Temple 2";
	case LEVEL_MAGGOT_LAIR_LEVEL_1:
		return "Maggot Lair 1";
	case LEVEL_MAGGOT_LAIR_LEVEL_2:
		return "Maggot Lair 2";
	case LEVEL_MAGGOT_LAIR_LEVEL_3:
		return "Maggot Lair 3";
	case LEVEL_ANCIENT_TUNNELS:
		return "Ancient Tunnels";
	case LEVEL_TAL_RASHAS_TOMB1:
		return "Tal Rashas Tomb";
	case LEVEL_TAL_RASHAS_TOMB2:
		return "Tal Rashas Tomb";
	case LEVEL_TAL_RASHAS_TOMB3:
		return "Tal Rashas Tomb";
	case LEVEL_TAL_RASHAS_TOMB4:
		return "Tal Rashas Tomb";
	case LEVEL_TAL_RASHAS_TOMB5:
		return "Tal Rashas Tomb";
	case LEVEL_TAL_RASHAS_TOMB6:
		return "Tal Rashas Tomb";
	case LEVEL_TAL_RASHAS_TOMB7:
		return "Tal Rashas Tomb";
	case LEVEL_DURIELS_LAIR:
		return "Duriels Lair";
	case LEVEL_ARCANE_SANCTUARY:
		return "Arcane Sanctuary";
		//Act 2 End
		//Act 3 Start
	case LEVEL_KURAST_DOCKTOWN:
		return "Kurast Dockown";
	case LEVEL_SPIDER_FOREST:
		return "Spider Forest";
	case LEVEL_GREAT_MARSH:
		return "Great Marsh";
	case LEVEL_FLAYER_JUNGLE:
		return "Flayer Jungle";
	case LEVEL_LOWER_KURAST:
		return "Lower Kurast";
	case LEVEL_KURAST_BAZAAR:
		return "Kurast Bazaar";
	case LEVEL_UPPER_KURAST:
		return "Upper Kurast";
	case LEVEL_KURAST_CAUSEWAY:
		return "Kurast Causeway";
	case LEVEL_TRAVINCAL:
		return "Travincal";
	case LEVEL_SPIDER_CAVE:
		return "Spider Cave";
	case LEVEL_SPIDER_CAVERN:
		return "Spider Cavern";
	case LEVEL_SWAMPY_PIT_LEVEL_1:
		return "Swampy Pit 1";
	case LEVEL_SWAMPY_PIT_LEVEL_2:
		return "Swampy Pit 2";
	case LEVEL_FLAYER_DUNGEON_LEVEL_1:
		return "Flayer Dungeon 1";
	case LEVEL_FLAYER_DUNGEON_LEVEL_2:
		return "Flayer Dungeon 2";
	case LEVEL_SWAMPY_PIT_LEVEL_3:
		return "Swampy Pit 3";
	case LEVEL_FLAYER_DUNGEON_LEVEL_3:
		return "Flayer Dungeon 3";
	case LEVEL_RUINED_TEMPLE:
		return "Ruined Temple";
	case LEVEL_DISUSED_FANE:
		return "Disused Fane";
	case LEVEL_FORGOTTEN_RELIQUARY:
		return "F. Reliquary";
	case LEVEL_FORGOTTEN_TEMPLE:
		return "Forgotten Temple";
	case LEVEL_RUINED_FANE:
		return "Ruined Fane";
	case LEVEL_DISUSED_RELIQUARY:
		return "D. Reliquary";
	case LEVEL_DURANCE_OF_HATE_LEVEL_1:
		return "Durance of Hate 1";
	case LEVEL_DURANCE_OF_HATE_LEVEL_2:
		return "Durance of Hate 2";
	case LEVEL_DURANCE_OF_HATE_LEVEL_3:
		return "Durance of Hate 3";
		//Act 3 End
		//Act 4 Start
	case LEVEL_THE_PANDEMONIUM_FORTRESS:
		return "P. Fortess";
	case LEVEL_OUTER_STEPPES:
		return "Outer Steppes";
	case LEVEL_PLAINS_OF_DESPAIR:
		return "P. of Despair";
	case LEVEL_CITY_OF_THE_DAMNED:
		return "City of Damned";
	case LEVEL_RIVER_OF_FLAME:
		return "River Of Flame";
	case LEVEL_CHAOS_SANCTUM:
		return "Chaos Sanctum";
		//Act 4 End
		//Act 5 Start
	case LEVEL_HARROGATH:
		return "Harrogath";
	case LEVEL_BLOODY_FOOTHILLS:
		return "Bloody Foothills";
	case LEVEL_RIGID_HIGHLANDS:
		return "Fridgid Highlands";
	case LEVEL_ARREAT_PLATEAU:
		return "Arreat Plateau";
	case LEVEL_CRYSTALIZED_CAVERN_LEVEL_1:
		return "Crystalline Passage";
	case LEVEL_CELLAR_OF_PITY:
		return "Cellar of Pitty";
	case LEVEL_CRYSTALIZED_CAVERN_LEVEL_2:
		return "Glacial T.";
	case LEVEL_ECHO_CHAMBER: //
		return "Halls of Pain";
	case LEVEL_TUNDRA_WASTELANDS:
		return "Frozen Tundra";
	case LEVEL_GLACIAL_CAVES_LEVEL_1:
		return "Ancients Way";
	case LEVEL_GLACIAL_CAVES_LEVEL_2:
		return "Glacial Caves 2";
	case LEVEL_ROCKY_SUMMIT:
		return "Rocky Summit";
	case LEVEL_NIHLATHAKS_TEMPLE:
		return "Nihlathaks Temple";
	case LEVEL_HALLS_OF_ANGUISH:
		return "Halls of Anguish";
	case LEVEL_HALLS_OF_DEATHS_CALLING: //
		return "Deaths Calling";
	case LEVEL_HALLS_OF_VAUGHT:
		return "Halls of Vaught";
	case LEVEL_HELL1: //
		return "Hell 1";
	case LEVEL_HELL2: //
		return "Hell 2";
	case LEVEL_HELL3: //
		return "Hell 3";
	case LEVEL_THE_WORLDSTONE_KEEP_LEVEL_1:
		return "Worldstone Keep 1";
	case LEVEL_THE_WORLDSTONE_KEEP_LEVEL_2:
		return "Worldstone Keep 2";
	case LEVEL_THE_WORLDSTONE_KEEP_LEVEL_3:
		return "Worldstone Keep 3";
	case LEVEL_THRONE_OF_DESTRUCTION:
		return "Throne of Destruction";
	case LEVEL_THE_WORLDSTONE_CHAMBER:
		return "Worldstone Chamber";
		// Act 5 End
	default:
		return "Unknown";
	}
}

DWORD GetPlayerArea(VOID)
{
	if (D2CLIENT_GetPlayerUnit())
		if (D2CLIENT_GetPlayerUnit()->pPath)
			if (D2CLIENT_GetPlayerUnit()->pPath->pRoom1)
				if (D2CLIENT_GetPlayerUnit()->pPath->pRoom1->pRoom2)
					if (D2CLIENT_GetPlayerUnit()->pPath->pRoom1->pRoom2->pLevel)
						return D2CLIENT_GetPlayerUnit()->pPath->pRoom1->pRoom2->pLevel->dwLevelNo;
	return NULL;
}

BOOL IsTownLevel(INT nLevel)
{
	if (nLevel == MAP_A1_ROGUE_ENCAMPMENT ||
		nLevel == MAP_A2_LUT_GHOLEIN ||
		nLevel == MAP_A3_KURAST_DOCKS ||
		nLevel == MAP_A4_THE_PANDEMONIUM_FORTRESS ||
		nLevel == MAP_A5_HARROGATH)
		return TRUE;
	return FALSE;
}

//TPBook finding function
DWORD FindTPBook(VOID) {
	UnitAny* pPlayer = D2CLIENT_GetPlayerUnit();
	if (pPlayer) {
		if (pPlayer->pInventory) {
			UnitAny* p = D2COMMON_GetItemFromInventory(pPlayer->pInventory);
			BOOL bFoundTPBook = FALSE;
			while (p) {
				if (p->pItemData)
					if (p->pItemData->ItemLocation == STORAGE_INVENTORY) {
						ItemTxt* pTxt = D2COMMON_GetItemText(p->dwTxtFileNo);
						if (pTxt) {
							char szCode[4];
							strncpy(szCode, pTxt->szCode, 3);
							szCode[3] = '\0';
							if (!_strcmpi(szCode, "tbk"))
								if (D2COMMON_GetUnitStat(p, QUANTITY_STAT_ID, 0))
									return p->dwUnitId;
								else
									bFoundTPBook = TRUE;
						}
					}
				p = D2COMMON_GetNextItemFromInventory(p);
			}
			if (bFoundTPBook) {
				PrintMessage("::ÿc  Your TP books are empty!", 1);
				return NULL;
			}
		}
	}
	PrintMessage("::ÿc  Couldn't find any TP book.", 1);
	return NULL;
}

//Get amount of TP's in the Book.
DWORD GetTPs() {
	UnitAny* pPlayer = D2CLIENT_GetPlayerUnit();
	if (pPlayer)
		if (pPlayer->pInventory) {
			UnitAny* p = D2COMMON_GetItemFromInventory(pPlayer->pInventory);
			bool bFoundTPBook = false;
			while (p) {
				if (p->pItemData)
					if (p->pItemData->ItemLocation == STORAGE_INVENTORY) {
						ItemTxt* pTxt = D2COMMON_GetItemText(p->dwTxtFileNo);
						if (pTxt) {
							char szCode[4];
							strncpy(szCode, pTxt->szCode, 3);
							szCode[3] = '\0';
							if (!_strcmpi(szCode, "tbk"))
								if (D2COMMON_GetUnitStat(p, QUANTITY_STAT_ID, 0))
									return D2COMMON_GetUnitStat(p, QUANTITY_STAT_ID, 0);
								else
									return 0;
						}
					}
				p = D2COMMON_GetNextItemFromInventory(p);
			}
		}
	return NULL;
}

// Create a TP based on the FindTPBook values.
BOOL MakeTP(VOID) {
	if (IsTownLevel(GetPlayerArea()) == true) {
		//PrintMessage("ÿc1::ÿc  Abort MakeTP, You are in town!",0);
		return FALSE;
	}
	UnitAny* pPlayer = D2CLIENT_GetPlayerUnit();
	if (pPlayer) {
		if (pPlayer->pPath) {
			BYTE CastTP[13] = { 0x20,0,0,0,0,0,0,0x00,0x00,0,0,0x00,0x00 };
			*(WORD*)&CastTP[5] = pPlayer->pPath->xPos;
			*(WORD*)&CastTP[9] = pPlayer->pPath->yPos;
			DWORD dwID = FindTPBook();
			if (dwID) {
				*(DWORD*)&CastTP[1] = dwID;
				SendGAMEPacket(CastTP, sizeof(CastTP));
				return TRUE;
			}
		}
	}
	return FALSE;
}

/*if(TakeNextTP) {
	if(CheckInTown())
		TakeNextTP=false;
}*//*
Act* GetAct() {
DWORD ActBase = (DWORD)LoadLibrary("D2Client.dll") +0x11C01C;
if(D2CLIENT_GetPlayerUnit()->dwAct!=NULL)
			return (D2CLIENT_GetPlayerUnit()->dwAct);
}*/
/*
void GetAct(int ID) {
	DWORD ID=D2CLIENT_GetPlayerUnit()->pAct->pRoom1->pRoom2->pLevel->dwLevelNo;
if(ID>=LEVEL_ROGUE_ENCAMPMENT&&ID<LEVEL_LUT_GHOLEIN)
	return 1;
if(ID>=LEVEL_LUT_GHOLEIN&&ID<LEVEL_KURAST_DOCKTOWN)
	return 2;
if(ID>=LEVEL_KURAST_DOCKTOWN&&ID<LEVEL_THE_PANDEMONIUM_FORTRESS)
	return 3;
if(ID>=LEVEL_HARROGATH)
	return 5;
if(ID>=LEVEL_THE_PANDEMONIUM_FORTRESS&&ID<LEVEL_HARROGATH);
	return 4;
return 5;
}
*/
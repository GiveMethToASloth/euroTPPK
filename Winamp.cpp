#include "EuroTPPK.h"

static int playerID = 0;
char currTitle[4096];
/*
HWND FindPlayer(int wanted) 
{
    HWND hwnd;

    if (wanted == 0 || wanted == 4) {
        hwnd = FindWindow("Sonique Window Class", NULL);
        if (hwnd != 0) {
            playerID = 4;
            return hwnd;
        }
    }

    if (wanted == 0 || wanted == 3) {
        hwnd = FindWindow("Studio", NULL);
        if (hwnd != 0) {
            playerID = 3;
		    return hwnd;
        }
    }

    if (wanted == 0 || wanted == 2) {
        hwnd = FindWindow("Winamp v1.x", NULL);
        if (hwnd != 0) {
            playerID = 2;
		    return hwnd;
        }
    }

    playerID = 0;

    return 0;
}

void SendW3Key(HWND hwnd_winamp,char message)
{
    short key = VkKeyScan(message);
    UINT scancode = MapVirtualKey(key, 0);
	PostMessage(hwnd_winamp, WM_KEYDOWN, key, scancode);
	PostMessage(hwnd_winamp, WM_CHAR, key, scancode);
	PostMessage(hwnd_winamp, WM_KEYUP, key, scancode);
}

char* AmpControl_GetPlayingTitle(void)
{
    HWND hwnd_winamp = FindPlayer(0);

    if (hwnd_winamp != 0) {
        if (playerID == 2 || playerID == 3 || playerID == 4) {
            GetWindowText(hwnd_winamp, currTitle, sizeof(currTitle));
            currTitle[4096] = '\0';

            if (strlen(currTitle) <= 0) {
                return "None";
            }
            else {
				*(strrchr(currTitle,'-')) = 0;
                return currTitle;
			}
		}
	}
  return "OFF";
}
*/

int GetMaxTrackTime() 
{ 
   HWND win = FindWindowA("Winamp v1.x",NULL); 
   if(win) 
   return SendMessage(win,WM_USER,1,105); 

   return 0; 
} 

int GetCurrentTrackTime() 
{ 
   HWND win = FindWindowA("Winamp v1.x",NULL); 
   if(win) 
   return SendMessage(win,WM_USER,0,105); 

   return 0; 
} 

char* GetCurrentWinampTrack() 
{ 
   char szTitle[0x200]; 
   HWND win = FindWindowA("Winamp v1.x",NULL); 
   if(!win) 
   return "Winamp OFF!"; 

   GetWindowTextA(win, szTitle, sizeof(szTitle)); 
   if(strlen(szTitle) <= 0) 
   return "No name!"; 
   return szTitle; 
}
void StopSong() {
	HWND hwndWinamp = FindWindow("Winamp v1.x",NULL);
	SendMessage(hwndWinamp, WM_COMMAND, W2_PAUSE, 0);
}
void NextSong()
{
	HWND hwndWinamp = FindWindow("Winamp v1.x",NULL);
	SendMessage(hwndWinamp, WM_COMMAND, 40048, 0);
}
void PrevSong()
{
	HWND hwndWinamp = FindWindow("Winamp v1.x",NULL);
	SendMessage(hwndWinamp, WM_COMMAND, 40044, 0);
}
void PlayPause()
{
	HWND hwndWinamp = FindWindow("Winamp v1.x",NULL);
	SendMessage(hwndWinamp, WM_COMMAND, 40046, 0);
}
void FastForward()
{
	HWND hwndWinamp = FindWindow("Winamp v1.x",NULL);
	SendMessage(hwndWinamp, WM_COMMAND, 40148, 0);
}
void Rewind()
{
	HWND hwndWinamp = FindWindow("Winamp v1.x",NULL);
	SendMessage(hwndWinamp, WM_COMMAND, 40144, 0);
}
void RaiseVolume()
{
	HWND hwndWinamp = FindWindow("Winamp v1.x",NULL);
	SendMessage(hwndWinamp, WM_COMMAND, 40058, 0);
	SendMessage(hwndWinamp, WM_COMMAND, 40058, 0);
	SendMessage(hwndWinamp, WM_COMMAND, 40058, 0);
	SendMessage(hwndWinamp, WM_COMMAND, 40058, 0);
	SendMessage(hwndWinamp, WM_COMMAND, 40058, 0);
}
void LowerVolume()
{
	HWND hwndWinamp = FindWindow("Winamp v1.x",NULL);
	SendMessage(hwndWinamp, WM_COMMAND, 40059, 0);
	SendMessage(hwndWinamp, WM_COMMAND, 40059, 0);
	SendMessage(hwndWinamp, WM_COMMAND, 40059, 0);
	SendMessage(hwndWinamp, WM_COMMAND, 40059, 0);
	SendMessage(hwndWinamp, WM_COMMAND, 40059, 0);
}
void Shuffle()
{
	HWND hwndWinamp = FindWindow("Winamp v1.x",NULL);
	SendMessage(hwndWinamp, WM_COMMAND, 40023, 0);
}
void Repeat()
{
	HWND hwndWinamp = FindWindow("Winamp v1.x",NULL);
	SendMessage(hwndWinamp, WM_COMMAND, 40022, 0);
}

void Close()
{
	HWND hwndWinamp = FindWindow("Winamp v1.x",NULL);
	SendMessage(hwndWinamp, WM_COMMAND, 40001, 0);
}

void D2Draw(INT xPos, INT yPos, DWORD dwColor,LPSTR Text,...) 
{ 
CHAR szBuffer[800] = ""; 
va_list Args; 

va_start(Args, Text); 
vsprintf(szBuffer, Text, Args); 
va_end(Args); 

typedef void (__fastcall *pPrint)(LPWSTR wStr, INT x, INT y, DWORD Color, DWORD Unk); 
pPrint Print = (pPrint)0x6F8F0890; 
wchar_t wBuffer[0x130]; 
MultiByteToWideChar(0, 1, szBuffer, 100, wBuffer, 100); 
Print (wBuffer,xPos,yPos,dwColor,6); 
} 

VOID PanelDraw(VOID) 
{ 
int ct = GetCurrentTrackTime(); 
int mt = GetMaxTrackTime(); 
if(v_DrawSongTitle)
    D2Draw(120,500,4,"%s; (%d:%02d/%d:%02d)",GetCurrentWinampTrack(),ct/(1000*60), (ct/1000)%60,mt/(60), (mt)%60); 
} 
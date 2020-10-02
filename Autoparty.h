#ifndef _AUTOPARTY_H
#define _AUTOPARTY_H

#define PARTY_NOT_IN_PARTY 0x00
#define PARTY_IN_PARTY 0x01
#define PARTY_INVITED_YOU 0x02
#define PARTY_INVITED_BY_YOU 0x04

#define clickParty_Loot 0
#define clickParty_Accept 1
#define clickParty_Invite 2
#define clickParty_Leave 3

void CheckParty();
DWORD WINAPI AutoPartyThread(LPVOID lpParameter);

DWORD WINAPI PKMessage(LPVOID lpParameter);
DWORD WINAPI SpamMessage(LPVOID lpParameter);
#endif
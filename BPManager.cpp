#include "EuroTPPK.h"

void MaxBPs(void) 
    {
	//ReadConfigFile();
    MaximizeFCR();
    MaximizeFBR();
    MaximizeFHR();
    MaximizeIAS();
//	MaxFRW();
    }
void UnloadMaxBPs(void) 
    {
    UnMaximizeFCR();
 // UnMaximizeFBR();
 // UnMaximizeFHR();
    UnMaximizeIAS();
    }    
// Maxing    
void MaximizeFCR(void) 
    {
    BYTE aPacket[3];
	aPacket[0] = 0x1D;
	aPacket[1] = 105;
	aPacket[2] = 240;
    D2NET_ReceivePacket(aPacket, sizeof(aPacket));
    }
void MaximizeFCRTeleport(void) 
    {
    BYTE aPacket[3];
	aPacket[0] = 0x1D;
	aPacket[1] = 105;
	aPacket[2] = 170;
    D2NET_ReceivePacket(aPacket, sizeof(aPacket));
    }

void MaximizeFBR(void) 
    {
    BYTE aPacket[3];
	aPacket[0] = 0x1D;
	aPacket[1] = 102;
	aPacket[2] = 240;
    D2NET_ReceivePacket(aPacket, sizeof(aPacket));
    }
void MaximizeFHR(void) 
    {
    BYTE aPacket[3];
	aPacket[0] = 0x1D;
	aPacket[1] = 99;
	aPacket[2] = 240;
    D2NET_ReceivePacket(aPacket, sizeof(aPacket));
    }
void MaximizeIAS(void) 
    {
    BYTE aPacket[3];
	aPacket[0] = 0x1D;
	aPacket[1] = 93;
	aPacket[2] = 240;
    D2NET_ReceivePacket(aPacket, sizeof(aPacket));
    }
    // Unmaxing
    
void UnMaximizeFCR(void) 
    {
  //int value=D2COMMON_GetUnitStat((UnitAny*)pUnit,sInfo[i].Statnumber,0);
    BYTE aPacket[3];
	aPacket[0] = 0x1D;
	aPacket[1] = 105;
    aPacket[2] = 50;
    D2NET_ReceivePacket(aPacket, sizeof(aPacket));
    }
void UnMaximizeFBR(void) 
    {
    BYTE aPacket[3];
	aPacket[0] = 0x1D;
	aPacket[1] = 102;
	aPacket[2] = 240;
    D2NET_ReceivePacket(aPacket, sizeof(aPacket));
    }
void UnMaximizeFHR(void) 
    {
    BYTE aPacket[3];
	aPacket[0] = 0x1D;
	aPacket[1] = 99;
	aPacket[2] = 240;
    D2NET_ReceivePacket(aPacket, sizeof(aPacket));
    }
void UnMaximizeIAS(void) 
    {
    BYTE aPacket[3];
	aPacket[0] = 0x1D;
	aPacket[1] = 93;
	aPacket[2] = 50;
    D2NET_ReceivePacket(aPacket, sizeof(aPacket));
    }

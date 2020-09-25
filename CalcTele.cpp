#include "EuroTPPK.h"
//POINT aPath[255];
//	POINT WalkPath[255];
//	DWORD dwCount;
//	int telex=0;
//	DWORD QuestID;
//	POINT Safed;
	bool AutoTele=false;
	int CurrentDW;

void Interact(DWORD ID,DWORD Type) {
	
	//fpGetUnitByCords
	//13 [DWORD entity kind] [DWORD id] 
	byte Interact[9]={0x13,00,00,00,00, 00,00,00,00};
	*(DWORD*)&Interact[5]=ID;
	*(DWORD*)&Interact[1]=Type;
	SendGAMEPacket(Interact,sizeof(Interact));
}
void TeleportTo(WORD x, WORD y) {

	BYTE Packet1[] = {0x3c,0x36,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF};
	SendGAMEPacket(Packet1,sizeof(Packet1));
		BYTE Packet2[] = {0xc,00,00,00,00};
		memcpy(&Packet2[1],&x,2);
		memcpy(&Packet2[3],&y,2);
		SendGAMEPacket(Packet2,sizeof(Packet2));
}



DWORD   fpCalculateTeleportPath(long x, long y, LPPOINT lpBuffer, DWORD dwMaxCount)
{
	CCollisionMap	g_collisionMap;
	if (!g_collisionMap.CreateMap(GetPlayerArea()))
		PrintMessage("Failed Creating Map",3);
		return 0;

	POINT ptStart = GetPosition();
	POINT ptEnd = { x, y };
	
	if (!g_collisionMap.IsValidAbsLocation(ptStart.x, ptStart.y)
		|| !g_collisionMap.IsValidAbsLocation(ptEnd.x, ptEnd.y))
		return 0;

	g_collisionMap.AbsToRelative(ptStart);
	g_collisionMap.AbsToRelative(ptEnd);

	WordMatrix matrix;
	if (!g_collisionMap.CopyMapData(matrix))
		return 0;

	g_collisionMap.MakeBlank(matrix, ptStart);
	g_collisionMap.MakeBlank(matrix, ptEnd);
	
	CTeleportPath tf(matrix.GetData(), matrix.GetCX(), matrix.GetCY());
	DWORD dwCount = tf.FindTeleportPath(ptStart, ptEnd, lpBuffer, dwMaxCount);

	for (DWORD i = 0; i < dwCount; i++)
		g_collisionMap.RelativeToAbs(lpBuffer[i]);

	return dwCount;

}
int WalkToPath(long x, long y, LPPOINT lpBuffer, DWORD dwMaxCount)
{	
	CCollisionMap g_collisionMap;
	if (!g_collisionMap.CreateMap(GetPlayerArea()))
		return 0;

	POINT ptStart = GetPosition();
	POINT ptEnd = { x, y };
	
	if (!g_collisionMap.IsValidAbsLocation(ptStart.x, ptStart.y)
		|| !g_collisionMap.IsValidAbsLocation(ptEnd.x, ptEnd.y))
		return 0;

	g_collisionMap.AbsToRelative(ptStart);
	g_collisionMap.AbsToRelative(ptEnd);
	
	WordMatrix matrix;
	if (!g_collisionMap.CopyMapData(matrix))
		return 0;

	g_collisionMap.ThickenWalls(matrix, 1);

	g_collisionMap.MakeBlank(matrix, ptStart);
	g_collisionMap.MakeBlank(matrix, ptEnd);

	CWalkPath wp(matrix.GetData(), matrix.GetCX(), matrix.GetCY());

	DWORD dwCount = (DWORD)wp.FindWalkPath(ptStart, ptEnd, lpBuffer, dwMaxCount);
	
	for (DWORD i = 0; i < dwCount; i++)
		g_collisionMap.RelativeToAbs(lpBuffer[i]);

	return dwCount;
}

	
	
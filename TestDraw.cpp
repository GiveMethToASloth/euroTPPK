#include "EuroTPPK.h"

#define VECTOR_NEXT		1
#define VECTOR_QUEST	2
#define VECTOR_WAYPOINT	3

#define TARGET_LEVEL	-1

Level* GetLevelPointerBA(ActMisc *pActMisc, int nLevel)
{
	if ((!pActMisc) || (nLevel < 0))
		return false;

	for (Level *pLevel = pActMisc->pLevelFirst; pLevel; pLevel = pLevel->pNextLevel)
	{
		if (!pLevel)
			continue;

		if ((pLevel->dwLevelNo == nLevel) && (pLevel->dwSizeX > 0))
			return pLevel;
	}
	return D2COMMON_GetLevel(pActMisc, nLevel);
}

void NewAEnum() 
		{ 
		UnitAny *pUnit = D2CLIENT_GetPlayerUnit (); 
		Level *pLevel = GetLevelPointerBA(pUnit->pAct->pMisc, GetPlayerArea()); 
			for(Room2 *pRoom2 = pLevel->pRoom2First;pRoom2;pRoom2=(Room2*)pRoom2->pRoom2Other) { 
			for(PresetUnit *unit = pRoom2->pPreset;unit;unit=unit->pPresetNext) { 
			BOOL add_room=FALSE;
			if(!pRoom2->pRoom1)
			{
			add_room=TRUE;
			D2COMMON_AddRoomData(D2CLIENT_GetPlayerUnit()->pAct,pRoom2->pLevel->dwLevelNo,pRoom2->dwPosX,pRoom2->dwPosY,D2CLIENT_GetPlayerUnit()->pPath->pRoom1);
			}
			LevelExit pu; 
			POINT Calc; 
			POINT DrawCalc; 
			pu.dwType = VECTOR_WAYPOINT;
			pu.ptPos.x = ((pRoom2->dwPosX * 5) + pu.ptPos.x) * 32;
			pu.ptPos.y = ((pRoom2->dwPosY * 5) + pu.ptPos.y) * 32;
			pu.dwTargetLevel = pu.dwTargetLevel;
			Calc.x = pu.ptPos.x;
			Calc.y = pu.ptPos.y;

			MapToScreenCoords(Calc); 
			ScreenToAutomapRelative(&DrawCalc,Calc.x,Calc.y); 
			if(pu.dwTargetLevel != D2CLIENT_GetPlayerUnit()->dwAct)
			D2DrawLine(DrawCalc.x,DrawCalc.y,Calc.x,Calc.y,11);
		//	MiniMapCell(DrawCalc.x,DrawCalc.y,D2CLIENT_GetPlayerUnit()->dwAct+1,GetPlayerArea(),pu.dwTxtFileNo,pu.dwPosX,pu.dwPosY,UnitID); 
		if(Units) {
		DrawTextToScreen(mitoa(unit->dwTxtFileNo),Calc.x,Calc.y,1,4); // Prints Type
		  DrawTextToScreen(mitoa(unit->dwType),Calc.x,Calc.y+10,2,4);; // PrintsUnitTypes
		  }
		  
		}
	} 
}
#include "EuroTPPK.h"

typedef struct VectorTarget_t
{
	POINT ptPos;
	INT nType;
	DWORD dwTarget;
	DWORD dwTargetType;
} VECTOR, *LPVECTOR;

INT nLastLevel = 0;
INT nColors[] = {168, 155, 131};
INT nWaypoints[] = {119, 157, 156, 402, 323, 288, 237, 324, 238, 496, 511, 494};
BOOL GetVectorArrows();
BOOL DrawVectorArrows();

BOOL GetVectorArrows()
{
	if(GetUnitLevel(Me)->dwLevelNo != nLastLevel)
	{
		LPLEVELEXIT pLevels[0x40] = {NULL};

		for(INT i = 0; i < v_CurrentVectors.GetSize(); i++)
			delete v_CurrentVectors[i];

		v_CurrentVectors.RemoveAll();
		v_GlobalMap->CreateCollisionMap();
		v_GlobalMap->GetLevelExits(pLevels, 0x40);

		for(INT i = 0; i < ArraySize(nWaypoints); i++)
		{
			LPROOM2 pRoom;
			LPPRESETUNIT pUnit = FindPresetUnit(nWaypoints[i], UNIT_TYPE_OBJECT, &pRoom);
			if(!pUnit)
				continue;

			LPVECTOR pVect = new VECTOR;
			pVect->nType = VECTOR_WAYPOINT;
			pVect->ptPos.x = ((pRoom->dwPosX * 5) + pUnit->dwPosX) * 32;
			pVect->ptPos.y = ((pRoom->dwPosY * 5) + pUnit->dwPosY) * 32;
			pVect->dwTarget = nWaypoints[i];
			pVect->dwTargetType = UNIT_TYPE_OBJECT;

			v_CurrentVectors.Add(pVect);
			break;
		}

		for(INT j = 0; j < ArraySize(Vectors); j++)
		{
			if(Vectors[j].dwCurrentLevel != GetUnitLevel(Me)->dwLevelNo)
				continue;

			if(Vectors[j].dwTargetType == TARGET_LEVEL)
			{
				for(INT i = 0; i < 0x40; i++)
				{
					if(!pLevels[i])
						break;

					if(Vectors[j].dwTarget != pLevels[i]->dwTargetLevel)
						continue;

					for(INT k = 0; k < v_CurrentVectors.GetSize(); k++)
					{
						if(v_CurrentVectors[k]->nType == Vectors[j].dwVectorType)
							goto ContinueIt;
					}

					LPVECTOR pVect = new VECTOR;
					pVect->ptPos.x = pLevels[i]->ptPos.x * 32;
					pVect->ptPos.y = pLevels[i]->ptPos.y * 32;
					pVect->nType = Vectors[j].dwVectorType;
					pVect->dwTarget = Vectors[j].dwTarget;
					pVect->dwTargetType = Vectors[j].dwTargetType;

					v_CurrentVectors.Add(pVect);
				}
			}
			else
			{
				LPROOM2 pRoom;
				LPPRESETUNIT pUnit = FindPresetUnit(Vectors[j].dwTarget, Vectors[j].dwTargetType, &pRoom);
				if(!pUnit)
					continue;

				for(INT k = 0; k < v_CurrentVectors.GetSize(); k++)
				{
					if(v_CurrentVectors[k]->nType == Vectors[j].dwVectorType)
						goto ContinueIt;
				}

				LPVECTOR pVect = new VECTOR;
				pVect->ptPos.x = ((pRoom->dwPosX * 5) + pUnit->dwPosX) * 32;
				pVect->ptPos.y = ((pRoom->dwPosY * 5) + pUnit->dwPosY) * 32;
				pVect->nType = Vectors[j].dwVectorType;

				v_CurrentVectors.Add(pVect);
				break;
			}

ContinueIt:
			continue;
		}

		nLastLevel = GetUnitLevel(Me)->dwLevelNo;
	}

	return TRUE;
}

BOOL DrawVectorArrows()
{
	if(!IsClientReady(TRUE) || InTown(Me))
		return FALSE;

	POINT ptPlayer, ptPos;
	GetPlayerPosition(&ptPlayer);

	if(!v_Players.IsEmpty())
	{
		LPUNITANY pUnit = GetUnit(v_Players[v_CurrentTarget]->UnitId, UNIT_TYPE_PLAYER);
		if(pUnit)
		{
			LONG fAngle = CalculateAngle(Me->pPath->xPos, Me->pPath->yPos, pUnit->pPath->xPos, pUnit->pPath->yPos);
			INT nColor = 0x87;

			for(DWORD i = 0; i < GetUnitDist(Me, pUnit); i++)
			{
				POINT ptOrigin = {Me->pPath->xPos, Me->pPath->yPos};
				POINT ptLine = CalculatePointOnTrack(ptOrigin, i, fAngle);

				INT nData = v_GlobalMap->GetCollisionInfo(ptLine.x, ptLine.y);

				if(nData % 2 && nData != 17)
				{
					nColor = 0x62;
					break;
				}
			}

			ScreenToAutomap(&ptPos, pUnit->pPath->xPos * 32, pUnit->pPath->yPos * 32);
			D2GFX_DrawLine(ptPlayer.x, ptPlayer.y, ptPos.x, ptPos.y, nColor, -1);
		}
	}

	for(INT i = 0; i < v_CurrentVectors.GetSize(); i++)
	{
		ScreenToAutomap(&ptPos, v_CurrentVectors[i]->ptPos.x, v_CurrentVectors[i]->ptPos.y);

		D2GFX_DrawLine(ptPlayer.x, ptPlayer.y, ptPos.x, ptPos.y, nColors[v_CurrentVectors[i]->nType - 1], -1);
		DrawCross(ptPos.x, ptPos.y, nColors[v_CurrentVectors[i]->nType - 1]);
	}

	return TRUE;
}
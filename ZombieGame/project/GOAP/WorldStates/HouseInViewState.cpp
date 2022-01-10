#include "stdafx.h"
#include "HouseInViewState.h"

#include <IExamInterface.h>

#include "GOAP/Memory/Memory.h"

void HouseInViewState::Update(float elapsedSec, IExamInterface* iFace, const vector<EntityInfo>& entities)
{
	Predicate = false;

	HouseInfo hi = {};
	for (int i = 0;; ++i)
	{
		if (iFace->Fov_GetHouseByIndex(i, hi))
		{
			if(Memory::GetInstance()->IsHouseInMemory(hi)) 
				continue;
			Predicate = true;
		}
		break;
	}
}

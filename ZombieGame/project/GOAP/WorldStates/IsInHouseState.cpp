#include "stdafx.h"
#include "IsInHouseState.h"

#include <IExamInterface.h>

#include "GOAP/Memory/Memory.h"

void IsInHouseState::Update(float elapsedSec, IExamInterface* iFace, const vector<EntityInfo>& entities)
{
	Predicate = iFace->Agent_GetInfo().IsInHouse && Memory::GetInstance()->IsHouseInMemory(Memory::GetInstance()->GetLastClosestHouse());
}

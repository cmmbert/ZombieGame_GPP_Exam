#include "stdafx.h"
#include "IsInHouseState.h"

#include <IExamInterface.h>

void IsInHouseState::Update(float elapsedSec, IExamInterface* iFace, const vector<EntityInfo>& entities)
{
	Predicate = iFace->Agent_GetInfo().IsInHouse;
}

#include "stdafx.h"
#include "IsInPurgeZoneState.h"

void IsInPurgeZoneState::Update(float elapsedSec, IExamInterface* iFace, const vector<EntityInfo>& entities)
{
	Predicate = false;
	for(const auto& entity : entities)
	{
		if(entity.Type == eEntityType::PURGEZONE)
		{
			Predicate = true;
		}
	}
}

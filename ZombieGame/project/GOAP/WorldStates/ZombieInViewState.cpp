#include "stdafx.h"
#include "ZombieInViewState.h"

void ZombieInViewState::Update(float elapsedSec, IExamInterface* iFace, const vector<EntityInfo>& entities)
{
	Predicate = false;
	for (auto entityInfo : entities)
	{
		if (entityInfo.Type == eEntityType::ENEMY)
		{
			Predicate = true;
			break;
		}
	}
}

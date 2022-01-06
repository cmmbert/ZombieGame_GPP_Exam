#include "stdafx.h"
#include "ItemInViewState.h"
#include "IExamInterface.h"


void ItemInViewState::Update(float elapsedSec, IExamInterface* iFace, const vector<EntityInfo>& entities)
{
	Predicate = false;
	for (auto entityInfo : entities)
	{
		if (entityInfo.Type == eEntityType::ITEM)
		{
			Predicate = true;
			break;
		}
	}
}
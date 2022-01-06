#include "stdafx.h"
#include "NextToPickupState.h"
#include "IExamInterface.h"


void NextToPickup::Update(float elapsedSec, IExamInterface* iFace, const vector<EntityInfo>& entities)
{
	Predicate = false;
	for (auto entityInfo : entities)
	{
		if (entityInfo.Type == eEntityType::ITEM)
		{
			if ((entityInfo.Location - iFace->Agent_GetInfo().Position).Magnitude() < m_PickupRange)
			{
				Predicate = true;
				break;
			}

		}
	}
}

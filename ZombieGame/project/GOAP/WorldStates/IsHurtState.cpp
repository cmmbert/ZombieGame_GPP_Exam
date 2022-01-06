#include "stdafx.h"
#include "IsHurtState.h"
#include <IExamInterface.h>

void IsHurtState::Update(float elapsedSec, IExamInterface* iFace, const vector<EntityInfo>& entities)
{
	if (iFace->Agent_GetInfo().Health < m_HealthThreshold)
	{
		iFace->Inventory_UseItem(1);
		ItemInfo pack;
		iFace->Inventory_GetItem(1, pack);
		if (iFace->Medkit_GetHealth(pack) == 0)
			iFace->Inventory_RemoveItem(1);
	}
}

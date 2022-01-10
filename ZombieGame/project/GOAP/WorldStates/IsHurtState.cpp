#include "stdafx.h"
#include "IsHurtState.h"
#include <IExamInterface.h>

void IsHurtState::Update(float elapsedSec, IExamInterface* iFace, const vector<EntityInfo>& entities)
{
	if (iFace->Agent_GetInfo().Health < m_HealthThreshold)
	{
		ItemInfo pack;
		if(iFace->Inventory_GetItem(1, pack))
		{
			iFace->Inventory_UseItem(1);
			if (iFace->Medkit_GetHealth(pack) == 0)
			{
				iFace->Inventory_RemoveItem(1);
			}
		}
	}
}

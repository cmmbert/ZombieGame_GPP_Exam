#include "stdafx.h"
#include "IsHungry.h"

#include <IExamInterface.h>

void IsHungry::Update(float elapsedSec, IExamInterface* iFace, const vector<EntityInfo>& entities)
{
	if(iFace->Agent_GetInfo().Energy < m_HungerThreshold)
	{
		iFace->Inventory_UseItem(2);
		ItemInfo food;
		iFace->Inventory_GetItem(2, food);
		if (iFace->Food_GetEnergy(food) == 0)
			iFace->Inventory_RemoveItem(2);
	}
}

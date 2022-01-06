#include "stdafx.h"
#include "PickupAction.h"

#include <IExamInterface.h>

#include "GOAP/WorldStates/ItemInInventoryState.h"
#include "GOAP/WorldStates/NextToPickupState.h"

PickupAction::PickupAction()
{
	m_Preconditions.push_back(new NextToPickup(true));
	m_EffectOnWorld.push_back(new ItemInInventoryState(true));
	m_Name = typeid(this).name();
}

bool PickupAction::Execute(SteeringPlugin_Output& steeringOutput, IExamInterface* iFace, const vector<EntityInfo>& entities)
{
	auto item = ItemInfo();
	for (const auto& entityInfo : entities)
	{
		if (entityInfo.Type == eEntityType::ITEM)
		{
			if ((entityInfo.Location - iFace->Agent_GetInfo().Position).Magnitude() < iFace->Agent_GetInfo().GrabRange)
			{
				iFace->Item_Grab(entityInfo, item);
				if (item.Type == eItemType::GARBAGE)
				{
					iFace->Item_Destroy(entityInfo);
					break;
				}
				iFace->Inventory_AddItem(0, item);
				break;
			}

		}
	}
	return false;
}

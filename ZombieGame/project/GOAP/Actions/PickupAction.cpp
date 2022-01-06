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
				switch (item.Type) {
				case eItemType::PISTOL:
					iFace->Inventory_RemoveItem(0);
					iFace->Inventory_AddItem(0, item);
					break;
				case eItemType::MEDKIT:
					iFace->Inventory_RemoveItem(1);
					iFace->Inventory_AddItem(1, item);
					break;
				case eItemType::FOOD:
					iFace->Inventory_RemoveItem(2);
					iFace->Inventory_AddItem(2, item);
					break;
				case eItemType::GARBAGE: 
				default:
					iFace->Inventory_AddItem(3, item);
					iFace->Inventory_RemoveItem(3);
					break;
				}
				break;
			}

		}
	}
	return false;
}

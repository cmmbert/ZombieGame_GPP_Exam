#include "stdafx.h"
#include "PickupAction.h"

#include <IExamInterface.h>

#include "GOAP/Memory/Memory.h"
#include "GOAP/WorldStates/IsInHouseState.h"
#include "GOAP/WorldStates/ItemInInventoryState.h"
#include "GOAP/WorldStates/NextToPickupState.h"

PickupAction::PickupAction()
{
	m_Preconditions.push_back(new NextToPickup(true));
	m_Preconditions.push_back(new IsInHouseState(true));
	m_EffectOnWorld.push_back(new ItemInInventoryState(true));
	m_Name = typeid(this).name();
}

bool PickupAction::Execute(float elapsedSec, SteeringPlugin_Output& steeringOutput, IExamInterface* iFace, const vector<EntityInfo>& entities)
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
					if (!iFace->Inventory_AddItem(0, item))
						if (!iFace->Inventory_AddItem(3, item))//If both pistol slots are already filled, check if one them has less ammo
						{
							ItemInfo pistol1;
							iFace->Inventory_GetItem(0, pistol1);

							ItemInfo pistol2;
							iFace->Inventory_GetItem(3, pistol2);

							if(iFace->Weapon_GetAmmo(pistol1) < iFace->Weapon_GetAmmo(pistol2))
							{
								if(iFace->Weapon_GetAmmo(item) > iFace->Weapon_GetAmmo(pistol1))
								{
									iFace->Inventory_RemoveItem(0);
									iFace->Inventory_AddItem(0, item);
								}
							}
							else
							{
								if (iFace->Weapon_GetAmmo(item) > iFace->Weapon_GetAmmo(pistol2))
								{
									iFace->Inventory_RemoveItem(3);
									iFace->Inventory_AddItem(3, item);
								}
							}
						}
					break;
				case eItemType::MEDKIT:
					if(!iFace->Inventory_AddItem(1, item))
					{
						iFace->Inventory_UseItem(1);
						iFace->Inventory_RemoveItem(1);
						iFace->Inventory_AddItem(1, item);
					}
					break;
				case eItemType::FOOD:
					{
						ItemInfo food;
						iFace->Inventory_GetItem(2, food);
						if(iFace->Food_GetEnergy(food) < iFace->Food_GetEnergy(item))
						{
							iFace->Inventory_UseItem(2);
							iFace->Inventory_RemoveItem(2);
							iFace->Inventory_AddItem(2, item);
						}
						else
						{
							iFace->Inventory_AddItem(4, item);
							iFace->Inventory_UseItem(4);
							iFace->Inventory_RemoveItem(4);
						}
						break;
					}
				case eItemType::GARBAGE: 
				default:
					iFace->Inventory_AddItem(4, item);
					iFace->Inventory_RemoveItem(4);
					break;
				}
				Memory::GetInstance()->RemoveItemFromMemory(item);
				iFace->Inventory_AddItem(4, item);
				iFace->Inventory_RemoveItem(4);
				break;
			}

		}
	}
	return false;
}

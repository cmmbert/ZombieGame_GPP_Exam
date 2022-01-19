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
				Memory::GetInstance()->RemoveItemFromMemory(item);
				switch (item.Type) {
				case eItemType::PISTOL:
					if (!iFace->Inventory_AddItem(0, item))
						if (!iFace->Inventory_AddItem(3, item))
						{
							if (!iFace->Inventory_AddItem(4, item))//If all pistol slots are already filled, check if one them has less ammo
							{
								ItemInfo pistol1;
								iFace->Inventory_GetItem(0, pistol1);

								ItemInfo pistol2;
								iFace->Inventory_GetItem(3, pistol2);

								ItemInfo pistol3;
								iFace->Inventory_GetItem(4, pistol2);

								int ammo0 = iFace->Weapon_GetAmmo(item);
								int ammo1 = iFace->Weapon_GetAmmo(pistol1);
								int ammo2 = iFace->Weapon_GetAmmo(pistol2);
								int ammo3 = iFace->Weapon_GetAmmo(pistol3);

								if(ammo1 < ammo0 && ammo1 < ammo2 && ammo1 < ammo3)
								{
									iFace->Inventory_RemoveItem(0);
									iFace->Inventory_AddItem(0, item);
									std::cout << "Replaced pistol in slot 0";
								}

								if (ammo2 < ammo0 && ammo2 < ammo1 && ammo2 < ammo3)
								{
									iFace->Inventory_RemoveItem(3);
									iFace->Inventory_AddItem(3, item);
									std::cout << "Replaced pistol in slot 3";
								}

								if (ammo3 < ammo0 && ammo3 < ammo2 && ammo3 < ammo1)
								{
									iFace->Inventory_RemoveItem(4);
									iFace->Inventory_AddItem(4, item);
									std::cout << "Replaced pistol in slot 4";
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
						break;
					}
				case eItemType::GARBAGE: 
				default:
					iFace->Item_Destroy(entityInfo);
					std::cout << "Picked up garbage and tossed it";

					break;
				}
				iFace->Item_Destroy(entityInfo);
				break;
			}

		}
	}
	return false;
}

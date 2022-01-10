#include "stdafx.h"
#include "HasWeaponState.h"

#include <IExamInterface.h>

void HasWeaponState::Update(float elapsedSec, IExamInterface* iFace, const vector<EntityInfo>& entities)
{
	ItemInfo item;
	Predicate = iFace->Inventory_GetItem(0, item) || iFace->Inventory_GetItem(3, item);
}

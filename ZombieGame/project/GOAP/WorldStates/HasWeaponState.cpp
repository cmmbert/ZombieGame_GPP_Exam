#include "stdafx.h"
#include "HasWeaponState.h"

#include <IExamInterface.h>

void HasWeaponState::Update(float elapsedSec, IExamInterface* iFace, const vector<EntityInfo>& entities)
{
	ItemInfo item;
	Predicate = true;// iFace->Inventory_GetItem(0, item);
}

#include "stdafx.h"
#include "ItemInInventoryState.h"

#include <IExamInterface.h>

void ItemInInventoryState::Update(float elapsedSec, IExamInterface* iFace, const vector<EntityInfo>& entities)
{
	ItemInfo item;
	Predicate = iFace->Inventory_GetItem(0, item);
}

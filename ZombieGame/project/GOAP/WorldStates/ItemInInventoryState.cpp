#include "stdafx.h"
#include "ItemInInventoryState.h"

#include <IExamInterface.h>

void ItemInInventoryState::Update(float elapsedSec, IExamInterface* iFace, const vector<EntityInfo>& entities)
{
	ItemInfo item;
	Predicate = false;
		/*iFace->Inventory_GetItem(0, item) && 
		iFace->Inventory_GetItem(1, item) && 
		iFace->Inventory_GetItem(2, item);*/

}

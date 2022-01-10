#include "stdafx.h"
#include "ItemInViewState.h"
#include "IExamInterface.h"
#include "GOAP/Memory/Memory.h"


void ItemInViewState::Update(float elapsedSec, IExamInterface* iFace, const vector<EntityInfo>& entities)
{
	Predicate = false;
	
	for (auto entityInfo : entities)
	{
		if (entityInfo.Type == eEntityType::ITEM)
		{
			Predicate = true;
			ItemInfo item;
			if (iFace->Item_GetInfo(entityInfo, item))
				Memory::GetInstance()->AddItemToMemory(item);
		}
	}
	if (!Memory::GetInstance()->GetAllItems().empty())
	{
		Predicate = true;
	}
}

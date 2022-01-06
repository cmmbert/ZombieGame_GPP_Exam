#pragma once
#include "WorldState.h"

class ItemInInventoryState : public WorldState{
public:
	explicit ItemInInventoryState(bool predicate)
		: WorldState(predicate)
	{
		m_Name = "ItemInInventory";
	}

	void Update(float elapsedSec, IExamInterface* iFace, const vector<EntityInfo>& entities) override;
};

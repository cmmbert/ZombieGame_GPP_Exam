#pragma once
#include "WorldState.h"

class NextToPickup : public WorldState {
public:
	explicit NextToPickup(bool predicate)
		: WorldState(predicate)
	{
		m_Name = "NextToPickup";
	}

	void Update(float elapsedSec, IExamInterface* iFace, const vector<EntityInfo>& entities) override;
};

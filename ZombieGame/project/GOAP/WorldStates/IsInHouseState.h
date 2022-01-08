#pragma once
#include "WorldState.h"

class IsInHouseState : public WorldState {
public:
	explicit IsInHouseState(bool predicate)
		: WorldState(predicate)
	{
		m_Name = "IsInHouseState";
	}

	void Update(float elapsedSec, IExamInterface* iFace, const vector<EntityInfo>& entities) override;
};
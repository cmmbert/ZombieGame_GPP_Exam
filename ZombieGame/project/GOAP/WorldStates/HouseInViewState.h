#pragma once
#include "WorldState.h"

class HouseInViewState : public WorldState {
public:
	explicit HouseInViewState(bool predicate)
		: WorldState(predicate)
	{
		m_Name = "HouseInViewState";
	}

	void Update(float elapsedSec, IExamInterface* iFace, const vector<EntityInfo>& entities) override;
};

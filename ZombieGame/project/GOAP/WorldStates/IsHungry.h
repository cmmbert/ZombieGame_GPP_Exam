#pragma once
#include "WorldState.h"

class IsHungry : public WorldState {
public:
	explicit IsHungry(bool predicate)
		: WorldState(predicate)
	{
		m_Name = "IsHungry";
	}

	void Update(float elapsedSec, IExamInterface* iFace, const vector<EntityInfo>& entities) override;

private:
	float m_HungerThreshold = 5.f;
};


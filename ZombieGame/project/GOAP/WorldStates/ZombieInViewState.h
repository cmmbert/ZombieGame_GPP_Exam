#pragma once
#include "GOAP/WorldStates/WorldState.h"

class ZombieInViewState : public WorldState {
public:
	explicit ZombieInViewState(bool predicate)
		: WorldState(predicate)
	{
		m_Name = "ZombieInViewState";
	}

	void Update(float elapsedSec, IExamInterface* iFace, const vector<EntityInfo>& entities) override;
};
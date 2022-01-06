#pragma once
#include "GOAP/WorldStates/WorldState.h"

class WanderlustState : public WorldState {
public:
	explicit WanderlustState(bool predicate)
		: WorldState(predicate)
	{
		m_Name = "Wanderlust";
	}

	void Update(float elapsedSec, IExamInterface* iFace, const vector<EntityInfo>& entities) override;
};

#pragma once
#include "WorldState.h"

class IsHurtState : public WorldState {
public:
	explicit IsHurtState(bool predicate)
		: WorldState(predicate)
	{
		m_Name = "IsHurtState";
	}

	void Update(float elapsedSec, IExamInterface* iFace, const vector<EntityInfo>& entities) override;

private:
	float m_HealthThreshold = 5.f;
};

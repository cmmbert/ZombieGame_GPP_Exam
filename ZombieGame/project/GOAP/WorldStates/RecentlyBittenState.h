#pragma once
#include "GOAP/WorldStates/WorldState.h"

class RecentlyBittenState : public WorldState {
public:
	explicit RecentlyBittenState(bool predicate)
		: WorldState(predicate)
	{
		m_Name = "RecentlyBittenState";
	}

	void Update(float elapsedSec, IExamInterface* iFace, const vector<EntityInfo>& entities) override;

private:
	float m_DefaultGracePeriod = 2.f;
	float m_GracePeriod = 0.f;
};

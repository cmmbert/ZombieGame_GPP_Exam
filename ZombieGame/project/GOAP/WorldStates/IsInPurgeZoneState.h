#pragma once
#include "WorldState.h"

class IsInPurgeZoneState : public WorldState {
public:
	explicit IsInPurgeZoneState(bool predicate)
		: WorldState(predicate)
	{
		m_Name = "IsInPurgeZoneState";
	}

	void Update(float elapsedSec, IExamInterface* iFace, const vector<EntityInfo>& entities) override;
};
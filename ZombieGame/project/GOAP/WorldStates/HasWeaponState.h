#pragma once
#include "WorldState.h"

class HasWeaponState : public WorldState {
public:
	explicit HasWeaponState(bool predicate)
		: WorldState(predicate)
	{
		m_Name = "HasWeaponState";
	}

	void Update(float elapsedSec, IExamInterface* iFace, const vector<EntityInfo>& entities) override;
};


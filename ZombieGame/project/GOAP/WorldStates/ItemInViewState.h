#pragma once
#include "WorldState.h"

class ItemInViewState : public WorldState {
public:
	explicit ItemInViewState(bool predicate)
		: WorldState(predicate)
	{
		m_Name = "ItemInView";
	}

	void Update(float elapsedSec, IExamInterface* iFace, const vector<EntityInfo>& entities) override;
};



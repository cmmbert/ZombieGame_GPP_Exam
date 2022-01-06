#pragma once
#include "GOAP/Actions/Action.h"

class MoveToPickup final : public Action
{
public:
	MoveToPickup();
	bool Execute(SteeringPlugin_Output& steeringOutput, IExamInterface* iFace, const vector<EntityInfo>& entities) override;
};


#pragma once
#include "GOAP/Actions/Action.h"

class PickupAction final : public Action
{
public:
	PickupAction();
	bool Execute(SteeringPlugin_Output& steeringOutput, IExamInterface* iFace, const vector<EntityInfo>& entities) override;
};


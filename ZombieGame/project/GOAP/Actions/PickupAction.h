#pragma once
#include "GOAP/Actions/Action.h"

class PickupAction final : public Action
{
public:
	PickupAction();
	SteeringPlugin_Output Execute(IExamInterface* iFace, const vector<EntityInfo>& entities) override;
};


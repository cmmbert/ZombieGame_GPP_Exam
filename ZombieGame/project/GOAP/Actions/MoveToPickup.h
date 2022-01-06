#pragma once
#include "GOAP/Actions/Action.h"

class MoveToPickup final : public Action
{
public:
	MoveToPickup();
	SteeringPlugin_Output Execute(IExamInterface* iFace, const vector<EntityInfo>& entities) override;
};


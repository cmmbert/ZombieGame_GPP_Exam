#pragma once
#include "GOAP/Actions/Action.h"

class LeaveHouse final : public Action
{
public:
	LeaveHouse();
	bool Execute(float elapsedSec, SteeringPlugin_Output& steeringOutput, IExamInterface* iFace, const vector<EntityInfo>& entities) override;
};
#pragma once
#include "GOAP/Actions/Action.h"

class RunFromPurge final : public Action
{
public:
	RunFromPurge();
	bool Execute(float elapsedSec, SteeringPlugin_Output& steeringOutput, IExamInterface* iFace, const vector<EntityInfo>& entities) override;
};

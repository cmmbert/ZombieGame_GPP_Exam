#pragma once
#include "GOAP/Actions/Action.h"

class Wander final : public Action
{
public:
	Wander();
	bool Execute(SteeringPlugin_Output& steeringOutput, IExamInterface* iFace, const vector<EntityInfo>& entities) override;
};


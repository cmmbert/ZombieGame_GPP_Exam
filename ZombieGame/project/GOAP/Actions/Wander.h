#pragma once
#include "GOAP/Actions/Action.h"

class Wander final : public Action
{
public:
	Wander();
	SteeringPlugin_Output Execute(IExamInterface* iFace, const vector<EntityInfo>& entities) override;
};


#pragma once
#include "GOAP/Actions/Action.h"

class MoveIntoHouse final : public Action
{
public:
	MoveIntoHouse();
	bool Execute(float elapsedSec, SteeringPlugin_Output& steeringOutput, IExamInterface* iFace, const vector<EntityInfo>& entities) override;
};
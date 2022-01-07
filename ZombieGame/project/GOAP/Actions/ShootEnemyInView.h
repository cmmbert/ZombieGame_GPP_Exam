#pragma once
#include "GOAP/Actions/Action.h"

class ShootEnemyInView final : public Action
{
public:
	ShootEnemyInView();
	bool Execute(float elapsedSec, SteeringPlugin_Output& steeringOutput, IExamInterface* iFace, const vector<EntityInfo>& entities) override;
};
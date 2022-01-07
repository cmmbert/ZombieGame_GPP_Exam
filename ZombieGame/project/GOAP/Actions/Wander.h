#pragma once
#include "GOAP/Actions/Action.h"

class Wander final : public Action
{
public:
	Wander();
	bool Execute(float elapsedSec, SteeringPlugin_Output& steeringOutput, IExamInterface* iFace, const vector<EntityInfo>& entities) override;

private:
	Elite::Vector2 m_WanderDir;
	float m_WanderTime = FLT_MAX - 10.f; //To trigger the random direction
	float m_MaxWanderTime = 10.f;
};


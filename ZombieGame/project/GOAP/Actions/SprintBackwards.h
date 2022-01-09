#pragma once
#include "GOAP/Actions/Action.h"

class SprintBackwards final : public Action
{
public:
	SprintBackwards();
	bool Execute(float elapsedSec, SteeringPlugin_Output& steeringOutput, IExamInterface* iFace, const vector<EntityInfo>& entities) override;

private:
	Elite::Vector2 m_Direction;
	float m_Duration = 1.8f; //is tightly linked to RecentlyBittenState
	float m_TimeSpent = 0;
};
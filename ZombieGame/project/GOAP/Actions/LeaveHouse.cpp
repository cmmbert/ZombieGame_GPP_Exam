#include "stdafx.h"
#include "LeaveHouse.h"

#include "GOAP/WorldStates/IsInHouseState.h"

LeaveHouse::LeaveHouse()
{
	m_Name = typeid(this).name();
	m_Preconditions.push_back(new IsInHouseState(false));
	m_EffectOnWorld.push_back(new IsInHouseState(true));
}

bool LeaveHouse::Execute(float elapsedSec, SteeringPlugin_Output& steeringOutput, IExamInterface* iFace,
                         const vector<EntityInfo>& entities)
{
	return true;
}

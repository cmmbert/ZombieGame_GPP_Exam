#include "stdafx.h"
#include "LeaveHouse.h"

#include <IExamInterface.h>

#include "GOAP/WorldStates/IsInHouseState.h"

LeaveHouse::LeaveHouse()
{
	m_Name = typeid(this).name();
	m_Preconditions.push_back(new IsInHouseState(true));
	m_EffectOnWorld.push_back(new IsInHouseState(false));
}

bool LeaveHouse::Execute(float elapsedSec, SteeringPlugin_Output& steeringOutput, IExamInterface* iFace,
                         const vector<EntityInfo>& entities)
{
	auto target = iFace->NavMesh_GetClosestPathPoint({ 0,0 });
	auto agentInfo = iFace->Agent_GetInfo();
	steeringOutput.LinearVelocity = (target - agentInfo.Position).GetNormalized() * agentInfo.MaxLinearSpeed;
	return true;
}

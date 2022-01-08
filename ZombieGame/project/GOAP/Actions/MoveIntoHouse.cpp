#include "stdafx.h"
#include "MoveIntoHouse.h"

#include <IExamInterface.h>

#include "GOAP/WorldStates/HouseInViewState.h"
#include "GOAP/WorldStates/IsInHouseState.h"

MoveIntoHouse::MoveIntoHouse()
{
	m_Name = typeid(this).name();
	m_Preconditions.push_back(new HouseInViewState(true));
	m_Preconditions.push_back(new IsInHouseState(false));
	m_EffectOnWorld.push_back(new IsInHouseState(true));
}

bool MoveIntoHouse::Execute(float elapsedSec, SteeringPlugin_Output& steeringOutput, IExamInterface* iFace,
	const vector<EntityInfo>& entities)
{
	HouseInfo closestHouse;
	if (!iFace->Fov_GetHouseByIndex(0, closestHouse))
		assert(false); //There's probably something wrong with HouseInViewState. We should not execute this when there's no houses in our FOV
	else
	{
		Elite::Vector2 target = iFace->NavMesh_GetClosestPathPoint(closestHouse.Center);
		auto agentInfo = iFace->Agent_GetInfo();
		steeringOutput.LinearVelocity = (target - agentInfo.Position).GetNormalized() * agentInfo.MaxLinearSpeed;
	}

	return true;
}

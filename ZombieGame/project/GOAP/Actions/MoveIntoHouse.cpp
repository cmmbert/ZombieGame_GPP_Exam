#include "stdafx.h"
#include "MoveIntoHouse.h"

#include <IExamInterface.h>

#include "GOAP/Memory/Memory.h"
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
	auto agentInfo = iFace->Agent_GetInfo();

	HouseInfo hi;
	if (!iFace->Fov_GetHouseByIndex(0, hi))
		assert(false); //There's probably something wrong with HouseInViewState. We should not execute this when there's no houses in our FOV

	HouseInfo closestValidHouse;
	closestValidHouse.Center = Elite::Vector2(FLT_MAX, FLT_MAX);
	for (int i = 0;; ++i)
	{
		if (iFace->Fov_GetHouseByIndex(i, hi))
		{
			if (Memory::GetInstance()->IsHouseInMemory(hi))
			{
				continue;
			}
			if((hi.Center - agentInfo.Position).Magnitude() < (closestValidHouse.Center - agentInfo.Position).Magnitude())
			{
				closestValidHouse = hi;
			}
		}
		break;
	}

	Elite::Vector2 target = iFace->NavMesh_GetClosestPathPoint(closestValidHouse.Center);
	steeringOutput.LinearVelocity = (target - agentInfo.Position).GetNormalized() * agentInfo.MaxLinearSpeed;

	return true;
}

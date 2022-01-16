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
	

	Elite::Vector2 target = iFace->NavMesh_GetClosestPathPoint(Memory::GetInstance()->GetLastClosestHouse().Center);
	steeringOutput.LinearVelocity = (target - agentInfo.Position).GetNormalized() * agentInfo.MaxLinearSpeed;
	iFace->Draw_Circle(target, 2, Elite::Vector3(0, 1, 0));

	return true;
}

#include "stdafx.h"
#include "LeaveHouse.h"

#include <IExamInterface.h>

#include "GOAP/Memory/Memory.h"
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
	auto agentInfo = iFace->Agent_GetInfo();
	auto dir = (Elite::Vector2(cosf(agentInfo.Orientation - static_cast<float>(M_PI / 2)), sinf(agentInfo.Orientation - static_cast<float>(M_PI / 2)))).GetNormalized() + agentInfo.Position;
	auto target = iFace->NavMesh_GetClosestPathPoint(dir * 10);
	iFace->Draw_Circle(dir * 10, 2, Elite::Vector3(0, 0, 1), 0.9f);
	steeringOutput.LinearVelocity = (target - agentInfo.Position).GetNormalized() * agentInfo.MaxLinearSpeed;

	HouseInfo hi;
	if (iFace->Fov_GetHouseByIndex(0, hi))
		Memory::GetInstance()->AddHouseToMemory(hi);
	return true;
}

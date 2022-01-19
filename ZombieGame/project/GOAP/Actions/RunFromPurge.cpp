#include "stdafx.h"
#include "RunFromPurge.h"

#include <IExamInterface.h>

#include "GOAP/Memory/Memory.h"
#include "GOAP/WorldStates/IsInPurgeZoneState.h"

RunFromPurge::RunFromPurge()
{
	m_Preconditions.push_back(new IsInPurgeZoneState(true));
	m_EffectOnWorld.push_back(new IsInPurgeZoneState(false));
	m_Name = typeid(this).name();
}

bool RunFromPurge::Execute(float elapsedSec, SteeringPlugin_Output& steeringOutput, IExamInterface* iFace,
	const vector<EntityInfo>& entities)
{
	Elite::Vector2 target;
	auto allSeenPurges = Memory::GetInstance()->GetAllSeenPurges();
	if (allSeenPurges.empty()) return false;
	PurgeZoneInfo purge = allSeenPurges[0];

	auto worldInfo = iFace->World_GetInfo();
	auto agentInfo = iFace->Agent_GetInfo();

	if((worldInfo.Center - purge.Center).Magnitude() > (worldInfo.Center - agentInfo.Position).Magnitude())
		target = (worldInfo.Center - purge.Center).GetNormalized() * 1000;
	else
		target = (agentInfo.Position - purge.Center).GetNormalized() * 1000;
	target = iFace->NavMesh_GetClosestPathPoint(target);
	steeringOutput.LinearVelocity = (target - agentInfo.Position).GetNormalized() * agentInfo.MaxLinearSpeed * iFace->Agent_GetInfo().MaxLinearSpeed;
	iFace->Draw_Circle(target, 2, Elite::Vector3(0, 1, 0));

	if ((iFace->Agent_GetInfo().Position - purge.Center).Magnitude() < purge.Radius / 2)
		steeringOutput.RunMode = true;

	return true;
}

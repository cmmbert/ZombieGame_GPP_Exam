#include "stdafx.h"
#include "RunFromPurge.h"

#include <IExamInterface.h>

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
	for(const auto& entity : entities)
	{
		if(entity.Type == eEntityType::PURGEZONE)
		{
			PurgeZoneInfo purge;
			iFace->PurgeZone_GetInfo(entity, purge);
			target = (iFace->World_GetInfo().Center - purge.Center).GetNormalized() * 1000;
			steeringOutput.LinearVelocity = iFace->NavMesh_GetClosestPathPoint(target) * iFace->Agent_GetInfo().MaxLinearSpeed;
			if ((iFace->Agent_GetInfo().Position - purge.Center).Magnitude() < purge.Radius / 2)
				steeringOutput.RunMode = true;

			return true;
		}
	}
}

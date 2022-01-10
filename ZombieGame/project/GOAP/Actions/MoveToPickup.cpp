#include "stdafx.h"
#include "MoveToPickup.h"

#include <IExamInterface.h>

#include "GOAP/Memory/Memory.h"
#include "GOAP/WorldStates/ItemInViewState.h"
#include "GOAP/WorldStates/NextToPickupState.h"

MoveToPickup::MoveToPickup()
{
	m_Preconditions.push_back(new ItemInViewState(true));
	m_EffectOnWorld.push_back(new NextToPickup(true));
	m_Name = typeid(this).name();
	m_Weight = 2.5f;
}

bool MoveToPickup::Execute(float elapsedSec, SteeringPlugin_Output& steeringOutput, IExamInterface* iFace, const vector<EntityInfo>& entities)
{
	//if (entities.empty()) return false;
	
	auto agentInfo = iFace->Agent_GetInfo();
	
	Elite::Vector2 target;
	float closestDistance = FLT_MAX;
	for(auto item : Memory::GetAllItems())
	{
		float distance = (item.Location - agentInfo.Position).Magnitude();
		if (distance < closestDistance)
		{
			closestDistance = distance;
			steeringOutput.LinearVelocity = item.Location - agentInfo.Position;
		}
	}
	steeringOutput.LinearVelocity = steeringOutput.LinearVelocity.GetNormalized() * agentInfo.MaxLinearSpeed;
	return true;
}

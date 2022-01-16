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
	auto agentInfo = iFace->Agent_GetInfo();
	
	Elite::Vector2 target;
	float closestDistance = FLT_MAX;
	for(auto item : Memory::GetAllItems())
	{
		float distance = (item.Location - agentInfo.Position).Magnitude();
		if (distance < closestDistance)
		{
			closestDistance = distance;
			target = iFace->NavMesh_GetClosestPathPoint(item.Location);
			steeringOutput.LinearVelocity = target - agentInfo.Position;
		}
	}
	steeringOutput.LinearVelocity = steeringOutput.LinearVelocity.GetNormalized() * agentInfo.MaxLinearSpeed;
	iFace->Draw_Circle(target, 2, Elite::Vector3(0, 1, 0));

	return true;
}

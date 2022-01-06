#include "stdafx.h"
#include "MoveToPickup.h"

#include <IExamInterface.h>

#include "GOAP/WorldStates/ItemInViewState.h"
#include "GOAP/WorldStates/NextToPickupState.h"

MoveToPickup::MoveToPickup()
{
	m_Preconditions.push_back(new ItemInViewState(true));
	m_EffectOnWorld.push_back(new NextToPickup(true));
	m_Name = typeid(this).name();
	m_Weight = 2.5f;
}

SteeringPlugin_Output MoveToPickup::Execute(IExamInterface* iFace, const vector<EntityInfo>& entities)
{
	SteeringPlugin_Output output{};

	if (entities.empty()) return output;
	Elite::Vector2 target;

	float closestDistance = FLT_MAX;
	auto agentInfo = iFace->Agent_GetInfo();

	for(const auto& entity : entities)
	{
		if(entity.Type == eEntityType::ITEM)
		{
			float distance = (entity.Location - agentInfo.Position).Magnitude();
			if(distance < closestDistance)
			{
				closestDistance = distance;
				output.LinearVelocity = entity.Location - agentInfo.Position;
			}
		}
	}
	output.LinearVelocity = output.LinearVelocity.GetNormalized() * agentInfo.MaxLinearSpeed;
	return output;
}

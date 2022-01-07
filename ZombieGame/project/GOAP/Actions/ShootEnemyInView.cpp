#include "stdafx.h"
#include "ShootEnemyInView.h"

#include <IExamInterface.h>

#include "GOAP/WorldStates/HasWeaponState.h"
#include "GOAP/WorldStates/ZombieInViewState.h"

ShootEnemyInView::ShootEnemyInView()
{
	m_Preconditions.push_back(new HasWeaponState(true));
	m_EffectOnWorld.push_back(new ZombieInViewState(false));
	m_Name = typeid(this).name();
	m_Weight = 2.5f;
}

bool ShootEnemyInView::Execute(float elapsedSec, SteeringPlugin_Output& steeringOutput, IExamInterface* iFace,
	const vector<EntityInfo>& entities)
{
	auto agent = iFace->Agent_GetInfo();

	Elite::Vector2 targetPosition{FLT_MAX, FLT_MAX};
	for (auto entityInfo : entities)
	{
		if (entityInfo.Type == eEntityType::ENEMY)
		{
			auto currentVector = entityInfo.Location - agent.Position;
			if (currentVector.Magnitude() < (targetPosition - agent.Position).Magnitude())
				targetPosition = entityInfo.Location;
			break;
		}
	}
	steeringOutput.LinearVelocity = targetPosition - agent.Position;
	return true;
}

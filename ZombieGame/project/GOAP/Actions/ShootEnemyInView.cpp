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

	auto targetVector = targetPosition - agent.Position;
	auto dir = agent.Orientation;
	Elite::Vector2 dirVector = Elite::Vector2(cos(dir), sin(dir));
	float crossProd = targetVector.Cross(dirVector);
	float sign = crossProd / abs(crossProd);
	auto part1 = (dirVector.x * targetVector.x) + (dirVector.y * targetVector.y);
	auto part2 = (sqrtf(powf(dirVector.x, 2) + powf(dirVector.y, 2)) * sqrtf(powf(targetVector.x, 2) + powf(targetVector.y, 2))) * sign;
	auto adjustAngle = acosf(part1 / part2);
	adjustAngle *= 180 / static_cast<float>(M_PI);
	if (adjustAngle < 1 && adjustAngle > -1)
	{
		iFace->Inventory_UseItem(0);
		ItemInfo pistol;
		iFace->Inventory_GetItem(0, pistol);
		if (iFace->Weapon_GetAmmo(pistol) == 0)
			iFace->Inventory_RemoveItem(0);
	}
	else if (adjustAngle > 0)
		steeringOutput.AngularVelocity = -agent.MaxAngularSpeed;
	else
		steeringOutput.AngularVelocity = agent.MaxAngularSpeed;

	steeringOutput.LinearVelocity = targetPosition - agent.Position;
	return true;
}

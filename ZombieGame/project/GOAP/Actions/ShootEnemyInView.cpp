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
	iFace->Draw_Circle(targetPosition, 2, Elite::Vector3(1, 0, 0), 0.9f);

	auto dir = (Elite::Vector2(cosf(agent.Orientation - static_cast<float>(M_PI /2)), sinf(agent.Orientation - static_cast<float>(M_PI / 2)))).GetNormalized();
	auto target = (targetPosition - agent.Position).GetNormalized();
	auto adjustVal = Elite::Cross(dir, target);
	std::cout << adjustVal << "\n";
	if (adjustVal < 0.1f && adjustVal > -0.1f)
	{
		iFace->Inventory_UseItem(0);
		ItemInfo pistol;
		iFace->Inventory_GetItem(0, pistol);
		if (iFace->Weapon_GetAmmo(pistol) == 0)
			iFace->Inventory_RemoveItem(0);
	}
	else if (adjustVal > 0)
		steeringOutput.AngularVelocity = -agent.MaxAngularSpeed;
	else
		steeringOutput.AngularVelocity = agent.MaxAngularSpeed;
	
	steeringOutput.LinearVelocity = targetPosition - agent.Position;
	return true;
}

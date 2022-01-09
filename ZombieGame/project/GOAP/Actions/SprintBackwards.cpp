#include "stdafx.h"
#include "SprintBackwards.h"

#include <IExamInterface.h>

#include "GOAP/WorldStates/HasWeaponState.h"
#include "GOAP/WorldStates/RecentlyBittenState.h"

SprintBackwards::SprintBackwards()
{
	m_Preconditions.push_back(new HasWeaponState(true));
	m_Preconditions.push_back(new RecentlyBittenState(true));
	m_EffectOnWorld.push_back(new RecentlyBittenState(false));
	m_Name = typeid(this).name();
	m_Weight = 2.5f;
}

bool SprintBackwards::Execute(float elapsedSec, SteeringPlugin_Output& steeringOutput, IExamInterface* iFace,
	const vector<EntityInfo>& entities)
{
	auto agent = iFace->Agent_GetInfo();
	if(m_Direction == Elite::Vector2{0,0})
		m_Direction = Elite::Vector2(cosf(agent.Orientation - static_cast<float>(M_PI / 2)), sinf(agent.Orientation - static_cast<float>(M_PI / 2)));
	steeringOutput.LinearVelocity = m_Direction * agent.MaxLinearSpeed;
	steeringOutput.RunMode = true;

	m_TimeSpent += elapsedSec;
	if (m_TimeSpent > m_Duration)
	{
		m_Direction = { 0,0 };
		m_TimeSpent = 0;
	}

	steeringOutput.AutoOrient = false;

	auto target = -m_Direction;
	auto adjustVal = Elite::Cross(m_Direction.GetNormalized(), target.GetNormalized());
	std::cout << adjustVal << "\n";
	if (adjustVal > 0)
		steeringOutput.AngularVelocity = -agent.MaxAngularSpeed;
	else
		steeringOutput.AngularVelocity = agent.MaxAngularSpeed;
	return true;
}

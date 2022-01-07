#include "stdafx.h"
#include "Wander.h"

#include <IExamInterface.h>

#include "GOAP/WorldStates/WanderlustState.h"

Wander::Wander()
{
	m_Name = typeid(this).name();
	m_EffectOnWorld.push_back(new WanderlustState(true));
	m_Weight = 100;
}

bool Wander::Execute(float elapsedSec, SteeringPlugin_Output& steeringOutput, IExamInterface* iFace, const vector<EntityInfo>& entities)
{
	m_WanderTime += elapsedSec;
	if (m_WanderTime > m_MaxWanderTime)
	{
		float degree = Elite::randomFloat(static_cast<float>(E_PI) * 2);
		m_WanderDir = Elite::Vector2(cos(degree), sin(degree));
		m_WanderTime = 0;
		std::cout << "******New rand direction********\n";
	}
	steeringOutput.LinearVelocity = m_WanderDir * iFace->Agent_GetInfo().MaxLinearSpeed;
	return true;
}

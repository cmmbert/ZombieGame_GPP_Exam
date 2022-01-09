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
	//return false;
	m_WanderTime += elapsedSec;
	auto worldInfo = iFace->World_GetInfo();
	auto agentPos = iFace->Agent_GetInfo().Position;
	bool outOfBounds =
		agentPos.y > worldInfo.Dimensions.y / 2 ||
		agentPos.x > worldInfo.Dimensions.x / 2 ||
		agentPos.y < -worldInfo.Dimensions.y / 2 ||
		agentPos.x < -worldInfo.Dimensions.x / 2;
	if (outOfBounds)
	{
		m_WanderDir = (worldInfo.Center - agentPos).GetNormalized();
		m_WanderTime = 0;
	}
	else if (m_WanderTime > m_MaxWanderTime)
	{
		float degree = Elite::randomFloat(static_cast<float>(E_PI) * 2);
		m_WanderDir = Elite::Vector2(cos(degree), sin(degree));
		m_WanderTime = 0;
		std::cout << "******New rand direction********\n";
	}
	steeringOutput.LinearVelocity = m_WanderDir * iFace->Agent_GetInfo().MaxLinearSpeed;

	if (iFace->Agent_GetInfo().WasBitten) steeringOutput.RunMode = true;
	return true;
}

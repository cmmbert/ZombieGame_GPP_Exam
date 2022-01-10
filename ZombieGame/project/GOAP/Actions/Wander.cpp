#include "stdafx.h"
#include "Wander.h"

#include <IExamInterface.h>

#include "GOAP/Memory/Memory.h"
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
	auto agent = iFace->Agent_GetInfo();
	auto agentPos = agent.Position;

	if (agent.CurrentLinearSpeed < agent.MaxLinearSpeed / 10)
		m_TimeStandingStill += elapsedSec;
	else
		m_TimeStandingStill = 0;


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
	else if (m_WanderTime > m_MaxWanderTime || m_TimeStandingStill > m_MaxTimeStandStill)
	{
		float degree = Elite::randomFloat(static_cast<float>(E_PI) * 2);
		m_WanderDir = Elite::Vector2(cos(degree), sin(degree));
		m_WanderTime = 0;
		std::cout << "******New rand direction********\n";
	}
	auto wanderTarget = m_WanderDir * 50 + agentPos;
	auto closestPathPoint = iFace->NavMesh_GetClosestPathPoint(wanderTarget);
	iFace->Draw_Circle(wanderTarget, 2, Elite::Vector3(1, 0, 0));
	iFace->Draw_Circle(closestPathPoint, 2, Elite::Vector3(0, 1, 0));
	steeringOutput.LinearVelocity = (closestPathPoint - agentPos) * iFace->Agent_GetInfo().MaxLinearSpeed;

	if (iFace->Agent_GetInfo().WasBitten) steeringOutput.RunMode = true;
	return true;
}

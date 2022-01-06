#include "stdafx.h"
#include "Wander.h"

#include "GOAP/WorldStates/WanderlustState.h"

Wander::Wander()
{
	m_Name = typeid(this).name();
	m_EffectOnWorld.push_back(new WanderlustState(true));
	m_Weight = 100;
}

bool Wander::Execute(SteeringPlugin_Output& steeringOutput, IExamInterface* iFace, const vector<EntityInfo>& entities)
{
	return false;
}

#include "stdafx.h"
#include "Wander.h"

#include "GOAP/WorldStates/WanderlustState.h"

Wander::Wander()
{
	m_Name = typeid(this).name();
	m_EffectOnWorld.push_back(new WanderlustState(true));
	m_Weight = 100;
}

SteeringPlugin_Output Wander::Execute(IExamInterface* iFace, const vector<EntityInfo>& entities)
{
	SteeringPlugin_Output output{};
	return output;
}

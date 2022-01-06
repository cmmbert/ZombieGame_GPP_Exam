#pragma once
#include "GOAP/WorldStates/WorldState.h"
#include <vector>

class Action
{
public:
	//virtual void DoAction();
	std::vector<WorldState*> GetPreconditions() const { return m_Preconditions; }
	std::vector<WorldState*> GetEffectsOnWorld() const { return m_EffectOnWorld; }
	int m_GraphNodeIdx;
	float GetWeight() { return m_Weight; }

	std::string GetName() { return m_Name; }


	virtual SteeringPlugin_Output Execute(IExamInterface* iFace, const vector<EntityInfo>& entities) = 0;
protected:
	~Action();
	std::vector<WorldState*> m_Preconditions;
	std::vector<WorldState*> m_EffectOnWorld;
	float m_Weight = 1.f;

	std::string m_Name = "Default";
};


#pragma once
#include "WorldState.h"
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
protected:
	~Action();
	std::vector<WorldState*> m_Preconditions;
	std::vector<WorldState*> m_EffectOnWorld;
	float m_Weight = 1.f;

	std::string m_Name = "Default";
};


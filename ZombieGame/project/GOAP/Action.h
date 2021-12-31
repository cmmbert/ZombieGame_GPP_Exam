#pragma once
#include "WorldState.h"

class Action
{
public:
	virtual void DoAction();
	std::vector<WorldState*> GetPreconditions() const { return m_Preconditions; }
	std::vector<WorldState*> GetEffectsOnWorld() const { return m_EffectOnWorld; }
	int m_GraphNodeIdx;
	int GetWeight() { return m_Weight; }
protected:
	~Action();
	std::vector<WorldState*> m_Preconditions;
	std::vector<WorldState*> m_EffectOnWorld;
	int m_Weight;

};


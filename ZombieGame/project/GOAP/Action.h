#pragma once
#include "WorldState.h"

class Action
{
public:
	virtual void DoAction();
protected:
	~Action();
	std::vector<WorldState*> m_Preconditions;
	std::vector<WorldState*> m_EffectOnWorld;

};


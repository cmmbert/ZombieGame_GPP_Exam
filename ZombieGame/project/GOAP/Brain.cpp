#include "stdafx.h"
#include "Brain.h"

SteeringPlugin_Output Brain::CalculateAction(IExamInterface* iFace)
{
	SteeringPlugin_Output steering;

	//Figure out what to do
	WorldState* currentGoal;
	for (auto* goal : m_Goals)
	{
		auto result = std::find(m_WorldStates.begin(), m_WorldStates.end(), goal);
		if(result != std::end(m_WorldStates))
		{
			if(m_WorldStates[int(*result)]->Predicate == goal->Predicate)
				continue;
			else
				currentGoal = goal;
		}
	}

	//Figure out how to do it
	Action* chosenAction;
	std::find_if(m_Actions.begin(), m_Actions.end(), )

	return steering;
}

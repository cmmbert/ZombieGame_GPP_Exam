#include "stdafx.h"
#include "Brain.h"

#include "Actions/MoveTo.h"
#include "Actions/PickupAction.h"

Brain::Brain()
{
	m_Actions.push_back(new PickupAction());
	m_Actions.push_back(new MoveTo());
}

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
			break;
		}
	}

	//Figure out how to do it
	Action* chosenAction;
	for (auto* action : m_Actions)
	{
		auto effects = action->GetEffectsOnWorld();
		auto result = std::find(effects.begin(), effects.end(), currentGoal);
		if(result != std::end(effects))
		{
			if(effects[int(*result)]->Predicate == currentGoal->Predicate)
			{
				chosenAction = action;
				break;
			}
		}
	}

	for (auto* precond : chosenAction->GetPreconditions())
	{
		auto result = std::find(m_WorldStates.begin(), m_WorldStates.end(), precond);
		if (result != std::end(m_WorldStates))
		{
			if (m_WorldStates[int(*result)]->Predicate != currentGoal->Predicate)
			{
				//precondition not met
			}
		}
	}

	return steering;
}

void Brain::MakeGraph()
{
	for (auto* action : m_Actions)
	{
		action->m_GraphNodeIdx = m_pGraph->AddNode(new Elite::GraphNode2D(m_pGraph->GetNextFreeNodeIndex(), { 0,0 }));
	}
	for (auto* action : m_Actions)
	{
		for (auto* precondition : action->GetPreconditions())
		{
			//Get all actions that can fulfill precondition and add connection to this action
			for (auto* subAction : m_Actions)
			{
				for(auto* effect : subAction->GetEffectsOnWorld())
				{
					if(effect->Predicate == precondition->Predicate)
					{
						m_pGraph->AddConnection(new Elite::GraphConnection(subAction->m_GraphNodeIdx, action->m_GraphNodeIdx, subAction->GetWeight()));
					}
				}
			}
		}
	}
}

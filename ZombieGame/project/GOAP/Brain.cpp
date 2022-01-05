#include "stdafx.h"

#include "Brain.h"

#include "Actions/MoveTo.h"
#include "Actions/PickupAction.h"
#include "Actions/Wander.h"


Brain::Brain(std::vector<WorldState*>* pWorldStates)
{
	m_Actions.push_back(new PickupAction());
	m_Actions.push_back(new MoveTo());
	m_Actions.push_back(new Wander());
	m_pGraph = new Graph();
	m_Goals.push_back(new ItemInInventoryState(true));
	m_pWorldStates = pWorldStates;
}

SteeringPlugin_Output Brain::CalculateAction(/*IExamInterface* iFace*/)
{
	SteeringPlugin_Output steering;

	//Figure out what to do
	WorldState* currentGoal{};
	for (auto* goal : m_Goals)
	{
		auto result = std::find(m_pWorldStates->begin(), m_pWorldStates->end(), goal);
		if(result != std::end(*m_pWorldStates))
		{
			if((*m_pWorldStates)[int(*result)]->Predicate == goal->Predicate)
				continue;
			else
				currentGoal = goal;
			break;
		}
	}

	//Figure out how to do it
	Action* chosenAction{};
	

	for (auto* precond : chosenAction->GetPreconditions())
	{
		auto result = std::find(m_pWorldStates->begin(), m_pWorldStates->end(), precond);
		if (result != std::end(*m_pWorldStates))
		{
			if ((*m_pWorldStates)[int(*result)]->Predicate != currentGoal->Predicate)
			{
				//precondition not met
			}
		}
	}

	return steering;
}

void Brain::MakeGraph(WorldState* stateToAchieve, bool predicate)
{
	m_pGraph->Reset();
	auto startNode = m_pGraph->AddNode("startNode");
	auto endNode = m_pGraph->AddNode("endNode");
	for (auto* action : m_Actions)
	{
		action->m_GraphNodeIdx = m_pGraph->AddNode();
		m_pGraph->GetNodeByIdx(action->m_GraphNodeIdx)->SetDescription(action->GetName());

		//Connect this node to the startnode if this node can be used to start from
		bool conditionsMet = true;
		for (auto* precondition : action->GetPreconditions())
		{
			for (auto* worldState : *m_pWorldStates)
			{
				if (precondition->m_Name == worldState->m_Name && precondition->Predicate != worldState->Predicate) 
					conditionsMet = false;
			}
		}
		if(conditionsMet)
		{
			m_pGraph->AddConnection(startNode, action->m_GraphNodeIdx, 0);
		}

		//Connect this node to the endnode if this action achieves the goal
		bool actionAchievesGoal = false;
		for( auto* effect : action->GetEffectsOnWorld())
		{
			if(effect->m_Name == stateToAchieve->m_Name)
			{
				actionAchievesGoal = true;
				break;
			}
		}
		if(actionAchievesGoal)
		{
			m_pGraph->AddConnection(action->m_GraphNodeIdx, endNode, 0);
		}
	}
	for (auto* action : m_Actions)
	{
		//Get all actions that can fulfill precondition and add connection to this action
		for (auto* precondition : action->GetPreconditions())
		{
			for (auto* subAction : m_Actions)
			{
				if(subAction == action) continue;
				for(auto* effect : subAction->GetEffectsOnWorld())
				{
					if(effect->Predicate == precondition->Predicate)
					{
						m_pGraph->AddConnection(subAction->m_GraphNodeIdx, action->m_GraphNodeIdx, subAction->GetWeight());
					}
				}
			}
		}
	}


}

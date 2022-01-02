#include "stdafx.h"

#include "Brain.h"

#include "Actions/MoveTo.h"
#include "Actions/PickupAction.h"
#include "Actions/Wander.h"


Brain::Brain()
{
	m_Actions.push_back(new PickupAction());
	m_Actions.push_back(new MoveTo());
	m_Actions.push_back(new Wander());
	m_pGraph = new Graph();
	m_Goals.push_back(new ItemInInventoryState(true));

	m_WorldStates.push_back(new NextToPickup(false));
}

SteeringPlugin_Output Brain::CalculateAction(/*IExamInterface* iFace*/)
{
	SteeringPlugin_Output steering;

	//Figure out what to do
	WorldState* currentGoal{};
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
	Action* chosenAction{};
	

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
	m_pGraph->Reset();
	auto startNode = m_pGraph->AddNode("startNode");
	for (auto* action : m_Actions)
	{
		action->m_GraphNodeIdx = m_pGraph->AddNode();
		m_pGraph->GetNodeByIdx(action->m_GraphNodeIdx)->SetDescription(action->GetName());

		//Connect this node to the startnode if this node can be used to start from
		bool conditionsMet = true;
		for (auto* precondition : action->GetPreconditions())
		{
			for (auto* worldState : m_WorldStates)
			{
				if (precondition != worldState) conditionsMet = false;
			}
		}
		if(conditionsMet)
		{
			m_pGraph->AddConnection(startNode, action->m_GraphNodeIdx);
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

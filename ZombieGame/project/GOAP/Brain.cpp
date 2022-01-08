#include "stdafx.h"

#include "Brain.h"

#include "Actions/MoveToPickup.h"
#include "Actions/PickupAction.h"
#include "Actions/Wander.h"
#include "Graph/Dijkstra.h"

#include "IExamInterface.h"
#include "Actions/LeaveHouse.h"
#include "Actions/MoveIntoHouse.h"
#include "Actions/ShootEnemyInView.h"
#include "WorldStates/IsInHouseState.h"
#include "WorldStates/ItemInInventoryState.h"
#include "WorldStates/WanderlustState.h"
#include "WorldStates/ZombieInViewState.h"


Brain::Brain(std::vector<WorldState*>* pWorldStates)
{
	m_Actions.push_back(new PickupAction());
	m_Actions.push_back(new MoveIntoHouse());
	m_Actions.push_back(new ShootEnemyInView());
	m_Actions.push_back(new MoveToPickup());
	m_Actions.push_back(new LeaveHouse());
	m_Actions.push_back(new Wander());
	m_pGraph = new Graph();
	m_Goals.push_back(new ZombieInViewState(false));
	m_Goals.push_back(new ItemInInventoryState(true));
	m_Goals.push_back(new IsInHouseState(false));
	m_Goals.push_back(new WanderlustState(true));
	m_pWorldStates = pWorldStates;
}

bool Brain::CalculateAction(float elapsedSec, SteeringPlugin_Output& steeringOutput, IExamInterface* iFace, const vector<EntityInfo>& entities)
{
	
	//Figure out what to do
	WorldState* currentGoal = nullptr;
	vector<GraphNode*> actions;
	for (auto* goal : m_Goals)
	{
		for(auto* state : (*m_pWorldStates))
		{
			if(state->m_Name == goal->m_Name && state->Predicate != goal->Predicate)
			{
				//Figure out how to do it
				if (goal->m_Name == "ZombieInViewState")
					auto test = 5;
				MakeGraph(goal);
				actions = Dijkstra::FindPath(m_pGraph, m_pGraph->GetNodeByIdx(0), m_pGraph->GetNodeByIdx(1));

				//Check if endnode is present, if so then we have found our goal
				//If endnode is not present in the path then the goal is impossible right now
				if (std::find(actions.begin(), actions.end(), m_pGraph->GetNodeByIdx(1)) != actions.end())
				{
					currentGoal = goal;
					break;
				}
			}
		}
		if (currentGoal != nullptr) break;
	}
	std::cout << actions[1]->GetDescription() << "\n";
	Action* currentAction = nullptr;
	for(auto pAction : m_Actions)
	{
		if(pAction->GetName() == actions[1]->GetDescription())
		{
			currentAction = pAction;
			break;
		}
	}
	
	

	return currentAction->Execute(elapsedSec, steeringOutput, iFace, entities);;
}

void Brain::MakeGraph(WorldState* stateToAchieve)
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
			if(effect->m_Name == stateToAchieve->m_Name && effect->Predicate == stateToAchieve->Predicate)
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
					if(effect->m_Name == precondition->m_Name && effect->Predicate == precondition->Predicate)
					{
						m_pGraph->AddConnection(subAction->m_GraphNodeIdx, action->m_GraphNodeIdx, subAction->GetWeight());
					}
				}
			}
		}
	}

}

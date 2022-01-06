#pragma once
#include "stdafx.h"


#include "Actions/Action.h"
#include "Goal.h"
#include "Exam_HelperStructs.h"
#include <vector>

#include "Graph/Graph.h"

class IExamInterface;


class Brain
{
public:
	Brain(std::vector<WorldState*>* pWorldStates);
	SteeringPlugin_Output CalculateAction(IExamInterface* iFace);
	void MakeGraph(WorldState* stateToAchieve);
private:
	std::vector<Action*> m_Actions;
	std::vector<WorldState*>* m_pWorldStates;
	std::vector<WorldState*> m_Goals;


	Graph* m_pGraph{};

};


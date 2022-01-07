#pragma once
#include "stdafx.h"


#include "Actions/Action.h"
#include "Exam_HelperStructs.h"
#include <vector>

#include "Graph/Graph.h"

class IExamInterface;


class Brain
{
public:
	Brain(std::vector<WorldState*>* pWorldStates);
	bool CalculateAction(float elapsedSec, SteeringPlugin_Output& steeringOutput, IExamInterface* iFace, const vector<EntityInfo>& entities);
	void MakeGraph(WorldState* stateToAchieve);
private:
	std::vector<Action*> m_Actions;
	std::vector<WorldState*>* m_pWorldStates;
	std::vector<WorldState*> m_Goals;


	Graph* m_pGraph{};

};


#pragma once
#include <IExamInterface.h>

#include "Action.h"
#include "Goal.h"
#include "Exam_HelperStructs.h"
#include "../EliteFramework/EliteAI/EliteGraphs/EGraphNodeTypes.h"
#include "../EliteFramework/EliteAI/EliteGraphs/EGraphConnectionTypes.h"
#include "../EliteFramework/EliteAI/EliteGraphs/EGraph2D.h"

class Brain
{
public:
	Brain();
	SteeringPlugin_Output CalculateAction(IExamInterface* iFace);
	void MakeGraph();
private:
	std::vector<Action*> m_Actions;
	std::vector<WorldState*> m_WorldStates;
	std::vector<WorldState*> m_Goals;


	Elite::Graph2D<Elite::GraphNode2D, Elite::GraphConnection>* m_pGraph;

};


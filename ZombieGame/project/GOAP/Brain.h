#pragma once
#include <IExamInterface.h>

#include "Action.h"
#include "Goal.h"
#include "Exam_HelperStructs.h"

class Brain
{
public:
	SteeringPlugin_Output CalculateAction(IExamInterface* iFace);
private:
	std::vector<Action*> m_Actions;
	std::vector<WorldState*> m_WorldStates;
	std::vector<WorldState*> m_Goals;
};


#pragma once
#include <Exam_HelperStructs.h>

class IExamInterface;

class WorldState
{
public:
	virtual ~WorldState() = default;
	WorldState() = delete;
	WorldState(bool predicate);
	virtual void Update(float elapsedSec, IExamInterface* iFace, const vector<EntityInfo>& entities) = 0;
	bool Predicate;
	std::string m_Name;
};






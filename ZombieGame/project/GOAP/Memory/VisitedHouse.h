#pragma once
#include "Exam_HelperStructs.h"

class VisitedHouse
{
public:
	VisitedHouse(const HouseInfo& hi);
	bool HasBeenForgotten(float elapsedSec);
	HouseInfo GetHouseInfo() const { return m_HouseInfo; }
private:
	HouseInfo m_HouseInfo;
	float m_SecondsSinceVisit = 0;
	float m_SecondsTillRefresh = 20.f;
};


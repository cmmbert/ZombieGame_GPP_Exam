#pragma once
struct HouseInfo;

class VisitedHouse
{
public:
	VisitedHouse(HouseInfo* hi);
	bool HasBeenForgotten(float elapsedSec);
private:
	HouseInfo* m_pHouseInfo;
	float m_SecondsSinceVisit = 0;
	float m_SecondsTillRefresh = 20.f;
};


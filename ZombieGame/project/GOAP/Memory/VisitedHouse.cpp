#include "stdafx.h"
#include "VisitedHouse.h"

VisitedHouse::VisitedHouse(HouseInfo* hi)
{
	m_pHouseInfo = hi;
}

bool VisitedHouse::HasBeenForgotten(float elapsedSec)
{
	m_SecondsSinceVisit += elapsedSec;
	if (m_SecondsSinceVisit > m_SecondsTillRefresh)
		return true;
	else
		return false;
}

#include "stdafx.h"
#include "MoveTo.h"

MoveTo::MoveTo()
{
	m_EffectOnWorld.push_back(new NextToPickup());
	m_Name = typeid(this).name();
	m_Weight = 2.5f;
}

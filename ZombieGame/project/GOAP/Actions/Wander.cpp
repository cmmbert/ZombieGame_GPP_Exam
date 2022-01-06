#include "stdafx.h"
#include "Wander.h"

Wander::Wander()
{
	m_Name = typeid(this).name();
	m_EffectOnWorld.push_back(new Wanderlust(true));
	m_Weight = 100;
}

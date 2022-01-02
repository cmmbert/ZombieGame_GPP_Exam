#include "stdafx.h"
#include "Wander.h"

Wander::Wander()
{
	m_Name = typeid(this).name();
	m_Weight = 100;
}

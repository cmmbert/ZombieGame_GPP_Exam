#include "stdafx.h"
#include "MoveTo.h"

MoveTo::MoveTo()
{
	m_EffectOnWorld.push_back(new NextToPickup());
}

#include "stdafx.h"
#include "MoveToPickup.h"

#include "GOAP/WorldStates/ItemInViewState.h"
#include "GOAP/WorldStates/NextToPickupState.h"

MoveToPickup::MoveToPickup()
{
	m_Preconditions.push_back(new ItemInViewState(true));
	m_EffectOnWorld.push_back(new NextToPickup(true));
	m_Name = typeid(this).name();
	m_Weight = 2.5f;
}

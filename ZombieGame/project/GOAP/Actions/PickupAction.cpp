#include "stdafx.h"
#include "PickupAction.h"

PickupAction::PickupAction()
{
	m_Preconditions.push_back(new ItemInViewState());
	m_EffectOnWorld.push_back(new ItemInInventoryState());
	m_Name = typeid(this).name();
}

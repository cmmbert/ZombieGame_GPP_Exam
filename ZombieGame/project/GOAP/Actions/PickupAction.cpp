#include "stdafx.h"
#include "PickupAction.h"

#include "GOAP/WorldStates/ItemInInventoryState.h"
#include "GOAP/WorldStates/NextToPickupState.h"

PickupAction::PickupAction()
{
	m_Preconditions.push_back(new NextToPickup(true));
	m_EffectOnWorld.push_back(new ItemInInventoryState(true));
	m_Name = typeid(this).name();
}

SteeringPlugin_Output PickupAction::Execute(IExamInterface* iFace, const vector<EntityInfo>& entities)
{
	SteeringPlugin_Output output{};
	return output;
}

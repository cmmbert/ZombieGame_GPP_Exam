#pragma once
#include "../Action.h"
#include "../WorldState.h"
class PickupAction final : public Action
{
public:
	PickupAction();

	void DoAction() override;
};


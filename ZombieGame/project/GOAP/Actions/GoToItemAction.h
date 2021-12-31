#pragma once
#include "../Action.h"
#include "../WorldState.h"
class GoToItemAction final : Action
{
public:
	GoToItemAction();

	void DoAction() override;
};


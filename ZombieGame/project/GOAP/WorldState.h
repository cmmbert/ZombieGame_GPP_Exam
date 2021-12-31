#pragma once
class WorldState
{
public:
	bool Predicate;
};

class ItemInViewState : public WorldState{};
class ItemInInventoryState : public WorldState{};
class NextToPickup : public WorldState{};


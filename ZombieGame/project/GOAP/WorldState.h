#pragma once
class WorldState
{
public:
	WorldState() = delete;
	WorldState(bool predicate);
	bool Predicate;
};

class ItemInViewState : public WorldState{
public:
	explicit ItemInViewState(bool predicate)
		: WorldState(predicate)
	{
	}
};
class ItemInInventoryState : public WorldState{
public:
	explicit ItemInInventoryState(bool predicate)
		: WorldState(predicate)
	{
	}
};
class NextToPickup : public WorldState{
public:
	explicit NextToPickup(bool predicate)
		: WorldState(predicate)
	{
	}
};


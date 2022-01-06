#pragma once

class IExamInterface;

class WorldState
{
public:
	WorldState() = delete;
	WorldState(bool predicate);
	//virtual void Update(float elapsedSec, IExamInterface* iFace);
	bool Predicate;
	std::string m_Name;
};

class ItemInViewState : public WorldState{
public:
	explicit ItemInViewState(bool predicate)
		: WorldState(predicate)
	{
		m_Name = "ItemInView";
	}
};
class ItemInInventoryState : public WorldState{
public:
	explicit ItemInInventoryState(bool predicate)
		: WorldState(predicate)
	{
		m_Name = "ItemInInventory";
	}
};
class NextToPickup : public WorldState{
public:
	explicit NextToPickup(bool predicate)
		: WorldState(predicate)
	{
		m_Name = "NextToPickup";
	}
};

class Wanderlust : public WorldState {
public:
	explicit Wanderlust(bool predicate)
		: WorldState(predicate)
	{
		m_Name = "Wanderlust";
	}
};


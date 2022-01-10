#include "stdafx.h"
#include "Memory.h"

#include <IExamInterface.h>

Memory* Memory::m_Instance = nullptr;

Memory* Memory::GetInstance()
{
	if (m_Instance == nullptr)
		m_Instance = new Memory();
	return m_Instance;
}

void Memory::Destroy()
{
	delete m_Instance;
	m_Instance = nullptr;
}

bool Memory::AddHouseToMemory(HouseInfo hi)
{
	if(IsHouseInMemory(hi)) return false;
	GetInstance()->m_HousesSeen.push_back(VisitedHouse(hi));
	return true;
}

bool Memory::IsHouseInMemory(HouseInfo hi)
{
	for (auto visitedHouse : GetInstance()->m_HousesSeen)
	{
		if (visitedHouse.GetHouseInfo().Center == hi.Center)	return true;
	}
	return false;
}

bool Memory::AddItemToMemory(ItemInfo item)
{
	if (IsItemInMemory(item)) return false;
	GetInstance()->m_ItemsSeen.push_back(item);
	return true;
}

bool Memory::RemoveItemFromMemory(ItemInfo item)
{
	for (int i = 0; i < GetInstance()->m_ItemsSeen.size(); ++i)
	{
		if (GetInstance()->m_ItemsSeen[i].Location == item.Location)
		{
			GetInstance()->m_ItemsSeen.erase(GetInstance()->m_ItemsSeen.begin() + i);
			return true;
		}
	}
	return false;
}

bool Memory::IsItemInMemory(ItemInfo item)
{
	for (const auto& seenItem : GetInstance()->m_ItemsSeen)
	{
		if (seenItem.Location == item.Location)	return true;
	}
	return false;
}

void Memory::Update(float elapsedSec, IExamInterface* iFace)
{
	for (int i = 0; i < GetInstance()->m_HousesSeen.size(); ++i)
	{
		if(GetInstance()->m_HousesSeen[i].HasBeenForgotten(elapsedSec))
		{
			GetInstance()->m_HousesSeen.erase(GetInstance()->m_HousesSeen.begin() + i);
			break; //Break because we changed the size of the vector. Any other houses that had to be deleted will be deleted in the next frame
		}
	}
	auto agent = iFace->Agent_GetInfo();
	if (GetInstance()->m_WasInHouseLastFrame == false && agent.IsInHouse == true)
	{
		HouseInfo hi = {};
		if(iFace->Fov_GetHouseByIndex(0, hi))
		{
			AddHouseToMemory(hi);
		}
	}
	GetInstance()->m_WasInHouseLastFrame = agent.IsInHouse;
}

Memory::Memory()
{

}

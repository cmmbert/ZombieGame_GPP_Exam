#include "stdafx.h"
#include "Memory.h"

#include <IExamInterface.h>

#include "SeenPurge.h"

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
	if (hi.Size == Elite::Vector2{ 0,0 }) return true; //Invalid house

	for (auto visitedHouse : GetInstance()->m_HousesSeen)
	{
		if (visitedHouse.GetHouseInfo().Center == hi.Center)	return true;
	}
	return false;
}

bool Memory::AddPurgeToMemory(PurgeZoneInfo zi)
{
	if (IsPurgeInMemory(zi)) return false;
	GetInstance()->m_PurgesSeen.push_back(SeenPurge(zi));
	return true;
}

bool Memory::IsPurgeInMemory(PurgeZoneInfo zi)
{
	if (zi.ZoneHash == 0) return true; //Invalid purge

	for (auto seenPurge : GetInstance()->m_PurgesSeen)
	{
		if (seenPurge.GetPurgeInfo().ZoneHash == zi.ZoneHash)	return true;
	}
	return false;
}

vector<PurgeZoneInfo> Memory::GetAllSeenPurges()
{
	vector<PurgeZoneInfo> purges;
	for (auto purgeSeen : GetInstance()->m_PurgesSeen)
	{
		purges.push_back(purgeSeen.GetPurgeInfo());
	}
	return purges;
}

bool Memory::AddItemToMemory(ItemInfo item)
{
	if (IsItemInMemory(item)) return false;
	GetInstance()->m_ItemsSeen.push_back(item);
	return true;
}

bool Memory::RemoveItemFromMemory(ItemInfo item)
{
	for (size_t i = 0; i < GetInstance()->m_ItemsSeen.size(); ++i)
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
	for (size_t i = 0; i < GetInstance()->m_HousesSeen.size(); ++i)
	{
		if(GetInstance()->m_HousesSeen[i].HasBeenForgotten(elapsedSec))
		{
			GetInstance()->m_HousesSeen.erase(GetInstance()->m_HousesSeen.begin() + i);
			break; //Break because we changed the size of the vector. Any other houses that had to be deleted will be deleted in the next frame
		}
	}

	for (size_t i = 0; i < GetInstance()->m_PurgesSeen.size(); ++i)
	{
		if (GetInstance()->m_PurgesSeen[i].ZoneIsSafeAgain(elapsedSec))
		{
			GetInstance()->m_PurgesSeen.erase(GetInstance()->m_PurgesSeen.begin() + i);
			break; //Break because we changed the size of the vector. Any other purges that had to be deleted will be deleted in the next frame
		}
	}


	auto agent = iFace->Agent_GetInfo();
	if ((GetInstance()->m_LastClosestHouse.Center - agent.Position).Magnitude() < 2)
	{
		AddHouseToMemory(GetInstance()->m_LastClosestHouse);
	}
	GetInstance()->m_WasInHouseLastFrame = agent.IsInHouse;


	auto agentInfo = iFace->Agent_GetInfo();

	//Update closestValidHouse
	HouseInfo hi;
	HouseInfo closestValidHouse;
	closestValidHouse.Center = Elite::Vector2(FLT_MAX, FLT_MAX);
	for (int i = 0;; ++i)
	{
		if (iFace->Fov_GetHouseByIndex(i, hi))
		{
			if (Memory::GetInstance()->IsHouseInMemory(hi))
			{
				continue;
			}
			if ((hi.Center - agentInfo.Position).Magnitude() < (closestValidHouse.Center - agentInfo.Position).Magnitude())
			{
				closestValidHouse = hi;
			}
		}
		break;
	}
	if(closestValidHouse.Size != Elite::Vector2{0,0})
		GetInstance()->m_LastClosestHouse = closestValidHouse;


	for(const auto& house: GetInstance()->m_HousesSeen)
	{
		iFace->Draw_Circle(house.GetHouseInfo().Center, 10, Elite::Vector3(1, 0, 0));
	}


	//Recently bitten
	if(GetInstance()->m_RecentlyBitten)
	{
		GetInstance()->m_TimeSinceBitten += elapsedSec;
		if(GetInstance()->m_TimeSinceBitten > GetInstance()->m_BittenGracePeriod)
		{
			GetInstance()->m_RecentlyBitten = false;
			GetInstance()->m_TimeSinceBitten = 0;
		}
	}




	//Debug visualization
	iFace->Draw_Circle(GetInstance()->m_LastClosestHouse.Center, 5, Elite::Vector3(0, 0, 1));

	for (auto item : GetInstance()->m_ItemsSeen)
	{
		iFace->Draw_Circle(item.Location, 2, Elite::Vector3(1, 1, 0));
	}
}

Memory::Memory()
{

}

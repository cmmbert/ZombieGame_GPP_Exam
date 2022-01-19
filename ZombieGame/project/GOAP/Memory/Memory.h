#pragma once
#include "stdafx.h"

#include <Exam_HelperStructs.h>

#include "VisitedHouse.h"

class SeenPurge;
class IExamInterface;

class Memory
{
public:
	Memory(const Memory&) = delete;
	Memory(Memory&&) noexcept = delete;
	Memory& operator=(const Memory&) = delete;
	Memory& operator=(Memory&&) noexcept = delete;
	Memory(Memory& other) = delete;

	static Memory* GetInstance();
	static void Destroy();
	static void Update(float elapsedSec, IExamInterface* iFace);

	//Returns false if house is already in memory
	static bool AddHouseToMemory(HouseInfo hi);
	static bool IsHouseInMemory(HouseInfo hi);

	//Returns false if purge is already in memory
	static bool AddPurgeToMemory(PurgeZoneInfo zi);
	static bool IsPurgeInMemory(PurgeZoneInfo zi);
	static vector<PurgeZoneInfo> GetAllSeenPurges();

	static bool AddItemToMemory(ItemInfo item);
	static bool RemoveItemFromMemory(ItemInfo item);
	static bool IsItemInMemory(ItemInfo item);
	static vector<ItemInfo> GetAllItems() { return GetInstance()->m_ItemsSeen; }


	static HouseInfo GetLastClosestHouse() { return GetInstance()->m_LastClosestHouse; }
	bool m_RecentlyBitten = false;

private:
	Memory();
	static Memory* m_Instance;

	vector<VisitedHouse> m_HousesSeen;
	vector<SeenPurge> m_PurgesSeen;

	vector<ItemInfo> m_ItemsSeen;

	HouseInfo m_LastClosestHouse;

	bool m_WasInHouseLastFrame = false;

	float m_TimeSinceBitten = 0;
	float m_BittenGracePeriod = 2.f;
};


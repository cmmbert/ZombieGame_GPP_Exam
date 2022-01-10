#pragma once
#include "stdafx.h"

#include <Exam_HelperStructs.h>

#include "VisitedHouse.h"

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

	static bool AddItemToMemory(ItemInfo item);
	static bool RemoveItemFromMemory(ItemInfo item);
	static bool IsItemInMemory(ItemInfo item);

private:
	Memory();
	static Memory* m_Instance;

	vector<VisitedHouse> m_HousesSeen;

	vector<ItemInfo> m_ItemsSeen;

	bool m_WasInHouseLastFrame = false;

};


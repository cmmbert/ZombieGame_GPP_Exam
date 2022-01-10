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

	//Returns false if house is already in memory
	static bool AddHouseToMemory(HouseInfo hi);
	static bool IsHouseInMemory(HouseInfo hi);
	static void Update(float elapsedSec, IExamInterface* iFace);

private:
	Memory();
	static Memory* m_Instance;

	vector<VisitedHouse> m_HousesSeen;

};


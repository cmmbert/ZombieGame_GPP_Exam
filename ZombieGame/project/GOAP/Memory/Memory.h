#pragma once
#include "stdafx.h"

#include <Exam_HelperStructs.h>

#include "VisitedHouse.h"

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

	static void AddHouseToMemory(HouseInfo* hi);

private:
	Memory();
	static Memory* m_Instance;

	vector<VisitedHouse> m_HousesSeen;

};


#include "stdafx.h"
#include "Memory.h"

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

void Memory::AddHouseToMemory(HouseInfo* hi)
{
	GetInstance()->m_HousesSeen.push_back(VisitedHouse(hi));
}

Memory::Memory()
{

}

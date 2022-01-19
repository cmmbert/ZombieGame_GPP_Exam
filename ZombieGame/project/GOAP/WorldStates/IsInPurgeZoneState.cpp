#include "stdafx.h"
#include "IsInPurgeZoneState.h"

#include <IExamInterface.h>

#include "GOAP/Memory/Memory.h"

void IsInPurgeZoneState::Update(float elapsedSec, IExamInterface* iFace, const vector<EntityInfo>& entities)
{
	Predicate = false;
	for(const auto& entity : entities)
	{
		if(entity.Type == eEntityType::PURGEZONE)
		{
			PurgeZoneInfo purge;
			iFace->PurgeZone_GetInfo(entity, purge);
			Memory::GetInstance()->AddPurgeToMemory(purge);
		}
	}
	auto agentInfo = iFace->Agent_GetInfo();
	for (auto seenPurge : Memory::GetInstance()->GetAllSeenPurges())
	{
		if ((agentInfo.Position - seenPurge.Center).Magnitude() < seenPurge.Radius + 5)
		{
			Predicate = true;
		}
	}
}

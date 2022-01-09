#include "stdafx.h"
#include "RecentlyBittenState.h"

#include <IExamInterface.h>

void RecentlyBittenState::Update(float elapsedSec, IExamInterface* iFace, const vector<EntityInfo>& entities)
{
	if (iFace->Agent_GetInfo().WasBitten)
		m_GracePeriod = m_DefaultGracePeriod;

	if(m_GracePeriod > 0)
	{
		m_GracePeriod -= elapsedSec;
		Predicate = true;
	}
	else
	{
		Predicate = false;
	}
}

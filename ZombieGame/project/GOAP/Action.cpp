#include "stdafx.h"
#include "Action.h"

Action::~Action()
{
	for (auto precondition : m_Preconditions)
	{
		delete precondition;
		precondition = nullptr;
	}
	for (auto effect : m_EffectOnWorld)
	{
		delete effect;
		effect = nullptr;
	}
}

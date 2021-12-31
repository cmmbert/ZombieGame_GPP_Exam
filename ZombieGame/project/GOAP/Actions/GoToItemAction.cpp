#include "stdafx.h"
#include "GoToItemAction.h"

GoToItemAction::GoToItemAction()
{
	m_Preconditions.push_back(new ItemInViewState());
	m_EffectOnWorld.push_back(new ItemInInventoryState());
}

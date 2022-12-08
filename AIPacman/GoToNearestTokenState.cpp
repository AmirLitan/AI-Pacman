#include "GoToNearestTokenState.h"

GoToNearestTokenState::GoToNearestTokenState()
{
}

GoToNearestTokenState::~GoToNearestTokenState()
{
}

void GoToNearestTokenState::makeTransition(Entity* owner)
{
	owner->getCurrentState()->onStateExit(owner);
	owner->setCurrentState(new GoToNearestSwitchState());
	owner->getCurrentState()->onStateEnter(owner);
}

void GoToNearestTokenState::onStateEnter(Entity* owner)
{
	owner->setIsMovingToToken(true);
}

void GoToNearestTokenState::onStateExit(Entity* owner)
{
	owner->setIsMovingToToken(false);
}

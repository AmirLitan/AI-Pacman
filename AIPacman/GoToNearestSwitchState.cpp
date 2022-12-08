#include "GoToNearestSwitchState.h"


GoToNearestSwitchState::GoToNearestSwitchState()
{
}

GoToNearestSwitchState::~GoToNearestSwitchState()
{
}

void GoToNearestSwitchState::makeTransition(Entity* owner)
{
	owner->getCurrentState()->onStateExit(owner);
	owner->setCurrentState(new ChaseTargetState());
	owner->getCurrentState()->onStateEnter(owner);
}

void GoToNearestSwitchState::onStateEnter(Entity* owner)
{
	owner->setIsMovingToSwitch(true);
}

void GoToNearestSwitchState::onStateExit(Entity* owner)
{
	owner->setIsMovingToSwitch(false);
}

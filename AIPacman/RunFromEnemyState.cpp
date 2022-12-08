#include "RunFromEnemyState.h"

RunFromEnemyState::RunFromEnemyState()
{
}

RunFromEnemyState::~RunFromEnemyState()
{
}

void RunFromEnemyState::makeTransition(Entity* owner)
{
	owner->getCurrentState()->onStateExit(owner);
	owner->setCurrentState(new GoToNearestTokenState());
	owner->getCurrentState()->onStateEnter(owner);
}

void RunFromEnemyState::onStateEnter(Entity* owner)
{
	owner->setIsRunning(true);
}

void RunFromEnemyState::onStateExit(Entity* owner)
{
	owner->setIsRunning(false);
}

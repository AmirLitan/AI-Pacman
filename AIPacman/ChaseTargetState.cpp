#include "ChaseTargetState.h"

ChaseTargetState::ChaseTargetState()
{
}

ChaseTargetState::~ChaseTargetState()
{
}

void ChaseTargetState::makeTransition(Entity* owner)
{
	owner->getCurrentState()->onStateExit(owner);
	owner->setCurrentState(new RunFromEnemyState());
	owner->getCurrentState()->onStateEnter(owner);
}

void ChaseTargetState::onStateEnter(Entity* owner)
{
	owner->setIsChasing(true);
}

void ChaseTargetState::onStateExit(Entity* owner)
{
	owner->setIsChasing(false);
}

#pragma once
#include "State.h"
#include "RunFromEnemyState.h"

class ChaseTargetState : public State
{
public:
	ChaseTargetState();
	~ChaseTargetState();

	void makeTransition(Entity* owner);
	void onStateEnter(Entity* owner);
	void onStateExit(Entity* owner);
};


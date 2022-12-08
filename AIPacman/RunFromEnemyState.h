#pragma once
#include "State.h"
#include "GoToNearestTokenState.h"
class RunFromEnemyState : public State
{
public:
	RunFromEnemyState();
	~RunFromEnemyState();

	void makeTransition(Entity* owner);
	void onStateEnter(Entity* owner);
	void onStateExit(Entity* owner);
};


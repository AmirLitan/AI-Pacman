#pragma once
#include "State.h"
#include "GoToNearestSwitchState.h"

class GoToNearestTokenState : public State
{
public:
	GoToNearestTokenState();
	~GoToNearestTokenState();

	void makeTransition(Entity* owner);
	void onStateEnter(Entity* owner);
	void onStateExit(Entity* owner);
};


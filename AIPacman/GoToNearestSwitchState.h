#pragma once
#include "State.h"
#include "ChaseTargetState.h"

class State;
class Entity;
class GoToNearestSwitchState : public State
{
public:
	GoToNearestSwitchState();
	~GoToNearestSwitchState();

	void makeTransition(Entity* owner);
	void onStateEnter(Entity* owner);
	void onStateExit(Entity* owner);
};


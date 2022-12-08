#pragma once
#include "Entity.h"

class Entity;
class State
{
public:
	State();
	~State();

	virtual void makeTransition(Entity* owner) = 0;
	virtual void onStateEnter(Entity* owner) = 0;
	virtual void onStateExit(Entity* owner) = 0;
};


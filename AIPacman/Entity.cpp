#include "Entity.h"
#include "GoToNearestTokenState.h"
#include <iostream>

Entity::Entity()
	: row(0), col(0), type(0), currentState(nullptr), timer(0), isMovingToToken(true), isMovingToSwitch(false), isChasing(false), isRunning(false), isSwitch(false), currantFloor(PACMAN), currentStateType(GO_TO_TOKEN)
{
}

Entity::Entity(const int& row, const int& col, const int& type)
	: row(row), col(col), type(type), timer(0), isMovingToToken(true), isMovingToSwitch(false), isChasing(false),
	isRunning(false), isSwitch(false), currantFloor(ROOM), currentStateType(GO_TO_TOKEN), isTargetSet(false)
{
	currentState = new GoToNearestTokenState();
}


Entity::~Entity()
{
	delete currentState;
}

void Entity::execute(const double& dis, const double& distanceFromEnemy, const int& direction, const int& currantFloor, bool isSwitch)
{
	this->currantFloor = currantFloor;
	if (isMovingToToken)
	{
		std::cout << "pacman is in MovingToToken" << endl;
		if (type == PACMAN)
		{
			if (dis > distanceFromEnemy)
			{
				isTargetSet = false;
 				currentState->makeTransition(this);
				currentStateType = GO_TO_SWITCH;
			}
			else
			{
				setDirection(direction);
			}
		}
		else if(type == ENEMY)
		{
			std::cout << "ENEMY is in MovingToToken" << endl;
			currentState->makeTransition(this);
			currentStateType = GO_TO_SWITCH;
		}
	}
	if (isMovingToSwitch)
	{
		if (type == PACMAN)
		{
			std::cout << "PACMAN is in isMovingToSwitch" << endl;
			if (!isSwitch)
			{
				setDirection(direction);
			}
			else
			{
				currentState->makeTransition(this);
				currentStateType = CHASE;
			}
		}
		else if (type == ENEMY)
		{
			std::cout << "ENEMY is in isMovingToSwitch" << endl;
			 currentState->makeTransition(this);
			 currentStateType = CHASE;
		}
	}
	if (isChasing)
	{
		if (type == PACMAN)
		{
			std::cout << "PACMAN is in isChasing" << endl;
			if (isSwitch)
			{
				setDirection(direction);
			}
			else
			{
				currentState->makeTransition(this);
				currentStateType = RUN;
			}
		}
		else if (type == ENEMY)
		{
			std::cout << "ENEMY is in isChasing" << endl;
			if(isSwitch)
			{
				currentState->makeTransition(this);
				currentStateType = RUN;
			}
			else
			{
				setDirection(direction);
			}
		}
	}
	if (isRunning)
	{
		if (type == PACMAN)
		{
			std::cout << "PACMAN is in isRunning" << endl;
			currentState->makeTransition(this);
			currentStateType = GO_TO_TOKEN;
		}
		else if (type == ENEMY)
		{
			std::cout << "ENEMY is in isRunning" << endl;
			if (!isSwitch)
			{
				currentState->makeTransition(this);
				currentStateType = GO_TO_TOKEN;
			}
			else
			{
				setOppositeDirection(direction);
			}
		}
	}
}

void Entity::setDirection(const int& dir)
{
	if (dir == UP)
	{
		row -= 1;
	}
	else if (dir == DOWN)
	{
		row += 1;
	}
	else if (dir == LEFT)
	{
		col -= 1;
	}
	else if (dir == RIGHT)
	{
		col += 1;
	}
}

void Entity::setOppositeDirection(const int& dir)
{
	if (dir == UP)
	{
		row += 1;
	}
	else if (dir == DOWN)
	{
		row -= 1;
	}
	else if (dir == LEFT)
	{
		col += 1;
	}
	else if (dir == RIGHT)
	{
		col -= 1;
	}
}

bool operator==(const Entity& e1, const Entity& e2)
{
	if (e1.getRow() == e2.getRow() && e1.getCol() == e2.getCol())
	{
		return true;
	}
	else
	{
		return false;
	}
}

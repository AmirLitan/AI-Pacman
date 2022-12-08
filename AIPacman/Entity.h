#pragma once
#include "Data.h"
#include "State.h"

class State;
class Entity
{
private:
	State* currentState;
	int currentStateType;
	int row, col, timer;
	int type, currantFloor;
	int targetRow, targetCol;
	bool isMovingToToken, isMovingToSwitch, isChasing, isRunning, isSwitch, isTargetSet;
public:
	Entity();
	Entity(const int& row, const int& col, const int& type);
	Entity(const Entity& entity);
	~Entity();

	int getRow() const { return row; }
	int getCol() const { return col; }
	int getType() const { return type; }
	int getStateType() const { return currentStateType; }
	int getCurrentFloor() const { return currantFloor; }
	int getTargetRow() const { return targetRow; }
	int getTargetCol() const { return targetCol; }
	bool getIsTargetSet() const { return isTargetSet; }
	State* getCurrentState() const { return currentState; }

	void setCurrentState(State* newState) { currentState = newState; }
	void setIsMovingToToken(bool value) { isMovingToToken = value; }
	void setIsMovingToSwitch(bool value) { isMovingToSwitch = value; }
	void setIsChasing(bool value) { isChasing = value; }
	void setIsRunning(bool value) { isRunning = value; }
	void setCurrentStateType(const int& stateType) { currentStateType = stateType; }
	void setCurrentFloor(const int& cFloor) { currantFloor = cFloor; }
	void setTargetRow(const int& tRow)  { targetRow = tRow; }
	void setTargetCol(const int& tCol)  { targetCol = tCol; }
	void setIsTargetSet(const bool& b) { isTargetSet = b; }

	void execute(const double& dis, const double& distanceFromEnemy, const int& direction, const int& currantFloor, bool isSwitch);
	void setDirection(const int& dir);
	void setOppositeDirection(const int& dir);

	friend bool operator==(const Entity& e1, const Entity& e2);
};


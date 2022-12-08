#pragma once
#include "glut.h"
#include <vector>
#include <time.h>
#include <iostream>
#include <queue>
#include <iomanip>

#include "Data.h"
#include "View.h"
#include "Room.h"
#include "Corridor.h"
#include "Cell.h"
#include "CompareAStar.h"
#include "CompareUnifromCost.h"
#include "Entity.h"
#include "Token.h"

using namespace std;

class GameController
{
private:
	View view;
	vector<Room*> rooms;
	//vector<Corridor*> corridors;
	vector<Entity*> entitys;
	vector<Token*>  tokens;
	int grid[NUM_OF_PIXEL][NUM_OF_PIXEL] = { 0 };
	priority_queue <Cell*, vector<Cell*>, CompareAStar> aStar_pq;
	priority_queue <Cell*, vector<Cell*>, CompareUnifromCost> unifromCost_pq;
	Entity* currantEntity;

	int direction, currantType, targetType, startType;
	double distance, distanceFromEnemy;

	bool isSwitch = false;
	bool gameIsOver = false;
	int timer, numOfToken, maxNumOfToken;

public: 
	GameController(int argc, char* argv[]);
	~GameController();

	void init();

	//on start
	void createRooms();
	void connectRoomsByAStar();
	void createEntitysInRooms();

	//While game is runing
	void showMap();
	void moveEntitys();
	void checkWinLoseScenario();
	void checkDirection();


	//utilities
	double calculateDistanceBetweenTwoPoints(const int& x1, const int& y1, const int& x2, const int& y2);

	//AstarRooms
	void findPath(const Room& rCurrent, const Room& rTarget);
	void setStartTargetPoints(const Room& rCurrent, const Room& rTarget, Cell* tCell, const int& tag);
	void checkNeighbor(const int& row, const int& col, Cell* rCurrent, const Cell& rTarget);
	void updatePQAStar(Cell* pCurrent, const int& row, const int& col, const double& dis, const double& path);
	void restorPathFromPQ(Cell* pc);
	void clearGrid();

	//Astar move
	void findPathAStar(const int& row1, const int& col1, const int& row2, const int& col2);
	void checkNeighbor(const int& row, const int& col, Cell* rCurrent, const int& tRow, const int& tCol);
	void restorPath(Cell* pc);
	void restorGrid();

	//UnifromCost move
	void findPathUnifromCost(const int& row1, const int& col1);
	void checkNeighbor(const int& row, const int& col, Cell* rCurrent);
	void updatePQUnifromCost(Cell* pCurrent, const int& row, const int& col, const double& dis, const double& path);
};


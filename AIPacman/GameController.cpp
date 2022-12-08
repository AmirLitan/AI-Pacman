#include "GameController.h"

GameController::GameController(int argc, char* argv[]): view(argc, argv) 
{
	srand(time(0));
	timer = 0;
	numOfToken = 0;
	maxNumOfToken = 0;
	GameController::init();
}

GameController::~GameController()
{
	for (int i = 0; i < NUM_OF_PIXEL; ++i) {
		delete[] grid[i];
	}
	delete[] grid;
}

void GameController::init()
{
	view.setBackGroundColor();
	glOrtho(0, NUM_OF_PIXEL,0 , NUM_OF_PIXEL, -1, 1); // Setup coordinate system
	for (int i = 0; i < NUM_OF_PIXEL; i++)
	{
		for (int j = 0; j < NUM_OF_PIXEL; j++)
		{
			if (i == 0 || i == NUM_OF_PIXEL - 1 || j == 0 || j == NUM_OF_PIXEL - 1)
			{
				grid[i][j] = ROOM;
			}
			else
			{
				grid[i][j] = BLANK;
			}
		}
	}
	GameController::createRooms();
	connectRoomsByAStar();
	createEntitysInRooms();
}


void GameController::createRooms()
{
	bool isPositionValid = false;
	bool isThereMoreRoom = true;
	int numOfAttempts = 0;
	int i, j;
	int id;
	int x, y;
	int width, height;
	double distanceBetweenPoints, newDistanceFromCenter;
	//int roomPositionX, roomPositionY, newPositionX, newPositionY;

	while (rooms.size() < MAX_NUMBER_OF_ROOMS && numOfAttempts < MAX_NUM_OF_ATTEMPTS)
	{
		isPositionValid = true;

		width = rand()  % SIZE_OF_ROOM_MAX + SIZE_OF_ROOM_MIN;
		height = rand() % SIZE_OF_ROOM_MAX + SIZE_OF_ROOM_MIN;
		x = rand() % (NUM_OF_PIXEL - (width*2) - MIN_DISTANCE_FROM_EDGE*2) + (width + MIN_DISTANCE_FROM_EDGE); 
		y = rand() % (NUM_OF_PIXEL - (height*2) - MIN_DISTANCE_FROM_EDGE*2) + (height + MIN_DISTANCE_FROM_EDGE); 

		for (i = 0; i < rooms.size() && isPositionValid; i++)
		{
			distanceBetweenPoints = calculateDistanceBetweenTwoPoints(x , y , rooms[i]->getX(), rooms[i]->getY());
			newDistanceFromCenter = sqrt(pow(width, 2) + pow(height, 2));
			if (distanceBetweenPoints < (newDistanceFromCenter + rooms[i]->getDistanceCenterToCorner() + MIN_DISTANCE_FOR_ROOM))
			{
				isPositionValid = false; 
			}
		}
		if (isPositionValid)
		{
			id = rooms.size() + 1;
			rooms.push_back(new Room(x, y, width, height, id));
			for (i = abs(y - height); i < y + height; i++)
			{
				for (j = abs(x - width); j < x + width; j++)
				{
					if (i == abs(y - height) || i == y + height - 1 || j == abs(x - width) || j == x + width - 1)
					{
						grid[i][j] = WALL;
					}
					else
					{
						grid[i][j] = ROOM;
					}
				}
			}
			numOfAttempts = 0;
		}
		else
		{
			numOfAttempts++;
		}
	}
	if (numOfAttempts >= MAX_NUM_OF_ATTEMPTS)
	{
		cout << "No more room" << endl;
	}
}

void GameController::connectRoomsByAStar()
{
	vector<Room*> tampRoom;
	bool first = true;
	int numOfRooms, distance;
	int i,j = 0;
	Room* currentRoom;
	Cell* currentCell;
	 
	//find neighbors that are in proximity
	//when find neighbors add them to the array
	numOfRooms = rooms.size();

	for (i = 0; i < numOfRooms; i++)
	{
		currentRoom = *rooms.begin();
		tampRoom.push_back(currentRoom);
		rooms.erase(rooms.begin());

		for (auto& room : rooms)
		{
			distance = calculateDistanceBetweenTwoPoints(currentRoom->getX(), currentRoom->getY(), room->getX(), room->getY());
			if (distance < MAX_DISTANCE_FROM_TARGET)
			{
				//find path (using Astar) to the traget and create a corridor
				findPath(*currentRoom, *room);
				j++;
			}
		}
		
	}

	for (i = 0; i < numOfRooms; i++)
	{
		rooms.push_back(tampRoom.back());
		tampRoom.pop_back();
	}

	while (!aStar_pq.empty())
	{
		aStar_pq.pop();
	}
		//take first room from rooms and pop it 
		//iterate throw rooms and make an array of neighbors py proximity
		//make path/corridors using Astar on neighbors 
		//posh-back current room
		

	//find path to all neighbors and create corridor
	//add corridor to room A and B
}

void GameController::createEntitysInRooms()
{

	int i, j, row, col, enetityNum = 0 , startPosition , numOfAttempts = 0;
	int numOfRoom = rooms.size();
	int roomSelection[MAX_NUMBER_OF_ROOMS] = { 0 };
	bool enetitysInPlace = false;
	bool pointFind = false;
	bool isSwitchTokenSet = false;
	bool firstSelection = true;
	Room* tmpRoom;

	// set enetitys in random rooms
	while (enetityNum < 4)
	{
		startPosition = rand() % numOfRoom;

		if (roomSelection[startPosition] == 0)
		{
			if (firstSelection)
			{
				roomSelection[startPosition] = PACMAN;
				enetityNum++;
				firstSelection = false;
			}
			else
			{
				roomSelection[startPosition] = ENEMY;
				enetityNum++;
			}
		}
	}

	for (i = 0; i < numOfRoom; i++)
	{
		isSwitchTokenSet = false;
		bool pointFind = false;
		tmpRoom = rooms[i];
		numOfAttempts = 0;

		while (!pointFind && numOfAttempts < MAX_NUM_OF_ATTEMPTS)
		{
			row = rand() % (tmpRoom->getY() + tmpRoom->getHeight() - (tmpRoom->getY() - tmpRoom->getHeight())) + (tmpRoom->getY() - tmpRoom->getHeight());
			col = rand() % (tmpRoom->getX() + tmpRoom->getWidth() - (tmpRoom->getX() - tmpRoom->getWidth())) + (tmpRoom->getX() - tmpRoom->getWidth());
			if (grid[row][col] == ROOM)
			{
				pointFind = true;
			}
			numOfAttempts++;
		}
		pointFind = false;
		numOfAttempts = 0;

		if (roomSelection[i] == PACMAN)
		{
			entitys.push_back(new Entity(row, col, PACMAN));
			grid[row][col] = PACMAN;
		}
		else if(roomSelection[i] == ENEMY)
		{
			entitys.push_back(new Entity(row, col, ENEMY));
			grid[row][col] = ENEMY;
		}

		for (j = 0; j < NUM_OF_TOKENS + 1; j++)
		{
			while (!pointFind && numOfAttempts < MAX_NUM_OF_ATTEMPTS)
			{
				row = rand() % (tmpRoom->getY() + tmpRoom->getHeight() - (tmpRoom->getY() - tmpRoom->getHeight())) + (tmpRoom->getY() - tmpRoom->getHeight());
				col = rand() % (tmpRoom->getX() + tmpRoom->getWidth() - (tmpRoom->getX() - tmpRoom->getWidth())) + (tmpRoom->getX() - tmpRoom->getWidth());
				if (grid[row][col] == ROOM)
				{
					pointFind = true;
				}
				numOfAttempts++;
			}
			pointFind = false;
			numOfAttempts = 0;

			if (!isSwitchTokenSet)
			{
				tokens.push_back(new Token(row, col, SWITCH_TOKEN));
				grid[row][col] = SWITCH_TOKEN;
				isSwitchTokenSet = true;
			}
			else
			{
				tokens.push_back(new Token(row, col, TOKEN));
				grid[row][col] = TOKEN;
				maxNumOfToken++;
			}
		}
	}
}


void GameController::showMap()
{
	for (int i = 0; i < NUM_OF_PIXEL; i++)
	{
		for (int j = 0; j < NUM_OF_PIXEL; j++)
		{
			int tag = grid[i][j];
			view.drawRoom(i, j, tag);
		}
	}
		
}

void GameController::moveEntitys()
{
	vector<Entity*> tmpE;
	if (!gameIsOver)
	{
		int  tmpDirToEnemy = 0, i;
		int pRow, pCol;
		double tmpDisToEnemy = 100;

		distanceFromEnemy = 100;


		for (auto & e : entitys)
		{
			if (e->getType() != PACMAN) 
			{
				for (auto& e : entitys)
				{
					if (e->getType() == PACMAN)
					{
						pRow = e->getRow();
						pCol = e->getCol();
					}
				}
			}
			currantEntity = e;
			if (e->getType() == PACMAN)
			{
				currantType = PACMAN;
				if (e->getCurrentFloor() == TOKEN)
				{
					e->setCurrentFloor(ROOM);
					e->setIsTargetSet(false);
					numOfToken++;
				}
				else if (e->getCurrentFloor() == SWITCH_TOKEN && e->getStateType() != GO_TO_TOKEN)
				{
					isSwitch = true;
					timer = 0;
					e->setCurrentFloor(ROOM);
					e->setIsTargetSet(false);
				}
				if (isSwitch)
				{
					if (timer < MAX_TIMER)
					{
						cout << "timer = " << timer << endl;
						for (i = 0; i < entitys.size(); i++)
						{
							if (entitys[i]->getType() != PACMAN)
							{
								findPathAStar(e->getRow(), e->getCol(), entitys[i]->getRow(), entitys[i]->getCol());
								if (tmpDisToEnemy > distance)
								{
									tmpDisToEnemy = distance;
									tmpDirToEnemy = direction;
								}
							}
						}
						grid[e->getRow()][e->getCol()] = e->getCurrentFloor();
						e->execute(distance, distanceFromEnemy, direction, grid[e->getRow()][e->getCol()], isSwitch);
						e->setCurrentFloor(grid[e->getRow()][e->getCol()]);
						grid[e->getRow()][e->getCol()] = PACMAN;
						timer++;
					}
					else
					{
						isSwitch = false;
						e->setIsTargetSet(false);
						e->execute(distance, distanceFromEnemy, NO_DIRECTION, e->getCurrentFloor(), isSwitch);
					}
				}
				if(!isSwitch)
				{
					findPathUnifromCost(e->getRow(), e->getCol());
					if (e->getIsTargetSet())
					{
						findPathAStar(e->getRow(), e->getCol(), e->getTargetRow(), e->getTargetCol());
					}
					grid[e->getRow()][e->getCol()] = e->getCurrentFloor();
					e->execute(distance, distanceFromEnemy, direction, grid[e->getRow()][e->getCol()],isSwitch);
					e->setCurrentFloor(grid[e->getRow()][e->getCol()]);
					grid[e->getRow()][e->getCol()] = PACMAN;
				}
			}
			else
			{
				currantType = ENEMY;
				findPathAStar(e->getRow(), e->getCol(), pRow, pCol);
				if (isSwitch)
				{
					checkDirection();
				}
				grid[e->getRow()][e->getCol()] = e->getCurrentFloor();
				e->execute(distance, distanceFromEnemy, direction, grid[e->getRow()][e->getCol()],isSwitch);
				if (grid[e->getRow()][e->getCol()] != ENEMY)
				{
					e->setCurrentFloor(grid[e->getRow()][e->getCol()]);
				}
				grid[e->getRow()][e->getCol()] = ENEMY;
				
			}
		}
	}
}

void GameController::checkWinLoseScenario()
{
	int i, row, col;
	vector<Entity*> tmpE;
	if (numOfToken == maxNumOfToken)
	{
		cout << "YOU WIN!!!" << endl;
		gameIsOver = true;
	}
	if (!gameIsOver)
	{
		for (auto& cEntity : entitys)
		{
			row = cEntity->getRow();
			col = cEntity->getCol();
			if (cEntity->getType() == PACMAN && cEntity->getCurrentFloor() == ENEMY)
			{
				if (isSwitch)
				{
					for (i = 0; i < entitys.size(); i++)
					{
						if (entitys.back()->getType() == ENEMY && entitys.back() == cEntity)
						{
							grid[row][col] = PACMAN;
							cEntity->setCurrentFloor(ROOM);
							entitys.pop_back();
						}
						else
						{
							tmpE.push_back(entitys.back());
							entitys.pop_back();
						}
					}
				}
				else
				{
					gameIsOver = true;
					cout << "GAME OVER!!!" << endl;
				}
			}
			else if(cEntity->getType() == ENEMY && cEntity->getCurrentFloor() == PACMAN)
			{
				if (isSwitch)
				{
					for (i = 0; i < entitys.size(); i++)
					{
						if (entitys.back()->getType() == ENEMY && entitys.back() == cEntity)
						{
							grid[row][col] = PACMAN;
							cEntity->setCurrentFloor(ROOM);
							entitys.pop_back();
						}
						else
						{
							tmpE.push_back(entitys.back());
							entitys.pop_back();
						}
					}
					for (auto& e : tmpE)
					{
						entitys.push_back(e);
					}
				}
				else
				{
					gameIsOver = true;
					cout << "GAME OVER!!!" << endl;
				}
			}
		}
	}
	
}

void GameController::checkDirection()
{
	if (direction == UP)
	{
		if (grid[currantEntity->getRow() + 1][currantEntity->getCol()] == BLANK || grid[currantEntity->getRow() + 1][currantEntity->getCol()] == ENEMY)
		{
			if (grid[currantEntity->getRow()][currantEntity->getCol() + 1] == BLANK || grid[currantEntity->getRow() + 1][currantEntity->getCol()] == ENEMY)
			{
				if (grid[currantEntity->getRow()][currantEntity->getCol() - 1] == BLANK || grid[currantEntity->getRow() + 1][currantEntity->getCol()] == ENEMY)
				{
					direction = NO_DIRECTION;
				}
				else
				{
					direction = RIGHT;
				}
			}
			else
			{
				direction = LEFT;
			}
		}
	}
	else if (direction == DOWN)
	{
		if (grid[currantEntity->getRow() - 1][currantEntity->getCol()] == BLANK || grid[currantEntity->getRow() + 1][currantEntity->getCol()] == ENEMY)
		{
			if (grid[currantEntity->getRow()][currantEntity->getCol() + 1] == BLANK || grid[currantEntity->getRow() + 1][currantEntity->getCol()] == ENEMY)
			{
				if (grid[currantEntity->getRow()][currantEntity->getCol() - 1] == BLANK || grid[currantEntity->getRow() + 1][currantEntity->getCol()] == ENEMY)
				{
					direction = NO_DIRECTION;
				}
				else
				{
					direction = RIGHT;
				}
			}
			else
			{
				direction = LEFT;
			}
		}
	}
	else if (direction == LEFT)
	{
		if (grid[currantEntity->getRow()][currantEntity->getCol() + 1] == BLANK || grid[currantEntity->getRow() + 1][currantEntity->getCol()] == ENEMY)
		{
			if (grid[currantEntity->getRow() - 1][currantEntity->getCol()] == BLANK || grid[currantEntity->getRow() + 1][currantEntity->getCol()] == ENEMY)
			{
				if (grid[currantEntity->getRow() + 1][currantEntity->getCol()] == BLANK || grid[currantEntity->getRow() + 1][currantEntity->getCol()] == ENEMY)
				{
					direction = NO_DIRECTION;
				}
				else
				{
					direction = UP;
				}
			}
			else
			{
				direction = DOWN;
			}
		}
	}
	else if (direction == RIGHT)
	{
		if (grid[currantEntity->getRow()][currantEntity->getCol() - 1] == BLANK || grid[currantEntity->getRow() + 1][currantEntity->getCol()] == ENEMY)
		{
			if (grid[currantEntity->getRow() - 1][currantEntity->getCol()] == BLANK || grid[currantEntity->getRow() + 1][currantEntity->getCol()] == ENEMY)
			{
				if (grid[currantEntity->getRow() + 1][currantEntity->getCol()] == BLANK || grid[currantEntity->getRow() + 1][currantEntity->getCol()] == ENEMY)
				{
					direction = NO_DIRECTION;
				}
				else
				{
					direction = UP;
				}
			}
			else
			{
				direction = DOWN;
			}
		}
	}
}

double GameController::calculateDistanceBetweenTwoPoints(const int& x1, const int& y1, const int& x2, const int& y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void GameController::findPath(const Room& rCurrent, const Room& rTarget)
{
	//implamnt A*... 
	Cell* currentCell;
	Cell* targetCell = new Cell();
	double distanceToTarget;
	bool AStarIsRunning = true;

	setStartTargetPoints(rCurrent, rTarget, targetCell, START);
	setStartTargetPoints(rTarget, rCurrent, targetCell, TARGET);

	while (AStarIsRunning)
	{
		
		int row, col;
		if (aStar_pq.empty())
		{
			cout << "There is no solution" << endl;
			clearGrid();
			AStarIsRunning = false;
		}
		else
		{
			currentCell = aStar_pq.top();
			row = currentCell->getRow();
			col = currentCell->getCol();
			aStar_pq.pop();

			//distanceToTarget = calculateDistanceBetweenTwoPoints(row, col, rTarget.getX(), rTarget.getY());

			if(grid[row][col] == SEARCH_TARGET)
			{
				//save path and dorw all path at the end;
				AStarIsRunning = false;
				clearGrid();
				restorPathFromPQ(currentCell);
				return;
			}
			
			if(grid[row][col] == SEARCH_WALL)
			{
				grid[row][col] = CHECK_WALL;
			}

			if(grid[row][col] == SEARCH)
			{
				grid[row][col] = CHECK;
			}

			if (grid[row][col] == SEARCH_CORRIDOR)
			{
				grid[row][col] = CHECK_CORRIDOR;
			}

			//scan all the neighbors and pick non-check_wall and non-start and non-check
			//and Add non- visited neighbors
			//up
			if(grid[row + 1][col] != ROOM && grid[row + 1][col] != CHECK && grid[row + 1][col] != CHECK_WALL && grid[row + 1][col] != CHECK_CORRIDOR && grid[row + 1][col] != START)
				checkNeighbor(row + 1, col, currentCell, *targetCell);
			//down
			if (grid[row - 1][col] != ROOM && grid[row - 1][col] != CHECK && grid[row - 1][col] != CHECK_WALL && grid[row - 1][col] != CHECK_CORRIDOR && grid[row - 1][col] != START)
				checkNeighbor(row - 1, col, currentCell, *targetCell);
			//left
			if (grid[row][col - 1] != ROOM && grid[row][col - 1] != CHECK && grid[row][col - 1] != CHECK_WALL && grid[row][col - 1] != CHECK_CORRIDOR && grid[row][col - 1] != START)
				checkNeighbor(row, col - 1, currentCell, *targetCell);
			//right
			if (grid[row][col + 1] != ROOM && grid[row][col + 1] != CHECK && grid[row][col + 1] != CHECK_WALL && grid[row][col + 1] != CHECK_CORRIDOR && grid[row][col + 1] != START)
				checkNeighbor(row, col + 1, currentCell, *targetCell);
		}
	}
}

void GameController::setStartTargetPoints(const Room& rCurrent, const Room& rTarget, Cell* tCell, const int& tag)
{
	int disX, disY, dis;
	disX = (rCurrent.getX() - rTarget.getX());
	disY = (rCurrent.getY() - rTarget.getY());
	dis = abs(disX) + abs(disY);


	if (abs(disY) > abs(disX))
	{
		if (disY >= 0)
		{
			if(tag == START)
				aStar_pq.push(new Cell(rCurrent.getY() - rCurrent.getHeight(), rCurrent.getX(), dis));
			else if (tag == TARGET)
			{
				tCell->setRow(rCurrent.getY() - rCurrent.getHeight());
				tCell->setCol(rCurrent.getX());
			}
			grid[rCurrent.getY() - rCurrent.getHeight()][rCurrent.getX()] = tag;
		}
		else
		{
			if (tag == START)
				aStar_pq.push(new Cell((rCurrent.getY() + rCurrent.getHeight() - 1), rCurrent.getX(), dis));
			else if (tag == TARGET)
			{
				tCell->setRow(rCurrent.getY() + rCurrent.getHeight() - 1);
				tCell->setCol(rCurrent.getX());
			}
			grid[rCurrent.getY() + rCurrent.getHeight() - 1][rCurrent.getX()] = tag;
		}
	}
	else
	{
		if (disX >= 0)
		{
			if (tag == START)
				aStar_pq.push(new Cell(rCurrent.getY(), rCurrent.getX() - rCurrent.getWidth(), dis));
			else if (tag == TARGET)
			{
				tCell->setRow(rCurrent.getY());
				tCell->setCol(rCurrent.getX() - rCurrent.getWidth());
			}
			grid[rCurrent.getY()][rCurrent.getX() - rCurrent.getWidth()] = tag;
		}
		else
		{
			if (tag == START)
				aStar_pq.push(new Cell(rCurrent.getY(), rCurrent.getX() + rCurrent.getWidth() - 1, dis));
			else if (tag == TARGET)
			{
				tCell->setRow(rCurrent.getY());
				tCell->setCol(rCurrent.getX() + rCurrent.getWidth() - 1);
			}
			grid[rCurrent.getY()][rCurrent.getX() + rCurrent.getWidth() - 1] = tag;
		}
	}
}

void GameController::checkNeighbor(const int& row, const int& col, Cell* rCurrent, const Cell& rTarget)
{
	Cell* newCell;

	int disX, disY, dis;
	disX = (col - rTarget.getCol());
	disY = (row - rTarget.getRow());
	dis = abs(disX) + abs(disY);

	switch (grid[row][col])
	{
	case TARGET:
		newCell = new Cell(row, col, rCurrent, dis, rCurrent->getG() + WALL_ROUTE);
		aStar_pq.push(newCell);
		grid[row][col] = SEARCH_TARGET;
		break;
	case WALL:
		newCell = new Cell(row, col, rCurrent, dis, rCurrent->getG() + WALL_ROUTE);
		aStar_pq.push(newCell);
		grid[row][col] = SEARCH_WALL;
		break;
	case CORRIDOR:
		newCell = new Cell(row, col, rCurrent, dis, rCurrent->getG() + WALL_ROUTE);
		aStar_pq.push(newCell);
		grid[row][col] = SEARCH_CORRIDOR;
		break;
	case SEARCH:
		updatePQAStar(rCurrent, row, col, dis, rCurrent->getG() + ROUTE);
		break;
	case SEARCH_TARGET:
	case SEARCH_WALL:
	case SEARCH_CORRIDOR:
		updatePQAStar(rCurrent, row, col, dis, rCurrent->getG() + WALL_ROUTE);
		break;
	case BLANK:
		newCell = new Cell(row, col, rCurrent, dis, rCurrent->getG() + ROUTE);
		aStar_pq.push(newCell);
		grid[row][col] = SEARCH;
		break;
	default:
		break;
	}
}

void GameController::updatePQAStar(Cell* pCurrent, const int& row, const int& col, const double& dis, const double& path)
{
	Cell* pc;
	vector<Cell*> tempQ;
	while (!aStar_pq.empty() && !(aStar_pq.top()->getRow() == row && aStar_pq.top()->getCol() == col))
	{
		tempQ.push_back(aStar_pq.top());
		aStar_pq.pop();
	}
	//Now wither pq is empty or pq.top is what we are looking for
	if (aStar_pq.empty())
	{
		cout << "ERROR! a gray Node wasn't found in QP aStar" << endl;
		//exit(1);
		return;
	}
	// the neighbor was found
	pc = aStar_pq.top();
	pc->setH(dis);
	pc->setG(path);
	pc->computeF();
	pc->setParent(pCurrent); // update parent
	aStar_pq.push(pc);
	while (!tempQ.empty())
	{
		aStar_pq.push(tempQ.back());
		tempQ.pop_back();
	}

}

void GameController::restorPathFromPQ(Cell* pc)
{
	int pRow, pCol, cRow, cCol;
	bool exitWall = true, enterWall = true, endPath = false;

	Cell* chiledPc(pc);

	cRow = pc->getRow();
	cCol = pc->getCol();

	pc = pc->getParent();

	pRow = pc->getRow();
	pCol = pc->getCol();

	while (pc->getParent() != nullptr)
	{
		if (grid[pRow][pCol] == BLANK && grid[cRow][cCol] == WALL && exitWall)
		{
			exitWall = false;
			grid[cRow][cCol] = CORRIDOR;
			grid[pRow][pCol] = CORRIDOR;
		}
		else if (grid[pRow][pCol] == WALL && grid[cRow][cCol] == CORRIDOR && enterWall)
		{
			enterWall = false;
			grid[cRow][cCol] = CORRIDOR;
			grid[pRow][pCol] = CORRIDOR;
		}
		else if (grid[pRow][pCol] == WALL)
		{
			//grid[pRow][pCol] = WALL;
		}
		else if (grid[pRow][pCol] == BLANK)
		{
			grid[pRow][pCol] = CORRIDOR;
		}

		cRow = pc->getRow();
		cCol = pc->getCol();

		pc = pc->getParent();

		pRow = pc->getRow();
		pCol = pc->getCol();
	}	
}


void GameController::clearGrid()
{
	while (!aStar_pq.empty())
	{
		aStar_pq.pop();
	}
	int i, j;
	for ( i = 0; i < NUM_OF_PIXEL; i++)
	{
		for (j = 0; j < NUM_OF_PIXEL; j++)
		{
			if (grid[i][j] == SEARCH_WALL || grid[i][j] == CHECK_WALL || grid[i][j] == TARGET || grid[i][j] == START || grid[i][j] == CHECK_TARGET || grid[i][j] == SEARCH_TARGET)
			{
				grid[i][j] = WALL;
			}
			if (grid[i][j] == CHECK || grid[i][j] == SEARCH)
			{
				grid[i][j] = BLANK;
			}
			if (grid[i][j] == SEARCH_CORRIDOR || grid[i][j] == CHECK_CORRIDOR)
			{
				grid[i][j] = CORRIDOR;
			}
		}
	}
}

void GameController::findPathAStar(const int& row1, const int& col1, const int& row2, const int& col2)
{
	cout << "findPathAStar" << endl;
	//implamnt A*... 
	//int distanceToTarget = abs(row1 - row2) + abs(col1 - col2);
	double dis = sqrt(pow(row1 - row2, 2) + pow(col1 - col2, 2));
	Cell* currentCell;
	aStar_pq.push(new Cell(row1, col1, dis));
	bool AStarIsRunning = true;
	int row, col;

	startType = currantEntity->getType();
	grid[currantEntity->getRow()][currantEntity->getCol()] = START;

	targetType = grid[row2][col2];
	grid[row2][col2] = TARGET;
	
	while (AStarIsRunning)
	{
		if (aStar_pq.empty())
		{
			direction = NO_DIRECTION;
			restorGrid();
			AStarIsRunning = false;
		}
		else
		{
			currentCell = aStar_pq.top();
			row = currentCell->getRow();
			col = currentCell->getCol();
			aStar_pq.pop();

			if (grid[row][col] == SEARCH_TARGET)
			{
				//save path and dorw all path at the end;
				AStarIsRunning = false;
				restorPath(currentCell);
				restorGrid();
				return;
			}

			if (grid[row][col] == SEARCH_ROOM)
			{
				grid[row][col] = CHECK_ROOM;
			}

			if (grid[row][col] == SEARCH_ENEMY)
			{
				grid[row][col] = CHECK_ENEMY;
			}

			if (grid[row][col] == SEARCH_CORRIDOR)
			{
				grid[row][col] = CHECK_CORRIDOR;
			}

			if (grid[row][col] == SEARCH_TOKEN)
			{
				grid[row][col] = CHECK_TOKEN;
			}

			if (grid[row][col] == SEARCH_SWITCH_TOKEN)
			{
				grid[row][col] = CHECK_SWITCH_TOKEN;
			}

			if (grid[row][col] == SEARCH_WALL)
			{
				grid[row][col] = CHECK_WALL;
			}

			//up
			if (grid[row + 1][col] != BLANK && grid[row + 1][col] != CHECK_WALL && grid[row + 1][col] != CHECK_SWITCH_TOKEN && grid[row + 1][col] != CHECK_TOKEN && grid[row + 1][col] != CHECK_CORRIDOR && grid[row + 1][col] != CHECK_ROOM && grid[row + 1][col] != START)
				checkNeighbor(row + 1, col, currentCell, row2, col2);
			//down
			if (grid[row - 1][col] != BLANK && grid[row - 1][col] != CHECK_WALL && grid[row - 1][col] != CHECK_SWITCH_TOKEN && grid[row - 1][col] != CHECK_TOKEN && grid[row - 1][col] != CHECK_CORRIDOR && grid[row - 1][col] != CHECK_ROOM && grid[row - 1][col] != START)
				checkNeighbor(row - 1, col, currentCell, row2, col2);
			//left
			if (grid[row][col - 1] != BLANK && grid[row][col - 1] != CHECK_WALL && grid[row][col - 1] != CHECK_SWITCH_TOKEN && grid[row][col - 1] != CHECK_TOKEN && grid[row][col - 1] != CHECK_CORRIDOR && grid[row][col - 1] != CHECK_ROOM && grid[row][col - 1] != START)
				checkNeighbor(row, col - 1, currentCell, row2, col2);
			//right
			if (grid[row][col + 1] != BLANK && grid[row][col + 1] != CHECK_WALL && grid[row][col + 1] != CHECK_SWITCH_TOKEN && grid[row][col + 1] != CHECK_TOKEN && grid[row][col + 1] != CHECK_CORRIDOR && grid[row][col + 1] != CHECK_ROOM && grid[row][col + 1] != START)
				checkNeighbor(row, col + 1, currentCell, row2, col2);
		}
	}
}

void GameController::findPathUnifromCost(const int& row1, const int& col1)
{
	cout << "findPathUnifromCost" << endl;
	Cell* currentCell;
	int row, col, c;
	bool unifromCostIsRunning = true;
	unifromCost_pq.push(new Cell(row1, col1));
	c = 0;
	while(unifromCostIsRunning)
	{
		c++;
		cout << "\r" << c << flush;
		if (unifromCost_pq.empty())
		{
			cout << endl << "There is no solution UnifromCost" << endl;
			direction = NO_DIRECTION;
			restorGrid();
			unifromCostIsRunning = false;
		}
		else // pq is not empty
		{
			currentCell = unifromCost_pq.top(); //pq.top is the "best" (defined in CompareNodes: G) Node
			row = currentCell->getRow();
			col = currentCell->getCol();
			unifromCost_pq.pop();

			if (grid[row][col] == ENEMY || grid[row][col] == SEARCH_ENEMY || grid[row][col] == CHECK_ENEMY)
			{
				if (distanceFromEnemy > currentCell->getG())
				{
					distanceFromEnemy = currentCell->getG();
				}
				if (currantEntity->getStateType() == RUN)
				{
					unifromCostIsRunning = false;
					restorPath(currentCell);
					restorGrid();
					return;
				}
			}

			if (currantEntity->getStateType() == GO_TO_TOKEN)
			{
				if (grid[row][col] == SEARCH_TOKEN)
				{
					if (!currantEntity->getIsTargetSet())
					{
						currantEntity->setTargetRow(row);
						currantEntity->setTargetCol(col);
						currantEntity->setIsTargetSet(true);
						restorPath(currentCell);
					}
					else
					{
						restorPath(currentCell);
					}
					cout << endl << "findPathUnifromCost GO_TO_TOKEN" << endl;
					unifromCostIsRunning = false;
					restorGrid();
					return;
				}
			}
			if(currantEntity->getStateType() == GO_TO_SWITCH)
			{
				if (grid[row][col] == SEARCH_SWITCH_TOKEN)
				{
					if (!currantEntity->getIsTargetSet())
					{
						currantEntity->setTargetRow(row);
						currantEntity->setTargetCol(col);
						currantEntity->setIsTargetSet(true);
						restorPath(currentCell);
					}
					else
					{
						restorPath(currentCell);
					}
					cout << endl << "findPathUnifromCost GO_TO_SWITCH" << endl;
					unifromCostIsRunning = false;
					restorPath(currentCell);
					restorGrid();
					return;
				}
			} 

			
			if (grid[row][col] == SEARCH_ROOM)
			{
				grid[row][col] = CHECK_ROOM;
			}

			if (grid[row][col] == SEARCH_ENEMY)
			{
				grid[row][col] = CHECK_ENEMY;
			}

			if (grid[row][col] == SEARCH_WALL)
			{
				grid[row][col] = CHECK_WALL;
			}

			if (grid[row][col] == SEARCH_CORRIDOR)
			{
				grid[row][col] = CHECK_CORRIDOR;
			}

			if (grid[row][col] == SEARCH_TOKEN && currantEntity->getStateType() != GO_TO_TOKEN)
			{
				grid[row][col] = CHECK_TOKEN;
			}

			if (grid[row][col] == SEARCH_SWITCH_TOKEN && currantEntity->getStateType() != GO_TO_SWITCH)
			{
				grid[row][col] = CHECK_SWITCH_TOKEN;
			}

			//up
			if (grid[row + 1][col] != BLANK && grid[row + 1][col] != currantType && grid[row + 1][col] != CHECK_SWITCH_TOKEN && grid[row + 1][col] != CHECK_TOKEN && grid[row + 1][col] != CHECK_CORRIDOR && grid[row + 1][col] != CHECK_ROOM && grid[row + 1][col] != CHECK_WALL)
				checkNeighbor(row + 1, col, currentCell);
			//down
			if (grid[row - 1][col] != BLANK && grid[row - 1][col] != currantType && grid[row - 1][col] != CHECK_SWITCH_TOKEN && grid[row - 1][col] != CHECK_TOKEN && grid[row - 1][col] != CHECK_CORRIDOR && grid[row - 1][col] != CHECK_ROOM && grid[row - 1][col] != CHECK_WALL)
				checkNeighbor(row - 1, col, currentCell);
			//left
			if (grid[row][col - 1] != BLANK && grid[row][col - 1] != currantType && grid[row][col - 1] != CHECK_SWITCH_TOKEN && grid[row][col - 1] != CHECK_TOKEN && grid[row][col - 1] != CHECK_CORRIDOR && grid[row][col - 1] != CHECK_ROOM && grid[row][col - 1] != CHECK_WALL)
				checkNeighbor(row, col - 1, currentCell);
			//right
			if (grid[row][col + 1] != BLANK && grid[row][col + 1] != currantType && grid[row][col + 1] != CHECK_SWITCH_TOKEN && grid[row][col + 1] != CHECK_TOKEN && grid[row][col + 1] != CHECK_CORRIDOR && grid[row][col + 1] != CHECK_ROOM && grid[row][col + 1] != CHECK_WALL)
				checkNeighbor(row, col + 1, currentCell);

			


		}
	}
}

void GameController::checkNeighbor(const int& row, const int& col, Cell* rCurrent, const int& tRow, const int& tCol)
{
	Cell* newCell;
	int disX, disY, dis;
	/*disX = (col - tCol);
	disY = (row - tRow);
	dis = abs(disX) + abs(disY);*/
	dis = sqrt(pow(col - tCol, 2) + pow(row - tRow, 2));

	switch (grid[row][col])
	{
	case TARGET:
		newCell = new Cell(row, col, rCurrent, dis, rCurrent->getG() + CHASE_ROUTE);
		aStar_pq.push(newCell);
		grid[row][col] = SEARCH_TARGET;
		break;
	case CORRIDOR:
		newCell = new Cell(row, col, rCurrent, dis, rCurrent->getG() + CHASE_ROUTE);
		aStar_pq.push(newCell);
		grid[row][col] = SEARCH_CORRIDOR;
		break;
	case ROOM:
		newCell = new Cell(row, col, rCurrent, dis, rCurrent->getG() + CHASE_ROUTE);
		aStar_pq.push(newCell);
		grid[row][col] = SEARCH_ROOM;
		break;
	case SWITCH_TOKEN:
		newCell = new Cell(row, col, rCurrent, dis, rCurrent->getG() + CHASE_ROUTE);
		aStar_pq.push(newCell);
		grid[row][col] = SEARCH_SWITCH_TOKEN;
		break;
	case TOKEN:
		newCell = new Cell(row, col, rCurrent, dis, rCurrent->getG() + CHASE_ROUTE);
		aStar_pq.push(newCell);
		grid[row][col] = SEARCH_TOKEN;
		break;
	case WALL:
		newCell = new Cell(row, col, rCurrent, dis, rCurrent->getG() + CHASE_ROUTE);
		aStar_pq.push(newCell);
		grid[row][col] = SEARCH_WALL;
		break;
	case ENEMY:
		newCell = new Cell(row, col, rCurrent, dis, rCurrent->getG() + CHASE_ROUTE);
		aStar_pq.push(newCell);
		grid[row][col] = SEARCH_ENEMY;
		break;
	case SEARCH_TARGET:
	case SEARCH_CORRIDOR:
	case SEARCH_ROOM:
	case SEARCH_SWITCH_TOKEN:
	case SEARCH_TOKEN:
	case SEARCH_WALL:
	case SEARCH_ENEMY:
		updatePQAStar(rCurrent, row, col, dis, rCurrent->getG() + CHASE_ROUTE);
		break;
	default:
		break;
	}
}

void GameController::updatePQUnifromCost(Cell* pCurrent, const int& row, const int& col, const double& dis, const double& path)
{
	Cell* pc;
	vector<Cell*> tempQ;
	while (!unifromCost_pq.empty() && !(unifromCost_pq.top()->getRow() == row && unifromCost_pq.top()->getCol() == col))
	{
		tempQ.push_back(unifromCost_pq.top());
		unifromCost_pq.pop();
	}
	//Now wither pq is empty or pq.top is what we are looking for
	if (unifromCost_pq.empty())
	{
		cout << "ERROR! a gray Node wasn't found in QP UnifromCost" << endl;
		//exit(1);
		return;
	}
	// the neighbor was found
	pc = unifromCost_pq.top();
	pc->setH(dis);
	pc->setG(path);
	pc->computeF();
	pc->setParent(pCurrent); // update parent
	unifromCost_pq.push(pc);
	while (!tempQ.empty())
	{
		unifromCost_pq.push(tempQ.back());
		tempQ.pop_back();
	}
}


void GameController::restorPath(Cell* pc)
{	
	
	distance = pc->getG();

	int row1, col1, row2, col2;
	while (pc->getParent()->getParent() != nullptr)
	{
		pc = pc->getParent();
	}
	
	row1 = pc->getRow();
	col1 = pc->getCol();
	pc = pc->getParent();
	row2 = pc->getRow();
	col2 = pc->getCol();
	
	if ((row1 - row2) != 0)
	{
		if ((row1 - row2) < 0)
		{
			direction = UP;
		}
		else if((row1 - row2) > 0)
		{
			direction = DOWN;
		}
	}
	else if ((col1 - col2) != 0)
	{
		if ((col1 - col2) < 0)
		{
			direction = LEFT;
		}
		else
		{
			direction = RIGHT;
		}
	}
	else
	{
		direction = NO_DIRECTION;
	}
}

void GameController::restorGrid()
{
	while (!aStar_pq.empty())
	{
		aStar_pq.pop();
	}
	while (!unifromCost_pq.empty())
	{
		unifromCost_pq.pop();
	}
	int i, j;
	for (i = 0; i < NUM_OF_PIXEL; i++)
	{
		for (j = 0; j < NUM_OF_PIXEL; j++)
		{
			if (grid[i][j] == CHECK_WALL || grid[i][j] == SEARCH_WALL)
			{
				grid[i][j] = WALL;
			}
			if (grid[i][j] == CHECK_CORRIDOR || grid[i][j] == SEARCH_CORRIDOR)
			{
				grid[i][j] = CORRIDOR;
			}
			if (grid[i][j] == CHECK_ROOM || grid[i][j] == SEARCH_ROOM)
			{
				grid[i][j] = ROOM;
			}
			if (grid[i][j] == CHECK_TOKEN || grid[i][j] == SEARCH_TOKEN)
			{
				grid[i][j] = TOKEN;
			}
			if (grid[i][j] == CHECK_SWITCH_TOKEN || grid[i][j] == SEARCH_SWITCH_TOKEN)
			{
				grid[i][j] = SWITCH_TOKEN;
			}
			if (grid[i][j] == CHECK_TARGET || grid[i][j] == SEARCH_TARGET || grid[i][j] == TARGET)
			{
				grid[i][j] = targetType;
			}
			if (grid[i][j] == CHECK_ENEMY || grid[i][j] == SEARCH_ENEMY)
			{
				grid[i][j] = ENEMY;
			}
			if (grid[i][j] == START)
			{
				grid[i][j] = startType;
			}
		}
	}
}


void GameController::checkNeighbor(const int& row, const int& col, Cell* rCurrent)
{
	Cell* newCell;

	switch (grid[row][col])
	{
	case ENEMY:
		newCell = new Cell(row, col, rCurrent, 0, rCurrent->getG() + PACMAN_ROUTE);
		unifromCost_pq.push(newCell);
		grid[row][col] = SEARCH_ENEMY;
		break;
	case WALL:
		newCell = new Cell(row, col, rCurrent, 0, rCurrent->getG() + PACMAN_ROUTE);
		unifromCost_pq.push(newCell);
		grid[row][col] = SEARCH_WALL;
		break;
	case CORRIDOR:
		newCell = new Cell(row, col, rCurrent, 0, rCurrent->getG() + PACMAN_ROUTE);
		unifromCost_pq.push(newCell);
		grid[row][col] = SEARCH_CORRIDOR;
		break;
	case ROOM:
		newCell = new Cell(row, col, rCurrent, 0, rCurrent->getG() + PACMAN_ROUTE);
		unifromCost_pq.push(newCell);
		grid[row][col] = SEARCH_ROOM;
		break;
	case SWITCH_TOKEN:
		newCell = new Cell(row, col, rCurrent, 0, rCurrent->getG() + PACMAN_ROUTE);
		unifromCost_pq.push(newCell);
		grid[row][col] = SEARCH_SWITCH_TOKEN;
		break;
	case TOKEN:
		newCell = new Cell(row, col, rCurrent, 0, rCurrent->getG() + CHASE_ROUTE );
		unifromCost_pq.push(newCell);
		grid[row][col] = SEARCH_TOKEN;
		break;
	case SEARCH_ENEMY:
	case SEARCH_CORRIDOR:
	case SEARCH_ROOM:
	case SEARCH_TOKEN:
	case SEARCH_WALL:
	case SEARCH_SWITCH_TOKEN:
		updatePQUnifromCost(rCurrent, row, col, 0, rCurrent->getG() + PACMAN_ROUTE);
		break;
	default:
		break;
	}
}


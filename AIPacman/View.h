#pragma once
#include <vector>
#include "Room.h"
#include "glut.h"
#include "Data.h"


class View
{
private:

public:
	View();
	View(int argc, char* argv[]);
	~View();

	void setBackGroundColor();
	void drawRoom(const int& i, const int& j, const int& tag);
	//void drawRoom(Room& room);
	//void drawCorridor();
	//void drawPlayer();
	//void drawEnemy();
	//void drawCollectingPoints();
};


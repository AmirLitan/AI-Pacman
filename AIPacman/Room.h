#pragma once
#include <math.h>

class Room
{
private:
	int id;
	int x, y;
	double distanceCenterToCorner;
	int width, height;
public:
	Room(const int& x, const int& y, const int& width, const int& height, const int& id);
	Room(Room&& room);
	~Room();

	Room operator=(Room&& r); //move

	void setCenterCoordinates(const int x, const int y);

	int getID() { return id; }
	int getX() const { return x; }
	int getY() const { return y; }
	double getDistanceCenterToCorner() const { return distanceCenterToCorner; }
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	
};


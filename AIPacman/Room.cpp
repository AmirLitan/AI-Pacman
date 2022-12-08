#include "Room.h"

Room::Room(const int& x, const int& y, const int& width, const int& height, const int& id)
	:x(x), y(y), width(width), height(height), id(id)
{
	distanceCenterToCorner = sqrt(pow(width, 2) + pow(width, 2));
}

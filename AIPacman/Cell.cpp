#include "Cell.h"

Cell::Cell() : row(0), col(0), parent(nullptr) ,h(0) ,g(0), f(0)
{

}

Cell::Cell(const int& row, const int& col)
	: row(row), col(col), parent(nullptr), h(0), g(0), f(0)
{

}
Cell::Cell(const int& row, const int& col, Cell* p)
	: row(row), col(col), parent(p), h(0), g(0), f(0)
{

}

Cell::Cell(const int& row, const int& col, const double& distance)
	: row(row), col(col), parent(nullptr), h(distance), g(0), f(0)
{
	computeF();
}

Cell::Cell(const int& row, const int& col, Cell* p, const double& distance)
	: row(row), col(col), parent(p), h(distance), g(0), f(0)
{
	computeF();
}


Cell::Cell(const int& row, const int& col, Cell* p, const double& distance, const double& route)
	: row(row), col(col), parent(p), h(distance), g(route), f(0)
{
	computeF();
}

Cell::~Cell() 
{
	delete parent;
}

Cell::Cell(const Cell& other)
{
	*this = other;
}

Cell& Cell::operator=(const Cell& other)
{
	this->col = other.col;
	this->row = other.row;
	this->h = other.h;
	this->g = other.g;
	this->f = other.f;
	this->parent = other.parent;
	return *this;
}



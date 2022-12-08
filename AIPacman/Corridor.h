#pragma once
class Corridor
{
private:
	int id;
	int x1, y1, x2, y2;
public:
	Corridor(const int& x1, const int& y1, const int& x2, const int& y2 );
	~Corridor();

	int getX1() const { return x1; }
	int getY1() const { return y1; }
	int getX2() const { return x2; }
	int getY2() const { return y2; }
};


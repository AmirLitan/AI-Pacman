#pragma once
class PacMan
{
private:
	int row, col;
public:
	PacMan();
	PacMan(const int& row, const int& col);
	~PacMan();

	int getRow() const { return row; }
	int getCol() const { return col; }
};


#pragma once
class Enemy
{
private:
	int row, col;
public:
	Enemy();
	Enemy(const int& row, const int& col);
	~Enemy();

	int getRow() const { return row; }
	int getCol() const { return col; }
};


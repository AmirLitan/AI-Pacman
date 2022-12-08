#pragma once
class Token
{
private:
	int row, col;
	int type;
public:
	Token();
	Token(const int& row, const int& col, const int& type);
	~Token();

	int getRow() const { return row; }
	int getCol() const { return col; }
	int getType() const { return type; }

};


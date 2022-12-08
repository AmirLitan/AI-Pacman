#pragma once
class Cell
{
private:
	int row;
	int col;
	Cell* parent;
	double h;
	double g;
	double f;
public:
	Cell();
	Cell(const int& row, const int& col);
	Cell(const int& row, const int& col, Cell* p);
	Cell(const int& row, const int& col, const double& distance);
	Cell(const int& row, const int& col, Cell* p, const double& distance);
	Cell(const int& row, const int& col, Cell* p, const double& distance, const double& route);
	~Cell();

	Cell(const Cell& other);
	Cell& operator=(const Cell& other);

	int getRow() const { return row; }
	int getCol() const { return col; }
	Cell* getParent() const { return parent; }
	double getH() const { return h; }
	double getG() const { return g; }
	double getF() const { return f; }

	void setH(const double& value) { h = value; }
	void setG(const double& value) { g = value; }
	void setParent(Cell* c) { parent = c; }
	void setRow(const int& r) { row = r; }
	void setCol(const int& c) { col = c; }

	void computeF() { f = g + h; }

};


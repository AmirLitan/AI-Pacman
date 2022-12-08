#pragma once
#include "Cell.h"
class CompareUnifromCost
{
public:
	CompareUnifromCost();
	~CompareUnifromCost();

	bool operator()(Cell* pc1, Cell* pc2)
	{
		return pc1->getG() > pc2->getG();
	}
};


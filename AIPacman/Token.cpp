#include "Token.h"

Token::Token()
	: row(0), col(0), type(0)
{
}

Token::Token(const int& row, const int& col, const int& type)
	: row(row), col(col), type(type)
{
}

Token::~Token()
{
}

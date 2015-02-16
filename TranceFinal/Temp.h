#pragma once
#include "Expr.h"

class Type;

class Temp : public Expr
{
public:
	Temp(shared_ptr<Type> p);
	~Temp();

	string ToString();

	static int GetCount();
protected:
	static int s_count;

	int m_number;
};
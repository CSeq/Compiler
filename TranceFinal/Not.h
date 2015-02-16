#pragma once
#include "Logical.h"

class Not : public Logical
{
public:
	Not(shared_ptr<Token> tok, Expr* x);
	~Not();

	void Jumping(int t, int f);
	string ToString();
protected:
};
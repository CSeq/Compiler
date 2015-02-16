#pragma once
#include "Logical.h"

class And : public Logical
{
public:
	And(shared_ptr<Token> tok, Expr* x1, Expr* x2);
	~And();

	void Jumping(int t, int f);

protected:
};
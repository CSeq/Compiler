#pragma once
#include "Logical.h"

class Or : public Logical
{
public:
	Or(shared_ptr<Token> tok, Expr* x1, Expr* x2);
	~Or();

	void Jumping(int t, int f);

protected:
};
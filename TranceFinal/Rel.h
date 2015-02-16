#pragma once
#include "Logical.h"

class Rel : public Logical
{
public:
	Rel(shared_ptr<Token> tok, Expr* x1, Expr* x2);
	~Rel();
	
	shared_ptr<Type> Check(shared_ptr<Type> p1, shared_ptr<Type> p2);
	void Jumping(int t, int f);

protected:
};
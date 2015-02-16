#pragma once
#include "Expr.h"

class Token;
class Type;

class Op : public Expr
{
public:
	Op(shared_ptr<Token> op, shared_ptr<Type> type);
	~Op();

	Expr* Reduce();
protected:
};
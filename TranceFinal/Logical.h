#pragma once
#include "Expr.h"

class Logical : public Expr
{
public:
	Logical(shared_ptr<Token> tok, Expr* x1, Expr* x2);
	~Logical();

	virtual shared_ptr<Type> Check(shared_ptr<Type> p1, shared_ptr<Type> p2);
	Expr* Gen() override;
	string ToString();

	Expr* GetExpr1() const;
	Expr* GetExpr2() const;
protected:
	Expr* m_expr1, *m_expr2;
};
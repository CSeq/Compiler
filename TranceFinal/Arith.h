#pragma once
#include "Op.h"

class Arith : public Op
{
public:
	Arith(shared_ptr<Token> tok, Expr* x1, Expr* x2);
	~Arith();

	Expr* Gen() override;
	string ToString();
	Expr* GetExpr1() const;
	Expr* GetExpr2() const;

protected:
	Expr* m_expr1, *m_expr2;
};
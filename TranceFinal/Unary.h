#pragma once
#include "Op.h"

class Unary : public Op
{
public:
	Unary(shared_ptr<Token> tok, Expr* x);
	~Unary();
	Expr* Gen() override;
	string ToString();

	Expr* GetExpr() const;
protected:
	Expr* m_expr;
};
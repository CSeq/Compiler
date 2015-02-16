#pragma once
#include "Stmt.h"

class Expr;

class Do : public Stmt
{
public:
	Do();
	~Do();

	void Init(Stmt* x, Expr *s);
	void Gen(int b, int a);

	Expr* GetExpr() const;
	Stmt* GetStmt() const;

protected:
	Expr* m_expr;
	Stmt* m_stmt;
};
#pragma once
#include "Stmt.h"

class Expr;

class While : public Stmt
{
public:
	While();
	~While();

	void Init(Expr* x, Stmt* stmt);
	void Gen(int b, int a);

	Expr* GetExpr() const;
	Stmt* GetStmt() const;
protected:
	Expr* m_expr;
	Stmt* m_stmt;
};
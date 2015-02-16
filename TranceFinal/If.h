#pragma once
#include "Stmt.h"

class Expr;

class If : public Stmt
{
public:
	If(Expr* x, Stmt* stmt);
	~If();

	void Gen(int b, int a);

	Expr* GetExpr() const;
	Stmt* GetStmt() const;
protected:
	Expr* m_expr;
	Stmt* m_stmt;
};
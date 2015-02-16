#pragma once
#include "Stmt.h"

class Expr;

class Else : public Stmt
{
public:
	Else(Expr* x, Stmt* s1, Stmt* s2);
	~Else();

	void Gen(int b, int a);

	Expr* GetExpr() const;
	Stmt* GetStmt1() const;
	Stmt* GetStmt2() const;
protected:
	Expr* m_expr;
	Stmt* m_stmt1, *m_stmt2;
};
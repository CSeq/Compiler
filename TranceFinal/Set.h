#pragma once
#include "Stmt.h"

class Id;
class Expr;
class Type;

class Set : public Stmt
{
public:
	Set(Id* i, Expr* x);
	~Set();

	shared_ptr<Type> Check(shared_ptr<Type> p1, shared_ptr<Type> p2);
	void Gen(int b, int a);

	Id* GetId() const;
	Expr* GetExpr() const;
protected:
	Id* m_id;
	Expr* m_expr;
};
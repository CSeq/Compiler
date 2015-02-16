#pragma once
#include "Stmt.h"

class Id;
class Expr;
class Access;
class Type;

class SetElem : public Stmt
{
public:
	SetElem(Access* x, Expr* y);
	~SetElem();

	shared_ptr<Type> Check(shared_ptr<Type> p1, shared_ptr<Type> p2);
	void Gen(int b, int a);

	Id* GetArray() const;
	Expr* GetIndex() const;
	Expr* GetExpr() const;
protected:
	Id* m_array;
	Expr* m_index;
	Expr* m_expr;
};
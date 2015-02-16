#include "Rel.h"
#include "Defines.h"
#include "Array.h"
#include "Type.h"
#include "Id.h"

Rel::Rel(shared_ptr<Token> tok, Expr* x1, Expr* x2) : Logical(tok, x1, x2)
{
}

Rel::~Rel()
{
}

shared_ptr<Type> Rel::Check(shared_ptr<Type> p1, shared_ptr<Type> p2)
{
	if (InstanceOf<Array, Type>(p1.get()) || InstanceOf<Array, Type>(p2.get()))
	{
		return nullptr;
	}
	if (p1 == p2)
		return Type::s_bool;
	else
		return nullptr;
}

void Rel::Jumping(int t, int f)
{
	Expr* a = m_expr1->Reduce();
	Expr* b = m_expr2->Reduce();

	string test = a->ToString() + " " + m_op->ToString() + " " + b->ToString();
	delete a;
	a = nullptr;
	delete b;
	b = nullptr;
	EmitJumps(test, t, f);
}
#include "SetElem.h"
#include "Type.h"
#include "Defines.h"
#include "Access.h"
#include "Id.h"
#include "Array.h"

SetElem::SetElem(Access* x, Expr* y)
{
	m_array = x->GetArray();
	m_index = x->GetIndex();
	m_expr = y;
	if (!Check(x->GetType(), m_expr->GetType()))
	{
		ThrowError("type error");
	}
}

SetElem::~SetElem()
{
}

shared_ptr<Type> SetElem::Check(shared_ptr<Type> p1, shared_ptr<Type> p2)
{
	if (InstanceOf<Array, Type>(p1.get()) || InstanceOf<Array, Type>(p2.get()))
	{
		return nullptr;
	}
	else if (p1 == p2)
	{
		return p2;
	}
	else if (Type::Numeric(p1) && Type::Numeric(p2))
	{
		return p2;
	}
	return nullptr;
}

void SetElem::Gen(int b, int a)
{
	Expr* expr1 = m_index->Reduce();
	Expr* expr2 = m_expr->Reduce();
	string s1 = expr1->ToString();
	string s2 = expr2->ToString();
	Emit(m_array->ToString() + " [ " + s1 + " ] = " + s2);
	delete m_index;
	m_index = nullptr;
	delete m_expr;
	m_expr = nullptr;
	delete m_array;
	m_array = nullptr;
	delete expr1;
	delete expr2;
}

Id* SetElem::GetArray() const
{
	return m_array;
}

Expr* SetElem::GetIndex() const
{
	return m_index;
}

Expr* SetElem::GetExpr() const
{
	return m_expr;
}
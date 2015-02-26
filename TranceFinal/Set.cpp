#include "Set.h"
#include "Expr.h"
#include "Type.h"
#include "Id.h"
#include "Defines.h"


Set::Set(Id* id, Expr* x)
{
	m_id = id;
	m_expr = x;
	if (Check(m_id->GetType(), m_expr->GetType()) == NULL)
		ThrowError("type error");
}

Set::~Set()
{
}

Id* Set::GetId() const
{
	return m_id;
}

Expr* Set::GetExpr() const
{
	return m_expr;
}

shared_ptr<Type> Set::Check(shared_ptr<Type> p1, shared_ptr<Type> p2)
{
	if (Type::Numeric(p1) && Type::Numeric(p2)) 
	{
		return p2;
	}
	else if(p1 == Type::s_bool && p2 == Type::s_bool)
	{
		return p2;
	}
	else
		return nullptr;
}

void Set::Gen(int b, int a)
{
	Expr* temp = m_expr->Gen();
	Emit(m_id->ToString() + " = " + temp->ToString());
	delete temp;
	temp = nullptr;
	delete m_expr;
	m_expr = nullptr;
	delete m_id;
	m_id = nullptr;
}
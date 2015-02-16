#include "Unary.h"
#include "Type.h"
#include "Defines.h"
#include "Id.h"

Unary::Unary(shared_ptr<Token> tok, Expr* x) : Op(tok, nullptr)
{
	m_expr = x;
	m_type = Type::Max(Type::s_int, m_expr->GetType());
	if (!m_type)
		ThrowError("type error");
}

Unary::~Unary()
{
	delete m_expr;
	m_expr = nullptr;
}

Expr* Unary::GetExpr() const
{
	return m_expr;
}

Expr* Unary::Gen()
{
	Expr* expr1 = m_expr->Reduce();
	delete m_expr;
	m_expr = nullptr;
	return NEW Unary(m_op, expr1);
}

string Unary::ToString()
{
	return m_op->ToString() + " " + m_expr->ToString();
}


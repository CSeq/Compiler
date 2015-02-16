#include "Arith.h"
#include "Type.h"
#include "Defines.h"
#include "Compiler.h"
#include "Parser.h"
#include "Id.h"

Arith::Arith(shared_ptr<Token> tok, Expr* x1, Expr* x2) : Op(tok, nullptr)
{
	m_expr1 = x1;
	m_expr2 = x2;
	m_type = Type::Max(m_expr1->GetType(), m_expr2->GetType());
	if (!m_type)
		ThrowError("type error");
}

Arith::~Arith()
{
	delete m_expr1;
	m_expr1 = nullptr;
	delete m_expr2;
	m_expr2 = nullptr;
}

Expr* Arith::GetExpr1() const
{
	return m_expr1;
}

Expr* Arith::GetExpr2() const
{
	return m_expr2;
}

Expr* Arith::Gen()
{
	Expr* expr1 = m_expr1->Reduce();
	Expr* expr2 = m_expr2->Reduce();
	delete m_expr1;
	m_expr1 = nullptr;
	delete m_expr2;
	m_expr2 = nullptr;
	return NEW Arith(m_op, expr1, expr2);
}

string Arith::ToString()
{
	return m_expr1->ToString() + " " + m_op->ToString() + " " + m_expr2->ToString();
}
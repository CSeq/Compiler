#include "Do.h"
#include "Expr.h"
#include "Type.h"
#include "Defines.h"
#include "Id.h"

Do::Do()
{
	m_expr = nullptr;
	m_stmt = nullptr;
}

Do::~Do()
{
}


Expr* Do::GetExpr() const
{
	return m_expr;
}

Stmt* Do::GetStmt() const
{
	return m_stmt;
}

void Do::Init(Stmt* x, Expr* s)
{
	m_expr = s;
	m_stmt = x;
	if (m_expr->GetType() != Type::s_bool)
		m_expr->ThrowError("boolean required in do");
}

void Do::Gen(int b, int a)
{
	m_after = a;
	int label = NewLabel();
	m_stmt->Gen(b, label);
	EmitLabel(label);
	m_expr->Jumping(b, 0);
	delete m_stmt;
	m_stmt = nullptr;
	delete m_expr;
	m_expr = nullptr;
}
#include "If.h"
#include "Expr.h"
#include "Type.h"
#include "Defines.h"
#include "Id.h"

If::If(Expr* x, Stmt* stmt)
{
	m_expr = x;
	m_stmt = stmt;
	if (m_expr->GetType() != Type::s_bool)
		m_expr->ThrowError("boolean required in if");
}

If::~If()
{
}

Expr* If::GetExpr() const
{
	return m_expr;
}

Stmt* If::GetStmt() const
{
	return m_stmt;
}

void If::Gen(int b, int a)
{
	int label = NewLabel();
	m_expr->Jumping(0, a);
	EmitLabel(label);
	m_stmt->Gen(label, a);
	delete m_stmt;
	m_stmt = nullptr;
	delete m_expr;
	m_expr = nullptr;
}
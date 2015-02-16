#include "While.h"
#include "Expr.h"
#include "Type.h"
#include "Defines.h"
#include "Id.h"

While::While()
{
	m_expr = nullptr;
	m_stmt = nullptr;
}

While::~While()
{
	delete m_stmt;
	m_stmt = nullptr;
	delete m_expr;
	m_expr = nullptr;
}

Expr* While::GetExpr() const
{
	return m_expr;
}

Stmt* While::GetStmt() const
{
	return m_stmt;
}

void While::Gen(int b, int a)
{
	m_after = a;
	m_expr->Jumping(0, a);
	int label = NewLabel();
	EmitLabel(label);
	m_stmt->Gen(label, b);
	Emit("goto L" + NumToString(b));
	delete m_stmt;
	m_stmt = nullptr;
	delete m_expr;
	m_expr = nullptr;
}

void While::Init(Expr* x, Stmt* stmt)
{
	m_expr = x;
	m_stmt = stmt;
	if (m_expr->GetType() != Type::s_bool)
	{
		m_expr->ThrowError("boolean required in while");
	}
}
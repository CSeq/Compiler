#include "Else.h"
#include "Type.h"
#include "Expr.h"
#include "Defines.h"
#include "Id.h"

Else::Else(Expr* x, Stmt* s1, Stmt* s2)
{
	m_expr = x;
	m_stmt1 = s1;
	m_stmt2 = s2;
	if (m_expr->GetType() != Type::s_bool)
	{
		m_expr->ThrowError("boolean required in if");
	}
}

Else::~Else()
{
	delete m_stmt1;
	m_stmt1 = nullptr;
	delete m_stmt2;
	m_stmt2 = nullptr;
	delete m_expr;
	m_expr = nullptr;
}


void Else::Gen(int b, int a)
{
	int label1 = NewLabel();
	int label2 = NewLabel();

	m_expr->Jumping(0, label2);
	EmitLabel(label1);
	m_stmt1->Gen(label1, a);
	Emit("goto L" + NumToString(a));
	EmitLabel(label2);
	m_stmt2->Gen(label2, a);
	delete m_stmt1;
	m_stmt1 = nullptr;
	delete m_stmt2;
	m_stmt2 = nullptr;
	delete m_expr;
	m_expr = nullptr;
}

Expr* Else::GetExpr() const
{
	return m_expr;
}

Stmt* Else::GetStmt1() const
{
	return m_stmt1;
}

Stmt* Else::GetStmt2() const
{
	return m_stmt2;
}
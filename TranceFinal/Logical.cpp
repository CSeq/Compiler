#include "Logical.h"
#include "Type.h"
#include "Temp.h"
#include "Defines.h"
#include "Id.h"

Logical::Logical(shared_ptr<Token> tok, Expr* x1, Expr* x2) : Expr(tok, NULL)
{
	m_expr1 = x1;
	m_expr2 = x2;

	m_type = Check(m_expr1->GetType(), m_expr2->GetType());
	if (!m_type)
		ThrowError("type error");
}

Logical::~Logical()
{
	delete m_expr1;
	m_expr1 = nullptr;
	delete m_expr2;
	m_expr2 = nullptr;
}

Expr* Logical::GetExpr1() const
{
	return m_expr1;
}

Expr* Logical::GetExpr2() const
{
	return m_expr2;
}

shared_ptr<Type> Logical::Check(shared_ptr<Type> t1, shared_ptr<Type> t2)
{
	if (t1 == t2) 
	{
		if (t1 == Type::s_bool || t1 == Type::s_int || t1 == Type::s_float)
			return Type::s_bool;
	}
	return nullptr;
}

Expr* Logical::Gen()
{
	int f = NewLabel();
	int a = NewLabel();

	Temp* temp = NEW Temp(m_type);
	Jumping(0, f);
	Emit(temp->ToString() + " = true");
	Emit("goto L" + NumToString(a));
	EmitLabel(f);
	Emit(temp->ToString() + " = false");
	EmitLabel(a);
	delete m_expr1;
	m_expr1 = nullptr;
	delete m_expr2;
	m_expr2 = nullptr;
	return temp;
}

string Logical::ToString()
{
	return m_expr1->ToString() + " " + m_op->ToString() + " " + m_expr2->ToString();
}
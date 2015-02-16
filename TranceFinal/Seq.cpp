#include "Seq.h"

Seq::Seq(Stmt* s1, Stmt* s2)
{
	m_stmt1 = s1;
	m_stmt2 = s2;
}

Seq::~Seq()
{
}

void Seq::Gen(int b, int a)
{
	if (m_stmt1 == Stmt::s_null.get())
	{
		m_stmt2->Gen(b, a);
		delete m_stmt2;
		m_stmt2 = nullptr;
	}
	else if (m_stmt2 == Stmt::s_null.get())
	{
		m_stmt1->Gen(b, a);
		delete m_stmt1;
		m_stmt1 = nullptr;
	}
	else
	{
		int label = NewLabel();
		m_stmt1->Gen(b, label);
		EmitLabel(label);
		m_stmt2->Gen(label, a);
		delete m_stmt2;
		delete m_stmt1;
		m_stmt2 = nullptr;
		m_stmt1 = nullptr;
	}
}

Stmt* Seq::GetStmt1() const
{
	return m_stmt1;
}

Stmt* Seq::GetStmt2() const
{
	return m_stmt2;
}
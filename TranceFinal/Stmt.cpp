#include "Stmt.h"
#include "Defines.h"

Stmt::Stmt()
{
	m_after = 0;
}

Stmt::~Stmt()
{
}

int Stmt::GetAfter() const
{
	return m_after;
}


shared_ptr<Stmt>Stmt::s_null = nullptr;
Stmt* Stmt::s_enclosing = nullptr;

void Stmt::Gen(int b, int a)
{
}

void Stmt::InitStmts()
{
	if (!s_null)
	{
		s_null.reset(NEW Stmt);
		s_enclosing = s_null.get();
	}
}
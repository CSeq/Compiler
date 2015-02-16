#include "Break.h"
#include "Defines.h"

Break::Break()
{
	if (!Stmt::s_enclosing)
	{
		ThrowError("unenclosed break");
	}
	m_stmt = Stmt::s_enclosing;
}

Break::~Break()
{
}


Stmt* Break::GetStmt() const
{
	return m_stmt;
}

void Break::Gen(int b, int a)
{
	Emit("goto L" + NumToString(m_stmt->GetAfter()));
}
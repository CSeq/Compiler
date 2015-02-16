#include "Not.h"
#include "Token.h"

Not::Not(shared_ptr<Token> tok, Expr* x) : Logical(tok, x, x)
{
}

Not::~Not()
{
}

void Not::Jumping(int t, int f)
{
	m_expr2->Jumping(f, t);
}

string Not::ToString()
{
	return m_op->ToString() + " " + m_expr2->ToString();
}
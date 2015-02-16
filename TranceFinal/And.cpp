#include "And.h"

And::And(shared_ptr<Token> tok, Expr* x1, Expr* x2) : Logical(tok, x1, x2)
{
}

And::~And()
{
}

void And::Jumping(int t, int f)
{
	int label = f != 0 ? f : NewLabel();
	m_expr1->Jumping(0, label);
	m_expr2->Jumping(t, f);
	if (f == 0)
	{
		EmitLabel(label);
	}
}
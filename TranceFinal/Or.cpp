#include "Or.h"

Or::Or(shared_ptr<Token> tok, Expr* x1, Expr* x2) : Logical(tok, x1, x2)
{
}

Or::~Or()
{
}

void Or::Jumping(int t, int f)
{
	int label = t != 0 ? t : NewLabel();
	m_expr1->Jumping(label, 0);
	m_expr2->Jumping(t, f);
	if (t == 0)
	{
		EmitLabel(label);
	}
}
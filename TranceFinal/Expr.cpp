#include "Expr.h"
#include "Token.h"
#include "Type.h"
#include "Defines.h"


Expr::Expr(shared_ptr<Token> tok, shared_ptr<Type> type)
{
	m_op = tok;
	m_type = type;
}

Expr::~Expr()
{
}

Expr* Expr::Gen()
{
	return NEW Expr(m_op, m_type);
}

Expr* Expr::Reduce()
{
	return NEW Expr(m_op, m_type);
}

void Expr::Jumping(int t, int f)
{
	EmitJumps(ToString(), t, f);
}

void Expr::EmitJumps(string s, int t, int f)
{
	if (t != 0 && f != 0)
	{
		Emit("if " + s + " goto L" + NumToString(t));
		Emit("goto L" + NumToString(f));
	}
	else if (t != 0)
	{
		Emit("if " + s + " goto L" + NumToString(t));
	}
	else if (f != 0)
	{
		Emit("iffalse " + s + " goto L" + NumToString(f));
	}
}

string Expr::ToString()
{
	return m_op->ToString();
}

shared_ptr<Token> Expr::GetToken() const
{
	return m_op;
}

shared_ptr<Type> Expr::GetType() const
{
	return m_type;
}
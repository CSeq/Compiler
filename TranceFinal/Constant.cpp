#include "Constant.h"
#include "Num.h"
#include "Type.h"
#include "Word.h"
#include "Compiler.h"
#include "Lexer.h"

Constant::Constant(shared_ptr<Token> tok, shared_ptr<Type> p) : Expr(tok, p)
{
}

Constant::Constant(int i) : Expr(nullptr, Type::s_int)
{
	m_op.reset(NEW Num(i));
}

Constant::~Constant()
{
}

void Constant::InitStatics()
{
	s_true->m_type = Type::s_bool;
	s_false->m_type = Type::s_bool;
	s_true->m_op = Word::s_true;
	s_false->m_op = Word::s_false;
}

void Constant::Jumping(int t, int f)
{
	if (this == s_true.get() && t != 0)
	{
		Emit("goto L" + NumToString(t));
	}
	else if (this == s_false.get() && f != 0)
	{
		Emit("goto L" + NumToString(f));
	}
}

shared_ptr<Constant> Constant::s_true(NEW Constant(nullptr, nullptr));
shared_ptr<Constant> Constant::s_false(NEW Constant(nullptr, nullptr));
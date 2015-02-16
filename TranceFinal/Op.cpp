#include "Op.h"
#include "Token.h"
#include "Type.h"
#include "Temp.h"
#include "Defines.h"
#include "Compiler.h"
#include "Parser.h"
#include "Id.h"

Op::Op(shared_ptr<Token> op, shared_ptr<Type> type) : Expr(op, type)
{
}

Op::~Op()
{
}

Expr* Op::Reduce()
{
	Expr* x = Gen();
	Temp* t = NEW Temp(m_type);
	Emit(t->ToString() + " = " + x->ToString());
	delete x;
	x = nullptr;
	return t;
}
#include "Access.h"
#include "Word.h"
#include "Defines.h"
#include "Id.h"
#include "Compiler.h"
#include "Lexer.h"
#include "Parser.h"

Access::Access(Id* id, Expr* x, shared_ptr<Type> type) : Op(nullptr, type)
{
	m_array = id;
	m_index = x;
}

Access::~Access()
{
}


Expr* Access::GetIndex() const
{
	return m_index;
}

Id* Access::GetArray() const
{
	return m_array;
}

Expr* Access::Gen()
{
	Expr* expr1 = m_index->Reduce();
	delete m_index;
	m_index = nullptr;
	delete m_array;
	m_array = nullptr;
	Id* temp = NEW Id(static_pointer_cast<Word>(m_array->GetToken()), static_pointer_cast<Type>(m_array->GetType()), m_array->GetOffset());
	return NEW Access(temp, expr1, m_type);
}

void Access::Jumping(int t, int f)
{
	Expr* expr = Reduce();
	EmitJumps(expr->ToString(), t, f);
	delete expr;
	expr = nullptr;
}

string Access::ToString()
{
	return m_array->ToString() + " [ " + m_index->ToString() + " ] ";
}
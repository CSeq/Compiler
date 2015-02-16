#include "Env.h"
#include "Lexer.h"
#include "Expr.h"
#include "Id.h"
#include "Defines.h"
#include "Type.h"



Env::Env(Env* n)
{
	prev = n;
}

Env::Env()
{
	prev = nullptr;
}

Env::~Env()
{
	auto it = m_table.begin();
	while (it != m_table.end())
	{
		delete it->second;
		it = m_table.erase(it);
	}
}

void Env::Put(shared_ptr<Token> t, Id* i)
{
	m_table[t->GetID()] = i;
}

Id* Env::Get(shared_ptr<Token> t)
{
	for (Env* e = this; e ; e = e->prev)
	{
		auto it = e->m_table.find(t->GetID());
		if (it != e->m_table.end())
			return NEW Id(static_pointer_cast<Word>(it->second->GetToken()), static_pointer_cast<Type>(it->second->GetType()), it->second->GetOffset());
	}
	return nullptr;
}

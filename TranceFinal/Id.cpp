#include "Id.h"
#include "Word.h"

Id::Id(shared_ptr<Word> id, shared_ptr<Type> type, int b) : Expr(id, type)
{
	m_offset = b;
}

Id::~Id()
{
}

int Id::GetOffset() const
{
	return m_offset;
}
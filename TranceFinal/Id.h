#pragma once
#include "Expr.h"

class Word;
class Type;

class Id : public Expr
{
public:
	Id(shared_ptr<Word> id, shared_ptr<Type> p, int b);
	~Id();

	int GetOffset() const;
protected:
	int m_offset;
};
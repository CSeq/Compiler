#include "Array.h"
#include "Defines.h"


Array::Array(int sz, shared_ptr<Type> p) : Type("[]", INDEX, sz*p->GetWidth())
{
	m_size = sz;
	m_of = p;
}

Array::~Array()
{
}

int Array::GetSize() const
{
	return m_size;
}

shared_ptr<Type> Array::GetOf() const
{
	return m_of;
}

string Array::ToString()
{
	return "[" + NumToString(m_size) + "] " + m_of->ToString();
}
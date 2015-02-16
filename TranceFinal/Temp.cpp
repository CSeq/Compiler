#include "Temp.h"
#include "Type.h"
#include "Defines.h"

int Temp::s_count = 0;

Temp::Temp(shared_ptr<Type> p) : Expr(Word::s_temp, p)
{
	m_number = ++s_count;
}

Temp::~Temp()
{
}

int Temp::GetCount()
{
	return s_count;
}

string Temp::ToString()
{
	return "t" + NumToString(m_number);
}
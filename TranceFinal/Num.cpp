#include "Num.h"
#include "Defines.h"


int Num::GetValue() const
{
	return m_value;
}

string Num::DebugString()
{
	return "<NUM, " + NumToString(m_value) + ">";
}

string Num::ToString()
{
	return "" + NumToString(m_value);
}
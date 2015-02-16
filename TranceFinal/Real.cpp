#include "Real.h"
#include "Defines.h"

string Real::ToString()
{
	return NumToString(m_value);
}

string Real::DebugString()
{
	return "<REAL, " + ToString() + ">";
}


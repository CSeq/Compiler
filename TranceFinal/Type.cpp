#include "Type.h"
#include "Defines.h"



int Type::GetWidth() const
{
	return m_width;
}

shared_ptr<Type> Type::s_int(NEW Type("int", BASIC, 4));
shared_ptr<Type> Type::s_float(NEW Type("float", BASIC, 8));
shared_ptr<Type> Type::s_char(NEW Type("char", BASIC, 1));
shared_ptr<Type> Type::s_bool(NEW Type("bool", BASIC, 1));

bool Type::Numeric(shared_ptr<Type> p)
{
	if (p->GetLexeme().compare(s_char->GetLexeme()) == 0 || p->GetLexeme().compare(s_float->GetLexeme()) == 0 ||
		p->GetLexeme().compare(s_int->GetLexeme()) == 0)
	{
		return true;
	}
	return false;

}

shared_ptr<Type> Type::Max(shared_ptr<Type> t1, shared_ptr<Type> t2)
{
	if (!Numeric(t1) || !Numeric(t2))
		return nullptr;
	if (t1->GetLexeme().compare(s_float->GetLexeme()) == 0 || t2->GetLexeme().compare(s_float->GetLexeme()) == 0) return s_float;
	if (t1->GetLexeme().compare(s_int->GetLexeme()) == 0 || t2->GetLexeme().compare(s_int->GetLexeme()) == 0) return s_int;
	return s_char;
}
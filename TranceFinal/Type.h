#pragma once
#include <string>
#include "Word.h"
using namespace std;

class Type : public Word
{
public:
	Type(string s, int tag, int w) : Word(s, tag), m_width(w) {}
	static shared_ptr<Type> s_int, s_float, s_char, s_bool;
	static bool Numeric(shared_ptr<Type> p);
	static shared_ptr<Type> Max(shared_ptr<Type> t1, shared_ptr<Type> t2);
	int GetWidth() const;
protected:
	int m_width;
	Type() {}
};
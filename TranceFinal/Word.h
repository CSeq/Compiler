#pragma once
#include "Token.h"

class Word : public Token
{
public:
	Word(string s, int tag);
	string GetLexeme() const;
	string ToString() override;
	string DebugString() override;
	static shared_ptr<Word> s_and, s_or, s_eq, s_ne, s_le, s_ge, s_minus, s_true, s_false, s_temp;
	static shared_ptr<Word> s_if, s_else, s_while, s_do, s_break;
protected:
	Word() {}
	string m_lexeme;
};
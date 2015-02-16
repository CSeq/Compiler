#include "Word.h"
#include "Defines.h"

shared_ptr<Word> Word::s_and(NEW Word("&&", AND));
shared_ptr<Word> Word::s_or(NEW Word("||", OR));
shared_ptr<Word> Word::s_eq(NEW Word("==", EQ));
shared_ptr<Word> Word::s_ne(NEW Word("!=", NE));
shared_ptr<Word> Word::s_le(NEW Word("<=", LE));
shared_ptr<Word> Word::s_ge(NEW Word(">=", GE));
shared_ptr<Word> Word::s_minus(NEW Word("minus", MINUS));
shared_ptr<Word> Word::s_true(NEW Word("true", TRUE));
shared_ptr<Word> Word::s_false(NEW Word("false", FALSE));
shared_ptr<Word> Word::s_temp(NEW Word("t", TEMP));
shared_ptr<Word> Word::s_if(NEW Word("if", IF));
shared_ptr<Word> Word::s_else(NEW Word("else", ELSE));
shared_ptr<Word> Word::s_while(NEW Word("while", WHILE));
shared_ptr<Word> Word::s_do(NEW Word("do", DO));
shared_ptr<Word> Word::s_break(NEW Word("break", BREAK));

string Word::GetLexeme() const
{
	return m_lexeme;
}

string Word::ToString()
{
	return m_lexeme;
}

string Word::DebugString()
{
	return "<" + ConvertTag(m_tag) + ", " + ToString() + ">";
}

Word::Word(string s, int tag) : Token(tag)
{
	m_lexeme = s;
}


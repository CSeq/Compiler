#include "Token.h"
#include "Defines.h"
#include "Constant.h"
#include "Type.h"

shared_ptr<Token>Token::s_band(NEW Token('&'));
shared_ptr<Token>Token::s_bor(NEW Token('|'));
shared_ptr<Token> Token::s_ass(NEW Token('='));
shared_ptr<Token> Token::s_not(NEW Token('!'));
shared_ptr<Token> Token::s_lt(NEW Token('<'));
shared_ptr<Token> Token::s_gt(NEW Token('>'));

long long Token::s_nextID = 0;

int Token::GetTag() const
{
	return m_tag;
}

string Token::DebugString()
{
	return "<" + ConvertTag(m_tag) + ">";
}

string Token::ToString()
{
	return string(1, char(m_tag));
}

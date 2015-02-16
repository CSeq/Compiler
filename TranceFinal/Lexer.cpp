#include "Lexer.h"
#include "Word.h"
#include "Defines.h"
#include "Num.h"
#include "Real.h"
#include "Type.h"
#include "Compiler.h"
#include <sstream>

using namespace std;



Lexer::Lexer(string fileName)
{
	Reserve(Word::s_if);
	Reserve(Word::s_else);
	Reserve(Word::s_while);
	Reserve(Word::s_do);
	Reserve(Word::s_break);
	Reserve(Word::s_true);
	Reserve(Word::s_false);
	Reserve(Type::s_int);
	Reserve(Type::s_char);
	Reserve(Type::s_bool);
	Reserve(Type::s_float);
	m_peek = ' ';
}

Lexer::~Lexer()
{
	m_symbolTable.clear();
}

void Lexer::ScanFile()
{
	while (true)
	{
		shared_ptr<Token> nextTok = Scan();
		if (!nextTok)
			break;
		g_Compiler->Print(string(nextTok->DebugString() + "\n"));
	}
}

void Lexer::ReadChar()
{
	m_peek = g_Compiler->GetNextChar();
}

bool Lexer::ReadChar(char c)
{
	ReadChar();
	if (m_peek != c)
		return false;
	m_peek = ' ';
	return true;
}

shared_ptr<Token> Lexer::Scan()
{
	for (;; ReadChar())
	{
		if (m_peek == ' ' || m_peek == '\t')
			continue;
		else if (m_peek == '\n') 
			s_line++;
		else
			break;
	}
	switch (m_peek)
	{
	case '&':
		if (ReadChar('&'))
			return Word::s_and;
		else
			return Token::s_band;
	case '|':
		if (ReadChar('|'))
			return Word::s_or;
		else
			return Token::s_bor;
	case '=':
		if (ReadChar('='))
			return Word::s_eq;
		else
			return Token::s_ass;
	case '!':
		if (ReadChar('='))
			return Word::s_ne;
		else
			return Token::s_not;
	case '<':
		if (ReadChar('='))
			return Word::s_le;
		else
			return Token::s_lt;
	case '>':
		if (ReadChar('='))
			return Word::s_ge;
		else
			return Token::s_gt;
	}
	if (isdigit(m_peek))
	{
		int v = 0;
		do {
			v = 10 * v + atoi(&m_peek); 
			ReadChar();
		} while ( isdigit(m_peek));
		if (m_peek != '.')
		{
			return shared_ptr<Num>(NEW Num(v));
		}
		float x = (float)v; float d = 10.f;
		for(;;)
		{
			ReadChar();
			if (!isdigit(m_peek)) break;
			x = x + atoi(&m_peek) / d; d = d* 10;
		}
		return shared_ptr<Real>(NEW Real(x));
	}
	if (isalpha(m_peek))
	{
		string b = "";
		do {
			b += m_peek;
			ReadChar();
		} while (isalpha(m_peek) || isdigit(m_peek));
		auto it = m_symbolTable.find(b);
		if (it != m_symbolTable.end())
		{
			return it->second;
		}
		shared_ptr<Word> w(NEW Word(b, ID));
		m_symbolTable[b] = w;
		return w;
	}
	if (m_peek == EOF)
		return nullptr;
	shared_ptr<Token> tok(NEW Token(m_peek));
	m_peek = ' ';
	return tok;
}


void Lexer::Reserve(shared_ptr<Word> w)
{
	auto it = m_symbolTable.find(w->GetLexeme());
	if (it == m_symbolTable.end())
		m_symbolTable[w->GetLexeme()] = w;
}

int Lexer::GetLine()
{
	return s_line;
}

int Lexer::s_line = 1;
#include "Compiler.h"
#include "Lexer.h"
#include "Parser.h"
#include "Constant.h"
#include "Type.h"
#include "Defines.h"

Compiler::Compiler(string file, int options)
{
	m_options = options;
	m_fileName = file;
	m_fileIn.open(m_fileName);
	string temp = m_fileName.substr(0, m_fileName.length() - 3);
	temp += "tce";
	m_fileOut.open(temp);
	m_parse = NEW Parser(NEW Lexer(m_fileName));
	Constant::InitStatics();
}

Compiler::~Compiler()
{
	m_fileIn.close();
	m_fileOut.close();
	delete m_parse;
	m_parse = nullptr;
}

void Compiler::Print(string s)
{
	m_fileOut << s;
}

char Compiler::GetNextChar()
{
	return m_fileIn.get();
}

void Compiler::Compile()
{
	m_parse->Move();
	m_parse->Program();
}
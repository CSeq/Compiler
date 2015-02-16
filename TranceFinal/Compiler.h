#pragma once
#include <string>
#include <fstream>
using namespace std;

class Lexer;
class Parser;

class Compiler
{
public:
	Compiler(string file, int options);
	~Compiler();

	void Compile();
	void Print(string s);
	char GetNextChar();
protected:
	ofstream m_fileOut;
	ifstream m_fileIn;
	Parser* m_parse;
	string m_fileName;
	int m_options;
};

extern Compiler* g_Compiler;
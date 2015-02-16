#pragma once
#include <unordered_map>
#include <fstream>
#include <vector>
#include <memory>
using namespace std;

class Word;
class Token;

class Lexer
{
public:
	Lexer(string fileName);
	~Lexer();

	static int GetLine();
	void Reserve(shared_ptr<Word> word);
	void ReadChar();
	bool ReadChar(char c);
	shared_ptr<Token> Scan();
	void ScanFile();
	void RemoveSymbol(Word* id);
protected:
	static int s_line;
	char m_peek;
	unordered_map<string, shared_ptr<Word>> m_symbolTable;
	Lexer() {}
};

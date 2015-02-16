#pragma once
#include <string>
#include <memory>
#include <vector>
using namespace std;

class Lexer;
class Token;
class Env;
class Stmt;
class Expr;
class Access;
class Type;
class Id;
class Node;

class Parser
{
public:
	Parser(Lexer* l);
	~Parser();

	void Move();
	void ThrowError(string s);
	shared_ptr<Token> Match(int i);
	void Program();
	Stmt* Block();
	void Decls();
	shared_ptr<Type> Types();
	shared_ptr<Type> Dims(shared_ptr<Type> p);
	Stmt* Stmts();
	Stmt* Statement();
	Stmt* Assign();
	Expr* Bool();
	Expr* Join();
	Expr* Equality();
	Expr* Relation();
	Expr* Expression();
	Expr* Term();
	Expr* UnaryOp();
	Expr* Factor();
	Access* Offset(Id* i);

	Lexer* GetLexer() const;
	shared_ptr<Token> GetLook() const;
	int GetUsed() const;
protected:
	Lexer* m_lex;
	shared_ptr<Token> m_look;
	Env* m_top;
	int m_used;
	void Shutdown();
};

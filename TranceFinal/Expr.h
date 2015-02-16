#pragma once
#include "Node.h"
#include <string>
#include <memory>
using namespace std;

class Token;
class Type;

class Expr : public Node
{
public:
	Expr(shared_ptr<Token> tok, shared_ptr<Type> type);
	~Expr();

	virtual Expr* Gen();
	virtual Expr* Reduce();
	virtual void Jumping(int t, int f);
	virtual void EmitJumps(string test, int t, int f);
	virtual string ToString();

	shared_ptr<Token> GetToken() const;
	shared_ptr<Type> GetType() const;
protected:
	shared_ptr<Token> m_op;
	shared_ptr<Type> m_type;
};
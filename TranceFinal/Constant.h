#pragma once
#include "Expr.h"
#include <memory>
using namespace std;

class Type;

class Constant : public Expr
{
public:
	Constant(shared_ptr<Token> tok, shared_ptr<Type> type);
	Constant(int i);
	~Constant();

	static shared_ptr<Constant> s_true;
	static shared_ptr<Constant> s_false;

	void Jumping(int t, int f);

	static void InitStatics();
protected:
};
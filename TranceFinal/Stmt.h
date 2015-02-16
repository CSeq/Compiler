#pragma once
#include "Node.h"
#include <memory>
using namespace std;

class Stmt : public Node
{
public:
	Stmt();
	~Stmt();

	static shared_ptr<Stmt> s_null;
	static Stmt* s_enclosing;

	virtual void Gen(int b, int a);

	static void InitStmts();

	int GetAfter() const;
protected:
	int m_after;
};
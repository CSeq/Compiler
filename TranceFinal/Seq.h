#pragma once
#include "Stmt.h"

class Seq : public Stmt
{
public:
	Seq(Stmt* s1, Stmt* s2);
	~Seq();

	void Gen(int b, int a);

	Stmt* GetStmt1() const;
	Stmt* GetStmt2() const;
protected:
	Stmt* m_stmt1;
	Stmt* m_stmt2;
};
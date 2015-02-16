#pragma once
#include "Stmt.h"

class Break : public Stmt
{
public:
	Break();
	~Break();

	void Gen(int b, int a);

	Stmt* GetStmt() const;
protected:
	Stmt* m_stmt;
};
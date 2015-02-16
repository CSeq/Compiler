#pragma once
#include "Op.h"

class Id;

class Access : public Op
{
public:
	Access(Id* id, Expr* x, shared_ptr<Type> type);
	~Access();

	Expr* Gen() override;
	void Jumping(int t, int f);
	string ToString();

	Id* GetArray() const;
	Expr* GetIndex() const;
protected:
	Id* m_array;
	Expr* m_index;
};
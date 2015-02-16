#pragma once
#include "Type.h"

class Array : public Type
{
public:
	Array(int sz, shared_ptr<Type> p);
	~Array();

	string ToString();

	shared_ptr<Type> GetOf() const;
	int GetSize() const;
protected:
	shared_ptr<Type> m_of;
	int m_size;
};
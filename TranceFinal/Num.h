#pragma once
#include "Token.h"
#include "Defines.h"

class Num : public Token
{
public:
	Num(int value) : Token(NUM),  m_value(value) {}
	~Num() {}
	int GetValue() const;
	string ToString() override;
	string DebugString() override;
protected:
	int m_value;
	Num() {}
};
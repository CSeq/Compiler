#pragma once
#include "Token.h"
#include "Defines.h"

class Real : public Token
{
public:
	Real(float value) : Token(REAL), m_value(value) {}
	float GetValue() const { return m_value; }
	string ToString() override;
	string DebugString() override;
protected:
	float m_value;
	Real() {}
};
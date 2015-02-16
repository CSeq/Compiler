#pragma once
#include <string>
using namespace std;


class Node
{
public:
	Node();
	virtual ~Node();

	int GetLexline() const;

	void ThrowError(string s);
	int NewLabel();
	void EmitLabel(int i);
	void Emit(string s);
protected:
	int m_lexline;
	static int s_labels;
};
#pragma once
#include <string>
using namespace std;

class Error
{
public:
	Error(string s);
	virtual ~Error();

	void PrintError();
protected:
	string m_error;
};
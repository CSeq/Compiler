#include "Error.h"
#include <string>
#include <iostream>
using namespace std;

Error::Error(string s)
{
	m_error = s;
}

Error::~Error()
{
}

void Error::PrintError()
{
	cout << m_error << endl;
}
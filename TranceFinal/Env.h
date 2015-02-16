#pragma once
#include <unordered_map>
#include "Token.h"
using namespace std;

class Id;

class Env
{
public:
	Env(Env *n);
	Env();
	~Env();
	void Put(shared_ptr<Token> t, Id* i);
	Env* GetPrev() { return prev; }
	Id* Get(shared_ptr<Token> t);
protected:
	unordered_map<long long, Id*> m_table;
	Env* prev;
};
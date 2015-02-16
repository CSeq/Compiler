#pragma once
#include <string>
#include <memory>
using namespace std;



class Token
{
public:
	Token(int tag) : m_tag(tag) { m_id = s_nextID++; }
	virtual ~Token() {}
	int GetTag() const;
	long long GetID() const { return m_id; }
	virtual string ToString();
	virtual string DebugString();
	static shared_ptr<Token> s_band, s_bor, s_ass, s_not, s_lt, s_gt;
protected:
	Token() {}
	int m_tag;
	long long m_id;
	static long long s_nextID;
};

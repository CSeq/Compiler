#pragma once
#include <sstream>
#include <string>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
using namespace std;
//Defines for the various compiler tokens
#define AND 256
#define BASIC 257
#define BREAK 258
#define DO 259
#define ELSE 260
#define EQ 261
#define	FALSE 262
#define GE 263
#define ID 264
#define IF 265
#define INDEX 266
#define LE 267
#define MINUS 268
#define NE 269
#define NUM 270
#define	OR 271
#define REAL 272
#define TEMP 273
#define TRUE 274
#define WHILE 275

#define NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)

string ConvertTag(int tag);

class Token;
class Expr;

template <typename T>
string NumToString(T num)
{
	ostringstream ss;
	ss << num;
	return ss.str();
}

template <class tocheck, class param>
bool InstanceOf(param* p1)
{
	tocheck* a;
	a = dynamic_cast<tocheck*>(p1);
	if (a == 0)
		return false;
	return true;
}

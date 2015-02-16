#include "Defines.h"
#include "Token.h"
#include "Constant.h"
#include "Word.h"
#include "Type.h"

string ConvertTag(int tag)
{
	switch (tag)
	{
	case AND :
		return "AND";
	case BASIC :
		return "BASIC";
	case BREAK :
		return "BREAK";
	case DO :
		return "DO";
	case ELSE:
		return "ELSE";
	case EQ :
		return "EQ";
	case FALSE:
		return "FALSE";
	case GE:
		return "GE";
	case ID:
		return "ID";
	case IF:
		return "IF";
	case INDEX: 
		return "INDEX";
	case LE:
		return "LE";
	case MINUS:
		return "MINUS";
	case NE:
		return "NE";
	case NUM:
		return "NUM";
	case OR:
		return "OR";
	case REAL:
		return "REAL";
	case TEMP:
		return "TEMP";
	case TRUE:
		return "TRUE";
	case WHILE:
		return "WHILE";
	default:
		return string(1, char(tag));
	}
}

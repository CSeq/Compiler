#include "Node.h"
#include "Lexer.h"
#include "Error.h"
#include "Compiler.h"
#include "Defines.h"


int Node::s_labels = 0;

Node::Node()
{
	m_lexline = Lexer::GetLine();
}

Node::~Node()
{
}

int Node::GetLexline() const
{
	return m_lexline;
}

void Node::ThrowError(string s)
{
	throw NEW Error("near line " + NumToString(m_lexline) + ": " + s);
}

int Node::NewLabel()
{
	return ++s_labels;
}

void Node::EmitLabel(int i)
{
	g_Compiler->Print("L" + NumToString(i) + string(":"));
}

void Node::Emit(string s)
{
	g_Compiler->Print("\t" + s + "\n");
}
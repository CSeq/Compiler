#include "Parser.h"
#include "Lexer.h"
#include "Token.h"
#include "Env.h"
#include "Stmt.h"
#include "Expr.h"
#include "Access.h"
#include "Type.h"
#include "Error.h"
#include "Defines.h"
#include "Id.h"
#include "Array.h"
#include "Num.h"
#include "Seq.h"
#include "If.h"
#include "Else.h"
#include "While.h"
#include "Do.h"
#include "Break.h"
#include "Set.h"
#include "SetElem.h"
#include "Or.h"
#include "And.h"
#include "Rel.h"
#include "Arith.h"
#include "Unary.h"
#include "Not.h"
#include "Constant.h"

Parser::Parser(Lexer* l)
{
	m_top = nullptr;
	m_used = 0;
	m_lex = l;
	m_look = nullptr;
	Stmt::InitStmts();
}

Parser::~Parser()
{
}

void Parser::Move()
{
	m_look = m_lex->Scan();
}

void Parser::ThrowError(string s)
{
	throw NEW Error("near line " + NumToString(Lexer::GetLine()) + ": " + s); 
}

shared_ptr<Token> Parser::Match(int t)
{
	if (m_look->GetTag() == t)
	{
		shared_ptr<Token> returnV = m_look;
		Move();
		return returnV;
	}
	else
	{
		ThrowError("syntax error: expected \'" + string(1, char(t)) + "\'");
	}
}

void Parser::Program()
{
	Stmt* s = Block();
	int begin = s->NewLabel();
	int after = s->NewLabel();
	s->EmitLabel(begin);
	s->Gen(begin, after);
	s->EmitLabel(after);
	delete s;
	Shutdown();
}

void Parser::Shutdown()
{
	while (m_top)
	{
		Env* temp = m_top->GetPrev();
		delete m_top;
		m_top = temp;
	}
	delete m_lex;
}

Stmt* Parser::Block()
{
	Match('{');
	Env* savedEnv = m_top;
	m_top = NEW Env(m_top);
	Decls();
	Stmt* s = Stmts();
	Match('}');
	delete m_top;
	m_top = savedEnv;
	return s;
}

void Parser::Decls()
{
	while (m_look->GetTag() == BASIC)
	{
		shared_ptr<Type> p = Types();
		shared_ptr<Token> tok = m_look;
		Match(ID);
		Match(';');
		Id* id = NEW Id(static_pointer_cast<Word>(tok), p, m_used);
		m_top->Put(tok, id);
		m_used = m_used + p->GetWidth();
	}
}

shared_ptr<Type> Parser::Types()
{
	shared_ptr<Type> p = static_pointer_cast<Type>(m_look);
	Match(BASIC);
	if (m_look->GetTag() != '[')
	{
		return p;
	}
	else
	{
		return Dims(p);
	}
}

shared_ptr<Type> Parser::Dims(shared_ptr<Type> p)
{
	Match('[');
	shared_ptr<Token> tok = m_look;
	Match(NUM);
	Match(']');
	if (m_look->GetTag() == '[')
	{
		p = Dims(p);
	}
	return shared_ptr<Array>(NEW Array((static_pointer_cast<Num>(tok))->GetValue(), p));
}

Stmt* Parser::Stmts()
{
	if (m_look->GetTag() == '}')
	{
		return Stmt::s_null.get();
	}
	Stmt* s1 = Statement();
	Stmt* s2 = Stmts();
	return NEW Seq(s1, s2);
}

Stmt* Parser::Statement()
{
	Expr* x;
	Stmt *s1, *s2;
	Stmt* savedStmt;
	switch(m_look->GetTag())
	{
	case ';':
		Move();
		return Stmt::s_null.get();
	case IF:
		{
			Match(IF);
			Match('(');
			x = Bool();
			Match(')');
			s1 = Statement();
			if(m_look->GetTag() != ELSE)
			{
				return NEW If(x, s1);
			}
			Match(ELSE);
			s2 = Statement();
			return NEW Else(x, s1, s2);
		}
	case WHILE:
		{
		While* whileNode = NEW While();
		savedStmt = Stmt::s_enclosing;
		Stmt::s_enclosing = whileNode;
		Match(WHILE);
		Match('(');
		x = Bool();
		Match(')');
		s1 = Statement();
		whileNode->Init(x, s1);
		Stmt::s_enclosing = savedStmt;
		return whileNode;
		}
	case DO:
		{
		Do* doNode = NEW Do();
		savedStmt = Stmt::s_enclosing;
		Stmt::s_enclosing = doNode;
		Match(DO);
		s1 = Statement();
		Match(WHILE);
		Match('(');
		x = Bool();
		Match(')');
		Match(';');
		doNode->Init(s1, x);
		Stmt::s_enclosing = savedStmt;
		return doNode;
		}
	case BREAK:
		{
		Match(BREAK);
		Match(';');
		return NEW Break();
		}
	case '{':
		return Block();
	default:
		return Assign();
	}
}

Stmt* Parser::Assign()
{
	Stmt* stmt;
	shared_ptr<Token> t = m_look;
	Match(ID);
	Id* id = m_top->Get(t);
	if (!id)
	{
		ThrowError(t->ToString() + " undeclared");
	}
	if (m_look->GetTag() == '=')
	{
		Move();
		stmt = NEW Set(id, Bool());
	}
	else
	{
		Access* x = Offset(id);
		Match('=');
		stmt = NEW SetElem(x, Bool());
	}
	Match(';');
	return stmt;
}

Expr* Parser::Bool()
{
	Expr* x = Join();
	while (m_look->GetTag() == OR)
	{
		shared_ptr<Token> tok = m_look;
		Move();
		x = NEW Or(tok, x, Join());
	}
	return x;
}

Expr* Parser::Join()
{
	Expr* x = Equality();
	while(m_look->GetTag() == AND)
	{
		shared_ptr<Token> tok = m_look;
		Move();
		x = NEW And(tok, x, Equality());
	}
	return x;
}

Expr* Parser::Equality()
{
	Expr* x = Relation();
	while(m_look->GetTag() == EQ || m_look->GetTag() == NE)
	{
		shared_ptr<Token> tok = m_look;
		Move();
		x = NEW Rel(tok, x, Relation());
	}
	return x;
}

Expr* Parser::Relation()
{
	Expr* x = Expression();
	switch (m_look->GetTag())
	{
	case '<':
	case LE:
	case GE:
	case '>':
		{
		shared_ptr<Token> tok = m_look;
		Move();
		return NEW Rel(tok, x, Expression());
		}
	default:
		return x;
	}
}

Expr* Parser::Expression()
{
	Expr* x = Term();
	while (m_look->GetTag() == '+' || m_look->GetTag() == '-')
	{
		shared_ptr<Token> tok = m_look;
		Move();
		x = NEW Arith(tok, x, Term());
	}
	return x;
}

Expr* Parser::Term()
{
	Expr* x = UnaryOp();
	while (m_look->GetTag() == '*' || m_look->GetTag() == '/')
	{
		shared_ptr<Token> tok = m_look;
		Move();
		x = NEW Arith(tok, x, UnaryOp());
	}
	return x;
}

Expr* Parser::UnaryOp()
{
	if (m_look->GetTag() == '-')
	{
		Move();
		return NEW Unary(Word::s_minus, UnaryOp());
	}
	else if (m_look->GetTag() == NE)
	{
		shared_ptr<Token> tok = m_look;
		Move();
		return NEW Not(tok, UnaryOp());
	}
	else
	{
		return Factor();
	}
}

Expr* Parser::Factor()
{
	Expr* x = nullptr;
	switch (m_look->GetTag())
	{
	case '(':
		Move();
		x = Bool();
		Match(')');
		return x;
	case NUM:
		x = NEW Constant(m_look, Type::s_int);
		Move();
		return x;
	case REAL:
		x = NEW Constant(m_look, Type::s_float);
		Move();
		return x;
	case TRUE:
		x = Constant::s_true.get();
		Move();
		return x;
	case FALSE:
		x = Constant::s_false.get();
		Move();
		return x;
	default:
		ThrowError("syntax error");
		return x;
	case ID:
		string s = m_look->ToString();
		Id* id = m_top->Get(m_look);
		if (!id)
		{
			ThrowError(m_look->ToString() + " undeclared");
		}
		Move();
		if(m_look->GetTag() != '[')
		{
			return id;
		}
		return Offset(id);
	}
}

Access* Parser::Offset(Id* a)
{
	Expr* i, *w, *t1, *t2, *loc;
	shared_ptr<Type> type = a->GetType();
	Match('[');
	i = Bool();
	Match(']');
	type = (static_pointer_cast<Array>(type))->GetOf();
	w = NEW Constant(type->GetWidth());
	shared_ptr<Token> tok(NEW Token('*'));
	t1 = NEW Arith(tok, i, w);
	loc = t1;
	while (m_look->GetTag() == '[')
	{
		Match('[');
		i = Bool();
		Match(']');
		type = (static_pointer_cast<Array>(type))->GetOf();
		w = NEW Constant(type->GetWidth());
		shared_ptr<Token> temp1(NEW Token('*'));
		shared_ptr<Token> temp2(NEW Token('+'));
		t1 = NEW Arith(temp1, i, w);
		t2 = NEW Arith(temp2, loc, t1);
		loc = t2;
	}
	return NEW Access(a, loc, type);
}

Lexer* Parser::GetLexer() const
{
	return m_lex;
}

shared_ptr<Token> Parser::GetLook() const
{
	return m_look;
}


int Parser::GetUsed() const
{
	return m_used;
}

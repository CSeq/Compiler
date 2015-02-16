#include <iostream>
#include "Compiler.h"
#include "Defines.h"
#include "Error.h"

using namespace std;

Compiler* g_Compiler;

int main(int arg, char* argv[])
{
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	if (arg < 2)
	{
		cout << "Usage: TranceComp.exe <filename> <compiler arguments>" << endl;
		exit(1);
	}
	try
	{
		g_Compiler = NEW Compiler(string(argv[1]), 0);
		g_Compiler->Compile();
		cout << "Compilation Successful\n";
	}
	catch(Error* n)
	{
		n->PrintError();
		delete n;
		n = nullptr;
	}
	delete g_Compiler;
	g_Compiler = nullptr;
	cin.get();
	return 0;
}
# Compiler
Top down recursive descent parser and lexical analyzer for a programming language

Author: Thomas Loudiana

Description:  This is the front end of a compiler that performs lexical analysis and parsing.

Installation:  No dependencies here.  Just clone and compile.  There is a .bat file that will run the compiler 
and pass in the 'Test.txt' file as a command line argument.  The front end will then compile, report errors,
and translate to 3 address code.  Change the .txt file and watch how the .tce file changes.

Future:  In the future there will a backend compiler that performs some optimization steps before translating to native
code.  The instruction set supported by the backend will be dependant on whatever type of instruction set I am running at
the time.

Sample:  Without listing the entire grammar for language here is what the sample file looks like:
'''
{
	int x;
	float[5] array;
	int index;
	index = 0;
	x = 3 + 2;
	if (x == 5)
	{
		x = 6;
	}
	do
	{
		x = x - 1;
	} while (x > 0);

	while (index < 5)
	{
		array[index] = index + 1;
	}
}
'''
and here is how it translates
'''
L1:	index = 0
L3:	x = 3 + 2
L4:	iffalse x == 5 goto L5
L6:	x = 6
L5:	x = x - 1
L8:	if x > 0 goto L5
L7:	iffalse index < 5 goto L2
L9:	t1 = index * 8
	t2 = index + 1
	array [ t1 ] = t2
	goto L7
L2:
'''

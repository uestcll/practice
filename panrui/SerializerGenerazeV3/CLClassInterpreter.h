#ifndef CLClassInterpreter_H
#define CLClassInterpreter_H

#include <map>
#include <iostream>
#include <fstream>

#define STRUCT_FLAG			"struct"
#define CLASS_FLAG			"class"
#define SERIAL_FLAG			"_SERIAL_"
#define VIRTUAL_FLAG		"virtual"

#define KEY_WORD_PUBLIC		"public:"
#define KEY_WORD_PRIVATE	"private:"
#define KEY_WORD_PROTECTED	"protected:"


#define VAR			0
#define STATIC_VAR	1
#define FUNCTION	2	

using namespace std;

class CLClassDescribe;
class CLAbstractType;

class CLClassInterpreter
{
public:

	CLClassInterpreter();
	~CLClassInterpreter();

	CLClassDescribe * loadClassByFilename(string &);

private:

	CLClassInterpreter(const CLClassInterpreter & );
	const CLClassInterpreter & operator = (const CLClassInterpreter & );

private:

	ifstream m_istr;
	CLClassDescribe * m_classDescribe;

	void getNextObj(string & );

	bool getClassEntryAndAllocateClassDescribe();
	void completeClassDescribeFromContent();

	int  getStatementType(string &);

public:
	static void getNextObj(string &in ,string &out ,bool if_reset);

	static map<string, CLAbstractType * (*)() > s_ElementGeterFunctionMap;
	static CLAbstractType * getNewElement(string & statement);
	static CLAbstractType * getBuiltIn();
	static CLAbstractType * getString();
	static CLAbstractType * getUserDef();


};

#endif
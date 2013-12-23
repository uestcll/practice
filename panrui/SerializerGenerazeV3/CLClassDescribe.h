#ifndef CLClassDescribe_H
#define CLClassDescribe_H

#define STRUCT_FEATURE		0x00000001
#define VIRTUAL_FEATURE		0x00000010
#define SERIAL_FEATURE		0x00000100


#include <string>
#include <set>
#include <list>

using namespace std;


class CLAbstractType;

class CLClassDescribe
{

public:
	
	CLClassDescribe();
	~CLClassDescribe();

public:

	string m_classname;
	string m_superClassname;
	set<int > m_featrueSet;
	list<CLAbstractType *> m_elementList; 

private:

	CLClassDescribe(const CLClassDescribe & );
	const CLClassDescribe & operator = (const CLClassDescribe &);

};


#endif
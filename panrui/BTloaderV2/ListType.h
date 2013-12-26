#ifndef ListType_H
#define ListType_H

#include <list>
#include <fstream>
using namespace std;

#include "BaseType.h"

class Unit;

class ListType:public BaseType
{
public:
	friend class Unit;

	ListType(ifstream & );

private:

	void initFromFile(ifstream & );

	virtual ~ListType();	

	list<Unit *> m_list;

};

#endif
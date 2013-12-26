#ifndef DictionaryType_H
#define DictionaryType_H

#include <map>
#include <fstream>
using namespace std;

#include "BaseType.h"

class Unit;

class DictionaryType:public BaseType
{
public:
	friend class Unit;

	DictionaryType(ifstream & );

private:

	void initFromFile(ifstream & );

	virtual ~DictionaryType();

	map<Unit *,Unit *> m_map;

};

#endif
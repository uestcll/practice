#ifndef Unit_H
#define Unit_H

#include <fstream>
using namespace std;

class BaseType;

class Unit
{
public:

	Unit();
	~Unit();
	Unit(BaseType * );

		
	Unit * build(ifstream & );

private:
	Unit(Unit &);
	const Unit & operator = (const Unit &);

	BaseType * m_data;

	BaseType * retStringType(ifstream & );
	BaseType * retIntegerType(ifstream & );
	BaseType * retDictionaryType(ifstream & );
	BaseType * retListType(ifstream & );
};


#endif
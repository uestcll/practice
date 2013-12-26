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

		
	static Unit * build(ifstream & );

private:
	Unit(Unit &);
	const Unit & operator = (const Unit &);

	BaseType * m_data;

	static BaseType * retStringType(ifstream & );
	static BaseType * retIntegerType(ifstream & );
	static BaseType * retDictionaryType(ifstream & );
	static BaseType * retListType(ifstream & );
};


#endif
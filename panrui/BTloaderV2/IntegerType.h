#ifndef IntegerType_H
#define IntegerType_H

#include <fstream>
using namespace std;

#include "BaseType.h"

class IntegerType:public BaseType
{
public:
	friend class Unit;
	
	IntegerType(ifstream & );

	const long long &data_ref;

private:

	virtual ~IntegerType();
	
	long long m_data;

};

#endif
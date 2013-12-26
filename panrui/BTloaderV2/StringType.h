#ifndef StringType_H
#define StringType_H

#include <fstream>
using namespace std;

#include "BaseType.h"

class StringType:public BaseType
{
public:
	friend class Unit;

	StringType(ifstream & );

	const int &size_ref;
	const char * const & buf_ref;

private:

	virtual ~StringType();

	char *	m_buf;
	int		m_size;

};


#endif
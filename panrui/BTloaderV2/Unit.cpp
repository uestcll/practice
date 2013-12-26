#include "Unit.h"
#include "BaseType.h"

#include "DictionaryType.h"
#include "IntegerType.h"
#include "ListType.h"
#include "StringType.h"

Unit::Unit():m_data(NULL)
{

}

Unit::~Unit()
{
	if(m_data)
	{
		delete m_data;
	}
}

Unit::Unit(BaseType * v_data)
{
	m_data = v_data;
}

Unit * Unit::build(ifstream & v_istr)
{
	char t_type = v_istr.get();
	v_istr.seekg(-1,ios::cur);

	if( t_type <='9' && t_type >= '0')
	{
		return new Unit(retStringType(v_istr));
	}
	else if(t_type == 'i')
	{
		return new Unit(retIntegerType(v_istr));
	}
	else if(t_type == 'l')
	{
		return new Unit(retListType(v_istr));
	}
	else if(t_type == 'd')
	{
		return new Unit(retDictionaryType(v_istr));
	}
	else
		return NULL;

}

BaseType * Unit::retStringType(ifstream & v_istr)
{
	return new StringType(v_istr);
}

BaseType * Unit::retIntegerType(ifstream & v_istr)
{
	return new IntegerType(v_istr);
}


BaseType * Unit::retDictionaryType(ifstream & v_istr)
{
	return new DictionaryType(v_istr);
}


BaseType * Unit::retListType(ifstream & v_istr)
{
	return new ListType(v_istr);
}

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
		return new Unit(new StringType(v_istr));
	}
	else if(t_type == 'i')
	{
		return new Unit(new IntegerType(v_istr));
	}
	else if(t_type == 'l')
	{
		return new Unit(new ListType(v_istr));
	}
	else if(t_type == 'd')
	{
		return new Unit(new DictionaryType(v_istr));
	}
	else
		return NULL;

}


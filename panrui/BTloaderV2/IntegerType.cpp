#include "IntegerType.h"

IntegerType::IntegerType(ifstream & v_istr):data_ref(m_data)
{
	v_istr.get();

	char t_int[20] = {0};
	v_istr.getline(t_int,20,'e');

	m_data = atoi(t_int);
}

IntegerType::~IntegerType()
{

}

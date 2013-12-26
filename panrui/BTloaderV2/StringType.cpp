#include "StringType.h"

StringType::StringType(ifstream & v_istr):size_ref(m_size),buf_ref(m_buf),m_buf(NULL)
{
	char t_size[20] = {0};
	v_istr.getline(t_size,20,':');

	m_size = atoi(t_size);
	if(!m_size)
		throw runtime_error("cannot get string size");
	
	m_buf = new char[m_size+1];
	memset(m_buf,0,m_size+1);

	v_istr.read(m_buf,m_size);
}

StringType::~StringType()
{
	if(m_buf != NULL)
		delete []m_buf;
}
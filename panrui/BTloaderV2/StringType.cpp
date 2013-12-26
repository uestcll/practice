#include "StringType.h"

StringType::StringType(ifstream & ):size_ref(m_size),buf_ref(m_buf),m_buf(NULL)
{

}

StringType::~StringType()
{
	if(m_buf != NULL)
		delete m_buf;
}
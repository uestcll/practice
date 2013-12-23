#include "CLAbstractType.h"

CLAbstractType::CLAbstractType():m_type_len(0),
	m_isPtr(false),m_isArray(false),m_arraySize(0),m_off(0)
{

}

CLAbstractType::~CLAbstractType()
{

}


void CLAbstractType::getNextItem(string &tmp,string &out,bool if_reset)
{
	static string::iterator it;
	out = "";

	if(if_reset)
		it = tmp.begin();

	while( it != tmp.end())
	{
		if(*it == ' '||*it == '\t'||*it == ';')
		{
			if(out == "")
			{
				it++;
				continue;
			}
			else
			{
				it++;
				break;
			}
		}

		if(*it == '*'||*it == '['||*it == ']')
		{
			if(out == "")
			{
				out.push_back(*it);
				it++;
				break;
			}
			else
			{
				break;
			}
		}

		out.push_back(*it);
		it++;
	}
}

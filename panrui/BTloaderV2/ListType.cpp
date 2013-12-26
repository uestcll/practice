#include "ListType.h"
#include "Unit.h"

ListType::ListType(ifstream & v_istr)
{
	initFromFile(v_istr);
}

void ListType::initFromFile(ifstream & v_istr)
{

}

ListType::~ListType()
{
	list<Unit *>::iterator it = m_list.begin();
	
	while(it != m_list.end())
	{
		delete *it;
	}
}
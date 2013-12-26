#include "ListType.h"
#include "Unit.h"

ListType::ListType(ifstream & v_istr)
{
	initFromFile(v_istr);
}

void ListType::initFromFile(ifstream & v_istr)
{
	v_istr.get();
	while(true)
	{
		this->m_list.push_back(Unit::build(v_istr));

		char endflag = v_istr.get();
		if(endflag = 'e')
			break;
		else
			v_istr.seekg(-1,ios::cur);
	}
}

ListType::~ListType()
{
	list<Unit *>::iterator it = m_list.begin();
	
	while(it != m_list.end())
	{
		delete *it;
	}
}
#include "DictionaryType.h"
#include "Unit.h"

DictionaryType::DictionaryType(ifstream & v_istr)
{
	initFromFile(v_istr);
}

void DictionaryType::initFromFile(ifstream & v_istr)
{

}

DictionaryType::~DictionaryType()
{
	map<Unit *,Unit *>::iterator it = m_map.begin();
	
	while( it != m_map.end())
	{
		delete it->first;
		delete it->second;
	}
}
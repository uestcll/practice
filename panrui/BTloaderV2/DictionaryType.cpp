#include "DictionaryType.h"
#include "Unit.h"

DictionaryType::DictionaryType(ifstream & v_istr)
{
	initFromFile(v_istr);
}

void DictionaryType::initFromFile(ifstream & v_istr)
{
	v_istr.get();
	while(true)
	{
		Unit *fir = Unit::build(v_istr);
		Unit *sec = Unit::build(v_istr);

		this->m_map.insert(pair<Unit *,Unit *>(fir,sec));

		char endflag = v_istr.get();
		if(endflag = 'e')
			break;
		else
			v_istr.seekg(-1,ios::cur);
	}
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
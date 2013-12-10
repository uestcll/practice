#include "CLOffsetSeter.h"
#include "CLMsgClass.h"
#include "CLMsgClassManager.h"
#include "CLMsgElement.h"
#include "CLUserType.h"


CLOffsetSeter::CLOffsetSeter(CLMsgClass * in_class):m_class(in_class)
{
}

CLOffsetSeter::~CLOffsetSeter()
{

}

offset CLOffsetSeter::setOffset(CLMsgClassManager * pmng)
{
	offset cur_off = {0,0};
	if(m_class->getSuperClass() == ""&&m_class->getVirtualClassFlag())
		cur_off.from_start+=8;
	if(m_class->getSuperClass() != "")
		cur_off += (m_class->m_pmng->findClass(m_class->getSuperClass()))->setOffset();

	list<shared_ptr<CLMsgElement> >::iterator  it = m_class->m_memberVar.begin();
	while(it !=  m_class->m_memberVar.end())
	{
		int type_len = (it->get())->getTypeLen();

		if(typeid(*(it->get())) == typeid(CLUserType))
		{
			offset latest = pmng->findClass(((CLUserType *)(it->get()))->getTypeName() )->setOffset();

			if(it->get()->getPtrFlag())
				cur_off.from_start+=4;
			else if(it->get()->getArrFlag())
			{
				cur_off.max_unit = cur_off.max_unit>latest.max_unit?cur_off.max_unit:latest.max_unit;
				cur_off.from_start += latest.from_start * it->get()->getArrLen();
			}
			else
			{
				cur_off.max_unit = cur_off.max_unit>latest.max_unit?cur_off.max_unit:latest.max_unit;
				cur_off.from_start += latest.from_start;			
			}
			it++;
			continue;
		}
		if(cur_off.from_start%type_len)
		{
			cur_off.from_start = (cur_off.from_start/type_len + 1)*type_len;
		}

		(it->get())->setOff(cur_off.from_start);


		if(it->get()->getArrFlag() )
			cur_off.from_start += type_len * it->get()->getArrLen();
		else
			cur_off.from_start += type_len;


		if(cur_off.max_unit < (unsigned long)type_len)
			cur_off.max_unit = type_len;
		it++;
	}
	if(cur_off.from_start%cur_off.max_unit)
		cur_off.from_start = (cur_off.from_start/cur_off.max_unit + 1)*cur_off.max_unit;

	return cur_off;
}
#include "CLSetOffset.h"
#include "CLClassDescribe.h"
#include "CLAbstractType.h"
#include "CLSerializerAndDeserializerCreater.h"

#include "CLUserDefType.h"

CLSetOffset::CLSetOffset()
{

}

CLSetOffset::~CLSetOffset()
{

}

offset startWork(CLClassDescribe * v_classDescribe ,CLSerializerAndDeserializerCreater * v_classDescribeMap)
{
	offset cur_off = {0,0};
	
	if(v_classDescribe->m_superClassname == ""&&(v_classDescribe->m_featrueSet.find(VIRTUAL_FEATURE ) != v_classDescribe->m_featrueSet.end() ) )
		cur_off.from_start+=8;
	
	if(v_classDescribe->m_superClassname != "")
	{
		cur_off += startWork(v_classDescribeMap->m_classDescribeMap.find(v_classDescribe->m_superClassname)->second,v_classDescribeMap);
	}

	list<CLAbstractType * >::iterator  it = v_classDescribe->m_elementList.begin();

	while(it !=  v_classDescribe->m_elementList.end())
	{
		int type_len = (*it)->getTypeLen();

		if(typeid( *(*it) ) == typeid(CLUserDefType ))
		{
			offset latest = startWork(v_classDescribeMap->m_classDescribeMap.find(((CLUserDefType *)(*it))->getUserDefName())->second,v_classDescribeMap);

			if(cur_off.from_start % latest.max_unit)
				cur_off.from_start = (cur_off.from_start/latest.max_unit + 1)*latest.max_unit;

			(*it)->setOff(cur_off.from_start);

			if((*it)->getPtrFlag())
			{
				cur_off.from_start += 8;
			}
			else if((*it)->getArrFlag())
			{
				cur_off.max_unit = cur_off.max_unit>latest.max_unit?cur_off.max_unit:latest.max_unit;
	
				cur_off.from_start += (*it)->getArrSize() * latest.from_start;
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

		(*it)->setOff(cur_off.from_start);


		if((*it)->getArrFlag() )
			cur_off.from_start += type_len * (*it)->getArrSize();
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
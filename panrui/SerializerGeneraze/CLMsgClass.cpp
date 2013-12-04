#include "CLMsgClass.h"
#include "CLMsgClassManager.h"
#include "CLMsgElement.h"
#include <iostream>


CLMsgClass::CLMsgClass(bool is_struct = false,CLMsgClassManager * p_mng = NULL):m_isVirtualClass(false)
	,m_isStruct(is_struct),m_superClass(""),m_pmng(p_mng)
{}
CLMsgClass::~CLMsgClass(){}

CLMsgElement * CLMsgClass::addMemberVar(CLMsgElement *memberVar)
{
	m_memberVar.push_back(shared_ptr<CLMsgElement >(memberVar));
	return memberVar;
}

void CLMsgClass::addSuperClass(string &superClass)
{
	if(superClass == "")
	{
		cout<<"add superclass error,nil string"<<endl;
		return;
	}
	m_superClass = superClass;
}

void CLMsgClass::setVirtualClass()
{
	this->m_isVirtualClass = true;
}



offset CLMsgClass::setOffset()
{
	offset cur_off = {0,0};
	if(m_superClass == ""&&m_isVirtualClass)
		cur_off.from_start+=8;
	if(m_superClass != "")
		cur_off += (m_pmng->findClass(m_superClass))->setOffset();

	list<shared_ptr<CLMsgElement> >::iterator  it = m_memberVar.begin();
	while(it != m_memberVar.end())
	{
		int type_len = (it->get())->getTypeLen();

		if(cur_off.from_start%type_len)
		{
			cur_off.from_start = (cur_off.from_start/type_len + 1)*type_len;
		}

		(it->get())->setOff(cur_off.from_start);
		cur_off.from_start += type_len;
		if(cur_off.max_unit < (unsigned long)type_len)
			cur_off.max_unit = type_len;
		it++;
	}
	if(cur_off.from_start%cur_off.max_unit)
		cur_off.from_start = (cur_off.from_start/cur_off.max_unit + 1)*cur_off.max_unit;

	return cur_off;
}

const offset & offset::operator += (const offset & another)
{
	this->from_start += another.from_start;
	if(this->max_unit<another.max_unit)
		this->max_unit = another.max_unit;
	return *this;
}


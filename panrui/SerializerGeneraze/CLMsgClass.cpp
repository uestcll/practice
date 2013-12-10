#include "CLMsgClass.h"
#include "CLMsgClassManager.h"
#include "CLMsgElement.h"
#include "CLOffsetSeter.h"
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
	CLOffsetSeter off_seter(this);
	return off_seter.setOffset(m_pmng);
}

const offset & offset::operator += (const offset & another)
{
	this->from_start += another.from_start;
	if(this->max_unit<another.max_unit)
		this->max_unit = another.max_unit;
	return *this;
}


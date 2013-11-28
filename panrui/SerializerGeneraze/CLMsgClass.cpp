#include "CLMsgClass.h"

#include <iostream>

CLMsgClass::CLMsgClass(bool is_struct = false):m_isVirtualClass(false),m_isStruct(is_struct){}
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


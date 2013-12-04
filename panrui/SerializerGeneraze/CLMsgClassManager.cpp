#include "CLMsgClassManager.h"
#include "CLMsgClassLoader.h"
#include "CLMsgClass.h"
CLMsgClassManager::CLMsgClassManager(){}

CLMsgClassManager::~CLMsgClassManager(){}

CLMsgClass* CLMsgClassManager::findClass(string classname)
{
	return (classMap.find(classname))->second.get();
}

CLMsgClass* CLMsgClassManager::classRegister(string classname,bool is_needserial,bool is_struct)
{
	if(is_needserial)
		serialingNameMap.push_back(string(classname));

	classMap[classname].reset(new CLMsgClass(is_struct,this));
	return classMap[classname].get();
}

void CLMsgClassManager::loadAlltheFile(string *filelist,int strNum)
{
	CLMsgClassLoader loader(this,filelist,strNum);
}
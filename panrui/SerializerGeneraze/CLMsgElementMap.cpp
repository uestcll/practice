#include "CLMsgElementMap.h"
#include <string>

#include "CLBasicType.h"
#include "CLPointerType.h"
#include "CLStringType.h"
#include "CLUserType.h"

CLMsgElementMap::CLMsgElementMap()
{
	registMap();
}
CLMsgElementMap::~CLMsgElementMap()
{

}
CLMsgElementMap * CLMsgElementMap::getInstance()
{
	static CLMsgElementMap s_msmap;
	return & s_msmap;
}


CLMsgElement * CLMsgElementMap::initNewElement(string &sentence)
{
	string type;
	getNextItem(sentence,type,true);
	while((type.find("const",0)!=string::npos)||(type.find("static",0)!=string::npos)||(type.find("*",0)!=string::npos)||(type.find("unsigned",0)!=string::npos)||(type.find("signed",0)!=string::npos))
	{
		getNextItem(sentence,type,false);
	}
	
	string check = "";
	getNextItem(sentence,check,false);
	if(check == "*")
		type = check;

	map<string ,CLMsgElement * (*)()>::iterator it = f_map.find(type);
	if(it == f_map.end())
	{
		if(type == "")
			return NULL;
		else
			type = "userdef";

		it = f_map.find(type);
	}
	
	return it->second();
}

void CLMsgElementMap::getNextItem(string &tmp,string &out,bool if_reset)
{
	static string::iterator it;
	out = "";
	if(if_reset)
		it = tmp.begin();
	while( it != tmp.end())
	{
		if(*it == ' '||*it == '\t'||*it == ';')
		{
			if(out == "")
			{
				it++;
				continue;
			}
			else{
				it++;
				break;
			}
		}
		if(*it == '*')
		{
			if(out == "")
			{
				out.push_back(*it);
				it++;
				break;
			}
			else
			{
				break;
			}
		}
		out.push_back(*it);
		it++;
	}
}

void CLMsgElementMap::registMap()
{
	f_map["int"] = initBasic;
	f_map["short"] = initBasic;
	f_map["long"] = initBasic;
	f_map["char"] = initBasic;
	f_map["float"] = initBasic;
	f_map["double"] = initBasic;
	f_map["uint32_t"] = initBasic;
	f_map["uint16_t"] = initBasic;
	f_map["uint8_t"] = initBasic;
	f_map["string"] = initString;
	f_map["*"] = initPointer;
	f_map["userdef"] = initUser;
}

CLMsgElement * CLMsgElementMap::initBasic()
{
	return new CLBasicType;
}

CLMsgElement * CLMsgElementMap::initPointer()
{
	return new CLPointerType;
}

CLMsgElement * CLMsgElementMap::initString()
{
	return new CLStringType;
}

CLMsgElement * CLMsgElementMap::initUser()
{
	return new CLUserType;
}
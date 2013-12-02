#include "CLBasicType.h"
#include "CLMsgClassLoader.h"

using namespace filedeal;
CLBasicType::CLBasicType()
{

}
CLBasicType::~CLBasicType()
{

}

void CLBasicType::newVarDefinitionSentence(string &sentence)
{
	string type;
	getNextItem(sentence,type,true);
	while((type.find("const",0)!=string::npos)||(type.find("static",0)!=string::npos)||(type.find("*",0)!=string::npos)||(type.find("unsigned",0)!=string::npos)||(type.find("signed",0)!=string::npos))
	{
		getNextItem(sentence,type,false);
	}	
	if(type == "int"||type == "float"||type == "uin32_t")
		this->type_len = 4;
	else if(type == "short"||type == "uint16_t")
		this->type_len = 2;
	else if(type == "char"||type == "uint8_t")
		this->type_len = 1;
	else if(type == "long"||type == "double")
		this->type_len = 8;
	else
		return ;
}

void CLBasicType::getNextItem(string &tmp,string &out,bool if_reset)
{
	static string::iterator it;
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

string CLBasicType::writeDeserializer(){
	return NULL;
}

string CLBasicType::writeSerialier()
{
	return NULL;
}
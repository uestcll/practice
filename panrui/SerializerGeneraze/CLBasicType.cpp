#include "CLBasicType.h"
#include "CLMsgClassLoader.cpp"

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
	while((type.find("const")!=string::npos)||(type.find("static")!=string::npos)||(type.find("*")!=string::npos)||(type.find("unsigned")!=string::npos)(type.find("signed")!=string::npos))
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

void CLBasicType::getNextItem(string tmp,string &out,bool if_reset)
{
	static string::iterator it;
	if(if_reset)
		it = tmp.begin();
	while( it != tmp.end())
	{
		if(*it == ' ')
		{
			if(out == "")
				continue;
			else
				break;
		}
		if(*it == '*')
		{
			out.push_back(*it);
			break;
		}
		out.push_back(*it);
	}
}
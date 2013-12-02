#include "CLUserType.h"

CLUserType::CLUserType()
{
	this->type_len = 0;
}

CLUserType::~CLUserType()
{

}

void CLUserType::newVarDefinitionSentence(string &sentence)
{
	getNextItem(sentence,type_name,true);
	while((type_name.find("const",0)!=string::npos)||(type_name.find("static",0)!=string::npos)||(type_name.find("*",0)!=string::npos)||(type_name.find("unsigned",0)!=string::npos)||(type_name.find("signed",0)!=string::npos))
	{
		getNextItem(sentence,type_name,false);
	}	
}

void CLUserType::getNextItem(string &tmp,string &out,bool if_reset)
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
			else
			{
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

string CLUserType::writeDeserializer(){	return NULL;}

string CLUserType::writeSerialier(){	return NULL;}
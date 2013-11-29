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
	while((type_name.find("const")!=string::npos)||(type_name.find("static")!=string::npos)||(type_name.find("*")!=string::npos)||(type_name.find("unsigned")!=string::npos)(type_name.find("signed")!=string::npos))
	{
		getNextItem(sentence,type_name,false);
	}	
}

void CLUserType::getNextItem(string tmp,string &out,bool if_reset)
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
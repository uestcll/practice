#include "CLStringType.h"

CLStringType::CLStringType()
{

}

CLStringType::~CLStringType()
{

}

void CLStringType::analysisFromStatement(string & v_statement)
{
	string type;
	getNextItem(v_statement,type,true);
	while((type.find("const",0)!=string::npos)||(type.find("static",0)!=string::npos)||(type.find("*",0)!=string::npos)||(type.find("unsigned",0)!=string::npos)||(type.find("signed",0)!=string::npos))
	{
		getNextItem(v_statement,type,false);
	}

	getNextItem(v_statement,type,false);
	if(type == "*")
	{
		this->m_isPtr = true;
		getNextItem(v_statement,type,false);
		this->m_type_len =0x08;
	}
	else
	{
		this->m_type_len = 0x08;
	}

	this->m_var_name = type;

	getNextItem(v_statement,type,false);
	if(type.find("[")!=string::npos)
	{
		this->m_isArray = true;
		getNextItem(v_statement,type,false);
		this->m_arraySize = atoi(type.c_str());
	}
}
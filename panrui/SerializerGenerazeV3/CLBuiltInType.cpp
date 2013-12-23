#include "CLBuiltInType.h"

CLBuiltInType::CLBuiltInType()
{
	
}

CLBuiltInType::~CLBuiltInType()
{

}

void CLBuiltInType::analysisFromStatement(string  & v_statement)
{
	string type;

	getNextItem(v_statement,type,true);
	while((type.find("const",0)!=string::npos)||(type.find("static",0)!=string::npos)||(type.find("*",0)!=string::npos)||(type.find("unsigned",0)!=string::npos)||(type.find("signed",0)!=string::npos))
	{
		getNextItem(v_statement,type,false);
	}	

	if(type == "int"||type == "float"||type == "uin32_t")
	{
		this->m_type_len = 4;
	}
	else if(type == "short"||type == "uint16_t")
	{
		this->m_type_len = 2;
	}
	else if(type == "char"||type == "uint8_t")
	{
		this->m_type_len = 1;
	}
	else if(type == "long"||type == "double")
	{
		this->m_type_len = 8;
	}
	else
	{
		throw std::runtime_error("CLBasic:bad type");
	}

	getNextItem(v_statement,type,false);
	if(type == "*")
	{
		this->m_isPtr = true;
		getNextItem(v_statement,type,false);
		m_type_len = 0x08;
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
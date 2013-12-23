#include "CLUserDefType.h"

CLUserDefType::CLUserDefType()
{

}

CLUserDefType::~CLUserDefType()
{

}

void CLUserDefType::analysisFromStatement(string & v_statement)
{
	getNextItem(v_statement,this->m_userdef_name,true);
	while((m_userdef_name.find("const",0)!=string::npos)||(m_userdef_name.find("static",0)!=string::npos)||(m_userdef_name.find("*",0)!=string::npos)||(m_userdef_name.find("unsigned",0)!=string::npos)||(m_userdef_name.find("signed",0)!=string::npos))
	{
		getNextItem(v_statement,m_userdef_name,false);
	}	

	string type;
	getNextItem(v_statement,type,false);
	if(type == "*")
	{
		this->m_isPtr = true;
		getNextItem(v_statement,type,false);
		this->m_type_len =0x08;
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
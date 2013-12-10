#include "CLBasicType.h"
#include "CLMsgClassLoader.h"
#include "CLClassContentTemplate.h"
#include <stdexcept>

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
		throw std::runtime_error("CLBasic:bad type");

	getNextItem(sentence,type,false);
	if(type == "*")
	{
		this->m_is_ptr = true;
		getNextItem(sentence,type,false);
		type_len = 0x04;
	}
	this->m_value_name = type;

	getNextItem(sentence,type,false);
	if(type.find("[")!=string::npos)
	{
		this->m_is_array = true;
		getNextItem(sentence,type,false);
		this->m_array_len = atoi(type.c_str());
	}
}
void CLBasicType::writeDeserializer(memberFunctionContent * in,unsigned long  Base,string base_ptr )
{
	char m_off_char[32] = {0};
	sprintf(m_off_char,"%ld",this->m_off+Base);
	string m_off_str = m_off_char;
	
	if(this->m_is_ptr&&this->m_is_array)
	{
		string tmp;

		char type_len_char[32] = {0};
		sprintf(type_len_char,"%ld",this->m_array_len * this->type_len );
		string type_len_str = type_len_char;

		tmp = "(char *)"+base_ptr+"["+m_off_str+"] = new char["+type_len_str+"];";
		tmp += "\n\tmemcpy(((char *)"+base_ptr+")["+m_off_str+"],(char *)&m_cla_buf[m_buf_pos]," + type_len_str + ");";
		tmp += "\n\tm_buf_pos += 4;\n\t";

		in->insertSentence(tmp);
	}
	else if(this->m_is_array)
	{
		string tmp;

		char type_len_char[32] = {0};
		sprintf(type_len_char,"%ld",this->m_array_len * this->type_len );
		string type_len_str = type_len_char;

		tmp = "memcpy((char *)&"+base_ptr+"["+m_off_str+"],(char *)&m_cla_buf[m_buf_pos]," + type_len_str + ");";
		tmp += "\n\tm_buf_pos += "+type_len_str+";\n\t";

		in->insertSentence(tmp);
	}
	else if(this->m_is_ptr)
	{
		string tmp;

		tmp = "(char *)"+base_ptr+"["+m_off_str+"] = new char[strlen((char *)&m_cla_buf[m_buf_pos])+1];";
		tmp+= "\n\tstrcpy((char *)"+base_ptr+"["+m_off_str+"],(char *)&m_cla_buf[m_buf_pos]);";
		tmp+= "\n\tm_buf_pos += strlen((char *)&m_cla_buf[m_buf_pos])+1;\n\t";

		in->insertSentence(tmp);
	}
	else
		in->insertSentence(this->getDeserializerSentence(Base));
}

void CLBasicType::writeSerialier(memberFunctionContent * in,unsigned long  Base,string base_ptr )
{
	if(this->m_is_ptr&&this->m_is_array)
	{
		for(unsigned int i = 0;i<this->m_array_len;i++)
		{
			string tmp = getSerializerSentence(Base);
			tmp.erase(tmp.find_last_of("&"),1);
			
			string::size_type pos = tmp.find_first_of('=');
			pos+=2;
			tmp.erase(pos,1);

			pos = tmp.find(';');
			
			char   i_char[32] = {0};
			sprintf(i_char,"%d",i);
			string i_str = i_char;
			tmp.insert(pos,"["+i_str+"]");
			
			in->insertSentence(tmp);
		}		

	}
	else if(this->m_is_array)
	{
		char m_off_char[32] = {0};
		sprintf(m_off_char,"%ld",this->m_off+Base);
		string m_off_str = m_off_char;

		string tmp;

		char type_len_char[32] = {0};
		sprintf(type_len_char,"%ld",this->m_array_len * this->type_len );
		string type_len_str = type_len_char;

		tmp = "memcpy((char *)&m_cla_buf[m_buf_pos],(char *)&"+base_ptr+"["+m_off_str+"]," + type_len_str + ");";
		tmp += "\n\tm_buf_pos += "+type_len_str+";\n\t";

		in->insertSentence(tmp);
	}
	else if(this->m_is_ptr)
	{

		char m_off_char[32] = {0};
		sprintf(m_off_char,"%ld",this->m_off+Base);
		string m_off_str = m_off_char;

		string	tmp = "strcpy((char *)&m_cla_buf[m_buf_pos],(char *)"+base_ptr+"["+m_off_str+"]);";
		tmp += "\n\tm_buf_pos += "+ getValueLen()+";\n\t";

		in->insertSentence(tmp);
	}
	else
		in->insertSentence(this->getSerializerSentence(Base));
}

string CLBasicType::getDeserializerSentence(unsigned long  Base,string base_ptr)
{
	string type;
	if(type_len == 8)
		type = "long long";
	else if(type_len == 4)
		type = "int";
	else if(type_len == 2)
		type = "short";
	else
		type = "char";

	char m_off_char[32] = {0};
	sprintf(m_off_char,"%ld",this->m_off+Base);
	string m_off_str = m_off_char;

	char type_len_char[32] = {0};
	sprintf(type_len_char,"%ld",this->type_len);	
	string type_len_str =  type_len_char;

	return "*(("+type+" *)&"+base_ptr+"["+m_off_char+"]) = *(("+type+" *)&m_cla_buf[m_buf_pos]);\n\tm_buf_pos += "+type_len_str+";\n\t";
}

string CLBasicType::getSerializerSentence(unsigned long Base,string base_ptr)
{
	string type;
	if(type_len == 8)
		type = "long long";
	else if(type_len == 4)
		type = "int";
	else if(type_len == 2)
		type = "short";
	else
		type = "char";

	char m_off_char[32] = {0};
	sprintf(m_off_char,"%ld",this->m_off+Base);
	string m_off_str = m_off_char;
	
	return "*(("+type+" *)&m_cla_buf[m_buf_pos]) = *(("+type+" *)&"+base_ptr+"["+m_off_str+"]);"+"\n\tm_buf_pos += " + getValueLen() +";\n\t";
}

string CLBasicType::getValueLen(unsigned long Base,string base_ptr)
{

	char type_len_char[32] = {0};
	if(!m_is_array&&!m_is_ptr)
	{
		sprintf(type_len_char,"%ld",this->type_len);
		string type_len_str =  type_len_char;
		return type_len_str;	
	
	}
	else if(m_is_array)
	{
		sprintf(type_len_char,"%ld",this->type_len * m_array_len);
		string type_len_str =  type_len_char;
		return type_len_str;
	}
	else
	{
		char m_off_char[32] = {0};
		sprintf(m_off_char,"%ld",this->m_off);
		string m_off_str = m_off_char;
		string tmp;

		return "strlen((char *)"+base_ptr+"["+m_off_str+"])+1";
	}
}
#include "CLStringType.h"

CLStringType::CLStringType()
{
	this->type_len = 0x08;
}

CLStringType::~CLStringType()
{

}

void CLStringType::newVarDefinitionSentence(string &sentence)
{

}

string CLStringType::writeDeserializer(){	return NULL;}

string CLStringType::writeSerialier()
{
	char m_off_char[32] = {0};
	sprintf(m_off_char,"%ld",this->m_off);
	string m_off_str = m_off_char;

	return "memcpy(&m_cla_buf[m_buf_pos],((string *)&m_char_cla["+m_off_str+"])->c_str(),((string)&m_char_cla["+m_off_str+"]).length());";
}

string CLStringType::getValueLen()
{
	char m_off_char[32] = {0};
	sprintf(m_off_char,"%ld",this->m_off);
	string m_off_str = m_off_char;

	return "((string)&m_char_cla["+m_off_str+"]).length()";
}
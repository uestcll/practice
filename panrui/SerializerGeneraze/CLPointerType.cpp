#include "CLPointerType.h"
#include "CLMsgElementMap.h"
#include "CLUserType.h"

CLPointerType::CLPointerType()
{
	this->type_len = 4;
}

CLPointerType::~CLPointerType()
{

}

void CLPointerType::newVarDefinitionSentence(string &sentence)
{
	string tmp = sentence;
	while(tmp.find('*')!=string::npos)
		tmp.erase(tmp.find('*'),1);

	this->p_value = CLMsgElementMap::getInstance()->initNewElement(tmp);
	p_value->newVarDefinitionSentence(tmp);
}

string CLPointerType::writeDeserializer(){	return NULL;}

string CLPointerType::writeSerialier()
{
	if(typeid(*p_value)!=typeid(CLUserType))
	{
		p_value->setOff(this->m_off);
		string tmp = p_value->writeSerialier();
		tmp.erase(tmp.find_last_of("&"),1);
		return tmp;
	}
	else
	{
		return NULL;
	}
}

string CLPointerType::getValueLen()
{
	if(typeid(*p_value)!=typeid(CLUserType))
	{
		char m_off_char[32] = {0};
		sprintf(m_off_char,"%ld",this->m_off);
		string m_off_str = m_off_char;
	
		string tmp = this->p_value->getValueLen();
	
		if(tmp == "1")
			return "strlen((char *)m_char_cla["+m_off_str+"])";
		else if(tmp[0]<='9'&&tmp[0]>='0')
			return this->p_value->getValueLen();	
		else
			tmp.erase(tmp.find_last_of('&',0),1);
		return tmp;
	}
	else
	{
		return NULL;
	}
}



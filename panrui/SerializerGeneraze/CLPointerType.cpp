#include "CLPointerType.h"
#include "CLMsgElementMap.h"

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





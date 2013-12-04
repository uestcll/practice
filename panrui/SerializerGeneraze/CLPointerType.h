#ifndef CLPointerType_H
#define CLPointerType_H
#include "CLMsgElement.h"
class CLPointerType:public CLMsgElement
{
public:
	CLPointerType();
	virtual ~CLPointerType();
	virtual void newVarDefinitionSentence(string &sentence);
	virtual string writeSerialier();
	virtual string writeDeserializer();
	virtual string getValueLen();
private:
	CLMsgElement * p_value;
	
};

#endif
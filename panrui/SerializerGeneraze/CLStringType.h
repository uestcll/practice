#ifndef CLStringType_H
#define CLStringType_H
#include "CLMsgElement.h"
class CLStringType:public CLMsgElement
{
public:
	CLStringType();
	virtual ~CLStringType();
	virtual void newVarDefinitionSentence(string &sentence);
	virtual string writeSerialier();
	virtual string writeDeserializer();
private:

};

#endif
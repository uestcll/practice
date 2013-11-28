#ifndef CLBasicType_H
#define CLBasicType_H
#include "CLMsgElement.h"
class CLBasicType:public CLMsgElement
{
public:
	CLBasicType();
	virtual ~CLBasicType();
	virtual void newVarDefinitionSentence(string &sentence);
	virtual string writeSerialier();
	virtual string writeDeserializer();
private:
	int type_len;
};

#endif
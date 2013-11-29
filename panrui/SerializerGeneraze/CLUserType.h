#ifndef CLUserType_H
#define CLUserType_H
#include "CLMsgElement.h"
class CLUserType:public CLMsgElement
{
public:
	CLUserType();
	virtual ~CLUserType();
	virtual void newVarDefinitionSentence(string &sentence);
	virtual string writeSerialier();
	virtual string writeDeserializer();
private:
	int type_len;
};

#endif
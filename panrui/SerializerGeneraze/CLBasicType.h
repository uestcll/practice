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
	void getNextItem(string &tmp,string &out,bool if_reset);
};

#endif
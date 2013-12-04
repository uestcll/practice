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
	virtual string getValueLen();
private:
	void getNextItem(string &tmp,string &out,bool if_reset);
	string type_name;
};

#endif
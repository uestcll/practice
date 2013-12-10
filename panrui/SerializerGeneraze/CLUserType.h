#ifndef CLUserType_H
#define CLUserType_H
#include "CLMsgElement.h"

class CLMsgClassManager;

class CLUserType:public CLMsgElement
{
public:
	CLUserType(CLMsgClassManager * pmng);
	virtual ~CLUserType();
	virtual void newVarDefinitionSentence(string &sentence);
	virtual void writeSerialier(memberFunctionContent * in,unsigned long  Base = 0,string base_ptr = "m_char_cla");
	virtual void writeDeserializer(memberFunctionContent * in,unsigned long  Base = 0,string base_ptr = "m_char_cla");
	virtual string getSerializerSentence(unsigned long  Base = 0,string base_ptr = "m_char_cla");
	virtual string getDeserializerSentence(unsigned long  Base = 0,string base_ptr = "m_char_cla");
	virtual string getValueLen(unsigned long Base = 0,string base_ptr = "m_char_cla");
	string getTypeName(){ return type_name;} 
private:
	string type_name;
	CLMsgClassManager * m_pmng;
};

#endif
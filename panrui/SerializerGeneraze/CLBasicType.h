#ifndef CLBasicType_H
#define CLBasicType_H
#include "CLMsgElement.h"



class CLBasicType:public CLMsgElement
{
public:
	CLBasicType();
	virtual ~CLBasicType();
	virtual void newVarDefinitionSentence(string &sentence);
	virtual void writeSerialier(memberFunctionContent * in,unsigned long  Base = 0,string base_ptr = "m_char_cla");
	virtual void writeDeserializer(memberFunctionContent * in,unsigned long  Base = 0,string base_ptr = "m_char_cla");
	virtual string getSerializerSentence(unsigned long  Base = 0,string base_ptr = "m_char_cla");
	virtual string getDeserializerSentence(unsigned long  Base = 0,string base_ptr = "m_char_cla");
	virtual string getValueLen(unsigned long Base = 0,string base_ptr = "m_char_cla");
private:
};

#endif
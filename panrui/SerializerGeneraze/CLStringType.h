#ifndef CLStringType_H
#define CLStringType_H
#include "CLMsgElement.h"



class CLStringType:public CLMsgElement
{
public:
	CLStringType();
	virtual ~CLStringType();
	virtual void newVarDefinitionSentence(string &sentence);
	virtual void writeSerialier(memberFunctionContent * in,unsigned long  Base = 0,string base_ptr = "m_char_cla");
	virtual void writeDeserializer(memberFunctionContent * in,unsigned long  Base = 0,string base_ptr = "m_char_cla");
	virtual string getSerializerSentence(unsigned long  Base = 0,string base_ptr = "m_char_cla");
	virtual string getDeserializerSentence(unsigned long  Base = 0,string base_ptr = "m_char_cla");
	virtual string getValueLen(unsigned long Base = 0,string base_ptr = "m_char_cla");
private:

};

#endif
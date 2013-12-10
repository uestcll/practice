#ifndef CLMsgElement_H
#define CLMsgElement_H
#include <string>

#define USER_DEF		true
#define NON_USER_DEF	false

using namespace std;

struct memberFunctionContent;
class CLMsgElement
{
public:
	CLMsgElement();
	virtual ~CLMsgElement();
	virtual void newVarDefinitionSentence(string &sentence) = 0;
	virtual void writeSerialier(memberFunctionContent * in,unsigned long  Base = 0,string base_ptr = "m_char_cla") = 0;
	virtual void writeDeserializer(memberFunctionContent * in,unsigned long  Base = 0,string base_ptr = "m_char_cla") = 0;
	virtual string getSerializerSentence(unsigned long  Base = 0,string base_ptr = "m_char_cla") = 0;
	virtual string getDeserializerSentence(unsigned long  Base = 0,string base_ptr = "m_char_cla") = 0;
	virtual string getValueLen(unsigned long Base = 0,string base_ptr = "m_char_cla") = 0;

	const unsigned long & getOff(){ return m_off;	}
	int	 getTypeLen(){	return type_len; }
	void setOff(unsigned long & off){ m_off = off;	}
	bool getPtrFlag(){	return m_is_ptr;}
	bool getArrFlag(){	return m_is_array;}
	unsigned int getArrLen(){	return m_array_len;}

protected:
	
	int type_len;
	string	 m_value_name;
	bool  m_is_ptr;
	bool  m_is_array;
	unsigned int  m_array_len;
	unsigned long m_off;

	void getNextItem(string &tmp,string &out,bool if_reset);
	string getNewName();

private:
	CLMsgElement(const CLMsgElement &);
	const CLMsgElement & operator = (const CLMsgElement &);
};

#endif
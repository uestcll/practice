#ifndef CLMsgElement_H
#define CLMsgElement_H
#include <string>

#define USER_DEF		true
#define NON_USER_DEF	false

using namespace std;

class CLMsgElement
{
public:
	CLMsgElement();
	virtual ~CLMsgElement();
	virtual void newVarDefinitionSentence(string &sentence) = 0;
	virtual string writeSerialier() = 0;
	virtual string writeDeserializer() = 0;
	virtual string getValueLen() = 0;

	const unsigned long & getOff(){ return m_off;	}
	int	 getTypeLen(){	return type_len; }
	void setOff(unsigned long & off){ m_off = off;	}

protected:
	int type_len;
	unsigned long m_off;
private:
	CLMsgElement(const CLMsgElement &);
	const CLMsgElement & operator = (const CLMsgElement &);
};

#endif
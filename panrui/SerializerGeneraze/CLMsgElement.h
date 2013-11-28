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
	bool type;
protected:
private:
	CLMsgElement(const CLMsgElement &);
	const CLMsgElement & operator = (const CLMsgElement &);
};

#endif
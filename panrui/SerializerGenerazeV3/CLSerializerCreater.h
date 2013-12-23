#ifndef CLSerializerCreater_H
#define CLSerializerCreater_H

#include <string>
#include <map>

using namespace std;

class CLClassTemplate;
class CLClassContentTemplate;
class CLClassDescribe;
class CLAbstractMethod;

class CLSerializerCreater
{
public:

	CLSerializerCreater();
	~CLSerializerCreater();

	void run(CLClassDescribe *,map< string , CLAbstractMethod *> *);
	
private:

	CLSerializerCreater(const CLSerializerCreater &);
	const CLSerializerCreater & operator = (const CLSerializerCreater &);

private:

	void initIncludingFile();
	void initNamespace();
	void initMemberFunction();
	void initMemberVar();
	void completeGetBuffer();
	void completeConAndDecon();
	void completeSerialInfo();
	void completeCountBufSize();

	CLClassTemplate * cla;
	CLClassContentTemplate * cla_content;

	CLClassDescribe * m_claInfo;

	map< string , CLAbstractMethod *> * m_map;
};


#endif
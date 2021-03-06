#ifndef CLDeserializerCreater_H
#define CLDeserializerCreater_H

#include <string>
#include <map>

using namespace std;

class CLClassTemplate;
class CLClassContentTemplate;
class CLClassDescribe;
class CLAbstractMethod;

class CLDeserializerCreater
{
public:
	
	CLDeserializerCreater();
	~CLDeserializerCreater();

	void run(CLClassDescribe *,map< string , CLAbstractMethod *> *);

private:

	CLDeserializerCreater(const CLDeserializerCreater &);
	const CLDeserializerCreater & operator = (const CLDeserializerCreater &);

private:

	void initIncludingFile();
	void initNamespace();
	void initMemberFunction();
	void initMemberVar();
	void completeConAndDecon();
	void completePaddingObj();
	void completeGetNewObject();
	void completeAllocateObj();

	CLClassTemplate * cla;
	CLClassContentTemplate * cla_content;

	CLClassDescribe * m_claInfo;

	map< string , CLAbstractMethod *> * m_map;


};

#endif
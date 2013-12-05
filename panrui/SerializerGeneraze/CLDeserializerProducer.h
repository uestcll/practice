#ifndef CLDeserializerProducer_H
#define CLDeserializerProducer_H



#include <string>
using namespace std;


class CLMsgClassManager;
class CLMsgClass;
class CLClassTemplate;
class CLClassContentTemplate;
struct offset;

class CLDeserializerProducer
{
public:
	CLDeserializerProducer(CLMsgClassManager * classMng,string & serial);
	void buildDeserializer();
private:
	CLDeserializerProducer(const CLDeserializerProducer &);
	const CLDeserializerProducer & operator = (const CLDeserializerProducer &);
	
	void initIncludingFile();
	void initNamespace();
	void initMemberFunction();
	void initMemberVar();
	void completePaddingObj();
	void completeGetNewObject();
	void completeAllocateObj();
	void completeConAndDecon();

	CLMsgClassManager * m_classMng;
	CLMsgClass	* m_serialClass;
	string		  className;
	CLClassTemplate * cla;
	CLClassContentTemplate * cla_content;
	unsigned	  unit_size;

	static const string m_cla;
	static const string m_char_cla;
	static const string m_cla_buf;
	static const string m_buf_pos;
};

#endif
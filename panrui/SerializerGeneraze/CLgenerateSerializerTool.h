#ifndef CLgenerateSerializerTool_H
#define CLgenerateSerializerTool_H
#define _WINDOWS_PROC_
//#define _LINUX_PROC_
#include <string>

#include "CLMsgClassManager.h"
#include "CLDeserializerProducer.h"
#include "CLSerializerProducer.h"

class CLgenerateSerializerTool
{
public:
	CLgenerateSerializerTool(string workspace);
	~CLgenerateSerializerTool();

	void startInitSerializerAndDeserializer();
private:

	void getFileList();
	void initCLMsgClass();
	void initCLCompleteInfo();
	void initSerializer();
	void initDeserializer();
	
	CLgenerateSerializerTool(const CLgenerateSerializerTool &);
	const CLgenerateSerializerTool & operator = (const CLgenerateSerializerTool &);

	string *m_filelist;
	int		strNum;
	string	m_workspace;

	CLMsgClassManager	   *m_msgClassMng;
	CLSerializerProducer   *m_serializerProducer;
	CLDeserializerProducer *m_deserializerProducer;
};

#endif
#ifndef CLgenerateSerializerTool_H
#define CLgenerateSerializerTool_H
#define _WINDOWS_PROC_
//#define _LINUX_PROC_
#include <string>

#include "CLMsgClassManager.h"

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
	string	originPath;

	CLMsgClassManager	   *m_msgClassMng;
};

#endif
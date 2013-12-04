#include "CLgenerateSerializerTool.h"
#include "CLDeserializerProducer.h"
#include "CLSerializerProducer.h"
#ifdef _WINDOWS_PROC_
#include <Windows.h>
#endif

#ifdef _LINUX_PROC_
#include <dirent.h>
#endif

using namespace std;
CLgenerateSerializerTool::CLgenerateSerializerTool(string workspace):m_workspace(workspace),
m_msgClassMng(NULL),strNum(0)
{
	
	if(m_workspace == "")
#ifdef _WINDOWS_PROC_
		m_workspace = ".\\";
		originPath = m_workspace;
		m_workspace += "*.h";

#endif
#ifdef _LINUX_PROC_
		m_workspace = "./";


#endif

}

CLgenerateSerializerTool::~CLgenerateSerializerTool()
{
	if(m_filelist!=NULL)
		delete []m_filelist;
	if(m_msgClassMng!=NULL)
		delete m_msgClassMng;
}

void CLgenerateSerializerTool::startInitSerializerAndDeserializer()
{
	getFileList();

	initCLMsgClass();
	initCLCompleteInfo();
	initSerializer();
	initDeserializer();
}

void CLgenerateSerializerTool::getFileList()
{
#ifdef _WINDOWS_PROC_
	WIN32_FIND_DATA fdFileData;
	HANDLE hFind;

	hFind = FindFirstFile(m_workspace.c_str(),&fdFileData);
	if(hFind == INVALID_HANDLE_VALUE )
	{
		strNum = 0;
		return;
	}
	else do{
	strNum++;
	}while(FindNextFile(hFind,&fdFileData)!= 0);

	m_filelist = new string[strNum];
	for(int i = 0;i<strNum;i++)
		m_filelist[i] = originPath;
	strNum = 0;

	hFind = FindFirstFile(m_workspace.c_str(),&fdFileData);
	if(hFind == INVALID_HANDLE_VALUE )
	{
		strNum = 0;
		return;
	}else do{
		m_filelist[strNum] += fdFileData.cFileName;
		m_filelist[strNum];
		strNum++;
	}while(FindNextFile(hFind,&fdFileData)!= 0);

#endif

#ifdef _LINUX_PROC_
	struct dirent **namelist;
	strNum = scandir(m_workspace.c_str(),&namelist,0,alphasort);

	m_filelist = new string[strNum];	

	for(int i = 2;i<strNum;i++)
	{
		m_filelist[i] = namelist[i].d_name;
		free(namelist[i]);
	}

	free(namelist);
	strNum-=2;
#endif
}
void CLgenerateSerializerTool::initCLMsgClass()
{
	m_msgClassMng = new CLMsgClassManager();
	m_msgClassMng->loadAlltheFile(m_filelist,strNum);
}
void CLgenerateSerializerTool::initCLCompleteInfo()
{
	

}
void CLgenerateSerializerTool::initDeserializer()
{
}
void CLgenerateSerializerTool::initSerializer()
{
	list<string>::iterator it = m_msgClassMng->serialingNameMapBegin();
	CLSerializerProducer * newSerializer;
	while(it != m_msgClassMng->serialingNameMapEnd())
	{
		newSerializer = new CLSerializerProducer(m_msgClassMng,*it);
		newSerializer->buildSerializer();
		delete newSerializer;
		it++;
	}
}
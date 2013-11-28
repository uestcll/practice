#include "CLgenerateSerializerTool.h"
#ifdef _WINDOWS_PROC_
#include <Windows.h>
#endif

#ifdef _LINUX_PROC_
#include <dirent.h>
#endif

using namespace std;
CLgenerateSerializerTool::CLgenerateSerializerTool(string workspace):m_workspace(workspace),
m_msgClassMng(NULL),m_serializerProducer(NULL),m_deserializerProducer(NULL),strNum(0)
{
	if(m_workspace == "")
#ifdef _WINDOWS_PROC_
		m_workspace = ".";
		m_workspace += "\\*.*";
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
	if(m_serializerProducer!=NULL)
		delete m_serializerProducer;
	if(m_serializerProducer!=NULL)
		delete m_deserializerProducer;
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

	m_filelist = new string[strNum-2];
	strNum = 0;

	hFind = FindFirstFile(m_workspace.c_str(),&fdFileData);
	FindNextFile(hFind,&fdFileData);
	FindNextFile(hFind,&fdFileData);
	if(hFind == INVALID_HANDLE_VALUE )
	{
		strNum = 0;
		return;
	}else do{
		m_filelist[strNum] = fdFileData.cFileName;
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
void CLgenerateSerializerTool::initDeserializer(){}
void CLgenerateSerializerTool::initSerializer(){}
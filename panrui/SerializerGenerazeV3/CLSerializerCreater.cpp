#include "CLSerializerCreater.h"
#include "CLClassContentTemplate.h"
#include "CLClassTemplate.h"
#include "CLClassDescribe.h"

#include "CLAbstractType.h"
#include "CLAbstractMethod.h"
#include "CLSerializerAndDeserializerCreater.h"

#include "CLUserDefType.h"

CLSerializerCreater::CLSerializerCreater():cla(NULL),cla_content(NULL)
{

}

CLSerializerCreater::~CLSerializerCreater()
{

}

void CLSerializerCreater::run(CLClassDescribe * v_claInfo,map< string , CLAbstractMethod *> * v_map)
{
	m_claInfo = v_claInfo;
	m_map = v_map;

	cla = new CLClassTemplate(v_claInfo->m_classname + "serializer",true);
	cla_content = new CLClassContentTemplate(cla);

	initIncludingFile();
	initNamespace();
	initMemberFunction();
	initMemberVar();

	completeConAndDecon();
	completeGetBuffer();
	completeCountBufSize();
	completeSerialInfo();

	cla->writeToFile();
	cla_content->writeCPPtoDisk();

	delete cla;
	delete cla_content;
}

void CLSerializerCreater::initIncludingFile()
{
	string includingFileInHeader = "#include <iostream>\n#include <string>\n#include <vector>\n#include <map>\n#include <list>\n";
	cla->addIncludingFile(includingFileInHeader);

	string includingFileInCPP = "#include \""+m_claInfo->m_classname+".h\"\n" + "#include \""+m_claInfo->m_classname + "serializer"+".h\"\n";
	cla_content->addHeader(includingFileInCPP);
}

void CLSerializerCreater::initNamespace()
{
	string namespaceStr = "using namespace std;\n";
	cla->addNameSpace(namespaceStr);
	string classDec = "class "+m_claInfo->m_classname+";";
	cla->addNameSpace(classDec);
}

void CLSerializerCreater::initMemberFunction()
{
	cla->addItem("public","",m_claInfo->m_classname + "serializer","const "+m_claInfo->m_classname+ " * in");
	cla->addItem("public","","virtual ~"+m_claInfo->m_classname + "serializer","");
	cla->addItem("public","char *","getBuffer","int * buf_size");
	cla->addItem("public","char *","serialInfo","char * in,char * out");
	cla->addItem("public","int","countBufSize","char * in");
}

void CLSerializerCreater::initMemberVar()
{
	cla->addItem("private","const " + m_claInfo->m_classname + " * ","m_cla");
}

void CLSerializerCreater::completeConAndDecon()
{
	memberFunctionContent * fc = cla_content->addNewFunction(m_claInfo->m_classname + "serializer");	
	fc->insertSentence("\n");
	fc->insertSentence("m_cla = in");

	memberFunctionContent * fdc = cla_content->addNewFunction("virtual ~"+m_claInfo->m_classname + "serializer");
	fdc->insertSentence("\n");
}

void CLSerializerCreater::completeCountBufSize()
{
	memberFunctionContent * fg = cla_content->addNewFunction("countBufSize");	
	list<CLAbstractType *>::iterator ite = m_claInfo->m_elementList.begin();

	fg->insertSentence("\n\tint bufsize = 0;");


	string str_size = "";
	_Longlong num_size = 0;

	while(ite != m_claInfo->m_elementList.end() )
	{
		str_size = m_map->find(typeid(**ite).name())->second->getSize((*ite));

		if(str_size[0] <= '9'&&str_size[0] >= '9')
		{
			num_size += atoi(str_size.c_str());
		}
		else
		{
			if(num_size != 0)
			{
				string out = to_string(num_size);
				fg->insertSentence("bufsize += "+out+";");
			}

			if(typeid(**ite) == typeid(CLUserDefType))
			{
				fg->insertSentence(str_size);
			}
			else
			{
				fg->insertSentence("bufsize += "+str_size+";");
			}
		}
		ite++;
	}

	if(num_size != 0)
	{
		string out = to_string(num_size);
		fg->insertSentence("bufsize += "+out+";");		
	}
}

void CLSerializerCreater::completeGetBuffer()
{
	memberFunctionContent * fb = cla_content->addNewFunction("getBuffer");	
	fb->insertSentence("\n");

	fb->insertSentence("*buf_size = countBufSize((char *)m_cla)");
	fb->insertSentence("char * buf = new char[*buf_size];\n");

	fb->insertSentence("return serialInfo((char *)m_cla,buf)");
}

void CLSerializerCreater::completeSerialInfo()
{
	memberFunctionContent * fs = cla_content->addNewFunction("serialInfo");	
	fs->insertSentence("\n");
	fs->insertSentence("int m_buf_pos = 0;");

	list<CLAbstractType *>::iterator ite = m_claInfo->m_elementList.begin();

	while(ite != m_claInfo->m_elementList.end() )
	{
		fs->insertSentence(m_map->find(typeid(**ite).name())->second->getSerialMethod((*ite)) + "\n");	
		
		if(typeid(**ite) == typeid(CLUserDefType))
		{
			cla_content->addHeader("#include \"" + ((CLUserDefType *)(*ite))->getUserDefName() + "serializer.h\"\n");
		}
		
		ite++;
	}

	fs->insertSentence("return out;\n");
}


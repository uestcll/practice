#include "CLSerializerProducer.h"
#include "CLMsgClass.h"
#include "CLMsgClassManager.h"

#include "CLClassContentTemplate.h"
#include "CLClassTemplate.h"

#include "CLMsgElement.h"

#include <memory>


const string CLSerializerProducer::m_cla = "m_cla";
const string CLSerializerProducer::m_char_cla = "m_char_cla";
const string CLSerializerProducer::m_cla_buf = "m_cla_buf";
const string CLSerializerProducer::m_buf_pos = "m_buf_pos";
const string CLSerializerProducer::m_buf_len = "m_buf_len";


CLSerializerProducer::CLSerializerProducer(CLMsgClassManager * classMng,string& serial):
m_classMng(classMng),className(serial),cla(NULL),cla_content(NULL)
{
	m_serialClass = m_classMng->findClass(serial);
}

void CLSerializerProducer::buildSerializer()
{
	cla = new CLClassTemplate(className+"serializer",true);
	cla_content = new CLClassContentTemplate(cla);
	initIncludingFile();
	initNamespace();
	initMemberFunction();
	initMemberVar();

	m_serialClass->setOffset();

	completeConAndDecon();
	completeGetBuffer();
	completeAllocateBuffer();
	completeConAndDecon();

	cla->writeToFile();
	cla_content->writeCPPtoDisk();
}

void CLSerializerProducer::initIncludingFile()
{
	string includingFileInHeader = "#include <iostream>\n#include <string>\n#include <vector>\n#include <map>\n#include <list>\n";
	cla->addIncludingFile(includingFileInHeader);

	string includingFileInCPP = "#include \""+className+".h\"\n" + "#include \""+className + "serializer"+".h\"\n";
	cla_content->addIncludingFile(includingFileInCPP);
	
}

void CLSerializerProducer::initNamespace()
{
	string namespaceStr = "using namespace std;\n";
	cla->addNameSpace(namespaceStr);
	string classDec = "class "+className+";";
	cla->addNameSpace(classDec);
}

void CLSerializerProducer::initMemberFunction()
{
	cla->addItem("public","",className + "serializer","const "+className+ " * in");
	cla->addItem("public","","~"+className + "serializer","");
	cla->addItem("public","char *","getBuffer","int * buf_size");
	cla->addItem("private","void","serialInfo","");
	cla->addItem("private","void","allocatBuf","");
}

void CLSerializerProducer::initMemberVar()
{
	cla->addItem("private","const "+className + " * ",m_cla);
	cla->addItem("private","char * ",m_cla_buf);
	cla->addItem("private","char * ",m_char_cla);
	cla->addItem("private","unsigned long ",m_buf_pos);
	cla->addItem("private","unsigned long ",m_buf_len);
}

void CLSerializerProducer::completeConAndDecon()
{
	memberFunctionContent * fc = cla_content->addNewFunction(className + "serializer");
	fc->insertSentence("m_cla = in;");
	fc->insertSentence("m_cla_buf = NULL;");
	fc->insertSentence("m_buf_pos = 0;");
	fc->insertSentence("m_buf_len = 0;");
	fc->insertSentence("m_char_cla = (char *)m_cla");

	memberFunctionContent * fdc = cla_content->addNewFunction("~"+className + "serializer");
	fdc->insertSentence("if( m_cla_buf != NULL)");
	fdc->insertSentence("	delete [] (m_cla_buf);");
}

void CLSerializerProducer::completeGetBuffer()
{
	memberFunctionContent * fg = cla_content->addNewFunction("getBuffer");
	fg->insertSentence("allocateBuf();");
	fg->insertSentence("buf_size = m_buf_len;");
	fg->insertSentence("serialInfo();");
	fg->insertSentence("return m_cla_buf;");
}

void CLSerializerProducer::completeAllocateBuffer()
{
	memberFunctionContent * fa = cla_content->addNewFunction("allocatBuf");
	list<shared_ptr<CLMsgElement> >::iterator  it = m_serialClass->beginVar();
	string tmp;
	int	   cur_size = 0;
	
	
	while(it != m_serialClass->endVar())
	{
		tmp = (it->get())->getValueLen();
		if(tmp[0]<='9'&&tmp[0]>='0')
			cur_size += std::atoi(tmp.c_str());
		else
		{
			if(cur_size != 0)
			{
				char size_char[32] = {0};
				sprintf(size_char,"%d",cur_size);
				string size_str = size_char;
				fa->insertSentence("m_buf_len += "+size_str);
				cur_size = 0;
			}
			fa->insertSentence("m_buf_len += "+tmp+";");
		}

	}
	if(cur_size != 0)
	{
		char size_char[32] = {0};
		sprintf(size_char,"%d",cur_size);
		string size_str = size_char;
		fa->insertSentence("m_buf_len += "+size_str+";");
	}
}

void CLSerializerProducer::completeSerialInfo()
{
	list<shared_ptr<CLMsgElement> >::iterator  it = m_serialClass->beginVar();
	memberFunctionContent * fs = cla_content->addNewFunction("serialInfo");
	while(it != m_serialClass->endVar())
	{
		fs->insertSentence((it->get())->writeSerialier());
		fs->insertSentence("m_buf_pos += "+(it->get())->getValueLen()+";");

	}
}
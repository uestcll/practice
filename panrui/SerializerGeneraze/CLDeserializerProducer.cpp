#include "CLDeserializerProducer.h"
#include "CLMsgClass.h"
#include "CLMsgClassManager.h"

#include "CLClassContentTemplate.h"
#include "CLClassTemplate.h"

#include "CLMsgElement.h"

#include <memory>


const string CLDeserializerProducer::m_cla = "m_cla";
const string CLDeserializerProducer::m_char_cla = "m_char_cla";
const string CLDeserializerProducer::m_cla_buf = "m_cla_buf";
const string CLDeserializerProducer::m_buf_pos = "m_buf_pos";
const string CLDeserializerProducer::m_buf_len = "m_buf_len";


CLDeserializerProducer::CLDeserializerProducer(CLMsgClassManager * classMng,string& serial):
m_classMng(classMng),className(serial),cla(NULL),cla_content(NULL)
{
	m_serialClass = m_classMng->findClass(serial);
}

void CLDeserializerProducer::buildSerializer()
{
	cla = new CLClassTemplate(className+"deserializer",true);
	cla_content = new CLClassContentTemplate(cla);
	initIncludingFile();
	initNamespace();
	initMemberFunction();
	initMemberVar();

	m_serialClass->setOffset();

	completeConAndDecon();
	completeGetBuffer();
	completeAllocateBuffer();
	completeSerialInfo();

	cla->writeToFile();
	cla_content->writeCPPtoDisk();
}

void CLDeserializerProducer::initIncludingFile()
{
	string includingFileInHeader = "#include <iostream>\n#include <string>\n#include <vector>\n#include <map>\n#include <list>\n";
	cla->addIncludingFile(includingFileInHeader);

	string includingFileInCPP = "#include \""+className+".h\"\n" + "#include \""+className + "deserializer"+".h\"\n";
	cla_content->addIncludingFile(includingFileInCPP);
	
}

void CLDeserializerProducer::initNamespace()
{
	string namespaceStr = "using namespace std;\n";
	cla->addNameSpace(namespaceStr);
	string classDec = "class "+className+";";
	cla->addNameSpace(classDec);
}

void CLDeserializerProducer::initMemberFunction()
{
	cla->addItem("public","",className + "deserializer","const "+className+ " * in");
	cla->addItem("public","","~"+className + "deserializer","");
	cla->addItem("public","char *","getBuffer","int * buf_size");
	cla->addItem("private","void","deserialInfo","");
	cla->addItem("private","void","allocatBuf","");
}

void CLDeserializerProducer::initMemberVar()
{
	cla->addItem("private","const "+className + " * ",m_cla);
	cla->addItem("private","char * ",m_cla_buf);
	cla->addItem("private","char * ",m_char_cla);
	cla->addItem("private","unsigned long ",m_buf_pos);
	cla->addItem("private","unsigned long ",m_buf_len);
}

void CLDeserializerProducer::completeConAndDecon()
{
	memberFunctionContent * fc = cla_content->addNewFunction(className + "deserializer");
	fc->insertSentence("m_cla = in;");
	fc->insertSentence("m_cla_buf = NULL;");
	fc->insertSentence("m_buf_pos = 0;");
	fc->insertSentence("m_buf_len = 0;");
	fc->insertSentence("m_char_cla = (char *)m_cla");

	memberFunctionContent * fdc = cla_content->addNewFunction("~"+className + "deserializer");
	fdc->insertSentence("if( m_cla_buf != NULL)");
	fdc->insertSentence("	delete [] (m_cla_buf);");
}

void CLDeserializerProducer::completeGetBuffer()
{
	memberFunctionContent * fg = cla_content->addNewFunction("getBuffer");
	fg->insertSentence("allocateBuf();");
	fg->insertSentence("buf_size = m_buf_len;");
	fg->insertSentence("deserialInfo();");
	fg->insertSentence("return m_cla_buf;");
}

void CLDeserializerProducer::completeAllocateBuffer()
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
				fa->insertSentence("m_buf_len += "+size_str+";");
				cur_size = 0;
			}
			fa->insertSentence("m_buf_len += "+tmp+";");
		}
		it++;
	}
	if(cur_size != 0)
	{
		char size_char[32] = {0};
		sprintf(size_char,"%d",cur_size);
		string size_str = size_char;
		fa->insertSentence("m_buf_len += "+size_str+";");
	}
}

void CLDeserializerProducer::completeSerialInfo()
{
	list<shared_ptr<CLMsgElement> >::iterator  it = m_serialClass->beginVar();
	memberFunctionContent * fs = cla_content->addNewFunction("deserialInfo");
	while(it != m_serialClass->endVar())
	{
		fs->insertSentence((it->get())->writeDeserializer());
		fs->insertSentence("m_buf_pos += "+(it->get())->getValueLen()+";");
		it++;

	}
}
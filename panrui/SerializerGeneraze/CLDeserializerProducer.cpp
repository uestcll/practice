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


CLDeserializerProducer::CLDeserializerProducer(CLMsgClassManager * classMng,string& serial):
m_classMng(classMng),className(serial),cla(NULL),cla_content(NULL)
{
	m_serialClass = m_classMng->findClass(serial);
}

void CLDeserializerProducer::buildDeserializer()
{
	cla = new CLClassTemplate(className+"deserializer",true);
	cla_content = new CLClassContentTemplate(cla);
	initIncludingFile();
	initNamespace();
	initMemberFunction();
	initMemberVar();

	m_serialClass->setOffset();

	completeConAndDecon();
	completeGetNewObject();
	completeAllocateObj();
	completePaddingObj();

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
	cla->addItem("public","",className + "deserializer","char * buf");
	cla->addItem("public","","~"+className + "deserializer","");
	cla->addItem("public",className+" *","getNewObject","");
	cla->addItem("private","void","paddingObj","");
	cla->addItem("private","void","allocateObj","");
}

void CLDeserializerProducer::initMemberVar()
{
	cla->addItem("private",className + " * ",m_cla);
	cla->addItem("private","char * ",m_cla_buf);
	cla->addItem("private","char * ",m_char_cla);
	cla->addItem("private","unsigned long ",m_buf_pos);

}

void CLDeserializerProducer::completeConAndDecon()
{
	memberFunctionContent * fc = cla_content->addNewFunction(className + "deserializer");
	fc->insertSentence("m_cla_buf = buf;");
	fc->insertSentence("m_buf_pos = 0;");

	memberFunctionContent * fdc = cla_content->addNewFunction("~"+className + "deserializer");
}

void CLDeserializerProducer::completeGetNewObject()
{
	memberFunctionContent * fg = cla_content->addNewFunction("getNewObject");
	fg->insertSentence("allocateObj();");
	fg->insertSentence("paddingObj();");
	fg->insertSentence("return m_cla;");
}

void CLDeserializerProducer::completeAllocateObj()
{
	memberFunctionContent * fa = cla_content->addNewFunction("allocateObj");
	list<shared_ptr<CLMsgElement> >::iterator  it = m_serialClass->beginVar();
	fa->insertSentence("m_cla = new" + className+";");
	fa->insertSentence("m_char_cla = (char *)m_cla;");
}

void CLDeserializerProducer::completePaddingObj()
{
	list<shared_ptr<CLMsgElement> >::iterator  it = m_serialClass->beginVar();
	memberFunctionContent * fs = cla_content->addNewFunction("paddingObj");
	while(it != m_serialClass->endVar())
	{
		(it->get())->writeDeserializer(fs);
		it++;
	}
}
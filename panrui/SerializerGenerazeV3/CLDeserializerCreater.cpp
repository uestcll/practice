#include "CLDeserializerCreater.h"
#include "CLClassContentTemplate.h"
#include "CLClassTemplate.h"
#include "CLClassDescribe.h"

#include "CLAbstractType.h"
#include "CLAbstractMethod.h"
#include "CLSerializerAndDeserializerCreater.h"

#include "CLUserDefType.h"

CLDeserializerCreater::CLDeserializerCreater():cla(NULL),cla_content(NULL),m_claInfo(NULL),m_map(NULL)
{

}

CLDeserializerCreater::~CLDeserializerCreater()
{

}

void CLDeserializerCreater::run(CLClassDescribe * v_claInfo,map< string , CLAbstractMethod *> * v_map)
{
	m_claInfo = v_claInfo;
	m_map = v_map;

	cla = new CLClassTemplate(v_claInfo->m_classname + "deserializer",true);
	cla_content = new CLClassContentTemplate(cla);

	initIncludingFile();
	initNamespace();
	initMemberFunction();
	initMemberVar();

	completeConAndDecon();
	completeGetNewObject();
	completeAllocateObj();
	completePaddingObj();

	cla->writeToFile();
	cla_content->writeCPPtoDisk();

	delete cla;
	delete cla_content;
}

void CLDeserializerCreater::initIncludingFile()
{
	string includingFileInHeader = "#include <iostream>\n#include <string>\n#include <vector>\n#include <map>\n#include <list>\n";
	cla->addIncludingFile(includingFileInHeader);

	string includingFileInCPP = "#include \""+m_claInfo->m_classname+".h\"\n" + "#include \""+m_claInfo->m_classname + "serializer"+".h\"\n";
	cla_content->addHeader(includingFileInCPP);
}

void CLDeserializerCreater::initNamespace()
{
	string namespaceStr = "using namespace std;\n";
	cla->addNameSpace(namespaceStr);
	string classDec = "class "+m_claInfo->m_classname+";";
	cla->addNameSpace(classDec);
}

void CLDeserializerCreater::initMemberFunction()
{
	cla->addItem("public","",m_claInfo->m_classname + "deserializer","char * buf");
	cla->addItem("public","","virtual ~" + m_claInfo->m_classname + "deserializer","");
	cla->addItem("public",m_claInfo->m_classname+" * ","getNewObject","char * buf");
	cla->addItem("private","char *","paddingObj","char * in,char * out");
	cla->addItem("private",m_claInfo->m_classname +" * ","allocateObj","");	
}

void CLDeserializerCreater::initMemberVar()
{
	cla->addItem("private","const char * ","buf");
}

void CLDeserializerCreater::completeConAndDecon()
{
	memberFunctionContent * fc = cla_content->addNewFunction(m_claInfo->m_classname + "serializer");	
	fc->insertSentence("\n");
	fc->insertSentence("this->buf = buf;");

	memberFunctionContent * fdc = cla_content->addNewFunction("virtual ~"+m_claInfo->m_classname + "serializer");
	fdc->insertSentence("\n");	
}

void CLDeserializerCreater::completeGetNewObject()
{
	memberFunctionContent * fg = cla_content->addNewFunction("getNewObject");
	fg->insertSentence("\n");
	fg->insertSentence(m_claInfo->m_classname +" * pObj = allocateObj()");
	fg->insertSentence("char * pstrObj = pObj");
	fg->insertSentence("return ("+m_claInfo->m_classname+" * )paddingObj(buf,pstrObj)");
}

void CLDeserializerCreater::completeAllocateObj()
{
	memberFunctionContent * fa = cla_content->addNewFunction("allocateObj");
	fa->insertSentence("\n");

	fa->insertSentence("return (char *)new "+m_claInfo->m_classname+";");
}

void CLDeserializerCreater::completePaddingObj()
{
	memberFunctionContent * fp = cla_content->addNewFunction("paddingObj");
	fp->insertSentence("\n");

	fp->insertSentence("int m_buf_pos = 0;");
	list<CLAbstractType *>::iterator ite = m_claInfo->m_elementList.begin();
	while(ite != m_claInfo->m_elementList.end() )
	{
		fp->insertSentence(m_map->find(m_claInfo->m_classname)->second->getDeserialMethod((*ite)) + "\n");	
		
		if(typeid(*ite) == typeid(CLUserDefType))
		{
			cla_content->addHeader("#include <" + ((CLUserDefType *)(*ite))->getUserDefName() + ".h>\n");
		}
		
		ite++;	
	}

	fp->insertSentence("return out;\n");
}

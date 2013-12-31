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
	string includingFileInHeader = "#include <iostream>\n#include <string.h>\n#include <string>\n#include <vector>\n#include <map>\n#include <list>\n";
	cla->addIncludingFile(includingFileInHeader);

	string includingFileInCPP = "#include \""+m_claInfo->m_classname+".h\"\n" + "#include \""+m_claInfo->m_classname + "deserializer"+".h\"\n";
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
	cla->addItem("public","",m_claInfo->m_classname + "deserializer","");
	cla->addItem("public","virtual ","~" + m_claInfo->m_classname + "deserializer","");
	cla->addItem("public",m_claInfo->m_classname+" * ","getNewObject","char * buf");
	cla->addItem("public","char *","paddingObj","char * in,char * out");
	cla->addItem("private",m_claInfo->m_classname +" * ","allocateObj","");	
}

void CLDeserializerCreater::initMemberVar()
{

}

void CLDeserializerCreater::completeConAndDecon()
{
	memberFunctionContent * fc = cla_content->addNewFunction(m_claInfo->m_classname + "deserializer");	
	fc->insertSentence("\n");

	memberFunctionContent * fdc = cla_content->addNewFunction("~"+m_claInfo->m_classname + "deserializer");
	fdc->insertSentence("\n");	
}

void CLDeserializerCreater::completeGetNewObject()
{
	memberFunctionContent * fg = cla_content->addNewFunction("getNewObject");
	fg->insertSentence("\n");
	fg->insertSentence(m_claInfo->m_classname +" * pObj = allocateObj();");
	fg->insertSentence("char * pstrObj = (char *)pObj;");
	fg->insertSentence("return ("+m_claInfo->m_classname+" * )paddingObj(buf,pstrObj);");
}

void CLDeserializerCreater::completeAllocateObj()
{
	memberFunctionContent * fa = cla_content->addNewFunction("allocateObj");
	fa->insertSentence("\n");

	fa->insertSentence("return new "+m_claInfo->m_classname+";");
}

void CLDeserializerCreater::completePaddingObj()
{
	memberFunctionContent * fp = cla_content->addNewFunction("paddingObj");
	fp->insertSentence("\n");

	fp->insertSentence("int m_buf_pos = 0;");
	list<CLAbstractType *>::iterator ite = m_claInfo->m_elementList.begin();
	while(ite != m_claInfo->m_elementList.end() )
	{
		fp->insertSentence(m_map->find(typeid(**ite).name())->second->getDeserialMethod((*ite)) + "\n");	
		
		if(typeid(**ite) == typeid(CLUserDefType))
		{
			cla_content->addHeader("#include \"" + ((CLUserDefType *)(*ite))->getUserDefName() + ".h\"\n");
			cla_content->addHeader("#include \"" + ((CLUserDefType *)(*ite))->getUserDefName() + "deserializer.h\"\n");
		}
		
		ite++;	
	}

	fp->insertSentence("return out;\n");
}

#include "CLClassContentTemplate.h"
#include "CLClassTemplate.h"

memberFunctionContent::memberFunctionContent(string typeName,string className,string functionName,string paraName):
typeName(typeName),className(className),functionName(functionName),paraName(paraName),content("")
{

}

void memberFunctionContent::insertSentence(string sentence)
{
	content.push_back('\t');
	content+= sentence;
	content.push_back('\n');
}

ofstream& operator <<(ofstream & ostr,memberFunctionContent & cur_fc)
{
	ostr<<cur_fc.typeName<<" "<<cur_fc.className<<"::"<<cur_fc.functionName<<"("<<cur_fc.paraName<<")"<<endl;
	ostr<<"{"<<cur_fc.content<<"}"<<endl;
	return ostr;
}

memberVarStatic::memberVarStatic(string typeName,string className,string VariableName,string value = "0"):
typeName(typeName),className(className),VariableName(VariableName),value(value)
{

}

ofstream& operator <<(ofstream & ostr,memberVarStatic & cur_vs)
{
	ostr<<cur_vs.typeName<<'\t'<<cur_vs.className<<"::"<<cur_vs.VariableName<<" = "<<cur_vs.value<<";"<<endl;
	return ostr;
}

CLClassContentTemplate::CLClassContentTemplate(CLClassTemplate * classHeader):
m_classHeader(classHeader)
{

}

CLClassContentTemplate::~CLClassContentTemplate()
{

}

void CLClassContentTemplate::writeCPPtoDisk()
{
	string add = "./";
	add += m_classHeader->className;
	add += ".cpp";
	ofstream fd(add.c_str(),ios::trunc);
	fd<<*this;
	fd.close();
}

memberFunctionContent * CLClassContentTemplate::addNewFunction(string functionName)
{
	memberFunction * mf = m_classHeader->findFunc(functionName);
	if(mf == NULL)
	{
		return NULL;
	}
	func_l.push_back(memberFunctionContent(mf->typeName,m_classHeader->className,mf->functionName,mf->paraName));
	list<memberFunctionContent>::iterator it = func_l.end();
	it--;
	return &(*it);
}

memberVarStatic * CLClassContentTemplate::addNewVarStatic(string varName)
{
	memberVariable * mv = m_classHeader->findVar(varName);
	if(mv == NULL)
		return NULL;
	var_l.push_back(memberVarStatic(mv->typeName,m_classHeader->className,mv->VariableName));
	list<memberVarStatic>::iterator it = var_l.end();
	it--;
	return &(*it);

}

ofstream& operator <<(ofstream & ostr,CLClassContentTemplate & cur_tc)
{
	if(cur_tc.IncludingFile != "")
		ostr<<cur_tc.IncludingFile<<endl;
	list<memberVarStatic>::iterator itv = cur_tc.var_l.begin();
	while(itv != cur_tc.var_l.end())
		ostr<<*itv++;

	list<memberFunctionContent>::iterator itf = cur_tc.func_l.begin();
	while(itf != cur_tc.func_l.end())
		ostr<<*itf++;
	return ostr;
}



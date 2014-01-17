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
	if(cur_fc.typeName.find("virtual") != string::npos)
	{
		ostr<< cur_fc.typeName.substr(7);
	}
	else
		ostr<<cur_fc.typeName;
	
	ostr<<" "<<cur_fc.className<<"::"<<cur_fc.functionName<<"(";
	
	if(cur_fc.paraName.find("=") != string::npos)
	{
		string::size_type equalpos;
		string::size_type compos;
		while((equalpos= cur_fc.paraName.find("=")) != string::npos)
		{
			compos = cur_fc.paraName.find_first_of(",",equalpos);
			cur_fc.paraName.erase(equalpos,compos);
		}
		ostr<<cur_fc.paraName<<")"<<endl;
	}
	else
		ostr<<cur_fc.paraName<<")"<<endl;
	
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
	string add = ".\\";
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
	if(cur_tc.m_header != "")
		ostr<<cur_tc.m_header<<endl;

	if(cur_tc.m_addition != "")
		ostr<<cur_tc.m_addition<<endl;

	list<memberVarStatic>::iterator itv = cur_tc.var_l.begin();
	while(itv != cur_tc.var_l.end())
		ostr<<*itv++;

	list<memberFunctionContent>::iterator itf = cur_tc.func_l.begin();
	while(itf != cur_tc.func_l.end())
		ostr<<*itf++;
	return ostr;
}

void CLClassContentTemplate::addHeader(string & v_include)
{
	m_header+=v_include;
	m_header.push_back('\n');
}

void CLClassContentTemplate::addAddtion(string & v_addition)
{
	m_addition += v_addition;
	m_addition.push_back('\n');
}



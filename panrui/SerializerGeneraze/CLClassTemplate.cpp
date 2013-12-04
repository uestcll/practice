#include "CLClassTemplate.h"

memberFunction::memberFunction(string typeName,string functionName,string paraName):typeName(typeName),functionName(functionName),paraName(paraName)
{

}

ofstream & operator <<(ofstream& ostr,memberFunction& cur_f)
{
	if(cur_f.typeName!= "")
	ostr<<'\t'<<cur_f.typeName<<' '<<cur_f.functionName<<'('<<cur_f.paraName<<')'<<';'<<endl;
	else
	ostr<<'\t'<<' '<<cur_f.functionName<<'('<<cur_f.paraName<<')'<<';'<<endl;
	return ostr;
}


memberVariable::memberVariable(string typeName,string VariableName):typeName(typeName),VariableName(VariableName)
{

}

ofstream & operator <<(ofstream& ostr,memberVariable& cur_v)
{
	ostr<<'\t'<<cur_v.typeName<<'\t'<<cur_v.VariableName<<';'<<endl;
	return ostr;
}

CLClassTemplate::CLClassTemplate(string className,bool isNoConstructer = false):className(className)
{
	if(!isNoConstructer)
	{
	this->private_f.push_back(memberFunction("",className,"const "+className+'&'));
	this->private_f.push_back(memberFunction("const "+className+"& ","operator = ","const "+className+"&"));

	}
}

void CLClassTemplate::addItem(string access,string typeName,string functionName,string paraName)
{
	if(typeName == "non")
		typeName = "";

	if(access == "public")
		this->public_f.push_back(memberFunction(typeName,functionName,paraName));
	else if(access == "protected")
		this->protected_f.push_back(memberFunction(typeName,functionName,paraName));
	else if(access == "private")
		this->private_f.push_back(memberFunction(typeName,functionName,paraName));
	else
	return;
}

void CLClassTemplate::addItem(string access,string typeName,string VariableName)
{

	if(access == "public")
		this->public_v.push_back(memberVariable(typeName,VariableName));
	else if(access == "protected")
		this->protected_v.push_back(memberVariable(typeName,VariableName));
	else if(access == "private")
		this->private_v.push_back(memberVariable(typeName,VariableName));
	else
	return;
}

void CLClassTemplate::addItem(string superclassName)
{
	relations.push_back(superclassName);
}
string CLClassTemplate::initDef(string & in)
{
	string tmp = in;
	for(unsigned int i = 0;i<tmp.size();i++)
	{
		if(tmp[i]>='a'&&tmp[i]<='z')
		{
			tmp[i] += ('A'-'a');	
		}
		else
		{
			tmp = tmp.insert(i,"_");
			i++;
		}

	}
	tmp += "_";
	return tmp;
}

void CLClassTemplate::writeSingleTeamTofile(ofstream &ostr,vector<memberFunction> & cur_f,vector<memberVariable> & cur_v,string teamName)
{
	vector<memberFunction>::iterator it_f = cur_f.begin();
    vector<memberVariable>::iterator it_v = cur_v.begin();
	ostr<<teamName<<":"<<endl;
	while(it_f != cur_f.end())
	{
		ostr<<'\t' ;
		ostr<< (*it_f);
		it_f++;
	}
	ostr<<endl<<endl;
	while(it_v != cur_v.end())
	{
		ostr<<'\t';
		ostr<<(*it_v);
		it_v++;
	}
}
ofstream & operator <<(ofstream &ostr,CLClassTemplate & cur_c)
{
	string def = cur_c.initDef(cur_c.className);
	ostr<<"#ifndef "<<def<<endl<<"#define "<<def<<endl<<endl;
	if(cur_c.beforeClass != "");
		ostr<<cur_c.beforeClass<<endl;

	ostr<<endl<<endl<<cur_c.className;
	if(cur_c.relations.size() != 0)
	{
		vector<string>::iterator it = cur_c.relations.begin();
		ostr<<*it++;
		while(it != cur_c.relations.end())
			ostr<<","<<*it++;
		
	}
	ostr<<endl<<'{'<<endl;
	cur_c.writeSingleTeamTofile(ostr,cur_c.private_f,cur_c.private_v,"private");
	cur_c.writeSingleTeamTofile(ostr,cur_c.protected_f,cur_c.protected_v,"protected");
	cur_c.writeSingleTeamTofile(ostr,cur_c.public_f,cur_c.public_v,"public");
	ostr<<endl<<"};"<<endl;
	ostr<<"#endif"<<endl;
	
	return ostr;
}

ostream & operator <<(ostream &ostr,CLClassTemplate & cur_c) 
{
	ostr<<"className : "<<cur_c.className<<endl;

	vector<memberFunction>::iterator it;
	
	it = cur_c.public_f.begin();
	while(it != cur_c.public_f.end())
	{
		ostr<<"public:"<<it->typeName<<"\t"<<it->functionName<<"\t"<<it->paraName<<endl;
		it++;
	}

	it = cur_c.protected_f.begin();
	while(it != cur_c.protected_f.end())
	{
		ostr<<"protected:"<<it->typeName<<"\t"<<it->functionName<<"\t"<<it->paraName<<endl;
		it++;
	}

	it = cur_c.private_f.begin();
	while(it != cur_c.private_f.end())
	{
		ostr<<"private:"<<it->typeName<<"\t"<<it->functionName<<"\t"<<it->paraName<<endl;
		it++;
	}

	vector<memberVariable>::iterator itv;
	itv = cur_c.public_v.begin();
	while(itv != cur_c.public_v.end())
	{
		ostr<<"public:"<<itv->typeName<<"\t"<<itv->VariableName<<endl;
		itv++;
	}

	itv = cur_c.protected_v.begin();
	while(itv != cur_c.protected_v.end())
	{
		ostr<<"protected:"<<itv->typeName<<"\t"<<itv->VariableName<<endl;
		itv++;
	}

	itv = cur_c.private_v.begin();
	while(itv != cur_c.private_v.end())
	{
		ostr<<"private:"<<itv->typeName<<"\t"<<itv->VariableName<<endl;
		itv++;
	}

	return ostr;
}

void CLClassTemplate::writeToFile()
{
	string add = "./";
	add+= className;
	add+= ".h";
	ofstream fd(add.c_str(),ios::trunc);
	fd<<*this;
	fd.close();
}
CLClassTemplate::~CLClassTemplate()
{

}

memberFunction * CLClassTemplate::findFunc(string funcName)
{
	vector<memberFunction>::iterator itpub = public_f.begin();
	vector<memberFunction>::iterator itpri = private_f.begin();
	vector<memberFunction>::iterator itpro = protected_f.begin();
	while(itpub != public_f.end())
		if(funcName == itpub->functionName)
			return &(*itpub);
		else itpub++;
	while(itpri != private_f.end())
		if(funcName == itpri->functionName)
			return &(*itpri);
		else itpri++;
	while(itpro != protected_f.end())
		if(funcName == itpri->functionName)
			return &(*itpro);
		else itpro++;
	return NULL;
}

memberVariable * CLClassTemplate::findVar(string varName)
{
	vector<memberVariable>::iterator itpub = public_v.begin();
	vector<memberVariable>::iterator itpri = private_v.begin();
	vector<memberVariable>::iterator itpro = protected_v.begin();
	while(itpub != public_v.end())
		if(varName == itpub->VariableName)
			return &(*itpub);
		else itpub++;
	while(itpri != private_v.end())
		if(varName == itpri->VariableName)
			return &(*itpri);
		else itpri++;
	while(itpro != protected_v.end())
		if(varName == itpri->VariableName)
			return &(*itpro);
		else itpro++;
	return NULL;
}

void CLClassTemplate::addIncludingFile(string & i_file)
{
	beforeClass+=i_file;
	beforeClass.push_back('\n');
}

void CLClassTemplate::addNameSpace(string & i_namespace )
{
	beforeClass+=i_namespace;
	beforeClass.push_back('\n');
}
#include "ClassTemplate.h"

memberFunction::memberFunction(string typeName,string functionName,string paraName):typeName(typeName),functionName(functionName),paraName(paraName)
{

}

ofstream & operator <<(ofstream& ostr,memberFunction& cur_f)
{
	ostr<<'\t'<<cur_f.typeName<<' '<<cur_f.functionName<<'('<<cur_f.paraName<<')'<<';'<<endl;
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

ClassTemplate::ClassTemplate(string className,bool isNoConstructer = false):className(className)
{
	if(!isNoConstructer)
	{
	this->private_f.push_back(memberFunction("",className,"const "+className+'&'));
	this->private_f.push_back(memberFunction("const "+className+"& ","operator = ","const "+className+"&"));

	}
}

void ClassTemplate::addItem(string access,string typeName,string functionName,string paraName)
{
	if(access == "public")
		this->public_f.push_back(memberFunction(typeName,functionName,paraName));
	else if(access == "protected")
		this->protected_f.push_back(memberFunction(typeName,functionName,paraName));
	else if(access == "private")
		this->private_f.push_back(memberFunction(typeName,functionName,paraName));
	else
	return;
}

void ClassTemplate::addItem(string access,string typeName,string VariableName)
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
string ClassTemplate::initDef(string & in)
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

void ClassTemplate::writeSingleTeamTofile(ofstream &ostr,vector<memberFunction> & cur_f,vector<memberVariable> & cur_v,string teamName)
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
ofstream & operator <<(ofstream &ostr,ClassTemplate & cur_c)
{
	string def = cur_c.initDef(cur_c.className);
	ostr<<"#ifndef "<<def<<endl<<"#define "<<def<<endl<<endl;
	ostr<<endl<<endl<<cur_c.className<<endl<<'{'<<endl;
	cur_c.writeSingleTeamTofile(ostr,cur_c.private_f,cur_c.private_v,"private");
	cur_c.writeSingleTeamTofile(ostr,cur_c.protected_f,cur_c.protected_v,"protected");
	cur_c.writeSingleTeamTofile(ostr,cur_c.public_f,cur_c.public_v,"public");
	ostr<<endl<<"};"<<endl;
	ostr<<"#endif"<<endl;
	
	return ostr;
}

void ClassTemplate::writeToFile()
{
	string add = "./";
	add+= className;
	add+= ".h";
	ofstream fd(add.c_str(),ios::trunc);
	fd<<*this;
	fd.close();
}
ClassTemplate::~ClassTemplate()
{

}

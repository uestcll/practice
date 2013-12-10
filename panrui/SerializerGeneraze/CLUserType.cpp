#include "CLUserType.h"
#include "CLMsgClassManager.h"
#include "CLMsgClass.h"

#include <memory>
#include "CLClassContentTemplate.h"

CLUserType::CLUserType(CLMsgClassManager * pmng):m_pmng(pmng)
{
	this->type_len = 0;
}

CLUserType::~CLUserType()
{

}

void CLUserType::newVarDefinitionSentence(string &sentence)
{
	getNextItem(sentence,type_name,true);
	while((type_name.find("const",0)!=string::npos)||(type_name.find("static",0)!=string::npos)||(type_name.find("*",0)!=string::npos)||(type_name.find("unsigned",0)!=string::npos)||(type_name.find("signed",0)!=string::npos))
	{
		getNextItem(sentence,type_name,false);
	}	

	string type;
	getNextItem(sentence,type,false);
	if(type == "*")
	{
		this->m_is_ptr = true;
		getNextItem(sentence,type,false);
	}
	this->m_value_name = type;

	getNextItem(sentence,type,false);
	if(type.find("[")!=string::npos)
	{
		this->m_is_array = true;
		getNextItem(sentence,type,false);
		this->m_array_len = atoi(type.c_str());
	}
}

void CLUserType::writeDeserializer(memberFunctionContent * in,unsigned long  Base,string base_ptr )
{
	if(this->m_is_ptr&&this->m_is_array)
	{
	}
	else if(this->m_is_array)
	{
	
	}
	else if(this->m_is_ptr)
	{
		CLMsgClass * t_class = m_pmng->findClass(this->type_name);
		list<shared_ptr<CLMsgElement> >::iterator  it = t_class->beginVar();

		char m_off_char[32] = {0};
		sprintf(m_off_char,"%ld",this->m_off);
		string m_off_str = m_off_char;
		string new_base = getNewName();

		in->insertSentence("("+this->type_name + " *)&"+base_ptr+"["+ m_off_str +"] = new "+this->type_name+";");
		in->insertSentence("char * "+new_base+" = &"+base_ptr+"["+ m_off_str +"];\n\t");


		while(it != t_class->endVar())
		{
			it->get()->writeDeserializer(in,0,new_base);
			it++;
		}		
		
	}
	else
	{
		in->insertSentence(this->getDeserializerSentence(0,base_ptr));
	}
}

void CLUserType::writeSerialier(memberFunctionContent * in,unsigned long  Base,string base_ptr )
{
	if(this->m_is_ptr&&this->m_is_array)
	{
	}
	else if(this->m_is_array)
	{
		
	}
	else if(this->m_is_ptr)
	{
		CLMsgClass * t_class = m_pmng->findClass(this->type_name);
		list<shared_ptr<CLMsgElement> >::iterator  it = t_class->beginVar();

		char m_off_char[32] = {0};
		sprintf(m_off_char,"%ld",this->m_off);
		string m_off_str = m_off_char;
		string new_base = getNewName();

		in->insertSentence("char * "+new_base+" = (char *)"+base_ptr+"["+m_off_str+"];\n\t");
		while(it != t_class->endVar())
		{
			it->get()->writeSerialier(in,0,new_base);
			it++;
		}

	}
	else
	{
		in->insertSentence(this->getSerializerSentence(0,base_ptr));
	}
}

string CLUserType::getDeserializerSentence(unsigned long  Base,string base_ptr)
{
	CLMsgClass * t_class = m_pmng->findClass(this->type_name);
	list<shared_ptr<CLMsgElement> >::iterator  it = t_class->beginVar();

	char m_off_char[32] = {0};
	sprintf(m_off_char,"%ld",this->m_off);
	string m_off_str = m_off_char;		
	string new_base = getNewName();

	string phrase = "char *"+new_base+" = (char *)&"+base_ptr+"["+m_off_str+"]";

	while(it != t_class->endVar())
	{
		phrase += it->get()->getDeserializerSentence(0,new_base)+"\n\t";
		it++;
	}
	return phrase;
}

string CLUserType::getSerializerSentence(unsigned long Base,string base_ptr)
{
	char m_off_char[32] = {0};
	sprintf(m_off_char,"%ld",this->m_off);
	string m_off_str = m_off_char;		
	string new_base = getNewName();

	string phrase = "char *"+new_base+" = (char *)&"+base_ptr+"["+m_off_str+"]";
	CLMsgClass * t_class = m_pmng->findClass(this->type_name);
	list<shared_ptr<CLMsgElement> >::iterator  it = t_class->beginVar();


	while(it != t_class->endVar())
	{
		phrase += it->get()->getSerializerSentence(0,new_base)+"\n\t";
		it++;
	}
	return phrase;
}

string CLUserType::getValueLen(unsigned long Base,string base_ptr)
{
	CLMsgClass * t_class = m_pmng->findClass(this->type_name);
	list<shared_ptr<CLMsgElement> >::iterator  it = t_class->beginVar();

	unsigned long numCounting = 0;
	string phraseCounting = "";
	string tmp;


	while(it != t_class->endVar())
	{
		tmp = it->get()->getValueLen();
		if(tmp[0]<='9'&&tmp[0]>='0')
			numCounting+= atoi(tmp.c_str());
		else
			phraseCounting+= tmp+";\n\t";
		it++;
	}

	if(numCounting != 0)
	{
		char num_char[32] = {0};
		sprintf(num_char,"%d",numCounting);
		string size_str = num_char;
		phraseCounting += "m_buf_len += "+size_str+";\n\t";
	}

	return phraseCounting;
}
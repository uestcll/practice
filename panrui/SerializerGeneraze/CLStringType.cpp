#include "CLStringType.h"
#include "CLClassContentTemplate.h"

CLStringType::CLStringType()
{
	this->type_len = 0x08;
}

CLStringType::~CLStringType()
{

}

void CLStringType::newVarDefinitionSentence(string &sentence)
{
	string type;
	getNextItem(sentence,type,true);
	while((type.find("const",0)!=string::npos)||(type.find("static",0)!=string::npos)||(type.find("*",0)!=string::npos)||(type.find("unsigned",0)!=string::npos)||(type.find("signed",0)!=string::npos))
	{
		getNextItem(sentence,type,false);
	}

	getNextItem(sentence,type,false);
	if(type == "*")
	{
		this->m_is_ptr = true;
		getNextItem(sentence,type,false);
		type_len =0x04;
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

void CLStringType::writeDeserializer(memberFunctionContent * in,unsigned long  Base,string base_ptr )
{
	if(this->m_is_ptr&&this->m_is_array)
	{
		char m_off_char[32] = {0};
		sprintf(m_off_char,"%ld",this->m_off+Base);
		string m_off_str = m_off_char;	

		char arr_len_char[32] = {0};
		sprintf(arr_len_char,"%ld",this->m_array_len);
		string arr_len_str = arr_len_char;
		
		string tmp = "(string *)"+base_ptr+"["+m_off_str+"] = new string["+arr_len_str+"];\n\t";
	
		in->insertSentence(tmp);
		for(unsigned int i = 0;i<this->m_array_len;i++)
		{
			string tmp_b = this->getDeserializerSentence(Base,base_ptr);
			tmp_b.erase(0,1);
			string::size_type pos = 0;
			while(pos = tmp_b.find("&"+base_ptr+"",pos)!= string::npos)
			{
				tmp.erase(pos,1);
			}

			char   i_char[32] = {0};
			sprintf(i_char,"%d",i);
			string i_str = i_char;

			pos = 0;
			while((pos = tmp.find_first_of("->",pos))!= string::npos)
			{
				tmp.erase(pos,2);
				tmp.insert(pos,"["+i_str+"].");

			}

			in->insertSentence(tmp_b);
		}


	}
	else if(this->m_is_array)
	{
		unsigned long origin_off = this->m_off;
		for(int i = 0;i<this->m_array_len;i++)
		{
			m_off += this->type_len;
			in->insertSentence(this->getDeserializerSentence(Base,base_ptr));
		}

		this->m_off = origin_off;	
	}
	else if(this->m_is_ptr)
	{
		char m_off_char[32] = {0};
		sprintf(m_off_char,"%ld",this->m_off+Base);
		string m_off_str = m_off_char;	

		string tmp = "(string *)"+base_ptr+"["+m_off_str+"] = new string;\n\t";
		tmp += getDeserializerSentence(Base,base_ptr);
		
		string::size_type pos = 0;
		while((pos = tmp.find("&"+base_ptr,pos))!= string::npos)
		{
			tmp.erase(pos,1);
		}

		in->insertSentence(tmp);

	}
	else
		in->insertSentence(this->getDeserializerSentence(Base,base_ptr));
}

void CLStringType::writeSerialier(memberFunctionContent * in,unsigned long  Base,string base_ptr )
{
	if(this->m_is_ptr&&this->m_is_array)
	{
		for(unsigned int i = 0;i<this->m_array_len;i++)
		{
			string tmp = getSerializerSentence(Base,base_ptr);
			string::size_type pos = 0;
			while((pos = tmp.find("&"+base_ptr,pos))!= string::npos)
			{
				tmp.erase(pos,1);
			}

			char   i_char[32] = {0};
			sprintf(i_char,"%d",i);
			string i_str = i_char;
			
			in->insertSentence(tmp);
		}			

	}
	else if(this->m_is_array)
	{
		unsigned long origin_off = this->m_off;
		for(int i = 0;i<this->m_array_len;i++)
		{
			m_off += this->type_len;
			in->insertSentence(this->getSerializerSentence(Base,base_ptr));
		}

		this->m_off = origin_off;		
	}
	else if(this->m_is_ptr)
	{
		string tmp = getSerializerSentence(Base,base_ptr);
		string::size_type pos = 0;
		while((pos = tmp.find("&"+base_ptr,pos))!= string::npos)
		{
			tmp.erase(pos,1);
		}

		in->insertSentence(tmp);
		
	}
	else
		in->insertSentence(this->getSerializerSentence(Base,base_ptr));
}

string CLStringType::getDeserializerSentence(unsigned long  Base,string base_ptr)
{
	char m_off_char[32] = {0};
	sprintf(m_off_char,"%ld",this->m_off + Base);
	string m_off_str = m_off_char;

	return "*((string *)&"+base_ptr+"["+m_off_str+"]) = (char *)&m_cla_buf[m_buf_pos];\n\tm_buf_pos += ((string *)&"+base_ptr+"["+m_off_str+"])->length() + 1;\n\t";
}

string CLStringType::getSerializerSentence(unsigned long Base,string base_ptr)
{
	char m_off_char[32] = {0};
	sprintf(m_off_char,"%ld",this->m_off + Base);
	string m_off_str = m_off_char;

	return "memcpy(&m_cla_buf[m_buf_pos],((string *)&"+base_ptr+"["+m_off_str+"])->c_str(),((string *)&"+base_ptr+"["+m_off_str+"])->length());"+"\n\tm_buf_pos += " + getValueLen() +";\n\t";;
}
string CLStringType::getValueLen(unsigned long Base,string base_ptr)
{
	char m_off_char[32] = {0};
	sprintf(m_off_char,"%ld",this->m_off + Base);
	string m_off_str = m_off_char;

	return "((string *)&"+base_ptr+"["+m_off_str+"])->length() + 1";
}
#include "CLPointerType.h"
#include "CLMsgElementMap.h"
#include "CLUserType.h"

CLPointerType::CLPointerType()
{
	this->type_len = 4;
}

CLPointerType::~CLPointerType()
{

}

void CLPointerType::newVarDefinitionSentence(string &sentence)
{
	string tmp = sentence;
	while(tmp.find('*')!=string::npos)
		tmp.erase(tmp.find('*'),1);

	this->p_value = CLMsgElementMap::getInstance()->initNewElement(tmp);
	p_value->newVarDefinitionSentence(tmp);
}

string CLPointerType::writeDeserializer()
{
	if(typeid(*p_value)!=typeid(CLUserType))
	{
		char m_off_char[32] = {0};
		sprintf(m_off_char,"%ld",this->m_off);
		string m_off_str = m_off_char;
		string tmp;


		
		if(this->p_value->getTypeLen() == 1)
		{
			tmp = "(char *)m_char_cla["+m_off_str+"] = new char[strlen((char *)&m_cla_buf[m_buf_pos])+1];";
			tmp+= "\n\tstrcpy((char *)m_char_cla["+m_off_str+"],(char *)&m_cla_buf[m_buf_pos]);";
			tmp+= "\n\tm_buf_pos += strlen((char *)&m_cla_buf[m_buf_pos])+1;";
		}
		else
		{
			this->p_value->setOff(this->m_off);
			tmp = p_value->writeDeserializer();
		
			tmp.erase(tmp.find_first_of("&"),1);

			string TypeName = typeid(*p_value).name();
			if(TypeName == "class CLBasicType")
			{
				if(p_value->getTypeLen() == 2)
					TypeName = "short";
				else if(p_value->getTypeLen() == 4)
					TypeName = "int";
				else 
					TypeName = "long";
			}
			else
			{
				TypeName.erase(0,8);
				string::iterator it = TypeName.end();
				it-=4;
				TypeName.erase(it,TypeName.end());
				if(TypeName[0]>='A'&&TypeName[0]<='Z')
					TypeName[0]+='a'-'A';
			}

			tmp.insert(0,"("+TypeName+"*)m_char_cla["+m_off_str+"] = new "+TypeName+";\n\t");
		}

		return tmp;
	}
	else
	{
	
	}

}

string CLPointerType::writeSerialier()
{
	if(typeid(*p_value)!=typeid(CLUserType))
	{
		p_value->setOff(this->m_off);
		string tmp = p_value->writeSerialier();
		tmp.erase(tmp.find_last_of("&"),1);
		return tmp;
	}
	else
	{

		return NULL;
	}
}

string CLPointerType::getValueLen()
{
	if(typeid(*p_value)!=typeid(CLUserType))
	{
		char m_off_char[32] = {0};
		sprintf(m_off_char,"%ld",this->m_off);
		string m_off_str = m_off_char;
	
		string tmp = this->p_value->getValueLen();
	
		if(tmp == "1")
			return "strlen((char *)m_char_cla["+m_off_str+"])";
		else if(tmp[0]<='9'&&tmp[0]>='0')
			return this->p_value->getValueLen();	
		else
		{
			tmp.erase(tmp.find_last_of("&"),1);
		}
		return tmp;
	}
	else
	{
		return NULL;
	}
}



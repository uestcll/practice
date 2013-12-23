#include "CLClassInterpreter.h"
#include "CLClassDescribe.h"

#include "CLAbstractType.h"

#include "CLBuiltInType.h"
#include "CLStringType.h"
#include "CLUserDefType.h"

#include <string>
using namespace std;

CLClassInterpreter::CLClassInterpreter():m_classDescribe(NULL)
{

}

CLClassInterpreter::~CLClassInterpreter()
{

}

CLClassDescribe * CLClassInterpreter::loadClassByFilename(string & v_filepath)
{
	m_istr.open(v_filepath.c_str(),ios::binary);

	while(m_istr.peek() != EOF)
	{
		if(getClassEntryAndAllocateClassDescribe())
		{
			completeClassDescribeFromContent();
		}
	}

	m_istr.close();
	return m_classDescribe;
}

void CLClassInterpreter::getNextObj(string & ret)
{
		ret = "";
		char tmp;

		while(tmp = m_istr.get())
			if(tmp == ' '||tmp =='\n'||tmp == 0x0d)
			{
				if(ret == "")
				continue;
				else
				break;
			}
			else if((tmp<='9'&&tmp>='0')||(tmp<='z'&&tmp>='a')||(tmp<='Z'&&tmp>='A')||tmp =='_')
			{
				ret.push_back(tmp);
				continue;
			}
			else if(ret != "")
			{
				m_istr.seekg(-1,ios::cur);
				break;
			}
			else
			{
				ret.push_back(tmp);
				
				if(tmp == ':')
				{
					tmp = m_istr.get();
					
					if(tmp == ':')
					{
						ret.push_back(tmp);
					}
					else
						m_istr.seekg(-1,ios::cur);
				}
				break;
			}
		
}

bool CLClassInterpreter::getClassEntryAndAllocateClassDescribe()
{
		string tmp;
		getNextObj(tmp);

		while((tmp!=STRUCT_FLAG&&tmp!=CLASS_FLAG)&&tmp!= SERIAL_FLAG&&m_istr.peek() != EOF)
		{	
			if(tmp == "define")
				getNextObj(tmp);

			getNextObj(tmp);
		}

		m_classDescribe = new CLClassDescribe;

		if(m_istr.peek() == EOF)
		{
			delete m_classDescribe;
			return false;
		}
		
		if(tmp == SERIAL_FLAG)
		{
			getNextObj(tmp);
			m_classDescribe->m_featrueSet.insert(SERIAL_FEATURE);
		}

		if(tmp ==STRUCT_FLAG)
		{
			m_classDescribe->m_featrueSet.insert(STRUCT_FEATURE);
		}

		getNextObj(m_classDescribe->m_classname);

		getNextObj(tmp);
		if(tmp == ";")
		{
			delete m_classDescribe;
			return false;
		}
		m_istr.seekg(-1,ios::cur);
		return true;
}

void CLClassInterpreter::completeClassDescribeFromContent()
{
	string tmp;
	char input[1024] = {0};

	getNextObj(tmp);
	if(tmp == ":")
	{
		getNextObj(tmp);
		this->m_classDescribe->m_superClassname = tmp;

		getNextObj(tmp);
	}

	m_istr.getline(input,sizeof(input),0x0d);
	m_istr.get();
	tmp = input;

	while(tmp != "};")
	{
		if(tmp == KEY_WORD_PUBLIC||tmp == KEY_WORD_PRIVATE||tmp == KEY_WORD_PROTECTED||tmp == ""||tmp[0] == 0x0d)
		{
		
		}
		else if( getStatementType(tmp) != VAR )
		{

		}
		else
		{
			m_classDescribe->m_elementList.push_back(getNewElement(tmp));
		}

		memset(input,0,sizeof(input));

		m_istr.getline(input,sizeof(input ),0x0d);
		m_istr.get();
		tmp = input;
	}

	
}

int	 CLClassInterpreter::getStatementType(string & statement)
{
	if(statement.find("(") != string::npos )
	{
		if(statement.find(VIRTUAL_FLAG) != string::npos )
		{	
			m_classDescribe->m_featrueSet.insert(VIRTUAL_FEATURE);
			return FUNCTION;
		}
		else
		{
			return FUNCTION;
		}
		
	}
	else
	{
		if(statement.find("static") != string::npos )
		{
			return STATIC_VAR;
		}
		else
		{
			return VAR;
		}
	}
}

void CLClassInterpreter::getNextObj(string &in ,string &out ,bool if_reset)
{
	static string::iterator it;
	out = "";
	if(if_reset)
		it = in.begin();
	while( it != in.end())
	{
		if(*it == ' '||*it == '\t'||*it == ';')
		{
			if(out == "")
			{
				it++;
				continue;
			}
			else{
				it++;
				break;
			}
		}
		if(*it == '*')
		{
			if(out == "")
			{
				out.push_back(*it);
				it++;
				break;
			}
			else
			{
				break;
			}
		}
		out.push_back(*it);
		it++;
	}
}

CLAbstractType * CLClassInterpreter::getNewElement(string & statement)
{
	string type;

	getNextObj(statement,type,true);
	while((type.find("const",0)!=string::npos)||(type.find("static",0)!=string::npos)||(type.find("*",0)!=string::npos)||(type.find("unsigned",0)!=string::npos)||(type.find("signed",0)!=string::npos))
	{
		getNextObj(statement,type,false);
	}
	
	static map<string, CLAbstractType * (*)() >::iterator it = s_ElementGeterFunctionMap.find(type);
	if(it == s_ElementGeterFunctionMap.end())
	{
		if(type == "")
			return NULL;
		else
			type = "UserDef";

		it = s_ElementGeterFunctionMap.find(type);
	}	

	CLAbstractType * ret = it->second();
	ret->analysisFromStatement(statement);

	return ret;

}

CLAbstractType * CLClassInterpreter::getBuiltIn()
{
	return new CLBuiltInType;
}

CLAbstractType * CLClassInterpreter::getString()
{
	return new CLStringType;
}

CLAbstractType * CLClassInterpreter::getUserDef()
{
	return new CLUserDefType;
}


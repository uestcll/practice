#include "CLMsgClassLoader.h"
#include "CLMsgClassManager.h"
#include "CLMsgClass.h"
#include "CLMsgElementMap.h"

#include "CLBasicType.h"
#include "CLPointerType.h"
#include "CLStringType.h"
#include "CLUserType.h"

#include <fstream>
namespace filedeal
{
	void getNextObj(ifstream & istr,string &ret)
	{
		ret = "";
		char tmp;

		while(tmp = istr.get())
			if(tmp == ' '||tmp =='\n')
				continue;
			else if((tmp<='9'&&tmp>='0')||(tmp<='z'&&tmp>='a')||(tmp<='Z'&&tmp>='A'))
			{
				ret.push_back(tmp);
				continue;
			}
			else if(ret != "")
			{
				istr.seekg(-1,ios::cur);
				break;
			}
			else
			{
				ret.push_back(tmp);
				
				if(tmp == ':')
				{
					tmp = istr.get();
					
					if(tmp == ':')
					{
						ret.push_back(tmp);
					}
					else
						istr.seekg(-1,ios::cur);
				}
				break;
			}
		
	}

	bool classJudge(ifstream & istr,string & classname,bool & is_needSerial,bool & is_struct)
	{
		string tmp;
		getNextObj(istr,tmp);
		while((tmp!=STRUCT_FLAG&&tmp!=CLASS_FLAG)&&tmp!= CLMsgClassLoader::serialFlag)
			getNextObj(istr,tmp);

		
		if(tmp == CLMsgClassLoader::serialFlag)
		{
			getNextObj(istr,tmp);
			is_needSerial = true;
		}
		if(tmp ==STRUCT_FLAG)
		{
			is_struct = true;	
		}

		getNextObj(istr,classname);;
		getNextObj(istr,tmp);
		if(tmp == ";")
			return false;
		istr.seekg(-1,ios::cur);
		return true;
	}
	bool sentenceJudge(string &in)
	{
		if(in.find("(")!= string::npos)
			return true;
		else
			return false;
	}

	void classContent(ifstream & istr,CLMsgClass * t_class)
	{
		string tmp;
		getNextObj(istr,tmp);
		if(tmp == ":")
		{
			getNextObj(istr,tmp);
			t_class->addSuperClass(tmp);
			getNextObj(istr,tmp);
		}
		istr.sync();
		getline(istr,tmp,'\n');
		while(tmp != "}")
		{
			if(tmp == KEY_WORD_PUBLIC||tmp == KEY_WORD_PRIVATE||tmp == KEY_WORD_PROTECTED)
			{
				istr.sync();
				getline(istr,tmp,'\n');
			}
			else
			{
				t_class->addMemberVar(CLMsgElementMap::getInstance()->initNewElement(tmp))->newVarDefinitionSentence(tmp);
			}
			istr.sync();
			getline(istr,tmp,'\n');
		}
	}

}


const string CLMsgClassLoader::serialFlag = "_SERIAL_";

CLMsgClassLoader::CLMsgClassLoader(const CLMsgClassManager * msgClassMng,string * filename,int strNum):
m_msgClassMng((CLMsgClassManager *)msgClassMng),
m_filename(filename),m_strNum(strNum)
{
	loadFileFromDisk();
}

void CLMsgClassLoader::loadFileFromDisk()
{
	for(int i = 0;i<m_strNum;i++)
	{
		loadSingleFile(m_filename[i]);
	}
}

void CLMsgClassLoader::loadSingleFile(string & filename)
{
	ifstream istr(filename.c_str(),ios::binary);
	string	classname;
	bool	is_needSerial;
	bool	is_struct = false;
	
	while(istr.peek()!= EOF)
	{
		using filedeal::classJudge;
		using filedeal::classContent;
	
		if(classJudge(istr,classname,is_needSerial,is_struct))
		{
			CLMsgClass * t_class = m_msgClassMng->classRegister(classname,is_needSerial,is_struct);
			classContent(istr,t_class);
		}
	}
	
	istr.close();
}
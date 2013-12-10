#include "CLMsgElement.h"


CLMsgElement::CLMsgElement():type_len(0),m_value_name(""),m_is_ptr(false)
	,m_is_array(false),m_array_len(0),m_off(0){};
CLMsgElement::~CLMsgElement(){};


void CLMsgElement::getNextItem(string &tmp,string &out,bool if_reset)
{
	static string::iterator it;
	out = "";
	if(if_reset)
		it = tmp.begin();
	while( it != tmp.end())
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
		if(*it == '*'||*it == '['||*it == ']')
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

string CLMsgElement::getNewName()
{
	static string Name = "m_char_cla_no";
	static string No = "0";

	int Nodec = atoi(No.c_str());
	Nodec++;
	char Nochar[32] = {0};
	sprintf(Nochar,"%d",Nodec);
	No = Nochar;

	return Name+No;
}
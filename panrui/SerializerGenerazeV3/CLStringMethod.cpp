#include "CLStringMethod.h"
#include "CLAbstractType.h"

string CLStringMethod::getDeserialMethod(CLAbstractType * v_elementType)
{
	string t_strOff = to_string((long long )v_elementType->getOff());

	if(v_elementType->getPtrFlag()&&v_elementType->getArrFlag())
	{
		string ret = "(string *)out["+t_strOff+"] = new string["+to_string((long long)v_elementType->getArrSize())+"]";
		long long  count = 0;

		long long t_arrSize = v_elementType->getArrSize();
		while(t_arrSize-- )
		{
			ret += "(string *)out["+t_strOff+"]["+to_string(count)+"].append(&in[m_buf_pos+4],*((int *)&in[m_buf_pos]));\n\tm_buf_pos += *((int *)&in[m_buf_pos]+4;\n\t";
		
			count++;
		}
		
		return ret;
	}
	else if(v_elementType->getArrFlag() )
	{
		string ret;
		long long  count = 0;

		long long t_arrSize = v_elementType->getArrSize();
		while(t_arrSize-- )
		{
			ret += "(string *)&out["+t_strOff+"]["+to_string(count)+"].append(&in[m_buf_pos+4],*((int *)&in[m_buf_pos]));\n\tm_buf_pos += *((int *)&in[m_buf_pos]+4;\n\t";
		
			count++;
		}
		
		return ret;
	}
	else if(v_elementType->getPtrFlag())
	{
		string ret = "(string *)out["+t_strOff+"] = new string";
		ret += "(string *)out["+t_strOff+"]->append(&in[m_buf_pos+4],*((int *)&in[m_buf_pos]));\n\tm_buf_pos += *((int *)&in[m_buf_pos]+4;\n\t";

		return ret;
	}
	else
	{
		string ret = "(string *)&out["+t_strOff+"]->append(&in[m_buf_pos+4],*((int *)&in[m_buf_pos]));\n\tm_buf_pos += *((int *)&in[m_buf_pos]+4;\n\t";

		return ret;
	}
}

string CLStringMethod::getSerialMethod(CLAbstractType * v_elementType)
{
	string t_strOff = to_string((long long )v_elementType->getOff());

	if(v_elementType->getPtrFlag()&&v_elementType->getArrFlag())
	{
		long long	   count = 0;
		string ret;

		long long t_arrSize = v_elementType->getArrSize();
		while(t_arrSize--)
		{
			string ret = "*((int *)&out[m_buf_pos]) = ((string *)in["+t_strOff+"])["+to_string(count)+"].length();\n\tm_buf_pos+=4;\n\t";
			ret += "memcpy(&out[m_buf_pos],((string *)in["+t_strOff+"])["+to_string(count)+"].c_str(),((string *)in["+t_strOff+"])["+to_string(count)+"].length());\n\tm_buf_pos+=((string *&in["+t_strOff+"])["+to_string(count)+"].length();\n\t";

			count++;
		}
		
		return ret;
	}
	else if(v_elementType->getArrFlag() )
	{
		long long	   count = 0;
		string ret;

		long long t_arrSize = v_elementType->getArrSize();
		while(t_arrSize--)
		{
			string ret = "*((int *)&out[m_buf_pos]) = ((string *)&in["+t_strOff+"])["+to_string(count)+"].length();\n\tm_buf_pos+=4;\n\t";
			ret += "memcpy(&out[m_buf_pos],((string *)&in["+t_strOff+"])["+to_string(count)+"].c_str(),((string *)&in["+t_strOff+"])["+to_string(count)+"].length());\n\tm_buf_pos+=((string *)&in["+t_strOff+"])["+to_string(count)+"].length();\n\t";

			count++;
		}
		
		return ret;
	}
	else if(v_elementType->getPtrFlag())
	{
		string ret = "*((int *)&out[m_buf_pos]) = ((string *)in["+t_strOff+"])->length();\n\tm_buf_pos+=4;\n\t";
		ret += "memcpy(&out[m_buf_pos],((string *)in["+t_strOff+"])->c_str(),((string *)in["+t_strOff+"])->length());\n\tm_buf_pos+=((string *)in["+t_strOff+"])->length();\n\t";
		
		return ret;
	}
	else
	{
		string ret = "*((int *)&out[m_buf_pos]) = ((string *)&in["+t_strOff+"])->length();\n\tm_buf_pos+=4;\n\t";
		ret += "memcpy(&out[m_buf_pos],((string *)&in["+t_strOff+"])->c_str(),((string *)&in["+t_strOff+"])->length());\n\tm_buf_pos+=((string *)&in["+t_strOff+"])->length();\n\t";

		return ret;
	}
}

string CLStringMethod::getSize(CLAbstractType * v_elementType)
{
	string t_strOff = to_string((long long )v_elementType->getOff());

	if(v_elementType->getPtrFlag()&&v_elementType->getArrFlag())
	{
		long long	   count = 0;
		string ret;

		long long t_arrSize = v_elementType->getArrSize();
		while(t_arrSize--)
		{
			ret += "((string *)in["+t_strOff+"])["+to_string(count++)+"].length()+4*"+to_string(t_arrSize)+";";
		}
		
		return ret;
	}
	else if(v_elementType->getArrFlag() )
	{
		long long	   count = 0;
		string ret;

		long long t_arrSize = v_elementType->getArrSize();
		while(t_arrSize--)
		{
			ret += "((string *)&in["+t_strOff+"])["+to_string(count++)+"].length()+4*"+to_string(t_arrSize)+";";
		}
		
		return ret;
	}
	else if(v_elementType->getPtrFlag())
	{
		return "((string *)in["+t_strOff+"])->length()+4;";
	}
	else
	{
		return "((string *)&in["+t_strOff+"])->length()+4;";
	}
}
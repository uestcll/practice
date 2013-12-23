#include "CLBuiltInMethod.h"
#include "CLAbstractType.h"

string CLBuiltInMethod::getDeserialMethod(CLAbstractType * v_elementType)
{
	string t_type = identifyType(v_elementType);

	string t_strOff = to_string((long long )v_elementType->getOff());

	if(v_elementType->getPtrFlag()&&v_elementType->getArrFlag())
	{
		string t_strTypeLen = "8";	
		string t_arrSize = to_string((long long )v_elementType->getTypeLen() * (long long)v_elementType->getArrSize());	

		string ret = "("+t_type+" *)out["+t_strOff+"] = new "+t_type+";\n\t";
		ret += "memcpy((char *)out["+t_strOff+"],&in[m_buf_pos],"+t_strTypeLen+")\n\tm_buf_pos += "+t_strTypeLen+";\n\t";

		return ret;
	}
	else if(v_elementType->getArrFlag())
	{
		string t_strTypeLen = to_string((long long )v_elementType->getTypeLen() * (long long)v_elementType->getArrSize());	

		string ret = "memcpy(&out["+t_strOff+"],&in[m_buf_pos],"+t_strTypeLen+")\n\tm_buf_pos += "+t_strTypeLen+";\n\t";

		return ret;
	}
	else if(v_elementType->getPtrFlag())
	{
		string t_strTypeLen = "8";	

		string ret = "("+t_type+" *)out["+t_strOff+"] = new "+t_type+";\n\t";
		ret += "*(("+t_type+" *)out["+t_strOff+"]) = *(("+t_type+" *)&in[m_buf_pos]);\n\tm_buf_pos += "+t_strTypeLen+";\n\t";

		return ret;
	}
	else
	{
		string t_strTypeLen = to_string((long long )v_elementType->getTypeLen());

		string ret = "*(("+t_type+" *)&out["+t_strOff+"]) = *(("+t_type+" *)&in[m_buf_pos]);\n\tm_buf_pos += "+t_strTypeLen+";\n\t";

		return ret;
	}
}

string CLBuiltInMethod::getSerialMethod(CLAbstractType * v_elementType)
{
	string t_type = identifyType(v_elementType);

	string t_strOff = to_string((long long )v_elementType->getOff());

	if(v_elementType->getPtrFlag()&&v_elementType->getArrFlag())
	{
		string t_arrSize = to_string((long long )v_elementType->getTypeLen() * (long long)v_elementType->getArrSize());	

		string ret = "memcpy(&out[m_buf_pos],(char *)in["+t_strOff+"],"+t_arrSize+")\n\tm_buf_pos += "+t_arrSize+";\n\t";

		return ret;
	}
	else if(v_elementType->getArrFlag())
	{
		string t_arrSize = to_string((long long )v_elementType->getTypeLen() * (long long)v_elementType->getArrSize());	

		string ret = "memcpy(&out[m_buf_pos],(char *)&in["+t_strOff+"],"+t_arrSize+")\n\tm_buf_pos += "+t_arrSize+";\n\t";

		return ret;
	}
	else if(v_elementType->getPtrFlag())
	{
		string t_strTypeLen = to_string((long long )v_elementType->getTypeLen());	

		string ret = "*(("+t_type+" *)&out[m_buf_pos]) = *(("+t_type+" *)in["+t_strOff+"]);\n\tm_buf_pos += "+t_strTypeLen+";\n\t";

		return ret;
	}
	else
	{
		string t_strTypeLen = to_string((long long )v_elementType->getTypeLen());

		string ret = "*(("+t_type+" *)&out[m_buf_pos]) = *(("+t_type+" *)&in["+t_strOff+"]);\n\tm_buf_pos += "+t_strTypeLen+";\n\t";

		return ret;
	}
}

string CLBuiltInMethod::getSize(CLAbstractType * v_elementType)
{
	if(v_elementType->getPtrFlag()&&v_elementType->getArrFlag())
	{
		return to_string((long long )v_elementType->getTypeLen() * (long long)v_elementType->getArrSize());
	}
	else if(v_elementType->getArrFlag())
	{
		return to_string((long long )v_elementType->getTypeLen() * (long long)v_elementType->getArrSize());
	}
	else if(v_elementType->getPtrFlag())
	{
		return to_string((long long )v_elementType->getTypeLen());
	}
	else
	{
		return to_string((long long )v_elementType->getTypeLen());
	}
}

string CLBuiltInMethod::identifyType(CLAbstractType * v_elementType )
{
	string t_type;

	if(v_elementType->getTypeLen() == 8)
	{
		t_type = "long";
	}
	else if(v_elementType->getTypeLen() == 4)
	{
		t_type = "int";
	}
	else if(v_elementType->getTypeLen() == 2)
	{
		t_type = "short";
	}
	else
	{
		t_type = "char";
	}

	return t_type;
}
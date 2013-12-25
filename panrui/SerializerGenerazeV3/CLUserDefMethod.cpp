#include "CLUserDefMethod.h"
#include "CLAbstractType.h"
#include "CLUserDefType.h"


CLUserDefMethod::CLUserDefMethod()
{

}

CLUserDefMethod::~CLUserDefMethod()
{

}

string CLUserDefMethod::getDeserialMethod(CLAbstractType * v_elementType ,string base_ptr )
{
	string t_strOff = to_string((long long )v_elementType->getOff());
	CLUserDefType * t_ud = dynamic_cast<CLUserDefType *>(v_elementType);

	string uniqueName = getUniqueName();
	string ret = t_ud->getUserDefName()+"deserializer "+uniqueName+";\n\t";


	if(v_elementType->getPtrFlag()&&v_elementType->getArrFlag())
	{

	}
	else if(v_elementType->getArrFlag() )
	{

	}
	else if(v_elementType->getPtrFlag())
	{
		ret += "(char *)&"+base_ptr+"["+t_strOff+"] = (char *)"+uniqueName+".getNewObject(&in[m_buf_pos]);";
	}
	else
	{
		ret += uniqueName+".paddingObj(&in[m_buf_pos],(char *)&"+base_ptr+"["+t_strOff+"]);\n\t";
	}

	return ret;
}

string CLUserDefMethod::getSerialMethod(CLAbstractType * v_elementType ,string base_ptr )
{
	string t_strOff = to_string((long long )v_elementType->getOff());
	CLUserDefType * t_ud = dynamic_cast<CLUserDefType *>(v_elementType);

	string uniqueName = getUniqueName();
	string ret = t_ud->getUserDefName()+"serializer "+uniqueName+";\n\t";


	if(v_elementType->getPtrFlag()&&v_elementType->getArrFlag())
	{

	}
	else if(v_elementType->getArrFlag() )
	{

	}
	else if(v_elementType->getPtrFlag())
	{
		ret += uniqueName+".serialInfo((char *)"+base_ptr+"["+t_strOff+"],&out[m_buf_pos]);\n\t";
	}
	else
	{
		ret += uniqueName+".serialInfo((char *)&"+base_ptr+"["+t_strOff+"],&out[m_buf_pos]);\n\t";
	}

	return ret;
}

string CLUserDefMethod::getSize(CLAbstractType * v_elementType ,string base_ptr )
{
	string t_strOff = to_string((long long )v_elementType->getOff());
	CLUserDefType * t_ud = dynamic_cast<CLUserDefType *>(v_elementType);

	string uniqueName = getUniqueName();
	string ret = t_ud->getUserDefName()+"serializer "+uniqueName+";\n\t";

	if(v_elementType->getPtrFlag()&&v_elementType->getArrFlag())
	{

	}
	else if(v_elementType->getArrFlag() )
	{

	}
	else if(v_elementType->getPtrFlag())
	{
		ret += "bufsize +="+uniqueName+".countBufSize((char *)"+base_ptr+"["+t_strOff+"]);\n\t";
	}
	else
	{
		ret += "bufsize +="+uniqueName+".countBufSize((char *)&"+base_ptr+"["+t_strOff+"]);\n\t";
	}

	return ret;
}

string CLUserDefMethod::getUniqueName()
{
	static long long unique;
	return "objNo"+to_string(unique++);
}
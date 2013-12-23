#include "CLUserDefMethod.h"
#include "CLAbstractType.h"
#include "CLUserDefType.h"

string CLUserDefMethod::getDeserialMethod(CLAbstractType * v_elementType)
{
	if(v_elementType->getPtrFlag()&&v_elementType->getArrFlag())
	{

	}
	else if(v_elementType->getArrFlag() )
	{

	}
	else if(v_elementType->getPtrFlag())
	{

	}
	else
	{

	}
}

string CLUserDefMethod::getSerialMethod(CLAbstractType * v_elementType)
{
	if(v_elementType->getPtrFlag()&&v_elementType->getArrFlag())
	{

	}
	else if(v_elementType->getArrFlag() )
	{

	}
	else if(v_elementType->getPtrFlag())
	{

	}
	else
	{

	}
}

string CLUserDefMethod::getSize(CLAbstractType * v_elementType)
{
	string t_strOff = to_string((long long )v_elementType->getOff());
	CLUserDefType * t_ud = dynamic_cast<CLUserDefType *>(v_elementType);

	if(v_elementType->getPtrFlag()&&v_elementType->getArrFlag())
	{

	}
	else if(v_elementType->getArrFlag() )
	{

	}
	else if(v_elementType->getPtrFlag())
	{

	}
	else
	{

	}
}
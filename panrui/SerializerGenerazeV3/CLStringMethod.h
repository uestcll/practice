#ifndef CLStringMethod_H
#define CLStringMethod_H

#include "CLAbstractMethod.h"

class CLStringMethod:public CLAbstractMethod
{
public:

	CLStringMethod();
	virtual ~CLStringMethod();

	virtual string getSerialMethod(CLAbstractType * v_elementType ,string base_ptr = "out");
	virtual string getDeserialMethod(CLAbstractType * v_elementType ,string base_ptr = "in");
	virtual string getSize(CLAbstractType * v_elementType ,string base_ptr = "in");

private:
	
	CLStringMethod(const CLStringMethod & );
	const CLStringMethod & operator = (const CLStringMethod & );

private:

};

#endif
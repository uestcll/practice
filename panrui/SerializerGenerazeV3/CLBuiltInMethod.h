#ifndef CLBuiltInMethod_H
#define CLBuiltInMethod_H

#include "CLAbstractMethod.h"

class CLBuiltInMethod:public CLAbstractMethod
{
public:

	CLBuiltInMethod();
	virtual ~CLBuiltInMethod();
	
	virtual string getSerialMethod(CLAbstractType * v_elementType ,string base_ptr = "in" );
	virtual string getDeserialMethod(CLAbstractType * v_elementType ,string base_ptr = "out" );
	virtual string getSize(CLAbstractType * v_elementType ,string base_ptr = "in" );

private:
	
	CLBuiltInMethod(const CLBuiltInMethod & );
	const CLBuiltInMethod & operator = (const CLBuiltInMethod & );

private:
	string identifyType(CLAbstractType *);
};

#endif
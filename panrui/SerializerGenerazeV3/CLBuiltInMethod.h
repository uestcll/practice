#ifndef CLBuiltInMethod_H
#define CLBuiltInMethod_H

#include "CLAbstractMethod.h"

class CLBuiltInMethod:public CLAbstractMethod
{
public:

	CLBuiltInMethod();
	virtual ~CLBuiltInMethod();
	
	virtual string getSerialMethod(CLAbstractType * v_elementType );
	virtual string getDeserialMethod(CLAbstractType * v_elementType );
	virtual string getSize(CLAbstractType * v_elementType );

private:
	
	CLBuiltInMethod(const CLBuiltInMethod & );
	const CLBuiltInMethod & operator = (const CLBuiltInMethod & );

private:
	string identifyType(CLAbstractType *);
};

#endif
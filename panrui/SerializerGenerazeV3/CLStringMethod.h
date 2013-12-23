#ifndef CLStringMethod_H
#define CLStringMethod_H

#include "CLAbstractMethod.h"

class CLStringMethod:public CLAbstractMethod
{
public:

	CLStringMethod();
	virtual ~CLStringMethod();

	virtual string getSerialMethod(CLAbstractType * v_elementType );
	virtual string getDeserialMethod(CLAbstractType * v_elementType );
	virtual string getSize(CLAbstractType * v_elementType );

private:
	
	CLStringMethod(const CLStringMethod & );
	const CLStringMethod & operator = (const CLStringMethod & );

private:

};

#endif
#ifndef CLUserDefMethod_H
#define CLUserDefMethod_H

#include "CLAbstractMethod.h"

class CLUserDefMethod:public CLAbstractMethod
{
public:

	CLUserDefMethod();
	virtual ~CLUserDefMethod();

	virtual string getSerialMethod(CLAbstractType * v_elementType ,string base_ptr = "out");
	virtual string getDeserialMethod(CLAbstractType * v_elementType ,string base_ptr = "in");
	virtual string getSize(CLAbstractType * v_elementType ,string base_ptr = "in");

private:
	
	CLUserDefMethod(const CLUserDefMethod & );
	const CLUserDefMethod & operator = (const CLUserDefMethod & );

private:

	static string getUniqueName();

};

#endif
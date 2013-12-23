#ifndef CLAbstractMethod_H
#define CLAbstractMethod_H

#include <string>

using namespace std;

class CLAbstractType;

class CLAbstractMethod
{
public:

	CLAbstractMethod();
	virtual ~CLAbstractMethod();

	virtual string getSerialMethod(CLAbstractType * v_elementType) = 0;
	virtual string getDeserialMethod(CLAbstractType * v_elementType) = 0;
	virtual string getSize(CLAbstractType * v_elementType) = 0;

private:

	CLAbstractMethod(const CLAbstractMethod & );
	const CLAbstractMethod & operator = (const CLAbstractMethod & );

};

#endif
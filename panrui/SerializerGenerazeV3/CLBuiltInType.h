#ifndef CLBuiltInType_H
#define CLBuiltInType_H

#include "CLAbstractType.h"

class CLBuiltInType:public CLAbstractType
{
public:

	CLBuiltInType();
	virtual ~CLBuiltInType();
	virtual void analysisFromStatement(string  & );

private:

	CLBuiltInType(const CLBuiltInType &);
	const CLBuiltInType & operator = (const CLBuiltInType &);

private:




};

#endif
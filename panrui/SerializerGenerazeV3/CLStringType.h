#ifndef CLStringType_H
#define CLStringType_H

#include "CLAbstractType.h"

class CLStringType:public CLAbstractType
{
public:

	CLStringType();
	virtual ~CLStringType();
	virtual void analysisFromStatement(string  & );

private:

	CLStringType(const CLStringType &);
	const CLStringType & operator = (const CLStringType &);

private:




};

#endif